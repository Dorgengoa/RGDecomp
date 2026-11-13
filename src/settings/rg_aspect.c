/* SPDX-License-Identifier: CC0-1.0 */
/* Widescreen policy, stages 0 and 1 (rg_aspect.h, docs/WIDESCREEN.md). */
#include "rg_aspect.h"
#include "rg_settings.h"
#include "rg_layout.h"
#include "port/vcall.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int g_ui_layout = RG_UI_LAYOUT_KEEP;   /* graphics.ui_layout (stage 2) */

static int gcd_i(int a, int b)
{
    while (b) { int t = a % b; a = b; b = t; }
    return a;
}

int rg_aspect_resolve(int mode, int win_w, int win_h, int *num, int *den)
{
    int n = 4, d = 3;
    switch (mode) {
    case RG_ASPECT_16_9:  n = 16; d = 9; break;
    case RG_ASPECT_16_10: n = 16; d = 10; break;
    case RG_ASPECT_21_9:  n = 64; d = 27; break;
    case RG_ASPECT_AUTO:
        if (win_w > 0 && win_h > 0 && win_w <= 1 << 15 && win_h <= 1 << 15) {
            n = win_w;
            d = win_h;
            /* within 1% of 4:3 (e.g. 1281x960) counts as 4:3 */
            if ((long long)n * 300 <= (long long)d * 404) { n = 4; d = 3; }
            else if ((long long)n * RG_ASPECT_MAX_DEN > (long long)d * RG_ASPECT_MAX_NUM) {
                n = RG_ASPECT_MAX_NUM; d = RG_ASPECT_MAX_DEN;
            }
        }
        break;
    default: break;
    }
    int g = gcd_i(n, d);
    n /= g;
    d /= g;
    *num = n;
    *den = d;
    return !(n == 4 && d == 3);
}

void rg_aspect_ctl_init(rg_aspect_ctl *c) { c->wrote_wide = 0; }

void rg_aspect_step_ratio(rg_aspect_ctl *c, int num, int den, int movie, int title,
                          int movie_open, rg_aspect_frame *out)
{
    if (num <= 0 || den <= 0 || (long long)num * 3 <= (long long)den * 4) {
        /* Original: the game's own state, untouched (undo our write once) */
        out->game_wide = c->wrote_wide ? 0 : -1;
        c->wrote_wide = 0;
        out->canvas_num = out->content_num = 4;
        out->canvas_den = out->content_den = 3;
        return;
    }
    out->canvas_num = num;
    out->canvas_den = den;
    if (title || (movie_open && movie == RG_MOVIE_ASPECT_KEEP)) {
        /* not WIDE-aware: native 4:3 picture, pillarboxed */
        out->game_wide = 0;
        out->content_num = 4;
        out->content_den = 3;
    } else {
        out->game_wide = 1;
        out->content_num = num;
        out->content_den = den;
    }
    c->wrote_wide = 1;
}

void rg_aspect_step(rg_aspect_ctl *c, int mode, int movie, int title, int movie_open,
                    rg_aspect_frame *out)
{
    int n, d;
    rg_aspect_resolve(mode, 0, 0, &n, &d);
    rg_aspect_step_ratio(c, n, d, movie, title, movie_open, out);
}

void rg_aspect_step_settings(rg_aspect_ctl *c, const rg_settings *s, int title, int movie_open,
                             int win_w, int win_h, rg_aspect_frame *out)
{
    int mode = RG_ASPECT_4_3, movie = RG_MOVIE_ASPECT_KEEP, n, d;
    if (s && rg_settings_find(s, "graphics.aspect") >= 0)
        mode = rg_settings_get_enum(s, "graphics.aspect");
    if (s && rg_settings_find(s, "graphics.movie_aspect") >= 0)
        movie = rg_settings_get_enum(s, "graphics.movie_aspect");
    if (s && rg_settings_find(s, "graphics.ui_layout") >= 0)
        rg_aspect_set_ui_layout(rg_settings_get_enum(s, "graphics.ui_layout"));
    /* graphics.menu_position / menu_margin / revelation_wide (docs/WIDESCREEN.md "Menu position") */
    if (s && rg_settings_find(s, "graphics.revelation_wide") >= 0)
        rg_layout_set_revelation_wide(rg_settings_get_bool(s, "graphics.revelation_wide"));
    if (s && rg_settings_find(s, "graphics.menu_position") >= 0)
        rg_layout_set_menu_position(rg_settings_get_enum(s, "graphics.menu_position") == 0,
                                    rg_settings_find(s, "graphics.menu_margin") >= 0
                                        ? (float)rg_settings_get_int(s, "graphics.menu_margin") / 100.0f : 0.0f);
    /* accessibility (presentation only, docs/SETTINGS.md): the 2D UI scale (rg_layout.h) and
     * the camera shake amount (CameraShakeApply_3056b0 override) */
    if (s && rg_settings_find(s, "accessibility.ui_scale") >= 0)
        rg_layout_set_ui_scale((float)rg_settings_get_int(s, "accessibility.ui_scale") / 100.0f);
    if (s && rg_settings_find(s, "accessibility.camera_shake") >= 0)
        rg_camera_shake_set((float)rg_settings_get_int(s, "accessibility.camera_shake") / 100.0f);
    /* gameplay.text_speed (a gameplay option, off in Original): MesWinAdvanceTypeout_275f00 */
    if (s && rg_settings_find(s, "gameplay.text_speed") >= 0)
        rg_text_speed_set(rg_settings_get_enum(s, "gameplay.text_speed"));
    /* gameplay.frog_log_order (display only, off in Original): WeaponCombineLogCollect_3e9270 */
    if (s && rg_settings_find(s, "gameplay.frog_log_order") >= 0)
        rg_froglog_order_set(rg_settings_get_enum(s, "gameplay.frog_log_order"));
    rg_aspect_resolve(mode, win_w, win_h, &n, &d);
    /* stage 2 showed a full-screen menu whole at 4:3 like the title; stage 3 (no aspect
     * switch for menus) keeps the canvas wide and lays the menu out as one centred 4:3
     * element (rg_layout.h): the switch is left only behind RG_LAYOUT_MENU_PILLARBOX=1 */
    if (g_ui_layout == RG_UI_LAYOUT_KEEP && rg_layout_wants_pillarbox())
        title = 1;
    /* (cardwide 2026-11-12) the title phase's memory-card screens are menus like the in-game
     * save screen: wide (laid out by stage 3) once their background is fully up; the title
     * itself stays 4:3.  RG_LAYOUT_CARD_WIDE=0: pillarboxed as before */
    else if (title && g_ui_layout == RG_UI_LAYOUT_KEEP && rg_layout_card_screen())
        title = 0;
    rg_aspect_step_ratio(c, n, d, movie, title, movie_open, out);
}

float rg_aspect_d_for(int num, int den)
{
    if (num <= 0 || den <= 0) return 0.75f;
    return (float)den / (float)num;
}

float rg_hud_xscale_for(int num, int den)
{
    if (num <= 0 || den <= 0) return 1.0f;
    return (float)(4 * den) / (float)(3 * num);
}

/* Retail WIDE constants until our policy owns the flag. */
static float g_cur_d = 0.5625f;
static float g_cur_s = 0.75f;
static int g_frames;

void rg_aspect_set_ui_layout(int v) { g_ui_layout = v; }

/* RG_ASPECT_LOG=file: one line per change of what is presented (flag write, canvas,
 * content shape): the "no aspect switch" check of tools/wide/stage3shots.py */
static void aspect_log(const rg_aspect_frame *f)
{
    static FILE *log;
    static int init, last_w = -2, last_cn, last_cd, last_n, last_d;
    if (!init) {
        const char *p = getenv("RG_ASPECT_LOG");
        init = 1;
        if (p && *p)
            log = fopen(p, "w");
    }
    if (!log || !f)
        return;
    int w = f->game_wide == -1 ? last_w : f->game_wide;
    if (w == last_w && f->canvas_num == last_cn && f->canvas_den == last_cd &&
        f->content_num == last_n && f->content_den == last_d)
        return;
    last_w = w;
    last_cn = f->canvas_num;
    last_cd = f->canvas_den;
    last_n = f->content_num;
    last_d = f->content_den;
    fprintf(log, "%d wide=%d canvas=%d:%d content=%d:%d menu=%d\n", g_frames, w, f->canvas_num,
            f->canvas_den, f->content_num, f->content_den, rg_layout_menu_screen());
    fflush(log);
}

void rg_aspect_set_current(const rg_aspect_frame *f)
{
    float layout = 1.0f;
    if (f && f->game_wide == 1) {
        g_cur_d = rg_aspect_d_for(f->content_num, f->content_den);
        g_cur_s = rg_hud_xscale_for(f->content_num, f->content_den);
        if (g_ui_layout == RG_UI_LAYOUT_KEEP)
            layout = g_cur_s;
    } else {
        g_cur_d = 0.5625f;
        g_cur_s = 0.75f;
    }
    /* stage 2: active only while our policy owns the WIDE flag (never at 4:3); full-screen
     * menu detection on any wide canvas */
    rg_layout_set_detect(f && g_ui_layout == RG_UI_LAYOUT_KEEP &&
                         (long long)f->canvas_num * 3 > (long long)f->canvas_den * 4);
    rg_layout_set_frame(layout, ++g_frames);
    aspect_log(f);
}

static int g_froglog_sorted;
void rg_froglog_order_set(int v) { g_froglog_sorted = v == 1; }
/* called when the Frog Log builds a list; RG_FROG_LOG_ORDER=0/1 overrides the setting (tests) */
int rg_froglog_sorted(void)
{
    static int env = -1;
    if (env < 0) {
        const char *e = getenv("RG_FROG_LOG_ORDER");
        env = e && (*e == '0' || *e == '1') ? *e - '0' : 2;
    }
    return env < 2 ? env : g_froglog_sorted;
}

static float g_text_mult = 1.0f;
void rg_text_speed_set(int v) { g_text_mult = v == 1 ? 2.0f : v == 2 ? 4096.0f : 1.0f; }
/* called on every type-out step of a message window; RG_TEXT_LOG=1 counts them */
float rg_text_speed_mult(void)
{
    static int log = -1;
    static unsigned long n;
    if (log < 0) {
        const char *e = getenv("RG_TEXT_LOG");
        log = e && *e == '1';
    }
    if (log && (++n <= 3 || n % 500 == 0))
        fprintf(stderr, "rg-text: frame %d type-out step (%lu), x%.0f\n", g_frames, n, g_text_mult);
    return g_text_mult;
}

static float g_shake = 1.0f;
float rg_camera_shake_k(void) { return g_shake; }
/* event-scene shakes (EventCameraCmdShake_254f90 / ShakeAt_254df0 overrides): the offset a
 * shake step added to the event camera's eye / look-at, summed until the next draw task takes
 * it (TaskUpdateDrawInfo_2f6ff0 override).  Host state only. */
static float g_ev_eye[3], g_ev_at[3];
static int g_ev_n;
void rg_event_shake_note(const void *eye, const void *eye0, const void *at, const void *at0)
{
    static int log = -1;
    static unsigned long n;
    const float *e = (const float *)eye, *e0 = (const float *)eye0, *t = (const float *)at, *t0 = (const float *)at0;
    for (int i = 0; i < 3; i++) {
        g_ev_eye[i] += e[i] - e0[i];
        g_ev_at[i] += t[i] - t0[i];
    }
    g_ev_n++;
    if (log < 0) {
        const char *v = getenv("RG_SHAKE_LOG");
        log = v && *v == '1';
    }
    if (log && (++n <= 3 || n % 100 == 0))
        fprintf(stderr, "rg-shake: frame %d event shake step (%lu steps), scale %.2f\n", g_frames, n, g_shake);
}
int rg_event_shake_take(float eye[3], float at[3])
{
    int had = g_ev_n > 0;
    for (int i = 0; i < 3; i++) {
        eye[i] = g_ev_eye[i];
        at[i] = g_ev_at[i];
        g_ev_eye[i] = g_ev_at[i] = 0.0f;
    }
    g_ev_n = 0;
    return had;
}
void rg_event_shake_unscale_draw_copy(void *cam)
{
    float e3[3], a3[3];
    if (rg_event_shake_take(e3, a3) && rg_camera_shake_k() < 1.0f) {
        float k = rg_camera_shake_k() - 1.0f;   /* -(1 - k) */
        float *e = (float *)((unsigned char *)cam + 0x50), *t = (float *)((unsigned char *)cam + 0x60);
        for (int i = 0; i < 3; i++) {
            e[i] += e3[i] * k;
            t[i] += a3[i] * k;
        }
        /* slot 0x40 through the vptr at +0xC0 (port/vcall.h VCALL0, spelled warning-free for C):
         * recompute from eye / look-at (CameraShakeApply_3056b0's f40) */
        vc_u32 slot = *(const vc_u32 *)(uintptr_t)(VC_VPTR(cam, 0xC0) + 0x40u);
        ((void (VC_CC *)(void *))(uintptr_t)slot)(cam);
    }
}
void rg_camera_shake_set(float k) { g_shake = k >= 0.0f && k <= 1.0f ? k : 1.0f; }
/* called by the override on every drawn frame with a shake running; RG_SHAKE_LOG=1 counts
 * them on stderr (the run-hash proof needs a run that shakes) */
float rg_camera_shake_scale(void)
{
    static int log = -1;
    static unsigned long n;
    if (log < 0) {
        const char *e = getenv("RG_SHAKE_LOG");
        log = e && *e == '1';
    }
    if (log && (++n <= 3 || n % 100 == 0))
        fprintf(stderr, "rg-shake: frame %d shaking (%lu frames), scale %.2f\n", g_frames, n, g_shake);
    return g_shake;
}

float rg_aspect_d(void) { return g_cur_d; }
/* stage 2: while the layout transform is active it squeezes the HUD itself, so the
 * WIDE-aware HUD sites draw at full width (1.0); world-anchored sites (lens flare,
 * door cursors, lock-on slots, the compass) suppress the layout and keep narrowing
 * themselves with rg_hud_xscale_world() */
float rg_hud_xscale(void) { return rg_layout_active() ? 1.0f : g_cur_s; }
float rg_hud_xscale_world(void) { return g_cur_s; }
