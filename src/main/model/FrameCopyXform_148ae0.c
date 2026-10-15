#include "types.h"
/* FrameCopyXform_148ae0 -- asm-free (s88m): the old vu0inline.h Vu0CopyVectorXYZ
 * (lqc2 vf1,d; lqc2 vf2,s; vaddx.xyz vf1,vf2,vf0x; sqc2 vf1,d) is spelled with mwcc
 * VU0 intrinsics on file-scope extern vf0/vf1/vf2 bindings (no .bss).
 * - the asm block was a scheduling barrier: zero-word basic-block splits
 *   (`if (p) { p = (T)(s32)(u32)p; }`, live assignment) at helper entry and after the
 *   else-branch copy in SetRot (on x) stand in for it;
 * - volatile loads keep the d-then-s lqc2 order. */
#pragma always_inline on
typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vz148ae0 asm("vf0");
extern u128 va148ae0 asm("vf1");
extern u128 vb148ae0 asm("vf2");

static inline void CopyXYZ(void *d, void *s)
{
    u128 *pd = (u128 *)d;
    u128 *ps = (u128 *)s;
    if (pd) { pd = (u128 *)(s32)(u32)pd; }
    if (ps) { ps = (u128 *)(s32)(u32)ps; }
    va148ae0 = *(volatile u128 *)pd;
    vb148ae0 = *(volatile u128 *)ps;
    va148ae0 = _vaddbc(va148ae0, 0xE, vb148ae0, vz148ae0, 8);
    *pd = va148ae0;
}

typedef union V4_148ae0 {
    struct {
        f32 x, y, z;
        s32 w;
    } v;
    unsigned __int128 q;
} __attribute__((aligned(16))) V4_148ae0;

typedef struct M4_148ae0 {
    V4_148ae0 r[4];
} M4_148ae0;

typedef struct Xf148ae0 {
    u8 pad0[0x14];
    V4_148ae0 *volatile pos;
    V4_148ae0 *volatile rot;
    V4_148ae0 *scale;
    u8 pad20[9];
    u8 dirty;
    u8 pad2A;
    u8 f2B;
    u8 f2C;
    u8 pad2D[3];
    V4_148ae0 posS;
    V4_148ae0 rotS;
    V4_148ae0 scaleS;
    M4_148ae0 mat;
} Xf148ae0;

static inline void FixW(s32 *w)
{
    if (*w == 0) {
        *w = 1;
    }
}

static inline void SetPos(Xf148ae0 *x, V4_148ae0 *p)
{
    V4_148ae0 *cur = x->pos;

    if (cur == NULL) {
        x->pos = &x->posS;
        x->f2B = 1;
        x->dirty = 1;
        x->f2C = 0;
        *x->pos = *p;
        x->dirty = 1;
    } else if (cur->v.x != p->v.x || cur->v.y != p->v.y || cur->v.z != p->v.z) {
        *x->pos = *p;
        x->dirty = 1;
    }
}

static inline void SetRot(Xf148ae0 *x, V4_148ae0 *r)
{
    V4_148ae0 *cur = x->rot;

    if (cur == NULL) {
        V4_148ae0 *n = &x->rotS;

        x->rot = n;
        if (n != NULL) {
            FixW(&n->v.w);
        }
        x->f2B = 1;
        x->dirty = 1;
        x->f2C = 0;
        x->rot->v.w = 1;
        {
            V4_148ae0 *d = x->rot;
            CopyXYZ(d, r);
        }
        x->dirty = 1;
    } else if (cur->v.x != r->v.x || cur->v.y != r->v.y || cur->v.z != r->v.z) {
        {
            V4_148ae0 *d = x->rot;
            CopyXYZ(d, r);
        }
        if (x) { x = (Xf148ae0 *)(s32)(u32)x; }
        x->dirty = 1;
    }
}

static inline void SetScale(Xf148ae0 *x, V4_148ae0 *s)
{
    V4_148ae0 *cur = x->scale;

    if (cur == NULL) {
        if (s->v.x == 1.0f && s->v.y == 1.0f && s->v.z == 1.0f) {
            return;
        }
        x->scale = &x->scaleS;
        x->f2B = 1;
        x->dirty = 1;
        x->f2C = 0;
        x->scale->q = s->q;
        x->dirty = 1;
    } else if (cur->v.x != s->v.x || cur->v.y != s->v.y || cur->v.z != s->v.z) {
        *x->scale = *s;
        x->dirty = 1;
    }
}

void FrameCopyXform_148ae0(Xf148ae0 *src, Xf148ae0 *dst)
{
    V4_148ae0 p;
    V4_148ae0 r;
    V4_148ae0 s;
    M4_148ae0 m;

    V4_148ae0 *srcPos = src->pos;
    V4_148ae0 *srcRot;
    if (srcPos == NULL) {
        return;
    }
    if (srcPos != NULL) {
        p = *srcPos;
    } else {
        p = src->mat.r[3];
    }
    srcRot = src->rot;
    if (srcRot != NULL) {
        CopyXYZ(&r, srcRot);
    } else {
        r.q = 0;
    }
    if (src->scale != NULL) {
        s = *src->scale;
    } else {
        s.v.w = 0;
        s.v.z = 1.0f;
        s.v.y = 1.0f;
        s.v.x = 1.0f;
    }
    m.r[0].q = src->mat.r[0].q;
    m.r[1].q = src->mat.r[1].q;
    m.r[2].q = src->mat.r[2].q;
    m.r[3].q = src->mat.r[3].q;
    SetPos(dst, &p);
    SetRot(dst, &r);
    SetScale(dst, &s);
    dst->mat.r[0] = m.r[0];
    dst->mat.r[1] = m.r[1];
    dst->mat.r[2] = m.r[2];
    dst->mat.r[3] = m.r[3];
    dst->dirty = 1;
}
