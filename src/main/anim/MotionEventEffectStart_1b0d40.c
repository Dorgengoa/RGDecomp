#pragma opt_common_subs off
#include "types.h"
#pragma opt_propagation off


extern void *HandleTableGetDeref_1a0ca0(s32 arg0, s32 arg1);
extern void MotionEventEffectSpawn_1b0e90(s32 *arg0, void *arg1, void *arg2);

s32 MotionEventEffectStart_1b0d40(void *arg0, void *arg1)
{
    s32 sp2C;
    void *temp_2;
    void *temp_5;
    s32 b;

    temp_5 = *(void **)((u8 *)arg0 + 0x4);
    if (temp_5 == NULL) {
        return 0;
    }
    b = !(*(s32 *)((u8 *)arg1 + 0x30) != 0);
    if (b)
    {
        MotionEventEffectSpawn_1b0e90(&sp2C, temp_5, arg1);
        *(s32 *)((u8 *)arg1 + 0x30) = sp2C;
    } else {
        temp_2 = HandleTableGetDeref_1a0ca0(*(s32 *)((u8 *)temp_5 + 0x53C), *(s32 *)((u8 *)arg1 + 0x30));
        if (temp_2 != NULL) {
            *(u8 *)((u8 *)temp_2 + 0xF0) = *(u8 *)((u8 *)arg1 + 0x34);
            *(u8 *)((u8 *)temp_2 + 0xF1) = *(u8 *)((u8 *)arg1 + 0x35);
        }
    }
    return 1;
}

