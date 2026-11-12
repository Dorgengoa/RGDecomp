/* SPDX-License-Identifier: CC0-1.0 */
/* Screen effects in the native renderer (docs/NATIVE-RENDER.md "Screen effects"): the game's
 * full-screen passes classified from the task that built each immediate packet (nr_im_task,
 * the TaskTableRun_1f5340 override) and the batch's own state, and drawn per the settings
 * graphics.bloom / depth_of_field / motion_blur (original / enhanced / off) and
 * accessibility.flashing (reduced flashing).  Presentation only: nothing the game reads
 * changes (a pass that writes depth keeps writing it, colour masked). */
#ifndef RG_NR_SFX_H
#define RG_NR_SFX_H

#include <stdint.h>
#include <stdio.h>

#include "gs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* stable class ids (census, logs, settings) */
enum {
    NR_SFX_NONE = 0,
    NR_SFX_GLARE,       /* "Draw Glare": GlareFilterDrawMaybe_17a0d0 (bloom: bright-pass, streaks, add) */
    NR_SFX_TBOX_BLOOM,  /* "Draw TBox": BloomExtractBlurMaybe_179360 (the chests' glow) */
    NR_SFX_DOF,         /* "Draw DOF": DofFilterDrawMaybe_17d150 (depth of field) */
    NR_SFX_FOCUS,       /* "Draw Focus": FocusFilterDrawMaybe_17c000 (focus blur) */
    NR_SFX_CBLUR,       /* "Draw Chara Blur": CBlurDrawMaybe_1784e0 (characters' motion blur / afterimage) */
    NR_SFX_TINT,        /* "Draw Gray Scale Filter": ScreenColorFilterMaybe_179c60 (tint / grey) */
    NR_SFX_FADE,        /* "Draw Fade": ScreenFadeBlockDraw_177540 (fades, colour flashes, wipes) */
    NR_SFX_PAUSE,       /* "Draw Pause Filter": TaskDrawPauseFilter_2f5ae0 (pause dimming) */
    NR_SFX_FLASH,       /* a full-screen flat / additive quad drawn by an effect task (hit / magic flashes),
                         * or an untagged (outside any task) full-screen bright additive batch */
    NR_SFX_PARTICLES,   /* an effect task's (or untagged) bright additive batch under half the screen: the
                         * particles / glows whose sum lights large areas (reduced flashing: the frame's
                         * light budget, nr_sfx.c light_limit) */
    NR_SFX_SHADOW,      /* (p6left) "Draw Shadow": TaskDrawShadow_1f7360 -> DrawListEndPlaneShadowPass_146cc0 (the
                         * plane shadows' soft pass: frame mask -> 192x192 buffer, 6 blur sprites, CT16 shuffle,
                         * the darkening sprite; graphics.shadow_res) */
    NR_SFX_COUNT
};
const char *nr_sfx_name(int cls);

/* NR_SFX_HIRES: drawn with gpu_set_im_hires on (nr_sfx_batch set it; the caller turns it off after
 * the submit): the effect chain at the internal resolution */
/* NR_SFX_BOX2 (p6left): as NR_SFX_BOX with the footprint widened to the PS2's blur at the internal
 * resolution (gpu_set_im_box mode 2: depth of field "enhanced") */
/* NR_SFX_FOCUSLP (ptbugs3): the focus blur's composite over the frame, drawn with gpu_set_im_focus on
 * (the value nr_sfx_focus_k() gives; the caller turns it off after the submit): at an internal scale
 * > 1 the frame under it is softened to the PS2's resolution first (nr_dev.cpp focus_prefilter) */
enum { NR_SFX_DRAW = 0, NR_SFX_SKIP = 1, NR_SFX_ZONLY = 2, NR_SFX_BOX = 3, NR_SFX_HIRES = 4, NR_SFX_BOX2 = 5,
       NR_SFX_FOCUSLP = 6 };
int nr_sfx_focus_k(void);   /* gpu_set_im_focus's value: the pre-filter's box in native pixels x 100 */

struct gpu_renderer;
#ifndef RG_GPU_GS_T
#define RG_GPU_GS_T
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
typedef struct nr_gs gpu_gs;
#else
typedef struct gs_state gpu_gs;
#endif
#endif

/* GS thread (nr_im.c flush): one batch of n primitives (3 vertex slots each) about to be drawn
 * with the state in gs; task = the record's task name (NULL: none), frame its EE frame.
 * May change the vertices' colours (reduced flashing).  Returns NR_SFX_*. */
int nr_sfx_batch(struct gpu_renderer *gr, gpu_gs *gs, gs_vertex *v, int n, int type, uint64_t attr,
                 const char *task, uint32_t frame);
void nr_sfx_stats(FILE *f);

#ifdef __cplusplus
}
#endif
#endif
