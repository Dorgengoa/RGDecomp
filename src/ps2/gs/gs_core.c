/* SPDX-License-Identifier: CC0-1.0 */
/* GS core: lifetime, GIF packet processing (PACKED / REGLIST / IMAGE, EOP,
 * path arbitration), general + privileged register writes, vertex queue and
 * drawing kicks, SIGNAL/FINISH/LABEL, CSR/IMR.  docs/GS.md. */
#if defined(_WIN32) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS /* getenv (RG_GS_CENSUS) */
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gs_internal.h"

static uint32_t f2u(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static float u2f(uint32_t u) { float f; memcpy(&f, &u, 4); return f; }

gs_state *gs_create(void)
{
    gs_state *gs = (gs_state *)calloc(1, sizeof *gs);
    if (!gs) return NULL;
    gs->vram = (uint8_t *)calloc(1, GS_VRAM_BYTES);
    if (!gs->vram) { free(gs); return NULL; }
    gs->sw_raster = 1;
    gs_reset(gs);
    return gs;
}

void gs_destroy(gs_state *gs)
{
    if (!gs) return;
    gs_async_stop(gs);
    for (int p = 1; p <= 3; p++) free(gs->path[p].q);
    free(gs->rb);
    gs_xfer_cache_free(gs);
    gs_mem_lazy_free(gs);
    free(gs->vram);
    free(gs);
}

void gs_reset(gs_state *gs)
{
    gs_mem_materialize(gs, NULL, 1);   /* pending transfers land first (lazy transfers) */
    memset(gs->reg, 0, sizeof gs->reg);
    memset(gs->preg, 0, sizeof gs->preg);
    memset(gs->clut, 0, sizeof gs->clut);
    gs->reg[GS_PRMODECONT] = 1;
    gs->preg[16 + 1] = 0x7F00; /* IMR: everything masked */
    gs->csr_events = 0;
    gs->csr_field = 0;
    gs->internal_q = 1.0f;
    gs->vq_n = 0;
    gs->strip_n = 0;
    gs->cbp0 = gs->cbp1 = 0;
    gs_xfer_stage_flush(gs);
    gs_xfer_end_hook(gs);
    gs_mem_gen_bump(gs, NULL);   /* upload elision: forget what local memory held */
    gs->xfer_dir = -1;
    gs->xfer_carry_n = 0;
    gs->rb_len = gs->rb_off = 0;
    for (int p = 1; p <= 3; p++) {
        gs_gif_path *g = &gs->path[p];
        g->in_tag = g->in_packet = 0;
        g->q_len = g->q_off = 0;
    }
    gs->bus_owner = 0;
}

void gs__gif_reset_now(gs_state *gs)
{
    if (gs->rec) gs->rec(gs->rec_user, GS_REC_GIF_RESET, 0, 0, NULL, 0);
    for (int p = 1; p <= 3; p++) {
        gs_gif_path *g = &gs->path[p];
        g->in_tag = g->in_packet = 0;
        g->nloop = 0;
        g->reg_i = 0;
        g->q_len = g->q_off = 0;
    }
    gs->bus_owner = 0;
    gs->vq_n = 0;
    gs->strip_n = 0;
}

/* ---- measurement: $RG_GS_CENSUS=N prints, every N vsyncs, how the EE side
 * observed the GS (CSR reads, events raised, FIFO reads; docs/PERF-3D.md) */
static struct { int init; uint32_t every, n; uint64_t csr_reads, priv_reads, ev[5], ev_unmasked[5], fifo; } g_census;
static int census_on(void)
{
    if (!g_census.init) {
        const char *e = getenv("RG_GS_CENSUS");
        g_census.init = 1;
        g_census.every = e ? (uint32_t)atoi(e) : 0;
    }
    return g_census.every != 0;
}
void gs_census_fifo(void) { if (census_on()) g_census.fifo++; }

/* ---- $RG_NR_FXCENSUS=1: what still goes through the model per source (docs/NATIVE-RENDER.md
 * "Census of the emulated residue"): register writes and drawing kicks from the GIF parser
 * (raw packets: VIF DIRECT, VU1 XGKICK, PATH3) vs inside a native marker (the immediate
 * records' state writes and fallbacks, shadow / line draws), transfers by direction and
 * format, CLUT loads, privileged writes.  Counting only. */
int gs__fx_on = -1;
static int g_fx_marker;
static uint64_t g_fx_reg[2][128], g_fx_prim[2][8], g_fx_priv[32], g_fx_xfer[4][64], g_fx_clut[2][16];
static int fx_on(void)
{
    if (gs__fx_on < 0) {
        const char *e = getenv("RG_NR_FXCENSUS");
        gs__fx_on = e && *e && *e != '0';
    }
    return gs__fx_on;
}
void gs__fx_prim(int type) { if (fx_on()) g_fx_prim[g_fx_marker][type & 7]++; }
void gs__fx_xfer(int dir, int psm) { if (fx_on()) g_fx_xfer[dir & 3][psm & 63]++; }
void gs__fx_clut(int cpsm) { if (fx_on()) g_fx_clut[g_fx_marker][cpsm & 15]++; }
void gs_fx_census_dump(FILE *f)
{
    static const char *src[2] = {"GIF", "marker"};
    if (!fx_on() || !f) return;
    for (int m = 0; m < 2; m++) {
        fprintf(f, "fxcensus %s register writes:", src[m]);
        for (int a = 0; a < 128; a++)
            if (g_fx_reg[m][a]) fprintf(f, " %02X:%llu", a, (unsigned long long)g_fx_reg[m][a]);
        fprintf(f, "\nfxcensus %s drawing kicks by type:", src[m]);
        for (int t = 0; t < 8; t++)
            if (g_fx_prim[m][t]) fprintf(f, " %d:%llu", t, (unsigned long long)g_fx_prim[m][t]);
        fprintf(f, "\nfxcensus %s CLUT loads by CPSM:", src[m]);
        for (int t = 0; t < 16; t++)
            if (g_fx_clut[m][t]) fprintf(f, " %02X:%llu", t, (unsigned long long)g_fx_clut[m][t]);
        fprintf(f, "\n");
    }
    for (int d = 0; d < 4; d++) {
        int any = 0;
        for (int p = 0; p < 64; p++) any |= g_fx_xfer[d][p] != 0;
        if (!any) continue;
        fprintf(f, "fxcensus transfers dir %d (0 host->local, 1 local->host, 2 local->local) by PSM:", d);
        for (int p = 0; p < 64; p++)
            if (g_fx_xfer[d][p]) fprintf(f, " %02X:%llu", p, (unsigned long long)g_fx_xfer[d][p]);
        fprintf(f, "\n");
    }
    fprintf(f, "fxcensus privileged writes by index:");
    for (int i = 0; i < 32; i++)
        if (g_fx_priv[i]) fprintf(f, " %d:%llu", i, (unsigned long long)g_fx_priv[i]);
    fprintf(f, "\n");
}

/* ---- events ---- */
static void raise_event(gs_state *gs, uint32_t bit)
{
    if (census_on()) {
        for (int k = 0; k < 5; k++)
            if (bit & (1u << k)) {
                g_census.ev[k]++;
                if (!((uint32_t)gs->preg[16 + 1] & (bit << 8))) g_census.ev_unmasked[k]++;
            }
    }
    /* atomic: with the worker (gs_async.c) a masked SIGNAL / FINISH lands
     * there while gs_vsync raises VSINT on the caller's thread */
    __atomic_fetch_or(&gs->csr_events, bit, __ATOMIC_SEQ_CST);
    uint32_t imr = (uint32_t)gs->preg[16 + 1];
    if (!(imr & (bit << 8)) && gs->irq) gs->irq(gs->irq_user, bit);
}

/* ---- vertex kick ---- */
static void vertex_kick(gs_state *gs, uint32_t x, uint32_t y, uint32_t z,
                        uint32_t f, int draw)
{
    gs_vertex nv;
    uint64_t rgbaq = gs->reg[GS_RGBAQ], st = gs->reg[GS_ST], uv = gs->reg[GS_UV];
    nv.x = (uint16_t)x; nv.y = (uint16_t)y; nv.z = z; nv.f = (uint8_t)f;
    nv.r = (uint8_t)GS_BITS(rgbaq, 0, 8); nv.g = (uint8_t)GS_BITS(rgbaq, 8, 8);
    nv.b = (uint8_t)GS_BITS(rgbaq, 16, 8); nv.a = (uint8_t)GS_BITS(rgbaq, 24, 8);
    nv.q = u2f(GS_BITS(rgbaq, 32, 32));
    nv.s = u2f(GS_BITS(st, 0, 32)); nv.t = u2f(GS_BITS(st, 32, 32));
    nv.u = (uint16_t)GS_BITS(uv, 0, 14); nv.v = (uint16_t)GS_BITS(uv, 16, 14);

    int type = (int)GS_BITS(gs->reg[GS_PRIM], 0, 3);
    static const int need[8] = { 1, 2, 2, 3, 3, 3, 2, 0 };
    if (need[type] == 0) return; /* reserved type: ignored */
    gs->vq[gs->vq_n++] = nv;
    gs->strip_n++;
    if (gs->vq_n < need[type]) return;
    if (draw) gs_draw_kick(gs, gs->vq, need[type], type);
    switch (type) {
    case GS_PRIM_LINESTRIP: gs->vq[0] = gs->vq[1]; gs->vq_n = 1; break;
    case GS_PRIM_TRISTRIP: gs->vq[0] = gs->vq[1]; gs->vq[1] = gs->vq[2]; gs->vq_n = 2; break;
    case GS_PRIM_TRIFAN: gs->vq[1] = gs->vq[2]; gs->vq_n = 2; break;
    default: gs->vq_n = 0; break;
    }
}

/* ---- general registers ---- */
void gs_write_reg(gs_state *gs, uint32_t addr, uint64_t data)
{
    addr &= 0x7F;
    if (gs__fx_on && fx_on()) g_fx_reg[g_fx_marker][addr]++;
    switch (addr) {
    case GS_PRIM:
        gs->reg[GS_PRIM] = data & 0x7FF;
        gs->vq_n = 0;
        gs->strip_n = 0;
        return;
    case GS_XYZF2: case GS_XYZF3:
        gs->reg[addr] = data;
        gs->reg[GS_FOG] = (uint64_t)GS_BITS(data, 56, 8) << 56;
        vertex_kick(gs, GS_BITS(data, 0, 16), GS_BITS(data, 16, 16),
                    GS_BITS(data, 32, 24), GS_BITS(data, 56, 8), addr == GS_XYZF2);
        return;
    case GS_XYZ2: case GS_XYZ3:
        gs->reg[addr] = data;
        vertex_kick(gs, GS_BITS(data, 0, 16), GS_BITS(data, 16, 16),
                    GS_BITS(data, 32, 32), GS_BITS(gs->reg[GS_FOG], 56, 8),
                    addr == GS_XYZ2);
        return;
    case GS_TEX0_1: case GS_TEX0_2:
        gs->reg[addr] = data;
        gs_tex0_written(gs, (int)(addr - GS_TEX0_1));
        return;
    case GS_TEX2_1: case GS_TEX2_2: {
        int ctx = (int)(addr - GS_TEX2_1);
        uint64_t mask = (0x3Full << 20) | (~0ull << 37);
        gs->reg[addr] = data;
        gs->reg[GS_TEX0_1 + ctx] = (gs->reg[GS_TEX0_1 + ctx] & ~mask) | (data & mask);
        gs_tex0_written(gs, ctx);
        return;
    }
    case GS_TRXDIR:
        gs->reg[addr] = data;
        gs_xfer_start(gs, (int)GS_BITS(data, 0, 2));
        return;
    case GS_HWREG:
        gs->reg[addr] = data;
        gs_xfer_hwreg(gs, data);
        return;
    case GS_SIGNAL: {
        uint32_t id = GS_BITS(data, 0, 32), msk = GS_BITS(data, 32, 32);
        uint64_t s = gs->preg[16 + 8];
        uint32_t sig = (uint32_t)s;
        sig = (sig & ~msk) | (id & msk);
        gs->preg[16 + 8] = (s & 0xFFFFFFFF00000000ull) | sig;
        raise_event(gs, GS_CSR_SIGNAL);
        return;
    }
    case GS_FINISH:
        raise_event(gs, GS_CSR_FINISH);
        return;
    case GS_LABEL: {
        uint32_t id = GS_BITS(data, 0, 32), msk = GS_BITS(data, 32, 32);
        uint64_t s = gs->preg[16 + 8];
        uint32_t lbl = (uint32_t)(s >> 32);
        lbl = (lbl & ~msk) | (id & msk);
        gs->preg[16 + 8] = (s & 0xFFFFFFFFull) | ((uint64_t)lbl << 32);
        return;
    }
    case GS_TEXFLUSH:
        return;
    case GS_NATIVE_MARK:
        gs->reg[addr] = data;
        g_fx_marker = 1;
        if (gs->hooks.native) gs->hooks.native(gs->hooks.user, gs, data);
        g_fx_marker = 0;
        return;
    case GS_RGBAQ: case GS_ST: case GS_UV: case GS_FOG:
    case GS_CLAMP_1: case GS_CLAMP_2: case GS_TEX1_1: case GS_TEX1_2:
    case GS_XYOFFSET_1: case GS_XYOFFSET_2: case GS_PRMODECONT: case GS_PRMODE:
    case GS_TEXCLUT: case GS_SCANMSK: case GS_MIPTBP1_1: case GS_MIPTBP1_2:
    case GS_MIPTBP2_1: case GS_MIPTBP2_2: case GS_TEXA: case GS_FOGCOL:
    case GS_SCISSOR_1: case GS_SCISSOR_2: case GS_ALPHA_1: case GS_ALPHA_2:
    case GS_DIMX: case GS_DTHE: case GS_COLCLAMP: case GS_TEST_1: case GS_TEST_2:
    case GS_PABE: case GS_FBA_1: case GS_FBA_2: case GS_FRAME_1: case GS_FRAME_2:
    case GS_ZBUF_1: case GS_ZBUF_2: case GS_BITBLTBUF: case GS_TRXPOS:
    case GS_TRXREG:
        gs->reg[addr] = data;
        return;
    default:
        gs->reg[addr] = data;
        gs->stats.unknown_reg_writes++;
        return;
    }
}

/* ---- privileged registers ---- */
static int preg_index(uint32_t a)
{
    a &= 0x1FFFu;
    if (a >= 0x1000u) {
        if ((a - 0x1000u) >= 0x100u) return -1;
        return 16 + (int)((a - 0x1000u) >> 4);
    }
    if (a >= 0x100u) return -1;
    return (int)(a >> 4);
}

void gs_write_priv(gs_state *gs, uint32_t ee_addr, uint64_t data)
{
    if (gs->async && (preg_index(ee_addr) == 16 || gs->rec)) gs_async_drain(gs);   /* CSR (RESET) / recorder order */
    if (preg_index(ee_addr) == 16 + 1) gs__async_events_settle(gs);              /* IMR after queued events */
    if (gs->rec) gs->rec(gs->rec_user, GS_REC_PRIV, ee_addr, data, NULL, 0);
    int i = preg_index(ee_addr);
    if (i < 0) return;
    if (gs__fx_on && fx_on()) g_fx_priv[i & 31]++;
    if (i == 16) { /* CSR */
        gs->csr_events &= ~(uint32_t)(data & 0x1Fu);
        if (data & GS_CSR_RESET) { gs_reset(gs); gs__async_rescan(gs); }
        return;
    }
    if (i == 16 + 1) { gs->preg[i] = data & 0x7F00u; return; } /* IMR */
    gs->preg[i] = data;
}

uint64_t gs_read_priv(gs_state *gs, uint32_t ee_addr)
{
    int i = preg_index(ee_addr);
    if (i < 0) return 0;
    if (census_on()) { g_census.priv_reads++; if (i == 16) g_census.csr_reads++; }
    if (i == 16 || i == 16 + 8) gs__async_events_settle(gs);   /* CSR, SIGLBLID */
    if (i == 16) {
        /* FIFO empty (bits 14-15 = 01); REV 0x1B, ID 0x55 (nominal, see GS.md) */
        return (uint64_t)gs->csr_events | ((uint64_t)(gs->csr_field & 1u) << 13) |
               (1ull << 14) | (0x1Bull << 16) | (0x55ull << 24);
    }
    return gs->preg[i];
}

void gs_vsync(gs_state *gs)
{
    if (gs->rec) gs->rec(gs->rec_user, GS_REC_VSYNC, 0, 0, NULL, 0);
    if (gs->preg[2] & 1) gs->csr_field ^= 1u; /* SMODE2.INT */
    else gs->csr_field = 0;
    raise_event(gs, GS_CSR_VSINT);
    if (census_on() && ++g_census.n % g_census.every == 0) {
        fprintf(stderr, "GSCENSUS vsync %u: csr reads %llu, priv reads %llu, fifo reads %llu, events raised "
                "(SIGNAL FINISH HSINT VSINT EDWINT) %llu %llu %llu %llu %llu, unmasked %llu %llu %llu %llu %llu\n",
                g_census.n, (unsigned long long)g_census.csr_reads, (unsigned long long)g_census.priv_reads,
                (unsigned long long)g_census.fifo, (unsigned long long)g_census.ev[0], (unsigned long long)g_census.ev[1],
                (unsigned long long)g_census.ev[2], (unsigned long long)g_census.ev[3], (unsigned long long)g_census.ev[4],
                (unsigned long long)g_census.ev_unmasked[0], (unsigned long long)g_census.ev_unmasked[1],
                (unsigned long long)g_census.ev_unmasked[2], (unsigned long long)g_census.ev_unmasked[3],
                (unsigned long long)g_census.ev_unmasked[4]);
    }
}

/* ---- GIF ---- */
static void packed_write(gs_state *gs, uint32_t desc, uint64_t lo, uint64_t hi)
{
    switch (desc) {
    case 0x0: gs_write_reg(gs, GS_PRIM, lo & 0x7FF); break;
    case 0x1: {
        uint64_t v = GS_BITS(lo, 0, 8) | (GS_BITS(lo, 32, 8) << 8) |
                     (GS_BITS(hi, 0, 8) << 16) | ((uint64_t)GS_BITS(hi, 32, 8) << 24) |
                     ((uint64_t)f2u(gs->internal_q) << 32);
        gs_write_reg(gs, GS_RGBAQ, v);
        break;
    }
    case 0x2:
        gs_write_reg(gs, GS_ST, lo);
        gs->internal_q = u2f((uint32_t)hi);
        break;
    case 0x3:
        gs_write_reg(gs, GS_UV, GS_BITS(lo, 0, 14) | ((uint64_t)GS_BITS(lo, 32, 14) << 16));
        break;
    case 0x4: {
        uint64_t v = GS_BITS(lo, 0, 16) | ((uint64_t)GS_BITS(lo, 32, 16) << 16) |
                     ((uint64_t)GS_BITS(hi, 4, 24) << 32) | ((uint64_t)GS_BITS(hi, 36, 8) << 56);
        gs_write_reg(gs, GS_BITS(hi, 47, 1) ? GS_XYZF3 : GS_XYZF2, v);
        break;
    }
    case 0x5: {
        uint64_t v = GS_BITS(lo, 0, 16) | ((uint64_t)GS_BITS(lo, 32, 16) << 16) |
                     ((uint64_t)GS_BITS(hi, 0, 32) << 32);
        gs_write_reg(gs, GS_BITS(hi, 47, 1) ? GS_XYZ3 : GS_XYZ2, v);
        break;
    }
    case 0x6: case 0x7: case 0x8: case 0x9: case 0xC: case 0xD:
        gs_write_reg(gs, desc, lo);
        break;
    case 0xA:
        gs_write_reg(gs, GS_FOG, (uint64_t)GS_BITS(hi, 36, 8) << 56);
        break;
    case 0xE:
        gs_write_reg(gs, (uint32_t)(hi & 0xFF), lo);
        break;
    default: /* 0xB reserved, 0xF NOP */
        break;
    }
}

/* Process one qword on a path.  Returns 1 when it completed a packet. */
static int gif_qword(gs_state *gs, int p, const uint8_t *q)
{
    gs_gif_path *g = &gs->path[p];
    uint64_t lo = gs_rd64(q), hi = gs_rd64(q + 8);
    g->qwords++;
    if (!g->in_tag) {
        g->nloop = GS_BITS(lo, 0, 15);
        g->eop = GS_BITS(lo, 15, 1);
        g->flg = GS_BITS(lo, 58, 2);
        /* staged transfer data (gs_mem.c) waits only for more IMAGE data of the
         * same path: anything else the GS does first writes it */
        if (g->flg < 2 || p != gs_stage_path) gs_xfer_stage_flush(gs);
        g->nreg = GS_BITS(lo, 60, 4);
        if (g->nreg == 0) g->nreg = 16;
        g->regs = hi;
        g->reg_i = 0;
        g->in_tag = 1;
        g->in_packet = 1;
        gs->internal_q = 1.0f;
        if (g->flg == 0 && GS_BITS(lo, 46, 1))
            gs_write_reg(gs, GS_PRIM, GS_BITS(lo, 47, 11));
    } else if (g->flg == 0) {
        packed_write(gs, (uint32_t)((g->regs >> (4 * g->reg_i)) & 15u), lo, hi);
        if (++g->reg_i == g->nreg) { g->reg_i = 0; g->nloop--; }
    } else if (g->flg == 1) {
        uint64_t half[2] = { lo, hi };
        for (int h = 0; h < 2 && g->nloop; h++) {
            uint32_t desc = (uint32_t)((g->regs >> (4 * g->reg_i)) & 15u);
            if (desc <= 0xD && desc != 0xB) gs_write_reg(gs, desc, half[h]);
            if (++g->reg_i == g->nreg) { g->reg_i = 0; g->nloop--; }
        }
    } else {
        gs_write_reg(gs, GS_HWREG, lo);
        gs_write_reg(gs, GS_HWREG, hi);
        g->nloop--;
    }
    if (g->nloop == 0) {
        g->in_tag = 0;
        if (g->eop) {
            g->in_packet = 0;
            g->packets++;
            return 1;
        }
    }
    return 0;
}

static void q_append(gs_gif_path *g, const uint8_t *d, uint32_t bytes)
{
    if (g->q_off == g->q_len) g->q_off = g->q_len = 0;
    if (g->q_len + bytes > g->q_cap) {
        uint32_t nc = g->q_cap ? g->q_cap : 4096;
        while (nc < g->q_len + bytes) nc *= 2;
        uint8_t *n = (uint8_t *)realloc(g->q, nc);
        if (!n) return;
        g->q = n; g->q_cap = nc;
    }
    memcpy(g->q + g->q_len, d, bytes);
    g->q_len += bytes;
}

static int q_has(const gs_gif_path *g) { return g->q_len - g->q_off >= 16; }

void gs__gif_write_now(gs_state *gs, int path, const void *qwords, uint32_t nqw)
{
    if (path < 1 || path > 3 || nqw == 0) return;
    if (gs->rec) gs->rec(gs->rec_user, GS_REC_GIF, (uint32_t)path, 0, qwords, nqw * 16u);
    q_append(&gs->path[path], (const uint8_t *)qwords, nqw * 16u);
    if (gs->in_arbitration) return;
    gs->in_arbitration = 1;
    for (;;) {
        int p = gs->bus_owner;
        if (p == 0) {
            for (int c = 1; c <= 3; c++)
                if (q_has(&gs->path[c])) { p = c; break; }
            if (p == 0) break;
        } else if (!q_has(&gs->path[p])) {
            break; /* owner is mid-packet and waits for more data */
        }
        gs_gif_path *g = &gs->path[p];
        while (q_has(g)) {
            if (g->in_tag && g->flg >= 2) {
                /* IMAGE data: every queued qword of the loop at once, the
                 * same as HWREG writes of lo, hi per qword (gs_xfer_image).
                 * HWREG ends up holding the last word. */
                uint32_t avail = (g->q_len - g->q_off) / 16u;
                uint32_t k = g->nloop < avail ? g->nloop : avail;
                const uint8_t *q = g->q + g->q_off;
                gs_stage_path = p;
                gs_xfer_image(gs, q, k * 16u);
                gs->reg[GS_HWREG] = gs_rd64(q + (k - 1) * 16u + 8);
                g->qwords += k;
                g->nloop -= k;
                g->q_off += 16u * k;
                int done = 0;
                if (g->nloop == 0) {
                    g->in_tag = 0;
                    if (g->eop) { g->in_packet = 0; g->packets++; done = 1; }
                }
                if (done) { gs->bus_owner = 0; break; }
                gs->bus_owner = g->in_packet ? p : 0;
                continue;
            }
            int done = gif_qword(gs, p, g->q + g->q_off);
            g->q_off += 16;
            if (done) { gs->bus_owner = 0; break; }
            gs->bus_owner = g->in_packet ? p : 0;
        }
        if (g->q_off == g->q_len) g->q_off = g->q_len = 0;
    }
    gs->in_arbitration = 0;
}

void gs_image_write(gs_state *gs, int path, const void *qwords, uint32_t nqw)
{
    const uint8_t *q = (const uint8_t *)qwords;
    if (nqw == 0) return;
    gs_stage_path = path;
    gs_xfer_image(gs, q, nqw * 16u);
    gs->reg[GS_HWREG] = gs_rd64(q + (nqw - 1) * 16u + 8);
    gs_xfer_stage_flush(gs);
}

void gs_vu1_gif_sink(void *user, const uint8_t *data, uint32_t bytes,
                     uint32_t vu_addr)
{
    (void)vu_addr;
    gs_gif_write((gs_state *)user, GS_PATH1, data, bytes / 16u);
}

void gs_vif1_gif_sink(void *user, const uint8_t *data, uint32_t bytes)
{
    gs_gif_write((gs_state *)user, GS_PATH2, data, bytes / 16u);
}

int gs_path_idle(const gs_state *gs, int path)
{
    gs_async_drain((gs_state *)gs);
    if (path < 1 || path > 3) return 1;
    const gs_gif_path *g = &gs->path[path];
    return !g->in_packet && g->q_len == g->q_off;
}
