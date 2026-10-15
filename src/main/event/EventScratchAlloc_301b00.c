#include "types.h"

extern s32 D_00482898;
extern s32 D_0048289C;

extern s32 AlignUp16_1cacd0(s32);

s32 EventScratchAlloc_301b00(s32 size)
{
    s32 n;
    s32 p;

    if (D_00482898 == 0 || D_0048289C == 0) return 0;
    n = AlignUp16_1cacd0(size);
    if (n <= 0) return 0;
    p = AlignUp16_1cacd0(D_0048289C);
    if (D_00482898 - p + 0x10000 < n) return 0;
    D_0048289C = p + n;
    return p;
}
