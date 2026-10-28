/* SPDX-License-Identifier: CC0-1.0 */
/* libdma without the DMAC model (RG_NATIVE_ONLY rg-game: rg_sce_graphics_native,
 * docs/NATIVE-RENDER.md "DMA without the DMAC").  The game's DMA sends are what the
 * hardware would have moved, done at the call:
 *
 *   channel 1 (VIF1), chain   the frame's draw list: the native walker (libdma.h
 *                             rg_vif1_chain_hook, src/native/render/nr_fx.c) feeds the GS
 *                             input with the DIRECT payloads and hands VU work to the VIF1 /
 *                             VU1 models (the overlay programs not native yet)
 *   channel 2 (GIF), chain / normal   GIF packets (texture uploads FixedTexUploadImpl,
 *                             GfxFlipBuffersMaybe's environment, sceGsPutDrawEnv, movie
 *                             frames): straight to the GS input (PATH3)
 *   channel 0 (VIF0)          the VU0 microcode upload (Vif0SendInitPacketMaybe): VU0 macros
 *                             are plain C (RG_VU0_MODE=native), nothing to load
 *
 * The channel register blocks the game touches (sceDmaGetChan: CHCR, MADR, QWC, TADR) are
 * plain memory here; a send leaves CHCR.STR clear (the transfer is done when the call
 * returns, as with the synchronous DMAC model).  The kernel sees what the DMAC model made it
 * see: the channel's completion (D_STAT.CISn) per transfer and, for a VIF1 i bit (the
 * frame's end-of-frame NOP), the VIF1 interrupt posted one cycle after the kick
 * (Vif1IntcHandler_15e170).  Costs: none (the native kernel's logic time ignores them). */
#include <stdio.h>
#include <string.h>

#include "graphics_internal.h"
#include "ps2k.h"
#include "ps2k_fpu.h"

dmac_state *g_rg_dmac;   /* always NULL here (graphics_internal.h) */
gs_state *g_rg_gs;

void sce_graphics_bind(dmac_state *dmac, gs_state *gs)
{
    (void)dmac;
    g_rg_gs = gs;
}

dmac_state *sce_graphics_dmac(void) { return NULL; }
gs_state *sce_graphics_gs(void) { return g_rg_gs; }

static dmac_chan_regs g_ch[DMAC_NCH];
static sceDmaEnv g_env;
static uint32_t g_ctrl;

#ifdef __cplusplus
static_assert(sizeof(sceDmaEnv) == 0x14, "sceDmaEnv");
#else
_Static_assert(sizeof(sceDmaEnv) == 0x14 || sizeof(void *) != 4, "sceDmaEnv is 0x14 bytes on i686");
_Static_assert(sizeof(sceDmaChan) == 0x90, "sceDmaChan");
#endif

uint32_t rg_dma_addr(const void *p) { return (uint32_t)(uintptr_t)p; }
void rg_poll_charge(void) {}
int rg_dma_wait_idle(int ch) { (void)ch; return 0; }

int (*rg_vif1_chain_hook)(uint32_t tadr, int tte, rg_vif1_chain_res *r);

static int chan_of(const sceDmaChan *c)
{
    int ch;
    for (ch = 0; ch < DMAC_NCH; ch++)
        if (c == &g_ch[ch]) return ch;
    return -1;
}

static struct { uint64_t sends[DMAC_NCH], gif_qw, vif1_fail, other; } g_st;

static void unsupported(int ch, uint32_t chcr, const char *what)
{
    static int warned[DMAC_NCH];
    g_st.other++;
    if (!warned[ch]++)
        fprintf(stderr, "libdma (native): channel %d CHCR 0x%08X: %s, ignored\n", ch, chcr, what);
}

/* set by the native renderer (nr_runtime_attach_gpu): the GIF channel's packets as its
 * immediate records (docs/NATIVE-RENDER.md checkpoint 9); NULL: straight to the GS */
void (*rg_gif3_hook)(const void *qw, uint32_t nqw);

static void gif(const void *p, uint32_t qwc)
{
    if (qwc && rg_gif3_hook) rg_gif3_hook(p, qwc);
#if !(defined(RG_NATIVE_GS) && RG_NATIVE_GS)
    else if (qwc && g_rg_gs) gs_gif_write(g_rg_gs, GS_PATH3, p, qwc);
#endif
    g_st.gif_qw += qwc;
}

/* a GIF source chain (tags not transferred: the GIF channel has no TTE) */
static void gif_chain(sceDmaChan *c, uint32_t tadr)
{
    uint32_t stack[2], sp = 0, tags = 0, lo = 0, madr = 0;
    int done = 0;
    while (!done && ++tags < (1u << 20)) {
        const uint8_t *t = (const uint8_t *)(uintptr_t)tadr;
        uint32_t hi, qwc, id;
        if (tadr < 0x10000u || (tadr & 0x80000000u)) { unsupported(DMAC_GIF, c->chcr, "chain tag at a bad / scratchpad address"); break; }
        memcpy(&lo, t, 4);
        memcpy(&hi, t + 4, 4);
        qwc = lo & 0xFFFF;
        id = (lo >> 28) & 7;
        switch (id) {
        case 1: madr = tadr + 16; tadr = madr + qwc * 16; break;            /* CNT */
        case 2: madr = tadr + 16; tadr = hi; break;                          /* NEXT */
        case 3: case 4: madr = hi; tadr += 16; break;                        /* REF / REFS */
        case 0: madr = hi; tadr += 16; done = 1; break;                      /* REFE */
        case 5: madr = tadr + 16; if (sp < 2) stack[sp++] = madr + qwc * 16; tadr = hi; break;   /* CALL */
        case 6: madr = tadr + 16; if (sp) tadr = stack[--sp]; else { tadr = madr + qwc * 16; done = 1; } break;   /* RET */
        default: madr = tadr + 16; done = 1; break;                          /* END */
        }
        if (qwc) {
            if (madr < 0x10000u || (madr & 0x80000000u)) { unsupported(DMAC_GIF, c->chcr, "data at a bad / scratchpad address"); break; }
            gif((const void *)(uintptr_t)madr, qwc);
            madr += qwc * 16;
        }
    }
    c->tadr = tadr;
    c->madr = madr;
    c->chcr = (c->chcr & 0xFFFFu) | (lo & 0xFFFF0000u);
}

/* CHCR written with STR: the transfer, then what the DMAC model's finish() did */
int rg_dma_start(int ch, uint32_t chcr)
{
    sceDmaChan *c = &g_ch[ch];
    uint32_t mod = (chcr >> 2) & 3u;
    int irq = 0;
    c->chcr = (chcr & 0xFFFFu) | (c->chcr & 0xFFFF0000u);
    g_st.sends[ch]++;
    if (ch == DMAC_VIF1 && mod == 1 && (chcr & 1u)) {
        rg_vif1_chain_res r;
        memset(&r, 0, sizeof r);
        if (rg_vif1_chain_hook && rg_vif1_chain_hook(c->tadr, (chcr & DMAC_CHCR_TTE) != 0, &r) == 0) {
            c->chcr = (c->chcr & 0xFFFFu & ~DMAC_CHCR_ASP) | (r.last_tag & 0xFFFF0000u);
            c->tadr = r.tadr;
            c->madr = r.madr;
            irq = r.irq;
        } else {
            g_st.vif1_fail++;
            unsupported(ch, chcr, "a VIF1 chain the walker cannot take");
        }
    } else if (ch == DMAC_GIF && mod == 1) {
        gif_chain(c, c->tadr);
    } else if (ch == DMAC_GIF && mod == 0) {
        if (c->madr >= 0x10000u && !(c->madr & 0x80000000u)) gif((const void *)(uintptr_t)c->madr, c->qwc);
        c->madr += c->qwc * 16;
        c->qwc = 0;
    } else if (ch == DMAC_VIF0) {
        /* VU0 microcode / data: VU0 is plain C natively */
    } else {
        unsupported(ch, chcr, "no native transfer for this channel / mode");
    }
    c->chcr &= ~(DMAC_CHCR_STR | DMAC_CHCR_ASP);
    ps2k_raise_dmac(ch);
    if (irq) ps2k_post_intc(PS2K_INTC_VIF1, 1);
    return (int)chcr;
}

/* ------------------------------------------------------------------ */

int sceDmaPutEnv(sceDmaEnv *env)
{
    if (env->sts >= 10) return -1;
    if (env->std >= 10) return -2;
    if (env->mfd >= 10) return -3;
    if (env->rcycle >= 7) return -4;
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
    static const uint8_t k_reset_ch[DMAC_NCH] = {1, 1, 1, 1, 1, 0, 0, 0, 1, 1};
    sceDmaEnv env;
    int old = (int)(g_ctrl & 1u), ch;
    for (ch = 0; ch < DMAC_NCH; ch++)
        if (k_reset_ch[ch]) memset(&g_ch[ch], 0, sizeof g_ch[ch]);
    memset(&env, 0, sizeof env);
    sceDmaPutEnv(&env);
    if (mode == 1) g_ctrl |= 1u;
    return old;
}

sceDmaChan *sceDmaGetChan(int id) { return (unsigned)id < 10u ? &g_ch[id] : NULL; }

int sceDmaSend(sceDmaChan *c, const void *tag)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    int ch = chan_of(c);
    if (ch < 0) return -1;
    if (c->tadr != 0xFFFFFFFFu) c->tadr = rg_dma_addr(tag);
    c->qwc = 0;
    return rg_dma_start(ch, (c->chcr & ~0xDu) | 0x105u);
}

int sceDmaSendN(sceDmaChan *c, const void *addr, int qwc)
{
    int ch = chan_of(c);
    if (ch < 0) return -1;
    if (c->madr != 0xFFFFFFFFu) c->madr = rg_dma_addr(addr);
    c->qwc = (uint32_t)qwc & 0xFFFFu;
    return rg_dma_start(ch, (c->chcr & ~0xDu) | 0x101u);
}

int sceDmaRecv(sceDmaChan *c)
{
    int ch = chan_of(c);
    if (ch < 0) return -1;
    unsupported(ch, c->chcr, "receive");
    return (int)c->chcr;
}

int sceDmaRecvN(sceDmaChan *c, void *addr, int qwc)
{
    int ch = chan_of(c);
    (void)addr; (void)qwc;
    if (ch < 0) return -1;
    unsupported(ch, c->chcr, "receive");
    return (int)c->chcr;
}

int sceDmaSync(sceDmaChan *c, int mode, int timeout)
{
    (void)c; (void)mode; (void)timeout;
    return 0;
}

int sceDmaPause(sceDmaChan *c)
{
    uint32_t old = c->chcr;
    c->chcr &= ~DMAC_CHCR_STR;
    return (int)old;
}

int sceDmaRestart(sceDmaChan *c, int chcr)
{
    uint32_t old = c->chcr;
    c->chcr = (uint32_t)chcr & ~DMAC_CHCR_STR;   /* nothing is ever held */
    return (int)((old >> 8) & 1u);
}

void sce_graphics_native_stats(FILE *f)
{
    if (!f) return;
    fprintf(f, "libdma (native): sends VIF0 %llu VIF1 %llu GIF %llu (%llu GIF qwords to the GS), VIF1 chains not walked %llu, "
               "other transfers ignored %llu\n",
            (unsigned long long)g_st.sends[0], (unsigned long long)g_st.sends[1], (unsigned long long)g_st.sends[2],
            (unsigned long long)g_st.gif_qw, (unsigned long long)g_st.vif1_fail, (unsigned long long)g_st.other);
}
