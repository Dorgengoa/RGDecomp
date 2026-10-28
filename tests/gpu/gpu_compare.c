/* SPDX-License-Identifier: CC0-1.0 */
/* SW reference vs GPU renderer comparison (gpu_compare.h). */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu_compare.h"

cmp_stats g_cmp;
int g_cmp_tol = 2;
int g_cmp_ppm = 0;
int g_cmp_disp_ppm = 0;
int (*g_cmp_excuse)(int psm, uint32_t x, uint32_t y);
static uint8_t g_covered[GS_VRAM_BYTES];
static int g_msgs;

void cmp_reset(void)
{
    memset(&g_cmp, 0, sizeof g_cmp);
    g_msgs = 0;
}

static int is16(int psm)
{
    return psm == GS_PSMCT16 || psm == GS_PSMCT16S || psm == GS_PSMZ16 || psm == GS_PSMZ16S;
}
static int isz(int psm) { return (psm & 0x30) == 0x30; }

static void note(const char *where, const char *fmt, ...)
{
    if (g_msgs++ >= (getenv("RG_CMP_NOTES") ? atoi(getenv("RG_CMP_NOTES")) : 12)) return;
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "  [%s] ", where);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
}

void cmp_vram(const gs_state *sw, const gs_state *hw, gpu_renderer *r, const char *where)
{
    gpu_target_info t[64];
    int nt = gpu_targets(r, t, 64);
    if (nt > 64) nt = 64;
    memset(g_covered, 0, sizeof g_covered);
    g_cmp.checkpoints++;
    for (int i = 0; i < nt; i++) {
        int psm = t[i].psm;
        int bytes = (psm == GS_PSMCT24 || psm == GS_PSMZ24) ? 3 : (is16(psm) ? 2 : 4);
        for (uint32_t y = 0; y < t[i].h; y++)
            for (uint32_t x = 0; x < t[i].w; x++) {
                uint32_t a = gs_pixel_addr(psm, t[i].bp, t[i].bw, x, y, NULL);
                int seen = 1;
                for (int b = 0; b < bytes; b++) if (!g_covered[(a + b) & (GS_VRAM_BYTES - 1)]) seen = 0;
                if (seen) continue;   /* overlapping targets: compared once */
                for (int b = 0; b < bytes; b++) g_covered[(a + b) & (GS_VRAM_BYTES - 1)] = 1;
                uint32_t vs = gs_read_pixel(sw, psm, t[i].bp, t[i].bw, x, y);
                uint32_t vh = gs_read_pixel(hw, psm, t[i].bp, t[i].bw, x, y);
                g_cmp.px++;
                if (vs == vh) { g_cmp.px_exact++; continue; }
                int diff = 0, bad = 0;
                if (isz(psm)) {
                    uint32_t dz = vs > vh ? vs - vh : vh - vs;
                    uint32_t tz = g_cmp_tol ? 2u + (vs >> 20) : 0u;   /* float32 interpolation */
                    diff = dz > 0x7FFFFFFF ? 0x7FFFFFFF : (int)dz;
                    bad = dz > tz;
                } else if (is16(psm)) {
                    for (int c = 0; c < 3; c++) {
                        int d = abs((int)((vs >> (5 * c)) & 31u) - (int)((vh >> (5 * c)) & 31u)) * 8;
                        if (d > diff) diff = d;
                    }
                    if ((vs ^ vh) & 0x8000u) diff = 255;
                    bad = diff > (g_cmp_tol ? ((g_cmp_tol + 7) / 8) * 8 : 0);
                } else {
                    int nch = psm == GS_PSMCT24 ? 3 : 4;
                    for (int c = 0; c < nch; c++) {
                        int d = abs((int)((vs >> (8 * c)) & 255u) - (int)((vh >> (8 * c)) & 255u));
                        if (d > diff) diff = d;
                    }
                    bad = diff > g_cmp_tol;
                }
                if (diff > g_cmp.max_diff) g_cmp.max_diff = diff;
                if (bad && g_cmp_excuse && g_cmp_excuse(psm, x, y)) {
                    g_cmp.px_excused++;
                    bad = 0;
                }
                if (bad) {
                    g_cmp.px_bad++;
                    note(where, "psm %02X bp %u (%u,%u): sw %08X gpu %08X", (unsigned)psm, (unsigned)t[i].bp, x, y,
                         vs, vh);
                }
            }
    }
    for (uint32_t a = 0; a < GS_VRAM_BYTES; a++) {
        if (g_covered[a]) continue;
        if (sw->vram[a] != hw->vram[a]) {
            g_cmp.raw_bad++;
            note(where, "raw byte %06X: sw %02X gpu %02X", a, sw->vram[a], hw->vram[a]);
        }
    }
}

void cmp_frame(const uint32_t *a, const uint32_t *b, uint32_t w, uint32_t h, const char *where)
{
    for (uint32_t i = 0; i < w * h; i++) {
        g_cmp.disp_px++;
        if (a[i] == b[i]) { g_cmp.disp_exact++; continue; }
        int diff = 0;
        for (int c = 0; c < 4; c++) {
            int d = abs((int)((a[i] >> (8 * c)) & 255u) - (int)((b[i] >> (8 * c)) & 255u));
            if (d > diff) diff = d;
        }
        if (diff > g_cmp.disp_max) g_cmp.disp_max = diff;
        if (diff > g_cmp_tol) {
            g_cmp.disp_bad++;
            note(where, "display (%u,%u): sw %08X gpu %08X", i % w, i / w, a[i], b[i]);
        }
    }
}

void cmp_fifo(const uint8_t *a, const uint8_t *b, uint32_t n, const char *where)
{
    for (uint32_t i = 0; i < n; i++) {
        g_cmp.fifo_bytes++;
        if (a[i] != b[i]) {
            g_cmp.fifo_bad++;
            note(where, "fifo byte %u: sw %02X gpu %02X", i, a[i], b[i]);
        }
    }
}

int cmp_report(const char *name)
{
    const cmp_stats *s = &g_cmp;
    double ex = s->px ? 100.0 * (double)s->px_exact / (double)s->px : 100.0;
    double dex = s->disp_px ? 100.0 * (double)s->disp_exact / (double)s->disp_px : 100.0;
    printf("%s: tol %d | checkpoints %d | target px %llu, exact %.3f%%, beyond tol %llu (allowed %d ppm), excused %llu, max diff %d"
           " | other bytes differing %llu | fifo %llu B, %llu bad | display px %llu, exact %.3f%%,"
           " beyond tol %llu, max diff %d\n",
           name, g_cmp_tol, s->checkpoints, (unsigned long long)s->px, ex,
           (unsigned long long)s->px_bad, g_cmp_ppm, (unsigned long long)s->px_excused, s->max_diff, (unsigned long long)s->raw_bad,
           (unsigned long long)s->fifo_bytes, (unsigned long long)s->fifo_bad,
           (unsigned long long)s->disp_px, dex, (unsigned long long)s->disp_bad, s->disp_max);
    int px_fail = s->px_bad && (double)s->px_bad * 1e6 > (double)g_cmp_ppm * (double)s->px;
    int disp_fail = s->disp_bad && (double)s->disp_bad * 1e6 > (double)g_cmp_disp_ppm * (double)s->disp_px;
    return (px_fail || s->raw_bad || s->fifo_bad || disp_fail) ? 1 : 0;
}
