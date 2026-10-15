#include "types.h"

extern s32 S16ArrayGetCount_1ce1b0(void *param_1);
extern s32 S16ArrayGetChecked_1ce170(void *param_1, s32 param_2);
extern void S16ArrayRemoveAt_1ce0a0(void *param_1, s32 param_2);

void LoaderQueueDropSeparator_1cd1e0(void *param_1)
{
    u8 *base = (u8 *)param_1;
    s32 r1;
    s32 r2;

    r1 = S16ArrayGetCount_1ce1b0(base + 0x20);
    r2 = S16ArrayGetChecked_1ce170(base + 0x20, r1 - 1);
    if ((s16)r2 == 0x3fff)
    {
        r1 = S16ArrayGetCount_1ce1b0(base + 0x20);
        S16ArrayRemoveAt_1ce0a0(base + 0x20, r1 - 1);
    }
}
