#include "types.h"

extern s32 *MemStackNew_14e230(s32);

void FrameAllocExtMaybe_149390(u8 *p0)
{
    s32 *q;

    if (*(s32 **)(p0 + 0x20) == 0) {
        q = MemStackNew_14e230(0x20);
        if (q != 0) {
            *q = 0;
        }
        *(s32 **)(p0 + 0x20) = q;
    }
}
