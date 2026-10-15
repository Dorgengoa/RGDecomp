#include "types.h"

extern u8 D_00464188[0x400];
extern u8 D_00464198[0x400];

#pragma opt_propagation off
void UiIconSetUvByIndexMaybe_3925d0(s32 pd0, void *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_4;
    s32 temp_5;
    u8 *var_7;
    s16 a, b;

    if ((arg1 != NULL) && ((temp_4 = *(s32 *)((u8 *)arg1 + 0x20)) != 0)) {
        if (arg3 == 0) {
            var_7 = (u8 *)temp_4 + 0x20;
        } else {
            var_7 = (u8 *)temp_4 + (arg4 << 5);
        }
        if ((arg2 >= 0) && (arg2 < 5)) {
            a = ((s16 *)D_00464188)[arg2];
            b = ((s16 *)D_00464198)[arg2];
            *(s16 *)(var_7 + 0x8) = a;
            *(s16 *)(var_7 + 0xA) = b;
            return;
        }
        *(s16 *)(var_7 + 0xA) = 0;
        *(s16 *)(var_7 + 0x8) = 0;
        *(s16 *)(var_7 + 0x4) = 0;
        *(s16 *)(var_7 + 0xC) = 0;
        *(s16 *)(var_7 + 0x6) = 0;
        *(s16 *)(var_7 + 0xE) = 0;
    }
}
