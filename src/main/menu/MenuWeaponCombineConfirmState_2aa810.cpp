#include "types.h"

extern "C" {
void UiSelFrameAnimStep_28d820(void *, s32);
s32 MenuGridCursorInput_28e170(s32, void *, s32, s32);
void UiEntryListSelectByTag_28ea90(s32, s32, s32);
u8 *UiEntryListGetCurrentData_28ec60(s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
void MenuWeaponCombineResultModelRelease_2a85e0(s32);
void MenuWeaponCombineUpdate_362920(s32, s32);
extern f32 D_0047D720;
extern f32 D_0047D724;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482384;
extern u8 D_004B2570[0x400];
extern u8 D_004DB430[];
}

extern "C" s32 MenuWeaponCombineConfirmState_2aa810(void) {
    s32 r;
    bool flag;
    u8 *p;

    r = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
    p = UiEntryListGetCurrentData_28ec60(D_00482364);
    MenuWeaponCombineUpdate_362920(D_00482384, r);
    flag = false;
    if (r == 1) {
        if (*(s16 *)(p + 0x10) == 0) {
            MenuWeaponCombineResultModelRelease_2a85e0(0);
        }
        flag = true;
    } else if (r == 2) {
        flag = true;
    }
    if (flag) {
        UiFadeWidgetAlpha_290690(D_00482360, 0x13C, 0.0f, D_0047D720, -1.0f);
        UiEntryListSelectByTag_28ea90(D_00482364, 3, 0);
        UiFadeWidgetAlpha_290690(D_00482360, 0x227, 1.0f, D_0047D724, -1.0f);
        UiFadeWidgetAlpha_290690(D_00482360, 0x78, 1.0f, D_0047D724, -1.0f);
    }
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
