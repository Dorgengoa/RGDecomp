/* SPDX-License-Identifier: CC0-1.0 */
/* Immediate packets natively (nr_im.h, docs/NATIVE-RENDER.md "Immediate
 * packets (slice 3)"). */
#include "nr_mem.h"
#include "nr_im.h"
#include "nr.h"

#include <stdlib.h>
#include <string.h>

#include "gs.h"
#ifdef RG_HAVE_GPU
#include "gpu.h"
#endif
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY && defined(RG_HAVE_GPU)
/* native-only (docs/NATIVE-RENDER.md "Checkpoint 10"): the records run on the native state
 * block (nr_gs.h), every GIF stream becomes records (nr_gs.c), nothing reaches a GS model */
#include "nr_gs.h"
#define NR_ONLY 1
#define GS_WRITE_REG(gs, a, d) nr_gs_write_reg(gs, a, d)
#else
#define NR_ONLY 0
#define GS_WRITE_REG(gs, a, d) gs_write_reg(gs, a, d)
#endif

static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static uint64_t rd64(const uint8_t *p) { uint64_t v; memcpy(&v, p, 8); return v; }

/* ---- mode ------------------------------------------------------------------ */
static int g_mode = -1;
int nr_im_mode(void)
{
    if (g_mode < 0) {
        const char *e = getenv("RG_NR_IM");
        if (nr_mode() != NR_NATIVE) g_mode = NRIM_OFF;
        else if (e && !strcmp(e, "off")) g_mode = NRIM_OFF;
        else if (e && !strcmp(e, "replay")) g_mode = NRIM_REPLAY;
        else g_mode = NRIM_NATIVE;
    }
    return g_mode;
}

/* ---- records ---------------------------------------------------------------
 * The command stream is a ring of 64-bit words written by the EE and read by
 * the GS thread when the marker arrives (the GS worker lags the EE by at most
 * about a field; the ring holds many frames):
 *   (1 << 60) | addr, data            a GS register write (gs_write_reg)
 *   (2 << 60) | nqw, nqw x (lo, hi)   IMAGE data (gs_image_write)            */
#define IM_RING (1u << 22)          /* words: 32 MB */
#define IM_RECS 65536u
enum { C_REG = 1, C_IMAGE = 2 };
typedef struct im_rec {
    uint32_t id;
    uint32_t n;            /* words */
    uint64_t start;        /* ring position */
    int mpg;               /* the packet carried microcode (composite draw-back, RG_NR_MPG=drop) */
    int xs;                /* squeezed in X by the widescreen layout (nr_im_note_xscaled) */
} im_rec;
static uint64_t *g_ring;
static uint64_t g_wpos;            /* EE: next ring word (monotonic) */
static im_rec *g_recs;
static uint32_t g_next = 1;
static int g_xs_pending;           /* EE: nr_im_note_xscaled since the last end_prim */

void nr_im_note_xscaled(void) { g_xs_pending = 1; }

static struct {
    uint64_t pkts, replaced, regs, image_qw, prims;
    uint64_t f_tag, f_vif, f_align, f_gif_open, f_signal, f_l2h, f_small, f_size;
    uint64_t gs_stale, gs_runs;
    uint64_t vifcmd[128];
    uint64_t mpg;
    uint64_t nat_batches, nat_prims, emu_prims, emu_batches, skip_batches, lines, kept_batches;
    uint64_t gif_pkts, gif_refused, gif_ref_why[8];   /* nr_im_gif */
} g_st;
static int ring_init(void);

/* ---- EE: decode ------------------------------------------------------------ */
typedef struct dec {
    int in_tag, in_packet;
    uint32_t nloop, nreg, flg, eop, reg_i;
    uint64_t regs;
    uint32_t iq;               /* PACKED internal Q (float bits), 1.0 at each tag */
    uint32_t direct_left;      /* DIRECT qwords still to come */
    uint32_t skip_left;        /* MPG payload words still to skip */
    int img_open;
    uint64_t img_hdr;
    uint32_t img_n;
    int flusha;
    int mpg;
    int allow_mark;            /* nr_im_gif: mesh markers (GS_NATIVE_MARK without NRIM_MARK_BIT) are kept */
    int ee_events;             /* nr_im_gif_rec (native-only): SIGNAL / FINISH / LABEL raised here, every
                                  marker and local->host start kept in the record */
    int err;
    uint32_t words;
} dec;
enum { E_TAG = 1, E_VIF, E_ALIGN, E_GIFOPEN, E_SIGNAL, E_L2H, E_SIZE };

static void put(dec *s, uint64_t w)
{
    g_ring[g_wpos & (IM_RING - 1)] = w;
    g_wpos++;
    if (++s->words > IM_RING / 4) s->err = E_SIZE;
}
static void img_close(dec *s)
{
    if (!s->img_open) return;
    g_ring[s->img_hdr & (IM_RING - 1)] = ((uint64_t)C_IMAGE << 60) | s->img_n;
    s->img_open = 0;
}
static void reg(dec *s, uint32_t addr, uint64_t data)
{
    addr &= 0x7F;
#if NR_ONLY
    if (s->ee_events) {
        if (addr == GS_SIGNAL || addr == GS_FINISH || addr == GS_LABEL) {
            nr_hw_gs_event(addr, data);   /* CSR / SIGLBLID / interrupt now, on the EE thread */
            return;
        }
        img_close(s);
        put(s, ((uint64_t)C_REG << 60) | addr);
        put(s, data);
        g_st.regs++;
        return;
    }
#endif
    if (addr == GS_NATIVE_MARK && s->allow_mark && !(data & NRIM_MARK_BIT)) {
        /* a native mesh's marker inside a DIRECT packet (nr_im_gif): run in the record, in order
         * (the executor's gs_write_reg calls the marker hook); immediate-record markers never */
    } else if (addr == GS_SIGNAL || addr == GS_FINISH || addr == GS_LABEL || addr == GS_NATIVE_MARK) {
        /* the GS worker runs SIGNAL / FINISH / LABEL packets synchronously
         * (gs_async.c): they must stay visible to it */
        s->err = E_SIGNAL;
        return;
    }
    if (addr == GS_TRXDIR && (data & 3) == 1) { s->err = E_L2H; return; }   /* local->host: the EE reads the FIFO */
    img_close(s);
    put(s, ((uint64_t)C_REG << 60) | addr);
    put(s, data);
    g_st.regs++;
}

#define BITS(v, lo, n) ((uint32_t)(((uint64_t)(v) >> (lo)) & ((1ull << (n)) - 1ull)))

static void packed(dec *s, uint32_t desc, uint64_t lo, uint64_t hi)
{
    switch (desc) {
    case 0x0: reg(s, GS_PRIM, lo & 0x7FF); break;
    case 0x1:
        reg(s, GS_RGBAQ, BITS(lo, 0, 8) | ((uint64_t)BITS(lo, 32, 8) << 8) | ((uint64_t)BITS(hi, 0, 8) << 16) |
                         ((uint64_t)BITS(hi, 32, 8) << 24) | ((uint64_t)s->iq << 32));
        break;
    case 0x2: reg(s, GS_ST, lo); s->iq = (uint32_t)hi; break;
    case 0x3: reg(s, GS_UV, BITS(lo, 0, 14) | ((uint64_t)BITS(lo, 32, 14) << 16)); break;
    case 0x4:
        reg(s, BITS(hi, 47, 1) ? GS_XYZF3 : GS_XYZF2,
            BITS(lo, 0, 16) | ((uint64_t)BITS(lo, 32, 16) << 16) | ((uint64_t)BITS(hi, 4, 24) << 32) |
            ((uint64_t)BITS(hi, 36, 8) << 56));
        break;
    case 0x5:
        reg(s, BITS(hi, 47, 1) ? GS_XYZ3 : GS_XYZ2,
            BITS(lo, 0, 16) | ((uint64_t)BITS(lo, 32, 16) << 16) | ((uint64_t)BITS(hi, 0, 32) << 32));
        break;
    case 0x6: case 0x7: case 0x8: case 0x9: case 0xC: case 0xD: reg(s, desc, lo); break;
    case 0xA: reg(s, GS_FOG, (uint64_t)BITS(hi, 36, 8) << 56); break;
    case 0xE: reg(s, (uint32_t)(hi & 0xFF), lo); break;
    default: break;   /* 0xB reserved, 0xF NOP */
    }
}

/* one GIF qword (gs_core.c gif_qword, without drawing) */
static void gif_qword(dec *s, const uint8_t *q)
{
    uint64_t lo = rd64(q), hi = rd64(q + 8);
    if (!s->in_tag) {
        s->nloop = BITS(lo, 0, 15);
        s->eop = BITS(lo, 15, 1);
        s->flg = BITS(lo, 58, 2);
        s->nreg = BITS(lo, 60, 4);
        if (s->nreg == 0) s->nreg = 16;
        s->regs = hi;
        s->reg_i = 0;
        s->in_tag = 1;
        s->in_packet = 1;
        s->iq = 0x3F800000u;
        if (s->flg == 0 && BITS(lo, 46, 1)) reg(s, GS_PRIM, BITS(lo, 47, 11));
        if (s->flg < 2) img_close(s);   /* consecutive IMAGE tags stay one IMAGE command */
    } else if (s->flg == 0) {
        packed(s, (uint32_t)((s->regs >> (4 * s->reg_i)) & 15u), lo, hi);
        if (++s->reg_i == s->nreg) { s->reg_i = 0; s->nloop--; }
    } else if (s->flg == 1) {
        uint64_t half[2] = { lo, hi };
        for (int h = 0; h < 2 && s->nloop; h++) {
            uint32_t desc = (uint32_t)((s->regs >> (4 * s->reg_i)) & 15u);
            if (desc <= 0xD && desc != 0xB) reg(s, desc, half[h]);
            if (++s->reg_i == s->nreg) { s->reg_i = 0; s->nloop--; }
        }
    } else {
        if (!s->img_open) {
            s->img_hdr = g_wpos;
            put(s, 0);
            s->img_open = 1;
            s->img_n = 0;
        }
        put(s, lo);
        put(s, hi);
        s->img_n++;
        g_st.image_qw++;
        s->nloop--;
    }
    if (s->nloop == 0) {
        s->in_tag = 0;
        if (s->eop) s->in_packet = 0;
    }
}

static int mpg_keep(void)
{
    static int k = -1;
    /* drop is the default since checkpoint 9 (the draw-back's CT24 texels expanded per tap
     * before the GS-exact bilinear filter: nr_draw.hlsl nr_expand / PF_GSLIN); keep = the old path */
    if (k < 0) { const char *e = getenv("RG_NR_MPG"); k = (e && !strcmp(e, "keep")) || !nr_comp_native(); }
    return k;
}

/* VIF codes of the GsPkt sub-chains: NOP, FLUSH*, MARK, DIRECT(HL).  aligned:
 * the next word starts a qword (DIRECT data must) */
static void vif_cmd(dec *s, uint32_t w, int aligned)
{
    uint32_t cmd = (w >> 24) & 0x7F;
    switch (cmd) {
    case 0x00: case 0x07: case 0x10: case 0x11: return;   /* NOP MARK FLUSHE FLUSH */
    case 0x13: s->flusha = 1; return;                       /* FLUSHA: kept in the marker */
    case 0x4A:
        /* MPG: VU1 microcode for the composite program 0x445C60, which only runs when a clip
         * range is unknown (an emulated mesh inside it); natively nothing executes VU code,
         * so the upload is dropped (the composite never falls back to the VU program since
         * 2026-10-18 (7)) and the packet decoded here (default since checkpoint 9).  These
         * packets are the composite's draw-back (the character work texture back onto the
         * frame); their alpha edges came out wrong natively until the CT24 texels were
         * expanded per tap before the filter (checkpoint 9).  RG_NR_MPG=keep: the packet goes
         * to the VIF path (the walker drops its MPG and hands its DIRECT data to the GS) */
        if (mpg_keep()) { s->err = E_VIF; g_st.vifcmd[cmd]++; return; }
        s->skip_left = (((w >> 16) & 0xFF) ? ((w >> 16) & 0xFF) : 256u) * 2u;
        g_st.mpg++;
        s->mpg = 1;
        return;
    case 0x50: case 0x51:
        if (!aligned) { s->err = E_ALIGN; return; }
        s->direct_left = (w & 0xFFFF) ? (w & 0xFFFF) : 65536u;
        return;
    default: s->err = E_VIF; g_st.vifcmd[cmd]++; return;
    }
}

static void vif_block(dec *s, const uint8_t *tag, const uint8_t *data, uint32_t qwc)
{
    uint32_t pos, nw = qwc * 4;
    if (s->direct_left || s->skip_left) { s->err = E_ALIGN; return; }   /* DIRECT / MPG data never spans a tag */
    vif_cmd(s, rd32(tag + 8), 0);
    if (s->err) return;
    if (s->direct_left || s->skip_left) { s->err = E_ALIGN; return; }
    vif_cmd(s, rd32(tag + 12), 1);
    for (pos = 0; pos < nw && !s->err;) {
        if (s->skip_left) {
            uint32_t k = s->skip_left < nw - pos ? s->skip_left : nw - pos;
            pos += k;
            s->skip_left -= k;
            continue;
        }
        if (s->direct_left) {
            if (pos & 3) { s->err = E_ALIGN; return; }
            gif_qword(s, data + pos * 4);
            pos += 4;
            s->direct_left--;
            continue;
        }
        vif_cmd(s, rd32(data + pos * 4), ((pos + 1) & 3) == 0);
        pos++;
    }
}

/* null / scratchpad / not readable memory / a poisoned (dead) packet (nr_mem.h) */
static const uint8_t *host(uint32_t a)
{
    const uint8_t *p = nr_game_ptr(a, 16);
    if (p && nr_poison_check(p, "nr_im", a)) return NULL;
    return p;
}

/* walk the DMA sub-chain from pkt to its final RET (CNT/NEXT/REF/REFS/CALL/RET/END) */
static int walk(dec *s, uint32_t pkt)
{
    uint32_t tadr = pkt, stack[4], sp = 0, tags = 0;
    for (;;) {
        const uint8_t *t = host(tadr);
        uint32_t lo, hi, qwc, id;
        if (!t || ++tags > 4096) return E_TAG;
        lo = rd32(t); hi = rd32(t + 4);
        qwc = lo & 0xFFFF; id = (lo >> 28) & 7;
        if (qwc && id != 0 && id != 3 && id != 4 && !nr_game_ptr(tadr, 16 + qwc * 16)) return E_TAG;   /* inline payload */
        switch (id) {
        case 1: vif_block(s, t, t + 16, qwc); tadr += 16 + qwc * 16; break;               /* CNT */
        case 2: vif_block(s, t, t + 16, qwc); tadr = hi; break;                            /* NEXT */
        case 3: case 4: {                                                                  /* REF(S) */
            const uint8_t *d = qwc ? (nr_game_ptr(hi, qwc * 16) ? host(hi) : NULL) : NULL;
            if (qwc && !d) return E_TAG;
            vif_block(s, t, d, qwc); tadr += 16; break;
        }
        case 0: {                                                                          /* REFE */
            const uint8_t *d = qwc ? (nr_game_ptr(hi, qwc * 16) ? host(hi) : NULL) : NULL;
            if (qwc && !d) return E_TAG;
            vif_block(s, t, d, qwc);
            return s->err;
        }
        case 5:                                                                            /* CALL */
            vif_block(s, t, t + 16, qwc);
            if (sp >= 4) return E_TAG;
            stack[sp++] = tadr + 16 + qwc * 16; tadr = hi; break;
        case 6:                                                                            /* RET */
            vif_block(s, t, t + 16, qwc);
            if (sp == 0) return s->err;
            tadr = stack[--sp]; break;
        default:                                                                           /* END */
            vif_block(s, t, t + 16, qwc);
            return s->err;
        }
        if (s->err) return s->err;
    }
}

int nr_im_end_prim(uint32_t pkt)
{
    dec s;
    const uint8_t *t;
    uint32_t id, q[16];
    uint64_t start;
    im_rec *r;
    int e, xs = g_xs_pending;
    g_xs_pending = 0;
    if (nr_im_mode() == NRIM_OFF || !pkt) return 0;
    if (!ring_init()) return 0;
    g_st.pkts++;
    t = host(pkt);
    /* the head must hold the marker + RET: a CNT tag with at least 3 qwords */
    if (!t || ((rd32(t) >> 28) & 7) != 1 || (rd32(t) & 0xFFFF) < 3) { g_st.f_small++; return 0; }
    memset(&s, 0, sizeof s);
    start = g_wpos;
    e = walk(&s, pkt);
    img_close(&s);
    if (!e && (s.in_packet || s.direct_left || s.skip_left)) e = E_GIFOPEN;
    if (!e && s.err) e = s.err;
    if (e) {
        g_wpos = start;   /* drop what was written */
        switch (e) {
        case E_TAG: g_st.f_tag++; break;
        case E_VIF: g_st.f_vif++; break;
        case E_ALIGN: g_st.f_align++; break;
        case E_GIFOPEN: g_st.f_gif_open++; break;
        case E_SIGNAL: g_st.f_signal++; break;
        case E_L2H: g_st.f_l2h++; break;
        default: g_st.f_size++; break;
        }
        return 0;
    }
    id = g_next++;
    if (g_next >= 0x7FFFFFFFu) g_next = 1;
    r = &g_recs[id % IM_RECS];
    r->id = id;
    r->n = (uint32_t)(g_wpos - start);
    r->start = start;
    r->mpg = s.mpg;
    r->xs = xs;
    /* the marker: CNT qwc 2 (VIF FLUSHA if the packet had one, DIRECT 2), GIF
     * tag A+D NLOOP 1 EOP, the write of id | bit 63 to GS_NATIVE_MARK; RET */
    q[0] = 0x10000002u; q[1] = 0; q[2] = s.flusha ? 0x13000000u : 0; q[3] = 0x50000002u;
    q[4] = 0x00008001u; q[5] = 0x10000000u; q[6] = 0x0000000Eu; q[7] = 0;
    q[8] = id; q[9] = 0x80000000u; q[10] = GS_NATIVE_MARK; q[11] = 0;
    q[12] = 0x60000000u; q[13] = 0; q[14] = 0; q[15] = 0;
    memcpy((void *)(uintptr_t)pkt, q, sizeof q);
    g_st.replaced++;
    return 1;
}

static int ring_init(void)
{
    if (!g_ring) {
        g_ring = (uint64_t *)malloc((size_t)IM_RING * sizeof *g_ring);
        g_recs = (im_rec *)calloc(IM_RECS, sizeof *g_recs);
        if (!g_ring || !g_recs) { free(g_ring); free(g_recs); g_ring = NULL; g_recs = NULL; g_mode = NRIM_OFF; return 0; }
    }
    return 1;
}

int nr_im_gif(const void *qw, uint32_t nqw, uint8_t out[32])
{
    dec s;
    uint64_t start;
    uint32_t id, i, q[8];
    im_rec *r;
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_GIFIM"); on = !(e && e[0] == '0'); }
    if (!on || nr_im_mode() != NRIM_NATIVE || !nqw || !ring_init()) return 0;
    memset(&s, 0, sizeof s);
    s.allow_mark = 1;
    start = g_wpos;
    for (i = 0; i < nqw && !s.err; i++) gif_qword(&s, (const uint8_t *)qw + 16u * i);
    img_close(&s);
    if (s.err || s.in_packet) {
        g_wpos = start;
        g_st.gif_refused++;
        g_st.gif_ref_why[s.err & 7]++;
        return 0;
    }
    id = g_next++;
    if (g_next >= 0x7FFFFFFFu) g_next = 1;
    r = &g_recs[id % IM_RECS];
    r->id = id;
    r->n = (uint32_t)(g_wpos - start);
    r->start = start;
    r->mpg = s.mpg;
    r->xs = 0;
    /* GIF tag A+D NLOOP 1 EOP, the write of id | bit 63 to GS_NATIVE_MARK */
    q[0] = 0x00008001u; q[1] = 0x10000000u; q[2] = 0x0000000Eu; q[3] = 0;
    q[4] = id; q[5] = 0x80000000u; q[6] = GS_NATIVE_MARK; q[7] = 0;
    memcpy(out, q, 32);
    g_st.gif_pkts++;
    return 1;
}

uint32_t nr_im_gif_rec(const void *qw, uint32_t nqw)
{
#if NR_ONLY
    dec s;
    uint64_t start;
    uint32_t id, i;
    im_rec *r;
    if (!nqw || !ring_init()) return 0;
    memset(&s, 0, sizeof s);
    s.allow_mark = 1;
    s.ee_events = 1;
    start = g_wpos;
    for (i = 0; i < nqw && !s.err; i++) gif_qword(&s, (const uint8_t *)qw + 16u * i);
    img_close(&s);
    if (s.err || s.in_packet) {
        g_wpos = start;
        g_st.gif_refused++;
        g_st.gif_ref_why[s.err & 7]++;
        return 0;
    }
    id = g_next++;
    if (g_next >= 0x7FFFFFFFu) g_next = 1;
    r = &g_recs[id % IM_RECS];
    r->id = id;
    r->n = (uint32_t)(g_wpos - start);
    r->start = start;
    r->mpg = 0;
    r->xs = 0;
    g_st.gif_pkts++;
    return id;
#else
    (void)qw; (void)nqw;
    return 0;
#endif
}

static uint32_t gtag_len(const uint8_t *t, uint32_t *flg, uint32_t *eop)
{
    uint32_t lo = rd32(t), hi = rd32(t + 4), nl = lo & 0x7FFF, nr = (hi >> 28) & 15;
    if (!nr) nr = 16;
    *flg = (hi >> 26) & 3;
    *eop = (lo >> 15) & 1;
    return 1 + (*flg == 0 ? nl * nr : *flg == 1 ? (nl * nr + 1) / 2 : nl);
}
/* qwords of a packet already open (st) up to its EOP; st->open stays 1 when it runs past */
static uint32_t gs_continue(nr_gif_split *st, const uint8_t *q, uint32_t nq)
{
    uint32_t i = 0;
    while (i < nq) {
        if (!st->in_tag) {
            uint32_t lo = rd32(q + 16 * i), hi = rd32(q + 16 * i + 4);
            st->nloop = lo & 0x7FFF;
            st->eop = (lo >> 15) & 1;
            st->flg = (hi >> 26) & 3;
            st->nreg = (hi >> 28) & 15;
            if (!st->nreg) st->nreg = 16;
            st->in_tag = 1;
            i++;
            if (st->flg == 0) st->nloop *= st->nreg;
            else if (st->flg == 1) st->nloop = (st->nloop * st->nreg + 1) / 2;
        } else {
            uint32_t k = st->nloop < nq - i ? st->nloop : nq - i;
            i += k;
            st->nloop -= k;
        }
        if (st->in_tag && st->nloop == 0) {
            st->in_tag = 0;
            if (st->eop) { st->open = 0; return i; }
        }
    }
    st->open = 1;
    return i;
}
static int grow_tmp(nr_gif_split *st, uint32_t bytes)
{
    if (bytes <= st->tcap) return 0;
    {
        uint32_t nc = st->tcap ? st->tcap : 4096;
        uint8_t *nb;
        while (nc < bytes) nc *= 2;
        nb = (uint8_t *)realloc(st->tmp, nc);
        if (!nb) return -1;
        st->tmp = nb;
        st->tcap = nc;
    }
    return 0;
}
void nr_im_gif_stream(nr_gif_split *st, const uint8_t *buf, uint32_t nq, nr_gif_sink sink, void *user)
{
    uint32_t at = 0, raw0 = 0;
    if (st->open) { at = gs_continue(st, buf, nq); st->raw_open++; }
    while (at < nq) {
        uint32_t s = at, i = s, img = 0, complete = 0, flg, eop;
        while (i < nq) {
            i += gtag_len(buf + 16 * i, &flg, &eop);
            if (flg >= 2) img = 1;
            if (eop) { complete = 1; break; }
        }
        if (!complete || i > nq) {
            st->in_tag = 0;
            (void)gs_continue(st, buf + 16 * s, nq - s);
            break;
        }
        at = i;
        st->pkts++;
        if (!img) {
            uint8_t mk[32];
            if (nr_im_gif(buf + 16 * s, at - s, mk)) {
                if (s > raw0) sink(user, buf + 16 * raw0, (s - raw0) * 16);
                sink(user, mk, 32);
                raw0 = at;
                st->recs++;
                continue;
            }
            st->raw++;
            continue;
        }
        {
            /* IMAGE tags (uploads) mixed with drawing tags: the runs of other tags as records
             * (EOP set on a copy of their last tag), the IMAGE tags as they are */
            uint32_t t = s, r0 = s, len = 0;
            while (t < at) {
                len = gtag_len(buf + 16 * t, &flg, &eop);
                if (flg < 2) { t += len; if (t < at) continue; }
                if (t > r0) {
                    uint32_t n = t - r0, last = r0, q, f2, e2;
                    uint8_t mk[32];
                    if (grow_tmp(st, n * 16)) break;
                    memcpy(st->tmp, buf + 16 * r0, n * 16);
                    for (q = r0; q < t; q += gtag_len(buf + 16 * q, &f2, &e2)) last = q;
                    st->tmp[16 * (last - r0) + 1] |= 0x80;   /* EOP (bit 15) */
                    if (nr_im_gif(st->tmp, n, mk)) {
                        if (r0 > raw0) sink(user, buf + 16 * raw0, (r0 - raw0) * 16);
                        sink(user, mk, 32);
                        raw0 = t;
                        st->recs++;
                    }
                }
                if (t >= at) break;
                t += len;
                r0 = t;
            }
            st->split++;
        }
    }
    if (nq > raw0) sink(user, buf + 16 * raw0, (nq - raw0) * 16);
}

/* ---- the GIF channel (PATH3) ---- */
static nr_gif_split g_p3;
static void p3_sink(void *user, const uint8_t *d, uint32_t bytes)
{
    (void)user;
    nr_im_path3_raw(d, bytes / 16);
}
void nr_im_path3(const void *qw, uint32_t nqw)
{
    if (nr_im_mode() == NRIM_NATIVE) nr_im_gif_stream(&g_p3, (const uint8_t *)qw, nqw, p3_sink, NULL);
    else nr_im_path3_raw((const uint8_t *)qw, nqw);
}
void nr_im_path3_stats(FILE *f)
{
    if (!f || !g_p3.pkts) return;
    fprintf(f, "native render GIF channel (PATH3) packets %llu: immediate records %llu, IMAGE packets split %llu, "
               "to the GS input %llu\n", (unsigned long long)g_p3.pkts, (unsigned long long)g_p3.recs,
            (unsigned long long)g_p3.split, (unsigned long long)g_p3.raw);
}

/* ---- GS thread: run a record ----------------------------------------------- */
#ifdef RG_HAVE_GPU
#define IM_MAXP 4096
static gs_vertex g_pv[IM_MAXP * 3];
static int g_pn, g_ptype;          /* batched primitives, their class (GS_PRIM_TRIANGLE / SPRITE) */
static uint64_t g_pattr;           /* the attribute bits they were kicked with */

static uint64_t attr_of(const gpu_gs *gs)
{
    return ((gs->reg[GS_PRMODECONT] & 1) ? gs->reg[GS_PRIM] : gs->reg[GS_PRMODE]) & 0x7F8;
}

static gpu_renderer *g_gr;          /* for the statistics */
#if !NR_ONLY
static uint16_t g_clut_save[512], g_clut_new[512];
#endif
/* registers whose write only stores the value (gs_core.c gs_write_reg) */
static int plain_reg(uint32_t a)
{
    switch (a) {
    case GS_CLAMP_1: case GS_CLAMP_2: case GS_TEX1_1: case GS_TEX1_2: case GS_XYOFFSET_1: case GS_XYOFFSET_2:
    case GS_PRMODECONT: case GS_PRMODE: case GS_TEXCLUT: case GS_SCANMSK: case GS_MIPTBP1_1: case GS_MIPTBP1_2:
    case GS_MIPTBP2_1: case GS_MIPTBP2_2: case GS_TEXA: case GS_FOGCOL: case GS_SCISSOR_1: case GS_SCISSOR_2:
    case GS_ALPHA_1: case GS_ALPHA_2: case GS_DIMX: case GS_DTHE: case GS_COLCLAMP: case GS_TEST_1: case GS_TEST_2:
    case GS_PABE: case GS_FBA_1: case GS_FBA_2: case GS_FRAME_1: case GS_FRAME_2: case GS_ZBUF_1: case GS_ZBUF_2:
        return 1;
    default:
        return 0;
    }
}
static int g_rec_mpg;   /* the record being run carried microcode */
static void flush(gpu_renderer *gr, gpu_gs *gs)
{
    int i, r;
    static int dbg = -1, dbgn, dmpg = -1;
    if (!g_pn) return;
    {
        /* the composite draw-back (records that carried microcode) at an internal scale > 1:
         * the GS draw path, whose upscaled sampling of the character work buffer the native
         * taps do not reproduce for every scene (docs/NATIVE-RENDER.md checkpoint 9 open item);
         * RG_NR_MPGX=native: native at every scale */
        static int mx = -1;
        if (mx < 0) { const char *e = getenv("RG_NR_MPGX"); mx = !(e && !strcmp(e, "native")); }
#if NR_ONLY
        (void)mx;   /* (native-only: no GS draw path; the device draws every state) */
        r = gpu_nr_im_submit(gr, g_pv, g_pn, g_ptype);
#else
        r = (g_rec_mpg && mx && gpu_get_scale(gr) > 1) ? -1 : gpu_nr_im_submit(gr, g_pv, g_pn, g_ptype);
#endif
    }
    if (dbg < 0) { const char *e = getenv("RG_NR_IM_DEBUG"); dbg = e ? atoi(e) : 0; }
    if (dmpg < 0) { const char *e = getenv("RG_NR_IM_DEBUG_MPG"); dmpg = e && e[0] == '1'; }
    {
        /* RG_NR_IM_DEBUG_FBP=bp[:N] (measurement): the next N batches (default 64) drawing into FBP bp
         * (block pointer): state and every primitive's vertices */
        static int df = -2, dfn;
        static uint32_t dfbp;
        if (df == -2) {
            const char *e = getenv("RG_NR_IM_DEBUG_FBP");
            df = -1;
            if (e) { const char *c = strchr(e, ':'); dfbp = (uint32_t)atoi(e); df = c ? atoi(c + 1) : 64; }
        }
        if (df > 0 && dfn < df) {
            int c = (int)BITS(g_pattr, 9, 1);
            if (BITS(gs->reg[GS_FRAME_1 + c], 0, 9) * 32u == dfbp) {
                int q, nv = g_ptype == GS_PRIM_SPRITE ? 2 : 3;
                dfn++;
                fprintf(stderr, "nr im fbp batch %d: type %d n %d attr %03llX rc %d FRAME %016llX TEST %016llX ALPHA %016llX TEX0 %016llX "
                                "TEX1 %016llX CLAMP %016llX XYOFF %016llX SCISSOR %016llX\n",
                        dfn, g_ptype, g_pn, (unsigned long long)g_pattr, r, (unsigned long long)gs->reg[GS_FRAME_1 + c],
                        (unsigned long long)gs->reg[GS_TEST_1 + c], (unsigned long long)gs->reg[GS_ALPHA_1 + c],
                        (unsigned long long)gs->reg[GS_TEX0_1 + c], (unsigned long long)gs->reg[GS_TEX1_1 + c],
                        (unsigned long long)gs->reg[GS_CLAMP_1 + c], (unsigned long long)gs->reg[GS_XYOFFSET_1 + c],
                        (unsigned long long)gs->reg[GS_SCISSOR_1 + c]);
                for (q = 0; q < g_pn && q < 64; q++) {
                    int j;
                    fprintf(stderr, "   p%d:", q);
                    for (j = 0; j < nv; j++) {
                        const gs_vertex *p = &g_pv[q * 3 + j];
                        fprintf(stderr, " (%u,%u z %u uv %u,%u st %g,%g q %g c %02X%02X%02X%02X)", p->x, p->y, p->z, p->u, p->v, p->s,
                                p->t, p->q, p->r, p->g, p->b, p->a);
                    }
                    fprintf(stderr, "\n");
                }
            }
        }
    }
    {
        /* RG_NR_IM_DEBUG_TEX0=hex (measurement): every batch with that TEX0 (context 1 or 2):
         * its CLUT (first 16 cells, both halves) and each primitive's colour */
        static int dt = -1;
        static uint64_t dtex;
        if (dt < 0) { const char *e = getenv("RG_NR_IM_DEBUG_TEX0"); dt = e != NULL; if (e) dtex = strtoull(e, NULL, 16); }
        if (dt && (gs->reg[GS_TEX0_1] == dtex || gs->reg[GS_TEX0_2] == dtex)) {
            int q;
            fprintf(stderr, "nr im tex0 batch rc %d n %d clut:", r, g_pn);
            for (q = 0; q < 16; q++) fprintf(stderr, " %04X%04X", gs->clut[q + 256], gs->clut[q]);
            fprintf(stderr, " TEXA %016llX | cols", (unsigned long long)gs->reg[GS_TEXA]);
            for (q = 0; q < g_pn && q < 64; q++) {
                const gs_vertex *p = &g_pv[q * 3 + (g_ptype == GS_PRIM_SPRITE ? 1 : 2)];
                fprintf(stderr, " %02X%02X%02X%02X", p->r, p->g, p->b, p->a);
            }
            fprintf(stderr, "\n");
        }
    }
    if (dbg && dbgn < dbg && (!dmpg || g_rec_mpg)) {
        /* RG_NR_IM_DEBUG=N: the first N batches (state and first primitive) */
        int c = (int)BITS(g_pattr, 9, 1);
        const gs_vertex *p = g_pv;
        dbgn++;
        fprintf(stderr, "nr im batch %d: %s n %d attr %03llX rc %d FRAME %016llX TEST %016llX ALPHA %016llX TEX0 %016llX "
                        "TEX1 %016llX CLAMP %016llX XYOFF %016llX | v0 %u,%u uv %u,%u st %g,%g q %g rgba %02X%02X%02X%02X | "
                        "v1 %u,%u uv %u,%u st %g,%g q %g\n",
                dbgn, g_ptype == GS_PRIM_SPRITE ? "sprite" : "tri", g_pn, (unsigned long long)g_pattr, r,
                (unsigned long long)gs->reg[GS_FRAME_1 + c], (unsigned long long)gs->reg[GS_TEST_1 + c],
                (unsigned long long)gs->reg[GS_ALPHA_1 + c], (unsigned long long)gs->reg[GS_TEX0_1 + c],
                (unsigned long long)gs->reg[GS_TEX1_1 + c], (unsigned long long)gs->reg[GS_CLAMP_1 + c],
                (unsigned long long)gs->reg[GS_XYOFFSET_1 + c], p[0].x, p[0].y, p[0].u, p[0].v, p[0].s, p[0].t, p[0].q,
                p[0].r, p[0].g, p[0].b, p[0].a, p[1].x, p[1].y, p[1].u, p[1].v, p[1].s, p[1].t, p[1].q);
    }
    if (r == 0) { g_st.nat_batches++; g_st.nat_prims += (uint64_t)g_pn; }
    else if (r > 0) g_st.skip_batches++;
    else {
#if NR_ONLY
        (void)i;
        g_st.emu_batches++;   /* (native-only: the device refused; nothing drawn) */
        g_st.emu_prims += (uint64_t)g_pn;
#else
        /* not covered natively: the GS draw path (exact), primitive by primitive */
        int nv = g_ptype == GS_PRIM_SPRITE ? 2 : 3;
        for (i = 0; i < g_pn; i++) gs_draw_kick(gs, &g_pv[i * 3], nv, g_ptype);
        g_st.emu_batches++;
        g_st.emu_prims += (uint64_t)g_pn;
#endif
    }
    g_pn = 0;
}

/* lines through the native pipeline as one-pixel quads (gpu_nr_im_submit, checkpoint 9);
 * RG_NR_IMLINES=0: the GS draw path */
static int lines_native(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_IMLINES"); on = !(e && e[0] == '0') || NR_ONLY; }
    return on;
}
static void vertex(gpu_renderer *gr, gpu_gs *gs, uint32_t addr, uint64_t data)
{
    static const int need[8] = { 1, 2, 2, 3, 3, 3, 2, 0 };
    gs_vertex nv;
    uint64_t rgbaq = gs->reg[GS_RGBAQ], st = gs->reg[GS_ST], uv = gs->reg[GS_UV];
    uint32_t f32;
    int type, xyzf = addr == GS_XYZF2 || addr == GS_XYZF3, draw = addr == GS_XYZF2 || addr == GS_XYZ2;
    gs->reg[addr] = data;
    if (xyzf) gs->reg[GS_FOG] = (uint64_t)BITS(data, 56, 8) << 56;
    nv.x = (uint16_t)BITS(data, 0, 16);
    nv.y = (uint16_t)BITS(data, 16, 16);
    nv.z = xyzf ? BITS(data, 32, 24) : BITS(data, 32, 32);
    nv.f = (uint8_t)(xyzf ? BITS(data, 56, 8) : BITS(gs->reg[GS_FOG], 56, 8));
    nv.r = (uint8_t)BITS(rgbaq, 0, 8); nv.g = (uint8_t)BITS(rgbaq, 8, 8);
    nv.b = (uint8_t)BITS(rgbaq, 16, 8); nv.a = (uint8_t)BITS(rgbaq, 24, 8);
    f32 = BITS(rgbaq, 32, 32); memcpy(&nv.q, &f32, 4);
    f32 = BITS(st, 0, 32); memcpy(&nv.s, &f32, 4);
    f32 = BITS(st, 32, 32); memcpy(&nv.t, &f32, 4);
    nv.u = (uint16_t)BITS(uv, 0, 14); nv.v = (uint16_t)BITS(uv, 16, 14);
    type = (int)BITS(gs->reg[GS_PRIM], 0, 3);
    if (need[type] == 0) return;
    gs->vq[gs->vq_n++] = nv;
    gs->strip_n++;
    if (gs->vq_n < need[type]) return;
    if (draw) {
        int cls = type >= GS_PRIM_TRIANGLE && type <= GS_PRIM_TRIFAN ? GS_PRIM_TRIANGLE : type == GS_PRIM_SPRITE ? GS_PRIM_SPRITE
                : (type == GS_PRIM_LINE || type == GS_PRIM_LINESTRIP) && lines_native() ? GS_PRIM_LINE
                : type == GS_PRIM_POINT && lines_native() ? GS_PRIM_POINT : -1;
        if (cls < 0) {
            /* points (and lines with RG_NR_IMLINES=0): the GS draw path */
            flush(gr, gs);
#if !NR_ONLY
            gs_draw_kick(gs, gs->vq, need[type], type);
#endif
            g_st.lines++;
        } else {
            uint64_t a = attr_of(gs);
            if (g_pn && (cls != g_ptype || a != g_pattr || g_pn >= IM_MAXP)) flush(gr, gs);
            g_ptype = cls;
            g_pattr = a;
            memcpy(&g_pv[g_pn * 3], gs->vq, (size_t)need[type] * sizeof(gs_vertex));
            if (cls == GS_PRIM_TRIANGLE && !(a & 8)) {
                /* flat shading: the colour of the last vertex */
                gs_vertex *p = &g_pv[g_pn * 3];
                p[0].r = p[1].r = p[2].r; p[0].g = p[1].g = p[2].g;
                p[0].b = p[1].b = p[2].b; p[0].a = p[1].a = p[2].a;
            }
            g_pn++;
            g_st.prims++;
        }
    }
    switch (type) {
    case GS_PRIM_LINESTRIP: gs->vq[0] = gs->vq[1]; gs->vq_n = 1; break;
    case GS_PRIM_TRISTRIP: gs->vq[0] = gs->vq[1]; gs->vq[1] = gs->vq[2]; gs->vq_n = 2; break;
    case GS_PRIM_TRIFAN: gs->vq[1] = gs->vq[2]; gs->vq_n = 2; break;
    default: gs->vq_n = 0; break;
    }
}

void nr_im_marker(gpu_renderer *gr, gpu_gs *gs, uint32_t id)
{
    const im_rec *r;
    uint64_t pos, end;
    int replay = nr_im_mode() == NRIM_REPLAY && !NR_ONLY;
    int outer_mpg = g_rec_mpg, outer_pn = g_pn;   /* (a record's marker can run another: native-only) */
    if (!g_recs) return;
    if (outer_pn) flush(gr, gs);
    r = &g_recs[id % IM_RECS];
    if (r->id != id || __atomic_load_n(&g_wpos, __ATOMIC_ACQUIRE) - r->start > IM_RING - (IM_RING >> 3)) {
        g_st.gs_stale++;
        return;
    }
    g_st.gs_runs++;
    g_gr = gr;
    g_rec_mpg = r->mpg;
    g_pn = 0;
    gpu_set_im_xfree(gr, r->xs);
    pos = r->start;
    end = r->start + r->n;
    while (pos < end) {
        uint64_t h = g_ring[pos & (IM_RING - 1)];
        uint32_t kind = (uint32_t)(h >> 60);
        pos++;
        if (kind == C_REG) {
            uint32_t addr = (uint32_t)(h & 0x7F);
            uint64_t data = g_ring[pos & (IM_RING - 1)];
            pos++;
            if (replay) { GS_WRITE_REG(gs, addr, data); continue; }
            switch (addr) {
            case GS_XYZ2: case GS_XYZF2: case GS_XYZ3: case GS_XYZF3:
                vertex(gr, gs, addr, data);
                break;
            case GS_RGBAQ: case GS_ST: case GS_UV: case GS_FOG:
                gs->reg[addr] = data;
                break;
            case GS_PRIM:
                if (g_pn && (((data & 0x7F8) != (g_pattr & 0x7F8) && (gs->reg[GS_PRMODECONT] & 1)))) flush(gr, gs);
                GS_WRITE_REG(gs, addr, data);
                break;
            case GS_TEX0_1: case GS_TEX0_2: case GS_TEX2_1: case GS_TEX2_2:
#if NR_ONLY
                /* the batch goes on when the write leaves the context's TEX0 / TEX2 and the CLUT as
                 * they are (the game reloads the same palette before every glyph or sprite) */
                if (g_pn) {
                    int c = (int)((addr - GS_TEX0_1) & 1);
                    uint64_t t0 = gs->reg[GS_TEX0_1 + c];
                    uint64_t mask = (0x3Full << 20) | (~0ull << 37);
                    uint64_t nt0 = addr <= GS_TEX0_2 ? data : ((t0 & ~mask) | (data & mask));
                    if (nt0 != t0 || (addr >= GS_TEX2_1 && gs->reg[addr] != data) || nr_gs_clut_would_change(gs, addr, data))
                        flush(gr, gs);
                    else
                        g_st.kept_batches++;
                }
                GS_WRITE_REG(gs, addr, data);
#else
                if (g_pn) {
                    /* the game reloads the same palette before every glyph or
                     * sprite: when the register and the CLUT come out unchanged,
                     * the batch goes on (else it is drawn with the old CLUT) */
                    uint64_t t0 = gs->reg[GS_TEX0_1 + ((addr - GS_TEX0_1) & 1)], tw = gs->reg[addr];
                    uint64_t lc0 = gs->stats.clut_loads;
                    memcpy(g_clut_save, gs->clut, sizeof g_clut_save);
                    gs_write_reg(gs, addr, data);
                    if (gs->reg[addr] != tw || gs->reg[GS_TEX0_1 + ((addr - GS_TEX0_1) & 1)] != t0 ||
                        memcmp(g_clut_save, gs->clut, sizeof g_clut_save)) {
                        uint64_t nt0 = gs->reg[GS_TEX0_1 + ((addr - GS_TEX0_1) & 1)], ntw = gs->reg[addr];
                        uint64_t lc1 = gs->stats.clut_loads;
                        memcpy(g_clut_new, gs->clut, sizeof g_clut_new);
                        memcpy(gs->clut, g_clut_save, sizeof g_clut_save);
                        gs->reg[GS_TEX0_1 + ((addr - GS_TEX0_1) & 1)] = t0;
                        gs->reg[addr] = tw;
                        gs->stats.clut_loads = lc0;    /* (the renderer re-reads the CLUT when the count moves) */
                        flush(gr, gs);
                        gs->stats.clut_loads = lc1;
                        memcpy(gs->clut, g_clut_new, sizeof g_clut_new);
                        gs->reg[GS_TEX0_1 + ((addr - GS_TEX0_1) & 1)] = nt0;
                        gs->reg[addr] = ntw;
                    } else {
                        g_st.kept_batches++;
                    }
                } else {
                    gs_write_reg(gs, addr, data);
                }
#endif
                break;
            case GS_TEXFLUSH:
                break;      /* (no effect in the model; the batch goes on) */
            default:
                if (g_pn && plain_reg(addr) && gs->reg[addr] == data) { g_st.kept_batches++; break; }   /* no change */
                flush(gr, gs);
                GS_WRITE_REG(gs, addr, data);
                break;
            }
        } else if (kind == C_IMAGE) {
            uint32_t n = (uint32_t)(h & 0xFFFFFFFu), k;
            static uint8_t *buf;
            static uint32_t cap;
            flush(gr, gs);
            if (n * 16u > cap) {
                free(buf);
                cap = n * 16u;
                buf = (uint8_t *)malloc(cap);
                if (!buf) { cap = 0; gpu_set_im_xfree(gr, 0); return; }
            }
            for (k = 0; k < n * 2; k++) {
                uint64_t w = g_ring[(pos + k) & (IM_RING - 1)];
                memcpy(buf + 8 * k, &w, 8);
            }
            pos += (uint64_t)n * 2;
#if NR_ONLY
            nr_gs_image(gs, buf, n);
#else
            gs_image_write(gs, GS_PATH2, buf, n);
#endif
        } else {
            break;
        }
    }
    flush(gr, gs);
    gpu_set_im_xfree(gr, 0);
    g_rec_mpg = outer_mpg;
}

/* (nr_interp.c) the record is still in the ring: a pass may run it again */
int nr_im_rec_valid(uint32_t id)
{
    const im_rec *r;
    if (!g_recs) return 0;
    r = &g_recs[id % IM_RECS];
    return r->id == id && __atomic_load_n(&g_wpos, __ATOMIC_ACQUIRE) - r->start <= IM_RING - (IM_RING >> 3);
}
/* (nr_interp.c census) FNV of the record's state writes and IMAGE sizes, its vertex writes
 * (XYZ*, RGBAQ, ST, UV, FOG) counted and hashed apart */
void nr_im_rec_info(uint32_t id, uint64_t *sig, uint32_t *nvtx, uint64_t *vhash)
{
    const im_rec *r;
    uint64_t pos, end, s = 1469598103934665603ull, v = 1469598103934665603ull;
    uint32_t nv = 0;
    *sig = *vhash = 0;
    *nvtx = 0;
    if (!nr_im_rec_valid(id)) return;
    r = &g_recs[id % IM_RECS];
    pos = r->start;
    end = r->start + r->n;
    while (pos < end) {
        uint64_t h = g_ring[pos & (IM_RING - 1)];
        uint32_t kind = (uint32_t)(h >> 60);
        pos++;
        if (kind == C_REG) {
            uint32_t addr = (uint32_t)(h & 0x7F);
            uint64_t data = g_ring[pos & (IM_RING - 1)];
            pos++;
            switch (addr) {
            case GS_XYZ2: case GS_XYZF2: case GS_XYZ3: case GS_XYZF3:
                nv++;
                /* fall through */
            case GS_RGBAQ: case GS_ST: case GS_UV: case GS_FOG:
                v = (v ^ addr) * 1099511628211ull;
                v = (v ^ data) * 1099511628211ull;
                break;
            default:
                s = (s ^ addr) * 1099511628211ull;
                s = (s ^ data) * 1099511628211ull;
                break;
            }
        } else if (kind == C_IMAGE) {
            uint32_t n = (uint32_t)(h & 0xFFFFFFFu);
            s = (s ^ (0x100000000ull | n)) * 1099511628211ull;
            pos += (uint64_t)n * 2;
        } else {
            break;
        }
    }
    *sig = s;
    *vhash = v;
    *nvtx = nv;
}
#else
void nr_im_marker(struct gpu_renderer *gr, gpu_gs *gs, uint32_t id) { (void)gr; (void)gs; (void)id; }
int nr_im_rec_valid(uint32_t id) { (void)id; return 0; }
void nr_im_rec_info(uint32_t id, uint64_t *sig, uint32_t *nvtx, uint64_t *vhash) { (void)id; *sig = *vhash = 0; *nvtx = 0; }
#endif

void nr_im_stats(FILE *f)
{
    if (!f || (!g_st.pkts && !g_st.gif_pkts)) return;
    fprintf(f, "native render immediate (%s): packets %llu, replaced %llu (kept: tag %llu, VIF code %llu, alignment %llu, "
               "GIF packet open %llu, SIGNAL/FINISH/LABEL %llu, local->host %llu, head too small %llu, size %llu); "
               "register writes %llu, IMAGE qwords %llu; GS: runs %llu (stale %llu), primitives %llu: native %llu in %llu batches, "
               "GS draw path %llu in %llu batches, nothing to draw %llu batches, points/lines %llu; batches kept across unchanged state writes %llu\n",
            nr_im_mode() == NRIM_REPLAY ? "replay" : "native",
            (unsigned long long)g_st.pkts, (unsigned long long)g_st.replaced, (unsigned long long)g_st.f_tag,
            (unsigned long long)g_st.f_vif, (unsigned long long)g_st.f_align, (unsigned long long)g_st.f_gif_open,
            (unsigned long long)g_st.f_signal, (unsigned long long)g_st.f_l2h, (unsigned long long)g_st.f_small,
            (unsigned long long)g_st.f_size, (unsigned long long)g_st.regs, (unsigned long long)g_st.image_qw,
            (unsigned long long)g_st.gs_runs, (unsigned long long)g_st.gs_stale, (unsigned long long)g_st.prims,
            (unsigned long long)g_st.nat_prims, (unsigned long long)g_st.nat_batches, (unsigned long long)g_st.emu_prims,
            (unsigned long long)g_st.emu_batches, (unsigned long long)g_st.skip_batches, (unsigned long long)g_st.lines,
            (unsigned long long)g_st.kept_batches);
    if (g_st.mpg) fprintf(f, "native render immediate: VU microcode uploads (MPG) dropped %llu\n", (unsigned long long)g_st.mpg);
    if (g_st.gif_pkts || g_st.gif_refused)
        fprintf(f, "native render immediate: GIF streams as records (VU1 program kicks, DIRECT packets) %llu (refused %llu: "
                   "open packet %llu, VIF %llu, SIGNAL/FINISH/LABEL/marker %llu, local->host %llu, size %llu)\n",
                (unsigned long long)g_st.gif_pkts, (unsigned long long)g_st.gif_refused,
                (unsigned long long)g_st.gif_ref_why[0], (unsigned long long)g_st.gif_ref_why[E_VIF],
                (unsigned long long)g_st.gif_ref_why[E_SIGNAL], (unsigned long long)g_st.gif_ref_why[E_L2H],
                (unsigned long long)g_st.gif_ref_why[E_SIZE & 7]);
#ifdef RG_HAVE_GPU
    if (g_gr) {
        static const char *nm[12] = { "CT16 frame", "dest. alpha test", "partial FBMSK", "AFAIL", "blend C=Ad",
                                      "COLCLAMP/PABE/SCANMSK", "frame-Z alias", "texture feedback", "mipmaps",
                                      "region clamp", "depth texture", "backend" };
        const gpu_nr_stats *ns = gpu_nr_get_stats(g_gr);
        int k;
        fprintf(f, "native render immediate: GS draw path primitives by reason:");
        for (k = 0; k < 12; k++)
            if (ns->im_why[k]) fprintf(f, " %s %llu", nm[k], (unsigned long long)ns->im_why[k]);
        fprintf(f, "\n");
    }
#endif
    {
        int k;
        for (k = 0; k < 128; k++)
            if (g_st.vifcmd[k]) fprintf(f, "native render immediate: kept for VIF command %02X: %llu\n", k, (unsigned long long)g_st.vifcmd[k]);
    }
}
