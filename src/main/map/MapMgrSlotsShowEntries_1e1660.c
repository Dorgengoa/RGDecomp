#include "types.h"

typedef struct S { u8 b[0x1CC]; } S;

extern void MapAreaActiveBlocksShowEntries_1d9200(S *);

void MapMgrSlotsShowEntries_1e1660(void *o)
{
    S *p = (S *)((u8 *)o + 0x1928);
    s32 i = 0;

    do {
        MapAreaActiveBlocksShowEntries_1d9200(p);
        i++;
        p++;
    } while (i < 0x4);
}
