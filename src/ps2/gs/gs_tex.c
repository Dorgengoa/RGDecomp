/* SPDX-License-Identifier: CC0-1.0 */
/* GS texturing: CLUT loads (TEX0/TEX2 CLD, CSM1/CSM2, CSA, TEXCLUT),
 * texel fetch for every PSM with TEXA alpha expansion, CLAMP wrap modes,
 * TEX1 LOD and point/bilinear/mipmap filtering.  docs/GS.md "Texturing". */
#include <math.h>

#include "gs_internal.h"

static int psm_indexed(int psm)
{
    return psm == GS_PSMT8 || psm == GS_PSMT8H || psm == GS_PSMT4 ||
           psm == GS_PSMT4HL || psm == GS_PSMT4HH;
}
static int psm_is4(int psm)
{
    return psm == GS_PSMT4 || psm == GS_PSMT4HL || psm == GS_PSMT4HH;
}

/* CLUT load triggered by a TEX0 (or TEX2) write to context ctx (0/1). */
void gs_tex0_written(gs_state *gs, int ctx)
{
    uint64_t t = gs->reg[GS_TEX0_1 + ctx];
    int psm = (int)GS_BITS(t, 20, 6);
    uint32_t cbp = GS_BITS(t, 37, 14);
    int cpsm = (int)GS_BITS(t, 51, 4);
    int csm = (int)GS_BITS(t, 55, 1);
    uint32_t csa = GS_BITS(t, 56, 5);
    int cld = (int)GS_BITS(t, 61, 3);
    int load = 0;

    if (!psm_indexed(psm)) return;
    switch (cld) {
    case 1: load = 1; break;
    case 2: load = 1; gs->cbp0 = cbp; break;
    case 3: load = 1; gs->cbp1 = cbp; break;
    case 4: if (cbp != gs->cbp0) load = 1; gs->cbp0 = cbp; break;
    case 5: if (cbp != gs->cbp1) load = 1; gs->cbp1 = cbp; break;
    default: break;
    }
    if (!load) return;
    gs->stats.clut_loads++;
    if (gs__fx_on) gs__fx_clut(cpsm);

    uint32_t n = psm_is4(psm) ? 16u : 256u;
    int is32 = (cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24);
    uint64_t tc = gs->reg[GS_TEXCLUT];
    uint32_t cbw = GS_BITS(tc, 0, 6), cou = GS_BITS(tc, 6, 6), cov = GS_BITS(tc, 12, 10);
    int rpsm = is32 ? GS_PSMCT32 : cpsm;
    {
        gs_mem_rect r;
        r.bp = cbp; r.psm = rpsm;
        if (csm == 0) { r.bw = 1; r.x = 0; r.y = 0; r.w = n == 256 ? 16 : 8; r.h = n == 256 ? 16 : 2; }
        else { r.bw = cbw; r.x = cou * 16u; r.y = cov; r.w = n; r.h = 1; }
        if (gs->hooks.clut_load && gs->hooks.clut_load(gs->hooks.user, gs, &r, csm, csa, cpsm, n))
            return;   /* loaded by the renderer on the GPU (gs.h hooks.clut_load) */
        gs_mem_materialize_rect(gs, r.psm, r.bp, r.bw, r.x, r.y, r.w, r.h);   /* (lazy transfers) */
        if (gs->hooks.mem) gs->hooks.mem(gs->hooks.user, gs, GS_MEM_READ, &r);
    }

    for (uint32_t i = 0; i < n; i++) {
        uint32_t x, y, bw;
        if (csm == 0) {
            bw = 1; /* CSM1: CLUT buffer is a 64-pixel-wide image */
            if (n == 256) {
                /* entries 8-15 and 16-23 of every 32 are swapped */
                uint32_t p = (i & 0xE7u) | ((i & 8u) << 1) | ((i & 0x10u) >> 1);
                x = p & 15u; y = p >> 4;
            } else {
                x = i & 7u; y = i >> 3;
            }
        } else {
            /* CSM2: one row, offset by TEXCLUT (only 16-bit CPSM is valid) */
            bw = cbw; x = cou * 16u + i; y = cov;
        }
        uint32_t c = gs_read_pixel(gs, rpsm, cbp, bw, x, y);
        if (is32 && csm == 0) {
            uint32_t e = ((csa & 15u) * 16u + i) & 255u;
            gs->clut[e] = (uint16_t)c;
            gs->clut[e + 256] = (uint16_t)(c >> 16);
        } else {
            gs->clut[(csa * 16u + i) & 511u] = (uint16_t)c;
        }
    }
}

static uint32_t expand16(uint32_t c, uint64_t texa)
{
    uint32_t ta0 = GS_BITS(texa, 0, 8), aem = GS_BITS(texa, 15, 1),
             ta1 = GS_BITS(texa, 32, 8);
    uint32_t rgb = ((c & 31u) << 3) | (((c >> 5) & 31u) << 11) | (((c >> 10) & 31u) << 19);
    uint32_t a;
    if (c & 0x8000u) a = ta1;
    else a = (aem && (c & 0x7FFFu) == 0) ? 0u : ta0;
    return rgb | (a << 24);
}

static uint32_t expand24(uint32_t c, uint64_t texa)
{
    uint32_t ta0 = GS_BITS(texa, 0, 8), aem = GS_BITS(texa, 15, 1);
    c &= 0xFFFFFFu;
    return c | ((aem && c == 0) ? 0u : (ta0 << 24));
}

/* texel at integer level coordinates, already wrapped */
static uint32_t fetch(const gs_state *gs, const gs_texctx *tc, uint32_t tbp,
                      uint32_t tbw, int x, int y)
{
    int psm = (int)GS_BITS(tc->tex0, 20, 6);
    uint32_t raw = gs_read_pixel(gs, psm, tbp, tbw, (uint32_t)x, (uint32_t)y);
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32: return raw;
    case GS_PSMCT24: case GS_PSMZ24: return expand24(raw, tc->texa);
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S:
        return expand16(raw, tc->texa);
    default: break;
    }
    /* indexed */
    int cpsm = (int)GS_BITS(tc->tex0, 51, 4);
    uint32_t csa = GS_BITS(tc->tex0, 56, 5);
    if (cpsm == GS_PSMCT32 || cpsm == GS_PSMCT24) {
        uint32_t e = ((csa & 15u) * 16u + raw) & 255u;
        uint32_t c = (uint32_t)gs->clut[e] | ((uint32_t)gs->clut[e + 256] << 16);
        return cpsm == GS_PSMCT24 ? expand24(c, tc->texa) : c;
    }
    return expand16(gs->clut[(csa * 16u + raw) & 511u], tc->texa);
}

/* CLAMP wrap of one integer coordinate.  mode: 0 REPEAT, 1 CLAMP,
 * 2 REGION_CLAMP, 3 REGION_REPEAT.  size is a power of two. */
static int wrap(int c, int mode, int size, int mn, int mx)
{
    switch (mode) {
    case 0: return c & (size - 1);
    case 1: return gs_clampi(c, 0, size - 1);
    case 2: return gs_clampi(c, mn, mx);
    default: return (c & mn) | mx;
    }
}

static void level_geom(const gs_texctx *tc, int k, uint32_t *tbp, uint32_t *tbw)
{
    if (k == 0) {
        *tbp = GS_BITS(tc->tex0, 0, 14);
        *tbw = GS_BITS(tc->tex0, 14, 6);
        return;
    }
    uint64_t m = k <= 3 ? tc->miptbp1 : tc->miptbp2;
    int j = (k - 1) % 3;
    *tbp = GS_BITS(m, j * 20, 14);
    *tbw = GS_BITS(m, j * 20 + 14, 6);
}

static uint32_t sample_level(const gs_state *gs, const gs_texctx *tc, int k,
                             int linear, double u, double v)
{
    int tw = (int)GS_BITS(tc->tex0, 26, 4), th = (int)GS_BITS(tc->tex0, 30, 4);
    if (tw > 10) tw = 10;
    if (th > 10) th = 10;
    int lw = tw - k < 0 ? 0 : tw - k, lh = th - k < 0 ? 0 : th - k;
    int W = 1 << lw, H = 1 << lh;
    int wms = (int)GS_BITS(tc->clamp, 0, 2), wmt = (int)GS_BITS(tc->clamp, 2, 2);
    int minu = (int)GS_BITS(tc->clamp, 4, 10), maxu = (int)GS_BITS(tc->clamp, 14, 10);
    int minv = (int)GS_BITS(tc->clamp, 24, 10), maxv = (int)GS_BITS(tc->clamp, 34, 10);
    if (k > 0 && wms == 2) { minu >>= k; maxu >>= k; }
    if (k > 0 && wmt == 2) { minv >>= k; maxv >>= k; }
    uint32_t tbp, tbw;
    level_geom(tc, k, &tbp, &tbw);
    double sc = 1.0 / (double)(1 << k);
    u *= sc; v *= sc;

    if (!linear) {
        int iu = wrap((int)floor(u), wms, W, minu, maxu);
        int iv = wrap((int)floor(v), wmt, H, minv, maxv);
        return fetch(gs, tc, tbp, tbw, iu, iv);
    }
    u -= 0.5; v -= 0.5;
    double fu0 = floor(u), fv0 = floor(v);
    int iu = (int)fu0, iv = (int)fv0;
    int fu = (int)((u - fu0) * 16.0), fv = (int)((v - fv0) * 16.0);
    int u0 = wrap(iu, wms, W, minu, maxu), u1 = wrap(iu + 1, wms, W, minu, maxu);
    int v0 = wrap(iv, wmt, H, minv, maxv), v1 = wrap(iv + 1, wmt, H, minv, maxv);
    uint32_t c00 = fetch(gs, tc, tbp, tbw, u0, v0), c10 = fetch(gs, tc, tbp, tbw, u1, v0);
    uint32_t c01 = fetch(gs, tc, tbp, tbw, u0, v1), c11 = fetch(gs, tc, tbp, tbw, u1, v1);
    uint32_t out = 0;
    for (int ch = 0; ch < 32; ch += 8) {
        int a = (int)((c00 >> ch) & 255u), b = (int)((c10 >> ch) & 255u);
        int c = (int)((c01 >> ch) & 255u), d = (int)((c11 >> ch) & 255u);
        int r = (a * (16 - fu) * (16 - fv) + b * fu * (16 - fv) +
                 c * (16 - fu) * fv + d * fu * fv) >> 8;
        out |= (uint32_t)r << ch;
    }
    return out;
}

double gs_tex_lod(const gs_texctx *tc, double q)
{
    int lcm = (int)GS_BITS(tc->tex1, 0, 1);
    int l = (int)GS_BITS(tc->tex1, 19, 2);
    int32_t k = (int32_t)(GS_BITS(tc->tex1, 32, 12) << 20) >> 20; /* signed 7.4 */
    double kk = (double)k / 16.0;
    if (lcm) return kk;
    double aq = fabs(q);
    if (aq < 1e-30) aq = 1e-30;
    return log2(1.0 / aq) * (double)(1 << l) + kk;
}

uint32_t gs_tex_sample(const gs_state *gs, const gs_texctx *tc, double u,
                       double v, double lod)
{
    int mxl = (int)GS_BITS(tc->tex1, 2, 3);
    int mmag = (int)GS_BITS(tc->tex1, 5, 1);
    int mmin = (int)GS_BITS(tc->tex1, 6, 3);
    if (mxl > 6) mxl = 6;

    if (lod <= 0.0) return sample_level(gs, tc, 0, mmag, u, v);
    switch (mmin) {
    case 0: return sample_level(gs, tc, 0, 0, u, v);
    case 1: return sample_level(gs, tc, 0, 1, u, v);
    case 2: case 4: {
        int k = (int)floor(lod + 0.5);
        if (k > mxl) k = mxl;
        return sample_level(gs, tc, k, mmin == 4, u, v);
    }
    case 3: case 5: {
        int k = (int)floor(lod);
        int lin = mmin == 5;
        if (k >= mxl) return sample_level(gs, tc, mxl, lin, u, v);
        int f = (int)((lod - (double)k) * 16.0);
        uint32_t a = sample_level(gs, tc, k, lin, u, v);
        uint32_t b = sample_level(gs, tc, k + 1, lin, u, v);
        uint32_t out = 0;
        for (int ch = 0; ch < 32; ch += 8) {
            int x = (int)((a >> ch) & 255u), y = (int)((b >> ch) & 255u);
            out |= (uint32_t)((x * (16 - f) + y * f) >> 4) << ch;
        }
        return out;
    }
    default:
        return sample_level(gs, tc, 0, 0, u, v);
    }
}
