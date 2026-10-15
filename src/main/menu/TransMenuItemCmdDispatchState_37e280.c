#include "types.h"

extern void *GetGameData_1fede0(void);
extern void UiSelFrameAnimStep_28d820(void *, s32);
extern s32 UiEntryListFindByTag_28ea40(s32, s32);
extern void UiEntryListSelectByTag_28ea90(s32, s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiFadeWidgetColor_2904e0(s32, s32, f32, f32, f32, f32, f32);
extern void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
extern f32 UiGetWidgetAlpha_290770(s32, s32);
extern void MenuShowMoneyAndItemCounts_2a32d0(s32, s32, s32);
extern s32 MenuGetMode_2a4e30(s32);
extern void InvMergeStacksMaybe_3c57f0(s32, s32, s32);
extern s32 InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
extern f32 D_0047D35C;
extern f32 D_0047D5D0;
extern f32 D_0047D980;
extern f32 D_0047D984;
extern f32 D_00483238;
extern s32 D_0048470C;
extern s32 D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern u8 D_004E9230[];

s32 TransMenuItemCmdDispatchState_37e280(s32 arg0, s32 arg1)
{
    s32 e;
    s32 g;
    s32 k;
    s32 h;
    s32 i;
    f32 v;
    f32 t;

    if (arg1 != 0) {
        UiEntryListSelectByTag_28ea90(D_00484720, 0x10, 0);
        D_00483238 = 0.0f;
        UiFadeWidgetAlpha_290690(D_00484710, 0x762B, 0.0f, -1.0f, -1.0f);
    } else {
        e = UiEntryListFindByTag_28ea40(D_00484720, 0xC);
        v = UiGetWidgetAlpha_290770(D_00484710, 0x762B);
        if (v < D_0047D5D0 && D_00483238 == 0.0f) {
            UiFadeWidgetColor_2904e0(D_00484710, (*(s16 *)(e + 0x16) + 0x7652) & 0xFFFF, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D35C, D_0047D5D0);
            D_00483238 = 1.0f;
        }
        if (D_00483238) {
            v = UiGetWidgetAlpha_290770(D_00484710, (*(s16 *)(e + 0x16) + 0x7652) & 0xFFFF);
            if (v >= D_0047D35C) {
                UiFadeWidgetColor_2904e0(D_00484710, (*(s16 *)(e + 0x16) + 0x7652) & 0xFFFF, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D980);
            } else if (v <= 1.0f) {
                t = D_00483238; t = t + 1.0f; D_00483238 = t;
                if (!(t <= 7.0f)) {
                    g = (s32)GetGameData_1fede0();
                    k = *(s16 *)(D_00484740 + 0x42);
                    h = MenuGetMode_2a4e30(D_00484740);
                    switch (*(s16 *)(e + 0x16)) {
                    case 0:
                        *(s8 *)(D_00484740 + 0x40) = 3;
                        StateMachineSetState_28ede0(D_0048470C, 0x3D, 0);
                        break;
                    case 1:
                        if (k == 0) {
                            *(s8 *)(D_00484740 + 0x40) = 2;
                            StateMachineSetState_28ede0(D_0048470C, 0x2D, 0);
                        } else if (k == 1) {
                            StateMachineSetState_28ede0(D_0048470C, 0x3A, 0);
                        }
                        break;
                    case 2:
                        if (k == 0) {
                            StateMachineSetState_28ede0(D_0048470C, 0x33, 0);
                        } else if (k == 1) {
                            *(s8 *)(D_00484740 + 0x40) = 1;
                            StateMachineSetState_28ede0(D_0048470C, 0x2A, 0);
                        } else if (k == 3) {
                            *(s8 *)(D_00484740 + 0x40) = 2;
                            StateMachineSetState_28ede0(D_0048470C, 0x2D, 0);
                        }
                        break;
                    case 3:
                        if (k == 0) {
                            *(s8 *)(D_00484740 + 0x40) = 1;
                            StateMachineSetState_28ede0(D_0048470C, 0x2A, 0);
                        } else if (k == 1) {
                            *(s8 *)(D_00484740 + 0x40) = 2;
                            StateMachineSetState_28ede0(D_0048470C, 0x2D, 0);
                        } else if (k == 3) {
                            StateMachineSetState_28ede0(D_0048470C, 0x30, 0);
                        }
                        break;
                    case 4:
                        if (k == 0) {
                            s32 m = UiEntryListFindByTag_28ea40(D_00484720, 0xB);
                            InvMergeStacksMaybe_3c57f0(*(s32 *)(g + 0x18), InvFindByCategoryIndex_3c86e0(*(s32 *)(g + 0x18), h, *(s8 *)(D_00484740 + 0x11), *(s16 *)(m + 0x14), *(s16 *)(m + 0x16), 0), 0);
                            MenuShowMoneyAndItemCounts_2a32d0(D_00484740, 0x754A, 0x7549);
                            StateMachineSetState_28ede0(D_0048470C, 0x24, 0);
                        } else if (k == 1) {
                            StateMachineSetState_28ede0(D_0048470C, 0x30, 0);
                        } else if (k == 4) {
                            *(s8 *)(D_00484740 + 0x40) = 2;
                            StateMachineSetState_28ede0(D_0048470C, 0x2D, 0);
                        }
                        break;
                    case 5:
                        StateMachineSetState_28ede0(D_0048470C, 0x30, 0);
                        break;
                    }
                } else {
                    if (t == 3.0f) {
                        UiFadeWidgetAlpha_290690(D_00484710, 0x760A, 0.0f, D_0047D984, -1.0f);
                        UiFadeWidgetAlpha_290690(D_00484710, 0x7609, 0.0f, D_0047D984, -1.0f);
                        i = 0;
                        do {
                            UiFadeWidgetAlpha_290690(D_00484710, (i + 0x7652) & 0xFFFF, 0.0f, D_0047D984, -1.0f);
                            i++;
                        } while (i < 6);
                    }
                }
            }
        }
    }
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
