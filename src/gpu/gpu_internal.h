/* SPDX-License-Identifier: CC0-1.0 */
/* Inside src/gpu: the backend interface between the API-agnostic core
 * (gpu_core.cpp: hooks, batching, coherence) and a graphics API
 * (gpu_d3d11.cpp).  docs/GPU.md "Architecture". */
#ifndef RG_GPU_INTERNAL_H
#define RG_GPU_INTERNAL_H

#include <stdint.h>

#include "gpu.h"

/* One expanded vertex (64 bytes); matches VSIn in shaders/gs_draw.hlsl. */
struct GpuVertex {
    float x, y;          /* window pixels (12.4 / 16, XYOFFSET applied) */
    float zf;
    uint32_t zi;
    float r, g, b, a;    /* 0..255 */
    float s, t, q;
    float u, v;          /* texels */
    float fog;
    uint32_t vflags;     /* bit 0: Z constant over the primitive -> zi
                            bit 1: STQ sprite: S/T from spr* (affine formula)
                            bit 2/3: line (minor-pixel DDA; 3 = x-major)
                            bit 4: triangle Z from the plane in spr*
                            bit 5: UV sprite: the fixed-point DDA in spr*
                            bit 6: exact triangle or line (with bit 2):
                                   every attribute from the GpuTri that
                                   spr_u0 indexes (float value) */
    /* STQ sprites: the reference's per-pixel formula, s = s0 + (s1-s0) *
     * (16*px - x0) / dx; all four vertices carry the same values.
     * UV sprites (bit 5, gs_sprite_uv_*): spr_x0/y0 = first covered pixel
     * (base), spr_s0/s1 = U_fp(base) >> 16 and & 0xFFFF, spr_u0/u1 = step
     * >> 16 and & 0xFFFF; V the same in spr_y0, spr_t0/t1, spr_v0/v1. */
    float spr_x0, spr_y0, spr_dx, spr_dy;   /* 12.4 units */
    float spr_s0, spr_s1, spr_t0, spr_t1;
    float spr_u0, spr_u1, spr_v0, spr_v1;   /* 10.4 units */
};

/* One triangle evaluated exactly (vflags bit 6; docs/GPU.md "Exact
 * triangles"): the reference's draw_triangle data, vertices already in its
 * order (v1/v2 swapped when the area is negative), flat shading applied.
 * Lines use entries 0 and 1 (draw_line: t along the major axis).
 * Matches GpuTri in shaders/gs_draw.hlsl (128 bytes). */
struct GpuTri {
    int32_t x[3], y[3];          /* window 12.4 (XYOFFSET applied) */
    uint32_t inv_lo, inv_hi;     /* 1.0 / area (double, the reference's `inv`) */
    float s[3], t[3], q[3];
    uint32_t z[3];
    uint32_t rgba[3];            /* r | g << 8 | b << 16 | a << 24 */
    uint32_t uv[3];              /* u | v << 16 (10.4) */
    uint32_t fog[3];
    uint32_t pad[3];             /* 0: always 0 (the shader's unfuse bound); 1: TF_* flags;
                                    2: (float)1/area, both for the float fast path
                                    (gpu_core.cpp tri_flags, docs/GPU.md "Checkpoint 4") */
};

/* Pixel-shader flags (DrawCB D[0].w), keep in sync with gs_draw.hlsl. */
enum {
    GF_TME = 1u << 0, GF_FGE = 1u << 1, GF_ABE = 1u << 2, GF_FST = 1u << 3,
    GF_DATE = 1u << 4, GF_DATM = 1u << 5, GF_ATE = 1u << 6, GF_NEEDDST = 1u << 7,
    GF_COLCLAMP = 1u << 8, GF_DTHE = 1u << 9, GF_FBA = 1u << 10, GF_PABE = 1u << 11,
    /* bits 12-13 SCANMSK, 14-16 ATST */
    GF_FAILPASS = 1u << 19, GF_MERGE = 1u << 20,
    GF_NOZ = 1u << 21      /* no depth target bound (exact triangles skip Z) */
};

/* Direct render-target sampling (DrawCB D[3].w, docs/GPU.md "Direct
 * sampling"): bit 0 on, bit 1 the source is a depth target, bits 8-15 the
 * source target's PSM.  Keep in sync with gs_draw.hlsl. */
enum { GD_DIRECT = 1u << 0, GD_DEPTH = 1u << 1, GD_DECODED = 1u << 2 };

/* Enhancements (DrawCB D[11].x, docs/GPU.md "Graphics settings"): bits 0-1
 * texture filter override (GPU_TEXF_*), bits 4-8 anisotropic taps (0/1 =
 * off), bit 12: the texture is ordinary memory (no live render target in
 * the pages read; the override and anisotropy apply only then).  0 = the
 * Original pipeline.  Keep in sync with gs_draw.hlsl. */
enum { GE_ORDINARY = 1u << 12 };

struct GpuDrawCB { uint32_t d[12][4]; };
struct GpuClutCB { uint32_t c[64][4]; };

enum GpuZFunc { GZ_OFF = 0, GZ_ALWAYS, GZ_GEQUAL, GZ_GREATER };

struct GpuPass {
    uint32_t failpass;   /* 0 main pass, 1 alpha-fail pass */
    int zwrite;
    uint32_t cmask;      /* D3D-style RGBA write mask bits: 1 R, 2 G, 4 B, 8 A */
};

struct GpuRect { int x0, y0, x1, y1; };   /* native pixels, half-open */

struct GpuDraw {
    int color_rt;            /* backend target id */
    int depth_rt;            /* -1: none bound */
    int rt_w, rt_h;          /* native size of both targets (equal) */
    int vp_w, vp_h;          /* viewport, native: powers of two >= rt (exact NDC) */
    const GpuVertex *verts;
    uint32_t nverts;         /* triangle list */
    const GpuTri *tris;      /* exact triangles the vertices index (vflags bit 6) */
    uint32_t ntris;
    GpuDrawCB cb;            /* pass bit is patched per pass by the backend */
    GpuZFunc zfunc;
    GpuRect scissor;         /* native, half-open */
    int need_dst;            /* snapshot `dst` of the colour target first */
    GpuRect dst;
    GpuPass pass[2];
    int npass;
    /* texture = a live render target sampled directly (-1: the mirror) */
    int tex_rt;
    int tex_snap;            /* tex_rt == color_rt: sample a snapshot of tex_rect */
    GpuRect tex_rect;        /* native, the texels the batch can read */
    /* ordered blending: drawn through the colour target's rasterizer-ordered
     * view in one draw (no snapshot, primitives may overlap; cb D[11].y
     * holds both alpha-test passes' masks).  Only without a depth target. */
    int rov;
    /* decoded texture (docs/GPU.md "Performance"): level-0 texels of the
     * mirror texture in dec_rect, decoded once (CLUT, TEXA expansion) into
     * an RGBA8 texture that the pixel shader reads instead of the mirror
     * (texels outside the rect keep the mirror path).  dec_key identifies
     * the decoded contents exactly (texture registers, CLUT generation,
     * newest mirror write of the pages read): a cached copy with the same
     * key and rect is reused.  dec_new: decode now when nothing is cached
     * (0: use a cached copy only). */
    int dec;
    int dec_new;
    GpuRect dec_rect;
    uint32_t dec_key[8];
};

/* Display: what the PCRTC reads (computed by the core from PMODE etc.). */
struct GpuCircuit {
    int en;
    int rt;                  /* backend colour target id, or -1 = mirror */
    int rt_scale;
    int af_hr;               /* anti-flicker partner one buffer row below the other
                                circuit: its row offset is applied as one row of
                                the internal resolution (docs/GPU.md "Display") */
    uint32_t fbp, fbw; int psm;
    uint32_t dbx, dby;
    int ox, oy, w, h;
};
struct GpuDisplay {
    int out_w, out_h;        /* native */
    int scale;
    int x0, y0;
    int field_sel, field;
    int mmod, slbg; uint32_t alp, bg;
    GpuCircuit c[2];
};

/* Output post chain (gpu_read_output), decided by the core. */
struct GpuPost {
    int ssaa_w, ssaa_h;      /* size after the SSAA resample (= display size: none) */
    int fxaa;
    float sharpen, gamma, brightness;
    int final_w, final_h;    /* size after the output resample */
    int downsample, upscale; /* GPU_RS_* */
    int output_filter;
    int src_lines;           /* native display lines (scanline phase) */
};

/* One vertex of a native immediate draw (gpu_nr_im_submit; nr_draw.hlsl VSImIn,
 * 32 bytes): GS primitive coordinates in pixels (XYOFFSET is applied by the
 * constant row 11), Z as the GS holds it, RGBA 0..255, texture coordinates
 * normalised (S, T, Q; UV mode: u / 16 / width, v / 16 / height, 1), fog. */
struct GpuImVtx {
    float x, y;
    uint32_t z;
    uint32_t rgba;           /* r | g << 8 | b << 16 | a << 24 */
    float s, t, q;
    uint32_t fog;
};

/* A native draw (gpu_nr_submit, docs/NATIVE-RENDER.md), resolved by the core:
 * targets, fixed-function state and the texture to decode/sample. */
struct GpuNrDraw {
    int color_rt, depth_rt;  /* depth_rt -1: no depth target */
    int rt_w, rt_h, vp_w, vp_h;
    GpuRect scissor;
    GpuZFunc zfunc;
    int zwrite;
    uint32_t cmask;          /* RGBA write mask bits: 1 R, 2 G, 4 B, 8 A */
    int abe;
    uint32_t alpha_abcd;     /* A | B << 2 | C << 4 | D << 6 */
    int cull;                /* 0 none, 1 cull clockwise (D3D front), 2 cull counter-clockwise */
    const gpu_nr_draw *d;    /* mesh and bones */
    float cb[26][4];         /* d->cb with rows 11 and 23 filled */
    /* texture: level 0 decoded once (CS_decode with dec_cb, as GpuDraw.dec) */
    int tme;
    GpuRect dec_rect;
    uint32_t dec_key[8];
    GpuDrawCB dec_cb;
    int lin;                 /* bilinear */
    int clamp_u, clamp_v;    /* 1: clamp, 0: repeat */
    /* graphics.anisotropic (gpu_enhance.aniso) on the native renderer: 0 = the plain
     * sampler (Original, off); 2..16 = the backend's anisotropic sampler of that degree.
     * Set by nr_dev only for decoded, ordinary-memory, bilinear 3D textures sampled by the
     * shader's plain Sample path (docs/NATIVE-RENDER.md "Anisotropic filtering") */
    int aniso;
    int tex_cached_only;     /* replay: a decoded texture not in the cache fails the draw (no decode) */
    const GpuImVtx *im;      /* immediate primitives (triangle list) instead of d->mesh; NULL: a mesh */
    /* texture = a live colour target sampled directly at the internal resolution
     * (immediate primitives; -1: the decoded texture); tex_snap: it is the
     * target drawn into: sample a copy of tex_rect taken before the draw */
    int tex_rt, tex_snap;
    GpuRect tex_rect;
    /* the decoded texels (dec_rect, RGBA8) computed by the core from a pending
     * transfer (lazy transfers); NULL: CS_decode from the mirror */
    const uint32_t *dec_rgba;
    uint32_t nim;
    /* immediate runs (gpu_nr_im_submit_swap): runs[2i] = end vertex of run i, runs[2i+1] = 1
     * when its ALPHA has A and B swapped (one draw, a blend state per run, order kept);
     * nruns 0: one run */
    const uint32_t *runs;
    int nruns;
    /* immediate primitives through the colour target's ordered view (PS_nr_c / PS_nr_cz:
     * the GS pixel back end in the shader; cb rows 1-2 hold its state) */
    int crov;
    /* HD texture replacement (src/native/render/nr_texrep.h, docs/TEXTURES.md): non-NULL = draw
     * with this RGBA8 mip chain (any size, same normalised coordinates) instead of the decoded
     * texture; the backend caches it by rep->id */
    const struct NrRepImg *rep;
};

/* GpuBackend::prof_tag categories (interpolated passes, nr_iprec.cpp) */
enum GpuProfTag { GPT_GAME = 0, GPT_SAVE, GPT_PRE, GPT_CREATE, GPT_CLEAR, GPT_LOAD, GPT_COPY, GPT_REINT, GPT_MESH, GPT_IM,
                  GPT_RESTORE, GPT_COMPOSE_PASS, GPT_COMPOSE, GPT_N };

class GpuBackend {
public:
    virtual ~GpuBackend() {}
    virtual const char *name() const = 0;
    /* the pixel shader evaluates GpuTri exactly (double-precision ops) */
    virtual bool exact() const = 0;
    /* rasterizer-ordered views of colour targets (GpuDraw.rov) */
    virtual bool rov() const = 0;
    /* depth targets are tested and written through an ordered view in the
     * pixel shader (no DSV): any depth test is allowed with GpuDraw.rov */
    virtual bool zrov() const { return false; }
    /* ---- the 4 MB local-memory mirror ---- */
    virtual void mirror_upload(uint32_t off, uint32_t len, const uint8_t *src) = 0;
    /* copies [off, off+len) for every run into vram (the CPU copy) */
    virtual void mirror_download(const uint32_t *runs, int nruns, uint8_t *vram) = 0;
    /* merge (data, mask) word pairs into the mirror words [w0, w0 + n):
     * mirror = (mirror & ~mask) | (data & mask), ordered after the work
     * queued so far (docs/GPU.md "Performance", checkpoint 3).  can_merge()
     * false: the core downloads instead. */
    virtual bool can_merge() const { return false; }
    virtual void mirror_merge(uint32_t w0, uint32_t n, const uint32_t *dm) { (void)w0; (void)n; (void)dm; }
    /* ---- render targets (native size; the backend applies the scale) ---- */
    virtual int rt_create(int depth, int w, int h) = 0;
    virtual void rt_resize(int id, int w, int h) = 0;   /* keeps contents */
    virtual void rt_destroy(int id) = 0;
    /* clear a target to 0 (colour) / far (depth); replay targets only */
    virtual void rt_clear(int id) { (void)id; }
    /* mirror -> target, rectangle in native pixels */
    virtual void rt_load(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) = 0;
    /* target -> mirror */
    virtual void rt_writeback(int id, uint32_t bp, uint32_t bw, int psm, const GpuRect &r) = 0;
    /* target -> target at the internal resolution: the native rect sr of src to (dx, dy) of
     * dst (same kind of target; false: not supported, the caller keeps the mirror's copy) */
    virtual bool rt_copy(int dst, int dx, int dy, int src, const GpuRect &sr)
    {
        (void)dst; (void)dx; (void)dy; (void)src; (void)sr;
        return false;
    }
    /* colour target -> colour target as another format over the same memory, at the internal
     * resolution (docs/NATIVE-RENDER.md checkpoint 12): sub-sample by sub-sample, src (stored
     * as spsm at sbp / sbw, native rect sr) is written into a scratch copy of local memory and
     * dst (dpsm at dbp / dbw) loaded from it in its native rect dr; the mirror is not touched
     * (false: not supported) */
    virtual bool rt_reinterpret(int dst, uint32_t dbp, uint32_t dbw, int dpsm, const GpuRect &dr, int src, uint32_t sbp,
                                uint32_t sbw, int spsm, const GpuRect &sr)
    {
        (void)dst; (void)dbp; (void)dbw; (void)dpsm; (void)dr; (void)src; (void)sbp; (void)sbw; (void)spsm; (void)sr;
        return false;
    }
    /* colour target -> RGBA8, (w*scale) x (h*scale) of the native rect (tests) */
    virtual int rt_read(int id, const GpuRect &r, uint32_t *out) = 0;
    /* ---- drawing ---- */
    virtual void set_clut(const GpuClutCB &c) = 0;
    /* GPU-side CLUT loads (docs/NATIVE-RENDER.md "GPU-side CLUT loads"): set_clut of the words
     * whose own[i] is 0 only; CS_clut from the mirror (u: cbp, psm, csm, csa / n, is32, cbw, cou /
     * cov); the CLUT buffer read back (waits) */
    virtual void set_clut_part(const GpuClutCB &c, const uint8_t *own) { (void)own; set_clut(c); }
    virtual bool clut_load_gpu(const uint32_t u[3][4]) { (void)u; return false; }
    virtual bool clut_read(GpuClutCB *out) { (void)out; return false; }
    /* local->local copy in the mirror (CS_l2l_read / _write; native-only device, checkpoint 10):
     * u = (sbp, sbw, spsm, sx) (sy, w, h, dbp) (dbw, dpsm, dx, dy) */
    virtual bool mem_copy(const uint32_t u[3][4]) { (void)u; return false; }
    /* host->local transfers into the mirror on the GPU (CS_xfer): their bytes (each transfer
     * 4-byte aligned, at most XFER_BYTES in all), one descriptor of 8 words per transfer (psm,
     * bp, bw, x, y, w, first pixel in the batch, byte offset; at most XFER_DESCS), npx pixels */
    enum { XFER_BYTES = 8u << 20, XFER_DESCS = 4096 };
    virtual bool mem_xfer_batch(const uint8_t *bytes, uint32_t nbytes, const uint32_t *desc, uint32_t ndesc, uint32_t npx)
    {
        (void)bytes; (void)nbytes; (void)desc; (void)ndesc; (void)npx;
        return false;
    }
    virtual void draw(const GpuDraw &d) = 0;
    /* submit the queued commands to the GPU now (lets the GPU work while
     * the CPU goes on; nothing waits) */
    virtual void kick() = 0;
    /* ---- early copies of a small read-back region (docs/GPU.md
     * "Checkpoint 4") ----
     * snap_copy queues a copy of the mirror byte runs (at most SNAP_BYTES in
     * all, packed in order) into a staging slot and returns the slot (-1:
     * not supported); snap_map waits for that copy only (not for work queued
     * after it) and returns the packed bytes until snap_unmap. */
    enum { SNAP_BYTES = 32768, SNAP_SLOTS = 8 };
    virtual int snap_copy(const uint32_t *runs, int nruns) { (void)runs; (void)nruns; return -1; }
    virtual const uint8_t *snap_map(int slot) { (void)slot; return NULL; }
    virtual void snap_unmap(int slot) { (void)slot; }
    /* ---- display: composes and reads back RGBA8 (out_w*scale x out_h*scale) */
    virtual int display(const GpuDisplay &d, uint32_t *out) = 0;
    /* display + post chain, reads back final_w x final_h RGBA8 */
    virtual int display_post(const GpuDisplay &d, const GpuPost &p, uint32_t *out) = 0;
    /* display / display_post with out == NULL: the frame goes to a shared
     * texture (zero-copy presentation, docs/PERF-3D.md) instead of being read
     * back; this returns its handle (NULL: not supported or failed) */
    virtual void *shared_out() { return NULL; }
    /* Vulkan: the device a presenter may share (gpu_vk_present_device; false: none) */
    virtual bool vk_present_device(gpu_vk_device *out) { (void)out; return false; }
    /* new internal resolution; the core has destroyed every target first */
    virtual void set_scale(int s) = 0;
    /* native draws (docs/NATIVE-RENDER.md): false = not supported */
    virtual bool nr_draw(const GpuNrDraw &g) { (void)g; return false; }
    /* a decoded native texture with this key and rect is cached */
    virtual bool nr_tex_cached(const uint32_t *key, const GpuRect &rc) { (void)key; (void)rc; return false; }
    /* HD texture replacement turned off (docs/TEXTURES.md): drop the uploaded replacements */
    virtual void nr_rep_clear() {}
    /* interpolated presentation (src/native/render/nr_interp.h): a new target holding a copy of
     * target src (same kind and size; -1: not supported), and a whole-target copy between two
     * targets of the same kind and size */
    virtual int rt_clone(int src) { (void)src; return -1; }
    virtual bool rt_put(int dst, int src) { (void)dst; (void)src; return false; }
    /* a new target of the native rect r's size holding that rect of src at (0, 0) (-1: not
     * supported) */
    virtual int rt_clone_rect(int src, const GpuRect &r) { (void)src; (void)r; return -1; }
    /* GPU time by segment ($RG_GPU_PROFILE=4, docs/NATIVE-RENDER.md "Interpolation at 5x"): the
     * GPU work queued from here to the next tag counts for category cat (GpuProfTag) */
    virtual void prof_tag(int cat) { (void)cat; }
    /* the GPU ms and segments counted for cat so far (false: not profiling) */
    virtual bool prof_get(int cat, double *ms, double *n) { (void)cat; (void)ms; (void)n; return false; }
    /* ray tracing, an interpolated present's own TLAS (docs/RAYTRACING.md "RT2d"; nr_iprec.cpp):
     * rt_pass(0) begins a present (false: not wanted), rt_pass_cast hands it each of the
     * present's mesh draws at its interpolated rows (casters only, nothing drawn), rt_pass(1)
     * builds its TLAS before the present draws, rt_pass(2) ends the present */
    virtual bool rt_pass(int phase) { (void)phase; return false; }
    /* (rt4) ray-traced character shadows shown at nearly full strength now (gpu_nr_rt_chars_shadow) */
    virtual int rt_chars_shadow() { return 0; }
    virtual void rt_pass_cast(const GpuNrDraw &g) { (void)g; }
    /* any thread: create the GPU copy of a native mesh ahead of its first draw (gpu.h
     * gpu_nr_mesh_prewarm) */
    virtual void nr_mesh_prewarm(const gpu_nr_mesh &m) { (void)m; }
    /* decoded-texture counters (gpu_stats.tex_decodes / tex_decode_hits) */
    uint64_t n_decodes = 0, n_decode_hits = 0;
    uint64_t n_nr_tex = 0, n_nr_mesh = 0, n_nr_blend_approx = 0, n_nr_mesh_pre = 0;
    uint64_t n_rt_pool_hits = 0;   /* rt_create served from the target pool (no D3D allocation) */
};

GpuBackend *gpu_backend_d3d11_create(const gpu_config *cfg, int scale, char *err, size_t cap);
/* the native-only device's Vulkan backend (src/native/render/nr_vulkan.cpp, RG_HAVE_VULKAN) */
GpuBackend *gpu_backend_vulkan_create(const gpu_config *cfg, int scale, char *err, size_t cap);

/* x64 (docs/X64-PLAN.md 0.6): the backend's device is created inside the address-space
 * fence of src/x64/lowmem_check.c, so the graphics driver's large ranges go above 4 GB */
#if defined(_WIN64)
extern "C" void rg_x64_va_fence(int on);
#define RG_X64_VA_FENCE(on) rg_x64_va_fence(on)
#else
#define RG_X64_VA_FENCE(on) ((void)0)
#endif

/* x64 (docs/X64-PLAN.md 0.10): driver-memory trim of the D3D11 backend.  The NVIDIA x64
 * driver backs EVERY default-usage resource (textures, render targets) with process-private
 * system memory of its size (64 KB granules), placed by the kernel: in this LAA:NO process
 * below 2 GB, and no user-mode hook or VA fence moves it higher (a fence only starves the
 * driver).  The i686 driver does not (tools/x64/d3dfence_probe.c: 2,000 128x128 textures cost
 * 243 MB private on x64, 0 on i686).  Released resources' memory stays committed in the
 * driver's per-size caches, so a stretch that evicts and re-creates many textures of varying
 * sizes (the Insectron results screen: 12,000 native texture decodes in 1,000 fields) grew
 * private commit by ~1.1 GB in a second and CreateTexture2D failed (E_OUTOFMEMORY).
 * rg_x64_trim_note(bytes) as a resource is released: every RG_X64_TRIM_MB released MB
 * (default 16, 0 = off) WHILE the address space is tight (rg_x64_va_tight: each trim stalls
 * ~20 ms) the context is flushed, the GPU waited for (event query) and IDXGIDevice3::Trim
 * returns the driver's cached allocations.  With the shared textures below this is a reserve
 * for non-texture resources.  Timing only. */
#if defined(_WIN64)
/* x64 (docs/X64-PLAN.md 0.10), both backends (D3D11 and Vulkan): the address-space budgets.
 * The NVIDIA x64 drivers back device resources with process-private memory below 2 GB (see
 * the D3D11 shared textures and trim above; Vulkan's allocations likewise).
 * rg_x64_va_tight(bytes about to be created): 1 while the free space below 2 GB is under
 * RG_X64_VA_LOW_MB (default 512; re-measured with a VirtualQuery walk after every 16 MB of
 * creations and every 256 calls); then the texture cache stops growing (evicts instead) and the
 * render-target pool is emptied and not refilled. */
extern "C" size_t rg_x64_va_free_below_2g(void);   /* src/x64/lowmem_check.c */
/* Vulkan twin of the shared textures (nr_vulkan.cpp, x64alt lines): every VMA memory type is
 * allocated EXPORTABLE (VkExportMemoryAllocateInfo, opaque Win32 handles; images and buffers
 * carry the matching VkExternalMemory*CreateInfo): the NVIDIA x64 Vulkan driver then gives it no
 * process-private backing either (Insectron results: free below 2 GB 48 -> 930 MB, commit
 * 1,458 -> 404 MB).  RG_X64_VK_EXTMEM=0 turns it off. */
static inline int rg_x64_vk_extmem(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_X64_VK_EXTMEM"); on = !(e && e[0] == '0'); }
    return on;
}
static inline int rg_x64_va_tight(size_t bytes)
{
    static size_t since, low;
    static unsigned calls;
    static int tight = -1;
    if (tight < 0) {
        const char *e = getenv("RG_X64_VA_LOW_MB");
        low = (size_t)(e && *e ? atoi(e) : 512) << 20;
    }
    since += bytes;
    if (tight < 0 || since >= ((size_t)16 << 20) || ++calls >= 256) {
        since = 0;
        calls = 0;
        int t = rg_x64_va_free_below_2g() < low;
        if (t && tight != 1) fprintf(stderr, "rg x64: address space below 2 GB is tight (under %u MB free)\n", (unsigned)(low >> 20));
        tight = t;
    }
    return tight;
}
#endif

#if defined(_WIN64) && defined(__d3d11_h__)
/* x64 (docs/X64-PLAN.md 0.10): default-usage 2D textures are created SHARED.  The NVIDIA x64
 * driver backs a non-shared default texture with process-private system memory of its size
 * (below 2 GB here), a D3D11_RESOURCE_MISC_SHARED one with none (tools/x64/d3dfence_probe.c:
 * 100 x 1024x1024 RGBA8 cost 420 MB private plain, 0 shared; the same for the formats and
 * bind flags of the backend: RGBA8 / R32 typeless with RT|SRV|UAV, depth R32 typeless with
 * DS(|SRV), R32_UINT SRV|UAV).  Without it the render targets at internal resolution 5x
 * (2560x1440 window: 23 MB each) and the texture cache exhausted the 2 GB in a windowed
 * session.  The macro rewrites every dev->CreateTexture2D(desc, ..) of the including TU (the
 * D3D11 backend) through rg_x64_td: eligible = default usage, no CPU access, one mip, one
 * array slice, no MSAA, no misc flags.  RG_X64_SHARED_TEX=0 turns it off. */
static inline const D3D11_TEXTURE2D_DESC *rg_x64_td(const D3D11_TEXTURE2D_DESC *d)
{
    static int on = -1;
    static thread_local D3D11_TEXTURE2D_DESC c;
    if (on < 0) { const char *e = getenv("RG_X64_SHARED_TEX"); on = e && e[0] >= '0' && e[0] <= '2' ? e[0] - '0' : 1; }
    if (!on || !d || d->Usage != D3D11_USAGE_DEFAULT || d->CPUAccessFlags || d->MipLevels != 1 || d->ArraySize != 1 ||
        d->SampleDesc.Count != 1 || d->MiscFlags)
        return d;
    if (on == 2 && (d->BindFlags & (D3D11_BIND_RENDER_TARGET | D3D11_BIND_DEPTH_STENCIL)))
        return d;   /* 2: textures only, not targets */
    c = *d;
    c.MiscFlags |= D3D11_RESOURCE_MISC_SHARED;
    return &c;
}
#define CreateTexture2D(desc, init, out) CreateTexture2D(rg_x64_td(desc), init, out)

#include <dxgi1_3.h>
struct rg_x64_trimstate {
    ID3D11DeviceContext *ctx;
    ID3D11Query *q;
    IDXGIDevice3 *d3;
    uint64_t n, us;
    size_t acc, step;
    int init;
};
static rg_x64_trimstate g_rg_x64_trim;
static void rg_x64_trim_report(void)
{
    const rg_x64_trimstate &s = g_rg_x64_trim;
    if (s.n)
        fprintf(stderr, "rg x64: driver memory trims: %llu (every %u MB released), %llu ms\n", (unsigned long long)s.n,
                (unsigned)(s.step >> 20), (unsigned long long)(s.us / 1000));
}
static inline void rg_x64_trim_note(ID3D11Device *dev, ID3D11DeviceContext *ctx, size_t bytes)
{
    rg_x64_trimstate &s = g_rg_x64_trim;
    if (!s.init) {
        const char *e = getenv("RG_X64_TRIM_MB");
        s.init = 1;
        s.step = e && *e ? (size_t)atoi(e) << 20 : (size_t)16 << 20;
        atexit(rg_x64_trim_report);
    }
    if (!s.step || !ctx || !dev) return;
    if (s.ctx != ctx) {   /* a new device */
        if (s.q) s.q->Release();
        if (s.d3) s.d3->Release();
        s.q = NULL;
        s.d3 = NULL;
        s.ctx = ctx;
        s.acc = 0;
        D3D11_QUERY_DESC qd = { D3D11_QUERY_EVENT, 0 };
        if (FAILED(dev->CreateQuery(&qd, &s.q))) s.q = NULL;
        if (FAILED(dev->QueryInterface(__uuidof(IDXGIDevice3), (void **)&s.d3))) s.d3 = NULL;
    }
    s.acc += bytes;
    if (s.acc < s.step || !s.d3 || !rg_x64_va_tight(0)) return;
    s.acc = 0;
    LARGE_INTEGER f, t0, t1;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&t0);
    if (s.q) {
        ctx->End(s.q);
        while (ctx->GetData(s.q, NULL, 0, 0) == S_FALSE) SwitchToThread();
    }
    s.d3->Trim();
    QueryPerformanceCounter(&t1);
    s.n++;
    s.us += (uint64_t)((t1.QuadPart - t0.QuadPart) * 1000000 / f.QuadPart);
}
#endif


#endif
