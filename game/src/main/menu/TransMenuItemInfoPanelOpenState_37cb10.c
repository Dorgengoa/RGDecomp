/* rgp:protos */
#define RGP_SELF_TransMenuItemInfoPanelOpenState_37cb10 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/
extern s32 D_004659F0[];
extern s32 D_004659F8[];
extern f32 D_0047D278;
extern f32 D_0047D288;
extern f32 D_0047D968;
extern f32 D_0047D964,D_0047D970;
extern f32 D_0047D96C;
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern s32 D_00482384;
extern u8 D_004823CC;
extern s32 D_00484770;
extern u8 D_004E9230[];

s32 TransMenuItemInfoPanelOpenState_37cb10(s32 pad0, s32 arg1) {
    s8 *obj;
    s32 a;
    s32 b;
    s32 i;
    s32 n;
    s32 w;

    if (arg1 != 0) {
        obj = ((s8 *)MenuGetSelItem_2a02d0(D_00484740));
        if (obj == NULL) {
            return 0;
        }
        MenuDrawWeaponGrowth_2a0600(D_00484740, D_00484710, obj, 0x7629, 0x7627, 0x7623, 0x7628);
        UiSetWidgetsVisibleById_291110(D_00484710, 0x7622, 1, 1);
        UiSetWidgetPos_290f60(D_00484710, 0x7622, 0xBE, 0x8C);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7622, 1.0f, D_0047D964, 0.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7632, 0.0f, D_0047D968, -1.0f);
        UiFadeWidgetColor_2904e0(D_00484710,0x75F8,D_0047D278,D_0047D278,D_0047D278,1.0f,D_0047D96C);
        w = *(s32 *)(obj + 0x10);
        a = ((s32)UiGetWidgetSprite_28fe10(D_00484710, 0x7659, 0));
        if (a == 0) {
            return 0;
        }
        b = ((s32)UiGetWidgetText_28f620(D_00484710, 0x7659, 0));
        if (b == 0) {
            return 0;
        }
        if (MenuWeaponCmdListBuildMaybe_289c90(w, D_00484770, a, b) > 0) {
            UiSetWidgetsVisibleById_291110(D_00484710, 0x7658, 1, 1);
            UiFadeWidgetAlpha_290690(D_00484710, 0x7658, 1.0f, D_0047D970, 0.0f);
            UiSetWidgetPos_290f60(D_00484710, 0x7658, 0x168, 0x85);
        }
        UiEntryListSelectByTag_28ea90(D_00484720, 0xF, 0);
            for (i = 0, n = D_004659F0[0] * D_004659F8[0]; i < n; i++) {
                UiSetSpriteFlags_290bd0(D_00484710, 0x7602, (long long)(0x20), 1, i, 0);
                UiSetSpriteFlags_290bd0(D_00484710, 0x7600, (long long)(0x20), 1, i, 0);
                UiSetSpriteFlags_290bd0(D_00484710, 0x7602, (long long)(0x18), -1, i, 0);
                UiSetSpriteFlags_290bd0(D_00484710, 0x7600, (long long)(0x18), -1, i, 0);
            }
    }
    StateMachineSetState_28ede0(D_0048470C, 0x3B, 0);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
