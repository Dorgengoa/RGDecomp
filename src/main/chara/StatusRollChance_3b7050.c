#include "types.h"

extern f32 RandFloat_13c010(void);

s32 StatusRollChance_3b7050(s32 unused0, s32 arg1, s32 arg2)
{
    if (arg2 < -0x63) {
        return 1;
    }
    if (arg2 >= 0x64) {
        return 0;
    }
    if (arg1 <= 0) {
        return 0;
    }
    if (arg1 >= 0x64) {
        return 1;
    }
    return (s32)(100.0f * RandFloat_13c010()) < (s32)((f32)arg1 * (1.0f - ((f32)arg2 / 100.0f)));
}
