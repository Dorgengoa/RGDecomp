/* SPDX-License-Identifier: CC0-1.0 */
/* libdma / libgraph / libpkt SDK surface over the DMAC and GS models
 * (docs/DMAC.md "SDK surface").  Types have the SDK's field offsets; the
 * functions follow the retail asm bodies (census/platform_sdk_surface.tsv,
 * families libdma, libgraph, libpkt), including return values. */
#ifndef RG_SCE_LIBDMA_H
#define RG_SCE_LIBDMA_H

#include <stdint.h>
#include <stdio.h>

#include "dmac.h"
#include "gs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ---- binding (platform glue / tests) ----
 * The SDK functions operate on one DMAC + GS pair.  VIF1 comes from
 * dmac->vif[1].  Must be called before the game's first SDK call. */
void sce_graphics_bind(dmac_state *dmac, gs_state *gs);
dmac_state *sce_graphics_dmac(void);
gs_state *sce_graphics_gs(void);

/* ---- libdma ---- */
/* x64 (docs/X64-PLAN.md): SDK structs live in game memory with 4-byte pointers */
#ifndef SCE_P32
#if defined(_WIN64)
#define SCE_P32 __ptr32 __uptr
#else
#define SCE_P32
#endif
#endif
typedef dmac_chan_regs sceDmaChan;   /* 0x90 bytes, CHCR at 0 */

typedef struct sceDmaEnv {
    uint8_t sts, std, mfd, rcycle;  /* D_CTRL fields, as channel ids / cycle count */
    uint16_t express;               /* D_PCR.CDE (bits 16-25) */
    uint16_t notify;                /* D_PCR.CPC (bits 0-9) */
    uint16_t sqwc, tqwc;            /* D_SQWC */
    void * SCE_P32 rbadr;           /* D_RBOR */
    uint32_t rbmsk;                 /* D_RBSR */
} sceDmaEnv;                        /* 0x14 bytes */

int sceDmaReset(int mode);                      /* returns the old D_CTRL.DMAE */
int sceDmaPutEnv(sceDmaEnv *env);               /* 0, or -1..-4 for a bad sts/std/mfd/rcycle */
sceDmaEnv *sceDmaGetEnv(sceDmaEnv *env);
sceDmaChan *sceDmaGetChan(int id);              /* NULL for id > 9 */
int sceDmaSend(sceDmaChan *d, const void *tag); /* chain mode; returns the CHCR value written */
int sceDmaSendN(sceDmaChan *d, const void *addr, int qwc); /* normal mode */
int sceDmaRecv(sceDmaChan *d);                  /* destination chain (SIF0/fromSPR) */
int sceDmaRecvN(sceDmaChan *d, void *addr, int qwc);
/* mode 0: wait for idle, returns 0 (always idle here unless held, see DMAC.md);
 * mode 1: returns CHCR.STR (1 = busy) */
int sceDmaSync(sceDmaChan *d, int mode, int timeout);
int sceDmaPause(sceDmaChan *d);                 /* clears STR, returns the old CHCR */

/* The frame chain without the DMAC / VIF models (docs/NATIVE-RENDER.md "Frame chain walker"):
 * when set, sceDmaSend on channel 1 offers the chain to the hook first; 0 = walked (the hook
 * fed the GS and filled r), anything else = the DMAC runs it as before.  sceDmaSend then
 * applies what the DMAC would have: CHCR / TADR / MADR, the channel-1 completion, the VIF1
 * interrupt for an i bit (posted one cycle after the kick), the modelled cost. */
typedef struct rg_vif1_chain_res {
    uint32_t tags, qwords, last_tag, tadr, madr;
    int irq;
} rg_vif1_chain_res;
extern int (*rg_vif1_chain_hook)(uint32_t tadr, int tte, rg_vif1_chain_res *r);
/* rg_sce_graphics_native (libdma_native.c, RG_NATIVE_ONLY rg-game): transfer counters */
void sce_graphics_native_stats(FILE *f);
int sceDmaRestart(sceDmaChan *d, int chcr);

#ifdef __cplusplus
}
#endif
#endif
