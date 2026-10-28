/* rgp:protos */
#define RGP_SELF_MapMgrSlotsStepObjs_1e1540 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void MapMgrSlotsStepObjs_1e1540(u8 *p, f32 x)
{
    u8 *q;
    s32 i;

    q = p + 0x1928;
    for (i = 0; i < 4; i++) {
        MapAreaActiveBlocksStepObjs_1d9040(q, x);
        q += 0x1CC;
    }
}
