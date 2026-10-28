/* PORT REPLACEMENT for game/include/vu0inline.h (this directory is ahead of
 * game/include on the include path).  Same helper names and signatures; each
 * body is the original COP2 sequence, instruction for instruction, on the
 * VU0 model in port/vu0.h -- so the vf/ACC/Q/GPR side effects the original
 * left behind are left behind here too (each helper takes the caller's
 * register file, `&rg_vu0` at the call: stage vu0frame).  Tests: tests/test_vu0.c. */
#ifndef VU0INLINE_H
#define VU0INLINE_H

#include "types.h"
#include "port/vu0.h"

/* d.xyz = s.xyz (d.w kept) */
static inline void Vu0CopyVectorXYZ_f(rg_vu0_state *rg_vu0_p_, void *d, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_lqc2(1, d);                                         /* lqc2 vf1, 0(d) */
    rg_vu0_lqc2(2, s);                                         /* lqc2 vf2, 0(s) */
    rg_vu0_fmac(RG_VADD, RG_XYZ, 1, 2, 0, RG_BC_X);            /* vaddx.xyz vf1, vf2, vf0x */
    rg_vu0_sqc2(1, d);                                         /* sqc2 vf1, 0(d) */
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* d = (0,0,0,1) */
static inline void Vu0UnitVector_f(rg_vu0_state *rg_vu0_p_, void *d)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_sqc2(0, d);                                         /* sqc2 vf0, 0(d) */
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* d = (s.x, s.y, s.z, 1) */
static inline void Vu0CopyVectorW1_f(rg_vu0_state *rg_vu0_p_, void *d, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_lqc2(4, s);                                         /* lqc2 vf4, 0(s) */
    rg_vu0_fmac(RG_VMUL, RG_W, 4, 0, 0, RG_BC_NONE);           /* vmul.w vf4, vf0, vf0 */
    rg_vu0_sqc2(4, d);                                         /* sqc2 vf4, 0(d) */
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* return v.x*v.x + v.y*v.y + v.z*v.z  (clobbers $a1, as the original did) */
static inline f32 Vu0SquareLength_f(rg_vu0_state *rg_vu0_p_, void *v)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_lqc2(4, v);                                         /* lqc2 vf4, 0(v) */
    rg_vu0_fmac(RG_VMUL, RG_XYZ, 4, 4, 4, RG_BC_NONE);         /* vmul.xyz vf4, vf4, vf4 */
    rg_vu0_fmac(RG_VADD, RG_X, 4, 4, 4, RG_BC_Y);              /* vaddy.x vf4, vf4, vf4y */
    rg_vu0_fmac(RG_VADD, RG_X, 4, 4, 4, RG_BC_Z);              /* vaddz.x vf4, vf4, vf4z */
    rg_vu0_qmfc2(RG_GPR_a1, 4);                                /* qmfc2.ni a1, vf4 */
    return rg_vu0_mtc1(RG_GPR_a1);                             /* mtc1 a1, r */
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* dst = p1 * t + p2 * (1 - t)   (Sony sceVu0InterVector; computed as
   p2 + (p1 - p2) * t, exactly as the VU sequence does) */
static inline void Vu0InterVector_f(rg_vu0_state *rg_vu0_p_, void *dst, void *p1, void *p2, f32 t)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_lqc2(4, p2);                                        /* lqc2 vf4, 0(p2) */
    rg_vu0_lqc2(5, p1);                                        /* lqc2 vf5, 0(p1) */
    rg_vu0_mfc1(RG_GPR_t0, t);                                 /* mfc1 t0, t */
    rg_vu0_qmtc2(RG_GPR_t0, 6);                                /* qmtc2.ni t0, vf6 */
    rg_vu0_fmac(RG_VSUB, RG_XYZW, 7, 5, 4, RG_BC_NONE);        /* vsub.xyzw vf7, vf5, vf4 */
    rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 0, RG_BC_W);          /* vmulaw.xyzw ACC, vf4, vf0w */
    rg_vu0_fmac(RG_VMADD, RG_XYZW, 8, 7, 6, RG_BC_X);          /* vmaddx.xyzw vf8, vf7, vf6x */
    rg_vu0_sqc2(8, dst);                                       /* sqc2 vf8, 0(dst) */
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* d = s with rows 0..2 scaled by v.x, v.y, v.z (row 3 copied) */
static inline void Vu0ScaleMatrix_f(rg_vu0_state *rg_vu0_p_, void *d, void *v, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_lqc2(10, v);
    rg_vu0_lqc2(1, (char *)s + 0x00);
    rg_vu0_lqc2(2, (char *)s + 0x10);
    rg_vu0_lqc2(3, (char *)s + 0x20);
    rg_vu0_lqc2(4, (char *)s + 0x30);
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 1, 1, 10, RG_BC_X);          /* vmulx.xyzw vf1, vf1, vf10x */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 2, 2, 10, RG_BC_Y);          /* vmuly.xyzw vf2, vf2, vf10y */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 3, 3, 10, RG_BC_Z);          /* vmulz.xyzw vf3, vf3, vf10z */
    rg_vu0_sqc2(1, (char *)d + 0x00);
    rg_vu0_sqc2(2, (char *)d + 0x10);
    rg_vu0_sqc2(3, (char *)d + 0x20);
    rg_vu0_sqc2(4, (char *)d + 0x30);
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* d = s with rows 0..2 divided by v.x, v.y, v.z (row 3 copied) */
static inline void Vu0InvScaleMatrix_f(rg_vu0_state *rg_vu0_p_, void *d, void *v, void *s)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    rg_vu0_lqc2(10, v);
    rg_vu0_lqc2(1, (char *)s + 0x00);
    rg_vu0_lqc2(2, (char *)s + 0x10);
    rg_vu0_lqc2(3, (char *)s + 0x20);
    rg_vu0_lqc2(4, (char *)s + 0x30);
    rg_vu0_div(0, RG_BC_W, 10, RG_BC_X);                       /* vdiv Q, vf0w, vf10x */
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 1, 1, RG_FT_Q, RG_BC_NONE);  /* vmulq.xyzw vf1, vf1, Q */
    rg_vu0_div(0, RG_BC_W, 10, RG_BC_Y);
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 2, 2, RG_FT_Q, RG_BC_NONE);
    rg_vu0_div(0, RG_BC_W, 10, RG_BC_Z);
    rg_vu0_fmac(RG_VMUL, RG_XYZW, 3, 3, RG_FT_Q, RG_BC_NONE);
    rg_vu0_sqc2(1, (char *)d + 0x00);
    rg_vu0_sqc2(2, (char *)d + 0x10);
    rg_vu0_sqc2(3, (char *)d + 0x20);
    rg_vu0_sqc2(4, (char *)d + 0x30);
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* vu0frame (docs/NATIVE-CPU.md section 4): the helpers run on the CALLER's
   register file, as they did on the shared one */
#define Vu0CopyVectorXYZ(...) Vu0CopyVectorXYZ_f(&rg_vu0, __VA_ARGS__)
#define Vu0UnitVector(...) Vu0UnitVector_f(&rg_vu0, __VA_ARGS__)
#define Vu0CopyVectorW1(...) Vu0CopyVectorW1_f(&rg_vu0, __VA_ARGS__)
#define Vu0SquareLength(...) Vu0SquareLength_f(&rg_vu0, __VA_ARGS__)
#define Vu0InterVector(...) Vu0InterVector_f(&rg_vu0, __VA_ARGS__)
#define Vu0ScaleMatrix(...) Vu0ScaleMatrix_f(&rg_vu0, __VA_ARGS__)
#define Vu0InvScaleMatrix(...) Vu0InvScaleMatrix_f(&rg_vu0, __VA_ARGS__)

#endif
