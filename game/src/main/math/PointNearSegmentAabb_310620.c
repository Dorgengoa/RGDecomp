/* rgp:protos */
#define RGP_SELF_PointNearSegmentAabb_310620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

s32 PointNearSegmentAabb_310620(s32 pad, f32 *p, f32 *a, f32 *b, f32 r)
{
    s32 i;
    f32 hi;
    f32 lo;

    for (i = 0; i < 3; i++) {
        if (a[i] > b[i]) {
            lo = b[i];
            hi = a[i];
        } else {
            lo = a[i];
            hi = b[i];
        }
        if (!(p[i] <= hi)) {
            if (!((p[i] - hi) * (p[i] - hi) <= r)) {
                return 0;
            }
        } else if (p[i] < lo) {
            if (!((lo - p[i]) * (lo - p[i]) <= r)) {
                return 0;
            }
        }
    }
    return 1;
}
