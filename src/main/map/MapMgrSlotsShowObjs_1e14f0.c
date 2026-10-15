#include "types.h"

typedef struct S { u8 b[0x1CC]; } S;

extern void MapAreaActiveBlocksShowObjs_1d8fc0(S *);

void MapMgrSlotsShowObjs_1e14f0(void *o)
{
    S *p = (S *)((u8 *)o + 0x1928);
    s32 i;

    for (i = 0; i < 0x4; i++) {
        MapAreaActiveBlocksShowObjs_1d8fc0(p);
        p++;
    }
}
