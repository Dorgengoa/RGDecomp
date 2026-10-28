/* SPDX-License-Identifier: CC0-1.0 */
/* Game-facing movie service (docs/MOVIE.md "Override list").
 *
 * The overrides of the game's movie layer (overrides/src/main/movie/) call these. They
 * use only plain C types, so the overrides declare them locally and game/ needs no extra
 * include path. One movie at a time (the game has one player), one host thread.
 *
 * Time comes from the kernel's virtual clock (ps2k_now) unless a test installs its own.
 * The A/V mode is a runtime setting: RG_MOVIE_SYNC=audio (default) or retail in the
 * environment, or rg_movie_g_set_sync(). */
#ifndef RG_MOVIE_GAME_H
#define RG_MOVIE_GAME_H

#include <stddef.h> /* size_t (not pulled in by <stdint.h> on glibc) */
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* rg_movie_g_update flags */
#define RG_MOVIE_G_STARTED  1  /* display + audio started (game D_004817BC) */
#define RG_MOVIE_G_FINISHED 2  /* MovieIsFinished: complete, skipped, stopped or failed */
#define RG_MOVIE_G_PAUSED   4

/* MovieOpen: start `path` (the game's movie path). audio = the game's audio flag
 * (D_004817B8), loop = its loop flag (D_004817C8). 0, or <0 if the movie cannot be
 * played (the service then reports FINISHED so the game moves on). */
int rg_movie_g_open(const char *path, int audio, int loop);
/* picture size (0 x 0 when nothing is open) */
void rg_movie_g_size(int *w, int *h);
/* MoviePlayerWaitTick: pump. may_start = the game's own start condition besides the
 * frame FIFO (MovieAudioIsPreset_1d2490). Returns RG_MOVIE_G_* flags. */
int rg_movie_g_update(int may_start);
/* MovieGetFrameCount: pictures decoded so far */
unsigned rg_movie_g_frames_decoded(void);
/* MovieFrameQueueSendNext: 1 and the frame written to dst in the GS upload block layout
 * (16x16 RGBA32 blocks, column-major; w*h*4 bytes) if a new frame is due now, else 0. */
int rg_movie_g_take_frame(void *dst);
/* The original private-stream-1 audio bytes (SShd/SSbd), for the AudioDec feed. */
unsigned rg_movie_g_read_ss(void *dst, unsigned n);
void rg_movie_g_pause(int paused);
/* MoviePlayerShutdown / skip */
void rg_movie_g_close(void);

/* Event observer (timing record, docs/TIMING-LOCKSTEP.md): called at the start of
 * rg_movie_g_open (event RG_MOVIE_G_EV_OPEN, the game's path) and of every
 * rg_movie_g_close (RG_MOVIE_G_EV_CLOSE; path NULL, active = a movie was open).
 * NULL removes it.  One observer. */
#define RG_MOVIE_G_EV_OPEN  1
#define RG_MOVIE_G_EV_CLOSE 2
typedef void (*rg_movie_g_hook_fn)(void *user, int event, const char *path, int active);
void rg_movie_g_set_hook(rg_movie_g_hook_fn fn, void *user);

/* configuration */
void rg_movie_g_set_sync(int retail);                    /* 0 audio-led (default), 1 retail */
void rg_movie_g_set_data_root(const char *dir);          /* default: runtime data dir, $RG_DATA, "data" */
void rg_movie_g_set_clock(uint64_t (*now)(void));        /* tests; NULL = ps2k_now */

/* Save-state hook (docs/TEST-FIXTURES.md; rg-game registers it as "movie"):
 * the playing movie's file positions; after a load the files are reopened. */
size_t rg_movie_g_ss_size(void);
int rg_movie_g_ss_save(void *buf, size_t cap);
int rg_movie_g_ss_load(const void *buf, size_t n);

/* Runtime binding (src/runtime): sets the data root from the runtime config.  (It used to
 * install IPU register/FIFO hooks on the hwbus and the fromIPU/toIPU DMAC channels; the
 * game code that touched the IPU is now stubbed out -- docs/NATIVE-CPU.md section 8 -- so
 * nothing is left to catch.) */
void rg_movie_runtime_attach(void);       /* rg_runtime_set_service_hook(rg_movie_runtime_service) */
void rg_movie_runtime_service(void *user); /* the hook itself (call it from a combined hook) */

/* The ViBuf* stub overrides call this: message + abort (a caller of the dead IPU layer). */
void rg_movie_g_unreachable(const char *fn);

#ifdef __cplusplus
}
#endif
#endif
