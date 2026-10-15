#include "types.h"

typedef struct {
    f32 x, y, z;
} V3;

typedef struct {
    f32 f;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 i0;
    s32 i1;
    u8 pad[8];
} P;

extern void SplineEvalHermiteScalar_14b4c0(f32 *, V3 *, V3 *, f32);
extern f32 AnimKeyFindSpan_155ff0(P *);

void AnimKeyEvalScalarHermite_154710(f32 *arg0, u8 *arg1, f32 fparg0)
{
    P p;
    f32 r;
    V3 *tbl;

    p.a = arg1[2];
    p.b = *(s32 *)(arg1 + 0x8);
    p.d = *(u16 *)(arg1 + 0x6);
    p.f = fparg0;
    p.c = *(s16 *)(arg1 + 0x4);
    r = AnimKeyFindSpan_155ff0(&p);
    if (arg1[1] == 0x20) {
        tbl = *(V3 **)(arg1 + 0xC);
        if (r == 0.0f) {
            *arg0 = tbl[p.i0].x;
        } else {
            SplineEvalHermiteScalar_14b4c0(arg0, &tbl[p.i0], &tbl[p.i1], r);
        }
    }
}
