#include "types.h"

extern s32 D_004829B0;
extern s32 D_004829B4;

extern s32 AlignUp16_1cacd0(s32);

s32 MovCfgScratchAllocAlign16_311eb0(s32 size)
{
    s32 n;
    s32 p;

    if (D_004829B0 == 0 || D_004829B4 == 0) return 0;
    n = AlignUp16_1cacd0(size);
    if (n <= 0) return 0;
    p = AlignUp16_1cacd0(D_004829B4);
    if (D_004829B0 - p + 0x10000 < n) return 0;
    D_004829B4 = p + n;
    return p;
}
