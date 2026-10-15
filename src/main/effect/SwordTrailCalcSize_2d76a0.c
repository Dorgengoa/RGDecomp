#include "types.h"

extern s32 AlignUp16_1cacd0(s32);

u32 SwordTrailCalcSize_2d76a0(s32 a0, s32 n)
{
    return (u32)AlignUp16_1cacd0(n * 48) >> 4;
}
