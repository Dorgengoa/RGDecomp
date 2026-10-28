/* rgp:protos */
#define RGP_SELF_MenuPartyGridOpenState_2a9450 1
#include "port/game_protos.h"
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: mechanical conversion; length 0x1A8 vs retail 0x1B4. */
#include "types.h"

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
extern f32 D_0047D580;
extern f32 D_0047D6D0;
extern f32 D_0047D6EC;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;
extern s32 D_004823D8;
extern u8 D_004DB430[0x400];

s32 MenuPartyGridOpenState_2a9450(s32 arg0, s32 arg1)
{

    s32 temp_16;
    s32 temp_16_2;
    s32 temp_17;
    s32 temp_2;
    void *temp_2_2;
    s32 a;
    s32 b;

    if (arg1 != 0) {
        temp_16 = *(s32 *)((u8 *)GetGameData_1fede0() + 0x18);
        temp_16_2 = PartyCountMembers_3c2010(temp_16, 1, 1);
        temp_17 = temp_16_2 + PartyCountReserve_3c1c20(temp_16, 1, 1);
        MenuPartyGridLayoutMaybe_2a3fc0(D_00482374);
        temp_2 = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0xAC, 0));
        if (temp_2 == 0) {
            return 0;
        }
        UiLayoutPanelFrame_28d580(temp_2, 0, 0, 0x1B1, 0x10A, 1);
        UiSetWidgetsVisibleById_291110(D_00482360, 0xAC, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0xAC, 0x4A, 0x57);
        UiFadeWidgetAlpha_290690(D_00482360, 0xAC, 1.0f, D_0047D6D0, D_0047D580);
        UiEntryListSelectByTag_28ea90(D_00482364, 0xA, 1);
        temp_2_2 = UiEntryListFindByTag_28ea40(D_00482364, 0xA);
        UiSetWidgetPos_290f60(D_00482360, 0x227, *(s16 *)((u8 *)temp_2_2 + 0x4), *(s16 *)((u8 *)temp_2_2 + 0x6));
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D6EC, -1.0f);
        if (temp_17 < 4) {
            *(s16 *)((u8 *)temp_2_2 + 0xC) = (s16)(temp_17 - 1);
            *(s16 *)((u8 *)temp_2_2 + 0xE) = 0;
        } else {
            *(s16 *)((u8 *)temp_2_2 + 0xC) = 3;
            *(s16 *)((u8 *)temp_2_2 + 0xE) = 1;
        }
        UiSetWidgetPos_290f60(D_00482360, 0xAE, 0x11, 0x31);
        UiSetTextString_28f510(D_00482360, 0xAD, MsgTableLookup_28aa30(D_004823D8, 0x460), 0);
    }
    UiSelFrameAnimStep_28d820(&(*(u8 *)D_004DB430), 0x78);
    StateMachineSetState_28ede0(D_0048235C, 0x47, 0);
    return 1;
}
