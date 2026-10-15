#include "types.h"

typedef struct S004B2570 {
    u8 pad0[0x12];
    s16 unk12;
} S004B2570;

typedef struct D0048470CType {
    u8 pad0[0x18];
    s32 unk18;
} D0048470CType;

extern void *GetGameData_1fede0(void);
extern s32 MenuGridCursorInput_28e170(s32 arg0, void *arg1, s32 arg2, s32 arg3);
extern S004B2570 *UiEntryListGetCurrentData_28ec60(s32 arg0);
extern void StateMachineSetState_28ede0(s32 arg0, s32 arg1, s32 arg2);
extern void UiSetTextColorScaled_290850(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4);
extern s32 MenuGetMode_2a4e30(s32 arg0);
extern void InvOrganizeMaybe_3c50c0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_0047D35C;
extern f32 D_0047D970;
extern f32 D_0047FB30;
extern s16 D_00483254;
extern s32 D_0048470C;
extern D0048470CType *D_00484710;
extern s32 D_00484720;
extern s32 D_00484740;
extern u8 D_004B2570[0x400];

s32 TransMenuItemCmdPopupSelectState_37c170(void)
{
    f32 temp_f12;
    s32 temp_7;
    s32 temp_16;
    D0048470CType *temp_16_2;
    S004B2570 *temp_2;

    temp_16 = MenuGridCursorInput_28e170(D_00484720, &(*(u8 *)D_004B2570), 4, 0);
    temp_2 = UiEntryListGetCurrentData_28ec60(D_00484720);
    if (D_00483254 == 0) {
        if (temp_16 == 1) {
            temp_7 = temp_2->unk12;
            D_00483254 = temp_7 + 1;
            UiSetTextColorScaled_290850((s32) D_00484710, 0x762A, 0xFF303030, temp_7, D_0047FB30);
        } else if (temp_16 == 2) {
            StateMachineSetState_28ede0(D_0048470C, 0x32, 0);
        }
    } else {
        temp_f12 = D_0047FB30 - D_0047D970;
        D_0047FB30 = temp_f12;
        UiSetTextColorScaled_290850((s32) D_00484710, 0x762A, 0xFF303030, (s16)(s32)D_00483254 - 1, temp_f12);
        if (D_0047FB30 <= 1.0f) {
            temp_16_2 = GetGameData_1fede0();
            switch (D_00483254) {
            case 1:
                InvOrganizeMaybe_3c50c0(temp_16_2->unk18, MenuGetMode_2a4e30(D_00484740), -1, 0x23);
                break;
            case 2:
                InvOrganizeMaybe_3c50c0(temp_16_2->unk18, MenuGetMode_2a4e30(D_00484740), -1, 0x13);
                break;
            case 3:
                break;
            }
            D_00483254 = 0;
            D_0047FB30 = D_0047D35C;
            StateMachineSetState_28ede0(D_0048470C, 0x32, 0);
        }
    }
    return 1;
}
