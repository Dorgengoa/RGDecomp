/* rgp:protos */
#define RGP_SELF_EventCollectCollPolys_1ff3b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EventCollectCollPolys_1ff3b0(u8 *p, s32 n, void *c, void *d)
{
    s32 k;
    void *y;

    if (p == 0 || n <= 0) {
        return 0;
    }
    k = 0;
    k = k + TreasureBoxPoolCollectCollPolys_338af0(GetTreasureBoxPool_3389b0(), p, n, c);
    y = GetEventObjMgr_2d1960();
    return k + EventObjMgrCollectCollPolys_2e7bc0(y, p + k * 0x60, n - k, c, d);
}
