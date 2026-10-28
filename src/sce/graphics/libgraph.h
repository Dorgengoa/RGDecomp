/* SPDX-License-Identifier: CC0-1.0 */
/* libgraph SDK surface over the GS model (docs/DMAC.md "SDK surface").
 * Struct layouts are the SDK's (the game's per-file views use the same
 * offsets); bit packing follows the retail asm bodies. */
#ifndef RG_SCE_LIBGRAPH_H
#define RG_SCE_LIBGRAPH_H

#include <stdint.h>

#include "libdma.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct { uint64_t lo, hi; } __attribute__((aligned(16))) sceGifTagRaw; /* 128-bit GIFtag */

/* libgraph's private parameter block (retail D_00445ED0) */
typedef struct sceGsGParam {
    int16_t sceGsInterMode;   /* 0x0 interlace */
    int16_t sceGsOutMode;     /* 0x2 omode (2 NTSC, 3 PAL, 0x50 DTV) */
    int16_t sceGsFFMode;      /* 0x4 1 = FRAME, 0 = FIELD */
    int16_t sceGsVersion;     /* 0x6 CSR.REV */
    int32_t sceGsVSCfunc;     /* 0x8 sync-V callback (non-zero = installed) */
    int32_t sceGsVSCid;       /* 0xC its INTC handler id */
} sceGsGParam;

typedef struct sceGsDispEnv {
    uint64_t pmode, smode2, dispfb, display, bgcolor;
} sceGsDispEnv;                                       /* 0x28 */

typedef struct sceGsDrawEnv1 {
    uint64_t frame1, frame1addr;
    uint64_t zbuf1, zbuf1addr;
    uint64_t xyoffset1, xyoffset1addr;
    uint64_t scissor1, scissor1addr;
    uint64_t prmodecont, prmodecontaddr;
    uint64_t colclamp, colclampaddr;
    uint64_t dthe, dtheaddr;
    uint64_t test1, test1addr;
} __attribute__((aligned(16))) sceGsDrawEnv1;         /* 0x80 */

typedef struct sceGsClear {
    uint64_t testa, testaaddr;
    uint64_t prim, primaddr;
    uint64_t rgbaq, rgbaqaddr;
    uint64_t xyz2a, xyz2aaddr;
    uint64_t xyz2b, xyz2baddr;
    uint64_t testb, testbaddr;
} __attribute__((aligned(16))) sceGsClear;            /* 0x60 */

typedef struct sceGsDBuff {
    sceGsDispEnv disp[2];      /* 0x000 */
    sceGifTagRaw giftag0;      /* 0x050 */
    sceGsDrawEnv1 draw0;       /* 0x060 */
    sceGsClear clear0;         /* 0x0E0 */
    sceGifTagRaw giftag1;      /* 0x140 */
    sceGsDrawEnv1 draw1;       /* 0x150 */
    sceGsClear clear1;         /* 0x1D0 */
} __attribute__((aligned(16))) sceGsDBuff;            /* 0x230 */

typedef struct sceGsStoreImage {
    uint32_t vifcode[4];       /* NOP, MSKPATH3(1), FLUSHA, DIRECT(6) */
    sceGifTagRaw giftag;
    uint64_t bitbltbuf, bitbltbufaddr;
    uint64_t trxpos, trxposaddr;
    uint64_t trxreg, trxregaddr;
    uint64_t finish, finishaddr;
    uint64_t trxdir, trxdiraddr;
} __attribute__((aligned(16))) sceGsStoreImage;       /* 0x70 */

typedef struct sceGsLoadImage {
    sceGifTagRaw giftag0;
    uint64_t bitbltbuf, bitbltbufaddr;
    uint64_t trxpos, trxposaddr;
    uint64_t trxreg, trxregaddr;
    uint64_t trxdir, trxdiraddr;
    sceGifTagRaw giftag1;
} __attribute__((aligned(16))) sceGsLoadImage;        /* 0x60 */

sceGsGParam *sceGsGetGParam(void);
/* mode 0: GS reset + IMR 0xFF00 + SetGsCrt; 1: CSR.FLUSH only; 5: SetGsCrt only */
int sceGsResetGraph(short mode, short inter, short omode, short ffmode);
void sceGsResetPath(void);
void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy);
void sceGsPutDispEnv(sceGsDispEnv *disp);
int sceGsSetDefDrawEnv(sceGsDrawEnv1 *draw, short psm, short w, short h, short ztest, short zpsm); /* 8 */
int sceGsPutDrawEnv(sceGifTagRaw *giftag);          /* GIF normal-mode kick of NLOOP+1 qwords; 0 */
int sceGsSetDefClear(sceGsClear *cp, short ztest, short x, short y, short w, short h,
                     uint32_t r, uint32_t g, uint32_t b, uint32_t a, uint32_t z); /* 6 */
short sceGszbufaddr(short psm, short w, short h);
void sceGsSetDefDBuff(sceGsDBuff *db, short psm, short w, short h, short ztest, short zpsm, short clear);
int sceGsSwapDBuff(sceGsDBuff *db, int id);
/* Blocks the calling thread until the next VBLANK_START; returns CSR.FIELD
 * when interlaced, else 1. */
int sceGsSyncV(int mode);
/* mode 0: wait for PATH1/2/3 idle (immediate here), 0; else a busy mask */
int sceGsSyncPath(int mode, uint16_t timeout);
/* installs func on INTC VBLANK_START (AddIntcHandler(2, func, -1)); returns the old one */
int sceGsSyncVCallback(int (*func)(int));
int sceGsSetDefStoreImage(sceGsStoreImage *sp, short sbp, short sbw, short spsm,
                          short x, short y, short w, short h); /* 7 */
int sceGsExecStoreImage(sceGsStoreImage *sp, void *dstaddr);  /* 0 / -1 */
/* Native store (docs/NATIVE-RENDER.md "Lens-flare depth probe"): when set, a
 * local->host read is served by it (the renderer reads the GS buffer
 * rectangle as the transfer would deliver it, fifo_bytes bytes, padding
 * included; bytes go to dst) instead of the VIF1 DMA / FIFO path.  0 done,
 * -1 not served (the DMA path runs). */
extern int (*rg_gs_store_hook)(uint64_t bitbltbuf, uint64_t trxpos, uint64_t trxreg, void *dst, int bytes,
                               int fifo_bytes);
/* Not in the census (the game does not call them); SDK semantics. */
int sceGsSetDefLoadImage(sceGsLoadImage *lp, short dbp, short dbw, short dpsm,
                         short x, short y, short w, short h);
int sceGsExecLoadImage(sceGsLoadImage *lp, const void *srcaddr);

/* ---- platform glue ---- */
/* DELIBERATELY WRONG (test control): sceGsSyncV returns without waiting. */
extern int sce_graphics_debug_syncv_nowait;

#ifdef __cplusplus
}
#endif
#endif
