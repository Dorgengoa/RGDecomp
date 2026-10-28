/* rgp:protos */
#define RGP_SELF_MapAreaActiveBlocksStepObjs_1d9040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapAreaActiveBlocksStepObjs_1d9040(void *p, f32 t)
{
    void **arr;
    s32 n;
    s32 i;

    if (((unsigned char)MapDataIsLoaded_1e79d0(p)) == 0) return;
    arr = ((void **)MapAreaGetActiveBlockList_1dc0c0(p));
    if (arr == 0) return;
    n = ((short)MapAreaGetActiveBlockCount_1dc0b0(p));
    i = 0;
    while (i < n) {
        MapBlockStepObjs_1de980(*arr, t);
        i++;
        arr++;
    }
}
