#include "types.h"

extern void EffectEntryNodeSetParamFloat_2d9f10(void *, void *, s32, f32);

void EffectEntriesSetParamFloat_2ddda0(u8 *arr, void *arg1, s32 arg2, f32 f0)
{
    s32 i;
    u8 *e;

    i = 0;
    do {
        e = arr + i * 0xE0;
        if (*(s16 *)(e + 0xE) == *(s32 *)((u8 *)arg1 + 8)) {
            EffectEntryNodeSetParamFloat_2d9f10(e, arg1, arg2, f0);
        }
        i += 1;
    } while (i < 0x30);
}
