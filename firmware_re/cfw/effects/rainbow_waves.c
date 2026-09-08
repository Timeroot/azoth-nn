/* ============================================================================
 * "Rainbow Waves" — custom Azoth backlight effect  (SAVED FOR REUSE)
 * ============================================================================
 * A slow flowing hue animation. Because the LED buffer index -> physical key is
 * SCATTERED by the IS31FL37xx CS/SW wiring, a smooth hue-vs-index gradient that
 * drifts over time reads on the physical board as soft RIPPLING WAVES of colour
 * rolling across the keys. The base hue is (optionally) tinted by an external
 * value (in the predictor firmware: the model's top predicted key), so the whole
 * board's colour subtly shifts as you type.
 *
 * This is the effect running in the v2 combined firmware (combo2_nn.c). Extracted
 * here standalone so it can be dropped into any custom firmware.
 *
 * --- HOW IT HOOKS (see RGB_NOTES.md) ---------------------------------------
 * Detour FUN_00031b28 (the LED framebuffer -> I2C-driver send). Its entry is
 *   0x31b28: push.w {r2,r3,r4,r5,r6,r7,r8,r9,r10,lr}   (4 bytes: 2d e9 fc 47)
 * Replace those 4 bytes with `b.w led_shim`. led_shim (asm) must:
 *   push {r0,r1,r2,r3,r12,lr}      ; r0=subop r1=half r2=rgbbuf
 *   bl   led_fill                  ; C fn below; preserves r4-r11
 *   pop  {r0,r1,r2,r3,r12,lr}
 *   push.w {r2,r3,r4,r5,r6,r7,r8,r9,r10,lr}   ; replicate original prologue
 *   b.w  0x31b2c                   ; resume the real send
 * led_fill overwrites the 60x3 RGB buffer on the colour-load subop (param_1==0);
 * the firmware then gamma-corrects, physically scatters, and I2C-writes it.
 * ~120 LEDs total = 2 halves x 60; led_fill is called once per half.
 *
 * --- STATE IT NEEDS ---------------------------------------------------------
 *   LEDT (u32) : animation clock. MUST be incremented by *something* that runs
 *                continuously — in the predictor fw the OLED flush-detour render()
 *                does `LEDT[0]++` each frame. A standalone LED-only build can
 *                increment it inside led_fill (e.g. only when half==0).
 *   HUE  (u32) : hue base tint (0 for a pure rainbow; set to a live value to tint).
 *
 * --- THE LOOK KNOBS ---------------------------------------------------------
 *   idx*6   : spatial frequency of the wave across LED index (bigger = tighter).
 *   t*2     : scroll speed (bigger = faster drift).
 *   base*11 : how strongly HUE shifts the whole board.
 * ==========================================================================*/
#include <stdint.h>

#define LEDT ((volatile uint32_t*)0x2003f030u)
#define HUE  ((volatile uint32_t*)0x2003f034u)

static void hsv6(uint32_t h, uint8_t *R, uint8_t *G, uint8_t *B){
    uint32_t h6=h*6u, seg=h6>>8, f=h6&255u, up=f, dn=255u-f;
    switch(seg){
      case 0: *R=255;*G=up;*B=0;break;   case 1: *R=dn;*G=255;*B=0;break;
      case 2: *R=0;*G=255;*B=up;break;    case 3: *R=0;*G=dn;*B=255;break;
      case 4: *R=up;*G=0;*B=255;break;    default:*R=255;*G=0;*B=dn;break;
    }
}

/* subop!=0 -> not the colour-load pass; half in {0,1}; buf = 60 x 3 RGB bytes */
__attribute__((section(".text.ledfill"), used))
void led_fill(int subop, int half, uint8_t *buf){
    if (subop != 0) return;
    /* Standalone use (no external clock): uncomment to self-animate.
     * if (half==0) LEDT[0] = LEDT[0] + 1; */
    uint32_t t = LEDT[0], base = HUE[0];
    for (uint32_t i=0;i<60u;i++){
        uint32_t idx = (uint32_t)half*60u + i;
        uint32_t hue = (idx*6u + t*2u + base*11u) & 0xffu;
        uint8_t r,g,b; hsv6(hue,&r,&g,&b);
        buf[i*3+0]=r; buf[i*3+1]=g; buf[i*3+2]=b;
    }
}
