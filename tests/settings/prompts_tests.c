/* SPDX-License-Identifier: CC0-1.0 */
/* Button-prompt swap tests (docs/PROMPTS.md "Implementation"):
 *   rg-prompts-tests <name> [args]; exit 0 = pass.
 *
 * Unit tests (synthetic gaiji2-shaped image, no game data):
 *   layout       rg_gaiji_layout_of accepts the IM3/TIM2 shape, rejects damage
 *   build        every style: index bytes outside the 8 rects and every palette
 *                entry used there unchanged (checked through an independent
 *                swizzle written here from the GS layout), the rects redrawn,
 *                deterministic, PlayStation = the original
 *   art          style-specific colours inside the rects (Xbox face colours,
 *                Nintendo white letters, keyboard light key caps, mouse icon)
 *   key_labels   binding text -> label (gaiji.py key_label)
 *   step         the runtime switch: never writes while PlayStation is wanted,
 *                writes once per change, restores the original byte for byte,
 *                re-captures a game reload, rebuilds on a keyboard rebind
 *   step_control (WILL_FAIL) a PlayStation step that writes must be caught
 * Helpers (tools/prompts/compare.py, the real-data check):
 *   build_img <orig.img> <style> <out.img> [k0..k7]   the C build of one style
 *   rgba <in.img> <out.rgba>                           decode to raw RGBA8 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rg_prompts.h"

static int g_fail;
#define CHECK(c) do { if (!(c)) { g_fail++; if (g_fail < 40) \
    fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { long long _a = (long long)(a), _b = (long long)(b); \
    if (_a != _b) { g_fail++; if (g_fail < 40) fprintf(stderr, \
    "%s:%d: %s == %lld, expected %s == %lld\n", __FILE__, __LINE__, #a, _a, #b, _b); } } while (0)
#define CHECK_STR(a, b) do { const char *_a = (a), *_b = (b); if (strcmp(_a, _b)) { g_fail++; \
    fprintf(stderr, "%s:%d: \"%s\", expected \"%s\"\n", __FILE__, __LINE__, _a, _b); } } while (0)

/* ------------------------------------------------------------ a synthetic gaiji2.img */
#define IMG_SIZE 0x10490   /* 0x50 IM3 + TIM2 0x10 + 0x30 + 0x10000 + 0x400 */
#define PIX 0x90
#define CLUT (PIX + 0x10000)

static void wr32(uint8_t *p, uint32_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); p[2] = (uint8_t)(v >> 16); p[3] = (uint8_t)(v >> 24); }
static void wr16(uint8_t *p, uint16_t v) { p[0] = (uint8_t)v; p[1] = (uint8_t)(v >> 8); }

static uint32_t g_rng = 12345;
static uint32_t rnd(void) { g_rng = g_rng * 1103515245u + 12345u; return g_rng >> 8; }

/* The swizzle again, from the GS PSMT8-through-PSMCT32 layout (gaiji.py
 * _swizzle8_table; "(x >> 2) & 2" written as bit 3 of x moved to bit 1). */
static uint32_t swizzle_off(int x, int y)
{
    int w = 256;
    return (uint32_t)((y & ~0xF) * w + (x & ~0xF) * 2 + ((((y & ~3) >> 1) + (y & 1)) & 7) * w * 2 +
                      ((x + (((y + 2) >> 2) & 1) * 4) & 7) * 4 + ((y >> 1) & 1) + (((x >> 3) & 1) << 1));
}
static int csm1(int i) { return (i & 0xE7) | ((i & 0x08) << 1) | ((i & 0x10) >> 1); }

static int in_rect(int x, int y)
{
    for (int b = 0; b < RG_GAIJI_BUTTONS; b++) {
        const rg_gaiji_rect *r = &rg_gaiji_button_rects[b];
        if (x >= r->u && x < r->u + r->w && y >= r->v && y < r->v + r->h) return 1;
    }
    return 0;
}

/* pixels: index 0..249 outside the rects (250..255 left unused, i.e. free),
 * a smooth gradient so neighbouring pixels differ; palette random, alpha
 * 0..0x80; index 0 transparent black. */
static void make_img(uint8_t *img, uint32_t seed)
{
    memset(img, 0, IMG_SIZE);
    memcpy(img, "IM3", 4);
    wr32(img + 4, 0x10);
    wr32(img + 8, 1);
    memcpy(img + 0x10, "gaiji2", 7);
    wr32(img + 0x10 + 0x20, 0x40);
    wr32(img + 0x10 + 0x24, 0x50);
    wr32(img + 0x10 + 0x34, 0x10440);
    uint8_t *t = img + 0x50;
    memcpy(t, "TIM2", 4);
    t[4] = 4; t[5] = 0;
    wr16(t + 6, 1);
    uint8_t *p = t + 0x10;
    wr32(p, 0x10430);
    wr32(p + 4, 1024);
    wr32(p + 8, 0x10000);
    wr16(p + 12, 0x30);
    wr16(p + 14, 256);
    p[16] = 0; p[17] = 1; p[18] = 3; p[19] = 5;
    wr16(p + 20, 256);
    wr16(p + 22, 256);
    g_rng = seed;
    for (int y = 0; y < 256; y++)
        for (int x = 0; x < 256; x++) {
            int v = in_rect(x, y) ? (int)(rnd() % 250) : (x + y * 3 + (int)(rnd() % 4)) % 250;
            img[PIX + swizzle_off(x, y)] = (uint8_t)v;
        }
    for (int i = 0; i < 256; i++) {
        uint8_t *e = img + CLUT + 4 * csm1(i);
        e[0] = (uint8_t)rnd(); e[1] = (uint8_t)rnd(); e[2] = (uint8_t)rnd();
        e[3] = (uint8_t)(rnd() % 0x81);
    }
    memset(img + CLUT + 4 * csm1(0), 0, 4);
}

static uint8_t idx_at(const uint8_t *region, int x, int y) { return region[swizzle_off(x, y)]; }
static const uint8_t *pal_at(const uint8_t *region, int i) { return region + 0x10000 + 4 * csm1(i); }

/* ------------------------------------------------------------ tests */
static int t_layout(void)
{
    static uint8_t img[IMG_SIZE + 64];
    rg_gaiji_layout L;
    make_img(img, 1);
    CHECK_EQ(rg_gaiji_layout_of(img, IMG_SIZE, &L), 0);
    CHECK_EQ(L.pixels, PIX);
    CHECK_EQ(L.clut, CLUT);
    CHECK_EQ(L.end, IMG_SIZE);
    CHECK_EQ(rg_gaiji_layout_of(img, RG_GAIJI_IMG_MAX, &L), 0);
    CHECK_EQ(rg_gaiji_layout_of(img, IMG_SIZE - 1, &L), -1);    /* truncated */
    CHECK_EQ(rg_gaiji_layout_of(NULL, IMG_SIZE, &L), -1);
    static const struct { int off; uint8_t v; } bad[] = {
        { 0, 'X' }, { 4, 0x11 }, { 8, 2 }, { 0x34, 0x60 }, { 0x50, 'X' }, { 0x55, 1 },
        { 0x56, 2 }, { 0x6F, 4 }, { 0x6E, 2 }, { 0x64, 1 }, { 0x68, 1 }, { 0x71, 2 },
        { 0x72, 2 }, { 0x73, 4 }, { 0x74, 0x80 }, { 0x77, 2 }, { 0x60, 0 },
    };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; i++) {
        make_img(img, 1);
        img[bad[i].off] = bad[i].v;
        if (rg_gaiji_layout_of(img, IMG_SIZE, &L) != -1) {
            g_fail++;
            fprintf(stderr, "layout accepted damage at +0x%x\n", bad[i].off);
        }
    }
    memset(img, 0, sizeof img);   /* the buffer before the game loads it */
    CHECK_EQ(rg_gaiji_layout_of(img, RG_GAIJI_IMG_MAX, &L), -1);
    return 0;
}

static int t_build(void)
{
    static uint8_t img[IMG_SIZE], out[RG_GAIJI_SWAP_BYTES], again[RG_GAIJI_SWAP_BYTES];
    make_img(img, 7);
    const uint8_t *orig = img + PIX;
    CHECK_EQ(rg_gaiji_build(orig, RG_GAIJI_PLAYSTATION, NULL, out), 0);
    CHECK(!memcmp(out, orig, RG_GAIJI_SWAP_BYTES));
    CHECK_EQ(rg_gaiji_build(orig, -1, NULL, out), -1);
    CHECK_EQ(rg_gaiji_build(orig, RG_GAIJI_STYLES, NULL, out), -1);
    for (int st = RG_GAIJI_XBOX; st < RG_GAIJI_STYLES; st++) {
        CHECK_EQ(rg_gaiji_build(orig, st, NULL, out), 0);
        CHECK_EQ(rg_gaiji_build(orig, st, NULL, again), 0);
        CHECK(!memcmp(out, again, RG_GAIJI_SWAP_BYTES));
        uint8_t used_out[256] = { 0 };
        int outside_diff = 0, inside_diff = 0;
        for (int y = 0; y < 256; y++)
            for (int x = 0; x < 256; x++) {
                int d = idx_at(out, x, y) != idx_at(orig, x, y);
                if (in_rect(x, y)) inside_diff += d;
                else { outside_diff += d; used_out[idx_at(orig, x, y)] = 1; }
            }
        CHECK_EQ(outside_diff, 0);
        CHECK(inside_diff > 2000);   /* of 4496 rect pixels */
        int pal_changed = 0, free_changed = 0;
        for (int i = 0; i < 256; i++) {
            int d = memcmp(pal_at(out, i), pal_at(orig, i), 4) != 0;
            if (used_out[i]) pal_changed += d;
            else free_changed += d;
            CHECK(pal_at(out, i)[3] <= 0x80);
        }
        CHECK_EQ(pal_changed, 0);
        CHECK(free_changed >= 1 && free_changed <= 6);
        /* every rect pixel indexes either a kept colour or a reassigned slot */
        fprintf(stderr, "style %d: %d rect pixels changed, %d palette slots reassigned\n", st,
                inside_diff, free_changed);
    }
    return 0;
}

static void rect_stats(const uint8_t *region, int btn, int *n_green, int *n_white, int *n_light,
                       int *n_red, int *n_opaque)
{
    const rg_gaiji_rect *r = &rg_gaiji_button_rects[btn];
    *n_green = *n_white = *n_light = *n_red = *n_opaque = 0;
    for (int y = r->v; y < r->v + r->h; y++)
        for (int x = r->u; x < r->u + r->w; x++) {
            const uint8_t *c = pal_at(region, idx_at(region, x, y));
            if (c[3] < 0x60) continue;
            (*n_opaque)++;
            if (c[1] > 150 && c[0] < 140 && c[2] < 100) (*n_green)++;
            if (c[0] > 200 && c[1] > 200 && c[2] > 200) (*n_white)++;
            if (c[0] > 180 && c[1] > 180 && c[2] > 180) (*n_light)++;
            if (c[0] > 180 && c[1] < 100 && c[2] < 100) (*n_red)++;
        }
}

static int t_art(void)
{
    static uint8_t img[IMG_SIZE], out[RG_GAIJI_SWAP_BYTES];
    int g, w, l, r, o;
    make_img(img, 3);
    CHECK_EQ(rg_gaiji_build(img + PIX, RG_GAIJI_XBOX, NULL, out), 0);
    rect_stats(out, RG_GAIJI_CROSS, &g, &w, &l, &r, &o);
    CHECK(g >= 8);          /* the green A */
    CHECK(o >= 250);        /* a disc fills most of 22x22 */
    rect_stats(out, RG_GAIJI_CIRCLE, &g, &w, &l, &r, &o);
    CHECK(r >= 8 && g == 0);  /* the red B */
    rect_stats(out, RG_GAIJI_L1, &g, &w, &l, &r, &o);
    CHECK(w >= 8 && g == 0);  /* LB in white */
    CHECK_EQ(rg_gaiji_build(img + PIX, RG_GAIJI_NINTENDO, NULL, out), 0);
    for (int b = RG_GAIJI_CIRCLE; b <= RG_GAIJI_CROSS; b++) {
        rect_stats(out, b, &g, &w, &l, &r, &o);
        CHECK(w >= 8 && g == 0 && r == 0);
    }
    CHECK_EQ(rg_gaiji_build(img + PIX, RG_GAIJI_KEYBOARD, NULL, out), 0);
    for (int b = 0; b < RG_GAIJI_BUTTONS; b++) {
        rect_stats(out, b, &g, &w, &l, &r, &o);
        CHECK(l >= 150);    /* a light key cap */
    }
    /* a mouse button binding draws the mouse with its button highlighted red */
    const char *keys[RG_GAIJI_BUTTONS] = { "key:1", "key:Q", "key:E", "key:3", "mouse:right",
                                           "key:Tab", "mouse:left", NULL };
    CHECK_EQ(rg_gaiji_build(img + PIX, RG_GAIJI_KEYBOARD, keys, out), 0);
    rect_stats(out, RG_GAIJI_CIRCLE, &g, &w, &l, &r, &o);
    CHECK(r >= 4);
    rect_stats(out, RG_GAIJI_SQUARE, &g, &w, &l, &r, &o);
    CHECK(r >= 4);
    rect_stats(out, RG_GAIJI_TRIANGLE, &g, &w, &l, &r, &o);
    CHECK(r == 0);
    return 0;
}

static int t_key_labels(void)
{
    static const struct { const char *in, *want; int mouse; } k[] = {
        { "key:Space", "SPC", 0 }, { "key:Return", "ENT", 0 }, { "key:Left Shift", "SHF", 0 },
        { "key:Right Ctrl", "CTL", 0 }, { "key:Up", "\x01", 0 }, { "key:Down", "\x02", 0 },
        { "key:Left", "\x03", 0 }, { "key:Right", "\x04", 0 }, { "key:comma", ",", 0 },
        { "key:Keypad 8", "K8", 0 }, { "key:Keypad Enter", "KEN", 0 }, { "key:Q", "Q", 0 },
        { "key:F11", "F11", 0 }, { "key:Escape", "ESC", 0 }, { "key:Tab", "TAB", 0 },
        { "key:PrintScreen", "PRIN", 0 }, { "key:1", "1", 0 }, { "key:Page Down", "PGD", 0 },
        { "mouse:left", "", 1 }, { "mouse:middle", "", 2 }, { "mouse:right", "", 3 },
        { "mouse:x1", "", 4 }, { "mouse:x2", "", 5 }, { NULL, "-", 0 }, { "", "-", 0 },
    };
    for (size_t i = 0; i < sizeof k / sizeof k[0]; i++) {
        char out[16];
        int m = -1;
        rg_gaiji_key_label(k[i].in, out, sizeof out, &m);
        CHECK_STR(out, k[i].want);
        CHECK_EQ(m, k[i].mouse);
    }
    return 0;
}

static int step_flow(int control)
{
    static uint8_t buf[RG_GAIJI_IMG_MAX], img[IMG_SIZE], snap[RG_GAIJI_IMG_MAX];
    rg_prompts_ctl c;
    rg_prompts_init(&c);
    memset(buf, 0, sizeof buf);
    /* not loaded yet: nothing happens, whatever is wanted */
    for (int st = 0; st < RG_GAIJI_STYLES; st++)
        CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, st, NULL), 0);
    for (size_t i = 0; i < sizeof buf; i++)
        if (buf[i]) { CHECK(!"buffer written before load"); break; }
    make_img(img, 11);
    memcpy(buf, img, IMG_SIZE);
    memcpy(snap, buf, sizeof buf);
    /* PlayStation (Original, scripted): reads only, for ever */
    for (int k = 0; k < 100; k++)
        CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_PLAYSTATION, NULL), 0);
    if (control)   /* the control: a write behind the switch's back must be seen */
        buf[PIX + 5] ^= 1;
    CHECK(!memcmp(buf, snap, sizeof buf));
    CHECK_EQ(c.writes, 0);
    CHECK_EQ(c.captures, 1);
    /* xbox: one write, then nothing while it stays */
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_XBOX, NULL), 1);
    CHECK(memcmp(buf + PIX, snap + PIX, RG_GAIJI_SWAP_BYTES) != 0);
    CHECK(!memcmp(buf, snap, PIX));   /* headers untouched */
    CHECK(!memcmp(buf + PIX + RG_GAIJI_SWAP_BYTES, snap + PIX + RG_GAIJI_SWAP_BYTES,
                  sizeof buf - PIX - RG_GAIJI_SWAP_BYTES));
    for (int k = 0; k < 10; k++)
        CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_XBOX, NULL), 0);
    CHECK_EQ(c.writes, 1);
    /* back to PlayStation: the original, byte for byte */
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_PLAYSTATION, NULL), 1);
    CHECK(!memcmp(buf, snap, sizeof buf));
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_PLAYSTATION, NULL), 0);
    /* every style round trip ends on the original */
    for (int a = 0; a < RG_GAIJI_STYLES; a++)
        for (int b = 0; b < RG_GAIJI_STYLES; b++) {
            rg_prompts_step(&c, buf, sizeof buf, a, NULL);
            rg_prompts_step(&c, buf, sizeof buf, b, NULL);
            rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_PLAYSTATION, NULL);
            CHECK(!memcmp(buf, snap, sizeof buf));
        }
    CHECK_EQ(c.captures, 1);
    /* the game reloads the file while Xbox is shown: re-captured, then Xbox again */
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_XBOX, NULL), 1);
    memcpy(buf, img, IMG_SIZE);
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_XBOX, NULL), 1);
    CHECK_EQ(c.captures, 2);
    /* a different file loaded (another pack): that becomes the original */
    static uint8_t img2[IMG_SIZE];
    make_img(img2, 99);
    memcpy(buf, img2, IMG_SIZE);
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_PLAYSTATION, NULL), 0);
    CHECK_EQ(c.captures, 3);
    CHECK(!memcmp(buf, img2, IMG_SIZE));
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_NINTENDO, NULL), 1);
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_PLAYSTATION, NULL), 1);
    CHECK(!memcmp(buf, img2, IMG_SIZE));
    /* keyboard: rebinding rebuilds; the same bindings don't */
    const char *k1[RG_GAIJI_BUTTONS] = { "key:1", "key:Q", "key:E", "key:3", "key:C", "key:Tab", "key:Z", "key:Space" };
    const char *k2[RG_GAIJI_BUTTONS] = { "key:1", "key:Q", "key:E", "key:3", "key:C", "key:Tab", "key:Z", "key:Return" };
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_KEYBOARD, k1), 1);
    static uint8_t kb1[RG_GAIJI_SWAP_BYTES];
    memcpy(kb1, buf + PIX, sizeof kb1);
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_KEYBOARD, k1), 0);
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_KEYBOARD, k2), 1);
    CHECK(memcmp(kb1, buf + PIX, sizeof kb1) != 0);
    /* only the Cross rect differs between the two keyboard images */
    for (int y = 0; y < 256; y++)
        for (int x = 0; x < 256; x++) {
            const rg_gaiji_rect *r = &rg_gaiji_button_rects[RG_GAIJI_CROSS];
            int cross = x >= r->u && x < r->u + r->w && y >= r->v && y < r->v + r->h;
            const uint8_t *a = pal_at(kb1, idx_at(kb1, x, y));
            const uint8_t *b = pal_at(buf + PIX, idx_at(buf + PIX, x, y));
            if (!cross && memcmp(a, b, 4)) { CHECK(!"keyboard rebind changed another glyph"); x = y = 999; }
        }
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, RG_GAIJI_KEYBOARD, k2), 0);
    CHECK_EQ(rg_prompts_step(&c, buf, sizeof buf, 77, NULL), 1);   /* bad -> PlayStation */
    CHECK(!memcmp(buf, img2, IMG_SIZE));
    rg_prompts_free(&c);
    return 0;
}
static int t_step(void) { return step_flow(0); }
static int t_step_control(void) { return step_flow(1); }

/* ------------------------------------------------------------ helpers */
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

static int h_build_img(int argc, char **argv)
{
    if (argc < 5) return 2;
    size_t n = 0;
    uint8_t *img = read_file(argv[2], &n);
    rg_gaiji_layout L;
    if (!img || rg_gaiji_layout_of(img, n, &L)) { fprintf(stderr, "bad image %s\n", argv[2]); return 1; }
    static const char *const names[] = { "playstation", "xbox", "nintendo", "keyboard" };
    int st = -1;
    for (int i = 0; i < 4; i++) if (!strcmp(argv[3], names[i])) st = i;
    const char *keys[RG_GAIJI_BUTTONS];
    const char *const *kp = NULL;
    if (argc >= 6 + RG_GAIJI_BUTTONS - 1) {
        for (int i = 0; i < RG_GAIJI_BUTTONS; i++) keys[i] = strcmp(argv[5 + i], "-") ? argv[5 + i] : NULL;
        kp = keys;
    }
    static uint8_t out[RG_GAIJI_SWAP_BYTES];
    if (rg_gaiji_build(img + L.pixels, st, kp, out)) { fprintf(stderr, "build failed\n"); return 1; }
    memcpy(img + L.pixels, out, sizeof out);
    FILE *f = fopen(argv[4], "wb");
    if (!f) return 1;
    fwrite(img, 1, n, f);
    fclose(f);
    free(img);
    return 0;
}

static int h_rgba(int argc, char **argv)
{
    if (argc < 4) return 2;
    size_t n = 0;
    uint8_t *img = read_file(argv[2], &n);
    rg_gaiji_layout L;
    if (!img || rg_gaiji_layout_of(img, n, &L)) return 1;
    static uint8_t rgba[256 * 256 * 4];
    rg_gaiji_region_rgba(img + L.pixels, rgba);
    FILE *f = fopen(argv[3], "wb");
    if (!f) return 1;
    fwrite(rgba, 1, sizeof rgba, f);
    fclose(f);
    free(img);
    return 0;
}

typedef struct test { const char *name; int (*fn)(void); } test;
static const test k_tests[] = {
    { "layout", t_layout }, { "build", t_build }, { "art", t_art }, { "key_labels", t_key_labels },
    { "step", t_step }, { "step_control", t_step_control },
};

int main(int argc, char **argv)
{
    if (argc < 2) { fprintf(stderr, "usage: rg-prompts-tests <name|all> [args]\n"); return 2; }
    if (!strcmp(argv[1], "build_img")) return h_build_img(argc, argv);
    if (!strcmp(argv[1], "rgba")) return h_rgba(argc, argv);
    int ran = 0;
    for (size_t i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        if (strcmp(argv[1], k_tests[i].name) && strcmp(argv[1], "all")) continue;
        if (!strcmp(argv[1], "all") && strstr(k_tests[i].name, "control")) continue;
        int before = g_fail;
        k_tests[i].fn();
        fprintf(stderr, "%s: %s\n", k_tests[i].name, g_fail == before ? "PASS" : "FAIL");
        ran++;
    }
    if (!ran) { fprintf(stderr, "unknown test %s\n", argv[1]); return 2; }
    return g_fail ? 1 : 0;
}
