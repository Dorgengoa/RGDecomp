#pragma optimization_level 3
#include "types.h"

typedef unsigned __int128 u128;
#define CP(d, s) (*(u128 *)&(d) = *(u128 *)&(s))

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4 __attribute__((aligned(16)));

typedef struct M4 {
    V4 r[4];
} M4;

typedef struct Sub {
    u8 pad0[0xC];
    s8 mC;
    s8 mD;
    u8 padE[2];
    s8 m10;
    u8 pad11[0xF];
    V4 m20;
    V4 m30;
    V4 m40;
} Sub;

typedef struct Lnk {
    u8 pad0[0x34];
    s32 m34;
    s32 m38;
} Lnk;

typedef struct Cam {
    u8 *m0;
    s32 m4;
    Lnk *m8;
    void *mC;
    s32 m10;
    s32 m14;
    u8 pad18[8];
    V4 m20;
    V4 m30;
} Cam;

typedef struct Clk {
    V4 pos;
    f32 m10;
} Clk;

extern f32 Atan2f_1291a8(f32, f32);
extern s32 Rand_133710(void);
extern void VecScale_13be00(V4 *, V4 *, f32);
extern void VecAdd_13be20(V4 *, V4 *, V4 *);
extern void VecSub_13be40(V4 *, V4 *, V4 *);
extern f32 RandFloat_13c010(void);
extern void MtxMulVec4_13c900(V4 *, M4 *, V4 *);
extern void VecMin_13df90(V4 *, V4 *, V4 *);
extern void VecMax_13dfe0(V4 *, V4 *, V4 *);
extern void VecAddInPlace_13e070(V4 *, V4 *);
extern void NodeCalcWorldMatrix_186130(void *, M4 *);
extern void NodeSetRotation_186620(void *, V4 *);
extern void NodeGetTranslation_186650(void *, V4 *);
extern void FuncAnimeGetValue_1911c0(Cam *, V4 *);
extern void FuncAnimeApplyValue_191270(Cam *, V4 *);
extern void sceVu0InversMatrix(M4 *, M4 *);
extern void NodeCalcWorldMatrixThunk_186130(void *, M4 *);
extern f32 sqrtf(f32);
extern f32 D_0047D1FC;

static inline s32 reached(V4 *vel, V4 *cur, V4 *tgt)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        f32 v_ = *(f32 *)((u32)&(&vel->x)[i]);

        if (v_ > 0.0f && !((&cur->x)[i] < (&tgt->x)[i])) {
            return 1;
        }
        if (v_ < 0.0f && (&cur->x)[(u32)i] <= (&tgt->x)[(u32)i]) {
            return 1;
        }
    }
    return 0;
}

static inline s32 inRange(f32 t, f32 a, f32 b)
{
    if (!(b <= a)) {
        if (t < a) {
            return 0;
        }
        if (!(t < b)) {
            return 0;
        }
        return 1;
    }
    {
        s32 r;
        if (a <= b) goto one;
        if (!(t < a)) {
            r = 1;
            goto end;
        }
        if (t < b) {
            r = 1;
        } else {
            r = 0;
        }
    end:
        return r;
    one:
        r = 1;
        goto end;
    }
}

static inline f32 wrap24(f32 x)
{
    if (!(x < 0.0f) && x < 24.0f) {
        x = x;
    } else {
        x -= 24.0f * (s32)(x / 24.0f);
        if (x < 0.0f) {
            x += 24.0f;
        }
    }
    if (x <= 12.0f) {
        x = x;
    } else {
        x = 24.0f - x;
    }
    return x;
}

static inline V4 *initZ(V4 *z)
{
    {
        u8 *p_ = (u8 *)z;
        u32 n_ = 0x10;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    z->x = 0.0f;
    z->y = 0.0f;
    z->z = 0.0f;
    return z;
}

static inline s32 target(Cam *c)
{
    s32 t;

    t = c->m4;
    if (t == 0) {
        t = (s32)c->m8;
    }
    if (t == 0) {
        t = (s32)c->mC;
    }
    return t;
}

void FuncAnimeUpdate_191650(Cam *c, Clk *clk)
{
    V4 vel;
    V4 add;
    V4 lo;
    V4 hi;
    V4 d7;
    V4 v;
    M4 m;
    M4 inv;
    V4 d6;
    Sub *s;
    Lnk *l;
    s32 i;
    f32 t;
    f32 a;
    f32 tm;
    f32 b;
    f32 d1;
    f32 d2;
    f32 w;

    s = (Sub *)(c->m0 + 0x60);
    if (c->m10 != 0) {
        return;
    }
    CP(vel, c->m30);
    switch (s->m10) {
    case 1:
        VecScale_13be00(&vel, &s->m30, RandFloat_13c010());
        break;
    case 2:
        VecScale_13be00(&vel, &s->m30, 2.0f * (RandFloat_13c010() - 0.5f));
        break;
    case 3:
        for (i = 0; i < 3; i++) {
            if ((&s->m30.x)[i] > 0.0f) {
                (&lo.x)[i] = 0.0f;
                (&hi.x)[i] = (&s->m30.x)[i];
            } else {
                (&hi.x)[i] = 0.0f;
                (&lo.x)[i] = (&s->m30.x)[i];
            }
        }
    case 4:
        if (s->m10 == 4) {
            for (i = 0; i < 3; i++) {
                if ((&s->m30.x)[i] > 0.0f) {
                    (&lo.x)[i] = -(&s->m30.x)[i];
                    (&hi.x)[i] = (&s->m30.x)[i];
                } else {
                    (&hi.x)[i] = -(&s->m30.x)[i];
                    (&lo.x)[i] = (&s->m30.x)[i];
                }
            }
        }
        VecScale_13be00(&add, &s->m30, 2.0f * (RandFloat_13c010() - 0.5f));
        VecAddInPlace_13e070(&vel, &add);
        VecMax_13dfe0(&vel, &vel, &lo);
        VecMin_13df90(&vel, &vel, &hi);
        break;
    case 0:
    default:
        CP(vel, s->m30);
        break;
    }
    CP(c->m30, vel);
    if (c->m14 != 0) {
        VecScale_13be00(&vel, &vel, -1.0f);
    }
    if (target(c) == 0) {
        return;
    }
    FuncAnimeGetValue_1911c0(c, &c->m20);
    switch (s->mD) {
    case 0:
        break;
    case 1:
        VecAddInPlace_13e070(&c->m20, &vel);
        break;
    case 2:
        VecAddInPlace_13e070(&c->m20, &vel);
        if (reached(&vel, &c->m20, &s->m40)) {
            CP(c->m20, s->m40);
        }
        break;
    case 7:
        VecSub_13be40(&d7, &s->m40, &s->m20);
        d7.x *= (f32)Rand_133710() / 2147483648.0f;
        d7.y *= (f32)Rand_133710() / 2147483648.0f;
        d7.z *= (f32)Rand_133710() / 2147483648.0f;
        VecAdd_13be20(&c->m20, &s->m20, &d7);
        break;
    case 3:
        VecAddInPlace_13e070(&c->m20, &vel);
        if (reached(&vel, &c->m20, &s->m40)) {
            CP(c->m20, s->m20);
        }
        break;
    case 4:
    case 5:
        VecAddInPlace_13e070(&c->m20, &vel);
        if (c->m14 != 0) {
            if (reached(&vel, &c->m20, &s->m20)) {
                CP(c->m20, s->m20);
                c->m14 = 0;
                if (s->mD == 5) {
                    c->m10 = 1;
                }
            }
        } else {
            if (reached(&vel, &c->m20, &s->m40)) {
                CP(c->m20, s->m40);
                c->m14 = 1;
            }
        }
        break;
    case 6:
        if (s->mC == 2 && clk != 0 && c->mC != 0) {
            CP(v, clk->pos);
            l = c->m8;
            if (l != 0) {
                v.w = 1.0f;
                if (c->m4 == 0) {
                    NodeCalcWorldMatrixThunk_186130(c->mC, &m);
                } else {
                    l->m34 = (s32)c->mC;
                    l->m38 = 0;
                    l = c->m8;
                    {
                        V4 z = {0};
                        z.x = 0.0f;
                        z.y = 0.0f;
                        z.z = 0.0f;
                        NodeSetRotation_186620(l, &z);
                    }
                    NodeCalcWorldMatrix_186130(c->m8, &m);
                    l = c->m8;
                    l->m34 = 0;
                    l->m38 = 0;
                }
                sceVu0InversMatrix(&inv, &m);
                MtxMulVec4_13c900(&v, &inv, &v);
            } else {
                NodeGetTranslation_186650(c->mC, &d6);
                v.x = v.x - d6.x;
                v.y = v.y - d6.y;
                v.z = v.z - d6.z;
            }
            c->m20.y = 180.0f * Atan2f_1291a8(v.x, v.z) / D_0047D1FC;
            c->m20.x = 180.0f * -Atan2f_1291a8(v.y, sqrtf(v.x * v.x + v.z * v.z)) / D_0047D1FC;
            for (i = 0; i < 3; i++) {
                if ((&c->m20.x)[i] <= (&s->m20.x)[i]) {
                    (&c->m20.x)[i] = (&s->m20.x)[i];
                }
                if (!((&c->m20.x)[i] <= (&s->m40.x)[i])) {
                    (&c->m20.x)[i] = (&s->m40.x)[i];
                }
            }
        }
        break;
    case 8:
        if (clk != 0) {
            c->m20.y = 360.0f * -clk->m10;
        }
        break;
    case 9:
        if (clk != 0) {
            c->m20.y = 360.0f * (-clk->m10 / 12.0f);
        }
        break;
    case 10:
        if (clk == 0 || (b = s->m30.y, a = s->m30.x, tm = clk->m10, inRange(tm, a, b))) {
            t = 1.0f;
        } else {
            {
                w = s->m30.z;
                t = 0.0f;
                if (!(w <= 0.0f)) {
                    d1 = wrap24(a - tm);
                    d2 = wrap24(tm - b);
                    if (!(d1 < 0.0f) && d1 <= w) {
                        t = 1.0f - d1 / w;
                    }
                    if (!(d2 < 0.0f) && d2 <= w) {
                        t = 1.0f - d2 / w;
                    }
                }
            }
        }
        c->m20.x = s->m20.x + t * (s->m40.x - s->m20.x);
        c->m20.y = s->m20.y + t * (s->m40.y - s->m20.y);
        c->m20.z = s->m20.z + t * (s->m40.z - s->m20.z);
        break;
    case 11:
        VecAddInPlace_13e070(&c->m20, &vel);
        VecMax_13dfe0(&c->m20, &c->m20, &s->m20);
        VecMin_13df90(&c->m20, &c->m20, &s->m40);
        break;
    }
    FuncAnimeApplyValue_191270(c, &c->m20);
}
