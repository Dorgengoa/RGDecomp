#include "types.h"


extern f32 Sinf_128fd0(f32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern void PlayMenuSe_289ef0(s32);
extern void PhaseAdvanceWrapPi_28b630(f32 *, f32);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern s32 MenuGridCursorInput_28e170(u8 *, void *, s32, s32);
extern void UiEntryListSelectByTag_28ea90(u8 *, s32, s32);
extern void *UiEntryListGetCurrentData_28ec60(u8 *);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern u8 *MenuGetSelItem_2a02d0(u8 *);
extern void MenuItemPageRefresh_2a03d0(u8 *, s32, s32, s32, s32, s32, s32);
extern void MenuShowMoneyAndItemCounts_2a32d0(u8 *, s32, s32);
extern void ItemPurgeUnheldKind9Maybe_2a6ee0(void);
extern void MenuItemDiscardConfirmLayout_2acb40(s32, s32);
extern void MenuToggleSpriteApply_2b3ab0(s32, s32, s32);
extern void ItemConsume_3d41b0(u8 *, s32, s32);
extern f32 D_0047D3B8;
extern f32 D_0047D6D0;
extern s32 D_0048235C;
extern s32 D_00482360;
extern u8 *D_00482364;
extern u8 *D_00482374;
extern s8 D_0048249C;
extern f32 D_004824C8;
extern s8 D_004824DC;
extern u8 D_004B2570[0x400];
extern u8 D_004DB430[0x400];

s32 MenuItemDiscardConfirmState_2ac750(s32 pad0, s32 arg1)
{
    u8 *r;
    s32 k;
    s16 x;
    f32 f;

    if (arg1 != 0) {
        if (D_0048249C != 0) {
            MenuItemDiscardConfirmLayout_2acb40(0, -1);
        } else {
            r = MenuGetSelItem_2a02d0(D_00482374);
            if (r == 0) {
                return 0;
            }
            k = *(s32 *)(D_00482374 + 0x3C);
            MenuItemDiscardConfirmLayout_2acb40(**(s16 **)(r + 0x10), k);
        }
        UiSetWidgetsVisibleById_291110(D_00482360, 0xA0, 1, 1);
        x = 0;
        if (D_0048249C != 0) {
            x = 1;
        }
        UiSetWidgetPos_290f60(D_00482360, 0xA0, 0x80, x * 40 + 0xA0);
        UiFadeWidgetAlpha_290690(D_00482360, 0xA0, 1.0f, D_0047D6D0, 0.0f);
        if (D_0048249C != 0) {
            D_004824DC = 0;
            MenuToggleSpriteApply_2b3ab0(0, D_00482360, 0xA2);
            UiSetWidgetPos_290f60(D_00482360, 0xA3, 0x50, 0x3D);
        } else {
            D_004824DC = 1;
            MenuToggleSpriteApply_2b3ab0(1, D_00482360, 0xA2);
            UiSetWidgetPos_290f60(D_00482360, 0xA3, 0xA0, 0x3D);
        }
        UiEntryListSelectByTag_28ea90(D_00482364, 0x26, 0);
    } else {
        k = MenuGridCursorInput_28e170(D_00482364, D_004B2570, 0, 0);
        UiEntryListGetCurrentData_28ec60(D_00482364);
        if (k == 1) {
            if (D_004824DC == 0) {
                if (D_0048249C != 0) {
                    D_0048249C = 2;
                    ItemPurgeUnheldKind9Maybe_2a6ee0();
                    MenuItemPageRefresh_2a03d0(D_00482374, 0x67, 0x76, 0x74, 0x77, 0x31, 0x30);
                } else {
                    r = MenuGetSelItem_2a02d0(D_00482374);
                    if (r == 0) {
                        return 0;
                    }
                    ItemConsume_3d41b0(r, *(s32 *)(D_00482374 + 0x3C), 0);
                    MenuShowMoneyAndItemCounts_2a32d0(D_00482374, 0x31, 0x30);
                }
            }
            StateMachineSetState_28ede0(D_0048235C, 0x35, 0);
        } else if (k == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x35, 0);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
            if (D_004824DC == 1) {
                PlayMenuSe_289ef0(4);
            }
            D_004824DC = 0;
            MenuToggleSpriteApply_2b3ab0(0, D_00482360, 0xA2);
        } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
            if (D_004824DC == 0) {
                PlayMenuSe_289ef0(4);
            }
            D_004824DC = 1;
            MenuToggleSpriteApply_2b3ab0(1, D_00482360, 0xA2);
        }
    }
    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    f = 8.0f * Sinf_128fd0(D_004824C8);
    UiMoveWidgetUniform_290f50(D_00482360, 0xA3, (s32)(f + (f32)((D_004824DC + 1) * 80)), 0x3D, 0, 0.25f);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
