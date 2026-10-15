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

void VecMinMax_1cb570(Vec *, Vec *, Vec *, Vec *);
f32 VecLengthSq_1cb470(Vec *);
void VecLinearCombine_1cb8b0(Vec *, Vec *, Vec *, f32, f32);
f32 VecDot3_1cba90(Vec *, Vec *);
void VecSubXyzW0_1cbce0(Vec *, Vec *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);
extern f32 sqrtf(f32);

s32 CollSweepTriEdge_1c7bf0(Coll *o, Vec *p0, Vec *p1) {
    Vec mn;
    Vec mx;
    Vec b;
    Vec a;
    Vec v90;
    Vec v80;
    Vec v70;
    Vec v60;
    Vec r;
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
    len = VecLengthSq_1cb470(&b);
    VecLinearCombine_1cb8b0(&v90, &b, &o->x10, VecDot3_1cba90(&b, &o->x10) / len, -1.0f);
    VecLinearCombine_1cb8b0(&v80, &b, &a, VecDot3_1cba90(&b, &a) / len, -1.0f);
    qa = VecLengthSq_1cb470(&v90);
    if (0.0f == qa) {
        return 0;
    }
    qb = VecDot3_1cba90(&v90, &v80);
    disc = qb * qb - qa * (VecLengthSq_1cb470(&v80) - o->x70);
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
