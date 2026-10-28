/* SPDX-License-Identifier: CC0-1.0 */
/* Game-side entry points of the native audio engine (ra_game.c, docs/NATIVE-AUDIO.md
 * "Game side").  The game's overrides see the same declarations through
 * include/port/native_audio.h (plain C types only). */
#ifndef RG_NATIVE_AUDIO_GAME_H
#define RG_NATIVE_AUDIO_GAME_H

#ifdef __cplusplus
extern "C" {
#endif

#define RG_AUDIO_HLE     0
#define RG_AUDIO_NATIVE  1
#define RG_AUDIO_COMPARE 2

#define RG_AUDIO_ROUTE_NATIVE 0  /* native mode: engine only */
#define RG_AUDIO_ROUTE_BOTH   1  /* native mode: engine and HLE (mixer settings) */
#define RG_AUDIO_ROUTE_HLE    2  /* HLE only (IOP addresses, raw libsd) */

int rg_audio_mode(void);
int rg_audio_pcm_native(void);
int rg_audio_movie_native(void);
int rg_audio_hle_needed(void);
int rg_audio_game_route(int cmd);
void rg_audio_game_init(void);
int rg_audio_game_cmd(int cmd, const int *args);
int rg_audio_game_bank(const void *hd, unsigned hd_size, const void *bd, unsigned bd_size);
int rg_audio_game_seq(const void *sq, unsigned size);
void rg_audio_game_compare(int cmd, int hle, int native);
unsigned rg_audio_game_mismatches(void);
int rg_audio_game_pcm(int fno, const int *args);
int rg_audio_game_pcm_mix(int port, const void *block, int vol_l, int vol_r);
/* the stream file a PCM port plays (presentation only: which source volume applies) */
void rg_audio_game_pcm_source(int port, const char *path);
unsigned rg_audio_game_stream_alloc(unsigned size);
void rg_audio_game_stream_map(unsigned hle_addr, unsigned size);
void rg_audio_game_stream_free(unsigned addr);
int rg_audio_game_stream_write(unsigned addr, const void *src, int n);

/* runtime glue (ra_host.c): clocks in 48 kHz frames.  native = the virtual clock,
 * hle = the HLE's own render position (compare mode: commands land where the HLE
 * applied them), hle_origin = the HLE's 240 Hz tick origin. */
void rg_audio_runtime_init(unsigned long long (*native_clock)(void *),
                           unsigned long long (*hle_clock)(void *),
                           unsigned long long (*hle_origin)(void *), void *user);
void rg_audio_runtime_sync(void);
/* after the runtime read n HLE frames into lr: native mode adds the engine's frames
 * (aligned to the end), compare mode writes them to $RG_AUDIO_NATIVE_WAV */
void rg_audio_runtime_mix(short *lr, unsigned n);
/* RG_IOP=native (docs/NATIVE-IOP.md): no HLE sound renders, so the runtime reads the
 * engine's own frames (everything rendered up to the last sync, at most max).  0 unless
 * native mode and the game started its sound driver. */
unsigned rg_audio_runtime_read(short *lr, unsigned max);
/* the frames to PLAY for the n frames the last rg_audio_runtime_read returned in lr: the
 * presentation mix with the per-source volumes (lr itself when there is none).  The run
 * hash and RG_AUDIO_WAV keep using lr (docs/NATIVE-AUDIO.md "Source volumes"). */
const short *rg_audio_runtime_present(const short *lr, unsigned n);
/* audio.music_volume / effects_volume / voice_volume / movie_volume, percent */
void rg_audio_runtime_volumes(int music, int effects, int voice, int movie);
void rg_audio_runtime_shutdown(void);

#ifdef __cplusplus
}
#endif
#endif
