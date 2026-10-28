/* SPDX-License-Identifier: CC0-1.0 */
/* VU1 block translator (docs/VU.md "Block translator").
 *
 * A block is a run of resident microcode pairs from an entry pc up to and
 * including the delay slot of the first branch or E bit (or a length cap).
 * It is decoded once (and pooled by content, so a re-uploaded program reuses
 * its blocks), then compiled into a list of pre-decoded operations for each
 * "timing variant": the pipeline state a block can be entered with that can
 * change its issue cycles.  Within a variant every issue cycle is a constant,
 * so stalls, the flag-event queue, Q/P landing and the cycle counter are
 * settled at compile time and only the values are computed at run time.
 *
 * The interpreter (vu.c) is the specification.  Every state a program can
 * observe ends up identical: VF/VI/ACC/Q/P/I/R, MAC/status/clip, memory, the
 * PATH1 packets, TPC, the cycle and stall counts, and the pipeline state the
 * next block or the interpreter continues from (pending flag events, Q/P in
 * flight, VF ready times that are still in the future, the VI history of the
 * integer-branch quirk).  Whenever a static assumption cannot be made the
 * block's pairs are interpreted instead (see blk_build for the list).
 * RG_VU_BLOCKS_CHECK=1 runs every block both ways and compares. */
#if defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS /* getenv */
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__)) && (defined(_WIN32) || defined(__linux__))
#define BLK_JIT 1
#endif
#ifdef BLK_JIT
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#else
#include <sys/mman.h>
#endif
#endif

#include "vu.h"
#include "vu_decode.h"
#include "vu_float_inl.h"
#include "vu_internal.h"
#include "vu_vec_inl.h"

enum { BLK_MAXP = 192, BLK_MAXVAR = 16, BLK_HASH = 4096, BLK_POOL_MAX = 16384 };

/* ------------------------------------------------------------ types */

typedef struct bctx {
    uint64_t c0;                 /* cycle at block entry */
    uint32_t csr0, csr_fast;     /* MXCSR outside the block / inside it (FMAC fast path) */
    uint32_t mac_or;             /* OR of the MAC values committed inside the block */
    int taken;
    uint32_t target;
    const uint8_t *ev_kind;      /* variant's event kinds (1 MAC, 2 clip) */
    uint16_t vold[4];            /* VI values before the writes of the last 4 pairs */
    uint32_t slot[BLK_MAXP];     /* flag event values, by event index */
} bctx;

/* handlers take their three arguments in registers on i686 */
#if defined(__i386__) && (defined(__GNUC__) || defined(__clang__))
#define BOPCC __attribute__((regparm(3)))
#else
#define BOPCC
#endif

typedef struct bop bop;
typedef void (BOPCC *bop_fn)(vu_state *, bctx *, const bop *);
struct bop {
    bop_fn fn;
    uint16_t dst;                /* byte offset of the destination vector in vu_state */
    uint8_t a, b, c, d, e, f;
    int32_t imm;
};

struct vblk;
struct bvar;

/* a transition seen from a variant: when the next pc is pc and the map still
 * holds b, the next variant is v (its VF key part follows statically from
 * this variant's tail; Q/P parts are rechecked) */
typedef struct bsucc {
    uint32_t pc;
    uint32_t cfg;                /* int_branch_quirk | break_on_dt << 1 when recorded */
    struct vblk *b;
    struct bvar *v;
} bsucc;

typedef void (*bjit_fn)(vu_state *, bctx *);   /* cdecl: the variant's ops as code */

typedef struct bvar {
    uint32_t key;
    bjit_fn code;                /* the ops as direct calls (BLK_JIT), or NULL: the op loop */
    bsucc succ[2];               /* last two successors (pc ~0 = none) */
    uint32_t succ_next;          /* slot the next new successor replaces */
    uint32_t cycles;             /* last issue + 1, relative to entry */
    uint32_t last_issue;
    uint32_t nops;
    uint32_t nev, n_commit;      /* events; [0, n_commit) land inside the block */
    uint32_t end_a;              /* events [end_a, n_commit) applied at the end */
    int32_t end_mac;             /* last MAC event in that range, or -1 */
    uint32_t ntail;
    uint32_t tail_mask[4];       /* tail_c as a set; all ones when cycles < 3 */
    bop *ops;
    uint8_t *ev_kind;
    uint32_t *ev_t;              /* relative visibility cycle of each event */
    uint8_t *tail_c;             /* VF components still in flight at the end */
    uint32_t *tail_t;
} bvar;

typedef struct vblk {
    struct vblk *hnext;
    uint32_t start, n, hash;
    uint32_t *words;             /* 2n raw words (lower, upper) */
    dc_entry *pe;
    uint8_t ok;                  /* 0: always interpreted */
    uint8_t ebit, has_branch, quirk_site, has_dt;
    uint8_t cond0;               /* pair 0 is a conditional branch */
    int8_t cond0_r0, cond0_r1;   /* VI it reads */
    int8_t last_vi_write;
    uint8_t kq, kp;              /* first pair that waits for Q / P (255 none) */
    uint8_t nli[3];
    uint8_t li[3][32];           /* live-in VF components read by pairs 0..2 */
    uint32_t li_mask[4];         /* the same as a 128-bit set */
    uint8_t nlog;                /* min(n, 4): pairs in the VI history log */
    int8_t log_reg[4];           /* VI each of them writes (-1 none), oldest first */
    uint32_t nvar;
    bvar *var[BLK_MAXVAR];
} vblk;

typedef struct vblk_cache {
    const vu_state *owner;
    /* tail of the last translated block: the VF components whose ready
     * time may still be in the future, valid while stats.pairs and cycle
     * are what they were when it ended */
    uint32_t tail[4];
    uint64_t stamp_pairs, stamp_cycle;
    vblk *map[2048];             /* by entry pair index */
    vblk *htab[BLK_HASH];        /* pool by content */
    uint32_t nblocks;
    uint32_t pool_max;           /* flush the pool beyond this many blocks */
    uint32_t flushes;            /* pool flushes so far (frees every block and variant) */
    /* call-threaded code of the variants (BLK_JIT, docs/PERF-3D.md): one
     * executable arena, bump-allocated, reset with the pool */
    uint8_t *jit;
    uint32_t jit_cap, jit_used;
    int jit_full;                /* a variant found no room: flush at the next block build */
    int jit_off;                 /* $RG_VU_JIT=0, or no executable memory */
} vblk_cache;

/* ------------------------------------------------------------ config */

static int env_flag(const char *name, int dflt)
{
    const char *v = getenv(name);
    if (!v || !*v) return dflt;
    return !(v[0] == '0' && v[1] == 0);
}

int vu__blocks_default(void) { return env_flag("RG_VU_BLOCKS", 1); }
int vu__blocks_check_default(void) { return env_flag("RG_VU_BLOCKS_CHECK", 0); }

/* ------------------------------------------------------------ flag helpers */

static uint32_t mac_agg(uint32_t mac)
{
    uint32_t agg = 0;
    if (mac & 0x000F) agg |= VU_ST_Z;
    if (mac & 0x00F0) agg |= VU_ST_S;
    if (mac & 0x0F00) agg |= VU_ST_U;
    if (mac & 0xF000) agg |= VU_ST_O;
    return agg;
}

/* the interpreter's commit_events, flag part only: events queued before the
 * block (they all land before any event of the block) */
static void commit_entry_flags(vu_state *vu, uint64_t now)
{
    while (vu->fq_n && vu->fq[vu->fq_head].t <= now) {
        vu_flag_event *ev = &vu->fq[vu->fq_head];
        if (ev->kind == 1) {
            uint32_t agg = mac_agg(ev->value);
            vu->mac = ev->value;
            vu->status = (vu->status & ~0xFu) | agg | (agg << 6);
        } else {
            vu->clip = ((vu->clip << 6) | ev->value) & 0xFFFFFFu;
        }
        vu->fq_head = (vu->fq_head + 1) & 15;
        vu->fq_n--;
    }
}

static void commit_q(vu_state *vu)
{
    vu->q = vu->q_next;
    vu->status = (vu->status & ~0x30u) | vu->q_next_flags | (vu->q_next_flags << 6);
    vu->q_busy = 0;
}

/* apply the block's own events [a, b): MAC sets mac and the low status
 * bits (the sticky bits are folded in at the end from mac_or), clip shifts */
static void apply_events(vu_state *vu, const bctx *x, uint32_t a, uint32_t b)
{
    uint32_t k;
    int last_mac = -1;
    for (k = a; k < b; k++) {
        if (x->ev_kind[k] == 1) last_mac = (int)k;
        else vu->clip = ((vu->clip << 6) | x->slot[k]) & 0xFFFFFFu;
    }
    if (last_mac >= 0) {
        vu->mac = x->slot[last_mac];
        vu->status = (vu->status & ~0xFu) | mac_agg(vu->mac);
    }
}

/* ------------------------------------------------------------ op handlers */

#define DSTP(vu, o) ((uint32_t *)((char *)(vu) + (o)->dst))
#define ON(d, c) ((d) & (8u >> (c)))

#if defined(__GNUC__) || defined(__clang__)
#define BLK_INLINE static inline __attribute__((always_inline))
#else
#define BLK_INLINE static __inline
#endif

BLK_INLINE void store4(vu_state *vu, const bop *o, const uint32_t r[4], unsigned d)
{
    uint32_t *p = DSTP(vu, o);
    if (d == 0xF) { p[0] = r[0]; p[1] = r[1]; p[2] = r[2]; p[3] = r[3]; return; }
    if (ON(d, 0)) p[0] = r[0];
    if (ON(d, 1)) p[1] = r[1];
    if (ON(d, 2)) p[2] = r[2];
    if (ON(d, 3)) p[3] = r[3];
}

BLK_INLINE void fin_mac(bctx *x, const bop *o, uint32_t mac)
{
    x->slot[o->e] = mac;
    if (o->f) x->mac_or |= mac;
}

/* 128-bit store of r into the destination, dest lanes only */
static const uint32_t lane_mask_tab[16][4] = {
#define LM(d) {((d) & 8) ? ~0u : 0, ((d) & 4) ? ~0u : 0, ((d) & 2) ? ~0u : 0, ((d) & 1) ? ~0u : 0}
    LM(0), LM(1), LM(2), LM(3), LM(4), LM(5), LM(6), LM(7),
    LM(8), LM(9), LM(10), LM(11), LM(12), LM(13), LM(14), LM(15)
#undef LM
};

BLK_INLINE void vstore(vu_state *vu, const bop *o, __m128i r, unsigned d)
{
    uint32_t *p = DSTP(vu, o);
    if (d != 0xF) {
        __m128i m = vuv_load(lane_mask_tab[d]);
        r = _mm_or_si128(_mm_and_si128(m, r), _mm_andnot_si128(m, vuv_load(p)));
    }
    vuv_store(p, r);
}

/* ---- FMAC fast path (docs/PERF-3D.md "VU1 single-precision fast path") ----
 * A variant runs with MXCSR = round toward zero, denormals-are-zero, flush-
 * to-zero off (bctx.csr_fast; run_variant switches).  For lanes whose
 * operands make the VU result an ordinary float, one SSE single operation
 * gives exactly the interpreter's bits:
 *   - MUL: the double product of two floats is exact and vuf_from_d keeps its
 *     top 23 fraction bits (truncation); mulps under round-toward-zero is the
 *     same truncation of the exact product.  Taken when no dest lane has an
 *     operand exponent of 255 and every product of nonzero operands has
 *     ea + eb in [128, 380] (result exponent 1..254: no overflow, no
 *     underflow; exponent-0 operands are zeros to both, DAZ).
 *   - ADD/SUB: when the exponents differ by at most 28 (or one is zero) the
 *     double sum is exact (24 + 28 + 1 bits), so its truncation is addps
 *     under round-toward-zero; max exponent <= 253 keeps the sum below
 *     exponent 255, and a denormal result (cancellation near exponent 1) goes
 *     to the double path.  An exact zero is +0 in both (RN and RZ agree).
 *   - MADD/MSUB: the product step as MUL (then no overflow bit), the sum step
 *     as ADD.
 * MAC bits as vuv_from_d_mac's fast lanes: Z for +-0, S from the sign bit.
 * Anything else takes the double path below, under the caller's MXCSR. */
static int g_blk_fast = 1;   /* $RG_VU_FAST=0: always the double path (check) */
#define BLK_CSR_FAST(c) ((((c) & ~0xE040u) | 0x6000u | 0x0040u))
/* The compiler does not model MXCSR: the memory clobbers (and the register
 * barriers on the operands in the FMAC handlers) keep the double path's
 * loads and arithmetic between the two switches. */
#define BLK_RN(x) do { _mm_setcsr((x)->csr0); __asm__ volatile("" ::: "memory"); } while (0)
#define BLK_RZ(x) do { __asm__ volatile("" ::: "memory"); _mm_setcsr((x)->csr_fast); } while (0)

VUF_INLINE __m128i vf_exp(__m128i v) { return _mm_and_si128(_mm_srli_epi32(v, 23), _mm_set1_epi32(0xFF)); }

/* product a * t: nonzero if the fast path applies to every lane in `lanes` */
VUF_INLINE int fast_mul_ok(__m128i ea, __m128i et, unsigned lanes)
{
    __m128i z = _mm_or_si128(_mm_cmpeq_epi32(ea, _mm_setzero_si128()), _mm_cmpeq_epi32(et, _mm_setzero_si128()));
    __m128i sum = _mm_add_epi32(ea, et);
    __m128i bad = _mm_or_si128(_mm_cmpgt_epi32(_mm_set1_epi32(128), sum), _mm_cmpgt_epi32(sum, _mm_set1_epi32(380)));
    bad = _mm_andnot_si128(z, bad);
    bad = _mm_or_si128(bad, _mm_or_si128(_mm_cmpeq_epi32(ea, _mm_set1_epi32(255)), _mm_cmpeq_epi32(et, _mm_set1_epi32(255))));
    return ((unsigned)_mm_movemask_ps(_mm_castsi128_ps(bad)) & lanes) == 0;
}

/* sum of a and b (exponent fields ea, eb) */
VUF_INLINE int fast_add_ok(__m128i ea, __m128i eb, unsigned lanes)
{
    __m128i z = _mm_or_si128(_mm_cmpeq_epi32(ea, _mm_setzero_si128()), _mm_cmpeq_epi32(eb, _mm_setzero_si128()));
    __m128i d = _mm_sub_epi32(ea, eb);
    __m128i far_ = _mm_or_si128(_mm_cmpgt_epi32(d, _mm_set1_epi32(28)), _mm_cmpgt_epi32(_mm_set1_epi32(-28), d));
    __m128i bad = _mm_andnot_si128(z, far_);
    bad = _mm_or_si128(bad, _mm_or_si128(_mm_cmpgt_epi32(ea, _mm_set1_epi32(253)), _mm_cmpgt_epi32(eb, _mm_set1_epi32(253))));
    return ((unsigned)_mm_movemask_ps(_mm_castsi128_ps(bad)) & lanes) == 0;
}

/* a denormal (exponent 0, fraction nonzero) result in `lanes` */
VUF_INLINE int has_denormal(__m128i r, unsigned lanes)
{
    /* the checks must stay integer: as float compares (which the compiler
     * may substitute for "magnitude == 0") a denormal reads as zero under DAZ */
    __asm__("" : "+x"(r));
    __m128i mag = _mm_and_si128(r, _mm_set1_epi32(0x7FFFFFFF));
    __m128i den = _mm_andnot_si128(_mm_cmpeq_epi32(mag, _mm_setzero_si128()),
                                   _mm_cmpeq_epi32(_mm_and_si128(r, _mm_set1_epi32(0x7F800000)), _mm_setzero_si128()));
    return ((unsigned)_mm_movemask_ps(_mm_castsi128_ps(den)) & lanes) != 0;
}

/* the MAC bits of fast lanes */
VUF_INLINE uint32_t fast_mac(__m128i r, unsigned lanes)
{
    __asm__("" : "+x"(r));   /* integer checks (see has_denormal) */
    __m128i mag = _mm_and_si128(r, _mm_set1_epi32(0x7FFFFFFF));
    unsigned zero = (unsigned)_mm_movemask_ps(_mm_castsi128_ps(_mm_cmpeq_epi32(mag, _mm_setzero_si128()))) & lanes;
    unsigned sb = (unsigned)_mm_movemask_ps(_mm_castsi128_ps(r)) & lanes;
    return (uint32_t)vuv_rev4[zero] | ((uint32_t)vuv_rev4[sb] << 4);
}

#define TI_VF vuv_load(vu->vf[o->b].u)
#define TI_BC _mm_set1_epi32((int)vu->vf[o->b].u[o->c])
#define TI_Q _mm_set1_epi32((int)vu->q)
#define TI_I _mm_set1_epi32((int)vu->i)

/* FMAC: a = fs, b = ft, c = bc, d = dest, e = event slot, f = lands in block.
 * The interpreter's exec_upper on four lanes at once (vu_vec_inl.h: the
 * lanes outside the VU exponent range 1..255 are redone with the scalar
 * helper, so every lane has the scalar result and condition bits). */
#define T_VF vuv_to_d(vuv_load(vu->vf[o->b].u))
#define T_BC vuv_bcast(vuf_to_d(vu->vf[o->b].u[o->c]))
#define T_Q  vuv_bcast(vuf_to_d(vu->q))
#define T_I  vuv_bcast(vuf_to_d(vu->i))
#define VFMAC_FN(NAME, TINIT, OP, TI, FOK, FOP)                          \
static BOPCC void NAME(vu_state *vu, bctx *x, const bop *o)             \
{                                                                       \
    unsigned d = o->d, lanes = vuv_rev4[d];                             \
    uint32_t mac = 0;                                                   \
    __m128i ai = vuv_load(vu->vf[o->a].u), ti = TI;                     \
    if (g_blk_fast && FOK(vf_exp(ai), vf_exp(ti), lanes)) {                           \
        __m128i r = _mm_castps_si128(FOP(_mm_castsi128_ps(ai), _mm_castsi128_ps(ti))); \
        if (!has_denormal(r, lanes)) {                                  \
            vstore(vu, o, r, d);                                        \
            fin_mac(x, o, fast_mac(r, lanes));                          \
            return;                                                     \
        }                                                               \
    }                                                                   \
    BLK_RN(x);                                                          \
    __asm__ volatile("" : "+x"(ai), "+x"(ti));                          \
    {                                                                   \
        vuv_d4 a = vuv_to_d(ai), t = TINIT;                             \
        __m128i r = vuv_from_d_mac(OP(a, t), lanes, &mac);              \
        vstore(vu, o, r, d);                                            \
        fin_mac(x, o, mac);                                             \
    }                                                                   \
    BLK_RZ(x);                                                          \
}
/* MADD / MSUB: the product is chopped to a VU float first (its overflow
 * is reported), then added to / subtracted from ACC */
#define VFMACC_FN(NAME, TINIT, OP, TI, FOK, FOP)                         \
static BOPCC void NAME(vu_state *vu, bctx *x, const bop *o)             \
{                                                                       \
    unsigned d = o->d, lanes = vuv_rev4[d];                             \
    uint32_t mac = 0;                                                   \
    __m128i ai = vuv_load(vu->vf[o->a].u), ti = TI;                     \
    __m128i ci = vuv_load(vu->acc.u);                                   \
    (void)FOK;                                                          \
    if (g_blk_fast && fast_mul_ok(vf_exp(ai), vf_exp(ti), lanes)) {                   \
        __m128i pr = _mm_castps_si128(_mm_mul_ps(_mm_castsi128_ps(ai), _mm_castsi128_ps(ti))); \
        if (fast_add_ok(vf_exp(ci), vf_exp(pr), lanes)) {               \
            __m128i r = _mm_castps_si128(FOP(_mm_castsi128_ps(ci), _mm_castsi128_ps(pr))); \
            if (!has_denormal(r, lanes)) {                              \
                vstore(vu, o, r, d);                                    \
                fin_mac(x, o, fast_mac(r, lanes));                      \
                return;                                                 \
            }                                                           \
        }                                                               \
    }                                                                   \
    BLK_RN(x);                                                          \
    __asm__ volatile("" : "+x"(ai), "+x"(ti), "+x"(ci));                \
    {                                                                   \
        vuv_d4 a = vuv_to_d(ai), t = TINIT;                             \
        __m128i pr = vuv_from_d_ovf(vuv_mul(a, t), lanes, &mac);        \
        vuv_d4 acc = vuv_to_d(ci);                                      \
        __m128i r = vuv_from_d_mac(OP(acc, vuv_to_d(pr)), lanes, &mac); \
        vstore(vu, o, r, d);                                            \
        fin_mac(x, o, mac);                                             \
    }                                                                   \
    BLK_RZ(x);                                                          \
}
#define VFMAC_SET(K, MK, OP, FOK, FOP)                     \
    MK(h_##K##_vf, T_VF, OP, TI_VF, FOK, FOP)              \
    MK(h_##K##_bc, T_BC, OP, TI_BC, FOK, FOP)              \
    MK(h_##K##_q, T_Q, OP, TI_Q, FOK, FOP)                 \
    MK(h_##K##_i, T_I, OP, TI_I, FOK, FOP)
VFMAC_SET(ADD, VFMAC_FN, vuv_add, fast_add_ok, _mm_add_ps)
VFMAC_SET(SUB, VFMAC_FN, vuv_sub, fast_add_ok, _mm_sub_ps)
VFMAC_SET(MUL, VFMAC_FN, vuv_mul, fast_mul_ok, _mm_mul_ps)
VFMAC_SET(MADD, VFMACC_FN, vuv_add, fast_add_ok, _mm_add_ps)
VFMAC_SET(MSUB, VFMACC_FN, vuv_sub, fast_add_ok, _mm_sub_ps)

/* [kind][src] */
static const bop_fn fmac_fn[5][4] = {
#define FROW(K) {h_##K##_vf, h_##K##_bc, h_##K##_q, h_##K##_i},
    FROW(ADD) FROW(SUB) FROW(MUL) FROW(MADD) FROW(MSUB)
#undef FROW
};

/* OPMULA / OPMSUB (c = 1): lanes x, y, z of fs.yzx * ft.zxy, chopped, then
 * (OPMSUB) subtracted from ACC; the interpreter's exec_upper on four lanes */
static BOPCC __attribute__((noinline)) void h_opm_rn(vu_state *vu, bctx *x, const bop *o);
static BOPCC void h_opm(vu_state *vu, bctx *x, const bop *o)
{
    BLK_RN(x);
    h_opm_rn(vu, x, o);
    BLK_RZ(x);
}
static BOPCC __attribute__((noinline)) void h_opm_rn(vu_state *vu, bctx *x, const bop *o)
{
    unsigned d = o->d & 0xE, lanes = vuv_rev4[d];
    uint32_t mac = 0;
    __m128i fs = _mm_shuffle_epi32(vuv_load(vu->vf[o->a].u), _MM_SHUFFLE(3, 0, 2, 1));
    __m128i ft = _mm_shuffle_epi32(vuv_load(vu->vf[o->b].u), _MM_SHUFFLE(3, 1, 0, 2));
    vuv_d4 pd = vuv_mul(vuv_to_d(fs), vuv_to_d(ft));
    __m128i r;
    if (!o->c) {
        r = vuv_from_d_mac(pd, lanes, &mac);
    } else {
        __m128i pr = vuv_from_d_ovf(pd, lanes, &mac);
        r = vuv_from_d_mac(vuv_sub(vuv_to_d(vuv_load(vu->acc.u)), vuv_to_d(pr)), lanes, &mac);
    }
    vstore(vu, o, r, d);
    fin_mac(x, o, mac);
}

/* MAX / MINI: c = 1 for MAX; e = src; f = bc */
static BOPCC void h_minmax(vu_state *vu, bctx *x, const bop *o)
{
    __m128i a = vuv_load(vu->vf[o->a].u), t;
    (void)x;
    switch (o->e) {
    case VU_SRC_BC: t = _mm_set1_epi32((int)vu->vf[o->b].u[o->f]); break;
    case VU_SRC_Q: t = _mm_set1_epi32((int)vu->q); break;
    case VU_SRC_I: t = _mm_set1_epi32((int)vu->i); break;
    default: t = vuv_load(vu->vf[o->b].u); break;
    }
    vstore(vu, o, vuv_minmax(a, t, o->c), o->d);
}

static BOPCC void h_itof(vu_state *vu, bctx *x, const bop *o)
{
    (void)x;
    vstore(vu, o, vuv_itof(vuv_load(vu->vf[o->a].u), o->c, vuv_rev4[o->d]), o->d);
}

static BOPCC void h_ftoi(vu_state *vu, bctx *x, const bop *o)
{
    (void)x;
    vstore(vu, o, vuv_ftoi(vuv_load(vu->vf[o->a].u), o->c), o->d);
}

static BOPCC void h_abs(vu_state *vu, bctx *x, const bop *o)
{
    (void)x;
    vstore(vu, o, _mm_and_si128(vuv_load(vu->vf[o->a].u), _mm_set1_epi32(0x7FFFFFFF)), o->d);
}

static BOPCC void h_clip(vu_state *vu, bctx *x, const bop *o)
{
    x->slot[o->e] = vuf_clip(vu->vf[o->a].u, vu->vf[o->b].u[3]);
}

/* upper result parked in blk_tmp because the lower reads or writes what it
 * writes: land it now (dst = real destination, d = mask) */
static BOPCC void h_land(vu_state *vu, bctx *x, const bop *o)
{
    (void)x;
    store4(vu, o, vu->blk_tmp.u, o->d);
}

/* ---- pipeline sync points (imm = issue cycle relative to entry) ---- */

/* before a flag-reading or FCSET pair: everything visible at its issue */
static BOPCC void h_sync(vu_state *vu, bctx *x, const bop *o)
{
    if (vu->fq_n) commit_entry_flags(vu, x->c0 + (uint32_t)o->imm);
    apply_events(vu, x, o->a, o->b);
}

/* before a Q reader or a DIV/SQRT/RSQRT; a = 1: count an early Q read */
static BOPCC void h_qsync(vu_state *vu, bctx *x, const bop *o)
{
    if (vu->q_busy && vu->q_done <= x->c0 + (uint32_t)o->imm) commit_q(vu);
    if (o->a && vu->q_busy) vu->stats.q_early_reads++;
}

static BOPCC void h_psync(vu_state *vu, bctx *x, const bop *o)
{
    if (vu->p_busy && vu->p_done <= x->c0 + (uint32_t)o->imm) {
        vu->p = vu->p_next;
        vu->p_busy = 0;
    }
}

/* VI history for the integer-branch quirk: the value a VI had before one
 * of the block's last 4 pairs wrote it (a = log index, b = VI) */
static BOPCC void h_vilog(vu_state *vu, bctx *x, const bop *o)
{
    x->vold[o->a] = vu->vi[o->b];
}

/* ---- lower ---- a = ft/it, b = fs/is, c = fd/id, d = dest, e = fsf, f = ftf */

static void set_vi(vu_state *vu, int r, uint32_t v)
{
    if (r > 0 && r < 16) vu->vi[r] = (uint16_t)v;
}

static void wr_vf(vu_state *vu, unsigned reg, unsigned dest, const uint32_t v[4])
{
    int c;
    if (!reg) return;
    for (c = 0; c < 4; c++)
        if (ON(dest, c)) vu->vf[reg].u[c] = v[c];
}

#define VMEM(vu, qa) ((uint32_t *)((vu)->mem + ((qa) & 1023u) * 16))

static BOPCC void h_loi(vu_state *vu, bctx *x, const bop *o) { (void)x; vu->i = (uint32_t)o->imm; }

static BOPCC void h_lq(vu_state *vu, bctx *x, const bop *o)
{
    const uint32_t *v = VMEM(vu, (uint32_t)(vu->vi[o->b] + o->imm));
    (void)x;
    wr_vf(vu, o->a, o->d, v);
}

/* LQ.xyzw to a VF other than VF0 */
static BOPCC void h_lq_f(vu_state *vu, bctx *x, const bop *o)
{
    const uint32_t *v = VMEM(vu, (uint32_t)(vu->vi[o->b] + o->imm));
    uint32_t *d = vu->vf[o->a].u;
    (void)x;
    d[0] = v[0]; d[1] = v[1]; d[2] = v[2]; d[3] = v[3];
}

static BOPCC void h_sq_f(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t *p = VMEM(vu, (uint32_t)(vu->vi[o->a] + o->imm));
    const uint32_t *s = vu->vf[o->b].u;
    (void)x;
    p[0] = s[0]; p[1] = s[1]; p[2] = s[2]; p[3] = s[3];
}

static BOPCC void h_sq(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t *p = VMEM(vu, (uint32_t)(vu->vi[o->a] + o->imm));
    const uint32_t *s = vu->vf[o->b].u;
    int c;
    (void)x;
    for (c = 0; c < 4; c++)
        if (ON(o->d, c)) p[c] = s[c];
}

static BOPCC void h_lqi(vu_state *vu, bctx *x, const bop *o)
{
    (void)x;
    wr_vf(vu, o->a, o->d, VMEM(vu, vu->vi[o->b]));
    set_vi(vu, o->b, vu->vi[o->b] + 1u);
}

static BOPCC void h_lqd(vu_state *vu, bctx *x, const bop *o)
{
    (void)x;
    set_vi(vu, o->b, vu->vi[o->b] - 1u);
    wr_vf(vu, o->a, o->d, VMEM(vu, vu->vi[o->b]));
}

static BOPCC void h_sqi(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t *p = VMEM(vu, vu->vi[o->a]);
    const uint32_t *s = vu->vf[o->b].u;
    int c;
    (void)x;
    for (c = 0; c < 4; c++)
        if (ON(o->d, c)) p[c] = s[c];
    set_vi(vu, o->a, vu->vi[o->a] + 1u);
}

static BOPCC void h_sqd(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t *p;
    const uint32_t *s = vu->vf[o->b].u;
    int c;
    (void)x;
    set_vi(vu, o->a, vu->vi[o->a] - 1u);
    p = VMEM(vu, vu->vi[o->a]);
    for (c = 0; c < 4; c++)
        if (ON(o->d, c)) p[c] = s[c];
}

/* ILW / ILWR: imm = offset (0 for ILWR), e = first dest field (4 = none) */
static BOPCC void h_ilw(vu_state *vu, bctx *x, const bop *o)
{
    const uint32_t *p = VMEM(vu, (uint32_t)(vu->vi[o->b] + (uint32_t)o->imm));
    (void)x;
    set_vi(vu, o->a, o->e < 4 ? p[o->e] : 0);
}

static BOPCC void h_isw(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t *p = VMEM(vu, (uint32_t)(vu->vi[o->b] + (uint32_t)o->imm));
    uint32_t v = vu->vi[o->a];
    int c;
    (void)x;
    for (c = 0; c < 4; c++)
        if (ON(o->d, c)) p[c] = v;
}

static BOPCC void h_iaddiu(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->vi[o->b] + (uint32_t)o->imm); }
static BOPCC void h_isubiu(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->vi[o->b] - (uint32_t)o->imm); }
static BOPCC void h_iadd(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->c, (uint32_t)vu->vi[o->b] + vu->vi[o->a]); }
static BOPCC void h_isub(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->c, (uint32_t)vu->vi[o->b] - vu->vi[o->a]); }
static BOPCC void h_iand(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->c, (uint32_t)vu->vi[o->b] & vu->vi[o->a]); }
static BOPCC void h_ior(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->c, (uint32_t)vu->vi[o->b] | vu->vi[o->a]); }

static BOPCC void h_fceq(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, 1, vu->clip == (uint32_t)o->imm); }
static BOPCC void h_fcset(vu_state *vu, bctx *x, const bop *o) { (void)x; vu->clip = (uint32_t)o->imm & 0xFFFFFFu; }
static BOPCC void h_fcand(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, 1, (vu->clip & (uint32_t)o->imm) != 0); }
static BOPCC void h_fcor(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, 1, ((vu->clip | (uint32_t)o->imm) & 0xFFFFFFu) == 0xFFFFFFu); }
static BOPCC void h_fcget(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->clip & 0xFFF); }
static BOPCC void h_fmeq(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->mac == vu->vi[o->b]); }
static BOPCC void h_fmand(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->mac & vu->vi[o->b]); }
static BOPCC void h_fmor(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->mac | vu->vi[o->b]); }

/* branches: imm = static target (B/BAL/IBxx) or none; c = link value */
static BOPCC void h_b(vu_state *vu, bctx *x, const bop *o) { (void)vu; x->taken = 1; x->target = (uint32_t)o->imm; }
static BOPCC void h_bal(vu_state *vu, bctx *x, const bop *o)
{
    x->taken = 1;
    x->target = (uint32_t)o->imm;
    set_vi(vu, o->a, (uint32_t)o->dst);
}
static BOPCC void h_jr(vu_state *vu, bctx *x, const bop *o)
{
    x->taken = 1;
    x->target = ((uint32_t)vu->vi[o->b] * 8) & (vu->code_bytes - 1);
}
static BOPCC void h_jalr(vu_state *vu, bctx *x, const bop *o)
{
    x->taken = 1;
    x->target = ((uint32_t)vu->vi[o->b] * 8) & (vu->code_bytes - 1);
    set_vi(vu, o->a, (uint32_t)o->dst);
}
static BOPCC void h_ibeq(vu_state *vu, bctx *x, const bop *o)
{
    x->taken = vu->vi[o->b] == vu->vi[o->a];
    x->target = (uint32_t)o->imm;
}
static BOPCC void h_ibne(vu_state *vu, bctx *x, const bop *o)
{
    x->taken = vu->vi[o->b] != vu->vi[o->a];
    x->target = (uint32_t)o->imm;
}
static BOPCC void h_ibltz(vu_state *vu, bctx *x, const bop *o) { x->taken = (int16_t)vu->vi[o->b] < 0; x->target = (uint32_t)o->imm; }
static BOPCC void h_ibgtz(vu_state *vu, bctx *x, const bop *o) { x->taken = (int16_t)vu->vi[o->b] > 0; x->target = (uint32_t)o->imm; }
static BOPCC void h_iblez(vu_state *vu, bctx *x, const bop *o) { x->taken = (int16_t)vu->vi[o->b] <= 0; x->target = (uint32_t)o->imm; }
static BOPCC void h_ibgez(vu_state *vu, bctx *x, const bop *o) { x->taken = (int16_t)vu->vi[o->b] >= 0; x->target = (uint32_t)o->imm; }

static BOPCC void h_move(vu_state *vu, bctx *x, const bop *o) { (void)x; wr_vf(vu, o->a, o->d, vu->vf[o->b].u); }
static BOPCC void h_mr32(vu_state *vu, bctx *x, const bop *o)
{
    const uint32_t *s = vu->vf[o->b].u;
    uint32_t v[4];
    (void)x;
    v[0] = s[1]; v[1] = s[2]; v[2] = s[3]; v[3] = s[0];
    wr_vf(vu, o->a, o->d, v);
}

/* DIV / SQRT / RSQRT: c = op, imm = issue + latency */
static BOPCC void h_fdiv(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t fl;
    BLK_RN(x);
    vu->q_next = vu_fdiv(o->c, vu->vf[o->b].u[o->e], vu->vf[o->a].u[o->f], &fl);
    BLK_RZ(x);
    vu->q_next_flags = fl;
    vu->q_done = x->c0 + (uint32_t)o->imm;
    vu->q_busy = 1;
}

static BOPCC void h_mtir(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->vf[o->b].u[o->e] & 0xFFFF); }
static BOPCC void h_mfir(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t v[4];
    (void)x;
    v[0] = v[1] = v[2] = v[3] = (uint32_t)(int32_t)(int16_t)vu->vi[o->b];
    wr_vf(vu, o->a, o->d, v);
}
static BOPCC void h_rnext(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t r = vu->r, bit = ((r >> 4) ^ (r >> 22)) & 1, v[4];
    (void)x;
    vu->r = 0x3F800000u | (((r << 1) | bit) & 0x7FFFFFu);
    v[0] = v[1] = v[2] = v[3] = vu->r;
    wr_vf(vu, o->a, o->d, v);
}
static BOPCC void h_rget(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t v[4];
    (void)x;
    v[0] = v[1] = v[2] = v[3] = vu->r;
    wr_vf(vu, o->a, o->d, v);
}
static BOPCC void h_rinit(vu_state *vu, bctx *x, const bop *o) { (void)x; vu->r = 0x3F800000u | (vu->vf[o->b].u[o->e] & 0x7FFFFFu); }
static BOPCC void h_rxor(vu_state *vu, bctx *x, const bop *o) { (void)x; vu->r = 0x3F800000u | ((vu->r ^ vu->vf[o->b].u[o->e]) & 0x7FFFFFu); }
static BOPCC void h_mfp(vu_state *vu, bctx *x, const bop *o)
{
    uint32_t v[4];
    (void)x;
    v[0] = v[1] = v[2] = v[3] = vu->p;
    wr_vf(vu, o->a, o->d, v);
}
static BOPCC void h_xtop(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->top & 0x3FF); }
static BOPCC void h_xitop(vu_state *vu, bctx *x, const bop *o) { (void)x; set_vi(vu, o->a, vu->itop & 0x3FF); }
static BOPCC void h_xgkick(vu_state *vu, bctx *x, const bop *o) { BLK_RN(x); vu__xgkick(vu, vu->vi[o->b]); BLK_RZ(x); }
/* EFU: c = op, imm = issue + latency */
static BOPCC void h_efu(vu_state *vu, bctx *x, const bop *o)
{
    BLK_RN(x);
    vu->p_next = vu_efu(o->c, vu->vf[o->b].u, o->e);
    BLK_RZ(x);
    vu->p_done = x->c0 + (uint32_t)o->imm;
    vu->p_busy = 1;
}

/* ------------------------------------------------------------ cache */

static vblk_cache *cache_of(vu_state *vu)
{
    vblk_cache *c = (vblk_cache *)vu->blk;
    if (!c) {
        c = (vblk_cache *)calloc(1, sizeof *c);
        if (!c) return NULL;
        c->owner = vu;
        /* RG_VU_BLOCKS_POOL: a small pool exercises the flush path in tests */
        {
            const char *e = getenv("RG_VU_BLOCKS_POOL");
            c->pool_max = e && atoi(e) > 0 ? (uint32_t)atoi(e) : BLK_POOL_MAX;
        }
        c->jit_off = !env_flag("RG_VU_JIT", 1);
        g_blk_fast = env_flag("RG_VU_FAST", 1);
        vu->blk = c;
    }
    if (c->owner != vu) { /* a copied vu_state: the map is not ours */
        memset(c->map, 0, sizeof c->map);
        c->owner = vu;
    }
    return c;
}

static void var_free(bvar *v)
{
    free(v->ops);
    free(v->ev_kind);
    free(v->ev_t);
    free(v->tail_c);
    free(v->tail_t);
    free(v);
}

static void blk_free(vblk *b)
{
    uint32_t k;
    for (k = 0; k < b->nvar; k++) var_free(b->var[k]);
    free(b->words);
    free(b->pe);
    free(b);
}

/* ------------------------------------------------------------ jit
 * Call-threaded code (docs/PERF-3D.md): a variant's op list becomes straight
 * code that calls each handler directly with its operands as immediates
 * (eax = vu, edx = bctx, ecx = the op: the handlers' regparm(3)), instead of
 * the loop's indirect call through o->fn.  Same handlers, same order, so the
 * results are the op loop's by construction. */
#ifdef BLK_JIT
enum { JIT_ARENA = 8u << 20 };

static void jit_arena_free(vblk_cache *c)
{
    if (!c->jit) return;
#ifdef _WIN32
    VirtualFree(c->jit, 0, MEM_RELEASE);
#else
    munmap(c->jit, c->jit_cap);
#endif
    c->jit = NULL;
    c->jit_cap = c->jit_used = 0;
}

static bjit_fn jit_gen(vblk_cache *c, const bvar *v)
{
    uint32_t need = 16 + 24 + v->nops * 14u, k;
    uint8_t *p, *q;
    if (c->jit_off) return NULL;
    if (!c->jit) {
#ifdef _WIN32
        c->jit = (uint8_t *)VirtualAlloc(NULL, JIT_ARENA, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
#else
        void *m = mmap(NULL, JIT_ARENA, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        c->jit = m == MAP_FAILED ? NULL : (uint8_t *)m;
#endif
        if (!c->jit) { c->jit_off = 1; return NULL; }
        c->jit_cap = JIT_ARENA;
        c->jit_used = 0;
    }
    if (c->jit_used + need > c->jit_cap) { c->jit_full = 1; return NULL; }
    p = q = c->jit + c->jit_used;
    /* push ebp; push esi; push edi; push ebx; sub esp, 12 (16-byte aligned
     * calls); mov esi, [esp+32] (vu); mov edi, [esp+36] (bctx) */
    *q++ = 0x55; *q++ = 0x56; *q++ = 0x57; *q++ = 0x53;
    *q++ = 0x83; *q++ = 0xEC; *q++ = 0x0C;
    *q++ = 0x8B; *q++ = 0x74; *q++ = 0x24; *q++ = 0x20;
    *q++ = 0x8B; *q++ = 0x7C; *q++ = 0x24; *q++ = 0x24;
    for (k = 0; k < v->nops; k++) {
        const bop *o = &v->ops[k];
        uint32_t imm = (uint32_t)(uintptr_t)o;
        int32_t rel;
        *q++ = 0x89; *q++ = 0xF0;                       /* mov eax, esi */
        *q++ = 0x89; *q++ = 0xFA;                       /* mov edx, edi */
        *q++ = 0xB9; memcpy(q, &imm, 4); q += 4;        /* mov ecx, o */
        *q++ = 0xE8;                                    /* call fn */
        rel = (int32_t)((uintptr_t)o->fn - (uintptr_t)(q + 4));
        memcpy(q, &rel, 4); q += 4;
    }
    /* add esp, 12; pop ebx; pop edi; pop esi; pop ebp; ret */
    *q++ = 0x83; *q++ = 0xC4; *q++ = 0x0C;
    *q++ = 0x5B; *q++ = 0x5F; *q++ = 0x5E; *q++ = 0x5D; *q++ = 0xC3;
    c->jit_used += (uint32_t)(q - p);
    c->jit_used = (c->jit_used + 15u) & ~15u;
#ifdef _WIN32
    FlushInstructionCache(GetCurrentProcess(), p, (SIZE_T)(q - p));
#endif
    return (bjit_fn)(void *)p;
}
#endif

static void pool_flush(vblk_cache *c)
{
    uint32_t h;
#ifdef BLK_JIT
    c->jit_used = 0;     /* every variant (and its code) goes */
    c->jit_full = 0;
#endif
    memset(c->map, 0, sizeof c->map);
    for (h = 0; h < BLK_HASH; h++) {
        vblk *b = c->htab[h];
        while (b) {
            vblk *nx = b->hnext;
            blk_free(b);
            b = nx;
        }
        c->htab[h] = NULL;
    }
    c->nblocks = 0;
    c->flushes++;
}

void vu_release(vu_state *vu)
{
    vblk_cache *c = (vblk_cache *)vu->blk;
    if (!c) return;
    pool_flush(c);
#ifdef BLK_JIT
    jit_arena_free(c);
#endif
    free(c);
    vu->blk = NULL;
}

void vu__block_invalidate(vu_state *vu, uint32_t first, uint32_t n)
{
    vblk_cache *c = (vblk_cache *)vu->blk;
    uint32_t np = vu->code_bytes >> 3, k;
    if (!c) return;
    if (n >= np) { memset(c->map, 0, sizeof c->map); return; }
    for (k = 0; k < np; k++) {
        vblk *b = c->map[k];
        uint32_t off;
        if (!b) continue;
        /* the block covers pairs k .. k + n_b - 1 (mod np); the change covers
         * first .. first + n - 1 (mod np): they meet if either start lies in
         * the other range */
        off = (first - k) & (np - 1);
        if (off < b->n || ((k - first) & (np - 1)) < n) c->map[k] = NULL;
    }
}

static uint32_t hash_words(const uint32_t *w, uint32_t n, uint32_t start)
{
    uint32_t h = 2166136261u ^ start, k;
    for (k = 0; k < n; k++) h = (h ^ w[k]) * 16777619u;
    return h;
}

static int is_flag_lower(int op)
{
    switch (op) {
    case VU_L_FCEQ: case VU_L_FCSET: case VU_L_FCAND: case VU_L_FCOR: case VU_L_FCGET:
    case VU_L_FMEQ: case VU_L_FMAND: case VU_L_FMOR:
        return 1;
    default:
        return 0;
    }
}

static int is_efu(int op)
{
    return op >= VU_L_ESADD && op <= VU_L_EEXP && op != VU_L_WAITP;
}

static int is_fmac_upper(int kind)
{
    switch (kind) {
    case VU_U_ADD: case VU_U_SUB: case VU_U_MADD: case VU_U_MSUB: case VU_U_MUL:
    case VU_U_OPMULA: case VU_U_OPMSUB:
        return 1;
    default:
        return 0;
    }
}

/* the VI the interpreter's integer-branch quirk would compare against */
static int cur_vi_write(const dc_entry *e)
{
    const vu_lower *l = &e->p.lo;
    if (e->is_branch || (l->op >= VU_L_FCEQ && l->op <= VU_L_FCGET)) return -1;
    return e->vi_w;
}

/* Decode the block at pc.  It is interpreted (ok = 0) when:
 *   - a branch or an E bit sits in a delay slot, or an E pair's delay slot
 *     branches (the interpreter's sequencing then needs pair by pair state);
 *   - it uses FSEQ/FSSET/FSAND/FSOR (the status flag is settled lazily);
 *   - a conditional branch inside it reads a VI the previous pair's integer
 *     op wrote (the integer-branch quirk; the retail code never does);
 * and at run time when D/T bits are set with break_on_dt, the quirk could
 * fire at its first pair, or the cycle budget would run out inside it. */
static vblk *blk_build(vu_state *vu, vblk_cache *c, uint32_t pc)
{
    uint32_t mask = vu->code_bytes - 1, n = 0, k, h, words[2 * BLK_MAXP];
    int ok = 1, ends = 0;
    vblk *b;

    for (;;) {
        dc_entry *e = vu__dc_get(vu, (pc + n * 8) & mask);
        n++;
        if (e->is_branch || (e->p.up.bits & VU_B_E)) {
            dc_entry *e2;
            if (n == BLK_MAXP) { n--; break; }  /* no room for the delay slot */
            e2 = vu__dc_get(vu, (pc + n * 8) & mask);
            n++;
            if (e2->is_branch || (e2->p.up.bits & VU_B_E)) ok = 0;
            ends = 1;
            break;
        }
        if (n == BLK_MAXP) break;
    }
    for (k = 0; k < n; k++) {
        memcpy(&words[2 * k], vu->code + ((pc + k * 8) & mask), 4);
        memcpy(&words[2 * k + 1], vu->code + ((pc + k * 8 + 4) & mask), 4);
    }
    h = hash_words(words, 2 * n, pc);
    for (b = c->htab[h & (BLK_HASH - 1)]; b; b = b->hnext)
        if (b->hash == h && b->start == pc && b->n == n && !memcmp(b->words, words, 8 * n)) return b;

    if (c->nblocks >= c->pool_max || c->jit_full) pool_flush(c);
    b = (vblk *)calloc(1, sizeof *b);
    if (!b) return NULL;
    b->words = (uint32_t *)malloc(8 * n);
    b->pe = (dc_entry *)malloc(sizeof(dc_entry) * n);
    if (!b->words || !b->pe) {
        free(b->words); free(b->pe); free(b);
        return NULL;
    }
    memcpy(b->words, words, 8 * n);
    for (k = 0; k < n; k++) b->pe[k] = *vu__dc_get(vu, (pc + k * 8) & mask);
    b->start = pc;
    b->n = n;
    b->hash = h;
    b->kq = b->kp = 255;
    b->cond0_r0 = b->cond0_r1 = -1;
    if (ends) {
        const dc_entry *e = &b->pe[n - 2];
        b->has_branch = e->is_branch;
        b->ebit = (e->p.up.bits & VU_B_E) != 0;
    }
    for (k = 0; k < n; k++) {
        const dc_entry *e = &b->pe[k];
        int op = e->p.lo.op;
        if (op == VU_L_FSEQ || op == VU_L_FSSET || op == VU_L_FSAND || op == VU_L_FSOR) ok = 0;
        if (e->p.up.bits & (VU_B_D | VU_B_T)) b->has_dt = 1;
        if (e->writes_q && b->kq == 255) b->kq = (uint8_t)k;
        if (e->writes_p && b->kp == 255) b->kp = (uint8_t)k;
        if (op >= VU_L_IBEQ && op <= VU_L_IBGEZ) {
            int two = op == VU_L_IBEQ || op == VU_L_IBNE;
            if (k == 0) {
                b->cond0 = 1;
                b->cond0_r0 = (int8_t)e->p.lo.fs;
                b->cond0_r1 = two ? (int8_t)e->p.lo.ft : -1;
            } else {
                int w = cur_vi_write(&b->pe[k - 1]);
                if (w > 0 && (w == e->p.lo.fs || (two && w == e->p.lo.ft))) b->quirk_site = 1;
            }
        }
    }
    b->last_vi_write = (int8_t)cur_vi_write(&b->pe[n - 1]);
    b->nlog = (uint8_t)(n < 4 ? n : 4);
    for (k = 0; k < b->nlog; k++) {
        int w = b->pe[n - b->nlog + k].vi_w;
        b->log_reg[k] = (int8_t)(w > 0 && w < 16 ? w : -1);
    }
    {   /* live-in VF components of pairs 0..2 */
        uint8_t written[128];
        uint32_t p, j;
        memset(written, 0, sizeof written);
        for (p = 0; p < 3 && p < n; p++) {
            const dc_entry *e = &b->pe[p];
            for (j = 0; j < e->n_rd; j++)
                if (!written[e->rd[j]]) {
                    b->li[p][b->nli[p]++] = e->rd[j];
                    b->li_mask[e->rd[j] >> 5] |= 1u << (e->rd[j] & 31);
                }
            for (j = 0; j < e->n_wr; j++) written[e->wr[j]] = 1;
        }
    }
    b->ok = (uint8_t)ok;
    b->hnext = c->htab[h & (BLK_HASH - 1)];
    c->htab[h & (BLK_HASH - 1)] = b;
    c->nblocks++;
    vu->stats.blk_builds++;
    return b;
}

/* ------------------------------------------------------------ compile */

/* the key: live-in VF stall of pairs 0..2 (2+2+2 bits), Q (4) and P (6)
 * still in flight when the first waiting pair could issue */
#define KEY_NONE 0xFFFFFFFFu

/* the Q and P parts of entry_key (see there) */
static uint32_t entry_key_qp(const vu_state *vu, const vblk *b)
{
    uint64_t c0 = vu->cycle;
    uint32_t key = 0;
    if (b->kq != 255 && vu->q_busy && vu->q_done > c0 + b->kq) {
        if (vu->q_done - c0 > 15) return KEY_NONE;
        key |= (uint32_t)(vu->q_done - c0) << 6;
    }
    if (b->kp != 255 && vu->p_busy && vu->p_done > c0 + b->kp) {
        if (vu->p_done - c0 > 63) return KEY_NONE;
        key |= (uint32_t)(vu->p_done - c0) << 10;
    }
    return key;
}

/* KEY_NONE when the state is outside what a key encodes (VF results more
 * than 3 cycles out, Q more than 15, P more than 63): the interpreter never
 * leaves such a state, but the block is then interpreted, not assumed */
static uint32_t entry_key(const vu_state *vu, const vblk *b, const vblk_cache *c)
{
    uint64_t c0 = vu->cycle;
    uint32_t key = 0, p, j;
    if (c->stamp_pairs != vu->stats.pairs || c->stamp_cycle != c0 ||
        ((c->tail[0] & b->li_mask[0]) | (c->tail[1] & b->li_mask[1]) |
         (c->tail[2] & b->li_mask[2]) | (c->tail[3] & b->li_mask[3]))) {
        for (p = 0; p < 3 && p < b->n; p++) {
            uint64_t m = c0 + p;
            for (j = 0; j < b->nli[p]; j++) {
                uint64_t r = (&vu->vf_ready[0][0])[b->li[p][j]];
                if (r > m) m = r;
            }
            if (m - c0 > 3) return KEY_NONE;
            key |= (uint32_t)(m - c0 - p) << (2 * p);
        }
    }
    if (b->kq != 255 && vu->q_busy && vu->q_done > c0 + b->kq) {
        if (vu->q_done - c0 > 15) return KEY_NONE;
        key |= (uint32_t)(vu->q_done - c0) << 6;
    }
    if (b->kp != 255 && vu->p_busy && vu->p_done > c0 + b->kp) {
        if (vu->p_done - c0 > 63) return KEY_NONE;
        key |= (uint32_t)(vu->p_done - c0) << 10;
    }
    return key;
}

static uint16_t vec_off(unsigned reg)
{
    return (uint16_t)(offsetof(vu_state, vf) + reg * sizeof(vu_vec));
}

typedef struct opbuf {
    bop *o;
    uint32_t n, cap;
    int fail;
} opbuf;

static bop *emit(opbuf *ob, bop_fn fn)
{
    bop *o;
    if (ob->n == ob->cap) {
        uint32_t nc = ob->cap ? ob->cap * 2 : 64;
        bop *no = (bop *)realloc(ob->o, nc * sizeof *no);
        if (!no) { ob->fail = 1; return NULL; }
        ob->o = no;
        ob->cap = nc;
    }
    o = &ob->o[ob->n++];
    memset(o, 0, sizeof *o);
    o->fn = fn;
    return o;
}

/* component bitmaps (128 bits) of a vu_use's VF reads / its write */
static void use_reads(const vu_use *u, uint8_t m[128])
{
    unsigned k, c;
    for (k = 0; k < u->n_vf_r; k++)
        for (c = 0; c < 4; c++)
            if (u->vf_r[k] && (u->vf_r_mask[k] & (8u >> c))) m[u->vf_r[k] * 4 + c] = 1;
}

static void use_write(unsigned reg, unsigned mask, uint8_t m[128])
{
    unsigned c;
    if (!reg) return;
    for (c = 0; c < 4; c++)
        if (mask & (8u >> c)) m[reg * 4 + c] = 1;
}

static int overlap(const uint8_t *a, const uint8_t *b)
{
    int k;
    for (k = 0; k < 128; k++)
        if (a[k] && b[k]) return 1;
    return 0;
}

/* emit the upper op; out = byte offset of its destination */
static void emit_upper(opbuf *ob, const vu_upper *u, uint16_t out, uint32_t slot, int lands)
{
    bop *o = NULL;
    switch (u->kind) {
    case VU_U_ADD: case VU_U_SUB: case VU_U_MUL: case VU_U_MADD: case VU_U_MSUB: {
        int k = u->kind == VU_U_ADD ? 0 : u->kind == VU_U_SUB ? 1 : u->kind == VU_U_MUL ? 2
              : u->kind == VU_U_MADD ? 3 : 4;
        o = emit(ob, fmac_fn[k][u->src & 3]);
        if (!o) return;
        o->c = u->bc;
        o->e = (uint8_t)slot;
        o->f = (uint8_t)lands;
        break;
    }
    case VU_U_OPMULA: case VU_U_OPMSUB:
        o = emit(ob, h_opm);
        if (!o) return;
        o->c = u->kind == VU_U_OPMSUB;
        o->e = (uint8_t)slot;
        o->f = (uint8_t)lands;
        break;
    case VU_U_MAX: case VU_U_MINI:
        o = emit(ob, h_minmax);
        if (!o) return;
        o->c = u->kind == VU_U_MAX;
        o->e = u->src;
        o->f = u->bc;
        break;
    case VU_U_ITOF: case VU_U_FTOI:
        o = emit(ob, u->kind == VU_U_ITOF ? h_itof : h_ftoi);
        if (!o) return;
        o->c = u->frac;
        break;
    case VU_U_ABS:
        o = emit(ob, h_abs);
        break;
    case VU_U_CLIP:
        o = emit(ob, h_clip);
        if (!o) return;
        o->e = (uint8_t)slot;
        break;
    default:
        return;
    }
    if (!o) return;
    o->dst = out;
    o->a = u->fs;
    o->b = u->ft;
    o->d = u->dest;
}

/* emit the lower op of the pair at pc (issue = relative issue cycle) */
static void emit_lower(opbuf *ob, vu_state *vu, const vu_lower *l, uint32_t pc, uint32_t issue)
{
    uint32_t cmask = vu->code_bytes - 1;
    bop_fn fn = NULL;
    bop *o;
    switch (l->op) {
    case VU_L_NOP: case VU_L_INVALID: case VU_L_WAITQ: case VU_L_WAITP: return;
    case VU_L_LOI: fn = h_loi; break;
    case VU_L_LQ:
        if (!l->ft) return;          /* to VF0: no effect */
        fn = l->dest == 0xF ? h_lq_f : h_lq;
        break;
    case VU_L_SQ: fn = l->dest == 0xF ? h_sq_f : h_sq; break;
    case VU_L_LQI: fn = h_lqi; break;
    case VU_L_LQD: fn = h_lqd; break;
    case VU_L_SQI: fn = h_sqi; break;
    case VU_L_SQD: fn = h_sqd; break;
    case VU_L_ILW: case VU_L_ILWR: fn = h_ilw; break;
    case VU_L_ISW: case VU_L_ISWR: fn = h_isw; break;
    case VU_L_IADDIU: case VU_L_IADDI: fn = h_iaddiu; break;
    case VU_L_ISUBIU: fn = h_isubiu; break;
    case VU_L_IADD: fn = h_iadd; break;
    case VU_L_ISUB: fn = h_isub; break;
    case VU_L_IAND: fn = h_iand; break;
    case VU_L_IOR: fn = h_ior; break;
    case VU_L_FCEQ: fn = h_fceq; break;
    case VU_L_FCSET: fn = h_fcset; break;
    case VU_L_FCAND: fn = h_fcand; break;
    case VU_L_FCOR: fn = h_fcor; break;
    case VU_L_FCGET: fn = h_fcget; break;
    case VU_L_FMEQ: fn = h_fmeq; break;
    case VU_L_FMAND: fn = h_fmand; break;
    case VU_L_FMOR: fn = h_fmor; break;
    case VU_L_B: fn = h_b; break;
    case VU_L_BAL: fn = h_bal; break;
    case VU_L_JR: fn = h_jr; break;
    case VU_L_JALR: fn = h_jalr; break;
    case VU_L_IBEQ: fn = h_ibeq; break;
    case VU_L_IBNE: fn = h_ibne; break;
    case VU_L_IBLTZ: fn = h_ibltz; break;
    case VU_L_IBGTZ: fn = h_ibgtz; break;
    case VU_L_IBLEZ: fn = h_iblez; break;
    case VU_L_IBGEZ: fn = h_ibgez; break;
    case VU_L_MOVE: fn = h_move; break;
    case VU_L_MR32: fn = h_mr32; break;
    case VU_L_DIV: case VU_L_SQRT: case VU_L_RSQRT: fn = h_fdiv; break;
    case VU_L_MTIR: fn = h_mtir; break;
    case VU_L_MFIR: fn = h_mfir; break;
    case VU_L_RNEXT: fn = h_rnext; break;
    case VU_L_RGET: fn = h_rget; break;
    case VU_L_RINIT: fn = h_rinit; break;
    case VU_L_RXOR: fn = h_rxor; break;
    case VU_L_MFP: fn = h_mfp; break;
    case VU_L_XTOP: fn = h_xtop; break;
    case VU_L_XITOP: fn = h_xitop; break;
    case VU_L_XGKICK: fn = h_xgkick; break;
    default:
        if (is_efu(l->op)) { fn = h_efu; break; }
        ob->fail = 1;   /* FS* never reach here (blk_build) */
        return;
    }
    o = emit(ob, fn);
    if (!o) return;
    o->a = l->ft;
    o->b = l->fs;
    o->c = l->fd;
    o->d = l->dest;
    o->e = l->fsf;
    o->f = l->ftf;
    o->imm = l->imm;
    switch (l->op) {
    case VU_L_ILW: case VU_L_ILWR: {
        int c;
        for (c = 0; c < 4; c++)
            if (l->dest & (8u >> c)) break;
        o->e = (uint8_t)c;
        o->imm = l->op == VU_L_ILW ? l->imm : 0;
        break;
    }
    case VU_L_ISW: case VU_L_ISWR:
        o->imm = l->op == VU_L_ISW ? l->imm : 0;
        break;
    case VU_L_B: case VU_L_BAL:
    case VU_L_IBEQ: case VU_L_IBNE: case VU_L_IBLTZ: case VU_L_IBGTZ: case VU_L_IBLEZ: case VU_L_IBGEZ:
        o->imm = (int32_t)((pc + 8 + (uint32_t)l->imm * 8) & cmask);
        o->dst = (uint16_t)((pc + 16) / 8);
        break;
    case VU_L_JR: case VU_L_JALR:
        o->dst = (uint16_t)((pc + 16) / 8);
        break;
    case VU_L_DIV: case VU_L_SQRT: case VU_L_RSQRT:
        o->c = (uint8_t)l->op;
        o->imm = (int32_t)(issue + (l->op == VU_L_RSQRT ? VU_LAT_RSQRT : VU_LAT_DIV));
        break;
    default:
        if (is_efu(l->op)) {
            o->c = (uint8_t)l->op;
            o->imm = (int32_t)(issue + vu__efu_latency(l->op));
        }
        break;
    }
}

static bvar *var_compile(vu_state *vu, vblk *b, uint32_t key)
{
    uint32_t n = b->n, p, j, nev = 0, applied = 0;
    uint32_t issue[BLK_MAXP], evt[BLK_MAXP];
    uint8_t evk[BLK_MAXP];
    int32_t ev_of[BLK_MAXP];
    int64_t ready[128];
    int64_t cyc = 0, qd = -1, pd = -1;
    uint32_t L;
    opbuf ob = {NULL, 0, 0, 0};
    bvar *v;

    /* ---- timing: the interpreter's step_pair issue rule on relative cycles ---- */
    for (j = 0; j < 128; j++) ready[j] = 0;
    if ((key >> 6) & 15) qd = (key >> 6) & 15;
    if ((key >> 10) & 63) pd = (key >> 10) & 63;
    for (p = 0; p < n; p++) {
        const dc_entry *e = &b->pe[p];
        int64_t iss = cyc;
        if (p < 3) {
            uint32_t r = (key >> (2 * p)) & 3;
            if (r && (int64_t)(p + r) > iss) iss = p + r;
        }
        for (j = 0; j < e->n_rd; j++)
            if (ready[e->rd[j]] > iss) iss = ready[e->rd[j]];
        if (e->writes_q && qd >= 0 && qd > iss) iss = qd;
        if (e->writes_p && pd >= 0 && pd > iss) iss = pd;
        if (qd >= 0 && qd <= iss) qd = -1;
        if (pd >= 0 && pd <= iss) pd = -1;
        if (e->p.lo.op == VU_L_DIV || e->p.lo.op == VU_L_SQRT) qd = iss + VU_LAT_DIV;
        else if (e->p.lo.op == VU_L_RSQRT) qd = iss + VU_LAT_RSQRT;
        else if (is_efu(e->p.lo.op)) pd = iss + vu__efu_latency(e->p.lo.op);
        for (j = 0; j < e->n_wr; j++) ready[e->wr[j]] = iss + VU_LAT_FMAC;
        issue[p] = (uint32_t)iss;
        ev_of[p] = -1;
        if (is_fmac_upper(e->p.up.kind) || e->p.up.kind == VU_U_CLIP) {
            ev_of[p] = (int32_t)nev;
            evk[nev] = e->p.up.kind == VU_U_CLIP ? 2 : 1;
            evt[nev] = (uint32_t)iss + VU_LAT_FMAC;
            nev++;
        }
        cyc = iss + 1;
    }
    L = issue[n - 1];

    v = (bvar *)calloc(1, sizeof *v);
    if (!v) return NULL;
    v->key = key;
    v->succ[0].pc = v->succ[1].pc = ~0u;
    v->cycles = L + 1;
    v->last_issue = L;
    v->nev = nev;
    for (v->n_commit = 0; v->n_commit < nev && evt[v->n_commit] <= L; v->n_commit++) {}

    /* ---- ops ---- */
    for (p = 0; p < n; p++) {
        const dc_entry *e = &b->pe[p];
        const vu_upper *u = &e->p.up;
        const vu_lower *l = &e->p.lo;
        uint32_t pc = (b->start + p * 8) & (vu->code_bytes - 1);
        uint8_t ur[128], uw[128], lr[128], lw[128];
        vu_use uu, lu;
        int up_writes, up_reads_i, a_conf, b_conf, c_conf, order; /* 0 up first, 1 low first, 2 temp */
        uint16_t out;
        uint32_t umask;
        bop *o;

        if (is_flag_lower(l->op)) {
            uint32_t to = applied;
            while (to < v->n_commit && evt[to] <= issue[p]) to++;
            o = emit(&ob, h_sync);
            if (o) { o->imm = (int32_t)issue[p]; o->a = (uint8_t)applied; o->b = (uint8_t)to; }
            applied = to;
        }
        if (u->src == VU_SRC_Q || l->op == VU_L_DIV || l->op == VU_L_SQRT || l->op == VU_L_RSQRT) {
            o = emit(&ob, h_qsync);
            if (o) { o->imm = (int32_t)issue[p]; o->a = u->src == VU_SRC_Q; }
        }
        if (l->op == VU_L_MFP || is_efu(l->op)) {
            o = emit(&ob, h_psync);
            if (o) o->imm = (int32_t)issue[p];
        }
        if (p + b->nlog >= n && b->log_reg[p + b->nlog - n] > 0) {
            o = emit(&ob, h_vilog);
            if (o) { o->a = (uint8_t)(p + b->nlog - n); o->b = (uint8_t)b->log_reg[p + b->nlog - n]; }
        }

        /* upper / lower order: both read the registers as they were before
         * the pair, the upper's results land last */
        vu_upper_use(u, &uu);
        vu_lower_use(l, &lu);
        memset(ur, 0, sizeof ur); memset(uw, 0, sizeof uw);
        memset(lr, 0, sizeof lr); memset(lw, 0, sizeof lw);
        use_reads(&uu, ur);
        use_reads(&lu, lr);
        use_write(lu.vf_w, lu.vf_w_mask, lw);
        up_writes = 0;
        umask = u->dest;
        out = (uint16_t)offsetof(vu_state, blk_junk);
        switch (u->kind) {
        case VU_U_ADD: case VU_U_SUB: case VU_U_MUL: case VU_U_MADD: case VU_U_MSUB:
            if (u->to_acc) out = (uint16_t)offsetof(vu_state, acc);
            else if (u->fd) { out = vec_off(u->fd); up_writes = 1; use_write(u->fd, umask, uw); }
            break;
        case VU_U_OPMULA:
            out = (uint16_t)offsetof(vu_state, acc);
            umask = u->dest & 0xE;
            break;
        case VU_U_OPMSUB:
            umask = u->dest & 0xE;
            if (u->fd) { out = vec_off(u->fd); up_writes = 1; use_write(u->fd, umask, uw); }
            break;
        case VU_U_MAX: case VU_U_MINI:
            if (u->fd) { out = vec_off(u->fd); up_writes = 1; use_write(u->fd, umask, uw); }
            break;
        case VU_U_ITOF: case VU_U_FTOI: case VU_U_ABS:
            if (u->ft) { out = vec_off(u->ft); up_writes = 1; use_write(u->ft, umask, uw); }
            break;
        default:
            break;
        }
        up_reads_i = u->src == VU_SRC_I &&
                     (u->kind == VU_U_ADD || u->kind == VU_U_SUB || u->kind == VU_U_MUL || u->kind == VU_U_MADD ||
                      u->kind == VU_U_MSUB || u->kind == VU_U_MAX || u->kind == VU_U_MINI);
        a_conf = up_writes && overlap(lr, uw);
        b_conf = overlap(lw, ur) || (l->op == VU_L_LOI && up_reads_i);
        c_conf = up_writes && overlap(lw, uw);
        if (!a_conf && !c_conf) order = 0;
        else if (a_conf && !b_conf && !c_conf) order = 1;
        else order = 2;

        if (order == 1) emit_lower(&ob, vu, l, pc, issue[p]);
        emit_upper(&ob, u, order == 2 ? (uint16_t)offsetof(vu_state, blk_tmp) : out,
                   ev_of[p] >= 0 ? (uint32_t)ev_of[p] : 0,
                   ev_of[p] >= 0 && (uint32_t)ev_of[p] < v->n_commit);
        if (order != 1) emit_lower(&ob, vu, l, pc, issue[p]);
        if (order == 2 && up_writes) {
            o = emit(&ob, h_land);
            if (o) { o->dst = out; o->d = (uint8_t)umask; }
        }
    }
    if (ob.fail) {
        free(ob.o);
        free(v);
        return NULL;
    }
    v->ops = ob.o;
    v->nops = ob.n;
    v->end_a = applied;
    v->end_mac = -1;
    for (j = applied; j < v->n_commit; j++)
        if (evk[j] == 1) v->end_mac = (int32_t)j;
    v->ev_kind = (uint8_t *)malloc(nev ? nev : 1);
    v->ev_t = (uint32_t *)malloc(sizeof(uint32_t) * (nev ? nev : 1));
    if (!v->ev_kind || !v->ev_t) { var_free(v); return NULL; }
    memcpy(v->ev_kind, evk, nev);
    memcpy(v->ev_t, evt, sizeof(uint32_t) * nev);
    /* VF components whose result is still in flight after the block */
    {
        uint32_t nt = 0;
        for (j = 0; j < 128; j++)
            if (ready[j] > (int64_t)v->cycles) nt++;
        v->tail_c = (uint8_t *)malloc(nt ? nt : 1);
        v->tail_t = (uint32_t *)malloc(sizeof(uint32_t) * (nt ? nt : 1));
        if (!v->tail_c || !v->tail_t) { var_free(v); return NULL; }
        for (j = 0; j < 128; j++)
            if (ready[j] > (int64_t)v->cycles) {
                v->tail_mask[j >> 5] |= 1u << (j & 31);
                v->tail_c[v->ntail] = (uint8_t)j;
                v->tail_t[v->ntail] = (uint32_t)ready[j];
                v->ntail++;
            }
    }
    if (v->cycles < 3) /* results from before the block may still be in flight */
        v->tail_mask[0] = v->tail_mask[1] = v->tail_mask[2] = v->tail_mask[3] = 0xFFFFFFFFu;
    vu->stats.blk_variants++;
    return v;
}

/* ------------------------------------------------------------ run */

static vu_stop run_variant(vu_state *vu, vblk_cache *c, const vblk *b, const bvar *v)
{
    bctx x;
    const bop *o = v->ops, *oe = v->ops + v->nops;
    uint64_t L;
    uint32_t k, next;

    x.c0 = vu->cycle;
    x.mac_or = 0;
    x.taken = 0;
    x.target = 0;
    x.ev_kind = v->ev_kind;
    x.csr0 = _mm_getcsr();
    x.csr_fast = BLK_CSR_FAST(x.csr0);
    _mm_setcsr(x.csr_fast);
    if (v->code) v->code(vu, &x);
    else
        for (; o < oe; o++) o->fn(vu, &x, o);
    _mm_setcsr(x.csr0);

    /* ---- settle the pipeline at the last issue ---- */
    L = x.c0 + v->last_issue;
    if (vu->fq_n) commit_entry_flags(vu, L);
    apply_events(vu, &x, v->end_a, v->n_commit);
    if (x.mac_or) vu->status |= mac_agg(x.mac_or) << 6;
    if (vu->q_busy && vu->q_done <= L) commit_q(vu);
    if (vu->p_busy && vu->p_done <= L) { vu->p = vu->p_next; vu->p_busy = 0; }
    for (k = v->n_commit; k < v->nev; k++) {
        vu_flag_event *ev;
        if (vu->fq_n == 16) vu__commit_events(vu, vu->fq[vu->fq_head].t); /* as push_event */
        ev = &vu->fq[(vu->fq_head + vu->fq_n) & 15];
        ev->t = x.c0 + v->ev_t[k];
        ev->kind = v->ev_kind[k];
        ev->value = x.slot[k];
        vu->fq_n++;
    }
    for (k = 0; k < v->ntail; k++) (&vu->vf_ready[0][0])[v->tail_c[k]] = x.c0 + v->tail_t[k];
    for (k = 0; k < b->nlog; k++) {   /* as step_pair: old value 0 when no VI is written */
        int8_t r = b->log_reg[k];
        vu->vih_pos = (vu->vih_pos - 1) & 3;
        vu->vih_reg[vu->vih_pos] = r;
        vu->vih_old[vu->vih_pos] = r > 0 ? x.vold[k] : 0;
    }
    vu->prev_vi_write = b->last_vi_write;
    vu->stats.stall_cycles += v->cycles - b->n;
    vu->cycle = x.c0 + v->cycles;
    vu->stats.cycles = vu->cycle;
    vu->stats.pairs += b->n;
    vu->stats.blk_pairs += b->n;
    vu->stats.blk_runs++;
    c->tail[0] = v->tail_mask[0];
    c->tail[1] = v->tail_mask[1];
    c->tail[2] = v->tail_mask[2];
    c->tail[3] = v->tail_mask[3];
    c->stamp_pairs = vu->stats.pairs;
    c->stamp_cycle = vu->cycle;

    /* ---- sequencing ---- */
    next = (b->start + b->n * 8) & (vu->code_bytes - 1);
    if (x.taken) next = x.target;
    vu->pc = next;
    if (b->ebit) {
        vu->running = 0;
        vu->tpc = next;
        vu->branch_pending = 0;
        vu_drain(vu);
        return VU_STOP_EBIT;
    }
    return VU_STOP_CYCLES;
}

/* ------------------------------------------------------------ lockstep check */

typedef struct vsnap {
    uint8_t regs[offsetof(vu_state, int_branch_quirk) - offsetof(vu_state, mem)];
    vu_stats stats;
} vsnap;

static void snap_save(const vu_state *vu, vsnap *s)
{
    memcpy(s->regs, (const char *)vu + offsetof(vu_state, mem), sizeof s->regs);
    s->stats = vu->stats;
}

static void snap_load(vu_state *vu, const vsnap *s)
{
    memcpy((char *)vu + offsetof(vu_state, mem), s->regs, sizeof s->regs);
    vu->stats = s->stats;
}

/* compare the state the interpreter left (a, restored into a scratch copy
 * of the fields) with the block's (vu); VF ready times are compared as
 * max(ready, cycle), the flag queue and the VI history logically */
static int snap_differs(const vu_state *a, const vu_state *b, char *why, size_t n)
{
    unsigned k, c;
#define D(cond, name) do { if (cond) { snprintf(why, n, "%s", name); return 1; } } while (0)
    D(memcmp(a->mem, b->mem, sizeof a->mem), "data memory");
    D(memcmp(a->vf, b->vf, sizeof a->vf), "VF");
    D(memcmp(&a->acc, &b->acc, sizeof a->acc), "ACC");
    D(memcmp(a->vi, b->vi, sizeof a->vi), "VI");
    D(a->q != b->q || a->p != b->p || a->i != b->i || a->r != b->r, "Q/P/I/R");
    D(a->mac != b->mac, "MAC");
    D(a->status != b->status, "status");
    D(a->clip != b->clip, "clip");
    D(a->pc != b->pc || a->tpc != b->tpc || a->running != b->running, "pc/tpc/running");
    D(a->cycle != b->cycle, "cycle");
    for (k = 0; k < 32; k++)
        for (c = 0; c < 4; c++) {
            uint64_t x = a->vf_ready[k][c] > a->cycle ? a->vf_ready[k][c] : a->cycle;
            uint64_t y = b->vf_ready[k][c] > b->cycle ? b->vf_ready[k][c] : b->cycle;
            D(x != y, "vf_ready");
        }
    D(a->fq_n != b->fq_n, "flag queue length");
    for (k = 0; k < a->fq_n; k++) {
        const vu_flag_event *x = &a->fq[(a->fq_head + k) & 15], *y = &b->fq[(b->fq_head + k) & 15];
        D(x->t != y->t || x->kind != y->kind || x->value != y->value, "flag queue entry");
    }
    D(a->q_busy != b->q_busy || a->q_next != b->q_next || a->q_next_flags != b->q_next_flags ||
      (a->q_busy && a->q_done != b->q_done), "Q pipeline");
    D(a->p_busy != b->p_busy || a->p_next != b->p_next || (a->p_busy && a->p_done != b->p_done), "P pipeline");
    D(a->branch_pending != b->branch_pending || a->ebit_pending != b->ebit_pending, "branch/ebit pending");
    for (k = 0; k < 4; k++) {
        int ra = a->vih_reg[(a->vih_pos + k) & 3], rb = b->vih_reg[(b->vih_pos + k) & 3];
        D(ra != rb || (ra >= 0 && a->vih_old[(a->vih_pos + k) & 3] != b->vih_old[(b->vih_pos + k) & 3]), "VI history");
    }
    D(a->prev_vi_write != b->prev_vi_write, "prev_vi_write");
    D(a->stats.pairs != b->stats.pairs || a->stats.cycles != b->stats.cycles ||
      a->stats.stall_cycles != b->stats.stall_cycles || a->stats.xgkicks != b->stats.xgkicks ||
      a->stats.xgkick_bytes != b->stats.xgkick_bytes || a->stats.int_branch_quirks != b->stats.int_branch_quirks ||
      a->stats.q_early_reads != b->stats.q_early_reads, "stats");
#undef D
    return 0;
}

static vu_stop checked_variant(vu_state *vu, vblk_cache *c, const vblk *b, const bvar *v)
{
    static vsnap s0, si;
    static vu_state ref;           /* fields compared by snap_differs */
    vu_gif_sink_fn sink = vu->gif_sink;
    vu_stop st_i = VU_STOP_CYCLES, st_b;
    uint32_t k;
    char why[64];

    snap_save(vu, &s0);
    vu->gif_sink = NULL;
    for (k = 0; k < b->n; k++) {
        st_i = vu__step(vu);
        if (st_i != VU_STOP_CYCLES) break;
    }
    snap_save(vu, &si);
    snap_load(vu, &s0);
    vu->gif_sink = sink;
    st_b = run_variant(vu, c, b, v);
    snap_load(&ref, &si);
    if (st_i != st_b || snap_differs(&ref, vu, why, sizeof why)) {
        fprintf(stderr, "vu_block: MISMATCH at block 0x%04X (%u pairs, key 0x%X): %s (stop %d vs %d)\n",
                b->start, b->n, v->key, st_i != st_b ? "stop reason" : why, (int)st_i, (int)st_b);
        abort();
    }
    return st_b;
}

/* ------------------------------------------------------------ dispatcher */

/* the block at pc, its checks, its key and variant (NULL: interpret b->n
 * pairs, or one pair when b is NULL too) */
static bvar *pick_variant(vu_state *vu, vblk_cache *c, uint32_t pc, vblk **bp)
{
    vblk *b = c->map[pc >> 3];
    bvar *v = NULL;
    uint32_t key, j;
    if (!b) {
        b = blk_build(vu, c, pc);
        c->map[pc >> 3] = b;
    }
    *bp = b;
    if (!b || !b->ok || (b->quirk_site && vu->int_branch_quirk) || (b->has_dt && vu->break_on_dt) ||
        (b->cond0 && vu->int_branch_quirk && vu->prev_vi_write > 0 &&
         (vu->prev_vi_write == b->cond0_r0 || vu->prev_vi_write == b->cond0_r1)))
        return NULL;
    key = entry_key(vu, b, c);
    if (key == KEY_NONE) return NULL;
    for (j = 0; j < b->nvar; j++)
        if (b->var[j]->key == key) return b->var[j];
    if (b->nvar < BLK_MAXVAR) {
        v = var_compile(vu, b, key);
        if (v) {
#ifdef BLK_JIT
            v->code = jit_gen(c, v);
#endif
            b->var[b->nvar++] = v;
        }
    }
    return v;
}

int vu__stats_default(void) { return env_flag("RG_VU_BLOCKS_STATS", 0); }

/* RG_VU_BLOCKS_STATS=1: vu_run calls this; a line on stderr at the first
 * program and then every 4 Mi pairs, per VU */
void vu__stats_tick(vu_state *vu)
{
    const vu_stats *s = &vu->stats;
    const vblk_cache *c = (const vblk_cache *)vu->blk;
    if (s->pairs < vu->stats_next) return;
    vu->stats_next = s->pairs + ((uint64_t)4 << 20);
    fprintf(stderr, "vu_block: VU%d runs %llu xgkicks %llu (%llu bytes) pairs %llu translated %llu (%.3f %%) "
            "interpreted %llu, block runs %llu (%.1f pairs each), blocks built %llu, variants %llu, pool %u, "
            "flushes %u\n",
            vu->id, (unsigned long long)s->runs, (unsigned long long)s->xgkicks,
            (unsigned long long)s->xgkick_bytes, (unsigned long long)s->pairs, (unsigned long long)s->blk_pairs,
            s->pairs ? 100.0 * (double)s->blk_pairs / (double)s->pairs : 0.0,
            (unsigned long long)s->blk_interp_pairs, (unsigned long long)s->blk_runs,
            s->blk_runs ? (double)s->blk_pairs / (double)s->blk_runs : 0.0,
            (unsigned long long)s->blk_builds, (unsigned long long)s->blk_variants, c ? c->nblocks : 0,
            c ? c->flushes : 0);
}

vu_stop vu__block_run(vu_state *vu, uint64_t max_cycles)
{
    uint64_t start = vu->cycle;
    vblk_cache *c = cache_of(vu);
    bvar *pv = NULL;   /* the variant that ran last, if nothing ran since */
    uint32_t cfg = (vu->int_branch_quirk ? 1u : 0u) | (vu->break_on_dt ? 2u : 0u);
    for (;;) {
        uint32_t ninterp = 1, k;
        if (!vu->running) return VU_STOP_IDLE;
        if (c && !vu->branch_pending && !vu->ebit_pending) {
            uint32_t pc = vu->pc & (vu->code_bytes - 1) & ~7u;
            vblk *b = NULL;
            bvar *v = NULL;
            bsucc *sc = NULL;
            if (pv) {
                sc = &pv->succ[0];
                if (sc->pc != pc) sc = &pv->succ[1];
                if (sc->pc == pc && c->map[pc >> 3] == sc->b && sc->cfg == cfg &&
                    ((sc->b->kq == 255 && sc->b->kp == 255) ||
                     entry_key_qp(vu, sc->b) == (sc->v->key & ~0x3Fu))) {
                    b = sc->b;
                    v = sc->v;
                } else {
                    sc = NULL;
                }
            }
            if (!v) {
                uint32_t fl = c->flushes;
                v = pick_variant(vu, c, pc, &b);
                if (c->flushes != fl) pv = NULL;   /* pv was freed */
                /* remember the transition when the VF key part was static:
                 * nothing older than pv can still be in flight (cycles >= 3) */
                if (v && pv && pv->cycles >= 3) {
                    bsucc *ns = &pv->succ[pv->succ_next];
                    pv->succ_next ^= 1;
                    ns->pc = pc;
                    ns->cfg = cfg;
                    ns->b = b;
                    ns->v = v;
                }
            }
            if (b) ninterp = b->n;
            if (v && !(max_cycles && vu->cycle + v->cycles - start >= max_cycles)) {
                vu_stop s = vu->blocks_check ? checked_variant(vu, c, b, v) : run_variant(vu, c, b, v);
                if (s != VU_STOP_CYCLES) return s;
                pv = v;
                continue;
            }
        }
        pv = NULL;
        for (k = 0; k < ninterp; k++) {
            vu_stop s = vu__step(vu);
            vu->stats.blk_interp_pairs++;
            if (s != VU_STOP_CYCLES) return s;
            if (max_cycles && vu->cycle - start >= max_cycles) return VU_STOP_CYCLES;
        }
    }
}

