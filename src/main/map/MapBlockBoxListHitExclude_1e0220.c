#include "types.h"

extern s32 AreaBoxContainsPoint_1e93c0(s32, s32, f32);

s32 MapBlockBoxListHitExclude_1e0220(void *self, s32 arg1, f32 f0)
{
    s32 p;
    s32 i;

    p = *(s32 *)((u8 *)self + 0xC);
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < *(s16 *)((u8 *)self + 0x12); i++, p += 0x4C) {
        if (AreaBoxContainsPoint_1e93c0(p, arg1, f0) != 0) {
            return 1;
        }
    }
    return 0;
}
