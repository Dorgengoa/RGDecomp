/* SPDX-License-Identifier: CC0-1.0 */
/* Primitive golden images.  The expected coverage masks and colours were
 * drawn/computed by hand from the rasterization rules in docs/GS.md (pixel
 * centres at integer coordinates, top-left fill, half-open sprites). */
#include "gs_test_util.h"

#define PRIM_IIP (1u << 3)
#define PRIM_TME (1u << 4)
#define PRIM_ABE (1u << 6)
#define PRIM_FST (1u << 8)
#define PRIM_CTXT2 (1u << 9)

/* compare a mask: 'X' = colour `on`, '.' = untouched (0) */
static void check_mask(gs_state *gs, const char *const *rows, int nrows, uint32_t on)
{
    for (int y = 0; y < nrows; y++)
        for (int x = 0; rows[y][x]; x++) {
            uint32_t want = rows[y][x] == 'X' ? on : 0u;
            uint32_t got = px32(gs, x, y);
            if (got != want)
                fprintf(stderr, "  pixel (%d,%d) = 0x%08X want 0x%08X\n", x, y, got, want);
            CHECK_EQ(got, want);
        }
}

static gs_state *fresh(void)
{
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    return gs;
}

static void vtx(gs_state *gs, int x16, int y16, uint32_t rgba)
{
    ad(gs, GS_RGBAQ, r_rgbaq(rgba & 255, (rgba >> 8) & 255, (rgba >> 16) & 255, rgba >> 24, 1.0f));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)x16, (uint32_t)y16, 0));
}

#define RED 0x800000FFu

static void prim_sprite(void)
{
    gs_state *gs = fresh();
    sprite(gs, 0, 1, 1, 4, 3, RED, 0);
    static const char *m[] = { "........", ".XXX....", ".XXX....", "........" };
    check_mask(gs, m, 4, RED);
    gs_destroy(gs);
    /* half-pixel corners (0.5,0.5)-(2.5,2.5): centres 1 and 2 are inside */
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_SPRITE);
    vtx(gs, 8, 8, RED);
    vtx(gs, 40, 40, RED);
    static const char *m2[] = { "....", ".XX.", ".XX.", "...." };
    check_mask(gs, m2, 4, RED);
    /* reversed corners draw the same rectangle */
    gs_destroy(gs);
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_SPRITE);
    vtx(gs, 4 * 16, 3 * 16, RED);
    vtx(gs, 1 * 16, 1 * 16, RED);
    check_mask(gs, m, 4, RED);
    gs_destroy(gs);
}

static void prim_triangle(void)
{
    gs_state *gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE);
    vtx(gs, 0, 0, RED); vtx(gs, 64, 0, RED); vtx(gs, 0, 64, RED);
    /* x+y<4: top and left edges in, the hypotenuse out */
    static const char *m[] = { "XXXX....", "XXX.....", "XX......", "X.......", "........" };
    check_mask(gs, m, 5, RED);
    CHECK_EQ(gs->stats.pixels_written, 10);
    gs_destroy(gs);

    /* opposite winding: identical coverage */
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE);
    vtx(gs, 0, 0, RED); vtx(gs, 0, 64, RED); vtx(gs, 64, 0, RED);
    check_mask(gs, m, 5, RED);
    gs_destroy(gs);

    /* strip of two triangles tiles a 4x4 square exactly once */
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_TRISTRIP);
    vtx(gs, 0, 0, RED); vtx(gs, 64, 0, RED); vtx(gs, 0, 64, RED); vtx(gs, 64, 64, RED);
    static const char *sq[] = { "XXXX.", "XXXX.", "XXXX.", "XXXX.", "....." };
    check_mask(gs, sq, 5, RED);
    CHECK_EQ(gs->stats.pixels_written, 16);
    CHECK_EQ(gs->stats.prims[GS_PRIM_TRISTRIP], 2);
    gs_destroy(gs);
}

static void prim_shading(void)
{
    /* Gouraud: R = 160 at (16,0), 0 at the other two -> R(x,y) = 10x */
    gs_state *gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_IIP);
    vtx(gs, 0, 0, 0x80000000u); vtx(gs, 256, 0, 0x800000A0u); vtx(gs, 0, 256, 0x80000000u);
    CHECK_EQ(px32(gs, 0, 0), 0x80000000u);
    CHECK_EQ(px32(gs, 5, 3), 0x80000032u);   /* 50 */
    CHECK_EQ(px32(gs, 10, 2), 0x80000064u);  /* 100 */
    CHECK_EQ(px32(gs, 15, 0), 0x80000096u);  /* 150 */
    gs_destroy(gs);
    /* flat: colour of the third (kicking) vertex everywhere */
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE);
    vtx(gs, 0, 0, 0x80000011u); vtx(gs, 256, 0, 0x80000022u); vtx(gs, 0, 256, 0x80000033u);
    CHECK_EQ(px32(gs, 0, 0), 0x80000033u);
    CHECK_EQ(px32(gs, 5, 3), 0x80000033u);
    gs_destroy(gs);
}

static void prim_line_point(void)
{
    gs_state *gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_LINE);
    vtx(gs, 0, 0, RED); vtx(gs, 80, 32, RED);
    /* y = 0.4x rounded: (0,0)(1,0)(2,1)(3,1)(4,2); the end point is open */
    static const char *m[] = { "XX......", "..XX....", "....X...", "........" };
    check_mask(gs, m, 4, RED);
    gs_destroy(gs);
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_LINE);
    vtx(gs, 0, 0, RED); vtx(gs, 16, 64, RED);
    static const char *m2[] = { "X...", "X...", ".X..", ".X..", "...." };
    check_mask(gs, m2, 5, RED);
    gs_destroy(gs);
    gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_POINT);
    vtx(gs, 48, 32, RED);
    static const char *m3[] = { "....", "....", "...X", "...." };
    check_mask(gs, m3, 4, RED);
    gs_destroy(gs);
}

static void prim_queue(void)
{
    gs_state *gs = fresh();
    ad(gs, GS_PRIM, GS_PRIM_TRIFAN);
    for (int i = 0; i < 5; i++) vtx(gs, i * 16, (i & 1) * 160, RED);
    CHECK_EQ(gs->stats.prims[GS_PRIM_TRIFAN], 3);
    ad(gs, GS_PRIM, GS_PRIM_LINESTRIP);
    for (int i = 0; i < 4; i++) vtx(gs, i * 32, 0, RED);
    CHECK_EQ(gs->stats.prims[GS_PRIM_LINESTRIP], 3);
    /* XYZ3 queues without drawing; the next XYZ2 completes the triangle */
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE);
    ad(gs, GS_XYZ3, r_xyz(0, 0, 0));
    ad(gs, GS_XYZ3, r_xyz(16, 0, 0));
    ad(gs, GS_XYZ3, r_xyz(0, 16, 0));
    CHECK_EQ(gs->stats.prims[GS_PRIM_TRIANGLE], 0);
    ad(gs, GS_XYZ3, r_xyz(0, 0, 0));
    ad(gs, GS_XYZ3, r_xyz(16, 0, 0));
    ad(gs, GS_XYZ2, r_xyz(0, 16, 0));
    CHECK_EQ(gs->stats.prims[GS_PRIM_TRIANGLE], 1);
    /* a PRIM write resets the queue */
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE);
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    CHECK_EQ(gs->stats.prims[GS_PRIM_TRIANGLE], 1);
    gs_destroy(gs);
}

/* 4x4 CT32 texture at block 400: texel(x,y) = 0x80000000 | (4y+x+1)*16 */
static uint32_t TX(int x, int y) { return 0x80000000u | (uint32_t)((4 * y + x + 1) * 16); }

static void tex_setup(gs_state *gs, uint64_t clamp)
{
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++) gs_write_pixel(gs, GS_PSMCT32, 400, 1, (uint32_t)x, (uint32_t)y, TX(x, y));
    ad(gs, GS_TEX0_1, r_tex0(400, 1, GS_PSMCT32, 2, 2, 1, 1, 0, 0, 0, 0, 0));
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, clamp);
}

static void uv_sprite(gs_state *gs, int w, int h, int u1, int v1)
{
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST);
    ad(gs, GS_RGBAQ, r_rgbaq(128, 128, 128, 128, 1.0f));
    ad(gs, GS_UV, 0);
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    ad(gs, GS_UV, (uint64_t)(u1 * 16) | ((uint64_t)(v1 * 16) << 16));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)w << 4, (uint32_t)h << 4, 0));
}

static void prim_texture_wrap(void)
{
    static const struct { uint64_t clamp; int map[8]; } C[4] = {
        { 0, { 0, 1, 2, 3, 0, 1, 2, 3 } },                          /* REPEAT */
        { 1 | (1 << 2), { 0, 1, 2, 3, 3, 3, 3, 3 } },               /* CLAMP */
        { 2 | (1ull << 4) | (2ull << 14) | (1 << 2), { 1, 1, 2, 2, 2, 2, 2, 2 } }, /* REGION_CLAMP 1..2 */
        { 3 | (1ull << 4) | (2ull << 14) | (1 << 2), { 2, 3, 2, 3, 2, 3, 2, 3 } }, /* REGION_REPEAT (u&1)|2 */
    };
    for (int k = 0; k < 4; k++) {
        gs_state *gs = fresh();
        tex_setup(gs, C[k].clamp);
        uv_sprite(gs, 8, 4, 8, 4);
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 8; x++) CHECK_EQ(px32(gs, x, y), TX(C[k].map[x], y));
        gs_destroy(gs);
    }
}

static void prim_bilinear(void)
{
    gs_state *gs = fresh();
    gs_write_pixel(gs, GS_PSMCT32, 400, 1, 0, 0, 0x00000000u);
    gs_write_pixel(gs, GS_PSMCT32, 400, 1, 1, 0, 0xFFFFFFFFu);
    ad(gs, GS_TEX0_1, r_tex0(400, 1, GS_PSMCT32, 1, 0, 1, 1, 0, 0, 0, 0, 0));
    ad(gs, GS_TEX1_1, 0x60); /* MMAG=MMIN=LINEAR */
    ad(gs, GS_CLAMP_1, 1 | (1 << 2));
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST);
    ad(gs, GS_RGBAQ, r_rgbaq(128, 128, 128, 128, 1.0f));
    /* pixel 0 samples u=1.0 texel: halfway between texel centres 0.5 and
     * 1.5 -> (0*8 + 255*8)/16 = 127 per channel; pixel 1 samples u=1.5 =
     * exactly texel 1 -> 255 */
    ad(gs, GS_UV, 16 | (8 << 16));
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    ad(gs, GS_UV, 48 | (8 << 16));
    ad(gs, GS_XYZ2, r_xyz(64, 16, 0));
    CHECK_EQ(px32(gs, 0, 0), 0x7F7F7F7Fu);
    CHECK_EQ(px32(gs, 1, 0), 0xFFFFFFFFu);
    gs_destroy(gs);
}

static void stq_vtx(gs_state *gs, int x16, int y16, float s, float t, float q)
{
    ad(gs, GS_ST, r_st(s, t));
    ad(gs, GS_RGBAQ, r_rgbaq(128, 128, 128, 128, q));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)x16, (uint32_t)y16, 0));
}

static void prim_perspective(void)
{
    gs_state *gs = fresh();
    for (int i = 0; i < 8; i++)
        gs_write_pixel(gs, GS_PSMCT32, 400, 1, (uint32_t)i, 0, 0x80000000u | (uint32_t)(i * 30));
    ad(gs, GS_TEX0_1, r_tex0(400, 1, GS_PSMCT32, 3, 0, 1, 1, 0, 0, 0, 0, 0));
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, 1 | (1 << 2));
    ad(gs, GS_PRIM, GS_PRIM_TRIANGLE | PRIM_TME);
    stq_vtx(gs, 0, 0, 0.0f, 0.5f, 1.0f);
    stq_vtx(gs, 128, 0, 2.0f, 1.0f, 2.0f);
    stq_vtx(gs, 0, 128, 0.0f, 0.5f, 1.0f);
    /* (4,0): S=1, Q=1.5 -> u = 8*0.667 = 5.33 -> texel 5 (affine would be 4)
     * (2,0): S=0.5, Q=1.25 -> u = 3.2 -> texel 3
     * (2,2): S=0.5, Q=1.25 -> texel 3;  (0,0) -> texel 0 */
    CHECK_EQ(px32(gs, 4, 0), 0x80000000u | 150);
    CHECK_EQ(px32(gs, 2, 0), 0x80000000u | 90);
    CHECK_EQ(px32(gs, 2, 2), 0x80000000u | 90);
    CHECK_EQ(px32(gs, 0, 0), 0x80000000u);
    gs_destroy(gs);
}

static void prim_mipmap(void)
{
    for (int k = 0; k < 2; k++) {
        gs_state *gs = fresh();
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++) gs_write_pixel(gs, GS_PSMCT32, 400, 1, (uint32_t)x, (uint32_t)y, RED);
        for (int y = 0; y < 2; y++)
            for (int x = 0; x < 2; x++) gs_write_pixel(gs, GS_PSMCT32, 420, 1, (uint32_t)x, (uint32_t)y, 0x8000FF00u);
        ad(gs, GS_TEX0_1, r_tex0(400, 1, GS_PSMCT32, 2, 2, 1, 1, 0, 0, 0, 0, 0));
        ad(gs, GS_MIPTBP1_1, 420 | (1ull << 14));
        /* LCM=1 (LOD=K), MXL=1, MMIN=NEAREST_MIPMAP_NEAREST, K = k (7.4) */
        ad(gs, GS_TEX1_1, 1 | (1 << 2) | (2 << 6) | ((uint64_t)(k * 16) << 32));
        ad(gs, GS_CLAMP_1, 1 | (1 << 2));
        uv_sprite(gs, 2, 2, 4, 4);
        CHECK_EQ(px32(gs, 1, 1), k ? 0x8000FF00u : RED);
        gs_destroy(gs);
    }
}

static void prim_env(void)
{
    /* scissor */
    gs_state *gs = fresh();
    ad(gs, GS_SCISSOR_1, r_scissor(2, 4, 1, 2));
    sprite(gs, 0, 0, 0, 8, 4, RED, 0);
    static const char *m[] = { "........", "..XXX...", "..XXX...", "........" };
    check_mask(gs, m, 4, RED);
    gs_destroy(gs);
    /* XYOFFSET: (101,100)-(103,102) with offset (100,100) -> pixels 1..2 x 0..1 */
    gs = fresh();
    ad(gs, GS_XYOFFSET_1, (100ull << 4) | ((100ull << 4) << 32));
    sprite(gs, 0, 101, 100, 103, 102, RED, 0);
    static const char *m2[] = { ".XX.", ".XX.", "...." };
    check_mask(gs, m2, 3, RED);
    gs_destroy(gs);
    /* PRMODECONT=0: attributes from PRMODE (ABE there, not in PRIM) */
    gs = fresh();
    ad(gs, GS_ALPHA_1, 0x44);
    ad(gs, GS_PRMODECONT, 0);
    ad(gs, GS_PRMODE, PRIM_ABE);
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 0, 0, 0x80785028u);
    sprite(gs, 0, 0, 0, 1, 1, 0x403264C8u, 0);
    CHECK_EQ(px32(gs, 0, 0), 0x40555A78u); /* preset 1: (120,90,85) */
    gs_destroy(gs);
    /* context 2 via PRIM.CTXT: FRAME_2 at page 2 */
    gs = fresh();
    ad(gs, GS_FRAME_2, r_frame(2, 1, GS_PSMCT32, 0));
    ad(gs, GS_ZBUF_2, r_zbuf(8, GS_PSMZ32, 1));
    ad(gs, GS_SCISSOR_2, r_scissor(0, 63, 0, 31));
    ad(gs, GS_XYOFFSET_2, 0);
    ad(gs, GS_TEST_2, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    sprite(gs, PRIM_CTXT2, 0, 0, 1, 1, RED, 0);
    CHECK_EQ(px32(gs, 0, 0), 0u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT32, 64, 1, 0, 0), RED);
    gs_destroy(gs);
    /* SCANMSK=2: odd lines are not drawn */
    gs = fresh();
    ad(gs, GS_SCANMSK, 2);
    sprite(gs, 0, 0, 0, 2, 4, RED, 0);
    static const char *m3[] = { "XX..", "....", "XX..", "....", "...." };
    check_mask(gs, m3, 5, RED);
    gs_destroy(gs);
}


/* Sprite UV stepping: the fixed-point DDA of docs/GS.md rule 3.  Texture is
 * a 512x512 CT32 at block 8192 with texel(x,y) = 0x80000000 | y<<12 | x, so
 * every pixel tells which texel it sampled.  Point sampling, CLAMP. */
static uint32_t UVT(int x, int y) { return 0x80000000u | ((uint32_t)y << 12) | (uint32_t)x; }

static gs_state *uv_fresh(int tw, int th)
{
    gs_state *gs = gs_create();
    ad(gs, GS_FRAME_1, r_frame(0, 1, GS_PSMCT32, 0));
    ad(gs, GS_ZBUF_1, r_zbuf(448, GS_PSMZ32, 1));
    ad(gs, GS_SCISSOR_1, r_scissor(0, 63, 0, 447));
    ad(gs, GS_XYOFFSET_1, 0);
    ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    ad(gs, GS_PRMODECONT, 1);
    for (int y = 0; y < (1 << th); y++)
        for (int x = 0; x < (1 << tw); x++)
            gs_write_pixel(gs, GS_PSMCT32, 8192, 8, (uint32_t)x, (uint32_t)y, UVT(x, y));
    ad(gs, GS_TEX0_1, r_tex0(8192, 8, GS_PSMCT32, (uint32_t)tw, (uint32_t)th, 1, 1, 0, 0, 0, 0, 0));
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, 1 | (1 << 2));
    return gs;
}

/* sprite (x0,y0)-(x1,y1) in 12.4 with UV in 1/16 texels */
static void uv_sprite16(gs_state *gs, int x0, int y0, int x1, int y1, int u0, int v0, int u1, int v1)
{
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST);
    ad(gs, GS_RGBAQ, r_rgbaq(128, 128, 128, 128, 1.0f));
    ad(gs, GS_UV, (uint64_t)u0 | ((uint64_t)v0 << 16));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)x0, (uint32_t)y0, 0));
    ad(gs, GS_UV, (uint64_t)u1 | ((uint64_t)v1 << 16));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)x1, (uint32_t)y1, 0));
}

static void prim_sprite_uv(void)
{
    /* 1. 448 rows, V 0 -> 448*16 with no +8 offset: the step is exactly one
     *    texel per row, so row y samples texel row y.  (Evaluated as
     *    v0 + (v1-v0) * ((16y - y0) / dy) in double, rows 61, 115, 122, 230,
     *    237, 244 and 251 land one ulp below 16y and read texel y-1.) */
    gs_state *gs = uv_fresh(1, 9);
    uv_sprite16(gs, 0, 0, 16, 448 * 16, 0, 0, 16, 448 * 16);
    for (int y = 0; y < 448; y++) CHECK_EQ(px32(gs, 0, y), UVT(0, y));
    gs_destroy(gs);
    /* 2. 3:1 minification over a non-power-of-two width: U 0 -> 300 texels
     *    on 100 px; step = 48 * 2^16 exactly, pixel x samples texel 3x */
    gs = uv_fresh(9, 0);
    ad(gs, GS_SCISSOR_1, r_scissor(0, 127, 0, 0));
    ad(gs, GS_FRAME_1, r_frame(0, 2, GS_PSMCT32, 0));
    uv_sprite16(gs, 0, 0, 100 * 16, 16, 0, 0, 300 * 16, 16);
    for (int x = 0; x < 100; x++)
        CHECK_EQ(gs_read_pixel(gs, GS_PSMCT32, 0, 2, (uint32_t)x, 0), UVT(3 * x, 0));
    gs_destroy(gs);
    /* 3. a step that is not a whole 16.16 value is truncated: 2 texels on
     *    6 px, step = trunc(32 * 2^20 / 96) = 349525 (exact 349525.33).  At
     *    px 3 the exact U is 16 (texel 1), the DDA gives (3*349525) >> 16 =
     *    15 -> texel 0; px 4: 1398100 >> 16 = 21 -> texel 1. */
    gs = uv_fresh(1, 0);
    uv_sprite16(gs, 0, 0, 6 * 16, 16, 0, 0, 32, 16);
    static const int m3[6] = { 0, 0, 0, 0, 1, 1 };
    for (int x = 0; x < 6; x++) CHECK_EQ(px32(gs, x, 0), UVT(m3[x], 0));
    gs_destroy(gs);
    /* 4. mirrored: U 64 -> 0 texels over 64 px (step -2^20).  px 0 samples
     *    U = 1024 = texel 64, clamped to 63; px x >= 1 samples texel 64 - x */
    gs = uv_fresh(6, 0);
    uv_sprite16(gs, 0, 0, 64 * 16, 16, 64 * 16, 0, 0, 16);
    CHECK_EQ(px32(gs, 0, 0), UVT(63, 0));
    for (int x = 1; x < 64; x++) CHECK_EQ(px32(gs, x, 0), UVT(64 - x, 0));
    gs_destroy(gs);
    /* 5. half-pixel corners: X 0.5 -> 4.5, U 0 -> 4 texels covers px 1..4;
     *    px 1 is half a pixel from X0: U = 8 (texel 0.5) -> texels 0,1,2,3.
     *    V the same with corners given in reverse order (sorted first). */
    gs = uv_fresh(2, 2);
    uv_sprite16(gs, 72, 72, 8, 8, 64, 64, 0, 0);
    for (int y = 1; y <= 4; y++)
        for (int x = 1; x <= 4; x++) CHECK_EQ(px32(gs, x, y), UVT(x - 1, y - 1));
    CHECK_EQ(px32(gs, 0, 1), 0u);
    CHECK_EQ(px32(gs, 5, 1), 0u);
    gs_destroy(gs);
    /* 6. the helpers themselves (the GPU renderer calls them) */
    CHECK_EQ(gs_sprite_uv_step(0, 32, 0, 96), 349525);
    CHECK_EQ(gs_sprite_uv_step(1024, 0, 0, 1024), (uint64_t)(int64_t)-(1 << 20));
    CHECK_EQ(gs_sprite_uv_step(0, 16383, 0, 1), 0x7FFFFFFF);   /* saturates */
    CHECK_EQ(gs_sprite_uv_at(0, 0, 349525, 3), 15);
    CHECK_EQ(gs_sprite_uv_at(1024, 0, -(1 << 20), 1), 1008);
    CHECK_EQ(gs_sprite_uv_at(0, 8, 1 << 20, 1), 8);
}

/* Full 640x448 frame (FBW=10, many pages) with a REPEAT-tiled T8 texture
 * through bilinear at texel centres (UV +8): every pixel must equal its
 * texel exactly.  Also a coarse speed smoke for the reference path. */
static void prim_fullscreen(void)
{
    gs_state *gs = gs_create();
    ad(gs, GS_FRAME_1, r_frame(0, 10, GS_PSMCT32, 0));
    ad(gs, GS_ZBUF_1, r_zbuf(140, GS_PSMZ24, 0));
    ad(gs, GS_SCISSOR_1, r_scissor(0, 639, 0, 447));
    ad(gs, GS_XYOFFSET_1, 0);
    ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    for (uint32_t i = 0; i < 256; i++)
        gs_write_pixel(gs, GS_PSMCT32, 9000, 1, i & 15, i >> 4, 0x80000000u | (i * 0x010203u));
    for (uint32_t y = 0; y < 64; y++)
        for (uint32_t x = 0; x < 64; x++)
            gs_write_pixel(gs, GS_PSMT8, 9216, 2, x, y, (x * 7 + y * 13) & 255);
    ad(gs, GS_TEX0_1, r_tex0(9216, 2, GS_PSMT8, 6, 6, 1, 1, 9000, GS_PSMCT32, 0, 0, 1));
    ad(gs, GS_TEX1_1, 0x60);
    ad(gs, GS_CLAMP_1, 0);
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST);
    ad(gs, GS_RGBAQ, r_rgbaq(128, 128, 128, 128, 1.0f));
    ad(gs, GS_UV, 8 | (8 << 16));
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    ad(gs, GS_UV, (640 * 16 + 8) | ((uint64_t)(448 * 16 + 8) << 16));
    ad(gs, GS_XYZ2, r_xyz(640 * 16, 448 * 16, 0));
    uint32_t bad = 0;
    for (uint32_t y = 0; y < 448; y += 7)
        for (uint32_t x = 0; x < 640; x += 3) {
            uint32_t i = ((x & 63) * 7 + (y & 63) * 13) & 255;
            uint32_t p = 0;
            /* CLUT CSM1 position of entry i */
            uint32_t pp = (i & 0xE7u) | ((i & 8u) << 1) | ((i & 0x10u) >> 1);
            p = gs_read_pixel(gs, GS_PSMCT32, 9000, 1, pp & 15, pp >> 4);
            if (gs_read_pixel(gs, GS_PSMCT32, 0, 10, x, y) != p) bad++;
        }
    CHECK_EQ(bad, 0);
    CHECK_EQ(gs->stats.pixels_written, 640 * 448);
    gs_destroy(gs);
}

/* A primitive's texture reads see memory as it was when the primitive
 * started, not its own writes (gs_raster.c tex_snapshot; docs/GPU.md
 * "Checkpoint 4").  1: a sprite adding the frame shifted one pixel right to
 * itself in place (DECAL here: a copy) gives every pixel its left
 * neighbour's old value, not a smear of the first one.  2: the same
 * sprite's Z32 writes land on the 1x1 texture it samples part-way through
 * the sprite; every pixel still gets the old texel.  3: with the snapshot
 * off (test control) the first case smears, as the reference did before. */
static void prim_self_read(void)
{
    for (int pass = 0; pass < 2; pass++) {
        gs_state *gs = gs_create();
        ad(gs, GS_FRAME_1, r_frame(0, 1, GS_PSMCT32, 0));
        ad(gs, GS_ZBUF_1, r_zbuf(448, GS_PSMZ32, 1));
        ad(gs, GS_SCISSOR_1, r_scissor(0, 63, 0, 31));
        ad(gs, GS_XYOFFSET_1, 0);
        ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
        ad(gs, GS_PRMODECONT, 1);
        for (int x = 0; x < 64; x++) gs_write_pixel(gs, GS_PSMCT32, 0, 1, (uint32_t)x, 0, UVT(x, 0));
        ad(gs, GS_TEX0_1, r_tex0(0, 1, GS_PSMCT32, 6, 5, 1, 1, 0, 0, 0, 0, 0));
        ad(gs, GS_TEX1_1, 0);
        ad(gs, GS_CLAMP_1, 1 | (1 << 2));
        gs_tex_snapshot_off = pass;
        uint64_t n0 = gs_tex_snapshots;
        uv_sprite16(gs, 16, 0, 64 * 16, 16, 8, 8, 63 * 16 + 8, 8);   /* px x reads texel x-1 */
        gs_tex_snapshot_off = 0;
        for (int x = 1; x < 64; x++) CHECK_EQ(px32(gs, x, 0), UVT(pass ? 0 : x - 1, 0));
        CHECK_EQ(gs_tex_snapshots - n0, pass ? 0u : 1u);
        gs_destroy(gs);
    }
    /* 2: FRAME elsewhere, Z32 written at block 0 (FBW 1: pixel (x, y)'s Z
     * word is the CT32 word of another pixel of the same page), TEX0 a 1x1
     * CT32 texture at block 0 */
    gs_state *gs = gs_create();
    ad(gs, GS_FRAME_1, r_frame(64, 1, GS_PSMCT32, 0));
    ad(gs, GS_ZBUF_1, r_zbuf(0, GS_PSMZ32, 0));
    ad(gs, GS_SCISSOR_1, r_scissor(0, 63, 0, 31));
    ad(gs, GS_XYOFFSET_1, 0);
    ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, 1));
    ad(gs, GS_PRMODECONT, 1);
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 0, 0, 0x8055AA33u);
    ad(gs, GS_TEX0_1, r_tex0(0, 1, GS_PSMCT32, 0, 0, 1, 1, 0, 0, 0, 0, 0));
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, 0);
    uv_sprite16(gs, 0, 0, 64 * 16, 32 * 16, 0, 0, 16, 16);
    uint32_t zword = 0;
    for (int y = 0; y < 32; y++)
        for (int x = 0; x < 64; x++) CHECK_EQ(gs_read_pixel(gs, GS_PSMCT32, 64 * 32, 1, (uint32_t)x, (uint32_t)y), 0x8055AA33u);
    zword = gs_read_pixel(gs, GS_PSMCT32, 0, 1, 0, 0);
    CHECK_EQ(zword, 0u);   /* the texel itself was overwritten by a Z write (z = 0) */
    gs_destroy(gs);
}

int test_prim(const char *name)
{
    if (!strcmp(name, "prim_self_read")) { prim_self_read(); return 1; }
    if (!strcmp(name, "prim_sprite")) { prim_sprite(); return 1; }
    if (!strcmp(name, "prim_triangle")) { prim_triangle(); return 1; }
    if (!strcmp(name, "prim_shading")) { prim_shading(); return 1; }
    if (!strcmp(name, "prim_line_point")) { prim_line_point(); return 1; }
    if (!strcmp(name, "prim_queue")) { prim_queue(); return 1; }
    if (!strcmp(name, "prim_texture_wrap")) { prim_texture_wrap(); return 1; }
    if (!strcmp(name, "prim_bilinear")) { prim_bilinear(); return 1; }
    if (!strcmp(name, "prim_perspective")) { prim_perspective(); return 1; }
    if (!strcmp(name, "prim_mipmap")) { prim_mipmap(); return 1; }
    if (!strcmp(name, "prim_env")) { prim_env(); return 1; }
    if (!strcmp(name, "prim_fullscreen")) { prim_fullscreen(); return 1; }
    if (!strcmp(name, "prim_sprite_uv")) { prim_sprite_uv(); return 1; }
    return 0;
}
