/* SPDX-License-Identifier: CC0-1.0 */
/* Differential test of the VU float helpers (docs/VU.md "Performance"):
 * the live bit-manipulation versions (src/ps2/vu/vu_float.c,
 * vu_float_inl.h) against the pre-rewrite ldexp/frexp reference
 * (tests/vu/vu_float_ref.c), result bits AND condition bits.
 *
 *   rg-vu-float-diff CLASS [COUNT] [SEED]
 *
 * CLASS: to_d from_d add sub mul madd msub ftoi itof cmp clip div sqrt rsqrt
 *        efu vec all.  "vec" compares the four-lane SSE2 forms used by the
 *        block translator (vu_vec_inl.h) against the scalar helpers, lane
 *        by lane (results and MAC bits; to_d bit for bit; MAX/MINI, FTOI,
 *        ITOF), on COUNT random quads of edge, near-exponent and uniform
 *        operands under random dest masks.  For to_d, ftoi, itof, COUNT 0 means every 32-bit pattern
 *        (exhaustive; with a 4th argument K in 0..15, only the patterns
 *        K<<28 .. (K+1)<<28 - 1); otherwise random patterns.  Every binary class also
 *        runs the full cross product of the edge set (all 256 exponents x 8
 *        fractions x 2 signs = 4096 values, 16.7 M pairs) unless COUNT < 0
 *        (then |COUNT| random only).  "all" runs every class (COUNT each).
 *        "control" must fail: it compares add against mul. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vu.h"
#include "vu_decode.h"
#include "vu_float_inl.h"
#include "vu_float_ref.h"
#include "vu_vec_inl.h"

static uint64_t rng_s = 0x9E3779B97F4A7C15ull;
static uint64_t rnd64(void)
{
    uint64_t z = (rng_s += 0x9E3779B97F4A7C15ull);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ull;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBull;
    return z ^ (z >> 31);
}
static uint32_t rnd32(void) { return (uint32_t)(rnd64() >> 32); }

static uint32_t edge[4096];
static void build_edges(void)
{
    static const uint32_t fr[8] = {0, 1, 2, 0x400000, 0x7FFFFF, 0x7FFFFE, 0x3FFFFF, 0x555555};
    int k = 0, e, f, s;
    for (s = 0; s < 2; s++)
        for (e = 0; e < 256; e++)
            for (f = 0; f < 8; f++)
                edge[k++] = ((uint32_t)s << 31) | ((uint32_t)e << 23) | fr[f];
}

/* operand generators: uniform, edge, near exponent of the other operand */
static uint32_t gen1(void)
{
    uint32_t r = rnd32();
    switch (r & 7) {
    case 0: return edge[rnd32() & 4095];
    case 1: return (rnd32() & 0x807FFFFFu) | ((uint32_t)(r >> 8 & 3) == 0 ? 0 :
                   (r >> 8 & 3) == 1 ? 0x7F800000u : (r >> 8 & 3) == 2 ? 0x00800000u : 0x3F800000u);
    default: return rnd32();
    }
}
static uint32_t gen_near(uint32_t a, int mul)
{
    uint32_t r = rnd32();
    int ea = (int)((a >> 23) & 0xFF), eb;
    if (mul) eb = 127 + 127 - ea + (int)(r % 64) - 32; /* product near 2^0 rescaled */
    else eb = ea + (int)(r % 64) - 32;               /* sums: cancellation, rounding */
    if (mul && (r & 0x100)) eb = 254 + 127 - ea + (int)(r % 16) - 8; /* near overflow */
    if (mul && (r & 0x200)) eb = 1 + 127 - ea + (int)(r % 16) - 8;   /* near underflow */
    if (eb < 0) eb = 0;
    if (eb > 255) eb = 255;
    return (rnd32() & 0x807FFFFFu) | ((uint32_t)eb << 23);
}

static unsigned long long n_checked, n_bad;
static int report(const char *cls, uint32_t a, uint32_t b, uint32_t got, uint32_t want,
                  unsigned gc, unsigned wc)
{
    n_bad++;
    if (n_bad <= 10)
        fprintf(stderr, "MISMATCH %s a=%08X b=%08X: got %08X/%X want %08X/%X\n", cls, a, b,
                got, gc, want, wc);
    return 1;
}

typedef uint32_t (*bin_fn)(uint32_t, uint32_t, unsigned *);

static uint32_t new_madd(uint32_t acc, uint32_t a, uint32_t b, unsigned *c)
{
    unsigned pc;
    uint32_t pr = vu_f_mul(a, b, &pc), r = vu_f_add(acc, pr, c);
    *c |= pc & VUF_O;
    return r;
}
static uint32_t ref_madd(uint32_t acc, uint32_t a, uint32_t b, unsigned *c)
{
    unsigned pc;
    uint32_t pr = ref_f_mul(a, b, &pc), r = ref_f_add(acc, pr, c);
    *c |= pc & VUF_O;
    return r;
}
static uint32_t new_msub(uint32_t acc, uint32_t a, uint32_t b, unsigned *c)
{
    unsigned pc;
    uint32_t pr = vu_f_mul(a, b, &pc), r = vu_f_sub(acc, pr, c);
    *c |= pc & VUF_O;
    return r;
}
static uint32_t ref_msub(uint32_t acc, uint32_t a, uint32_t b, unsigned *c)
{
    unsigned pc;
    uint32_t pr = ref_f_mul(a, b, &pc), r = ref_f_sub(acc, pr, c);
    *c |= pc & VUF_O;
    return r;
}

static void check_bin(const char *cls, bin_fn nf, bin_fn rf, uint32_t a, uint32_t b)
{
    unsigned gc = 0xEE, wc = 0xEE;
    uint32_t g = nf(a, b, &gc), w = rf(a, b, &wc);
    n_checked++;
    if (g != w || gc != wc) report(cls, a, b, g, w, gc, wc);
}

static void run_bin(const char *cls, bin_fn nf, bin_fn rf, long long count, int mul)
{
    long long i;
    int x, y;
    if (count >= 0)
        for (x = 0; x < 4096; x++)
            for (y = 0; y < 4096; y++) check_bin(cls, nf, rf, edge[x], edge[y]);
    if (count < 0) count = -count;
    for (i = 0; i < count; i++) {
        uint32_t a = gen1(), b = (i & 1) ? gen_near(a, mul) : gen1();
        check_bin(cls, nf, rf, a, b);
    }
}

static void run_tri(const char *cls, uint32_t (*nf)(uint32_t, uint32_t, uint32_t, unsigned *),
                    uint32_t (*rf)(uint32_t, uint32_t, uint32_t, unsigned *), long long count)
{
    long long i;
    if (count < 0) count = -count;
    for (i = 0; i < count; i++) {
        uint32_t a = gen1(), b = (i & 1) ? gen_near(a, 1) : gen1(), acc;
        unsigned gc = 0xEE, wc = 0xEE, pc;
        uint32_t g, w;
        /* the accumulator near the product half the time (cancellation) */
        acc = (i & 2) ? (vu_f_mul(a, b, &pc) ^ ((rnd32() & 1) << 31)) ^ (rnd32() & 0x3F) : gen1();
        if (i & 4) acc = gen_near(vu_f_mul(a, b, &pc), 0);
        g = nf(acc, a, b, &gc);
        w = rf(acc, a, b, &wc);
        n_checked++;
        if (g != w || gc != wc) report(cls, acc, a ^ b, g, w, gc, wc);
    }
}

static int slice = -1; /* exhaustive runs: one 16th of the patterns (argv[4]) */

static void run_unary(const char *cls, int which, long long count)
{
    static const int fracs[4] = {0, 4, 12, 15};
    unsigned long long i, n = count ? (unsigned long long)(count < 0 ? -count : count) : 0x100000000ull;
    unsigned long long base = 0;
    if (!count && slice >= 0) n = 0x10000000ull, base = (unsigned long long)slice << 28;
    for (i = 0; i < n; i++) {
        uint32_t a = count ? gen1() : (uint32_t)(base + i);
        if (which == 0) {
            double g = vu_f_to_d(a), w = ref_f_to_d(a);
            n_checked++;
            if (memcmp(&g, &w, 8)) report(cls, a, 0, vuf_d_bits(g) >> 32, vuf_d_bits(w) >> 32, 0, 0);
        } else {
            int k;
            for (k = 0; k < 4; k++) {
                uint32_t g = which == 1 ? vu_ftoi(a, fracs[k]) : vu_itof(a, fracs[k]);
                uint32_t w = which == 1 ? ref_ftoi(a, fracs[k]) : ref_itof(a, fracs[k]);
                n_checked++;
                if (g != w) report(cls, a, (uint32_t)fracs[k], g, w, 0, 0);
            }
        }
    }
}

/* doubles: random patterns of every finite exponent, the VU-range binades
 * densely, subnormals, zeros; plus the boundary exponents exhaustively in
 * their top mantissa bits */
static void run_from_d(long long count)
{
    long long i;
    int e;
    if (count < 0) count = -count;
    for (i = 0; i < count; i++) {
        uint64_t r = rnd64(), b;
        unsigned gc = 0xEE, wc = 0xEE;
        uint32_t g, w;
        double d;
        switch (r & 3) {
        case 0: b = r; break;                                    /* any pattern */
        case 1: b = (r & 0x800FFFFFFFFFFFFFull) | ((uint64_t)(880 + (r >> 8) % 280) << 52); break;
        case 2: b = r & 0x800FFFFFFFFFFFFFull; break;             /* subnormal / zero */
        default: b = (r & 0x8000000000000000ull) | ((r >> 40) & 0x7) << 29 |
                     ((uint64_t)(894 + (r >> 4) % 6) << 52) | (r & 0x1FFFFFFFull); break;
        }
        if (((b >> 52) & 0x7FF) == 0x7FF) b &= ~(1ull << 62); /* finite only (callers never pass Inf/NaN) */
        memcpy(&d, &b, 8);
        g = vu_f_from_d(d, &gc);
        w = ref_f_from_d(d, &wc);
        n_checked++;
        if (g != w || gc != wc) report("from_d", (uint32_t)(b >> 32), (uint32_t)b, g, w, gc, wc);
    }
    for (e = 0; e < 0x7FF; e++) {
        uint32_t m;
        for (m = 0; m < 4096; m++) {
            uint64_t b = ((uint64_t)e << 52) | ((uint64_t)m << 40) | (m * 0x9E37ull & 0xFFFFFFFFFFull);
            int s;
            for (s = 0; s < 2; s++) {
                unsigned gc = 0xEE, wc = 0xEE;
                uint32_t g, w;
                double d;
                b ^= (uint64_t)s << 63;
                memcpy(&d, &b, 8);
                g = vu_f_from_d(d, &gc);
                w = ref_f_from_d(d, &wc);
                n_checked++;
                if (g != w || gc != wc) report("from_d", (uint32_t)(b >> 32), (uint32_t)b, g, w, gc, wc);
            }
        }
    }
}

static int cmp_new(uint32_t a, uint32_t b, unsigned *c) { *c = 0; return (uint32_t)vu_f_cmp(a, b); }
static int cmp_ref(uint32_t a, uint32_t b, unsigned *c) { *c = 0; return (uint32_t)ref_f_cmp(a, b); }
static uint32_t cmpn(uint32_t a, uint32_t b, unsigned *c) { return (uint32_t)cmp_new(a, b, c); }
static uint32_t cmpr(uint32_t a, uint32_t b, unsigned *c) { return (uint32_t)cmp_ref(a, b, c); }

static uint32_t clipn(uint32_t a, uint32_t b, unsigned *c)
{
    uint32_t v[4] = {a, b, a ^ b ^ 0x80000000u, 0};
    *c = 0;
    return vuf_clip(v, b ^ (a & 0x80000000u)) | vuf_clip(v, a) << 6 | vuf_clip(v, (a & 0xFF800000u) | (b & 0x7FFFFF)) << 12;
}
static uint32_t clipr(uint32_t a, uint32_t b, unsigned *c)
{
    uint32_t v[4] = {a, b, a ^ b ^ 0x80000000u, 0};
    *c = 0;
    return ref_clip(v, b ^ (a & 0x80000000u)) | ref_clip(v, a) << 6 | ref_clip(v, (a & 0xFF800000u) | (b & 0x7FFFFF)) << 12;
}

static int fdiv_op;
static uint32_t fdivn(uint32_t a, uint32_t b, unsigned *c)
{
    uint32_t fl, r = vu_fdiv(fdiv_op, a, b, &fl);
    *c = fl;
    return r;
}
static uint32_t fdivr(uint32_t a, uint32_t b, unsigned *c)
{
    uint32_t fl, r = ref_fdiv(fdiv_op, a, b, &fl);
    *c = fl;
    return r;
}

/* ---- vec: vu_vec_inl.h against vu_float_inl.h ---- */
static uint32_t mac_of(unsigned cond, int c)
{
    return (((cond & VUF_Z) ? 0x0008u : 0) | ((cond & VUF_S) ? 0x0080u : 0) |
            ((cond & VUF_U) ? 0x0800u : 0) | ((cond & VUF_O) ? 0x8000u : 0)) >> c;
}

static uint32_t gen_vec(uint32_t near)
{
    switch (rnd32() % 6) {
    case 0: return edge[rnd32() & 4095];
    case 1: return 0;
    case 2: return gen_near(near, (int)(rnd32() & 1));
    default: return gen1();
    }
}

static void run_vec(long long count)
{
    long long i;
    if (count < 0) count = -count;
    for (i = 0; i < count; i++) {
        uint32_t a[4], t[4], acc[4], g[4], w[4], gm = 0, wm = 0;
        unsigned dest = rnd32() & 15, lanes = vuv_lanes(dest), op = rnd32() % 9;
        int c, frac = (int)((const int[]){0, 4, 12, 15})[rnd32() & 3];
        vuv_d4 da, dt;
        __m128i r = _mm_setzero_si128();
        for (c = 0; c < 4; c++) a[c] = gen_vec(0x3F800000u);
        for (c = 0; c < 4; c++) t[c] = (rnd32() & 3) ? gen_vec(a[c]) : a[(c + 1) & 3];
        for (c = 0; c < 4; c++) acc[c] = (rnd32() & 1) ? gen_vec(a[c]) : vu_f_mul(a[c], t[c], (unsigned *)&g[0]) ^ (rnd32() & 0x80000000u);
        da = vuv_to_d(vuv_load(a));
        dt = vuv_to_d(vuv_load(t));
        switch (op) {
        case 0: r = vuv_from_d_mac(vuv_add(da, dt), lanes, &gm); break;
        case 1: r = vuv_from_d_mac(vuv_sub(da, dt), lanes, &gm); break;
        case 2: r = vuv_from_d_mac(vuv_mul(da, dt), lanes, &gm); break;
        case 3: case 4: {
            __m128i pr = vuv_from_d_ovf(vuv_mul(da, dt), lanes, &gm);
            vuv_d4 dacc = vuv_to_d(vuv_load(acc));
            r = vuv_from_d_mac(op == 3 ? vuv_add(dacc, vuv_to_d(pr)) : vuv_sub(dacc, vuv_to_d(pr)), lanes, &gm);
            break;
        }
        case 5: {
            int is_max = (int)(rnd32() & 1);
            r = vuv_minmax(vuv_load(a), vuv_load(t), is_max);
            op = is_max ? 50 : 51;
            break;
        }
        case 6: r = vuv_ftoi(vuv_load(a), frac); break;
        case 7: r = vuv_itof(vuv_load(a), frac, lanes); break;
        default: { /* to_d: both halves of every lane */
            double ga[4], wa[4];
            _mm_storeu_pd(ga, da.lo);
            _mm_storeu_pd(ga + 2, da.hi);
            for (c = 0; c < 4; c++) {
                wa[c] = vuf_to_d(a[c]);
                n_checked++;
                if (memcmp(&ga[c], &wa[c], 8)) report("vec.to_d", a[c], 0, (uint32_t)(vuf_d_bits(ga[c]) >> 32), (uint32_t)(vuf_d_bits(wa[c]) >> 32), 0, 0);
            }
            continue;
        }
        }
        vuv_store(g, r);
        for (c = 0; c < 4; c++) {
            unsigned cond = 0, pc = 0;
            if (op >= 50) { /* every lane: MAX (50) / MINI (51) */
                uint32_t want = op == 50 ? (vuf_cmp(a[c], t[c]) >= 0 ? a[c] : t[c])
                                         : (vuf_cmp(a[c], t[c]) <= 0 ? a[c] : t[c]);
                n_checked++;
                if (g[c] != want) report("vec.minmax", a[c], t[c], g[c], want, op, c);
                continue;
            }
            if (!(lanes & (1u << c))) continue;
            switch (op) {
            case 0: w[c] = vuf_add(a[c], t[c], &cond); break;
            case 1: w[c] = vuf_sub(a[c], t[c], &cond); break;
            case 2: w[c] = vuf_mul(a[c], t[c], &cond); break;
            case 3: w[c] = vuf_add(acc[c], vuf_mul(a[c], t[c], &pc), &cond); cond |= pc & VUF_O; break;
            case 4: w[c] = vuf_sub(acc[c], vuf_mul(a[c], t[c], &pc), &cond); cond |= pc & VUF_O; break;
            case 6: w[c] = vuf_ftoi(a[c], frac); break;
            default: w[c] = vuf_itof(a[c], frac); break;
            }
            if (op <= 4) wm |= mac_of(cond, c);
            n_checked++;
            if (g[c] != w[c]) report("vec", a[c], t[c], g[c], w[c], op, c);
        }
        if (op <= 4 && gm != wm) {
            n_checked++;
            report("vec.mac", a[0], t[0], gm, wm, op, dest);
        }
    }
}

static void run_efu(long long count)
{
    static const int ops[] = {VU_L_ESADD, VU_L_ERSADD, VU_L_ELENG, VU_L_ERLENG, VU_L_EATANxy,
                              VU_L_EATANxz, VU_L_ESUM, VU_L_ESQRT, VU_L_ERSQRT, VU_L_ERCPR,
                              VU_L_ESIN, VU_L_EATAN, VU_L_EEXP};
    long long i;
    if (count < 0) count = -count;
    for (i = 0; i < count; i++) {
        int op = ops[rnd32() % 13], fsf = (int)(rnd32() & 3);
        uint32_t s[4], g, w;
        int k;
        for (k = 0; k < 4; k++) s[k] = (i & 1) ? gen1() : gen_near(0x3F800000u, 0);
        g = vu_efu(op, s, fsf);
        w = ref_efu(op, s, fsf);
        n_checked++;
        if (g != w) report("efu", s[0], (uint32_t)op, g, w, 0, 0);
    }
}

static int run_class(const char *c, long long n)
{
    unsigned long long bad0 = n_bad, chk0 = n_checked;
    if (!strcmp(c, "to_d")) run_unary(c, 0, n);
    else if (!strcmp(c, "ftoi")) run_unary(c, 1, n);
    else if (!strcmp(c, "itof")) run_unary(c, 2, n);
    else if (!strcmp(c, "from_d")) run_from_d(n);
    else if (!strcmp(c, "add")) run_bin(c, vu_f_add, ref_f_add, n, 0);
    else if (!strcmp(c, "sub")) run_bin(c, vu_f_sub, ref_f_sub, n, 0);
    else if (!strcmp(c, "mul")) run_bin(c, vu_f_mul, ref_f_mul, n, 1);
    else if (!strcmp(c, "madd")) run_tri(c, new_madd, ref_madd, n);
    else if (!strcmp(c, "msub")) run_tri(c, new_msub, ref_msub, n);
    else if (!strcmp(c, "cmp")) run_bin(c, cmpn, cmpr, n, 0);
    else if (!strcmp(c, "clip")) run_bin(c, clipn, clipr, n, 0);
    else if (!strcmp(c, "div")) fdiv_op = VU_L_DIV, run_bin(c, fdivn, fdivr, n, 1);
    else if (!strcmp(c, "sqrt")) fdiv_op = VU_L_SQRT, run_bin(c, fdivn, fdivr, n, 1);
    else if (!strcmp(c, "rsqrt")) fdiv_op = VU_L_RSQRT, run_bin(c, fdivn, fdivr, n, 1);
    else if (!strcmp(c, "efu")) run_efu(n);
    else if (!strcmp(c, "vec")) run_vec(n);
    else if (!strcmp(c, "control")) run_bin(c, vu_f_add, ref_f_mul, -100000, 0);
    else {
        fprintf(stderr, "unknown class %s\n", c);
        return 2;
    }
    printf("%-7s checked %llu, mismatches %llu\n", c, n_checked - chk0, n_bad - bad0);
    fflush(stdout);
    return n_bad != bad0;
}

int main(int argc, char **argv)
{
    static const char *all[] = {"to_d", "from_d", "add", "sub", "mul", "madd", "msub", "ftoi",
                                "itof", "cmp", "clip", "div", "sqrt", "rsqrt", "efu", "vec"};
    const char *cls = argc > 1 ? argv[1] : "all";
    long long n = argc > 2 ? strtoll(argv[2], NULL, 0) : 1000000;
    int rc = 0;
    size_t k;
    if (argc > 4) slice = atoi(argv[4]) & 15;
    if (argc > 3) rng_s ^= strtoull(argv[3], NULL, 0) * 0xD1B54A32D192ED03ull;
    build_edges();
    if (!strcmp(cls, "all")) {
        for (k = 0; k < sizeof all / sizeof all[0]; k++) {
            /* "all" with the default count: the unary classes random too */
            rc |= run_class(all[k], n ? n : 1000000);
            if (rc == 2) return 2;
        }
    } else {
        rc = run_class(cls, n);
    }
    printf("total checked %llu, mismatches %llu\n", n_checked, n_bad);
    return rc ? 1 : 0;
}
