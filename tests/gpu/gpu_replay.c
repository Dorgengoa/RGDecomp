/* SPDX-License-Identifier: CC0-1.0 */
/* Replay of a GS input recording (gs.h "recordings", RG_GS_REC in
 * src/runtime) through the software reference and the GPU renderer, in
 * lockstep: every local->host read (FIFO) is compared byte for byte, the
 * display after every VSync, and local memory at the end.  docs/GPU.md
 * "Real game validation".
 *
 *   rg-gpu-tests replay FILE          (scaleN.replay FILE: internal res xN)
 *   rg-gpu-tests replay-all DIR       every *.rggs in DIR (skips if none)
 *
 * RG_REPLAY_BISECT=1: after every event, sync and compare local memory
 * exactly; stop at the first event that makes them differ and describe it
 * (debugging aid, slow). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu_compare.h"
#include "gpu_tests.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <dirent.h>
#endif

static void describe_gif(const gs_rec_ev *ev)
{
    /* the GIFtags of a GS_REC_GIF event, and its A+D register writes */
    uint32_t nq = ev->bytes / 16, i = 0;
    while (i < nq) {
        const uint8_t *q = ev->data + i * 16;
        uint64_t lo, hi;
        memcpy(&lo, q, 8);
        memcpy(&hi, q + 8, 8);
        uint32_t nloop = (uint32_t)(lo & 0x7FFF), flg = (uint32_t)((lo >> 58) & 3);
        uint32_t nreg = (uint32_t)((lo >> 60) & 15);
        if (!nreg) nreg = 16;
        fprintf(stderr, "    tag @%u: nloop %u flg %u nreg %u prim %s%03llX regs %016llX\n", i, nloop,
                flg, nreg, ((lo >> 46) & 1) ? "" : "(no) ", (unsigned long long)((lo >> 47) & 0x7FF),
                (unsigned long long)hi);
        i++;
        uint32_t data = flg == 0 ? nloop * nreg : (flg == 1 ? (nloop * nreg + 1) / 2 : nloop);
        if (flg == 0)
            for (uint32_t k = 0; k < data && i + k < nq && k < 64; k++) {
                const uint8_t *d = ev->data + (i + k) * 16;
                uint32_t desc = (uint32_t)((hi >> (4 * (k % nreg))) & 15);
                uint64_t a, b;
                memcpy(&a, d, 8);
                memcpy(&b, d + 8, 8);
                if (desc == 0xE)
                    fprintf(stderr, "      A+D reg %02X = %016llX\n", (unsigned)(b & 0xFF),
                            (unsigned long long)a);
                else
                    fprintf(stderr, "      desc %X: %016llX %016llX\n", desc, (unsigned long long)a,
                            (unsigned long long)b);
            }
        i += data;
    }
}

static int bisect_check(gs_state *sw, gs_state *hw, gpu_renderer *r, uint64_t idx,
                        const gs_rec_ev *ev, int field)
{
    gpu_sync(r);
    if (memcmp(sw->vram, hw->vram, GS_VRAM_BYTES) == 0) return 0;
    uint32_t first = 0, last = 0, n = 0;
    for (uint32_t a = 0; a < GS_VRAM_BYTES; a++)
        if (sw->vram[a] != hw->vram[a]) {
            if (!n) first = a;
            last = a;
            n++;
        }
    fprintf(stderr, "replay: local memory first differs after event %llu (kind %d, field %d): %u bytes, "
            "%06X..%06X\n", (unsigned long long)idx, ev->kind, field, n, first, last);
    for (uint32_t a = first, k = 0; a <= last && k < 8; a++)
        if (sw->vram[a] != hw->vram[a]) {
            fprintf(stderr, "  byte %06X: sw %02X gpu %02X\n", a, sw->vram[a], hw->vram[a]);
            k++;
        }
    for (int i = 0; i < 128; i++)
        if (sw->reg[i]) fprintf(stderr, "  reg %02X = %016llX\n", i, (unsigned long long)sw->reg[i]);
    if (ev->kind == GS_REC_GIF) describe_gif(ev);
    return 1;
}

/* Box-filter an upscaled RGBA8 frame to native (truncated mean). */
static void downsample(const uint32_t *in, uint32_t w, uint32_t h, int s, uint32_t *out)
{
    for (uint32_t y = 0; y < h; y++)
        for (uint32_t x = 0; x < w; x++) {
            uint32_t acc[4] = { 0, 0, 0, 0 };
            for (int j = 0; j < s; j++)
                for (int i = 0; i < s; i++) {
                    uint32_t c = in[(y * s + j) * w * s + x * s + i];
                    for (int k = 0; k < 4; k++) acc[k] += (c >> (8 * k)) & 255u;
                }
            uint32_t o = 0;
            for (int k = 0; k < 4; k++) o |= (acc[k] / (uint32_t)(s * s)) << (8 * k);
            out[y * w + x] = o;
        }
}

/* gfx.replay-all: the display is read through the post chain (the Original
 * preset's must be the identity: gpu_read_output == gpu_read_display) */
const gpu_post *g_replay_post = NULL;

int run_replay(const char *path, gpu_renderer *r)
{
    gs_rec_file rf;
    if (gs_rec_open(&rf, path) != 0) {
        fprintf(stderr, "replay: %s: not a GS recording\n", path);
        return -1;
    }
    gs_state *sw = gs_create(), *hw = gs_create();
    if (gs_rec_load(&rf, sw) != 0 || gs_rec_load(&rf, hw) != 0) {
        fprintf(stderr, "replay: %s: bad snapshot\n", path);
        gs_rec_close(&rf);
        return -1;
    }
    gpu_attach(r, hw);
    int s = gpu_get_scale(r);
    int bisect = getenv("RG_REPLAY_BISECT") != NULL;
    static uint8_t fa[1 << 20], fb[1 << 20];
    uint32_t *da = (uint32_t *)malloc(1024u * 1024u * 4u);
    uint32_t *db = (uint32_t *)malloc(1024u * 1024u * 4u * (uint32_t)(s * s));
    uint32_t *dn = (uint32_t *)malloc(1024u * 1024u * 4u);
    gs_rec_ev ev;
    uint64_t idx = 0, gif_bytes = 0;
    int fields = 0, rc;
    /* GPUHASH: FNV-1a of every frame the GPU presented (at the internal
     * resolution) and of its local memory at the end, to compare two
     * renderer builds bit for bit where the reference does not apply
     * (scale > 1, enhancements; docs/PERF-3D.md) */
    uint64_t gh = 1469598103934665603ull;
    while ((rc = gs_rec_next(&rf, &ev)) == 1) {
        uint32_t na = 0, nb = 0;
        if (ev.kind == GS_REC_FIFO_READ && ev.a > sizeof fa) ev.a = sizeof fa;
        na = gs_rec_apply(sw, &ev, fa);
        nb = gs_rec_apply(hw, &ev, fb);
        if (ev.kind == GS_REC_GIF) gif_bytes += ev.bytes;
        if (ev.kind == GS_REC_FIFO_READ) {
            if (na != nb) {
                fprintf(stderr, "replay: FIFO read %llu: %u vs %u bytes\n", (unsigned long long)idx, na, nb);
                g_cmp.fifo_bad++;
            }
            cmp_fifo(fa, fb, na < nb ? na : nb, "fifo");
        }
        if (ev.kind == GS_REC_VSYNC) {
            fields++;
            uint32_t w0 = 0, h0 = 0, w1 = 0, h1 = 0;
            int ra = gs_read_display(sw, GS_READ_FRAME, da, 1024u * 1024u, &w0, &h0);
            int rb = g_replay_post
                         ? gpu_read_output(r, GS_READ_FRAME, g_replay_post, db, 1024u * 1024u * (uint32_t)(s * s), &w1, &h1)
                         : gpu_read_display(r, GS_READ_FRAME, db, 1024u * 1024u * (uint32_t)(s * s), &w1, &h1);
            if (rb == 0) {
                const uint8_t *hp = (const uint8_t *)db;
                for (size_t q = 0; q < (size_t)w1 * h1 * 4; q++) gh = (gh ^ hp[q]) * 1099511628211ull;
            }
            if (ra == 0 && rb == 0 && w1 == w0 * (uint32_t)s && h1 == h0 * (uint32_t)s) {
                if (s > 1) downsample(db, w0, h0, s, dn);
                char where[32];
                snprintf(where, sizeof where, "display f%d", fields);
                cmp_frame(da, s > 1 ? dn : db, w0, h0, where);
                const char *pd = getenv("RG_REPLAY_DUMP");   /* debugging: raw RGBA frames */
                if (pd) {
                    char fn[600];
                    snprintf(fn, sizeof fn, "%s/f%02d_sw_%ux%u.rgba", pd, fields, w0, h0);
                    FILE *f = fopen(fn, "wb");
                    if (f) { fwrite(da, 4, (size_t)w0 * h0, f); fclose(f); }
                    snprintf(fn, sizeof fn, "%s/f%02d_gpu_%ux%u.rgba", pd, fields, w1, h1);
                    f = fopen(fn, "wb");
                    if (f) { fwrite(db, 4, (size_t)w1 * h1, f); fclose(f); }
                }
            } else if (ra != rb) {
                fprintf(stderr, "replay: field %d: display %d vs %d\n", fields, ra, rb);
                g_cmp.raw_bad++;   /* hard failure, not covered by g_cmp_disp_ppm */
            }
        }
        if (bisect && bisect_check(sw, hw, r, idx, &ev, fields)) {
            g_cmp.raw_bad++;
            break;
        }
        idx++;
    }
    if (rc < 0) {
        fprintf(stderr, "replay: %s: truncated after event %llu\n", path, (unsigned long long)idx);
        g_cmp.raw_bad++;
    }
    gpu_sync(r);
    cmp_vram(sw, hw, r, "end");
    for (size_t q = 0; q < GS_VRAM_BYTES; q++) gh = (gh ^ hw->vram[q]) * 1099511628211ull;
    printf("GPUHASH %016llx\n", (unsigned long long)gh);
    printf("replay %s: %llu events, %d fields, %llu KB of GIF data\n", path, (unsigned long long)idx,
           fields, (unsigned long long)(gif_bytes >> 10));
    gpu_detach(r);
    gs_destroy(sw);
    gs_destroy(hw);
    free(da);
    free(db);
    free(dn);
    gs_rec_close(&rf);
    return 0;
}

/* One recording of a directory.  Upscaled 3D (the field-scene recordings,
 * field_*): sub-pixel geometry and Z of an upscaled scene differ from the
 * native reference by design (the write-back sub-sample is off the pixel
 * centre, docs/GPU.md "Upscaling"), so at scale > 1 they are replayed and
 * reported but only their FIFO reads count; scale 1 is exact like every
 * other recording. */
static int replay_one(const char *p, const char *name, gpu_renderer *r)
{
    if (gpu_get_scale(r) <= 1 || strncmp(name, "field_", 6) != 0) return run_replay(p, r);
    cmp_stats keep = g_cmp;
    cmp_reset();
    int rc = run_replay(p, r);
    printf("replay %s (upscaled 3D, report only): target px %llu, exact %.3f%%, beyond tol %llu, "
           "max diff %d | other bytes differing %llu | display exact %.3f%%, max diff %d | "
           "fifo %llu B, %llu bad\n", name, (unsigned long long)g_cmp.px,
           g_cmp.px ? 100.0 * (double)g_cmp.px_exact / (double)g_cmp.px : 100.0,
           (unsigned long long)g_cmp.px_bad, g_cmp.max_diff, (unsigned long long)g_cmp.raw_bad,
           g_cmp.disp_px ? 100.0 * (double)g_cmp.disp_exact / (double)g_cmp.disp_px : 100.0,
           g_cmp.disp_max, (unsigned long long)g_cmp.fifo_bytes, (unsigned long long)g_cmp.fifo_bad);
    uint64_t fb = g_cmp.fifo_bytes, fbad = g_cmp.fifo_bad;
    g_cmp = keep;
    g_cmp.fifo_bytes += fb;
    g_cmp.fifo_bad += fbad;
    return rc;
}

/* Every *.rggs of a directory; returns the number replayed (-1 on error). */
int run_replay_dir(const char *dir, gpu_renderer *r)
{
    int n = 0;
    char p[1024];
#ifdef _WIN32
    WIN32_FIND_DATAA fd;
    snprintf(p, sizeof p, "%s\\*.rggs", dir);
    HANDLE h = FindFirstFileA(p, &fd);
    if (h == INVALID_HANDLE_VALUE) return 0;
    do {
        snprintf(p, sizeof p, "%s/%s", dir, fd.cFileName);
        if (replay_one(p, fd.cFileName, r) != 0) { FindClose(h); return -1; }
        n++;
    } while (FindNextFileA(h, &fd));
    FindClose(h);
#else
    DIR *d = opendir(dir);
    if (!d) return 0;
    struct dirent *e;
    while ((e = readdir(d))) {
        size_t l = strlen(e->d_name);
        if (l < 5 || strcmp(e->d_name + l - 5, ".rggs")) continue;
        snprintf(p, sizeof p, "%s/%s", dir, e->d_name);
        if (replay_one(p, e->d_name, r) != 0) { closedir(d); return -1; }
        n++;
    }
    closedir(d);
#endif
    return n;
}
