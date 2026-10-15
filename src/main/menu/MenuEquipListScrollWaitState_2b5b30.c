/* PARKED: 1 round trip: mechanical conversion; length 0x130 vs retail 0x12C. */
#include "types.h"

extern void UiSelFrameAnimStep_28d820(void *, s32);
extern void *UiEntryListFindByTag_28ea40(s32, s32);
extern void StateMachineSetState_28ede0(s32, s32, s32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiSetWidgetsVisibleById_291110(s32, s32, s32, s32);
extern void MenuEquipCandidateGridRefresh_29e080(s32, s32, s32, s32);
extern s32 MenuGetEquipCandidateCount_29e280(s32);
extern s32 MenuGetEquipCandidate_29f9f0(s32, s32);
extern void MenuEquipCandidateInfoPanelUpdate_2b4360(s32);
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s32 D_00482370;
extern u8 D_004DB790[];
extern u8 D_004DB7C0[];

typedef struct { u8 pad0[0x14]; s16 x14; s16 x16; u8 pad18[2]; s16 x1A; } T;
s32 MenuEquipListScrollWaitState_2b5b30(void)
{
    s32 sp2C;
    s32 sp28;
    s32 var_16;
    T *temp_16;

    UiGetWidgetPos_2910a0(D_00482360, 0x134, &sp2C, &sp28);
    if ((sp28 == 0x32) || (sp28 == -0x32)) {
        temp_16 = (T *)UiEntryListFindByTag_28ea40(D_00482364, 0x15);
        MenuEquipCandidateGridRefresh_29e080(D_00482370, 0x166, MenuGetEquipCandidateCount_29e280(D_00482370), temp_16->x1A);
        MenuEquipCandidateInfoPanelUpdate_2b4360(MenuGetEquipCandidate_29f9f0(D_00482370,
            temp_16->x14 + (temp_16->x16 * 8) +
            (temp_16->x1A * 8)));
        UiSetWidgetPos_290f60(D_00482360, 0x165, 0, 0);
        UiSetWidgetPos_290f60(D_00482360, 0x134, 0, 0);
        var_16 = 0x10;
        do {
            UiSetWidgetsVisibleById_291110(D_00482360, (var_16 + 0x166) & 0xFFFF, 0, 1);
            var_16 += 1;
        } while (var_16 < 0x18);
        StateMachineSetState_28ede0(D_0048235C, 0x60, 0);
    }
    UiSelFrameAnimStep_28d820(D_004DB7C0, 0x14E);
    UiSelFrameAnimStep_28d820(D_004DB790, 0x14D);
    return 1;
}
