/* SPDX-License-Identifier: CC0-1.0
 * rg-timing-tests <out.jsonl>: drives src/trace/timing.c over synthetic game
 * memory (fake frame context, Db, scene, globals registered in the trace
 * address map) and every built-in source, and writes a timing record that
 * tests/trace/timing_check.py judges (record words, timing.py build output).
 * Scenario (game vbl counter V):
 *   V=10  baseline, no flip yet; interval 2, game mode -1
 *   V=11  flip 11 (main thread: tick 1); overlay 2 load observed
 *   V=13  flip 13 (tick 2); interval 1, scene locked; CD read; pad read
 *   V=14  flip 14 from thread 5 (loadscreen: tick 3); game mode 11
 *   V=15  movie open (overlay 3 resident) + flip 15 (moviemodal: tick 4)
 *   V=16  movie close; wrappers start: GfxEndFrame enter/leave (tick 5, by
 *         the wrapper), PadUpdate (return only), TaskListChanged (a0 = 0
 *         skipped, a0 = 1 logged), SoundSeqUpdate (f12); then a flip that
 *         memory sees is NOT synthesised (GfxEndFrame is wrapped).
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ps2k.h"
#include "rg_trace.h"
#include "rg_timing.h"
#include "ovl.h"
#include "libcdvd.h"
#include "libpad.h"
#include "movie_game.h"

static uint32_t g_vbl, g_drawctx, g_scene, g_overlay, g_sysmode, g_pausestep, g_vsync_sema, g_waitflag;
static uint32_t g_tickready, g_diskwatch, g_seqowner, g_vutime;
static uint32_t g_taskdepth[2];
static int32_t g_modes[16], g_phases[16];
static uint8_t g_ctx[0x3D40], g_db[0x40], g_scn[0x5E20], g_pad[0x260];

static void put(uint8_t *b, uint32_t off, uint32_t v) { memcpy(b + off, &v, 4); }

static int add(uint32_t a, uint32_t n, void *p, const char *name)
{
    return rg_trace_add_symbol(a, n, p, name);
}

static void kwait(int tid)
{
    /* what the kernel's trace hook sees when a thread blocks on the vsync sema */
    ps2k_trace_rec r;
    memset(&r, 0, sizeof r);
    r.type = PS2K_TR_SEMA_WAIT;
    r.a = (int32_t)g_vsync_sema;
    r.b = tid;
    /* the hook is internal to timing.c: go through the kernel's hook slot */
    extern void rg_timing_test_ktrace(const ps2k_trace_rec *r);
    rg_timing_test_ktrace(&r);
}

int main(int argc, char **argv)
{
    rg_timing_config c;
    static const rg_ovl_desc ovls[2] = {
        {"title", "TITLE.BIN", 2, 2, 0x004E9E80u, 0, 0, 0, 0, 0, NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0},
        {"normal", "NORMAL.BIN", 3, 3, 0x004E9E80u, 0, 0, 0, 0, 0, NULL, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0},
    };
    static rg_ovl_registry reg;
    ps2k_config kc;
    int fails = 0;
    if (argc < 2) {
        fprintf(stderr, "usage: rg-timing-tests OUT.jsonl\n");
        return 2;
    }
    ps2k_default_config(&kc);
    if (ps2k_init(&kc) != 0)
        return 1;
    reg.ovls = ovls;
    reg.novls = 2;
    reg.arena_base = 0x004E9E80u;
    reg.arena_size = 0x00528200u - 0x004E9E80u;
    if (rg_ovl_bind(&reg) != 0)
        return 1;

    /* the game globals timing.c reads (probe.py T_* addresses) */
    fails += add(0x004810C4u, 4, &g_vbl, "VblankCount") != 0;
    fails += add(0x004810A4u, 4, &g_drawctx, "DrawCtx") != 0;
    fails += add(0x00481998u, 4, &g_scene, "Scene") != 0;
    fails += add(0x004B51A0u, 0x40, g_modes, "GameModeStack") != 0;
    fails += add(0x004B51E0u, 0x40, g_phases, "GameModePhaseStack") != 0;
    fails += add(0x0047E254u, 4, &g_overlay, "LoadedOverlayId") != 0;
    fails += add(0x0047E224u, 4, &g_sysmode, "SysMode") != 0;
    fails += add(0x0048276Cu, 4, &g_pausestep, "PauseStep") != 0;
    fails += add(0x00482278u, 8, g_taskdepth, "TaskDepth") != 0;
    fails += add(0x0047DF18u, 4, &g_vsync_sema, "VsyncSema") != 0;
    fails += add(0x004810C0u, 4, &g_waitflag, "VblankWaitFlag") != 0;
    fails += add(0x0047E250u, 4, &g_tickready, "TickReady") != 0;
    fails += add(0x00481558u, 4, &g_diskwatch, "DiskWatch") != 0;
    fails += add(0x00481554u, 4, &g_seqowner, "SeqOwner") != 0;
    fails += add(0x004810B4u, 4, &g_vutime, "VuTime") != 0;
    fails += add(0x004B2570u, sizeof g_pad, g_pad, "Pad0") != 0;   /* PadUpdate's object maps back */
    if (fails) {
        fprintf(stderr, "symbol registration failed\n");
        return 1;
    }
    g_drawctx = (uint32_t)(uintptr_t)g_ctx;
    g_scene = (uint32_t)(uintptr_t)g_scn;
    put(g_ctx, 0x270, (uint32_t)(uintptr_t)g_db);
    put(g_db, 0x24, 2);              /* interval */
    put(g_db, 0x2C, 262);            /* divisor */
    put(g_ctx, 0xF10, 0x40000000u);  /* fb 2.0 */
    put(g_ctx, 0x3CD0, 1);
    put(g_ctx, 0x3CDC, 0xFFFFFFFFu);
    put(g_scn, 0x5E0C, 0x3F800000u); /* mult 1.0 */
    for (int i = 0; i < 16; i++)
        g_modes[i] = g_phases[i] = -1;
    g_overlay = 0xFFFFFFFFu;
    g_vsync_sema = 7;
    g_tickready = 1;
    g_seqowner = 0;

    rg_timing_default_config(&c);
    c.out = argv[1];
    c.input = "fixture";
    if (rg_timing_open(&c) != 0 || rg_timing_attach() != 0)
        return 1;
    if (!rg_timing_on) {
        fprintf(stderr, "rg_timing_on not set\n");
        return 1;
    }

    g_vbl = 10;
    rg_timing_vblank(0);                       /* baseline */

    kwait(1);
    g_overlay = 0xFFFFFFFFu;
    rg_ovl_load(0);                            /* loader index 2 */
    g_overlay = 2;
    g_vbl = 11;
    put(g_ctx, 0xF00, 11);                     /* flip at 11 */
    rg_timing_vblank(1);

    kwait(1);
    g_vbl = 12;
    rg_timing_vblank(2);                       /* no flip */
    g_vbl = 13;
    put(g_ctx, 0xF00, 13);
    put(g_db, 0x24, 1);
    put(g_scn, 0x5E14, 1);
    {
        sceCdRMode m = {0, 0, 0, 0};
        static uint8_t buf[2048];
        sceCdRead(1234, 3, buf, &m);           /* observer fires before the drive */
    }
    rg_timing_vblank(3);

    kwait(5);                                  /* the loading-screen thread flips */
    g_vbl = 14;
    put(g_ctx, 0xF00, 14);
    g_modes[0] = 11;
    rg_timing_vblank(4);

    kwait(1);
    rg_ovl_load(1);                            /* NORMAL (loader index 3) resident */
    g_overlay = 3;
    rg_movie_g_open("cdrom0:\\MOVIE\\NONE.PSS;1", 0, 0);   /* fails to play: still an open event */
    g_vbl = 15;
    put(g_ctx, 0xF00, 15);
    rg_timing_vblank(5);
    rg_movie_g_close();

    /* the probe_wrap stage's calls */
    g_vbl = 16;
    put(g_ctx, 0xF04, 0);
    rg_timing_enter(RG_TIMING_GfxEndFrame, RG_TIMING_ARGPTR(0), NULL, (uint32_t)(uintptr_t)g_ctx, 1, 0, 0, 0);
    put(g_ctx, 0xF00, 16);
    rg_timing_leave(RG_TIMING_GfxEndFrame, 0, 25);
    put(g_pad, 4, 0xBFFF);
    put(g_pad, 0x5C, 0xFFFF);
    rg_timing_enter(RG_TIMING_PadUpdate, RG_TIMING_ARGPTR(0), NULL, (uint32_t)(uintptr_t)g_pad, 0, 0, 0, 0);
    rg_timing_leave(RG_TIMING_PadUpdate, 0, 0);
    rg_timing_enter(RG_TIMING_TaskListChanged, 0, NULL, 0, 0, 0, 0, 0);
    rg_timing_leave(RG_TIMING_TaskListChanged, 0, 0);
    rg_timing_enter(RG_TIMING_TaskListChanged, 0, NULL, 1, 0, 0, 0, 0);
    rg_timing_leave(RG_TIMING_TaskListChanged, 0, 0);
    rg_timing_enter(RG_TIMING_SoundSeqUpdate, 0, NULL, 0, 0, 0, 0, 0x40000000u);
    rg_timing_leave(RG_TIMING_SoundSeqUpdate, 0, 0);
    g_vbl = 18;
    put(g_ctx, 0xF00, 18);                     /* memory flip: not synthesised any more */
    rg_timing_vblank(6);

    if (rg_timing_site_count() != 21 || rg_timing_site_find("GfxEndFrame_141c20") != RG_TIMING_GfxEndFrame ||
        rg_timing_site_find("VblankStart") != 1) {
        fprintf(stderr, "site table lookups wrong (%d sites)\n", rg_timing_site_count());
        return 1;
    }
    {
        const rg_timing_stats *st = rg_timing_get_stats();
        printf("records=%llu vblanks=%llu mem_ticks=%llu wrapped=%llu ovl=%llu cd=%llu movie=%llu vsw=%llu\n",
               (unsigned long long)st->records, (unsigned long long)st->vblanks,
               (unsigned long long)st->mem_ticks, (unsigned long long)st->wrapped_calls,
               (unsigned long long)st->overlay_loads, (unsigned long long)st->cd_reads,
               (unsigned long long)st->movie_events, (unsigned long long)st->vsync_waits);
    }
    rg_timing_detach();
    rg_timing_close("test end");
    rg_ovl_unbind();
    ps2k_shutdown();
    return 0;
}
