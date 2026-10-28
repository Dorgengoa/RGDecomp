/* SPDX-License-Identifier: CC0-1.0 */
/* The native GS state block and GIF input (nr_gs.h; docs/NATIVE-RENDER.md "Checkpoint 10").
 * RG_NATIVE_ONLY only: the default build and the oracle twin keep the GS model. */
#include "nr_gs.h"

#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_GPU)

#include <stdlib.h>
#include <string.h>

#include "gpu.h"
#include "nr_gsmem.h"
#include "nr_im.h"
#include "nr_interp.h"

#define BITS(v, lo, n) ((uint32_t)(((uint64_t)(v) >> (lo)) & ((1ull << (n)) - 1ull)))

static nr_gs *g_gs;
static gpu_renderer *g_gr;
static nr_gs_marker_fn g_marker;
static void *g_marker_user;

void nr_gs_bind(nr_gs *gs, gpu_renderer *gr)
{
    g_gs = gs;
    g_gr = gr;
}
void nr_gs_set_marker(nr_gs_marker_fn fn, void *user)
{
    g_marker = fn;
    g_marker_user = user;
}
nr_gs *nr_gs_state(void) { return g_gs; }
gpu_renderer *nr_gs_device(void) { return g_gr; }

/* ============================================================== the state */
static uint8_t *g_xbuf;           /* host->local transfer data received (worker) */
static uint32_t g_xlen, g_xcap;

static void xfer_end(nr_gs *gs);

void nr_gs_reset(nr_gs *gs)
{
    xfer_end(gs);
    memset(gs->reg, 0, sizeof gs->reg);
    memset(gs->clut, 0, sizeof gs->clut);
    gs->reg[GS_PRMODECONT] = 1;
    gs->vq_n = gs->strip_n = 0;
    gs->cbp0 = gs->cbp1 = 0;
    gs->xfer_dir = -1;
    gs->xfer_px = 0;
    gs->stats.resets++;
}

void nr_gs_init(nr_gs *gs)
{
    memset(gs, 0, sizeof *gs);
    gs->reg[GS_PRMODECONT] = 1;
    gs->preg[16 + 1] = 0x7F00;   /* IMR: everything masked */
    gs->xfer_dir = -1;
}

/* ---- transfers (BITBLTBUF / TRXPOS / TRXREG / TRXDIR) ---- */
static void xfer_rect_dst(const nr_gs *gs, gs_mem_rect *r)
{
    uint64_t b = gs->reg[GS_BITBLTBUF], p = gs->reg[GS_TRXPOS], g = gs->reg[GS_TRXREG];
    r->bp = BITS(b, 32, 14);
    r->bw = BITS(b, 48, 6);
    r->psm = (int)BITS(b, 56, 6);
    r->x = BITS(p, 32, 11);
    r->y = BITS(p, 48, 11);
    r->w = BITS(g, 0, 12);
    r->h = BITS(g, 32, 12);
}

/* the transfer in progress ends (complete, or abandoned by a new TRXDIR / a reset): what
 * arrived is written */
static void xfer_end(nr_gs *gs)
{
    if (gs->xfer_dir == 0 && gs->xfer_px && g_gr) gpu_mem_xfer(g_gr, &gs->xfer_rc, g_xbuf, gs->xfer_px);
    if (gs->xfer_dir == 0 && gs->xfer_px) {
        gs->stats.xfers++;
        gs->stats.xfer_bytes += g_xlen;
    }
    gs->xfer_dir = -1;
    gs->xfer_px = 0;
    g_xlen = 0;
}

static void xfer_start(nr_gs *gs, int dir)
{
    xfer_end(gs);
    if (dir == 0) {
        xfer_rect_dst(gs, &gs->xfer_rc);
        if (gs->xfer_rc.w && gs->xfer_rc.h && nr_psm_bpp(gs->xfer_rc.psm)) gs->xfer_dir = 0;
    } else if (dir == 2) {
        uint64_t b = gs->reg[GS_BITBLTBUF], p = gs->reg[GS_TRXPOS], g = gs->reg[GS_TRXREG];
        gs_mem_rect s;
        s.bp = BITS(b, 0, 14);
        s.bw = BITS(b, 16, 6);
        s.psm = (int)BITS(b, 24, 6);
        s.x = BITS(p, 0, 11);
        s.y = BITS(p, 16, 11);
        s.w = BITS(g, 0, 12);
        s.h = BITS(g, 32, 12);
        if (s.w && s.h && g_gr)
            gpu_mem_copy(g_gr, &s, BITS(b, 32, 14), BITS(b, 48, 6), (int)BITS(b, 56, 6), BITS(p, 32, 11), BITS(p, 48, 11));
        gs->stats.l2l++;
    } else if (dir == 1) {
        /* local->host from the GIF stream: the only reader the game has is sceGsExecStoreImage,
         * served directly (libgraph rg_gs_store_hook); counted */
        gs->stats.l2h++;
    }
}

static void xfer_data(nr_gs *gs, const uint8_t *d, uint32_t n)
{
    uint32_t bpp, want, take, npx;
    if (gs->xfer_dir != 0 || !n) return;
    bpp = (uint32_t)nr_psm_bpp(gs->xfer_rc.psm);
    want = (uint32_t)(((uint64_t)gs->xfer_rc.w * gs->xfer_rc.h * bpp + 7) / 8);
    take = want - g_xlen < n ? want - g_xlen : n;   /* excess data is dropped */
    if (!g_xlen && take == want) {
        /* the whole transfer in one run (most of them): written from the data as it is */
        gs->xfer_px = (uint32_t)((uint64_t)want * 8 / bpp);
        if (gs->xfer_px > gs->xfer_rc.w * gs->xfer_rc.h) gs->xfer_px = gs->xfer_rc.w * gs->xfer_rc.h;
        if (g_gr) gpu_mem_xfer(g_gr, &gs->xfer_rc, d, gs->xfer_px);
        gs->stats.xfers++;
        gs->stats.xfer_bytes += want;
        gs->xfer_dir = -1;
        gs->xfer_px = 0;
        return;
    }
    if (g_xlen + take > g_xcap) {
        uint32_t nc = g_xcap ? g_xcap : 65536;
        uint8_t *nb;
        while (nc < g_xlen + take) nc *= 2;
        nb = (uint8_t *)realloc(g_xbuf, nc);
        if (!nb) return;
        g_xbuf = nb;
        g_xcap = nc;
    }
    memcpy(g_xbuf + g_xlen, d, take);
    g_xlen += take;
    npx = (uint32_t)((uint64_t)g_xlen * 8 / bpp);
    gs->xfer_px = npx;
    if (g_xlen >= want) xfer_end(gs);
}

void nr_gs_image(nr_gs *gs, const void *qw, uint32_t nqw)
{
    gs->stats.image_qw += nqw;
    xfer_data(gs, (const uint8_t *)qw, nqw * 16u);
}

/* ---- CLUT loads (TEX0 / TEX2 CLD: gs_tex.c gs_tex0_written's rules) ---- */
static int psm_indexed(int psm)
{
    return psm == GS_PSMT8 || psm == GS_PSMT8H || psm == GS_PSMT4 || psm == GS_PSMT4HL || psm == GS_PSMT4HH;
}
/* the load a TEX0 value t would make (0: none); cbp0 / cbp1 updated when upd */
static int clut_decide(nr_gs *gs, uint64_t t, int upd, gs_mem_rect *r, int *csm, uint32_t *csa, int *cpsm, uint32_t *n)
{
    int psm = (int)BITS(t, 20, 6), cld = (int)BITS(t, 61, 3), load = 0;
    uint32_t cbp = BITS(t, 37, 14), c0 = gs->cbp0, c1 = gs->cbp1;
    if (!psm_indexed(psm)) return 0;
    switch (cld) {
    case 1: load = 1; break;
    case 2: load = 1; c0 = cbp; break;
    case 3: load = 1; c1 = cbp; break;
    case 4: if (cbp != c0) load = 1; c0 = cbp; break;
    case 5: if (cbp != c1) load = 1; c1 = cbp; break;
    default: break;
    }
    if (upd) { gs->cbp0 = c0; gs->cbp1 = c1; }
    if (!load) return 0;
    *cpsm = (int)BITS(t, 51, 4);
    *csm = (int)BITS(t, 55, 1);
    *csa = BITS(t, 56, 5);
    *n = (psm == GS_PSMT4 || psm == GS_PSMT4HL || psm == GS_PSMT4HH) ? 16u : 256u;
    {
        int is32 = *cpsm == GS_PSMCT32 || *cpsm == GS_PSMCT24;
        uint64_t tc = gs->reg[GS_TEXCLUT];
        r->bp = cbp;
        r->psm = is32 ? GS_PSMCT32 : *cpsm;
        if (*csm == 0) { r->bw = 1; r->x = 0; r->y = 0; r->w = *n == 256 ? 16 : 8; r->h = *n == 256 ? 16 : 2; }
        else { r->bw = BITS(tc, 0, 6); r->x = BITS(tc, 6, 6) * 16u; r->y = BITS(tc, 12, 10); r->w = *n; r->h = 1; }
    }
    return 1;
}
static uint64_t tex0_after(const nr_gs *gs, uint32_t addr, uint64_t data, int *ctx)
{
    if (addr == GS_TEX0_1 || addr == GS_TEX0_2) { *ctx = (int)(addr - GS_TEX0_1); return data; }
    *ctx = (int)(addr - GS_TEX2_1);
    {
        uint64_t mask = (0x3Full << 20) | (~0ull << 37);
        return (gs->reg[GS_TEX0_1 + *ctx] & ~mask) | (data & mask);
    }
}
int nr_gs_clut_would_change(nr_gs *gs, uint32_t addr, uint64_t data)
{
    gs_mem_rect r;
    int csm, cpsm, ctx;
    uint32_t csa, n;
    uint64_t t = tex0_after(gs, addr, data, &ctx);
    if (!clut_decide(gs, t, 0, &r, &csm, &csa, &cpsm, &n) || !g_gr) return 0;
    return gpu_clut_load(g_gr, gs, &r, csm, csa, cpsm, n, 1) != 0;
}
static void tex0_written(nr_gs *gs, int ctx)
{
    gs_mem_rect r;
    int csm, cpsm;
    uint32_t csa, n;
    if (!clut_decide(gs, gs->reg[GS_TEX0_1 + ctx], 1, &r, &csm, &csa, &cpsm, &n)) return;
    gs->stats.clut_loads++;
    if (g_gr) (void)gpu_clut_load(g_gr, gs, &r, csm, csa, cpsm, n, 0);
}

void nr_gs_write_reg(nr_gs *gs, uint32_t addr, uint64_t data)
{
    addr &= 0x7F;
    switch (addr) {
    case GS_PRIM:
        gs->reg[GS_PRIM] = data & 0x7FF;
        gs->vq_n = 0;
        gs->strip_n = 0;
        return;
    case GS_XYZF2: case GS_XYZF3:
        gs->reg[addr] = data;
        gs->reg[GS_FOG] = (uint64_t)BITS(data, 56, 8) << 56;
        return;   /* (vertex kicks: the immediate executor's own queue, nr_im.c) */
    case GS_TEX0_1: case GS_TEX0_2:
        gs->reg[addr] = data;
        tex0_written(gs, (int)(addr - GS_TEX0_1));
        return;
    case GS_TEX2_1: case GS_TEX2_2: {
        int ctx = (int)(addr - GS_TEX2_1);
        uint64_t mask = (0x3Full << 20) | (~0ull << 37);
        gs->reg[addr] = data;
        gs->reg[GS_TEX0_1 + ctx] = (gs->reg[GS_TEX0_1 + ctx] & ~mask) | (data & mask);
        tex0_written(gs, ctx);
        return;
    }
    case GS_TRXDIR:
        gs->reg[addr] = data;
        xfer_start(gs, (int)BITS(data, 0, 2));
        return;
    case GS_HWREG: {
        uint8_t b[8];
        int i;
        gs->reg[addr] = data;
        for (i = 0; i < 8; i++) b[i] = (uint8_t)(data >> (8 * i));
        gs->stats.hwreg++;
        xfer_data(gs, b, 8);
        return;
    }
    case GS_SIGNAL: case GS_FINISH: case GS_LABEL:
        return;   /* raised by the GIF input on the EE thread (nr_hw_gs_event) */
    case GS_TEXFLUSH:
        return;
    case GS_NATIVE_MARK:
        gs->reg[addr] = data;
        if (g_marker) g_marker(g_marker_user, g_gr, gs, data);
        return;
    default:
        if (addr > GS_LABEL) gs->stats.unknown_reg_writes++;
        gs->reg[addr] = data;
        return;
    }
}

/* ============================================================ GIF input (EE)
 * Per path a streaming parse: runs of tags without IMAGE data become records (nr_im_gif_rec)
 * queued to the worker at tag boundaries; IMAGE data goes to the worker as it arrives (the
 * record ring holds records, the worker's ring the data).  While a path is inside a packet,
 * data for the other paths waits (copied) and runs in priority order (PATH1 > PATH2 > PATH3)
 * when the packet is done: the GIF's arbitration at packet boundaries. */
typedef struct gpath {
    /* the stream position: inside a tag (its data qwords left), inside a packet */
    int in_tag, in_packet;
    uint32_t flg, left, eop;
    /* tags of the current run without IMAGE data (a record when the run ends) */
    uint8_t *rec;
    uint32_t rec_n, rec_cap, rec_last;
    /* data received while another path owned the bus */
    uint8_t *wait;
    uint32_t wait_n, wait_cap;
} gpath;
static gpath g_p[4];
static int g_owner;             /* path with an open packet, 0 */
static struct { uint64_t pkts, recs, refused, images, image_qw, waits, opens, resets; } g_gst;

static int grow(uint8_t **b, uint32_t *cap, uint32_t want)
{
    uint32_t nc;
    uint8_t *nb;
    if (want <= *cap) return 0;
    nc = *cap ? *cap : 4096;
    while (nc < want) nc *= 2;
    nb = (uint8_t *)realloc(*b, nc);
    if (!nb) return -1;
    *b = nb;
    *cap = nc;
    return 0;
}

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

/* worker: IMAGE data (qwords) for the transfer in progress */
static void w_image(void *user, const void *data)
{
    uint32_t n;
    (void)user;
    memcpy(&n, data, 4);
    nr_ip_w_image((const uint8_t *)data + 16, n);   /* interpolated presentation: the frame's log */
    if (g_gs) nr_gs_image(g_gs, (const uint8_t *)data + 16, n);
}
static void w_record(void *user, const void *data)
{
    uint32_t id;
    (void)user;
    memcpy(&id, data, 4);
    nr_ip_w_rec(id);   /* interpolated presentation: the frame's log */
    if (g_gs && g_gr) nr_im_marker(g_gr, g_gs, id);
}

/* the path's pending run of tags as a record (EOP set on its last tag: a record is closed) */
static void flush_rec(gpath *g)
{
    uint32_t id;
    if (!g->rec_n) return;
    g->rec[g->rec_last + 1] |= 0x80;
    id = nr_im_gif_rec(g->rec, g->rec_n / 16u);
    g->rec_n = 0;
    if (!id) { g_gst.refused++; return; }
    g_gst.recs++;
    nr_q_call(w_record, NULL, &id, 4);
}
/* IMAGE data to the worker, at most 4 MB per call (a transfer's data may span calls) */
static void put_image(const uint8_t *q, uint32_t nqw)
{
    while (nqw) {
        uint32_t k = nqw < (4u << 20) / 16u ? nqw : (4u << 20) / 16u;
        uint32_t hdr[4] = { k, 0, 0, 0 };
        nr_q_call2(w_image, NULL, hdr, 16, q, k * 16u);
        g_gst.images++;
        g_gst.image_qw += k;
        q += 16u * k;
        nqw -= k;
    }
}

/* the path's stream, qword by tag: IMAGE data goes on as it arrives (texture uploads and
 * movie frames span many sends), the other tags gather into records */
static void path_stream(gpath *g, const uint8_t *q, uint32_t nqw)
{
    uint32_t i = 0;
    while (i < nqw) {
        if (!g->in_tag) {
            uint32_t lo = rd32(q + 16u * i), hi = rd32(q + 16u * i + 4), nl = lo & 0x7FFF, nr = (hi >> 28) & 15;
            if (!nr) nr = 16;
            g->flg = (hi >> 26) & 3;
            g->eop = (lo >> 15) & 1;
            g->left = g->flg == 0 ? nl * nr : g->flg == 1 ? (nl * nr + 1) / 2 : nl;
            if (!g->in_packet) g_gst.opens++;
            g->in_packet = 1;
            if (g->flg >= 2) {
                flush_rec(g);
            } else {
                if (grow(&g->rec, &g->rec_cap, g->rec_n + 16u)) return;
                memcpy(g->rec + g->rec_n, q + 16u * i, 16);
                g->rec_last = g->rec_n;
                g->rec_n += 16u;
            }
            i++;
            g->in_tag = g->left != 0;
        } else {
            uint32_t k = g->left < nqw - i ? g->left : nqw - i;
            if (g->flg >= 2) {
                put_image(q + 16u * i, k);
            } else {
                if (grow(&g->rec, &g->rec_cap, g->rec_n + k * 16u)) return;
                memcpy(g->rec + g->rec_n, q + 16u * i, k * 16u);
                g->rec_n += k * 16u;
            }
            g->left -= k;
            i += k;
            g->in_tag = g->left != 0;
        }
        if (!g->in_tag && g->eop) {
            g->in_packet = 0;
            g_gst.pkts++;
        }
    }
    if (!g->in_tag) flush_rec(g);   /* (at a tag boundary: the records so far run in order) */
}

static void path_data(int p, const uint8_t *q, uint32_t nqw);
static void run_waiting(void)
{
    int p;
    for (p = 1; p <= 3 && !g_owner; p++) {
        gpath *g = &g_p[p];
        if (g->wait_n) {
            uint8_t *b = g->wait;
            uint32_t n = g->wait_n / 16u;
            g->wait = NULL;
            g->wait_n = 0;
            g->wait_cap = 0;
            path_data(p, b, n);
            free(b);
            p = 0;   /* (from PATH1 again) */
        }
    }
}

static void path_data(int p, const uint8_t *q, uint32_t nqw)
{
    gpath *g = &g_p[p];
    if (g_owner && g_owner != p) {
        /* another path is in the middle of a packet: this waits (the GIF arbitrates at packet
         * boundaries) */
        if (grow(&g->wait, &g->wait_cap, g->wait_n + nqw * 16u)) return;
        memcpy(g->wait + g->wait_n, q, nqw * 16u);
        g->wait_n += nqw * 16u;
        g_gst.waits++;
        return;
    }
    path_stream(g, q, nqw);
    g_owner = g->in_packet ? p : 0;
    if (!g_owner) run_waiting();
}

void nr_gs_gif(int path, const void *qw, uint32_t nqw)
{
    if (path < 1 || path > 3 || !nqw) return;
    path_data(path, (const uint8_t *)qw, nqw);
}
void nr_gs_gif_path2(void *user, const uint8_t *d, uint32_t bytes) { (void)user; nr_gs_gif(GS_PATH2, d, bytes / 16u); }
void nr_gs_gif_path1(void *user, const uint8_t *d, uint32_t bytes) { (void)user; nr_gs_gif(GS_PATH1, d, bytes / 16u); }
void nr_gs_gif_path3(const void *qw, uint32_t nqw) { nr_gs_gif(GS_PATH3, qw, nqw); }

void nr_gs_gif_reset(void)
{
    int p;
    for (p = 1; p <= 3; p++) {
        gpath *g = &g_p[p];
        free(g->wait);
        g->wait = NULL;
        g->wait_n = g->wait_cap = 0;
        g->rec_n = 0;
        g->in_tag = g->in_packet = 0;
    }
    g_owner = 0;
    g_gst.resets++;
}

int nr_gs_path_idle(int path)
{
    if (path < 1 || path > 3) return 1;
    return !g_p[path].in_packet && g_p[path].wait_n == 0;
}

void nr_gs_gif_stats(FILE *f)
{
    const nr_gs *gs = g_gs;
    if (!f) return;
    fprintf(f, "native GS input: packets %llu, records %llu (refused %llu), IMAGE runs %llu (%llu qwords), open packets %llu, "
               "arbitration waits %llu, GIF resets %llu\n",
            (unsigned long long)g_gst.pkts, (unsigned long long)g_gst.recs, (unsigned long long)g_gst.refused,
            (unsigned long long)g_gst.images, (unsigned long long)g_gst.image_qw, (unsigned long long)g_gst.opens,
            (unsigned long long)g_gst.waits, (unsigned long long)g_gst.resets);
    if (gs)
        fprintf(f, "native GS state: CLUT loads %llu, transfers %llu (%llu KB), local->local %llu, local->host in the stream %llu, "
                   "HWREG %llu, CSR resets %llu, unknown register writes %llu\n",
                (unsigned long long)gs->stats.clut_loads, (unsigned long long)gs->stats.xfers,
                (unsigned long long)(gs->stats.xfer_bytes >> 10), (unsigned long long)gs->stats.l2l,
                (unsigned long long)gs->stats.l2h, (unsigned long long)gs->stats.hwreg, (unsigned long long)gs->stats.resets,
                (unsigned long long)gs->stats.unknown_reg_writes);
}

#endif /* RG_NATIVE_ONLY && RG_HAVE_GPU */
