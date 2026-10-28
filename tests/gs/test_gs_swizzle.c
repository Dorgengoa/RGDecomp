/* SPDX-License-Identifier: CC0-1.0 */
/* Swizzle tests.  The REFERENCE here is independent of src/ps2/gs/gs_mem.c:
 * it is built from the arrangement figures of the GS manual typed in as
 * literal tables (block order in a page, word/halfword/byte/nibble order in a
 * column pair), whereas the implementation uses bit formulas.  Every pixel of
 * a multi-page buffer is compared for every PSM. */
#include "gs_test_util.h"

/* block number in a page, [by][bx] */
static const int T_BLK32[4][8] = {
    { 0, 1, 4, 5, 16, 17, 20, 21 }, { 2, 3, 6, 7, 18, 19, 22, 23 },
    { 8, 9, 12, 13, 24, 25, 28, 29 }, { 10, 11, 14, 15, 26, 27, 30, 31 } };
static const int T_BLKZ32[4][8] = {
    { 24, 25, 28, 29, 8, 9, 12, 13 }, { 26, 27, 30, 31, 10, 11, 14, 15 },
    { 16, 17, 20, 21, 0, 1, 4, 5 }, { 18, 19, 22, 23, 2, 3, 6, 7 } };
static const int T_BLK16[8][4] = {
    { 0, 2, 8, 10 }, { 1, 3, 9, 11 }, { 4, 6, 12, 14 }, { 5, 7, 13, 15 },
    { 16, 18, 24, 26 }, { 17, 19, 25, 27 }, { 20, 22, 28, 30 }, { 21, 23, 29, 31 } };
static const int T_BLK16S[8][4] = {
    { 0, 2, 16, 18 }, { 1, 3, 17, 19 }, { 8, 10, 24, 26 }, { 9, 11, 25, 27 },
    { 4, 6, 20, 22 }, { 5, 7, 21, 23 }, { 12, 14, 28, 30 }, { 13, 15, 29, 31 } };
static const int T_BLKZ16[8][4] = {
    { 24, 26, 16, 18 }, { 25, 27, 17, 19 }, { 28, 30, 20, 22 }, { 29, 31, 21, 23 },
    { 8, 10, 0, 2 }, { 9, 11, 1, 3 }, { 12, 14, 4, 6 }, { 13, 15, 5, 7 } };
static const int T_BLKZ16S[8][4] = {
    { 24, 26, 8, 10 }, { 25, 27, 9, 11 }, { 16, 18, 0, 2 }, { 17, 19, 1, 3 },
    { 28, 30, 12, 14 }, { 29, 31, 13, 15 }, { 20, 22, 4, 6 }, { 21, 23, 5, 7 } };

/* 32-bit column (8x2): word index */
static const int T_COL32[2][8] = { { 0, 1, 4, 5, 8, 9, 12, 13 },
                                   { 2, 3, 6, 7, 10, 11, 14, 15 } };
/* 16-bit column (16x2): halfword index */
static const int T_COL16[2][16] = {
    { 0, 2, 8, 10, 16, 18, 24, 26, 1, 3, 9, 11, 17, 19, 25, 27 },
    { 4, 6, 12, 14, 20, 22, 28, 30, 5, 7, 13, 15, 21, 23, 29, 31 } };
/* 8-bit: rows 0-3 = even column, rows 4-7 = odd column; byte index within
 * the 128-byte column pair */
static const int T_COL8[8][16] = {
    { 0, 4, 16, 20, 32, 36, 48, 52, 2, 6, 18, 22, 34, 38, 50, 54 },
    { 8, 12, 24, 28, 40, 44, 56, 60, 10, 14, 26, 30, 42, 46, 58, 62 },
    { 33, 37, 49, 53, 1, 5, 17, 21, 35, 39, 51, 55, 3, 7, 19, 23 },
    { 41, 45, 57, 61, 9, 13, 25, 29, 43, 47, 59, 63, 11, 15, 27, 31 },
    { 96, 100, 112, 116, 64, 68, 80, 84, 98, 102, 114, 118, 66, 70, 82, 86 },
    { 104, 108, 120, 124, 72, 76, 88, 92, 106, 110, 122, 126, 74, 78, 90, 94 },
    { 65, 69, 81, 85, 97, 101, 113, 117, 67, 71, 83, 87, 99, 103, 115, 119 },
    { 73, 77, 89, 93, 105, 109, 121, 125, 75, 79, 91, 95, 107, 111, 123, 127 } };
/* 4-bit: nibble index within the 256-nibble column pair */
static const int T_COL4[8][32] = {
    { 0, 8, 32, 40, 64, 72, 96, 104, 2, 10, 34, 42, 66, 74, 98, 106,
      4, 12, 36, 44, 68, 76, 100, 108, 6, 14, 38, 46, 70, 78, 102, 110 },
    { 16, 24, 48, 56, 80, 88, 112, 120, 18, 26, 50, 58, 82, 90, 114, 122,
      20, 28, 52, 60, 84, 92, 116, 124, 22, 30, 54, 62, 86, 94, 118, 126 },
    { 65, 73, 97, 105, 1, 9, 33, 41, 67, 75, 99, 107, 3, 11, 35, 43,
      69, 77, 101, 109, 5, 13, 37, 45, 71, 79, 103, 111, 7, 15, 39, 47 },
    { 81, 89, 113, 121, 17, 25, 49, 57, 83, 91, 115, 123, 19, 27, 51, 59,
      85, 93, 117, 125, 21, 29, 53, 61, 87, 95, 119, 127, 23, 31, 55, 63 },
    { 192, 200, 224, 232, 128, 136, 160, 168, 194, 202, 226, 234, 130, 138, 162, 170,
      196, 204, 228, 236, 132, 140, 164, 172, 198, 206, 230, 238, 134, 142, 166, 174 },
    { 208, 216, 240, 248, 144, 152, 176, 184, 210, 218, 242, 250, 146, 154, 178, 186,
      212, 220, 244, 252, 148, 156, 180, 188, 214, 222, 246, 254, 150, 158, 182, 190 },
    { 129, 137, 161, 169, 193, 201, 225, 233, 131, 139, 163, 171, 195, 203, 227, 235,
      133, 141, 165, 173, 197, 205, 229, 237, 135, 143, 167, 175, 199, 207, 231, 239 },
    { 145, 153, 177, 185, 209, 217, 241, 249, 147, 155, 179, 187, 211, 219, 243, 251,
      149, 157, 181, 189, 213, 221, 245, 253, 151, 159, 183, 191, 215, 223, 247, 255 } };

static int g_corrupt; /* control: perturb the reference */

/* Reference address in NIBBLES (so 4-bit formats fit the same comparison). */
static uint32_t ref_nibaddr(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    uint32_t pw, ph, ppr, blk, inblk;
    int blk32tab[4][8];
    memcpy(blk32tab, T_BLK32, sizeof blk32tab);
    if (g_corrupt) { blk32tab[0][1] = 2; blk32tab[1][0] = 1; }
    switch (psm) {
    case GS_PSMCT32: case GS_PSMCT24: case GS_PSMZ32: case GS_PSMZ24:
    case GS_PSMT8H: case GS_PSMT4HL: case GS_PSMT4HH:
        pw = 64; ph = 32; ppr = bw;
        blk = (psm == GS_PSMZ32 || psm == GS_PSMZ24) ? (uint32_t)T_BLKZ32[(y >> 3) & 3][(x >> 3) & 7]
                                                     : (uint32_t)blk32tab[(y >> 3) & 3][(x >> 3) & 7];
        inblk = ((y >> 1) & 3) * 64 + (uint32_t)T_COL32[y & 1][x & 7] * 4;
        inblk *= 2;
        break;
    case GS_PSMCT16: case GS_PSMCT16S: case GS_PSMZ16: case GS_PSMZ16S: {
        pw = 64; ph = 64; ppr = bw;
        uint32_t by = (y >> 3) & 7, bx = (x >> 4) & 3;
        blk = psm == GS_PSMCT16 ? (uint32_t)T_BLK16[by][bx]
            : psm == GS_PSMCT16S ? (uint32_t)T_BLK16S[by][bx]
            : psm == GS_PSMZ16 ? (uint32_t)T_BLKZ16[by][bx] : (uint32_t)T_BLKZ16S[by][bx];
        inblk = (((y >> 1) & 3) * 64 + (uint32_t)T_COL16[y & 1][x & 15] * 2) * 2;
        break;
    }
    case GS_PSMT8: {
        pw = 128; ph = 64; ppr = bw >> 1;
        blk = (uint32_t)blk32tab[(y >> 4) & 3][(x >> 4) & 7];
        uint32_t col = (y >> 2) & 3;
        inblk = ((col >> 1) * 128 + (uint32_t)T_COL8[(col & 1) * 4 + (y & 3)][x & 15]) * 2;
        break;
    }
    default: { /* PSMT4 */
        pw = 128; ph = 128; ppr = bw >> 1;
        blk = (uint32_t)T_BLK16[(y >> 4) & 7][(x >> 5) & 3];
        uint32_t col = (y >> 2) & 3;
        inblk = (col >> 1) * 256 + (uint32_t)T_COL4[(col & 1) * 4 + (y & 3)][x & 31];
        break;
    }
    }
    uint32_t page = (x / pw) + (y / ph) * ppr;
    return (((bp + page * 32 + blk) & 0x3FFF) * 256) * 2 + inblk;
}

static const int ALL_PSM[] = { GS_PSMCT32, GS_PSMCT24, GS_PSMCT16, GS_PSMCT16S,
                               GS_PSMT8, GS_PSMT4, GS_PSMT8H, GS_PSMT4HL, GS_PSMT4HH,
                               GS_PSMZ32, GS_PSMZ24, GS_PSMZ16, GS_PSMZ16S };

static uint32_t impl_nibaddr(int psm, uint32_t bp, uint32_t bw, uint32_t x, uint32_t y)
{
    int nib;
    uint32_t a = gs_pixel_addr(psm, bp, bw, x, y, &nib);
    return a * 2 + (uint32_t)nib;
}

static void check_format_vs_tables(int psm)
{
    /* buffer 4 pages wide in 64-px units (bw=4: 256 px), 300 lines, two base
     * pointers: page aligned and odd block offset (exercises the bp+blk add) */
    const uint32_t bps[2] = { 64, 37 };
    for (int b = 0; b < 2; b++) {
        uint32_t errs = 0;
        for (uint32_t y = 0; y < 300; y++)
            for (uint32_t x = 0; x < 256; x++) {
                uint32_t r = ref_nibaddr(psm, bps[b], 4, x, y);
                uint32_t i = impl_nibaddr(psm, bps[b], 4, x, y);
                if (r != i) {
                    if (errs++ < 3)
                        fprintf(stderr, "psm 0x%02X bp %u (%u,%u): impl %u ref %u\n",
                                psm, bps[b], x, y, i, r);
                }
            }
        CHECK_EQ(errs, 0);
    }
}

/* Every pixel of one page maps to a distinct unit and the page fills exactly
 * 8 KB (16384 nibbles) worth of its unit size. */
static void check_bijection(int psm)
{
    static uint8_t seen[16384];
    int bpp = gs_psm_bpp(psm);
    uint32_t pw = 64, ph = 32;
    if (bpp == 16) { pw = 64; ph = 64; }
    /* the H formats live in the 32-bit layout */
    if (psm == GS_PSMT8) { pw = 128; ph = 64; }
    if (psm == GS_PSMT4) { pw = 128; ph = 128; }
    memset(seen, 0, sizeof seen);
    uint32_t dup = 0, out = 0;
    uint32_t unit = (bpp == 24 || psm == GS_PSMT8H || psm == GS_PSMT4HL || psm == GS_PSMT4HH)
                        ? 8 : (uint32_t)bpp / 4; /* nibbles per pixel slot */
    for (uint32_t y = 0; y < ph; y++)
        for (uint32_t x = 0; x < pw; x++) {
            uint32_t a = impl_nibaddr(psm, 32, 2, x, y) - 32 * 512;
            if (a >= 16384) { out++; continue; }
            if (seen[a]) dup++;
            seen[a] = 1;
        }
    CHECK_EQ(out, 0);
    CHECK_EQ(dup, 0);
    CHECK_EQ(pw * ph * unit, 16384);
}

int test_swizzle(const char *name)
{
    if (!strcmp(name, "swizzle_tables")) {
        for (size_t i = 0; i < sizeof ALL_PSM / sizeof ALL_PSM[0]; i++)
            check_format_vs_tables(ALL_PSM[i]);
        return 1;
    }
    if (!strcmp(name, "swizzle_bijection")) {
        for (size_t i = 0; i < sizeof ALL_PSM / sizeof ALL_PSM[0]; i++)
            check_bijection(ALL_PSM[i]);
        return 1;
    }
    if (!strcmp(name, "swizzle_control")) {
        /* deliberately wrong reference (two blocks swapped): MUST fail */
        g_corrupt = 1;
        check_format_vs_tables(GS_PSMCT32);
        g_corrupt = 0;
        return 1;
    }
    return 0;
}
