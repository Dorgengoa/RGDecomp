#include "types.h"
#pragma divbyzerocheck on
extern s32 GroupTableFindEntry_422950(s32, s16, s16);

s32 GroupTableFindEntryByCode_422910(s32 p0, s32 p1)
{
    return GroupTableFindEntry_422950(p0, (s16)(p1 / 10), (s16)(p1 % 10));
}
