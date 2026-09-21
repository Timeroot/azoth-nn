/* On-device char next-key predictor v3 for the ROG Azoth (nRF52840 / M4F @64MHz).
 *
 * BIG vocab V=72:  a-z(0..25) 0-9(26..35) space(36) TAB(37) NEWLINE(38)
 *   CAPESC(39, its OWN token) and 32 ASCII-order punctuation(40..71):
 *   ! " # $ % & ' ( ) * + , - . /  :  ;  <  =  >  ?  @  [  \  ]  ^  _  `  {  |  }  ~
 *
 * TWO-TIMESCALE recurrence:
 *   - FAST char GRU (state hf[HF]) updates on EVERY typed symbol.
 *   - SLOW word GRU (state hs[HS]) updates ONLY right after a NON-alphabetic
 *     symbol (word boundary; alphabetic = a-z or CAPESC), consuming hf.
 *   - Prediction reads OUT @ [hf ; hs ; emb(last)]  (input->output skip).
 *
 * Weights int8 (per-output-row symmetric quant) + float32 scales/biases + float32
 * embedding, in flash at 0x50000 (byte offsets from nn_weights.h).  Compute in
 * float32 on the FPU:  acc = sum_i (float)w_int8[i]*x[i];  out = acc*scale + bias.
 *
 * Persistent state : hf[HF]+hs[HS] float32 (<=1KB) at 0x2003f100.
 * Shadow (1-level undo): prev hf/hs + disp at 0x2003f600.
 * Transient scratch: gate accumulators at 0x2003b000 (<=16KB).
 *
 * ------------- on-device INPUT mapping (HID report -> symbol stream) -------------
 * RPT[] = live u16 keycode array @0x2000b6f8, count @0x20003370.
 * Shift held = keycode 0xe1 (LShift) or 0xe5 (RShift) present.
 * Main key   = first non-modifier keycode >= 0x04 in the report; edge-detected on
 *              token (shift<<16)|keycode so held/repeat keys fire once.
 *   letters 0x04..0x1d -> a..z ; if Shift -> emit CAPESC then the lowercase letter.
 *   digits  0x1e..0x27 -> 1..9,0 ; if Shift -> ! @ # $ % ^ & * ( ) respectively.
 *   Enter 0x28 -> NEWLINE ; Tab 0x2b -> TAB ; Space 0x2c -> space.
 *   0x2d - _ | 0x2e = + | 0x2f [ { | 0x30 ] } | 0x31 \ | | 0x33 ; : |
 *   0x34 ' " | 0x35 ` ~ | 0x36 , < | 0x37 . > | 0x38 / ?   (unshifted/shifted).
 *   Backspace 0x2a -> ONE-LEVEL undo (restore shadow: prev fast+slow state + disp).
 *   Any other key (arrows, Caps, Ins/Home/..., F-keys, Esc, GUI, keypad) -> IGNORE.
 */
#include <stdint.h>
#include "nn_weights.h"       /* VOCAB EDIM HF HS OUT_SKIP OUTIN + OFF_* offsets */

#define STRIDE 0x80u
#define MAG    0x460F5DEDu          /* NEW unique seed magic per build (bump each flash) */
#define E   EDIM
#define V   VOCAB
#define HFF HF
#define HSS HS
#define SFLOATS (NLAYERS_FAST*HFF + HSS)   /* persistent recurrent-state floats  */

/* RAM (all confirmed-free above the firmware's working set).  State+shadow live
 * just above 0x2003f100; scratch fills 0x2003b000..0x2003f000 (16 KB). */
#define M      ((volatile uint32_t*)0x2003f000u)  /* [0]magic [1]token [2]disp [4]shadow */
#define PREDS  ((volatile uint8_t*)0x2003f00cu)   /* 3 predicted symbols (word M[3])     */
#define ST     ((float*)0x2003f100u)              /* persistent: hf0..hf{FL-1}, hs        */
#define SHF    (ST + SFLOATS)                      /* shadow copy of the state (undo)     */
#define SHDISP (*(volatile uint32_t*)(SHF + SFLOATS))  /* shadow display symbol           */
#define GI     ((float*)0x2003b000u)              /* scratch gate acc (input side, 8KB)  */
#define GH     ((float*)0x2003d000u)              /* scratch gate acc (hidden side, 8KB) */
#define DIRTY  (*(volatile uint8_t*)0x200034bau)
#define RPTCNT (*(volatile uint32_t*)0x20003370u)
#define RPT    ((volatile uint16_t*)0x2000b6f8u)

/* symbol ids */
#define SYM_SP 36
#define SYM_TAB 37
#define SYM_NL 38
#define SYM_CAP 39
#define IS_ALPHA(s) ((s) < 26 || (s) == SYM_CAP)     /* word-interior char */

/* weight blob base in flash.  With the expanded budget the blob is flashed into
 * the region above the old DFU ceiling (0x61000..0xdb000) via self-programming;
 * set -DWBASE=<addr> to wherever this model's nn_weights.bin was written. */
#ifndef WBASE
#define WBASE 0x61000u
#endif
#define W_IS  ((const int8_t*)(WBASE + OFF_WIS))
#define W_HS  ((const int8_t*)(WBASE + OFF_WHS))
#define W_OUT ((const int8_t*)(WBASE + OFF_OUT))
#define EMB   ((const float*)  (WBASE + OFF_EMB))
#define S_IS  ((const float*)  (WBASE + OFF_WIS_SCALE))
#define S_HS  ((const float*)  (WBASE + OFF_WHS_SCALE))
#define S_OUT ((const float*)  (WBASE + OFF_OUT_SCALE))
#define B_IS  ((const float*)  (WBASE + OFF_BIS))
#define B_HS  ((const float*)  (WBASE + OFF_BHS))
#define B_OUT ((const float*)  (WBASE + OFF_BOUT))

/* per fast-layer weight pointers (built into arrays for the layer loop) */
static const int8_t *const W_IFL[NLAYERS_FAST] = { (const int8_t*)(WBASE+OFF_WIF0)
#if NLAYERS_FAST>=2
    , (const int8_t*)(WBASE+OFF_WIF1)
#endif
#if NLAYERS_FAST>=3
    , (const int8_t*)(WBASE+OFF_WIF2)
#endif
};
static const int8_t *const W_HFL[NLAYERS_FAST] = { (const int8_t*)(WBASE+OFF_WHF0)
#if NLAYERS_FAST>=2
    , (const int8_t*)(WBASE+OFF_WHF1)
#endif
#if NLAYERS_FAST>=3
    , (const int8_t*)(WBASE+OFF_WHF2)
#endif
};
static const float *const S_IFL[NLAYERS_FAST] = { (const float*)(WBASE+OFF_WIF0_SCALE)
#if NLAYERS_FAST>=2
    , (const float*)(WBASE+OFF_WIF1_SCALE)
#endif
#if NLAYERS_FAST>=3
    , (const float*)(WBASE+OFF_WIF2_SCALE)
#endif
};
static const float *const S_HFL[NLAYERS_FAST] = { (const float*)(WBASE+OFF_WHF0_SCALE)
#if NLAYERS_FAST>=2
    , (const float*)(WBASE+OFF_WHF1_SCALE)
#endif
#if NLAYERS_FAST>=3
    , (const float*)(WBASE+OFF_WHF2_SCALE)
#endif
};
static const float *const B_IFL[NLAYERS_FAST] = { (const float*)(WBASE+OFF_BIF0)
#if NLAYERS_FAST>=2
    , (const float*)(WBASE+OFF_BIF1)
#endif
#if NLAYERS_FAST>=3
    , (const float*)(WBASE+OFF_BIF2)
#endif
};
static const float *const B_HFL[NLAYERS_FAST] = { (const float*)(WBASE+OFF_BHF0)
#if NLAYERS_FAST>=2
    , (const float*)(WBASE+OFF_BHF1)
#endif
#if NLAYERS_FAST>=3
    , (const float*)(WBASE+OFF_BHF2)
#endif
};

static const uint8_t FONT[72][8] = {
  {0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0x00}, /*  0 a */
  {0x3F,0x66,0x66,0x3E,0x66,0x66,0x3F,0x00}, /*  1 b */
  {0x3C,0x66,0x03,0x03,0x03,0x66,0x3C,0x00}, /*  2 c */
  {0x1F,0x36,0x66,0x66,0x66,0x36,0x1F,0x00}, /*  3 d */
  {0x7F,0x46,0x16,0x1E,0x16,0x46,0x7F,0x00}, /*  4 e */
  {0x7F,0x46,0x16,0x1E,0x16,0x06,0x0F,0x00}, /*  5 f */
  {0x3C,0x66,0x03,0x03,0x73,0x66,0x7C,0x00}, /*  6 g */
  {0x33,0x33,0x33,0x3F,0x33,0x33,0x33,0x00}, /*  7 h */
  {0x1E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00}, /*  8 i */
  {0x78,0x30,0x30,0x30,0x33,0x33,0x1E,0x00}, /*  9 j */
  {0x67,0x66,0x36,0x1E,0x36,0x66,0x67,0x00}, /* 10 k */
  {0x0F,0x06,0x06,0x06,0x46,0x66,0x7F,0x00}, /* 11 l */
  {0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00}, /* 12 m */
  {0x63,0x67,0x6F,0x7B,0x73,0x63,0x63,0x00}, /* 13 n */
  {0x1C,0x36,0x63,0x63,0x63,0x36,0x1C,0x00}, /* 14 o */
  {0x3F,0x66,0x66,0x3E,0x06,0x06,0x0F,0x00}, /* 15 p */
  {0x1E,0x33,0x33,0x33,0x3B,0x1E,0x38,0x00}, /* 16 q */
  {0x3F,0x66,0x66,0x3E,0x36,0x66,0x67,0x00}, /* 17 r */
  {0x1E,0x33,0x07,0x0E,0x38,0x33,0x1E,0x00}, /* 18 s */
  {0x3F,0x2D,0x0C,0x0C,0x0C,0x0C,0x1E,0x00}, /* 19 t */
  {0x33,0x33,0x33,0x33,0x33,0x33,0x3F,0x00}, /* 20 u */
  {0x33,0x33,0x33,0x33,0x33,0x1E,0x0C,0x00}, /* 21 v */
  {0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00}, /* 22 w */
  {0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00}, /* 23 x */
  {0x33,0x33,0x33,0x1E,0x0C,0x0C,0x1E,0x00}, /* 24 y */
  {0x7F,0x63,0x31,0x18,0x4C,0x66,0x7F,0x00}, /* 25 z */
  {0x1E,0x21,0x31,0x29,0x25,0x23,0x1E,0x00}, /* 26 0 */
  {0x0C,0x0E,0x0C,0x0C,0x0C,0x0C,0x1E,0x00}, /* 27 1 */
  {0x1E,0x21,0x10,0x08,0x04,0x02,0x3F,0x00}, /* 28 2 */
  {0x1F,0x10,0x08,0x0C,0x10,0x21,0x1E,0x00}, /* 29 3 */
  {0x18,0x14,0x12,0x11,0x3F,0x10,0x10,0x00}, /* 30 4 */
  {0x3F,0x01,0x1F,0x10,0x10,0x11,0x0E,0x00}, /* 31 5 */
  {0x1C,0x02,0x01,0x1F,0x21,0x21,0x1E,0x00}, /* 32 6 */
  {0x3F,0x10,0x08,0x04,0x04,0x02,0x02,0x00}, /* 33 7 */
  {0x1E,0x21,0x21,0x1E,0x21,0x21,0x1E,0x00}, /* 34 8 */
  {0x1E,0x21,0x21,0x3E,0x10,0x08,0x06,0x00}, /* 35 9 */
  {0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00}, /* 36 space */
  {0x00,0x09,0x12,0x24,0x12,0x09,0x00,0x00}, /* 37 tab >> */
  {0x10,0x10,0x10,0x14,0x12,0x1F,0x20,0x00}, /* 38 newline return-arrow */
  {0x0C,0x1E,0x1B,0x2D,0x0C,0x0C,0x0C,0x00}, /* 39 CAPESC up-arrow */
  {0x0C,0x0C,0x0C,0x0C,0x0C,0x00,0x0C,0x00}, /* 40 ! */
  {0x36,0x36,0x12,0x00,0x00,0x00,0x00,0x00}, /* 41 " */
  {0x0A,0x0A,0x1F,0x0A,0x1F,0x0A,0x0A,0x00}, /* 42 # */
  {0x04,0x1E,0x05,0x0E,0x14,0x1F,0x04,0x00}, /* 43 $ */
  {0x23,0x13,0x08,0x04,0x62,0x31,0x00,0x00}, /* 44 % */
  {0x06,0x09,0x05,0x02,0x15,0x09,0x16,0x00}, /* 45 & */
  {0x0C,0x0C,0x04,0x00,0x00,0x00,0x00,0x00}, /* 46 ' */
  {0x08,0x04,0x02,0x02,0x02,0x04,0x08,0x00}, /* 47 ( */
  {0x02,0x04,0x08,0x08,0x08,0x04,0x02,0x00}, /* 48 ) */
  {0x00,0x15,0x0E,0x1F,0x0E,0x15,0x00,0x00}, /* 49 * */
  {0x00,0x04,0x04,0x1F,0x04,0x04,0x00,0x00}, /* 50 + */
  {0x00,0x00,0x00,0x00,0x0C,0x0C,0x04,0x00}, /* 51 , */
  {0x00,0x00,0x00,0x1F,0x00,0x00,0x00,0x00}, /* 52 - */
  {0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00}, /* 53 . */
  {0x10,0x10,0x08,0x04,0x02,0x01,0x01,0x00}, /* 54 / */
  {0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x00,0x00}, /* 55 : */
  {0x00,0x0C,0x0C,0x00,0x0C,0x0C,0x04,0x00}, /* 56 ; */
  {0x08,0x04,0x02,0x01,0x02,0x04,0x08,0x00}, /* 57 < */
  {0x00,0x00,0x1F,0x00,0x1F,0x00,0x00,0x00}, /* 58 = */
  {0x02,0x04,0x08,0x10,0x08,0x04,0x02,0x00}, /* 59 > */
  {0x1E,0x21,0x10,0x08,0x04,0x00,0x04,0x00}, /* 60 ? */
  {0x1E,0x21,0x5D,0x55,0x1D,0x01,0x1E,0x00}, /* 61 @ */
  {0x0E,0x02,0x02,0x02,0x02,0x02,0x0E,0x00}, /* 62 [ */
  {0x01,0x01,0x02,0x04,0x08,0x10,0x10,0x00}, /* 63 \ */
  {0x07,0x04,0x04,0x04,0x04,0x04,0x07,0x00}, /* 64 ] */
  {0x04,0x0A,0x11,0x00,0x00,0x00,0x00,0x00}, /* 65 ^ */
  {0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x00}, /* 66 _ */
  {0x04,0x08,0x00,0x00,0x00,0x00,0x00,0x00}, /* 67 ` */
  {0x18,0x04,0x04,0x06,0x04,0x04,0x18,0x00}, /* 68 { */
  {0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x0C,0x00}, /* 69 | */
  {0x06,0x08,0x08,0x30,0x08,0x08,0x06,0x00}, /* 70 } */
  {0x00,0x00,0x26,0x19,0x00,0x00,0x00,0x00}, /* 71 ~ */
};

/* Pade(7,7) tanh, clamped; sigmoid built from it (identical to nn_common.py). */
static float tanhf_(float x){
    if (x > 4.9f) return 1.0f;
    if (x < -4.9f) return -1.0f;
    float x2 = x*x;
    return x*(135135.0f + x2*(17325.0f + x2*(378.0f + x2)))
           / (135135.0f + x2*(62370.0f + x2*(3150.0f + x2*28.0f)));
}
static float sig_(float x){ return 0.5f*(1.0f + tanhf_(0.5f*x)); }

/* one GRU step (torch gate order r,z,n) into state h[HN] with input x[IN]. */
static void gru_step(float *h, int HN, const float *x, int IN,
                     const int8_t *Wi, const float *Si, const float *Bi,
                     const int8_t *Wh, const float *Sh, const float *Bh){
    int G = 3*HN;
    for (int j=0;j<G;j++){
        const int8_t *w=&Wi[j*IN]; float a=0.0f;
        for (int k=0;k<IN;k++) a += (float)w[k]*x[k];
        GI[j] = a*Si[j] + Bi[j];
    }
    for (int j=0;j<G;j++){
        const int8_t *w=&Wh[j*HN]; float a=0.0f;
        for (int k=0;k<HN;k++) a += (float)w[k]*h[k];
        GH[j] = a*Sh[j] + Bh[j];
    }
    for (int i=0;i<HN;i++){
        float r = sig_(GI[i]        + GH[i]);
        float z = sig_(GI[HN+i]     + GH[HN+i]);
        float n = tanhf_(GI[2*HN+i] + r*GH[2*HN+i]);
        h[i] = (1.0f - z)*n + z*h[i];
    }
}

/* full two-timescale advance by one typed symbol (FL stacked fast layers) */
static void tt_step(int sym){
    float *hs = ST + NLAYERS_FAST*HFF;
    const float *x = &EMB[sym*E];
    const float *inp = x; int in_dim = E;
    for (int l=0; l<NLAYERS_FAST; l++){
        float *hf = ST + l*HFF;
        gru_step(hf, HFF, inp, in_dim, W_IFL[l], S_IFL[l], B_IFL[l],
                 W_HFL[l], S_HFL[l], B_HFL[l]);
        inp = hf; in_dim = HFF;
    }
    if (!IS_ALPHA(sym)){       /* word boundary -> update slow from TOP fast state */
        float *top = ST + (NLAYERS_FAST-1)*HFF;
        gru_step(hs, HSS, top, HFF, W_IS, S_IS, B_IS, W_HS, S_HS, B_HS);
    }
}

static void predict(int lastsym){
    const float *hf = ST + (NLAYERS_FAST-1)*HFF, *hs = ST + NLAYERS_FAST*HFF;
    const float *xe = &EMB[lastsym*E];
    float b0=-1e30f,b1=-1e30f,b2=-1e30f; int i0=SYM_SP,i1=SYM_SP,i2=SYM_SP;
    for (int o=0;o<V;o++){
        const int8_t *w=&W_OUT[o*OUTIN]; float a=0.0f;
        for (int k=0;k<HFF;k++) a += (float)w[k]*hf[k];
        for (int k=0;k<HSS;k++) a += (float)w[HFF+k]*hs[k];
#if OUT_SKIP
        for (int k=0;k<E;k++)   a += (float)w[HFF+HSS+k]*xe[k];
#endif
        a = a*S_OUT[o] + B_OUT[o];
        if (a>b0){b2=b1;i2=i1;b1=b0;i1=i0;b0=a;i0=o;}
        else if (a>b1){b2=b1;i2=i1;b1=a;i1=o;}
        else if (a>b2){b2=a;i2=o;}
    }
    PREDS[0]=i0; PREDS[1]=i1; PREDS[2]=i2;
}

/* health: 1 if any state value is non-finite or out of a sane range. */
static int state_bad(void){
    for (int i=0;i<SFLOATS;i++){
        union { float f; uint32_t u; } v; v.f = ST[i];
        uint32_t e = (v.u>>23)&0xFFu;
        if (e==0xFFu) return 1;                 /* inf / nan */
        v.u &= 0x7FFFFFFFu;
        if (v.f > 30.0f) return 1;              /* implausibly large */
    }
    return 0;
}

static void reseed(void){
    for (int i=0;i<SFLOATS;i++) ST[i]=0.0f;
    tt_step(SYM_SP);              /* seed with a space (a boundary: updates all) */
    predict(SYM_SP);
    M[0]=MAG; M[1]=0xFFFFFFFFu; M[2]=SYM_SP; M[4]=0;   /* M[4]=have_shadow */
}

/* map main keycode + shift -> up to 2 symbols; returns count (0 = ignore). */
static int map_key(int kc, int shift, int *s){
    if (kc>=0x04 && kc<=0x1d){                       /* a..z */
        int base=kc-0x04;
        if (shift){ s[0]=SYM_CAP; s[1]=base; return 2; }
        s[0]=base; return 1;
    }
    if (kc>=0x1e && kc<=0x27){                        /* digit row 1..9,0 */
        static const uint8_t sh[10]={40,61,42,43,44,65,45,49,47,48}; /* ! @ # $ % ^ & * ( ) */
        if (shift){ s[0]=sh[kc-0x1e]; return 1; }
        s[0]= (kc==0x27) ? 26 : (27 + (kc-0x1e)); return 1;   /* '0'=26 ; '1'..'9'=27..35 */
    }
    switch (kc){
        case 0x28: s[0]=SYM_NL;  return 1;            /* Enter -> newline */
        case 0x2b: s[0]=SYM_TAB; return 1;            /* Tab */
        case 0x2c: s[0]=SYM_SP;  return 1;            /* Space */
        case 0x2d: s[0]= shift?66:52; return 1;       /* -  _ */
        case 0x2e: s[0]= shift?50:58; return 1;       /* =  + */
        case 0x2f: s[0]= shift?68:62; return 1;       /* [  { */
        case 0x30: s[0]= shift?70:64; return 1;       /* ]  } */
        case 0x31: s[0]= shift?69:63; return 1;       /* \  | */
        case 0x33: s[0]= shift?55:56; return 1;       /* ;  : */
        case 0x34: s[0]= shift?41:46; return 1;       /* '  " */
        case 0x35: s[0]= shift?71:67; return 1;       /* `  ~ */
        case 0x36: s[0]= shift?57:51; return 1;       /* ,  < */
        case 0x37: s[0]= shift?59:53; return 1;       /* .  > */
        case 0x38: s[0]= shift?60:54; return 1;       /* /  ? */
        default:   return 0;                          /* ignore everything else */
    }
}

static void setpx(uint8_t *fb,uint32_t x,uint32_t y,uint8_t nib){
    uint8_t *p=fb+y*STRIDE+(x>>1);
    if(x&1)*p=(*p&0x0F)|(nib<<4); else *p=(*p&0xF0)|nib;
}
static void draw_char(uint8_t *fb,uint32_t px,uint32_t py,uint32_t g,uint8_t nib,uint32_t s){
    for(uint32_t row=0;row<8;row++){ uint8_t bits=FONT[g][row];
        for(uint32_t c=0;c<8;c++) if((bits>>c)&1){ uint32_t x0=px+c*s,y0=py+row*s;
            for(uint32_t a=0;a<s;a++) for(uint32_t b=0;b<s;b++) setpx(fb,x0+a,y0+b,nib); } }
}

__attribute__((section(".text.render"), used))
void render(uint8_t *fb, int len){
    (void)len;
    if (M[0] != MAG || state_bad()) reseed();
    DIRTY=1;

    uint32_t n=RPTCNT; if(n>0x78u)n=0x78u;
    int shift=0, kc=-1;
    for(uint32_t i=0;i<n;i++){ uint16_t k=RPT[i]; if(k==0xe1||k==0xe5) shift=1; }
    for(uint32_t i=0;i<n;i++){ uint16_t k=RPT[i];
        if(k>=0xe0 && k<=0xe7) continue; if(k>=0x04){ kc=(int)k; break; } }

    if (kc>=0){
        uint32_t tok=((uint32_t)shift<<16)|(uint32_t)kc;
        if (tok!=M[1]){
            M[1]=tok;
            if (kc==0x2a){                        /* Backspace: one-level undo */
                if (M[4]){
                    for(int i=0;i<SFLOATS;i++) ST[i]=SHF[i];
                    M[2]=SHDISP;                              /* prev display symbol */
                    M[4]=0;
                    predict((int)M[2]);
                }
            } else {
                int s[2]; int c=map_key(kc,shift,s);
                if (c>0){
                    for(int i=0;i<SFLOATS;i++) SHF[i]=ST[i];      /* snapshot state */
                    SHDISP=M[2];                                  /* snapshot disp  */
                    M[4]=1;
                    for(int j=0;j<c;j++) tt_step(s[j]);
                    M[2]=(uint32_t)s[c-1];
                    predict(s[c-1]);
                }
            }
        }
    } else M[1]=0xFFFFFFFFu;

    uint32_t *pp=(uint32_t*)fb; for(int i=0;i<0x2000/4;i++) pp[i]=0;
    draw_char(fb, 4, 20, M[2], 0xC, 2);                 /* last typed symbol (context) */
    setpx(fb,26,26,0x6); setpx(fb,27,26,0x6); setpx(fb,28,26,0x6);
    draw_char(fb, 60,  16, PREDS[0], 0xF, 5);           /* #1 prediction, biggest */
    draw_char(fb, 150, 20, PREDS[1], 0xA, 4);
    draw_char(fb, 210, 24, PREDS[2], 0x6, 3);
}
