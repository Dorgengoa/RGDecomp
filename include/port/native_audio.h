/* SPDX-License-Identifier: CC0-1.0 */
/* Game-side view of the native audio engine (src/native/audio/rg_audio_game.h,
 * docs/NATIVE-AUDIO.md), for the overrides of the game's sound driver layer.  Plain C
 * types only, so it can be included next to the game's types.h. */
#ifndef RG_PORT_NATIVE_AUDIO_H
#define RG_PORT_NATIVE_AUDIO_H

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
/* the stream file a PCM port plays (presentation only: which source volume applies,
 * docs/NATIVE-AUDIO.md "Source volumes") */
void rg_audio_game_pcm_source(int port, const char *path);
unsigned rg_audio_game_stream_alloc(unsigned size);
void rg_audio_game_stream_map(unsigned hle_addr, unsigned size);
void rg_audio_game_stream_free(unsigned addr);
int rg_audio_game_stream_write(unsigned addr, const void *src, int n);


#ifdef __cplusplus
}
#endif
#endif
