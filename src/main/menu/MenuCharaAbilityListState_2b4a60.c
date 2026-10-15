#include "types.h"

typedef struct {
    s32 w[6];
} Tmp;

typedef struct {
    s32 w[2];
} It;

extern void *GetGameData_1fede0(void);
extern f32 UiPageScrollBarLayout_289710(s32, s32, s32, s32, s32, s32);
extern void UiLayoutPanelFrame_28d580(s32, s32, s32, s32, s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern s16 *UiEntryListGetCurrentData_28ec60(s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetSpriteX_28fcd0(s32, s32, s32, s32);
extern s16 *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern s32 UiFindWidget_290460(s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiSetWidgetAlpha_2907a0(s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void UiSetWidgetParent_2911a0(s32, s32, s32);
extern void MenuCharaAbilityInfoBoxSetup_29afe0(s32, s32, s32, s32, s32, s32, f32);
extern void MenuCharaAbilityListFill_29b180(s32, s32, s32);
extern s32 MenuGetListCount_29b580(s32);
extern void MenuSetScrollStep_29f990(s32, f32);
extern void MenuSetScrollTop_29fa50(s32, s32);
extern s32 MenuGetCursorIndex_29fa80(s32);
extern s8 *MenuGetCursorPos_29fae0(s32);
extern u8 MenuPartyFadeSequenceStep_2b9240(s32, s32, s32);
extern s32 IterNext_370040(It *);
extern void IterInit_370170(It *, Tmp *);
extern void CharaAbilityViewCtor_3a8180(Tmp *, s32, s32, s32);
extern s32 PartyGetSlotChara_3c2fb0(s32, s32);
extern u16 D_004614C0[];
extern f32 D_0047D5D0;
extern f32 D_0047D678;
extern f32 D_0047D67C;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern f32 D_00482584;
extern s16 D_00482588;

s32 MenuCharaAbilityListState_2b4a60(s32 arg0, s32 arg1)
{
    It it;
    Tmp t;
    s16 *p;
    s32 g;
    s32 c;

    if (arg1 != 0) {
        MenuCharaAbilityListFill_29b180(D_00482370, MenuGetCursorIndex_29fa80(D_00482370), 0);
        MenuSetScrollStep_29f990(D_00482370, UiPageScrollBarLayout_289710(D_00482370, 0x12E, 0x8D, 5, (s16)MenuGetListCount_29b580(D_00482370), 0));
        UiSetWidgetPos_290f60(D_00482360, 0x12E, 0x18A, 0x24);
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x122, 0);
        if (p == 0) {
            return 0;
        }
        p[0xC6 / 2] = 0x70;
        p[0x26 / 2] = 0x70;
        p[0xE2 / 2] = 0xAF;
        p[0x82 / 2] = 0xAF;
        p[0x42 / 2] = 0xAF;
        p = UiGetWidgetSprite_28fe10(D_00482360, 0x12D, 0);
        if (p == 0) {
            return 0;
        }
        p[0x26 / 2] = 0x80;
        p[0x42 / 2] = 0xB7;
        UiSetSpriteX_28fcd0(D_00482360, 0x12B, -1, 5);
        UiSetSpriteX_28fcd0(D_00482360, 0x12C, -1, 5);
        MenuSetScrollTop_29fa50(D_00482370, 0);
    }
    if (MenuPartyFadeSequenceStep_2b9240(0x183, 0x11E, D_004614C0[MenuGetCursorPos_29fae0(D_00482370)[1]]) != 0) {
        UiLayoutPanelFrame_28d580(*(s32 *)(UiFindWidget_290460(D_00482360, 0x121) + 0x20), 0, 0, 0x1B1, 0xD2, 0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x121, 1, 1);
        UiSetWidgetPos_290f60(D_00482360, 0x121, 0x42, 0x90);
        UiFadeWidgetAlpha_290690(D_00482360, 0x121, 1.0f, D_0047D678, 0.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x183, 1.0f, D_0047D67C, -1.0f);
        UiSetWidgetParent_2911a0(D_00482360, 0x183, 0x121);
        UiEntryListSelectByTag_28ea90(D_00482364, 0x16, 1);
        p = UiEntryListGetCurrentData_28ec60(D_00482364);
        UiSetWidgetPos_290f60(D_00482360, 0x183, p[0], p[1]);
        g = (s32)GetGameData_1fede0();
        c = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), MenuGetCursorIndex_29fa80(D_00482370));
        if (c == 0) {
            return 0;
        }
        CharaAbilityViewCtor_3a8180(&t, c, -1, -1);
        IterInit_370170(&it, &t);
        MenuCharaAbilityInfoBoxSetup_29afe0(D_00482370, IterNext_370040(&it), 0x1AA, 0x1A9, 0x5D, 0x146, D_0047D5D0);
        UiSetWidgetsVisibleById_291110(D_00482360, 0x123, 1, 1);
        UiSetWidgetAlpha_2907a0(D_00482360, 0x123, 0.5f);
        UiSetWidgetPos_290f60(D_00482360, 0x123, 0xA, -0xC);
        D_00482584 = 0.5f;
        D_00482588 = 1;
        StateMachineSetState_28ede0(D_0048235C, 0x6B, 0);
    }
    return 1;
}
