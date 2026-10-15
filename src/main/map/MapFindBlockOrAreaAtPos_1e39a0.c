#include "types.h"
extern void MapFindSmallestBlockAtPos_1e3b50(s32, s32, s32 *, s32);
s32 MapFindBlockOrAreaAtPos_1e39a0(s32 p0, s32 p1)
{
    s32 v;
    MapFindSmallestBlockAtPos_1e3b50(p0, 0, &v, p1);
    return v;
}
