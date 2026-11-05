/* SPDX-License-Identifier: CC0-1.0
 * WSOLA time compression of the host audio stream (rg_tstretch.h). */
#include "rg_tstretch.h"

#include <math.h>
#include <string.h>

void rg_tstretch_init(rg_tstretch *t)
{
    memset(t, 0, sizeof *t);
    for (uint32_t i = 0; i < RG_TS_N; i++)
        t->win[i] = (float)(0.5 - 0.5 * cos(2.0 * 3.14159265358979323846 * (double)i / (double)RG_TS_N));
    /* one hop of silence before the stream: the first window then overlaps a (silent) previous
     * one, and at speed 1 the output is the input delayed by a hop plus the window's look-ahead */
    t->len = RG_TS_HS;
    t->prev = -(int32_t)RG_TS_HS;
    t->pos = 0.0;
}

static float mono(const rg_tstretch *t, int32_t i) { return t->in[2 * i] + t->in[2 * i + 1]; }

/* normalised correlation of the candidate at c with the natural continuation at nat */
static double score(const rg_tstretch *t, int32_t nat, int32_t c, int step)
{
    double xy = 0.0, yy = 1e-3;
    for (int32_t i = 0; i < (int32_t)RG_TS_HS; i += step) {
        float y = mono(t, c + i);
        xy += (double)mono(t, nat + i) * y;
        yy += (double)y * y;
    }
    return xy / sqrt(yy);
}

static int16_t clamp16(float v)
{
    if (v > 32767.0f) return 32767;
    if (v < -32768.0f) return -32768;
    return (int16_t)lrintf(v);
}

uint32_t rg_tstretch_process(rg_tstretch *t, const int16_t *in, uint32_t n, double speed,
                             int16_t *out, uint32_t cap)
{
    if (speed < 1.0) speed = 1.0;
    if (speed > 8.0) speed = 8.0;
    uint32_t room = RG_TS_BUF - t->len;
    uint32_t take = n < room ? n : room;
    for (uint32_t i = 0; i < 2 * take; i++)
        t->in[2 * t->len + i] = (float)in[i];
    t->len += take;
    t->frames_in += take;
    uint32_t done = 0;
    int search = speed > 1.0001;
    for (;;) {
        int32_t nat = t->prev + (int32_t)RG_TS_HS;   /* where the last window's input continues */
        int32_t nom = search ? (int32_t)floor(t->pos + 0.5) : nat;
        if (!search)
            t->pos = (double)nat;                     /* back on the input's own grid */
        int32_t s = search && nat >= 0 ? RG_TS_S : 0;
        if (nom + s + (int32_t)RG_TS_N > (int32_t)t->len || done + RG_TS_HS > cap)
            break;
        int32_t best = nom;
        if (s) {
            int32_t lo = nom - s < 0 ? 0 : nom - s, hi = nom + s;
            double bs = -1e300;
            for (int32_t c = lo; c <= hi; c += 2) {     /* coarse: every 2nd lag, every 4th frame */
                double v = score(t, nat, c, 4);
                if (v > bs) { bs = v; best = c; }
            }
            int32_t c0 = best;
            bs = -1e300;
            for (int32_t c = c0 - 2; c <= c0 + 2; c++) { /* fine */
                if (c < lo || c > hi) continue;
                double v = score(t, nat, c, 1);
                if (v > bs) { bs = v; best = c; }
            }
        }
        const float *x = t->in + 2 * best;
        int16_t *o = out + 2 * done;
        for (uint32_t j = 0; j < RG_TS_HS; j++) {
            o[2 * j] = clamp16(t->ola[2 * j] + t->win[j] * x[2 * j]);
            o[2 * j + 1] = clamp16(t->ola[2 * j + 1] + t->win[j] * x[2 * j + 1]);
            t->ola[2 * j] = t->win[RG_TS_HS + j] * x[2 * (RG_TS_HS + j)];
            t->ola[2 * j + 1] = t->win[RG_TS_HS + j] * x[2 * (RG_TS_HS + j) + 1];
        }
        done += RG_TS_HS;
        t->prev = best;
        t->pos = search ? t->pos + (double)RG_TS_HS * speed : (double)(best + (int32_t)RG_TS_HS);
        /* drop input nothing can reach any more: the next natural continuation and the next
         * search window's start */
        int32_t keep = t->prev + (int32_t)RG_TS_HS;
        int32_t ns = (int32_t)floor(t->pos + 0.5) - RG_TS_S;
        if (search && ns < keep) keep = ns;
        if (keep > (int32_t)t->len) keep = (int32_t)t->len;
        if (keep > 0) {
            memmove(t->in, t->in + 2 * keep, (size_t)(t->len - (uint32_t)keep) * 2 * sizeof(float));
            t->len -= (uint32_t)keep;
            t->pos -= keep;
            t->prev -= keep;
        }
    }
    t->frames_out += done;
    return done;
}
