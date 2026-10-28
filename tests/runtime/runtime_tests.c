/* SPDX-License-Identifier: CC0-1.0
 * tests/runtime: rg_runtime glue (docs/RUNTIME.md "Tests").
 *   rg-runtime-tests <name> [args]      ctest -L runtime
 * Exit 0 pass, 1 fail, 77 skipped. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "demo_guest.h"
#include "gs.h"
#include "host.h"
#include "libgraph.h"
#include "mcserv.h"
#include "padman.h"
#include "ps2k.h"
/* last: it #defines DMAC_* names that dmac.h declares as enumerators */
#include "eekernel.h"
#include "rg_runtime.h"
#include "rg_iop.h"
#include "sif.h"
#include "libsif.h"
#include "snd.h"
#ifdef RG_HAVE_GPU
#include <stdint.h>
#include "gpu.h"
#endif

static int g_fail;
#define CHECK(c, ...)                                                        \
    do {                                                                     \
        if (!(c)) {                                                          \
            fprintf(stderr, "%s:%d: CHECK failed: %s: ", __FILE__, __LINE__, #c); \
            fprintf(stderr, __VA_ARGS__);                                    \
            fprintf(stderr, "\n");                                           \
            g_fail++;                                                        \
        }                                                                    \
    } while (0)

static const char *g_tmp = "runtime-tmp";

static void base_config(rg_runtime_config *c)
{
    rg_runtime_default_config(c);
    c->headless = 1;
    c->throttle = 0;
    c->quiet = 1;
    c->gpu = 0; /* the software GS, whatever $RG_GPU says (gpu_smoke sets its own) */
    static char data[256], saves[256];
    snprintf(data, sizeof data, "%s/disc", g_tmp);
    snprintf(saves, sizeof saves, "%s/saves", g_tmp);
    c->data_dir = data;
    c->saves_dir = saves;
}

static void make_dirs(void)
{
    char d[256];
#ifdef _WIN32
    snprintf(d, sizeof d, "if not exist \"%s\" mkdir \"%s\"", g_tmp, g_tmp);
#else
    snprintf(d, sizeof d, "mkdir -p '%s'", g_tmp);
#endif
    if (system(d) != 0) { /* the fixture writer reports a real failure */ }
    snprintf(d, sizeof d, "%s/disc", g_tmp);
    if (rg_demo_write_fixture(d) != 0) {
        fprintf(stderr, "cannot write fixture %s\n", d);
        exit(2);
    }
}

/* ------------------------------------------------------------ init_order */
static int idle_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    for (;;)
        sceGsSyncV(0);
    return 0;
}

static int t_init_order(void)
{
    rg_runtime_config c;
    base_config(&c);
    c.entry = idle_entry;
    for (int round = 0; round < 2; round++) { /* init -> shutdown -> init works */
        CHECK(rg_runtime_init(&c) == 0, "init round %d", round);
        int order[RG_INIT_COUNT];
        int n = rg_runtime_init_order(order, RG_INIT_COUNT);
        CHECK(n == RG_INIT_COUNT - 1, "%d steps", n);
        for (int i = 0; i < n; i++)
            CHECK(order[i] == i + 1, "step %d is %s, want %s", i, rg_runtime_init_step_name(order[i]),
                  rg_runtime_init_step_name(i + 1));
        /* RG_IOP=native (docs/NATIVE-IOP.md): no SIF boot, no servers, and running
         * fields never enters the IOP / SIF HLE */
        if (rg_iop_native()) {
            uint64_t h0 = rg_iop_hle_total_native();
            CHECK(!rg_sif_booted(), "native: SIF not booted");
            CHECK(rg_runtime_run(5) == 0, "5 fields");
            CHECK(rg_iop_hle_total_native() == h0, "native: %llu HLE entries",
                  (unsigned long long)(rg_iop_hle_total_native() - h0));
            /* (these probes are HLE calls themselves: after the count) */
            CHECK(!padman_installed() && !mcserv_installed(), "native: no padman / mcserv");
            rg_runtime_shutdown();
            CHECK(!rg_runtime_inited(), "shut down");
            continue;
        }
        /* what the steps must have left behind */
        CHECK(rg_sif_booted(), "SIF booted");
        CHECK(padman_installed(), "padman installed at boot (not first Init)");
        CHECK(mcserv_installed(), "mcserv installed at boot");
        const sif_server_info *sdr = sif_server_find(0x80000701u);
        const sif_server_info *pcm = sif_server_find(0x00123456u);
        CHECK(sdr && pcm, "sound servers registered");
        CHECK(sdr && strcmp(sdr->name, "sdr_driver") == 0 && pcm && strcmp(pcm->name, "pcm_mixer") == 0,
              "real sound HLE, not placeholders (%s / %s)", sdr ? sdr->name : "-", pcm ? pcm->name : "-");
        CHECK(sif_now() == ps2k_now(), "SIF clock hook = kernel clock");
        CHECK(rg_crt0_ram()->heap_start != NULL, "game heap");
        CHECK(rg_runtime_gs() && rg_runtime_dmac(), "graphics models");
        CHECK(ps2k_vblank_start_line() == 240, "start line");
        /* a few fields run, and SIF time follows the kernel */
        CHECK(rg_runtime_run(5) == 0, "5 fields");
        CHECK(ps2k_vblank_count() == 5, "vblank %llu", (unsigned long long)ps2k_vblank_count());
        CHECK(sif_now() == ps2k_now(), "SIF clock after running");
        rg_runtime_shutdown();
        CHECK(!rg_runtime_inited(), "shut down");
    }
    return g_fail;
}

/* ---------------------------------------------------------- vblank_rate */
static uint64_t g_obs_start, g_obs_end, g_obs_bad_time;
static void test_observer(int which, uint64_t field, void *u)
{
    (void)u;
    uint64_t want = which == PS2K_VBLANK_START ? ps2k_vblank_start_time(field) : ps2k_vblank_end_time(field);
    if (ps2k_now() != want)
        g_obs_bad_time++;
    if (which == PS2K_VBLANK_START)
        g_obs_start++;
    else
        g_obs_end++;
}

static int t_vblank_rate(int control)
{
    rg_runtime_config c;
    base_config(&c);
    c.entry = idle_entry;
    CHECK(rg_runtime_init(&c) == 0, "init");
    ps2k_add_vblank_observer(test_observer, NULL);
    /* run whole fields until one virtual second (and then ten) has passed */
    const uint64_t sec = PS2K_BUSCLK;
    uint64_t starts_1s = 0, ends_1s = 0;
    int stepped_one = 1;
    while (ps2k_now() < 10 * sec) {
        uint64_t before = ps2k_vblank_count();
        if (rg_runtime_run_field() != 0)
            break;
        if (ps2k_vblank_count() != before + 1)
            stepped_one = 0;
        if (ps2k_now() <= sec) {
            starts_1s = g_obs_start;
            ends_1s = g_obs_end;
        }
    }
    /* exact NTSC arithmetic: VBLANK_START k at floor((k*F + 240*H)), END at (k+1)*F,
     * F = 2,460,060 cycles (BUSCLK/59.94).  In [0, 1 s]: starts k = 0..59, ends k = 0..58. */
    uint64_t want_s = 0, want_e = 0;
    while (ps2k_vblank_start_time(want_s) <= sec) want_s++;
    while (ps2k_vblank_end_time(want_e) <= sec) want_e++;
    CHECK(want_s == 60 && want_e == 59, "formula %llu/%llu", (unsigned long long)want_s, (unsigned long long)want_e);
    if (control) /* DELIBERATELY WRONG: a 60.00 Hz field would give 60 ends in the first second */
        want_e = 60;
    CHECK(starts_1s == want_s, "starts in 1 s: %llu want %llu", (unsigned long long)starts_1s, (unsigned long long)want_s);
    CHECK(ends_1s == want_e, "ends in 1 s: %llu want %llu", (unsigned long long)ends_1s, (unsigned long long)want_e);
    CHECK(g_obs_bad_time == 0, "%llu observer calls off their exact time", (unsigned long long)g_obs_bad_time);
    CHECK(stepped_one, "every run_field advanced exactly one VBLANK_START");
    /* ten seconds: 599.4 fields -> 600 starts at or before 10 s (k = 0..599 since start(599) = 9.9937 s) */
    uint64_t want10 = 0;
    while (ps2k_vblank_start_time(want10) <= 10 * sec) want10++;
    const rg_runtime_stats *st = rg_runtime_get_stats();
    CHECK(st->vblank_start == g_obs_start && st->vblank_end == g_obs_end, "runtime observer counts agree");
    double rate = (double)(g_obs_start - 1) * (double)sec /
                  (double)(ps2k_vblank_start_time(g_obs_start - 1) - ps2k_vblank_start_time(0));
    CHECK(rate > 59.9399 && rate < 59.9401, "rate %.6f Hz", rate);
    printf("vblank: 1 s: %llu starts %llu ends; %llu fields, %.6f Hz\n", (unsigned long long)starts_1s,
           (unsigned long long)ends_1s, (unsigned long long)g_obs_start, rate);
    rg_runtime_shutdown();
    return g_fail;
}

/* ---------------------------------------------------------- audio_field */
static int t_audio_field(void)
{
    rg_runtime_config c;
    base_config(&c);
    c.entry = idle_entry;
    CHECK(rg_runtime_init(&c) == 0, "init");
    const rg_runtime_stats *st = rg_runtime_get_stats();
    uint64_t first = 0, sum = 0, minf = ~0ull, maxf = 0;
    const int N = 600;
    for (int k = 0; k < N; k++) {
        CHECK(rg_runtime_run_field() == 0, "field %d", k);
        uint64_t got = st->audio_frames_last;
        if (k == 0) {
            first = got;
            continue;
        }
        sum += got;
        if (got < minf) minf = got;
        if (got > maxf) maxf = got;
    }
    /* frames rendered up to VBLANK_START k = floor(t_k / 3072), 3072 cycles per 48 kHz frame */
    uint64_t want_first = ps2k_vblank_start_time(0) / SND_CYCLES_PER_FRAME;
    uint64_t want_sum = ps2k_vblank_start_time(N - 1) / SND_CYCLES_PER_FRAME - want_first;
    CHECK(first == want_first, "first field %llu want %llu", (unsigned long long)first, (unsigned long long)want_first);
    CHECK(sum == want_sum, "sum %llu want %llu", (unsigned long long)sum, (unsigned long long)want_sum);
    double avg = (double)sum / (N - 1);
    CHECK(avg > 800.79 && avg < 800.81, "avg %.4f", avg);
    CHECK(minf >= 800 && maxf <= 801, "per field %llu..%llu", (unsigned long long)minf, (unsigned long long)maxf);
    CHECK(st->audio_dropped == 0, "dropped %llu", (unsigned long long)st->audio_dropped);
    CHECK(rg_host_audio_pushed_total(rg_runtime_host()) == st->audio_frames, "all frames reached the host");
    printf("audio: first %llu, then avg %.4f frames/field (%llu..%llu)\n", (unsigned long long)first, avg,
           (unsigned long long)minf, (unsigned long long)maxf);
    rg_runtime_shutdown();
    return g_fail;
}

/* ----------------------------------------------------------- pad_script */
static int t_pad_script(int control)
{
    char path[256];
    snprintf(path, sizeof path, "%s/pad_script.txt", g_tmp);
    FILE *f = fopen(path, "wb");
    if (!f) return 2;
    fputs("# CROSS held on kernel VBlanks 40..80, START on 100\n40 80 CROSS\n100 START\n", f);
    fclose(f);
    rg_runtime_config c;
    base_config(&c);
    c.input_script = path;
    c.entry = rg_demo_entry;
    rg_demo_config dc;
    rg_demo_default_config(&dc);
    dc.parts = RG_DEMO_PAD;
    rg_demo_setup(&dc);
    CHECK(rg_runtime_init(&c) == 0, "init");
    CHECK(rg_runtime_run(130) == 0, "run");
    const rg_demo_result *r = rg_demo_get_result();
    CHECK(r->pad_stable_field >= 0 && r->pad_stable_field < 10, "stable at field %d", r->pad_stable_field);
    /* every read: the word the script gives for the VBlank padman's buffer
     * was written at (libpad reads padman's buffer for the current VBlank) */
    int first_cross = -1, last_cross = -1, starts = 0, bad = 0, reads = 0;
    for (int fl = 0; fl < 130; fl++) {
        uint64_t vb = r->pad_vblank[fl];
        if (!vb) continue;
        reads++;
        uint16_t w = r->pad_word[fl];
        uint16_t want = (vb >= 40 && vb <= 80 ? 0x0040 : 0) | (vb == 100 ? 0x0800 : 0);
        if (control) /* DELIBERATELY WRONG: the script one VBlank later */
            want = (vb >= 41 && vb <= 81 ? 0x0040 : 0) | (vb == 101 ? 0x0800 : 0);
        if (w != want) bad++;
        if (w & 0x0040) { if (first_cross < 0) first_cross = (int)vb; last_cross = (int)vb; }
        if (w & 0x0800) starts++;
    }
    CHECK(reads > 100, "%d reads", reads);
    CHECK(bad == 0, "%d reads differ from the script", bad);
    CHECK(first_cross == 40 && last_cross == 80, "CROSS on VBlanks %d..%d", first_cross, last_cross);
    CHECK(starts == 1, "START seen %d times", starts);
    /* CROSS drives the vibration: aligned well before VBlank 40, on then off */
    uint8_t sm = 9, lg = 9;
    rg_host_rumble_state(rg_runtime_host(), 0, &sm, &lg);
    CHECK(r->rumble_set, "actuators aligned");
    CHECK(rg_runtime_get_stats()->rumble_changes >= 2, "rumble changes %llu",
          (unsigned long long)rg_runtime_get_stats()->rumble_changes);
    CHECK(sm == 0 && lg == 0, "motors off after CROSS released (%u %u)", sm, lg);
    printf("pad: %d reads, CROSS %d..%d, rumble changes %llu\n", reads, first_cross, last_cross,
           (unsigned long long)rg_runtime_get_stats()->rumble_changes);
    rg_runtime_shutdown();
    return g_fail;
}

/* ----------------------------------------------------------- cdvd_async */
static int t_cdvd_async(int real)
{
    rg_runtime_config c;
    base_config(&c);
    if (real) {
        const char *d = getenv("RG_DATA");
        if (!d || !*d) {
            printf("RG_DATA not set: skipped\n");
            return 77;
        }
        c.data_dir = d;
    }
    c.entry = rg_demo_entry;
    rg_demo_config dc;
    rg_demo_default_config(&dc);
    dc.parts = RG_DEMO_CD;
    rg_demo_setup(&dc);
    CHECK(rg_runtime_init(&c) == 0, "init");
    const rg_demo_result *r = rg_demo_get_result();
    for (int k = 0; k < 30 && r->cd_ok == 0; k++)
        rg_runtime_run_field();
    const rg_runtime_stats *st = rg_runtime_get_stats();
    CHECK(r->cd_ok == 1, "read completed (%d: %s)", r->cd_ok, r->cd_text);
    CHECK(strcmp(r->cd_text, "BOOT2 = cdrom0:\\SCUS_974.90;1") == 0, "SYSTEM.CNF: \"%s\"", r->cd_text);
    CHECK(r->cd_busy_after_issue == 1, "sceCdSync(1) busy right after issue, no data yet (%d)", r->cd_busy_after_issue);
    /* completion on the kernel loop at exactly the drive's due time:
     * 1000 us command + 370 us per sector = 1370 us = 202,014.7 cycles */
    uint64_t dt = r->cd_due_cycles - r->cd_issue_cycles;
    CHECK(dt >= 201867 && dt <= 202016, "due - issue = %llu cycles", (unsigned long long)dt);
    CHECK(r->cd_done_cycles == r->cd_due_cycles, "woke at %llu, due %llu", (unsigned long long)r->cd_done_cycles,
          (unsigned long long)r->cd_due_cycles);
    CHECK(st->cdvd_completions == 1 && st->cdvd_waits >= 1, "device completions %llu waits %llu",
          (unsigned long long)st->cdvd_completions, (unsigned long long)st->cdvd_waits);
    CHECK(r->cd_sema_after == r->cd_sema_before, "no sema id left behind (%d %d)", r->cd_sema_before,
          r->cd_sema_after);
    printf("cdvd: lsn %u \"%s\" issue %llu done %llu (+%llu cycles)\n", r->cd_lsn, r->cd_text,
           (unsigned long long)r->cd_issue_cycles, (unsigned long long)r->cd_done_cycles, (unsigned long long)dt);
    rg_runtime_shutdown();
    return g_fail;
}

/* ------------------------------------------------------------ smoke_all */
static int t_smoke_all(void)
{
    rg_runtime_config c;
    base_config(&c);
    c.entry = rg_demo_entry;
    c.display_hash_every = 30;
    rg_demo_config dc;
    rg_demo_default_config(&dc);
    rg_demo_setup(&dc);
    CHECK(rg_runtime_init(&c) == 0, "init");
    CHECK(rg_runtime_run(90) == 0, "90 fields");
    const rg_demo_result *r = rg_demo_get_result();
    const rg_runtime_stats *st = rg_runtime_get_stats();
    CHECK(r->snd_ok == 1, "SE key-on accepted (%d)", r->snd_ok);
    CHECK(snd_get_stats()->key_ons >= 1, "key ons %u", snd_get_stats()->key_ons);
    CHECK(st->audio_peak > 1000, "audible after the key-on (peak %d)", st->audio_peak);
    CHECK(r->cd_ok == 1, "cd (%s)", r->cd_text);
    CHECK(r->pad_reads > 50, "pad reads %u", r->pad_reads);
    CHECK(r->gfx_frames >= 85, "gfx frames %u", r->gfx_frames);
    gs_state *gs = rg_runtime_gs();
    CHECK(gs->path[1].packets >= 85, "XGKICK packets on PATH1: %llu", (unsigned long long)gs->path[1].packets);
    CHECK(gs->stats.prims[6] >= 170, "sprites drawn %llu", (unsigned long long)gs->stats.prims[6]);
    uint64_t h = 0;
    uint32_t w = 0, hh = 0;
    CHECK(rg_runtime_screenshot(NULL, &h, &w, &hh) == 0 && w == 640 && hh == 448, "display %ux%u", w, hh);
    printf("smoke: snd peak %d, gfx %u frames, %llu sprites, display %ux%u\n", st->audio_peak, r->gfx_frames,
           (unsigned long long)gs->stats.prims[6], w, hh);
    rg_runtime_shutdown();
    return g_fail;
}

/* ------------------------------------------------------------ audio_wav */
/* RG_AUDIO_WAV: every frame the host got, as a 48 kHz s16 stereo WAV, and
 * <wav>.fields.tsv with one row per field (docs/SOUND.md "Validation"). */
static uint32_t rd32(const unsigned char *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }

static int t_audio_wav(void)
{
    char wav[300], tsv[320];
    snprintf(wav, sizeof wav, "%s/audio.wav", g_tmp);
    snprintf(tsv, sizeof tsv, "%s.fields.tsv", wav);
    remove(wav);
    remove(tsv);
#ifdef _WIN32
    _putenv_s("RG_AUDIO_WAV", wav);
#else
    setenv("RG_AUDIO_WAV", wav, 1);
#endif
    rg_runtime_config c;
    base_config(&c);
    c.entry = rg_demo_entry;
    rg_demo_config dc;
    rg_demo_default_config(&dc);
    rg_demo_setup(&dc);
    CHECK(rg_runtime_init(&c) == 0, "init");
    enum { N = 90 };
    static uint64_t want_end[N + 1];
    for (int k = 0; k < N; k++) {
        CHECK(rg_runtime_run_field() == 0, "field %d", k);
        /* field k+1 ends with everything rendered up to VBLANK_START k */
        want_end[k + 1] = ps2k_vblank_start_time((uint64_t)k) / SND_CYCLES_PER_FRAME;
    }
    rg_runtime_shutdown();
#ifdef _WIN32
    _putenv_s("RG_AUDIO_WAV", "");
#else
    unsetenv("RG_AUDIO_WAV");
#endif
    const rg_runtime_stats *st = rg_runtime_get_stats(); /* readable after shutdown */
    FILE *f = fopen(wav, "rb");
    CHECK(f != NULL, "no %s", wav);
    if (!f)
        return g_fail;
    unsigned char h[44];
    CHECK(fread(h, 1, 44, f) == 44, "short header");
    CHECK(!memcmp(h, "RIFF", 4) && !memcmp(h + 8, "WAVEfmt ", 8) && !memcmp(h + 36, "data", 4), "RIFF/WAVE/fmt/data tags");
    CHECK(rd32(h + 16) == 16 && h[20] == 1 && h[22] == 2 && h[34] == 16, "PCM, 2 channels, 16 bits");
    CHECK(rd32(h + 24) == 48000 && rd32(h + 28) == 192000 && h[32] == 4, "48000 Hz, 192000 B/s, align 4");
    uint32_t bytes = rd32(h + 40);
    CHECK(bytes == st->audio_frames * 4, "data %u bytes, host got %llu frames", bytes,
          (unsigned long long)st->audio_frames);
    CHECK(rd32(h + 4) == 36 + bytes, "RIFF size");
    int32_t peak = 0;
    uint64_t n = 0;
    int16_t s[2];
    while (fread(s, 4, 1, f) == 1) {
        for (int i = 0; i < 2; i++) {
            int32_t v = s[i] < 0 ? -(int32_t)s[i] : s[i];
            if (v > peak) peak = v;
        }
        n++;
    }
    fclose(f);
    CHECK(n == st->audio_frames, "frames in file %llu", (unsigned long long)n);
    CHECK(peak == st->audio_peak && peak > 1000, "peak %d, runtime %d (the demo SE is in the file)", peak,
          st->audio_peak);
    /* sidecar: one row per completed field, cumulative frames */
    FILE *t = fopen(tsv, "r");
    CHECK(t != NULL, "no %s", tsv);
    int rows = 0;
    unsigned long long last_field = 0, last_frames = 0;
    if (t) {
        char line[256];
        while (fgets(line, sizeof line, t)) {
            unsigned long long fi, kv, fr, cy;
            unsigned gv;
            if (line[0] == '#')
                continue;
            if (sscanf(line, "%llu %llu %u %llu %llu", &fi, &kv, &gv, &fr, &cy) == 5) {
                rows++;
                last_field = fi;
                last_frames = fr;
                uint64_t want = fi >= 1 && fi <= N ? want_end[fi] : ~0ull;
                CHECK(fr == want && cy >= want * SND_CYCLES_PER_FRAME, "field %llu: %llu frames, want %llu",
                      fi, fr, (unsigned long long)want);
            }
        }
        fclose(t);
    }
    CHECK(rows == N && last_field == (unsigned long long)N, "%d rows, last field %llu", rows, last_field);
    CHECK(last_frames == st->audio_frames, "last row %llu frames", last_frames);
    printf("audio_wav: %llu frames, peak %d, %d field rows\n", (unsigned long long)n, peak, rows);
    return g_fail;
}

/* ------------------------------------------------------------- crt0 */
static int g_ctor_calls;
static void ctor_a(void) { g_ctor_calls = g_ctor_calls * 10 + 1; }
static void ctor_b(void) { g_ctor_calls = g_ctor_calls * 10 + 2; }

static int t_crt0(void)
{
    rg_runtime_config c;
    base_config(&c);
    c.entry = NULL; /* the weak default rg_game_entry */
    CHECK(rg_runtime_init(&c) == 0, "init");
    const rg_ps2_ram *ram = rg_crt0_ram();
    /* the heap alone, page + 0x200 (== the retail start mod 4 KB), docs/NATIVE-CPU.md 8 */
    CHECK(((uintptr_t)ram->heap_start & 4095u) == (0x00528200u & 4095u), "heap start %p mod 4 KB",
          (void *)ram->heap_start);
    CHECK(rg_crt0_host_to_retail(ram->heap_start) == 0x00528200u &&
              rg_crt0_host_to_retail(ram->heap_end - 1) == 0x01FD0000u - 1 &&
              rg_crt0_host_to_retail(ram->heap_end) == 0 &&
              rg_crt0_retail_to_host(0x00528210u) == ram->heap_start + 0x10 &&
              rg_crt0_retail_to_host(0x00100000u) == NULL,
          "retail mapping");
    CHECK(ram->heap_end - ram->heap_start == 0x01FD0000 - 0x00528200, "heap size %ld",
          (long)(ram->heap_end - ram->heap_start));
    /* SysCalcFreeHeapMaybe_15e1d0 mallocs 0x2000000 - 0x2000 - 0x30000 - 0x528200 - 0x10 */
    CHECK((uint32_t)(ram->heap_end - ram->heap_start) >= 0x2000000u - 0x2000u - 0x30000u - 0x528200u,
          "the game's free-heap probe fits");
    extern void *EndOfHeap(void);
    extern void *sbrk(intptr_t);
    CHECK(EndOfHeap() == ram->heap_end, "EndOfHeap");
    uint8_t *p0 = (uint8_t *)sbrk(0x1000);
    CHECK(p0 == ram->heap_start, "first sbrk at the heap start");
    CHECK((uint8_t *)sbrk(0) == ram->heap_start + 0x1000, "break moved");
    CHECK(sbrk(0x7FFFFFFF) == (void *)-1, "over-allocation refused");
    CHECK((uint8_t *)sbrk(-0x1000) == ram->heap_start + 0x1000 && sbrk(0) == ram->heap_start, "shrink");
    uint32_t table[3] = {(uint32_t)(uintptr_t)ctor_a, (uint32_t)(uintptr_t)ctor_b, 0};
    extern void RunStaticCtors_100df0(void *, void *, void *, void *);
    RunStaticCtors_100df0(table, table + 2, NULL, NULL);
    CHECK(g_ctor_calls == 12, "ctors in table order (%d)", g_ctor_calls);
    /* the EE starts rg_ps2_main -> weak rg_game_entry -> exit: main exits in field 0 */
    int rc = rg_runtime_run_field();
    CHECK(rc == PS2K_RUN_MAIN_EXIT + 1, "rc %d", rc);
    CHECK(rg_ps2_exit_code() == RG_GAME_NOT_LINKED, "exit code %d", rg_ps2_exit_code());
    rg_runtime_shutdown();
    return g_fail;
}

/* ---------------------------------------------------------- kernel_glue */
static volatile int g_vbs_handler_ran, g_flag_seen_by_waiter, g_waits;
static int g_probe_ids[8];
static int vbs_handler(int cause)
{
    (void)cause;
    g_vbs_handler_ran++;
    return 0;
}

static void prober(void *a)
{
    (void)a;
    struct SemaParam sp = {0, 1, 0, 0, 0, 0};
    for (int i = 0; i < 8; i++) {
        int id = CreateSema(&sp);
        g_probe_ids[i] = id;
        DeleteSema(id);
        DelayThread(2000);
    }
}

static int glue_entry(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    AddIntcHandler(2, vbs_handler, -1);
    EnableIntc(2);
    struct ThreadParam tp;
    memset(&tp, 0, sizeof tp);
    tp.entry = (void *)prober;
    tp.initPriority = 50;
    StartThread(CreateThread(&tp), NULL);
    for (int i = 0; i < 4; i++) {
        int before = g_vbs_handler_ran;
        uint64_t vb = ps2k_vblank_count();
        sceGsSyncV(0);
        if (g_vbs_handler_ran == before + 1 && ps2k_vblank_count() == vb + 1 &&
            ps2k_now() == ps2k_vblank_start_time(vb))
            g_flag_seen_by_waiter++;
        g_waits++;
    }
    uint64_t t = ps2k_now() + 12345;
    ps2k_wait_until(t);
    if (ps2k_now() != t)
        g_flag_seen_by_waiter = -100;
    for (;;)
        sceGsSyncV(0);
    return 0;
}

static int t_kernel_glue(void)
{
    rg_runtime_config c;
    base_config(&c);
    c.entry = glue_entry;
    c.main_priority = 10;
    CHECK(rg_runtime_init(&c) == 0, "init");
    CHECK(rg_runtime_run(12) == 0, "run");
    CHECK(g_waits == 4, "waits %d", g_waits);
    CHECK(g_flag_seen_by_waiter == 4,
          "each sceGsSyncV woke once per VBLANK_START, at its exact time, after its handler (%d)",
          g_flag_seen_by_waiter);
    /* the waits take no game-visible id: a probe sema created (and deleted) during them
     * always gets id 0 (sema ids start at 0, last freed = first reused; VALIDATION.md 2c) */
    int same = 1;
    for (int i = 0; i < 8; i++)
        if (g_probe_ids[i] != g_probe_ids[0]) same = 0;
    CHECK(same && g_probe_ids[0] == 0, "probe sema ids stable (%d ...)", g_probe_ids[0]);
    rg_runtime_shutdown();
    return g_fail;
}

/* ------------------------------------------------------------ gpu_smoke */
/* cfg.gpu: the demo workload drawn by the GPU renderer (WARP; RG_GPU_HW=1:
 * the hardware adapter) must show the software GS's frame (+-2: the demo's
 * Gouraud triangle, docs/GPU.md), and the game RAM block must stay below
 * 0x10000000 with the D3D11 runtime loaded (game pointers go through 28-bit
 * masks; creating the device before the RAM block put it at 0x143A2000 on an
 * RTX 3080 and the game's first VIF1 chain faulted: docs/GPU.md "Real game
 * validation").  Skipped (77) without a GPU renderer. */
static int t_gpu_smoke(void)
{
#ifndef RG_HAVE_GPU
    printf("gpu_smoke: built without the GPU renderer: skipped\n");
    return 77;
#else
    static uint32_t frame[2][640 * 448];
    uint32_t w[2] = {0, 0}, h[2] = {0, 0};
    for (int pass = 0; pass < 2; pass++) {
        rg_runtime_config c;
        base_config(&c);
        c.entry = rg_demo_entry;
        c.gpu = pass == 0 ? 0 : (getenv("RG_GPU_HW") ? 1 : 2);
        rg_demo_config dc;
        rg_demo_default_config(&dc);
        rg_demo_setup(&dc);
        CHECK(rg_runtime_init(&c) == 0, "init (pass %d)", pass);
        if (pass == 1 && !rg_runtime_gpu()) {
            rg_runtime_shutdown();
            printf("gpu_smoke: no D3D11 device: skipped\n");
            return 77;
        }
        if (pass == 1)
            CHECK(gpu_attached_state(rg_runtime_gpu()) == rg_runtime_gs(), "GPU drives the runtime's GS");
        const rg_ps2_ram *ram = rg_crt0_ram();
        CHECK(ram && (!RG_HEAP_DMA_PLACEMENT || (uintptr_t)ram->heap_end <= RG_HEAP_DMA_HI),
              "game heap %p must end below 0x10000000 (pass %d)", ram ? (void *)ram->heap_start : NULL, pass);
        CHECK(rg_runtime_run(90) == 0, "90 fields (pass %d)", pass);
        int rc = pass == 0
                     ? gs_read_display(rg_runtime_gs(), GS_READ_FRAME, frame[0], 640 * 448, &w[0], &h[0])
                     : gpu_read_display(rg_runtime_gpu(), GS_READ_FRAME, frame[1], 640 * 448, &w[1], &h[1]);
        CHECK(rc == 0, "display read-out (pass %d)", pass);
        rg_runtime_shutdown();
    }
    CHECK(w[0] == w[1] && h[0] == h[1] && w[0] == 640 && h[0] == 448, "display %ux%u vs %ux%u", w[0], h[0],
          w[1], h[1]);
    uint32_t ndiff = 0, maxd = 0, colours = 0;
    for (uint32_t i = 0; i < 640u * 448u; i++) {
        if (i && frame[0][i] != frame[0][i - 1])
            colours++;
        for (int k = 0; k < 24; k += 8) {
            int a = (int)((frame[0][i] >> k) & 255u), b = (int)((frame[1][i] >> k) & 255u);
            uint32_t d = (uint32_t)(a > b ? a - b : b - a);
            if (d > maxd)
                maxd = d;
            if (d) {
                ndiff++;
                break;
            }
        }
    }
    CHECK(colours > 100, "the frame has content (%u colour changes)", colours);
    CHECK(maxd <= 2, "GPU frame within +-2 of the software GS (max %u, %u px differ)", maxd, ndiff);
    printf("gpu_smoke: %u of %u px differ, max %u\n", ndiff, 640u * 448u, maxd);
    return g_fail;
#endif
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-runtime-tests <test> [tmpdir]\n");
        return 2;
    }
    if (argc > 2)
        g_tmp = argv[2];
    make_dirs();
    const char *t = argv[1];
    int r;
    if (!strcmp(t, "init_order")) r = t_init_order();
    else if (!strcmp(t, "vblank_rate")) r = t_vblank_rate(0);
    else if (!strcmp(t, "vblank_rate_control")) r = t_vblank_rate(1);
    else if (!strcmp(t, "audio_field")) r = t_audio_field();
    else if (!strcmp(t, "pad_script")) r = t_pad_script(0);
    else if (!strcmp(t, "pad_script_control")) r = t_pad_script(1);
    else if (!strcmp(t, "cdvd_async")) r = t_cdvd_async(0);
    else if (!strcmp(t, "cdvd_realdata")) r = t_cdvd_async(1);
    else if (!strcmp(t, "smoke_all")) r = t_smoke_all();
    else if (!strcmp(t, "audio_wav")) r = t_audio_wav();
    else if (!strcmp(t, "crt0")) r = t_crt0();
    else if (!strcmp(t, "kernel_glue")) r = t_kernel_glue();
    else if (!strcmp(t, "gpu_smoke")) r = t_gpu_smoke();
    else {
        fprintf(stderr, "unknown test %s\n", t);
        return 2;
    }
    if (r == 77)
        return 77;
    if (r)
        fprintf(stderr, "%s: %d check(s) failed\n", t, r);
    else
        printf("%s: PASS\n", t);
    return r ? 1 : 0;
}
