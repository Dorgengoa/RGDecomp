#include "types.h"

extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern s32 UiEntryListFindByTag_28ea40(s32, s32);
extern void GetGridCellPosOffset_28ecd0(s32, void *, void *, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void MenuItemTabsAvailUpdate_2b0070(void);
extern s32 StateMachineSetState_28ede0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;

s32 MenuItemTabEnterState_2afa90(void)
{
    s32 v1C;
    s32 v18;
    s32 t0;
    s32 t1;
    s32 r1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    s32 r5;

    t0 = D_00482364;
    UiEntryListSelectByTag_28ea90(t0, 7, 0);
    t1 = D_00482364;
    r1 = UiEntryListFindByTag_28ea40(t1, 7);
    GetGridCellPosOffset_28ecd0((r1 + 4), &v1C, &v18, 0x62, 0x49);
    t2 = D_00482360;
    t3 = v1C;
    t4 = v18;
    UiSetWidgetPos_290f60(t2, 0x227, t3, t4);
    MenuItemTabsAvailUpdate_2b0070();
    t5 = D_0048235C;
    r5 = StateMachineSetState_28ede0(t5, 0x18, 0);
    return 1;
}
