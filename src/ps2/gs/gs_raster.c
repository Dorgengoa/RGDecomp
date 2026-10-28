/* SPDX-License-Identifier: CC0-1.0 */
/* Software reference rasterizer: primitive setup (points, lines, triangles,
 * sprites), attribute interpolation, texture function, fog, alpha test,
 * destination alpha test, depth test, alpha blending, dithering, COLCLAMP,
 * FBA, FBMSK/ZMSK.  docs/GS.md "Rasterizer" lists the rules and the places
 * where hardware rounding is approximated. */
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "gs_internal.h"

typedef struct dctx {
    int iip, tme, fge, abe, fst;
    uint32_t fbp, fbw, fbmsk; int fpsm;
    uint32_t zbp; int zpsm, zmsk;
    int ofx, ofy;
    int scx0, scx1, scy0, scy1;
    int a, b, c, d; uint32_t fix;
    int ate, atst, afail; uint32_t aref;
    int date, datm, zte, ztst;
    int fba, pabe, colclamp, dthe;
    int dimx[4][4];
    uint32_t fogcol;
    int scanmsk;
    int tfx, tcc, tw, th;
    gs_texctx tc;
    const gs_state *texmem;   /* the memory texels are read from (tex_snapshot) */
} dctx;

static void dctx_init(const gs_state *gs, dctx *d)
{
    uint64_t prim = gs->reg[GS_PRIM];
    uint64_t attr = (gs->reg[GS_PRMODECONT] & 1) ? prim : gs->reg[GS_PRMODE];
    int c = (int)GS_BITS(attr, 9, 1);
    memset(d, 0, sizeof *d);
    d->iip = (int)GS_BITS(attr, 3, 1);
    d->tme = (int)GS_BITS(attr, 4, 1);
    d->fge = (int)GS_BITS(attr, 5, 1);
    d->abe = (int)GS_BITS(attr, 6, 1);
    d->fst = (int)GS_BITS(attr, 8, 1);

    uint64_t fr = gs->reg[GS_FRAME_1 + c];
    d->fbp = GS_BITS(fr, 0, 9) * 32u;
    d->fbw = GS_BITS(fr, 16, 6);
    d->fpsm = (int)GS_BITS(fr, 24, 6);
    d->fbmsk = GS_BITS(fr, 32, 32);
    uint64_t zb = gs->reg[GS_ZBUF_1 + c];
    d->zbp = GS_BITS(zb, 0, 9) * 32u;
    d->zpsm = (int)GS_BITS(zb, 24, 4) | 0x30;
    d->zmsk = (int)GS_BITS(zb, 32, 1);
    uint64_t xo = gs->reg[GS_XYOFFSET_1 + c];
    d->ofx = (int)GS_BITS(xo, 0, 16);
    d->ofy = (int)GS_BITS(xo, 32, 16);
    uint64_t sc = gs->reg[GS_SCISSOR_1 + c];
    d->scx0 = (int)GS_BITS(sc, 0, 11); d->scx1 = (int)GS_BITS(sc, 16, 11);
    d->scy0 = (int)GS_BITS(sc, 32, 11); d->scy1 = (int)GS_BITS(sc, 48, 11);
    uint64_t al = gs->reg[GS_ALPHA_1 + c];
    d->a = (int)GS_BITS(al, 0, 2); d->b = (int)GS_BITS(al, 2, 2);
    d->c = (int)GS_BITS(al, 4, 2); d->d = (int)GS_BITS(al, 6, 2);
    d->fix = GS_BITS(al, 32, 8);
    uint64_t te = gs->reg[GS_TEST_1 + c];
    d->ate = (int)GS_BITS(te, 0, 1); d->atst = (int)GS_BITS(te, 1, 3);
    d->aref = GS_BITS(te, 4, 8); d->afail = (int)GS_BITS(te, 12, 2);
    d->date = (int)GS_BITS(te, 14, 1); d->datm = (int)GS_BITS(te, 15, 1);
    d->zte = (int)GS_BITS(te, 16, 1); d->ztst = (int)GS_BITS(te, 17, 2);
    d->fba = (int)GS_BITS(gs->reg[GS_FBA_1 + c], 0, 1);
    d->pabe = (int)GS_BITS(gs->reg[GS_PABE], 0, 1);
    d->colclamp = (int)GS_BITS(gs->reg[GS_COLCLAMP], 0, 1);
    d->dthe = (int)GS_BITS(gs->reg[GS_DTHE], 0, 1);
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            int v = (int)GS_BITS(gs->reg[GS_DIMX], i * 16 + j * 4, 3);
            d->dimx[i][j] = v >= 4 ? v - 8 : v;
        }
    d->fogcol = GS_BITS(gs->reg[GS_FOGCOL], 0, 24);
    d->scanmsk = (int)GS_BITS(gs->reg[GS_SCANMSK], 0, 2);

    d->tc.tex0 = gs->reg[GS_TEX0_1 + c];
    d->tc.tex1 = gs->reg[GS_TEX1_1 + c];
    d->tc.clamp = gs->reg[GS_CLAMP_1 + c];
    d->tc.miptbp1 = gs->reg[GS_MIPTBP1_1 + c];
    d->tc.miptbp2 = gs->reg[GS_MIPTBP2_1 + c];
    d->tc.texa = gs->reg[GS_TEXA];
    d->tc.fst = d->fst;
    d->tfx = (int)GS_BITS(d->tc.tex0, 35, 2);
    d->tcc = (int)GS_BITS(d->tc.tex0, 34, 1);
    d->tw = (int)GS_BITS(d->tc.tex0, 26, 4);
    d->th = (int)GS_BITS(d->tc.tex0, 30, 4);
    if (d->tw > 10) d->tw = 10;
    if (d->th > 10) d->th = 10;
}

/* interpolated fragment inputs */
typedef struct frag {
    double z;
    double r, g, b, a;
    double s, t, q;   /* STQ */
    double u, v;      /* UV in 10.4 units */
    double f;
} frag;

static int alpha_test(int atst, uint32_t a, uint32_t ref)
{
    switch (atst) {
    case 0: return 0;
    case 1: return 1;
    case 2: return a < ref;
    case 3: return a <= ref;
    case 4: return a == ref;
    case 5: return a >= ref;
    case 6: return a > ref;
    default: return a != ref;
    }
}

static uint32_t clamp255(int v) { return (uint32_t)gs_clampi(v, 0, 255); }

/* texture function; returns the fragment colour RGBA8 */
static uint32_t tex_function(const dctx *d, uint32_t t, uint32_t cr, uint32_t cg,
                             uint32_t cb, uint32_t ca)
{
    uint32_t tr = t & 255u, tg = (t >> 8) & 255u, tb = (t >> 16) & 255u, ta = t >> 24;
    uint32_t r, g, b, a;
    switch (d->tfx) {
    case 0: /* MODULATE */
        r = clamp255((int)((tr * cr) >> 7)); g = clamp255((int)((tg * cg) >> 7));
        b = clamp255((int)((tb * cb) >> 7));
        a = d->tcc ? clamp255((int)((ta * ca) >> 7)) : ca;
        break;
    case 1: /* DECAL */
        r = tr; g = tg; b = tb; a = d->tcc ? ta : ca;
        break;
    case 2: /* HIGHLIGHT */
        r = clamp255((int)((tr * cr) >> 7) + (int)ca);
        g = clamp255((int)((tg * cg) >> 7) + (int)ca);
        b = clamp255((int)((tb * cb) >> 7) + (int)ca);
        a = d->tcc ? clamp255((int)(ta + ca)) : ca;
        break;
    default: /* HIGHLIGHT2 */
        r = clamp255((int)((tr * cr) >> 7) + (int)ca);
        g = clamp255((int)((tg * cg) >> 7) + (int)ca);
        b = clamp255((int)((tb * cb) >> 7) + (int)ca);
        a = d->tcc ? ta : ca;
        break;
    }
    return r | (g << 8) | (b << 16) | (a << 24);
}

static uint32_t zmax(int zpsm)
{
    switch (zpsm) {
    case GS_PSMZ24: return 0xFFFFFFu;
    case GS_PSMZ16: case GS_PSMZ16S: return 0xFFFFu;
    default: return 0xFFFFFFFFu;
    }
}

/* The per-pixel pipeline after rasterization.  x,y are window pixels. */
static void pixel(gs_state *gs, const dctx *d, int x, int y, const frag *fr,
                  int textured)
{
    if (x < d->scx0 || x > d->scx1 || y < d->scy0 || y > d->scy1) return;
    if (d->scanmsk == 2 && (y & 1)) return;
    if (d->scanmsk == 3 && !(y & 1)) return;
    gs->stats.pixels_tested++;

    uint32_t cr = (uint32_t)gs_clampi((int)fr->r, 0, 255);
    uint32_t cg = (uint32_t)gs_clampi((int)fr->g, 0, 255);
    uint32_t cb = (uint32_t)gs_clampi((int)fr->b, 0, 255);
    uint32_t ca = (uint32_t)gs_clampi((int)fr->a, 0, 255);
    uint32_t col = cr | (cg << 8) | (cb << 16) | (ca << 24);

    if (textured) {
        double u, v, lod;
        double W = (double)(1 << d->tw), H = (double)(1 << d->th);
        double q = fr->q;
        if (d->fst) {
            u = fr->u / 16.0; v = fr->v / 16.0;
        } else {
            double qq = q == 0.0 ? 1e-30 : q;
            u = fr->s / qq * W; v = fr->t / qq * H;
        }
        lod = gs_tex_lod(&d->tc, q);
        uint32_t t = gs_tex_sample(d->texmem, &d->tc, u, v, lod);
        col = tex_function(d, t, cr, cg, cb, ca);
    }
    if (d->fge) {
        uint32_t f = (uint32_t)gs_clampi((int)fr->f, 0, 255);
        uint32_t out = col & 0xFF000000u;
        for (int ch = 0; ch < 24; ch += 8) {
            uint32_t c = (col >> ch) & 255u, fc = (d->fogcol >> ch) & 255u;
            out |= ((f * c + (255u - f) * fc) >> 8) << ch;
        }
        col = out;
    }

    uint32_t as = col >> 24;
    int fb_write = 1, z_write = !d->zmsk, a_write = 1;
    if (d->ate && !alpha_test(d->atst, as, d->aref)) {
        switch (d->afail) {
        case 0: return;
        case 1: z_write = 0; break;          /* FB_ONLY */
        case 2: fb_write = 0; break;         /* ZB_ONLY */
        default: z_write = 0; a_write = 0; break; /* RGB_ONLY */
        }
    }

    int f16 = gs_psm_is16(d->fpsm);
    uint32_t draw = 0;
    int have_dst = 0;
    if (d->date) {
        draw = gs_read_pixel(gs, d->fpsm, d->fbp, d->fbw, (uint32_t)x, (uint32_t)y);
        have_dst = 1;
        if (d->fpsm == GS_PSMCT32 || f16) {
            uint32_t bit = f16 ? (draw >> 15) & 1u : (draw >> 31);
            if ((int)bit != d->datm) return;
        }
    }

    uint32_t z = (uint32_t)(fr->z < 0.0 ? 0.0 : (fr->z > 4294967295.0 ? 4294967295.0 : fr->z));
    uint32_t zm = zmax(d->zpsm);
    if (z > zm) z = zm;
    if (d->zte) {
        uint32_t zd;
        switch (d->ztst) {
        case 0: return;
        case 1: break;
        case 2:
            zd = gs_read_pixel(gs, d->zpsm, d->zbp, d->fbw, (uint32_t)x, (uint32_t)y);
            if (z < zd) return;
            break;
        default:
            zd = gs_read_pixel(gs, d->zpsm, d->zbp, d->fbw, (uint32_t)x, (uint32_t)y);
            if (z <= zd) return;
            break;
        }
    }

    if (fb_write) {
        if (!have_dst)
            draw = gs_read_pixel(gs, d->fpsm, d->fbp, d->fbw, (uint32_t)x, (uint32_t)y);
        uint32_t dcol = gs_color_from_stored(d->fpsm, draw);
        uint32_t ad = (d->fpsm == GS_PSMCT24) ? 0x80u : (dcol >> 24);
        int rgb[3];
        for (int ch = 0; ch < 3; ch++) rgb[ch] = (int)((col >> (ch * 8)) & 255u);
        if (d->abe && !(d->pabe && !(as & 0x80u))) {
            int cc = d->c == 0 ? (int)as : (d->c == 1 ? (int)ad : (int)d->fix);
            for (int ch = 0; ch < 3; ch++) {
                int cs = (int)((col >> (ch * 8)) & 255u);
                int cdv = (int)((dcol >> (ch * 8)) & 255u);
                int A = d->a == 0 ? cs : (d->a == 1 ? cdv : 0);
                int B = d->b == 0 ? cs : (d->b == 1 ? cdv : 0);
                int D = d->d == 0 ? cs : (d->d == 1 ? cdv : 0);
                rgb[ch] = (((A - B) * cc) >> 7) + D;
            }
        }
        if (d->dthe && f16) {
            int dv = d->dimx[y & 3][x & 3];
            for (int ch = 0; ch < 3; ch++) rgb[ch] += dv;
        }
        uint32_t out = 0;
        for (int ch = 0; ch < 3; ch++) {
            int v = rgb[ch];
            v = d->colclamp ? gs_clampi(v, 0, 255) : (v & 255);
            out |= (uint32_t)v << (ch * 8);
        }
        uint32_t aout = as | (d->fba ? 0x80u : 0u);
        out |= (aout & 255u) << 24;
        uint32_t nraw = gs_color_to_stored(d->fpsm, out);
        uint32_t mask = gs_color_to_stored(d->fpsm, d->fbmsk);
        if (!a_write) mask |= f16 ? 0x8000u : 0xFF000000u;
        nraw = (draw & mask) | (nraw & ~mask);
        if (d->fpsm == GS_PSMCT24) nraw &= 0xFFFFFFu;
        gs_write_pixel(gs, d->fpsm, d->fbp, d->fbw, (uint32_t)x, (uint32_t)y, nraw);
        gs->stats.pixels_written++;
    }
    if (z_write)
        gs_write_pixel(gs, d->zpsm, d->zbp, d->fbw, (uint32_t)x, (uint32_t)y, z);
}

/* ---- vertex -> fragment attributes ---- */
typedef struct wv {
    int64_t x, y;   /* window 12.4 */
    frag a;
} wv;

static void to_wv(const dctx *d, const gs_vertex *v, wv *o)
{
    o->x = (int64_t)v->x - d->ofx;
    o->y = (int64_t)v->y - d->ofy;
    o->a.z = (double)v->z;
    o->a.r = v->r; o->a.g = v->g; o->a.b = v->b; o->a.a = v->a;
    o->a.s = v->s; o->a.t = v->t; o->a.q = v->q;
    o->a.u = v->u; o->a.v = v->v;
    o->a.f = v->f;
}

/* Written as a + (b-a)*w1 + (c-a)*w2 (w0 = 1-w1-w2): an attribute that is
 * the same at all three vertices is exactly that value at every fragment
 * (a*w0 + b*w1 + c*w2 can land one ulp below it, and truncation then loses
 * a whole unit: a constant-Z triangle wrote z-1 at scattered pixels). */
static void lerp3(frag *o, const frag *a, const frag *b, const frag *c,
                  double w0, double w1, double w2)
{
    (void)w0;
#define L3(m) o->m = a->m + (b->m - a->m) * w1 + (c->m - a->m) * w2
    L3(z); L3(r); L3(g); L3(b); L3(a); L3(s); L3(t); L3(q); L3(u); L3(v); L3(f);
#undef L3
}

static void lerp2(frag *o, const frag *a, const frag *b, double t)
{
#define L2(m) o->m = a->m + (b->m - a->m) * t
    L2(z); L2(r); L2(g); L2(b); L2(a); L2(s); L2(t); L2(q); L2(u); L2(v); L2(f);
#undef L2
}

/* flat shading: colour (and fog) from the provoking vertex */
static void apply_flat(const dctx *d, frag *o, const frag *pv)
{
    if (d->iip) return;
    o->r = pv->r; o->g = pv->g; o->b = pv->b; o->a = pv->a;
    o->f = pv->f;
}

static int ceil16(int64_t v) { return (int)((v + 15) >> 4); }   /* v in 12.4 */

static void draw_point(gs_state *gs, const dctx *d, const wv *v)
{
    pixel(gs, d, ceil16(v->x), ceil16(v->y), &v->a, d->tme);
}

/* floor(a / 2^k) for signed a */
static int64_t fsr(int64_t a, int k)
{
    return a >= 0 ? a >> k : -((-a + ((int64_t)1 << k) - 1) >> k);
}

int64_t gs_sprite_uv_step(int64_t c0, int64_t c1, int64_t p0, int64_t p1)
{
    int64_t dp = p1 - p0;
    if (dp <= 0) return 0;
    int64_t s = ((c1 - c0) * ((int64_t)1 << 20)) / dp;   /* truncates toward zero */
    if (s > INT32_MAX) s = INT32_MAX;
    if (s < INT32_MIN) s = INT32_MIN;
    return s;
}

int32_t gs_sprite_uv_at(int64_t c0, int64_t p0, int64_t step, int px)
{
    return (int32_t)fsr(c0 * 65536 + fsr(step * ((int64_t)px * 16 - p0), 4), 16);
}

static void draw_sprite(gs_state *gs, const dctx *d, const wv *v0, const wv *v1)
{
    int64_t x0 = v0->x, x1 = v1->x, y0 = v0->y, y1 = v1->y;
    frag base = v1->a;   /* colour, Z, fog, Q from the second vertex */
    double s0 = v0->a.s, s1 = v1->a.s, t0 = v0->a.t, t1 = v1->a.t;
    double u0 = v0->a.u, u1 = v1->a.u, vv0 = v0->a.v, vv1 = v1->a.v;
    if (x1 < x0) { int64_t tt = x0; x0 = x1; x1 = tt; double q = s0; s0 = s1; s1 = q; q = u0; u0 = u1; u1 = q; }
    if (y1 < y0) { int64_t tt = y0; y0 = y1; y1 = tt; double q = t0; t0 = t1; t1 = q; q = vv0; vv0 = vv1; vv1 = q; }
    int px0 = ceil16(x0), px1 = ceil16(x1), py0 = ceil16(y0), py1 = ceil16(y1);
    if (px0 < d->scx0) px0 = d->scx0;
    if (px1 > d->scx1 + 1) px1 = d->scx1 + 1;
    if (py0 < d->scy0) py0 = d->scy0;
    if (py1 > d->scy1 + 1) py1 = d->scy1 + 1;
    double dx = (double)(x1 - x0), dy = (double)(y1 - y0);
    /* UV (FST=1): the fixed-point DDA of GS.md rule 3 */
    int64_t U0 = (int64_t)u0, V0 = (int64_t)vv0;
    int64_t du = gs_sprite_uv_step(U0, (int64_t)u1, x0, x1);
    int64_t dv = gs_sprite_uv_step(V0, (int64_t)vv1, y0, y1);
    for (int py = py0; py < py1; py++) {
        double fy = dy > 0 ? ((double)py * 16.0 - (double)y0) / dy : 0.0;
        double vy = (double)gs_sprite_uv_at(V0, y0, dv, py);
        for (int px = px0; px < px1; px++) {
            double fx = dx > 0 ? ((double)px * 16.0 - (double)x0) / dx : 0.0;
            frag f = base;
            f.s = s0 + (s1 - s0) * fx; f.u = (double)gs_sprite_uv_at(U0, x0, du, px);
            f.t = t0 + (t1 - t0) * fy; f.v = vy;
            pixel(gs, d, px, py, &f, d->tme);
        }
    }
}

static void draw_line(gs_state *gs, const dctx *d, const wv *v0, const wv *v1)
{
    int64_t dx = v1->x - v0->x, dy = v1->y - v0->y;
    int64_t adx = dx < 0 ? -dx : dx, ady = dy < 0 ? -dy : dy;
    if (adx == 0 && ady == 0) return;
    int xmajor = adx >= ady;
    int64_t a0 = xmajor ? v0->x : v0->y, a1 = xmajor ? v1->x : v1->y;
    int64_t b0 = xmajor ? v0->y : v0->x;
    double da = (double)(a1 - a0), db = (double)(xmajor ? dy : dx);
    int64_t lo = a0 < a1 ? a0 : a1, hi = a0 < a1 ? a1 : a0;
    for (int p = ceil16(lo); p < ceil16(hi); p++) {
        double t = ((double)p * 16.0 - (double)a0) / da;
        double bb = (double)b0 + db * t;
        int q = (int)floor((bb + 8.0) / 16.0);
        frag f;
        lerp2(&f, &v0->a, &v1->a, t);
        apply_flat(d, &f, &v1->a);
        if (xmajor) pixel(gs, d, p, q, &f, d->tme);
        else pixel(gs, d, q, p, &f, d->tme);
    }
}

static int64_t edgef(const wv *a, const wv *b, int64_t px, int64_t py)
{
    return (b->x - a->x) * (py - a->y) - (b->y - a->y) * (px - a->x);
}
static int topleft(const wv *a, const wv *b)
{
    int64_t dx = b->x - a->x, dy = b->y - a->y;
    return dy < 0 || (dy == 0 && dx > 0);
}

static void draw_triangle(gs_state *gs, const dctx *d, const wv *v0,
                          const wv *v1, const wv *v2)
{
    const wv *pv = v2; /* provoking vertex: the one that kicked */
    int64_t area = edgef(v0, v1, v2->x, v2->y);
    if (area == 0) return;
    if (area < 0) { const wv *t = v1; v1 = v2; v2 = t; area = -area; }
    int64_t minx = v0->x, maxx = v0->x, miny = v0->y, maxy = v0->y;
    const wv *vs[3] = { v0, v1, v2 };
    for (int i = 1; i < 3; i++) {
        if (vs[i]->x < minx) minx = vs[i]->x;
        if (vs[i]->x > maxx) maxx = vs[i]->x;
        if (vs[i]->y < miny) miny = vs[i]->y;
        if (vs[i]->y > maxy) maxy = vs[i]->y;
    }
    int px0 = ceil16(minx), px1 = (int)(maxx >> 4), py0 = ceil16(miny), py1 = (int)(maxy >> 4);
    if (px0 < d->scx0) px0 = d->scx0;
    if (px1 > d->scx1) px1 = d->scx1;
    if (py0 < d->scy0) py0 = d->scy0;
    if (py1 > d->scy1) py1 = d->scy1;
    int b0 = topleft(v1, v2) ? 0 : -1, b1 = topleft(v2, v0) ? 0 : -1,
        b2 = topleft(v0, v1) ? 0 : -1;
    double inv = 1.0 / (double)area;
    for (int py = py0; py <= py1; py++) {
        for (int px = px0; px <= px1; px++) {
            int64_t X = (int64_t)px * 16, Y = (int64_t)py * 16;
            int64_t e0 = edgef(v1, v2, X, Y), e1 = edgef(v2, v0, X, Y),
                    e2 = edgef(v0, v1, X, Y);
            if (e0 + b0 < 0 || e1 + b1 < 0 || e2 + b2 < 0) continue;
            frag f;
            lerp3(&f, &v0->a, &v1->a, &v2->a, (double)e0 * inv, (double)e1 * inv,
                  (double)e2 * inv);
            apply_flat(d, &f, &pv->a);
            pixel(gs, d, px, py, &f, d->tme);
        }
    }
}

/* ---- texture reads within a primitive ----
 * A primitive samples local memory as it was when the primitive started:
 * its own colour and Z writes are not seen by its texture reads.  The GS
 * reads texels through its texture buffer, which drawing does not update
 * (the GS manual has software flush it with TEXFLUSH after drawing into a
 * texture), so a primitive that samples the area it draws into does not
 * see its own pixels; the game's in-place blur passes (32-pixel strips
 * adding the buffer shifted by a pixel to itself) are written for that.
 * Primitives see what earlier primitives drew (TEXFLUSH is a no-op here).
 * docs/GPU.md "Checkpoint 4".  Implemented by sampling a copy of the
 * texture's pages when the primitive can write any of them. */
int gs_tex_snapshot_off;   /* test control only: sample memory as it is written */
uint64_t gs_tex_snapshots;  /* primitives that sampled a snapshot (all gs_states) */

typedef struct pageset { uint32_t w[16]; } pageset;

static void ps_rect(pageset *p, uint32_t bp, uint32_t bw, int psm, int x0, int y0, int x1, int y1)
{
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > 2048) x1 = 2048;
    if (y1 > 2048) y1 = 2048;
    if (x1 <= x0 || y1 <= y0) return;
    if (bw == 0) bw = 1;
    int pw = 64, ph = 32;
    uint32_t bwp = bw;
    if (gs_psm_is16(psm)) { pw = 64; ph = 64; }
    else if (psm == GS_PSMT8) { pw = 128; ph = 64; bwp = bw >> 1; }
    else if (psm == GS_PSMT4) { pw = 128; ph = 128; bwp = bw >> 1; }
    if (bwp == 0) bwp = 1;
    uint32_t base = bp >> 5;
    int spill = (bp & 31) != 0;
    for (int r = y0 / ph; r <= (y1 - 1) / ph; r++)
        for (int c = x0 / pw; c <= (x1 - 1) / pw; c++) {
            uint32_t pg = (base + (uint32_t)c + (uint32_t)r * bwp) & 511u;
            p->w[pg >> 5] |= 1u << (pg & 31);
            if (spill) { pg = (pg + 1) & 511u; p->w[pg >> 5] |= 1u << (pg & 31); }
        }
}

/* one axis of a texture level: every texel the wrap mode can address */
static int tex_extent(int size, int mode, int mn, int mx)
{
    int e = size;
    if (mode == 2 && mx + 1 > e) e = mx + 1;
    if (mode == 3 && (mn | mx) + 1 > e) e = (mn | mx) + 1;
    return e;
}

static int tex_snapshot(const gs_state *gs, const dctx *d, const wv *w, int nv, int type,
                        gs_state *view)
{
    /* the primitive's pixel box (conservative), inside the scissor */
    int64_t lx = w[0].x, hx = w[0].x, ly = w[0].y, hy = w[0].y;
    for (int i = 1; i < nv; i++) {
        if (w[i].x < lx) lx = w[i].x;
        if (w[i].x > hx) hx = w[i].x;
        if (w[i].y < ly) ly = w[i].y;
        if (w[i].y > hy) hy = w[i].y;
    }
    (void)type;
    int x0 = (int)(lx >> 4) - 1, x1 = (int)(hx >> 4) + 2, y0 = (int)(ly >> 4) - 1, y1 = (int)(hy >> 4) + 2;
    if (x0 < d->scx0) x0 = d->scx0;
    if (y0 < d->scy0) y0 = d->scy0;
    if (x1 > d->scx1 + 1) x1 = d->scx1 + 1;
    if (y1 > d->scy1 + 1) y1 = d->scy1 + 1;
    if (x1 <= x0 || y1 <= y0) return 0;
    pageset wr, tx;
    memset(&wr, 0, sizeof wr);
    memset(&tx, 0, sizeof tx);
    ps_rect(&wr, d->fbp, d->fbw, d->fpsm, x0, y0, x1, y1);
    if (!d->zmsk) ps_rect(&wr, d->zbp, d->fbw, d->zpsm, x0, y0, x1, y1);
    const gs_texctx *tc = &d->tc;
    int psm = (int)GS_BITS(tc->tex0, 20, 6);
    int mxl = (int)GS_BITS(tc->tex1, 2, 3), mmin = (int)GS_BITS(tc->tex1, 6, 3);
    if (mxl > 6) mxl = 6;
    if (mmin < 2 || mmin > 5) mxl = 0;
    int wms = (int)GS_BITS(tc->clamp, 0, 2), wmt = (int)GS_BITS(tc->clamp, 2, 2);
    int minu = (int)GS_BITS(tc->clamp, 4, 10), maxu = (int)GS_BITS(tc->clamp, 14, 10);
    int minv = (int)GS_BITS(tc->clamp, 24, 10), maxv = (int)GS_BITS(tc->clamp, 34, 10);
    for (int k = 0; k <= mxl; k++) {
        uint32_t tbp, tbw;
        if (k == 0) { tbp = GS_BITS(tc->tex0, 0, 14); tbw = GS_BITS(tc->tex0, 14, 6); }
        else {
            uint64_t m = k <= 3 ? tc->miptbp1 : tc->miptbp2;
            int j = (k - 1) % 3;
            tbp = GS_BITS(m, j * 20, 14); tbw = GS_BITS(m, j * 20 + 14, 6);
        }
        int W = 1 << (d->tw - k < 0 ? 0 : d->tw - k), H = 1 << (d->th - k < 0 ? 0 : d->th - k);
        ps_rect(&tx, tbp, tbw, psm, 0, 0, tex_extent(W, wms, k > 0 && wms == 2 ? minu >> k : minu,
                k > 0 && wms == 2 ? maxu >> k : maxu), tex_extent(H, wmt, k > 0 && wmt == 2 ? minv >> k : minv,
                k > 0 && wmt == 2 ? maxv >> k : maxv));
    }
    int hit = 0;
    for (int i = 0; i < 16; i++) hit |= (wr.w[i] & tx.w[i]) != 0;
    if (!hit) return 0;
    static _Thread_local uint8_t *snap;
    if (!snap) snap = (uint8_t *)malloc(GS_VRAM_BYTES);
    if (!snap) return 0;
    for (uint32_t pg = 0; pg < 512; pg++)
        if ((tx.w[pg >> 5] >> (pg & 31)) & 1u) memcpy(snap + pg * 8192u, gs->vram + pg * 8192u, 8192u);
    *view = *gs;
    view->vram = snap;
    gs_tex_snapshots++;
    return 1;
}

void gs_draw_kick(gs_state *gs, const gs_vertex *v, int nv, int prim_type)
{
    dctx d;
    wv w[3];
    gs->stats.prims[prim_type & 7]++;
    if (gs__fx_on) gs__fx_prim(prim_type);
    if (gs__feat_on) gs__feat_prim(gs, v, nv, prim_type);
    if (gs->hooks.draw) gs->hooks.draw(gs->hooks.user, gs, v, nv, prim_type);
    if (!gs->sw_raster) return;
    dctx_init(gs, &d);
    for (int i = 0; i < nv; i++) to_wv(&d, &v[i], &w[i]);
    d.texmem = gs;
    gs_state view;
    if (d.tme && !gs_tex_snapshot_off && tex_snapshot(gs, &d, w, nv, prim_type, &view)) d.texmem = &view;
    switch (prim_type) {
    case GS_PRIM_POINT: draw_point(gs, &d, &w[0]); break;
    case GS_PRIM_LINE: case GS_PRIM_LINESTRIP: draw_line(gs, &d, &w[0], &w[1]); break;
    case GS_PRIM_TRIANGLE: case GS_PRIM_TRISTRIP: case GS_PRIM_TRIFAN:
        draw_triangle(gs, &d, &w[0], &w[1], &w[2]);
        break;
    case GS_PRIM_SPRITE: draw_sprite(gs, &d, &w[0], &w[1]); break;
    default: break;
    }
}
