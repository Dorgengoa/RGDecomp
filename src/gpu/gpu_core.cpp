/* SPDX-License-Identifier: CC0-1.0 */
/* GPU GS renderer, API-agnostic core: GS hooks, register decode, primitive
 * expansion, batching, render-target bookkeeping and the local-memory
 * coherence rules.  docs/GPU.md.  The graphics API lives behind GpuBackend
 * (gpu_internal.h; gpu_d3d11.cpp). */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <chrono>
#include <map>
#include <tuple>
#include <vector>

#include "gpu_internal.h"

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

struct gpu_renderer {
    gpu_config cfg;
    int scale;
    GpuBackend *be;
    gs_state *gs;
    gpu_stats stats;
    std::vector<Rt> rts;
    Pages cpu_newer;     /* gs->vram newer than the mirror */
    Pages gpu_newer;     /* the mirror newer than gs->vram */
    /* Pages a GPU draw wrote since their last host->local upload (item 8, BRINGUP.md): a
     * texture there is a render result (post pass, CLUT trick) and keeps the GS filter;
     * a texture uploaded after the draw is ordinary even while a target spans its pages
     * (short-lived targets inside the character texture pool) */
    Pages drawn;
    int texrt_overlap;   /* $RG_NR_TEXRT=overlap: the old rule (any live target in the pages) */
    int no_rt_pagecopy;  /* $RG_GPU_RT_PAGECOPY=0: evicted targets reach a new one only through the 1x mirror */
    FILE *filt_log;      /* measurement: $RG_NR_FILTLOG (per native draw: filter choice and why) */
    /* pending batch */
    int have_key;
    Key key;
    Derived dv;
    std::vector<GpuVertex> verts;
    std::vector<GpuTri> tris;   /* exact triangles of the pending batch */
    int exact;                  /* the backend evaluates GpuTri (docs/GPU.md "Exact triangles") */
    int nr_exact_saved;         /* gpu_nr_prims_begin: exact while native primitives are drawn */
    int nr_swap;                /* gpu_nr_prims_alpha_swap: vflags bit 7 on the next primitives */
    int rov;                    /* the backend draws through ordered views (GpuDraw.rov) */
    int zrov;                   /* ... and tests depth in the shader (any depth test with rov) */
    std::vector<GpuRect> boxes;
    GpuRect bbox;
    Pages batch_read;      /* texture pages the pending batch samples */
    Pages batch_written;   /* pages the pending batch draws into (feedback states) */
    GpuRect batch_texrect; /* level-0 texels the pending batch can sample */
    int sw_once;           /* gs->sw_raster was set for one primitive (CPU draw) */
    uint64_t clut_uploaded_gen;
    int clut_valid;
    /* CLUT generations follow the CLUT's contents, not its loads: the game
     * reloads an unchanged palette before every few sprites (TEX0.CLD), and
     * a new generation would end the batch (docs/GPU.md "Performance") */
    uint64_t clut_seen_loads;  /* gs->stats.clut_loads last compared */
    uint64_t clut_gen_id;      /* generation of clut_copy */
    uint16_t clut_copy[512];   /* the CLUT of generation clut_gen_id */
    uint16_t batch_clut[512];  /* the CLUT of the pending batch's key */
    /* GPU-side CLUT loads (hooks.clut_load): the CLUT words whose cells the last load into
     * them made on the GPU (the CLUT buffer is newer than gs->clut / clut_copy there) */
    uint8_t clut_own[256];
    int clut_own_any;
    int clut_force;            /* a CPU load since: next key is a new generation */
    int no_gpu_clut;           /* $RG_GPU_CLUT=0: every CLUT load by the model (read-backs) */
    int clut_check;            /* $RG_GPU_CLUT=check: every GPU load compared with the model's (reads back);
                                  check2: mirror vs local memory of its pages, no state change (+ wide) */
    int clut_wide;             /* $RG_GPU_CLUT=wide / check2: also palettes on split / CPU-newer pages */
    /* mirror write stamps per page (decoded-texture cache keys, docs/GPU.md
     * "Performance"): the stamp of the last upload or write-back into it */
    uint32_t page_stamp[512];
    uint32_t stamp;
    double kick_px;        /* target pixels drawn since the last kick */
    double kick_at;        /* kick every this many (0: never; $RG_GPU_KICK_PX) */
    int tri_box;           /* exact triangles always as their box ($RG_GPU_TRI_BOX=1) */
    FILE *sync_log;        /* measurement: $RG_GPU_SYNC_LOG (on_mem) */
    FILE *trace;           /* measurement: $RG_GPU_TRACE (batches, memory ops, displays) */
    FILE *rt_log;          /* measurement: $RG_GPU_RT_LOG (target creates / drops, displays) */
    /* Split pages (docs/GPU.md "Performance", checkpoint 3): host->local
     * transfers into pages the mirror holds newer data for are not preceded
     * by a read-back.  The CPU model writes gs->vram; merge_mask collects the
     * bits transfers wrote (gs_xfer_mask), which are the newest in gs->vram,
     * every other bit of a split page is the newest in the mirror.
     * merge_split puts the collected bits into the mirror on the GPU when
     * anything needs the pages. */
    Pages split;
    int xfer_split;        /* the open host->local transfer writes split pages */
    gs_mem_rect xfer_rect; /* ... its rectangle */
    uint8_t *merge_mask;   /* GS_VRAM_BYTES; nonzero only on split pages */
    uint8_t *read_mask;    /* GS_VRAM_BYTES scratch: the bits a CPU read uses (read_current) */
    /* Block-level staleness (docs/NATIVE-RENDER.md "Split-page CLUT loads", checkpoint 9):
     * blk_stale[b] bit i = 1 when word i (of 64) of the 256-byte block b of gs->vram may be
     * older than the mirror (a target write-back wrote it since the last download; complete
     * CPU writes clear whole blocks, and single words for the 32-bit formats).  With the dirty rectangles of
     * the live targets it decides at block granularity whether a CPU read (CLUT loads of a
     * palette the CPU uploaded into a corner of a drawn page) can use gs->vram as it is,
     * where the page-level rule (read_current) reads the whole page back. */
    uint64_t blk_stale[16384];
    int no_blk;            /* $RG_GPU_BLK=0: page-level rule only (the checkpoint 8 behaviour) */
    int blk_check;         /* $RG_GPU_BLK=check: every block-rule read also read back and compared */
    uint64_t blk_reads, blk_check_bad;
    HotRead hot[4];        /* early-copied read-back regions */
    uint64_t hot_tick;
    int no_early;          /* $RG_GPU_NO_EARLY_READ=1: read back at the read only */
    std::vector<uint32_t> merge_dm;
    int no_defer;          /* $RG_GPU_NO_DEFER=1: read back as before */
    char name[128];
    gpu_enhance enh;       /* renderer enhancements (docs/GPU.md "Graphics settings") */
    /* native draws (docs/NATIVE-RENDER.md): the marker handler and counters */
    gpu_native_fn nat_fn;
    void *nat_user;
    gpu_nr_stats nrs;
    /* content hash per page for the native texture cache: textures are
     * uploaded again every frame with the same bytes, and a key from the
     * page stamps would decode them again every frame */
    uint32_t page_hash[512];
    uint32_t page_hash_stamp[512];
    uint64_t nr_clut_hash_gen;
    uint32_t nr_clut_hash;
    const uint64_t *disp_preg; /* gpu_set_display_regs: PCRTC register snapshot (NULL: gs->preg) */
    int no_elide;              /* $RG_GPU_NO_ELIDE=1: veto every upload elision (hooks.xfer_clean) */
    int no_lazy;               /* $RG_GPU_NO_LAZY=1: no lazy transfers (hooks.lazy_ok) */
    int no_lazy_tex;           /* $RG_GPU_NO_LAZY_TEX=1: native draws never take textures from pending transfers */
    int lazy_cpu_decode;       /* $RG_GPU_LAZY_CPU=1: decode them on the CPU (scratch replay) instead of on the GPU */
    uint32_t nr_last_key[8];   /* the last native draw's decoded-texture key (gpu_nr_last_texkey) */
    const uint32_t *im_runs;   /* gpu_nr_im_submit_swap: the runs of the draw being made */
    int im_nruns;
    int im_crov;               /* gpu_nr_im_submit: the draw goes through the colour target's ordered view */
    int im_xfree;              /* gpu_set_im_xfree: squeezed 2D, sprites not snapped in X when upscaled */
    /* $RG_NR_IMFB_CENSUS=1: immediate fallbacks by (reason, FRAME, TEX0), primitives (printed at destroy) */
    int fb_census;
    std::map<std::tuple<int, uint64_t, uint64_t>, uint64_t> fbc;
    int no_crov;               /* $RG_NR_CROV=0: those states fall back to the GS draw path */
    int no_gslin;              /* $RG_NR_GSLIN=0: immediate bilinear by the hardware sampler */
    int no_fbrect;             /* $RG_NR_FBRECT=0: texture feedback decided on whole pages (checkpoint 8) */
    int no_asat;               /* $RG_NR_ASAT=0: blend factor As > 0x80 saturated by the dual-source blend */
    uint64_t im_asat_prims;
    uint64_t im_crov_prims;
    /* replay (gpu_nr_replay_*): offscreen colour / depth pair, scratch GS state */
    int rp_c, rp_z, rp_w, rp_h;
    gs_state *rp_gs;
    std::vector<uint32_t> rp_buf;
    std::vector<uint32_t> lz_rgba;   /* a texture decoded from a pending transfer */
    uint64_t lz_key[9];              /* lazy_before_draw: the state last checked */
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

static void merge_split(gpu_renderer *r);

/* ---- block geometry (blk_stale) ----
 * A block is 256 contiguous bytes in every format; blk_dims gives its size in pixels,
 * blk_inv the block cell (bx, by) inside a page for each of the 32 block numbers. */
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
static const uint8_t *blk_inv(int psm)
{
    static uint8_t tab[64][32];
    static uint8_t have[64];
    psm &= 63;
    if (!have[psm]) {
        int bwk, bhk, pw, ph;
        uint32_t bwp;
        if (!blk_dims(psm, &bwk, &bhk)) return NULL;
        page_geom(psm, 2, &pw, &ph, &bwp);
        for (int by = 0; by < ph / bhk; by++)
            for (int bx = 0; bx < pw / bwk; bx++) {
                uint32_t b = (gs_pixel_addr(psm, 0, 2, (uint32_t)(bx * bwk), (uint32_t)(by * bhk), NULL) >> 8) & 31u;
                tab[psm][b] = (uint8_t)(bx | (by << 4));
            }
        have[psm] = 1;
    }
    return tab[psm];
}
/* the pixel rectangle block blk occupies in buffer (bp, bw, psm); 0 if it is not a block of it */
static int blk_rect(uint32_t blk, uint32_t bp, uint32_t bw, int psm, GpuRect *out)
{
    int bwk, bhk, pw, ph;
    uint32_t bwp;
    const uint8_t *inv = blk_inv(psm);
    if (!inv || !blk_dims(psm, &bwk, &bhk)) return 0;
    page_geom(psm, bw ? bw : 1, &pw, &ph, &bwp);
    if (bwp == 0) bwp = 1;
    uint32_t off = (blk - bp) & 16383u;
    uint32_t k = off >> 5, c = inv[off & 31u];
    int x = (int)(k % bwp) * pw + (int)(c & 15u) * bwk, y = (int)(k / bwp) * ph + (int)(c >> 4) * bhk;
    if (y >= 2048) return 0;
    out->x0 = x; out->y0 = y; out->x1 = x + bwk; out->y1 = y + bhk;
    return 1;
}
/* the blocks of rectangle d of buffer (bp, bw, psm) get value v in blk_stale; only = 1:
 * only blocks lying wholly inside d */
static void blk_mark(gpu_renderer *r, uint32_t bp, uint32_t bw, int psm, GpuRect d, uint8_t v, int only)
{
    int bwk, bhk, pw, ph;
    uint32_t bwp;
    if (!blk_dims(psm, &bwk, &bhk)) {
        if (!only) memset(r->blk_stale, v ? 0xFF : 0, sizeof r->blk_stale);
        return;
    }
    if (d.x0 < 0) d.x0 = 0;
    if (d.y0 < 0) d.y0 = 0;
    if (d.x1 > 2048) d.x1 = 2048;
    if (d.y1 > 2048) d.y1 = 2048;
    if (d.x1 <= d.x0 || d.y1 <= d.y0) return;
    page_geom(psm, bw ? bw : 1, &pw, &ph, &bwp);
    int bx0, by0, bx1, by1;
    if (only) { bx0 = (d.x0 + bwk - 1) / bwk; by0 = (d.y0 + bhk - 1) / bhk; bx1 = d.x1 / bwk; by1 = d.y1 / bhk; }
    else { bx0 = d.x0 / bwk; by0 = d.y0 / bhk; bx1 = (d.x1 + bwk - 1) / bwk; by1 = (d.y1 + bhk - 1) / bhk; }
    int cpw = pw / bwk, cph = ph / bhk;
    for (int by = by0; by < by1; by++) {
        for (int bx = bx0; bx < bx1; bx++) {
            /* page-aligned buffer: a page whose every block cell lies in the run is set
             * whole (at its first cell; its other cells are skipped) */
            if (!(bp & 31)) {
                int px0 = bx / cpw * cpw, py0 = by / cph * cph;
                if (px0 >= bx0 && px0 + cpw <= bx1 && py0 >= by0 && py0 + cph <= by1) {
                    if (bx == px0 && by == py0) {
                        uint32_t pg = (bp >> 5) + (uint32_t)(bx / cpw) + (uint32_t)(by / cph) * bwp;
                        memset(r->blk_stale + ((pg & 511u) * 32u), v ? 0xFF : 0, 32 * sizeof(uint64_t));
                    }
                    continue;
                }
            }
            uint32_t b = gs_pixel_addr(psm, bp, bw ? bw : 1, (uint32_t)(bx * bwk), (uint32_t)(by * bhk), NULL) >> 8;
            r->blk_stale[b & 16383u] = v ? ~0ull : 0ull;
        }
    }
}
/* every block of pages p: value v */
static void blk_mark_pages(gpu_renderer *r, const Pages &p, uint8_t v)
{
    for (uint32_t pg = 0; pg < 512; pg++)
        if (p.get(pg)) memset(r->blk_stale + pg * 32u, v ? 0xFF : 0, 32 * sizeof(uint64_t));
}

/* tex: the caller reads only texels it has made current (the blocks of a
 * texture rect, lazy transfers): pages that still hold pending blocks are
 * uploaded but stay marked newer in local memory, so they go up again once
 * those blocks are written.  Otherwise every pending transfer in the pages is
 * written first (targets read whole pages). */
static void upload_pages(gpu_renderer *r, const Pages &want, int tex = 0)
{
    Pages keep;
    keep.clear();
    {
        Pages lz;
        lz.clear();
        if (r->gs && gs_mem_lazy_pages(r->gs, lz.w) && lz.overlaps(want)) {
            Pages p = lz.and_(want);
            if (tex) {
                keep = p;
            } else {
                /* written into local memory now, without hooks (the renderer
                 * holds nothing there: lazy_ok) */
                Pages w;
                w.clear();
                gs_mem_lazy_take_written(r->gs, NULL);
                gs_mem_materialize(r->gs, p.w, 0);
                gs_mem_lazy_take_written(r->gs, w.w);
                r->cpu_newer.add(w);
            }
        }
    }
    if (r->split.overlaps(want)) merge_split(r);
    Pages p = r->cpu_newer.and_(want);
    if (!p.any()) return;
    for (uint32_t pg = 0; pg < 512;) {
        if (!p.get(pg)) { pg++; continue; }
        uint32_t e = pg;
        while (e < 512 && p.get(e)) e++;
        r->be->mirror_upload(pg * 8192u, (e - pg) * 8192u, r->gs->vram + pg * 8192u);
        r->stats.upload_bytes += (e - pg) * 8192u;
        pg = e;
    }
    r->cpu_newer.sub(p);
    stamp_pages(r, p);
    r->cpu_newer.add(keep);
}

static void download_pages(gpu_renderer *r, const Pages &want)
{
    if (r->split.overlaps(want)) merge_split(r);
    Pages p = r->gpu_newer.and_(want);
    if (!p.any()) return;
    uint32_t runs[1024];
    int n = 0;
    for (uint32_t pg = 0; pg < 512;) {
        if (!p.get(pg)) { pg++; continue; }
        uint32_t e = pg;
        while (e < 512 && p.get(e)) e++;
        runs[2 * n] = pg * 8192u;
        runs[2 * n + 1] = (e - pg) * 8192u;
        r->stats.download_bytes += (e - pg) * 8192u;
        n++;
        pg = e;
    }
    double t0 = now_us();
    r->be->mirror_download(runs, n, r->gs->vram);
    r->stats.download_us += (uint64_t)(now_us() - t0);
    r->stats.downloads++;
    r->gpu_newer.sub(p);
    blk_mark_pages(r, p, 0);
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

static void rt_writeback(gpu_renderer *r, Rt &t)
{
    if (!t.has_dirty) return;
    if (r->split.overlaps(t.pages)) merge_split(r);
    upload_pages(r, t.pages);      /* partial-word formats merge with the mirror */
    GpuRect d = t.dirty;
    if (d.x1 > t.w) d.x1 = t.w;
    if (d.y1 > t.h) d.y1 = t.h;
    if (d.x1 > d.x0 && d.y1 > d.y0) {
        r->be->rt_writeback(t.id, t.bp, t.bw, t.psm, d);
        blk_mark(r, t.bp, t.bw, t.psm, d, 1, 0);
        Pages wp = pages_of(t.bp, t.bw, t.psm, d.x0, d.y0, d.x1, d.y1);
        r->gpu_newer.add(wp);
        stamp_pages(r, wp);
        gs_mem_gen_bump(r->gs, wp.w);   /* upload elision: these pages changed */
        r->stats.rt_writebacks++;
    }
    t.has_dirty = 0;
}

static void rt_load_rows(gpu_renderer *r, Rt &t, int y0, int y1)
{
    if (y1 <= y0) return;
    upload_pages(r, pages_of(t.bp, t.bw, t.psm, 0, y0, t.w, y1));
    GpuRect rc = { 0, y0, t.w, y1 };
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

/* Pages a transfer into rc writes every bit of: whole page cells inside the
 * rectangle, a page-aligned BP and a format that fills its words. */
static Pages whole_pages(const gs_mem_rect &rc)
{
    Pages p;
    p.clear();
    int psm = rc.psm;
    if ((rc.bp & 31) || psm == GS_PSMCT24 || psm == GS_PSMZ24 || psm == GS_PSMT8H ||
        psm == GS_PSMT4HL || psm == GS_PSMT4HH)
        return p;
    int pw, ph;
    uint32_t bwp;
    page_geom(psm, rc.bw, &pw, &ph, &bwp);
    int x0 = ((int)rc.x + pw - 1) / pw, x1 = (int)(rc.x + rc.w) / pw;
    int y0 = ((int)rc.y + ph - 1) / ph, y1 = (int)(rc.y + rc.h) / ph;
    for (int r = y0; r < y1; r++)
        for (int c = x0; c < x1; c++) p.set((rc.bp >> 5) + (uint32_t)c + (uint32_t)r * bwp);
    return p;
}

static uint8_t *split_mask(gpu_renderer *r)
{
    if (!r->merge_mask) r->merge_mask = (uint8_t *)calloc(1, GS_VRAM_BYTES);
    return r->merge_mask;
}

/* the bits the first npx pixels of a transfer into rc wrote, added to the
 * mask of the split pages (the mask stays zero elsewhere) */
static void split_add(gpu_renderer *r, const gs_mem_rect &rc, uint64_t npx)
{
    uint8_t *m = split_mask(r);
    Pages tp = pages_of_rect(&rc);
    if (!tp.overlaps(r->split)) return;
    /* only the rows of page bands that hold split pages (a page-aligned
     * buffer: each band of page rows maps to its own pages) */
    uint32_t ya = rc.y, yb = rc.y + rc.h;
    if (!(rc.bp & 31)) {
        int pw, ph;
        uint32_t bwp;
        page_geom(rc.psm, rc.bw, &pw, &ph, &bwp);
        uint32_t lo = yb, hi = ya;
        for (uint32_t y = rc.y; y < rc.y + rc.h;) {
            uint32_t e = (y / (uint32_t)ph + 1) * (uint32_t)ph;
            if (e > rc.y + rc.h) e = rc.y + rc.h;
            if (pages_of(rc.bp, rc.bw, rc.psm, (int)rc.x, (int)y, (int)(rc.x + rc.w), (int)e).overlaps(r->split)) {
                if (y < lo) lo = y;
                hi = e;
            }
            y = e;
        }
        if (hi <= lo) return;
        ya = lo; yb = hi;
    }
    uint64_t skip = (uint64_t)(ya - rc.y) * rc.w;
    if (npx > skip) {
        uint64_t n = npx - skip;
        if (n > (uint64_t)(yb - ya) * rc.w) n = (uint64_t)(yb - ya) * rc.w;
        gs_xfer_mask(rc.psm, rc.bp, rc.bw, rc.x, ya, rc.w, yb - ya, (uint32_t)n, m);
    }
    for (uint32_t pg = 0; pg < 512; pg++)
        if (tp.get(pg) && !r->split.get(pg)) memset(m + (size_t)pg * 8192u, 0, 8192u);
}

/* pixels of the open transfer written so far */
static uint64_t xfer_done(const gs_state *gs, const gs_mem_rect &rc)
{
    uint64_t n = (uint64_t)gs->xfer_y * rc.w + gs->xfer_x;
    return n > (uint64_t)rc.w * rc.h ? (uint64_t)rc.w * rc.h : n;
}

/* Split pages -> mirror-newer: the collected transfer bits (and those of the
 * open transfer so far) are merged into the mirror, (data, mask) per word,
 * after everything queued before.  A page whose every bit was written by
 * transfers is current in both copies.  If the open transfer writes split
 * pages, they are read back (now complete) and the rest of the transfer is
 * an ordinary CPU write. */
static void merge_split(gpu_renderer *r)
{
    if (!r->split.any()) return;
    const gs_state *gs = r->gs;
    uint8_t *m = split_mask(r);
    if (r->xfer_split) split_add(r, r->xfer_rect, xfer_done(gs, r->xfer_rect));
    Pages sp = r->split;
    r->split.clear();
    Pages whole;
    whole.clear();
    for (uint32_t pg = 0; pg < 512;) {
        if (!sp.get(pg)) { pg++; continue; }
        uint32_t e = pg;
        while (e < 512 && sp.get(e)) e++;
        uint32_t w0 = pg * 2048u, n = (e - pg) * 2048u;
        r->merge_dm.resize((size_t)n * 2);
        uint32_t *dm = r->merge_dm.data();
        const uint8_t *v = gs->vram + (size_t)w0 * 4, *mk = m + (size_t)w0 * 4;
        for (uint32_t i = 0; i < n; i++) {
            uint32_t d, k;
            memcpy(&d, v + 4 * i, 4);
            memcpy(&k, mk + 4 * i, 4);
            dm[2 * i] = d & k;
            dm[2 * i + 1] = k;
            if (r->cfg.fault == 8) { dm[2 * i] = d; dm[2 * i + 1] = 0xFFFFFFFFu; }   /* control: no mask */
        }
        r->be->mirror_merge(w0, n, dm);
        for (uint32_t q = pg; q < e; q++) {
            const uint32_t *pm = (const uint32_t *)(m + (size_t)q * 8192u);
            bool all = true;
            for (uint32_t i = 0; i < 2048u && all; i++) all = pm[i] == 0xFFFFFFFFu;
            if (all) whole.set(q);
            memset(m + (size_t)q * 8192u, 0, 8192u);
        }
        pg = e;
    }
    stamp_pages(r, sp);
    r->stats.merges++;
    r->gpu_newer.add(sp);
    r->gpu_newer.sub(whole);
    if (r->xfer_split) {
        r->xfer_split = 0;
        Pages d = pages_of_rect(&r->xfer_rect).and_(sp);
        download_pages(r, d);
        r->cpu_newer.add(d);
    }
}

/* The CPU is about to read `p`: everything newer on the GPU goes back. */
static void sync_for_cpu_read(gpu_renderer *r, const Pages &p)
{
    for (Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(p)) rt_writeback(r, t);
    download_pages(r, p);
}

static void flush_batch(gpu_renderer *r);
static volatile uint32_t g_filt_frame;   /* $RG_NR_FILTLOG: EE frame (gpu_nr_filtlog_frame) */
extern "C" void gpu_nr_filtlog_frame(uint32_t frame) { g_filt_frame = frame; }
static void clut_resolve(gpu_renderer *r);

/* Pages the pending batch can draw into: FRAME and ZBUF over its bounding
 * box (conservatively both, whatever the masks). */
static Pages pending_writes(gpu_renderer *r)
{
    Pages w;
    w.clear();
    if (r->verts.empty()) return w;
    const Derived &d = r->dv;
    uint32_t fw = d.fbw ? d.fbw : 1;
    const GpuRect &b = r->bbox;
    w = pages_of(d.fbp, fw, d.fpsm, b.x0, b.y0, b.x1, b.y1);
    w.add(pages_of(d.zbp, fw, d.zpsm, b.x0, b.y0, b.x1, b.y1));
    return w;
}

/* the CPU writes pages p: early copies of them are void */
static void hot_cpu_write(gpu_renderer *r, const Pages &p)
{
    for (HotRead &h : r->hot)
        if (h.used && h.pages.overlaps(p)) h.state = 0;
}

static void cpu_write_begin(gpu_renderer *r, const Pages &p, const gs_mem_rect *xfer = NULL)
{
    /* the pending batch is drawn first when the write meets what it reads
     * (textures: the mirror is sampled at flush) or draws */
    Pages rw = pending_writes(r);
    rw.add(r->batch_read);
    if (rw.overlaps(p)) flush_batch(r);
    Pages cw = p;
    if (xfer) {
        /* a host->local transfer: targets with newer data go to the mirror
         * (GPU work, no wait), and the pages the mirror is newer on become
         * split pages instead of being read back (merge_split) */
        for (Rt &t : r->rts)
            if (t.has_dirty && t.pages.overlaps(p)) rt_writeback(r, t);
        Pages g = r->gpu_newer.and_(p);
        r->gpu_newer.sub(g);
        r->split.add(g);
        r->xfer_split = r->split.overlaps(p);
        r->xfer_rect = *xfer;
        cw.sub(r->split);
    } else {
        sync_for_cpu_read(r, p);
    }
    for (Rt &t : r->rts)
        if (t.pages.overlaps(p)) { t.stale = 1; t.stale_pages.add(p); }
    r->cpu_newer.add(cw);
    hot_cpu_write(r, p);
}

static void cpu_write_end(gpu_renderer *r, const Pages &p)
{
    for (Rt &t : r->rts)
        if (t.pages.overlaps(p)) { t.stale = 1; t.stale_pages.add(p); }
    r->cpu_newer.add(p);
    hot_cpu_write(r, p);
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
    upload_pages(r, sp);
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
    Rt srcs[4];
    int nsrc = 0;
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
    return t;
}

static Rt *rt_find_id(gpu_renderer *r, int id)
{
    for (Rt &x : r->rts) if (x.id == id) return &x;
    return NULL;
}

/* ================================================== state derivation */
static void make_key(gpu_renderer *r, const gs_state *gs, Key *k)
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

static void derive(gpu_renderer *r, const gs_state *gs, const Key &k, Derived *d)
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

/* ===================================================== batch submit */
/* The live render target the pending batch can sample directly instead of
 * the mirror (docs/GPU.md "Direct sampling"), or NULL: same base and width,
 * a format whose texels the target holds exactly (same PSM, or CT32 read as
 * CT24), not stale, every texel the batch can address inside the rows the
 * target owns, no other target sharing the pages read, and not the depth
 * buffer this batch tests against (a bound DSV cannot be sampled). */
static int g_ds_why;   /* $RG_NR_FILTLOG: why direct_source declined (G lines) */
static Rt *direct_source(gpu_renderer *r, const Rt *ct, const Rt *zt)
{
    const Derived &d = r->dv;
    g_ds_why = 1;
    if (!d.tme || !d.direct_ok) return NULL;
    int want_depth = (d.tpsm & 0x30) == 0x30;
    Rt *s = NULL;
    for (Rt &t : r->rts) {
        if (t.depth != want_depth || t.bp != d.tbp || t.bw != d.tbw) continue;
        if (t.psm == d.tpsm || (t.psm == GS_PSMCT32 && d.tpsm == GS_PSMCT24)) { s = &t; break; }
    }
    g_ds_why = !s ? 2 : 4;
    if (!s || s == zt) return NULL;
    /* (the read set carries a 2-texel bilinear margin past the last texel: for a source
     * other than the target drawn into, up to that past the target is still the target, the
     * shader clamps to its edge (DIRECT bits 16-28), as the native path does.  Item 8:
     * composites of character parts at the bottom of the frame and the blur passes read the
     * 1x mirror for that margin.  In place (s == ct) the texels past the target can be ones
     * the batch itself reads back exactly: gpu-tests scene.alias_pages "in-place strips") */
    GpuRect tr = r->batch_texrect;
    if (s != ct) {
        if (tr.x1 > s->w && tr.x1 <= s->w + 2) tr.x1 = s->w;
        if (tr.y1 > s->h && tr.y1 <= s->h + 2) tr.y1 = s->h;
    }
    g_ds_why = 5;
    if (tr.x0 < 0 || tr.y0 < 0 || tr.x1 > s->w || tr.y1 > s->h) return NULL;
    /* the pages actually read (the batch's read set keeps margins that can
     * reach past the target, e.g. into the display buffer after the frame) */
    Pages rp = pages_of(d.tbp, d.tbw, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
    g_ds_why = 3;
    if (!rt_current_in(r, *s, rp)) return NULL;   /* (stale where it is read) */
    g_ds_why = 6;
    for (const Rt &t : r->rts)
        if (&t != s && t.pages.overlaps(rp)) return NULL;
    return s;
}

/* Screen-effect hook (graphics.bloom / depth_of_field / motion_blur,
 * docs/GPU.md "Screen effects").  A batch that belongs to one of the
 * game's full-screen effect passes would be classified here (GPU_FX_*) and,
 * per r->enh.fx[class], drawn as the original, at full internal resolution
 * ("enhanced") or skipped ("off").  Recognising the passes needs game-side
 * knowledge (which buffers, states and call sites form each effect: the
 * bloom/DOF chains of the field renderer, not reached yet); until then
 * nothing is classified and every mode draws the original. */
static int effect_class(gpu_renderer *r, const GpuDraw &g)
{
    (void)r;
    (void)g;
    return -1;
}

/* Copy the pages of a hot read region to a staging slot now: the mirror
 * first made current for them (uploads, write-backs of targets dirty
 * there; GPU work, no wait). */
static void hot_snapshot(gpu_renderer *r, HotRead &h)
{
    upload_pages(r, h.pages);
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
            r->be->rt_writeback(t.id, t.bp, t.bw, t.psm, d);
            blk_mark(r, t.bp, t.bw, t.psm, d, 1, 0);
            Pages wp;
            wp.clear();
            wp.set(pg);
            r->gpu_newer.add(wp);
            stamp_pages(r, wp);
            gs_mem_gen_bump(r->gs, wp.w);
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
    h.slot = r->be->snap_copy(runs, n);
    h.state = h.slot >= 0 ? 1 : 0;
    if (h.slot >= 0) r->stats.early_copies++;
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

static void flush_batch(gpu_renderer *r)
{
    if (r->verts.empty()) {
        r->boxes.clear();
        r->batch_read.clear();
        r->batch_written.clear();
        return;
    }
    Derived &d = r->dv;
    GpuRect bb = r->bbox;
    int fbw = (int)(d.fbw ? d.fbw : 1);
    /* targets */
    Rt *ct = rt_bind(r, 0, d.fbp, (uint32_t)fbw, d.fpsm, bb.y1, -1);
    Rt *zt = NULL;
    if (ct && d.need_depth) {
        int cid = ct->id;
        /* A colour target whose rows reach the Z buffer's pages (or the
         * other way round) while this state's scissor keeps the draws
         * apart (otherwise d.alias): both stay live for the draw, so the
         * depth target must load what the colour target drew there
         * (docs/GPU.md "Checkpoint 4"). */
        if (ct->has_dirty && r->cfg.fault != 10) {
            int zh = bb.y1;
            for (const Rt &x : r->rts)
                if (x.depth && x.bp == d.zbp && x.bw == (uint32_t)fbw && x.psm == d.zpsm && x.h > zh) zh = x.h;
            int ph = page_h(d.zpsm);
            zh = (zh + ph - 1) / ph * ph;
            if (ct->pages.overlaps(pages_of(d.zbp, (uint32_t)fbw, d.zpsm, 0, 0, fbw * 64, zh)))
                rt_writeback(r, *ct);
        }
        zt = rt_bind(r, 1, d.zbp, (uint32_t)fbw, d.zpsm, bb.y1, cid);
        ct = rt_find_id(r, cid);
        if (!ct) zt = NULL;
    }
    if (!ct) {
        r->verts.clear(); r->tris.clear(); r->boxes.clear();
        r->batch_read.clear(); r->batch_written.clear();
        return;
    }
    if (zt && zt->h_alloc != ct->h_alloc) {
        Rt *small = zt->h_alloc < ct->h_alloc ? zt : ct;
        small->h_alloc = 2048;
        r->be->rt_resize(small->id, small->w, small->h_alloc);
    }
    /* textures: a live target sampled directly, or the mirror, which must
     * then be current */
    Rt *src = NULL;
    if (d.tme) {
        src = direct_source(r, ct, zt);
        if (src) {
            r->stats.direct_samples++;
            if (src->has_dirty) r->stats.writebacks_avoided++;
        } else {
            for (Rt &t : r->rts)
                if (t.has_dirty && t.pages.overlaps(r->batch_read) &&
                    !(d.hbyte_tex && (t.psm == GS_PSMCT24 || t.psm == GS_PSMZ24)))
                    rt_writeback(r, t);
            upload_pages(r, r->batch_read, 1);
        }
        if (d.indexed && (!r->clut_valid || r->clut_uploaded_gen != r->key.clut_gen)) {
            GpuClutCB c;
            memset(&c, 0, sizeof c);
            for (int i = 0; i < 256; i++)
                c.c[i >> 2][i & 3] = (uint32_t)r->batch_clut[2 * i] |
                                     ((uint32_t)r->batch_clut[2 * i + 1] << 16);
            if (r->clut_own_any) r->be->set_clut_part(c, r->clut_own);
            else r->be->set_clut(c);
            r->clut_uploaded_gen = r->key.clut_gen;
            r->clut_valid = 1;
        }
    }
    if (r->filt_log) {
        /* GS draw path batch: fb, texture, direct (live target) or decoded from the 1x mirror */
        const GpuRect &tr = r->batch_texrect;
        fprintf(r->filt_log,
                "G %u fb %u bw %u psm %02x box %d,%d-%d,%d tme %d tbp %u tbw %u tpsm %02x read %d,%d-%d,%d src %s\n",
                (unsigned)g_filt_frame, d.fbp, d.fbw, d.fpsm, bb.x0, bb.y0, bb.x1, bb.y1, d.tme, d.tme ? d.tbp : 0u,
                d.tme ? d.tbw : 0u, d.tme ? d.tpsm : 0, tr.x0, tr.y0, tr.x1, tr.y1,
                !d.tme ? "-" : src ? "target" : g_ds_why == 1 ? "mirror(format)" : g_ds_why == 2 ? "mirror(no-target)" :
                g_ds_why == 3 ? "mirror(stale)" : g_ds_why == 4 ? "mirror(is-z)" : g_ds_why == 5 ? "mirror(outside)" :
                "mirror(other-target)");
    }
    GpuDraw g;
    memset(&g, 0, sizeof g);
    g.color_rt = ct->id;
    g.depth_rt = zt ? zt->id : -1;
    g.rt_w = ct->w;
    g.rt_h = ct->h_alloc;
    g.verts = r->verts.data();
    g.nverts = (uint32_t)r->verts.size();
    g.tris = r->tris.empty() ? NULL : r->tris.data();
    g.ntris = (uint32_t)r->tris.size();
    g.cb = d.cb;
    /* power-of-two viewport: (x + 0.5) * 2 / vp - 1 is exact in float, so
     * every 12.4 vertex lands exactly on the rasterizer's subpixel grid */
    g.vp_w = 1; while (g.vp_w < g.rt_w) g.vp_w <<= 1;
    g.vp_h = 1; while (g.vp_h < g.rt_h) g.vp_h <<= 1;
    float kx = 2.0f / (float)g.vp_w, ky = 2.0f / (float)g.vp_h;
    memcpy(&g.cb.d[0][0], &kx, 4);
    memcpy(&g.cb.d[0][1], &ky, 4);
    g.zfunc = zt ? d.zfunc : GZ_OFF;
    if (!zt) g.cb.d[0][3] |= GF_NOZ;
    g.scissor.x0 = d.scx0; g.scissor.y0 = d.scy0;
    g.scissor.x1 = d.scx1 < ct->w ? d.scx1 : ct->w;
    g.scissor.y1 = d.scy1 < ct->h ? d.scy1 : ct->h;
    g.need_dst = d.need_dst;
    g.dst = bb;
    g.tex_rt = -1;
    if (src) {
        g.tex_rt = src->id;
        g.tex_snap = src == ct;   /* in place: sample a copy of the texels */
        g.tex_rect = r->batch_texrect;
        if (g.tex_rect.x1 > src->w) g.tex_rect.x1 = src->w;   /* (the margin direct_source allows) */
        if (g.tex_rect.y1 > src->h) g.tex_rect.y1 = src->h;
        g.cb.d[3][3] = GD_DIRECT | (src->depth ? GD_DEPTH : 0u) | ((uint32_t)src->psm << 8) |
                       ((uint32_t)(src->w / 64) & 63u) << 16 | ((uint32_t)(src->h / 32) & 127u) << 22;
        if (g.tex_snap) r->stats.tex_copies++;
    }
    /* Enhancements: the texture filter override and anisotropic taps apply
     * to ordinary textures only (no live render target in the pages read,
     * not sampled directly), so post-processing passes and format tricks
     * keep the GS filter.  Original: D[11] = 0. */
    if (d.tme && !src && (r->enh.tex_filter || r->enh.aniso > 1)) {
        int ordinary = tex_pages_ordinary(r, r->batch_read, NULL);
        if (ordinary) {
            int an = r->enh.aniso > 1 ? (r->enh.aniso > 16 ? 16 : r->enh.aniso) : 0;
            g.cb.d[11][0] = (uint32_t)(r->enh.tex_filter & 3) | ((uint32_t)an << 4) | GE_ORDINARY;
            /* anisotropic taps reach past the batch's read set: make the
             * texture's whole page set current in the mirror */
            if (an) upload_pages(r, d.tex_pages, 1);
        }
    }
    /* Decoded texture (docs/GPU.md "Performance"): the level-0 texels the
     * batch can read, decoded once from the mirror (indexed formats through
     * the CLUT, TEXA expansion) into RGBA8.  The pixel shader filters the
     * decoded texels exactly as it filters tex_fetch's (the GS order:
     * texel -> CLUT -> expansion per tap, then the bilinear weights), and
     * reads texels outside the rect from the mirror as before. */
    if (d.tme && !src && !r->cfg.no_tex_decode) {
        GpuRect tr = r->batch_texrect;
        const GpuRect &wr = d.tex_wrap;
        /* anisotropic taps (up to 2 x 16 bilinear samples per pixel) spread
         * past the batch's texel rect: decode the whole level-0 wrap rect
         * (its pages were made current above), whatever the format; the
         * decoded copy then stays cached while the texture is unchanged
         * (docs/PERF-3D.md) */
        const bool aniso_dec = (g.cb.d[11][0] >> 4) & 31u;
        if (aniso_dec) tr = wr;
        if (tr.x0 < wr.x0) tr.x0 = wr.x0;
        if (tr.y0 < wr.y0) tr.y0 = wr.y0;
        if (tr.x1 > wr.x1) tr.x1 = wr.x1;
        if (tr.y1 > wr.y1) tr.y1 = wr.y1;
        if (tr.x0 < 0) tr.x0 = 0;
        if (tr.y0 < 0) tr.y0 = 0;
        if (tr.x1 > 1024) tr.x1 = 1024;
        if (tr.y1 > 1024) tr.y1 = 1024;
        if (tr.x1 > tr.x0 && tr.y1 > tr.y0) {
            Pages rp = pages_of(d.tbp, d.tbw ? d.tbw : 1, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
            uint32_t newest = 0;
            for (uint32_t pg = 0; pg < 512; pg++)
                if (rp.get(pg) && r->page_stamp[pg] > newest) newest = r->page_stamp[pg];
            uint64_t cg = d.indexed ? r->key.clut_gen : 0;
            g.dec = 1;
            g.dec_rect = tr;
            g.dec_key[0] = d.tbp | (d.tbw << 14) | ((uint32_t)d.tpsm << 20);
            g.dec_key[1] = d.cb.d[4][2];                       /* CPSM, CSA */
            g.dec_key[2] = d.cb.d[6][1] | (d.cb.d[6][2] << 8) | (d.cb.d[6][3] << 16);   /* TEXA */
            g.dec_key[3] = (uint32_t)cg;
            g.dec_key[4] = (uint32_t)(cg >> 32);
            g.dec_key[5] = newest;
            /* decode when it pays: indexed textures (each tap otherwise reads
             * the mirror and then the CLUT), at most one texel per covered
             * sample (measured: decoding direct-colour textures, or more
             * texels, costs more GPU time than the taps it saves) */
            double area = (double)(tr.x1 - tr.x0) * (double)(tr.y1 - tr.y0);
            double px = (double)(bb.x1 - bb.x0) * (double)(bb.y1 - bb.y0) * r->scale * r->scale;
            g.dec_new = (d.indexed && area <= px) || aniso_dec;
        }
    }
    (void)effect_class(r, g);
    g.npass = d.npass;
    int cwrite = 0, zwrite = 0;
    for (int i = 0; i < d.npass; i++) {
        g.pass[i] = d.pass[i];
        if (!zt) g.pass[i].zwrite = 0;
        if (g.pass[i].cmask) cwrite = 1;
        if (g.pass[i].zwrite) zwrite = 1;
    }
    g.rov = d.rov;
    if (g.rov) g.need_dst = 0;
    r->be->draw(g);
    r->stats.batches++;
    if (r->trace)
        fprintf(r->trace, "B %llu f %u/%u %02x z %u %02x zf %d tex %u/%u %02x box %d,%d-%d,%d n %u tris %u rov %d dir %d np %d cw %llx\n",
                (unsigned long long)r->stats.batches, d.fbp, d.fbw, d.fpsm, zt ? d.zbp : 0u, d.zpsm, (int)g.zfunc,
                d.tme ? d.tbp : 0u, d.tbw, d.tpsm, bb.x0, bb.y0, bb.x1, bb.y1, g.nverts, g.ntris, g.rov, src ? 1 : 0,
                d.npass, (unsigned long long)d.cmask_base);
    /* let the GPU start on what is queued while the CPU goes on (the
     * display read-back at the end of the field then waits for less).
     * Counted in native pixels: each Flush costs the CPU ~50-70 us in the
     * driver, and at x3 a count of upscaled pixels kicked 9 times as often
     * for the same GPU-bound field (docs/GPU.md "Checkpoint 4"). */
    r->kick_px += (double)(bb.x1 - bb.x0) * (double)(bb.y1 - bb.y0);
    if (r->kick_at > 0.0 && r->kick_px >= r->kick_at) {
        double t0 = now_us();
        r->be->kick();
        r->stats.kick_us += (uint64_t)(now_us() - t0);
        r->stats.kicks++;
        r->kick_px = 0.0;
    }
    r->stats.passes += g.rov ? 1u : (uint64_t)d.npass;
    if (g.rov) r->stats.rov_batches++;
    else if (d.need_dst) r->stats.dst_copies++;
    r->stats.tex_decodes = r->be->n_decodes;
    r->stats.rt_pool_hits = r->be->n_rt_pool_hits;
    r->stats.tex_decode_hits = r->be->n_decode_hits;
    GpuRect wb = bb;
    if (wb.x0 < g.scissor.x0) wb.x0 = g.scissor.x0;
    if (wb.y0 < g.scissor.y0) wb.y0 = g.scissor.y0;
    if (wb.x1 > g.scissor.x1) wb.x1 = g.scissor.x1;
    if (wb.y1 > g.scissor.y1) wb.y1 = g.scissor.y1;
    if (wb.x1 > wb.x0 && wb.y1 > wb.y0) {
        if (cwrite) {
            if (ct->has_dirty) rect_union(ct->dirty, wb);
            else { ct->dirty = wb; ct->has_dirty = 1; }
            r->drawn.add(pages_of(ct->bp, ct->bw, ct->psm, wb.x0, wb.y0, wb.x1, wb.y1));
        }
        if (zt && zwrite) {
            if (zt->has_dirty) rect_union(zt->dirty, wb);
            else { zt->dirty = wb; zt->has_dirty = 1; }
            r->drawn.add(pages_of(zt->bp, zt->bw, zt->psm, wb.x0, wb.y0, wb.x1, wb.y1));
        }
    }
    /* Colour and depth targets sharing pages: each now holds an old copy of
     * what the other drew there (their draws never share pages inside the
     * scissor, so the two write-backs do not overlap).  Both go to the
     * mirror and reload on their next use, so neither a later draw nor a
     * write-back of a dirty rectangle can bring old bytes back. */
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
            if (cwrite) wpg.add(pages_of(ct->bp, ct->bw, ct->psm, wb.x0, wb.y0, wb.x1, wb.y1));
            if (zt && zwrite) wpg.add(pages_of(zt->bp, zt->bw, zt->psm, wb.x0, wb.y0, wb.x1, wb.y1));
        }
        hot_after_batch(r, wpg);
    }
    r->verts.clear();
    r->tris.clear();
    r->boxes.clear();
    r->batch_read.clear();
    r->batch_written.clear();
}

/* ================================================= primitive expansion */
static void set_attr(GpuVertex *o, const gs_vertex *v)
{
    o->r = v->r; o->g = v->g; o->b = v->b; o->a = v->a;
    o->s = v->s; o->t = v->t; o->q = v->q;
    o->u = (float)v->u / 16.0f; o->v = (float)v->v / 16.0f;
    o->fog = v->f;
    o->zf = (float)v->z;
    o->zi = v->z;
    o->vflags = 0;
    o->spr_x0 = o->spr_y0 = o->spr_dx = o->spr_dy = 0;
    o->spr_s0 = o->spr_s1 = o->spr_t0 = o->spr_t1 = 0;
    o->spr_u0 = o->spr_u1 = o->spr_v0 = o->spr_v1 = 0;
}

static void set_flat(GpuVertex *o, const gs_vertex *pv)
{
    o->r = pv->r; o->g = pv->g; o->b = pv->b; o->a = pv->a; o->fog = pv->f;
}

static int ceil16(int v) { return (v + 15) >> 4; }   /* arithmetic shift */

/* Texel range [lo, hi) of one axis that a primitive can sample, given the
 * extreme coordinates (texels) at its vertices; false = unknown (use the
 * whole texture).  Conservative: two texels of margin for float error and
 * the bilinear taps.  Mirrors the wrap modes of gs_tex.c. */
static bool axis_range(double cmin, double cmax, int size, int wm, int mn, int mx, int *lo,
                       int *hi)
{
    if (!(cmin >= -4096.0 && cmax <= 4096.0)) return false;   /* also NaN */
    int a = (int)floor(cmin) - 2, b = (int)floor(cmax) + 3;
    switch (wm) {
    case 0:   /* REPEAT: exact only when nothing wraps */
        if (a < 0 || b > size) return false;
        break;
    case 1:   /* CLAMP */
        a = a < 0 ? 0 : (a > size - 1 ? size - 1 : a);
        b = b < 1 ? 1 : (b > size ? size : b);
        break;
    case 2:   /* REGION_CLAMP */
        a = a < mn ? mn : (a > mx ? mx : a);
        b = b < mn + 1 ? mn + 1 : (b > mx + 1 ? mx + 1 : b);
        break;
    default:
        return false;
    }
    if (b <= a) b = a + 1;
    *lo = a; *hi = b;
    return true;
}

/* The pages one primitive can sample: its texel bounding box when the
 * coordinates are bounded by the vertices (UV; STQ with Q of one sign),
 * otherwise every page of the texture. */
static Pages prim_read_pages(const Key &k, const Derived &d, const gs_vertex *v, int nv, int type,
                             GpuRect *tr)
{
    *tr = d.tex_wrap;   /* level-0 texels it can address (refined below) */
    if (!d.tex_lvl0) return d.tex_pages;
    int tw = (int)BITS(k.tex0, 26, 4), th = (int)BITS(k.tex0, 30, 4);
    if (tw > 10) tw = 10;
    if (th > 10) th = 10;
    int W = 1 << tw, H = 1 << th;
    double umin = 1e30, umax = -1e30, vmin = 1e30, vmax = -1e30;
    int n = type == GS_PRIM_POINT ? 1 : (type == GS_PRIM_SPRITE || type == GS_PRIM_LINE ||
                                         type == GS_PRIM_LINESTRIP) ? 2 : 3;
    if (n > nv) n = nv;
    for (int i = 0; i < n; i++) {
        double u, w;
        if (d.fst) {
            u = v[i].u / 16.0; w = v[i].v / 16.0;
        } else {
            double q = type == GS_PRIM_SPRITE ? v[1].q : v[i].q;
            double q0 = type == GS_PRIM_SPRITE ? v[1].q : v[0].q;
            if (!(q != 0.0) || (q > 0) != (q0 > 0)) return d.tex_pages;
            u = v[i].s / q * W; w = v[i].t / q * H;
        }
        if (u < umin) umin = u;
        if (u > umax) umax = u;
        if (w < vmin) vmin = w;
        if (w > vmax) vmax = w;
    }
    int u0, u1, v0, v1;
    if (!axis_range(umin, umax, W, (int)BITS(k.clamp, 0, 2), (int)BITS(k.clamp, 4, 10),
                    (int)BITS(k.clamp, 14, 10), &u0, &u1) ||
        !axis_range(vmin, vmax, H, (int)BITS(k.clamp, 2, 2), (int)BITS(k.clamp, 24, 10),
                    (int)BITS(k.clamp, 34, 10), &v0, &v1))
        return d.tex_pages;
    uint32_t tbp = BITS(k.tex0, 0, 14), tbw = BITS(k.tex0, 14, 6);
    tr->x0 = u0; tr->y0 = v0; tr->x1 = u1; tr->y1 = v1;
    return pages_of(tbp, tbw ? tbw : 1, (int)BITS(k.tex0, 20, 6), u0, v0, u1, v1);
}

/* The exact level-0 texels a UV sprite samples (for the direct-sampling
 * decision, which needs the rect inside the source target's rows; the page
 * set keeps axis_range's margins): the reference's DDA over the covered
 * pixels, +- half a step for the sub-sample offsets of bilinear direct
 * sampling at scale > 1, the bilinear taps, a 1/64-texel slack for float rounding, then
 * the wrap mode.  REGION_REPEAT keeps the wrap rect. */
static void hr_axis(int64_t S, int64_t step, int k0, int k1, int lin, int scale, int wm, int size,
                    int mn, int mx, int *lo, int *hi)
{
    double a = (double)((S + step * k0) >> 16) / 16.0, b = (double)((S + step * k1) >> 16) / 16.0;
    if (a > b) { double t = a; a = b; b = t; }
    /* point sampling keeps the reference's native texel (gs_draw.hlsl
     * g_anchor); bilinear moves with the sub-sample offset */
    double half = scale > 1 && lin ? fabs((double)step / 65536.0 / 16.0) * 0.5 : 0.0;
    a -= half + 1.0 / 64.0;
    b += half + 1.0 / 64.0;
    int l, h;
    if (lin) { l = (int)floor(a - 0.5); h = (int)floor(b - 0.5) + 2; }
    else { l = (int)floor(a); h = (int)floor(b) + 1; }
    switch (wm) {
    case 0: if (l < 0 || h > size) return; break;    /* wraps: keep the wrap rect */
    case 1:
        l = l < 0 ? 0 : (l > size - 1 ? size - 1 : l);
        h = h < 1 ? 1 : (h > size ? size : h);
        break;
    case 2:
        l = l < mn ? mn : (l > mx ? mx : l);
        h = h < mn + 1 ? mn + 1 : (h > mx + 1 ? mx + 1 : h);
        break;
    default: return;
    }
    if (h <= l) h = l + 1;
    *lo = l; *hi = h;
}

static void sprite_texel_rect(const gpu_renderer *r, const Derived &d, const GpuRect &box, int bx,
                              int by, int64_t Su, int64_t su, int64_t Sv, int64_t sv, GpuRect *tr)
{
    const Key &k = r->key;
    int tw = (int)BITS(k.tex0, 26, 4), th = (int)BITS(k.tex0, 30, 4);
    if (tw > 10) tw = 10;
    if (th > 10) th = 10;
    int mmag = (int)BITS(k.tex1, 5, 1), mmin = (int)BITS(k.tex1, 6, 3);
    int lin = mmag || mmin == 1 || mmin == 4 || mmin == 5;   /* either filter may apply */
    hr_axis(Su, su, box.x0 - bx, box.x1 - 1 - bx, lin, r->scale, (int)BITS(k.clamp, 0, 2), 1 << tw,
            (int)BITS(k.clamp, 4, 10), (int)BITS(k.clamp, 14, 10), &tr->x0, &tr->x1);
    hr_axis(Sv, sv, box.y0 - by, box.y1 - 1 - by, lin, r->scale, (int)BITS(k.clamp, 2, 2), 1 << th,
            (int)BITS(k.clamp, 24, 10), (int)BITS(k.clamp, 34, 10), &tr->y0, &tr->y1);
    (void)d;
}

/* The triangle (12.4 window coordinates) grown by one pixel on every side
 * (each edge moved one pixel outward, the vertices where the moved edges
 * meet), clipped to the rectangle [xlo, xhi] x [ylo, yhi]: a convex polygon
 * of up to 7 vertices, returned as a fan (docs/GPU.md "Performance").
 * Exact triangles decide coverage in the pixel shader, so the rasterizer
 * only has to cover a superset of the samples the reference covers: one
 * pixel is far beyond its snapping error, and the rectangle (the box of
 * covered pixels plus a pixel, inside the viewport) keeps the rasterizer
 * from clipping (WARP clips into fans whose inner edges do not tile).  The
 * fan's triangles share their vertices bit for bit, so the rasterization
 * rules cover each sample once.  Returns the vertex count, 0 when the
 * polygon is larger than `maxarea` (the box is then cheaper). */
static int grow_poly(const int X[3], const int Y[3], double xlo, double ylo, double xhi, double yhi,
                     double maxarea, float ox[8], float oy[8])
{
    double px[3], py[3];
    for (int i = 0; i < 3; i++) { px[i] = X[i] / 16.0; py[i] = Y[i] / 16.0; }
    double cx = (px[0] + px[1] + px[2]) / 3.0, cy = (py[0] + py[1] + py[2]) / 3.0;
    double nx[3], ny[3], nc[3];   /* edge i: from vertex i to i+1, outward unit normal */
    for (int i = 0; i < 3; i++) {
        int j = (i + 1) % 3;
        double ex = px[j] - px[i], ey = py[j] - py[i];
        double len = sqrt(ex * ex + ey * ey);
        if (!(len > 0.0)) return 0;
        double a = ey / len, b = -ex / len;
        if (a * (cx - px[i]) + b * (cy - py[i]) > 0.0) { a = -a; b = -b; }
        nx[i] = a; ny[i] = b;
        nc[i] = a * px[i] + b * py[i] + 1.0;   /* moved line: n . p = nc */
    }
    double gx[16], gy[16];
    int n = 3;
    for (int k = 0; k < 3; k++) {
        int i = (k + 2) % 3, j = k;           /* the moved edges meeting at vertex k */
        double det = nx[i] * ny[j] - ny[i] * nx[j];
        if (fabs(det) < 1e-12) return 0;
        gx[k] = (nc[i] * ny[j] - ny[i] * nc[j]) / det;
        gy[k] = (nx[i] * nc[j] - nc[i] * nx[j]) / det;
        if (!(fabs(gx[k]) < 1e7 && fabs(gy[k]) < 1e7)) return 0;
    }
    /* Sutherland-Hodgman against the four sides; a clipped coordinate is set
     * to the side's value exactly */
    for (int side = 0; side < 4; side++) {
        double tx[16], ty[16];
        int m = 0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            double vi = side == 0 ? gx[i] - xlo : side == 1 ? xhi - gx[i] : side == 2 ? gy[i] - ylo : yhi - gy[i];
            double vj = side == 0 ? gx[j] - xlo : side == 1 ? xhi - gx[j] : side == 2 ? gy[j] - ylo : yhi - gy[j];
            if (vi >= 0.0) { tx[m] = gx[i]; ty[m] = gy[i]; m++; }
            if ((vi >= 0.0) != (vj >= 0.0)) {
                double t = vi / (vi - vj);
                double x = gx[i] + (gx[j] - gx[i]) * t, y = gy[i] + (gy[j] - gy[i]) * t;
                if (side == 0) x = xlo;
                else if (side == 1) x = xhi;
                else if (side == 2) y = ylo;
                else y = yhi;
                tx[m] = x; ty[m] = y; m++;
            }
            if (m > 12) return 0;
        }
        n = m;
        for (int i = 0; i < n; i++) { gx[i] = tx[i]; gy[i] = ty[i]; }
        if (n < 3) return 0;
    }
    if (n > 8) return 0;
    double area = 0.0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += gx[i] * gy[j] - gx[j] * gy[i];
    }
    if (!(fabs(area) * 0.5 <= maxarea)) return 0;
    for (int k = 0; k < n; k++) { ox[k] = (float)gx[k]; oy[k] = (float)gy[k]; }
    return n;
}

/* GpuTri.pad[1] flags and pad[2] (float of 1/area) for the exact shader's
 * float fast path (docs/GPU.md "Checkpoint 4"; gs_draw.hlsl TF_*).
 * TF_SMALL: 32-bit edge functions are exact at every pixel the shader
 * evaluates (the box of covered pixels plus two pixels): every coordinate
 * difference stays below 2^15, so each product is below 2^30 (sub-samples
 * at scale > 1 add a small exact term in the shader).  Not with a denormal S/T/Q (float flushes them; the double path
 * handles them as before).  TF_C*: the attribute is equal at the three
 * vertices, so the reference's a + (b-a)*w1 + (c-a)*w2 is exactly a. */
enum { TF_SMALL = 1, TF_CRGBA = 2, TF_CZ = 4, TF_CFOG = 8, TF_CS = 16, TF_CT = 32, TF_CQ = 64,
       TF_CU = 128, TF_CV = 256 };

static bool denormal(float f)
{
    uint32_t b;
    memcpy(&b, &f, 4);
    return (b & 0x7F800000u) == 0 && (b & 0x7FFFFFu) != 0;
}

static void tri_flags(GpuTri *t, const GpuRect &box, int scale)
{
    int64_t lx = (int64_t)(box.x0 - 2) * 16, hx = (int64_t)(box.x1 + 2) * 16;
    int64_t ly = (int64_t)(box.y0 - 2) * 16, hy = (int64_t)(box.y1 + 2) * 16;
    for (int k = 0; k < 3; k++) {
        if (t->x[k] < lx) lx = t->x[k];
        if (t->x[k] > hx) hx = t->x[k];
        if (t->y[k] < ly) ly = t->y[k];
        if (t->y[k] > hy) hy = t->y[k];
    }
    int64_t ext = hx - lx > hy - ly ? hx - lx : hy - ly;
    uint32_t f = 0;
    (void)scale;   /* the shader splits e * scale into scale * n + d (gs_draw.hlsl) */
    if (ext <= 32767) f |= TF_SMALL;
    for (int k = 0; k < 3; k++)
        if (denormal(t->s[k]) || denormal(t->t[k]) || denormal(t->q[k])) f &= ~(uint32_t)TF_SMALL;
    if (t->rgba[0] == t->rgba[1] && t->rgba[1] == t->rgba[2]) f |= TF_CRGBA;
    if (t->z[0] == t->z[1] && t->z[1] == t->z[2]) f |= TF_CZ;
    if (t->fog[0] == t->fog[1] && t->fog[1] == t->fog[2]) f |= TF_CFOG;
    if (t->s[0] == t->s[1] && t->s[1] == t->s[2]) f |= TF_CS;
    if (t->t[0] == t->t[1] && t->t[1] == t->t[2]) f |= TF_CT;
    if (t->q[0] == t->q[1] && t->q[1] == t->q[2]) f |= TF_CQ;
    if ((t->uv[0] & 0xFFFF) == (t->uv[1] & 0xFFFF) && (t->uv[1] & 0xFFFF) == (t->uv[2] & 0xFFFF)) f |= TF_CU;
    if ((t->uv[0] >> 16) == (t->uv[1] >> 16) && (t->uv[1] >> 16) == (t->uv[2] >> 16)) f |= TF_CV;
    t->pad[1] = f;
    uint64_t ib = (uint64_t)t->inv_lo | ((uint64_t)t->inv_hi << 32);
    double inv;
    memcpy(&inv, &ib, 8);
    float invf = (float)inv;
    memcpy(&t->pad[2], &invf, 4);
}

/* A primitive the software rasterizer drew (gs->sw_raster set for one kick)
 * is complete once the core calls back in: back to GPU drawing. */
static void sw_restore(gpu_renderer *r)
{
    if (r->sw_once && r->gs) r->gs->sw_raster = 0;
    r->sw_once = 0;
}

static void lazy_before_draw(gpu_renderer *r, gs_state *gs, int skip_tex);
static void on_draw(void *user, gs_state *gs, const gs_vertex *v, int nv, int type)
{
    gpu_renderer *r = (gpu_renderer *)user;
    sw_restore(r);
    lazy_before_draw(r, gs, 0);
    r->stats.prims++;
    Key k;
    make_key(r, gs, &k);
    if (!r->have_key || memcmp(&k, &r->key, sizeof k) != 0) {
        flush_batch(r);
        r->key = k;
        r->have_key = 1;
        derive(r, gs, k, &r->dv);
        if (k.clut_gen) memcpy(r->batch_clut, r->clut_copy, sizeof r->batch_clut);
    }
    Derived &d = r->dv;
    if (d.skip) return;
    uint64_t prim = gs->reg[GS_PRIM];
    uint64_t attr = (gs->reg[GS_PRMODECONT] & 1) ? prim : gs->reg[GS_PRMODE];
    int iip = (int)BITS(attr, 3, 1);
    uint64_t xo = gs->reg[GS_XYOFFSET_1 + d.ctx];
    int ofx = (int)BITS(xo, 0, 16), ofy = (int)BITS(xo, 32, 16);

    GpuVertex out[18];   /* up to a 6-triangle fan (grow_poly) */
    int n = 0;
    GpuTri tri;
    int have_tri = 0;
    int X[3], Y[3];
    /* UV sprite DDA (16.16 of 1/16 texels), for the exact texel rect */
    int uv_dda = 0, dda_bx = 0, dda_by = 0;
    int64_t dda_Su = 0, dda_su = 0, dda_Sv = 0, dda_sv = 0;
    for (int i = 0; i < nv; i++) { X[i] = (int)v[i].x - ofx; Y[i] = (int)v[i].y - ofy; }
    GpuRect box;
    switch (type) {
    case GS_PRIM_POINT: {
        int px = ceil16(X[0]), py = ceil16(Y[0]);
        GpuVertex b;
        set_attr(&b, &v[0]);
        b.vflags = 1;
        float x0 = (float)px - 0.5f, y0 = (float)py - 0.5f, x1 = x0 + 1.0f, y1 = y0 + 1.0f;
        GpuVertex c[4] = { b, b, b, b };
        c[0].x = x0; c[0].y = y0; c[1].x = x1; c[1].y = y0;
        c[2].x = x0; c[2].y = y1; c[3].x = x1; c[3].y = y1;
        out[0] = c[0]; out[1] = c[1]; out[2] = c[2]; out[3] = c[1]; out[4] = c[3]; out[5] = c[2];
        n = 6;
        box.x0 = px; box.y0 = py; box.x1 = px + 1; box.y1 = py + 1;
        break;
    }
    case GS_PRIM_SPRITE: {
        GpuVertex c[4];
        for (int i = 0; i < 4; i++) set_attr(&c[i], &v[1]);   /* colour/Z/fog/Q: 2nd */
        float fx[2] = { X[0] / 16.0f, X[1] / 16.0f }, fy[2] = { Y[0] / 16.0f, Y[1] / 16.0f };
        if (r->scale > 1) {
            /* Block-aligned coverage: a native pixel p's sub-samples span
             * GS [p - 0.5, p + 0.5), so a sprite on whole pixels would cover
             * half of its first and half of the next pixel.  Edges on
             * ceil(x) - 0.5 cover exactly the s x s blocks of the pixels the
             * reference draws (ceil(x0) <= p < ceil(x1)); every attribute
             * of a sprite is evaluated per pixel, not interpolated.  Scale 1
             * keeps the GS edges (same coverage). */
            for (int i = 0; i < 2; i++) {
                fx[i] = (float)ceil16(X[i]) - 0.5f;
                fy[i] = (float)ceil16(Y[i]) - 0.5f;
            }
        }
        for (int i = 0; i < 4; i++) {
            int sx = i & 1, sy = i >> 1;
            c[i].x = fx[sx]; c[i].y = fy[sy];
            c[i].s = v[sx].s; c[i].u = (float)v[sx].u / 16.0f;
            c[i].t = v[sy].t; c[i].v = (float)v[sy].v / 16.0f;
            c[i].vflags = 1;
        }
        {
            /* the reference's sprite formula, corners sorted as it does */
            int sx = X[1] < X[0];
            int sy = Y[1] < Y[0];
            const gs_vertex &a = v[sx], &b = v[1 - sx], &e = v[sy], &f = v[1 - sy];
            if (d.fst) {
                /* UV: the reference's fixed-point DDA (gs_sprite_uv_*), split
                 * so the shader evaluates it exactly in 32-bit integers:
                 * U(px) = Shi + Thi*k + ((Slo + Tlo*k) >> 16), k = px - base,
                 * where S = U_fp(base) and T = step (16.16).  Every value is
                 * below 2^24 and travels exactly as a float. */
                int64_t su = gs_sprite_uv_step(a.u, b.u, X[sx], X[1 - sx]);
                int64_t sv = gs_sprite_uv_step(e.v, f.v, Y[sy], Y[1 - sy]);
                int bx = ceil16(X[sx]), by = ceil16(Y[sy]);
                int64_t Su = (int64_t)a.u * 65536 +
                             ((su * ((int64_t)bx * 16 - X[sx])) >> 4);
                int64_t Sv = (int64_t)e.v * 65536 +
                             ((sv * ((int64_t)by * 16 - Y[sy])) >> 4);
                uv_dda = 1; dda_bx = bx; dda_by = by;
                dda_Su = Su; dda_su = su; dda_Sv = Sv; dda_sv = sv;
                for (int i = 0; i < 4; i++) {
                    GpuVertex &o = c[i];
                    o.vflags |= 32;
                    o.spr_x0 = (float)bx; o.spr_y0 = (float)by;
                    o.spr_dx = o.spr_dy = 0;
                    o.spr_s0 = (float)(Su >> 16); o.spr_s1 = (float)(Su & 0xFFFF);
                    o.spr_u0 = (float)(su >> 16); o.spr_u1 = (float)(su & 0xFFFF);
                    o.spr_t0 = (float)(Sv >> 16); o.spr_t1 = (float)(Sv & 0xFFFF);
                    o.spr_v0 = (float)(sv >> 16); o.spr_v1 = (float)(sv & 0xFFFF);
                }
            } else {
                for (int i = 0; i < 4; i++) {
                    GpuVertex &o = c[i];
                    o.vflags |= 2;
                    o.spr_x0 = (float)X[sx]; o.spr_dx = (float)(X[1 - sx] - X[sx]);
                    o.spr_y0 = (float)Y[sy]; o.spr_dy = (float)(Y[1 - sy] - Y[sy]);
                    o.spr_s0 = a.s; o.spr_s1 = b.s; o.spr_u0 = (float)a.u; o.spr_u1 = (float)b.u;
                    o.spr_t0 = e.t; o.spr_t1 = f.t; o.spr_v0 = (float)e.v; o.spr_v1 = (float)f.v;
                }
            }
        }
        out[0] = c[0]; out[1] = c[1]; out[2] = c[2]; out[3] = c[1]; out[4] = c[3]; out[5] = c[2];
        n = 6;
        int lx = X[0] < X[1] ? X[0] : X[1], hx = X[0] < X[1] ? X[1] : X[0];
        int ly = Y[0] < Y[1] ? Y[0] : Y[1], hy = Y[0] < Y[1] ? Y[1] : Y[0];
        box.x0 = ceil16(lx); box.x1 = ceil16(hx); box.y0 = ceil16(ly); box.y1 = ceil16(hy);
        break;
    }
    case GS_PRIM_LINE: case GS_PRIM_LINESTRIP: {
        int dx = X[1] - X[0], dy = Y[1] - Y[0];
        if (dx == 0 && dy == 0) return;
        int xmajor = (dx < 0 ? -dx : dx) >= (dy < 0 ? -dy : dy);
        /* The reference's DDA picks, per major-axis pixel p, the minor
         * pixel q = floor((b(p) + 8) / 16) (12.4).  D3D's fill rule cannot
         * express that half-open-the-other-way interval, so the band is
         * rasterized 2 px wide and the pixel shader keeps exactly the q of
         * the reference, computed with exact integer math (vflags bit 2).
         * The major-axis extent [ceil(lo), ceil(hi)) is the band's
         * vertical/horizontal edges, which D3D's rule gets right. */
        GpuVertex a0, a1;
        set_attr(&a0, &v[0]);
        set_attr(&a1, &v[1]);
        if (!iip) { set_flat(&a0, &v[1]); set_flat(&a1, &v[1]); }
        uint32_t lf = 4u | (xmajor ? 8u : 0u) | (v[0].z == v[1].z ? 1u : 0u);
        a0.vflags = a1.vflags = lf;
        a0.spr_x0 = a1.spr_x0 = (float)(xmajor ? X[0] : Y[0]);           /* a0 */
        a0.spr_y0 = a1.spr_y0 = (float)(xmajor ? Y[0] : X[0]);           /* b0 */
        a0.spr_dx = a1.spr_dx = (float)(xmajor ? dx : dy);               /* da */
        a0.spr_dy = a1.spr_dy = (float)(xmajor ? dy : dx);               /* db */
        if (r->exact) {
            /* exact line attributes (docs/GPU.md "Exact triangles"): the
             * reference's t = (16p - a0) / da and a + (b-a)*t in double;
             * flat lines take v[1]'s colour and fog */
            memset(&tri, 0, sizeof tri);
            for (int k = 0; k < 2; k++) {
                const gs_vertex &sv = v[k];
                const gs_vertex &cv = iip ? sv : v[1];
                tri.x[k] = X[k];
                tri.y[k] = Y[k];
                tri.s[k] = sv.s; tri.t[k] = sv.t; tri.q[k] = sv.q;
                tri.z[k] = sv.z;
                tri.rgba[k] = (uint32_t)cv.r | ((uint32_t)cv.g << 8) | ((uint32_t)cv.b << 16) |
                              ((uint32_t)cv.a << 24);
                tri.uv[k] = (uint32_t)sv.u | ((uint32_t)sv.v << 16);
                tri.fog[k] = cv.f;
            }
            a0.vflags = a1.vflags = lf | 64u;
            have_tri = 1;
        }
        GpuVertex c[4] = { a0, a1, a0, a1 };
        float x0 = X[0] / 16.0f, y0 = Y[0] / 16.0f, x1 = X[1] / 16.0f, y1 = Y[1] / 16.0f;
        if (xmajor) {
            c[0].x = x0; c[0].y = y0 - 1.0f; c[1].x = x1; c[1].y = y1 - 1.0f;
            c[2].x = x0; c[2].y = y0 + 1.0f; c[3].x = x1; c[3].y = y1 + 1.0f;
        } else {
            c[0].x = x0 - 1.0f; c[0].y = y0; c[1].x = x1 - 1.0f; c[1].y = y1;
            c[2].x = x0 + 1.0f; c[2].y = y0; c[3].x = x1 + 1.0f; c[3].y = y1;
        }
        out[0] = c[0]; out[1] = c[1]; out[2] = c[2]; out[3] = c[1]; out[4] = c[3]; out[5] = c[2];
        n = 6;
        int lx = X[0] < X[1] ? X[0] : X[1], hx = X[0] < X[1] ? X[1] : X[0];
        int ly = Y[0] < Y[1] ? Y[0] : Y[1], hy = Y[0] < Y[1] ? Y[1] : Y[0];
        box.x0 = (lx >> 4) - 1; box.x1 = (hx >> 4) + 2; box.y0 = (ly >> 4) - 1; box.y1 = (hy >> 4) + 2;
        break;
    }
    case GS_PRIM_TRIANGLE: case GS_PRIM_TRISTRIP: case GS_PRIM_TRIFAN: {
        int64_t area = (int64_t)(X[1] - X[0]) * (Y[2] - Y[0]) - (int64_t)(Y[1] - Y[0]) * (X[2] - X[0]);
        if (area == 0) return;
        int zc = v[0].z == v[1].z && v[1].z == v[2].z;
        for (int i = 0; i < 3; i++) {
            set_attr(&out[i], &v[i]);
            if (!iip) set_flat(&out[i], &v[2]);
            out[i].x = X[i] / 16.0f;
            out[i].y = Y[i] / 16.0f;
            out[i].vflags = (uint32_t)zc;
        }
        if (r->exact) {
            /* Exact triangles (docs/GPU.md "Exact triangles"): the pixel
             * shader evaluates the reference's draw_triangle per pixel in
             * double precision (edge functions, w = e * inv, a + (b-a)*w1 +
             * (c-a)*w2, truncation), from this record.  Same vertex order
             * as the reference: v1 and v2 swap when the area is negative;
             * flat shading takes the kicking vertex (v[2]) before the swap. */
            int o[3] = { 0, 1, 2 };
            if (area < 0) { o[1] = 2; o[2] = 1; }
            int64_t aa = area < 0 ? -area : area;
            double inv = 1.0 / (double)aa;
            uint64_t ib;
            memcpy(&ib, &inv, 8);
            memset(&tri, 0, sizeof tri);
            tri.inv_lo = (uint32_t)ib;
            tri.inv_hi = (uint32_t)(ib >> 32);
            for (int k = 0; k < 3; k++) {
                const gs_vertex &sv = v[o[k]];
                const gs_vertex &cv = iip ? sv : v[2];
                tri.x[k] = X[o[k]];
                tri.y[k] = Y[o[k]];
                tri.s[k] = sv.s; tri.t[k] = sv.t; tri.q[k] = sv.q;
                tri.z[k] = sv.z;
                tri.rgba[k] = (uint32_t)cv.r | ((uint32_t)cv.g << 8) | ((uint32_t)cv.b << 16) |
                              ((uint32_t)cv.a << 24);
                tri.uv[k] = (uint32_t)sv.u | ((uint32_t)sv.v << 16);
                tri.fog[k] = cv.f;
            }
            for (int i = 0; i < 3; i++) out[i].vflags = 64;
            have_tri = 1;
        } else if (!zc) {
            /* Z from the plane equation per pixel (vflags bit 4): exact
             * 12.4 deltas times gradients computed here in double; rasterizer
             * attribute interpolation (WARP especially) is less precise */
            double ax = X[1] - X[0], ay = Y[1] - Y[0], bx = X[2] - X[0], by = Y[2] - Y[0];
            double det = ax * by - ay * bx;
            double dz1 = (double)v[1].z - (double)v[0].z, dz2 = (double)v[2].z - (double)v[0].z;
            double gx = (dz1 * by - dz2 * ay) / det, gy = (dz2 * ax - dz1 * bx) / det;
            for (int i = 0; i < 3; i++) {
                out[i].vflags |= 16;
                out[i].spr_x0 = (float)X[0];
                out[i].spr_y0 = (float)Y[0];
                out[i].spr_dx = (float)gx;
                out[i].spr_dy = (float)gy;
                out[i].spr_s0 = (float)v[0].z;
            }
        }
        n = 3;
        int lx = X[0], hx = X[0], ly = Y[0], hy = Y[0];
        for (int i = 1; i < 3; i++) {
            if (X[i] < lx) lx = X[i];
            if (X[i] > hx) hx = X[i];
            if (Y[i] < ly) ly = Y[i];
            if (Y[i] > hy) hy = Y[i];
        }
        box.x0 = ceil16(lx); box.x1 = (hx >> 4) + 1; box.y0 = ceil16(ly); box.y1 = (hy >> 4) + 1;
        if (have_tri && r->scale > 1) {
            /* a native pixel's sub-samples span GS (p - 0.5, p + 0.5): one
             * outside the native box can be covered (x1 = 9.4 covers pixel
             * 9's sub-sample 9.4375 at x8) */
            box.x0--; box.y0--; box.x1++; box.y1++;
        }
        break;
    }
    default:
        return;
    }
    /* sprites/points: everything from one vertex; points use their own */
    if (type == GS_PRIM_POINT) for (int i = 0; i < n; i++) out[i].vflags = 1;
    /* natively generated primitive whose ALPHA is the batch's with A and B
     * swapped (gpu_nr_prims_alpha_swap): the shader swaps them per vertex */
    if (r->nr_swap) for (int i = 0; i < n; i++) out[i].vflags |= 128u;
    /* clip the box to the scissor */
    if (box.x0 < d.scx0) box.x0 = d.scx0;
    if (box.y0 < d.scy0) box.y0 = d.scy0;
    if (box.x1 > d.scx1) box.x1 = d.scx1;
    if (box.y1 > d.scy1) box.y1 = d.scy1;
    if (box.x1 <= box.x0 || box.y1 <= box.y0) return;
    if (have_tri && type != GS_PRIM_LINE && type != GS_PRIM_LINESTRIP && r->cfg.fault != 5) {
        /* Exact triangles are drawn as their bounding box (clipped to the
         * scissor) and the pixel shader decides coverage with the
         * reference's integer edge functions and top-left rule.  Leaving
         * coverage to the rasterizer was exact on the RTX 3080 but not on
         * WARP: a triangle reaching outside the viewport is clipped into a
         * fan whose float vertices leave pixels on the new inner edges
         * drawn twice or not at all (the NORMAL overlay's rotated quads,
         * docs/GPU.md "Real game validation"; control_cover). */
        /* Since the "Performance" work the triangle itself, grown by a
         * pixel, when that stays inside the viewport (x in [0, FBW*64),
         * y in [0, 1024): every target is at least 1024 rows) and is
         * smaller than the box: half the pixels of a box for most
         * triangles, and the exact shader's doubles run only there. */
        GpuVertex b = out[0];
        float gx[8], gy[8];
        double fwpx = (double)((d.fbw ? d.fbw : 1) * 64);
        double barea = (double)(box.x1 - box.x0) * (double)(box.y1 - box.y0);
        /* the box of covered pixels plus a pixel, inside the viewport (x in
         * [0, FBW*64), y in [0, 1024): every target is at least 1024 rows) */
        double rx0 = box.x0 - 1.5, ry0 = box.y0 - 1.5, rx1 = box.x1 + 0.5, ry1 = box.y1 + 0.5;
        if (rx0 < -0.5) rx0 = -0.5;
        if (ry0 < -0.5) ry0 = -0.5;
        if (rx1 > fwpx - 0.5) rx1 = fwpx - 0.5;
        if (ry1 > 1023.5) ry1 = 1023.5;
        int np = r->tri_box ? 0 : grow_poly(X, Y, rx0, ry0, rx1, ry1, barea, gx, gy);
        if (np >= 3) {
            n = 0;
            for (int i = 1; i + 1 < np; i++) {
                int idx[3] = { 0, i, i + 1 };
                for (int k = 0; k < 3; k++) { out[n] = b; out[n].x = gx[idx[k]]; out[n].y = gy[idx[k]]; n++; }
            }
            r->stats.grown_tris++;
        } else {
            float x0 = (float)box.x0 - 0.5f, y0 = (float)box.y0 - 0.5f;
            float x1 = (float)box.x1 - 0.5f, y1 = (float)box.y1 - 0.5f;
            GpuVertex c[4] = { b, b, b, b };
            c[0].x = x0; c[0].y = y0; c[1].x = x1; c[1].y = y0;
            c[2].x = x0; c[2].y = y1; c[3].x = x1; c[3].y = y1;
            out[0] = c[0]; out[1] = c[1]; out[2] = c[2]; out[3] = c[1]; out[4] = c[3]; out[5] = c[2];
            n = 6;
        }
    }
    if (d.alias) {
        /* FRAME and ZBUF on the same pages: the reference interleaves the
         * colour and Z writes of every pixel in one memory.  Make gs->vram
         * current for everything the primitive touches, let the software
         * rasterizer draw it (gs_draw_kick runs it right after this hook),
         * and treat the result as a CPU write (exact, slow, rare). */
        flush_batch(r);
        uint32_t fw = d.fbw ? d.fbw : 1;
        Pages w = pages_of(d.fbp, fw, d.fpsm, box.x0, box.y0, box.x1, box.y1);
        w.add(pages_of(d.zbp, fw, d.zpsm, box.x0, box.y0, box.x1, box.y1));
        Pages rd = w;
        if (d.tme) rd.add(d.tex_pages);
        sync_for_cpu_read(r, rd);
        for (Rt &t : r->rts)
            if (t.pages.overlaps(w)) { t.stale = 1; t.stale_pages.add(w); }
        r->cpu_newer.add(w);
        r->drawn.add(w);            /* (a draw, not an upload) */
        hot_cpu_write(r, w);
        gs_mem_gen_bump(gs, w.w);   /* the software rasterizer writes local memory */
        if (d.tme) clut_resolve(r);   /* it reads gs->clut */
        gs->sw_raster = 1;
        r->sw_once = 1;
        r->stats.cpu_prims++;
        return;
    }
    Pages rp, wp;
    GpuRect tr = { 0, 0, 0, 0 };
    rp.clear();
    wp.clear();
    if (d.tme) {
        /* Render-target feedback: the GS draws primitives in order, so a
         * primitive sampling memory an earlier primitive of the batch drew
         * must see that result.  The batch samples the mirror (written back
         * at flush), so such a primitive starts a new batch. */
        rp = prim_read_pages(r->key, d, v, nv, type, &tr);
        if (uv_dda && d.tex_lvl0) {
            sprite_texel_rect(r, d, box, dda_bx, dda_by, dda_Su, dda_su, dda_Sv, dda_sv, &tr);
            /* the exact texels (plus taps and slack) instead of
             * axis_range's two-texel margins: a copy of a whole buffer no
             * longer reaches into the page row below it (feedback splits
             * against a buffer drawn there) */
            rp = pages_of(BITS(r->key.tex0, 0, 14), d.tbw ? d.tbw : 1, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
        }
        if (d.feedback) {
            int fw = (int)(d.fbw ? d.fbw : 1);
            if (d.fb_feedback) wp = pages_of(d.fbp, (uint32_t)fw, d.fpsm, box.x0, box.y0, box.x1, box.y1);
            if (d.zb_feedback)
                wp.add(pages_of(d.zbp, (uint32_t)fw, d.zpsm, box.x0, box.y0, box.x1, box.y1));
            if (r->cfg.fault != 2 && rp.overlaps(r->batch_written)) {
                flush_batch(r);
                r->stats.feedback_splits++;
            }
        }
    }
    if (d.serial) {
        for (const GpuRect &b : r->boxes)
            if (rect_overlap(b, box)) { flush_batch(r); break; }
        if (r->boxes.size() >= 512) flush_batch(r);
        r->boxes.push_back(box);
    }
    if (r->verts.size() + (size_t)n > 65536) flush_batch(r);
    if (r->verts.empty()) { r->bbox = box; r->batch_texrect = tr; }
    else { rect_union(r->bbox, box); rect_union(r->batch_texrect, tr); }
    if (have_tri) {
        for (int i = 0; i < n; i++) out[i].spr_u0 = (float)r->tris.size();
        if (type != GS_PRIM_LINE && type != GS_PRIM_LINESTRIP) {
            tri_flags(&tri, box, r->scale);
            if (!(tri.pad[1] & TF_SMALL)) {
                r->stats.big_tris++;
                r->stats.big_px += (uint64_t)(box.x1 - box.x0) * (uint64_t)(box.y1 - box.y0);
            }
        }
        r->tris.push_back(tri);
        r->stats.exact_tris++;
    }
    r->verts.insert(r->verts.end(), out, out + n);
    r->batch_read.add(rp);
    r->batch_written.add(wp);
}

/* the rectangle of a host->local transfer that may be merged (BEGIN of an
 * IMAGE transfer through the core's own rectangle), else NULL */
static const gs_mem_rect *mem_xfer(gpu_renderer *r, const gs_state *gs, const gs_mem_rect *rc)
{
    if (r->no_defer || !r->be->can_merge() || rc != &gs->hooks.xfer_rect || !gs->hooks.xfer_open ||
        gs->xfer_dir != 0 || rc->w == 0 || rc->x + rc->w > 2048 || rc->y + rc->h > 2048 ||
        gs_psm_bpp(rc->psm) == 0)
        return NULL;
    return rc;
}

/* GS_MEM_WRITE_END.  A transfer into split pages adds its bits to their
 * mask; split pages it wrote whole (complete transfer) are CPU-newer. */
static void end_write(gpu_renderer *r, const gs_state *gs, const gs_mem_rect *rc, Pages p)
{
    {
        /* blocks the write filled completely now hold their newest bytes in gs->vram
         * (formats that write every bit of their words only) */
        int psm = rc->psm;
        uint64_t n = rc == &gs->hooks.xfer_rect ? xfer_done(gs, *rc) : (uint64_t)rc->w * rc->h;
        if (n == (uint64_t)rc->w * rc->h && psm != GS_PSMCT24 && psm != GS_PSMZ24 && psm != GS_PSMT8H &&
            psm != GS_PSMT4HL && psm != GS_PSMT4HH) {
            GpuRect d = { (int)rc->x, (int)rc->y, (int)(rc->x + rc->w), (int)(rc->y + rc->h) };
            blk_mark(r, rc->bp, rc->bw, psm, d, 0, 1);
            if ((psm == GS_PSMCT32 || psm == GS_PSMZ32) && (uint64_t)rc->w * rc->h <= 4096) {
                /* the words of the blocks the rectangle covers only in part (a 16-entry
                 * palette in a corner of a drawn page: 8x2 of an 8x8 block) */
                for (uint32_t y = 0; y < rc->h; y++)
                    for (uint32_t x = 0; x < rc->w; x++) {
                        uint32_t a = gs_pixel_addr(psm, rc->bp, rc->bw ? rc->bw : 1, rc->x + x, rc->y + y, NULL);
                        r->blk_stale[(a >> 8) & 16383u] &= ~(1ull << ((a >> 2) & 63u));
                    }
            }
        }
    }
    if (r->xfer_split && rc == &gs->hooks.xfer_rect) {
        r->xfer_split = 0;
        uint64_t n = xfer_done(gs, *rc);
        /* split pages the complete transfer wrote whole are plain CPU-newer
         * pages (their mask is cleared: not split any more) */
        if (n == (uint64_t)rc->w * rc->h) {
            Pages wh = whole_pages(*rc).and_(r->split);
            for (uint32_t pg = 0; pg < 512; pg++)
                if (wh.get(pg)) memset(split_mask(r) + (size_t)pg * 8192u, 0, 8192u);
            r->split.sub(wh);
        }
        split_add(r, *rc, n);
        for (Rt &t : r->rts)
            if (t.pages.overlaps(p)) { t.stale = 1; t.stale_pages.add(p); }
        p.sub(r->split);
    }
    cpu_write_end(r, p);
}

/* The block rule (blk_stale): every block rc touches holds its newest bytes in gs->vram
 * when no target write-back wrote it since the last download (or a complete CPU write
 * filled it since) and no live target holds newer data for it (its dirty rectangle
 * misses the block).  The pending batch must have been flushed if it can write p. */
static bool blk_current(gpu_renderer *r, const gs_mem_rect *rc)
{
    int bwk, bhk;
    if (r->no_blk || r->xfer_split || rc->w == 0 || !blk_dims(rc->psm, &bwk, &bhk)) return false;
    int bx0 = (int)rc->x / bwk, by0 = (int)rc->y / bhk;
    int bx1 = (int)(rc->x + rc->w + bwk - 1) / bwk, by1 = (int)(rc->y + rc->h + bhk - 1) / bhk;
    if ((bx1 - bx0) * (by1 - by0) > 256) return false;
    int per_px = (uint64_t)rc->w * rc->h <= 4096;
    if (per_px)
        for (uint32_t y = 0; y < rc->h; y++)
            for (uint32_t x = 0; x < rc->w; x++) {
                uint32_t a = gs_pixel_addr(rc->psm, rc->bp, rc->bw ? rc->bw : 1, rc->x + x, rc->y + y, NULL);
                if ((r->blk_stale[(a >> 8) & 16383u] >> ((a >> 2) & 63u)) & 1u) return false;
            }
    for (int by = by0; by < by1; by++)
        for (int bx = bx0; bx < bx1; bx++) {
            uint32_t b = (gs_pixel_addr(rc->psm, rc->bp, rc->bw ? rc->bw : 1, (uint32_t)(bx * bwk),
                                        (uint32_t)(by * bhk), NULL) >> 8) & 16383u;
            if (!per_px && r->blk_stale[b]) return false;
            for (const Rt &t : r->rts) {
                if (!t.has_dirty || !t.pages.get(b >> 5)) continue;
                GpuRect br;
                if (!blk_rect(b, t.bp, t.bw, t.psm, &br) || rect_overlap(br, t.dirty)) return false;
            }
        }
    return true;
}
static bool blk_read_current(gpu_renderer *r, const gs_mem_rect *rc, const Pages &p)
{
    if (!blk_current(r, rc)) return false;
    r->blk_reads++;
    if (r->blk_check) {
        /* $RG_GPU_BLK=check: the pixels as gs->vram holds them vs after a full read-back */
        std::vector<uint32_t> a((size_t)rc->w * rc->h);
        for (uint32_t y = 0; y < rc->h; y++)
            for (uint32_t x = 0; x < rc->w; x++)
                a[(size_t)y * rc->w + x] = gs_read_pixel(r->gs, rc->psm, rc->bp, rc->bw, rc->x + x, rc->y + y);
        sync_for_cpu_read(r, p);
        int bad = 0;
        for (uint32_t y = 0; y < rc->h; y++)
            for (uint32_t x = 0; x < rc->w; x++)
                if (a[(size_t)y * rc->w + x] != gs_read_pixel(r->gs, rc->psm, rc->bp, rc->bw, rc->x + x, rc->y + y)) bad++;
        if (bad) {
            static int printed;
            r->blk_check_bad++;
            if (printed++ < 20)
                fprintf(stderr, "gpu blk check: read psm %02x bp %u bw %u rect %u,%u %ux%u: %d pixels differ\n",
                        (unsigned)rc->psm, (unsigned)rc->bp, (unsigned)rc->bw, (unsigned)rc->x, (unsigned)rc->y,
                        (unsigned)rc->w, (unsigned)rc->h, bad);
        }
    }
    return true;
}

/* A CPU read of rc needs no read-back when every bit it reads is newest in
 * gs->vram already: no live target is dirty on its pages, none of them is
 * newer on the GPU, and on split pages the bits host->local transfers wrote
 * since (merge_mask) cover every bit the read uses (the bits a transfer into
 * the same rectangle would write, gs_xfer_mask).  The game uploads a
 * 16x16 palette into a corner of a render target's last page and loads it
 * as the CLUT right after: the read needs only the uploaded bits
 * (docs/GPU.md "Checkpoint 4"). */
static bool read_current(gpu_renderer *r, const gs_mem_rect *rc, const Pages &p)
{
    if (r->xfer_split || rc->w == 0 || rc->x + rc->w > 2048 || rc->y + rc->h > 2048 ||
        (uint64_t)rc->w * rc->h > 65536 || gs_psm_bpp(rc->psm) == 0 || r->cfg.fault == 13)
        return false;
    bool page_ok = !r->gpu_newer.overlaps(p);
    for (const Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(p)) page_ok = false;
    if (!page_ok) return blk_read_current(r, rc, p);
    Pages sp = r->split.and_(p);
    if (!sp.any()) return true;
    if (!r->read_mask) r->read_mask = (uint8_t *)calloc(1, GS_VRAM_BYTES);
    uint8_t *need = r->read_mask, *have = split_mask(r);
    for (uint32_t pg = 0; pg < 512; pg++)
        if (p.get(pg)) memset(need + (size_t)pg * 8192u, 0, 8192u);
    gs_xfer_mask(rc->psm, rc->bp, rc->bw, rc->x, rc->y, rc->w, rc->h, rc->w * rc->h, need);
    if (r->cfg.fault == 14) return true;   /* control: split pages taken as current */
    for (uint32_t pg = 0; pg < 512; pg++) {
        if (!sp.get(pg)) continue;
        const uint32_t *n = (const uint32_t *)(need + (size_t)pg * 8192u);
        const uint32_t *h = (const uint32_t *)(have + (size_t)pg * 8192u);
        for (uint32_t i = 0; i < 2048u; i++)
            if (n[i] & ~h[i]) return blk_read_current(r, rc, p);
    }
    return true;
}

/* A CPU read of rc: from an early copy of its pages when one is valid (the
 * pages unchanged since: as a read-back of them, without waiting for work
 * queued after the copy), else read back as before and remembered as a
 * hot region (at most 4 pages, the 4 most recent). */
static void cpu_read(gpu_renderer *r, const gs_mem_rect *rc, const Pages &p)
{
    HotRead *h = NULL;
    if (!r->no_early && !r->xfer_split)
        for (HotRead &x : r->hot)
            if (x.used && x.rc.bp == rc->bp && x.rc.bw == rc->bw && x.rc.psm == rc->psm && x.rc.x == rc->x &&
                x.rc.y == rc->y && x.rc.w == rc->w && x.rc.h == rc->h) { h = &x; break; }
    if (h && h->state == 2) hot_snapshot(r, *h);   /* written by the last batch */
    if (h && h->state == 1 && !r->split.overlaps(p)) {
        double t0 = now_us();
        const uint8_t *m = r->be->snap_map(h->slot);
        if (m) {
            uint32_t at = 0;
            for (uint32_t pg = 0; pg < 512; pg++)
                if (h->pages.get(pg)) {
                    memcpy(r->gs->vram + pg * 8192u, m + at, 8192u);
                    at += 8192u;
                }
            r->be->snap_unmap(h->slot);
            r->gpu_newer.sub(h->pages);
            blk_mark_pages(r, h->pages, 0);
            r->stats.download_us += (uint64_t)(now_us() - t0);
            r->stats.early_reads++;
            h->last = ++r->hot_tick;
            return;
        }
    }
    sync_for_cpu_read(r, p);
    if (r->no_early || h) {
        if (h) h->last = ++r->hot_tick;
        return;
    }
    int np = 0;
    for (int i = 0; i < 16; i++) for (uint32_t m = p.w[i]; m; m &= m - 1) np++;
    if (np > 4) return;
    HotRead *v = &r->hot[0];
    for (HotRead &x : r->hot) if (!x.used || x.last < v->last) { v = &x; if (!x.used) break; }
    v->used = 1;
    v->rc = *rc;
    v->pages = p;
    v->state = 0;
    v->slot = -1;
    v->last = ++r->hot_tick;
}

static void on_mem(void *user, gs_state *gs, int op, const gs_mem_rect *rc)
{
    gpu_renderer *r = (gpu_renderer *)user;
    (void)gs;
    sw_restore(r);
    Pages p = pages_of_rect(rc);
    if (r->trace)
        fprintf(r->trace, "M op %d trxdir %u psm %02x bp %u bw %u rect %u,%u %ux%u\n", op, (unsigned)(gs->reg[0x53] & 3),
                (unsigned)rc->psm, (unsigned)rc->bp, (unsigned)rc->bw, (unsigned)rc->x, (unsigned)rc->y,
                (unsigned)rc->w, (unsigned)rc->h);
    if (r->sync_log) {
        /* measurement ($RG_GPU_SYNC_LOG): which GS memory traffic makes the
         * CPU wait for the GPU */
        uint64_t d0 = r->stats.downloads;
        static uint64_t seq;
        seq++;
        if (op == GS_MEM_READ) {
            if (pending_writes(r).overlaps(p)) flush_batch(r);
            if (read_current(r, rc, p)) r->stats.reads_current++;
            else cpu_read(r, rc, p);
        } else if (op == GS_MEM_WRITE_BEGIN) {
            cpu_write_begin(r, p, mem_xfer(r, gs, rc));
            if (gs->xfer_dir == 0) r->drawn.sub(p);   /* host->local: uploaded data */
        } else {
            end_write(r, gs, rc, p);
        }
        if (r->stats.downloads != d0)
            fprintf(r->sync_log, "%llu op %d trxdir %u psm %02x bp %u bw %u rect %u,%u %ux%u\n",
                    (unsigned long long)seq, op, (unsigned)(gs->reg[0x53] & 3), (unsigned)rc->psm,
                    (unsigned)rc->bp, (unsigned)rc->bw, (unsigned)rc->x, (unsigned)rc->y,
                    (unsigned)rc->w, (unsigned)rc->h);
        return;
    }
    switch (op) {
    case GS_MEM_READ:
        /* the pending batch only has to be drawn first when it can write
         * what is read (a CLUT load from an untouched palette does not end
         * the batch) */
        if (pending_writes(r).overlaps(p)) flush_batch(r);
        if (read_current(r, rc, p)) {
            r->stats.reads_current++;
            break;
        }
        cpu_read(r, rc, p);
        break;
    case GS_MEM_WRITE_BEGIN:
        if (r->rt_log || r->filt_log)
            for (const Rt &t : r->rts)
                if (t.pages.overlaps(p)) {
                    /* (measurement: a CPU write into pages a live target owns) */
                    fprintf(r->filt_log ? r->filt_log : r->rt_log,
                            "W psm %02x bp %u bw %u rect %u,%u %ux%u dir %d into bp %u bw %u psm %02x h %d dirty %d\n",
                            (unsigned)rc->psm, (unsigned)rc->bp, (unsigned)rc->bw, (unsigned)rc->x, (unsigned)rc->y,
                            (unsigned)rc->w, (unsigned)rc->h, gs->xfer_dir, t.bp, t.bw, t.psm, t.h, t.has_dirty);
                    break;
                }
        cpu_write_begin(r, p, mem_xfer(r, gs, rc));
        if (gs->xfer_dir == 0) r->drawn.sub(p);   /* host->local: uploaded data (item 8) */
        break;
    default:
        end_write(r, gs, rc, p);
        break;
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
static int on_clut_load(void *user, gs_state *gs, const gs_mem_rect *rc, int csm, uint32_t csa, int cpsm, uint32_t n)
{
    gpu_renderer *r = (gpu_renderer *)user;
    sw_restore(r);
    Pages p = pages_of_rect(rc);
    if (!r->no_blk) {
        /* a palette whose blocks gs->vram holds current (the CPU uploaded it into a corner of
         * a drawn page): the model loads it from there, no GPU work, no read-back */
        if (pending_writes(r).overlaps(p)) flush_batch(r);
        if (blk_current(r, rc)) {
            if (r->clut_own_any) {
                clut_words(csm, csa, cpsm, n, r->clut_own, 0);
                r->clut_own_any = 0;
                for (int i = 0; i < 256; i++) r->clut_own_any |= r->clut_own[i];
                r->clut_force = 1;
            }
            return 0;
        }
    }
    /* only a palette the GPU drew: the source in a dirty target (or under the pending batch),
     * none of its pages holding bits the CPU wrote since (split pages, CPU-newer pages, pending
     * transfers: those loads stay with the model, which reads them exactly, mostly without a
     * read-back: read_current) */
    int need = pending_writes(r).overlaps(p);
    for (const Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(p)) need = 1;
    if (r->clut_wide && r->gpu_newer.overlaps(p)) need = 1;   /* investigation: the first, wider condition */
    if (need && !r->clut_wide && (r->split.overlaps(p) || r->cpu_newer.overlaps(p))) need = 0;
    if (need && !r->clut_wide) {
        Pages lz;
        lz.clear();
        if (gs_mem_lazy_pages(gs, lz.w) && lz.overlaps(p)) need = 0;
    }
    if (!need || r->no_gpu_clut || r->xfer_split || rc->w == 0 || rc->x + rc->w > 2048 || rc->y + rc->h > 2048) {
        /* the model loads it: the words it writes are the CPU's again */
        if (r->clut_own_any) {
            clut_words(csm, csa, cpsm, n, r->clut_own, 0);
            r->clut_own_any = 0;
            for (int i = 0; i < 256; i++) r->clut_own_any |= r->clut_own[i];
            r->clut_force = 1;
        }
        return 0;
    }
    flush_batch(r);                       /* drawn with the CLUT buffer as it is now */
    for (Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(p)) rt_writeback(r, t);
    upload_pages(r, p);
    int is32 = cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24;
    uint32_t u[3][4] = { { rc->bp, (uint32_t)rc->psm, (uint32_t)csm, csa },
                         { n, (uint32_t)is32, rc->bw, rc->x / 16u },
                         { rc->y, 0, 0, 0 } };
    if (!r->be->clut_load_gpu(u)) return 0;
    if (r->clut_check == 2) {
        /* $RG_GPU_CLUT=check2 (with wide): without changing any page state, the mirror of p
         * vs local memory on the pages local memory is current for (neither GPU-newer nor
         * split), per page */
        static uint8_t *mir;
        static int printed2;
        if (!mir) mir = (uint8_t *)malloc(GS_VRAM_BYTES);
        uint32_t runs[1024];
        int nr_ = 0;
        for (uint32_t pg = 0; pg < 512; pg++)
            if (p.get(pg)) { runs[2 * nr_] = pg * 8192u; runs[2 * nr_ + 1] = 8192u; nr_++; }
        r->be->mirror_download(runs, nr_, mir);
        for (uint32_t pg = 0; pg < 512; pg++) {
            if (!p.get(pg)) continue;
            int gn = r->gpu_newer.get(pg), sp = r->split.get(pg), cn = r->cpu_newer.get(pg);
            int same = !memcmp(mir + pg * 8192u, gs->vram + pg * 8192u, 8192u);
            if (!same && !gn && !sp) {
                r->stats.clut_check_bad++;
                if (printed2 < 30) {
                    printed2++;
                    fprintf(stderr, "gpu clut check2: page %u mirror != local memory (gpu_newer %d split %d cpu_newer %d) load bp %u at %u,%u\n",
                            pg, gn, sp, cn, (unsigned)rc->bp, (unsigned)rc->x, (unsigned)rc->y);
                }
            }
        }
    }
    if (r->clut_check == 1) {
        /* $RG_GPU_CLUT=check: the model's arithmetic on the read-back bytes vs the GPU's */
        static int printed;
        GpuClutCB gb;
        sync_for_cpu_read(r, p);
        if (r->be->clut_read(&gb)) {
            const uint32_t *w = &gb.c[0][0];
            int bad = 0;
            for (uint32_t i = 0; i < n; i++) {
                uint32_t x, y, bw;
                if (csm == 0) {
                    bw = 1;
                    if (n == 256) { uint32_t q = (i & 0xE7u) | ((i & 8u) << 1) | ((i & 0x10u) >> 1); x = q & 15u; y = q >> 4; }
                    else { x = i & 7u; y = i >> 3; }
                } else { bw = rc->bw; x = rc->x + i; y = rc->y; }
                uint32_t v = gs_read_pixel(gs, rc->psm, rc->bp, bw, x, y), lo, hi = 0, c0, c1 = 0;
                if (is32 && csm == 0) {
                    uint32_t e = ((csa & 15u) * 16u + i) & 255u;
                    c0 = e; c1 = e + 256; lo = v & 0xFFFF; hi = v >> 16;
                } else {
                    c0 = (csa * 16u + i) & 511u; lo = v & 0xFFFF;
                }
                uint32_t g0 = (w[c0 >> 1] >> ((c0 & 1) * 16)) & 0xFFFF;
                if (g0 != lo) bad++;
                if (is32 && csm == 0) {
                    uint32_t g1 = (w[c1 >> 1] >> ((c1 & 1) * 16)) & 0xFFFF;
                    if (g1 != hi) bad++;
                }
            }
            r->stats.clut_check_bad += bad ? 1 : 0;
            if (bad && printed < 20) {
                printed++;
                fprintf(stderr, "gpu clut check: load psm %02x bp %u bw %u at %u,%u csm %d csa %u cpsm %02x n %u: %d cells differ\n",
                        (unsigned)rc->psm, (unsigned)rc->bp, (unsigned)rc->bw, (unsigned)rc->x, (unsigned)rc->y, csm, csa, cpsm, n, bad);
            }
        }
    }
    clut_words(csm, csa, cpsm, n, r->clut_own, 1);
    r->clut_own_any = 1;
    r->clut_seen_loads = gs->stats.clut_loads;   /* gs->clut did not change: the generation by hand */
    r->clut_gen_id++;
    r->clut_uploaded_gen = r->clut_gen_id;       /* the buffer holds it */
    r->clut_valid = 1;
    r->stats.clut_gpu++;
    if (r->trace)
        fprintf(r->trace, "C gpu clut psm %02x bp %u bw %u rect %u,%u %ux%u csm %d csa %u cpsm %02x n %u\n", (unsigned)rc->psm,
                (unsigned)rc->bp, (unsigned)rc->bw, (unsigned)rc->x, (unsigned)rc->y, (unsigned)rc->w, (unsigned)rc->h,
                csm, csa, cpsm, n);
    return 1;
}

static void replay_free(gpu_renderer *r);

/* hooks.xfer_clean (gs.h, redundant upload elision): local memory holds the
 * newest data of rc's pages, so a transfer that would write the bytes gs->vram
 * already holds changes nothing anywhere */
static int on_xfer_clean(void *user, gs_state *gs, const gs_mem_rect *rc);
/* hooks.lazy_ok (gs.h "lazy transfers"): nothing of ours in the rectangle's
 * pages, so the model may keep the transfer pending ($RG_GPU_NO_LAZY=1: never) */
static int on_lazy_ok(void *user, gs_state *gs, const gs_mem_rect *rc)
{
    gpu_renderer *r = (gpu_renderer *)user;
    if (r->no_lazy || !on_xfer_clean(user, gs, rc)) return 0;
    Pages p = pages_of_rect(rc);
    for (const Rt &t : r->rts)
        if (t.pages.overlaps(p)) return 0;
    if (r->batch_read.overlaps(p)) return 0;
    r->drawn.sub(p);   /* a host->local upload (kept pending): item 8, tex_pages_ordinary */
    return 1;
}

/* the pages a draw with the GS state in force can read or write (texture
 * levels unless skip_tex, frame and Z buffer rows to the scissor): pending
 * transfers there are written first (they are older than the draw) */
static void lazy_before_draw(gpu_renderer *r, gs_state *gs, int skip_tex)
{
    uint64_t gen = gs_mem_lazy_gen(gs);
    if (!gen) return;
    uint64_t prim = gs->reg[GS_PRIM];
    uint64_t attr = (gs->reg[GS_PRMODECONT] & 1) ? prim : gs->reg[GS_PRMODE];
    int c = (int)BITS(attr, 9, 1);
    {
        /* nothing accepted since the last check of the same state: nothing to write */
        uint64_t key[9] = { gen, attr & 0x210, gs->reg[GS_FRAME_1 + c], gs->reg[GS_ZBUF_1 + c], gs->reg[GS_SCISSOR_1 + c],
                            gs->reg[GS_TEX0_1 + c], gs->reg[GS_TEX1_1 + c], gs->reg[GS_MIPTBP1_1 + c], (uint64_t)skip_tex };
        if (!memcmp(key, r->lz_key, sizeof key)) return;
        memcpy(r->lz_key, key, sizeof key);
    }
    Pages lz;
    lz.clear();
    if (!gs_mem_lazy_pages(gs, lz.w)) return;
    uint64_t fr = gs->reg[GS_FRAME_1 + c], zb = gs->reg[GS_ZBUF_1 + c], sc = gs->reg[GS_SCISSOR_1 + c];
    uint32_t fbw = BITS(fr, 16, 6) ? BITS(fr, 16, 6) : 1;
    int y1 = (int)BITS(sc, 48, 11) + 1;
    Pages p = pages_of(BITS(fr, 0, 9) * 32u, fbw, (int)BITS(fr, 24, 6), 0, 0, (int)fbw * 64, y1);
    p.add(pages_of(BITS(zb, 0, 9) * 32u, fbw, (int)BITS(zb, 24, 4) | 0x30, 0, 0, (int)fbw * 64, y1));
    if (lz.overlaps(p)) {
        Pages w = lz.and_(p);
        gs_mem_materialize(gs, w.w, 1);
    }
    if ((attr & 0x10) && !skip_tex) {
        uint64_t t0 = gs->reg[GS_TEX0_1 + c], t1 = gs->reg[GS_TEX1_1 + c];
        int tw = (int)BITS(t0, 26, 4), th = (int)BITS(t0, 30, 4);
        if (tw > 10) tw = 10;
        if (th > 10) th = 10;
        /* level 0: the pending transfers holding its blocks (not whole pages) */
        gs_mem_materialize_rect_h(gs, (int)BITS(t0, 20, 6), BITS(t0, 0, 14), BITS(t0, 14, 6) ? BITS(t0, 14, 6) : 1, 0, 0,
                                  1u << tw, 1u << th, 1);
        int mxl = (int)BITS(t1, 2, 3), mmin = (int)BITS(t1, 6, 3);
        if (mxl > 0 && mmin >= 2 && mmin <= 5) {
            Key k;
            memset(&k, 0, sizeof k);
            k.tex0 = t0;
            k.tex1 = t1;
            k.clamp = gs->reg[GS_CLAMP_1 + c];
            k.miptbp1 = gs->reg[GS_MIPTBP1_1 + c];
            k.miptbp2 = gs->reg[GS_MIPTBP2_1 + c];
            Pages tp = tex_pages(k);
            if (lz.overlaps(tp)) {
                Pages w = lz.and_(tp);
                gs_mem_materialize(gs, w.w, 1);
            }
        }
    }
}

static int on_xfer_clean(void *user, gs_state *gs, const gs_mem_rect *rc)
{
    gpu_renderer *r = (gpu_renderer *)user;
    (void)gs;
    if (r->no_elide) return 0;
    Pages p = pages_of_rect(rc);
    if (r->gpu_newer.overlaps(p) || r->split.overlaps(p) || pending_writes(r).overlaps(p)) return 0;
    for (const Rt &t : r->rts)
        if (t.has_dirty && t.pages.overlaps(p)) return 0;
    return 1;
}

/* ============================================================ public */
extern "C" {

/* GS_NATIVE_MARK written (docs/NATIVE-RENDER.md): the native handler */
static void on_native(void *user, gs_state *gs, uint64_t value)
{
    gpu_renderer *r = (gpu_renderer *)user;
    if (r->nat_fn) r->nat_fn(r->nat_user, r, gs, value);
}

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
        const char *nz = getenv("RG_GPU_NO_ZROV");
        if (nz && nz[0] == '1') c.no_zrov = 1;
    }
    if (c.no_rov) c.no_zrov = 1;
    RG_X64_VA_FENCE(1);
    GpuBackend *be = gpu_backend_d3d11_create(&c, c.scale, err, errcap);
    RG_X64_VA_FENCE(0);
    if (!be) return NULL;
    gpu_renderer *r = new gpu_renderer();
    r->rp_c = r->rp_z = -1;
    r->cfg = c;
    r->scale = c.scale;
    r->be = be;
    r->gs = NULL;
    memset(&r->stats, 0, sizeof r->stats);
    r->cpu_newer.all();
    r->gpu_newer.clear();
    r->have_key = 0;
    r->clut_valid = 0;
    r->clut_uploaded_gen = 0;
    r->clut_seen_loads = ~0ull;
    r->clut_gen_id = 1;
    memset(r->clut_copy, 0, sizeof r->clut_copy);
    r->sw_once = 0;
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
        const char *tb = getenv("RG_GPU_TRI_BOX");   /* measurement */
        r->tri_box = tb && tb[0] == '1';
        const char *nd = getenv("RG_GPU_NO_DEFER");
        r->no_defer = nd && nd[0] == '1';
        const char *nel = getenv("RG_GPU_NO_ELIDE");   /* control: no redundant upload elision */
        r->no_elide = nel && nel[0] == '1';
        const char *nlz = getenv("RG_GPU_NO_LAZY");    /* control: no lazy transfers */
        r->no_lazy = nlz && nlz[0] == '1';
        const char *nlt = getenv("RG_GPU_NO_LAZY_TEX"); /* control: native textures never from pending transfers */
        r->no_lazy_tex = nlt && nlt[0] == '1';
        const char *gcl = getenv("RG_GPU_CLUT");        /* 0: CLUT loads always by the model (read-backs) */
        r->no_gpu_clut = gcl && gcl[0] == '0';
        r->clut_check = gcl && gcl[0] == 'c' ? (gcl[5] == '2' ? 2 : 1) : 0;
        r->clut_wide = gcl && (gcl[0] == 'w' || r->clut_check == 2);
        const char *gb = getenv("RG_GPU_BLK");
        r->no_blk = gb && gb[0] == '0';
        const char *fc = getenv("RG_NR_IMFB_CENSUS");
        r->fb_census = fc && fc[0] == '1';
        const char *as = getenv("RG_NR_ASAT");
        r->no_asat = as && as[0] == '0';
        const char *fr = getenv("RG_NR_FBRECT");
        r->no_fbrect = fr && fr[0] == '0';
        const char *gl = getenv("RG_NR_GSLIN");
        r->no_gslin = gl && gl[0] == '0';
        const char *cr = getenv("RG_NR_CROV");
        r->no_crov = cr && cr[0] == '0';
        r->blk_check = gb && gb[0] == 'c';
        const char *lcd = getenv("RG_GPU_LAZY_CPU");
        r->lazy_cpu_decode = lcd && lcd[0] == '1';
        const char *sl = getenv("RG_GPU_SYNC_LOG");   /* measurement */
        r->sync_log = sl && sl[0] ? fopen(sl, "w") : NULL;
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
    r->exact = be->exact() && c.fault != 4;
    r->rov = be->rov();
    r->zrov = r->rov && be->zrov();
    snprintf(r->name, sizeof r->name, "%s%s", be->name(), r->exact ? "" : " [float triangles]");
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
    fprintf(stderr, "gpu coherence: %llu downloads (%.1f ms, %llu KB), %llu reads served by the block rule, "
            "blk check bad %llu, clut gpu %llu, resolves %llu; meshes pre-warmed %llu, uploaded on the GS thread %llu; immediate primitives through the ordered colour view %llu (As > 0x80: %llu)\n",
            (unsigned long long)r->stats.downloads, r->stats.download_us / 1000.0,
            (unsigned long long)(r->stats.download_bytes >> 10), (unsigned long long)r->blk_reads,
            (unsigned long long)r->blk_check_bad, (unsigned long long)r->stats.clut_gpu,
            (unsigned long long)r->stats.clut_resolves, (unsigned long long)r->be->n_nr_mesh_pre,
            (unsigned long long)r->be->n_nr_mesh, (unsigned long long)r->im_crov_prims, (unsigned long long)r->im_asat_prims);
    if ((getenv("RG_GPU_PROFILE") && getenv("RG_GPU_PROFILE")[0] == '1') ||
        (getenv("RG_GPU_STATS") && getenv("RG_GPU_STATS")[0] == '1')) {
        const gpu_stats &st = r->stats;
        fprintf(stderr, "gpu cpu waits: %llu downloads %.1f ms (%llu KB), %llu kicks %.1f ms, "
                "%llu merges, %llu batches, %llu write-backs, %llu KB uploaded\n",
                (unsigned long long)st.downloads, st.download_us / 1000.0,
                (unsigned long long)(st.download_bytes >> 10), (unsigned long long)st.kicks,
                st.kick_us / 1000.0, (unsigned long long)st.merges, (unsigned long long)st.batches,
                (unsigned long long)st.rt_writebacks, (unsigned long long)(st.upload_bytes >> 10));
    }
    if (r->gs) gpu_detach(r);
    free(r->read_mask);
    if (r->sync_log) fclose(r->sync_log);
    if (r->trace) fclose(r->trace);
    if (r->rt_log) fclose(r->rt_log);
    if (r->filt_log) fclose(r->filt_log);
    free(r->merge_mask);
    for (Rt &t : r->rts) r->be->rt_destroy(t.id);
    replay_free(r);
    free(r->rp_gs);
    delete r->be;
    delete r;
}

const char *gpu_device_name(const gpu_renderer *r) { return r->name; }

int gpu_exact_triangles(const gpu_renderer *r) { return r->exact; }

int gpu_ordered_blend(const gpu_renderer *r) { return r->rov; }
int gpu_ordered_depth(const gpu_renderer *r) { return r->zrov; }

void gpu_attach(gpu_renderer *r, gs_state *gs)
{
    if (r->gs) gpu_detach(r);
    r->gs = gs;
    gs->hooks.user = r;
    gs->hooks.draw = on_draw;
    gs->hooks.mem = on_mem;
    gs->hooks.native = on_native;
    gs->hooks.xfer_clean = on_xfer_clean;
    gs->hooks.lazy_ok = on_lazy_ok;
    gs->hooks.clut_load = on_clut_load;
    gs->sw_raster = 0;
    gs_mem_gen_bump(gs, NULL);   /* whatever drew before is unknown to the elision */
    r->cpu_newer.all();
    r->gpu_newer.clear();
    if (r->merge_mask) memset(r->merge_mask, 0, GS_VRAM_BYTES);
    memset(r->blk_stale, 0, sizeof r->blk_stale);
    r->split.clear();
    r->xfer_split = 0;
    for (Rt &t : r->rts) r->be->rt_destroy(t.id);
    r->rts.clear();
    r->have_key = 0;
    r->clut_valid = 0;
    r->clut_seen_loads = ~0ull;
    r->clut_gen_id++;
    memset(r->clut_own, 0, sizeof r->clut_own);   /* gs->clut is the truth again */
    r->clut_own_any = 0;
    r->verts.clear();
    r->tris.clear();
    r->boxes.clear();
    r->batch_read.clear();
    r->batch_written.clear();
}

void gpu_detach(gpu_renderer *r)
{
    gs_state *gs = r->gs;
    if (!gs) return;
    gpu_sync(r);
    r->sw_once = 0;
    gs->hooks.user = NULL;
    gs->hooks.draw = NULL;
    gs->hooks.mem = NULL;
    gs->hooks.native = NULL;
    gs->hooks.xfer_clean = NULL;
    gs->hooks.lazy_ok = NULL;
    gs->hooks.clut_load = NULL;
    gs->sw_raster = 1;
    r->gs = NULL;
}

gs_state *gpu_attached_state(const gpu_renderer *r) { return r->gs; }

void gpu_flush(gpu_renderer *r)
{
    if (!r->gs) return;
    sw_restore(r);
    flush_batch(r);
}

void gpu_sync(gpu_renderer *r)
{
    if (!r->gs) return;
    sw_restore(r);
    flush_batch(r);
    clut_resolve(r);                      /* GPU-side CLUT loads back into gs->clut */
    gs_mem_materialize(r->gs, NULL, 1);   /* pending (lazy) transfers into local memory */
    for (Rt &t : r->rts) rt_writeback(r, t);
    Pages all;
    all.all();
    download_pages(r, all);
}

void gpu_mem_written(gpu_renderer *r, const gs_mem_rect *rc)
{
    if (!r->gs) return;
    sw_restore(r);
    Pages p;
    if (rc) p = pages_of_rect(rc);
    else p.all();
    gs_mem_gen_bump(r->gs, p.w);
    cpu_write_begin(r, p);
    cpu_write_end(r, p);
    r->drawn.sub(p);   /* the host wrote local memory directly */
}

const gpu_stats *gpu_get_stats(const gpu_renderer *r) { return &r->stats; }

int gpu_get_scale(const gpu_renderer *r) { return r->scale; }
void gpu_set_im_xfree(gpu_renderer *r, int on) { if (r) r->im_xfree = on != 0; }

int gpu_read_target(gpu_renderer *r, uint32_t bp, uint32_t bw, int psm, int x, int y, int w,
                    int h, uint32_t *out)
{
    if (!r->gs) return -1;
    sw_restore(r);
    flush_batch(r);
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
    gs_state *gs = r->gs;
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
    gs_state *gs = r->gs;
    if (!gs) return -1;
    sw_restore(r);
    flush_batch(r);
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
            upload_pages(r, p);
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
    sw_restore(r);
    flush_batch(r);
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

int gpu_read_output(gpu_renderer *r, int field, const gpu_post *p, uint32_t *out,
                    uint32_t out_cap_px, uint32_t *w, uint32_t *h)
{
    if (gpu_post_identity(p)) return gpu_read_display(r, field, out, out_cap_px, w, h);
    *w = *h = 0;
    if (!r->gs) return -1;
    sw_restore(r);
    flush_batch(r);
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
    return r->be->display_post(d, pp, out);
}

int gpu_set_scale(gpu_renderer *r, int scale)
{
    if (scale < 1) scale = 1;
    if (scale > 8) scale = 8;
    if (scale == r->scale) return r->scale;
    if (r->gs) {
        sw_restore(r);
        flush_batch(r);
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
    r->have_key = 0;   /* the derived constants carry the scale */
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
        sw_restore(r);
        flush_batch(r);   /* the pending batch keeps the old settings */
    }
    r->enh = n;
}

void gpu_get_enhance(const gpu_renderer *r, gpu_enhance *e) { *e = r->enh; }

/* ======================================================== native draws
 * docs/NATIVE-RENDER.md: a mesh drawn by the native pipeline at the marker's
 * place in the GS stream.  Targets, coherence and the texture follow the same
 * rules as a batch (flush_batch); the state is the GS registers in force. */
void gpu_nr_prims_begin(gpu_renderer *r)
{
    flush_batch(r);
    r->nr_exact_saved = r->exact;
    r->exact = 0;
    r->have_key = 0;   /* a batch never mixes exact and natively generated triangles */
}

void gpu_nr_prims_alpha_swap(gpu_renderer *r, int on) { r->nr_swap = on != 0; }

void gpu_nr_prims_end(gpu_renderer *r)
{
    r->nr_swap = 0;
    flush_batch(r);
    r->exact = r->nr_exact_saved;
    r->have_key = 0;
}

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

/* Textures straight from a pending transfer's linear data (lazy transfers):
 * the formats whose texel value is the transfer's pixel value, decoded exactly
 * as tex_fetch (gs_draw.hlsl) does for level 0 (CLUT, TEXA expansion). */
static int lazy_psm_ok(int psm)
{
    return psm == GS_PSMCT32 || psm == GS_PSMCT24 || psm == GS_PSMCT16 || psm == GS_PSMCT16S || psm == GS_PSMT8 ||
           psm == GS_PSMT4 || psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH;
}
static inline uint32_t lz_e16(uint32_t c, uint32_t ta0, uint32_t ta1, uint32_t aem)
{
    uint32_t a = (c & 0x8000) ? ta1 : ((aem && (c & 0x7FFF) == 0) ? 0 : ta0);
    return ((c & 31) << 3) | ((((c >> 5) & 31) << 3) << 8) | ((((c >> 10) & 31) << 3) << 16) | (a << 24);
}
static inline uint32_t lz_e24(uint32_t c, uint32_t ta0, uint32_t aem)
{
    c &= 0xFFFFFF;
    return c | (((aem && c == 0) ? 0u : ta0) << 24);
}
/* raw texel values (gs_read_pixel) -> RGBA8 in place */
static void lazy_decode(int psm, uint32_t *px, int W, int H, const uint16_t *clut, uint32_t cpsm, uint32_t csa,
                        uint32_t ta0, uint32_t ta1, uint32_t aem)
{
    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++) {
            uint32_t i = (uint32_t)(y * W + x), raw = px[i], c;
            switch (psm) {
            case GS_PSMCT32: c = raw; break;
            case GS_PSMCT24: c = lz_e24(raw, ta0, aem); break;
            case GS_PSMCT16: case GS_PSMCT16S: c = lz_e16(raw, ta0, ta1, aem); break;
            default:
                if (cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24) {
                    uint32_t e = ((csa & 15) * 16 + raw) & 255;
                    uint32_t cc = (uint32_t)clut[e] | ((uint32_t)clut[e + 256] << 16);
                    c = cpsm == GS_PSMCT24 ? lz_e24(cc, ta0, aem) : cc;
                } else {
                    c = lz_e16(clut[(csa * 16 + raw) & 511], ta0, ta1, aem);
                }
                break;
            }
            px[i] = c;
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
static int nr_draw_resolved(gpu_renderer *r, const Key &k, const Derived &d, const gpu_nr_draw *nd,
                            const GpuImVtx *iv, uint32_t niv, int keep_gs_filter, const GpuRect *im_read)
{
    gs_state *gs = r->gs;
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
         * clipped to the target) */
        GpuRect tr = *im_read;
        if (src) {
            if (tr.x1 > src->w && tr.x1 <= src->w + 2) tr.x1 = src->w;
            if (tr.y1 > src->h && tr.y1 <= src->h + 2) tr.y1 = src->h;
        }
        /* RG_NR_DIRECT_LOG=N (measurement): the first N immediates with a target at the
         * texture's base that are not sampled directly, and why */
        static int dlg = -1, dln;
        if (dlg < 0) { const char *e = getenv("RG_NR_DIRECT_LOG"); dlg = e ? atoi(e) : 0; }
        int why_nd = 0;
        if (!src) why_nd = 4;
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
                if (&t != src && t.pages.overlaps(rp)) {
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
        dir_why = src ? 0 : why_nd;
    }
    if (r->filt_log && d.tme) {
        /* dir: -1 not eligible for direct sampling (mesh, indexed, ...), 0 sampled from the live
         * target, 1 target stale where read, 2 read outside the target, 3 another target overlaps,
         * 4 no target at the texture's base (1-4: decoded from the 1x mirror) */
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
        if (nat < 0) { const char *e = getenv("RG_NR_NATTAP"); nat = !(e && e[0] == '0'); }
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
    uint64_t lkey = 0;
    int lazy_tex = 0, lazy_miss = 0;
    uint32_t lazy_key[8];
    if (d.tme && g.tex_rt < 0 && !r->no_lazy_tex && d.tbw && lazy_psm_ok(d.tpsm)) {
        /* the texture lies in one pending transfer (lazy transfers): decoded
         * from the transfer's bytes once, keyed by their content; local memory
         * and the mirror are not needed */
        lazy_tex = gs_mem_lazy_texels(gs, d.tbp, d.tbw, d.tpsm, (uint32_t)(g.dec_rect.x1 - g.dec_rect.x0),
                                      (uint32_t)(g.dec_rect.y1 - g.dec_rect.y0), &lkey, NULL);
    }
    if (lazy_tex) {
        int wms = (int)BITS(k.clamp, 0, 2), wmt = (int)BITS(k.clamp, 2, 2);
        if (wms >= 2 || wmt >= 2) r->nrs.unsupported_state++;
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
        g.dec_key[0] = 0x80000000u | ((uint32_t)d.tpsm << 20);   /* (bit 31: not a local-memory key) */
        g.dec_key[3] = (uint32_t)cg;
        g.dec_key[4] = (uint32_t)(cg >> 32);
        g.dec_key[5] = (uint32_t)lkey;
        g.dec_key[7] = (uint32_t)(lkey >> 32);
        if (!r->be->nr_tex_cached(g.dec_key, g.dec_rect)) {
            if (r->lazy_cpu_decode) {
                int W = g.dec_rect.x1 - g.dec_rect.x0, H = g.dec_rect.y1 - g.dec_rect.y0;
                if (d.indexed) clut_resolve(r);
                r->lz_rgba.resize((size_t)W * H);
                if (gs_mem_lazy_texels(gs, d.tbp, d.tbw, d.tpsm, (uint32_t)W, (uint32_t)H, &lkey, r->lz_rgba.data())) {
                    lazy_decode(d.tpsm, r->lz_rgba.data(), W, H, r->clut_copy, d.cb.d[4][2] & 15u, (d.cb.d[4][2] >> 4) & 31u,
                                d.cb.d[6][1], d.cb.d[6][2], d.cb.d[6][3]);
                    g.dec_rgba = r->lz_rgba.data();
                }
            } else {
                /* not decoded yet: the transfer is written (only its blocks) and
                 * the GPU decodes from the mirror as for any texture, but the copy
                 * is filed under the content key, so the next upload of the same
                 * bytes (next frame, another pool slot) finds it */
                lazy_miss = 1;
                memcpy(lazy_key, g.dec_key, sizeof lazy_key);
            }
            r->nrs.lazy_decodes++;
        }
        r->nrs.lazy_tex++;
        memcpy(r->nr_last_key, g.dec_key, sizeof r->nr_last_key);
    }
    if (d.tme && g.tex_rt < 0 && (!lazy_tex || lazy_miss)) {
        int wms = (int)BITS(k.clamp, 0, 2), wmt = (int)BITS(k.clamp, 2, 2);
        const GpuRect &tr = g.dec_rect;
        if (wms >= 2 || wmt >= 2) r->nrs.unsupported_state++;   /* region modes: sampled as clamp/repeat */
        Pages rp = pages_of(d.tbp, d.tbw ? d.tbw : 1, d.tpsm, tr.x0, tr.y0, tr.x1, tr.y1);
        for (Rt &t : r->rts)
            if (t.has_dirty && t.pages.overlaps(rp) && !(d.hbyte_tex && (t.psm == GS_PSMCT24 || t.psm == GS_PSMZ24)))
                rt_writeback(r, t);
        {
            /* pending transfers holding the texture's blocks: written now
             * (only those; lazy transfers) */
            Pages w;
            w.clear();
            gs_mem_lazy_take_written(gs, NULL);
            /* immediate primitives: only the texels they read (an effect pass
             * reading part of a big buffer must not write every pending
             * texture of the pool beside it) */
            GpuRect mr = tr;
            /* (not for a lazy miss: the decode below is filed under the whole
             * transfer's content key, so the transfer must be written even when
             * the batch reads only texels outside the level-0 rect (repeat UVs
             * past the texture: mr empty, nothing written, stale mirror decoded);
             * writing any of its blocks writes all of it, so this costs nothing) */
            if (im_read && !lazy_miss) {
                mr.x0 = im_read->x0 > tr.x0 ? im_read->x0 : tr.x0;
                mr.y0 = im_read->y0 > tr.y0 ? im_read->y0 : tr.y0;
                mr.x1 = im_read->x1 < tr.x1 ? im_read->x1 : tr.x1;
                mr.y1 = im_read->y1 < tr.y1 ? im_read->y1 : tr.y1;
            }
            if (mr.x1 > mr.x0 && mr.y1 > mr.y0)
                gs_mem_materialize_rect_h(gs, d.tpsm, d.tbp, d.tbw ? d.tbw : 1, (uint32_t)mr.x0, (uint32_t)mr.y0,
                                          (uint32_t)(mr.x1 - mr.x0), (uint32_t)(mr.y1 - mr.y0), 0);
            gs_mem_lazy_take_written(gs, w.w);
            r->cpu_newer.add(w);
            static int nlog = -1;
            if (nlog < 0) nlog = getenv("RG_GPU_LAZY_LOG") ? 0 : 1 << 30;
            if (w.any() && nlog < 60) {
                nlog++;
                fprintf(stderr, "gpu lazy: texture bp %u bw %u psm %02x %dx%d written from pending (tried %d, im %d, tex_rt %d)\n", d.tbp,
                        d.tbw, d.tpsm, tr.x1 - tr.x0, tr.y1 - tr.y0, (int)(!r->no_lazy_tex && d.tbw && lazy_psm_ok(d.tpsm)),
                        iv != NULL, g.tex_rt);
                fprintf(stderr, "   read %d,%d-%d,%d frame %u/%u %02x n %u\n", mr.x0, mr.y0, mr.x1, mr.y1, d.fbp, d.fbw, d.fpsm, niv);
            }
        }
        upload_pages(r, rp, 1);
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
        /* content key of the pages read: FNV of gs->vram per page, cached by
         * the page's mirror stamp; pages the GPU holds newer data for (render
         * targets written back) use their stamp */
        uint32_t newest = 2166136261u;
        for (uint32_t pg = 0; pg < 512; pg++) {
            if (!rp.get(pg)) continue;
            uint32_t ph;
            if (r->gpu_newer.get(pg)) {
                ph = r->page_stamp[pg] ^ 0x80000000u;
            } else {
                if (r->page_hash_stamp[pg] != r->page_stamp[pg] || r->page_hash_stamp[pg] == 0) {
                    const uint32_t *w = (const uint32_t *)(gs->vram + pg * 8192u);
                    uint32_t h = 2166136261u;
                    for (int i = 0; i < 2048; i++) h = (h ^ w[i]) * 16777619u;
                    r->page_hash[pg] = h;
                    r->page_hash_stamp[pg] = r->page_stamp[pg];
                }
                ph = r->page_hash[pg];
            }
            newest = (newest ^ ph ^ pg) * 16777619u;
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
        if (lazy_miss) memcpy(g.dec_key, lazy_key, sizeof lazy_key);
        memcpy(r->nr_last_key, g.dec_key, sizeof r->nr_last_key);
    }
    if (!r->be->nr_draw(g)) { r->nrs.skipped++; return -1; }
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
    gs_state *gs = r->gs;
    if (!gs) return -1;
    sw_restore(r);
    flush_batch(r);                 /* everything before the marker first */
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
    gs_state *gs = r->gs;
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
                    (d.tpsm == d.fpsm && psm_is16(d.fpsm) && r->rov && !r->no_crov)) && !d.zb_feedback;
    int why = psm_is16(d.fpsm) ? 0 : d.date ? 1 : d.merge ? 2 : (d.ate && d.afail != 0) ? 3 : (d.abe && C == 1) ? 4
            : (!k.colclamp || k.pabe || k.scanmsk) ? 5 : d.alias ? 6 : -1;
    int crov = 0;
    if (why < 0 && d.abe && C == 0 && r->rov && !r->no_crov && (!d.need_depth || r->zrov) && !r->no_asat) {
        /* blend factor As above 0x80 (vertex alpha 0xFF: the main menu's caption font, the card
         * screens' text): the GS multiplies by As / 128 > 1 ((Cs - Cd) * 255 >> 7 + Cd, brighter
         * than Cs); the dual-source factor saturates at 1.  The ordered-view back end computes it
         * as the GS does.  (Texel alpha above 0x80 is not looked at.)  RG_NR_ASAT=0: off */
        int nv = type == GS_PRIM_TRIANGLE ? 3 : type == GS_PRIM_POINT ? 1 : 2;
        for (int i = 0; i < nprim && !crov; i++)
            for (int j = 0; j < nv; j++)
                if (v[i * 3 + j].a > 0x80) { crov = 1; break; }
        if (crov) r->im_asat_prims += (uint64_t)nprim;
    }
    if (why >= 0 && why <= 5 && r->rov && !r->no_crov && (!d.need_depth || r->zrov) && !(k.scanmsk & 3) == !(k.scanmsk & 2)) {
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
    if (why >= 0) {
        r->nrs.im_fallback++;
        r->nrs.im_why[why] += (uint64_t)nprim;
        if (r->fb_census) r->fbc[std::make_tuple(why, k.frame, d.tme ? k.tex0 : 0ull)] += (uint64_t)nprim;
        /* RG_NR_IMFB_LOG=N (measurement): the first N fallback batches with their state */
        static int fbl = -1, fbn;
        if (fbl < 0) { const char *e = getenv("RG_NR_IMFB_LOG"); fbl = e ? atoi(e) : 0; }
        if (fbn < fbl) {
            fbn++;
            fprintf(stderr, "nr im fallback %d: why %d type %d n %d FRAME %016llX ZBUF %016llX TEST %016llX ALPHA %016llX "
                            "TEX0 %016llX TEX1 %016llX CLAMP %016llX attr %03llX v0 %u,%u v1 %u,%u uv %u,%u-%u,%u\n",
                    fbn, why, type, nprim, (unsigned long long)k.frame, (unsigned long long)k.zbuf, (unsigned long long)k.test,
                    (unsigned long long)k.alpha, (unsigned long long)k.tex0, (unsigned long long)k.tex1,
                    (unsigned long long)k.clamp, (unsigned long long)k.attr, v[0].x, v[0].y, v[1].x, v[1].y, v[0].u, v[0].v,
                    v[1].u, v[1].v);
        }
        return -1;
    }
    {
        /* RG_NR_IM_EMU=mask (bisection only): leave states to the GS draw path:
         * 1 textured, 2 untextured, 4 triangles, 8 sprites, 16 blended, 32 Z test */
        static int m = -1, efbp = -2;
        if (m < 0) { const char *e = getenv("RG_NR_IM_EMU"); m = e ? atoi(e) : 0; }
        /* RG_NR_IM_EMU_FBP=bp[,bp..] (bisection only): immediates drawing into these FBPs to the GS draw path */
        static uint32_t efb[8];
        if (efbp == -2) {
            const char *e = getenv("RG_NR_IM_EMU_FBP");
            efbp = 0;
            while (e && *e && efbp < 8) { efb[efbp++] = (uint32_t)strtoul(e, (char **)&e, 10); if (*e == ',') e++; else break; }
        }
        static int ealpha = -2;   /* RG_NR_IM_EMU_ALPHA=hex: ... only those with this ALPHA (low byte) */
        if (ealpha == -2) { const char *e = getenv("RG_NR_IM_EMU_ALPHA"); ealpha = e ? (int)strtol(e, NULL, 16) : -1; }
        for (int q = 0; q < efbp; q++)
            if (d.fbp == efb[q] && (ealpha < 0 || (int)(k.alpha & 0xFF) == ealpha)) return -1;
        if (m && (((m & 1) && d.tme) || ((m & 2) && !d.tme) || ((m & 4) && type == GS_PRIM_TRIANGLE) ||
                  ((m & 8) && type == GS_PRIM_SPRITE) || ((m & 16) && d.abe) || ((m & 32) && d.zfunc >= GZ_GEQUAL) ||
                  ((m & 64) && same_buf) || ((m & 128) && d.tme && d.tbp == 0) || ((m & 256) && (k.frame >> 32) != 0)))
            return -1;
    }
    sw_restore(r);
    flush_batch(r);                 /* everything before the primitives first */
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
    sw_restore(r);
    flush_batch(r);
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
    if (!r->rp_gs) r->rp_gs = (gs_state *)malloc(sizeof(gs_state));
    if (!r->rp_gs) return -1;
    /* the GS state of the item: its registers over a copy of the live state
     * (only reg[] is read for a native draw's pipeline) */
    memcpy(r->rp_gs, r->gs, sizeof(gs_state));
    memcpy(r->rp_gs->reg, regs, sizeof r->rp_gs->reg);
    Key k;
    Derived d;
    make_key(r, r->rp_gs, &k);
    derive(r, r->rp_gs, k, &d);
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
