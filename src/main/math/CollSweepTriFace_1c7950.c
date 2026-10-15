#include "types.h"

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Ray {
    Vec org;
    Vec dir;
    f32 rad;
    f32 tmax;
    u8 pad28[8];
    Vec v30;
    Vec v40;
    Vec v50;
    Vec v60;
} Ray;

void VecMinMax_1cb570(Vec *, Vec *, Ray *, Vec *);
f32 TriNormalDot_1cb600(Vec *, Vec *, Vec *, Vec *);
void VecLinearCombine_1cb8b0(Vec *, Vec *, Ray *, f32, f32);
void TriNormal_1cb970(Vec *);
f32 VecDot3_1cba90(Vec *, Vec *);
void VecNormalize_1cbb80(Vec *, Vec *);
void VecScale_1cbca0(Vec *, Vec *, f32);
void VecSubXyzW0_1cbce0(Vec *, Ray *, Vec *);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void VecAdd_1cbdc0(Vec *, Vec *, Vec *);

static inline void zero_mem(void *p, u32 size) {
    u8 *c = (u8 *)p;
    u32 n = size;
    if (c != 0) {
        do {
            *c = 0;
            n--;
            c++;
        } while (n != 0);
    }
}

s32 CollSweepTriFace_1c7950(Ray *r, Vec *a, Vec *b, Vec *c) {
    Vec n;
    Vec pa;
    Vec off;
    Vec hp;
    Vec hp2;
    Vec v;
    f32 d;
    f32 ad;
    f32 rad;
    f32 t;

    TriNormal_1cb970(&n);
    VecNormalize_1cbb80(&n, &n);
    VecSubXyzW0_1cbce0(&pa, r, a);
    d = VecDot3_1cba90(&n, &pa);
    rad = r->rad;
    ad = d;
    if (ad < 0.0f) {
        ad = -ad;
    }
    if (ad <= rad) {
        t = 0.0f;
    } else {
        if (!(rad <= 0.0f)) {
            VecScale_1cbca0(&off, &n, rad);
            if (d < 0.0f) {
                VecAdd_1cbdc0(&pa, &pa, &off);
            } else {
                VecSub_1cbd00(&pa, &pa, &off);
            }
        }
        d = VecDot3_1cba90(&n, &pa);
        t = -d / VecDot3_1cba90(&n, &r->dir);
        if (!(t < r->tmax)) {
            return 0;
        }
        if (t < 0.0f) {
            return 0;
        }
    }
    VecLinearCombine_1cb8b0(&hp, &r->dir, r, t, 1.0f);
    if (TriNormalDot_1cb600(&hp, a, b, &n) < 0.0f) {
        return 0;
    }
    if (TriNormalDot_1cb600(&hp, b, c, &n) < 0.0f) {
        return 0;
    }
    if (TriNormalDot_1cb600(&hp, c, a, &n) < 0.0f) {
        return 0;
    }
    r->tmax = t;
    VecLinearCombine_1cb8b0(&hp2, &r->dir, r, r->tmax, 1.0f);
    VecMinMax_1cb570(&r->v40, &r->v30, r, &hp2);
    zero_mem(&v, 0x10);
    v.x = r->rad;
    v.y = r->rad;
    v.z = r->rad;
    VecAdd_1cbdc0(&r->v60, &r->v40, &v);
    VecSub_1cbd00(&r->v50, &r->v30, &v);
    return 1;
}
