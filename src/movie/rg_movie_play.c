/* SPDX-License-Identifier: CC0-1.0 */
/* rg-movie-play: decode or play a converted movie (docs/MOVIE.md "Tool").
 *
 *   rg-movie-play [options] MOVIE
 *
 * MOVIE is a converted .mpg path, or a game path ("MOVIE/00/TITLE01.MVI", "00/TITLE01")
 * resolved under --data (default $RG_DATA, else "data").
 *
 * Headless modes (default: decode every frame and print a summary):
 *   --hash            one line per frame: index type pts fnv64(Y,Cb,Cr)
 *   --yuv FILE        raw yuv420p of every frame ("-" = stdout)
 *   --png PREFIX      PNG of frames (every --every N, default 30); needs RG_HOST
 *   --frames N        stop after N frames
 *   --bench           decode timing only (ms/frame, no output)
 *   --service         play through the movie service on a simulated virtual clock: one
 *                     vblank per NTSC field, the game's frame pop every --pop-every fields
 *                     (default 2); prints A/V drift, drops/repeats, completion
 *   --sync audio|retail   service pacing (default audio)
 *   --skip-at SEC     service: skip at that time
 * Windowed (RG_HOST builds): --window plays with sound, paced in real time (Esc quits). */
#if !defined(_WIN32) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 200809L /* clock_gettime */
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "movie.h"
#ifdef RG_MOVIE_HAVE_HOST
#include "host.h"
#endif
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h> /* after host.h: rpcndr.h #defines `small` */
#endif

static double now_ms(void)
{
#ifdef _WIN32
    LARGE_INTEGER f, c;
    QueryPerformanceFrequency(&f);
    QueryPerformanceCounter(&c);
    return (double)c.QuadPart * 1000.0 / (double)f.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
#endif
}

static uint64_t field_cycles(uint64_t k) { return k * 2460060ull; } /* = BUSCLK / 59.94 */

static void usage(void)
{
    fprintf(stderr,
            "usage: rg-movie-play [--data DIR] [--hash] [--yuv FILE] [--png PREFIX [--every N]]\n"
            "                     [--frames N] [--bench] [--service [--sync audio|retail]\n"
            "                     [--pop-every N] [--skip-at SEC]] [--window] MOVIE\n");
}

static int resolve(const char *data, const char *arg, char *mpg, char *wav, size_t cap)
{
    size_t n = strlen(arg);
    if (n > 4 && (!strcmp(arg + n - 4, ".mpg") || !strcmp(arg + n - 4, ".MPG"))) {
        snprintf(mpg, cap, "%s", arg);
        snprintf(wav, cap, "%.*s.wav", (int)(n - 4), arg);
        return 0;
    }
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = data;
    char base[600];
    if (rg_movie_resolve(&c, arg, base, sizeof base)) return -1;
    snprintf(mpg, cap, "%s.mpg", base);
    snprintf(wav, cap, "%s.wav", base);
    return 0;
}

static void write_yuv(FILE *o, const rg_mvframe *f)
{
    for (int y = 0; y < f->height; y++) fwrite(f->y + y * f->ystride, 1, (size_t)f->width, o);
    for (int y = 0; y < f->height / 2; y++) fwrite(f->cb + y * f->cstride, 1, (size_t)f->width / 2, o);
    for (int y = 0; y < f->height / 2; y++) fwrite(f->cr + y * f->cstride, 1, (size_t)f->width / 2, o);
}

/* ------------------------------------------------------------- headless */

static int run_decode(const char *mpg, int hash, const char *yuv, const char *png, int every,
                      long maxf, int bench)
{
    char err[256];
    rg_mvdec *d;
    int r = rg_mvdec_open(&d, mpg, err, sizeof err);
    if (r) {
        fprintf(stderr, "rg-movie-play: %s\n", err);
        return 2;
    }
    const rg_mvdec_info *in = rg_mvdec_get_info(d);
    FILE *log = stdout;
    FILE *o = NULL;
    if (yuv) {
        if (!strcmp(yuv, "-")) {
#ifdef _WIN32
            _setmode(1, _O_BINARY);
#endif
            o = stdout;
            log = stderr;
        } else if (!(o = fopen(yuv, "wb"))) {
            fprintf(stderr, "rg-movie-play: cannot write %s\n", yuv);
            return 2;
        }
    }
    fprintf(log, "%s: %dx%d %d/%d fps, PTS step %d, aspect %d, %u bit/s\n", mpg, in->width, in->height,
            in->fps_num, in->fps_den, in->pts_step, in->aspect_code, in->bit_rate);
    uint32_t *rgba = NULL;
    (void)png;
    (void)every;
#ifdef RG_MOVIE_HAVE_HOST
    if (png) rgba = (uint32_t *)malloc((size_t)in->width * in->height * 4);
#else
    if (png) fprintf(stderr, "rg-movie-play: --png needs an RG_HOST build; ignored\n");
#endif
    rg_mvframe f;
    long n = 0;
    double t0 = now_ms(), tprev = t0, worst = 0;
    int64_t first = 0, last = 0;
    while ((maxf <= 0 || n < maxf) && (r = rg_mvdec_next(d, &f, 1)) == RG_MV_OK) {
        if (bench) {
            double t = now_ms();
            if (t - tprev > worst) worst = t - tprev;
            tprev = t;
        }
        if (n == 0) first = f.pts;
        last = f.pts;
        if (!bench) {
            if (hash) fprintf(log, "%u %c %lld %016llx\n", f.index, " IPB"[f.type], (long long)f.pts,
                              (unsigned long long)rg_mv_frame_hash(&f));
            if (o) write_yuv(o, &f);
#ifdef RG_MOVIE_HAVE_HOST
            if (rgba && (n % (every > 0 ? every : 30)) == 0) {
                char p[600];
                rg_mv_to_rgba(&f, rgba, f.width, 255);
                snprintf(p, sizeof p, "%s%05ld.png", png, n);
                rg_png_write(p, rgba, (uint32_t)f.width, (uint32_t)f.height);
            }
#endif
        }
        n++;
    }
    double ms = now_ms() - t0;
    if (r < 0) fprintf(stderr, "rg-movie-play: decode error: %s\n", rg_mvdec_error(d));
    fprintf(log, "frames %ld, pictures %u, PTS %lld..%lld, %.3f ms/frame (%s), out-of-picture MC %u\n", n,
            rg_mvdec_pictures_decoded(d), (long long)first, (long long)last, n ? ms / n : 0.0,
            bench ? "decode only" : "incl. output", rg_mvdec_oob_predictions());
    if (bench) fprintf(log, "slowest frame %.3f ms\n", worst);
    free(rgba);
    if (o && o != stdout) fclose(o);
    rg_mvdec_close(d);
    return r < 0 ? 1 : 0;
}

static const char *state_name(rg_movie_state s)
{
    static const char *n[] = {"IDLE", "PREROLL", "PLAYING", "PAUSED", "COMPLETE", "STOPPED", "ERROR"};
    return (unsigned)s < 7 ? n[s] : "?";
}

static int run_service(const char *data, const char *arg, rg_movie_sync sync, int pop_every, double skip_at,
                       int hash)
{
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = data;
    c.sync = sync;
    rg_movie *m = rg_movie_create(&c);
    char mpg[620], wav[620];
    int r;
    if (resolve(data, arg, mpg, wav, sizeof mpg)) {
        fprintf(stderr, "rg-movie-play: cannot map '%s'\n", arg);
        return 2;
    }
    r = rg_movie_start_file(m, mpg, wav, 0);
    if (r) {
        fprintf(stderr, "rg-movie-play: start failed: %s\n", rg_movie_error(m));
        rg_movie_destroy(m);
        return 2;
    }
    rg_movie_status st;
    double max_drift = 0, sum_drift = 0;
    long pops = 0;
    uint64_t k = 0, start_field = 0;
    int started = 0;
    double t0 = now_ms();
    rg_mvaudio *a = rg_movie_audio(m);
    uint32_t arate = a ? rg_mvaudio_rate(a) : RG_MOVIE_SPU_RATE;
    for (;; k++) {
        uint64_t now = field_cycles(k);
        rg_movie_update(m, now);
        rg_movie_get_status(m, &st);
        if (st.started && !started) {
            started = 1;
            start_field = k;
        }
        if (st.finished) break;
        if (skip_at > 0 && started && (double)(k - start_field) / 59.94 >= skip_at) {
            rg_movie_skip(m);
            continue;
        }
        if (started && ((k - start_field) % (uint64_t)pop_every) == 0) {
            rg_mvframe f;
            int got = rg_movie_take_frame(m, now, &f);
            rg_movie_get_status(m, &st);
            pops++;
            /* drift: authored time of the frame on screen vs the audio being heard */
            double audio_ms = (double)st.audio_frames * 1000.0 / arate;
            double video_ms = (double)st.shown_pts / 90.0;
            double dr = video_ms - audio_ms;
            if (st.frames_shown > 0) {
                if (dr < 0 ? -dr > max_drift : dr > max_drift) max_drift = dr < 0 ? -dr : dr;
                sum_drift += dr;
            }
            if (got && hash)
                printf("show %u %lld %016llx\n", st.frames_shown - 1, (long long)f.pts,
                       (unsigned long long)rg_mv_frame_hash(&f));
        }
        if (k > 60ull * 60 * 60 * 2) break; /* 2 h safety */
    }
    double audio_ms = (double)st.audio_frames * 1000.0 / arate;
    printf("service: state %s, fields %llu (%.2f s), shown %u, decoded %u, dropped %u, repeated %u\n",
           state_name(st.state), (unsigned long long)k, k / 59.94, st.frames_shown, st.frames_decoded,
           st.frames_dropped, st.frames_repeated);
    printf("service: final video %.1f ms, audio %.1f ms, drift %.1f ms; max |drift| %.1f ms, mean %.1f ms "
           "over %ld pops; %.0f ms wall\n",
           st.shown_pts / 90.0, audio_ms, st.shown_pts / 90.0 - audio_ms, max_drift,
           pops ? sum_drift / pops : 0.0, pops, now_ms() - t0);
    rg_movie_destroy(m);
    return 0;
}

/* ------------------------------------------------------------- windowed */

#ifdef RG_MOVIE_HAVE_HOST
static int run_window(const char *data, const char *arg, rg_movie_sync sync)
{
    rg_host_config hc;
    rg_host_config_default(&hc);
    hc.title = "rg-movie-play";
    rg_host *h = rg_host_create(&hc);
    if (!h) {
        fprintf(stderr, "rg-movie-play: %s\n", rg_host_last_error());
        return 2;
    }
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = data;
    c.sync = sync;
    rg_movie *m = rg_movie_create(&c);
    char mpg[620], wav[620];
    int r;
    if (resolve(data, arg, mpg, wav, sizeof mpg)) {
        fprintf(stderr, "rg-movie-play: cannot map '%s'\n", arg);
        return 2;
    }
    r = rg_movie_start_file(m, mpg, wav, 0);
    if (r) {
        fprintf(stderr, "rg-movie-play: %s\n", rg_movie_error(m));
        return 2;
    }
    rg_pacer pacer;
    rg_pacer_init(&pacer, 1);
    rg_movie_status st;
    uint32_t *rgba = NULL;
    int16_t pcm[2 * 2048];
    uint64_t pushed = 0, k = 0, start_field = 0;
    int started = 0;
    for (;; k++) {
        if (!rg_host_pump(h)) break;
        uint64_t now = field_cycles(k);
        if (k) rg_pacer_hook(field_cycles(k - 1), now, &pacer);
        rg_movie_update(m, now);
        rg_movie_get_status(m, &st);
        if (st.finished) break;
        if (st.started && !started) {
            started = 1;
            start_field = k;
        }
        if (!started) continue;
        /* audio: everything the SPU would have played by the end of this field */
        uint64_t want = (field_cycles(k + 1 - start_field)) * RG_MOVIE_SPU_RATE / RG_MOVIE_BUSCLK;
        while (pushed < want) {
            uint32_t n = (uint32_t)(want - pushed > 2048 ? 2048 : want - pushed);
            uint32_t got = rg_movie_read_pcm(m, pcm, n);
            if (got < n) memset(pcm + 2 * got, 0, (n - got) * 4);
            rg_host_audio_push(h, pcm, n);
            pushed += n;
        }
        if (((k - start_field) & 1) == 0) {
            rg_mvframe f;
            if (rg_movie_take_frame(m, now, &f)) {
                if (!rgba) rgba = (uint32_t *)malloc((size_t)f.width * f.height * 4);
                rg_mv_to_rgba(&f, rgba, f.width, 255);
            }
            if (rgba) rg_host_present(h, rgba, (uint32_t)st.width, (uint32_t)st.height);
        }
    }
    printf("window: state %s, shown %u, dropped %u\n", state_name(st.state), st.frames_shown, st.frames_dropped);
    free(rgba);
    rg_movie_destroy(m);
    rg_host_destroy(h);
    return 0;
}
#endif

int main(int argc, char **argv)
{
    const char *data = getenv("RG_DATA");
    const char *yuv = NULL, *png = NULL, *movie = NULL;
    int hash = 0, bench = 0, service = 0, window = 0, every = 30, pop_every = 2;
    long frames = 0;
    double skip_at = 0;
    rg_movie_sync sync = RG_MOVIE_SYNC_AUDIO;
    if (!data || !*data) data = "data";
    for (int i = 1; i < argc; i++) {
        const char *a = argv[i];
        if (!strcmp(a, "--data") && i + 1 < argc) data = argv[++i];
        else if (!strcmp(a, "--hash")) hash = 1;
        else if (!strcmp(a, "--yuv") && i + 1 < argc) yuv = argv[++i];
        else if (!strcmp(a, "--png") && i + 1 < argc) png = argv[++i];
        else if (!strcmp(a, "--every") && i + 1 < argc) every = atoi(argv[++i]);
        else if (!strcmp(a, "--frames") && i + 1 < argc) frames = atol(argv[++i]);
        else if (!strcmp(a, "--bench")) bench = 1;
        else if (!strcmp(a, "--service")) service = 1;
        else if (!strcmp(a, "--window")) window = 1;
        else if (!strcmp(a, "--pop-every") && i + 1 < argc) pop_every = atoi(argv[++i]);
        else if (!strcmp(a, "--skip-at") && i + 1 < argc) skip_at = atof(argv[++i]);
        else if (!strcmp(a, "--sync") && i + 1 < argc) {
            const char *s = argv[++i];
            if (!strcmp(s, "retail")) sync = RG_MOVIE_SYNC_RETAIL;
            else if (!strcmp(s, "audio")) sync = RG_MOVIE_SYNC_AUDIO;
            else {
                usage();
                return 1;
            }
        } else if (a[0] == '-' && a[1]) {
            usage();
            return 1;
        } else movie = a;
    }
    if (!movie || pop_every < 1) {
        usage();
        return 1;
    }
    if (window) {
#ifdef RG_MOVIE_HAVE_HOST
        return run_window(data, movie, sync);
#else
        fprintf(stderr, "rg-movie-play: built without RG_HOST; --window unavailable\n");
        return 1;
#endif
    }
    if (service) return run_service(data, movie, sync, pop_every, skip_at, hash);
    char mpg[620], wav[620];
    if (resolve(data, movie, mpg, wav, sizeof mpg)) {
        fprintf(stderr, "rg-movie-play: cannot map '%s'\n", movie);
        return 1;
    }
    return run_decode(mpg, hash, yuv, png, every, frames, bench);
}
