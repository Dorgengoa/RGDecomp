/* SPDX-License-Identifier: CC0-1.0 */
/* CLUT: CSM1 (T8 entry arrangement, T4 8x2), CSM2 (TEXCLUT row), CSA, CT32
 * low/high half storage, CLD load conditions, TEX2. */
#include "gs_test_util.h"

#define PRIM_TME (1u << 4)
#define PRIM_FST (1u << 8)

/* DECAL, TCC=1, nearest, UV sprite of w x h texels at (0,0) */
static void tex_sprite(gs_state *gs, int w, int h)
{
    ad(gs, GS_PRIM, GS_PRIM_SPRITE | PRIM_TME | PRIM_FST);
    ad(gs, GS_RGBAQ, r_rgbaq(128, 128, 128, 128, 1.0f));
    ad(gs, GS_UV, 0);
    ad(gs, GS_XYZ2, r_xyz(0, 0, 0));
    ad(gs, GS_UV, ((uint64_t)w << 4) | ((uint64_t)(h << 4) << 16));
    ad(gs, GS_XYZ2, r_xyz((uint32_t)w << 4, (uint32_t)h << 4, 0));
}

static uint32_t V(uint32_t x, uint32_t y) { return 0x80000000u | (y << 8) | x; }

static void csm1_t8(void)
{
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    /* CLUT image 16x16 CT32 at block 200 (inside page 6), width 64 */
    for (uint32_t y = 0; y < 16; y++)
        for (uint32_t x = 0; x < 16; x++)
            gs_write_pixel(gs, GS_PSMCT32, 200, 1, x, y, V(x, y));
    /* T8 texture 16x16 at block 320: texel = y*16+x */
    for (uint32_t y = 0; y < 16; y++)
        for (uint32_t x = 0; x < 16; x++)
            gs_write_pixel(gs, GS_PSMT8, 320, 2, x, y, y * 16 + x);
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, 1 | (1 << 2));
    ad(gs, GS_TEX0_1, r_tex0(320, 2, GS_PSMT8, 4, 4, 1, 1, 200, GS_PSMCT32, 0, 0, 1));
    tex_sprite(gs, 16, 16);
    /* hand-derived: entries 8-15 and 16-23 of each 32 are swapped */
    CHECK_EQ(px32(gs, 7, 0), V(7, 0));    /* index 7  -> (7,0)  */
    CHECK_EQ(px32(gs, 8, 0), V(0, 1));    /* index 8  -> (0,1)  */
    CHECK_EQ(px32(gs, 15, 0), V(7, 1));   /* index 15 -> (7,1)  */
    CHECK_EQ(px32(gs, 0, 1), V(8, 0));    /* index 16 -> (8,0)  */
    CHECK_EQ(px32(gs, 7, 1), V(15, 0));   /* index 23 -> (15,0) */
    CHECK_EQ(px32(gs, 8, 1), V(8, 1));    /* index 24 -> (8,1)  */
    CHECK_EQ(px32(gs, 8, 2), V(0, 3));    /* index 40 -> (0,3)  */
    CHECK_EQ(px32(gs, 15, 15), V(15, 15)); /* index 255 */
    /* CT32 entries keep low halves at 0-255 and high halves at 256-511 */
    CHECK_EQ(gs->clut[8], (uint16_t)V(0, 1));
    CHECK_EQ(gs->clut[256 + 8], (uint16_t)(V(0, 1) >> 16));
    gs_destroy(gs);
}

static void csm1_t4_csa_ct16(void)
{
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    /* 8x2 CT16 CLUT at block 300: entry i = (x + 8y) */
    for (uint32_t i = 0; i < 16; i++) {
        uint32_t r = i, g = 31 - i, b = i & 3, a = (i & 1);
        gs_write_pixel(gs, GS_PSMCT16, 300, 1, i & 7, i >> 3, r | (g << 5) | (b << 10) | (a << 15));
    }
    for (uint32_t x = 0; x < 16; x++) gs_write_pixel(gs, GS_PSMT4, 400, 2, x, 0, x);
    ad(gs, GS_TEXA, 0x30 | (1ull << 15) | (0x70ull << 32)); /* TA0=0x30 AEM=1 TA1=0x70 */
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, 1 | (1 << 2));
    ad(gs, GS_TEX0_1, r_tex0(400, 2, GS_PSMT4, 4, 0, 1, 1, 300, GS_PSMCT16, 0, 2, 1));
    for (uint32_t i = 0; i < 16; i++) {
        uint32_t c = i | ((31 - i) << 5) | ((i & 3) << 10) | ((i & 1) << 15);
        CHECK_EQ(gs->clut[32 + i], c);
    }
    tex_sprite(gs, 16, 1);
    for (uint32_t i = 0; i < 16; i++) {
        uint32_t r = i << 3, g = (31 - i) << 3, b = (i & 3) << 3;
        uint32_t a = (i & 1) ? 0x70u : 0x30u;
        CHECK_EQ(px32(gs, (int)i, 0), r | (g << 8) | (b << 16) | (a << 24));
    }
    /* entry 0 has RGB=0 and A bit 0: AEM makes alpha 0.  Make it so. */
    gs_write_pixel(gs, GS_PSMCT16, 300, 1, 0, 0, 0);
    ad(gs, GS_TEX0_1, r_tex0(400, 2, GS_PSMT4, 4, 0, 1, 1, 300, GS_PSMCT16, 0, 2, 1));
    tex_sprite(gs, 1, 1);
    CHECK_EQ(px32(gs, 0, 0), 0u);
    gs_destroy(gs);
}

static void csm1_t4_ct32_csa(void)
{
    gs_state *gs = gs_create();
    for (uint32_t i = 0; i < 16; i++)
        gs_write_pixel(gs, GS_PSMCT32, 300, 1, i & 7, i >> 3, 0xA0000000u + i * 0x10101u);
    ad(gs, GS_TEX0_1, r_tex0(400, 2, GS_PSMT4, 4, 0, 1, 1, 300, GS_PSMCT32, 0, 1, 1));
    for (uint32_t i = 0; i < 16; i++) {
        uint32_t c = 0xA0000000u + i * 0x10101u;
        CHECK_EQ(gs->clut[16 + i], c & 0xFFFF);
        CHECK_EQ(gs->clut[256 + 16 + i], c >> 16);
    }
    gs_destroy(gs);
}

static void csm2(void)
{
    gs_state *gs = gs_create();
    std_target(gs, GS_PSMCT32, GS_PSMZ32);
    /* TEXCLUT: CBW=4 (256 px), COU=2 (x offset 32), COV=5 */
    ad(gs, GS_TEXCLUT, 4 | (2 << 6) | (5 << 12));
    for (uint32_t i = 0; i < 256; i++)
        gs_write_pixel(gs, GS_PSMCT16, 500, 4, 32 + i, 5, (i & 0x7FFF) | 0x8000u);
    for (uint32_t x = 0; x < 16; x++) gs_write_pixel(gs, GS_PSMT8, 700, 2, x, 0, x * 16 + 1);
    ad(gs, GS_TEXA, 0x80ull << 32);
    ad(gs, GS_TEX1_1, 0);
    ad(gs, GS_CLAMP_1, 1 | (1 << 2));
    ad(gs, GS_TEX0_1, r_tex0(700, 2, GS_PSMT8, 4, 0, 1, 1, 500, GS_PSMCT16, 1, 0, 1));
    /* CSM2 is linear: no 8-15/16-23 swap */
    for (uint32_t i = 0; i < 256; i++) CHECK_EQ(gs->clut[i], (i & 0x7FFF) | 0x8000u);
    tex_sprite(gs, 16, 1);
    for (uint32_t x = 0; x < 16; x++) {
        uint32_t i = x * 16 + 1;
        uint32_t c = (i & 31) << 3 | (((i >> 5) & 31) << 11);
        CHECK_EQ(px32(gs, (int)x, 0), c | 0x80000000u);
    }
    gs_destroy(gs);
}

static void cld_modes(void)
{
    gs_state *gs = gs_create();
    for (uint32_t i = 0; i < 16; i++) gs_write_pixel(gs, GS_PSMCT32, 300, 1, i & 7, i >> 3, 100 + i);
    for (uint32_t i = 0; i < 16; i++) gs_write_pixel(gs, GS_PSMCT32, 332, 1, i & 7, i >> 3, 200 + i);
    uint64_t base = r_tex0(0, 1, GS_PSMT4, 4, 4, 1, 1, 300, GS_PSMCT32, 0, 0, 0);
    uint64_t cld = 61;
    ad(gs, GS_TEX0_1, base);                   /* CLD 0: nothing */
    CHECK_EQ(gs->stats.clut_loads, 0);
    ad(gs, GS_TEX0_1, base | (2ull << cld));   /* CLD 2: load, CBP0=300 */
    CHECK_EQ(gs->stats.clut_loads, 1);
    CHECK_EQ(gs->clut[3], 103);
    CHECK_EQ(gs->cbp0, 300);
    gs_write_pixel(gs, GS_PSMCT32, 300, 1, 3, 0, 999);
    ad(gs, GS_TEX0_1, base | (4ull << cld));   /* CLD 4, same CBP: no load */
    CHECK_EQ(gs->stats.clut_loads, 1);
    CHECK_EQ(gs->clut[3], 103);
    ad(gs, GS_TEX0_1, base | (1ull << cld));   /* CLD 1: always */
    CHECK_EQ(gs->stats.clut_loads, 2);
    CHECK_EQ(gs->clut[3], 999);
    uint64_t other = r_tex0(0, 1, GS_PSMT4, 4, 4, 1, 1, 332, GS_PSMCT32, 0, 0, 0);
    ad(gs, GS_TEX0_1, other | (4ull << cld));  /* CLD 4, new CBP: load */
    CHECK_EQ(gs->stats.clut_loads, 3);
    CHECK_EQ(gs->clut[3], 203);
    CHECK_EQ(gs->cbp0, 332);
    ad(gs, GS_TEX0_1, base | (5ull << cld));   /* CLD 5 vs CBP1 (0): load */
    CHECK_EQ(gs->stats.clut_loads, 4);
    CHECK_EQ(gs->cbp1, 300);
    ad(gs, GS_TEX0_1, base | (5ull << cld));   /* again: no load */
    CHECK_EQ(gs->stats.clut_loads, 4);
    ad(gs, GS_TEX0_1, other | (3ull << cld));  /* CLD 3: load, CBP1=332 */
    CHECK_EQ(gs->stats.clut_loads, 5);
    CHECK_EQ(gs->cbp1, 332);
    /* non-indexed PSM never loads */
    ad(gs, GS_TEX0_1, r_tex0(0, 1, GS_PSMCT32, 4, 4, 1, 1, 300, GS_PSMCT32, 0, 0, 1));
    CHECK_EQ(gs->stats.clut_loads, 5);
    /* TEX2 replaces PSM/CBP.. and loads; TBP0/TBW/TW/TH kept */
    ad(gs, GS_TEX0_1, r_tex0(1234, 3, GS_PSMCT32, 5, 6, 1, 1, 0, 0, 0, 0, 0));
    ad(gs, GS_TEX2_1, r_tex0(0, 0, GS_PSMT4, 0, 0, 0, 0, 300, GS_PSMCT32, 0, 0, 1));
    CHECK_EQ(gs->stats.clut_loads, 6);
    CHECK_EQ(gs->reg[GS_TEX0_1] & 0x3FFF, 1234);
    CHECK_EQ((gs->reg[GS_TEX0_1] >> 20) & 0x3F, GS_PSMT4);
    CHECK_EQ((gs->reg[GS_TEX0_1] >> 26) & 0xF, 5);
    gs_destroy(gs);
}

int test_clut(const char *name)
{
    if (!strcmp(name, "clut_csm1_t8")) { csm1_t8(); return 1; }
    if (!strcmp(name, "clut_csm1_t4_ct16")) { csm1_t4_csa_ct16(); return 1; }
    if (!strcmp(name, "clut_csm1_t4_ct32")) { csm1_t4_ct32_csa(); return 1; }
    if (!strcmp(name, "clut_csm2")) { csm2(); return 1; }
    if (!strcmp(name, "clut_cld")) { cld_modes(); return 1; }
    return 0;
}
