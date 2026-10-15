#include "types.h"

extern s32 UiSetWidgetVisible_290010(s32, s32, s32, s32);
extern s32 InsectCageGetType_3910c0(void);
extern s32 InsectCageMenuRefreshInsectNames_38d5f0(void);
extern s32 InsectCageMenuSetRowMarker_389a80(s32, s32, s32, s32);
extern s32 InsectCageMenuSlotTextSetStateMaybe_38d550(s32, s32);
extern s32 InsectCageMenuMsgLookup_389d30(s32);
extern s32 strcpy(s32, s32);
extern s32 UiFitCenterWindow_388270(s32, s32);
extern s32 InsectCageMenuSetCursorVisible_389d00(s32);
extern s32 InsectCageMenuSetCursorTarget_389790(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483304;
extern s32 D_00483308;
extern s16 D_00483334;

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 InsectCageMenuSwitchCageOpen_38caa0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 l3;
    s32 l4;
    s32 r5;
    s32 r6;
    s16 t1;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 t2;
    s32 r10;
    s32 r11;
    s32 r12;
    s32 r13;

    t0 = D_00483308;
    r0 = UiSetWidgetVisible_290010(t0, 0x7576, 1, -1);
    D_00483334 = 2;
    r1 = InsectCageGetType_3910c0();
    p0->m10 = r1;
    r2 = InsectCageMenuRefreshInsectNames_38d5f0();
    l3 = r2;
    l4 = 0;
    do {
        r5 = InsectCageMenuSetRowMarker_389a80(0, 0, l4, -1);
        r6 = InsectCageMenuSetRowMarker_389a80(1, 0, l4, -1);
        l3 = ((l4 + 1) < 3);
        l4 = (l4 + 1);
    } while (l3 != 0);
    t1 = p0->m10;
    r7 = InsectCageMenuSlotTextSetStateMaybe_38d550(t1, 0);
    r8 = UiSetWidgetVisible_290010(p1, 0x754E, 1, -1);
    r9 = InsectCageMenuMsgLookup_389d30(0x578);
    t2 = D_00483304;
    r10 = strcpy((t2 + 0x200), r9);
    r11 = UiFitCenterWindow_388270(0x754E, 0);
    r12 = InsectCageMenuSetCursorVisible_389d00(1);
    r13 = InsectCageMenuSetCursorTarget_389790(1, p0, 1);
    return 1;
}
