/* rg-override: replaces game/src/main/ui/TextEntryNameGridTextStyle_433380.c sha256 06540496000afe3887c0d1d717691e16b9410c921c69a0e0307d86d3c8a6f8a5
 * why: retail UB (lane insnet 2026-11-12, docs/INSECTRON-VERSUS.md): with arg5 = 1 the callback points the
 * text-entry field's text element at its own stack buffer `buf` and RETURNS; UiDrawWidgets_291910 draws
 * the text after the call, from a dead frame.  On the PS2 the bytes survived under the draw's own
 * buffer; on the port they are gone, so names / victory codes / passwords drew as dashes only.
 * Fix: `buf` is static (one text entry exists at a time), so the draw reads exactly what retail meant. */
/* rgp:protos */
#define RGP_SELF_TextEntryNameGridTextStyle_433380 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_004DB150[];

s32 TextEntryNameGridTextStyle_433380(s32 *arg0, s32 a1, s32 a2, s32 a3, s32 t0, s32 arg5)
{
    static s8 buf[0x100] __attribute__((aligned(16)));   /* rg-port: was a stack local (see header) */
    u8 *q;
    u32 n;
    s8 *d;
    s8 *s;
    s32 i;
    void *r;
    s8 c;

    if (arg5 != 0) {
        if (*arg0 == 0) {
            return 1;
        }
        q = (u8 *)buf;
        n = 0x100;
        if (q != NULL) {
            do {
                *q = 0;
                n--;
                q++;
            } while (n != 0);
        }
        d = buf;
        r = UiGetWidgetText_28f620(*arg0, 0xB, 0);
        s = (s8 *)arg0 + 0x30;
        for (i = 0; i < 0xAE; i++) {
            c = *s;
            if (c == 0x2A) {
                *d = 0x20;
            } else {
                *d = c;
            }
            d++;
            s++;
        }
        *(void **)((u8 *)r + 4) = buf;
        if (D_004DB150 != NULL) {
            TextStyleSetFixedCell_26f0e0(D_004DB150, 0xE, 0x1C);
        }
    } else {
        if (*arg0 == 0) {
            return 1;
        }
        r = UiGetWidgetText_28f620(*arg0, 0xB, 0);
        *(void **)((u8 *)r + 4) = (u8 *)arg0 + 0x30;
        if (D_004DB150 != NULL) {
            TextStyleSetFixedPitch_26f140(D_004DB150, 0);
        }
    }
    return 1;
}
