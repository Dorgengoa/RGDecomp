/* SPDX-License-Identifier: CC0-1.0 */
/* The tee behind gpu_tee.h: each gs_state a golden test creates is paired
 * with a shadow gs_state whose drawing goes to the GPU renderer.  Writes go
 * to both; reads compare (gpu_compare.c) and then answer from the software
 * reference, so the test's own hand-written checks still run unchanged. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gpu_compare.h"
#include "gpu_tests.h"

typedef struct tee_ent {
    gs_state *sw, *sh;
    int dirty;
} tee_ent;

static tee_ent g_ent[32];
static gpu_renderer *g_r;
const char *g_tee_name = "golden";

void tee_set_renderer(gpu_renderer *r) { g_r = r; }

static tee_ent *find(const gs_state *sw)
{
    for (int i = 0; i < 32; i++)
        if (g_ent[i].sw == sw) return &g_ent[i];
    return NULL;
}

static void use(tee_ent *e)
{
    if (gpu_attached_state(g_r) != e->sh) gpu_attach(g_r, e->sh);
}

static void checkpoint(tee_ent *e)
{
    if (!e || !e->dirty) return;
    use(e);
    gpu_sync(g_r);
    cmp_vram(e->sw, e->sh, g_r, g_tee_name);
    e->dirty = 0;
}

gs_state *tee_gs_create(void)
{
    for (int i = 0; i < 32; i++) {
        if (g_ent[i].sw) continue;
        g_ent[i].sw = gs_create();
        g_ent[i].sh = gs_create();
        g_ent[i].dirty = 0;
        use(&g_ent[i]);
        return g_ent[i].sw;
    }
    fprintf(stderr, "tee: too many gs_state\n");
    exit(3);
}

void tee_gs_destroy(gs_state *sw)
{
    tee_ent *e = find(sw);
    if (!e) { gs_destroy(sw); return; }
    checkpoint(e);
    if (gpu_attached_state(g_r) == e->sh) gpu_detach(g_r);
    gs_destroy(e->sw);
    gs_destroy(e->sh);
    memset(e, 0, sizeof *e);
}

void tee_gs_reset(gs_state *sw)
{
    tee_ent *e = find(sw);
    gs_reset(sw);
    if (e) { use(e); gs_reset(e->sh); }
}

void tee_gs_gif_write(gs_state *sw, int path, const void *q, uint32_t nqw)
{
    tee_ent *e = find(sw);
    gs_gif_write(sw, path, q, nqw);
    if (e) { use(e); gs_gif_write(e->sh, path, q, nqw); e->dirty = 1; }
}

void tee_gs_vu1_gif_sink(void *user, const uint8_t *data, uint32_t bytes, uint32_t vu_addr)
{
    (void)vu_addr;
    tee_gs_gif_write((gs_state *)user, GS_PATH1, data, bytes / 16u);
}

void tee_gs_vif1_gif_sink(void *user, const uint8_t *data, uint32_t bytes)
{
    tee_gs_gif_write((gs_state *)user, GS_PATH2, data, bytes / 16u);
}

void tee_gs_write_reg(gs_state *sw, uint32_t addr, uint64_t v)
{
    tee_ent *e = find(sw);
    gs_write_reg(sw, addr, v);
    if (e) { use(e); gs_write_reg(e->sh, addr, v); e->dirty = 1; }
}

void tee_gs_write_priv(gs_state *sw, uint32_t a, uint64_t v)
{
    tee_ent *e = find(sw);
    gs_write_priv(sw, a, v);
    if (e) { use(e); gs_write_priv(e->sh, a, v); }
}

void tee_gs_vsync(gs_state *sw)
{
    tee_ent *e = find(sw);
    gs_vsync(sw);
    if (e) { use(e); gs_vsync(e->sh); }
}

void tee_gs_write_pixel(gs_state *sw, int psm, uint32_t bp, uint32_t bw, uint32_t x,
                        uint32_t y, uint32_t v)
{
    tee_ent *e = find(sw);
    gs_write_pixel(sw, psm, bp, bw, x, y, v);
    if (e) {
        use(e);
        gs_mem_rect rc = { bp, bw, psm, x, y, 1, 1 };
        gpu_mem_written(g_r, &rc);   /* flushes and syncs what overlaps first */
        gs_write_pixel(e->sh, psm, bp, bw, x, y, v);
        gpu_mem_written(g_r, &rc);
        e->dirty = 1;
    }
}

uint32_t tee_gs_read_pixel(const gs_state *sw, int psm, uint32_t bp, uint32_t bw,
                           uint32_t x, uint32_t y)
{
    checkpoint(find(sw));
    return gs_read_pixel(sw, psm, bp, bw, x, y);
}

void tee_gs_read_rect_rgba(const gs_state *sw, int psm, uint32_t bp, uint32_t bw,
                           uint32_t x0, uint32_t y0, uint32_t w, uint32_t h, uint32_t *out)
{
    checkpoint(find(sw));
    gs_read_rect_rgba(sw, psm, bp, bw, x0, y0, w, h, out);
}

int tee_gs_read_display(const gs_state *sw, int field, uint32_t *out, uint32_t cap,
                        uint32_t *w, uint32_t *h)
{
    tee_ent *e = find(sw);
    checkpoint(e);
    int rc = gs_read_display(sw, field, out, cap, w, h);
    if (e && rc == 0) {
        use(e);
        uint32_t *tmp = (uint32_t *)malloc((size_t)cap * 4);
        uint32_t w2 = 0, h2 = 0;
        int rc2 = gpu_read_display(g_r, field, tmp, cap, &w2, &h2);
        if (rc2 != 0 || w2 != *w || h2 != *h) {
            fprintf(stderr, "  [%s] display size: sw %ux%u gpu %ux%u rc %d\n", g_tee_name,
                    *w, *h, w2, h2, rc2);
            g_cmp.disp_bad++;
        } else {
            cmp_frame(out, tmp, *w, *h, g_tee_name);
        }
        free(tmp);
    }
    return rc;
}

uint32_t tee_gs_read_fifo(gs_state *sw, void *dst, uint32_t bytes)
{
    tee_ent *e = find(sw);
    uint32_t n = gs_read_fifo(sw, dst, bytes);
    if (e) {
        uint8_t *tmp = (uint8_t *)malloc(bytes ? bytes : 1);
        uint32_t n2 = gs_read_fifo(e->sh, tmp, bytes);
        if (n2 != n) { g_cmp.fifo_bad++; fprintf(stderr, "  fifo length %u vs %u\n", n, n2); }
        cmp_fifo((const uint8_t *)dst, tmp, n < n2 ? n : n2, g_tee_name);
        free(tmp);
    }
    return n;
}
