/* Phase-1a: isolated high-flash SELF-PROGRAM primitive test.
 * NO HID hook (that path bricked USB). Uses ONLY the proven OLED flush detour.
 * On boot, after a frame delay (so USB is fully up before the ~85ms erase stall),
 * erase page 0 at 0x61000 and write a known pattern using our OWN inline NVMC code
 * (no guessed firmware entry points). The OLED then shows the words living at
 * 0x61000, so a successful write shows DEAD0000 / DEAD0001 / ... appear live.
 * Touches only 0x61000 (free flash). Recovery if needed: Fn+L+B / stock reflash. */
#include <stdint.h>

#define STRIDE 0x80u
#define DIRTY  (*(volatile uint8_t*)0x200034bau)
#define HIBASE 0x61000u

/* one-time-guard state (RAM survives reflash -> MAG-guarded init) */
#define MAG  ((volatile uint32_t*)0x2003f200u)
#define CNT  ((volatile uint32_t*)0x2003f204u)
#define DONE ((volatile uint32_t*)0x2003f208u)
#define MAGVAL 0x1A0F5EEDu

/* ---- inline nRF52 NVMC flash controller (self-contained) ---- */
#define NVMC_READY     (*(volatile uint32_t*)0x4001E400u)
#define NVMC_CONFIG    (*(volatile uint32_t*)0x4001E504u)
#define NVMC_ERASEPAGE (*(volatile uint32_t*)0x4001E508u)
static void nvmc_erase(uint32_t page){
    NVMC_CONFIG = 2u; __asm volatile("dsb sy":::"memory");         /* EEN */
    NVMC_ERASEPAGE = page; __asm volatile("dsb sy":::"memory");
    while ((NVMC_READY & 1u) == 0u) {}
    NVMC_CONFIG = 0u; __asm volatile("dsb sy":::"memory");
}
static void nvmc_write(volatile uint32_t *dst, const uint32_t *src, uint32_t n){
    NVMC_CONFIG = 1u; __asm volatile("dsb sy":::"memory");         /* WEN */
    for (uint32_t i=0;i<n;i++){ dst[i]=src[i]; __asm volatile("dsb sy":::"memory");
        while ((NVMC_READY & 1u) == 0u) {} }
    NVMC_CONFIG = 0u; __asm volatile("dsb sy":::"memory");
}

/* ---- tiny OLED hex readout ---- */
static const uint8_t DIGIT[16][8]={
{0x3E,0x63,0x73,0x7B,0x6F,0x67,0x3E,0},{0x0C,0x0E,0x0C,0x0C,0x0C,0x0C,0x3F,0},
{0x1E,0x33,0x30,0x1C,0x06,0x33,0x3F,0},{0x1E,0x33,0x30,0x1C,0x30,0x33,0x1E,0},
{0x38,0x3C,0x36,0x33,0x7F,0x30,0x78,0},{0x3F,0x03,0x1F,0x30,0x30,0x33,0x1E,0},
{0x1C,0x06,0x03,0x1F,0x33,0x33,0x1E,0},{0x3F,0x33,0x30,0x18,0x0C,0x0C,0x0C,0},
{0x1E,0x33,0x33,0x1E,0x33,0x33,0x1E,0},{0x1E,0x33,0x33,0x3E,0x30,0x18,0x0E,0},
{0x0C,0x1E,0x33,0x33,0x3F,0x33,0x33,0},{0x3F,0x66,0x66,0x3E,0x66,0x66,0x3F,0},
{0x3C,0x66,0x03,0x03,0x03,0x66,0x3C,0},{0x1F,0x36,0x66,0x66,0x66,0x36,0x1F,0},
{0x7F,0x46,0x16,0x1E,0x16,0x46,0x7F,0},{0x7F,0x46,0x16,0x1E,0x16,0x06,0x0F,0}};
static void setpx(uint8_t*fb,uint32_t x,uint32_t y,uint8_t n){
    uint8_t*p=fb+y*STRIDE+(x>>1); if(x&1)*p=(*p&0x0F)|(n<<4); else *p=(*p&0xF0)|n; }
static void gl(uint8_t*fb,uint32_t px,uint32_t py,const uint8_t*b,uint8_t n,uint32_t s){
    for(uint32_t r=0;r<8;r++){uint8_t bt=b[r];for(uint32_t c=0;c<8;c++)if((bt>>c)&1){
        uint32_t x0=px+c*s,y0=py+r*s;for(uint32_t a=0;a<s;a++)for(uint32_t e=0;e<s;e++)setpx(fb,x0+a,y0+e,n);}}}
static void hx(uint8_t*fb,uint32_t px,uint32_t py,uint32_t v,int nd,uint8_t n,uint32_t s){
    for(int k=0;k<nd;k++){uint32_t q=(v>>((nd-1-k)*4))&0xF;gl(fb,px+(uint32_t)k*6u*s,py,DIGIT[q],n,s);}}

__attribute__((section(".text.render"), used))
void render(uint8_t *fb, int len){
    (void)len; DIRTY=1;
    if (MAG[0]!=MAGVAL){ MAG[0]=MAGVAL; CNT[0]=0; DONE[0]=0; }
    CNT[0]++;
    if (DONE[0]==0 && CNT[0]>=60u){          /* once, ~60 frames after boot */
        DONE[0]=1;
        nvmc_erase(HIBASE);
        uint32_t buf[16]; for(int i=0;i<16;i++) buf[i]=0xDEAD0000u+(uint32_t)i;
        nvmc_write((volatile uint32_t*)HIBASE, buf, 16);
    }
    uint32_t *pp=(uint32_t*)fb; for(int i=0;i<0x2000/4;i++) pp[i]=0;
    hx(fb, 2,  2, CNT[0],  6, 0xE, 2);        /* frame counter (liveness)    */
    hx(fb, 120,2, DONE[0], 1, 0xF, 2);        /* 1 once write attempted      */
    volatile uint32_t *hf=(volatile uint32_t*)HIBASE;   /* words now at 0x61000 */
    hx(fb, 2, 26, hf[0], 8, 0x9, 3);          /* expect DEAD0000 after write */
    hx(fb, 2, 48, hf[1], 8, 0x6, 2);          /* expect DEAD0001             */
}
