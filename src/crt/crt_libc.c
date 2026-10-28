/* SPDX-License-Identifier: CC0-1.0 */
/* newlib libc entry points under the game's names (docs/BINDINGS.md).
 * Where the host CRT has the same contract it is used; where newlib's
 * observable behaviour differs (rand's LCG, qsort's ordering of equal keys,
 * the ctype table quirks of str*casecmp/toupper) newlib's is reproduced. */
#include "crt.h"
/* x64 (docs/X64-PLAN.md): size parameters from the game are 32-bit values */
#if defined(_WIN64)
#define RG_GSIZE(x) ((x) = (size_t)(uint32_t)(x))
#else
#define RG_GSIZE(x) ((void)0)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* src/runtime (crt0.c): leave the guest program with an exit code */
extern void rg_ps2_exit(int code);

/* ---- assert / exit ---------------------------------------------------- */

/* newlib __assert(file, line, expr): message on stderr, then abort() */
void __assert(const char *file, int line, const char *expr)
{
    fprintf(stderr, "assertion \"%s\" failed: file \"%s\", line %d\n", expr, file, line);
    fflush(stderr);
    Abort_12de80();
}

/* abort(): raise(SIGABRT) (no handler is installed), then _exit(1).  Weak:
 * the runtime may bind a stronger one (it owns guest-program exit). */
__attribute__((weak)) void Abort_12de80(void)
{
    fprintf(stderr, "rg: game called abort()\n");
    fflush(stderr);
    rg_ps2_exit(1);
}

/* exit(code): atexit list + __cleanup + Exit syscall = rg_ps2_exit.  Weak for
 * the same reason (src/runtime/crt0.c has a TODO to bind it there). */
__attribute__((weak)) void Exit_12f4e0(int code)
{
    fflush(stdout);
    fflush(stderr);
    rg_ps2_exit(code);
}

/* ---- stdio ------------------------------------------------------------ */
/* The game's FILE pointers are newlib's (reent _stdout/_stderr); the only
 * callers print diagnostics, so every stream is the host's stderr. */
int Fflush_12f590(void *fp)
{
    (void)fp;
    fflush(stdout);
    return fflush(stderr);
}

#if defined(_WIN64)
/* x64 (docs/X64-PLAN.md section 0.7): the game's variadic arguments are retail's 32-bit
 * words.  A pointer it passes for %s is often an s32 (`(s32)rec->name`,
 * SaveHeaderBuild_3e5520) whose 8-byte vararg slot has undefined upper bits, so the host
 * vsprintf would read a wild pointer.  rg_gvformat walks the format and fetches every
 * integer / pointer conversion as a 32-bit word (64 bits only for ll / q / j),
 * floating ones as double, and formats one conversion at a time. */
static int rg_gvformat(char *out, size_t cap, const char *fmt, va_list ap)
{
    size_t o = 0;
    char spec[64], tmp[512];
    const char *p = fmt;
    while (*p) {
        if (*p != '%') {
            if (o + 1 < cap) out[o] = *p;
            o++;
            p++;
            continue;
        }
        const char *s = p++;
        size_t k = 0;
        int star[2], nstar = 0, wide = 0;
        while (*p && strchr("-+ #0", *p)) p++;
        if (*p == '*') { star[nstar++] = va_arg(ap, int); p++; }
        else while (*p >= '0' && *p <= '9') p++;
        if (*p == '.') {
            p++;
            if (*p == '*') { star[nstar++] = va_arg(ap, int); p++; }
            else while (*p >= '0' && *p <= '9') p++;
        }
        while (*p && strchr("hlLqjzt", *p)) {
            if ((*p == 'l' && p[1] == 'l') || *p == 'q' || *p == 'j') wide = 1;
            p += (*p == 'l' && p[1] == 'l') ? 2 : 1;
        }
        char c = *p ? *p++ : '\0';
        /* the spec without its length modifiers, for the host snprintf */
        for (const char *q = s; q < p && k + 4 < sizeof spec; q++)
            if (!strchr("hlLqjzt", *q) || q == p - 1) spec[k++] = *q;
        spec[k] = '\0';
        int n;
        switch (c) {
        case 'd': case 'i': case 'c':
            if (wide) {
                long long v = va_arg(ap, long long);
                spec[k - 1] = 'l'; spec[k] = 'l'; spec[k + 1] = c; spec[k + 2] = '\0';
                n = nstar == 2 ? snprintf(tmp, sizeof tmp, spec, star[0], star[1], v)
                  : nstar == 1 ? snprintf(tmp, sizeof tmp, spec, star[0], v) : snprintf(tmp, sizeof tmp, spec, v);
            } else {
                int v = va_arg(ap, int);
                n = nstar == 2 ? snprintf(tmp, sizeof tmp, spec, star[0], star[1], v)
                  : nstar == 1 ? snprintf(tmp, sizeof tmp, spec, star[0], v) : snprintf(tmp, sizeof tmp, spec, v);
            }
            break;
        case 'u': case 'x': case 'X': case 'o':
            if (wide) {
                unsigned long long v = va_arg(ap, unsigned long long);
                spec[k - 1] = 'l'; spec[k] = 'l'; spec[k + 1] = c; spec[k + 2] = '\0';
                n = nstar == 2 ? snprintf(tmp, sizeof tmp, spec, star[0], star[1], v)
                  : nstar == 1 ? snprintf(tmp, sizeof tmp, spec, star[0], v) : snprintf(tmp, sizeof tmp, spec, v);
            } else {
                unsigned v = va_arg(ap, unsigned);
                n = nstar == 2 ? snprintf(tmp, sizeof tmp, spec, star[0], star[1], v)
                  : nstar == 1 ? snprintf(tmp, sizeof tmp, spec, star[0], v) : snprintf(tmp, sizeof tmp, spec, v);
            }
            break;
        case 's': case 'p': {
            const char *v = (const char *)(uintptr_t)va_arg(ap, unsigned);
            if (c == 's' && !v) v = "(null)";
            n = nstar == 2 ? snprintf(tmp, sizeof tmp, spec, star[0], star[1], v)
              : nstar == 1 ? snprintf(tmp, sizeof tmp, spec, star[0], v) : snprintf(tmp, sizeof tmp, spec, v);
            break;
        }
        case 'n': {
            int *v = (int *)(uintptr_t)va_arg(ap, unsigned);
            if (v) *v = (int)o;
            n = 0;
            tmp[0] = '\0';
            break;
        }
        case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A': {
            double v = va_arg(ap, double);
            n = nstar == 2 ? snprintf(tmp, sizeof tmp, spec, star[0], star[1], v)
              : nstar == 1 ? snprintf(tmp, sizeof tmp, spec, star[0], v) : snprintf(tmp, sizeof tmp, spec, v);
            break;
        }
        case '%':
            tmp[0] = '%'; tmp[1] = '\0'; n = 1;
            break;
        default: /* unknown conversion: copy it through */
            n = snprintf(tmp, sizeof tmp, "%.*s", (int)(p - s), s);
            break;
        }
        if (n < 0) n = 0;
        if ((size_t)n >= sizeof tmp) n = (int)sizeof tmp - 1;
        for (int i = 0; i < n; i++) {
            if (o + 1 < cap) out[o] = tmp[i];
            o++;
        }
    }
    if (cap) out[o < cap ? o : cap - 1] = '\0';
    return (int)o;
}
#endif

int Fprintf_12f9a0(void *fp, const char *fmt, ...)
{
    va_list ap;
    int n;
    (void)fp;
    va_start(ap, fmt);
#if defined(_WIN64)
    {
        static char buf[4096];
        n = rg_gvformat(buf, sizeof buf, fmt, ap);
        fputs(buf, stderr);
    }
#else
    n = vfprintf(stderr, fmt, ap);
#endif
    va_end(ap);
    return n;
}

#if defined(_WIN64)
int Vprintf_138e68(const char *fmt, va_list ap)
{
    static char buf[4096];
    int n = rg_gvformat(buf, sizeof buf, fmt, ap);
    fputs(buf, stdout);
    return n;
}
#else
int Vprintf_138e68(const char *fmt, va_list ap) { return vprintf(fmt, ap); }
#endif

int Sprintf_1343b8(char *buf, const char *fmt, ...)
{
    va_list ap;
    int n;
    va_start(ap, fmt);
#if defined(_WIN64)
    n = rg_gvformat(buf, (size_t)1 << 20, fmt, ap); /* unbounded like vsprintf */
#else
    n = vsprintf(buf, fmt, ap);
#endif
    va_end(ap);
    return n;
}

/* ---- strings ---------------------------------------------------------- */
char *Index_1308f0(const char *s, int c) { return strchr(s, c); }
char *Strchr_1347c0(const char *s, int c) { return strchr(s, c); }
char *Strstr_135138(const char *s, const char *find) { return strstr(s, find); }
long Strtol_136360(const char *s, char **end, int base) { return strtol(s, end, base); }
/* atof = newlib _strtod_r (David Gay's strtod) as linked.  Its fast path (at most 15
 * significant digits, |exponent| within the exact powers of ten) is ONE inexact double
 * operation, and retail's soft double (gcc fp-bit) rounds toward zero: "0.1" is
 * 0x3FB9999999999999 there (0x3DCCCCCC after dptofp), not the correctly rounded
 * ...999A.  The same steps here use the native double ops, which follow the game's
 * MXCSR (round toward zero under RG_EE_FPU=chop, src/native/threads/rg_nk_internal.h).
 * Longer inputs take Gay's bignum correction loop on retail; the host's strtod (correct
 * rounding) stands in for it (docs/BRINGUP.md "Retail parity": text configs use short
 * numbers). */
double Atof_12dee8(const char *s)
{
    static const double tens[23] = {1e0, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11,
                                    1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19, 1e20, 1e21, 1e22};
    const char *p = s;
    int neg = 0, nd = 0, nf = 0, nz = 0, e = 0, any = 0;
    unsigned y = 0, z = 0;
    while (*p == ' ' || (*p >= 9 && *p <= 13))
        p++;
    if (*p == '-' || *p == '+')
        neg = *p++ == '-';
    while (*p == '0') {         /* leading zeros */
        p++;
        any = 1;
    }
    for (; *p >= '0' && *p <= '9'; nd++, p++, any = 1) {
        if (nd < 9)
            y = 10 * y + (unsigned)(*p - '0');
        else if (nd < 16)
            z = 10 * z + (unsigned)(*p - '0');
    }
    if (*p == '.') {
        p++;
        if (!nd)
            for (; *p == '0'; p++) {
                nz++;
                any = 1;
            }
        for (; *p >= '0' && *p <= '9'; p++) {
            int c = *p - '0';
            any = 1;
            nz++;
            if (c) {
                nf += nz;
                for (int i = 1; i < nz; i++) {
                    if (nd++ < 9)
                        y *= 10;
                    else if (nd <= 16)
                        z *= 10;
                }
                if (nd++ < 9)
                    y = 10 * y + (unsigned)c;
                else if (nd <= 16)
                    z = 10 * z + (unsigned)c;
                nz = 0;
            }
        }
    }
    if (!any)
        return 0.0;
    if (*p == 'e' || *p == 'E') {
        const char *q = p + 1;
        int eneg = 0, ex = 0, digs = 0;
        if (*q == '-' || *q == '+')
            eneg = *q++ == '-';
        for (; *q >= '0' && *q <= '9'; q++, digs++)
            ex = ex < 100000 ? 10 * ex + (*q - '0') : ex;
        if (digs)
            e = eneg ? -ex : ex;
    }
    if (!nd)
        return neg ? -0.0 : 0.0;
    e -= nf;
    if (nd <= 15) {
        volatile double rv = (double)y;     /* volatile: no folding across the MXCSR mode */
        if (nd > 9)
            rv = tens[nd - 9] * rv + (double)z;
        if (!e)
            return neg ? -rv : rv;
        if (e > 0) {
            if (e <= 22) {
                rv = rv * tens[e];
                return neg ? -rv : rv;
            }
            int i = 15 - nd;
            if (e <= 22 + i) {
                rv = rv * tens[i];
                rv = rv * tens[e - i];
                return neg ? -rv : rv;
            }
        } else if (e >= -22) {
            rv = rv / tens[-e];
            return neg ? -rv : rv;
        }
    }
    return strtod(s, NULL);
}

/* newlib's ctype bits as the game reads them: _ctype_+1 indexed by c.  For
 * 0..255 the upper/lower bits are plain ASCII A-Z / a-z.  The game indexes
 * with a SIGNED char in places, so c = -128..-1 reads the 128 .rodata bytes
 * before the table; their upper (bit 0) and lower (bit 1) bits, measured
 * from retail 0x00457E11..0x00457E90, are these masks (bit c + 128). */
static const uint32_t neg_upper[4] = {0x5E858D01u, 0xF75F809Eu, 0x8C678320u, 0x00543285u};
static const uint32_t neg_lower[4] = {0xC8459A0Au, 0x6E498564u, 0x5ACB10A9u, 0x01086850u};

static int ct_upper(int c)
{
    if (c >= 0)
        return c >= 'A' && c <= 'Z';
    if (c < -128)
        return 0;
    c += 128;
    return (neg_upper[c >> 5] >> (c & 31)) & 1;
}

static int ct_lower(int c)
{
    if (c >= 0)
        return c >= 'a' && c <= 'z';
    if (c < -128)
        return 0;
    c += 128;
    return (neg_lower[c >> 5] >> (c & 31)) & 1;
}

/* toupper(c): `_ctype_[c+1] & _L ? c - 0x20 : c` with c as given */
int Toupper_1363e0(int c) { return ct_lower(c) ? c - 0x20 : c; }

/* strupr: in place; each SIGNED char that the table calls lower gets -0x20 */
char *Strupr_136390(char *s)
{
    char *p;
    for (p = s; *p; p++)
        if (ct_lower((signed char)*p))
            *p = (char)((signed char)*p - 0x20);
    return s;
}

static int fold_s(signed char c) { return ct_upper(c) ? c + 0x20 : c; }
static int fold_u(unsigned char c) { return ct_upper(c) ? c + 0x20 : c; }

/* strcasecmp as linked: the loop folds SIGNED chars, the final difference
 * folds the UNSIGNED bytes where the loop stopped. */
int Strcasecmp_1345b8(const char *a, const char *b)
{
    const signed char *s1 = (const signed char *)a, *s2 = (const signed char *)b;
    while (*s1 && fold_s(*s1) == fold_s(*s2)) {
        s1++;
        s2++;
    }
    return fold_u((unsigned char)*s1) - fold_u((unsigned char)*s2);
}

int Strncasecmp_134ce8(const char *a, const char *b, size_t n)
{ RG_GSIZE(n);
    const signed char *s1 = (const signed char *)a, *s2 = (const signed char *)b;
    if (n == 0)
        return 0;
    for (n--;; n--, s1++, s2++) {
        if (fold_s(*s1) != fold_s(*s2))
            break;
        if (n == 0 || *s1 == 0 || *s2 == 0)
            break;
    }
    return fold_u((unsigned char)*s1) - fold_u((unsigned char)*s2);
}

/* ---- rand ------------------------------------------------------------- */
/* newlib: 64-bit LCG in the reent struct (_impure_ptr->_new._reent._rand_next,
 * initial value 1). */
uint64_t rg_crt_rand_next = 1;   /* not static: tools/parity reads it (rg-game.map) */
#define rand_next rg_crt_rand_next

void Srand_1336f8(unsigned seed) { rand_next = seed; }

int Rand_133710(void)
{
    rand_next = rand_next * 6364136223846793005ull + 1;
    return (int)((rand_next >> 32) & 0x7FFFFFFF);
}

/* ---- qsort ------------------------------------------------------------ */
/* newlib's qsort (the 4.4BSD-Lite Bentley-McIlroy code): median of three
 * (ninther above 40), three-way partition, insertion sort below 7 elements
 * and when a partition pass did no swap.  The ORDER of equal elements is
 * part of the game's behaviour, so the algorithm is reproduced; how bytes
 * are swapped is not observable and is a plain byte loop here. */
typedef int (*cmp_fn)(const void *, const void *);

static void swapb(char *a, char *b, size_t n)
{
    while (n--) {
        char t = *a;
        *a++ = *b;
        *b++ = t;
    }
}

static char *med3(char *a, char *b, char *c, cmp_fn cmp)
{
    return cmp(a, b) < 0 ? (cmp(b, c) < 0 ? b : (cmp(a, c) < 0 ? c : a))
                         : (cmp(b, c) > 0 ? b : (cmp(a, c) < 0 ? a : c));
}

void Qsort_132d08(void *base, size_t n, size_t es, cmp_fn cmp)
{ RG_GSIZE(n); RG_GSIZE(es);
    char *a = (char *)base, *pa, *pb, *pc, *pd, *pl, *pm, *pn;
    size_t d, r;
    int cr, swap_cnt;

loop:
    swap_cnt = 0;
    if (n < 7) {
        for (pm = a + es; pm < a + n * es; pm += es)
            for (pl = pm; pl > a && cmp(pl - es, pl) > 0; pl -= es)
                swapb(pl, pl - es, es);
        return;
    }
    pm = a + (n / 2) * es;
    if (n > 7) {
        pl = a;
        pn = a + (n - 1) * es;
        if (n > 40) {
            d = (n / 8) * es;
            pl = med3(pl, pl + d, pl + 2 * d, cmp);
            pm = med3(pm - d, pm, pm + d, cmp);
            pn = med3(pn - 2 * d, pn - d, pn, cmp);
        }
        pm = med3(pl, pm, pn, cmp);
    }
    swapb(a, pm, es);
    pa = pb = a + es;
    pc = pd = a + (n - 1) * es;
    for (;;) {
        while (pb <= pc && (cr = cmp(pb, a)) <= 0) {
            if (cr == 0) {
                swap_cnt = 1;
                swapb(pa, pb, es);
                pa += es;
            }
            pb += es;
        }
        while (pb <= pc && (cr = cmp(pc, a)) >= 0) {
            if (cr == 0) {
                swap_cnt = 1;
                swapb(pc, pd, es);
                pd -= es;
            }
            pc -= es;
        }
        if (pb > pc)
            break;
        swapb(pb, pc, es);
        swap_cnt = 1;
        pb += es;
        pc -= es;
    }
    if (swap_cnt == 0) { /* switch to insertion sort */
        for (pm = a + es; pm < a + n * es; pm += es)
            for (pl = pm; pl > a && cmp(pl - es, pl) > 0; pl -= es)
                swapb(pl, pl - es, es);
        return;
    }
    pn = a + n * es;
    r = (size_t)(pa - a) < (size_t)(pb - pa) ? (size_t)(pa - a) : (size_t)(pb - pa);
    if (r > 0)
        swapb(a, pb - r, r);
    r = (size_t)(pd - pc) < (size_t)(pn - pd) - es ? (size_t)(pd - pc) : (size_t)(pn - pd) - es;
    if (r > 0)
        swapb(pb, pn - r, r);
    if ((r = (size_t)(pb - pa)) > es)
        Qsort_132d08(a, r / es, es, cmp);
    if ((r = (size_t)(pd - pc)) > es) {
        /* iterate rather than recurse */
        a = pn - r;
        n = r / es;
        goto loop;
    }
}
