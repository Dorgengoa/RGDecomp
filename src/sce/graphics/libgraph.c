/* SPDX-License-Identifier: CC0-1.0 */
/* libgraph over the GS + DMAC models.  Register values, struct packing and
 * return values follow the retail asm bodies (game/src/main/sdk/sceGs*.c,
 * gs/sceGsSetDefDispEnv_1083c8.c, sys/sceGsSyncVCallback_109b18.c).  The
 * waits retail does by polling (CHCR.STR, VIF1_STAT, GS CSR, INTC_STAT) are
 * immediate here because the models complete synchronously; sceGsSyncV
 * blocks the thread on the kernel instead of spinning.  docs/DMAC.md. */
#include <stdio.h>
#include <string.h>

#include "graphics_internal.h"
#include "ps2k.h"
#include "rg_threads.h" /* sceGsSyncV is a frame-driver point (docs/NATIVE-THREADS.md) */
#include "ps2k_fpu.h"

int sce_graphics_debug_syncv_nowait;

static sceGsGParam g_gp = {1, 2, 1, 3, 0, 0}; /* retail D_00445ED0 initial value */

sceGsGParam *sceGsGetGParam(void) { return &g_gp; }

#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
/* no GS model (docs/NATIVE-RENDER.md "Checkpoint 10"): the privileged registers are the native
 * state block's (src/native/render/nr_hw.c), the GIF paths the native GIF input's (nr_gs.c) */
unsigned long long rg_gs_priv_r64(unsigned int addr);
void rg_gs_priv_w64(unsigned int addr, unsigned long long v);
void nr_gs_gif_reset(void);
int nr_gs_path_idle(int path);
int nr_psm_bpp(int psm);
#define gs_psm_bpp nr_psm_bpp
static void gs_w(uint32_t addr, uint64_t v) { rg_gs_priv_w64(addr, v); }
static uint64_t gs_r(uint32_t addr) { return rg_gs_priv_r64(addr); }
#define GIF_RESET() nr_gs_gif_reset()
#define GIF_IDLE(p) nr_gs_path_idle(p)
#define HAVE_GIF 1
#else
static void gs_w(uint32_t addr, uint64_t v)
{
    if (g_rg_gs) gs_write_priv(g_rg_gs, addr, v);
}

static uint64_t gs_r(uint32_t addr)
{
    return g_rg_gs ? gs_read_priv(g_rg_gs, addr) : 0;
}
#define GIF_RESET() do { if (g_rg_gs) gs_gif_reset(g_rg_gs); } while (0)
#define GIF_IDLE(p) gs_path_idle(g_rg_gs, p)
#define HAVE_GIF (g_rg_gs != NULL)
#endif

/* kernel SetGsCrt(interlace, omode, ffmode): the CRTC mode.  Only SMODE2 is
 * visible to the GS model (INT, FFMD). */
static void set_gs_crt(int inter, int omode, int ff)
{
    (void)omode;
    gs_w(GS_P_SMODE2, (uint64_t)(inter & 1) | ((uint64_t)(ff & 1) << 1));
}

static void remove_vsync_cb(void)
{
    ps2k_disable_intc(PS2K_INTC_VBLANK_START, 0);
    ps2k_remove_intc_handler(PS2K_INTC_VBLANK_START, g_gp.sceGsVSCid);
}

int sceGsResetGraph(short mode, short inter, short omode, short ffmode)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    if (mode == 1) {
        gs_w(GS_P_CSR, 0x100); /* FLUSH */
        return 0x12001000;     /* retail returns the CSR address left in $v0 */
    }
    if (mode != 0 && mode != 5) return mode < 2 ? 1 : 5;
    if (mode == 0) gs_w(GS_P_CSR, 0x200); /* GS reset */
    g_gp.sceGsInterMode = inter;
    g_gp.sceGsOutMode = omode;
    g_gp.sceGsVersion = (int16_t)((gs_r(GS_P_CSR) >> 16) & 0xFF);
    if (mode == 0) gs_w(GS_P_IMR, 0xFF00);
    g_gp.sceGsFFMode = ffmode != 0;
    if (mode == 0 && g_gp.sceGsVSCfunc) {
        remove_vsync_cb();
        g_gp.sceGsVSCid = 0;
        g_gp.sceGsVSCfunc = 0;
    }
    set_gs_crt(inter & 1, omode & 0xFF, ffmode & 1);
    return 0;
}

void sceGsResetPath(void)
{
#if RG_GRAPHICS_NATIVE
    /* no VIF1 / VU1 to reset natively (libdma_native.c); GIF_CTRL = RST */
    GIF_RESET();
}
#else
    static const uint32_t vif_init[8] = {
        0x01000404u, 0x20000000u, 0x00000000u, 0x05000000u, /* STCYCL 4/4, STMASK 0, STMOD 0 */
        0x06000000u, 0x03000000u, 0x02000000u, 0x04000000u, /* MSKPATH3 0, BASE 0, OFFSET 0, ITOP 0 */
    };
    dmac_state *d = g_rg_dmac;
    if (!d) return;
    dmac_vif_reset(d, 1);                          /* VIF1_FBRST = RST */
    if (d->vif[1] && d->vif[1]->vu) vu_reset_regs(d->vif[1]->vu); /* FBRST (vi28) VU1 reset */
    dmac_vif_fifo_write(d, 1, vif_init, 2);
    /* GIF_CTRL = RST */
    GIF_RESET();
}
#endif

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    int32_t off[4] = {0, 0, 0, 0}; /* GetGsDxDyOffset: 0 (see DMAC.md) */
    int inter = g_gp.sceGsInterMode, ff = g_gp.sceGsFFMode, omode = (uint16_t)g_gp.sceGsOutMode;
    disp->pmode = 0x66;
    disp->smode2 = inter == 0 ? 2 : ff != 0 ? 3 : 1;
    disp->dispfb = ((uint64_t)(psm & 0xF) << 15) | ((uint64_t)(((w + 63) >> 6) & 0x3F) << 9);
    if (omode == 2 || omode == 3) {
        int32_t magh = w ? (w + 0x9FF) / w : 0;
        int32_t x0 = omode == 2 ? 0x27C : 0x290, ydx, dh;
        uint64_t vdx, vdy;
        if ((uint16_t)inter == 1) {
            ydx = omode == 2 ? 0x32 : 0x48;
            dh = ff ? 2 * h - 1 : h - 1;
        } else {
            ydx = omode == 2 ? 0x19 : 0x24;
            dh = h - 1;
        }
        vdy = (uint64_t)((dy + off[1] + ydx) & 0xFFF);
        vdx = (uint64_t)((magh * dx + off[0] + x0) & 0xFFF);
        disp->display = vdx | (vdy << 12) | ((uint64_t)(uint32_t)(magh - 1) << 23) |
                        ((uint64_t)(uint32_t)(magh * w - 1) << 32) | ((uint64_t)(uint32_t)dh << 44);
    } else if (omode == 0x50) {
        uint64_t vdx = (uint64_t)((((0x2D0 - w) / 2) * 2 + off[0] + dx * 2 + 0xE8) & 0xFFF);
        uint64_t vdy = (uint64_t)((dy + off[1] + 0x23) & 0xFFF);
        disp->display = vdx | 0x800000u | (vdy << 12) | ((uint64_t)(uint32_t)(2 * w - 1) << 32) |
                        ((uint64_t)(uint32_t)(h - 1) << 44);
    } else {
        fprintf(stderr, "sceGsSetDefDispEnv: invalid output mode %d\n", omode);
    }
    disp->bgcolor = 0;
}

void sceGsPutDispEnv(sceGsDispEnv *disp)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    gs_w(GS_P_PMODE, disp->pmode);
    if (g_gp.sceGsVersion == 1) { /* first GS revision: circuit 1 */
        gs_w(GS_P_DISPFB1, disp->dispfb);
        gs_w(GS_P_DISPLAY1, disp->display);
        gs_w(GS_P_EXTDATA, disp->bgcolor);
        return;
    }
    gs_w(GS_P_SMODE2, disp->smode2);
    gs_w(GS_P_DISPFB2, disp->dispfb);
    gs_w(GS_P_DISPLAY2, disp->display);
    gs_w(GS_P_BGCOLOR, disp->bgcolor);
}

short sceGszbufaddr(short psm, short w, short h)
{
    int32_t wp = (w + 63 > -1 ? w + 63 : w + 126) >> 6;
    int32_t hp = (psm & 2) ? (h + 63 > -1 ? h + 63 : h + 126) >> 6 : (h + 31 > -1 ? h + 31 : h + 62) >> 5;
    int32_t pages = wp * hp;
    int field_mode = g_gp.sceGsInterMode == 1 && g_gp.sceGsFFMode == 0;
    return field_mode ? (short)pages : (short)(pages << 1);
}

int sceGsSetDefDrawEnv(sceGsDrawEnv1 *draw, short psm, short w, short h, short ztest, short zpsm)
{
    uint64_t zb = (uint64_t)(uint32_t)(int32_t)sceGszbufaddr(psm, w, h);
    draw->frame1addr = GS_FRAME_1;
    draw->frame1 = ((uint64_t)(((w + 63) >> 6) & 0x3F) << 16) | ((uint64_t)(psm & 0xF) << 24);
    draw->zbuf1addr = GS_ZBUF_1;
    zb = (uint64_t)(int64_t)(int16_t)zb; /* retail keeps the value sign-extended from 16 bits */
    draw->zbuf1 = zb | ((uint64_t)(zpsm & 0xF) << 24) | (ztest == 0 ? 1ull << 32 : 0);
    draw->xyoffset1 = ((uint64_t)(int64_t)(0x800 - (w >> 1)) << 4) |
                      ((uint64_t)(int64_t)(0x800 - (h >> 1)) << 36);
    draw->xyoffset1addr = GS_XYOFFSET_1;
    draw->scissor1 = ((uint64_t)(int64_t)(w - 1) << 16) | ((uint64_t)(int64_t)(h - 1) << 48);
    draw->scissor1addr = GS_SCISSOR_1;
    draw->prmodecont |= 1;
    draw->prmodecontaddr = GS_PRMODECONT;
    draw->colclamp |= 1;
    draw->colclampaddr = GS_COLCLAMP;
    draw->dtheaddr = GS_DTHE;
    if (psm & 2) draw->dthe |= 1;
    else draw->dthe &= ~1ull;
    draw->test1addr = GS_TEST_1;
    draw->test1 = ztest ? (((uint64_t)(ztest & 3) << 17) | 0x10000) : 0x30000;
    return 8;
}

int sceGsPutDrawEnv(sceGifTagRaw *giftag)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
#if RG_GRAPHICS_NATIVE
    sceDmaChan *c = sceDmaGetChan(DMAC_GIF);
    c->qwc = (uint32_t)(giftag->lo & 0x7FFF) + 1;
    c->madr = rg_dma_addr(giftag);
    rg_dma_start(DMAC_GIF, 0x101);
    return 0;
#else
    dmac_state *d = g_rg_dmac;
    dmac_chan_regs *r;
    if (!d) return -1;
    if (rg_dma_wait_idle(DMAC_GIF) < 0) {
        fprintf(stderr, "sceGsPutDrawEnv: DMA Ch.2 does not terminate\n");
        return -1;
    }
    r = &d->ch[DMAC_GIF];
    r->qwc = (uint32_t)(giftag->lo & 0x7FFF) + 1;
    r->madr = rg_dma_addr(giftag);
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    return 0;
#endif
}

int sceGsSetDefClear(sceGsClear *cp, short ztest, short x, short y, short w, short h,
                     uint32_t r, uint32_t g, uint32_t b, uint32_t a, uint32_t z)
{
    uint64_t zz = (uint64_t)z << 32;
    cp->testa = 0x30000;
    cp->testaaddr = GS_TEST_1;
    cp->prim = GS_PRIM_SPRITE;
    cp->primaddr = GS_PRIM;
    cp->rgbaq = (uint64_t)(r & 0xFF) | ((uint64_t)(g & 0xFF) << 8) | ((uint64_t)(b & 0xFF) << 16) |
                ((uint64_t)(a & 0xFF) << 24) | (0x3F800000ull << 32);
    cp->rgbaqaddr = GS_RGBAQ;
    cp->xyz2a = (uint64_t)(int64_t)(x << 4) | ((uint64_t)(int64_t)(y << 4) << 16) | zz;
    cp->xyz2aaddr = GS_XYZ2;
    cp->xyz2b = (uint64_t)(int64_t)((x + w) << 4) | ((uint64_t)(int64_t)((y + h) << 4) << 16) | zz;
    cp->xyz2baddr = GS_XYZ2;
    cp->testb = ztest ? (((uint64_t)(ztest & 3) << 17) | 0x10000) : 0x30000;
    cp->testbaddr = GS_TEST_1;
    return 6;
}

static void dbuff_tag(sceGifTagRaw *t, int clear)
{
    t->lo = 0;
    t->hi = 0;
    t->lo = (t->lo & ~0x7FFFull) | (uint64_t)(clear ? 14 : 8) | 0x8000; /* NLOOP, EOP */
    t->lo = (t->lo & (~0ull >> 4)) | (1ull << 60);                       /* NREG 1 */
    t->hi = (t->hi & ~0xFull) | 0xE;                                      /* A+D */
}

void sceGsSetDefDBuff(sceGsDBuff *db, short psm, short w, short h, short ztest, short zpsm, short clear)
{
    short zb;
    sceGsSetDefDispEnv(&db->disp[0], psm, w, h, 0, 0);
    sceGsSetDefDispEnv(&db->disp[1], psm, w, h, 0, 0);
    sceGsSetDefDrawEnv(&db->draw0, psm, w, h, ztest, zpsm);
    sceGsSetDefDrawEnv(&db->draw1, psm, w, h, ztest, zpsm);
    if (clear) {
        short cx = (short)(0x800 - (w >> 1)), cy = (short)(0x800 - (h >> 1));
        sceGsSetDefClear(&db->clear0, ztest, cx, cy, w, h, 0, 0, 0, 0, 0);
        sceGsSetDefClear(&db->clear1, ztest, cx, cy, w, h, 0, 0, 0, 0, 0);
    }
    dbuff_tag(&db->giftag0, clear);
    dbuff_tag(&db->giftag1, clear);
    zb = sceGszbufaddr(psm, w, h);
    /* field mode, or non-interlaced: the second buffer starts half a z
     * allocation in (retail writes disp[1].dispfb.FBP and draw0.frame.FBP) */
    if ((g_gp.sceGsInterMode == 1 && g_gp.sceGsFFMode == 0) || g_gp.sceGsInterMode == 0) {
        uint64_t fbp = (uint64_t)((zb >> 1) & 0x1FF);
        db->draw0.frame1 = (db->draw0.frame1 & ~0x1FFull) | fbp;
        db->disp[1].dispfb = (db->disp[1].dispfb & ~0x1FFull) | fbp;
    }
}

int sceGsSwapDBuff(sceGsDBuff *db, int id)
{
    PS2K_FPU_HOST_SCOPE; /* host float rules (ps2k_fpu.h) */
    sceGsPutDispEnv(&db->disp[id & 1]);
    return sceGsPutDrawEnv(id & 1 ? &db->giftag1 : &db->giftag0);
}

/* ------------------------------------------------------------------ VSync */

/* Block the calling guest thread until the next VBLANK_START is processed
 * by the kernel.  Retail busy-waits on INTC_STAT (VSync_116a30); docs/SPIN.md
 * requires a block so lower-priority threads run and the pacing hook sees an
 * idle jump.  ps2k_wait_vblank is a kernel-private wait: it takes no
 * game-visible semaphore or alarm id, and readies the thread after that
 * VBLANK_START's handlers have run (docs/KERNEL.md). */
static void wait_vblank(void)
{
    static int warned;
    if (ps2k_get_thread_id() == 0 || ps2k_in_handler()) {
        if (!warned++) fprintf(stderr, "sceGsSyncV: not called from a guest thread; not waiting\n");
        return;
    }
    if (ps2k_wait_vblank() < 0 && !warned++)
        fprintf(stderr, "sceGsSyncV: no VBLANK_START can arrive (VBlank events off?)\n");
}

int sceGsSyncV(int mode)
{
    (void)mode;
    if (!sce_graphics_debug_syncv_nowait) wait_vblank();
    /* RG_THREADS=native|frame: a driver point after the wait (the driven steps woken by
     * this VBlank run before the caller continues, as the HLE ran them) */
    if (rg_frame_native()) rg_frame_point();
    if (g_gp.sceGsInterMode == 1) return (int)((gs_r(GS_P_CSR) >> 13) & 1);
    return 1;
}

int sceGsSyncVCallback(int (*func)(int))
{
    int32_t old = g_gp.sceGsVSCfunc;
    if (!func) {
        remove_vsync_cb();
        g_gp.sceGsVSCfunc = 0;
        g_gp.sceGsVSCid = 0;
        return old;
    }
    if (old) remove_vsync_cb();
    g_gp.sceGsVSCfunc = (int32_t)(intptr_t)func;
    g_gp.sceGsVSCid = ps2k_add_intc_handler(PS2K_INTC_VBLANK_START, (ps2k_handler_fn)func, -1);
    ps2k_enable_intc(PS2K_INTC_VBLANK_START, 0);
    return old;
}

int sceGsSyncPath(int mode, uint16_t timeout)
{
#if RG_GRAPHICS_NATIVE
    /* no DMA channel or VIF1 is ever busy natively; the GIF paths drain on the GS side */
    int gif_path_busy = 0, p;
    (void)timeout;
    if (HAVE_GIF)
        for (p = 1; p <= 3; p++)
            if (!GIF_IDLE(p)) gif_path_busy = 1;
    if (mode != 0) return gif_path_busy ? 0x10 : 0;
    if (gif_path_busy) {
        fprintf(stderr, "sceGsSyncPath: time out (GIF path busy)\n");
        return -1;
    }
    return 0;
#else
    dmac_state *d = g_rg_dmac;
    int vif1_busy, gif_path_busy = 0, p;
    (void)timeout;
    if (!d) return 0;
    dmac_service(d);
    vif1_busy = d->vif[1] && !vif_idle(d->vif[1]);
    if (HAVE_GIF)
        for (p = 1; p <= 3; p++)
            if (!GIF_IDLE(p)) gif_path_busy = 1;
    if (mode != 0) {
        int m = 0;
        if (dmac_busy(d, DMAC_VIF1)) m |= 1;
        if (dmac_busy(d, DMAC_GIF)) m |= 2;
        if (vif1_busy) m |= 4;
        if (gif_path_busy) m |= 0x10;
        if (m) rg_poll_charge();
        return m;
    }
    if (dmac_busy(d, DMAC_VIF1) || dmac_busy(d, DMAC_GIF) || vif1_busy || gif_path_busy) {
        fprintf(stderr, "sceGsSyncPath: time out (VIF1 CHCR=0x%08X GIF CHCR=0x%08X vif1 %s, GIF path %s)\n",
                d->ch[DMAC_VIF1].chcr, d->ch[DMAC_GIF].chcr, vif1_busy ? "busy" : "idle",
                gif_path_busy ? "busy" : "idle");
        return -1;
    }
    return 0;
#endif
}

/* ------------------------------------------------------------------ images */

int sceGsSetDefStoreImage(sceGsStoreImage *sp, short sbp, short sbw, short spsm,
                          short x, short y, short w, short h)
{
    sp->vifcode[0] = 0;           /* NOP */
    sp->vifcode[1] = 0x06008000u; /* MSKPATH3 (mask) */
    sp->vifcode[2] = 0x13000000u; /* FLUSHA */
    sp->vifcode[3] = 0x50000006u; /* DIRECT 6 */
    sp->giftag.lo = 5 | 0x8000 | (1ull << 60);
    sp->giftag.hi = 0xE;
    sp->bitbltbuf = (uint64_t)(int64_t)sbp | ((uint64_t)(uint32_t)sbw << 16) |
                    ((uint64_t)(int64_t)spsm << 24);
    sp->bitbltbufaddr = GS_BITBLTBUF;
    sp->trxpos = (uint64_t)(uint32_t)(int32_t)x | ((uint64_t)(uint32_t)y << 16);
    sp->trxposaddr = GS_TRXPOS;
    sp->trxreg = (uint64_t)(int64_t)w | ((uint64_t)(int64_t)h << 32);
    sp->trxregaddr = GS_TRXREG;
    sp->finish = 0;
    sp->finishaddr = GS_FINISH;
    sp->trxdir = 1;
    sp->trxdiraddr = GS_TRXDIR;
    return 7;
}

#if !RG_GRAPHICS_NATIVE
static int store_fail(const char *why)
{
    fprintf(stderr, "sceGsExecStoreImage: %s\n", why);
    gs_w(GS_P_CSR, 0x100);
    gs_w(GS_P_BUSDIR, 0);
    /* GIF_CTRL = RST; VIF1_FBRST = RST */
    GIF_RESET();
    if (g_rg_dmac) dmac_vif_reset(g_rg_dmac, 1);
    return -1;
}
#endif

int (*rg_gs_store_hook)(uint64_t bitbltbuf, uint64_t trxpos, uint64_t trxreg, void *dst, int bytes, int fifo_bytes);

#if RG_GRAPHICS_NATIVE
int sceGsExecStoreImage(sceGsStoreImage *sp, void *dstaddr)
{
    /* local->host reads natively (the renderer serves them: rg_gs_store_hook); the two
     * channel-1 completions the DMA path raised, as in the oracle */
    uint8_t *dst = (uint8_t *)dstaddr;
    int32_t w = (int32_t)(sp->trxreg & 0xFFF), h = (int32_t)((sp->trxreg >> 32) & 0xFFF);
    int psm = (int)((sp->bitbltbuf >> 24) & 0x3F);
    int32_t bytes = 0, total = 0, hh = h, dmaq;
    switch (psm) {
    case 0x00: case 0x30: bytes = w * h * 4; hh = (h + 3) & 0x1FFC; total = (w * hh) >> 2; break;
    case 0x01: case 0x31: bytes = w * h * 3; hh = (h + 15) & 0x1FF0; total = (w * hh * 3) >> 4; break;
    case 0x02: case 0x0A: case 0x32: case 0x3A:
        bytes = w * h * 2; hh = (h + 7) & ~7; total = (w * hh) >> 3; break;
    case 0x13: case 0x1B: bytes = w * h; hh = (h + 7) & ~7; total = (w * hh) >> 4; break;
    case 0x14: case 0x24: case 0x2C: bytes = (w * h) >> 1; hh = (h + 7) & ~7; total = (w * hh) >> 5; break;
    default: hh = 0; break;
    }
    if ((bytes & 0xF) != 0)
        sp->trxreg = (uint64_t)(uint32_t)w | ((uint64_t)(uint32_t)hh << 32); /* padded height */
    dmaq = (bytes >> 4) & ~7;
    if (bytes <= 0) return 0;
    if (!rg_gs_store_hook || rg_gs_store_hook(sp->bitbltbuf, sp->trxpos, sp->trxreg, dst, bytes, total * 16) != 0) {
        static int warned;
        if (!warned++) fprintf(stderr, "sceGsExecStoreImage: no native local->host read (renderer off?)\n");
        memset(dst, 0, (size_t)bytes);
        return -1;
    }
    ps2k_raise_dmac(DMAC_VIF1);
    if (dmaq) ps2k_raise_dmac(DMAC_VIF1);
    return 0;
}
#else
int sceGsExecStoreImage(sceGsStoreImage *sp, void *dstaddr)
{
    static const uint32_t release[4] = {0x06000000u, 0, 0, 0}; /* retail 0x445F00: MSKPATH3 0 + NOPs */
    dmac_state *d = g_rg_dmac;
    uint8_t *dst = (uint8_t *)dstaddr;
    int32_t w = (int32_t)(sp->trxreg & 0xFFF), h = (int32_t)((sp->trxreg >> 32) & 0xFFF);
    int psm = (int)((sp->bitbltbuf >> 24) & 0x3F);
    int32_t bytes = 0, total = 0, hh = h, extra = 0, dmaq, cpuq, rem, i;
    uint64_t imr;
    dmac_chan_regs *r;
    uint8_t tmp[16];
    if (!d) return -1;
    switch (psm) {
    case 0x00: case 0x30: bytes = w * h * 4; hh = (h + 3) & 0x1FFC; total = (w * hh) >> 2; break;
    case 0x01: case 0x31: bytes = w * h * 3; hh = (h + 15) & 0x1FF0; total = (w * hh * 3) >> 4; break;
    case 0x02: case 0x0A: case 0x32: case 0x3A:
        bytes = w * h * 2; hh = (h + 7) & ~7; total = (w * hh) >> 3; break;
    case 0x13: case 0x1B: bytes = w * h; hh = (h + 7) & ~7; total = (w * hh) >> 4; break;
    case 0x14: case 0x24: case 0x2C: bytes = (w * h) >> 1; hh = (h + 7) & ~7; total = (w * hh) >> 5; break;
    default: hh = 0; break; /* retail computes no size: nothing is read back */
    }
    rem = bytes & 0xF;
    dmaq = (bytes >> 4) & ~7;
    cpuq = (bytes >> 4) & 7;
    if (rem) {
        extra = total - dmaq - cpuq - 1;
        sp->trxreg = (uint64_t)(uint32_t)w | ((uint64_t)(uint32_t)hh << 32); /* padded height */
    }
    if (rg_gs_store_hook && bytes > 0 && rg_dma_wait_idle(DMAC_VIF1) == 0 &&
        rg_gs_store_hook(sp->bitbltbuf, sp->trxpos, sp->trxreg, dst, bytes, total * 16) == 0) {
        /* the native store: no VIF1 DMA, no FIFO.  The kernel still sees the channel-1
         * completions the two DMA transfers would have raised (D_STAT bits, and the run
         * hash folds the kernel trace: emu and native runs stay comparable;
         * docs/NATIVE-RENDER.md "Run hash") */
        if (d->kernel) {
            ps2k_raise_dmac(DMAC_VIF1);
            if (dmaq) ps2k_raise_dmac(DMAC_VIF1);
        }
        return 0;
    }
    if (rg_dma_wait_idle(DMAC_VIF1) < 0) return store_fail("DMA Ch.1 does not terminate");
    imr = gs_r(GS_P_IMR);
    gs_w(GS_P_IMR, imr | 0x200); /* mask FINISH */
    gs_w(GS_P_CSR, 2);           /* clear FINISH */
    /* VIF1 normal mode, 7 qwords: MSKPATH3, FLUSHA, DIRECT -> BITBLTBUF..TRXDIR=1 */
    r = &d->ch[DMAC_VIF1];
    r->qwc = 7;
    r->madr = rg_dma_addr(sp);
    dmac_write_chcr(d, DMAC_VIF1, 0x101);
    if (rg_dma_wait_idle(DMAC_VIF1) < 0) return store_fail("DMA Ch.1 does not terminate");
    if (!(gs_r(GS_P_CSR) & 2)) {
        dmac_vif_fifo_write(d, 1, release, 1);
        fprintf(stderr, "sceGsExecStoreImage: GS does not finish\n");
        return -1;
    }
    gs_w(GS_P_BUSDIR, 1); /* VIF1_STAT.FDR = 1 (GS -> EE) is implicit in the VIF1 readback path */
    if (dmaq) {
        r->qwc = (uint32_t)dmaq;
        r->madr = rg_dma_addr(dst);
        dmac_write_chcr(d, DMAC_VIF1, 0x100);
        if (rg_dma_wait_idle(DMAC_VIF1) < 0) return store_fail("DMA Ch.1 does not terminate (readback)");
    }
    for (i = 0; i < cpuq; i++)
        if (dmac_vif1_fifo_read(d, dst + (dmaq + i) * 16, 1) < 16) return store_fail("VIF1 FIFO empty");
    if (rem) {
        if (dmac_vif1_fifo_read(d, tmp, 1) < 16) return store_fail("VIF1 FIFO empty");
        memcpy(dst + (dmaq + cpuq) * 16, tmp, (size_t)rem);
        for (i = 0; i < extra; i++)
            if (dmac_vif1_fifo_read(d, tmp, 1) < 16) return store_fail("VIF1 FIFO empty");
    }
    gs_w(GS_P_BUSDIR, 0);
    gs_w(GS_P_IMR, imr);
    gs_w(GS_P_CSR, 2);
    dmac_vif_fifo_write(d, 1, release, 1); /* MSKPATH3 off: held PATH3 resumes */
    return 0;
}
#endif

int sceGsSetDefLoadImage(sceGsLoadImage *lp, short dbp, short dbw, short dpsm,
                         short x, short y, short w, short h)
{
    uint32_t bpp = (uint32_t)gs_psm_bpp(dpsm);
    uint32_t qwc = ((uint32_t)w * (uint32_t)h * bpp + 127) / 128;
    lp->giftag0.lo = 4 | (1ull << 60);
    lp->giftag0.hi = 0xE;
    lp->bitbltbuf = ((uint64_t)(uint16_t)dbp << 32) | ((uint64_t)(dbw & 0x3F) << 48) |
                    ((uint64_t)(dpsm & 0x3F) << 56);
    lp->bitbltbufaddr = GS_BITBLTBUF;
    lp->trxpos = ((uint64_t)(x & 0x7FF) << 32) | ((uint64_t)(y & 0x7FF) << 48);
    lp->trxposaddr = GS_TRXPOS;
    lp->trxreg = (uint64_t)(w & 0xFFF) | ((uint64_t)(h & 0xFFF) << 32);
    lp->trxregaddr = GS_TRXREG;
    lp->trxdir = 0;
    lp->trxdiraddr = GS_TRXDIR;
    lp->giftag1.lo = (qwc & 0x7FFF) | 0x8000 | (2ull << 58);
    lp->giftag1.hi = 0;
    return 6;
}

int sceGsExecLoadImage(sceGsLoadImage *lp, const void *srcaddr)
{
#if RG_GRAPHICS_NATIVE
    sceDmaChan *c = sceDmaGetChan(DMAC_GIF);
    c->qwc = 6;
    c->madr = rg_dma_addr(lp);
    rg_dma_start(DMAC_GIF, 0x101);
    c->qwc = (uint32_t)(lp->giftag1.lo & 0x7FFF);
    c->madr = rg_dma_addr(srcaddr);
    rg_dma_start(DMAC_GIF, 0x101);
    return 0;
#else
    dmac_state *d = g_rg_dmac;
    dmac_chan_regs *r;
    uint32_t qwc = (uint32_t)(lp->giftag1.lo & 0x7FFF);
    if (!d) return -1;
    if (rg_dma_wait_idle(DMAC_GIF) < 0) return -1;
    r = &d->ch[DMAC_GIF];
    r->qwc = 6;
    r->madr = rg_dma_addr(lp);
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    if (rg_dma_wait_idle(DMAC_GIF) < 0) return -1;
    r->qwc = qwc;
    r->madr = rg_dma_addr(srcaddr);
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    return 0;
#endif
}
