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
/* Prompt slots beyond the 8 gaiji2 buttons (textures with baked prompts, rg_texpatch.h). */
enum { RG_PROMPT_L3 = RG_GAIJI_BUTTONS, RG_PROMPT_R3, RG_PROMPT_START, RG_PROMPT_SELECT,
       RG_PROMPT_SLOTS };
/* The input action of each slot (the first 8 = rg_gaiji_button_action). */
extern const char *const rg_prompt_slot_action[RG_PROMPT_SLOTS];

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

/* Binding text -> physical gamepad button: 0 south, 1 east, 2 west, 3 north, 4 LB, 5 RB,
 * 6 LT (axis:lefttrigger+), 7 RT, 8 LS, 9 RS, 10 start, 11 back, 12..15 d-pad up / down /
 * left / right, 16 guide, 17 another pad input; -1 = none (NULL, "", key:, mouse:). */
int rg_prompt_pad_button(const char *binding);
/* The slot's positional button (the PS2 layout: Cross = south, L2 = LT, START = start). */
int rg_prompt_slot_default_button(int slot);
/* 1 when keys (n slots, NULL = defaults) is what the style shows without bindings: always
 * for NULL; for the pad styles every slot's binding names its positional button.  (The
 * keyboard always draws its keys.) */
int rg_prompt_keys_default(int style, const char *const *keys, int n);

/* One slot's glyph art in `style`, drawn into a w x h RGBA8 buffer (straight alpha, 0 =
 * transparent): shape CELL = the whole glyph (key cap, pad disc or shoulder cap, as in
 * gaiji2), DISC = the same, for a disc already in the art (the caller composites it),
 * TEXT = only the label (white, dark outline: L3 / START words).  keys as rg_gaiji_build
 * (RG_PROMPT_SLOTS entries).  0, or -1 for a bad argument. */
enum { RG_PROMPT_SHAPE_CELL = 0, RG_PROMPT_SHAPE_DISC, RG_PROMPT_SHAPE_TEXT };
int rg_prompt_glyph_rgba(int style, int slot, const char *const *keys, int w, int h, int shape,
                         uint8_t *rgba);

/* Builds `style`'s swap region (RG_GAIJI_SWAP_BYTES: swizzled pixels then the
 * CSM1 CLUT, ready to copy over buf + L.pixels) from the original region.
 * keys: for KEYBOARD, the first key/mouse binding text of each button's
 * action; for the pad styles the first pad / trigger binding (entries indexed
 * by slot, at least RG_GAIJI_BUTTONS of them, NULL entry = unbound); keys NULL
 * = gaiji.py's defaults.  PLAYSTATION copies the original unless a binding
 * moves a slot to another button: that slot then gets the bound button's
 * original art (same-sized rect) or a procedural PlayStation glyph.  Returns 0, or -1 (bad style,
 * or an original whose palette is not PS2-shaped). */
int rg_gaiji_build(const uint8_t *orig_region, int style, const char *const *keys,
                   uint8_t *out_region);

/* KEYBOARD with full key names (gaiji.py --wide): the original rects get the short labels as
 * rg_gaiji_build (fixed-rect draws read them), and a second, wider copy of each glyph (SPACE,
 * ENTER, SHIFT, ...; w = max(original, min(label + 8, original + 12))) is drawn into the largest band of fully
 * transparent rows; wide_rects receives where (the metric records the text paths should use).
 * -1 when the copies do not fit. */
int rg_gaiji_build_wide(const uint8_t *orig_region, const char *const *keys, uint8_t *out_region,
                        rg_gaiji_rect wide_rects[RG_GAIJI_BUTTONS]);

/* Decode a swap region to 256x256 RGBA8 (alpha = min(255, 2a)): review aid
 * and tests. */
void rg_gaiji_region_rgba(const uint8_t *region, uint8_t *rgba /* 256*256*4 */);

/* ------------------------------------------------------------ the runtime switch */
typedef struct rg_prompts_ctl {
    uint8_t *orig;                    /* the game's own region (captured) */
    uint8_t *img[RG_GAIJI_STYLES];    /* built regions (lazily) */
    uint32_t keys_hash;               /* (unused since p6a11y: img_keys) */
    uint32_t img_keys[RG_GAIJI_STYLES]; /* bindings each built image was made with */
    uint32_t cur_keys;                /* bindings of the image in the buffer (0 = defaults) */
    int have_orig;
    int cur;                          /* the style now in the buffer */
    unsigned writes;                  /* buffer writes so far (diagnostics) */
    unsigned captures;                /* originals captured (game loads seen) */
    int wide;                         /* caller: KEYBOARD with full key names (rg_gaiji_build_wide) */
    int img_wide;                     /* img[KEYBOARD] has the wide copies */
    int cur_wide;                     /* the buffer holds the wide keyboard image ... */
    rg_gaiji_rect wide_rects[RG_GAIJI_BUTTONS];   /* ... with its wide copies here */
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
