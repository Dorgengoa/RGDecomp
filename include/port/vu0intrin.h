/* mwcc VU0 intrinsics on the VU0 model (stage `vu0bind`, docs/LINK.md).
 *
 * The de-asm'd decomp (d784320c+) writes VU0 macro code as C: variables bound
 * to VU registers with `#pragma vu0_mmi_reg_binding on` +
 * `extern u128 v asm("vf4")`, and mwcc intrinsics that return the new value
 * of the destination register (`v5 = _vmul(v5, 0xE, v4, v4)` = vmul.xyz
 * vf5, vf4, vf4).  The `vu0bind` ingest stage turns each binding into an
 * lvalue on the model's register file (rg_vu0.vf[N] / acc / q), so the bound
 * variables, the libvu0.h macros and the vu0asm-stage calls all see ONE
 * register file, as on the EE.  These functions compute on values with the
 * model's VU arithmetic (rounding toward zero, clamping, no denormals).
 *
 * Each intrinsic writes its first argument (the destination register) in
 * place and also yields the new value, so both `v5 = _vmul(v5, ...)` and a
 * bare `_vmul(v4, ...);` work (VecLengthSq_1cb470 uses the latter).
 *
 * Encodings (mwcc): dest mask x=8 y=4 z=2 w=1; broadcast/field selector the
 * same (8 = x ... 1 = w).  Lanes outside the mask keep the `d` argument.
 */
#ifndef RG_PORT_VU0INTRIN_H
#define RG_PORT_VU0INTRIN_H

#include "port/u128.h"
#include "port/vu0.h"

#ifdef __cplusplus
extern "C" {
#endif

/* bound-register lvalues (alignment 4: rg_vu0 is a plain struct).  `rg_vu0`
   expands at the use, so it is the file's register file under RG_VU0_LOCAL or
   a named context (port/vu0_ctx.h); docs/NATIVE-CPU.md */
typedef rg_u128 __attribute__((aligned(4))) rg_vu0b_u128;
#define RG_VU0_BIND_VF(n, T) (*(T *)(void *)&rg_vu0.vf[n])
#define RG_VU0_BIND_ACC(T)   (*(T *)(void *)&rg_vu0.acc)
#define RG_VU0_BIND_Q(T)     (*(T *)(void *)&rg_vu0.q)

static inline rg_vf rg_vb_in(rg_u128 v) { rg_vf r; __builtin_memcpy(&r, &v, 16); return r; }
static inline rg_u128 rg_vb_out(rg_vf v) { rg_u128 r; __builtin_memcpy(&r, &v, 16); return r; }
static inline int rg_vb_lane(int mask, int k) { return (mask >> (3 - k)) & 1; }
static inline int rg_vb_field(int f) { return f == 8 ? 0 : f == 4 ? 1 : f == 2 ? 2 : 3; }
static inline rg_vu_u32 rg_vb_qbits(float q) { return rg_f2u(q); }

enum { RG_VB_ADD, RG_VB_SUB, RG_VB_MUL, RG_VB_MAX, RG_VB_MINI, RG_VB_MADD, RG_VB_MSUB };

static inline rg_u128 rg_vb_op(int op, rg_u128 d_, int mask, const rg_vf *acc,
                               rg_u128 a_, rg_vf t)
{
    rg_vf d = rg_vb_in(d_), s = rg_vb_in(a_);
    int k;
    for (k = 0; k < 4; k++) {
        if (!rg_vb_lane(mask, k))
            continue;
        switch (op) {
        case RG_VB_ADD:  d.u[k] = rg_vu_addf(s.u[k], t.u[k]); break;
        case RG_VB_SUB:  d.u[k] = rg_vu_subf(s.u[k], t.u[k]); break;
        case RG_VB_MUL:  d.u[k] = rg_vu_mulf(s.u[k], t.u[k]); break;
        case RG_VB_MAX:  d.u[k] = rg_vu_maxf(s.u[k], t.u[k]); break;
        case RG_VB_MINI: d.u[k] = rg_vu_minf(s.u[k], t.u[k]); break;
        case RG_VB_MADD: d.u[k] = rg_vu_addf(acc->u[k], rg_vu_mulf(s.u[k], t.u[k])); break;
        case RG_VB_MSUB: d.u[k] = rg_vu_subf(acc->u[k], rg_vu_mulf(s.u[k], t.u[k])); break;
        }
    }
    return rg_vb_out(d);
}
static inline rg_vf rg_vb_bc(rg_u128 b, int bc)
{
    rg_vf t = rg_vb_in(b);
    rg_vu_u32 c = t.u[rg_vb_field(bc)];
    t.u[0] = t.u[1] = t.u[2] = t.u[3] = c;
    return t;
}
static inline rg_vf rg_vb_sc(float q)
{
    rg_vf t;
    t.u[0] = t.u[1] = t.u[2] = t.u[3] = rg_vb_qbits(q);
    return t;
}

/* vector-vector */
static inline rg_u128 rg_vbi_vadd(rg_u128 d, int m, rg_u128 a, rg_u128 b) { return rg_vb_op(RG_VB_ADD, d, m, 0, a, rg_vb_in(b)); }
static inline rg_u128 rg_vbi_vsub(rg_u128 d, int m, rg_u128 a, rg_u128 b) { return rg_vb_op(RG_VB_SUB, d, m, 0, a, rg_vb_in(b)); }
static inline rg_u128 rg_vbi_vmul(rg_u128 d, int m, rg_u128 a, rg_u128 b) { return rg_vb_op(RG_VB_MUL, d, m, 0, a, rg_vb_in(b)); }
static inline rg_u128 rg_vbi_vmax(rg_u128 d, int m, rg_u128 a, rg_u128 b) { return rg_vb_op(RG_VB_MAX, d, m, 0, a, rg_vb_in(b)); }
static inline rg_u128 rg_vbi_vmini(rg_u128 d, int m, rg_u128 a, rg_u128 b) { return rg_vb_op(RG_VB_MINI, d, m, 0, a, rg_vb_in(b)); }
/* broadcast */
static inline rg_u128 rg_vbi_vaddbc(rg_u128 d, int m, rg_u128 a, rg_u128 b, int bc) { return rg_vb_op(RG_VB_ADD, d, m, 0, a, rg_vb_bc(b, bc)); }
static inline rg_u128 rg_vbi_vsubbc(rg_u128 d, int m, rg_u128 a, rg_u128 b, int bc) { return rg_vb_op(RG_VB_SUB, d, m, 0, a, rg_vb_bc(b, bc)); }
static inline rg_u128 rg_vbi_vmulbc(rg_u128 d, int m, rg_u128 a, rg_u128 b, int bc) { return rg_vb_op(RG_VB_MUL, d, m, 0, a, rg_vb_bc(b, bc)); }
static inline rg_u128 rg_vbi_vmaxbc(rg_u128 d, int m, rg_u128 a, rg_u128 b, int bc) { return rg_vb_op(RG_VB_MAX, d, m, 0, a, rg_vb_bc(b, bc)); }
static inline rg_u128 rg_vbi_vminibc(rg_u128 d, int m, rg_u128 a, rg_u128 b, int bc) { return rg_vb_op(RG_VB_MINI, d, m, 0, a, rg_vb_bc(b, bc)); }
/* Q (or I) scalar operand */
static inline rg_u128 rg_vbi_vaddf(rg_u128 d, int m, rg_u128 a, float q) { return rg_vb_op(RG_VB_ADD, d, m, 0, a, rg_vb_sc(q)); }
static inline rg_u128 rg_vbi_vsubf(rg_u128 d, int m, rg_u128 a, float q) { return rg_vb_op(RG_VB_SUB, d, m, 0, a, rg_vb_sc(q)); }
static inline rg_u128 rg_vbi_vmulf(rg_u128 d, int m, rg_u128 a, float q) { return rg_vb_op(RG_VB_MUL, d, m, 0, a, rg_vb_sc(q)); }
/* multiply-accumulate with an explicit ACC operand */
static inline rg_u128 rg_vbi_vmadd(rg_u128 d, int m, rg_u128 acc, rg_u128 a, rg_u128 b)
{ rg_vf c = rg_vb_in(acc); return rg_vb_op(RG_VB_MADD, d, m, &c, a, rg_vb_in(b)); }
static inline rg_u128 rg_vbi_vmsub(rg_u128 d, int m, rg_u128 acc, rg_u128 a, rg_u128 b)
{ rg_vf c = rg_vb_in(acc); return rg_vb_op(RG_VB_MSUB, d, m, &c, a, rg_vb_in(b)); }
static inline rg_u128 rg_vbi_vmaddbc(rg_u128 d, int m, rg_u128 acc, rg_u128 a, rg_u128 b, int bc)
{ rg_vf c = rg_vb_in(acc); return rg_vb_op(RG_VB_MADD, d, m, &c, a, rg_vb_bc(b, bc)); }
static inline rg_u128 rg_vbi_vmsubbc(rg_u128 d, int m, rg_u128 acc, rg_u128 a, rg_u128 b, int bc)
{ rg_vf c = rg_vb_in(acc); return rg_vb_op(RG_VB_MSUB, d, m, &c, a, rg_vb_bc(b, bc)); }
/* vopmsub.xyz fd, fs, ft : fd.xyz = ACC.xyz - fs.yzx * ft.zxy (w kept) */
static inline rg_u128 rg_vbi_vopmsub(rg_u128 d_, rg_u128 acc, rg_u128 a, rg_u128 b)
{
    rg_vf d = rg_vb_in(d_), c = rg_vb_in(acc), s = rg_vb_in(a), t = rg_vb_in(b);
    d.u[0] = rg_vu_subf(c.u[0], rg_vu_mulf(s.u[1], t.u[2]));
    d.u[1] = rg_vu_subf(c.u[1], rg_vu_mulf(s.u[2], t.u[0]));
    d.u[2] = rg_vu_subf(c.u[2], rg_vu_mulf(s.u[0], t.u[1]));
    return rg_vb_out(d);
}
/* vopmula.xyz ACC, fs, ft : ACC.xyz = fs.yzx * ft.zxy */
static inline rg_u128 rg_vbi_vopmula(rg_u128 acc, rg_u128 a, rg_u128 b)
{
    rg_vf d = rg_vb_in(acc), s = rg_vb_in(a), t = rg_vb_in(b);
    d.u[0] = rg_vu_mulf(s.u[1], t.u[2]);
    d.u[1] = rg_vu_mulf(s.u[2], t.u[0]);
    d.u[2] = rg_vu_mulf(s.u[0], t.u[1]);
    return rg_vb_out(d);
}
/* moves and conversions */
static inline rg_u128 rg_vb_mask(rg_u128 d_, int m, rg_vf s)
{
    rg_vf d = rg_vb_in(d_);
    int k;
    for (k = 0; k < 4; k++)
        if (rg_vb_lane(m, k))
            d.u[k] = s.u[k];
    return rg_vb_out(d);
}
static inline rg_u128 rg_vbi_vmove(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_in(a)); }
static inline rg_u128 rg_vbi_vmr32(rg_u128 d, int m, rg_u128 a)
{
    rg_vf s = rg_vb_in(a), r;
    r.u[0] = s.u[1]; r.u[1] = s.u[2]; r.u[2] = s.u[3]; r.u[3] = s.u[0];
    return rg_vb_mask(d, m, r);
}
static inline rg_u128 rg_vbi_vabs(rg_u128 d, int m, rg_u128 a)
{
    rg_vf s = rg_vb_in(a);
    int k;
    for (k = 0; k < 4; k++)
        s.u[k] &= 0x7FFFFFFFu;
    return rg_vb_mask(d, m, s);
}
static inline rg_vf rg_vb_ftoi(int n, rg_vf s)
{
    rg_vf r;
    int k;
    for (k = 0; k < 4; k++) {
        double v = rg_vu_in(s.u[k]) * (double)(1u << n);
        if (v >= 2147483647.0) r.i[k] = 0x7FFFFFFF;
        else if (v <= -2147483648.0) r.i[k] = (rg_vu_s32)0x80000000u;
        else r.i[k] = (rg_vu_s32)v;     /* truncation toward zero */
    }
    return r;
}
static inline rg_vf rg_vb_itof(int n, rg_vf s)
{
    rg_vf r;
    int k;
    for (k = 0; k < 4; k++)
        r.f[k] = (float)((double)s.i[k] / (double)(1u << n));
    return r;
}
static inline rg_u128 rg_vbi_vftoi0(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_ftoi(0, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vftoi4(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_ftoi(4, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vftoi12(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_ftoi(12, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vftoi15(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_ftoi(15, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vitof0(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_itof(0, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vitof4(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_itof(4, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vitof12(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_itof(12, rg_vb_in(a))); }
static inline rg_u128 rg_vbi_vitof15(rg_u128 d, int m, rg_u128 a) { return rg_vb_mask(d, m, rg_vb_itof(15, rg_vb_in(a))); }
/* Q unit: vdiv / vsqrt / vrsqrt; field selectors 8=x .. 1=w */
static inline float rg_vbi_vdiv(float q, rg_u128 a, int af, rg_u128 b, int bf)
{
    (void)q;
    return rg_u2f(rg_vu_divf(rg_vb_in(a).u[rg_vb_field(af)], rg_vb_in(b).u[rg_vb_field(bf)]));
}
static inline float rg_vbi_vsqrt(float q, rg_u128 b, int bf)
{
    (void)q;
    return rg_u2f(rg_vu_sqrtf(rg_vb_in(b).u[rg_vb_field(bf)]));
}
static inline float rg_vbi_vrsqrt(float q, rg_u128 a, int af, rg_u128 b, int bf)
{
    (void)q;
    return rg_u2f(rg_vu_divf(rg_vb_in(a).u[rg_vb_field(af)],
                             rg_vu_sqrtf(rg_vb_in(b).u[rg_vb_field(bf)])));
}
static inline float rg_vbi_vwaitq(float q) { return q; }
static inline void rg_vbi_vnop(void) {}

#ifdef __cplusplus
}
#endif

/* mwcc semantics: the FIRST argument is the bound destination register and is
 * written in place, whether or not the value is used
 * (`_vmul(v4, 0xE, v4, v4);` as a statement updates vf4). */
#define _vadd(d, ...) ((d) = rg_vbi_vadd((d), ##__VA_ARGS__))
#define _vsub(d, ...) ((d) = rg_vbi_vsub((d), ##__VA_ARGS__))
#define _vmul(d, ...) ((d) = rg_vbi_vmul((d), ##__VA_ARGS__))
#define _vmax(d, ...) ((d) = rg_vbi_vmax((d), ##__VA_ARGS__))
#define _vmini(d, ...) ((d) = rg_vbi_vmini((d), ##__VA_ARGS__))
#define _vaddbc(d, ...) ((d) = rg_vbi_vaddbc((d), ##__VA_ARGS__))
#define _vsubbc(d, ...) ((d) = rg_vbi_vsubbc((d), ##__VA_ARGS__))
#define _vmulbc(d, ...) ((d) = rg_vbi_vmulbc((d), ##__VA_ARGS__))
#define _vmaxbc(d, ...) ((d) = rg_vbi_vmaxbc((d), ##__VA_ARGS__))
#define _vminibc(d, ...) ((d) = rg_vbi_vminibc((d), ##__VA_ARGS__))
#define _vaddf(d, ...) ((d) = rg_vbi_vaddf((d), ##__VA_ARGS__))
#define _vsubf(d, ...) ((d) = rg_vbi_vsubf((d), ##__VA_ARGS__))
#define _vmulf(d, ...) ((d) = rg_vbi_vmulf((d), ##__VA_ARGS__))
#define _vmadd(d, ...) ((d) = rg_vbi_vmadd((d), ##__VA_ARGS__))
#define _vmsub(d, ...) ((d) = rg_vbi_vmsub((d), ##__VA_ARGS__))
#define _vmaddbc(d, ...) ((d) = rg_vbi_vmaddbc((d), ##__VA_ARGS__))
#define _vmsubbc(d, ...) ((d) = rg_vbi_vmsubbc((d), ##__VA_ARGS__))
#define _vopmsub(d, ...) ((d) = rg_vbi_vopmsub((d), ##__VA_ARGS__))
#define _vopmula(d, ...) ((d) = rg_vbi_vopmula((d), ##__VA_ARGS__))
#define _vmove(d, ...) ((d) = rg_vbi_vmove((d), ##__VA_ARGS__))
#define _vmr32(d, ...) ((d) = rg_vbi_vmr32((d), ##__VA_ARGS__))
#define _vabs(d, ...) ((d) = rg_vbi_vabs((d), ##__VA_ARGS__))
#define _vftoi0(d, ...) ((d) = rg_vbi_vftoi0((d), ##__VA_ARGS__))
#define _vftoi4(d, ...) ((d) = rg_vbi_vftoi4((d), ##__VA_ARGS__))
#define _vftoi12(d, ...) ((d) = rg_vbi_vftoi12((d), ##__VA_ARGS__))
#define _vftoi15(d, ...) ((d) = rg_vbi_vftoi15((d), ##__VA_ARGS__))
#define _vitof0(d, ...) ((d) = rg_vbi_vitof0((d), ##__VA_ARGS__))
#define _vitof4(d, ...) ((d) = rg_vbi_vitof4((d), ##__VA_ARGS__))
#define _vitof12(d, ...) ((d) = rg_vbi_vitof12((d), ##__VA_ARGS__))
#define _vitof15(d, ...) ((d) = rg_vbi_vitof15((d), ##__VA_ARGS__))
#define _vdiv(d, ...) ((d) = rg_vbi_vdiv((d), ##__VA_ARGS__))
#define _vsqrt(d, ...) ((d) = rg_vbi_vsqrt((d), ##__VA_ARGS__))
#define _vrsqrt(d, ...) ((d) = rg_vbi_vrsqrt((d), ##__VA_ARGS__))
#define _vwaitq(d, ...) ((d) = rg_vbi_vwaitq((d), ##__VA_ARGS__))
#define _vnop() rg_vbi_vnop()

#endif
