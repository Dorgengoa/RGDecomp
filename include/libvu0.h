/* PORT REPLACEMENT for include/libvu0.h (the s88m de-asm VU0 macros; the
 * header first appears in the decomp at d784320c -- the 2efa6b43 snapshot
 * game/ is built from has no user yet).  Same macro names, same parameters
 * (register TOKENS such as vf5 / xyzw / x / t0, glued with ## exactly as the
 * original glues `col##x`); each expands to the original instruction span on
 * the VU0 model in port/vu0.h, so register-file side effects match.
 *
 * The C around these macros in the decomp keeps its values in VU registers
 * through `#pragma vu0_mmi_reg_binding` + mwcc VU0 intrinsics (_vmul,
 * _vmaddbc, ... on `extern u128 x asm("vfN")`).  That binding layer is NOT
 * part of this header: when a snapshot with such users is ingested, the bound
 * variables must map onto rg_vu0.vf[N] / rg_vu0.acc (docs/PORT-HEADERS.md).
 *
 * Tests: tests/test_vu0.c (one or more known-vector checks per macro). */
#ifndef LIBVU0_H
#define LIBVU0_H

#include "port/vu0.h"

#define RG__VF(r) RG_VF_##r
#define RG__M(m) RG_MASK_##m
#define RG__G(g) RG_GPR_##g

/* ---- qword loads / stores ------------------------------------------------ */

/* *d = (0,0,0,1): sqc2 vf0, 0(d) */
#define Vu0UnitVector(d) do { rg_vu0_sqc2(0, (void *)(d)); } while (0)

/* *d = *s through a1: lq a1,0(s); sq a1,0(d) */
#define Vu0CopyVector(d, s) \
    do { rg_vu0_lq(RG_GPR_a1, (const void *)(s)); rg_vu0_sq(RG_GPR_a1, (void *)(d)); } while (0)

/* swap two qwords through a1/a2 */
#define Vu0SwapVector(a, b) \
    do { rg_vu0_lq(RG_GPR_a1, (const void *)(a)); rg_vu0_lq(RG_GPR_a2, (const void *)(b)); \
         rg_vu0_sq(RG_GPR_a1, (void *)(b)); rg_vu0_sq(RG_GPR_a2, (void *)(a)); } while (0)

/* 4-qword copy through a1/a2/a3/t0 (all four loads, then the stores) */
#define Vu0CopyMatrix(d, s) \
    do { const char *rg_s_ = (const char *)(s); char *rg_d_ = (char *)(d); \
         rg_vu0_lq(RG_GPR_a1, rg_s_ + 0x00); rg_vu0_lq(RG_GPR_a2, rg_s_ + 0x10); \
         rg_vu0_lq(RG_GPR_a3, rg_s_ + 0x20); rg_vu0_lq(RG_GPR_t0, rg_s_ + 0x30); \
         rg_vu0_sq(RG_GPR_a1, rg_d_ + 0x00); rg_vu0_sq(RG_GPR_a2, rg_d_ + 0x10); \
         rg_vu0_sq(RG_GPR_a3, rg_d_ + 0x20); rg_vu0_sq(RG_GPR_t0, rg_d_ + 0x30); } while (0)

/* ---- scalar moves (FPR/Q <-> VU0) ---------------------------------------- */

/* mfc1 gpr, f; nop; qmtc2.ni gpr, vf  -> vf.x = f (yzw = the GPR's upper bits) */
#define Vu0ScaleF(gpr, f, vf) \
    do { rg_vu0_mfc1(RG__G(gpr), (f)); rg_vu0_qmtc2(RG__G(gpr), RG__VF(vf)); } while (0)

/* r = sqrt(vf4.fld): vsqrt Q, vf4<fld>; vwaitq; cfc2.ni a1, vi22; mtc1 a1, r */
#define Vu0Length(r, fld) \
    do { rg_vu0_sqrt(4, RG_BC_##fld); rg_vu0_cfc2(RG_GPR_a1, 22); (r) = rg_vu0_mtc1(RG_GPR_a1); } while (0)

/* ---- ACC-destination heads ----------------------------------------------- */

/* vmulax.mask ACC, a, bx */
#define Vu0MulAccX(mask, a, b) rg_vu0_fmac(RG_VMULA, RG__M(mask), 0, RG__VF(a), RG__VF(b), RG_BC_X)

/* vmulax.mask ACC, m0, colx; vmadday.mask ACC, m1, coly */
#define Vu0ApplyMatrix3Acc(mask, m0, m1, col) \
    do { rg_vu0_fmac(RG_VMULA, RG__M(mask), 0, RG__VF(m0), RG__VF(col), RG_BC_X); \
         rg_vu0_fmac(RG_VMADDA, RG__M(mask), 0, RG__VF(m1), RG__VF(col), RG_BC_Y); } while (0)

/* vmulax ACC,m0,colx; vmadday ACC,m1,coly; vmaddaz ACC,m2,colz */
#define Vu0MulMatrixAcc(mask, m0, m1, m2, col) \
    do { rg_vu0_fmac(RG_VMULA, RG__M(mask), 0, RG__VF(m0), RG__VF(col), RG_BC_X); \
         rg_vu0_fmac(RG_VMADDA, RG__M(mask), 0, RG__VF(m1), RG__VF(col), RG_BC_Y); \
         rg_vu0_fmac(RG_VMADDA, RG__M(mask), 0, RG__VF(m2), RG__VF(col), RG_BC_Z); } while (0)

/* vadda.xyzw ACC, a, b */
#define Vu0AddAcc(a, b) rg_vu0_fmac(RG_VADDA, RG_XYZW, 0, RG__VF(a), RG__VF(b), RG_BC_NONE)

/* vopmula.xyz ACC, a, b */
#define Vu0OuterProductAcc(a, b) rg_vu0_opmula(RG__VF(a), RG__VF(b))

/* vmulaw.xyzw ACC, vf4, vf0w */
#define Vu0InterVectorAcc() rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 0, RG_BC_W)

/* ---- routine-specific spans ---------------------------------------------- */

/* lqc2 vf4, 0(p2) */
#define Vu0InterVectorLoad(p2) rg_vu0_lqc2(4, (const void *)(p2))

/* mfc1 a1, s; mfc1 a2, t */
#define Vu0BlendVectorF(s, t) do { rg_vu0_mfc1(RG_GPR_a1, (s)); rg_vu0_mfc1(RG_GPR_a2, (t)); } while (0)
/* qmtc2.ni a1, vf8; qmtc2.ni a2, vf9; vmulax.xyzw ACC, vf4, vf8x */
#define Vu0BlendVectorAcc() \
    do { rg_vu0_qmtc2(RG_GPR_a1, 8); rg_vu0_qmtc2(RG_GPR_a2, 9); \
         rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 8, RG_BC_X); } while (0)

/* mfc1 a1..a3, fa..fc */
#define Vu0BlendVector3F(fa, fb, fc) \
    do { rg_vu0_mfc1(RG_GPR_a1, (fa)); rg_vu0_mfc1(RG_GPR_a2, (fb)); rg_vu0_mfc1(RG_GPR_a3, (fc)); } while (0)
/* qmtc2.ni a1..a3 -> vf8..vf10; vmulax ACC,vf4,vf8x; vmaddax ACC,vf5,vf9x */
#define Vu0BlendVector3Acc() \
    do { rg_vu0_qmtc2(RG_GPR_a1, 8); rg_vu0_qmtc2(RG_GPR_a2, 9); rg_vu0_qmtc2(RG_GPR_a3, 10); \
         rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 8, RG_BC_X); \
         rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 5, 9, RG_BC_X); } while (0)

/* vmaddw.xyzw vf26, vf4, vf0w; sqc2 vf26, 0(d) */
#define Vu0StoreAccW26(d) \
    do { rg_vu0_fmac(RG_VMADD, RG_XYZW, 26, 4, 0, RG_BC_W); rg_vu0_sqc2(26, (void *)(d)); } while (0)

/* vsqrt Q, vf8x; vsub.w vf, vf0, vf0; vwaitq */
#define Vu0OrthoNormalSqrt(vf) \
    do { rg_vu0_sqrt(8, RG_BC_X); rg_vu0_fmac(RG_VSUB, RG_W, RG__VF(vf), 0, 0, RG_BC_NONE); } while (0)

/* addiu a2,m,0x10; addiu a3,m,0x20; addiu t0,m,0x30; lqc2 vf1..vf4
   (the GPR temps hold host pointers: 32-bit build only, like the EE) */
#define Vu0InversMatrixLoad(m) \
    do { const char *rg_m_ = (const char *)(m); \
         rg_vu0_gpr_setp(RG_GPR_a2, rg_m_ + 0x10); rg_vu0_gpr_setp(RG_GPR_a3, rg_m_ + 0x20); \
         rg_vu0_gpr_setp(RG_GPR_t0, rg_m_ + 0x30); \
         rg_vu0_lqc2(1, rg_m_); rg_vu0_lqc2(2, rg_m_ + 0x10); \
         rg_vu0_lqc2(3, rg_m_ + 0x20); rg_vu0_lqc2(4, rg_m_ + 0x30); } while (0)
/* vdiv Q,vf0w,vf9x; qmfc2.ni a1,vf9; mtc1 a1,r  -> r = vf9.x, Q = 1/vf9.x */
#define Vu0InversMatrixDet(r) \
    do { rg_vu0_div(0, RG_BC_W, 9, RG_BC_X); rg_vu0_qmfc2(RG_GPR_a1, 9); (r) = rg_vu0_mtc1(RG_GPR_a1); } while (0)

/* vf31 = (1,1,1,1): vsub.xyzw vf31,vf31,vf31; vaddw.xyzw vf31,vf31,vf0w */
#define Vu0PushApartOne() \
    do { rg_vu0_fmac(RG_VSUB, RG_XYZW, 31, 31, 31, RG_BC_NONE); \
         rg_vu0_fmac(RG_VADD, RG_XYZW, 31, 31, 0, RG_BC_W); } while (0)
/* mfc1 a3,a; mfc1 t0,b; qmtc2.ni a3,vf12; qmtc2.ni t0,vf13;
   vadday.x ACC,vf2,vf2y; vmaddz.x vf6,vf31,vf2z */
#define Vu0PushApartLen(a, b) \
    do { rg_vu0_mfc1(RG_GPR_a3, (a)); rg_vu0_mfc1(RG_GPR_t0, (b)); \
         rg_vu0_qmtc2(RG_GPR_a3, 12); rg_vu0_qmtc2(RG_GPR_t0, 13); \
         rg_vu0_fmac(RG_VADDA, RG_X, 0, 2, 2, RG_BC_Y); \
         rg_vu0_fmac(RG_VMADD, RG_X, 6, 31, 2, RG_BC_Z); } while (0)
/* vrsqrt Q, vf12x, vf6x; vsub.x vf14, vf31, vf13 */
#define Vu0PushApartRsqrt() \
    do { rg_vu0_rsqrt(12, RG_BC_X, 6, RG_BC_X); \
         rg_vu0_fmac(RG_VSUB, RG_X, 14, 31, 13, RG_BC_NONE); } while (0)
/* vsubq.x vf20, vf31, Q */
#define Vu0PushApartSubQ() rg_vu0_fmac(RG_VSUB, RG_X, 20, 31, RG_FT_Q, RG_BC_NONE)

/* sin/cos ACC spans of FUN_001cbfb0 */
#define Vu0SinCosAccR() \
    do { rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 4, 5, RG_BC_Y); \
         rg_vu0_fmac(RG_VMSUBA, RG_XYZW, 0, 8, 5, RG_BC_Z); \
         rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 8, 5, RG_BC_Z); \
         rg_vu0_fmac(RG_VMSUBA, RG_XYZW, 0, 4, 5, RG_BC_Y); } while (0)
#define Vu0SinCosAccP0() rg_vu0_fmac(RG_VMULA, RG_XYZW, 0, 9, 12, RG_BC_NONE)
#define Vu0SinCosAccP1() \
    do { rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 11, 13, RG_BC_NONE); \
         rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 10, 13, RG_BC_NONE); \
         rg_vu0_fmac(RG_VMADDA, RG_XYZW, 0, 4, 5, RG_BC_W); } while (0)

#endif /* LIBVU0_H */
