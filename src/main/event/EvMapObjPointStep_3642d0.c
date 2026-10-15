#include "types.h"
#include "vec.h"

typedef struct Obj {
    Vec4 pos;       /* 0x00 */
    Vec4 vel;       /* 0x10 */
    f32 prev[3];    /* 0x20 */
    f32 nrm[3];     /* 0x2C */
    s32 hit;        /* 0x38 */
} Obj;

extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecScale_13be00(Vec4 *, Vec4 *, f32);
extern void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern f32 VecLength_13d4a0(Vec4 *);
extern s32 CollSegmentVsPlanesMaybe_364520(s32, s32, Vec4 *, Obj *, Vec4 *, Vec4 *, f32 *);
extern f32 D_0047D244;
extern f32 D_0047D27C;
extern f32 D_0047D2A0;
extern f32 D_0047D2A4;
typedef struct F4 { f32 a, b, c, d; } F4;
extern F4 D_0047F900 __attribute__((section(".sdata")));

void EvMapObjPointStep_3642d0(Obj *o, s32 a, s32 b, f32 t) {
    Vec4 g;
    Vec4 old;
    Vec4 hp;
    Vec4 n;
    Vec4 v80;
    Vec4 d;
    Vec4 p;
    Vec4 r;
    f32 len;

    *(F4 *)&g = D_0047F900;
    VecAdd_13be20(&o->vel, &o->vel, &g);
    VecScale_13be00(&o->vel, &o->vel, D_0047D27C);
    len = VecLength_13d4a0(&o->vel);
    if (!(len <= D_0047D2A0)) {
        VecScale_13be00(&o->vel, &o->vel, D_0047D2A0 / len);
    }
    old = o->pos;
    VecAdd_13be20(&o->pos, &o->pos, &o->vel);
    p.x = o->prev[0];
    p.y = o->prev[1];
    p.z = o->prev[2];
    p.w = 1.0f;
    VecSub_13be40(&d, &p, &o->pos);
    VecNormalize_13bd90(&d, &d);
    VecScale_13be00(&d, &d, 5.0f);
    VecAdd_13be20(&d, &p, &d);
    if (CollSegmentVsPlanesMaybe_364520(a, b, &d, o, &hp, &n, &t) != 0) {
        VecNormalize_13bd90(&n, &n);
        VecScale_13be00(&v80, &n, D_0047D244 + t);
        VecAdd_13be20(&hp, &hp, &v80);
        o->pos = hp;
        VecScale_13be00(&r, &o->vel, -1.0f);
        VecScale_13be00(&r, &n, 2.0f * Vu0InnerProduct_13bd60(&r, &n));
        VecAdd_13be20(&o->vel, &o->vel, &r);
        VecScale_13be00(&o->vel, &o->vel, D_0047D2A4);
        o->hit = 1;
        o->nrm[0] = n.x;
        o->nrm[1] = n.y;
        o->nrm[2] = n.z;
    } else {
        o->hit = 0;
    }
    o->prev[0] = old.x;
    o->prev[1] = old.y;
    o->prev[2] = old.z;
}
