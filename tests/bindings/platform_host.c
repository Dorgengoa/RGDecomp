/* SPDX-License-Identifier: CC0-1.0 */
/* Host side of the `platform` and `vcallms` binding lanes (ctest -L bindings):
 * the real kernel HLE (src/ps2/kernel + src/sce/kernel), the HW_* bus
 * (src/ps2/hwbus) over a GS / DMAC / VIF1 model, and the retail VU0
 * microprogram on the src/ps2/vu interpreter.  The lane files themselves are
 * compiled with the game flags and only see these bth_* entry points. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "dmac.h"
#include "gs.h"
#include "hwbus.h"
#include "ps2k.h"
#include "vif.h"
#include "vu.h"
#include "vu_retail.h"

/* include/port/vu0.h (not includable here: it is the game-side header) */
void rg_vu0_micro_bind(struct vu_state *vu);

/* ------------------------------------------------------------ kernel + bus */

static gs_state *g_gs;
static dmac_state *g_dmac;
static vu_state g_vu1;
static vif_state g_vif1;
static unsigned g_violations;

static void on_violation(const char *call, const char *why)
{
    g_violations++;
    printf("kernel violation: %s: %s\n", call, why);
}

/* Boots the kernel and the bus, runs `main` as guest thread 1 (prio 10) to
 * completion, tears everything down.  Returns the PS2K_RUN_* code. */
int bth_kernel_run(void (*main_fn)(void *))
{
    ps2k_config cfg;
    int rc;
    ps2k_default_config(&cfg);
    cfg.stop_at_cycles = 200ull * 2460060ull; /* 200 fields: a hang fails, not blocks */
    g_violations = 0;
    ps2k_set_violation_hook(on_violation);
    if (ps2k_init(&cfg) != 0)
        return -1;
    g_gs = gs_create();
    g_dmac = dmac_create();
    vu_init(&g_vu1, 1);
    vif_init(&g_vif1, 1, &g_vu1);
    dmac_attach_vif(g_dmac, 1, &g_vif1);
    hwbus_init();
    hwbus_bind(g_dmac, g_gs);
    hwbus_set_read_cycles(0); /* reads must not move the clock under the checks */
    rc = ps2k_run(main_fn, NULL, 10);
    ps2k_shutdown();
    hwbus_init();
    dmac_destroy(g_dmac);
    vif_free(&g_vif1);
    gs_destroy(g_gs);
    g_dmac = NULL;
    g_gs = NULL;
    ps2k_set_violation_hook(NULL);
    return rc;
}

unsigned bth_violations(void) { return g_violations; }
int bth_create_sema(int init, int max) { return ps2k_create_sema(init, max, 0, 0); }
int bth_wait_sema(int id) { return ps2k_wait_sema(id); }
int bth_signal_sema(int id) { return ps2k_signal_sema(id, 0); }
int bth_poll_sema(int id) { return ps2k_poll_sema(id, 0); }
void bth_delete_sema(int id) { ps2k_delete_sema(id, 0); }

int bth_sema_count(int id)
{
    ps2k_sema_info info;
    if (ps2k_refer_sema_status(id, &info, 0) < 0)
        return -1;
    return info.current_count;
}

int bth_add_intc(int cause, int (*fn)(int), int next)
{
    int id = ps2k_add_intc_handler(cause, (ps2k_handler_fn)fn, next);
    ps2k_enable_intc(cause, 0);
    return id;
}

void bth_remove_intc(int cause, int id) { ps2k_remove_intc_handler(cause, id); }
void bth_raise_intc(int cause) { ps2k_raise_intc(cause); }
void bth_poll(void) { ps2k_poll(); }
int bth_wait_vblank(void) { return ps2k_wait_vblank(); }
uint64_t bth_vblank_count(void) { return ps2k_vblank_count(); }
uint64_t bth_now(void) { return ps2k_now(); }

void bth_gs_set_field(int f) { g_gs->csr_field = (uint32_t)f & 1u; }
/* T0: count BUSCLK (MODE.CUE), so its COUNT moves with virtual time */
void bth_t0_start(void) { ps2k_hw_write32(0x10000010u, 0x80u); }
uint32_t bth_t0_count(void) { return ps2k_hw_read32(0x10000000u); }
void bth_vif1_set_irq(int v) { g_vif1.irq = v; }
int bth_vif1_irq(void) { return g_vif1.irq; }
uint64_t bth_vif_writes(void) { return hwbus_get_stats()->writes[HWBUS_VIF]; }

/* ------------------------------------------------------------ VU0 micro mode */

static rg_elf g_elf;
static int g_elf_ok = -1;
static vu_state g_vu0;      /* the port's VU0 (bound to vcallms) */
static vu_state g_vu0_ref;  /* reference: the tests/vu vu0_srt procedure */
static vif_state g_vif0, g_vif0_ref;

static int load_program(vif_state *vif, vu_state *vu)
{
    size_t n;
    const uint32_t *w;
    vu_init(vu, 0);
    vif_init(vif, 0, vu);
    w = rg_vif_packet(&g_elf, 0x445810u, &n); /* GfxSysInit's VIF0 chain (MPG) */
    if (!w)
        return -1;
    vif_write(vif, w, n);
    return 0;
}

/* 0 = ready, 77 = no retail ELF, -1 = broken */
int bth_vcallms_setup(void)
{
    if (g_elf_ok < 0) {
        if (rg_elf_load(&g_elf, rg_retail_elf_path())) {
            printf("SKIP vcallms: retail ELF not found at %s (set RG_ELF)\n", rg_retail_elf_path());
            g_elf_ok = 0;
            return 77;
        }
        if (load_program(&g_vif0, &g_vu0) || load_program(&g_vif0_ref, &g_vu0_ref))
            return -1;
        g_elf_ok = 1;
    }
    if (!g_elf_ok)
        return 77;
    rg_vu0_micro_bind(&g_vu0);
    return 0;
}

void bth_vcallms_unbind(void) { rg_vu0_micro_bind(NULL); }

/* tests/vu vu_smoke.c run_vu0: scale vf1, angles vf2, translation vf3 (w as
 * given), vcallms 0 = vu_start(0) + run to the E bit; matrix rows vf4..vf7. */
int bth_vu0_srt_ref(const float s[4], const float r[4], const float t[4], float m[16])
{
    vu_state *vu = &g_vu0_ref;
    int i;
    memcpy(vu->vf[1].f, s, 16);
    memcpy(vu->vf[2].f, r, 16);
    memcpy(vu->vf[3].f, t, 16);
    vu_start(vu, 0);
    if (vu_run(vu, 100000) != VU_STOP_EBIT)
        return -1;
    vu_drain(vu);
    for (i = 0; i < 4; i++)
        memcpy(m + 4 * i, vu->vf[4 + i].f, 16);
    return 0;
}

/* registers of the bound VU0 interpreter, for the shared-state checks */
void bth_vu0_get_vf(int r, float out[4]) { memcpy(out, g_vu0.vf[r].f, 16); }
void bth_vu0_set_vf(int r, const float in[4]) { memcpy(g_vu0.vf[r].f, in, 16); }
uint64_t bth_vu0_runs(void) { return g_vu0.stats.runs; }
