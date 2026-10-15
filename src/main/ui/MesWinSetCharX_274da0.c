#include "types.h"

void MesWinSetCharX_274da0(void *p, s32 i, s16 v)
{
    if (i < 0 || i >= 0x300) return;
    *(s16 *)((u8 *)(i * 8) + (u32)p + 0xC6) = v;
}
