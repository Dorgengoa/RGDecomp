#include "types.h"

typedef struct { f32 x, y, z; } FV3;
typedef struct { FV3 r[3]; } M33;

typedef struct T154cb0 {
    u8  f00;
    u8  f01;
    u8  f02;
    u8  f03;
    s16 f04;
    u16 f06;
    s32 f08;
    M33 *f0C;
} T154cb0;

typedef struct S154cb0 {
    f32 f30;
    s32 f34;
    s32 f38;
    s32 f3C;
    s32 f40;
    s32 f44;
    s32 f48;
    s32 f4C;
    s32 f50;
    s32 f54;
    s32 f58;
    s32 f5C;
} S154cb0;

extern f32 AnimKeyFindSpan_155ff0(S154cb0 *);
extern void SplineEvalHermiteVec3_14b5c0(f32 *, FV3 *, FV3 *, f32);

void AnimKeyEvalVec3Hermite_154cb0(f32 *out, T154cb0 *obj, f32 t)
{
    S154cb0 loc;
    f32 r;
    M33 *base;
    FV3 *e;

    loc.f34 = obj->f02;
    loc.f38 = obj->f08;
    loc.f40 = obj->f06;
    loc.f30 = t;
    loc.f3C = obj->f04;
    r = AnimKeyFindSpan_155ff0(&loc);
    if (obj->f01 == 0x20) {
        base = obj->f0C;
        if (0.0f == r) {
            e = base[loc.f44].r;
            out[0] = e->x;
            out[1] = e->y;
            out[2] = e->z;
        } else {
            SplineEvalHermiteVec3_14b5c0(out, base[loc.f44].r, base[loc.f48].r, r);
        }
    }
}
