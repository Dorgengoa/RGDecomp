#include "types.h"

struct S197 {
    u8   pad000[8];
    s32  f08;
    s32  f0C;
    s16 *f10;
    u8   pad014[8];
    f32 *f1C;
};

extern "C" void EffCurveAddKey_197610(S197 *p, s32 v, f32 f)
{
    s32 i;
    u8 ok;

    i = p->f0C;
    p->f0C = i + 1;
    ok = (i >= 0) && (i < p->f08);
    if (ok != 0) {
        p->f10[i] = (s16)v;
        p->f1C[i] = f;
    }
}
