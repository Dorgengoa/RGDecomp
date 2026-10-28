/* SPDX-License-Identifier: CC0-1.0 */
/* GS feature census (measurement only; docs/PERF-3D.md "GS features"):
 * between gs_features_begin and gs_features_dump every drawing kick is
 * counted by the pipeline state it uses (primitive, shading, texture format
 * / CLUT / filter, blend equation, alpha / destination-alpha / depth tests,
 * frame and Z formats, FBMSK) with its bounding-box pixels, plus local
 * memory traffic (host->local, local->host, local->local transfers) and
 * draws that sample (or take a CLUT from) pages a draw of the range wrote
 * (render to texture).  Off unless gs_features_begin was called; costs
 * nothing then. */
#if defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gs_internal.h"

int gs__feat_on;

/* the state a draw is counted under: the register fields that select the
 * pipeline (masked), compared as raw words; formatted only when dumped */
typedef struct fkey {
    uint32_t type, attr;            /* primitive, PRIM/PRMODE IIP TME FGE ABE FST */
    uint64_t alpha, test, frame, zbuf, tex0, tex1;
} fkey;

typedef struct feat {
    fkey k;
    int used;
    uint64_t prims, px, rtt_prims, rtt_clut;
} feat;

enum { FEAT_MAX = 4096 };   /* a power of two: open addressing */
static feat *g_feat;
static int g_nfeat;
static uint8_t g_drawn[512];        /* pages a draw of the range wrote (frame / Z) */
static uint64_t g_mem[3][2];        /* [xdir] = { transfers, bytes } */

static const char *k_prim[8] = { "point", "line", "linestrip", "tri", "tristrip", "trifan", "sprite", "?" };

static int psm_page_h(int psm)
{
    switch (psm) {
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: return 64;
    case GS_PSMT8: case GS_PSMT8H: return 64;
    case GS_PSMT4: case GS_PSMT4HL: case GS_PSMT4HH: return 128;
    default: return 32;
    }
}

static void mark_target(uint32_t base_page, uint32_t fbw, int psm, uint32_t h)
{
    uint32_t ph = (uint32_t)psm_page_h(psm);
    uint32_t pw = fbw ? fbw : 1;   /* pages per row: 64 px wide CT32; close enough for 16-bit */
    uint32_t n = pw * ((h + ph - 1) / ph);
    for (uint32_t i = 0; i < n && i < 512; i++) g_drawn[(base_page + i) & 511] = 1;
}

static void fmt_key(const fkey *q, char *k, size_t cap)
{
    int tme = (int)GS_BITS(q->attr, 4, 1), fge = (int)GS_BITS(q->attr, 5, 1), abe = (int)GS_BITS(q->attr, 6, 1);
    int fst = (int)GS_BITS(q->attr, 8, 1), iip = (int)GS_BITS(q->attr, 3, 1);
    int fpsm = (int)GS_BITS(q->frame, 24, 6), zpsm = (int)GS_BITS(q->zbuf, 24, 4) | 0x30, zmsk = (int)GS_BITS(q->zbuf, 32, 1);
    uint32_t fbmsk = GS_BITS(q->frame, 32, 32);
    int ate = (int)GS_BITS(q->test, 0, 1), atst = (int)GS_BITS(q->test, 1, 3), afail = (int)GS_BITS(q->test, 12, 2);
    int date = (int)GS_BITS(q->test, 14, 1), datm = (int)GS_BITS(q->test, 15, 1);
    int zte = (int)GS_BITS(q->test, 16, 1), ztst = (int)GS_BITS(q->test, 17, 2);
    char t[96], b[40], at[24];
    t[0] = b[0] = at[0] = 0;
    if (tme) {
        int psm = (int)GS_BITS(q->tex0, 20, 6), cpsm = (int)GS_BITS(q->tex0, 51, 4);
        int indexed = psm == GS_PSMT8 || psm == GS_PSMT4 || psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH;
        snprintf(t, sizeof t, " tex psm%02x%s tfx%u tcc%u mag%u min%u mxl%u lcm%u %s", psm,
                 indexed ? (cpsm == 0 ? " clut32" : " clut16") : "", GS_BITS(q->tex0, 35, 2), GS_BITS(q->tex0, 34, 1),
                 GS_BITS(q->tex1, 5, 1), GS_BITS(q->tex1, 6, 3), GS_BITS(q->tex1, 2, 3), GS_BITS(q->tex1, 0, 1),
                 fst ? "uv" : "stq");
    }
    if (abe) {
        int A = (int)GS_BITS(q->alpha, 0, 2), B = (int)GS_BITS(q->alpha, 2, 2), C = (int)GS_BITS(q->alpha, 4, 2), D = (int)GS_BITS(q->alpha, 6, 2);
        static const char *ab[4] = { "Cs", "Cd", "0", "?" }, *cc[4] = { "As", "Ad", "FIX", "?" };
        if (C == 2) snprintf(b, sizeof b, " blend(%s-%s)*%u+%s", ab[A], ab[B], GS_BITS(q->alpha, 32, 8), ab[D]);
        else snprintf(b, sizeof b, " blend(%s-%s)*%s+%s", ab[A], ab[B], cc[C], ab[D]);
    }
    if (ate) snprintf(at, sizeof at, " atest%d/fail%d", atst, afail);
    snprintf(k, cap, "%s%s%s%s%s fb%02x%s%s%s%s%s", k_prim[q->type & 7], iip ? " gouraud" : " flat", t,
             fge ? " fog" : "", b, fpsm, fbmsk ? " fbmsk" : "", at,
             date ? (datm ? " date1" : " date0") : "",
             zte && ztst != 1 ? (ztst == 2 ? " zge" : (ztst == 3 ? " zgt" : " znever")) : " znotest",
             zmsk ? "" : " zwrite");
    if (!zmsk || (zte && ztst >= 2)) {
        size_t n = strlen(k);
        snprintf(k + n, cap - n, " z%02x", zpsm);
    }
}

static uint64_t g_last_frame = ~0ull, g_last_zbuf = ~0ull;
static uint32_t g_last_sy1 = ~0u;

void gs__feat_prim(gs_state *gs, const gs_vertex *v, int nv, int type)
{
    uint64_t prim = gs->reg[GS_PRIM];
    uint64_t attr = (gs->reg[GS_PRMODECONT] & 1) ? prim : gs->reg[GS_PRMODE];
    int ctx = (int)GS_BITS(attr, 9, 1);
    int tme = (int)GS_BITS(attr, 4, 1), abe = (int)GS_BITS(attr, 6, 1);
    uint64_t frame = gs->reg[GS_FRAME_1 + ctx], zbuf = gs->reg[GS_ZBUF_1 + ctx];
    uint64_t tex0 = gs->reg[GS_TEX0_1 + ctx];
    uint64_t sc = gs->reg[GS_SCISSOR_1 + ctx];
    fkey q;
    memset(&q, 0, sizeof q);
    q.type = (uint32_t)type & 7u;
    q.attr = (uint32_t)(attr & 0x178u);                     /* IIP TME FGE ABE FST */
    if (abe) {
        q.alpha = gs->reg[GS_ALPHA_1 + ctx] & 0xFFull;
        if (GS_BITS(q.alpha, 4, 2) == 2) q.alpha |= gs->reg[GS_ALPHA_1 + ctx] & 0xFF00000000ull;
    }
    q.test = gs->reg[GS_TEST_1 + ctx] & 0x7F00Full;           /* ATE ATST . AFAIL DATE DATM ZTE ZTST; AREF dropped */
    if (!(q.test & 1)) q.test &= ~0x300Eull;
    q.frame = frame & 0xFFFFFFFF3F000000ull;                 /* PSM, FBMSK */
    q.zbuf = zbuf & 0x10F000000ull;                          /* PSM, ZMSK */
    if (tme) {
        q.tex0 = tex0 & 0x0078001C03F00000ull;                /* PSM, TCC, TFX, CPSM */
        q.tex1 = gs->reg[GS_TEX1_1 + ctx] & 0x1FDull;         /* LCM, MXL, MMAG, MMIN */
    }
    int zmsk = (int)GS_BITS(zbuf, 32, 1);
    uint32_t fbmsk = GS_BITS(frame, 32, 32);
    /* bounding box (native pixels) */
    uint64_t xo = gs->reg[GS_XYOFFSET_1 + ctx];
    int ofx = (int)GS_BITS(xo, 0, 16), ofy = (int)GS_BITS(xo, 32, 16);
    int x0 = 1 << 30, y0 = 1 << 30, x1 = -(1 << 30), y1 = -(1 << 30);
    for (int i = 0; i < nv; i++) {
        int x = ((int)v[i].x - ofx) >> 4, y = ((int)v[i].y - ofy) >> 4;
        if (x < x0) x0 = x; if (x > x1) x1 = x;
        if (y < y0) y0 = y; if (y > y1) y1 = y;
    }
    int sx0 = (int)GS_BITS(sc, 0, 11), sx1 = (int)GS_BITS(sc, 16, 11), sy0 = (int)GS_BITS(sc, 32, 11), sy1 = (int)GS_BITS(sc, 48, 11);
    if (x0 < sx0) x0 = sx0; if (x1 > sx1) x1 = sx1;
    if (y0 < sy0) y0 = sy0; if (y1 > sy1) y1 = sy1;
    uint64_t px = x1 >= x0 && y1 >= y0 ? (uint64_t)(x1 - x0 + 1) * (uint64_t)(y1 - y0 + 1) : 0;
    /* render to texture: the texture / CLUT on pages a draw of the range wrote */
    int rtt = tme && g_drawn[(GS_BITS(tex0, 0, 14) >> 5) & 511];
    int rttc = tme && GS_BITS(tex0, 61, 3) && g_drawn[(GS_BITS(tex0, 37, 14) >> 5) & 511];
    if (frame != g_last_frame || zbuf != g_last_zbuf || (uint32_t)sy1 != g_last_sy1) {
        if (fbmsk != 0xFFFFFFFFu) mark_target(GS_BITS(frame, 0, 9), GS_BITS(frame, 16, 6), (int)GS_BITS(frame, 24, 6), (uint32_t)sy1 + 1);
        if (!zmsk) mark_target(GS_BITS(zbuf, 0, 9), GS_BITS(frame, 16, 6), (int)GS_BITS(zbuf, 24, 4) | 0x30, (uint32_t)sy1 + 1);
        g_last_frame = frame;
        g_last_zbuf = zbuf;
        g_last_sy1 = (uint32_t)sy1;
    }
    if (!g_feat) return;
    uint32_t h = 2166136261u;
    const uint8_t *qb = (const uint8_t *)&q;
    for (size_t i = 0; i < sizeof q; i++) h = (h ^ qb[i]) * 16777619u;
    for (uint32_t n = 0; n < FEAT_MAX; n++) {
        feat *f = &g_feat[(h + n) & (FEAT_MAX - 1)];
        if (!f->used) {
            if (g_nfeat >= FEAT_MAX * 3 / 4) return;
            f->used = 1;
            f->k = q;
            g_nfeat++;
        } else if (memcmp(&f->k, &q, sizeof q)) {
            continue;
        }
        f->prims++;
        f->px += px;
        f->rtt_prims += rtt;
        f->rtt_clut += rttc;
        return;
    }
}

void gs__feat_xfer(int xdir, uint64_t bytes, uint32_t dbp, uint32_t dbw, int dpsm, uint32_t y1)
{
    if (xdir < 0 || xdir > 2) return;
    if (xdir != 1) {
        /* written by a transfer: no longer render-target output */
        uint32_t ph = (uint32_t)psm_page_h(dpsm), pw = dbw ? dbw : 1;
        uint32_t n = pw * ((y1 + ph - 1) / ph);
        for (uint32_t i = 0; i < n && i < 512; i++) g_drawn[((dbp >> 5) + i) & 511] = 0;
    }
    g_mem[xdir][0]++;
    g_mem[xdir][1] += bytes;
}

void gs_features_begin(void)
{
    if (!g_feat) g_feat = (feat *)calloc(FEAT_MAX, sizeof *g_feat);
    g_nfeat = 0;
    if (g_feat) memset(g_feat, 0, FEAT_MAX * sizeof *g_feat);
    g_last_frame = g_last_zbuf = ~0ull;
    g_last_sy1 = ~0u;
    memset(g_drawn, 0, sizeof g_drawn);
    memset(g_mem, 0, sizeof g_mem);
    gs__feat_on = g_feat != NULL;
}

int gs_features_dump(const char *path)
{
    FILE *f = fopen(path, "w");
    gs__feat_on = 0;
    if (!f) return -1;
    fprintf(f, "# kind\tprims\tbbox_px\trtt_prims\trtt_clut_prims\tstate\n");
    for (int i = 0; i < FEAT_MAX; i++) {
        char k[200];
        if (!g_feat[i].used) continue;
        fmt_key(&g_feat[i].k, k, sizeof k);
        fprintf(f, "draw\t%llu\t%llu\t%llu\t%llu\t%s\n", (unsigned long long)g_feat[i].prims,
                (unsigned long long)g_feat[i].px, (unsigned long long)g_feat[i].rtt_prims,
                (unsigned long long)g_feat[i].rtt_clut, k);
    }
    static const char *xn[3] = { "host->local", "local->host", "local->local" };
    for (int d = 0; d < 3; d++)
        fprintf(f, "xfer\t%llu\t%llu\t0\t0\t%s\n", (unsigned long long)g_mem[d][0], (unsigned long long)g_mem[d][1], xn[d]);
    fclose(f);
    return 0;
}
