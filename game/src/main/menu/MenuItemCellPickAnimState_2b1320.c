/* rgp:protos */
#define RGP_SELF_MenuItemCellPickAnimState_2b1320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P2b1320 {
    u8 pad00[0x11];
    s8 m11;
    u8 pad12[0xA];
    u8 m1C;
} P2b1320;

typedef struct X2b1320 {
    u8 pad00[0x18];
    void *m18;
} X2b1320;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern P2b1320 *D_00482374;
extern f32 D_0047D430;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

s32 MenuItemCellPickAnimState_2b1320(s32 unused, s32 en)
{
    s32 a;
    s32 b;
    u8 v[0x18] __attribute__((aligned(16)));
    s16 *r;
    X2b1320 *x;
    s32 k;
    s16 *r2;
    void *h;

    if (en != 0) {
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        r = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00482364));
        GetGridCellPosOffset_28ecd0(r, &a, &b, -0x3C, -0x1A);
        MenuItemCellPickSetup_2a3bc0(D_00482374, 0x7B, 0x7C, 0x77, r[8], r[9]);
        MenuShowItemCount_2a02f0(D_00482374, 0x76, 0x74, 0x77, r[8] + r[9] * 8);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x7B, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x7B, 1.0f);
        UiSetWidgetPos_290f60(D_00482360, 0x7B, a + 0xB, b + 0xF);
        UiMoveWidget_290e00(D_00482360, 0x7B, a, b, 1, D_0047D430, 3.0f);
        PlayMenuSe_289ef0(7);
    }
    if (UiWidgetIsMoving_290d30(D_00482360, 0x7B) == 0) {
        x = ((X2b1320 *)GetGameData_1fede0());
        r2 = ((s16 *)UiEntryListGetCurrentData_28ec60(D_00482364));
        h = InvFindByCategoryIndex_3c86e0(x->m18, 0, D_00482374->m11, r2[8], r2[9], 0);
        k = r2[8] + r2[9] * 8;
        MenuItemInfoWidgetsCache_2a65f0(v);
        MenuItemInfoPopupShow_2a33e0(D_00482374, h, 0x1AA, 0x1A9, v, 0x68, 0x15E, k, 2.0f);
        D_00482374->m1C = 1;
        StateMachineSetState_28ede0(D_0048235C, 0xE, 1);
    }
    return 1;
}
