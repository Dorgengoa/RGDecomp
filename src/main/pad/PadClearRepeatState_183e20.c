#include "types.h"

void PadClearRepeatState_183e20(u8 *p, u32 flags)
{
    u32 *q = (u32 *)(p + 0xC0);
    s32 i;
    u32 mask = 1;

    for (i = 0; i < 0x20; i++, mask <<= 1) {
        if ((flags & mask) != 0) {
            q[0] &= ~mask;
            q[1] &= ~mask;
            q[i + 2] = 0;
            q[i + 0x22] = 0;
            q[i + 0x42] = 0;
        }
    }
}
