/* SPDX-License-Identifier: CC0-1.0 */
/* Hardware GS renderer (PLAN.md D3): the GS drawing pipeline, local-memory
 * coherence and the PCRTC display on a GPU.  docs/GPU.md.
 *
 * It attaches to a gs_state (src/ps2/gs) through gs_state.hooks: the GS model
 * keeps doing GIF parsing, registers, transfers and CLUT loads on the CPU, and
 * every drawing kick goes to the GPU instead of the software rasterizer.
 * gs->vram stays the authoritative local memory; the renderer keeps
 *   - a 4 MB mirror of it on the GPU (textures and CLUT-free reads are
 *     sampled from the mirror with the real swizzles: no texture cache),
 *   - render targets (colour + depth) keyed by FBP/FBW/PSM and ZBP/FBW/ZPSM,
 *     optionally at an integer upscale factor,
 * and moves data between the three levels only when someone needs it
 * (coherence rules: docs/GPU.md "Coherence").
 *
 * Backend: Direct3D 11 (Windows), hardware or WARP.  The public API is plain
 * C and backend-agnostic.
 */
#ifndef RG_GPU_H
#define RG_GPU_H

#include <stddef.h>
#include <stdint.h>

#include "gs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct gpu_renderer gpu_renderer;

/* The GS state the renderer works with (docs/NATIVE-RENDER.md "Checkpoint 10"): the GS model
 * (src/ps2/gs, rg_gpu: default builds and the oracle twin) or, in RG_NATIVE_ONLY units, the
 * native state block (src/native/render/nr_gs.h; the device is rg_native_render's nr_dev.cpp,
 * rg_gpu and rg_ps2_gs are not linked).  Both have reg[128], clut[512], vq[3] / vq_n / strip_n
 * and stats.clut_loads. */
#ifndef RG_GPU_GS_T
#define RG_GPU_GS_T
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
typedef struct nr_gs gpu_gs;
#else
typedef struct gs_state gpu_gs;
#endif
#endif

typedef struct gpu_config {
    int warp;     /* 1: D3D11 WARP software device (headless tests, CI) */
    int scale;    /* internal resolution factor 1..8 (1 = native, default) */
    int debug;    /* D3D11 debug layer (if the SDK layers are installed) */
    int fault;    /* TEST CONTROL ONLY: 1 = deliberately wrong blend shift,
                     2 = no render-target feedback splitting,
                     3 = no CPU fallback for FRAME/ZBUF on the same pages,
                     4 = triangles through float attribute interpolation
                         even where the device can evaluate them exactly,
                     5 = exact triangles drawn as triangles (rasterizer
                         coverage) instead of their bounding box,
                     6 = destination-reading batches that ordered blending
                         would draw are batched without an overlap split
                         but drawn from one snapshot,
                     7 = decoded textures with a wrong red channel */
    int rtt_native; /* 1: textures that are live render targets are always read
                       through the native-resolution local-memory mirror (each
                       dependent batch writes the target back).  0 (default):
                       a texture that maps cleanly onto a live target (same
                       base/width, compatible format) is sampled from the
                       target itself, at the internal resolution, with no
                       write-back.  Identical results at scale 1; at scale > 1
                       it keeps the upscaled detail (docs/GPU.md "Direct
                       sampling"). */
    int native_af;  /* 1: the anti-flicker display merge (both circuits on one
                       buffer, one row apart) offsets by a whole native row
                       at scale > 1, as the reference.  0 (default): by one
                       row of the internal resolution, so upscaled detail is
                       not shown twice (docs/GPU.md "Display") */
    int no_rov;     /* 1: never draw through rasterizer-ordered views; blended
                       (and DATE / FBMSK-merge) primitives that overlap are
                       then split into batches with a destination snapshot
                       each (docs/GPU.md "Performance").  $RG_GPU_NO_ROV=1
                       sets it too. */
    int readback_lag; /* 1: gpu_read_display / gpu_read_output return the frame
                       of the previous call (presentation only: one field of
                       latency, no wait for the GPU to finish the current
                       frame; docs/GPU.md "Performance").  Never for dumps or
                       validation.  $RG_GPU_READBACK_LAG=1 sets it too. */
    int no_tex_decode; /* 1: textures are always sampled from the mirror (no
                       decoded RGBA copy per batch; docs/GPU.md "Performance").
                       $RG_GPU_NO_DECODE=1 sets it too. */
    int no_zrov;    /* 1: depth targets are hardware depth buffers (D32_FLOAT
                       DSV) even on a device with ordered views; blended or
                       two-pass primitives under a depth test that can fail are
                       then split into serial batches with a destination
                       snapshot each.  0 (default, with ordered views): depth is
                       tested and written in the pixel shader through an
                       ordered view of the depth target, so such primitives
                       share one batch (docs/PERF-3D.md).  $RG_GPU_NO_ZROV=1
                       sets it too; no_rov implies it. */
    int api;        /* graphics API of the native-only device: 0 Direct3D 11 (default on
                       Windows), 1 Vulkan (docs/NATIVE-VULKAN.md; setting display.backend).
                       $RG_GPU_API=vulkan|d3d11 overrides it. */
    int probe_lag;  /* native renderer, real-time play only: small depth read-backs (the
                       lens flare's 8x8 Z probes) are served from the copy taken at the
                       previous probe group, so the game thread does not wait for the GPU
                       to finish the frame (docs/NATIVE-THREADS.md "3h").  Changes what
                       the game reads (flare occlusion one frame late): never in tests,
                       traces or save states.  $RG_GPU_PROBE_LAG=1 / =0 overrides it. */
} gpu_config;

typedef struct gpu_stats {
    uint64_t prims;          /* primitives received */
    uint64_t batches;        /* GPU draw batches submitted */
    uint64_t passes;         /* draw calls (a batch may need 2: AFAIL) */
    uint64_t dst_copies;     /* frame-buffer snapshots for shader blending */
    uint64_t rt_creates, rt_loads, rt_writebacks, rt_drops;
    uint64_t upload_bytes;   /* CPU vram -> GPU mirror */
    uint64_t download_bytes; /* GPU mirror -> CPU vram */
    uint64_t display_frames;
    uint64_t display_af_hr;  /* displays whose anti-flicker merge was applied at
                                the internal resolution (scale > 1) */
    uint64_t feedback_splits; /* batches split because a primitive samples memory
                                 an earlier primitive of the batch drew */
    uint64_t direct_samples;  /* textured batches that sampled a live render
                                 target directly (no mirror round trip) */
    uint64_t writebacks_avoided; /* target write-backs the mirror path would
                                 have done for those batches */
    uint64_t tex_copies;      /* snapshots of the colour target for batches
                                 sampling the target they draw into */
    uint64_t cpu_prims;       /* primitives drawn by the software reference
                                 (FRAME and ZBUF on the same pages) */
    uint64_t exact_tris;      /* triangles whose attributes were evaluated per
                                 pixel in double precision like the reference
                                 (docs/GPU.md "Exact triangles") */
    uint64_t rov_batches;     /* batches drawn through the rasterizer-ordered
                                 view (ordered blending, no snapshot) */
    uint64_t tex_decodes;     /* textures decoded into an RGBA copy (CLUT and
                                 TEXA applied once per texel) */
    uint64_t tex_decode_hits; /* batches that sampled a cached decoded copy */
    uint64_t grown_tris;      /* exact triangles drawn as the triangle grown by a
                                 pixel instead of their bounding box */
    uint64_t kicks;           /* command-buffer flushes (GpuBackend::kick) */
    uint64_t downloads;       /* mirror read-backs (the CPU waits for the GPU) */
    uint64_t download_us;     /* CPU time in them, microseconds */
    uint64_t kick_us;         /* CPU time in the flushes, microseconds */
    uint64_t merges;          /* host->local transfers merged into the mirror on the
                                 GPU instead of a read-back (checkpoint 3) */
    uint64_t shared_rt_batches; /* batches whose colour and depth targets share pages
                                 (rows the scissor keeps apart): both written back
                                 and reloaded afterwards (checkpoint 4) */
    uint64_t reads_current;   /* CPU reads served from gs->vram without a read-back:
                                 every bit read was newest there (checkpoint 4) */
    uint64_t early_copies;    /* copies of a hot read-back region queued after its last
                                 write (checkpoint 4) */
    uint64_t early_reads;     /* CPU reads served from such a copy */
    uint64_t big_tris;        /* exact triangles too large for the 32-bit edge
                                 functions (TF_SMALL off: coverage in double) */
    uint64_t big_px;          /* their bounding boxes, native pixels */
    uint64_t clut_gpu;        /* CLUT loads made on the GPU from its newer copy (docs/NATIVE-RENDER.md
                                 "GPU-side CLUT loads"): no read-back */
    uint64_t clut_resolves;   /* GPU-loaded CLUT words read back for a CPU user (gpu_sync, CPU draws) */
    uint64_t rt_pool_hits;    /* rt_creates served from the backend's target pool (no allocation) */
    uint64_t clut_check_bad;  /* $RG_GPU_CLUT=check: GPU loads that differ from the model's */
} gpu_stats;

/* Describes one live render target (tests: which vram regions it covers). */
typedef struct gpu_target_info {
    uint32_t bp, bw;   /* block pointer, width (64-px units) */
    int psm;           /* GS_PSM* (Z formats for depth targets) */
    uint32_t w, h;     /* native size in use */
} gpu_target_info;

void gpu_config_default(gpu_config *c);
/* NULL on failure (reason in err). */
gpu_renderer *gpu_create(const gpu_config *cfg, char *err, size_t errcap);
void gpu_destroy(gpu_renderer *r);
const char *gpu_device_name(const gpu_renderer *r);
/* 1 when triangles are evaluated exactly (the device has double-precision
 * shader ops incl. the D3D11.1 extended set; docs/GPU.md "Exact triangles"). */
int gpu_exact_triangles(const gpu_renderer *r);
/* 1 when blended / DATE / FBMSK-merge batches without a depth target are drawn
 * through rasterizer-ordered views (D3D11.3 ROVs; docs/GPU.md "Performance"). */
int gpu_ordered_blend(const gpu_renderer *r);
/* 1 when depth is also tested in ordered views (gpu_config.no_zrov): primitives
 * under any depth test then batch like ordered blending without Z */
int gpu_ordered_depth(const gpu_renderer *r);

/* Install the hooks on gs and turn its software rasterizer off.  gs->vram
 * becomes the backing store of the renderer's mirror (uploaded entirely). */
void gpu_attach(gpu_renderer *r, gpu_gs *gs);
/* gpu_sync, then remove the hooks and turn the software rasterizer back on. */
void gpu_detach(gpu_renderer *r);
/* The attached gs_state (NULL if none). */
gpu_gs *gpu_attached_state(const gpu_renderer *r);

/* Submit the pending batch (drawing is otherwise deferred until a state
 * change, a coherence event or a display/sync call). */
void gpu_flush(gpu_renderer *r);
/* Make gs->vram current: flush, write every render target back to the
 * mirror and download every page the GPU changed.  Call before reading
 * gs->vram directly (gs_read_pixel, gs_read_display, dumps). */
void gpu_sync(gpu_renderer *r);
/* Someone wrote gs->vram behind the hooks (gs_write_pixel, memcpy): rect =
 * the region, or NULL for "anything may have changed". */
void gpu_mem_written(gpu_renderer *r, const gs_mem_rect *rect);

/* The PCRTC output (same contract as gs_read_display, built on the GPU from
 * the render targets / mirror), at native size x scale.  RGBA8, A = 0xFF. */
int gpu_read_display(gpu_renderer *r, int field, uint32_t *out, uint32_t out_cap_px,
                     uint32_t *w, uint32_t *h);

const gpu_stats *gpu_get_stats(const gpu_renderer *r);
/* The internal resolution factor in use (1..8). */
int gpu_get_scale(const gpu_renderer *r);
/* Tests/debugging: the upscaled contents of the live colour target
 * (bp, bw, psm) over the native rectangle (x, y, w, h), as the target holds
 * them: (w*scale) x (h*scale) RGBA8 (the decoded stored colour; CT24 alpha
 * 0, CT16 quantised).  Flushes first.  -1 if there is no such live,
 * up-to-date target or the rectangle is outside it. */
int gpu_read_target(gpu_renderer *r, uint32_t bp, uint32_t bw, int psm, int x, int y, int w,
                    int h, uint32_t *out);
/* Live render targets; returns the count (writes at most cap). */
int gpu_targets(gpu_renderer *r, gpu_target_info *out, int cap);

/* ===================================================== native draws
 * The native renderer (src/native/render, docs/NATIVE-RENDER.md) draws model
 * meshes with its own pipeline into the same render targets, at the point of
 * the GS stream where the game's DMA chain carries its marker (an A+D write
 * to GS_NATIVE_MARK).  The handler runs on the GS thread (the GS worker when
 * gs_async is on) in GIF order; it calls gpu_nr_submit. */
typedef void (*gpu_native_fn)(void *user, gpu_renderer *r, gpu_gs *gs, uint64_t value);
void gpu_set_native_handler(gpu_renderer *r, gpu_native_fn fn, void *user);

/* a mesh: vertex and triangle-list index arrays, stable while `id` lives
 * (the renderer keeps GPU copies keyed by id; vertex layout nr_vtx, 28 bytes) */
typedef struct gpu_nr_mesh {
    uint32_t id;
    const void *vtx;
    uint32_t nvtx, stride;
    const uint32_t *idx;
    uint32_t nidx;
} gpu_nr_mesh;

typedef struct gpu_nr_draw {
    gpu_nr_mesh mesh;
    /* nr_draw.hlsl NrCB: rows 0-10, 12-22 from the scene side; rows 11 (target
     * mapping) and 23 (pixel state) are written by gpu_nr_draw */
    float cb[24][4];
    float bones[256][4];       /* VU1 qwords 768..1023 (skinned meshes) */
    int nbones_rows;           /* 0: no bone upload */
    int cull;                  /* 1: cull triangles whose screen area * cull_sign > 0 */
    float cull_sign;
    int has_box;               /* 1: box bounds everything the draw can touch */
    float box[4];              /* GS window coordinates in pixels (before XYOFFSET): x0, y0, x1, y1;
                                  the coherence (dirty) rectangle is clipped to it */
} gpu_nr_draw;

typedef struct gpu_nr_stats {
    uint64_t draws, tris, skipped, tex_decodes, mesh_uploads, blend_approx, unsupported_state, boxed;
    uint64_t im_draws, im_prims, im_fallback, im_skipped;   /* gpu_nr_im_submit */
    uint64_t lazy_tex, lazy_decodes;   /* native draws whose texture came from a pending transfer, CPU decodes */
    /* gpu_nr_im_submit fallbacks by reason: 0 CT16 frame, 1 dest. alpha test, 2 partial FBMSK, 3 AFAIL,
     * 4 blend C = Ad, 5 COLCLAMP off / PABE / SCANMSK, 6 frame-Z alias, 7 texture feedback, 8 mipmaps,
     * 9 region clamp, 10 depth-format texture, 11 backend */
    uint64_t im_why[12];
} gpu_nr_stats;

/* Draw one native mesh with the GS register state in force (FRAME, ZBUF,
 * TEST, ALPHA, TEX0/1, CLAMP, FOGCOL, XYOFFSET, SCISSOR of the PRMODE context).
 * GS thread only.  Returns 0 drawn, 1 nothing to draw (state writes nothing),
 * -1 not drawable (no renderer attached). */
int gpu_nr_submit(gpu_renderer *r, const gpu_nr_draw *d);
/* ANY thread (the EE thread at record time): create the GPU copy of mesh m now, so its
 * first draw on the GS thread does not (docs/NATIVE-RENDER.md "Pre-warm"; the first battle
 * frame uploaded tens of meshes on the GS worker, the pipeline's bottleneck).  m's arrays
 * are copied before the call returns. */
void gpu_nr_mesh_prewarm(gpu_renderer *r, const gpu_nr_mesh *m);
const gpu_nr_stats *gpu_nr_get_stats(const gpu_renderer *r);

/* Re-rendering a retained frame (docs/NATIVE-RENDER.md "Replay": the frame
 * list drawn again without the game, the base of the unlocked frame rate).
 *   gpu_nr_last_texkey  the decoded-texture key (content identity) of the
 *                       last gpu_nr_submit (zeros: untextured / nothing drawn)
 *   gpu_nr_replay_begin an offscreen colour + depth pair (native w x h at the
 *                       internal scale), cleared; not a GS buffer: nothing the
 *                       game or the GS model can see
 *   gpu_nr_replay_draw  d drawn into it with the GS registers regs[128] (the
 *                       item's state at its GS addresses) and the decoded
 *                       texture texkey names, from the renderer's cache only
 *                       (never from local memory, which may hold anything by
 *                       now): 0 drawn, 1 nothing to draw, -1 not drawable
 *                       (texture no longer cached)
 *   gpu_nr_replay_end   reads the colour target back: FNV-64 of its pixels
 * GS thread only. */
void gpu_nr_last_texkey(const gpu_renderer *r, uint32_t key[8]);
/* $RG_NR_FILTLOG (measurement): the EE frame number the per-draw filter log lines carry
 * (nr_frame_begin; any thread, approximate when the GS side lags) */
void gpu_nr_filtlog_frame(uint32_t frame);
int gpu_nr_replay_begin(gpu_renderer *r, int w, int h);
int gpu_nr_replay_draw(gpu_renderer *r, const gpu_nr_draw *d, const uint64_t *regs, const uint32_t *texkey);
int gpu_nr_replay_end(gpu_renderer *r, uint64_t *hash);

/* Immediate primitives natively (docs/NATIVE-RENDER.md "Immediate packets"):
 * the game's 2D / effect packets, decoded by the native renderer, drawn by the
 * native pipeline (hardware rasterizer, decoded texture, hardware blending)
 * with the GS register state in force.  v holds 3 vertices per primitive
 * (sprites use the first 2), as latched by the XYZ writes; type is
 * GS_PRIM_TRIANGLE (triangles of lists, strips and fans; flat shading already
 * applied) or GS_PRIM_SPRITE.  Returns 0 drawn, 1 nothing to draw (the state
 * writes nothing), -1 not covered (the caller draws them through the GS draw
 * path: CT16 targets, destination alpha test / blend factor, partial FBMSK,
 * texture feedback, region clamps, mipmaps, ...).  GS thread only. */
int gpu_nr_im_submit(gpu_renderer *r, const gs_vertex *v, int nprim, int type);
/* 1 while the immediate primitives being submitted were squeezed in X by the widescreen
 * layout (nr_im.c): at an internal scale > 1 point sprites snap only Y to native pixels
 * (coverage and nr_draw.hlsl PF_SNAP), so a 0.75x glyph keeps every texel column */
void gpu_set_im_xfree(gpu_renderer *r, int on);
/* the same, primitive i with the ALPHA register's A and B selectors swapped when swap[i]
 * is 1 (generated shadow faces alternate between (Cs-0)*As+Cd and (0-Cs)*As+Cd: one native
 * draw, a hardware blend state per run of equal flags, primitive order kept) */
int gpu_nr_im_submit_swap(gpu_renderer *r, const gs_vertex *v, int nprim, int type, const uint8_t *swap);

/* Natively generated GS primitives (the native renderer's replacements of
 * the VU1 programs that still produce screen-space primitives, e.g. the
 * shadow volumes, docs/NATIVE-RENDER.md "Shadow volumes"): between begin and
 * end the caller hands primitives to the GS draw path (gs_draw_kick) with the
 * GS register state it wants; they are batched and drawn like the emulated
 * path's, except that triangles always take the float-interpolation path
 * (hardware rasterizer coverage, no exact evaluation).  GS thread only. */
void gpu_nr_prims_begin(gpu_renderer *r);
void gpu_nr_prims_end(gpu_renderer *r);
/* the following primitives' ALPHA is the GS register's with its A and B
 * selectors swapped (the shader swaps them per vertex), so primitives that
 * alternate between (Cs-0)*As+Cd and (0-Cs)*As+Cd share one batch in their
 * order (blending is done in the pixel shader on every path) */
void gpu_nr_prims_alpha_swap(gpu_renderer *r, int on);

/* ===================================================== graphics settings
 * Renderer-side enhancements (PLAN.md P6 "Graphics settings", docs/GPU.md
 * "Graphics settings").  None of them changes what the GS model computes:
 * local memory, FIFO reads, CLUT loads and everything the game can observe
 * stay as at scale 1 / Original, except that upscaled targets write back
 * one sub-sample per pixel (docs/GPU.md "Upscaling").  All-zero / default
 * structures are the Original behaviour, bit-exact with the reference. */

/* Internal resolution, live: writes every render target back, drops them
 * (they reload from local memory at the new scale on their next use) and
 * changes the factor.  Returns the scale in use (1..8). */
int gpu_set_scale(gpu_renderer *r, int scale);

enum { GPU_TEXF_ORIGINAL = 0, GPU_TEXF_BILINEAR = 1, GPU_TEXF_NEAREST = 2 };
/* Effect classes for graphics.bloom / depth_of_field / motion_blur. */
enum { GPU_FX_BLOOM = 0, GPU_FX_DOF = 1, GPU_FX_MOTION_BLUR = 2, GPU_FX_COUNT = 3 };
enum { GPU_FXMODE_ORIGINAL = 0, GPU_FXMODE_ENHANCED = 1, GPU_FXMODE_OFF = 2 };

typedef struct gpu_enhance {
    /* GPU_TEXF_*: overrides the GS MMAG/MMIN choice (nearest <-> bilinear,
     * per mip mode) for non-sprite primitives whose texture is ordinary
     * memory (no live render target in the pages read).  Sprites (2D/UI)
     * and render-target reads (post passes, CLUT tricks) keep the GS
     * filter. */
    int tex_filter;
    /* 0/1 = off, 2..16: anisotropic taps along the major axis of the pixel
     * footprint, at the GS-chosen mip level, for the same primitives when
     * they are sampled bilinearly (after the override).  Exact-triangle
     * devices only (the footprint comes from the triangle's own gradients). */
    int aniso;
    /* graphics.bloom / depth_of_field / motion_blur (GPU_FXMODE_*).  Plumbing
     * only: gpu_core.cpp's effect_class() hook (docs/GPU.md "Screen
     * effects") would classify the game's effect passes, which needs
     * game-side knowledge; until then every mode draws the original. */
    int fx[GPU_FX_COUNT];
} gpu_enhance;

void gpu_enhance_default(gpu_enhance *e);   /* Original: all zero */
void gpu_set_enhance(gpu_renderer *r, const gpu_enhance *e);
void gpu_get_enhance(const gpu_renderer *r, gpu_enhance *e);

/* ---- output post-processing (presentation only; gpu_read_output) ---- */
enum { GPU_RS_BOX = 0, GPU_RS_BILINEAR = 1, GPU_RS_BICUBIC = 2, GPU_RS_LANCZOS = 3,
       GPU_RS_NEAREST = 4, GPU_RS_SHARP = 5 };
enum { GPU_OUTF_OFF = 0, GPU_OUTF_SCANLINES = 1, GPU_OUTF_CRT = 2 };

typedef struct gpu_post {
    int ssaa;          /* 1 (off), 2..4: the display (native x scale) is
                          resampled down by this factor first (supersampling:
                          the caller renders at ssaa x the wanted scale) */
    int downsample;    /* GPU_RS_BOX/BILINEAR/BICUBIC/LANCZOS: filter for every
                          minification (SSAA, and to out_w x out_h) */
    int fxaa;          /* post-process anti-aliasing (own FXAA-style edge blend) */
    float sharpen;     /* 0..1, contrast-adaptive sharpening */
    float gamma;       /* 1 = unchanged; > 1 brightens mid-tones */
    float brightness;  /* 1 = unchanged; multiplier */
    int out_w, out_h;  /* the window rectangle the frame will fill (0: none).
                          The frame is resampled to it when it is larger
                          (minification with `downsample`) or when an output
                          filter needs the final pixel grid */
    int upscale;       /* GPU_RS_NEAREST/BILINEAR/SHARP: magnification filter
                          when the frame is resampled up to out_w x out_h */
    int output_filter; /* GPU_OUTF_* (needs out_w/out_h; applied at that size) */
} gpu_post;

/* Original: ssaa 1, gamma/brightness 1, everything else off. */
void gpu_post_default(gpu_post *p);
/* 1 when p changes nothing (gpu_read_output == gpu_read_display). */
int gpu_post_identity(const gpu_post *p);
/* The PCRTC output through the post chain, for presentation.  With an
 * identity chain this is gpu_read_display (bit for bit).  Otherwise the
 * display is composed on the GPU at native x scale and resampled /
 * filtered there; w x h is the final size (which may be out_w x out_h).
 * Returns -1 with *w, *h set when out_cap_px is too small. */
/* Zero-copy presentation (docs/PERF-3D.md): what gpu_read_output would return,
 * left on the GPU in a texture shared with other D3D11 devices (an NT-less
 * DXGI shared handle with a keyed mutex: acquire key 1 to read it, release
 * key 0; two such textures alternate).  No read-back and no wait for the GPU.
 * *handle is the texture's shared handle (stable while w x h stays), NULL on
 * failure (then use gpu_read_output). */
int gpu_present_shared(gpu_renderer *r, int field, const gpu_post *p, void **handle, uint32_t *w,
                       uint32_t *h);
/* Zero-copy presentation with the Vulkan backend (native-only device, docs/NATIVE-VULKAN.md
 * "Presentation"): the window's renderer runs on the backend's own VkDevice (queue_index 0 of
 * queue_family; the backend submits on another queue of that family), and gpu_present_shared's
 * *handle is then a gpu_vk_frame (not a DXGI handle).  Handles as integers / pointers so no
 * Vulkan header is needed (host.h rg_host_vk_device / rg_host_vk_frame have the same layout). */
typedef struct gpu_vk_device {
    void *instance;            /* VkInstance (with the window-system surface extensions) */
    void *physical_device;     /* VkPhysicalDevice */
    void *device;              /* VkDevice (VK_KHR_swapchain enabled) */
    uint32_t queue_family;     /* the presenter's queue: (queue_family, 0) */
} gpu_vk_device;
typedef struct gpu_vk_frame {
    uint64_t image;            /* VkImage, R8G8B8A8_UNORM, SHADER_READ_ONLY_OPTIMAL while acquired */
    uint32_t img_w, img_h;     /* its size; the frame is its top-left w x h */
    int (*acquire)(void *arg); /* waits until the GPU wrote it; 0 = ok, -1 = taken back / timeout */
    void (*release)(void *arg);/* the presenter's GPU reads of it have completed */
    void *arg;
} gpu_vk_frame;
/* 0 and *out filled when this renderer's backend is Vulkan and can share its device with a
 * presenter; -1 otherwise (D3D11, no second queue, no surface / swapchain extensions) */
int gpu_vk_present_device(gpu_renderer *r, gpu_vk_device *out);
int gpu_read_output(gpu_renderer *r, int field, const gpu_post *p, uint32_t *out,
                    uint32_t out_cap_px, uint32_t *w, uint32_t *h);
/* Display reads (gpu_read_display / gpu_read_output / gpu_present_shared /
 * gpu_display_size) take the PCRTC registers (preg[0..14]: PMODE, SMODE2,
 * DISPFB/DISPLAY, BGCOLOR) from `preg` instead of the attached gs_state until
 * called again with NULL.  For a display composed on the GS worker after the
 * caller has moved on (pipelined presentation, docs/NATIVE-RENDER.md
 * "Overlap"): the caller's thread keeps writing the live registers. */
void gpu_set_display_regs(gpu_renderer *r, const uint64_t *preg);
/* Native display size the PCRTC would show now (0 if off). */
int gpu_display_size(gpu_renderer *r, uint32_t *w, uint32_t *h);

/* ---- the graphics settings as renderer parameters (gpu_gfx.c) ---- */
struct rg_settings;
typedef struct gpu_gfx {
    int internal_res;   /* 1..8, or 0 = match the window */
    int ssaa;           /* 1..4: render at ssaa x, filter down (post.ssaa per frame) */
    gpu_enhance enh;
    gpu_post post;      /* ssaa/out_w/out_h/upscale are filled per frame by the presenter */
} gpu_gfx;
void gpu_gfx_default(gpu_gfx *g);   /* Original */
/* graphics.* of the registry (absent ids keep the Original values) */
void gpu_gfx_from_settings(gpu_gfx *g, const struct rg_settings *s);
/* The render scale for a window rectangle dst_h pixels high showing
 * native_h lines (match window = the smallest factor reaching dst_h), times
 * the SSAA factor, capped at 8x; *ssaa_eff = the SSAA factor kept. */
int gpu_gfx_scale(const gpu_gfx *g, int dst_h, int native_h, int *ssaa_eff);
/* 1 when g is the Original preset's renderer behaviour */
int gpu_gfx_original(const gpu_gfx *g);

#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
/* ===================================================== native-only device (nr_dev.cpp)
 * Local memory is the GPU's alone (docs/NATIVE-RENDER.md "Checkpoint 10"): what the GS model
 * did on its CPU copy, the device does on the mirror.  Worker thread (or drained).
 *   gpu_mem_xfer   a host->local transfer: the first npx pixels (raster order of rc) of the
 *                  transfer data (as the GIF IMAGE data packs them) written into the mirror
 *   gpu_mem_copy   a local->local transfer (TRXDIR 2), pixel values copied (no conversion)
 *   gpu_mem_read   a local->host transfer: rc's pixels packed as transfer data into out
 *                  (bytes); the one read-back (early copies of a region read every frame)
 *   gpu_clut_load  a CLUT load (TEX0 / TEX2 CLD) from rc: from the bytes of the transfer that
 *                  wrote the palette when the CPU knows them (cells written into gs->clut),
 *                  else on the GPU (CS_clut; the device owns those cells).  Returns 0 nothing
 *                  changed, 1 cells changed, 2 loaded on the GPU; dry: decide only
 *   gpu_mem_save   every target written back, the 4 MB mirror read into out (save states)
 *   gpu_mem_load   the 4 MB uploaded, every target dropped, CLUT cells the CPU's (load) */
void gpu_mem_xfer(gpu_renderer *r, const gs_mem_rect *rc, const uint8_t *data, uint32_t npx);
void gpu_mem_copy(gpu_renderer *r, const gs_mem_rect *src, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t dx,
                  uint32_t dy);
int gpu_mem_read(gpu_renderer *r, const gs_mem_rect *rc, uint8_t *out, uint32_t bytes);
int gpu_clut_load(gpu_renderer *r, gpu_gs *gs, const gs_mem_rect *rc, int csm, uint32_t csa, int cpsm, uint32_t n,
                  int dry);
int gpu_mem_save(gpu_renderer *r, uint8_t *out);
void gpu_mem_load(gpu_renderer *r, const uint8_t *in);
/* exit-line counters of the native device (transfers, elisions, CLUT loads by path) */
void gpu_mem_stats(const gpu_renderer *r, FILE *f);
#endif


#ifdef __cplusplus
}
#endif
#endif
