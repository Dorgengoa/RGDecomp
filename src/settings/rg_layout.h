/* SPDX-License-Identifier: CC0-1.0 */
/* Widescreen stage 2: the 2D layout transform (docs/WIDESCREEN.md "Stage 2").
 *
 * On a wide canvas the game's 512x448 frame is shown anamorphically, so every 2D
 * element the game does not narrow itself is stretched by A / (4/3).  Stage 2
 * squeezes those elements back to 4:3 proportions (x scale s = rg_hud_xscale_for
 * the content shape, the same s the stage 1 WIDE sites use) about an anchor, so
 * corner HUD stays in its corner and centred menus stay centred:
 *
 *   x' = a + (x - a) * s,  a = left edge | screen centre | right edge.
 *
 * Where: at the game's own 2D packet builder.  Every EE-built 2D primitive goes
 * through a GsPkt (GsPktOpen .. GsPktClose, game/src/main/gs); the GsPktClose
 * override hands the finished packet to rg_layout_packet, which records where
 * its vertex X words (XYZ2 / XYZ3 / XYZF2 / XYZF3, A+D, PACKED and REGLIST) and
 * scissor rectangles are.  Packets are grouped by the game task that drew them
 * (TaskTableRun_1f5340 override: rg_layout_task_begin / _end) and, inside a task,
 * by overlap; each group gets one anchor from its bounding box, so a window and
 * its text move together.  Nothing is rewritten for:
 *   - packets drawn with the Z test on (3D effects, projected world markers),
 *   - packets wider than RG_LAYOUT_FULL of the screen (fades, backgrounds,
 *     full-screen captures: they keep covering the screen),
 *   - packets drawn while a WIDE-aware stage 1 site has suppressed the layout
 *     (rg_layout_suppress: they narrow themselves about their own position).
 * 3D (VU1 microcode output) never passes through a GsPkt and is untouched.
 *
 * Inactive (every hook returns at once, no memory written) unless our aspect
 * policy owns the WIDE flag on a canvas wider than 4:3 and graphics.ui_layout is
 * "keep" (rg_layout_set_frame, from rg_aspect_set_current).  4:3 / the Original
 * preset never activate it.
 *
 * Pure C, no game symbols: the packet layout offsets are passed as plain memory. */
#ifndef RG_LAYOUT_H
#define RG_LAYOUT_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RG_LAYOUT_FULL 0.90f   /* group wider than this fraction of the screen: untouched */
#define RG_LAYOUT_FRAME_H 448.0f /* frame height in pixels (covering-piece test) */

enum { RG_ANCHOR_NONE = 0, RG_ANCHOR_LEFT, RG_ANCHOR_CENTER, RG_ANCHOR_RIGHT };

/* graphics.ui_layout values */
enum { RG_UI_LAYOUT_KEEP = 0, RG_UI_LAYOUT_STRETCH = 1 };

/* per field (between fields): s < 1 activates, s >= 1 deactivates */
void rg_layout_set_frame(float s, int field);
int rg_layout_active(void);
/* full-screen menus (an indexed-colour UI background covering the screen, drawn by a
 * game task): detection runs on any wide canvas.  Stage 3 (USER 2026-10-19, no aspect
 * switch for menus): the canvas, the WIDE flag and the 3D stay wide; everything the
 * menu's task draws (its indexed-colour background pieces included) is laid out as ONE
 * 4:3 element about the screen centre, so the background's holes stay on their panels
 * and the live wide scene shows through them and at the sides.  Fades, dims and scene
 * captures (non-indexed covering packets) keep covering the whole canvas.
 * rg_layout_menu_screen: a full-screen menu is up (the last drawn frame);
 * rg_layout_wants_pillarbox: stage 2's whole-screen 4:3 pillarbox for such screens, now
 * only with RG_LAYOUT_MENU_PILLARBOX=1 (debug, before/after comparisons). */
void rg_layout_set_detect(int on);
int rg_layout_menu_screen(void);
int rg_layout_wants_pillarbox(void);
float rg_layout_scale(void);

/* the hooks (game overrides) */
void rg_layout_task_begin(const void *fn);
void rg_layout_task_end(void);
/* returns 1 when the packet's X was squeezed (s != 1): the GsPktClose override tells the
 * native renderer (nr_im_note_xscaled) so upscaled point sprites keep every texel column */
int rg_layout_packet(void *pkt, const void *caller);
void rg_layout_suppress(int on);       /* nesting counter */
int rg_layout_suppressed(void);
/* world-anchored text (NPC name labels, damage numbers: ScreenMarkerDrawAll_31af50,
 * DamagePopupDraw_2d3240 overrides): while set, every packet's vertex X is squeezed by s
 * about the point ax (x' = ax + (x - ax) * s), so the string keeps its projected position
 * and gets 4:3 glyph widths.  screen_px: ax in pixels from the screen's left edge, else
 * 12.4 GS units (offset included).  Wins over suppress / the Z test; not nested. */
void rg_layout_about_begin(float ax, int screen_px);
void rg_layout_about_end(void);
/* stage 3: the main menu's portrait-circle copy of the field frame
 * (MenuCaptureScreenTex_298810 override): resampled from the wide frame so it holds what
 * the 4:3 copy holds.  src = the frame download at row 106 (512 RGBA32 pixels a row),
 * dst = the 256x256 RGBA32 texture.  0 = not active (the game's own copy runs). */
int rg_layout_capture_wide(const uint8_t *src, uint8_t *dst);

/* ---- pure helpers (tests) ---- */
/* anchor of a group bbox [x0, x1] on a screen [left, left + width] (any units) */
int rg_layout_anchor(float x0, float x1, float left, float width);
/* the same for a cluster of elements (as wide as the screen: centre, kept together) */
int rg_layout_cluster_anchor(float x0, float x1, float left, float width);
/* transformed coordinate */
float rg_layout_map(float x, int anchor, float left, float width, float s);

/* A GIF-tagged packet scan: every vertex X (u16 at *x) and scissor X pair.
 * buf points at the first GIF tag, qwc qwords long.  Returns the number of X
 * fields found (also when out == NULL); out receives pointers (max n). */
typedef struct rg_layout_xref {
    uint16_t *x;     /* vertex X (12.4 GS units, offset included) */
    uint16_t *y;
    void *tc;        /* vertex: its texture coordinate (the UV / ST written before it), or NULL */
    uint8_t tck;     /* 0 none, 1 UV (u16 U, 14 bits, 10.4), 2 ST (float S) */
    uint8_t prim;    /* vertex: primitive type of the last PRIM (6 sprite), 0xFF unknown */
    uint8_t ad;      /* vertex: written as A+D (register number at x + 8, tc + 8) */
    uint16_t vix;    /* vertex: index since that PRIM */
    uint8_t kind;    /* 0 vertex, 1 scissor x0/x1 (11 bits, window pixels) */
    uint8_t shift;   /* scissor: bit position of the field in a u64 */
    uint64_t *sc;    /* scissor qword */
    uint8_t *col;    /* vertex: the A+D RGBAQ qword written before it, or NULL */
} rg_layout_xref;
int rg_layout_scan_gif(uint8_t *buf, int qwc, rg_layout_xref *out, int max);

/* counters for logs / tests */
typedef struct rg_layout_stats {
    unsigned packets, groups, moved, full, ztest, suppressed, verts, about, menu, capture, strips;
} rg_layout_stats;
void rg_layout_get_stats(rg_layout_stats *st);

#ifdef __cplusplus
}
#endif
#endif
