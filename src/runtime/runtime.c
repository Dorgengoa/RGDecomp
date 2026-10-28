/* SPDX-License-Identifier: CC0-1.0
 * rg_runtime: platform glue (docs/RUNTIME.md).  Boots every model under the
 * host shell in a fixed order and drives the kernel's virtual clock a field
 * at a time.  See rg_runtime.h. */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rg_runtime.h"
#include "rg_settings.h"

#include "cdvd.h"
#include "dmac.h"
#include "gs.h"
#include "host.h"
#include "hwbus.h"
#include "iop.h"
#include "libcdvd.h"
#include "libdma.h"
#include "libsif.h"
#include "mccard.h"
#include "mcserv.h"
#include "padman.h"
#include "rg_iop.h"     /* RG_IOP=native|hle (docs/NATIVE-IOP.md) */
#include "rg_iop_fio.h"
#include "rg_npad.h"    /* native pad service */
#include "ps2k.h"
#include "rg_threads.h" /* frame driver field end (docs/NATIVE-THREADS.md) */
#include "rg_pace.h"    /* paced mode: host clock -> VBlank phases (docs/NATIVE-THREADS.md) */
#include "rg_fs.h"
#include "rg_fs_oracle.h"
#include "fstats_sys.h" /* $RG_FIELD_STATS host samples */
#include "snd.h"
#include "vif.h"
#include "vu.h"
#ifdef RG_HAVE_GPU
#include "gpu.h"
#else
/* the counters $RG_AUDIO_LOG reads (all zero without the GPU renderer) */
typedef struct gpu_stats {
    uint64_t prims, batches, dst_copies, rt_writebacks, upload_bytes, download_bytes;
} gpu_stats;
#endif
#ifdef RG_HAVE_NATIVE_RENDER
#include "nr.h"   /* native renderer (docs/NATIVE-RENDER.md) */
#include "nr_interp.h"   /* interpolated presentation (docs/NATIVE-RENDER.md) */
#endif
/* interpolated presentation (the unlocked frame rate): the native-only device only */
#if defined(RG_HAVE_NATIVE_RENDER) && defined(RG_NATIVE_GS) && RG_NATIVE_GS && defined(RG_HAVE_GPU)
#define RT_IP 1
#else
#define RT_IP 0
#endif
#if RT_IP
/* zero-copy presentation with the Vulkan backend (docs/NATIVE-VULKAN.md "Presentation"): the
 * handle gpu_present_shared returns goes to rg_host_present_shared as it is */
_Static_assert(sizeof(gpu_vk_frame) == sizeof(rg_host_vk_frame) &&
                   offsetof(gpu_vk_frame, arg) == offsetof(rg_host_vk_frame, arg) &&
                   offsetof(gpu_vk_frame, release) == offsetof(rg_host_vk_frame, release) &&
                   offsetof(gpu_vk_frame, img_w) == offsetof(rg_host_vk_frame, img_w),
               "gpu_vk_frame / rg_host_vk_frame layouts");
#endif
/* The GS of this build (docs/NATIVE-RENDER.md "Checkpoint 10"): RG_NATIVE_GS (a native-only
 * rg-game with the native device) has no GS model: the native state block (nr_gs.h), the native
 * worker (nr_q.c) and the device's local memory; every other build the GS model (src/ps2/gs)
 * and its worker (gs_async.c).  gsq_* are the worker calls of either. */
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
#include "nr_gs.h"
typedef nr_gs rt_gs;
static void gsq_drain(void) { nr_q_drain(); }
static int gsq_on(void) { return nr_q_on(); }
static int gsq_start(void) { return nr_q_start(); }
static void gsq_stop(void) { nr_q_stop(); }
static void gsq_stats(uint64_t o[4]) { nr_q_stats(o); }
static double gsq_wait_ms(void) { return nr_q_wait_ms(); }
static uint64_t gsq_mark(void) { return nr_q_mark(); }
static void gsq_wait_mark(uint64_t m) { nr_q_wait_mark(m); }
#else
typedef gs_state rt_gs;
#define gsq_drain() gs_async_drain(R.gs)
#define gsq_on() gs_async_on(R.gs)
#define gsq_start() gs_async_start(R.gs)
#define gsq_stop() gs_async_stop(R.gs)
#define gsq_stats(o) gs_async_stats(R.gs, o)
#define gsq_wait_ms() gs_async_wait_ms(R.gs)
#define gsq_mark() gs_async_mark(R.gs)
#define gsq_wait_mark(m) gs_async_wait_mark(R.gs, m)
#endif
#ifdef RG_HAVE_NATIVE_AUDIO
#include "rg_audio_game.h"   /* native audio engine (docs/NATIVE-AUDIO.md) */
#include "rg_audio.h"        /* ra_get_stats ($RG_FIELD_STATS) */
/* its clocks in 48 kHz frames: the virtual clock; the HLE's render position (compare
 * mode puts each command where the HLE applied it) and the HLE's 240 Hz tick origin */
static unsigned long long ra_clk_native(void *u) { (void)u; return ps2k_now() / SND_CYCLES_PER_FRAME; }
#if RG_IOP_ORACLE
static unsigned long long ra_clk_hle(void *u) { (void)u; return snd_clock_frame(); }
static unsigned long long ra_clk_hle_origin(void *u) { (void)u; snd_sync(); return snd_clock_frame() - snd_frames_rendered(); }
#else
#define ra_clk_hle NULL /* native-only: no sound HLE to align a compare run with */
#define ra_clk_hle_origin NULL
#endif
#elif !RG_IOP_ORACLE
#error "RG_NATIVE_ONLY needs the native audio engine (RG_HAVE_NATIVE_AUDIO)"
#endif

/* include/port/vu0.h: vcallms runs on this VU0 (src/ps2/vu0_micro.c).  Only the VU0 model
 * (RG_VU0_MODE=model, the oracle) has a vcallms interpreter path; local / native call the
 * microprogram as C (rg_vu0_srt) and never bind (docs/NATIVE-CPU.md section 8). */
#if RG_VU0_MICRO_BIND
void rg_vu0_micro_bind(struct vu_state *vu);
#endif

/* libmc.h pulls in the SDK card structs; only the clock is needed here */
struct mc_datetime;
void rg_mc_virtual_clock(void *user, struct mc_datetime *out);

#define AUDIO_CAP_FRAMES 4096u
#define DISPLAY_CAP_PX (1024u * 1024u)

static struct {
    int inited, started, finished, quit;
    int last_rc;
    rg_runtime_config cfg;
    char data_dir[512], saves_dir[512];

    rg_host *host;
    rg_pacer pacer;
    /* paced mode (docs/NATIVE-THREADS.md "Paced mode"): host clock -> VBlank phases; host
     * state only (never saved, never folded into the run hash) */
    rg_pace pace;
    uint64_t pace_gen;
    int pace_applied;
    FILE *pace_log;            /* $RG_PACE_LOG=path: one TSV row per host second */
    FILE *present_log;         /* $RG_PRESENT_LOG=path: one TSV row per present (tools/native/present_pacing.py) */
    double present_log_t0;
    uint64_t pace_sec, pace_row_ticks, pace_row_presents, pace_row_logic;
    rg_input_script script;
    int have_script;

    rt_gs *gs;
    uint8_t *gs_img;           /* RG_NATIVE_GS: the device's local memory at a save / load (4 MB) */
    vu_state vu0, vu1;
    vif_state vif0, vif1;
    dmac_state *dmac;

    int obs_id, cdvd_dev_id;
    int order[RG_INIT_COUNT];
    int norder;

    rg_runtime_stats st;
    int16_t *audio;
    uint32_t *frame;
    uint32_t frame_cap;        /* pixels in frame (DISPLAY_CAP_PX x gpu scale^2) */

    /* GS renderer: NULL = the software GS rasterizes (docs/GPU.md) */
    struct gpu_renderer *gpu;
    int gpu_scale;
    int gpu_scale_forced;      /* cfg.gpu_scale or $RG_GPU_SCALE: graphics.internal_res ignored */
    /* graphics settings (docs/GPU.md "Graphics settings"), from cfg.settings */
    uint64_t gfx_gen;          /* rg_settings_generation applied */
    int gfx_applied;
#ifdef RG_HAVE_GPU
    gpu_gfx gfx;
#endif
    int frame_cap_fps;         /* display.frame_rate: presentation cap (0: none) */
    double last_present_ms;
    /* $RG_GS_DUMP_DIR + $RG_GS_DUMP_FIELDS: display / local memory dumps at
     * the end of the listed fields (docs/GPU.md "Real game validation") */
    char dump_dir[512];
    uint64_t dump_fields[64];
    int ndump;
    /* $RG_FIELD_TIMES: wall time of every field (EE + host half), TSV */
    FILE *field_times;
    double field_t0;
    double field_step_ms;      /* this field's ps2k_step (EE, VU, VIF, GS, GPU submit) */
    double field_read_ms;      /* ... the display read-back for presentation */
    double field_present_ms;   /* ... rg_host_present */
    double field_gswait0;      /* gs_async_wait_ms at the field's start */
    double field_pace_ms;      /* ... paced mode: sleeping until host time owes the phase */
    double field_sync_ms;      /* ... host_half: draining the GS worker before presenting */
    double field_pump_ms;      /* ... rg_host_pump (window events, hot-plug, overlay) */
    double field_audio_ms;     /* ... reading the audio engine and queueing it to the device */
    double field_post_ms;      /* ... host_half after the audio (display, present queueing, hashes) */
    double field_out_ms;       /* ... between the previous field's end and this field's start (the caller) */
    double field_end_ms;       /* wall_ms at the previous field's end */
    /* $RG_FIELD_STATS: per-field counter deltas (docs/PERF-3D.md "Transition stutter") */
    FILE *field_stats;
    double fstats_t0;
    uint64_t fs_presents, fs_newimg; /* presents; ... of a new image (the game drew since the last) */
    uint64_t fs_gsq_at_present;
    int no_shared;             /* zero-copy presentation unavailable (or $RG_PRESENT_COPY=1) */
    int vk_present;            /* the window's renderer runs on the Vulkan backend's device */
    /* Overlap of the main thread and the GS worker (docs/NATIVE-RENDER.md
     * "Overlap"; $RG_GS_OVERLAP=0 turns it off): a field's end does not drain
     * the worker; it waits only until the worker has finished the previous
     * field, and the frame is composed on the worker (gs_async_call) and
     * presented one field later.  Fields that read the renderer on this
     * thread (hash, dumps, shots, census, recording, copy presentation)
     * drain as before. */
    int overlap;
    uint64_t ov_mark;          /* the worker's stream position at the previous field's end */
    uint64_t ov_fields, ov_synced;
    /* $RG_PERF_CENSUS=DIR:a-b[,c-d...]: GS feature and VU microprogram
     * census per field range (docs/PERF-3D.md, tools/perf3d) */
    char census_dir[400];
    uint64_t census_r[16][2];
    int ncensus;
    uint64_t shot_field;       /* $RG_WINDOW_SHOT */
    char shot_path[512];
    /* interpolated presentation (display.interpolation, docs/NATIVE-RENDER.md "Interpolated
     * presentation"): presents made from a pass; headless measurement: $RG_INTERP_SIM=hz (a
     * simulated present clock after every field), $RG_INTERP_SIM_SNAP=1 (the same clock without
     * passes: the control), $RG_INTERP_DUMP=dir + $RG_INTERP_DUMP_FIELDS=a-b (PNG per present),
     * $RG_INTERP_CHECK=1 (an exact pass per field: is the frame self-contained) */
    uint64_t ip_presents, ip_between;
    double ip_sim_hz;
    int ip_sim_snap, ip_check;
    char ip_dump[512];
    uint64_t ip_dump_a, ip_dump_b;
    uint64_t ip_sim_n, ip_sim_changed, ip_sim_passes, ip_check_same, ip_check_differ, ip_seq;
    uint64_t ip_last_hash;
    /* $RG_GS_REC=path + $RG_GS_REC_FIELDS=first-last: GS input recording */
    FILE *rec;
    char rec_path[512];
    uint64_t rec_first, rec_last;

    /* $RG_AUDIO_WAV: every frame handed to the host, as a 48 kHz s16 stereo WAV,
     * plus <path>.fields.tsv (field, kernel vblank, frames written so far) */
    FILE *wav, *wav_fields;
    uint64_t wav_frames;

    /* re-anchors of both pacers already passed to the host audio regulator */
    uint64_t resyncs_seen;
    /* $RG_AUDIO_LOG: one TSV row per field of host-side audio / pacing
     * measurements (docs/SOUND.md "Load-screen audio"); wall clock only,
     * nothing feeds back into the run */
    FILE *alog;
    double alog_t0, alog_present_ms;
    uint64_t alog_slept_ns;
    uint32_t alog_q0;
    rg_audio_stats alog_st;
    cdvd_io_stats alog_io;
    gpu_stats alog_gpu;

} R;

/* ---------------------------------------------------------------- hash */
static void fold(uint64_t *h, const void *p, size_t n)
{
    const uint8_t *b = (const uint8_t *)p;
    for (size_t i = 0; i < n; i++) {
        *h ^= b[i];
        *h *= 0x100000001b3ull;
    }
}
static void fold64(uint64_t v) { fold(&R.st.run_hash, &v, sizeof v); }

/* RG_HASH_LOG=path: one row per field with the run hash and its parts (pad reads, audio,
 * display folds tracked apart), the kernel trace hash and the clock: which part of a run
 * hash difference is game-visible (docs/NATIVE-RENDER.md "Run hash"). Diagnostic only. */
static FILE *g_hash_log;
static uint64_t g_hpart[3] = {0xcbf29ce484222325ull, 0xcbf29ce484222325ull, 0xcbf29ce484222325ull};
static void fold_part(int i, uint64_t *h, const void *p, size_t n)
{
    fold(h, p, n);
    if (g_hash_log)
        fold(&g_hpart[i], p, n);
}

static void say(const char *fmt, const char *a)
{
    if (!R.cfg.quiet) {
        fprintf(stderr, fmt, a);
        fflush(stderr);
    }
}

/* ---------------------------------------------------------------- pacing
 * docs/NATIVE-THREADS.md "Paced mode".  Two cadences:
 *   retail (the Original preset; every run without a host clock: --headless, --unthrottled,
 *          tests, traces, save states): one VBlank phase per run_field, one present per
 *          phase; with throttle on, the kernel's idle jumps sleep to wall time (rg_pacer).
 *   host   (display.pacing = host, or RG_PACE=host): run_field waits until host time owes a
 *          phase (rg_pace: bounded fixed-step accumulator), the phase itself runs flat out
 *          (no idle-jump sleeps), and host_half presents only when no further phase is owed
 *          and the frame cap allows (0..k phases per present; between-phase presents are the
 *          renderer lane's interpolation, rg_pace_between: none yet).
 * The game sees neither: its state is a function of the inputs per phase. */
static uint64_t pace_now(void) { return R.pacer.now_ns(R.pacer.clock_user); }
#if RT_IP
static int ip_present(double tau);
#endif

static void pace_kernel_hook(uint64_t from, uint64_t to, void *user)
{
    if (R.pace.cfg.mode == RG_PACE_RETAIL)
        rg_pacer_hook(from, to, user);
}

static const int k_pace_caps[] = { 0, 30, 60, 120, 144, 0 }; /* display.frame_rate order */

static void pace_update(void)
{
    rg_settings *s = R.cfg.settings;
    if (R.pace_applied && (!s || rg_settings_generation(s) == R.pace_gen))
        return;
    int first = !R.pace_applied;
    R.pace_applied = 1;
    R.pace_gen = s ? rg_settings_generation(s) : 0;
    rg_pace_config c;
    rg_pace_default_config(&c);
    if (s && rg_settings_find(s, "display.pacing") >= 0 && rg_settings_get_enum(s, "display.pacing") == 1)
        c.mode = RG_PACE_HOST;
    const char *e = getenv("RG_PACE");
    if (e && *e)
        c.mode = !strcmp(e, "host") ? RG_PACE_HOST : RG_PACE_RETAIL;
    if (!R.cfg.throttle || R.cfg.headless)
        c.mode = RG_PACE_RETAIL; /* no host clock: the deterministic cadence */
    if (s && rg_settings_find(s, "display.frame_rate") >= 0) {
        int v = rg_settings_get_enum(s, "display.frame_rate");
        if (v >= 0 && v < (int)(sizeof k_pace_caps / sizeof k_pace_caps[0]))
            c.cap_fps = (uint32_t)k_pace_caps[v];
    }
    if (s && rg_settings_find(s, "display.vsync") >= 0)
        c.vsync = rg_settings_get_bool(s, "display.vsync");
#if RT_IP
    /* display.interpolation (or $RG_INTERP): presents interpolated between game frames */
    nr_ip_configure(s && rg_settings_find(s, "display.interpolation") >= 0 && rg_settings_get_bool(s, "display.interpolation"));
#endif
    e = getenv("RG_PACE_MAX_TICKS");
    if (e && *e)
        c.max_ticks = (uint32_t)strtoul(e, NULL, 0);
    e = getenv("RG_PACE_CAP");
    if (e && *e)
        c.cap_fps = (uint32_t)strtoul(e, NULL, 0);
    e = getenv("RG_PACE_CATCHUP"); /* phases owed before presents are skipped (rg_pace.h) */
    if (e && *e)
        c.catchup = (uint32_t)strtoul(e, NULL, 0);
    e = getenv("RG_PACE_COST_AT_DECISION"); /* control: phase cost without the GS worker wait */
    c.cost_at_decision = e && e[0] == '1';
    if (!first && c.mode != R.pace.cfg.mode)
        rg_pacer_reset(&R.pacer); /* re-anchor the idle-jump pacer */
    if ((first || c.mode != R.pace.cfg.mode || c.cap_fps != R.pace.cfg.cap_fps || c.vsync != R.pace.cfg.vsync) &&
        !R.cfg.quiet && R.cfg.throttle && !R.cfg.headless)
        fprintf(stderr, "rg_runtime: pacing %s (frame cap %u, vsync %s, up to %u phases per present)\n",
                c.mode == RG_PACE_HOST ? "host clock" : "retail", c.cap_fps, c.vsync ? "on" : "off",
                c.max_ticks);
    rg_pace_configure(&R.pace, &c);
}

/* host mode: wait until host time owes the next VBlank phase */
static void pace_before_field(void)
{
    pace_update();
    if (R.pace.cfg.mode == RG_PACE_HOST) {
        for (;;) {
            uint64_t now = pace_now();
            uint64_t w = rg_pace_until_tick(&R.pace, now);
            if (!w)
                break;
            /* N presents per phase: interpolated presentation shows a new image between phases
             * when rg_pace_between says its slot came, then sleeps rg_pace_sleep_ns(.., between) */
            int between = 0;
#if RT_IP
            if (nr_ip_on() && R.cfg.present && !R.cfg.headless) {
                uint32_t a16 = 0;
                between = 1;
                if (rg_pace_between(&R.pace, now, &a16)) {
                    if (ip_present((double)R.pace.ticks + (double)a16 / 65536.0)) {
                        R.ip_between++;
                        rg_pace_presented(&R.pace, pace_now());
                        continue;
                    }
                    between = 0;   /* nothing to interpolate yet: wait for the phase */
                }
            }
#endif
            uint64_t sl = rg_pace_sleep_ns(&R.pace, w, now, between);
            R.pace.waits++;
            R.pace.slept_ns += sl;
            R.pacer.sleep_ns(R.pacer.clock_user, sl);
        }
    }
    if (!R.pace.t0_ns)
        R.pace.t0_ns = pace_now(); /* statistics only (retail: the report's wall time) */
    rg_pace_take_tick(&R.pace);
#if RT_IP
    nr_ip_tick(R.pace.ticks); /* the phase clock of the frame starts (interpolation weights) */
#endif
}

static void pace_log_row(int force)
{
    if (!R.pace_log || !R.pace.t0_ns)
        return;
    uint64_t sec = (pace_now() - R.pace.t0_ns) / 1000000000ull;
    if (!force && sec == R.pace_sec)
        return;
    uint64_t lt = rg_frame_logic_ticks();
    fprintf(R.pace_log, "%llu\t%llu\t%llu\t%llu\t%llu\n", (unsigned long long)R.pace_sec,
            (unsigned long long)(R.pace.ticks - R.pace_row_ticks),
            (unsigned long long)(R.pace.presents - R.pace_row_presents), (unsigned long long)(lt - R.pace_row_logic),
            (unsigned long long)R.pace.resyncs);
    fflush(R.pace_log);
    R.pace_sec = sec;
    R.pace_row_ticks = R.pace.ticks;
    R.pace_row_presents = R.pace.presents;
    R.pace_row_logic = lt;
}

/* $RG_PACE_LOG (1 or a path): one summary line at shutdown */
static void pace_report(void)
{
    const rg_pace *p = &R.pace;
    if (!getenv("RG_PACE_LOG"))
        return;
    pace_log_row(1);
    double wall = p->t0_ns ? (double)(pace_now() - p->t0_ns) / 1e9 : 0.0;
    uint64_t lt = rg_frame_logic_ticks();
    fprintf(stderr,
            "rg_pace: mode=%s cap=%u vsync=%d k=%u wall=%.2fs phases=%llu (%.3f/s) logic_ticks=%llu (%.3f/s) "
            "presents=%llu (%.3f/s) between=%llu waits=%llu slept=%.2fs resyncs=%llu dropped=%llu forced=%llu "
            "catchup=%u slow_presents=%llu phase_cost=%.1fms phases/present:",
            p->cfg.mode == RG_PACE_HOST ? "host" : "retail", p->cfg.cap_fps, p->cfg.vsync, p->cfg.max_ticks, wall,
            (unsigned long long)p->ticks, wall > 0 ? p->ticks / wall : 0.0, (unsigned long long)lt,
            wall > 0 ? lt / wall : 0.0, (unsigned long long)p->presents, wall > 0 ? p->presents / wall : 0.0,
            (unsigned long long)p->between_presents, (unsigned long long)p->waits, p->slept_ns / 1e9,
            (unsigned long long)p->resyncs, (unsigned long long)p->dropped_ticks, (unsigned long long)p->forced,
            p->cfg.catchup, (unsigned long long)p->skipped_slow, p->cost_ns / 1e6);
    for (int i = 0; i < RG_PACE_HIST; i++)
        if (p->hist[i])
            fprintf(stderr, " %d%s:%llu", i, i == RG_PACE_HIST - 1 ? "+" : "", (unsigned long long)p->hist[i]);
    fprintf(stderr, "\n");
}

/* ---------------------------------------------------------------- config */
void rg_runtime_default_config(rg_runtime_config *c)
{
    memset(c, 0, sizeof *c);
    c->throttle = 1;
    c->audio = 1;
    c->present = 1;
    c->scale = RG_SCALE_LINEAR;
    c->title = "Rogue Galaxy";
    c->main_priority = 1;
    c->vblank_start_line = 240;
    c->host_stack_size = 1u << 20;
    c->gpu = -1;
    c->gpu_scale = 0;
    c->cdvd_model = -1;
}

void rg_runtime_config_from_settings(rg_runtime_config *c, struct rg_settings *s)
{
    c->settings = s;
    if (!s)
        return;
    if (rg_settings_find(s, "system.throttle") >= 0)
        c->throttle = rg_settings_get_bool(s, "system.throttle");
    if (rg_settings_find(s, "audio.enabled") >= 0)
        c->audio = rg_settings_get_bool(s, "audio.enabled");
    if (rg_settings_find(s, "display.window_mode") >= 0)
        c->fullscreen = rg_settings_get_enum(s, "display.window_mode") != 0;
    if (rg_settings_find(s, "display.scale") >= 0)
        c->scale = rg_settings_get_enum(s, "display.scale");
}

static const char *k_step_names[RG_INIT_COUNT] = {
    "?", "host", "kernel", "graphics", "hwbus", "cdvd", "cards", "iop", "observers", "game-ram",
};

const char *rg_runtime_init_step_name(int step)
{
    return step > 0 && step < RG_INIT_COUNT ? k_step_names[step] : "?";
}

int rg_runtime_init_order(int *out, int cap)
{
    int n = R.norder < cap ? R.norder : cap;
    for (int i = 0; i < n; i++)
        out[i] = R.order[i];
    return R.norder;
}

static void step_done(int s)
{
    if (R.norder < RG_INIT_COUNT)
        R.order[R.norder++] = s;
}

#if RG_IOP_ORACLE /* RG_NATIVE_ONLY: no CDVD model, no IOP HLE (docs/NATIVE-ONLY.md) */
/* ---------------------------------------------------------------- CDVD glue
 * The drive keeps virtual microseconds; the kernel keeps bus cycles
 * (147.456 per us).  A due time converts UP so that the poll at that cycle
 * converts back to at least the due microsecond. */
static uint64_t us_to_cycles_ceil(uint64_t us) { return (us * 147456u + 999u) / 1000u; }
static uint64_t cycles_to_us_floor(uint64_t c) { return c * 1000u / 147456u; }

static int cdvd_dev_next(void *user, uint64_t *due)
{
    (void)user;
    uint64_t us;
    if (!cdvd_next_event(&us))
        return 0;
    *due = us_to_cycles_ceil(us);
    return 1;
}

static void cdvd_dev_poll(void *user, uint64_t now)
{
    (void)user;
    int busy = cdvd_drive_busy();
    cdvd_poll(cycles_to_us_floor(now)); /* also keeps the drive's clock at the kernel's */
    if (busy) {
        R.st.cdvd_polls++;
        if (!cdvd_drive_busy())
            R.st.cdvd_completions++;
    }
}

/* sceCdSync(0) -> cdvd_drive_wait -> here: block the EE thread on a
 * kernel-private timed wait (no sema id); the kernel's device poll at the due
 * cycle completes the command before the thread runs again.  Outside a guest
 * thread (host setup) the drive's own clock jumps, as without a kernel. */
static void cdvd_wait_hook(void *ctx, uint64_t due_us)
{
    (void)ctx;
    R.st.cdvd_waits++;
    if (ps2k_get_thread_id() > 0 && !ps2k_in_handler() &&
        ps2k_wait_until(us_to_cycles_ceil(due_us)) == 0)
        return;
    cdvd_poll(due_us);
}
#endif /* RG_IOP_ORACLE */

/* ---------------------------------------------------------------- pad glue */
static int pad_source(void *user, int port, uint64_t vblank, rg_pad_report *out)
{
    (void)user;
    rg_pad p;
    uint32_t vbl = R.cfg.game_vblank ? R.cfg.game_vblank(R.cfg.game_vblank_user, vblank) : (uint32_t)vblank;
    rg_host_read_pad(R.host, port, vbl, &p);
    memset(out, 0, sizeof *out);
    if (port == 0)
        out->connected = 1;
    else
        out->connected = rg_host_port_connected(R.host, 1) ? 1 : 0; /* live 2-player only */
    out->has_pressure = 1;
    out->buttons = p.buttons;
    out->lx = p.lx;
    out->ly = p.ly;
    out->rx = p.rx;
    out->ry = p.ry;
    for (int i = 0; i < RG_PAD_P_COUNT && i < RG_PRS_COUNT; i++)
        out->pressure[i] = p.pressure[i]; /* same byte order (DS2 bytes 8..19) */
    R.st.pad_reads++;
    uint32_t rec[3] = {(uint32_t)port, vbl, p.buttons};
    fold_part(0, &R.st.run_hash, rec, sizeof rec);
    return 1;
}

static void pad_rumble(void *user, int port, uint8_t small, uint8_t large)
{
    (void)user;
    R.st.rumble_changes++;
    rg_host_rumble(R.host, port, small, large);
}

/* ---------------------------------------------------------------- IOP glue */
#if RG_IOP_ORACLE
/* iop_hle_install's post-install: the real pad, card and sound servers replace
 * the placeholders at boot (and after every rg_sif_boot), not at first Init. */
static void iop_post_install(void *user)
{
    (void)user;
    padman_install();
    mcserv_install();
    snd_config sc;
    snd_default_config(&sc);
    sc.quiet = R.cfg.quiet;
    snd_install(&sc);
}
#endif

/* ---------------------------------------------------------------- observers */
/* Model-side work at the exact virtual time of the VBlank edge (it may run on
 * a guest fiber: no kernel calls).  The host half (events, audio push,
 * present) runs after the field in rg_runtime_run_field. */
static void on_vblank(int which, uint64_t field, void *user)
{
    (void)user;
    (void)field;
    if (which == PS2K_VBLANK_START) {
        R.st.vblank_start++;
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        nr_hw_vsync();                    /* CSR.FIELD toggle + VSINT (native state block) */
#else
        gs_vsync(R.gs);                   /* CSR.FIELD toggle + VSINT */
#endif
        if (rg_iop_native()) {
            rg_npad_update(ps2k_vblank_count()); /* the native pad's per-VBlank step */
        } else {
#if RG_IOP_ORACLE
            padman_update(ps2k_vblank_count()); /* padman's per-frame DMA buffer write */
            snd_sync();                       /* render audio up to this VBlank */
#endif
        }
#ifdef RG_HAVE_NATIVE_AUDIO
        rg_audio_runtime_sync();          /* the native engine, to the same frame */
#endif
    } else {
        R.st.vblank_end++;
    }
}

/* ---------------------------------------------------------------- init */
static const char *pick(const char *v, const char *env, const char *def, char *buf, size_t cap)
{
    const char *s = v ? v : getenv(env);
    if (!s || !*s)
        s = def;
    snprintf(buf, cap, "%s", s);
    return buf;
}

#if RG_IOP_ORACLE /* (only the CDVD mount uses it) */
static int file_exists(const char *dir, const char *name)
{
    char p[600];
    snprintf(p, sizeof p, "%s/%s", dir, name);
    FILE *f = fopen(p, "rb");
    if (!f)
        return 0;
    fclose(f);
    return 1;
}
#endif

static void run_service_hooks(void);
static void gpu_choose(void);
static void gpu_start(void);
static void gfx_update(void);
#ifdef RG_HAVE_NATIVE_RENDER
#if RG_NATIVE_ONLY
/* the GS model's SIGNAL / FINISH events (what dmac_attach_gs wired in the oracle) */
static void gs_irq_kernel(void *user, uint32_t ev)
{
    (void)user; (void)ev;
    ps2k_raise_intc(PS2K_INTC_GS);
}
#endif
#if RG_NATIVE_ONLY
#define RG_NR_VU_DEFAULT 2
#else
#define RG_NR_VU_DEFAULT 1
#endif
#if !RG_NATIVE_ONLY
/* VU work of a walked chain (UNPACK / MPG / VIF registers / a still-emulated VU program):
 * to the VIF1 model (oracle builds; RG_NR_VU=model), so VU memory stays what the oracle path
 * makes it */
static void vif1_fwd(void *user, const uint8_t *d, uint32_t bytes)
{
    (void)user;
    vif_write(&R.vif1, (const uint32_t *)(const void *)d, bytes / 4);
}
/* RG_NR_VU=check: the native consumer first (its packets queued), then the models */
static void vif1_fwd_check(void *user, const uint8_t *d, uint32_t bytes)
{
    nr_vux_cmd(d, bytes);
    vif1_fwd(user, d, bytes);
}
#endif
/* the native VU1 consumer's XGKICK packets: GS PATH1, as VU1's were */
static void vux_path1(void *user, const uint8_t *d, uint32_t bytes)
{
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    nr_gs_gif_path1(user, d, bytes);   /* the native GIF input */
#else
    gs_vu1_gif_sink(user, d, bytes, 0);
#endif
}
/* libdma's channel-1 hook: the walker feeds the GS input VIF1's DIRECT would have fed */
static int vif1_chain(uint32_t tadr, int tte, rg_vif1_chain_res *r)
{
    nr_fx_out o;
    memset(&o, 0, sizeof o);
    /* RG_NR_VU=0: VU work dropped here too (checks that nothing needs it); RG_NR_VU=native:
     * to the native VU1 consumer (nr_vux.c: VU memory + translated programs, no VIF / VU
     * models; docs/NATIVE-RENDER.md "VU1 programs at the walker") */
    /* RG_NR_VU: native (native-only builds: the only choice) | model (oracle builds' default:
     * the VIF1 / VU1 models; demos and tests run VU1 programs nr_vux does not know) | check
     * (oracle builds: both, nr_vux's packets compared with VU1's) | 0 (dropped) */
    static int vu = -1;
    static uint32_t cl = 4, wl = 4;   /* the VIF's cycle registers carry over between chains */
    if (vu < 0) {
        const char *e = getenv("RG_NR_VU");
        vu = (e && e[0] == '0') ? 0 : (e && e[0] == 'n') ? 2 : (e && e[0] == 'c') ? 3 : (e && e[0] == 'm') ? 1 : RG_NR_VU_DEFAULT;
#if RG_NATIVE_ONLY
        if (vu == 1 || vu == 3) {
            fprintf(stderr, "rg_runtime: RG_NR_VU=%s needs the VIF1 / VU1 models (oracle builds); native\n", e);
            vu = 2;
        }
#else
        if (vu == 3) {   /* both: the models draw, nr_vux's packets are compared with VU1's */
            nr_vux_check_bind((nr_vux_p1_fn)R.vu1.gif_sink, R.vu1.gif_user);
            R.vu1.gif_sink = (vu_gif_sink_fn)nr_vux_p1_tap;
        }
#endif
        if (vu == 2) nr_vux_bind(vux_path1, R.gs);
    }
    o.cl = cl;
    o.wl = wl;
#if RG_NATIVE_ONLY
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    if (nr_fx_walk(tadr, tte, nr_gs_gif_path2, NULL, vu == 2 ? nr_vux_fwd : NULL, NULL, &o) != 0)
        return -1;
#else
    if (nr_fx_walk(tadr, tte, gs_vif1_gif_sink, R.gs, vu == 2 ? nr_vux_fwd : NULL, NULL, &o) != 0)
        return -1;
#endif
#else
    if (nr_fx_walk(tadr, tte, R.vif1.gif_sink, R.vif1.gif_user,
                   vu == 2 ? nr_vux_fwd : vu == 3 ? vif1_fwd_check : vu ? vif1_fwd : NULL, NULL, &o) != 0)
        return -1;
#endif
    cl = o.cl;
    wl = o.wl;
    r->tags = o.tags;
    r->qwords = o.qwords;
    r->last_tag = o.last_tag;
    r->tadr = o.tadr;
    r->madr = o.madr;
    r->irq = o.irq;
    return 0;
}
#endif

static void gpu_stop(void);
static void dump_field(void);
static void rec_field_start(void);
static void rec_field_end(void);
static double wall_ms(void);
static int read_display(uint32_t *w, uint32_t *h);
/* $RG_PRESENT_LOG: the wall time a present returned, its kind (0 read-back copy, 1 zero-copy,
 * 2 zero-copy composed on the worker (overlap), 3 interpolated), the field and the ms the present
 * took on this thread (from present_start: pass + compose + the window's present) and of it the
 * window's present (interpolated presents: rg_host_present_shared; the rest is the GS worker
 * running the pass behind whatever it had queued, and the compose) */
static double g_present_t0, g_present_tw;   /* (tw: the window's present began) */
static void present_start(void) { if (R.present_log) { g_present_t0 = wall_ms(); g_present_tw = 0.0; } }
static void present_mark(int kind)
{
    if (!R.present_log) return;
    double t = wall_ms();
    fprintf(R.present_log, "%.3f\t%d\t%llu\t%.3f\t%.3f\n", t - R.present_log_t0, kind, (unsigned long long)R.st.fields,
            g_present_t0 > 0.0 ? t - g_present_t0 : 0.0, g_present_tw > 0.0 ? t - g_present_tw : 0.0);
    g_present_t0 = 0.0;
}
static void wav_open(void);
static void wav_close(void);

int rg_runtime_init(const rg_runtime_config *cfg)
{
    if (R.inited)
        return -1;
    memset(&R, 0, sizeof R);
    if (cfg)
        R.cfg = *cfg;
    else
        rg_runtime_default_config(&R.cfg);
    if (R.cfg.headless)
        R.cfg.throttle = 0;
    pick(R.cfg.data_dir, "RG_DATA", "data", R.data_dir, sizeof R.data_dir);
    pick(R.cfg.saves_dir, "RG_SAVES", "saves", R.saves_dir, sizeof R.saves_dir);
    gpu_choose();
    R.audio = (int16_t *)malloc(AUDIO_CAP_FRAMES * 2 * sizeof(int16_t));
    R.frame_cap = DISPLAY_CAP_PX * (uint32_t)(R.cfg.gpu ? R.gpu_scale * R.gpu_scale : 1);
    R.frame = (uint32_t *)malloc((size_t)R.frame_cap * sizeof(uint32_t));
    if (!R.audio || !R.frame)
        goto fail;
    R.st.run_hash = 0xcbf29ce484222325ull;
    {
        const char *hl = getenv("RG_HASH_LOG");
        if (hl && *hl && (g_hash_log = fopen(hl, "w")) != NULL)
            fputs("field\trun_hash\tpad\taudio\tdisplay\tktrace\tktrace_n\tnow\n", g_hash_log);
    }
    wav_open();

    /* The game RAM block first (step 9 only binds it): it must end below
     * 0x10000000 (below), and a windowed host creates the SDL window and its
     * D3D11 renderer, whose display-driver DLLs and heaps fragment the low
     * address space: with the block allocated at step 9 a windowed GPU run
     * got 0x1CFCB000 and faulted on the first 28-bit masked address. */
    if (rg_crt0_init() != 0)
        goto fail;

    /* 1. host shell */
    {
        rg_host_config hc;
        rg_host_config_default(&hc);
        if (R.cfg.settings)
            rg_host_config_from_settings(&hc, R.cfg.settings); /* window size, vsync, ... */
        hc.title = R.cfg.title;
        hc.headless = R.cfg.headless;
        hc.audio = R.cfg.audio;
        hc.fullscreen = R.cfg.fullscreen;
        hc.scale = (rg_scale_mode)R.cfg.scale;
        R.host = rg_host_create(&hc);
        if (!R.host) {
            fprintf(stderr, "rg_runtime: host: %s\n", rg_host_last_error());
            goto fail;
        }
        if (R.cfg.input_script) {
            char err[256];
            if (rg_input_script_load(&R.script, R.cfg.input_script, err, sizeof err) != 0) {
                fprintf(stderr, "rg_runtime: input script: %s\n", err);
                goto fail;
            }
            R.have_script = 1;
            rg_host_set_input_script(R.host, &R.script);
        }
        if (R.cfg.settings) {
            /* cfg fields set after rg_runtime_config_from_settings win */
            rg_host_settings_from_config(R.cfg.settings, &hc);
            rg_host_attach_settings(R.host, R.cfg.settings, R.cfg.settings_path);
        }
        rg_pacer_init(&R.pacer, R.cfg.throttle);
        rg_pace_init(&R.pace, NULL);
        {
            const char *pl = getenv("RG_PACE_LOG");
            if (pl && *pl && strcmp(pl, "1")) {
                R.pace_log = fopen(pl, "w");
                if (R.pace_log)
                    fprintf(R.pace_log, "#sec\tphases\tpresents\tlogic_ticks\tresyncs\n");
            }
            const char *pr = getenv("RG_PRESENT_LOG");
            if (pr && *pr) {
                R.present_log = fopen(pr, "w");
                if (R.present_log) {
                    R.present_log_t0 = wall_ms();
                    fprintf(R.present_log, "#ms\tkind\tfield\tpresent_ms\twindow_ms\n");
                }
            }
        }
        step_done(RG_INIT_HOST);
    }

    /* 2. EE kernel */
    {
        ps2k_config kc;
        ps2k_default_config(&kc);
        kc.vblank_start_line = R.cfg.vblank_start_line ? R.cfg.vblank_start_line : 240;
        kc.stop_at_cycles = R.cfg.stop_at_cycles;
        kc.stall_cycles = R.cfg.stall_cycles;
        kc.kcall_cycles = R.cfg.kcall_cycles;
        /* RG_THREADS=native (docs/NATIVE-THREADS.md "Slice 5"): the frame-driven kernel; it
         * needs the native sound path (its threads are driven steps there) */
#ifdef RG_HAVE_NATIVE_AUDIO
        if (rg_threads_mode() == RG_THREADS_NATIVE && rg_audio_mode() != RG_AUDIO_NATIVE)
            rg_threads_force_mode(RG_THREADS_FRAME, "the frame-driven kernel needs RG_AUDIO=native");
#else
        if (rg_threads_mode() == RG_THREADS_NATIVE)
            rg_threads_force_mode(RG_THREADS_FRAME, "the frame-driven kernel needs the native audio build");
#endif
        kc.native = rg_threads_mode() == RG_THREADS_NATIVE;
        if (R.cfg.host_stack_size)
            kc.host_stack_size = R.cfg.host_stack_size;
        if (ps2k_init(&kc) != 0) {
            fprintf(stderr, "rg_runtime: ps2k_init failed (kernel still running?)\n");
            goto fail;
        }
        step_done(RG_INIT_KERNEL);
    }

    /* 3. graphics: GS, VU0/VU1, VIF0/VIF1, DMAC and their sinks (DMAC.md "Wiring") */
#if RG_NATIVE_ONLY
    /* native-only: no DMAC model (docs/NATIVE-RENDER.md "DMA without the DMAC"): libdma
     * moves the game's sends itself (libdma_native.c) and the frame chain goes through the
     * walker.  VU1 / VIF1 stay as the executor of the VU1 programs that are not native yet
     * (the main route has none; the INSECT overlay's do), fed by the walker's forward sink.
     * No VIF0 / VU0 model (VU0 is plain C).  The GS raises SIGNAL / FINISH on the kernel. */
    {
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        /* no GS model (docs/NATIVE-RENDER.md "Checkpoint 10"): the native state block (saved in
         * the runtime's blob), the privileged registers on it (nr_hw.c), the
         * GIF input and the worker natively; local memory is the device's */
        R.gs = (rt_gs *)calloc(1, sizeof *R.gs);
        if (!R.gs)
            goto fail;
        nr_gs_init(R.gs);
        nr_hw_bind_gs(R.gs, gs_irq_kernel, NULL);
        /* (host memory: the runtime's save-state blob carries the state block and this image of
         * the device's local memory, rg_runtime_ss_pre_save / _save / _load / _post_load) */
        R.gs_img = (uint8_t *)malloc(GS_VRAM_BYTES);
        if (!R.gs_img)
            goto fail;
        sce_graphics_bind(NULL, NULL);
#else
        R.gs = gs_create();
        if (!R.gs)
            goto fail;
        R.gs->irq = gs_irq_kernel;
        R.gs->irq_user = NULL;
        /* no VIF1 / VU1 either (docs/NATIVE-RENDER.md "VU1 programs at the walker"): the walker
         * feeds the GS directly and hands VU work to nr_vux.c */
        sce_graphics_bind(NULL, R.gs);
#ifdef RG_HAVE_NATIVE_RENDER
        nr_hw_bind(R.gs, NULL);
#endif
#endif
        step_done(RG_INIT_GRAPHICS);
    }
#else
    {
        R.gs = gs_create();
        R.dmac = dmac_create();
        if (!R.gs || !R.dmac)
            goto fail;
        vu_init(&R.vu1, 1);
        vu_init(&R.vu0, 0);
        R.vu0.vu1 = &R.vu1;
#if RG_VU0_MICRO_BIND
        rg_vu0_micro_bind(&R.vu0);       /* vcallms: VU0 micro mode on the rg_vu0 registers */
#endif
        vif_init(&R.vif0, 0, &R.vu0);
        vif_init(&R.vif1, 1, &R.vu1);
        R.vu1.gif_sink = gs_vu1_gif_sink;   /* PATH1: XGKICK */
        R.vu1.gif_user = R.gs;
        R.vif1.gif_sink = gs_vif1_gif_sink; /* PATH2: DIRECT/DIRECTHL */
        R.vif1.gif_user = R.gs;
#ifdef RG_HAVE_NATIVE_RENDER
        nr_runtime_attach_vif(&R.vif1, &R.vu1);   /* RG_RENDER=native only */
#endif
        dmac_attach_vif(R.dmac, 0, &R.vif0);
        dmac_attach_vif(R.dmac, 1, &R.vif1);
        dmac_attach_gs(R.dmac, R.gs);       /* PATH3 + VIF1 readback; GS irq -> INTC GS */
        /* SIF0/1/2: the SIF HLE moves data itself (sceSifSetDma, SIF0 events),
         * so the DMAC SIF channels stay unbound.
         * TODO(movie): the movie service binds fromIPU/toIPU here with
         * dmac_set_in/dmac_set_out (via rg_runtime_set_service_hook). */
        sce_graphics_bind(R.dmac, R.gs);
#ifdef RG_HAVE_NATIVE_RENDER
        nr_hw_bind(R.gs, &R.vif1);   /* GS privileged / VIF1_FBRST sites (port/hwaccess.h) */
#endif
        step_done(RG_INIT_GRAPHICS);
    }
#endif

    /* 4. HW_* register bus over every model (DMAC asked before the kernel for D_STAT) */
    {
#if !RG_NATIVE_ONLY
        /* native-only: no bus; the game's remaining register sites (T0, GS privileged,
         * VIF1_FBRST) are routed by port/hwaccess.h (docs/NATIVE-RENDER.md "Hardware
         * register sites") */
        hwbus_init();
        hwbus_bind(R.dmac, R.gs);
#endif
        /* frame-driven kernel: a flow's own work costs no logic time (nominal profile):
         * no modelled DMA / register-read costs (docs/NATIVE-THREADS.md "Slice 5") */
#if !RG_NATIVE_ONLY
        if (ps2k_native()) {
            R.dmac->cycles_per_qword = 0;
            hwbus_set_read_cycles(0);
        }
#endif
        /* TODO(movie): hwbus_set_ipu(&ipu_hooks) once src/movie provides the IPU service.
         * TODO(overlay): the overlay manager installs hwbus_set_ovl_resolver. */
        step_done(RG_INIT_HWBUS);
    }

    /* 5. files: the native file service over data/ (docs/NATIVE-FS.md); the CDVD
     *    sector model only for libcdvd callers (cfg.cdvd_model) */
    {
        int nf = rg_fs_mount(R.data_dir);
        const char *ev;
        if (nf < 0)
            say("rg_runtime: no files in %s (run rg-extract)\n", R.data_dir);
        else if (!R.cfg.quiet)
            fprintf(stderr, "rg_fs: mounted %s: %d files\n", R.data_dir, nf);
        ev = getenv("RG_FS_ORACLE");
#if RG_IOP_ORACLE
        if (ev && *ev && *ev != '0')
            rg_fs_oracle_start(R.data_dir);
        if (R.cfg.cdvd_model < 0) {
            ev = getenv("RG_CDVD_MODEL");
            R.cfg.cdvd_model = (ev && *ev) ? (*ev != '0') : 1;
        }
#else
        /* native-only build: no sector model to compare with or mount */
        if (ev && *ev && *ev != '0')
            say("rg_runtime: %s\n", "RG_FS_ORACLE ignored: native-only build (no CDVD model)");
        ev = getenv("RG_CDVD_MODEL");
        if (R.cfg.cdvd_model > 0 || (R.cfg.cdvd_model < 0 && ev && *ev && *ev != '0'))
            say("rg_runtime: %s\n", "CDVD model requested but not built (native-only build)");
        R.cfg.cdvd_model = 0;
#endif
    }
#if RG_IOP_ORACLE
    if (R.cfg.cdvd_model) {
        if (file_exists(R.data_dir, "MANIFEST.tsv")) {
            if (!sceCdHleMount(R.data_dir))
                say("rg_runtime: cannot mount %s (tray empty)\n", R.data_dir);
        } else {
            say("rg_runtime: no MANIFEST.tsv in %s: tray empty (run rg-extract)\n", R.data_dir);
        }
        cdvd_drive_set_clock(0); /* the kernel clock restarts at 0 */
        cdvd_drive_set_wait_hook(cdvd_wait_hook, NULL);
        ps2k_device dev = {"cdvd", cdvd_dev_next, cdvd_dev_poll, NULL};
        R.cdvd_dev_id = ps2k_add_device(&dev);
    }
#endif
    step_done(RG_INIT_CDVD);

    /* 6. memory cards, pad model, host input/rumble.  RG_IOP=native (default,
     *    docs/NATIVE-IOP.md): the native pad and save services, no IOP/SIF at all;
     *    hle (the oracle, or forced while a sound path still needs the IOP HLE). */
    {
        int want = rg_iop_requested_mode();
#ifdef RG_HAVE_NATIVE_AUDIO
        if (want == RG_IOP_MODE_NATIVE && rg_audio_hle_needed()) {
            say("rg_runtime: %s\n", "RG_IOP=native needs RG_AUDIO=native (all paths): using the IOP HLE");
            want = RG_IOP_MODE_HLE;
        }
#else
        want = RG_IOP_MODE_HLE;
#endif
        rg_iop_set_mode(want);
        if (!R.cfg.quiet)
            fprintf(stderr, "rg_runtime: IOP %s\n", want == RG_IOP_MODE_NATIVE ? "native (no SIF/IOP)" : "hle");
    }
    {
        mccard_config mc;
        mccard_default_config(&mc);
        mc.root = R.saves_dir;
        mc.clock = (mc_clock_fn)rg_mc_virtual_clock;
        if (mccard_init(&mc) != 0)
            say("rg_runtime: memory cards under %s unavailable\n", R.saves_dir);
        if (rg_iop_native()) {
            rg_npad_config nc;
            rg_npad_default_config(&nc);
            nc.start_analog = R.cfg.start_analog;
            nc.keep_analog_lock = !R.cfg.pad_power_cycle;
            rg_npad_reset(&nc);
        } else {
#if RG_IOP_ORACLE
            padman_config pc;
            padman_default_config(&pc);
            pc.start_analog = R.cfg.start_analog;
            pc.keep_analog_lock = !R.cfg.pad_power_cycle;
            padman_reset(&pc);
#endif
        }
        rg_pad_set_input_source(pad_source, NULL);
        rg_pad_set_rumble_hook(pad_rumble, NULL);
        step_done(RG_INIT_CARDS);
    }

    /* 7. IOP: SIF + IOP RAM + HLE servers (post-install: padman, mcserv, sound).
     *    Native: none of it; fileio's host roots for the native sceOpen. */
    if (rg_iop_native()) {
#ifdef RG_HAVE_NATIVE_AUDIO
        rg_audio_runtime_init(ra_clk_native, ra_clk_hle, ra_clk_hle_origin, NULL);
#endif
        rg_fio_set_roots(R.data_dir, NULL);
        step_done(RG_INIT_IOP);
    } else {
#if RG_IOP_ORACLE
        iop_hle_set_post_install(iop_post_install, NULL);
#ifdef RG_HAVE_NATIVE_AUDIO
        rg_audio_runtime_init(ra_clk_native, ra_clk_hle, ra_clk_hle_origin, NULL);
#endif
        rg_sif_boot_config sb;
        rg_sif_default_boot_config(&sb);
        sb.cdrom_root = R.data_dir;
        sb.host_root = NULL;
        sb.rpc_latency = R.cfg.rpc_latency;
        sb.dma_setup = R.cfg.sif_dma_setup;
        sb.dma_cycles_per_qword = R.cfg.sif_dma_cycles_per_qword;
        sb.boot_latency = R.cfg.iop_boot_latency;
        sb.use_kernel = 1;
        if (rg_sif_boot(&sb) != 0)
            say("rg_runtime: %s\n", "rg_sif_boot reported a server registration failure");
        step_done(RG_INIT_IOP);
#endif
    }

    /* 8. VBlank observers and real-time pacing */
    {
        R.obs_id = ps2k_add_vblank_observer(on_vblank, NULL);
        if (R.cfg.throttle) /* the retail cadence only (paced mode sleeps between phases) */
            ps2k_set_pacing_hook(pace_kernel_hook, &R.pacer);
        step_done(RG_INIT_OBSERVERS);
    }

    /* 9. crt0: the game heap (one host allocation, docs/NATIVE-CPU.md section 8) */
    {
        if (rg_crt0_init() != 0)
            goto fail;
        step_done(RG_INIT_GAME_RAM);
    }

    /* Game pointers are host addresses (i686).  The still-emulated DMA path
     * (renderer lane) keeps 28 bits of DMA addresses in three render overrides, so
     * with RG_HEAP_DMA_PLACEMENT the heap must end below 0x10000000 (docs/GPU.md
     * "Real game validation": with the GPU renderer created first, the D3D11
     * runtime and the display driver pushed it to 0x143A2000 and the first
     * VIF1 chain read a masked address). */
#if RG_HEAP_DMA_PLACEMENT
    {
        const rg_ps2_ram *ram = rg_crt0_ram();
        if (ram && (uintptr_t)ram->heap_end > RG_HEAP_DMA_HI)
            fprintf(stderr, "rg_runtime: warning: game heap at %p ends above 0x10000000; "
                            "28-bit address masks will fault\n", (void *)ram->heap_start);
    }
#endif

    R.inited = 1;
    /* TODO(overlay): call the overlay manager's install (hwbus resolver,
     * MAIN -> 0x4E9E80 call table) from the service hook. */
    run_service_hooks();
    /* The GPU renderer starts last for the same reason: after every
     * allocation the game addresses (RAM block, service buffers). */
    gpu_start();
    /* GS worker thread (docs/PERF-3D.md): GIF input executes beside the EE
     * and VU1; the GS's observable state is unchanged.  $RG_GS_ASYNC=0: off */
    {
        const char *ga = getenv("RG_GS_ASYNC");
        if (!(ga && ga[0] == '0') && gsq_start() == 0 && !R.cfg.quiet)
            fprintf(stderr, "rg_runtime: GS input on a worker thread\n");
    }
    return 0;

fail:
    R.inited = 1; /* let shutdown free what was built */
    rg_runtime_shutdown();
    return -1;
}

int rg_runtime_inited(void) { return R.inited; }

/* Several services (overlay manager, movie service, ...) each register one
 * hook; all run in registration order after init. Registering the same
 * (fn, user) pair twice is a no-op. */
#define RG_MAX_SERVICE_HOOKS 8
static struct { rg_runtime_service_fn fn; void *user; } g_svc[RG_MAX_SERVICE_HOOKS];
static int g_nsvc;

static void run_service_hooks(void)
{
    for (int i = 0; i < g_nsvc; i++)
        g_svc[i].fn(g_svc[i].user);
}

void rg_runtime_set_service_hook(rg_runtime_service_fn after_init, void *user)
{
    if (!after_init)
        return;
    for (int i = 0; i < g_nsvc; i++)
        if (g_svc[i].fn == after_init && g_svc[i].user == user)
            return;
    if (g_nsvc == RG_MAX_SERVICE_HOOKS) {
        say("rg_runtime: %s\n", "too many service hooks (max 8)");
        abort();
    }
    g_svc[g_nsvc].fn = after_init;
    g_svc[g_nsvc].user = user;
    g_nsvc++;
    if (R.inited)
        after_init(user);
}

/* ---------------------------------------------------------------- audio dump */
static void wav_le32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24);
}

/* Writes the 44-byte canonical PCM header for `frames` stereo s16 frames at
 * 48 kHz at the start of f, then returns to the end. */
static void wav_header(FILE *f, uint64_t frames)
{
    uint64_t bytes64 = frames * 4u;
    uint32_t bytes = bytes64 > 0xFFFFFFD3u ? 0xFFFFFFD3u : (uint32_t)bytes64;
    uint8_t h[44];
    memcpy(h, "RIFF", 4); wav_le32(h + 4, 36u + bytes);
    memcpy(h + 8, "WAVEfmt ", 8); wav_le32(h + 16, 16);
    h[20] = 1; h[21] = 0; h[22] = 2; h[23] = 0;         /* PCM, 2 channels (L, R) */
    wav_le32(h + 24, 48000); wav_le32(h + 28, 48000u * 4u);
    h[32] = 4; h[33] = 0; h[34] = 16; h[35] = 0;         /* block align 4, 16 bits */
    memcpy(h + 36, "data", 4); wav_le32(h + 40, bytes);
    fseek(f, 0, SEEK_SET);
    fwrite(h, 1, sizeof h, f);
    fseek(f, 0, SEEK_END);
}

static void wav_open(void)
{
    const char *path = getenv("RG_AUDIO_WAV");
    if (!path || !*path)
        return;
    R.wav = fopen(path, "wb");
    if (!R.wav) {
        fprintf(stderr, "rg_runtime: RG_AUDIO_WAV: cannot create %s\n", path);
        return;
    }
    wav_header(R.wav, 0);
    char p2[600];
    snprintf(p2, sizeof p2, "%s.fields.tsv", path);
    R.wav_fields = fopen(p2, "w");
    if (R.wav_fields)
        fprintf(R.wav_fields, "# field\tkernel_vblank\tgame_vblank\tframes_end\tcycle\n");
}

static void wav_close(void)
{
    if (R.wav) {
        wav_header(R.wav, R.wav_frames);
        fclose(R.wav);
    }
    if (R.wav_fields)
        fclose(R.wav_fields);
    R.wav = R.wav_fields = NULL;
}

/* ---------------------------------------------------------------- GS renderer
 * cfg.gpu / $RG_GPU picks what draws the GS model's primitives: the software
 * rasterizer (src/ps2/gs, the reference) or the Direct3D 11 GPU renderer
 * (src/gpu, hardware or WARP).  The GS model itself (GIF, registers,
 * transfers, CLUT, local memory) is the same either way; only drawing and the
 * PCRTC read-out move to the GPU.  docs/GPU.md "Real game validation". */
/* host wall clock: C11 timespec_get on Windows; POSIX clock_gettime elsewhere (the Linux
 * target builds with -std=gnu99, where glibc hides timespec_get / TIME_UTC: docs/LINUX.md) */
static void rt_wall_ts(struct timespec *ts)
{
#ifdef _WIN32
    timespec_get(ts, TIME_UTC);
#else
    clock_gettime(CLOCK_REALTIME, ts);
#endif
}

static double wall_ms(void)
{
    struct timespec ts;
    rt_wall_ts(&ts);
    return (double)ts.tv_sec * 1e3 + (double)ts.tv_nsec / 1e6;
}

#if RG_IOP_ORACLE /* (the CDVD model's I/O clock) */
static uint64_t alog_now_ns(void)
{
    struct timespec ts;
    rt_wall_ts(&ts);
    return (uint64_t)ts.tv_sec * 1000000000u + (uint64_t)ts.tv_nsec;
}
#endif


/* $RG_AUDIO_LOG row for the field just finished */
static void alog_field(uint32_t frames)
{
    double now = wall_ms();
    rg_audio_stats st;
    cdvd_io_stats io;
    rg_host_audio_stats(R.host, &st);
#if RG_IOP_ORACLE
    cdvd_get_io_stats(&io);
#else
    memset(&io, 0, sizeof io); /* native-only: no CDVD model (cd_* columns 0) */
#endif
    double slept = (double)(R.pacer.slept_ns - R.alog_slept_ns) / 1e6;
    double wall = now - R.alog_t0;
    fprintf(R.alog, "%llu\t%llu\t%.3f\t%.3f\t%.3f\t%.3f\t%llu\t%llu\t%.3f\t%u\t%u\t%u\t%llu\t%llu\t%llu\t%llu\t%.5f\t%llu",
            (unsigned long long)R.st.fields, (unsigned long long)ps2k_vblank_count(), wall, wall - slept,
            slept, R.alog_present_ms, (unsigned long long)(io.reads - R.alog_io.reads),
            (unsigned long long)(io.sectors - R.alog_io.sectors), (double)(io.wall_ns - R.alog_io.wall_ns) / 1e6,
            frames, R.alog_q0, st.queued, (unsigned long long)(st.starves - R.alog_st.starves),
            (unsigned long long)(st.starve_frames - R.alog_st.starve_frames),
            (unsigned long long)(st.pad_frames - R.alog_st.pad_frames),
            (unsigned long long)(st.drop_frames - R.alog_st.drop_frames), st.ratio,
            (unsigned long long)(R.pacer.resyncs + R.pace.resyncs)); /* both pacers' re-anchors */
    gpu_stats g;
    memset(&g, 0, sizeof g);
#ifdef RG_HAVE_GPU
    if (R.gpu)
        g = *gpu_get_stats(R.gpu);
#endif
    fprintf(R.alog, "\t%llu\t%llu\t%llu\t%llu\t%llu\t%llu\t%u\n", (unsigned long long)(g.prims - R.alog_gpu.prims),
            (unsigned long long)(g.batches - R.alog_gpu.batches),
            (unsigned long long)(g.dst_copies - R.alog_gpu.dst_copies),
            (unsigned long long)(g.rt_writebacks - R.alog_gpu.rt_writebacks),
            (unsigned long long)((g.upload_bytes - R.alog_gpu.upload_bytes) >> 10),
            (unsigned long long)((g.download_bytes - R.alog_gpu.download_bytes) >> 10), st.target);
    R.alog_gpu = g;
    if (R.st.fields % 60 == 0)
        fflush(R.alog);
    R.alog_st = st;
    R.alog_io = io;
    R.alog_slept_ns = R.pacer.slept_ns;
    R.alog_t0 = now;
}

static void gpu_choose(void)
{
    if (R.cfg.gpu < 0) {
        const char *e = getenv("RG_GPU");
        R.cfg.gpu = 0;
        if (e && *e && strcmp(e, "0") && strcmp(e, "sw") && strcmp(e, "off"))
            R.cfg.gpu = !strcmp(e, "warp") ? 2 : 1;
#if RG_NATIVE_ONLY && defined(RG_HAVE_GPU) && defined(RG_HAVE_NATIVE_RENDER)
        /* a native-only exe has no DMAC / VIF1 / VU1 models: the frame chain only runs
         * through the native walker, which gpu_start installs with the GPU renderer.
         * Without it every VIF1 send is dropped, the end-of-frame VIF1 interrupt never
         * comes and the game logic stalls on the title (docs/BRINGUP.md 2026-10-22).
         * So the default is the hardware GPU; RG_GPU=0/sw/off still forces software. */
        if (!(e && *e))
            R.cfg.gpu = 1;
        else if (!R.cfg.gpu)
            fprintf(stderr, "rg_runtime: RG_GPU=%s: software GS in a native-only exe; "
                            "the frame chain needs the GPU renderer (game will stall)\n", e);
#endif
    }
    R.gpu_scale = R.cfg.gpu_scale;
    R.gpu_scale_forced = R.gpu_scale > 0;
    if (R.gpu_scale <= 0) {
        const char *e = getenv("RG_GPU_SCALE");
        R.gpu_scale_forced = e && *e;
        R.gpu_scale = e && *e ? atoi(e) : 1;
    }
    if (R.gpu_scale < 1)
        R.gpu_scale = 1;
    if (R.gpu_scale > 8)
        R.gpu_scale = 8;
#ifndef RG_HAVE_GPU
    if (R.cfg.gpu) {
        fprintf(stderr, "rg_runtime: built without the GPU renderer (src/gpu); software GS\n");
        R.cfg.gpu = 0;
    }
#endif
    /* validation: dumps at chosen fields, per-field wall time */
    const char *dd = getenv("RG_GS_DUMP_DIR"), *df = getenv("RG_GS_DUMP_FIELDS");
    if (dd && *dd && df && *df) {
        snprintf(R.dump_dir, sizeof R.dump_dir, "%s", dd);
        char spec[1024];
        snprintf(spec, sizeof spec, "%s", df);
        for (char *t = strtok(spec, ", "); t && R.ndump < 64; t = strtok(NULL, ", "))
            R.dump_fields[R.ndump++] = strtoull(t, NULL, 0);
    }
    const char *rp = getenv("RG_GS_REC"), *rfl = getenv("RG_GS_REC_FIELDS");
    if (rp && *rp && rfl && *rfl) {
        snprintf(R.rec_path, sizeof R.rec_path, "%s", rp);
        char *e = NULL;
        R.rec_first = strtoull(rfl, &e, 0);
        R.rec_last = (e && *e == '-') ? strtoull(e + 1, NULL, 0) : R.rec_first;
        if (R.rec_first < 1)
            R.rec_first = 1;
    }
    /* RG_WINDOW_SHOT=field:path: a PNG of the window (scaled, as presented)
     * at the end of that field (windowed runs only) */
    const char *ws = getenv("RG_WINDOW_SHOT");
    if (ws && *ws && strchr(ws, ':')) {
        R.shot_field = strtoull(ws, NULL, 0);
        snprintf(R.shot_path, sizeof R.shot_path, "%s", strchr(ws, ':') + 1);
    }
#if RT_IP
    {
        const char *e = getenv("RG_INTERP_SIM");
        if (e && *e) R.ip_sim_hz = atof(e);
        e = getenv("RG_INTERP_SIM_SNAP");
        R.ip_sim_snap = e && e[0] == '1';
        e = getenv("RG_INTERP_CHECK");
        R.ip_check = e && e[0] == '1';
        e = getenv("RG_INTERP_DUMP");
        if (e && *e) {
            const char *f = getenv("RG_INTERP_DUMP_FIELDS");
            char *x = NULL;
            snprintf(R.ip_dump, sizeof R.ip_dump, "%s", e);
            R.ip_dump_a = 0;
            R.ip_dump_b = ~0ull;
            if (f && *f) {
                R.ip_dump_a = strtoull(f, &x, 0);
                R.ip_dump_b = (x && *x == '-') ? strtoull(x + 1, NULL, 0) : R.ip_dump_a;
            }
        }
    }
#endif
    const char *al = getenv("RG_AUDIO_LOG");
    if (al && *al) {
        R.alog = fopen(al, "w");
        if (R.alog) {
            fprintf(R.alog, "field\tvbl\twall_ms\twork_ms\tslept_ms\tpresent_ms\tcd_reads\tcd_sectors\tcd_ms"
                            "\tframes\tq_before\tq_after\tstarves\tstarve_frames\tpad\tdrop\tratio\tresyncs"
                            "\tgpu_prims\tgpu_batches\tgpu_dst_copies\tgpu_writebacks\tgpu_up_kb\tgpu_down_kb\ttarget\n");
#if RG_IOP_ORACLE
            cdvd_set_io_clock(alog_now_ns);
#endif
            R.alog_t0 = wall_ms();
        }
    }
    {
        const char *pce = getenv("RG_PERF_CENSUS");
        const char *colon = pce ? strrchr(pce, ':') : NULL;
        if (colon && colon - pce < (int)sizeof R.census_dir) {
            memcpy(R.census_dir, pce, (size_t)(colon - pce));
            R.census_dir[colon - pce] = 0;
            const char *q = colon + 1;
            while (*q && R.ncensus < 16) {
                char *e = NULL;
                unsigned long long a = strtoull(q, &e, 10), b = a;
                if (e && *e == '-') b = strtoull(e + 1, &e, 10);
                R.census_r[R.ncensus][0] = a;
                R.census_r[R.ncensus][1] = b;
                R.ncensus++;
                if (!e || *e != ',') break;
                q = e + 1;
            }
        }
    }
    const char *fsx = getenv("RG_FIELD_STATS");
    if (fsx && *fsx) {
        R.field_stats = fopen(fsx, "w");
        /* big buffer, rare flushes: a write that blocks on a busy disk (seen: 1-25 s on the
         * shared PC) must not land in the fields being measured */
        if (R.field_stats)
            setvbuf(R.field_stats, NULL, _IOFBF, 1 << 22);
    }
    const char *pc = getenv("RG_PRESENT_COPY");   /* 1: read frames back to present (docs/PERF-3D.md) */
    R.no_shared = pc && pc[0] == '1';
    const char *ov = getenv("RG_GS_OVERLAP");
    R.overlap = !(ov && ov[0] == '0');
    const char *ft = getenv("RG_FIELD_TIMES");
    if (ft && *ft) {
        R.field_times = fopen(ft, "w");
        if (R.field_times)
            fprintf(R.field_times, "# field\twall_ms\tstep_ms\tread_ms\tpresent_ms\tgs_wait_ms\tpace_ms\tsync_ms\tpump_ms\taudio_ms\tpost_ms\tout_ms\n");
    }
}

static void gpu_start(void)
{
#if !(defined(RG_NATIVE_GS) && RG_NATIVE_GS)   /* (no GS model natively: nothing to leave unrasterized) */
    if (!R.cfg.gpu && getenv("RG_GS_NULL")) {
        /* RG_GS_NULL=1 (measurement only): nothing rasterizes; the GS model
         * still parses, transfers and loads CLUTs.  The wall time per field
         * is then the game and the models without drawing. */
        R.gs->sw_raster = 0;
        fprintf(stderr, "rg_runtime: RG_GS_NULL: no rasterizer (measurement only)\n");
    }
#endif
#if !defined(RG_HAVE_GPU) && RG_NATIVE_ONLY && defined(RG_HAVE_NATIVE_RENDER)
    /* The headless renderer: a build with no GPU backend (Linux today, src/gpu is D3D11 only;
     * docs/LINUX.md "Headless renderer").  A native-only exe has no DMAC / VIF1 / VU1 models,
     * so the frame chain still has to be walked natively or every VIF1 send is dropped and the
     * game stalls on the title (docs/BRINGUP.md 2026-10-22).  Here the walker feeds the
     * software GS model itself, VU1 programs run in nr_vux.c; nr_scene draws nothing (no
     * device, so the game keeps its original MSCAL + CALL); RG_GS_NULL=1 skips rasterizing. */
    rg_vif1_chain_hook = nr_fx_on() ? vif1_chain : NULL;
    if (!R.cfg.quiet)
        fprintf(stderr, "rg_runtime: no GPU backend in this build: headless renderer (frame chain "
                        "walker -> software GS%s)\n", R.gs && !R.gs->sw_raster ? ", not rasterized" : "");   /* (no device) */
#endif
#ifdef RG_HAVE_GPU
    if (!R.cfg.gpu)
        return;
    gpu_config gc;
    char err[256];
    gpu_config_default(&gc);
    gc.warp = R.cfg.gpu == 2;
    gc.scale = R.gpu_scale;
    if (R.cfg.settings && rg_settings_find(R.cfg.settings, "display.backend") >= 0)
        gc.api = rg_settings_get_enum(R.cfg.settings, "display.backend");   /* docs/NATIVE-VULKAN.md */
    /* real-time play only: the lens flare's depth probes are served a frame late instead of
     * waiting on the game thread for the GPU (docs/NATIVE-THREADS.md "3h"); every headless /
     * unthrottled / display-hashed run (tests, traces, save states) reads exactly */
    gc.probe_lag = R.cfg.throttle && !R.cfg.headless && R.cfg.present && !R.cfg.display_hash_every;
#ifdef RG_HAVE_NATIVE_RENDER
    nr_runtime_gpu_config(&gc);
#endif
    R.gpu = gpu_create(&gc, err, sizeof err);
#if RG_NATIVE_ONLY && defined(RG_HAVE_NATIVE_RENDER)
    if (!R.gpu && !gc.warp) {
        /* no hardware adapter: WARP still runs the frame chain (software GS cannot) */
        fprintf(stderr, "rg_runtime: GPU renderer unavailable (%s); trying WARP\n", err);
        gc.warp = 1;
        R.cfg.gpu = 2;
        R.gpu = gpu_create(&gc, err, sizeof err);
    }
#endif
    if (!R.gpu) {
        fprintf(stderr, "rg_runtime: GPU renderer unavailable (%s); software GS\n", err);
        R.cfg.gpu = 0;
        return;
    }
    gpu_attach(R.gpu, R.gs);
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    nr_gs_bind(R.gs, R.gpu);   /* the state block's side effects reach the device */
#endif
#ifdef RG_HAVE_NATIVE_RENDER
    nr_runtime_attach_gpu(R.gpu);
    {
        /* local->host reads (the lens-flare depth probe) natively (libgraph) */
        extern int (*rg_gs_store_hook)(uint64_t, uint64_t, uint64_t, void *, int, int);
        rg_gs_store_hook = nr_native_store_fn();
        /* the frame chain walked natively, no DMAC / VIF1 (docs/NATIVE-RENDER.md "Frame chain walker") */
        rg_vif1_chain_hook = nr_fx_on() ? vif1_chain : NULL;
    }
#endif
#if RT_IP
    {
        /* Vulkan backend: the window's renderer moves onto the backend's device, so frames are
         * presented without a read-back (docs/NATIVE-VULKAN.md "Presentation") */
        gpu_vk_device vd;
        int vk_dev = gpu_vk_present_device(R.gpu, &vd) == 0;
        if (!vk_dev && !strncmp(gpu_device_name(R.gpu), "Vulkan", 6))
            R.no_shared = 1;   /* Vulkan without a presenter queue ($RG_VK_PRESENT=0, one queue): read back */
        if (R.host && !R.cfg.headless && R.cfg.present && vk_dev) {
            rg_host_vk_device hd;
            memset(&hd, 0, sizeof hd);
            hd.instance = vd.instance;
            hd.physical_device = vd.physical_device;
            hd.device = vd.device;
            hd.queue_family = vd.queue_family;
            if (rg_host_use_vulkan(R.host, &hd) == 0) {
                R.vk_present = 1;
                if (!R.cfg.quiet) fprintf(stderr, "rg_runtime: window presents from the Vulkan device (zero-copy)\n");
            } else {
                R.no_shared = 1;
                if (!R.cfg.quiet)
                    fprintf(stderr, "rg_runtime: Vulkan presentation unavailable (%s), reading frames back\n", rg_host_last_error());
            }
        }
    }
#endif
    R.gfx_applied = 0;
    gfx_update(); /* graphics.* (enhancements now; the scale per field) */
    if (!R.cfg.quiet)
        fprintf(stderr, "rg_runtime: GS drawn by the GPU renderer: %s, scale %d (game heap at %p)\n",
                gpu_device_name(R.gpu), gpu_get_scale(R.gpu),
                rg_crt0_ram() ? (void *)rg_crt0_ram()->heap_start : NULL);
#endif
}

static void gpu_stop(void)
{
#ifdef RG_HAVE_GPU
    if (!R.gpu)
        return;
    const gpu_stats *g = gpu_get_stats(R.gpu);
    if (!R.cfg.quiet)
        fprintf(stderr,
                "rg_runtime: gpu prims=%llu batches=%llu passes=%llu dst_copies=%llu rt "
                "creates=%llu loads=%llu writebacks=%llu drops=%llu up=%llu down=%llu "
                "feedback_splits=%llu direct=%llu wb_avoided=%llu tex_copies=%llu cpu_prims=%llu clut_gpu=%llu "
                "clut_resolves=%llu rt_pool_hits=%llu clut_check_bad=%llu\n",
                (unsigned long long)g->prims, (unsigned long long)g->batches,
                (unsigned long long)g->passes, (unsigned long long)g->dst_copies,
                (unsigned long long)g->rt_creates, (unsigned long long)g->rt_loads,
                (unsigned long long)g->rt_writebacks, (unsigned long long)g->rt_drops,
                (unsigned long long)g->upload_bytes, (unsigned long long)g->download_bytes,
                (unsigned long long)g->feedback_splits, (unsigned long long)g->direct_samples,
                (unsigned long long)g->writebacks_avoided, (unsigned long long)g->tex_copies,
                (unsigned long long)g->cpu_prims, (unsigned long long)g->clut_gpu, (unsigned long long)g->clut_resolves, (unsigned long long)g->rt_pool_hits, (unsigned long long)g->clut_check_bad);
    if (getenv("RG_NR_FXCENSUS") && R.gs) {
        /* the emulated residue census (docs/NATIVE-RENDER.md "Census of the emulated residue") */
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        nr_gs_gif_stats(stderr);   /* (no GS model left to count) */
#else
        gs_fx_census_dump(stderr);
#endif
#if RG_NATIVE_ONLY
        sce_graphics_native_stats(stderr);
#else
        for (int vi = 0; vi < 2; vi++) {
            const vif_state *vv = vi ? &R.vif1 : &R.vif0;
            fprintf(stderr, "fxcensus VIF%d commands:", vi);
            for (int c = 0; c < 128; c++)
                if (vv->stats.cmds[c]) fprintf(stderr, " %02X:%llu", c, (unsigned long long)vv->stats.cmds[c]);
            fprintf(stderr, " | unpack qw %llu mscal %llu mpg bytes %llu direct bytes %llu\n",
                    (unsigned long long)vv->stats.unpack_qwords, (unsigned long long)vv->stats.mscal,
                    (unsigned long long)vv->stats.mpg_bytes, (unsigned long long)vv->stats.direct_bytes);
        }
        if (R.dmac) {
            fprintf(stderr, "fxcensus DMAC kicks / qwords by channel:");
            for (int c = 0; c < DMAC_NCH; c++)
                if (R.dmac->stats[c].kicks)
                    fprintf(stderr, " %d:%llu/%llu", c, (unsigned long long)R.dmac->stats[c].kicks,
                            (unsigned long long)R.dmac->stats[c].qwords);
            fputc('\n', stderr);
        }
#endif
    }
#ifdef RG_HAVE_NATIVE_RENDER
    if (!R.cfg.quiet) {
        const gpu_nr_stats *ns = gpu_nr_get_stats(R.gpu);
        nr_runtime_stats(stderr);
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        nr_gs_gif_stats(stderr);
#endif
#if RT_IP
        if (nr_ip_on() || R.ip_presents)
            fprintf(stderr, "rg_runtime: interpolated presents %llu (between phases %llu); sim %llu presents at %.2f Hz "
                            "(%llu from a pass), %llu changed from the previous; exact check %llu same, %llu differ\n",
                    (unsigned long long)R.ip_presents, (unsigned long long)R.ip_between, (unsigned long long)R.ip_sim_n,
                    R.ip_sim_hz, (unsigned long long)R.ip_sim_passes, (unsigned long long)R.ip_sim_changed,
                    (unsigned long long)R.ip_check_same, (unsigned long long)R.ip_check_differ);
#endif
        if (ns->draws || ns->skipped)
            fprintf(stderr, "rg_runtime: native draws %llu tris %llu skipped %llu tex decodes %llu mesh uploads %llu "
                            "blend approx %llu unsupported state %llu\n",
                    (unsigned long long)ns->draws, (unsigned long long)ns->tris, (unsigned long long)ns->skipped,
                    (unsigned long long)ns->tex_decodes, (unsigned long long)ns->mesh_uploads,
                    (unsigned long long)ns->blend_approx, (unsigned long long)ns->unsupported_state);
            if (ns->lazy_tex || ns->im_draws)
                fprintf(stderr, "rg_runtime: native immediate draws %llu (%llu primitives), textures from pending transfers %llu (%llu CPU decodes)\n",
                        (unsigned long long)ns->im_draws, (unsigned long long)ns->im_prims, (unsigned long long)ns->lazy_tex,
                        (unsigned long long)ns->lazy_decodes);
    }
#endif
    if (R.vk_present) {
        /* the window's renderer lives on the device the backend is about to destroy */
        rg_host_drop_vulkan(R.host);
        R.vk_present = 0;
    }
    gpu_destroy(R.gpu); /* syncs gs->vram and detaches first */
    R.gpu = NULL;
#endif
}

/* $RG_GS_REC / $RG_GS_REC_FIELDS=first-last: every GS input of fields
 * first..last (gs.h "input recorder") after a snapshot of the model taken
 * at the start of field `first`; replay with `rg-gpu-tests replay FILE`
 * (tests/gpu, docs/GPU.md "Real game validation").  Recordings hold game
 * data: keep them under out/. */
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
/* (no GS model: no GS input recording) */
static void rec_field_start(void) {}
static void rec_field_end(void) {}
#else
static void rec_cb(void *user, int kind, uint32_t a, uint64_t v, const void *data, uint32_t bytes)
{
    (void)user;
    if (R.rec)
        gs_rec_event(R.rec, kind, a, v, data, bytes);
}

static void rec_field_start(void)
{
    if (!R.rec_path[0] || R.rec || R.st.fields + 1 != R.rec_first)
        return;
    gsq_drain();
#ifdef RG_HAVE_GPU
    if (R.gpu)
        gpu_sync(R.gpu);
#endif
    R.rec = fopen(R.rec_path, "wb");
    if (!R.rec || gs_rec_snapshot(R.rec, R.gs) != 0) {
        fprintf(stderr, "rg_runtime: RG_GS_REC: cannot write %s\n", R.rec_path);
        if (R.rec)
            fclose(R.rec);
        R.rec = NULL;
        R.rec_path[0] = 0;
        return;
    }
    R.gs->rec = rec_cb;
    R.gs->rec_user = NULL;
}

static void rec_field_end(void)
{
    if (!R.rec || R.st.fields < R.rec_last)
        return;
    R.gs->rec = NULL;
    fclose(R.rec);
    R.rec = NULL;
    if (!R.cfg.quiet)
        fprintf(stderr, "GSREC fields %llu-%llu %s\n", (unsigned long long)R.rec_first,
                (unsigned long long)R.rec_last, R.rec_path);
    R.rec_path[0] = 0;
}
#endif

/* R.frame holds at least px pixels (grows only). */
static int frame_reserve(uint64_t px)
{
    if (px <= R.frame_cap)
        return 0;
    if (px > (64ull << 20))
        return -1;
    uint32_t *n = (uint32_t *)realloc(R.frame, (size_t)px * sizeof(uint32_t));
    if (!n)
        return -1;
    R.frame = n;
    R.frame_cap = (uint32_t)px;
    return 0;
}

/* What the PCRTC shows now: the GPU's display (native size x scale) or the
 * software read-out of local memory. */
static int read_display(uint32_t *w, uint32_t *h)
{
#ifdef RG_HAVE_GPU
    if (R.gpu) {
        int rc = gpu_read_display(R.gpu, GS_READ_FRAME, R.frame, R.frame_cap, w, h);
        if (rc != 0 && *w && *h && frame_reserve((uint64_t)*w * *h) == 0)
            rc = gpu_read_display(R.gpu, GS_READ_FRAME, R.frame, R.frame_cap, w, h);
        return rc;
    }
#endif
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    (void)w; (void)h;
    return -1;   /* (no GS model to read local memory on the CPU: the device composes the display) */
#else
    return gs_read_display(R.gs, GS_READ_FRAME, R.frame, R.frame_cap, w, h);
#endif
}

/* ---------------------------------------------------------------- graphics
 * The renderer-side graphics settings (graphics.*, display.frame_rate;
 * docs/GPU.md "Graphics settings", PLAN.md P6).  Presentation only: the GS
 * model, the game and the virtual clock never see them.  Without a
 * registry (cfg.settings NULL) or at the Original preset nothing changes. */
static const int k_frame_caps[] = { 0, 30, 60, 120, 144, 0 };   /* display.frame_rate order */

/* audio.music_volume / effects_volume / voice_volume / movie_volume (PLAN.md P6, docs/
 * NATIVE-AUDIO.md "Source volumes"): gains of the engine's presentation mix, which only the
 * device hears; the run hash and RG_AUDIO_WAV fold the model mix.  Live. */
static uint64_t g_amix_gen;
static int g_amix_applied;
static void audio_mix_update(void)
{
#ifdef RG_HAVE_NATIVE_AUDIO
    rg_settings *s = R.cfg.settings;
    if (!s || (g_amix_applied && rg_settings_generation(s) == g_amix_gen))
        return;
    g_amix_applied = 1;
    g_amix_gen = rg_settings_generation(s);
    static const char *const ids[4] = {"audio.music_volume", "audio.effects_volume", "audio.voice_volume",
                                       "audio.movie_volume"};
    int v[4];
    for (int i = 0; i < 4; i++)
        v[i] = rg_settings_find(s, ids[i]) >= 0 ? rg_settings_get_int(s, ids[i]) : 100;
    rg_audio_runtime_volumes(v[0], v[1], v[2], v[3]);
#endif
}

static void gfx_update(void)
{
    rg_settings *s = R.cfg.settings;
    if (!s || (R.gfx_applied && rg_settings_generation(s) == R.gfx_gen))
        return;
    R.gfx_applied = 1;
    R.gfx_gen = rg_settings_generation(s);
    R.frame_cap_fps = 0;
    if (rg_settings_find(s, "display.frame_rate") >= 0) {
        int v = rg_settings_get_enum(s, "display.frame_rate");
        if (v >= 0 && v < (int)(sizeof k_frame_caps / sizeof k_frame_caps[0]))
            R.frame_cap_fps = k_frame_caps[v];
    }
#ifdef RG_HAVE_GPU
    gpu_gfx_from_settings(&R.gfx, s);
    if (R.gpu) {
        gsq_drain();   /* the worker draws with the renderer's settings */
        gpu_set_enhance(R.gpu, &R.gfx.enh);
    }
#endif
}

#ifdef RG_HAVE_GPU
/* Per field: the window rectangle the frame fills, the render scale that
 * follows from graphics.internal_res / antialiasing (applied live, also
 * headless: "match window" is then native), and the post chain for it.
 * Returns 1 when the post chain is not the identity. */
static int gfx_frame(gpu_post *post)
{
    gpu_post_default(post);
    if (!R.gpu || !R.cfg.settings)
        return 0;
    uint32_t nw = 0, nh = 0;
    if (gpu_display_size(R.gpu, &nw, &nh) != 0 || !nw || !nh)
        return 0;
    int ww = 0, wh = 0;
    rg_scale_mode mode = rg_host_scale(R.host);
    if (R.cfg.present && !R.cfg.headless)
        rg_host_window_size(R.host, &ww, &wh);
    rg_rect dst = { 0, 0, 0, 0 };
    int factor = 0, need_h = 0;
    if (ww > 0 && wh > 0) {
        /* the host's rectangle (4:3, or graphics.aspect's canvas with the
         * frame pillarboxed in it: docs/WIDESCREEN.md) */
        dst = rg_host_fit(R.host, ww, wh, (int)nw, (int)nh, &factor);
        need_h = dst.h;
        int an = 4, ad = 3;
        rg_host_get_aspect(R.host, &an, &ad, NULL, NULL);
        if ((int64_t)an * 3 != (int64_t)ad * 4) {
            /* a wide canvas stretches the 512 columns more than the 448
             * rows: "match window" reaches its width too.  From the canvas,
             * not the (pillarboxed) frame, so movies keep the scale. */
            rg_rect cv = rg_fit_rect(ww, wh, (int)nw, (int)nh, an, ad, mode, NULL);
            int hw = (int)(((int64_t)cv.w * nh + nw - 1) / nw);
            need_h = cv.h > hw ? cv.h : hw;
        }
    }
    int ssaa = 1;
    if (!R.gpu_scale_forced) {
        int sc = gpu_gfx_scale(&R.gfx, need_h, (int)nh, &ssaa);
        if (sc != gpu_get_scale(R.gpu)) {
            gsq_drain();   /* the worker owns the renderer (overlap) */
            gpu_set_scale(R.gpu, sc);
            if (!R.cfg.quiet)
                fprintf(stderr, "rg_runtime: internal resolution %dx (ssaa %d)\n", sc, ssaa);
        }
    }
    *post = R.gfx.post;
    post->ssaa = ssaa;
    if (gpu_post_identity(post))
        return 0;   /* nothing to do on the GPU: the presenter scales as before */
    post->out_w = dst.w;
    post->out_h = dst.h;
    post->upscale = mode == RG_SCALE_NEAREST ? GPU_RS_NEAREST
                  : (mode == RG_SCALE_INTEGER ? GPU_RS_SHARP : GPU_RS_BILINEAR);
    return 1;
}
static gpu_post g_post;   /* this field's chain (gfx_frame) */
static int g_post_on;
#endif

/* The frame to present: the display through the post chain (GPU), or the
 * display itself. */
static int read_present(uint32_t *w, uint32_t *h, int *same_as_display)
{
    *same_as_display = 1;
#ifdef RG_HAVE_GPU
    if (R.gpu && g_post_on) {
        *same_as_display = 0;
        int rc = gpu_read_output(R.gpu, GS_READ_FRAME, &g_post, R.frame, R.frame_cap, w, h);
        if (rc != 0 && *w && *h && frame_reserve((uint64_t)*w * *h) == 0)
            rc = gpu_read_output(R.gpu, GS_READ_FRAME, &g_post, R.frame, R.frame_cap, w, h);
        return rc;
    }
#endif
    return read_display(w, h);
}

/* $RG_GS_DUMP_DIR + $RG_GS_DUMP_FIELDS (comma list): at the end of each listed
 * field write
 *   fNNNNN_display.png  what is presented (GPU: its display, native x scale)
 *   fNNNNN_local.png    gs_read_display of local memory (GPU: after gpu_sync,
 *                       the native write-back the CPU sees)
 *   fNNNNN.vram         the 4 MB of local memory (GPU: after gpu_sync)
 *   fNNNNN.regs         preg[32], reg[128] (u64 LE), clut[512] (u16 LE)
 * The same run on the software GS writes the reference set (runs are
 * deterministic: tools/gpu_validate.py compares the two directories). */
static void dump_field(void)
{
    int hit = 0;
    for (int i = 0; i < R.ndump; i++)
        if (R.dump_fields[i] == R.st.fields)
            hit = 1;
    if (!hit)
        return;
    char p[700];
    unsigned long long fld = (unsigned long long)R.st.fields;
    uint32_t w = 0, h = 0;
    if (read_display(&w, &h) == 0) {
        snprintf(p, sizeof p, "%s/f%05llu_display.png", R.dump_dir, fld);
        rg_png_write(p, R.frame, w, h);
    }
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    if (R.gpu) {
        /* fNNNNN.vram: the device's local memory (every target written back); no CPU read-out */
        static uint8_t *img;
        if (!img) img = (uint8_t *)malloc(GS_VRAM_BYTES);
        snprintf(p, sizeof p, "%s/f%05llu.vram", R.dump_dir, fld);
        FILE *vf = img ? fopen(p, "wb") : NULL;
        if (vf) {
            gpu_mem_save(R.gpu, img);
            fwrite(img, 1, GS_VRAM_BYTES, vf);
            fclose(vf);
        }
    }
    snprintf(p, sizeof p, "%s/f%05llu.regs", R.dump_dir, fld);
    FILE *rf = fopen(p, "wb");
    if (rf) {
        fwrite(R.gs->preg, 8, 32, rf);
        fwrite(R.gs->reg, 8, 128, rf);
        fwrite(R.gs->clut, 2, 512, rf);
        fclose(rf);
    }
    if (!R.cfg.quiet)
        fprintf(stderr, "GSDUMP field=%llu dir=%s\n", fld, R.dump_dir);
#else
#ifdef RG_HAVE_GPU
    if (R.gpu && gpu_get_scale(R.gpu) > 1) {
        /* fNNNNN_target.png: the displayed buffer as the GPU holds it, at the
         * internal resolution and before the PCRTC merge (sub-pixel detail
         * check of tools/gpu_validate.py) */
        uint64_t pm = R.gs->preg[0];
        uint64_t fb = R.gs->preg[(pm & 2) ? 9 : 7];
        uint32_t nw = 0, nh = 0;
        if (gs_read_display(R.gs, GS_READ_FRAME, NULL, 0, &nw, &nh) != 0 && nw && nh &&
            frame_reserve((uint64_t)nw * nh * (uint64_t)gpu_get_scale(R.gpu) * (uint64_t)gpu_get_scale(R.gpu)) == 0 &&
            gpu_read_target(R.gpu, (uint32_t)(fb & 0x1FF) * 32u, (uint32_t)((fb >> 9) & 0x3F),
                            (int)((fb >> 15) & 0x1F), (int)((fb >> 32) & 0x7FF),
                            (int)((fb >> 43) & 0x7FF), (int)nw, (int)nh, R.frame) == 0) {
            uint32_t s = (uint32_t)gpu_get_scale(R.gpu);
            for (uint32_t i = 0; i < nw * s * nh * s; i++)
                R.frame[i] |= 0xFF000000u;
            snprintf(p, sizeof p, "%s/f%05llu_target.png", R.dump_dir, fld);
            rg_png_write(p, R.frame, nw * s, nh * s);
        }
    }
    if (R.gpu)
        gpu_sync(R.gpu);
#endif
    if (gs_read_display(R.gs, GS_READ_FRAME, R.frame, R.frame_cap, &w, &h) == 0) {
        snprintf(p, sizeof p, "%s/f%05llu_local.png", R.dump_dir, fld);
        rg_png_write(p, R.frame, w, h);
    }
    snprintf(p, sizeof p, "%s/f%05llu.vram", R.dump_dir, fld);
    FILE *f = fopen(p, "wb");
    if (f) {
        fwrite(R.gs->vram, 1, GS_VRAM_BYTES, f);
        fclose(f);
    }
    snprintf(p, sizeof p, "%s/f%05llu.regs", R.dump_dir, fld);
    f = fopen(p, "wb");
    if (f) {
        fwrite(R.gs->preg, 8, 32, f);
        fwrite(R.gs->reg, 8, 128, f);
        fwrite(R.gs->clut, 2, 512, f);
        fclose(f);
    }
    if (!R.cfg.quiet)
        fprintf(stderr, "GSDUMP field=%llu dir=%s\n", fld, R.dump_dir);
#endif
}

/* ---------------------------------------------------------------- per field */
#ifdef RG_HAVE_GPU
/* Pipelined presentation (R.overlap): the frame of field N is composed on the
 * GS worker after field N's packets (gs_async_call) into a shared texture,
 * from a snapshot of the PCRTC registers, and presented by host_half of field
 * N + 1 (one field of latency, like RG_GPU_READBACK_LAG). */
typedef struct ov_present_req {
    uint64_t preg[16];
    gpu_post post;
    int post_on;
    uint32_t seq;
} ov_present_req;
static struct {
    volatile uint32_t seq;     /* last request composed (worker writes) */
    int rc;
    void *handle;
    uint32_t w, h;
    uint32_t queued, presented;   /* main thread */
} g_ovp;
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
static void ov_present_worker(void *user, const void *data)
{
    const ov_present_req *q = (const ov_present_req *)data;
    void *hd = NULL;
    uint32_t w = 0, h = 0;
    (void)user;
#else
static void ov_present_worker(void *user, gs_state *gs, const void *data)
{
    const ov_present_req *q = (const ov_present_req *)data;
    void *hd = NULL;
    uint32_t w = 0, h = 0;
    (void)user; (void)gs;
#endif
    gpu_set_display_regs(R.gpu, q->preg);
    int rc = gpu_present_shared(R.gpu, GS_READ_FRAME, q->post_on ? &q->post : NULL, &hd, &w, &h);
    gpu_set_display_regs(R.gpu, NULL);
    g_ovp.rc = rc;
    g_ovp.handle = hd;
    g_ovp.w = w;
    g_ovp.h = h;
    __atomic_store_n(&g_ovp.seq, q->seq, __ATOMIC_RELEASE);
}
/* present the frame the worker composed for the previous field (the worker
 * has run up to it: host_half waited for its mark) */
static void ov_present_pending(void)
{
    if (g_ovp.presented == g_ovp.queued) return;
    if (__atomic_load_n(&g_ovp.seq, __ATOMIC_ACQUIRE) != g_ovp.queued) gsq_drain();
    g_ovp.presented = g_ovp.queued;
    if (g_ovp.rc != 0 || !g_ovp.handle) {
        /* the display is off (no size: nothing to show, e.g. the first fields after power-on):
         * not a reason to give up zero-copy for the rest of the run */
        if (g_ovp.rc != 0 && (!g_ovp.w || !g_ovp.h)) return;
        if (!R.no_shared && !R.cfg.quiet) fprintf(stderr, "rg_runtime: zero-copy presentation failed, reading frames back\n");
        R.no_shared = 1;   /* the next fields present through the copy path */
        return;
    }
    double t0 = R.field_times ? wall_ms() : 0.0;
    present_start();
    if (rg_host_present_shared(R.host, g_ovp.handle, g_ovp.w, g_ovp.h) == 0) {
        R.st.presents++;
        R.last_present_ms = wall_ms();
        present_mark(2);
        if (R.field_times) R.field_present_ms = wall_ms() - t0;
    } else {
        R.no_shared = 1;
        if (!R.cfg.quiet)
            fprintf(stderr, "rg_runtime: zero-copy presentation unavailable, reading frames back\n");
    }
}
#endif

/* this field must drain the worker: something reads the renderer or the GS
 * on this thread at its end */
static int host_needs_sync(int want_hash, int want_present)
{
    if (!R.overlap || !R.gs || !gsq_on() || R.finished || R.quit) return 1;
    if (want_hash) return 1;
    if (want_present && (R.no_shared || !R.gpu)) return 1;
    if (R.shot_field && (R.st.fields == R.shot_field || R.st.fields + 1 == R.shot_field)) return 1;
    for (int i = 0; i < R.ndump; i++)
        if (R.dump_fields[i] == R.st.fields) return 1;
    if (R.rec || R.ncensus) return 1;
    return 0;
}

#if RT_IP
/* ---------------------------------------------------------------- interpolated presentation
 * docs/NATIVE-RENDER.md "Interpolated presentation": a pass of the retained frame at host time
 * tau (VBlank phases) on the worker, then the display composed and presented as usual
 * (zero-copy path only).  0: nothing to interpolate (present as usual). */
static double ip_tau(void)
{
    double t = (double)R.pace.ticks;
    if (R.pace.cfg.mode == RG_PACE_HOST) t += (double)R.pace.acc / (double)RG_PACE_FIELD_U;
    return t;
}
static int ip_present(double tau)
{
    void *hd = NULL;
    uint32_t w = 0, h = 0;
    if (!R.gpu || R.no_shared || !R.host) return 0;
    present_start();
    if (!nr_ip_queue_present(tau, nr_hw_display_regs())) return 0;
    gsq_drain();
    if (gpu_present_shared(R.gpu, GS_READ_FRAME, g_post_on ? &g_post : NULL, &hd, &w, &h) != 0) return 0;
    if (R.shot_field && R.st.fields == R.shot_field)
        rg_host_request_window_shot(R.host, R.shot_path);
    if (R.present_log) g_present_tw = wall_ms();
    if (rg_host_present_shared(R.host, hd, w, h) != 0) return 0;
    R.st.presents++;
    R.ip_presents++;
    R.last_present_ms = wall_ms();
    present_mark(3);
    return 1;
}
/* headless measurement ($RG_INTERP_SIM=hz): after the field, the presents a host at hz would
 * make before the next phase (tau in [ticks, ticks + 1)), each a pass + the display read out
 * (hashed; PNG in $RG_INTERP_DUMP for the fields in $RG_INTERP_DUMP_FIELDS), then the restore */
static void ip_hash_frame(uint32_t w, uint32_t h, uint64_t *out)
{
    uint64_t x = 1469598103934665603ull;
    for (size_t i = 0; i < (size_t)w * h; i++) x = (x ^ R.frame[i]) * 1099511628211ull;
    *out = x;
}
static void ip_sim_field(void)
{
    uint32_t w = 0, h = 0;
    uint64_t hh;
    if (R.ip_check && nr_ip_on()) {
        /* exact pass of the newest frame: does re-executing it reproduce it? */
        uint64_t h0 = 0;
        gsq_drain();
        if (read_display(&w, &h) == 0) {
            static uint32_t *before;
            static size_t bcap;
            ip_hash_frame(w, h, &h0);
            if ((size_t)w * h > bcap) {
                free(before);
                bcap = (size_t)w * h;
                before = (uint32_t *)malloc(bcap * 4);
                if (!before) bcap = 0;
            }
            if (before) memcpy(before, R.frame, (size_t)w * h * 4);
            if (nr_ip_queue_exact()) {
                gsq_drain();
                if (read_display(&w, &h) == 0) {
                    ip_hash_frame(w, h, &hh);
                    if (hh == h0) R.ip_check_same++;
                    else {
                        R.ip_check_differ++;
                        if (before && R.ip_dump[0] && R.ip_check_differ <= 8) {
                            /* the first differing frames: before / after and the pixel count */
                            char p[700];
                            size_t nd = 0;
                            for (size_t i = 0; i < (size_t)w * h; i++) nd += before[i] != R.frame[i];
                            fprintf(stderr, "interp check: field %llu differs in %zu pixels\n", (unsigned long long)R.st.fields, nd);
                            snprintf(p, sizeof p, "%s/check_f%05llu_after.png", R.ip_dump, (unsigned long long)R.st.fields);
                            rg_png_write(p, R.frame, w, h);
                            snprintf(p, sizeof p, "%s/check_f%05llu_before.png", R.ip_dump, (unsigned long long)R.st.fields);
                            rg_png_write(p, before, w, h);
                        }
                    }
                }
            }
        }
    }
    if (R.ip_sim_hz <= 0.0) return;
    double step = (60000.0 / 1001.0) / R.ip_sim_hz, t0 = (double)R.pace.ticks;
    uint64_t k0 = (uint64_t)(t0 / step);
    while ((double)k0 * step < t0 - 1e-9) k0++;
    for (uint64_t k = k0; (double)k * step < t0 + 1.0 - 1e-9; k++) {
        double tau = (double)k * step;
        int passed = !R.ip_sim_snap && nr_ip_queue_present(tau, nr_hw_display_regs());
        gsq_drain();
        if (read_display(&w, &h) != 0) continue;
        ip_hash_frame(w, h, &hh);
        R.ip_sim_n++;
        R.ip_sim_passes += passed ? 1 : 0;
        if (R.ip_sim_n > 1 && hh != R.ip_last_hash) R.ip_sim_changed++;
        R.ip_last_hash = hh;
        if (R.ip_dump[0] && R.st.fields >= R.ip_dump_a && R.st.fields <= R.ip_dump_b) {
            char p[700];
            snprintf(p, sizeof p, "%s/s%06llu_f%05llu.png", R.ip_dump, (unsigned long long)R.ip_seq,
                     (unsigned long long)R.st.fields);
            rg_png_write(p, R.frame, w, h);
        }
        R.ip_seq++;
    }
    nr_ip_settle();
    gsq_drain();
}
#endif

static void host_half(void)
{
    int want_hash = R.cfg.display_hash_every && R.st.fields % R.cfg.display_hash_every == 0;
    int want_present = R.cfg.present && !R.cfg.headless;
    int shot_now = R.shot_field && R.st.fields == R.shot_field;
    if (want_present && R.pace.cfg.mode == RG_PACE_HOST) {
        /* paced: present when no further phase is owed now and the frame cap's slot came */
        if (!shot_now && !rg_pace_present_now(&R.pace, pace_now()))
            want_present = 0;
    } else if (want_present && R.frame_cap_fps > 0 && !shot_now) {
        /* display.frame_rate: present at most this often (wall clock); the
         * fields themselves keep running on the virtual clock */
        double now = wall_ms();
        if (R.last_present_ms > 0.0 && now - R.last_present_ms < 1000.0 / R.frame_cap_fps - 0.5)
            want_present = 0;
    }
    int presenting = want_present;
    int sync = host_needs_sync(want_hash, want_present);
    double th0 = R.field_times ? wall_ms() : 0.0;
    if (sync) {
        /* the presentation below reads the renderer and the GS: everything the
         * field queued must have run (docs/PERF-3D.md "GS worker thread") */
        gsq_drain();
        if (R.overlap) R.ov_synced++;
    } else {
        /* overlap: the worker may still draw this field while the next one
         * runs; it must have finished the previous one (bounded lag: the
         * native renderer's record ring, presentation latency) */
        gsq_wait_mark(R.ov_mark);
        R.ov_fields++;
    }
#ifdef RG_HAVE_GPU
    ov_present_pending();
#endif
    /* the phase's cost for the catch-up decision includes the GS worker wait above */
    if (R.pace.cfg.mode == RG_PACE_HOST) rg_pace_phase_done(&R.pace, pace_now());
    double th1 = R.field_times ? wall_ms() : 0.0;
    if (R.field_times) R.field_sync_ms = th1 - th0;
    /* events: quit, hotkeys, gamepad hot-plug */
    if (!rg_host_pump(R.host))
        R.quit = 1;
    rg_host_fps_logic(R.host, rg_frame_logic_ticks()); /* display.fps_counter's logic rate */
    double th2 = R.field_times ? wall_ms() : 0.0;
    if (R.field_times) R.field_pump_ms = th2 - th1;

    /* audio: everything snd_sync rendered up to the VBlank.  A pacer
     * re-anchor dropped wall time the device queue had been covering: let
     * the host rebuild its cushion (presentation only). */
    if (R.pacer.resyncs + R.pace.resyncs != R.resyncs_seen) {
        R.resyncs_seen = R.pacer.resyncs + R.pace.resyncs;
        rg_host_audio_resync(R.host);
    }
    if (R.alog)
        R.alog_q0 = rg_host_audio_queued(R.host);
    if (R.pace.cfg.mode == RG_PACE_HOST) /* phases owed now = audio a catch-up pushes at once */
        rg_host_audio_owed(R.host, (uint32_t)(R.pace.acc / RG_PACE_FIELD_U) * 800u);
    uint32_t got = 0;
    audio_mix_update(); /* audio.*_volume -> the engine's presentation mix */
    for (;;) {
        uint32_t n;
        const int16_t *play = R.audio; /* what the device gets: the presentation mix */
#ifdef RG_HAVE_NATIVE_AUDIO
        if (rg_iop_native()) {
            /* no HLE sound: the native engine's own frames (docs/NATIVE-IOP.md) */
            n = rg_audio_runtime_read(R.audio, AUDIO_CAP_FRAMES);
            if (!n)
                break;
            play = rg_audio_runtime_present(R.audio, n); /* per-source volumes (after the hash point) */
        } else {
#if RG_IOP_ORACLE
            n = snd_output_read(R.audio, AUDIO_CAP_FRAMES);
            if (!n)
                break;
            rg_audio_runtime_mix(R.audio, n); /* native: + the engine; compare: engine -> its WAV */
#else
            break;
#endif
        }
#else
        n = snd_output_read(R.audio, AUDIO_CAP_FRAMES);
        if (!n)
            break;
#endif
        for (uint32_t i = 0; i < n * 2; i++) {
            int32_t v = R.audio[i] < 0 ? -(int32_t)R.audio[i] : R.audio[i];
            if (v > R.st.audio_peak)
                R.st.audio_peak = v;
        }
        fold_part(1, &R.st.run_hash, R.audio, (size_t)n * 4);
        rg_host_audio_push(R.host, play, n);
        if (R.wav)
            R.wav_frames += fwrite(R.audio, 4, n, R.wav);
        got += n;
    }
    R.st.audio_frames += got;
    double th3 = R.field_times ? wall_ms() : 0.0;
    if (R.field_times) R.field_audio_ms = th3 - th2;
    if (R.wav_fields) {
        uint64_t kv = ps2k_vblank_count();
        uint32_t gv = R.cfg.game_vblank ? R.cfg.game_vblank(R.cfg.game_vblank_user, kv) : (uint32_t)kv;
        fprintf(R.wav_fields, "%llu\t%llu\t%u\t%llu\t%llu\n", (unsigned long long)R.st.fields,
                (unsigned long long)kv, gv, (unsigned long long)R.wav_frames,
                (unsigned long long)ps2k_now());
    }
    if (R.wav && R.st.fields % 60 == 0) {
        wav_header(R.wav, R.wav_frames); /* keep the file valid if the process dies */
        fflush(R.wav);
        if (R.wav_fields)
            fflush(R.wav_fields);
    }
    R.st.audio_frames_last = got;
    R.st.audio_dropped = RG_IOP_PICK(0, snd_output_dropped());

    /* display: the PCRTC read-out of what the GS shows now.  The hash
     * always folds the display itself; the presented frame may have gone
     * through the graphics settings' post chain (presentation only). */
    gfx_update();
#ifdef RG_HAVE_GPU
    g_post_on = gfx_frame(&g_post);
#if RT_IP
    /* interpolated presentation: this present from a pass (when there is a frame pair) */
    if (want_present && nr_ip_on() && ip_present(ip_tau()))
        want_present = 0;
    if (nr_ip_on() && (want_present || want_hash || R.ndump || R.shot_field || R.rec)) {
        nr_ip_settle(); /* the exact frame again before this thread reads the device */
        if (sync) gsq_drain();
    }
#endif
    if (want_present && !sync) {
        /* composed on the worker after this field's packets, presented by
         * the next field's host_half */
        ov_present_req q;
        memset(&q, 0, sizeof q);
        memcpy(q.preg, R.gs->preg, sizeof q.preg);
        q.post = g_post;
        q.post_on = g_post_on;
        q.seq = ++g_ovp.queued;
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        nr_q_call(ov_present_worker, NULL, &q, sizeof q);
#else
        gs_async_call(R.gs, ov_present_worker, NULL, &q, sizeof q);
#endif
        want_present = 0;
    }
#endif
    if (want_present) {
        uint32_t w = 0, h = 0;
        int same = 1;
        double tp = R.alog || R.field_times ? wall_ms() : 0.0;
        int rp = -1;
        present_start();
#ifdef RG_HAVE_GPU
        if (R.gpu && !R.no_shared) {
            /* zero-copy (docs/PERF-3D.md): the frame stays on the GPU in a
             * texture the window's renderer draws; no read-back, no wait */
            void *hd = NULL;
            if (gpu_present_shared(R.gpu, GS_READ_FRAME, g_post_on ? &g_post : NULL, &hd, &w, &h) == 0) {
                double tr0 = R.field_times ? wall_ms() : 0.0;
                if (R.field_times) R.field_read_ms = tr0 - tp;
                if (R.shot_field && R.st.fields == R.shot_field)
                    rg_host_request_window_shot(R.host, R.shot_path);
                if (rg_host_present_shared(R.host, hd, w, h) == 0) {
                    R.st.presents++;
                    R.last_present_ms = wall_ms();
                    present_mark(1);
                    if (R.field_times) R.field_present_ms = wall_ms() - tr0;
                    rp = 1;   /* presented */
                } else {
                    R.no_shared = 1;
                    if (!R.cfg.quiet)
                        fprintf(stderr, "rg_runtime: zero-copy presentation unavailable, reading frames back\n");
                }
            } else if (w && h) {   /* (no size: the display is off, see ov_present_pending) */
                R.no_shared = 1;
                if (!R.cfg.quiet) fprintf(stderr, "rg_runtime: zero-copy presentation failed, reading frames back\n");
            }
        }
#endif
        if (rp != 1) rp = read_present(&w, &h, &same);
        double tr = R.field_times ? wall_ms() : 0.0;
        if (R.field_times && rp != 1) R.field_read_ms = tr - tp;
        if (rp == 0) {
            if (R.shot_field && R.st.fields == R.shot_field)
                rg_host_request_window_shot(R.host, R.shot_path); /* the window as shown */
            if (rg_host_present(R.host, R.frame, w, h) == 0) {
                R.st.presents++;
                R.last_present_ms = wall_ms();
                present_mark(0);
            }
            if (R.field_times) R.field_present_ms = wall_ms() - tr;
            if (R.alog)
                R.alog_present_ms = wall_ms() - tp;
            if (want_hash && same) {
                uint32_t dim[2] = {w, h};
                fold_part(2, &R.st.run_hash, dim, sizeof dim);
                fold_part(2, &R.st.run_hash, R.frame, (size_t)w * h * 4);
                want_hash = 0;
            }
        }
    }
    if (want_hash) {
        uint32_t w = 0, h = 0;
        if (read_display(&w, &h) == 0) {
            uint32_t dim[2] = {w, h};
            fold_part(2, &R.st.run_hash, dim, sizeof dim);
            fold_part(2, &R.st.run_hash, R.frame, (size_t)w * h * 4);
        }
    }
    fold64(ps2k_trace_hash());
    fold64(ps2k_now());
    if (g_hash_log)
        fprintf(g_hash_log, "%llu\t%016llx\t%016llx\t%016llx\t%016llx\t%016llx\t%llu\t%llu\n",
                (unsigned long long)R.st.fields, (unsigned long long)R.st.run_hash,
                (unsigned long long)g_hpart[0], (unsigned long long)g_hpart[1],
                (unsigned long long)g_hpart[2], (unsigned long long)ps2k_trace_hash(),
                (unsigned long long)ps2k_trace_count(), (unsigned long long)ps2k_now());
    if (presenting)
        rg_pace_presented(&R.pace, pace_now()); /* presented now or queued for the worker */
    if (presenting && R.field_stats && R.gs) {
        /* $RG_FIELD_STATS: does this present show a new game image or the previous one again?
         * The game hands the GS a frame (its DMA chain: GS worker payload) only in the fields
         * it draws; DISPFB stays put on this route, so payload since the last present it is */
        uint64_t aq[4] = {0};
        gsq_stats(aq);
        R.fs_presents++;
        if (aq[1] - R.fs_gsq_at_present > 16384) /* (a present's own compose call is ~1 KB) */
            R.fs_newimg++;
        R.fs_gsq_at_present = aq[1];
    }
    pace_log_row(0);
    if (!sync) R.ov_mark = gsq_mark();
    if (R.field_times) R.field_post_ms = wall_ms() - th3;
    if (R.alog) {
        alog_field(got);
        R.alog_present_ms = 0.0;
    }
}

/* $RG_FIELD_STATS=file: one TSV row per field of counter deltas, to attribute a slow field
 * (a scene / battle transition) to the work done in it: host CPU (process, this thread, every
 * thread by start address), page faults and private bytes, file reads, sound banks, GS
 * worker traffic, GPU target / upload / read-back / flush work and native-renderer first-use
 * work.  Counters written on the GS worker are read racily (diagnostics only; nothing here
 * feeds back into the run).  tools/perf3d/stutter.py joins it with $RG_FIELD_TIMES. */
#define FST_N 30
static void fstats_field(void)
{
    static double prev[FST_N];
    static double thr_prev[RG_FSTATS_MAX_THREADS];
    static uint32_t thr_tid[RG_FSTATS_MAX_THREADS];
    static int have;
    double v[FST_N];
    memset(v, 0, sizeof v);
    double now = wall_ms();
    rg_fstats_sys sys;
    if (R.st.fields % 300 == 1)
        rg_fstats_sys_refresh(); /* threads started since (a system-wide snapshot: ms) */
    rg_fstats_sys_sample(&sys);
    double self_ms = wall_ms() - now; /* this sampling's own cost (in the field's wall) */
    v[0] = sys.proc_cpu_ms;
    v[1] = sys.main_cpu_ms;
    v[2] = (double)sys.page_faults;
    v[3] = (double)sys.private_kb;
    rg_fs_stats fs;
    rg_fs_get_stats(&fs);
    v[4] = (double)fs.reads;
    v[5] = (double)fs.bytes / 1024.0;
    v[6] = (double)fs.read_ns / 1e6;
#ifdef RG_HAVE_NATIVE_AUDIO
    {
        const ra_stats *ra = ra_get_stats();
        if (ra) {
            v[7] = ra->banks_loaded;
            v[8] = (double)ra->bank_bytes / 1024.0;
            v[9] = ra->seqs_loaded;
        }
    }
#endif
    if (R.gs) {
        uint64_t aq[4] = {0}, lz[8] = {0};
        gsq_stats(aq);
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        (void)lz;
        v[10] = (double)aq[1] / 1024.0;
        v[11] = (double)R.gs->stats.xfer_bytes / 4000.0;   /* (transfer bytes / 4: pixels at 32 bits) */
        v[12] = 0.0;
        v[13] = (double)R.gs->stats.clut_loads;
#else
        gs_mem_lazy_stats(R.gs, lz);
        v[10] = (double)aq[1] / 1024.0;
        v[11] = (double)R.gs->stats.xfer_h2l_px / 1000.0;
        v[12] = (double)lz[4] / 1024.0;
        v[13] = (double)R.gs->stats.clut_loads;
#endif
    }
#ifdef RG_HAVE_GPU
    if (R.gpu) {
        const gpu_stats *g = gpu_get_stats(R.gpu);
        v[14] = (double)g->batches;
        v[15] = (double)g->rt_creates;
        v[16] = (double)g->rt_loads;
        v[17] = (double)g->rt_writebacks;
        v[18] = (double)g->upload_bytes / 1024.0;
        v[19] = (double)g->download_bytes / 1024.0;
        v[20] = (double)g->downloads;
        v[21] = (double)g->download_us / 1000.0;
        v[22] = (double)g->kick_us / 1000.0;
        v[23] = (double)g->tex_decodes;
        const gpu_nr_stats *n = gpu_nr_get_stats(R.gpu);
        if (n) {
            v[24] = (double)(n->draws + n->im_draws);
            v[25] = (double)n->tex_decodes;
            v[26] = (double)n->mesh_uploads;
            v[27] = (double)n->lazy_decodes;
        }
    }
#endif
    v[28] = (double)R.fs_presents;
    v[29] = (double)R.fs_newimg;
    if (!have) {
        fprintf(R.field_stats, "# image_base=0x%08x\n", sys.image_base);
        fprintf(R.field_stats, "# field\twall_ms\tfstats_ms\tproc_cpu_ms\tmain_cpu_ms\tpage_faults\tprivate_kb\t"
                               "fs_reads\tfs_kb\tfs_ms\tsnd_banks\tsnd_kb\tsnd_seqs\t"
                               "gsq_kb\th2l_kpx\tlazy_mat_kb\tclut_loads\t"
                               "gpu_batches\trt_creates\trt_loads\trt_writebacks\tup_kb\tdown_kb\tdownloads\t"
                               "download_ms\tkick_ms\ttex_decodes\t"
                               "nr_draws\tnr_tex_decodes\tnr_mesh_uploads\tnr_lazy_decodes\tpresents\tnew_images\tthreads\n");
        have = 1;
        memcpy(prev, v, sizeof v);
        R.fstats_t0 = now;
    }
    fprintf(R.field_stats, "%llu\t%.3f\t%.3f", (unsigned long long)R.st.fields, now - R.fstats_t0, self_ms);
    for (int i = 0; i < FST_N; i++) {
        double d = v[i] - prev[i]; /* every column is a delta (private_kb included) */
        if (i <= 1 || i == 6 || i == 21 || i == 22)
            fprintf(R.field_stats, "\t%.3f", d);
        else
            fprintf(R.field_stats, "\t%.0f", d);
    }
    /* threads: start address : tid : CPU ms this field (>= 0.5 ms; "m" = this thread) */
    fputc('\t', R.field_stats);
    int any = 0;
    for (int i = 0; i < sys.nthr; i++) {
        double d = thr_tid[i] == sys.tid[i] ? sys.thr_cpu_ms[i] - thr_prev[i] : 0.0;
        thr_tid[i] = sys.tid[i];
        thr_prev[i] = sys.thr_cpu_ms[i];
        if (d >= 0.5) {
            fprintf(R.field_stats, "%s%08x:%u:%.1f%s", any ? "," : "", sys.start[i], sys.tid[i], d,
                    sys.tid[i] == sys.main_tid ? "m" : "");
            any = 1;
        }
    }
    if (!any)
        fputc('-', R.field_stats);
    fputc('\n', R.field_stats);
    memcpy(prev, v, sizeof v);
    R.fstats_t0 = now;
    if (R.st.fields % 4096 == 0)
        fflush(R.field_stats);
}

int rg_runtime_run_field(void)
{
    if (!R.inited)
        return PS2K_RUN_ERROR + 1;
    if (R.finished)
        return R.last_rc;
    if (!R.started) {
        int prio = R.cfg.main_priority;
        if (prio < 0 || prio > PS2K_PRIO_MAX)
            prio = 1;
        if (ps2k_start(rg_ps2_main, NULL, prio) != 0) {
            R.finished = 1;
            R.last_rc = PS2K_RUN_ERROR + 1;
            return R.last_rc;
        }
        R.started = 1;
    }
    if (R.field_times && R.field_t0 == 0.0)
        R.field_t0 = R.field_end_ms = wall_ms();
    if (R.field_times) R.field_out_ms = wall_ms() - R.field_end_ms;
    rec_field_start();
    for (int ci = 0; ci < R.ncensus; ci++)
        if (R.st.fields + 1 == R.census_r[ci][0]) {
            gsq_drain();
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
            /* (no GS model: no feature census) */
#else
            gs_features_begin();
#endif
#if !RG_NATIVE_ONLY
            vif_census_begin();
#endif
        }
    double tpace = R.field_times ? wall_ms() : 0.0;
    pace_before_field(); /* paced mode: until host time owes this phase */
    double ts0 = R.field_times ? wall_ms() : 0.0;
    if (R.field_times) R.field_pace_ms = ts0 - tpace;
    int rc = ps2k_step(ps2k_vblank_count() + 1);
    rg_threads_field_end(); /* native threads: no host job in flight at a field boundary */
    if (R.field_times) R.field_step_ms = wall_ms() - ts0;
    if (rc != PS2K_RUN_YIELD) {
        ps2k_finish(rc);
        R.finished = 1;
        R.last_rc = rc + 1;
        host_half();
        return R.last_rc;
    }
    R.st.fields++;
    host_half();
    if (R.ndump)
        dump_field();
#if RT_IP
    if ((R.ip_sim_hz > 0.0 || R.ip_check) && nr_ip_on())
        ip_sim_field();
#endif
    for (int ci = 0; ci < R.ncensus; ci++)
        if (R.st.fields == R.census_r[ci][1]) {
            char cp[600];
            gsq_drain();
            snprintf(cp, sizeof cp, "%s/f%llu-%llu_gs.tsv", R.census_dir, (unsigned long long)R.census_r[ci][0],
                     (unsigned long long)R.census_r[ci][1]);
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
            (void)cp;
#else
            gs_features_dump(cp);
#endif
            snprintf(cp, sizeof cp, "%s/f%llu-%llu_vu.tsv", R.census_dir, (unsigned long long)R.census_r[ci][0],
                     (unsigned long long)R.census_r[ci][1]);
#if !RG_NATIVE_ONLY
            vif_census_dump(cp);
#endif
        }
    rec_field_end();
    if (R.field_stats)
        fstats_field();
    if (R.field_times) {
        double now = wall_ms();
        double gw = gsq_wait_ms();
        fprintf(R.field_times, "%llu\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n",
                (unsigned long long)R.st.fields, now - R.field_t0, R.field_step_ms, R.field_read_ms,
                R.field_present_ms, gw - R.field_gswait0, R.field_pace_ms, R.field_sync_ms, R.field_pump_ms,
                R.field_audio_ms, R.field_post_ms, R.field_out_ms);
        R.field_gswait0 = gw;
        R.field_read_ms = R.field_present_ms = 0.0;
        R.field_t0 = R.field_end_ms = now;
        if (R.st.fields % 100 == 0)
            fflush(R.field_times);
    }
    return R.quit ? RG_RUN_QUIT : 0;
}

int rg_runtime_run(uint64_t max_fields)
{
    int rc = 0;
    for (uint64_t k = 0; !max_fields || k < max_fields; k++) {
        rc = rg_runtime_run_field();
        if (rc)
            break;
    }
    return rc;
}

void rg_runtime_request_quit(void) { R.quit = 1; }

/* ---------------------------------------------------------------- shutdown */
void rg_runtime_shutdown(void)
{
    if (!R.inited)
        return;
    if (R.started && !R.finished && ps2k_running())
        ps2k_finish(PS2K_RUN_STOPPED);
    pace_report();
    if (R.pace_log) {
        fclose(R.pace_log);
        R.pace_log = NULL;
    }
    if (R.present_log) {
        fclose(R.present_log);
        R.present_log = NULL;
    }
    /* IOP side: flush the cards, eject the disc, drop the hooks into us */
#if RG_IOP_ORACLE
    if (rg_iop_hle())
        iop_hle_set_post_install(NULL, NULL);
#endif
    rg_iop_report(R.cfg.quiet);
    if (mccard_inited())
        mccard_shutdown();
    rg_pad_set_input_source(NULL, NULL);
    rg_pad_set_rumble_hook(NULL, NULL);
#if RG_IOP_ORACLE
    cdvd_drive_set_wait_hook(NULL, NULL);
    sceCdHleUnmount();
    rg_fs_oracle_stop();
#endif
    if (rg_fs_mounted() && !R.cfg.quiet) {
        rg_fs_stats fs;
        rg_fs_get_stats(&fs);
        fprintf(stderr, "rg_fs: %llu reads (%llu async), %.1f MB, %.1f ms host I/O, %llu opens, "
            "%llu misses, %llu errors\n",
            (unsigned long long)fs.reads, (unsigned long long)fs.async_reads, fs.bytes / 1e6,
            fs.read_ns / 1e6, (unsigned long long)fs.opens, (unsigned long long)fs.open_misses,
            (unsigned long long)fs.errors);
    }
    rg_fs_unmount();
    ps2k_shutdown();
#if !RG_NATIVE_ONLY
    hwbus_init();
#endif
#ifdef RG_HAVE_NATIVE_RENDER
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    nr_hw_bind_gs(NULL, NULL, NULL);
#else
    nr_hw_bind(NULL, NULL);
#endif
#endif
    sce_graphics_bind(NULL, NULL);
#if !RG_NATIVE_ONLY
    if (R.dmac)
        dmac_destroy(R.dmac);
#if RG_VU0_MICRO_BIND
    rg_vu0_micro_bind(NULL);
#endif
    vif_free(&R.vif0);
    vif_free(&R.vif1);
#endif
    if (R.rec) {
#if !(defined(RG_NATIVE_GS) && RG_NATIVE_GS)
        R.gs->rec = NULL;
#endif
        fclose(R.rec);
        R.rec = NULL;
    }
    if (R.gs && gsq_on()) {
        uint64_t as[4];
        gsq_stats(as);
        if (!R.cfg.quiet)
            fprintf(stderr, "rg_runtime: GS worker: %llu entries, %llu MB, %llu drains, %llu packets run synchronously\n",
                    (unsigned long long)as[0], (unsigned long long)(as[1] >> 20), (unsigned long long)as[2],
                    (unsigned long long)as[3]);
#if !(defined(RG_NATIVE_GS) && RG_NATIVE_GS)   /* (the GS model's upload counters) */
        uint64_t el[4];
        gs_xfer_elide_stats(R.gs, el);
        if (!R.cfg.quiet && el[0])
            fprintf(stderr, "rg_runtime: GS uploads: %llu host->local transfers, %llu hashed, %llu elided (%.1f MB, already in local memory)\n",
                    (unsigned long long)el[0], (unsigned long long)el[3], (unsigned long long)el[1], (double)el[2] / 1e6);
        if (!R.cfg.quiet) {
            uint64_t lz[8];
            gs_mem_lazy_stats(R.gs, lz);
            if (lz[0])
                fprintf(stderr, "rg_runtime: GS lazy transfers: %llu pending (%.1f MB), %llu written later (%.1f MB; %llu by the renderer "
                                "without hooks), %llu replaced unread, %llu refused by the renderer, %llu textures served to native draws\n",
                        (unsigned long long)lz[0], (double)lz[3] / 1e6, (unsigned long long)lz[1], (double)lz[4] / 1e6,
                        (unsigned long long)lz[7], (unsigned long long)lz[2], (unsigned long long)lz[5], (unsigned long long)lz[6]);
        }
#endif
        if (!R.cfg.quiet && R.overlap)
            fprintf(stderr, "rg_runtime: GS overlap: %llu fields overlapped, %llu drained at the field end, %.0f ms waited for the worker\n",
                    (unsigned long long)R.ov_fields, (unsigned long long)R.ov_synced, gsq_wait_ms());
        gsq_stop();
    }
    gpu_stop();
    if (R.field_times)
        fclose(R.field_times);
    if (R.field_stats)
        fclose(R.field_stats);
    if (g_hash_log) { fclose(g_hash_log); g_hash_log = NULL; }
    if (R.alog) {
        fclose(R.alog);
#if RG_IOP_ORACLE
        cdvd_set_io_clock(NULL);
#endif
    }

    if (R.gs)
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
        free(R.gs);
#else
        gs_destroy(R.gs);
#endif
    rg_crt0_shutdown();
    if (R.host)
        rg_host_destroy(R.host);
    if (R.have_script)
        rg_input_script_free(&R.script);
    wav_close();
    free(R.audio);
    free(R.frame);
    rg_runtime_stats st = R.st;
    memset(&R, 0, sizeof R); /* service hooks live outside R and survive */
    R.st = st; /* stats stay readable after shutdown */
}

int rg_runtime_screenshot(const char *path, uint64_t *hash, uint32_t *w, uint32_t *h)
{
    uint32_t ww = 0, hh = 0;
    if (R.gs)
        gsq_drain();
    if (!R.gs || !R.frame || read_display(&ww, &hh) != 0)
        return -1;
    if (hash) {
        *hash = 0xcbf29ce484222325ull;
        fold(hash, R.frame, (size_t)ww * hh * 4);
    }
    if (w) *w = ww;
    if (h) *h = hh;
    return path ? rg_png_write(path, R.frame, ww, hh) : 0;
}

const uint32_t *rg_runtime_read_display(uint32_t *w, uint32_t *h)
{
    uint32_t ww = 0, hh = 0;
    if (R.gs)
        gsq_drain();
    if (!R.gs || !R.frame || read_display(&ww, &hh) != 0)
        return NULL;
    if (w) *w = ww;
    if (h) *h = hh;
    return R.frame;
}

/* ---------------------------------------------------------------- access */
const rg_runtime_stats *rg_runtime_get_stats(void) { return &R.st; }
rg_host *rg_runtime_host(void) { return R.host; }
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
gs_state *rg_runtime_gs(void) { return NULL; }   /* (no GS model: nr_gs_state() is the state block) */
#else
gs_state *rg_runtime_gs(void) { return R.gs; }
#endif
dmac_state *rg_runtime_dmac(void) { return R.dmac; }
vu_state *rg_runtime_vu1(void) { return &R.vu1; }
struct gpu_renderer *rg_runtime_gpu(void) { return R.gpu; }
const rg_runtime_config *rg_runtime_get_config(void) { return &R.cfg; }

/* ---------------------------------------------------------------- save states
 * The runtime's part of a port save state (docs/TEST-FIXTURES.md; src/savestate
 * registers these as the "runtime" hook).  R itself is never written back raw:
 * most of it is this process's host side (host shell, renderer, files, input
 * script, config).  The blob holds the guest-visible part: the run's progress
 * and statistics (run_hash continues), VU0/VU1 and VIF0/VIF1 (inline in R).
 * The GS model lives in the state heap and comes back raw; its host side (the
 * worker thread, the renderer hooks, the recorder) is rebuilt here. */
#define RSS_MAGIC 0x31535352u /* "RSS1" */

typedef struct rss_blob {
    uint32_t magic, bytes, vu_bytes, vif_bytes;
    int started, finished, last_rc, pad;
    rg_runtime_stats st;
    vu_state vu0, vu1;
    vif_state vif0, vif1;
} rss_blob;

static int rss_async_was_on;

int rg_runtime_ss_can_save(char *why, size_t cap)
{
    if (!R.inited || !R.gs) {
        snprintf(why, cap, "the runtime is not initialised");
        return -1;
    }
    if (!R.started || R.finished) {
        snprintf(why, cap, "%s", !R.started ? "no field has run yet" : "the game has stopped");
        return -1;
    }
    if (R.rec || R.ncensus) {
        snprintf(why, cap, "a GS recording / census is active");
        return -1;
    }
    return 0;
}

#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
/* no GS model: the native state block and the device's local memory travel in the runtime's blob
 * (runtime.c's allocations are host memory, not part of the state heap's raw sections) */
#define RSS_GS_BYTES (sizeof(nr_gs) + GS_VRAM_BYTES)
#else
#define RSS_GS_BYTES 0
#endif
size_t rg_runtime_ss_size(void) { return sizeof(rss_blob) + RSS_GS_BYTES; }

/* before any section is written: everything queued has run, and the GS
 * model's local memory holds what the renderer drew */
void rg_runtime_ss_pre_save(void)
{
    if (R.gs)
        gsq_drain();
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    if (R.gpu && R.gs_img)
        gpu_mem_save(R.gpu, R.gs_img);   /* local memory is the GPU's: into the state heap */
#elif defined(RG_HAVE_GPU)
    if (R.gpu)
        gpu_sync(R.gpu);
#endif
}

int rg_runtime_ss_save(void *buf, size_t cap)
{
    if (cap < sizeof(rss_blob) + RSS_GS_BYTES)
        return -1;
    rss_blob *b = (rss_blob *)buf;
    memset(b, 0, sizeof *b);
    b->magic = RSS_MAGIC;
    b->bytes = (uint32_t)sizeof *b;
    b->vu_bytes = (uint32_t)sizeof(vu_state);
    b->vif_bytes = (uint32_t)sizeof(vif_state);
    b->started = R.started;
    b->finished = R.finished;
    b->last_rc = R.last_rc;
    b->st = R.st;
    b->vu0 = R.vu0;
    b->vu1 = R.vu1;
    b->vif0 = R.vif0;
    b->vif1 = R.vif1;
    b->vu0.blk = b->vu1.blk = NULL; /* host translation caches: not state */
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    if (!R.gs || !R.gs_img)
        return -1;
    memcpy((uint8_t *)buf + sizeof *b, R.gs, sizeof(nr_gs));
    memcpy((uint8_t *)buf + sizeof *b + sizeof(nr_gs), R.gs_img, GS_VRAM_BYTES);
    return (int)(sizeof *b + RSS_GS_BYTES);
#else
    return (int)sizeof *b;
#endif
}

/* before the raw sections overwrite the GS model: stop this process's GS
 * worker and take the renderer off it */
void rg_runtime_ss_pre_load(void)
{
    rss_async_was_on = R.gs && gsq_on();
    if (rss_async_was_on)
        gsq_stop();
#if defined(RG_HAVE_GPU) && !(defined(RG_NATIVE_GS) && RG_NATIVE_GS)
    if (R.gpu)
        gpu_detach(R.gpu);
#endif
}

int rg_runtime_ss_load(const void *buf, size_t n)
{
    const rss_blob *b = (const rss_blob *)buf;
    if (n != sizeof(rss_blob) + RSS_GS_BYTES || b->magic != RSS_MAGIC || b->bytes != sizeof(rss_blob) ||
        b->vu_bytes != sizeof(vu_state) || b->vif_bytes != sizeof(vif_state))
        return -1;
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    if (R.gs && R.gs_img) {
        memcpy(R.gs, (const uint8_t *)buf + sizeof *b, sizeof(nr_gs));
        memcpy(R.gs_img, (const uint8_t *)buf + sizeof *b + sizeof(nr_gs), GS_VRAM_BYTES);
    }
#endif
    /* this process's configuration of the VUs and VIFs stays */
    vu_state cfg0 = R.vu0, cfg1 = R.vu1;
    vif_state vcfg0 = R.vif0, vcfg1 = R.vif1;
    R.started = b->started;
    R.finished = b->finished;
    R.last_rc = b->last_rc;
    R.st = b->st;
    R.vu0 = b->vu0;
    R.vu1 = b->vu1;
    R.vif0 = b->vif0;
    R.vif1 = b->vif1;
    vu_state *v[2] = {&R.vu0, &R.vu1}, *c[2] = {&cfg0, &cfg1};
    for (int i = 0; i < 2; i++) {
        v[i]->int_branch_quirk = c[i]->int_branch_quirk;
        v[i]->break_on_dt = c[i]->break_on_dt;
        v[i]->blocks = c[i]->blocks;
        v[i]->blocks_check = c[i]->blocks_check;
        v[i]->stats_print = c[i]->stats_print;
        v[i]->blk = NULL;   /* a fresh translation cache (the old one was the saver's) */
        v[i]->vu1 = c[i]->vu1;
        v[i]->gif_sink = c[i]->gif_sink;
        v[i]->gif_user = c[i]->gif_user;
    }
    vif_state *w[2] = {&R.vif0, &R.vif1}, *d[2] = {&vcfg0, &vcfg1};
    for (int i = 0; i < 2; i++) {
        w[i]->vu = d[i]->vu;
        w[i]->vu_cycle_budget = d[i]->vu_cycle_budget;
        w[i]->stall_on_irq = d[i]->stall_on_irq;
        w[i]->gif_sink = d[i]->gif_sink;
        w[i]->gif_user = d[i]->gif_user;
        w[i]->mpg_hook = d[i]->mpg_hook;
        w[i]->mpg_user = d[i]->mpg_user;
        w[i]->irq_fn = d[i]->irq_fn;
        w[i]->irq_user = d[i]->irq_user;
        w[i]->ahead = NULL;
        w[i]->ahead_n = 0;
    }
    return 0;
}

/* after every hook's load: the GS model's host side for this process */
void rg_runtime_ss_post_load(void)
{
    if (!R.gs)
        return;
#if defined(RG_NATIVE_GS) && RG_NATIVE_GS
    if (R.gpu) {
        gpu_attach(R.gpu, R.gs);        /* the restored state block */
        if (R.gs_img)
            gpu_mem_load(R.gpu, R.gs_img);   /* the saved local memory back on the GPU */
    }
#else
    R.gs->async = NULL;                 /* the saver's worker (host heap) */
    memset(&R.gs->hooks, 0, sizeof R.gs->hooks);
    R.gs->sw_raster = 1;
    R.gs->rec = R.rec ? rec_cb : NULL;
    R.gs->rec_user = NULL;
#ifdef RG_HAVE_GPU
    if (R.gpu)
        gpu_attach(R.gpu, R.gs);        /* local memory is authoritative again */
#endif
#endif
    if (rss_async_was_on)
        gsq_start();
}
