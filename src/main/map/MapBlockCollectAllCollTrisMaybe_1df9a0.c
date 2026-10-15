#include "types.h"

extern s32 MapBlockCollectEntryCollTrisMaybe_1dfa20(void);
extern s32 MapDataCollectCollTrisMaybe_1e6c80(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 MapBlockCollectAllCollTrisMaybe_1df9a0(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 n;

    n = 0;
    n += MapBlockCollectEntryCollTrisMaybe_1dfa20();
    return n + MapDataCollectCollTrisMaybe_1e6c80(arg0, arg1 + n * 0x60, arg2 - n, arg3);
}
