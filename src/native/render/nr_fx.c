/* SPDX-License-Identifier: CC0-1.0 */
/* The frame's draw list without the DMAC / VIF1 models (docs/NATIVE-RENDER.md "Frame chain
 * walker").
 *
 * GfxEndFrame_141c20 hands the frame's DMA chain to Vif1DmaStart_15e070, which kicks it on
 * DMA channel 1 (sceDmaSend, tag transfer on).  With the native renderer every VU1 program of
 * the frame is native (model meshes, shadow volumes, line strands, refraction, composite;
 * "VU1 off the default path"), so what the chain still carries for the hardware is only GS
 * input: the VIF DIRECT packets (material / environment state, texture uploads, the native
 * draw markers, immediate records' markers).  The walker reads the chain once on the EE at the
 * send, like the DMAC would (CNT / NEXT / REF / REFS / REFE / CALL / RET / END, the two VIF
 * words of every tag, then its data), parses the VIF command stream for sizes, and hands the
 * DIRECT payloads, in order, to the GS input the VIF would have fed (one buffer per chain).
 * Every other VIF command (UNPACK, MPG, STCYCL / BASE / OFFSET / ITOP / STMOD / MSKPATH3 /
 * STMASK / STROW / STCOL / MARK, and a still-emulated VU program start) goes to the fwd sink
 * whole: the runtime hands it to the VIF1 / VU1 models while they are linked (VU memory stays
 * exact for a fallback program; the DIRECT data before a program start is fed first), and a
 * build without VU1 passes NULL: dropped.  NOP / FLUSH* are dropped.
 *
 * Left to the DMAC (counted): a scratchpad / bad address, an invalid VIF code, a payload left
 * open at the end, more than 2^20 tags (a validation pass runs first; nothing is fed unless the
 * whole chain is walkable).
 *
 * The kernel sees what the DMAC model makes it see: the channel-1 completion (D_STAT.CIS1),
 * and for the VIF i-bit (the end-of-frame NOP) the VIF1 interrupt posted one cycle after the
 * kick (dmac.c vif_irq: Vif1IntcHandler_15e170 latches T0 after GfxEndFrame's reset).  The
 * caller (libdma.c sceDmaSend) applies those; nr_fx_walk reports them.
 *
 * RG_NR_FX=0: every chain through the DMAC / VIF models (the comparison twin). */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nr.h"
#include "nr_im.h"
#include "nr_mem.h"


static uint32_t rd32(const uint8_t *p) { uint32_t v; memcpy(&v, p, 4); return v; }

static struct {
    uint64_t chains, walked, qwords, direct_qw, unpack_w, mpg_w, tags, irq, vu_starts, vu_chains;
    uint64_t f_addr, f_vif, f_open, f_tags;
} g_st;

int nr_fx_on(void)
{
    static int on = -1;
    if (on < 0) {
        const char *e = getenv("RG_NR_FX");
        on = nr_mode() == NR_NATIVE && !(e && e[0] == '0');
    }
    return on;
}

enum { FX_OK = 0, FX_ADDR, FX_VIF, FX_OPEN, FX_TAGS };

typedef struct walker {
    int exec;               /* 0: the validation pass (no side effects), 1: run */
    uint32_t cl, wl;
    uint32_t need;          /* payload words of the current command still to consume */
    int kind;               /* the current command: K_DROP, K_DIRECT, K_VU */
    int irq, err, vu_starts;
    nr_fx_sink sink, fwd;
    void *user, *fwd_user;
    uint8_t *buf;           /* DIRECT payloads not yet handed to the GS, in order */
    uint32_t len, cap;
    uint32_t *vb;           /* the VU command being collected (code + payload) */
    uint32_t vn, vcap;
    uint64_t direct_bytes;
} walker;
enum { K_DROP = 0, K_DIRECT, K_VU };

static uint32_t unpack_words(uint32_t code, uint32_t cl, uint32_t wl)
{
    uint32_t cmd = (code >> 24) & 0x7F, vn = (cmd >> 2) & 3, vl = cmd & 3;
    uint32_t num = (code >> 16) & 0xFF, n, bits;
    if (num == 0) num = 256;
    if (wl <= cl || cl == 0) n = num;                       /* skipping write (or CL 0: treated as 1:1) */
    else n = cl * (num / wl) + (num % wl < cl ? num % wl : cl);   /* filling write: CL of every WL from data */
    bits = n * (vn + 1) * (32u >> vl);
    return (bits + 31) / 32;
}

static int grow(void **p, uint32_t *cap, uint32_t want, uint32_t unit, uint32_t first)
{
    uint32_t nc = *cap ? *cap : first;
    void *nb;
    if (want <= *cap) return 0;
    while (nc < want) nc *= 2;
    nb = realloc(*p, (size_t)nc * unit);
    if (!nb) return -1;
    *p = nb;
    *cap = nc;
    return 0;
}

/* DIRECT payloads: drawing packets as immediate records, the rest to the GS input (nr_im.h
 * nr_im_gif_stream, checkpoint 9); RG_NR_FXIM=0: all of it to the GS input */
static nr_gif_split g_gi;
static int fxim_on(void)
{
    static int on = -1;
    if (on < 0) { const char *e = getenv("RG_NR_FXIM"); on = !(e && e[0] == '0') && nr_im_mode() == NRIM_NATIVE; }
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
    on = 0;   /* (native-only: the sink is the native GIF input, which makes the records itself) */
#endif
    return on;
}
static void flush_direct(walker *w)
{
    if (w->len && w->sink) {
        if (fxim_on() && !(w->len & 15)) nr_im_gif_stream(&g_gi, w->buf, w->len / 16, w->sink, w->user);
        else w->sink(w->user, w->buf, w->len);
    }
    w->direct_bytes += w->len;
    w->len = 0;
}

static void vu_word(walker *w, uint32_t v)
{
    if (!w->fwd) return;
    if (grow((void **)&w->vb, &w->vcap, w->vn + 1, 4, 1024)) { w->err = FX_OPEN; return; }
    w->vb[w->vn++] = v;
}
static void vu_end(walker *w)
{
    if (w->fwd && w->vn) w->fwd(w->fwd_user, (const uint8_t *)w->vb, w->vn * 4);
    w->vn = 0;
}

/* VU program starts by address (MSCNT: 0xFFFF), for the stats */
static struct { uint32_t pc; uint64_t n; } g_ms[32];
static void mscal_note(uint32_t pc)
{
    int i;
    for (i = 0; i < 32; i++) {
        if (g_ms[i].n && g_ms[i].pc != pc) continue;
        g_ms[i].pc = pc;
        g_ms[i].n++;
        return;
    }
}

/* $RG_NR_FXCENSUS=1: the VU1 microprogram census (docs/NATIVE-RENDER.md "INSECT VU1 census").
 * Every MPG is identified by (load address, size, FNV of its code, EE address of its payload);
 * the resident segments of a 2,048-instruction shadow say which upload a program start runs
 * (the segment holding the start pc; MSCNT = the last pc + 1 is approximated by the last start's
 * segment).  $RG_NR_FXCENSUS_DIR=dir also writes every distinct upload as
 * mpg_<dest>_<hash>.bin (raw microcode, for rg-vucensus-style listings). */
#define VC_SEG 64
#define VC_KEY 256
static struct {
    int on;
    uint16_t owner[2048];            /* resident segment per instruction (index + 1), 0 = none */
    struct { uint32_t dest, n; uint64_t hash; uint32_t src; uint64_t uploads; } seg[VC_SEG];
    int nseg;
    struct { uint64_t hash; uint32_t pc, cmd; uint64_t n; } key[VC_KEY];
    int nkey, last_seg;
    uint32_t mpg_dest, mpg_n, mpg_got, mpg_src;
    uint32_t mpg_buf[512];
} g_vc;

static int vc_on(void)
{
    if (!g_vc.on) {
        const char *e = getenv("RG_NR_FXCENSUS");
        g_vc.on = (e && e[0] && e[0] != '0') ? 1 : -1;
    }
    return g_vc.on > 0;
}

static uint64_t vc_fnv(const uint8_t *p, uint32_t n)
{
    uint64_t h = 1469598103934665603ull;
    while (n--) { h ^= *p++; h *= 1099511628211ull; }
    return h;
}

static void vc_mpg_done(void)
{
    uint64_t h = vc_fnv((const uint8_t *)g_vc.mpg_buf, g_vc.mpg_n * 8);
    int i;
    for (i = 0; i < g_vc.nseg; i++)
        if (g_vc.seg[i].hash == h && g_vc.seg[i].dest == g_vc.mpg_dest && g_vc.seg[i].n == g_vc.mpg_n) break;
    if (i == g_vc.nseg) {
        if (g_vc.nseg >= VC_SEG) return;
        g_vc.nseg++;
        g_vc.seg[i].dest = g_vc.mpg_dest;
        g_vc.seg[i].n = g_vc.mpg_n;
        g_vc.seg[i].hash = h;
        g_vc.seg[i].src = g_vc.mpg_src;
        {
            const char *d = getenv("RG_NR_FXCENSUS_DIR");
            if (d && d[0]) {
                char path[512];
                FILE *f;
                snprintf(path, sizeof path, "%s/mpg_%04x_%016llx.bin", d, g_vc.mpg_dest * 8, (unsigned long long)h);
                f = fopen(path, "wb");
                if (f) { fwrite(g_vc.mpg_buf, 8, g_vc.mpg_n, f); fclose(f); }
            }
        }
    }
    g_vc.seg[i].uploads++;
    {
        uint32_t k;
        for (k = 0; k < g_vc.mpg_n; k++) g_vc.owner[(g_vc.mpg_dest + k) & 2047] = (uint16_t)(i + 1);
    }
}

static void vc_start(uint32_t cmd, uint32_t pc)
{
    int s = cmd == 0x17 ? g_vc.last_seg : (int)g_vc.owner[pc & 2047] - 1, i;
    uint64_t h = s >= 0 ? g_vc.seg[s].hash : 0;
    g_vc.last_seg = s;
    for (i = 0; i < g_vc.nkey; i++)
        if (g_vc.key[i].hash == h && g_vc.key[i].pc == pc && g_vc.key[i].cmd == cmd) { g_vc.key[i].n++; return; }
    if (g_vc.nkey >= VC_KEY) return;
    g_vc.key[g_vc.nkey].hash = h;
    g_vc.key[g_vc.nkey].pc = pc;
    g_vc.key[g_vc.nkey].cmd = cmd;
    g_vc.key[g_vc.nkey].n = 1;
    g_vc.nkey++;
}

/* one VIF code */
static void code(walker *w, uint32_t c)
{
    uint32_t cmd = (c >> 24) & 0x7F, imm = c & 0xFFFF, num = (c >> 16) & 0xFF;
    if (c & 0x80000000u) w->irq = 1;
    w->kind = K_VU;
    w->need = 0;
    if (cmd >= 0x60) {
        w->need = unpack_words(c, w->cl, w->wl);
        if (w->exec) g_st.unpack_w += w->need;
    } else {
        switch (cmd) {
        case 0x00: case 0x10: case 0x11: case 0x13: w->kind = K_DROP; return;   /* NOP, FLUSHE / FLUSH / FLUSHA */
        case 0x01: w->cl = imm & 0xFF; w->wl = (imm >> 8) & 0xFF; break;
        case 0x02: case 0x03: case 0x04: case 0x05: case 0x06: case 0x07: break;
        case 0x14: case 0x15: case 0x17:
            /* a VU program start (an emulated VU1 program): what the GS got before it first */
            if (w->exec) {
                flush_direct(w);
                w->vu_starts++;
                mscal_note(cmd == 0x17 ? 0xFFFF : imm);
                if (vc_on()) vc_start(cmd, cmd == 0x17 ? 0xFFFF : imm);
            }
            break;
        case 0x20: w->need = 1; break;
        case 0x30: case 0x31: w->need = 4; break;
        case 0x4A:
            w->need = (num ? num : 256u) * 2u;
            if (w->exec) {
                g_st.mpg_w += w->need;
                if (vc_on()) { g_vc.mpg_dest = imm; g_vc.mpg_n = num ? num : 256u; g_vc.mpg_got = 0; g_vc.mpg_src = 0; }
            }
            break;
        case 0x50: case 0x51: w->need = (imm ? imm : 65536u) * 4u; w->kind = K_DIRECT; return;
        default: w->err = FX_VIF; return;
        }
    }
    /* VU work goes to the VIF / VU models (fwd) without the i bit: the end-of-frame
     * interrupt is posted by the caller, after the kick, like the DMAC's deferral */
    if (w->exec) {
        vu_word(w, c & 0x7FFFFFFFu);
        if (!w->need) vu_end(w);
    }
}

/* words in the VIF stream order (the tag's two words, then its data) */
static void words(walker *w, const uint8_t *p, uint32_t n)
{
    uint32_t i = 0;
    while (i < n && !w->err) {
        if (w->need) {
            uint32_t k = w->need < n - i ? w->need : n - i, j;
            if (w->exec) {
                if (w->kind == K_DIRECT) {
                    if (grow((void **)&w->buf, &w->cap, w->len + k * 4, 1, 1u << 20)) { w->err = FX_OPEN; return; }
                    memcpy(w->buf + w->len, p + i * 4, k * 4);
                    w->len += k * 4;
                } else if (w->kind == K_VU && w->fwd) {
                    for (j = 0; j < k; j++) vu_word(w, rd32(p + (i + j) * 4));
                }
                if (w->kind == K_VU && g_vc.on > 0 && g_vc.mpg_n && w->vb && w->vn &&
                    ((w->vb[0] >> 24) & 0x7F) == 0x4A) {
                    if (!g_vc.mpg_got) g_vc.mpg_src = (uint32_t)(uintptr_t)(p + i * 4);
                    for (j = 0; j < k && g_vc.mpg_got < g_vc.mpg_n * 2; j++) g_vc.mpg_buf[g_vc.mpg_got++] = rd32(p + (i + j) * 4);
                    if (w->need == k) { vc_mpg_done(); g_vc.mpg_n = 0; }
                }
            }
            w->need -= k;
            i += k;
            if (!w->need && w->exec && w->kind == K_VU) vu_end(w);
            continue;
        }
        code(w, rd32(p + i * 4));
        i++;
    }
}

/* bus error / scratchpad / not readable memory / a poisoned (dead) packet: the DMAC's job
 * (nr_mem.h; an unreadable address used to fault here) */
static const uint8_t *host(uint32_t a, uint32_t bytes)
{
    const uint8_t *p = nr_game_ptr(a, bytes ? bytes : 16);
    if (p && nr_poison_check(p, "nr_fx (frame chain)", a)) return NULL;
    return p;
}

static walker g_w;

static int walk(walker *w, uint32_t tadr, int tte, nr_fx_out *out)
{
    uint32_t stack[2], sp = 0, tags = 0, qwords = 0, lo = 0, madr = 0;
    int done = 0;
    w->cl = out->cl;       /* the VIF's cycle registers carry over between transfers */
    w->wl = out->wl;
    w->need = 0;
    w->kind = K_DROP;
    w->irq = 0;
    w->err = 0;
    w->len = 0;
    w->vn = 0;
    w->vu_starts = 0;
    w->direct_bytes = 0;
    while (!done && !w->err) {
        const uint8_t *t = host(tadr, 16), *d;
        uint32_t hi, qwc, id;
        if (!t) { w->err = FX_ADDR; break; }
        if (++tags > (1u << 20)) { w->err = FX_TAGS; break; }
        lo = rd32(t);
        hi = rd32(t + 4);
        qwc = lo & 0xFFFF;
        id = (lo >> 28) & 7;
        if (tte) words(w, t + 8, 2);
        switch (id) {
        case 1: madr = tadr + 16; tadr = madr + qwc * 16; break;            /* CNT */
        case 2: madr = tadr + 16; tadr = hi; break;                          /* NEXT */
        case 3: case 4: madr = hi; tadr += 16; break;                        /* REF / REFS */
        case 0: madr = hi; tadr += 16; done = 1; break;                      /* REFE */
        case 5:                                                              /* CALL */
            madr = tadr + 16;
            if (sp >= 2) { w->err = FX_TAGS; break; }
            stack[sp++] = madr + qwc * 16;
            tadr = hi;
            break;
        case 6:                                                              /* RET */
            madr = tadr + 16;
            if (sp) tadr = stack[--sp];
            else { tadr = madr + qwc * 16; done = 1; }
            break;
        default: madr = tadr + 16; done = 1; break;                          /* END */
        }
        if (w->err) break;
        if (qwc) {
            d = host(madr, qwc * 16);
            if (!d) { w->err = FX_ADDR; break; }
            words(w, d, qwc * 4);
            qwords += qwc;
            madr += qwc * 16;
        }
    }
    if (!w->err && w->need) w->err = FX_OPEN;
    out->tags = tags;
    out->qwords = qwords;
    out->last_tag = lo;
    out->tadr = tadr;
    out->madr = madr;
    out->irq = w->irq;
    return w->err;
}

int nr_fx_walk(uint32_t tadr, int tte, nr_fx_sink sink, void *user, nr_fx_sink fwd, void *fwd_user, nr_fx_out *out)
{
    walker *w = &g_w;
    nr_fx_out o = *out;
    int e;
    g_st.chains++;
    /* pass 1: validate (nothing is fed before the whole chain is known to be walkable) */
    w->exec = 0;
    e = walk(w, tadr, tte, &o);
    if (e) {
        switch (e) {
        case FX_ADDR: g_st.f_addr++; break;
        case FX_VIF: g_st.f_vif++; break;
        case FX_OPEN: g_st.f_open++; break;
        default: g_st.f_tags++; break;
        }
        return -1;
    }
    /* pass 2: run */
    w->exec = 1;
    w->sink = sink;
    w->user = user;
    w->fwd = fwd;
    w->fwd_user = fwd_user;
    o = *out;
    walk(w, tadr, tte, &o);
    flush_direct(w);
    *out = o;
    out->cl = w->cl;
    out->wl = w->wl;
    g_st.walked++;
    g_st.tags += o.tags;
    g_st.qwords += o.qwords;
    g_st.direct_qw += w->direct_bytes / 16;
    g_st.vu_starts += (uint64_t)w->vu_starts;
    if (w->vu_starts) g_st.vu_chains++;
    if (o.irq) g_st.irq++;
    return 0;
}

void nr_fx_stats(FILE *f)
{
    if (!f || !g_st.chains) return;
    fprintf(f, "native render frame chains: %llu sent, %llu walked natively (%llu tags, %llu qwords; DIRECT %llu qwords "
               "to the GS; VU work %s: UNPACK %llu words, MPG %llu words, VU program starts %llu "
               "in %llu chains; end-of-frame interrupts %llu); left to the DMAC: address %llu, VIF code %llu, open payload %llu, tags %llu\n",
            (unsigned long long)g_st.chains, (unsigned long long)g_st.walked, (unsigned long long)g_st.tags,
            (unsigned long long)g_st.qwords, (unsigned long long)g_st.direct_qw,
            g_w.fwd ? "handed to the VIF / VU models" : "dropped (no VU1)", (unsigned long long)g_st.unpack_w,
            (unsigned long long)g_st.mpg_w, (unsigned long long)g_st.vu_starts, (unsigned long long)g_st.vu_chains,
            (unsigned long long)g_st.irq, (unsigned long long)g_st.f_addr, (unsigned long long)g_st.f_vif,
            (unsigned long long)g_st.f_open, (unsigned long long)g_st.f_tags);
    if (g_gi.pkts)
        fprintf(f, "native render frame chains: DIRECT GIF packets %llu: immediate records %llu, IMAGE packets split %llu, "
                   "to the GS input %llu (SIGNAL / local->host / refused), packets continued across payloads %llu\n",
                (unsigned long long)g_gi.pkts, (unsigned long long)g_gi.recs, (unsigned long long)g_gi.split,
                (unsigned long long)g_gi.raw, (unsigned long long)g_gi.raw_open);
    nr_im_path3_stats(f);
    if (g_st.vu_starts && !g_w.fwd)
        fprintf(f, "native render WARNING: %llu VU program starts dropped (no VU1 linked or RG_NR_VU=0): every one is a "
                   "missing draw (a fallback mesh or an uncovered program; docs/NATIVE-RENDER.md \"Regression: missing map geometry\")\n",
                (unsigned long long)g_st.vu_starts);
    if (g_st.vu_starts) {
        int i;
        fprintf(f, "native render frame chains: VU program starts by address (x8; ffff = MSCNT):");
        for (i = 0; i < 32 && g_ms[i].n; i++) fprintf(f, " %04x:%llu", g_ms[i].pc, (unsigned long long)g_ms[i].n);
        fputc(10, f);
    }
    if (g_vc.on > 0) {
        int i;
        for (i = 0; i < g_vc.nseg; i++)
            fprintf(f, "fxcensus VU1 upload %d: dest 0x%04x, %u instructions, code %016llx, payload at 0x%08x, %llu uploads\n", i,
                    g_vc.seg[i].dest * 8, g_vc.seg[i].n, (unsigned long long)g_vc.seg[i].hash, g_vc.seg[i].src,
                    (unsigned long long)g_vc.seg[i].uploads);
        for (i = 0; i < g_vc.nkey; i++)
            fprintf(f, "fxcensus VU1 start %s pc 0x%04x code %016llx: %llu\n", g_vc.key[i].cmd == 0x17 ? "MSCNT" :
                    g_vc.key[i].cmd == 0x15 ? "MSCALF" : "MSCAL", g_vc.key[i].pc * 8, (unsigned long long)g_vc.key[i].hash,
                    (unsigned long long)g_vc.key[i].n);
    }
}
