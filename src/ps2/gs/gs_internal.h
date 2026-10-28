/* SPDX-License-Identifier: CC0-1.0 */
/* Internal helpers shared by the GS model's translation units. */
#ifndef RG_PS2_GS_INTERNAL_H
#define RG_PS2_GS_INTERNAL_H

#include "gs.h"

#define GS_BITS(v, lo, n) ((uint32_t)(((uint64_t)(v) >> (lo)) & ((1ull << (n)) - 1ull)))

static inline int gs_clampi(int v, int lo, int hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

static inline uint32_t gs_rd32(const uint8_t *p)
{
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
           ((uint32_t)p[3] << 24);
}
static inline uint64_t gs_rd64(const uint8_t *p)
{
    return (uint64_t)gs_rd32(p) | ((uint64_t)gs_rd32(p + 4) << 32);
}

/* is the format a 16-bit one (frame/texture/Z)? */
static inline int gs_psm_is16(int psm)
{
    return psm == GS_PSMCT16 || psm == GS_PSMCT16S || psm == GS_PSMZ16 ||
           psm == GS_PSMZ16S;
}

/* --- gs_core.c: the synchronous GIF input (gs_async.c queues the public
 * gs_gif_write / gs_gif_reset onto these) --- */
void gs__gif_write_now(gs_state *gs, int path, const void *qwords, uint32_t nqw);
void gs__gif_reset_now(gs_state *gs);
void gs__async_rescan(gs_state *gs);
void gs__async_events_settle(gs_state *gs);
/* --- gs_census.c (measurement) --- */
extern int gs__feat_on;
extern int gs__fx_on;   /* $RG_NR_FXCENSUS (gs_core.c), -1 until read */
void gs__fx_prim(int type);
void gs__fx_xfer(int dir, int psm);
void gs__fx_clut(int cpsm);
void gs__feat_prim(gs_state *gs, const gs_vertex *v, int nv, int type);
void gs__feat_xfer(int xdir, uint64_t bytes, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t y1);

/* --- gs_mem.c --- */
void gs_xfer_start(gs_state *gs, int xdir);
void gs_xfer_hwreg(gs_state *gs, uint64_t data);
/* the IMAGE words d[0..n) (n a multiple of 8): gs_xfer_hwreg on each */
void gs_xfer_image(gs_state *gs, const uint8_t *d, uint32_t n);
/* end of an IMAGE run: staged transfer data is written (gs_mem.c) */
void gs_xfer_stage_flush(gs_state *gs);
extern int gs_stage_path;   /* GIF path of the IMAGE data being staged */
void gs_xfer_cache_free(gs_state *gs);
void gs_mem_lazy_free(gs_state *gs);   /* lazy transfers: everything pending forgotten (gs_destroy) */
void gs_xfer_end_hook(gs_state *gs); /* renderer hook: transfer over */
/* RGBA8 (R lowest byte) <-> stored colour for a frame/texture format */
uint32_t gs_color_from_stored(int psm, uint32_t raw); /* alpha as stored (CT24: 0) */
uint32_t gs_color_to_stored(int psm, uint32_t rgba);

/* --- gs_tex.c --- */
void gs_tex0_written(gs_state *gs, int ctx);
struct gs_texctx;
typedef struct gs_texctx {
    uint64_t tex0, tex1, clamp, miptbp1, miptbp2, texa;
    int fst;
} gs_texctx;
/* Sample at texel-space coordinates (u,v in level-0 texels, already divided
 * by Q for STQ) with the given LOD; returns RGBA8 (alpha expanded). */
uint32_t gs_tex_sample(const gs_state *gs, const gs_texctx *tc, double u,
                       double v, double lod);
/* LOD per the TEX1 rule for a fragment with the given Q */
double gs_tex_lod(const gs_texctx *tc, double q);

/* --- gs_raster.c --- */
void gs_draw_kick(gs_state *gs, const gs_vertex *v, int nv, int prim_type);

#endif
