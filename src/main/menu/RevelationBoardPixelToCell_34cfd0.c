#include "types.h"

#pragma divbyzerocheck on

void RevelationBoardPixelToCell_34cfd0(s32 unused, s32 *ox, s32 *oy, s32 x1, s32 y1, s32 x0, s32 y0)
{
    *ox = (x1 - x0) / 42;
    *oy = (y1 - y0) / 46;
}
