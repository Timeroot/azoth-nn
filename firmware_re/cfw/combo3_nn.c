/* On-device char next-key predictor for the ROG Azoth (nRF52840, M4F @ 64MHz).
 *
 * Vocab V=32:  a-z(0..25), space(26), '(27) .(28) ,(29) -(30) ^(31 CAPITAL ESCAPE).
 * Single-layer GRU, H=256, E=EDIM; optional input->output skip (OUT reads
 * [h ; emb(last_sym)]).  Weights int8 (per-output-row symmetric quant) with
 * float32 row-scales + float32 biases and a float32 embedding, all in flash at
 * 0x50000 (byte offsets from nn_weights.h).  Compute float32 on the FPU:
 *      acc = sum_i (float)w_int8[i]*x_float[i];   out = acc*row_scale + bias.
 *
 * Persistent state : h[H] float32 (<=1024 B) at 0x2003f100.
 * Transient scratch: GI[3H]+GH[3H] float32 at 0x2003b000 (<=16 KB).
 * Contract (STRIDE/DIRTY/RPT/RPTCNT, edge-detect, font, draw) matches gru.c.
 *
 * -------- on-device INPUT mapping (HID report -> symbol stream) --------
 * RPT[] = live u16 keycode array @0x2000b6f8, count @0x20003370.
 * Shift held  = keycode 0xe1 (LShift) or 0xe5 (RShift) present in the report.
 * Main key    = first non-modifier keycode >= 0x04 in the report.
 *   letters 0x04..0x1d -> a..z ; if Shift: emit '^'(caret) THEN the letter.
 *   space 0x2c / enter 0x28 -> space(26).
 *   apostrophe 0x34 -> ' (Shift -> ", not in vocab -> space).
 *   period 0x37 -> . (Shift -> >, -> space).
 *   comma  0x36 -> , (Shift -> <, -> space).
 *   dash   0x2d -> - (Shift -> _, -> space).
 *   1 key 0x1e + Shift -> '!' -> . ;  / key 0x38 + Shift -> '?' -> .
 *   anything else -> space (runs collapse via edge-detect on shift|keycode).
 */
#include <stdint.h>
#include "combo3_weights.h"       /* dims + OFF_* byte offsets into the weight blob */

#define STRIDE 0x80u
#define MAG    0xC0FFEE07u                        /* bumped: v2 vocab/layout    */
#define M      ((volatile uint32_t*)0x2003f000u)  /* 0=magic 1=last_token 2=disp*/
#define PREDS  ((volatile uint8_t*)0x2003f00cu)   /* 3 predicted symbols        */
#define HID    ((float*)0x2003f100u)              /* h[H] persistent (<=1024 B) */
#define GI     ((float*)0x2003b000u)              /* scratch gate acc (in) 3H   */
#define GH     ((float*)0x2003bc00u)              /* scratch gate acc (hid) 3H  */
#define DIRTY  (*(volatile uint8_t*)0x200034bau)
#define LEDT   ((volatile uint32_t*)0x2003f030u)
#define HUE    ((volatile uint32_t*)0x2003f034u)
#define RPTCNT (*(volatile uint32_t*)0x20003370u)
#define RPT    ((volatile uint16_t*)0x2000b6f8u)

/* symbol ids */
#define SYM_SP 26
#define SYM_AP 27
#define SYM_DT 28
#define SYM_CM 29
#define SYM_DS 30
#define SYM_CT 31

/* weight blob @ flash 0x50000 (offsets from nn_weights.h) */
#define WBASE 0x50000u
#define W_IH  ((const int8_t*)(WBASE + OFF_WIH0))
#define W_HH  ((const int8_t*)(WBASE + OFF_WHH0))
#define W_OUT ((const int8_t*)(WBASE + OFF_OUT))
#define EMB   ((const float*)  (WBASE + OFF_EMB))
#define S_IH  ((const float*)  (WBASE + OFF_WIH0_SCALE))
#define S_HH  ((const float*)  (WBASE + OFF_WHH0_SCALE))
#define S_OUT ((const float*)  (WBASE + OFF_OUT_SCALE))
#define B_IH  ((const float*)  (WBASE + OFF_BIH0))
#define B_HH  ((const float*)  (WBASE + OFF_BHH0))
#define B_OUT ((const float*)  (WBASE + OFF_BOUT))

#define H   HLAST
#define E   EDIM
#define V   VOCAB
#define G3  (GATES*H)

static const uint8_t FONT[32][8] = {
{0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0x00},{0x3F,0x66,0x66,0x3E,0x66,0x66,0x3F,0x00},
{0x3C,0x66,0x03,0x03,0x03,0x66,0x3C,0x00},{0x1F,0x36,0x66,0x66,0x66,0x36,0x1F,0x00},
{0x7F,0x46,0x16,0x1E,0x16,0x46,0x7F,0x00},{0x7F,0x46,0x16,0x1E,0x16,0x06,0x0F,0x00},
{0x3C,0x66,0x03,0x03,0x73,0x66,0x7C,0x00},{0x33,0x33,0x33,0x3F,0x33,0x33,0x33,0x00},
{0x1E,0x0C,0x0C,0x0C,0x0C,0x0C,0x1E,0x00},{0x78,0x30,0x30,0x30,0x33,0x33,0x1E,0x00},
{0x67,0x66,0x36,0x1E,0x36,0x66,0x67,0x00},{0x0F,0x06,0x06,0x06,0x46,0x66,0x7F,0x00},
{0x63,0x77,0x7F,0x7F,0x6B,0x63,0x63,0x00},{0x63,0x67,0x6F,0x7B,0x73,0x63,0x63,0x00},
{0x1C,0x36,0x63,0x63,0x63,0x36,0x1C,0x00},{0x3F,0x66,0x66,0x3E,0x06,0x06,0x0F,0x00},
{0x1E,0x33,0x33,0x33,0x3B,0x1E,0x38,0x00},{0x3F,0x66,0x66,0x3E,0x36,0x66,0x67,0x00},
{0x1E,0x33,0x07,0x0E,0x38,0x33,0x1E,0x00},{0x3F,0x2D,0x0C,0x0C,0x0C,0x0C,0x1E,0x00},
{0x33,0x33,0x33,0x33,0x33,0x33,0x3F,0x00},{0x33,0x33,0x33,0x33,0x33,0x1E,0x0C,0x00},
{0x63,0x63,0x63,0x6B,0x7F,0x77,0x63,0x00},{0x63,0x63,0x36,0x1C,0x1C,0x36,0x63,0x00},
{0x33,0x33,0x33,0x1E,0x0C,0x0C,0x1E,0x00},{0x7F,0x63,0x31,0x18,0x4C,0x66,0x7F,0x00},
{0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00},          /* 26 space (underscore)   */
{0x18,0x18,0x08,0x10,0x00,0x00,0x00,0x00},          /* 27 apostrophe '         */
{0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18},          /* 28 period .             */
{0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x08},          /* 29 comma ,              */
{0x00,0x00,0x00,0x7E,0x7E,0x00,0x00,0x00},          /* 30 dash -               */
{0x08,0x1C,0x36,0x63,0x41,0x00,0x00,0x00},          /* 31 caret ^ (cap escape) */
};

/* vocab symbol -> LED buffer position (half*60 + slot), 255 = key has no LED.
 * Derived statically from the stock firmware's own tables:
 *   keycode --0x47184--> trail-id --> (col,row): col=(id-32)/9, row=(id-32)%9
 *   (row,col) --invert 0x47510--> (half, slot).   Verified: Esc..F5 = slots 0..5.
 * space (physical row5,col5) and ^/capesc have NO backlight LED -> 255. */
static const uint8_t VOCABPOS[32] = {
   37, 84, 52, 39, 27, 40, 41, 78, 74, 79, 80, 42, 86, 85, 30, 31,
   25, 28, 38, 29, 73, 53, 26, 51, 72, 50, 255, 44, 81, 47, 20, 255 };

/* Pade(7,7) tanh, clamped; sigmoid built from it (identical to nn_ref.py). */
static float tanhf_(float x){
    if (x > 4.9f) return 1.0f;
    if (x < -4.9f) return -1.0f;
    float x2 = x*x;
    return x*(135135.0f + x2*(17325.0f + x2*(378.0f + x2)))
           / (135135.0f + x2*(62370.0f + x2*(3150.0f + x2*28.0f)));
}
static float sig_(float x){ return 0.5f*(1.0f + tanhf_(0.5f*x)); }

static void gru_step(int sym){
    const float *x = &EMB[sym*E];
    for (int j=0;j<G3;j++){
        const int8_t *w=&W_IH[j*E]; float a=0.0f;
        for (int k=0;k<E;k++) a += (float)w[k]*x[k];
        GI[j] = a*S_IH[j] + B_IH[j];
    }
    for (int j=0;j<G3;j++){
        const int8_t *w=&W_HH[j*H]; float a=0.0f;
        for (int k=0;k<H;k++) a += (float)w[k]*HID[k];
        GH[j] = a*S_HH[j] + B_HH[j];
    }
    for (int i=0;i<H;i++){                       /* torch gate order r,z,n */
        float r = sig_(GI[i]       + GH[i]);
        float z = sig_(GI[H+i]     + GH[H+i]);
        float n = tanhf_(GI[2*H+i] + r*GH[2*H+i]);
        HID[i] = (1.0f - z)*n + z*HID[i];
    }
}

static void predict(int lastsym){
    const float *xe = &EMB[lastsym*E];
    float b0=-1e30f,b1=-1e30f,b2=-1e30f; int i0=SYM_SP,i1=SYM_SP,i2=SYM_SP;
    for (int o=0;o<V;o++){
        const int8_t *w=&W_OUT[o*OUTIN]; float a=0.0f;
        for (int k=0;k<H;k++) a += (float)w[k]*HID[k];
#if OUT_SKIP
        for (int k=0;k<E;k++) a += (float)w[H+k]*xe[k];
#endif
        a = a*S_OUT[o] + B_OUT[o];
        if (a>b0){b2=b1;i2=i1;b1=b0;i1=i0;b0=a;i0=o;}
        else if (a>b1){b2=b1;i2=i1;b1=a;i1=o;}
        else if (a>b2){b2=a;i2=o;}
    }
    PREDS[0]=i0; PREDS[1]=i1; PREDS[2]=i2;
}

/* map main keycode + shift -> up to 2 symbols; returns count, fills s[] */
static int map_key(int kc, int shift, int *s){
    if (kc>=0x04 && kc<=0x1d){ int base=kc-0x04;
        if (shift){ s[0]=SYM_CT; s[1]=base; return 2; } s[0]=base; return 1; }
    switch (kc){
        case 0x2c: case 0x28: s[0]=SYM_SP; return 1;          /* space / enter */
        case 0x34: s[0]= shift?SYM_SP:SYM_AP; return 1;       /* '  "          */
        case 0x37: s[0]= shift?SYM_SP:SYM_DT; return 1;       /* .  >          */
        case 0x36: s[0]= shift?SYM_SP:SYM_CM; return 1;       /* ,  <          */
        case 0x2d: s[0]= shift?SYM_SP:SYM_DS; return 1;       /* -  _          */
        case 0x1e: s[0]= shift?SYM_DT:SYM_SP; return 1;       /* 1  !          */
        case 0x38: s[0]= shift?SYM_DT:SYM_SP; return 1;       /* /  ?          */
        default:   s[0]=SYM_SP; return 1;
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
    /* seed if magic missing OR hidden state is not healthy (RAM survives reflash,
       so a stale magic must not skip seeding). */
    float h0=HID[0]; int healthy=(h0==h0) && h0>-100.0f && h0<100.0f;
    if (M[0] != MAG || !healthy){
        M[0]=MAG; M[1]=0xFFFFFFFFu; M[2]=SYM_SP;
        for(int i=0;i<H;i++) HID[i]=0.0f;
        gru_step(SYM_SP); predict(SYM_SP);       /* seed with a space */
    }
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
            int s[2]; int c=map_key(kc,shift,s);
            for(int j=0;j<c;j++) gru_step(s[j]);
            M[2]=(uint32_t)s[c-1];               /* display last emitted symbol */
            predict(s[c-1]);
        }
    } else M[1]=0xFFFFFFFFu;

    uint32_t *pp=(uint32_t*)fb; for(int i=0;i<0x2000/4;i++) pp[i]=0;
    draw_char(fb, 4, 20, M[2], 0xC, 2);                 /* last typed char (context) */
    setpx(fb,26,26,0x6); setpx(fb,27,26,0x6); setpx(fb,28,26,0x6);
    draw_char(fb, 60,  16, PREDS[0], 0xF, 5);           /* #1 prediction, biggest */
    draw_char(fb, 150, 20, PREDS[1], 0xA, 4);
    draw_char(fb, 210, 24, PREDS[2], 0x6, 3);

}

/* Backlight: every key BLUE, the 3 predicted next-keys RED.
 * led_fill is called once per half (60 slots each); VOCABPOS encodes half*60+slot.
 * buf is R,G,B per LED (gamma + physical scatter happen downstream). */
__attribute__((section(".text.ledfill"),used))
void led_fill(int subop,int half,uint8_t*buf){
    if(subop!=0)return;
    for(uint32_t i=0;i<60u;i++){ buf[i*3+0]=0; buf[i*3+1]=0; buf[i*3+2]=110; }
    for(int p=0;p<3;p++){
        uint8_t sym=PREDS[p]; if(sym>=32u) continue;
        uint8_t vp=VOCABPOS[sym];
        if(vp!=255u && (int)(vp/60u)==half){
            uint32_t i=vp%60u; buf[i*3+0]=255; buf[i*3+1]=0; buf[i*3+2]=0;
        }
    }
}
