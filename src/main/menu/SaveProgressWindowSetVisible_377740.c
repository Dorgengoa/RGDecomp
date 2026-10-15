#include "types.h"

extern void UiSetWidgetVisible_290010(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u16 D_0047FAAC;

void SaveProgressWindowSetVisible_377740(s32 p0, s32 p1)
{
    u16 t0;
    u16 t1;

    if (p0 != 0) {
        if (p1 != 0) {
            t0 = D_0047FAAC;
            UiSetWidgetVisible_290010(p0, t0, 1, -1);
            return;
        }
        t1 = D_0047FAAC;
        UiSetWidgetVisible_290010(p0, t1, 0, -1);
        return;
    }
}
