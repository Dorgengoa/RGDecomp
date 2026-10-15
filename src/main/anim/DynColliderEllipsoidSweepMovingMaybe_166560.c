#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec166;

typedef struct {
    u8 pad0[0x10];
    u8 m10[0x40];
    u8 m50[0x80];
    u8 mD0[0x50];
    Vec166 ofs;
    Vec166 scl;
} Obj166;

void MtxMulPoint_13c890(Vec166 *, void *, Vec166 *);
void VecSub_13be40(Vec166 *, Vec166 *, Vec166 *);
void VecAdd_13be20(Vec166 *, Vec166 *, Vec166 *);
void VecScale_13be00(Vec166 *, Vec166 *, f32);
s32 SegmentSphereIntersect_13da60(Vec166 *, Vec166 *, Vec166 *, f32);
f32 VecDistance_13d3d0(Vec166 *, Vec166 *);

s32 DynColliderEllipsoidSweepMovingMaybe_166560(Obj166 *self, Vec166 *a, Vec166 *b)
{
    Vec166 p[3];
    Vec166 q[3];
    Vec166 hit[2];
    Vec166 dir;
    Vec166 tmp;
    Vec166 v90;
    Vec166 v80;
    s32 found;
    s32 i;
    f32 best;
    f32 d;
    Vec166 *qp;

    MtxMulPoint_13c890(&p[0], self->m50, a);
    VecSub_13be40(&p[0], &p[0], &self->ofs);
    p[0].x /= self->scl.x;
    p[0].y /= self->scl.y;
    p[0].z /= self->scl.z;
    MtxMulPoint_13c890(&p[1], self->m50, b);
    VecSub_13be40(&p[1], &p[1], &self->ofs);
    p[1].x /= self->scl.x;
    p[1].y /= self->scl.y;
    p[1].z /= self->scl.z;
    MtxMulPoint_13c890(&q[0], self->mD0, a);
    VecSub_13be40(&q[0], &q[0], &self->ofs);
    q[0].x /= self->scl.x;
    q[0].y /= self->scl.y;
    q[0].z /= self->scl.z;
    MtxMulPoint_13c890(&q[1], self->mD0, b);
    VecSub_13be40(&q[1], &q[1], &self->ofs);
    q[1].x /= self->scl.x;
    q[1].y /= self->scl.y;
    q[1].z /= self->scl.z;
    VecAdd_13be20(&p[2], &p[0], &p[1]);
    VecAdd_13be20(&q[2], &q[0], &q[1]);
    VecScale_13be00(&p[2], &p[2], 0.5f);
    VecScale_13be00(&q[2], &q[2], 0.5f);
    found = 0;
    best = 0.0f;
    for (i = 0; i < 3; i++) {
        qp = &q[i];
        if (SegmentSphereIntersect_13da60(qp, &p[i], hit, 1.0f) != 0) {
            d = VecDistance_13d3d0(hit, qp);
            if (found == 0 || !(best <= d)) {
                best = d;
                VecSub_13be40(&dir, hit, qp);
            }
            found = 1;
        }
    }
    if (found != 0) {
    VecSub_13be40(&tmp, &p[0], &q[0]);
    VecScale_13be00(&tmp, &tmp, best);
    VecAdd_13be20(a, &q[0], &tmp);
    VecSub_13be40(&tmp, &p[1], &q[1]);
    VecScale_13be00(&tmp, &tmp, best);
    VecAdd_13be20(b, &q[1], &tmp);
    v90.x = a->x * self->scl.x;
    v90.y = a->y * self->scl.y;
    v90.z = a->z * self->scl.z;
    VecAdd_13be20(&v90, &v90, &self->ofs);
    MtxMulPoint_13c890(a, self->m10, &v90);
    v80.x = b->x * self->scl.x;
    v80.y = b->y * self->scl.y;
    v80.z = b->z * self->scl.z;
    VecAdd_13be20(&v80, &v80, &self->ofs);
    MtxMulPoint_13c890(b, self->m10, &v80);
    }
    return found;
}
