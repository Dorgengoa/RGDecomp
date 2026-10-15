#pragma optimization_level 3
#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s32 m10;
} Obj;

extern u8 D_0044A3C0[];
extern f32 D_0047D24C;
extern const f32 D_0047D254 __attribute__((section(".sdata")));
extern f32 D_0047D258;
extern f32 D_0047D25C;
extern f32 D_0047D260;

static inline s32 Lt(f32 a, f32 b) { return a < b; }

f32 AmixerBlendCurveEvalMaybe_170180(Obj *arg0, f32 x);
void MtxMulVec4_13c900(f32 *, void *, f32 *);

f32 AmixerBlendCurveEvalMaybe_170180(Obj *arg0, f32 x)
{
    f32 c[4];
    f32 v[4];
    f32 w[4];
    f32 lo;
    f32 hi;
    f32 t;

    if (x > 0.9999f) {
        return 1.0f;
    }
    if (x < 0.0001f) {
        return 0.0f;
    }
    if (arg0->m10 != 3) {
        return x;
    }
    v[0] = 0.0f;
    v[1] = 0.3333f;
    v[2] = 0.6666f;
    w[0] = 0.0f;
    w[1] = 0.0f;
    w[2] = 1.0f;
    v[3] = 1.0f;
    w[3] = 1.0f;
    MtxMulVec4_13c900(c, D_0044A3C0, v);
    lo = 0.0f;
    if (!(x <= lo)) {
        hi = 1.0f;
        if (x < hi) {
            f32 c0 = c[0], c1 = c[1], c2 = c[2], c3 = c[3];
            do {
                t = (lo + hi) / 2.0f;
                { s32 b = c3 + t * (c2 + t * (c1 + c0 * t)) < x; if ((b ^ 1) == 0) lo = t; else hi = t; }
            } while (((hi - lo < 0.001f) ^ 1));
            x = 0.5f * (lo + hi);
        }
    }
    MtxMulVec4_13c900(c, D_0044A3C0, w);
    return c[3] + x * (c[2] + x * (c[1] + c[0] * x));
}
