/* SPDX-License-Identifier: CC0-1.0 */
/* GPU-vs-reference scenes beyond the tests/gs golden set: every frame and
 * Z format, the census blend presets (and all 81 A/B/C/D combinations),
 * every texture format incl. CLUT (CSM1/CSM2, CSA, CT16/CT32 palettes, TEXA),
 * wrap and filter modes, the pixel-test matrix, coherence (readback,
 * local->local, upload over a target, render-to-texture, CLUT from a
 * target) and the display merge.  Each scene drives a software-reference
 * gs_state and a GPU-rendered one with identical GIF packets. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu_compare.h"
#include "gpu_tests.h"

#define PRIM_IIP (1u << 3)
#define PRIM_TME (1u << 4)
#define PRIM_FGE (1u << 5)
#define PRIM_ABE (1u << 6)
#define PRIM_FST (1u << 8)
#define PRIM_CTXT2 (1u << 9)

typedef struct dual {
    gs_state *sw, *hw;
    gpu_renderer *r;
} dual;

/* ------------------------------------------------------------ packets */
static uint64_t g_q[2 * 65536];
static uint32_t g_n;

static void qw(uint64_t lo, uint64_t hi)
{
    g_q[2 * g_n] = lo;
    g_q[2 * g_n + 1] = hi;
    g_n++;
}
static void send(dual *d)
{
    if (!g_n) return;
    gs_gif_write(d->sw, GS_PATH3, g_q, g_n);
    gs_gif_write(d->hw, GS_PATH3, g_q, g_n);
    g_n = 0;
}
/* A+D writes accumulate in one PACKED packet */
static uint32_t g_tag = 0xFFFFFFFFu;
static void ad(dual *d, uint32_t reg, uint64_t v)
{
    if (g_n > 2 * 65536 / 2 - 8) {
        g_q[2 * g_tag] = (uint64_t)(g_n - g_tag - 1) | (1ull << 15) | (1ull << 60);
        send(d);
        g_tag = 0xFFFFFFFFu;
    }
    if (g_tag == 0xFFFFFFFFu) { g_tag = g_n; qw(0, 0xE); }
    qw(v, reg);
}
static void flush(dual *d)
{
    if (g_tag != 0xFFFFFFFFu) {
        g_q[2 * g_tag] = (uint64_t)(g_n - g_tag - 1) | (1ull << 15) | (1ull << 60);
        g_tag = 0xFFFFFFFFu;
    }
    send(d);
}

static uint64_t r_frame(uint32_t fbp, uint32_t fbw, uint32_t psm, uint32_t msk)
{ return fbp | ((uint64_t)fbw << 16) | ((uint64_t)psm << 24) | ((uint64_t)msk << 32); }
static uint64_t r_zbuf(uint32_t zbp, uint32_t psm, int zmsk)
{ return zbp | ((uint64_t)(psm & 15) << 24) | ((uint64_t)zmsk << 32); }
static uint64_t r_scissor(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1)
{ return x0 | ((uint64_t)x1 << 16) | ((uint64_t)y0 << 32) | ((uint64_t)y1 << 48); }
static uint64_t r_test(int ate, int atst, uint32_t aref, int afail, int date, int datm,
                       int zte, int ztst)
{
    return (uint64_t)ate | ((uint64_t)atst << 1) | ((uint64_t)aref << 4) | ((uint64_t)afail << 12) |
           ((uint64_t)date << 14) | ((uint64_t)datm << 15) | ((uint64_t)zte << 16) |
           ((uint64_t)ztst << 17);
}
static uint64_t r_alpha(int a, int b, int c, int dd, uint32_t fix)
{ return (uint64_t)a | ((uint64_t)b << 2) | ((uint64_t)c << 4) | ((uint64_t)dd << 6) | ((uint64_t)fix << 32); }
static uint64_t r_tex0(uint32_t tbp, uint32_t tbw, uint32_t psm, uint32_t tw, uint32_t th,
                       int tcc, int tfx, uint32_t cbp, uint32_t cpsm, int csm, uint32_t csa,
                       int cld)
{
    return tbp | ((uint64_t)tbw << 14) | ((uint64_t)psm << 20) | ((uint64_t)tw << 26) |
           ((uint64_t)th << 30) | ((uint64_t)tcc << 34) | ((uint64_t)tfx << 35) |
           ((uint64_t)cbp << 37) | ((uint64_t)cpsm << 51) | ((uint64_t)csm << 55) |
           ((uint64_t)csa << 56) | ((uint64_t)cld << 61);
}
static uint64_t r_clamp(int wms, int wmt, uint32_t minu, uint32_t maxu, uint32_t minv, uint32_t maxv)
{
    return (uint64_t)wms | ((uint64_t)wmt << 2) | ((uint64_t)minu << 4) | ((uint64_t)maxu << 14) |
           ((uint64_t)minv << 24) | ((uint64_t)maxv << 34);
}
static uint64_t r_tex1(int lcm, int mxl, int mmag, int mmin, int l, int k16)
{
    return (uint64_t)lcm | ((uint64_t)mxl << 2) | ((uint64_t)mmag << 5) | ((uint64_t)mmin << 6) |
           ((uint64_t)l << 19) | ((uint64_t)(k16 & 0xFFF) << 32);
}
static uint64_t r_rgbaq(uint32_t rgba, float q)
{
    uint32_t qu;
    memcpy(&qu, &q, 4);
    return (uint64_t)rgba | ((uint64_t)qu << 32);
}
static uint64_t r_xyz(int x16, int y16, uint32_t z)
{ return (uint64_t)(x16 & 0xFFFF) | ((uint64_t)(y16 & 0xFFFF) << 16) | ((uint64_t)z << 32); }
static uint64_t r_xyzf(int x16, int y16, uint32_t z, uint32_t f)
{ return (uint64_t)(x16 & 0xFFFF) | ((uint64_t)(y16 & 0xFFFF) << 16) | ((uint64_t)(z & 0xFFFFFF) << 32) | ((uint64_t)f << 56); }
static uint64_t r_st(float s, float t)
{
    uint32_t a, b;
    memcpy(&a, &s, 4);
    memcpy(&b, &t, 4);
    return a | ((uint64_t)b << 32);
}
static uint64_t r_uv(int u16, int v16) { return (uint64_t)(u16 & 0x3FFF) | ((uint64_t)(v16 & 0x3FFF) << 16); }

static uint32_t g_rng = 0x12345678u;
static uint32_t rnd(void)
{
    g_rng ^= g_rng << 13;
    g_rng ^= g_rng >> 17;
    g_rng ^= g_rng << 5;
    return g_rng;
}

/* host->local upload of raw bytes into a rectangle (both states) */
static void upload(dual *d, uint32_t dbp, uint32_t dbw, uint32_t dpsm, uint32_t x, uint32_t y,
                   uint32_t w, uint32_t h, const uint8_t *data, uint32_t nbytes)
{
    flush(d);
    qw(4 | (1ull << 60), 0xE);
    qw(((uint64_t)dbp << 32) | ((uint64_t)dbw << 48) | ((uint64_t)dpsm << 56), GS_BITBLTBUF);
    qw(((uint64_t)x << 32) | ((uint64_t)y << 48), GS_TRXPOS);
    qw(w | ((uint64_t)h << 32), GS_TRXREG);
    qw(0, GS_TRXDIR);
    uint32_t nq = (nbytes + 15) / 16;
    uint32_t done = 0;
    while (done < nq) {
        uint32_t chunk = nq - done > 30000 ? 30000 : nq - done;
        qw((uint64_t)chunk | ((uint64_t)(done + chunk == nq) << 15) | (2ull << 58), 0);
        for (uint32_t i = 0; i < chunk; i++) {
            uint8_t b[16] = { 0 };
            for (uint32_t k = 0; k < 16 && (done + i) * 16 + k < nbytes; k++) b[k] = data[(done + i) * 16 + k];
            uint64_t lo, hi;
            memcpy(&lo, b, 8);
            memcpy(&hi, b + 8, 8);
            qw(lo, hi);
        }
        send(d);
        done += chunk;
    }
}

/* smooth CT32 texture (gradients + low noise): bilinear/mip weight steps of
 * 1/16 then move a pixel by a few units, not by the texel-to-texel noise */
static void upload_smooth(dual *d, uint32_t dbp, uint32_t dbw, uint32_t w, uint32_t h)
{
    uint8_t *b = (uint8_t *)malloc(w * h * 4);
    for (uint32_t y = 0; y < h; y++)
        for (uint32_t x = 0; x < w; x++) {
            uint8_t *p = b + (y * w + x) * 4;
            p[0] = (uint8_t)(x * 255 / w + (rnd() & 3));
            p[1] = (uint8_t)(y * 255 / h + (rnd() & 3));
            p[2] = (uint8_t)(((x + y) * 127) / (w + h) + 60 + (rnd() & 3));
            p[3] = (uint8_t)(0x40 + ((x ^ y) & 31));
        }
    upload(d, dbp, dbw, GS_PSMCT32, 0, 0, w, h, b, w * h * 4);
    free(b);
}

static void upload_random(dual *d, uint32_t dbp, uint32_t dbw, uint32_t dpsm, uint32_t w, uint32_t h)
{
    uint32_t bpp = (uint32_t)gs_psm_bpp((int)dpsm);
    uint32_t n = (w * h * bpp + 7) / 8;
    uint8_t *b = (uint8_t *)malloc(n);
    for (uint32_t i = 0; i < n; i++) b[i] = (uint8_t)rnd();
    upload(d, dbp, dbw, dpsm, 0, 0, w, h, b, n);
    free(b);
}

static void local_to_local(dual *d, uint32_t sbp, uint32_t sbw, uint32_t spsm, uint32_t sx,
                           uint32_t sy, uint32_t dbp, uint32_t dbw, uint32_t dpsm, uint32_t dx,
                           uint32_t dy, uint32_t w, uint32_t h)
{
    ad(d, GS_BITBLTBUF, sbp | ((uint64_t)sbw << 16) | ((uint64_t)spsm << 24) |
                            ((uint64_t)dbp << 32) | ((uint64_t)dbw << 48) | ((uint64_t)dpsm << 56));
    ad(d, GS_TRXPOS, sx | ((uint64_t)sy << 16) | ((uint64_t)dx << 32) | ((uint64_t)dy << 48));
    ad(d, GS_TRXREG, w | ((uint64_t)h << 32));
    ad(d, GS_TRXDIR, 2);
    flush(d);
}

static void download_cmp(dual *d, uint32_t sbp, uint32_t sbw, uint32_t spsm, uint32_t x,
                         uint32_t y, uint32_t w, uint32_t h, const char *where)
{
    ad(d, GS_BITBLTBUF, sbp | ((uint64_t)sbw << 16) | ((uint64_t)spsm << 24));
    ad(d, GS_TRXPOS, x | ((uint64_t)y << 16));
    ad(d, GS_TRXREG, w | ((uint64_t)h << 32));
    ad(d, GS_TRXDIR, 1);
    flush(d);
    uint32_t n = gs_fifo_pending(d->sw), n2 = gs_fifo_pending(d->hw);
    uint8_t *a = (uint8_t *)malloc(n + 16), *b = (uint8_t *)malloc(n2 + 16);
    gs_read_fifo(d->sw, a, n);
    gs_read_fifo(d->hw, b, n2);
    if (n != n2) g_cmp.fifo_bad++;
    cmp_fifo(a, b, n < n2 ? n : n2, where);
    free(a);
    free(b);
}

/* ------------------------------------------------------------- duals */
static void d_open(dual *d, gpu_renderer *r)
{
    d->sw = gs_create();
    d->hw = gs_create();
    d->r = r;
    gpu_attach(r, d->hw);
}
static void d_check(dual *d, const char *where)
{
    flush(d);
    gpu_sync(d->r);
    cmp_vram(d->sw, d->hw, d->r, where);
}
static void d_close(dual *d, const char *where)
{
    d_check(d, where);
    gpu_detach(d->r);
    gs_destroy(d->sw);
    gs_destroy(d->hw);
}
static void d_display(dual *d, int field, const char *where)
{
    flush(d);
    static uint32_t a[1024 * 1024], b[4096 * 4096];
    uint32_t w = 0, h = 0, w2 = 0, h2 = 0;
    gpu_sync(d->r);
    int rc = gs_read_display(d->sw, field, a, 1024 * 1024, &w, &h);
    int rc2 = gpu_read_display(d->r, field, b, 4096 * 4096, &w2, &h2);
    /* upscaled renderer: compare the sample the write-back uses (s/2, s/2) */
    uint32_t s = w ? w2 / w : 1;
    if (rc2 == 0 && s > 1 && w2 == w * s && h2 == h * s) {
        for (uint32_t y = 0; y < h; y++)
            for (uint32_t x = 0; x < w; x++) b[y * w + x] = b[(y * s + s / 2) * w2 + x * s + s / 2];
        w2 = w; h2 = h;
    }
    if (rc != rc2 || w != w2 || h != h2) {
        fprintf(stderr, "  [%s] display: sw rc %d %ux%u gpu rc %d %ux%u\n", where, rc, w, h, rc2, w2, h2);
        g_cmp.disp_bad++;
        return;
    }
    if (rc == 0) cmp_frame(a, b, w, h, where);
}

/* standard target: W x H at FBP 0, Z at page zbp */
static void target(dual *d, uint32_t fbw, uint32_t fpsm, uint32_t zbp, uint32_t zpsm, int w, int h)
{
    ad(d, GS_FRAME_1, r_frame(0, fbw, fpsm, 0));
    ad(d, GS_ZBUF_1, r_zbuf(zbp, zpsm, 0));
    ad(d, GS_SCISSOR_1, r_scissor(0, (uint32_t)w - 1, 0, (uint32_t)h - 1));
    ad(d, GS_XYOFFSET_1, 0);
    ad(d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    ad(d, GS_PRMODECONT, 1);
    ad(d, GS_COLCLAMP, 1);
    ad(d, GS_DTHE, 0);
    ad(d, GS_ALPHA_1, 0x44);
    ad(d, GS_TEXA, 0x80 | (0x80ull << 32));
}

static void sprite(dual *d, uint32_t prim, int x0, int y0, int x1, int y1, uint32_t rgba, uint32_t z)
{
    ad(d, GS_PRIM, GS_PRIM_SPRITE | prim);
    ad(d, GS_RGBAQ, r_rgbaq(rgba, 1.0f));
    ad(d, GS_XYZ2, r_xyz(x0 << 4, y0 << 4, z));
    ad(d, GS_XYZ2, r_xyz(x1 << 4, y1 << 4, z));
}

/* textured sprite with UV in 1/16 texels */
static void tsprite(dual *d, uint32_t prim, int x0, int y0, int x1, int y1, int u0, int v0,
                    int u1, int v1, uint32_t rgba)
{
    ad(d, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST | prim);
    ad(d, GS_RGBAQ, r_rgbaq(rgba, 1.0f));
    ad(d, GS_UV, r_uv(u0, v0));
    ad(d, GS_XYZ2, r_xyz(x0 << 4, y0 << 4, 0));
    ad(d, GS_UV, r_uv(u1, v1));
    ad(d, GS_XYZ2, r_xyz(x1 << 4, y1 << 4, 0));
}

static void vtx(dual *d, uint32_t rgba, int x16, int y16, uint32_t z)
{
    ad(d, GS_RGBAQ, r_rgbaq(rgba, 1.0f));
    ad(d, GS_XYZ2, r_xyz(x16, y16, z));
}

static uint32_t zmax_of(uint32_t zpsm)
{
    switch (zpsm) {
    case GS_PSMZ24: return 0xFFFFFF;
    case GS_PSMZ16: case GS_PSMZ16S: return 0xFFFF;
    default: return 0xFFFFFFFFu;
    }
}

/* ================================================================ scenes */

/* every frame format x every Z format: overlapping Gouraud triangles with
 * depth test, sprites, lines and points */
static void scene_formats(gpu_renderer *r)
{
    static const uint32_t F[4] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16, GS_PSMCT16S };
    static const uint32_t Z[4] = { GS_PSMZ32, GS_PSMZ24, GS_PSMZ16, GS_PSMZ16S };
    for (int fi = 0; fi < 4; fi++)
        for (int zi = 0; zi < 4; zi++) {
            dual d;
            d_open(&d, r);
            char where[64];
            snprintf(where, sizeof where, "formats f%02X z%02X", F[fi], Z[zi]);
            target(&d, 4, F[fi], 32, Z[zi], 256, 128);
            uint32_t zm = zmax_of(Z[zi]);
            if (zm > 0xFFFFFF) zm = 0xFFFFFF;   /* keep Z32 in the exact float range */
            sprite(&d, 0, 0, 0, 256, 128, 0x80402010u, 0);
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));   /* GEQUAL */
            /* sloped triangles in disjoint Z slabs: the depth test must not
             * hinge on interpolation rounding (that is what tol covers) */
            for (int i = 0; i < 24; i++) {
                uint32_t base = (uint32_t)(((uint64_t)zm * (uint64_t)((i * 7) % 24 + 1)) / 26);
                ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
                for (int k = 0; k < 3; k++)
                    vtx(&d, rnd() | 0x80000000u, (int)(rnd() % (300 * 16)),
                        (int)(rnd() % (160 * 16)), base + rnd() % (zm / 60));
            }
            for (int i = 0; i < 12; i++) {
                int x = (int)(rnd() % 220), y = (int)(rnd() % 100);
                uint32_t gap = (uint32_t)(((uint64_t)zm * (uint64_t)(rnd() % 24 + 1)) / 26) + zm / 52;
                sprite(&d, 0, x, y, x + 1 + (int)(rnd() % 40), y + 1 + (int)(rnd() % 30), rnd(), gap);
            }
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
            for (int i = 0; i < 16; i++) {
                ad(&d, GS_PRIM, (i & 1) ? GS_PRIM_LINE : (GS_PRIM_LINE | PRIM_IIP));
                vtx(&d, rnd(), (int)(rnd() % 4096), (int)(rnd() % 2048), 5);
                vtx(&d, rnd(), (int)(rnd() % 4096), (int)(rnd() % 2048), 5);
                ad(&d, GS_PRIM, GS_PRIM_POINT);
                vtx(&d, rnd(), (int)(rnd() % 4096), (int)(rnd() % 2048), 7);
            }
            d_close(&d, where);
        }
}

static const uint64_t PRESETS[12] = { 0x800000002Aull, 0x44, 0x48, 0x42, 0x8000000064ull,
                                      0x4A, 0x89, 0x46, 0x88, 0x8000000068ull,
                                      0x8000000062ull, 0x0 };

/* flat sprites over a random destination (incl. random dst alpha): the 12
 * census presets x COLCLAMP x PABE, all 81 A/B/C/D combinations, FBA, in
 * CT32 / CT24 / CT16.  Exact. */
static void scene_blend_flat(gpu_renderer *r)
{
    static const uint32_t F[3] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16 };
    for (int fi = 0; fi < 3; fi++) {
        dual d;
        d_open(&d, r);
        target(&d, 4, F[fi], 32, GS_PSMZ24, 256, 192);
        upload_random(&d, 0, 4, F[fi], 256, 192);
        static const uint32_t AS[4] = { 0x20, 0x40, 0x80, 0xC0 };
        for (int p = 0; p < 12; p++)
            for (int v = 0; v < 4; v++) {
                ad(&d, GS_ALPHA_1, PRESETS[p]);
                ad(&d, GS_COLCLAMP, (uint64_t)(v & 1));
                ad(&d, GS_PABE, (uint64_t)(v >> 1));
                for (int a = 0; a < 4; a++)
                    sprite(&d, PRIM_ABE, p * 20, v * 16 + a * 4, p * 20 + 18, v * 16 + a * 4 + 4,
                           (rnd() & 0xFFFFFF) | (AS[a] << 24), 0);
            }
        ad(&d, GS_COLCLAMP, 1);
        ad(&d, GS_PABE, 0);
        for (int c = 0; c < 81; c++) {
            ad(&d, GS_ALPHA_1, r_alpha(c % 3, (c / 3) % 3, (c / 9) % 3, (c / 27) % 3, 0x50));
            ad(&d, GS_FBA_1, (uint64_t)(c & 1));
            int x = (c % 16) * 16, y = 64 + (c / 16) * 12;
            sprite(&d, PRIM_ABE, x, y, x + 15, y + 11, rnd(), 0);
        }
        ad(&d, GS_FBA_1, 0);
        d_close(&d, F[fi] == GS_PSMCT32 ? "blend_flat ct32" : F[fi] == GS_PSMCT24 ? "blend_flat ct24" : "blend_flat ct16");
    }
}

/* Ordered blending (docs/GPU.md "Performance"): heaps of overlapping
 * primitives whose pixels read the destination (the 12 blend presets with
 * COLCLAMP/PABE/FBA, DATE/DATM, partial FBMSK, AFAIL FB_ONLY / RGB_ONLY /
 * ZB_ONLY, dithering, blended Gouraud strips and lines, textured sprites),
 * without Z and with Z written under ZTST ALWAYS (both drawn through the
 * ordered view), then with a Z test that can fail (snapshot batches), on a
 * random destination, for CT32, CT24 and CT16.  On a device with ordered
 * blending most primitives must share a batch. */
static void scene_ordered(gpu_renderer *r)
{
    static const uint32_t F[3] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16 };
    static const char *NM[3][4] = { { "ordered ct32 noz", "ordered ct32 zalways", "ordered ct32 ztest", "ordered ct32 zgreater" },
                                    { "ordered ct24 noz", "ordered ct24 zalways", "ordered ct24 ztest", "ordered ct24 zgreater" },
                                    { "ordered ct16 noz", "ordered ct16 zalways", "ordered ct16 ztest", "ordered ct16 zgreater" } };
    for (int fi = 0; fi < 3; fi++)
        for (int zm = 0; zm < 4; zm++) {
            dual d;
            d_open(&d, r);
            gpu_stats s0 = *gpu_get_stats(r);
            target(&d, 4, F[fi], 32, GS_PSMZ24, 256, 192);
            upload_random(&d, 0, 4, F[fi], 256, 192);
            upload_random(&d, 32 * 32, 4, GS_PSMZ24, 256, 192);
            /* a 64x64 CT32 texture at page 96 */
            upload_random(&d, 96 * 32, 1, GS_PSMCT32, 64, 64);
            ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, zm == 0));
            int zte = zm >= 2 ? zm : 1;          /* GEQUAL, GREATER or ALWAYS */
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, zte));
            /* 1. blend presets x COLCLAMP x PABE x FBA, 160 overlapping sprites */
            for (int i = 0; i < 160; i++) {
                if (i % 8 == 0) {
                    ad(&d, GS_ALPHA_1, PRESETS[(i / 8) % 12]);
                    ad(&d, GS_COLCLAMP, (uint64_t)((i / 16) & 1));
                    ad(&d, GS_PABE, (uint64_t)((i / 32) & 1));
                    ad(&d, GS_FBA_1, (uint64_t)((i / 64) & 1));
                }
                int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                sprite(&d, PRIM_ABE, x, y, x + 8 + (int)(rnd() % 48), y + 8 + (int)(rnd() % 48),
                       rnd(), rnd() & 0xFFFFFF);
            }
            ad(&d, GS_COLCLAMP, 1);
            ad(&d, GS_PABE, 0);
            ad(&d, GS_FBA_1, 0);
            ad(&d, GS_ALPHA_1, 0x44);
            /* 2. blended Gouraud strips and lines over each other */
            for (int i = 0; i < 12; i++) {
                int x = (int)(rnd() % 180), y = (int)(rnd() % 120);
                ad(&d, GS_PRIM, GS_PRIM_TRISTRIP | PRIM_IIP | PRIM_ABE);
                vtx(&d, rnd(), (x + 2) * 16 + 3, (y + 2) * 16, rnd() & 0xFFFFFF);
                vtx(&d, rnd(), (x + 70) * 16 + 5, (y + 9) * 16 + 7, rnd() & 0xFFFFFF);
                vtx(&d, rnd(), (x + 5) * 16, (y + 66) * 16 + 9, rnd() & 0xFFFFFF);
                vtx(&d, rnd(), (x + 72) * 16 + 11, (y + 70) * 16, rnd() & 0xFFFFFF);
                ad(&d, GS_PRIM, GS_PRIM_LINE | PRIM_IIP | PRIM_ABE);
                vtx(&d, rnd(), x * 16, y * 16 + 5, rnd() & 0xFFFFFF);
                vtx(&d, rnd(), (x + 75) * 16 + 9, (y + 40) * 16, rnd() & 0xFFFFFF);
            }
            /* 3. destination alpha test (DATM 0 and 1) on blended sprites */
            for (int m = 0; m < 2; m++) {
                ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 1, m, 1, zte));
                for (int i = 0; i < 20; i++) {
                    int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                    sprite(&d, PRIM_ABE, x, y, x + 40, y + 40, rnd(), rnd() & 0xFFFFFF);
                }
            }
            /* 4. partial FBMSK merged in the stored format, blended */
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, zte));
            ad(&d, GS_FRAME_1, r_frame(0, 4, F[fi], 0x0F0F00F0u));
            for (int i = 0; i < 20; i++) {
                int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                sprite(&d, PRIM_ABE, x, y, x + 40, y + 40, rnd(), rnd() & 0xFFFFFF);
            }
            ad(&d, GS_FRAME_1, r_frame(0, 4, F[fi], 0));
            /* 5. alpha test with FB_ONLY, ZB_ONLY, RGB_ONLY on blended sprites */
            for (int af = 1; af < 4; af++) {
                ad(&d, GS_TEST_1, r_test(1, 4 + (af & 1), 0x60, af, 0, 0, 1, zte));
                for (int i = 0; i < 20; i++) {
                    int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                    sprite(&d, PRIM_ABE, x, y, x + 40, y + 40, rnd(), rnd() & 0xFFFFFF);
                }
            }
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, zte));
            /* 6. dithering under blending */
            ad(&d, GS_DTHE, 1);
            ad(&d, GS_DIMX, 0x0617150427130524ull);
            for (int i = 0; i < 20; i++) {
                int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                sprite(&d, PRIM_ABE, x, y, x + 40, y + 40, rnd(), rnd() & 0xFFFFFF);
            }
            ad(&d, GS_DTHE, 0);
            /* 7. textured blended sprites (bilinear, modulate) */
            ad(&d, GS_TEX0_1, r_tex0(96 * 32, 1, GS_PSMCT32, 6, 6, 1, 0, 0, 0, 0, 0, 0));
            ad(&d, GS_TEX1_1, r_tex1(0, 0, 1, 1, 0, 0));
            ad(&d, GS_CLAMP_1, r_clamp(1, 1, 0, 0, 0, 0));
            for (int i = 0; i < 30; i++) {
                int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                tsprite(&d, PRIM_ABE, x, y, x + 48, y + 40, 8, 8, 60 * 16, 50 * 16, rnd());
            }
            if (zm >= 2) {
                /* 8. opaque Gouraud triangles and AFAIL ZB_ONLY / FB_ONLY two-pass
                 * primitives under the Z test (no destination read: with depth
                 * in ordered views the two passes are one draw) */
                ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, zte));
                for (int i = 0; i < 16; i++) {
                    int x = (int)(rnd() % 180), y = (int)(rnd() % 120);
                    ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
                    vtx(&d, rnd(), (x + 1) * 16 + 7, (y + 3) * 16, rnd() & 0xFFFFFF);
                    vtx(&d, rnd(), (x + 66) * 16 + 2, (y + 11) * 16 + 9, rnd() & 0xFFFFFF);
                    vtx(&d, rnd(), (x + 9) * 16 + 13, (y + 61) * 16 + 4, rnd() & 0xFFFFFF);
                }
                for (int af = 1; af < 3; af++) {
                    ad(&d, GS_TEST_1, r_test(1, 6, 0x50, af, 0, 0, 1, zte));
                    for (int i = 0; i < 20; i++) {
                        int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                        sprite(&d, 0, x, y, x + 36, y + 36, rnd(), rnd() & 0xFFFFFF);
                    }
                }
                /* the Z test against the drawn Z, then ordered again */
                ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
                for (int i = 0; i < 20; i++) {
                    int x = (int)(rnd() % 200), y = (int)(rnd() % 140);
                    sprite(&d, PRIM_ABE, x, y, x + 30, y + 30, rnd(), rnd() & 0xFFFFFF);
                }
            }
            flush(&d);
            gpu_flush(r);
            const gpu_stats *s1 = gpu_get_stats(r);
            uint64_t prims = s1->prims - s0.prims, batches = s1->batches - s0.batches;
            uint64_t ordered = s1->rov_batches - s0.rov_batches;
            printf("%s: %llu prims, %llu batches, %llu ordered\n", NM[fi][zm], (unsigned long long)prims,
                   (unsigned long long)batches, (unsigned long long)ordered);
            if (gpu_ordered_blend(r) && (zm < 2 || gpu_ordered_depth(r)) && (ordered == 0 || batches * 4 > prims)) {
                fprintf(stderr, "  [%s] ordered blending did not batch the overlapping primitives\n",
                        NM[fi][zm]);
                g_cmp.raw_bad++;
            }
            d_close(&d, NM[fi][zm]);
        }
}

/* Gouraud triangles with alpha gradients over a random destination */
static void scene_blend_gouraud(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 192);
    upload_random(&d, 0, 4, GS_PSMCT32, 256, 192);
    for (int p = 0; p < 12; p++) {
        ad(&d, GS_ALPHA_1, PRESETS[p]);
        int x = (p % 4) * 64, y = (p / 4) * 64;
        ad(&d, GS_PRIM, GS_PRIM_TRISTRIP | PRIM_IIP | PRIM_ABE);
        vtx(&d, 0x00FF8040u, (x + 2) * 16, (y + 2) * 16, 0);
        vtx(&d, 0x8040FF80u, (x + 62) * 16 + 5, (y + 3) * 16, 0);
        vtx(&d, 0xFF8080FFu, (x + 1) * 16, (y + 61) * 16 + 9, 0);
        vtx(&d, 0x40FFFFFFu, (x + 63) * 16, (y + 62) * 16, 0);
    }
    d_close(&d, "blend_gouraud");
}

/* texture formats, CLUT variants, TFX x TCC, wrap modes: point sampling on
 * sprites at texel centres.  Exact. */
static void scene_tex_point(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 256);
    sprite(&d, 0, 0, 0, 256, 256, 0x80000000u, 0);
    /* textures at page 64+ (block 2048+), CLUTs at page 120+ */
    const uint32_t T32 = 64 * 32, T24 = 66 * 32, T16 = 68 * 32, T8 = 70 * 32, T4 = 72 * 32,
                   T8H = 74 * 32;
    const uint32_t C32 = 120 * 32, C16 = 121 * 32, C4_32 = 122 * 32, C16ROW = 123 * 32;
    upload_random(&d, T32, 1, GS_PSMCT32, 64, 32);
    upload_random(&d, T24, 1, GS_PSMCT24, 64, 32);
    upload_random(&d, T16, 1, GS_PSMCT16, 64, 64);
    upload_random(&d, T8, 2, GS_PSMT8, 128, 64);
    upload_random(&d, T4, 2, GS_PSMT4, 128, 128);
    upload_random(&d, T8H, 1, GS_PSMCT32, 64, 32);
    upload_random(&d, C32, 1, GS_PSMCT32, 16, 16);
    upload_random(&d, C16, 1, GS_PSMCT16, 16, 16);
    upload_random(&d, C4_32, 1, GS_PSMCT32, 8, 2);
    upload_random(&d, C16ROW, 4, GS_PSMCT16, 256, 4);
    struct { uint64_t tex0; uint64_t texa; } T[] = {
        { r_tex0(T32, 1, GS_PSMCT32, 6, 5, 1, 1, 0, 0, 0, 0, 0), 0x80 | (0x80ull << 32) },
        { r_tex0(T24, 1, GS_PSMCT24, 6, 5, 1, 1, 0, 0, 0, 0, 0), 0x30 | (1ull << 15) | (0x90ull << 32) },
        { r_tex0(T16, 1, GS_PSMCT16, 6, 6, 1, 1, 0, 0, 0, 0, 0), 0x10 | (1ull << 15) | (0xF0ull << 32) },
        { r_tex0(T16, 1, GS_PSMCT16S, 6, 6, 1, 1, 0, 0, 0, 0, 0), 0x40 | (0x77ull << 32) },
        { r_tex0(T8, 2, GS_PSMT8, 7, 6, 1, 1, C32, GS_PSMCT32, 0, 0, 1), 0x80 | (0x80ull << 32) },
        { r_tex0(T8, 2, GS_PSMT8, 7, 6, 1, 1, C16, GS_PSMCT16, 0, 0, 1), 0x20 | (0xA0ull << 32) },
        { r_tex0(T4, 2, GS_PSMT4, 7, 7, 1, 1, C4_32, GS_PSMCT32, 0, 0, 1), 0x80 | (0x80ull << 32) },
        { r_tex0(T4, 2, GS_PSMT4, 7, 7, 1, 1, C16, GS_PSMCT16, 0, 5, 1), 0x30 | (0x60ull << 32) },
        { r_tex0(T4, 2, GS_PSMT4, 7, 7, 1, 1, C16ROW, GS_PSMCT16, 1, 3, 1), 0x30 | (0x60ull << 32) },
        { r_tex0(T8H, 1, GS_PSMT8H, 6, 5, 1, 1, C32, GS_PSMCT32, 0, 0, 1), 0x80 | (0x80ull << 32) },
        { r_tex0(T8H, 1, GS_PSMT4HL, 6, 5, 1, 1, C4_32, GS_PSMCT32, 0, 0, 1), 0x80 | (0x80ull << 32) },
        { r_tex0(T8H, 1, GS_PSMT4HH, 6, 5, 1, 1, C16, GS_PSMCT16, 0, 2, 1), 0x80 | (0x80ull << 32) },
    };
    ad(&d, GS_TEXCLUT, 4 | (2ull << 6) | (1ull << 12));   /* CSM2: CBW 4, COU 2, COV 1 */
    int n = (int)(sizeof T / sizeof T[0]);
    for (int i = 0; i < n; i++) {
        ad(&d, GS_TEXA, T[i].texa);
        ad(&d, GS_TEX1_1, 0);
        ad(&d, GS_CLAMP_1, r_clamp(0, 0, 0, 0, 0, 0));
        for (int f = 0; f < 4; f++) {
            /* TFX f, TCC alternating, a modulating vertex colour */
            uint64_t t0 = (T[i].tex0 & ~(3ull << 35) & ~(1ull << 34)) | ((uint64_t)f << 35) |
                          ((uint64_t)(f & 1) << 34);
            ad(&d, GS_TEX0_1, t0);
            int x = (i % 4) * 64 + (f & 1) * 32, y = (i / 4) * 64 + (f >> 1) * 32;
            tsprite(&d, 0, x, y, x + 31, y + 31, 8 + 16 * 3, 8 + 16 * 2, 8 + 16 * 34, 8 + 16 * 33,
                    0x50A0C060u);
        }
    }
    /* wrap modes: UV beyond the texture */
    ad(&d, GS_TEX0_1, r_tex0(T32, 1, GS_PSMCT32, 4, 4, 1, 1, 0, 0, 0, 0, 0));
    static const uint64_t CL[4] = { 0, 0, 0, 0 };
    (void)CL;
    uint64_t clamps[4] = { r_clamp(0, 0, 0, 0, 0, 0), r_clamp(1, 1, 0, 0, 0, 0),
                           r_clamp(2, 2, 3, 9, 2, 12), r_clamp(3, 3, 7, 4, 3, 8) };
    for (int m = 0; m < 4; m++) {
        ad(&d, GS_CLAMP_1, clamps[m]);
        tsprite(&d, 0, m * 64, 192, m * 64 + 60, 252, 8 - 16 * 20, 8 - 16 * 13, 8 + 16 * 40,
                8 + 16 * 47, 0x80808080u);
    }
    d_close(&d, "tex_point");
}

/* bilinear, mipmaps (MIPTBP, MMIN 0-5, L/K), STQ perspective triangles */
static void scene_tex_filter(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 256);
    sprite(&d, 0, 0, 0, 256, 256, 0x80000000u, 0);
    const uint32_t L0 = 64 * 32, L1 = 72 * 32, L2 = 76 * 32, L3 = 78 * 32;
    upload_smooth(&d, L0, 2, 128, 128);
    upload_smooth(&d, L1, 1, 64, 64);
    upload_smooth(&d, L2, 1, 32, 32);
    upload_smooth(&d, L3, 1, 16, 16);
    ad(&d, GS_TEX0_1, r_tex0(L0, 2, GS_PSMCT32, 7, 7, 1, 0, 0, 0, 0, 0, 0));
    ad(&d, GS_MIPTBP1_1, (uint64_t)L1 | (1ull << 14) | ((uint64_t)L2 << 20) | (1ull << 34) |
                             ((uint64_t)L3 << 40) | (1ull << 54));
    ad(&d, GS_CLAMP_1, r_clamp(0, 0, 0, 0, 0, 0));
    /* bilinear sprites (MMAG linear), off-centre UVs */
    ad(&d, GS_TEX1_1, r_tex1(0, 0, 1, 1, 0, 0));
    tsprite(&d, 0, 0, 0, 64, 64, 3, 5, 16 * 50 + 7, 16 * 40 + 1, 0x80808080u);
    tsprite(&d, 0, 64, 0, 128, 64, 16 * 100, 16 * 100, 16 * 140 + 9, 16 * 160 + 3, 0x80808080u);
    /* clamp + bilinear at the edge */
    ad(&d, GS_CLAMP_1, r_clamp(1, 1, 0, 0, 0, 0));
    tsprite(&d, 0, 128, 0, 192, 64, 16 * 120, 16 * 120, 16 * 136, 16 * 136, 0x80808080u);
    ad(&d, GS_CLAMP_1, r_clamp(0, 0, 0, 0, 0, 0));
    /* mip filters: LCM=1 with fixed K selects the level */
    for (int mm = 0; mm < 6; mm++)
        for (int k = 0; k < 2; k++) {
            ad(&d, GS_TEX1_1, r_tex1(1, 3, 1, mm, 0, k ? 0x18 : 0x0C));   /* K = 1.5 / 0.75 */
            int x = mm * 40, y = 64 + k * 40;
            tsprite(&d, 0, x, y, x + 38, y + 38, 16 * 5 + 3, 16 * 7 + 1, 16 * 90, 16 * 70, 0x80808080u);
        }
    /* STQ perspective triangles with LOD from Q (LCM=0, L=0, K=0) */
    ad(&d, GS_TEX1_1, r_tex1(0, 3, 1, 5, 0, 0));
    for (int i = 0; i < 6; i++) {
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_IIP);
        for (int k = 0; k < 3; k++) {
            float q = 0.2f + (float)(rnd() % 1000) / 600.0f;
            float s = (float)(rnd() % 1000) / 500.0f * q, t = (float)(rnd() % 1000) / 500.0f * q;
            ad(&d, GS_ST, r_st(s, t));
            ad(&d, GS_RGBAQ, r_rgbaq(rnd() | 0x80000000u, q));
            ad(&d, GS_XYZ2, r_xyz((int)(rnd() % (256 * 16)), 16 * 150 + (int)(rnd() % (100 * 16)), 0));
        }
    }
    d_close(&d, "tex_filter");
}

/* alpha test x AFAIL, DATE/DATM, FBMSK (partial bits and channels), ZMSK,
 * SCANMSK, dither (CT16), flat fog, XYOFFSET, context 2, PRMODE.  Exact. */
static void scene_pixel_ops(gpu_renderer *r)
{
    for (int f16 = 0; f16 < 2; f16++) {
        dual d;
        d_open(&d, r);
        uint32_t fpsm = f16 ? GS_PSMCT16 : GS_PSMCT32;
        target(&d, 4, fpsm, 32, GS_PSMZ24, 256, 256);
        upload_random(&d, 0, 4, fpsm, 256, 256);
        upload_random(&d, 32 * 32, 4, GS_PSMZ24, 256, 256);
        /* ATST x AFAIL with a depth test, sprites with increasing alpha */
        for (int atst = 0; atst < 8; atst++)
            for (int af = 0; af < 4; af++) {
                ad(&d, GS_TEST_1, r_test(1, atst, 0x60, af, 0, 0, 1, 2));
                for (int a = 0; a < 4; a++) {
                    int x = atst * 32 + a * 8, y = af * 8;
                    sprite(&d, 0, x, y, x + 8, y + 8, (rnd() & 0xFFFFFF) | ((0x40u + 0x20u * (uint32_t)a) << 24),
                           rnd() & 0xFFFFFF);
                }
            }
        /* DATE / DATM */
        for (int m = 0; m < 2; m++) {
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 1, m, 1, 1));
            sprite(&d, 0, m * 128, 32, m * 128 + 120, 48, rnd(), 0);
        }
        /* FBMSK: partial bits, whole channels */
        static const uint32_t M[4] = { 0x0F0F00F0u, 0xFF000000u, 0x00FF00FFu, 0x80000007u };
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        for (int i = 0; i < 4; i++) {
            ad(&d, GS_FRAME_1, r_frame(0, 4, fpsm, M[i]));
            ad(&d, GS_ALPHA_1, PRESETS[1 + i]);
            sprite(&d, i & 1 ? PRIM_ABE : 0, i * 64, 48, i * 64 + 60, 64, rnd(), 0);
        }
        ad(&d, GS_FRAME_1, r_frame(0, 4, fpsm, 0));
        /* ZMSK on, then a Z-only draw (FBMSK all) */
        ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 1));
        sprite(&d, 0, 0, 64, 128, 80, rnd(), 0x123456);
        ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 0));
        ad(&d, GS_FRAME_1, r_frame(0, 4, fpsm, 0xFFFFFFFFu));
        sprite(&d, 0, 128, 64, 256, 80, rnd(), 0x654321);
        ad(&d, GS_FRAME_1, r_frame(0, 4, fpsm, 0));
        /* SCANMSK 2/3 */
        for (int s = 2; s < 4; s++) {
            ad(&d, GS_SCANMSK, (uint64_t)s);
            sprite(&d, 0, (s - 2) * 128, 80, (s - 2) * 128 + 128, 96, rnd(), 0);
        }
        ad(&d, GS_SCANMSK, 0);
        /* dither + blending (DIMX = the libgraph default matrix) */
        ad(&d, GS_DTHE, 1);
        ad(&d, GS_DIMX, 0x0617150427130524ull);
        ad(&d, GS_ALPHA_1, 0x44);
        sprite(&d, PRIM_ABE, 0, 96, 256, 112, 0x60C08040u, 0);
        sprite(&d, 0, 0, 112, 256, 120, 0x80336699u, 0);
        ad(&d, GS_DTHE, 0);
        /* fog (flat, from the sprite's 2nd vertex) */
        ad(&d, GS_FOGCOL, 0x2080C0);
        ad(&d, GS_PRIM, GS_PRIM_SPRITE | PRIM_FGE);
        ad(&d, GS_RGBAQ, r_rgbaq(0x80F0A050u, 1.0f));
        ad(&d, GS_XYZF2, r_xyzf(0, 120 << 4, 0, 0x30));
        ad(&d, GS_XYZF2, r_xyzf(256 << 4, 136 << 4, 0, 0xA0));
        /* context 2 with XYOFFSET, PRMODECONT=0 + PRMODE */
        ad(&d, GS_FRAME_2, r_frame(0, 4, fpsm, 0));
        ad(&d, GS_ZBUF_2, r_zbuf(32, GS_PSMZ24, 1));
        ad(&d, GS_SCISSOR_2, r_scissor(16, 200, 130, 180));
        ad(&d, GS_XYOFFSET_2, (uint64_t)(100 * 16) | ((uint64_t)(50 * 16) << 32));
        ad(&d, GS_TEST_2, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        ad(&d, GS_ALPHA_2, 0x48);
        sprite(&d, PRIM_CTXT2 | PRIM_ABE, 100, 170, 400, 260, 0x40FF2020u, 0);
        ad(&d, GS_PRMODECONT, 0);
        ad(&d, GS_PRMODE, PRIM_CTXT2);
        sprite(&d, 0, 110, 230, 150, 250, 0x8020FF20u, 0);
        ad(&d, GS_PRMODECONT, 1);
        d_close(&d, f16 ? "pixel_ops ct16" : "pixel_ops ct32");
    }
}

/* lines in all octants, line strips, points, fans, strips, interpolated fog */
static void scene_prims(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 256);
    sprite(&d, 0, 0, 0, 256, 256, 0x80101010u, 0);
    for (int i = 0; i < 64; i++) {
        double a = i * 6.2831853 / 64.0;
        int cx = 64 * 16 + 8 * (i & 1), cy = 64 * 16 + 5 * (i & 2);
        ad(&d, GS_PRIM, GS_PRIM_LINE | ((i & 4) ? PRIM_IIP : 0));
        vtx(&d, 0x80FFFFFFu, cx, cy, 0);
        vtx(&d, rnd() | 0x80000000u, cx + (int)(cos(a) * 60 * 16), cy + (int)(sin(a) * 60 * 16), 0);
    }
    ad(&d, GS_PRIM, GS_PRIM_LINESTRIP | PRIM_IIP);
    for (int i = 0; i < 20; i++)
        vtx(&d, rnd() | 0x80000000u, 130 * 16 + (int)(rnd() % (120 * 16)), (int)(rnd() % (120 * 16)), 0);
    ad(&d, GS_PRIM, GS_PRIM_POINT);
    for (int i = 0; i < 50; i++)
        vtx(&d, rnd(), (int)(rnd() % (256 * 16)), (int)(rnd() % (256 * 16)), 0);
    ad(&d, GS_PRIM, GS_PRIM_TRIFAN | PRIM_IIP);
    vtx(&d, 0x80FFFFFFu, 64 * 16, 190 * 16, 0);
    for (int i = 0; i <= 12; i++) {
        double a = i * 6.2831853 / 12.0;
        vtx(&d, rnd() | 0x80000000u, 64 * 16 + (int)(cos(a) * 50 * 16), 190 * 16 + (int)(sin(a) * 50 * 16), 0);
    }
    ad(&d, GS_FOGCOL, 0x10E0F0);
    ad(&d, GS_PRIM, GS_PRIM_TRISTRIP | PRIM_IIP | PRIM_FGE);
    for (int i = 0; i < 10; i++) {
        ad(&d, GS_RGBAQ, r_rgbaq(rnd() | 0x80000000u, 1.0f));
        ad(&d, GS_XYZF2, r_xyzf(140 * 16 + (i >> 1) * 22 * 16 + 3, (150 + (i & 1) * 90) * 16 + 7, 0,
                                rnd() & 255));
    }
    d_close(&d, "prims");
}

/* coherence: readback after drawing, local->local from a target into a
 * texture, an upload over a target, render-to-texture, CLUT from a target */
static void scene_coherence(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
    sprite(&d, 0, 0, 0, 256, 128, 0x80204060u, 0);
    for (int i = 0; i < 20; i++) {
        int x = (int)(rnd() % 230), y = (int)(rnd() % 100);
        sprite(&d, 0, x, y, x + 20, y + 20, rnd(), 0);
    }
    /* 1. local->host straight after drawing (sceGsExecStoreImage) */
    download_cmp(&d, 0, 4, GS_PSMCT32, 10, 7, 100, 50, "coherence readback ct32");
    download_cmp(&d, 0, 4, GS_PSMCT16, 0, 0, 64, 64, "coherence readback as ct16");
    /* 2. local->local from the target into texture memory, then sample it */
    local_to_local(&d, 0, 4, GS_PSMCT32, 0, 0, 64 * 32, 1, GS_PSMCT32, 0, 0, 64, 32);
    ad(&d, GS_TEX0_1, r_tex0(64 * 32, 1, GS_PSMCT32, 6, 5, 1, 1, 0, 0, 0, 0, 0));
    ad(&d, GS_TEX1_1, 0);
    ad(&d, GS_CLAMP_1, 0);
    tsprite(&d, 0, 128, 64, 192, 96, 8, 8, 8 + 64 * 16, 8 + 32 * 16, 0x80808080u);
    /* 3. upload over part of the target, then blend on top of it */
    upload_random(&d, 0, 4, GS_PSMCT32, 64, 32);
    ad(&d, GS_ALPHA_1, 0x44);
    sprite(&d, PRIM_ABE, 16, 8, 80, 40, 0x40FFFFFFu, 0);
    /* 4. render to an offscreen CT32 target (page 80), then texture from it */
    ad(&d, GS_FRAME_2, r_frame(80, 1, GS_PSMCT32, 0));
    ad(&d, GS_ZBUF_2, r_zbuf(32, GS_PSMZ24, 1));
    ad(&d, GS_SCISSOR_2, r_scissor(0, 63, 0, 31));
    ad(&d, GS_XYOFFSET_2, 0);
    ad(&d, GS_TEST_2, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP | PRIM_CTXT2);
    vtx(&d, 0x80FF0000u, 0, 0, 0); vtx(&d, 0x8000FF00u, 64 * 16, 0, 0); vtx(&d, 0x800000FFu, 0, 32 * 16, 0);
    ad(&d, GS_TEX0_1, r_tex0(80 * 32, 1, GS_PSMCT32, 6, 5, 1, 1, 0, 0, 0, 0, 0));
    tsprite(&d, 0, 192, 64, 256, 96, 8, 8, 8 + 64 * 16, 8 + 32 * 16, 0x80808080u);
    /* 5. a CLUT drawn by the GPU (16x16 CT32 at page 84), then a T8 texture using it */
    ad(&d, GS_FRAME_2, r_frame(84, 1, GS_PSMCT32, 0));
    ad(&d, GS_SCISSOR_2, r_scissor(0, 15, 0, 15));
    ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP | PRIM_CTXT2);
    vtx(&d, 0x80FFFF00u, 0, 0, 0); vtx(&d, 0x8000FFFFu, 16 * 16, 0, 0); vtx(&d, 0x80FF00FFu, 0, 16 * 16, 0);
    upload_random(&d, 88 * 32, 2, GS_PSMT8, 128, 64);
    ad(&d, GS_TEX0_1, r_tex0(88 * 32, 2, GS_PSMT8, 7, 6, 1, 1, 84 * 32, GS_PSMCT32, 0, 0, 1));
    tsprite(&d, 0, 0, 96, 128, 128, 8, 8, 8 + 128 * 16, 8 + 64 * 16, 0x80808080u);
    /* 6. the frame drawn as CT32, sampled as CT16 + readback of the Z buffer */
    ad(&d, GS_TEX0_1, r_tex0(0, 4, GS_PSMCT16, 7, 6, 1, 1, 0, 0, 0, 0, 0));
    ad(&d, GS_TEXA, 0x80 | (0x40ull << 32));
    ad(&d, GS_FRAME_2, r_frame(90, 1, GS_PSMCT32, 0));
    ad(&d, GS_SCISSOR_2, r_scissor(0, 63, 0, 31));
    ad(&d, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST | PRIM_CTXT2);
    ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, 1.0f));
    ad(&d, GS_UV, r_uv(8, 8)); ad(&d, GS_XYZ2, r_xyz(0, 0, 0));
    ad(&d, GS_UV, r_uv(8 + 64 * 16, 8 + 32 * 16)); ad(&d, GS_XYZ2, r_xyz(64 * 16, 32 * 16, 0));
    ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
    sprite(&d, 0, 100, 0, 200, 40, 0x80123456u, 0x345678);
    download_cmp(&d, 32 * 32, 4, GS_PSMZ24, 90, 0, 120, 50, "coherence readback z24");
    d_close(&d, "coherence");
}

/* the PCRTC: demo setup (interlaced FRAME), the game's 0x7F23 two-circuit
 * anti-flicker merge, FIELD mode both fields, a CT16 display buffer */
static void scene_display(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 10, GS_PSMCT32, 70 * 2, GS_PSMZ24, 640, 448);
    upload_random(&d, 0, 10, GS_PSMCT32, 640, 448);
    for (int i = 0; i < 40; i++) {
        int x = (int)(rnd() % 600), y = (int)(rnd() % 400);
        sprite(&d, PRIM_ABE, x, y, x + 40, y + 40, rnd(), 0);
    }
    flush(&d);
    gs_write_priv(d.sw, GS_P_SMODE2, 3); gs_write_priv(d.hw, GS_P_SMODE2, 3);
    uint64_t dispfb = 0 | (10ull << 9) | ((uint64_t)GS_PSMCT32 << 15);
    uint64_t display = 636 | (50ull << 12) | (3ull << 23) | (2559ull << 32) | (895ull << 44);
    gs_write_priv(d.sw, GS_P_DISPFB1, dispfb); gs_write_priv(d.hw, GS_P_DISPFB1, dispfb);
    gs_write_priv(d.sw, GS_P_DISPLAY1, display); gs_write_priv(d.hw, GS_P_DISPLAY1, display);
    gs_write_priv(d.sw, GS_P_BGCOLOR, 0x102030); gs_write_priv(d.hw, GS_P_BGCOLOR, 0x102030);
    uint64_t pmode = 1 | (1u << 2) | (1u << 5) | (0xFFu << 8);
    gs_write_priv(d.sw, GS_P_PMODE, pmode); gs_write_priv(d.hw, GS_P_PMODE, pmode);
    d_display(&d, GS_READ_FRAME, "display demo");
    /* 0x7F23: circuit 1 at DBY=1 / DH-1, circuit 2 at DBY=0, ALP 0x7F */
    uint64_t fb1 = dispfb | (1ull << 43);
    uint64_t dp1 = 636 | (50ull << 12) | (3ull << 23) | (2559ull << 32) | (893ull << 44);
    gs_write_priv(d.sw, GS_P_DISPFB1, fb1); gs_write_priv(d.hw, GS_P_DISPFB1, fb1);
    gs_write_priv(d.sw, GS_P_DISPLAY1, dp1); gs_write_priv(d.hw, GS_P_DISPLAY1, dp1);
    gs_write_priv(d.sw, GS_P_DISPFB2, dispfb); gs_write_priv(d.hw, GS_P_DISPFB2, dispfb);
    gs_write_priv(d.sw, GS_P_DISPLAY2, display); gs_write_priv(d.hw, GS_P_DISPLAY2, display);
    gs_write_priv(d.sw, GS_P_PMODE, 0x7F23); gs_write_priv(d.hw, GS_P_PMODE, 0x7F23);
    d_display(&d, GS_READ_FRAME, "display 7F23");
    /* MMOD=0 (circuit-1 alpha) with a background colour */
    gs_write_priv(d.sw, GS_P_PMODE, 0x83); gs_write_priv(d.hw, GS_P_PMODE, 0x83);
    d_display(&d, GS_READ_FRAME, "display mmod0");
    /* FIELD mode, both fields */
    gs_write_priv(d.sw, GS_P_SMODE2, 1); gs_write_priv(d.hw, GS_P_SMODE2, 1);
    uint64_t dpf = 636 | (25ull << 12) | (3ull << 23) | (2559ull << 32) | (447ull << 44);
    gs_write_priv(d.sw, GS_P_DISPLAY1, dpf); gs_write_priv(d.hw, GS_P_DISPLAY1, dpf);
    gs_write_priv(d.sw, GS_P_DISPFB1, dispfb); gs_write_priv(d.hw, GS_P_DISPFB1, dispfb);
    gs_write_priv(d.sw, GS_P_PMODE, pmode); gs_write_priv(d.hw, GS_P_PMODE, pmode);
    d_display(&d, 0, "display field0");
    d_display(&d, 1, "display field1");
    /* a CT16 display buffer at page 300 that no target covers (mirror path) */
    upload_random(&d, 300 * 32, 10, GS_PSMCT16, 640, 224);
    uint64_t fb16 = 300 | (10ull << 9) | ((uint64_t)GS_PSMCT16 << 15);
    gs_write_priv(d.sw, GS_P_DISPFB1, fb16); gs_write_priv(d.hw, GS_P_DISPFB1, fb16);
    gs_write_priv(d.sw, GS_P_DISPLAY1, dpf); gs_write_priv(d.hw, GS_P_DISPLAY1, dpf);
    d_display(&d, 0, "display ct16");
    d_close(&d, "display");
}

/* a full 640x448 frame like rg-host-demo, Gouraud + blended sprites */
static void scene_frame640(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 10, GS_PSMCT32, 140, GS_PSMZ32, 640, 448);
    sprite(&d, 0, 0, 0, 640, 448, 0x80281210u, 0);
    ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
    vtx(&d, 0x802828FFu, 490 * 16, 200 * 16, 0);
    vtx(&d, 0x8028FF28u, 235 * 16, 330 * 16, 0);
    vtx(&d, 0x80FF5028u, 235 * 16, 70 * 16, 0);
    for (int i = 0; i < 30; i++) {
        int x = (int)(rnd() % 580), y = (int)(rnd() % 380);
        sprite(&d, PRIM_ABE, x, y, x + 64, y + 64, 0x4000AAFFu, 0);
    }
    d_close(&d, "frame640");
}

/* debug: which texel does each pixel of a 640-wide UV sprite pick? */
static void scene_debug_uv(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 10, GS_PSMCT32, 140, GS_PSMZ24, 640, 64);
    uint8_t *b = (uint8_t *)malloc(1024 * 4);
    for (int x = 0; x < 1024; x++) { b[4*x] = (uint8_t)x; b[4*x+1] = (uint8_t)(x >> 8); b[4*x+2] = 0; b[4*x+3] = 0x80; }
    upload(&d, 300 * 32, 16, GS_PSMCT32, 0, 0, 1024, 1, b, 4096);
    free(b);
    ad(&d, GS_TEX0_1, r_tex0(300 * 32, 16, GS_PSMCT32, 10, 0, 1, 1, 0, 0, 0, 0, 0));
    ad(&d, GS_CLAMP_1, 0);
    ad(&d, GS_TEX1_1, 0);
    tsprite(&d, 0, 0, 0, 640, 8, 0, 0, 640 * 16, 16, 0x80808080u);
    tsprite(&d, 0, 0, 8, 640, 16, 8, 0, 640 * 16 + 8, 16, 0x80808080u);
    ad(&d, GS_TEX1_1, 0x60);
    tsprite(&d, 0, 0, 16, 640, 24, 8, 0, 640 * 16 + 8, 16, 0x80808080u);
    d_close(&d, "debug_uv");
}

/* debug: single lines, report the first that differs */
static void scene_debug_lines(gpu_renderer *r)
{
    for (int i = 0; i < 300; i++) {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
        int x0 = (int)(rnd() % 2048), y0 = (int)(rnd() % 1024), x1 = (int)(rnd() % 2048), y1 = (int)(rnd() % 1024);
        ad(&d, GS_PRIM, GS_PRIM_LINE);
        vtx(&d, 0x80FFFFFFu, x0, y0, 0);
        vtx(&d, 0x80FFFFFFu, x1, y1, 0);
        uint64_t before = g_cmp.px_bad;
        d_close(&d, "debug_lines");
        if (g_cmp.px_bad != before) fprintf(stderr, "line %d: (%d,%d)-(%d,%d) [12.4]\n", i, x0, y0, x1, y1);
    }
}

/* debug: single random flat triangles, report the first that differs */
/* Triangles reaching far outside the target, and Gouraud slivers (WARP:
 * docs/GPU.md "Real game validation").  The NORMAL overlay's story screen
 * draws rotated full-screen quads as blended triangle strips from about
 * (-124,-168); a rasterizer that clips them into fans leaves pixels on the
 * fans' inner edges drawn twice or not at all (WARP did, at 2 pixels of the
 * real frame), so coverage is decided by the shader on the bounding box.
 * The sliver is scene.formats' triangle where WARP's itod of a dtoi result
 * made floor_d round 100.92 up.  Exact (tol 0). */
static void scene_offscreen(gpu_renderer *r)
{
    static const uint32_t F[2] = { GS_PSMCT32, GS_PSMCT24 };
    for (int fi = 0; fi < 2; fi++) {
        dual d;
        d_open(&d, r);
        target(&d, 4, F[fi], 32, GS_PSMZ16, 256, 224);
        upload_random(&d, 0, 4, F[fi], 256, 224);
        /* the game's quad: XYOFFSET (0x7000, 0x7200), blended strip */
        ad(&d, GS_XYOFFSET_1, 0x7000ull | (0x7200ull << 32));
        ad(&d, GS_ALPHA_1, 0x44);
        ad(&d, GS_PRIM, GS_PRIM_TRISTRIP | PRIM_ABE);
        vtx(&d, 0x405D5D5Du, 0x6840, 0x67C1, 0);
        vtx(&d, 0x405D5D5Du, 0x803F, 0x6801, 0);
        vtx(&d, 0x405D5D5Du, 0x6801, 0x7FC0, 0);
        vtx(&d, 0x405D5D5Du, 0x8000, 0x8000, 0);
        /* rotated quads 600..3000 px wide around the target, blended, so a
         * pixel drawn twice or missed changes the result */
        ad(&d, GS_XYOFFSET_1, (1024ull << 4) | ((1024ull << 4) << 32));
        for (int i = 0; i < 24; i++) {
            double cx = 1024 + (double)(rnd() % 256), cy = 1024 + (double)(rnd() % 224);
            double h = 300.0 + (double)(rnd() % 1200), ang = (double)(rnd() % 6283) / 1000.0;
            double c = cos(ang) * h, sn = sin(ang) * h;
            double px[4] = { cx - c + sn, cx + c + sn, cx - c - sn, cx + c - sn };
            double py[4] = { cy - sn - c, cy + sn - c, cy - sn + c, cy + sn + c };
            ad(&d, GS_PRIM, GS_PRIM_TRISTRIP | PRIM_ABE | ((i & 1) ? PRIM_IIP : 0));
            for (int k = 0; k < 4; k++) {
                int x16 = (int)(px[k] * 16.0), y16 = (int)(py[k] * 16.0);
                if (x16 < 0) x16 = 0;
                if (y16 < 0) y16 = 0;
                if (x16 > 0xFFFF) x16 = 0xFFFF;
                if (y16 > 0xFFFF) y16 = 0xFFFF;
                vtx(&d, (rnd() & 0x00FFFFFFu) | 0x30000000u, x16, y16, 0);
            }
        }
        ad(&d, GS_XYOFFSET_1, 0);
        /* the Gouraud sliver */
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
        vtx(&d, 2540877309u, 1459, 559, 0);
        vtx(&d, 2922821501u, 2612, 521, 0);
        vtx(&d, 4135188805u, 4749, 476, 0);
        d_close(&d, F[fi] == GS_PSMCT32 ? "offscreen ct32" : "offscreen ct24");
    }
}

static void scene_debug_tris(gpu_renderer *r)
{
    for (int i = 0; i < 300; i++) {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
        int X[3], Y[3];
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE);
        for (int k = 0; k < 3; k++) {
            X[k] = (int)(rnd() % (300 * 16)); Y[k] = (int)(rnd() % (160 * 16));
            vtx(&d, 0x80FFFFFFu, X[k], Y[k], 0);
        }
        uint64_t before = g_cmp.px_bad;
        if (getenv("RG_DEBUG_ONE") && atoi(getenv("RG_DEBUG_ONE")) != i) { g_n = 0; g_tag = 0xFFFFFFFFu; gpu_detach(d.r); gs_destroy(d.sw); gs_destroy(d.hw); continue; }
        d_close(&d, "debug_tris");
        if (g_cmp.px_bad != before)
            fprintf(stderr, "tri %d: (%d,%d) (%d,%d) (%d,%d)\n", i, X[0], Y[0], X[1], Y[1], X[2], Y[2]);
    }
}

/* ================================================ render targets as textures
 * The game samples its own render targets: bloom / blur / depth-of-field
 * passes texture from the frame buffer, CLUT tricks read a CT32 buffer as
 * T8/T4/T8H, depth effects read the Z buffer as colour, and GfxEndFrame reads
 * 8x8 Z rectangles back (sceGsExecStoreImage, PSMZ32 over a Z24 buffer).
 * Every scene here is exact (tol 0). */

static void frame1(dual *d, uint32_t fbp, uint32_t fbw, uint32_t psm, int w, int h)
{
    ad(d, GS_FRAME_1, r_frame(fbp, fbw, psm, 0));
    ad(d, GS_SCISSOR_1, r_scissor(0, (uint32_t)w - 1, 0, (uint32_t)h - 1));
}

static void tex1(dual *d, uint64_t tex0, int linear, uint64_t clamp)
{
    ad(d, GS_TEX0_1, tex0);
    ad(d, GS_TEX1_1, linear ? 0x60 : 0);
    ad(d, GS_CLAMP_1, clamp);
}

/* textured sprite with UV in 1/16 texels and a Z value */
static void tsprite_z(dual *d, uint32_t prim, int x0, int y0, int x1, int y1, int u0, int v0,
                      int u1, int v1, uint32_t rgba, uint32_t z)
{
    ad(d, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST | prim);
    ad(d, GS_RGBAQ, r_rgbaq(rgba, 1.0f));
    ad(d, GS_UV, r_uv(u0, v0));
    ad(d, GS_XYZ2, r_xyz(x0 << 4, y0 << 4, z));
    ad(d, GS_UV, r_uv(u1, v1));
    ad(d, GS_XYZ2, r_xyz(x1 << 4, y1 << 4, z));
}

/* 1:1 copy of the w x h texel block at (sx,sy) to the pixels at (dx,dy),
 * sampled at texel centres */
static void copy_spr(dual *d, uint32_t prim, int dx, int dy, int sx, int sy, int w, int h,
                     uint32_t rgba)
{
    tsprite(d, prim, dx, dy, dx + w, dy + h, 8 + 16 * sx, 8 + 16 * sy, 8 + 16 * (sx + w),
            8 + 16 * (sy + h), rgba);
}

/* random flat sprites; z_max > 0 gives each a random Z below it */
static void scribble(dual *d, int w, int h, int n, uint32_t z_max)
{
    for (int i = 0; i < n; i++) {
        int x = (int)(rnd() % (uint32_t)(w - 4)), y = (int)(rnd() % (uint32_t)(h - 4));
        int sw = 4 + (int)(rnd() % 60), sh = 4 + (int)(rnd() % 40);
        if (x + sw > w) sw = w - x;
        if (y + sh > h) sh = h - y;
        sprite(d, 0, x, y, x + sw, y + sh, rnd(), z_max ? rnd() % z_max : 0);
    }
}

/* flat triangles of constant Z on whole-pixel vertices */
static void flat_tris(dual *d, int w, int h, int n, uint32_t z_max)
{
    for (int i = 0; i < n; i++) {
        int x = (int)(rnd() % (uint32_t)(w - 40)), y = (int)(rnd() % (uint32_t)(h - 40));
        uint32_t z = rnd() % z_max, c = rnd();
        int x1 = x + 8 + (int)(rnd() % 32), y1 = y + (int)(rnd() % 8);
        int x2 = x + (int)(rnd() % 16), y2 = y + 8 + (int)(rnd() % 32);
        ad(d, GS_PRIM, GS_PRIM_TRIANGLE);
        vtx(d, c, x * 16, y * 16, z);
        vtx(d, c, x1 * 16, y1 * 16, z);
        vtx(d, c, x2 * 16, y2 * 16, z);
    }
}

/* A CT32 frame sampled back in every texture format (format reinterpretation
 * of the same pages), then a bilinear downsample chain A -> C -> D added back
 * onto A (the bloom shape), then a CLUT drawn by the GPU.  A is re-dirtied
 * between passes so every pass samples data only the GPU target holds. */
static void scene_rtt_formats(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
    ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 1));
    sprite(&d, 0, 0, 0, 256, 128, 0x80402010u, 0);
    scribble(&d, 256, 128, 60, 0);
    const uint32_t B = 64, C = 96, D = 112;            /* pages */
    const uint32_t C32 = 120 * 32, C16 = 121 * 32;    /* CLUTs (blocks) */
    upload_random(&d, C32, 1, GS_PSMCT32, 16, 16);
    upload_random(&d, C16, 1, GS_PSMCT16, 16, 16);
    static const struct {
        const char *n;
        uint32_t psm, tbw;
        int clut;
        uint32_t csa;
        uint64_t texa;
    } T[] = {
        { "A as ct32", GS_PSMCT32, 4, 0, 0, 0x80 | (0x80ull << 32) },
        { "A as ct24", GS_PSMCT24, 4, 0, 0, 0x30 | (1ull << 15) | (0x90ull << 32) },
        { "A as ct16", GS_PSMCT16, 4, 0, 0, 0x10 | (1ull << 15) | (0xF0ull << 32) },
        { "A as ct16s", GS_PSMCT16S, 4, 0, 0, 0x40 | (0x77ull << 32) },
        { "A as t8 (ct32 clut)", GS_PSMT8, 4, 32, 0, 0x80 | (0x80ull << 32) },
        { "A as t8 (ct16 clut)", GS_PSMT8, 8, 16, 0, 0x20 | (0xA0ull << 32) },
        { "A as t4", GS_PSMT4, 4, 16, 3, 0x30 | (0x60ull << 32) },
        { "A as t8h", GS_PSMT8H, 4, 32, 0, 0x80 | (0x80ull << 32) },
        { "A as t4hl", GS_PSMT4HL, 4, 16, 1, 0x80 | (0x80ull << 32) },
        { "A as t4hh", GS_PSMT4HH, 4, 32, 2, 0x80 | (0x80ull << 32) },
        { "A as z32", GS_PSMZ32, 4, 0, 0, 0x80 | (0x80ull << 32) },
        { "A as z24", GS_PSMZ24, 4, 0, 0, 0x50 | (0x80ull << 32) },
        { "A as z16", GS_PSMZ16, 4, 0, 0, 0x50 | (0x60ull << 32) },
    };
    for (size_t i = 0; i < sizeof T / sizeof T[0]; i++) {
        /* draw a little more into A: the newest data lives in its target */
        frame1(&d, 0, 4, GS_PSMCT32, 256, 128);
        scribble(&d, 256, 128, 4, 0);
        frame1(&d, B, 4, GS_PSMCT32, 256, 128);
        ad(&d, GS_TEXA, T[i].texa);
        uint32_t cbp = T[i].clut == 32 ? C32 : (T[i].clut == 16 ? C16 : 0);
        uint32_t cpsm = T[i].clut == 16 ? GS_PSMCT16 : GS_PSMCT32;
        tex1(&d, r_tex0(0, T[i].tbw, T[i].psm, 8, 7, 1, 1, cbp, cpsm, 0, T[i].csa,
                        T[i].clut ? 1 : 0), 0, r_clamp(0, 0, 0, 0, 0, 0));
        copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x80808080u);
        d_check(&d, T[i].n);
    }
    /* bloom: A -> C (1/2, 2x2 box via bilinear at texel corners) -> D (1/4)
     * -> added back onto A, magnified x4 with bilinear */
    frame1(&d, C, 2, GS_PSMCT32, 128, 64);
    tex1(&d, r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0), 1, r_clamp(1, 1, 0, 0, 0, 0));
    tsprite(&d, 0, 0, 0, 128, 64, 16, 16, 16 + 256 * 16, 16 + 128 * 16, 0x80808080u);
    frame1(&d, D, 1, GS_PSMCT32, 64, 32);
    tex1(&d, r_tex0(C * 32, 2, GS_PSMCT32, 7, 6, 1, 1, 0, 0, 0, 0, 0), 1, r_clamp(1, 1, 0, 0, 0, 0));
    tsprite(&d, 0, 0, 0, 64, 32, 16, 16, 16 + 128 * 16, 16 + 64 * 16, 0x80808080u);
    d_check(&d, "bloom downsample");
    frame1(&d, 0, 4, GS_PSMCT32, 256, 128);
    ad(&d, GS_ALPHA_1, r_alpha(0, 2, 2, 1, 0x40));     /* Cs * 0.5 + Cd */
    tex1(&d, r_tex0(D * 32, 1, GS_PSMCT32, 6, 5, 1, 0, 0, 0, 0, 0, 0), 1, r_clamp(1, 1, 0, 0, 0, 0));
    tsprite(&d, PRIM_ABE, 0, 0, 256, 128, 4, 4, 4 + 64 * 16, 4 + 32 * 16, 0x80808080u);
    d_check(&d, "bloom add back");
    /* the CLUT itself drawn by the GPU, then A as T8 through it */
    frame1(&d, 120, 1, GS_PSMCT32, 16, 16);
    scribble(&d, 16, 16, 6, 0);
    frame1(&d, B, 4, GS_PSMCT32, 256, 128);
    tex1(&d, r_tex0(0, 4, GS_PSMT8, 8, 7, 1, 1, C32, GS_PSMCT32, 0, 0, 1), 0, r_clamp(0, 0, 0, 0, 0, 0));
    copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x80808080u);
    d_close(&d, "rtt_formats");
}

typedef struct texfmt { uint32_t psm; int clut; uint64_t texa; } texfmt;

/* Z buffers read back and sampled: GfxEndFrame's 8x8 PSMZ32 store-image of
 * a Z24 buffer (and the same as Z24 / colour), repeated after more drawing;
 * part of the Z buffer cleared by drawing into it as a colour buffer, then
 * depth-tested against; the Z buffer sampled as CT32/CT24/Z/T8/T8H/CT16 and
 * blurred into a depth-of-field blend.  CT32+Z24, then CT16+Z16. */
static void scene_rtt_depth(gpu_renderer *r)
{
    static const texfmt T0[] = {
        { GS_PSMCT32, 0, 0x80 | (0x80ull << 32) }, { GS_PSMCT24, 0, 0x30 | (0x90ull << 32) },
        { GS_PSMZ24, 0, 0x60 | (0x90ull << 32) }, { GS_PSMZ32, 0, 0x80 | (0x80ull << 32) },
        { GS_PSMT8, 1, 0x80 | (0x80ull << 32) }, { GS_PSMT8H, 1, 0x80 | (0x80ull << 32) },
        { GS_PSMT4HH, 1, 0x80 | (0x80ull << 32) },
    };
    static const texfmt T1[] = {
        { GS_PSMCT16, 0, 0x10 | (1ull << 15) | (0xF0ull << 32) },
        { GS_PSMZ16, 0, 0x50 | (0x60ull << 32) }, { GS_PSMCT16S, 0, 0x50 | (0x60ull << 32) },
        { GS_PSMT8, 1, 0x80 | (0x80ull << 32) }, { GS_PSMT4, 1, 0x80 | (0x80ull << 32) },
        { GS_PSMCT32, 0, 0x80 | (0x80ull << 32) },
    };
    for (int pass = 0; pass < 2; pass++) {
        uint32_t fpsm = pass ? GS_PSMCT16 : GS_PSMCT32, zpsm = pass ? GS_PSMZ16 : GS_PSMZ24;
        uint32_t zm = pass ? 0x10000u : 0x1000000u;
        uint32_t zcol = pass ? GS_PSMCT16 : GS_PSMCT32;   /* Z memory as a colour buffer */
        const uint32_t ZB = 32, B = 64, C = 96;
        const char *tag = pass ? "z16" : "z24";
        char where[96];
        dual d;
        d_open(&d, r);
        target(&d, 4, fpsm, ZB, zpsm, 256, 128);
        sprite(&d, 0, 0, 0, 256, 128, 0x80000000u, 0);           /* clears Z (ALWAYS) */
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));       /* GEQUAL */
        for (int round = 0; round < 3; round++) {
            scribble(&d, 256, 128, 30, zm);
            flat_tris(&d, 256, 128, 12, zm);
            /* GfxEndFrame: four 8x8 slots, PSMZ32 over the Z buffer */
            for (int s = 0; s < 4; s++) {
                int x = 4 + (int)(rnd() % 248), y = 4 + (int)(rnd() % 120);
                snprintf(where, sizeof where, "%s readback psmz32 round %d", tag, round);
                download_cmp(&d, ZB * 32, 4, GS_PSMZ32, (uint32_t)(x - 4), (uint32_t)(y - 4), 8, 8,
                             where);
            }
            snprintf(where, sizeof where, "%s readback as zpsm round %d", tag, round);
            download_cmp(&d, ZB * 32, 4, zpsm, 16, 8, 64, 32, where);
            snprintf(where, sizeof where, "%s readback as colour round %d", tag, round);
            download_cmp(&d, ZB * 32, 4, zcol, 100, 50, 40, 30, where);
            if (round == 1) {
                /* clear part of the Z buffer by drawing into it as colour */
                frame1(&d, ZB, 4, zcol, 256, 128);
                ad(&d, GS_ZBUF_1, r_zbuf(ZB, zpsm, 1));
                ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
                sprite(&d, 0, 64, 0, 192, 128, pass ? 0x00000000u : 0x00012345u, 0);
                frame1(&d, 0, 4, fpsm, 256, 128);
                ad(&d, GS_ZBUF_1, r_zbuf(ZB, zpsm, 0));
                ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
            }
        }
        snprintf(where, sizeof where, "%s drawn", tag);
        d_check(&d, where);
        /* the Z buffer sampled as colour, with depth-tested drawing between */
        const uint32_t CL = 121 * 32;
        upload_random(&d, CL, 1, GS_PSMCT32, 16, 16);
        const texfmt *T = pass ? T1 : T0;
        int nt = pass ? (int)(sizeof T1 / sizeof T1[0]) : (int)(sizeof T0 / sizeof T0[0]);
        for (int i = 0; i < nt; i++) {
            ad(&d, GS_ZBUF_1, r_zbuf(ZB, zpsm, 1));
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
            frame1(&d, B, 4, GS_PSMCT32, 256, 128);
            ad(&d, GS_TEXA, T[i].texa);
            tex1(&d, r_tex0(ZB * 32, 4, T[i].psm, 8, 7, 1, 1, T[i].clut ? CL : 0, GS_PSMCT32, 0, 0,
                            T[i].clut), 0, r_clamp(1, 1, 0, 0, 0, 0));
            copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x80808080u);
            snprintf(where, sizeof where, "%s sampled as psm %02X", tag, T[i].psm);
            d_check(&d, where);
            frame1(&d, 0, 4, fpsm, 256, 128);
            ad(&d, GS_ZBUF_1, r_zbuf(ZB, zpsm, 0));
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
            scribble(&d, 256, 128, 3, zm);
        }
        /* depth of field: blur the Z buffer (as colour) to half size, then
         * blend the frame towards it with the blurred alpha */
        ad(&d, GS_ZBUF_1, r_zbuf(ZB, zpsm, 1));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        frame1(&d, C, 2, GS_PSMCT32, 128, 64);
        ad(&d, GS_TEXA, 0x80 | (0x80ull << 32));
        tex1(&d, r_tex0(ZB * 32, 4, zcol, 8, 7, 1, 1, 0, 0, 0, 0, 0), 1, r_clamp(1, 1, 0, 0, 0, 0));
        tsprite(&d, 0, 0, 0, 128, 64, 16, 16, 16 + 256 * 16, 16 + 128 * 16, 0x80808080u);
        frame1(&d, 0, 4, fpsm, 256, 128);
        ad(&d, GS_ALPHA_1, r_alpha(0, 1, 0, 1, 0));   /* (Cs - Cd) * As + Cd */
        tex1(&d, r_tex0(C * 32, 2, GS_PSMCT32, 7, 6, 1, 1, 0, 0, 0, 0, 0), 1, r_clamp(1, 1, 0, 0, 0, 0));
        tsprite(&d, PRIM_ABE, 0, 0, 256, 128, 8, 8, 8 + 128 * 16, 8 + 64 * 16, 0x80808080u);
        snprintf(where, sizeof where, "rtt_depth %s", tag);
        d_close(&d, where);
    }
}

/* Feedback: the texture is the buffer being drawn.  Each primitive must see
 * what the earlier primitives drew (the GS draws in order), so a chain of
 * copies inside one batch propagates.  Every primitive here reads either
 * pixels it does not write or exactly its own pixel (the cases whose result
 * does not depend on the order of pixels within one primitive). */
static void scene_rtt_feedback(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
    ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 1));
    upload_random(&d, 0, 4, GS_PSMCT32, 256, 128);
    scribble(&d, 256, 128, 12, 0);
    const uint64_t A32 = r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0);
    const uint64_t CLAMP = r_clamp(1, 1, 0, 0, 0, 0);
    /* 1. horizontal chain: block k-1 -> block k */
    tex1(&d, A32, 0, CLAMP);
    for (int k = 1; k < 8; k++) copy_spr(&d, 0, 32 * k, 0, 32 * (k - 1), 0, 32, 32, 0x80808080u);
    d_check(&d, "feedback chain x");
    /* 2. vertical chain of 8-row bands, bilinear at texel centres */
    tex1(&d, A32, 1, CLAMP);
    for (int y = 32; y <= 112; y += 8) copy_spr(&d, 0, 0, y + 8, 0, y, 128, 8, 0x80808080u);
    d_check(&d, "feedback chain y bilinear");
    /* 3. in place, three times: each pass halves what the previous wrote */
    tex1(&d, r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), 0, CLAMP);
    for (int i = 0; i < 3; i++) copy_spr(&d, 0, 128, 32, 128, 32, 128, 96, 0x40404040u);
    d_check(&d, "feedback in place");
    /* 4. additive chain (blending reads the destination too) */
    ad(&d, GS_ALPHA_1, r_alpha(0, 2, 2, 1, 0x60));
    tex1(&d, A32, 0, CLAMP);
    for (int k = 1; k < 8; k++)
        copy_spr(&d, PRIM_ABE, 32 * k, 96, 32 * (k - 1), 96, 32, 32, 0x80808080u);
    d_check(&d, "feedback additive chain");
    /* 5. Z feedback: each sprite writes Z, the next samples that Z as CT32.
     * One whole Z page each: CT32 and Z24 arrange the blocks of a page
     * differently, so a sprite reading half a page as CT32 would also read
     * Z it is writing itself (order-dependent, see GPU.md). */
    ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 0));
    tex1(&d, r_tex0(32 * 32, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0), 0, CLAMP);
    for (int k = 0; k < 4; k++) {
        int sx = k ? 64 * (k - 1) : 0, sy = k ? 64 : 0;
        tsprite_z(&d, 0, 64 * k, 64, 64 * k + 64, 96, 8 + 16 * sx, 8 + 16 * sy, 8 + 16 * (sx + 64),
                  8 + 16 * (sy + 32), 0x80808080u, (rnd() & 0xFFFFFF) | 0x10101);
    }
    ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 1));
    d_check(&d, "feedback z");
    /* 6. T8H in place: the alpha byte indexes a CLUT, RGB written, alpha kept */
    const uint32_t C32 = 120 * 32;
    upload_random(&d, C32, 1, GS_PSMCT32, 16, 16);
    ad(&d, GS_FRAME_1, r_frame(0, 4, GS_PSMCT32, 0xFF000000u));
    tex1(&d, r_tex0(0, 4, GS_PSMT8H, 8, 7, 1, 1, C32, GS_PSMCT32, 0, 0, 1), 0, CLAMP);
    copy_spr(&d, 0, 0, 0, 0, 0, 128, 64, 0x80808080u);
    copy_spr(&d, 0, 128, 0, 128, 0, 128, 64, 0x80808080u);
    copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x80808080u);
    ad(&d, GS_FRAME_1, r_frame(0, 4, GS_PSMCT32, 0));
    d_check(&d, "feedback t8h");
    /* 7. A as T4 (16-colour CLUT) feeding itself, rows of pages */
    const uint32_t C16 = 121 * 32;
    upload_random(&d, C16, 1, GS_PSMCT16, 8, 2);
    tex1(&d, r_tex0(0, 4, GS_PSMT4, 8, 7, 1, 1, C16, GS_PSMCT16, 0, 0, 1), 0, CLAMP);
    for (int k = 0; k < 4; k++) copy_spr(&d, 0, 64 * k, 64, 64 * k, 0, 64, 64, 0x80808080u);
    d_check(&d, "feedback t4");
    /* 8. an upload into the sampled block between two primitives */
    tex1(&d, A32, 0, CLAMP);
    copy_spr(&d, 0, 192, 0, 0, 0, 32, 32, 0x80808080u);
    upload_random(&d, 0, 4, GS_PSMCT32, 32, 32);
    copy_spr(&d, 0, 224, 0, 0, 0, 32, 32, 0x80808080u);
    d_close(&d, "rtt_feedback");
}

/* ============================================== direct (upscaled) sampling
 * Bloom and depth-of-field passes whose textures are live render targets:
 * every pass samples the target itself (docs/GPU.md "Direct sampling"), at
 * the internal resolution, with no write-back.  Scale 1: exact.  Scale > 1:
 * the native result (the write-back's sub-sample (s/2, s/2)) must match the
 * reference within the tolerance set below (bilinear on the upscaled image
 * vs bilinear on the native one, smooth sources).  Then an upscaled-detail check: a
 * target with sub-pixel triangle edges copied 1:1 must arrive bit-identical
 * at the internal resolution (the mirror path would make it blocky). */
extern int g_fail;
static uint64_t g_up_wb0, g_up_dir0, g_up_av0, g_up_cp0;
static void stats_mark(dual *d)
{
    flush(d);
    gpu_flush(d->r);
    const gpu_stats *s = gpu_get_stats(d->r);
    g_up_wb0 = s->rt_writebacks;
    g_up_dir0 = s->direct_samples;
    g_up_av0 = s->writebacks_avoided;
    g_up_cp0 = s->tex_copies;
}
/* the passes since stats_mark: all direct, no write-back, `avoid` avoided */
static void stats_expect(dual *d, const char *where, uint64_t passes, uint64_t avoid,
                         uint64_t copies)
{
    gpu_renderer *r = d->r;
    flush(d);
    gpu_flush(r);
    const gpu_stats *s = gpu_get_stats(r);
    uint64_t wb = s->rt_writebacks - g_up_wb0, dir = s->direct_samples - g_up_dir0,
             av = s->writebacks_avoided - g_up_av0, cp = s->tex_copies - g_up_cp0;
    printf("  [%s] direct samples %llu, write-backs %llu, write-backs avoided %llu, target copies %llu\n",
           where, (unsigned long long)dir, (unsigned long long)wb, (unsigned long long)av,
           (unsigned long long)cp);
    if (dir != passes || wb != 0 || av < avoid || cp != copies) {
        fprintf(stderr, "  [%s] expected %llu direct samples, 0 write-backs, >= %llu avoided, %llu copies\n",
                where, (unsigned long long)passes, (unsigned long long)avoid,
                (unsigned long long)copies);
        g_fail++;
    }
}

int g_rtt_native;   /* gpu_tests.c: the renderer samples targets through the mirror */

/* a smooth CT32 image: gradients in every channel, 2 bits of noise, no
 * wrap-around (bloom/DOF sources are smooth) */
static void upload_soft(dual *d, uint32_t dbp, uint32_t dbw, uint32_t w, uint32_t h)
{
    uint8_t *b = (uint8_t *)malloc(w * h * 4);
    for (uint32_t y = 0; y < h; y++)
        for (uint32_t x = 0; x < w; x++) {
            uint8_t *p = b + (y * w + x) * 4;
            p[0] = (uint8_t)(16 + x * 200 / w + (rnd() & 3));
            p[1] = (uint8_t)(16 + y * 200 / h + (rnd() & 3));
            p[2] = (uint8_t)(60 + ((x + y) * 127) / (w + h) + (rnd() & 3));
            p[3] = (uint8_t)(0x30 + ((x + 2 * y) * 0x40) / (w + 2 * h));
        }
    upload(d, dbp, dbw, GS_PSMCT32, 0, 0, w, h, b, w * h * 4);
    free(b);
}

/* Scale 1: d_check (exact).  Scale > 1: every colour target of the scene,
 * read at the internal resolution and box-filtered (truncated mean of each
 * scale x scale block: "the reference downsampled"), against the reference
 * with tolerance g_cmp_tol.  The write-back keeps one sub-sample per pixel,
 * which at a hard edge an upscaled pass resolves differently by design, so
 * local memory is not compared there. */
static const struct { uint32_t page, bw, w, h; } UPT[] = {
    { 0, 4, 256, 128 }, { 64, 2, 128, 64 }, { 72, 1, 64, 32 }, { 76, 2, 128, 64 }, { 80, 4, 256, 128 },
};
static void up_check(dual *d, const char *where)
{
    int s = gpu_get_scale(d->r);
    if (s == 1) { d_check(d, where); return; }
    flush(d);
    g_cmp.checkpoints++;
    static uint32_t hi[256 * 128 * 64];
    for (size_t t = 0; t < sizeof UPT / sizeof UPT[0]; t++) {
        uint32_t bp = UPT[t].page * 32, bw = UPT[t].bw, w = UPT[t].w, h = UPT[t].h;
        if (gpu_read_target(d->r, bp, bw, GS_PSMCT32, 0, 0, (int)w, (int)h, hi)) continue;
        for (uint32_t y = 0; y < h; y++)
            for (uint32_t x = 0; x < w; x++) {
                uint32_t acc[4] = { 0, 0, 0, 0 };
                for (int sy = 0; sy < s; sy++)
                    for (int sx = 0; sx < s; sx++) {
                        uint32_t c = hi[(size_t)(y * s + sy) * w * s + x * s + sx];
                        for (int k = 0; k < 4; k++) acc[k] += (c >> (8 * k)) & 255u;
                    }
                uint32_t vh = 0;
                for (int k = 0; k < 4; k++) vh |= (acc[k] / (uint32_t)(s * s)) << (8 * k);
                uint32_t vs = gs_read_pixel(d->sw, GS_PSMCT32, bp, bw, x, y);
                g_cmp.px++;
                if (vs == vh) { g_cmp.px_exact++; continue; }
                int diff = 0;
                for (int k = 0; k < 4; k++) {
                    int dd = abs((int)((vs >> (8 * k)) & 255u) - (int)((vh >> (8 * k)) & 255u));
                    if (dd > diff) diff = dd;
                }
                if (diff > g_cmp.max_diff) g_cmp.max_diff = diff;
                if (diff > g_cmp_tol) {
                    g_cmp.px_bad++;
                    if (g_cmp.px_bad <= 12)
                        fprintf(stderr, "  [%s] page %u (%u,%u): sw %08X gpu (box) %08X\n", where,
                                UPT[t].page, x, y, vs, vh);
                }
            }
    }
}

static void scene_rtt_upscaled(gpu_renderer *r)
{
    const int s = gpu_get_scale(r);
    g_cmp_tol = s > 1 ? 4 : 0;
    const uint32_t A = 0, ZB = 32, T = 48, C = 64, D = 72, DZ = 76, E = 80;   /* pages */
    const uint64_t CLAMP = r_clamp(1, 1, 0, 0, 0, 0);
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, ZB, GS_PSMZ24, 256, 128);
    upload_soft(&d, T * 32, 4, 256, 128);
    /* A: the smooth texture (modulated, so only the GPU target holds it);
     * Z: sprites of random depth over a cleared (0) buffer, drawn with the
     * colour fully masked (bloom sources are smooth: the comparison
     * measures the resampling, not the resolve of hard edges) */
    tex1(&d, r_tex0(T * 32, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), 0, CLAMP);
    copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x70707070u);
    ad(&d, GS_FRAME_1, r_frame(A, 4, GS_PSMCT32, 0xFFFFFFFFu));
    ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));          /* GEQUAL */
    for (int i = 0; i < 24; i++) {
        int x = (int)(rnd() % 200), y = (int)(rnd() % 90);
        int w = 16 + (int)(rnd() % 56), h = 12 + (int)(rnd() % 38);
        if (x + w > 256) w = 256 - x;
        if (y + h > 128) h = 128 - y;
        sprite(&d, 0, x, y, x + w, y + h, rnd(), 0x100000u + (rnd() & 0xEFFFFF));
    }
    ad(&d, GS_FRAME_1, r_frame(A, 4, GS_PSMCT32, 0));
    ad(&d, GS_ZBUF_1, r_zbuf(ZB, GS_PSMZ24, 1));
    ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    const uint64_t ADD_HALF = r_alpha(0, 2, 2, 1, 0x40);        /* Cs/2 + Cd */

    /* ---- bloom: A -> C (1/2) -> D (1/4), then D -> C (x2) and C -> A (x2),
     * added; every source is a dirty target */
    stats_mark(&d);
    frame1(&d, C, 2, GS_PSMCT32, 128, 64);
    tex1(&d, r_tex0(A * 32, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, 0, 0, 0, 128, 64, 16, 16, 16 + 256 * 16, 16 + 128 * 16, 0x80808080u);
    frame1(&d, D, 1, GS_PSMCT32, 64, 32);
    tex1(&d, r_tex0(C * 32, 2, GS_PSMCT32, 7, 6, 1, 1, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, 0, 0, 0, 64, 32, 16, 16, 16 + 128 * 16, 16 + 64 * 16, 0x80808080u);
    frame1(&d, C, 2, GS_PSMCT32, 128, 64);
    ad(&d, GS_ALPHA_1, ADD_HALF);
    tex1(&d, r_tex0(D * 32, 1, GS_PSMCT32, 6, 5, 1, 0, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, PRIM_ABE, 0, 0, 128, 64, 4, 4, 4 + 64 * 16, 4 + 32 * 16, 0x80808080u);
    frame1(&d, A, 4, GS_PSMCT32, 256, 128);
    tex1(&d, r_tex0(C * 32, 2, GS_PSMCT32, 7, 6, 1, 0, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, PRIM_ABE, 0, 0, 256, 128, 4, 4, 4 + 128 * 16, 4 + 64 * 16, 0x80808080u);
    stats_expect(&d, "bloom", g_rtt_native ? 0 : 4, g_rtt_native ? 0 : 4, 0);
    up_check(&d, "bloom down/up");

    /* ---- in place: C blurred into itself (bilinear at texel corners reads
     * ahead of the raster order), twice; direct through a target copy */
    stats_mark(&d);
    frame1(&d, C, 2, GS_PSMCT32, 128, 64);
    tex1(&d, r_tex0(C * 32, 2, GS_PSMCT32, 7, 6, 1, 1, 0, 0, 0, 0, 0), 1, CLAMP);
    for (int i = 0; i < 2; i++)
        tsprite(&d, 0, 0, 0, 128, 64, 16, 16, 16 + 128 * 16, 16 + 64 * 16, 0x80808080u);
    stats_expect(&d, "in-place blur", g_rtt_native ? 0 : 2, 0, g_rtt_native ? 0 : 2);
    up_check(&d, "in-place blur");

    /* ---- depth of field: A blurred to C; the Z buffer sampled directly as
     * PSMZ24 into DZ (AEM: alpha 0 where nothing was drawn, else TA0), its
     * alpha moved into C's alpha, then A = A + (C - A) * Ac, magnified x2 */
    frame1(&d, A, 4, GS_PSMCT32, 256, 128);
    tex1(&d, r_tex0(T * 32, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), 0, CLAMP);
    copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x78787878u);              /* dirty A again */
    stats_mark(&d);
    frame1(&d, C, 2, GS_PSMCT32, 128, 64);
    tex1(&d, r_tex0(A * 32, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, 0, 0, 0, 128, 64, 16, 16, 16 + 256 * 16, 16 + 128 * 16, 0x80808080u);
    frame1(&d, DZ, 2, GS_PSMCT32, 128, 64);
    ad(&d, GS_TEXA, 0x08 | (1ull << 15) | (0x08ull << 32));   /* soft mask: see GPU.md */
    tex1(&d, r_tex0(ZB * 32, 4, GS_PSMZ24, 8, 7, 1, 1, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, 0, 0, 0, 128, 64, 16, 16, 16 + 256 * 16, 16 + 128 * 16, 0x80808080u);
    ad(&d, GS_TEXA, 0x80 | (0x80ull << 32));
    frame1(&d, C, 2, GS_PSMCT32, 128, 64);
    ad(&d, GS_FRAME_1, r_frame(C, 2, GS_PSMCT32, 0x00FFFFFFu));    /* alpha only */
    tex1(&d, r_tex0(DZ * 32, 2, GS_PSMCT32, 7, 6, 1, 1, 0, 0, 0, 0, 0), 0, CLAMP);
    copy_spr(&d, 0, 0, 0, 0, 0, 128, 64, 0x80808080u);
    frame1(&d, A, 4, GS_PSMCT32, 256, 128);
    ad(&d, GS_ALPHA_1, r_alpha(0, 1, 0, 1, 0));                    /* (Cs-Cd)*As + Cd */
    tex1(&d, r_tex0(C * 32, 2, GS_PSMCT32, 7, 6, 1, 1, 0, 0, 0, 0, 0), 1, CLAMP);
    tsprite(&d, PRIM_ABE, 0, 0, 256, 128, 4, 4, 4 + 128 * 16, 4 + 64 * 16, 0x80808080u);
    stats_expect(&d, "dof", g_rtt_native ? 0 : 4, g_rtt_native ? 0 : 3, 0);
    up_check(&d, "dof blend");

    /* ---- upscaled detail: Gouraud triangles with sub-pixel vertices in A,
     * A copied 1:1 (texel centres, point) to E: at the internal resolution
     * E must equal A exactly.  The triangles are then covered with flat
     * sprites (their upscaled edges resolve differently from the reference's
     * coverage, which is not what this scene measures). */
    frame1(&d, A, 4, GS_PSMCT32, 256, 128);
    for (int i = 0; i < 6; i++) {
        int x = 8 + (int)(rnd() % 180), y = 8 + (int)(rnd() % 60);
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
        vtx(&d, rnd(), x * 16 + (int)(rnd() & 15), y * 16 + (int)(rnd() & 15), 0);
        vtx(&d, rnd(), (x + 50) * 16 + (int)(rnd() & 15), (y + 7) * 16 + (int)(rnd() & 15), 0);
        vtx(&d, rnd(), (x + 13) * 16 + (int)(rnd() & 15), (y + 45) * 16 + (int)(rnd() & 15), 0);
    }
    frame1(&d, E, 4, GS_PSMCT32, 256, 128);
    tex1(&d, r_tex0(A * 32, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0), 0, CLAMP);
    copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x80808080u);
    flush(&d);
    {
        size_t n = (size_t)256 * 128 * (size_t)(s * s);
        uint32_t *ha = (uint32_t *)malloc(n * 4), *he = (uint32_t *)malloc(n * 4);
        int ra = gpu_read_target(r, A * 32, 4, GS_PSMCT32, 0, 0, 256, 128, ha);
        int re = gpu_read_target(r, E * 32, 4, GS_PSMCT32, 0, 0, 256, 128, he);
        uint64_t diff = 0, nonuni = 0;
        for (size_t i = 0; i < n; i++) diff += ha[i] != he[i];
        /* sub-sample variation inside native pixels: the detail itself */
        for (int y = 0; y < 128 * s && ra == 0; y++)
            for (int x = 0; x < 256 * s; x++)
                nonuni += ha[(size_t)y * 256 * s + (size_t)x] !=
                          ha[(size_t)(y / s * s) * 256 * s + (size_t)(x / s * s)];
        printf("  [upscaled detail] scale %d: %llu sub-samples, %llu differ within their pixel,"
               " copy differs at %llu\n", s, (unsigned long long)n, (unsigned long long)nonuni,
               (unsigned long long)diff);
        if (ra || re || diff || (s > 1 && !nonuni)) {
            fprintf(stderr, "  [upscaled detail] read %d/%d, %llu sub-samples of the copy differ\n",
                    ra, re, (unsigned long long)diff);
            g_fail++;
        }
        free(ha);
        free(he);
    }
    frame1(&d, A, 4, GS_PSMCT32, 256, 128);
    sprite(&d, 0, 0, 0, 256, 128, 0x80406080u, 0);
    frame1(&d, E, 4, GS_PSMCT32, 256, 128);
    sprite(&d, 0, 0, 0, 256, 128, 0x80806040u, 0);
    if (s == 1) {
        d_close(&d, "rtt_upscaled");
    } else {
        up_check(&d, "rtt_upscaled");
        gpu_detach(r);
        gs_destroy(d.sw);
        gs_destroy(d.hw);
    }
}

/* FRAME and ZBUF on the same pages in one draw: the reference interleaves
 * every pixel's colour and Z write in one memory (CT32 and Z24 arrange a
 * page's blocks differently, so one pixel's Z lands in another pixel's
 * colour).  The renderer hands these primitives to the software rasterizer;
 * the result must be exact, and the GPU targets around them coherent. */
static void scene_rtt_alias(gpu_renderer *r)
{
    static const struct { uint32_t f, z, zbp; const char *n; } V[] = {
        { GS_PSMCT32, GS_PSMZ24, 0, "ct32 + z24 same pages" },
        { GS_PSMCT32, GS_PSMZ32, 8, "ct32 + z32 lower half" },
        { GS_PSMCT16, GS_PSMZ16, 0, "ct16 + z16 same pages" },
    };
    for (size_t vi = 0; vi < sizeof V / sizeof V[0]; vi++) {
        uint32_t zm = V[vi].z == GS_PSMZ16 ? 0x10000u : 0x1000000u;
        dual d;
        d_open(&d, r);
        target(&d, 4, V[vi].f, 64, V[vi].z, 256, 128);       /* separate Z first */
        upload_random(&d, 0, 4, V[vi].f, 256, 128);
        scribble(&d, 256, 128, 10, zm);                        /* GPU targets live */
        ad(&d, GS_ZBUF_1, r_zbuf(V[vi].zbp, V[vi].z, 0));     /* now the same pages */
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
        scribble(&d, 256, 128, 20, zm);
        flat_tris(&d, 256, 128, 8, zm);
        d_check(&d, V[vi].n);
        /* back to GPU drawing over the CPU-drawn pages, then sampling them */
        ad(&d, GS_ZBUF_1, r_zbuf(64, V[vi].z, 0));
        scribble(&d, 256, 128, 6, zm);
        ad(&d, GS_ZBUF_1, r_zbuf(64, V[vi].z, 1));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        frame1(&d, 96, 4, GS_PSMCT32, 256, 128);
        tex1(&d, r_tex0(0, 4, V[vi].f, 8, 7, 1, 1, 0, 0, 0, 0, 0), 0, r_clamp(1, 1, 0, 0, 0, 0));
        copy_spr(&d, 0, 0, 0, 0, 0, 256, 128, 0x80808080u);
        /* and once more on the same pages, textured, after GPU drawing */
        frame1(&d, 0, 4, V[vi].f, 256, 128);
        ad(&d, GS_ZBUF_1, r_zbuf(V[vi].zbp, V[vi].z, 0));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
        tex1(&d, r_tex0(96 * 32, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), 0, r_clamp(1, 1, 0, 0, 0, 0));
        for (int i = 0; i < 4; i++) {
            int x = (int)(rnd() % 200), y = (int)(rnd() % 90);
            tsprite_z(&d, 0, x, y, x + 50, y + 30, 8 + 16 * x, 8 + 16 * y, 8 + 16 * (x + 50),
                      8 + 16 * (y + 30), 0x60606060u, rnd() % zm);
        }
        d_close(&d, V[vi].n);
    }
    if (!gpu_get_stats(r)->cpu_prims && r) printf("  [rtt_alias] no primitive took the CPU path\n");
}

/* The game's present (GfxFlipBuffersMaybe_143650): every frame the 512x448
 * draw buffer is copied to the display buffer by a textured sprite, and the
 * PCRTC shows the display buffer.  That copy must sample the draw buffer
 * directly, or all upscaling is lost.  CT32 and CT16 frames (the CT16 copy
 * also through a CT16 texture), UV on texel corners and on texel centres;
 * at the internal resolution the display buffer, and the PCRTC output, must
 * equal the draw buffer exactly, with no write-back.  Then a capture into
 * main memory (local->host, ScreenFadeBlockCaptureFrame_177ed0 style) goes
 * through the mirror with native semantics. */
static void scene_rtt_flip(gpu_renderer *r)
{
    const int s = gpu_get_scale(r);
    static const struct { uint32_t psm; int centres; const char *n; } V[] = {
        { GS_PSMCT32, 0, "flip ct32 (texel corners)" },
        { GS_PSMCT32, 1, "flip ct32 (texel centres)" },
        { GS_PSMCT16, 0, "flip ct16 (texel corners)" },
    };
    const uint32_t DRAW = 0, DISP = 112, ZB = 224;   /* pages; 512x448 = 112 pages (CT32) */
    for (size_t vi = 0; vi < sizeof V / sizeof V[0]; vi++) {
        uint32_t psm = V[vi].psm;
        dual d;
        d_open(&d, r);
        target(&d, 8, psm, ZB, GS_PSMZ24, 512, 448);
        upload_random(&d, DRAW * 32, 8, psm, 512, 448);
        /* sub-pixel Gouraud triangles and blended sprites: upscaled detail */
        for (int i = 0; i < 24; i++) {
            int x = 8 + (int)(rnd() % 440), y = 8 + (int)(rnd() % 380);
            ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
            vtx(&d, rnd(), x * 16 + (int)(rnd() & 15), y * 16 + (int)(rnd() & 15), 0);
            vtx(&d, rnd(), (x + 60) * 16 + (int)(rnd() & 15), (y + 9) * 16 + (int)(rnd() & 15), 0);
            vtx(&d, rnd(), (x + 17) * 16 + (int)(rnd() & 15), (y + 55) * 16 + (int)(rnd() & 15), 0);
        }
        for (int i = 0; i < 16; i++) {
            int x = (int)(rnd() % 460), y = (int)(rnd() % 400);
            sprite(&d, PRIM_ABE, x, y, x + 50, y + 40, rnd(), 0);
        }
        /* the flip: draw buffer -> display buffer, one sprite, point */
        stats_mark(&d);
        frame1(&d, DISP, 8, psm, 512, 448);
        ad(&d, GS_TEXA, 0x80ull << 32);   /* CT16: STP 0 -> alpha 0, 1 -> 0x80 (kept) */
        tex1(&d, r_tex0(DRAW * 32, 8, psm, 9, 9, 1, 1, 0, 0, 0, 0, 0), 0, r_clamp(1, 1, 0, 0, 0, 0));
        if (V[vi].centres) copy_spr(&d, 0, 0, 0, 0, 0, 512, 448, 0x80808080u);
        else tsprite(&d, 0, 0, 0, 512, 448, 0, 0, 512 * 16, 448 * 16, 0x80808080u);
        stats_expect(&d, V[vi].n, g_rtt_native ? 0 : 1, g_rtt_native ? 0 : 1, 0);
        size_t n = (size_t)512 * 448 * (size_t)(s * s);
        uint32_t *ha = (uint32_t *)malloc(n * 4), *hb = (uint32_t *)malloc(n * 4);
        int ra = gpu_read_target(r, DRAW * 32, 8, (int)psm, 0, 0, 512, 448, ha);
        int rb = gpu_read_target(r, DISP * 32, 8, (int)psm, 0, 0, 512, 448, hb);
        uint64_t diff = 0, nonuni = 0;
        for (size_t i = 0; i < n; i++) diff += ha[i] != hb[i];
        for (int y = 0; y < 448 * s && ra == 0; y++)
            for (int x = 0; x < 512 * s; x++)
                nonuni += ha[(size_t)y * 512 * s + (size_t)x] !=
                          ha[(size_t)(y / s * s) * 512 * s + (size_t)(x / s * s)];
        /* the PCRTC shows the display buffer at the internal resolution:
         * FIELD mode, 512 wide (MAGH 4), 448 lines, MMOD=1 ALP=0xFF */
        flush(&d);
        uint64_t dispfb = DISP | (8ull << 9) | ((uint64_t)psm << 15);
        uint64_t display = 636 | (25ull << 12) | (3ull << 23) | (2047ull << 32) | (447ull << 44);
        gs_write_priv(d.sw, GS_P_SMODE2, 1); gs_write_priv(d.hw, GS_P_SMODE2, 1);
        gs_write_priv(d.sw, GS_P_DISPFB1, dispfb); gs_write_priv(d.hw, GS_P_DISPFB1, dispfb);
        gs_write_priv(d.sw, GS_P_DISPLAY1, display); gs_write_priv(d.hw, GS_P_DISPLAY1, display);
        uint64_t pmode = 1 | (1u << 5) | (0xFFu << 8);
        gs_write_priv(d.sw, GS_P_PMODE, pmode); gs_write_priv(d.hw, GS_P_PMODE, pmode);
        static uint32_t disp[512 * 448 * 64];
        uint32_t dw = 0, dh = 0;
        int rd = gpu_read_display(r, GS_READ_FRAME, disp, 512 * 448 * 64, &dw, &dh);
        uint64_t ddiff = 0;
        if (rd == 0 && dw == 512u * (uint32_t)s && dh == 448u * (uint32_t)s && rb == 0)
            for (size_t i = 0; i < n; i++) ddiff += ((disp[i] ^ hb[i]) & 0xFFFFFFu) != 0;
        printf("  [%s] scale %d: %llu sub-samples, %llu differ within their pixel, copy differs"
               " at %llu, display %ux%u differs at %llu\n", V[vi].n, s, (unsigned long long)n,
               (unsigned long long)nonuni, (unsigned long long)diff, dw, dh,
               (unsigned long long)ddiff);
        if (ra || rb || rd || diff || ddiff || dw != 512u * (uint32_t)s || (s > 1 && !nonuni)) {
            fprintf(stderr, "  [%s] upscaled flip lost (read %d/%d/%d)\n", V[vi].n, ra, rb, rd);
            g_fail++;
        }
        free(ha);
        free(hb);
        /* cover the sub-pixel edges (they resolve differently from the
         * reference's coverage at scale > 1), flip again, then capture */
        frame1(&d, DRAW, 8, psm, 512, 448);
        for (int y = 0; y < 448; y += 64)
            for (int x = 0; x < 512; x += 64) sprite(&d, 0, x, y, x + 64, y + 64, rnd(), 0);
        frame1(&d, DISP, 8, psm, 512, 448);
        tsprite(&d, 0, 0, 0, 512, 448, 0, 0, 512 * 16, 448 * 16, 0x80808080u);
        d_display(&d, GS_READ_FRAME, V[vi].n);
        download_cmp(&d, DISP * 32, 8, psm, 0, 0, 512, 448, V[vi].n);
        d_close(&d, V[vi].n);
    }
}

/* Scale > 1: the game's anti-flicker display merge (PMODE 0x7F23: both
 * circuits on one buffer, circuit 1 one row lower, 50/50) applied at the
 * internal resolution (docs/GPU.md "Display").  Over sub-pixel Gouraud
 * triangles (content varies inside native pixels) every output pixel
 * (X, Y) must be merge(target[Y + 1], target[Y]) exactly, i.e. the lower
 * circuit is one internal row down, not one native row (which showed every
 * upscaled detail twice, `scale` rows apart).  Scale 1: skipped (the merge
 * is exact in scene.display). */
/* upscaled sub-pixel triangles write back the sub-sample (s/2, s/2), not
 * the reference's pixel centre: no local-memory comparison here */
static void af_close(dual *d)
{
    flush(d);
    gpu_detach(d->r);
    gs_destroy(d->sw);
    gs_destroy(d->hw);
}

static void scene_af_upscaled(gpu_renderer *r)
{
    int s = gpu_get_scale(r);
    if (s < 2) return;
    dual d;
    d_open(&d, r);
    target(&d, 8, GS_PSMCT32, 140, GS_PSMZ24, 512, 448);
    sprite(&d, 0, 0, 0, 512, 448, 0x80102030u, 0);
    ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
    for (int i = 0; i < 60; i++)
        for (int k = 0; k < 3; k++)
            vtx(&d, rnd() | 0x80000000u, (int)(rnd() % (512 * 16)), (int)(rnd() % (448 * 16)), 0);
    flush(&d);
    /* the game's display: DISPFB1 DBY 1, DISPFB2 DBY 0, 512x448 (DH 447/448) */
    const uint64_t prv[][2] = {
        { GS_P_SMODE2, 1 },
        { GS_P_DISPFB1, 0x80000000000ull | (8ull << 9) },
        { GS_P_DISPLAY1, 0x1be9ff0203227cull },
        { GS_P_DISPFB2, (8ull << 9) },
        { GS_P_DISPLAY2, 0x1bf9ff0203227cull },
        { GS_P_BGCOLOR, 0 },
        { GS_P_PMODE, 0x7F23 },
    };
    for (size_t i = 0; i < sizeof prv / sizeof prv[0]; i++) {
        gs_write_priv(d.sw, (uint32_t)prv[i][0], prv[i][1]);
        gs_write_priv(d.hw, (uint32_t)prv[i][0], prv[i][1]);
    }
    static uint32_t T[4096 * 4096], D[4096 * 4096];
    uint32_t W = 512u * (uint32_t)s, H = 448u * (uint32_t)s, w = 0, h = 0;
    int rt = gpu_read_target(r, 0, 8, GS_PSMCT32, 0, 0, 512, 448, T);
    int rd = gpu_read_display(r, GS_READ_FRAME, D, 4096u * 4096u, &w, &h);
    g_cmp.checkpoints++;
    if (rt != 0 || rd != 0 || w != W || h != H) {
        fprintf(stderr, "  [af_upscaled] target %d display %d %ux%u (want %ux%u)\n", rt, rd, w, h, W, H);
        g_cmp.disp_bad++;
        af_close(&d);
        return;
    }
    uint64_t detail = 0;
    for (uint32_t Y = 0; Y < H; Y++)
        for (uint32_t X = 0; X < W; X++) {
            uint32_t p2 = T[Y * W + X], want = p2;
            if (Y / (uint32_t)s < 447) {
                uint32_t p1 = T[(Y + 1) * W + X];
                if (Y + (uint32_t)s < H && T[(Y + (uint32_t)s) * W + X] != p1) detail++;
                want = 0;
                for (int c = 0; c < 24; c += 8) {
                    uint32_t a = (p1 >> c) & 255u, b = (p2 >> c) & 255u;
                    want |= ((a * 0x7Fu + b * (255u - 0x7Fu) + 127u) / 255u) << c;
                }
            }
            g_cmp.disp_px++;
            if (((D[Y * W + X] ^ want) & 0xFFFFFFu) == 0) {
                g_cmp.disp_exact++;
            } else {
                if (g_cmp.disp_bad < 8)
                    fprintf(stderr, "  [af_upscaled] (%u,%u): gpu %08X want %08X\n", X, Y, D[Y * W + X], want);
                g_cmp.disp_bad++;
            }
        }
    /* the check is armed: one internal row vs one native row differ */
    if (detail < 1000) {
        fprintf(stderr, "  [af_upscaled] only %llu sub-row details: scene not armed\n",
                (unsigned long long)detail);
        g_cmp.disp_bad++;
    }
    printf("af_upscaled: x%d, %llu output pixels where a native-row offset would differ\n", s,
           (unsigned long long)detail);
    af_close(&d);
}

/* split pages (docs/GPU.md "Performance", checkpoint 3): host->local
 * transfers into pages a target drew are merged into the mirror on the GPU
 * instead of read back.  Partial-word formats over drawn pages (CT24 keeps
 * byte 3, T4HH one nibble of it, T4 nibbles over a drawn Z buffer), a
 * page-aligned CT32 upload (whole pages), an abandoned transfer, and a
 * transfer whose pages a CLUT load reads while it is still open (between its
 * two packets: merged and read back); then draws over and sampling of the
 * results, read-backs and the final memory. */
static void upload_open(dual *d, uint32_t dbp, uint32_t dbw, uint32_t dpsm, uint32_t x, uint32_t y,
                        uint32_t w, uint32_t h)
{
    flush(d);
    qw(4 | (1ull << 60), 0xE);
    qw(((uint64_t)dbp << 32) | ((uint64_t)dbw << 48) | ((uint64_t)dpsm << 56), GS_BITBLTBUF);
    qw(((uint64_t)x << 32) | ((uint64_t)y << 48), GS_TRXPOS);
    qw(w | ((uint64_t)h << 32), GS_TRXREG);
    qw(0, GS_TRXDIR);
    send(d);
}
static void upload_qwords(dual *d, uint32_t nq)
{
    qw((uint64_t)nq | (1ull << 15) | (2ull << 58), 0);
    for (uint32_t i = 0; i < nq; i++) qw(((uint64_t)rnd() << 32) | rnd(), ((uint64_t)rnd() << 32) | rnd());
    send(d);
}

static int g_split_zbuf0;   /* debugging: leave ZBUF_2 at 0 (Z32 on the frame's pages) */
static void scene_split(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
    ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    for (int i = 0; i < 40; i++) {
        int x = (int)(rnd() % 230), y = (int)(rnd() % 100);
        sprite(&d, 0, x, y, x + 26, y + 26, rnd(), rnd() & 0xFFFFFF);
    }
    flush(&d);
    /* partial words over drawn pages */
    upload_random(&d, 0, 4, GS_PSMCT24, 37, 19);
    upload_open(&d, 0, 4, GS_PSMT4HH, 64, 40, 50, 30);
    upload_qwords(&d, (50 * 30 / 2 + 15) / 16);
    upload_open(&d, 32 * 32, 4, GS_PSMT4, 40, 8, 24, 24);   /* Z pages as T4 */
    upload_qwords(&d, (24 * 24 / 2 + 15) / 16);
    /* whole pages: page-aligned CT32 64x32 at (128, 0) */
    upload_open(&d, 0, 4, GS_PSMCT32, 128, 0, 64, 32);
    upload_qwords(&d, 64 * 32 * 4 / 16);
    /* abandoned after a third of its data */
    upload_open(&d, 0, 4, GS_PSMCT16, 16, 70, 40, 30);
    upload_qwords(&d, 40 * 30 * 2 / 16 / 3);
    ad(&d, GS_TRXDIR, 3);
    /* more drawing over the split pages, depth-tested against the T4 bytes */
    for (int i = 0; i < 20; i++) {
        int x = (int)(rnd() % 230), y = (int)(rnd() % 100);
        sprite(&d, PRIM_ABE, x, y, x + 20, y + 20, rnd(), rnd() & 0xFFFFFF);
    }
    flush(&d);
    /* a transfer still open when its pages are sampled */
    upload_random(&d, 0, 4, GS_PSMCT32, 8, 8);   /* (new split pages at 0,0) */
    upload_random(&d, 64 * 32, 2, GS_PSMT8, 128, 64);
    upload_open(&d, 0, 4, GS_PSMCT24, 0, 64, 120, 40);
    upload_qwords(&d, 120 * 20 * 3 / 16);
    /* a CLUT load (CT32, CSM1 16x16 at block 256 = page 8, rows 64-95 of
    * the frame) reads the half-written pages: merge and read back now */
    ad(&d, GS_TEX0_1, r_tex0(64 * 32, 2, GS_PSMT8, 7, 6, 1, 1, 256, GS_PSMCT32, 0, 0, 1));
    flush(&d);
    upload_qwords(&d, 120 * 20 * 3 / 16);
    /* sample the T8 texture through that CLUT, then the frame, draw over
     * them, read back */
    ad(&d, GS_TEX1_1, 0);
    ad(&d, GS_CLAMP_1, 0);
    ad(&d, GS_FRAME_2, r_frame(96, 2, GS_PSMCT32, 0));
    ad(&d, GS_SCISSOR_2, r_scissor(0, 127, 0, 63));
    ad(&d, GS_XYOFFSET_2, 0);
    if (!g_split_zbuf0) ad(&d, GS_ZBUF_2, r_zbuf(32, GS_PSMZ24, 1));
    ad(&d, GS_TEST_2, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    ad(&d, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST | PRIM_CTXT2);
    ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, 1.0f));
    ad(&d, GS_UV, r_uv(8, 8)); ad(&d, GS_XYZ2, r_xyz(0, 0, 0));
    ad(&d, GS_UV, r_uv(128 * 16 + 8, 64 * 16 + 8)); ad(&d, GS_XYZ2, r_xyz(128 * 16, 64 * 16, 0));
    ad(&d, GS_TEX0_1, r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 1, 0, 0, 0, 0, 0));
    ad(&d, GS_SCISSOR_2, r_scissor(0, 127, 0, 127));
    ad(&d, GS_UV, r_uv(8, 8)); ad(&d, GS_XYZ2, r_xyz(0, 64 * 16, 0));
    ad(&d, GS_UV, r_uv(128 * 16 + 8, 128 * 16 + 8)); ad(&d, GS_XYZ2, r_xyz(128 * 16, 128 * 16, 0));
    sprite(&d, PRIM_ABE, 100, 30, 200, 90, 0x60FFFFFFu, 0x123456);
    download_cmp(&d, 0, 4, GS_PSMCT32, 0, 0, 256, 128, "split readback ct32");
    download_cmp(&d, 32 * 32, 4, GS_PSMZ24, 0, 0, 256, 128, "split readback z24");
    download_cmp(&d, 96 * 32, 2, GS_PSMCT32, 0, 0, 128, 128, "split readback sampled");
    d_close(&d, "split");
}

/* The exact-triangle shader's float fast path (docs/GPU.md "Checkpoint 4"):
 * values on and near the integers where the float bound cannot decide and
 * the reference's double rounding does.  The game's half-resolution strips
 * (U on whole 1/16 texels at every pixel, two triangles per 32-pixel strip,
 * depth-tested), 1:1 and 2:1 texel-centre mappings, Gouraud colour and fog
 * stepping by whole units, random sub-pixel UV triangles, STQ with constant
 * Q (affine, S/Q on texel edges) and perspective Q with mipmaps (the LOD's
 * float of Q), triangles reaching far off screen (the double edge
 * functions), Gouraud lines, Z small (float) and near 2^24 (double).  Random
 * textures, so a texel or a 1/16 weight off shows.  gpu.control_floatpath
 * accepts every float value (fault 12) and must fail. */
static void scene_exact_float(gpu_renderer *r)
{
    dual d;
    d_open(&d, r);
    target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
    upload_random(&d, 0, 4, GS_PSMCT32, 256, 128);
    const uint32_t L0 = 64 * 32, L1 = 72 * 32, L2 = 76 * 32;
    upload_random(&d, L0, 2, GS_PSMCT32, 128, 128);
    upload_random(&d, L1, 1, GS_PSMCT32, 64, 64);
    upload_random(&d, L2, 1, GS_PSMCT32, 32, 32);
    ad(&d, GS_TEX0_1, r_tex0(L0, 2, GS_PSMCT32, 7, 7, 1, 0, 0, 0, 0, 0, 0));
    ad(&d, GS_MIPTBP1_1, (uint64_t)L1 | (1ull << 14) | ((uint64_t)L2 << 20) | (1ull << 34));
    ad(&d, GS_CLAMP_1, r_clamp(0, 0, 0, 0, 0, 0));
    ad(&d, GS_ALPHA_1, r_alpha(0, 1, 0, 1, 0));
    for (int filt = 0; filt < 2; filt++) {
        ad(&d, GS_TEX1_1, r_tex1(0, 0, filt, filt, 0, 0));
        /* 1. the strips: two UV triangles per 32-pixel column, U 0 -> 16
         * texels over 32 px (and 32, 64 texels), V scaled, Z 3500..3900 with
         * GEQUAL, flat colour */
        static const int DU[3] = { 256, 512, 1024 };
        for (int k = 0; k < 3; k++) {
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
            for (int c = 0; c < 8; c++) {
                int x0 = c * 32 * 16, x1 = x0 + 32 * 16, y0 = 0, y1 = 128 * 16;
                int u0 = c * DU[k] % 2048, u1 = u0 + DU[k], v0 = 16, v1 = 16 + 111 * 16 + k;
                uint32_t za = 3500 + (uint32_t)(rnd() % 400), zb = 3500 + (uint32_t)(rnd() % 400);
                ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_FST);
                ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, 1.0f));
                ad(&d, GS_UV, r_uv(u0, v0)); ad(&d, GS_XYZ2, r_xyz(x0, y0, za));
                ad(&d, GS_UV, r_uv(u1, v0)); ad(&d, GS_XYZ2, r_xyz(x1, y0, zb));
                ad(&d, GS_UV, r_uv(u0, v1)); ad(&d, GS_XYZ2, r_xyz(x0, y1, za));
                ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_FST);
                ad(&d, GS_UV, r_uv(u0, v1)); ad(&d, GS_XYZ2, r_xyz(x0, y1, za));
                ad(&d, GS_UV, r_uv(u1, v0)); ad(&d, GS_XYZ2, r_xyz(x1, y0, zb));
                ad(&d, GS_UV, r_uv(u1, v1)); ad(&d, GS_XYZ2, r_xyz(x1, y1, zb));
            }
        }
        /* 2. 1:1 texel-centre quads and Gouraud colour stepping by one unit
         * per pixel (blended over the frame: every channel shows) */
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        for (int i = 0; i < 6; i++) {
            int x = (int)(rnd() % 180), y = (int)(rnd() % 80), w = 40 + (int)(rnd() % 30), h = 30;
            int u = (int)(rnd() % 60), v = (int)(rnd() % 60);
            uint32_t c0 = 0x40000000u | (rnd() & 0x3F3F3F), c1 = c0 + (uint32_t)w * 0x010101u;
            ad(&d, GS_PRIM, GS_PRIM_TRISTRIP | PRIM_TME | PRIM_FST | PRIM_IIP | PRIM_ABE);
            ad(&d, GS_RGBAQ, r_rgbaq(c0, 1.0f)); ad(&d, GS_UV, r_uv(u * 16 + 8, v * 16 + 8)); ad(&d, GS_XYZ2, r_xyz(x * 16, y * 16, 0));
            ad(&d, GS_RGBAQ, r_rgbaq(c1, 1.0f)); ad(&d, GS_UV, r_uv((u + w) * 16 + 8, v * 16 + 8)); ad(&d, GS_XYZ2, r_xyz((x + w) * 16, y * 16, 0));
            ad(&d, GS_RGBAQ, r_rgbaq(c0, 1.0f)); ad(&d, GS_UV, r_uv(u * 16 + 8, (v + h) * 16 + 8)); ad(&d, GS_XYZ2, r_xyz(x * 16, (y + h) * 16, 0));
            ad(&d, GS_RGBAQ, r_rgbaq(c1, 1.0f)); ad(&d, GS_UV, r_uv((u + w) * 16 + 8, (v + h) * 16 + 8)); ad(&d, GS_XYZ2, r_xyz((x + w) * 16, (y + h) * 16, 0));
        }
        /* 3. random sub-pixel Gouraud UV triangles */
        for (int i = 0; i < 12; i++) {
            ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_FST | PRIM_IIP);
            for (int k = 0; k < 3; k++) {
                ad(&d, GS_RGBAQ, r_rgbaq(rnd() | 0x80000000u, 1.0f));
                ad(&d, GS_UV, r_uv((int)(rnd() % 2048), (int)(rnd() % 2048)));
                ad(&d, GS_XYZ2, r_xyz((int)(rnd() % (256 * 16)), (int)(rnd() % (128 * 16)), 0));
            }
        }
        /* 4. STQ, Q constant: S/Q on texel edges and centres */
        for (int i = 0; i < 6; i++) {
            int x = (int)(rnd() % 180), y = (int)(rnd() % 80), w = 64;
            float q = (i & 1) ? 1.0f : 0.5f;
            ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_IIP);
            ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, q)); ad(&d, GS_ST, r_st(0.0f * q, 0.25f * q)); ad(&d, GS_XYZ2, r_xyz(x * 16, y * 16, 0));
            ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, q)); ad(&d, GS_ST, r_st(0.5f * q, 0.25f * q)); ad(&d, GS_XYZ2, r_xyz((x + w) * 16, y * 16, 0));
            ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, q)); ad(&d, GS_ST, r_st(0.0f * q, 0.5f * q)); ad(&d, GS_XYZ2, r_xyz(x * 16, (y + 32) * 16, 0));
        }
        /* 5. fog stepping by whole units, Gouraud */
        ad(&d, GS_FOGCOL, 0x305070);
        for (int i = 0; i < 4; i++) {
            int x = (int)(rnd() % 180), y = (int)(rnd() % 80);
            ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_FST | PRIM_IIP | PRIM_FGE);
            ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, 1.0f)); ad(&d, GS_UV, r_uv(8, 8)); ad(&d, GS_XYZF2, r_xyzf(x * 16, y * 16, 0, 10));
            ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, 1.0f)); ad(&d, GS_UV, r_uv(16 * 60 + 8, 8)); ad(&d, GS_XYZF2, r_xyzf((x + 60) * 16, y * 16, 0, 70));
            ad(&d, GS_RGBAQ, r_rgbaq(0x80808080u, 1.0f)); ad(&d, GS_UV, r_uv(8, 16 * 40 + 8)); ad(&d, GS_XYZF2, r_xyzf(x * 16, (y + 40) * 16, 0, 130));
        }
    }
    /* 6. perspective STQ with mipmaps (LOD from Q: the LOD's float of Q
     * stays double), trilinear */
    ad(&d, GS_TEX1_1, r_tex1(0, 2, 1, 5, 0, 0));
    for (int i = 0; i < 10; i++) {
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_IIP);
        for (int k = 0; k < 3; k++) {
            float q = 0.15f + (float)(rnd() % 1000) / 700.0f;
            float s = (float)(rnd() % 1000) / 500.0f * q, t = (float)(rnd() % 1000) / 500.0f * q;
            ad(&d, GS_ST, r_st(s, t));
            ad(&d, GS_RGBAQ, r_rgbaq(rnd() | 0x80000000u, q));
            ad(&d, GS_XYZ2, r_xyz((int)(rnd() % (256 * 16)), (int)(rnd() % (128 * 16)), 0));
        }
    }
    /* 7. triangles far off screen (double edge functions), Gouraud, Z near
     * 2^24 with GEQUAL, and small Z */
    ad(&d, GS_TEX1_1, r_tex1(0, 0, 1, 1, 0, 0));
    ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
    for (int i = 0; i < 8; i++) {
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_FST | PRIM_IIP);
        int cx = 128 * 16, cy = 64 * 16;
        for (int k = 0; k < 3; k++) {
            int ang = (int)(rnd() % 360);
            double a = ang * 3.14159265358979 / 180.0;
            int rad = (i & 1) ? 3000 * 16 : 900 * 16;
            ad(&d, GS_RGBAQ, r_rgbaq(rnd() | 0x80000000u, 1.0f));
            ad(&d, GS_UV, r_uv((int)(rnd() % 2048), (int)(rnd() % 2048)));
            ad(&d, GS_XYZ2, r_xyz(cx + (int)(rad * cos(a)) + (k == 0 ? 0 : 0), cy + (int)(rad * sin(a)),
                                  (i & 2) ? 0xFFF000u + (rnd() % 0xFFF) : 100 + rnd() % 1000));
        }
    }
    /* 8. many triangles on whole pixels with UV, colour and fog changing by
     * whole units per pixel along random directions (values on the
     * integers at most pixels), bilinear and point */
    ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    for (int i = 0; i < 240; i++) {
        ad(&d, GS_TEX1_1, r_tex1(0, 0, i & 1, i & 1, 0, 0));
        int x = (int)(rnd() % 220), y = (int)(rnd() % 100), w = 4 + (int)(rnd() % 36), h = 4 + (int)(rnd() % 28);
        int du = (int)(rnd() % 5) - 2, dv = (int)(rnd() % 5) - 2;   /* 1/16 texels per pixel, times 8 */
        int u = 400 + (int)(rnd() % 1200), v = 400 + (int)(rnd() % 1200);
        int xs[3] = { x, x + w, (i & 2) ? x : x + w }, ys[3] = { y, (i & 4) ? y + h : y, y + h };
        uint32_t c = 0x40404040u | (rnd() & 0x1F1F1F1Fu);
        ad(&d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | PRIM_FST | PRIM_IIP | PRIM_FGE);
        for (int k = 0; k < 3; k++) {
            int dx = xs[k] - x, dy = ys[k] - y;
            ad(&d, GS_RGBAQ, r_rgbaq(c + (uint32_t)(dx + dy) * 0x01010101u, 1.0f));
            ad(&d, GS_UV, r_uv(u + 8 * du * dx + 8 * dv * dy, v + 8 * dv * dx - 8 * du * dy));
            ad(&d, GS_XYZF2, r_xyzf(xs[k] * 16, ys[k] * 16, 0, (uint32_t)(64 + 2 * dx)));
        }
    }
    /* 9. Gouraud lines */
    for (int i = 0; i < 16; i++) {
        ad(&d, GS_PRIM, GS_PRIM_LINE | PRIM_TME | PRIM_FST | PRIM_IIP);
        for (int k = 0; k < 2; k++) {
            ad(&d, GS_RGBAQ, r_rgbaq(rnd() | 0x80000000u, 1.0f));
            ad(&d, GS_UV, r_uv((int)(rnd() % 2048), (int)(rnd() % 2048)));
            ad(&d, GS_XYZ2, r_xyz((int)(rnd() % (256 * 16)), (int)(rnd() % (128 * 16)), rnd() % 0x1000000u));
        }
    }
    d_close(&d, "exact_float");
}

/* FRAME / ZBUF / TEX pages aliasing within a primitive, within a batch and
 * across batches and contexts (docs/GPU.md "Checkpoint 4").
 *
 * Within a primitive the GPU samples memory as it was before the
 * primitive; the reference does the same since checkpoint 4 (gs_raster.c
 * tex_snapshot: the GS's texture buffer does not see the primitive's own
 * writes).  gpu.control_selfread replays this scene with the reference
 * reading memory as it writes it, and must fail. */
static void ctx2_regs(dual *d, uint64_t frame, uint64_t zbuf, uint64_t test, uint64_t tex0, int linear,
                      uint64_t clamp, int w, int h)
{
    ad(d, GS_FRAME_2, frame);
    ad(d, GS_ZBUF_2, zbuf);
    ad(d, GS_TEST_2, test);
    ad(d, GS_SCISSOR_2, r_scissor(0, (uint32_t)w - 1, 0, (uint32_t)h - 1));
    ad(d, GS_XYOFFSET_2, 0);
    ad(d, GS_ALPHA_2, 0x44);
    ad(d, GS_TEX0_2, tex0);
    ad(d, GS_TEX1_2, linear ? 0x60 : 0);
    ad(d, GS_CLAMP_2, clamp);
}

/* a textured triangle, UV (FST) or STQ (q = 1 at every vertex, s/t from
 * texel positions over a W x H texture), with Z */
static void ttri(dual *d, uint32_t prim, int stq, const int xy[6], const int uv[6], int W, int H,
                 uint32_t rgba, uint32_t z)
{
    ad(d, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME | (stq ? 0u : PRIM_FST) | prim);
    for (int k = 0; k < 3; k++) {
        ad(d, GS_RGBAQ, r_rgbaq(rgba, 1.0f));
        if (stq) ad(d, GS_ST, r_st((float)uv[2 * k] / (16.0f * (float)W), (float)uv[2 * k + 1] / (16.0f * (float)H)));
        else ad(d, GS_UV, r_uv(uv[2 * k], uv[2 * k + 1]));
        ad(d, GS_XYZ2, r_xyz(xy[2 * k], xy[2 * k + 1], z));
    }
}

static void scene_alias_pages(gpu_renderer *r)
{
    const uint32_t ZM = 0x1000000u;
    /* 1. the scene that found it: scene.split with context 2's ZBUF left
     * at 0 (Z32 written over the CT32 frame's pages while FRAME_2 draws
     * elsewhere) and TEX0_2 at 0 (a 1x1 CT32 texture whose texel the
     * sprite's own Z write overwrites part-way through the sprite) */
    g_split_zbuf0 = 1;
    scene_split(r);
    g_split_zbuf0 = 0;
    /* 2. context 2 drawing elsewhere with its Z32 buffer on context 1's
     * frame pages, sampling that frame (sprites point/bilinear, UV and STQ
     * triangles), interleaved with context 1 drawing on the frame */
    {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
        upload_random(&d, 0, 4, GS_PSMCT32, 256, 128);
        scribble(&d, 256, 128, 8, ZM);
        for (int lin = 0; lin < 2; lin++) {
            ctx2_regs(&d, r_frame(96, 2, GS_PSMCT32, 0), r_zbuf(0, GS_PSMZ32, 0), r_test(0, 0, 0, 0, 0, 0, 1, 1),
                      r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), lin, r_clamp(1, 1, 0, 0, 0, 0), 128, 128);
            for (int i = 0; i < 6; i++) {
                int x = (int)(rnd() % 100), y = (int)(rnd() % 100), sx = (int)(rnd() % 200), sy = (int)(rnd() % 100);
                tsprite_z(&d, PRIM_CTXT2, x, y, x + 28, y + 28, 8 + 16 * sx, 4 + 16 * sy, 8 + 16 * (sx + 40),
                          4 + 16 * (sy + 20), 0x80808080u, rnd() % ZM);
                sprite(&d, PRIM_ABE, sx, sy, sx + 20, sy + 12, rnd(), rnd() % ZM);   /* context 1 */
            }
            for (int i = 0; i < 6; i++) {
                int x = (int)(rnd() % 90), y = (int)(rnd() % 90);
                int xy[6] = { x * 16 + 3, y * 16 + 5, (x + 37) * 16 + 9, (y + 4) * 16, (x + 6) * 16 + 1, (y + 33) * 16 + 7 };
                int uv[6] = { 16 * 10, 16 * 3, 16 * 200, 16 * 9, 16 * 30, 16 * 120 };
                ttri(&d, PRIM_CTXT2 | PRIM_IIP, i & 1, xy, uv, 256, 128, rnd() | 0x80808080u, rnd() % ZM);
            }
        }
        d_close(&d, "ctx2 z32 on ctx1 frame");
    }
    /* 3. in-place strips: the game's blur (32-pixel strips adding the frame
     * shifted by one or two pixels to itself, reading behind the raster
     * order and ahead of it), point and bilinear, CT32 and CT16 */
    {
        static const uint32_t F[2] = { GS_PSMCT32, GS_PSMCT16 };
        for (int fi = 0; fi < 2; fi++) {
            dual d;
            d_open(&d, r);
            target(&d, 4, F[fi], 32, GS_PSMZ24, 256, 128);
            upload_random(&d, 0, 4, F[fi], 256, 128);
            ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 1));
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 0, 0));
            ad(&d, GS_ALPHA_1, r_alpha(0, 2, 2, 1, 0x30));       /* Cs * FIX + Cd */
            static const int SH[6][2] = { { 1, 0 }, { 0, 1 }, { 2, 0 }, { -1, 0 }, { 0, -2 }, { 1, 1 } };
            for (int lin = 0; lin < 2; lin++)
                for (int k = 0; k < 6; k++) {
                    tex1(&d, r_tex0(0, 4, F[fi], 8, 7, 1, 0, 0, 0, 0, 0, 0), lin, r_clamp(1, 1, 0, 0, 0, 0));
                    for (int x = 0; x < 192; x += 32) {
                        int dx = SH[k][0], dy = SH[k][1], half = lin && k == 5 ? 8 : 0;
                        tsprite(&d, PRIM_ABE, x + (dx > 0 ? dx : 0), dy > 0 ? dy : 0, x + 32, 96,
                                8 + half + 16 * (x + (dx > 0 ? 0 : -dx)), 8 + half + 16 * (dy > 0 ? 0 : -dy),
                                8 + half + 16 * (x + 32 - (dx > 0 ? dx : 0) + (dx > 0 ? 0 : -dx)),
                                8 + half + 16 * (96 - (dy > 0 ? dy : 0) + (dy > 0 ? 0 : -dy)), 0x40404040u);
                    }
                }
            d_close(&d, fi ? "in-place strips ct16" : "in-place strips ct32");
        }
    }
    /* 4. the Z buffer sampled while the same primitives write it: as Z24
     * (its own arrangement) and as CT32 (another arrangement), shifted
     * behind and ahead, the frame elsewhere */
    {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
        upload_random(&d, 32 * 32, 4, GS_PSMZ24, 256, 128);
        scribble(&d, 256, 128, 10, ZM);
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        static const uint32_t T[2] = { GS_PSMZ24, GS_PSMCT32 };
        for (int ti = 0; ti < 2; ti++) {
            tex1(&d, r_tex0(32 * 32, 4, T[ti], 8, 7, 1, 1, 0, 0, 0, 0, 0), ti, r_clamp(1, 1, 0, 0, 0, 0));
            for (int i = 0; i < 8; i++) {
                int x = (int)(rnd() % 190), y = (int)(rnd() % 80), sx = x + (int)(rnd() % 5) - 2, sy = y + (int)(rnd() % 5) - 2;
                if (sx < 0) sx = 0;
                if (sy < 0) sy = 0;
                tsprite_z(&d, 0, x, y, x + 48, y + 40, 8 + 16 * sx, 8 + 16 * sy, 8 + 16 * (sx + 48), 8 + 16 * (sy + 40),
                          0x80808080u, rnd() % ZM);
            }
        }
        d_close(&d, "z sampled while written");
    }
    /* 5. triangles sampling the frame they draw into (UV and STQ, shifted
     * by a pixel), and the CT32 frame read in place as CT16 and T8 (other
     * arrangements of the same pages) */
    {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 32, GS_PSMZ24, 256, 128);
        upload_random(&d, 0, 4, GS_PSMCT32, 256, 128);
        ad(&d, GS_ZBUF_1, r_zbuf(32, GS_PSMZ24, 1));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 0, 0));
        ad(&d, GS_ALPHA_1, r_alpha(0, 2, 2, 1, 0x30));
        tex1(&d, r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), 1, r_clamp(1, 1, 0, 0, 0, 0));
        for (int i = 0; i < 12; i++) {
            int x = 2 + (int)(rnd() % 180), y = 2 + (int)(rnd() % 70);
            int xy[6] = { x * 16, y * 16, (x + 60) * 16 + 5, (y + 3) * 16, (x + 9) * 16 + 11, (y + 50) * 16 + 2 };
            int uv[6] = { (x - 1) * 16 + 8, (y - 1) * 16 + 8, (x + 59) * 16 + 13, (y + 2) * 16 + 8, (x + 8) * 16 + 3, (y + 49) * 16 + 10 };
            ttri(&d, PRIM_ABE | PRIM_IIP, i & 1, xy, uv, 256, 128, 0x40404040u | (rnd() & 0x1F1F1F), 0);
        }
        d_check(&d, "triangles in place");
        static const uint32_t T[2] = { GS_PSMCT16, GS_PSMT8 };
        for (int ti = 0; ti < 2; ti++) {
            uint32_t tw = T[ti] == GS_PSMT8 ? 8 : 8, th = 7;
            if (T[ti] == GS_PSMT8) {
                upload_random(&d, 200 * 32, 1, GS_PSMCT32, 16, 16);   /* palette, then load it */
                ad(&d, GS_TEX0_1, r_tex0(0, 4, GS_PSMT8, tw, th, 1, 0, 200 * 32, GS_PSMCT32, 0, 0, 1));
                ad(&d, GS_TEX1_1, 0);
            } else {
                tex1(&d, r_tex0(0, 4, T[ti], tw, th, 1, 0, 0, 0, 0, 0, 0), 0, r_clamp(1, 1, 0, 0, 0, 0));
            }
            for (int i = 0; i < 6; i++) {
                int x = (int)(rnd() % 180), y = (int)(rnd() % 80);
                tsprite(&d, PRIM_ABE, x, y, x + 64, y + 40, 8 + 16 * (x + 3), 8 + 16 * y, 8 + 16 * (x + 67), 8 + 16 * (y + 40),
                        0x40404040u);
            }
        }
        d_close(&d, "ct32 frame read in place as ct16, t8");
    }
    /* 6. colour and depth targets whose rows overlap while the scissor keeps
     * the draws apart: the colour target grown over the Z buffer's pages
     * (dirty there) before depth-tested drawing, and the other way round */
    {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 16, GS_PSMZ24, 256, 256);   /* Z at page 16 = frame rows 128+ */
        upload_random(&d, 0, 4, GS_PSMCT32, 256, 256);
        ad(&d, GS_ZBUF_1, r_zbuf(16, GS_PSMZ24, 1));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 0, 0));
        scribble(&d, 256, 256, 16, 0);                         /* colour target: 256 rows, dirty */
        for (int round = 0; round < 3; round++) {
            ad(&d, GS_SCISSOR_1, r_scissor(0, 255, 0, 127));
            ad(&d, GS_ZBUF_1, r_zbuf(16, GS_PSMZ24, 0));
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
            scribble(&d, 256, 128, 12, ZM);
            flat_tris(&d, 256, 128, 6, ZM);
            ad(&d, GS_SCISSOR_1, r_scissor(0, 255, 0, 255));
            ad(&d, GS_ZBUF_1, r_zbuf(16, GS_PSMZ24, 1));
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 0, 0));
            for (int i = 0; i < 6; i++) {
                int x = (int)(rnd() % 200), y = 100 + (int)(rnd() % 120);
                sprite(&d, PRIM_ABE, x, y, x + 40, y + 30, rnd(), 0);
            }
        }
        d_check(&d, "colour target over the z pages");
        /* Z target first (Z32 at page 0, 256 rows deep), then a colour
         * target at page 16 (= Z rows 128+) drawing above the Z rows used */
        ad(&d, GS_FRAME_1, r_frame(16, 4, GS_PSMCT32, 0));
        ad(&d, GS_ZBUF_1, r_zbuf(0, GS_PSMZ32, 0));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        ad(&d, GS_SCISSOR_1, r_scissor(0, 255, 0, 255));
        frame1(&d, 64, 4, GS_PSMCT32, 256, 256);              /* Z drawn over 256 rows */
        scribble(&d, 256, 256, 10, ZM);
        for (int round = 0; round < 3; round++) {
            frame1(&d, 16, 4, GS_PSMCT32, 256, 128);         /* colour on Z rows 128-255 */
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
            scribble(&d, 256, 128, 10, ZM);
            frame1(&d, 64, 4, GS_PSMCT32, 256, 256);
            ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
            scribble(&d, 256, 128, 4, ZM);
        }
        d_close(&d, "z target over the colour pages");
    }
    /* 7. two contexts with FRAME and ZBUF swapped (each one's colour buffer
     * is the other's Z buffer), primitives alternating, depth-tested */
    {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 16, GS_PSMZ24, 256, 128);
        upload_random(&d, 0, 4, GS_PSMCT32, 256, 256);
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 2));
        ctx2_regs(&d, r_frame(16, 4, GS_PSMCT32, 0), r_zbuf(0, GS_PSMZ24, 0), r_test(0, 0, 0, 0, 0, 0, 1, 2),
                  r_tex0(0, 4, GS_PSMCT32, 8, 7, 1, 0, 0, 0, 0, 0, 0), 0, r_clamp(1, 1, 0, 0, 0, 0), 256, 128);
        for (int i = 0; i < 24; i++) {
            int x = (int)(rnd() % 200), y = (int)(rnd() % 90);
            sprite(&d, (i & 1) ? PRIM_CTXT2 : 0, x, y, x + 50, y + 36, rnd(), rnd() % ZM);
            if (i % 6 == 5) {
                int xy[6] = { x * 16, y * 16, (x + 40) * 16, (y + 5) * 16, (x + 3) * 16, (y + 30) * 16 };
                int uv[6] = { 16 * 20, 16 * 20, 16 * 90, 16 * 25, 16 * 30, 16 * 70 };
                ttri(&d, (i & 2) ? PRIM_CTXT2 : 0, 0, xy, uv, 256, 128, 0x80808080u, rnd() % ZM);
            }
        }
        d_close(&d, "contexts with frame and z swapped");
    }
    /* 8. a palette uploaded into the last page of a drawn render target
     * (the game's CLUTs at odd blocks next to a 256x256 buffer) and loaded
     * right after: read from gs->vram without a read-back when the upload
     * wrote every bit read (gpu_stats.reads_current), read back when it
     * wrote only part of them (an 8x8 upload, then a 16x16 CLUT load).
     * gpu.control_readcurrent takes split pages as current (fault 14). */
    {
        dual d;
        d_open(&d, r);
        target(&d, 4, GS_PSMCT32, 64, GS_PSMZ24, 256, 256);
        ad(&d, GS_ZBUF_1, r_zbuf(64, GS_PSMZ24, 1));
        ad(&d, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 0, 0));
        upload_random(&d, 80 * 32, 2, GS_PSMT8, 128, 64);   /* the T8 texture */
        uint64_t rc0 = gpu_get_stats(r)->reads_current;
        for (int round = 0; round < 4; round++) {
            scribble(&d, 256, 256, 12, 0);                       /* page 31 drawn */
            uint32_t cbp = 31 * 32 + 4 + 4 * (uint32_t)round;    /* a 16x16 CLUT inside it */
            if (round & 1) {
                uint8_t b[8 * 8 * 4];
                for (int i = 0; i < (int)sizeof b; i++) b[i] = (uint8_t)rnd();
                upload(&d, cbp, 1, GS_PSMCT32, 0, 0, 8, 8, b, sizeof b);
            } else {
                upload_random(&d, cbp, 1, GS_PSMCT32, 16, 16);
            }
            ad(&d, GS_TEX0_1, r_tex0(80 * 32, 2, GS_PSMT8, 7, 6, 1, 1, cbp, GS_PSMCT32, 0, 0, 1));
            ad(&d, GS_TEX1_1, 0);
            ad(&d, GS_CLAMP_1, 0);
            tsprite(&d, 0, 0, 0, 128, 64, 8, 8, 128 * 16 + 8, 64 * 16 + 8, 0x80808080u);
        }
        d_close(&d, "clut in a drawn page");
        if (gpu_get_stats(r)->reads_current == rc0 && r) printf("  [clut in a drawn page] no read served from gs->vram\n");
    }
}

int g_scene_tol = 2;
int g_scene_tol_force = -1;   /* >= 0: every scene compares with this tolerance (controls) */

int run_scene(const char *name, gpu_renderer *r)
{
    /* tol: float attribute interpolation; tol_x: with exact triangles
     * (docs/GPU.md "Exact triangles"; formats keeps 2 for WARP, whose
     * rasterizer covers pixel centres within ~1e-4 px of an edge
     * differently; exact on hardware) */
    static const struct { const char *n; void (*f)(gpu_renderer *); int tol, tol_x; } S[] = {
        { "formats", scene_formats, 2, 0 },
        { "offscreen", scene_offscreen, 2, 0 },
        { "blend_flat", scene_blend_flat, 0, 0 },
        { "ordered", scene_ordered, 2, 0 },
        { "blend_gouraud", scene_blend_gouraud, 2, 0 },
        { "tex_point", scene_tex_point, 0, 0 },
        { "tex_filter", scene_tex_filter, 2, 0 },
        { "pixel_ops", scene_pixel_ops, 0, 0 },
        { "prims", scene_prims, 2, 0 },
        { "coherence", scene_coherence, 0, 0 },
        { "split", scene_split, 0, 0 },
        { "alias_pages", scene_alias_pages, 0, 0 },
        { "exact_float", scene_exact_float, 2, 0 },
        { "display", scene_display, 0, 0 },
        { "frame640", scene_frame640, 2, 0 },
        { "rtt_formats", scene_rtt_formats, 0, 0 },
        { "rtt_depth", scene_rtt_depth, 0, 0 },
        { "rtt_feedback", scene_rtt_feedback, 0, 0 },
        { "rtt_upscaled", scene_rtt_upscaled, 0, 0 },
        { "rtt_alias", scene_rtt_alias, 0, 0 },
        { "rtt_flip", scene_rtt_flip, 0, 0 },
        { "af_upscaled", scene_af_upscaled, 0, 0 },
        { "debug_uv", scene_debug_uv, 0, 0 },
        { "debug_lines", scene_debug_lines, 0, 0 },
        { "debug_tris", scene_debug_tris, 0, 0 },
    };
    for (size_t i = 0; i < sizeof S / sizeof S[0]; i++)
        if (!strcmp(name, S[i].n)) {
            g_cmp_tol = gpu_exact_triangles(r) ? S[i].tol_x : S[i].tol;
            if (g_scene_tol_force >= 0) g_cmp_tol = g_scene_tol_force;
            if (getenv("RG_SCENE_TOL")) g_cmp_tol = atoi(getenv("RG_SCENE_TOL")); /* debugging */
            g_rng = 0x12345678u;
            S[i].f(r);
            return 1;
        }
    return 0;
}
