#include "types.h"

extern void VecAddScaled_13bdd0(void *arg0, void *arg1, f32 arg2);

void EffAttachIntegrateTexUv_1978b0(void *arg0, void *arg1, f32 fparg0)
{
    f32 *temp_4;
    f32 temp_f1;
    f32 temp_f1_2;
    s32 temp_3;
    void *temp_16;
    s32 i;
    u8 *temp_5;

    temp_16 = (u8 *)(*(void **)((u8 *)arg1 + 0xB4)) + (*(s32 *)((u8 *)arg0 + 0x4) * 0x10);
    VecAddScaled_13bdd0((u8 *)arg1 + 0x50, temp_16, fparg0);
    VecAddScaled_13bdd0(temp_16, (u8 *)temp_16 + 0x10, fparg0);
    i = 0;
    do {
        temp_3 = i * 4;
        temp_5 = (u8 *)arg1 + temp_3;
        temp_4 = (f32 *)((u8 *)temp_16 + temp_3);
        temp_f1 = *(f32 *)(temp_5 + 0x50);
        i += 1;
        *(f32 *)(temp_5 + 0x50) = temp_f1 - (f32)(s32)temp_f1;
        temp_f1_2 = *temp_4;
        *temp_4 = temp_f1_2 - (f32)(s32)temp_f1_2;
    } while (i < 2);
}
