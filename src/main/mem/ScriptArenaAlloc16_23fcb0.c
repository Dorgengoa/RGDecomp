#include "types.h"

extern s32 D_00481EF0;
extern s32 D_00481EF4;

extern s32 AlignUp16_1cacd0(s32);

s32 ScriptArenaAlloc16_23fcb0(s32 size)
{
    s32 n;
    s32 p;

    if (D_00481EF0 == 0 || D_00481EF4 == 0) return 0;
    n = AlignUp16_1cacd0(size);
    if (n <= 0) return 0;
    p = AlignUp16_1cacd0(D_00481EF4);
    if (D_00481EF0 - p + 0x20000 < n) return 0;
    D_00481EF4 = p + n;
    return p;
}
