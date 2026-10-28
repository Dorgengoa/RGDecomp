/* rgp:protos */
#define RGP_SELF_MapAreaActiveBlocksShowObjs_1d8fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapAreaActiveBlocksShowObjs_1d8fc0(void *o)
{
    void **p;
    s32    n;
    s32    i;

    if (((unsigned char)MapDataIsLoaded_1e79d0(o)) == 0) return;
    p = ((void **)MapAreaGetActiveBlockList_1dc0c0(o));
    if (p == 0) return;
    n = ((short)MapAreaGetActiveBlockCount_1dc0b0(o));
    for (i = 0; i < n; i++, p++) {
        MapBlockShowObjs_1de910(*p);
    }
}
