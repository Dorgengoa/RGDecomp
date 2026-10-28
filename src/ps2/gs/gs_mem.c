/* SPDX-License-Identifier: CC0-1.0 */
/* GS local memory: block/page swizzling for every PSM, pixel access, and the
 * BITBLTBUF/TRXPOS/TRXREG/TRXDIR transfers.  docs/GS.md section "Memory".
 *
 * Geometry (GS manual):
 *   memory = 512 pages of 8 KB; page = 32 blocks of 256 B; block = 4 columns
 *   of 64 B.  Page sizes in pixels: 32-bit 64x32, 16-bit 64x64, 8-bit
 *   128x64, 4-bit 128x128.  Block sizes: 8x8, 16x8, 16x16, 32x16.
 *
 * The arrangements are expressed here as BIT FORMULAS (block number from
 * interleaved block-x/y bits, word number inside a column from x/y bits).
 * tests/gs/test_gs_swizzle.c checks them against the manual's figures typed
 * in as literal tables.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gs_internal.h"

/* Block number inside a page for the 32-bit arrangement (8 x 4 blocks):
 *    0  1  4  5 16 17 20 21
 *    2  3  6  7 18 19 22 23
 *    8  9 12 13 24 25 28 29
 *   10 11 14 15 26 27 30 31          bx in 0..7, by in 0..3 */
static inline uint32_t blk32(uint32_t bx, uint32_t by)
{
    return (bx & 1) | ((by & 1) << 1) | ((bx & 2) << 1) | ((by & 2) << 2) |
           ((bx & 4) << 2);
}
/* 16-bit arrangement (4 x 8 blocks):
 *    0  2  8 10 / 1 3 9 11 / 4 6 12 14 / 5 7 13 15 / then +16 */
static inline uint32_t blk16(uint32_t bx, uint32_t by)
{
    return (by & 1) | ((bx & 1) << 1) | ((by & 2) << 1) | ((bx & 2) << 2) |
           ((by & 4) << 2);
}
/* 16S arrangement (4 x 8 blocks):
 *    0  2 16 18 / 1 3 17 19 / 8 10 24 26 / 9 11 25 27 / 4 6 20 22 / ... */
static inline uint32_t blk16s(uint32_t bx, uint32_t by)
{
    return (by & 1) | ((bx & 1) << 1) | ((by & 4) << 0) | ((by & 2) << 2) |
           ((bx & 2) << 3);
}

/* word (0..15) inside a 64-byte column for the 32-bit layout, x in 0..7,
 * y in 0..1:   0 1 4 5 8 9 12 13 / 2 3 6 7 10 11 14 15 */
static inline uint32_t colword32(uint32_t x, uint32_t y)
{
    return (x & 1) | ((y & 1) << 1) | ((x & 6) << 1);
}

int gs_psm_bpp(int psm)
{
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32: return 32;
    case GS_PSMCT24: case GS_PSMZ24: return 24;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: return 16;
    case GS_PSMT8: case GS_PSMT8H: return 8;
    case GS_PSMT4: case GS_PSMT4HL: case GS_PSMT4HH: return 4;
    default: return 0;
    }
}

static inline uint32_t blkaddr(uint32_t bp, uint32_t page, uint32_t blk)
{
    return ((bp + page * 32u + blk) & 0x3FFFu) << 8;
}

/* 32-bit-layout address (CT32/24, Z32/24, T8H, T4HL/HH) */
static uint32_t addr32(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, int z)
{
    uint32_t page = (x >> 6) + (y >> 5) * bw;
    uint32_t blk = blk32((x >> 3) & 7, (y >> 3) & 3);
    if (z) blk ^= 24;
    return blkaddr(bp, page, blk) | (((y >> 1) & 3) << 6) |
           (colword32(x & 7, y & 1) << 2);
}

static uint32_t addr16(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y,
                       int s, int z)
{
    uint32_t page = (x >> 6) + (y >> 6) * bw;
    uint32_t bx = (x >> 4) & 3, by = (y >> 3) & 7;
    uint32_t blk = s ? blk16s(bx, by) : blk16(bx, by);
    if (z) blk ^= 24;
    /* 16x2 column: pixel x&7 shares the CT32 word slot, x>>3 picks the half */
    uint32_t w = colword32(x & 7, y & 1);
    return blkaddr(bp, page, blk) | (((y >> 1) & 3) << 6) | (w << 2) |
           (((x >> 3) & 1) << 1);
}

/* 8-bit: 16x4 column.  Rows 0,1 use bytes 0/2 of the CT32 words, rows 2,3
 * bytes 1/3; the x>>3 half picks byte +2; and the word x position is rotated
 * by 4 on rows 2,3 of even columns and on rows 0,1 of odd columns. */
static uint32_t addr8(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    uint32_t page = (x >> 7) + (y >> 6) * (bw >> 1);
    uint32_t blk = blk32((x >> 4) & 7, (y >> 4) & 3);
    uint32_t col = (y >> 2) & 3;
    uint32_t cy = y & 3, hi = cy >> 1;
    uint32_t xx = x & 7;
    if (hi ^ (col & 1)) xx ^= 4;
    uint32_t w = colword32(xx, cy & 1);
    uint32_t byte = (((x >> 3) & 1) << 1) | hi;
    return blkaddr(bp, page, blk) | (col << 6) | (w << 2) | byte;
}

/* 4-bit: 32x4 column, same rotation rule; nibble index in the word =
 * (x>>3 & 3)*2 + hi.  Returns the NIBBLE address. */
static uint32_t addr4n(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    uint32_t page = (x >> 7) + (y >> 7) * (bw >> 1);
    uint32_t blk = blk16((x >> 5) & 3, (y >> 4) & 7);
    uint32_t col = (y >> 2) & 3;
    uint32_t cy = y & 3, hi = cy >> 1;
    uint32_t xx = x & 7;
    if (hi ^ (col & 1)) xx ^= 4;
    uint32_t w = colword32(xx, cy & 1);
    uint32_t nib = (((x >> 3) & 3) << 1) | hi;
    return ((blkaddr(bp, page, blk) | (col << 6) | (w << 2)) << 1) + nib;
}

/* The pixel access functions are inlined into the transfer loop (host->local
 * uploads are most of the GS model's time on the GPU path, docs/GPU.md
 * "Performance"); the exported functions are the same code. */
#if defined(__GNUC__) || defined(__clang__)
#define GS_INLINE static inline __attribute__((always_inline))
#else
#define GS_INLINE static inline
#endif

GS_INLINE uint32_t pixel_addr_i(int psm, uint32_t bp, uint32_t bw, uint32_t x,
                                uint32_t y, int *nib)
{
    uint32_t a;
    x &= 2047; y &= 2047;
    if (nib) *nib = 0;
    switch (psm) {
    case GS_PSMCT32: case GS_PSMCT24: case GS_PSMT8H:
    case GS_PSMT4HL: case GS_PSMT4HH:
        return addr32(bp, bw, x, y, 0);
    case GS_PSMZ32: case GS_PSMZ24:
        return addr32(bp, bw, x, y, 1);
    case GS_PSMCT16: return addr16(bp, bw, x, y, 0, 0);
    case GS_PSMCT16S: return addr16(bp, bw, x, y, 1, 0);
    case GS_PSMZ16: return addr16(bp, bw, x, y, 0, 1);
    case GS_PSMZ16S: return addr16(bp, bw, x, y, 1, 1);
    case GS_PSMT8: return addr8(bp, bw, x, y);
    case GS_PSMT4:
        a = addr4n(bp, bw, x, y);
        if (nib) *nib = (int)(a & 1);
        return a >> 1;
    default:
        return addr32(bp, bw, x, y, 0);
    }
}

uint32_t gs_pixel_addr(int psm, uint32_t bp, uint32_t bw, uint32_t x,
                       uint32_t y, int *nib)
{
    return pixel_addr_i(psm, bp, bw, x, y, nib);
}

uint32_t gs_read_pixel(const gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                       uint32_t x, uint32_t y)
{
    int nib;
    uint32_t a = pixel_addr_i(psm, bp, bw, x, y, &nib);
    const uint8_t *m = gs->vram;
    uint32_t w;
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32: return gs_rd32(m + a);
    case GS_PSMCT24: case GS_PSMZ24: return gs_rd32(m + a) & 0xFFFFFFu;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S:
        return (uint32_t)m[a] | ((uint32_t)m[a + 1] << 8);
    case GS_PSMT8: return m[a];
    case GS_PSMT4: return nib ? (m[a] >> 4) : (m[a] & 15u);
    case GS_PSMT8H: return m[a + 3];
    case GS_PSMT4HL: return m[a + 3] & 15u;
    case GS_PSMT4HH: return m[a + 3] >> 4;
    default: w = gs_rd32(m + a); return w;
    }
}

GS_INLINE void write_pixel_i(gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                             uint32_t x, uint32_t y, uint32_t v)
{
    int nib;
    uint32_t a = pixel_addr_i(psm, bp, bw, x, y, &nib);
    uint8_t *m = gs->vram;
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32:
        m[a] = (uint8_t)v; m[a + 1] = (uint8_t)(v >> 8);
        m[a + 2] = (uint8_t)(v >> 16); m[a + 3] = (uint8_t)(v >> 24);
        break;
    case GS_PSMCT24: case GS_PSMZ24:
        m[a] = (uint8_t)v; m[a + 1] = (uint8_t)(v >> 8);
        m[a + 2] = (uint8_t)(v >> 16);
        break;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S:
        m[a] = (uint8_t)v; m[a + 1] = (uint8_t)(v >> 8);
        break;
    case GS_PSMT8: m[a] = (uint8_t)v; break;
    case GS_PSMT4:
        if (nib) m[a] = (uint8_t)((m[a] & 0x0F) | ((v & 15u) << 4));
        else m[a] = (uint8_t)((m[a] & 0xF0) | (v & 15u));
        break;
    case GS_PSMT8H: m[a + 3] = (uint8_t)v; break;
    case GS_PSMT4HL: m[a + 3] = (uint8_t)((m[a + 3] & 0xF0) | (v & 15u)); break;
    case GS_PSMT4HH: m[a + 3] = (uint8_t)((m[a + 3] & 0x0F) | ((v & 15u) << 4)); break;
    default: break;
    }
}

void gs_write_pixel(gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                    uint32_t x, uint32_t y, uint32_t v)
{
    write_pixel_i(gs, psm, bp, bw, x, y, v);
}

/* ---- colour conversion (frame/display/texture direct colour) ---- */
uint32_t gs_color_from_stored(int psm, uint32_t raw)
{
    if (gs_psm_is16(psm)) {
        uint32_t r = (raw & 31u) << 3, g = ((raw >> 5) & 31u) << 3,
                 b = ((raw >> 10) & 31u) << 3, a = (raw & 0x8000u) ? 0x80u : 0u;
        return r | (g << 8) | (b << 16) | (a << 24);
    }
    if (psm == GS_PSMCT24 || psm == GS_PSMZ24) return raw & 0xFFFFFFu;
    return raw;
}

uint32_t gs_color_to_stored(int psm, uint32_t c)
{
    if (gs_psm_is16(psm)) {
        return ((c >> 3) & 31u) | (((c >> 11) & 31u) << 5) |
               (((c >> 19) & 31u) << 10) | ((c >> 31) << 15);
    }
    if (psm == GS_PSMCT24 || psm == GS_PSMZ24) return c & 0xFFFFFFu;
    return c;
}

void gs_read_rect_rgba(const gs_state *gs, int psm, uint32_t bp, uint32_t bw,
                       uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                       uint32_t *out)
{
    for (uint32_t y = 0; y < h; y++)
        for (uint32_t x = 0; x < w; x++)
            out[y * w + x] = gs_color_from_stored(
                psm, gs_read_pixel(gs, psm, bp, bw, x0 + x, y0 + y));
}

/* ---------------------------------------------------------------------- */
/* Transfers                                                                */

typedef struct xfer_geom {
    uint32_t sbp, sbw, spsm, dbp, dbw, dpsm;
    uint32_t ssax, ssay, dsax, dsay, dir;
    uint32_t rrw, rrh;
} xfer_geom;

static void xfer_geom_get(const gs_state *gs, xfer_geom *g)
{
    uint64_t b = gs->reg[GS_BITBLTBUF], p = gs->reg[GS_TRXPOS],
             r = gs->reg[GS_TRXREG];
    g->sbp = GS_BITS(b, 0, 14); g->sbw = GS_BITS(b, 16, 6);
    g->spsm = GS_BITS(b, 24, 6); g->dbp = GS_BITS(b, 32, 14);
    g->dbw = GS_BITS(b, 48, 6); g->dpsm = GS_BITS(b, 56, 6);
    g->ssax = GS_BITS(p, 0, 11); g->ssay = GS_BITS(p, 16, 11);
    g->dsax = GS_BITS(p, 32, 11); g->dsay = GS_BITS(p, 48, 11);
    g->dir = GS_BITS(p, 59, 2);
    g->rrw = GS_BITS(r, 0, 12); g->rrh = GS_BITS(r, 32, 12);
}

/* ---------------------------------------------------------------------- */
/* Redundant upload elision (gs.h "redundant upload elision").
 *
 * Every page has a write generation, bumped by the model's own writes
 * (host->local transfers when they start writing, local->local copies, a GS
 * reset) and, through gs_mem_gen_bump, by the renderer's (drawn targets
 * written back to its local-memory copy, CPU-fallback draws, external
 * writers).  A completed host->local transfer that arrived in one IMAGE run
 * is remembered as (geometry, hash of its bytes, sum of its pages'
 * generations after it).  The next transfer with the same geometry whose
 * bytes hash the same, while that sum is unchanged and the renderer holds no
 * newer data there (hooks.xfer_clean), would write exactly the bytes local
 * memory holds: it is elided.  Generations only grow, so an unchanged sum
 * means no page was written.  The WRITE_BEGIN hook of a host->local transfer
 * is deferred to its first data (nothing is written before), so an elided
 * transfer makes no hook call at all. */
#define ELIDE_SLOTS 16384
typedef struct gs_xfer_elide {
    uint32_t gen[16384];        /* per 256-byte block */
    struct {
        uint32_t key[7];        /* dbp, dbw, dpsm, dsax, dsay, rrw, rrh */
        uint32_t bytes;
        uint64_t hash;
        uint64_t gsum;
        int used;
    } ent[ELIDE_SLOTS];
    int pending;                /* host->local transfer started, BEGIN hook deferred */
    int cand;                   /* this transfer is recorded at its end (whole in one run) */
    uint32_t cand_key[7], cand_bytes;
    uint64_t cand_hash;
    int nowrite;                /* xfer_row writes nothing (the transfer is elided) */
    /* staging: a transfer whose IMAGE data comes in several GIF writes of one
     * IMAGE run (nothing else can run on the GS meanwhile: the path owns the
     * bus mid-packet) is collected and written whole (block-wise / elided) */
    uint8_t *stage;
    uint32_t stage_len, stage_cap;
    int staging;
} gs_xfer_elide;
/* the switch and the counters are the process's, not the run's: host state
 * (src/savestate/ss_map.c), a loaded state keeps the loader's */
static volatile struct {
    int on;                     /* -1 unknown, 0 off ($RG_GS_ELIDE=0), 1 on */
    uint64_t seen, elided, bytes_elided, hashed;
    uint64_t miss_noent, miss_hash, miss_gen, miss_veto, fast, fast_bytes, staged, row_px, row_calls;
} g_elide_host = { -1 };

int gs_stage_path;   /* the GIF path of the IMAGE data being staged (gs_core.c) */
static int fastxfer_on = -1, fastxfer_check = -1, elide_log;   /* $RG_GS_FASTXFER, $RG_GS_XFER_CHECK (host state, ss_map.c) */

static gs_xfer_elide *elide_get(gs_state *gs)
{
    gs_xfer_elide *e = (gs_xfer_elide *)gs->xfer_elide;
    if (!e) {
        e = (gs_xfer_elide *)calloc(1, sizeof *e);
        if (!e) return NULL;
        gs->xfer_elide = e;
    }
    if (g_elide_host.on < 0) {
        const char *v = getenv("RG_GS_ELIDE");
        g_elide_host.on = !(v && v[0] == '0');
    }
    if (fastxfer_on < 0) {
        const char *v = getenv("RG_GS_FASTXFER");
        fastxfer_on = !(v && v[0] == '0');
        v = getenv("RG_GS_XFER_CHECK");
        fastxfer_check = v && v[0] == '1';
        elide_log = getenv("RG_GS_ELIDE_LOG") != NULL;
    }
    return e;
}

static int lz_accept(gs_state *gs, gs_xfer_elide *e, const struct xfer_geom *g, const uint8_t *d, uint32_t bytes, uint64_t h);
static void lz_before_write(gs_state *gs, const gs_mem_rect *r, int whole);

/* every 256-byte block of the rectangle of a buffer: the generations are kept
 * per block (textures share pages; a page granularity made every upload into
 * a page look like a write to its neighbours).  op 0: sum, 1: bump. */
static uint64_t gen_rect(gs_xfer_elide *e, int op, int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y,
                         uint32_t w, uint32_t h)
{
    uint32_t bwk = 8, bhk = 8, x1 = x + w, y1 = y + h;
    uint64_t sum = 0;
    if (!w || !h) return 0;
    switch (psm) {
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: bwk = 16; bhk = 8; break;
    case GS_PSMT8: bwk = 16; bhk = 16; break;
    case GS_PSMT4: bwk = 32; bhk = 16; break;
    default: break;
    }
    if (x1 > 2048 || y1 > 2048) {   /* wraps: every block */
        for (uint32_t i = 0; i < 16384; i++) { if (op) e->gen[i]++; sum += e->gen[i]; }
        return sum;
    }
    for (uint32_t by = y / bhk; by <= (y1 - 1) / bhk; by++)
        for (uint32_t bx = x / bwk; bx <= (x1 - 1) / bwk; bx++) {
            uint32_t blk = (gs_pixel_addr(psm, bp, bw ? bw : 1, bx * bwk, by * bhk, NULL) >> 8) & 16383u;
            if (op) e->gen[blk]++;
            sum += e->gen[blk];
        }
    return sum;
}

void gs_mem_gen_bump(gs_state *gs, const uint32_t *pages16)
{
    gs_xfer_elide *e = gs ? (gs_xfer_elide *)gs->xfer_elide : NULL;
    if (!e) return;
    for (uint32_t pg = 0; pg < 512; pg++)
        if (!pages16 || ((pages16[pg >> 5] >> (pg & 31)) & 1u))
            for (uint32_t k = 0; k < 32; k++) e->gen[pg * 32 + k]++;
}

void gs_xfer_elide_stats(const gs_state *gs, uint64_t out[4])
{
    (void)gs;
    out[0] = g_elide_host.seen;
    out[1] = g_elide_host.elided;
    out[2] = g_elide_host.bytes_elided;
    out[3] = g_elide_host.hashed;
    if (getenv("RG_GS_ELIDE_STATS"))
        fprintf(stderr, "gs elide: misses: no entry %llu, other bytes %llu, written since %llu, renderer veto %llu; block-wise %llu (%.1f MB), staged %llu; row path %llu pixels in %llu rows\n",
                (unsigned long long)g_elide_host.miss_noent, (unsigned long long)g_elide_host.miss_hash, (unsigned long long)g_elide_host.miss_gen,
                (unsigned long long)g_elide_host.miss_veto, (unsigned long long)g_elide_host.fast,
                (double)g_elide_host.fast_bytes / 1e6, (unsigned long long)g_elide_host.staged,
                (unsigned long long)g_elide_host.row_px, (unsigned long long)g_elide_host.row_calls);
}

/* four interleaved 32-bit lanes (murmur3 mixing) + length: 128 bits folded to 64 */
static uint64_t elide_hash(const uint8_t *d, uint32_t n)
{
    uint32_t h[4] = { 0x9747B28Cu, 0x85EBCA6Bu, 0xC2B2AE35u, 0x27D4EB2Fu }, i, k;
    uint32_t w[4];
    for (i = 0; i + 16 <= n; i += 16) {
        memcpy(w, d + i, 16);
        for (k = 0; k < 4; k++) {
            uint32_t v = w[k] * 0xCC9E2D51u;
            v = (v << 15) | (v >> 17);
            v *= 0x1B873593u;
            h[k] ^= v;
            h[k] = ((h[k] << 13) | (h[k] >> 19)) * 5u + 0xE6546B64u;
        }
    }
    for (k = 0; i < n; i++, k++) h[k & 3] = (h[k & 3] ^ d[i]) * 0x01000193u;
    for (k = 0; k < 4; k++) {
        h[k] ^= n;
        h[k] ^= h[k] >> 16; h[k] *= 0x85EBCA6Bu; h[k] ^= h[k] >> 13; h[k] *= 0xC2B2AE35u; h[k] ^= h[k] >> 16;
    }
    return ((uint64_t)(h[0] ^ h[2]) << 32) | (h[1] ^ h[3]);
}

static uint32_t xfer_bytes(const xfer_geom *g)
{
    uint64_t px = (uint64_t)g->rrw * g->rrh;
    int bpp = gs_psm_bpp((int)g->dpsm);
    return (uint32_t)(bpp == 4 ? (px + 1) / 2 : px * (uint64_t)(bpp / 8));
}

static void elide_key(const xfer_geom *g, uint32_t k[7])
{
    k[0] = g->dbp; k[1] = g->dbw; k[2] = g->dpsm; k[3] = g->dsax; k[4] = g->dsay; k[5] = g->rrw; k[6] = g->rrh;
}

static uint32_t elide_slot(const uint32_t k[7])
{
    uint32_t h = 2166136261u;
    for (int i = 0; i < 7; i++) h = (h ^ k[i]) * 16777619u;
    return (h ^ (h >> 15)) % ELIDE_SLOTS;
}

/* the deferred WRITE_BEGIN of the open host->local transfer: the model
 * writes from now on */
static void elide_commit(gs_state *gs, gs_xfer_elide *e)
{
    gs_mem_rect *r = &gs->hooks.xfer_rect;
    e->pending = 0;
    gen_rect(e, 1, r->psm, r->bp, r->bw, r->x, r->y, r->w, r->h);
    gs->hooks.xfer_open = 1;
    if (gs->hooks.mem) gs->hooks.mem(gs->hooks.user, gs, GS_MEM_WRITE_BEGIN, r);
}

/* first data of a deferred transfer: 1 = elide it (d holds all of it and
 * local memory holds the same bytes), 0 = written (BEGIN made) */
static int elide_decide(gs_state *gs, gs_xfer_elide *e, const xfer_geom *g, const uint8_t *d, uint32_t n)
{
    uint32_t key[7], bytes = xfer_bytes(g);
    e->cand = 0;
    if (gs->xfer_x == 0 && gs->xfer_y == 0 && gs->xfer_carry_n == 0 && bytes && n >= bytes) {
        uint64_t h = elide_hash(d, bytes);
        uint32_t s;
        g_elide_host.hashed++;
        elide_key(g, key);
        s = elide_slot(key);
        if (!e->ent[s].used || e->ent[s].bytes != bytes || memcmp(e->ent[s].key, key, sizeof key)) g_elide_host.miss_noent++;
        else if (e->ent[s].hash != h) g_elide_host.miss_hash++;
        else if (gen_rect(e, 0, (int)g->dpsm, g->dbp, g->dbw, g->dsax, g->dsay, g->rrw, g->rrh) != e->ent[s].gsum) g_elide_host.miss_gen++;
        else if (!gs->hooks.xfer_clean || !gs->hooks.xfer_clean(gs->hooks.user, gs, &gs->hooks.xfer_rect)) g_elide_host.miss_veto++;
        else goto elide;
        if (elide_log && g_elide_host.hashed < 3000)
            fprintf(stderr, "gs elide: miss %llu: bp %u bw %u psm %u at %u,%u %ux%u bytes %u hash %016llx (slot: %u,%u %ux%u hash %016llx)\n",
                    (unsigned long long)g_elide_host.hashed, key[0], key[1], key[2], key[3], key[4], key[5], key[6], bytes,
                    (unsigned long long)h, e->ent[s].key[3], e->ent[s].key[4], e->ent[s].key[5], e->ent[s].key[6],
                    (unsigned long long)e->ent[s].hash);
        if (0) {
        elide:
            e->pending = 0;
            g_elide_host.elided++;
            g_elide_host.bytes_elided += bytes;
            return 1;
        }
        if (lz_accept(gs, e, g, d, bytes, h)) {
            /* pending: written when something needs the bytes (lazy transfers) */
            e->pending = 0;
            e->cand = 0;
            return 1;
        }
        e->cand = 1;
        memcpy(e->cand_key, key, sizeof key);
        e->cand_bytes = bytes;
        e->cand_hash = h;
        lz_before_write(gs, &gs->hooks.xfer_rect, 1);
    } else {
        lz_before_write(gs, &gs->hooks.xfer_rect, 0);
    }
    elide_commit(gs, e);
    return 0;
}

/* the transfer ended: remember it when it was hashed and completed */
static void elide_end(gs_state *gs, gs_xfer_elide *e, int complete)
{
    e->pending = 0;
    if (!e->cand) return;
    e->cand = 0;
    if (!complete) return;
    {
        uint32_t s = elide_slot(e->cand_key);
        const gs_mem_rect *r = &gs->hooks.xfer_rect;
        memcpy(e->ent[s].key, e->cand_key, sizeof e->cand_key);
        e->ent[s].bytes = e->cand_bytes;
        e->ent[s].hash = e->cand_hash;
        e->ent[s].gsum = gen_rect(e, 0, r->psm, r->bp, r->bw, r->x, r->y, r->w, r->h);
        e->ent[s].used = 1;
    }
}

/* ---------------------------------------------------------------------- */
/* Lazy host->local transfers (gs.h "lazy transfers", docs/NATIVE-RENDER.md
 * "Texture uploads").
 *
 * A whole transfer (the data of one IMAGE run, staged) whose rectangle the
 * renderer does not hold (hooks.lazy_ok) is kept as an entry: its registers,
 * a copy of its bytes and their hash.  Every 256-byte block it covers is
 * owned by it (owner[]); blocks are owned by at most one entry, because a new
 * entry first materializes (writes) every entry it partly overlaps and
 * replaces the one with exactly its geometry.  Materializing replays the
 * transfer through the normal path (xfer_image_body, with the WRITE_BEGIN /
 * WRITE_END hooks unless the renderer asks from inside its bookkeeping) with
 * the transfer registers and state saved around it.  Accepting an entry
 * bumps the elision generations of its blocks: local memory no longer holds
 * what an elision entry recorded there.  All of it lives in the GS model's
 * heap block (gs->xfer_lazy), which save states keep with the model; the
 * runtime materializes everything before a state is written (gpu_sync). */
#define LZ_MAX 2048
#define LZ_MAX_BYTES (1u << 20)
typedef struct gs_lazy_ent {
    int used;
    uint64_t bitblt, trxpos, trxreg;   /* the transfer registers at issue */
    xfer_geom g;
    uint32_t bytes;
    uint8_t *data;
    uint64_t hash;
    uint32_t memo[4][5];        /* textures (bp + 1, bw, psm, w, h) whose blocks it covers */
    uint32_t nmemo;
} gs_lazy_ent;
typedef struct gs_lazy {
    int on;                     /* $RG_GS_LAZY (default on) */
    uint16_t owner[16384];      /* per 256-byte block: entry + 1, 0 = none */
    uint16_t pcnt[512];         /* owned blocks per page */
    uint32_t any[16];           /* pages with owned blocks */
    uint16_t tmp[16384];        /* block list scratch */
    gs_lazy_ent e[LZ_MAX];
    uint32_t n, hint;
    uint64_t st[8];
    int cause;                  /* measurement: who asked (bycause[]) */
    uint64_t bycause[8];        /* 0 pages+hooks, 1 pages raw, 2 rect (model reads), 3 overlap at accept, 4 real write */
    uint8_t *scratch;           /* gs_mem_lazy_texels: a local-memory copy to decode in */
    uint32_t wpages[16];        /* pages written by materializations (gs_mem_lazy_take_written) */
} gs_lazy;

static void xfer_image_body(gs_state *gs, const xfer_geom *gp, int bpp, const uint8_t *d, uint32_t n);

static gs_lazy *lz_get(gs_state *gs)
{
    gs_lazy *lz = (gs_lazy *)gs->xfer_lazy;
    if (!lz) {
        const char *v = getenv("RG_GS_LAZY");
        lz = (gs_lazy *)calloc(1, sizeof *lz);
        if (!lz) return NULL;
        lz->on = !(v && v[0] == '0');
        gs->xfer_lazy = lz;
    }
    return lz;
}

/* the blocks of a rectangle (no wrap: the caller checks) into lz->tmp */
static uint32_t lz_blocks(gs_lazy *lz, int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    uint32_t bwk = 8, bhk = 8, n = 0;
    if (!w || !h) return 0;
    switch (psm) {
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: bwk = 16; bhk = 8; break;
    case GS_PSMT8: bwk = 16; bhk = 16; break;
    case GS_PSMT4: bwk = 32; bhk = 16; break;
    default: break;
    }
    if (x + w > 2048 || y + h > 2048) {     /* wraps: every block (callers only ask) */
        for (uint32_t i = 0; i < 16384; i++) lz->tmp[i] = (uint16_t)i;
        return 16384;
    }
    {
        /* the block layout of a page as a table (the formats lazy transfers and
         * textures use): block = bp + page * 32 + table[block row][block col] */
        static uint8_t tab[4][8][8];
        static int tab_ok[4];
        int L = -1;
        uint32_t pw = 64, ph = 32, bwp = bw ? bw : 1;
        switch (psm) {
        case GS_PSMCT32: case GS_PSMCT24: case GS_PSMT8H: case GS_PSMT4HL: case GS_PSMT4HH: L = 0; break;
        case GS_PSMCT16: L = 1; ph = 64; break;
        case GS_PSMT8: if (!(bwp & 1)) { L = 2; pw = 128; ph = 64; bwp >>= 1; } break;
        case GS_PSMT4: if (!(bwp & 1)) { L = 3; pw = 128; ph = 128; bwp >>= 1; } break;
        default: break;
        }
        if (L >= 0) {
            uint32_t ncol = pw / bwk, nrow = ph / bhk;
            if (!tab_ok[L]) {
                int tpsm = L == 0 ? GS_PSMCT32 : L == 1 ? GS_PSMCT16 : L == 2 ? GS_PSMT8 : GS_PSMT4;
                for (uint32_t r = 0; r < nrow; r++)
                    for (uint32_t c = 0; c < ncol; c++)
                        tab[L][r][c] = (uint8_t)(gs_pixel_addr(tpsm, 0, pw / 64, c * bwk, r * bhk, NULL) >> 8);
                tab_ok[L] = 1;
            }
            for (uint32_t by = y / bhk; by <= (y + h - 1) / bhk; by++) {
                uint32_t prow = (by * bhk) / ph, r = by % nrow;
                for (uint32_t bx = x / bwk; bx <= (x + w - 1) / bwk && n < 16384; bx++) {
                    uint32_t pcol = (bx * bwk) / pw;
                    lz->tmp[n++] = (uint16_t)((bp + (pcol + prow * bwp) * 32u + tab[L][r][bx % ncol]) & 16383u);
                }
            }
            return n;
        }
    }
    for (uint32_t by = y / bhk; by <= (y + h - 1) / bhk; by++)
        for (uint32_t bx = x / bwk; bx <= (x + w - 1) / bwk && n < 16384; bx++)
            lz->tmp[n++] = (uint16_t)((gs_pixel_addr(psm, bp, bw ? bw : 1, bx * bwk, by * bhk, NULL) >> 8) & 16383u);
    return n;
}

static int lz_same(const xfer_geom *a, const xfer_geom *b)
{
    return a->dbp == b->dbp && a->dbw == b->dbw && a->dpsm == b->dpsm && a->dsax == b->dsax && a->dsay == b->dsay &&
           a->rrw == b->rrw && a->rrh == b->rrh;
}

static void lz_drop(gs_lazy *lz, uint32_t i)
{
    gs_lazy_ent *en = &lz->e[i];
    uint32_t nb = lz_blocks(lz, (int)en->g.dpsm, en->g.dbp, en->g.dbw, en->g.dsax, en->g.dsay, en->g.rrw, en->g.rrh);
    for (uint32_t k = 0; k < nb; k++) {
        uint32_t b = lz->tmp[k];
        if (lz->owner[b] != i + 1) continue;
        lz->owner[b] = 0;
        if (--lz->pcnt[b >> 5] == 0) lz->any[b >> 10] &= ~(1u << ((b >> 5) & 31));
    }
    free(en->data);
    en->data = NULL;
    en->used = 0;
    lz->n--;
}

/* the transfer of entry en (bytes `data`) replayed through the normal path,
 * with every bit of transfer state saved around it; hooks: the renderer's
 * WRITE_BEGIN / WRITE_END; gen: bump the elision generations */
static void lz_replay(gs_state *gs, const gs_lazy_ent *en, const uint8_t *data, int hooks, int gen)
{
    gs_xfer_elide *el = elide_get(gs);
    xfer_geom g = en->g;
    int bpp = gs_psm_bpp((int)g.dpsm);
    uint64_t r0 = gs->reg[GS_BITBLTBUF], r1 = gs->reg[GS_TRXPOS], r2 = gs->reg[GS_TRXREG], hw = gs->reg[GS_HWREG];
    int xdir = gs->xfer_dir, xo = gs->hooks.xfer_open;
    uint32_t xx = gs->xfer_x, xy = gs->xfer_y, cn = gs->xfer_carry_n;
    uint8_t carry[8];
    gs_mem_rect xr = gs->hooks.xfer_rect;
    uint64_t px = gs->stats.xfer_h2l_px;
    int ep = el ? el->pending : 0, ec = el ? el->cand : 0, enw = el ? el->nowrite : 0, est = el ? el->staging : 0;
    memcpy(carry, gs->xfer_carry, sizeof carry);
    if (el) { el->pending = 0; el->cand = 0; el->nowrite = 0; el->staging = 0; }
    gs->reg[GS_BITBLTBUF] = en->bitblt;
    gs->reg[GS_TRXPOS] = en->trxpos;
    gs->reg[GS_TRXREG] = en->trxreg;
    gs->xfer_dir = 0;
    gs->xfer_x = gs->xfer_y = 0;
    gs->xfer_carry_n = 0;
    {
        gs_mem_rect *r = &gs->hooks.xfer_rect;
        r->bp = g.dbp; r->bw = g.dbw; r->psm = (int)g.dpsm; r->x = g.dsax; r->y = g.dsay; r->w = g.rrw; r->h = g.rrh;
        if (el && gen) gen_rect(el, 1, r->psm, r->bp, r->bw, r->x, r->y, r->w, r->h);
        gs->hooks.xfer_open = hooks && gs->hooks.mem;
        if (gs->hooks.xfer_open) gs->hooks.mem(gs->hooks.user, gs, GS_MEM_WRITE_BEGIN, r);
    }
    if (bpp && data) xfer_image_body(gs, &g, bpp, data, en->bytes);
    if (gs->hooks.xfer_open) gs_xfer_end_hook(gs);   /* (the body ends it when complete) */
    gs->reg[GS_BITBLTBUF] = r0; gs->reg[GS_TRXPOS] = r1; gs->reg[GS_TRXREG] = r2; gs->reg[GS_HWREG] = hw;
    gs->xfer_dir = xdir; gs->xfer_x = xx; gs->xfer_y = xy; gs->xfer_carry_n = cn;
    memcpy(gs->xfer_carry, carry, sizeof carry);
    gs->hooks.xfer_rect = xr; gs->hooks.xfer_open = xo;
    gs->stats.xfer_h2l_px = px;
    if (el) { el->pending = ep; el->cand = ec; el->nowrite = enw; el->staging = est; }
}

/* write entry i into local memory now (the transfer replayed), then forget it */
static void lz_write(gs_state *gs, gs_lazy *lz, uint32_t i, int hooks)
{
    gs_lazy_ent en = lz->e[i];
    {
        uint32_t nb = lz_blocks(lz, (int)en.g.dpsm, en.g.dbp, en.g.dbw, en.g.dsax, en.g.dsay, en.g.rrw, en.g.rrh);
        for (uint32_t k = 0; k < nb; k++) lz->wpages[lz->tmp[k] >> 10] |= 1u << ((lz->tmp[k] >> 5) & 31);
    }
    lz->e[i].data = NULL;
    lz_drop(lz, i);                 /* the blocks are free before anything is written */
    lz_replay(gs, &en, en.data, hooks, 1);
    free(en.data);
    lz->st[1]++;
    lz->bycause[lz->cause & 7]++;
    lz->st[4] += en.bytes;
    if (!hooks) lz->st[7]++;
}

/* materialize every entry owning one of the blocks in lz->tmp[0..nb) except
 * `keep` (an entry index, or -1); returns how many were written */
static int lz_write_blocks(gs_state *gs, gs_lazy *lz, uint32_t nb, int keep, int hooks)
{
    static uint16_t own[LZ_MAX];
    uint32_t no = 0, k;
    int w = 0;
    for (k = 0; k < nb; k++) {
        uint32_t o = lz->owner[lz->tmp[k]];
        if (o && (int)o - 1 != keep) {
            uint32_t j;
            for (j = 0; j < no && own[j] != o; j++) {}
            if (j == no && no < LZ_MAX) own[no++] = (uint16_t)o;
        }
    }
    for (k = 0; k < no; k++)
        if (lz->e[own[k] - 1].used) { lz_write(gs, lz, own[k] - 1u, hooks); w++; }
    return w;
}

void gs_mem_materialize(gs_state *gs, const uint32_t *pages16, int hooks)
{
    gs_lazy *lz = gs ? (gs_lazy *)gs->xfer_lazy : NULL;
    if (!lz || !lz->n) return;
    lz->cause = hooks ? 0 : 1;
    for (uint32_t pg = 0; pg < 512; pg++) {
        if (!((lz->any[pg >> 5] >> (pg & 31)) & 1u)) continue;
        if (pages16 && !((pages16[pg >> 5] >> (pg & 31)) & 1u)) continue;
        for (uint32_t k = 0; k < 32 && lz->pcnt[pg]; k++) {
            uint32_t o = lz->owner[pg * 32 + k];
            if (o && lz->e[o - 1].used) lz_write(gs, lz, o - 1, hooks);
        }
    }
}

void gs_mem_materialize_rect_h(gs_state *gs, int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y,
                               uint32_t w, uint32_t h, int hooks)
{
    gs_lazy *lz = gs ? (gs_lazy *)gs->xfer_lazy : NULL;
    if (!lz || !lz->n) return;
    lz->cause = hooks ? 2 : 5;
    lz_write_blocks(gs, lz, lz_blocks(lz, psm, bp, bw, x & 2047, y & 2047, w, h), -1, hooks);
}

void gs_mem_materialize_rect(gs_state *gs, int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y,
                             uint32_t w, uint32_t h)
{
    gs_mem_materialize_rect_h(gs, psm, bp, bw, x, y, w, h, 1);
}

void gs_mem_lazy_take_written(gs_state *gs, uint32_t *pages16)
{
    gs_lazy *lz = gs ? (gs_lazy *)gs->xfer_lazy : NULL;
    if (!lz) return;
    if (pages16) for (int i = 0; i < 16; i++) pages16[i] |= lz->wpages[i];
    memset(lz->wpages, 0, sizeof lz->wpages);
}

int gs_mem_lazy_pages(const gs_state *gs, uint32_t *pages16)
{
    const gs_lazy *lz = gs ? (const gs_lazy *)gs->xfer_lazy : NULL;
    if (!lz || !lz->n) return 0;
    for (int i = 0; i < 16; i++) pages16[i] |= lz->any[i];
    return 1;
}

int gs_mem_lazy_texels(gs_state *gs, uint32_t bp, uint32_t bw, int psm, uint32_t w, uint32_t h, uint64_t *key,
                       uint32_t *raw)
{
    gs_lazy *lz = gs ? (gs_lazy *)gs->xfer_lazy : NULL;
    uint32_t o, k, nb;
    gs_lazy_ent *en;
    int m;
    if (!lz || !lz->n || !w || !h || w > 1024 || h > 1024) return 0;
    o = lz->owner[(gs_pixel_addr(psm, bp, bw ? bw : 1, 0, 0, NULL) >> 8) & 16383u];
    if (!o) {
        static int nlog0 = -1;
        if (nlog0 < 0) nlog0 = getenv("RG_GS_LAZY_LOG") ? 0 : 1000000;
        if (nlog0 < 300) {
            uint32_t nb2 = lz_blocks(lz, psm, bp, bw, 0, 0, w, h), k2, np = 0, o1 = 0;
            for (k2 = 0; k2 < nb2; k2++) if (lz->owner[lz->tmp[k2]]) { np++; if (!o1) o1 = lz->owner[lz->tmp[k2]]; }
            nlog0++;
            if (np) {
                const gs_lazy_ent *e1 = &lz->e[o1 - 1];
                fprintf(stderr, "gs lazy texels nofirst: texture bp %u bw %u psm %02x %ux%u: %u of %u blocks pending; e.g. bp %u bw %u psm %02x at %u,%u %ux%u\n",
                        bp, bw, psm, w, h, np, nb2, e1->g.dbp, e1->g.dbw, e1->g.dpsm, e1->g.dsax, e1->g.dsay, e1->g.rrw, e1->g.rrh);
            }
        }
        return 0;
    }
    en = &lz->e[o - 1];
    if (!en->used) return 0;
    /* every block of the texture belongs to this one transfer (checked once per
     * entry and texture: the entry keeps its blocks while it lives) */
    for (m = 0; m < 4; m++)
        if (en->memo[m][0] == bp + 1 && en->memo[m][1] == bw && en->memo[m][2] == (uint32_t)psm &&
            en->memo[m][3] == w && en->memo[m][4] == h)
            break;
    if (m == 4) {
        nb = lz_blocks(lz, psm, bp, bw, 0, 0, w, h);
        for (k = 0; k < nb; k++)
            if (lz->owner[lz->tmp[k]] != o) {
                static int nlog = -1;
                if (nlog < 0) nlog = getenv("RG_GS_LAZY_LOG") ? 0 : 1000000;
                if (nlog < 100000000 && (nlog++ % 997) == 0) {   /* (a sample of the misses) */
                    uint32_t o2 = lz->owner[lz->tmp[k]];
                    fprintf(stderr, "gs lazy texels miss: texture bp %u bw %u psm %02x %ux%u; pending bp %u bw %u psm %02x at %u,%u %ux%u; block %u/%u owner %u%s\n",
                            bp, bw, psm, w, h, en->g.dbp, en->g.dbw, en->g.dpsm, en->g.dsax, en->g.dsay, en->g.rrw, en->g.rrh,
                            k, nb, o2, o2 ? "" : " (none)");
                }
                return 0;
            }
        m = en->nmemo++ & 3;
        en->memo[m][0] = bp + 1; en->memo[m][1] = bw; en->memo[m][2] = (uint32_t)psm;
        en->memo[m][3] = w; en->memo[m][4] = h;
    }
    {
        /* content key: the bytes, the transfer's geometry relative to the
         * texture, the texture's format (not its address: pool slots alike) */
        uint64_t x = en->hash;
        uint32_t f[10] = { en->g.dpsm, en->g.dbw, en->g.rrw, en->g.rrh, en->g.dsax, en->g.dsay, en->g.dbp - bp,
                           (uint32_t)psm | (bw << 8), w | (h << 16), bp & 31u };
        for (k = 0; k < 10; k++) x = (x ^ f[k]) * 0x100000001B3ull;
        *key = x;
    }
    if (raw) {
        /* the texels as local memory would hold them: the transfer written into
         * a scratch copy of local memory (only its blocks matter), read back */
        uint8_t *vram = gs->vram;
        if (!lz->scratch) lz->scratch = (uint8_t *)calloc(1, GS_VRAM_BYTES);
        if (!lz->scratch) return 0;
        gs->vram = lz->scratch;
        lz_replay(gs, en, en->data, 0, 0);
        for (uint32_t y = 0; y < h; y++)
            for (uint32_t xx = 0; xx < w; xx++) raw[y * w + xx] = gs_read_pixel(gs, psm, bp, bw, xx, y);
        gs->vram = vram;
    }
    lz->st[6]++;
    return 1;
}

void gs_mem_lazy_free(gs_state *gs)
{
    gs_lazy *lz = (gs_lazy *)gs->xfer_lazy;
    if (!lz) return;
    for (uint32_t i = 0; i < LZ_MAX; i++) free(lz->e[i].data);
    free(lz->scratch);
    free(lz);
    gs->xfer_lazy = NULL;
}

uint64_t gs_mem_lazy_gen(const gs_state *gs)
{
    const gs_lazy *lz = gs ? (const gs_lazy *)gs->xfer_lazy : NULL;
    return lz && lz->n ? lz->st[0] : 0;
}

void gs_mem_lazy_stats(const gs_state *gs, uint64_t out[8])
{
    const gs_lazy *lz = gs ? (const gs_lazy *)gs->xfer_lazy : NULL;
    for (int i = 0; i < 8; i++) out[i] = lz ? lz->st[i] : 0;
    if (lz && getenv("RG_GS_LAZY_STATS"))
        fprintf(stderr, "gs lazy: written by cause: pages %llu, pages raw %llu, model reads %llu, overlap at accept %llu, real write %llu, texture rect raw %llu\n",
                (unsigned long long)lz->bycause[0], (unsigned long long)lz->bycause[1], (unsigned long long)lz->bycause[2],
                (unsigned long long)lz->bycause[3], (unsigned long long)lz->bycause[4], (unsigned long long)lz->bycause[5]);
}

/* elide_decide: the whole transfer (d, bytes, hash h) stays pending instead of
 * being written; 1 = accepted (the caller runs it without writing) */
static int lz_accept(gs_state *gs, gs_xfer_elide *e, const xfer_geom *g, const uint8_t *d, uint32_t bytes, uint64_t h)
{
    gs_lazy *lz = lz_get(gs);
    uint32_t nb, k, i;
    int same = -1;
    if (!lz || !lz->on || !gs->hooks.lazy_ok || bytes > LZ_MAX_BYTES || !gs_psm_bpp((int)g->dpsm) ||
        g->dsax + g->rrw > 2048 || g->dsay + g->rrh > 2048)
        return 0;
    if (!gs->hooks.lazy_ok(gs->hooks.user, gs, &gs->hooks.xfer_rect)) { lz->st[5]++; return 0; }
    nb = lz_blocks(lz, (int)g->dpsm, g->dbp, g->dbw, g->dsax, g->dsay, g->rrw, g->rrh);
    for (k = 0; k < nb && same < 0; k++) {
        uint32_t o = lz->owner[lz->tmp[k]];
        if (o && lz_same(&lz->e[o - 1].g, g)) same = (int)o - 1;
    }
    /* partly overlapping entries are older bytes under this one: written first */
    lz->cause = 3;
    if (lz_write_blocks(gs, lz, nb, same, 1)) {
        if (same >= 0 && !lz->e[same].used) same = -1;   /* (written meanwhile by the renderer) */
        nb = lz_blocks(lz, (int)g->dpsm, g->dbp, g->dbw, g->dsax, g->dsay, g->rrw, g->rrh);
    }
    gen_rect(e, 1, (int)g->dpsm, g->dbp, g->dbw, g->dsax, g->dsay, g->rrw, g->rrh);
    if (same >= 0) {
        gs_lazy_ent *en = &lz->e[same];
        lz->st[2]++;
        if (en->hash != h || en->bytes != bytes) {
            uint8_t *nd = (uint8_t *)realloc(en->data, bytes);
            if (!nd) { lz_write(gs, lz, (uint32_t)same, 1); return 0; }
            en->data = nd;
            memcpy(en->data, d, bytes);
            en->bytes = bytes;
            en->hash = h;
        }
        en->bitblt = gs->reg[GS_BITBLTBUF]; en->trxpos = gs->reg[GS_TRXPOS]; en->trxreg = gs->reg[GS_TRXREG];
        lz->st[0]++;
        lz->st[3] += bytes;
        return 1;
    }
    if (lz->n >= LZ_MAX) return 0;
    for (i = lz->hint; lz->e[i].used; i = (i + 1) % LZ_MAX) {}
    lz->hint = (i + 1) % LZ_MAX;
    {
        gs_lazy_ent *en = &lz->e[i];
        en->data = (uint8_t *)malloc(bytes);
        if (!en->data) return 0;
        memcpy(en->data, d, bytes);
        en->used = 1;
        en->nmemo = 0;
        memset(en->memo, 0, sizeof en->memo);
        en->g = *g;
        en->bytes = bytes;
        en->hash = h;
        en->bitblt = gs->reg[GS_BITBLTBUF]; en->trxpos = gs->reg[GS_TRXPOS]; en->trxreg = gs->reg[GS_TRXREG];
        lz->n++;
        for (k = 0; k < nb; k++) {
            uint32_t b = lz->tmp[k];
            if (lz->owner[b]) continue;     /* (cannot happen: overlaps were written) */
            lz->owner[b] = (uint16_t)(i + 1);
            if (lz->pcnt[b >> 5]++ == 0) lz->any[b >> 10] |= 1u << ((b >> 5) & 31);
        }
    }
    lz->st[0]++;
    lz->st[3] += bytes;
    return 1;
}

/* a host->local transfer is about to be written for real (elide_commit): the
 * entries it overlaps are older bytes; the one with exactly its geometry is
 * dropped when the transfer arrives whole (whole = 1), all are written otherwise */
static void lz_before_write(gs_state *gs, const gs_mem_rect *r, int whole)
{
    gs_lazy *lz = (gs_lazy *)gs->xfer_lazy;
    uint32_t nb, k;
    int same = -1;
    if (!lz || !lz->n) return;
    nb = lz_blocks(lz, r->psm, r->bp, r->bw, r->x, r->y, r->w, r->h);
    if (whole) {
        xfer_geom g;
        memset(&g, 0, sizeof g);
        g.dbp = r->bp; g.dbw = r->bw; g.dpsm = (uint32_t)r->psm; g.dsax = r->x; g.dsay = r->y; g.rrw = r->w; g.rrh = r->h;
        for (k = 0; k < nb && same < 0; k++) {
            uint32_t o = lz->owner[lz->tmp[k]];
            if (o && lz_same(&lz->e[o - 1].g, &g)) same = (int)o - 1;
        }
    }
    lz->cause = 4;
    if (lz_write_blocks(gs, lz, nb, same, 1) && same >= 0)
        nb = lz_blocks(lz, r->psm, r->bp, r->bw, r->x, r->y, r->w, r->h);
    if (same >= 0 && lz->e[same].used) { lz_drop(lz, (uint32_t)same); lz->st[2]++; }
}

static void rb_push(gs_state *gs, uint8_t byte)
{
    if (gs->rb_len == gs->rb_cap) {
        uint32_t nc = gs->rb_cap ? gs->rb_cap * 2 : 4096;
        uint8_t *n = (uint8_t *)realloc(gs->rb, nc);
        if (!n) return;
        gs->rb = n; gs->rb_cap = nc;
    }
    gs->rb[gs->rb_len++] = byte;
}

static void xfer_local_to_local(gs_state *gs, const xfer_geom *g)
{
    /* DIR: 0 UL->LR, 1 LL->UR, 2 UR->LL, 3 LR->UL (order matters only for
     * overlapping rectangles). */
    int xrev = (g->dir == 2 || g->dir == 3), yrev = (g->dir == 1 || g->dir == 3);
    for (uint32_t j = 0; j < g->rrh; j++) {
        uint32_t yy = yrev ? g->rrh - 1 - j : j;
        for (uint32_t i = 0; i < g->rrw; i++) {
            uint32_t xx = xrev ? g->rrw - 1 - i : i;
            uint32_t v = gs_read_pixel(gs, (int)g->spsm, g->sbp, g->sbw,
                                       (g->ssax + xx) & 2047, (g->ssay + yy) & 2047);
            gs_write_pixel(gs, (int)g->dpsm, g->dbp, g->dbw,
                           (g->dsax + xx) & 2047, (g->dsay + yy) & 2047, v);
        }
    }
    gs->stats.xfer_l2l_px += (uint64_t)g->rrw * g->rrh;
}

static void xfer_local_to_host(gs_state *gs, const xfer_geom *g)
{
    int bpp = gs_psm_bpp((int)g->spsm);
    uint32_t nib_acc = 0, nib_n = 0;
    gs->rb_len = 0; gs->rb_off = 0;
    for (uint32_t j = 0; j < g->rrh; j++) {
        for (uint32_t i = 0; i < g->rrw; i++) {
            uint32_t v = gs_read_pixel(gs, (int)g->spsm, g->sbp, g->sbw,
                                       (g->ssax + i) & 2047, (g->ssay + j) & 2047);
            switch (bpp) {
            case 32: rb_push(gs, (uint8_t)v); rb_push(gs, (uint8_t)(v >> 8));
                     rb_push(gs, (uint8_t)(v >> 16)); rb_push(gs, (uint8_t)(v >> 24)); break;
            case 24: rb_push(gs, (uint8_t)v); rb_push(gs, (uint8_t)(v >> 8));
                     rb_push(gs, (uint8_t)(v >> 16)); break;
            case 16: rb_push(gs, (uint8_t)v); rb_push(gs, (uint8_t)(v >> 8)); break;
            case 8: rb_push(gs, (uint8_t)v); break;
            case 4:
                nib_acc |= (v & 15u) << (nib_n * 4);
                if (++nib_n == 2) { rb_push(gs, (uint8_t)nib_acc); nib_acc = 0; nib_n = 0; }
                break;
            default: break;
            }
        }
    }
    if (nib_n) rb_push(gs, (uint8_t)nib_acc);
    /* the FIFO hands out whole quadwords */
    while (gs->rb_len & 15u) rb_push(gs, 0);
    gs->stats.xfer_l2h_px += (uint64_t)g->rrw * g->rrh;
}

/* renderer hooks (gs.h gs_hooks): announce local-memory traffic */
static void hook_mem(gs_state *gs, int op, uint32_t bp, uint32_t bw, uint32_t psm,
                     uint32_t x, uint32_t y, uint32_t w, uint32_t h)
{
    gs_mem_rect r;
    if (!gs->hooks.mem) return;
    r.bp = bp; r.bw = bw; r.psm = (int)psm; r.x = x; r.y = y; r.w = w; r.h = h;
    gs->hooks.mem(gs->hooks.user, gs, op, &r);
}

/* End an announced host->local transfer (completed or abandoned). */
void gs_xfer_end_hook(gs_state *gs)
{
    gs_xfer_elide *e = (gs_xfer_elide *)gs->xfer_elide;
    int complete = gs->xfer_dir == 0 && gs->xfer_y >= gs->hooks.xfer_rect.h;
    if (e) e->pending = 0;   /* announced, no data: nothing was written */
    if (!gs->hooks.xfer_open) return;
    gs->hooks.xfer_open = 0;
    if (gs->hooks.mem)
        gs->hooks.mem(gs->hooks.user, gs, GS_MEM_WRITE_END, &gs->hooks.xfer_rect);
    if (e) elide_end(gs, e, complete);
}

void gs_xfer_start(gs_state *gs, int xdir)
{
    gs_xfer_stage_flush(gs);
    xfer_geom g;
    xfer_geom_get(gs, &g);
    gs_xfer_end_hook(gs);
    gs->xfer_x = gs->xfer_y = 0;
    gs->xfer_carry_n = 0;
    gs->xfer_dir = -1;
    if (gs__fx_on && xdir >= 0 && xdir <= 2) gs__fx_xfer(xdir, (int)(xdir == 1 ? g.spsm : g.dpsm));
    if (gs__feat_on && xdir >= 0 && xdir <= 2)
        gs__feat_xfer(xdir, (uint64_t)g.rrw * g.rrh * (uint64_t)gs_psm_bpp((int)(xdir == 1 ? g.spsm : g.dpsm)) / 8u,
                      g.dbp, g.dbw, (int)g.dpsm, g.dsay + g.rrh);
    switch (xdir) {
    case 0:
        gs->xfer_dir = 0;
        if (gs->hooks.mem && g.rrw && g.rrh) {
            gs_mem_rect *r = &gs->hooks.xfer_rect;
            gs_xfer_elide *e = gs->hooks.xfer_clean ? elide_get(gs) : NULL;
            r->bp = g.dbp; r->bw = g.dbw; r->psm = (int)g.dpsm;
            r->x = g.dsax; r->y = g.dsay; r->w = g.rrw; r->h = g.rrh;
            if (e && g_elide_host.on) {
                /* WRITE_BEGIN at the first data (elide_decide) */
                g_elide_host.seen++;
                e->pending = 1;
                e->cand = 0;
            } else {
                lz_before_write(gs, r, 0);
                if (e) elide_commit(gs, e);
                else {
                    gs->hooks.xfer_open = 1;
                    gs->hooks.mem(gs->hooks.user, gs, GS_MEM_WRITE_BEGIN, r);
                }
            }
        }
        break;
    case 1:
        gs_mem_materialize_rect(gs, (int)g.spsm, g.sbp, g.sbw, g.ssax, g.ssay, g.rrw, g.rrh);
        hook_mem(gs, GS_MEM_READ, g.sbp, g.sbw, g.spsm, g.ssax, g.ssay, g.rrw, g.rrh);
        xfer_local_to_host(gs, &g);
        break;
    case 2:
        gs_mem_materialize_rect(gs, (int)g.spsm, g.sbp, g.sbw, g.ssax, g.ssay, g.rrw, g.rrh);
        gs_mem_materialize_rect(gs, (int)g.dpsm, g.dbp, g.dbw, g.dsax, g.dsay, g.rrw, g.rrh);
        hook_mem(gs, GS_MEM_READ, g.sbp, g.sbw, g.spsm, g.ssax, g.ssay, g.rrw, g.rrh);
        if (gs->xfer_elide)
            gen_rect((gs_xfer_elide *)gs->xfer_elide, 1, (int)g.dpsm, g.dbp, g.dbw, g.dsax, g.dsay, g.rrw, g.rrh);
        hook_mem(gs, GS_MEM_WRITE_BEGIN, g.dbp, g.dbw, g.dpsm, g.dsax, g.dsay, g.rrw, g.rrh);
        xfer_local_to_local(gs, &g);
        hook_mem(gs, GS_MEM_WRITE_END, g.dbp, g.dbw, g.dpsm, g.dsax, g.dsay, g.rrw, g.rrh);
        break;
    default: break; /* 3: deactivated */
    }
}

GS_INLINE void xfer_put_pixel(gs_state *gs, const xfer_geom *g, uint32_t v)
{
    if (gs->xfer_y >= g->rrh) return; /* excess data is dropped */
    write_pixel_i(gs, (int)g->dpsm, g->dbp, g->dbw, (g->dsax + gs->xfer_x) & 2047,
                  (g->dsay + gs->xfer_y) & 2047, v);
    gs->stats.xfer_h2l_px++;
    if (++gs->xfer_x >= g->rrw) {
        gs->xfer_x = 0;
        gs->xfer_y++;
        if (gs->xfer_y >= g->rrh) gs_xfer_end_hook(gs);
    }
}

void gs_xfer_hwreg(gs_state *gs, uint64_t data)
{
    gs_xfer_stage_flush(gs);
    xfer_geom g;
    if (gs->xfer_dir != 0) return;
    xfer_geom_get(gs, &g);
    if (g.rrw == 0) return;
    if (gs->xfer_elide && ((gs_xfer_elide *)gs->xfer_elide)->pending) {
        lz_before_write(gs, &gs->hooks.xfer_rect, 0);
        elide_commit(gs, (gs_xfer_elide *)gs->xfer_elide);
    }
    int bpp = gs_psm_bpp((int)g.dpsm);
    uint8_t bytes[8];
    for (int i = 0; i < 8; i++) bytes[i] = (uint8_t)(data >> (8 * i));
    if (bpp == 4) {
        for (int i = 0; i < 8; i++) {
            xfer_put_pixel(gs, &g, bytes[i] & 15u);
            xfer_put_pixel(gs, &g, bytes[i] >> 4);
        }
        return;
    }
    if (bpp == 0) return;
    uint32_t bpx = (uint32_t)bpp / 8;
    for (int i = 0; i < 8; i++) {
        gs->xfer_carry[gs->xfer_carry_n++] = bytes[i];
        if (gs->xfer_carry_n == bpx) {
            uint32_t v = 0;
            for (uint32_t k = 0; k < bpx; k++) v |= (uint32_t)gs->xfer_carry[k] << (8 * k);
            gs->xfer_carry_n = 0;
            xfer_put_pixel(gs, &g, v);
        }
    }
}

/* ---------------------------------------------------------------------- */
/* Bulk host->local (IMAGE packets; docs/GPU.md "Performance", checkpoint 3)
 *
 * gs_xfer_image(gs, d, n) has exactly the effect of gs_xfer_hwreg on each of
 * the n/8 little-endian words of d in order (vram, xfer_x/y, carry, stats,
 * the end hook), with the per-pixel address split into a part of x and a
 * part of y.  For every PSM the address is
 *     ((bp + page(x,y)*32 + blk(x,y)) & 0x3FFF) << 8  |  low(x,y)
 * where page is a sum of an x and a y term, blk takes each of its bits from
 * x or from y only (the Z formats' "^ 24" flips one x-owned and one y-owned
 * bit) and low is an XOR of an x part and a y part (the 8/4-bit column
 * rotation flips an x-owned bit by a y-dependent amount).  So with
 *     X = addr(x, 0) (bp 0), Y = addr(0, y) (bp), O = addr(0, 0) (bp 0)
 *     addr(x, y) = (((Xblk + Yblk - Oblk) & 0x3FFF) << S) | (Xlow ^ Ylow ^ Olow)
 * (S = 8 bits of byte offset, 9 of nibble offset for PSMT4).  X is a table
 * per transfer (keyed by PSM, DSAX, RRW), Y one call per row.
 * tests/gs xfer_separable checks the identity for every PSM, x, y < 2048 and
 * several BP/BW; xfer_bulk compares the bulk path with gs_xfer_hwreg. */

typedef struct gs_xfer_cache {
    int ok;
    uint32_t psm, dsax, rrw;
    uint32_t o;                 /* addr(0, 0), bp 0 */
    uint32_t xt[4096];          /* addr(x_i, 0), bp 0, i < RRW */
} gs_xfer_cache;

/* address in S-bit-offset units (byte address, or nibble address for T4) */
GS_INLINE uint32_t sep_addr(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    if (psm == GS_PSMT4) return addr4n(bp, bw, x & 2047, y & 2047);
    return pixel_addr_i(psm, bp, bw, x, y, NULL);
}

static gs_xfer_cache *xfer_cache(gs_state *gs, const xfer_geom *g)
{
    gs_xfer_cache *c = (gs_xfer_cache *)gs->xfer_cache;
    if (!c) {
        c = (gs_xfer_cache *)calloc(1, sizeof *c);
        if (!c) return NULL;
        gs->xfer_cache = c;
    }
    if (c->ok && c->psm == g->dpsm && c->dsax == g->dsax && c->rrw == g->rrw) return c;
    int psm = (int)g->dpsm;
    c->o = sep_addr(psm, 0, 1, 0, 0);
    for (uint32_t i = 0; i < g->rrw; i++)
        c->xt[i] = sep_addr(psm, 0, 1, (g->dsax + i) & 2047, 0);
    c->psm = g->dpsm; c->dsax = g->dsax; c->rrw = g->rrw; c->ok = 1;
    return c;
}

void gs_xfer_cache_free(gs_state *gs)
{
    free(gs->xfer_cache);
    gs->xfer_cache = NULL;
    if (gs->xfer_elide) free(((gs_xfer_elide *)gs->xfer_elide)->stage);
    free(gs->xfer_elide);
    gs->xfer_elide = NULL;
}

/* one byte of a >= 8 bpp stream, as gs_xfer_hwreg does it */
GS_INLINE void xfer_byte(gs_state *gs, const xfer_geom *g, uint32_t bpx, uint8_t b)
{
    gs->xfer_carry[gs->xfer_carry_n++] = b;
    if (gs->xfer_carry_n == bpx) {
        uint32_t v = 0;
        for (uint32_t k = 0; k < bpx; k++) v |= (uint32_t)gs->xfer_carry[k] << (8 * k);
        gs->xfer_carry_n = 0;
        xfer_put_pixel(gs, g, v);
    }
}

/* pixels [xfer_x, xfer_x + cnt) of the current row from stream pixel k0 on */
static void xfer_row(gs_state *gs, const xfer_geom *g, const gs_xfer_cache *c,
                     const uint8_t *d, uint32_t k0, uint32_t cnt)
{
    int psm = (int)g->dpsm;
    uint32_t y = (g->dsay + gs->xfer_y) & 2047;
    uint32_t ya = sep_addr(psm, g->dbp, g->dbw, 0, y);
    const uint32_t *xt = c->xt + gs->xfer_x;
    uint8_t *m = gs->vram;
    if (gs->xfer_elide && ((const gs_xfer_elide *)gs->xfer_elide)->nowrite) return;   /* elided transfer */
    g_elide_host.row_px += cnt;
    g_elide_host.row_calls++;
    if (psm == GS_PSMT4) {
        uint32_t yb = (ya >> 9) - (c->o >> 9), yl = (ya ^ c->o) & 0x1FFu;
        /* branch-free nibble insert: the stream nibble k, the target nibble
         * of address na (bit 0 = high nibble) */
        for (uint32_t i = 0; i < cnt; i++) {
            uint32_t k = k0 + i;
            uint32_t v = ((uint32_t)d[k >> 1] >> ((k & 1) << 2)) & 15u;
            uint32_t na = (((yb + (xt[i] >> 9)) & 0x3FFFu) << 9) | ((yl ^ xt[i]) & 0x1FFu);
            uint32_t sh = (na & 1) << 2;
            uint8_t *p = m + (na >> 1);
            *p = (uint8_t)((*p & ~(15u << sh)) | (v << sh));
        }
        return;
    }
    uint32_t yb = (ya >> 8) - (c->o >> 8), yl = (ya ^ c->o) & 0xFFu;
#define XFER_A(i) ((((yb + (xt[i] >> 8)) & 0x3FFFu) << 8) | ((yl ^ xt[i]) & 0xFFu))
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32: {
        const uint8_t *s = d + 4 * k0;
        for (uint32_t i = 0; i < cnt; i++) memcpy(m + XFER_A(i), s + 4 * i, 4);
        break;
    }
    case GS_PSMCT24: case GS_PSMZ24: {
        const uint8_t *s = d + 3 * k0;
        for (uint32_t i = 0; i < cnt; i++) {
            uint8_t *p = m + XFER_A(i);
            p[0] = s[3 * i]; p[1] = s[3 * i + 1]; p[2] = s[3 * i + 2];
        }
        break;
    }
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: {
        const uint8_t *s = d + 2 * k0;
        for (uint32_t i = 0; i < cnt; i++) memcpy(m + XFER_A(i), s + 2 * i, 2);
        break;
    }
    case GS_PSMT8: {
        const uint8_t *s = d + k0;
        for (uint32_t i = 0; i < cnt; i++) m[XFER_A(i)] = s[i];
        break;
    }
    case GS_PSMT8H: {
        const uint8_t *s = d + k0;
        for (uint32_t i = 0; i < cnt; i++) m[XFER_A(i) + 3] = s[i];
        break;
    }
    case GS_PSMT4HL: case GS_PSMT4HH: {
        int hh = psm == GS_PSMT4HH;
        for (uint32_t i = 0; i < cnt; i++) {
            uint32_t k = k0 + i;
            uint32_t v = (k & 1) ? (uint32_t)(d[k >> 1] >> 4) : (uint32_t)(d[k >> 1] & 15u);
            uint8_t *p = m + XFER_A(i) + 3;
            if (hh) *p = (uint8_t)((*p & 0x0F) | (v << 4));
            else *p = (uint8_t)((*p & 0xF0) | v);
        }
        break;
    }
    default: break;
    }
#undef XFER_A
}

/* advance past cnt pixels of the current row (xfer_put_pixel's bookkeeping) */
GS_INLINE void xfer_advance(gs_state *gs, const xfer_geom *g, uint32_t cnt)
{
    gs->stats.xfer_h2l_px += cnt;
    gs->xfer_x += cnt;
    if (gs->xfer_x >= g->rrw) {
        gs->xfer_x = 0;
        gs->xfer_y++;
        if (gs->xfer_y >= g->rrh) gs_xfer_end_hook(gs);
    }
}


/* ---------------------------------------------------------------------- */
/* Block-wise host->local transfers (docs/NATIVE-RENDER.md "Texture uploads").
 * A transfer whose data arrives whole in one IMAGE run and whose rectangle is
 * aligned to the format's blocks (CT32 8x8, CT16 16x8, T8 16x16, T4 32x16) is
 * written block by block: every block is 256 contiguous bytes of local memory
 * (its base from the block's origin), and inside it the pixel layout is the
 * same for every block, so one table of in-block offsets per format replaces
 * the per-pixel address arithmetic.  The bytes written are exactly the
 * row path's (pixel_addr_i(x, y) = block base + offset(x mod bw, y mod bh); the
 * table is built from pixel_addr_i itself and RG_GS_XFER_CHECK=1 compares).
 * $RG_GS_FASTXFER=0 turns it off. */
typedef struct blk_tab {
    int ok;
    uint16_t off[512];           /* byte (T4: nibble) offset of pixel (x, y) in the block, y * bw + x */
} blk_tab;
static blk_tab g_blk[4];         /* CT32, CT16, T8, T4: constant tables (host state, ss_map.c) */

static int blk_dims(int psm, uint32_t *bw, uint32_t *bh, int *k)
{
    switch (psm) {
    case GS_PSMCT32: *bw = 8; *bh = 8; *k = 0; return 1;
    case GS_PSMCT16: *bw = 16; *bh = 8; *k = 1; return 1;
    case GS_PSMT8: *bw = 16; *bh = 16; *k = 2; return 1;
    case GS_PSMT4: *bw = 32; *bh = 16; *k = 3; return 1;
    default: return 0;
    }
}

static const blk_tab *blk_table(int psm, int k, uint32_t bw, uint32_t bh)
{
    blk_tab *t = &g_blk[k];
    if (!t->ok) {
        uint32_t base = psm == GS_PSMT4 ? addr4n(0, 1, 0, 0) : pixel_addr_i(psm, 0, 1, 0, 0, NULL);
        for (uint32_t y = 0; y < bh; y++)
            for (uint32_t x = 0; x < bw; x++) {
                uint32_t a = psm == GS_PSMT4 ? addr4n(0, 1, x, y) : pixel_addr_i(psm, 0, 1, x, y, NULL);
                t->off[y * bw + x] = (uint16_t)(a - base);
            }
        t->ok = 1;
    }
    return t;
}

/* 1: written (the transfer is complete; the caller does the bookkeeping) */
static int xfer_blocks(gs_state *gs, const xfer_geom *g, const uint8_t *d, uint32_t n)
{
    uint32_t bw, bh, bytes = xfer_bytes(g);
    int k, psm = (int)g->dpsm;
    if (fastxfer_on < 0) {
        const char *v = getenv("RG_GS_FASTXFER");
        fastxfer_on = !(v && v[0] == '0');
        v = getenv("RG_GS_XFER_CHECK");
        fastxfer_check = v && v[0] == '1';
    }
    if (!fastxfer_on || gs->xfer_x || gs->xfer_y || gs->xfer_carry_n || n < bytes || !blk_dims(psm, &bw, &bh, &k)) return 0;
    if ((g->dsax % bw) || (g->dsay % bh) || (g->rrw % bw) || (g->rrh % bh) || !g->rrw || !g->rrh ||
        g->dsax + g->rrw > 2048 || g->dsay + g->rrh > 2048)
        return 0;
    const blk_tab *t = blk_table(psm, k, bw, bh);
    uint8_t *m = gs->vram;
    uint32_t nbx = g->rrw / bw, nby = g->rrh / bh;
    for (uint32_t by = 0; by < nby; by++)
        for (uint32_t bx = 0; bx < nbx; bx++) {
            uint32_t x0 = g->dsax + bx * bw, y0 = g->dsay + by * bh;
            if (psm == GS_PSMT4) {
                uint32_t base = addr4n(g->dbp, g->dbw, x0, y0);        /* nibble address, even */
                uint8_t *blk = m + (base >> 1);
                for (uint32_t y = 0; y < bh; y++) {
                    uint32_t k0 = (by * bh + y) * g->rrw + bx * bw;   /* stream nibble */
                    const uint16_t *o = t->off + y * bw;
                    for (uint32_t x = 0; x < bw; x++) {
                        uint32_t kk = k0 + x;
                        uint32_t v = ((uint32_t)d[kk >> 1] >> ((kk & 1) << 2)) & 15u;
                        uint32_t na = o[x], sh = (na & 1) << 2;
                        uint8_t *p = blk + (na >> 1);
                        *p = (uint8_t)((*p & ~(15u << sh)) | (v << sh));
                    }
                }
                continue;
            }
            uint8_t *blk = m + pixel_addr_i(psm, g->dbp, g->dbw, x0, y0, NULL);
            for (uint32_t y = 0; y < bh; y++) {
                const uint16_t *o = t->off + y * bw;
                uint32_t k0 = (by * bh + y) * g->rrw + bx * bw;
                if (psm == GS_PSMT8) {
                    const uint8_t *src = d + k0;
                    for (uint32_t x = 0; x < bw; x++) blk[o[x]] = src[x];
                } else if (psm == GS_PSMCT16) {
                    const uint8_t *src = d + 2 * k0;
                    for (uint32_t x = 0; x < bw; x++) memcpy(blk + o[x], src + 2 * x, 2);
                } else {
                    const uint8_t *src = d + 4 * k0;
                    for (uint32_t x = 0; x < bw; x++) memcpy(blk + o[x], src + 4 * x, 4);
                }
            }
        }
    g_elide_host.fast++;
    g_elide_host.fast_bytes += bytes;
    if (fastxfer_check) {
        /* every pixel against the per-pixel address */
        uint32_t bad = 0;
        for (uint32_t y = 0; y < g->rrh && bad < 4; y++)
            for (uint32_t x = 0; x < g->rrw && bad < 4; x++) {
                uint32_t kk = y * g->rrw + x, v, w;
                int nib = 0;
                uint32_t a = pixel_addr_i(psm, g->dbp, g->dbw, g->dsax + x, g->dsay + y, &nib);
                if (psm == GS_PSMT4) { v = (d[kk >> 1] >> ((kk & 1) << 2)) & 15u; w = (m[a] >> (nib << 2)) & 15u; }
                else if (psm == GS_PSMT8) { v = d[kk]; w = m[a]; }
                else if (psm == GS_PSMCT16) { v = (uint32_t)d[2 * kk] | ((uint32_t)d[2 * kk + 1] << 8); w = (uint32_t)m[a] | ((uint32_t)m[a + 1] << 8); }
                else { memcpy(&v, d + 4 * kk, 4); memcpy(&w, m + a, 4); }
                if (v != w) {
                    bad++;
                    fprintf(stderr, "gs fastxfer: psm %d bp %u bw %u at %u,%u: pixel %u,%u wrote %x, per-pixel address holds %x\n", psm,
                            g->dbp, g->dbw, g->dsax, g->dsay, x, y, v, w);
                }
            }
    }
    return 1;
}

static void xfer_image_body(gs_state *gs, const xfer_geom *gp, int bpp, const uint8_t *d, uint32_t n);
static void xfer_image_now(gs_state *gs, const uint8_t *d, uint32_t n);
void gs_xfer_image(gs_state *gs, const uint8_t *d, uint32_t n)
{
    xfer_geom g;
    gs_xfer_elide *el = (gs_xfer_elide *)gs->xfer_elide;
    if (gs->xfer_dir != 0 || n == 0) return;
    if (el && (el->staging || el->pending) && fastxfer_on != 0) {
        xfer_geom_get(gs, &g);
        uint32_t bytes = xfer_bytes(&g);
        if (!el->staging && gs->xfer_x == 0 && gs->xfer_y == 0 && gs->xfer_carry_n == 0 && n < bytes &&
            bytes <= (8u << 20) && gs_psm_bpp((int)g.dpsm)) {
            el->staging = 1;
            el->stage_len = 0;
            g_elide_host.staged++;
        }
        if (el->staging) {
            if (el->stage_len + n > el->stage_cap) {
                uint32_t nc = el->stage_cap ? el->stage_cap : 65536u;
                while (nc < el->stage_len + n) nc *= 2;
                uint8_t *nb = (uint8_t *)realloc(el->stage, nc);
                if (!nb) { gs_xfer_stage_flush(gs); xfer_image_now(gs, d, n); return; }
                el->stage = nb;
                el->stage_cap = nc;
            }
            memcpy(el->stage + el->stage_len, d, n);
            el->stage_len += n;
            if (el->stage_len >= bytes) gs_xfer_stage_flush(gs);   /* whole: written now */
            return;
        }
    }
    xfer_image_now(gs, d, n);
}

/* the staged data goes through the normal path (whole, or what arrived when
 * the IMAGE run ended early / something else touches the transfer) */
void gs_xfer_stage_flush(gs_state *gs)
{
    gs_xfer_elide *el = (gs_xfer_elide *)gs->xfer_elide;
    if (!el || !el->staging) return;
    el->staging = 0;
    if (elide_log) {
        static int nlog;
        xfer_geom g;
        xfer_geom_get(gs, &g);
        if (nlog++ < 40)
            fprintf(stderr, "gs stage flush (path %d): %u of %u bytes, psm %u %ux%u at %u,%u bp %u\n", gs_stage_path, el->stage_len, xfer_bytes(&g),
                    g.dpsm, g.rrw, g.rrh, g.dsax, g.dsay, g.dbp);
    }
    if (el->stage_len) xfer_image_now(gs, el->stage, el->stage_len);
    el->stage_len = 0;
}

static void xfer_image_now(gs_state *gs, const uint8_t *d, uint32_t n)
{
    xfer_geom g;
    if (gs->xfer_dir != 0 || n == 0) return;
    xfer_geom_get(gs, &g);
    if (g.rrw == 0) return;
    int bpp = gs_psm_bpp((int)g.dpsm);
    if (bpp == 0) return;
    gs_xfer_elide *el = (gs_xfer_elide *)gs->xfer_elide;
    if (el && el->pending && elide_decide(gs, el, &g, d, n)) {
        /* elided: everything below runs without writing local memory */
        el->nowrite = 1;
        xfer_image_body(gs, &g, bpp, d, n);
        el->nowrite = 0;
        return;
    }
    xfer_image_body(gs, &g, bpp, d, n);
}

static void xfer_image_body(gs_state *gs, const xfer_geom *gp, int bpp, const uint8_t *d, uint32_t n)
{
    xfer_geom g = *gp;
    gs_xfer_elide *el = (gs_xfer_elide *)gs->xfer_elide;
    if (!(el && el->nowrite) && xfer_blocks(gs, &g, d, n)) {
        /* written block by block: the row path's bookkeeping for the whole
         * transfer, then the excess like the row path */
        uint32_t bytes = xfer_bytes(&g), px = g.rrw * g.rrh;
        gs->stats.xfer_h2l_px += px;
        gs->xfer_x = 0;
        gs->xfer_y = g.rrh;
        if (bpp != 4) memcpy(gs->xfer_carry, d + bytes - (uint32_t)bpp / 8, (uint32_t)bpp / 8);
        gs_xfer_end_hook(gs);
        if (bpp != 4)
            for (uint32_t pos = bytes; pos < n; pos++) xfer_byte(gs, &g, (uint32_t)bpp / 8, d[pos]);
        return;
    }
    /* a transfer whose x would leave the table (RRW > 4096 cannot occur: 12
     * bits) or that is already complete takes the per-word path */
    gs_xfer_cache *c = gs->xfer_y < g.rrh ? xfer_cache(gs, &g) : NULL;
    if (!c) {
        for (uint32_t o = 0; o + 8 <= n; o += 8) gs_xfer_hwreg(gs, gs_rd64(d + o));
        return;
    }
    if (bpp == 4) {
        /* two pixels per byte, low nibble first; nothing is carried */
        uint32_t npx = 2 * n, k = 0;
        while (k < npx && gs->xfer_y < g.rrh) {
            uint32_t cnt = g.rrw - gs->xfer_x;
            if (cnt > npx - k) cnt = npx - k;
            xfer_row(gs, &g, c, d, k, cnt);
            k += cnt;
            xfer_advance(gs, &g, cnt);
        }
        return; /* the rest is dropped (xfer_put_pixel) */
    }
    uint32_t bpx = (uint32_t)bpp / 8, pos = 0;
    while (gs->xfer_carry_n && pos < n) xfer_byte(gs, &g, bpx, d[pos++]);
    uint32_t pos0 = pos;
    while (gs->xfer_y < g.rrh && n - pos >= bpx) {
        uint32_t cnt = g.rrw - gs->xfer_x, avail = (n - pos) / bpx;
        if (cnt > avail) cnt = avail;
        xfer_row(gs, &g, c, d + pos, 0, cnt);
        pos += cnt * bpx;
        xfer_advance(gs, &g, cnt);
    }
    /* the carry bytes hold the last whole pixel, as byte by byte (only the
     * first xfer_carry_n are ever read; a recording snapshot saves all 8) */
    if (pos > pos0) memcpy(gs->xfer_carry, d + pos - bpx, bpx);
    /* a partial pixel, or data past the end: byte by byte as before */
    while (pos < n) xfer_byte(gs, &g, bpx, d[pos++]);
}

/* The bits of local memory that the first npx pixels (raster order) of a
 * host->local transfer into (psm, bp, bw, x0, y0, w, h) write, OR-ed into
 * mask[GS_VRAM_BYTES]: exactly what gs_write_pixel touches (24-bit formats
 * keep byte 3, T8H/T4HL/T4HH only their byte/nibble of byte 3, T4 one
 * nibble).  The GPU renderer merges a transfer into its local-memory copy
 * with it (docs/GPU.md "Performance", checkpoint 3). */
void gs_xfer_mask(int psm, uint32_t bp, uint32_t bw, uint32_t x0, uint32_t y0,
                  uint32_t w, uint32_t h, uint32_t npx, uint8_t *mask)
{
    static uint32_t xt[4096];
    if (gs_psm_bpp(psm) == 0 || w == 0 || w > 4096) return;
    if ((uint64_t)npx > (uint64_t)w * h) npx = w * h;
    uint32_t o = sep_addr(psm, 0, 1, 0, 0);
    for (uint32_t i = 0; i < w; i++) xt[i] = sep_addr(psm, 0, 1, (x0 + i) & 2047, 0);
    for (uint32_t j = 0; npx && j < h; j++) {
        uint32_t cnt = npx < w ? npx : w;
        npx -= cnt;
        uint32_t ya = sep_addr(psm, bp, bw, 0, (y0 + j) & 2047);
        if (psm == GS_PSMT4) {
            uint32_t yb = (ya >> 9) - (o >> 9), yl = (ya ^ o) & 0x1FFu;
            for (uint32_t i = 0; i < cnt; i++) {
                uint32_t na = (((yb + (xt[i] >> 9)) & 0x3FFFu) << 9) | ((yl ^ xt[i]) & 0x1FFu);
                mask[na >> 1] |= (uint8_t)(15u << ((na & 1) << 2));
            }
            continue;
        }
        uint32_t yb = (ya >> 8) - (o >> 8), yl = (ya ^ o) & 0xFFu;
        for (uint32_t i = 0; i < cnt; i++) {
            uint8_t *p = mask + ((((yb + (xt[i] >> 8)) & 0x3FFFu) << 8) | ((yl ^ xt[i]) & 0xFFu));
            switch (psm) {
            case GS_PSMCT32: case GS_PSMZ32: p[0] = p[1] = p[2] = p[3] = 0xFF; break;
            case GS_PSMCT24: case GS_PSMZ24: p[0] = p[1] = p[2] = 0xFF; break;
            case GS_PSMT8: p[0] = 0xFF; break;
            case GS_PSMT8H: p[3] = 0xFF; break;
            case GS_PSMT4HL: p[3] |= 0x0F; break;
            case GS_PSMT4HH: p[3] |= 0xF0; break;
            default: p[0] = p[1] = 0xFF; break;   /* 16-bit */
            }
        }
    }
}

uint32_t gs_fifo_pending(const gs_state *gs)
{
    return gs->rb_len - gs->rb_off;
}

void gs_census_fifo(void);
uint32_t gs_read_fifo(gs_state *gs, void *dst, uint32_t bytes)
{
    gs_async_drain(gs);
    gs_census_fifo();
    if (gs->rec) gs->rec(gs->rec_user, GS_REC_FIFO_READ, bytes, 0, NULL, 0);
    uint32_t n = gs->rb_len - gs->rb_off;
    if (n > bytes) n = bytes;
    memcpy(dst, gs->rb + gs->rb_off, n);
    gs->rb_off += n;
    return n;
}
