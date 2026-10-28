/* SPDX-License-Identifier: CC0-1.0 */
/* libm, gcc soft-double (fp-bit) helpers, libgcc 64-bit division and the
 * mwcc/libgcc int<->float conversions, under the game's names
 * (docs/BINDINGS.md).
 *
 * - float libm: under the game's EE MXCSR (RG_EE_FPU=chop, the default) the retail
 *   fdlibm float routines (crt_eelibm.c, written from the listings); with
 *   RG_EE_FPU=ieee (MXCSR round to nearest) the host's, as before 2026-10-24.
 *   Double libm: the host's (retail: fdlibm double on fp-bit; not modelled).
 * - fp-bit dp*: IEEE double, but retail's fp-bit rounds TOWARD ZERO (verified on PCSX2
 *   2026-10-19: dptofp(0.70136020040698988) = 0x3F338C57, the RN neighbour is ...58;
 *   docs/BRINGUP.md "Retail parity"), like the EE FPU: exactly SSE2 double under the
 *   game's MXCSR when RG_EE_FPU=chop (src/native/threads/rg_nk_internal.h).
 * - Conversions follow the retail call chains step by step (they round
 *   twice in places, saturate in others), written as native double ops
 *   that are exact where the soft-float steps are exact. */
#include "crt.h"

#include <math.h>
#include <string.h>

/* ---- libm --------------------------------------------------------------- */
/* EE mode = MXCSR rounding toward zero (rg_nk_internal.h nk_guest_csr) */
#if defined(__i386__) || defined(__x86_64__) || defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
static inline int ee_mode(void) { return (_mm_getcsr() & 0x6000u) == 0x6000u; }
#else
static inline int ee_mode(void) { return 1; }
#endif
float Sinf_128fd0(float x) { return ee_mode() ? rg_ee_sinf(x) : sinf(x); }
float Cosf_128d30(float x) { return ee_mode() ? rg_ee_cosf(x) : cosf(x); }
float Tanf_1290b8(float x) { return ee_mode() ? rg_ee_tanf(x) : tanf(x); }
float Acosf_129178(float x) { return ee_mode() ? rg_ee_acosf(x) : acosf(x); }
float Asinf_129190(float x) { return ee_mode() ? rg_ee_asinf(x) : asinf(x); }
float Atan2f_1291a8(float y, float x) { return ee_mode() ? rg_ee_atan2f(y, x) : atan2f(y, x); }
float Powf_1291c0(float x, float y) { return ee_mode() ? rg_ee_powf(x, y) : powf(x, y); }
float Floorf_128e30(float x) { return floorf(x); }
#if defined(_WIN64)
/* x64 (docs/X64-PLAN.md section 0.7): the x64 UCRT's sin / cos / tan are WRONG under the
 * game's MXCSR (round toward zero): errors up to 2^32 ulp (tools/x64/libmcheck.c); the
 * i686 UCRT's stay within 3 ulp of their round-to-nearest results.  So on x64 the host
 * double libm runs with MXCSR rounding to nearest (FTZ / DAZ kept).  Not bit-equal to
 * i686 (a different libm: 1 ulp apart in a few % of inputs). */
static inline unsigned rn_enter(void) { unsigned o = _mm_getcsr(); _mm_setcsr(o & ~0x6000u); return o; }
#define HOST_RN(expr) do { unsigned o_ = rn_enter(); double r_ = (expr); _mm_setcsr(o_); return r_; } while (0)
#else
#define HOST_RN(expr) return (expr)
#endif
double Sin_128880(double x) { HOST_RN(sin(x)); }
double Tan_1289b8(double x) { HOST_RN(tan(x)); }
double AtanDouble_127d68(double x) { HOST_RN(atan(x)); }
double Cos_128278(double x) { HOST_RN(cos(x)); }
double Sqrt_129160(double x) { return sqrt(x); }
double FabsDouble_1283a0(double x) { return fabs(x); }
double Atan2_129148(double y, double x) { HOST_RN(atan2(y, x)); }
double Acos_129130(double x) { HOST_RN(acos(x)); }
/* newlib finite(): exponent != 0x7FF; isnan(): NaN bit pattern */
int Finite_1283d8(double x)
{
    uint64_t b;
    memcpy(&b, &x, 8);
    return ((b >> 52) & 0x7FF) != 0x7FF;
}
int Isnan_128658(double x)
{
    uint64_t b;
    memcpy(&b, &x, 8);
    return ((b >> 52) & 0x7FF) == 0x7FF && (b & 0xFFFFFFFFFFFFFull) != 0;
}

/* ---- fp-bit soft double ----------------------------------------------- */
double dpadd(double a, double b) { return a + b; }
double dpsub(double a, double b) { return a - b; }
double dpmul(double a, double b) { return a * b; }
double dpdiv(double a, double b) { return a / b; }
float dptofp(double a) { return (float)a; }
double fptodp(float a) { return (double)a; }
double litodp(int a) { return (double)a; }

/* fp-bit __fixdfsi: NaN -> 0, |a| >= 2^31 saturates, else truncation */
int dptoli(double a)
{
    if (a != a)
        return 0;
    if (a >= 2147483648.0)
        return 0x7FFFFFFF;
    if (a <= -2147483648.0)
        return (int)0x80000000u;
    return (int)a;
}

/* __fpcmp_parts_d: -1 / 0 / 1; an unordered pair compares as 1 */
int DoubleCmp_13b948(double a, double b)
{
    if (a != a || b != b)
        return 1;
    return a < b ? -1 : a > b ? 1 : 0;
}

/* ---- libgcc 64-bit division ------------------------------------------- */
/* The EE divu does not trap and libgcc does not check: x / 0 is whatever
 * the long-division loop leaves.  The host returns 0 instead of trapping
 * (PLAN.md hazard "integer divide by zero"; not reached in traces so far). */
int64_t Divdi3_139188(int64_t a, int64_t b)
{
    if (b == 0)
        return 0;
    if (b == -1)
        return (int64_t)(0 - (uint64_t)a); /* INT64_MIN / -1 wraps, no trap */
    return a / b;
}
int64_t ModDi3_139820(int64_t a, int64_t b)
{
    if (b == 0)
        return a;
    if (b == -1)
        return 0;
    return a % b;
}
uint64_t UDivDi3_139eb0(uint64_t a, uint64_t b) { return b ? a / b : 0; }
uint64_t UModDi3_13a430(uint64_t a, uint64_t b) { return b ? a % b : a; }

/* ---- conversions ------------------------------------------------------ */

/* __floatdidf as linked: hi * 65536 * 65536 (exact) + lo (one rounding) */
double S64ToDouble_13a998(int64_t a)
{
    double hi = (double)(int32_t)(a >> 32) * 65536.0 * 65536.0;
    double lo = (double)(int32_t)(uint32_t)a;
    if ((int32_t)(uint32_t)a < 0)
        lo += 4294967296.0;
    return hi + lo;
}

/* __floatdisf: a sticky bit against double rounding, then via double */
float S64ToFloat_13aa40(int64_t a)
{
    uint64_t u = (uint64_t)a;
    if (u + 0x1FFFFFFFFFFFFFull > 0x3FFFFFFFFFFFFEull && (u & 0x7FF) != 0)
        u |= 0x800;
    return (float)S64ToDouble_13a998((int64_t)u);
}

/* unsigned -> double: halve with a sticky bit when the top bit is set */
double U64ToDouble_100370(uint64_t a)
{
    if ((int64_t)a > 0)
        return S64ToDouble_13a998((int64_t)a);
    double h = S64ToDouble_13a998((int64_t)((a >> 1) | (a & 1)));
    return h + h;
}
double UIntToDouble_100320(uint32_t a) { return U64ToDouble_100370(a); }

/* fp-bit __fixunsdfsi as linked: NaN, negative, |a| < 1 -> 0;
 * Inf and >= 2^32 -> 0xFFFFFFFF; else truncation */
uint32_t DoubleToUInt_13bb78(double a)
{
    if (a != a || a < 1.0)
        return 0;
    if (a >= 4294967296.0)
        return 0xFFFFFFFFu;
    return (uint32_t)a;
}

/* libgcc __fixunsdfdi on the helpers above */
uint64_t DoubleToU64_13ab28(double a)
{
    if (DoubleCmp_13b948(a, 0.0) < 0)
        return 0;
    uint64_t v = (uint64_t)DoubleToUInt_13bb78(a * 2.3283064365386963e-10) << 32;
    a -= U64ToDouble_100370(v);
    if (DoubleCmp_13b948(a, 0.0) < 0)
        v -= DoubleToUInt_13bb78(0.0 - a);
    else
        v += DoubleToUInt_13bb78(a);
    return v;
}

int64_t DoubleToS64_13ac40(double a)
{
    if (DoubleCmp_13b948(a, 0.0) < 0)
        return (int64_t)(0 - DoubleToU64_13ab28(0.0 - a));
    return (int64_t)DoubleToU64_13ab28(a);
}

uint64_t FloatToU64_13acb8(float f) { return DoubleToU64_13ab28((double)f); }

int64_t FloatToS64_13ade0(float f)
{
    if (f < 0.0f)
        return (int64_t)(0 - FloatToU64_13acb8(-f));
    return (int64_t)FloatToU64_13acb8(f);
}
