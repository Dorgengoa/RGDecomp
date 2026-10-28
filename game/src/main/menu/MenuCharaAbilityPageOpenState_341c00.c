/* rgp:protos */
#define RGP_SELF_MenuCharaAbilityPageOpenState_341c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct R341c00 {
    u8 pad00[4];
    s16 m04;
    s16 m06;
    u8 pad08[2];
    s16 m0A;
    u8 pad0C[8];
    s16 m14;
    s16 m16;
} R341c00;

typedef struct S341c00 {
    u8 pad00[0x6C];
    s8 m6C;
    u8 pad6D[9];
    s16 m76;
} S341c00;

extern void *D_00482360;
extern void *D_00482364;
extern void *D_0048235C;
extern void *D_004823D8;
extern S341c00 *D_00482378;
extern f32 D_0047D660;
extern f32 D_0047D5D0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuCharaAbilityPageOpenState_341c00(s32 unused, s32 en)
{
    R341c00 *r;

    if (en != 0) {
        r = ((R341c00 *)UiEntryListFindByTag_28ea40(D_00482364, 0x19));
        r->m14 = D_00482378->m6C;
        UiSetWidgetPos_290f60(D_00482360, 0x19E, r->m04, r->m06);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x18D, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x18D, 0.5f);
        UiSetWidgetPos_290f60(D_00482360, 0x18D, 0, r->m16 * r->m0A);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x38, 1, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x37, 1, 1);
        UiSetWidgetColor_2905b0(D_00482360, 0x37, 0.0f, 0.0f, 0.0f, D_0047D660);
        UiSetWidgetPos_290f60(D_00482360, 0x38, 0x11A, -0x28);
        UiSetWidgetPos_290f60(D_00482360, 0x37, 0x11D, -0x25);
        UiMoveWidgetUniform_290f50(D_00482360, 0x38, 0x11A, 0x12, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_00482360, 0x37, 0x11D, 0x15, D_0047D5D0, 0);
        UiSetTextString_28f510(D_00482360, 0x38, MsgTableLookup_28aa30(D_004823D8, 0xBB8), 0);
        D_00482378->m76 = 0;
    }
    StateMachineSetState_28ede0(D_0048235C, 0x7C, 0);
    return 1;
}
