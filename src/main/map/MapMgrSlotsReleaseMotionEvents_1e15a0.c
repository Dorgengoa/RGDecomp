#include "types.h"

typedef struct S { u8 b[0x1CC]; } S;

extern void MapAreaActiveBlocksReleaseMotionEvents_1d90d0(S *);

void MapMgrSlotsReleaseMotionEvents_1e15a0(void *o)
{
    S *p = (S *)((u8 *)o + 0x1928);
    s32 i;

    for (i = 0; i < 0x4; i++, p++) {
        MapAreaActiveBlocksReleaseMotionEvents_1d90d0(p);
    }
}
