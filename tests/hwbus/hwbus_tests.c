/* SPDX-License-Identifier: CC0-1.0 */
/* Hardware register bus tests (docs/HWBUS.md): ctest -L hwbus.
 *
 * Every region is routed into the REAL model (kernel, DMAC, VIF, GS, SIF)
 * and checked through that model's own state / public API.  `game_e2e`
 * calls game functions rewritten by the hwaccess stage (built from game/ by
 * CMake through tools/stages/hwaccess.py --one).  `*_control` runs a
 * deliberately-wrong configuration and must FAIL. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dmac.h"
#include "gs.h"
#include "hwbus.h"
#include "ps2k.h"
#include "sif.h"
#include "vif.h"
#include "vu.h"

/* the accessor spellings the stage emits (include/port/hwaccess.h) */
#include "port/hwaccess.h"

static int g_fail;
#define CHECK(c)                                                                     \
    do {                                                                             \
        if (!(c)) {                                                                  \
            fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c);    \
            g_fail = 1;                                                              \
        }                                                                            \
    } while (0)
#define CHECKX(a, b)                                                                 \
    do {                                                                             \
        unsigned long long a_ = (unsigned long long)(a), b_ = (unsigned long long)(b); \
        if (a_ != b_) {                                                              \
            fprintf(stderr, "%s:%d: %s = 0x%llX, want 0x%llX\n", __FILE__, __LINE__,   \
                    #a, a_, b_);                                                     \
            g_fail = 1;                                                              \
        }                                                                            \
    } while (0)

/* ---------------------------------------------------------------- rig */
typedef struct rig {
    dmac_state *d;
    gs_state *gs;
    vu_state vu0, vu1;
    vif_state vif0, vif1;
} rig;

static int g_logs;
static char g_last_log[256];
static void count_log(void *u, const char *line)
{
    (void)u;
    g_logs++;
    snprintf(g_last_log, sizeof g_last_log, "%s", line);
}

static void rig_up(rig *r, int with_kernel)
{
    ps2k_config cfg;
    sif_config sc;
    memset(r, 0, sizeof *r);
    ps2k_default_config(&cfg);
    cfg.vblank_enable = 0;
    ps2k_init(&cfg);
    sif_default_config(&sc);
    sif_init(&sc);
    r->d = dmac_create();
    r->d->kernel = with_kernel;
    r->gs = gs_create();
    vu_init(&r->vu0, 0);
    vu_init(&r->vu1, 1);
    vif_init(&r->vif0, 0, &r->vu0);
    vif_init(&r->vif1, 1, &r->vu1);
    r->vif1.gif_sink = gs_vif1_gif_sink;
    r->vif1.gif_user = r->gs;
    dmac_attach_vif(r->d, 0, &r->vif0);
    dmac_attach_vif(r->d, 1, &r->vif1);
    dmac_attach_gs(r->d, r->gs);
    hwbus_init();
    hwbus_bind(r->d, NULL);
    hwbus_set_log(count_log, NULL);
    g_logs = 0;
}

static void rig_down(rig *r)
{
    vif_free(&r->vif0);
    vif_free(&r->vif1);
    gs_destroy(r->gs);
    dmac_destroy(r->d);
    ps2k_shutdown();
}

/* ---------------------------------------------------------------- tests */
static void t_claims(void)
{
    rig r;
    rig_up(&r, 1);
    CHECK(hwbus_claims(PS2K_T0_COUNT) == HWBUS_KERNEL);
    CHECK(hwbus_claims(PS2K_T3_BASE + 0x10) == HWBUS_KERNEL);
    CHECK(hwbus_claims(PS2K_INTC_MASK) == HWBUS_KERNEL);
    CHECK(hwbus_claims(DMAC_D_STAT) == HWBUS_DMAC);        /* DMAC before kernel */
    CHECK(hwbus_claims(0x1000B410u) == HWBUS_DMAC);
    CHECK(hwbus_claims(DMAC_D_ENABLEW) == HWBUS_DMAC);
    CHECK(hwbus_claims(0x10002010u) == HWBUS_IPU);
    CHECK(hwbus_claims(0x10003020u) == HWBUS_GIF);
    CHECK(hwbus_claims(0x10003C10u) == HWBUS_VIF);
    CHECK(hwbus_claims(0x10003840u) == HWBUS_VIF);
    CHECK(hwbus_claims(0x100038A0u) == HWBUS_UNKNOWN);     /* VIF0 has no BASE */
    CHECK(hwbus_claims(DMAC_GIF_FIFO) == HWBUS_FIFO);
    CHECK(hwbus_claims(0x1000F230u) == HWBUS_SIF);
    CHECK(hwbus_claims(GS_P_CSR) == HWBUS_GS);
    CHECK(hwbus_claims(GS_P_DISPLAY1 + 4) == HWBUS_GS);
    CHECK(hwbus_claims(0x1000F100u) == HWBUS_UNKNOWN);     /* SIO */
    CHECK(hwbus_claims(0x10000040u) == HWBUS_UNKNOWN);     /* hole in T0 */
    CHECK(hwbus_claims(0x11000000u) == HWBUS_UNKNOWN);     /* VU0 micro mem */
    rig_down(&r);
}

static void t_kernel(void)
{
    rig r;
    rig_up(&r, 1);
    hw_w32(PS2K_T0_MODE, 0x83);
    CHECKX(ps2k_hw_read32(PS2K_T0_MODE), 0x83);
    CHECKX(hw_r32(PS2K_T0_MODE), ps2k_hw_read32(PS2K_T0_MODE));
    hw_w32(PS2K_T1_BASE + 0x20, 0x1234);                   /* T1_COMP */
    CHECKX(ps2k_hw_read32(PS2K_T1_BASE + 0x20), 0x1234);
    /* INTC_MASK: write 1 toggles */
    {
        uint32_t m0 = ps2k_hw_read32(PS2K_INTC_MASK);
        hw_w32(PS2K_INTC_MASK, 1u << PS2K_INTC_TIMER0);
        CHECKX(ps2k_hw_read32(PS2K_INTC_MASK), m0 ^ (1u << PS2K_INTC_TIMER0));
        CHECKX(hw_r32(PS2K_INTC_MASK), m0 ^ (1u << PS2K_INTC_TIMER0));
    }
    /* sub-word access: the low halfword of T0_MODE */
    CHECKX(hw_r16(PS2K_T0_MODE), 0x83);
    CHECKX(hw_r8(PS2K_T0_MODE), 0x83);
    CHECK(r.d->stats[0].kicks == 0);
    CHECK(hwbus_get_stats()->reads[HWBUS_KERNEL] >= 3);
    rig_down(&r);
}

static void t_dmac(void)
{
    rig r;
    rig_up(&r, 1);
    hw_w32(DMAC_D_CTRL, 1);
    CHECKX(r.d->ctrl, 1);
    CHECKX(hw_r32(DMAC_D_CTRL), 1);
    /* ViBuf's toIPU channel registers */
    hw_w32(0x1000B410u, 0x00ABCDE0u);                      /* D4_MADR */
    hw_w32(0x1000B420u, 0x12345u);                         /* D4_QWC: 16 bits */
    CHECKX(r.d->ch[DMAC_TO_IPU].madr, 0x00ABCDE0u);
    CHECKX(r.d->ch[DMAC_TO_IPU].qwc, 0x2345u);
    CHECKX(hw_r32(0x1000B420u), 0x2345u);
    /* D_ENABLEW / D_ENABLER (the ViBufSetD*Chcr sequence) */
    hw_w32(DMAC_D_ENABLEW, hw_r32(DMAC_D_ENABLER) | 0x10000u);
    CHECKX(r.d->enable & 0x10000u, 0x10000u);
    hw_w32(DMAC_D_ENABLEW, hw_r32(DMAC_D_ENABLER) & 0xFFFEFFFFu);
    CHECKX(r.d->enable & 0x10000u, 0);
    /* D_STAT: CIS/CIM in the kernel, SIS/MEIS/BEIS + SIM/MEIM in the DMAC */
    ps2k_raise_dmac(PS2K_DMAC_GIF);
    r.d->stat_local |= 1u << 15;                           /* BEIS latched */
    CHECKX(hw_r32(DMAC_D_STAT) & 0x8004u, 0x8004u);
    hw_w32(DMAC_D_STAT, (1u << 15) | (1u << PS2K_DMAC_GIF) | (1u << 29));
    CHECKX(hw_r32(DMAC_D_STAT) & 0x8004u, 0);              /* both w1c'd */
    CHECKX(ps2k_hw_read32(PS2K_D_STAT) & 4u, 0);           /* reached the kernel */
    CHECKX(hw_r32(DMAC_D_STAT) & (1u << 29), 1u << 29);    /* SIM toggled in the DMAC */
    /* MovieOpen's D_CTRL |= 3 through the read-modify-write spelling */
    HW_W32(0x1000E000u, (int)HW_R32(0x1000E000u) | (3));
    CHECKX(r.d->ctrl & 3u, 3u);
    rig_down(&r);
}

static void t_fifo_vif_gif(void)
{
    rig r;
    uint32_t q[4];
    uint64_t tag[2], ad[2];
    rig_up(&r, 0);
    /* VIF1 FIFO: MARK 0x1234 -> VIF1_MARK */
    q[0] = 0x07001234u; q[1] = q[2] = q[3] = 0;
    hw_w128(DMAC_VIF1_FIFO, q);
    CHECKX(r.vif1.mark, 0x1234u);
    CHECKX(hw_r32(0x10003C30u), 0x1234u);
    /* VIF0 FIFO: STCYCL CL=4 WL=2 -> VIF0_CYCLE */
    q[0] = 0x01000204u;
    hw_w128(DMAC_VIF0_FIFO, q);
    CHECKX(hw_r32(0x10003840u), 0x0204u);
    /* VIF1_FBRST.RST -> dmac_vif_reset: clears MSKPATH3 (GIF_STAT.M3P) */
    r.vif1.mskpath3 = 1;
    CHECKX(hw_r32(0x10003020u) & 2u, 2u);
    hw_w32(0x10003C10u, 1);
    CHECKX(r.vif1.mskpath3, 0);
    CHECKX(hw_r32(0x10003020u) & 2u, 0);
    /* FBRST.STC clears STAT.INT (Vif1IntcHandler's write) */
    r.vif1.irq = 1;
    CHECKX(hw_r32(0x10003C00u) & (1u << 11), 1u << 11);
    hw_w32(0x10003C10u, 8);
    CHECKX(r.vif1.irq, 0);
    /* a read-only VIF register write is ignored, not unknown */
    hw_w32(0x10003C40u, 0x0101u);
    CHECK(hwbus_get_stats()->ignored_writes == 1);
    /* GIF FIFO: one A+D packet sets FOGCOL in the GS model */
    tag[0] = 1u | (1u << 15) | (1ull << 60); tag[1] = 0xE;
    hw_w128(DMAC_GIF_FIFO, tag);
    ad[0] = 0x00ABCDEFull; ad[1] = GS_FOGCOL;
    hw_w128(DMAC_GIF_FIFO, ad);
    CHECKX(r.gs->reg[GS_FOGCOL], 0x00ABCDEFull);
    CHECK(gs_path_idle(r.gs, GS_PATH3));
    CHECK(hwbus_unknown_count() == 0);
    rig_down(&r);
}

static void t_gs_priv(void)
{
    rig r;
    rig_up(&r, 0);
    hw_w64(GS_P_PMODE, 0x7F23);
    CHECKX(gs_read_priv(r.gs, GS_P_PMODE), 0x7F23);
    CHECKX(HW_R64(0x12000000u) & ~3ull, 0x7F20);
    /* SysInitHardware's 64-bit read-modify-write */
    HW_W64(0x12000000u, ((unsigned long long)HW_R64(0x12000000u)) & ~3LL);
    CHECKX(gs_read_priv(r.gs, GS_P_PMODE), 0x7F20);
    /* 32-bit halves of a 64-bit register */
    hw_w64(GS_P_DISPLAY1, 0x1122334455667788ull);
    CHECKX(hw_r32(GS_P_DISPLAY1), 0x55667788u);
    CHECKX(hw_r32(GS_P_DISPLAY1 + 4), 0x11223344u);
    hw_w32(GS_P_DISPLAY1 + 4, 0xAABBCCDDu);
    CHECKX(gs_read_priv(r.gs, GS_P_DISPLAY1), 0xAABBCCDD55667788ull);
    /* CSR: event bits are write-1-to-clear */
    r.gs->csr_events = GS_CSR_SIGNAL | GS_CSR_FINISH;
    CHECKX(hw_r32(GS_P_CSR) & 3u, 3u);
    hw_w32(GS_P_CSR, GS_CSR_SIGNAL);
    CHECKX(r.gs->csr_events, GS_CSR_FINISH);
    hw_w64(GS_P_IMR, 0xFF00);
    CHECKX(gs_read_priv(r.gs, GS_P_IMR), 0x7F00);          /* the model masks IMR */
    rig_down(&r);
}

static void t_sif(void)
{
    rig r;
    rig_up(&r, 0);
    CHECKX(hw_r32(0x1000F230u), SIF_STAT_SIFINIT | SIF_STAT_CMDINIT | SIF_STAT_BOOTEND);
    hw_w32(0x1000F200u, 0xCAFE0000u);                      /* MSCOM */
    CHECKX(sif_reg_get(SIF_REG_MSCOM), 0xCAFE0000u);
    hw_w32(0x1000F220u, 0x10);                             /* MSFLAG: EE writes set */
    hw_w32(0x1000F220u, 0x01);
    CHECKX(sif_reg_get(SIF_REG_MSFLAG), 0x11);
    hw_w32(0x1000F230u, SIF_STAT_CMDINIT);                 /* SMFLAG: EE writes clear */
    CHECKX(sif_reg_get(SIF_REG_SMFLAG), SIF_STAT_SIFINIT | SIF_STAT_BOOTEND);
    hw_w32(0x1000F260u, 7);                                /* BD6 */
    CHECKX(hw_r32(0x1000F260u), 7);
    rig_down(&r);
}

static uint64_t g_ipu_last;
static int g_ipu_calls;
static uint64_t ipu_rd(void *u, uint32_t a, int bits)
{
    (void)u; (void)bits;
    g_ipu_calls++;
    return a == 0x10002010u ? 0x80000000u : 0;
}
static void ipu_wr(void *u, uint32_t a, uint64_t v, int bits)
{
    (void)u; (void)a; (void)bits;
    g_ipu_calls++;
    g_ipu_last = v;
}

static void t_ipu(void)
{
    rig r;
    hwbus_ipu_hooks h;
    rig_up(&r, 0);
    /* stub: BUSY reads 0, so `while (IPU_CTRL < 0)` exits */
    hw_w32(0x10002010u, 0x80000000u | 0x00F00000u);
    CHECK((int32_t)hw_r32(0x10002010u) >= 0);
    hw_w32(0x10002010u, 1u << 30);                         /* RST */
    CHECKX(hw_r32(0x10002010u), 0);
    CHECK(hwbus_get_stats()->ipu_stub_accesses >= 3);
    /* hooked: the service owns the registers */
    memset(&h, 0, sizeof h);
    h.read = ipu_rd;
    h.write = ipu_wr;
    hwbus_set_ipu(&h);
    hw_w32(0x10002000u, 0x70000000u);
    CHECKX(g_ipu_last, 0x70000000u);
    CHECK((int32_t)hw_r32(0x10002010u) < 0);
    CHECK(g_ipu_calls == 2);
    hwbus_set_ipu(NULL);
    rig_down(&r);
}

static void t_unknown(void)
{
    rig r;
    const hwbus_unknown_rec *u;
    rig_up(&r, 0);
    CHECKX(hw_r32(0x1000F100u), 0);
    CHECKX(hw_r32(0x1000F100u), 0);
    hw_w32(0x1000F100u, 0x55);
    hw_w64(0x11000000u, 0x77);
    CHECK(g_logs == 2);                                    /* once per address */
    CHECK(strstr(g_last_log, "0x11000000") != NULL);
    CHECK(hwbus_unknown_count() == 2);
    u = hwbus_unknown_get(0);
    CHECK(u && u->addr == 0x1000F100u && u->reads == 2 && u->writes == 1 &&
          u->last_write == 0x55 && u->bits == 32);
    u = hwbus_unknown_get(1);
    CHECK(u && u->addr == 0x11000000u && u->writes == 1 && u->bits == 64);
    CHECK(hwbus_unknown_total() == 4);
    /* misaligned access to a known register is unknown too */
    hw_r32(0x10000002u);
    CHECK(hwbus_unknown_count() == 3);
    rig_down(&r);
}

/* ---- spin backstop: per-read charge ---- */
static uint64_t g_hook_cycles;
static void hook_charge(void *u, uint64_t c) { (void)u; g_hook_cycles += c; }

static uint64_t g_t_before, g_t_after;
static uint32_t g_count_before, g_count_after;
static int g_reads;
static void spin_main(void *arg)
{
    int i;
    (void)arg;
    g_t_before = ps2k_now();
    for (i = 0; i < 1000; i++) hw_r32(PS2K_INTC_STAT);
    g_t_after = ps2k_now();
    /* a T0_COUNT poll loop (HBLNK clock) terminates: time passes per read */
    hw_w32(PS2K_T0_MODE, 0x83);
    g_count_before = hw_r32(PS2K_T0_COUNT);
    g_reads = 0;
    while (hw_r32(PS2K_T0_COUNT) < g_count_before + 3u && g_reads < 10000000) g_reads++;
    g_count_after = hw_r32(PS2K_T0_COUNT);
}

static void t_spin_charge(void)
{
    rig r;
    rig_up(&r, 1);
    /* hook: every read charges read_cycles, writes nothing */
    hwbus_set_charge(hook_charge, NULL);
    g_hook_cycles = 0;
    hw_r32(PS2K_T0_COUNT); hw_r64(GS_P_CSR); hw_w32(PS2K_T0_MODE, 0x80);
    CHECKX(g_hook_cycles, 2 * HWBUS_DEFAULT_READ_CYCLES);
    hwbus_set_read_cycles(10);
    hw_r16(PS2K_T0_MODE);
    CHECKX(g_hook_cycles, 2 * HWBUS_DEFAULT_READ_CYCLES + 10);
    hwbus_set_read_cycles(0);
    hw_r32(PS2K_T0_COUNT);
    CHECKX(g_hook_cycles, 2 * HWBUS_DEFAULT_READ_CYCLES + 10);
    hwbus_set_read_cycles(HWBUS_DEFAULT_READ_CYCLES);
    hwbus_set_charge(NULL, NULL);
    /* outside a guest thread: counted as uncharged, the clock does not move */
    {
        uint64_t t0 = ps2k_now();
        hw_r32(PS2K_T0_COUNT);
        CHECKX(ps2k_now(), t0);
        CHECKX(hwbus_get_stats()->uncharged_cycles, HWBUS_DEFAULT_READ_CYCLES);
    }
    /* in a guest thread: the real kernel clock advances 4 cycles per read */
    CHECK(ps2k_run(spin_main, NULL, 10) == PS2K_RUN_MAIN_EXIT);
    CHECKX(g_t_after - g_t_before, 1000 * HWBUS_DEFAULT_READ_CYCLES);
    CHECK(g_count_after >= g_count_before + 3u);
    CHECK(g_reads > 0 && g_reads < 10000000);
    rig_down(&r);
}

static void t_spr_ovl(void)
{
    rig r;
    static uint8_t ovl_block[0x400];
    rig_up(&r, 0);
    CHECK(hw_spr_base() == r.d->spr);
    CHECK((uint8_t *)PS2_SPR(0x40) == r.d->spr + 0x40);
    CHECK((uint8_t *)PS2_SPR(0x70000040u) == r.d->spr + 0x40);   /* raw window offset */
    CHECKX(dmac_canon_addr(r.d, (uint32_t)(uintptr_t)PS2_SPR(0x40)), 0x80000040u);
    /* identity mirrors */
    {
        int x;
        CHECK(PS2_UNCACHED(&x) == &x && PS2_UCAB(&x) == &x && PS2_PHYS(0x1234) == 0x1234);
    }
    hwbus_set_ovl_resolver(NULL, NULL);
    /* unresolved: scratch slot, reported, value round-trips */
    RG_OVL_DATA(signed char, normal, D_00527020, 0x00527020u, 0x3AE) = 1;
    CHECK(RG_OVL_DATA(signed char, normal, D_00527020, 0x00527020u, 0x3AE) == 1);
    CHECK(hwbus_ovl_unresolved() == 2);
    rig_down(&r);
    (void)ovl_block;
}

/* ---- control: kernel asked first for D_STAT drops the DMAC's bits ---- */
static void t_dstat_order(int control)
{
    rig r;
    rig_up(&r, 1);
    hwbus_debug_kernel_first = control;
    r.d->stat_local |= 1u << 15;                           /* BEIS */
    CHECKX(hw_r32(DMAC_D_STAT) & 0x8000u, 0x8000u);
    hw_w32(DMAC_D_STAT, 1u << 15);
    CHECKX(r.d->stat_local & 0x8000u, 0);
    hwbus_debug_kernel_first = 0;
    rig_down(&r);
}

/* ---------------------------------------------------------------- game e2e */
#ifdef RG_HWBUS_GAME_E2E
/* game functions rewritten by the hwaccess stage (built from game/) */
typedef struct { uint8_t pad00[0x1C]; int32_t f[9]; int32_t sema, f44; } vibuf_save;
void ViBufSetD4Chcr_1d47a0(unsigned int h);
void ViBufSetD3Chcr_1d4800(unsigned int h);
int ViBufStopDma_1d4180(vibuf_save *s);
int ViBufDelete_1d3e20(void *p);
void FieldHudInitOnce_204120(void);
int ViBufGetFifoIndex_1d4860(uint8_t *o, int arg);
/* their callees, stubbed */
static int g_di, g_ei, g_sema;
int DisableIntr_120660(void) { g_di++; return 1; }
void EnableIntr_1206b0(void) { g_ei++; }
void WaitSema(int s) { (void)s; g_sema++; }
void SignalSema(int s) { (void)s; g_sema++; }
void DeleteSema(int s) { (void)s; g_sema++; }
int D_00481C5C = 1;  /* FieldHudInitOnce: already initialised, skip the overlay calls */
uint8_t D_004BBC80[16], D_004BC250[16];
uint8_t D_00527020[0x400];  /* NORMAL FieldHud block (the arena label in rg-game) */
void func_4F19E0(const uint8_t *p) { (void)p; abort(); }
void func_4F6F00(const uint8_t *p) { (void)p; abort(); }
void func_4F6F50(const uint8_t *p) { (void)p; abort(); }
void func_4FAAC0(uint8_t *p) { (void)p; abort(); }
void func_506B70(const uint8_t *p, int x) { (void)p; (void)x; abort(); }
void func_506C10(const uint8_t *p) { (void)p; abort(); }
void func_506D80(const uint8_t *p) { (void)p; abort(); }
void func_506DC0(const uint8_t *p, uint8_t *q) { (void)p; (void)q; abort(); }
void func_509040(int a, int b, int c) { (void)a; (void)b; (void)c; abort(); }

static uint8_t g_normal_bss[0x1200];
static void *resolve_normal(void *u, const char *ovl, const char *sym, uint32_t addr)
{
    (void)u;
    if (strcmp(ovl, "normal") == 0 && strcmp(sym, "D_00527020") == 0 && addr == 0x00527020u)
        return g_normal_bss + (addr - 0x00527000u);
    return NULL;
}

static void t_game_e2e(void)
{
    rig r;
    vibuf_save s;
    uint8_t ring[0x60];
    rig_up(&r, 0);
    /* ViBufSetD4Chcr: suspend D4 via D_ENABLEW, write CHCR, resume */
    r.d->enable = 0x1200u;
    ViBufSetD4Chcr_1d47a0(5);
    CHECKX(r.d->ch[DMAC_TO_IPU].chcr & 0xFFFFu, 5);
    CHECKX(r.d->enable, 0x1200u);                          /* CPND set, then cleared */
    CHECK(g_di == 1 && g_ei == 1);
    CHECK(hwbus_get_stats()->writes[HWBUS_DMAC] == 3);
    /* ViBufStopDma: saves D4/D3 registers and the IPU, polls IPU_CTRL */
    r.d->ch[DMAC_TO_IPU].madr = 0x00400000u;
    r.d->ch[DMAC_TO_IPU].tadr = 0x00400100u;
    r.d->ch[DMAC_TO_IPU].qwc = 0x20;
    r.d->ch[DMAC_FROM_IPU].madr = 0x00500000u;
    r.d->ch[DMAC_FROM_IPU].qwc = 0x30;
    hw_w32(0x10002010u, 0x00A00000u);                      /* IPU_CTRL (stub) */
    memset(&s, 0, sizeof s);
    CHECK(ViBufStopDma_1d4180(&s) == 1);
    CHECKX(s.f[0], 0x00400000u);                           /* D4_MADR */
    CHECKX(s.f[1], 0x00400100u);                           /* D4_TADR */
    CHECKX(s.f[2], 0x20);                                  /* D4_QWC */
    CHECKX(s.f[3] & 0xFFFF, 5);                            /* D4_CHCR */
    CHECKX(s.f[4], 0x00500000u);                           /* D3_MADR */
    CHECKX(s.f[5], 0x30);                                  /* D3_QWC */
    CHECKX(s.f[8], 0x00A00000u);                           /* IPU_CTRL */
    /* ViBufDelete zeroes D4 QWC/MADR/TADR */
    CHECK(ViBufDelete_1d3e20(ring) == 1);
    CHECKX(r.d->ch[DMAC_TO_IPU].madr, 0);
    CHECKX(r.d->ch[DMAC_TO_IPU].qwc, 0);
    CHECKX(r.d->ch[DMAC_TO_IPU].tadr, 0);
    /* ViBufGetFifoIndex: the 0x0FFFFFFF mask is now the identity on a host
     * address above 0x0FFFFFFF (the retail mask would have broken it) */
    memset(ring, 0, sizeof ring);
    *(int32_t *)(ring + 4) = 0x12345670;                   /* data (host address) */
    *(int32_t *)(ring + 8) = 1;                            /* count - 1 */
    CHECK(ViBufGetFifoIndex_1d4860(ring, 0x12345670 + (2 << 4)) == 0);
    /* FieldHudInitOnce: the overlay-data store lands in NORMAL's D_00527020 + 0x3AE,
     * a direct reference since 2026-10-18 (docs/UB-AUDIT.md "RG_OVL_DATA"); the
     * resolver must not be asked */
    hwbus_set_ovl_resolver(resolve_normal, NULL);
    memset(g_normal_bss, 0, sizeof g_normal_bss);
    memset(D_00527020, 0, sizeof D_00527020);
    FieldHudInitOnce_204120();
    CHECKX(D_00527020[0x3AE], 1);
    CHECKX(g_normal_bss[0x5273CE - 0x527000], 0);
    hwbus_set_ovl_resolver(NULL, NULL);
    CHECK(hwbus_unknown_count() == 0);
    rig_down(&r);
}
#endif

/* ---------------------------------------------------------------- main */
int main(int argc, char **argv)
{
    const char *t = argc > 1 ? argv[1] : "";
    if (!strcmp(t, "claims")) t_claims();
    else if (!strcmp(t, "kernel")) t_kernel();
    else if (!strcmp(t, "dmac")) t_dmac();
    else if (!strcmp(t, "fifo_vif_gif")) t_fifo_vif_gif();
    else if (!strcmp(t, "gs_priv")) t_gs_priv();
    else if (!strcmp(t, "sif")) t_sif();
    else if (!strcmp(t, "ipu")) t_ipu();
    else if (!strcmp(t, "unknown")) t_unknown();
    else if (!strcmp(t, "spin_charge")) t_spin_charge();
    else if (!strcmp(t, "spr_ovl")) t_spr_ovl();
    else if (!strcmp(t, "dstat_order")) t_dstat_order(0);
    else if (!strcmp(t, "dstat_order_control")) t_dstat_order(1);
#ifdef RG_HWBUS_GAME_E2E
    else if (!strcmp(t, "game_e2e")) t_game_e2e();
#endif
    else {
        fprintf(stderr, "unknown test '%s'\n", t);
        return 2;
    }
    if (g_fail) return 1;
    printf("%s: ok\n", t);
    return 0;
}
