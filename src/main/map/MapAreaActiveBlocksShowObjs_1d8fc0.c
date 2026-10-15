#include "types.h"

extern s32    MapDataIsLoaded_1e79d0(void *o);
extern void **MapAreaGetActiveBlockList_1dc0c0(void *o);
extern s32    MapAreaGetActiveBlockCount_1dc0b0(void *o);
extern void   MapBlockShowObjs_1de910(void *e);

void MapAreaActiveBlocksShowObjs_1d8fc0(void *o)
{
    void **p;
    s32    n;
    s32    i;

    if (MapDataIsLoaded_1e79d0(o) == 0) return;
    p = MapAreaGetActiveBlockList_1dc0c0(o);
    if (p == 0) return;
    n = MapAreaGetActiveBlockCount_1dc0b0(o);
    for (i = 0; i < n; i++, p++) {
        MapBlockShowObjs_1de910(*p);
    }
}
