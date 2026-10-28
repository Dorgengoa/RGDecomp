/* SPDX-License-Identifier: CC0-1.0 */
/* Movie service: the replacement for the game's movie layer (docs/MOVIE.md "Service").
 *
 * The PS2 player (src/main/movie) runs three threads: MovieReadThread_1d4f50 reads sectors
 * and demuxes, VideoDecMain_1d5240 decodes through libmpeg/IPU into a 2-slot frame FIFO
 * (VoBuf), DefMain_1d52b0 yields; the game thread pops one decoded frame per game frame
 * (MovieFrameQueueSendNext_1d4b20) and DMAs it to GS memory, where MovieDrawFrame_1d5870
 * draws it as a textured sprite under the game's own fades and menus. This service keeps
 * that contract (FIFO depth, preroll -> started flag, one pop per game frame, frame count,
 * finished flag, pause, loop) and replaces the threads, IPU and DMA with a synchronous
 * decoder pumped from the game thread on the virtual clock. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"

#define MAX_FIFO 8

typedef struct slot {
    uint8_t *buf;          /* Y, Cb, Cr planes, tightly packed */
    rg_mvframe f;          /* f.pts is RELATIVE (0 = first frame of pass 0) */
    int has_pixels;
} slot;

struct rg_movie {
    rg_movie_config cfg;
    char root[512];
    rg_movie_state state;
    rg_movie_source src;
    int have_src;
    rg_mvaudio *audio;
    rg_mvdec_info info;
    slot fifo[MAX_FIFO];
    int head, count, cap;
    slot out;
    size_t frame_bytes;
    int src_eof;
    int64_t base_pts;
    int have_base;
    int64_t pass_offset;
    uint32_t pass_frames;
    /* virtual clock */
    uint64_t t0, pause_at, paused_total;
    /* status */
    uint32_t decoded, shown, dropped, repeated;
    int64_t shown_pts;
    int has_shown;
    int started;
    int gate_closed;   /* rg_movie_set_start_gate(m, 0): hold PREROLL -> PLAYING */
    int loops;
    uint64_t audio_frames;
    char err[256];
};

void rg_movie_config_default(rg_movie_config *c)
{
    memset(c, 0, sizeof *c);
    c->data_root = NULL;
    c->sync = RG_MOVIE_SYNC_AUDIO;
    c->fifo_frames = 2;
    c->audio = 1;
    c->loop = 0;
    c->preroll_audio_frames = 0;
}

rg_movie *rg_movie_create(const rg_movie_config *c)
{
    rg_movie *m = (rg_movie *)calloc(1, sizeof *m);
    if (!m) return NULL;
    if (c) m->cfg = *c;
    else rg_movie_config_default(&m->cfg);
    const char *root = m->cfg.data_root;
    if (!root || !*root) root = getenv("RG_DATA");
    if (!root || !*root) root = "data";
    snprintf(m->root, sizeof m->root, "%s", root);
    m->cfg.data_root = m->root;
    if (m->cfg.fifo_frames < 1) m->cfg.fifo_frames = 1;
    if (m->cfg.fifo_frames > MAX_FIFO) m->cfg.fifo_frames = MAX_FIFO;
    m->cap = m->cfg.fifo_frames;
    return m;
}

static void free_slots(rg_movie *m)
{
    for (int i = 0; i < MAX_FIFO; i++) {
        free(m->fifo[i].buf);
        m->fifo[i].buf = NULL;
    }
    free(m->out.buf);
    m->out.buf = NULL;
    m->frame_bytes = 0;
}

void rg_movie_stop(rg_movie *m)
{
    if (!m) return;
    if (m->have_src && m->src.close) m->src.close(m->src.user);
    m->have_src = 0;
    rg_mvaudio_close(m->audio);
    m->audio = NULL;
    free_slots(m);
    m->state = RG_MOVIE_IDLE;
    m->head = m->count = 0;
}

void rg_movie_destroy(rg_movie *m)
{
    if (!m) return;
    rg_movie_stop(m);
    free(m);
}

const char *rg_movie_error(const rg_movie *m) { return m->err; }
rg_mvaudio *rg_movie_audio(rg_movie *m) { return m->audio; }

/* ------------------------------------------------------------- resolving */

static int ieq_n(const char *a, const char *b, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (toupper((unsigned char)a[i]) != toupper((unsigned char)b[i])) return 0;
    return 1;
}

int rg_movie_resolve(const rg_movie_config *c, const char *game_path, char *out, size_t cap)
{
    char p[256];
    size_t n = 0;
    if (!game_path) return -1;
    /* normalise separators, drop a device prefix ("cdrom0:") and the ";1" version */
    const char *s = strchr(game_path, ':');
    s = s ? s + 1 : game_path;
    for (; *s && *s != ';' && n + 1 < sizeof p; s++) p[n++] = (*s == '\\') ? '/' : *s;
    p[n] = 0;
    char *q = p;
    while (*q == '/') q++;
    /* find "MOVIE/" anywhere (case-insensitive) and keep what follows */
    for (char *t = q; *t; t++)
        if ((t == q || t[-1] == '/') && strlen(t) > 6 && ieq_n(t, "MOVIE/", 6)) {
            q = t + 6;
            break;
        }
    size_t len = strlen(q);
    if (len > 4 && ieq_n(q + len - 4, ".MVI", 4)) q[len - 4] = 0;
    else if (len > 4 && (ieq_n(q + len - 4, ".MPG", 4) || ieq_n(q + len - 4, ".WAV", 4))) q[len - 4] = 0;
    if (!*q || !strchr(q, '/')) return -1;
    for (char *t = q; *t; t++) *t = (char)toupper((unsigned char)*t);
    const char *root = c && c->data_root && *c->data_root ? c->data_root : "data";
    int w = snprintf(out, cap, "%s/converted/MOVIE/%s", root, q);
    return (w < 0 || (size_t)w >= cap) ? -1 : 0;
}

/* ---------------------------------------------------------------- source */

static int dec_next(void *u, rg_mvframe *f, int want) { return rg_mvdec_next((rg_mvdec *)u, f, want); }
static int dec_rewind(void *u) { return rg_mvdec_rewind((rg_mvdec *)u); }
static const rg_mvdec_info *dec_info(void *u) { return rg_mvdec_get_info((rg_mvdec *)u); }
static void dec_close(void *u) { rg_mvdec_close((rg_mvdec *)u); }

static void reset_play(rg_movie *m)
{
    m->head = m->count = 0;
    m->src_eof = 0;
    m->have_base = 0;
    m->pass_offset = 0;
    m->pass_frames = 0;
    m->t0 = m->pause_at = m->paused_total = 0;
    m->decoded = m->shown = m->dropped = m->repeated = 0;
    m->shown_pts = 0;
    m->has_shown = 0;
    m->started = 0;
    m->loops = 0;
    m->audio_frames = 0;
}

static int alloc_slots(rg_movie *m)
{
    size_t w = (size_t)((m->info.width + 15) & ~15), h = (size_t)((m->info.height + 15) & ~15);
    m->frame_bytes = w * h + 2 * (w / 2) * (h / 2);
    for (int i = 0; i < m->cap; i++) {
        m->fifo[i].buf = (uint8_t *)malloc(m->frame_bytes);
        if (!m->fifo[i].buf) return -1;
    }
    m->out.buf = (uint8_t *)malloc(m->frame_bytes);
    return m->out.buf ? 0 : -1;
}

int rg_movie_start_source(rg_movie *m, rg_movie_source src, rg_mvaudio *audio, uint64_t now)
{
    (void)now;
    rg_movie_stop(m);
    m->err[0] = 0;
    m->src = src;
    m->have_src = 1;
    m->audio = audio;
    m->info = *src.info(src.user);
    reset_play(m);
    if (alloc_slots(m)) {
        snprintf(m->err, sizeof m->err, "out of memory");
        m->state = RG_MOVIE_ERROR;
        return RG_MV_ERR_NOMEM;
    }
    m->state = RG_MOVIE_PREROLL;
    return 0;
}

rg_movie_source rg_movie_source_decoder(rg_mvdec *d)
{
    rg_movie_source src = {d, dec_next, dec_rewind, dec_info, dec_close};
    return src;
}

int rg_movie_start_file(rg_movie *m, const char *mpg, const char *wav, uint64_t now)
{
    char err[200];
    rg_movie_stop(m);
    m->err[0] = 0;
    reset_play(m);
    rg_mvdec *d = NULL;
    int r = rg_mvdec_open(&d, mpg, err, sizeof err);
    if (r) {
        snprintf(m->err, sizeof m->err, "%s", err);
        m->state = RG_MOVIE_ERROR;
        return r;
    }
    rg_mvaudio *a = NULL;
    char aerr[256] = "";
    if (m->cfg.audio && wav) {
        if (rg_mvaudio_open(&a, wav, err, sizeof err)) {
            /* video without its audio still plays (on the clock alone); remember why */
            snprintf(aerr, sizeof aerr, "audio: %s", err);
            a = NULL;
        }
    }
    r = rg_movie_start_source(m, rg_movie_source_decoder(d), a, now);
    if (!r && aerr[0]) snprintf(m->err, sizeof m->err, "%s", aerr);
    return r;
}

int rg_movie_start(rg_movie *m, const char *game_path, uint64_t now)
{
    char base[600], mpg[620], wav[620];
    if (rg_movie_resolve(&m->cfg, game_path, base, sizeof base)) {
        rg_movie_stop(m);
        reset_play(m);
        snprintf(m->err, sizeof m->err, "cannot map movie path '%s'", game_path ? game_path : "(null)");
        m->state = RG_MOVIE_ERROR;
        return RG_MV_ERR_IO;
    }
    snprintf(mpg, sizeof mpg, "%s.mpg", base);
    snprintf(wav, sizeof wav, "%s.wav", base);
    return rg_movie_start_file(m, mpg, wav, now);
}

/* --------------------------------------------------------------- playing */

static int64_t step90(const rg_movie *m) { return m->info.pts_step > 0 ? m->info.pts_step : 3003; }

/* Authored time (90 kHz, relative to the first frame) of the audio being heard at `now`. */
static int64_t clock90(rg_movie *m, uint64_t now)
{
    if (m->state != RG_MOVIE_PLAYING && m->state != RG_MOVIE_PAUSED && m->state != RG_MOVIE_COMPLETE)
        return 0;
    uint64_t t = (m->state == RG_MOVIE_PAUSED) ? m->pause_at : now;
    uint64_t el = t > m->t0 + m->paused_total ? t - m->t0 - m->paused_total : 0;
    m->audio_frames = el * RG_MOVIE_SPU_RATE / RG_MOVIE_BUSCLK;
    /* The SPU plays the ring at 48000 frames/s; sample n of the stream is authored at
     * n / header_rate. Without audio the movie runs on its own timeline in real time. */
    uint32_t rate = m->audio ? rg_mvaudio_rate(m->audio) : RG_MOVIE_SPU_RATE;
    return (int64_t)(m->audio_frames * 90000u / rate);
}

static slot *fifo_at(rg_movie *m, int i) { return &m->fifo[(m->head + i) % m->cap]; }

static void fifo_pop(rg_movie *m)
{
    m->head = (m->head + 1) % m->cap;
    m->count--;
}

static int pull(rg_movie *m, int want_pixels)
{
    if (m->src_eof || m->count >= m->cap) return 0;
    rg_mvframe f;
    int r = m->src.next(m->src.user, &f, want_pixels);
    if (r == RG_MV_EOF && m->cfg.loop && m->pass_frames > 0) {
        m->pass_offset += (int64_t)m->pass_frames * step90(m);
        m->pass_frames = 0;
        m->loops++;
        if (m->src.rewind(m->src.user) == 0) r = m->src.next(m->src.user, &f, want_pixels);
    }
    if (r != RG_MV_OK) {
        if (r < 0 && !m->err[0]) snprintf(m->err, sizeof m->err, "decode error %d", r);
        m->src_eof = 1;
        return 0;
    }
    if (!m->have_base) {
        m->base_pts = f.pts;
        m->have_base = 1;
    }
    slot *s = fifo_at(m, m->count);
    s->f = f;
    s->f.pts = f.pts - m->base_pts + m->pass_offset;
    s->has_pixels = f.y != NULL;
    if (s->has_pixels) {
        int w = f.width, h = f.height, cw = w / 2, ch = h / 2;
        uint8_t *y = s->buf, *cb = y + (size_t)w * h, *cr = cb + (size_t)cw * ch;
        for (int i = 0; i < h; i++) memcpy(y + (size_t)i * w, f.y + (size_t)i * f.ystride, (size_t)w);
        for (int i = 0; i < ch; i++) {
            memcpy(cb + (size_t)i * cw, f.cb + (size_t)i * f.cstride, (size_t)cw);
            memcpy(cr + (size_t)i * cw, f.cr + (size_t)i * f.cstride, (size_t)cw);
        }
        s->f.y = y;
        s->f.cb = cb;
        s->f.cr = cr;
        s->f.ystride = w;
        s->f.cstride = cw;
    }
    m->count++;
    m->decoded++;
    m->pass_frames++;
    return 1;
}

static void check_complete(rg_movie *m, uint64_t now)
{
    if (m->state != RG_MOVIE_PLAYING || !m->src_eof) return;
    if (m->cfg.sync == RG_MOVIE_SYNC_RETAIL) {
        /* VideoDecMain sets state 3 once the decoder ended and VoBuf drained */
        if (m->count == 0) m->state = RG_MOVIE_COMPLETE;
        return;
    }
    /* audio clock: complete once the last frame's display interval has passed, whether
     * or not the game fetched every frame */
    int64_t last = m->count > 0 ? fifo_at(m, m->count - 1)->f.pts : (m->has_shown ? m->shown_pts : -1);
    if (last < 0 || clock90(m, now) >= last + step90(m)) m->state = RG_MOVIE_COMPLETE;
}

void rg_movie_set_start_gate(rg_movie *m, int open) { m->gate_closed = !open; }

void rg_movie_update(rg_movie *m, uint64_t now)
{
    if (m->state == RG_MOVIE_PREROLL) {
        while (m->count < m->cap && pull(m, 1)) {
        }
        if ((m->count >= m->cap || m->src_eof) && (!m->gate_closed || m->count == 0)) {
            if (m->count == 0) {
                m->state = RG_MOVIE_COMPLETE; /* empty or unreadable stream: never hang */
                return;
            }
            /* MovieReadThread: VoBuf full + audio preset -> MovieDisplayStart + AudioDecStart */
            m->t0 = now;
            m->paused_total = 0;
            m->started = 1;
            m->state = RG_MOVIE_PLAYING;
        }
        return;
    }
    if (m->state == RG_MOVIE_PLAYING) {
        clock90(m, now);
        if (m->cfg.sync == RG_MOVIE_SYNC_RETAIL) {
            while (m->count < m->cap && pull(m, 1)) {
            }
        }
        check_complete(m, now);
    }
}

static void give(rg_movie *m, slot *s, rg_mvframe *f)
{
    slot tmp = m->out;
    m->out = *s;
    s->buf = tmp.buf; /* swap buffers: the FIFO slot gets the old output buffer */
    m->shown++;
    m->shown_pts = m->out.f.pts;
    m->has_shown = 1;
    *f = m->out.f;
}

int rg_movie_take_frame(rg_movie *m, uint64_t now, rg_mvframe *f)
{
    memset(f, 0, sizeof *f);
    if (m->state != RG_MOVIE_PLAYING) return 0;
    if (m->cfg.sync == RG_MOVIE_SYNC_RETAIL) {
        clock90(m, now);
        /* 2-VBlank cadence (VALIDATION.md 6: 0.500014 frames per VBlank, no drops): frame n
         * is due from display start + n x 2 fields; a pop before that keeps the picture. */
        if (m->state == RG_MOVIE_PLAYING) {
            uint64_t el = now > m->t0 + m->paused_total ? now - m->t0 - m->paused_total : 0;
            uint64_t due = el / (2ull * RG_MOVIE_FIELD_CYCLES) + 1;
            if (m->shown >= due) {
                m->repeated++;
                check_complete(m, now);
                return 0;
            }
        }
        if (m->count == 0) pull(m, 1);
        if (m->count == 0) {
            m->repeated++;
            check_complete(m, now);
            return 0;
        }
        slot *s = fifo_at(m, 0);
        if (!s->has_pixels) { /* cannot happen in retail mode (always decodes pixels) */
            fifo_pop(m);
            m->dropped++;
            m->repeated++;
            return 0;
        }
        give(m, s, f);
        fifo_pop(m);
        return 1;
    }
    int64_t step = step90(m);
    int64_t t = clock90(m, now) + step / 2; /* nearest frame: |error| <= half a frame */
    /* make sure the FIFO reaches past t (decoding, and dropping what is already late) */
    for (;;) {
        if (m->count > 0 && fifo_at(m, m->count - 1)->f.pts > t) break;
        if (m->src_eof) break;
        if (m->count == m->cap) {
            if (fifo_at(m, 0)->f.pts <= t && m->count > 1) {
                fifo_pop(m);
                m->dropped++;
                continue;
            }
            break;
        }
        int64_t next = m->count > 0 ? fifo_at(m, m->count - 1)->f.pts + step
                                    : (m->has_shown ? m->shown_pts + step : 0);
        int want = !(next + step <= t); /* the frame after it is due too: skip its pixels */
        if (!pull(m, want)) break;
    }
    int pick = -1;
    for (int i = 0; i < m->count; i++) {
        slot *s = fifo_at(m, i);
        if (s->f.pts > t) break;
        if (s->has_pixels) pick = i;
    }
    if (pick < 0) {
        /* nothing due with pixels: drop due pixel-less frames, keep the current picture */
        while (m->count > 0 && fifo_at(m, 0)->f.pts <= t && !fifo_at(m, 0)->has_pixels) {
            fifo_pop(m);
            m->dropped++;
        }
        m->repeated++;
        check_complete(m, now);
        return 0;
    }
    for (int i = 0; i < pick; i++) {
        fifo_pop(m);
        m->dropped++;
    }
    give(m, fifo_at(m, 0), f);
    fifo_pop(m);
    return 1;
}

void rg_movie_pause(rg_movie *m, uint64_t now)
{
    if (m->state != RG_MOVIE_PLAYING) return;
    m->pause_at = now;
    m->state = RG_MOVIE_PAUSED;
}

void rg_movie_resume(rg_movie *m, uint64_t now)
{
    if (m->state != RG_MOVIE_PAUSED) return;
    m->paused_total += now - m->pause_at;
    m->state = RG_MOVIE_PLAYING;
}

void rg_movie_skip(rg_movie *m)
{
    if (m->state == RG_MOVIE_IDLE) return;
    m->state = RG_MOVIE_STOPPED;
}

int rg_movie_restart(rg_movie *m, uint64_t now)
{
    (void)now;
    if (!m->have_src) return -1;
    if (m->src.rewind(m->src.user) != 0) {
        m->state = RG_MOVIE_ERROR;
        return -1;
    }
    if (m->audio) rg_mvaudio_rewind(m->audio);
    reset_play(m);
    m->err[0] = 0;
    m->state = RG_MOVIE_PREROLL;
    return 0;
}

void rg_movie_get_status(const rg_movie *m, rg_movie_status *s)
{
    memset(s, 0, sizeof *s);
    s->state = m->state;
    s->started = m->started;
    s->finished = m->state == RG_MOVIE_COMPLETE || m->state == RG_MOVIE_STOPPED ||
                  m->state == RG_MOVIE_ERROR || m->state == RG_MOVIE_IDLE;
    s->frames_decoded = m->decoded;
    s->frames_shown = m->shown;
    s->frames_dropped = m->dropped;
    s->frames_repeated = m->repeated;
    s->shown_pts = m->shown_pts;
    s->audio_frames = m->audio_frames;
    s->width = m->info.width;
    s->height = m->info.height;
    s->loops = m->loops;
}

/* ------------------------------------------------------------------ audio */

uint32_t rg_movie_read_pcm(rg_movie *m, int16_t *lr, uint32_t n)
{
    if (!m->audio) return 0;
    uint32_t got = rg_mvaudio_read_pcm(m->audio, lr, n);
    if (got < n && m->cfg.loop && rg_mvaudio_frames(m->audio) > 0) {
        rg_mvaudio_seek_pcm(m->audio, 0);
        got += rg_mvaudio_read_pcm(m->audio, lr + 2 * got, n - got);
    }
    return got;
}

uint32_t rg_movie_read_ss(rg_movie *m, uint8_t *dst, uint32_t n)
{
    if (!m->audio) return 0;
    return rg_mvaudio_read_ss(m->audio, dst, n);
}

/* ---- save states (docs/TEST-FIXTURES.md): the decoder and audio reader of a
 * movie, for the movie hook (mv_game.c) */
rg_mvdec *rg_movie_ss_decoder(rg_movie *m)
{
    return m && m->have_src && m->src.next == dec_next ? (rg_mvdec *)m->src.user : NULL;
}

rg_mvaudio *rg_movie_ss_audio(rg_movie *m) { return m ? m->audio : NULL; }
