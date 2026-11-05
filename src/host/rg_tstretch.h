/* SPDX-License-Identifier: CC0-1.0
 * Pitch-keeping time compression of the host audio stream (WSOLA) for gameplay.battle_speed
 * (docs/SETTINGS.md "Gameplay options", docs/SOUND.md "Battle speed-up").
 *
 * The game's sound is rendered on the virtual VBlank clock (its frames, and the run hash, are
 * unchanged); when battles run k VBlank phases per host phase the device gets k times as many
 * frames per host second.  This stage plays them back in 1/k of the time with the pitch kept:
 * waveform-similarity overlap-add, 20 ms periodic-Hann windows at 50 % overlap (sums to 1),
 * each next window taken within +-10 ms of its nominal input position where it best matches
 * the natural continuation of the previous one (normalised cross-correlation on a mono mix,
 * coarse then fine).  At speed 1 the search is off and the windows sit on the input's own
 * grid: the output is the input, delayed by one window (RG_TS_N frames), exactly up to float
 * rounding; speed changes are seamless.  Pure logic, unit-tested by rg-host-tests. */
#ifndef RG_TSTRETCH_H
#define RG_TSTRETCH_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RG_TS_N    960u               /* window: 20 ms at 48 kHz */
#define RG_TS_HS   (RG_TS_N / 2)      /* output hop */
#define RG_TS_S    480                /* search radius (frames) */
#define RG_TS_BUF  16384u             /* input frames kept (stereo) */

typedef struct rg_tstretch {
    float in[RG_TS_BUF * 2];          /* input frames not yet consumed, from in[0] */
    uint32_t len;                     /* frames in `in` */
    double pos;                       /* nominal start of the next window (frames into `in`) */
    int32_t prev;                     /* start of the last window taken (-RG_TS_HS: none yet) */
    float ola[RG_TS_HS * 2];          /* the last window's second half, windowed */
    float win[RG_TS_N];
    int started;
    uint64_t frames_in, frames_out;   /* statistics */
} rg_tstretch;

void rg_tstretch_init(rg_tstretch *t);
/* Feed n stereo frames played at `speed` (>= 1: output time = input time / speed; 1 = as is),
 * write at most cap output frames to out; returns the frames written.  Input that does not fit
 * the buffer is dropped (the caller's queue regulator sees fewer frames). */
uint32_t rg_tstretch_process(rg_tstretch *t, const int16_t *in, uint32_t n, double speed,
                             int16_t *out, uint32_t cap);

#ifdef __cplusplus
}
#endif
#endif
