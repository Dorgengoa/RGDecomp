#include "types.h"

f32 FloatInRange_1c9280(f32 a, f32 b, f32 c)
{
    u32 t;

    if (b <= a) {
        t = 1;
    } else {
        t = 0;
    }
    if (t != 0) {
        t = 1;
        if (a > c) {
            t = 0;
        }
    }
    return (f32)t;
}
