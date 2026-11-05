/* SPDX-License-Identifier: CC0-1.0 */
/* Upload-time texture patch tests (src/settings/rg_texpatch.h; docs/PROMPTS.md "Prompts baked
 * into other textures", docs/ACCESSIBILITY.md):  rg-texpatch-tests <name> [args]; exit 0 = pass.
 *
 * Unit tests (synthetic textures, no game data):
 *   sites      prompt sites: PlayStation with default bindings changes nothing; every other
 *              style redraws inside the site rects only (index bytes outside untouched, CLUT
 *              untouched); a moved binding redraws a PlayStation site; deterministic
 *   marks      colour-blind groups: off changes nothing; protan / deutan recolour only the
 *              CLUT entries used by one group alone (shared / outside entries and the pixels
 *              untouched), keeping each entry's alpha
 *   switch     the runtime switch: inactive (PlayStation, defaults, off) returns NULL without
 *              hashing or capturing anything; transfers of other sizes / contents pass through
 *   pad_button binding text -> physical button (rg_prompt_pad_button)
 * Helper (tools/p6/texpatch_gen.py --verify, the real-data check):
 *   build <target> <pix> <clut> <style> <cb> <out.pix> <out.clut> [k0..k11]
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_prompts.h"
#include "rg_texpatch.h"

static int g_fail;
#define CHECK(c) do { if (!(c)) { g_fail++; if (g_fail < 40) \
    fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { long long _a = (long long)(a), _b = (long long)(b); \
    if (_a != _b) { g_fail++; if (g_fail < 40) fprintf(stderr, \
    "%s:%d: %s == %lld, expected %s == %lld\n", __FILE__, __LINE__, #a, _a, #b, _b); } } while (0)

/* independent PSMT8 swizzle (the GS layout of a PSMCT32 upload, written out again here) */
static uint32_t swz(int w, int x, int y)
{
    int bx = x & ~0xF, by = y & ~0xF, ly = y & 0xF;
    int swap = (((y + 2) >> 2) & 1) * 4;
    int col = ((((ly & ~3) >> 1) + (ly & 1)) & 7);
    return (uint32_t)(by * w + bx * 2 + col * w * 2 + ((x + swap) & 7) * 4 + ((y >> 1) & 1) + ((x >> 2) & 2));
}
static int csm1(int i) { return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1); }

#define TW 64
#define TH 64
static uint8_t g_pix[TW * TH], g_clut[1024];

/* a synthetic 64x64 PSMT8 sheet: background index 0 (clear), a grey "disc" of index 1..3 in
 * cell (4,4,22,22), random art elsewhere from indices 10..60, four 8x8 marker squares
 * coloured by groups (entries 100..103 alone, 110 shared by all four: an outline) */
static void make_tex(void)
{
    uint32_t r = 77;
    memset(g_pix, 0, sizeof g_pix);
    for (int y = 0; y < TH; y++)
        for (int x = 0; x < TW; x++) {
            int v = 0;
            r = r * 1103515245u + 12345u;
            if (y >= 32) v = 10 + (int)((r >> 8) % 50);
            if (x >= 4 && x < 26 && y >= 4 && y < 26) {
                int dx = x - 15, dy = y - 15;
                v = dx * dx + dy * dy < 100 ? 1 + (dx > 0) + (dy > 0) : 0;
            }
            for (int g = 0; g < 4; g++)
                if (x >= 30 + 8 * g && x < 38 + 8 * g && y >= 4 && y < 12)
                    v = (x == 30 + 8 * g || y == 4) ? 110 : 100 + g;
            g_pix[swz(TW, x, y)] = (uint8_t)v;
        }
    for (int i = 0; i < 256; i++) {
        uint8_t *e = g_clut + 4 * csm1(i);
        e[0] = (uint8_t)(i * 7); e[1] = (uint8_t)(i * 13); e[2] = (uint8_t)(i * 29); e[3] = i ? 0x80 : 0;
    }
    /* marker groups: red, green, orange, blue */
    static const uint8_t mc[4][3] = { { 200, 40, 40 }, { 40, 180, 60 }, { 230, 140, 30 }, { 40, 80, 220 } };
    for (int g = 0; g < 4; g++) memcpy(g_clut + 4 * csm1(100 + g), mc[g], 3);
}

static const rg_tp_site k_sites[] = {
    { 4, 4, 22, 22, RG_GAIJI_SQUARE, RG_PROMPT_SHAPE_CELL },
    { 0, 50, 30, 12, RG_PROMPT_START, RG_PROMPT_SHAPE_TEXT },
};
static const rg_tp_mark k_marks[] = { { 30, 4, 8, 8, 0 }, { 38, 4, 8, 8, 1 }, { 46, 4, 8, 8, 2 }, { 54, 4, 8, 8, 3 } };
static const uint32_t k_cols[][4] = {
    { 0xFF000000u, 0xD55E00u, 0xD55E00u, 0xFF000000u },
    { 0xFF000000u, 0x56B4E9u, 0x56B4E9u, 0xFF000000u },
    { 0xFF000000u, 0xE69F00u, 0xE69F00u, 0xFF000000u },
    { 0xFF000000u, 0x0072B2u, 0x0072B2u, 0xFF000000u },
};
static const rg_tp_target k_t = { "synthetic", TW, TH, 8, TW * TH, 1024, 0, 0, k_sites, 2, k_marks, 4, k_cols, 4 };

static int in_sites(int x, int y)
{
    for (int s = 0; s < 2; s++)
        if (x >= k_sites[s].x && x < k_sites[s].x + k_sites[s].w && y >= k_sites[s].y && y < k_sites[s].y + k_sites[s].h)
            return 1;
    return 0;
}

static int t_sites(void)
{
    make_tex();
    static uint8_t p[TW * TH], c[1024], p2[TW * TH], c2[1024];
    int pc = -1, cc = -1;
    CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, RG_GAIJI_PLAYSTATION, NULL, RG_CB_OFF, p, c, &pc, &cc), 0);
    CHECK_EQ(pc, 0);
    CHECK_EQ(cc, 0);
    CHECK(!memcmp(p, g_pix, sizeof p) && !memcmp(c, g_clut, sizeof c));
    for (int st = RG_GAIJI_XBOX; st < RG_GAIJI_STYLES; st++) {
        CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, st, NULL, RG_CB_OFF, p, c, &pc, &cc), 0);
        CHECK_EQ(pc, 1);
        CHECK_EQ(cc, 0);
        CHECK(!memcmp(c, g_clut, sizeof c));
        int inside = 0, outside = 0;
        for (int y = 0; y < TH; y++)
            for (int x = 0; x < TW; x++) {
                int d = p[swz(TW, x, y)] != g_pix[swz(TW, x, y)];
                if (in_sites(x, y)) inside += d; else outside += d;
            }
        CHECK(inside > 20);
        CHECK_EQ(outside, 0);
        CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, st, NULL, RG_CB_OFF, p2, c2, NULL, NULL), 0);
        CHECK(!memcmp(p, p2, sizeof p));   /* deterministic */
    }
    /* PlayStation with Square's action moved to south: that site is redrawn, START is not */
    const char *keys[RG_PROMPT_SLOTS] = { "axis:lefttrigger+", "pad:leftshoulder", "pad:rightshoulder",
        "axis:righttrigger+", "pad:b", "pad:y", "pad:a", "pad:a", "pad:leftstick", "pad:rightstick",
        "pad:start", "pad:back" };
    CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, RG_GAIJI_PLAYSTATION, keys, RG_CB_OFF, p, c, &pc, &cc), 0);
    CHECK_EQ(pc, 1);
    int sq = 0, st = 0;
    for (int y = 0; y < TH; y++)
        for (int x = 0; x < TW; x++)
            if (p[swz(TW, x, y)] != g_pix[swz(TW, x, y)]) { if (y < 32) sq++; else st++; }
    CHECK(sq > 0);
    CHECK_EQ(st, 0);
    keys[RG_GAIJI_SQUARE] = "pad:x";   /* back to positional: nothing */
    CHECK(rg_prompt_keys_default(RG_GAIJI_PLAYSTATION, keys, RG_PROMPT_SLOTS));
    CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, RG_GAIJI_PLAYSTATION, keys, RG_CB_OFF, p, c, &pc, &cc), 0);
    CHECK_EQ(pc, 0);
    return 0;
}

static int t_marks(void)
{
    make_tex();
    static uint8_t p[TW * TH], c[1024];
    int pc = -1, cc = -1;
    CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, RG_GAIJI_PLAYSTATION, NULL, RG_CB_TRITAN, p, c, &pc, &cc), 0);
    CHECK_EQ(cc, 0);   /* (tritan keeps these groups) */
    for (int cb = RG_CB_PROTAN; cb <= RG_CB_DEUTAN; cb++) {
        CHECK_EQ(rg_tp_build(&k_t, g_pix, g_clut, RG_GAIJI_PLAYSTATION, NULL, cb, p, c, &pc, &cc), 0);
        CHECK_EQ(pc, 0);
        CHECK_EQ(cc, 1);
        CHECK(!memcmp(p, g_pix, sizeof p));
        for (int i = 0; i < 256; i++) {
            const uint8_t *a = g_clut + 4 * csm1(i), *b = c + 4 * csm1(i);
            int group = i >= 100 && i <= 103;
            if (!group) CHECK(!memcmp(a, b, 4));   /* (110: the shared outline stays) */
            else {
                CHECK(memcmp(a, b, 3) != 0);
                CHECK_EQ(a[3], b[3]);
            }
        }
        /* the hues: group 1 (green) became sky blue: blue is now its largest channel */
        const uint8_t *g1 = c + 4 * csm1(101);
        CHECK(g1[2] > g1[0] && g1[2] > g1[1] - 20);
    }
    return 0;
}

static int t_switch(void)
{
    static uint8_t d[65536];
    unsigned rep0, cap0, b0, rep, cap, b;
    rg_texpatch_stats(&rep0, &cap0, &b0);
    rg_texpatch_update(RG_GAIJI_PLAYSTATION, NULL, RG_CB_OFF);
    for (int k = 0; k < 100; k++) CHECK(rg_texpatch_xfer(d, sizeof d) == NULL);
    rg_texpatch_stats(&rep, &cap, &b);
    CHECK_EQ(cap, cap0);
    CHECK_EQ(rep, rep0);
    /* active, but nothing the table knows: passes through */
    rg_texpatch_update(RG_GAIJI_XBOX, NULL, RG_CB_OFF);
    for (int k = 0; k < 10; k++) {
        d[0] = (uint8_t)k;
        CHECK(rg_texpatch_xfer(d, sizeof d) == NULL);
        CHECK(rg_texpatch_xfer(d, 1024) == NULL);
        CHECK(rg_texpatch_xfer(d, 77) == NULL);
    }
    rg_texpatch_stats(&rep, &cap, &b);
    CHECK_EQ(cap, cap0);
    CHECK_EQ(rep, rep0);
    rg_texpatch_update(RG_GAIJI_PLAYSTATION, NULL, RG_CB_OFF);
    return 0;
}

static int t_pad_button(void)
{
    CHECK_EQ(rg_prompt_pad_button("pad:a"), 0);
    CHECK_EQ(rg_prompt_pad_button("pad:B"), 1);
    CHECK_EQ(rg_prompt_pad_button("pad:x"), 2);
    CHECK_EQ(rg_prompt_pad_button("pad:y"), 3);
    CHECK_EQ(rg_prompt_pad_button("pad:leftshoulder"), 4);
    CHECK_EQ(rg_prompt_pad_button("axis:righttrigger+"), 7);
    CHECK_EQ(rg_prompt_pad_button("axis:lefttrigger-"), 17);
    CHECK_EQ(rg_prompt_pad_button("axis:leftx+"), 17);
    CHECK_EQ(rg_prompt_pad_button("pad:start"), 10);
    CHECK_EQ(rg_prompt_pad_button("pad:dpleft"), 14);
    CHECK_EQ(rg_prompt_pad_button("key:Space"), -1);
    CHECK_EQ(rg_prompt_pad_button(NULL), -1);
    for (int s = 0; s < RG_PROMPT_SLOTS; s++) CHECK(rg_prompt_slot_default_button(s) >= 0);
    CHECK_EQ(rg_prompt_slot_default_button(RG_GAIJI_CROSS), 0);
    CHECK_EQ(rg_prompt_slot_default_button(RG_PROMPT_START), 10);
    return 0;
}

/* ------------------------------------------------------------ helper */
static uint8_t *read_file(const char *p, size_t *n)
{
    FILE *f = fopen(p, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *b = (uint8_t *)malloc((size_t)sz + 1);
    if (b && fread(b, 1, (size_t)sz, f) != (size_t)sz) { free(b); b = NULL; }
    fclose(f);
    *n = (size_t)sz;
    return b;
}
static int write_file(const char *p, const uint8_t *d, size_t n)
{
    FILE *f = fopen(p, "wb");
    if (!f) return 1;
    fwrite(d, 1, n, f);
    fclose(f);
    return 0;
}

static int h_build(int argc, char **argv)
{
    if (argc < 9) return 2;
    const rg_tp_target *t = NULL;
    for (int i = 0; i < rg_tp_ntargets; i++)
        if (!strcmp(rg_tp_targets[i].name, argv[2])) t = &rg_tp_targets[i];
    if (!t) { fprintf(stderr, "no target %s\n", argv[2]); return 1; }
    size_t np = 0, nc = 0;
    uint8_t *pix = read_file(argv[3], &np), *clut = read_file(argv[4], &nc);
    if (!pix || !clut || np != t->pix_bytes || nc != t->clut_bytes) { fprintf(stderr, "bad input sizes\n"); return 1; }
    if (rg_tp_fnv64(pix, np) != t->pix_hash || rg_tp_fnv64(clut, nc) != t->clut_hash)
        fprintf(stderr, "warning: input hashes differ from the table\n");
    const char *keys[RG_PROMPT_SLOTS];
    const char *const *kp = NULL;
    if (argc >= 9 + RG_PROMPT_SLOTS) {
        for (int i = 0; i < RG_PROMPT_SLOTS; i++) keys[i] = strcmp(argv[9 + i], "-") ? argv[9 + i] : NULL;
        kp = keys;
    }
    uint8_t *op = (uint8_t *)malloc(np), *oc = (uint8_t *)malloc(nc);
    int pc = 0, cc = 0;
    if (!op || !oc || rg_tp_build(t, pix, clut, atoi(argv[5]), kp, atoi(argv[6]), op, oc, &pc, &cc)) return 1;
    printf("pixels %s clut %s\n", pc ? "patched" : "orig", cc ? "patched" : "orig");
    return write_file(argv[7], op, np) || write_file(argv[8], oc, nc);
}

typedef struct test { const char *name; int (*fn)(void); } test;
static const test k_tests[] = {
    { "sites", t_sites }, { "marks", t_marks }, { "switch", t_switch }, { "pad_button", t_pad_button },
};

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: rg-texpatch-tests <name|all> [args]\n"); return 2; }
    if (!strcmp(argv[1], "build")) return h_build(argc, argv);
    int ran = 0;
    for (size_t i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        if (strcmp(argv[1], k_tests[i].name) && strcmp(argv[1], "all")) continue;
        int before = g_fail;
        k_tests[i].fn();
        fprintf(stderr, "%s: %s\n", k_tests[i].name, g_fail == before ? "PASS" : "FAIL");
        ran++;
    }
    if (!ran) { fprintf(stderr, "unknown test %s\n", argv[1]); return 2; }
    return g_fail ? 1 : 0;
}
