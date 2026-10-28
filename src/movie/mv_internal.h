/* SPDX-License-Identifier: CC0-1.0 */
/* Internals of the movie decoder (docs/MOVIE.md). Not part of the public API. */
#ifndef RG_MV_INTERNAL_H
#define RG_MV_INTERNAL_H

#include <stdint.h>
#include "movie.h"

/* ---- VLC tables (mv_vlc.c), built from the code lists of ISO/IEC 13818-2 Annex B */

typedef struct mv_vlc {   /* small single-level table indexed by the next `bits` bits */
    int8_t val;           /* decoded value */
    uint8_t len;          /* code length; 0 = no such code */
} mv_vlc;

enum { MV_RUN_EOB = 64, MV_RUN_ESC = 65 };

typedef struct mv_dct_ent {
    uint8_t run;          /* 0..31, MV_RUN_EOB or MV_RUN_ESC */
    uint8_t level;        /* magnitude (sign bit follows the code) */
    uint8_t len;          /* code length without the sign bit; 0 = invalid */
    uint8_t pad;
} mv_dct_ent;

typedef struct mv_dct_tab {   /* two-level: codes up to 12 bits, then the 8-zeros group */
    mv_dct_ent a[4096];       /* index: next 12 bits, for codes not starting 0000 0000 */
    mv_dct_ent b[256];        /* index: bits 9..16, for codes starting 0000 0000 (13-16 bits) */
} mv_dct_tab;

#define MV_MBA_BITS 11
#define MV_MBT_BITS 6
#define MV_CBP_BITS 9
#define MV_MC_BITS 10
#define MV_DCL_BITS 9
#define MV_DCC_BITS 10

/* macroblock_type flags */
enum { MB_QUANT = 1, MB_FWD = 2, MB_BWD = 4, MB_PAT = 8, MB_INTRA = 16 };

typedef struct mv_tables {
    mv_vlc mba[1 << MV_MBA_BITS];      /* B-1; value 34 = macroblock_escape */
    mv_vlc mbt[3][1 << MV_MBT_BITS];   /* B-2 (I), B-3 (P), B-4 (B); value = MB_* flags */
    mv_vlc cbp[1 << MV_CBP_BITS];      /* B-9 */
    mv_vlc mc[1 << MV_MC_BITS];        /* B-10 magnitude (sign bit follows if != 0) */
    mv_vlc dcl[1 << MV_DCL_BITS];      /* B-12 */
    mv_vlc dcc[1 << MV_DCC_BITS];      /* B-13 */
    mv_dct_tab dct0;                   /* B-14 */
    mv_dct_tab dct1;                   /* B-15 */
} mv_tables;

/* Builds every table; returns 0, or -1 if a code list is not prefix-free (a table bug). */
int mv_tables_build(mv_tables *t);
/* For tests: number of codes in each list, and a Kraft-sum check. */
int mv_tables_selftest(char *err, size_t cap);

extern const uint8_t mv_zigzag[64];
extern const uint8_t mv_default_intra_q[64];   /* natural order */
extern const uint8_t mv_nonlinear_qscale[32];

/* ---- IDCT (mv_idct.c). blk: 64 dequantized coefficients, natural order (row = vertical
 * frequency). rowmask: bit r set if row r may be non-zero (0xFF = unknown). */
void mv_idct_put(const int32_t *blk, unsigned rowmask, uint8_t *dst, int stride);
void mv_idct_add(const int32_t *blk, unsigned rowmask, uint8_t *dst, int stride);
/* The 8x8 IDCT without rounding/saturation, double precision (reference for tests). */
void mv_idct_ref(const int32_t *blk, double *out);
/* The production transform's unclamped integer output (for accuracy tests). */
void mv_idct_int(const int32_t *blk, unsigned rowmask, int32_t *out);

#endif
