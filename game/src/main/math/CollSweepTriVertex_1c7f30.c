/* rgp:protos */
#define RGP_SELF_CollSweepTriVertex_1c7f30 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    Vec d __attribute__((aligned(16)));
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
    c = VecLengthSq_1cb470(&d, 0) - self->f70;
    if (c <= 0.0f) {
        Vec m __attribute__((aligned(16)));
        Vec s __attribute__((aligned(16)));

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
        Vec m __attribute__((aligned(16)));
        Vec s __attribute__((aligned(16)));

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
