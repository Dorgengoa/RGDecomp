/* SPDX-License-Identifier: CC0-1.0 */
/* Native audio engine: the presentation mix (docs/NATIVE-AUDIO.md "Source volumes",
 * PLAN.md P6 "Audio": separate music, effects, voice and movie volumes).
 *
 * The model mix (ra_mix.c) is what the runtime hashes, what RG_AUDIO_WAV records and what
 * the game's pacing depends on; it never sees these gains.  While some source gain is not 1
 * ra_mix.c renders a second mix of the same voice samples beside it (bus_tick, "pon"):
 * each source's part is scaled by (gain - 1) and added to the model's sums, it runs its own
 * copy of each bus's reverb, and the result goes to a presentation FIFO that mirrors the
 * model FIFO frame for frame (ra_output_read2).  With every gain at 1 that FIFO holds the
 * model's frames, bit for bit.
 *
 * Sources: sequenced notes (SQ tracks) = music, the game's key ons = effects, PCM stream
 * ports by the stream's file path (ra_pcm_source_of), the movie stream = movie.
 *
 * Everything here is HOST for save states (src/savestate/ss_map.c): presentation state is
 * never saved and the model never reads it.  A load is detected (the model's frame counter
 * or FIFO is not where this file left it) and the copies are taken again from the model. */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ra_internal.h"
#include "rg_audio_game.h"

#define Q1 65536
#define RAMP_FRAMES 480u                /* 10 ms from 0 to 1 */
#define UNITY_GIVE_UP (2u * RA_RATE)    /* back at 1 for 2 s: stop even if the reverb copy differs */
#define UNITY_CHECK (RA_RATE / 10u)     /* compare the reverb copies every 100 ms */

ra_present g_rp = {
    .target_q = {Q1, Q1, Q1, Q1},
    .g = {1.0f, 1.0f, 1.0f, 1.0f},
    .port_src = {RA_SRC_EFFECTS, RA_SRC_EFFECTS, RA_SRC_EFFECTS, RA_SRC_EFFECTS},
};
static uint32_t g_rev_cap[RA_BUSES];    /* halfwords allocated in g_rp.rev[b].buf */

/* ---- gains -------------------------------------------------------------------------------- */
void ra_present_set_gain(int src, float gain)
{
    if (src < 0 || src >= RA_SRC_COUNT)
        return;
    if (!(gain > 0.0f))
        gain = 0.0f;   /* also NaN */
    if (gain > 1.0f)
        gain = 1.0f;
    g_rp.target_q[src] = (int32_t)(gain * (float)Q1 + 0.5f);
}

float ra_present_get_gain(int src)
{
    return src < 0 || src >= RA_SRC_COUNT ? 1.0f : (float)g_rp.target_q[src] / (float)Q1;
}

int ra_present_active(void) { return g_rp.on; }

static int targets_unity(void)
{
    for (int i = 0; i < RA_SRC_COUNT; i++)
        if (g_rp.target_q[i] != Q1)
            return 0;
    return 1;
}

static int gains_unity(void)
{
    for (int i = 0; i < RA_SRC_COUNT; i++)
        if (g_rp.g[i] != 1.0f)
            return 0;
    return 1;
}

void ra_present_frame(void)
{
    const float step = 1.0f / (float)RAMP_FRAMES;
    for (int i = 0; i < RA_SRC_COUNT; i++) {
        float t = (float)g_rp.target_q[i] / (float)Q1, g = g_rp.g[i];
        if (g != t) {
            float d = t - g;
            g = d > step ? g + step : d < -step ? g - step : t;   /* lands exactly on t */
            g_rp.g[i] = g;
        }
        g_rp.gm1[i] = g - 1.0f;   /* exactly 0 at unity */
    }
}

/* ---- reverb copies -------------------------------------------------------------------------- */
static int rev_clone(int b)
{
    const ra_reverb *m = &g_ra->bus[b].rev;
    ra_reverb *p = &g_rp.rev[b];
    if (m->size > g_rev_cap[b] || !p->buf) {
        int16_t *nb = (int16_t *)realloc(p->buf, (size_t)(m->size ? m->size : 1) * sizeof(int16_t));
        if (!nb)
            return 0;
        p->buf = nb;
        g_rev_cap[b] = m->size ? m->size : 1;
    }
    int16_t *keep = p->buf;
    *p = *m;
    p->buf = keep;
    if (m->size && m->buf)
        memcpy(p->buf, m->buf, (size_t)m->size * sizeof(int16_t));
    else
        p->size = 0;
    return 1;
}

static int rev_equal(int b)
{
    const ra_reverb *m = &g_ra->bus[b].rev, *p = &g_rp.rev[b];
    if (!g_rp.rev_ok[b])
        return 0;
    if (m->mode != p->mode || m->pos != p->pos || m->half != p->half || m->acc[0] != p->acc[0] ||
        m->acc[1] != p->acc[1] || m->out[0] != p->out[0] || m->out[1] != p->out[1])
        return 0;
    if ((m->size && m->buf) != (p->size != 0) || m->size != p->size)
        return 0;
    return !m->size || !memcmp(m->buf, p->buf, (size_t)m->size * sizeof(int16_t));
}

void ra_present_reverb_changed(int bus)
{
    if (bus >= 0 && bus < RA_BUSES)
        g_rp.rev_ok[bus] = 0;   /* re-cloned at the next render */
}

/* ---- PCM parts per source ---------------------------------------------------------------- */
static int pcm_idx(int src) { return src == RA_SRC_MUSIC ? 0 : src == RA_SRC_VOICE ? 2 : 1; }

void ra_present_pcm_free(void)
{
    for (int c = 0; c < RA_PCM_SRCS; c++) {
        free(g_rp.ring[c]);
        free(g_rp.play[c]);
        g_rp.ring[c] = g_rp.play[c] = NULL;
    }
    g_rp.nblocks = g_rp.block_bytes = 0;
}

void ra_present_pcm_init(uint32_t nblocks, uint32_t block_bytes)
{
    ra_present_pcm_free();
    uint32_t hw = block_bytes / 2;
    for (int c = 0; c < RA_PCM_SRCS; c++) {
        g_rp.ring[c] = (int32_t *)calloc((size_t)nblocks * hw, sizeof(int32_t));
        g_rp.play[c] = (int32_t *)calloc((size_t)2 * hw, sizeof(int32_t));
        if (!g_rp.ring[c] || !g_rp.play[c]) {
            ra_present_pcm_free();   /* no parts: PCM plays at the model's level */
            return;
        }
    }
    g_rp.nblocks = nblocks;
    g_rp.block_bytes = block_bytes;
}

static void pcm_zero(void)
{
    uint32_t hw = g_rp.block_bytes / 2;
    for (int c = 0; c < RA_PCM_SRCS && g_rp.ring[c]; c++) {
        memset(g_rp.ring[c], 0, (size_t)g_rp.nblocks * hw * sizeof(int32_t));
        memset(g_rp.play[c], 0, (size_t)2 * hw * sizeof(int32_t));
    }
}

void ra_present_pcm_start(void)
{
    uint32_t hw = g_rp.block_bytes / 2;
    for (int c = 0; c < RA_PCM_SRCS && g_rp.play[c]; c++)
        memset(g_rp.play[c], 0, (size_t)2 * hw * sizeof(int32_t));
}

/* the model just mixed `src` into its ring block `block` for `port` (ra_pcm_mix): the same
 * product, unclamped, into that port's source ring */
void ra_present_pcm_mix(int port, uint32_t block, const uint8_t *src, int vol_l, int vol_r)
{
    if (!g_rp.ring[0] || port < 0 || port > 3 || block >= g_rp.nblocks)
        return;
    uint32_t hw = g_rp.block_bytes / 2;
    int32_t *dst = g_rp.ring[pcm_idx(g_rp.port_src[port])] + (size_t)block * hw;
    for (uint32_t i = 0; i < hw; i++) {
        int32_t sv = (int16_t)(src[2 * i] | src[2 * i + 1] << 8);
        int32_t vol = ((i >> 8) & 1) ? vol_r : vol_l;
        dst[i] += (sv * vol) >> 15;
    }
}

void ra_present_pcm_block(uint32_t rpos, int have_play)
{
    if (!g_rp.ring[0] || rpos >= g_rp.nblocks)
        return;
    uint32_t hw = g_rp.block_bytes / 2;
    for (int c = 0; c < RA_PCM_SRCS; c++) {
        int32_t *s = g_rp.ring[c] + (size_t)rpos * hw;
        memcpy(g_rp.play[c] + (size_t)(have_play & 1) * hw, s, (size_t)hw * sizeof(int32_t));
        memset(s, 0, (size_t)hw * sizeof(int32_t));
    }
}

void ra_present_pcm_frame(int have_play, uint32_t il, uint32_t ir, float cls[RA_PCM_SRCS][2])
{
    uint32_t hw = g_rp.block_bytes / 2;
    if (!g_rp.play[0] || il >= hw || ir >= hw)
        return;   /* zeros: the stream plays at the model's level */
    for (int c = 0; c < RA_PCM_SRCS; c++) {
        const int32_t *h = g_rp.play[c] + (size_t)(have_play & 1) * hw;
        cls[c][0] = (float)h[il];
        cls[c][1] = (float)h[ir];
    }
}

/* ---- PCM port sources (the stream's file path) ------------------------------------------- */
int ra_pcm_source_of(const char *path)
{
    char u[160];
    size_t n = 0;
    if (!path)
        return RA_SRC_EFFECTS;
    for (; path[n] && n < sizeof u - 1; n++)
        u[n] = path[n] == '\\' ? '/' : (char)toupper((unsigned char)path[n]);
    u[n] = 0;
    if (strstr(u, "BGM") || strstr(u, "SND2/MWV"))   /* wav/BGM_MWV_NEW/BG_nnn, jingles 8nn */
        return RA_SRC_MUSIC;
    if (strstr(u, "LIVETALK"))                       /* wav/<lang>/LiveTalk/... */
        return RA_SRC_VOICE;
    for (const char *p = u; (p = strstr(p, "/EV")) != NULL; p++)   /* wav/<lang>/EVnn-nnnn/ */
        if (isdigit((unsigned char)p[3]) && isdigit((unsigned char)p[4]) && p[5] == '-')
            return RA_SRC_VOICE;
    return RA_SRC_EFFECTS;
}

static FILE *g_srclog;
static int g_srclog_state;

void ra_pcm_source(int port, const char *path)
{
    if (port < 0 || port > 3 || !path)
        return;
    if (!strncmp(g_rp.port_path[port], path, sizeof g_rp.port_path[port] - 1))
        return;
    snprintf(g_rp.port_path[port], sizeof g_rp.port_path[port], "%s", path);
    g_rp.port_src[port] = ra_pcm_source_of(path);
    if (g_srclog_state == 0) { /* $RG_AUDIO_SRCLOG: one row per change (the source census) */
        const char *p = getenv("RG_AUDIO_SRCLOG");
        g_srclog = p && *p ? fopen(p, "w") : NULL;
        g_srclog_state = g_srclog ? 1 : -1;
        if (g_srclog)
            fputs("# frame\tport\tsource (0 music, 1 effects, 2 voice)\tpath\n", g_srclog);
    }
    if (g_srclog_state > 0) {
        fprintf(g_srclog, "%llu\t%d\t%d\t%s\n", (unsigned long long)g_ra->frame, port, g_rp.port_src[port],
                g_rp.port_path[port]);
        fflush(g_srclog);
    }
}

int ra_pcm_port_source(int port) { return port < 0 || port > 3 ? -1 : g_rp.port_src[port]; }

void rg_audio_game_pcm_source(int port, const char *path) { ra_pcm_source(port, path); }

/* ---- FIFO mirror ---------------------------------------------------------------------------- */
static void fifo_resync(void)
{
    ra_state *s = g_ra;
    if (g_rp.cap != s->fifo_cap || !g_rp.fifo) {
        free(g_rp.fifo);
        g_rp.fifo = s->fifo_cap ? (int16_t *)calloc(s->fifo_cap, 4) : NULL;
        g_rp.cap = g_rp.fifo ? s->fifo_cap : 0;
    }
    if (g_rp.fifo && s->fifo)
        memcpy(g_rp.fifo, s->fifo, (size_t)g_rp.cap * 4);
    g_rp.rd = s->fifo_rd;
    g_rp.n = s->fifo_n;
}

static int fifo_ok(void)
{
    ra_state *s = g_ra;
    if (!s->fifo || !s->fifo_cap)
        return 0;
    if (g_rp.cap != s->fifo_cap || !g_rp.fifo || g_rp.n != s->fifo_n || g_rp.rd != s->fifo_rd)
        fifo_resync();
    return g_rp.fifo != NULL;
}

/* called before the model's fifo_push of the same frames: the same drop rule */
void ra_present_fifo_push(const int16_t *lr, uint32_t n)
{
    if (!fifo_ok())
        return;
    for (uint32_t i = 0; i < n; i++) {
        if (g_rp.n == g_rp.cap) {
            g_rp.rd = (g_rp.rd + 1) % g_rp.cap;
            g_rp.n--;
        }
        uint32_t w = (g_rp.rd + g_rp.n) % g_rp.cap;
        g_rp.fifo[2 * w] = lr[2 * i];
        g_rp.fifo[2 * w + 1] = lr[2 * i + 1];
        g_rp.n++;
    }
}

/* called before the model's read of n frames */
uint32_t ra_present_fifo_read(int16_t *lr, uint32_t n)
{
    if (!fifo_ok()) {
        if (lr)
            memset(lr, 0, (size_t)n * 4);
        return 0;
    }
    if (n > g_rp.n)
        n = g_rp.n;
    for (uint32_t i = 0; i < n; i++) {
        if (lr) {
            lr[2 * i] = g_rp.fifo[2 * g_rp.rd];
            lr[2 * i + 1] = g_rp.fifo[2 * g_rp.rd + 1];
        }
        g_rp.rd = (g_rp.rd + 1) % g_rp.cap;
    }
    g_rp.n -= n;
    return n;
}

/* ---- render hooks ---------------------------------------------------------------------------- */
void ra_present_reset(void)
{
    g_rp.on = 0;
    for (int i = 0; i < RA_SRC_COUNT; i++) {
        g_rp.g[i] = 1.0f;
        g_rp.gm1[i] = 0.0f;
    }
    for (int b = 0; b < RA_BUSES; b++) {
        g_rp.rev_ok[b] = 0;
        g_rp.out[b][0] = g_rp.out[b][1] = 0.0f;
    }
    for (int p = 0; p < 4; p++) {
        g_rp.port_src[p] = RA_SRC_EFFECTS;
        g_rp.port_path[p][0] = 0;
    }
    pcm_zero();
    g_rp.unity_frames = 0;
    g_rp.n = g_rp.rd = 0;
    if (g_ra->fifo && g_ra->fifo_cap)
        fifo_resync();
    g_rp.frame_seen = g_ra->frame;
}

void ra_present_begin(uint32_t frames)
{
    (void)frames;
    if (g_rp.frame_seen != g_ra->frame) {
        /* the model moved without us (a save-state load, a test resetting the clock): take
         * the copies again; PCM parts restart empty (those blocks play at the model level) */
        for (int b = 0; b < RA_BUSES; b++)
            g_rp.rev_ok[b] = 0;
        pcm_zero();
        if (g_ra->fifo && g_ra->fifo_cap)
            fifo_resync();
    }
    if (!g_rp.on && !targets_unity()) {
        g_rp.on = 1;
        g_rp.unity_frames = 0;
        for (int b = 0; b < RA_BUSES; b++) {
            g_rp.out[b][0] = g_ra->bus[b].out[0];
            g_rp.out[b][1] = g_ra->bus[b].out[1];
            g_rp.rev_ok[b] = 0;
        }
    }
    if (g_rp.on)
        for (int b = 0; b < RA_BUSES; b++)
            if (!g_rp.rev_ok[b])
                g_rp.rev_ok[b] = rev_clone(b);
}

void ra_present_end(uint32_t frames)
{
    g_rp.frame_seen = g_ra->frame + frames;   /* render() advances the frame after the mix */
    if (!g_rp.on)
        return;
    g_rp.frames_on += frames;
    if (!targets_unity() || !gains_unity()) {
        g_rp.unity_frames = 0;
        return;
    }
    uint32_t before = g_rp.unity_frames;
    g_rp.unity_frames += frames;
    /* back at 1: the second mix equals the model once the reverb copies do */
    if (g_rp.unity_frames / UNITY_CHECK != before / UNITY_CHECK || g_rp.unity_frames >= UNITY_GIVE_UP) {
        int same = 1;
        for (int b = 0; b < RA_BUSES && same; b++)
            same = rev_equal(b);
        if (same || g_rp.unity_frames >= UNITY_GIVE_UP)
            g_rp.on = 0;
    }
}
