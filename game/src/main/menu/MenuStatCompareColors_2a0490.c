/* rgp:protos */
#define RGP_SELF_MenuStatCompareColors_2a0490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D288;
extern f32 D_0047D354;

s32 MenuStatCompareColors_2a0490(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;
    s32 l1;
    s64 t0;
    s16 t1;
    f32 t2;
    f32 t3;
    f32 t4;
    f32 t5;

    r0 = ((s32)UiGetWidgetSubItem_28f2b0(p1, p3, 0));
    if (r0 == 0) {
        return 0;
    }
    l1 = 0;
    do {
        UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x1A0), -1, l1);
        t0 = *(s64 *)((u8 *)r0 + (l1 << 5) + 0x8);
        t1 = *(s16 *)((u8 *)p4 + (l1 << 1));
        if (t0 < t1) {
            UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x80), 1, l1);
        } else {
            if (t1 == t0) {
                UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x20), 1, l1);
            } else {
                UiSetSubItemFlags_28ef30(p1, p3, (long long)(0x100), 1, l1);
            }
        }
        l1 = (l1 + 1);
    } while (l1 < 6);
    t2 = D_0047D288;
    t3 = D_0047D354;
    UiSetWidgetColor_2905b0(p1, p3, t3, t2, t2, 1.0f);
    t4 = D_0047D288;
    t5 = D_0047D354;
    UiSetWidgetColor_2905b0(p1, p2, t4, t5, t4, 1.0f);
    return 1;
}
