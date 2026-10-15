#include "types.h"

void InsectHudBarSetRatioMaybe_392370(s32 pd0, void *arg1, s32 arg2, f32 fparg0)
{
    f32 temp_f1;
    f32 var_f3;
    u8 *temp_7;

    if (arg1 != NULL) {
        temp_7 = *(u8 **)((u8 *)arg1 + 0x20);
        if (temp_7 != NULL) {
            var_f3 = 218.0f * fparg0;
            temp_f1 = 50.0f * fparg0;
            *(s16 *)(temp_7 + 0xC) = (s16)(s32)temp_f1;
            switch (arg2) {
            case 0:
                break;
            case 1:
                *(s16 *)(temp_7 + 0) = (s16)(s32)(218.0f - var_f3);
                *(s16 *)(temp_7 + 8) = (s16)(s32)(332.0f + temp_f1);
                *(s16 *)(temp_7 + 0xA) = 0xF4;
                *(s16 *)(temp_7 + 0xC) = (s16)(-*(s16 *)(temp_7 + 0xC));
                break;
            }
            if (var_f3 <= 0.0f) {
                var_f3 = 0.0f;
                *(s16 *)(temp_7 + 0xC) = 0;
            }
            *(s16 *)(temp_7 + 4) = (s16)(s32)var_f3;
        }
    }
}
