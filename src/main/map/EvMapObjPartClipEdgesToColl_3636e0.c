#include "types.h"
#include "vec.h"
#pragma opt_common_subs off
#pragma opt_propagation off
#pragma opt_loop_invariants off

typedef struct Vtx {
    Vec4 pos;
    u8 pad10[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad2C[0x14];
} Vtx;

typedef struct Tri {
    Vtx v[3];
    u8 padC0[0x74];
    f32 f134;
} Tri;

extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vtx *, Vec4 *);
extern s32 CollSegmentVsPlanesMaybe_364520(s32, s32, Vtx *, Vtx *, Vec4 *, Vec4 *, f32 *);
extern f32 D_0047D244;

s32 EvMapObjPartClipEdgesToColl_3636e0(Tri *self, s32 arg1, s32 arg2)
{
    f32 t;
    Vec4 hit;
    Vec4 n;
    Vec4 tmp;
    s32 i;
    s32 j;
    Vtx *pi;
    Vtx *d;

    i = 0;
    do {
        j = (i + 1) % 3;
        t = self->f134;
        pi = &self->v[i];
        if (CollSegmentVsPlanesMaybe_364520(arg1, arg2, pi, &self->v[j], &hit, &n, &t) == 1) {
            { Vec4 *q_ = &n; VecNormalize_13bd90(q_, q_); }
            VecScale_13be00(&tmp, &n, D_0047D244 + self->f134);
            { Vec4 *h_ = &hit; VecAdd_13be20(h_, h_, &tmp); }
            VecSub_13be40(&tmp, pi, &hit);
            if (Vu0InnerProduct_13bd60(&tmp, &n) < 0.0f) {
                d = &self->v[i];
                d->pos = hit;
                d->x = hit.x;
                d->y = hit.y;
                d->z = hit.z;
            } else {
                d = &self->v[j];
                d->pos = hit;
                d->x = hit.x;
                d->y = hit.y;
                d->z = hit.z;
            }
        }
        i++;
    } while (i < 3);
    return 0;
}
