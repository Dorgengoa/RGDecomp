#include "types.h"

extern s32 MapDataIsLoaded_1e79d0(void *);
extern void **MapAreaGetActiveBlockList_1dc0c0(void *);
extern s32 MapAreaGetActiveBlockCount_1dc0b0(void *);
extern void MapBlockStepObjs_1de980(void *, f32);

void MapAreaActiveBlocksStepObjs_1d9040(void *p, f32 t)
{
    void **arr;
    s32 n;
    s32 i;

    if (MapDataIsLoaded_1e79d0(p) == 0) return;
    arr = MapAreaGetActiveBlockList_1dc0c0(p);
    if (arr == 0) return;
    n = MapAreaGetActiveBlockCount_1dc0b0(p);
    i = 0;
    while (i < n) {
        MapBlockStepObjs_1de980(*arr, t);
        i++;
        arr++;
    }
}
