/* SPDX-License-Identifier: CC0-1.0
 * rg-runtime-demo: boots the whole platform stack through rg_runtime WITHOUT
 * game code and runs the guest smoke workload (demo_guest.c): libpad reads
 * (scripted or live), a libcdvd read of SYSTEM.CNF (RG_DATA, or a synthetic
 * disc folder), an SE key-on through libsdr/SK, and a VIF1 -> VU1 XGKICK ->
 * GS draw, presented through the host.  docs/RUNTIME.md.
 *
 *   rg-runtime-demo [--headless] [--fields N] [--data DIR] [--saves DIR]
 *                   [--input script.txt] [--screenshot out.png] [--unthrottled]
 *                   [--hash-every N] [--parts pad,cd,snd,gfx] [--fixture DIR]
 *                   [--settings FILE] [--set id=value] [--preset original|default]
 *
 * --settings/--set/--preset go to the settings registry (docs/SETTINGS.md);
 * the overlay (F1) saves back to the --settings file.
 *
 * Prints one summary line per part and a final `run_hash=`; exit 0 when every
 * enabled part passed its smoke check. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "demo_guest.h"
#include "rg_input.h"
#include "rg_runtime.h"
#include "rg_settings.h"
#include "snd.h"
#ifdef RG_WITH_TRACE
/* Optional state-trace hook (docs/TRACE-PORT.md): src/trace links rg_trace +
 * the demo's synthetic trace symbols into this exe and defines RG_WITH_TRACE.
 * It does nothing unless RG_TRACE_OUT is set. */
#include "rg_trace.h"
#include "trace_demo_syms.h"
#endif

static void usage(void)
{
    fprintf(stderr,
            "usage: rg-runtime-demo [--headless] [--fields N] [--data DIR] [--saves DIR]\n"
            "                       [--input script.txt] [--screenshot out.png] [--unthrottled]\n"
            "                       [--hash-every N] [--parts pad,cd,snd,gfx] [--fixture DIR]\n"
            "                       [--settings FILE] [--set id=value] [--preset NAME]\n");
}

static uint32_t parse_parts(const char *s)
{
    uint32_t p = 0;
    if (strstr(s, "pad")) p |= RG_DEMO_PAD;
    if (strstr(s, "cd")) p |= RG_DEMO_CD;
    if (strstr(s, "snd")) p |= RG_DEMO_SND;
    if (strstr(s, "gfx")) p |= RG_DEMO_GFX;
    if (strstr(s, "all")) p |= RG_DEMO_ALL;
    return p;
}

int main(int argc, char **argv)
{
    rg_runtime_config cfg;
    rg_runtime_default_config(&cfg);
    /* settings first: --settings / --set / --preset are consumed from argv */
    rg_settings *settings = rg_settings_create();
    rg_settings_register_core(settings);
    rg_actions_register_settings(settings);
    const char *settings_path = NULL;
    int set_errors = 0;
    argc = rg_settings_apply_args(settings, argc, argv, &set_errors, &settings_path);
    if (set_errors) { usage(); return 2; }
    rg_runtime_config_from_settings(&cfg, settings);
    cfg.settings_path = settings_path;
    rg_demo_config dc;
    rg_demo_default_config(&dc);
    uint64_t fields = 0; /* 0 = until the window closes */
    const char *shot = NULL, *fixture = NULL;
    int headless = 0;
    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        const char *v = i + 1 < argc ? argv[i + 1] : NULL;
        if (!strcmp(a, "--headless")) headless = 1;
        else if (!strcmp(a, "--unthrottled")) cfg.throttle = 0;
        else if (!strcmp(a, "--fields") && v) { fields = strtoull(v, NULL, 0); i++; }
        else if (!strcmp(a, "--data") && v) { cfg.data_dir = v; i++; }
        else if (!strcmp(a, "--saves") && v) { cfg.saves_dir = v; i++; }
        else if (!strcmp(a, "--input") && v) { cfg.input_script = v; i++; }
        else if (!strcmp(a, "--screenshot") && v) { shot = v; i++; }
        else if (!strcmp(a, "--hash-every") && v) { cfg.display_hash_every = (uint32_t)strtoul(v, NULL, 0); i++; }
        else if (!strcmp(a, "--parts") && v) { dc.parts = parse_parts(v); i++; }
        else if (!strcmp(a, "--fixture") && v) { fixture = v; i++; }
        else { usage(); return 2; }
    }
    cfg.headless = headless;
    if (headless && !fields)
        fields = 600;
    cfg.title = "rg-runtime-demo";

    /* the disc: --data, else $RG_DATA, else a synthetic folder */
    if (!cfg.data_dir && !getenv("RG_DATA")) {
        if (!fixture)
            fixture = "rg-runtime-fixture";
        if (rg_demo_write_fixture(fixture) != 0) {
            fprintf(stderr, "rg-runtime-demo: cannot write the fixture disc %s\n", fixture);
            return 1;
        }
        cfg.data_dir = fixture;
        fprintf(stderr, "rg-runtime-demo: no RG_DATA; using the synthetic disc in %s\n", fixture);
    }
    if (!cfg.saves_dir && !getenv("RG_SAVES"))
        cfg.saves_dir = "rg-runtime-saves";

    /* main returns one field before the run ends, so the last field's host
     * half still runs; 0 = run until the window closes */
    dc.fields = fields ? (uint32_t)fields + 1 : 0;
    rg_demo_setup(&dc);
    cfg.entry = rg_demo_entry;
#ifdef RG_WITH_TRACE
    rg_trace_demo_register();
    if (rg_trace_apply_env(&cfg) < 0)
        return 2;
#endif
    if (rg_runtime_init(&cfg) != 0)
        return 1;
    int rc = rg_runtime_run(fields);
    uint64_t shot_hash = 0;
    uint32_t sw = 0, sh = 0;
    int shot_rc = rg_runtime_screenshot(shot, &shot_hash, &sw, &sh);
    const rg_runtime_stats *st = rg_runtime_get_stats();
    const rg_demo_result *r = rg_demo_get_result();
    uint64_t nf = st->fields ? st->fields : 1;
    int ok = 1;

    printf("fields=%llu vblank_start=%llu vblank_end=%llu rc=%d\n", (unsigned long long)st->fields,
           (unsigned long long)st->vblank_start, (unsigned long long)st->vblank_end, rc);
    printf("audio: frames=%llu avg_per_field=%.4f peak=%d dropped=%llu key_ons=%u\n",
           (unsigned long long)st->audio_frames, (double)st->audio_frames / (double)nf, st->audio_peak,
           (unsigned long long)st->audio_dropped, snd_get_stats()->key_ons);
    if (dc.parts & RG_DEMO_PAD) {
        uint16_t last = 0;
        for (uint32_t f = 0; f < RG_DEMO_MAX_FIELDS && f < nf; f++)
            if (r->pad_word[f]) last = r->pad_word[f];
        printf("pad: stable_field=%d reads=%u last_nonzero_word=0x%04x rumble_aligned=%d rumble_changes=%llu\n",
               r->pad_stable_field, r->pad_reads, last, r->rumble_set, (unsigned long long)st->rumble_changes);
        ok &= r->pad_stable_field >= 0 && r->pad_reads > 0;
    }
    if (dc.parts & RG_DEMO_CD) {
        printf("cd: ok=%d lsn=%u text=\"%s\" issue=%llu due=%llu done=%llu busy_after_issue=%d\n", r->cd_ok,
               r->cd_lsn, r->cd_text, (unsigned long long)r->cd_issue_cycles, (unsigned long long)r->cd_due_cycles,
               (unsigned long long)r->cd_done_cycles, r->cd_busy_after_issue);
        ok &= r->cd_ok == 1;
    }
    if (dc.parts & RG_DEMO_SND) {
        printf("snd: ok=%d entry=%d track=%d keyon_vblank=%llu\n", r->snd_ok, r->snd_entry, r->snd_track,
               (unsigned long long)r->snd_keyon_vblank);
        ok &= r->snd_ok == 1 && (fields == 0 || fields <= dc.keyon_field + 2 || st->audio_peak > 1000);
    }
    if (dc.parts & RG_DEMO_GFX) {
        printf("gfx: frames=%u display=%ux%u display_hash=%016llx%s%s\n", r->gfx_frames, sw, sh,
               (unsigned long long)shot_hash, shot ? " screenshot=" : "", shot ? shot : "");
        ok &= r->gfx_frames > 0 && shot_rc == 0;
    }
    printf("run_hash=%016llx\n", (unsigned long long)st->run_hash);
    rg_runtime_shutdown();
    rg_settings_destroy(settings);
    printf("%s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
