#include "types.h"

typedef struct Vec { f32 x, y, z, w; } Vec;

extern void MtxMulPoint_13c890(Vec *dst, void *mtx, Vec *src);
extern void VecSub_13be40(Vec *dst, Vec *a, Vec *b);
extern void VecAdd_13be20(Vec *dst, Vec *a, Vec *b);
extern void VecScale_13be00(Vec *dst, Vec *a, f32 s);
extern s32 SegmentSphereIntersect_13da60(Vec *a, Vec *b, Vec *out, f32 r);
extern f32 VecDistance_13d3d0(Vec *a, Vec *b);

typedef struct {
    u8 pad0[0x10];
    u8 mtx10[0x40];
    u8 mtx50[0xD0];
    Vec ofs;
    f32 sx;
    f32 sy;
    f32 sz;
} T1661c0;

s32 DynColliderEllipsoidSweepSegmentMaybe_1661c0(T1661c0 *self, Vec *arg1, Vec *arg2, Vec *arg3, Vec *arg4) {
    Vec b[3];
    Vec a[3];
    Vec hit[2];
    Vec diff;
    Vec d;
    Vec t90;
    Vec t80;
    s32 found;
    s32 i;
    f32 best;
    Vec *p;

    MtxMulPoint_13c890(&b[0], self->mtx50, arg3);
    VecSub_13be40(&b[0], &b[0], &self->ofs);
    b[0].x /= self->sx;
    b[0].y /= self->sy;
    b[0].z /= self->sz;
    MtxMulPoint_13c890(&b[1], self->mtx50, arg4);
    VecSub_13be40(&b[1], &b[1], &self->ofs);
    b[1].x /= self->sx;
    b[1].y /= self->sy;
    b[1].z /= self->sz;
    MtxMulPoint_13c890(&a[0], self->mtx50, arg1);
    VecSub_13be40(&a[0], &a[0], &self->ofs);
    a[0].x /= self->sx;
    a[0].y /= self->sy;
    a[0].z /= self->sz;
    MtxMulPoint_13c890(&a[1], self->mtx50, arg2);
    VecSub_13be40(&a[1], &a[1], &self->ofs);
    a[1].x /= self->sx;
    a[1].y /= self->sy;
    a[1].z /= self->sz;
    VecAdd_13be20(&b[2], &b[0], &b[1]);
    VecAdd_13be20(&a[2], &a[0], &a[1]);
    VecScale_13be00(&b[2], &b[2], 0.5f);
    VecScale_13be00(&a[2], &a[2], 0.5f);
    found = 0;
    best = 0.0f;
    for (i = 0; i < 3; i++) {
        p = &a[i];
        if (SegmentSphereIntersect_13da60(p, &b[i], hit, 1.0f) != 0) {
            f32 dist = VecDistance_13d3d0(hit, p);
            if (found == 0 || !(best <= dist)) {
                best = dist;
                VecSub_13be40(&diff, hit, p);
            }
            found = 1;
        }
    }
    if (found != 0) {
        VecSub_13be40(&d, &b[0], &a[0]);
        VecScale_13be00(&d, &d, best);
        VecAdd_13be20(arg3, &a[0], &d);
        VecSub_13be40(&d, &b[1], &a[1]);
        VecScale_13be00(&d, &d, best);
        VecAdd_13be20(arg4, &a[1], &d);
        t90.x = arg3->x * self->sx;
        t90.y = arg3->y * self->sy;
        t90.z = arg3->z * self->sz;
        VecAdd_13be20(&t90, &t90, &self->ofs);
        MtxMulPoint_13c890(arg3, self->mtx10, &t90);
        t80.x = arg4->x * self->sx;
        t80.y = arg4->y * self->sy;
        t80.z = arg4->z * self->sz;
        VecAdd_13be20(&t80, &t80, &self->ofs);
        MtxMulPoint_13c890(arg4, self->mtx10, &t80);
    }
    return found;
}
