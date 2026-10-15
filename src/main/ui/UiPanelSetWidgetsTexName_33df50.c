#include "types.h"

extern s32 UiPanelGetWidgetDefs_33e960(s32);
extern void strcpy(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u16 m00;
};

void UiPanelSetWidgetsTexName_33df50(s32 p0, s32 p1)
{
    s32 r0;
    struct Obj0 *l1;
    u16 t0;

    r0 = UiPanelGetWidgetDefs_33e960(p0);
    l1 = (struct Obj0 *)r0;
    while (l1 != 0) {
        t0 = l1->m00;
        if (t0 <= 0) {
            return;
        }
        strcpy((struct Obj0 *)((u8 *)l1 + 4), p1);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x94);
    }
}
