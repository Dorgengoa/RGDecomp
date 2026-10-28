/* SPDX-License-Identifier: CC0-1.0 */
/* The libdma / libgraph / libpkt entry points under the names the decompiled
 * game calls them by (game/EXCLUDED.tsv: their asm bodies are excluded from
 * the build, PLAN.md transform 6, and bound here).  Functions whose game name
 * is the SDK name (sceGsPutDispEnv, sceDmaGetChan, sceGifPkCnt, ...) are
 * defined once, in libgraph.c / libdma.c / libpkt.c.
 *
 * sceDmaSync_10a2e0, sceGifPkInit_10a400, sceGifPkReset_10a410 and
 * sceGsGetGParam_1082a0 have C bodies in the game tree and are compiled from
 * there; sceDmaSync_10a2e0 reaches DmaWaitChannelIdle_109bb8 below. */
#include "graphics_internal.h"
#include "libpkt.h"

int sceGsResetGraph_108110(short mode, short inter, short omode, short ffmode)
{
    return sceGsResetGraph(mode, inter, omode, ffmode);
}
void sceGsSetDefDispEnv_1083c8(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    sceGsSetDefDispEnv(disp, psm, w, h, dx, dy);
}
int sceGsSyncPath_109030(int mode, int timeout) { return sceGsSyncPath(mode, (uint16_t)timeout); }
int sceGsSyncVCallback_109b18(int (*func)(int)) { return sceGsSyncVCallback(func); }

int sceDmaSend_10a040(sceDmaChan *d, const void *tag) { return sceDmaSend(d, tag); }
int sceDmaSendN_10a0a8(sceDmaChan *d, const void *addr, int qwc) { return sceDmaSendN(d, addr, qwc); }
int sceDmaRecv_10a198(sceDmaChan *d) { return sceDmaRecv(d); }
int sceDmaRecvN_10a1e0(sceDmaChan *d, void *addr, int qwc) { return sceDmaRecvN(d, addr, qwc); }
int sceDmaPause_10a350(sceDmaChan *d) { return sceDmaPause(d); }
int sceDmaRestart_10a3e8(sceDmaChan *d, int chcr) { return sceDmaRestart(d, chcr); }

/* libdma internal, reached from the game's C sceDmaSync_10a2e0.  NOTE: that
 * file declares it `(void)`, so until prototype unification passes the
 * channel, `chan` is whatever the stack holds; anything that is not one of
 * the DMAC's channel blocks is ignored (every transfer is synchronous). */
#if RG_GRAPHICS_NATIVE
int DmaWaitChannelIdle_109bb8(sceDmaChan *chan) { (void)chan; return 0; }   /* nothing is ever in flight */
uint32_t DmaAddrFromSpr_109cb0(uint32_t addr) { return addr; }
#else
int DmaWaitChannelIdle_109bb8(sceDmaChan *chan)
{
    int ch = g_rg_dmac ? dmac_chan_index(g_rg_dmac, chan) : -1;
    return ch < 0 ? 0 : rg_dma_wait_idle(ch);
}
uint32_t DmaAddrFromSpr_109cb0(uint32_t addr) { return g_rg_dmac ? dmac_canon_addr(g_rg_dmac, addr) : addr; }
#endif

uint32_t *sceGifPkTerminate_10a420(sceGifPacket *pk) { return sceGifPkTerminate(pk); }
