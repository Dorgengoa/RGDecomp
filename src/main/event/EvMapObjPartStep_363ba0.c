#include "types.h"
typedef unsigned __int128 u128;
#pragma optimization_level 3

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;

typedef struct {
    Vec4 p;
    Vec4 v;
    f32 m20;
    f32 m24;
    f32 m28;
    Vec4 m2C_;
} PtRaw;

typedef struct {
    Vec4 p;
    Vec4 v;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    f32 m30;
    f32 m34;
    s32 m38;
    s32 m3C;
} Pt;

typedef struct {
    Pt pt[3];
    u8 padC0[0x30];
    Vec4 mF0;
    Vec4 m100;
    Vec4 m110;
    f32 m120[3];
    f32 m12C;
    f32 m130;
    f32 m134;
    s32 m138;
} Obj;

extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern void EvMapObjPointStep_3642d0(Pt *, s32, s32, f32);
extern s32 CollSegmentVsPlanesMaybe_364520(s32, s32, Vec4 *, Vec4 *, Vec4 *, Vec4 *, f32 *);
extern void VecSolveDistanceConstraint_364740(Vec4 *, Vec4 *, u128, f32, f32);
extern void sceVu0CopyVector(Vec4 *, Vec4 *);
extern f32 D_0047D244;
extern f32 D_0047D2A8;

void EvMapObjPartStep_363ba0(Obj *obj, s32 arg1, s32 arg2) {
    f32 rad;
    Vec4 save[3];
    volatile Vec4 t1;
    volatile Vec4 t0;
    Vec4 a;
    Vec4 b;
    Vec4 cur;
    Vec4 lim;
    Vec4 d;
    Vec4 hit;
    Vec4 nrm;
    Vec4 off;
    Vec4 c;
    s32 i;
    s32 j;
    Pt *p;
    Pt *q;

    for (i = 0; i < 3; i++) {
        EvMapObjPointStep_3642d0(&obj->pt[i], arg1, arg2, obj->m134);
    }
    for (j = 0; j < 3; j++) {
        *(u128 *)&save[j] = *(u128 *)&obj->pt[j].p;
    }
    if (obj->m138 == 1) {
        obj->m138 = 2;
    }
    if (obj->m138 == 0) {
        obj->m110.x = obj->pt[0].m2C;
        obj->m110.y = obj->pt[0].m30;
        obj->m110.z = obj->pt[0].m34;
        obj->m110.w = 0.0f;
        if (obj->pt[0].m38 != 0) {
            obj->m138 = 1;
        } else {
            obj->m110.x = obj->pt[1].m2C;
            obj->m110.y = obj->pt[1].m30;
            obj->m110.z = obj->pt[1].m34;
            obj->m110.w = 0.0f;
            if (obj->pt[1].m38 != 0) {
                obj->m138 = 1;
            } else {
                obj->m110.x = obj->pt[2].m2C;
                obj->m110.y = obj->pt[2].m30;
                obj->m110.z = obj->pt[2].m34;
                obj->m110.w = 0.0f;
                if (obj->pt[2].m38 != 0) {
                    obj->m138 = 1;
                }
            }
        }
    }
    if (obj->m138 != 0) {
        for (i = 0; i < 3; i++) {
            q = &obj->pt[(i + 1) % 3];
            p = &obj->pt[i];
            t0 = q->p;
            a = p->p;
            b = q->p;
            t1 = a;
            VecSolveDistanceConstraint_364740(&a, &b, *(u128 *)&a, obj->m120[i], obj->m12C);
            p->p = a;
            q->p = b;
        }
        for (i = 0; i < 3; i++) {
            p = &obj->pt[i];
            *(u128 *)&cur = *(u128 *)&p->p;
            lim.x = p->m20;
            lim.y = p->m24;
            lim.z = p->m28;
            lim.w = 1.0f;
            rad = obj->m134;
            if (CollSegmentVsPlanesMaybe_364520(arg1, arg2, &lim, &cur, &hit, &nrm, &rad) != 0) {
                VecNormalize_13bd90(&nrm, &nrm);
                VecScale_13be00(&off, &nrm, D_0047D244 + rad);
                VecAdd_13be20(&hit, &hit, &off);
                p->p = hit;
            }
            VecSub_13be40(&d, &cur, &save[i]);
            VecScale_13be00(&d, &d, 0.5f);
            VecAdd_13be20(&obj->pt[i].v, &obj->pt[i].v, &d);
        }
    }
    for (j = 0; j < 3; j++) {
        *(u128 *)&save[j] = *(u128 *)&obj->pt[j].p;
    }
    VecAdd_13be20(&c, &save[0], &save[1]);
    VecAdd_13be20(&c, &c, &save[2]);
    VecScale_13be00(&c, &c, D_0047D2A8);
    sceVu0CopyVector(&obj->m100, &obj->mF0);
    sceVu0CopyVector(&obj->mF0, &c);
}
