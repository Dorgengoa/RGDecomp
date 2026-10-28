/* rgp:protos */
#define RGP_SELF_MapAreaFindSmallestBlockAt_1db4f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D1EC;
extern f32 D_0047D240;

s32 MapAreaFindSmallestBlockAt_1db4f0(s32 arg0, s32 arg1, f32 f)
{
    s32 a1;
    s32 p;
    s32 res;
    s32 i;
    s32 e;
    s32 n;
    f32 best;
    f32 d;

    a1 = arg1;
    if (((unsigned char)MapDataIsEnabled_1e7c20((void *)arg0)) == 0) {
        return 0;
    }
    if (((unsigned char)MapDataIsLoaded_1e79d0(arg0)) == 0) {
        return 0;
    }
    p = MapAreaGetPartTables_1dce00(arg0);
    if (p == 0) {
        return 0;
    }
    n = MapAreaGetPartTableCount_1dcdf0(arg0);
    if (n <= 0) {
        return 0;
    }
    if (f < D_0047D240) {
        f = D_0047D240;
    }
    res = 0;
    best = D_0047D1EC;
    for (i = 0; i < n; i++, p += 0x3C) {
        e = MapPartTableFindSmallestBlockAt_1de090(p, a1, f);
        if (e == 0) {
            continue;
        }
        d = MapBlockGetBoxVolume_1dfe80(e);
        if (best <= d) {
            continue;
        }
        best = d;
        res = e;
    }
    return res;
}
