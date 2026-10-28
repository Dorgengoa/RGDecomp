/* SPDX-License-Identifier: CC0-1.0
 * rg_trace runtime glue: environment -> rg_runtime config, the RAM-block
 * mapping, and the VBLANK_START observer that takes the samples
 * (docs/TRACE-PORT.md "Running").  Uses only public runtime/kernel APIs: a
 * service hook and a kernel VBlank observer; no runtime internals. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k.h"
#include "rg_runtime.h"
#include "rg_trace.h"
#include "rg_timing.h"

static struct {
    rg_trace_config cfg;
    int armed;      /* apply_env saw RG_TRACE_OUT */
    int obs;
    int atexit_set;
} G;

/* Sample point: the kernel processes VBLANK_START at its exact virtual time,
 * before any game handler for it runs: the same instant PCSX2's frame
 * limiter freezes the EE (tools/trace/README.md), so the game counter has not
 * yet been incremented for this VBlank on either side. */
static void on_vblank(int which, uint64_t field, void *user)
{
    (void)user;
    if (which != PS2K_VBLANK_START || !rg_trace_is_open())
        return;
    if (rg_trace_sample(field, ps2k_now(), (uint32_t)field))
        rg_runtime_request_quit();
}

static void at_exit(void) { rg_trace_close("process exit"); }

static void service(void *user)
{
    (void)user;
    const rg_ps2_ram *ram = rg_crt0_ram();
    if (ram && ram->heap_start)
        rg_trace_set_heap(ram->heap_start, RG_PS2_HEAP_START, RG_PS2_HEAP_SIZE);
    if (rg_trace_open(&G.cfg) != 0) {
        fprintf(stderr, "rg_trace: recorder not started; quitting\n");
        rg_runtime_request_quit();
        return;
    }
    G.obs = ps2k_add_vblank_observer(on_vblank, NULL);
    if (G.obs < 0) {
        fprintf(stderr, "rg_trace: no free VBlank observer slot\n");
        rg_trace_close("no observer slot");
        rg_runtime_request_quit();
        return;
    }
    if (!G.atexit_set) {
        atexit(at_exit);
        G.atexit_set = 1;
    }
    if (!G.cfg.quiet)
        fprintf(stderr, "rg_trace: recording %s (regions %s)\n", G.cfg.out, G.cfg.regions);
}

uint32_t rg_trace_game_vblank(void *user, uint64_t kernel_vblank)
{
    (void)user;
    int game = 0;
    uint32_t v = rg_trace_read_vbl((uint32_t)kernel_vblank, &game);
    /* padman writes the frame's report at VBLANK_START, before the game's
     * handler increments the counter; the game decodes it later in the frame,
     * when the counter is one higher.  input.py's hook ORs table[counter] at
     * decode time, so the report for this VBlank is the script word for
     * counter + 1 (RG_TRACE_INPUT_LEAD, default 1). */
    return game ? v + (uint32_t)G.cfg.input_lead : (uint32_t)kernel_vblank;
}

/* ---- timing record (rg_timing.h, docs/TIMING-LOCKSTEP.md) ---- */
static struct {
    rg_timing_config cfg;
    int atexit_set;
} TM;

static void timing_at_exit(void) { rg_timing_close("process exit"); }

static void timing_service(void *user)
{
    (void)user;
    const rg_ps2_ram *ram = rg_crt0_ram();
    if (ram && ram->heap_start)
        rg_trace_set_heap(ram->heap_start, RG_PS2_HEAP_START, RG_PS2_HEAP_SIZE);
    if (rg_timing_open(&TM.cfg) != 0 || rg_timing_attach() != 0) {
        fprintf(stderr, "rg_timing: record not started; quitting\n");
        rg_timing_close("attach failed");
        rg_runtime_request_quit();
        return;
    }
    if (!TM.atexit_set) {
        atexit(timing_at_exit);
        TM.atexit_set = 1;
    }
    if (!TM.cfg.quiet)
        fprintf(stderr, "rg_timing: recording %s\n", TM.cfg.out);
}

int rg_timing_apply(struct rg_runtime_config *cfg)
{
    rg_timing_default_config(&TM.cfg);
    int r = rg_timing_config_from_env(&TM.cfg);
    if (r < 0)
        return -1;
    if (cfg->timing_out) {
        TM.cfg.out = cfg->timing_out;
        r = 1;
    }
    if (!r)
        return 0;
    TM.cfg.input = cfg->input_script;
    TM.cfg.quiet = cfg->quiet;
    /* input scripts are keyed by the game counter (docs/TRACE-PORT.md "Sample point") */
    if (!cfg->game_vblank) {
        cfg->game_vblank = rg_trace_game_vblank;
        cfg->game_vblank_user = NULL;
    }
    rg_runtime_set_service_hook(timing_service, NULL);
    return 1;
}

int rg_trace_apply_env(struct rg_runtime_config *cfg)
{
    rg_trace_default_config(&G.cfg);
    int r = rg_trace_config_from_env(&G.cfg);
    if (r < 0)
        return r;
    int t = rg_timing_apply(cfg);
    if (t < 0)
        return -1;
    if (r == 0)
        return t;
    if (!G.cfg.regions) {
        fprintf(stderr, "rg_trace: RG_TRACE_OUT needs RG_TRACE_REGIONS\n");
        return -1;
    }
    const char *hl = getenv("RG_TRACE_HEADLESS");
    if (!hl || strcmp(hl, "0") != 0)
        cfg->headless = 1;
    if (G.cfg.input && !cfg->input_script)
        cfg->input_script = G.cfg.input;
    else if (cfg->input_script && !G.cfg.input)
        G.cfg.input = cfg->input_script;
    if (!cfg->game_vblank) {
        cfg->game_vblank = rg_trace_game_vblank;
        cfg->game_vblank_user = NULL;
    }
    G.cfg.quiet = cfg->quiet;
    if (t > 0 && !TM.cfg.input)
        TM.cfg.input = cfg->input_script;
    G.armed = 1;
    rg_runtime_set_service_hook(service, NULL);
    return 1;
}
