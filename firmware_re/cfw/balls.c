/* C reimplementation of the bouncing-balls renderer, to validate the
 * compile -> link-at-fixed-addr -> objcopy -> inject pipeline.
 * render() is called by a tiny asm shim that detours the OLED flush FUN_00031658;
 * r0=fb (buffer being DMA'd), r1=len. We draw into fb, sustain continuous flush,
 * and keep a private frame counter in free RAM above the stack. */
#include <stdint.h>

#define STRIDE   0x80u
#define CNT      ((volatile uint32_t*)0x2003f000u)   /* free RAM (above SP) */
#define CNTMAGIC 0xBA11B011u
#define DIRTY    (*(volatile uint8_t*)0x200034bau)    /* content-changed flag */

/* triangle wave: p folded into [0, M]. cortex-m4 udiv used for %, no libc. */
static uint32_t tri(uint32_t p, uint32_t M) {
    uint32_t two = 2u * M;
    p %= two;
    if (p >= M) p = two - p;
    return p;
}

static void draw_ball(uint8_t *fb, uint32_t px, uint32_t py, uint8_t col) {
    px &= ~1u;
    uint32_t xb = px >> 1;               /* byte offset */
    for (uint32_t r = 0; r < 10; r++) {
        uint8_t *row = fb + (py + r) * STRIDE + xb;
        for (uint32_t c = 0; c < 5; c++) row[c] = col;   /* 5 bytes = 10 px */
    }
}

__attribute__((section(".text.render"), used))
void render(uint8_t *fb, int len) {
    (void)len;
    if (CNT[1] != CNTMAGIC) { CNT[0] = 0; CNT[1] = CNTMAGIC; }
    uint32_t t = (CNT[0] + 1u) & 0xFFFFu;
    CNT[0] = t;
    DIRTY = 1;                            /* sustain continuous refresh */

    uint32_t *p = (uint32_t *)fb;         /* clear 8192 bytes */
    for (int i = 0; i < 0x2000 / 4; i++) p[i] = 0;

    draw_ball(fb, tri(t * 2u, 246), tri(t, 54), 0xFF);
    draw_ball(fb, tri(t + 60u, 246), tri(t * 3u + 20u, 54), 0xAA);
    draw_ball(fb, tri(t * 3u + 120u, 246), tri(t * 2u + 40u, 54), 0x66);
}
