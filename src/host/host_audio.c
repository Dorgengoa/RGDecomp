/* SPDX-License-Identifier: CC0-1.0 */
/* Output-queue regulator for the host audio stream (docs/SOUND.md
 * "Load-screen audio", docs/HOST.md "Audio").  Pure: no SDL, no clock.
 *
 * The runtime pushes each field's audio right after the field, on the
 * virtual clock that the pacer keeps on wall time.  Without a cushion the
 * device queue holds about one field, so any field that ends late (a CD
 * read, a shader compile, a slow present) starves the device.  The cushion
 * is built from silence, never from game audio, so what the game rendered is
 * untouched. */
#include <string.h>

#include "host.h"

void rg_audio_reg_init(rg_audio_reg *r, uint32_t target_frames)
{
    rg_audio_reg z = {0};
    *r = z;
    r->target = target_frames;
    r->ratio = 1.0;
}

void rg_audio_reg_resync(rg_audio_reg *r) { r->resync = 1; }

/* ---- output device and focus (docs/HOST.md "Audio devices and focus") ---- */
static int lower(int c) { return c >= 'A' && c <= 'Z' ? c + 32 : c; }

int rg_audio_device_pick(const char *want, const char *const *names, int n)
{
    if (!want || !*want || !names) return -1;
    for (int i = 0; i < n; i++)
        if (names[i] && !strcmp(names[i], want)) return i;
    for (int i = 0; i < n; i++) {
        const char *a = names[i], *b = want;
        if (!a) continue;
        while (*a && *b && lower((unsigned char)*a) == lower((unsigned char)*b)) { a++; b++; }
        if (!*a && !*b) return i;
    }
    return -1;
}

float rg_audio_output_gain(float volume, int focused, int keep_playing)
{
    float v = volume < 0 ? 0 : volume > 1 ? 1 : volume;
    return focused || keep_playing ? v : 0.0f;
}

/* Adaptive cushion (docs/NATIVE-THREADS.md "3h"): a starve means a game-thread stall outlasted
 * the cushion.  The audio of those fields does not exist yet (the game renders it), so no
 * thread can fill the gap; a deeper cushion is the only cover for the NEXT stall of that size.
 * Grow by what the device starved (+25 % + 10 ms), at most max_target; after ADAPT_CALM pushes
 * without a starve step back towards the base by ADAPT_STEP every ADAPT_EVERY pushes (the
 * drift trim then drains the excess at 0.5 %, inaudible).  Costs A/V latency only while the
 * machine stalls the game. */
#define ADAPT_CALM  1200u   /* ~20 s */
#define ADAPT_EVERY 120u    /* ~2 s */
#define ADAPT_STEP  384u    /* 8 ms */

void rg_audio_reg_adapt(rg_audio_reg *r, uint32_t max_frames)
{
    if (!r->base_target || r->target < r->base_target) r->base_target = r->target;
    r->max_target = max_frames;
    if (r->target > max_frames && max_frames >= r->base_target) r->target = max_frames;
}

void rg_audio_reg_push(rg_audio_reg *r, uint32_t queued, int starved, uint32_t frames,
                       uint32_t *pad, uint32_t *drop)
{
    *pad = 0;
    *drop = 0;
    r->pushes++;
    if (!r->target) {
        r->ratio = 1.0;
        return;
    }
    uint32_t owed = r->owed_in, sf = r->starve_in;
    r->owed_in = 0;
    r->starve_in = 0;
    if (r->base_target && r->max_target > r->base_target && r->primed) {
        if (starved && sf < r->max_target) {
            /* (not after a starve longer than the cap: a load-class hitch no cushion covers;
             * the latency would stay for nothing.  A host-clock pacer drops the debt of any
             * stall over 4 phases (a re-anchor), so re-anchors are not excluded) */
            uint32_t g = sf + sf / 4 + 480u;
            uint32_t nt = r->target + g > r->max_target ? r->max_target : r->target + g;
            if (nt > r->target) {
                r->target = nt;
                r->grows++;
            }
            r->calm = 0;
        } else if (starved || queued < r->target / 3) {
            r->calm = 0;   /* (a stall the cushion covered, but only just: keep it) */
        } else if (++r->calm >= ADAPT_CALM && r->target > r->base_target) {
            r->target = r->target - r->base_target > ADAPT_STEP ? r->target - ADAPT_STEP : r->base_target;
            r->calm = ADAPT_CALM - ADAPT_EVERY;
            r->shrinks++;
        }
    }
    uint32_t t = r->target;
    /* far over target: the pacer caught up after a hitch that had already
     * starved the device (and was refilled).  "Far" is half the target or
     * two fields, whichever is more; ordinary field-end jitter only ever
     * brings the queue below the target. */
    uint32_t hi = t + (t / 2 > 1602u ? t / 2 : 1602u);
    if (!r->primed) {
        *pad = queued < t ? t - queued : 0;
        r->primed = 1;
        r->resync = 0;
        r->err_avg = 0.0;
    } else if ((starved || r->resync) && queued < t / 2) {
        /* the cushion is gone: rebuild it now instead of starving again on
         * every late field until starvation itself has rebuilt it */
        /* ... less the owed phases' audio the pacer is about to push (a catch-up): half of
         * it, since running those phases takes wall time the device drains meanwhile */
        uint32_t have = queued + owed / 2;
        *pad = have < t ? t - have : 0;
        r->resync = 0;
        r->err_avg = 0.0;
    } else if (queued > hi) {
        uint32_t over = queued - t;
        *drop = over < frames ? over : frames;
        r->resync = 0;
    } else {
        r->resync = 0;
    }
    if (*pad) {
        r->primes++;
        r->pad_frames += *pad;
    }
    if (*drop) {
        r->drops++;
        r->drop_frames += *drop;
    }
    /* drift: the queue before a push should sit at the target (it is target
     * + one field just after the push and drains to the target by the next
     * one).  Trim the playback rate in proportion to the smoothed error,
     * correcting a 4 s worth of error per second at most 0.5 %. */
    double err = (double)queued + (double)*pad - (double)*drop - (double)t;
    r->err_avg += 0.05 * (err - r->err_avg);
    double adj = r->err_avg / (4.0 * 48000.0);
    if (adj > RG_AUDIO_RATIO_MAX) adj = RG_AUDIO_RATIO_MAX;
    if (adj < -RG_AUDIO_RATIO_MAX) adj = -RG_AUDIO_RATIO_MAX;
    r->ratio = 1.0 + adj;
}

void rg_audio_declick(int16_t *lr, uint32_t n, const int16_t from[2])
{
    for (uint32_t i = 0; i < n; i++) {
        /* linear crossfade: frame 0 is `from`, frame n is the signal */
        int32_t g = (int32_t)((i * 32768u) / n);
        for (int c = 0; c < 2; c++) {
            int32_t v = (from[c] * (32768 - g) + lr[2 * i + c] * g) / 32768;
            lr[2 * i + c] = (int16_t)(v < -32768 ? -32768 : v > 32767 ? 32767 : v);
        }
    }
}
