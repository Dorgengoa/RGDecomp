/* SPDX-License-Identifier: CC0-1.0 */
/* GIF: PACKED formats (incl. Q latching, ADC, FOG, PRE), REGLIST padding,
 * NREG=0, NLOOP=0, packets split across writes, EOP + path arbitration, the
 * VU1 XGKICK adapter, SIGNAL/FINISH/LABEL with CSR/IMR and the IRQ hook. */
#include "gs_test_util.h"

static float qf(uint64_t rgbaq) { uint32_t u = (uint32_t)(rgbaq >> 32); float f; memcpy(&f, &u, 4); return f; }
static uint64_t fu(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }

static void packed_formats(void)
{
    gs_state *gs = gs_create();
    static pk p;
    gs->sw_raster = 0;
    /* PRE sets PRIM=SPRITE; regs: ST, RGBAQ, UV, XYZF2, FOG, XYZ2, NOP, A+D */
    pk_reset(&p);
    pk_tag(&p, 1, 1, 1, GS_PRIM_SPRITE, 0, 8, 0xEF5A4312ull);
    pk_qw(&p, fu(0.5f) | (fu(0.75f) << 32), fu(0.25f));          /* S, T, Q */
    pk_qw(&p, 10 | (20ull << 32), 30 | (40ull << 32));          /* R G B A */
    pk_qw(&p, 0x3FFF | (0x1234ull << 32) | (1ull << 20), 0);      /* U V (junk bit 20 dropped) */
    pk_qw(&p, 0x1230 | (0x4560ull << 32),
          (0xABCDEFull << 4) | (0x77ull << 36));                  /* X Y | Z F */
    pk_qw(&p, 0, 0x99ull << 36);                                  /* FOG */
    pk_qw(&p, 0x10 | (0x20ull << 32), 0xDEADBEEFull);             /* XYZ2 */
    pk_qw(&p, ~0ull, ~0ull);                                      /* NOP */
    pk_qw(&p, 0x123456, GS_FOGCOL);                               /* A+D */
    pk_send(gs, GS_PATH3, &p);

    CHECK_EQ(gs->reg[GS_PRIM], GS_PRIM_SPRITE);
    CHECK_EQ(gs->reg[GS_RGBAQ] & 0xFFFFFFFFu, 10 | (20 << 8) | (30 << 16) | (40u << 24));
    CHECK(qf(gs->reg[GS_RGBAQ]) == 0.25f);  /* Q from the packed ST */
    CHECK_EQ(gs->reg[GS_UV], 0x3FFF | (0x1234ull << 16));
    CHECK_EQ(gs->reg[GS_FOGCOL], 0x123456);
    /* the XYZF2 vertex then the XYZ2 vertex completed one sprite */
    CHECK_EQ(gs->stats.prims[GS_PRIM_SPRITE], 1);
    CHECK_EQ(gs->reg[GS_XYZF2], 0x1230 | (0x4560ull << 16) | (0xABCDEFull << 32) | (0x77ull << 56));
    CHECK_EQ(gs->reg[GS_XYZ2], 0x10 | (0x20ull << 16) | (0xDEADBEEFull << 32));
    CHECK_EQ(gs->reg[GS_FOG] >> 56, 0x99);

    /* Q resets to 1.0 at each GIFtag; ADC=1 makes XYZF2/XYZ2 the "3" forms */
    pk_tag(&p, 1, 1, 1, GS_PRIM_SPRITE, 0, 3, 0x541ull);
    pk_qw(&p, 1 | (2ull << 32), 3 | (4ull << 32));               /* RGBAQ */
    pk_qw(&p, 0x10 | (0x20ull << 32), (1ull << 47));              /* XYZF2, ADC */
    pk_qw(&p, 0x30 | (0x40ull << 32), 5 | (1ull << 47));          /* XYZ2, ADC */
    pk_send(gs, GS_PATH3, &p);
    CHECK(qf(gs->reg[GS_RGBAQ]) == 1.0f);
    CHECK_EQ(gs->reg[GS_XYZF3] & 0xFFFF, 0x10);
    CHECK_EQ(gs->reg[GS_XYZ3] >> 32, 5);
    CHECK_EQ(gs->stats.prims[GS_PRIM_SPRITE], 1);  /* no kick */
    CHECK_EQ(gs->vq_n, 0);                          /* but the queue advanced */
    gs_destroy(gs);
}

static void reglist_and_tags(void)
{
    gs_state *gs = gs_create();
    static pk p;
    gs->sw_raster = 0;
    /* REGLIST, NREG=3, NLOOP=1: 3 items = 2 qwords, the last half is padding;
     * then a second tag in the same packet must line up */
    pk_tag(&p, 1, 0, 0, 0, 1, 3, 0x3D1ull); /* RGBAQ, XYZ3, UV */
    pk_qw(&p, 0x11223344ull, 0x0000000500000006ull);
    pk_qw(&p, 0x00070008ull, 0xFFFFFFFFFFFFFFFFull);
    pk_tag(&p, 1, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_FOGCOL, 0xABCDEF);
    pk_send(gs, GS_PATH2, &p);
    CHECK_EQ(gs->reg[GS_RGBAQ], 0x11223344ull);
    CHECK_EQ(gs->reg[GS_XYZ3], 0x0000000500000006ull);
    CHECK_EQ(gs->reg[GS_UV], 0x00070008ull);
    CHECK_EQ(gs->reg[GS_FOGCOL], 0xABCDEF);
    CHECK(gs_path_idle(gs, GS_PATH2));

    /* NREG=0 means 16 */
    pk_tag(&p, 1, 1, 0, 0, 0, 0, 0xEEEEEEEEEEEEEEEEull);
    for (int i = 0; i < 16; i++) pk_ad(&p, GS_FOGCOL, (uint64_t)i);
    pk_tag(&p, 1, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_TEXA, 0x55);
    pk_send(gs, GS_PATH3, &p);
    CHECK_EQ(gs->reg[GS_FOGCOL], 15);
    CHECK_EQ(gs->reg[GS_TEXA], 0x55);

    /* NLOOP=0 tags (with and without EOP) carry no data */
    pk_tag(&p, 0, 0, 0, 0, 0, 1, 0xE);
    pk_tag(&p, 1, 0, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_FOGCOL, 0x42);
    pk_tag(&p, 0, 1, 0, 0, 0, 1, 0xE);
    pk_send(gs, GS_PATH3, &p);
    CHECK_EQ(gs->reg[GS_FOGCOL], 0x42);
    CHECK(gs_path_idle(gs, GS_PATH3));

    /* a packet split mid-data across three writes */
    pk_tag(&p, 3, 1, 0, 0, 0, 1, 0xE);
    pk_send(gs, GS_PATH3, &p);
    CHECK(!gs_path_idle(gs, GS_PATH3));
    pk_ad(&p, GS_FOGCOL, 1);
    pk_send(gs, GS_PATH3, &p);
    pk_ad(&p, GS_FOGCOL, 2);
    pk_ad(&p, GS_FOGCOL, 3);
    pk_send(gs, GS_PATH3, &p);
    CHECK_EQ(gs->reg[GS_FOGCOL], 3);
    CHECK(gs_path_idle(gs, GS_PATH3));
    gs_destroy(gs);
}

static void arbitration(void)
{
    gs_state *gs = gs_create();
    static pk p;
    /* PATH3 starts a packet (first tag has no EOP) */
    pk_tag(&p, 1, 0, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_FOGCOL, 3);
    pk_send(gs, GS_PATH3, &p);
    CHECK_EQ(gs->bus_owner, GS_PATH3);
    /* PATH1 and PATH2 packets arrive meanwhile: queued */
    pk_tag(&p, 1, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_FOGCOL, 2);
    pk_send(gs, GS_PATH2, &p);
    pk_tag(&p, 1, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_FOGCOL, 1);
    pk_send(gs, GS_PATH1, &p);
    CHECK_EQ(gs->reg[GS_FOGCOL], 3);
    CHECK(!gs_path_idle(gs, GS_PATH1));
    CHECK(!gs_path_idle(gs, GS_PATH2));
    /* PATH3 ends its packet: then PATH1 (higher priority), then PATH2 */
    pk_tag(&p, 1, 1, 0, 0, 0, 1, 0xE);
    pk_ad(&p, GS_FOGCOL, 4);
    pk_send(gs, GS_PATH3, &p);
    CHECK_EQ(gs->reg[GS_FOGCOL], 2);   /* PATH2 ran last */
    CHECK_EQ(gs->path[1].packets, 1);
    CHECK_EQ(gs->path[2].packets, 1);
    CHECK_EQ(gs->path[3].packets, 1);
    CHECK(gs_path_idle(gs, GS_PATH1) && gs_path_idle(gs, GS_PATH2) && gs_path_idle(gs, GS_PATH3));
    CHECK_EQ(gs->bus_owner, 0);

    /* XGKICK adapter: a VU1 memory image of a packet goes to PATH1 */
    uint64_t vumem[4] = { 1 | (1ull << 15) | (1ull << 60), 0xE, 0x777, GS_FOGCOL };
    gs_vu1_gif_sink(gs, (const uint8_t *)vumem, 32, 0x100);
    CHECK_EQ(gs->reg[GS_FOGCOL], 0x777);
    CHECK_EQ(gs->path[1].packets, 2);
    gs_destroy(gs);
}

static uint32_t g_irq_bits;
static void irq_cb(void *u, uint32_t bits) { (void)u; g_irq_bits |= bits; }

static void signal_finish(void)
{
    gs_state *gs = gs_create();
    gs->irq = irq_cb;
    g_irq_bits = 0;
    ad(gs, GS_SIGNAL, 0x12345678ull | (0x0000FFFFull << 32));
    CHECK_EQ(gs_read_priv(gs, GS_P_SIGLBLID) & 0xFFFFFFFF, 0x5678);
    CHECK(gs_read_priv(gs, GS_P_CSR) & GS_CSR_SIGNAL);
    CHECK_EQ(g_irq_bits, 0);  /* IMR masks everything after reset */
    gs_write_priv(gs, GS_P_CSR, GS_CSR_SIGNAL);
    CHECK(!(gs_read_priv(gs, GS_P_CSR) & GS_CSR_SIGNAL));
    gs_write_priv(gs, GS_P_IMR, 0x7F00 & ~(1u << 9)); /* unmask FINISH */
    ad(gs, GS_FINISH, 0);
    CHECK(gs_read_priv(gs, GS_P_CSR) & GS_CSR_FINISH);
    CHECK_EQ(g_irq_bits, GS_CSR_FINISH);
    ad(gs, GS_LABEL, 0xAAAA0000ull | (0xFFFF0000ull << 32));
    CHECK_EQ(gs_read_priv(gs, GS_P_SIGLBLID) >> 32, 0xAAAA0000ull);
    /* VSync toggles FIELD only when interlaced */
    gs_vsync(gs);
    CHECK(!(gs_read_priv(gs, GS_P_CSR) & GS_CSR_FIELD));
    gs_write_priv(gs, GS_P_SMODE2, 1);
    gs_vsync(gs);
    CHECK(gs_read_priv(gs, GS_P_CSR) & GS_CSR_FIELD);
    gs_vsync(gs);
    CHECK(!(gs_read_priv(gs, GS_P_CSR) & GS_CSR_FIELD));
    CHECK(gs_read_priv(gs, GS_P_CSR) & GS_CSR_VSINT);
    /* CSR.RESET restores the power-on register state, keeps VRAM */
    gs->vram[100] = 7;
    gs_write_priv(gs, GS_P_CSR, GS_CSR_RESET);
    CHECK_EQ(gs->reg[GS_FOGCOL], 0);
    CHECK_EQ(gs->vram[100], 7);
    gs_destroy(gs);
}

int test_gif(const char *name)
{
    if (!strcmp(name, "gif_packed")) { packed_formats(); return 1; }
    if (!strcmp(name, "gif_reglist_tags")) { reglist_and_tags(); return 1; }
    if (!strcmp(name, "gif_arbitration")) { arbitration(); return 1; }
    if (!strcmp(name, "gif_signal")) { signal_finish(); return 1; }
    return 0;
}
