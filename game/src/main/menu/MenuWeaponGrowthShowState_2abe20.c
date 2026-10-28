/* rgp:protos */
#define RGP_SELF_MenuWeaponGrowthShowState_2abe20 1
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
extern f32 D_0047D750;
extern f32 D_0047D758;
extern f32 D_0047D75C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482374;
extern s32 D_00482384;
extern u8 D_004823CC;
extern s32 D_004823D8;
extern u8 D_004DB430[];

s32 MenuWeaponGrowthShowState_2abe20(s32 pad0, s32 arg1) {
    s8 *obj;
    s32 a;
    s32 b;
    s32 i;
    s32 n;
    s32 w;

    if (arg1 != 0) {
        obj = ((s8 *)MenuGetSelItem_2a02d0(D_00482374));
        if (obj == NULL) {
            return 0;
        }
        MenuDrawWeaponGrowth_2a0600(D_00482374, D_00482360, obj, 0x161, 0x157, 0x153, 0x15F);
        UiSetWidgetVisible_290010(D_00482360, 0x151, 1, -1);
        UiSetWidgetPos_290f60(D_00482360, 0x151, 0xBE, 0x8C);
        UiFadeWidgetAlpha_290690(D_00482360, 0x151, 1.0f, D_0047D758, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 0.0f, D_0047D750, -1.0f);
        w = *(s32 *)(obj + 0x10);
        a = ((s32)UiGetWidgetSprite_28fe10(D_00482360, 0x164, 0));
        if (a == 0) {
            return 0;
        }
        b = ((s32)UiGetWidgetText_28f620(D_00482360, 0x164, 0));
        if (b == 0) {
            return 0;
        }
        if (MenuWeaponCmdListBuildMaybe_289c90(w, D_004823D8, a, b) > 0) {
            UiSetWidgetsVisibleById_291110(D_00482360, 0x163, 1, 1);
            UiFadeWidgetAlpha_290690(D_00482360, 0x163, 1.0f, D_0047D758, 0.0f);
            UiSetWidgetPos_290f60(D_00482360, 0x163, 0x168, 0x85);
        }
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
        if (D_004823CC == 0) {
            if (MenuGetMode_2a4e30(D_00482374) == 9) {
                UiFadeWidgetColor_2904e0(D_00482360, 0x65, 1.5f, D_0047D278, D_0047D288, 1.0f, D_0047D75C);
            } else {
                UiFadeWidgetColor_2904e0(D_00482360, 0x65, D_0047D278, D_0047D278, D_0047D278, 1.0f, D_0047D75C);
            }
            for (i = 0, n = D_004659F0[0] * D_004659F8[0]; i < n; i++) {
                UiSetSpriteFlags_290bd0(D_00482360, 0x76, (long long)(0x20), 1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x74, (long long)(0x20), 1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x76, (long long)(0x18), -1, i, 0);
                UiSetSpriteFlags_290bd0(D_00482360, 0x74, (long long)(0x18), -1, i, 0);
            }
        }
    }
    if (D_004823CC != 0) {
        w = D_00482384;
        MenuWeaponCombineAutoHideTick_362700(w);
        MenuWeaponCombineAnimTickMaybe_361cd0(w);
    }
    StateMachineSetState_28ede0(D_0048235C, 0x1E, 0);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
