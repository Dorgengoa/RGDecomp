#include "types.h"
void ScreenMarkerSetFlag_31bf70(u8 *base, s32 i, u8 v)
{
    if (i >= 0x20) i = 0x1F;
    *(u8 *)(i + (s32)base + 0x80) = v;
}
