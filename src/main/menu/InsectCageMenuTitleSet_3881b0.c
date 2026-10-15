#include "types.h"

extern s32 InsectCageGetType_3910c0(void);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern s32 UiSetTextString_28f510(s32, s32, s32, s32);
extern s32 UiSetTextPos_28f5d0(s32, s32, s32, s32, s32);
extern s32 UiSetTextColor_290a40(s32, s32, s32, s32);
extern s32 UiGetWidgetTextSize_28f430(s32, s32, void *, void *, s32);
extern s32 UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s32 UiWindowFrameSetSize_388380(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483308;

void InsectCageMenuTitleSet_3881b0(void)
{
    s32 v1C;
    s32 v18;
    s32 t0;
    s32 r0;
    s32 r1;
    s32 t1;
    s32 r2;
    s32 t2;
    s32 r3;
    s32 t3;
    s32 r4;
    s32 t4;
    s32 r5;
    s32 t5;
    s32 r6;
    s32 t6;
    s32 t7;
    s32 r7;

    t0 = D_00483308;
    if (t0 != 0) {
        r0 = InsectCageGetType_3910c0();
        r1 = InsectCageMenuMsgLookup_389d30((r0 + 0xA));
        t1 = D_00483308;
        r2 = UiSetTextString_28f510(t1, 0x753A, r1, 0);
        t2 = D_00483308;
        r3 = UiSetTextPos_28f5d0(t2, 0x753A, 0xA, 0x10, 0);
        t3 = D_00483308;
        r4 = UiSetTextColor_290a40(t3, 0x753A, 0xFF444444, 0);
        t4 = D_00483308;
        r5 = UiGetWidgetTextSize_28f430(t4, 0x753A, &v1C, &v18, 0);
        t5 = D_00483308;
        r6 = UiGetWidgetSprite_28fe10(t5, 0x753A, 0);
        t6 = v1C;
        t7 = v18;
        r7 = UiWindowFrameSetSize_388380(r6, (t6 + 0x16), (t7 + 0x10));
        return;
    }
}
