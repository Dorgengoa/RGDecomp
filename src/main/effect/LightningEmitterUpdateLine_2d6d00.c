/* main s27m: CLOSED -- the 0x20 bound is an s16 (lh) and the 0x2C field an s8 (lb). */
#include "types.h"

extern void *LightningMgrFindFreeBolt_2d64f0(s32);
extern void LightningBoltBuild_2d6960(void *, void *, void *, f32);

void LightningEmitterUpdateLine_2d6d00(s32 arg0, s32 arg1)
{
    s16 temp_3;
    void *temp_17;
    s32 var_16;
    void *temp_2;
    u8 *temp_4;

    temp_4 = (u8 *)arg0 + (arg1 * 0x30);
    temp_17 = temp_4 + 0x10;
    if ((*(s16 *)(temp_4 + 0x38) % 3) == 0) {
        var_16 = 0;
        while (var_16 < *(s16 *)((u8 *)temp_17 + 0x20)) {
            temp_2 = LightningMgrFindFreeBolt_2d64f0(arg0);
            if (temp_2 != NULL) {
                LightningBoltBuild_2d6960(temp_2, temp_17, (u8 *)temp_17 + 0x10, *(f32 *)((u8 *)temp_17 + 0x24));
                *(s8 *)((u8 *)temp_2 + 0xC0) = *(s8 *)((u8 *)temp_17 + 0x2C);
            }
            var_16 += 1;
        }
    }
    temp_3 = *(s16 *)((u8 *)temp_17 + 0x28) - 1;
    *(s16 *)((u8 *)temp_17 + 0x28) = temp_3;
    if (temp_3 <= 0) {
        *(s16 *)((u8 *)temp_17 + 0x2A) = 0;
    }
}
