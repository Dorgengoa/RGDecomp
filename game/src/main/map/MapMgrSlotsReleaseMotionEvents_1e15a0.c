/* rgp:protos */
#define RGP_SELF_MapMgrSlotsReleaseMotionEvents_1e15a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { u8 b[0x1CC]; } S;

/*rgp*/

void MapMgrSlotsReleaseMotionEvents_1e15a0(void *o)
{
    S *p = (S *)((u8 *)o + 0x1928);
    s32 i;

    for (i = 0; i < 0x4; i++, p++) {
        MapAreaActiveBlocksReleaseMotionEvents_1d90d0(p);
    }
}
