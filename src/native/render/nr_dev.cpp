/* SPDX-License-Identifier: CC0-1.0 */
/* The native renderer's device (docs/NATIVE-RENDER.md "Checkpoint 10"): render targets, the
 * decoded-texture cache, native mesh and immediate draws, CLUT loads, transfers and the display
 * on the GPU, driven by the native state block (nr_gs.h).  RG_NATIVE_ONLY only: what rg_gpu's
 * gpu_core.cpp is for the oracle twin, without the GS model behind it.  Local memory is the
 * GPU's alone (the mirror): no CPU copy, no page coherence with one, no GS-exact draw path.
 * The graphics API lives behind GpuBackend (src/gpu/gpu_internal.h; nr_d3d11.cpp). */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <chrono>
#include <map>
#include <unordered_map>
#include <tuple>
#include <vector>

#include "gpu_internal.h"
#include "nr_gs.h"
#include "nr_gsmem.h"
#include "nr_interp.h"

#define gs_pixel_addr nr_px_addr
#define gs_psm_bpp nr_psm_bpp

#define BITS(v, lo, n) ((uint32_t)(((uint64_t)(v) >> (lo)) & ((1ull << (n)) - 1ull)))

/* ------------------------------------------------------------ page sets */
/* Local memory = 512 pages of 8 KB.  Coherence is tracked per page. */
struct Pages {
    uint32_t w[16];
    void clear() { memset(w, 0, sizeof w); }
    void all() { memset(w, 0xFF, sizeof w); }
    void set(uint32_t p) { p &= 511; w[p >> 5] |= 1u << (p & 31); }
    bool get(uint32_t p) const { p &= 511; return (w[p >> 5] >> (p & 31)) & 1; }
    bool any() const { for (int i = 0; i < 16; i++) if (w[i]) return true; return false; }
    bool overlaps(const Pages &o) const
    {
        for (int i = 0; i < 16; i++) if (w[i] & o.w[i]) return true;
        return false;
    }
    void add(const Pages &o) { for (int i = 0; i < 16; i++) w[i] |= o.w[i]; }
    void sub(const Pages &o) { for (int i = 0; i < 16; i++) w[i] &= ~o.w[i]; }
    Pages and_(const Pages &o) const { Pages r; for (int i = 0; i < 16; i++) r.w[i] = w[i] & o.w[i]; return r; }
};

static int psm_is16(int psm)
{
    return psm == GS_PSMCT16 || psm == GS_PSMCT16S || psm == GS_PSMZ16 || psm == GS_PSMZ16S;
}

/* page geometry: width/height of a page in pixels, pages per buffer row */
static void page_geom(int psm, uint32_t bw, int *pw, int *ph, uint32_t *bwp)
{
    switch (psm) {
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S:
        *pw = 64; *ph = 64; *bwp = bw; break;
    case GS_PSMT8: *pw = 128; *ph = 64; *bwp = bw >> 1; break;
    case GS_PSMT4: *pw = 128; *ph = 128; *bwp = bw >> 1; break;
    default: *pw = 64; *ph = 32; *bwp = bw; break;
    }
}

/* Pages touched by the rectangle [x0,x1) x [y0,y1) of buffer (bp, bw, psm).
 * Exact at page granularity (a non-page-aligned bp spills into the next
 * page, which is included). */
static Pages pages_of(uint32_t bp, uint32_t bw, int psm, int x0, int y0, int x1, int y1)
{
    Pages p;
    p.clear();
    if (x1 <= x0 || y1 <= y0) return p;
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > 2048) x1 = 2048;
    if (y1 > 2048) y1 = 2048;
    int pw, ph;
    uint32_t bwp;
    page_geom(psm, bw, &pw, &ph, &bwp);
    uint32_t base = bp >> 5;
    int spill = (bp & 31) != 0;
    if (spill) {
        /* A buffer that does not start on a page: the pages of the blocks
         * the rectangle covers, exactly (each block lies in one page).  The
         * page-grid estimate below adds the next page of every page, which
         * made the game's CLUT loads (16x16 at odd blocks next to a drawn
         * buffer) read back a page the GPU had drawn, once per frame
         * (docs/GPU.md "Checkpoint 4"). */
        int bwk = 0, bhk = 0;
        switch (psm) {
        case GS_PSMCT32: case GS_PSMCT24: case GS_PSMZ32: case GS_PSMZ24:
        case GS_PSMT8H: case GS_PSMT4HL: case GS_PSMT4HH: bwk = 8; bhk = 8; break;
        case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: bwk = 16; bhk = 8; break;
        case GS_PSMT8: bwk = 16; bhk = 16; break;
        case GS_PSMT4: bwk = 32; bhk = 16; break;
        default: break;
        }
        if (bwk && (int64_t)((x1 - 1) / bwk - x0 / bwk + 1) * ((y1 - 1) / bhk - y0 / bhk + 1) <= 4096) {
            for (int by = y0 / bhk; by <= (y1 - 1) / bhk; by++)
                for (int bx = x0 / bwk; bx <= (x1 - 1) / bwk; bx++)
                    p.set(gs_pixel_addr(psm, bp, bw, (uint32_t)(bx * bwk), (uint32_t)(by * bhk), NULL) >> 13);
            return p;
        }
    }
    for (int r = y0 / ph; r <= (y1 - 1) / ph; r++)
        for (int c = x0 / pw; c <= (x1 - 1) / pw; c++) {
            uint32_t pg = base + (uint32_t)c + (uint32_t)r * bwp;
            p.set(pg);
            if (spill) p.set(pg + 1);
        }
    return p;
}

static Pages pages_of_rect(const gs_mem_rect *r)
{
    return pages_of(r->bp, r->bw, r->psm, (int)r->x, (int)r->y, (int)(r->x + r->w),
                    (int)(r->y + r->h));
}

/* ------------------------------------------------------------- targets */
struct Rt {
    int id;            /* backend id */
    int depth;
    uint32_t bp, bw;
    int psm;
    int w, h;          /* native: w = bw*64, h = rows owned (multiple of page height) */
    int h_alloc;
    Pages pages;
    int has_dirty;
    GpuRect dirty;     /* newer than the mirror */
    int stale;         /* the mirror is newer than the target */
    Pages stale_pages; /* ... in these pages (the rest still current: rt_copy_pages) */
};

/* ------------------------------------------------------- batched state */
/* The registers that shape a draw.  A primitive whose key differs from the
 * pending batch's flushes it. */
struct Key {
    uint64_t attr;      /* PRIM/PRMODE attribute bits (IIP excluded) */
    uint64_t frame, zbuf, test, alpha, fba, pabe, colclamp, dthe, dimx, fogcol,
        scanmsk, scissor, tex0, tex1, clamp, miptbp1, miptbp2, texa;
    uint64_t clut_gen;
};

struct Derived {
    int ctx;
    int tme, fge, abe, fst, iip;
    uint32_t fbp, fbw, fbmsk; int fpsm;
    uint32_t zbp; int zpsm, zmsk;
    int zte, ztst;
    int ate, atst, afail, date, datm;
    int need_dst, merge, need_depth;
    uint32_t cmask_base;
    int scx0, scy0, scx1, scy1;  /* half-open native */
    int skip;                   /* nothing can be written */
    int serial;                 /* primitives may not overlap within a batch */
    int hbyte_tex;              /* the texture reads only bits 24-31 of each word
                                   (T8H, T4HL, T4HH) */
    int rov;                    /* ordered blending: one draw through the colour
                                   target's rasterizer-ordered view */
    GpuDrawCB cb;
    GpuZFunc zfunc;
    GpuPass pass[2];
    int npass;
    /* texture pages */
    Pages tex_pages;     /* every page any primitive of this state can sample */
    int indexed;
    int tex_lvl0;        /* only mip level 0 can be sampled */
    /* feedback: the texture can alias memory this state draws into (the
     * colour buffer, or the Z buffer when Z is written) */
    int feedback;
    int zwrite_any;
    int fb_feedback, zb_feedback;   /* FRAME / ZBUF pages are in the write set */
    /* direct sampling of a live render target (docs/GPU.md "Direct sampling") */
    uint32_t tbp, tbw;
    int tpsm;
    int direct_ok;       /* the texture format can be read from a target */
    GpuRect tex_wrap;    /* level-0 texels the wrap mode can reach */
    /* FRAME and ZBUF share pages inside the scissor: the reference interleaves
     * colour and Z writes per pixel, so the software rasterizer draws */
    int alias;
};

/* A small region the CPU reads back every frame (GfxEndFrame's 8x8 Z read):
 * its pages are copied to a staging slot right after the last batch that
 * writes them, so the read waits only for that copy, not for the rest of
 * the frame queued behind it (docs/GPU.md "Checkpoint 4"). */
struct HotRead {
    int used;
    gs_mem_rect rc;
    Pages pages;
    int state;          /* 0: no copy; 1: copy valid in `slot`; 2: written since */
    int slot;
    uint64_t last;      /* LRU */
};

/* Probe lag (real-time play only, docs/NATIVE-THREADS.md "3h"): the copy of a depth probe's
 * page neighbourhood taken at one probe group, served to the next group's probes, so the read
 * maps a copy the GPU finished a frame ago instead of waiting for the frame being drawn. */
struct LagRead {
    int used;
    Pages pages;
    int slot;
    uint64_t serial;    /* the slot's copy serial when taken (a newer copy reused the slot) */
    uint64_t gen;       /* the write generation it was taken at (lag_gen) */
};

/* A transfer the device keeps the words of (small ones: palettes and other CPU-known data,
 * docs/NATIVE-RENDER.md "Checkpoint 10"): the CLUT loads that read only blocks it was the last
 * write of take the cells from here instead of the GPU */
/* The words of the blocks small CT32 / CT16 transfers (palettes, docs/NATIVE-RENDER.md
 * "Checkpoint 10") were the last write of: CLUT loads that read only such blocks take the cells
 * from here instead of the GPU.  Valid while the block's epoch is the one it was kept at. */
struct KBlk { uint32_t epoch; uint32_t d[64], m[64]; };
/* A kept transfer as it came (checkpoint 12: the words are made only when a CLUT load reads one
 * of its blocks, or when its slot is reused while a block still holds it): the title movie
 * sends 16x16 CT32 macroblocks, 1 KB each like a 256-colour palette, ~400 per field, and the
 * eager per-block words cost ~1.2 ms per field of worker time ($RG_NR_KEEP_EAGER=1: eager) */
struct KXfer { uint32_t epoch; gs_mem_rect rc; uint32_t npx; uint16_t nb; uint16_t blk[16]; uint8_t data[1024]; };
enum { KX_N = 4096 };
/* the last transfer into a rectangle (redundant upload elision): same rectangle, same bytes,
 * and none of its blocks written since: local memory already holds exactly those bytes */
struct Elide {
    uint32_t key[7];
    uint64_t hash;
    uint32_t epoch;
    std::vector<uint16_t> blocks;
    int used;
};

struct gpu_renderer {
    gpu_config cfg;
    int scale;
    GpuBackend *be;
    gpu_gs *gs;
    gpu_stats stats;
    std::vector<Rt> rts;
    /* Pages a GPU draw wrote since their last host->local upload (item 8, BRINGUP.md): a
     * texture there is a render result (post pass, CLUT trick) and keeps the GS filter;
     * a texture uploaded after the draw is ordinary even while a target spans its pages
     * (short-lived targets inside the character texture pool) */
    Pages drawn;
    int texrt_overlap;   /* $RG_NR_TEXRT=overlap: the old rule (any live target in the pages) */
    int no_rt_pagecopy;  /* $RG_GPU_RT_PAGECOPY=0: evicted targets reach a new one only through the 1x mirror */
    FILE *filt_log;      /* measurement: $RG_NR_FILTLOG (per native draw: filter choice and why) */
    int rov;                    /* the backend draws through ordered views */
    int zrov;                   /* ... and tests depth in the shader (any depth test with rov) */
    uint64_t clut_uploaded_gen;
    int clut_valid;
    /* CLUT generations follow the CLUT's contents, not its loads: the game
     * reloads an unchanged palette before every few sprites (TEX0.CLD), and
     * a new generation would end the batch (docs/GPU.md "Performance") */
    uint64_t clut_seen_loads;  /* gs->stats.clut_loads last compared */
    uint64_t clut_gen_id;      /* generation of clut_copy */
    uint16_t clut_copy[512];   /* the CLUT of generation clut_gen_id */
    /* GPU-side CLUT loads: the CLUT words whose cells the last load into them made on the GPU
     * (the CLUT buffer is newer than gs->clut / clut_copy there) */
    uint8_t clut_own[256];
    int clut_own_any;
    int clut_force;            /* a CPU load since: next key is a new generation */
    int no_cpu_clut;           /* $RG_NR_CPUCLUT=0: every CLUT load on the GPU */
    uint64_t clut_cpu, clut_gpu_n, clut_dry_gpu;
    /* mirror write stamps per page (decoded-texture cache keys, docs/GPU.md
     * "Performance"): the stamp of the last upload or write-back into it */
    uint32_t page_stamp[512];
    uint32_t stamp;
    /* Block bookkeeping of the mirror (256-byte blocks), checkpoint 10: the epoch of the last
     * write of each block (transfers, target write-backs, copies), the transfer that made it
     * (0: a GPU write or a transfer whose words are not kept), and a content key (transfers:
     * the transfer's bytes and geometry; GPU writes: unique) for the decoded-texture keys */
    uint32_t blk_epoch[16384];
    uint32_t blk_owner[16384];           /* (1: the block's words are kept: kblk) */
    uint32_t blk_key[16384];
    uint32_t epoch;
    KBlk *kblk[16384];                   /* (allocated on first use, reused) */
    std::vector<KXfer> kx;               /* kept transfers not made into words yet (ring of KX_N) */
    uint32_t kx_next;
    uint16_t blk_kx[16384];              /* the block's kept transfer: slot + 1 (0 none) */
    uint64_t kx_made, kx_evict_made;
    int keep_eager;
    double x_us_px, x_us_up;
    uint64_t x_flushes, x_batch_fail;
    std::vector<uint8_t> xb;            /* the pending transfers' bytes (CS_xfer batch) */
    std::vector<uint32_t> xd;           /* ... their descriptors */
    uint32_t xb_ndesc, xb_bytes, xb_px;
    double x_t[5];
    std::vector<Elide> elide;            /* by rectangle hash */
    std::vector<uint32_t> dm;            /* (data, mask) per mirror word of the transfers not uploaded yet */
    std::vector<uint16_t> pend;          /* their blocks (mem_flush uploads them before the mirror is read) */
    std::vector<uint8_t> pend_on;
    uint64_t x_n, x_bytes, x_elided, x_elided_bytes, x_kept, x_merge_words, l2l_n, l2h_n;
    double x_us;
    int no_elide;              /* $RG_GPU_NO_ELIDE=1: every transfer written */
    double kick_px;        /* target pixels drawn since the last kick */
    double kick_at;        /* kick every this many (0: never; $RG_GPU_KICK_PX) */
    FILE *trace;           /* measurement: $RG_GPU_TRACE (draws, memory ops, displays) */
    FILE *rt_log;          /* measurement: $RG_GPU_RT_LOG (target creates / drops, displays) */
    HotRead hot[4];        /* early-copied read-back regions */
    uint64_t hot_tick;
    int probe_lag;         /* gpu_config.probe_lag / $RG_GPU_PROBE_LAG: depth probes a group late */
    LagRead lag[8];
    uint64_t snap_serial;  /* early copies taken; per slot, the serial of the copy it holds */
    uint64_t snap_slot_serial[GpuBackend::SNAP_SLOTS];
    uint64_t lag_hits, lag_misses, lag_copies;
    uint64_t lag_cur, lag_prev;   /* the current and the previous probe group (lag_gen) */
    int no_early;          /* $RG_GPU_NO_EARLY_READ=1: read back at the read only */
    char name[128];
    gpu_enhance enh;       /* renderer enhancements (docs/GPU.md "Graphics settings") */
    /* native draws (docs/NATIVE-RENDER.md): the marker handler and counters */
    gpu_native_fn nat_fn;
    void *nat_user;
    gpu_nr_stats nrs;
    /* content key per page for the native texture cache (from blk_key), cached by stamp */
    uint32_t page_hash[512];
    uint32_t page_hash_stamp[512];
    uint64_t nr_clut_hash_gen;
    uint32_t nr_clut_hash;
    const uint64_t *disp_preg; /* gpu_set_display_regs: PCRTC register snapshot (NULL: nr_hw's) */
    uint32_t nr_last_key[8];   /* the last native draw's decoded-texture key (gpu_nr_last_texkey) */
    const uint32_t *im_runs;   /* gpu_nr_im_submit_swap: the runs of the draw being made */
    int im_nruns;
    int im_crov;               /* gpu_nr_im_submit: the draw goes through the colour target's ordered view */
    int im_xfree;              /* gpu_set_im_xfree: squeezed 2D, sprites not snapped in X when upscaled */
    /* $RG_NR_IMFB_CENSUS=1: approximated immediate states by (reason, FRAME, TEX0), primitives */
    int fb_census;
    std::map<std::tuple<int, uint64_t, uint64_t>, uint64_t> fbc;
    int no_gslin;              /* $RG_NR_GSLIN=0: immediate bilinear by the hardware sampler */
    int no_fbrect;             /* $RG_NR_FBRECT=0: texture feedback decided on whole pages (checkpoint 8) */
    int no_asat;               /* $RG_NR_ASAT=0: blend factor As > 0x80 saturated by the dual-source blend */
    uint64_t im_asat_prims, im_asat_tex_prims;
    uint64_t im_crov_prims;
    uint64_t im_approx[12];    /* immediate primitives drawn natively where the oracle's GS draw path drew (why) */
    uint64_t im_fb_split;      /* texture-feedback primitives drawn one by one */
    /* replay (gpu_nr_replay_*): offscreen colour / depth pair */
    int rp_c, rp_z, rp_w, rp_h;
    std::vector<uint32_t> rp_buf;
};

static int rect_overlap(const GpuRect &a, const GpuRect &b)
{
    return a.x0 < b.x1 && b.x0 < a.x1 && a.y0 < b.y1 && b.y0 < a.y1;
}
static void rect_union(GpuRect &a, const GpuRect &b)
{
    if (b.x0 < a.x0) a.x0 = b.x0;
    if (b.y0 < a.y0) a.y0 = b.y0;
    if (b.x1 > a.x1) a.x1 = b.x1;
    if (b.y1 > a.y1) a.y1 = b.y1;
}

/* CPU-side wait accounting (gpu_stats.download_us / kick_us) */
static double now_us()
{
    return std::chrono::duration<double, std::micro>(
        std::chrono::steady_clock::now().time_since_epoch()).count();
}

/* ================================================== mirror coherence */
/* the mirror changed on pages p (decoded textures of them are stale) */
static void stamp_pages(gpu_renderer *r, const Pages &p)
{
    r->stamp++;
    for (int i = 0; i < 16; i++)
        for (uint32_t m = p.w[i]; m; m &= m - 1) {
            int b = 0;
            while (!((m >> b) & 1u)) b++;
            r->page_stamp[i * 32 + b] = r->stamp;
        }
}


/* ---- block geometry: a block is 256 contiguous bytes in every format; its size in pixels */
static int blk_dims(int psm, int *bwk, int *bhk)
{
    switch (psm) {
    case GS_PSMCT32: case GS_PSMCT24: case GS_PSMZ32: case GS_PSMZ24:
    case GS_PSMT8H: case GS_PSMT4HL: case GS_PSMT4HH: *bwk = 8; *bhk = 8; return 1;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: *bwk = 16; *bhk = 8; return 1;
    case GS_PSMT8: *bwk = 16; *bhk = 16; return 1;
    case GS_PSMT4: *bwk = 32; *bhk = 16; return 1;
    default: return 0;
    }
}


/* ---- block bookkeeping (checkpoint 10: no CPU copy; who wrote each block last) ---- */
static inline void blk_release(gpu_renderer *r, uint32_t b) { r->blk_owner[b] = 0; }
static inline uint32_t mix32(uint32_t h, uint32_t v) { return (h ^ v) * 16777619u; }
/* a GPU write (target write-back, local->local copy) of rectangle d of buffer (bp, bw, psm):
 * every block it touches gets a new epoch, no kept transfer, a unique content key */
static void blk_write_gpu(gpu_renderer *r, uint32_t bp, uint32_t bw, int psm, GpuRect d)
{
    int bwk, bhk;
    if (d.x0 < 0) d.x0 = 0;
    if (d.y0 < 0) d.y0 = 0;
    if (d.x1 > 2048) d.x1 = 2048;
    if (d.y1 > 2048) d.y1 = 2048;
    if (d.x1 <= d.x0 || d.y1 <= d.y0) return;
    uint32_t e = ++r->epoch;
    if (!blk_dims(psm, &bwk, &bhk)) bwk = bhk = 8;
    if (bw == 0) bw = 1;
    for (int by = d.y0 / bhk; by <= (d.y1 - 1) / bhk; by++)
        for (int bx = d.x0 / bwk; bx <= (d.x1 - 1) / bwk; bx++) {
            uint32_t b = (gs_pixel_addr(psm, bp, bw, (uint32_t)(bx * bwk), (uint32_t)(by * bhk), NULL) >> 8) & 16383u;
            blk_release(r, b);
            r->blk_epoch[b] = e;
            r->blk_key[b] = mix32(mix32(0x9E3779B9u, e), b) | 1u;
        }
}

/* A texture reading pages tp is ordinary (the texture-filter enhancement applies) unless a
 * live render target spans pages of it that a GPU draw wrote since their last upload
 * (item 8, docs/BRINGUP.md): page overlap alone also caught character textures uploaded
 * into a pool slot after a short-lived target there had drawn ($RG_NR_TEXRT=overlap: that
 * old rule).  why: the deciding target, if any. */
static int tex_pages_ordinary(const gpu_renderer *r, const Pages &tp, const Rt **why)
{
    if (why) *why = NULL;
    for (const Rt &t : r->rts) {
        if (!t.pages.overlaps(tp)) continue;
        if (r->texrt_overlap || t.pages.and_(tp).overlaps(r->drawn)) {
            if (why) *why = &t;
            return 0;
        }
    }
    return 1;
}

static void hot_cpu_write(gpu_renderer *r, const Pages &p);
static void mem_flush(gpu_renderer *r);
static void rt_writeback(gpu_renderer *r, Rt &t)
{
    if (!t.has_dirty) return;
    GpuRect d = t.dirty;
    if (d.x1 > t.w) d.x1 = t.w;
    if (d.y1 > t.h) d.y1 = t.h;
    if (d.x1 > d.x0 && d.y1 > d.y0) {
        mem_flush(r);
        r->be->rt_writeback(t.id, t.bp, t.bw, t.psm, d);
        blk_write_gpu(r, t.bp, t.bw, t.psm, d);
        Pages wp = pages_of(t.bp, t.bw, t.psm, d.x0, d.y0, d.x1, d.y1);
        stamp_pages(r, wp);
        r->stats.rt_writebacks++;
    }
    t.has_dirty = 0;
}

static void rt_load_rows(gpu_renderer *r, Rt &t, int y0, int y1)
{
    if (y1 <= y0) return;
    GpuRect rc = { 0, y0, t.w, y1 };
    mem_flush(r);
    r->be->rt_load(t.id, t.bp, t.bw, t.psm, rc);
    r->stats.rt_loads++;
}

static void rt_drop(gpu_renderer *r, size_t i)
{
    if (r->rt_log) {
        const Rt &t = r->rts[i];
        fprintf(r->rt_log, "X %d bp %u bw %u psm %02x h %d dirty %d\n", t.depth, t.bp, t.bw, t.psm, t.h, t.has_dirty);
    }
    rt_writeback(r, r->rts[i]);
    r->be->rt_destroy(r->rts[i].id);
    r->rts.erase(r->rts.begin() + (long)i);
    r->stats.rt_drops++;
}







static volatile uint32_t g_filt_frame;   /* $RG_NR_FILTLOG: EE frame (gpu_nr_filtlog_frame) */
extern "C" void gpu_nr_filtlog_frame(uint32_t frame) { g_filt_frame = frame; }
static void clut_resolve(gpu_renderer *r);

/* the mirror is written (a transfer, a copy): early copies of those pages are void */
static void hot_cpu_write(gpu_renderer *r, const Pages &p)
{
    for (HotRead &h : r->hot)
        if (h.used && h.pages.overlaps(p)) h.state = 0;
}



/* ====================================================== render targets */
static int page_h(int psm) { return psm_is16(psm) ? 64 : 32; }

/* o holds the same pixels as a target (depth, bp, psm) would in the pages they share, page
 * for page: same kind and format, page-aligned bases (any widths); its stale pages are not
 * copied */
static int rt_page_compatible(const gpu_renderer *r, const Rt &o, int depth, uint32_t bp, int psm)
{
    return !r->no_rt_pagecopy && o.depth == depth && o.psm == psm && o.h > 0 && (o.bp & 31) == 0 &&
           (bp & 31) == 0 && (psm == GS_PSMCT32 || psm == GS_PSMCT24 || psm_is16(psm) || psm == GS_PSMZ32 ||
                              psm == GS_PSMZ24);
}

/* t holds current texels in pages rp: not stale there (a CPU write into another page of a
 * stale target leaves these as drawn; item 8: the game uploads textures into the top rows
 * of the view it composites characters from, and the next composite pass read the 1x mirror) */
static int rt_current_in(const gpu_renderer *r, const Rt &t, const Pages &rp)
{
    if (!t.stale) return 1;
    if (r->no_rt_pagecopy) return 0;
    return !t.stale_pages.overlaps(rp);
}

/* the pixel origin of page pg in target t (pg inside t's pages) */
static void rt_page_xy(const Rt &t, uint32_t pg, int *x, int *y)
{
    int pw, ph;
    uint32_t bwp;
    page_geom(t.psm, t.bw, &pw, &ph, &bwp);
    if (bwp == 0) bwp = 1;
    uint32_t i = (pg - t.bp / 32u) & 511u;   /* (local memory wraps) */
    *x = (int)(i % bwp) * pw;
    *y = (int)(i / bwp) * ph;
}

/* t is stale: load its stale pages among rows [0, h) from the mirror (runs of pages in a
 * row as one load).  0: not page-aligned, the caller loads every row. */
static int rt_load_stale_pages(gpu_renderer *r, Rt &t, int h)
{
    if (t.bp & 31) return 0;
    int pw, ph;
    uint32_t bwp;
    page_geom(t.psm, t.bw, &pw, &ph, &bwp);
    Pages sp = pages_of(t.bp, t.bw, t.psm, 0, 0, t.w, h).and_(t.stale_pages);
    int n = 0;
    for (uint32_t pg = 0; pg < 512; pg++) {
        if (!sp.get(pg)) continue;
        int x, y;
        rt_page_xy(t, pg, &x, &y);
        uint32_t e = pg + 1;
        while (e < 512 && sp.get(e)) {
            int x2, y2;
            rt_page_xy(t, e, &x2, &y2);
            if (y2 != y || x2 != x + (int)(e - pg) * pw) break;
            e++;
        }
        int x1 = x + (int)(e - pg) * pw, y1 = y + ph;
        if (x1 > t.w) x1 = t.w;
        if (y1 > h) y1 = h;
        if (x1 > x && y1 > y) {
            GpuRect rc = { x, y, x1, y1 };
            mem_flush(r);
            r->be->rt_load(t.id, t.bp, t.bw, t.psm, rc);
            r->stats.rt_loads++;
            n += (int)(e - pg);
        }
        pg = e - 1;
    }
    FILE *lf = r->filt_log ? r->filt_log : r->rt_log;
    if (lf) fprintf(lf, "L bp %u bw %u psm %02x stale pages %d\n", t.bp, t.bw, t.psm, n);
    return 1;
}

/* rows [y0, y1) of t were just loaded from the mirror: the pages src (written back, about
 * to be destroyed) also holds are copied from it at the internal resolution; runs of pages
 * consecutive in both targets go as one copy */
static void rt_copy_pages(gpu_renderer *r, Rt &t, const Rt &src, int y0, int y1)
{
    int pw, ph;
    uint32_t bwp;
    page_geom(t.psm, t.bw, &pw, &ph, &bwp);
    Pages tp = pages_of(t.bp, t.bw, t.psm, 0, y0, t.w, y1);
    Pages sp = pages_of(src.bp, src.bw, src.psm, 0, 0, src.w, src.h);
    Pages both = tp.and_(sp);
    both.sub(src.stale_pages);   /* (the mirror is newer there) */
    if (!both.any()) return;
    int n = 0;
    for (uint32_t pg = 0; pg < 512; pg++) {
        if (!both.get(pg)) continue;
        int tx, ty, sx, sy;
        rt_page_xy(t, pg, &tx, &ty);
        rt_page_xy(src, pg, &sx, &sy);
        /* extend along a row while the next page follows in both */
        uint32_t e = pg + 1;
        while (e < 512 && both.get(e)) {
            int tx2, ty2, sx2, sy2;
            rt_page_xy(t, e, &tx2, &ty2);
            rt_page_xy(src, e, &sx2, &sy2);
            int k = (int)(e - pg);
            if (ty2 != ty || sy2 != sy || tx2 != tx + k * pw || sx2 != sx + k * pw) break;
            e++;
        }
        int wpx = (int)(e - pg) * pw;
        if (ty < y0 || ty + ph > y1 || sy + ph > src.h || tx + wpx > t.w || sx + wpx > src.w) {
            pg = e - 1;
            continue;   /* (a page not wholly inside both: keep the mirror's copy) */
        }
        GpuRect sr = { sx, sy, sx + wpx, sy + ph };
        if (r->be->rt_copy(t.id, tx, ty, src.id, sr)) n += (int)(e - pg);
        pg = e - 1;
    }
    FILE *lf = r->filt_log ? r->filt_log : r->rt_log;
    if (lf && n)
        fprintf(lf, "C bp %u bw %u -> bp %u bw %u psm %02x pages %d\n", src.bp, src.bw, t.bp, t.bw, t.psm, n);
}

/* format-changing views at the internal resolution (checkpoint 12; reint_view): $RG_NR_REINT=
 *   0  off (checkpoint 11: a target bound over another format's is loaded from the 1x mirror,
 *      immediates read at most 2 texels past a target directly),
 *   1  (default) a target bound over a live target of another format is filled from it at the
 *      internal resolution (rt_bind), and immediates read up to 4 texels past a target directly,
 *   2  also: an immediate that reads a live target as another format samples a reinterpreted
 *      copy at the internal resolution (measured on the ch07_rosa battle at x3: the CT16 dust
 *      effect at the characters' feet turns blockier than through the 1x mirror; off) */
static struct { uint64_t views, binds, margin, refused; int last_src; } g_reint;
static int reint_level()
{
    static int lv = -1;
    if (lv < 0) { const char *e = getenv("RG_NR_REINT"); lv = e && *e ? atoi(e) : 1; }
    return lv;
}
static int reint_on() { return reint_level() >= 1; }
static int reint_fmt(int psm) { return psm == GS_PSMCT32 || psm == GS_PSMCT24 || psm == GS_PSMCT16 || psm == GS_PSMCT16S; }

/* Find or create the target (bp,bw,psm), owning at least rows [0, need_h).
 * Other targets overlapping its pages are written back and dropped
 * (`keep` = the partner bound in the same draw). */
static Rt *rt_bind(gpu_renderer *r, int depth, uint32_t bp, uint32_t bw, int psm,
                   int need_h, int keep_id)
{
    if (bw == 0) bw = 1;
    int ph = page_h(psm);
    if (need_h < 1) need_h = 1;
    if (need_h > 2048) need_h = 2048;
    int want_h = (need_h + ph - 1) / ph * ph;
    if (want_h > 2048) want_h = 2048;
    Rt *t = NULL;
    for (Rt &x : r->rts)
        if (x.depth == depth && x.bp == bp && x.bw == bw && x.psm == psm) { t = &x; break; }
    int old_h = t ? t->h : 0;
    int new_h = t && t->h > want_h ? t->h : want_h;
    Pages np = pages_of(bp, bw, psm, 0, 0, (int)bw * 64, new_h);
    /* evict overlapping others.  One holding the same format page for page (another
     * view of the same memory: the game draws through page-offset FBPs and small work
     * targets inside its frame buffer) is written back but kept until this target is
     * loaded, then its pages are copied in at the internal resolution (rt_copy_pages):
     * through the 1x mirror alone everything drawn so far lost its upscaled detail
     * (item 8, docs/BRINGUP.md: low-res model parts) */
    Rt srcs[4], rsrcs[4];
    int nsrc = 0, nrsrc = 0;
    for (size_t i = 0; i < r->rts.size();) {
        Rt &o = r->rts[i];
        if (&o != t && o.id != keep_id && o.pages.overlaps(np)) {
            int tid = t ? t->id : -1;
            if (nsrc < 4 && rt_page_compatible(r, o, depth, bp, psm)) {
                if (r->rt_log)
                    fprintf(r->rt_log, "X %d bp %u bw %u psm %02x h %d dirty %d (pages kept)\n", o.depth, o.bp, o.bw, o.psm,
                            o.h, o.has_dirty);
                rt_writeback(r, o);
                srcs[nsrc++] = o;
                r->rts.erase(r->rts.begin() + (long)i);
                r->stats.rt_drops++;
            } else if (reint_on() && nrsrc < 4 && !depth && !o.depth && !o.stale && o.psm != psm && reint_fmt(o.psm) &&
                       reint_fmt(psm) && !(o.bp & 31) && !(bp & 31) && !r->no_rt_pagecopy) {
                /* a colour target of another format over these pages (the CT16 trick): written
                 * back, kept until this one is loaded, then reinterpreted into it at the
                 * internal resolution */
                if (r->rt_log)
                    fprintf(r->rt_log, "X %d bp %u bw %u psm %02x h %d dirty %d (reinterpreted)\n", o.depth, o.bp, o.bw, o.psm,
                            o.h, o.has_dirty);
                rt_writeback(r, o);
                rsrcs[nrsrc++] = o;
                r->rts.erase(r->rts.begin() + (long)i);
                r->stats.rt_drops++;
            } else {
                rt_drop(r, i);
            }
            if (tid >= 0) {
                t = NULL;
                for (Rt &x : r->rts) if (x.id == tid) { t = &x; break; }
            }
            continue;
        }
        i++;
    }
    if (!t) {
        Rt n;
        memset(&n, 0, sizeof n);
        n.depth = depth; n.bp = bp; n.bw = bw; n.psm = psm;
        n.w = (int)bw * 64;
        n.h = 0;
        n.h_alloc = new_h <= 1024 ? 1024 : 2048;
        n.id = r->be->rt_create(depth, n.w, n.h_alloc);
        if (n.id < 0) return NULL;
        r->rts.push_back(n);
        t = &r->rts.back();
        r->stats.rt_creates++;
        if (r->rt_log) fprintf(r->rt_log, "R %d bp %u bw %u psm %02x h %d keep %d\n", depth, bp, bw, psm, new_h, keep_id);
        old_h = 0;
    }
    int ly0 = new_h, ly1 = new_h;   /* rows loaded from the mirror now */
    if (t->stale) {
        /* only the pages the CPU wrote: the rest still holds what was drawn at the
         * internal resolution (item 8: a texture upload into a page the frame target
         * claims reloaded the whole frame at 1x) */
        if (r->no_rt_pagecopy || !rt_load_stale_pages(r, *t, old_h)) {
            rt_load_rows(r, *t, 0, old_h);
            ly0 = 0;
            ly1 = old_h;
        }
        t->stale = 0;
        t->stale_pages.clear();
    }
    if (new_h > old_h) {
        if (new_h > t->h_alloc) {
            t->h_alloc = 2048;
            r->be->rt_resize(t->id, t->w, t->h_alloc);
        }
        t->h = new_h;
        t->pages = np;
        rt_load_rows(r, *t, old_h, new_h);
        if (ly0 > old_h) ly0 = old_h;
        ly1 = new_h;
    }
    for (int i = 0; i < nsrc; i++) {
        if (ly1 > ly0) rt_copy_pages(r, *t, srcs[i], ly0, ly1);
        r->be->rt_destroy(srcs[i].id);
    }
    for (int i = 0; i < nrsrc; i++) {
        if (ly1 > ly0) {
            GpuRect dr = { 0, ly0, t->w, ly1 }, sr = { 0, 0, rsrcs[i].w, rsrcs[i].h };
            mem_flush(r);
            if (r->be->rt_reinterpret(t->id, t->bp, t->bw, t->psm, dr, rsrcs[i].id, rsrcs[i].bp, rsrcs[i].bw, rsrcs[i].psm, sr))
                g_reint.binds++;
            else
                g_reint.refused++;
            FILE *lf = r->filt_log ? r->filt_log : r->rt_log;
            if (lf)
                fprintf(lf, "I bp %u bw %u psm %02x -> bp %u bw %u psm %02x rows %d-%d\n", rsrcs[i].bp, rsrcs[i].bw, rsrcs[i].psm,
                        t->bp, t->bw, t->psm, ly0, ly1);
        }
        r->be->rt_destroy(rsrcs[i].id);
    }
    return t;
}

static Rt *rt_find_id(gpu_renderer *r, int id)
{
    for (Rt &x : r->rts) if (x.id == id) return &x;
    return NULL;
}

/* ================================================== state derivation */
static void make_key(gpu_renderer *r, const gpu_gs *gs, Key *k)
{
    uint64_t prim = gs->reg[GS_PRIM];
    uint64_t attr = (gs->reg[GS_PRMODECONT] & 1) ? prim : gs->reg[GS_PRMODE];
    int c = (int)BITS(attr, 9, 1);
    memset(k, 0, sizeof *k);
    k->attr = attr & 0x7F0;   /* TME FGE ABE AA1 FST CTXT FIX */
    k->frame = gs->reg[GS_FRAME_1 + c];
    k->zbuf = gs->reg[GS_ZBUF_1 + c];
    k->test = gs->reg[GS_TEST_1 + c];
    k->alpha = gs->reg[GS_ALPHA_1 + c];
    k->fba = gs->reg[GS_FBA_1 + c] & 1;
    k->pabe = gs->reg[GS_PABE] & 1;
    k->colclamp = gs->reg[GS_COLCLAMP] & 1;
    k->dthe = gs->reg[GS_DTHE] & 1;
    k->dimx = gs->reg[GS_DIMX];
    k->fogcol = gs->reg[GS_FOGCOL] & 0xFFFFFF;
    k->scanmsk = gs->reg[GS_SCANMSK] & 3;
    k->scissor = gs->reg[GS_SCISSOR_1 + c];
    if (attr & (1u << 4)) {
        k->tex0 = gs->reg[GS_TEX0_1 + c] & ((1ull << 61) - 1); /* CLD excluded */
        k->tex1 = gs->reg[GS_TEX1_1 + c];
        k->clamp = gs->reg[GS_CLAMP_1 + c];
        k->miptbp1 = gs->reg[GS_MIPTBP1_1 + c];
        k->miptbp2 = gs->reg[GS_MIPTBP2_1 + c];
        k->texa = gs->reg[GS_TEXA];
        int psm = (int)BITS(k->tex0, 20, 6);
        if (psm == GS_PSMT8 || psm == GS_PSMT4 || psm == GS_PSMT8H || psm == GS_PSMT4HL ||
            psm == GS_PSMT4HH) {
            if (gs->stats.clut_loads != r->clut_seen_loads) {
                r->clut_seen_loads = gs->stats.clut_loads;
                if (r->clut_force || memcmp(gs->clut, r->clut_copy, sizeof r->clut_copy) != 0) {
                    memcpy(r->clut_copy, gs->clut, sizeof r->clut_copy);
                    r->clut_gen_id++;
                    r->clut_force = 0;
                }
            }
            k->clut_gen = r->clut_gen_id;
        }
    }
}

static uint32_t to_stored16(uint32_t c)
{
    return ((c >> 3) & 31u) | (((c >> 11) & 31u) << 5) | (((c >> 19) & 31u) << 10) |
           ((c >> 31) << 15);
}

/* The texels of mip level lv (W x H) that the wrap mode can address:
 * gs_tex.c REPEAT/CLAMP [0, size), REGION_CLAMP [min, max],
 * REGION_REPEAT (c & min) | max. */
static GpuRect wrap_rect(const Key &k, int lv, int W, int H)
{
    int wms = (int)BITS(k.clamp, 0, 2), wmt = (int)BITS(k.clamp, 2, 2);
    int minu = (int)BITS(k.clamp, 4, 10), maxu = (int)BITS(k.clamp, 14, 10);
    int minv = (int)BITS(k.clamp, 24, 10), maxv = (int)BITS(k.clamp, 34, 10);
    int u0 = 0, u1 = W, v0 = 0, v1 = H;
    if (wms == 2) { u0 = minu >> lv; u1 = (maxu >> lv) + 1; }
    else if (wms == 3) { u0 = maxu; u1 = (minu | maxu) + 1; }
    if (wmt == 2) { v0 = minv >> lv; v1 = (maxv >> lv) + 1; }
    else if (wmt == 3) { v0 = maxv; v1 = (minv | maxv) + 1; }
    if (u1 > 1024) u1 = 1024;
    if (v1 > 1024) v1 = 1024;
    if (u1 <= u0) u1 = u0 + 1;
    if (v1 <= v0) v1 = v0 + 1;
    GpuRect rc = { u0, v0, u1, v1 };
    return rc;
}

/* texture pages for every mip level that can be sampled */
static Pages tex_pages(const Key &k)
{
    Pages p;
    p.clear();
    int psm = (int)BITS(k.tex0, 20, 6);
    int tw = (int)BITS(k.tex0, 26, 4), th = (int)BITS(k.tex0, 30, 4);
    if (tw > 10) tw = 10;
    if (th > 10) th = 10;
    int mxl = (int)BITS(k.tex1, 2, 3);
    if (mxl > 6) mxl = 6;
    int mmin = (int)BITS(k.tex1, 6, 3);
    if (mmin < 2 || mmin > 5) mxl = 0;
    for (int lv = 0; lv <= mxl; lv++) {
        uint32_t tbp, tbw;
        if (lv == 0) { tbp = BITS(k.tex0, 0, 14); tbw = BITS(k.tex0, 14, 6); }
        else {
            uint64_t m = lv <= 3 ? k.miptbp1 : k.miptbp2;
            int j = (lv - 1) % 3;
            tbp = BITS(m, j * 20, 14); tbw = BITS(m, j * 20 + 14, 6);
        }
        int W = 1 << (tw - lv < 0 ? 0 : tw - lv), H = 1 << (th - lv < 0 ? 0 : th - lv);
        GpuRect rc = wrap_rect(k, lv, W, H);
        p.add(pages_of(tbp, tbw ? tbw : 1, psm, rc.x0, rc.y0, rc.x1, rc.y1));
    }
    return p;
}

static void derive(gpu_renderer *r, const gpu_gs *gs, const Key &k, Derived *d)
{
    memset(d, 0, sizeof *d);
    uint64_t attr = k.attr;
    d->ctx = (int)BITS(attr, 9, 1);
    d->tme = (int)BITS(attr, 4, 1);
    d->fge = (int)BITS(attr, 5, 1);
    d->abe = (int)BITS(attr, 6, 1);
    d->fst = (int)BITS(attr, 8, 1);
    d->fbp = BITS(k.frame, 0, 9) * 32u;
    d->fbw = BITS(k.frame, 16, 6);
    d->fpsm = (int)BITS(k.frame, 24, 6);
    d->fbmsk = BITS(k.frame, 32, 32);
    d->zbp = BITS(k.zbuf, 0, 9) * 32u;
    d->zpsm = (int)BITS(k.zbuf, 24, 4) | 0x30;
    d->zmsk = (int)BITS(k.zbuf, 32, 1);
    d->ate = (int)BITS(k.test, 0, 1);
    d->atst = (int)BITS(k.test, 1, 3);
    uint32_t aref = BITS(k.test, 4, 8);
    d->afail = (int)BITS(k.test, 12, 2);
    d->date = (int)BITS(k.test, 14, 1);
    d->datm = (int)BITS(k.test, 15, 1);
    d->zte = (int)BITS(k.test, 16, 1);
    d->ztst = (int)BITS(k.test, 17, 2);
    int fpsm = d->fpsm;
    int f16 = psm_is16(fpsm);
    /* the frame formats the GS can draw into */
    if (!(fpsm == GS_PSMCT32 || fpsm == GS_PSMCT24 || f16)) { d->skip = 1; return; }
    if (d->zte && d->ztst == 0) { d->skip = 1; return; }
    if (d->ate && d->atst == 1) d->ate = 0;                    /* ALWAYS */
    if (d->ate && d->atst == 0 && d->afail == 0) { d->skip = 1; return; }

    uint64_t sc = k.scissor;
    d->scx0 = (int)BITS(sc, 0, 11); d->scx1 = (int)BITS(sc, 16, 11) + 1;
    d->scy0 = (int)BITS(sc, 32, 11); d->scy1 = (int)BITS(sc, 48, 11) + 1;
    int fw = (int)(d->fbw ? d->fbw : 1) * 64;
    if (d->scx1 > fw) d->scx1 = fw;
    if (d->scx1 <= d->scx0 || d->scy1 <= d->scy0) { d->skip = 1; return; }

    /* blend: decide whether the destination is needed */
    int A = (int)BITS(k.alpha, 0, 2), B = (int)BITS(k.alpha, 2, 2), C = (int)BITS(k.alpha, 4, 2),
        Dd = (int)BITS(k.alpha, 6, 2);
    uint32_t fix = BITS(k.alpha, 32, 8);
    int abe = d->abe;
    uint32_t rgb_keep = 0;   /* blend leaves RGB = Cd: mask RGB instead */
    if (abe && A == B) {
        if (Dd == 0) abe = 0;                       /* result = Cs */
        else if (Dd == 1 && !k.pabe) { abe = 0; rgb_keep = 1; } /* result = Cd (PABE would
                                                    write Cs where As < 0x80) */
    } else if (abe && A == 0 && B == 2 && C == 2 && fix == 128 && Dd == 2) {
        abe = 0;                                    /* Cs * 128 >> 7 = Cs */
    }
    if (r->cfg.fault == 1 && d->abe) abe = 1;      /* control: keep the shader blend */
    d->abe = abe;

    /* FBMSK: channel write mask, or merge in the shader */
    uint32_t cm = 0;
    int merge = 0;
    if (f16) {
        uint32_t m = to_stored16(d->fbmsk);
        uint32_t fld[4] = { m & 31u, (m >> 5) & 31u, (m >> 10) & 31u, (m >> 15) & 1u };
        uint32_t full[4] = { 31, 31, 31, 1 };
        for (int i = 0; i < 4; i++) {
            if (fld[i] == 0) cm |= 1u << i;
            else if (fld[i] != full[i]) merge = 1;
        }
    } else {
        for (int i = 0; i < 4; i++) {
            uint32_t b = (d->fbmsk >> (8 * i)) & 255u;
            if (b == 0) cm |= 1u << i;
            else if (b != 255) merge = 1;
        }
        if (fpsm == GS_PSMCT24) cm &= 7u;
    }
    if (merge) cm = fpsm == GS_PSMCT24 ? 7u : 15u;
    if (rgb_keep) cm &= 8u;
    int date = d->date && (fpsm == GS_PSMCT32 || f16);
    d->merge = merge;
    d->need_dst = abe || date || merge;
    d->cmask_base = cm;
    d->need_depth = (d->zte && d->ztst >= 2) || !d->zmsk;
    d->zfunc = !d->need_depth ? GZ_OFF
             : (!d->zte || d->ztst == 1) ? GZ_ALWAYS : (d->ztst == 2 ? GZ_GEQUAL : GZ_GREATER);

    /* passes (alpha test FAIL modes) */
    int zw = !d->zmsk;
    if (d->ate && d->afail != 0) {
        int n = 0;
        if (d->atst != 0) { d->pass[n].failpass = 0; d->pass[n].zwrite = zw; d->pass[n].cmask = cm; n++; }
        switch (d->afail) {
        case 1: d->pass[n].failpass = 1; d->pass[n].zwrite = 0; d->pass[n].cmask = cm; n++; break;
        case 2: if (zw) { d->pass[n].failpass = 1; d->pass[n].zwrite = 1; d->pass[n].cmask = 0; n++; } break;
        default: d->pass[n].failpass = 1; d->pass[n].zwrite = 0; d->pass[n].cmask = cm & 7u; n++; break;
        }
        d->npass = n;
    } else {
        d->pass[0].failpass = 0; d->pass[0].zwrite = zw; d->pass[0].cmask = cm;
        d->npass = 1;
    }
    d->serial = d->need_dst || d->npass > 1;
    /* Ordered blending (docs/GPU.md "Performance"): the colour target's
     * rasterizer-ordered view does every pixel's read-modify-write in
     * primitive order, both alpha-test passes in one draw.  Overlapping
     * primitives then share one batch and need no destination snapshot; the
     * shader computes exactly what the snapshot path does.  The view is
     * written whether or not the depth test passes, so a depth target is
     * allowed only when its test cannot fail (ZTE=0 or ZTST ALWAYS), and
     * then only with the same Z write for both alpha-test passes (one draw
     * has one depth write mask); depth writes keep primitive order like any
     * output-merger operation.  With depth in an ordered view too
     * (r->zrov, docs/PERF-3D.md) the shader tests and writes Z per pixel in
     * primitive order, so any depth test and per-pass Z write masks work. */
    int rov_depth_ok = !d->need_depth || r->zrov;
    if (d->need_depth && !r->zrov && d->zfunc == GZ_ALWAYS) {
        rov_depth_ok = 1;
        for (int i = 1; i < d->npass; i++)
            if (d->pass[i].zwrite != d->pass[0].zwrite) rov_depth_ok = 0;
    }
    if (d->serial && rov_depth_ok && r->cfg.fault == 6) {
        d->serial = 0;      /* control: overlapping primitives read one snapshot */
    } else if (d->serial && r->rov && rov_depth_ok) {
        d->serial = 0;
        d->rov = 1;
        uint32_t ctl = 0;
        for (int i = 0; i < d->npass; i++) {
            if (d->pass[i].failpass) ctl |= 0x100u | ((d->pass[i].cmask & 15u) << 4);
            else ctl |= 0x200u | (d->pass[i].cmask & 15u);
        }
        d->cb.d[11][1] = ctl;
    }

    /* constants */
    uint32_t (*D)[4] = d->cb.d;
    uint32_t fl = 0;
    if (d->tme) fl |= GF_TME;
    if (d->fge) fl |= GF_FGE;
    if (abe) fl |= GF_ABE;
    if (d->fst) fl |= GF_FST;
    if (date) fl |= GF_DATE;
    if (d->datm) fl |= GF_DATM;
    if (d->ate) fl |= GF_ATE;
    if (d->need_dst) fl |= GF_NEEDDST;
    if (k.colclamp) fl |= GF_COLCLAMP;
    if (k.dthe) fl |= GF_DTHE;
    if (k.fba) fl |= GF_FBA;
    if (k.pabe) fl |= GF_PABE;
    if (merge) fl |= GF_MERGE;
    fl |= (uint32_t)k.scanmsk << 12;
    fl |= (uint32_t)d->atst << 14;
    D[0][2] = (uint32_t)r->scale;
    D[0][3] = fl;
    D[1][0] = (uint32_t)fpsm;
    D[1][1] = d->fbmsk;
    D[1][2] = aref;
    D[1][3] = (uint32_t)d->zpsm;
    D[2][0] = (uint32_t)(A | (B << 2) | (C << 4) | (Dd << 6));
    D[2][1] = fix;
    D[2][2] = (uint32_t)k.fogcol;
    D[2][3] = d->zpsm == GS_PSMZ24 ? 0xFFFFFFu
            : (d->zpsm == GS_PSMZ16 || d->zpsm == GS_PSMZ16S) ? 0xFFFFu : 0xFFFFFFFFu;
    D[3][0] = (uint32_t)k.dimx;
    D[3][1] = (uint32_t)(k.dimx >> 32);
    D[3][2] = (uint32_t)r->cfg.fault;
    if (d->tme) {
        uint64_t t0 = k.tex0, t1 = k.tex1, cl = k.clamp;
        int psm = (int)BITS(t0, 20, 6);
        D[4][0] = (uint32_t)psm;
        D[4][1] = BITS(t0, 26, 4) | (BITS(t0, 30, 4) << 4) | (BITS(t0, 34, 1) << 8) |
                  (BITS(t0, 35, 2) << 9);
        D[4][2] = BITS(t0, 51, 4) | (BITS(t0, 56, 5) << 4);
        D[4][3] = BITS(cl, 0, 2) | (BITS(cl, 2, 2) << 2) | (BITS(t1, 5, 1) << 4) |
                  (BITS(t1, 6, 3) << 5) | (BITS(t1, 2, 3) << 8) | (BITS(t1, 0, 1) << 11) |
                  (BITS(t1, 19, 2) << 12);
        D[5][0] = BITS(cl, 4, 10); D[5][1] = BITS(cl, 14, 10);
        D[5][2] = BITS(cl, 24, 10); D[5][3] = BITS(cl, 34, 10);
        D[6][0] = (uint32_t)((int32_t)(BITS(t1, 32, 12) << 20) >> 20);
        D[6][1] = BITS(k.texa, 0, 8); D[6][2] = BITS(k.texa, 32, 8); D[6][3] = BITS(k.texa, 15, 1);
        for (int lv = 0; lv < 7; lv++) {
            uint32_t tbp, tbw;
            if (lv == 0) { tbp = BITS(t0, 0, 14); tbw = BITS(t0, 14, 6); }
            else {
                uint64_t m = lv <= 3 ? k.miptbp1 : k.miptbp2;
                int j = (lv - 1) % 3;
                tbp = BITS(m, j * 20, 14); tbw = BITS(m, j * 20 + 14, 6);
            }
            D[7 + lv / 2][(lv & 1) * 2] = tbp;
            D[7 + lv / 2][(lv & 1) * 2 + 1] = tbw;
        }
        d->tex_pages = tex_pages(k);
        d->indexed = k.clut_gen != 0;
        int mxl = (int)BITS(t1, 2, 3), mmin = (int)BITS(t1, 6, 3);
        d->tex_lvl0 = mxl == 0 || mmin < 2 || mmin > 5;
        d->zwrite_any = !d->zmsk;
        /* Texels that live in bits 24-31 (T8H, T4HL, T4HH) are never written
         * by a 24-bit frame (CT24) or Z buffer (Z24): the GS keeps the high
         * byte, and so do the write-backs (docs/GPU.md "Performance").  Such
         * a buffer is not part of the feedback write set and is not written
         * back for the texture. */
        d->hbyte_tex = psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH;
        d->fb_feedback = !(d->hbyte_tex && fpsm == GS_PSMCT24);
        d->zb_feedback = d->zwrite_any && !(d->hbyte_tex && d->zpsm == GS_PSMZ24);
        Pages w;
        w.clear();
        if (d->fb_feedback) w.add(pages_of(d->fbp, (uint32_t)(fw / 64), fpsm, 0, 0, fw, d->scy1));
        if (d->zb_feedback) w.add(pages_of(d->zbp, (uint32_t)(fw / 64), d->zpsm, 0, 0, fw, d->scy1));
        d->feedback = d->tex_pages.overlaps(w);
        /* direct sampling: level 0 only, no CLUT, and a format whose texel
         * value a target holds exactly (CT32/CT24/CT16/CT16S colour, Z24
         * and Z16/Z16S depth; Z32 above 2^24 does not survive D32_FLOAT) */
        d->tbp = BITS(t0, 0, 14);
        d->tbw = BITS(t0, 14, 6);
        d->tpsm = psm;
        {
            int tw0 = (int)BITS(t0, 26, 4), th0 = (int)BITS(t0, 30, 4);
            if (tw0 > 10) tw0 = 10;
            if (th0 > 10) th0 = 10;
            d->tex_wrap = wrap_rect(k, 0, 1 << tw0, 1 << th0);
        }
        d->direct_ok = !r->cfg.rtt_native && d->tex_lvl0 && !d->indexed && d->tbw != 0 &&
                       (psm == GS_PSMCT32 || psm == GS_PSMCT24 || psm == GS_PSMCT16 ||
                        psm == GS_PSMCT16S || psm == GS_PSMZ24 || psm == GS_PSMZ16 ||
                        psm == GS_PSMZ16S);
    }
    /* FRAME and ZBUF on the same pages (inside the scissor) while Z is
     * tested or written: two GPU targets cannot interleave their writes the
     * way the reference does per pixel, so these primitives are drawn by the
     * software rasterizer (on_draw). */
    if (d->need_depth && r->cfg.fault != 3) {
        uint32_t bw = (uint32_t)(fw / 64);
        d->alias = pages_of(d->fbp, bw, fpsm, d->scx0, d->scy0, d->scx1, d->scy1)
                       .overlaps(pages_of(d->zbp, bw, d->zpsm, d->scx0, d->scy0, d->scx1, d->scy1));
    }
    (void)gs;
}



/* Copy the pages of a hot read region to a staging slot now: the mirror
 * first made current for them (uploads, write-backs of targets dirty
 * there; GPU work, no wait). */
static void hot_snapshot(gpu_renderer *r, HotRead &h)
{
    for (Rt &t : r->rts) {
        if (!t.has_dirty || !t.pages.overlaps(h.pages)) continue;
        /* only the target's pixels on those pages (the target stays dirty
         * elsewhere): each page is a pw x ph cell of a page-aligned buffer */
        int pw, ph;
        uint32_t bwp;
        page_geom(t.psm, t.bw, &pw, &ph, &bwp);
        bool cells = !(t.bp & 31) && bwp > 0;
        for (uint32_t pg = 0; pg < 512 && cells; pg++) {
            if (!h.pages.get(pg) || !t.pages.get(pg)) continue;
            int k = (int)((pg - (t.bp >> 5)) & 511u);
            GpuRect c = { (int)(k % bwp) * pw, (int)(k / bwp) * ph, (int)(k % bwp) * pw + pw, (int)(k / bwp) * ph + ph };
            GpuRect d = t.dirty;
            if (c.x0 > d.x0) d.x0 = c.x0;
            if (c.y0 > d.y0) d.y0 = c.y0;
            if (c.x1 < d.x1) d.x1 = c.x1;
            if (c.y1 < d.y1) d.y1 = c.y1;
            if (d.x1 > t.w) d.x1 = t.w;
            if (d.y1 > t.h) d.y1 = t.h;
            if (d.x1 <= d.x0 || d.y1 <= d.y0) continue;
            if (!pages_of(t.bp, t.bw, t.psm, d.x0, d.y0, d.x1, d.y1).and_(h.pages).any()) { cells = false; break; }
            mem_flush(r);
            r->be->rt_writeback(t.id, t.bp, t.bw, t.psm, d);
            blk_write_gpu(r, t.bp, t.bw, t.psm, d);
            Pages wp;
            wp.clear();
            wp.set(pg);
            stamp_pages(r, wp);
        }
        if (!cells) rt_writeback(r, t);
    }
    uint32_t runs[16];
    int n = 0;
    for (uint32_t pg = 0; pg < 512 && n < 8;) {
        if (!h.pages.get(pg)) { pg++; continue; }
        uint32_t e = pg;
        while (e < 512 && h.pages.get(e)) e++;
        runs[2 * n] = pg * 8192u;
        runs[2 * n + 1] = (e - pg) * 8192u;
        n++;
        pg = e;
    }
    mem_flush(r);
    h.slot = r->be->snap_copy(runs, n);
    h.state = h.slot >= 0 ? 1 : 0;
    if (h.slot >= 0) {
        r->stats.early_copies++;
        if (h.slot < GpuBackend::SNAP_SLOTS) r->snap_slot_serial[h.slot] = ++r->snap_serial;
    }
}

/* after a batch: early copies of the pages it wrote are void; regions
 * written before and left alone by this batch are copied now (their last
 * write is queued) */
static void hot_after_batch(gpu_renderer *r, const Pages &wp)
{
    for (HotRead &h : r->hot) {
        if (!h.used) continue;
        if (h.pages.overlaps(wp)) {
            if (r->cfg.fault != 16) h.state = 2;
            else if (h.state != 1) hot_snapshot(r, h);   /* control: a copy outlives later writes */
        }
        else if (h.state == 2) hot_snapshot(r, h);
    }
}










/* ---- GPU-side CLUT loads (docs/NATIVE-RENDER.md "GPU-side CLUT loads") ----------
 * A CLUT load whose source the GPU holds newer data for (a dirty target, pages newer in
 * the mirror: the game draws a palette and loads it as the CLUT) would read back.  It is
 * made on the GPU instead: the source written back into the mirror (GPU work), the
 * mirror's CPU-newer pages uploaded, then CS_clut does the model's CLUT arithmetic
 * (gs_tex.c gs_tex0_written) into the CLUT buffer.  The words it wrote are owned by the
 * GPU (clut_own) until a CPU load writes them again; CPU uploads leave them alone
 * (set_clut_part); a CPU user of the values (gpu_sync, software draws, CPU texture
 * decodes) reads them back (clut_resolve). */
static void clut_words(int csm, uint32_t csa, int cpsm, uint32_t n, uint8_t *own, uint8_t v)
{
    int is32 = cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24;
    for (uint32_t c = 0; c < 512; c++) {
        uint32_t i = (is32 && csm == 0) ? (((c & 255) - (csa & 15) * 16) & 255) : ((c - csa * 16) & 511);
        if (i < n) own[c >> 1] = v;
    }
}
/* the texture of key k reads CLUT words the GPU loaded (their values are not in clut_copy:
 * the native texture key takes the generation instead) */
static int clut_tex_gpu(const gpu_renderer *r, const Key &k)
{
    if (!r->clut_own_any) return 0;
    int psm = (int)BITS(k.tex0, 20, 6), cpsm = (int)BITS(k.tex0, 51, 4);
    uint32_t csa = (uint32_t)BITS(k.tex0, 56, 5);
    uint32_t n = (psm == GS_PSMT8 || psm == GS_PSMT8H) ? 256u : 16u;
    uint8_t w[256];
    memset(w, 0, sizeof w);
    clut_words(0, csa, cpsm, n, w, 1);    /* the words such a load writes = the words the texture reads */
    for (int i = 0; i < 256; i++)
        if (w[i] && r->clut_own[i]) return 1;
    return 0;
}
static void clut_resolve(gpu_renderer *r)
{
    if (!r->clut_own_any || !r->gs) return;
    GpuClutCB c;
    if (r->be->clut_read(&c)) {
        const uint32_t *w = &c.c[0][0];
        for (int i = 0; i < 256; i++) {
            if (!r->clut_own[i]) continue;
            r->gs->clut[2 * i] = (uint16_t)w[i];
            r->gs->clut[2 * i + 1] = (uint16_t)(w[i] >> 16);
            r->clut_copy[2 * i] = (uint16_t)w[i];
            r->clut_copy[2 * i + 1] = (uint16_t)(w[i] >> 16);
        }
    }
    memset(r->clut_own, 0, sizeof r->clut_own);
    r->clut_own_any = 0;
    r->stats.clut_resolves++;
}

static void replay_free(gpu_renderer *r);

/* ==================================================== local memory on the GPU
 * (docs/NATIVE-RENDER.md "Checkpoint 10").  The mirror is the only copy of the GS's 4 MB:
 * transfers are merged into it on the GPU (data / mask words the CPU builds from the transfer
 * bytes with the GS address functions), copies and CLUT loads read it there, and the one
 * read-back is the lens-flare probe's small region (early copy). */
static uint64_t fnv64(const uint8_t *d, size_t n)
{
    uint64_t h = 1469598103934665603ull;
    size_t i = 0;
    for (; i + 8 <= n; i += 8) {
        uint64_t v;
        memcpy(&v, d + i, 8);
        h = (h ^ v) * 1099511628211ull;
    }
    for (; i < n; i++) h = (h ^ d[i]) * 1099511628211ull;
    return h;
}
/* the pages rows [y, y + rows) of rc can touch (every page when the rectangle wraps at 2048) */
static Pages xfer_pages(const gs_mem_rect &rc, uint32_t rows)
{
    Pages p;
    if (rc.x + rc.w > 2048 || rc.y + rows > 2048) { p.all(); return p; }
    return pages_of(rc.bp, rc.bw ? rc.bw : 1, rc.psm, (int)rc.x, (int)rc.y, (int)(rc.x + rc.w), (int)(rc.y + rows));
}
/* the mirror changed in pages p (a transfer or a copy): targets there reload those pages, early
 * copies of them are void */
static void mirror_written(gpu_renderer *r, const Pages &p)
{
    stamp_pages(r, p);
    for (Rt &t : r->rts)
        if (t.pages.overlaps(p)) { t.stale = 1; t.stale_pages.add(p); }
    hot_cpu_write(r, p);
}

/* a format's pixel -> (word in the block, bit shift) table (blocks are 256 bytes in every
 * format; its pixel size from blk_dims) */
struct BlkTab { uint32_t bwk, bhk, mask; uint8_t word[512], shift[512]; };
static const BlkTab *blk_tab(int psm)
{
    static BlkTab tab[64];
    static uint8_t have[64];
    psm &= 63;
    if (!have[psm]) {
        BlkTab &t = tab[psm];
        int bwk, bhk;
        if (!blk_dims(psm, &bwk, &bhk)) { bwk = 8; bhk = 8; }
        t.bwk = (uint32_t)bwk;
        t.bhk = (uint32_t)bhk;
        for (int y = 0; y < bhk; y++)
            for (int x = 0; x < bwk; x++) {
                uint32_t w, m, sh;
                nr_px_word(psm, 0, 4, (uint32_t)x, (uint32_t)y, &w, &m, &sh);
                t.word[y * bwk + x] = (uint8_t)(w & 63u);
                t.shift[y * bwk + x] = (uint8_t)sh;
                t.mask = m >> sh;
            }
        have[psm] = 1;
    }
    return &tab[psm];
}

/* the (data, mask) words of the first npx pixels of a transfer into rc (BPP bits per pixel): the
 * block's arrangement is the same everywhere, so one address per block, then each pixel's word
 * and bits inside the block from a table (nr_px_word of block 0) */
template <int BPP>
static void xfer_fill(const gs_mem_rect &rc, int psm, const uint8_t *data, uint32_t npx, uint32_t *dm, uint8_t *btouch,
                      std::vector<uint16_t> &blist)
{
    const BlkTab *bt = blk_tab(psm);
    const uint32_t bwk = bt->bwk, bhk = bt->bhk, msk = bt->mask;
    const bool full = BPP == 32 && msk == 0xFFFFFFFFu;
    for (uint32_t i = 0, py = 0; i < npx; py++) {
        uint32_t y = (rc.y + py) & 2047u, cy = y & (bhk - 1), base = 0, bx_last = ~0u;
        const uint8_t *wrow = &bt->word[cy * bwk], *srow = &bt->shift[cy * bwk];
        uint32_t n = rc.w < npx - i ? rc.w : npx - i;
        for (uint32_t px = 0; px < n; px++, i++) {
            uint32_t x = (rc.x + px) & 2047u, bxk = x / bwk;
            if (bxk != bx_last) {
                base = (nr_px_addr(psm, rc.bp, rc.bw, x & ~(bwk - 1), y & ~(bhk - 1), NULL) >> 2) & 0xFFFC0u;
                bx_last = bxk;
                uint32_t b = base >> 6;
                if (!btouch[b]) { btouch[b] = 1; blist.push_back((uint16_t)b); }
            }
            uint32_t e = x & (bwk - 1), w = base + wrow[e], v;
            if (BPP == 32) memcpy(&v, data + 4u * i, 4);
            else if (BPP == 24) v = (uint32_t)data[3u * i] | ((uint32_t)data[3u * i + 1] << 8) | ((uint32_t)data[3u * i + 2] << 16);
            else if (BPP == 16) v = (uint32_t)data[2u * i] | ((uint32_t)data[2u * i + 1] << 8);
            else if (BPP == 8) v = data[i];
            else v = (data[i >> 1] >> ((i & 1) * 4)) & 15u;
            if (full) {
                dm[2 * w] = v;
                dm[2 * w + 1] = 0xFFFFFFFFu;
            } else {
                uint32_t sh = srow[e], m = msk << sh;
                dm[2 * w] = (dm[2 * w] & ~m) | ((v << sh) & m);
                dm[2 * w + 1] |= m;
            }
        }
    }
}

/* The transfers since the last flush, swizzled into the mirror on the GPU (CS_xfer): their bytes
 * and one descriptor each.  Before anything reads or writes the mirror on the GPU, and before a
 * transfer that shares a block with one of them (the batch's pixels are written in no order). */
static void mem_flush(gpu_renderer *r)
{
    if (!r->xb_ndesc) return;
    double t1 = now_us();
    if (!r->be->mem_xfer_batch(r->xb.data(), r->xb_bytes, r->xd.data(), r->xb_ndesc, r->xb_px)) r->x_batch_fail++;
    for (uint16_t b : r->pend) r->pend_on[b] = 0;
    r->pend.clear();
    r->xb_ndesc = r->xb_bytes = r->xb_px = 0;
    r->x_flushes++;
    r->x_us_up += now_us() - t1;
}
/* one transfer (or a run of its rows) into the batch */
static void xb_add(gpu_renderer *r, const gs_mem_rect &rc, uint32_t y, const uint8_t *data, uint32_t bytes, uint32_t npx)
{
    uint32_t need = (bytes + 3u) & ~3u;
    if (r->xb_ndesc >= GpuBackend::XFER_DESCS || r->xb_bytes + need > GpuBackend::XFER_BYTES || r->xb_px + npx > (64u << 20))
        mem_flush(r);
    if (r->xb.size() < GpuBackend::XFER_BYTES + 16u) r->xb.resize(GpuBackend::XFER_BYTES + 16u);
    if (r->xd.size() < GpuBackend::XFER_DESCS * 8u) r->xd.resize(GpuBackend::XFER_DESCS * 8u);
    uint32_t *d = &r->xd[(size_t)r->xb_ndesc * 8u];
    d[0] = (uint32_t)rc.psm; d[1] = rc.bp; d[2] = rc.bw; d[3] = rc.x; d[4] = y; d[5] = rc.w; d[6] = r->xb_px; d[7] = r->xb_bytes;
    memcpy(r->xb.data() + r->xb_bytes, data, bytes);
    r->xb_bytes += need;
    r->xb_px += npx;
    r->xb_ndesc++;
}

/* the words of kept transfer slot i into the KBlk of every block it is still the last write of */
static void kx_make(gpu_renderer *r, uint32_t i)
{
    KXfer &x = r->kx[i];
    if (!x.epoch) return;
    static std::vector<uint16_t> kl;
    static std::vector<uint8_t> kt;
    if (kt.empty()) kt.assign(16384, 0);
    if (r->dm.empty()) r->dm.assign((size_t)GS_VRAM_BYTES / 2u, 0u);
    uint32_t *dm = r->dm.data();
    kl.clear();
    if (gs_psm_bpp(x.rc.psm) == 32) xfer_fill<32>(x.rc, x.rc.psm, x.data, x.npx, dm, kt.data(), kl);
    else xfer_fill<16>(x.rc, x.rc.psm, x.data, x.npx, dm, kt.data(), kl);
    for (uint16_t b : kl) {
        kt[b] = 0;
        if (r->blk_owner[b] && r->blk_epoch[b] == x.epoch && r->blk_kx[b] == i + 1) {
            KBlk *kb = r->kblk[b];
            if (!kb) kb = r->kblk[b] = new KBlk;
            kb->epoch = x.epoch;
            for (uint32_t k = 0; k < 64; k++) {
                uint32_t w = (uint32_t)b * 64u + k;
                kb->d[k] = dm[2 * w];
                kb->m[k] = dm[2 * w + 1];
            }
        }
        if (r->blk_kx[b] == i + 1) r->blk_kx[b] = 0;
        for (uint32_t k = 0; k < 64; k++) {
            uint32_t w = (uint32_t)b * 64u + k;
            dm[2 * w] = dm[2 * w + 1] = 0;
        }
    }
    x.epoch = 0;
    r->kx_made++;
}
/* the kept block b: its words (made now if its transfer is still waiting) */
static const KBlk *kblk_of(gpu_renderer *r, uint32_t b)
{
    if (!r->blk_owner[b]) return NULL;
    const KBlk *kb = r->kblk[b];
    if ((!kb || kb->epoch != r->blk_epoch[b]) && r->blk_kx[b]) {
        uint32_t i = r->blk_kx[b] - 1u;
        if (i < r->kx.size() && r->kx[i].epoch == r->blk_epoch[b]) kx_make(r, i);
        kb = r->kblk[b];
    }
    return kb && kb->epoch == r->blk_epoch[b] ? kb : NULL;
}

static void mem_xfer(gpu_renderer *r, const gs_mem_rect *rc0, const uint8_t *data, uint32_t npx)
{
    gs_mem_rect rc = *rc0;
    int psm = rc.psm, bpp = gs_psm_bpp(psm);
    if (!bpp || !npx || !rc.w || !rc.h) return;
    if (rc.bw == 0) rc.bw = 1;
    uint64_t total = (uint64_t)rc.w * rc.h;
    if (npx > total) npx = (uint32_t)total;
    double t0 = now_us();
    uint32_t bytes = (uint32_t)(((uint64_t)npx * (uint32_t)bpp + 7) / 8);
    uint32_t rows = (npx + rc.w - 1) / rc.w;
    Pages tp = xfer_pages(rc, rows);
    uint32_t key[7] = { rc.bp, rc.bw, (uint32_t)psm, rc.x, rc.y, rc.w, rc.h };
    uint64_t kh = fnv64((const uint8_t *)key, sizeof key);
    uint32_t slot = (uint32_t)(kh % 4096u);
    if (r->elide.empty()) r->elide.resize(4096);
    /* (the bytes' hash is also the blocks' content key: always) */
    int seen = r->elide[slot].used && !memcmp(r->elide[slot].key, key, sizeof key);
    uint64_t h = fnv64(data, bytes) ^ (kh * 31u);
    r->x_n++;
    r->x_bytes += bytes;
    if (!r->no_elide && npx == total && seen && r->elide[slot].hash == h) {
        /* the same bytes into the same rectangle, none of its blocks written since and no target
         * holding newer pixels there: the mirror already holds exactly these bytes */
        Elide &e = r->elide[slot];
        bool ok = true;
        for (uint16_t b : e.blocks)
            if (r->blk_epoch[b] != e.epoch) { ok = false; break; }
        if (ok)
            for (const Rt &t : r->rts)
                if (t.has_dirty && t.pages.overlaps(tp)) { ok = false; break; }
        if (ok) {
            r->x_elided++;
            r->x_elided_bytes += bytes;
            r->x_us += now_us() - t0;
            return;
        }
    }
    double tB = now_us(); r->x_t[0] += tB - t0;
    /* targets holding newer pixels there go to the mirror first (the transfer's bits then land
     * over them) */
    for (Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(tp)) rt_writeback(r, t);
    double tC = now_us(); r->x_t[1] += tC - tB;
    /* the blocks of the rectangle (its formats' block grid) and whether the transfer writes every
     * bit of each (the content key: a whole block is the transfer's alone) */
    static std::vector<uint8_t> btouch;
    static std::vector<uint16_t> blist;
    static std::vector<uint8_t> bfull;
    if (btouch.empty()) btouch.assign(16384, 0);
    if (r->pend_on.empty()) r->pend_on.assign(16384, 0);
    blist.clear();
    bfull.clear();
    const BlkTab *bt = blk_tab(psm);
    const uint32_t bwk = bt->bwk, bhk = bt->bhk, full_rows = npx / rc.w;
    const int fullfmt = !(psm == GS_PSMCT24 || psm == GS_PSMZ24 || psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH);
    int clash = 0;
    for (uint32_t yb = rc.y & ~(bhk - 1); yb < rc.y + rows; yb += bhk)
        for (uint32_t xb = rc.x & ~(bwk - 1); xb < rc.x + rc.w; xb += bwk) {
            uint32_t b = (nr_px_addr(psm, rc.bp, rc.bw, xb & 2047u, yb & 2047u, NULL) >> 8) & 16383u;
            int full = fullfmt && xb >= rc.x && xb + bwk <= rc.x + rc.w && yb >= rc.y && yb + bhk <= rc.y + full_rows;
            if (btouch[b]) continue;   /* (a rectangle that wraps at 2048) */
            btouch[b] = 1;
            blist.push_back((uint16_t)b);
            bfull.push_back((uint8_t)full);
            clash |= r->pend_on[b];
        }
    if (clash) mem_flush(r);   /* (a block of a pending transfer: that one lands first) */
    if (bytes + 3u <= GpuBackend::XFER_BYTES) {
        xb_add(r, rc, rc.y, data, bytes, npx);
    } else {
        /* larger than a batch: runs of rows (an even number: 4-bit rows may end mid-byte) */
        uint32_t rb = (uint32_t)(((uint64_t)rc.w * (uint32_t)bpp + 7) / 8);
        uint32_t chunk = (GpuBackend::XFER_BYTES / 2u) / (rb ? rb : 1u);
        if (chunk < 2) chunk = 2;
        chunk &= ~1u;
        for (uint32_t y0 = 0; y0 < rows; y0 += chunk) {
            uint32_t n = rows - y0 < chunk ? rows - y0 : chunk, p0 = y0 * rc.w;
            uint32_t np = (uint32_t)((uint64_t)n * rc.w < npx - p0 ? (uint64_t)n * rc.w : npx - p0);
            uint32_t o = (uint32_t)((uint64_t)p0 * (uint32_t)bpp / 8), nbt = (uint32_t)(((uint64_t)np * (uint32_t)bpp + 7) / 8);
            mem_flush(r);
            xb_add(r, rc, (rc.y + y0) & 2047u, data + o, nbt, np);
        }
    }
    for (uint16_t b : blist)
        if (!r->pend_on[b]) { r->pend_on[b] = 1; r->pend.push_back(b); }
    double tD = now_us(); r->x_t[2] += tD - tC;
    /* blocks: epoch, owner, content key; the words of small palette-format transfers kept */
    uint32_t ep = ++r->epoch;
    int keep = bytes <= 1024u && (psm == GS_PSMCT32 || psm == GS_PSMCT16 || psm == GS_PSMCT16S) && !r->no_cpu_clut;
    uint32_t *dm = NULL;
    int lazy = keep && !r->keep_eager && blist.size() <= 16;
    if (lazy) {
        /* kept as it came: the words when a CLUT load reads it (kblk_of) */
        if (r->kx.empty()) r->kx.resize(KX_N);
        uint32_t i = r->kx_next++ % (uint32_t)KX_N;
        KXfer &x = r->kx[i];
        if (x.epoch) {
            /* the slot's transfer: its words now if a block still holds it */
            int live = 0;
            for (uint16_t k = 0; k < x.nb; k++) {
                uint16_t b = x.blk[k];
                if (r->blk_owner[b] && r->blk_epoch[b] == x.epoch && r->blk_kx[b] == i + 1) live = 1;
            }
            if (live) { kx_make(r, i); r->kx_evict_made++; }
            else
                for (uint16_t k = 0; k < x.nb; k++)
                    if (r->blk_kx[x.blk[k]] == i + 1) r->blk_kx[x.blk[k]] = 0;
        }
        x.epoch = ep;
        x.rc = rc;
        x.npx = npx;
        x.nb = (uint16_t)blist.size();
        for (size_t k = 0; k < blist.size(); k++) x.blk[k] = blist[k];
        memcpy(x.data, data, bytes);
        for (uint16_t b : blist) r->blk_kx[b] = (uint16_t)(i + 1);
        keep = 0;
    }
    if (keep) {
        static std::vector<uint16_t> kl;
        if (r->dm.empty()) r->dm.assign((size_t)GS_VRAM_BYTES / 2u, 0u);   /* (data, mask) per word; zero between uses */
        dm = r->dm.data();
        kl.clear();
        static std::vector<uint8_t> kt;
        if (kt.empty()) kt.assign(16384, 0);
        switch (bpp) {
        case 32: xfer_fill<32>(rc, psm, data, npx, dm, kt.data(), kl); break;
        default: xfer_fill<16>(rc, psm, data, npx, dm, kt.data(), kl); break;
        }
        for (uint16_t b : kl) kt[b] = 0;
    }
    uint32_t h32 = (uint32_t)h ^ (uint32_t)(h >> 32);
    for (size_t i = 0; i < blist.size(); i++) {
        uint16_t b = blist[i];
        btouch[b] = 0;
        blk_release(r, b);
        r->blk_epoch[b] = ep;
        if (lazy) r->blk_owner[b] = 1;
        else if (r->blk_kx[b]) r->blk_kx[b] = 0;
        if (keep) {
            KBlk *kb = r->kblk[b];
            if (!kb) kb = r->kblk[b] = new KBlk;
            kb->epoch = ep;
            for (uint32_t k = 0; k < 64; k++) {
                uint32_t w = (uint32_t)b * 64u + k;
                kb->d[k] = dm[2 * w];
                kb->m[k] = dm[2 * w + 1];
                dm[2 * w] = dm[2 * w + 1] = 0;
            }
            r->blk_owner[b] = 1;
        }
        r->blk_key[b] = bfull[i] ? (mix32(mix32(h32, b), 0x51ED27u) & ~1u) : (mix32(mix32(r->blk_key[b], h32), b) | 1u);
    }
    if (keep || lazy) r->x_kept++;
    if (npx == total) {
        Elide &e = r->elide[slot];
        memcpy(e.key, key, sizeof key);
        e.hash = h;
        e.epoch = ep;
        e.blocks = blist;
        e.used = 1;
    }
    double tE = now_us(); r->x_t[3] += tE - tD;
    mirror_written(r, tp);
    r->drawn.sub(tp);   /* uploaded data (item 8, tex_pages_ordinary) */
    r->stats.upload_bytes += bytes;
    r->x_t[4] += now_us() - tE;
    r->x_us += now_us() - t0;
}

/* the CLUT cell values a load would write (gs_tex.c gs_tex0_written's arithmetic) from the
 * words of the kept transfers that were the last write of every block the palette lies in;
 * 0 when one of them is not CPU-known */
static int clut_cpu_values(gpu_renderer *r, const gs_mem_rect *rc, int csm, uint32_t csa, int cpsm, uint32_t n,
                           uint16_t *cells)
{
    int is32 = cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24;
    for (uint32_t i = 0; i < n; i++) {
        uint32_t x, y, bw;
        if (csm == 0) {
            bw = 1;
            if (n == 256) { uint32_t q = (i & 0xE7u) | ((i & 8u) << 1) | ((i & 0x10u) >> 1); x = q & 15u; y = q >> 4; }
            else { x = i & 7u; y = i >> 3; }
        } else {
            bw = rc->bw ? rc->bw : 1; x = rc->x + i; y = rc->y;
        }
        uint32_t w, m, sh;
        nr_px_word(rc->psm, rc->bp, bw, x, y, &w, &m, &sh);
        uint32_t b = w >> 6;
        const KBlk *kb = kblk_of(r, b);
        if (!kb || (kb->m[w & 63u] & m) != m) return 0;
        uint32_t c = (kb->d[w & 63u] & m) >> sh;
        if (is32 && csm == 0) {
            uint32_t e = ((csa & 15u) * 16u + i) & 255u;
            cells[e] = (uint16_t)c;
            cells[e + 256] = (uint16_t)(c >> 16);
        } else {
            cells[(csa * 16u + i) & 511u] = (uint16_t)c;
        }
    }
    return 1;
}

static int clut_load(gpu_renderer *r, gpu_gs *gs, const gs_mem_rect *rc, int csm, uint32_t csa, int cpsm, uint32_t n,
                     int dry)
{
    Pages p = pages_of_rect(rc);
    /* targets with newer pixels in the palette's pages first (the block epochs then say whether
     * a kept transfer still holds the palette) */
    for (Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(p)) rt_writeback(r, t);
    uint16_t cells[512];
    memcpy(cells, gs->clut, sizeof cells);
    if (!r->no_cpu_clut && rc->w && clut_cpu_values(r, rc, csm, csa, cpsm, n, cells)) {
        int changed = memcmp(cells, gs->clut, sizeof cells) != 0;
        if (dry) {
            if (!changed && r->clut_own_any) {
                uint8_t w[256];
                memset(w, 0, sizeof w);
                clut_words(csm, csa, cpsm, n, w, 1);
                for (int i = 0; i < 256; i++) if (w[i] && r->clut_own[i]) return 1;   /* GPU-owned cells become the CPU's */
            }
            return changed;
        }
        memcpy(gs->clut, cells, sizeof cells);
        if (r->clut_own_any) {
            uint8_t before[256];
            memcpy(before, r->clut_own, sizeof before);
            clut_words(csm, csa, cpsm, n, r->clut_own, 0);
            r->clut_own_any = 0;
            for (int i = 0; i < 256; i++) r->clut_own_any |= r->clut_own[i];
            if (memcmp(before, r->clut_own, sizeof before)) { r->clut_force = 1; changed = 1; }
        }
        r->clut_cpu++;
        return changed;
    }
    if (dry) { r->clut_dry_gpu++; return 2; }
    int is32 = cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24;
    uint32_t u[3][4] = { { rc->bp, (uint32_t)rc->psm, (uint32_t)csm, csa },
                         { n, (uint32_t)is32, rc->bw, rc->x / 16u },
                         { rc->y, 0, 0, 0 } };
    mem_flush(r);
    if (!r->be->clut_load_gpu(u)) return 0;
    clut_words(csm, csa, cpsm, n, r->clut_own, 1);
    r->clut_own_any = 1;
    r->clut_seen_loads = gs->stats.clut_loads;   /* gs->clut did not change: the generation by hand */
    r->clut_gen_id++;
    r->clut_uploaded_gen = r->clut_gen_id;       /* the buffer holds it */
    r->clut_valid = 1;
    r->clut_gpu_n++;
    r->stats.clut_gpu++;
    return 2;
}

/* Probe lag (gpu_config.probe_lag; docs/NATIVE-THREADS.md "3h").  A probe group = the reads
 * between two writes to local memory (GfxEndFrame's four 8x8 Z reads of one frame).  Each read
 * takes a copy of its rectangle's page neighbourhood (12 px around it: at most 2 x 2 pages) for
 * the NEXT group, and is served from the previous group's copy when one holds all its pages
 * (else from its own copy, waiting: exact).  Probe reads never become HotRead entries (their
 * per-batch early copies would recycle the staging slots under the kept copies).
 * Deterministic (a function of the draw stream); the copy is a frame old when mapped, so the
 * map does not wait for the frame being drawn. */
static uint64_t lag_gen(const gpu_renderer *r) { return r->stats.batches + r->x_n + r->l2l_n + 1; }

static bool pages_within(const Pages &a, const Pages &b)
{
    for (int i = 0; i < 16; i++) if (a.w[i] & ~b.w[i]) return false;
    return true;
}

static int lag_serve(gpu_renderer *r, const LagRead &e, std::vector<uint8_t> &mem, int16_t *off)
{
    double t0 = now_us();
    const uint8_t *m = r->be->snap_map(e.slot);
    if (m) {
        int n = 0;
        for (uint32_t pg = 0; pg < 512; pg++) off[pg] = e.pages.get(pg) ? (int16_t)n++ : (int16_t)-1;
        mem.resize((size_t)n * 8192u);
        memcpy(mem.data(), m, (size_t)n * 8192u);
        r->be->snap_unmap(e.slot);
    }
    r->stats.download_us += (uint64_t)(now_us() - t0);
    return m != NULL;
}

static bool lag_live(const gpu_renderer *r, const LagRead &e)
{
    return e.used && e.slot >= 0 && e.slot < GpuBackend::SNAP_SLOTS && r->snap_slot_serial[e.slot] == e.serial;
}

static int lag_read(gpu_renderer *r, const gs_mem_rect *rc, const Pages &p, std::vector<uint8_t> &mem, int16_t *off)
{
    uint64_t g = lag_gen(r);
    if (g != r->lag_cur) { r->lag_prev = r->lag_cur; r->lag_cur = g; }
    int served = 0;
    for (LagRead &e : r->lag)
        if (e.gen == r->lag_prev && lag_live(r, e) && pages_within(p, e.pages)) {
            served = lag_serve(r, e, mem, off);
            break;
        }
    if (served) r->lag_hits++;
    /* the copy for the next group (also this read's, when the previous group had none) */
    int x0 = (int)rc->x - 12, y0 = (int)rc->y - 12;
    Pages pe = pages_of(rc->bp, rc->bw, rc->psm, x0 < 0 ? 0 : x0, y0 < 0 ? 0 : y0, (int)(rc->x + rc->w) + 12,
                        (int)(rc->y + rc->h) + 12);
    int npe = 0;
    for (int i = 0; i < 16; i++) for (uint32_t m = pe.w[i]; m; m &= m - 1) npe++;
    if (npe > 4 || !pages_within(p, pe)) pe = p;
    LagRead *cur = NULL;
    for (LagRead &e : r->lag)
        if (e.gen == g && lag_live(r, e) && pages_within(pe, e.pages)) { cur = &e; break; }
    if (!cur) {
        LagRead *v = NULL;
        for (LagRead &e : r->lag) {
            if (!e.used) { v = &e; break; }
            if (e.gen == g) continue;
            if (!v || e.gen < v->gen) v = &e;
        }
        if (v) {
            HotRead h = {};
            h.pages = pe;
            h.slot = -1;
            hot_snapshot(r, h);   /* write-backs of the targets on those pages + the copy (no wait) */
            v->used = h.state == 1;
            v->pages = pe;
            v->slot = h.slot;
            v->serial = h.slot >= 0 && h.slot < GpuBackend::SNAP_SLOTS ? r->snap_slot_serial[h.slot] : 0;
            v->gen = g;
            if (v->used) { r->lag_copies++; cur = v; }
        }
    }
    if (!served && cur) {
        /* no copy from the previous group: this group's copy, now (waits, exact) */
        served = lag_serve(r, *cur, mem, off);
        if (served) r->lag_misses++;
    }
    return served;
}

/* local->host: rc's pixels from an early copy of its pages when one is valid (the pages
 * unchanged since), else written back and copied now (waits for the GPU) */
static int mem_read(gpu_renderer *r, const gs_mem_rect *rc, uint8_t *out, uint32_t cap)
{
    Pages p = pages_of_rect(rc);
    int np = 0;
    for (int i = 0; i < 16; i++) for (uint32_t m = p.w[i]; m; m &= m - 1) np++;
    static std::vector<uint8_t> mem;   /* the pages read, in page order */
    static int16_t off[512];
    const uint8_t *src = NULL;
    if (r->probe_lag && np <= 4 && (rc->psm & 0x30) == 0x30 && rc->w <= 16 && rc->h <= 16 &&
        lag_read(r, rc, p, mem, off))
        src = mem.data();
    if (!src && np <= 4) {
        HotRead *h = NULL;
        for (HotRead &x : r->hot)
            if (x.used && x.rc.bp == rc->bp && x.rc.bw == rc->bw && x.rc.psm == rc->psm && x.rc.x == rc->x &&
                x.rc.y == rc->y && x.rc.w == rc->w && x.rc.h == rc->h) { h = &x; break; }
        if (!h) {
            HotRead *v = &r->hot[0];
            for (HotRead &x : r->hot) if (!x.used || x.last < v->last) { v = &x; if (!x.used) break; }
            v->used = 1;
            v->rc = *rc;
            v->pages = p;
            v->state = 0;
            v->slot = -1;
            h = v;
        }
        h->last = ++r->hot_tick;
        if (h->state != 1 || r->no_early) hot_snapshot(r, *h);
        double t0 = now_us();
        const uint8_t *m = h->state == 1 ? r->be->snap_map(h->slot) : NULL;
        if (m) {
            mem.resize((size_t)np * 8192u);
            memcpy(mem.data(), m, (size_t)np * 8192u);
            r->be->snap_unmap(h->slot);
            r->stats.early_reads++;
            int k = 0;
            for (uint32_t pg = 0; pg < 512; pg++) off[pg] = p.get(pg) ? (int16_t)k++ : (int16_t)-1;
            src = mem.data();
        }
        r->stats.download_us += (uint64_t)(now_us() - t0);
        if (r->no_early) h->state = 0;
    }
    if (!src) {
        /* larger regions: written back and read back (no reader in the game so far) */
        for (Rt &t : r->rts)
            if (t.has_dirty && t.pages.overlaps(p)) rt_writeback(r, t);
        static std::vector<uint8_t> all;
        all.resize(GS_VRAM_BYTES);
        uint32_t runs[1024];
        int n = 0, k = 0;
        for (uint32_t pg = 0; pg < 512;) {
            if (!p.get(pg)) { pg++; continue; }
            uint32_t e = pg;
            while (e < 512 && p.get(e)) e++;
            runs[2 * n] = pg * 8192u;
            runs[2 * n + 1] = (e - pg) * 8192u;
            n++;
            pg = e;
        }
        double t0 = now_us();
        mem_flush(r);
        r->be->mirror_download(runs, n, all.data());
        r->stats.download_us += (uint64_t)(now_us() - t0);
        r->stats.downloads++;
        mem.resize((size_t)np * 8192u);
        for (uint32_t pg = 0; pg < 512; pg++) {
            off[pg] = -1;
            if (p.get(pg)) { memcpy(mem.data() + (size_t)k * 8192u, all.data() + (size_t)pg * 8192u, 8192u); off[pg] = (int16_t)k++; }
        }
        src = mem.data();
    }
    int bpp = gs_psm_bpp(rc->psm);
    uint32_t at = 0, nib_acc = 0, nib_n = 0;
    uint32_t bw = rc->bw ? rc->bw : 1;
    auto push = [&](uint8_t b) { if (at < cap) out[at] = b; at++; };
    for (uint32_t j = 0; j < rc->h; j++)
        for (uint32_t i = 0; i < rc->w; i++) {
            uint32_t w, m, sh;
            nr_px_word(rc->psm, rc->bp, bw, (rc->x + i) & 2047u, (rc->y + j) & 2047u, &w, &m, &sh);
            uint32_t pg = w >> 11, word = 0;
            if (off[pg] >= 0) memcpy(&word, src + (size_t)off[pg] * 8192u + (w & 2047u) * 4u, 4);
            uint32_t v = (word & m) >> sh;
            switch (bpp) {
            case 32: push((uint8_t)v); push((uint8_t)(v >> 8)); push((uint8_t)(v >> 16)); push((uint8_t)(v >> 24)); break;
            case 24: push((uint8_t)v); push((uint8_t)(v >> 8)); push((uint8_t)(v >> 16)); break;
            case 16: push((uint8_t)v); push((uint8_t)(v >> 8)); break;
            case 8: push((uint8_t)v); break;
            case 4:
                nib_acc |= (v & 15u) << (nib_n * 4);
                if (++nib_n == 2) { push((uint8_t)nib_acc); nib_acc = 0; nib_n = 0; }
                break;
            default: break;
            }
        }
    if (nib_n) push((uint8_t)nib_acc);
    while (at < cap) out[at++] = 0;   /* (the FIFO hands out whole quadwords) */
    r->l2h_n++;
    return 0;
}

static void mem_copy(gpu_renderer *r, const gs_mem_rect *s, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t dx, uint32_t dy)
{
    gs_mem_rect d;
    d.bp = dbp; d.bw = dbw ? dbw : 1; d.psm = dpsm; d.x = dx; d.y = dy; d.w = s->w; d.h = s->h;
    Pages sp = xfer_pages(*s, s->h), dp = xfer_pages(d, d.h), both = sp;
    both.add(dp);
    for (Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(both)) rt_writeback(r, t);
    uint32_t u[3][4] = { { s->bp, s->bw ? s->bw : 1, (uint32_t)s->psm, s->x }, { s->y, s->w, s->h, dbp },
                         { d.bw, (uint32_t)dpsm, dx, dy } };
    mem_flush(r);
    if (!r->be->mem_copy(u)) return;
    GpuRect dr = { (int)dx, (int)dy, (int)(dx + s->w), (int)(dy + s->h) };
    blk_write_gpu(r, dbp, d.bw, dpsm, dr);
    mirror_written(r, dp);
    r->l2l_n++;
}

/* ============================================================ public */
extern "C" {


void gpu_config_default(gpu_config *c)
{
    memset(c, 0, sizeof *c);
    c->scale = 1;
}

gpu_renderer *gpu_create(const gpu_config *cfg, char *err, size_t errcap)
{
    gpu_config c;
    if (cfg) c = *cfg;
    else gpu_config_default(&c);
    if (c.scale < 1) c.scale = 1;
    if (c.scale > 8) c.scale = 8;
    {
        const char *nr = getenv("RG_GPU_NO_ROV");
        if (nr && nr[0] == '1') c.no_rov = 1;
        const char *nd = getenv("RG_GPU_NO_DECODE");
        if (nd && nd[0] == '1') c.no_tex_decode = 1;
        const char *rl = getenv("RG_GPU_READBACK_LAG");
        if (rl && rl[0] == '1') c.readback_lag = 1;
        const char *pl = getenv("RG_GPU_PROBE_LAG");
        if (pl && (pl[0] == '0' || pl[0] == '1')) c.probe_lag = pl[0] == '1';
        const char *nz = getenv("RG_GPU_NO_ZROV");
        if (nz && nz[0] == '1') c.no_zrov = 1;
    }
    if (c.no_rov) c.no_zrov = 1;
    GpuBackend *be = NULL;
    RG_X64_VA_FENCE(1);
#ifdef RG_HAVE_VULKAN
    {
        /* the Vulkan backend (docs/NATIVE-VULKAN.md): display.backend (gpu_config.api) or
         * $RG_GPU_API=vulkan; without a usable Vulkan 1.3 device the run continues on D3D11
         * (Windows; elsewhere Vulkan is the only backend) */
        const char *api = getenv("RG_GPU_API");
        if (api && *api) c.api = !strcmp(api, "vulkan") || !strcmp(api, "vk") ? 1 : 0;
#if !defined(_WIN32)
        c.api = 1;
#endif
        if (c.api == 1) {
            be = gpu_backend_vulkan_create(&c, c.scale, err, errcap);
            if (be) fprintf(stderr, "rg gpu: %s\n", be->name());
#if defined(_WIN32)
            else fprintf(stderr, "rg gpu: Vulkan backend unavailable (%s); using Direct3D 11\n", err);
#endif
        }
    }
#endif
#if defined(_WIN32)
    if (!be) be = gpu_backend_d3d11_create(&c, c.scale, err, errcap);
#endif
    RG_X64_VA_FENCE(0);
    if (!be) return NULL;
    gpu_renderer *r = new gpu_renderer();
    r->rp_c = r->rp_z = -1;
    r->cfg = c;
    r->scale = c.scale;
    r->be = be;
    r->gs = NULL;
    memset(&r->stats, 0, sizeof r->stats);
    r->clut_valid = 0;
    r->clut_uploaded_gen = 0;
    r->clut_seen_loads = ~0ull;
    r->clut_gen_id = 1;
    memset(r->clut_copy, 0, sizeof r->clut_copy);
    memset(&r->enh, 0, sizeof r->enh);
    {
        /* measurement ($RG_GPU_ANISO=N): anisotropic taps from the start, for
         * renderer-only replays; a program's gpu_set_enhance replaces it */
        const char *an = getenv("RG_GPU_ANISO");
        if (an) r->enh.aniso = atoi(an);
    }
    memset(r->page_stamp, 0, sizeof r->page_stamp);
    r->stamp = 0;
    r->kick_px = 0.0;
    r->kick_at = 262144.0;
    {
        const char *kp = getenv("RG_GPU_KICK_PX");   /* measurement: 0 = never */
        if (kp) r->kick_at = atof(kp);
        const char *nel = getenv("RG_GPU_NO_ELIDE");   /* control: no redundant upload elision */
        r->no_elide = nel && nel[0] == '1';
        const char *ncc = getenv("RG_NR_CPUCLUT");     /* control: 0 = every CLUT load on the GPU */
        r->no_cpu_clut = ncc && ncc[0] == '0';
        {
            const char *ke = getenv("RG_NR_KEEP_EAGER");   /* control: kept transfers made into words at once */
            r->keep_eager = ke && ke[0] == '1';
        }
        const char *fc = getenv("RG_NR_IMFB_CENSUS");
        r->fb_census = fc && fc[0] == '1';
        const char *as = getenv("RG_NR_ASAT");
        r->no_asat = as && as[0] == '0';
        const char *fr = getenv("RG_NR_FBRECT");
        r->no_fbrect = fr && fr[0] == '0';
        const char *gl = getenv("RG_NR_GSLIN");
        r->no_gslin = gl && gl[0] == '0';
        const char *ne = getenv("RG_GPU_NO_EARLY_READ");
        r->no_early = (ne && ne[0] == '1') || r->cfg.fault == 15;
        const char *tr = getenv("RG_GPU_TRACE");     /* measurement: every batch and memory op */
        r->trace = tr && tr[0] ? fopen(tr, "w") : NULL;
        if (r->trace) setvbuf(r->trace, NULL, _IONBF, 0);
        const char *rl2 = getenv("RG_GPU_RT_LOG");   /* measurement: target creates / drops */
        r->rt_log = rl2 && rl2[0] ? fopen(rl2, "w") : NULL;
        const char *rpc = getenv("RG_GPU_RT_PAGECOPY");   /* control: 0 = drop + 1x reload (pre item 8) */
        r->no_rt_pagecopy = rpc && rpc[0] == '0';
        const char *trt = getenv("RG_NR_TEXRT");      /* control: overlap = the pre-item-8 rule */
        r->texrt_overlap = trt && trt[0] == 'o';
        const char *flg = getenv("RG_NR_FILTLOG");    /* measurement: per native draw filter choice */
        r->filt_log = flg && flg[0] ? fopen(flg, "w") : NULL;
    }
    r->probe_lag = c.probe_lag && !r->no_early;
    r->rov = be->rov();
    r->zrov = r->rov && be->zrov();
    snprintf(r->name, sizeof r->name, "%s (native device)", be->name());
    return r;
}

void gpu_destroy(gpu_renderer *r)
{
    if (!r) return;
    if (r->fb_census) {
        std::vector<std::pair<uint64_t, std::tuple<int, uint64_t, uint64_t>>> v;
        for (auto &e : r->fbc) v.push_back(std::make_pair(e.second, e.first));
        std::sort(v.begin(), v.end(), [](const std::pair<uint64_t, std::tuple<int, uint64_t, uint64_t>> &a,
                                         const std::pair<uint64_t, std::tuple<int, uint64_t, uint64_t>> &b) { return a.first > b.first; });
        for (size_t i = 0; i < v.size() && i < 40; i++)
            fprintf(stderr, "nr im fallback census: %llu prims why %d FRAME %016llX TEX0 %016llX\n", (unsigned long long)v[i].first,
                    std::get<0>(v[i].second), (unsigned long long)std::get<1>(v[i].second), (unsigned long long)std::get<2>(v[i].second));
    }
    gpu_mem_stats(r, stderr);
    if (r->trace) fclose(r->trace);
    if (r->rt_log) fclose(r->rt_log);
    if (r->filt_log) fclose(r->filt_log);
    for (Rt &t : r->rts) r->be->rt_destroy(t.id);
    for (uint32_t b = 0; b < 16384; b++) delete r->kblk[b];
    replay_free(r);
    delete r->be;
    delete r;
}

void gpu_mem_stats(const gpu_renderer *r, FILE *f)
{
    if (!r || !f) return;
    fprintf(f, "native device memory: transfers %llu (%llu KB), elided %llu (%llu KB), words kept %llu, merged %llu KB, %.1f ms; "
               "CLUT loads from transfer bytes %llu, on the GPU %llu (dry %llu); local->local %llu, local->host %llu "
               "(early %llu, read-backs %llu, %.1f ms wait)\n",
            (unsigned long long)r->x_n, (unsigned long long)(r->x_bytes >> 10), (unsigned long long)r->x_elided,
            (unsigned long long)(r->x_elided_bytes >> 10), (unsigned long long)r->x_kept,
            (unsigned long long)(r->x_merge_words >> 8), r->x_us / 1000.0, (unsigned long long)r->clut_cpu,
            (unsigned long long)r->clut_gpu_n, (unsigned long long)r->clut_dry_gpu, (unsigned long long)r->l2l_n,
            (unsigned long long)r->l2h_n, (unsigned long long)r->stats.early_reads, (unsigned long long)r->stats.downloads,
            r->stats.download_us / 1000.0);
    if (r->probe_lag)
        fprintf(f, "native device probe lag: %llu reads served a group late, %llu read exactly (no previous copy), %llu copies\n",
                (unsigned long long)r->lag_hits, (unsigned long long)r->lag_misses, (unsigned long long)r->lag_copies);
    fprintf(f, "native device memory time: pixels %.1f ms, uploads %.1f ms (%llu flushes); kept transfers made into words %llu (at slot reuse %llu)\n",
            r->x_us_px / 1000.0, r->x_us_up / 1000.0, (unsigned long long)r->x_flushes, (unsigned long long)r->kx_made,
            (unsigned long long)r->kx_evict_made);
    if (r->x_batch_fail) fprintf(f, "native device: transfer batches the backend refused %llu\n", (unsigned long long)r->x_batch_fail);
    fprintf(f, "native device transfer sections ms: setup %.0f writeback %.0f fill %.0f blocks %.0f tail %.0f\n", r->x_t[0] / 1000.0,
            r->x_t[1] / 1000.0, r->x_t[2] / 1000.0, r->x_t[3] / 1000.0, r->x_t[4] / 1000.0);
    fprintf(f, "native device draws: meshes pre-warmed %llu, uploaded on the worker %llu; immediate primitives through the ordered "
               "colour view %llu (As > 0x80: %llu, of them texel alpha %llu); drawn natively where the oracle uses the GS draw path:",
            (unsigned long long)r->be->n_nr_mesh_pre, (unsigned long long)r->be->n_nr_mesh,
            (unsigned long long)r->im_crov_prims, (unsigned long long)r->im_asat_prims, (unsigned long long)r->im_asat_tex_prims);
    static const char *nm[12] = { "CT16 frame", "dest. alpha test", "partial FBMSK", "AFAIL", "blend C=Ad",
                                  "COLCLAMP/PABE/SCANMSK", "frame-Z alias", "texture feedback", "mipmaps",
                                  "region clamp", "depth texture", "backend" };
    for (int k = 0; k < 12; k++)
        if (r->im_approx[k]) fprintf(f, " %s %llu", nm[k], (unsigned long long)r->im_approx[k]);
    fprintf(f, " (feedback primitives one by one %llu)\n", (unsigned long long)r->im_fb_split);
    if (reint_on())
        fprintf(f, "native device reinterpretations: views sampled %llu, targets bound over another format %llu, "
                   "reads 3-4 texels past a target %llu, refused %llu\n",
                (unsigned long long)g_reint.views, (unsigned long long)g_reint.binds, (unsigned long long)g_reint.margin,
                (unsigned long long)g_reint.refused);
}

const char *gpu_device_name(const gpu_renderer *r) { return r->name; }

int gpu_exact_triangles(const gpu_renderer *r) { (void)r; return 0; }

int gpu_ordered_blend(const gpu_renderer *r) { return r->rov; }
int gpu_ordered_depth(const gpu_renderer *r) { return r->zrov; }

/* the native state block the device works with (its registers, CLUT cells, display registers) */
void gpu_attach(gpu_renderer *r, gpu_gs *gs)
{
    r->gs = gs;
    for (Rt &t : r->rts) r->be->rt_destroy(t.id);
    r->rts.clear();
    r->clut_valid = 0;
    r->clut_seen_loads = ~0ull;
    r->clut_gen_id++;
    memset(r->clut_own, 0, sizeof r->clut_own);   /* gs->clut is the truth again */
    r->clut_own_any = 0;
}

void gpu_detach(gpu_renderer *r) { r->gs = NULL; }

gpu_gs *gpu_attached_state(const gpu_renderer *r) { return r->gs; }

void gpu_flush(gpu_renderer *r) { (void)r; }

/* every target written back into the mirror (the CPU never holds local memory natively) */
void gpu_sync(gpu_renderer *r)
{
    clut_resolve(r);
    for (Rt &t : r->rts) rt_writeback(r, t);
}

void gpu_mem_written(gpu_renderer *r, const gs_mem_rect *rc) { (void)r; (void)rc; }

void gpu_mem_xfer(gpu_renderer *r, const gs_mem_rect *rc, const uint8_t *data, uint32_t npx) { mem_xfer(r, rc, data, npx); }

void gpu_mem_copy(gpu_renderer *r, const gs_mem_rect *src, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t dx, uint32_t dy)
{
    mem_copy(r, src, dbp, dbw, dpsm, dx, dy);
}

int gpu_mem_read(gpu_renderer *r, const gs_mem_rect *rc, uint8_t *out, uint32_t bytes) { return mem_read(r, rc, out, bytes); }

int gpu_clut_load(gpu_renderer *r, gpu_gs *gs, const gs_mem_rect *rc, int csm, uint32_t csa, int cpsm, uint32_t n, int dry)
{
    return clut_load(r, gs, rc, csm, csa, cpsm, n, dry);
}

int gpu_mem_save(gpu_renderer *r, uint8_t *out)
{
    gpu_sync(r);
    uint32_t runs[2] = { 0, GS_VRAM_BYTES };
    mem_flush(r);
    r->be->mirror_download(runs, 1, out);
    r->stats.downloads++;
    return 0;
}

void gpu_mem_load(gpu_renderer *r, const uint8_t *in)
{
    for (Rt &t : r->rts) r->be->rt_destroy(t.id);
    r->rts.clear();
    mem_flush(r);
    r->be->mirror_upload(0, GS_VRAM_BYTES, in);
    for (Elide &e : r->elide) e.used = 0;
    uint32_t e = ++r->epoch;
    for (uint32_t b = 0; b < 16384; b++) {
        r->blk_owner[b] = 0;
        r->blk_kx[b] = 0;
        r->blk_epoch[b] = e;
        r->blk_key[b] = mix32(mix32(0x7F4A7C15u, e), b) | 1u;
    }
    for (KXfer &x : r->kx) x.epoch = 0;
    Pages all;
    all.all();
    stamp_pages(r, all);
    for (HotRead &h : r->hot) h.state = 0;
    for (LagRead &l : r->lag) l.used = 0;   /* (probe lag: copies of the memory replaced) */
    r->drawn.clear();
    r->clut_valid = 0;
    r->clut_seen_loads = ~0ull;
    r->clut_gen_id++;
    memset(r->clut_own, 0, sizeof r->clut_own);
    r->clut_own_any = 0;
}

const gpu_stats *gpu_get_stats(const gpu_renderer *r) { return &r->stats; }

int gpu_get_scale(const gpu_renderer *r) { return r->scale; }
void gpu_set_im_xfree(gpu_renderer *r, int on) { if (r) r->im_xfree = on != 0; }

int gpu_read_target(gpu_renderer *r, uint32_t bp, uint32_t bw, int psm, int x, int y, int w,
                    int h, uint32_t *out)
{
    if (!r->gs) return -1;
    for (Rt &t : r->rts)
        if (!t.depth && t.bp == bp && t.bw == bw && t.psm == psm) {
            if (t.stale || x < 0 || y < 0 || w <= 0 || h <= 0 || x + w > t.w || y + h > t.h)
                return -1;
            GpuRect rc = { x, y, x + w, y + h };
            return r->be->rt_read(t.id, rc, out);
        }
    return -1;
}

int gpu_targets(gpu_renderer *r, gpu_target_info *out, int cap)
{
    int n = 0;
    for (const Rt &t : r->rts) {
        if (n < cap) {
            out[n].bp = t.bp; out[n].bw = t.bw; out[n].psm = t.psm;
            out[n].w = (uint32_t)t.w; out[n].h = (uint32_t)t.h;
        }
        n++;
    }
    return n;
}

/* ---- display: same geometry as src/ps2/gs/gs_display.c ---- */
/* the PCRTC registers display reads use: a snapshot (gpu_set_display_regs) or the GS's */
static const uint64_t *disp_preg(const gpu_renderer *r) { return r->disp_preg ? r->disp_preg : r->gs->preg; }

static void circ_get(const uint64_t *preg, int i, int en, int frame_lines, GpuCircuit *c)
{
    uint64_t fb = preg[7 + 2 * i], dp = preg[8 + 2 * i];
    c->en = en;
    c->fbp = BITS(fb, 0, 9) * 32u;
    c->fbw = BITS(fb, 9, 6);
    c->psm = (int)BITS(fb, 15, 5);
    c->dbx = BITS(fb, 32, 11);
    c->dby = BITS(fb, 43, 11);
    int dx = (int)BITS(dp, 0, 12), dy = (int)BITS(dp, 12, 11);
    int magh = (int)BITS(dp, 23, 4) + 1, magv = (int)BITS(dp, 27, 2) + 1;
    int dw = (int)BITS(dp, 32, 12) + 1, dh = (int)BITS(dp, 44, 11) + 1;
    int vu = magv * frame_lines;
    c->w = dw / magh;
    c->h = dh / vu;
    c->ox = dx / magh;
    c->oy = dy / vu;
    c->rt = -1;
    c->rt_scale = 1;
    c->af_hr = 0;
}

/* Native display size of field `field` (the geometry of build_display). */
static int gpu_display_size_field(gpu_renderer *r, int field, uint32_t *w, uint32_t *h)
{
    *w = *h = 0;
    gpu_gs *gs = r->gs;
    if (!gs) return -1;
    const uint64_t *preg = disp_preg(r);
    uint64_t pmode = preg[0], smode2 = preg[2];
    int en1 = (int)BITS(pmode, 0, 1), en2 = (int)BITS(pmode, 1, 1);
    int inter = (int)BITS(smode2, 0, 1), ffmd = (int)BITS(smode2, 1, 1);
    int frame_lines = (inter && ffmd) ? 2 : 1;
    if (!en1 && !en2) return -1;
    GpuCircuit c[2];
    circ_get(preg, 0, en1, frame_lines, &c[0]);
    circ_get(preg, 1, en2, frame_lines, &c[1]);
    int x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    for (int i = 0; i < 2; i++) {
        if (!c[i].en) continue;
        if (c[i].ox < x0) x0 = c[i].ox;
        if (c[i].oy < y0) y0 = c[i].oy;
        if (c[i].ox + c[i].w > x1) x1 = c[i].ox + c[i].w;
        if (c[i].oy + c[i].h > y1) y1 = c[i].oy + c[i].h;
    }
    int W = x1 - x0, H = y1 - y0;
    if (W <= 0 || H <= 0) return -1;
    int fsel = (field >= 0 && inter && !ffmd);
    int OH = fsel ? (H - (field & 1) + 1) / 2 : H;
    *w = (uint32_t)W;
    *h = (uint32_t)OH;
    return 0;
}

/* The PCRTC set-up of field `field` (GS_READ_FRAME or 0/1), as d.  Native
 * size W x OH; returns -1 when nothing is displayed.  Flushes, and makes
 * the circuits' sources current (a live target or the mirror). */
static int build_display(gpu_renderer *r, int field, GpuDisplay &d, int *Wo, int *Ho)
{
    gpu_gs *gs = r->gs;
    if (!gs) return -1;
    const uint64_t *preg = disp_preg(r);
    uint64_t pmode = preg[0], smode2 = preg[2];
    int en1 = (int)BITS(pmode, 0, 1), en2 = (int)BITS(pmode, 1, 1);
    int inter = (int)BITS(smode2, 0, 1), ffmd = (int)BITS(smode2, 1, 1);
    int frame_lines = (inter && ffmd) ? 2 : 1;
    memset(&d, 0, sizeof d);
    circ_get(preg, 0, en1, frame_lines, &d.c[0]);
    circ_get(preg, 1, en2, frame_lines, &d.c[1]);
    if (!en1 && !en2) return -1;
    int x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    for (int i = 0; i < 2; i++) {
        GpuCircuit &c = d.c[i];
        if (!c.en) continue;
        if (c.ox < x0) x0 = c.ox;
        if (c.oy < y0) y0 = c.oy;
        if (c.ox + c.w > x1) x1 = c.ox + c.w;
        if (c.oy + c.h > y1) y1 = c.oy + c.h;
    }
    int W = x1 - x0, H = y1 - y0;
    if (W <= 0 || H <= 0) return -1;
    int fsel = (field >= 0 && inter && !ffmd);
    int OH = fsel ? (H - (field & 1) + 1) / 2 : H;
    int s = r->scale;
    *Wo = W;
    *Ho = OH;
    d.out_w = W; d.out_h = OH; d.scale = s; d.x0 = x0; d.y0 = y0;
    d.field_sel = fsel; d.field = field & 1;
    d.mmod = (int)BITS(pmode, 5, 1);
    d.slbg = (int)BITS(pmode, 7, 1);
    d.alp = BITS(pmode, 8, 8);
    d.bg = BITS(preg[14], 0, 24);
    for (int i = 0; i < 2; i++) {
        GpuCircuit &c = d.c[i];
        if (!c.en || c.w <= 0 || c.h <= 0) continue;
        uint32_t bw = c.fbw ? c.fbw : 1;
        int need_y1 = (int)c.dby + c.h, need_x1 = (int)c.dbx + c.w;
        Rt *t = NULL;
        for (Rt &x : r->rts)
            if (!x.depth && x.bp == c.fbp && x.bw == bw && x.psm == c.psm) { t = &x; break; }
        if (t && !t->stale && need_y1 <= t->h && need_x1 <= t->w) {
            c.rt = t->id;
            c.rt_scale = s;
        } else {
            Pages p = pages_of(c.fbp, bw, c.psm, (int)c.dbx, (int)c.dby, need_x1, need_y1);
            for (Rt &x : r->rts)
                if (x.has_dirty && x.pages.overlaps(p)) rt_writeback(r, x);
            c.rt = -1;
        }
        if (r->rt_log || r->filt_log)
            fprintf(r->filt_log ? r->filt_log : r->rt_log, "S circuit %d fbp %u bw %u psm %02x db %u,%u %dx%d from %s\n", i,
                    c.fbp, bw, c.psm, c.dbx, c.dby, c.w, c.h, c.rt >= 0 ? "target" : "mirror");
    }
    /* Anti-flicker merge (both circuits on the same buffer, one of them a
     * buffer row lower: PMODE 0x7F23 in this game).  At scale 1 that averages
     * rows y and y+1.  At scale > 1, offsetting by a whole native row (s
     * internal rows) shows every upscaled detail twice, s rows apart (thin
     * stars became vertical pairs); the lower circuit is offset by one
     * internal row instead, the same filter at the internal resolution.
     * Scale 1 and the mirror path are unchanged. */
    if (s > 1 && !r->cfg.native_af && d.c[0].en && d.c[1].en && d.c[0].rt >= 0 && d.c[0].rt == d.c[1].rt &&
        d.c[0].dbx == d.c[1].dbx && d.c[0].ox == d.c[1].ox && d.c[0].oy == d.c[1].oy &&
        (d.c[0].dby == d.c[1].dby + 1 || d.c[1].dby == d.c[0].dby + 1)) {
        d.c[d.c[0].dby > d.c[1].dby ? 0 : 1].af_hr = 1;
        r->stats.display_af_hr++;
    }
    return 0;
}

int gpu_read_display(gpu_renderer *r, int field, uint32_t *out, uint32_t out_cap_px,
                     uint32_t *w, uint32_t *h)
{
    *w = *h = 0;
    if (!r->gs) return -1;
    if (r->trace) fprintf(r->trace, "D\n");
    if (r->rt_log) fprintf(r->rt_log, "D\n");
    /* the size first (no coherence work when the buffer is too small) */
    uint32_t nw = 0, nh = 0;
    if (gpu_display_size_field(r, field, &nw, &nh) != 0) return -1;
    int s = r->scale;
    *w = nw * (uint32_t)s;
    *h = nh * (uint32_t)s;
    if ((uint64_t)*w * *h > out_cap_px) return -1;
    GpuDisplay d;
    int W = 0, OH = 0;
    if (build_display(r, field, d, &W, &OH) != 0) return -1;
    r->stats.display_frames++;
    mem_flush(r);
    return r->be->display(d, out);
}

/* the native size build_display would produce (no side effects) */
void gpu_set_display_regs(gpu_renderer *r, const uint64_t *preg) { r->disp_preg = preg; }

int gpu_display_size(gpu_renderer *r, uint32_t *w, uint32_t *h)
{
    return gpu_display_size_field(r, GS_READ_FRAME, w, h);
}

void gpu_post_default(gpu_post *p)
{
    memset(p, 0, sizeof *p);
    p->ssaa = 1;
    p->downsample = GPU_RS_BOX;
    p->gamma = 1.0f;
    p->brightness = 1.0f;
    p->upscale = GPU_RS_BILINEAR;
}

int gpu_post_identity(const gpu_post *p)
{
    return !p || (p->ssaa <= 1 && !p->fxaa && p->sharpen <= 0.0f && p->gamma == 1.0f &&
                  p->brightness == 1.0f && p->output_filter == GPU_OUTF_OFF && p->out_w <= 0);
}

int gpu_present_shared(gpu_renderer *r, int field, const gpu_post *p, void **handle, uint32_t *w,
                       uint32_t *h)
{
    *handle = NULL;
    int rc = gpu_read_output(r, field, p, NULL, 0xFFFFFFFFu, w, h);
    if (rc != 0) return rc;
    *handle = r->be->shared_out();
    return *handle ? 0 : -1;
}

int gpu_vk_present_device(gpu_renderer *r, gpu_vk_device *out)
{
    if (!r || !r->be || !out) return -1;
    memset(out, 0, sizeof *out);
    return r->be->vk_present_device(out) ? 0 : -1;
}

int gpu_read_output(gpu_renderer *r, int field, const gpu_post *p, uint32_t *out,
                    uint32_t out_cap_px, uint32_t *w, uint32_t *h)
{
    if (gpu_post_identity(p)) return gpu_read_display(r, field, out, out_cap_px, w, h);
    *w = *h = 0;
    if (!r->gs) return -1;
    uint32_t nw = 0, nh = 0;
    if (gpu_display_size_field(r, field, &nw, &nh) != 0) return -1;
    int s = r->scale;
    GpuPost pp;
    memset(&pp, 0, sizeof pp);
    int ssaa = p->ssaa < 1 ? 1 : (p->ssaa > 8 ? 8 : p->ssaa);
    /* after supersampling: the display at scale / ssaa (rounded, >= native) */
    int fw = (int)nw * s, fh = (int)nh * s;
    if (ssaa > 1) {
        fw = ((int)nw * s + ssaa / 2) / ssaa;
        fh = ((int)nh * s + ssaa / 2) / ssaa;
        if (fw < (int)nw) fw = (int)nw;
        if (fh < (int)nh) fh = (int)nh;
    }
    pp.ssaa_w = fw; pp.ssaa_h = fh;
    pp.fxaa = p->fxaa;
    pp.sharpen = p->sharpen < 0.0f ? 0.0f : (p->sharpen > 1.0f ? 1.0f : p->sharpen);
    pp.gamma = p->gamma;
    pp.brightness = p->brightness;
    pp.downsample = p->downsample;
    pp.upscale = p->upscale;
    pp.output_filter = p->output_filter;
    pp.src_lines = (int)nh;
    /* to the window rectangle: when the frame is larger (a good minifying
     * filter instead of the presenter's bilinear) or an output filter has
     * to work on the final pixel grid; otherwise the presenter scales */
    pp.final_w = fw; pp.final_h = fh;
    if (p->out_w > 0 && p->out_h > 0 &&
        (fw > p->out_w || fh > p->out_h || p->output_filter != GPU_OUTF_OFF)) {
        pp.final_w = p->out_w;
        pp.final_h = p->out_h;
    }
    *w = (uint32_t)pp.final_w;
    *h = (uint32_t)pp.final_h;
    if ((uint64_t)*w * *h > out_cap_px) return -1;
    GpuDisplay d;
    int W = 0, OH = 0;
    if (build_display(r, field, d, &W, &OH) != 0) return -1;
    r->stats.display_frames++;
    mem_flush(r);
    return r->be->display_post(d, pp, out);
}

int gpu_set_scale(gpu_renderer *r, int scale)
{
    if (scale < 1) scale = 1;
    if (scale > 8) scale = 8;
    if (scale == r->scale) return r->scale;
    if (r->gs) {
        /* every target back to the mirror, then gone: they reload from local
         * memory at the new scale on their next use */
        while (!r->rts.empty()) rt_drop(r, r->rts.size() - 1);
    } else {
        for (Rt &t : r->rts) r->be->rt_destroy(t.id);
        r->rts.clear();
    }
    replay_free(r);
    r->be->set_scale(scale);
    r->scale = scale;
    r->cfg.scale = scale;
    return r->scale;
}

void gpu_enhance_default(gpu_enhance *e) { memset(e, 0, sizeof *e); }

void gpu_set_enhance(gpu_renderer *r, const gpu_enhance *e)
{
    gpu_enhance n;
    if (e) n = *e;
    else gpu_enhance_default(&n);
    if (memcmp(&n, &r->enh, sizeof n) == 0) return;
    if (r->gs) {
    }
    r->enh = n;
}

void gpu_get_enhance(const gpu_renderer *r, gpu_enhance *e) { *e = r->enh; }

/* ======================================================== native draws
 * docs/NATIVE-RENDER.md: a mesh drawn by the native pipeline at the marker's
 * place in the GS stream.  Targets, coherence and the texture follow the same
 * rules as a batch (flush_batch); the state is the GS registers in force. */
void gpu_nr_prims_begin(gpu_renderer *r) { (void)r; }   /* (no GS draw path natively) */
void gpu_nr_prims_alpha_swap(gpu_renderer *r, int on) { (void)r; (void)on; }
void gpu_nr_prims_end(gpu_renderer *r) { (void)r; }

void gpu_set_native_handler(gpu_renderer *r, gpu_native_fn fn, void *user)
{
    r->nat_fn = fn;
    r->nat_user = user;
}

const gpu_nr_stats *gpu_nr_get_stats(const gpu_renderer *r)
{
    gpu_nr_stats *s = (gpu_nr_stats *)&r->nrs;
    s->tex_decodes = r->be->n_nr_tex;
    s->mesh_uploads = r->be->n_nr_mesh;
    s->blend_approx = r->be->n_nr_blend_approx;
    return &r->nrs;
}

/* The GpuNrDraw of a native draw from the GS state (k, d of context ctx with
 * XYOFFSET xy) into colour / depth targets ct / zt (zt NULL: none): pipeline
 * state, constant rows 10.z, 11, 23, culling and the texture's registers
 * (level-0 rect, decode constants, filter, wrap).  The texture's content key
 * (dec_key[3..5]) is the caller's. */
static void nr_fill(gpu_renderer *r, const Key &k, const Derived &d, uint64_t xy, const gpu_nr_draw *nd,
                    int ct_id, int ct_w, int ct_h, int ct_halloc, int zt_id, GpuNrDraw &g)
{
    memset(&g, 0, sizeof g);
    g.tex_rt = -1;
    g.color_rt = ct_id;
    g.depth_rt = zt_id;
    g.rt_w = ct_w;
    g.rt_h = ct_halloc;
    g.vp_w = 1; while (g.vp_w < g.rt_w) g.vp_w <<= 1;
    g.vp_h = 1; while (g.vp_h < g.rt_h) g.vp_h <<= 1;
    g.scissor.x0 = d.scx0; g.scissor.y0 = d.scy0;
    g.scissor.x1 = d.scx1 < ct_w ? d.scx1 : ct_w;
    g.scissor.y1 = d.scy1 < ct_h ? d.scy1 : ct_h;
    g.zfunc = zt_id >= 0 ? d.zfunc : GZ_OFF;
    g.zwrite = zt_id >= 0 ? d.pass[0].zwrite : 0;
    g.cmask = d.pass[0].cmask;
    g.abe = d.abe;
    g.alpha_abcd = d.cb.d[2][0];
    g.d = nd;
    memcpy(g.cb, nd->cb, sizeof g.cb);
    /* row 11: GS window -> target NDC (as VS_main: (x + 0.5) * kx - 1) */
    {
        float ofx = (float)BITS(xy, 0, 16) / 16.0f, ofy = (float)BITS(xy, 32, 16) / 16.0f;
        g.cb[11][0] = ofx - 0.5f;
        g.cb[11][1] = ofy - 0.5f;
        g.cb[11][2] = 2.0f / (float)g.vp_w;
        g.cb[11][3] = 2.0f / (float)g.vp_h;
    }
    /* row 10.z: the depth format's largest Z */
    g.cb[10][2] = d.zpsm == GS_PSMZ24 ? 16777215.0f
                : (d.zpsm == GS_PSMZ16 || d.zpsm == GS_PSMZ16S) ? 65535.0f : 4294967295.0f;
    /* row 23: pixel state (nr_draw.hlsl PS_FLAGS / PS_ATEST / PS_FOGCOL) */
    {
        uint32_t fl = 0, at = 0;
        int C = (int)BITS(k.alpha, 4, 2);
        if (d.tme) fl |= 1u;
        if (d.fge) fl |= 2u;
        if (d.ate) fl |= 4u;
        if (k.fba) fl |= 8u;
        if (d.tme && BITS(k.tex0, 34, 1)) fl |= 16u;
        if (d.abe) fl |= 32u;
        if (C == 2) fl |= 64u;
        if (C == 1) { fl |= 128u; if (d.abe) r->be->n_nr_blend_approx++; }
        if (r->cfg.fault == 7) fl |= 0x100u;
        at = (uint32_t)d.atst | (BITS(k.test, 4, 8) << 8) | (d.tme ? BITS(k.tex0, 35, 2) << 16 : 0u) |
             (BITS(k.alpha, 32, 8) << 24);
        memcpy(&g.cb[23][0], &fl, 4);
        memcpy(&g.cb[23][1], &at, 4);
        uint32_t fc = (uint32_t)k.fogcol;
        memcpy(&g.cb[23][2], &fc, 4);
    }
    /* cull: the program culls triangles whose screen area * hand > 0 (area of
     * the even-strip winding, GS y down); GS y down maps to target y down, so
     * area > 0 is clockwise = D3D11 front (FrontCounterClockwise FALSE) */
    g.cull = nd->cull ? (nd->cull_sign > 0 ? 1 : 2) : 0;
    if (d.tme) {
        int tw0 = (int)BITS(k.tex0, 26, 4), th0 = (int)BITS(k.tex0, 30, 4);
        if (tw0 > 10) tw0 = 10;
        if (th0 > 10) th0 = 10;
        int wms = (int)BITS(k.clamp, 0, 2), wmt = (int)BITS(k.clamp, 2, 2);
        GpuRect tr = { 0, 0, 1 << tw0, 1 << th0 };
        g.tme = 1;
        g.dec_rect = tr;
        g.dec_key[0] = d.tbp | (d.tbw << 14) | ((uint32_t)d.tpsm << 20);
        g.dec_key[1] = d.cb.d[4][2];
        g.dec_key[2] = d.cb.d[6][1] | (d.cb.d[6][2] << 8) | (d.cb.d[6][3] << 16);
        g.dec_key[6] = (uint32_t)tw0 | ((uint32_t)th0 << 4);
        g.dec_cb = d.cb;
        int mmag = (int)BITS(k.tex1, 5, 1), mmin = (int)BITS(k.tex1, 6, 3);
        g.lin = mmag || mmin == 1 || mmin == 4 || mmin == 5;
        if (r->enh.tex_filter == GPU_TEXF_BILINEAR) g.lin = 1;
        else if (r->enh.tex_filter == GPU_TEXF_NEAREST) g.lin = 0;
        g.clamp_u = wms == 1 || wms == 2;
        g.clamp_v = wmt == 1 || wmt == 2;
    }
}


/* The draw of a native mesh (iv NULL) or of immediate primitives (iv: a triangle
 * list of niv vertices) with the state k / d derived from the GS registers:
 * targets, pipeline, texture (decoded once, content key), the backend draw
 * and the coherence bookkeeping. */
/* the texture override of gpu_enhance applies: no live render target in the pages the
 * state can sample (the emulated path's "ordinary" texture) */
static int nr_tex_ordinary(const gpu_renderer *r, const Derived &d)
{
    if (!d.tme) return 1;
    return tex_pages_ordinary(r, d.tex_pages, NULL);
}
/* ---- format-changing views at the internal resolution (checkpoint 12) -------------------
 * The effect passes read a colour target through a view of another format (a CT32 view of a
 * CT16 target the pass drew: the CT16 trick's way back); the view's texels were decoded from
 * the 1x mirror.  RG_NR_REINT=2: a temporary target in the view's format is filled from the
 * live target at the internal resolution (backend rt_reinterpret: sub-sample by sub-sample
 * through a scratch copy of local memory, the GS's own address arithmetic) and sampled
 * directly. */
/* d's texture read rect tr as a view of a live colour target of another format at its base:
 * a temporary target (id returned, *out its geometry) holding the view at the internal
 * resolution; -1 none */
static int reint_view(gpu_renderer *r, const Derived &d, const GpuRect &tr, const Rt *ct, Rt *out)
{
    if (!reint_fmt(d.tpsm) || (d.tbp & 31) || tr.x0 < 0 || tr.y0 < 0 || tr.x1 <= tr.x0 || tr.y1 <= tr.y0) return -1;
    const Rt *t = NULL;
    for (const Rt &x : r->rts)
        if (!x.depth && x.bp == d.tbp && x.bw == d.tbw && x.psm != d.tpsm && reint_fmt(x.psm)) { t = &x; break; }
    if (!t || t == ct) return -1;   /* (a draw into the target it reads as another format: the mirror path) */
    int w = (int)d.tbw * 64, ph = page_h(d.tpsm);
    int vh = t->h / page_h(t->psm) * ph;   /* (the target's page rows in the view's format) */
    int x1 = tr.x1 > w && tr.x1 <= w + 4 ? w : tr.x1;
    int y1 = tr.y1 > vh && tr.y1 <= vh + 4 ? vh : tr.y1;
    int rows = (y1 + ph - 1) / ph * ph;
    if (x1 > w || rows > 2048) { g_reint.refused++; return -1; }
    /* the view's pages inside the target, current there; no other target over them */
    Pages vp = pages_of(d.tbp, d.tbw, d.tpsm, 0, 0, w, rows);
    Pages out_of = vp;
    out_of.sub(t->pages);
    if (out_of.any() || !rt_current_in(r, *t, vp)) { g_reint.refused++; return -1; }
    for (const Rt &x : r->rts)
        if (&x != t && x.pages.overlaps(vp)) { g_reint.refused++; return -1; }
    int id = r->be->rt_create(0, w, rows);
    if (id < 0) return -1;
    mem_flush(r);
    GpuRect dr = { 0, 0, w, rows }, sr = { 0, 0, t->w, t->h };
    if (!r->be->rt_reinterpret(id, d.tbp, d.tbw, d.tpsm, dr, t->id, t->bp, t->bw, t->psm, sr)) {
        r->be->rt_destroy(id);
        g_reint.refused++;
        return -1;
    }
    memset(out, 0, sizeof *out);
    out->id = id;
    out->bp = d.tbp;
    out->bw = d.tbw;
    out->psm = d.tpsm;
    out->w = w;
    out->h = rows;
    out->h_alloc = rows;
    out->pages = vp;
    g_reint.last_src = t->id;
    g_reint.views++;
    return id;
}

static int nr_draw_resolved(gpu_renderer *r, const Key &k, const Derived &d, const gpu_nr_draw *nd,
                            const GpuImVtx *iv, uint32_t niv, int keep_gs_filter, const GpuRect *im_read)
{
    gpu_gs *gs = r->gs;
    {
        /* RG_NR_DBGSKIP=K:F:T (investigation): native draws of kind K (m mesh, i immediate,
         * * any) into FBP F with TBP T (-1: any) are not drawn */
        static int sk = -2, sf, st;
        static char skk;
        if (sk == -2) {
            const char *e = getenv("RG_NR_DBGSKIP");
            sk = -1;
            if (e && sscanf(e, "%c:%d:%d", &skk, &sf, &st) == 3) sk = 1;
        }
        if (sk == 1 && (skk == '*' || (skk == 'm') == (iv == NULL)) && (sf < 0 || (uint32_t)sf == d.fbp) &&
            (st < 0 || (d.tme && (uint32_t)st == (uint32_t)BITS(k.tex0, 0, 14))))
            return 1;
    }
    int fbw = (int)(d.fbw ? d.fbw : 1);
    int need_h = d.scy1;
    Rt *ct = rt_bind(r, 0, d.fbp, (uint32_t)fbw, d.fpsm, need_h, -1);
    Rt *zt = NULL;
    if (ct && d.need_depth) {
        int cid = ct->id;
        zt = rt_bind(r, 1, d.zbp, (uint32_t)fbw, d.zpsm, need_h, cid);
        ct = rt_find_id(r, cid);
        if (!ct) zt = NULL;
    }
    if (!ct) { r->nrs.skipped++; return 1; }
    if (zt && zt->h_alloc != ct->h_alloc) {
        Rt *small = zt->h_alloc < ct->h_alloc ? zt : ct;
        small->h_alloc = 2048;
        r->be->rt_resize(small->id, small->w, small->h_alloc);
    }
    GpuNrDraw g;
    nr_fill(r, k, d, gs->reg[GS_XYOFFSET_1 + d.ctx], nd, ct->id, ct->w, ct->h, ct->h_alloc, zt ? zt->id : -1, g);
    g.im = iv;
    g.nim = niv;
    if (iv && r->im_nruns > 0) { g.runs = r->im_runs; g.nruns = r->im_nruns; }
    if (iv && r->im_crov) {
        /* the GS pixel back end in the shader (nr_draw.hlsl NR_CROV): rows 1-2 */
        uint32_t fl = 0, fbm = BITS(k.frame, 32, 32), az;
        if (d.date) fl |= 1u;
        if (d.datm) fl |= 2u;
        if (k.pabe & 1) fl |= 4u;
        if (k.colclamp & 1) fl |= 8u;
        if (k.dthe & 1) fl |= 16u;
        if ((k.scanmsk & 3) >= 2) fl |= 32u | ((k.scanmsk & 1) ? 64u : 0u);
        if (d.ate) fl |= (uint32_t)(d.afail & 3) << 8;
        if (d.abe) fl |= 0x800u;
        az = BITS(k.alpha, 0, 8) | (BITS(k.alpha, 32, 8) << 8) | ((uint32_t)d.fpsm << 16);
        uint32_t dx0 = (uint32_t)k.dimx, dx1 = (uint32_t)(k.dimx >> 32);
        memcpy(&g.cb[1][0], &fl, 4);
        memcpy(&g.cb[1][1], &fbm, 4);
        memcpy(&g.cb[1][2], &az, 4);
        memcpy(&g.cb[2][0], &dx0, 4);
        memcpy(&g.cb[2][1], &dx1, 4);
        g.cb[2][2] = (float)r->scale;
        g.crov = 1;
        g.cmask = 15;   /* (FBMSK is merged in the shader) */
    }
    if (keep_gs_filter && r->scale > 1) {
        /* sprites upscaled: texture coordinates at the native pixel's centre
         * (nr_draw.hlsl PF_SNAP) */
        uint32_t fl;
        memcpy(&fl, &g.cb[23][0], 4);
        fl |= 0x400u;
        /* RG_NR_UV16=0 (control, tools/shadow/shadowcheck.py): the snap without the GS's
         * 1/16-texel rounding (nr_draw.hlsl gs_uv16, shadow bands 2026-10-26) */
        static int uv16 = -1;
        if (uv16 < 0) { const char *e = getenv("RG_NR_UV16"); uv16 = !(e && e[0] == '0'); }
        if (!uv16) fl |= 0x2000000u;
        memcpy(&g.cb[23][0], &fl, 4);
        g.cb[22][1] = (float)r->scale;
    }
    if (d.tme && (keep_gs_filter || !nr_tex_ordinary(r, d))) {
        /* sprites (2D) and textures in live render targets (post passes, CLUT tricks) keep
         * the GS filter, as on the emulated path (gpu.h gpu_enhance) */
        int mmag = (int)BITS(k.tex1, 5, 1), mmin = (int)BITS(k.tex1, 6, 3);
        g.lin = mmag || mmin == 1 || mmin == 4 || mmin == 5;
    }
    if (r->filt_log && d.tme) {
        /* $RG_NR_FILTLOG: one line per textured native draw (tools/native/filtlog.py sums it):
         * F frame kind tbp tbw psm WxH keep ord old lin enh [rt bp bw psm h drawn n]
         * ord = this rule, old = page overlap alone, enh = filter override applied (-1: GS TEX1) */
        const Rt *why = NULL, *ov = NULL;
        int ord = tex_pages_ordinary(r, d.tex_pages, &why);
        for (const Rt &t : r->rts)
            if (t.pages.overlaps(d.tex_pages)) { ov = &t; break; }
        if (why) ov = why;
        fprintf(r->filt_log, "F %llu %s tbp %u tbw %u psm %02x %ux%u keep %d ord %d old %d lin %d enh %d",
                (unsigned long long)g_filt_frame, iv ? "im" : "mesh", (unsigned)BITS(k.tex0, 0, 14),
                (unsigned)BITS(k.tex0, 14, 6), (unsigned)BITS(k.tex0, 20, 6), 1u << BITS(k.tex0, 26, 4),
                1u << BITS(k.tex0, 30, 4), keep_gs_filter, ord, ov ? 0 : 1, g.lin,
                (keep_gs_filter || !ord) ? -1 : (int)r->enh.tex_filter);
        if (ov) {
            Pages dp = ov->pages.and_(d.tex_pages).and_(r->drawn);
            int n = 0;
            for (uint32_t pg = 0; pg < 512; pg++) n += dp.get(pg);
            fprintf(r->filt_log, " rt %u bw %u psm %02x h %d drawn %d", ov->bp, ov->bw, ov->psm, ov->h, n);
        }
        /* (the line ends after the direct-sampling decision: " fb FBP dir D [read x0,y0-x1,y1]") */
    }
    if (d.ate && d.afail != 0) r->nrs.unsupported_state++;   /* AFAIL modes: drawn as KEEP */
    if (d.date || d.merge) r->nrs.unsupported_state++;
    if (keep_gs_filter && r->scale > 1 && d.tme && g.lin) {
        /* RG_NR_SNAPLIN=0 (experiment): bilinear sprites' coordinates per sub-sample instead
         * of at the native pixel centre (no gain measured: 8,280 x3 unchanged, save2 x3 -0.3 dB) */
        static int sl = -1;
        if (sl < 0) { const char *e = getenv("RG_NR_SNAPLIN"); sl = !(e && e[0] == '0'); }
        if (!sl) {
            uint32_t fl;
            memcpy(&fl, &g.cb[23][0], 4);
            fl &= ~0x400u;
            memcpy(&g.cb[23][0], &fl, 4);
        }
    }
    /* immediate primitives reading a live colour target (screen-effect passes,
     * docs/NATIVE-RENDER.md "Immediate packets"): sampled directly at the
     * internal resolution, no write-back and no decode; the target drawn into
     * is read through a copy of the texels taken before the draw */
    int dir_why = -1;   /* $RG_NR_FILTLOG */
    GpuRect dir_rd = {0, 0, 0, 0};
    int reint_tmp = -1;   /* a temporary target the draw samples (reint_view), destroyed after it */
    static int nodirect = -1;
    if (nodirect < 0) { const char *e = getenv("RG_NR_NODIRECT"); nodirect = e && e[0] == '1'; }
    if (d.tme && iv && im_read && !d.indexed && d.tex_lvl0 && d.tbw && !r->cfg.rtt_native && !nodirect &&
        (d.tpsm == GS_PSMCT32 || d.tpsm == GS_PSMCT24 ||
         (psm_is16(d.tpsm) && !BITS(k.tex1, 5, 1) && BITS(k.tex1, 6, 3) != 1 && BITS(k.tex1, 6, 3) != 4 && BITS(k.tex1, 6, 3) != 5))) {
        /* (16-bit targets point-sampled only: the stored alpha bit is expanded after the fetch) */
        Rt *src = NULL;
        for (Rt &t : r->rts)
            if (!t.depth && t.bp == d.tbp && t.bw == d.tbw && (t.psm == d.tpsm || (t.psm == GS_PSMCT32 && d.tpsm == GS_PSMCT24))) {
                src = &t;
                break;
            }
        /* (the read rect carries a 2-texel bilinear margin past the last texel:
         * clipped to the target; RG_NR_REINT >= 1: up to 4, the effect passes' 64x64 work targets
         * read 3 past (checkpoint 12)) */
        GpuRect tr = *im_read;
        int marg = reint_on() ? 4 : 2;
        if (src) {
            if (tr.x1 > src->w && tr.x1 <= src->w + marg) { if (tr.x1 > src->w + 2) g_reint.margin++; tr.x1 = src->w; }
            if (tr.y1 > src->h && tr.y1 <= src->h + marg) { if (tr.y1 > src->h + 2) g_reint.margin++; tr.y1 = src->h; }
        }
        /* RG_NR_DIRECT_LOG=N (measurement): the first N immediates with a target at the
         * texture's base that are not sampled directly, and why */
        static int dlg = -1, dln;
        if (dlg < 0) { const char *e = getenv("RG_NR_DIRECT_LOG"); dlg = e ? atoi(e) : 0; }
        int why_nd = 0;
        if (!src) why_nd = 4;
        Rt reint_rt;   /* (a temporary target: a live colour target read as another format) */
        if (!src && reint_level() >= 2 && (reint_tmp = reint_view(r, d, tr, ct, &reint_rt)) >= 0) {
            src = &reint_rt;
            if (tr.x1 > src->w && tr.x1 <= src->w + 4) tr.x1 = src->w;
            if (tr.y1 > src->h && tr.y1 <= src->h + 4) tr.y1 = src->h;
        }
        dir_rd = tr;
        if (!src && dln < dlg) {
            Pages rp0 = pages_of(d.tbp, d.tbw, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
            for (const Rt &t : r->rts)
                if (t.pages.overlaps(rp0)) {
                    dln++;
                    fprintf(stderr, "nr direct: tex %u/%u %02x read %d,%d-%d,%d: no target at the base; target %u/%u %02x%s %dx%d covers it\n",
                            d.tbp, d.tbw, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1, t.bp, t.bw, t.psm, t.depth ? " (Z)" : "", t.w, t.h);
                    break;
                }
        }
        if (src && tr.x0 >= 0 && tr.y0 >= 0 && tr.x1 <= src->w && tr.y1 <= src->h &&
            rt_current_in(r, *src, pages_of(d.tbp, d.tbw, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1))) {
            Pages rp = pages_of(d.tbp, d.tbw, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
            for (const Rt &t : r->rts)
                if (&t != src && !(reint_tmp >= 0 && t.id == g_reint.last_src) && t.pages.overlaps(rp)) {
                    if (dln < dlg) {
                        dln++;
                        fprintf(stderr, "nr direct: tex %u/%u %02x read %d,%d-%d,%d: other target %u/%u %02x%s h %d overlaps\n",
                                d.tbp, d.tbw, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1, t.bp, t.bw, t.psm, t.depth ? " (Z)" : "", t.h);
                    }
                    src = NULL;
                    why_nd = 3;
                    break;
                }
        } else {
            if (src) why_nd = (tr.x0 >= 0 && tr.y0 >= 0 && tr.x1 <= src->w && tr.y1 <= src->h) ? 1 : 2;
            if (src && dln < dlg) {
                dln++;
                fprintf(stderr, "nr direct: tex %u/%u %02x read %d,%d-%d,%d: %s (target %dx%d)\n", d.tbp, d.tbw, d.tpsm, tr.x0,
                        tr.y0, tr.x1, tr.y1, why_nd == 1 ? "target stale" : "read outside the target", src->w, src->h);
            }
            src = NULL;
        }
        if (src) {
            int tw0 = (int)BITS(k.tex0, 26, 4), th0 = (int)BITS(k.tex0, 30, 4);
            if (tw0 > 10) tw0 = 10;
            if (th0 > 10) th0 = 10;
            g.tex_rt = src->id;
            g.tex_snap = src == ct;
            g.tex_rect = tr;
            g.clamp_u = g.clamp_v = 1;
            g.cb[12][0] = (float)(1 << tw0) / (float)src->w;      /* GS-normalised -> target-normalised */
            g.cb[12][1] = (float)(1 << th0) / (float)src->h_alloc;
            g.cb[13][0] = (float)src->w;                           /* the target's native size (PF_NATTAP) */
            g.cb[13][1] = (float)src->h_alloc;
            if (d.tpsm == GS_PSMCT24 && BITS(k.tex0, 34, 1)) {
                uint32_t fl;
                memcpy(&fl, &g.cb[23][0], 4);
                fl |= 0x200u | (BITS(k.texa, 0, 8) << 16) | (BITS(k.texa, 15, 1) << 24);   /* PF_CT24: alpha TA0 (AEM) */
                memcpy(&g.cb[23][0], &fl, 4);
            }
            if (psm_is16(d.tpsm)) {
                /* PF_CT16: the target holds the stored bit as alpha 0x80 / 0: TEXA TA1 / TA0 (AEM) */
                uint32_t fl;
                memcpy(&fl, &g.cb[23][0], 4);
                fl |= 0x2000u | (BITS(k.texa, 0, 8) << 16) | (BITS(k.texa, 15, 1) << 24);
                memcpy(&g.cb[23][0], &fl, 4);
                g.cb[13][2] = (float)BITS(k.texa, 32, 8);
            }
            r->stats.direct_samples++;
            if (g.tex_snap) r->stats.tex_copies++;
        }
        dir_why = src ? (reint_tmp >= 0 ? 5 : 0) : why_nd;
        if (!src && reint_tmp >= 0) { r->be->rt_destroy(reint_tmp); reint_tmp = -1; }
    }
    if (r->filt_log && d.tme) {
        /* dir: -1 not eligible for direct sampling (mesh, indexed, ...), 0 sampled from the live
         * target, 1 target stale where read, 2 read outside the target, 3 another target overlaps,
         * 4 no target at the texture's base (1-4: decoded from the 1x mirror), 5 sampled from a
         * live target of another format, reinterpreted at the internal resolution (RG_NR_REINT=2) */
        fprintf(r->filt_log, " fb %u dir %d", d.fbp, dir_why);
        if (dir_why >= 0) fprintf(r->filt_log, " read %d,%d-%d,%d", dir_rd.x0, dir_rd.y0, dir_rd.x1, dir_rd.y1);
        fputc('\n', r->filt_log);
    }
    if (g.tex_rt >= 0 && r->scale > 1) {
        /* an upscaled target as the texture: the GS picks (point) or blends
         * (bilinear: the game's half-pixel blur passes) native texels; the
         * shader does that in native texel units and reads each tap's
         * sub-texel at the destination pixel's sub-sample phase, so a 1:1
         * copy keeps the upscaled detail (nr_draw.hlsl PF_NATTAP / PF_SUBPH) */
        uint32_t fl;
        memcpy(&fl, &g.cb[23][0], 4);
        /* bilinear: taps a native texel apart (PF_NATTAP, checkpoint 6; GS weights since
         * checkpoint 9); RG_NR_NATTAP=0: the emulated path's sample_direct (upscaled texels,
         * PF_GSLIN below): better for the composite draw-back on save2 x3 (36.8 vs 33.1 dB),
         * worse on the route's 8,280 cutscene x3 (30.3 / SSIM 0.92 vs 33.5 / 0.958) */
        static int nat = -1;
        /* (default 0 since checkpoint 10: with the composite draw-back native at every scale the
         * upscaled-texel taps win everywhere measured: x3 route 0 failing (8,150 30.76 / 8,280 44.14 dB
         * vs 29.61 / 30.78 FAIL with native taps), save2 close-up x3 38.2 vs 32.2 dB; RG_NR_NATTAP=1:
         * native-texel taps) */
        if (nat < 0) { const char *e = getenv("RG_NR_NATTAP"); nat = e && e[0] == '1'; }
        if (!g.lin || nat || r->no_gslin) fl |= g.lin ? 0x800u : 0x1000u;
        else fl &= ~0x400u;   /* (no PF_SNAP: sample_direct evaluates bilinear coordinates per sub-sample) */
        memcpy(&g.cb[23][0], &fl, 4);
        g.cb[22][1] = (float)r->scale;
    }
    uint32_t fl23;
    memcpy(&fl23, &g.cb[23][0], 4);
    if (iv && d.tme && g.lin && !(fl23 & 0x800u) && !r->no_gslin) {
        /* immediate primitives: the GS's bilinear weights (nr_draw.hlsl PF_GSLIN); the
         * decoded texture is power-of-two sized (repeat = mask), a target is clamped */
        uint32_t fl, cl = (g.clamp_u ? 1u : 0u) | (g.clamp_v ? 2u : 0u);
        if (g.tex_rt >= 0) cl = 3u;
        memcpy(&fl, &g.cb[23][0], 4);
        fl |= 0x4000u;
        memcpy(&g.cb[23][0], &fl, 4);
        memcpy(&g.cb[13][3], &cl, 4);
    }
    if (iv && d.tme && !g.lin && g.cb[22][3] != 0.0f && !(fl23 & 0x1800u)) {
        /* squeezed 2D (gpu_set_im_xfree), point-sampled: sharp-bilinear in X (nr_draw.hlsl
         * PF_SHARPX), so a 0.75x glyph keeps every texel column at any internal res */
        uint32_t fl;
        memcpy(&fl, &g.cb[23][0], 4);
        fl |= 0x8000u;
        memcpy(&g.cb[23][0], &fl, 4);
    }
    /* texture: the level-0 wrap rect, decoded once (key: registers, CLUT
     * content, content of the pages read) */
    if (d.tme && g.tex_rt < 0) {
        int wms = (int)BITS(k.clamp, 0, 2), wmt = (int)BITS(k.clamp, 2, 2);
        const GpuRect &tr = g.dec_rect;
        if (wms >= 2 || wmt >= 2) r->nrs.unsupported_state++;   /* region modes: sampled as clamp/repeat */
        Pages rp = pages_of(d.tbp, d.tbw ? d.tbw : 1, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
        for (Rt &t : r->rts)
            if (t.has_dirty && t.pages.overlaps(rp) && !(d.hbyte_tex && (t.psm == GS_PSMCT24 || t.psm == GS_PSMZ24)))
                rt_writeback(r, t);
        if (d.indexed && (!r->clut_valid || r->clut_uploaded_gen != k.clut_gen)) {
            GpuClutCB c;
            memset(&c, 0, sizeof c);
            for (int i = 0; i < 256; i++)
                c.c[i >> 2][i & 3] = (uint32_t)r->clut_copy[2 * i] | ((uint32_t)r->clut_copy[2 * i + 1] << 16);
            if (r->clut_own_any) r->be->set_clut_part(c, r->clut_own);
            else r->be->set_clut(c);
            r->clut_uploaded_gen = k.clut_gen;
            r->clut_valid = 1;
        }
        /* content key of the pages read: the content keys of their blocks (the transfers that
         * wrote them, by bytes and geometry; GPU writes unique), cached by the page's stamp */
        uint32_t newest = 2166136261u;
        for (uint32_t pg = 0; pg < 512; pg++) {
            if (!rp.get(pg)) continue;
            if (r->page_hash_stamp[pg] != r->page_stamp[pg] || r->page_hash_stamp[pg] == 0) {
                uint32_t h = 2166136261u;
                for (uint32_t b = 0; b < 32; b++) h = mix32(h, r->blk_key[pg * 32u + b]);
                r->page_hash[pg] = h;
                r->page_hash_stamp[pg] = r->page_stamp[pg];
            }
            newest = (newest ^ r->page_hash[pg] ^ pg) * 16777619u;
        }
        /* the CLUT by content too (generations count changes: A, B, A is
         * three generations) */
        uint64_t cg = 0;
        if (d.indexed) {
            if (r->nr_clut_hash_gen != k.clut_gen) {
                uint32_t h = 2166136261u;
                for (int i = 0; i < 512; i++) h = (h ^ r->clut_copy[i]) * 16777619u;
                r->nr_clut_hash = h;
                r->nr_clut_hash_gen = k.clut_gen;
            }
            cg = (uint64_t)r->nr_clut_hash | (1ull << 32);
            if (clut_tex_gpu(r, k)) cg ^= (uint64_t)(uint32_t)(k.clut_gen * 2654435761u);   /* GPU-loaded words */
        }
        g.dec_key[3] = (uint32_t)cg;
        g.dec_key[4] = (uint32_t)(cg >> 32);
        g.dec_key[5] = newest;
        memcpy(r->nr_last_key, g.dec_key, sizeof r->nr_last_key);
    }
    if (!r->pend.empty() && g.tme && g.tex_rt < 0 && !r->be->nr_tex_cached(g.dec_key, g.dec_rect))
        mem_flush(r);   /* (the decode reads the mirror) */
    {
        bool drawn = r->be->nr_draw(g);
        if (reint_tmp >= 0) r->be->rt_destroy(reint_tmp);
        if (!drawn) { r->nrs.skipped++; return -1; }
    }
    {
        /* RG_NR_RTDUMP=FBP:FRAME:N:DIR (investigation, shadow-bands lane 2026-10-26): after each
         * native draw into FBP from EE frame FRAME on, the whole target at the internal resolution
         * as DIR/rt_FRAME_SEQ_fbFBP_psmP.pam (RGBA, at most N files; tools/shadow/pam2png.py) */
        static int rd = -2, rdn;
        static unsigned rdf, rdfr;
        static char rdd[260];
        if (rd == -2) {
            const char *e = getenv("RG_NR_RTDUMP");
            rd = -1;
            if (e && sscanf(e, "%u:%u:%d:%259s", &rdf, &rdfr, &rdn, rdd) == 4) rd = 0;
        }
        static int rdt = -2;   /* RG_NR_RTDUMP_TBP=T: only draws texturing from TBP T (+ their state on stderr) */
        if (rdt == -2) { const char *e = getenv("RG_NR_RTDUMP_TBP"); rdt = e ? atoi(e) : -1; }
        if (rd >= 0 && rd < rdn && d.fbp == rdf && g_filt_frame >= rdfr && (rdt < 0 || (d.tme && d.tbp == (uint32_t)rdt))) {
            fprintf(stderr, "nr rtdump %d: frame %u FRAME %016llX TEX0 %016llX TEX1 %016llX ALPHA %016llX TEST %016llX tex_rt %d fl %08X nim %u\n",
                    rd, (unsigned)g_filt_frame, (unsigned long long)k.frame, (unsigned long long)k.tex0,
                    (unsigned long long)k.tex1, (unsigned long long)k.alpha, (unsigned long long)k.test, g.tex_rt,
                    *(const uint32_t *)&g.cb[23][0], niv);
            for (uint32_t q = 0; iv && q < niv && q < 12; q++)
                fprintf(stderr, "  v%u %.3f %.3f s %.6f t %.6f q %.6f\n", q, iv[q].x, iv[q].y, iv[q].s, iv[q].t, iv[q].q);
            if (rdt >= 0) {
                /* (with a TBP filter: the 4 MB mirror the draw decoded from, as DIR/rt_..._mem.vram) */
                static std::vector<uint8_t> mem(GS_VRAM_BYTES);
                uint32_t runs[2] = { 0, GS_VRAM_BYTES };
                mem_flush(r);
                r->be->mirror_download(runs, 1, mem.data());
                char fn[400];
                snprintf(fn, sizeof fn, "%s/rt_%05u_%04d_mem.vram", rdd, (unsigned)g_filt_frame, rd);
                FILE *f = fopen(fn, "wb");
                if (f) { fwrite(mem.data(), 1, mem.size(), f); fclose(f); }
            }
            Rt *t = rt_find_id(r, ct->id);
            GpuRect fr = { 0, 0, t ? t->w : 0, t ? t->h : 0 };
            int s = r->scale > 0 ? r->scale : 1;
            std::vector<uint32_t> px((size_t)fr.x1 * s * fr.y1 * s);
            if (t && !px.empty() && r->be->rt_read(t->id, fr, px.data()) >= 0) {
                char fn[400];
                snprintf(fn, sizeof fn, "%s/rt_%05u_%04d_fb%u_psm%02x.pam", rdd, (unsigned)g_filt_frame, rd, d.fbp, d.fpsm);
                FILE *f = fopen(fn, "wb");
                if (f) {
                    fprintf(f, "P7\nWIDTH %d\nHEIGHT %d\nDEPTH 4\nMAXVAL 255\nTUPLTYPE RGB_ALPHA\nENDHDR\n", fr.x1 * s, fr.y1 * s);
                    fwrite(px.data(), 4, px.size(), f);
                    fclose(f);
                }
            }
            rd++;
        }
    }
    if (iv) { r->nrs.im_draws++; r->nrs.im_prims += niv / 3; } else r->nrs.draws++;
    if (r->trace)
        fprintf(r->trace, "N %llu mesh %u f %u/%u %02x z %u %02x zf %d zw %d tex %u/%u %02x sc %d,%d-%d,%d rt %d/%d h %d cw %x abe %d\n",
                (unsigned long long)r->nrs.draws, nd->mesh.id, d.fbp, d.fbw, d.fpsm, zt ? d.zbp : 0u, d.zpsm,
                (int)g.zfunc, g.zwrite, d.tme ? d.tbp : 0u, d.tbw, d.tpsm, g.scissor.x0, g.scissor.y0, g.scissor.x1,
                g.scissor.y1, g.color_rt, g.depth_rt, ct->h, g.cmask, g.abe);
    r->nrs.tris += iv ? niv / 3 : nd->mesh.nidx / 3;
    r->stats.batches++;
    /* coherence: the scissor rect is what the draw can have written (or the
     * scene side's screen box of the mesh, when it gives one) */
    GpuRect wb = g.scissor;
    if (nd->has_box) {
        uint64_t xy = gs->reg[GS_XYOFFSET_1 + d.ctx];
        float ofx = (float)BITS(xy, 0, 16) / 16.0f, ofy = (float)BITS(xy, 32, 16) / 16.0f;
        float fx0 = nd->box[0] - ofx, fy0 = nd->box[1] - ofy, fx1 = nd->box[2] - ofx, fy1 = nd->box[3] - ofy;
        if (fx0 > -1e6f && fy0 > -1e6f && fx1 < 1e6f && fy1 < 1e6f) {
            int bx0 = (int)floorf(fx0) - 1, by0 = (int)floorf(fy0) - 1;
            int bx1 = (int)ceilf(fx1) + 2, by1 = (int)ceilf(fy1) + 2;
            if (bx0 > wb.x0) wb.x0 = bx0;
            if (by0 > wb.y0) wb.y0 = by0;
            if (bx1 < wb.x1) wb.x1 = bx1;
            if (by1 < wb.y1) wb.y1 = by1;
            r->nrs.boxed++;
        }
    }
    if (wb.x1 > wb.x0 && wb.y1 > wb.y0) {
        if (g.cmask) {
            if (ct->has_dirty) rect_union(ct->dirty, wb);
            else { ct->dirty = wb; ct->has_dirty = 1; }
            r->drawn.add(pages_of(ct->bp, ct->bw, ct->psm, wb.x0, wb.y0, wb.x1, wb.y1));
        }
        if (zt && g.zwrite) {
            if (zt->has_dirty) rect_union(zt->dirty, wb);
            else { zt->dirty = wb; zt->has_dirty = 1; }
            r->drawn.add(pages_of(zt->bp, zt->bw, zt->psm, wb.x0, wb.y0, wb.x1, wb.y1));
        }
    }
    if (zt && ct->pages.overlaps(zt->pages) && r->cfg.fault != 10) {
        rt_writeback(r, *ct);
        rt_writeback(r, *zt);
        ct->stale = 1;
        zt->stale = 1;
        ct->stale_pages.all();
        zt->stale_pages.all();
        r->stats.shared_rt_batches++;
    }
    if (!r->no_early) {
        Pages wpg;
        wpg.clear();
        if (wb.x1 > wb.x0 && wb.y1 > wb.y0) {
            if (g.cmask) wpg.add(pages_of(ct->bp, ct->bw, ct->psm, wb.x0, wb.y0, wb.x1, wb.y1));
            if (zt && g.zwrite) wpg.add(pages_of(zt->bp, zt->bw, zt->psm, wb.x0, wb.y0, wb.x1, wb.y1));
        }
        hot_after_batch(r, wpg);
    }
    r->kick_px += (double)(wb.x1 - wb.x0) * (double)(wb.y1 - wb.y0) * 0.25;
    if (r->kick_at > 0.0 && r->kick_px >= r->kick_at) {
        double t0 = now_us();
        r->be->kick();
        r->stats.kick_us += (uint64_t)(now_us() - t0);
        r->stats.kicks++;
        r->kick_px = 0.0;
    }
    return 0;
}


void gpu_nr_mesh_prewarm(gpu_renderer *r, const gpu_nr_mesh *m)
{
    if (r && m) r->be->nr_mesh_prewarm(*m);
}

int gpu_nr_submit(gpu_renderer *r, const gpu_nr_draw *nd)
{
    gpu_gs *gs = r->gs;
    if (!gs) return -1;
    memset(r->nr_last_key, 0, sizeof r->nr_last_key);
    Key k;
    Derived d;
    make_key(r, gs, &k);
    derive(r, gs, k, &d);
    if (d.skip || d.alias) {
        if (d.alias) r->nrs.unsupported_state++;
        r->nrs.skipped++;
        return 1;
    }
    return nr_draw_resolved(r, k, d, nd, NULL, 0, 0, NULL);
}

/* Immediate primitives (gpu.h gpu_nr_im_submit, docs/NATIVE-RENDER.md "Immediate
 * packets"): the state in force must be one the native pipeline draws as the GS
 * would (within the level-4 tolerances); everything else is left to the GS
 * draw path by returning -1 before anything is drawn. */
enum { NRV_IM_BIT = 2048 };   /* nr_draw.hlsl NRV_IM */
int gpu_nr_im_submit(gpu_renderer *r, const gs_vertex *v, int nprim, int type)
{
    return gpu_nr_im_submit_swap(r, v, nprim, type, NULL);
}
int gpu_nr_im_submit_swap(gpu_renderer *r, const gs_vertex *v, int nprim, int type, const uint8_t *swap)
{
    gpu_gs *gs = r->gs;
    if (!gs || nprim <= 0 || (type != GS_PRIM_TRIANGLE && type != GS_PRIM_SPRITE && type != GS_PRIM_LINE && type != GS_PRIM_POINT))
        return -1;
    Key k;
    Derived d;
    make_key(r, gs, &k);
    derive(r, gs, k, &d);
    if (d.skip) { r->nrs.im_skipped++; return 1; }
    int C = (int)BITS(k.alpha, 4, 2);
    /* reading the buffer drawn into (glare / streak accumulation passes): each
     * primitive reads memory as it was when it started (docs/GPU.md
     * "Checkpoint 4"), so primitives that read what an earlier one of the
     * batch drew start a new draw; only when texels and pixels share one
     * coordinate space (same base, width and a 32/24-bit format) */
    int same_buf = d.tme && d.tbp == d.fbp && d.tbw == d.fbw &&
                   (((d.tpsm == GS_PSMCT32 || d.tpsm == GS_PSMCT24) && (d.fpsm == GS_PSMCT32 || d.fpsm == GS_PSMCT24)) ||
                    (d.tpsm == d.fpsm && psm_is16(d.fpsm) && r->rov)) && !d.zb_feedback;
    int why = psm_is16(d.fpsm) ? 0 : d.date ? 1 : d.merge ? 2 : (d.ate && d.afail != 0) ? 3 : (d.abe && C == 1) ? 4
            : (!k.colclamp || k.pabe || k.scanmsk) ? 5 : d.alias ? 6 : -1;
    int crov = 0;
    if (why < 0 && d.abe && C == 0 && r->rov && (!d.need_depth || r->zrov) && !r->no_asat) {
        /* blend factor As above 0x80 (vertex alpha 0xFF: the main menu's caption font, the card
         * screens' text): the GS multiplies by As / 128 > 1 ((Cs - Cd) * 255 >> 7 + Cd, brighter
         * than Cs); the dual-source factor saturates at 1.  The ordered-view back end computes it
         * as the GS does.  (Texel alpha above 0x80 is not looked at.)  RG_NR_ASAT=0: off */
        int nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_POINT ? 1 : 2;
        for (int i = 0; i < nprim && !crov; i++)
            for (int j = 0; j < nv; j++)
                if (v[i * 3 + j].a > 0x80) { crov = 1; break; }
        if (!crov && d.tme && BITS(k.tex0, 34, 1) && d.tex_pages.overlaps(r->drawn)) {
            /* texel alpha above 0x80 (TCC): a texture the GPU drew (a frame copy: the ch09 glow
             * pass Cs * As >> 7 doubles where the copy's alpha is 0xFF) can hold any alpha; the
             * vertex alpha scales it by Av / 128 (TFX modulate) */
            int tfx = (int)BITS(k.tex0, 35, 2);
            for (int i = 0; i < nprim && !crov; i++)
                for (int j = 0; j < nv; j++)
                    if (tfx != 0 || v[i * 3 + j].a >= 0x80) { crov = 1; break; }
            if (crov) r->im_asat_tex_prims += (uint64_t)nprim;
        }
        if (crov) r->im_asat_prims += (uint64_t)nprim;
    }
    if (why >= 0 && why <= 5 && r->rov && (!d.need_depth || r->zrov) && !(k.scanmsk & 3) == !(k.scanmsk & 2)) {
        /* states of the pixel back end the output merger cannot express: the GS back end in
         * the shader, through the colour target's ordered view (nr_draw.hlsl NR_CROV) */
        crov = 1;
        why = -1;
    }
    int fbk = d.feedback && !same_buf;
    if (why < 0 && d.tme && fbk && !r->no_fbrect) {
        /* the state can sample memory it draws into (page level, whole texture vs the frame
         * over the scissor): with the texels these primitives read and the pixels they cover
         * it often cannot (an effect pass reading the frame's first rows, drawing into the
         * buffer after it); then no primitive reads what another draws */
        const uint64_t fxy = gs->reg[GS_XYOFFSET_1 + d.ctx];
        const float fox = (float)BITS(fxy, 0, 16) / 16.0f, foy = (float)BITS(fxy, 32, 16) / 16.0f;
        float tw_ = (float)(1 << std::min(10, (int)BITS(k.tex0, 26, 4))), th_ = (float)(1 << std::min(10, (int)BITS(k.tex0, 30, 4)));
        float u0 = 1e30f, v0 = 1e30f, u1 = -1e30f, v1 = -1e30f, x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f;
        int nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_POINT ? 1 : 2;
        for (int i = 0; i < nprim; i++)
            for (int j = 0; j < nv; j++) {
                const gs_vertex &c = v[i * 3 + j];
                float U, V;
                if (d.fst) { U = (float)c.u / 16.0f; V = (float)c.v / 16.0f; }
                else { float iq = c.q != 0.0f ? 1.0f / c.q : 0.0f; U = c.s * iq * tw_; V = c.t * iq * th_; }
                float X = (float)c.x / 16.0f - fox, Y = (float)c.y / 16.0f - foy;
                u0 = std::min(u0, U); u1 = std::max(u1, U); v0 = std::min(v0, V); v1 = std::max(v1, V);
                x0 = std::min(x0, X); x1 = std::max(x1, X); y0 = std::min(y0, Y); y1 = std::max(y1, Y);
            }
        if (u0 > -1e6f && u1 < 1e6f && v0 > -1e6f && v1 < 1e6f) {
            /* (texels [floor(u0), ceil(u1)): a bilinear tap past the last coordinate has weight 0
             * at a 1:1 mapping, which is what these passes use) */
            static int mg = -1;
            if (mg < 0) { const char *e = getenv("RG_NR_FBMARGIN"); mg = e ? atoi(e) : 1; }
            int ra = std::max(0, (int)floorf(u0) - mg), rb = std::max(0, (int)floorf(v0) - mg);
            int rc_ = std::min((int)tw_, (int)ceilf(u1) + mg), rd_ = std::min((int)th_, (int)ceilf(v1) + mg);
            int wa = std::max(d.scx0, (int)floorf(x0) - 1), wb = std::max(d.scy0, (int)floorf(y0) - 1);
            int wc = std::min(d.scx1, (int)ceilf(x1) + 2), wd = std::min(d.scy1, (int)ceilf(y1) + 2);
            Pages rp = pages_of(d.tbp, d.tbw ? d.tbw : 1, d.tpsm, ra, rb, rc_, rd_), wp;
            wp.clear();
            uint32_t fw = d.fbw ? d.fbw : 1;
            if (d.fb_feedback) wp.add(pages_of(d.fbp, fw, d.fpsm, wa, wb, wc, wd));
            if (d.zb_feedback) wp.add(pages_of(d.zbp, fw, d.zpsm, wa, wb, wc, wd));
            if (!rp.overlaps(wp)) fbk = 0;
        }
    }
    if (why < 0 && d.tme) {
        int wms = (int)BITS(k.clamp, 0, 2), wmt = (int)BITS(k.clamp, 2, 2);
        why = fbk ? 7 : !d.tex_lvl0 ? 8 : (wms >= 2 || wmt >= 2) ? 9 : (d.tpsm & 0x30) == 0x30 ? 10 : -1;
    }
    if (why == 7 && nprim > 1) {
        /* texture feedback the texel / pixel rectangles cannot rule out: one primitive at a
         * time, each decoded after the previous one's pixels reached the mirror (what the GS
         * does: a primitive reads memory as it was when it started) */
        int rc = 1;
        r->im_fb_split += (uint64_t)nprim;
        for (int i = 0; i < nprim; i++) {
            int c = gpu_nr_im_submit_swap(r, v + 3 * i, 1, type, swap ? swap + i : NULL);
            if (c == 0) rc = 0;
            else if (c < 0 && rc != 0) rc = -1;
        }
        return rc;
    }
    if (why >= 0) {
        /* (the oracle twin draws these through its GS draw path; natively they are drawn with the
         * nearest native state: no ordered view -> output merger, level 0 of mipmaps, region
         * clamps as clamp, frame-Z alias as two targets; counted) */
        r->im_approx[why] += (uint64_t)nprim;
        if (r->fb_census) r->fbc[std::make_tuple(why, k.frame, d.tme ? k.tex0 : 0ull)] += (uint64_t)nprim;
        static int fbl = -1, fbn;
        if (fbl < 0) { const char *e = getenv("RG_NR_IMFB_LOG"); fbl = e ? atoi(e) : 0; }
        if (fbn < fbl) {
            fbn++;
            fprintf(stderr, "nr im approximated %d: why %d type %d n %d FRAME %016llX ZBUF %016llX TEST %016llX ALPHA %016llX "
                            "TEX0 %016llX TEX1 %016llX CLAMP %016llX attr %03llX v0 %u,%u v1 %u,%u uv %u,%u-%u,%u\n",
                    fbn, why, type, nprim, (unsigned long long)k.frame, (unsigned long long)k.zbuf, (unsigned long long)k.test,
                    (unsigned long long)k.alpha, (unsigned long long)k.tex0, (unsigned long long)k.tex1,
                    (unsigned long long)k.clamp, (unsigned long long)k.attr, v[0].x, v[0].y, v[1].x, v[1].y, v[0].u, v[0].v,
                    v[1].u, v[1].v);
        }
    }
    /* vertices: a triangle list in GS primitive coordinates (pixels) */
    static std::vector<GpuImVtx> iv;
    iv.resize((size_t)nprim * 6);
    int tw0 = 0, th0 = 0;
    float tw = 1.0f, th = 1.0f;
    if (d.tme) {
        tw0 = (int)BITS(k.tex0, 26, 4); th0 = (int)BITS(k.tex0, 30, 4);
        if (tw0 > 10) tw0 = 10;
        if (th0 > 10) th0 = 10;
        tw = (float)(1 << tw0);
        th = (float)(1 << th0);
    }
    const float ku = 1.0f / (16.0f * tw), kv = 1.0f / (16.0f * th);
    /* point sampling: the GS computes texel coordinates in fixed point, so 1:1
     * mappings land exactly on texel boundaries, where float interpolation may
     * fall either side; a 1/512 texel bias picks the GS's texel */
    float eu = 0.0f, ev = 0.0f;
    if (d.tme) {
        int mmag = (int)BITS(k.tex1, 5, 1);
        int ovr = type != GS_PRIM_SPRITE && nr_tex_ordinary(r, d);   /* (as nr_draw_resolved decides) */
        bool lin = mmag || (ovr && r->enh.tex_filter == GPU_TEXF_BILINEAR);
        if (ovr && r->enh.tex_filter == GPU_TEXF_NEAREST) lin = false;
        if (!lin) { eu = 1.0f / (512.0f * tw); ev = 1.0f / (512.0f * th); }
    }
    const uint64_t xy = gs->reg[GS_XYOFFSET_1 + d.ctx];
    const float ofx = (float)BITS(xy, 0, 16) / 16.0f, ofy = (float)BITS(xy, 32, 16) / 16.0f;
    float x0 = 1e30f, y0 = 1e30f, x1 = -1e30f, y1 = -1e30f;     /* the run's box (coherence) */
    float px0, py0, px1, py1, tu0, tv0, tu1, tv1;               /* one primitive's box, texels read */
    auto put = [&](GpuImVtx &o, const gs_vertex &c, float px, float py, const gs_vertex &tc) {
        o.x = px;
        o.y = py;
        o.z = c.z;
        o.rgba = (uint32_t)c.r | ((uint32_t)c.g << 8) | ((uint32_t)c.b << 16) | ((uint32_t)c.a << 24);
        float U, V;
        if (d.fst) {
            o.s = (float)tc.u * ku + eu; o.t = (float)tc.v * kv + ev; o.q = 1.0f;
            U = (float)tc.u / 16.0f; V = (float)tc.v / 16.0f;
        } else {
            o.s = tc.s + eu * tc.q; o.t = tc.t + ev * tc.q; o.q = tc.q;
            float iq = tc.q != 0.0f ? 1.0f / tc.q : 0.0f;
            U = tc.s * iq * tw; V = tc.t * iq * th;
        }
        o.fog = c.f;
        if (px < px0) px0 = px;
        if (px > px1) px1 = px;
        if (py < py0) py0 = py;
        if (py > py1) py1 = py;
        if (U < tu0) tu0 = U;
        if (U > tu1) tu1 = U;
        if (V < tv0) tv0 = V;
        if (V > tv1) tv1 = V;
    };
    gpu_nr_draw nd;
    memset(&nd, 0, sizeof nd);
    uint32_t var = NRV_IM_BIT;
    memcpy(&nd.cb[22][0], &var, 4);
    nd.cb[22][3] = r->im_xfree && type == GS_PRIM_SPRITE ? 1.0f : 0.0f;   /* PF_SNAP: Y only */
    nd.cb[12][0] = nd.cb[12][1] = 1.0f;   /* texture coordinate scale (direct target sampling) */
    nd.has_box = 1;
    memset(r->nr_last_key, 0, sizeof r->nr_last_key);
    uint32_t n = 0, nstart = 0;
    GpuRect rd = { 1 << 30, 1 << 30, -(1 << 30), -(1 << 30) };   /* texels the run reads */
    GpuRect wr = { 0, 0, 0, 0 };                                 /* pixels the run writes (same_buf) */
    int have_wr = 0, rc = 1, drawn = 0;
    static std::vector<uint32_t> runs;   /* (end vertex, swap) of the pending draw's runs */
    runs.clear();
    auto submit = [&]() -> int {
        if (n == nstart) return 1;
        if (swap) {
            for (size_t q = 0; q < runs.size(); q += 2) runs[q] -= nstart;
            r->im_runs = runs.data();
            r->im_nruns = (int)(runs.size() / 2);
        }
        nd.box[0] = x0; nd.box[1] = y0; nd.box[2] = x1; nd.box[3] = y1;
        GpuRect rr = rd;
        if (rr.x0 < 0) rr.x0 = 0;
        if (rr.y0 < 0) rr.y0 = 0;
        if (rr.x1 <= rr.x0) rr.x1 = rr.x0 + 1;
        if (rr.y1 <= rr.y0) rr.y1 = rr.y0 + 1;
        r->im_crov = crov;
        int c = nr_draw_resolved(r, k, d, &nd, iv.data() + nstart, n - nstart, type == GS_PRIM_SPRITE, d.tme ? &rr : NULL);
        r->im_crov = 0;
        if (c == 0 && crov) r->im_crov_prims += (n - nstart) / 3;
        r->im_runs = NULL;
        r->im_nruns = 0;
        runs.clear();
        nstart = n;
        x0 = y0 = 1e30f; x1 = y1 = -1e30f;
        rd.x0 = rd.y0 = 1 << 30; rd.x1 = rd.y1 = -(1 << 30);
        have_wr = 0;
        return c;
    };
    for (int i = 0; i < nprim; i++) {
        const gs_vertex *pv = &v[i * 3];
        uint32_t n0 = n;
        px0 = py0 = tu0 = tv0 = 1e30f;
        px1 = py1 = tu1 = tv1 = -1e30f;
        if (type == GS_PRIM_TRIANGLE) {
            for (int j = 0; j < 3; j++)
                put(iv[n++], pv[j], (float)pv[j].x / 16.0f, (float)pv[j].y / 16.0f, pv[j]);
        } else if (type == GS_PRIM_POINT) {
            /* a point: the pixel whose centre is nearest, as a one-pixel quad */
            const gs_vertex &a = pv[0];
            float ax = (float)a.x / 16.0f, ay = (float)a.y / 16.0f;
            GpuImVtx c0, c1, c2, c3;
            put(c0, a, ax - 0.5f, ay - 0.5f, a);
            put(c1, a, ax + 0.5f, ay - 0.5f, a);
            put(c2, a, ax - 0.5f, ay + 0.5f, a);
            put(c3, a, ax + 0.5f, ay + 0.5f, a);
            iv[n++] = c0; iv[n++] = c1; iv[n++] = c2;
            iv[n++] = c1; iv[n++] = c3; iv[n++] = c2;
        } else if (type == GS_PRIM_LINE) {
            /* a line as a quad one pixel across the minor axis, centred on it: the GS's
             * minor pixel floor(b + 1/2) is the pixel centre in [b - 1/2, b + 1/2), the
             * major extent [ceil(lo), ceil(hi)) the quad's ends (hardware fill rule);
             * flat lines take the second vertex's colour and fog */
            gs_vertex a = pv[0], b = pv[1];
            if (!BITS((gs->reg[GS_PRMODECONT] & 1) ? gs->reg[GS_PRIM] : gs->reg[GS_PRMODE], 3, 1)) { a.r = b.r; a.g = b.g; a.b = b.b; a.a = b.a; a.f = b.f; }
            float ax = (float)a.x / 16.0f, ay = (float)a.y / 16.0f, bx = (float)b.x / 16.0f, by = (float)b.y / 16.0f;
            float ddx = bx - ax, ddy = by - ay;
            if (ddx == 0.0f && ddy == 0.0f) continue;
            int xmaj = fabsf(ddx) >= fabsf(ddy);
            float hx = xmaj ? 0.0f : 0.5f, hy = xmaj ? 0.5f : 0.0f;
            GpuImVtx c0, c1, c2, c3;
            put(c0, a, ax - hx, ay - hy, a);
            put(c1, b, bx - hx, by - hy, b);
            put(c2, a, ax + hx, ay + hy, a);
            put(c3, b, bx + hx, by + hy, b);
            iv[n++] = c0; iv[n++] = c1; iv[n++] = c2;
            iv[n++] = c1; iv[n++] = c3; iv[n++] = c2;
        } else {
            /* sprite: colour, Z and fog of the second vertex; texture
             * coordinates interpolated between the corners */
            const gs_vertex &a = pv[0], &b = pv[1];
            float ax = (float)a.x / 16.0f, ay = (float)a.y / 16.0f, bx = (float)b.x / 16.0f, by = (float)b.y / 16.0f;
            gs_vertex t01 = a, t10 = a, t00 = a;
            const gs_vertex &t11 = b;
            t01.u = b.u; t01.s = b.s;          /* (b.x, a.y): u of b, v of a */
            t10.v = b.v; t10.t = b.t;          /* (a.x, b.y): u of a, v of b */
            t00.q = t01.q = t10.q = b.q;
            GpuImVtx c00, c10, c01, c11;
            put(c00, b, ax, ay, t00);
            put(c10, b, bx, ay, t01);
            put(c01, b, ax, by, t10);
            put(c11, b, bx, by, t11);
            if (r->scale > 1) {
                /* upscaled: the GS's pixel coverage (ceil(x0) <= p < ceil(x1))
                 * as whole s x s blocks, like the emulated path; the texture
                 * coordinates follow their linear function to the moved edges,
                 * and the shader evaluates them at the native pixel's centre
                 * (PF_SNAP), so every sub-sample of a pixel reads the GS's texel */
                auto snap = [](float x, float of) { return ceilf(x - of) - 0.5f + of; };
                float sax = snap(ax, ofx), sbx = snap(bx, ofx), say = snap(ay, ofy), sby = snap(by, ofy);
                if (r->im_xfree) { sax = ax; sbx = bx; }   /* squeezed 2D: X at the upscaled pixel */
                float kx = bx != ax ? 1.0f / (bx - ax) : 0.0f, ky = by != ay ? 1.0f / (by - ay) : 0.0f;
                float fa = (sax - ax) * kx, fb = (sbx - ax) * kx, ga = (say - ay) * ky, gb = (sby - ay) * ky;
                float s0 = c00.s, s1 = c10.s, t0 = c00.t, t1 = c01.t;
                float ns0 = s0 + (s1 - s0) * fa, ns1 = s0 + (s1 - s0) * fb;
                float nt0 = t0 + (t1 - t0) * ga, nt1 = t0 + (t1 - t0) * gb;
                c00.x = c01.x = sax; c10.x = c11.x = sbx; c00.y = c10.y = say; c01.y = c11.y = sby;
                c00.s = c01.s = ns0; c10.s = c11.s = ns1; c00.t = c10.t = nt0; c01.t = c11.t = nt1;
            }
            iv[n++] = c00; iv[n++] = c10; iv[n++] = c01;
            iv[n++] = c10; iv[n++] = c11; iv[n++] = c01;
        }
        /* this primitive's window box and texel rect (bilinear margin) */
        GpuRect pw = { (int)floorf(px0 - ofx) - 1, (int)floorf(py0 - ofy) - 1, (int)ceilf(px1 - ofx) + 1, (int)ceilf(py1 - ofy) + 1 };
        GpuRect pr = { (int)floorf(tu0) - 1, (int)floorf(tv0) - 1, (int)ceilf(tu1) + 2, (int)ceilf(tv1) + 2 };
        if (!(tu0 > -1e6f && tu1 < 1e6f && tv0 > -1e6f && tv1 < 1e6f)) { pr.x0 = pr.y0 = 0; pr.x1 = 1 << 20; pr.y1 = 1 << 20; }
        if (same_buf && have_wr && rect_overlap(pr, wr)) {
            /* reads what this run drew: draw the run first, then this one from a new copy */
            uint32_t keep = n - n0;
            n = n0;
            int c = submit();
            if (c == 0) drawn = 1;
            else if (c < 0) rc = -1;
            memmove(&iv[nstart], &iv[n0], keep * sizeof(GpuImVtx));
            n = nstart + keep;
        }
        if (rc < 0) break;
        if (swap) {
            uint32_t f = swap[i] ? 1u : 0u;
            if (!runs.empty() && runs.back() == f) runs[runs.size() - 2] = n;
            else { runs.push_back(n); runs.push_back(f); }
        }
        if (px0 < x0) x0 = px0;
        if (py0 < y0) y0 = py0;
        if (px1 > x1) x1 = px1;
        if (py1 > y1) y1 = py1;
        if (pr.x0 < rd.x0) rd.x0 = pr.x0;
        if (pr.y0 < rd.y0) rd.y0 = pr.y0;
        if (pr.x1 > rd.x1) rd.x1 = pr.x1;
        if (pr.y1 > rd.y1) rd.y1 = pr.y1;
        if (same_buf) {
            if (have_wr) rect_union(wr, pw);
            else { wr = pw; have_wr = 1; }
        }
    }
    if (rc >= 0) {
        int c = submit();
        if (c == 0) drawn = 1;
        else if (c < 0) rc = -1;
    }
    if (rc < 0) {
        /* the backend refused a draw (missing pipeline: then nothing was drawn,
         * and the caller's GS draw path draws everything) */
        r->nrs.im_fallback++;
        r->nrs.im_why[11] += (uint64_t)nprim;
        return drawn ? 0 : -1;
    }
    return drawn ? 0 : 1;
}

/* ---- re-rendering a retained frame (gpu.h "replay", docs/NATIVE-RENDER.md
 * "Replay") ---- */
void gpu_nr_last_texkey(const gpu_renderer *r, uint32_t key[8]) { memcpy(key, r->nr_last_key, sizeof r->nr_last_key); }

static void replay_free(gpu_renderer *r)
{
    if (r->rp_c >= 0) r->be->rt_destroy(r->rp_c);
    if (r->rp_z >= 0) r->be->rt_destroy(r->rp_z);
    r->rp_c = r->rp_z = -1;
}

int gpu_nr_replay_begin(gpu_renderer *r, int w, int h)
{
    if (!r->gs || w <= 0 || h <= 0 || w > 2048 || h > 2048) return -1;
    if (r->rp_c < 0 || r->rp_w != w || r->rp_h != h) {
        replay_free(r);
        r->rp_c = r->be->rt_create(0, w, h);
        r->rp_z = r->be->rt_create(1, w, h);
        r->rp_w = w;
        r->rp_h = h;
        if (r->rp_c < 0 || r->rp_z < 0) { replay_free(r); return -1; }
    }
    r->be->rt_clear(r->rp_c);
    r->be->rt_clear(r->rp_z);
    return 0;
}

int gpu_nr_replay_draw(gpu_renderer *r, const gpu_nr_draw *nd, const uint64_t *regs, const uint32_t *texkey)
{
    if (!r->gs || r->rp_c < 0) return -1;
    static nr_gs rp_gs;
    /* the GS state of the item: its registers over a copy of the live state
     * (only reg[] is read for a native draw's pipeline) */
    rp_gs = *r->gs;
    memcpy(rp_gs.reg, regs, sizeof rp_gs.reg);
    Key k;
    Derived d;
    make_key(r, &rp_gs, &k);
    derive(r, &rp_gs, k, &d);
    if (d.skip || d.alias) return 1;
    GpuNrDraw g;
    nr_fill(r, k, d, regs[GS_XYOFFSET_1 + d.ctx], nd, r->rp_c, r->rp_w, r->rp_h, r->rp_h, d.need_depth ? r->rp_z : -1, g);
    if (g.tme) {
        /* the decoded texture the original draw used, by its content key; the
         * renderer's cache only (local memory may hold anything now) */
        memcpy(g.dec_key, texkey, sizeof g.dec_key);
        g.tex_cached_only = 1;
    }
    return r->be->nr_draw(g) ? 0 : -1;
}

int gpu_nr_replay_end(gpu_renderer *r, uint64_t *hash)
{
    if (r->rp_c < 0) return -1;
    GpuRect rc = { 0, 0, r->rp_w, r->rp_h };
    size_t n = (size_t)r->rp_w * r->scale * (size_t)r->rp_h * r->scale;
    r->rp_buf.resize(n);
    if (r->be->rt_read(r->rp_c, rc, r->rp_buf.data()) != 0) return -1;
    uint64_t h = 1469598103934665603ull;
    for (size_t i = 0; i < n; i++) h = (h ^ r->rp_buf[i]) * 1099511628211ull;
    *hash = h;
    return 0;
}

} /* extern "C" */

/* interpolated presentation (nr_iprec.cpp): the backend pointer the recorder wraps */
GpuBackend **gpu_ip_backend(gpu_renderer *r) { return &r->be; }

#endif /* RG_NATIVE_ONLY */
