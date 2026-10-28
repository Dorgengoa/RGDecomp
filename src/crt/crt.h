/* SPDX-License-Identifier: CC0-1.0 */
/* src/crt: the game-name bindings of the C/C++ runtime the game links
 * (newlib libc/libm, gcc 2.9 libgcc + soft-double, mwcc runtime, MSL C++).
 * Their asm bodies are excluded from the build (PLAN.md transform 6,
 * game/EXCLUDED.tsv); docs/BINDINGS.md lists every symbol and its provider.
 *
 * Rules:
 *  - Game names only.  The handful of unsuffixed libc names the game calls
 *    (memcpy, memset, strcpy, strlen, strcmp, strcat, strncpy, strncmp,
 *    memmove) resolve to the host CRT directly; nothing here redefines a host
 *    CRT name.  `__assert` (newlib's) does not exist in the MSVC CRT.
 *  - Semantics are the game's where they differ from the host: newlib's
 *    rand LCG, the BSD qsort (equal elements land where retail puts them),
 *    newlib's ctype quirks in str*casecmp/toupper, soft-double conversions
 *    that round twice, MSL's array cookies.
 *  - Doubles: the EE passes soft-double values as 64-bit integers in GPRs;
 *    cdecl passes both double and int64 as 8 stack bytes, so arguments agree
 *    whatever the caller declared.  RETURNS do not (ST0 vs EDX:EAX): these
 *    return double, and callers that declare s64 are listed as ABI conflicts
 *    in docs/BINDINGS.md (build/bind-i686/abi_conflicts.tsv) for the protos
 *    stage to fix.
 */
#ifndef RG_CRT_H
#define RG_CRT_H

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/* x64 (docs/X64-PLAN.md): a pointer stored in game memory keeps its 4-byte retail size
 * (`__ptr32 __uptr`; every x64 host address is below 2 GB); empty on i686 */
#ifndef CRT_P32
#if defined(__x86_64__)
#define CRT_P32 __ptr32 __uptr
#else
#define CRT_P32
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ---- libc (newlib) ---- */
void __assert(const char *file, int line, const char *expr);
void Abort_12de80(void);
void Exit_12f4e0(int code);
int Fflush_12f590(void *fp);
int Fprintf_12f9a0(void *fp, const char *fmt, ...);
int Vprintf_138e68(const char *fmt, va_list ap);
int Sprintf_1343b8(char *buf, const char *fmt, ...);
char *Index_1308f0(const char *s, int c);
char *Strchr_1347c0(const char *s, int c);
char *Strstr_135138(const char *s, const char *find);
long Strtol_136360(const char *s, char **end, int base);
double Atof_12dee8(const char *s);
int Toupper_1363e0(int c);
char *Strupr_136390(char *s);
int Strcasecmp_1345b8(const char *a, const char *b);
int Strncasecmp_134ce8(const char *a, const char *b, size_t n);
int Rand_133710(void);
void Srand_1336f8(unsigned seed);
void Qsort_132d08(void *base, size_t n, size_t es, int (*cmp)(const void *, const void *));

/* ---- heap (newlib malloc over the game RAM heap, sbrk from src/runtime) ---- */
void *Malloc_130dd8(size_t n);
void Free_130e30(void *p);
void *Memalign_130ba8(size_t align, size_t n);
/* Use the game's own allocator state (retail .data: av_ at 0x00449868, the
 * parameters/statistics block at 0x00449C70); without it a private copy is
 * used.  Call before the first allocation. */
void rg_crt_heap_bind(void *av_00449868, void *params_00449c70);
/* test/diagnostic hooks */
size_t rg_crt_heap_free_bytes(void);
int rg_crt_heap_check(void);

/* ---- libm (newlib, float and double) ---- */
float Sinf_128fd0(float x);
float Cosf_128d30(float x);
float Tanf_1290b8(float x);
float Acosf_129178(float x);
float Asinf_129190(float x);
float Atan2f_1291a8(float y, float x);
float Powf_1291c0(float x, float y);
float Floorf_128e30(float x);
/* the retail fdlibm float routines (crt_eelibm.c; used by the above in the EE MXCSR mode) */
float rg_ee_sinf(float x);
float rg_ee_cosf(float x);
float rg_ee_tanf(float x);
float rg_ee_asinf(float x);
float rg_ee_acosf(float x);
float rg_ee_atan2f(float y, float x);
float rg_ee_powf(float x, float y);
double Sin_128880(double x);
double Tan_1289b8(double x);
double AtanDouble_127d68(double x);
double Cos_128278(double x);
double Sqrt_129160(double x);
double FabsDouble_1283a0(double x);
/* libm double wrappers (j IeeeAtan2_123838 / j IeeeAcos_123110; docs/LINK.md) */
double Atan2_129148(double y, double x);
double Acos_129130(double x);
int Finite_1283d8(double x);
int Isnan_128658(double x);

/* ---- gcc soft-double (fp-bit) and libgcc ---- */
double dpadd(double a, double b);
double dpsub(double a, double b);
double dpmul(double a, double b);
double dpdiv(double a, double b);
float dptofp(double a);
double fptodp(float a);
int dptoli(double a);
double litodp(int a);
int DoubleCmp_13b948(double a, double b);
int64_t Divdi3_139188(int64_t a, int64_t b);
int64_t ModDi3_139820(int64_t a, int64_t b);
uint64_t UDivDi3_139eb0(uint64_t a, uint64_t b);
uint64_t UModDi3_13a430(uint64_t a, uint64_t b);
int64_t DoubleToS64_13ac40(double a);
uint64_t DoubleToU64_13ab28(double a);
uint32_t DoubleToUInt_13bb78(double a);
int64_t FloatToS64_13ade0(float a);
uint64_t FloatToU64_13acb8(float a);
double S64ToDouble_13a998(int64_t a);
float S64ToFloat_13aa40(int64_t a);

/* ---- mwcc runtime ---- */
double UIntToDouble_100320(uint32_t a);
double U64ToDouble_100370(uint64_t a);

/* ---- MSL C++ runtime ---- */
void *OperatorNew_100990(size_t n);
void OperatorDelete_100840(void *p);
typedef void (*rg_xtor_fn)(void *obj, int flag);
void *ConstructNewArray_100710(void *block, rg_xtor_fn ctor, rg_xtor_fn dtor, size_t size, size_t n);
void ConstructArray_100620(void *ptr, rg_xtor_fn ctor, rg_xtor_fn dtor, size_t size, size_t n);
void DestroyArray_1005b0(void *ptr, rg_xtor_fn dtor, size_t size, size_t n);
void DestroyGlobalChain_100d60(void *chain);
void *IosBaseInitCtor_102bd0(void *self);
/* basic_string<char> internals (crt_mslstr.c) */
void StringReserve_107e80(void *s, uint32_t n);
void *StringReplace_106f90(void *s, uint32_t pos, uint32_t n1, const char *first, const char *last,
                           int alloc_unused);
void *StringReplaceFill_1075d0(void *s, uint32_t pos, uint32_t n1, uint32_t n2, int c);
void *WIosBaseInitCtor_103110(void *self);
/* basic_ostream flush and sentry (narrow + wide; sentry = {u8 ok, u8 flushed, pad, os}) */
void *OstreamFlush_1040b0(void *os);
void *WOstreamFlush_104320(void *os);
void *OstreamSentryCtor_106230(void *sentry, void *os);
void *WOstreamSentryCtor_106510(void *sentry, void *os);

#ifdef __cplusplus
}
#endif
#endif
