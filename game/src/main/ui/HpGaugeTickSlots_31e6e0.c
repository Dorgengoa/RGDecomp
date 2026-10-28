/* rgp:protos */
#define RGP_SELF_HpGaugeTickSlots_31e6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/

s32 HpGaugeTickSlots_31e6e0(s32 arg0) {
    s32 i;
    u8 *p6;
    u8 *p2;
    u8 *p3;
    u8 *q;
    s64 *r;
    s16 *h;
    s16 t;

    i = 0;
    do {
        p6 = (u8 *)(arg0 + (i * 2));
        if (*(s16 *)p6 != -1) {
            p2 = (u8 *)(arg0 + i);
            q = p2 + 0x1C0;
            if (*(u8 *)(p2 + 0x1C0) != 0) {
                u8 *p8 = (u8 *)(arg0 + (i * 8));
                r = (s64 *)(p8 + 0x20);
                {
                    s64 v = *(s64 *)(p8 + 0x20);
                    if (v > 0) {
                        *r = v - 1;
                    }
                }
                if (*r <= 0) {
                    h = (s16 *)(p6 + 0xA0);
                    if (*(s16 *)(p6 + 0xA0) > 0) {
                        p3 = (u8 *)(arg0 + (i * 2));
                        t = *(s16 *)(p3 + 0xA0) - 1;
                        *(s16 *)(p3 + 0xA0) = t;
                        if (t <= 0) {
                            *h = -1;
                            *q = 0;
                        }
                    } else {
                        *h = 0xC;
                    }
                }
                if (*q == 2) {
                    HpGaugeReleaseSlot_31e310(arg0, i);
                }
            }
        }
        i += 1;
    } while (i < 0x10);
    return 1;
}
