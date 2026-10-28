/* SPDX-License-Identifier: CC0-1.0 */
/* Pixel pipeline on known pixels: every blend preset of the census table
 * (census/platform_gs.tsv, D_00449EF0), COLCLAMP, PABE, FBA, Ad sources,
 * FBMSK, depth test x Z format matrix, alpha test x AFAIL matrix,
 * destination alpha test, dithering, fog, texture functions.  Every expected
 * value below was computed by hand (see the comments), not by the model. */
#include "gs_test_util.h"

#define PRIM_TME (1u << 4)
#define PRIM_FGE (1u << 5)
#define PRIM_ABE (1u << 6)
#define PRIM_FST (1u << 8)

#define CD 0x80785028u /* dst (R,G,B,A) = (40,80,120,0x80) */
#define CS 0x403264C8u /* src (R,G,B,A) = (200,100,50,0x40) */

static uint32_t rgb(uint32_t r, uint32_t g, uint32_t b) { return r | (g << 8) | (b << 16); }

static uint32_t blend_one(uint64_t alpha, uint32_t src, uint32_t dst, int colclamp)
{
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    ad(gs, GS_COLCLAMP, (uint64_t)colclamp);
    ad(gs, GS_ALPHA_1, alpha);
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 5, 6, dst);
    sprite(gs, PRIM_ABE, 5, 6, 6, 7, src, 0);
    uint32_t v = px32(gs, 5, 6);
    gs_destroy(gs);
    return v;
}

static void blend_presets(int control)
{
    /* ALPHA_1 values of the census blend table D_00449EF0[0..11] */
    static const uint64_t T[12] = { 0x800000002Aull, 0x44, 0x48, 0x42, 0x8000000064ull,
                                    0x4A, 0x89, 0x46, 0x88, 0x8000000068ull,
                                    0x8000000062ull, 0x0 };
    /* hand-computed RGB, As=64:
     * 1: R (200-40)*64>>7=80 +40=120  G (100-80)*64>>7=10 +80=90  B (50-120)*64>>7=-35 +120=85
     * 2: R 200*64>>7=100+40=140  G 50+80=130  B 25+120=145
     * 3: R -100+40=-60 ->0  G -50+80=30  B -25+120=95
     * 4: FIX=128 -> (Cs-Cd)+Cd = Cs
     * 5: Cd
     * 6: Cd*64>>7 = 20,40,60
     * 7: -Cd/2+Cd = 20,40,60
     * 8: Cs/2 = 100,50,25
     * 9: Cs+Cd = 240,180,170
     * 10: -Cs+Cd = -160->0, -20->0, 70
     * 11: Cs */
    const uint32_t E[12] = { rgb(200, 100, 50), rgb(120, 90, 85), rgb(140, 130, 145),
                             rgb(0, 30, 95), rgb(200, 100, 50), rgb(40, 80, 120),
                             rgb(20, 40, 60), rgb(20, 40, 60), rgb(100, 50, 25),
                             rgb(240, 180, 170), rgb(0, 0, 70), rgb(200, 100, 50) };
    for (int i = 0; i < 12; i++) {
        uint32_t want = E[control ? (i == 1 ? 2 : i) : i] | 0x40000000u;
        uint32_t got = blend_one(T[i], CS, CD, 1);
        if (got != want)
            fprintf(stderr, "blend preset %d: got 0x%08X want 0x%08X\n", i, got, want);
        CHECK_EQ(got, want);
    }
}

static void blend_misc(void)
{
    /* COLCLAMP=0 wraps: preset 3 R = -60 & 255 = 196 */
    CHECK_EQ(blend_one(0x42, CS, CD, 0), rgb(196, 30, 95) | 0x40000000u);
    /* C = Ad (dst alpha 0x40): same numbers as preset 1 */
    CHECK_EQ(blend_one(r_alpha(0, 1, 1, 1, 0), CS, 0x40785028u, 1), rgb(120, 90, 85) | 0x40000000u);

    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    ad(gs, GS_ALPHA_1, 0x44);
    /* PABE: As=0x40 has MSB clear -> no blend, Cs written */
    ad(gs, GS_PABE, 1);
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 1, 1, CD);
    sprite(gs, PRIM_ABE, 1, 1, 2, 2, CS, 0);
    CHECK_EQ(px32(gs, 1, 1), CS);
    /* PABE with As=0xC0: blends. R (160*192)>>7=240+40=280->255,
     * G (20*192)>>7=30+80=110, B (-70*192)>>7=-105+120=15 */
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 2, 1, CD);
    sprite(gs, PRIM_ABE, 2, 1, 3, 2, 0xC03264C8u, 0);
    CHECK_EQ(px32(gs, 2, 1), rgb(255, 110, 15) | 0xC0000000u);
    ad(gs, GS_PABE, 0);
    /* FBA: alpha written with bit 7 set */
    ad(gs, GS_FBA_1, 1);
    sprite(gs, 0, 3, 1, 4, 2, CS, 0);
    CHECK_EQ(px32(gs, 3, 1), (CS & 0xFFFFFFu) | 0xC0000000u);
    ad(gs, GS_FBA_1, 0);
    /* FBMSK 0x00FF00FF keeps dst R and B: (CD & m) | (CS & ~m) */
    ad(gs, GS_FRAME_1, r_frame(0, 1, GS_PSMCT32, 0x00FF00FFu));
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 4, 1, CD);
    sprite(gs, 0, 4, 1, 5, 2, CS, 0);
    CHECK_EQ(px32(gs, 4, 1), 0x40786428u);
    gs_destroy(gs);

    /* CT24 frame: Ad reads as 0x80 (C=Ad -> (Cs-Cd)+Cd = Cs), top byte kept */
    gs = gs_create();
    std_target(gs, GS_PSMCT24, GS_PSMZ32);
    ad(gs, GS_ALPHA_1, r_alpha(0, 1, 1, 1, 0));
    gs_write_pixel(gs, GS_PSMCT32, 0, 1, 0, 0, 0x11785028u);
    sprite(gs, PRIM_ABE, 0, 0, 1, 1, CS, 0);
    CHECK_EQ(px32(gs, 0, 0), 0x113264C8u);
    gs_destroy(gs);

    /* CT16 frame: 5:5:5:1, Ad = 0x80 when the A bit is set */
    gs = gs_create();
    std_target(gs, GS_PSMCT16, GS_PSMZ32);
    ad(gs, GS_ALPHA_1, 0x44);
    /* dst (40,80,120,1) -> 5-bit 5,10,15 */
    gs_write_pixel(gs, GS_PSMCT16, 0, 1, 0, 0, 5 | (10 << 5) | (15 << 10) | 0x8000);
    sprite(gs, PRIM_ABE, 0, 0, 1, 1, CS, 0);
    /* (120,90,85) -> 15, 11, 10; A bit = As>>7 = 0 */
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT16, 0, 1, 0, 0), 15 | (11 << 5) | (10 << 10));
    gs_destroy(gs);
}

/* depth test x format matrix */
static void depth_matrix(void)
{
    static const int zpsms[3] = { GS_PSMZ32, GS_PSMZ24, GS_PSMZ16 };
    for (int f = 0; f < 3; f++)
        for (int ztst = 0; ztst < 4; ztst++)
            for (int zmsk = 0; zmsk < 2; zmsk++)
                for (int k = 0; k < 3; k++) {
                    uint32_t zs = 999u + (uint32_t)k; /* below / equal / above 1000 */
                    gs_state *gs = gs_create();
                    std_target(gs, GS_PSMCT32, (uint32_t)zpsms[f]);
                    ad(gs, GS_ZBUF_1, r_zbuf(8, (uint32_t)zpsms[f], zmsk));
                    ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 0, 0, 1, ztst));
                    gs_write_pixel(gs, zpsms[f], 8 * 32, 1, 2, 3, 1000);
                    sprite(gs, 0, 2, 3, 3, 4, 0x80FFFFFFu, zs);
                    int pass = ztst == 1 || (ztst == 2 && zs >= 1000) || (ztst == 3 && zs > 1000);
                    CHECK_EQ(px32(gs, 2, 3), pass ? 0x80FFFFFFu : 0u);
                    CHECK_EQ(gs_read_pixel(gs, zpsms[f], 8 * 32, 1, 2, 3),
                             (pass && !zmsk) ? zs : 1000u);
                    gs_destroy(gs);
                }
    /* Z clamps to the format: Z24 -> 0xFFFFFF (top byte untouched),
     * Z16 -> 0xFFFF */
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ24);
    gs_write_pixel(gs, GS_PSMZ32, 8 * 32, 1, 0, 0, 0xAB000000u);
    sprite(gs, 0, 0, 0, 1, 1, 0x80FFFFFFu, 0x01234567u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMZ32, 8 * 32, 1, 0, 0), 0xABFFFFFFu);
    ad(gs, GS_ZBUF_1, r_zbuf(8, GS_PSMZ16, 0));
    sprite(gs, 0, 1, 0, 2, 1, 0x80FFFFFFu, 0x12345u);
    CHECK_EQ(gs_read_pixel(gs, GS_PSMZ16, 8 * 32, 1, 1, 0), 0xFFFFu);
    gs_destroy(gs);
}

static void alpha_matrix(void)
{
    /* ATST x As relative to AREF=0x50 */
    static const int passes[8][3] = {
        { 0, 0, 0 }, { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 0 },
        { 0, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 }, { 1, 0, 1 } };
    for (int atst = 0; atst < 8; atst++)
        for (int k = 0; k < 3; k++) {
            gs_state *gs = gs_create();
            std_target(gs, GS_PSMCT32, GS_PSMZ32);
            ad(gs, GS_TEST_1, r_test(1, atst, 0x50, 0, 0, 0, 1, 1));
            uint32_t as = 0x4Fu + (uint32_t)k;
            sprite(gs, 0, 0, 0, 1, 1, (as << 24) | 0x123456u, 7);
            CHECK_EQ(px32(gs, 0, 0), passes[atst][k] ? ((as << 24) | 0x123456u) : 0u);
            gs_destroy(gs);
        }
    /* AFAIL with a failing test (ATST NEVER); dst = CD, Z = 5, new Z = 9 */
    for (int afail = 0; afail < 4; afail++) {
        gs_state *gs = gs_create();
        std_target(gs, GS_PSMCT32, GS_PSMZ32);
        ad(gs, GS_TEST_1, r_test(1, 0, 0, afail, 0, 0, 1, 1));
        gs_write_pixel(gs, GS_PSMCT32, 0, 1, 0, 0, CD);
        gs_write_pixel(gs, GS_PSMZ32, 8 * 32, 1, 0, 0, 5);
        sprite(gs, 0, 0, 0, 1, 1, CS, 9);
        uint32_t fb = px32(gs, 0, 0), z = gs_read_pixel(gs, GS_PSMZ32, 8 * 32, 1, 0, 0);
        switch (afail) {
        case 0: CHECK_EQ(fb, CD); CHECK_EQ(z, 5); break;               /* KEEP */
        case 1: CHECK_EQ(fb, CS); CHECK_EQ(z, 5); break;               /* FB_ONLY */
        case 2: CHECK_EQ(fb, CD); CHECK_EQ(z, 9); break;               /* ZB_ONLY */
        default: CHECK_EQ(fb, 0x803264C8u); CHECK_EQ(z, 5); break;     /* RGB_ONLY */
        }
        gs_destroy(gs);
    }
    /* destination alpha test: dst A bit 31 set */
    for (int datm = 0; datm < 2; datm++) {
        gs_state *gs = gs_create();
        std_target(gs, GS_PSMCT32, GS_PSMZ32);
        ad(gs, GS_TEST_1, r_test(0, 0, 0, 0, 1, datm, 1, 1));
        gs_write_pixel(gs, GS_PSMCT32, 0, 1, 0, 0, CD);      /* bit 31 = 1 */
        gs_write_pixel(gs, GS_PSMCT32, 0, 1, 1, 0, 0x7F000000u); /* bit 31 = 0 */
        sprite(gs, 0, 0, 0, 2, 1, CS, 0);
        CHECK_EQ(px32(gs, 0, 0), datm ? CS : CD);
        CHECK_EQ(px32(gs, 1, 0), datm ? 0x7F000000u : CS);
        gs_destroy(gs);
    }
}

static void dither_fog(void)
{
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT16, GS_PSMZ32);
    /* DIMX: row 2 col 1 = +3; row 0 col 0 = -4 (0b100) */
    ad(gs, GS_DIMX, (3ull << (2 * 16 + 1 * 4)) | (4ull << 0));
    ad(gs, GS_DTHE, 1);
    sprite(gs, 0, 1, 2, 2, 3, 0x80000065u, 0); /* R=101: +3 = 104 -> 13 */
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT16, 0, 1, 1, 2) & 31, 13);
    sprite(gs, 0, 0, 0, 1, 1, 0x80000068u, 0); /* R=104: -4 = 100 -> 12 */
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT16, 0, 1, 0, 0) & 31, 12);
    ad(gs, GS_DTHE, 0);
    sprite(gs, 0, 1, 2, 2, 3, 0x80000065u, 0); /* 101 -> 12 */
    CHECK_EQ(gs_read_pixel(gs, GS_PSMCT16, 0, 1, 1, 2) & 31, 12);
    gs_destroy(gs);

    /* fog: F=0x80, FOGCOL=(10,20,30), C=(200,100,50):
     * R (128*200+127*10)>>8 = 26870>>8 = 104, G 15340>>8 = 59, B 10210>>8 = 39 */
    gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    ad(gs, GS_FOGCOL, rgb(10, 20, 30));
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_FGE);
    ad(gs, GS_RGBAQ, r_rgbaq(200, 100, 50, 0x80, 1.0f));
    ad(gs, GS_XYZF2, r_xyz(0, 0, 0) | (0x80ull << 56));
    ad(gs, GS_XYZF2, r_xyz(16, 16, 0) | (0x80ull << 56));
    CHECK_EQ(px32(gs, 0, 0), rgb(104, 59, 39) | 0x80000000u);
    /* XYZ2 after XYZF2 keeps the latched fog value (FOG register) */
    ad(gs, GS_XYZ2, r_xyz(32, 0, 0));
    ad(gs, GS_XYZ2, r_xyz(48, 16, 0));
    CHECK_EQ(px32(gs, 2, 0), rgb(104, 59, 39) | 0x80000000u);
    gs_destroy(gs);
}

static void tex_functions(void)
{
    /* texel (100,200,40,0x60), vertex (128,64,255,0x80)
     * MODULATE: 100*128>>7=100, 200*64>>7=100, 40*255>>7=79, A 0x60*0x80>>7=0x60
     * DECAL: texel; HIGHLIGHT: RGB + Af(128) = 228,228,207, A 0x60+0x80=0xE0;
     * HIGHLIGHT2: same RGB, A = At = 0x60; TCC=0: A = Af = 0x80 */
    static const uint32_t want[4][2] = {
        { 0x804F6464u, 0x604F6464u }, { 0x8028C864u, 0x6028C864u },
        { 0x80CFE4E4u, 0xE0CFE4E4u }, { 0x80CFE4E4u, 0x60CFE4E4u } };
    for (int tfx = 0; tfx < 4; tfx++)
        for (int tcc = 0; tcc < 2; tcc++) {
            gs_state *gs = gs_create();
            std_target(gs, GS_PSMCT32, GS_PSMZ32);
            gs_write_pixel(gs, GS_PSMCT32, 400, 1, 0, 0, 0x6028C864u);
            ad(gs, GS_TEX0_1, r_tex0(400, 1, GS_PSMCT32, 0, 0, tcc, tfx, 0, 0, 0, 0, 0));
            ad(gs, GS_TEX1_1, 0);
            ad(gs, GS_CLAMP_1, 1 | (1 << 2));
            ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST);
            ad(gs, GS_RGBAQ, r_rgbaq(128, 64, 255, 0x80, 1.0f));
            ad(gs, GS_UV, 8 | (8 << 16));
            ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
            ad(gs, GS_XYZ2, r_xyz(16, 16, 0));
            CHECK_EQ(px32(gs, 0, 0), want[tfx][tcc]);
            gs_destroy(gs);
        }
}

int test_pixel(const char *name)
{
    if (!strcmp(name, "blend_presets")) { blend_presets(0); return 1; }
    if (!strcmp(name, "blend_control")) { blend_presets(1); return 1; }
    if (!strcmp(name, "blend_misc")) { blend_misc(); return 1; }
    if (!strcmp(name, "depth_matrix")) { depth_matrix(); return 1; }
    if (!strcmp(name, "alpha_matrix")) { alpha_matrix(); return 1; }
    if (!strcmp(name, "dither_fog")) { dither_fog(); return 1; }
    if (!strcmp(name, "tex_functions")) { tex_functions(); return 1; }
    return 0;
}
