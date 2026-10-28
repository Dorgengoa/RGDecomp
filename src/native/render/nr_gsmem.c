/* SPDX-License-Identifier: CC0-1.0 */
/* GS local-memory address arithmetic (nr_gsmem.h).  The formulas of src/ps2/gs/gs_mem.c
 * (block number from interleaved block-x/y bits, word in a column from x/y bits). */
#include "nr_gsmem.h"

#include "gs.h"

static inline uint32_t blk32(uint32_t bx, uint32_t by)
{
    return (bx & 1) | ((by & 1) << 1) | ((bx & 2) << 1) | ((by & 2) << 2) | ((bx & 4) << 2);
}
static inline uint32_t blk16(uint32_t bx, uint32_t by)
{
    return (by & 1) | ((bx & 1) << 1) | ((by & 2) << 1) | ((bx & 2) << 2) | ((by & 4) << 2);
}
static inline uint32_t blk16s(uint32_t bx, uint32_t by)
{
    return (by & 1) | ((bx & 1) << 1) | ((by & 4) << 0) | ((by & 2) << 2) | ((bx & 2) << 3);
}
static inline uint32_t colword32(uint32_t x, uint32_t y) { return (x & 1) | ((y & 1) << 1) | ((x & 6) << 1); }
static inline uint32_t blkaddr(uint32_t bp, uint32_t page, uint32_t blk) { return ((bp + page * 32u + blk) & 0x3FFFu) << 8; }

static uint32_t addr32(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, int z)
{
    uint32_t page = (x >> 6) + (y >> 5) * bw;
    uint32_t blk = blk32((x >> 3) & 7, (y >> 3) & 3);
    if (z) blk ^= 24;
    return blkaddr(bp, page, blk) | (((y >> 1) & 3) << 6) | (colword32(x & 7, y & 1) << 2);
}
static uint32_t addr16(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, int s, int z)
{
    uint32_t page = (x >> 6) + (y >> 6) * bw;
    uint32_t bx = (x >> 4) & 3, by = (y >> 3) & 7;
    uint32_t blk = s ? blk16s(bx, by) : blk16(bx, by);
    if (z) blk ^= 24;
    return blkaddr(bp, page, blk) | (((y >> 1) & 3) << 6) | (colword32(x & 7, y & 1) << 2) | (((x >> 3) & 1) << 1);
}
static uint32_t addr8(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    uint32_t page = (x >> 7) + (y >> 6) * (bw >> 1);
    uint32_t blk = blk32((x >> 4) & 7, (y >> 4) & 3);
    uint32_t col = (y >> 2) & 3, cy = y & 3, hi = cy >> 1, xx = x & 7;
    if (hi ^ (col & 1)) xx ^= 4;
    return blkaddr(bp, page, blk) | (col << 6) | (colword32(xx, cy & 1) << 2) | ((((x >> 3) & 1) << 1) | hi);
}
static uint32_t addr4n(uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    uint32_t page = (x >> 7) + (y >> 7) * (bw >> 1);
    uint32_t blk = blk16((x >> 5) & 3, (y >> 4) & 7);
    uint32_t col = (y >> 2) & 3, cy = y & 3, hi = cy >> 1, xx = x & 7;
    if (hi ^ (col & 1)) xx ^= 4;
    return ((blkaddr(bp, page, blk) | (col << 6) | (colword32(xx, cy & 1) << 2)) << 1) + ((((x >> 3) & 3) << 1) | hi);
}

uint32_t nr_px_addr(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, int *nib)
{
    uint32_t a;
    x &= 2047;
    y &= 2047;
    if (nib) *nib = 0;
    switch (psm) {
    case GS_PSMCT32: case GS_PSMCT24: case GS_PSMT8H: case GS_PSMT4HL: case GS_PSMT4HH: return addr32(bp, bw, x, y, 0);
    case GS_PSMZ32: case GS_PSMZ24: return addr32(bp, bw, x, y, 1);
    case GS_PSMCT16: return addr16(bp, bw, x, y, 0, 0);
    case GS_PSMCT16S: return addr16(bp, bw, x, y, 1, 0);
    case GS_PSMZ16: return addr16(bp, bw, x, y, 0, 1);
    case GS_PSMZ16S: return addr16(bp, bw, x, y, 1, 1);
    case GS_PSMT8: return addr8(bp, bw, x, y);
    case GS_PSMT4:
        a = addr4n(bp, bw, x, y);
        if (nib) *nib = (int)(a & 1);
        return a >> 1;
    default: return addr32(bp, bw, x, y, 0);
    }
}

int nr_psm_bpp(int psm)
{
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32: return 32;
    case GS_PSMCT24: case GS_PSMZ24: return 24;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: return 16;
    case GS_PSMT8: case GS_PSMT8H: return 8;
    case GS_PSMT4: case GS_PSMT4HL: case GS_PSMT4HH: return 4;
    default: return 0;
    }
}

void nr_px_word(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y, uint32_t *word, uint32_t *mask,
                uint32_t *shift)
{
    int nib;
    uint32_t a = nr_px_addr(psm, bp, bw, x, y, &nib), sh, m;
    switch (psm) {
    case GS_PSMCT32: case GS_PSMZ32: sh = 0; m = 0xFFFFFFFFu; break;
    case GS_PSMCT24: case GS_PSMZ24: sh = 0; m = 0x00FFFFFFu; break;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: sh = (a & 2) * 8; m = 0xFFFFu << sh; break;
    case GS_PSMT8: sh = (a & 3) * 8; m = 0xFFu << sh; break;
    case GS_PSMT4: sh = (a & 3) * 8 + (nib ? 4 : 0); m = 0xFu << sh; break;
    case GS_PSMT8H: sh = 24; m = 0xFF000000u; break;
    case GS_PSMT4HL: sh = 24; m = 0x0F000000u; break;
    case GS_PSMT4HH: sh = 28; m = 0xF0000000u; break;
    default: sh = 0; m = 0xFFFFFFFFu; break;
    }
    *word = (a >> 2) & 0xFFFFFu;
    *mask = m;
    *shift = sh;
}
