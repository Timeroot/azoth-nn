/* On-device char next-key predictor for the ROG Azoth (nRF52840, M4F @ 64MHz).
 *
 * Single-layer GRU, H=256, E=64, vocab=27 (a-z + space).  Weights are int8
 * (per-output-row symmetric quant) with float32 row-scales + float32 biases,
 * and a float32 embedding table -- all living in the erased flash region at
 * 0x50000 (see nn_weights.bin / nn_weights.h for the exact byte layout).
 * Compute is float32 on the hardware FPU:  for each linear
 *      acc = sum_i (float)w_int8[i] * x_float[i];   out = acc*row_scale + bias.
 *
 * Persistent state  : h[256] float32 = 1024 B  at 0x2003f100.
 * Transient scratch : GI[768]+GH[768] float32 = 6144 B at 0x2003b000.
 * MAC/step ~= 252k.  tanh/sigmoid use the same Pade approx as nn_ref.py.
 *
 * Contract (STRIDE/DIRTY/RPT/RPTCNT, edge-detect, font, draw) matches gru.c.
 */
#include <stdint.h>
#include "combo_weights.h"       /* dims + OFF_* byte offsets into the weight blob */

#define STRIDE 0x80u
#define MAG    0xBA11B031u                        /* bumped: new model layout   */
#define M      ((volatile uint32_t*)0x2003f000u)  /* 0=magic 1=last_seen 2=last */
#define PREDS  ((volatile uint8_t*)0x2003f00cu)   /* 3 predicted symbols        */
#define HID    ((float*)0x2003f100u)              /* h[H] persistent (1024 B)   */
#define GI     ((float*)0x2003b000u)              /* scratch gate acc (in) 3H=3072B */
#define GH     ((float*)0x2003bc00u)              /* scratch gate acc (hid) 3H=3072B */
#define DIRTY  (*(volatile uint8_t*)0x200034bau)
#define LEDT   ((volatile uint32_t*)0x2003f030u)   /* LED animation clock */
#define HUE    ((volatile uint32_t*)0x2003f034u)   /* hue base from top prediction */
#define RPTCNT (*(volatile uint32_t*)0x20003370u)
#define RPT    ((volatile uint16_t*)0x2000b6f8u)

/* ---- weight blob at flash 0x50000 (offsets from nn_weights.h) ---- */
#define WBASE 0x50000u
#define W_IH  ((const int8_t*)(WBASE + OFF_WIH0))       /* [3H,E] int8  */
#define W_HH  ((const int8_t*)(WBASE + OFF_WHH0))       /* [3H,H] int8  */
#define W_OUT ((const int8_t*)(WBASE + OFF_OUT))        /* [V,H]  int8  */
#define EMB   ((const float*)  (WBASE + OFF_EMB))        /* [V,E]  f32   */
#define S_IH  ((const float*)  (WBASE + OFF_WIH0_SCALE)) /* [3H]   f32   */
#define S_HH  ((const float*)  (WBASE + OFF_WHH0_SCALE)) /* [3H]   f32   */
#define S_OUT ((const float*)  (WBASE + OFF_OUT_SCALE))  /* [V]    f32   */
#define B_IH  ((const float*)  (WBASE + OFF_BIH0))       /* [3H]   f32   */
#define B_HH  ((const float*)  (WBASE + OFF_BHH0))       /* [3H]   f32   */
#define B_OUT ((const float*)  (WBASE + OFF_BOUT))       /* [V]    f32   */

#define H   HLAST      /* 256 */
#define E   EDIM       /* 64  */
#define V   VOCAB      /* 27  */
#define G3  (GATES*H)  /* 768 */

static const uint8_t FONT[27][8] = {
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
{0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x00},
};

/* Pade(7,7) tanh, clamped; sigmoid built from it (identical to nn_ref.py). */
static float tanhf_(float x){
    if (x > 4.9f) return 1.0f; if (x < -4.9f) return -1.0f;
    float x2 = x*x;
    return x*(135135.0f + x2*(17325.0f + x2*(378.0f + x2)))
           / (135135.0f + x2*(62370.0f + x2*(3150.0f + x2*28.0f)));
}
static float sig_(float x){ return 0.5f*(1.0f + tanhf_(0.5f*x)); }

static void gru_step(int sym){
    const float *x = &EMB[sym*E];
    /* input-side gate pre-activations: GI = (Wih . x)*Sih + Bih   [3H]      */
    for (int j=0;j<G3;j++){
        const int8_t *w=&W_IH[j*E]; float a=0.0f;
        for (int k=0;k<E;k++) a += (float)w[k]*x[k];
        GI[j] = a*S_IH[j] + B_IH[j];
    }
    /* hidden-side gate pre-activations: GH = (Whh . h)*Shh + Bhh  [3H]      */
    for (int j=0;j<G3;j++){
        const int8_t *w=&W_HH[j*H]; float a=0.0f;
        for (int k=0;k<H;k++) a += (float)w[k]*HID[k];
        GH[j] = a*S_HH[j] + B_HH[j];
    }
    /* torch GRU gate order in rows: r, z, n */
    for (int i=0;i<H;i++){
        float r = sig_(GI[i]       + GH[i]);
        float z = sig_(GI[H+i]     + GH[H+i]);
        float n = tanhf_(GI[2*H+i] + r*GH[2*H+i]);
        HID[i] = (1.0f - z)*n + z*HID[i];
    }
}

static void predict(void){
    float b0=-1e30f,b1=-1e30f,b2=-1e30f; int i0=26,i1=26,i2=26;
    for (int o=0;o<V;o++){
        const int8_t *w=&W_OUT[o*H]; float a=0.0f;
        for (int k=0;k<H;k++) a += (float)w[k]*HID[k];
        a = a*S_OUT[o] + B_OUT[o];
        if (a>b0){b2=b1;i2=i1;b1=b0;i1=i0;b0=a;i0=o;}
        else if (a>b1){b2=b1;i2=i1;b1=a;i1=o;}
        else if (a>b2){b2=a;i2=o;}
    }
    PREDS[0]=i0; PREDS[1]=i1; PREDS[2]=i2;
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
    if (M[0] != MAG){
        M[0]=MAG; M[1]=0xFF; M[2]=26;
        for(int i=0;i<H;i++) HID[i]=0.0f;
        gru_step(26); predict();               /* seed with a space -> word-initial */
    }
    DIRTY=1;

    int sym=-1; uint32_t n=RPTCNT; if(n>0x78u)n=0x78u;
    for(uint32_t i=0;i<n;i++){ uint16_t kc=RPT[i];
        if(kc>=0x04&&kc<=0x1d){sym=(int)(kc-0x04);break;}
        if(kc==0x2c||kc==0x28){sym=26;break;} }
    if (sym>=0){
        if((uint32_t)sym!=M[1]){ M[1]=(uint32_t)sym; M[2]=(uint32_t)sym; gru_step(sym); predict(); }
    } else M[1]=0xFF;

    uint32_t *pp=(uint32_t*)fb; for(int i=0;i<0x2000/4;i++) pp[i]=0;
    draw_char(fb, 4, 20, M[2], 0xC, 2);                 /* last typed char (context) */
    setpx(fb,26,26,0x6); setpx(fb,27,26,0x6); setpx(fb,28,26,0x6);
    draw_char(fb, 60,  16, PREDS[0], 0xF, 5);           /* #1 prediction, biggest */
    draw_char(fb, 150, 20, PREDS[1], 0xA, 4);
    draw_char(fb, 210, 24, PREDS[2], 0x6, 3);

    LEDT[0] = LEDT[0] + 1;         /* advance LED animation clock */
    HUE[0]  = PREDS[0];            /* backlight hue base tracks the top prediction */
}

/* ---- backlight: flowing rainbow tinted by the top prediction ---- */
static void hsv6(uint32_t h, uint8_t *R, uint8_t *G, uint8_t *B){
    uint32_t h6=h*6u, seg=h6>>8, f=h6&255u, up=f, dn=255u-f;
    switch(seg){
      case 0: *R=255;*G=up;*B=0;break;   case 1: *R=dn;*G=255;*B=0;break;
      case 2: *R=0;*G=255;*B=up;break;    case 3: *R=0;*G=dn;*B=255;break;
      case 4: *R=up;*G=0;*B=255;break;    default:*R=255;*G=0;*B=dn;break;
    }
}
__attribute__((section(".text.ledfill"), used))
void led_fill(int subop, int half, uint8_t *buf){
    if (subop != 0) return;                 /* only the colour-load subop */
    uint32_t t=LEDT[0], base=HUE[0];
    for (uint32_t i=0;i<60u;i++){
        uint32_t idx=(uint32_t)half*60u + i;
        uint32_t hue=(idx*6u + t*2u + base*11u) & 0xffu;
        uint8_t r,g,b; hsv6(hue,&r,&g,&b);
        buf[i*3+0]=r; buf[i*3+1]=g; buf[i*3+2]=b;
    }
}
