/* rgp:protos */
#define RGP_SELF_MenuItemTabEnterState_2affb0 1
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

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s16 m14;
    s16 m16;
};

s32 MenuItemTabEnterState_2affb0(void)
{
    s32 v2C;
    s32 v28;
    s32 t0;
    s32 t1;
    struct Obj0 *r1;
    s32 t2;
    s32 t3;
    s32 t4;
    s16 t5;
    u8 rv4;
    s16 t6;
    u8 rv5;
    s32 t7;

    t0 = D_00482364;
    UiEntryListSelectByTag_28ea90(t0, 6, 0);
    t1 = D_00482364;
    r1 = (struct Obj0 *)UiEntryListFindByTag_28ea40(t1, 6);
    GetGridCellPosOffset_28ecd0((struct Obj0 *)((u8 *)r1 + 4), &v2C, &v28, 0x62, 0x49);
    t2 = D_00482360;
    t3 = v2C;
    t4 = v28;
    UiSetWidgetPos_290f60(t2, 0x227, t3, t4);
    t5 = r1->m14;
    rv4 = t5;
    if (t5 >= 0) {
        if (t5 >= 3) {
            r1->m14 = 0;
        }
        rv4 = (t5 < 3);
    } else {
        r1->m14 = 0;
        rv4 = t5;
    }
    t6 = r1->m16;
    rv5 = t6;
    if (t6 >= 0) {
        if (t6 >= 3) {
            r1->m16 = 0;
        }
        rv5 = (t6 < 3);
    } else {
        r1->m16 = 0;
        rv5 = t6;
    }
    MenuItemTabsAvailUpdate_2b0070();
    t7 = D_0048235C;
    StateMachineSetState_28ede0(t7, 0x15, 0);
    return 1;
}
