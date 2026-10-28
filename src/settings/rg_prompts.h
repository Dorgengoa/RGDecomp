/* SPDX-License-Identifier: CC0-1.0 */
/* Button prompts per device: the gaiji2 texture swap (docs/PROMPTS.md).
 *
 * Pure C, no SDL and no game state.  The game keeps `gaiji2.img` (IM3 ->
 * TIM2, PSMT8 256x256, swizzled pixels, CSM1 CLUT) in the static buffer
 * D_004C3180; every gaiji draw (tagged message text, the page icon / choice
 * arrow, the insect-cage hint) samples that one texture.  This module
 *
 *   - validates the buffer's layout (rg_gaiji_layout),
 *   - builds the per-style image from the game's own original bytes, with the
 *     8 button rects redrawn procedurally exactly like tools/assets/gaiji.py
 *     `build` (same shapes, stroke font, colours, 4x4 supersampling, palette
 *     quantisation into the slots unused outside the rects), so it never ships
 *     game art and never needs a file next to the exe (rg_gaiji_build),
 *   - and decides, field by field, what to copy into the buffer
 *     (rg_prompts_step): nothing while the wanted style is the one in the
 *     buffer, so the PlayStation style (the Original preset, every scripted
 *     run) only ever READS the buffer.  A game reload of the buffer (a font
 *     pack loaded again) is detected by content and re-captured as the new
 *     original.
 *
 * Only the pixels and the CLUT change (0x10400 bytes at TIM2 + 0x40); the
 * headers, the texture handle and the name-table entry stay, so TEX0 and
 * every fixed-id texture load are unaffected.  Pixels outside the 8 rects
 * keep their exact index bytes.
 */
#ifndef RG_PROMPTS_H
#define RG_PROMPTS_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Styles: the same order as rg_prompt_style (src/host/rg_input.h). */
enum { RG_GAIJI_PLAYSTATION = 0, RG_GAIJI_XBOX, RG_GAIJI_NINTENDO, RG_GAIJI_KEYBOARD,
       RG_GAIJI_STYLES };

/* The 8 button glyphs, in this order everywhere (labels, rects). */
enum { RG_GAIJI_L2 = 0, RG_GAIJI_L1, RG_GAIJI_R1, RG_GAIJI_R2,
       RG_GAIJI_CIRCLE, RG_GAIJI_TRIANGLE, RG_GAIJI_SQUARE, RG_GAIJI_CROSS,
       RG_GAIJI_BUTTONS };

#define RG_GAIJI_IMG_MAX 0x10800u    /* GaijiLoadImage_2705a0's buffer cap */
#define RG_GAIJI_W 256
#define RG_GAIJI_H 256
#define RG_GAIJI_SWAP_BYTES (RG_GAIJI_W * RG_GAIJI_H + 1024)   /* pixels + CLUT */

typedef struct rg_gaiji_rect { uint16_t code; int16_t u, v, w, h; } rg_gaiji_rect;
/* The button rects of the US atlas (D_0044E680 records FD02..FD09). */
extern const rg_gaiji_rect rg_gaiji_button_rects[RG_GAIJI_BUTTONS];
/* The input action that drives each button (docs/INPUT.md ids). */
extern const char *const rg_gaiji_button_action[RG_GAIJI_BUTTONS];

typedef struct rg_gaiji_layout {
    size_t pixels;   /* offset of the swizzled 256x256 index bytes */
    size_t clut;     /* offset of the 256 x RGBA CLUT (= pixels + 0x10000) */
    size_t end;      /* end of the TIM2 picture */
} rg_gaiji_layout;

/* 0 when buf (n bytes) holds a gaiji2-shaped IM3: one TIM2 picture, PSMT8
 * 256x256, 256-colour 32-bit CLUT, everything inside n.  -1 otherwise. */
int rg_gaiji_layout_of(const uint8_t *buf, size_t n, rg_gaiji_layout *L);

/* The keyboard label for a binding text: "key:Space" -> "SPC", "key:Left
 * Shift" -> "SHF", arrows -> codes 1..4 (up, down, left, right), "key:Keypad
 * 8" -> "K8", others upper-cased and cut to 4 characters (gaiji.py
 * key_label).  "mouse:left|middle|right|x1|x2" -> "" and *mouse = 1..5
 * (SDL button numbers 1 left, 2 middle, 3 right, 4 x1, 5 x2).  NULL or ""
 * (unbound) -> "-".  Returns out. */
const char *rg_gaiji_key_label(const char *binding, char *out, size_t cap, int *mouse);

/* Builds `style`'s swap region (RG_GAIJI_SWAP_BYTES: swizzled pixels then the
 * CSM1 CLUT, ready to copy over buf + L.pixels) from the original region.
 * keys: for KEYBOARD, the first key/mouse binding text of each button's
 * action (RG_GAIJI_BUTTONS entries, NULL = unbound); NULL = gaiji.py's
 * defaults.  PLAYSTATION copies the original.  Returns 0, or -1 (bad style,
 * or an original whose palette is not PS2-shaped). */
int rg_gaiji_build(const uint8_t *orig_region, int style, const char *const *keys,
                   uint8_t *out_region);

/* Decode a swap region to 256x256 RGBA8 (alpha = min(255, 2a)): review aid
 * and tests. */
void rg_gaiji_region_rgba(const uint8_t *region, uint8_t *rgba /* 256*256*4 */);

/* ------------------------------------------------------------ the runtime switch */
typedef struct rg_prompts_ctl {
    uint8_t *orig;                    /* the game's own region (captured) */
    uint8_t *img[RG_GAIJI_STYLES];    /* built regions (lazily) */
    uint32_t keys_hash;               /* bindings the keyboard image was built with */
    int have_orig;
    int cur;                          /* the style now in the buffer */
    unsigned writes;                  /* buffer writes so far (diagnostics) */
    unsigned captures;                /* originals captured (game loads seen) */
} rg_prompts_ctl;

void rg_prompts_init(rg_prompts_ctl *c);
void rg_prompts_free(rg_prompts_ctl *c);

/* One step, between fields (no guest code running).  buf/cap: the game's
 * buffer.  wanted: the style to show.  keys: as rg_gaiji_build.
 *   - an invalid buffer (not loaded yet) -> 0, nothing touched;
 *   - the buffer holds neither the captured original nor what was last
 *     written -> the game (re)loaded it: captured as the new original,
 *     current style = PLAYSTATION;
 *   - wanted == current (and, for KEYBOARD, the same bindings) -> 0;
 *   - otherwise the wanted region is copied in -> 1.
 * PLAYSTATION wanted with the original in the buffer therefore never writes. */
int rg_prompts_step(rg_prompts_ctl *c, uint8_t *buf, size_t cap, int wanted,
                    const char *const *keys);

#ifdef __cplusplus
}
#endif
#endif
