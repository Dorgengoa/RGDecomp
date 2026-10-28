/* SPDX-License-Identifier: CC0-1.0 */
/* Widescreen policy, stages 0 and 1 (docs/WIDESCREEN.md, docs/WIDESCREEN-AUDIT.md "Plan").
 *
 * graphics.aspect = 4:3 (Original) | 16:9 | 16:10 | 21:9 | auto turns on the
 * game's own hidden WIDE mode (D_00481638 = 1) and shows the 512x448 frame
 * anamorphically on a canvas of that shape.  Stage 0 used the retail constants
 * (projection 0.5625, 2D widths x 0.75: 16:9 only); stage 1 overrides the 13
 * places that read the flag (SceneCameraApplyAspect_1c6a10 and the 12 2D
 * sites, plus the compass, menu model previews and the session-start
 * projection) so they take rg_aspect_d() / rg_hud_xscale() instead, which
 * follow the canvas.  Screens nothing in the game makes WIDE-aware are shown
 * 4:3 pillarboxed inside the canvas, with the flag cleared:
 *   - the title (TITLE overlay loaded),
 *   - movies, when graphics.movie_aspect = keep (the default).
 *
 * The decision part is pure (no SDL, no game symbols): the caller
 * (src/game/rg_game_main.c) feeds it the screen state between fields, writes
 * the flag, hands the aspect pair to the host (rg_host_set_aspect) and
 * publishes the frame with rg_aspect_set_current for the game overrides.
 *
 * 4:3 never writes the flag, except once after a live switch from a wide
 * aspect (to undo it), so the Original preset leaves the game exactly as it
 * was.  When the flag was not written by us (4:3; the game's own key-capture
 * mode can set it), rg_aspect_d() / rg_hud_xscale() return the retail 16:9
 * constants, so the overrides compute exactly what the game did. */
#ifndef RG_ASPECT_H
#define RG_ASPECT_H

#ifdef __cplusplus
extern "C" {
#endif

struct rg_settings;

/* graphics.aspect values (enum order; new values go at the end) */
enum { RG_ASPECT_4_3 = 0, RG_ASPECT_16_9 = 1, RG_ASPECT_16_10 = 2, RG_ASPECT_21_9 = 3,
       RG_ASPECT_AUTO = 4, RG_ASPECT_COUNT };
/* graphics.movie_aspect values (enum order) */
enum { RG_MOVIE_ASPECT_KEEP = 0, RG_MOVIE_ASPECT_STRETCH = 1 };

/* "auto" (the window's shape) is clamped to [4:3, 32:9]; a window narrower
 * than 4:3 (or within 1% of it) is 4:3 (letterboxed, flag untouched). */
#define RG_ASPECT_MAX_NUM 32
#define RG_ASPECT_MAX_DEN 9

typedef struct rg_aspect_ctl {
    int wrote_wide;   /* the game flag was set by us (undo on a switch to 4:3) */
} rg_aspect_ctl;

typedef struct rg_aspect_frame {
    int game_wide;                 /* -1 leave D_00481638 alone, else write 0 / 1 */
    int canvas_num, canvas_den;    /* the shape the window shows (reduced) */
    int content_num, content_den;  /* the frame's shape inside the canvas
                                      (== canvas, or 4:3 pillarboxed) */
} rg_aspect_frame;

/* The canvas shape of a graphics.aspect value (reduced fraction).  auto uses
 * win_w x win_h (<= 0: no window known = 4:3), clamped as above.  21:9 is
 * 64:27 (2560x1080).  Returns 1 when the shape is wider than 4:3. */
int rg_aspect_resolve(int mode, int win_w, int win_h, int *num, int *den);

void rg_aspect_ctl_init(rg_aspect_ctl *c);
/* One decision.  mode / movie: the two settings (RG_ASPECT_*, RG_MOVIE_ASPECT_*);
 * title: the TITLE overlay is loaded; movie_open: the movie service has a movie.
 * auto (no window here) behaves as 4:3: use rg_aspect_step_ratio. */
void rg_aspect_step(rg_aspect_ctl *c, int mode, int movie, int title, int movie_open,
                    rg_aspect_frame *out);
/* The same for a resolved canvas shape num:den (4:3 or narrower = Original). */
void rg_aspect_step_ratio(rg_aspect_ctl *c, int num, int den, int movie, int title,
                          int movie_open, rg_aspect_frame *out);
/* The same, reading graphics.aspect / graphics.movie_aspect from a registry
 * (missing settings = 4:3 / keep); win_w x win_h: the window, for auto. */
void rg_aspect_step_settings(rg_aspect_ctl *c, const struct rg_settings *s, int title,
                             int movie_open, int win_w, int win_h, rg_aspect_frame *out);

/* The values for a frame shape num:den (exact floats: 4:3 -> 0.75 / 1, 16:9 ->
 * 0.5625 / 0.75).  Projection aspect (the game's 0.75 at 4:3): den/num.
 * HUD x scale s = (4/3) / (num/den). */
float rg_aspect_d_for(int num, int den);
float rg_hud_xscale_for(int num, int den);

/* ---- the frame the game is drawing (set between fields by rg-game) ----
 * Read by the stage 1 overrides, only on the game's WIDE branch (flag == 1).
 * While our policy owns the flag (game_wide == 1) they follow the content
 * shape; otherwise they are the retail constants 0.5625 / 0.75. */
void rg_aspect_set_current(const rg_aspect_frame *f);
float rg_aspect_d(void);      /* projection aspect for SceneCameraApplyAspect etc. */
float rg_hud_xscale(void);    /* replaces the WIDE sites' 0.75 width factor */
float rg_hud_xscale_world(void); /* the same for world-anchored 2D (not laid out by stage 2) */
/* stage 2 (rg_layout.h): graphics.ui_layout (RG_UI_LAYOUT_KEEP / _STRETCH); read by
 * rg_aspect_step_settings, applied by rg_aspect_set_current */
void rg_aspect_set_ui_layout(int v);

#ifdef __cplusplus
}
#endif
#endif
