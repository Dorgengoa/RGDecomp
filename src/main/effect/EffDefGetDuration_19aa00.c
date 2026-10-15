#include "types.h"

f32 EffObjGetDuration_1a96e0(s32);
static inline f32 inner(u8 *e)
{
    f32 m;
    f32 f;
    u8 *n;

    m = 0.0f;
    for (n = *(u8 **)(e + 0x44); n != 0; n = *(u8 **)n) {
        f = EffObjGetDuration_1a96e0(*(s32 *)(n + 4));
        if (f < 0.0f) {
            return f;
        }
        if (!(f <= m)) {
            m = f;
        }
    }
    return m;
}
f32 EffDefGetDuration_19aa00(u8 *o)
{
    u8 ***p;
    f32 best;
    f32 f;
    s32 i;
    u8 *e;

    p = *(u8 ****)(o + 0xA0);
    best = 0.0f;
    for (i = 0; i < *(s32 *)(o + 0x9C); i++, p++) {
        e = *(u8 **)((u8 *)*p + 0xC);
        if (e != 0) {
            f = inner(e);
            if (f < 0.0f) {
                return f;
            }
            if (!(f <= best)) {
                best = f;
            }
        }
    }
    return best;
}
