/* SPDX-License-Identifier: CC0-1.0 */
/* Host side of the native audio engine (library rg_native_audio_host, classified HOST
 * for save states: nothing here is game state).  Environment switches, the command
 * log, the compare-mode WAV of the engine's output, and the runtime glue that drains
 * the engine each field (docs/NATIVE-AUDIO.md "Runtime").
 *
 *   RG_AUDIO=native|hle|compare   engine selection (default native)
 *   RG_AUDIO_PCM=native|hle       PCM streams on the engine (default native) or the HLE
 *   RG_AUDIO_MOVIE=native|hle     movie audio on the engine (default native) or the HLE
 *   RG_AUDIO_BREAK=pitch|volume|reverb   deliberately wrong engine (compare control)
 *   RG_AUDIO_CMDLOG=<path>        one line per driver command (audio_census.py dynamic)
 *   RG_AUDIO_NATIVE_WAV=<path>    compare mode: the engine's output, frame-aligned
 *                                 with RG_AUDIO_WAV (the HLE's, what is heard) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ra_internal.h"
#include "rg_audio_game.h"

static int env_is(const char *name, const char *v)
{
    const char *e = getenv(name);
    return e && !strcmp(e, v);
}

int ra_host_env_mode(void)
{
    const char *e = getenv("RG_AUDIO");
    int m = RG_AUDIO_NATIVE;
    if (e && !strcmp(e, "hle"))
        m = RG_AUDIO_HLE;
    else if (e && !strcmp(e, "compare"))
        m = RG_AUDIO_COMPARE;
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
    /* native-only build (docs/NATIVE-ONLY.md): no sound HLE to run or compare with */
    if (m != RG_AUDIO_NATIVE) {
        fprintf(stderr, "rg_audio: RG_AUDIO=%s ignored: native-only build (no sound HLE)\n", e);
        m = RG_AUDIO_NATIVE;
    }
#endif
    if (!getenv("RG_QUIET"))
        fprintf(stderr, "rg_audio: mode %s\n", m == RG_AUDIO_HLE ? "hle" : m == RG_AUDIO_COMPARE ? "compare" : "native");
    return m;
}

#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
int ra_host_env_pcm_native(void) { return 1; }   /* RG_AUDIO_PCM=hle: not built */
int ra_host_env_movie_native(void) { return 1; } /* RG_AUDIO_MOVIE=hle: not built */
#else
int ra_host_env_pcm_native(void) { return !env_is("RG_AUDIO_PCM", "hle"); }
int ra_host_env_movie_native(void) { return !env_is("RG_AUDIO_MOVIE", "hle"); }
#endif


int ra_host_env_break(void)
{
    if (env_is("RG_AUDIO_BREAK", "pitch")) return 1;
    if (env_is("RG_AUDIO_BREAK", "volume")) return 2;
    if (env_is("RG_AUDIO_BREAK", "reverb")) return 3;
    return 0;
}

/* ---- command log ------------------------------------------------------------------------ */
static FILE *g_log;
static int g_log_state; /* 0 unknown, 1 on, -1 off */

void ra_host_cmdlog(uint64_t frame, char kind, int id, const int *w, int n, int result)
{
    if (g_log_state == 0) {
        const char *p = getenv("RG_AUDIO_CMDLOG");
        g_log = p && *p ? fopen(p, "w") : NULL;
        g_log_state = g_log ? 1 : -1;
        if (g_log)
            fprintf(g_log, "# rg_audio cmdlog: frame\tkind (T thread cmd, P pcm, B bank/seq load, "
                           "V sounding voice once a second)\tid\twords\tresult\n");
    }
    if (g_log_state < 0 || kind == '#')
        return;
    fprintf(g_log, "%llu\t%c\t%X", (unsigned long long)frame, kind, (unsigned)id);
    for (int i = 0; i < n; i++)
        fprintf(g_log, "\t%X", (unsigned)w[i]);
    fprintf(g_log, "\t%d\n", result);
}

int ra_host_cmdlog_on(void)
{
    if (g_log_state == 0)
        ra_host_cmdlog(0, '#', 0, NULL, 0, 0);
    return g_log_state > 0;
}

/* ---- WAV (compare mode) ------------------------------------------------------------------ */
static FILE *g_wav;
static uint64_t g_wav_frames;
static int g_wav_state;

static void wav_header(FILE *f, uint64_t frames)
{
    uint32_t data = (uint32_t)(frames * 4), riff = data + 36;
    uint8_t h[44] = {'R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ', 16, 0, 0, 0, 1, 0, 2, 0,
                     0x80, 0xBB, 0, 0, 0x00, 0xEE, 0x02, 0, 4, 0, 16, 0, 'd', 'a', 't', 'a', 0, 0, 0, 0};
    memcpy(h + 4, &riff, 4);
    memcpy(h + 40, &data, 4);
    fseek(f, 0, SEEK_SET);
    fwrite(h, 1, sizeof h, f);
    fseek(f, 0, SEEK_END);
}

static void at_exit(void)
{
    if (g_wav) {
        wav_header(g_wav, g_wav_frames);
        fclose(g_wav);
        g_wav = NULL;
    }
    if (g_log)
        fflush(g_log);
    if (ra_initialized() && !getenv("RG_QUIET")) {
        const ra_stats *st = ra_get_stats();
        fprintf(stderr,
                "rg_audio: mode %d, %llu frames, %u key ons, %u key offs, %u steals, %u unresolved notes, "
                "%u banks (%u bytes), %u sequences, %u seq notes, %u pcm blocks (%u underruns), %u clipped, "
                "%u id mismatches vs hle\n",
                rg_audio_mode(), (unsigned long long)st->frames, st->key_ons, st->key_offs, st->voice_steals,
                st->no_layer, st->banks_loaded, st->bank_bytes, st->seqs_loaded, st->seq_notes, st->pcm_blocks,
                st->pcm_underruns, st->clips, rg_audio_game_mismatches());
        if (g_rp.frames_on) /* the per-source volumes' second mix (ra_present.c) */
            fprintf(stderr, "rg_audio: presentation mix %llu frames (music %.2f effects %.2f voice %.2f movie %.2f)\n",
                    (unsigned long long)g_rp.frames_on, ra_present_get_gain(RA_SRC_MUSIC),
                    ra_present_get_gain(RA_SRC_EFFECTS), ra_present_get_gain(RA_SRC_VOICE),
                    ra_present_get_gain(RA_SRC_MOVIE));
    }
}

static void wav_write(const int16_t *lr, uint32_t n)
{
    if (g_wav_state == 0) {
        const char *p = getenv("RG_AUDIO_NATIVE_WAV");
        g_wav = p && *p ? fopen(p, "wb") : NULL;
        g_wav_state = g_wav ? 1 : -1;
        if (g_wav)
            wav_header(g_wav, 0);
    }
    if (g_wav_state < 0)
        return;
    g_wav_frames += fwrite(lr, 4, n, g_wav);
    if ((g_wav_frames / 48000) != ((g_wav_frames - n) / 48000))
        wav_header(g_wav, g_wav_frames); /* keep it valid if the process dies */
}

/* ---- runtime glue -------------------------------------------------------------------------- */
static unsigned long long (*g_native_clock)(void *);
static unsigned long long (*g_hle_clock)(void *);
static unsigned long long (*g_hle_origin)(void *);
static void *g_user;
static int g_exit_registered;

void rg_audio_runtime_init(unsigned long long (*native_clock)(void *), unsigned long long (*hle_clock)(void *),
                           unsigned long long (*hle_origin)(void *), void *user)
{
    g_native_clock = native_clock;
    g_hle_clock = hle_clock;
    g_hle_origin = hle_origin;
    g_user = user;
    if (!g_exit_registered) {
        atexit(at_exit);
        g_exit_registered = 1;
    }
}

/* called by rg_audio_game_init: pick the engine's clock for the mode */
void ra_host_runtime_attach(void)
{
    if (rg_audio_mode() == RG_AUDIO_COMPARE && g_hle_clock) {
        ra_set_clock((uint64_t(*)(void *))g_hle_clock, g_user);
        g_ra->frame = g_hle_clock(g_user);
        if (g_hle_origin)
            ra_set_tick_origin(g_hle_origin(g_user));
    } else if (g_native_clock) {
        ra_set_clock((uint64_t(*)(void *))g_native_clock, g_user);
        g_ra->frame = g_native_clock(g_user);
        ra_set_tick_origin(g_ra->frame);
    }
}

void rg_audio_runtime_sync(void)
{
    if (ra_initialized() && rg_audio_mode() != RG_AUDIO_HLE)
        ra_sync();
}

/* the presentation frames of the last rg_audio_runtime_read (docs/NATIVE-AUDIO.md
 * "Source volumes"): what the host plays; the runtime hashes the model frames */
#define PRESENT_CAP 4096u
static int16_t g_present[2 * PRESENT_CAP];
static unsigned g_present_n;

unsigned rg_audio_runtime_read(short *lr, unsigned max)
{
    g_present_n = 0;
    if (rg_audio_mode() != RG_AUDIO_NATIVE || !ra_initialized() || !max)
        return 0;
    if (max > PRESENT_CAP)
        max = PRESENT_CAP;
    unsigned n = ra_output_read2(lr, g_present, max);
    g_present_n = n;
    return n;
}

const short *rg_audio_runtime_present(const short *lr, unsigned n)
{
    return n && n == g_present_n ? g_present : lr;
}

void rg_audio_runtime_volumes(int music, int effects, int voice, int movie)
{
    const int pct[RA_SRC_COUNT] = {music, effects, voice, movie};
    for (int i = 0; i < RA_SRC_COUNT; i++)
        ra_present_set_gain(i, (float)(pct[i] < 0 ? 0 : pct[i] > 100 ? 100 : pct[i]) / 100.0f);
}

void rg_audio_runtime_mix(short *lr, unsigned n)
{
    if (rg_audio_mode() == RG_AUDIO_HLE || !n)
        return;
    if (!ra_initialized()) { /* compare: silence until the game starts its sound driver */
        if (rg_audio_mode() == RG_AUDIO_COMPARE) {
            static int16_t z[2 * 1024];
            for (unsigned k = 0; k < n; k += 1024)
                wav_write(z, n - k < 1024 ? n - k : 1024);
        }
        return;
    }
    static int16_t buf[2 * 4096];
    uint32_t want = n > 4096 ? 4096 : n;
    uint32_t got = ra_output_read(buf, want);
    uint32_t off = n - got; /* the engine started inside this block: its frames are the last ones */
    if (rg_audio_mode() == RG_AUDIO_NATIVE) {
        for (uint32_t i = 0; i < got * 2; i++) {
            int32_t v = (int32_t)lr[off * 2 + i] + buf[i];
            lr[off * 2 + i] = (short)(v < -32768 ? -32768 : v > 32767 ? 32767 : v);
        }
    } else {
        static int16_t out[2 * 4096];
        uint32_t m = n > 4096 ? 4096 : n;
        memset(out, 0, (size_t)m * 4);
        if (got)
            memcpy(out + (size_t)(m - got) * 2, buf, (size_t)got * 4);
        wav_write(out, m);
    }
}

void rg_audio_runtime_shutdown(void) { at_exit(); }
