/* SPDX-License-Identifier: CC0-1.0 */
/* The line-strand VU1 program as plain C (docs/NATIVE-RENDER.md "Line
 * strands", slice 2).  Retail packet 0x441660 (head at VU 0x320, table row 1,
 * material kind 1) with its main piece 0x441840 at 0x10E0 and the decode
 * pieces at 0x960 (skinned 0x43A020 on the golden route).
 *
 * Every record is a short segment a -> b in screen space drawn as four GS
 * lines offset by +-hw in x and in y (PRIM 1, attributes from PRMODE qw87.x,
 * GIF loop of 9 registers: one PACKED RGBAQ (16, 16, 16, alpha) and eight
 * XYZF2).  Two layouts, chosen by the batch header's .x:
 *   0x13: four vertices per record, segment P1 -> P2; drawn only when P1 and
 *         P2 are inside the guard band (qw109/110) and the strand does not
 *         fold ((s1-s0) x (s2-s0)).z * ((s2-s1) x (s3-s1)).z >= 0;
 *   else: two vertices per record, segment P0 -> P1, guard band only.
 * fade = clamp(1.11111 - 0.00277778 * w, 0, 1) (w of the segment's first
 * vertex's clip vector), alpha = int(64 fade), hw = 0.5 fade.  A record that
 * fails carries ADC on all eight vertices (nothing drawn).
 *
 * VU arithmetic (chopped singles, the program's operation order): the
 * records match the VU1 interpreter bit for bit (rg-nr-nmcheck). */
#ifndef RG_NR_VU1LN_H
#define RG_NR_VU1LN_H

#include <stdint.h>

#include "nr_vu1.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nr_lnrec {
    uint32_t alpha;            /* RGBAQ A (R = G = B = 16) */
    int32_t x[8], y[8], z[8];  /* ftoi4 of the screen vector */
    int adc;                   /* XYZF2 word 3: 0xFFFF8000 (ADC, no drawing kick) or 0 */
} nr_lnrec;

/* pos: decoded vertices of one batch (n of them), four (layout 0x13) or two
 * per record; c: VU qwords 0..111 (qw68-71 screen matrix, 109/110 guard).
 * Returns the record count written (at most max). */
int nr_vu1ln_records(const nr_qw *c, const float (*pos)[3], uint32_t n, int four, nr_lnrec *out, int max);

/* piece signature of the line main piece at 0x10E0 (corpus header) */
int nr_vu1ln_is_line_sig(const uint32_t sig[10]);

#ifdef __cplusplus
}
#endif
#endif
