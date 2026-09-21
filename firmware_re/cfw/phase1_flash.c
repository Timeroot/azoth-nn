/* Phase-1: isolated high-flash self-program TEST (no model).
 *
 * Adds a custom HID command (magic 'W','F') by detouring the app's HID command
 * dispatch FUN_0003a0f0, and writes/erases the free flash region at 0x61000+
 * using the firmware's OWN NVMC routines (flash_erase_page @0x3df55,
 * flash_write_words @0x3df89). The OLED (flush detour) shows counters + the
 * first bytes now living at 0x61000 so an upload can be visually verified.
 *
 * SAFETY: the handler only ever erases/writes inside [0x61000, 0xdb000) (the
 * free/asset region) with hard bounds checks; it can't touch app code or the
 * checksummed region. Recovery if anything goes wrong: Fn+L+B / stock reflash.
 */
#include <stdint.h>

#define STRIDE 0x80u
#define DIRTY  (*(volatile uint8_t*)0x200034bau)
#define HIBASE 0x61000u
#define HISPAN 0x7a000u                 /* 0x61000..0xdb000 = 490KB, 122 pages   */

/* persistent test state (RAM) */
#define WCNT    ((volatile uint32_t*)0x2003f200u)   /* write blocks applied      */
#define ECNT    ((volatile uint32_t*)0x2003f204u)   /* pages erased              */
#define LASTOFF ((volatile uint32_t*)0x2003f208u)   /* last write byte offset    */
#define SUMV    ((volatile uint32_t*)0x2003f20cu)   /* running sum32 of writes   */

/* inline nRF52 NVMC flash controller (self-contained; no guessed entry points) */
#define NVMC_READY     (*(volatile uint32_t*)0x4001E400u)
#define NVMC_CONFIG    (*(volatile uint32_t*)0x4001E504u)
#define NVMC_ERASEPAGE (*(volatile uint32_t*)0x4001E508u)
static void flash_erase(uint32_t page){
    NVMC_CONFIG=2u; __asm volatile("dsb sy":::"memory");
    NVMC_ERASEPAGE=page; __asm volatile("dsb sy":::"memory");
    while((NVMC_READY&1u)==0u){}
    NVMC_CONFIG=0u; __asm volatile("dsb sy":::"memory");
}
static void flash_write(volatile uint32_t *dst, const uint32_t *src, uint32_t n){
    NVMC_CONFIG=1u; __asm volatile("dsb sy":::"memory");
    for(uint32_t i=0;i<n;i++){ dst[i]=src[i]; __asm volatile("dsb sy":::"memory");
        while((NVMC_READY&1u)==0u){} }
    NVMC_CONFIG=0u; __asm volatile("dsb sy":::"memory");
}

/* ---- HID command handler: return 1 if it was OUR command (swallow), else 0 ---
 * Report layout (64 bytes at the dispatch's data pointer):
 *   [0]='W' [1]='F' [2]=sub
 *   sub 0x01 ERASE page:  [3]=page_index (0..121) -> erase 0x61000+idx*0x1000
 *   sub 0x02 WRITE block: [3..6]=byte offset (LE, word-aligned), [7]=len (<=52,
 *                         mult of 4), [8..]=payload -> write at 0x61000+offset
 *   sub 0x03 RESET counters
 */
__attribute__((section(".text.hidcmd"), used))
int hid_cmd(int p1, int p2){
    if (p2 != 2) return 0;                          /* only the data-stage report */
    uint32_t *pp = *(uint32_t**)(p1 + 0x20);
    if (!pp) return 0;
    uint8_t *d = (uint8_t*)(*pp);
    if (!d) return 0;
    if (d[0] != 'W' || d[1] != 'F') return 0;       /* not ours -> original path  */
    uint8_t sub = d[2];
    if (sub == 0x01){
        uint32_t pi = d[3];
        if (pi < (HISPAN >> 12)) { flash_erase(HIBASE + pi*0x1000u); ECNT[0]++; }
        return 1;
    }
    if (sub == 0x02){
        uint32_t off = (uint32_t)d[3] | ((uint32_t)d[4]<<8) | ((uint32_t)d[5]<<16) | ((uint32_t)d[6]<<24);
        uint32_t len = d[7]; if (len > 52u) len = 52u; len &= ~3u;
        if ((off & 3u)==0 && off + len <= HISPAN){
            uint32_t buf[13];
            for (uint32_t i=0;i<len/4;i++)
                buf[i] = (uint32_t)d[8+i*4] | ((uint32_t)d[9+i*4]<<8)
                       | ((uint32_t)d[10+i*4]<<16) | ((uint32_t)d[11+i*4]<<24);
            flash_write((uint32_t*)(HIBASE+off), buf, len/4);
            for (uint32_t i=0;i<len/4;i++) SUMV[0]+=buf[i];
            WCNT[0]++; LASTOFF[0]=off;
        }
        return 1;
    }
    if (sub == 0x03){ WCNT[0]=0; ECNT[0]=0; LASTOFF[0]=0; SUMV[0]=0; return 1; }
    return 1;                                        /* WF but unknown -> swallow  */
}

/* ---------- tiny OLED (hex readout) ---------- */
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
    uint32_t *pp=(uint32_t*)fb; for(int i=0;i<0x2000/4;i++) pp[i]=0;
    /* row0: E=erase count  W=write count */
    hx(fb, 2,  2, ECNT[0], 4, 0xE, 2);
    hx(fb, 70, 2, WCNT[0], 4, 0xF, 2);
    hx(fb, 150,2, LASTOFF[0], 6, 0xA, 2);
    /* row1: running sum32 of written words (host compares) */
    hx(fb, 2, 24, SUMV[0], 8, 0x6, 2);
    /* row2: first 8 bytes currently at 0x61000 (hex) */
    volatile uint8_t *hf=(volatile uint8_t*)HIBASE;
    for(int i=0;i<8;i++) hx(fb, 2+i*32u, 46, hf[i], 2, 0x9, 2);
}
