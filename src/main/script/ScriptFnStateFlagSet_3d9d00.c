#include "types.h"

extern s32 VariantGetS8_36fe50(s32);
extern void StateFlagSet_3ccb70(s32, s32, s32, s32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
extern void *D_00483968;

void ScriptFnStateFlagSet_3d9d00(s32 arg0, s32 *arg1)
{
    s32 temp_16;
    s32 temp_18;
    s32 temp_17;
    u8 var_3;
    s32 var_7;

    if (arg0 == 0 || arg1 == NULL) {
        return;
    }
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
            temp_18 = *arg1;
            temp_16 = StateFlagTest_3ccd70(*(s32 *)((u8 *)D_00483960 + 0x10), temp_18) & 0xFF;
            temp_17 = VariantGetS8_36fe50(arg0) != 0;
            StateFlagSet_3ccb70(*(s32 *)((u8 *)D_00483960 + 0x10), 0x7F3, 0, 1);
            var_3 = 0;
            if (((temp_18 >= 0x4B0) && (temp_18 <= 0x53B)) || ((temp_18 >= 0x44C) && (temp_18 <= 0x493)) || ((temp_18 >= 0x582) && (temp_18 <= 0x596)) || ((temp_18 >= 0x5A0) && (temp_18 <= 0x5B0)) || ((temp_18 >= 0x5B4) && (temp_18 <= 0x5CA))) {
                var_3 = 1;
            }
            if (var_3 && (temp_16 == 0)) {
                StateFlagSet_3ccb70(*(s32 *)((u8 *)D_00483960 + 0x10), 0x7F3, 1, 1);
            }
            var_7 = 0;
            if (D_00483968 != NULL) {
                var_7 = *(u8 *)((u8 *)D_00483968 + 0xE0C) & 1;
            }
            StateFlagSet_3ccb70(*(s32 *)((u8 *)D_00483960 + 0x10), temp_18, temp_17, var_7);
}
