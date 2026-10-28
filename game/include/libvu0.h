#ifndef LIBVU0_H
#define LIBVU0_H

/* libvu0.h -- SDK VU0 macros, modelled on Sony's libvu0 inline-asm routines.
 *
 * Permitted by the user ruling of 2026-10-04 #2 (build/s88m/DEASM_BRIEF.md):
 * ONLY sequences proven to have no C emitter in mwccps2 -- ACC-destination
 * ops, cfc2.ni Q reads, bare mfc1 float->GPR moves, unplaceable volatile-GPR
 * temps, SDK scheduling barriers, vf26+ registers. One Sony-style macro per
 * routine span, SHORTEST span that contains the blocked op(s); every
 * instruction C can emit stays C in the function body (vf bindings under
 * `#pragma vu0_mmi_reg_binding on` + mwcc VU0 intrinsics). Each macro names
 * its blocked op(s) and the proof NOTES path (build/s88m/<lane>/NOTES.md).
 *
 * Spelling: the `asm volatile { ... }` block form, register tokens passed as
 * macro parameters (vf5, xyzw, ...) and glued with ## for broadcast fields
 * (col##x -> vf5x). No macro needs the `__asm__("..." : operands)` form:
 * Vu0UnitVector takes an address expression through a block-local pointer
 * (`void *vu0_d = (d)`), object-identical to the old "r" operand form; the
 * old "m" form of Vu0InterVectorLoad is likewise identical in block form
 * (build/s88m/vu0h/NOTES.md).
 *
 * Users (installed src, s88m vu0h audit 2026-10-04):
 *   Vu0UnitVector         DynColliderEllipsoidPushSegmentMaybe_166ba0
 *   Vu0CopyVector         VecCopy_1cbe30
 *   Vu0SwapVector         Swap128_1cb4f0
 *   Vu0CopyMatrix         MtxCopy_1cbde0
 *   Vu0ScaleF             VecScaleToLength_1cb510 1cbbc0 1cbbf0 1cbc60 1cbc80 1cbca0 (vf5),
 *                         VecLerpPoint_1cbac0 1cbaf0 1cbb20 (vf6), MatFromPosScale_1cb2b0 (vf9),
 *                         AnimKeyEvalScalarLinear_154a10 00155180 001559e0 00155bf0 (t0, vf6)
 *   Vu0Length             MatDecomposeScaleRotPos_1cad20 1cb3f0 1cb420 1cb490 1cb4c0
 *   Vu0MulAccX            BoxToCenterExtentsVu0Maybe_14ff40, VecLerp_1cbb20 (xyzw), VecLerpPoint_1cbac0 1cbaf0 (xyz)
 *   Vu0ApplyMatrix3Acc    BoxTransformExtentsVu0Maybe_14fed0 001cb5d0 001cb640 001cb910
 *   Vu0MulMatrixAcc       FrameCalcWorldMatrix_148ff0 0014fed0 (vf1-3), MatMul_1cb700 1cb780 1cb7f0
 *                         1cb8e0 1cb940 (vf4-6), BoxToCenterExtentsVu0Maybe_14ff40 0016c1a0 (vf10-12)
 *   Vu0AddAcc             BoxTransformExtentsVu0Maybe_14fed0
 *   Vu0StoreAccW26        BoxTransformExtentsVu0Maybe_14fed0
 *   Vu0OuterProductAcc    CollTriTransform_16c1a0 001cb300 1cb600 1cb640 1cb970 1cb9c0 1cb9f0
 *   Vu0InterVectorLoad    AnimKeyBlendMaterial_1559e0 00155bf0
 *   Vu0InterVectorAcc     AnimKeyEvalScalarLinear_154a10 00155180 001559e0 00155bf0
 *   Vu0BlendVectorF/Acc   VecLinearCombine_1cb8b0
 *   Vu0BlendVector3F/Acc  VecWeightedSum3_1cb860
 *   Vu0OrthoNormalSqrt    MatOrthonormalizeY_1cb300
 *   Vu0InversMatrixLoad/Det MtxInverseAffine_1cb640
 *   Vu0PushApart*         DynClothSolveSpring_16a480 00185450 00364740
 *   Vu0SinCosAcc*         VecSinCos_1cbfb0
 */

/* ---- qword loads / stores ------------------------------------------------ */

/* Vu0UnitVector(d): *d = (0,0,0,1) via `sqc2 vf0, 0(d)` (Sony libvu0 style).
 * Blocked op: the SDK asm SCHEDULING BARRIER. In C the store is
 * `*(__int128 *)d = vf0` and the block boundary after it costs one word
 * (dividefix nop after div.s, or a 0x108 pcode such as vnop); only an asm
 * statement sets the block flags (0x80) that stop the pcode merge and make
 * dividefix skip the block. Proof: build/s88m/div1, div2, div3 NOTES.md;
 * user build/s88m/div4/NOTES.md. d may be any address expression (&local):
 * it is held in a block-local pointer, as the asm block takes only names. */
#define Vu0UnitVector(d) do { void *vu0_d = (d); asm volatile { sqc2 vf0, 0(vu0_d) } } while (0)

/* Vu0CopyVector(d, s): *d = *s as Sony's sceVu0CopyVector
 * (`lq $5,0(s); sq $5,0(d)`; this build's temp is $5 = a1, not the SDK's $6).
 * Blocked op: the hard-coded volatile a1 lq/sq temp -- in C the temp takes
 * first-fit v1 (2 bad). Proof: build/s88m/lqa1, lqa2 NOTES.md; build/s88m/lqm. */
#define Vu0CopyVector(d, s) asm volatile { lq a1, 0(s); sq a1, 0(d) }

/* Vu0SwapVector(a, b): swap two qwords through the hard-coded temps a1/a2:
 * `lq a1,0(a); lq a2,0(b); sq a1,0(b); sq a2,0(a)`. The a1 clobber makes
 * mwcc move b out of a1 (retail's entry `daddu v1,a1`). Blocked op: the
 * hard-coded volatile a1/a2 temps -- pure C best = retail + 1 dead daddu.
 * Proof: build/s88m/lqa1, lqa2 NOTES.md; build/s88m/lqm. */
#define Vu0SwapVector(a, b) asm volatile { lq a1, 0(a); lq a2, 0(b); sq a1, 0(b); sq a2, 0(a) }

/* Vu0CopyMatrix(d, s): 4-qword copy as Sony's sceVu0CopyMatrix (4 lq then
 * 4 sq; this build's temps are a1/a2/a3/t0, not the SDK's $6-$9). The a1
 * clobber makes mwcc move s out of a1 (retail's entry `daddu v1,a1`).
 * Blocked op: the hard-coded volatile temps -- pure C best = retail + 1 dead
 * daddu. Proof: build/s88m/lqa1, lqa2 NOTES.md; build/s88m/lqm. */
#define Vu0CopyMatrix(d, s) \
    asm volatile { lq a1, 0x0(s); lq a2, 0x10(s); lq a3, 0x20(s); lq t0, 0x30(s); \
                   sq a1, 0x0(d); sq a2, 0x10(d); sq a3, 0x20(d); sq t0, 0x30(d) }

/* ---- scalar moves (FPR/Q <-> VU0) ---------------------------------------- */

/* Vu0ScaleF(gpr, f, vf): load the float scalar f into vf.x, the scalar
 * prologue of the Sony-style libvu0 routines (sceVu0ScaleVector /
 * ScaleVectorXYZ / ScaleLength: vf5; sceVu0InterVector t: vf6; the scale
 * matrix routine MatFromPosScale_1cb2b0: vf9): `mfc1 gpr, f; nop; qmtc2.ni gpr, vf`,
 * gpr = the routine's hard-coded temp (t0, or a1 once the source pointer is
 * dead; the a1 clobber also yields retail's entry `daddu v1,a1`). The lqc2 /
 * vmulx / vrsqrt / vmulq / sqc2 stay C (vf bindings + intrinsics).
 * Blocked op: the bare mfc1 float->GPR->qmtc2 move through a hard-coded
 * volatile GPR (C gives cvt.w.s or a stack pun, temp from first-fit).
 * Proof: build/s88m/mfc1, mfc2, mfc3, 1551, 1cb2 NOTES.md; users
 * build/s88m/mfcm, lqm, acc2, acc5, acc8, acc9 NOTES.md. */
#define Vu0ScaleF(gpr, f, vf) asm volatile { mfc1 gpr, f; nop; qmtc2.ni gpr, vf }

/* Vu0Length(r, fld): f32 r = sqrt(vf4.fld) -- the Q tail of Sony-style
 * Vu0Length: `vsqrt Q, vf4<fld>; vwaitq; cfc2.ni a1, vi22; mtc1 a1, r`.
 * The lqc2/vmul/vadd feed into vf4 stays C (bound vf4 + _vmul/_vaddbc).
 * Blocked ops: `cfc2.ni` (every C read of a Q binding emits cfc2.i; no codegen
 * site emits plain cfc2), the vsqrt (DCE'd at -O4 when Q is only read into a
 * GPR) and the hard-coded volatile a1 temp (the clobber also yields retail's
 * entry `daddu v0,a1` in MatDecomposeScaleRotPos_1cad20). Proof: build/s88m/cfq1, cfq2, 1cae
 * NOTES.md; users build/s88m/vlen/NOTES.md. */
#define Vu0Length(r, fld) \
    asm volatile { vsqrt Q, vf4##fld; vwaitq; cfc2.ni a1, vi22; mtc1 a1, r }

/* ---- ACC-destination heads (vmula / vmadda family) ----------------------- */
/* Blocked ops for this whole group: ACC-destination ops (vmula*, vmadda*,
 * vadda*, vopmula) have no C emitter in any mwcc build. The closing op that
 * reads ACC (vmaddw / vmaddz / vmsubx / vopmsub ...) stays C: the intrinsic
 * (_vmaddbc, _vmsubbc, _vopmsub) on a read-only `extern u128 asm("ACC")`
 * binding. Proof: build/s88m/acc1, 148f, 1552 NOTES.md. mask = xyz / xyzw
 * token; m0.. / a / b / col = vf register tokens. */

/* Vu0MulAccX(mask, a, b): `vmulax.mask ACC, a, bx` -- one-row head: the
 * `a*bx - c*bx` pair of BoxToCenterExtentsVu0Maybe_14ff40 (acc7) and the ACC part of Sony's
 * sceVu0InterVector in its `vaddw.x vf7,vf0,vf0w; vsub.x vf8,vf7,vf6` form
 * (t in vf6x, Vu0MulAccX(xyzw|xyz, vf4, vf6); acc8, acc9). */
#define Vu0MulAccX(mask, a, b) asm volatile { vmulax.mask ACC, a, b##x }

/* Vu0ApplyMatrix3Acc(mask, m0, m1, col): two-row head of a Sony-style 3-row
 * apply (sceVu0ApplyMatrix on a 3x3 / rotation part, InversMatrix tail):
 * `vmulax.mask ACC, m0, colx; vmadday.mask ACC, m1, coly`; the closing
 * `vmaddz.mask vfD, m2, colz` stays C. Users: acc6, acc7 NOTES.md. */
#define Vu0ApplyMatrix3Acc(mask, m0, m1, col) \
    asm volatile { vmulax.mask ACC, m0, col##x; vmadday.mask ACC, m1, col##y }

/* Vu0MulMatrixAcc(mask, m0, m1, m2, col): three-row head of one column of
 * Sony-style sceVu0MulMatrix / sceVu0ApplyMatrix (matrix rows m0..m3 times
 * column vector col): `vmulax ACC,m0,colx; vmadday ACC,m1,coly; vmaddaz
 * ACC,m2,colz`; the closing `vmaddw vfD,m3,colw` (or vf0w) and the sqc2s stay
 * C. Rows vf1-3 (Vu0MulMatrix2, FrameCalcWorldMatrix_148ff0 acc3; BoxTransformExtentsVu0Maybe_14fed0), vf4-6
 * (ApplyMatrix leaves, acc6) or vf10-12 (game leaves, acc7). */
#define Vu0MulMatrixAcc(mask, m0, m1, m2, col) \
    asm volatile { vmulax.mask ACC, m0, col##x; vmadday.mask ACC, m1, col##y; vmaddaz.mask ACC, m2, col##z }

/* Vu0AddAcc(a, b): `vadda.xyzw ACC, a, b`; the following vmaddw stays C
 * (mwcc only writes ACC through its own `vaddax ACC,vfT,vf0x` input move).
 * User: BoxTransformExtentsVu0Maybe_14fed0 (acc7). */
#define Vu0AddAcc(a, b) asm volatile { vadda.xyzw ACC, a, b }

/* Vu0OuterProductAcc(a, b): the ACC half of Sony-style sceVu0OuterProduct
 * (cross product): `vopmula.xyz ACC, a, b`. The closing `vopmsub.xyz vfD, b,
 * a` stays C: _vopmsub(old, acc, b, a). _vopmula exists but its result ICEs
 * (Operands.c:791) or is copied out/back via vmaddx/vaddax. Users: acc6, acc7. */
#define Vu0OuterProductAcc(a, b) asm volatile { vopmula.xyz ACC, a, b }

/* Vu0InterVectorAcc(): `vmulaw.xyzw ACC, vf4, vf0w`, the ACC head of Sony's
 * sceVu0InterVector in its retail form `lqc2 vf4,0(p2); lqc2 vf5,0(p1);
 * mfc1 t0,t; nop; qmtc2.ni t0,vf6; vsub vf7,vf5,vf4; vmulaw ACC,vf4,vf0w;
 * vmaddx vf8,vf7,vf6x; sqc2 vf8,0(d)` (t load = Vu0ScaleF(t0, t, vf6); the
 * lqc2s, vsub, vmaddx and sqc2 stay C). Users: acc2, acc5 NOTES.md. */
#define Vu0InterVectorAcc() asm volatile { vmulaw.xyzw ACC, vf4, vf0w }

/* ---- routine-specific spans ---------------------------------------------- */

/* Vu0InterVectorLoad(p2): first word of Sony's sceVu0InterVector asm block,
 * `lqc2 vf4, 0(p2)` (p2 = qword pointer variable).
 * Blocked op: the SDK asm SCHEDULING BARRIER between the `t/f` div.s and the
 * loads: in C the pre-RA list scheduler fills the add.s->div.s stall with the
 * dep-free lqc2 vf4 (3 swaps, every launder/volatile/order spelling); a
 * zero-word split after the div costs dividefix nops and a fall-through
 * boundary needs a word-emitting 0x108 pcode (build/s88m/div1, div2 NOTES.md).
 * Proof: build/s88m/acc5/NOTES.md. (Was `__asm__("lqc2 vf4, %0" : : "m"(*p2))`;
 * the block form is object-identical for both users, build/s88m/vu0h.) */
#define Vu0InterVectorLoad(p2) asm volatile { lqc2 vf4, 0(p2) }

/* Vu0BlendVectorF(s, t) / Vu0BlendVectorAcc(): Sony-style two-scalar blend
 * d = a*s + b*t (`mfc1 a1,s; mfc1 a2,t; lqc2 vf4; lqc2 vf5; qmtc2.ni a1,vf8;
 * qmtc2.ni a2,vf9; vmulax ACC,vf4,vf8x; vmaddx vf9,vf5,vf9x; sqc2`).
 * The two lqc2s (between the halves, filling the mfc1 hazard), the closing
 * vmaddx (_vmaddbc on an ACC binding) and the sqc2 stay C.
 * Blocked ops: bare mfc1 float->GPR->qmtc2 through the hard-coded volatile
 * a1/a2 (the clobber also yields retail's entry `daddu a3,a1; daddu v1,a2`;
 * proof build/s88m/mfc1-3 NOTES.md) and vmulax (ACC-dest; acc1/148f).
 * User: VecLinearCombine_1cb8b0 (build/s88m/acc9/NOTES.md). */
#define Vu0BlendVectorF(s, t) asm volatile { mfc1 a1, s; mfc1 a2, t }
#define Vu0BlendVectorAcc() \
    asm volatile { qmtc2.ni a1, vf8; qmtc2.ni a2, vf9; vmulax.xyzw ACC, vf4, vf8x }

/* Vu0BlendVector3F(fa, fb, fc) / Vu0BlendVector3Acc(): three-scalar form of
 * the blend, d = a*fa + b*fb + c*fc (VecWeightedSum3_1cb860): `mfc1 a1..a3, fa..fc` /
 * `qmtc2.ni a1..a3, vf8..vf10; vmulax ACC,vf4,vf8x; vmaddax ACC,vf5,vf9x`.
 * The three lqc2s between them, the closing vmaddx and the sqc2 stay C; the
 * a1-a3 clobber yields retail's entry daddu t1/t0/v1. Blocked ops as
 * Vu0BlendVectorF/Acc plus vmaddax. Not merged with the two-scalar pair: the
 * extra mfc1/qmtc2 sit inside the same asm blocks (one block per half).
 * Proof: build/s88m/acc6/NOTES.md. */
#define Vu0BlendVector3F(fa, fb, fc) asm volatile { mfc1 a1, fa; mfc1 a2, fb; mfc1 a3, fc }
#define Vu0BlendVector3Acc() \
    asm volatile { qmtc2.ni a1, vf8; qmtc2.ni a2, vf9; qmtc2.ni a3, vf10; \
                   vmulax.xyzw ACC, vf4, vf8x; vmaddax.xyzw ACC, vf5, vf9x }

/* Vu0StoreAccW26(d): `vmaddw.xyzw vf26, vf4, vf0w; sqc2 vf26, 0(d)` -- the
 * closing row of an ApplyMatrix (after Vu0MulMatrixAcc) whose result lives
 * in vf26. Blocked op: vf26 itself -- mwcc caps VU0 register bindings at
 * vf25 (the limit byte 0x636528 is clamped to 25 at 0x472c4d; vf26..vf31 =
 * "global register variable assigned to reserved non-volatile register") and
 * never allocates vf26+ itself, so neither the vmaddw nor the sqc2 can name
 * vf26 from C. Proof: build/s88m/acc7/NOTES.md. */
#define Vu0StoreAccW26(d) asm volatile { vmaddw.xyzw vf26, vf4, vf0w; sqc2 vf26, 0(d) }

/* Vu0OrthoNormalSqrt(vf): Q = sqrt(vf8x) step of a Sony-style matrix
 * orthonormalise (MatOrthonormalizeY_1cb300: normalise row 1, rebuild rows by outer
 * products): `vsqrt Q, vf8x; vsub.w vf, vf0, vf0; vwaitq`. The vaddq/vdiv/
 * vmulq that follow, the vopmsub (Vu0OuterProductAcc + _vopmsub) and all
 * loads/stores stay C. Blocked ops: the `vsub.w vf,vf0,vf0` w-prefill of the
 * next vopmsub destination -- _vopmsub is modelled as a FULL .xyzw def, so C
 * dead-strips the prefill (acc6 t1.c fc); and as an asm statement the vsqrt
 * must ride along, since a C Q write gets its vwaitq before any asm block.
 * Proof: build/s88m/acc6/NOTES.md. */
#define Vu0OrthoNormalSqrt(vf) asm volatile { vsqrt Q, vf8x; vsub.w vf, vf0, vf0; vwaitq }

/* Vu0InversMatrixLoad(m) / Vu0InversMatrixDet(r): the SDK-asm pieces of a
 * Sony-style 3x3 cofactor inverse (MtxInverseAffine_1cb640, returns det in f0).
 * Load: `addiu a2,m,0x10; addiu a3,m,0x20; j 1f; addiu t0,m,0x30; 1: lqc2
 * vf1..vf4` -- blocked: the hand-asm `j` to the next word (mwcc never emits
 * `j` for an intra-function jump) and the lqc2s through the hard-coded
 * volatile a2/a3/t0 it sets up. Det: `vdiv Q,vf0w,vf9x; qmfc2.ni a1,vf9;
 * mtc1 a1,r` -- blocked: qmfc2/mtc1 through hard-coded a1 (C _vgetf temp is
 * first-fit v0, build/s88m/vleaf1, vleaf4 NOTES.md); the vdiv rides along
 * because a C Q write gets its vwaitq before the asm block (C `_vwaitq(q)`
 * then places retail's vwaitq). Cross products/vmulq/vmr32/sqc2 stay C.
 * Proof: build/s88m/acc6/NOTES.md. */
#define Vu0InversMatrixLoad(m) \
    asm volatile { .set noreorder; addiu a2, m, 0x10; addiu a3, m, 0x20; j @1; addiu t0, m, 0x30; @1: \
                   lqc2 vf1, 0x0(m); lqc2 vf2, 0x0(a2); lqc2 vf3, 0x0(a3); lqc2 vf4, 0x0(t0) }
#define Vu0InversMatrixDet(r) asm volatile { vdiv Q, vf0w, vf9x; qmfc2.ni a1, vf9; mtc1 a1, r }

/* Vu0PushApart*: the vf31/ACC/mfc1 pieces of the game's separation routine
 * (VecSolveDistanceConstraint_364740 family: p0/p1 pushed apart along p0-p1 to distance a, vf31 =
 * (1,1,1,1)). Every lqc2/vsub/vmul/vmulx/vadd/sqc2 between them stays C.
 * Blocked ops: vf31 (unbindable, see Vu0StoreAccW26), bare mfc1 float->GPR->
 * qmtc2.ni through hard-coded a3/t0 (proof build/s88m/mfc1-3 NOTES.md),
 * vadday (ACC-dest, proof acc1/1552 NOTES.md). Vu0PushApartRsqrt also carries
 * the vrsqrt: a C Q write always gets its vwaitq right after it, but retail
 * issues the vf31 vsub.x between them. Proof: build/s88m/acc7/NOTES.md. */
#define Vu0PushApartOne() asm volatile { vsub.xyzw vf31, vf31, vf31; vaddw.xyzw vf31, vf31, vf0w }
#define Vu0PushApartLen(a, b) \
    asm volatile { mfc1 a3, a; mfc1 t0, b; qmtc2.ni a3, vf12; qmtc2.ni t0, vf13; \
                   vadday.x ACC, vf2, vf2y; vmaddz.x vf6, vf31, vf2z }
#define Vu0PushApartRsqrt() asm volatile { vrsqrt Q, vf12x, vf6x; vsub.x vf14, vf31, vf13 }
#define Vu0PushApartSubQ() asm volatile { vsubq.x vf20, vf31, Q }

/* Vu0SinCosAccR() / Vu0SinCosAccP0() / Vu0SinCosAccP1(): the ACC-dest spans
 * of the SDK fast sin/cos routine VecSinCos_1cbfb0 (table D_0044B2C0 = {pi/2,
 * -1/2pi, 1.5*2^23, 2pi}, {0.5, 0.25, 0, 0}, poly coefficients).
 * R: range reduction `vmulay; vmsubaz; vmaddaz; vmsubay` (ACC accumulate
 * chain, closed by C _vmsubbc); P0: `vmula ACC,vf9,vf12` opens the
 * polynomial accumulate, C vmulbc/vmul run while ACC holds it, P1: `vmadda;
 * vmadda; vmaddaw` continues it and C _vmadd on an ACC binding closes it. Every lqc2/vmul/vabs/vmax/vsub and the sqc2 stay C.
 * Blocked ops: vmulay/vmsubaz/vmaddaz/vmsubay, vmula, vmadda/vmaddaw
 * (ACC-dest). Proof: build/s88m/148f, acc1 NOTES.md; build/s88m/acc6/NOTES.md. */
#define Vu0SinCosAccR() \
    asm volatile { vmulay.xyzw ACC, vf4, vf5y; vmsubaz.xyzw ACC, vf8, vf5z; \
                   vmaddaz.xyzw ACC, vf8, vf5z; vmsubay.xyzw ACC, vf4, vf5y }
#define Vu0SinCosAccP0() asm volatile { vmula.xyzw ACC, vf9, vf12 }
#define Vu0SinCosAccP1() \
    asm volatile { vmadda.xyzw ACC, vf11, vf13; vmadda.xyzw ACC, vf10, vf13; vmaddaw.xyzw ACC, vf4, vf5w }

#endif /* LIBVU0_H */
