/* rgp:protos */
#define RGP_SELF_MenuItemCmdPopupSelectState_2ac290 1
#include "port/game_protos.h"
#line 1
/* PARKED: 1 round trip: mechanical conversion; length 0x164 vs retail 0x16C (close). */
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D35C;
extern f32 D_0047D6D0;
extern f32 D_0047EC88;
extern s32 D_0048235C;
extern s32 D_00482360;
extern s32 D_00482364;
extern s16 D_004824F4;
extern u8 D_004B2570[0x400];

s32 MenuItemCmdPopupSelectState_2ac290(void)
{
    f32 temp_f12;
    s32 temp_7;
    s32 temp_16;
    void *temp_2;
    void *temp_2_2;
    s32 n;

    temp_16 = MenuGridCursorInput_28e170(D_00482364, &(*(u8 *)D_004B2570), 4, 0);
    temp_2 = UiEntryListGetCurrentData_28ec60(D_00482364);
    n = D_004824F4;
    if (n == 0) {
        if (temp_16 == 1) {
            temp_7 = *(s16 *)((u8 *)temp_2 + 0x12);
            D_004824F4 = temp_7 + 1;
            UiSetTextColorScaled_290850(D_00482360, 0x89, 0xFF303030, temp_7, D_0047EC88);
        } else if (temp_16 == 2) {
            StateMachineSetState_28ede0(D_0048235C, 0x3B, 0);
        }
    } else {
        temp_f12 = D_0047EC88 - D_0047D6D0;
        D_0047EC88 = temp_f12;
        UiSetTextColorScaled_290850(D_00482360, 0x89, 0xFF303030, (s16)n - 1, temp_f12);
        if (D_0047EC88 <= 1.0f) {
            temp_2_2 = GetGameData_1fede0();
            switch (D_004824F4) {
            case 1:
                InvOrganizeMaybe_3c50c0(*(s32 *)((u8 *)temp_2_2 + 0x18), 0, -1, 0x23);
                break;
            case 2:
                InvOrganizeMaybe_3c50c0(*(s32 *)((u8 *)temp_2_2 + 0x18), 0, -1, 0x13);
                break;
            case 3:
                break;
            }
            D_004824F4 = 0;
            D_0047EC88 = D_0047D35C;
            StateMachineSetState_28ede0(D_0048235C, 0x3B, 0);
        }
    }
    return 1;
}
