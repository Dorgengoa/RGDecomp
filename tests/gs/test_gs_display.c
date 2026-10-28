/* SPDX-License-Identifier: CC0-1.0 */
/* Display read-out: one circuit, merge (ALP / pixel alpha / background),
 * FIELD and FRAME interlace, the game's 0x7F23 anti-flicker setup, CT16. */
#include "gs_test_util.h"

static uint64_t dispfb(uint32_t fbp, uint32_t fbw, uint32_t psm, uint32_t dbx, uint32_t dby)
{ return fbp | ((uint64_t)fbw << 9) | ((uint64_t)psm << 15) | ((uint64_t)dbx << 32) | ((uint64_t)dby << 43); }
static uint64_t display(uint32_t dx, uint32_t dy, uint32_t magh, uint32_t magv, uint32_t dw, uint32_t dh)
{ return dx | ((uint64_t)dy << 12) | ((uint64_t)magh << 23) | ((uint64_t)magv << 27) | ((uint64_t)dw << 32) | ((uint64_t)dh << 44); }

static uint32_t out[64 * 64];

static void fill(gs_state *gs, uint32_t fbp_blocks, uint32_t (*f)(uint32_t, uint32_t))
{
    for (uint32_t y = 0; y < 32; y++)
        for (uint32_t x = 0; x < 64; x++)
            gs_write_pixel(gs, GS_PSMCT32, fbp_blocks, 1, x, y, f(x, y));
}
static uint32_t pat(uint32_t x, uint32_t y) { return 0x80000000u | (y << 8) | x; }
static uint32_t c200(uint32_t x, uint32_t y) { (void)x; (void)y; return 0x40C8C8C8u; }
static uint32_t c100(uint32_t x, uint32_t y) { (void)x; (void)y; return 0x80646464u; }

static void one_circuit(void)
{
    gs_state *gs = gs_create();
    uint32_t w, h;
    CHECK_EQ(gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h), -1); /* nothing enabled */
    fill(gs, 0, pat);
    gs_write_priv(gs, GS_P_PMODE, 1 | (1 << 5) | (0xFF << 8));
    gs_write_priv(gs, GS_P_DISPFB1, dispfb(0, 1, GS_PSMCT32, 0, 0));
    gs_write_priv(gs, GS_P_DISPLAY1, display(636, 50, 3, 0, 64 * 4 - 1, 31));
    CHECK_EQ(gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h), 0);
    CHECK_EQ(w, 64);
    CHECK_EQ(h, 32);
    uint32_t bad = 0;
    for (uint32_t y = 0; y < 32; y++)
        for (uint32_t x = 0; x < 64; x++)
            if (out[y * 64 + x] != (0xFF000000u | (y << 8) | x)) bad++;
    CHECK_EQ(bad, 0);
    /* too small a buffer reports the size */
    CHECK_EQ(gs_read_display(gs, GS_READ_FRAME, out, 10, &w, &h), -1);
    CHECK_EQ(w * h, 64 * 32);
    /* DBX/DBY scroll the read window */
    gs_write_priv(gs, GS_P_DISPFB1, dispfb(0, 1, GS_PSMCT32, 3, 2));
    gs_write_priv(gs, GS_P_DISPLAY1, display(0, 0, 3, 0, 8 * 4 - 1, 3));
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(out[0], 0xFF000000u | (2 << 8) | 3);
    CHECK_EQ(out[1 * 8 + 1], 0xFF000000u | (3 << 8) | 4);
    gs_destroy(gs);
}

static void merge(void)
{
    gs_state *gs = gs_create();
    uint32_t w, h;
    fill(gs, 0, c200);   /* circuit 1, alpha 0x40 */
    fill(gs, 64, c100);  /* circuit 2 at FBP page 2 */
    gs_write_priv(gs, GS_P_DISPFB1, dispfb(0, 1, GS_PSMCT32, 0, 0));
    gs_write_priv(gs, GS_P_DISPLAY1, display(0, 0, 3, 0, 255, 31));
    gs_write_priv(gs, GS_P_DISPFB2, dispfb(2, 1, GS_PSMCT32, 0, 0));
    gs_write_priv(gs, GS_P_DISPLAY2, display(0, 0, 3, 0, 255, 31));
    /* MMOD=1 ALP=0x80: (200*128 + 100*127 + 127)/255 = 38427/255 = 150 */
    gs_write_priv(gs, GS_P_PMODE, 3 | (1 << 5) | (0x80 << 8));
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(out[5], 0xFF969696u);
    /* MMOD=0: circuit-1 pixel alpha 0x40 doubled = 0x80 -> same */
    gs_write_priv(gs, GS_P_PMODE, 3);
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(out[5], 0xFF969696u);
    /* SLBG=1, ALP=0: background colour */
    gs_write_priv(gs, GS_P_BGCOLOR, 10 | (20 << 8) | (30 << 16));
    gs_write_priv(gs, GS_P_PMODE, 3 | (1 << 5) | (1 << 7));
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(out[5], 0xFF1E140Au);
    /* circuit 2 alone */
    gs_write_priv(gs, GS_P_PMODE, 2);
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(out[5], 0xFF646464u);
    gs_destroy(gs);
}

static void interlace(void)
{
    gs_state *gs = gs_create();
    uint32_t w, h;
    fill(gs, 0, pat);
    gs_write_priv(gs, GS_P_PMODE, 1 | (1 << 5) | (0xFF << 8));
    gs_write_priv(gs, GS_P_DISPFB1, dispfb(0, 1, GS_PSMCT32, 0, 0));
    /* FIELD mode: DH = height-1, a field is every other line */
    gs_write_priv(gs, GS_P_SMODE2, 1);
    gs_write_priv(gs, GS_P_DISPLAY1, display(0, 0, 3, 0, 255, 31));
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(h, 32);
    gs_read_display(gs, 1, out, 64 * 64, &w, &h);
    CHECK_EQ(h, 16);
    CHECK_EQ(out[0] & 0xFFFF, 1 << 8);           /* line 1 */
    CHECK_EQ(out[3 * 64] & 0xFFFF, 7 << 8);      /* line 7 */
    gs_read_display(gs, 0, out, 64 * 64, &w, &h);
    CHECK_EQ(out[3 * 64] & 0xFFFF, 6 << 8);
    /* FRAME mode: libgraph writes DH = 2*height-1; each field shows all lines */
    gs_write_priv(gs, GS_P_SMODE2, 3);
    gs_write_priv(gs, GS_P_DISPLAY1, display(0, 0, 3, 0, 255, 63));
    gs_read_display(gs, 1, out, 64 * 64, &w, &h);
    CHECK_EQ(h, 32);
    CHECK_EQ(out[3 * 64] & 0xFFFF, 3 << 8);
    gs_destroy(gs);
}

static void game_antiflicker(void)
{
    /* GsDbufPutEnv_144150: PMODE 0x7F23, circuit 1 = same buffer at DBY=1
     * with DH-1, circuit 2 = libgraph's DBY=0.  Output line y blends line
     * y+1 (ALP 0x7F) over line y: (L(y+1)*127 + L(y)*128 + 127) / 255. */
    gs_state *gs = gs_create();
    uint32_t w, h;
    for (uint32_t y = 0; y < 32; y++)
        for (uint32_t x = 0; x < 64; x++)
            gs_write_pixel(gs, GS_PSMCT32, 0, 1, x, y, 0x80000000u | (y * 8 * 0x010101u));
    gs_write_priv(gs, GS_P_SMODE2, 3);
    gs_write_priv(gs, GS_P_PMODE, 0x7F23);
    gs_write_priv(gs, GS_P_DISPFB2, dispfb(0, 1, GS_PSMCT32, 0, 0));
    gs_write_priv(gs, GS_P_DISPLAY2, display(636, 50, 3, 0, 255, 63));
    gs_write_priv(gs, GS_P_DISPFB1, dispfb(0, 1, GS_PSMCT32, 0, 1));
    gs_write_priv(gs, GS_P_DISPLAY1, display(636, 50, 3, 0, 255, 62));
    CHECK_EQ(gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h), 0);
    CHECK_EQ(h, 32);
    /* y=2: L2=16, L3=24 -> (24*127 + 16*128 + 127)/255 = 5223/255 = 20 */
    CHECK_EQ(out[2 * 64] & 0xFF, 20);
    /* last line has no circuit-1 pixel: L31 = 248 */
    CHECK_EQ(out[31 * 64] & 0xFF, 248);
    gs_destroy(gs);
}

static void ct16_display(void)
{
    gs_state *gs = gs_create();
    uint32_t w, h;
    gs_write_pixel(gs, GS_PSMCT16, 0, 1, 0, 0, 31 | (16 << 5) | (1 << 10));
    gs_write_priv(gs, GS_P_PMODE, 1 | (1 << 5) | (0xFF << 8));
    gs_write_priv(gs, GS_P_DISPFB1, dispfb(0, 1, GS_PSMCT16, 0, 0));
    gs_write_priv(gs, GS_P_DISPLAY1, display(0, 0, 3, 0, 255, 31));
    gs_read_display(gs, GS_READ_FRAME, out, 64 * 64, &w, &h);
    CHECK_EQ(out[0], 0xFF0880F8u);
    gs_destroy(gs);
}

int test_display(const char *name)
{
    if (!strcmp(name, "display_one")) { one_circuit(); return 1; }
    if (!strcmp(name, "display_merge")) { merge(); return 1; }
    if (!strcmp(name, "display_interlace")) { interlace(); return 1; }
    if (!strcmp(name, "display_antiflicker")) { game_antiflicker(); return 1; }
    if (!strcmp(name, "display_ct16")) { ct16_display(); return 1; }
    return 0;
}
