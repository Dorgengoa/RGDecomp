#include "types.h"

extern s32 D_004829B0;
extern s32 D_004829B4;

extern s32 AlignUp4_1cace0(s32);

s32 MovCfgScratchAllocAlign4_311f40(s32 size)
{
    s32 n;
    s32 p;

    if (D_004829B0 == 0 || D_004829B4 == 0) return 0;
    n = AlignUp4_1cace0(size);
    if (n <= 0) return 0;
    p = AlignUp4_1cace0(D_004829B4);
    if (D_004829B0 - p + 0x10000 < n) return 0;
    D_004829B4 = p + n;
    return p;
}
