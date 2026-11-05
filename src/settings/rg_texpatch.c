/* SPDX-License-Identifier: CC0-1.0 */
/* Texture patches at upload time (rg_texpatch.h; docs/PROMPTS.md "Prompts baked into other
 * textures", docs/ACCESSIBILITY.md). */
#include "rg_texpatch.h"

#include "rg_prompts.h"

#include <math.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t rg_tp_fnv64(const uint8_t *d, size_t n)
{
    uint64_t h = 0xCBF29CE484222325ull;
    for (size_t i = 0; i < n; i++) h = (h ^ d[i]) * 0x100000001B3ull;
    return h;
}

/* ---------------------------------------------------------------- formats */
/* PSMT8 stored as the GS holds it after an upload as PSMCT32 (gaiji.py _swizzle8_table) */
static uint32_t swz8(int w, int x, int y)
{
    int row = (y & ~0xF) * w;
    int swap = (((y + 2) >> 2) & 1) * 4;
    int col = ((((y & ~3) >> 1) + (y & 1)) & 7) * w * 2;
    int byte = (y >> 1) & 1;
    return (uint32_t)(row + (x & ~0xF) * 2 + col + ((x + swap) & 7) * 4 + byte + ((x >> 2) & 2));
}
static int csm1(int i) { return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1); }

static int get_idx(const rg_tp_target *t, const uint8_t *pix, int x, int y)
{
    if (t->bits == 8) return pix[swz8(t->w, x, y)];
    uint32_t n = (uint32_t)y * t->w + (uint32_t)x;   /* PSMT4: linear, low nibble first */
    return n & 1 ? pix[n >> 1] >> 4 : pix[n >> 1] & 15;
}
static void set_idx(const rg_tp_target *t, uint8_t *pix, int x, int y, int v)
{
    if (t->bits == 8) { pix[swz8(t->w, x, y)] = (uint8_t)v; return; }
    uint32_t n = (uint32_t)y * t->w + (uint32_t)x;
    uint8_t *p = &pix[n >> 1];
    *p = n & 1 ? (uint8_t)((*p & 0x0F) | (v << 4)) : (uint8_t)((*p & 0xF0) | (v & 15));
}
static int ncolors(const rg_tp_target *t) { return t->bits == 8 ? 256 : 16; }
static const uint8_t *pal_at(const rg_tp_target *t, const uint8_t *clut, int i)
{
    return clut + 4 * (t->bits == 8 ? csm1(i) : i);
}
static uint8_t *pal_at_w(const rg_tp_target *t, uint8_t *clut, int i)
{
    return clut + 4 * (t->bits == 8 ? csm1(i) : i);
}

void rg_tp_rgba(const rg_tp_target *t, const uint8_t *pix, const uint8_t *clut, uint8_t *rgba)
{
    for (int y = 0; y < t->h; y++)
        for (int x = 0; x < t->w; x++) {
            const uint8_t *c = pal_at(t, clut, get_idx(t, pix, x, y));
            uint8_t *o = rgba + 4 * (y * t->w + x);
            o[0] = c[0]; o[1] = c[1]; o[2] = c[2];
            o[3] = (uint8_t)(c[3] * 2 > 255 ? 255 : c[3] * 2);
        }
}

/* ---------------------------------------------------------------- prompt sites */
/* nearest palette entry to a PS2 colour (alpha 0..0x80), alpha-weighted like rg_prompts.c */
static int nearest(const rg_tp_target *t, const uint8_t *clut, double r, double g, double b, double a)
{
    int best = 0;
    double bd = 1e300;
    for (int i = 0; i < ncolors(t); i++) {
        const uint8_t *c = pal_at(t, clut, i);
        double ca = c[3] / 128.0, aa = a / 128.0, d = 0, q;
        q = c[0] * ca - r * aa; d += q * q;
        q = c[1] * ca - g * aa; d += q * q;
        q = c[2] * ca - b * aa; d += q * q;
        q = 2.0 * (c[3] - a); d += q * q;
        if (d < bd) { bd = d; best = i; }
    }
    return best;
}

static int site_skip(int style, const char *const *keys, int slot)
{
    /* PlayStation keeps its art unless a binding moved the slot to another button */
    if (style != RG_GAIJI_PLAYSTATION) return 0;
    if (!keys) return 1;
    return rg_prompt_pad_button(keys[slot]) == rg_prompt_slot_default_button(slot);
}

static int patch_sites(const rg_tp_target *t, const uint8_t *clut, int style, const char *const *keys, uint8_t *pix)
{
    int changed = 0;
    for (int s = 0; s < t->nsites; s++) {
        const rg_tp_site *S = &t->sites[s];
        if (site_skip(style, keys, S->slot)) continue;
        uint8_t *g = (uint8_t *)malloc((size_t)S->w * S->h * 4);
        if (!g) continue;
        if (rg_prompt_glyph_rgba(style, S->slot, keys, S->w, S->h, S->shape, g) != 0) { free(g); continue; }
        /* (a transparent entry, for erased text) */
        int clear = -1;
        for (int i = 0; i < ncolors(t) && clear < 0; i++)
            if (pal_at(t, clut, i)[3] == 0) clear = i;
        for (int y = 0; y < S->h; y++)
            for (int x = 0; x < S->w; x++) {
                int tx = S->x + x, ty = S->y + y;
                if (tx < 0 || ty < 0 || tx >= t->w || ty >= t->h) continue;
                const uint8_t *gp = g + 4 * (y * S->w + x);
                int oi = get_idx(t, pix, tx, ty);
                const uint8_t *oc = pal_at(t, clut, oi);
                double orr = oc[0], og = oc[1], ob = oc[2], oa = oc[3] * 2.0 > 255 ? 255 : oc[3] * 2.0;
                if (S->shape == RG_PROMPT_SHAPE_TEXT) {
                    /* the original label goes: everything but the cell's background */
                    if (clear >= 0) { orr = og = ob = 0; oa = 0; }
                } else if (S->shape == RG_PROMPT_SHAPE_CELL) {
                    orr = og = ob = 0;
                    oa = 0;
                }
                double ga = gp[3] / 255.0, A = ga + oa / 255.0 * (1 - ga);
                double r = 0, gg = 0, b = 0;
                if (A > 0) {
                    r = (gp[0] * ga + orr * (oa / 255.0) * (1 - ga)) / A;
                    gg = (gp[1] * ga + og * (oa / 255.0) * (1 - ga)) / A;
                    b = (gp[2] * ga + ob * (oa / 255.0) * (1 - ga)) / A;
                }
                int v;
                if (A <= 0 && clear >= 0) v = clear;
                else v = nearest(t, clut, r, gg, b, floor(A * 255.0 / 2.0 + 0.5));
                if (S->shape == RG_PROMPT_SHAPE_DISC && gp[3] == 0) v = oi;   /* outside the disc art */
                if (v != oi) { set_idx(t, pix, tx, ty, v); changed = 1; }
            }
        free(g);
    }
    return changed;
}

/* ---------------------------------------------------------------- marker colours */
static double lin(double c) { c /= 255.0; return c <= 0.04045 ? c / 12.92 : pow((c + 0.055) / 1.055, 2.4); }
static double unlin(double v)
{
    v = v < 0 ? 0 : v > 1 ? 1 : v;
    v = v <= 0.0031308 ? v * 12.92 : 1.055 * pow(v, 1 / 2.4) - 0.055;
    return floor(v * 255.0 + 0.5);
}
static double luma(double r, double g, double b) { return 0.2126 * lin(r) + 0.7152 * lin(g) + 0.0722 * lin(b); }

/* an entry of a marker group gets the group's hue at luminance y_des (linear): scaled in linear
 * light, then mixed toward white when a channel saturates */
static void recolour(uint8_t *c, uint32_t hue, double y_des)
{
    double tr = lin((hue >> 16) & 255), tg = lin((hue >> 8) & 255), tb = lin(hue & 255);
    double yt = 0.2126 * tr + 0.7152 * tg + 0.0722 * tb;
    if (yt <= 1e-6) { c[0] = c[1] = c[2] = (uint8_t)unlin(y_des); return; }
    double k = y_des / yt, r = tr * k, g = tg * k, b = tb * k;
    double m = fmax(r, fmax(g, b));
    if (m > 1) {
        r /= m; g /= m; b /= m;
        double yy = 0.2126 * r + 0.7152 * g + 0.0722 * b, f = yy < 1 ? (y_des - yy) / (1 - yy) : 0;
        if (f < 0) f = 0;
        if (f > 1) f = 1;
        r += (1 - r) * f; g += (1 - g) * f; b += (1 - b) * f;
    }
    c[0] = (uint8_t)unlin(r);
    c[1] = (uint8_t)unlin(g);
    c[2] = (uint8_t)unlin(b);
}

static int saturated(const uint8_t *c)
{
    int mx = c[0] > c[1] ? (c[0] > c[2] ? c[0] : c[2]) : (c[1] > c[2] ? c[1] : c[2]);
    int mn = c[0] < c[1] ? (c[0] < c[2] ? c[0] : c[2]) : (c[1] < c[2] ? c[1] : c[2]);
    return c[3] != 0 && mx - mn >= 48;
}

/* Colour-coded marker sets.  Each group gets its replacement hue for the deficiency, with the
 * group's shading kept relative to its mean (a pixel at the group's mean luminance gets the
 * hue's own luminance), so the groups also differ in lightness as the chosen hues do:
 *   - a palette entry only this group uses (inside its rects, nowhere else): recoloured in the
 *     CLUT (exact);
 *   - a coloured entry the group shares with the rest of the sheet (the same orange in other
 *     art): the group's pixels are re-indexed to the entry nearest their recoloured value;
 *   - entries several groups use (outlines, frames) and grey / black / white ones: unchanged. */
static int patch_marks(const rg_tp_target *t, const uint8_t *pix, int cb, uint8_t *clut, uint8_t *out_pix,
                       int *pix_changed)
{
    if (cb <= RG_CB_OFF || cb >= RG_CB_COUNT || !t->nmarks || !t->colours) return 0;
    int n = ncolors(t);
    uint64_t gmask[256];
    uint8_t outside[256];
    memset(gmask, 0, sizeof gmask);
    memset(outside, 0, sizeof outside);
    double ysum[64] = { 0 }, wsum[64] = { 0 };
    uint8_t *in = (uint8_t *)calloc((size_t)t->w * t->h, 1);
    if (!in) return 0;
    for (int m = 0; m < t->nmarks; m++) {
        const rg_tp_mark *M = &t->marks[m];
        if (M->group >= 64) continue;
        for (int y = M->y; y < M->y + M->h && y < t->h; y++)
            for (int x = M->x; x < M->x + M->w && x < t->w; x++) {
                in[y * t->w + x] = 1;
                int i = get_idx(t, pix, x, y);
                const uint8_t *c = pal_at(t, clut, i);
                if (c[3] == 0) continue;
                gmask[i] |= 1ull << M->group;
                if (saturated(c)) {
                    ysum[M->group] += luma(c[0], c[1], c[2]);
                    wsum[M->group] += 1;
                }
            }
    }
    for (int y = 0; y < t->h; y++)
        for (int x = 0; x < t->w; x++)
            if (!in[y * t->w + x]) outside[get_idx(t, pix, x, y)] = 1;
    free(in);
    uint8_t orig[256][4];
    for (int i = 0; i < n; i++) memcpy(orig[i], pal_at(t, clut, i), 4);
    int changed = 0;
    for (int i = 0; i < n; i++) {
        uint64_t g = gmask[i];
        if (!g || (g & (g - 1)) || outside[i]) continue;   /* one group, nowhere else */
        int grp = 0;
        while (!(g >> grp & 1)) grp++;
        if (grp >= t->ngroups || wsum[grp] <= 0) continue;
        uint32_t hue = t->colours[grp][cb];
        if (hue & 0xFF000000u) continue;
        uint8_t *c = pal_at_w(t, clut, i);
        double yg = ysum[grp] / wsum[grp];
        double tr = lin((hue >> 16) & 255), tg = lin((hue >> 8) & 255), tb = lin(hue & 255);
        double yt = 0.2126 * tr + 0.7152 * tg + 0.0722 * tb;
        recolour(c, hue, yg > 1e-6 ? yt * luma(c[0], c[1], c[2]) / yg : yt);
        changed |= memcmp(orig[i], c, 4) != 0;
    }
    for (int m = 0; m < t->nmarks; m++) {
        const rg_tp_mark *M = &t->marks[m];
        if (M->group >= t->ngroups || M->group >= 64 || wsum[M->group] <= 0) continue;
        uint32_t hue = t->colours[M->group][cb];
        if (hue & 0xFF000000u) continue;
        double yg = ysum[M->group] / wsum[M->group];
        double tr = lin((hue >> 16) & 255), tg = lin((hue >> 8) & 255), tb = lin(hue & 255);
        double yt = 0.2126 * tr + 0.7152 * tg + 0.0722 * tb;
        for (int y = M->y; y < M->y + M->h && y < t->h; y++)
            for (int x = M->x; x < M->x + M->w && x < t->w; x++) {
                int i = get_idx(t, pix, x, y);
                uint64_t g = gmask[i];
                if (!outside[i] || (g & (g - 1)) || !saturated(orig[i])) continue;
                uint8_t c[4];
                memcpy(c, orig[i], 4);
                recolour(c, hue, yg > 1e-6 ? yt * luma(c[0], c[1], c[2]) / yg : yt);
                int v = nearest(t, clut, c[0], c[1], c[2], c[3]);
                if (v != i) {
                    set_idx(t, out_pix, x, y, v);
                    if (pix_changed) *pix_changed = 1;
                }
            }
    }
    return changed;
}

int rg_tp_build(const rg_tp_target *t, const uint8_t *pix, const uint8_t *clut, int style,
                const char *const *keys, int cb, uint8_t *out_pix, uint8_t *out_clut,
                int *pix_changed, int *clut_changed)
{
    if (!t || !pix || !clut || !out_pix || !out_clut || style < 0 || style >= RG_GAIJI_STYLES)
        return -1;
    memcpy(out_pix, pix, t->pix_bytes);
    memcpy(out_clut, clut, t->clut_bytes);
    int pc = patch_sites(t, clut, style, keys, out_pix);
    int cc = patch_marks(t, pix, cb, out_clut, out_pix, &pc);
    if (pix_changed) *pix_changed = pc;
    if (clut_changed) *clut_changed = cc;
    return 0;
}

/* ---------------------------------------------------------------- the runtime switch */
#define TP_MAX 32
#define RETIRE 16
typedef struct {
    uint8_t *orig_pix, *orig_clut;
    atomic_int have_pix, have_clut;
    _Atomic(uint8_t *) pub_pix, pub_clut;   /* NULL: upload the original */
    uint32_t built_cfg;
    int nlog;                 /* RG_TEXPATCH_LOG=2 lines printed */
} tp_state;

static tp_state g_tp[TP_MAX];
static atomic_int g_active;
static atomic_uint g_replaced, g_captured;
static unsigned g_built;

static void *g_retire[RETIRE];
static int g_retire_n;
static int g_log = -1;
static int g_last_match = -1;     /* GS worker: target of the last pixel transfer matched (-1) */
static atomic_uint g_updates;     /* rg_texpatch_update calls (about one per field) */
static atomic_int g_cb;           /* the colour-blind mode of the last update (rg_texpatch_colour_blind) */

static uint32_t cfg_hash(int style, const char *const *keys, int cb)
{
    uint32_t h = 2166136261u;
    h = (h ^ (uint32_t)style) * 16777619u;
    h = (h ^ (uint32_t)cb) * 16777619u;
    for (int i = 0; keys && i < RG_PROMPT_SLOTS; i++) {
        for (const char *s = keys[i] ? keys[i] : ""; *s; s++) h = (h ^ (uint8_t)*s) * 16777619u;
        h = (h ^ 0xFF) * 16777619u;
    }
    return h | 1u;
}

static void retire(void *p)
{
    if (!p) return;
    if (g_retire_n == RETIRE) {
        free(g_retire[0]);
        memmove(g_retire, g_retire + 1, sizeof g_retire[0] * (RETIRE - 1));
        g_retire_n--;
    }
    g_retire[g_retire_n++] = p;
}

void rg_texpatch_update(int style, const char *const *keys, int cb)
{
    atomic_fetch_add(&g_updates, 1);
    if (g_log < 0) { const char *e = getenv("RG_TEXPATCH_LOG"); g_log = e && *e && *e != '0' ? (*e == '2' ? 2 : 1) : 0; }
    if (style < 0 || style >= RG_GAIJI_STYLES) style = RG_GAIJI_PLAYSTATION;
    if (cb < 0 || cb >= RG_CB_COUNT) cb = RG_CB_OFF;
    atomic_store(&g_cb, cb);
    int deflt = style == RG_GAIJI_PLAYSTATION && cb == RG_CB_OFF && rg_prompt_keys_default(style, keys, RG_PROMPT_SLOTS);
    if (deflt) keys = NULL;
    uint32_t cfg = deflt ? 0 : cfg_hash(style, keys, cb);
    atomic_store(&g_active, !deflt);
    int n = rg_tp_ntargets < TP_MAX ? rg_tp_ntargets : TP_MAX;
    for (int i = 0; i < n; i++) {
        tp_state *S = &g_tp[i];
        const rg_tp_target *t = &rg_tp_targets[i];
        if (S->built_cfg == cfg) continue;
        if (!cfg) {
            retire(atomic_exchange(&S->pub_pix, NULL));
            retire(atomic_exchange(&S->pub_clut, NULL));
            S->built_cfg = 0;
            continue;
        }
        if (!atomic_load(&S->have_pix) || !atomic_load(&S->have_clut)) continue;
        uint8_t *p = (uint8_t *)malloc(t->pix_bytes), *c = (uint8_t *)malloc(t->clut_bytes);
        int pc = 0, cc = 0;
        if (!p || !c || rg_tp_build(t, S->orig_pix, S->orig_clut, style, keys, cb, p, c, &pc, &cc) != 0) {
            free(p);
            free(c);
            continue;
        }
        {   /* $RG_TEXPATCH_PROBE=name (diagnostic, an active mode): that target's whole CLUT magenta,
             * so shots show where its pixels reach the screen (lane fpsgate 2026-11-01) */
            const char *pr = getenv("RG_TEXPATCH_PROBE");
            if (pr && !strcmp(pr, t->name)) {
                for (uint32_t k = 0; k + 3 < t->clut_bytes; k += 4) { c[k] = 255; c[k + 1] = 0; c[k + 2] = 255; }
                cc = 1;
            }
        }
        if (!pc) { free(p); p = NULL; }
        if (!cc) { free(c); c = NULL; }
        retire(atomic_exchange(&S->pub_pix, p));
        retire(atomic_exchange(&S->pub_clut, c));
        S->built_cfg = cfg;
        g_built++;
        if (g_log)
            fprintf(stderr, "TEXPATCH built %s style=%d cb=%d pixels=%s clut=%s\n", t->name, style, cb,
                    p ? "patched" : "orig", c ? "patched" : "orig");
    }

}

const uint8_t *rg_texpatch_xfer(const uint8_t *data, uint32_t bytes)
{
    g_last_match = -1;
    if (!atomic_load_explicit(&g_active, memory_order_relaxed) || !data) return NULL;
    uint64_t h = 0;
    uint32_t hb = 0;
    int n = rg_tp_ntargets < TP_MAX ? rg_tp_ntargets : TP_MAX;
    for (int i = 0; i < n; i++) {
        const rg_tp_target *t = &rg_tp_targets[i];
        int is_pix = bytes == t->pix_bytes, is_clut = bytes == t->clut_bytes;
        if (!is_pix && !is_clut) continue;
        if (hb != bytes) { h = rg_tp_fnv64(data, bytes); hb = bytes; }
        tp_state *S = &g_tp[i];
        if (g_log > 1 && ((is_pix && h == t->pix_hash) || (is_clut && h == t->clut_hash)) && S->nlog < 40) {
            S->nlog++;   /* RG_TEXPATCH_LOG=2: the first transfers of each target (which part, replaced?) */
            int px = is_pix && h == t->pix_hash;
            uint8_t *pp = px ? atomic_load(&S->pub_pix) : atomic_load(&S->pub_clut);
            fprintf(stderr, "TEXPATCH xfer %s %s %s\n", t->name, px ? "pixels" : "clut", pp ? "replaced" : "orig");
        }
        if (is_pix && h == t->pix_hash) {
            g_last_match = i;
            if (!atomic_load(&S->have_pix)) {
                uint8_t *o = (uint8_t *)malloc(bytes);
                if (o) {
                    memcpy(o, data, bytes);
                    S->orig_pix = o;
                    atomic_store(&S->have_pix, 1);
                    atomic_fetch_add(&g_captured, 1);
                }
            }
            uint8_t *p = atomic_load(&S->pub_pix);
            if (p) atomic_fetch_add(&g_replaced, 1);
            return p;
        }
        if (is_clut && h == t->clut_hash) {
            if (!atomic_load(&S->have_clut)) {
                uint8_t *o = (uint8_t *)malloc(bytes);
                if (o) {
                    memcpy(o, data, bytes);
                    S->orig_clut = o;
                    atomic_store(&S->have_clut, 1);
                    atomic_fetch_add(&g_captured, 1);
                }
            }
            uint8_t *p = atomic_load(&S->pub_clut);
            if (p) atomic_fetch_add(&g_replaced, 1);
            return p;
        }
    }
    return NULL;
}

void rg_texpatch_stats(unsigned *replaced, unsigned *captured, unsigned *built)
{
    if (replaced) *replaced = atomic_load(&g_replaced);
    if (captured) *captured = atomic_load(&g_captured);
    if (built) *built = g_built;
}

int rg_texpatch_last_match(void) { return g_last_match; }
unsigned rg_texpatch_updates(void) { return atomic_load(&g_updates); }
int rg_texpatch_colour_blind(void) { return atomic_load(&g_cb); }
