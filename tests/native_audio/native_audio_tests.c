/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine tests (docs/NATIVE-AUDIO.md "Verification"), ctest -L audio.
 *
 *   native-audio-tests <name>
 *
 * The oracle is the bring-up HLE (src/ps2/iop/sound + src/ps2/spu) driven through its
 * SIF RPC path by snd_eesim (the game's request sequence); the native side gets the
 * same requests through the game-side entry points (rg_audio_game_*: the thread
 * command ids the game's SoundQueueCmd_1b6d60 carries).  Both render pull-mode
 * (no clock) and the outputs are compared with the metric in audio_metric().
 * Exit 0 = pass, 1 = fail, 77 = skipped (RG_DATA not available). */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_audio.h"
#include "rg_audio_game.h"
#include "iop.h"
#include "snd.h"
#include "snd_eesim.h"
#include "snd_pack.h"
#include "spu2.h"

#define CHECK(c, ...)                                                    \
    do {                                                                 \
        if (!(c)) {                                                      \
            fprintf(stderr, "FAIL %s:%d: ", __FILE__, __LINE__);         \
            fprintf(stderr, __VA_ARGS__);                                \
            fprintf(stderr, "\n");                                       \
            return 1;                                                    \
        }                                                                \
    } while (0)

static int g_control; /* *_control: the native engine is deliberately broken */

/* ---- metric ------------------------------------------------------------------------------ */
/* Compare native output `b` against the reference `a` (s16 stereo, n frames):
 *   snr      = 10 log10(sum a^2 / sum (a-b)^2) over the whole signal,
 *   worst    = the lowest per-window SNR over 50 ms windows whose reference RMS is at
 *              least -60 dBFS (quiet windows say nothing),
 *   lag      = the frame offset (+-8) with the least error, reported (0 expected).
 * Pass: snr >= 40 dB and worst >= 20 dB at lag 0. */
typedef struct metric {
    double snr, worst, ref_rms_db;
    int lag, windows;
    int32_t peak_diff;
} metric;

static double err_at(const int16_t *a, const int16_t *b, uint32_t n, int lag)
{
    double e = 0;
    for (uint32_t i = 16; i + 16 < n; i++) {
        int64_t j = (int64_t)i + lag;
        for (int c = 0; c < 2; c++) {
            double d = (double)a[2 * i + c] - (double)b[2 * j + c];
            e += d * d;
        }
    }
    return e;
}

static metric audio_metric(const int16_t *a, const int16_t *b, uint32_t n)
{
    metric m;
    memset(&m, 0, sizeof m);
    double p = 0, e = 0;
    for (uint32_t i = 0; i < n * 2; i++) {
        double d = (double)a[i] - (double)b[i];
        p += (double)a[i] * a[i];
        e += d * d;
        int32_t ad = abs((int32_t)a[i] - (int32_t)b[i]);
        if (ad > m.peak_diff)
            m.peak_diff = ad;
    }
    m.snr = e > 0 ? 10.0 * log10(p / e) : 200.0;
    m.ref_rms_db = p > 0 ? 10.0 * log10(p / (n * 2.0) / (32768.0 * 32768.0)) : -200.0;
    double best = -1;
    for (int lag = -8; lag <= 8; lag++) {
        double el = err_at(a, b, n, lag);
        if (best < 0 || el < best) {
            best = el;
            m.lag = lag;
        }
    }
    m.worst = 200.0;
    const uint32_t w = 2400;
    for (uint32_t s = 0; s + w <= n; s += w) {
        double pw = 0, ew = 0;
        for (uint32_t i = s * 2; i < (s + w) * 2; i++) {
            double d = (double)a[i] - (double)b[i];
            pw += (double)a[i] * a[i];
            ew += d * d;
        }
        if (pw / (w * 2.0) < 32768.0 * 32768.0 * 1e-6)
            continue;
        m.windows++;
        double snr = ew > 0 ? 10.0 * log10(pw / ew) : 200.0;
        if (snr < m.worst)
            m.worst = snr;
    }
    return m;
}

static int metric_pass(const char *what, metric m)
{
    printf("%s: snr %.1f dB, worst 50 ms window %.1f dB (%d windows), best lag %d, peak |diff| %d, "
           "reference %.1f dBFS rms\n", what, m.snr, m.worst, m.windows, m.lag, m.peak_diff, m.ref_rms_db);
    CHECK(m.ref_rms_db > -70.0, "%s: the reference is silent (test not armed)", what);
    CHECK(m.lag == 0, "%s: best alignment at lag %d", what, m.lag);
    CHECK(m.snr >= 40.0, "%s: snr %.1f dB < 40", what, m.snr);
    CHECK(m.worst >= 20.0, "%s: worst window %.1f dB < 20", what, m.worst);
    return 0;
}

/* ---- native setup: the game's init sequence through the game-side entry points ---------- */
static int cmd(int c, int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int a[10] = {a0, a1, a2, a3, a4, a5, a6, a7, a8, a9};
    return rg_audio_game_cmd(c, a);
}
#define CMD(c, ...) cmd_v(c, (int[10]){__VA_ARGS__})
static int cmd_v(int c, int *a) { return rg_audio_game_cmd(c, a); }

static void native_boot(void)
{
    rg_audio_game_init();          /* SoundIopInit_1b7160 */
    /* SoundSpuInit_1bb710 as snd_ee_boot sends it */
    CMD(0x21, 0, 0);
    CMD(0x22, 0, 4);
    CMD(0x22, 1, 0);
    CMD(0x23, 0, 0x28);
}

typedef struct nbank { int entry, msin_track, midi_track; } nbank;

static int native_load(const uint8_t *hd, uint32_t hs, const uint8_t *bd, uint32_t bs, const uint8_t *sq,
                       uint32_t ss, nbank *o)
{
    o->midi_track = -1;
    o->entry = rg_audio_game_bank(hd, hs, bd, bs);
    if (o->entry < 0)
        return -1;
    int msin = CMD(0x04, -1);
    o->msin_track = CMD(0x07, -1, msin);
    if (o->msin_track < 0 || CMD(0x08, o->msin_track, o->entry, 0) < 0)
        return -2;
    if (sq) {
        int e = rg_audio_game_seq(sq, ss);
        o->midi_track = CMD(0x06, -1, e);
        if (o->midi_track < 0 || CMD(0x08, o->midi_track, o->entry, 0) < 0)
            return -3;
    }
    return 0;
}

static const char *data_dir(void)
{
    const char *d = getenv("RG_DATA");
    return d && *d ? d : NULL;
}

typedef struct pack {
    uint8_t *d;
    uint32_t size;
    const snd_pack_entry *hd, *bd, *sq;
    snd_pack_entry e[64];
    int n;
} pack;

static int pack_load(pack *p, const char *path)
{
    memset(p, 0, sizeof *p);
    const char *dd = data_dir();
    if (!dd)
        return 77;
    p->d = snd_data_load(dd, path, &p->size);
    if (!p->d) {
        fprintf(stderr, "skip: %s not found under %s\n", path, dd);
        return 77;
    }
    p->n = snd_pack_list(p->d, p->size, p->e, 64);
    p->hd = snd_pack_find(p->e, p->n, ".hd");
    p->bd = snd_pack_find(p->e, p->n, ".bd");
    p->sq = snd_pack_find(p->e, p->n, ".sq");
    return p->hd && p->bd ? 0 : 1;
}

/* ---- tests ------------------------------------------------------------------------------- */
static int t_adpcm_same(void)
{
    uint32_t x = 12345;
    for (int k = 0; k < 20000; k++) {
        uint8_t blk[16];
        for (int i = 0; i < 16; i++) {
            x = x * 1103515245u + 12345u;
            blk[i] = (uint8_t)(x >> 16);
        }
        int16_t h1[2] = {(int16_t)(x >> 3), (int16_t)(x >> 7)}, h2[2] = {h1[0], h1[1]};
        int16_t o1[28], o2[28];
        uint8_t f1 = ra_adpcm_decode_block(blk, o1, h1), f2 = spu2_adpcm_decode_block(blk, o2, h2);
        CHECK(f1 == f2 && !memcmp(o1, o2, sizeof o1) && !memcmp(h1, h2, sizeof h1), "block %d differs", k);
    }
    for (int n = 0; n < 128; n++)
        for (int f = -256; f <= 256; f += 7)
            CHECK(ra_note2pitch(60, 0, n, f) == spu2_note2pitch(60, 0, n, f), "note2pitch %d %d", n, f);
    printf("adpcm: 20000 random blocks and the note2pitch grid identical to the HLE\n");
    return 0;
}

static int t_ids(void)
{
    native_boot();
    static const uint8_t none[1];
    for (int i = 0; i < RA_BANKS; i++)
        CHECK(rg_audio_game_bank(none, 0, none, 0) == i, "bank %d", i);
    CHECK(rg_audio_game_bank(none, 0, none, 0) == RA_E_INDEX, "bank table full");
    CHECK(CMD(0x17, 3) == 0 && rg_audio_game_bank(none, 0, none, 0) == 3, "first free after release");
    int se = CMD(0x04, -1);
    CHECK(se == 0, "SE input 0");
    int t = CMD(0x07, -1, se);
    CHECK(t == 0, "SE track 0, got %d", t);
    CHECK(CMD(0x07, 0, se) == RA_E_BUSY, "track busy");
    CHECK(CMD(0x08, 0, 5, 0) == 0 && ra_track_status(0) == 3, "attach");
    CHECK(CMD(0x08, 0, 5, 16) == RA_E_STATE, "bad slot");
    CHECK(CMD(0x20, 0, 0x66, 0, 0, 0, 60, 127, 0x40, 0x7F, 0x2000) == 0x66, "key on returns the id");
    CHECK(CMD(0x20, 9, 0x66, 0, 0, 0, 60, 127, 0x40, 0x7F, 0x2000) == RA_E_STATE, "key on, no input");
    printf("ids: entries, tracks, SE ids and error codes follow the SK rules\n");
    return 0;
}

/* PCM ports: the same calls into the HLE pcm_mixer and the native ports, sample exact */
static int t_pcm(void)
{
    snd_ee_boot();
    native_boot();
    uint32_t args[4];
    args[0] = 1; args[1] = 0x1000; args[2] = 3;
    snd_pcm_rpc(0x8000, 3, args);
    int na[4] = {1, 0x1000, 3, 0};
    rg_audio_game_pcm(0x8000, na);
    args[0] = 0x7FFF7FFF;
    snd_pcm_rpc(0x200, 1, args);
    na[0] = 0x7FFF7FFF;
    rg_audio_game_pcm(0x200, na);
    snd_pcm_rpc(0x8100, 0, args);
    rg_audio_game_pcm(0x8100, na);
    const uint32_t frames = 48000;
    int16_t *a = (int16_t *)calloc(frames, 4), *b = (int16_t *)calloc(frames, 4);
    int16_t blk[2048];
    uint32_t staging = (iop_heap_alloc(0x1004) + 3) & ~3u; /* like SoundRpcInit_1bc840 */
    int written = 0;
    for (uint32_t done = 0; done < frames; done += 800) {
        for (int port = 0; port < 2; port++) {
            na[0] = port;
            args[0] = (uint32_t)port;
            int fa = snd_pcm_rpc(0x80A0, 1, args), fb = rg_audio_game_pcm(0x80A0, na);
            CHECK(fa == fb, "free blocks differ at frame %u: hle %d native %d", done, fa, fb);
            if (fa > 0) {
                for (int i = 0; i < 2048; i++)
                    blk[i] = (int16_t)(sin((written * 2048 + i) * 0.01 * (port + 1)) * 12000);
                iop_write(staging, blk, sizeof blk);
                uint32_t m[4] = {(uint32_t)port, staging, 0x6000, 0x3000};
                int ra = snd_pcm_rpc(0x8090, 4, m);
                int rb = rg_audio_game_pcm_mix(port, blk, 0x6000, 0x3000);
                CHECK(ra == rb, "mix result differs");
                written++;
            }
        }
        uint32_t n = frames - done < 800 ? frames - done : 800;
        snd_render(a + 2 * done, n);
        ra_render(b + 2 * done, n);
    }
    uint32_t first = 0;
    while (first < frames && !b[2 * first] && !b[2 * first + 1])
        first++;
    printf("pcm: %d blocks mixed, first sound at frame %u\n", written, first);
    CHECK(first == 3072, "first block heard at frame %u, expected 3072", first);
    if (getenv("RG_AUDIO_TEST_DUMP")) {
        FILE *f = fopen("pcm_hle.raw", "wb"); fwrite(a, 4, frames, f); fclose(f);
        f = fopen("pcm_native.raw", "wb"); fwrite(b, 4, frames, f); fclose(f);
    }
    metric mt = audio_metric(a, b, frames);
    int r = metric_pass("pcm", mt);
    CHECK(mt.peak_diff <= 2, "pcm peak diff %d > 2 LSB", mt.peak_diff);
    free(a);
    free(b);
    return r;
}

/* SEs from the system bank: the title cursor, a held program with a bend, pan and volume
 * changes while it sounds, overlapping notes */
static int t_se_compare(void)
{
    pack p;
    int pr = pack_load(&p, "snd2\\sy_000.snd");
    if (pr)
        return pr;
    CHECK(snd_ee_boot() == 0, "HLE boot");
    snd_ee_bank hb;
    CHECK(snd_ee_load_bank(p.d + p.hd->offset, p.hd->size, p.d + p.bd->offset, p.bd->size, 0x5040, 0, NULL, 0,
                           &hb) == 0, "HLE bank");
    native_boot();
    nbank nb;
    CHECK(native_load(p.d + p.hd->offset, p.hd->size, p.d + p.bd->offset, p.bd->size, NULL, 0, &nb) == 0,
          "native bank");
    CHECK(nb.entry == hb.entry && nb.msin_track == hb.msin_track, "ids: entry %d/%d track %d/%d", nb.entry,
          hb.entry, nb.msin_track, hb.msin_track);
    const uint32_t frames = 48000 * 6;
    int16_t *a = (int16_t *)calloc(frames, 4), *b = (int16_t *)calloc(frames, 4);
    struct ev { uint32_t at; int what, id, prog, note, vel, pan, vol, bend; } evs[] = {
        {1000, 0, 0x66, 4, 60, 127, 0x40, 0x28, 0x2000},   /* title cursor */
        {24000, 0, 0x67, 3, 60, 100, 0x20, 0x7F, 0x2000},
        {30000, 2, 0x67, 3, 60, 0, 0, 0x50, 0},            /* volume */
        {36000, 3, 0x67, 3, 60, 0, 0x70, 0, 0},            /* pan */
        {42000, 4, 0x67, 3, 60, 0, 0, 0, 0x3000},          /* bend */
        {60000, 1, 0x67, 3, 60, 0, 0, 0, 0},               /* key off */
        {72000, 0, 0x68, 27, 64, 127, 0x40, 0x7F, 0x2000},
        {72000, 0, 0x69, 50, 67, 90, 0x40, 0x60, 0x1800},
        {80000, 0, 0x6A, 51, 72, 127, 0x60, 0x7F, 0x2000},
        {120000, 1, 0x68, 27, 64, 0, 0, 0, 0},
        {130000, 1, 0x69, 50, 67, 0, 0, 0, 0},
        {150000, 0, 0x6B, 8, 48, 127, 0x40, 0x7F, 0x2000},
        {200000, 1, 0x6B, 8, 48, 0, 0, 0, 0},
    };
    uint32_t done = 0;
    for (size_t k = 0; k <= sizeof evs / sizeof evs[0]; k++) {
        uint32_t until = k < sizeof evs / sizeof evs[0] ? evs[k].at : frames;
        snd_render(a + 2 * done, until - done);
        ra_render(b + 2 * done, until - done);
        done = until;
        if (k == sizeof evs / sizeof evs[0])
            break;
        const struct ev *e = &evs[k];
        int t = hb.msin_track;
        switch (e->what) {
        case 0:
            snd_ee_key_on_ex(t, e->id, 0, e->prog, e->note, e->vel, e->pan, e->vol, e->bend);
            CMD(0x20, t, e->id, 0, e->prog, 0, e->note, e->vel, e->pan, e->vol, e->bend);
            break;
        case 1:
            snd_ee_key_off(t, e->id, 0, e->prog, e->note);
            CMD(0x1B, t, e->id, 0, e->prog, 0, e->note);
            break;
        default: {
            uint32_t blk[16] = {3u << 24, 2, (uint32_t)t, e->what == 2 ? 0x42u : e->what == 3 ? 0x40u : 0x41u,
                                (uint32_t)e->id, 0, (uint32_t)e->note,
                                (uint32_t)(e->what == 2 ? e->vol : e->what == 3 ? e->pan : e->bend)};
            snd_sk(blk);
            CMD(e->what == 2 ? 0x1D : e->what == 3 ? 0x1E : 0x1F, t, e->id, 0, e->note,
                e->what == 2 ? e->vol : e->what == 3 ? e->pan : e->bend);
            break;
        }
        }
    }
    metric m = audio_metric(a, b, frames);
    printf("se: hle key ons %u, native key ons %u\n", snd_get_stats()->key_ons, ra_get_stats()->key_ons);
    free(a);
    free(b);
    free(p.d);
    return metric_pass("se", m);
}

static int t_seq_compare(void)
{
    pack p;
    int pr = pack_load(&p, "snd2\\bgm\\bg_000.snd");
    if (pr)
        return pr;
    CHECK(p.sq, "bg_000 has no .sq");
    CHECK(snd_ee_boot() == 0, "HLE boot");
    snd_ee_bank hb;
    CHECK(snd_ee_load_bank(p.d + p.hd->offset, p.hd->size, p.d + p.bd->offset, p.bd->size, 0x5040, 0,
                           p.d + p.sq->offset, p.sq->size, &hb) == 0, "HLE bank");
    native_boot();
    nbank nb;
    CHECK(native_load(p.d + p.hd->offset, p.hd->size, p.d + p.bd->offset, p.bd->size, p.d + p.sq->offset,
                      p.sq->size, &nb) == 0, "native bank");
    CHECK(nb.midi_track == hb.midi_track, "midi track %d/%d", nb.midi_track, hb.midi_track);
    const uint32_t frames = 48000 * 20;
    int16_t *a = (int16_t *)calloc(frames, 4), *b = (int16_t *)calloc(frames, 4);
    snd_ee_seq_play(hb.midi_track, 0, 0x40);
    CMD(0x12, nb.midi_track, 0x40);
    CMD(0x0E, nb.midi_track, 0);
    snd_render(a, frames / 2);
    ra_render(b, frames / 2);
    /* a volume change and a stop/replay half way */
    uint32_t blk[16] = {2u << 24, 2, (uint32_t)hb.midi_track, 0x30, 0, 0x60};
    snd_sk(blk);
    CMD(0x12, nb.midi_track, 0x60);
    snd_render(a + frames, frames / 4);
    ra_render(b + frames, frames / 4);
    snd_ee_seq_stop(hb.midi_track);
    CMD(0x0F, nb.midi_track);
    snd_ee_seq_play(hb.midi_track, 0, 0x60);
    CMD(0x12, nb.midi_track, 0x60);
    CMD(0x0E, nb.midi_track, 0);
    snd_render(a + frames + frames / 2, frames / 4);
    ra_render(b + frames + frames / 2, frames / 4);
    printf("seq: hle notes %u, native notes %u, native steals %u, unresolved %u\n", snd_get_stats()->seq_notes,
           ra_get_stats()->seq_notes, ra_get_stats()->voice_steals, ra_get_stats()->no_layer);
    metric m = audio_metric(a, b, frames);
    free(a);
    free(b);
    free(p.d);
    return metric_pass("seq", m);
}

/* ---- per-source volumes (docs/NATIVE-AUDIO.md "Source volumes") ------------------------------
 * One scene with every source at once: a BGM sequence (music), held SE notes (effects), two PCM
 * ports tagged by stream path (a jingle = music, an event voice line = voice), a looping movie
 * stream (movie), reverb on.  Rendered with ra_render2 under several gain settings:
 *   - the MODEL frames (what the runtime hashes) are bit-identical whatever the gains,
 *   - at unity the presentation frames are the model frames and no second mix runs,
 *   - every gain 0: the presentation is silent (within 1 LSB) once the ramp is over,
 *   - a change mid-scene and back to 1: identical before, different during, the second mix
 *     stops and the presentation is the model again after. */
#define SRC_FRAMES (48000u * 4u)

typedef struct src_scene {
    pack bg, sy;
    int se_track;
} src_scene;

static void pcm_sine(int16_t *blk, int k, double w, double amp)
{
    for (int i = 0; i < 2048; i++)
        blk[i] = (int16_t)(sin((k * 2048 + i) * w) * amp);
}

/* gains[4] applied before frame `at` (UINT32_MAX = never); back to 1 at `back` */
static int src_run(src_scene *sc, int fx, const float g0[4], uint32_t at, const float g1[4], uint32_t back,
                   int16_t *model, int16_t *pres, int *active_end)
{
    for (int i = 0; i < RA_SRC_COUNT; i++)
        ra_present_set_gain(i, g0[i]);
    native_boot();
    ra_bus_master(0, 0x3FFF, 0x3FFF);
    ra_bus_master(1, 0x3FFF, 0x3FFF);
    CMD(0x21, fx, 1);         /* effects (reverb) on, stream inputs wet */
    CMD(0x22, 1, 4);          /* bus 1 reverb mode */
    CMD(0x23, 1, 0x3000);     /* depth */
    CMD(0x25, 0, 0x7FFF);     /* bus 0 (movie) input volume */
    nbank nb, ns;
    pack *b = &sc->bg, *s = &sc->sy;
    CHECK(native_load(b->d + b->hd->offset, b->hd->size, b->d + b->bd->offset, b->bd->size, b->d + b->sq->offset,
                      b->sq->size, &nb) == 0, "bgm bank");
    CHECK(native_load(s->d + s->hd->offset, s->hd->size, s->d + s->bd->offset, s->bd->size, NULL, 0, &ns) == 0,
          "se bank");
    CMD(0x12, nb.midi_track, 0x60);
    CMD(0x0E, nb.midi_track, 0);
    CMD(0x20, ns.msin_track, 0x66, 0, 3, 0, 60, 110, 0x30, 0x7F, 0x2000);
    CMD(0x20, ns.msin_track, 0x67, 0, 27, 0, 64, 110, 0x50, 0x7F, 0x2000);
    /* PCM on bus 1: port 0 a jingle, port 1 an event voice line */
    int na[4] = {1, 0x1000, 3, 0};
    rg_audio_game_pcm(0x8000, na);
    na[0] = 0x7FFF7FFF;
    rg_audio_game_pcm(0x200, na);
    rg_audio_game_pcm(0x8100, na);
    ra_pcm_source(0, "cdrom0:\\SND2\\MWV\\800.MWV;1");
    ra_pcm_source(1, "cdrom0:\\WAV\\E\\EV01-0010\\01-0010-0001.MWV;1");
    CHECK(ra_pcm_port_source(0) == RA_SRC_MUSIC && ra_pcm_port_source(1) == RA_SRC_VOICE, "port tags");
    /* movie on bus 0: a looping ring of 16 units */
    uint32_t ring = ra_stream_alloc(16 * 1024);
    CHECK(ring != 0, "movie ring");
    static int16_t unit[512];
    for (int u = 0; u < 16; u++) {
        for (int i = 0; i < 256; i++)
            unit[i] = unit[256 + i] = (int16_t)(sin((u * 256 + i) * 0.031) * 6000);
        ra_stream_write(ring + (uint32_t)u * 1024, unit, sizeof unit);
    }
    CHECK(ra_movie_start(0, ring, 16 * 1024, ring, 1) == 0, "movie start");
    int16_t blk[2048];
    int k[2] = {0, 0};
    for (uint32_t done = 0; done < SRC_FRAMES; done += 800) {
        if (done >= at && done < at + 800)
            for (int i = 0; i < RA_SRC_COUNT; i++)
                ra_present_set_gain(i, g1[i]);
        if (done >= back && done < back + 800)
            for (int i = 0; i < RA_SRC_COUNT; i++)
                ra_present_set_gain(i, 1.0f);
        for (int port = 0; port < 2; port++) {
            na[0] = port;
            if (rg_audio_game_pcm(0x80A0, na) > 0) {
                pcm_sine(blk, k[port]++, 0.01 * (port + 1), 9000);
                rg_audio_game_pcm_mix(port, blk, 0x6000, 0x6000);
            }
        }
        uint32_t n = SRC_FRAMES - done < 800 ? SRC_FRAMES - done : 800;
        ra_render2(model + 2 * done, pres + 2 * done, n);
    }
    *active_end = ra_present_active();
    for (int i = 0; i < RA_SRC_COUNT; i++)
        ra_present_set_gain(i, 1.0f);
    return 0;
}

static int t_source_gain(void)
{
    src_scene sc;
    int pr = pack_load(&sc.bg, "snd2\\bgm\\bg_000.snd");
    if (pr)
        return pr;
    pr = pack_load(&sc.sy, "snd2\\sy_000.snd");
    if (pr)
        return pr;
    CHECK(sc.bg.sq, "bg_000 has no .sq");
    /* the classifier on the game's path formats (main_data: D_0045C5C0, D_0045C5A0, D_0045EC50,
     * D_0045C540) as FileMakeDevicePath / PathLocalize leave them */
    CHECK(ra_pcm_source_of("cdrom0:\\WAV\\BGM_MWV_NEW\\BG_012.MWV;1") == RA_SRC_MUSIC, "bgm");
    CHECK(ra_pcm_source_of("host0:wav/BGM_MWV_NEW/BG_012.mwv") == RA_SRC_MUSIC, "bgm (host path)");
    CHECK(ra_pcm_source_of("cdrom0:\\SND2\\MWV\\801.MWV;1") == RA_SRC_MUSIC, "jingle");
    CHECK(ra_pcm_source_of("cdrom0:\\WAV\\E\\EV02-0130\\02-0130-0004.MWV;1") == RA_SRC_VOICE, "event voice");
    CHECK(ra_pcm_source_of("cdrom0:\\WAV\\E\\LIVETALK\\0001-2-00003.MWV;1") == RA_SRC_VOICE, "livetalk");
    CHECK(ra_pcm_source_of("cdrom0:\\WAV\\SE\\AMB_01.MWV;1") == RA_SRC_EFFECTS, "other stream");
    CHECK(ra_pcm_source_of("cdrom0:\\EVENT\\X.MWV;1") == RA_SRC_EFFECTS, "EV without digits");
    CHECK(ra_pcm_source_of(NULL) == RA_SRC_EFFECTS && ra_pcm_source_of("") == RA_SRC_EFFECTS, "empty");

    size_t bytes = (size_t)SRC_FRAMES * 4;
    int16_t *m0 = (int16_t *)calloc(1, bytes), *p0 = (int16_t *)calloc(1, bytes);
    int16_t *m1 = (int16_t *)calloc(1, bytes), *p1 = (int16_t *)calloc(1, bytes);
    CHECK(m0 && p0 && m1 && p1, "alloc");
    static const float one[4] = {1, 1, 1, 1}, zero[4] = {0, 0, 0, 0}, mixed[4] = {0.3f, 0.0f, 0.5f, 0.0f};
    static const float music_down[4] = {0.2f, 1, 1, 1};
    int act = 0, fails = 0;

    /* A: unity throughout */
    if (src_run(&sc, 1, one, UINT32_MAX, one, UINT32_MAX, m0, p0, &act)) return 1;
    CHECK(!act, "unity: no second mix");
    CHECK(!memcmp(m0, p0, bytes), "unity: presentation == model");
    uint64_t e0 = 0;
    for (uint32_t i = 0; i < SRC_FRAMES * 2; i++)
        e0 += (uint64_t)((int32_t)m0[i] * m0[i]);
    CHECK(e0 > (uint64_t)SRC_FRAMES * 2 * 1000, "the scene is audible (energy %llu)", (unsigned long long)e0);

    /* B: mixed gains from the start: model unchanged, presentation differs */
    if (src_run(&sc, 1, mixed, UINT32_MAX, mixed, UINT32_MAX, m1, p1, &act)) return 1;
    CHECK(!memcmp(m0, m1, bytes), "mixed gains: the model frames changed");
    CHECK(memcmp(m1, p1, bytes) != 0, "mixed gains: the presentation did not change");
    CHECK(act, "mixed gains: second mix running");

    /* C: every source at 0, reverb off (with reverb the 10 ms ramp from 1 leaves a tail in the
     * presentation's reverb copy, as it should): the model as in a dry run A', presentation
     * silent after the ramp */
    if (src_run(&sc, 0, one, UINT32_MAX, one, UINT32_MAX, m0, p0, &act)) return 1;
    CHECK(!act && !memcmp(m0, p0, bytes), "dry unity: presentation == model");
    if (src_run(&sc, 0, zero, UINT32_MAX, zero, UINT32_MAX, m1, p1, &act)) return 1;
    CHECK(!memcmp(m0, m1, bytes), "all 0: the model frames changed");
    int peak = 0;
    for (uint32_t i = 2 * 2000; i < SRC_FRAMES * 2; i++) {
        int v = p1[i] < 0 ? -p1[i] : p1[i];
        if (v > peak) peak = v;
    }
    CHECK(peak <= 1, "all 0: presentation peak %d after the ramp", peak);

    if (src_run(&sc, 1, one, UINT32_MAX, one, UINT32_MAX, m0, p0, &act)) return 1;
    /* D: music 0.2 from 0.5 s to 1 s, then 1 again (the second mix must stop) */
    uint32_t at = 24000, back = 48000;
    if (src_run(&sc, 1, one, at, music_down, back, m1, p1, &act)) return 1;
    CHECK(!memcmp(m0, m1, bytes), "change: the model frames changed");
    CHECK(!memcmp(p1, m1, (size_t)at * 4), "change: differs before the change");
    CHECK(memcmp(p1 + 2 * at, m1 + 2 * at, (size_t)(back - at) * 4) != 0, "change: no effect");
    CHECK(!act, "change: the second mix still runs 3 s after the gains came back");
    uint32_t tail = 48000 * 7 / 2;
    CHECK(!memcmp(p1 + 2 * tail, m1 + 2 * tail, (size_t)(SRC_FRAMES - tail) * 4), "change: not the model again");
    printf("source_gain: model frames identical under 4 gain settings; unity = model; all 0 peak %d LSB; "
           "change mid-scene and back: second mix stopped\n", peak);
    free(m0); free(p0); free(m1); free(p1);
    free(sc.bg.d);
    free(sc.sy.d);
    return fails;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: native-audio-tests <test>[_control]\n");
        return 2;
    }
    char name[64];
    snprintf(name, sizeof name, "%s", argv[1]);
    char *c = strstr(name, "_control");
    if (c) {
        *c = 0;
        g_control = 1;
        /* the deliberately broken engine: one semitone sharp (PCM: 6 dB quiet) */
#ifdef _WIN32
        _putenv(!strcmp(name, "pcm") ? "RG_AUDIO_BREAK=volume" : "RG_AUDIO_BREAK=pitch");
#else
        setenv("RG_AUDIO_BREAK", !strcmp(name, "pcm") ? "volume" : "pitch", 1);
#endif
    }
    (void)cmd;
    struct { const char *n; int (*f)(void); } t[] = {
        {"adpcm_same", t_adpcm_same}, {"ids", t_ids}, {"pcm", t_pcm},
        {"se_compare", t_se_compare}, {"seq_compare", t_seq_compare},
        {"source_gain", t_source_gain},
    };
    for (size_t i = 0; i < sizeof t / sizeof t[0]; i++)
        if (!strcmp(name, t[i].n)) {
            int r = t[i].f();
            if (r == 77)
                printf("%s: skipped\n", argv[1]);
            else
                printf("%s: %s\n", argv[1], r ? "FAIL" : "ok");
            return r;
        }
    fprintf(stderr, "unknown test %s\n", argv[1]);
    return 2;
}
