#include "types.h"
#include "libvu0.h"
/* VU0 code as mwcc intrinsics: file-scope VU0 register bindings under vu0_mmi_reg_binding.
 * Only the ACC-destination ops of the inline Vu0MulMatrix2 (vmulax/vmadday/vmaddaz) use the
 * SDK macro Vu0MulMatrixAcc from libvu0.h. Retail's inline-assembly blocks were scheduling
 * barriers; the empty `if (p) { p = launder(p); }` statements below emit no code but keep a
 * basic-block boundary through both scheduling passes, reproducing that order. */
#pragma optimization_level 3
#pragma vu0_mmi_reg_binding on
extern unsigned __int128 vz148ff0 asm("vf0");
extern unsigned __int128 v1_148ff0 asm("vf1");
extern unsigned __int128 v2_148ff0 asm("vf2");
extern unsigned __int128 v3_148ff0 asm("vf3");
extern unsigned __int128 v4_148ff0 asm("vf4");
extern unsigned __int128 v5_148ff0 asm("vf5");
extern unsigned __int128 v6_148ff0 asm("vf6");
extern unsigned __int128 v7_148ff0 asm("vf7");
extern unsigned __int128 v8_148ff0 asm("vf8");
extern unsigned __int128 va148ff0 asm("vf10");
extern unsigned __int128 r20_148ff0 asm("vf20");
extern unsigned __int128 r21_148ff0 asm("vf21");
extern unsigned __int128 r22_148ff0 asm("vf22");
extern unsigned __int128 r23_148ff0 asm("vf23");
extern unsigned __int128 acc148ff0 asm("ACC");
extern float q148ff0 asm("Q");
typedef volatile unsigned __int128 VQ148ff0;
#define SPLIT148ff0(p, T) if (p) { p = (T *)(s32)(u32)p; }

static inline void ScaleLoad(void *v0, void *s0)
{
    VQ148ff0 *v = (VQ148ff0 *)(s32)v0;
    VQ148ff0 *s = (VQ148ff0 *)(s32)s0;
    v = (VQ148ff0 *)(s32)v;
    SPLIT148ff0(s, VQ148ff0)
    va148ff0 = *v;
    v1_148ff0 = s[0];
    v2_148ff0 = s[1];
    v3_148ff0 = s[2];
    v4_148ff0 = s[3];
}

static inline void ScaleMul(void)
{
    v1_148ff0 = _vmulbc(v1_148ff0, 0xF, v1_148ff0, va148ff0, 8);
    v2_148ff0 = _vmulbc(v2_148ff0, 0xF, v2_148ff0, va148ff0, 4);
    v3_148ff0 = _vmulbc(v3_148ff0, 0xF, v3_148ff0, va148ff0, 2);
}

static inline void InvScaleLoad(void *v0, void *s0)
{
    VQ148ff0 *v = (VQ148ff0 *)(u32)v0;
    VQ148ff0 *s = (VQ148ff0 *)(u32)s0;
    v = (VQ148ff0 *)(s32)v;
    va148ff0 = *v;
    v1_148ff0 = s[0];
    v2_148ff0 = s[1];
    v3_148ff0 = s[2];
    v4_148ff0 = s[3];
}

static inline void InvScaleMul(void)
{
    q148ff0 = _vdiv(q148ff0, vz148ff0, 1, va148ff0, 8);
    v1_148ff0 = _vmulf(v1_148ff0, 0xF, v1_148ff0, q148ff0);
    q148ff0 = _vdiv(q148ff0, vz148ff0, 1, va148ff0, 4);
    v2_148ff0 = _vmulf(v2_148ff0, 0xF, v2_148ff0, q148ff0);
    q148ff0 = _vdiv(q148ff0, vz148ff0, 1, va148ff0, 2);
    v3_148ff0 = _vmulf(v3_148ff0, 0xF, v3_148ff0, q148ff0);
}

static inline void StoreMatrix(void *d0)
{
    VQ148ff0 *d = (VQ148ff0 *)(s32)d0;
    d[0] = v1_148ff0;
    d[1] = v2_148ff0;
    d[2] = v3_148ff0;
    d[3] = v4_148ff0;
}

static inline void LoadScaleVec(void *v0)
{
    VQ148ff0 *v = (VQ148ff0 *)(s32)v0;
    v = (VQ148ff0 *)(s32)v;
    va148ff0 = *v;
}

typedef union V4_148ff0 {
    struct {
        f32 x, y, z;
        s32 w;
    } v;
    unsigned __int128 q;
} __attribute__((aligned(16))) V4_148ff0;

typedef struct M4_148ff0 {
    V4_148ff0 r[4];
} M4_148ff0;

typedef struct Xf148ff0 {
    u8 pad0[4];
    struct Xf148ff0 *parent;
    struct Xf148ff0 *child;
    struct Xf148ff0 *next;
    u8 pad10[0xC];
    V4_148ff0 *scale;
    u8 pad20[8];
    s8 f28;
    s8 dirty;
    u8 pad2A;
    s8 f2B;
    u8 pad2C;
    s8 f2D;
    u8 pad2E[0x60 - 0x2E];
    M4_148ff0 local;
    M4_148ff0 world;
} Xf148ff0;

extern void FrameCalcLocalMatrix_149b40(Xf148ff0 *x, M4_148ff0 *m);
extern void MatMul33_13d180(M4_148ff0 *d, M4_148ff0 *a, M4_148ff0 *b);
extern void MtxMulPoint_13c890(V4_148ff0 *d, M4_148ff0 *m, V4_148ff0 *v);
extern void VecMul_13bd40(V4_148ff0 *d, V4_148ff0 *s, V4_148ff0 *v);
extern f32 VecLength_13d4a0(V4_148ff0 *v);

extern void FrameCalcLocalMatrix_149b40(Xf148ff0 *x, M4_148ff0 *m);
extern void MatMul33_13d180(M4_148ff0 *d, M4_148ff0 *a, M4_148ff0 *b);
extern void MtxMulPoint_13c890(V4_148ff0 *d, M4_148ff0 *m, V4_148ff0 *v);
extern void VecMul_13bd40(V4_148ff0 *d, V4_148ff0 *s, V4_148ff0 *v);
extern f32 VecLength_13d4a0(V4_148ff0 *v);

#define XS SPLIT148ff0(x, Xf148ff0)

void FrameCalcWorldMatrix_148ff0(Xf148ff0 *x, M4_148ff0 *out)
{
    M4_148ff0 m;
    M4_148ff0 pw;
    V4_148ff0 ps;
    Xf148ff0 *p;

    if (x->dirty == 0) {
        p = x->parent;
        if (p == NULL) {
            out->r[0].q = x->world.r[0].q;
            out->r[1].q = x->world.r[1].q;
            out->r[2].q = x->world.r[2].q;
            out->r[3].q = x->world.r[3].q;
            return;
        }
        if (x->f28 == 0) {
            while (p != NULL) {
                if (p->dirty != 0) {
                    break;
                }
                p = p->parent;
                if (p == NULL) {
                    out->r[0].q = x->world.r[0].q;
                    out->r[1].q = x->world.r[1].q;
                    out->r[2].q = x->world.r[2].q;
                    out->r[3].q = x->world.r[3].q;
                    return;
                }
            }
        }
    }
    for (p = x->child; p != NULL; p = p->next) {
        p->dirty = 1;
    }
    if (x->f2B == 0) {
        m.r[0].q = x->local.r[0].q;
        m.r[1].q = x->local.r[1].q;
        m.r[2].q = x->local.r[2].q;
        m.r[3].q = x->local.r[3].q;
    } else {
        FrameCalcLocalMatrix_149b40(x, &m);
    }
    if (x->f2D == 0) {
        if (x->parent == NULL) {
            out->r[0].q = m.r[0].q;
            out->r[1].q = m.r[1].q;
            out->r[2].q = m.r[2].q;
            out->r[3].q = m.r[3].q;
            x->world.r[0].q = m.r[0].q;
            x->world.r[1].q = m.r[1].q;
            x->world.r[2].q = m.r[2].q;
            x->world.r[3].q = m.r[3].q;
        } else {
            FrameCalcWorldMatrix_148ff0(x->parent, &pw);
            {
                VQ148ff0 *a = (VQ148ff0 *)(s32)&pw;
                VQ148ff0 *b;

                SPLIT148ff0(a, VQ148ff0)
                b = (VQ148ff0 *)(s32)&m;

                v5_148ff0 = b[0];
                v1_148ff0 = a[0];
                v2_148ff0 = a[1];
                v3_148ff0 = a[2];
                v4_148ff0 = a[3];
                Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf5);
                r20_148ff0 = _vmaddbc(r20_148ff0, 0xF, acc148ff0, v4_148ff0, v5_148ff0, 1);
                XS
                v6_148ff0 = b[1];
                v7_148ff0 = b[2];
                v8_148ff0 = b[3];
                x->world.r[0].q = r20_148ff0;
                out->r[0].q = r20_148ff0;
                Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf6);
                r21_148ff0 = _vmaddbc(r21_148ff0, 0xF, acc148ff0, v4_148ff0, v6_148ff0, 1);
                Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf7);
                r22_148ff0 = _vmaddbc(r22_148ff0, 0xF, acc148ff0, v4_148ff0, v7_148ff0, 1);
                XS
                x->world.r[1].q = r21_148ff0;
                out->r[1].q = r21_148ff0;
                Vu0MulMatrixAcc(xyzw, vf1, vf2, vf3, vf8);
                r23_148ff0 = _vmaddbc(r23_148ff0, 0xF, acc148ff0, v4_148ff0, v8_148ff0, 1);
                XS
                x->world.r[2].q = r22_148ff0;
                out->r[2].q = r22_148ff0;
                x->world.r[3].q = r23_148ff0;
                out->r[3].q = r23_148ff0;
            }
        }
    } else {
        if (x->parent == NULL) {
            if (x->scale != NULL) {
                ScaleLoad(x->scale, &m);
                XS
                ScaleMul();
                XS
                StoreMatrix(&x->world);
            } else {
                x->world.r[0].q = m.r[0].q;
                x->world.r[1].q = m.r[1].q;
                x->world.r[2].q = m.r[2].q;
                x->world.r[3].q = m.r[3].q;
            }
            out->r[0].q = x->world.r[0].q;
            out->r[1].q = x->world.r[1].q;
            out->r[2].q = x->world.r[2].q;
            out->r[3].q = x->world.r[3].q;
        } else {
            FrameCalcWorldMatrix_148ff0(x->parent, &pw);
            ps.v.w = 0;
            ps.v.x = VecLength_13d4a0(&pw.r[0]);
            ps.v.y = VecLength_13d4a0(&pw.r[1]);
            ps.v.z = VecLength_13d4a0(&pw.r[2]);
            InvScaleLoad(&ps, &pw);
            XS
            InvScaleMul();
            XS
            StoreMatrix(&x->world);
            if (x->scale != NULL) {
                VecMul_13bd40(&ps, &ps, x->scale);
            }
            MatMul33_13d180(&x->world, &x->world, &m);
            LoadScaleVec(&ps);
            XS
            v1_148ff0 = x->world.r[0].q;
            v2_148ff0 = x->world.r[1].q;
            v3_148ff0 = x->world.r[2].q;
            v4_148ff0 = x->world.r[3].q;
            XS
            ScaleMul();
            XS
            x->world.r[0].q = v1_148ff0;
            x->world.r[1].q = v2_148ff0;
            x->world.r[2].q = v3_148ff0;
            x->world.r[3].q = v4_148ff0;
            XS
            {
                V4_148ff0 *p0 = &x->world.r[3];
                M4_148ff0 *p1 = &pw;

                SPLIT148ff0(p0, V4_148ff0)
                MtxMulPoint_13c890(p0, p1, &m.r[3]);
            }
            out->r[0].q = x->world.r[0].q;
            out->r[1].q = x->world.r[1].q;
            out->r[2].q = x->world.r[2].q;
            out->r[3].q = x->world.r[3].q;
        }
    }
    x->dirty = 0;
}
