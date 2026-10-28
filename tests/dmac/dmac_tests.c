/* SPDX-License-Identifier: CC0-1.0 */
/* DMAC model + libdma/libgraph/libpkt tests (docs/DMAC.md).  ctest -L dmac
 * Run one: rg-dmac-tests <name>; "<name>_control" runs a deliberately wrong
 * variant that must fail. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmac.h"
#include "gs.h"
#include "libdma.h"
#include "libgraph.h"
#include "libpkt.h"
#include "ps2k.h"
#include "vif.h"
#include "vu.h"
#include "vu_retail.h"

static int g_fail;
static int g_control;
static int g_skip;

#define CHECK(c)                                                                        \
    do {                                                                                \
        if (!(c)) {                                                                     \
            printf("FAIL %s:%d: %s\n", __FILE__, __LINE__, #c);                         \
            g_fail++;                                                                   \
        }                                                                               \
    } while (0)
#define CHECKX(a, b)                                                                    \
    do {                                                                                \
        unsigned long long a_ = (unsigned long long)(a), b_ = (unsigned long long)(b);  \
        if (a_ != b_) {                                                                 \
            printf("FAIL %s:%d: %s = 0x%llX, expected 0x%llX\n", __FILE__, __LINE__, #a, \
                   a_, b_);                                                             \
            g_fail++;                                                                   \
        }                                                                               \
    } while (0)

/* ------------------------------------------------------------------ helpers */

#define RAM_SIZE (32u << 20)
static uint8_t *g_ram;

static uint8_t *ram(uint32_t a) { return g_ram + a; }

static void put32(uint32_t a, uint32_t v) { memcpy(ram(a), &v, 4); }

/* source-chain DMAtag: w0 = qwc | id<<28 | irq<<31, w1 = addr; w2/w3 upper half */
static void tag(uint32_t at, uint32_t qwc, uint32_t id, int irq, uint32_t addr, uint32_t w2, uint32_t w3)
{
    put32(at, qwc | (id << 28) | (irq ? 0x80000000u : 0));
    put32(at + 4, addr);
    put32(at + 8, w2);
    put32(at + 12, w3);
}

/* a data qword whose 4 words all carry `v` */
static void dq(uint32_t at, uint32_t v)
{
    put32(at, v); put32(at + 4, v); put32(at + 8, v); put32(at + 12, v);
}

/* recorder peripheral: data qword markers and tag halves, in order */
typedef struct rec {
    uint32_t items[512];
    int n;
    int tags;
    uint32_t bytes;
} rec;

static void rec_out(void *user, int ch, const uint8_t *p, uint32_t bytes, uint32_t flags)
{
    rec *r = (rec *)user;
    (void)ch;
    r->bytes += bytes;
    if (flags & DMAC_OUT_TAG) {
        uint32_t w2;
        memcpy(&w2, p, 4);
        if (r->n < 512) r->items[r->n++] = 0xEE000000u | (w2 & 0xFFFFFFu);
        r->tags++;
        return;
    }
    for (uint32_t o = 0; o + 16 <= bytes; o += 16) {
        uint32_t w;
        memcpy(&w, p + o, 4);
        if (r->n < 512) r->items[r->n++] = w;
    }
}

static dmac_state *new_guest_dmac(void)
{
    dmac_state *d = dmac_create();
    if (!g_ram) g_ram = (uint8_t *)calloc(1, RAM_SIZE);
    else memset(g_ram, 0, RAM_SIZE);
    d->kernel = 0;
    dmac_map_guest_ram(d, g_ram, RAM_SIZE);
    return d;
}

static int kick_chain(dmac_state *d, int ch, uint32_t tadr, uint32_t extra_chcr)
{
    dmac_chan_regs *r = dmac_chan(d, ch);
    r->tadr = tadr;
    r->qwc = 0;
    dmac_write_chcr(d, ch, 0x105u | extra_chcr); /* DIR, chain, STR */
    return !dmac_busy(d, ch);
}

/* ------------------------------------------------------------------ chain walking */

static void t_chain_tags(void)
{
    dmac_state *d = new_guest_dmac();
    rec r;
    static const uint32_t want[] = {
        0xEE0000A1, 0xA, 0xEE0000A2, 0xB, 0xEE0000A3, 0xC, 0xD, 0xEE0000A4, 0xE,
        0xEE0000A5, 0xF, 0xEE0000A6, 0xEE0000A7, 0x10, 0xEE0000A8, 0x11,
        0xEE0000A9, 0xEE0000AA, 0x12};
    memset(&r, 0, sizeof r);
    d->debug_ret_ends_chain = g_control;
    dmac_set_out(d, DMAC_VIF1, rec_out, &r);
    /* CNT -> NEXT -> REF -> REFS -> CALL(-> CALL(-> CNT -> RET) -> RET) -> REFE.
     * The tag upper halves carry 0xA1.. so the TTE stream is visible. */
    tag(0x1000, 1, DMAC_TAG_CNT, 0, 0, 0xA1, 0); dq(0x1010, 0xA);
    tag(0x1020, 1, DMAC_TAG_NEXT, 0, 0x2000, 0xA2, 0); dq(0x1030, 0xB);
    tag(0x2000, 2, DMAC_TAG_REF, 0, 0x3000, 0xA3, 0); dq(0x3000, 0xC); dq(0x3010, 0xD);
    tag(0x2010, 1, DMAC_TAG_REFS, 0, 0x3100, 0xA4, 0); dq(0x3100, 0xE);
    tag(0x2020, 1, DMAC_TAG_CALL, 0, 0x4000, 0xA5, 0); dq(0x2030, 0xF);
    tag(0x4000, 0, DMAC_TAG_CALL, 0, 0x5000, 0xA6, 0);
    tag(0x5000, 1, DMAC_TAG_CNT, 0, 0, 0xA7, 0); dq(0x5010, 0x10);
    tag(0x5020, 1, DMAC_TAG_RET, 0, 0, 0xA8, 0); dq(0x5030, 0x11);
    tag(0x4010, 0, DMAC_TAG_RET, 0, 0, 0xA9, 0);
    tag(0x2040, 1, DMAC_TAG_REFE, 0, 0x3200, 0xAA, 0); dq(0x3200, 0x12);
    CHECK(kick_chain(d, DMAC_VIF1, 0x1000, DMAC_CHCR_TTE));
    CHECK(r.n == (int)(sizeof want / sizeof want[0]));
    for (int i = 0; i < r.n && i < (int)(sizeof want / sizeof want[0]); i++) {
        if (r.items[i] != want[i]) {
            printf("  item %d: 0x%08X, expected 0x%08X\n", i, r.items[i], want[i]);
            g_fail++;
            break;
        }
    }
    {
        dmac_chan_regs *c = dmac_chan(d, DMAC_VIF1);
        CHECKX(c->chcr & 0x1FF, 0x045);      /* STR clear, ASP 0, TTE + chain + DIR kept */
        CHECKX(c->qwc, 0);
        CHECKX(c->madr, 0x3210);
        CHECKX(c->tadr, 0x2050);
        CHECKX(c->chcr >> 16, 0x0000);        /* TAG field = upper half of the REFE tag's word 0 */
        CHECK(d->stats[DMAC_VIF1].tags == 10);
        CHECK(d->stats[DMAC_VIF1].qwords == 9);      /* data qwords (tags counted apart) */
        CHECK(d->stat_local & (1u << DMAC_VIF1)); /* CIS latched (no kernel bound) */
    }

    /* TTE off: no tag halves; END ends; RET with ASP 0 ends */
    memset(&r, 0, sizeof r);
    tag(0x6000, 1, DMAC_TAG_CNT, 0, 0, 0xB1, 0); dq(0x6010, 0x21);
    tag(0x6020, 1, DMAC_TAG_END, 0, 0, 0xB2, 0); dq(0x6030, 0x22);
    tag(0x6040, 1, DMAC_TAG_CNT, 0, 0, 0xB3, 0); dq(0x6050, 0x99); /* never reached */
    CHECK(kick_chain(d, DMAC_VIF1, 0x6000, 0));
    CHECK(r.n == 2 && r.items[0] == 0x21 && r.items[1] == 0x22 && r.tags == 0);
    memset(&r, 0, sizeof r);
    tag(0x7000, 1, DMAC_TAG_RET, 0, 0, 0, 0); dq(0x7010, 0x31);
    tag(0x7020, 1, DMAC_TAG_CNT, 0, 0, 0, 0); dq(0x7030, 0x99);
    CHECK(kick_chain(d, DMAC_VIF1, 0x7000, 0));
    CHECK(r.n == 1 && r.items[0] == 0x31);

    /* IRQ bit: stops the chain only with CHCR.TIE */
    memset(&r, 0, sizeof r);
    tag(0x8000, 1, DMAC_TAG_CNT, 1, 0, 0, 0); dq(0x8010, 0x41);
    tag(0x8020, 1, DMAC_TAG_END, 0, 0, 0, 0); dq(0x8030, 0x42);
    CHECK(kick_chain(d, DMAC_VIF1, 0x8000, DMAC_CHCR_TIE));
    CHECK(r.n == 1 && r.items[0] == 0x41);
    CHECKX(dmac_chan(d, DMAC_VIF1)->chcr >> 16, 0x9000); /* TAG field: IRQ | id CNT */
    memset(&r, 0, sizeof r);
    CHECK(kick_chain(d, DMAC_VIF1, 0x8000, 0));
    CHECK(r.n == 2);

    /* a third nested CALL overflows the address stack: stop + BEIS */
    memset(&r, 0, sizeof r);
    d->stat_local = 0;
    tag(0x9000, 0, DMAC_TAG_CALL, 0, 0x9100, 0, 0);
    tag(0x9100, 0, DMAC_TAG_CALL, 0, 0x9200, 0, 0);
    tag(0x9200, 0, DMAC_TAG_CALL, 0, 0x9300, 0, 0);
    tag(0x9300, 0, DMAC_TAG_END, 0, 0, 0, 0);
    kick_chain(d, DMAC_VIF1, 0x9000, 0);
    CHECK(!dmac_busy(d, DMAC_VIF1));
    CHECK(d->stat_local & 0x8000u);
    CHECK(!(d->stat_local & (1u << DMAC_VIF1)));

    /* REF into the scratchpad (address bit 31) */
    memset(&r, 0, sizeof r);
    memset(d->spr + 0x3FF0, 0x51, 16);
    memset(d->spr, 0x52, 16);
    tag(0xA000, 2, DMAC_TAG_REFE, 0, 0x80003FF0u, 0, 0); /* wraps at 16 KB */
    CHECK(kick_chain(d, DMAC_VIF1, 0xA000, 0));
    CHECK(r.n == 2 && r.items[0] == 0x51515151u && r.items[1] == 0x52525252u);

    /* uncached / UCAB mirrors resolve to the same RAM in guest mode */
    memset(&r, 0, sizeof r);
    tag(0xB000, 1, DMAC_TAG_REF, 0, 0x2000B100u, 0, 0); dq(0xB100, 0x61);
    tag(0xB010, 1, DMAC_TAG_REFE, 0, 0x3000B110u, 0, 0); dq(0xB110, 0x62);
    CHECK(kick_chain(d, DMAC_VIF1, 0x2000B000u, 0));
    CHECK(r.n == 2 && r.items[0] == 0x61 && r.items[1] == 0x62);

    /* a bad address is a bus error, not a crash */
    memset(&r, 0, sizeof r);
    d->stat_local = 0;
    tag(0xC000, 1, DMAC_TAG_REFE, 0, 0x12000000u, 0, 0);
    kick_chain(d, DMAC_VIF1, 0xC000, 0);
    CHECK(!dmac_busy(d, DMAC_VIF1) && (d->stat_local & 0x8000u) && d->bus_errors >= 1);
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ normal / SPR / interleave */

static void t_normal_spr(void)
{
    dmac_state *d = new_guest_dmac();
    rec r;
    dmac_chan_regs *c;
    memset(&r, 0, sizeof r);
    dmac_set_out(d, DMAC_GIF, rec_out, &r);
    for (uint32_t i = 0; i < 4; i++) dq(0x1000 + i * 16, 0x100 + i);
    c = dmac_chan(d, DMAC_GIF);
    c->madr = 0x1000; c->qwc = 4;
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    CHECK(!dmac_busy(d, DMAC_GIF) && r.n == 4 && r.items[3] == 0x103);
    CHECKX(c->madr, 0x1040);
    CHECKX(c->qwc, 0);

    /* toSPR normal, then fromSPR normal back to another place */
    c = dmac_chan(d, DMAC_TO_SPR);
    c->madr = 0x1000; c->sadr = 0x100; c->qwc = 4;
    dmac_write_chcr(d, DMAC_TO_SPR, 0x100);
    CHECK(!dmac_busy(d, DMAC_TO_SPR));
    CHECK(memcmp(d->spr + 0x100, ram(0x1000), 64) == 0);
    CHECKX(c->sadr, 0x140);
    c = dmac_chan(d, DMAC_FROM_SPR);
    c->madr = 0x2000; c->sadr = 0x100; c->qwc = 4;
    dmac_write_chcr(d, DMAC_FROM_SPR, 0x100);
    CHECK(memcmp(ram(0x2000), ram(0x1000), 64) == 0);

    /* interleave toSPR: TQWC 2, SQWC 1 -> memory qwords 0,1,3,4,6 */
    for (uint32_t i = 0; i < 8; i++) dq(0x3000 + i * 16, 0x200 + i);
    dmac_hw_write32(d, DMAC_D_SQWC, (2u << 16) | 1u);
    c = dmac_chan(d, DMAC_TO_SPR);
    c->madr = 0x3000; c->sadr = 0x400; c->qwc = 5;
    dmac_write_chcr(d, DMAC_TO_SPR, 0x108);
    {
        static const uint32_t want[5] = {0x200, 0x201, 0x203, 0x204, 0x206};
        for (int i = 0; i < 5; i++) {
            uint32_t w;
            memcpy(&w, d->spr + 0x400 + i * 16, 4);
            CHECKX(w, want[i]);
        }
    }

    /* fromSPR destination chain: tags in the scratchpad; STS = fromSPR updates D_STADR */
    dmac_hw_write32(d, DMAC_D_CTRL, 1u | (2u << 4));
    {
        uint32_t t0[4] = {1u | (DMAC_DTAG_CNT << 28), 0x5000, 0, 0};
        uint32_t t1[4] = {2u | (DMAC_DTAG_END << 28), 0x6000, 0, 0};
        memcpy(d->spr + 0x800, t0, 16); memset(d->spr + 0x810, 0x71, 16);
        memcpy(d->spr + 0x820, t1, 16); memset(d->spr + 0x830, 0x72, 32);
    }
    c = dmac_chan(d, DMAC_FROM_SPR);
    c->sadr = 0x800; c->qwc = 0;
    dmac_write_chcr(d, DMAC_FROM_SPR, 0x104);
    CHECK(!dmac_busy(d, DMAC_FROM_SPR));
    CHECK(ram(0x5000)[0] == 0x71 && ram(0x6000)[0] == 0x72 && ram(0x6010)[15] == 0x72);
    CHECKX(c->sadr, 0x850);
    CHECKX(d->stadr, 0x6020);

    /* D_CTRL.DMAE = 0 holds a kick; enabling runs it.  D_ENABLEW.CPND too. */
    memset(&r, 0, sizeof r);
    dmac_hw_write32(d, DMAC_D_CTRL, 0);
    c = dmac_chan(d, DMAC_GIF);
    c->madr = 0x1000; c->qwc = 2;
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    CHECK(dmac_busy(d, DMAC_GIF) && r.n == 0);
    dmac_hw_write32(d, DMAC_D_CTRL, 1);
    CHECK(!dmac_busy(d, DMAC_GIF) && r.n == 2);
    dmac_hw_write32(d, DMAC_D_ENABLEW, 0x1201u | 0x10000u);
    CHECKX(dmac_hw_read32(d, DMAC_D_ENABLER), 0x11201);
    c->madr = 0x1000; c->qwc = 1;
    dmac_hw_write32(d, 0x1000A000u, 0x101);       /* CHCR through the register path */
    CHECK(dmac_hw_read32(d, 0x1000A000u) & 0x100u); /* held */
    dmac_hw_write32(d, DMAC_D_ENABLEW, 0x1201u);
    CHECK(!(dmac_hw_read32(d, 0x1000A000u) & 0x100u) && r.n == 3);
    CHECK(dmac_hw_claims(0x1000A010u) && dmac_hw_claims(DMAC_D_STAT) && !dmac_hw_claims(0x1000A060u));
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ D_STAT and kernel interrupts */

static dmac_state *g_kd;
static int g_dmac_hits, g_vif1_hits;
static uint64_t g_t_kick, g_t_after;
static uint32_t g_dstat_in_handler;

static int on_dmac(int ch)
{
    if (ch == DMAC_GIF) g_dmac_hits++;
    g_dstat_in_handler = dmac_hw_read32(g_kd, DMAC_D_STAT);
    return 0;
}

static int on_vif1(int cause)
{
    if (cause == PS2K_INTC_VIF1) g_vif1_hits++;
    return 0;
}

static void kernel_main(void *arg)
{
    dmac_state *d = g_kd;
    dmac_chan_regs *c = dmac_chan(d, DMAC_GIF);
    rec *r = (rec *)arg;
    (void)r;
    ps2k_add_dmac_handler(DMAC_GIF, on_dmac, -1);
    ps2k_enable_dmac(DMAC_GIF, 0);
    /* 100 qwords, normal mode: delivered inside the kick, at kick time + 100 cycles */
    c->madr = 0x10000; c->qwc = 100;
    g_t_kick = ps2k_now();
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    g_t_after = ps2k_now();
    CHECK(g_dmac_hits == 1);
    CHECK(!(g_dstat_in_handler & (1u << DMAC_GIF)));  /* the kernel clears CIS before the handler */
    /* masked channel: CIS stays latched and is visible in D_STAT */
    ps2k_disable_dmac(DMAC_GIF, 0);
    c->madr = 0x10000; c->qwc = 1;
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    CHECK(g_dmac_hits == 1);
    CHECK(dmac_hw_read32(d, DMAC_D_STAT) & (1u << DMAC_GIF));
    CHECK(!(dmac_hw_read32(d, DMAC_D_STAT) & (1u << (16 + DMAC_GIF))));
    dmac_hw_write32(d, DMAC_D_STAT, 1u << DMAC_GIF);  /* write 1 to clear */
    CHECK(!(dmac_hw_read32(d, DMAC_D_STAT) & (1u << DMAC_GIF)));
    dmac_hw_write32(d, DMAC_D_STAT, 1u << (16 + DMAC_GIF)); /* toggle the mask on */
    CHECK(dmac_hw_read32(d, DMAC_D_STAT) & (1u << (16 + DMAC_GIF)));
    /* VIF1 i bit -> INTC VIF1 */
    ps2k_add_intc_handler(PS2K_INTC_VIF1, on_vif1, -1);
    ps2k_enable_intc(PS2K_INTC_VIF1, 0);
    c = dmac_chan(d, DMAC_VIF1);
    c->madr = 0x20000; c->qwc = 1;
    dmac_write_chcr(d, DMAC_VIF1, 0x101);
    /* the i-bit interrupt is posted after the kick (one cycle later): the
     * kicker runs on first, the handler runs once virtual time advances */
    CHECK(g_vif1_hits == 0);
    ps2k_charge(2);
    CHECK(g_vif1_hits == 1);
}

static void t_dstat_interrupts(void)
{
    ps2k_config cfg;
    dmac_state *d = new_guest_dmac();
    static vu_state vu1;
    static vif_state vif1;
    rec r;
    /* without the kernel: CIS / CIM live in the DMAC */
    memset(&r, 0, sizeof r);
    dmac_set_out(d, DMAC_GIF, rec_out, &r);
    dmac_chan(d, DMAC_GIF)->madr = 0x1000;
    dmac_chan(d, DMAC_GIF)->qwc = 1;
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    CHECKX(dmac_hw_read32(d, DMAC_D_STAT), 1u << DMAC_GIF);
    dmac_hw_write32(d, DMAC_D_STAT, (1u << DMAC_GIF) | (1u << (16 + DMAC_VIF0)) | (1u << 29));
    CHECKX(dmac_hw_read32(d, DMAC_D_STAT), (1u << 16) | (1u << 29));
    dmac_destroy(d);

    /* with the kernel */
    d = new_guest_dmac();
    d->kernel = 1;
    g_kd = d;
    memset(&r, 0, sizeof r);
    dmac_set_out(d, DMAC_GIF, rec_out, &r);
    vu_init(&vu1, 1);
    vif_init(&vif1, 1, &vu1);
    dmac_attach_vif(d, 1, &vif1);
    put32(0x20000, 0x80000000u); /* VIF NOP with the i bit */
    put32(0x20004, 0); put32(0x20008, 0); put32(0x2000C, 0);
    ps2k_default_config(&cfg);
    cfg.vblank_enable = 0;
    ps2k_init(&cfg);
    g_dmac_hits = g_vif1_hits = 0;
    CHECK(ps2k_run(kernel_main, &r, 10) == PS2K_RUN_MAIN_EXIT);
    CHECKX(g_t_after - g_t_kick, 100);   /* cycles_per_qword = 1 */
    CHECK(r.n == 101);
    vif_free(&vif1);
    ps2k_shutdown();
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ MSKPATH3 */

static void t_mskpath3(void)
{
    dmac_state *d = new_guest_dmac();
    static vu_state vu1;
    static vif_state vif1;
    rec r;
    static const uint32_t unmask[4] = {0x06000000u, 0, 0, 0};
    memset(&r, 0, sizeof r);
    vu_init(&vu1, 1);
    vif_init(&vif1, 1, &vu1);
    dmac_attach_vif(d, 1, &vif1);
    dmac_set_out(d, DMAC_GIF, rec_out, &r);
    /* VIF1: MSKPATH3(1) via a CNT tag's upper half (TTE) */
    tag(0x1000, 0, DMAC_TAG_END, 0, 0, 0x06008000u, 0);
    CHECK(kick_chain(d, DMAC_VIF1, 0x1000, DMAC_CHCR_TTE));
    CHECK(vif1.mskpath3 == 1);
    dq(0x2000, 0x77);
    dmac_chan(d, DMAC_GIF)->madr = 0x2000;
    dmac_chan(d, DMAC_GIF)->qwc = 1;
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    CHECK(dmac_busy(d, DMAC_GIF) && r.n == 0);       /* PATH3 held */
    dmac_vif_fifo_write(d, 1, unmask, 1);             /* MSKPATH3(0) through the VIF1 FIFO */
    CHECK(!dmac_busy(d, DMAC_GIF) && r.n == 1 && r.items[0] == 0x77);
    /* a VIF1 reset also releases it */
    tag(0x1000, 0, DMAC_TAG_END, 0, 0, 0x06008000u, 0);
    kick_chain(d, DMAC_VIF1, 0x1000, DMAC_CHCR_TTE);
    dmac_chan(d, DMAC_GIF)->madr = 0x2000;
    dmac_chan(d, DMAC_GIF)->qwc = 1;
    dmac_write_chcr(d, DMAC_GIF, 0x101);
    CHECK(dmac_busy(d, DMAC_GIF));
    dmac_vif_reset(d, 1);
    CHECK(!dmac_busy(d, DMAC_GIF) && r.n == 2);
    vif_free(&vif1);
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ SIF / IPU hooks */

typedef struct src_q {
    uint8_t buf[1024];
    uint32_t len, off;
    int starts;
} src_q;

static uint32_t q_in(void *user, int ch, uint8_t *dst, uint32_t bytes)
{
    src_q *q = (src_q *)user;
    uint32_t n = q->len - q->off;
    (void)ch;
    if (n > bytes) n = bytes;
    n &= ~15u; /* whole qwords only (dmac_in_fn contract) */
    memcpy(dst, q->buf + q->off, n);
    q->off += n;
    return n;
}

static void q_start(void *user, int ch) { (void)ch; ((src_q *)user)->starts++; }

static dmac_state *g_reent_d;
static void reent_out(void *user, int ch, const uint8_t *p, uint32_t bytes, uint32_t flags)
{
    rec_out(user, ch, p, bytes, flags);
    dmac_service(g_reent_d); /* a peripheral that pokes the DMAC from its sink */
}

static void t_sif_ipu_hooks(void)
{
    dmac_state *d = new_guest_dmac();
    rec r1, r4;
    src_q q0, q3;
    dmac_chan_regs *c;
    memset(&r1, 0, sizeof r1);
    memset(&r4, 0, sizeof r4);
    memset(&q0, 0, sizeof q0);
    memset(&q3, 0, sizeof q3);
    /* SIF1 source chain with TTE: the IOP side sees the tag upper halves */
    dmac_set_out(d, DMAC_SIF1, rec_out, &r1);
    tag(0x1000, 1, DMAC_TAG_CNT, 0, 0, 0xC1, 0); dq(0x1010, 0x81);
    tag(0x1020, 1, DMAC_TAG_END, 0, 0, 0xC2, 0); dq(0x1030, 0x82);
    CHECK(kick_chain(d, DMAC_SIF1, 0x1000, DMAC_CHCR_TTE));
    CHECK(r1.n == 4 && r1.items[0] == 0xEE0000C1u && r1.items[1] == 0x81 && r1.tags == 2);
    /* the same chain through a sink that re-enters the DMAC: no duplicates */
    memset(&r1, 0, sizeof r1);
    g_reent_d = d;
    dmac_set_out(d, DMAC_SIF1, reent_out, &r1);
    CHECK(kick_chain(d, DMAC_SIF1, 0x1000, DMAC_CHCR_TTE));
    CHECK(r1.n == 4 && r1.items[3] == 0x82);
    /* GIF ignores TTE (the game sets it on GIF; see DMAC.md) */
    dmac_set_out(d, DMAC_GIF, rec_out, &r4);
    CHECK(kick_chain(d, DMAC_GIF, 0x1000, DMAC_CHCR_TTE));
    CHECK(r4.n == 2 && r4.tags == 0 && d->stats[DMAC_GIF].tte_ignored == 2);

    /* SIF0 destination chain from a source that starts empty */
    dmac_set_in(d, DMAC_SIF0, q_in, &q0);
    dmac_set_start(d, DMAC_SIF0, q_start, &q0);
    c = dmac_chan(d, DMAC_SIF0);
    c->qwc = 0;
    dmac_write_chcr(d, DMAC_SIF0, 0x104);
    CHECK(q0.starts == 1 && dmac_busy(d, DMAC_SIF0));
    {
        uint32_t t0[4] = {1u | (DMAC_DTAG_CNT << 28), 0x8000, 0, 0};
        uint32_t t1[4] = {1u | (DMAC_DTAG_END << 28) | 0x80000000u, 0x9000, 0, 0};
        memcpy(q0.buf, t0, 16); memset(q0.buf + 16, 0x91, 16);
        memcpy(q0.buf + 32, t1, 16); memset(q0.buf + 48, 0x92, 8); /* half a qword so far */
        q0.len = 56;
    }
    dmac_service(d);
    CHECK(dmac_busy(d, DMAC_SIF0) && ram(0x8000)[0] == 0x91);
    memset(q0.buf + 56, 0x92, 8);
    q0.len = 64;
    dmac_service(d);
    CHECK(!dmac_busy(d, DMAC_SIF0) && ram(0x9000)[15] == 0x92);
    CHECKX(c->chcr >> 16, 0xF000 | 0x0000);  /* TAG: IRQ + END */

    /* IPU: toIPU out, fromIPU in */
    memset(&r4, 0, sizeof r4);
    dmac_set_out(d, DMAC_TO_IPU, rec_out, &r4);
    c = dmac_chan(d, DMAC_TO_IPU);
    c->madr = 0x1010; c->qwc = 1;
    dmac_write_chcr(d, DMAC_TO_IPU, 0x101);
    CHECK(r4.n == 1 && r4.items[0] == 0x81);
    dmac_set_in(d, DMAC_FROM_IPU, q_in, &q3);
    memset(q3.buf, 0xA5, 32);
    q3.len = 32;
    c = dmac_chan(d, DMAC_FROM_IPU);
    c->madr = 0xA000; c->qwc = 2;
    dmac_write_chcr(d, DMAC_FROM_IPU, 0x100);
    CHECK(!dmac_busy(d, DMAC_FROM_IPU) && ram(0xA01F)[0] == 0xA5);
    /* an unbound peripheral drops data loudly instead of hanging */
    c = dmac_chan(d, DMAC_SIF2);
    c->madr = 0x1010; c->qwc = 1;
    dmac_write_chcr(d, DMAC_SIF2, 0x101);
    CHECK(!dmac_busy(d, DMAC_SIF2) && d->stats[DMAC_SIF2].unbound_qwords == 1);
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ retail VU1 microprogram */

static rg_elf g_elf;

static uint32_t g_seed;
static uint32_t rnd(void) { g_seed = g_seed * 1664525u + 1013904223u; return g_seed >> 8; }
static uint32_t fbits(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }

typedef struct kick_rec { unsigned kicks, prims; } kick_rec;
static kick_rec g_kicks;
static void count_kick(void *user, const uint8_t *data, uint32_t bytes, uint32_t addr)
{
    uint32_t hi;
    memcpy(&hi, data + 4, 4);
    g_kicks.kicks++;
    if ((hi >> 14) & 1) g_kicks.prims++;
    gs_vu1_gif_sink(user, data, bytes, addr);
}

/* VU1 data memory image for one batch, in the layout the head programs read
 * (worked out for tests/vu/vu_smoke.c from the retail disassembly). */
static void synth_vu_mem(uint32_t *m, uint32_t seed, uint32_t n)
{
    g_seed = seed;
    for (unsigned k = 0; k < 0x4000 / 4; k++) {
        uint32_t r = rnd();
        if (r & 1) m[k] = (r >> 1) & 3;
        else m[k] = fbits((float)((int)(r >> 1) % 4000) / 1000.0f) & 0xFFFF0000u;
    }
    m[0] = 2; m[1] = 0x10000000u; m[2] = 0xE; m[3] = 0;
    m[76 * 4] = 0x60;
    m[86 * 4 + 1] = 0x30000000u; m[86 * 4 + 2] = 0x412; m[86 * 4 + 3] = 0;
    {
        static const uint32_t tops[2] = {0x100, 0x280};
        for (unsigned k = 0; k < 2; k++) {
            uint32_t *h = m + tops[k] * 4;
            h[0] = 0x123; h[1] = n; h[2] = n | 0x8000; h[3] = n;
            h[4] = 2 * n; h[5] = 3 * n;
        }
    }
}

static void t_vif1_vu1_retail(void)
{
    static vu_state vu1;
    static vif_state vif1;
    dmac_state *d;
    gs_state *gs;
    const uint32_t head = 0x441660;           /* variant a[0][1]: a single head piece at VU 0x320 */
    uint32_t at, list = 0x01800000, data = 0x01900000;
    if (rg_elf_load(&g_elf, rg_retail_elf_path())) {
        printf("SKIP: retail ELF not found at %s (set RG_ELF)\n", rg_retail_elf_path());
        g_skip = 1;
        return;
    }
    d = new_guest_dmac();
    /* the ELF's loadable bytes at their EE addresses */
    for (int i = 0; i < g_elf.nph; i++) {
        uint32_t va = g_elf.ph[i].vaddr, n = g_elf.ph[i].filesz;
        const uint8_t *p = n ? rg_elf_ptr(&g_elf, va, n) : NULL;
        if (p && va + n <= RAM_SIZE) memcpy(ram(va), p, n);
    }
    gs = gs_create();
    vu_init(&vu1, 1);
    vif_init(&vif1, 1, &vu1);
    vif1.vu_cycle_budget = 300000;
    vu1.gif_sink = count_kick;
    vu1.gif_user = gs;
    vif1.gif_sink = gs_vif1_gif_sink;
    vif1.gif_user = gs;
    dmac_attach_vif(d, 1, &vif1);
    dmac_attach_gs(d, gs);
    /* draw context: 1024x1024 CT32 at 0, everything passes */
    gs_write_reg(gs, GS_FRAME_1, (16ull << 16));
    gs_write_reg(gs, GS_SCISSOR_1, (1023ull << 16) | (1023ull << 48));
    gs_write_reg(gs, GS_TEST_1, 0x30000);
    gs_write_reg(gs, GS_XYOFFSET_1, 0);

    /* batch data for UNPACK V4-32 (4 x 256 qwords) */
    synth_vu_mem((uint32_t *)(void *)ram(data), 1234u, 4);
    /* the chain: CALL the retail RET-tagged MPG packet (TTE: its VIF codes),
     * then CNT with BASE/OFFSET + 4 UNPACKs (REF data) + MSCAL/MSCNT, END */
    at = list;
    {
        /* the second-level pieces the head may jump into (as vu_smoke uploads
         * them), then the head itself: five CALLs into RET-tagged packets */
        static const uint32_t pieces[] = {0x438C70, 0x43B4F0, 0x43D110, 0x441840};
        for (unsigned k = 0; k < 4; k++) { tag(at, 0, DMAC_TAG_CALL, 0, pieces[k], 0, 0); at += 16; }
    }
    tag(at, 0, DMAC_TAG_CALL, 0, head, 0, 0); at += 16;
    tag(at, 0, DMAC_TAG_CNT, 0, 0, 0x03000100u, 0x02000180u); at += 16; /* BASE 0x100, OFFSET 0x180 */
    for (uint32_t k = 0; k < 4; k++) {
        /* UNPACK V4-32 (0x6C), NUM 0 (=256), ADDR k*256 */
        tag(at, 256, DMAC_TAG_REF, 0, data + k * 4096, 0, 0x6C000000u | (k * 256)); at += 16;
    }
    tag(at, 0, DMAC_TAG_CNT, 0, 0, 0x14000064u, 0x17000000u); at += 16; /* MSCAL 0x320, MSCNT */
    tag(at, 0, DMAC_TAG_END, 0, 0, 0x17000000u, 0);                   /* MSCNT */
    memset(&g_kicks, 0, sizeof g_kicks);
    CHECK(kick_chain(d, DMAC_VIF1, list, DMAC_CHCR_TTE));
    CHECK(vif1.stats.invalid_cmds == 0);
    CHECK(vif1.stats.mpg_bytes > 0);
    CHECK(vif1.stats.mscal >= 3);
    CHECK(vif1.stats.vu_runaways == 0);
    /* the retail code landed where the packet says: VU1 code at 0x320 */
    {
        size_t nw;
        const uint32_t *w = rg_vif_packet(&g_elf, head, &nw);
        int found = 0;
        for (size_t i = 0; w && i + 1 < nw; i++)
            if ((w[i] >> 24) == 0x4A) { /* MPG: code follows */
                uint32_t imm = w[i] & 0xFFFF, num = (w[i] >> 16) & 0xFF;
                if (!num) num = 256;
                CHECK(memcmp(vu1.code + imm * 8, &w[i + 1], num * 8) == 0);
                found = 1;
                break;
            }
        CHECK(found);
    }
    printf("  VU1: %u XGKICKs (%u with PRIM), GS: %llu prims, %llu pixels written\n", g_kicks.kicks,
           g_kicks.prims, (unsigned long long)(gs->stats.prims[3] + gs->stats.prims[4] + gs->stats.prims[5] +
                                               gs->stats.prims[6] + gs->stats.prims[0] + gs->stats.prims[1] +
                                               gs->stats.prims[2]),
           (unsigned long long)gs->stats.pixels_written);
    CHECK(g_kicks.kicks > 0);
    CHECK(gs->path[1].packets == g_kicks.kicks);   /* XGKICK output reached the GS on PATH1 */
    CHECK(gs->stats.prims[0] + gs->stats.prims[1] + gs->stats.prims[2] + gs->stats.prims[3] +
          gs->stats.prims[4] + gs->stats.prims[5] + gs->stats.prims[6] > 0);
    CHECK(gs->stats.pixels_written > 0);
    {
        /* and the pixels are in VRAM (it starts zeroed) */
        uint32_t lit = 0;
        for (uint32_t y = 0; y < 1024; y++)
            for (uint32_t x = 0; x < 1024; x++)
                if (gs_read_pixel(gs, GS_PSMCT32, 0, 16, x, y)) lit++;
        printf("  %u non-zero pixels in the 1024x1024 frame\n", lit);
        CHECK(lit > 0);
    }
    CHECK(gs_path_idle(gs, 1));
    vif_free(&vif1);
    gs_destroy(gs);
    dmac_destroy(d);
    rg_elf_free(&g_elf);
}

/* ------------------------------------------------------------------ libgraph / libpkt (host mode) */

static dmac_state *new_host_gfx(gs_state **gsp, vu_state *vu1, vif_state *vif1)
{
    dmac_state *d = dmac_create();
    gs_state *gs = gs_create();
    d->kernel = 0;
    vu_init(vu1, 1);
    vif_init(vif1, 1, vu1);
    vu1->gif_sink = gs_vu1_gif_sink;
    vu1->gif_user = gs;
    vif1->gif_sink = gs_vif1_gif_sink;
    vif1->gif_user = gs;
    dmac_attach_vif(d, 1, vif1);
    dmac_attach_gs(d, gs);
    sce_graphics_bind(d, gs);
    *gsp = gs;
    return d;
}

static uint8_t g_pkbuf[64 * 1024] __attribute__((aligned(16)));
static uint8_t g_img[64 * 64 * 4] __attribute__((aligned(16)));
static uint8_t g_back[64 * 64 * 4 + 64] __attribute__((aligned(16)));

/* upload w x h of psm at (x,y) of buffer bp/bw through libpkt + GIF chain
 * DMA, the way FixedTexUploadImpl does (TTE set on the GIF channel) */
static void upload(int psm, int bp, int bw, int x, int y, int w, int h, const void *img, uint32_t bytes)
{
    sceGifPacket pk;
    sceDmaChan *ch = sceDmaGetChan(2);
    sceGifPkInit(&pk, g_pkbuf);
    sceGifPkReset(&pk);
    sceGifPkRefLoadImage(&pk, (uint16_t)bp, (uint8_t)psm, (uint16_t)bw, img, (bytes + 15) / 16, (uint32_t)x,
                         (uint32_t)y, (uint32_t)w, (uint32_t)h);
    sceGifPkCnt(&pk, 0, 0, 0);
    sceGifPkOpenGifTag(&pk, RG_U128(0xE, (1ull << 60) | 0x8000));
    sceGifPkAddGsAD(&pk, GS_TEXFLUSH, 0);
    sceGifPkCloseGifTag(&pk);
    sceGifPkEnd(&pk, 0, 0, 0);
    sceGifPkTerminate(&pk);
    ch->chcr |= DMAC_CHCR_TTE;
    sceDmaSend(ch, g_pkbuf);
    CHECK(sceDmaSync(ch, 0, 0) == 0);
    CHECK(sceGsSyncPath(0, 0) == 0);
}

static void t_path3_storeimage(void)
{
    static vu_state vu1;
    static vif_state vif1;
    static sceGsStoreImage si;
    gs_state *gs;
    dmac_state *d = new_host_gfx(&gs, &vu1, &vif1);
    static const struct { int psm, w, h, bpp; } cases[] = {
        {GS_PSMCT32, 64, 32, 32}, /* 512 qwords: all through VIF1 DMA */
        {GS_PSMCT32, 6, 5, 32},   /* 7 qwords + 8 bytes: FIFO reads + padded height */
        {GS_PSMCT24, 5, 3, 24},   /* 45 bytes */
        {GS_PSMCT16, 10, 3, 16},  /* 60 bytes */
        {GS_PSMT8, 24, 9, 8},     /* 216 bytes */
    };
    for (unsigned k = 0; k < sizeof cases / sizeof cases[0]; k++) {
        int psm = cases[k].psm, w = cases[k].w, h = cases[k].h;
        uint32_t bytes = (uint32_t)(w * h * cases[k].bpp / 8);
        int x = 3 + (int)k, y = 2;
        uint64_t imr = gs_read_priv(gs, GS_P_IMR);
        for (uint32_t i = 0; i < sizeof g_img; i++) g_img[i] = (uint8_t)(i * 7 + k * 13 + (i >> 8));
        upload(psm, 0x40, 2, x, y, w, h, g_img, bytes);
        /* placement checked independently of the readback */
        CHECKX(gs_read_pixel(gs, psm, 0x40, 2, (uint32_t)x, (uint32_t)y),
               psm == GS_PSMCT32 ? (uint32_t)g_img[0] | g_img[1] << 8 | g_img[2] << 16 | (uint32_t)g_img[3] << 24
               : psm == GS_PSMCT24 ? (uint32_t)g_img[0] | g_img[1] << 8 | g_img[2] << 16
               : psm == GS_PSMCT16 ? (uint32_t)g_img[0] | g_img[1] << 8 : g_img[0]);
        memset(g_back, 0xCC, sizeof g_back);
        CHECK(sceGsSetDefStoreImage(&si, 0x40, 2, (short)psm, (short)x, (short)y, (short)w, (short)h) == 7);
        CHECK(sceGsExecStoreImage(&si, g_back) == 0);
        if (memcmp(g_back, g_img, bytes) != 0) {
            printf("  store/load mismatch: psm 0x%02X %dx%d\n", psm, w, h);
            g_fail++;
        }
        CHECK(g_back[bytes] == 0xCC);                 /* no write past the image */
        CHECK(vif1.mskpath3 == 0);                     /* MSKPATH3 released */
        CHECK(gs_read_priv(gs, GS_P_BUSDIR) == 0);
        CHECK(gs_read_priv(gs, GS_P_IMR) == imr);
        CHECK(gs_fifo_pending(gs) == 0);               /* padding qwords consumed */
        CHECK(!dmac_busy(d, DMAC_VIF1) && !dmac_busy(d, DMAC_GIF));
    }
    /* the SDK LoadImage pair goes through PATH3 too */
    {
        static sceGsLoadImage li;
        for (uint32_t i = 0; i < 16 * 4 * 4; i++) g_img[i] = (uint8_t)(0x5A ^ i);
        CHECK(sceGsSetDefLoadImage(&li, 0x80, 1, GS_PSMCT32, 0, 0, 16, 4) == 6);
        CHECK(sceGsExecLoadImage(&li, g_img) == 0);
        CHECKX(gs_read_pixel(gs, GS_PSMCT32, 0x80, 1, 15, 3),
               (uint32_t)g_img[252] | g_img[253] << 8 | g_img[254] << 16 | (uint32_t)g_img[255] << 24);
    }
    vif_free(&vif1);
    sce_graphics_bind(NULL, NULL);
    gs_destroy(gs);
    dmac_destroy(d);
}

static void t_libgraph_env(void)
{
    static vu_state vu1;
    static vif_state vif1;
    static sceGsDBuff db;
    static sceDmaEnv env;
    gs_state *gs;
    dmac_state *d = new_host_gfx(&gs, &vu1, &vif1);
    /* libdma env / reset: D_CTRL fields from the retail tables */
    CHECK(sceDmaReset(1) == 1);
    sceDmaGetEnv(&env);
    env.notify = 0x100;
    env.sts = 8; env.std = 2; env.mfd = 0; env.rcycle = 3;
    CHECK(sceDmaPutEnv(&env) == 0);
    CHECKX(dmac_hw_read32(d, DMAC_D_CTRL), 1u | (2u << 4) | (2u << 6) | 2u | (2u << 8));
    CHECKX(dmac_hw_read32(d, DMAC_D_PCR), 0x100);
    env.rcycle = 7;
    CHECK(sceDmaPutEnv(&env) == -4);
    CHECK(sceDmaReset(0) == 1);
    /* DMAE kept, STS/STD/MFD/RELE cleared; RCYC is only written when rcycle != 0 (retail) */
    CHECKX(dmac_hw_read32(d, DMAC_D_CTRL), 1u | (2u << 8));
    CHECK(sceDmaGetChan(10) == NULL && sceDmaGetChan(2) == dmac_chan(d, 2));

    /* the game's GfxSetVideoMode setup: ResetGraph(0, 1, 2, 1), 640x448 CT32, Z24 */
    sceGsResetGraph(0, 1, 2, 1);
    CHECKX(gs_read_priv(gs, GS_P_SMODE2), 3);
    CHECKX(gs_read_priv(gs, GS_P_IMR), 0x7F00);
    CHECK(sceGszbufaddr(0, 640, 448) == 280);
    sceGsSetDefDBuff(&db, GS_PSMCT32, 640, 448, 3, GS_PSMZ24, 1);
    CHECKX(db.disp[0].pmode, 0x66);
    CHECKX(db.disp[0].smode2, 3);
    CHECKX(db.disp[0].dispfb, 10u << 9);
    CHECKX(db.disp[0].display, 636ull | (50ull << 12) | (3ull << 23) | (2559ull << 32) | (895ull << 44));
    CHECKX(db.draw0.frame1, 10ull << 16);
    CHECKX(db.draw0.zbuf1, 280ull | (1ull << 24));
    CHECKX(db.draw0.xyoffset1, (1728ull << 4) | (1824ull << 36));
    CHECKX(db.draw0.scissor1, (639ull << 16) | (447ull << 48));
    CHECKX(db.draw0.test1, 0x70000);
    CHECKX(db.draw0.test1addr, GS_TEST_1);
    CHECKX(db.giftag0.lo, 14ull | 0x8000 | (1ull << 60));
    CHECKX(db.giftag0.hi, 0xE);
    CHECKX(db.clear0.xyz2a, (1728ull << 4) | (1824ull << 20));
    CHECKX(db.clear0.xyz2b, (2368ull << 4) | (2272ull << 20));
    CHECKX(db.clear0.rgbaq, 0x3F80000000000000ull);
    /* swap: display regs, then the draw env + clear through PATH3 */
    CHECK(sceGsSwapDBuff(&db, 1) == 0);
    CHECKX(gs_read_priv(gs, GS_P_DISPLAY2), db.disp[1].display);
    CHECKX(gs_read_priv(gs, GS_P_PMODE), 0x66);
    CHECKX(gs->reg[GS_FRAME_1], db.draw1.frame1);
    CHECKX(gs->reg[GS_ZBUF_1], db.draw1.zbuf1);
    CHECKX(gs->reg[GS_TEST_1], db.clear1.testb);
    CHECK(gs->stats.prims[GS_PRIM_SPRITE] == 1);
    CHECK(gs->stats.pixels_written == 640u * 448u);
    CHECK(sceGsSyncPath(0, 0) == 0 && sceGsSyncPath(1, 0) == 0);
    /* field mode: half-height buffers share the z allocation */
    sceGsResetGraph(0, 1, 2, 0);
    CHECK(sceGszbufaddr(0, 640, 224) == 70);
    sceGsSetDefDBuff(&db, GS_PSMCT32, 640, 224, 3, GS_PSMZ24, 0);
    CHECKX(db.draw0.frame1 & 0x1FF, 35);
    CHECKX(db.disp[1].dispfb & 0x1FF, 35);
    CHECKX(db.disp[0].smode2, 1);
    CHECKX(db.giftag0.lo & 0x7FFF, 8);
    vif_free(&vif1);
    sce_graphics_bind(NULL, NULL);
    gs_destroy(gs);
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ sceGsSyncV + kernel */

static volatile uint32_t g_low_count;
static int g_syncv_ok;
static uint64_t g_wake_lag_max;

static void low_thread(void *arg)
{
    (void)arg;
    for (;;) {
        g_low_count++;
        ps2k_charge(1000);
    }
}

static void syncv_main(void *arg)
{
    struct SemaProbe { int before, after; } *sp = (struct SemaProbe *)arg;
    int low = ps2k_create_thread(low_thread, NULL, 0x1000, NULL, 50, 0, 0);
    int ok = 1;
    sp->before = ps2k_create_sema(0, 1, 0, 0);
    ps2k_delete_sema(sp->before, 0);
    ps2k_start_thread(low, NULL);
    sceGsResetGraph(0, 1, 2, 1);
    for (int i = 0; i < 6; i++) {
        uint64_t c = ps2k_vblank_count();
        uint32_t lc = g_low_count;
        uint64_t vbs = (c * PS2K_FIELD_SUB + 240ull * PS2K_HSYNC_SUB) / PS2K_SUB;
        int r = sceGsSyncV(0);
        if (ps2k_vblank_count() != c + 1) ok = 0;
        if (ps2k_now() < vbs) ok = 0;
        if (ps2k_now() - vbs > g_wake_lag_max) g_wake_lag_max = ps2k_now() - vbs;
        if (g_low_count == lc) ok = 0;  /* blocked, not spun: the low thread ran */
        if (r != 0) ok = 0;             /* CSR.FIELD: nothing toggles it here */
    }
    sceGsResetGraph(0, 0, 2, 0);
    if (sceGsSyncV(0) != 1) ok = 0;  /* not interlaced: 1 */
    sp->after = ps2k_create_sema(0, 1, 0, 0);
    g_syncv_ok = ok;
    ps2k_terminate_thread(low, 0);
}

static void t_syncv_blocking(void)
{
    ps2k_config cfg;
    static vu_state vu1;
    static vif_state vif1;
    struct { int before, after; } sp;
    gs_state *gs;
    dmac_state *d = new_host_gfx(&gs, &vu1, &vif1);
    d->kernel = 1;
    sce_graphics_debug_syncv_nowait = g_control;
    ps2k_default_config(&cfg);
    ps2k_init(&cfg);
    g_syncv_ok = 0;
    g_wake_lag_max = 0;
    CHECK(ps2k_run(syncv_main, &sp, 10) == PS2K_RUN_MAIN_EXIT);
    printf("  6 x sceGsSyncV: woke at most %llu cycles after VBLANK_START; low thread ran %u times\n",
           (unsigned long long)g_wake_lag_max, (unsigned)g_low_count);
    CHECK(g_syncv_ok);
    CHECK(g_wake_lag_max < 1000 + 1);   /* the low thread charges 1000 cycles at a time */
    CHECK(sp.before == sp.after);        /* the private semaphore is freed */
    sce_graphics_debug_syncv_nowait = 0;
    ps2k_shutdown();
    vif_free(&vif1);
    sce_graphics_bind(NULL, NULL);
    gs_destroy(gs);
    dmac_destroy(d);
}

/* ------------------------------------------------------------------ main */

typedef struct { const char *name; void (*fn)(void); } test_t;
static const test_t k_tests[] = {
    {"chain_tags", t_chain_tags},
    {"normal_spr", t_normal_spr},
    {"dstat_interrupts", t_dstat_interrupts},
    {"mskpath3", t_mskpath3},
    {"sif_ipu_hooks", t_sif_ipu_hooks},
    {"vif1_vu1_retail", t_vif1_vu1_retail},
    {"path3_storeimage", t_path3_storeimage},
    {"libgraph_env", t_libgraph_env},
    {"syncv_blocking", t_syncv_blocking},
};

int main(int argc, char **argv)
{
    int ran = 0;
    setvbuf(stdout, NULL, _IONBF, 0);
    for (size_t i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        char ctl[64];
        int before = g_fail, want, want_ctl;
        snprintf(ctl, sizeof ctl, "%s_control", k_tests[i].name);
        want = argc < 2 || strcmp(argv[1], k_tests[i].name) == 0;
        want_ctl = argc >= 2 && strcmp(argv[1], ctl) == 0;
        if (!want && !want_ctl) continue;
        g_control = want_ctl;
        g_skip = 0;
        k_tests[i].fn();
        printf("%-24s %s\n", want_ctl ? ctl : k_tests[i].name,
               g_skip ? "SKIP" : g_fail == before ? "PASS" : "FAIL");
        ran++;
        if (g_skip && argc >= 2) return 77;
    }
    if (!ran) {
        fprintf(stderr, "unknown test '%s'\n", argc > 1 ? argv[1] : "");
        return 2;
    }
    return g_fail ? 1 : 0;
}
