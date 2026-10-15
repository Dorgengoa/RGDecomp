#include "types.h"

extern "C" s32 MapAreaGetBoxCount_1dcdd0(s32);
extern "C" s32 MapAreaGetBoxes_1dcde0(s32);
extern "C" s32 MapBoxGetNumMaybe_1ddf00(s32);
extern "C" s32 AreaBoxContainsPointXZ_1e9310(s32, f32 *, f32);
extern "C" f32 AreaBoxGetBottomY_1e9890(s32);
extern "C" f32 AreaBoxGetTopY_1e98a0(s32);
extern "C" f32 AreaBoxGetVolume_1e98b0(s32);
extern "C" f32 D_0047D1EC;
extern "C" f32 D_0047D5D0;

extern "C" s32 MapAreaFindSmallestBoxAt_1db350(s32 arg0, f32 *arg1, f32 f)
{
    f32 *q1;
    s32 p;
    s32 best;
    u8 found;
    s32 i;
    f32 bestv;
    f32 v;

    q1 = arg1;
    p = MapAreaGetBoxes_1dcde0(arg0);
    if (p == 0) {
        return 0;
    }
    arg0 = MapAreaGetBoxCount_1dcdd0(arg0);
    if (arg0 <= 0) {
        return 0;
    }
    if (f < D_0047D5D0) {
        f = D_0047D5D0;
    }
    best = 0;
    found = 0;
    bestv = D_0047D1EC;
    for (i = 0; i < arg0; i++, p += 0x50) {
        if (MapBoxGetNumMaybe_1ddf00(p) < 0) {
            continue;
        }
        if (AreaBoxContainsPointXZ_1e9310(p, q1, f) == 0) {
            continue;
        }
        v = AreaBoxGetVolume_1e98b0(p);
        if (found) {
            if (bestv <= v) {
                continue;
            }
            if (q1[1] < AreaBoxGetBottomY_1e9890(p)) {
                continue;
            }
            if (AreaBoxGetTopY_1e98a0(p) < q1[1]) {
                continue;
            }
        } else if (AreaBoxGetBottomY_1e9890(p) <= q1[1] && q1[1] <= AreaBoxGetTopY_1e98a0(p)) {
            found = 1;
        } else if (bestv <= v) {
            continue;
        }
        bestv = v;
        best = p;
    }
    return best;
}
