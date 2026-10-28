/* rgp:protos */
#define RGP_SELF_MapMgrAuxAreaRender_1e13a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MapMgrAuxAreaRender_1e13a0(s32 p0, s32 p1)
{
    DrawWorkHeapInit_2f6f10();
    {
        u8 v3C[4] = {0};

        *(s32 *)v3C = p0 + 0x2058;
        MapAreasDrawLit_1e1830(p0, p1, v3C, 1);
    }
    MapDrawGroupRange_1e1710(p0, 0, 0xF);
    DrawWorkHeapRelease_2f6ec0();
}
