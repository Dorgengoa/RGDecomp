#include "types.h"

extern s32 Bit64Test_33de60(s32, s32);
extern s32 Bit64Assign_33de80(s32, s32, s32);
extern s32 UiPanelGetWidgetList_33e860(s32);
extern s32 UiSetWidgetVisible_290010(s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiPanelClose_33dc80(s32 p0)
{
    s32 r0;
    s32 rv9;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;

    r0 = Bit64Test_33de60(p0, 7);
    rv9 = r0;
    if (r0 != 0) {
        r1 = Bit64Assign_33de80(p0, 0, 0);
        r2 = Bit64Assign_33de80(p0, 1, 0);
        r3 = Bit64Assign_33de80(p0, 2, 0);
        r4 = Bit64Assign_33de80(p0, 7, 0);
        r5 = Bit64Assign_33de80(p0, 0xA, 0);
        r6 = Bit64Assign_33de80(p0, 9, 0);
        r7 = UiPanelGetWidgetList_33e860(p0);
        r8 = UiSetWidgetVisible_290010(r7, 1, 0, -1);
        rv9 = r8;
    }
    return rv9;
}
