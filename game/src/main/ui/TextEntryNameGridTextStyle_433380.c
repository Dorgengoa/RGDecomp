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
    s8 buf[0x100] __attribute__((aligned(16)));
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
