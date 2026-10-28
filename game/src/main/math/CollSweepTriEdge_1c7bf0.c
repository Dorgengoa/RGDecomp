/* rgp:protos */
#define RGP_SELF_CollSweepTriEdge_1c7bf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct Coll {
    Vec x00;
    Vec x10;
    f32 x20;
    f32 x24;
    u8 pad28[8];
    Vec x30;
    Vec x40;
    Vec x50;
    Vec x60;
    f32 x70;
} Coll;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 sqrtf(f32);

s32 CollSweepTriEdge_1c7bf0(Coll *o, Vec *p0, Vec *p1) {
    Vec mn __attribute__((aligned(16)));
    Vec mx __attribute__((aligned(16)));
    Vec b __attribute__((aligned(16)));
    Vec a __attribute__((aligned(16)));
    Vec v90 __attribute__((aligned(16)));
    Vec v80 __attribute__((aligned(16)));
    Vec v70 __attribute__((aligned(16)));
    Vec v60 __attribute__((aligned(16)));
    Vec r __attribute__((aligned(16)));
    f32 len;
    f32 qa;
    f32 qb;
    f32 disc;
    f32 nb;
    f32 t;
    f32 s;
    u8 *p;
    u32 n;

    VecMinMax_1cb570(&mn, &mx, p0, p1);
    if (mn.x < o->x50.x || mn.y < o->x50.y || mn.z < o->x50.z) {
        return 0;
    }
    if (!(mx.x <= o->x60.x) || !(mx.y <= o->x60.y) || !(mx.z <= o->x60.z)) {
        return 0;
    }
    VecSubXyzW0_1cbce0(&a, &o->x00, p0);
    VecSubXyzW0_1cbce0(&b, p1, p0);
    len = VecLengthSq_1cb470(&b, 0);
    VecLinearCombine_1cb8b0(&v90, &b, &o->x10, VecDot3_1cba90(&b, &o->x10) / len, -1.0f);
    VecLinearCombine_1cb8b0(&v80, &b, &a, VecDot3_1cba90(&b, &a) / len, -1.0f);
    qa = VecLengthSq_1cb470(&v90, 0);
    if (0.0f == qa) {
        return 0;
    }
    qb = VecDot3_1cba90(&v90, &v80);
    disc = qb * qb - qa * (VecLengthSq_1cb470(&v80, 0) - o->x70);
    if (disc < 0.0f) {
        return 0;
    }
    disc = sqrtf(disc);
    nb = -qb;
    t = (nb - disc) / qa;
    if (!(t < o->x24)) {
        return 0;
    }
    if (t < 0.0f) {
        if ((nb + disc) / qa < 0.0f) {
            return 0;
        }
        t = 0.0f;
    }
    VecLinearCombine_1cb8b0(&v70, &o->x10, &a, t, 1.0f);
    s = VecDot3_1cba90(&b, &v70) / len;
    if (s < 0.0f) {
        return 0;
    }
    if (!(s <= 1.0f)) {
        return 0;
    }
    o->x24 = t;
    VecLinearCombine_1cb8b0(&v60, &o->x10, &o->x00, o->x24, 1.0f);
    VecMinMax_1cb570(&o->x40, &o->x30, &o->x00, &v60);
    p = (u8 *)&r;
    n = 16;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
    r.x = o->x20;
    r.y = o->x20;
    r.z = o->x20;
    VecAdd_1cbdc0(&o->x60, &o->x40, &r);
    VecSub_1cbd00(&o->x50, &o->x30, &r);
    return 1;
}
