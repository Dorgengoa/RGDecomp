/* rgp:protos */
#define RGP_SELF_EventCollectCollTris_1ff300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EventCollectCollTris_1ff300(u8 *p, s32 n, void *c, void *d)
{
    s32 k;
    void *y;

    if (p == 0 || n <= 0) {
        return 0;
    }
    k = 0;
    k = k + TreasureBoxPoolCollectCollTris_338a30(GetTreasureBoxPool_3389b0(), p, n, c);
    y = GetEventObjMgr_2d1960();
    return k + EventObjMgrCollectCollTrisNone_2e7bb0();
}
