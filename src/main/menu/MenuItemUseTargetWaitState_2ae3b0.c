#include "types.h"

extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void * UiGetWidgetColor_2904b0(s32, s32);
extern s32 StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;

struct Obj0;

struct Obj0 {
    f32 m00;
};

s32 MenuItemUseTargetWaitState_2ae3b0(s32 p0, s32 p1)
{
    s32 t0;
    s32 l1;
    s32 t1;
    struct Obj0 *r2;
    f32 t2;
    s32 t3;
    s32 r3;

    if (p1 != 0) {
        t0 = D_00482364;
        UiEntryListSelectByTag_28ea90(t0, 0x27, 0);
    }
    l1 = 0;
    while (l1 < 0xA) {
        t1 = D_00482360;
        r2 = UiGetWidgetColor_2904b0(t1, ((l1 + 0x8F) & 0xFFFF));
        t2 = r2->m00;
        if (t2 > 1.0f) {
            return 0;
        }
        l1 = (l1 + 1);
    }
    t3 = D_0048235C;
    r3 = StateMachineSetState_28ede0(t3, 0x2A, 0);
    return 1;
}
