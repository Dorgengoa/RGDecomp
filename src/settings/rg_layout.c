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

static float g_s = 1.0f;
static int g_active;
static int g_detect;
static int g_screen_fbp, g_screen_known;   /* this frame's draw buffer (FRAME FBP) */          /* wide canvas: watch for full-screen menus even when pillarboxed */
static unsigned g_cover_now, g_cover_last;   /* menu backgrounds this / the last drawn frame */
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
static int g_strip_mode = -1;   /* RG_LAYOUT_STRIPS: 0 mirror (default), 1 smear (edge band stretched) */
static int g_strip_fade = -1;   /* RG_LAYOUT_STRIP_FADE: % darker at the canvas edge (default 75) */
static void strip_opts(void)
{
    if (g_strip_mode >= 0)
        return;
    const char *e = getenv("RG_LAYOUT_STRIPS");
    g_strip_mode = e && e[0] == 's' ? 1 : 0;
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

int rg_layout_active(void) { return g_active; }
void rg_layout_set_detect(int on) { g_detect = on; }
static unsigned g_roll_packets;   /* g_st.packets at the last frame roll */
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
void rg_layout_about_begin(float ax, int screen_px) { g_about = 1; g_about_x = ax; g_about_px = screen_px; }
void rg_layout_about_end(void) { g_about = 0; }
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
typedef struct aent { uint32_t key; uint8_t anchor; } aent;
static aent g_prev[TAB], g_next[TAB];

static uint32_t mix(uint32_t h, uint32_t v)
{
    h ^= v;
    h *= 16777619u;
    return h;
}

static void tab_put(aent *t, uint32_t key, int anchor)
{
    for (uint32_t i = key & (TAB - 1), n = 0; n < TAB; i = (i + 1) & (TAB - 1), n++)
        if (t[i].key == 0 || t[i].key == key) {
            t[i].key = key;
            t[i].anchor = (uint8_t)anchor;
            return;
        }
}

static int tab_get(const aent *t, uint32_t key)
{
    for (uint32_t i = key & (TAB - 1), n = 0; n < TAB; i = (i + 1) & (TAB - 1), n++) {
        if (t[i].key == key)
            return t[i].anchor;
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
} pkrec;
static pkrec g_pk[MAXPK];
static int g_npk;
#define MAXDEPTH 16
static int g_mark[MAXDEPTH];
static const void *g_task[MAXDEPTH];
static int g_depth;

static int find(int *par, int i)
{
    while (par[i] != i)
        i = par[i] = par[par[i]];
    return i;
}

/* cluster g_pk[first..g_npk) by overlap and file their anchors for the next frame */
static void cluster(int first)
{
    static int par[MAXPK];
    static float gx0[MAXPK], gx1[MAXPK];
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
        gx0[i] = 1e30f;
        gx1[i] = -1e30f;
    }
    for (int i = first; i < g_npk; i++) {
        int r = find(par, i);
        if (g_pk[i].x0 < gx0[r]) gx0[r] = g_pk[i].x0;
        if (g_pk[i].x1 > gx1[r]) gx1[r] = g_pk[i].x1;
    }
    for (int i = first; i < g_npk; i++) {
        int r = find(par, i);
        int a = rg_layout_cluster_anchor(gx0[r], gx1[r], g_pk[i].left, g_pk[i].w);
        tab_put(g_next, g_pk[i].key, a);
        if (r == i)
            g_st.groups++;
    }
}

void rg_layout_set_frame(float s, int field)
{
    /* close the frame that ended: packets drawn outside any task form one group.  The
     * game draws at 30 or 60 Hz: a field without packets (the second VBlank of a 30 Hz
     * frame) keeps the last drawn frame's anchors. */
    static unsigned last_packets;
    if ((g_active || g_detect) && g_st.packets != last_packets) {
        g_cover_last = g_cover_now;
        g_cover_now = 0;
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
        g_nct_last = g_nct_now = 0;
        g_ndrawn = 0;
    }
    if (g_active && g_st.packets != last_packets) {
        cluster(0);
        memcpy(g_prev, g_next, sizeof g_prev);
        memset(g_next, 0, sizeof g_next);
        memset(g_ord, 0, sizeof g_ord);
    } else if (!g_active) {
        memset(g_prev, 0, sizeof g_prev);
        memset(g_next, 0, sizeof g_next);
        memset(g_ord, 0, sizeof g_ord);
    }
    last_packets = g_st.packets;
    g_npk = 0;
    g_depth = 0;
    g_field = field;
    const char *e = getenv("RG_LAYOUT");
    if (e && *e == '0')
        s = 1.0f;
    g_s = s;
    g_active = s < 0.999f;
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
        cluster(first);
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
    uint8_t *ms = *(uint8_t **)pkt;
    uint8_t *base = *(uint8_t **)((uint8_t *)pkt + PK_BASE);
    uint8_t *cur = *(uint8_t **)((uint8_t *)pkt + PK_CUR);
    uint8_t *tag = *(uint8_t **)((uint8_t *)pkt + 0x100);
    uint32_t *dma = *(uint32_t **)((uint8_t *)pkt + 0x104);
    uint32_t *vif = *(uint32_t **)((uint8_t *)pkt + 0x108);
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
    *(uint8_t **)((uint8_t *)pkt + PK_CUR) = cur + 16 * k;
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
    int side;
} strip_job;

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
        for (int bnd = 0; bnd < nb; bnd++) {
            if (k + 7 > MAXAD)
                return -1;
            float t0 = (float)bnd / (float)nb, t1 = (float)(bnd + 1) / (float)nb;
            float xa = seam + (edge - seam) * t0, xb = seam + (edge - seam) * t1;
            float ua = j->uin + (j->uout - j->uin) * t0, ub = j->uin + (j->uout - j->uin) * t1;
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
        }
    }
    if (nb > 1) {                                   /* the packet's last colour, as it was */
        val[k] = c0;
        reg[k++] = 0x01;
    }
    return k;
}

static void menu_sprites(void *pkt, rg_layout_xref *xs, int n, float left, float w, int bg, uint8_t *done)
{
    const float L = left, R = left + w, px = 16.0f;
    const float top = 1824.0f * 16.0f, bot = (1824.0f + RG_LAYOUT_FRAME_H) * 16.0f;
    static uint64_t val[MAXAD];
    static uint8_t reg[MAXAD];
    strip_job sj[MAXSTRIPS];
    int nst = 0, sides = 0;
    int nstrip0[2] = { g_nstrip[0], g_nstrip[1] };
    strip_opts();
    g_strip_L = L;
    g_strip_R = R;
    for (int j = 0; j + 1 < n; j++) {
        rg_layout_xref *a = &xs[j], *b = &xs[j + 1];
        if (a->kind || b->kind || a->prim != 6 || b->prim != 6 || (a->vix & 1) || b->vix != a->vix + 1)
            continue;
        done[j] = done[j + 1] = 1;
        j++;
        rg_layout_xref *l = (float)*a->x <= (float)*b->x ? a : b, *r = l == a ? b : a;
        float xl = (float)*l->x, xr = (float)*r->x;
        float ya = (float)*a->y, yb = (float)*b->y;
        float sy0 = ya < yb ? ya : yb, sy1 = ya < yb ? yb : ya;
        float ml = rg_layout_map(xl, RG_ANCHOR_CENTER, left, w, g_s);
        float mr = rg_layout_map(xr, RG_ANCHOR_CENTER, left, w, g_s);
        /* a background tile: at least an eighth of the screen each way */
        int sbg = bg && xr - xl >= 0.125f * w && sy1 - sy0 >= 0.125f * (bot - top);
        if (!sbg && (xr <= L + px || xl >= R - px)) { /* hidden at 4:3: keep it hidden */
            set_x(l, ml);
            set_x(r, ml);
            continue;
        }
        float vis = xr > xl ? ((xr < R ? xr : R) - (xl > L ? xl : L)) / (xr - xl) : 1.0f;
        int tcok = l->tck && r->tck && l->tck == r->tck;
        if (!sbg && (vis < 0.5f || xr - xl < 0.25f * w)) {   /* mostly hidden / small: clip to the screen */
            float ul = tcok ? tc_get(l) : 0.0f, ur = tcok ? tc_get(r) : 0.0f;
            float cl = xl < L ? L : xl, cr = xr > R ? R : xr;
            if (tcok && xr > xl) {
                float nl = ul + (ur - ul) * (cl - xl) / (xr - xl);
                float nr = ul + (ur - ul) * (cr - xl) / (xr - xl);
                tc_set(l, nl);
                if (r->tc != l->tc)
                    tc_set(r, nr);
            } else if (!tcok && (l->tck || r->tck)) {
                cl = cr = xl;                        /* cannot cut its texture: hide it */
            }
            set_x(l, rg_layout_map(cl, RG_ANCHOR_CENTER, left, w, g_s));
            set_x(r, rg_layout_map(cr, RG_ANCHOR_CENTER, left, w, g_s));
            continue;
        }
        if (!sbg) {                                  /* bleeding off an edge: pin it there */
            if (xl < L - px && ml > L) ml = L;
            if (xr > R + px && mr < R) mr = R;
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
            float cap = 0.3f * (umax - umin);
            if (g * dir > cap || g * dir < -cap)
                uout = uin + (dir > 0 ? cap : -cap);
            if (bg == 2)   /* an overlay (over a scene capture): its edge column stretched */
                uout = uin + 0.5f * (dir > 0 ? 1.0f : -1.0f);
            else if (g_strip_mode == 1 && (g * dir > 6.0f || g * dir < -6.0f))
                uout = uin + (dir > 0 ? 6.0f : -6.0f);             /* smear: the outer 6 texels */
            if (uout < umin) uout = umin;
            if (uout > umax) uout = umax;
            /* a sprite of this packet drawn over an earlier one's rows replaces its strip
             * (the main menu's backdrop: a translucent black shadow sprite, then the art) */
            for (int q = 0; q < nst; q++) {
                float o0 = sj[q].y0 > vy0 ? sj[q].y0 : vy0, o1 = sj[q].y1 < vy1 ? sj[q].y1 : vy1;
                if (sj[q].side == side && o1 - o0 >= 0.5f * (sj[q].y1 - sj[q].y0))
                    sj[q--] = sj[--nst];
            }
            sj[nst++] = (strip_job){ a, l, r, ml, mr, uin, uout, vy0, vy1, side };
        }
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
    int nb = (MAXAD - 2) / (5 * nst);
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
    uint8_t *base = *(uint8_t **)((uint8_t *)pkt + PK_BASE);
    uint8_t *cur = *(uint8_t **)((uint8_t *)pkt + PK_CUR);
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
    int menu = 0;   /* stage 3: part of a full-screen menu (laid out whole, centred) */
    if (g_scan_fbp >= 0 && g_scan_fbp != g_screen_fbp) {
        why = "offscreen";
    } else if (g_about) {
        why = "about";
        g_st.about++;
    } else if (g_suppress) {
        why = "suppressed";
        g_st.suppressed++;
    } else if ((zt & 1) && ((zt >> 1) & 3) >= 2) {
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
    /* stage 3: on a full-screen menu the frame clear (an untextured packet covering the
     * screen, drawn outside any task: DrawListClearScreen) is drawn black.  At 4:3 the
     * menu covers it entirely; on the wide canvas it shows only where the centred menu's
     * background does not reach (the edges of the canvas at 21:9), black like a
     * pillarbox instead of the field's clear colour. */
    if (!g_clear_done && !task && g_scan_psm < 0 && g_cover_last > 0 && x0 <= left + edge && x1 >= left + w - edge &&
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
    int from_prev = 0;
    if (task && (menu || !why))
        drawn_add((const void *)task);
    if (menu) {
        /* stage 3: the whole menu is one 4:3 element in the middle of the wide canvas */
        anchor = RG_ANCHOR_CENTER;
        from_prev = 1;
        g_st.menu++;
    } else if (!why) {
        anchor = tab_get(g_prev, key);
        from_prev = anchor >= 0;
        if (anchor < 0)
            anchor = rg_layout_anchor(x0, x1, left, w);
        if (g_npk < MAXPK) {
            pkrec *k = &g_pk[g_npk++];
            k->key = key;
            k->x0 = x0; k->x1 = x1; k->y0 = y0; k->y1 = y1;
            k->left = left; k->w = w;
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
        fprintf(g_log, "%d pk task=%08lx caller=%08lx x=%.1f..%.1f y=%.1f..%.1f n=%d psm=%d fbp=%d/%d %s%s tbp=%d u=%g..%g\n", g_field,
                (unsigned long)(task ? task - image_base() : 0), (unsigned long)((uintptr_t)caller - image_base()),
                (x0 - left) / 16.0f, (x1 - left) / 16.0f, y0 / 16.0f, y1 / 16.0f, nv, g_scan_psm, g_scan_fbp, g_scan_fbw,
                why ? why : aname(anchor), menu ? " (menu)" : why || from_prev ? "" : " (own)", g_scan_tbp,
                u0 < 1e29f ? u0 : -1.0f, u0 < 1e29f ? u1 : -1.0f);
    if (g_about && why && why[0] == 'a') {
        /* world-anchored text: about its own projected point (no grouping, no scissor) */
        float a = g_about_px ? left + 16.0f * g_about_x : g_about_x;
        g_st.moved++;
        for (int j = 0; j < n; j++)
            if (xs[j].kind == 0) {
                float v = a + ((float)*xs[j].x - a) * g_s;
                if (v < 0.0f) v = 0.0f;
                if (v > 65535.0f) v = 65535.0f;
                *xs[j].x = (uint16_t)(v + 0.5f);
            }
        return g_s != 1.0f;
    }
    if (anchor == RG_ANCHOR_NONE)
        return 0;
    g_st.moved++;
    float wpx = w / 16.0f;
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
            float v = rg_layout_map(o, anchor, left, w, g_s);
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
        } else {
            /* scissor (window pixels): only a rectangle narrower than the screen moves */
            uint64_t sc = *x->sc;
            float a0 = (float)(sc & 0x7FF), a1 = (float)((sc >> 16) & 0x7FF);
            if (a1 - a0 + 1.0f >= RG_LAYOUT_FULL * wpx)
                continue;
            float b0 = rg_layout_map(a0, anchor, 0.0f, wpx, g_s);
            float b1 = rg_layout_map(a1 + 1.0f, anchor, 0.0f, wpx, g_s) - 1.0f;
            if (b0 < 0.0f) b0 = 0.0f;
            if (b1 < b0) b1 = b0;
            sc &= ~((uint64_t)0x7FF | ((uint64_t)0x7FF << 16));
            sc |= (uint64_t)((unsigned)(b0 + 0.5f) & 0x7FF) | ((uint64_t)((unsigned)(b1 + 0.5f) & 0x7FF) << 16);
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
    return g_s != 1.0f;
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
