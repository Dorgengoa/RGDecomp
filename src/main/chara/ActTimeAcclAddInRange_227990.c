#include "types.h"

void ActTimeAcclAddInRange_227990(f32 *p, f32 *out, f32 a, f32 len)
{
    f32 end;
    f32 x;
    u8 r;

    end = a + len;
    if (a < 0.0f) a = 0.0f;
    x = p[0];
    r = 0;
    if (a > x) goto done;
    if (x >= end) goto done;
    r = 1;
done:
    if (r) {
        out[0] = out[0] + p[1];
        out[1] = out[1] + p[2];
        out[2] = out[2] + p[3];
    }
}
