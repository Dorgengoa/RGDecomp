/* SPDX-License-Identifier: CC0-1.0 */
/* Movie tests (docs/MOVIE.md "Tests"). One subcommand per CTest case:
 *   rg-movie-tests <name>
 * Exit 0 = pass, 1 = fail, 77 = skipped (needs RG_DATA / RG_FFMPEG). */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"
#include "mv_internal.h"

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#define POPEN_RB "rb"
#else
#define POPEN_RB "r"
#endif

#define SKIP 77
#define FAILF(...)                                                \
    do {                                                          \
        fprintf(stderr, "FAIL %s:%d: ", __FILE__, __LINE__);      \
        fprintf(stderr, __VA_ARGS__);                             \
        fputc('\n', stderr);                                      \
        return 1;                                                 \
    } while (0)
#define CHECK(c, ...)                   \
    do {                                \
        if (!(c)) FAILF(__VA_ARGS__);   \
    } while (0)

static const char *g_data;     /* RG_DATA or NULL */
static const char *g_fixtures; /* tests/movie */

#define BUSCLK 147456000ull
static uint64_t field(uint64_t k) { return k * 2460060ull; }

/* ------------------------------------------------------------- pure tests */

static int t_vlc(void)
{
    char err[200];
    CHECK(mv_tables_selftest(err, sizeof err) == 0, "%s", err);
    static mv_tables t;
    CHECK(mv_tables_build(&t) == 0, "build");
    /* spot checks against Annex B */
    CHECK(t.mba[0x400].val == 1 && t.mba[0x400].len == 1, "B-1 '1'");
    CHECK(t.mba[0x008].val == 34 && t.mba[0x008].len == 11, "B-1 escape");
    CHECK(t.cbp[0x1FF >> 0].len == 3 && t.cbp[0x1FF].val == 60, "B-9 '111' = 60");
    CHECK(t.cbp[0x001].val == 0 && t.cbp[0x001].len == 9, "B-9 '0000 0000 1' = 0");
    CHECK(t.dct0.a[0x800].run == MV_RUN_EOB && t.dct0.a[0x800].len == 2, "B-14 EOB '10'");
    CHECK(t.dct1.a[0x600].run == MV_RUN_EOB && t.dct1.a[0x600].len == 4, "B-15 EOB '0110'");
    CHECK(t.dct1.a[0xFF0].level == 15 && t.dct1.a[0xFF0].len == 8, "B-15 '1111 1111' = 0,15");
    CHECK(t.dct0.b[0x10 << 0].run == 1 && t.dct0.b[0x10].level == 18, "B-14 0000 0000 0001 0000 = 1,18");
    return 0;
}

static uint32_t g_lcg = 1;
static int64_t rnd(int64_t lo, int64_t hi) /* IEEE 1180-1990 style generator */
{
    g_lcg = g_lcg * 1103515245u + 12345u;
    double x = (double)((g_lcg >> 1) & 0x7FFFFFFF) / 2147483648.0;
    return lo + (int64_t)(x * (double)(hi - lo + 1));
}

static void fdct_ref(const int32_t *in, int32_t *out)
{
    const double pi = 3.14159265358979323846;
    for (int v = 0; v < 8; v++)
        for (int u = 0; u < 8; u++) {
            double s = 0;
            for (int y = 0; y < 8; y++)
                for (int x = 0; x < 8; x++)
                    s += in[y * 8 + x] * cos((2 * x + 1) * u * pi / 16) * cos((2 * y + 1) * v * pi / 16);
            double cu = u ? 1 : sqrt(0.5), cv = v ? 1 : sqrt(0.5);
            double c = s * cu * cv / 4;
            int r = (int)floor(c + 0.5);
            out[v * 8 + u] = r < -2048 ? -2048 : r > 2047 ? 2047 : r;
        }
}

static int t_idct(void)
{
    /* IEEE 1180: for ranges (L,H) = (256,255), (5,5), (300,300), 10000 blocks each, both
     * signs: peak error <= 1, per-pixel MSE <= 0.06, overall MSE <= 0.02, per-pixel mean
     * error <= 0.015, overall mean error <= 0.0015. */
    static const int ranges[3][2] = {{256, 255}, {5, 5}, {300, 300}};
    for (int ri = 0; ri < 3; ri++)
        for (int sign = 1; sign >= -1; sign -= 2) {
            double pe[64] = {0}, pse[64] = {0};
            int peak = 0;
            g_lcg = 1;
            const int nblk = 10000;
            for (int b = 0; b < nblk; b++) {
                int32_t sp[64], co[64], got[64];
                double ref[64];
                for (int i = 0; i < 64; i++) sp[i] = (int32_t)(sign * rnd(-ranges[ri][0], ranges[ri][1]));
                fdct_ref(sp, co);
                mv_idct_ref(co, ref);
                mv_idct_int(co, 0xFF, got);
                for (int i = 0; i < 64; i++) {
                    int r = (int)floor(ref[i] + 0.5);
                    r = r < -256 ? -256 : r > 255 ? 255 : r;
                    int g = got[i] < -256 ? -256 : got[i] > 255 ? 255 : got[i];
                    int e = g - r;
                    if (abs(e) > peak) peak = abs(e);
                    pe[i] += e;
                    pse[i] += e * e;
                }
            }
            double omse = 0, ome = 0;
            for (int i = 0; i < 64; i++) {
                CHECK(pse[i] / nblk <= 0.06, "range %d sign %d: pmse[%d] = %f", ri, sign, i, pse[i] / nblk);
                CHECK(fabs(pe[i] / nblk) <= 0.015, "pme[%d] = %f", i, pe[i] / nblk);
                omse += pse[i];
                ome += pe[i];
            }
            CHECK(peak <= 1, "peak error %d", peak);
            CHECK(omse / (64.0 * nblk) <= 0.02, "omse %f", omse / (64.0 * nblk));
            CHECK(fabs(ome / (64.0 * nblk)) <= 0.0015, "ome %f", ome / (64.0 * nblk));
        }
    /* the sparse-row fast path equals the full transform */
    for (int b = 0; b < 2000; b++) {
        int32_t co[64] = {0}, a[64], c[64];
        unsigned mask = 0;
        int n = (int)rnd(1, 6);
        for (int k = 0; k < n; k++) {
            int pos = (int)rnd(0, 63);
            co[pos] = (int32_t)rnd(-300, 300);
            mask |= 1u << (pos >> 3);
        }
        mv_idct_int(co, mask, a);
        mv_idct_int(co, 0xFF, c);
        CHECK(!memcmp(a, c, sizeof a), "row mask path differs (block %d)", b);
    }
    return 0;
}

static int t_color(void)
{
    uint8_t y[32 * 32], cb[16 * 16], cr[16 * 16];
    rg_mvframe f;
    memset(&f, 0, sizeof f);
    f.y = y;
    f.cb = cb;
    f.cr = cr;
    f.ystride = 32;
    f.cstride = 16;
    f.width = 32;
    f.height = 32;
    uint32_t px[32 * 32];
    memset(y, 16, sizeof y);
    memset(cb, 128, sizeof cb);
    memset(cr, 128, sizeof cr);
    rg_mv_to_rgba(&f, px, 32, 0x80);
    CHECK(px[0] == 0x80000000u, "black = %08x", px[0]);
    memset(y, 235, sizeof y);
    rg_mv_to_rgba(&f, px, 32, 0xFF);
    CHECK(px[5] == 0xFFFFFFFFu, "white = %08x", px[5]);
    /* BT.601 red: Y 81, Cb 90, Cr 240 -> about (255, 0, 0) */
    memset(y, 81, sizeof y);
    memset(cb, 90, sizeof cb);
    memset(cr, 240, sizeof cr);
    rg_mv_to_rgba(&f, px, 32, 0);
    CHECK((px[0] & 0xFF) >= 250 && ((px[0] >> 8) & 0xFF) <= 3 && ((px[0] >> 16) & 0xFF) <= 3, "red = %08x", px[0]);
    /* PS2 block order: 16x16 blocks, column-major (x outer, y inner) */
    for (int j = 0; j < 32; j++)
        for (int i = 0; i < 32; i++) y[j * 32 + i] = (uint8_t)(16 + (i / 16) * 100 + (j / 16) * 50);
    memset(cb, 128, sizeof cb);
    memset(cr, 128, sizeof cr);
    uint8_t blk[4 * 1024];
    rg_mv_to_ps2_blocks(&f, blk, 0x80);
    /* block k: k=0 (0,0) -> Y 16; k=1 (x0,y1) -> 66; k=2 (x1,y0) -> 116; k=3 -> 166 */
    int want[4] = {16, 66, 116, 166};
    for (int k = 0; k < 4; k++) {
        int r = blk[k * 1024], ex = (298 * (want[k] - 16) + 128) >> 8;
        CHECK(r == ex && blk[k * 1024 + 3] == 0x80, "block %d red %d expected %d", k, r, ex);
        CHECK(!memcmp(blk + k * 1024, blk + k * 1024 + 4 * 37, 4), "block %d not uniform", k);
    }
    return 0;
}

static void put32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)v;
    p[1] = (uint8_t)(v >> 8);
    p[2] = (uint8_t)(v >> 16);
    p[3] = (uint8_t)(v >> 24);
}

/* a stereo s16 WAV in memory: frame i = (L = i, R = -i - 1) */
static uint8_t *make_wav(uint32_t frames, uint32_t rate, size_t *size)
{
    size_t n = 44 + (size_t)frames * 4;
    uint8_t *w = (uint8_t *)calloc(1, n);
    memcpy(w, "RIFF", 4);
    put32(w + 4, (uint32_t)n - 8);
    memcpy(w + 8, "WAVEfmt ", 8);
    put32(w + 16, 16);
    w[20] = 1;
    w[22] = 2;
    put32(w + 24, rate);
    put32(w + 28, rate * 4);
    w[32] = 4;
    w[34] = 16;
    memcpy(w + 36, "data", 4);
    put32(w + 40, frames * 4);
    for (uint32_t i = 0; i < frames; i++) {
        int16_t l = (int16_t)i, r = (int16_t)(-(int32_t)i - 1);
        w[44 + i * 4] = (uint8_t)l;
        w[45 + i * 4] = (uint8_t)((uint16_t)l >> 8);
        w[46 + i * 4] = (uint8_t)r;
        w[47 + i * 4] = (uint8_t)((uint16_t)r >> 8);
    }
    *size = n;
    return w;
}

static int16_t rd16s(const uint8_t *p) { return (int16_t)(p[0] | (p[1] << 8)); }
static uint32_t rd32u(const uint8_t *p) { return p[0] | (p[1] << 8) | (p[2] << 16) | ((uint32_t)p[3] << 24); }

static int t_audio_ss(void)
{
    size_t sz;
    uint8_t *w = make_wav(600, 48048, &sz);
    rg_mvaudio *a;
    char err[200];
    CHECK(rg_mvaudio_open_memory(&a, w, sz, err, sizeof err) == 0, "%s", err);
    CHECK(rg_mvaudio_rate(a) == 48048 && rg_mvaudio_frames(a) == 600, "rate/frames");
    uint64_t total = rg_mvaudio_ss_size(a);
    CHECK(total == 40 + 3 * 1024, "ss size %llu", (unsigned long long)total);
    uint8_t *one = (uint8_t *)malloc((size_t)total), *chunk = (uint8_t *)malloc((size_t)total);
    CHECK(rg_mvaudio_read_ss(a, one, (uint32_t)total + 100) == total, "one-shot read");
    CHECK(!memcmp(one, "SShd", 4) && rd32u(one + 4) == 24 && rd32u(one + 8) == 1, "SShd");
    CHECK(rd32u(one + 12) == 48048 && rd32u(one + 16) == 2 && rd32u(one + 20) == 512, "SShd fields");
    CHECK(rd32u(one + 24) == 0xFFFFFFFFu && !memcmp(one + 32, "SSbd", 4) && rd32u(one + 36) == 3072, "SSbd");
    const uint8_t *body = one + 40;
    for (int blk = 0; blk < 3; blk++)
        for (int i = 0; i < 256; i++) {
            int fr = blk * 256 + i;
            int16_t l = rd16s(body + blk * 1024 + i * 2), r = rd16s(body + blk * 1024 + 512 + i * 2);
            int16_t el = fr < 600 ? (int16_t)fr : 0, er = fr < 600 ? (int16_t)(-fr - 1) : 0;
            CHECK(l == el && r == er, "block %d sample %d: %d/%d expected %d/%d", blk, i, l, r, el, er);
        }
    /* odd-sized reads give the same bytes */
    rg_mvaudio_rewind(a);
    uint32_t got = 0, step = 7;
    while (got < total) {
        uint32_t k = rg_mvaudio_read_ss(a, chunk + got, step);
        if (!k) break;
        got += k;
        step = step * 3 % 1031 + 1;
    }
    CHECK(got == total && !memcmp(one, chunk, (size_t)total), "chunked SS read differs");
    /* host PCM */
    int16_t pcm[2 * 700];
    CHECK(rg_mvaudio_read_pcm(a, pcm, 700) == 600, "pcm count");
    CHECK(pcm[0] == 0 && pcm[1] == -1 && pcm[2 * 599] == 599 && pcm[2 * 599 + 1] == -600, "pcm LRLR");
    rg_mvaudio_close(a);
    free(one);
    free(chunk);
    free(w);
    return 0;
}

static int t_resolve(void)
{
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = "D";
    char o[300];
    static const char *in[] = {"cdrom0:\\MOVIE\\00\\TITLE01.MVI;1", "MOVIE/00/TITLE01.MVI", "\\movie\\00\\title01.mvi",
                               "00/TITLE01", "host0:../scratch/MOVIE/00/TITLE01.mpg"};
    for (size_t i = 0; i < sizeof in / sizeof in[0]; i++) {
        CHECK(rg_movie_resolve(&c, in[i], o, sizeof o) == 0, "resolve '%s'", in[i]);
        CHECK(!strcmp(o, "D/converted/MOVIE/00/TITLE01"), "'%s' -> '%s'", in[i], o);
    }
    CHECK(rg_movie_resolve(&c, "TITLE01", o, sizeof o) != 0, "bare name must not resolve");
    return 0;
}

/* --------------------------------------------------------- synthetic source */

typedef struct synth {
    int n, idx;
    rg_mvdec_info info;
    uint8_t y[32 * 32], c[16 * 16];
    int64_t pts0;
} synth;

static int s_next(void *u, rg_mvframe *f, int want)
{
    synth *s = (synth *)u;
    memset(f, 0, sizeof *f);
    if (s->idx >= s->n) return RG_MV_EOF;
    int i = s->idx++;
    f->type = (i % 3 == 0) ? 1 : 3;
    f->index = (uint32_t)i;
    f->pts = s->pts0 + (int64_t)i * s->info.pts_step;
    f->width = 32;
    f->height = 32;
    f->ystride = 32;
    f->cstride = 16;
    if (want || f->type != 3) {
        memset(s->y, i & 0xFF, sizeof s->y);
        s->y[1] = (uint8_t)(i >> 8);
        f->y = s->y;
        f->cb = s->c;
        f->cr = s->c;
    }
    return RG_MV_OK;
}
static int s_rewind(void *u)
{
    ((synth *)u)->idx = 0;
    return 0;
}
static const rg_mvdec_info *s_info(void *u) { return &((synth *)u)->info; }
static void s_close(void *u) { free(u); }

static rg_movie_source synth_src(int n, int fps_num, int fps_den)
{
    synth *s = (synth *)calloc(1, sizeof *s);
    s->n = n;
    s->info.width = 32;
    s->info.height = 32;
    s->info.fps_num = fps_num;
    s->info.fps_den = fps_den;
    s->info.pts_step = (int)(90000LL * fps_den / fps_num);
    s->pts0 = 4302;
    memset(s->c, 128, sizeof s->c);
    rg_movie_source src = {s, s_next, s_rewind, s_info, s_close};
    return src;
}

static rg_mvaudio *rate_only_audio(uint32_t rate)
{
    static uint8_t *w[4];
    static int k;
    size_t sz;
    rg_mvaudio *a = NULL;
    char err[100];
    w[k & 3] = make_wav(1, rate, &sz); /* the service clock needs only the header rate */
    rg_mvaudio_open_memory(&a, w[k++ & 3], sz, err, sizeof err);
    return a;
}

static int frame_id(const rg_mvframe *f) { return f->y ? f->y[0] | (f->y[1] << 8) : -1; }

typedef struct run_stats {
    int shown_ids[20000];
    int nshown;
    double max_drift_ms;
    rg_movie_status st;
    uint64_t fields;
} run_stats;

/* Drive a started service like the game: update every field, pop every 2nd field once
 * started. Stops at finished or after max_fields. */
/* Frames in the movie being driven (0 = unknown). The final frame is held until its display
 * interval ends; that hold is not an A/V error, so drift is measured only while a newer
 * frame exists. */
static uint32_t g_total;

static void drive(rg_movie *m, run_stats *rs, uint64_t max_fields, uint32_t arate)
{
    memset(rs, 0, sizeof *rs);
    uint64_t k, start = 0;
    int started = 0;
    for (k = 0; k < max_fields; k++) {
        uint64_t now = field(k);
        rg_movie_update(m, now);
        rg_movie_get_status(m, &rs->st);
        if (rs->st.finished) break;
        if (rs->st.started && !started) {
            started = 1;
            start = k;
        }
        if (started && rs->st.state == RG_MOVIE_PLAYING && ((k - start) & 1) == 0) {
            rg_mvframe f;
            if (rg_movie_take_frame(m, now, &f) && rs->nshown < 20000) rs->shown_ids[rs->nshown++] = frame_id(&f);
            rg_movie_get_status(m, &rs->st);
            if (rs->st.frames_shown && (!g_total || rs->st.frames_shown + rs->st.frames_dropped < g_total)) {
                double d = rs->st.shown_pts / 90.0 - (double)rs->st.audio_frames * 1000.0 / arate;
                if (fabs(d) > rs->max_drift_ms) rs->max_drift_ms = fabs(d);
                if (getenv("RG_MOVIE_TRACE") && fabs(d) > 16.7)
                    fprintf(stderr, "k=%llu shown=%u pts=%lld audio=%llu d=%.2f dropped=%u rep=%u\n",
                            (unsigned long long)k, rs->st.frames_shown, (long long)rs->st.shown_pts,
                            (unsigned long long)rs->st.audio_frames, d, rs->st.frames_dropped, rs->st.frames_repeated);
            }
        }
    }
    rs->fields = k;
}

static run_stats g_rs, g_rs2;

static int t_service_sm(void)
{
    rg_movie *m = rg_movie_create(NULL);
    rg_movie_status st;
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_IDLE && st.finished && !st.started, "idle");
    CHECK(rg_movie_start_source(m, synth_src(60, 30000, 1001), NULL, 0) == 0, "start");
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PREROLL && !st.started && !st.finished, "preroll state %d", st.state);
    rg_mvframe f;
    CHECK(rg_movie_take_frame(m, 0, &f) == 0, "no frame before display start");
    rg_movie_update(m, field(3));
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PLAYING && st.started && st.frames_decoded == 2, "playing after preroll (%d, %u)",
          st.state, st.frames_decoded);
    rg_movie_destroy(m);

    m = rg_movie_create(NULL);
    rg_movie_start_source(m, synth_src(60, 30000, 1001), NULL, 0);
    drive(m, &g_rs, 100000, 48000);
    CHECK(g_rs.st.state == RG_MOVIE_COMPLETE && g_rs.st.finished, "complete (state %d)", g_rs.st.state);
    CHECK(g_rs.st.frames_decoded == 60 && g_rs.st.frames_shown == 60 && g_rs.st.frames_dropped == 0,
          "shown %u dropped %u", g_rs.st.frames_shown, g_rs.st.frames_dropped);
    for (int i = 0; i < g_rs.nshown; i++) CHECK(g_rs.shown_ids[i] == i, "frame %d shown as %d", i, g_rs.shown_ids[i]);
    /* 60 frames at 29.97 + preroll: ~120 fields */
    CHECK(g_rs.fields >= 120 && g_rs.fields <= 126, "fields %llu", (unsigned long long)g_rs.fields);
    CHECK(rg_movie_take_frame(m, field(g_rs.fields + 2), &f) == 0, "no frame after completion");
    rg_movie_stop(m);
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_IDLE, "stop -> idle");
    rg_movie_destroy(m);
    return 0;
}

static int t_service_skip(void)
{
    rg_movie *m = rg_movie_create(NULL);
    rg_movie_start_source(m, synth_src(600, 30000, 1001), NULL, 0);
    rg_movie_status st;
    for (uint64_t k = 0; k < 100; k++) {
        rg_movie_update(m, field(k));
        rg_mvframe f;
        if (k % 2 == 0) rg_movie_take_frame(m, field(k), &f);
    }
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PLAYING && st.frames_shown > 40, "playing before skip");
    rg_movie_skip(m);
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_STOPPED && st.finished && st.started, "skip -> stopped/finished");
    rg_mvframe f;
    CHECK(rg_movie_take_frame(m, field(102), &f) == 0, "no frames after skip");
    rg_movie_update(m, field(103));
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_STOPPED, "stays stopped");
    /* skip during preroll */
    rg_movie_start_source(m, synth_src(600, 30000, 1001), NULL, 0);
    rg_movie_skip(m);
    rg_movie_get_status(m, &st);
    CHECK(st.finished && !st.started, "skip in preroll");
    rg_movie_destroy(m);
    return 0;
}

static int t_service_restart(void)
{
    rg_movie *m = rg_movie_create(NULL);
    rg_movie_start_source(m, synth_src(45, 30, 1), NULL, 0);
    drive(m, &g_rs, 100000, 48000);
    CHECK(g_rs.st.state == RG_MOVIE_COMPLETE, "first pass complete");
    CHECK(rg_movie_restart(m, 0) == 0, "restart");
    rg_movie_status st;
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PREROLL && !st.finished && st.frames_shown == 0, "restart -> preroll");
    drive(m, &g_rs2, 100000, 48000);
    CHECK(g_rs2.st.state == RG_MOVIE_COMPLETE, "second pass complete");
    CHECK(g_rs.nshown == g_rs2.nshown && !memcmp(g_rs.shown_ids, g_rs2.shown_ids, sizeof(int) * (size_t)g_rs.nshown),
          "second pass differs");
    CHECK(g_rs2.shown_ids[0] == 0, "restart begins at frame 0");
    /* restart mid-movie */
    rg_movie_restart(m, 0);
    for (uint64_t k = 0; k < 30; k++) {
        rg_mvframe f;
        rg_movie_update(m, field(k));
        if (k % 2 == 0) rg_movie_take_frame(m, field(k), &f);
    }
    rg_movie_restart(m, field(30));
    rg_movie_update(m, field(31));
    rg_mvframe f;
    CHECK(rg_movie_take_frame(m, field(31), &f) == 1 && frame_id(&f) == 0, "mid restart shows frame 0 (%d)",
          frame_id(&f));
    rg_movie_destroy(m);
    return 0;
}

static int t_service_pause(void)
{
    rg_movie *m = rg_movie_create(NULL);
    rg_movie_start_source(m, synth_src(300, 30000, 1001), NULL, 0);
    rg_mvframe f;
    rg_movie_status st;
    uint64_t k;
    for (k = 0; k < 100; k++) {
        rg_movie_update(m, field(k));
        if (k % 2 == 0) rg_movie_take_frame(m, field(k), &f);
    }
    rg_movie_get_status(m, &st);
    uint32_t shown = st.frames_shown;
    int64_t pts = st.shown_pts;
    rg_movie_pause(m, field(k));
    for (; k < 400; k++) {
        rg_movie_update(m, field(k));
        if (k % 2 == 0) CHECK(rg_movie_take_frame(m, field(k), &f) == 0, "frame while paused");
    }
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PAUSED && st.frames_shown == shown && st.shown_pts == pts && !st.finished,
          "paused state");
    rg_movie_resume(m, field(k));
    int got = 0;
    for (; k < 420; k++) {
        rg_movie_update(m, field(k));
        if (k % 2 == 0) got += rg_movie_take_frame(m, field(k), &f);
    }
    rg_movie_get_status(m, &st);
    CHECK(got >= 9 && st.frames_dropped == 0, "resume continues without dropping (%d, %u)", got, st.frames_dropped);
    CHECK(frame_id(&f) == (int)st.frames_shown - 1, "continuity after pause");
    rg_movie_destroy(m);
    return 0;
}

static int t_service_loop(void)
{
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.loop = 1;
    rg_movie *m = rg_movie_create(&c);
    rg_movie_start_source(m, synth_src(30, 30000, 1001), NULL, 0);
    drive(m, &g_rs, 400, 48000);
    CHECK(!g_rs.st.finished && g_rs.st.loops >= 5, "looping (loops %d)", g_rs.st.loops);
    for (int i = 1; i < g_rs.nshown; i++)
        CHECK(g_rs.shown_ids[i] == (g_rs.shown_ids[i - 1] + 1) % 30, "loop order at %d", i);
    CHECK(g_rs.max_drift_ms <= 16.7, "loop drift %.2f ms", g_rs.max_drift_ms);
    rg_movie_destroy(m);
    return 0;
}

static int t_service_error(void)
{
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = "this/does/not/exist";
    rg_movie *m = rg_movie_create(&c);
    CHECK(rg_movie_start(m, "MOVIE/00/NOPE.MVI", 0) != 0, "missing movie must fail");
    rg_movie_status st;
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_ERROR && st.finished && !st.started, "error -> finished (never hang)");
    CHECK(rg_movie_error(m)[0] != 0, "error text");
    rg_movie_update(m, field(1));
    rg_mvframe f;
    CHECK(rg_movie_take_frame(m, field(1), &f) == 0, "no frames");
    CHECK(rg_movie_start(m, "nonsense", 0) != 0, "unmappable path");
    rg_movie_destroy(m);
    /* an empty source completes instead of hanging */
    m = rg_movie_create(NULL);
    rg_movie_start_source(m, synth_src(0, 30, 1), NULL, 0);
    rg_movie_update(m, 0);
    rg_movie_get_status(m, &st);
    CHECK(st.finished, "empty source finishes");
    rg_movie_destroy(m);
    return 0;
}

/* A/V sync over a long synthetic movie: 10000 frames at fps, audio header rate `rate`.
 * Bound: the frame on screen is within half a frame (+1 tick) of the audio clock at every
 * pop, and the movie completes. */
static int av_sync(int fps_num, int fps_den, uint32_t rate, rg_movie_sync sync, const char *what)
{
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.sync = sync;
    rg_movie *m = rg_movie_create(&c);
    rg_movie_start_source(m, synth_src(10000, fps_num, fps_den), rate_only_audio(rate), 0);
    g_total = 10000;
    drive(m, &g_rs, 10000ull * 3, rate);
    double half = 90000.0 * fps_den / fps_num / 2 / 90.0 + 1.0 / 90.0;
    printf("%s: shown %u dropped %u repeated %u, max |A/V| %.2f ms (bound %.2f)\n", what, g_rs.st.frames_shown,
           g_rs.st.frames_dropped, g_rs.st.frames_repeated, g_rs.max_drift_ms, half);
    CHECK(g_rs.st.state == RG_MOVIE_COMPLETE, "%s: not complete (state %d)", what, g_rs.st.state);
    CHECK(g_rs.max_drift_ms <= half, "%s: A/V drift %.2f ms exceeds %.2f ms", what, g_rs.max_drift_ms, half);
    for (int i = 1; i < g_rs.nshown; i++) CHECK(g_rs.shown_ids[i] > g_rs.shown_ids[i - 1], "%s: order", what);
    rg_movie_destroy(m);
    return 0;
}

static int t_av_sync(void) { return av_sync(30000, 1001, 48048, RG_MOVIE_SYNC_AUDIO, "29.97/48048 audio-sync"); }
static int t_av_sync_30(void)
{
    if (av_sync(30, 1, 48048, RG_MOVIE_SYNC_AUDIO, "30/48048 audio-sync")) return 1;
    if (av_sync(30, 1, 48000, RG_MOVIE_SYNC_AUDIO, "30/48000 audio-sync")) return 1;
    /* retail pacing is in sync on the compensated 30 fps / 48048 Hz movies */
    return av_sync(30, 1, 48048, RG_MOVIE_SYNC_RETAIL, "30/48048 retail");
}
/* control: retail pacing on 29.97/48048 drifts 0.1% (10 s over 10000 frames) */
static int t_av_sync_control(void) { return av_sync(30000, 1001, 48048, RG_MOVIE_SYNC_RETAIL, "29.97/48048 retail"); }

/* Retail mode as measured on PCSX2 (docs/VALIDATION.md section 6): with the game popping
 * every VBlank, video still advances exactly one frame per two VBlanks from display start
 * (0.5 frames per VBlank = 29.97 fps), never dropping or resyncing; audio drains at the
 * SPU2's 48000 Hz whatever the header rate, so a 29.97 / 48048 Hz movie's audio runs late
 * by 0.1% of elapsed time. The control expects a new frame at every pop. */
static int retail_cadence(int control)
{
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.sync = RG_MOVIE_SYNC_RETAIL;
    rg_movie *m = rg_movie_create(&c);
    const uint32_t n = 2000;
    rg_movie_start_source(m, synth_src((int)n, 30000, 1001), rate_only_audio(48048), 0);
    rg_movie_status st;
    uint64_t k, start = 0, j = 0;
    int started = 0, prev_id = -1;
    for (k = 0; k < 10ull * n; k++) {
        uint64_t now = field(k);
        rg_movie_update(m, now);
        rg_movie_get_status(m, &st);
        if (st.finished) break;
        if (st.started && !started) {
            started = 1;
            start = k;
        }
        if (!started || st.state != RG_MOVIE_PLAYING) continue;
        rg_mvframe f;
        int got = rg_movie_take_frame(m, now, &f); /* pop at EVERY VBlank */
        rg_movie_get_status(m, &st);
        j = k - start;
        uint64_t want = control ? j + 1 : j / 2 + 1;
        if (want > n) want = n;
        CHECK(st.frames_shown == want, "retail field %llu: %u frames shown, want %llu", (unsigned long long)j,
              st.frames_shown, (unsigned long long)want);
        CHECK(st.frames_dropped == 0, "retail never drops (field %llu)", (unsigned long long)j);
        if (got) {
            CHECK(frame_id(&f) == prev_id + 1, "retail shows every frame in order (%d after %d)", frame_id(&f), prev_id);
            prev_id = frame_id(&f);
        }
        uint64_t aw = field(j) * RG_MOVIE_SPU_RATE / BUSCLK;
        CHECK(st.audio_frames == aw, "audio drains at 48000 Hz: %llu frames at field %llu, want %llu",
              (unsigned long long)st.audio_frames, (unsigned long long)j, (unsigned long long)aw);
    }
    CHECK(st.state == RG_MOVIE_COMPLETE && st.frames_shown == n, "complete with all %u frames (state %d, %u)", n,
          st.state, st.frames_shown);
    /* video rate: n frames over 2n fields from display start */
    CHECK(j >= 2ull * (n - 1) && j <= 2ull * n + 1, "video at 0.5 frames per VBlank (%llu fields for %u frames)",
          (unsigned long long)j, n);
    /* A/V: the last frame (authored at (n-1) x 1001/30 ms) vs the audio heard then (48048-Hz
     * content consumed at 48000 Hz): late by 48/48048 of the elapsed time, within a frame */
    double el_ms = (double)field(2ull * (n - 1)) * 1000.0 / BUSCLK;
    double video_ms = (double)(n - 1) * 1001.0 / 30.0;
    double audio_ms = (double)(field(2ull * (n - 1)) * RG_MOVIE_SPU_RATE / BUSCLK) * 1000.0 / 48048.0;
    double drift = video_ms - audio_ms, want_drift = el_ms * 48.0 / 48048.0;
    printf("retail: %u frames in %llu fields, A/V at the last frame %.2f ms (0.1%% of %.0f ms = %.2f)\n", n,
           (unsigned long long)j, drift, el_ms, want_drift);
    CHECK(fabs(drift - want_drift) < 0.1, "retail drift %.3f ms, want %.3f", drift, want_drift);
    rg_movie_destroy(m);
    return 0;
}
static int t_retail_cadence(void) { return retail_cadence(0); }
static int t_retail_cadence_control(void) { return retail_cadence(1); }

static int t_determinism_synth(void)
{
    for (int r = 0; r < 2; r++) {
        rg_movie *m = rg_movie_create(NULL);
        rg_movie_start_source(m, synth_src(3000, 30000, 1001), rate_only_audio(48048), 0);
        drive(m, r ? &g_rs2 : &g_rs, 10000, 48048);
        rg_movie_destroy(m);
    }
    CHECK(g_rs.nshown == g_rs2.nshown && g_rs.fields == g_rs2.fields &&
              !memcmp(g_rs.shown_ids, g_rs2.shown_ids, sizeof(int) * (size_t)g_rs.nshown),
          "two runs differ");
    return 0;
}

/* ------------------------------------------------------------- real data */

typedef struct ref_movie {
    char name[64];
    long frames;
    int w, h, fps_num, fps_den;
    long long first_pts, last_pts;
    unsigned long long digest;
    int nidx;
    long idx[8];
    unsigned long long hash[8];
} ref_movie;

static ref_movie g_ref[16];
static int g_nref;

static int load_refs(void)
{
    char p[600], line[2048];
    snprintf(p, sizeof p, "%s/reference.tsv", g_fixtures ? g_fixtures : ".");
    FILE *f = fopen(p, "r");
    if (!f) return -1;
    while (fgets(line, sizeof line, f) && g_nref < 16) {
        if (line[0] == '#' || line[0] == '\n') continue;
        ref_movie *r = &g_ref[g_nref];
        int pos = 0;
        if (sscanf(line, "%63s %ld %d %d %d %d %lld %lld %llx%n", r->name, &r->frames, &r->w, &r->h, &r->fps_num,
                   &r->fps_den, &r->first_pts, &r->last_pts, &r->digest, &pos) != 9)
            continue;
        const char *s = line + pos;
        int n;
        r->nidx = 0;
        while (r->nidx < 8 && sscanf(s, " %ld:%llx%n", &r->idx[r->nidx], &r->hash[r->nidx], &n) == 2) {
            r->nidx++;
            s += n;
        }
        g_nref++;
    }
    fclose(f);
    return g_nref ? 0 : -1;
}

static int mpg_path(const char *name, char *out, size_t cap)
{
    snprintf(out, cap, "%s/converted/MOVIE/%s.mpg", g_data, name);
    FILE *f = fopen(out, "rb");
    if (!f) return -1;
    fclose(f);
    return 0;
}

static int need_data(void)
{
    if (!g_data || !*g_data) {
        printf("skipped: RG_DATA not set\n");
        return SKIP;
    }
    if (load_refs()) {
        printf("skipped: no reference.tsv\n");
        return SKIP;
    }
    char p[600];
    if (mpg_path(g_ref[0].name, p, sizeof p)) {
        printf("skipped: %s missing (run the extraction pass)\n", p);
        return SKIP;
    }
    return 0;
}

typedef struct dec_run {
    long n;
    long long first_pts, last_pts;
    unsigned long long digest;
    unsigned long long *hashes;
    long long *pts;
    int w, h, fps_num, fps_den;
    double ms;
} dec_run;

static int decode_all(const char *name, dec_run *dr, int do_rewind_first)
{
    char p[600], err[200];
    memset(dr, 0, sizeof *dr);
    if (mpg_path(name, p, sizeof p)) FAILF("missing %s", p);
    rg_mvdec *d;
    CHECK(rg_mvdec_open(&d, p, err, sizeof err) == 0, "%s: %s", name, err);
    const rg_mvdec_info *in = rg_mvdec_get_info(d);
    dr->w = in->width;
    dr->h = in->height;
    dr->fps_num = in->fps_num;
    dr->fps_den = in->fps_den;
    rg_mvframe f;
    if (do_rewind_first) { /* decode some frames, then rewind: must not change anything */
        for (int i = 0; i < 37 && rg_mvdec_next(d, &f, 1) == RG_MV_OK; i++) {
        }
        CHECK(rg_mvdec_rewind(d) == 0, "rewind");
    }
    size_t cap = 20000;
    dr->hashes = (unsigned long long *)malloc(cap * sizeof *dr->hashes);
    dr->pts = (long long *)malloc(cap * sizeof *dr->pts);
    dr->digest = 0xcbf29ce484222325ull;
    int r;
    while ((r = rg_mvdec_next(d, &f, 1)) == RG_MV_OK) {
        if ((size_t)dr->n == cap) {
            cap *= 2;
            dr->hashes = (unsigned long long *)realloc(dr->hashes, cap * sizeof *dr->hashes);
            dr->pts = (long long *)realloc(dr->pts, cap * sizeof *dr->pts);
        }
        uint64_t h = rg_mv_frame_hash(&f);
        CHECK(f.index == (uint32_t)dr->n, "%s: index %u at %ld", name, f.index, dr->n);
        dr->hashes[dr->n] = h;
        dr->pts[dr->n] = f.pts;
        dr->digest = (dr->digest ^ h) * 0x100000001b3ull;
        if (dr->n == 0) dr->first_pts = f.pts;
        dr->last_pts = f.pts;
        dr->n++;
    }
    CHECK(r == RG_MV_EOF, "%s: decode error %d: %s", name, r, rg_mvdec_error(d));
    rg_mvdec_close(d);
    return 0;
}

static void free_run(dec_run *d)
{
    free(d->hashes);
    free(d->pts);
}

static int t_real_frames(void)
{
    int s = need_data();
    if (s) return s;
    for (int i = 0; i < g_nref; i++) {
        dec_run d;
        if (decode_all(g_ref[i].name, &d, 0)) return 1;
        CHECK(d.n == g_ref[i].frames, "%s: %ld frames, expected %ld", g_ref[i].name, d.n, g_ref[i].frames);
        CHECK(d.w == g_ref[i].w && d.h == g_ref[i].h, "%s: size", g_ref[i].name);
        CHECK(d.fps_num == g_ref[i].fps_num && d.fps_den == g_ref[i].fps_den, "%s: rate", g_ref[i].name);
        printf("%s: %ld frames ok\n", g_ref[i].name, d.n);
        free_run(&d);
    }
    return 0;
}

static int hashes(int flip)
{
    int s = need_data();
    if (s) return s;
    for (int i = 0; i < g_nref; i++) {
        dec_run d;
        if (decode_all(g_ref[i].name, &d, 0)) return 1;
        for (int k = 0; k < g_ref[i].nidx; k++) {
            long ix = g_ref[i].idx[k];
            unsigned long long want = g_ref[i].hash[k] ^ (flip && i == 0 && k == 0 ? 1ull : 0ull);
            CHECK(ix < d.n && d.hashes[ix] == want, "%s frame %ld: hash %016llx, expected %016llx", g_ref[i].name, ix,
                  ix < d.n ? d.hashes[ix] : 0ull, want);
        }
        CHECK(d.digest == g_ref[i].digest, "%s: digest %016llx, expected %016llx", g_ref[i].name, d.digest,
              g_ref[i].digest);
        printf("%s: %d frame hashes + digest ok\n", g_ref[i].name, g_ref[i].nidx);
        free_run(&d);
    }
    return 0;
}
static int t_real_hashes(void) { return hashes(0); }
static int t_hashes_control(void) { return hashes(1); }

/* PTS: our timestamps against ffprobe's (ffprobe_pts.txt; '-' where ffprobe has none),
 * and a constant step of 90000 * den / num. */
static int t_real_timestamps(void)
{
    int s = need_data();
    if (s) return s;
    char p[600];
    snprintf(p, sizeof p, "%s/ffprobe_pts.txt", g_fixtures);
    FILE *f = fopen(p, "r");
    CHECK(f, "missing %s", p);
    static char line[1 << 17];
    int movies = 0;
    while (fgets(line, sizeof line, f)) {
        char name[64];
        int pos;
        if (line[0] == '#' || sscanf(line, "%63s%n", name, &pos) != 1) continue;
        dec_run d;
        if (decode_all(name, &d, 0)) return 1;
        const char *q = line + pos;
        long i = 0, known = 0;
        char tok[32];
        int n;
        while (sscanf(q, " %31[^,\n]%n", tok, &n) == 1) {
            q += n;
            if (*q == ',') q++;
            CHECK(i < d.n, "%s: ffprobe lists more frames", name);
            if (tok[0] != '-') {
                long long v = atoll(tok);
                CHECK(v == d.pts[i], "%s frame %ld: pts %lld, ffprobe %lld", name, i, d.pts[i], v);
                known++;
            }
            i++;
        }
        CHECK(i == d.n, "%s: ffprobe %ld frames, ours %ld", name, i, d.n);
        long long step = 90000LL * d.fps_den / d.fps_num;
        for (long k = 1; k < d.n; k++) CHECK(d.pts[k] - d.pts[k - 1] == step, "%s: pts step at %ld", name, k);
        printf("%s: %ld frames, %ld PTS checked against ffprobe, step %lld\n", name, d.n, known, step);
        free_run(&d);
        movies++;
    }
    fclose(f);
    CHECK(movies > 0, "no movies in %s", p);
    return 0;
}

static int t_real_service(void)
{
    int s = need_data();
    if (s) return s;
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = g_data;
    rg_movie *m = rg_movie_create(&c);
    CHECK(rg_movie_start(m, "cdrom0:\\MOVIE\\00\\GAMEOVER.MVI;1", 0) == 0, "start: %s", rg_movie_error(m));
    rg_movie_status st;
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PREROLL && st.width == 512 && st.height == 336, "preroll");
    g_total = 210;
    drive(m, &g_rs, 100000, rg_mvaudio_rate(rg_movie_audio(m)));
    CHECK(g_rs.st.state == RG_MOVIE_COMPLETE, "complete (%d)", g_rs.st.state);
    CHECK(g_rs.st.frames_decoded == 210 && g_rs.st.frames_shown + g_rs.st.frames_dropped == 210, "frames %u+%u",
          g_rs.st.frames_shown, g_rs.st.frames_dropped);
    CHECK(g_rs.max_drift_ms <= 16.7, "drift %.2f", g_rs.max_drift_ms);
    printf("GAMEOVER: shown %u dropped %u repeated %u, %llu fields, max |A/V| %.2f ms\n", g_rs.st.frames_shown,
           g_rs.st.frames_dropped, g_rs.st.frames_repeated, (unsigned long long)g_rs.fields, g_rs.max_drift_ms);
    /* the SS stream matches the original framing */
    uint8_t hdr[40];
    CHECK(rg_movie_read_ss(m, hdr, 40) == 40 && !memcmp(hdr, "SShd", 4) && rd32u(hdr + 12) == 48048, "SS header");
    /* restart and skip on real data */
    CHECK(rg_movie_restart(m, 0) == 0, "restart");
    rg_mvframe f;
    for (uint64_t k = 0; k < 40; k++) {
        rg_movie_update(m, field(k));
        if (k % 2 == 0) rg_movie_take_frame(m, field(k), &f);
    }
    rg_movie_get_status(m, &st);
    CHECK(st.state == RG_MOVIE_PLAYING && st.frames_shown >= 18, "replaying");
    rg_movie_skip(m);
    rg_movie_get_status(m, &st);
    CHECK(st.finished && st.state == RG_MOVIE_STOPPED, "skip");
    rg_movie_stop(m);
    /* the 48000 Hz movie, through the retail pacing */
    rg_movie_destroy(m);
    c.sync = RG_MOVIE_SYNC_RETAIL;
    m = rg_movie_create(&c);
    CHECK(rg_movie_start(m, "MOVIE/01/01_11.MVI", 0) == 0, "start 01_11");
    g_total = 150;
    drive(m, &g_rs, 100000, 48000);
    CHECK(g_rs.st.state == RG_MOVIE_COMPLETE && g_rs.st.frames_shown == 150, "01_11 retail: %u shown", g_rs.st.frames_shown);
    rg_movie_destroy(m);
    return 0;
}

static int t_real_av_sync(void)
{
    int s = need_data();
    if (s) return s;
    char p[600];
    if (mpg_path("97/01_14", p, sizeof p)) {
        printf("skipped: 97/01_14 missing\n");
        return SKIP;
    }
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = g_data;
    rg_movie *m = rg_movie_create(&c);
    CHECK(rg_movie_start(m, "MOVIE/97/01_14.MVI", 0) == 0, "start: %s", rg_movie_error(m));
    uint32_t rate = rg_mvaudio_rate(rg_movie_audio(m));
    uint64_t aframes = rg_mvaudio_frames(rg_movie_audio(m));
    g_total = 9835;
    drive(m, &g_rs, 60ull * 60 * 10, rate);
    double audio_s = (double)aframes / rate, video_s = (g_rs.st.shown_pts / 90000.0) + 3003 / 90000.0;
    printf("01_14: shown %u dropped %u repeated %u, max |A/V| %.2f ms; video %.3f s, audio %.3f s (authored)\n",
           g_rs.st.frames_shown, g_rs.st.frames_dropped, g_rs.st.frames_repeated, g_rs.max_drift_ms, video_s, audio_s);
    CHECK(g_rs.st.state == RG_MOVIE_COMPLETE, "complete");
    CHECK(g_rs.max_drift_ms <= 16.7, "A/V drift %.2f ms over the whole movie", g_rs.max_drift_ms);
    CHECK(g_rs.st.frames_shown + g_rs.st.frames_dropped == 9835, "frames");
    /* 0.1%: the 29.97 movie on the 48000 Hz SPU clock repeats ~1 frame in 1000 */
    CHECK(g_rs.st.frames_dropped <= 2 && g_rs.st.frames_repeated >= 5 && g_rs.st.frames_repeated <= 15,
          "drops %u repeats %u", g_rs.st.frames_dropped, g_rs.st.frames_repeated);
    rg_movie_destroy(m);
    return 0;
}

static int t_real_determinism(void)
{
    int s = need_data();
    if (s) return s;
    dec_run a, b;
    if (decode_all("13/13_07_1A", &a, 0) || decode_all("13/13_07_1A", &b, 1)) return 1;
    CHECK(a.n == b.n && !memcmp(a.hashes, b.hashes, sizeof(unsigned long long) * (size_t)a.n), "rewind run differs");
    free_run(&a);
    free_run(&b);
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = g_data;
    for (int r = 0; r < 2; r++) {
        rg_movie *m = rg_movie_create(&c);
        CHECK(rg_movie_start(m, "MOVIE/13/13_07_1A.MVI", 0) == 0, "start");
        drive(m, r ? &g_rs2 : &g_rs, 100000, 48048);
        rg_movie_destroy(m);
    }
    CHECK(g_rs.nshown == g_rs2.nshown && g_rs.fields == g_rs2.fields &&
              !memcmp(g_rs.shown_ids, g_rs2.shown_ids, sizeof(int) * (size_t)g_rs.nshown),
          "service replay differs");
    return 0;
}

/* PSNR against FFmpeg (verification only: run as a separate process, never linked). */
static int t_real_psnr(void)
{
    int s = need_data();
    if (s) return s;
    const char *ff = getenv("RG_FFMPEG");
    if (!ff || !*ff) {
        printf("skipped: RG_FFMPEG not set (ffmpeg not found at configure time)\n");
        return SKIP;
    }
    double worst_all = 1e9;
    for (int i = 0; i < g_nref; i++) {
        char p[600], cmd[1400];
        mpg_path(g_ref[i].name, p, sizeof p);
        snprintf(cmd, sizeof cmd, "\"\"%s\" -v error -i \"%s\" -f rawvideo -pix_fmt yuv420p -\"", ff, p);
#ifndef _WIN32
        snprintf(cmd, sizeof cmd, "\"%s\" -v error -i \"%s\" -f rawvideo -pix_fmt yuv420p -", ff, p);
#endif
        FILE *pf = popen(cmd, POPEN_RB);
        CHECK(pf, "cannot run ffmpeg");
        char err[200];
        rg_mvdec *d;
        CHECK(rg_mvdec_open(&d, p, err, sizeof err) == 0, "%s", err);
        size_t fs = (size_t)g_ref[i].w * g_ref[i].h * 3 / 2;
        uint8_t *ref = (uint8_t *)malloc(fs);
        rg_mvframe f;
        long n = 0;
        double worst = 1e9, sum = 0;
        int maxd = 0;
        while (rg_mvdec_next(d, &f, 1) == RG_MV_OK) {
            CHECK(fread(ref, 1, fs, pf) == fs, "%s: ffmpeg gave fewer frames (%ld)", g_ref[i].name, n);
            double se = 0;
            const uint8_t *r = ref;
            for (int pl = 0; pl < 3; pl++) {
                const uint8_t *b = pl == 0 ? f.y : pl == 1 ? f.cb : f.cr;
                int w = pl ? f.width / 2 : f.width, h = pl ? f.height / 2 : f.height, st = pl ? f.cstride : f.ystride;
                for (int y = 0; y < h; y++)
                    for (int x = 0; x < w; x++) {
                        int dd = b[y * st + x] - *r++;
                        se += dd * dd;
                        if (abs(dd) > maxd) maxd = abs(dd);
                    }
            }
            double mse = se / (double)fs;
            double ps = mse == 0 ? 99.0 : 10 * log10(65025.0 / mse);
            if (ps < worst) worst = ps;
            sum += ps;
            n++;
        }
        CHECK(fread(ref, 1, fs, pf) == 0, "%s: ffmpeg gave more frames than %ld", g_ref[i].name, n);
        pclose(pf);
        rg_mvdec_close(d);
        free(ref);
        printf("%s: %ld frames, PSNR mean %.2f dB, worst %.2f dB, max |diff| %d\n", g_ref[i].name, n, sum / n, worst,
               maxd);
        CHECK(n == g_ref[i].frames, "frame count");
        CHECK(worst >= 55.0 && maxd <= 8, "%s: worst PSNR %.2f dB / max diff %d vs ffmpeg", g_ref[i].name, worst, maxd);
        if (worst < worst_all) worst_all = worst;
    }
    return 0;
}

/* ------------------------------------------------------------------ main */

typedef struct test {
    const char *name;
    int (*fn)(void);
} test;

static const test k_tests[] = {
    {"vlc", t_vlc},
    {"idct", t_idct},
    {"color", t_color},
    {"audio_ss", t_audio_ss},
    {"resolve", t_resolve},
    {"service_sm", t_service_sm},
    {"service_skip", t_service_skip},
    {"service_restart", t_service_restart},
    {"service_pause", t_service_pause},
    {"service_loop", t_service_loop},
    {"service_error", t_service_error},
    {"av_sync", t_av_sync},
    {"av_sync_30", t_av_sync_30},
    {"av_sync_control", t_av_sync_control},
    {"retail_cadence", t_retail_cadence},
    {"retail_cadence_control", t_retail_cadence_control},
    {"determinism_synth", t_determinism_synth},
    {"real_frames", t_real_frames},
    {"real_hashes", t_real_hashes},
    {"hashes_control", t_hashes_control},
    {"real_timestamps", t_real_timestamps},
    {"real_service", t_real_service},
    {"real_av_sync", t_real_av_sync},
    {"real_determinism", t_real_determinism},
    {"real_psnr", t_real_psnr},
};

int main(int argc, char **argv)
{
    g_data = getenv("RG_DATA");
    g_fixtures = getenv("RG_MOVIE_FIXTURES");
    if (!g_fixtures || !*g_fixtures) g_fixtures = "tests/movie";
    int ran = 0, failed = 0;
    for (size_t i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        if (argc > 1 && strcmp(argv[1], k_tests[i].name) && strcmp(argv[1], "all")) continue;
        int r = k_tests[i].fn();
        ran++;
        if (r == SKIP && argc > 1 && strcmp(argv[1], "all")) return SKIP;
        if (r == 1) failed++;
        printf("%-20s %s\n", k_tests[i].name, r == 0 ? "ok" : r == SKIP ? "skipped" : "FAIL");
    }
    if (!ran) {
        fprintf(stderr, "unknown test '%s'\n", argc > 1 ? argv[1] : "");
        return 2;
    }
    return failed ? 1 : 0;
}
