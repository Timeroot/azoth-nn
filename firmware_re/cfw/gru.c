/* On-device char-GRU next-key predictor. Float32 weights (in .weights flash section
 * at 0x50000), hardware FPU. Keeps a persistent hidden state in RAM across keystrokes,
 * so it uses the WHOLE typed prefix (not just 2 chars like the trigram). */
#include <stdint.h>
#include "weights.h"                 /* V,E,H + EMB,W_ih,W_hh,B_ih,B_hh,W_out,B_out */

#define STRIDE 0x80u
#define MAG    0xBA11B030u
#define M      ((volatile uint32_t*)0x2003f000u)  /* 0=magic 1=last_seen 2=last_char */
#define PREDS  ((volatile uint8_t*)0x2003f00cu)   /* 3 predicted symbols */
#define HID    ((float*)0x2003f100u)              /* h[H] persistent hidden state */
#define GI     ((float*)0x2003f200u)              /* gate pre-acts (input side) */
#define GH     ((float*)0x2003f380u)              /* gate pre-acts (hidden side) */
#define DIRTY  (*(volatile uint8_t*)0x200034bau)
#define RPTCNT (*(volatile uint32_t*)0x20003370u)
#define RPT    ((volatile uint16_t*)0x2000b6f8u)

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

/* Pade(7,7) tanh, clamped; sigmoid built from it */
static float tanhf_(float x){
    if (x > 4.9f) return 1.0f; if (x < -4.9f) return -1.0f;
    float x2 = x*x;
    return x*(135135.0f + x2*(17325.0f + x2*(378.0f + x2)))
           / (135135.0f + x2*(62370.0f + x2*(3150.0f + x2*28.0f)));
}
static float sig_(float x){ return 0.5f*(1.0f + tanhf_(0.5f*x)); }

static void gru_step(int sym){
    const float *x = &EMB[sym*E];
    for (int j=0;j<3*H;j++){ float a=B_ih[j]; const float *w=&W_ih[j*E]; for(int k=0;k<E;k++) a+=w[k]*x[k]; GI[j]=a; }
    for (int j=0;j<3*H;j++){ float a=B_hh[j]; const float *w=&W_hh[j*H]; for(int k=0;k<H;k++) a+=w[k]*HID[k]; GH[j]=a; }
    for (int i=0;i<H;i++){
        float r = sig_(GI[i]     + GH[i]);
        float z = sig_(GI[H+i]   + GH[H+i]);
        float n = tanhf_(GI[2*H+i] + r*GH[2*H+i]);
        HID[i] = (1.0f - z)*n + z*HID[i];
    }
}
static void predict(void){
    float b0=-1e30f,b1=-1e30f,b2=-1e30f; int i0=26,i1=26,i2=26;
    for (int o=0;o<V;o++){
        float a=B_out[o]; const float *w=&W_out[o*H]; for(int k=0;k<H;k++) a+=w[k]*HID[k];
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
        gru_step(26); predict();               /* seed with a space -> word-initial preds */
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
}
