/* rgp:protos */
#define RGP_SELF_MenuItemTabEnterState_2af3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;

s32 MenuItemTabEnterState_2af3e0(void)
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
    UiEntryListSelectByTag_28ea90(t0, 8, 0);
    t1 = D_00482364;
    r1 = ((s32)UiEntryListFindByTag_28ea40(t1, 8));
    GetGridCellPosOffset_28ecd0((r1 + 4), &v1C, &v18, 0x62, 0x49);
    t2 = D_00482360;
    t3 = v1C;
    t4 = v18;
    UiSetWidgetPos_290f60(t2, 0x227, t3, t4);
    MenuItemTabsAvailUpdate_2b0070();
    t5 = D_0048235C;
    r5 = StateMachineSetState_28ede0(t5, 0x1B, 0);
    return 1;
}
