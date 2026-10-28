/* SPDX-License-Identifier: CC0-1.0 */
/* GS input recordings: a snapshot of the model state plus every input the
 * model takes from outside (gs_state.rec, gs.h), replayable through the
 * software rasterizer or any renderer.  docs/GPU.md "Real game validation".
 *
 * The snapshot is written field by field (no structs with pointers), little
 * endian, in the order below; gs_vertex is plain data and is written as
 * stored (recordings are read back by the same build). */
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdlib.h>
#include <string.h>

#include "gs_internal.h"

static const char k_magic[8] = { 'R', 'G', 'G', 'S', 'R', 'E', 'C', '1' };

static void w32(FILE *f, uint32_t v) { fwrite(&v, 4, 1, f); }
static void w64(FILE *f, uint64_t v) { fwrite(&v, 8, 1, f); }

int gs_rec_snapshot(FILE *f, const gs_state *gs)
{
    gs_async_drain((gs_state *)gs);
    gs_mem_materialize((gs_state *)gs, NULL, 1);   /* (lazy transfers) */
    fwrite(k_magic, 1, 8, f);
    w32(f, (uint32_t)sizeof(gs_vertex));
    fwrite(gs->reg, 8, 128, f);
    fwrite(gs->preg, 8, 32, f);
    w32(f, gs->csr_events);
    w32(f, gs->csr_field);
    fwrite(&gs->internal_q, 4, 1, f);
    fwrite(gs->vq, sizeof(gs_vertex), 3, f);
    w32(f, (uint32_t)gs->vq_n);
    w32(f, (uint32_t)gs->strip_n);
    fwrite(gs->clut, 2, 512, f);
    w32(f, gs->cbp0);
    w32(f, gs->cbp1);
    w32(f, (uint32_t)gs->xfer_dir);
    w32(f, gs->xfer_x);
    w32(f, gs->xfer_y);
    fwrite(gs->xfer_carry, 1, 8, f);
    w32(f, gs->xfer_carry_n);
    w32(f, gs->rb_len - gs->rb_off);
    fwrite(gs->rb + gs->rb_off, 1, gs->rb_len - gs->rb_off, f);
    for (int p = 1; p <= 3; p++) {
        const gs_gif_path *g = &gs->path[p];
        w32(f, (uint32_t)g->in_tag);
        w32(f, (uint32_t)g->in_packet);
        w32(f, g->nloop);
        w32(f, g->nreg);
        w32(f, g->flg);
        w32(f, g->eop);
        w64(f, g->regs);
        w32(f, g->reg_i);
        w32(f, g->q_len - g->q_off);
        fwrite(g->q + g->q_off, 1, g->q_len - g->q_off, f);
    }
    w32(f, (uint32_t)gs->bus_owner);
    fwrite(&gs->hooks.xfer_rect, sizeof gs->hooks.xfer_rect, 1, f);
    w32(f, (uint32_t)gs->hooks.xfer_open);
    fwrite(gs->vram, 1, GS_VRAM_BYTES, f);
    return ferror(f) ? -1 : 0;
}

void gs_rec_event(FILE *f, int kind, uint32_t a, uint64_t v, const void *data, uint32_t bytes)
{
    w32(f, (uint32_t)kind);
    w32(f, a);
    w64(f, v);
    w32(f, bytes);
    if (bytes) fwrite(data, 1, bytes, f);
}

int gs_rec_open(gs_rec_file *rf, const char *path)
{
    memset(rf, 0, sizeof *rf);
    FILE *f = fopen(path, "rb");
    if (!f) return -1;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n < 16) { fclose(f); return -1; }
    rf->buf = (uint8_t *)malloc((size_t)n);
    if (!rf->buf || fread(rf->buf, 1, (size_t)n, f) != (size_t)n) {
        fclose(f);
        gs_rec_close(rf);
        return -1;
    }
    fclose(f);
    rf->len = (size_t)n;
    if (memcmp(rf->buf, k_magic, 8) != 0) { gs_rec_close(rf); return -1; }
    return 0;
}

void gs_rec_close(gs_rec_file *rf)
{
    free(rf->buf);
    memset(rf, 0, sizeof *rf);
}

/* bounded reader over the file image */
typedef struct rd { const uint8_t *p; size_t n, o; int bad; } rd;
static void rbytes(rd *r, void *dst, size_t k)
{
    if (r->bad || r->o + k > r->n) { r->bad = 1; memset(dst, 0, k); return; }
    memcpy(dst, r->p + r->o, k);
    r->o += k;
}
static uint32_t r32(rd *r) { uint32_t v; rbytes(r, &v, 4); return v; }
static uint64_t r64(rd *r) { uint64_t v; rbytes(r, &v, 8); return v; }

static uint8_t *grow(uint8_t *p, uint32_t *cap, uint32_t need)
{
    if (need <= *cap) return p;
    uint32_t nc = *cap ? *cap : 4096;
    while (nc < need) nc *= 2;
    uint8_t *q = (uint8_t *)realloc(p, nc);
    if (q) *cap = nc;
    return q;
}

int gs_rec_load(gs_rec_file *rf, gs_state *gs)
{
    rd r = { rf->buf, rf->len, 8, 0 };
    if (r32(&r) != (uint32_t)sizeof(gs_vertex)) return -1;
    rbytes(&r, gs->reg, 8 * 128);
    rbytes(&r, gs->preg, 8 * 32);
    gs->csr_events = r32(&r);
    gs->csr_field = r32(&r);
    rbytes(&r, &gs->internal_q, 4);
    rbytes(&r, gs->vq, sizeof(gs_vertex) * 3);
    gs->vq_n = (int)r32(&r);
    gs->strip_n = (int)r32(&r);
    rbytes(&r, gs->clut, 2 * 512);
    gs->cbp0 = r32(&r);
    gs->cbp1 = r32(&r);
    gs->xfer_dir = (int)r32(&r);
    gs->xfer_x = r32(&r);
    gs->xfer_y = r32(&r);
    rbytes(&r, gs->xfer_carry, 8);
    gs->xfer_carry_n = r32(&r);
    uint32_t n = r32(&r);
    gs->rb = grow(gs->rb, &gs->rb_cap, n);
    if (n && !gs->rb) return -1;
    rbytes(&r, gs->rb, n);
    gs->rb_off = 0;
    gs->rb_len = n;
    for (int p = 1; p <= 3; p++) {
        gs_gif_path *g = &gs->path[p];
        g->in_tag = (int)r32(&r);
        g->in_packet = (int)r32(&r);
        g->nloop = r32(&r);
        g->nreg = r32(&r);
        g->flg = r32(&r);
        g->eop = r32(&r);
        g->regs = r64(&r);
        g->reg_i = r32(&r);
        n = r32(&r);
        g->q = grow(g->q, &g->q_cap, n);
        if (n && !g->q) return -1;
        rbytes(&r, g->q, n);
        g->q_off = 0;
        g->q_len = n;
    }
    gs->bus_owner = (int)r32(&r);
    rbytes(&r, &gs->hooks.xfer_rect, sizeof gs->hooks.xfer_rect);
    gs->hooks.xfer_open = (int)r32(&r);
    rbytes(&r, gs->vram, GS_VRAM_BYTES);
    if (r.bad) return -1;
    rf->events_off = rf->off = r.o;
    return 0;
}

int gs_rec_next(gs_rec_file *rf, gs_rec_ev *ev)
{
    if (rf->off == rf->len) return 0;
    rd r = { rf->buf, rf->len, rf->off, 0 };
    ev->kind = (int)r32(&r);
    ev->a = r32(&r);
    ev->v = r64(&r);
    ev->bytes = r32(&r);
    if (r.bad || r.o + ev->bytes > r.n) return -1;
    ev->data = rf->buf + r.o;
    rf->off = r.o + ev->bytes;
    return 1;
}

uint32_t gs_rec_apply(gs_state *gs, const gs_rec_ev *ev, uint8_t *fifo_out)
{
    switch (ev->kind) {
    case GS_REC_GIF: gs_gif_write(gs, (int)ev->a, ev->data, ev->bytes / 16u); break;
    case GS_REC_PRIV: gs_write_priv(gs, ev->a, ev->v); break;
    case GS_REC_VSYNC: gs_vsync(gs); break;
    case GS_REC_GIF_RESET: gs_gif_reset(gs); break;
    case GS_REC_FIFO_READ: return gs_read_fifo(gs, fifo_out, ev->a);
    default: break;
    }
    return 0;
}
