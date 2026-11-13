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

/* per field (between fields): s < 1 activates, s >= 1 deactivates (unless a UI scale is set) */
void rg_layout_set_frame(float s, int field);
/* the X squeeze runs (s < 1): the WIDE-aware HUD sites then draw at full width */
int rg_layout_active(void);
/* accessibility.ui_scale (docs/WIDESCREEN.md "UI scale"): u != 1 (0.5 .. 2) also activates
 * the transform, on any canvas (4:3 included), before rg_layout_set_frame.  Every laid-out
 * group (in-field windows, message text, the HUD) is scaled by u in X (times s) and Y about
 * its anchor (x: left / centre / right edge, y: top / middle / bottom), limited per group so
 * it stays on the screen; world-anchored text (rg_layout_about_begin) about its own point;
 * full-screen menus (stage 3) keep their size.  1 = off: nothing changes (Original). */
void rg_layout_set_ui_scale(float u);
/* graphics.menu_position / menu_margin (docs/WIDESCREEN.md "Menu position"): the full-screen
 * menus' 4:3 block flush left (left != 0; margin = fraction of the canvas width in, at most
 * centred) or centred (0: the stage 3 layout, Original).  $RG_MENU_LEFT overrides it. */
void rg_layout_set_menu_position(int left, float margin);
/* a menu task that stays centred whatever the menu position (help sheets, battle results) */
void rg_layout_menu_centred_task(const void *fn);
/* 3D on menu screens (docs/WIDESCREEN.md "Menu 3D models"): a camera view packet (VU qw 0-19,
 * CameraWriteViewPacket_148740 override) written while a stage 3 menu task runs with the menu
 * block off the centre (menu_position left) gets its screen-centre X (screen matrix ox, GS
 * pixels) moved like the task's 2D: the menu's models stay with their panels.  Untouched when
 * the layout is inactive (4:3, Original), for other tasks, centred menus, RG_LAYOUT_MENU_3D=0.
 * rg_layout_menu_view_x: the ox such a packet gets (ox itself when untouched). */
void rg_layout_view_packet(void *pkt);
float rg_layout_menu_view_x(float ox);
/* the X shift (GS pixels) the running task's last view packet got this frame, else 0: the
 * offscreen composite (ModelDrawOffscreenCompositeMaybe_16aac0 override) moves the rectangle it
 * clears and copies the model back from (centre-relative boxes) by it */
float rg_layout_view_dx(void);
/* Wide content in a menu (the Revelation board's cells, $RG_REV_WIDE >= 1): menu sprites drawn
 * between begin / end past the 4:3 screen's right edge are shown up to the canvas's right edge
 * instead of hidden.  rg_layout_wide_mode(): $RG_REV_WIDE if set (0 off, 1 cells, 2 cells +
 * the board's scroll window), else graphics.revelation_wide (2 / 0); rg_layout_wide_extra(): 4:3-frame pixels visible right of the 4:3
 * screen now (0 unless mode 2 and the layout is active). */
void rg_layout_wide_begin(void);
void rg_layout_wide_end(void);
int rg_layout_wide_mode(void);
/* graphics.revelation_wide: on = mode 2 unless $RG_REV_WIDE is set (0 = off) */
void rg_layout_set_revelation_wide(int on);
int rg_layout_wide_extra(void);
float rg_layout_ui_scale(void);
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
/* (cardwide 2026-11-12, docs/WIDESCREEN.md "Memory-card screens") the title phase's
 * memory-card screens (load: slot select, file list, questions): the TitleLoadDrawBgCb_4ed9e0
 * override brackets their scrolling background (alpha = its opacity, 0..1).  Its task is a
 * menu task (laid out as one 4:3 block like the in-game save screen); rg_layout_card_screen:
 * that background is up in the last drawn frame on a wide canvas (it reached full opacity, and
 * it stays up while it fades out until it is gone) -> the aspect policy shows the screen wide
 * instead of pillarboxed like the title.
 * RG_LAYOUT_CARD_WIDE=0: off (pillarboxed, as before). */
void rg_layout_card_bg_begin(float alpha);
void rg_layout_card_bg_end(void);
int rg_layout_card_screen(void);
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
/* the same about an explicit centre (screen pixels from the top-left) with explicit X / Y
 * factors (no squeeze added): the world-anchored HP gauges under the UI scale
 * (HpGaugeDrawBar* overrides, tools/p6/gauge_about_override.py).  Ended by about_end. */
void rg_layout_about_xy_begin(float ax_px, float ay_px, float kx, float ky);
void rg_layout_about_end(void);
/* an element's extent known ahead of its packets (message windows: MesWinDraw_270cb0 override,
 * the text block [x, x + the page's widest line] in screen pixels): while set, the packets'
 * rectangles are widened to it for the anchor and the grouping, so a line of text being typed
 * out from the left of a centred block is centred from its first glyph (docs/WIDESCREEN.md
 * "Anchor snaps (2026-10-31)").  Not nested. */
void rg_layout_elem_begin(float x0_px, float x1_px);
void rg_layout_elem_end(void);
/* follow another task's layout (the battle menu's panel and cursor over the party HUD:
 * normal_BtlChgMenuDraw_4f9f80 override, docs/WIDESCREEN.md "Battle menu cursor"): every packet
 * drawn between begin and end takes one anchor, decided at the end of the last such bracket:
 * the anchor that the given task's lowest packet overlapping the bracket's packets in X, at most
 * a quarter of the screen height below them, got in the last drawn frame (the HUD slot under
 * the panel); none when the bracket's packets together are wider than 0.62 of the screen or
 * nothing of that task is under them (then: as usual).  RG_LAYOUT_FOLLOW=0: off (as before).
 * Not nested; one bracket a frame. */
void rg_layout_follow_begin(const void *task_fn);
void rg_layout_follow_end(void);
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
/* UI scale: the largest k in [1, u] (u when u <= 1) that keeps the group [x0, x1] x [y0, y1]
 * (anchors ax / ay, X squeeze s) inside the screen [left, left + w] x [top, top + h]; 1 when
 * it is already past an edge unscaled */
float rg_layout_fit_scale(float u, int ax, int ay, float x0, float x1, float y0, float y1,
                          float left, float w, float top, float h, float s);

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
    unsigned packets, groups, moved, full, ztest, suppressed, verts, about, menu, capture, strips, inherited;
    unsigned followed;   /* rg_layout_follow_begin: packets that took the followed task's anchor */
} rg_layout_stats;
void rg_layout_get_stats(rg_layout_stats *st);

#ifdef __cplusplus
}
#endif
#endif
