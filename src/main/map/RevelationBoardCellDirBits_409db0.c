#include "types.h"

s32 RevelationBoardCellDirBits_409db0(void *arg0, s32 arg1)
{
    s32 bit;
    s32 r;
    if ((arg1 < 0) || (arg1 > 7)) return 0;
    bit = 1 << arg1;
    r = 0;
    r |= (((u64)((s64)(*(s32*)((u8 *)arg0 + 0x0)) << 0x2B) >> 0x38) & bit) ? 1 : 0;
    r |= (((u64)((s64)(*(u16 *)((u8 *)arg0 + 0x2)) << 0x33) >> 0x38) & bit) ? 2 : 0;
    return r;
}
