/* SPDX-License-Identifier: CC0-1.0 */
/* HD texture replacement and texture dumping for the native renderer (docs/TEXTURES.md).
 *
 * Off by default (graphics.texture_dump / graphics.texture_replace).  Render-only: nothing here is
 * read by game logic; with both settings off no function below does any work (the device calls
 * them behind nr_texrep_on()).
 *
 * Data flow (GS worker thread):
 *   - host->local transfers are also written into a CPU copy of GS local memory (the "shadow"),
 *     allocated only while a mode is on; GPU writes into local memory (target write-backs,
 *     local->local copies) mark their blocks unknown;
 *   - a native draw whose decoded texture is new (its content key, nr_dev.cpp dec_key) asks
 *     nr_texrep_draw(): the texture's name is computed from the shadow (texture data hash, CLUT
 *     hash, TEX0 bits: the PCSX2 texture-replacement naming, docs/TEXTURES.md "Names"); dump mode
 *     writes it once as PNG (a dump thread); replace mode looks the name up in the pack's index
 *     and, when the file is loaded (a loader thread: PNG / DDS decode, mip chain), returns the
 *     image the backend uploads in place of the decoded texture;
 *   - until a replacement is loaded the original texture is drawn (no stall).
 *
 * The backends (nr_d3d11.cpp, nr_vulkan.cpp) see only GpuNrDraw.rep (a NrRepImg): an RGBA8 mip
 * chain of any size, sampled with the same normalised coordinates as the decoded texture. */
#ifndef RG_NR_TEXREP_H
#define RG_NR_TEXREP_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "gpu.h"   /* gs_mem_rect (via gs.h / nr_gs.h) */

#ifdef __cplusplus
extern "C" {
#endif

enum { NR_REP_MAX_LEVELS = 14 };

/* A loaded replacement: RGBA8 (GS alpha: 0x80 = opaque, as the dumps), level 0 = w x h, then the
 * mip chain down to 1x1 in px at off[i] (lw[i] x lh[i] texels each). */
typedef struct NrRepImg {
    uint64_t id;          /* unique per load (the backends' cache key) */
    int w, h, levels;
    const uint32_t *px;
    uint32_t off[NR_REP_MAX_LEVELS];
    uint16_t lw[NR_REP_MAX_LEVELS], lh[NR_REP_MAX_LEVELS];
    size_t bytes;
    /* emissive map (lanes rt8 / rt9): `<name>_e.png` beside the replacement, loaded the same way
     * (same size rules); NULL when the pack has none.  The Vulkan backend's ray-traced emissive
     * lighting reads it (nr_emi.h "HD packs", docs/RAYTRACING.md "RT9"). */
    const struct NrRepImg *emissive;
    /* (rt9) the texture's name (PCSX2's, docs/TEXTURES.md "Names"), the emissive table's key
     * `pcsx2:<name>` */
    char name[48];
} NrRepImg;

/* the modes (graphics.texture_dump: 1 = without movie frames, 2 = with them / texture_replace);
 * returns 1 when the shadow was just allocated (the caller then fills it from the mirror:
 * nr_texrep_load_all).  Live: replacement off frees every loaded image (the caller drops the
 * backend copies: GpuBackend::nr_rep_clear); both off frees the CPU copy of local memory */
int nr_texrep_config(int dump, int replace);
int nr_texrep_on(void);
/* host->local transfer (the bytes as the GS receives them) */
void nr_texrep_xfer(const gs_mem_rect *rc, const uint8_t *data, uint32_t npx);
/* a GPU write into local memory: the blocks of rectangle d of (bp, bw, psm) are no longer known */
void nr_texrep_gpu_write(uint32_t bp, uint32_t bw, int psm, int x0, int y0, int x1, int y1, int copy);
/* a local->local copy (TRXDIR 2) done on the CPU copy too when every source block is known
 * (returns 1; 0: not done, the caller marks the destination unknown: nr_texrep_gpu_write).  The
 * game builds some textures this way (a face's blink frames); PCSX2 names them from the result */
int nr_texrep_copy(const gs_mem_rect *s, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t dx, uint32_t dy);
/* the device's mirror read for blocks the GPU wrote: fn fills vram at the (offset, length) byte
 * runs, returns 1 when done (nr_dev.cpp: mem_flush + GpuBackend::mirror_download).  A texture
 * over such blocks is then named from the GPU's bytes ($RG_TEXREP_READBACK=0: not named) */
void nr_texrep_set_reader(int (*fn)(void *user, const uint32_t *runs, int nruns, uint8_t *vram), void *user);
/* the whole of local memory known again (a save-state load, the snapshot at enable) */
void nr_texrep_load_all(const uint8_t *vram);
/* a native draw's decoded texture: key = its content key (dec_key[0..7]), tex0 / texa / clamp the
 * GS registers, clut = the 512 CLUT cells (NULL / clut_known 0: the CLUT is not CPU-known).
 * Returns the replacement image to draw with, or NULL (draw the decoded texture). */
const NrRepImg *nr_texrep_draw(const uint32_t key[8], uint64_t tex0, uint64_t texa, const uint16_t *clut,
                               int clut_known);
/* the image is still loaded (a recorded draw replayed after the replacement setting went off, or
 * after an eviction, may point at a freed one: the backend then draws the decoded texture) */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
int nr_texrep_valid(const NrRepImg *im);
/* staged uploads (backends): bytes a backend uploads per frame ($RG_TEXREP_UPLOAD_MB, default
 * 2 MB: the worst frame 11-14 ms -> 1.4-2.2 ms, out/hdtex2/REPORT.md; 0 = each image whole in its
 * first draw); an image is drawn once all its levels are up */
size_t nr_texrep_upload_budget(void);
/* a backend's uploads of one frame (CPU ms in the upload calls, bytes), for the exit line */
void nr_texrep_upload(double ms, size_t bytes);
/* the field number in GS-stream order (nr_gs_fields): a backend's budget is per field */
uint32_t nr_texrep_frame(void);
/* (rt9) the name of a decoded texture by its content key (dec_key) once named (dump or replace
 * mode): 1 and the name in out, else 0.  The emissive census records name <-> content key pairs
 * with it (tools/rt/emi_table.py --names: table rows for HD packs) */
int nr_texrep_key_name(const uint32_t key[8], char *out, size_t n);
#else   /* (the backends are also built into rg_gpu, which has no nr_texrep.cpp: nothing is replaced there) */
static inline int nr_texrep_valid(const NrRepImg *im) { (void)im; return 0; }
static inline size_t nr_texrep_upload_budget(void) { return 0; }
static inline void nr_texrep_upload(double ms, size_t bytes) { (void)ms; (void)bytes; }
static inline uint32_t nr_texrep_frame(void) { return 0; }
static inline int nr_texrep_key_name(const uint32_t key[8], char *out, size_t n) { (void)key; (void)out; (void)n; return 0; }
#endif
/* counters for the exit line ("texture replacement: ..."); also stops the loader threads (call
 * it at the renderer's exit whatever the settings are now: nothing happens if never enabled) */
void nr_texrep_stats(FILE *f);
/* test / tools: the name a texture would get (out >= 64 chars) from raw inputs; 0 when it cannot
 * be named (unknown blocks) */
int nr_texrep_name(uint64_t tex0, uint64_t texa, const uint16_t *clut, char *out, size_t n);

#ifdef __cplusplus
}
#endif
#endif
