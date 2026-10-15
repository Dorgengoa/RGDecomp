#include "types.h"

extern s32 MapAreaGetPartTableCount_1dcdf0(s32);
extern s32 MapAreaGetPartTables_1dce00(s32);
extern s32 MapPartTableFindSmallestBlockAt_1de090(s32, s32, f32);
extern f32 MapBlockGetBoxVolume_1dfe80(s32);
extern s32 MapDataIsLoaded_1e79d0(s32);
extern s32 MapDataIsEnabled_1e7c20(void);
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
    if (MapDataIsEnabled_1e7c20() == 0) {
        return 0;
    }
    if (MapDataIsLoaded_1e79d0(arg0) == 0) {
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
