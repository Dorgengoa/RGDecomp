/* SPDX-License-Identifier: CC0-1.0 */
/* Texture patches at upload time: button prompts baked into game textures and colour-blind
 * friendly markers (lane p6a11y 2026-11-01; docs/PROMPTS.md "Prompts baked into other
 * textures", docs/ACCESSIBILITY.md).
 *
 * Pure C, no SDL and no game state.  The game uploads each texture's pixels and CLUT to the GS
 * as host->local transfers whose bytes are the TIM2 file's bytes (PSMT8 pixels as the GS holds
 * them after an upload as PSMCT32, the CSM1 CLUT as a 16x16 PSMCT32 rectangle).  A target is
 * known by the size and 64-bit FNV-1a hash of those two transfers (never by its art: the table
 * holds hashes, rectangles and colours, no game bytes); its patched image is built at run time
 * from the original bytes the transfers carry:
 *
 *   - prompt sites: rectangles holding a PlayStation glyph are redrawn for the prompt style
 *     and bindings (rg_prompt_glyph_rgba), quantised to the texture's own palette (pixel
 *     transfer only; the CLUT is not changed);
 *   - marker groups: palette entries used only by a colour-coded marker set are recoloured
 *     for the chosen colour-vision deficiency (CLUT transfer only).
 *
 * Threads: rg_texpatch_update runs on the game thread between fields (it draws and builds);
 * rg_texpatch_xfer runs on the GS worker for every host->local transfer.  With the PlayStation
 * style, default bindings and accessibility.colour_blind = off the switch is inactive and
 * rg_texpatch_xfer returns NULL at once (nothing hashed, nothing captured): the Original preset
 * uploads exactly the game's bytes. */
#ifndef RG_TEXPATCH_H
#define RG_TEXPATCH_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum { RG_CB_OFF = 0, RG_CB_PROTAN, RG_CB_DEUTAN, RG_CB_TRITAN, RG_CB_COUNT };

typedef struct rg_tp_site {        /* a baked prompt glyph */
    int16_t x, y, w, h;            /* texel rectangle */
    uint8_t slot;                  /* RG_GAIJI_* / RG_PROMPT_* */
    uint8_t shape;                 /* RG_PROMPT_SHAPE_* */
} rg_tp_site;

typedef struct rg_tp_mark {        /* one member of a colour-coded marker set */
    int16_t x, y, w, h;
    uint8_t group;                 /* index into the target's colours */
} rg_tp_mark;

typedef struct rg_tp_target {
    const char *name;              /* the IM3 entry name (documentation, logs) */
    uint16_t w, h;                 /* texels; PSMT8 (bits 8) or PSMT4 (bits 4) */
    uint8_t bits;
    uint32_t pix_bytes, clut_bytes;
    uint64_t pix_hash, clut_hash;  /* rg_tp_fnv64 of the original transfers */
    const rg_tp_site *sites;
    int nsites;
    const rg_tp_mark *marks;
    int nmarks;
    /* per deficiency (RG_CB_PROTAN..TRITAN) and group: the replacement hue, 0xRRGGBB, or
     * 0xFF000000 = keep the group's colours */
    const uint32_t (*colours)[4];
    int ngroups;
} rg_tp_target;

extern const rg_tp_target rg_tp_targets[];
extern const int rg_tp_ntargets;

uint64_t rg_tp_fnv64(const uint8_t *d, size_t n);

/* Builds target t's patched transfers from the original ones (pix: pix_bytes, clut:
 * clut_bytes).  keys: RG_PROMPT_SLOTS binding texts as rg_gaiji_build (NULL = defaults).
 * *pix_changed / *clut_changed say whether out_pix / out_clut differ from the originals.
 * 0, or -1 (bad arguments). */
int rg_tp_build(const rg_tp_target *t, const uint8_t *pix, const uint8_t *clut, int style,
                const char *const *keys, int cb, uint8_t *out_pix, uint8_t *out_clut,
                int *pix_changed, int *clut_changed);

/* Decodes a target's transfers to w x h RGBA8 (alpha doubled): review aid and tests. */
void rg_tp_rgba(const rg_tp_target *t, const uint8_t *pix, const uint8_t *clut, uint8_t *rgba);

/* ---- the runtime switch ---- */
/* Game thread, between fields: the wanted prompt style (rg_prompts.h styles), the bindings
 * (RG_PROMPT_SLOTS texts, NULL = defaults) and the colour-blind mode.  Builds what changed. */
void rg_texpatch_update(int style, const char *const *keys, int cb);
/* GS worker: one host->local transfer (its bytes).  The replacement bytes (same size) or NULL
 * to upload the game's own.  The pointer stays valid for at least 8 more updates. */
const uint8_t *rg_texpatch_xfer(const uint8_t *data, uint32_t bytes);
/* GS worker, right after rg_texpatch_xfer: the target whose pixel transfer that was (-1: none;
 * active modes only).  rg_texpatch_updates: calls of rg_texpatch_update so far (~ fields).
 * Diagnostics ($RG_TEXPATCH_DRAWLOG, nr_gs.c: which fields draw a target). */
int rg_texpatch_last_match(void);
/* the accessibility.colour_blind mode of the last rg_texpatch_update (RG_CB_*): game-side
 * marker colours that are not textures (overrides MenuStatCompareColors_2a0490.c) */
int rg_texpatch_colour_blind(void);
unsigned rg_texpatch_updates(void);
/* counters: transfers replaced, originals captured, images built */
void rg_texpatch_stats(unsigned *replaced, unsigned *captured, unsigned *built);

#ifdef __cplusplus
}
#endif
#endif
