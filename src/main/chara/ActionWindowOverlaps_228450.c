#include "types.h"

s32 ActionWindowOverlaps_228450(f32 *p, f32 v, f32 w)
{
    f32 a;
    f32 b;
    s32 r;

    a = p[0];
    if (0.0f <= a) {
        if (v + w < a) return 0;
    }
    b = p[1];
    if (!(1.0f < b)) {
        if (v > b) return 0;
    }
    r = 1;
    if (a > b) {
        r = 0;
    }
    return r;
}
