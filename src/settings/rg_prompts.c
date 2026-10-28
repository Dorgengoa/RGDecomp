/* SPDX-License-Identifier: CC0-1.0 */
/* Button prompts per device: the gaiji2 texture swap (docs/PROMPTS.md,
 * rg_prompts.h).  The drawing is a line-for-line port of
 * tools/assets/gaiji.py (Canvas, the stroke font, draw_pad_face /
 * draw_pad_shoulder / draw_keycap / draw_mouse, index_rgba), which stays the
 * reference: tools/prompts/compare.py diffs this module's output against it. */
#include "rg_prompts.h"

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------ game facts */
const rg_gaiji_rect rg_gaiji_button_rects[RG_GAIJI_BUTTONS] = {
    { 0xFD04, 0, 0, 32, 20 },    /* L2 */
    { 0xFD02, 32, 0, 32, 20 },   /* L1 */
    { 0xFD03, 64, 0, 32, 20 },   /* R1 */
    { 0xFD05, 96, 0, 32, 20 },   /* R2 */
    { 0xFD06, 0, 20, 22, 22 },   /* Circle */
    { 0xFD07, 22, 20, 22, 22 },  /* Triangle */
    { 0xFD09, 44, 20, 22, 22 },  /* Square */
    { 0xFD08, 66, 20, 22, 22 },  /* Cross */
};
const char *const rg_gaiji_button_action[RG_GAIJI_BUTTONS] = {
    "decline", "camera_turn_left", "camera_turn_right", "camera_recentre",
    "cancel", "menu", "attack", "confirm",
};
/* gaiji.py draws in metric-table order (FD02, FD03, FD04, FD05, FD06, FD07,
 * FD08, FD09); kept so any sub-pixel spill composites the same way. */
static const int k_draw_order[RG_GAIJI_BUTTONS] = {
    RG_GAIJI_L1, RG_GAIJI_R1, RG_GAIJI_L2, RG_GAIJI_R2,
    RG_GAIJI_CIRCLE, RG_GAIJI_TRIANGLE, RG_GAIJI_CROSS, RG_GAIJI_SQUARE,
};
/* gaiji.py DEFAULT_KEYS, by button */
static const char *const k_default_keys[RG_GAIJI_BUTTONS] = {
    "key:1", "key:Q", "key:E", "key:3", "key:C", "key:Tab", "key:Z", "key:Space",
};

/* ------------------------------------------------------------ layout */
static uint32_t rd32(const uint8_t *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }
static uint16_t rd16(const uint8_t *p) { return (uint16_t)(p[0] | p[1] << 8); }

int rg_gaiji_layout_of(const uint8_t *b, size_t n, rg_gaiji_layout *L)
{
    if (!b || n < 0x50 || memcmp(b, "IM3", 4) || rd32(b + 4) != 0x10 || rd32(b + 8) != 1)
        return -1;
    uint32_t t = rd32(b + 0x10 + 0x24);
    if (t > n || n - t < 0x40 || memcmp(b + t, "TIM2", 4) || b[t + 5] != 0 || rd16(b + t + 6) != 1)
        return -1;
    size_t p = t + 0x10;
    uint32_t total = rd32(b + p), clut_size = rd32(b + p + 4), img_size = rd32(b + p + 8);
    uint16_t hdr = rd16(b + p + 12), colors = rd16(b + p + 14);
    uint8_t mips = b[p + 17], clut_type = b[p + 18], img_type = b[p + 19];
    uint16_t w = rd16(b + p + 20), h = rd16(b + p + 22);
    if (img_type != 5 || clut_type != 3 || colors != 256 || mips != 1 || w != RG_GAIJI_W ||
        h != RG_GAIJI_H || img_size != (uint32_t)w * h || clut_size != 1024)
        return -1;
    if (total < hdr + img_size + clut_size || p + total > n)
        return -1;
    L->pixels = p + hdr;
    L->clut = L->pixels + img_size;
    L->end = p + total;
    return 0;
}

/* ------------------------------------------------------------ PS2 formats */
static int g_perm_ready;
static uint32_t g_perm[RG_GAIJI_W * RG_GAIJI_H];   /* linear (x, y) -> swizzled offset */

static void perm_init(void)
{
    if (g_perm_ready)
        return;
    const int w = RG_GAIJI_W;
    for (int y = 0; y < RG_GAIJI_H; y++) {
        int row = (y & ~0xF) * w;
        int swap = (((y + 2) >> 2) & 1) * 4;
        int col = ((((y & ~3) >> 1) + (y & 1)) & 7) * w * 2;
        int byte = (y >> 1) & 1;
        for (int x = 0; x < w; x++)
            g_perm[y * w + x] = (uint32_t)(row + (x & ~0xF) * 2 + col + ((x + swap) & 7) * 4 + byte +
                                           ((x >> 2) & 2));
    }
    g_perm_ready = 1;
}

static int csm1(int i) { return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1); }

typedef struct { uint8_t r, g, b, a; } col4;   /* a = PS2 alpha 0..0x80 */

static uint32_t col_key(col4 c) { return (uint32_t)c.r | (uint32_t)c.g << 8 | (uint32_t)c.b << 16 | (uint32_t)c.a << 24; }

static void region_decode(const uint8_t *region, uint8_t *idx, col4 *pal)
{
    perm_init();
    for (int i = 0; i < RG_GAIJI_W * RG_GAIJI_H; i++)
        idx[i] = region[g_perm[i]];
    const uint8_t *c = region + RG_GAIJI_W * RG_GAIJI_H;
    for (int i = 0; i < 256; i++) {
        const uint8_t *e = c + 4 * csm1(i);
        pal[i] = (col4){ e[0], e[1], e[2], e[3] };
    }
}

static void region_encode(const uint8_t *idx, const col4 *pal, uint8_t *region)
{
    perm_init();
    for (int i = 0; i < RG_GAIJI_W * RG_GAIJI_H; i++)
        region[g_perm[i]] = idx[i];
    uint8_t *c = region + RG_GAIJI_W * RG_GAIJI_H;
    for (int i = 0; i < 256; i++) {
        uint8_t *e = c + 4 * csm1(i);
        e[0] = pal[i].r; e[1] = pal[i].g; e[2] = pal[i].b; e[3] = pal[i].a;
    }
}

void rg_gaiji_region_rgba(const uint8_t *region, uint8_t *rgba)
{
    static uint8_t idx[RG_GAIJI_W * RG_GAIJI_H];
    col4 pal[256];
    region_decode(region, idx, pal);
    for (int i = 0; i < RG_GAIJI_W * RG_GAIJI_H; i++) {
        col4 c = pal[idx[i]];
        rgba[4 * i + 0] = c.r; rgba[4 * i + 1] = c.g; rgba[4 * i + 2] = c.b;
        rgba[4 * i + 3] = (uint8_t)(c.a * 2 > 255 ? 255 : c.a * 2);
    }
}

/* ------------------------------------------------------------ canvas (gaiji.py Canvas) */
#define SS 4
typedef struct canvas { int w, h; double *px; /* premultiplied-over RGBA */ } canvas;
typedef struct rgbaf { double r, g, b, a; } rgbaf;
typedef int (*inside_fn)(const void *ctx, double x, double y);

static rgbaf hexc(uint32_t v)
{
    return (rgbaf){ (v >> 16) / 255.0, ((v >> 8) & 255) / 255.0, (v & 255) / 255.0, 1.0 };
}

static void cv_fill(canvas *cv, inside_fn inside, const void *ctx, double bx0, double by0,
                    double bx1, double by1, rgbaf col)
{
    int x0 = (int)floor(bx0), y0 = (int)floor(by0), x1 = (int)ceil(bx1), y1 = (int)ceil(by1);
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > cv->w) x1 = cv->w;
    if (y1 > cv->h) y1 = cv->h;
    double offs[SS];
    for (int i = 0; i < SS; i++)
        offs[i] = (i + 0.5) / SS;
    for (int y = y0; y < y1; y++)
        for (int x = x0; x < x1; x++) {
            int cov = 0;
            for (int sy = 0; sy < SS; sy++)
                for (int sx = 0; sx < SS; sx++)
                    cov += inside(ctx, x + offs[sx], y + offs[sy]) ? 1 : 0;
            if (!cov)
                continue;
            double k = col.a * cov / (SS * SS);
            double *p = cv->px + 4 * (y * cv->w + x);
            double inv = 1.0 - k;
            p[0] = col.r * k + p[0] * inv;
            p[1] = col.g * k + p[1] * inv;
            p[2] = col.b * k + p[2] * inv;
            p[3] = k + p[3] * inv;
        }
}

typedef struct { double x, y, w, h, r, rt; } rrect_t;
static int in_rrect_t(const void *ctx, double px, double py)
{
    const rrect_t *q = (const rrect_t *)ctx;
    if (!(q->x <= px && px <= q->x + q->w && q->y <= py && py <= q->y + q->h))
        return 0;
    double rad = py < q->y + q->h / 2 ? q->rt : q->r;
    double cx = fmin(fmax(px, q->x + rad), q->x + q->w - rad);
    double cy = fmin(fmax(py, q->y + rad), q->y + q->h - rad);
    return (px - cx) * (px - cx) + (py - cy) * (py - cy) <= rad * rad;
}
static void cv_rrect(canvas *cv, double x, double y, double w, double h, double r, rgbaf c, double rt)
{
    rrect_t q = { x, y, w, h, r, rt };
    cv_fill(cv, in_rrect_t, &q, x, y, x + w, y + h, c);
}

typedef struct { double cx, cy, rx, ry; } ell_t;
static int in_ell(const void *ctx, double px, double py)
{
    const ell_t *e = (const ell_t *)ctx;
    double a = (px - e->cx) / e->rx, b = (py - e->cy) / e->ry;
    return a * a + b * b <= 1.0;
}
static void cv_ellipse(canvas *cv, double cx, double cy, double rx, double ry, rgbaf c)
{
    ell_t e = { cx, cy, rx, ry };
    cv_fill(cv, in_ell, &e, cx - rx, cy - ry, cx + rx, cy + ry, c);
}

#define MAX_SEGS 256
typedef struct { double ax, ay, bx, by; } seg_t;
typedef struct { seg_t s[MAX_SEGS]; int n; double rr; } segs_t;
static int in_segs(const void *ctx, double px, double py)
{
    const segs_t *S = (const segs_t *)ctx;
    for (int i = 0; i < S->n; i++) {
        const seg_t *q = &S->s[i];
        double dx = q->bx - q->ax, dy = q->by - q->ay;
        double ll = dx * dx + dy * dy;
        double t = 0.0;
        if (ll != 0) {
            t = ((px - q->ax) * dx + (py - q->ay) * dy) / ll;
            t = fmax(0.0, fmin(1.0, t));
        }
        double ex = q->ax + t * dx - px, ey = q->ay + t * dy - py;
        if (ex * ex + ey * ey <= S->rr)
            return 1;
    }
    return 0;
}
static void segs_fill(canvas *cv, segs_t *S, double radius, rgbaf c)
{
    if (!S->n)
        return;
    double x0 = 1e18, y0 = 1e18, x1 = -1e18, y1 = -1e18;
    for (int i = 0; i < S->n; i++) {
        const seg_t *q = &S->s[i];
        x0 = fmin(x0, fmin(q->ax, q->bx)); x1 = fmax(x1, fmax(q->ax, q->bx));
        y0 = fmin(y0, fmin(q->ay, q->by)); y1 = fmax(y1, fmax(q->ay, q->by));
    }
    S->rr = radius * radius;
    cv_fill(cv, in_segs, S, x0 - radius, y0 - radius, x1 + radius, y1 + radius, c);
}
/* one polyline (pts x,y pairs); a single point is a dot */
static void segs_add(segs_t *S, const double *pts, int npts)
{
    if (npts == 1) {
        if (S->n < MAX_SEGS) S->s[S->n++] = (seg_t){ pts[0], pts[1], pts[0], pts[1] };
        return;
    }
    for (int i = 0; i + 1 < npts && S->n < MAX_SEGS; i++)
        S->s[S->n++] = (seg_t){ pts[2 * i], pts[2 * i + 1], pts[2 * i + 2], pts[2 * i + 3] };
}

/* ------------------------------------------------------------ stroke font (gaiji.py STROKES) */
/* Each glyph: polylines separated by a NAN pair, ended by an INF pair.
 * Arrows are codes 1 up, 2 down, 3 left, 4 right. */
#define BRK NAN, NAN
#define END INFINITY, INFINITY
typedef struct { char ch; const double *pts; } stroke_glyph;
#define G(c, ...) static const double g_##c[] = { __VA_ARGS__, END };
G(A, 0,6, 0,2, 2,0, 4,2, 4,6, BRK, 0,3.6, 4,3.6)
G(B, 0,0, 0,6, 3,6, 4,5, 4,4, 3,3, 0,3, BRK, 0,0, 3,0, 4,1, 4,2, 3,3)
G(C, 4,1, 3,0, 1,0, 0,1, 0,5, 1,6, 3,6, 4,5)
G(D, 0,0, 0,6, 2.5,6, 4,4.5, 4,1.5, 2.5,0, 0,0)
G(E, 4,0, 0,0, 0,6, 4,6, BRK, 0,3, 3,3)
G(F, 4,0, 0,0, 0,6, BRK, 0,3, 3,3)
G(Gg, 4,1, 3,0, 1,0, 0,1, 0,5, 1,6, 3,6, 4,5, 4,3, 2,3)
G(H, 0,0, 0,6, BRK, 4,0, 4,6, BRK, 0,3, 4,3)
G(I, 1,0, 3,0, BRK, 2,0, 2,6, BRK, 1,6, 3,6)
G(J, 4,0, 4,5, 3,6, 1,6, 0,5)
G(K, 0,0, 0,6, BRK, 4,0, 0,4, BRK, 1.5,2.6, 4,6)
G(L, 0,0, 0,6, 4,6)
G(M, 0,6, 0,0, 2,3, 4,0, 4,6)
G(N, 0,6, 0,0, 4,6, 4,0)
G(O, 1,0, 3,0, 4,1, 4,5, 3,6, 1,6, 0,5, 0,1, 1,0)
G(P, 0,6, 0,0, 3,0, 4,1, 4,2, 3,3, 0,3)
G(Q, 1,0, 3,0, 4,1, 4,5, 3,6, 1,6, 0,5, 0,1, 1,0, BRK, 2.5,4.5, 4,6)
G(R, 0,6, 0,0, 3,0, 4,1, 4,2, 3,3, 0,3, BRK, 2,3, 4,6)
G(S, 4,1, 3,0, 1,0, 0,1, 0,2, 1,3, 3,3, 4,4, 4,5, 3,6, 1,6, 0,5)
G(T, 0,0, 4,0, BRK, 2,0, 2,6)
G(U, 0,0, 0,5, 1,6, 3,6, 4,5, 4,0)
G(V, 0,0, 2,6, 4,0)
G(W, 0,0, 1,6, 2,3, 3,6, 4,0)
G(X, 0,0, 4,6, BRK, 4,0, 0,6)
G(Y, 0,0, 2,3, 4,0, BRK, 2,3, 2,6)
G(Z, 0,0, 4,0, 0,6, 4,6)
G(d0, 1,0, 3,0, 4,1, 4,5, 3,6, 1,6, 0,5, 0,1, 1,0, BRK, 3.5,1, 0.5,5)
G(d1, 1,1, 2,0, 2,6, BRK, 1,6, 3,6)
G(d2, 0,1, 1,0, 3,0, 4,1, 4,2, 0,6, 4,6)
G(d3, 0,1, 1,0, 3,0, 4,1, 4,2, 3,3, 4,4, 4,5, 3,6, 1,6, 0,5, BRK, 1.5,3, 3,3)
G(d4, 3,6, 3,0, 0,4, 4,4)
G(d5, 4,0, 0,0, 0,3, 3,3, 4,4, 4,5, 3,6, 0,6)
G(d6, 4,0, 1,0, 0,1, 0,5, 1,6, 3,6, 4,5, 4,4, 3,3, 0,3)
G(d7, 0,0, 4,0, 1.5,6)
G(d8, 1,0, 3,0, 4,1, 4,2, 3,3, 1,3, 0,2, 0,1, 1,0, BRK, 1,3, 0,4, 0,5, 1,6, 3,6, 4,5, 4,4, 3,3)
G(d9, 0,6, 3,6, 4,5, 4,1, 3,0, 1,0, 0,1, 0,2, 1,3, 4,3)
G(minus, 0.5,3, 3.5,3)
G(plus, 0,3, 4,3, BRK, 2,1, 2,5)
G(eq, 0.5,2, 3.5,2, BRK, 0.5,4, 3.5,4)
G(dot, 2,6, 2,6)
G(comma, 2,5.5, 1.4,7)
G(semi, 2,2, 2,2, BRK, 2,5.5, 1.4,7)
G(apos, 2,0, 2,1.6)
G(grave, 1.5,0, 2.5,1.2)
G(slash, 4,0, 0,6)
G(bslash, 0,0, 4,6)
G(lbr, 3,0, 1,0, 1,6, 3,6)
G(rbr, 1,0, 3,0, 3,6, 1,6)
G(quest, 0,1, 1,0, 3,0, 4,1, 4,2, 2,3.5, 2,4.2, BRK, 2,6, 2,6)
G(up, 2,6, 2,0, BRK, 0,2, 2,0, 4,2)
G(down, 2,0, 2,6, BRK, 0,4, 2,6, 4,4)
G(left, 4,3, 0,3, BRK, 2,1, 0,3, 2,5)
G(right, 0,3, 4,3, BRK, 2,1, 4,3, 2,5)
#undef G

static const stroke_glyph k_font[] = {
    { 'A', g_A }, { 'B', g_B }, { 'C', g_C }, { 'D', g_D }, { 'E', g_E }, { 'F', g_F },
    { 'G', g_Gg }, { 'H', g_H }, { 'I', g_I }, { 'J', g_J }, { 'K', g_K }, { 'L', g_L },
    { 'M', g_M }, { 'N', g_N }, { 'O', g_O }, { 'P', g_P }, { 'Q', g_Q }, { 'R', g_R },
    { 'S', g_S }, { 'T', g_T }, { 'U', g_U }, { 'V', g_V }, { 'W', g_W }, { 'X', g_X },
    { 'Y', g_Y }, { 'Z', g_Z },
    { '0', g_d0 }, { '1', g_d1 }, { '2', g_d2 }, { '3', g_d3 }, { '4', g_d4 },
    { '5', g_d5 }, { '6', g_d6 }, { '7', g_d7 }, { '8', g_d8 }, { '9', g_d9 },
    { '-', g_minus }, { '+', g_plus }, { '=', g_eq }, { '.', g_dot }, { ',', g_comma },
    { ';', g_semi }, { '\'', g_apos }, { '`', g_grave }, { '/', g_slash }, { '\\', g_bslash },
    { '[', g_lbr }, { ']', g_rbr }, { '?', g_quest },
    { '\x01', g_up }, { '\x02', g_down }, { '\x03', g_left }, { '\x04', g_right },
};

static const double *font_glyph(char ch)
{
    for (size_t i = 0; i < sizeof k_font / sizeof k_font[0]; i++)
        if (k_font[i].ch == ch)
            return k_font[i].pts;
    return NULL;
}

#define GLYPH_GAP 1.4

/* gaiji.py draw_text: centre text in a max_w x max_h box around (cx, cy). */
static void draw_text(canvas *cv, const char *text, double cx, double cy, double max_w, double max_h,
                      rgbaf color)
{
    char t[16];
    size_t n = 0;
    for (; text[n] && n < sizeof t - 1; n++) {
        char ch = (char)toupper((unsigned char)text[n]);
        t[n] = font_glyph(ch) ? ch : '?';
    }
    t[n] = 0;
    double tw = n ? (double)n * (4 + GLYPH_GAP) - GLYPH_GAP : 0;
    double s = fmin(2.0, fmin(max_w / (tw + 1.2), max_h / 7.2));
    double radius = fmax(0.55, 0.5 * s);
    double x = cx - tw * s / 2;
    double y = cy - 3 * s;
    static segs_t S;
    S.n = 0;
    for (size_t i = 0; i < n; i++) {
        const double *p = font_glyph(t[i]);
        double pts[64];
        int np = 0;
        for (;; p += 2) {
            if (isinf(p[0]) || isnan(p[0])) {
                if (np) segs_add(&S, pts, np);
                np = 0;
                if (isinf(p[0])) break;
                continue;
            }
            if (np < 32) {
                pts[2 * np] = x + p[0] * s;
                pts[2 * np + 1] = y + p[1] * s;
                np++;
            }
        }
        x += (4 + GLYPH_GAP) * s;
    }
    segs_fill(cv, &S, radius, color);
}

/* ------------------------------------------------------------ styles (gaiji.py) */
#define C_DARK 0x3A3A3E
#define C_EDGE 0x141416
#define C_LIGHT 0x5C5C62
#define C_WHITE 0xF4F4F4

static void draw_pad_face(canvas *cv, double x, double y, double w, double h, const char *letter,
                          uint32_t color)
{
    double cx = x + w / 2, cy = y + h / 2;
    double r = fmin(w, h) / 2 - 0.5;
    cv_ellipse(cv, cx, cy, r, r, hexc(C_EDGE));
    cv_ellipse(cv, cx, cy, r - 1.2, r - 1.2, hexc(C_LIGHT));
    cv_ellipse(cv, cx, cy + 0.6, r - 2.0, r - 2.4, hexc(C_DARK));
    draw_text(cv, letter, cx, cy + 0.3, (r - 2) * 1.5, (r - 2) * 1.45, hexc(color));
}

static void draw_pad_shoulder(canvas *cv, double x, double y, double w, double h, const char *text,
                              int trigger)
{
    double rt = trigger ? 7.0 : 4.0;
    cv_rrect(cv, x + 0.5, y + 0.5, w - 1, h - 1, 4.0, hexc(C_EDGE), rt);
    cv_rrect(cv, x + 1.5, y + 1.5, w - 3, h - 3, 3.0, hexc(C_LIGHT), rt - 1);
    cv_rrect(cv, x + 2.0, y + 2.6, w - 4, h - 4.6, 2.6, hexc(C_DARK), rt - 1.5);
    draw_text(cv, text, x + w / 2, y + h / 2 + 0.4, w - 9, h - 8, hexc(C_WHITE));
}

static void draw_keycap(canvas *cv, double x, double y, double w, double h, const char *label)
{
    cv_rrect(cv, x + 0.5, y + 0.5, w - 1, h - 1, 3.5, hexc(0x1E1E22), 3.5);
    cv_rrect(cv, x + 1.5, y + 1.5, w - 3, h - 3, 2.6, hexc(0x8C8C94), 2.6);
    cv_rrect(cv, x + 1.5, y + 1.5, w - 3, h - 5, 2.6, hexc(0xE8E8EC), 2.6);
    draw_text(cv, label, x + w / 2, y + (h - 2) / 2, w - 7, h - 9, hexc(0x18181C));
}

typedef struct { rrect_t body; double mid, split; int side; } mhalf_t;
static int in_mouse_half(const void *ctx, double px, double py)
{
    const mhalf_t *m = (const mhalf_t *)ctx;
    if (m->side < 0 ? !(px < m->mid - 0.5) : !(px > m->mid + 0.5))
        return 0;
    if (!(py < m->split - 0.5))
        return 0;
    return in_rrect_t(&m->body, px, py);
}

static void draw_mouse(canvas *cv, double x, double y, double w, double h, int which)
{
    double bw = fmin(w - 6, (h - 3) * 0.66), bh = h - 3;
    double bx = x + (w - bw) / 2, by = y + 1.5;
    cv_rrect(cv, bx, by, bw, bh, bw / 2 - 0.5, hexc(0x1E1E22), bw / 2 - 0.5);
    cv_rrect(cv, bx + 1, by + 1, bw - 2, bh - 2, bw / 2 - 1.5, hexc(0xE8E8EC), bw / 2 - 1.5);
    double split = by + bh * 0.42;
    double mid = bx + bw / 2;
    rgbaf hi = hexc(0xE3352B);
    mhalf_t m = { { bx + 1, by + 1, bw - 2, bh - 2, bw / 2 - 1.5, bw / 2 - 1.5 }, mid, split, 0 };
    if (which == 1) {
        m.side = -1;
        cv_fill(cv, in_mouse_half, &m, bx, by, mid, split, hi);
    } else if (which == 3) {
        m.side = 1;
        cv_fill(cv, in_mouse_half, &m, mid, by, bx + bw, split, hi);
    } else if (which == 2) {
        cv_rrect(cv, mid - 1.2, by + 2.5, 2.4, bh * 0.28, 1.2, hi, 1.2);
    }
    static segs_t S;
    S.n = 0;
    double l1[4] = { bx + 1, split, bx + bw - 1, split }, l2[4] = { mid, by + 1, mid, split };
    segs_add(&S, l1, 2);
    segs_add(&S, l2, 2);
    segs_fill(cv, &S, 0.5, hexc(0x1E1E22));
    if (which == 4 || which == 5)
        draw_text(cv, which == 4 ? "4" : "5", mid, split + (by + bh - split) / 2, bw - 3,
                  (by + bh - split) - 3, hexc(0x18181C));
}

/* ------------------------------------------------------------ keyboard labels */
static const struct { const char *name, *label; } k_key_labels[] = {
    { "space", "SPC" }, { "return", "ENT" }, { "tab", "TAB" }, { "backspace", "BS" },
    { "escape", "ESC" }, { "left shift", "SHF" }, { "right shift", "SHF" },
    { "left ctrl", "CTL" }, { "right ctrl", "CTL" }, { "left alt", "ALT" },
    { "right alt", "ALT" }, { "capslock", "CAP" }, { "delete", "DEL" }, { "insert", "INS" },
    { "home", "HOM" }, { "end", "END" }, { "page up", "PGU" }, { "page down", "PGD" },
    { "up", "\x01" }, { "down", "\x02" }, { "left", "\x03" }, { "right", "\x04" },
    { "comma", "," }, { "period", "." }, { "slash", "/" }, { "backslash", "\\" },
    { "semicolon", ";" }, { "apostrophe", "'" }, { "grave", "`" }, { "minus", "-" },
    { "equals", "=" }, { "leftbracket", "[" }, { "rightbracket", "]" },
    { "keypad enter", "KEN" },
};

static void str_lower_trim(const char *s, char *out, size_t cap)
{
    while (*s == ' ') s++;
    size_t n = 0;
    for (; s[n] && n < cap - 1; n++)
        out[n] = (char)tolower((unsigned char)s[n]);
    while (n && out[n - 1] == ' ') n--;
    out[n] = 0;
}

static void key_name_label(const char *name, char *out, size_t cap)
{
    char n[64];
    str_lower_trim(name, n, sizeof n);
    for (size_t i = 0; i < sizeof k_key_labels / sizeof k_key_labels[0]; i++)
        if (!strcmp(n, k_key_labels[i].name)) {
            snprintf(out, cap, "%s", k_key_labels[i].label);
            return;
        }
    if (!strncmp(n, "keypad ", 7)) {
        char sub[16];
        key_name_label(n + 7, sub, sizeof sub);
        snprintf(out, cap, "K%s", sub);
        return;
    }
    /* name.strip().upper()[:4] */
    while (*name == ' ') name++;
    size_t len = strlen(name);
    while (len && name[len - 1] == ' ') len--;
    size_t k = 0;
    for (; k < len && k < 4 && k < cap - 1; k++)
        out[k] = (char)toupper((unsigned char)name[k]);
    out[k] = 0;
}

const char *rg_gaiji_key_label(const char *binding, char *out, size_t cap, int *mouse)
{
    if (mouse) *mouse = 0;
    if (!cap) return out;
    if (!binding || !*binding) {
        snprintf(out, cap, "-");
        return out;
    }
    const char *colon = strchr(binding, ':');
    const char *name = colon ? colon + 1 : "";
    if (colon && colon - binding == 5 && !strncmp(binding, "mouse", 5)) {
        char n[16];
        str_lower_trim(name, n, sizeof n);
        int m = !strcmp(n, "left") ? 1 : !strcmp(n, "middle") ? 2 : !strcmp(n, "right") ? 3
              : !strcmp(n, "x1") ? 4 : !strcmp(n, "x2") ? 5 : 6;
        if (mouse) *mouse = m;
        out[0] = 0;
        return out;
    }
    key_name_label(name, out, cap);
    return out;
}

static void draw_glyph(canvas *cv, int style, int btn, const char *const *keys)
{
    const rg_gaiji_rect *R = &rg_gaiji_button_rects[btn];
    double x = R->u, y = R->v, w = R->w, h = R->h;
    if (style == RG_GAIJI_KEYBOARD) {
        const char *b = keys ? keys[btn] : k_default_keys[btn];
        char lab[16];
        int mouse = 0;
        rg_gaiji_key_label(b, lab, sizeof lab, &mouse);
        if (mouse)
            draw_mouse(cv, x, y, w, h, mouse);
        else
            draw_keycap(cv, x, y, w, h, lab);
        return;
    }
    static const char *const xb_sh[4] = { "LT", "LB", "RB", "RT" };
    static const char *const nt_sh[4] = { "ZL", "L", "R", "ZR" };
    if (btn <= RG_GAIJI_R2) {
        draw_pad_shoulder(cv, x, y, w, h, style == RG_GAIJI_XBOX ? xb_sh[btn] : nt_sh[btn],
                          btn == RG_GAIJI_L2 || btn == RG_GAIJI_R2);
        return;
    }
    /* face: Circle east, Triangle north, Square west, Cross south */
    static const char *const xb_l[4] = { "B", "Y", "X", "A" };
    static const uint32_t xb_c[4] = { 0xE3352B, 0xF5C400, 0x2D8FE6, 0x5DC21E };
    static const char *const nt_l[4] = { "A", "X", "Y", "B" };   /* positional */
    int f = btn - RG_GAIJI_CIRCLE;
    if (style == RG_GAIJI_XBOX)
        draw_pad_face(cv, x, y, w, h, xb_l[f], xb_c[f]);
    else
        draw_pad_face(cv, x, y, w, h, nt_l[f], C_WHITE);
}

/* ------------------------------------------------------------ quantisation (gaiji.py index_rgba) */
static double cdist(col4 a, col4 b)
{
    double aa = a.a / 128.0, ab = b.a / 128.0, d = 0.0, t;
    t = a.r * aa - b.r * ab; d += t * t;
    t = a.g * aa - b.g * ab; d += t * t;
    t = a.b * aa - b.b * ab; d += t * t;
    t = 2.0 * (a.a - b.a);
    return d + t * t;
}

#define HBITS 13
#define HSIZE (1u << HBITS)
typedef struct { uint32_t key[HSIZE]; int val[HSIZE]; uint8_t used[HSIZE]; } cmap;
static int cmap_find(const cmap *m, uint32_t k)
{
    uint32_t h = (k * 2654435761u) >> (32 - HBITS);
    while (m->used[h]) {
        if (m->key[h] == k) return m->val[h];
        h = (h + 1) & (HSIZE - 1);
    }
    return -1;
}
static void cmap_put(cmap *m, uint32_t k, int v)
{
    uint32_t h = (k * 2654435761u) >> (32 - HBITS);
    while (m->used[h] && m->key[h] != k) h = (h + 1) & (HSIZE - 1);
    m->used[h] = 1; m->key[h] = k; m->val[h] = v;
}

#define MAX_NEW 4096
typedef struct quant {
    col4 lk_col[256 + 8];      /* lookup, in gaiji.py's dict insertion order */
    int lk_idx[256 + 8];
    int nlk;
    col4 mcol[MAX_NEW];        /* colours missing from the lookup, first-seen order */
    int mcount[MAX_NEW];
    double best[MAX_NEW];
    uint8_t alive[MAX_NEW];
    int nm;
    cmap seen;                 /* colour -> missing slot */
    cmap near;                 /* colour -> resolved index */
} quant;

static int lk_find(const quant *q, col4 c)
{
    uint32_t k = col_key(c);
    for (int i = 0; i < q->nlk; i++)
        if (col_key(q->lk_col[i]) == k) return q->lk_idx[i];
    return -1;
}

static uint8_t ps2_alpha(uint8_t a8) { return (uint8_t)((a8 + 1) / 2); }

/* rint() rounds half to even, like Python's round() */
static uint8_t chan8(double v) { double r = rint(v); return (uint8_t)(r > 255 ? 255 : r < 0 ? 0 : r); }

int rg_gaiji_build(const uint8_t *orig_region, int style, const char *const *keys, uint8_t *out)
{
    if (style < 0 || style >= RG_GAIJI_STYLES)
        return -1;
    if (style == RG_GAIJI_PLAYSTATION) {
        memcpy(out, orig_region, RG_GAIJI_SWAP_BYTES);
        return 0;
    }
    const int W = RG_GAIJI_W, H = RG_GAIJI_H;
    uint8_t *idx = (uint8_t *)malloc((size_t)W * H);
    uint8_t *in_new = (uint8_t *)calloc((size_t)W * H, 1);
    canvas cv = { W, 48, (double *)calloc((size_t)W * 48 * 4, sizeof(double)) };
    quant *q = (quant *)calloc(1, sizeof *q);
    col4 pal[256];
    int rc = -1;
    if (!idx || !in_new || !cv.px || !q)
        goto done;
    region_decode(orig_region, idx, pal);
    for (int i = 0; i < 256; i++)
        if (pal[i].a > 0x80)
            goto done;
    for (int k = 0; k < RG_GAIJI_BUTTONS; k++)
        draw_glyph(&cv, style, k_draw_order[k], keys);
    for (int b = 0; b < RG_GAIJI_BUTTONS; b++) {
        const rg_gaiji_rect *R = &rg_gaiji_button_rects[b];
        for (int y = R->v; y < R->v + R->h; y++)
            for (int x = R->u; x < R->u + R->w; x++)
                in_new[y * W + x] = 1;
    }
    /* the palette: indices used outside the rects stay; the rest are free */
    uint8_t keep[256] = { 0 };
    for (int i = 0; i < W * H; i++)
        if (!in_new[i]) keep[idx[i]] = 1;
    for (int i = 0; i < 256; i++)
        if (keep[i] && lk_find(q, pal[i]) < 0) {
            q->lk_col[q->nlk] = pal[i];
            q->lk_idx[q->nlk++] = i;
        }
    if (lk_find(q, (col4){ 0, 0, 0, 0 }) < 0)
        for (int i = 0; i < 256; i++)
            if (keep[i] && pal[i].a == 0) {
                q->lk_col[q->nlk] = (col4){ 0, 0, 0, 0 };
                q->lk_idx[q->nlk++] = i;
                break;
            }
    /* the new art (Canvas.rgba -> PS2 colours), counted in raster order */
    static col4 px[RG_GAIJI_W * 48];
    for (int y = 0; y < cv.h; y++)
        for (int x = 0; x < W; x++) {
            int i = y * W + x;
            if (!in_new[i]) continue;
            const double *p = cv.px + 4 * i;
            col4 c = { 0, 0, 0, 0 };
            double pa = rint(p[3] * 128);
            if (pa != 0) {
                double f = 1.0 / p[3];
                c.r = chan8(p[0] * f * 255);
                c.g = chan8(p[1] * f * 255);
                c.b = chan8(p[2] * f * 255);
                c.a = ps2_alpha((uint8_t)(pa * 2 > 255 ? 255 : pa * 2));
            }
            px[i] = c;
            if (lk_find(q, c) >= 0) continue;
            int s = cmap_find(&q->seen, col_key(c));
            if (s < 0) {
                if (q->nm >= MAX_NEW) goto done;
                s = q->nm++;
                q->mcol[s] = c;
                q->alive[s] = 1;
                cmap_put(&q->seen, col_key(c), s);
            }
            q->mcount[s]++;
        }
    /* free slots go to the colours that would cost the most */
    if (q->nm) {
        for (int m = 0; m < q->nm; m++) {
            double b = q->nlk ? 1e300 : 1e18;
            for (int i = 0; i < q->nlk; i++) b = fmin(b, cdist(q->mcol[m], q->lk_col[i]));
            q->best[m] = b;
        }
        for (int slot = 0; slot < 256; slot++) {
            if (keep[slot]) continue;
            int pick = -1;
            double pv = 0;
            for (int m = 0; m < q->nm; m++)
                if (q->alive[m] && (pick < 0 || q->best[m] * q->mcount[m] > pv)) {
                    pick = m;
                    pv = q->best[m] * q->mcount[m];
                }
            if (pick < 0 || q->best[pick] == 0) break;
            pal[slot] = q->mcol[pick];
            q->lk_col[q->nlk] = q->mcol[pick];
            q->lk_idx[q->nlk++] = slot;
            q->alive[pick] = 0;
            for (int m = 0; m < q->nm; m++)
                if (q->alive[m]) q->best[m] = fmin(q->best[m], cdist(q->mcol[m], q->mcol[pick]));
            if (q->nlk >= 256 + 8) break;
        }
    }
    /* index the rect pixels (exact, else the nearest entry, first wins) */
    for (int y = 0; y < cv.h; y++)
        for (int x = 0; x < W; x++) {
            int i = y * W + x;
            if (!in_new[i]) continue;
            int v = lk_find(q, px[i]);
            if (v < 0) v = cmap_find(&q->near, col_key(px[i]));
            if (v < 0) {
                double bd = 0;
                for (int k = 0; k < q->nlk; k++) {
                    double d = cdist(px[i], q->lk_col[k]);
                    if (v < 0 || d < bd) { v = q->lk_idx[k]; bd = d; }
                }
                cmap_put(&q->near, col_key(px[i]), v);
            }
            idx[i] = (uint8_t)v;
        }
    region_encode(idx, pal, out);
    rc = 0;
done:
    free(idx);
    free(in_new);
    free(cv.px);
    free(q);
    return rc;
}

/* ------------------------------------------------------------ the runtime switch */
void rg_prompts_init(rg_prompts_ctl *c)
{
    memset(c, 0, sizeof *c);
    c->cur = RG_GAIJI_PLAYSTATION;
}

void rg_prompts_free(rg_prompts_ctl *c)
{
    free(c->orig);
    for (int i = 0; i < RG_GAIJI_STYLES; i++)
        free(c->img[i]);
    memset(c, 0, sizeof *c);
}

static uint32_t keys_hash(const char *const *keys)
{
    uint32_t h = 2166136261u;
    for (int b = 0; b < RG_GAIJI_BUTTONS; b++) {
        const char *s = keys ? (keys[b] ? keys[b] : "") : k_default_keys[b];
        for (; *s; s++) h = (h ^ (uint8_t)*s) * 16777619u;
        h = (h ^ 0xFF) * 16777619u;
    }
    return h;
}

static void drop_images(rg_prompts_ctl *c)
{
    for (int i = 0; i < RG_GAIJI_STYLES; i++) {
        free(c->img[i]);
        c->img[i] = NULL;
    }
}

int rg_prompts_step(rg_prompts_ctl *c, uint8_t *buf, size_t cap, int wanted, const char *const *keys)
{
    rg_gaiji_layout L;
    if (wanted < 0 || wanted >= RG_GAIJI_STYLES)
        wanted = RG_GAIJI_PLAYSTATION;
    if (rg_gaiji_layout_of(buf, cap, &L) != 0)
        return 0;
    uint8_t *region = buf + L.pixels;
    const uint8_t *expect = c->cur == RG_GAIJI_PLAYSTATION ? c->orig : c->img[c->cur];
    if (!c->have_orig || !expect || memcmp(region, expect, RG_GAIJI_SWAP_BYTES) != 0) {
        /* first sight, or the game loaded the file again: that is the original */
        if (!c->orig && !(c->orig = (uint8_t *)malloc(RG_GAIJI_SWAP_BYTES)))
            return 0;
        memcpy(c->orig, region, RG_GAIJI_SWAP_BYTES);
        c->have_orig = 1;
        c->cur = RG_GAIJI_PLAYSTATION;
        c->captures++;
        drop_images(c);
    }
    uint32_t kh = wanted == RG_GAIJI_KEYBOARD ? keys_hash(keys) : 0;
    if (wanted == c->cur && (wanted != RG_GAIJI_KEYBOARD || kh == c->keys_hash))
        return 0;
    const uint8_t *src = c->orig;
    if (wanted != RG_GAIJI_PLAYSTATION) {
        if (wanted == RG_GAIJI_KEYBOARD && c->img[wanted] && kh != c->keys_hash) {
            free(c->img[wanted]);
            c->img[wanted] = NULL;
        }
        if (!c->img[wanted]) {
            uint8_t *im = (uint8_t *)malloc(RG_GAIJI_SWAP_BYTES);
            if (!im || rg_gaiji_build(c->orig, wanted, keys, im) != 0) {
                free(im);
                return 0;
            }
            c->img[wanted] = im;
            if (wanted == RG_GAIJI_KEYBOARD) c->keys_hash = kh;
        }
        src = c->img[wanted];
    }
    memcpy(region, src, RG_GAIJI_SWAP_BYTES);
    c->cur = wanted;
    c->writes++;
    return 1;
}
