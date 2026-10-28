/* SPDX-License-Identifier: CC0-1.0 */
/* libdma over the DMAC model.  Behaviour follows the retail asm bodies
 * (game/src/main/sdk/sceDma*.c, gs/sceDma*.c): which registers each call
 * writes, in which order, and what it returns.  docs/DMAC.md. */
#include <stdio.h>
#include <string.h>

#include "graphics_internal.h"
#include "ps2k.h"

dmac_state *g_rg_dmac;
gs_state *g_rg_gs;

void sce_graphics_bind(dmac_state *dmac, gs_state *gs)
{
    g_rg_dmac = dmac;
    g_rg_gs = gs;
    if (dmac && gs && dmac->gs != gs) dmac_attach_gs(dmac, gs);
}

dmac_state *sce_graphics_dmac(void) { return g_rg_dmac; }
gs_state *sce_graphics_gs(void) { return g_rg_gs; }

/* retail tables (libdma .data 0x456028..0x456070) */
static const uint8_t k_reset_ch[DMAC_NCH] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1};
static const uint8_t k_sts[DMAC_NCH] = {0, 0, 0, 3, 0, 1, 0, 0, 2, 0};
static const uint8_t k_std[DMAC_NCH] = {0, 1, 2, 0, 0, 0, 3, 0, 0, 0};
static const uint8_t k_mfd[DMAC_NCH] = {0, 2, 3, 0, 0, 0, 0, 0, 0, 0};

#ifdef __cplusplus
static_assert(sizeof(sceDmaEnv) == 0x14, "sceDmaEnv");
#else
_Static_assert(sizeof(sceDmaEnv) == 0x14 || sizeof(void *) != 4, "sceDmaEnv is 0x14 bytes on i686");
_Static_assert(sizeof(sceDmaChan) == 0x90, "sceDmaChan");
#endif

static sceDmaEnv g_env; /* retail caches the last PutEnv at 0x485978 */

uint32_t rg_dma_addr(const void *p)
{
    return dmac_canon_addr(g_rg_dmac, (uint32_t)(uintptr_t)p);
}

void rg_poll_charge(void)
{
    if (g_rg_dmac && g_rg_dmac->kernel && ps2k_get_thread_id() != 0 && !ps2k_in_handler())
        ps2k_charge(32);
}

int rg_dma_wait_idle(int ch)
{
    dmac_state *d = g_rg_dmac;
    if (!d || ch < 0 || !dmac_busy(d, ch)) return 0;
    dmac_service(d);
    if (!dmac_busy(d, ch)) return 0;
    /* retail: 16M polls, then "libdma: sync timeout" and sceDmaPause */
    fprintf(stderr, "libdma: sync timeout (channel %d held: CHCR=0x%08X MADR=0x%08X QWC=%u TADR=0x%08X)\n",
            ch, d->ch[ch].chcr, d->ch[ch].madr, d->ch[ch].qwc, d->ch[ch].tadr);
    dmac_write_chcr(d, ch, d->ch[ch].chcr & ~DMAC_CHCR_STR);
    return -1;
}

static int chan_of(const sceDmaChan *c)
{
    return g_rg_dmac ? dmac_chan_index(g_rg_dmac, c) : -1;
}

/* ------------------------------------------------------------------ */

int sceDmaPutEnv(sceDmaEnv *env)
{
    dmac_state *d = g_rg_dmac;
    uint32_t ctrl;
    if (!d) return -1;
    ctrl = d->ctrl;
    if (env->sts >= 10) return -1;
    if (env->std >= 10) return -2;
    if (env->mfd >= 10) return -3;
    if (env->rcycle >= 7) return -4;
    ctrl = (ctrl & ~0x30u) | ((uint32_t)k_sts[env->sts] << 4);
    ctrl = (ctrl & ~0xC0u) | ((uint32_t)k_std[env->std] << 6);
    ctrl = (ctrl & ~0x0Cu) | ((uint32_t)k_mfd[env->mfd] << 2);
    if (env->rcycle) ctrl = (ctrl | 2u) & ~0x700u, ctrl |= (uint32_t)(env->rcycle - 1) << 8;
    else ctrl &= ~2u;
    dmac_hw_write32(d, DMAC_D_CTRL, ctrl);
    dmac_hw_write32(d, DMAC_D_PCR, ((uint32_t)env->express << 16) | env->notify);
    dmac_hw_write32(d, DMAC_D_SQWC, ((uint32_t)env->tqwc << 16) | env->sqwc);
    dmac_hw_write32(d, DMAC_D_RBOR, (uint32_t)(uintptr_t)env->rbadr);
    dmac_hw_write32(d, DMAC_D_RBSR, env->rbmsk);
    memcpy(&g_env, env, sizeof g_env);
    return 0;
}

sceDmaEnv *sceDmaGetEnv(sceDmaEnv *env)
{
    memcpy(env, &g_env, sizeof *env);
    return env;
}

int sceDmaReset(int mode)
{
    dmac_state *d = g_rg_dmac;
    sceDmaEnv env;
    int old, ch;
    if (!d) return 0;
    old = (int)(d->ctrl & 1u);
    for (ch = 0; ch < DMAC_NCH; ch++) {
        dmac_chan_regs *r = &d->ch[ch];
        if (!k_reset_ch[ch]) continue;
        r->sadr = 0;
        dmac_write_chcr(d, ch, 0);
        r->chcr = 0;
        r->tadr = 0;
        r->madr = 0;
        r->asr1 = 0;
        r->asr0 = 0;
    }
    dmac_hw_write32(d, DMAC_D_STAT, 0xFF1Fu);
    dmac_hw_write32(d, DMAC_D_STAT, dmac_hw_read32(d, DMAC_D_STAT) & 0xFF1F0000u);
    memset(&env, 0, sizeof env);
    sceDmaPutEnv(&env);
    if (mode == 1) dmac_hw_write32(d, DMAC_D_CTRL, d->ctrl | 1u);
    return old;
}

sceDmaChan *sceDmaGetChan(int id)
{
    if (!g_rg_dmac || (unsigned)id >= 10u) return NULL;
    return &g_rg_dmac->ch[id];
}

static int start(int ch, uint32_t chcr)
{
    dmac_write_chcr(g_rg_dmac, ch, chcr);
    return (int)chcr;
}

int (*rg_vif1_chain_hook)(uint32_t tadr, int tte, rg_vif1_chain_res *r);

/* the walked chain's effects, as dmac.c's run_pending / finish / charge would make them */
static void chain_done(dmac_state *d, sceDmaChan *c, uint32_t chcr, const rg_vif1_chain_res *r)
{
    uint64_t cyc = (uint64_t)(r->tags + r->qwords) * d->cycles_per_qword;
    d->stats[DMAC_VIF1].kicks++;
    d->stats[DMAC_VIF1].tags += r->tags;
    d->stats[DMAC_VIF1].qwords += r->qwords;
    d->stats[DMAC_VIF1].completions++;
    c->chcr = (chcr & 0xFFFFu & ~(DMAC_CHCR_STR | DMAC_CHCR_ASP)) | (r->last_tag & 0xFFFF0000u);
    c->tadr = r->tadr;
    c->madr = r->madr;
    if (r->irq && d->vif[1]) d->vif[1]->irq = 1;
    if (d->kernel) ps2k_raise_dmac(DMAC_VIF1);
    else d->stat_local |= 1u << DMAC_VIF1;
    if (cyc && d->kernel) {
        if (ps2k_get_thread_id() != 0 && !ps2k_in_handler()) ps2k_charge(cyc);
        else d->uncharged_cycles += cyc;
    }
    if (r->irq && d->kernel) ps2k_post_intc(PS2K_INTC_VIF1, 1);
    dmac_service(d);   /* what else the DMAC holds (PATH3), as after any VIF1 transfer */
}

int sceDmaSend(sceDmaChan *c, const void *tag)
{
    int ch = chan_of(c);
    uint32_t addr, chcr;
    if (ch < 0) return -1;
    addr = rg_dma_addr(tag);
    rg_dma_wait_idle(ch);
    if (c->tadr != 0xFFFFFFFFu) c->tadr = addr;
    c->qwc = 0;
    chcr = (c->chcr & ~0xDu) | 0x105u;
    if (ch == DMAC_VIF1 && rg_vif1_chain_hook) {
        rg_vif1_chain_res r;
        memset(&r, 0, sizeof r);
        if (rg_vif1_chain_hook(addr, (chcr & DMAC_CHCR_TTE) != 0, &r) == 0) {
            chain_done(g_rg_dmac, c, chcr, &r);
            return (int)chcr;
        }
    }
    return start(ch, chcr);
}

int sceDmaSendN(sceDmaChan *c, const void *addr, int qwc)
{
    int ch = chan_of(c);
    uint32_t a;
    if (ch < 0) return -1;
    a = rg_dma_addr(addr);
    rg_dma_wait_idle(ch);
    if (c->madr != 0xFFFFFFFFu) c->madr = a;
    c->qwc = (uint32_t)qwc & 0xFFFFu;
    return start(ch, (c->chcr & ~0xDu) | 0x101u);
}

int sceDmaRecv(sceDmaChan *c)
{
    int ch = chan_of(c);
    if (ch < 0) return -1;
    rg_dma_wait_idle(ch);
    c->qwc = 0;
    return start(ch, (((c->chcr & ~0xDu) | 0x4u) & ~0x2u) | 0x100u);
}

int sceDmaRecvN(sceDmaChan *c, void *addr, int qwc)
{
    int ch = chan_of(c);
    uint32_t a;
    if (ch < 0) return -1;
    a = rg_dma_addr(addr);
    rg_dma_wait_idle(ch);
    if (c->madr != 0xFFFFFFFFu) c->madr = a;
    c->qwc = (uint32_t)qwc & 0xFFFFu;
    return start(ch, (c->chcr & ~0xDu & ~0x1u) | 0x100u);
}

int sceDmaSync(sceDmaChan *c, int mode, int timeout)
{
    int ch = chan_of(c);
    (void)timeout;
    if (ch < 0) return 0;
    if (mode == 1) {
        if (dmac_busy(g_rg_dmac, ch)) {
            dmac_service(g_rg_dmac);
            if (dmac_busy(g_rg_dmac, ch)) rg_poll_charge();
        }
        return dmac_busy(g_rg_dmac, ch);
    }
    rg_dma_wait_idle(ch);
    return 0;
}

int sceDmaPause(sceDmaChan *c)
{
    int ch = chan_of(c);
    uint32_t old = c->chcr;
    if (ch < 0) return (int)old;
    dmac_write_chcr(g_rg_dmac, ch, old & ~DMAC_CHCR_STR);
    return (int)old;
}

int sceDmaRestart(sceDmaChan *c, int chcr)
{
    int ch = chan_of(c);
    uint32_t old = c->chcr;
    if (ch < 0) c->chcr = (uint32_t)chcr;
    else dmac_write_chcr(g_rg_dmac, ch, (uint32_t)chcr);
    return (int)((old >> 8) & 1u);
}
