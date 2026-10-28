/* SPDX-License-Identifier: CC0-1.0 */
/* Host shell tests (docs/HOST.md): rg-host-tests <name> [args]; exit 0 = pass.
 *
 * Unit tests: pad_report, input_mapping, input_config, input_script,
 *             script_determinism, scaling, png_roundtrip, png_corrupt_control,
 *             pacing, audio_reg, audio_device, audio_focus, wide_fit, wide_present, wide_present_control,
 *             wide_policy, wide_any, wide_host, wide_layout, wide_menu, wide_strips.
 * Helpers used by the CTest scripts:
 *   script_dump <script> <out.bin>   input.py PINE blob (u32 count, u16 words)
 *   png_write <out.png>              a fixed test image (for pngcheck.py)
 *   pngcheck <file.png> [w h]        decode + validate; also checks that the
 *                                    image is not a single flat colour */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "host.h"
#include "rg_aspect.h"
#include "rg_layout.h"
#include "rg_menu.h"
#include "rg_settings.h"
#include "ps2k.h"   /* the pacing hook must have ps2k_pacing_fn's exact type */

static int g_fail;
#define CHECK(c) do { if (!(c)) { g_fail++; if (g_fail < 40) \
    fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { long long _a = (long long)(a), _b = (long long)(b); \
    if (_a != _b) { g_fail++; if (g_fail < 40) fprintf(stderr, \
    "%s:%d: %s == %lld (0x%llX), expected %s == %lld (0x%llX)\n", __FILE__, __LINE__, \
    #a, _a, (unsigned long long)_a, #b, _b, (unsigned long long)_b); } } while (0)

/* ================================================================ PNG check
 * An independent minimal decoder: chunk CRCs, IHDR, zlib header + Adler-32,
 * deflate STORED blocks only (all our encoder emits), filters 0-4. */
static uint32_t be32(const uint8_t *p) { return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3]; }

static uint32_t crc_bitwise(const uint8_t *p, size_t n)
{
    uint32_t c = 0xFFFFFFFFu;
    for (size_t i = 0; i < n; i++) {
        c ^= p[i];
        for (int k = 0; k < 8; k++) c = (c >> 1) ^ (0xEDB88320u & (0u - (c & 1)));
    }
    return ~c;
}

static int paeth(int a, int b, int c)
{
    int p = a + b - c, pa = abs(p - a), pb = abs(p - b), pc = abs(p - c);
    return (pa <= pb && pa <= pc) ? a : (pb <= pc ? b : c);
}

/* returns malloc'd RGBA or NULL (reason in why) */
static uint32_t *png_decode(const uint8_t *d, size_t n, uint32_t *w, uint32_t *h, const char **why)
{
    static const uint8_t sig[8] = { 0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A };
    *why = "signature";
    if (n < 8 || memcmp(d, sig, 8)) return NULL;
    size_t off = 8, zn = 0, zcap = 0;
    uint8_t *z = NULL;
    int have_ihdr = 0, have_iend = 0;
    while (off + 12 <= n) {
        uint32_t len = be32(d + off);
        if (len > n - off - 12) { *why = "chunk length"; free(z); return NULL; }
        const uint8_t *type = d + off + 4, *data = d + off + 8;
        if (crc_bitwise(type, 4 + (size_t)len) != be32(data + len)) { *why = "chunk CRC"; free(z); return NULL; }
        if (!memcmp(type, "IHDR", 4)) {
            if (len != 13 || data[8] != 8 || data[9] != 6 || data[10] || data[11] || data[12]) {
                *why = "IHDR (want 8-bit RGBA, no interlace)"; free(z); return NULL;
            }
            *w = be32(data); *h = be32(data + 4);
            have_ihdr = 1;
        } else if (!memcmp(type, "IDAT", 4)) {
            if (zn + len > zcap) { zcap = (zn + len) * 2; z = (uint8_t *)realloc(z, zcap); }
            memcpy(z + zn, data, len);
            zn += len;
        } else if (!memcmp(type, "IEND", 4)) {
            have_iend = 1;
            off += 12 + len;
            break;
        }
        off += 12 + len;
    }
    if (!have_ihdr || !have_iend || off != n) { *why = "chunk structure"; free(z); return NULL; }
    if (zn < 6 || (z[0] & 15) != 8 || ((z[0] << 8) | z[1]) % 31) { *why = "zlib header"; free(z); return NULL; }
    size_t row = 1 + (size_t)*w * 4, raw_n = row * *h, rn = 0;
    uint8_t *raw = (uint8_t *)malloc(raw_n);
    size_t zp = 2;
    for (;;) {
        if (zp + 5 > zn) { *why = "truncated deflate"; goto fail; }
        uint8_t hdr = z[zp++];
        if ((hdr >> 1) != 0) { *why = "non-stored deflate block"; goto fail; }
        uint32_t L = z[zp] | (uint32_t)z[zp + 1] << 8, NL = z[zp + 2] | (uint32_t)z[zp + 3] << 8;
        zp += 4;
        if ((L ^ 0xFFFF) != NL) { *why = "LEN/NLEN"; goto fail; }
        if (zp + L > zn || rn + L > raw_n) { *why = "stored block overrun"; goto fail; }
        memcpy(raw + rn, z + zp, L);
        rn += L; zp += L;
        if (hdr & 1) break;
    }
    if (rn != raw_n || zp + 4 != zn) { *why = "decompressed size"; goto fail; }
    {
        uint32_t a = 1, b = 0;
        for (size_t i = 0; i < raw_n; i++) { a = (a + raw[i]) % 65521; b = (b + a) % 65521; }
        if (((b << 16) | a) != be32(z + zp)) { *why = "Adler-32"; goto fail; }
    }
    {
        uint32_t *px = (uint32_t *)malloc((size_t)*w * *h * 4);
        uint8_t *out = (uint8_t *)px;
        size_t stride = (size_t)*w * 4;
        for (uint32_t y = 0; y < *h; y++) {
            const uint8_t *s = raw + y * row;
            uint8_t *o = out + y * stride;
            const uint8_t *up = y ? o - stride : NULL;
            if (s[0] > 4) { *why = "filter type"; free(px); goto fail; }
            for (size_t i = 0; i < stride; i++) {
                int a = i >= 4 ? o[i - 4] : 0, b = up ? up[i] : 0, c = (up && i >= 4) ? up[i - 4] : 0;
                int pr = s[0] == 0 ? 0 : s[0] == 1 ? a : s[0] == 2 ? b : s[0] == 3 ? (a + b) / 2 : paeth(a, b, c);
                o[i] = (uint8_t)(s[1 + i] + pr);
            }
        }
        free(raw);
        free(z);
        *why = NULL;
        return px;
    }
fail:
    free(raw);
    free(z);
    return NULL;
}

static uint8_t *slurp(const char *path, size_t *n)
{
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long L = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *b = (uint8_t *)malloc((size_t)L + 1);
    *n = fread(b, 1, (size_t)L, f);
    fclose(f);
    b[*n] = 0;
    return b;
}

static void test_image(uint32_t *px, uint32_t w, uint32_t h)
{
    for (uint32_t y = 0; y < h; y++)
        for (uint32_t x = 0; x < w; x++)
            px[y * w + x] = (x * 7 + y) & 255 | ((x ^ y) & 255) << 8 | ((x * y) & 255) << 16 |
                            (uint32_t)((255 - x) & 255) << 24;
}

static void png_roundtrip(void)
{
    static const uint32_t sizes[][2] = { { 1, 1 }, { 37, 23 }, { 300, 300 }, { 640, 448 } };
    for (size_t t = 0; t < sizeof sizes / sizeof sizes[0]; t++) {
        uint32_t w = sizes[t][0], h = sizes[t][1];
        uint32_t *px = (uint32_t *)malloc((size_t)w * h * 4);
        test_image(px, w, h);
        size_t n;
        uint8_t *png = rg_png_encode(px, w, h, &n);
        CHECK(png != NULL);
        uint32_t dw = 0, dh = 0;
        const char *why;
        uint32_t *back = png_decode(png, n, &dw, &dh, &why);
        if (!back) fprintf(stderr, "decode %ux%u: %s\n", w, h, why);
        CHECK(back != NULL);
        if (back) {
            CHECK_EQ(dw, w);
            CHECK_EQ(dh, h);
            CHECK(memcmp(back, px, (size_t)w * h * 4) == 0);
        }
        free(back);
        free(png);
        free(px);
    }
    /* CRC / Adler reference values (RFC 1950/2083 test vectors) */
    CHECK_EQ(rg_crc32(0, "123456789", 9), 0xCBF43926u);
    CHECK_EQ(rg_adler32(1, "Wikipedia", 9), 0x11E60398u);
    CHECK(rg_png_encode(NULL, 0, 4, &(size_t){0}) == NULL);
}

/* Control: a flipped pixel byte must be rejected (the IDAT CRC catches it).
 * Registered WILL_FAIL: proves the checker is armed. */
static void png_corrupt_control(void)
{
    uint32_t px[16 * 16];
    test_image(px, 16, 16);
    size_t n;
    uint8_t *png = rg_png_encode(px, 16, 16, &n);
    png[n - 12 - 4 - 30] ^= 1;   /* inside the IDAT pixel data */
    uint32_t w, h;
    const char *why;
    uint32_t *back = png_decode(png, n, &w, &h, &why);
    CHECK(back != NULL);   /* expected to fail */
    free(back);
    free(png);
}

static int cmd_pngcheck(int argc, char **argv)
{
    if (argc < 3) return 2;
    size_t n;
    uint8_t *d = slurp(argv[2], &n);
    if (!d) { fprintf(stderr, "cannot read %s\n", argv[2]); return 1; }
    uint32_t w, h;
    const char *why;
    uint32_t *px = png_decode(d, n, &w, &h, &why);
    free(d);
    if (!px) { fprintf(stderr, "%s: invalid PNG: %s\n", argv[2], why); return 1; }
    int rc = 0;
    if (argc >= 5 && (w != (uint32_t)atoi(argv[3]) || h != (uint32_t)atoi(argv[4]))) {
        fprintf(stderr, "%s: size %ux%u, expected %sx%s\n", argv[2], w, h, argv[3], argv[4]);
        rc = 1;
    }
    /* distinct colours: a blank/flat frame would mean nothing was drawn */
    uint32_t distinct = 0, seen[64];
    for (size_t i = 0; i < (size_t)w * h && distinct < 64; i++) {
        uint32_t k;
        for (k = 0; k < distinct && seen[k] != px[i]; k++) {}
        if (k == distinct) seen[distinct++] = px[i];
    }
    if (distinct < 8) { fprintf(stderr, "%s: only %u colours\n", argv[2], distinct); rc = 1; }
    printf("%s: %ux%u PNG ok, >= %u colours\n", argv[2], w, h, distinct);
    free(px);
    return rc;
}

static int cmd_png_write(int argc, char **argv)
{
    if (argc < 3) return 2;
    uint32_t px[37 * 23];
    test_image(px, 37, 23);
    return rg_png_write(argv[2], px, 37, 23) ? 1 : 0;
}

/* ================================================================== pad */
static void pad_report(void)
{
    rg_pad p;
    rg_pad_neutral(&p);
    CHECK_EQ(p.lx, 0x80); CHECK_EQ(p.ly, 0x80); CHECK_EQ(p.rx, 0x80); CHECK_EQ(p.ry, 0x80);
    p.buttons = RG_BTN_CROSS | RG_BTN_START | RG_BTN_L2 | RG_BTN_LEFT;
    p.lx = 1; p.ly = 2; p.rx = 3; p.ry = 4;
    rg_pad_fill_pressure(&p);
    uint8_t r[RG_DS2_REPORT_BYTES];
    CHECK_EQ(rg_pad_ds2_report(&p, r), 20);
    CHECK_EQ(r[0], 0x00);
    CHECK_EQ(r[1], 0x79);
    /* the game's decode: word = 0xFFFF ^ (raw[2] << 8 | raw[3]) */
    CHECK_EQ(0xFFFF ^ ((r[2] << 8) | r[3]), p.buttons);
    CHECK_EQ(r[2], 0x77);    /* ~(0x88) : START (bit 11) and LEFT (bit 15) low */
    CHECK_EQ(r[3], 0xBE);    /* ~(0x41) : CROSS (bit 6) and L2 (bit 0) low */
    CHECK_EQ(r[4], 3); CHECK_EQ(r[5], 4); CHECK_EQ(r[6], 1); CHECK_EQ(r[7], 2);
    for (int i = 0; i < RG_PRS_COUNT; i++) {
        int want = (i == RG_PRS_CROSS || i == RG_PRS_L2 || i == RG_PRS_LEFT) ? 255 : 0;
        CHECK_EQ(r[8 + i], want);
    }
    /* names */
    CHECK_EQ(rg_input_from_name("cross"), 6);
    CHECK_EQ(rg_input_from_name("LY+"), RG_IN_LY_POS);
    CHECK_EQ(rg_input_from_name("nope"), -1);
    for (int i = 0; i < 16; i++) CHECK_EQ(rg_input_from_name(rg_input_name(i)), i);
    CHECK(rg_input_name(RG_IN_COUNT) == NULL);
}

static void input_mapping(void)
{
    rg_input_map m;
    rg_input_map_default(&m);
    static bool keys[SDL_SCANCODE_COUNT];
    rg_pad p;

    rg_input_eval(&m, NULL, 0, NULL, 0, &p);
    CHECK_EQ(p.buttons, 0);
    CHECK_EQ(p.lx, 128); CHECK_EQ(p.ly, 128);

    keys[SDL_SCANCODE_X] = 1;
    keys[SDL_SCANCODE_RETURN] = 1;
    keys[SDL_SCANCODE_UP] = 1;
    keys[SDL_SCANCODE_W] = 1;          /* LY- : up = 0x00 */
    keys[SDL_SCANCODE_D] = 1;          /* LX+ */
    keys[SDL_SCANCODE_J] = 1;          /* RX- and RX+ together cancel */
    keys[SDL_SCANCODE_L] = 1;
    rg_input_eval(&m, keys, SDL_SCANCODE_COUNT, NULL, 0, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS | RG_BTN_START | RG_BTN_UP);
    CHECK_EQ(p.ly, 0);
    CHECK_EQ(p.lx, 255);
    CHECK_EQ(p.rx, 128);
    CHECK_EQ(p.ry, 128);
    CHECK_EQ(p.pressure[RG_PRS_CROSS], 255);
    CHECK_EQ(p.pressure[RG_PRS_UP], 255);
    CHECK_EQ(p.pressure[RG_PRS_CIRCLE], 0);
    /* nkeys bounds the array */
    rg_input_eval(&m, keys, SDL_SCANCODE_X, NULL, 0, &p);
    CHECK_EQ(p.buttons & RG_BTN_CROSS, 0);
    memset(keys, 0, sizeof keys);

    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.button[SDL_GAMEPAD_BUTTON_SOUTH] = 1;
    g.button[SDL_GAMEPAD_BUTTON_DPAD_LEFT] = 1;
    g.axis[SDL_GAMEPAD_AXIS_LEFT_TRIGGER] = 20000;   /* L2 on */
    g.axis[SDL_GAMEPAD_AXIS_RIGHT_TRIGGER] = 5000;   /* R2 below threshold */
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = -32768;
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = 32767;
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 4000;          /* inside the deadzone */
    g.axis[SDL_GAMEPAD_AXIS_RIGHTY] = 20000;         /* (20000-8000)*32767/24767 = 15876 */
    rg_input_eval(&m, NULL, 0, &g, 1, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS | RG_BTN_LEFT | RG_BTN_L2);
    CHECK_EQ(p.lx, 0);
    CHECK_EQ(p.ly, 255);
    CHECK_EQ(p.rx, 128);
    CHECK_EQ(p.ry, 128 + 15876 * 128 / 32767);
    CHECK_EQ(p.pressure[RG_PRS_L2], 255);
    CHECK_EQ(p.pressure[RG_PRS_R2], 0);
    /* two pads merge (OR / strongest deflection) */
    rg_gamepad_snap g2[2];
    memset(g2, 0, sizeof g2);
    g2[1].button[SDL_GAMEPAD_BUTTON_NORTH] = 1;
    g2[1].axis[SDL_GAMEPAD_AXIS_LEFTX] = 32767;
    g2[0].button[SDL_GAMEPAD_BUTTON_START] = 1;
    rg_input_eval(&m, NULL, 0, g2, 2, &p);
    CHECK_EQ(p.buttons, RG_BTN_TRIANGLE | RG_BTN_START);
    CHECK_EQ(p.lx, 255);
    /* keyboard and pad together */
    keys[SDL_SCANCODE_C] = 1;
    rg_input_eval(&m, keys, SDL_SCANCODE_COUNT, &g, 1, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS | RG_BTN_LEFT | RG_BTN_L2 | RG_BTN_CIRCLE);
}

static void input_config(void)
{
    rg_input_map m, d;
    rg_input_map_default(&d);
    rg_input_map_default(&m);
    char err[256] = "";
    const char *cfg =
        "# remap\n"
        "CROSS = key:Space, pad:b   # comment\n"
        "  l2 = axis:lefttrigger+ , key:Left Shift\n"
        "LX- = axis:rightx-\n"
        "SELECT =\n"
        "deadzone = 1000\n"
        "threshold = 30000\n";
    CHECK_EQ(rg_input_map_parse(&m, cfg, err, sizeof err), 0);
    if (err[0]) fprintf(stderr, "err: %s\n", err);
    CHECK_EQ(m.deadzone, 1000);
    CHECK_EQ(m.threshold, 30000);
    static bool keys[SDL_SCANCODE_COUNT];
    rg_pad p;
    keys[SDL_SCANCODE_X] = 1;                     /* old CROSS key: no longer bound */
    rg_input_eval(&m, keys, SDL_SCANCODE_COUNT, NULL, 0, &p);
    CHECK_EQ(p.buttons, 0);
    keys[SDL_SCANCODE_SPACE] = 1;
    keys[SDL_SCANCODE_LSHIFT] = 1;
    keys[SDL_SCANCODE_BACKSPACE] = 1;             /* SELECT cleared */
    rg_input_eval(&m, keys, SDL_SCANCODE_COUNT, NULL, 0, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS | RG_BTN_L2);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.button[SDL_GAMEPAD_BUTTON_EAST] = 1;
    g.axis[SDL_GAMEPAD_AXIS_LEFT_TRIGGER] = 20000;   /* now below threshold 30000 */
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = -32768;
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = -32768;          /* LX- no longer reads leftx */
    rg_input_eval(&m, NULL, 0, &g, 1, &p);
    /* east is now CROSS ("pad:b") and still CIRCLE (its default binding) */
    CHECK_EQ(p.buttons, RG_BTN_CROSS | RG_BTN_CIRCLE);
    CHECK_EQ(p.lx, 0);
    CHECK_EQ(p.rx, 0);                                 /* RX- still default rightx- */

    /* errors carry the line number */
    struct { const char *text, *want; } bad[] = {
        { "FOO = key:X\n", "line 1: unknown input" },
        { "\nCROSS = key:NotAKeyName\n", "line 2: unknown key" },
        { "CROSS = axis:leftx\n", "line 1: axis" },
        { "CROSS = pad:nope\n", "line 1: unknown gamepad button" },
        { "CROSS = key:A, key:B, key:C, key:D, key:E\n", "line 1: more than 4" },
        { "CROSS key:A\n", "line 1: expected" },
        { "CROSS = joy:1\n", "line 1: unknown binding kind" },
        { "deadzone = 40000\n", "line 1: deadzone" },
    };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; i++) {
        rg_input_map t;
        rg_input_map_default(&t);
        err[0] = 0;
        CHECK_EQ(rg_input_map_parse(&t, bad[i].text, err, sizeof err), -1);
        if (!strstr(err, bad[i].want)) {
            fprintf(stderr, "config error for %s: got '%s', want '%s'\n", bad[i].text, err, bad[i].want);
            g_fail++;
        }
    }

    /* format -> parse round trip (from a default map, every line replaces) */
    static char text[16384];
    size_t n = rg_input_map_format(&m, text, sizeof text);
    CHECK(n > 0 && n < sizeof text);
    rg_input_map back;
    rg_input_map_default(&back);
    CHECK_EQ(rg_input_map_parse(&back, text, err, sizeof err), 0);
    CHECK(memcmp(&back, &m, sizeof m) == 0);
    n = rg_input_map_format(&d, text, sizeof text);
    rg_input_map_default(&back);
    back.key[0][0] = 99;
    CHECK_EQ(rg_input_map_parse(&back, text, err, sizeof err), 0);
    CHECK(memcmp(&back, &d, sizeof d) == 0);
    /* truncation keeps a NUL and reports the full length */
    char small[16];
    CHECK_EQ(rg_input_map_format(&d, small, sizeof small), n);
    CHECK_EQ(strlen(small), sizeof small - 1);
}

/* ================================================================ script */
static const char *k_example =
    "# SPDX-License-Identifier: CC0-1.0\n"
    "100 110 START\n"
    "200 210 CROSS\n"
    "260 262 DOWN+CROSS\n";

static void input_script(void)
{
    rg_input_script s;
    char err[256] = "";
    CHECK_EQ(rg_input_script_parse(&s, k_example, "ex", err, sizeof err), 0);
    CHECK_EQ(s.count, 32636);
    CHECK_EQ(s.span, 263);
    CHECK_EQ(rg_input_script_word(&s, 99), 0);
    CHECK_EQ(rg_input_script_word(&s, 100), RG_BTN_START);
    CHECK_EQ(rg_input_script_word(&s, 110), RG_BTN_START);
    CHECK_EQ(rg_input_script_word(&s, 111), 0);
    CHECK_EQ(rg_input_script_word(&s, 205), RG_BTN_CROSS);
    CHECK_EQ(rg_input_script_word(&s, 261), RG_BTN_DOWN | RG_BTN_CROSS);
    CHECK_EQ(rg_input_script_word(&s, 40000), 0);
    rg_pad p;
    rg_input_script_pad(&s, 261, &p);
    CHECK_EQ(p.buttons, RG_BTN_DOWN | RG_BTN_CROSS);
    CHECK_EQ(p.lx, 128);
    CHECK_EQ(p.pressure[RG_PRS_DOWN], 255);
    CHECK_EQ(p.pressure[RG_PRS_CROSS], 255);
    CHECK_EQ(p.pressure[RG_PRS_UP], 0);
    rg_input_script_free(&s);

    /* grammar: single-VBlank form, hex/octal/binary/underscores, case, OR of
     * overlaps, trailing comments, extra tokens ignored (as input.py) */
    const char *t =
        "5 cross+Start   # trailing\n"
        "0x10 0o21 l1\n"
        "0b10001 1_8 R1 extra tokens\n"
        "\n   # only a comment\n"
        "0 0 SELECT\n"
        "7 3 TRIANGLE\n";              /* empty range, but extends the span */
    CHECK_EQ(rg_input_script_parse(&s, t, "t", err, sizeof err), 0);
    CHECK_EQ(rg_input_script_word(&s, 5), RG_BTN_CROSS | RG_BTN_START);
    CHECK_EQ(rg_input_script_word(&s, 16), RG_BTN_L1);
    CHECK_EQ(rg_input_script_word(&s, 17), RG_BTN_L1 | RG_BTN_R1);
    CHECK_EQ(rg_input_script_word(&s, 18), RG_BTN_R1);
    CHECK_EQ(rg_input_script_word(&s, 0), RG_BTN_SELECT);
    CHECK_EQ(rg_input_script_word(&s, 4), 0);
    CHECK_EQ(s.span, 19);
    rg_input_script_free(&s);

    /* the table limit: last index MAX-1 is fine, MAX is not */
    char buf[64];
    snprintf(buf, sizeof buf, "%u START\n", RG_SCRIPT_MAX_ENTRIES - 1);
    CHECK_EQ(rg_input_script_parse(&s, buf, "t", err, sizeof err), 0);
    CHECK_EQ(rg_input_script_word(&s, RG_SCRIPT_MAX_ENTRIES - 1), RG_BTN_START);
    rg_input_script_free(&s);
    snprintf(buf, sizeof buf, "1 %u START\n", RG_SCRIPT_MAX_ENTRIES);
    CHECK_EQ(rg_input_script_parse(&s, buf, "t", err, sizeof err), -1);
    CHECK(strstr(err, "too long") != NULL);

    struct { const char *text, *want; } bad[] = {
        { "1 2 JUMP\n", "t:1: unknown button 'JUMP'" },
        { "\n1 2 CROSS+\n", "t:2: unknown button ''" },
        { "010 CROSS\n", "t:1: bad integer" },
        { "0x CROSS\n", "t:1: bad integer" },
        { "1_ CROSS\n", "t:1: bad integer" },
        { "-1 CROSS\n", "t:1: negative" },
        { "12\n", "t:1: expected" },
    };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; i++) {
        err[0] = 0;
        CHECK_EQ(rg_input_script_parse(&s, bad[i].text, "t", err, sizeof err), -1);
        CHECK(s.words == NULL);
        if (!strstr(err, bad[i].want)) {
            fprintf(stderr, "script error for %s: got '%s', want '%s'\n", bad[i].text, err, bad[i].want);
            g_fail++;
        }
    }
    CHECK_EQ(rg_input_script_load(&s, "no/such/file.txt", err, sizeof err), -1);

    /* the stick channel (docs/INPUT.md "Scripted sticks"): comments to the
     * button table, later lines override, right stick centred when omitted */
    const char *st =
        "#!stick 1 0\n"
        "10 12 CROSS\n"
        "#!stick 10 20 128 0\n"
        "#!stick 15 16 255 255 0 0x40   # with the right stick\n";
    CHECK_EQ(rg_input_script_parse(&s, st, "st", err, sizeof err), 0);
    CHECK(s.stick != NULL);
    CHECK_EQ(s.span, 13);
    rg_input_script_pad(&s, 9, &p);
    CHECK_EQ(p.lx, 128); CHECK_EQ(p.ly, 128);
    rg_input_script_pad(&s, 11, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS);
    CHECK_EQ(p.lx, 128); CHECK_EQ(p.ly, 0); CHECK_EQ(p.rx, 128);
    rg_input_script_pad(&s, 15, &p);
    CHECK_EQ(p.lx, 255); CHECK_EQ(p.ly, 255); CHECK_EQ(p.rx, 0); CHECK_EQ(p.ry, 0x40);
    rg_input_script_pad(&s, 17, &p);
    CHECK_EQ(p.lx, 128); CHECK_EQ(p.ly, 0); CHECK_EQ(p.rx, 128);
    rg_input_script_pad(&s, 21, &p);
    CHECK_EQ(p.ly, 128);
    rg_input_script_free(&s);
    CHECK_EQ(rg_input_script_parse(&s, "#!stick 1 2 3 4\n", "t", err, sizeof err), -1);
    CHECK(strstr(err, "must come before") != NULL);
    CHECK_EQ(rg_input_script_parse(&s, "#!stick 1 0\n#!stick 1 2 300 4\n", "t", err, sizeof err), -1);
    CHECK(strstr(err, "out of range") != NULL);
    CHECK_EQ(rg_input_script_parse(&s, k_example, "ex", err, sizeof err), 0);
    CHECK(s.stick == NULL);
    rg_input_script_free(&s);
}

static uint64_t fnv(const void *d, size_t n)
{
    const uint8_t *p = (const uint8_t *)d;
    uint64_t h = 0xCBF29CE484222325ull;
    while (n--) { h ^= *p++; h *= 0x100000001B3ull; }
    return h;
}

/* Replaying the same script gives the same pad stream, through the host
 * (headless) exactly as through the bare table; live input never leaks in. */
static void script_determinism(void)
{
    uint64_t hs[2];
    for (int run = 0; run < 2; run++) {
        rg_input_script s;
        char err[256];
        CHECK_EQ(rg_input_script_parse(&s, k_example, "ex", err, sizeof err), 0);
        rg_host_config c;
        rg_host_config_default(&c);
        c.headless = 1;
        rg_host *h = rg_host_create(&c);
        CHECK(h != NULL);
        rg_host_set_input_script(h, &s);
        uint64_t acc = 0xCBF29CE484222325ull;
        for (uint32_t v = 0; v < 400; v++) {
            rg_pad p0, p1;
            uint8_t r[RG_DS2_REPORT_BYTES * 2];
            rg_host_read_pad(h, 0, v, &p0);
            rg_host_read_pad(h, 1, v, &p1);
            CHECK_EQ(p0.buttons, rg_input_script_word(&s, v));
            CHECK_EQ(p1.buttons, 0);
            rg_pad_ds2_report(&p0, r);
            rg_pad_ds2_report(&p1, r + RG_DS2_REPORT_BYTES);
            acc ^= fnv(r, sizeof r);
            acc *= 0x100000001B3ull;
        }
        hs[run] = acc;
        size_t need = rg_input_script_blob(&s, NULL, 0);
        CHECK_EQ(need, 4 + 2 * 32636);
        uint8_t *blob = (uint8_t *)malloc(need);
        CHECK_EQ(rg_input_script_blob(&s, blob, need), need);
        CHECK_EQ(blob[0] | blob[1] << 8 | blob[2] << 16 | blob[3] << 24, 32636);
        CHECK_EQ(blob[4 + 2 * 100] | blob[5 + 2 * 100] << 8, RG_BTN_START);
        free(blob);
        /* without a script, a headless host reads a neutral pad */
        rg_host_set_input_script(h, NULL);
        rg_pad p;
        rg_host_read_pad(h, 0, 205, &p);
        CHECK_EQ(p.buttons, 0);
        CHECK_EQ(p.lx, 128);
        rg_host_destroy(h);
        rg_input_script_free(&s);
    }
    CHECK_EQ(hs[0], hs[1]);
}

static int cmd_script_dump(int argc, char **argv)
{
    if (argc < 4) return 2;
    rg_input_script s;
    char err[512];
    if (rg_input_script_load(&s, argv[2], err, sizeof err)) { fprintf(stderr, "%s\n", err); return 1; }
    size_t n = rg_input_script_blob(&s, NULL, 0);
    uint8_t *b = (uint8_t *)malloc(n);
    rg_input_script_blob(&s, b, n);
    FILE *f = fopen(argv[3], "wb");
    int ok = f && fwrite(b, 1, n, f) == n;
    if (f) fclose(f);
    free(b);
    rg_input_script_free(&s);
    return ok ? 0 : 1;
}

/* =============================================================== scaling */
static void check_rect(int ww, int wh, int sw, int sh, int an, int ad, rg_scale_mode m,
                       int x, int y, int w, int h, int factor, int line)
{
    int f = -1;
    rg_rect r = rg_fit_rect(ww, wh, sw, sh, an, ad, m, &f);
    if (r.x != x || r.y != y || r.w != w || r.h != h || f != factor) {
        fprintf(stderr, "line %d: fit(%dx%d, %s) = %d,%d %dx%d f%d; want %d,%d %dx%d f%d\n",
                line, ww, wh, rg_scale_name(m), r.x, r.y, r.w, r.h, f, x, y, w, h, factor);
        g_fail++;
    }
}
#define RECT(...) check_rect(__VA_ARGS__, __LINE__)

static void scaling(void)
{
    /* 4:3 linear fit */
    RECT(1280, 960, 640, 448, 4, 3, RG_SCALE_LINEAR, 0, 0, 1280, 960, 0);
    RECT(1920, 1080, 640, 448, 4, 3, RG_SCALE_LINEAR, 240, 0, 1440, 1080, 0);
    RECT(1000, 2000, 640, 448, 4, 3, RG_SCALE_NEAREST, 0, 625, 1000, 750, 0);
    RECT(641, 481, 640, 448, 4, 3, RG_SCALE_LINEAR, 0, 0, 641, 481, 0);    /* 480.75 -> 481 */
    /* integer: height = n * 448, width = round(h * 4/3) */
    RECT(1920, 1080, 640, 448, 4, 3, RG_SCALE_INTEGER, 362, 92, 1195, 896, 2);
    RECT(3840, 2160, 640, 448, 4, 3, RG_SCALE_INTEGER, 725, 184, 2389, 1792, 4);
    RECT(800, 600, 640, 448, 4, 3, RG_SCALE_INTEGER, 101, 76, 597, 448, 1);
    RECT(600, 1000, 640, 448, 4, 3, RG_SCALE_INTEGER, 1, 276, 597, 448, 1);  /* 2x too wide */
    RECT(500, 400, 640, 448, 4, 3, RG_SCALE_INTEGER, 0, 12, 500, 375, 0);    /* fallback */
    /* field-height source (224 lines) at 4:3 */
    RECT(1920, 1080, 640, 224, 4, 3, RG_SCALE_INTEGER, 362, 92, 1195, 896, 4);
    /* stretch, square pixels, degenerate */
    RECT(1920, 1080, 640, 448, 4, 3, RG_SCALE_STRETCH, 0, 0, 1920, 1080, 0);
    RECT(1280, 960, 640, 448, 0, 0, RG_SCALE_LINEAR, 0, 32, 1280, 896, 0);
    RECT(0, 960, 640, 448, 4, 3, RG_SCALE_LINEAR, 0, 0, 0, 0, 0);
    RECT(1280, 960, 0, 448, 4, 3, RG_SCALE_LINEAR, 0, 0, 0, 0, 0);
    RECT(1, 1, 640, 448, 4, 3, RG_SCALE_LINEAR, 0, 0, 1, 1, 0);
    /* property sweep: inside the window, centred, aspect within 1 px */
    for (int ww = 50; ww <= 4000; ww += 37)
        for (int wh = 50; wh <= 2500; wh += 41)
            for (int m = 0; m < 3; m++) {
                int f;
                rg_rect r = rg_fit_rect(ww, wh, 640, 448, 4, 3, (rg_scale_mode)m, &f);
                CHECK(r.x >= 0 && r.y >= 0 && r.x + r.w <= ww && r.y + r.h <= wh);
                CHECK(abs(2 * r.x + r.w - ww) <= 1 && abs(2 * r.y + r.h - wh) <= 1);
                CHECK(llabs((long long)r.w * 3 - (long long)r.h * 4) <= 4);
                CHECK(r.w == ww || r.h == wh || (m == RG_SCALE_INTEGER && f > 0));
                if (m == RG_SCALE_INTEGER && f > 0) CHECK_EQ(r.h, 448 * f);
            }
    for (int m = 0; m < 4; m++) CHECK_EQ(rg_scale_from_name(rg_scale_name((rg_scale_mode)m)), m);
    CHECK_EQ(rg_scale_from_name("bogus"), -1);
}

/* ================================================================ pacing */
typedef struct fake_clock { uint64_t now; uint64_t calls; } fake_clock;
static uint64_t fk_now(void *u) { return ((fake_clock *)u)->now; }
static void fk_sleep(void *u, uint64_t ns) { ((fake_clock *)u)->now += ns; ((fake_clock *)u)->calls++; }

static void pacing(void)
{
    ps2k_pacing_fn fn = rg_pacer_hook;   /* compile-time signature check */
    (void)fn;
    CHECK_EQ(rg_cycles_to_ns(RG_BUSCLK), 1000000000ull);
    CHECK_EQ(rg_cycles_to_ns(147456), 1000000ull);
    CHECK_EQ(rg_cycles_to_ns(1), 6);
    CHECK_EQ(rg_cycles_to_ns(4000000000000000ull), 27126736111111111ull); /* no overflow */
    CHECK_EQ(rg_field_cycles(0), 0);
    CHECK_EQ(rg_field_cycles(1), 2460060);      /* PCSX2: BUSCLK/59.94 */
    CHECK_EQ(rg_field_cycles(5), 12300300);
    CHECK_EQ(rg_field_cycles(60000), 147603600000ull);
    /* The kernel's field (PS2K_FIELD_SUB) is 2,460,060 cycles, PCSX2's value
     * (4,920,120 EE cycles per field in tools/trace): 60000 fields take
     * 1001.000977 s.  The pacer follows the kernel's constant. */
    CHECK_EQ(rg_cycles_to_ns(rg_field_cycles(60000)), 1001000976562ull);
    for (uint64_t k = 0; k < 100000; k += 7)
        CHECK_EQ(rg_field_cycles(k), k * PS2K_FIELD_SUB / PS2K_SUB);
    CHECK_EQ(RG_BUSCLK, PS2K_BUSCLK);

    /* throttled, no work: wall time tracks virtual time exactly */
    fake_clock fc = { 5000000000ull, 0 };
    rg_pacer p;
    rg_pacer_init(&p, 1);
    p.now_ns = fk_now; p.sleep_ns = fk_sleep; p.clock_user = &fc;
    for (uint64_t k = 0; k < 600; k++) rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &p);
    CHECK_EQ(fc.now - 5000000000ull, rg_cycles_to_ns(rg_field_cycles(600)));   /* 10.01 s */
    CHECK_EQ(p.resyncs, 0);
    /* with 5 ms of work per field: still on schedule; sleeps shrink */
    uint64_t t0 = fc.now;
    rg_pacer_reset(&p);
    for (uint64_t k = 0; k < 600; k++) {
        fc.now += 5000000;
        rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &p);
    }
    /* anchor taken after the first 5 ms of work */
    CHECK_EQ(fc.now - t0, 5000000 + rg_cycles_to_ns(rg_field_cycles(600)));
    /* a 400 ms stall: re-anchor once, then keep the 59.94 Hz cadence */
    fc.now += 400000000;
    rg_pacer_hook(rg_field_cycles(600), rg_field_cycles(601), &p);
    CHECK_EQ(p.resyncs, 1);
    uint64_t t1 = fc.now;
    for (uint64_t k = 601; k < 661; k++) rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &p);
    CHECK_EQ(fc.now - t1, rg_cycles_to_ns(rg_field_cycles(661) - rg_field_cycles(601)));
    /* a 100 ms stall is below max_lag: it is caught up (no resync) */
    fc.now += 100000000;
    uint64_t sl = fc.calls;
    for (uint64_t k = 661; k < 680; k++) rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &p);
    CHECK_EQ(p.resyncs, 1);
    CHECK(fc.calls - sl < 19);    /* the first few fields ran without sleeping */
    /* virtual time going backwards (new kernel run) re-anchors silently */
    uint64_t t2 = fc.now;
    rg_pacer_hook(0, rg_field_cycles(1), &p);
    CHECK_EQ(fc.now - t2, rg_cycles_to_ns(rg_field_cycles(1)));

    /* unthrottled: never sleeps, never reads the clock */
    fake_clock fz = { 0, 0 };
    rg_pacer u;
    rg_pacer_init(&u, 0);
    u.now_ns = fk_now; u.sleep_ns = fk_sleep; u.clock_user = &fz;
    for (uint64_t k = 0; k < 1000; k++) rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &u);
    CHECK_EQ(fz.calls, 0);
    CHECK_EQ(fz.now, 0);

    /* the real clock: 6 fields throttled take >= 100 ms (loose upper bound) */
    rg_pacer r;
    rg_pacer_init(&r, 1);
    uint64_t a = SDL_GetTicksNS();
    for (uint64_t k = 0; k < 6; k++) rg_pacer_hook(rg_field_cycles(k), rg_field_cycles(k + 1), &r);
    uint64_t el = SDL_GetTicksNS() - a;
    CHECK(el >= 100000000ull - 1000000ull);
    CHECK(el < 1000000000ull);
}

/* ============================================================ audio_reg
 * The output-queue regulator against a simulated device (docs/SOUND.md
 * "Load-screen audio"): the game pushes one field (800/801 frames) when each
 * field ends, the device pulls 480-frame periods on its own clock. */
typedef struct audio_sim {
    double q;                  /* frames queued */
    double t_dev;              /* next device pull, ms */
    double dev_rate;           /* device frames per ms (48 = nominal) */
    double wall, anchor;       /* pacer model, ms */
    uint64_t base, k;          /* anchor field, next field */
    uint64_t starves, pulls;   /* device pulls that found the queue short */
    uint64_t episodes;         /* fields whose push followed a starve */
    uint32_t starve_frames;    /* frames the device could not get since the last push */
    int starved_since_push, prev_starved;
    rg_audio_reg reg;
} audio_sim;

static void sim_init(audio_sim *s, uint32_t target, double dev_rate)
{
    memset(s, 0, sizeof *s);
    s->dev_rate = dev_rate;
    rg_audio_reg_init(&s->reg, target);
}

/* advance the device to wall time `t` ms */
static void sim_dev(audio_sim *s, double t)
{
    while (s->t_dev <= t) {
        double want = 480.0 * s->reg.ratio;
        if (s->reg.primed || !s->reg.target) {
            if (s->q < want) {
                if (s->pulls > 0 && (s->reg.primed || s->reg.pushes)) {
                    s->starves++;
                    s->starved_since_push = 1;
                    s->starve_frames += (uint32_t)(want - s->q);
                }
                s->q = 0;
            } else {
                s->q -= want;
            }
        }
        s->pulls++;
        s->t_dev += 480.0 / s->dev_rate;
    }
}

/* `fields` more fields; field k nominally ends at k * 16.6833 ms, plus
 * `late(k)` ms of extra wall time.  The pacer catches lateness up unless it
 * exceeds 250 ms; then it re-anchors and the regulator is told. */
static void sim_run(audio_sim *s, uint64_t fields, double (*late)(uint64_t), double *maxq_ms)
{
    const double field_ms = 1001.0 / 60.0;
    *maxq_ms = 0;
    for (uint64_t n = 0; n < fields; n++, s->k++) {
        uint64_t k = s->k;
        double due = s->anchor + (double)(k + 1 - s->base) * field_ms;
        double end = (s->wall > due ? s->wall : due) + late(k);
        if (end - due > 250.0) {   /* pacer resync */
            s->anchor = end - field_ms;
            s->base = k;
            rg_audio_reg_resync(&s->reg);
        }
        sim_dev(s, end);
        s->wall = end;
        uint32_t frames = (uint32_t)(48000ull * 1001 * (k + 1) / 60000 - 48000ull * 1001 * k / 60000);
        uint32_t pad, drop;
        s->episodes += s->starved_since_push && !s->prev_starved;
        s->prev_starved = s->starved_since_push;
        s->reg.starve_in = s->starve_frames;
        double due2 = s->anchor + (double)(k + 1 - s->base) * field_ms; /* (after a re-anchor) */
        s->reg.owed_in = end > due2 ? (uint32_t)((end - due2) / field_ms) * 800u : 0u; /* catch-up ahead */
        rg_audio_reg_push(&s->reg, (uint32_t)(s->q + 0.5), s->starved_since_push, frames, &pad, &drop);
        s->starved_since_push = 0;
        s->starve_frames = 0;
        s->q += pad + (frames - drop);
        if (k > 120 && s->q / 48.0 > *maxq_ms) *maxq_ms = s->q / 48.0;
    }
}

static double late_none(uint64_t k) { (void)k; return 0.0; }
/* load-screen-like: every 7th field ends 25 ms late (a CD read + work) */
static double late_load(uint64_t k) { return k % 7 == 3 ? 25.0 : 0.0; }
/* jitter: every 3rd field 12 ms late */
static double late_jitter(uint64_t k) { return k % 3 == 1 ? 12.0 : 0.0; }
/* one 150 ms hitch (caught up), then one 400 ms hitch (re-anchor) */
static double late_hitch(uint64_t k) { return k == 600 ? 150.0 : k == 1500 ? 400.0 : 0.0; }
/* a loading loop: a 300 ms hitch (re-anchor) every 10 s, 25 ms late every 7th field */
static double late_loading(uint64_t k) { return k % 600 == 300 ? 300.0 : late_load(k); }

/* machine-load-like: a 120 ms game-thread stall every 5 s (caught up), for the first minute */
static double late_stall(uint64_t k) { return k < 3600 && k % 300 == 150 ? 120.0 : 0.0; }

static void audio_reg(void)
{
    /* the decisions, one push at a time */
    rg_audio_reg r;
    uint32_t pad, drop;
    rg_audio_reg_init(&r, 0);
    rg_audio_reg_push(&r, 0, 1, 801, &pad, &drop);
    CHECK_EQ(pad, 0);
    CHECK_EQ(drop, 0);
    CHECK(r.ratio == 1.0);                          /* off: pass-through */
    rg_audio_reg_init(&r, 3072);
    rg_audio_reg_push(&r, 0, 0, 801, &pad, &drop);
    CHECK_EQ(pad, 3072);                            /* first push: prime */
    CHECK_EQ(drop, 0);
    rg_audio_reg_push(&r, 3072, 0, 800, &pad, &drop);
    CHECK_EQ(pad, 0);                               /* on target: nothing */
    CHECK_EQ(drop, 0);
    rg_audio_reg_push(&r, 2000, 1, 800, &pad, &drop);
    CHECK_EQ(pad, 0);                               /* starved, cushion > half */
    rg_audio_reg_push(&r, 100, 1, 800, &pad, &drop);
    CHECK_EQ(pad, 2972);                            /* starved and short: refill */
    rg_audio_reg_push(&r, 1000, 0, 800, &pad, &drop);
    CHECK_EQ(pad, 0);                               /* short, not starved */
    rg_audio_reg_resync(&r);
    rg_audio_reg_push(&r, 1000, 0, 800, &pad, &drop);
    CHECK_EQ(pad, 2072);                            /* re-anchor and short: refill */
    rg_audio_reg_push(&r, 3072 + 1602 + 1, 0, 800, &pad, &drop);
    CHECK_EQ(drop, 800);                            /* far over: drop */
    rg_audio_reg_push(&r, 3072 + 700, 0, 801, &pad, &drop);
    CHECK_EQ(drop, 0);                              /* within two fields: rate trim only */
    rg_audio_reg_push(&r, 3072 + 1700, 0, 801, &pad, &drop);
    CHECK_EQ(drop, 801);
    CHECK(r.ratio > 1.0 && r.ratio <= 1.0 + RG_AUDIO_RATIO_MAX + 1e-12);
    for (int i = 0; i < 1000; i++) rg_audio_reg_push(&r, 3072 / 2, 0, 800, &pad, &drop);
    CHECK(r.ratio < 1.0 && r.ratio >= 1.0 - RG_AUDIO_RATIO_MAX - 1e-12);
    CHECK_EQ(r.primes, 3);
    CHECK_EQ(r.drops, 2);

    /* de-click: starts at `from`, ends at the signal, monotone across a step */
    {
        int16_t b[2 * RG_AUDIO_DECLICK_FRAMES], from[2] = {8000, -8000};
        for (int i = 0; i < 2 * RG_AUDIO_DECLICK_FRAMES; i++) b[i] = (i & 1) ? 2000 : -2000;
        rg_audio_declick(b, RG_AUDIO_DECLICK_FRAMES, from);
        CHECK_EQ(b[0], 8000);
        CHECK_EQ(b[1], -8000);
        int mono = 1;
        for (int i = 1; i < RG_AUDIO_DECLICK_FRAMES; i++)
            mono &= b[2 * i] <= b[2 * i - 2] && b[2 * i + 1] >= b[2 * i - 1];
        CHECK(mono);
        CHECK(b[2 * RG_AUDIO_DECLICK_FRAMES - 2] - (-2000) < 200); /* within one step of the signal */
        int16_t z[2 * 8] = {0};
        rg_audio_declick(z, 8, from);                      /* zeros: a fade to silence */
        CHECK_EQ(z[0], 8000);
        CHECK(z[14] > 0 && z[14] <= 1000);
    }

    double maxq;
    const uint32_t tgt = RG_AUDIO_LATENCY_DEFAULT_MS * 48;
    audio_sim s;
    /* off (the old behaviour): every re-anchor leaves no cushion, and each
     * later field that ends late starves the device again until starving
     * has rebuilt it */
    sim_init(&s, 0, 48.0);
    sim_run(&s, 3600, late_loading, &maxq);
    CHECK(s.episodes >= 6 * 3);
    /* default target: one starve per re-anchor (the hitch itself), none from
     * the late fields */
    sim_init(&s, tgt, 48.0);
    sim_run(&s, 3600, late_loading, &maxq);
    CHECK_EQ(s.episodes, 6);
    CHECK(s.reg.primes >= 1 + 6);
    sim_init(&s, tgt, 48.0);
    sim_run(&s, 3600, late_load, &maxq);
    CHECK_EQ(s.starves, 0);
    CHECK(maxq < RG_AUDIO_LATENCY_DEFAULT_MS + 17.0 + 26.0);
    sim_init(&s, tgt, 48.0);
    sim_run(&s, 3600, late_jitter, &maxq);
    CHECK_EQ(s.starves, 0);

    /* clock drift: device 0.3 % fast / slow for 30 simulated minutes: the
     * rate trim holds the queue; no starve, no drop */
    for (int sgn = -1; sgn <= 1; sgn += 2) {
        sim_init(&s, tgt, 48.0 * (1.0 + sgn * 0.003));
        sim_run(&s, 108000, late_none, &maxq);
        CHECK_EQ(s.starves, 0);
        CHECK_EQ(s.reg.drops, 0);
        CHECK(maxq < RG_AUDIO_LATENCY_DEFAULT_MS + 17.0 + 30.0);
        CHECK(fabs(s.reg.ratio - (1.0 - sgn * 0.003)) < 0.0005);
    }

    /* hitches: 150 ms (the pacer catches up) and 400 ms (re-anchor).  Each
     * is one starve episode (that gap is real); afterwards the queue is back
     * near the target and nothing starves. */
    sim_init(&s, tgt, 48.0);
    sim_run(&s, 1400, late_hitch, &maxq);
    CHECK_EQ(s.episodes, 1);
    uint64_t st1 = s.starves;
    sim_run(&s, 600, late_none, &maxq);
    CHECK_EQ(s.starves, st1);
    CHECK(s.q / 48.0 < RG_AUDIO_LATENCY_DEFAULT_MS + 17.0 + 10.0);
    sim_init(&s, tgt, 48.0);
    sim_run(&s, 1700, late_hitch, &maxq);
    CHECK_EQ(s.episodes, 2);
    CHECK(s.reg.primes >= 2);                      /* the first prime + the re-anchor */
    uint64_t st2 = s.starves;
    sim_run(&s, 600, late_none, &maxq);
    CHECK_EQ(s.starves, st2);
    CHECK(s.q / 48.0 > RG_AUDIO_LATENCY_DEFAULT_MS * 0.5);
    CHECK(s.q / 48.0 < RG_AUDIO_LATENCY_DEFAULT_MS + 17.0 + 10.0);

    /* adaptive cushion (docs/NATIVE-THREADS.md "3h"): repeated 120 ms stalls.  A fixed 64 ms
     * cushion starves at every one; the adaptive one after the first only, then decays back
     * to the base once the stalls stop.  A 400 ms stall (its starve longer than the cap) does not grow it. */
    sim_init(&s, tgt, 48.0);
    sim_run(&s, 3600, late_stall, &maxq);
    uint64_t fixed_ep = s.episodes;
    CHECK(fixed_ep >= 11);
    sim_init(&s, tgt, 48.0);
    rg_audio_reg_adapt(&s.reg, 192 * 48);
    sim_run(&s, 3600, late_stall, &maxq);
    CHECK(s.episodes <= 2);
    CHECK(s.reg.grows >= 1);
    CHECK(s.reg.target > tgt && s.reg.target <= 192 * 48);
    if (maxq >= 192.0 + 17.0 + 60.0) fprintf(stderr, "adaptive: max queue %.1f ms\n", maxq);
    CHECK(maxq < 192.0 + 17.0 + 60.0);  /* cap + one field + half a 120 ms catch-up */
    sim_run(&s, 7200, late_none, &maxq);          /* two quiet minutes */
    CHECK_EQ(s.reg.target, tgt);
    CHECK(s.reg.shrinks >= 1);
    CHECK(s.q / 48.0 < RG_AUDIO_LATENCY_DEFAULT_MS + 17.0 + 10.0);
    sim_init(&s, tgt, 48.0);
    rg_audio_reg_adapt(&s.reg, 192 * 48);
    sim_run(&s, 1700, late_hitch, &maxq);
    CHECK_EQ(s.episodes, 2);
    CHECK(s.reg.target <= tgt + 150 * 48 * 5 / 4 + 480);   /* 150 ms: grown; 400 ms: not */
    /* owed phases: the refill after a starve leaves room for half of them */
    {
        rg_audio_reg r;
        uint32_t pad, drop;
        rg_audio_reg_init(&r, 3072);
        rg_audio_reg_push(&r, 0, 0, 800, &pad, &drop);
        r.owed_in = 3200;
        rg_audio_reg_push(&r, 100, 1, 800, &pad, &drop);
        CHECK_EQ(pad, 3072 - 100 - 1600);
        rg_audio_reg_push(&r, 100, 1, 800, &pad, &drop);
        CHECK_EQ(pad, 2972);                       /* owed_in is per push */
    }
}

/* ============================================================ widescreen
 * docs/WIDESCREEN.md: the canvas + content fit, the presented-image
 * resampler, the stage 0 policy (src/settings/rg_aspect.h) and the host's
 * aspect state.  ctest -L wide */
static void check_crect(int ww, int wh, int an, int ad, int cn, int cd, rg_scale_mode m,
                        int x, int y, int w, int h, int factor, int line)
{
    int f = -1;
    rg_rect r = rg_fit_rect_content(ww, wh, 512, 448, an, ad, cn, cd, m, &f);
    if (r.x != x || r.y != y || r.w != w || r.h != h || f != factor) {
        fprintf(stderr, "line %d: fitc(%dx%d %d:%d in %d:%d, %s) = %d,%d %dx%d f%d; want %d,%d %dx%d f%d\n",
                line, ww, wh, cn, cd, an, ad, rg_scale_name(m), r.x, r.y, r.w, r.h, f, x, y, w, h,
                factor);
        g_fail++;
    }
}
#define CRECT(...) check_crect(__VA_ARGS__, __LINE__)

static void wide_fit(void)
{
    /* the 16:9 canvas */
    CRECT(1280, 720, 16, 9, 0, 0, RG_SCALE_LINEAR, 0, 0, 1280, 720, 0);
    CRECT(1280, 960, 16, 9, 16, 9, RG_SCALE_LINEAR, 0, 120, 1280, 720, 0);
    CRECT(1920, 1080, 16, 9, 0, 0, RG_SCALE_INTEGER, 163, 92, 1593, 896, 2);
    /* 4:3 pillarboxed in it: same height, 3/4 of the width */
    CRECT(1280, 720, 16, 9, 4, 3, RG_SCALE_LINEAR, 160, 0, 960, 720, 0);
    CRECT(1280, 960, 16, 9, 4, 3, RG_SCALE_NEAREST, 160, 120, 960, 720, 0);
    /* integer: the same rectangle as a plain 4:3 integer fit (362,92 1195x896) */
    CRECT(1920, 1080, 16, 9, 4, 3, RG_SCALE_INTEGER, 362, 92, 1195, 896, 2);
    /* stretch: the proportion of the stretched canvas */
    CRECT(1280, 1024, 16, 9, 4, 3, RG_SCALE_STRETCH, 160, 0, 960, 1024, 0);
    /* a wider frame in a narrower canvas is letterboxed */
    CRECT(1280, 960, 4, 3, 16, 9, RG_SCALE_LINEAR, 0, 120, 1280, 720, 0);
    /* degenerate */
    CRECT(0, 720, 16, 9, 4, 3, RG_SCALE_LINEAR, 0, 0, 0, 0, 0);
    /* 4:3 and "content = canvas" are rg_fit_rect exactly; pillarboxed content
     * lies inside the canvas, centred, at 4:3 within a pixel */
    for (int ww = 50; ww <= 4000; ww += 53)
        for (int wh = 50; wh <= 2500; wh += 47)
            for (int m = 0; m < 4; m++) {
                int f0, f1, f2;
                rg_rect a = rg_fit_rect(ww, wh, 512, 448, 4, 3, (rg_scale_mode)m, &f0);
                rg_rect b = rg_fit_rect_content(ww, wh, 512, 448, 4, 3, 4, 3, (rg_scale_mode)m, &f1);
                rg_rect b0 = rg_fit_rect_content(ww, wh, 512, 448, 4, 3, 0, 0, (rg_scale_mode)m, NULL);
                CHECK(!memcmp(&a, &b, sizeof a) && !memcmp(&a, &b0, sizeof a) && f0 == f1);
                rg_rect cv = rg_fit_rect(ww, wh, 512, 448, 16, 9, (rg_scale_mode)m, &f0);
                rg_rect c = rg_fit_rect_content(ww, wh, 512, 448, 16, 9, 4, 3, (rg_scale_mode)m, &f2);
                CHECK_EQ(f0, f2);
                CHECK(c.x >= cv.x && c.x + c.w <= cv.x + cv.w && c.y == cv.y && c.h == cv.h);
                CHECK(abs(2 * (c.x - cv.x) + c.w - cv.w) <= 1);
                if (m != RG_SCALE_STRETCH && c.h > 8)
                    CHECK(llabs((long long)c.w * 3 - (long long)c.h * 4) <= 4);
            }
}

/* a 512x448 test frame: a horizontal ramp per channel, rows differ */
static void wide_frame(uint32_t *px)
{
    for (uint32_t y = 0; y < 448; y++)
        for (uint32_t x = 0; x < 512; x++)
            px[y * 512 + x] = (x >> 1) | ((255 - (x >> 1)) << 8) | ((y * 255 / 447) << 16) | 0x80000000u;
}

static void wide_present(void)
{
    static uint32_t src[512 * 448], a[900 * 448], b[900 * 448];
    uint32_t w = 0;
    wide_frame(src);
    /* square pixels at the source width: the frame itself, alpha forced */
    CHECK_EQ(rg_present_image(src, 512, 448, 512, 448, 0, 0, a, 900 * 448, &w), 0);
    CHECK_EQ(w, 512);
    int same = 1;
    for (uint32_t i = 0; i < 512 * 448; i++) same &= a[i] == (src[i] | 0xFF000000u);
    CHECK(same);
    /* 4:3 -> 597 wide, 16:9 -> 796 wide */
    CHECK_EQ(rg_present_image(src, 512, 448, 4, 3, 0, 0, a, 900 * 448, &w), 0);
    CHECK_EQ(w, 597);
    /* the ramp stays monotonic and ends at the source's end values */
    for (uint32_t x = 1; x < 597; x++) CHECK((a[100 * 597 + x] & 0xFF) >= (a[100 * 597 + x - 1] & 0xFF));
    CHECK_EQ(a[100 * 597] & 0xFFFFFF, src[100 * 512] & 0xFFFFFF);
    CHECK_EQ(a[100 * 597 + 596] & 0xFFFFFF, src[100 * 512 + 511] & 0xFFFFFF);
    CHECK_EQ(rg_present_image(src, 512, 448, 16, 9, 0, 0, b, 900 * 448, &w), 0);
    CHECK_EQ(w, 796);
    /* 4:3 pillarboxed in 16:9: 99 + 597 + 100 columns; the middle is the 4:3
     * picture exactly, the bars opaque black */
    CHECK_EQ(rg_present_image(src, 512, 448, 16, 9, 4, 3, b, 900 * 448, &w), 0);
    CHECK_EQ(w, 796);
    int bars = 1, mid = 1;
    for (uint32_t y = 0; y < 448; y++) {
        for (uint32_t x = 0; x < 99; x++) bars &= b[y * 796 + x] == 0xFF000000u;
        for (uint32_t x = 696; x < 796; x++) bars &= b[y * 796 + x] == 0xFF000000u;
        for (uint32_t x = 0; x < 597; x++) mid &= b[y * 796 + 99 + x] == a[y * 597 + x];
    }
    CHECK(bars);
    CHECK(mid);
    /* too small a buffer: -1, the width still reported */
    w = 0;
    CHECK_EQ(rg_present_image(src, 512, 448, 16, 9, 4, 3, b, 796 * 448 - 1, &w), -1);
    CHECK_EQ(w, 796);
    CHECK_EQ(rg_present_image(NULL, 512, 448, 16, 9, 0, 0, b, 900 * 448, &w), -1);
}

/* WILL_FAIL control: the pillarbox check above must notice a frame that
 * was not pillarboxed */
static void wide_present_control(void)
{
    static uint32_t src[512 * 448], b[900 * 448];
    uint32_t w = 0;
    wide_frame(src);
    CHECK_EQ(rg_present_image(src, 512, 448, 16, 9, 0, 0, b, 900 * 448, &w), 0);
    int bars = 1;
    for (uint32_t y = 0; y < 448; y++)
        for (uint32_t x = 0; x < 99; x++) bars &= b[y * 796 + x] == 0xFF000000u;
    CHECK(bars);
}

static void wide_policy(void)
{
    rg_aspect_ctl c;
    rg_aspect_frame f;
    rg_aspect_ctl_init(&c);
    /* 4:3 never touches the game flag, in any screen state */
    for (int i = 0; i < 64; i++) {
        rg_aspect_step(&c, RG_ASPECT_4_3, i & 1, (i >> 1) & 1, (i >> 2) & 1, &f);
        CHECK_EQ(f.game_wide, -1);
        CHECK(f.canvas_num == 4 && f.canvas_den == 3 && f.content_num == 4 && f.content_den == 3);
    }
    /* 16:9: the field is WIDE; the title and kept movies are 4:3 in the canvas, flag 0 */
    rg_aspect_step(&c, RG_ASPECT_16_9, RG_MOVIE_ASPECT_KEEP, 0, 0, &f);
    CHECK(f.game_wide == 1 && f.canvas_num == 16 && f.canvas_den == 9 && f.content_num == 16 && f.content_den == 9);
    rg_aspect_step(&c, RG_ASPECT_16_9, RG_MOVIE_ASPECT_KEEP, 1, 0, &f);
    CHECK(f.game_wide == 0 && f.canvas_num == 16 && f.content_num == 4 && f.content_den == 3);
    rg_aspect_step(&c, RG_ASPECT_16_9, RG_MOVIE_ASPECT_KEEP, 0, 1, &f);
    CHECK(f.game_wide == 0 && f.canvas_num == 16 && f.content_num == 4 && f.content_den == 3);
    rg_aspect_step(&c, RG_ASPECT_16_9, RG_MOVIE_ASPECT_STRETCH, 0, 1, &f);
    CHECK(f.game_wide == 1 && f.content_num == 16 && f.content_den == 9);
    rg_aspect_step(&c, RG_ASPECT_16_9, RG_MOVIE_ASPECT_STRETCH, 1, 1, &f);   /* title wins */
    CHECK(f.game_wide == 0 && f.content_num == 4);
    /* a live switch back to 4:3 clears the flag once, then leaves it alone */
    rg_aspect_step(&c, RG_ASPECT_4_3, RG_MOVIE_ASPECT_KEEP, 0, 0, &f);
    CHECK_EQ(f.game_wide, 0);
    CHECK(f.canvas_num == 4 && f.content_num == 4);
    rg_aspect_step(&c, RG_ASPECT_4_3, RG_MOVIE_ASPECT_KEEP, 0, 0, &f);
    CHECK_EQ(f.game_wide, -1);

    /* through the registry: names, Original, --set */
    rg_settings *s = rg_settings_create();
    rg_settings_set_warn(s, NULL, NULL);
    rg_aspect_ctl_init(&c);
    rg_aspect_step_settings(&c, s, 0, 0, 0, 0, &f);            /* not registered: 4:3 */
    CHECK_EQ(f.game_wide, -1);
    rg_settings_register_core(s);
    int ia = rg_settings_find(s, "graphics.aspect"), im = rg_settings_find(s, "graphics.movie_aspect");
    CHECK(ia >= 0 && im >= 0);
    const rg_setting_def *da = rg_settings_def(s, ia), *dm = rg_settings_def(s, im);
    CHECK(da->enum_count == RG_ASPECT_COUNT && !strcmp(da->enum_names[RG_ASPECT_4_3], "4:3") &&
          !strcmp(da->enum_names[RG_ASPECT_16_9], "16:9") &&
          !strcmp(da->enum_names[RG_ASPECT_16_10], "16:10") &&
          !strcmp(da->enum_names[RG_ASPECT_21_9], "21:9") &&
          !strcmp(da->enum_names[RG_ASPECT_AUTO], "auto"));
    CHECK(dm->enum_count == 2 && !strcmp(dm->enum_names[RG_MOVIE_ASPECT_KEEP], "keep") &&
          !strcmp(dm->enum_names[RG_MOVIE_ASPECT_STRETCH], "stretch"));
    CHECK(!(da->flags & RG_SETF_PLACEHOLDER) && !(dm->flags & RG_SETF_PLACEHOLDER));
    CHECK(!(da->flags & RG_SETF_GAMEPLAY) && (da->flags & RG_SETF_DISPLAY));
    CHECK_EQ(rg_settings_get_enum(s, "graphics.aspect"), RG_ASPECT_4_3);   /* default */
    rg_aspect_step_settings(&c, s, 0, 0, 0, 0, &f);
    CHECK_EQ(f.game_wide, -1);
    char *argv[] = { "x", "--set", "graphics.aspect=16:9", "--set=graphics.movie_aspect=stretch" };
    int errors = 0;
    CHECK_EQ(rg_settings_apply_args(s, 4, argv, &errors, NULL), 1);
    CHECK_EQ(errors, 0);
    rg_aspect_step_settings(&c, s, 0, 1, 0, 0, &f);
    CHECK(f.game_wide == 1 && f.canvas_num == 16 && f.content_num == 16);
    /* the Original preset is 4:3 / keep */
    rg_settings_clear_overrides(s);
    CHECK_EQ(rg_settings_apply_preset(s, "original"), 0);
    CHECK_EQ(rg_settings_get_enum(s, "graphics.aspect"), RG_ASPECT_4_3);
    CHECK_EQ(rg_settings_get_enum(s, "graphics.movie_aspect"), RG_MOVIE_ASPECT_KEEP);
    CHECK(rg_settings_matches_preset(s, "original"));
    rg_aspect_step_settings(&c, s, 0, 0, 0, 0, &f);
    CHECK_EQ(f.game_wide, 0);                            /* undo of the 16:9 above */
    rg_aspect_step_settings(&c, s, 0, 0, 0, 0, &f);
    CHECK_EQ(f.game_wide, -1);
    /* stage 1 values through the registry: 21:9 from a file, auto from the window */
    rg_settings_parse(s, "[graphics]\naspect = 21:9\n", "t.ini");
    CHECK_EQ(rg_settings_get_enum(s, "graphics.aspect"), RG_ASPECT_21_9);
    rg_aspect_step_settings(&c, s, 0, 0, 0, 0, &f);
    CHECK(f.game_wide == 1 && f.canvas_num == 64 && f.canvas_den == 27 && f.content_num == 64);
    rg_settings_parse(s, "[graphics]\naspect = auto\n", "t.ini");
    CHECK_EQ(rg_settings_get_enum(s, "graphics.aspect"), RG_ASPECT_AUTO);
    rg_aspect_step_settings(&c, s, 0, 0, 1920, 1200, &f);
    CHECK(f.game_wide == 1 && f.canvas_num == 8 && f.canvas_den == 5);
    rg_aspect_step_settings(&c, s, 0, 0, 1280, 960, &f);   /* a 4:3 window: Original, undo once */
    CHECK(f.game_wide == 0 && f.canvas_num == 4 && f.canvas_den == 3);
    rg_aspect_step_settings(&c, s, 0, 0, 0, 0, &f);         /* no window known: 4:3 */
    CHECK_EQ(f.game_wide, -1);
    /* a file value outside the enum falls back to 4:3 */
    rg_settings_set_text(s, ia, "16:9", RG_SRC_API, NULL, 0);
    rg_settings_parse(s, "[graphics]\naspect = 32:9\n", "t.ini");
    CHECK_EQ(rg_settings_get_enum(s, "graphics.aspect"), RG_ASPECT_4_3);
    rg_settings_destroy(s);
}

/* Widescreen stage 2 (src/settings/rg_layout.h): anchors, the map, the GIF scan
 * and the packet hook on a hand-built GsPkt (A+D sprite + scissor, PACKED quad). */
static uint8_t g_lpkt[0x140];
static uint64_t g_lbuf[64] __attribute__((aligned(16)));
static int lpkt_build(int x0, int x1, int ztest, int scx0, int scx1)
{
    memset(g_lpkt, 0, sizeof g_lpkt);
    memset(g_lbuf, 0, sizeof g_lbuf);
    int q = 0;
    const int C = 2048 * 16, W = 512 * 16, L = C - W / 2;
    /* DMA cnt + VIF DIRECT, filled at the end */
    q++;
    g_lbuf[2 * q] = 4 | (1ull << 15) | (0ull << 58) | (1ull << 60);  /* NLOOP 4, A+D */
    g_lbuf[2 * q + 1] = 0xE;
    q++;
    g_lbuf[2 * q] = (uint64_t)(L + x0 * 16) | ((uint64_t)(100 * 16) << 16); g_lbuf[2 * q + 1] = 5; q++;
    g_lbuf[2 * q] = (uint64_t)(L + x1 * 16) | ((uint64_t)(120 * 16) << 16); g_lbuf[2 * q + 1] = 5; q++;
    g_lbuf[2 * q] = (uint64_t)scx0 | ((uint64_t)scx1 << 16) | (0ull << 32) | (447ull << 48); g_lbuf[2 * q + 1] = 0x40; q++;
    g_lbuf[2 * q] = 0; g_lbuf[2 * q + 1] = 0x3F; q++;
    /* PACKED XYZ2 x2 (a second form of vertex) */
    g_lbuf[2 * q] = 2 | (1ull << 15) | (0ull << 58) | (1ull << 60);
    g_lbuf[2 * q + 1] = 0x5;
    q++;
    g_lbuf[2 * q] = (uint64_t)(L + x0 * 16) | ((uint64_t)(200 * 16) << 32); q++;
    g_lbuf[2 * q] = (uint64_t)(L + x1 * 16) | ((uint64_t)(210 * 16) << 32); q++;
    uint32_t *t = (uint32_t *)g_lbuf;
    t[0] = (uint32_t)(q - 1) | 0x10000000u;
    t[3] = (uint32_t)(q - 1) | 0x50000000u;
    uint8_t *base = (uint8_t *)g_lbuf, *cur = base + 16 * q;
    memcpy(g_lpkt + 0xEC, &base, sizeof base);
    memcpy(g_lpkt + 0xF4, &cur, sizeof cur);
    int32_t c = C, w = W;
    memcpy(g_lpkt + 0x128, &c, 4);
    memcpy(g_lpkt + 0x130, &w, 4);
    g_lpkt[0x32] = ztest ? (uint8_t)(1 | (2 << 1)) : (uint8_t)(1 | (1 << 1));
    return q;
}
static int lpkt_x(int k)   /* vertex k's X in pixels from the left edge */
{
    const int L = 2048 * 16 - 256 * 16;
    uint64_t v = k < 2 ? g_lbuf[2 * (2 + k)] : g_lbuf[2 * (7 + k - 2)];
    return ((int)(v & 0xFFFF) - L + 8) / 16;
}
static void wide_layout(void)
{
    CHECK_EQ(rg_layout_anchor(10, 100, 0, 512), RG_ANCHOR_LEFT);
    CHECK_EQ(rg_layout_anchor(200, 300, 0, 512), RG_ANCHOR_CENTER);
    CHECK_EQ(rg_layout_anchor(420, 500, 0, 512), RG_ANCHOR_RIGHT);
    CHECK_EQ(rg_layout_anchor(0, 512, 0, 512), RG_ANCHOR_NONE);
    CHECK(fabsf(rg_layout_map(100, RG_ANCHOR_LEFT, 0, 512, 0.75f) - 75) < 1e-4f);
    CHECK(fabsf(rg_layout_map(256, RG_ANCHOR_CENTER, 0, 512, 0.75f) - 256) < 1e-4f);
    CHECK(fabsf(rg_layout_map(500, RG_ANCHOR_RIGHT, 0, 512, 0.75f) - 503) < 1e-4f);
    CHECK(fabsf(rg_layout_map(77, RG_ANCHOR_NONE, 0, 512, 0.75f) - 77) < 1e-4f);
    int q = lpkt_build(20, 60, 0, 10, 99);
    CHECK_EQ(rg_layout_scan_gif((uint8_t *)g_lbuf + 16, q - 1, NULL, 0), 5);
    /* inactive (4:3): nothing written */
    rg_layout_set_frame(1.0f, 1);
    rg_layout_task_begin(NULL);
    rg_layout_packet(g_lpkt, NULL);
    rg_layout_task_end();
    CHECK_EQ(lpkt_x(0), 20);
    CHECK_EQ(lpkt_x(1), 60);
    /* 16:9: a left element shrinks toward the left edge, both vertex forms + scissor */
    rg_layout_set_frame(0.75f, 2);
    rg_layout_task_begin(NULL);
    rg_layout_packet(g_lpkt, NULL);
    rg_layout_task_end();
    CHECK_EQ(lpkt_x(0), 15);
    CHECK_EQ(lpkt_x(1), 45);
    CHECK_EQ(lpkt_x(2), 15);
    CHECK_EQ(lpkt_x(3), 45);
    CHECK_EQ((int)(g_lbuf[8] & 0x7FF), 8);           /* scissor 10..99 -> 7.5..74 */
    CHECK_EQ((int)((g_lbuf[8] >> 16) & 0x7FF), 74);
    /* right / centre anchors */
    lpkt_build(440, 500, 0, 0, 511);
    rg_layout_task_begin(NULL); rg_layout_packet(g_lpkt, NULL); rg_layout_task_end();
    CHECK_EQ(lpkt_x(0), 458);
    CHECK_EQ(lpkt_x(1), 503);
    CHECK_EQ((int)((g_lbuf[8] >> 16) & 0x7FF), 511);  /* full-width scissor untouched */
    lpkt_build(200, 312, 0, 0, 511);
    rg_layout_task_begin(NULL); rg_layout_packet(g_lpkt, NULL); rg_layout_task_end();
    CHECK_EQ(lpkt_x(0), 214);
    CHECK_EQ(lpkt_x(1), 298);
    /* full screen, Z test and suppressed packets are left alone */
    lpkt_build(0, 512, 0, 0, 511);
    rg_layout_task_begin(NULL); rg_layout_packet(g_lpkt, NULL); rg_layout_task_end();
    CHECK_EQ(lpkt_x(0), 0);
    CHECK_EQ(lpkt_x(1), 512);
    lpkt_build(20, 60, 1, 0, 511);
    rg_layout_task_begin(NULL); rg_layout_packet(g_lpkt, NULL); rg_layout_task_end();
    CHECK_EQ(lpkt_x(0), 20);
    lpkt_build(20, 60, 0, 0, 511);
    rg_layout_suppress(1);
    rg_layout_task_begin(NULL); rg_layout_packet(g_lpkt, NULL); rg_layout_task_end();
    rg_layout_suppress(0);
    CHECK_EQ(lpkt_x(0), 20);
    /* two overlapping packets of one task share one anchor: a window across the
     * centre third and its text in the left third both centre-anchor.  The grouping is
     * one frame behind (packets are consumed as they close): the first frame lays the
     * text out by its own rectangle (left), the next by the group (centre). */
    static uint8_t pk1[0x140];
    static uint64_t b1[64] __attribute__((aligned(16)));
    rg_layout_set_frame(1.0f, 9);              /* inactive: forget earlier anchors */
    for (int fr = 0; fr < 2; fr++) {
        rg_layout_set_frame(0.75f, 10 + fr);
        lpkt_build(100, 400, 0, 0, 511);
        memcpy(pk1, g_lpkt, sizeof pk1);
        memcpy(b1, g_lbuf, sizeof b1);
        uint8_t *bb = (uint8_t *)b1, *cc = bb + ((uint8_t *)*(uint8_t **)(g_lpkt + 0xF4) - (uint8_t *)g_lbuf);
        memcpy(pk1 + 0xEC, &bb, sizeof bb);
        memcpy(pk1 + 0xF4, &cc, sizeof cc);
        lpkt_build(110, 150, 0, 0, 511);
        rg_layout_task_begin(NULL);
        rg_layout_packet(pk1, NULL);
        rg_layout_packet(g_lpkt, NULL);
        rg_layout_task_end();
        CHECK_EQ(lpkt_x(0), fr == 0 ? 83 : 147);   /* 110 * 0.75 = 82.5; 256 + (110 - 256) * 0.75 = 146.5 */
    }
    rg_layout_set_frame(1.0f, 12);
}

/* Widescreen stage 3 (USER 2026-10-19: no aspect switch for menus): a full-screen
 * indexed-colour background drawn by a task makes that task a menu task; the background
 * and every other packet of the task are squeezed about the screen centre (one 4:3
 * element), other tasks keep their own anchors, nothing asks for the 4:3 pillarbox. */
static int lpkt_cover(int x0, int x1, int y0, int y1, int psm)
{
    memset(g_lpkt, 0, sizeof g_lpkt);
    memset(g_lbuf, 0, sizeof g_lbuf);
    int q = 1;
    const int C = 2048 * 16, W = 512 * 16, L = C - W / 2;
    g_lbuf[2 * q] = 4 | (1ull << 15) | (0ull << 58) | (1ull << 60);  /* NLOOP 4, A+D */
    g_lbuf[2 * q + 1] = 0xE;
    q++;
    g_lbuf[2 * q] = (uint64_t)psm << 20; g_lbuf[2 * q + 1] = 0x06; q++;   /* TEX0_1 */
    g_lbuf[2 * q] = (uint64_t)(L + x0 * 16) | ((uint64_t)((1824 + y0) * 16) << 16); g_lbuf[2 * q + 1] = 5; q++;
    g_lbuf[2 * q] = (uint64_t)(L + x1 * 16) | ((uint64_t)((1824 + y1) * 16) << 16); g_lbuf[2 * q + 1] = 5; q++;
    g_lbuf[2 * q] = 0; g_lbuf[2 * q + 1] = 0x3F; q++;
    uint32_t *t = (uint32_t *)g_lbuf;
    t[0] = (uint32_t)(q - 1) | 0x10000000u;
    t[3] = (uint32_t)(q - 1) | 0x50000000u;
    uint8_t *base = (uint8_t *)g_lbuf, *cur = base + 16 * q;
    memcpy(g_lpkt + 0xEC, &base, sizeof base);
    memcpy(g_lpkt + 0xF4, &cur, sizeof cur);
    int32_t c = C, w = W;
    memcpy(g_lpkt + 0x128, &c, 4);
    memcpy(g_lpkt + 0x130, &w, 4);
    g_lpkt[0x32] = (uint8_t)(1 | (1 << 1));
    return q;
}
static int lcov_x(int k)
{
    const int L = 2048 * 16 - 256 * 16;
    return ((int)(g_lbuf[2 * (3 + k)] & 0xFFFF) - L + 8) / 16;
}
static void wide_menu(void)
{
    static int menu_fn, hud_fn;   /* two task identities */
    rg_layout_set_detect(0);
    rg_layout_set_frame(1.0f, 30);             /* forget earlier state */
    rg_layout_set_detect(1);
    rg_layout_set_frame(0.75f, 31);
    CHECK(!rg_layout_menu_screen());
    /* a field HUD task: a left element stays left-anchored */
    rg_layout_task_begin(&hud_fn);
    lpkt_cover(20, 60, 100, 120, 0x13);
    rg_layout_packet(g_lpkt, NULL);
    rg_layout_task_end();
    CHECK(lcov_x(0) == 15 && lcov_x(1) == 45);
    /* a 32-bit full-screen packet (a scene capture / fade) in a task: not a menu */
    rg_layout_task_begin(&menu_fn);
    lpkt_cover(0, 512, 0, 448, 0x00);
    rg_layout_packet(g_lpkt, NULL);
    CHECK(lcov_x(0) == 0 && lcov_x(1) == 512);
    /* the menu background (PSMT8, covering): squeezed about the centre with the menu */
    lpkt_cover(0, 512, 0, 448, 0x13);
    rg_layout_packet(g_lpkt, NULL);
    CHECK(lcov_x(0) == 64 && lcov_x(1) == 448);
    /* the menu's panel in the left third: centre-anchored with its background */
    lpkt_cover(20, 60, 100, 120, 0x14);
    rg_layout_packet(g_lpkt, NULL);
    CHECK(lcov_x(0) == 79 && lcov_x(1) == 109);   /* 256 + (20 - 256) * 0.75 = 79 */
    /* the scene capture drawn after it still covers the canvas */
    lpkt_cover(0, 512, 0, 448, 0x00);
    rg_layout_packet(g_lpkt, NULL);
    CHECK(lcov_x(0) == 0 && lcov_x(1) == 512);
    rg_layout_task_end();
    rg_layout_set_frame(0.75f, 32);
    CHECK(rg_layout_menu_screen());
    CHECK(!rg_layout_wants_pillarbox());       /* no aspect switch (stage 2: 1) */
    /* next frame: the menu task's packets are centred from their first packet on; the
     * HUD task keeps its anchor */
    rg_layout_task_begin(&menu_fn);
    lpkt_cover(20, 60, 100, 120, 0x14);
    rg_layout_packet(g_lpkt, NULL);
    CHECK(lcov_x(0) == 79);
    rg_layout_task_end();
    rg_layout_task_begin(&hud_fn);
    lpkt_cover(20, 60, 100, 120, 0x13);
    rg_layout_packet(g_lpkt, NULL);
    CHECK(lcov_x(0) == 15);
    rg_layout_task_end();
    /* the menu closed: two drawn frames without its background -> an ordinary task */
    rg_layout_set_frame(0.75f, 33);
    rg_layout_task_begin(&menu_fn);
    lpkt_cover(20, 60, 100, 120, 0x14);
    rg_layout_packet(g_lpkt, NULL);
    rg_layout_task_end();
    rg_layout_set_frame(0.75f, 34);
    CHECK(!rg_layout_menu_screen());
    rg_layout_task_begin(&menu_fn);
    lpkt_cover(20, 60, 100, 120, 0x14);
    rg_layout_packet(g_lpkt, NULL);
    rg_layout_task_end();
    CHECK(lcov_x(0) == 15);
    /* menu sprites off the 4:3 screen (GIF tag PRE: PRIM sprite): one slid out entirely
     * stays hidden (zero width), a small one across the left edge is clipped to the screen
     * with its UV cut, so neither shows in the wide canvas's side */
    rg_layout_set_frame(0.75f, 36);
    rg_layout_task_begin(&menu_fn);
    lpkt_cover(0, 512, 0, 448, 0x13);              /* the menu's background: a menu task */
    rg_layout_packet(g_lpkt, NULL);
    for (int c = 0; c < 2; c++) {
        int sx0 = c == 0 ? -100 : -40, sx1 = c == 0 ? -20 : 40;
        lpkt_cover(sx0, sx1, 100, 120, 0x13);
        /* -> PRE sprite tag and UV before each vertex: rebuild in place */
        const int C = 2048 * 16, W = 512 * 16, L = C - W / 2;
        int q = 1;
        memset(g_lbuf, 0, sizeof g_lbuf);
        g_lbuf[2 * q] = 5 | (1ull << 15) | (1ull << 46) | (0x116ull << 47) | (1ull << 60);
        g_lbuf[2 * q + 1] = 0xE;
        q++;
        g_lbuf[2 * q] = 0x13ull << 20; g_lbuf[2 * q + 1] = 0x06; q++;
        g_lbuf[2 * q] = 0; g_lbuf[2 * q + 1] = 0x03; q++;                        /* UV u 0 */
        g_lbuf[2 * q] = (uint64_t)(L + sx0 * 16) | ((uint64_t)(1924 * 16) << 16); g_lbuf[2 * q + 1] = 5; q++;
        g_lbuf[2 * q] = 80 * 16; g_lbuf[2 * q + 1] = 0x03; q++;                   /* UV u 80 */
        g_lbuf[2 * q] = (uint64_t)(L + sx1 * 16) | ((uint64_t)(1944 * 16) << 16); g_lbuf[2 * q + 1] = 5; q++;
        uint32_t *t = (uint32_t *)g_lbuf;
        t[0] = (uint32_t)(q - 1) | 0x10000000u;
        t[3] = (uint32_t)(q - 1) | 0x50000000u;
        uint8_t *cur = (uint8_t *)g_lbuf + 16 * q;
        memcpy(g_lpkt + 0xF4, &cur, sizeof cur);
        rg_layout_packet(g_lpkt, NULL);
        int xa = ((int)(g_lbuf[2 * 4] & 0xFFFF) - L + 8) / 16, xb = ((int)(g_lbuf[2 * 6] & 0xFFFF) - L + 8) / 16;
        if (c == 0) {
            CHECK(xa == xb);                                   /* hidden */
        } else {
            CHECK(xa == 64 && xb == 94);                       /* 0..40 about the centre */
            CHECK((g_lbuf[2 * 3] & 0x3FFF) == 40 * 16);        /* u 0 -> 40 at the screen edge */
            CHECK((g_lbuf[2 * 5] & 0x3FFF) == 80 * 16);
        }
    }
    rg_layout_task_end();
    rg_layout_set_detect(0);
    rg_layout_set_frame(1.0f, 37);
}

/* Widescreen stage 3 side strips (2026-10-24 gaps): a menu background sprite gets faded
 * mirrored strips appended to its packet (16 colour bands a side, 75 % darker at the canvas
 * edge, the packet's colour restored after them); a small sprite in the same packet off the
 * 4:3 screen stays hidden (per-sprite background test); a second background layer of the
 * same drawing function over the same rows gets no strips, another function's does. */
static uint64_t g_sbuf[2 * 512] __attribute__((aligned(16)));
static uint8_t g_sms[0x40];
static int spkt_build(int x0)
{
    const int C = 2048 * 16, W = 512 * 16, L = C - W / 2, T = 1824 * 16;
    memset(g_lpkt, 0, sizeof g_lpkt);
    memset(g_sbuf, 0, sizeof g_sbuf);
    memset(g_sms, 0, sizeof g_sms);
    int q = 1;
    q++;                                                                    /* GIF tag below */
    g_sbuf[2 * q] = 0x14ull << 20; g_sbuf[2 * q + 1] = 0x06; q++;          /* TEX0_1 PSMT4, TFX 0 */
    g_sbuf[2 * q] = 0x80808080ull; g_sbuf[2 * q + 1] = 0x01; q++;          /* RGBAQ */
    g_sbuf[2 * q] = 6; g_sbuf[2 * q + 1] = 0x00; q++;                      /* PRIM sprite */
    g_sbuf[2 * q] = 0; g_sbuf[2 * q + 1] = 0x03; q++;                      /* UV 0, 0 */
    g_sbuf[2 * q] = (uint64_t)(L + x0 * 16) | ((uint64_t)T << 16); g_sbuf[2 * q + 1] = 5; q++;
    g_sbuf[2 * q] = (256 * 16) | ((uint64_t)(448 * 16) << 16); g_sbuf[2 * q + 1] = 0x03; q++;
    g_sbuf[2 * q] = (uint64_t)(L + 512 * 16) | ((uint64_t)(T + 448 * 16) << 16); g_sbuf[2 * q + 1] = 5; q++;
    g_sbuf[2 * q] = 0; g_sbuf[2 * q + 1] = 0x03; q++;                      /* small sprite, off screen */
    g_sbuf[2 * q] = (uint64_t)(L + 600 * 16) | ((uint64_t)(T + 100 * 16) << 16); g_sbuf[2 * q + 1] = 5; q++;
    g_sbuf[2 * q] = 40 * 16; g_sbuf[2 * q + 1] = 0x03; q++;
    g_sbuf[2 * q] = (uint64_t)(L + 640 * 16) | ((uint64_t)(T + 120 * 16) << 16); g_sbuf[2 * q + 1] = 5; q++;
    g_sbuf[2 * q] = 0; g_sbuf[2 * q + 1] = 0x3F; q++;                      /* GsPktClose's NOP */
    g_sbuf[2] = (uint64_t)(q - 2) | 0x8000ull | (1ull << 60);              /* NLOOP, EOP, A+D */
    g_sbuf[3] = 0xE;
    uint32_t *t = (uint32_t *)g_sbuf;
    t[0] = (uint32_t)(q - 1) | 0x10000000u;
    t[3] = (uint32_t)(q - 1) | 0x50000000u;
    uint8_t *base = (uint8_t *)g_sbuf, *cur = base + 16 * q, *tag = base + 16;
    uint32_t *dma = t, *vif = t + 3;
    uint8_t *ms = g_sms;
    uint32_t msbase = (uint32_t)(uintptr_t)base;
    int32_t used = 0, cap = 512;
    memcpy(ms + 0x28, &msbase, 4);
    memcpy(ms + 0x2C, &used, 4);
    memcpy(ms + 0x34, &cap, 4);
    memcpy(g_lpkt + 0x00, &ms, sizeof ms);
    memcpy(g_lpkt + 0xEC, &base, sizeof base);
    memcpy(g_lpkt + 0xF4, &cur, sizeof cur);
    memcpy(g_lpkt + 0x100, &tag, sizeof tag);
    memcpy(g_lpkt + 0x104, &dma, sizeof dma);
    memcpy(g_lpkt + 0x108, &vif, sizeof vif);
    int32_t c = C, w = W;
    memcpy(g_lpkt + 0x128, &c, 4);
    memcpy(g_lpkt + 0x130, &w, 4);
    g_lpkt[0x32] = (uint8_t)(1 | (1 << 1));
    return q;
}
static int spkt_qw(void)   /* the packet's length in qwords (its cursor) */
{
    uint8_t *cur;
    memcpy(&cur, g_lpkt + 0xF4, sizeof cur);
    return (int)((cur - (uint8_t *)g_sbuf) / 16);
}
static void wide_strips(void)
{
    static int menu_fn, other_fn;
    const int L = 2048 * 16 - 256 * 16;
    rg_layout_set_detect(0);
    rg_layout_set_frame(1.0f, 40);
    rg_layout_set_detect(1);
    rg_layout_set_frame(0.75f, 41);
    rg_layout_task_begin(&menu_fn);
    int q = spkt_build(0);
    rg_layout_packet(g_lpkt, NULL);
    CHECK_EQ(((int)(g_sbuf[2 * 6] & 0xFFFF) - L + 8) / 16, 64);     /* background about the centre */
    CHECK_EQ(((int)(g_sbuf[2 * 8] & 0xFFFF) - L + 8) / 16, 448);
    CHECK_EQ(g_sbuf[2 * 10] & 0xFFFF, g_sbuf[2 * 12] & 0xFFFF);       /* off-screen sprite hidden */
    /* PRIM + 2 sides x 16 bands x (RGBAQ + 2 x (UV, XYZ2)) + the colour restored */
    CHECK_EQ(spkt_qw(), q + 1 + 2 * 16 * 5 + 1);
    CHECK_EQ((int)(g_sbuf[2] & 0x7FFF), q - 2 + 162);                 /* GIF NLOOP */
    CHECK_EQ((int)(((uint32_t *)g_sbuf)[0] & 0xFFFF), q - 1 + 162);   /* DMA QWC */
    CHECK_EQ(g_sbuf[2 * q + 1], 0x00ull);                             /* PRIM first */
    int b0 = q + 1, b7 = q + 1 + 15 * 5;                              /* left side, bands 0 / 15 */
    CHECK_EQ(g_sbuf[2 * b0 + 1], 0x01ull);
    CHECK((g_sbuf[2 * b0] & 0xFF) >= 0x7C);                           /* at the seam: ~full colour */
    CHECK((g_sbuf[2 * b7] & 0xFF) >= 0x1E && (g_sbuf[2 * b7] & 0xFF) <= 0x22);   /* edge: ~25 % */
    CHECK_EQ((g_sbuf[2 * b7] >> 24) & 0xFF, 0x80ull);                 /* alpha kept */
    /* band 15's outer vertex: the canvas edge, u mirrored 64 / 384 * 256 = 42.7 texels out */
    int xo = -1, uo = -1;
    for (int e = 1; e < 5; e += 2) {
        int x = ((int)(g_sbuf[2 * (b7 + e + 1)] & 0xFFFF) - L + 8) / 16;
        if (x == 0) { xo = x; uo = (int)(g_sbuf[2 * (b7 + e)] & 0x3FFF); }
    }
    CHECK_EQ(xo, 0);
    CHECK(uo >= 680 && uo <= 686);
    CHECK_EQ(g_sbuf[2 * (spkt_qw() - 1)], 0x80808080ull);              /* colour restored */
    CHECK_EQ(g_sbuf[2 * (spkt_qw() - 1) + 1], 0x01ull);
    /* a second layer of the same drawing function over the same rows: no strips */
    q = spkt_build(0);
    rg_layout_packet(g_lpkt, NULL);
    CHECK_EQ(spkt_qw(), q);
    /* another function's layer replaces them */
    q = spkt_build(0);
    rg_layout_packet(g_lpkt, &other_fn);
    CHECK_EQ(spkt_qw(), q + 162);
    /* a later layer of the first function reaching further out (x -64: squeezed edge 16
     * instead of 64) is extended from its own edge, on the left only */
    q = spkt_build(-64);
    rg_layout_packet(g_lpkt, NULL);
    CHECK_EQ(spkt_qw(), q + 1 + 16 * 5 + 1);
    rg_layout_task_end();
    /* dedicated menu task: on its first frame a packet drawn before its background keeps
     * its own (left) anchor; after frames with the background, one closing frame without
     * it, frames where the task draws nothing (menu closed) and reopening, the same packet
     * is centred from its first packet on */
    static int ded_fn;
    for (int fr = 0; fr < 6; fr++) {
        int bgnow = fr == 0 || fr == 1 || fr == 5;
        rg_layout_set_frame(0.75f, 43 + fr);
        if (fr == 3 || fr == 4)
            continue;
        rg_layout_task_begin(&ded_fn);
        lpkt_cover(20, 60, 100, 120, 0x14);
        rg_layout_packet(g_lpkt, NULL);
        if (fr == 0)
            CHECK_EQ(lcov_x(0), 15);                /* first ever frame: own anchor */
        if (fr == 5)
            CHECK_EQ(lcov_x(0), 79);                /* reopened: the menu from its first packet */
        if (bgnow) {
            lpkt_cover(0, 512, 0, 448, 0x13);
            rg_layout_packet(g_lpkt, NULL);
        }
        rg_layout_task_end();
    }
    rg_layout_set_detect(0);
    rg_layout_set_frame(1.0f, 42);
}

/* Widescreen stage 1: canvas shapes, the projection aspect / HUD x scale for
 * any shape, and the values the game overrides read (src/settings/rg_aspect.h). */
static void wide_any(void)
{
    int n = 0, d = 0;
    CHECK(!rg_aspect_resolve(RG_ASPECT_4_3, 0, 0, &n, &d) && n == 4 && d == 3);
    CHECK(rg_aspect_resolve(RG_ASPECT_16_9, 0, 0, &n, &d) && n == 16 && d == 9);
    CHECK(rg_aspect_resolve(RG_ASPECT_16_10, 0, 0, &n, &d) && n == 8 && d == 5);
    CHECK(rg_aspect_resolve(RG_ASPECT_21_9, 0, 0, &n, &d) && n == 64 && d == 27);
    CHECK(!rg_aspect_resolve(RG_ASPECT_AUTO, 0, 0, &n, &d) && n == 4 && d == 3);
    CHECK(rg_aspect_resolve(RG_ASPECT_AUTO, 1280, 720, &n, &d) && n == 16 && d == 9);
    CHECK(rg_aspect_resolve(RG_ASPECT_AUTO, 3440, 1440, &n, &d) && n == 43 && d == 18);
    CHECK(rg_aspect_resolve(RG_ASPECT_AUTO, 1366, 768, &n, &d) && n == 683 && d == 384);
    CHECK(!rg_aspect_resolve(RG_ASPECT_AUTO, 1281, 960, &n, &d) && n == 4 && d == 3);  /* within 1% */
    CHECK(!rg_aspect_resolve(RG_ASPECT_AUTO, 768, 1024, &n, &d) && n == 4 && d == 3);  /* portrait */
    CHECK(rg_aspect_resolve(RG_ASPECT_AUTO, 7680, 1080, &n, &d) && n == 32 && d == 9); /* clamp */
    CHECK(!rg_aspect_resolve(99, 1920, 1080, &n, &d) && n == 4 && d == 3);
    /* exact retail constants at 4:3 and 16:9 */
    CHECK(rg_aspect_d_for(4, 3) == 0.75f && rg_hud_xscale_for(4, 3) == 1.0f);
    CHECK(rg_aspect_d_for(16, 9) == 0.5625f && rg_hud_xscale_for(16, 9) == 0.75f);
    CHECK(rg_aspect_d_for(1920, 1080) == 0.5625f && rg_hud_xscale_for(1920, 1080) == 0.75f);
    CHECK(rg_aspect_d_for(8, 5) == 0.625f);
    CHECK(rg_hud_xscale_for(8, 5) == (float)(20.0 / 24.0));
    CHECK(rg_hud_xscale_for(64, 27) == (float)(108.0 / 192.0));
    /* s = d / 0.75 (the HUD squeeze equals the projection's), monotonic */
    float last = 2.0f;
    for (int w = 1024; w <= 4096; w += 7) {
        float dd = rg_aspect_d_for(w, 768), ss = rg_hud_xscale_for(w, 768);
        CHECK(fabs(ss - dd / 0.75) < 1e-6 && ss <= last);
        last = ss;
    }
    /* the published values: retail constants unless our policy owns the flag */
    rg_aspect_ctl c;
    rg_aspect_frame f;
    rg_aspect_ctl_init(&c);
    rg_aspect_set_current(NULL);
    CHECK(rg_aspect_d() == 0.5625f && rg_hud_xscale() == 0.75f);
    rg_aspect_step(&c, RG_ASPECT_4_3, 0, 0, 0, &f);          /* the game's own flag (key capture) */
    rg_aspect_set_current(&f);
    CHECK(rg_aspect_d() == 0.5625f && rg_hud_xscale() == 0.75f);
    rg_aspect_step(&c, RG_ASPECT_16_9, 0, 0, 0, &f);
    rg_aspect_set_current(&f);
    CHECK(rg_aspect_d() == 0.5625f && rg_hud_xscale_world() == 0.75f);   /* stage 0 values */
    CHECK(rg_hud_xscale() == 1.0f);   /* stage 2 active (ui_layout keep): the layout squeezes the HUD */
    rg_aspect_step(&c, RG_ASPECT_16_10, 0, 0, 0, &f);
    rg_aspect_set_current(&f);
    CHECK(f.game_wide == 1 && rg_aspect_d() == 0.625f && rg_hud_xscale_world() == (float)(20.0 / 24.0));
    rg_aspect_set_ui_layout(RG_UI_LAYOUT_STRETCH);              /* stage 1 look: the sites narrow themselves */
    rg_aspect_set_current(&f);
    CHECK(rg_hud_xscale() == (float)(20.0 / 24.0) && !rg_layout_active());
    rg_aspect_set_ui_layout(RG_UI_LAYOUT_KEEP);
    rg_aspect_set_current(&f);
    CHECK(rg_hud_xscale() == 1.0f && rg_layout_active());
    rg_aspect_step(&c, RG_ASPECT_21_9, RG_MOVIE_ASPECT_KEEP, 0, 1, &f);   /* kept movie: flag 0 */
    rg_aspect_set_current(&f);
    CHECK(f.game_wide == 0 && f.canvas_num == 64 && f.content_num == 4 && rg_aspect_d() == 0.5625f);
    rg_aspect_step_ratio(&c, 43, 18, RG_MOVIE_ASPECT_STRETCH, 0, 1, &f);  /* stretched movie */
    rg_aspect_set_current(&f);
    CHECK(f.game_wide == 1 && f.content_num == 43 && rg_aspect_d() == 18.0f / 43.0f);
    rg_aspect_step_ratio(&c, 4, 3, 0, 0, 0, &f);
    CHECK_EQ(f.game_wide, 0);                                  /* undo */
    rg_aspect_set_current(&f);
    CHECK(rg_aspect_d() == 0.5625f && rg_hud_xscale() == 0.75f);
}

static void wide_host(void)
{
    rg_host_config c;
    rg_host_config_default(&c);
    c.headless = 1;
    rg_host *h = rg_host_create(&c);
    CHECK(h != NULL);
    if (!h) return;
    int an, ad, cn, cd;
    rg_host_get_aspect(h, &an, &ad, &cn, &cd);
    CHECK(an == 4 && ad == 3 && cn == 4 && cd == 3);
    /* by default the host fit is the old 4:3 rg_fit_rect, every mode */
    for (int m = 0; m < 4; m++) {
        rg_host_set_scale(h, (rg_scale_mode)m);
        for (int ww = 64; ww <= 3000; ww += 97)
            for (int wh = 64; wh <= 2000; wh += 89) {
                int f0, f1;
                rg_rect a = rg_fit_rect(ww, wh, 512, 448, 4, 3, (rg_scale_mode)m, &f0);
                rg_rect b = rg_host_fit(h, ww, wh, 512, 448, &f1);
                CHECK(!memcmp(&a, &b, sizeof a) && f0 == f1);
            }
    }
    rg_host_set_scale(h, RG_SCALE_LINEAR);
    rg_host_set_aspect(h, 16, 9, 4, 3);
    rg_host_get_aspect(h, &an, &ad, &cn, &cd);
    CHECK(an == 16 && ad == 9 && cn == 4 && cd == 3);
    rg_rect r = rg_host_fit(h, 1280, 720, 512, 448, NULL);
    CHECK(r.x == 160 && r.y == 0 && r.w == 960 && r.h == 720);
    /* the post chain hands the presenter a frame already at the content size:
     * it lands in the same place */
    rg_rect r2 = rg_host_fit(h, 1280, 720, 960, 720, NULL);
    CHECK(!memcmp(&r, &r2, sizeof r));
    rg_host_set_aspect(h, 16, 9, 0, 0);
    rg_host_get_aspect(h, &an, &ad, &cn, &cd);
    CHECK(cn == 16 && cd == 9);
    r = rg_host_fit(h, 1280, 960, 512, 448, NULL);
    CHECK(r.x == 0 && r.y == 120 && r.w == 1280 && r.h == 720);
    rg_host_set_aspect(h, 0, 0, 0, 0);                    /* bad -> 4:3 */
    rg_host_get_aspect(h, &an, &ad, &cn, &cd);
    CHECK(an == 4 && ad == 3 && cn == 4 && cd == 3);
    /* presenting headless keeps the frame for screenshots, any aspect */
    static uint32_t px[512 * 448];
    wide_frame(px);
    rg_host_set_aspect(h, 16, 9, 4, 3);
    CHECK_EQ(rg_host_present(h, px, 512, 448), 0);
    uint32_t w = 0, hh = 0;
    CHECK(rg_host_last_frame(h, &w, &hh) != NULL && w == 512 && hh == 448);
    rg_host_destroy(h);
}

/* ================================================================== main */
typedef struct test { const char *name; void (*fn)(void); } test;
/* ============================================================ audio_device / audio_focus
 * P6 audio (docs/HOST.md "Audio devices and focus"): device choice by name with fallback,
 * hot switch on removal, the menu's device list, mute when unfocused. */
static int fake_choices(const char *id, const char **out, int cap, void *user)
{
    (void)user;
    static const char *const k[] = {"", "Speakers (Realtek)", "Headphones (USB)"};
    if (strcmp(id, "audio.device")) return 0;
    int n = cap < 3 ? cap : 3;
    for (int i = 0; i < n; i++) out[i] = k[i];
    return n;
}

/* a non-headless host on SDL's dummy video + dummy audio drivers (NULL if unavailable) */
static rg_host *dummy_host(void)
{
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "dummy");
    SDL_SetHint(SDL_HINT_AUDIO_DRIVER, "dummy");
    rg_host_config c;
    rg_host_config_default(&c);
    c.win_w = 320;
    c.win_h = 240;
    return rg_host_create(&c);
}

static void audio_device(void)
{
    /* pick: exact, then ignoring case; "" / missing = the default (-1) */
    const char *names[] = {"Speakers (Realtek)", "Headphones (USB)", "speakers (realtek) 2"};
    CHECK_EQ(rg_audio_device_pick("Headphones (USB)", names, 3), 1);
    CHECK_EQ(rg_audio_device_pick("headphones (usb)", names, 3), 1);
    CHECK_EQ(rg_audio_device_pick("Speakers (Realtek)", names, 3), 0);
    CHECK_EQ(rg_audio_device_pick("speakers (realtek) 2", names, 3), 2);
    CHECK_EQ(rg_audio_device_pick("Speakers", names, 3), -1);
    CHECK_EQ(rg_audio_device_pick("", names, 3), -1);
    CHECK_EQ(rg_audio_device_pick(NULL, names, 3), -1);
    CHECK_EQ(rg_audio_device_pick("Headphones (USB)", NULL, 0), -1);

    /* the menu: LEFT / RIGHT on audio.device steps through the choices */
    rg_settings *s = rg_settings_create();
    rg_settings_set_warn(s, NULL, NULL);
    rg_settings_register_core(s);
    rg_menu m;
    rg_menu_init(&m, s);
    rg_menu_set_choices(&m, fake_choices, NULL);
    m.open = true;
    int idx = rg_settings_find(s, "audio.device");
    CHECK(idx >= 0);
    const rg_setting_def *d = rg_settings_def(s, idx);
    CHECK(d && !(d->flags & (RG_SETF_PLACEHOLDER | RG_SETF_RESTART)));   /* live now */
    /* put the cursor on the row */
    bool found = false;
    for (int pg = 0; pg < m.npages && !found; pg++) {
        m.page = pg;
        int rows[RG_MENU_MAX_ROWS];
        int n = rg_menu_rows(&m, rows, RG_MENU_MAX_ROWS);
        for (int r = 0; r < n; r++)
            if (rows[r] == idx) { m.cursor = r; found = true; break; }
    }
    CHECK(found);
    rg_menu_command(&m, RG_MENU_RIGHT, 0);
    CHECK(!strcmp(rg_settings_get_string(s, "audio.device"), "Speakers (Realtek)"));
    rg_menu_command(&m, RG_MENU_RIGHT, 0);
    CHECK(!strcmp(rg_settings_get_string(s, "audio.device"), "Headphones (USB)"));
    rg_menu_command(&m, RG_MENU_RIGHT, 0);
    CHECK(!strcmp(rg_settings_get_string(s, "audio.device"), ""));   /* wraps to the default */
    rg_menu_command(&m, RG_MENU_LEFT, 0);
    CHECK(!strcmp(rg_settings_get_string(s, "audio.device"), "Headphones (USB)"));
    /* a saved name that is not present: RIGHT goes to the first choice */
    rg_settings_set_string(s, "audio.device", "Old DAC", RG_SRC_FILE);
    rg_menu_command(&m, RG_MENU_RIGHT, 0);
    CHECK(!strcmp(rg_settings_get_string(s, "audio.device"), ""));
    /* without choices the row still asks for the editor (text entry) */
    rg_menu_set_choices(&m, NULL, NULL);
    rg_menu_command(&m, RG_MENU_RIGHT, 0);
    CHECK(!strcmp(rg_settings_get_string(s, "audio.device"), ""));
    rg_settings_destroy(s);

    /* headless: no device, setting a name is harmless */
    {
        rg_host_config c;
        rg_host_config_default(&c);
        c.headless = 1;
        rg_host *h = rg_host_create(&c);
        CHECK(h != NULL);
        if (h) {
            CHECK_EQ(rg_host_set_audio_device(h, "Headphones (USB)"), 0);
            const char *list[8];
            CHECK_EQ(rg_host_audio_devices(h, list, 8), 1);   /* just "" (the default) */
            int16_t z[2 * 800] = {0};
            CHECK_EQ(rg_host_audio_push(h, z, 800), 0);
            rg_host_destroy(h);
        }
    }

    /* a real SDL stream on the dummy audio driver: fallback, switch, removal */
    rg_host *h = dummy_host();
    if (!h) {
        printf("audio_device: SDL dummy drivers unavailable (%s): device part skipped\n", SDL_GetError());
        return;
    }
    const char *list[RG_MENU_MAX_CHOICES];
    int n = rg_host_audio_devices(h, list, RG_MENU_MAX_CHOICES);
    CHECK(n >= 1 && !strcmp(list[0], ""));
    int fb = -1;
    CHECK(!strcmp(rg_host_audio_device(h, &fb), "") && fb == 0);
    uint32_t dev0 = rg_host_audio_device_id(h);
    CHECK(dev0 != 0);
    int16_t blk[2 * 800];
    for (int i = 0; i < 800; i++) blk[2 * i] = blk[2 * i + 1] = (int16_t)(i * 37);
    CHECK_EQ(rg_host_audio_push(h, blk, 800), 0);
    /* a name that is not present: the default, flagged */
    CHECK_EQ(rg_host_set_audio_device(h, "No Such Device 1234"), 0);
    CHECK(!strcmp(rg_host_audio_device(h, &fb), "") && fb == 1);
    CHECK(rg_host_audio_device_id(h) != 0);
    CHECK_EQ(rg_host_audio_push(h, blk, 800), 0);
    if (n >= 2) { /* a present device by name (case-insensitive) */
        char lowered[256];
        snprintf(lowered, sizeof lowered, "%s", list[1]);
        for (char *p = lowered; *p; p++) if (*p >= 'A' && *p <= 'Z') *p = (char)(*p + 32);
        CHECK_EQ(rg_host_set_audio_device(h, lowered), 0);
        CHECK(rg_host_audio_device(h, &fb)[0] != 0 && fb == 0);
        CHECK_EQ(rg_host_audio_push(h, blk, 800), 0);
        /* it disappears (an unplug): the default, the stream keeps working.  First drain the
         * driver's own start-up events (ADDED for each device present). */
        rg_host_pump(h);
        CHECK(rg_host_audio_device(h, &fb)[0] != 0 && fb == 0);
        uint32_t sw = rg_host_audio_device_switches(h);
        SDL_Event e;
        SDL_zero(e);
        e.type = SDL_EVENT_AUDIO_DEVICE_REMOVED;
        e.adevice.which = rg_host_audio_device_id(h);
        e.adevice.recording = false;
        SDL_PushEvent(&e);
        rg_host_pump(h);
        CHECK(!strcmp(rg_host_audio_device(h, &fb), "") && fb == 1);
        CHECK(rg_host_audio_device_switches(h) == sw + 1);
        CHECK(rg_host_audio_device_id(h) != 0);
        CHECK_EQ(rg_host_audio_push(h, blk, 800), 0);
        /* it comes back (ADDED): the chosen device again */
        SDL_zero(e);
        e.type = SDL_EVENT_AUDIO_DEVICE_ADDED;
        e.adevice.which = 1;
        SDL_PushEvent(&e);
        rg_host_pump(h);
        CHECK(rg_host_audio_device(h, &fb)[0] != 0 && fb == 0);
    }
    CHECK_EQ(rg_host_set_audio_device(h, ""), 0);
    CHECK(!strcmp(rg_host_audio_device(h, &fb), "") && fb == 0);
    CHECK(rg_host_audio_pushed_total(h) >= 4 * 800);
    printf("audio_device: %d playback device(s) on the dummy driver, %u binds\n", n - 1,
           rg_host_audio_device_switches(h));
    rg_host_destroy(h);
}

static void audio_focus(void)
{
    CHECK(rg_audio_output_gain(0.8f, 1, 0) == 0.8f);
    CHECK(rg_audio_output_gain(0.8f, 0, 0) == 0.0f);   /* unfocused, mute */
    CHECK(rg_audio_output_gain(0.8f, 0, 1) == 0.8f);   /* unfocused, keep playing */
    CHECK(rg_audio_output_gain(2.0f, 1, 1) == 1.0f);
    CHECK(rg_audio_output_gain(-1.0f, 1, 1) == 0.0f);
    /* the registry: audio.background is live, keep-playing in Original and by default */
    rg_settings *s = rg_settings_create();
    rg_settings_set_warn(s, NULL, NULL);
    rg_settings_register_core(s);
    int i = rg_settings_find(s, "audio.background");
    CHECK(i >= 0);
    const rg_setting_def *d = rg_settings_def(s, i);
    CHECK(d && !(d->flags & RG_SETF_PLACEHOLDER) && (d->flags & RG_SETF_HAS_ORIGINAL) && d->orig_i == 1 && d->def_i == 1);
    static const char *const vols[] = {"audio.music_volume", "audio.effects_volume", "audio.voice_volume",
                                       "audio.movie_volume"};
    for (int k = 0; k < 4; k++) {
        const rg_setting_def *v = rg_settings_def(s, rg_settings_find(s, vols[k]));
        CHECK(v && !(v->flags & (RG_SETF_PLACEHOLDER | RG_SETF_GAMEPLAY)) && v->orig_i == 100 && v->def_i == 100);
    }
    rg_settings_destroy(s);

    rg_host *h = dummy_host();
    if (!h) {
        printf("audio_focus: SDL dummy drivers unavailable: host part skipped\n");
        return;
    }
    rg_host_set_volume(h, 0.5f);
    rg_host_set_focus(h, 1);
    CHECK(rg_host_audio_output_gain(h) == 0.5f);
    rg_host_set_audio_background(h, 0);
    rg_host_set_focus(h, 0);
    CHECK(rg_host_audio_output_gain(h) == 0.0f);
    rg_host_set_audio_background(h, 1);            /* keep playing */
    CHECK(rg_host_audio_output_gain(h) == 0.5f);
    rg_host_set_audio_background(h, 0);
    CHECK(rg_host_audio_output_gain(h) == 0.0f);
    rg_host_set_focus(h, 1);
    CHECK(rg_host_audio_output_gain(h) == 0.5f);
    /* through the event loop and the settings registry */
    rg_settings *rs = rg_settings_create();
    rg_settings_set_warn(rs, NULL, NULL);
    rg_settings_register_core(rs);
    rg_settings_set_bool(rs, "audio.background", false, RG_SRC_API);
    rg_settings_set_int(rs, "audio.master_volume", 50, RG_SRC_API);
    rg_host_attach_settings(h, rs, NULL);
    SDL_Event e;
    SDL_zero(e);
    e.type = SDL_EVENT_WINDOW_FOCUS_LOST;
    SDL_PushEvent(&e);
    rg_host_pump(h);
    CHECK(rg_host_audio_output_gain(h) == 0.0f);
    SDL_zero(e);
    e.type = SDL_EVENT_WINDOW_FOCUS_GAINED;
    SDL_PushEvent(&e);
    rg_host_pump(h);
    CHECK(rg_host_audio_output_gain(h) == 0.5f);
    rg_settings_set_bool(rs, "audio.background", true, RG_SRC_MENU);
    SDL_zero(e);
    e.type = SDL_EVENT_WINDOW_FOCUS_LOST;
    SDL_PushEvent(&e);
    rg_host_pump(h);
    CHECK(rg_host_audio_output_gain(h) == 0.5f);   /* keep playing */
    rg_host_attach_settings(h, NULL, NULL);
    rg_host_destroy(h);
    rg_settings_destroy(rs);
    printf("audio_focus: mute on focus loss follows audio.background (events and registry)\n");
}

static const test k_tests[] = {
    { "pad_report", pad_report },
    { "input_mapping", input_mapping },
    { "input_config", input_config },
    { "input_script", input_script },
    { "script_determinism", script_determinism },
    { "scaling", scaling },
    { "png_roundtrip", png_roundtrip },
    { "png_corrupt_control", png_corrupt_control },
    { "pacing", pacing },
    { "audio_reg", audio_reg },
    { "audio_device", audio_device },
    { "audio_focus", audio_focus },
    { "wide_fit", wide_fit },
    { "wide_present", wide_present },
    { "wide_present_control", wide_present_control },
    { "wide_policy", wide_policy },
    { "wide_any", wide_any },
    { "wide_host", wide_host },
    { "wide_layout", wide_layout },
    { "wide_menu", wide_menu },
    { "wide_strips", wide_strips },
};

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-host-tests <test> | script_dump | png_write | pngcheck\n");
        return 2;
    }
    const char *n = argv[1];
    if (!strcmp(n, "script_dump")) return cmd_script_dump(argc, argv);
    if (!strcmp(n, "png_write")) return cmd_png_write(argc, argv);
    if (!strcmp(n, "pngcheck")) return cmd_pngcheck(argc, argv);
    for (size_t i = 0; i < sizeof k_tests / sizeof k_tests[0]; i++) {
        if (strcmp(n, k_tests[i].name)) continue;
        k_tests[i].fn();
        if (g_fail) {
            fprintf(stderr, "%s: FAIL (%d checks)\n", n, g_fail);
            return 1;
        }
        printf("%s: PASS\n", n);
        return 0;
    }
    fprintf(stderr, "unknown test %s\n", n);
    return 2;
}
