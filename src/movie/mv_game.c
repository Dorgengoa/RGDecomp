/* SPDX-License-Identifier: CC0-1.0 */
/* Game-facing movie service: one global rg_movie driven by the movie-layer overrides
 * (movie_game.h, docs/MOVIE.md "Override list"). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie.h"
#include "movie_game.h"
#include "ps2k.h"

static rg_movie *g_m;
static int g_sync = -1;           /* -1: not set, read RG_MOVIE_SYNC */
static char g_root[512];
static uint64_t (*g_clock)(void);
static int g_paused;

static uint64_t now(void) { return g_clock ? g_clock() : ps2k_now(); }

void rg_movie_g_set_sync(int retail) { g_sync = retail ? 1 : 0; }
void rg_movie_g_set_clock(uint64_t (*fn)(void)) { g_clock = fn; }
void rg_movie_g_set_data_root(const char *dir) { snprintf(g_root, sizeof g_root, "%s", dir ? dir : ""); }

static int sync_mode(void)
{
    if (g_sync >= 0) return g_sync;
    const char *e = getenv("RG_MOVIE_SYNC");
    return (e && !strcmp(e, "retail")) ? 1 : 0;
}

static rg_movie_g_hook_fn g_hook;
static void *g_hook_user;
void rg_movie_g_set_hook(rg_movie_g_hook_fn fn, void *user) { g_hook = fn; g_hook_user = user; }

int rg_movie_g_open(const char *path, int audio, int loop)
{
    if (g_hook) g_hook(g_hook_user, RG_MOVIE_G_EV_OPEN, path, g_m != NULL);
    rg_movie_config c;
    rg_movie_config_default(&c);
    c.data_root = g_root[0] ? g_root : NULL;
    c.sync = sync_mode() ? RG_MOVIE_SYNC_RETAIL : RG_MOVIE_SYNC_AUDIO;
    c.audio = audio != 0;
    c.loop = loop != 0;
    rg_movie_destroy(g_m);
    g_m = rg_movie_create(&c);
    g_paused = 0;
    if (!g_m) return RG_MV_ERR_NOMEM;
    int r = rg_movie_start(g_m, path, now());
    if (r) fprintf(stderr, "[movie] cannot play '%s': %s\n", path ? path : "(null)", rg_movie_error(g_m));
    return r;
}

void rg_movie_g_size(int *w, int *h)
{
    rg_movie_status st;
    *w = *h = 0;
    if (!g_m) return;
    rg_movie_get_status(g_m, &st);
    *w = st.width;
    *h = st.height;
}

int rg_movie_g_update(int may_start)
{
    if (!g_m) return RG_MOVIE_G_FINISHED;
    rg_movie_set_start_gate(g_m, may_start);
    rg_movie_update(g_m, now());
    rg_movie_status st;
    rg_movie_get_status(g_m, &st);
    return (st.started ? RG_MOVIE_G_STARTED : 0) | (st.finished ? RG_MOVIE_G_FINISHED : 0) |
           (st.state == RG_MOVIE_PAUSED ? RG_MOVIE_G_PAUSED : 0);
}

unsigned rg_movie_g_frames_decoded(void)
{
    rg_movie_status st;
    if (!g_m) return 0;
    rg_movie_get_status(g_m, &st);
    return st.frames_decoded;
}

int rg_movie_g_take_frame(void *dst)
{
    rg_mvframe f;
    if (!g_m || !rg_movie_take_frame(g_m, now(), &f)) return 0;
    if (dst) rg_mv_to_ps2_blocks(&f, (uint8_t *)dst, 0x80);
    return 1;
}

unsigned rg_movie_g_read_ss(void *dst, unsigned n) { return g_m ? rg_movie_read_ss(g_m, (uint8_t *)dst, n) : 0; }

void rg_movie_g_pause(int paused)
{
    if (!g_m || paused == g_paused) return;
    g_paused = paused;
    if (paused) rg_movie_pause(g_m, now());
    else rg_movie_resume(g_m, now());
}

void rg_movie_g_close(void)
{
    if (g_hook) g_hook(g_hook_user, RG_MOVIE_G_EV_CLOSE, NULL, g_m != NULL);
    if (!g_m) return;
    rg_movie_skip(g_m);
    rg_movie_destroy(g_m);
    g_m = NULL;
    g_paused = 0;
}

/* ---- save states (docs/TEST-FIXTURES.md) ---------------------------------
 * g_m and everything under it are model memory (state heap, raw); only the
 * FILEs of the playing movie are host state.  Saved: the decoder's file
 * position.  Loaded: both files reopened (the audio reader seeks per read). */
typedef struct mv_ss_blob {
    uint32_t magic;          /* "MVS1" */
    int32_t has_dec, has_audio, pad;
    int64_t dec_pos;
} mv_ss_blob;

size_t rg_movie_g_ss_size(void) { return sizeof(mv_ss_blob); }

int rg_movie_g_ss_save(void *buf, size_t cap)
{
    mv_ss_blob b;
    if (cap < sizeof b) return -1;
    memset(&b, 0, sizeof b);
    b.magic = 0x3153564Du;
    rg_mvdec *d = rg_movie_ss_decoder(g_m);
    rg_mvaudio *a = rg_movie_ss_audio(g_m);
    b.dec_pos = rg_mvdec_ss_tell(d);
    b.has_dec = b.dec_pos >= 0;
    b.has_audio = rg_mvaudio_ss_file_backed(a);
    memcpy(buf, &b, sizeof b);
    return (int)sizeof b;
}

int rg_movie_g_ss_load(const void *buf, size_t n)
{
    mv_ss_blob b;
    if (n != sizeof b) return -1;
    memcpy(&b, buf, sizeof b);
    if (b.magic != 0x3153564Du) return -1;
    if (b.has_dec && rg_mvdec_ss_reopen(rg_movie_ss_decoder(g_m), b.dec_pos) != 0) return -1;
    if (b.has_audio && rg_mvaudio_ss_reopen(rg_movie_ss_audio(g_m)) != 0) return -1;
    return 0;
}

/* ---- the game's own IPU / DMA ch3-4 layer (docs/NATIVE-CPU.md section 8) -
 * The ViBuf* functions that programmed the IPU, DMA channels 3/4 and D_ENABLE are
 * overridden by stubs that call this: nothing linked references them
 * (tools/native/reach_census.py), so a call means a new caller appeared. */
void rg_movie_g_unreachable(const char *fn)
{
    fprintf(stderr, "[movie] %s: the game's IPU movie layer is not part of the port (the movie "
                    "service replaces it; docs/NATIVE-CPU.md section 8): unexpected call\n",
            fn ? fn : "?");
    fflush(stderr);
    abort();
}
