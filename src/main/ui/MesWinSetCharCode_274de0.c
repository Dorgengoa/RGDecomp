#include "types.h"

void MesWinSetCharCode_274de0(void *p, s32 i, s16 v)
{
    if (i < 0 || i >= 0x300) return;
    *(s16 *)((u8 *)(i * 8) + (u32)p + 0xC4) = v;
}
