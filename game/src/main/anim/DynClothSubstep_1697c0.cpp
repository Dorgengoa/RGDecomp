#pragma optimization_level 3
#pragma opt_dead_assignments off
#include "types.h"

typedef rg_u128 u128;
typedef f32 VEC[4] __attribute__((aligned(16)));
typedef struct { VEC v[4]; } MTX;
typedef struct { MTX cur; MTX inv; } MM;

class Col {
public:
    u8 pad0[0x10];
    MM now;
    MM old;
    VC_VPTR_MEMBER;
    
    s32 Hit(VEC * a0) { return VCM(s32, (void *, VEC *), 0x10, a0); }
    u32 mask;
    s32 part;
    f32 fric;
};

typedef struct { u8 pad0[0x10]; MTX m; } Bone;
typedef struct { VEC local; s32 part; f32 w; f32 k; u8 pad1C[4]; } Pin;
typedef struct { s32 f0; s32 idx; f32 k; } Drag;
typedef struct { s32 a; s32 b; f32 w8; f32 wC; } Link;
typedef struct { s32 a; s32 b; f32 w8; f32 wC; u8 pad10[4]; f32 w14; u8 pad18[8]; } Spr;

typedef struct {
    s32 f0;
    s32 f4;
    u8 pad8[8];
    MTX m;
    MTX inv;
    s32 nb;
    s32 *parts;
    Bone *bones;
    MTX *out;
    s32 n;
    s32 fA4;
    VEC *pos;
    VEC *prev;
    VEC *vel;
    s32 fB4;
    u32 *masks;
    u8 padBC[4];
    Pin *pins;
    s32 nd;
    Drag *drags;
    u8 padCC[8];
    s32 nl;
    Link *links;
    s32 ns;
    Spr *sprs;
    u8 padE4[8];
    s32 nc;
    Col **cols;
    s32 iter;
    u8 padF8[8];
    VEC grav;
    f32 f110;
    f32 damp;
    s32 f118;
    f32 f11C;
    f32 f120;
    u8 pad124[0xC];
    VEC wind;
    u32 seed;
    f32 gust;
    s32 f148;
    f32 floor;
    u8 pad150[4];
    s32 f154;
    u8 pad158[8];
    VEC push;
} Cloth;

extern "C" {
extern void VecNormalize_13bd90(f32 *, f32 *);
extern void VecScale_13be00(f32 *, f32 *, f32);
extern void VecSub_13be40(f32 *, f32 *, f32 *);
extern void MtxTransformPoints_13c810(s32, MTX *, s32, s32);
extern void MtxMulPoint_13c890(f32 *, MTX *, f32 *);
extern void MtxInverse_13cf40(MTX *, MTX *);
extern void MtxIdentity_13d2e0(MTX *);
extern f32 VecLength_13d4a0(f32 *);
extern void VecMinMax3_13df40(f32 *, f32 *, f32 *, f32 *, f32 *);
extern void VecSubInPlace_13e050(f32 *, f32 *);
extern void VecAddInPlace_13e070(f32 *, f32 *);
extern void FrameCalcWorldMatrix_148ff0(s32, MTX *);
extern void DynFramePoseApply_169530(Cloth *, s32, Bone *);
extern void DynClothSolveSpring_16a480(f32 *, f32 *, f32, f32);
extern f32 D_0047D1D8;
extern f32 D_0047D1E8;
extern f32 D_0047D244;
}

#define CP4(d, s) { ((u128 *)(d))[0] = ((u128 *)(s))[0]; ((u128 *)(d))[1] = ((u128 *)(s))[1]; ((u128 *)(d))[2] = ((u128 *)(s))[2]; ((u128 *)(d))[3] = ((u128 *)(s))[3]; }
#define CP8(d, s) { ((u128 *)(d))[0] = ((u128 *)(s))[0]; ((u128 *)(d))[1] = ((u128 *)(s))[1]; ((u128 *)(d))[2] = ((u128 *)(s))[2]; ((u128 *)(d))[3] = ((u128 *)(s))[3]; ((u128 *)(d))[4] = ((u128 *)(s))[4]; ((u128 *)(d))[5] = ((u128 *)(s))[5]; ((u128 *)(d))[6] = ((u128 *)(s))[6]; ((u128 *)(d))[7] = ((u128 *)(s))[7]; }

static inline s32 GetPart(Cloth *o, s32 i) {
    if (i < 0 || i >= o->nb) {
        return 0;
    }
    return o->parts[i];
}

static inline f32 Rand(u32 *seed, f32 max) {
    u32 v = *seed * 0x343FD;
    *seed = v + 0x269EC3;
    return (f32)((*seed >> 16) & 0xFFFF) / max;
}

extern "C" void DynClothSubstep_1697c0(Cloth *o) {
    MTX m __attribute__((aligned(16)));
    MTX inv __attribute__((aligned(16)));
    VEC t __attribute__((aligned(16)));
    VEC a __attribute__((aligned(16)));
    VEC b __attribute__((aligned(16)));
    VEC c __attribute__((aligned(16)));
    VEC lo __attribute__((aligned(16)));
    VEC hi __attribute__((aligned(16)));
    VEC w __attribute__((aligned(16)));
    VEC g __attribute__((aligned(16)));
    VEC d __attribute__((aligned(16)));
    VEC u __attribute__((aligned(16)));
    VEC pa __attribute__((aligned(16)));
    VEC pb __attribute__((aligned(16)));
    f32 k;
    f32 amp;
    Link *l;
    VEC *pp;
    MTX *dst;
    Pin *pin;
    s32 j;
    s32 hit;
    f32 *q;
    f32 len;
    f32 best;
    Bone *bn;
    Spr *s;
    s32 part;
    VEC *vp;
    f32 *p;
    s32 i;
    s32 cnt;
    Col *col;
    s32 bi;
    Drag *dr;
    f32 f;
    f32 f2;
    f32 r_;
    f32 e_;

    pin = 0;
    if (o->f0 == 0) {
        return;
    }
    if (o->n <= 0) {
        return;
    }
    k = o->f110;
    if (o->f4 != 0) {
        FrameCalcWorldMatrix_148ff0(o->f4, &m);
        MtxInverse_13cf40(&inv, &m);
    } else {
        k = 0.0f;
    }
    if (!(k <= 0.0f)) {
        MtxTransformPoints_13c810(o->fB4, &m, o->fA4, o->n);
    }
    for (i = 0; i < o->nc; i++) {
        col = o->cols[i];
        if (col == 0) {
            continue;
        }
        part = GetPart(o, col->part);
        if (part != 0) {
            CP8(&col->old, &col->now);
            FrameCalcWorldMatrix_148ff0(part, &col->now.cur);
            MtxInverse_13cf40(&col->now.inv, &col->now.cur);
        }
    }
    for (i = 0; i < o->nb; i++) {
        bn = &o->bones[i];
        if (o->parts[i] != 0) {
            FrameCalcWorldMatrix_148ff0(o->parts[i], &bn->m);
        } else {
            MtxIdentity_13d2e0(&bn->m);
        }
    }
    for (i = 0; i < o->nd; i++) {
        dr = &o->drags[i];
        p = o->pos[dr->idx];
        q = o->prev[dr->idx];
        MtxMulPoint_13c890(a, &o->inv, p);
        MtxMulPoint_13c890(b, &m, a);
        VecSub_13be40(c, b, p);
        VecScale_13be00(c, c, dr->k);
        VecAddInPlace_13e070(p, c);
        VecAddInPlace_13e070(q, c);
    }
    for (i = 0; i < o->n; i++) {
        VecAddInPlace_13e070(o->pos[i], o->push);
        VecAddInPlace_13e070(o->prev[i], o->push);
    }
    pp = o->pos;
    vp = o->vel;
    for (i = 0; i < o->n; i++, pp++, vp++) {
        VecAddInPlace_13e070(*vp, o->grav);
        VecAddInPlace_13e070(*pp, *vp);
    }
    if (o->f118 != 0) {
        for (i = 0; i < o->n; i++) {
            pin = &o->pins[i];
            if (pin->w < 1.0f) {
                continue;
            }
            if (pin->part >= 0) {
                MtxMulPoint_13c890(o->pos[i], &o->bones[pin->part].m, pin->local);
            }
        }
    }
    for (i = 0; i < o->ns; i++) {
        f32 *q, *p;
        s = &o->sprs[i];
        p = o->pos[s->b];
        q = o->pos[s->a];
        VecSub_13be40(d, q, p);
        len = VecLength_13d4a0(d);
        VecScale_13be00(u, d, 1.0f / len);
        e_ = s->w8;
        r_ = s->w14;
        f = 1.0f - e_;
        f2 = e_ * (len - r_);
        f = f * (r_ - len);
        VecScale_13be00(pa, u, f * s->wC);
        VecScale_13be00(pb, u, f2 * s->wC);
        VecAddInPlace_13e070(q, pa);
        VecAddInPlace_13e070(p, pb);
        VecSub_13be40(d, q, p);
        f = VecLength_13d4a0(d);
        VecScale_13be00(u, d, 1.0f / f);
    }
    for (j = 0; j < o->iter; j++) {
        for (l = o->links, cnt = o->nl; cnt > 0; cnt--, l++) {
            DynClothSolveSpring_16a480(o->pos[l->a], o->pos[l->b], l->wC, l->w8);
        }
        for (pin = o->pins, pp = o->pos, cnt = o->n; cnt > 0; cnt--, pin++, pp++) {
            if (pin->w < 1.0f) {
                continue;
            }
            if (pin->part >= 0) {
                MtxMulPoint_13c890(*pp, &o->bones[pin->part].m, pin->local);
            }
        }
    }
    *(u128 *)lo = *(u128 *)o->pos[0];
    *(u128 *)hi = *(u128 *)o->pos[0];
    k = o->f120;
    *(u128 *)w = *(u128 *)o->wind;
    for (i = 0; i < 3; i++) {
        w[i] = w[i] + 0.3f * (Rand(&o->seed, 0xFFFF) - 0.5f);
    }
    VecNormalize_13bd90(w, w);
    w[3] = 0.0f;
    k = k * 0.1f;
    for (i = 0; i < o->n; i++) {
        VecSub_13be40(o->vel[i], o->pos[i], o->prev[i]);
        pin = &o->pins[i];
        if (pin->w < 1.0f) {
            if (!(pin->w <= 0.0f)) {
                bi = pin->part;
                if (GetPart(o, bi) != 0) {
                    MtxMulPoint_13c890(t, &o->bones[bi].m, pin->local);
                    VecSubInPlace_13e050(t, o->pos[i]);
                    VecScale_13be00(t, t, pin->w);
                    VecAddInPlace_13e070(o->pos[i], t);
                    VecScale_13be00(t, t, pin->k);
                    VecSubInPlace_13e050(o->vel[i], t);
                }
            }
        }
        if (pin->w < 1.0f) {
            best = 1.0f;
            hit = 0;
            for (j = 0; j < o->nc; j++) {
                col = o->cols[j];
                if (col == 0) {
                    continue;
                }
                if (col->mask & o->masks[i]) {
                    continue;
                }
                hit |= col->Hit(&o->pos[i]);
                if (!(best <= col->fric)) {
                    best = col->fric;
                }
            }
            if (hit) {
                VecScale_13be00(o->vel[i], o->vel[i], best);
            }
        }
        VecScale_13be00(o->vel[i], o->vel[i], o->damp);
        if (k != 0.0f) {
            o->gust = o->gust + 0.5f * (Rand(&o->seed, 0xFFFF) - 0.5f);
            Rand(&o->seed, 0xFFFF);
            if (!(o->gust <= 1.0f)) {
                o->gust = 1.0f;
            }
            if (o->gust < -0.1f) {
                o->gust = -0.1f;
            }
            VecScale_13be00(g, w, o->f11C * (k * o->gust));
            VecAddInPlace_13e070(o->vel[i], g);
        }
        if (o->f148 != 0) {
            if (o->pos[i][1] < o->floor) {
                o->pos[i][1] = o->floor;
                VecScale_13be00(o->vel[i], o->vel[i], 0.3f);
            }
        }
        VecMinMax3_13df40(lo, hi, lo, hi, o->pos[i]);
        *(u128 *)o->prev[i] = *(u128 *)o->pos[i];
    }
    for (i = 0; i < o->nb; i++) {
        bn = &o->bones[i];
        part = o->parts[i];
        DynFramePoseApply_169530(o, part, bn);
        if (part == 0) {
            continue;
        }
        dst = &o->out[i];
        CP4(dst, &bn->m);
    }
    if (o->f4 != 0) {
        FrameCalcWorldMatrix_148ff0(o->f4, &o->m);
        MtxInverse_13cf40(&o->inv, &o->m);
    }
    if (o->f154 != 0) {
        *(u128 *)o->push = 0;
    }
}
