#include "types.h"

typedef struct Vec {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct Body {
    u8 pad0[0x10];
    Vec pos;
    f32 f20;
    f32 t;
    u8 pad28[8];
    Vec v30;
    Vec v40;
    Vec min;
    Vec max;
    f32 f70;
    f32 f74;
} Body;

extern f32 sqrtf(f32);
extern f32 VecLengthSq_1cb470(Vec *);
extern void VecMinMax_1cb570(Vec *, Vec *, Body *, Vec *);
extern void VecLinearCombine_1cb8b0(Vec *, Vec *, Body *, f32, f32);
extern f32 VecDot3_1cba90(Vec *, Vec *);
extern void VecSubXyzW0_1cbce0(Vec *, Body *, Vec *);
extern void VecSub_1cbd00(Vec *, Vec *, Vec *);
extern void VecAdd_1cbdc0(Vec *, Vec *, Vec *);

static inline void clr(Vec *v)
{
    u8 *p = (u8 *)v;
    u32 n;

    n = 0x10;
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}

s32 CollSweepTriVertex_1c7f30(Body *self, Vec *p)
{
    Vec d;
    f32 c;
    f32 a;
    f32 b;
    f32 disc;
    f32 t;
    f32 f;

    if (p->x < self->min.x || p->y < self->min.y || p->z < self->min.z) {
        return 0;
    }
    if (!(p->x <= self->max.x) || !(p->y <= self->max.y) || !(p->z <= self->max.z)) {
        return 0;
    }
    VecSubXyzW0_1cbce0(&d, self, p);
    c = VecLengthSq_1cb470(&d) - self->f70;
    if (c <= 0.0f) {
        Vec m;
        Vec s;

        self->t = 0.0f;
        VecLinearCombine_1cb8b0(&m, &self->pos, self, self->t, 1.0f);
        VecMinMax_1cb570(&self->v40, &self->v30, self, &m);
        clr(&s);
        f = self->f20;
        s.x = f;
        s.y = f;
        s.z = f;
        VecAdd_1cbdc0(&self->max, &self->v40, &s);
        VecSub_1cbd00(&self->min, &self->v30, &s);
        return 1;
    } else {
        Vec m;
        Vec s;

        a = self->f74;
        b = VecDot3_1cba90(&self->pos, &d);
        disc = b * b - a * c;
        if (disc < 0.0f) {
            return 0;
        }
        t = (-b - sqrtf(disc)) / a;
        if (!(t < self->t)) {
            return 0;
        }
        if (t < 0.0f) {
            return 0;
        }
        self->t = t;
        VecLinearCombine_1cb8b0(&m, &self->pos, self, self->t, 1.0f);
        VecMinMax_1cb570(&self->v40, &self->v30, self, &m);
        clr(&s);
        f = self->f20;
        s.x = f;
        s.y = f;
        s.z = f;
        VecAdd_1cbdc0(&self->max, &self->v40, &s);
        VecSub_1cbd00(&self->min, &self->v30, &s);
        return 1;
    }
}
