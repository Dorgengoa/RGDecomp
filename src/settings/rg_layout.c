/* SPDX-License-Identifier: CC0-1.0 */
/* Widescreen stage 2: the 2D layout transform (rg_layout.h, docs/WIDESCREEN.md "Stage 2").
 *
 * Timing: the native renderer decodes each GsPkt packet once, at DrawListEndPrim, right
 * after GsPktClose (docs/NATIVE-RENDER.md "Immediate packets"), so a packet must be laid
 * out when it closes; it cannot wait for the rest of its widget.  The grouping is
 * therefore one frame behind: at the end of each game task the packets it drew this frame
 * (original rectangles) are clustered by 2D overlap and every packet's identity (task,
 * calling function, n-th such packet of the task) is given its cluster's anchor; the next
 * frame applies it as each packet closes.  A packet with no anchor from the last frame (a
 * widget's first frame) uses the anchor of its own rectangle. */
#include "rg_layout.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../native/threads/kapi/ps2k_fpu.h"
#ifdef _WIN32
#include <windows.h>
static uintptr_t image_base(void) { return (uintptr_t)GetModuleHandleA(NULL); }
#else
static uintptr_t image_base(void) { return 0; }
#endif

/* ---- packet object offsets (GsPkt, overrides/src/main/gs/GsPktClose_13f5b0.c) ---- */
#define PK_BASE   0xEC    /* packet base (DMA tag of the first segment) */
#define PK_CUR    0xF4    /* write cursor */
#define PK_ZTEST  0x32    /* env (+0x10) test byte +0x22: bit0 ZTE, bits 1-2 ZTST */
#define PK_CX     0x128   /* screen centre X, 12.4 GS units (GsPktSetOriginMode_13e2f0) */
#define PK_W      0x130   /* screen width, 12.4 */
#define PK_CY     0x12C   /* screen centre Y, 12.4 */
#define PK_H      0x134   /* screen height, 12.4 */
/* pointer words of the game's packet and memory-stack objects: 4 bytes in game memory, on
 * x64 too (strategy A: every host address is below 2 GB; docs/X64-PLAN.md 0.8) */
#if defined(__x86_64__)
#define PK_PTR(T, p, off) ((T *)(uintptr_t)*(const uint32_t *)((const uint8_t *)(p) + (off)))
#define PK_SET(p, off, v) (*(uint32_t *)((uint8_t *)(p) + (off)) = (uint32_t)(uintptr_t)(v))
#else
#define PK_PTR(T, p, off) (*(T **)((uint8_t *)(p) + (off)))
#define PK_SET(p, off, v) (*(uint8_t **)((uint8_t *)(p) + (off)) = (v))
#endif

static float g_s = 1.0f;
static int g_active;   /* the transform runs: an X squeeze (g_s < 1) and / or a UI scale */
/* accessibility.ui_scale (rg_layout_set_ui_scale): every laid-out group is scaled by g_u in
 * X and Y about its anchor (x: left / centre / right, y: top / middle / bottom), limited per
 * group so it stays on the screen; 1 = off (nothing below changes) */
static float g_u = 1.0f;
static int g_uon;
static const void *g_vdx_task;   /* menu 3D: the task whose view packet was shifted last (rg_layout_view_dx) */
static float g_vdx;
static int g_wide_now, g_wide_last;   /* a wide-content bracket ran this / the last frame (menu position) */
static int g_detect;
static int g_screen_fbp, g_screen_known;   /* this frame's draw buffer (FRAME FBP) */          /* wide canvas: watch for full-screen menus even when pillarboxed */
static unsigned g_cover_now, g_cover_last;   /* menu backgrounds this / the last drawn frame */
/* (cardwide 2026-11-12) the title phase's memory-card screens: their scrolling background
 * (TitleLoadDrawBgCb_4ed9e0 override -> rg_layout_card_bg_begin / _end) up this / the
 * last drawn frame (drawn at full opacity, then while it fades out); RG_LAYOUT_CARD_WIDE=0: pillarboxed like the title (as before) */
static int g_card_bg;                       /* inside the bracket */
static float g_card_alpha;
static unsigned g_card_now, g_card_last;
/* stage 3: the game tasks that drew a full-screen menu background this / the last drawn
 * frame ("menu tasks"): everything they draw is laid out as ONE 4:3 element about the
 * screen centre, background included, over the unchanged wide scene */
#define MAXCT 8
static const void *g_ctask_now[MAXCT], *g_ctask_last[MAXCT];
static int g_nct_now, g_nct_last;
static int g_clear_done;   /* this frame's clear seen (stage 3: black on menu screens) */
static uintptr_t g_capture_task;   /* a task that drew a full-screen scene capture this frame */
/* this frame's edge strips: per canvas side, the screen rows (y0..y1, 12.4) a drawing
 * function already filled; a piece of the same function over rows already filled is a layer
 * over that background (no strips), another function's piece replaces them */
#define MAXSTRIP 16
typedef struct strip_band { uintptr_t fn; float y0, y1, seam; } strip_band;
static strip_band g_strip[2][MAXSTRIP];
static int g_nstrip[2];
static uintptr_t g_pk_task;   /* the packet's drawing function */
static float g_strip_L, g_strip_R;   /* the screen's edges (12.4) for strip_emit */
static int g_strip_mode = -1;   /* RG_LAYOUT_STRIPS: 0 mirror (default), 1 smear (edge band stretched),
                                 * 2 stretch (before 2026-10-31: mirror up to the cap, then the
                                 * last texel stretched; default now mirrors back and forth) */
static int g_menu_vignette = -1;   /* RG_LAYOUT_VIGNETTE=0: a menu's shading layer squeezed with the
                                    * menu (before 2026-10-31) instead of covering the canvas */
static int g_strip_fade = -1;   /* RG_LAYOUT_STRIP_FADE: % darker at the canvas edge (default 75) */
static void strip_opts(void)
{
    if (g_strip_mode >= 0)
        return;
    const char *e = getenv("RG_LAYOUT_STRIPS");
    g_strip_mode = e && e[0] == 's' && e[1] == 'm' ? 1 : e && e[0] == 's' && e[1] == 't' ? 2 : 0;
    e = getenv("RG_LAYOUT_VIGNETTE");
    g_menu_vignette = !(e && *e == '0');
    e = getenv("RG_LAYOUT_STRIP_FADE");
    g_strip_fade = e && *e ? atoi(e) : 75;
    if (g_strip_fade < 0) g_strip_fade = 0;
    if (g_strip_fade > 100) g_strip_fade = 100;
}
/* rows [y0, y1] of this side already filled by function fn from a seam at least as far
 * out as this one (covered fraction); a later layer reaching further out (the Revelation
 * board's parchment over the menu backdrop) is extended from its own edge */
static float strip_covered(int side, uintptr_t fn, float y0, float y1, float seam)
{
    float c = 0.0f;
    for (int i = 0; i < g_nstrip[side]; i++) {
        strip_band *b = &g_strip[side][i];
        if (b->fn != fn || (side == 0 ? b->seam > seam + 16.0f : b->seam < seam - 16.0f))
            continue;
        float a = b->y0 > y0 ? b->y0 : y0, z = b->y1 < y1 ? b->y1 : y1;
        if (z > a)
            c += z - a;
    }
    return y1 > y0 ? c / (y1 - y0) : 1.0f;
}
static void strip_note(int side, uintptr_t fn, float y0, float y1, float seam)
{
    if (g_nstrip[side] < MAXSTRIP)
        g_strip[side][g_nstrip[side]++] = (strip_band){ fn, y0, y1, seam };
}
static int g_menu_pillarbox = -1;   /* RG_LAYOUT_MENU_PILLARBOX=1: stage 2's 4:3 switch (debug) */

static int ded_state(const void *t);
static int menu_task(const void *t)
{
    if (!t)
        return 0;
    for (int i = 0; i < g_nct_now; i++)
        if (g_ctask_now[i] == t)
            return 1;
    for (int i = 0; i < g_nct_last; i++)
        if (g_ctask_last[i] == t)
            return 1;
    return ded_state(t) == 1;   /* a dedicated menu task: the menu from its first packet */
}

static void menu_task_add(const void *t)
{
    for (int i = 0; i < g_nct_now; i++)
        if (g_ctask_now[i] == t)
            return;
    if (g_nct_now < MAXCT)
        g_ctask_now[g_nct_now++] = t;
}

/* Dedicated menu tasks (the menu's first frame): a task is known as a menu task from its
 * background on, so a menu's first frame laid out what it drew BEFORE its background by
 * per-element anchors (the INSMENU team select's labels).  A task that has drawn a menu
 * background and has never drawn a laid-out packet in a frame without one (this frame or
 * the one before) is a dedicated menu task (TaskDrawMenuMain, TaskDrawMenuTrans,
 * TaskDrawMenuShop, TaskDrawMenuInsectVs): everything it draws is the menu from its first
 * packet, also on a later menu's first frame.  The first frame it draws without a menu
 * background two frames running disqualifies it for good (TaskDrawEvent1: help sheets and
 * dialogues). */
#define MAXDED 32
static const void *g_ded[MAXDED];
static int8_t g_ded_st[MAXDED];   /* 1 dedicated, -1 disqualified */
static int g_nded;
static const void *g_drawn[MAXCT * 2];   /* tasks that drew a laid-out packet this frame */
static int g_ndrawn;
static int ded_state(const void *t)
{
    for (int i = 0; i < g_nded; i++)
        if (g_ded[i] == t)
            return g_ded_st[i];
    return 0;
}
static void ded_set(const void *t, int st)
{
    for (int i = 0; i < g_nded; i++)
        if (g_ded[i] == t) {
            if (g_ded_st[i] >= 0)
                g_ded_st[i] = (int8_t)st;
            return;
        }
    if (g_nded < MAXDED) {
        g_ded[g_nded] = t;
        g_ded_st[g_nded++] = (int8_t)st;
    }
}
static void drawn_add(const void *t)
{
    for (int i = 0; i < g_ndrawn; i++)
        if (g_drawn[i] == t)
            return;
    if (g_ndrawn < MAXCT * 2)
        g_drawn[g_ndrawn++] = t;
}
/* at the end of a drawn frame, before the menu task lists roll */
static void ded_roll(void)
{
    for (int i = 0; i < g_ndrawn; i++) {
        int in = 0;
        for (int j = 0; j < g_nct_now && !in; j++)
            in = g_ctask_now[j] == g_drawn[i];
        for (int j = 0; j < g_nct_last && !in; j++)
            in = g_ctask_last[j] == g_drawn[i];
        if (!in)
            ded_set(g_drawn[i], -1);
    }
    for (int j = 0; j < g_nct_now; j++)
        if (ded_state(g_ctask_now[j]) == 0)
            ded_set(g_ctask_now[j], 1);
    g_ndrawn = 0;
}
static int g_field;
static int g_suppress;
static rg_layout_stats g_st;
static FILE *g_log;
static int g_log_init;

static void log_open(void)
{
    if (g_log_init)
        return;
    g_log_init = 1;
    const char *p = getenv("RG_LAYOUT_LOG");
    if (p && *p)
        g_log = fopen(p, "w");
}

/* the X squeeze (the WIDE-aware sites draw at full width while it runs); a UI scale alone
 * (4:3, or the stretch layout) leaves them as they were */
int rg_layout_active(void) { return g_active && g_s < 0.999f; }
void rg_layout_set_ui_scale(float u)
{
    if (!(u >= 0.5f && u <= 2.0f))
        u = 1.0f;
    g_u = u;
    g_uon = fabsf(u - 1.0f) > 0.001f;
    if (!g_uon)
        g_u = 1.0f;
}
float rg_layout_ui_scale(void) { return g_uon ? g_u : 1.0f; }
void rg_layout_set_detect(int on) { g_detect = on; }
static unsigned g_roll_packets;   /* g_st.packets at the last frame roll */
static int card_wide_on(void)   /* read each time (once a field, and on the card packets) */
{
    const char *e = getenv("RG_LAYOUT_CARD_WIDE");
    return !(e && *e == '0');
}
void rg_layout_card_bg_begin(float alpha) { g_card_bg = 1; g_card_alpha = alpha; }
void rg_layout_card_bg_end(void) { g_card_bg = 0; }
int rg_layout_card_screen(void)
{
    if (!g_detect || !card_wide_on())
        return 0;
    return g_st.packets != g_roll_packets ? g_card_now > 0 : g_card_last > 0;
}
/* asked between fields, before rg_layout_set_frame: the frame just drawn decides (a field
 * without packets, the second VBlank of a 30 Hz frame, keeps the last drawn frame's) */
int rg_layout_menu_screen(void)
{
    if (!g_detect)
        return 0;
    return g_st.packets != g_roll_packets ? g_cover_now > 0 : g_cover_last > 0;
}
/* stage 3 (USER 2026-10-19): no aspect switch for menus; the stage 2 pillarbox only with
 * RG_LAYOUT_MENU_PILLARBOX=1 (debug, before/after comparisons) */
int rg_layout_wants_pillarbox(void)
{
    if (g_menu_pillarbox < 0) {
        const char *e = getenv("RG_LAYOUT_MENU_PILLARBOX");
        g_menu_pillarbox = e && *e == '1';
    }
    return g_menu_pillarbox && rg_layout_menu_screen();
}
float rg_layout_scale(void) { return g_active ? g_s : 1.0f; }
void rg_layout_suppress(int on) { g_suppress += on ? 1 : -1; if (g_suppress < 0) g_suppress = 0; }
int rg_layout_suppressed(void) { return g_suppress > 0; }
static int g_about, g_about_px;
static float g_about_x;
static int g_about_xy;          /* rg_layout_about_xy_begin: explicit centre and factors */
static float g_about_y, g_about_kx, g_about_ky;
void rg_layout_about_begin(float ax, int screen_px) { g_about = 1; g_about_x = ax; g_about_px = screen_px; g_about_xy = 0; }
void rg_layout_about_xy_begin(float ax_px, float ay_px, float kx, float ky)
{
    g_about = 1;
    g_about_px = 1;
    g_about_x = ax_px;
    g_about_xy = 1;
    g_about_y = ay_px;
    g_about_kx = kx;
    g_about_ky = ky;
}
void rg_layout_about_end(void) { g_about = 0; g_about_xy = 0; }
static int g_elem;              /* rg_layout_elem_begin: an element extent is set */
static float g_elem_x0, g_elem_x1;   /* (screen pixels) */
void rg_layout_elem_begin(float x0_px, float x1_px) { g_elem = x1_px >= x0_px; g_elem_x0 = x0_px; g_elem_x1 = x1_px; }
void rg_layout_elem_end(void) { g_elem = 0; }
/* rg_layout_follow_begin / _end: the followed task; the bracket's packets' union this frame
 * (12.4); the anchor the bracket's packets get (decided at the last bracket's end), the next */
static const void *g_follow;
static float g_fu_x0, g_fu_x1, g_fu_y0, g_fu_y1, g_fu_w;
static int g_fu_n;
static int g_fa = -1, g_fa_next = -1, g_fa_seen, g_fa_seen_last;
static int follow_anchor(const void *task, float x0, float x1, float y0, float y1);
void rg_layout_follow_begin(const void *task_fn)
{
    const char *e = getenv("RG_LAYOUT_FOLLOW");
    g_follow = (e && *e == '0') ? NULL : task_fn;
    /* the last bracket's decision; the first bracket after none (the menu opening): the anchor
     * of the followed task's lowest packet (the HUD row) */
    g_fa = g_fa_seen_last || g_fa_seen ? g_fa_next
         : g_follow ? follow_anchor(g_follow, -1e30f, 1e30f, -1e30f, 1e30f) : -1;
    g_fu_n = 0;
}
#define FOLLOW_MAXW 0.62f
void rg_layout_follow_end(void)
{
    if (g_follow) {
        g_fa_seen = 1;
        g_fa_next = -1;
        if (g_fu_n > 0 && g_fu_x1 - g_fu_x0 <= FOLLOW_MAXW * g_fu_w)
            g_fa_next = follow_anchor(g_follow, g_fu_x0, g_fu_x1, g_fu_y0, g_fu_y1);
    }
    g_follow = NULL;
}
void rg_layout_get_stats(rg_layout_stats *st) { *st = g_st; }

int rg_layout_anchor(float x0, float x1, float left, float width)
{
    if (width <= 0.0f)
        return RG_ANCHOR_NONE;
    if (x1 - x0 >= RG_LAYOUT_FULL * width)
        return RG_ANCHOR_NONE;
    float c = 0.5f * (x0 + x1) - left;
    if (c < width / 3.0f)
        return RG_ANCHOR_LEFT;
    if (c > 2.0f * width / 3.0f)
        return RG_ANCHOR_RIGHT;
    return RG_ANCHOR_CENTER;
}

/* a cluster of several elements: as wide as the screen = a whole-screen layout (a menu),
 * kept together about the centre */
int rg_layout_cluster_anchor(float x0, float x1, float left, float width)
{
    int a = rg_layout_anchor(x0, x1, left, width);
    return a == RG_ANCHOR_NONE && width > 0.0f ? RG_ANCHOR_CENTER : a;
}

float rg_layout_map(float x, int anchor, float left, float width, float s)
{
    float a;
    switch (anchor) {
    case RG_ANCHOR_LEFT: a = left; break;
    case RG_ANCHOR_CENTER: a = left + 0.5f * width; break;
    case RG_ANCHOR_RIGHT: a = left + width; break;
    default: return x;
    }
    return a + (x - a) * s;
}

static float anchor_pos(int anchor, float left, float width)
{
    return anchor == RG_ANCHOR_LEFT ? left : anchor == RG_ANCHOR_RIGHT ? left + width : left + 0.5f * width;
}

/* the largest k <= want with a + (v - a) * k inside [lo, hi] for v = v0, v1 (v0..v1 inside
 * at k = 1); want itself when nothing limits it */
static float fit_axis(float want, float a, float v0, float v1, float lo, float hi)
{
    float k = want;
    if (v1 > a + 1.0f && (hi - a) / (v1 - a) < k) k = (hi - a) / (v1 - a);
    if (v0 < a - 1.0f && (a - lo) / (a - v0) < k) k = (a - lo) / (a - v0);
    return k;
}

float rg_layout_fit_scale(float u, int ax, int ay, float x0, float x1, float y0, float y1,
                          float left, float w, float top, float h, float s)
{
    if (!(u > 1.0f))
        return u;                       /* shrinking always fits */
    float k = u;
    if (ax != RG_ANCHOR_NONE && s > 0.0f) {
        float kx = fit_axis(u * s, anchor_pos(ax, left, w), x0, x1, left, left + w) / s;
        if (kx < k) k = kx;
    }
    if (ay != RG_ANCHOR_NONE) {
        float ky = fit_axis(u, anchor_pos(ay, top, h), y0, y1, top, top + h);
        if (ky < k) k = ky;
    }
    return k < 1.0f ? 1.0f : k;         /* already past an edge at 1: left as drawn */
}

/* PSMT8 / PSMT4 / PSMT8H / PSMT4HL / PSMT4HH: indexed-colour UI art */
static int indexed_psm(int p)
{
    return p == 0x13 || p == 0x14 || p == 0x1B || p == 0x24 || p == 0x2C;
}

/* ---- GIF scan ---- */
static int g_scan_psm = -1;   /* the last TEX0 pixel format a scan saw (-1 none) */
static int g_scan_fbp = -1, g_scan_fbw = -1;   /* the last FRAME a scan saw */
static int g_scan_tbp = -1;   /* the last TEX0 base pointer (64-word blocks) */
static void *g_scan_tc;       /* the last texture coordinate written (UV / ST) */
static uint8_t g_scan_tck;    /* 0 none, 1 UV (u16, 14 bits), 2 ST (float S) */
/* the packet's vertex colours (RGBAQ): byte pointers to R, G, B (stride 1 for A+D /
 * REGLIST, 4 for PACKED) */
#define MAXCOL 64
static uint8_t *g_scan_col[MAXCOL];
static uint8_t g_scan_colstep[MAXCOL];
static int g_scan_ncol;
static uint8_t *g_scan_primq;  /* the last A+D PRIM qword (NULL none) */
static uint8_t g_scan_prim = 0xFF;   /* its primitive type (6 = sprite), 0xFF unknown */
static uint16_t g_scan_vix;    /* vertices since that PRIM */
static uint8_t g_scan_ad;      /* scanning an A+D qword (the register is at q + 8) */
static uint64_t g_scan_tex0;   /* the last TEX0 value (TFX bits 35-36) */
static uint8_t *g_scan_rgbaq;  /* the last A+D RGBAQ qword (NULL none) */
static void add_color(uint8_t *q, int step)
{
    if (g_scan_ncol < MAXCOL) {
        g_scan_col[g_scan_ncol] = q;
        g_scan_colstep[g_scan_ncol++] = (uint8_t)step;
    }
}
static int add_vertex(rg_layout_xref *out, int n, int max, uint8_t *q, int xoff, int yoff)
{
    if (out && n < max) {
        out[n].x = (uint16_t *)(q + xoff);
        out[n].y = (uint16_t *)(q + yoff);
        out[n].tc = g_scan_tc;
        out[n].tck = g_scan_tck;
        out[n].prim = g_scan_prim;
        out[n].vix = g_scan_vix;
        out[n].ad = g_scan_ad;
        out[n].kind = 0;
        out[n].sc = NULL;
        out[n].shift = 0;
        out[n].col = g_scan_rgbaq;
    }
    g_scan_vix++;
    return n + 1;
}

/* a vertex's texture coordinate U: UV in texels (10.4 -> float), ST as is */
static float tc_get(const rg_layout_xref *x)
{
    if (x->tck == 1)
        return (float)(*(uint16_t *)x->tc & 0x3FFF) / 16.0f;
    float f;
    memcpy(&f, x->tc, 4);
    return f;
}

static void tc_set(const rg_layout_xref *x, float u)
{
    if (x->tck == 1) {
        float v = u * 16.0f + 0.5f;
        if (v < 0.0f) v = 0.0f;
        if (v > 16383.0f) v = 16383.0f;
        uint16_t *p = (uint16_t *)x->tc;
        *p = (uint16_t)((*p & ~0x3FFF) | ((unsigned)v & 0x3FFF));
    } else if (x->tck == 2) {
        memcpy(x->tc, &u, 4);
    }
}

static int add_scissor(rg_layout_xref *out, int n, int max, uint8_t *q)
{
    if (out && n < max) {
        out[n].x = NULL;
        out[n].y = NULL;
        out[n].tc = NULL;
        out[n].tck = 0;
        out[n].prim = 0xFF;
        out[n].vix = 0;
        out[n].ad = 0;
        out[n].kind = 1;
        out[n].sc = (uint64_t *)q;
        out[n].shift = 0;
        out[n].col = NULL;
    }
    return n + 1;
}

/* one A+D / REGLIST register value at q (64 bits) */
static int reg64(rg_layout_xref *out, int n, int max, uint8_t *q, unsigned reg)
{
    switch (reg) {
    case 0x04: case 0x05: case 0x0C: case 0x0D:   /* XYZF2 XYZ2 XYZF3 XYZ3: X 0-15, Y 16-31 */
        return add_vertex(out, n, max, q, 0, 2);
    case 0x00:                                     /* PRIM: type bits 0-2 */
        g_scan_primq = g_scan_ad ? q : NULL;
        g_scan_prim = (uint8_t)(q[0] & 7);
        g_scan_vix = 0;
        return n;
    case 0x01:                                     /* RGBAQ: R G B A bytes 0-3 */
        add_color(q, 1);
        g_scan_rgbaq = g_scan_ad ? q : NULL;
        return n;
    case 0x02: case 0x03:                          /* ST (S float bits 0-31) / UV (U bits 0-13) */
        g_scan_tc = q;
        g_scan_tck = reg == 0x03 ? 1 : 2;
        return n;
    case 0x40: case 0x41:                          /* SCISSOR_1/2 */
        return add_scissor(out, n, max, q);
    case 0x4C: case 0x4D: {                        /* FRAME_1/2: the target's base (FBP) */
        uint64_t v;
        memcpy(&v, q, 8);
        g_scan_fbp = (int)(v & 0x1FF);
        g_scan_fbw = (int)((v >> 16) & 0x3F);
        return n;
    }
    case 0x06: case 0x07: {                        /* TEX0_1/2: the texture's pixel format */
        uint64_t v;
        memcpy(&v, q, 8);
        g_scan_psm = (int)((v >> 20) & 0x3F);
        g_scan_tbp = (int)(v & 0x3FFF);
        g_scan_tex0 = v;
        return n;
    }
    default:
        return n;
    }
}

int rg_layout_scan_gif(uint8_t *buf, int qwc, rg_layout_xref *out, int max)
{
    int n = 0, i = 0;
    while (i < qwc) {
        uint64_t lo, hi;
        memcpy(&lo, buf + 16 * i, 8);
        memcpy(&hi, buf + 16 * i + 8, 8);
        unsigned nloop = (unsigned)(lo & 0x7FFF);
        unsigned flg = (unsigned)((lo >> 58) & 3);
        unsigned nreg = (unsigned)((lo >> 60) & 0xF);
        if (nreg == 0)
            nreg = 16;
        if ((lo >> 46) & 1) {                        /* PRE: the tag sets PRIM (bits 47-57) */
            g_scan_primq = NULL;
            g_scan_prim = (uint8_t)((lo >> 47) & 7);
            g_scan_vix = 0;
        }
        i++;
        if (flg == 0) {                              /* PACKED */
            if ((uint64_t)i + (uint64_t)nloop * nreg > (uint64_t)qwc)
                break;
            for (unsigned l = 0; l < nloop; l++)
                for (unsigned r = 0; r < nreg; r++, i++) {
                    unsigned rd = (unsigned)((hi >> (4 * r)) & 0xF);
                    uint8_t *q = buf + 16 * i;
                    if (rd == 0x4 || rd == 0x5 || rd == 0xC || rd == 0xD)
                        n = add_vertex(out, n, max, q, 0, 4);   /* X bits 0-15, Y 32-47 */
                    else if (rd == 0x1) {                       /* RGBAQ: R G B A words */
                        add_color(q, 4);
                        g_scan_rgbaq = NULL;
                    }
                    else if (rd == 0x2 || rd == 0x3) {          /* ST: S float; UV: U 0-13 */
                        g_scan_tc = q;
                        g_scan_tck = rd == 0x3 ? 1 : 2;
                    } else if (rd == 0xE) {
                        g_scan_ad = 1;
                        n = reg64(out, n, max, q, q[8]);
                        g_scan_ad = 0;
                    } else if (rd == 0x0) {                     /* PRIM */
                        g_scan_primq = NULL;
                        g_scan_prim = (uint8_t)(q[0] & 7);
                        g_scan_vix = 0;
                    }
                }
        } else if (flg == 1) {                       /* REGLIST: 64-bit values, 2 per qword */
            uint64_t total = (uint64_t)nloop * nreg;
            uint64_t qw = (total + 1) / 2;
            if ((uint64_t)i + qw > (uint64_t)qwc)
                break;
            for (uint64_t k = 0; k < total; k++) {
                unsigned rd = (unsigned)((hi >> (4 * (k % nreg))) & 0xF);
                uint8_t *q = buf + 16 * i + 8 * k;
                if (rd == 0x4 || rd == 0x5 || rd == 0xC || rd == 0xD)
                    n = add_vertex(out, n, max, q, 0, 2);
                else if (rd == 0x1 || rd == 0x2 || rd == 0x3)
                    n = reg64(out, n, max, q, rd);
            }
            i += (int)qw;
        } else {                                     /* IMAGE / disabled: skip data */
            i += (int)nloop;
        }
    }
    return n;
}

/* the packet's DMA chain from its base to the cursor: cnt segments carry VIF
 * DIRECT / DIRECTHL GIF data; call / ref tags point elsewhere (skipped) */
static int scan_packet(uint8_t *base, uint8_t *end, rg_layout_xref *out, int max)
{
    int n = 0;
    uint8_t *p = base;
    int guard = 0;
    while (p + 16 <= end && guard++ < 4096) {
        uint32_t tag, v2, v3;
        memcpy(&tag, p, 4);
        memcpy(&v2, p + 8, 4);
        memcpy(&v3, p + 12, 4);
        unsigned qwc = tag & 0xFFFF, id = (tag >> 28) & 7;
        if (id == 1) {                               /* cnt */
            uint8_t *data = p + 16;
            if (data + 16 * qwc > end)
                qwc = (unsigned)((end - data) / 16);
            unsigned cmd = (v3 >> 24) & 0x7F;
            if (cmd == 0x50 || cmd == 0x51) {
                unsigned sz = v3 & 0xFFFF;
                if (sz == 0 || sz > qwc)
                    sz = qwc;
                n += rg_layout_scan_gif(data, (int)sz, out ? out + n : NULL, max > n ? max - n : 0);
            }
            (void)v2;
            p = data + 16 * qwc;
        } else if (id == 5 || id == 3 || id == 0) {  /* call / ref / refe */
            p += 16;
        } else {
            break;
        }
    }
    return n;
}


/* ---- anchors from the last frame: identity -> anchor ---- */
#define TAB 16384                       /* power of two */
typedef struct aent { uint32_t key; uint8_t anchor, yanchor; float u; } aent;
static aent g_prev[TAB], g_next[TAB];

static uint32_t mix(uint32_t h, uint32_t v)
{
    h ^= v;
    h *= 16777619u;
    return h;
}

static void tab_put(aent *t, uint32_t key, int anchor, int yanchor, float u)
{
    for (uint32_t i = key & (TAB - 1), n = 0; n < TAB; i = (i + 1) & (TAB - 1), n++)
        if (t[i].key == 0 || t[i].key == key) {
            t[i].key = key;
            t[i].anchor = (uint8_t)anchor;
            t[i].yanchor = (uint8_t)yanchor;
            t[i].u = u;
            return;
        }
}

/* the anchor (-1: none filed); *ya / *u: the UI-scale Y anchor and the group's scale */
static int tab_get(const aent *t, uint32_t key, int *ya, float *u)
{
    for (uint32_t i = key & (TAB - 1), n = 0; n < TAB; i = (i + 1) & (TAB - 1), n++) {
        if (t[i].key == key) {
            *ya = t[i].yanchor;
            *u = t[i].u;
            return t[i].anchor;
        }
        if (t[i].key == 0)
            return -1;
    }
    return -1;
}

/* ordinal of (task, caller) within the frame */
#define ORD 4096
typedef struct oent { uint32_t key; uint32_t n; } oent;
static oent g_ord[ORD];

static uint32_t ordinal(uint32_t k)
{
    for (uint32_t i = k & (ORD - 1), n = 0; n < ORD; i = (i + 1) & (ORD - 1), n++)
        if (g_ord[i].key == 0 || g_ord[i].key == k) {
            g_ord[i].key = k;
            return g_ord[i].n++;
        }
    return 0;
}

/* ---- this frame's movable packets, per open task ---- */
#define MAXPK 4096
typedef struct pkrec {
    uint32_t key;
    float x0, x1, y0, y1;     /* original rectangle, 12.4 */
    float left, w;            /* screen, 12.4 */
    float top, h;             /*   (Y) */
    int anchor;               /* the anchor it was drawn with this frame */
    int yanchor;              /* UI scale: its Y anchor and its group's scale */
    float u;
    int forced;               /* rg_layout_follow_begin: the followed anchor (filed as is), else 0 */
} pkrec;
static pkrec g_pk[MAXPK];
static int g_npk;
#define MAXDEPTH 16
static int g_mark[MAXDEPTH];
static const void *g_task[MAXDEPTH];
static int g_depth;

/* every task's packets with the anchors their groups got (rg_layout_follow_begin reads the
 * last drawn frame's) */
typedef struct frec { const void *task; float x0, x1, y0, y1; int anchor; } frec;
static frec g_fr[2][MAXPK];
static int g_nfr[2];
static int g_frcur;              /* g_fr[g_frcur]: this frame's; the other: the last drawn frame's */

static void follow_note(const void *task, const pkrec *k, int anchor)
{
    if (task && g_nfr[g_frcur] < MAXPK) {
        frec *f = &g_fr[g_frcur][g_nfr[g_frcur]++];
        f->task = task;
        f->x0 = k->x0;
        f->x1 = k->x1;
        f->y0 = k->y0;
        f->y1 = k->y1;
        f->anchor = anchor;
    }
}

/* the anchor of the followed task's lowest packet overlapping [x0, x1] in the last drawn
 * frame and at most a quarter of the screen height below [y0, y1] (12.4 units), or -1.  (The
 * battle menu's widget set also draws the "Main Menu / Team Command" box at the top left,
 * far above the HUD: it keeps its own layout.) */
#define FOLLOW_BELOW (0.25f * RG_LAYOUT_FRAME_H * 16.0f)
/* (FOLLOW_MAXW, above) a bracket follows only when all its packets together are at most this
 * share of the screen wide: the command page, panel + cursor over one member's slot (~0.35;
 * with the slot glow of the menu's opening, 16..307, 0.57); the Items page (grid and
 * description box, ~0.73) keeps its own layout: following the HUD row under part of it tore
 * it apart (widegate btlitems, a first version of this lane decided per packet).  One anchor
 * for the whole bracket: per group, the opening's sparkles (single packets, identities
 * shuffled each frame) mixed two anchors. */
static int follow_anchor(const void *task, float x0, float x1, float y0, float y1)
{
    const frec *fr = g_fr[g_frcur ^ 1];
    int best = -1;
    float by = -1e30f;
    for (int i = 0; i < g_nfr[g_frcur ^ 1]; i++)
        if (fr[i].task == task && fr[i].x0 <= x1 && x0 <= fr[i].x1 && fr[i].y1 > by &&
            fr[i].y1 >= y0 && fr[i].y0 - y1 <= FOLLOW_BELOW &&
            fr[i].anchor > RG_ANCHOR_NONE) {
            by = fr[i].y1;
            best = fr[i].anchor;
        }
    return best;
}

static int find(int *par, int i)
{
    while (par[i] != i)
        i = par[i] = par[par[i]];
    return i;
}

/* cluster g_pk[first..g_npk) (drawn by `task`, NULL: outside any task) by overlap and file
 * their anchors for the next frame */
static void cluster(int first, const void *task)
{
    static int par[MAXPK];
    static float gx0[MAXPK], gx1[MAXPK], gy0[MAXPK], gy1[MAXPK];
    const float slack = 4.0f * 16.0f;
    for (int i = first; i < g_npk; i++)
        par[i] = i;
    for (int i = first; i < g_npk; i++)
        for (int j = first; j < i; j++) {
            pkrec *a = &g_pk[i], *b = &g_pk[j];
            if (a->x0 <= b->x1 + slack && b->x0 <= a->x1 + slack &&
                a->y0 <= b->y1 + slack && b->y0 <= a->y1 + slack)
                par[find(par, i)] = find(par, j);
        }
    for (int i = first; i < g_npk; i++) {
        gx0[i] = gy0[i] = 1e30f;
        gx1[i] = gy1[i] = -1e30f;
    }
    for (int i = first; i < g_npk; i++) {
        int r = find(par, i);
        if (g_pk[i].x0 < gx0[r]) gx0[r] = g_pk[i].x0;
        if (g_pk[i].x1 > gx1[r]) gx1[r] = g_pk[i].x1;
        if (g_pk[i].y0 < gy0[r]) gy0[r] = g_pk[i].y0;
        if (g_pk[i].y1 > gy1[r]) gy1[r] = g_pk[i].y1;
    }
    for (int i = first; i < g_npk; i++) {
        int r = find(par, i);
        const pkrec *k = &g_pk[i];
        int a = rg_layout_cluster_anchor(gx0[r], gx1[r], k->left, k->w);
        int ya = RG_ANCHOR_NONE;
        float u = 1.0f;
        if (g_uon) {
            ya = rg_layout_cluster_anchor(gy0[r], gy1[r], k->top, k->h);
            u = rg_layout_fit_scale(g_u, a, ya, gx0[r], gx1[r], gy0[r], gy1[r], k->left, k->w, k->top, k->h, g_s);
        }
        if (k->forced > RG_ANCHOR_NONE)
            a = k->forced;               /* follows another task's layout (follow_begin) */
        tab_put(g_next, g_pk[i].key, a, ya, u);
        follow_note(task, k, a);
        if (r == i)
            g_st.groups++;
    }
}

void rg_layout_set_frame(float s, int field)
{
    g_vdx_task = NULL;   /* (menu 3D) a new frame: no view packet shifted yet */
    /* close the frame that ended: packets drawn outside any task form one group.  The
     * game draws at 30 or 60 Hz: a field without packets (the second VBlank of a 30 Hz
     * frame) keeps the last drawn frame's anchors. */
    static unsigned last_packets;
    if ((g_active || g_detect) && g_st.packets != last_packets) {
        g_cover_last = g_cover_now;
        g_cover_now = 0;
        g_card_last = g_card_now;
        g_card_now = 0;
        ded_roll();
        memcpy(g_ctask_last, g_ctask_now, sizeof g_ctask_last);
        g_nct_last = g_nct_now;
        g_nct_now = 0;
    }
    g_roll_packets = g_st.packets;
    if (g_st.packets != last_packets)
        g_screen_known = 0;
    if (g_st.packets != last_packets)
        g_clear_done = 0;
    if (g_st.packets != last_packets)
        g_nstrip[0] = g_nstrip[1] = 0;
    if (g_st.packets != last_packets)
        g_capture_task = 0;
    if (!g_detect && !g_active) {
        g_cover_last = g_cover_now = 0;
        g_card_last = g_card_now = 0;
        g_nct_last = g_nct_now = 0;
        g_ndrawn = 0;
    }
    if (g_active && g_st.packets != last_packets) {
        cluster(0, NULL);
        g_fa_seen_last = g_fa_seen;
        g_fa_seen = 0;
        g_frcur ^= 1;
        g_nfr[g_frcur] = 0;
        memcpy(g_prev, g_next, sizeof g_prev);
        memset(g_next, 0, sizeof g_next);
        memset(g_ord, 0, sizeof g_ord);
    } else if (!g_active) {
        memset(g_prev, 0, sizeof g_prev);
        memset(g_next, 0, sizeof g_next);
        memset(g_ord, 0, sizeof g_ord);
        g_nfr[0] = g_nfr[1] = 0;
    }
    last_packets = g_st.packets;
    g_npk = 0;
    g_depth = 0;
    g_field = field;
    g_wide_last = g_wide_now;
    g_wide_now = 0;
    const char *e = getenv("RG_LAYOUT");
    if (e && *e == '0')
        s = 1.0f;
    g_s = s;
    g_active = s < 0.999f || (g_uon && !(e && *e == '0'));
    if (g_active || g_detect) {
        log_open();
        if (g_log)
            fprintf(g_log, "%d frame s=%.4f cover=%u/%u packets=%u moved=%u full=%u ztest=%u suppressed=%u groups=%u\n",
                    field, s, g_cover_last, g_cover_now, g_st.packets, g_st.moved, g_st.full, g_st.ztest, g_st.suppressed, g_st.groups);
    }
}

void rg_layout_task_begin(const void *fn)
{
    if (!g_active && !g_detect)
        return;
    if (g_depth < MAXDEPTH) {
        g_mark[g_depth] = g_npk;
        g_task[g_depth] = fn;
    }
    g_depth++;
}

void rg_layout_task_end(void)
{
    if ((!g_active && !g_detect) || g_depth <= 0)
        return;
    g_depth--;
    if (g_active && g_depth < MAXDEPTH) {
        int first = g_mark[g_depth];
        cluster(first, g_task[g_depth]);
        g_npk = first;
    }
}

static const char *aname(int a)
{
    return a == RG_ANCHOR_LEFT ? "left" : a == RG_ANCHOR_RIGHT ? "right" : a == RG_ANCHOR_CENTER ? "center" : "none";
}

/* ---- stage 3: menu sprites (rg_layout_packet, menu packets only) ---- */
/* append A+D qwords (reg, value) to the packet being closed: only when it is a single A+D
 * GIF tag at the top of its memory stack with room left (GsPktClose then reserves the
 * longer packet); returns 0 (nothing written) otherwise */
#define MS_USED 0x2C    /* memory stack (MemStackAllocQw_14d950): qwords used */
#define MS_BASE 0x28    /*   base address */
#define MS_CAP  0x34    /*   capacity in qwords */
#define MS_OFF  0x20    /*   non-zero: allocation refused */
static int append_ad(void *pkt, const uint64_t *val, const uint8_t *reg, int k)
{
    uint8_t *ms = PK_PTR(uint8_t, pkt, 0);
    uint8_t *base = PK_PTR(uint8_t, pkt, PK_BASE);
    uint8_t *cur = PK_PTR(uint8_t, pkt, PK_CUR);
    uint8_t *tag = PK_PTR(uint8_t, pkt, 0x100);
    uint32_t *dma = PK_PTR(uint32_t, pkt, 0x104);
    uint32_t *vif = PK_PTR(uint32_t, pkt, 0x108);
    if (!ms || !base || !cur || !tag || !dma || !vif || k <= 0)
        return 0;
    int32_t used = *(int32_t *)(ms + MS_USED), cap = *(int32_t *)(ms + MS_CAP);
    uint8_t *msbase = (uint8_t *)(uintptr_t)*(uint32_t *)(ms + MS_BASE);
    if (*(int32_t *)(ms + MS_OFF) != 0 || msbase + 16 * (intptr_t)used != base) {
        if (g_log)
            fprintf(g_log, "  append: not at the stack top (off %d, top %p, base %p)\n", *(int32_t *)(ms + MS_OFF),
                    (void *)(msbase + 16 * (intptr_t)used), (void *)base);
        return 0;
    }
    if ((cur - base) / 16 + k + 1 > cap - used) {
        if (g_log)
            fprintf(g_log, "  append: no room (%d + %d of %d)\n", (int)((cur - base) / 16), k, cap - used);
        return 0;
    }
    uint64_t lo, hi;
    memcpy(&lo, tag, 8);
    memcpy(&hi, tag + 8, 8);
    if (((lo >> 58) & 3) != 0 || ((lo >> 60) & 0xF) != 1 || (hi & 0xF) != 0xE)
    {
        if (g_log)
            fprintf(g_log, "  append: not an A+D tag (%016llx %016llx)\n", (unsigned long long)lo, (unsigned long long)hi);
        return 0;                                    /* not one A+D tag */
    }
    if ((lo & 0x7FFF) + (uint64_t)k > 0x7FFF || (dma[0] & 0xFFFF) + (uint32_t)k > 0xFFFF ||
        (vif[0] & 0xFFFF) + (uint32_t)k > 0xFFFF)
        return 0;
    for (int i = 0; i < k; i++) {
        uint64_t r = reg[i];
        memcpy(cur + 16 * i, &val[i], 8);
        memcpy(cur + 16 * i + 8, &r, 8);
    }
    *(uint32_t *)tag = (uint32_t)(((lo & 0x7FFF) + (uint64_t)k) | 0x8000u);
    dma[0] = (dma[0] & 0xFFFF0000u) | ((dma[0] & 0xFFFF) + (uint32_t)k);
    vif[0] = (vif[0] & 0xFFFF0000u) | ((vif[0] & 0xFFFF) + (uint32_t)k);
    PK_SET(pkt, PK_CUR, cur + 16 * k);
    return 1;
}

static void set_x(rg_layout_xref *x, float v)
{
    if (v < 0.0f) v = 0.0f;
    if (v > 65535.0f) v = 65535.0f;
    *x->x = (uint16_t)(v + 0.5f);
}

/* Sprites of a full-screen menu (laid out as one 4:3 element about the centre):
 *   - entirely outside the 4:3 screen (panels slid out, hidden at 4:3): collapsed to
 *     zero width, so they stay hidden on the wide canvas;
 *   - mostly outside, or small: clipped to the 4:3 screen (UV cut with it), then laid out;
 *   - mostly inside, at least a quarter of the screen wide and bleeding off an edge
 *     (title bars): laid out, the outer vertex pinned to the canvas edge;
 *   - the menu's background pieces (bg: a tall, wide indexed-colour packet; per sprite at
 *     least an eighth of the screen each way, so the small cells and icons a background
 *     packet may carry (the Revelation board) follow the rules above): laid out, and the
 *     canvas left uncovered beside them is filled with strips of their own edge art
 *     (appended to the packet), so the background reaches the canvas edges without moving
 *     its cut-outs.  bg 1: the strip mirrors the art across the seam and darkens toward
 *     the canvas edge in up to 16 bands (RG_LAYOUT_STRIP_FADE, default 75 % at the edge, so strong
 *     features near the art's edge -- the main menu's compass rose -- read as a dim
 *     vignette, not a mirrored copy; RG_LAYOUT_STRIPS=smear stretches the outer 6 texels
 *     instead).  Per drawing function only the lowest layer over given screen rows is
 *     extended (a layer drawn over it, e.g. the main menu's backdrop with its shaded
 *     cut-out, would mirror its shading into the side; tiles in other rows still get
 *     theirs), unless the later layer reaches further out (the Revelation board's
 *     parchment over the menu backdrop); within one packet the topmost sprite of the
 *     rows wins (the backdrop's translucent black shadow sprite, then its art).  bg 2: an overlay drawn over a full-screen scene capture (help sheets over
 *     a battle): its edge column (the dimmed margin) is stretched over the sides.
 * done[j] is set for every vertex handled here. */
#define MAXAD 320
#define MAXSTRIPS 32
typedef struct strip_job {
    rg_layout_xref *a, *l, *r;     /* first-written vertex, left / right vertex */
    float ml, mr, uin, uout, y0, y1;
    float cap;                     /* > 0: the strip mirrors back and forth within this many
                                    * texels of uin (uout is then the unbounded end) */
    int side;
} strip_job;

/* the U of a strip at texel distance d from its seam: straight (as before) or, with a cap,
 * mirrored back and forth within the cap (a triangle wave: no stretched last texel) */
static int strip_turns(const strip_job *j)
{
    float dist = j->uout > j->uin ? j->uout - j->uin : j->uin - j->uout;
    if (j->cap <= 0.0f || dist <= j->cap)
        return 0;
    int n = (int)(dist / j->cap);
    return (float)n * j->cap < dist - 1e-3f ? n : n - 1;
}

/* the A+D qwords of nst strips, nb colour bands each (nb 1: no colour writes); -1 too long */
static int strip_emit(const strip_job *sj, int nst, int nb, uint64_t *val, uint8_t *reg)
{
    int k = 0;
    if (g_scan_primq) {
        memcpy(&val[k], g_scan_primq, 8);
        reg[k++] = 0x00;
    }
    uint64_t c0 = 0;
    if (nb > 1)
        memcpy(&c0, g_scan_rgbaq, 8);
    for (int i = 0; i < nst; i++) {
        const strip_job *j = &sj[i];
        float seam = j->side == 0 ? j->ml : j->mr, edge = j->side == 0 ? g_strip_L : g_strip_R;
        /* a sprite takes the colour of its second (kicking) vertex */
        const rg_layout_xref *kv = j->a == j->l ? j->r : j->l;
        uint64_t cs = 0;
        if (nb > 1)
            memcpy(&cs, kv->col, 8);
        float dist = j->uout > j->uin ? j->uout - j->uin : j->uin - j->uout;
        float sgn = j->uout >= j->uin ? 1.0f : -1.0f;
        int pp = strip_turns(j) > 0;
        for (int bnd = 0; bnd < nb; bnd++) {
            if (k + 7 > MAXAD)
                return -1;
            float t0 = (float)bnd / (float)nb, t1 = (float)(bnd + 1) / (float)nb;
            if (nb > 1) {
                float tc = 0.5f * (t0 + t1);
                float f = 1.0f - 0.01f * (float)g_strip_fade * tc * tc * (3.0f - 2.0f * tc);
                uint64_t c = cs;
                for (int ch = 0; ch < 3; ch++) {
                    unsigned v = (unsigned)((cs >> (8 * ch)) & 0xFF);
                    v = (unsigned)((float)v * f + 0.5f);
                    c = (c & ~((uint64_t)0xFF << (8 * ch))) | ((uint64_t)(v & 0xFF) << (8 * ch));
                }
                val[k] = c;
                reg[k++] = 0x01;
            }
            /* the band as one sprite, or (mirroring back and forth) split where U turns */
            float d0 = t0 * dist, d1 = t1 * dist;
            for (int once = 1; once || d0 < d1 - 1e-4f; once = 0) {
                float dn = d1, fa, fb;
                if (pp) {
                    int seg = (int)(d0 / j->cap + 1e-4f);
                    float tn = (float)(seg + 1) * j->cap;
                    if (tn < dn) dn = tn;
                    fa = d0 - (float)seg * j->cap;
                    fb = dn - (float)seg * j->cap;
                    if (seg & 1) {
                        fa = j->cap - fa;
                        fb = j->cap - fb;
                    }
                } else {
                    fa = d0;
                    fb = dn;
                }
                if (k + 6 > MAXAD)
                    return -1;
                float xa = seam + (edge - seam) * (dist > 0.0f ? d0 / dist : t0);
                float xb = seam + (edge - seam) * (dist > 0.0f ? dn / dist : t1);
                float ua = j->uin + sgn * fa, ub = j->uin + sgn * fb;
                float xlv = xa < xb ? xa : xb, xrv = xa < xb ? xb : xa;
                float ulv = xa < xb ? ua : ub, urv = xa < xb ? ub : ua;
                for (int e = 0; e < 2; e++) {     /* the original write order: a first */
                    rg_layout_xref *s0 = e == 0 ? j->a : (j->a == j->l ? j->r : j->l);
                    float xv = s0 == j->l ? xlv : xrv, uv = s0 == j->l ? ulv : urv;
                    uint64_t t, xyz;
                    memcpy(&t, s0->tc, 8);
                    memcpy(&xyz, s0->x, 8);
                    t = (t & ~(uint64_t)0x3FFF) | ((unsigned)(uv * 16.0f + 0.5f) & 0x3FFF);
                    xyz = (xyz & ~(uint64_t)0xFFFF) | ((unsigned)(xv + 0.5f) & 0xFFFF);
                    val[k] = t;
                    reg[k++] = ((uint8_t *)s0->tc)[8];
                    val[k] = xyz;
                    reg[k++] = ((uint8_t *)s0->x)[8];
                }
                d0 = dn;
            }
        }
    }
    if (nb > 1) {                                   /* the packet's last colour, as it was */
        val[k] = c0;
        reg[k++] = 0x01;
    }
    return k;
}

/* (2026-10-31) Repeated frame strips.  A menu frame's long bars are drawn as a row of
 * identical tiles (the top frame strip of the main menu and its sub-screens: 7 columns of 64
 * px, two rows, u 106..170 each, from x 111 to 559, past the right edge of the screen).
 * Tile by tile they were small sprites, so the one across the screen edge was clipped and
 * the ones beyond hidden: the bar stopped at the old 4:3 edge while the header bar under it
 * (one wide sprite) was pinned to the canvas edge.  A row of at least two abutting tiles
 * with the same size, rows and texture range, together at least a quarter of the screen
 * wide, mostly on it and running past an edge, is laid out whole (no clip / hide) and
 * continued to the canvas edge with more copies of its outermost tile (appended to the
 * packet like the strips): the bar keeps its art at its own scale instead of a stretch.
 * rep[j] (j: the sprite's first vertex) = 1 tile of such a row; the copies are emitted by
 * rep_emit.  RG_LAYOUT_REPEAT=0: as before. */
typedef struct rep_spr {
    int j;
    float xl, xr, y0, y1, ul, ur;
} rep_spr;
typedef struct rep_job {
    int o;          /* xs index of the outermost tile's first vertex */
    int side;       /* 0 left, 1 right */
} rep_job;
static int g_repeat = -1;

static int rep_find(rg_layout_xref *xs, int n, float L, float w, uint8_t *rep, rep_job *jobs, int maxjobs)
{
    static rep_spr sp[4096];
    static uint8_t used[4096];
    const float R = L + w, px = 16.0f;
    int ns = 0, nj = 0;
    if (g_repeat < 0) {
        const char *e = getenv("RG_LAYOUT_REPEAT");
        g_repeat = !(e && *e == '0');
    }
    if (!g_repeat)
        return 0;
    for (int j = 0; j + 1 < n && ns < 4096; j++) {
        rg_layout_xref *a = &xs[j], *b = &xs[j + 1];
        if (a->kind || b->kind || a->prim != 6 || b->prim != 6 || (a->vix & 1) || b->vix != a->vix + 1)
            continue;
        rg_layout_xref *l = (float)*a->x <= (float)*b->x ? a : b, *r = l == a ? b : a;
        if (l->tck == 1 && r->tck == 1 && l->ad && r->ad && *r->x > *l->x) {
            float ya = (float)*a->y, yb = (float)*b->y;
            sp[ns++] = (rep_spr){ j, (float)*l->x, (float)*r->x, ya < yb ? ya : yb, ya < yb ? yb : ya,
                                  tc_get(l), tc_get(r) };
        }
        j++;
    }
    memset(used, 0, (size_t)ns);
    for (int i = 0; i < ns; i++) {
        if (used[i])
            continue;
        /* the row of tiles like sp[i]: same rows, width and texture range */
        static int mem[4096];
        int nm = 0;
        for (int k = i; k < ns; k++)
            if (!used[k] && fabsf(sp[k].y0 - sp[i].y0) <= px && fabsf(sp[k].y1 - sp[i].y1) <= px &&
                fabsf((sp[k].xr - sp[k].xl) - (sp[i].xr - sp[i].xl)) <= px &&
                fabsf(sp[k].ul - sp[i].ul) < 0.5f && fabsf(sp[k].ur - sp[i].ur) < 0.5f) {
                used[k] = 1;
                mem[nm++] = k;
            }
        if (nm < 2)
            continue;
        for (int p = 1; p < nm; p++)                 /* by x (insertion sort: short rows) */
            for (int q = p; q > 0 && sp[mem[q]].xl < sp[mem[q - 1]].xl; q--) {
                int t = mem[q];
                mem[q] = mem[q - 1];
                mem[q - 1] = t;
            }
        /* abutting; a tile may be drawn twice in place (the main menu's frame strips are:
         * two passes over the same rectangles) */
        int ok = 1, nu = 1;
        for (int p = 1; p < nm && ok; p++) {
            if (fabsf(sp[mem[p]].xl - sp[mem[p - 1]].xl) <= px)
                continue;
            ok = fabsf(sp[mem[p]].xl - sp[mem[p - 1]].xr) <= px;
            nu++;
        }
        if (nu < 2)
            continue;
        float x0 = sp[mem[0]].xl, x1 = sp[mem[nm - 1]].xr;
        float vis = ((x1 < R ? x1 : R) - (x0 > L ? x0 : L)) / (x1 - x0);
        int out0 = x0 < L - px, out1 = x1 > R + px;
        if (g_log && (out0 || out1))
            fprintf(g_log, "  repeat?: %d tiles x=%.1f..%.1f abut %d vis %.2f\n", nm, (x0 - L) / 16.0f,
                    (x1 - L) / 16.0f, ok, vis);
        if (!ok || x1 - x0 < 0.25f * w || vis < 0.5f || !(out0 || out1))
            continue;
        for (int p = 0; p < nm; p++)
            rep[sp[mem[p]].j] = 1;
        /* every sprite of the outermost tile continues (each pass of a doubly drawn one) */
        for (int p = 0; out0 && p < nm && fabsf(sp[mem[p]].xl - x0) <= px; p++)
            if (nj < maxjobs)
                jobs[nj++] = (rep_job){ sp[mem[p]].j, 0 };
        for (int p = nm - 1; out1 && p >= 0 && fabsf(sp[mem[p]].xr - x1) <= px; p--)
            if (nj < maxjobs)
                jobs[nj++] = (rep_job){ sp[mem[p]].j, 1 };
    }
    return nj;
}

/* the A+D qwords continuing each job's row to the canvas edge (after the layout: the
 * outermost tile's vertices are already mapped); 0 none, -1 too long */
/* (2026-11-11, lane menupolish) Copies in drawing order.  UiDrawSpriteMaybe_2929d0 draws
 * every tile twice in place: a black translucent shadow (RGBA 0,0,0,0x33), then the art.
 * The right end's jobs were collected outermost-first (art, then shadow), and all copies of
 * one job were emitted before the next job's, so past the last original tile the shadow
 * lay OVER the art: the frame's top bar went 40 % darker in a hard step at the old 4:3
 * edge's tile (USER 11-11 "a visual break in the top border"; main menu, items, every
 * screen with that frame, both menu positions, 16:9 and wider).  Now the copies go
 * position by position (copy 1 of every job, copy 2 of every job, ..) and, at one
 * position, the jobs in the order their tiles were drawn (shadow, then art), each with its
 * own colour: the continued bar is drawn as the game draws its tiles.
 * RG_LAYOUT_REPEAT_ORDER=0: the old order (for comparisons). */
static int g_repeat_order = -1;
static int g_pin_edge = -1;   /* RG_LAYOUT_PIN_EDGE (menu_sprites) */
static int rep_emit_ordered(rg_layout_xref *xs, const rep_job *jobs0, int nj, float L, float R, uint64_t *val, uint8_t *reg)
{
    rep_job jobs[8];
    int k = 0, ncol = 0;
    const uint8_t *lastcol = NULL;
    if (nj > 8)
        nj = 8;
    memcpy(jobs, jobs0, (size_t)nj * sizeof jobs[0]);
    for (int p = 1; p < nj; p++)                     /* by side, then drawing order (xs index) */
        for (int q = p; q > 0 && (jobs[q].side < jobs[q - 1].side ||
                                  (jobs[q].side == jobs[q - 1].side && jobs[q].o < jobs[q - 1].o)); q--) {
            rep_job t = jobs[q];
            jobs[q] = jobs[q - 1];
            jobs[q - 1] = t;
        }
    if (g_scan_primq) {
        memcpy(&val[k], g_scan_primq, 8);
        reg[k++] = 0x00;
    }
    for (int c = 1; c < 64; c++) {
        int any = 0;
        for (int i = 0; i < nj; i++) {
            rg_layout_xref *a = &xs[jobs[i].o], *b = &xs[jobs[i].o + 1];
            rg_layout_xref *l = (float)*a->x <= (float)*b->x ? a : b, *r = l == a ? b : a;
            float ml = (float)*l->x, mr = (float)*r->x, tw = mr - ml;
            if (tw < 16.0f)
                continue;
            float xa = jobs[i].side ? mr + (float)(c - 1) * tw : ml - (float)c * tw;
            if (jobs[i].side ? xa >= R : xa + tw <= L)
                continue;
            any = 1;
            if (b->col && g_scan_rgbaq && b->col != lastcol &&
                (!lastcol || memcmp(b->col, lastcol, 8) != 0)) {
                if (k + 1 > MAXAD)
                    return -1;
                memcpy(&val[k], b->col, 8);          /* a sprite takes its second vertex's colour */
                reg[k++] = 0x01;
                lastcol = b->col;
                ncol++;
            }
            if (k + 4 + 1 > MAXAD)
                return -1;
            for (int e = 0; e < 2; e++) {            /* the original write order: a first */
                rg_layout_xref *s0 = e == 0 ? a : b;
                float xv = s0 == l ? xa : xa + tw;
                uint64_t t, xyz;
                memcpy(&t, s0->tc, 8);
                memcpy(&xyz, s0->x, 8);
                xyz = (xyz & ~(uint64_t)0xFFFF) | ((unsigned)(xv < 0.0f ? 0.0f : xv > 65535.0f ? 65535.0f : xv + 0.5f) & 0xFFFF);
                val[k] = t;
                reg[k++] = ((uint8_t *)s0->tc)[8];
                val[k] = xyz;
                reg[k++] = ((uint8_t *)s0->x)[8];
            }
        }
        if (!any)
            break;
    }
    if (ncol) {                                      /* the packet's last colour, as it was */
        memcpy(&val[k], g_scan_rgbaq, 8);
        reg[k++] = 0x01;
    }
    return k > (g_scan_primq ? 1 : 0) ? k : 0;
}

static int rep_emit(rg_layout_xref *xs, const rep_job *jobs, int nj, float L, float R, uint64_t *val, uint8_t *reg)
{
    int k = 0, ncol = 0;
    if (g_repeat_order < 0) {
        const char *e = getenv("RG_LAYOUT_REPEAT_ORDER");
        g_repeat_order = !(e && *e == '0');
    }
    if (g_repeat_order)
        return rep_emit_ordered(xs, jobs, nj, L, R, val, reg);
    if (g_scan_primq) {
        memcpy(&val[k], g_scan_primq, 8);
        reg[k++] = 0x00;
    }
    for (int i = 0; i < nj; i++) {
        rg_layout_xref *a = &xs[jobs[i].o], *b = &xs[jobs[i].o + 1];
        rg_layout_xref *l = (float)*a->x <= (float)*b->x ? a : b, *r = l == a ? b : a;
        rg_layout_xref *kv = b;                      /* a sprite takes its second vertex's colour */
        float ml = (float)*l->x, mr = (float)*r->x, tw = mr - ml;
        if (tw < 16.0f)
            continue;
        if (kv->col && g_scan_rgbaq) {
            if (k + 1 > MAXAD)
                return -1;
            memcpy(&val[k], kv->col, 8);
            reg[k++] = 0x01;
            ncol++;
        }
        for (int c = 1; c < 64; c++) {
            float xa = jobs[i].side ? mr + (float)(c - 1) * tw : ml - (float)c * tw;
            if (jobs[i].side ? xa >= R : xa + tw <= L)
                break;
            if (k + 4 + 1 > MAXAD)
                return -1;
            for (int e = 0; e < 2; e++) {            /* the original write order: a first */
                rg_layout_xref *s0 = e == 0 ? a : b;
                float xv = s0 == l ? xa : xa + tw;
                uint64_t t, xyz;
                memcpy(&t, s0->tc, 8);
                memcpy(&xyz, s0->x, 8);
                xyz = (xyz & ~(uint64_t)0xFFFF) | ((unsigned)(xv < 0.0f ? 0.0f : xv > 65535.0f ? 65535.0f : xv + 0.5f) & 0xFFFF);
                val[k] = t;
                reg[k++] = ((uint8_t *)s0->tc)[8];
                val[k] = xyz;
                reg[k++] = ((uint8_t *)s0->x)[8];
            }
        }
    }
    if (ncol) {                                      /* the packet's last colour, as it was */
        memcpy(&val[k], g_scan_rgbaq, 8);
        reg[k++] = 0x01;
    }
    return k > (g_scan_primq ? 1 : 0) ? k : 0;
}

/* Menu position (lane menuleft 2026-11-10, USER: "in-game menus aligned with the left side";
 * docs/WIDESCREEN.md "Menu position").  graphics.menu_position (rg_layout_set_menu_position):
 * where the full-screen menus' 4:3 block (stage 3 menu tasks) sits in the wide canvas:
 * left (default; flush with the canvas's left edge, or graphics.menu_margin percent of the
 * canvas width in, at most centred; the background strips then fill the right) or centre (the
 * stage 3 layout: this code path is the old one, unchanged; Original).  Tasks registered with
 * rg_layout_menu_centred_task (help sheets, battle results: overlays over the scene) stay
 * centred.  $RG_MENU_LEFT overrides it (tests / comparisons): 0 centre, 1 left (A), 2 left +
 * $RG_MENU_LEFT_MARGIN % (C, default 5), 3 panels left with the background tiles centred (B,
 * the rejected prototype: the portrait circle and panel shadows separate).
 * x' = left + off + (x - left) * s, off = the block's left edge in the canvas. */
static int g_mpos_left;            /* the setting: 1 = left */
static float g_mpos_margin;        /* the setting: margin (fraction of the canvas width) */
static int g_mleft_env = -2;       /* $RG_MENU_LEFT: -1 unset, else 0..3 */
static float g_mleft_env_margin;
static int g_menu_ctr;             /* this packet's task stays centred */
#define MAXCTR 8
static const void *g_ctr_task[MAXCTR];
static int g_nctr;

void rg_layout_set_menu_position(int left, float margin)
{
    g_mpos_left = left != 0;
    g_mpos_margin = margin < 0.0f ? 0.0f : margin > 0.5f ? 0.5f : margin;
}

void rg_layout_menu_centred_task(const void *fn)
{
    for (int i = 0; i < g_nctr; i++)
        if (g_ctr_task[i] == fn)
            return;
    if (fn && g_nctr < MAXCTR)
        g_ctr_task[g_nctr++] = fn;
}

static int menu_ctr_task(const void *t)
{
    for (int i = 0; i < g_nctr; i++)
        if (g_ctr_task[i] == t)
            return 1;
    return 0;
}

/* 0 centre, 1 left, 2 left + margin, 3 B (env only) */
static int mleft_mode(float *margin)
{
    if (g_mleft_env == -2) {
        const char *e = getenv("RG_MENU_LEFT");
        g_mleft_env = e && *e >= '0' && *e <= '3' ? *e - '0' : -1;
        e = getenv("RG_MENU_LEFT_MARGIN");
        g_mleft_env_margin = (e && *e ? (float)atof(e) : 5.0f) / 100.0f;
    }
    if (g_mleft_env >= 0) {
        *margin = g_mleft_env_margin;
        return g_mleft_env;
    }
    *margin = g_mpos_margin;
    return g_mpos_left ? (g_mpos_margin > 0.0f ? 2 : 1) : 0;
}

/* the 4:3 menu block's left edge in the canvas (same units as w) */
static float menu_off(int m, float margin, float w, float s)
{
    float slack = (1.0f - s) * w, off = 0.0f;
    if (m == 2) {
        off = margin * w;
        if (off > 0.5f * slack) off = 0.5f * slack;
    }
    return off;
}

/* a menu piece's X (bg: a background tile, which mode 3 leaves centred) */
static float menu_map(float x, float left, float w, float s, int bg)
{
    float margin;
    int m = mleft_mode(&margin);
    if (m == 0 || g_menu_ctr || (m == 3 && bg))
        return rg_layout_map(x, RG_ANCHOR_CENTER, left, w, s);
    return left + menu_off(m, margin, w, s) + (x - left) * s;
}

/* 3D drawn by a menu task (lane froglog 2026-11-11; docs/WIDESCREEN.md "Menu 3D models").
 * A menu's models (the Frog Log frog, item / weapon previews, ...) are projected about the
 * screen centre X of the camera view packet their task writes (the screen matrix's
 * translation ox, GS pixels, 2048 = the frame's centre), with the wide (Hor+) projection: a
 * model is already squeezed by s about ox, so it stays with a menu laid out about the centre
 * (stage 3) when ox is the centre.  With the menu block elsewhere (menu_position left) it was
 * left behind: centred on the canvas, away from its panels (the frog left its speech bubble at
 * 21:9).  Now, while a stage 3 menu task (not a centred one) writes a view packet, ox goes
 * where the task's 2D puts that X (menu_map: the same block offset); the projection's screen
 * rows and the inverse translation follow.  RG_LAYOUT_MENU_3D=0: as before. */
static int g_menu3d = -1;
float rg_layout_menu_view_x(float ox)
{
    if (!g_active || !(g_s < 0.999f) || g_depth <= 0 || g_depth > MAXDEPTH)
        return ox;
    if (g_menu3d < 0) {
        const char *e = getenv("RG_LAYOUT_MENU_3D");
        g_menu3d = !(e && *e == '0');
    }
    const void *t = g_task[g_depth - 1];
    if (!g_menu3d || !t || !menu_task(t) || menu_ctr_task(t))
        return ox;
    float margin;
    int m = mleft_mode(&margin);
    const float left = 2048.0f - 256.0f, w = 512.0f;
    if (m == 0)
        return ox;                       /* centre: the stage 3 layout (Original), unchanged */
    return left + menu_off(m, margin, w, g_s) + (ox - left) * g_s;   /* = menu_map */
}

/* the shift the current menu task's last view packet got (0 none): the offscreen composite
 * (ModelDrawOffscreenCompositeMaybe_16aac0 override) clears and copies a model back about the
 * screen centre from its box (CameraSetView_156200's m2D0 has no screen translation), so its
 * rectangle takes the same shift as the model drawn into it */
float rg_layout_view_dx(void)
{
    if (!g_active || g_depth <= 0 || g_depth > MAXDEPTH || !g_vdx_task || g_task[g_depth - 1] != g_vdx_task)
        return 0.0f;
    return g_vdx;
}

void rg_layout_view_packet(void *pkt)
{
    if (!pkt || !g_active)
        return;
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    float *q = (float *)pkt;            /* VU qw n = packet qw n + 1 (qw 0: the DMA / VIF tags) */
    float ox = q[64];                   /* packet qw 13..16 = the screen matrix (columns): m[12] */
    float nx = rg_layout_menu_view_x(ox);
    float dx = nx - ox;
    g_vdx_task = g_depth > 0 && g_depth <= MAXDEPTH ? g_task[g_depth - 1] : NULL;
    g_vdx = dx;
    if (!(dx != 0.0f))
        return;
    /* packet qw 5..8 = screen x clip (P1, columns; w = the clip w): GS x = x / w, so x += dx * w */
    for (int c = 0; c < 4; c++)
        q[20 + 4 * c] += dx * q[20 + 4 * c + 3];
    q[64] = nx;                         /* the screen matrix's translation */
    q[76] -= dx;                        /* packet qw 19 = -translation */
    if (g_log)
        fprintf(g_log, "  view3d: ox=%g -> %g task=%p\n", ox, nx, g_vdx_task);
}

/* Wide content (rg_layout_wide_begin / _end, the Revelation board's cells): menu sprites past
 * the 4:3 screen's right edge are shown up to the canvas's right edge instead of hidden.  The
 * right limit in the game's (4:3) coordinates: the original x that maps to the canvas edge. */
static int g_wide;
static int g_wide_env = -2;   /* $RG_REV_WIDE: -1 unset, 0 off, 1 cells, 2 cells + scroll window */
static int g_wide_set;        /* graphics.revelation_wide (rg_layout_set_revelation_wide): 2 or 0 */
void rg_layout_set_revelation_wide(int on) { g_wide_set = on ? 2 : 0; }
/* mode 2: a board was drawn this / the last frame: the board's cursor and balloons (small
 * widgets of the menu, drawn outside the bracket) are kept up to the canvas edge too */
void rg_layout_wide_begin(void)
{
    g_wide = rg_layout_wide_mode() >= 1;
    g_wide_now |= g_wide;
}
void rg_layout_wide_end(void) { g_wide = 0; }
int rg_layout_wide_mode(void)
{
    if (g_wide_env == -2) {
        const char *e = getenv("RG_REV_WIDE");
        g_wide_env = e && *e >= '0' && *e <= '2' ? *e - '0' : -1;
    }
    return g_wide_env >= 0 ? g_wide_env : g_wide_set;
}
static float wide_right(float left, float w, float s)
{
    float margin;
    int m = mleft_mode(&margin);
    float off = m == 0 || g_menu_ctr ? 0.5f * (1.0f - s) * w : menu_off(m, margin, w, s);
    return left + (w - off) / s;
}
/* screen pixels (of the 4:3 frame) visible right of the 4:3 screen for wide content now:
 * 0 at 4:3, with the layout off or with RG_REV_WIDE below 2 */
int rg_layout_wide_extra(void)
{
    if (rg_layout_wide_mode() < 2 || !g_active || !(g_s < 0.999f))
        return 0;
    float r = wide_right(0.0f, 512.0f, g_s) - 512.0f;
    /* at most the board's whole scroll range (0x222): beyond (32:9) the board fits unscrolled */
    if (r > 546.0f) r = 546.0f;
    return r > 0.0f ? (int)r : 0;
}

static void menu_sprites(void *pkt, rg_layout_xref *xs, int n, float left, float w, int bg, uint8_t *done)
{
    const float L = left, R = left + w, px = 16.0f;
    /* wide content (rg_layout_wide_begin): sprites are kept up to the canvas's right edge */
    const float RR0 = g_wide ? wide_right(left, w, g_s) : R;
    const float RRs = !g_wide && (g_wide_now || g_wide_last) && rg_layout_wide_mode() >= 2 ? wide_right(left, w, g_s) : RR0;
    const float top = 1824.0f * 16.0f, bot = (1824.0f + RG_LAYOUT_FRAME_H) * 16.0f;
    static uint64_t val[MAXAD];
    static uint8_t reg[MAXAD];
    static uint8_t rep[8192];
    rep_job rj[8];
    strip_job sj[MAXSTRIPS];
    int nst = 0, sides = 0;
    int nstrip0[2] = { g_nstrip[0], g_nstrip[1] };
    strip_opts();
    g_strip_L = L;
    g_strip_R = R;
    int nrj = 0;
    if (!bg && n <= 8192) {
        memset(rep, 0, (size_t)n);
        nrj = rep_find(xs, n, L, w, rep, rj, 8);
    }
    for (int j = 0; j + 1 < n; j++) {
        rg_layout_xref *a = &xs[j], *b = &xs[j + 1];
        if (a->kind || b->kind || a->prim != 6 || b->prim != 6 || (a->vix & 1) || b->vix != a->vix + 1)
            continue;
        done[j] = done[j + 1] = 1;
        if (nrj && rep[j]) {                         /* a tile of a repeated frame strip: whole */
            set_x(a, menu_map((float)*a->x, left, w, g_s, 0));
            set_x(b, menu_map((float)*b->x, left, w, g_s, 0));
            j++;
            continue;
        }
        j++;
        rg_layout_xref *l = (float)*a->x <= (float)*b->x ? a : b, *r = l == a ? b : a;
        float xl = (float)*l->x, xr = (float)*r->x;
        float ya = (float)*a->y, yb = (float)*b->y;
        float sy0 = ya < yb ? ya : yb, sy1 = ya < yb ? yb : ya;
        /* a background tile: at least an eighth of the screen each way */
        int sbg = bg && xr - xl >= 0.125f * w && sy1 - sy0 >= 0.125f * (bot - top);
        float ml = menu_map(xl, left, w, g_s, sbg);
        float mr = menu_map(xr, left, w, g_s, sbg);
        int tck1 = l->tck == 1 && r->tck == 1;
        /* (2026-10-31) the menu's shading layer: one sprite covering exactly the 4:3 screen,
         * drawn over the backdrop with a low-detail texture magnified about 4-5x (every
         * full-screen menu has one: 103..129 texels over the 512-pixel screen; it darkens
         * the screen's edges).  Squeezed with the menu it stopped at the old 4:3 edge, and
         * the brighter backdrop / strips beyond it showed a seam down the whole height
         * (tools/wide/seamscan.py).  It has no cut-outs to keep on the panels, so it is laid
         * over the whole canvas instead: left where it is (the frame is the canvas), it
         * shades the canvas edges as it shaded the 4:3 screen's.  RG_LAYOUT_VIGNETTE=0: as
         * before. */
        if (sbg && bg == 1 && g_menu_vignette && tck1 && xl <= L + px && xr >= R - px && sy0 <= top + px &&
            sy1 >= bot - px && xr - xl <= w + 2.0f * px &&
            16.0f * fabsf(tc_get(r) - tc_get(l)) <= 0.3f * (xr - xl)) {
            if (g_log)
                fprintf(g_log, "  vignette: u=%g..%g over the canvas\n", tc_get(l), tc_get(r));
            continue;
        }
        const float RR = xr - xl < 0.125f * w ? RRs : RR0;   /* (wide content, rg_layout_wide_begin) */
        if (!sbg && (xr <= L + px || xl >= RR - px)) { /* hidden at 4:3: keep it hidden */
            set_x(l, ml);
            set_x(r, ml);
            continue;
        }
        float vis = xr > xl ? ((xr < RR ? xr : RR) - (xl > L ? xl : L)) / (xr - xl) : 1.0f;
        int tcok = l->tck && r->tck && l->tck == r->tck;
        if (!sbg && (vis < 0.5f || xr - xl < 0.25f * w)) {   /* mostly hidden / small: clip to the screen */
            float ul = tcok ? tc_get(l) : 0.0f, ur = tcok ? tc_get(r) : 0.0f;
            float cl = xl < L ? L : xl, cr = xr > RR ? RR : xr;
            if (tcok && xr > xl) {
                float nl = ul + (ur - ul) * (cl - xl) / (xr - xl);
                float nr = ul + (ur - ul) * (cr - xl) / (xr - xl);
                tc_set(l, nl);
                if (r->tc != l->tc)
                    tc_set(r, nr);
            } else if (!tcok && (l->tck || r->tck)) {
                cl = cr = xl;                        /* cannot cut its texture: hide it */
            }
            set_x(l, menu_map(cl, left, w, g_s, 0));
            set_x(r, menu_map(cr, left, w, g_s, 0));
            continue;
        }
        if (!sbg) {                                  /* bleeding off an edge: pin it there */
            if (xl < L - px && ml > L) ml = L;
            if (xr > R + px && mr < R) mr = R;
            /* (2026-11-11, lane menupolish) a bar ending exactly at the 4:3 screen's right
             * edge looks the same at 4:3 as one bleeding past it, and the frame draws the
             * two kinds side by side: the transporter / save screens' header box fill
             * (x 158..512) and its inner line (170..511) stopped at the old edge while the
             * box's border lines (173..535, 174..517) were pinned to the canvas edge (a
             * navy box with its outline running on alone, 21:9 left most visibly).  A wide
             * plain bar (>= a quarter of the screen wide, the rule above; see `bar` below)
             * reaching the right edge within 1 px is pinned like one bleeding off it.
             * RG_LAYOUT_PIN_EDGE=0: off. */
            if (g_pin_edge < 0) {
                const char *e = getenv("RG_LAYOUT_PIN_EDGE");
                g_pin_edge = !(e && *e == '0');
            }
            /* the same at the left edge: battle results' header rule is two halves, 0..256
             * and 256..512, and its "Acquired Items" box lines 271..513; centred they
             * stopped at the old 4:3 edges in mid-screen */
            /* a plain bar: at least 4x as wide as tall (not a panel / the portrait ring,
             * which slides past 512 while the main menu opens) and a low-detail texture
             * (at most 1 texel per 4 pixels: a fill or rule, safe to stretch; the shop's /
             * Galaxy Map's titles start at x 0 with their lettering 1:1 and stay as they are) */
            float du = tcok ? fabsf(tc_get(r) - tc_get(l)) : 0.0f;
            int bar = g_pin_edge && 4.0f * (sy1 - sy0) <= xr - xl && 16.0f * 4.0f * du <= xr - xl;
            if (bar && xr >= R - px && xr <= R + px && xl > L + px && mr < R) mr = R;
            if (bar && xl >= L - px && xl <= L + px && xr < R - px && ml > L) ml = L;
            set_x(l, ml);
            set_x(r, mr);
            continue;
        }
        set_x(l, ml);
        set_x(r, mr);
        /* background piece: strips over the canvas it no longer covers */
        if (!(tcok && l->tck == 1 && l->ad && r->ad) || !(mr > ml))
            continue;
        float vy0 = sy0 > top ? sy0 : top, vy1 = sy1 < bot ? sy1 : bot;
        float ul = tc_get(l), ur = tc_get(r), kx = (ur - ul) / (mr - ml);
        float umin = ul < ur ? ul : ur, umax = ul < ur ? ur : ul;
        for (int side = 0; side < 2; side++) {
            float g = side == 0 ? ml - L : R - mr;
            if (g < px || vy1 - vy0 < px || (side == 0 ? xl > L + px : xr < R - px) || nst >= MAXSTRIPS ||
                strip_covered(side, g_pk_task, vy0, vy1, side == 0 ? ml : mr) >= 0.5f)
                continue;
            float uin = side == 0 ? ul : ur;                       /* at the piece's edge */
            float dir = side == 0 ? kx : -kx;                      /* texels per unit, outward */
            float uout = uin + g * dir;                            /* mirrored at the canvas edge */
            /* at most the outer 30 % of the art is mirrored (stretched beyond, at 32:9):
             * deeper in, art has cut-outs (the main menu's portrait circle) that would
             * show the clear through the strip */
            /* Beyond the cap the strip mirrors back and forth within it (2026-10-31: it
             * used to stretch the cap's last texel, horizontal streaks over half the side at
             * 21:9; RG_LAYOUT_STRIPS=stretch for that) */
            float cap = 0.3f * (umax - umin), pcap = 0.0f;
            if (bg == 2)   /* an overlay (over a scene capture): its edge column stretched */
                uout = uin + 0.5f * (dir > 0 ? 1.0f : -1.0f);
            else if (g_strip_mode == 1 && (g * dir > 6.0f || g * dir < -6.0f))
                uout = uin + (dir > 0 ? 6.0f : -6.0f);             /* smear: the outer 6 texels */
            else if (g * dir > cap || g * dir < -cap) {
                if (g_strip_mode == 0 && cap >= 4.0f)
                    pcap = cap;                                    /* uout stays unbounded */
                else
                    uout = uin + (dir > 0 ? cap : -cap);
            }
            if (pcap <= 0.0f) {
                if (uout < umin) uout = umin;
                if (uout > umax) uout = umax;
            }
            /* a sprite of this packet drawn over an earlier one's rows replaces its strip
             * (the main menu's backdrop: a translucent black shadow sprite, then the art) */
            for (int q = 0; q < nst; q++) {
                float o0 = sj[q].y0 > vy0 ? sj[q].y0 : vy0, o1 = sj[q].y1 < vy1 ? sj[q].y1 : vy1;
                if (sj[q].side == side && o1 - o0 >= 0.5f * (sj[q].y1 - sj[q].y0))
                    sj[q--] = sj[--nst];
            }
            sj[nst++] = (strip_job){ a, l, r, ml, mr, uin, uout, vy0, vy1, pcap, side };
        }
    }
    if (nrj) {
        int kr = rep_emit(xs, rj, nrj, L, R, val, reg);
        int okr = kr > 0 && append_ad(pkt, val, reg, kr);
        if (g_log)
            fprintf(g_log, "  repeat: %d row ends continued, %d qwords%s\n", nrj, kr, okr ? "" : " (not appended)");
    }
    if (!nst)
        return;
    for (int i = 0; i < nst; i++) {
        strip_note(sj[i].side, g_pk_task, sj[i].y0, sj[i].y1, sj[i].side == 0 ? sj[i].ml : sj[i].mr);
        sides |= 1 << sj[i].side;
    }
    /* faded bands need a modulating texture function (TEX0 TFX 0) and the A+D colours */
    int fade = bg == 1 && g_strip_fade > 0 && ((g_scan_tex0 >> 35) & 3) == 0 && g_scan_rgbaq;
    for (int i = 0; fade && i < nst; i++)
        if (!(sj[i].a == sj[i].l ? sj[i].r : sj[i].l)->col)
            fade = 0;
    /* bands: as many as fit (up to 16: steps of ~4 % at the default fade) */
    int turns = 0;
    for (int i = 0; i < nst; i++)
        turns += strip_turns(&sj[i]);
    int nb = (MAXAD - 2 - 4 * turns) / (5 * nst);
    if (nb > 16) nb = 16;
    if (nb < 4) fade = 0;
    int k = fade ? strip_emit(sj, nst, nb, val, reg) : -1;
    int ok = k > 0 && append_ad(pkt, val, reg, k);
    if (!ok) {                                       /* no room for the bands: one strip each */
        fade = 0;
        k = strip_emit(sj, nst, 1, val, reg);
        ok = k > 0 && append_ad(pkt, val, reg, k);
    }
    if (ok) {
        g_st.strips++;
        if (g_log) {
            fprintf(g_log, "  strips: %d qwords, sides %d%s\n", k, sides, fade ? " (faded)" : "");
            static int dump = -1;
            if (dump < 0) {
                const char *e = getenv("RG_LAYOUT_LOG_STRIPS");
                dump = e && *e == '1';
            }
            for (int i = 0; dump && i < k; i++)
                fprintf(g_log, "    %02x %016llx\n", reg[i], (unsigned long long)val[i]);
        }
    } else {
        g_nstrip[0] = nstrip0[0];                    /* not drawn: another piece may fill them */
        g_nstrip[1] = nstrip0[1];
    }
}

int rg_layout_packet(void *pkt, const void *caller)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    static rg_layout_xref xs[8192];
    if (!g_active && !g_detect)
        return 0;
    log_open();
    uint8_t *base = PK_PTR(uint8_t, pkt, PK_BASE);
    uint8_t *cur = PK_PTR(uint8_t, pkt, PK_CUR);
    if (!base || cur <= base)
        return 0;
    g_st.packets++;
    float cx = (float)*(int32_t *)((uint8_t *)pkt + PK_CX);
    float w = (float)*(int32_t *)((uint8_t *)pkt + PK_W);
    if (w <= 0.0f) {                       /* origin mode without a screen: assume 512 wide */
        w = 512.0f * 16.0f;
        cx = 2048.0f * 16.0f;
    }
    float left = cx - 0.5f * w;
    float cy = (float)*(int32_t *)((uint8_t *)pkt + PK_CY);
    float h = (float)*(int32_t *)((uint8_t *)pkt + PK_H);
    if (h <= 0.0f) {
        h = RG_LAYOUT_FRAME_H * 16.0f;
        cy = 2048.0f * 16.0f;
    }
    float top = cy - 0.5f * h;
    g_scan_psm = -1;
    g_scan_fbp = g_scan_fbw = -1;
    g_scan_tbp = -1;
    g_scan_tc = NULL;
    g_scan_tck = 0;
    g_scan_ncol = 0;
    g_scan_primq = NULL;
    g_scan_prim = 0xFF;
    g_scan_vix = 0;
    g_scan_ad = 0;
    g_scan_tex0 = 0;
    g_scan_rgbaq = NULL;
    int n = scan_packet(base, cur, xs, (int)(sizeof xs / sizeof xs[0]));
    if (n > (int)(sizeof xs / sizeof xs[0]))
        n = (int)(sizeof xs / sizeof xs[0]);
    float x0 = 1e30f, x1 = -1e30f, y0 = 1e30f, y1 = -1e30f;
    int nv = 0;
    for (int j = 0; j < n; j++)
        if (xs[j].kind == 0) {
            float v = (float)*xs[j].x, u = (float)*xs[j].y;
            if (v < x0) x0 = v;
            if (v > x1) x1 = v;
            if (u < y0) y0 = u;
            if (u > y1) y1 = u;
            nv++;
        }
    if (nv == 0) {
        /* a scissor-only packet (FontSetScissor, MesWinSetScissor): its rectangle stands
         * for the element, so it moves with the window it clips */
        for (int j = 0; j < n && nv == 0; j++)
            if (xs[j].kind == 1) {
                uint64_t sc = *xs[j].sc;
                x0 = left + 16.0f * (float)(sc & 0x7FF);
                x1 = left + 16.0f * (float)(((sc >> 16) & 0x7FF) + 1);
                y0 = 16.0f * (float)((sc >> 32) & 0x7FF) + 1824.0f * 16.0f;
                y1 = 16.0f * (float)(((sc >> 48) & 0x7FF) + 1) + 1824.0f * 16.0f;
                nv = -1;
            }
        if (nv == 0)
            return 0;
    }
    g_st.verts += nv > 0 ? (unsigned)nv : 0u;
    uintptr_t task = g_depth > 0 && g_depth <= MAXDEPTH ? (uintptr_t)g_task[g_depth - 1] : 0;
    uint32_t ck = mix(mix(2166136261u, (uint32_t)task), (uint32_t)(uintptr_t)caller);
    /* a follow_begin bracket's packets count apart: the menu page's packets, all with the
     * followed anchor, would otherwise shift the n-th-packet identities (and so the filed
     * anchors) of the same task's other packets (the opening's sparkles) frame to frame */
    if (g_follow)
        ck = mix(ck, 0x666F6C6Cu);
    uint32_t key = mix(ck, ordinal(ck ? ck : 1));
    if (!key)
        key = 1;
    const char *why = NULL;
    float edge = 4.0f * 16.0f;
    unsigned zt = *((uint8_t *)pkt + PK_ZTEST);
    /* the frame's draw buffer: the FRAME of the first packet covering the whole screen
     * (DrawListClearScreen); packets drawn into other buffers (minimap tiles, character
     * composites, blur / glare work buffers, texture animations) are off-screen passes */
    if (!g_screen_known && g_scan_fbp >= 0 && x0 <= left + edge && x1 >= left + w - edge &&
        (y1 - y0) >= 0.9f * RG_LAYOUT_FRAME_H * 16.0f) {
        g_screen_fbp = g_scan_fbp;
        g_screen_known = 1;
    }
    /* (cardwide) the title phase's memory-card background: the screen is up (at full
     * opacity: the aspect policy then shows it wide, rg_aspect.c) and its task is a menu
     * task, laid out like the in-game save screen (stage 3) */
    if (g_card_bg && card_wide_on()) {
        /* up once fully opaque (it fades in under the screen fade); then up while it is drawn
         * at all, so a cancel's fade-out stays wide until the background is gone (no pop
         * back to the pillarbox over a half-faded screen) */
        if (g_card_alpha >= 0.999f || (g_card_last > 0 && g_card_alpha > 0.001f))
            g_card_now++;
        if (task) {
            g_cover_now++;
            menu_task_add((const void *)task);
        }
    }
    int menu = 0;   /* stage 3: part of a full-screen menu (laid out whole, centred) */
    if (g_scan_fbp >= 0 && g_scan_fbp != g_screen_fbp) {
        why = "offscreen";
    } else if (g_about) {
        why = "about";
        g_st.about++;
    } else if (g_suppress) {
        why = "suppressed";
        g_st.suppressed++;
    } else if (nv > 0 && (zt & 1) && ((zt >> 1) & 3) >= 2) {
        /* (not for a scissor-only packet: it draws nothing, its Z state is whatever the
         * shared GsPkt last had -- the item grid's selection-frame scissor
         * (GsPktSetScissor_28c2e0 after a Z-tested draw) was left unmoved while the frame's
         * dashes were laid out, so they were clipped to the wrong cell: USER 1030a) */
        why = "ztest";
        g_st.ztest++;
    } else if ((x0 <= left + edge && x1 >= left + w - edge) ||
               ((y1 - y0) >= 0.5f * RG_LAYOUT_FRAME_H * 16.0f &&
                (x1 - x0 >= RG_LAYOUT_FULL * w ||
                 (x1 - x0 >= 0.4f * w && (x0 < left - edge || x1 > left + w + edge))))) {
        /* covers the screen: spans it edge to edge (fades, letterbox bars, backgrounds), or
         * a tall background piece as wide as the screen / running past its edge */
        why = "full";
        /* a full-screen direct-colour picture drawn by a task: a capture of the scene
         * (help sheets over a battle draw one under the sheet) */
        if (task && (g_scan_psm == 0x00 || g_scan_psm == 0x01 || g_scan_psm == 0x02) &&
            x0 <= left + edge && x1 >= left + w - edge && (y1 - y0) >= 0.9f * RG_LAYOUT_FRAME_H * 16.0f)
            g_capture_task = task;
        g_st.full++;
        /* a full-screen menu background: an indexed-colour UI texture covering the visible
         * screen, drawn by a game task (the field's screen-effect passes sample 32/24/16-bit
         * render targets) -> its task is a menu task (stage 3; stage 2 pillarboxed the
         * whole screen at 4:3 instead, now only with RG_LAYOUT_MENU_PILLARBOX=1) */
        if (task && w == 512.0f * 16.0f && x0 <= left + edge && x1 >= left + w - edge &&
            (y1 - y0) >= 0.9f * RG_LAYOUT_FRAME_H * 16.0f && indexed_psm(g_scan_psm)) {
            g_cover_now++;
            menu_task_add((const void *)task);
        }
        /* stage 3: a menu task's indexed-colour background pieces (the covering one
         * above included) are part of the menu: squeezed with its panels so the holes
         * stay on them (background tiles running past a screen edge too: their
         * vertices outside the screen are pinned to the canvas edge below); fades, dims
         * and scene captures (32/24/16-bit or untextured) keep covering the canvas */
        if (menu_task((const void *)task) && indexed_psm(g_scan_psm)) {
            why = NULL;
            menu = 1;
        }
    } else if (!why && menu_task((const void *)task)) {
        menu = 1;
    }
    if (!g_active)
        return 0;                            /* detection only (pillarboxed screen) */
    /* a UI scale without the X squeeze (4:3, the stretch layout): full-screen menus fill
     * the height already and keep their size (nor is their frame clear touched) */
    if (menu && !(g_s < 0.999f))
        return 0;
    /* stage 3: on a full-screen menu the frame clear (an untextured packet covering the
     * screen, drawn outside any task: DrawListClearScreen) is drawn black.  At 4:3 the
     * menu covers it entirely; on the wide canvas it shows only where the centred menu's
     * background does not reach (the edges of the canvas at 21:9), black like a
     * pillarbox instead of the field's clear colour. */
    if (g_s < 0.999f && !g_clear_done && !task && g_scan_psm < 0 && g_cover_last > 0 && x0 <= left + edge && x1 >= left + w - edge &&
        (y1 - y0) >= 0.9f * RG_LAYOUT_FRAME_H * 16.0f) {
        for (int j = 0; j < g_scan_ncol; j++) {
            uint8_t *c = g_scan_col[j];
            int st = g_scan_colstep[j];
            c[0] = 0;
            c[st] = 0;
            c[2 * st] = 0;
        }
        why = "clear";
        g_clear_done = 1;
    }
    int anchor = RG_ANCHOR_NONE;
    int yanchor = RG_ANCHOR_NONE;   /* UI scale (g_uon): Y anchor, the group's scale */
    float ue = 1.0f;
    int from_prev = 0;
    if (task && (menu || !why))
        drawn_add((const void *)task);
    if (menu) {
        /* stage 3: the whole menu is one 4:3 element in the middle of the wide canvas */
        anchor = RG_ANCHOR_CENTER;
        from_prev = 1;
        g_st.menu++;
        g_menu_ctr = menu_ctr_task((const void *)task);   /* menu position: this task stays centred */
    } else if (!why) {
        /* the element's extent when known ahead (rg_layout_elem_begin: a message window's
         * text block): a partly typed-out line is anchored and grouped as the whole block; a
         * scissor-only packet (the window's clip before any glyph shows) stands for it alone */
        float ex0 = x0, ex1 = x1;
        if (g_elem) {
            float h0 = left + 16.0f * g_elem_x0, h1 = left + 16.0f * g_elem_x1;
            if (nv < 0) {
                ex0 = h0;
                ex1 = h1;
            }
            if (h0 < ex0) ex0 = h0;
            if (h1 > ex1) ex1 = h1;
        }
        anchor = tab_get(g_prev, key, &yanchor, &ue);
        int forced = g_follow ? g_fa : -1;
        if (g_follow) {
            if (g_fu_n++ == 0) {
                g_fu_x0 = ex0; g_fu_x1 = ex1; g_fu_y0 = y0; g_fu_y1 = y1; g_fu_w = w;
            } else {
                if (ex0 < g_fu_x0) g_fu_x0 = ex0;
                if (ex1 > g_fu_x1) g_fu_x1 = ex1;
                if (y0 < g_fu_y0) g_fu_y0 = y0;
                if (y1 > g_fu_y1) g_fu_y1 = y1;
            }
        }
        if (forced > RG_ANCHOR_NONE) {
            anchor = forced;
            g_st.followed++;
        }
        from_prev = anchor >= 0;
        if (anchor < 0) {
            /* a packet new this frame (no anchor filed under its identity): the anchor of a
             * packet of its group drawn before it this frame that it overlaps (a new line
             * under the lines of a paragraph, text in a window drawn just before), which is
             * what the group's anchor will be next frame; else its own rectangle */
            const float slack = 4.0f * 16.0f;
            int first = g_depth > 0 && g_depth <= MAXDEPTH ? g_mark[g_depth - 1] : 0;
            for (int i = g_npk - 1; i >= first && anchor < 0 && !g_elem; i--) {
                const pkrec *b = &g_pk[i];
                if (ex0 <= b->x1 + slack && b->x0 <= ex1 + slack && y0 <= b->y1 + slack && b->y0 <= y1 + slack &&
                    b->anchor > RG_ANCHOR_NONE) {
                    anchor = b->anchor;
                    yanchor = b->yanchor;
                    ue = b->u;
                    g_st.inherited++;
                }
            }
            if (anchor < 0) {
                /* an element extent known ahead is a group: the cluster rule its next frame gets
                 * (a window as wide as the screen centred, not left untouched for one frame) */
                anchor = g_elem ? rg_layout_cluster_anchor(ex0, ex1, left, w) : rg_layout_anchor(ex0, ex1, left, w);
                yanchor = RG_ANCHOR_NONE;
                ue = 1.0f;
                if (g_uon) {
                    yanchor = rg_layout_cluster_anchor(y0, y1, top, h);
                    ue = rg_layout_fit_scale(g_u, anchor, yanchor, ex0, ex1, y0, y1, left, w, top, h, g_s);
                }
            }
        }
        if (!g_uon) {
            yanchor = RG_ANCHOR_NONE;
            ue = 1.0f;
        }
        if (g_npk < MAXPK) {
            pkrec *k = &g_pk[g_npk++];
            k->key = key;
            k->x0 = ex0; k->x1 = ex1; k->y0 = y0; k->y1 = y1;
            k->left = left; k->w = w;
            k->top = top; k->h = h;
            k->anchor = anchor;
            k->yanchor = yanchor;
            k->u = ue;
            k->forced = forced > RG_ANCHOR_NONE ? forced : 0;
        }
    }
    float u0 = 1e30f, u1 = -1e30f;   /* texture coordinate range (U texels / S) */
    for (int j = 0; j < n; j++)
        if (xs[j].kind == 0 && xs[j].tck) {
            float u = tc_get(&xs[j]);
            if (u < u0) u0 = u;
            if (u > u1) u1 = u;
        }
    if (g_log)
        fprintf(g_log, "%d pk task=%08lx caller=%08lx x=%.1f..%.1f y=%.1f..%.1f n=%d psm=%d fbp=%d/%d %s%s tbp=%d u=%g..%g%s\n", g_field,
                (unsigned long)(task ? task - image_base() : 0), (unsigned long)((uintptr_t)caller - image_base()),
                (x0 - left) / 16.0f, (x1 - left) / 16.0f, y0 / 16.0f, y1 / 16.0f, nv, g_scan_psm, g_scan_fbp, g_scan_fbw,
                why ? why : aname(anchor), menu ? " (menu)" : why || from_prev ? "" : " (own)", g_scan_tbp,
                u0 < 1e29f ? u0 : -1.0f, u0 < 1e29f ? u1 : -1.0f, g_elem && !why ? " elem" : g_follow && !why ? " follow" : "");
    if (g_about && why && why[0] == 'a') {
        /* world-anchored text: about its own projected point (no grouping, no scissor) */
        float a = g_about_px ? left + 16.0f * g_about_x : g_about_x;
        float k = g_about_xy ? g_about_kx : g_uon ? g_s * g_u : g_s;
        float ym = g_about_xy ? top + 16.0f * g_about_y : 0.5f * (y0 + y1);   /* UI scale: Y about the packet's own middle */
        float ky = g_about_xy ? g_about_ky : g_u;
        int doy = g_about_xy ? ky != 1.0f : g_uon;
        g_st.moved++;
        for (int j = 0; j < n; j++)
            if (xs[j].kind == 0) {
                float v = a + ((float)*xs[j].x - a) * k;
                if (v < 0.0f) v = 0.0f;
                if (v > 65535.0f) v = 65535.0f;
                *xs[j].x = (uint16_t)(v + 0.5f);
                if (doy && nv > 0) {
                    float q = ym + ((float)*xs[j].y - ym) * ky;
                    if (q < 0.0f) q = 0.0f;
                    if (q > 65535.0f) q = 65535.0f;
                    *xs[j].y = (uint16_t)(q + 0.5f);
                }
            }
        return k != 1.0f;
    }
    if (anchor == RG_ANCHOR_NONE)
        return 0;
    g_st.moved++;
    float wpx = w / 16.0f;
    /* the X scale: the squeeze times the group's UI scale (exactly g_s without one) */
    float sx = ue != 1.0f ? g_s * ue : g_s;
    int ysc = ue != 1.0f && yanchor != RG_ANCHOR_NONE;
    float hpx = h / 16.0f;
    int tall = (y1 - y0) >= 0.5f * RG_LAYOUT_FRAME_H * 16.0f;
    int pin = !tall;
    /* only a piece mostly on the screen is pinned (one mostly off it, slid out, is not
     * stretched across the side) */
    if (x1 - x0 < 0.25f * w ||
        (x1 > x0 && ((x1 < left + w ? x1 : left + w) - (x0 > left ? x0 : left)) < 0.5f * (x1 - x0)))
        pin = 0;
    static uint8_t done[sizeof xs / sizeof xs[0]];
    memset(done, 0, (size_t)n);
    g_pk_task = (uintptr_t)caller;   /* strips: per drawing function */
    if (menu)
        menu_sprites(pkt, xs, n, left, w,
                     tall && x1 - x0 >= 0.4f * w && indexed_psm(g_scan_psm) ? (g_capture_task == task ? 2 : 1) : 0,
                     done);
    for (int j = 0; j < n; j++) {
        rg_layout_xref *x = &xs[j];
        if (done[j])
            continue;
        if (x->kind == 0) {
            float o = (float)*x->x;
            float v = menu ? menu_map(o, left, w, sx, 0) : rg_layout_map(o, anchor, left, w, sx);
            /* stage 3: a menu piece that bleeds off the screen (title bars, frame
             * strips) keeps reaching the canvas edge: its vertices outside the screen
             * are pinned there (a slight stretch of that piece instead of a gap).  Not
             * the tall background tiles: their art has cut-outs that must stay on the
             * menu's (stretching them shows the clear through the cut-outs) */
            if (menu && pin && o < left - 16.0f && v > left)
                v = left;
            if (menu && pin && o > left + w + 16.0f && v < left + w)
                v = left + w;
            if (v < 0.0f) v = 0.0f;
            if (v > 65535.0f) v = 65535.0f;
            *x->x = (uint16_t)(v + 0.5f);
            if (ysc) {
                float q = rg_layout_map((float)*x->y, yanchor, top, h, ue);
                if (q < 0.0f) q = 0.0f;
                if (q > 65535.0f) q = 65535.0f;
                *x->y = (uint16_t)(q + 0.5f);
            }
        } else {
            /* scissor (window pixels): only a rectangle narrower than the screen moves */
            uint64_t sc = *x->sc;
            float a0 = (float)(sc & 0x7FF), a1 = (float)((sc >> 16) & 0x7FF);
            if (a1 - a0 + 1.0f >= RG_LAYOUT_FULL * wpx)
                continue;
            float b0 = menu ? menu_map(a0, 0.0f, wpx, sx, 0) : rg_layout_map(a0, anchor, 0.0f, wpx, sx);
            float b1 = (menu ? menu_map(a1 + 1.0f, 0.0f, wpx, sx, 0) : rg_layout_map(a1 + 1.0f, anchor, 0.0f, wpx, sx)) - 1.0f;
            if (b0 < 0.0f) b0 = 0.0f;
            if (b1 < b0) b1 = b0;
            sc &= ~((uint64_t)0x7FF | ((uint64_t)0x7FF << 16));
            sc |= (uint64_t)((unsigned)(b0 + 0.5f) & 0x7FF) | ((uint64_t)((unsigned)(b1 + 0.5f) & 0x7FF) << 16);
            if (ysc) {
                /* (window pixels from the frame's top) */
                float c0 = (float)((sc >> 32) & 0x7FF), c1 = (float)((sc >> 48) & 0x7FF);
                float d0 = rg_layout_map(c0, yanchor, 0.0f, hpx, ue);
                float d1 = rg_layout_map(c1 + 1.0f, yanchor, 0.0f, hpx, ue) - 1.0f;
                if (d0 < 0.0f) d0 = 0.0f;
                if (d1 < d0) d1 = d0;
                sc &= ~(((uint64_t)0x7FF << 32) | ((uint64_t)0x7FF << 48));
                sc |= ((uint64_t)((unsigned)(d0 + 0.5f) & 0x7FF) << 32) | ((uint64_t)((unsigned)(d1 + 0.5f) & 0x7FF) << 48);
            }
            *x->sc = sc;
        }
    }
    if (g_log && menu && (x0 < left || x1 > left + w)) {   /* pieces off the 4:3 screen: where they went */
        fprintf(g_log, "  ->");
        for (int j = 0; j < n && j < 24; j++)
            if (xs[j].kind == 0)
                fprintf(g_log, " %.1f%s", ((float)*xs[j].x - left) / 16.0f, xs[j].prim == 6 ? "s" : "");
        fprintf(g_log, "\n");
    }
    return sx != 1.0f;
}

/* stage 3: the main menu's portrait circle (MenuCaptureScreenTex_298810 override).  The
 * game copies the field frame's x 191..446, y 106..361 into a 256x256 texture when the
 * menu opens (src = the downloaded frame, 512 RGBA32 pixels a row, already at row 106).
 * On a wide canvas the frame is anamorphic (Hor+): the 4:3 picture's column x is the wide
 * frame's column 256 + (x - 256) * s.  Resampling that region (linear in x) gives the
 * texture the 4:3 copy would hold, so the circle (squeezed with its menu) shows the
 * party in proportion.  Returns 0 (the game's own copy runs) unless the layout is
 * active. */
int rg_layout_capture_wide(const uint8_t *src, uint8_t *dst)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    if (!g_active || !(g_s < 1.0f) || !src || !dst)
        return 0;
    for (int y = 0; y < 256; y++) {
        const uint8_t *row = src + 0x800 * y;
        for (int x = 0; x < 256; x++) {
            float fx = 256.0f + ((float)(191 + x) + 0.5f - 256.0f) * g_s - 0.5f;
            int i0 = (int)fx;
            float t = fx - (float)i0;
            if (i0 < 0) { i0 = 0; t = 0.0f; }
            if (i0 > 510) { i0 = 510; t = 1.0f; }
            const uint8_t *a = row + 4 * i0, *b = a + 4;
            for (int c = 0; c < 3; c++)
                dst[c] = (uint8_t)((float)a[c] + ((float)b[c] - (float)a[c]) * t + 0.5f);
            dst[3] = 0x80;
            dst += 4;
        }
    }
    g_st.capture++;
    return 1;
}
