#include "types.h"

extern s32 D_00481EF0;
extern s32 D_00481EF4;

extern s32 AlignUp4_1cace0(s32);

s32 StrArenaAlloc_23fd40(s32 size)
{
    s32 n;
    s32 p;

    if (D_00481EF0 == 0 || D_00481EF4 == 0) return 0;
    n = AlignUp4_1cace0(size);
    if (n <= 0) return 0;
    p = AlignUp4_1cace0(D_00481EF4);
    if (D_00481EF0 - p + 0x20000 < n) return 0;
    D_00481EF4 = p + n;
    return p;
}
