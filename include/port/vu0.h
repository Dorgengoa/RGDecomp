/* VU0 macro-mode model for the PC port (PLAN.md transform 4).
 *
 * The game's COP2 code is register-transfer code: an `asm volatile {}` block,
 * a libvu0.h macro or a vu0inline.h helper leaves values in vf/ACC/Q that the
 * NEXT block reads (vf31 = (1,1,1,1) is set by one routine and used by later
 * ones; the libvu0.h macros are fragments around C code).  So the bring-up
 * model keeps ONE global VU0 register file, rg_vu0, and every COP2
 * instruction becomes a call below with the same operands.  RG_VU0_MODE
 * local / native (native is the default) make `rg_vu0` a register file per
 * FUNCTION instead (RG_VU0_FRAME, see RG_VU0_LOCAL below, docs/NATIVE-CPU.md).  The ingest stage `vu0asm`
 * (tools/portxform.py) emits these calls; include/vu0inline.h and
 * include/libvu0.h are written with them.
 *
 * Float semantics (RG_VU0_IEEE undefined, the default) follow the VU FMAC as
 * documented by Sony and measured by the emulator community:
 *   - inputs: exponent 0 (denormal or zero) reads as a signed zero; exponent
 *     255 is an ordinary number ((1.m) * 2^128), never Inf/NaN;
 *   - results: rounded TOWARD ZERO to 24 bits; |r| >= 2^129 clamps to
 *     +-0x7FFFFFFF (the largest VU value); |r| < 2^-126 flushes to +-0;
 *   - madd/msub round the product first, then the sum (not fused);
 *   - div/sqrt/rsqrt follow the same in/out rules; x/0 gives +-max, sqrt
 *     takes |x| (the D/I flags are not modelled).
 * APPROXIMATIONS: the arithmetic is done in double and then truncated, so it
 * is exact for mul (48-bit product) and for add/sub except the rare case
 * where the 53-bit rounding of the exact sum carries across the 24-bit
 * truncation point.  Real VU adders also drop guard bits on large exponent
 * differences (results can differ by 1 ulp from round-to-zero of the exact
 * sum); that is NOT modelled.  MAC/status flags are not modelled (cfc2 of
 * vi16/vi17 reads 0); the clip flag (vi18) IS.  Define RG_VU0_IEEE to use
 * plain IEEE single arithmetic instead (faster, not bit-faithful).
 *
 * Micro mode: `vcallms` is rg_vu0_vcallms() (bottom of this file), which
 * runs the program on the src/ps2/vu interpreter over this same state.
 *
 * Memory: lqc2/sqc2/lq/sq on hardware ignore the low 4 address bits.  The
 * port does NOT mask: the host object is assumed to be where the pointer
 * says (Vec4/u128 are 16-aligned anyway; a masked address would be wrong for
 * any host object that is not).
 */
#ifndef RG_PORT_VU0_H
#define RG_PORT_VU0_H

/* RG_VU0_ORACLE: this file checks the bring-up model itself (global register
 * file, VU float rules) whatever RG_VU0_MODE the build uses. */
#ifdef RG_VU0_ORACLE
#undef RG_VU0_IEEE
#undef RG_VU0_LOCAL
#endif

/* Freestanding on purpose: it is force-included into game TUs whose own
   extern declarations of memcpy/sqrtf/... must not meet the system headers. */
typedef unsigned int rg_vu_u32;
typedef int rg_vu_s32;
typedef unsigned long long rg_vu_u64;
typedef long long rg_vu_s64;

#ifdef __cplusplus
extern "C" {
#endif

typedef union rg_vf {
    float f[4];
    rg_vu_u32 u[4];
    rg_vu_s32 i[4];
} __attribute__((aligned(16))) rg_vf;

typedef struct rg_vu0_state {
    rg_vf vf[32];        /* vf0 is the constant (0,0,0,1); writes are dropped */
    rg_vf acc;
    rg_vu_u32 q, p, r, i; /* special registers, as bit patterns */
    rg_vu_u32 vi[16];     /* integer registers (16-bit); vi0 = 0 */
    rg_vu_u32 clip;       /* vi18, 24-bit clipping flag history */
    rg_vu_u32 gpr[32][4]; /* EE GPRs NAMED by asm text as temps (128-bit) */
} rg_vu0_state;

/* Which register file code uses (docs/NATIVE-CPU.md):
 *   default          ONE global file `rg_vu0` (src/ps2/vu0.c), the bring-up
 *                    model and the oracle;
 *   RG_VU0_LOCAL     a file private to each function (RG_VU0_FRAME).  The census
 *                    (tools/native/vu0_census.py) shows no value travels
 *                    between functions of different files through VU
 *                    registers except the named protocols, which share an
 *                    explicit context (port/vu0_ctx.h); every other
 *                    function writes what it reads.
 *   RG_VU0_ORACLE    forces the default (tests that check the global model).
 * The calls below name the file at the call site (`&rg_vu0`), so a file can
 * also select a shared context by redefining rg_vu0 before its code. */
#if defined(RG_VU0_LOCAL) && !defined(RG_VU0_ORACLE)
#define RG_VU0_IS_LOCAL 1
/* Function-local register files (ingest stage `vu0frame`, docs/NATIVE-CPU.md
 * section 4): every game function that touches the model starts with
 * `RG_VU0_FRAME;`, a block-scope `rg_vu0` (vf0 = (0,0,0,1)) that the
 * spellings above resolve to by ordinary scope; the stage's frame helpers
 * take the caller's file as `rg_vu0_state *rg_vu0_p_`.  Hand-written code
 * (overrides, src/sce/vu0/libvu0.c) uses the same convention
 * (tools/native/override_vu0frame.py).  There is NO file-scope register file:
 * a function that names the model without a frame fails to compile
 * (`use of undeclared identifier 'rg_vu0'`), so no code can carry VU values
 * between calls by accident.  (RG_VU0_STRICT, which used to remove the old
 * per-file fallback, is now the only behaviour; the macro is ignored.)
 * RG_VU0_NO_FRAMES (cmake -DRG_VU0_NO_FRAMES=ON, A/B verification only) turns the
 * frames off and brings back one file-scope register file per translation
 * unit (the pre-vu0frame semantics). */
#define RG_VU0_RESET_INIT { { { { 0.0f, 0.0f, 0.0f, 1.0f } } } }
#ifdef RG_VU0_NO_FRAMES   /* A/B check only: frames off = the old per-file register file */
#define RG_VU0_FRAME ((void)0)
#else
#define RG_VU0_FRAME rg_vu0_state rg_vu0 = RG_VU0_RESET_INIT
#endif
#ifdef RG_VU0_NO_FRAMES   /* A/B check only: the old per-file register file */
static rg_vu0_state rg_vu0 __attribute__((unused)) = RG_VU0_RESET_INIT;
#endif
#else
#define RG_VU0_IS_LOCAL 0
#define RG_VU0_FRAME ((void)0)
extern rg_vu0_state rg_vu0;
#endif

/* A cross-file VU register protocol (e.g. AabbLoadToVu -> AabbPlaneDistances
 * through vf7, vf10-12) shares a NAMED context instead: each participating
 * file does `#define RG_VU0_CTX_NAME xfbox` + `#include "port/vu0_ctx.h"`
 * before its code (src/sce/vu0/vu0_ctx.c defines the contexts). */

/* dest field masks (bit k = lane k: x=1 y=2 z=4 w=8) */
enum {
    RG_X = 1, RG_Y = 2, RG_Z = 4, RG_W = 8,
    RG_XY = 3, RG_XZ = 5, RG_YZ = 6, RG_XYZ = 7, RG_XW = 9, RG_YW = 10,
    RG_XYW = 11, RG_ZW = 12, RG_XZW = 13, RG_YZW = 14, RG_XYZW = 15
};
/* broadcast field (bc) / scalar field selector; RG_BC_NONE = lane-wise */
enum { RG_BC_NONE = -1, RG_BC_X = 0, RG_BC_Y = 1, RG_BC_Z = 2, RG_BC_W = 3 };
/* special ft sources for the FMAC: Q and I */
enum { RG_FT_Q = 32, RG_FT_I = 33 };
/* FMAC operations; the `A` forms write ACC */
enum {
    RG_VADD, RG_VSUB, RG_VMUL, RG_VMAX, RG_VMINI, RG_VMADD, RG_VMSUB,
    RG_VADDA, RG_VSUBA, RG_VMULA, RG_VMADDA, RG_VMSUBA
};

/* ------------------------------------------------------------ float model */
static inline rg_vu_u32 rg_f2u(float f) { rg_vu_u32 u; __builtin_memcpy(&u, &f, 4); return u; }
static inline float rg_u2f(rg_vu_u32 u) { float f; __builtin_memcpy(&f, &u, 4); return f; }

static inline rg_vu_u64 rg_d2u(double d) { rg_vu_u64 u; __builtin_memcpy(&u, &d, 8); return u; }
static inline double rg_u2d(rg_vu_u64 u) { double d; __builtin_memcpy(&d, &u, 8); return d; }

/* VU float bits -> exact double (exp 0 = signed zero, exp 255 = 2^128 range) */
static inline double rg_vu_in(rg_vu_u32 b)
{
    rg_vu_u32 e = (b >> 23) & 0xFF;
    rg_vu_u64 s = (rg_vu_u64)(b >> 31) << 63;
    if (e == 0)
        return rg_u2d(s);
    return rg_u2d(s | ((rg_vu_u64)(e - 127 + 1023) << 52) | ((rg_vu_u64)(b & 0x7FFFFF) << 29));
}

/* double -> VU float bits: truncate to 24 bits, clamp to +-max, flush tiny */
static inline rg_vu_u32 rg_vu_out(double v)
{
    rg_vu_u64 b = rg_d2u(v);
    rg_vu_u32 s = (rg_vu_u32)(b >> 63) << 31;
    int e = (int)((b >> 52) & 0x7FF);
    int be;
    if (e == 0x7FF) /* Inf/NaN cannot come from VU inputs except 0*max etc.; clamp */
        return s | 0x7FFFFFFFu;
    be = e - 1023 + 127;
    if (e == 0 || be <= 0)
        return s;               /* underflow: flush to signed zero */
    if (be > 255)
        return s | 0x7FFFFFFFu; /* overflow: clamp to the VU maximum */
    return s | ((rg_vu_u32)be << 23) | (rg_vu_u32)((b >> 29) & 0x7FFFFF);
}

#ifdef RG_VU0_IEEE
/* Native float semantics (RG_VU0_MODE=native): IEEE single arithmetic, round
 * to nearest, as the rest of the port's game code, with the VU rules kept
 * exactly where IEEE and the VU part ways in a way game code can see
 * (docs/NATIVE-CPU.md "Native float rules"):
 *   - a result that is not finite (overflow, or an input with exponent 255,
 *     which the VU reads as a number: 0x7FFFFFFF is the VU maximum the model
 *     itself produces) is recomputed with the VU rule (clamp to +-max);
 *   - x / 0 (and x / denormal) gives +-max with the xor sign, sqrt takes |x|;
 *   - an add or subtract with +-1.5*2^23 as an operand uses the VU's
 *     round-toward-zero: the round-to-integer idiom x + 1.5*2^23 - 1.5*2^23
 *     (VecWrapAngle_1cbe90, VecSinCos_1cbfb0, sceVu0ecossin, the vcallms
 *     program) is floor/trunc on the VU but round() in IEEE.
 * Everything else (rounding of ordinary results, denormals) is IEEE. */
static inline int rg_vu_magic(rg_vu_u32 a, rg_vu_u32 b)
{
    return ((a & 0x7FFFFFFFu) == 0x4B400000u) | ((b & 0x7FFFFFFFu) == 0x4B400000u);
}
static inline int rg_vu_nonfinite(rg_vu_u32 r) { return (r & 0x7F800000u) == 0x7F800000u; }
static inline rg_vu_u32 rg_vu_addf(rg_vu_u32 a, rg_vu_u32 b)
{
    rg_vu_u32 r = rg_f2u(rg_u2f(a) + rg_u2f(b));
    if (__builtin_expect(rg_vu_nonfinite(r) | rg_vu_magic(a, b), 0))
        return rg_vu_out(rg_vu_in(a) + rg_vu_in(b));
    return r;
}
static inline rg_vu_u32 rg_vu_subf(rg_vu_u32 a, rg_vu_u32 b)
{
    rg_vu_u32 r = rg_f2u(rg_u2f(a) - rg_u2f(b));
    if (__builtin_expect(rg_vu_nonfinite(r) | rg_vu_magic(a, b), 0))
        return rg_vu_out(rg_vu_in(a) - rg_vu_in(b));
    return r;
}
static inline rg_vu_u32 rg_vu_mulf(rg_vu_u32 a, rg_vu_u32 b)
{
    rg_vu_u32 r = rg_f2u(rg_u2f(a) * rg_u2f(b));
    if (__builtin_expect(rg_vu_nonfinite(r), 0))
        return rg_vu_out(rg_vu_in(a) * rg_vu_in(b));
    return r;
}
static inline rg_vu_u32 rg_vu_divf(rg_vu_u32 a, rg_vu_u32 b)
{
    rg_vu_u32 r;
    if ((b & 0x7F800000u) == 0) /* VU: exponent 0 is zero: +-max, sign xor */
        return ((a ^ b) & 0x80000000u) | 0x7FFFFFFFu;
    r = rg_f2u(rg_u2f(a) / rg_u2f(b));
    if (__builtin_expect(rg_vu_nonfinite(r) | rg_vu_nonfinite(a) | rg_vu_nonfinite(b), 0))
        return rg_vu_out(rg_vu_in(a) / rg_vu_in(b));
    return r;
}
static inline rg_vu_u32 rg_vu_sqrtf(rg_vu_u32 a)
{
    if (__builtin_expect(rg_vu_nonfinite(a), 0))
        return rg_vu_out(__builtin_sqrt(__builtin_fabs(rg_vu_in(a)))) & 0x7FFFFFFFu;
    return rg_f2u(__builtin_sqrtf(__builtin_fabsf(rg_u2f(a))));
}
#else
static inline rg_vu_u32 rg_vu_addf(rg_vu_u32 a, rg_vu_u32 b) { return rg_vu_out(rg_vu_in(a) + rg_vu_in(b)); }
static inline rg_vu_u32 rg_vu_subf(rg_vu_u32 a, rg_vu_u32 b) { return rg_vu_out(rg_vu_in(a) - rg_vu_in(b)); }
static inline rg_vu_u32 rg_vu_mulf(rg_vu_u32 a, rg_vu_u32 b) { return rg_vu_out(rg_vu_in(a) * rg_vu_in(b)); }
static inline rg_vu_u32 rg_vu_divf(rg_vu_u32 a, rg_vu_u32 b)
{
    double x = rg_vu_in(a), y = rg_vu_in(b);
    if (y == 0.0) /* VU: +-max, sign = sign(a) xor sign(b); 0/0 too */
        return ((a ^ b) & 0x80000000u) | 0x7FFFFFFFu;
    return rg_vu_out(x / y);
}
static inline rg_vu_u32 rg_vu_sqrtf(rg_vu_u32 a) { return rg_vu_out(__builtin_sqrt(__builtin_fabs(rg_vu_in(a)))) & 0x7FFFFFFFu; }
#endif

/* VU MAX/MINI compare the operands as VU values; the chosen operand's bits
   are returned unchanged. */
static inline rg_vu_u32 rg_vu_maxf(rg_vu_u32 a, rg_vu_u32 b) { return rg_vu_in(a) >= rg_vu_in(b) ? a : b; }
static inline rg_vu_u32 rg_vu_minf(rg_vu_u32 a, rg_vu_u32 b) { return rg_vu_in(a) < rg_vu_in(b) ? a : b; }

/* ------------------------------------------------------------- registers */
static inline void rg_vu0s_setvf(rg_vu0_state *S, int fd, const rg_vf *v, int mask)
{
    int k;
    if (fd == 0)
        return;
    for (k = 0; k < 4; k++)
        if (mask & (1 << k))
            S->vf[fd].u[k] = v->u[k];
}

static inline rg_vu_u32 rg_vu0s_scalar(rg_vu0_state *S, int ft)
{
    return ft == RG_FT_Q ? S->q : S->i;
}

/* The FMAC: fd/ACC = op(fs, ft) on the lanes in mask.
   ft = vf index, or RG_FT_Q / RG_FT_I; bc = broadcast lane of ft or RG_BC_NONE. */
static inline void rg_vu0s_fmac(rg_vu0_state *S, int op, int mask, int fd, int fs, int ft, int bc)
{
    rg_vf s = S->vf[fs], a = S->acc, t, d;
    int k;
    if (ft >= 32) {
        rg_vu_u32 c = rg_vu0s_scalar(S, ft);
        t.u[0] = t.u[1] = t.u[2] = t.u[3] = c;
    } else {
        t = S->vf[ft];
        if (bc >= 0)
            t.u[0] = t.u[1] = t.u[2] = t.u[3] = S->vf[ft].u[bc];
    }
    d = (op >= RG_VADDA) ? a : S->vf[fd];
    for (k = 0; k < 4; k++) {
        if (!(mask & (1 << k)))
            continue;
        switch (op) {
        case RG_VADD: case RG_VADDA: d.u[k] = rg_vu_addf(s.u[k], t.u[k]); break;
        case RG_VSUB: case RG_VSUBA: d.u[k] = rg_vu_subf(s.u[k], t.u[k]); break;
        case RG_VMUL: case RG_VMULA: d.u[k] = rg_vu_mulf(s.u[k], t.u[k]); break;
        case RG_VMAX:  d.u[k] = rg_vu_maxf(s.u[k], t.u[k]); break;
        case RG_VMINI: d.u[k] = rg_vu_minf(s.u[k], t.u[k]); break;
        case RG_VMADD: case RG_VMADDA:
            d.u[k] = rg_vu_addf(a.u[k], rg_vu_mulf(s.u[k], t.u[k])); break;
        case RG_VMSUB: case RG_VMSUBA:
            d.u[k] = rg_vu_subf(a.u[k], rg_vu_mulf(s.u[k], t.u[k])); break;
        }
    }
    if (op >= RG_VADDA)
        S->acc = d;
    else
        rg_vu0s_setvf(S, fd, &d, mask);
}

/* vopmula.xyz ACC, fs, ft : ACC.xyz = fs.yzx * ft.zxy */
static inline void rg_vu0s_opmula(rg_vu0_state *S, int fs, int ft)
{
    rg_vf s = S->vf[fs], t = S->vf[ft];
    S->acc.u[0] = rg_vu_mulf(s.u[1], t.u[2]);
    S->acc.u[1] = rg_vu_mulf(s.u[2], t.u[0]);
    S->acc.u[2] = rg_vu_mulf(s.u[0], t.u[1]);
}

/* vopmsub.xyz fd, fs, ft : fd.xyz = ACC.xyz - fs.yzx * ft.zxy */
static inline void rg_vu0s_opmsub(rg_vu0_state *S, int fd, int fs, int ft)
{
    rg_vf s = S->vf[fs], t = S->vf[ft], d;
    d.u[0] = rg_vu_subf(S->acc.u[0], rg_vu_mulf(s.u[1], t.u[2]));
    d.u[1] = rg_vu_subf(S->acc.u[1], rg_vu_mulf(s.u[2], t.u[0]));
    d.u[2] = rg_vu_subf(S->acc.u[2], rg_vu_mulf(s.u[0], t.u[1]));
    d.u[3] = 0;
    rg_vu0s_setvf(S, fd, &d, RG_XYZ);
}

/* vabs.mask ft, fs */
static inline void rg_vu0s_abs(rg_vu0_state *S, int mask, int ft, int fs)
{
    rg_vf d = S->vf[fs];
    int k;
    for (k = 0; k < 4; k++)
        d.u[k] &= 0x7FFFFFFFu;
    rg_vu0s_setvf(S, ft, &d, mask);
}

/* vmove.mask ft, fs */
static inline void rg_vu0s_move(rg_vu0_state *S, int mask, int ft, int fs)
{
    rg_vf d = S->vf[fs];
    rg_vu0s_setvf(S, ft, &d, mask);
}

/* vmr32.mask ft, fs : ft = fs.yzwx */
static inline void rg_vu0s_mr32(rg_vu0_state *S, int mask, int ft, int fs)
{
    rg_vf s = S->vf[fs], d;
    d.u[0] = s.u[1]; d.u[1] = s.u[2]; d.u[2] = s.u[3]; d.u[3] = s.u[0];
    rg_vu0s_setvf(S, ft, &d, mask);
}

/* vftoiN.mask ft, fs : fixed point with N fraction bits, toward zero,
   saturating to the int32 range. */
static inline void rg_vu0s_ftoi(rg_vu0_state *S, int n, int mask, int ft, int fs)
{
    rg_vf s = S->vf[fs], d;
    int k;
    for (k = 0; k < 4; k++) {
        double v = rg_vu_in(s.u[k]) * (double)(1 << n);
        rg_vu_s32 r;
        if (v >= 2147483647.0)
            r = 0x7FFFFFFF;
        else if (v <= -2147483648.0)
            r = (rg_vu_s32)0x80000000u;
        else
            r = (rg_vu_s32)v; /* C truncation = toward zero */
        d.i[k] = r;
    }
    rg_vu0s_setvf(S, ft, &d, mask);
}

/* vitofN.mask ft, fs : int32 / 2^N */
static inline void rg_vu0s_itof(rg_vu0_state *S, int n, int mask, int ft, int fs)
{
    rg_vf s = S->vf[fs], d;
    int k;
    for (k = 0; k < 4; k++)
        d.u[k] = rg_vu_out((double)s.i[k] / (double)(1 << n));
    rg_vu0s_setvf(S, ft, &d, mask);
}

/* vclipw.xyz fs, ftw : shift the clip flag history and judge fs.xyz
   against +-|ft.w|. */
static inline void rg_vu0s_clip(rg_vu0_state *S, int fs, int ft)
{
    double w = __builtin_fabs(rg_vu_in(S->vf[ft].u[3]));
    double x = rg_vu_in(S->vf[fs].u[0]);
    double y = rg_vu_in(S->vf[fs].u[1]);
    double z = rg_vu_in(S->vf[fs].u[2]);
    rg_vu_u32 f = 0;
    if (x > w) f |= 0x01;
    if (x < -w) f |= 0x02;
    if (y > w) f |= 0x04;
    if (y < -w) f |= 0x08;
    if (z > w) f |= 0x10;
    if (z < -w) f |= 0x20;
    S->clip = ((S->clip << 6) | f) & 0xFFFFFFu;
}

/* vdiv Q, fs<fsf>, ft<ftf> */
static inline void rg_vu0s_div(rg_vu0_state *S, int fs, int fsf, int ft, int ftf)
{
    S->q = rg_vu_divf(S->vf[fs].u[fsf], S->vf[ft].u[ftf]);
}

/* vsqrt Q, ft<ftf> */
static inline void rg_vu0s_sqrt(rg_vu0_state *S, int ft, int ftf)
{
    S->q = rg_vu_sqrtf(S->vf[ft].u[ftf]);
}

/* vrsqrt Q, fs<fsf>, ft<ftf> : Q = fs / sqrt(|ft|) */
static inline void rg_vu0s_rsqrt(rg_vu0_state *S, int fs, int fsf, int ft, int ftf)
{
    S->q = rg_vu_divf(S->vf[fs].u[fsf], rg_vu_sqrtf(S->vf[ft].u[ftf]));
}

/* vwaitq / vnop: the model is synchronous. */
static inline void rg_vu0s_waitq(rg_vu0_state *S) { (void)S; }

/* ------------------------------------------------- transfers (EE <-> VU0) */
static inline void rg_vu0s_lqc2(rg_vu0_state *S, int ft, const void *addr)
{
    rg_vf v;
    __builtin_memcpy(&v, addr, 16);
    rg_vu0s_setvf(S, ft, &v, RG_XYZW);
}

static inline void rg_vu0s_sqc2(rg_vu0_state *S, int ft, void *addr)
{
    __builtin_memcpy(addr, &S->vf[ft], 16);
}

/* GPR temps.  $0 reads 0 and drops writes. */
static inline void rg_vu0s_gpr_w64(rg_vu0_state *S, int rt, rg_vu_u64 v)
{
    if (rt == 0)
        return;
    S->gpr[rt][0] = (rg_vu_u32)v;
    S->gpr[rt][1] = (rg_vu_u32)(v >> 32);
}

static inline rg_vu_u32 rg_vu0s_gpr_r32(rg_vu0_state *S, int rt)
{
    return rt == 0 ? 0u : S->gpr[rt][0];
}

/* mfc1 rt, f : rt(63:0) = sign-extended float bits */
static inline void rg_vu0s_mfc1(rg_vu0_state *S, int rt, float f)
{
    rg_vu0s_gpr_w64(S, rt, (rg_vu_u64)(rg_vu_s64)(rg_vu_s32)rg_f2u(f));
}

/* mtc1 rt, f : f = rt(31:0) */
static inline float rg_vu0s_mtc1(rg_vu0_state *S, int rt)
{
    return rg_u2f(rg_vu0s_gpr_r32(S, rt));
}

/* qmtc2 rt, vf : vf = rt(127:0) */
static inline void rg_vu0s_qmtc2(rg_vu0_state *S, int rt, int ft)
{
    rg_vf v;
    if (rt == 0)
        __builtin_memset(&v, 0, 16);
    else
        __builtin_memcpy(&v, S->gpr[rt], 16);
    rg_vu0s_setvf(S, ft, &v, RG_XYZW);
}

/* qmfc2 rt, vf : rt(127:0) = vf */
static inline void rg_vu0s_qmfc2(rg_vu0_state *S, int rt, int ft)
{
    if (rt != 0)
        __builtin_memcpy(S->gpr[rt], &S->vf[ft], 16);
}

/* control register file view: vi0-15, 16 status, 17 MAC, 18 clip,
   20 R, 21 I, 22 Q, 23 P; others read 0 */
static inline rg_vu_u32 rg_vu0s_ctl_read(rg_vu0_state *S, int id)
{
    if (id < 16)
        return id == 0 ? 0u : (S->vi[id] & 0xFFFFu);
    switch (id) {
    case 18: return S->clip;
    case 20: return S->r;
    case 21: return S->i;
    case 22: return S->q;
    case 23: return S->p;
    default: return 0;
    }
}

static inline void rg_vu0s_ctl_write(rg_vu0_state *S, int id, rg_vu_u32 v)
{
    if (id > 0 && id < 16)
        S->vi[id] = v & 0xFFFFu;
    else if (id == 18)
        S->clip = v & 0xFFFFFFu;
    else if (id == 20)
        S->r = v;
    else if (id == 21)
        S->i = v;
    else if (id == 22)
        S->q = v;
}

/* cfc2 rt, vi : rt(63:0) = sign-extended control register */
static inline void rg_vu0s_cfc2(rg_vu0_state *S, int rt, int id)
{
    rg_vu0s_gpr_w64(S, rt, (rg_vu_u64)(rg_vu_s64)(rg_vu_s32)rg_vu0s_ctl_read(S, id));
}

/* ctc2 rt, vi */
static inline void rg_vu0s_ctc2(rg_vu0_state *S, int rt, int id)
{
    rg_vu0s_ctl_write(S, id, rg_vu0s_gpr_r32(S, rt));
}

/* lq / sq through an EE GPR temp (MMI qword moves) */
static inline void rg_vu0s_lq(rg_vu0_state *S, int rt, const void *addr)
{
    if (rt != 0)
        __builtin_memcpy(S->gpr[rt], addr, 16);
}

static inline void rg_vu0s_sq(rg_vu0_state *S, int rt, void *addr)
{
    if (rt == 0)
        __builtin_memset(addr, 0, 16);
    else
        __builtin_memcpy(addr, S->gpr[rt], 16);
}

/* GPR temp as a host pointer (lqc2 vfN, off(a2) after `addiu a2, m, 0x10`) */
static inline char *rg_vu0s_gptr(rg_vu0_state *S, int rt)
{
    return (char *)(unsigned long)rg_vu0s_gpr_r32(S, rt);
}

static inline void rg_vu0s_gpr_setp(rg_vu0_state *S, int rt, const void *p)
{
    rg_vu0s_gpr_w64(S, rt, (rg_vu_u64)(unsigned long)p);
}

/* qword / float access for ported C (bound-register style) */
static inline float rg_vu0s_getf(rg_vu0_state *S, int vf, int lane) { return rg_u2f(S->vf[vf].u[lane]); }
static inline float rg_vu0s_getq(rg_vu0_state *S) { return rg_u2f(S->q); }


/* Call-site spellings: the state is named where the call is written, so a
 * translation unit decides which register file it uses (see RG_VU0_LOCAL). */
#define rg_vu0_setvf(...) rg_vu0s_setvf(&rg_vu0, __VA_ARGS__)
#define rg_vu0_scalar(...) rg_vu0s_scalar(&rg_vu0, __VA_ARGS__)
#define rg_vu0_fmac(...) rg_vu0s_fmac(&rg_vu0, __VA_ARGS__)
#define rg_vu0_opmula(...) rg_vu0s_opmula(&rg_vu0, __VA_ARGS__)
#define rg_vu0_opmsub(...) rg_vu0s_opmsub(&rg_vu0, __VA_ARGS__)
#define rg_vu0_abs(...) rg_vu0s_abs(&rg_vu0, __VA_ARGS__)
#define rg_vu0_move(...) rg_vu0s_move(&rg_vu0, __VA_ARGS__)
#define rg_vu0_mr32(...) rg_vu0s_mr32(&rg_vu0, __VA_ARGS__)
#define rg_vu0_ftoi(...) rg_vu0s_ftoi(&rg_vu0, __VA_ARGS__)
#define rg_vu0_itof(...) rg_vu0s_itof(&rg_vu0, __VA_ARGS__)
#define rg_vu0_clip(...) rg_vu0s_clip(&rg_vu0, __VA_ARGS__)
#define rg_vu0_div(...) rg_vu0s_div(&rg_vu0, __VA_ARGS__)
#define rg_vu0_sqrt(...) rg_vu0s_sqrt(&rg_vu0, __VA_ARGS__)
#define rg_vu0_rsqrt(...) rg_vu0s_rsqrt(&rg_vu0, __VA_ARGS__)
#define rg_vu0_waitq() rg_vu0s_waitq(&rg_vu0)
#define rg_vu0_lqc2(...) rg_vu0s_lqc2(&rg_vu0, __VA_ARGS__)
#define rg_vu0_sqc2(...) rg_vu0s_sqc2(&rg_vu0, __VA_ARGS__)
#define rg_vu0_gpr_w64(...) rg_vu0s_gpr_w64(&rg_vu0, __VA_ARGS__)
#define rg_vu0_gpr_r32(...) rg_vu0s_gpr_r32(&rg_vu0, __VA_ARGS__)
#define rg_vu0_mfc1(...) rg_vu0s_mfc1(&rg_vu0, __VA_ARGS__)
#define rg_vu0_mtc1(...) rg_vu0s_mtc1(&rg_vu0, __VA_ARGS__)
#define rg_vu0_qmtc2(...) rg_vu0s_qmtc2(&rg_vu0, __VA_ARGS__)
#define rg_vu0_qmfc2(...) rg_vu0s_qmfc2(&rg_vu0, __VA_ARGS__)
#define rg_vu0_ctl_read(...) rg_vu0s_ctl_read(&rg_vu0, __VA_ARGS__)
#define rg_vu0_ctl_write(...) rg_vu0s_ctl_write(&rg_vu0, __VA_ARGS__)
#define rg_vu0_cfc2(...) rg_vu0s_cfc2(&rg_vu0, __VA_ARGS__)
#define rg_vu0_ctc2(...) rg_vu0s_ctc2(&rg_vu0, __VA_ARGS__)
#define rg_vu0_lq(...) rg_vu0s_lq(&rg_vu0, __VA_ARGS__)
#define rg_vu0_sq(...) rg_vu0s_sq(&rg_vu0, __VA_ARGS__)
#define rg_vu0_gptr(...) rg_vu0s_gptr(&rg_vu0, __VA_ARGS__)
#define rg_vu0_gpr_setp(...) rg_vu0s_gpr_setp(&rg_vu0, __VA_ARGS__)
#define rg_vu0_getf(...) rg_vu0s_getf(&rg_vu0, __VA_ARGS__)
#define rg_vu0_getq() rg_vu0s_getq(&rg_vu0)

/* ------------------------------------------------ micro mode (vcallms) */
/* VU0 micro mode shares this register file (src/ps2/vu0_micro.c): vcallms
   copies vf1-31/ACC/vi1-15/Q/P/I/R/clip into the bound interpreter VU0,
   runs the program at imm*8 to its E bit, and copies them back, so macro and
   micro mode see ONE state.  Returns 0, or -1 (no VU0 bound / runaway).
   rg_vu0_micro_bind takes the src/ps2/vu `vu_state` whose micro memory holds
   the uploaded programs (src/runtime binds its VU0). */
struct vu_state;
void rg_vu0_micro_bind(struct vu_state *vu);
struct vu_state *rg_vu0_micro_bound(void);
int rg_vu0_vcallms(unsigned imm);

/* The game's only VU0 microprogram (vcallms 0x0, uploaded by GfxSysInit's
 * VIF0 chain D_00445810) as native C: src/sce/vu0/vu0_srt.c.  In: s = scale
 * (xyz), r = Euler angles (xyz, radians), t = translation (xyz).  Out: the
 * four rows vf4..vf7 the program leaves, i.e. diag(s) * Rx * Ry * Rz with row
 * 3 = (t.xyz, 1), computed with the program's own sin/cos polynomial and the
 * same operation order (bit-exact against the interpreter with VU floats,
 * ctest vu0native).  Native code only: nothing else of the program's register
 * state is kept (the census finds no reader of it). */
void rg_vu0_srt(rg_vf out[4], const rg_vf *s, const rg_vf *r, const rg_vf *t);

#ifdef __cplusplus
}
#endif

/* Register tokens for macro token-pasting (libvu0.h passes vf5, xyzw, x, a1). */
#define RG_VF_vf0 0
#define RG_VF_vf1 1
#define RG_VF_vf2 2
#define RG_VF_vf3 3
#define RG_VF_vf4 4
#define RG_VF_vf5 5
#define RG_VF_vf6 6
#define RG_VF_vf7 7
#define RG_VF_vf8 8
#define RG_VF_vf9 9
#define RG_VF_vf10 10
#define RG_VF_vf11 11
#define RG_VF_vf12 12
#define RG_VF_vf13 13
#define RG_VF_vf14 14
#define RG_VF_vf15 15
#define RG_VF_vf16 16
#define RG_VF_vf17 17
#define RG_VF_vf18 18
#define RG_VF_vf19 19
#define RG_VF_vf20 20
#define RG_VF_vf21 21
#define RG_VF_vf22 22
#define RG_VF_vf23 23
#define RG_VF_vf24 24
#define RG_VF_vf25 25
#define RG_VF_vf26 26
#define RG_VF_vf27 27
#define RG_VF_vf28 28
#define RG_VF_vf29 29
#define RG_VF_vf30 30
#define RG_VF_vf31 31
#define RG_MASK_x RG_X
#define RG_MASK_y RG_Y
#define RG_MASK_z RG_Z
#define RG_MASK_w RG_W
#define RG_MASK_xy RG_XY
#define RG_MASK_xz RG_XZ
#define RG_MASK_yz RG_YZ
#define RG_MASK_xyz RG_XYZ
#define RG_MASK_xw RG_XW
#define RG_MASK_yw RG_YW
#define RG_MASK_xyw RG_XYW
#define RG_MASK_zw RG_ZW
#define RG_MASK_xzw RG_XZW
#define RG_MASK_yzw RG_YZW
#define RG_MASK_xyzw RG_XYZW
#define RG_BC_x RG_BC_X
#define RG_BC_y RG_BC_Y
#define RG_BC_z RG_BC_Z
#define RG_BC_w RG_BC_W
#define RG_GPR_zero 0
#define RG_GPR_at 1
#define RG_GPR_v0 2
#define RG_GPR_v1 3
#define RG_GPR_a0 4
#define RG_GPR_a1 5
#define RG_GPR_a2 6
#define RG_GPR_a3 7
#define RG_GPR_t0 8
#define RG_GPR_t1 9
#define RG_GPR_t2 10
#define RG_GPR_t3 11
#define RG_GPR_t4 12
#define RG_GPR_t5 13
#define RG_GPR_t6 14
#define RG_GPR_t7 15

#endif /* RG_PORT_VU0_H */
