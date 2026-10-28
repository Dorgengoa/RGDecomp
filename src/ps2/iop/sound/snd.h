/* SPDX-License-Identifier: CC0-1.0 */
/* Sound HLE (PLAN.md D4/P4, docs/SOUND.md, protocol in docs/SOUND-PROTOCOL.md).
 *
 * Replaces the placeholder sound servers registered by iop_hle.c:
 *   0x80000701 sdr_driver (libsd remote calls + 0x90F0 Standard Kit command blocks:
 *              G0 SKSOUND, G1 SKHSYNTH, G2 SKMIDI, G3 SKMSIN)
 *   0x00123456 pcm_mixer (4-port PCM mixer feeding core 1 AutoDMA)
 * on top of the SPU2 engine in src/ps2/spu.
 *
 * Time: the engine renders on the virtual clock. 1 frame (48 kHz) = 3072 bus cycles
 * (147.456 MHz); one NTSC field = 800.8 frames. Every server call first renders up to
 * the current clock (so key ons and the movie read position land at exact sample
 * times), and the host drains the output FIFO each field:
 *     snd_sync(); n = snd_output_read(buf, max);  ->  rg_host_audio_push(h, buf, n)
 * Tools and tests without a clock (snd_set_clock(NULL)) pull with snd_render().
 * Single host thread; nothing locks. */
#ifndef RG_SND_H
#define RG_SND_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SND_CYCLES_PER_FRAME 3072u /* 147456000 / 48000 */

typedef struct snd_config {
    int interp;               /* SPU2_INTERP_* (default B-spline) */
    uint32_t fifo_frames;     /* output FIFO capacity (default 96000 = 2 s) */
    int quiet;                /* no stderr log of unknown calls (also env RG_IOP_QUIET) */
} snd_config;

typedef struct snd_stats {
    uint32_t sdr_calls, sk_calls, pcm_calls, unknown_calls;
    uint32_t key_ons, key_offs, voice_steals, no_layer;
    uint32_t seq_events, seq_notes;
    uint32_t bank_uploads, bank_bytes;
} snd_stats;

void snd_default_config(snd_config *cfg);
/* Reset all sound state and (re-)register the two servers with the SIF core
 * (sif_server_register replaces the placeholders). The clock defaults to sif_now().
 * 0 on success. */
int snd_install(const snd_config *cfg);
void snd_reset(void);

/* Clock (bus cycles). NULL = no clock: servers never render, use snd_render(). */
void snd_set_clock(uint64_t (*now)(void *user), void *user);
/* Render up to the clock into the output FIFO. Returns frames rendered by this call. */
uint32_t snd_sync(void);
uint32_t snd_output_available(void);
uint32_t snd_output_read(int16_t *lr, uint32_t max_frames);
uint64_t snd_output_dropped(void);
/* Pull API: render `frames` stereo s16 frames now (no FIFO, no clock). */
void snd_render(int16_t *lr, uint32_t frames);
uint64_t snd_frames_rendered(void);
/* Absolute clock frame of the next sample (install base + frames rendered). */
uint64_t snd_clock_frame(void);
/* Frames in NTSC field k so that the long-run rate is exactly 48000*1001/60000 per field. */
uint32_t snd_frames_for_field(uint64_t k);

/* The SPU2 instance (tests, tools, debugging). */
struct spu2;
struct spu2 *snd_spu(void);
const snd_stats *snd_get_stats(void);

/* Convenience front ends that go through the SIF RPC path exactly like the EE does
 * (sif_rpc_call + delivery), for tools and tests. Need sif_init() and snd_install().
 *   snd_sdremote: sceSdRemote(1, cmd, a1..a6) packing (buf[0] = self, buf[1..6] = args)
 *   snd_sk:       0x90F0 command block (16 words, w0 = module << 24)
 *   snd_pcm_rpc:  pcm_mixer call with up to 15 argument words */
int32_t snd_sdremote(uint32_t cmd, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4,
                     uint32_t a5, uint32_t a6);
int32_t snd_sk(const uint32_t blk[16]);
int32_t snd_pcm_rpc(uint32_t fno, int n, const uint32_t *args);

/* Introspection for tests. */
int snd_voices_playing(void);              /* hardware voices with a live envelope */
int snd_track_status(int track);
int snd_midi_playing(int track);           /* 1 while the track's sequence plays */
uint32_t snd_midi_ticks(int track);
uint32_t snd_movie_position(int core);     /* byte offset of the unit being played */

#ifdef __cplusplus
}
#endif
#endif
