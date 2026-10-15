#include "types.h"

extern s32 Bit64Test_33de60(s32, s32);
extern s32 UiPanelGetWidgetList_33e860(s32);
extern s32 UiUpdateWidgets_2913a0(s32);
extern s32 UiPanelStepIfOpen_33de10(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 UiPanelUpdate_33ded0(s32 p0)
{
    s32 r0;
    s32 rv4;
    s32 r1;
    s32 r2;
    s32 r3;

    r0 = Bit64Test_33de60(p0, 0);
    rv4 = 1;
    if (r0 == 0) {
        rv4 = 0;
    } else {
        r1 = UiPanelGetWidgetList_33e860(p0);
        r2 = UiUpdateWidgets_2913a0(r1);
        r3 = UiPanelStepIfOpen_33de10(p0);
        rv4 = 1;
    }
    return rv4;
}
