/* SPDX-License-Identifier: CC0-1.0 */
/* EE DMA controller model.  Semantics, timing model and deviations:
 * docs/DMAC.md.  Written from public EE DMAC descriptions; no emulator code. */
#include "dmac.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k.h"

/* ------------------------------------------------------------------ */

static const uint32_t k_chan_base[DMAC_NCH] = {
    0x10008000u, 0x10009000u, 0x1000A000u, 0x1000B000u, 0x1000B400u,
    0x1000C000u, 0x1000C400u, 0x1000C800u, 0x1000D000u, 0x1000D400u,
};

static const char *const k_chan_name[DMAC_NCH] = {
    "VIF0", "VIF1", "GIF", "fromIPU", "toIPU", "SIF0", "SIF1", "SIF2", "fromSPR", "toSPR",
};

static void set_error(dmac_state *d, const char *fmt, int ch, uint32_t a, uint32_t b)
{
    snprintf(d->error, sizeof d->error, fmt, ch >= 0 && ch < DMAC_NCH ? k_chan_name[ch] : "?", a, b);
    fprintf(stderr, "[dmac] %s\n", d->error);
}

/* ------------------------------------------------------------------ lifetime */

dmac_state *dmac_create(void)
{
    /* dmac_state holds 16-byte aligned members: over-allocate and align */
    uint8_t *raw = (uint8_t *)calloc(1, sizeof(dmac_state) + 16 + sizeof(void *));
    uintptr_t p;
    dmac_state *d;
    if (!raw) return NULL;
    p = ((uintptr_t)raw + sizeof(void *) + 15) & ~(uintptr_t)15;
    ((void **)p)[-1] = raw;
    d = (dmac_state *)p;
    d->kernel = 1;
    d->cycles_per_qword = 1;
    d->max_tags = 1u << 24;
    dmac_reset(d);
    return d;
}

static dmac_state *vif_owner[2];   /* the kernel-bound DMAC each VIF is attached to */

void dmac_destroy(dmac_state *d)
{
    if (vif_owner[0] == d) vif_owner[0] = NULL;
    if (vif_owner[1] == d) vif_owner[1] = NULL;
    if (d) free(((void **)d)[-1]);
}

void dmac_reset(dmac_state *d)
{
    memset(d->ch, 0, sizeof d->ch);
    memset(d->cs, 0, sizeof d->cs);
    d->ctrl = 1;           /* DMAE: the boot ROM leaves the DMAC enabled */
    d->pcr = d->sqwc = d->rbsr = d->rbor = d->stadr = 0;
    d->enable = 0x1201;    /* D_ENABLER power-on value, CPND clear */
    d->stat_local = d->mask_local = 0;
    d->depth = 0;
    d->cost = 0;
    d->error[0] = 0;
}

void dmac_map_guest_ram(dmac_state *d, uint8_t *ram, uint32_t size)
{
    d->mem_mode = DMAC_MEM_GUEST;
    d->ram = ram;
    d->ram_size = size;
}

/* ------------------------------------------------------------------ peripherals */

/* Debug capture (docs/RENDER-BRINGUP.md): RG_VIF1_DUMP=path with
 * RG_VIF1_DUMP_KICKS=first-last writes the VIF1 word stream of those VIF1
 * channel kicks (records: u32 0xFFFFFFFF + u32 kick, then u32 bytes + data). */
static struct { FILE *f; uint32_t kick, first, last; int init, on; } vdump;
static void vdump_kick(void)
{
    if (!vdump.init) {
        const char *p = getenv("RG_VIF1_DUMP"), *k = getenv("RG_VIF1_DUMP_KICKS");
        vdump.init = 1;
        if (p && k && sscanf(k, "%u-%u", &vdump.first, &vdump.last) == 2)
            vdump.f = fopen(p, "wb");
    }
    vdump.kick++;
    if (vdump.f && (vdump.kick & 255) == 0)
        fprintf(stderr, "VIF1DUMP at kick %u\n", vdump.kick);
    vdump.on = vdump.f && vdump.kick >= vdump.first && vdump.kick <= vdump.last;
    if (vdump.on) {
        uint32_t h[2] = {0xFFFFFFFFu, vdump.kick};
        fwrite(h, 4, 2, vdump.f);
        fflush(vdump.f);
        fprintf(stderr, "VIF1DUMP kick %u\n", vdump.kick);
    } else if (vdump.f && vdump.kick > vdump.last) {
        fclose(vdump.f);
        vdump.f = NULL;
    }
}

static void vif_out(void *user, int ch, const uint8_t *data, uint32_t bytes, uint32_t flags)
{
    vif_state *v = (vif_state *)user;
    uint32_t tmp[64];
    (void)ch; (void)flags;
    if (vdump.on && v->id == 1) { fwrite(&bytes, 4, 1, vdump.f); fwrite(data, 1, bytes, vdump.f); }
    if (((uintptr_t)data & 3) == 0) {
        vif_write(v, (const uint32_t *)(const void *)data, bytes / 4);
        return;
    }
    while (bytes) {
        uint32_t n = bytes > sizeof tmp ? (uint32_t)sizeof tmp : bytes;
        memcpy(tmp, data, n);
        vif_write(v, tmp, n / 4);
        data += n;
        bytes -= n;
    }
}

static void vif_irq(void *user, uint32_t code)
{
    vif_state *v = (vif_state *)user;
    dmac_state *d = vif_owner[v->id ? 1 : 0];
    (void)code;
    /* The VIF does not stall on the i bit here (DMAC.md "VIF interrupts").
     * Inside a DMA kick the interrupt is deferred until the kick has been
     * charged, then posted one cycle later: the kicking code runs on (as the
     * EE does while the chain is in flight) and the handler runs at the next
     * advance of the virtual clock.  GfxEndFrame_141c20 kicks the frame's
     * VIF1 chain and then zeroes T0; the VIF1 handler's T0 sample
     * (Vif1IntcHandler_15e170 -> D_004810B4) must come after that reset, or
     * it reads the whole frame interval and the stored frame-time feedback
     * (+0xF10) becomes 2.0038 instead of the interval. */
    if (d && d->depth > 0) {
        d->vif_irq_deferred |= 1u << (v->id ? 1 : 0);
        return;
    }
    ps2k_raise_intc(v->id ? PS2K_INTC_VIF1 : PS2K_INTC_VIF0);
}

static void post_deferred_vif_irqs(dmac_state *d)
{
    uint32_t m = d->vif_irq_deferred;
    d->vif_irq_deferred = 0;
    if (m & 1) ps2k_post_intc(PS2K_INTC_VIF0, 1);
    if (m & 2) ps2k_post_intc(PS2K_INTC_VIF1, 1);
}

static void vif_irq_nokernel(void *user, uint32_t code) { (void)user; (void)code; }

void dmac_attach_vif(dmac_state *d, int which, vif_state *vif)
{
    which &= 1;
    d->vif[which] = vif;
    if (!vif) {
        d->out[which] = NULL;
        return;
    }
    vif->irq_fn = d->kernel ? vif_irq : vif_irq_nokernel;
    vif->irq_user = vif;
    if (d->kernel)
        vif_owner[vif->id ? 1 : 0] = d;
    vif->stall_on_irq = 0;
    d->out[which] = vif_out;
    d->out_user[which] = vif;
}

static void gif_out(void *user, int ch, const uint8_t *data, uint32_t bytes, uint32_t flags)
{
    (void)ch; (void)flags;
    gs_gif_write((gs_state *)user, GS_PATH3, data, bytes / 16);
}

static uint32_t vif1_readback(void *user, int ch, uint8_t *dst, uint32_t bytes)
{
    (void)ch;
    return gs_read_fifo((gs_state *)user, dst, bytes) & ~15u;
}

static void gs_irq_to_intc(void *user, uint32_t ev)
{
    (void)user; (void)ev;
    ps2k_raise_intc(PS2K_INTC_GS);
}

void dmac_attach_gs(dmac_state *d, gs_state *gs)
{
    d->gs = gs;
    d->out[DMAC_GIF] = gs ? gif_out : NULL;
    d->out_user[DMAC_GIF] = gs;
    d->in[DMAC_VIF1] = gs ? vif1_readback : NULL;
    d->in_user[DMAC_VIF1] = gs;
    if (gs && !gs->irq && d->kernel) {
        gs->irq = gs_irq_to_intc;
        gs->irq_user = d;
    }
}

void dmac_set_out(dmac_state *d, int ch, dmac_out_fn fn, void *user)
{
    if (ch >= 0 && ch < DMAC_NCH) { d->out[ch] = fn; d->out_user[ch] = user; }
}
void dmac_set_in(dmac_state *d, int ch, dmac_in_fn fn, void *user)
{
    if (ch >= 0 && ch < DMAC_NCH) { d->in[ch] = fn; d->in_user[ch] = user; }
}
void dmac_set_start(dmac_state *d, int ch, dmac_start_fn fn, void *user)
{
    if (ch >= 0 && ch < DMAC_NCH) { d->start[ch] = fn; d->start_user[ch] = user; }
}

/* ------------------------------------------------------------------ memory */

uint8_t *dmac_mem(dmac_state *d, uint32_t addr, uint32_t bytes)
{
    if (addr & 0x80000000u) {
        uint32_t off = addr & 0x3FF0u;
        return off + bytes <= DMAC_SPR_BYTES ? d->spr + off : NULL;
    }
    if (d->mem_mode == DMAC_MEM_GUEST) {
        uint32_t top = addr >> 28, phys;
        if (top == 7) {
            uint32_t off = addr & 0x3FF0u;
            return off + bytes <= DMAC_SPR_BYTES ? d->spr + off : NULL;
        }
        if (top != 0 && top != 2 && top != 3) return NULL; /* registers / unmapped */
        phys = addr & 0x0FFFFFF0u;
        if (!d->ram || phys > d->ram_size || bytes > d->ram_size - phys) return NULL;
        return d->ram + phys;
    }
    /* host mode: the address is the host pointer (i686) */
    if (addr < 0x10000u) return NULL;
    return (uint8_t *)(uintptr_t)addr;
}

uint32_t dmac_addr_of(const dmac_state *d, const void *p)
{
    const uint8_t *b = (const uint8_t *)p;
    if (b >= d->spr && b < d->spr + DMAC_SPR_BYTES) return 0x80000000u | (uint32_t)(b - d->spr);
    if (d->mem_mode == DMAC_MEM_GUEST && d->ram && b >= d->ram && b < d->ram + d->ram_size)
        return (uint32_t)(b - d->ram);
    return (uint32_t)(uintptr_t)p;
}

uint32_t dmac_canon_addr(const dmac_state *d, uint32_t addr)
{
    if (d->mem_mode == DMAC_MEM_GUEST) {
        if ((addr >> 28) == 7) return (addr & 0x0FFFFFFFu) | 0x80000000u;
        return addr;
    }
    return dmac_addr_of(d, (const void *)(uintptr_t)addr);
}

/* ------------------------------------------------------------------ helpers */

static int is_to_mem(const dmac_state *d, int ch)
{
    switch (ch) {
    case DMAC_VIF1:
    case DMAC_SIF2: return !(d->ch[ch].chcr & DMAC_CHCR_DIR);
    case DMAC_FROM_IPU:
    case DMAC_SIF0:
    case DMAC_FROM_SPR: return 1;
    default: return 0;
    }
}

static int suspended(const dmac_state *d)
{
    return !(d->ctrl & 1u) || (d->enable & 0x10000u);
}

static int path3_masked(const dmac_state *d)
{
    return d->vif[1] && d->vif[1]->mskpath3;
}

static int sts_channel(const dmac_state *d)
{
    static const int map[4] = {-1, DMAC_SIF0, DMAC_FROM_SPR, DMAC_FROM_IPU};
    return map[(d->ctrl >> 4) & 3];
}

static void bus_error(dmac_state *d, int ch, uint32_t addr, uint32_t bytes)
{
    d->bus_errors++;
    d->stat_local |= 1u << 15; /* BEIS */
    set_error(d, "%s: bus error at 0x%08X (%u bytes); channel stopped", ch, addr, bytes);
}

static void periph_out(dmac_state *d, int ch, const uint8_t *p, uint32_t bytes, uint32_t flags)
{
    if (d->out[ch]) {
        d->out[ch](d->out_user[ch], ch, p, bytes, flags);
        return;
    }
    if (!d->stats[ch].unbound_qwords)
        fprintf(stderr, "[dmac] %s: no peripheral bound; data dropped\n", k_chan_name[ch]);
    d->stats[ch].unbound_qwords += (bytes + 15) / 16;
}

/* memory -> peripheral, qwc qwords at addr (scratchpad addresses wrap) */
static int xfer_out(dmac_state *d, int ch, uint32_t addr, uint32_t qwc)
{
    while (qwc) {
        uint32_t n = qwc;
        uint8_t *p;
        if (addr & 0x80000000u) {
            uint32_t off = addr & 0x3FF0u, room = (DMAC_SPR_BYTES - off) / 16;
            if (n > room) n = room;
        }
        p = dmac_mem(d, addr, n * 16);
        if (!p) {
            bus_error(d, ch, addr, n * 16);
            return -1;
        }
        periph_out(d, ch, p, n * 16, 0);
        d->stats[ch].qwords += n;
        d->cost += n;
        qwc -= n;
        addr = (addr & 0x80000000u) ? (0x80000000u | ((addr + n * 16) & 0x3FF0u)) : addr + n * 16;
    }
    return 0;
}

/* peripheral -> memory.  Returns qwords moved (< qwc means the source ran
 * dry), or -1 on a bus error. */
static int64_t xfer_in(dmac_state *d, int ch, uint32_t addr, uint32_t qwc)
{
    uint32_t done = 0;
    if (!d->in[ch]) return 0;
    while (done < qwc) {
        uint32_t n = qwc - done, got;
        uint32_t a = (addr & 0x80000000u) ? (0x80000000u | ((addr + done * 16) & 0x3FF0u)) : addr + done * 16;
        uint8_t *p;
        if (a & 0x80000000u) {
            uint32_t room = (DMAC_SPR_BYTES - (a & 0x3FF0u)) / 16;
            if (n > room) n = room;
        }
        p = dmac_mem(d, a, n * 16);
        if (!p) {
            bus_error(d, ch, a, n * 16);
            return -1;
        }
        got = d->in[ch](d->in_user[ch], ch, p, n * 16) / 16;
        done += got;
        d->stats[ch].qwords += got;
        d->cost += got;
        if (got < n) break;
    }
    return done;
}

static uint32_t spr_advance(uint32_t sadr, uint32_t qw) { return (sadr + qw * 16) & 0x3FF0u; }

/* SPR channels: copy qwc qwords between memory (MADR) and the scratchpad
 * (SADR), both wrapping as hardware does for the scratchpad side. */
static int xfer_spr(dmac_state *d, int ch, uint32_t qwc)
{
    dmac_chan_regs *r = &d->ch[ch];
    while (qwc) {
        uint32_t n = qwc, sroom = (DMAC_SPR_BYTES - (r->sadr & 0x3FF0u)) / 16;
        uint8_t *m, *s;
        if (n > sroom) n = sroom;
        if (r->madr & 0x80000000u) {
            uint32_t mroom = (DMAC_SPR_BYTES - (r->madr & 0x3FF0u)) / 16;
            if (n > mroom) n = mroom;
        }
        m = dmac_mem(d, r->madr, n * 16);
        if (!m) {
            bus_error(d, ch, r->madr, n * 16);
            return -1;
        }
        s = d->spr + (r->sadr & 0x3FF0u);
        if (ch == DMAC_TO_SPR) memmove(s, m, n * 16);
        else memmove(m, s, n * 16);
        r->madr += n * 16;
        r->sadr = spr_advance(r->sadr, n);
        r->qwc -= n;
        qwc -= n;
        d->stats[ch].qwords += n;
        d->cost += n;
    }
    return 0;
}

static void finish(dmac_state *d, int ch)
{
    dmac_chan_regs *r = &d->ch[ch];
    r->chcr &= ~DMAC_CHCR_STR;
    d->cs[ch].pending = 0;
    d->cs[ch].chain_end = 0;
    d->stats[ch].completions++;
    if (d->kernel) ps2k_raise_dmac(ch);
    else d->stat_local |= 1u << ch;
}

static void stop_on_error(dmac_state *d, int ch)
{
    d->ch[ch].chcr &= ~DMAC_CHCR_STR;
    d->cs[ch].pending = 0;
    d->cs[ch].chain_end = 0;
}

static void update_stall(dmac_state *d, int ch)
{
    if (sts_channel(d) == ch) d->stadr = d->ch[ch].madr;
}

/* ------------------------------------------------------------------ modes */

/* move the current QWC block of a channel; returns 1 done, 0 held, -1 error */
static int move_block(dmac_state *d, int ch)
{
    dmac_chan_regs *r = &d->ch[ch];
    if (!r->qwc) return 1;
    if (ch == DMAC_FROM_SPR || ch == DMAC_TO_SPR) {
        if (xfer_spr(d, ch, r->qwc) < 0) return -1;
        update_stall(d, ch);
        return 1;
    }
    if (is_to_mem(d, ch)) {
        int64_t got = xfer_in(d, ch, r->madr, r->qwc);
        if (got < 0) return -1;
        r->madr += (uint32_t)got * 16;
        r->qwc -= (uint32_t)got;
        update_stall(d, ch);
        if (r->qwc) {
            d->stats[ch].holds++;
            return 0;
        }
        return 1;
    }
    if (xfer_out(d, ch, r->madr, r->qwc) < 0) return -1;
    r->madr += r->qwc * 16;
    r->qwc = 0;
    return 1;
}

static int run_normal(dmac_state *d, int ch)
{
    int rc = move_block(d, ch);
    if (rc < 0) { stop_on_error(d, ch); return 1; }
    if (rc == 0) return 0;
    finish(d, ch);
    return 1;
}

static int tte_channel(int ch)
{
    return ch == DMAC_VIF0 || ch == DMAC_VIF1 || ch == DMAC_SIF1;
}

static int run_source_chain(dmac_state *d, int ch)
{
    dmac_chan_regs *r = &d->ch[ch];
    dmac_chan_state *cs = &d->cs[ch];
    uint64_t tags = 0;
    for (;;) {
        uint8_t *t;
        uint32_t lo, hi, qwc, id, asp;
        int rc = move_block(d, ch);
        if (rc < 0) { stop_on_error(d, ch); return 1; }
        if (rc == 0) return 0;
        if (cs->chain_end) {
            finish(d, ch);
            return 1;
        }
        if (suspended(d) || (ch == DMAC_GIF && path3_masked(d))) {
            d->stats[ch].holds++;
            return 0;
        }
        if (++tags > d->max_tags) {
            set_error(d, "%s: chain TRUNCATED after %u tags (TADR 0x%08X); raise max_tags if genuine",
                      ch, (uint32_t)d->max_tags, r->tadr);
            stop_on_error(d, ch);
            return 1;
        }
        t = dmac_mem(d, r->tadr, 16);
        if (!t) {
            bus_error(d, ch, r->tadr, 16);
            stop_on_error(d, ch);
            return 1;
        }
        memcpy(&lo, t, 4);
        memcpy(&hi, t + 4, 4);
        d->stats[ch].tags++;
        d->cost++;
        qwc = lo & 0xFFFFu;
        id = (lo >> 28) & 7u;
        r->chcr = (r->chcr & 0xFFFFu) | (lo & 0xFFFF0000u);
        if (r->chcr & DMAC_CHCR_TTE) {
            if (tte_channel(ch)) periph_out(d, ch, t + 8, 8, DMAC_OUT_TAG);
            else d->stats[ch].tte_ignored++;
        }
        asp = (r->chcr >> 4) & 3u;
        switch (id) {
        case DMAC_TAG_REFE:
            r->madr = hi;
            r->tadr += 16;
            cs->chain_end = 1;
            break;
        case DMAC_TAG_CNT:
            r->madr = r->tadr + 16;
            r->tadr = r->madr + qwc * 16;
            break;
        case DMAC_TAG_NEXT:
            r->madr = r->tadr + 16;
            r->tadr = hi;
            break;
        case DMAC_TAG_REF:
        case DMAC_TAG_REFS: /* no stall: the stall source ran to completion already */
            r->madr = hi;
            r->tadr += 16;
            break;
        case DMAC_TAG_CALL:
            r->madr = r->tadr + 16;
            if (asp >= 2) {
                set_error(d, "%s: CALL with the address stack full (TADR 0x%08X)", ch, r->tadr, 0);
                d->stat_local |= 1u << 15;
                stop_on_error(d, ch);
                return 1;
            }
            if (asp == 0) r->asr0 = r->madr + qwc * 16;
            else r->asr1 = r->madr + qwc * 16;
            r->chcr = (r->chcr & ~DMAC_CHCR_ASP) | ((asp + 1) << 4);
            r->tadr = hi;
            break;
        case DMAC_TAG_RET:
            r->madr = r->tadr + 16;
            if (asp > 0 && !d->debug_ret_ends_chain) {
                r->tadr = asp == 2 ? r->asr1 : r->asr0;
                r->chcr = (r->chcr & ~DMAC_CHCR_ASP) | ((asp - 1) << 4);
            } else {
                r->tadr = r->madr + qwc * 16;
                cs->chain_end = 1;
            }
            break;
        default: /* END */
            r->madr = r->tadr + 16;
            cs->chain_end = 1;
            break;
        }
        r->qwc = qwc;
        if ((lo & 0x80000000u) && (r->chcr & DMAC_CHCR_TIE)) {
            if (!cs->chain_end) d->stats[ch].irq_stops++;
            cs->chain_end = 1;
        }
    }
}

/* read one qword from a destination-chain source; 1 = got it, 0 = dry, -1 = error */
static int read_dtag(dmac_state *d, int ch, uint8_t tag[16])
{
    dmac_chan_regs *r = &d->ch[ch];
    if (ch == DMAC_FROM_SPR) {
        memcpy(tag, d->spr + (r->sadr & 0x3FF0u), 16);
        r->sadr = spr_advance(r->sadr, 1);
        return 1;
    }
    if (!d->in[ch]) return 0;
    if (d->in[ch](d->in_user[ch], ch, tag, 16) < 16) return 0;
    return 1;
}

static int run_dest_chain(dmac_state *d, int ch)
{
    dmac_chan_regs *r = &d->ch[ch];
    dmac_chan_state *cs = &d->cs[ch];
    uint64_t tags = 0;
    for (;;) {
        uint8_t t[16];
        uint32_t lo, hi, id;
        int rc = move_block(d, ch);
        if (rc < 0) { stop_on_error(d, ch); return 1; }
        if (rc == 0) return 0;
        if (cs->chain_end) {
            finish(d, ch);
            return 1;
        }
        if (suspended(d)) {
            d->stats[ch].holds++;
            return 0;
        }
        if (++tags > d->max_tags) {
            set_error(d, "%s: destination chain TRUNCATED after %u tags (0x%08X)", ch, (uint32_t)d->max_tags, 0);
            stop_on_error(d, ch);
            return 1;
        }
        rc = read_dtag(d, ch, t);
        if (rc == 0) {
            d->stats[ch].holds++;
            return 0;
        }
        memcpy(&lo, t, 4);
        memcpy(&hi, t + 4, 4);
        d->stats[ch].tags++;
        d->cost++;
        id = (lo >> 28) & 7u;
        r->chcr = (r->chcr & 0xFFFFu) | (lo & 0xFFFF0000u);
        r->madr = hi;
        r->qwc = lo & 0xFFFFu;
        if (id == DMAC_DTAG_END) cs->chain_end = 1;
        else if (id != DMAC_DTAG_CNT && id != DMAC_DTAG_CNTS)
            set_error(d, "%s: destination tag id %u treated as CNT (0x%08X)", ch, id, lo);
        if ((lo & 0x80000000u) && (r->chcr & DMAC_CHCR_TIE)) {
            if (!cs->chain_end) d->stats[ch].irq_stops++;
            cs->chain_end = 1;
        }
    }
}

static int run_interleave(dmac_state *d, int ch)
{
    dmac_chan_regs *r = &d->ch[ch];
    uint32_t skip = d->sqwc & 0xFFu, tq = (d->sqwc >> 16) & 0xFFu;
    if (!tq) {
        set_error(d, "%s: interleave with TQWC 0 (QWC %u)", ch, r->qwc, 0);
        stop_on_error(d, ch);
        return 1;
    }
    while (r->qwc) {
        uint32_t n = r->qwc < tq ? r->qwc : tq;
        if (xfer_spr(d, ch, n) < 0) { stop_on_error(d, ch); return 1; }
        if (r->qwc) r->madr += skip * 16;
    }
    finish(d, ch);
    return 1;
}

/* 1 = finished (or stopped), 0 = held */
static int run_channel(dmac_state *d, int ch)
{
    dmac_chan_regs *r = &d->ch[ch];
    uint32_t mod = (r->chcr >> 2) & 3u;
    if (suspended(d) || (ch == DMAC_GIF && path3_masked(d))) {
        d->stats[ch].holds++;
        return 0;
    }
    if ((d->ctrl & 0xCu) && (ch == DMAC_FROM_SPR || ch == DMAC_VIF1 || ch == DMAC_GIF)) {
        static int warned;
        if (!warned++) fprintf(stderr, "[dmac] D_CTRL.MFD=%u: MFIFO is not modelled; plain transfers\n",
                               (d->ctrl >> 2) & 3u);
    }
    if (mod == 1) {
        if (ch == DMAC_SIF0 || ch == DMAC_FROM_SPR) return run_dest_chain(d, ch);
        if (ch == DMAC_FROM_IPU || ch == DMAC_SIF2 || is_to_mem(d, ch)) {
            set_error(d, "%s: chain mode not supported in this direction (CHCR 0x%08X)", ch, r->chcr, 0);
            return run_normal(d, ch);
        }
        return run_source_chain(d, ch);
    }
    if (mod == 2) {
        if (ch == DMAC_FROM_SPR || ch == DMAC_TO_SPR) return run_interleave(d, ch);
        set_error(d, "%s: interleave mode on a non-SPR channel (CHCR 0x%08X)", ch, r->chcr, 0);
    }
    return run_normal(d, ch);
}

static void charge(dmac_state *d)
{
    uint64_t cyc = d->cost * d->cycles_per_qword;
    d->cost = 0;
    if (!cyc || !d->kernel) return;
    if (ps2k_get_thread_id() != 0 && !ps2k_in_handler()) ps2k_charge(cyc);
    else d->uncharged_cycles += cyc;
}

static void run_pending(dmac_state *d)
{
    int progress;
    d->depth++;
    do {
        int ch;
        progress = 0;
        for (ch = 0; ch < DMAC_NCH; ch++) {
            if (!d->cs[ch].pending || d->cs[ch].running) continue;
            if (!(d->ch[ch].chcr & DMAC_CHCR_STR)) {
                d->cs[ch].pending = 0;
                continue;
            }
            d->cs[ch].running = 1;
            if (run_channel(d, ch)) progress = 1;
            d->cs[ch].running = 0;
        }
    } while (progress);
    d->depth--;
    if (d->depth == 0) {
        charge(d);
        if (d->vif_irq_deferred)
            post_deferred_vif_irqs(d);
    }
}

/* ------------------------------------------------------------------ channels */

dmac_chan_regs *dmac_chan(dmac_state *d, int ch)
{
    return ch >= 0 && ch < DMAC_NCH ? &d->ch[ch] : NULL;
}

int dmac_chan_index(const dmac_state *d, const void *regs)
{
    int ch;
    for (ch = 0; ch < DMAC_NCH; ch++)
        if ((const void *)&d->ch[ch] == regs) return ch;
    return -1;
}

int dmac_kick(dmac_state *d, int ch)
{
    if (ch < 0 || ch >= DMAC_NCH) return 1;
    if (!(d->ch[ch].chcr & DMAC_CHCR_STR)) return 1;
    d->stats[ch].kicks++;
    if (ch == 1 && !d->cs[ch].pending) vdump_kick();
    if (!d->cs[ch].pending) {
        d->cs[ch].pending = 1;
        d->cs[ch].chain_end = 0;
        }
    if (is_to_mem(d, ch) && d->start[ch]) {
        d->depth++;
        d->start[ch](d->start_user[ch], ch);
        d->depth--;
    }
    run_pending(d);
    return !d->cs[ch].pending;
}

void dmac_service(dmac_state *d)
{
    run_pending(d);
}

void dmac_write_chcr(dmac_state *d, int ch, uint32_t v)
{
    dmac_chan_regs *r;
    uint32_t old;
    if (ch < 0 || ch >= DMAC_NCH) return;
    r = &d->ch[ch];
    old = r->chcr;
    r->chcr = (v & 0xFFFFu) | (old & 0xFFFF0000u); /* TAG bits are read-only */
    if ((v & DMAC_CHCR_STR) && !(old & DMAC_CHCR_STR)) dmac_kick(d, ch);
    else if (!(v & DMAC_CHCR_STR)) d->cs[ch].pending = 0; /* suspend */
}

int dmac_busy(const dmac_state *d, int ch)
{
    return ch >= 0 && ch < DMAC_NCH && (d->ch[ch].chcr & DMAC_CHCR_STR) != 0;
}

/* ------------------------------------------------------------------ registers */

static int reg_index(uint32_t addr, int *ch, uint32_t *off)
{
    int i;
    for (i = 0; i < DMAC_NCH; i++) {
        uint32_t o = addr - k_chan_base[i];
        if (o < 0x90u && (o & 0xFu) == 0 && (o <= 0x50u || o == 0x80u)) {
            *ch = i;
            *off = o;
            return 1;
        }
    }
    return 0;
}

int dmac_hw_claims(uint32_t addr)
{
    int ch;
    uint32_t off;
    if (reg_index(addr, &ch, &off)) return 1;
    return (addr >= DMAC_D_CTRL && addr <= DMAC_D_STADR && (addr & 0xFu) == 0) ||
           addr == DMAC_D_ENABLER || addr == DMAC_D_ENABLEW;
}

uint32_t dmac_hw_read32(dmac_state *d, uint32_t addr)
{
    int ch;
    uint32_t off;
    if (reg_index(addr, &ch, &off)) {
        const dmac_chan_regs *r = &d->ch[ch];
        switch (off) {
        case 0x00: return r->chcr;
        case 0x10: return r->madr;
        case 0x20: return r->qwc;
        case 0x30: return r->tadr;
        case 0x40: return r->asr0;
        case 0x50: return r->asr1;
        default: return r->sadr;
        }
    }
    switch (addr) {
    case DMAC_D_CTRL: return d->ctrl;
    case DMAC_D_STAT:
        if (d->kernel)
            return (ps2k_hw_read32(PS2K_D_STAT) & 0x03FF03FFu) | (d->stat_local & 0xE000u) |
                   (d->mask_local & 0x60000000u);
        return (d->stat_local & 0xE3FFu) | (d->mask_local & 0x63FF0000u);
    case DMAC_D_PCR: return d->pcr;
    case DMAC_D_SQWC: return d->sqwc;
    case DMAC_D_RBSR: return d->rbsr;
    case DMAC_D_RBOR: return d->rbor;
    case DMAC_D_STADR: return d->stadr;
    case DMAC_D_ENABLER: return d->enable;
    default: return 0;
    }
}

void dmac_hw_write32(dmac_state *d, uint32_t addr, uint32_t v)
{
    int ch;
    uint32_t off;
    if (reg_index(addr, &ch, &off)) {
        dmac_chan_regs *r = &d->ch[ch];
        switch (off) {
        case 0x00: dmac_write_chcr(d, ch, v); break;
        case 0x10: r->madr = v; break;
        case 0x20: r->qwc = v & 0xFFFFu; break;
        case 0x30: r->tadr = v; break;
        case 0x40: r->asr0 = v; break;
        case 0x50: r->asr1 = v; break;
        default: r->sadr = v & 0x3FF0u; break;
        }
        return;
    }
    switch (addr) {
    case DMAC_D_CTRL: {
        uint32_t old = d->ctrl;
        d->ctrl = v & 0x7FFu;
        if ((v & 1u) && !(old & 1u)) dmac_service(d);
        break;
    }
    case DMAC_D_STAT:
        if (d->kernel) ps2k_hw_write32(PS2K_D_STAT, v & 0x03FF03FFu);
        else {
            d->stat_local &= ~(v & 0x3FFu);
            d->mask_local ^= v & 0x03FF0000u;
        }
        d->stat_local &= ~(v & 0xE000u);       /* SIS/MEIS/BEIS: write 1 to clear */
        d->mask_local ^= v & 0x60000000u;      /* SIM/MEIM: write 1 to toggle */
        break;
    case DMAC_D_PCR: d->pcr = v; break;
    case DMAC_D_SQWC: d->sqwc = v; break;
    case DMAC_D_RBSR: d->rbsr = v; break;
    case DMAC_D_RBOR: d->rbor = v; break;
    case DMAC_D_STADR: d->stadr = v; break;
    case DMAC_D_ENABLEW: {
        uint32_t old = d->enable;
        d->enable = v;
        if ((old & 0x10000u) && !(v & 0x10000u)) dmac_service(d);
        break;
    }
    default: break;
    }
}

/* ------------------------------------------------------------------ FIFOs */

void dmac_vif_fifo_write(dmac_state *d, int which, const void *qwords, uint32_t nqw)
{
    which &= 1;
    if (d->out[which]) d->out[which](d->out_user[which], which, (const uint8_t *)qwords, nqw * 16, 0);
    if (which == 1) dmac_service(d); /* MSKPATH3 may have been released */
}

void dmac_gif_fifo_write(dmac_state *d, const void *qwords, uint32_t nqw)
{
    if (d->gs) gs_gif_write(d->gs, GS_PATH3, qwords, nqw);
}

uint32_t dmac_vif1_fifo_read(dmac_state *d, void *dst, uint32_t nqw)
{
    return d->gs ? gs_read_fifo(d->gs, dst, nqw * 16) : 0;
}

void dmac_vif_reset(dmac_state *d, int which)
{
    which &= 1;
    if (d->vif[which]) vif_reset(d->vif[which]);
    if (which == 1) dmac_service(d);
}
