#include "types.h"

extern s32 AabbContainsPoint_13e130(void *, void *, void *);

s32 CollShapeContainsPoint_16d440(u8 *a, void *b)
{
    return AabbContainsPoint_13e130(b, a + 0x10, a + 0x20) != 0;
}
