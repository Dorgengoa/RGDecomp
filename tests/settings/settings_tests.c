/* SPDX-License-Identifier: CC0-1.0 */
/* Settings registry (docs/SETTINGS.md) and input-action layer (docs/INPUT.md)
 * tests: rg-settings-tests <name> <outdir>; exit 0 = pass. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "host.h"
#include "rg_input.h"
#include "rg_menu.h"
#include "rg_settings.h"

static int g_fail;
#define CHECK(c) do { if (!(c)) { g_fail++; if (g_fail < 60) \
    fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { long long _a = (long long)(a), _b = (long long)(b); \
    if (_a != _b) { g_fail++; if (g_fail < 60) fprintf(stderr, \
    "%s:%d: %s == %lld (0x%llX), expected %s == %lld (0x%llX)\n", __FILE__, __LINE__, \
    #a, _a, (unsigned long long)_a, #b, _b, (unsigned long long)_b); } } while (0)
#define CHECK_STR(a, b) do { const char *_a = (a), *_b = (b); \
    if (strcmp(_a ? _a : "(null)", _b ? _b : "(null)")) { g_fail++; if (g_fail < 60) \
    fprintf(stderr, "%s:%d: %s == \"%s\", expected \"%s\"\n", __FILE__, __LINE__, #a, \
    _a ? _a : "(null)", _b ? _b : "(null)"); } } while (0)

static const char *g_out = ".";

/* ------------------------------------------------------------ helpers */
typedef struct warnlog { int n; char all[8192]; } warnlog;
static warnlog g_warn;

static void collect(void *user, const char *msg)
{
    warnlog *w = (warnlog *)user;
    w->n++;
    size_t L = strlen(w->all);
    snprintf(w->all + L, sizeof w->all - L, "%s\n", msg);
}

static rg_settings *mk_empty(void)
{
    memset(&g_warn, 0, sizeof g_warn);
    rg_settings *s = rg_settings_create();
    rg_settings_set_warn(s, collect, &g_warn);
    return s;
}

static rg_settings *mk(void)
{
    rg_settings *s = mk_empty();
    CHECK_EQ(rg_settings_register_core(s), 0);
    CHECK_EQ(rg_actions_register_settings(s), 0);
    CHECK_EQ(g_warn.n, 0);
    return s;
}

static const char *val(const rg_settings *s, const char *id)
{
    static char buf[4][1024];
    static int k;
    k = (k + 1) & 3;
    rg_settings_value_text(s, rg_settings_find(s, id), buf[k], sizeof buf[k]);
    return buf[k];
}

static const char *pval(const rg_settings *s, const char *id)
{
    static char buf[4][1024];
    static int k;
    k = (k + 1) & 3;
    rg_settings_persistent_text(s, rg_settings_find(s, id), buf[k], sizeof buf[k]);
    return buf[k];
}

static int set(rg_settings *s, const char *id, const char *text, rg_setting_source src)
{
    return rg_settings_set_text(s, rg_settings_find(s, id), text, src, NULL, 0);
}

static char *slurp(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *b = (char *)malloc((size_t)n + 1);
    if (fread(b, 1, (size_t)n, f) != (size_t)n) n = 0;
    b[n] = 0;
    fclose(f);
    return b;
}

static void spit(const char *path, const char *text)
{
    FILE *f = fopen(path, "wb");
    if (!f) { CHECK(!"cannot write a test file"); return; }
    fputs(text, f);
    fclose(f);
}

static void outpath(char *buf, size_t cap, const char *name)
{
    snprintf(buf, cap, "%s/%s", g_out, name);
}

/* ================================================================ registry */
static const char *const k_colors[] = { "red", "green", "blue" };

static int lower_no_bang(const char *text, char *norm, size_t cap, char *err, size_t errcap, void *u)
{
    (void)u;
    if (strchr(text, '!')) { snprintf(err, errcap, "no '!' allowed"); return -1; }
    size_t i = 0;
    for (; text[i] && i + 1 < cap; i++) norm[i] = (char)(text[i] >= 'A' && text[i] <= 'Z' ? text[i] + 32 : text[i]);
    norm[i] = 0;
    return 0;
}

static const rg_setting_def k_tdefs[] = {
    { .id = "t.b", .type = RG_SET_BOOL, .label = "Bool", .flags = RG_SETF_HAS_ORIGINAL, .def_i = 1, .orig_i = 0 },
    { .id = "t.i", .type = RG_SET_INT, .def_i = 5, .min_i = 0, .max_i = 10, .step_i = 2 },
    { .id = "t.f", .type = RG_SET_FLOAT, .def_f = 0.5, .min_f = 0.0, .max_f = 1.0, .step_f = 0.1 },
    { .id = "t.e", .type = RG_SET_ENUM, .def_i = 1, .enum_names = k_colors, .enum_count = 3 },
    { .id = "t.s", .type = RG_SET_STRING, .def_s = "abc", .validate = lower_no_bang },
    { .id = "t.k", .type = RG_SET_BINDING, .def_s = "key:A", .validate = rg_binding_validate },
    /* refused */
    { .id = "t.b", .type = RG_SET_BOOL },
    { .id = "Bad.Id", .type = RG_SET_BOOL },
    { .id = "t.bad_int", .type = RG_SET_INT, .def_i = 20, .min_i = 0, .max_i = 10 },
    { .id = "t.bad_enum", .type = RG_SET_ENUM, .def_i = 5, .enum_names = k_colors, .enum_count = 3 },
};

static rg_settings *mk_t(void)
{
    rg_settings *s = mk_empty();
    CHECK_EQ(rg_settings_register(s, k_tdefs, 10), -1);
    CHECK_EQ(rg_settings_count(s), 6);
    CHECK_EQ(g_warn.n, 4);
    memset(&g_warn, 0, sizeof g_warn);
    return s;
}

static int t_registry_types(void)
{
    rg_settings *s = mk_t();
    char err[256];
    CHECK(rg_settings_get_bool(s, "t.b"));
    CHECK_EQ(rg_settings_get_int(s, "t.i"), 5);
    CHECK(fabs(rg_settings_get_float(s, "t.f") - 0.5) < 1e-12);
    CHECK_EQ(rg_settings_get_enum(s, "t.e"), 1);
    CHECK_STR(rg_settings_get_string(s, "t.e"), "green");
    CHECK_STR(rg_settings_get_string(s, "t.s"), "abc");
    CHECK_STR(rg_settings_get_string(s, "t.k"), "key:A");
    CHECK(rg_settings_is_default(s, rg_settings_find(s, "t.i")));
    /* bool spellings */
    const char *yes[] = { "true", "ON", "Yes", "1", "enabled" }, *no[] = { "false", "off", "NO", "0", "disabled" };
    for (int i = 0; i < 5; i++) {
        CHECK(set(s, "t.b", no[i], RG_SRC_API) >= 0); CHECK(!rg_settings_get_bool(s, "t.b"));
        CHECK(set(s, "t.b", yes[i], RG_SRC_API) >= 0); CHECK(rg_settings_get_bool(s, "t.b"));
    }
    CHECK_EQ(set(s, "t.b", "maybe", RG_SRC_API), RG_SET_INVALID);
    CHECK(rg_settings_get_bool(s, "t.b"));
    /* int */
    CHECK_EQ(set(s, "t.i", "0x0A", RG_SRC_API), RG_SET_OK);
    CHECK_EQ(rg_settings_get_int(s, "t.i"), 10);
    CHECK_EQ(rg_settings_set_text(s, rg_settings_find(s, "t.i"), "11", RG_SRC_API, err, sizeof err), RG_SET_INVALID);
    CHECK(strstr(err, "outside 0..10") != NULL);
    CHECK_EQ(set(s, "t.i", "7x", RG_SRC_API), RG_SET_INVALID);
    CHECK_EQ(set(s, "t.i", "", RG_SRC_API), RG_SET_INVALID);
    CHECK_EQ(rg_settings_get_int(s, "t.i"), 10);
    CHECK_EQ(rg_settings_set_int(s, "t.i", 11, RG_SRC_API), RG_SET_INVALID);
    CHECK_EQ(rg_settings_set_int(s, "t.i", 10, RG_SRC_API), RG_SET_UNCHANGED);
    CHECK_EQ(rg_settings_set_int(s, "t.i", 3, RG_SRC_API), RG_SET_OK);
    /* float */
    CHECK_EQ(set(s, "t.f", "1.5", RG_SRC_API), RG_SET_INVALID);
    CHECK_EQ(set(s, "t.f", "nan", RG_SRC_API), RG_SET_INVALID);
    CHECK_EQ(set(s, "t.f", "0.25", RG_SRC_API), RG_SET_OK);
    CHECK_STR(val(s, "t.f"), "0.25");
    CHECK_EQ(rg_settings_set_float(s, "t.f", -0.1, RG_SRC_API), RG_SET_INVALID);
    CHECK_EQ(rg_settings_set_float(s, "t.i", 0.1, RG_SRC_API), RG_SET_TYPE);
    /* enum: case-insensitive names, index access */
    CHECK_EQ(set(s, "t.e", "BLUE", RG_SRC_API), RG_SET_OK);
    CHECK_EQ(rg_settings_get_enum(s, "t.e"), 2);
    CHECK_EQ(rg_settings_set_text(s, rg_settings_find(s, "t.e"), "purple", RG_SRC_API, err, sizeof err), RG_SET_INVALID);
    CHECK(strstr(err, "red|green|blue") != NULL);
    CHECK_EQ(rg_settings_set_int(s, "t.e", 0, RG_SRC_API), RG_SET_OK);
    CHECK_STR(val(s, "t.e"), "red");
    CHECK_EQ(rg_settings_set_int(s, "t.e", 3, RG_SRC_API), RG_SET_INVALID);
    /* string + validator normalisation */
    CHECK_EQ(rg_settings_set_string(s, "t.s", "Hello World", RG_SRC_API), RG_SET_OK);
    CHECK_STR(rg_settings_get_string(s, "t.s"), "hello world");
    CHECK_EQ(rg_settings_set_string(s, "t.s", "bad!", RG_SRC_API), RG_SET_INVALID);
    CHECK_STR(rg_settings_get_string(s, "t.s"), "hello world");
    /* binding normalised to canonical text */
    CHECK_EQ(rg_settings_set_string(s, "t.k", "KEY:a ,  pad:A,key:a", RG_SRC_API), RG_SET_OK);
    CHECK_STR(rg_settings_get_string(s, "t.k"), "key:A, pad:a");
    CHECK_EQ(rg_settings_set_string(s, "t.k", "key:A,pad:a", RG_SRC_API), RG_SET_UNCHANGED);
    CHECK_EQ(rg_settings_set_string(s, "t.k", "key:NoSuchKey", RG_SRC_API), RG_SET_INVALID);
    /* unknown / display text / reset */
    CHECK_EQ(rg_settings_set_bool(s, "t.nope", true, RG_SRC_API), RG_SET_UNKNOWN);
    CHECK_EQ(rg_settings_find(s, "t.nope"), -1);
    char d[64];
    rg_settings_display_text(s, rg_settings_find(s, "t.b"), d, sizeof d);
    CHECK_STR(d, "On");
    rg_settings_reset(s, rg_settings_find(s, "t.i"));
    CHECK_EQ(rg_settings_get_int(s, "t.i"), 5);
    CHECK_EQ(rg_settings_source(s, rg_settings_find(s, "t.i")), RG_SRC_DEFAULT);
    rg_settings_reset_all(s);
    CHECK_STR(rg_settings_get_string(s, "t.s"), "abc");
    rg_settings_destroy(s);
    return 0;
}

static int t_ini_parse(void)
{
    rg_settings *s = mk_t();
    const char *text =
        "\xEF\xBB\xBF# comment\n"          /* 1 */
        "t.i = 7   # trailing comment\n"    /* 2 */
        "[t]\n"                             /* 3 */
        "b = no\n"                          /* 4 */
        "f = 0.75\n"                        /* 5 */
        "e = Green\n"                       /* 6 */
        "s = \"  spaced # not a \\\"comment\\\" \"\n" /* 7 */
        "unknown_key = 42\n"                /* 8 */
        "i = 99\n"                          /* 9: invalid -> the default, not line 2 */
        "garbage line\n"                    /* 10 */
        "[other]\r\n"                       /* 11 (CRLF) */
        "x.y = 1\r\n"                       /* 12 */
        "   [ t ]   \n"                     /* 13 */
        "k = pad:a, key:Keypad 8\n";        /* 14 */
    int w = rg_settings_parse(s, text, "test.ini");
    CHECK_EQ(w, 4);
    CHECK_EQ(rg_settings_get_int(s, "t.i"), 5);
    CHECK(strstr(g_warn.all, "test.ini:9: t.i: 99 is outside 0..10; using the default (5)") != NULL);
    CHECK(strstr(g_warn.all, "test.ini:8: unknown setting 't.unknown_key' (kept)") != NULL);
    CHECK(strstr(g_warn.all, "test.ini:10: expected key = value") != NULL);
    CHECK(strstr(g_warn.all, "test.ini:12: unknown setting 'other.x.y' (kept)") != NULL);
    CHECK(!rg_settings_get_bool(s, "t.b"));
    CHECK(fabs(rg_settings_get_float(s, "t.f") - 0.75) < 1e-12);
    CHECK_EQ(rg_settings_get_enum(s, "t.e"), 1);
    CHECK_STR(rg_settings_get_string(s, "t.s"), "  spaced # not a \"comment\" ");
    CHECK_STR(rg_settings_get_string(s, "t.k"), "pad:a, key:Keypad 8");   /* order kept */
    CHECK_EQ(rg_settings_source(s, rg_settings_find(s, "t.b")), RG_SRC_FILE);
    /* unknown keys are written back in their sections; the string is quoted */
    char out[8192];
    rg_settings_format(s, out, sizeof out, RG_FMT_NO_COMMENTS);
    CHECK(strstr(out, "[t]\n") != NULL);
    CHECK(strstr(out, "unknown_key = 42\n") != NULL);
    CHECK(strstr(out, "[other]\nx.y = 1\n") != NULL);
    CHECK(strstr(out, "s = \"  spaced # not a \\\"comment\\\" \"\n") != NULL);
    /* registering a definition later picks the kept value up */
    static const rg_setting_def late = { .id = "t.unknown_key", .type = RG_SET_INT, .def_i = 0, .min_i = 0, .max_i = 100 };
    CHECK_EQ(rg_settings_register(s, &late, 1), 0);
    CHECK_EQ(rg_settings_get_int(s, "t.unknown_key"), 42);
    rg_settings_format(s, out, sizeof out, RG_FMT_NO_COMMENTS);
    CHECK(strstr(out, "unknown_key = 42\n") != NULL);
    /* an empty / comment-only text changes nothing */
    CHECK_EQ(rg_settings_parse(s, "\n# x\n   \n", "empty"), 0);
    rg_settings_destroy(s);
    return 0;
}

static int t_ini_roundtrip(void)
{
    rg_settings *s = mk();
    CHECK_EQ(set(s, "display.window_mode", "fullscreen", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "display.width", "1920", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "display.vsync", "on", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "graphics.gamma", "1.15", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "graphics.lod_bias", "-0.1", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "audio.master_volume", "35", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "audio.device", " Speakers #2 \"USB\" ", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "system.screenshot_dir", "C:\\shots dir", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "input.bind.confirm", "key:Keypad 8, key:comma, mouse:left, pad:a, axis:righttrigger+", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "input.bind.cancel", "", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(set(s, "input.sensitivity_camera", "0.3333333333333333", RG_SRC_MENU), RG_SET_OK);
    rg_settings_parse(s, "[future]\nthing = \"a # b\"\n", "extra");
    size_t n = rg_settings_format(s, NULL, 0, 0);
    char *a = (char *)malloc(n + 1), *b = (char *)malloc(n + 1);
    CHECK_EQ(rg_settings_format(s, a, n + 1, 0), n);
    CHECK_EQ(strlen(a), n);
    rg_settings *t = mk();
    CHECK_EQ(rg_settings_parse(t, a, "roundtrip"), 1);   /* only future.thing warns */
    size_t m = rg_settings_format(t, b, n + 1, 0);
    CHECK_EQ(m, n);
    CHECK(memcmp(a, b, n) == 0);
    for (int i = 0; i < rg_settings_count(s); i++) {
        char x[1024], y[1024];
        rg_settings_value_text(s, i, x, sizeof x);
        rg_settings_value_text(t, i, y, sizeof y);
        if (strcmp(x, y)) { CHECK_STR(y, x); break; }
    }
    CHECK_STR(rg_settings_get_string(t, "audio.device"), " Speakers #2 \"USB\" ");
    CHECK(rg_settings_get_float(t, "input.sensitivity_camera") == rg_settings_get_float(s, "input.sensitivity_camera"));
    /* CHANGED_ONLY: exactly the 11 changed settings + the kept unknown */
    char c[8192];
    rg_settings_format(s, c, sizeof c, RG_FMT_CHANGED_ONLY | RG_FMT_NO_COMMENTS);
    int lines = 0;
    for (const char *p = c; (p = strstr(p, " = ")) != NULL; p += 3) lines++;
    CHECK_EQ(lines, 12);
    rg_settings *u = mk();
    rg_settings_parse(u, c, "changed");
    for (int i = 0; i < rg_settings_count(s); i++) {
        char x[1024], y[1024];
        rg_settings_value_text(s, i, x, sizeof x);
        rg_settings_value_text(u, i, y, sizeof y);
        if (strcmp(x, y)) { CHECK_STR(y, x); break; }
    }
    /* truncated output stays NUL-terminated and reports the full length */
    char small[40];
    CHECK_EQ(rg_settings_format(s, small, sizeof small, 0), n);
    CHECK_EQ(strlen(small), sizeof small - 1);
    free(a);
    free(b);
    rg_settings_destroy(s);
    rg_settings_destroy(t);
    rg_settings_destroy(u);
    return 0;
}

static int t_presets(void)
{
    rg_settings *s = mk();
    CHECK(rg_settings_matches_preset(s, "default"));
    CHECK(!rg_settings_matches_preset(s, "original"));
    CHECK_EQ(rg_settings_preset_count(s), 2);
    CHECK_STR(rg_settings_preset_name(s, 0), "original");
    CHECK_EQ(rg_settings_apply_preset(s, "original"), 0);
    CHECK(rg_settings_matches_preset(s, "original"));
    CHECK(!rg_settings_matches_preset(s, "default"));
    CHECK_STR(val(s, "graphics.internal_res"), "native");
    CHECK_STR(val(s, "graphics.anisotropic"), "off");
    CHECK_STR(val(s, "gameplay.skip_seen_movies"), "false");
    CHECK_STR(val(s, "display.scale"), "linear");
    CHECK_STR(val(s, "audio.master_volume"), "100");
    CHECK_EQ(rg_settings_source(s, rg_settings_find(s, "display.scale")), RG_SRC_PRESET);
    CHECK_EQ(rg_settings_apply_preset(s, "Default"), 0);
    CHECK(rg_settings_matches_preset(s, "default"));
    CHECK_STR(val(s, "graphics.internal_res"), "window");
    CHECK_EQ(rg_settings_apply_preset(s, "nope"), -1);
    /* user presets */
    char err[256] = "";
    CHECK_EQ(rg_settings_add_preset(s, "quiet", "Quiet", "display.vsync = true\n[audio]\nmaster_volume = 20\n",
                                    err, sizeof err), 0);
    CHECK_EQ(rg_settings_add_preset(s, "quiet", "again", "", err, sizeof err), -1);
    CHECK_EQ(rg_settings_add_preset(s, "original", "x", "", err, sizeof err), -1);
    CHECK_EQ(rg_settings_add_preset(s, "bad", "x", "[audio]\nmaster_volume = 200\n", err, sizeof err), -1);
    CHECK(strstr(err, "bad:2: audio.master_volume: 200 is outside 0..100") != NULL);
    CHECK_EQ(rg_settings_add_preset(s, "bad2", "x", "nope.x = 1\n", err, sizeof err), -1);
    CHECK(strstr(err, "unknown setting 'nope.x'") != NULL);
    CHECK_EQ(rg_settings_preset_count(s), 3);
    CHECK_STR(rg_settings_preset_label(s, 2), "Quiet");
    CHECK_EQ(set(s, "display.scale", "nearest", RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(rg_settings_apply_preset(s, "quiet"), 0);
    CHECK_EQ(rg_settings_get_int(s, "audio.master_volume"), 20);
    CHECK(rg_settings_get_bool(s, "display.vsync"));
    CHECK_STR(val(s, "display.scale"), "linear");     /* not named -> default */
    CHECK(rg_settings_matches_preset(s, "quiet"));
    /* "preset =" in a file applies at that point; later lines win */
    rg_settings_parse(s, "preset = original\n[graphics]\nanisotropic = 4x\n", "p.ini");
    CHECK_STR(val(s, "graphics.internal_res"), "native");
    CHECK_STR(val(s, "graphics.anisotropic"), "4x");
    CHECK_EQ(rg_settings_get_int(s, "audio.master_volume"), 100);
    CHECK(!rg_settings_matches_preset(s, "original"));
    /* gameplay options are off in Original */
    for (int i = 0; i < rg_settings_count(s); i++) {
        const rg_setting_def *d = rg_settings_def(s, i);
        if (!(d->flags & RG_SETF_GAMEPLAY)) continue;
        CHECK(d->flags & RG_SETF_HAS_ORIGINAL);
        CHECK_EQ(d->orig_i, 0);
    }
    rg_settings_destroy(s);
    return 0;
}

static int t_cmdline(void)
{
    rg_settings *s = mk();
    char path[600];
    outpath(path, sizeof path, "cmdline.ini");
    spit(path, "[audio]\nmaster_volume = 70\n[display]\nscale = nearest\n");
    char *argv[] = { "prog", "--set", "display.vsync=true", "--foo", "--set=audio.master_volume=50", "bar",
                     "--preset", "original", "--set", "nope.x=1", "--set", "Audio.Master_Volume = 500",
                     "--settings", path, "--set", "display.width=\"1600\"", NULL };
    int argc = 16, errors = -1;
    const char *sp = NULL;
    int n = rg_settings_apply_args(s, argc, argv, &errors, &sp);
    CHECK_EQ(n, 3);
    CHECK_STR(argv[0], "prog");
    CHECK_STR(argv[1], "--foo");
    CHECK_STR(argv[2], "bar");
    CHECK(argv[3] == NULL);
    CHECK_EQ(errors, 2);
    CHECK(sp == path);
    CHECK(strstr(g_warn.all, "--set: unknown setting 'nope.x'") != NULL);
    CHECK(strstr(g_warn.all, "--set audio.master_volume: 500 is outside 0..100 (ignored)") != NULL);
    /* overrides survive the later preset and the later file */
    CHECK(rg_settings_get_bool(s, "display.vsync"));
    CHECK(rg_settings_overridden(s, rg_settings_find(s, "display.vsync")));
    CHECK_EQ(rg_settings_get_int(s, "audio.master_volume"), 50);
    CHECK_STR(pval(s, "audio.master_volume"), "70");
    CHECK_STR(pval(s, "display.vsync"), "false");
    CHECK_STR(val(s, "display.scale"), "nearest");
    CHECK_STR(val(s, "graphics.internal_res"), "native");
    CHECK_EQ(rg_settings_get_int(s, "display.width"), 1600);
    CHECK_EQ(rg_settings_source(s, rg_settings_find(s, "display.width")), RG_SRC_CMDLINE);
    /* the file layer is what gets saved */
    char out[16384];
    rg_settings_format(s, out, sizeof out, RG_FMT_NO_COMMENTS);
    CHECK(strstr(out, "master_volume = 70\n") != NULL);
    CHECK(strstr(out, "vsync = false\n") != NULL);
    CHECK(strstr(out, "width = 1280\n") != NULL);
    /* a menu change replaces the override */
    CHECK_EQ(rg_settings_set_int(s, "audio.master_volume", 40, RG_SRC_MENU), RG_SET_OK);
    CHECK(!rg_settings_overridden(s, rg_settings_find(s, "audio.master_volume")));
    CHECK_STR(pval(s, "audio.master_volume"), "40");
    /* clear_overrides falls back to the persistent layer */
    rg_settings_clear_overrides(s);
    CHECK(!rg_settings_get_bool(s, "display.vsync"));
    CHECK_EQ(rg_settings_get_int(s, "display.width"), 1280);
    /* override() alone; missing value; no args */
    CHECK_EQ(rg_settings_override(s, "display.vsync"), RG_SET_INVALID);
    CHECK_EQ(rg_settings_override(s, " display.vsync = on "), RG_SET_OK);
    CHECK(rg_settings_get_bool(s, "display.vsync"));
    char *argv2[] = { "prog", "--set", NULL };
    CHECK_EQ(rg_settings_apply_args(s, 2, argv2, &errors, NULL), 1);
    CHECK_EQ(errors, 1);
    /* a missing --settings file is not an error (first run) */
    char missing[600];
    outpath(missing, sizeof missing, "does-not-exist.ini");
    char *argv3[] = { "prog", "--settings", missing, NULL };
    CHECK_EQ(rg_settings_apply_args(s, 3, argv3, &errors, &sp), 1);
    CHECK_EQ(errors, 0);
    CHECK_STR(sp, missing);
    rg_settings_destroy(s);
    return 0;
}

typedef struct cbrec { int calls; int last; int per[512]; } cbrec;
static void on_change(rg_settings *s, int idx, void *user)
{
    (void)s;
    cbrec *r = (cbrec *)user;
    r->calls++;
    r->last = idx;
    if (idx >= 0 && idx < 512) r->per[idx]++;
}

static int t_change_tracking(void)
{
    rg_settings *s = mk();
    static cbrec r;
    memset(&r, 0, sizeof r);
    CHECK_EQ(rg_settings_on_change(s, on_change, &r), 0);
    uint64_t g0 = rg_settings_generation(s);
    int vs = rg_settings_find(s, "display.vsync");
    CHECK_EQ(rg_settings_set_bool(s, "display.vsync", false, RG_SRC_API), RG_SET_UNCHANGED);
    CHECK_EQ(r.calls, 0);
    CHECK_EQ(rg_settings_set_bool(s, "display.vsync", true, RG_SRC_API), RG_SET_OK);
    CHECK_EQ(r.calls, 1);
    CHECK_EQ(r.last, vs);
    CHECK_EQ(rg_settings_generation(s), g0 + 1);
    CHECK_EQ(rg_settings_override(s, "display.vsync=true"), RG_SET_OK);   /* same value: no event */
    CHECK_EQ(r.calls, 1);
    /* a file value under an override does not change the effective value */
    rg_settings_parse(s, "[display]\nvsync = false\n", "f");
    CHECK_EQ(r.calls, 1);
    /* preset: one event per setting that changed */
    memset(&r, 0, sizeof r);
    rg_settings_apply_preset(s, "original");
    int expect = 0;
    rg_settings *ref = mk();
    for (int i = 0; i < rg_settings_count(ref); i++) {
        char a[256], b[256];
        rg_settings_value_text(ref, i, a, sizeof a);
        rg_settings_value_text(s, i, b, sizeof b);
        if (strcmp(a, b)) expect++;
    }
    rg_settings_destroy(ref);
    CHECK_EQ(r.calls, expect - 1);   /* vsync stays overridden (true) and is not reported */
    CHECK(expect >= 4);
    /* restart pending */
    int pend[8];
    CHECK_EQ(rg_settings_restart_pending(s, pend, 8), 0);   /* no snapshot yet */
    rg_settings_mark_applied(s);
    CHECK_EQ(rg_settings_set_bool(s, "audio.enabled", false, RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(rg_settings_restart_pending(s, pend, 8), 1);
    CHECK_EQ(pend[0], rg_settings_find(s, "audio.enabled"));
    CHECK_EQ(rg_settings_set_int(s, "audio.master_volume", 10, RG_SRC_MENU), RG_SET_OK);  /* live */
    CHECK_EQ(rg_settings_restart_pending(s, pend, 8), 1);
    CHECK_EQ(rg_settings_set_bool(s, "audio.enabled", true, RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(rg_settings_restart_pending(s, pend, 8), 0);
    rg_settings_destroy(s);
    return 0;
}

static int t_display_trial(void)
{
    rg_settings *s = mk();
    static cbrec r;
    memset(&r, 0, sizeof r);
    rg_settings_on_change(s, on_change, &r);
    int sc = rg_settings_find(s, "display.scale");
    /* revert on timeout */
    CHECK_EQ(rg_settings_trial_begin(s, sc, 1000, 15000), 0);
    CHECK_EQ(rg_settings_step(s, sc, 1), RG_SET_OK);
    CHECK_STR(val(s, "display.scale"), "nearest");
    CHECK(rg_settings_trial_active(s));
    CHECK_EQ(rg_settings_trial_remaining(s, 1000), 15000);
    CHECK_EQ(rg_settings_trial_remaining(s, 15999), 1);
    CHECK_EQ(rg_settings_tick(s, 15999), 0);
    CHECK_EQ(rg_settings_tick(s, 16000), 1);
    CHECK_STR(val(s, "display.scale"), "linear");
    CHECK_STR(pval(s, "display.scale"), "linear");
    CHECK(!rg_settings_trial_active(s));
    CHECK_EQ(r.per[sc], 2);
    /* a second begin extends the trial and keeps the OLDEST values */
    rg_settings_trial_begin(s, sc, 0, 15000);
    rg_settings_step(s, sc, 1);
    int ws = rg_settings_find(s, "display.window_mode");
    rg_settings_trial_begin(s, ws, 5000, 15000);
    rg_settings_step(s, ws, 1);
    rg_settings_trial_begin(s, sc, 6000, 15000);
    rg_settings_step(s, sc, 1);
    CHECK_STR(val(s, "display.scale"), "integer");
    CHECK_STR(val(s, "display.window_mode"), "fullscreen");
    CHECK_EQ(rg_settings_tick(s, 20999), 0);
    CHECK_EQ(rg_settings_tick(s, 21000), 1);
    CHECK_STR(val(s, "display.scale"), "linear");
    CHECK_STR(val(s, "display.window_mode"), "windowed");
    /* confirm keeps */
    rg_settings_trial_begin(s, sc, 0, 15000);
    rg_settings_step(s, sc, -1);
    CHECK_STR(val(s, "display.scale"), "stretch");   /* wraps backwards */
    rg_settings_trial_confirm(s);
    CHECK_EQ(rg_settings_tick(s, 1000000), 0);
    CHECK_STR(pval(s, "display.scale"), "stretch");
    /* an override is restored by a revert */
    rg_settings_override(s, "display.vsync=true");
    int vs = rg_settings_find(s, "display.vsync");
    rg_settings_trial_begin(s, vs, 0, 100);
    rg_settings_step(s, vs, 1);
    CHECK(!rg_settings_get_bool(s, "display.vsync"));
    CHECK(!rg_settings_overridden(s, vs));
    rg_settings_trial_revert(s);
    CHECK(rg_settings_get_bool(s, "display.vsync"));
    CHECK(rg_settings_overridden(s, vs));
    CHECK_STR(pval(s, "display.vsync"), "false");
    /* step: int clamps, float snaps to its grid, enum wraps, text is a no-op */
    int vol = rg_settings_find(s, "audio.master_volume");
    CHECK_EQ(rg_settings_step(s, vol, 1), RG_SET_UNCHANGED);
    CHECK_EQ(rg_settings_step(s, vol, -1), RG_SET_OK);
    CHECK_EQ(rg_settings_get_int(s, "audio.master_volume"), 95);
    int dz = rg_settings_find(s, "input.deadzone_move");
    for (int i = 0; i < 3; i++) rg_settings_step(s, dz, 1);
    CHECK_STR(val(s, "input.deadzone_move"), "0.4");
    for (int i = 0; i < 40; i++) rg_settings_step(s, dz, -1);
    CHECK_STR(val(s, "input.deadzone_move"), "0");
    CHECK_EQ(rg_settings_step(s, rg_settings_find(s, "input.bind.confirm"), 1), RG_SET_TYPE);
    rg_settings_destroy(s);
    return 0;
}

static int t_save_load(void)
{
    rg_settings *s = mk();
    char path[600], tmp[620];
    outpath(path, sizeof path, "save.ini");
    snprintf(tmp, sizeof tmp, "%s.tmp", path);
    remove(path);
    set(s, "display.scale", "integer", RG_SRC_MENU);
    set(s, "input.bind.menu", "key:F, pad:y", RG_SRC_MENU);
    set(s, "audio.master_volume", "65", RG_SRC_MENU);
    rg_settings_override(s, "audio.master_volume=5");
    CHECK_EQ(rg_settings_save(s, path, 0), 0);
    FILE *f = fopen(tmp, "rb");
    CHECK(f == NULL);
    if (f) fclose(f);
    set(s, "display.vsync", "true", RG_SRC_MENU);
    CHECK_EQ(rg_settings_save(s, path, 0), 0);    /* replaces an existing file */
    rg_settings *t = mk();
    CHECK_EQ(rg_settings_load(t, path), 0);
    CHECK_EQ(g_warn.n, 0);
    CHECK_STR(val(t, "display.scale"), "integer");
    CHECK_STR(val(t, "input.bind.menu"), "key:F, pad:y");
    CHECK_EQ(rg_settings_get_int(t, "audio.master_volume"), 65);   /* not the override */
    CHECK(rg_settings_get_bool(t, "display.vsync"));
    char *text = slurp(path);
    CHECK(text && strstr(text, "# Scaling: how the 4:3 frame fills the window\n") != NULL);
    CHECK(text && strstr(text, "[planned: no effect yet]") != NULL);
    free(text);
    /* a missing file is fine; a directory is not a readable file */
    char missing[600];
    outpath(missing, sizeof missing, "missing.ini");
    remove(missing);
    CHECK_EQ(rg_settings_load(t, missing), 0);
    rg_settings_destroy(s);
    rg_settings_destroy(t);
    return 0;
}

static int t_core_defs(void)
{
    rg_settings *s = mk();
    const char *cats[32];
    int nc = rg_settings_categories(s, cats, 32);
    const char *want[] = { "display", "graphics", "audio", "gameplay", "system", "controls", "controls_ui" };
    for (size_t w = 0; w < sizeof want / sizeof want[0]; w++) {
        int found = 0;
        for (int i = 0; i < nc; i++) if (!strcmp(cats[i], want[w])) found = 1;
        if (!found) fprintf(stderr, "missing category %s\n", want[w]);
        CHECK(found);
    }
    for (int i = 0; i < rg_settings_count(s); i++) {
        const rg_setting_def *d = rg_settings_def(s, i);
        char t[1024];
        rg_settings_default_text(s, i, t, sizeof t);
        /* the default text parses back to the same value */
        CHECK_EQ(rg_settings_set_text(s, i, t, RG_SRC_API, NULL, 0), RG_SET_UNCHANGED);
        CHECK(d->label != NULL);
        /* graphics settings: the renderer-side ones are real (docs/GPU.md
         * "Graphics settings"); the ones that need game-side work are still
         * planned */
        if (!strncmp(d->id, "graphics.", 9)) {
            /* graphics.aspect / movie_aspect: real since widescreen stage 0 (docs/WIDESCREEN.md) */
            static const char *const planned[] = { "graphics.bloom", "graphics.depth_of_field",
                                                   "graphics.motion_blur", "graphics.lod_bias",
                                                   "graphics.shadow_res" };
            int want = 0;
            for (size_t k = 0; k < sizeof planned / sizeof planned[0]; k++)
                if (!strcmp(d->id, planned[k])) want = 1;
            CHECK_EQ((d->flags & RG_SETF_PLACEHOLDER) != 0, want);
        }
    }
    /* the knobs the host / runtime had */
    const char *ids[] = { "display.window_mode", "display.width", "display.height", "display.scale",
                          "display.vsync", "audio.enabled", "audio.master_volume", "system.throttle",
                          "system.screenshot_dir", "input.players", "input.vibration" };
    for (size_t i = 0; i < sizeof ids / sizeof ids[0]; i++) CHECK(rg_settings_find(s, ids[i]) >= 0);
    /* display.scale names are rg_scale_mode's order */
    for (int m = 0; m < 4; m++) {
        CHECK_EQ(rg_settings_set_text(s, rg_settings_find(s, "display.scale"), rg_scale_name((rg_scale_mode)m),
                                      RG_SRC_API, NULL, 0) >= 0, 1);
        CHECK_EQ(rg_settings_get_enum(s, "display.scale"), m);
    }
    /* host config from settings */
    rg_host_config hc;
    rg_host_config_default(&hc);
    set(s, "display.window_mode", "fullscreen", RG_SRC_API);
    set(s, "display.width", "800", RG_SRC_API);
    set(s, "display.height", "600", RG_SRC_API);
    set(s, "display.scale", "integer", RG_SRC_API);
    set(s, "display.vsync", "on", RG_SRC_API);
    set(s, "audio.enabled", "off", RG_SRC_API);
    set(s, "system.screenshot_dir", "shots", RG_SRC_API);
    rg_host_config_from_settings(&hc, s);
    CHECK_EQ(hc.fullscreen, 1);
    CHECK_EQ(hc.win_w, 800);
    CHECK_EQ(hc.win_h, 600);
    CHECK_EQ(hc.scale, RG_SCALE_INTEGER);
    CHECK_EQ(hc.vsync, 1);
    CHECK_EQ(hc.audio, 0);
    CHECK_STR(hc.screenshot_dir, "shots");
    /* program flags applied after from_settings become overrides (not saved) */
    hc.scale = RG_SCALE_STRETCH;
    hc.fullscreen = 0;
    rg_host_settings_from_config(s, &hc);
    CHECK_STR(val(s, "display.scale"), "stretch");
    CHECK_STR(pval(s, "display.scale"), "integer");
    CHECK(rg_settings_overridden(s, rg_settings_find(s, "display.scale")));
    CHECK_STR(val(s, "display.window_mode"), "windowed");
    CHECK(!rg_settings_overridden(s, rg_settings_find(s, "display.vsync")));   /* agreed: untouched */
    hc.headless = 1;
    rg_host *h = rg_host_create(&hc);
    CHECK(h != NULL);
    if (h) {
        rg_host_attach_settings(h, s, NULL);
        CHECK_EQ(rg_host_scale(h), RG_SCALE_STRETCH);
        CHECK_EQ(rg_host_fullscreen(h), 0);
        set(s, "audio.master_volume", "25", RG_SRC_MENU);   /* applied on the next pump */
        rg_host_attach_settings(h, s, NULL);
        CHECK(fabsf(rg_host_volume(h) - 0.25f) < 1e-6f);
        rg_host_destroy(h);
    }
    rg_settings_destroy(s);
    return 0;
}

/* ================================================================ menu */
/* One UI "press": hold the source for one update, then release. */
typedef struct uienv {
    rg_settings *s;
    rg_actions a;
    rg_menu m;
    rg_ui_nav nav;
    uint64_t t;
    int kb;           /* 1 = keyboard, 0 = gamepad */
    rg_bind_capture cap;   /* the host's rebinding detector, driven as host_sdl.c does */
} uienv;

/* As the host: start / stop the detector to match the menu. */
static void cap_sync(uienv *e, const rg_gamepad_snap *pads, int npads)
{
    if (!e->cap.ncancel) rg_capture_init(&e->cap);
    bool on = rg_menu_capturing(&e->m);
    if (on && e->cap.state != RG_CAPTURE_WAITING) {
        if (rg_menu_capturing_motion(&e->m)) rg_capture_begin_motion(&e->cap);
        else rg_capture_begin(&e->cap, pads, npads);
    }
    else if (!on && e->cap.state != RG_CAPTURE_IDLE) rg_capture_end(&e->cap);
}

/* As the host: hand a finished capture to the menu. */
static void cap_finish(uienv *e)
{
    char t[96];
    if (e->cap.state == RG_CAPTURE_DONE) {
        rg_capture_text(&e->cap, t, sizeof t);
        rg_menu_capture_input(&e->m, t, e->t);
    } else if (e->cap.state == RG_CAPTURE_CANCELLED) {
        rg_menu_capture_input(&e->m, NULL, e->t);
    } else {
        return;
    }
    rg_capture_end(&e->cap);
}

/* Live press events during a capture (the event path of rg_host_pump). */
static void cap_key(uienv *e, int sc) { cap_sync(e, NULL, 0); rg_capture_key(&e->cap, sc); cap_finish(e); }
static void cap_button(uienv *e, int b) { cap_sync(e, NULL, 0); rg_capture_pad_button(&e->cap, b); cap_finish(e); }
static void cap_axis(uienv *e, int axis, int16_t v) { cap_sync(e, NULL, 0); rg_capture_pad_axis(&e->cap, 0, axis, v); cap_finish(e); }
static void cap_motion(uienv *e, float dx, float dy) { cap_sync(e, NULL, 0); rg_capture_mouse_motion(&e->cap, dx, dy); cap_finish(e); }

static void ui_feed(uienv *e, int code, int axis, int16_t axis_value)
{
    static bool keys[SDL_SCANCODE_COUNT];
    rg_gamepad_snap pad;
    memset(keys, 0, sizeof keys);
    memset(&pad, 0, sizeof pad);
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    if (e->kb) {
        if (code >= 0) keys[code] = true;
        in.keys = keys;
        in.nkeys = SDL_SCANCODE_COUNT;
    } else {
        if (code >= 0) pad.button[code] = 1;
        if (axis >= 0) pad.axis[axis] = axis_value;
        in.pads = &pad;
        in.npads = 1;
    }
    int32_t v[RG_ACT_COUNT];
    rg_actions_values(&e->a, &in, v);
    /* the game never sees UI-only presses as game buttons? (checked elsewhere) */
    int fired[RG_ACT_COUNT - RG_ACT_GAME_COUNT];
    int n = rg_ui_nav_update(&e->nav, v, e->t, fired);
    bool quiet = rg_menu_capturing(&e->m);   /* the host drops nav commands while capturing */
    for (int i = 0; i < n && !quiet; i++) {
        static const rg_menu_cmd map[] = { RG_MENU_UP, RG_MENU_DOWN, RG_MENU_LEFT, RG_MENU_RIGHT,
                                           RG_MENU_ACCEPT, RG_MENU_BACK, RG_MENU_PAGE_PREV,
                                           RG_MENU_PAGE_NEXT, RG_MENU_TOGGLE };
        rg_menu_cmd c = map[fired[i] - RG_ACT_GAME_COUNT];
        if (c != RG_MENU_TOGGLE && !e->m.open) continue;
        rg_menu_command(&e->m, c, e->t);
        if (rg_menu_capturing(&e->m)) break;
    }
    rg_menu_tick(&e->m, e->t);
    cap_sync(e, e->kb ? NULL : &pad, e->kb ? 0 : 1);
    e->t += 50;
}

static void ui_press(uienv *e, int code)
{
    ui_feed(e, code, -1, 0);
    ui_feed(e, -1, -1, 0);
}

/* UI sources per command for the two devices */
enum { U_UP, U_DOWN, U_LEFT, U_RIGHT, U_ACCEPT, U_BACK, U_PREV, U_NEXT, U_TOGGLE };
static const int k_kb_src[] = { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT,
                                SDL_SCANCODE_RETURN, SDL_SCANCODE_ESCAPE, SDL_SCANCODE_PAGEUP,
                                SDL_SCANCODE_PAGEDOWN, SDL_SCANCODE_F1 };
static const int k_pad_src[] = { SDL_GAMEPAD_BUTTON_DPAD_UP, SDL_GAMEPAD_BUTTON_DPAD_DOWN,
                                 SDL_GAMEPAD_BUTTON_DPAD_LEFT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT,
                                 SDL_GAMEPAD_BUTTON_SOUTH, SDL_GAMEPAD_BUTTON_EAST,
                                 SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER,
                                 SDL_GAMEPAD_BUTTON_GUIDE };

static void cmd(uienv *e, int u) { ui_press(e, e->kb ? k_kb_src[u] : k_pad_src[u]); }

/* Navigate to setting idx with UI commands only; returns 0 when the cursor is
 * on it. */
static int go_to(uienv *e, int idx)
{
    if (!e->m.open) cmd(e, U_TOGGLE);
    if (!e->m.open) return -1;
    const char *cat = rg_settings_category(e->s, idx);
    for (int i = 0; i < RG_MENU_MAX_PAGES && strcmp(e->m.pages[e->m.page], cat); i++) cmd(e, U_NEXT);
    if (strcmp(e->m.pages[e->m.page], cat)) return -1;
    int rows[RG_MENU_MAX_ROWS];
    int n = rg_menu_rows(&e->m, rows, RG_MENU_MAX_ROWS);
    for (int i = 0; i < n + 1; i++) {
        if (rows[e->m.cursor] == idx) return 0;
        cmd(e, U_DOWN);
    }
    return -1;
}

static int menu_every_setting(int kb)
{
    uienv e;
    memset(&e, 0, sizeof e);
    e.s = mk();
    e.kb = kb;
    rg_actions_from_settings(&e.a, e.s);
    rg_menu_init(&e.m, e.s);
    rg_ui_nav_init(&e.nav);
    int changed = 0, visited = 0;
    for (int i = 0; i < rg_settings_count(e.s); i++) {
        const rg_setting_def *d = rg_settings_def(e.s, i);
        if (d->flags & RG_SETF_HIDDEN) continue;
        visited++;
        if (go_to(&e, i)) { fprintf(stderr, "cannot reach %s\n", d->id); CHECK(!"reach"); continue; }
        char before[1024], after[1024];
        rg_settings_value_text(e.s, i, before, sizeof before);
        if (d->type == RG_SET_STRING) {
            /* text entry: typed on the keyboard, or picked on the on-screen selector */
            cmd(&e, U_ACCEPT);
            CHECK(rg_menu_text_editing(&e.m));
            if (kb) {
                rg_menu_text_input(&e.m, "x");
                rg_menu_text_key(&e.m, RG_TEXT_COMMIT);
            } else {
                cmd(&e, U_ACCEPT);            /* 'a' (row 0, column 0) */
                cmd(&e, U_UP);                /* wraps to the Space/Delete/Clear/OK/Cancel row */
                for (int r = 0; r < 3; r++) cmd(&e, U_RIGHT);
                cmd(&e, U_ACCEPT);            /* OK */
            }
            CHECK(!rg_menu_text_editing(&e.m));
            rg_settings_value_text(e.s, i, after, sizeof after);
            if (strcmp(before, after)) changed++;
            else { fprintf(stderr, "cannot type into %s (%s)\n", d->id, e.m.status); CHECK(!"text"); }
            continue;
        }
        if (d->type == RG_SET_BINDING && kb && !strcmp(d->id, "input.overlay_chord")) {
            /* gamepad buttons only (a key is refused): from the keyboard,
             * remove one (row 0, Remove) */
            cmd(&e, U_ACCEPT);
            CHECK_EQ(e.m.view, RG_MENU_VIEW_BINDINGS);
            cmd(&e, U_RIGHT);
            cmd(&e, U_ACCEPT);
            cmd(&e, U_BACK);
            CHECK_EQ(e.m.view, RG_MENU_VIEW_PAGE);
            rg_settings_value_text(e.s, i, after, sizeof after);
            if (strcmp(before, after)) changed++;
            else { fprintf(stderr, "cannot edit %s (%s)\n", d->id, e.m.status); CHECK(!"chord"); }
            continue;
        }
        if (d->type == RG_SET_BINDING) {
            /* rebinding: open the editor, "Add a binding", press something new */
            cmd(&e, U_ACCEPT);
            CHECK_EQ(e.m.view, RG_MENU_VIEW_BINDINGS);
            rg_binding b[RG_BIND_MAX];
            int nb = rg_binding_parse_list(rg_settings_get_string(e.s, d->id), b, NULL, 0);
            for (int r = 0; r < nb; r++) cmd(&e, U_DOWN);
            cmd(&e, U_ACCEPT);
            CHECK(rg_menu_capturing(&e.m));
            if (kb) cap_key(&e, SDL_SCANCODE_F13);
            else cap_button(&e, SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1);
            CHECK(!rg_menu_capturing(&e.m));
            cmd(&e, U_BACK);
            CHECK_EQ(e.m.view, RG_MENU_VIEW_PAGE);
            rg_settings_value_text(e.s, i, after, sizeof after);
            if (strcmp(before, after)) changed++;
            else { fprintf(stderr, "cannot rebind %s (%s)\n", d->id, e.m.status); CHECK(!"bind"); }
            continue;
        }
        cmd(&e, U_RIGHT);
        rg_settings_value_text(e.s, i, after, sizeof after);
        if (!strcmp(before, after)) {   /* at the top of its range */
            cmd(&e, U_LEFT);
            rg_settings_value_text(e.s, i, after, sizeof after);
        }
        if (!strcmp(before, after)) { fprintf(stderr, "cannot change %s\n", d->id); CHECK(!"change"); continue; }
        if (d->flags & RG_SETF_DISPLAY) {
            CHECK(rg_settings_trial_active(e.s));
            cmd(&e, U_ACCEPT);   /* keep */
            CHECK(!rg_settings_trial_active(e.s));
        }
        rg_settings_value_text(e.s, i, after, sizeof after);
        if (strcmp(before, after)) changed++;
        else { fprintf(stderr, "%s reverted\n", d->id); CHECK(!"kept"); }
    }
    CHECK(visited > 60);   /* every visible setting, bindings and strings included */
    CHECK_EQ(changed, visited);
    /* display trial: back reverts, and an unconfirmed change reverts on time */
    int sc = rg_settings_find(e.s, "display.scale");
    char v0[64];
    rg_settings_value_text(e.s, sc, v0, sizeof v0);
    CHECK_EQ(go_to(&e, sc), 0);
    cmd(&e, U_RIGHT);
    CHECK(strcmp(val(e.s, "display.scale"), v0) != 0);
    cmd(&e, U_DOWN);                        /* ignored during a trial */
    { int rows[RG_MENU_MAX_ROWS]; rg_menu_rows(&e.m, rows, RG_MENU_MAX_ROWS); CHECK_EQ(rows[e.m.cursor], sc); }
    cmd(&e, U_BACK);
    CHECK_STR(val(e.s, "display.scale"), v0);
    CHECK(e.m.open);                        /* BACK ended the trial, did not close */
    cmd(&e, U_RIGHT);
    e.t += 15000;
    ui_feed(&e, -1, -1, 0);
    CHECK_STR(val(e.s, "display.scale"), v0);
    CHECK(strstr(e.m.status, "not confirmed") != NULL);
    /* presets page: apply Original with accept */
    for (int i = 0; i < RG_MENU_MAX_PAGES && strcmp(e.m.pages[e.m.page], "presets"); i++) cmd(&e, U_PREV);
    CHECK_STR(e.m.pages[e.m.page], "presets");
    cmd(&e, U_ACCEPT);
    CHECK(rg_settings_matches_preset(e.s, "original"));
    rg_menu_line lines[RG_MENU_MAX_ROWS + 8];
    int nl = rg_menu_render(&e.m, e.t, lines, RG_MENU_MAX_ROWS + 8);
    CHECK(nl >= 4);
    int active = 0;
    for (int i = 0; i < nl; i++) if (strstr(lines[i].text, "Original (PS2)  (active)")) active = 1;
    CHECK(active);
    /* back closes; toggle reopens */
    cmd(&e, U_BACK);
    CHECK(!e.m.open);
    CHECK_EQ(rg_menu_render(&e.m, e.t, lines, 8), 0);
    cmd(&e, U_TOGGLE);
    CHECK(e.m.open);
    rg_settings_destroy(e.s);
    return 0;
}

static int t_menu_keyboard(void) { return menu_every_setting(1); }

static int t_menu_gamepad(void)
{
    menu_every_setting(0);
    /* the left stick navigates too, with auto-repeat */
    uienv e;
    memset(&e, 0, sizeof e);
    e.s = mk();
    rg_actions_from_settings(&e.a, e.s);
    rg_menu_init(&e.m, e.s);
    rg_ui_nav_init(&e.nav);
    e.kb = 0;
    cmd(&e, U_TOGGLE);
    CHECK(e.m.open);
    CHECK_EQ(e.m.cursor, 0);
    ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 30000);   /* t=100: press -> 1 */
    CHECK_EQ(e.m.cursor, 1);
    for (int i = 0; i < 7; i++) ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 30000);  /* up to t+350: no repeat */
    CHECK_EQ(e.m.cursor, 1);
    ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 30000);   /* t+400: repeat */
    CHECK_EQ(e.m.cursor, 2);
    ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 30000);   /* +450: < rate 90 */
    CHECK_EQ(e.m.cursor, 2);
    ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 30000);   /* +500: repeat */
    CHECK_EQ(e.m.cursor, 3);
    ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 5000);    /* under the threshold: released */
    ui_feed(&e, -1, SDL_GAMEPAD_AXIS_LEFTY, 5000);
    CHECK_EQ(e.m.cursor, 3);
    rg_settings_destroy(e.s);
    return 0;
}

static int t_invalid_control(void)
{
    rg_settings *s = mk();
    rg_settings_parse(s, "[audio]\nmaster_volume = 150\n", "control");
    CHECK_EQ(rg_settings_get_int(s, "audio.master_volume"), 150);   /* must fail: it falls back to 100 */
    rg_settings_destroy(s);
    return 0;
}

/* ================================================================ input */
static bool g_keys[SDL_SCANCODE_COUNT];

static void keys_clear(void) { memset(g_keys, 0, sizeof g_keys); }

static rg_pad eval_keys(const rg_actions *a, const int *sc, int n)
{
    keys_clear();
    for (int i = 0; i < n; i++) g_keys[sc[i]] = true;
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.keys = g_keys;
    in.nkeys = SDL_SCANCODE_COUNT;
    rg_pad p;
    rg_actions_eval(a, &in, &p);
    return p;
}

static rg_pad eval_key(const rg_actions *a, int sc) { return eval_keys(a, &sc, 1); }

static rg_pad eval_pads(const rg_actions *a, const rg_gamepad_snap *g, int n)
{
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.pads = g;
    in.npads = n;
    rg_pad p;
    rg_actions_eval(a, &in, &p);
    return p;
}

static int t_binding_text(void)
{
    rg_binding b[RG_BIND_MAX], c[RG_BIND_MAX];
    char err[256], txt[512];
    int n = rg_binding_parse_list("key:Space, key:x ,pad:a, axis:leftx-, mouse:left, mouse:Y+, key:comma",
                                  b, err, sizeof err);
    CHECK_EQ(n, 7);
    CHECK_EQ(b[0].kind, RG_BIND_KEY); CHECK_EQ(b[0].code, SDL_SCANCODE_SPACE);
    CHECK_EQ(b[1].kind, RG_BIND_KEY); CHECK_EQ(b[1].code, SDL_SCANCODE_X);
    CHECK_EQ(b[2].kind, RG_BIND_PAD_BUTTON); CHECK_EQ(b[2].code, SDL_GAMEPAD_BUTTON_SOUTH);
    CHECK_EQ(b[3].kind, RG_BIND_PAD_AXIS); CHECK_EQ(b[3].code, SDL_GAMEPAD_AXIS_LEFTX); CHECK_EQ(b[3].pos, 0);
    CHECK_EQ(b[4].kind, RG_BIND_MOUSE); CHECK_EQ(b[4].code, 1);
    CHECK_EQ(b[5].kind, RG_BIND_MOUSE_MOTION); CHECK_EQ(b[5].code, 1); CHECK_EQ(b[5].pos, 1);
    CHECK_EQ(b[6].kind, RG_BIND_KEY); CHECK_EQ(b[6].code, SDL_SCANCODE_COMMA);
    rg_binding_format_list(b, n, txt, sizeof txt);
    CHECK_STR(txt, "key:Space, key:X, pad:a, axis:leftx-, mouse:left, mouse:y+, key:comma");
    CHECK_EQ(rg_binding_parse_list(txt, c, err, sizeof err), 7);
    CHECK(memcmp(b, c, sizeof b[0] * 7) == 0);
    /* duplicates dropped, empties fine */
    CHECK_EQ(rg_binding_parse_list("key:A, KEY:a, key:A", b, err, sizeof err), 1);
    CHECK_EQ(rg_binding_parse_list("", b, err, sizeof err), 0);
    CHECK_EQ(rg_binding_parse_list(" , ,", b, err, sizeof err), 0);
    /* errors */
    const char *bad[] = { "foo", "key:NoSuchKey", "pad:zz", "axis:leftx", "axis:foo+", "mouse:wheel",
                          "bar:1", "key:A,key:B,key:C,key:D,key:E,key:F,key:G,key:H,key:I" };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; i++) {
        err[0] = 0;
        CHECK_EQ(rg_binding_parse_list(bad[i], b, err, sizeof err), -1);
        CHECK(err[0] != 0);
    }
    /* every default list round-trips */
    rg_actions a;
    rg_actions_default(&a);
    for (int act = 0; act < RG_ACT_COUNT; act++) {
        rg_binding_format_list(a.bind[act], a.nbind[act], txt, sizeof txt);
        int m = rg_binding_parse_list(txt, c, err, sizeof err);
        CHECK_EQ(m, a.nbind[act]);
        CHECK(m <= 0 || memcmp(c, a.bind[act], sizeof c[0] * (size_t)m) == 0);
        CHECK(a.nbind[act] > 0);
        CHECK_EQ(rg_action_from_id(rg_action_id(act)), act);
    }
    CHECK_EQ(rg_action_from_id("nope"), -1);
    CHECK_EQ(rg_action_target(RG_ACT_CONFIRM), 6);
    CHECK(rg_action_is_axis(RG_ACT_CAMERA_DOWN));
    CHECK(!rg_action_is_axis(RG_ACT_UI_UP));
    return 0;
}

static int t_default_layout(void)
{
    rg_actions a;
    rg_actions_default(&a);
    rg_pad p = eval_keys(&a, NULL, 0);
    CHECK_EQ(p.buttons, 0); CHECK_EQ(p.lx, 0x80); CHECK_EQ(p.ry, 0x80);
    struct { int sc; uint16_t bit; } kb[] = {
        { SDL_SCANCODE_SPACE, RG_BTN_CROSS }, { SDL_SCANCODE_X, RG_BTN_CROSS }, { SDL_SCANCODE_C, RG_BTN_CIRCLE },
        { SDL_SCANCODE_Z, RG_BTN_SQUARE }, { SDL_SCANCODE_TAB, RG_BTN_TRIANGLE }, { SDL_SCANCODE_Q, RG_BTN_L1 },
        { SDL_SCANCODE_E, RG_BTN_R1 }, { SDL_SCANCODE_1, RG_BTN_L2 }, { SDL_SCANCODE_3, RG_BTN_R2 },
        { SDL_SCANCODE_V, RG_BTN_L3 }, { SDL_SCANCODE_B, RG_BTN_R3 }, { SDL_SCANCODE_RETURN, RG_BTN_START },
        { SDL_SCANCODE_BACKSPACE, RG_BTN_SELECT }, { SDL_SCANCODE_UP, RG_BTN_UP }, { SDL_SCANCODE_DOWN, RG_BTN_DOWN },
        { SDL_SCANCODE_LEFT, RG_BTN_LEFT }, { SDL_SCANCODE_RIGHT, RG_BTN_RIGHT },
        { SDL_SCANCODE_F1, 0 }, { SDL_SCANCODE_ESCAPE, 0 }, { SDL_SCANCODE_PAGEUP, 0 },   /* UI only */
    };
    for (size_t i = 0; i < sizeof kb / sizeof kb[0]; i++) {
        p = eval_key(&a, kb[i].sc);
        if (p.buttons != kb[i].bit) fprintf(stderr, "key %s\n", SDL_GetScancodeName((SDL_Scancode)kb[i].sc));
        CHECK_EQ(p.buttons, kb[i].bit);
        CHECK_EQ(p.lx, 0x80); CHECK_EQ(p.ly, 0x80);
    }
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_W).ly, 0x00);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_S).ly, 0xFF);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_A).lx, 0x00);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_D).lx, 0xFF);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_I).ry, 0x00);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_K).ry, 0xFF);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_J).rx, 0x00);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_L).rx, 0xFF);
    int ad[2] = { SDL_SCANCODE_A, SDL_SCANCODE_D };
    CHECK_EQ(eval_keys(&a, ad, 2).lx, 0x80);       /* opposite keys cancel */
    /* gamepad */
    rg_gamepad_snap g;
    struct { int btn; uint16_t bit; } gp[] = {
        { SDL_GAMEPAD_BUTTON_SOUTH, RG_BTN_CROSS }, { SDL_GAMEPAD_BUTTON_EAST, RG_BTN_CIRCLE },
        { SDL_GAMEPAD_BUTTON_WEST, RG_BTN_SQUARE }, { SDL_GAMEPAD_BUTTON_NORTH, RG_BTN_TRIANGLE },
        { SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, RG_BTN_L1 }, { SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER, RG_BTN_R1 },
        { SDL_GAMEPAD_BUTTON_LEFT_STICK, RG_BTN_L3 }, { SDL_GAMEPAD_BUTTON_RIGHT_STICK, RG_BTN_R3 },
        { SDL_GAMEPAD_BUTTON_START, RG_BTN_START }, { SDL_GAMEPAD_BUTTON_BACK, RG_BTN_SELECT },
        { SDL_GAMEPAD_BUTTON_DPAD_UP, RG_BTN_UP }, { SDL_GAMEPAD_BUTTON_DPAD_LEFT, RG_BTN_LEFT },
        { SDL_GAMEPAD_BUTTON_GUIDE, 0 },
    };
    for (size_t i = 0; i < sizeof gp / sizeof gp[0]; i++) {
        memset(&g, 0, sizeof g);
        g.button[gp[i].btn] = 1;
        CHECK_EQ(eval_pads(&a, &g, 1).buttons, gp[i].bit);
    }
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFT_TRIGGER] = 32767;
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_L2);
    g.axis[SDL_GAMEPAD_AXIS_LEFT_TRIGGER] = (int16_t)(rg_actions_raw(0.35) - 1);
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, 0);
    g.axis[SDL_GAMEPAD_AXIS_LEFT_TRIGGER] = (int16_t)rg_actions_raw(0.35);
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_L2);
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = -32768;
    g.axis[SDL_GAMEPAD_AXIS_RIGHTY] = 32767;
    p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.lx, 0x00); CHECK_EQ(p.ry, 0xFF); CHECK_EQ(p.ly, 0x80); CHECK_EQ(p.rx, 0x80);
    CHECK_EQ(p.buttons, 0);   /* a stick never presses UI or game buttons by default */
    return 0;
}

static int t_ds2_report(void)
{
    rg_actions a;
    rg_actions_default(&a);
    keys_clear();
    g_keys[SDL_SCANCODE_SPACE] = g_keys[SDL_SCANCODE_W] = true;
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHT_TRIGGER] = 32767;
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 32767;
    rg_input_snapshot in = { g_keys, SDL_SCANCODE_COUNT, 0, 0, 0, &g, 1 };
    uint8_t r[RG_DS2_REPORT_BYTES];
    CHECK_EQ(rg_actions_ds2_report(&a, &in, r), 20);
    static const uint8_t want[20] = {
        0x00, 0x79, 0xFF, 0xBD,           /* CROSS|R2 = 0x0042, active low */
        0xFF, 0x80, 0x80, 0x00,           /* rx ry lx ly */
        0, 0, 0, 0, 0, 0, 255, 0, 0, 0, 0, 255 };
    CHECK(memcmp(r, want, 20) == 0);
    CHECK_EQ(0xFFFF ^ (r[2] << 8 | r[3]), RG_BTN_CROSS | RG_BTN_R2);
    /* deterministic: the same snapshot gives the same bytes */
    uint8_t r2[20];
    for (int i = 0; i < 100; i++) { rg_actions_ds2_report(&a, &in, r2); CHECK(memcmp(r, r2, 20) == 0); }
    return 0;
}

static int t_multi_binding(void)
{
    rg_settings *s = mk();
    CHECK_EQ(set(s, "input.bind.confirm", "key:Return, key:K, mouse:left, pad:x, axis:righttrigger+, axis:lefty-",
                 RG_SRC_API), RG_SET_OK);
    rg_actions a;
    rg_actions_from_settings(&a, s);
    CHECK_EQ(a.nbind[RG_ACT_CONFIRM], 6);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_K).buttons, RG_BTN_CROSS | 0);
    /* Return is START by default too: both actions fire (documented) */
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_RETURN).buttons, RG_BTN_CROSS | RG_BTN_START);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_SPACE).buttons, 0);       /* rebinding replaced Space */
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.mouse_buttons = 1u;   /* left */
    rg_pad p;
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.button[SDL_GAMEPAD_BUTTON_WEST] = 1;
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_CROSS | RG_BTN_SQUARE);
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHT_TRIGGER] = 30000;
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_CROSS | RG_BTN_R2);
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = -30000;      /* stick up: move AND confirm */
    p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.buttons, RG_BTN_CROSS);
    CHECK(p.ly < 0x40);
    /* the strongest of several analog bindings wins */
    CHECK_EQ(set(s, "input.bind.move_right", "axis:leftx+, axis:rightx+", RG_SRC_API), RG_SET_OK);
    rg_actions_from_settings(&a, s);
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 12000;
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 32767;
    p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.lx, 0xFF);
    CHECK_EQ(p.rx, 0xFF);
    /* eight bindings fit, a ninth is refused (value kept) */
    CHECK_EQ(set(s, "input.bind.menu", "key:A,key:B,key:C,key:D,key:E,key:F,key:G,key:H", RG_SRC_API), RG_SET_OK);
    CHECK_EQ(set(s, "input.bind.menu", "key:A,key:B,key:C,key:D,key:E,key:F,key:G,key:H,key:I", RG_SRC_API),
             RG_SET_INVALID);
    rg_actions_from_settings(&a, s);
    CHECK_EQ(a.nbind[RG_ACT_MENU], 8);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_H).buttons & RG_BTN_TRIANGLE, RG_BTN_TRIANGLE);
    rg_settings_destroy(s);
    return 0;
}

static uint32_t g_rng = 12345;
static uint32_t rnd(void) { g_rng = g_rng * 1664525u + 1013904223u; return g_rng >> 8; }

static int equivalence_run(const rg_input_map *m, int iters)
{
    rg_actions a;
    rg_actions_from_input_map(&a, m);
    static const int scs[] = { SDL_SCANCODE_X, SDL_SCANCODE_C, SDL_SCANCODE_Z, SDL_SCANCODE_S, SDL_SCANCODE_Q,
        SDL_SCANCODE_E, SDL_SCANCODE_1, SDL_SCANCODE_3, SDL_SCANCODE_V, SDL_SCANCODE_B, SDL_SCANCODE_RETURN,
        SDL_SCANCODE_BACKSPACE, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT,
        SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_F, SDL_SCANCODE_D, SDL_SCANCODE_I, SDL_SCANCODE_J,
        SDL_SCANCODE_K, SDL_SCANCODE_L, SDL_SCANCODE_SPACE, SDL_SCANCODE_LSHIFT, SDL_SCANCODE_KP_8 };
    static const int16_t axv[] = { 0, 100, -100, 7999, 8000, 8001, -8001, 11999, 12000, 12001, -12000,
                                   16000, -16000, 20000, 32767, -32767, -32768, 5000, 6000, 25000 };
    int bad = 0;
    for (int it = 0; it < iters; it++) {
        keys_clear();
        for (size_t k = 0; k < sizeof scs / sizeof scs[0]; k++)
            if (rnd() % 10 == 0) g_keys[scs[k]] = true;
        rg_gamepad_snap g[2];
        memset(g, 0, sizeof g);
        int np = (int)(rnd() % 3);
        for (int p = 0; p < np; p++) {
            for (int b = 0; b < SDL_GAMEPAD_BUTTON_COUNT; b++) g[p].button[b] = rnd() % 10 == 0;
            for (int x = 0; x < SDL_GAMEPAD_AXIS_COUNT; x++)
                g[p].axis[x] = rnd() % 3 ? axv[rnd() % (sizeof axv / sizeof axv[0])] : (int16_t)(rnd() & 0xFFFF);
        }
        int nk = (int)(rnd() % 2 ? SDL_SCANCODE_COUNT : SDL_SCANCODE_X);   /* also a short key array */
        rg_pad want, got;
        rg_input_eval(m, it % 7 ? g_keys : NULL, nk, np ? g : NULL, np, &want);
        rg_input_snapshot in = { it % 7 ? g_keys : NULL, nk, 0, 0, 0, np ? g : NULL, np };
        rg_actions_eval(&a, &in, &got);
        if (memcmp(&want, &got, sizeof want)) {
            if (bad++ < 5)
                fprintf(stderr, "iter %d: legacy %04X %02X%02X%02X%02X vs actions %04X %02X%02X%02X%02X\n", it,
                        want.buttons, want.lx, want.ly, want.rx, want.ry, got.buttons, got.lx, got.ly, got.rx, got.ry);
        }
    }
    CHECK_EQ(bad, 0);
    return bad;
}

static int t_legacy_equivalence(void)
{
    rg_input_map m;
    rg_input_map_default(&m);
    equivalence_run(&m, 20000);
    char err[256];
    CHECK_EQ(rg_input_map_parse(&m,
        "deadzone = 5000\nthreshold = 20000\n"
        "CROSS = key:Space, key:Keypad 8, pad:a, axis:righttrigger+\n"
        "LX- = key:A, axis:leftx-, axis:rightx-, pad:dpleft\n"
        "RY+ = key:Left Shift, axis:lefttrigger+\n"
        "SELECT =\n", err, sizeof err), 0);
    equivalence_run(&m, 20000);
    return 0;
}

static int t_tuning(void)
{
    rg_actions a;
    rg_actions_default(&a);
    CHECK_EQ(a.deadzone[0], 8192);
    CHECK_EQ(a.threshold, 11468);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 8192;
    CHECK_EQ(eval_pads(&a, &g, 1).lx, 0x80);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 20000;   /* (20000-8192)*32767/(30146-8192) = 17623 -> 128+68 (stick range) */
    CHECK_EQ(eval_pads(&a, &g, 1).lx, 196);
    /* camera sensitivity, per stick */
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 12000;  /* (3808*32767)/21954 = 5683 -> 128+22 */
    CHECK_EQ(eval_pads(&a, &g, 1).rx, 150);
    a.sensitivity[1] = 2.0f;                  /* 11366 -> 128+44 */
    CHECK_EQ(eval_pads(&a, &g, 1).rx, 172);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 12000;
    CHECK_EQ(eval_pads(&a, &g, 1).lx, 150);   /* move stick unaffected */
    a.stick_square = false;                   /* the per-axis path: (3808*32767)/24575 = 5077 -> 128+19 */
    CHECK_EQ(eval_pads(&a, &g, 1).lx, 147);
    a.stick_square = true;
    a.sensitivity[1] = 4.0f;
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 32767;
    CHECK_EQ(eval_pads(&a, &g, 1).rx, 255);   /* clamped */
    /* per-stick deadzone */
    rg_actions_default(&a);
    a.deadzone[1] = 0;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHTY] = 4096;   /* 4096*32767/30146 = 4452 -> 128+17 */
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = 4096;
    rg_pad p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.ry, 145);
    CHECK_EQ(p.ly, 0x80);
    /* per-axis inversion */
    rg_actions_default(&a);
    a.invert[RG_AXIS_MOVE_Y] = 1;
    a.invert[RG_AXIS_CAMERA_X] = 1;
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_W).ly, 0xFF);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_A).lx, 0x00);    /* X not inverted */
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_J).rx, 0xFF);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_I).ry, 0x00);
    /* threshold */
    rg_actions_default(&a);
    a.threshold = rg_actions_raw(0.5);
    CHECK_EQ(a.threshold, 16384);
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHT_TRIGGER] = 16383;
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, 0);
    g.axis[SDL_GAMEPAD_AXIS_RIGHT_TRIGGER] = 16384;
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_R2);
    /* the tuning settings reach the map */
    rg_settings *s = mk();
    set(s, "input.deadzone_camera", "0", RG_SRC_API);
    set(s, "input.trigger_threshold", "0.5", RG_SRC_API);
    set(s, "input.sensitivity_camera", "2", RG_SRC_API);
    set(s, "input.invert_camera_y", "true", RG_SRC_API);
    set(s, "input.vibration", "0.3", RG_SRC_API);
    set(s, "input.players", "two", RG_SRC_API);
    set(s, "input.min_press_fields", "0", RG_SRC_API);
    set(s, "input.mouse_sensitivity", "2.5", RG_SRC_API);
    rg_actions_from_settings(&a, s);
    CHECK_EQ(a.deadzone[1], 0);
    CHECK_EQ(a.deadzone[0], 8192);
    CHECK_EQ(a.threshold, 16384);
    CHECK(a.sensitivity[1] == 2.0f);
    CHECK(a.invert[RG_AXIS_CAMERA_Y]);
    CHECK(fabsf(a.vibration - 0.3f) < 1e-6f);
    CHECK_EQ(a.players, RG_PLAYERS_TWO);
    CHECK_EQ(a.min_press_fields, 0);
    CHECK(a.mouse_sensitivity == 2.5f);
    rg_settings_destroy(s);
    return 0;
}

static int t_mouse(void)
{
    rg_settings *s = mk();
    set(s, "input.bind.camera_right", "mouse:x+", RG_SRC_API);
    set(s, "input.bind.camera_left", "mouse:x-", RG_SRC_API);
    set(s, "input.bind.attack", "mouse:left", RG_SRC_API);
    set(s, "input.bind.confirm", "mouse:right", RG_SRC_API);
    set(s, "input.bind.menu", "mouse:y+", RG_SRC_API);
    set(s, "input.bind.shoulder_left", "mouse:x1", RG_SRC_API);
    rg_actions a;
    rg_actions_from_settings(&a, s);
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    rg_pad p;
    in.mouse_dx = 10;          /* 10 * 32767/20 = 16383 -> 128+63 */
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.rx, 191);
    in.mouse_dx = -30;
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.rx, 0);
    a.mouse_sensitivity = 2.0f;
    in.mouse_dx = 10;
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.rx, 255);
    a.mouse_sensitivity = 1.0f;
    in.mouse_dx = 0;
    in.mouse_buttons = 1u << 0;    /* left */
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, RG_BTN_SQUARE);
    in.mouse_buttons = 1u << 2;    /* right (SDL button 3) */
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS);
    in.mouse_buttons = 1u << 3;    /* x1 */
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, RG_BTN_L1);
    /* motion on a digital action: the threshold applies */
    in.mouse_buttons = 0;
    in.mouse_dy = 5;               /* 8191 < 11468 */
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, 0);
    in.mouse_dy = 8;               /* 13106 */
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, RG_BTN_TRIANGLE);
    in.mouse_dy = -8;
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, 0);
    rg_settings_destroy(s);
    return 0;
}

static int t_hotplug(void)
{
    rg_pad_roster r;
    rg_roster_init(&r);
    int sl[RG_MAX_GAMEPADS];
    CHECK_EQ(rg_roster_port_slots(&r, RG_PLAYERS_ONE, 0, sl), 0);
    CHECK(rg_roster_port_connected(&r, RG_PLAYERS_ONE, 0));
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_ONE, 0), -1);
    CHECK_EQ(rg_roster_add(&r, 101), 0);
    CHECK_EQ(rg_roster_add(&r, 102), 1);
    CHECK_EQ(rg_roster_add(&r, 103), 2);
    CHECK_EQ(rg_roster_add(&r, 102), 1);   /* known id */
    CHECK_EQ(r.n, 3);
    /* one player: every pad drives port 0; port 1 stays disconnected */
    CHECK_EQ(rg_roster_port_slots(&r, RG_PLAYERS_ONE, 0, sl), 3);
    CHECK_EQ(sl[0], 0); CHECK_EQ(sl[2], 2);
    CHECK_EQ(rg_roster_port_slots(&r, RG_PLAYERS_ONE, 1, sl), 0);
    CHECK(!rg_roster_port_connected(&r, RG_PLAYERS_ONE, 1));
    /* two players: slot 0 / slot 1 */
    CHECK_EQ(rg_roster_port_slots(&r, RG_PLAYERS_TWO, 0, sl), 1); CHECK_EQ(sl[0], 0);
    CHECK_EQ(rg_roster_port_slots(&r, RG_PLAYERS_TWO, 1, sl), 1); CHECK_EQ(sl[0], 1);
    CHECK(rg_roster_port_connected(&r, RG_PLAYERS_TWO, 1));
    /* rumble follows the most recently used pad (one player) */
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_ONE, 0), 0);
    rg_roster_note_activity(&r, RG_DEV_GAMEPAD, 103);
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_ONE, 0), 2);
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_TWO, 1), 1);
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_ONE, 1), -1);
    /* unplug: slots close the gap, the active pad falls back */
    CHECK_EQ(rg_roster_remove(&r, 101), 0);
    CHECK_EQ(r.n, 2);
    CHECK_EQ(rg_roster_slot(&r, 102), 0);
    CHECK_EQ(rg_roster_slot(&r, 103), 1);
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_ONE, 0), 1);
    CHECK_EQ(rg_roster_remove(&r, 103), 1);
    CHECK_EQ(r.active_kind, RG_DEV_GAMEPAD);
    CHECK_EQ(r.active_id, 102u);
    CHECK_EQ(rg_roster_remove(&r, 999), -1);
    CHECK(!rg_roster_port_connected(&r, RG_PLAYERS_TWO, 1));
    rg_roster_note_activity(&r, RG_DEV_KEYBOARD_MOUSE, 0);
    CHECK_EQ(rg_roster_rumble_slot(&r, RG_PLAYERS_ONE, 0), 0);
    for (uint32_t id = 200; id < 207; id++) CHECK(rg_roster_add(&r, id) >= 0);
    CHECK_EQ(r.n, 8);
    CHECK_EQ(rg_roster_add(&r, 300), -1);
    /* reports through the roster: pad A presses CROSS, pad B d-pad up */
    rg_actions a;
    rg_actions_default(&a);
    rg_pad_roster r2;
    rg_roster_init(&r2);
    rg_gamepad_snap by_slot[RG_MAX_GAMEPADS];
    memset(by_slot, 0, sizeof by_slot);
    rg_roster_add(&r2, 1);
    rg_roster_add(&r2, 2);
    by_slot[0].button[SDL_GAMEPAD_BUTTON_SOUTH] = 1;
    by_slot[1].button[SDL_GAMEPAD_BUTTON_DPAD_UP] = 1;
    for (int players = 0; players < 2; players++)
        for (int port = 0; port < 2; port++) {
            rg_gamepad_snap feed[RG_MAX_GAMEPADS];
            int n = rg_roster_port_slots(&r2, players, port, sl);
            for (int i = 0; i < n; i++) feed[i] = by_slot[sl[i]];
            uint16_t b = eval_pads(&a, feed, n).buttons;
            uint16_t want = players == RG_PLAYERS_ONE ? (port == 0 ? RG_BTN_CROSS | RG_BTN_UP : 0)
                                                      : (port == 0 ? RG_BTN_CROSS : RG_BTN_UP);
            CHECK_EQ(b, want);
        }
    /* unplug pad A (two players): pad B becomes player 1, port 1 disconnects */
    int gone = rg_roster_remove(&r2, 1);
    CHECK_EQ(gone, 0);
    memmove(&by_slot[gone], &by_slot[gone + 1], sizeof by_slot[0] * (RG_MAX_GAMEPADS - 1 - (size_t)gone));
    int n = rg_roster_port_slots(&r2, RG_PLAYERS_TWO, 0, sl);
    CHECK_EQ(n, 1);
    CHECK_EQ(eval_pads(&a, &by_slot[sl[0]], 1).buttons, RG_BTN_UP);
    CHECK(!rg_roster_port_connected(&r2, RG_PLAYERS_TWO, 1));
    /* re-plug: the new pad is player 2 again */
    CHECK_EQ(rg_roster_add(&r2, 3), 1);
    CHECK(rg_roster_port_connected(&r2, RG_PLAYERS_TWO, 1));
    /* activity detection */
    rg_gamepad_snap q;
    memset(&q, 0, sizeof q);
    CHECK(!rg_gamepad_snap_active(&q, 11468));
    q.axis[0] = 11000;
    CHECK(!rg_gamepad_snap_active(&q, 11468));
    q.axis[0] = -12000;
    CHECK(rg_gamepad_snap_active(&q, 11468));
    return 0;
}

/* play-test 2 (gun cadence, BRINGUP.md "User play-test 2"): a gamepad button tapped at any
 * human rate must reach the game as one press edge per tap.  Model: one host pump per field
 * (latch step, down events latched, live state at pump time), the game reading the pad at
 * its 30 Hz logic rate (every second field, either phase) and firing on an edge.  Taps of
 * every length from "down and up between two pumps" to 3 fields, periods 4..12 fields
 * (15 Hz .. 5 Hz; 20 Hz taps are beyond a 30 Hz reader on retail too), every start phase. */
static int tap_cadence(int latch_off)
{
    rg_actions a;
    rg_actions_default(&a);
    if (latch_off)
        a.min_press_fields = 0;     /* control: without the latch a short tap is lost */
    for (int period = 4; period <= 12; period++)
        for (int len = 0; len <= 3 && len < period - 1; len++)
            for (int phase = 0; phase < period; phase++)
                for (int rphase = 0; rphase < 2; rphase++) {
                    rg_press_latch l;
                    rg_latch_clear(&l);
                    int taps = 0, edges = 0, prev = 0;
                    const int fields = 240;
                    for (int f = 0; f < fields; f++) {
                        rg_latch_step(&l);
                        int k = f - phase;
                        int start = k >= 0 && k % period == 0 && f < fields - 8;
                        if (start) {
                            taps++;
                            rg_latch_pad(&l, 0, SDL_GAMEPAD_BUTTON_WEST, a.min_press_fields);
                        }
                        /* physically down for len fields after the event (0 = released
                         * again before this pump) */
                        int down = k >= 0 && (k % period) < len && (k / period) * period + phase < fields - 8;
                        rg_gamepad_snap g;
                        memset(&g, 0, sizeof g);
                        g.button[SDL_GAMEPAD_BUTTON_WEST] = (uint8_t)down;
                        rg_latch_apply_pad(&l, 0, &g);
                        rg_pad p = eval_pads(&a, &g, 1);
                        if ((f & 1) == rphase) {            /* the game's logic read */
                            int now = (p.buttons & RG_BTN_SQUARE) != 0;
                            if (now && !prev)
                                edges++;
                            prev = now;
                        }
                    }
                    if (edges != taps) {
                        fprintf(stderr, "tap_cadence: period %d len %d phase %d read %d: %d taps, %d edges\n",
                                period, len, phase, rphase, taps, edges);
                        CHECK_EQ(edges, taps);
                        return 1;
                    }
                }
    return 0;
}
static int t_tap_cadence(void) { return tap_cadence(0); }
static int t_tap_cadence_control(void) { return tap_cadence(1); }

static int t_latch(void)
{
    rg_actions a;
    rg_actions_default(&a);
    rg_press_latch l;
    rg_latch_clear(&l);
    static bool live[SDL_SCANCODE_COUNT], eff[SDL_SCANCODE_COUNT];
    memset(live, 0, sizeof live);
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.keys = eff;
    in.nkeys = SDL_SCANCODE_COUNT;
    rg_pad p;
    /* field 0's pump saw X go down and up again: the live state says released */
    rg_latch_step(&l);
    rg_latch_key(&l, SDL_SCANCODE_X, a.min_press_fields);
    uint16_t seen[5];
    for (int f = 0; f < 5; f++) {
        if (f) rg_latch_step(&l);       /* next field's pump */
        rg_latch_apply_keys(&l, live, SDL_SCANCODE_COUNT, eff, SDL_SCANCODE_COUNT);
        rg_actions_eval(&a, &in, &p);
        seen[f] = p.buttons;
        /* every read inside a field gives the same answer */
        rg_pad again;
        rg_actions_eval(&a, &in, &again);
        CHECK(memcmp(&p, &again, sizeof p) == 0);
    }
    CHECK_EQ(seen[0], RG_BTN_CROSS);
    CHECK_EQ(seen[1], RG_BTN_CROSS);
    CHECK_EQ(seen[2], 0);
    CHECK_EQ(seen[4], 0);
    /* a held key is unaffected by the latch running out */
    live[SDL_SCANCODE_X] = true;
    rg_latch_apply_keys(&l, live, SDL_SCANCODE_COUNT, eff, SDL_SCANCODE_COUNT);
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, RG_BTN_CROSS);
    /* latch length 0 = off */
    live[SDL_SCANCODE_X] = false;
    rg_latch_key(&l, SDL_SCANCODE_C, 0);
    rg_latch_apply_keys(&l, live, SDL_SCANCODE_COUNT, eff, SDL_SCANCODE_COUNT);
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.buttons, 0);
    /* a re-press extends, never shortens */
    rg_latch_key(&l, SDL_SCANCODE_C, 3);
    rg_latch_key(&l, SDL_SCANCODE_C, 1);
    CHECK_EQ(l.key[SDL_SCANCODE_C], 3);
    /* mouse + pad latches; slot removal mirrors the roster */
    rg_latch_clear(&l);
    rg_latch_mouse(&l, 3, 2);
    CHECK_EQ(rg_latch_apply_mouse(&l, 0), 1u << 2);
    rg_latch_pad(&l, 1, SDL_GAMEPAD_BUTTON_EAST, 2);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    rg_latch_apply_pad(&l, 1, &g);
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_CIRCLE);
    rg_latch_remove_slot(&l, 0);
    memset(&g, 0, sizeof g);
    rg_latch_apply_pad(&l, 0, &g);
    CHECK_EQ(g.button[SDL_GAMEPAD_BUTTON_EAST], 1);
    memset(&g, 0, sizeof g);
    rg_latch_apply_pad(&l, 1, &g);
    CHECK_EQ(g.button[SDL_GAMEPAD_BUTTON_EAST], 0);
    return 0;
}

static int t_ui_nav(void)
{
    rg_ui_nav n;
    rg_ui_nav_init(&n);
    int32_t v[RG_ACT_COUNT];
    int out[RG_ACT_COUNT];
    memset(v, 0, sizeof v);
    v[RG_ACT_UI_DOWN] = 32767;
    CHECK_EQ(rg_ui_nav_update(&n, v, 0, out), 1);
    CHECK_EQ(out[0], RG_ACT_UI_DOWN);
    CHECK_EQ(rg_ui_nav_update(&n, v, 100, out), 0);
    CHECK_EQ(rg_ui_nav_update(&n, v, 399, out), 0);
    CHECK_EQ(rg_ui_nav_update(&n, v, 400, out), 1);
    CHECK_EQ(rg_ui_nav_update(&n, v, 489, out), 0);
    CHECK_EQ(rg_ui_nav_update(&n, v, 490, out), 1);
    v[RG_ACT_UI_DOWN] = 0;
    CHECK_EQ(rg_ui_nav_update(&n, v, 1000, out), 0);
    /* accept and the overlay toggle never repeat */
    v[RG_ACT_UI_ACCEPT] = 32767;
    v[RG_ACT_UI_OVERLAY] = 32767;
    CHECK_EQ(rg_ui_nav_update(&n, v, 2000, out), 2);
    for (uint64_t t = 2050; t < 6000; t += 50) CHECK_EQ(rg_ui_nav_update(&n, v, t, out), 0);
    /* game actions are ignored */
    memset(v, 0, sizeof v);
    v[RG_ACT_CONFIRM] = 32767;
    CHECK_EQ(rg_ui_nav_update(&n, v, 7000, out), 0);
    return 0;
}

static int t_settings_bindings(void)
{
    rg_settings *s = mk();
    int w = rg_settings_parse(s,
        "[input]\n"
        "bind.confirm = KEY:return ,pad:x\n"
        "bind.cancel = key:Nope\n"
        "invert_camera_y = yes\n"
        "bind.ui_overlay = key:F10, pad:misc1\n", "in.ini");
    CHECK_EQ(w, 1);
    CHECK(strstr(g_warn.all, "in.ini:3: input.bind.cancel: unknown key 'Nope'; using the default (key:C, pad:b)") != NULL);
    CHECK_STR(val(s, "input.bind.confirm"), "key:Return, pad:x");
    CHECK_STR(val(s, "input.bind.cancel"), "key:C, pad:b");
    rg_actions a;
    rg_actions_from_settings(&a, s);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_RETURN).buttons, RG_BTN_CROSS | RG_BTN_START);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_C).buttons, RG_BTN_CIRCLE);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_SPACE).buttons, 0);
    CHECK(a.invert[RG_AXIS_CAMERA_Y]);
    CHECK_EQ(a.nbind[RG_ACT_UI_OVERLAY], 2);
    CHECK_EQ(a.bind[RG_ACT_UI_OVERLAY][0].code, SDL_SCANCODE_F10);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.button[SDL_GAMEPAD_BUTTON_WEST] = 1;     /* also attack's default */
    CHECK_EQ(eval_pads(&a, &g, 1).buttons, RG_BTN_CROSS | RG_BTN_SQUARE);
    /* defaults written to a file reproduce the default layout exactly */
    char text[32768];
    rg_settings_format(s, text, sizeof text, 0);
    rg_settings *t = mk();
    rg_settings_reset_all(s);
    rg_actions d, back;
    rg_actions_default(&d);
    rg_actions_from_settings(&back, t);
    CHECK(memcmp(&d, &back, sizeof d) == 0);
    rg_settings_destroy(s);
    rg_settings_destroy(t);
    return 0;
}

static uint64_t fnv(uint64_t h, const void *d, size_t n)
{
    const uint8_t *p = (const uint8_t *)d;
    while (n--) { h ^= *p++; h *= 0x100000001B3ull; }
    return h;
}

static int t_script_bypass(void)
{
    char err[256];
    rg_input_script sc = { 0 };
    CHECK_EQ(rg_input_script_parse(&sc, "10 20 CROSS\n15 CIRCLE+START\n100 140 UP\n", "t", err, sizeof err), 0);
    uint64_t hashes[2];
    for (int run = 0; run < 2; run++) {
        rg_settings *s = mk();
        /* settings that would change live input must not touch a script */
        set(s, "input.bind.confirm", "key:Space", RG_SRC_API);
        set(s, "input.invert_move_y", "true", RG_SRC_API);
        set(s, "input.players", "two", RG_SRC_API);
        rg_host_config hc;
        rg_host_config_default(&hc);
        rg_host_config_from_settings(&hc, s);
        hc.headless = 1;
        rg_host *h = rg_host_create(&hc);
        CHECK(h != NULL);
        if (!h) return 1;
        rg_host_attach_settings(h, s, NULL);
        rg_host_set_input_script(h, &sc);
        uint64_t hash = 0xCBF29CE484222325ull;
        for (uint32_t vbl = 0; vbl < 400; vbl++) {
            CHECK(rg_host_pump(h));
            rg_pad p0, p1, want;
            rg_host_read_pad(h, 0, vbl, &p0);
            rg_host_read_pad(h, 1, vbl, &p1);
            rg_input_script_pad(&sc, vbl, &want);
            if (memcmp(&p0, &want, sizeof want)) { CHECK(!"port 0 != script"); break; }
            uint8_t r0[20], r1[20];
            rg_pad_ds2_report(&p0, r0);
            rg_pad_ds2_report(&p1, r1);
            hash = fnv(hash, r0, 20);
            hash = fnv(hash, r1, 20);
            CHECK_EQ(p1.buttons, 0);
        }
        CHECK(!rg_host_port_connected(h, 1));
        CHECK(rg_host_port_connected(h, 0));
        CHECK(!rg_host_overlay_open(h));
        rg_pad p;
        rg_host_read_pad(h, 0, 15, &p);
        CHECK_EQ(p.buttons, RG_BTN_CROSS | RG_BTN_CIRCLE | RG_BTN_START);
        rg_host_read_pad(h, 0, 120, &p);
        CHECK_EQ(p.buttons, RG_BTN_UP);
        CHECK_EQ(p.ly, 0x80);
        /* without the script, headless reads are neutral */
        rg_host_set_input_script(h, NULL);
        rg_host_read_pad(h, 0, 15, &p);
        CHECK_EQ(p.buttons, 0);
        rg_host_destroy(h);
        rg_settings_destroy(s);
        hashes[run] = hash;
    }
    CHECK(hashes[0] == hashes[1]);
    rg_input_script_free(&sc);
    return 0;
}

/* Pre-audit action ids keep working (docs/INPUT.md "Actions"). */
static int t_action_aliases(void)
{
    static const struct { const char *old_id; int act; } al[] = {
        { "shoulder_left", RG_ACT_CAMERA_TURN_LEFT }, { "shoulder_right", RG_ACT_CAMERA_TURN_RIGHT },
        { "trigger_left", RG_ACT_DECLINE }, { "trigger_right", RG_ACT_CAMERA_RECENTRE },
        { "stick_left_click", RG_ACT_SWITCH_LEADER }, { "stick_right_click", RG_ACT_FIRST_PERSON },
        { "start", RG_ACT_PAUSE }, { "select", RG_ACT_MAP },
    };
    int n = 0, act = -1;
    while (rg_action_alias(n, &act)) n++;
    CHECK_EQ(n, (int)(sizeof al / sizeof al[0]));
    for (size_t i = 0; i < sizeof al / sizeof al[0]; i++) {
        CHECK_EQ(rg_action_from_id(al[i].old_id), al[i].act);
        CHECK(strcmp(rg_action_id(al[i].act), al[i].old_id) != 0);
    }
    CHECK_STR(rg_action_id(RG_ACT_CAMERA_TURN_LEFT), "camera_turn_left");
    CHECK_STR(rg_action_id(RG_ACT_PAUSE), "pause");
    CHECK_STR(rg_action_id(RG_ACT_WALK), "walk");
    CHECK_EQ(rg_action_target(RG_ACT_WALK), -1);
    CHECK_EQ(RG_ACT_START, RG_ACT_PAUSE);   /* old enum names still compile */
    /* retail-confirmed roles (X sword, SQUARE gun, CIRCLE jump); R1 guard still provisional */
    CHECK(strstr(rg_action_label(RG_ACT_CANCEL), "Jump (Circle)") != NULL);
    CHECK(strstr(rg_action_label(RG_ACT_ATTACK), "Gun") != NULL);
    CHECK(strstr(rg_action_label(RG_ACT_CONFIRM), "Sword") != NULL);
    CHECK(strstr(rg_action_label(RG_ACT_CAMERA_TURN_RIGHT), "Guard?") != NULL);
    /* an old config file loads into the new ids, without warnings */
    rg_settings *s = mk();
    int w = rg_settings_parse(s,
        "[input]\n"
        "bind.shoulder_left = key:F\n"
        "bind.start = key:P, pad:start\n"
        "bind.stick_right_click = \n", "old.ini");
    CHECK_EQ(w, 0);
    CHECK_STR(val(s, "input.bind.camera_turn_left"), "key:F");
    CHECK_STR(val(s, "input.bind.pause"), "key:P, pad:start");
    CHECK_STR(val(s, "input.bind.first_person"), "");
    CHECK_EQ(rg_settings_find(s, "input.bind.select"), rg_settings_find(s, "input.bind.map"));
    /* --set with an old id */
    CHECK_EQ(rg_settings_override(s, "input.bind.trigger_right=key:G"), RG_SET_OK);
    CHECK_STR(val(s, "input.bind.camera_recentre"), "key:G");
    rg_actions a;
    rg_actions_from_settings(&a, s);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_F).buttons, RG_BTN_L1);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_P).buttons, RG_BTN_START);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_G).buttons, RG_BTN_R2);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_B).buttons, 0);
    /* the file is written with the new ids only */
    static char text[32768];
    rg_settings_format(s, text, sizeof text, 0);
    CHECK(strstr(text, "bind.camera_turn_left = key:F") != NULL);
    CHECK(strstr(text, "shoulder_left") == NULL && strstr(text, "bind.start") == NULL);
    /* an alias cannot shadow a real id, or point nowhere */
    rg_settings_set_warn(s, NULL, NULL);
    CHECK_EQ(rg_settings_add_alias(s, "input.bind.map", "input.bind.pause"), -1);
    CHECK_EQ(rg_settings_add_alias(s, "input.bind.zz", "input.bind.nope"), -1);
    rg_settings_destroy(s);
    return 0;
}

/* The game's stick decode and movement bands (docs/CONTROLS-AUDIT.md 5). */
static double game_len(const rg_pad *p)
{
    double x = rg_game_stick_value(p->lx) / 128.0, y = rg_game_stick_value(p->ly) / 128.0;
    double l = sqrt(x * x + y * y);
    return l > 1.0 ? 1.0 : l;
}
static int band(double len) { return len >= 0.9 ? 2 : len >= 0.16 ? 1 : 0; }   /* 0 still, 1 walk, 2 run */

/* docs/INPUT.md "Stick range": a round gamepad stick at full tilt runs in every
 * direction (the play-test symptom: diagonals walked), small tilts still walk */
static int t_stick_range(void)
{
    rg_actions a;
    rg_actions_default(&a);
    CHECK(a.stick_square);
    rg_gamepad_snap g;
    int worst = 2;
    for (int deg = 0; deg < 360; deg++) {
        double t = deg * 3.14159265358979 / 180.0;
        memset(&g, 0, sizeof g);
        g.axis[SDL_GAMEPAD_AXIS_LEFTX] = (int16_t)lround(32767.0 * cos(t));
        g.axis[SDL_GAMEPAD_AXIS_LEFTY] = (int16_t)lround(32767.0 * sin(t));
        rg_pad p = eval_pads(&a, &g, 1);
        int b = band(game_len(&p));
        if (b < worst) worst = b;
        if (b != 2 && deg % 45 == 0) fprintf(stderr, "deg %d: %02X %02X walks\n", deg, p.lx, p.ly);
        /* 90% tilt (worn or round-gated sticks) runs too */
        g.axis[SDL_GAMEPAD_AXIS_LEFTX] = (int16_t)lround(0.90 * 32767.0 * cos(t));
        g.axis[SDL_GAMEPAD_AXIS_LEFTY] = (int16_t)lround(0.90 * 32767.0 * sin(t));
        p = eval_pads(&a, &g, 1);
        CHECK_EQ(band(game_len(&p)), 2);
        /* 70% tilt walks in every direction (the game's own dead zone takes ~60% on an axis) */
        g.axis[SDL_GAMEPAD_AXIS_LEFTX] = (int16_t)lround(0.7 * 32767.0 * cos(t));
        g.axis[SDL_GAMEPAD_AXIS_LEFTY] = (int16_t)lround(0.7 * 32767.0 * sin(t));
        p = eval_pads(&a, &g, 1);
        CHECK_EQ(band(game_len(&p)), 1);
    }
    CHECK_EQ(worst, 2);
    /* the 45-degree corner reaches the square's corner */
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 23170;
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = -23170;
    rg_pad p = eval_pads(&a, &g, 1);
    CHECK(p.lx >= 0xFE && p.ly <= 0x01);
    /* round dead zone: 20% on a diagonal is inside the 25% default */
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 4633;
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = 4633;
    p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.lx, 0x80);
    CHECK_EQ(p.ly, 0x80);
    /* pure axis values: the radial rescale to the outer edge (the tuning test's numbers) */
    int ox, oy;
    rg_stick_shape(20000, 0, 8192, &ox, &oy);
    CHECK_EQ(ox, 17623);
    rg_stick_shape(RG_STICK_OUTER, 0, 8192, &ox, &oy);
    CHECK_EQ(ox, 32767);
    rg_stick_shape(0, 0, 0, &ox, &oy);
    CHECK_EQ(ox, 0);
    rg_stick_shape(31000, 0, 31129, &ox, &oy);   /* dead zone past the outer edge: still works */
    CHECK_EQ(ox, 0);
    rg_stick_shape(32767, 0, 31129, &ox, &oy);
    CHECK_EQ(ox, 32767);
    CHECK_EQ(oy, 0);
    rg_stick_shape(0, -32768, 8192, &ox, &oy);
    CHECK_EQ(ox, 0);
    CHECK_EQ(oy, -32767);
    rg_stick_shape(8192, 0, 8192, &ox, &oy);
    CHECK_EQ(ox, 0);
    /* the right stick too, and per-stick dead zones */
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 23170;
    g.axis[SDL_GAMEPAD_AXIS_RIGHTY] = 23170;
    p = eval_pads(&a, &g, 1);
    CHECK(p.rx >= 0xFE && p.ry >= 0xFE);
    CHECK_EQ(p.lx, 0x80);
    /* off: the old per-axis behaviour (a full diagonal walks) */
    a.stick_square = false;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 23170;
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = 23170;
    p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.lx, 206);
    CHECK_EQ(band(game_len(&p)), 1);
    /* the setting reaches the map; default on, Original keeps it on */
    rg_settings *s = mk();
    rg_actions_from_settings(&a, s);
    CHECK(a.stick_square);
    set(s, "input.stick_ds2_range", "false", RG_SRC_API);
    rg_actions_from_settings(&a, s);
    CHECK(!a.stick_square);
    rg_settings_destroy(s);
    /* the legacy map keeps the legacy evaluation */
    rg_input_map m;
    rg_input_map_default(&m);
    rg_actions_from_input_map(&a, &m);
    CHECK(!a.stick_square);
    CHECK(!a.camera_pc);
    return 0;
}

/* docs/INPUT.md "Camera stick convention": PC = orbit X flipped, Y flipped in every
 * camera, first-person X unchanged; nothing changes without a camera hint */
static int t_camera_convention(void)
{
    rg_actions a;
    rg_actions_default(&a);
    CHECK(a.camera_pc);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 32767;   /* right */
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 32767;
    rg_pad p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.rx, 0xFF);                      /* no camera: the stick as it is */
    a.camera_view = RG_CAMVIEW_ORBIT;
    p = eval_pads(&a, &g, 1);
    CHECK_EQ(p.rx, 0x00);                      /* orbit: right = view right */
    CHECK_EQ(p.lx, 0xFF);                      /* the move stick never */
    a.camera_view = RG_CAMVIEW_FIRST_PERSON;
    CHECK_EQ(eval_pads(&a, &g, 1).rx, 0xFF);   /* first person already turns right */
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHTY] = -32767;  /* up */
    CHECK_EQ(eval_pads(&a, &g, 1).ry, 0xFF);   /* look up */
    a.camera_view = RG_CAMVIEW_ORBIT;
    CHECK_EQ(eval_pads(&a, &g, 1).ry, 0xFF);
    a.camera_view = RG_CAMVIEW_NONE;
    CHECK_EQ(eval_pads(&a, &g, 1).ry, 0x00);
    /* the invert settings apply on top; keys follow the convention too */
    a.camera_view = RG_CAMVIEW_ORBIT;
    a.invert[RG_AXIS_CAMERA_X] = 1;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_RIGHTX] = 32767;
    CHECK_EQ(eval_pads(&a, &g, 1).rx, 0xFF);
    a.invert[RG_AXIS_CAMERA_X] = 0;
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_L).rx, 0x00);   /* camera_right key */
    /* Original: the PS2 directions everywhere */
    a.camera_pc = false;
    CHECK_EQ(eval_pads(&a, &g, 1).rx, 0xFF);
    rg_settings *s = mk();
    rg_actions_from_settings(&a, s);
    CHECK(a.camera_pc);
    set(s, "input.camera_convention", "original", RG_SRC_API);
    rg_actions_from_settings(&a, s);
    CHECK(!a.camera_pc);
    rg_settings_destroy(s);
    return 0;
}

static int t_walk(void)
{
    /* the decode itself: dead zone, edges, endpoints */
    CHECK_EQ(rg_game_stick_value(0x80), 0);
    CHECK_EQ(rg_game_stick_value(128 + 49), 0);
    CHECK_EQ(rg_game_stick_value(128 - 49), 0);
    CHECK_EQ(rg_game_stick_value(128 + 50), 1);
    CHECK_EQ(rg_game_stick_value(128 - 50), 0);
    CHECK_EQ(rg_game_stick_value(128 - 51), -1);
    CHECK_EQ(rg_game_stick_value(0xFF), 128);
    CHECK_EQ(rg_game_stick_value(0x00), -128);
    /* the walk bytes decode to +-68/128 = 0.53125, the band's middle (0.53) */
    CHECK_EQ(rg_game_stick_value(RG_WALK_POS), 68);
    CHECK_EQ(rg_game_stick_value(RG_WALK_NEG), -68);
    rg_actions a;
    rg_actions_default(&a);
    CHECK_EQ(a.nbind[RG_ACT_WALK], 1);
    CHECK_EQ(a.bind[RG_ACT_WALK][0].code, SDL_SCANCODE_LSHIFT);
    /* keyboard movement is full run by default, cardinal and diagonal */
    int dirs[8][2] = { { SDL_SCANCODE_W, 0 }, { SDL_SCANCODE_S, 0 }, { SDL_SCANCODE_A, 0 }, { SDL_SCANCODE_D, 0 },
                       { SDL_SCANCODE_W, SDL_SCANCODE_A }, { SDL_SCANCODE_W, SDL_SCANCODE_D },
                       { SDL_SCANCODE_S, SDL_SCANCODE_A }, { SDL_SCANCODE_S, SDL_SCANCODE_D } };
    for (int i = 0; i < 8; i++) {
        int k[3] = { dirs[i][0], dirs[i][1], SDL_SCANCODE_LSHIFT };
        int nk = dirs[i][1] ? 2 : 1;
        rg_pad p = eval_keys(&a, k, nk);
        CHECK(p.lx == 0x00 || p.lx == 0xFF || p.lx == 0x80);
        CHECK(p.ly == 0x00 || p.ly == 0xFF || p.ly == 0x80);
        CHECK_EQ(band(game_len(&p)), 2);
        CHECK_EQ(p.buttons, 0);
        /* + walk: every direction lands in the walk band, at the walk bytes */
        k[nk] = SDL_SCANCODE_LSHIFT;
        p = eval_keys(&a, k, nk + 1);
        CHECK(p.lx == RG_WALK_POS || p.lx == RG_WALK_NEG || p.lx == 0x80);
        CHECK(p.ly == RG_WALK_POS || p.ly == RG_WALK_NEG || p.ly == 0x80);
        CHECK_EQ(band(game_len(&p)), 1);
        CHECK_EQ(p.buttons, 0);   /* walk drives no PS2 input */
        CHECK_EQ(p.rx, 0x80);
    }
    int wl[2] = { SDL_SCANCODE_W, SDL_SCANCODE_LSHIFT };
    CHECK_EQ(eval_keys(&a, wl, 2).ly, RG_WALK_NEG);
    int dl[2] = { SDL_SCANCODE_D, SDL_SCANCODE_LSHIFT };
    CHECK_EQ(eval_keys(&a, dl, 2).lx, RG_WALK_POS);
    /* walk alone, and walk with the camera: nothing moves; the camera is not limited */
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_LSHIFT).lx, 0x80);
    int ll[2] = { SDL_SCANCODE_L, SDL_SCANCODE_LSHIFT };
    CHECK_EQ(eval_keys(&a, ll, 2).rx, 0xFF);
    /* a gamepad stick past the band is limited; a smaller one is unchanged */
    keys_clear();
    g_keys[SDL_SCANCODE_LSHIFT] = true;
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = 32767;
    g.axis[SDL_GAMEPAD_AXIS_LEFTY] = 16000;
    rg_input_snapshot in = { g_keys, SDL_SCANCODE_COUNT, 0, 0, 0, &g, 1 };
    rg_pad p;
    rg_actions_eval(&a, &in, &p);
    CHECK_EQ(p.lx, RG_WALK_POS);
    CHECK_EQ(p.ly, eval_pads(&a, &g, 1).ly);   /* below the walk byte: unchanged */
    CHECK(p.ly > 0x80 && p.ly < RG_WALK_POS);
    /* rebindable like any action, also to a gamepad button */
    rg_settings *s = mk();
    CHECK_EQ(set(s, "input.bind.walk", "key:Left Ctrl, pad:leftstick", RG_SRC_API), RG_SET_OK);
    rg_actions_from_settings(&a, s);
    int wc[2] = { SDL_SCANCODE_W, SDL_SCANCODE_LCTRL };
    CHECK_EQ(eval_keys(&a, wc, 2).ly, RG_WALK_NEG);
    CHECK_EQ(eval_keys(&a, wl, 2).ly, 0x00);
    rg_settings_destroy(s);
    return 0;
}

/* Dead-zone compensation (gameplay option, off by default and in Original). */
static int t_stick_compensation(void)
{
    CHECK_EQ(rg_stick_compensate(0), 0x80);
    CHECK_EQ(rg_stick_compensate(1), 128 + 50);          /* first byte past the game's dead zone */
    CHECK_EQ(rg_stick_compensate(-1), 128 - 51);
    CHECK_EQ(rg_stick_compensate(32767), 0xFF);
    CHECK_EQ(rg_stick_compensate(-32767), 0x00);
    CHECK_EQ(rg_game_stick_value(rg_stick_compensate(1)), 1);
    CHECK_EQ(rg_game_stick_value(rg_stick_compensate(-1)), -1);
    /* monotonic, never in the game's dead zone, and the game reads about v / 32767 */
    int prev = -129, worst = 0;
    for (int v = -32767; v <= 32767; v++) {
        int g = rg_game_stick_value(rg_stick_compensate(v));
        if (v) CHECK(g != 0);
        if (g < prev) { CHECK(!"monotonic"); break; }
        prev = g;
        int want = (int)lround((double)v * 128.0 / 32767.0);
        int err = g > want ? g - want : want - g;
        if (err > worst) worst = err;
    }
    CHECK(worst <= 2);
    /* off (default): a 30% stick is inside the game's ~39% dead zone and does nothing */
    rg_actions a;
    rg_actions_default(&a);
    CHECK(!a.stick_compensation);
    a.deadzone[0] = rg_actions_raw(0.10);
    rg_gamepad_snap g;
    memset(&g, 0, sizeof g);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = (int16_t)rg_actions_raw(0.30);
    CHECK_EQ(rg_game_stick_value(eval_pads(&a, &g, 1).lx), 0);
    /* on: the same stick moves; the host dead zone is the only one */
    a.stick_compensation = true;
    rg_pad p = eval_pads(&a, &g, 1);
    CHECK(rg_game_stick_value(p.lx) > 20);
    g.axis[SDL_GAMEPAD_AXIS_LEFTX] = (int16_t)rg_actions_raw(0.09);
    CHECK_EQ(eval_pads(&a, &g, 1).lx, 0x80);
    /* keyboard: full deflection is unchanged; walk still lands mid-band */
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_W).ly, 0x00);
    int wl[2] = { SDL_SCANCODE_W, SDL_SCANCODE_LSHIFT };
    CHECK_EQ(eval_keys(&a, wl, 2).ly, RG_WALK_NEG);
    /* the setting: gameplay-flagged, off by default and in Original, reaches the map */
    rg_settings *s = mk();
    int i = rg_settings_find(s, "input.stick_compensation");
    CHECK(i >= 0);
    const rg_setting_def *d = rg_settings_def(s, i);
    CHECK(d->flags & RG_SETF_GAMEPLAY);
    CHECK(d->flags & RG_SETF_HAS_ORIGINAL);
    CHECK_EQ(d->def_i, 0);
    CHECK_EQ(d->orig_i, 0);
    CHECK_EQ(set(s, "input.stick_compensation", "true", RG_SRC_MENU), RG_SET_OK);
    rg_actions_from_settings(&a, s);
    CHECK(a.stick_compensation);
    CHECK(!rg_settings_matches_preset(s, "original"));
    CHECK_EQ(rg_settings_apply_preset(s, "original"), 0);
    CHECK(!rg_settings_get_bool(s, "input.stick_compensation"));
    /* vibration: kept, hidden, labelled as unused (the US build never vibrates) */
    d = rg_settings_def(s, rg_settings_find(s, "input.vibration"));
    CHECK(d->flags & RG_SETF_HIDDEN);
    CHECK(strstr(d->label, "never vibrates") != NULL);
    rg_settings_destroy(s);
    return 0;
}

static int t_report_control(void)
{
    rg_settings *s = mk();
    set(s, "input.bind.cancel", "key:C", RG_SRC_API);
    rg_actions a;
    rg_actions_from_settings(&a, s);
    CHECK_EQ(eval_key(&a, SDL_SCANCODE_C).buttons, RG_BTN_CROSS);   /* must fail: C is CIRCLE */
    rg_settings_destroy(s);
    return 0;
}


/* ================================================================ P6 menu: rebinding, text, prompts */
static void env_init(uienv *e, int kb)
{
    memset(e, 0, sizeof *e);
    e->s = mk();
    e->kb = kb;
    rg_actions_from_settings(&e->a, e->s);
    rg_menu_init(&e->m, e->s);
    rg_ui_nav_init(&e->nav);
    rg_capture_init(&e->cap);
}

static int menu_has(const uienv *e, const char *needle)
{
    rg_menu_line lines[RG_MENU_MAX_ROWS + 16];
    int n = rg_menu_render(&e->m, e->t, lines, RG_MENU_MAX_ROWS + 16);
    for (int i = 0; i < n; i++) if (strstr(lines[i].text, needle)) return 1;
    return 0;
}

/* Opens the binding editor of action `act` and puts the cursor on editor row
 * `row` (0.. = bindings, then Add, Reset, Back). */
static int open_editor(uienv *e, int act, int row)
{
    char id[64];
    snprintf(id, sizeof id, "input.bind.%s", rg_action_id(act));
    int idx = rg_settings_find(e->s, id);
    if (go_to(e, idx)) return -1;
    cmd(e, U_ACCEPT);
    if (e->m.view != RG_MENU_VIEW_BINDINGS || e->m.edit != idx) return -1;
    for (int i = 0; i < row; i++) cmd(e, U_DOWN);
    return idx;
}

static int nbind(const uienv *e, int idx)
{
    rg_binding b[RG_BIND_MAX];
    return rg_binding_parse_list(rg_settings_get_string(e->s, rg_settings_def(e->s, idx)->id), b, NULL, 0);
}

static rg_pad eval_now(uienv *e, int sc)
{
    rg_actions_from_settings(&e->a, e->s);
    return eval_key(&e->a, sc);
}

/* The capture state machine through the menu, one device only. */
static int rebind_flow(int kb)
{
    uienv e;
    env_init(&e, kb);
    /* the confirm action: add a binding */
    int conf = rg_settings_find(e.s, "input.bind.confirm");
    int canc = rg_settings_find(e.s, "input.bind.cancel");
    char def_conf[256];
    snprintf(def_conf, sizeof def_conf, "%s", rg_settings_get_string(e.s, "input.bind.confirm"));
    int n0 = nbind(&e, conf);
    CHECK(n0 >= 2);
    CHECK_EQ(open_editor(&e, RG_ACT_CONFIRM, n0), conf);   /* on "Add a binding" */
    CHECK(menu_has(&e, "Add a binding"));
    CHECK(menu_has(&e, "Reset to default"));
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing(&e.m));
    CHECK_EQ(e.cap.state, RG_CAPTURE_WAITING);
    CHECK(menu_has(&e, "Press a key, mouse button, gamepad button or stick"));
    CHECK(menu_has(&e, "cancels, 5 s"));
    /* menu commands are ignored while capturing (the host drops them anyway) */
    int sub = e.m.sub;
    rg_menu_command(&e.m, RG_MENU_DOWN, e.t);
    CHECK_EQ(e.m.sub, sub);
    CHECK(rg_menu_capturing(&e.m));
    char want[512];
    if (kb) {
        cap_key(&e, SDL_SCANCODE_F);
        snprintf(want, sizeof want, "%s, key:F", def_conf);
        CHECK_STR(rg_settings_get_string(e.s, "input.bind.confirm"), want);
        CHECK_EQ(eval_now(&e, SDL_SCANCODE_F).buttons, RG_BTN_CROSS);
    } else {
        cap_button(&e, SDL_GAMEPAD_BUTTON_LEFT_PADDLE1);
        snprintf(want, sizeof want, "%s, pad:paddle2", def_conf);   /* SDL: left paddle 1 = "paddle2" */
        char b[64];
        rg_binding one = { RG_BIND_PAD_BUTTON, 0, SDL_GAMEPAD_BUTTON_LEFT_PADDLE1 };
        rg_binding_format(&one, b, sizeof b);
        snprintf(want, sizeof want, "%s, %s", def_conf, b);
        CHECK_STR(rg_settings_get_string(e.s, "input.bind.confirm"), want);
    }
    CHECK(!rg_menu_capturing(&e.m));
    CHECK(strstr(e.m.status, "added") != NULL);
    CHECK_EQ(e.m.sub, n0);           /* the cursor is on the new binding */
    CHECK(e.m.dirty);

    /* replace binding 0 */
    while (e.m.sub != 0) cmd(&e, U_UP);
    CHECK_EQ(e.m.sub_col, 0);
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing(&e.m));
    if (kb) cap_key(&e, SDL_SCANCODE_G);
    else cap_axis(&e, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, 30000);
    {
        rg_binding b[RG_BIND_MAX];
        int n = rg_binding_parse_list(rg_settings_get_string(e.s, "input.bind.confirm"), b, NULL, 0);
        CHECK_EQ(n, n0 + 1);
        if (kb) { CHECK_EQ(b[0].kind, RG_BIND_KEY); CHECK_EQ(b[0].code, SDL_SCANCODE_G); }
        else { CHECK_EQ(b[0].kind, RG_BIND_PAD_AXIS); CHECK_EQ(b[0].code, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER); CHECK_EQ(b[0].pos, 1); }
    }
    CHECK(strstr(e.m.status, "replaced by") != NULL);

    /* a duplicate inside the same action changes nothing */
    char before[512];
    snprintf(before, sizeof before, "%s", rg_settings_get_string(e.s, "input.bind.confirm"));
    cmd(&e, U_DOWN);                 /* row 1 */
    cmd(&e, U_ACCEPT);
    if (kb) cap_key(&e, SDL_SCANCODE_G);
    else cap_axis(&e, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, 30000);
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.confirm"), before);
    CHECK(strstr(e.m.status, "already has") != NULL);

    /* conflict: another game action already uses it -> warn, keep both */
    while (e.m.sub != nbind(&e, conf)) cmd(&e, U_DOWN);   /* Add */
    cmd(&e, U_ACCEPT);
    const char *ctok;
    if (kb) { cap_key(&e, SDL_SCANCODE_C); ctok = "key:C"; }              /* cancel's default key */
    else { cap_button(&e, SDL_GAMEPAD_BUTTON_EAST); ctok = "pad:b"; }   /* cancel's default button */
    CHECK(strstr(rg_settings_get_string(e.s, "input.bind.confirm"), ctok) != NULL);
    CHECK(strstr(rg_settings_get_string(e.s, "input.bind.cancel"), ctok) != NULL);
    CHECK(strstr(e.m.status, "WARNING") != NULL);
    CHECK(strstr(e.m.status, "Cancel") != NULL);
    int c[4];
    CHECK_EQ(rg_menu_binding_conflicts(&e.m, conf, ctok, c, 4), 1);
    CHECK_EQ(c[0], canc);
    CHECK(menu_has(&e, "also: Cancel"));
    if (kb) CHECK_EQ(eval_now(&e, SDL_SCANCODE_C).buttons, RG_BTN_CROSS | RG_BTN_CIRCLE);   /* both fire */

    /* no conflict across contexts: a menu-control input on a game action */
    while (e.m.sub != nbind(&e, conf)) cmd(&e, U_DOWN);
    cmd(&e, U_ACCEPT);
    const char *xtok;
    if (kb) { cap_key(&e, SDL_SCANCODE_PAGEUP); xtok = "key:PageUp"; }   /* ui_page_prev */
    else { cap_button(&e, SDL_GAMEPAD_BUTTON_GUIDE); xtok = NULL; }    /* Guide cancels instead */
    if (xtok) {
        CHECK(strstr(e.m.status, "WARNING") == NULL);
        CHECK_EQ(rg_menu_binding_conflicts(&e.m, conf, xtok, c, 4), 0);
    } else {
        CHECK(strstr(e.m.status, "cancelled") != NULL);
    }

    /* cancel: Esc (keyboard) / Guide (gamepad) */
    snprintf(before, sizeof before, "%s", rg_settings_get_string(e.s, "input.bind.confirm"));
    while (e.m.sub != nbind(&e, conf)) cmd(&e, U_DOWN);
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing(&e.m));
    if (kb) cap_key(&e, SDL_SCANCODE_ESCAPE);
    else cap_button(&e, SDL_GAMEPAD_BUTTON_GUIDE);
    CHECK(!rg_menu_capturing(&e.m));
    CHECK_EQ(e.cap.state, RG_CAPTURE_IDLE);
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.confirm"), before);
    CHECK(strstr(e.m.status, "cancelled") != NULL);

    /* timeout: 5 s without input */
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing(&e.m));
    uint64_t t0 = e.t - 100;         /* the accept press (press, release, +50 each) */
    CHECK_EQ(e.m.capture_deadline, t0 + 5000);
    while (e.t < t0 + 5000) ui_feed(&e, -1, -1, 0);
    CHECK(rg_menu_capturing(&e.m));  /* last tick at t0 + 4950: still waiting */
    ui_feed(&e, -1, -1, 0);          /* t0 + 5000 */
    CHECK(!rg_menu_capturing(&e.m));
    CHECK_EQ(e.cap.state, RG_CAPTURE_IDLE);   /* the host stops its detector */
    CHECK(strstr(e.m.status, "no input for 5 s") != NULL);
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.confirm"), before);
    /* a press after the timeout is not a binding */
    rg_capture_key(&e.cap, SDL_SCANCODE_H);
    CHECK_EQ(e.cap.state, RG_CAPTURE_IDLE);

    /* remove binding 0: right = Remove, accept */
    int nb = nbind(&e, conf);
    while (e.m.sub != 0) cmd(&e, U_UP);
    cmd(&e, U_RIGHT);
    CHECK_EQ(e.m.sub_col, 1);
    CHECK(menu_has(&e, "[Remove]"));
    cmd(&e, U_ACCEPT);
    CHECK_EQ(nbind(&e, conf), nb - 1);
    CHECK(strstr(e.m.status, "removed") != NULL);

    /* reset this action (rows: bindings, Add, Capture mouse motion, Reset, Back) */
    nb = nbind(&e, conf);
    while (e.m.sub != nb + 2) cmd(&e, U_DOWN);
    CHECK(menu_has(&e, "> Reset to default"));
    cmd(&e, U_ACCEPT);
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.confirm"), def_conf);

    /* back to the page; reset all bindings */
    cmd(&e, U_BACK);
    CHECK_EQ(e.m.view, RG_MENU_VIEW_PAGE);
    CHECK_EQ(open_editor(&e, RG_ACT_ATTACK, 0), rg_settings_find(e.s, "input.bind.attack"));
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* remove attack's first binding */
    cmd(&e, U_BACK);
    int ui = open_editor(&e, RG_ACT_UI_OVERLAY, 0);
    CHECK(ui >= 0);
    /* menu controls keep a keyboard and a gamepad binding (key:F1, pad:guide,
     * pad:touchpad; details in menu_device_guard) */
    CHECK_EQ(nbind(&e, ui), 3);
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* F1: the only key */
    CHECK_EQ(nbind(&e, ui), 3);
    CHECK(strstr(e.m.status, "not removed") != NULL);
    CHECK_EQ(e.m.sub, 3);            /* moved to "Add a binding" */
    cmd(&e, U_UP);                   /* touchpad */
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);
    CHECK_EQ(nbind(&e, ui), 2);
    CHECK(strstr(e.m.status, "removed pad:touchpad") != NULL);
    while (e.m.sub != 1) cmd(&e, U_UP);   /* guide: now the only gamepad binding */
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);
    CHECK_EQ(nbind(&e, ui), 2);
    CHECK(strstr(e.m.status, "last gamepad binding") != NULL);
    CHECK(!rg_menu_capturing(&e.m));
    cmd(&e, U_BACK);
    CHECK(!rg_settings_is_default(e.s, rg_settings_find(e.s, "input.bind.attack")));
    CHECK(!rg_settings_is_default(e.s, ui));
    {
        int rows[RG_MENU_MAX_ROWS];
        int n = rg_menu_rows(&e.m, rows, RG_MENU_MAX_ROWS);
        int found = 0;
        for (int i = 0; i < n + 1 && !found; i++) {
            if (rows[e.m.cursor] == -1 - RG_ROW_RESET_BINDINGS) found = 1;
            else cmd(&e, U_DOWN);
        }
        CHECK(found);
        CHECK(menu_has(&e, "Reset all bindings"));
        cmd(&e, U_ACCEPT);
    }
    for (int i = 0; i < rg_settings_count(e.s); i++)
        if (rg_settings_def(e.s, i)->type == RG_SET_BINDING) CHECK(rg_settings_is_default(e.s, i));
    /* the registry's defaults rebuild the default layout */
    rg_actions a, d;
    rg_actions_from_settings(&a, e.s);
    rg_actions_default(&d);
    CHECK(!memcmp(a.bind, d.bind, sizeof a.bind));
    /* closing the overlay during a capture cancels it */
    CHECK_EQ(open_editor(&e, RG_ACT_MENU, 0), rg_settings_find(e.s, "input.bind.menu"));
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing(&e.m));
    rg_menu_command(&e.m, RG_MENU_TOGGLE, e.t);
    CHECK(!e.m.open);
    CHECK(!rg_menu_capturing(&e.m));
    rg_settings_destroy(e.s);
    return 0;
}

static int t_menu_rebind_keyboard(void) { return rebind_flow(1); }
static int t_menu_rebind_gamepad(void) { return rebind_flow(0); }

/* The detector alone (rg_bind_capture). */
static int t_capture(void)
{
    rg_bind_capture c;
    rg_capture_init(&c);
    char t[96];
    CHECK_EQ(c.state, RG_CAPTURE_IDLE);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_A), RG_CAPTURE_IDLE);   /* not listening */
    rg_capture_cancel_hint(&c, t, sizeof t);
    CHECK_STR(t, "key:Escape / pad:guide");
    /* keys: unknown / unnamed are ignored */
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_UNKNOWN), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_key(&c, 600), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_KP_8), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "key:Keypad 8");
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_B), RG_CAPTURE_DONE);   /* first press wins */
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "key:Keypad 8");
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_COMMA), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "key:comma");
    /* mouse buttons 1..5 only */
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_mouse_button(&c, 0), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_mouse_button(&c, 6), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_mouse_button(&c, 4), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "mouse:x1");
    /* pad buttons */
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_pad_button(&c, SDL_GAMEPAD_BUTTON_COUNT), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_pad_button(&c, SDL_GAMEPAD_BUTTON_LEFT_STICK), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "pad:leftstick");
    /* cancel inputs */
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_pad_button(&c, SDL_GAMEPAD_BUTTON_GUIDE), RG_CAPTURE_CANCELLED);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "");
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_ESCAPE), RG_CAPTURE_CANCELLED);
    /* axes: thresholds, both directions, edges */
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_pad_axis(&c, 0, SDL_GAMEPAD_AXIS_LEFTX, RG_CAPTURE_AXIS_HIGH - 1), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_pad_axis(&c, 0, SDL_GAMEPAD_AXIS_LEFTX, -RG_CAPTURE_AXIS_HIGH), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "axis:leftx-");
    rg_capture_begin(&c, NULL, 0);
    CHECK_EQ(rg_capture_pad_axis(&c, 3, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, RG_CAPTURE_AXIS_HIGH), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "axis:righttrigger+");
    CHECK_EQ(rg_capture_pad_axis(&c, RG_MAX_GAMEPADS, 0, 32767), RG_CAPTURE_DONE);   /* ignored: done */
    /* an axis held at begin must return to rest first; the other direction is free */
    rg_gamepad_snap held[2];
    memset(held, 0, sizeof held);
    held[1].axis[SDL_GAMEPAD_AXIS_LEFT_TRIGGER] = 30000;
    held[1].axis[SDL_GAMEPAD_AXIS_RIGHTY] = -20000;
    rg_capture_begin(&c, held, 2);
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 32767), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, RG_CAPTURE_AXIS_LOW + 1), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 30000), RG_CAPTURE_WAITING);  /* not at rest yet */
    CHECK_EQ(rg_capture_pad_axis(&c, 0, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 0), RG_CAPTURE_WAITING);      /* pad 0 rests anyway */
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_RIGHTY, -32768), RG_CAPTURE_WAITING);       /* held up */
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, RG_CAPTURE_AXIS_LOW), RG_CAPTURE_WAITING);  /* rest */
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, RG_CAPTURE_AXIS_HIGH), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "axis:lefttrigger+");
    rg_capture_begin(&c, held, 2);
    CHECK_EQ(rg_capture_pad_axis(&c, 1, SDL_GAMEPAD_AXIS_RIGHTY, 20000), RG_CAPTURE_DONE);   /* down was never held */
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "axis:righty+");
    /* the text parses back to the same binding */
    rg_binding b[RG_BIND_MAX];
    CHECK_EQ(rg_binding_parse_list(t, b, NULL, 0), 1);
    CHECK(!memcmp(&b[0], &c.result, sizeof b[0]));
    rg_capture_end(&c);
    CHECK_EQ(c.state, RG_CAPTURE_IDLE);
    return 0;
}

static int t_pad_family(void)
{
    static const struct { int type; rg_pad_family f; } k[] = {
        { SDL_GAMEPAD_TYPE_UNKNOWN, RG_PAD_FAMILY_GENERIC },
        { SDL_GAMEPAD_TYPE_STANDARD, RG_PAD_FAMILY_GENERIC },
        { SDL_GAMEPAD_TYPE_XBOX360, RG_PAD_FAMILY_XBOX },
        { SDL_GAMEPAD_TYPE_XBOXONE, RG_PAD_FAMILY_XBOX },
        { SDL_GAMEPAD_TYPE_PS3, RG_PAD_FAMILY_PLAYSTATION },
        { SDL_GAMEPAD_TYPE_PS4, RG_PAD_FAMILY_PLAYSTATION },
        { SDL_GAMEPAD_TYPE_PS5, RG_PAD_FAMILY_PLAYSTATION },
        { SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_PRO, RG_PAD_FAMILY_NINTENDO },
        { SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_LEFT, RG_PAD_FAMILY_NINTENDO },
        { SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT, RG_PAD_FAMILY_NINTENDO },
        { SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_PAIR, RG_PAD_FAMILY_NINTENDO },
        { SDL_GAMEPAD_TYPE_GAMECUBE, RG_PAD_FAMILY_NINTENDO },
        { SDL_GAMEPAD_TYPE_STEAM, RG_PAD_FAMILY_XBOX },
        { SDL_GAMEPAD_TYPE_COUNT, RG_PAD_FAMILY_GENERIC },
        { -1, RG_PAD_FAMILY_GENERIC },
        { 1000, RG_PAD_FAMILY_GENERIC },
    };
    CHECK_EQ(SDL_GAMEPAD_TYPE_COUNT, 13);   /* a new SDL type: add it to the table */
    for (size_t i = 0; i < sizeof k / sizeof k[0]; i++) {
        if (rg_pad_family_from_sdl_type(k[i].type) != k[i].f) fprintf(stderr, "SDL type %d\n", k[i].type);
        CHECK_EQ(rg_pad_family_from_sdl_type(k[i].type), k[i].f);
    }
    CHECK_STR(rg_pad_family_name(RG_PAD_FAMILY_NONE), "none");
    CHECK_STR(rg_pad_family_name(RG_PAD_FAMILY_PLAYSTATION), "playstation");
    CHECK_STR(rg_pad_family_name(RG_PAD_FAMILY_XBOX), "xbox");
    CHECK_STR(rg_pad_family_name(RG_PAD_FAMILY_NINTENDO), "nintendo");
    CHECK_STR(rg_pad_family_name(RG_PAD_FAMILY_GENERIC), "generic");
    /* a headless host has no gamepads */
    rg_host_config hc;
    rg_host_config_default(&hc);
    hc.headless = 1;
    rg_host *h = rg_host_create(&hc);
    CHECK(h != NULL);
    if (h) {
        CHECK_EQ(rg_host_active_pad_family(h), RG_PAD_FAMILY_NONE);
        rg_host_destroy(h);
    }
    return 0;
}

static int t_prompt_style(void)
{
    static const rg_device_kind kinds[] = { RG_DEV_NONE, RG_DEV_KEYBOARD_MOUSE, RG_DEV_GAMEPAD };
    /* scripted / headless: PlayStation, whatever the setting, device and history */
    for (int set = 0; set <= RG_PROMPTS_KEYBOARD; set++)
        for (int k = 0; k < 3; k++)
            for (int f = RG_PAD_FAMILY_NONE; f <= RG_PAD_FAMILY_GENERIC; f++)
                for (int prev = 0; prev < RG_PROMPT_COUNT; prev++)
                    CHECK_EQ(rg_prompt_style_resolve(set, true, kinds[k], (rg_pad_family)f, (rg_prompt_style)prev),
                             RG_PROMPT_PLAYSTATION);
    /* a fixed setting wins over the device */
    for (int k = 0; k < 3; k++) {
        CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_PLAYSTATION, false, kinds[k], RG_PAD_FAMILY_XBOX, RG_PROMPT_KEYBOARD), RG_PROMPT_PLAYSTATION);
        CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_XBOX, false, kinds[k], RG_PAD_FAMILY_PLAYSTATION, RG_PROMPT_KEYBOARD), RG_PROMPT_XBOX);
        CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_NINTENDO, false, kinds[k], RG_PAD_FAMILY_XBOX, RG_PROMPT_KEYBOARD), RG_PROMPT_NINTENDO);
        CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_KEYBOARD, false, kinds[k], RG_PAD_FAMILY_XBOX, RG_PROMPT_XBOX), RG_PROMPT_KEYBOARD);
    }
    /* auto follows the device in use */
    CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_KEYBOARD_MOUSE, RG_PAD_FAMILY_PLAYSTATION, RG_PROMPT_XBOX), RG_PROMPT_KEYBOARD);
    CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_GAMEPAD, RG_PAD_FAMILY_PLAYSTATION, RG_PROMPT_XBOX), RG_PROMPT_PLAYSTATION);
    CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_GAMEPAD, RG_PAD_FAMILY_XBOX, RG_PROMPT_KEYBOARD), RG_PROMPT_XBOX);
    CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_GAMEPAD, RG_PAD_FAMILY_NINTENDO, RG_PROMPT_KEYBOARD), RG_PROMPT_NINTENDO);
    CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_GAMEPAD, RG_PAD_FAMILY_GENERIC, RG_PROMPT_KEYBOARD), RG_PROMPT_XBOX);
    /* no device used yet: keep the previous style */
    for (int prev = 0; prev < RG_PROMPT_COUNT; prev++)
        CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_NONE, RG_PAD_FAMILY_NONE, (rg_prompt_style)prev), prev);
    CHECK_EQ(rg_prompt_style_resolve(RG_PROMPTS_AUTO, false, RG_DEV_NONE, RG_PAD_FAMILY_NONE, (rg_prompt_style)99), RG_PROMPT_PLAYSTATION);
    CHECK_STR(rg_prompt_style_name(RG_PROMPT_PLAYSTATION), "playstation");
    CHECK_STR(rg_prompt_style_name(RG_PROMPT_KEYBOARD), "keyboard");

    /* the setting */
    rg_settings *s = mk();
    int i = rg_settings_find(s, "prompts.style");
    CHECK(i >= 0);
    if (i < 0) return 1;
    const rg_setting_def *d = rg_settings_def(s, i);
    CHECK_EQ(d->type, RG_SET_ENUM);
    CHECK_STR(rg_settings_category(s, i), "controls");
    CHECK(!(d->flags & RG_SETF_PLACEHOLDER));   /* real since the gaiji2 swap (docs/PROMPTS.md) */
    CHECK(!(d->flags & RG_SETF_GAMEPLAY));
    CHECK(d->flags & RG_SETF_HAS_ORIGINAL);
    CHECK_STR(val(s, "prompts.style"), "auto");
    const char *names[] = { "auto", "playstation", "xbox", "nintendo", "keyboard" };
    for (int k = 0; k < 5; k++) {
        CHECK_EQ(set(s, "prompts.style", names[k], RG_SRC_API) >= 0, 1);
        CHECK_EQ(rg_settings_get_enum(s, "prompts.style"), k);
    }
    CHECK_EQ(set(s, "prompts.style", "ps", RG_SRC_API), RG_SET_INVALID);
    rg_settings_apply_preset(s, "original");
    CHECK_STR(val(s, "prompts.style"), "playstation");
    rg_settings_apply_preset(s, "default");
    CHECK_STR(val(s, "prompts.style"), "auto");
    rg_settings_parse(s, "[prompts]\nstyle = Nintendo\n", "p.ini");
    CHECK_STR(val(s, "prompts.style"), "nintendo");

    /* scripted and headless hosts report PlayStation whatever the setting */
    char err[128];
    rg_input_script sc = { 0 };
    CHECK_EQ(rg_input_script_parse(&sc, "10 20 CROSS\n", "t", err, sizeof err), 0);
    for (int k = 0; k < 5; k++) {
        set(s, "prompts.style", names[k], RG_SRC_API);
        rg_host_config hc;
        rg_host_config_default(&hc);
        hc.headless = 1;
        rg_host *h = rg_host_create(&hc);
        CHECK(h != NULL);
        if (!h) break;
        rg_host_attach_settings(h, s, NULL);
        CHECK_EQ(rg_host_prompt_style(h), RG_PROMPT_PLAYSTATION);
        rg_host_set_input_script(h, &sc);
        CHECK_EQ(rg_host_prompt_style(h), RG_PROMPT_PLAYSTATION);
        CHECK(rg_host_pump(h));
        CHECK_EQ(rg_host_prompt_style(h), RG_PROMPT_PLAYSTATION);
        rg_host_destroy(h);
    }
    /* --set prompts.style=xbox on a scripted run: still PlayStation */
    CHECK_EQ(rg_settings_override(s, "prompts.style=xbox"), 0);
    {
        rg_host_config hc;
        rg_host_config_default(&hc);
        hc.headless = 1;
        rg_host *h = rg_host_create(&hc);
        if (h) {
            rg_host_attach_settings(h, s, NULL);
            rg_host_set_input_script(h, &sc);
            CHECK_EQ(rg_host_prompt_style(h), RG_PROMPT_PLAYSTATION);
            rg_host_destroy(h);
        }
    }
    rg_input_script_free(&sc);
    rg_settings_destroy(s);
    return 0;
}

/* Text entry for string settings: keyboard typing and the on-screen selector. */
static int text_open(uienv *e, const char *id)
{
    int idx = rg_settings_find(e->s, id);
    if (idx < 0 || go_to(e, idx)) return -1;
    cmd(e, U_ACCEPT);
    return rg_menu_text_editing(&e->m) ? idx : -1;
}

static int t_menu_text_entry(void)
{
    uienv e;
    /* keyboard */
    env_init(&e, 1);
    CHECK(text_open(&e, "system.screenshot_dir") >= 0);
    CHECK_STR(e.m.text, ".");
    CHECK_EQ(e.m.text_cur, 1);
    CHECK(menu_has(&e, "[.|]"));
    rg_menu_text_key(&e.m, RG_TEXT_BACKSPACE);
    CHECK_STR(e.m.text, "");
    rg_menu_text_key(&e.m, RG_TEXT_BACKSPACE);   /* nothing to delete */
    rg_menu_text_input(&e.m, "C:\\shots dir\xC3\xA9");   /* UTF-8 e-acute */
    CHECK_STR(e.m.text, "C:\\shots dir\xC3\xA9");
    rg_menu_text_key(&e.m, RG_TEXT_BACKSPACE);   /* removes both bytes */
    CHECK_STR(e.m.text, "C:\\shots dir");
    rg_menu_text_input(&e.m, "\x01\t");          /* control characters are dropped */
    CHECK_STR(e.m.text, "C:\\shots dir");
    rg_menu_text_key(&e.m, RG_TEXT_HOME);
    rg_menu_text_key(&e.m, RG_TEXT_DELETE);
    rg_menu_text_input(&e.m, "D");
    rg_menu_text_key(&e.m, RG_TEXT_END);
    rg_menu_text_key(&e.m, RG_TEXT_LEFT);
    rg_menu_text_key(&e.m, RG_TEXT_LEFT);
    rg_menu_text_key(&e.m, RG_TEXT_LEFT);
    rg_menu_text_input(&e.m, "#");
    rg_menu_text_key(&e.m, RG_TEXT_RIGHT);
    CHECK_STR(e.m.text, "D:\\shots #dir");
    CHECK_EQ(e.m.text_cur, 11);
    rg_menu_text_key(&e.m, RG_TEXT_COMMIT);
    CHECK(!rg_menu_text_editing(&e.m));
    CHECK_STR(rg_settings_get_string(e.s, "system.screenshot_dir"), "D:\\shots #dir");
    CHECK(e.m.dirty);
    CHECK(strstr(e.m.status, "set") != NULL);
    /* it survives a file round trip (quotes for the '#') */
    {
        char buf[65536];
        rg_settings_format(e.s, buf, sizeof buf, RG_FMT_CHANGED_ONLY);
        rg_settings *t = mk();
        rg_settings_parse(t, buf, "rt");
        CHECK_STR(rg_settings_get_string(t, "system.screenshot_dir"), "D:\\shots #dir");
        rg_settings_destroy(t);
    }
    /* cancel keeps the value */
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_text_editing(&e.m));
    rg_menu_text_input(&e.m, "zzz");
    rg_menu_text_key(&e.m, RG_TEXT_CANCEL);
    CHECK(!rg_menu_text_editing(&e.m));
    CHECK_STR(rg_settings_get_string(e.s, "system.screenshot_dir"), "D:\\shots #dir");
    /* too long: refused at the buffer size */
    cmd(&e, U_ACCEPT);
    for (int i = 0; i < 300; i++) rg_menu_text_input(&e.m, "a");
    CHECK_EQ((int)strlen(e.m.text), RG_MENU_TEXT_MAX - 1);
    rg_menu_text_key(&e.m, RG_TEXT_CANCEL);
    /* closing the overlay drops an open edit */
    cmd(&e, U_ACCEPT);
    rg_menu_text_input(&e.m, "q");
    cmd(&e, U_TOGGLE);
    CHECK(!e.m.open);
    CHECK(!rg_menu_text_editing(&e.m));
    CHECK_STR(rg_settings_get_string(e.s, "system.screenshot_dir"), "D:\\shots #dir");
    rg_settings_destroy(e.s);

    /* gamepad only: the on-screen selector */
    env_init(&e, 0);
    CHECK(text_open(&e, "system.screenshot_dir") >= 0);
    cmd(&e, U_BACK);                 /* back deletes */
    CHECK_STR(e.m.text, "");
    CHECK(e.m.open);
    for (int i = 0; i < 2; i++) cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* c */
    cmd(&e, U_DOWN);
    cmd(&e, U_DOWN);                 /* row 2: A..M, column 2 */
    cmd(&e, U_ACCEPT);               /* C */
    cmd(&e, U_LEFT);
    cmd(&e, U_LEFT);
    cmd(&e, U_LEFT);                 /* wraps to M */
    cmd(&e, U_ACCEPT);
    CHECK_STR(e.m.text, "cCM");
    CHECK(menu_has(&e, "[M]"));
    cmd(&e, U_PREV);                 /* cursor left */
    cmd(&e, U_DOWN);
    cmd(&e, U_DOWN);                 /* row 4: digits, column 12 = '_' */
    cmd(&e, U_ACCEPT);
    CHECK_STR(e.m.text, "cC_M");
    cmd(&e, U_NEXT);
    cmd(&e, U_DOWN);
    cmd(&e, U_DOWN);                 /* special row: column clamped to Cancel (4) */
    CHECK_EQ(e.m.osk_row, 6);
    CHECK_EQ(e.m.osk_col, 4);
    CHECK(menu_has(&e, "[Cancel]"));
    for (int i = 0; i < 4; i++) cmd(&e, U_LEFT);   /* Space */
    cmd(&e, U_ACCEPT);
    CHECK_STR(e.m.text, "cC_M ");
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* Delete */
    CHECK_STR(e.m.text, "cC_M");
    cmd(&e, U_RIGHT);
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* OK */
    CHECK(!rg_menu_text_editing(&e.m));
    CHECK_STR(rg_settings_get_string(e.s, "system.screenshot_dir"), "cC_M");
    /* Clear, then Cancel */
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_text_editing(&e.m));
    cmd(&e, U_UP);                   /* wraps to the special row */
    cmd(&e, U_RIGHT);
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* Clear */
    CHECK_STR(e.m.text, "");
    cmd(&e, U_RIGHT);
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);               /* Cancel */
    CHECK(!rg_menu_text_editing(&e.m));
    CHECK_STR(rg_settings_get_string(e.s, "system.screenshot_dir"), "cC_M");
    rg_settings_destroy(e.s);

    /* an invalid value keeps the editor open with the reason */
    rg_settings *s = mk_t();
    rg_menu m;
    rg_menu_init(&m, s);
    rg_menu_command(&m, RG_MENU_TOGGLE, 0);
    int rows[RG_MENU_MAX_ROWS];
    int n = rg_menu_rows(&m, rows, RG_MENU_MAX_ROWS);
    int ts = rg_settings_find(s, "t.s");
    for (int i = 0; i < n && rows[m.cursor] != ts; i++) rg_menu_command(&m, RG_MENU_DOWN, 0);
    CHECK_EQ(rows[m.cursor], ts);
    rg_menu_command(&m, RG_MENU_ACCEPT, 0);
    CHECK(rg_menu_text_editing(&m));
    rg_menu_text_input(&m, "X!");
    rg_menu_text_key(&m, RG_TEXT_COMMIT);
    CHECK(rg_menu_text_editing(&m));
    CHECK(strstr(m.status, "no '!' allowed") != NULL);
    CHECK_STR(rg_settings_get_string(s, "t.s"), "abc");
    rg_menu_text_key(&m, RG_TEXT_BACKSPACE);
    rg_menu_text_input(&m, "YZ");
    rg_menu_text_key(&m, RG_TEXT_COMMIT);
    CHECK(!rg_menu_text_editing(&m));
    CHECK_STR(rg_settings_get_string(s, "t.s"), "abcxyz");   /* normalised by the validator */
    rg_settings_destroy(s);
    return 0;
}

/* Restart / gameplay / planned markers and the 15 s display trial. */
static int t_menu_flags(void)
{
    uienv e;
    env_init(&e, 1);
    rg_settings_mark_applied(e.s);
    /* a restart setting: marked always, "pending" once changed */
    int ae = rg_settings_find(e.s, "audio.enabled");
    CHECK_EQ(go_to(&e, ae), 0);
    CHECK(menu_has(&e, "[restart]"));
    CHECK(menu_has(&e, "[restart] takes effect after a restart"));
    CHECK(!menu_has(&e, "(restart pending)"));
    cmd(&e, U_ACCEPT);
    CHECK(menu_has(&e, "(restart pending)"));
    CHECK(strstr(e.m.status, "after a restart") != NULL);
    cmd(&e, U_ACCEPT);
    CHECK(!menu_has(&e, "(restart pending)"));
    /* a gameplay option */
    CHECK_EQ(go_to(&e, rg_settings_find(e.s, "input.stick_compensation")), 0);
    CHECK(menu_has(&e, "[gameplay]"));
    CHECK(menu_has(&e, "[gameplay] changes game logic, off in Original"));
    /* a planned one */
    CHECK_EQ(go_to(&e, rg_settings_find(e.s, "graphics.bloom")), 0);   /* prompts.style is real now */
    CHECK(menu_has(&e, "(planned)"));
    CHECK(menu_has(&e, "(planned) stored, no effect yet"));
    /* every row says what it is */
    for (int i = 0; i < rg_settings_count(e.s); i++) {
        const rg_setting_def *d = rg_settings_def(e.s, i);
        if (d->flags & RG_SETF_HIDDEN) continue;
        if (!(d->flags & (RG_SETF_RESTART | RG_SETF_GAMEPLAY))) continue;
        CHECK_EQ(go_to(&e, i), 0);
        rg_menu_line lines[RG_MENU_MAX_ROWS + 16];
        int n = rg_menu_render(&e.m, e.t, lines, RG_MENU_MAX_ROWS + 16);
        int ok = 0;
        for (int k = 0; k < n; k++)
            if (lines[k].selected && strstr(lines[k].text, (d->flags & RG_SETF_RESTART) ? "[restart]" : "[gameplay]")) ok = 1;
        if (!ok) fprintf(stderr, "%s: no marker\n", d->id);
        CHECK(ok);
    }
    /* the display trial still reverts after 15 s */
    int vs = rg_settings_find(e.s, "display.vsync");
    CHECK_EQ(go_to(&e, vs), 0);
    CHECK(menu_has(&e, "display change: reverts in 15 s unless kept"));
    bool v0 = rg_settings_get_bool(e.s, "display.vsync");
    cmd(&e, U_RIGHT);
    uint64_t t0 = e.t - 100;
    CHECK(rg_settings_get_bool(e.s, "display.vsync") != v0);
    CHECK(menu_has(&e, "Keep these display settings?"));
    CHECK(menu_has(&e, "(15 s)"));
    CHECK_EQ(rg_settings_trial_remaining(e.s, t0 + 14950), 50);
    while (e.t < t0 + 15000) ui_feed(&e, -1, -1, 0);
    CHECK(rg_settings_get_bool(e.s, "display.vsync") != v0);   /* last tick at t0 + 14950 */
    ui_feed(&e, -1, -1, 0);          /* t0 + 15000 */
    CHECK_EQ(rg_settings_get_bool(e.s, "display.vsync"), v0);
    CHECK(strstr(e.m.status, "not confirmed") != NULL);
    rg_settings_destroy(e.s);
    return 0;
}

/* ================================================================ P6 menu follow-ups */
/* Moves the editor cursor to row r with UI commands. */
static void editor_row(uienv *e, int r)
{
    for (int i = 0; i < 40 && e->m.sub != r; i++) cmd(e, e->m.sub < r ? U_DOWN : U_UP);
}

static int count_kind(const uienv *e, int idx, int dev)   /* 1 keyboard, 2 gamepad */
{
    rg_binding b[RG_BIND_MAX];
    int n = rg_binding_parse_list(rg_settings_get_string(e->s, rg_settings_def(e->s, idx)->id), b, NULL, 0);
    int k = 0;
    for (int i = 0; i < n; i++)
        k += dev == 1 ? b[i].kind == RG_BIND_KEY : (b[i].kind == RG_BIND_PAD_BUTTON || b[i].kind == RG_BIND_PAD_AXIS);
    return k;
}

/* The value of action `act` with only binding `b` of the device held. */
static int32_t fires(const rg_actions *a, int act, const rg_binding *b)
{
    static bool keys[SDL_SCANCODE_COUNT];
    rg_gamepad_snap pad;
    memset(keys, 0, sizeof keys);
    memset(&pad, 0, sizeof pad);
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.keys = keys;
    in.nkeys = SDL_SCANCODE_COUNT;
    in.pads = &pad;
    in.npads = 1;
    if (b->kind == RG_BIND_KEY) keys[b->code] = true;
    else if (b->kind == RG_BIND_PAD_BUTTON) pad.button[b->code] = 1;
    else if (b->kind == RG_BIND_PAD_AXIS) pad.axis[b->code] = b->pos ? 32767 : -32768;
    int32_t v[RG_ACT_COUNT];
    rg_actions_values(a, &in, v);
    return v[act];
}

/* Device guard: every menu control (ui_* incl. the overlay toggle) keeps a
 * keyboard and a gamepad binding through removes and replaces, driven by one
 * device only. */
static int device_guard_flow(int kb)
{
    uienv e;
    env_init(&e, kb);
    for (int act = RG_ACT_UI_UP; act <= RG_ACT_UI_OVERLAY; act++) {
        int idx = open_editor(&e, act, 0);
        CHECK(idx >= 0);
        if (idx < 0) continue;
        CHECK(menu_has(&e, "Menu control: keeps at least one keyboard and one gamepad binding"));
        CHECK(!menu_has(&e, "WARNING: no"));
        int refused = 0;
        /* remove every binding, last row first */
        for (int r = nbind(&e, idx) - 1; r >= 0; r--) {
            editor_row(&e, r);
            cmd(&e, U_RIGHT);
            CHECK(menu_has(&e, "[Remove]"));
            int before = nbind(&e, idx);
            cmd(&e, U_ACCEPT);
            if (nbind(&e, idx) == before) {
                refused++;
                CHECK(strstr(e.m.status, "not removed") != NULL);
                CHECK(strstr(e.m.status, "first (selected)") != NULL);
                CHECK_EQ(e.m.sub, nbind(&e, idx));   /* offered: the cursor is on "Add a binding" */
                CHECK(menu_has(&e, "> Add a binding"));
            }
        }
        CHECK_EQ(refused, 2);
        CHECK_EQ(nbind(&e, idx), 2);
        CHECK_EQ(count_kind(&e, idx, 1), 1);
        CHECK_EQ(count_kind(&e, idx, 2), 1);
        /* the survivors still drive the action (rebuilt like the host does) */
        {
            rg_actions a;
            rg_actions_from_settings(&a, e.s);
            rg_binding b[RG_BIND_MAX];
            int n = rg_binding_parse_list(rg_settings_get_string(e.s, rg_settings_def(e.s, idx)->id), b, NULL, 0);
            for (int i = 0; i < n; i++) CHECK(fires(&a, act, &b[i]) != 0);
        }
        /* replace the last binding of the device in use with the other device's
         * input: refused, offered as an add; accepting the offer keeps both */
        int row = -1;
        rg_binding b[RG_BIND_MAX];
        int n = rg_binding_parse_list(rg_settings_get_string(e.s, rg_settings_def(e.s, idx)->id), b, NULL, 0);
        for (int i = 0; i < n; i++)
            if (kb ? b[i].kind == RG_BIND_KEY : b[i].kind != RG_BIND_KEY) row = i;
        CHECK(row >= 0);
        editor_row(&e, row);
        CHECK_EQ(e.m.sub_col, 0);
        char before[256];
        snprintf(before, sizeof before, "%s", rg_settings_get_string(e.s, rg_settings_def(e.s, idx)->id));
        cmd(&e, U_ACCEPT);           /* Replace */
        CHECK(rg_menu_capturing(&e.m));
        const char *other;
        if (kb) { cap_button(&e, SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2); other = "pad:paddle3"; }
        else { cap_key(&e, SDL_SCANCODE_F14); other = "key:F14"; }
        {   /* SDL's name for the paddle */
            char nm[64];
            rg_binding one = { RG_BIND_PAD_BUTTON, 0, SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2 };
            rg_binding_format(&one, nm, sizeof nm);
            if (kb) CHECK_STR(other, nm);
        }
        CHECK(!rg_menu_capturing(&e.m));
        CHECK_STR(rg_settings_get_string(e.s, rg_settings_def(e.s, idx)->id), before);
        CHECK(strstr(e.m.status, "not replaced") != NULL);
        CHECK(strstr(e.m.status, kb ? "last keyboard binding" : "last gamepad binding") != NULL);
        CHECK_EQ(e.m.sub, 2);        /* on the offer */
        {
            char want[96];
            snprintf(want, sizeof want, "> Add %s instead", other);
            CHECK(menu_has(&e, want));
        }
        cmd(&e, U_ACCEPT);           /* take the offer */
        CHECK_EQ(nbind(&e, idx), 3);
        CHECK(strstr(rg_settings_get_string(e.s, rg_settings_def(e.s, idx)->id), other) != NULL);
        CHECK(strstr(e.m.status, "added") != NULL);
        CHECK(!menu_has(&e, "instead"));
        /* a replace within the same device is allowed */
        editor_row(&e, row);
        cmd(&e, U_ACCEPT);
        if (kb) cap_key(&e, SDL_SCANCODE_F15);
        else cap_button(&e, SDL_GAMEPAD_BUTTON_LEFT_PADDLE2);
        CHECK(strstr(e.m.status, "replaced by") != NULL);
        CHECK_EQ(count_kind(&e, idx, 1), kb ? 1 : 2);
        CHECK_EQ(count_kind(&e, idx, 2), kb ? 2 : 1);
        /* an offer is dropped by anything but accepting it */
        editor_row(&e, row);
        cmd(&e, U_ACCEPT);
        if (kb) cap_button(&e, SDL_GAMEPAD_BUTTON_MISC1);
        else cap_key(&e, SDL_SCANCODE_F16);
        CHECK(menu_has(&e, "instead"));   /* still the device's only binding: refused + offer */
        editor_row(&e, 0);
        CHECK(menu_has(&e, "instead"));   /* moving keeps it */
        cmd(&e, U_BACK);             /* drops the offer, leaves the editor */
        CHECK_EQ(e.m.view, RG_MENU_VIEW_PAGE);
        CHECK_EQ(e.m.offer[0], 0);
        cmd(&e, U_BACK);             /* closes the menu */
        CHECK(!e.m.open);
    }
    /* a binding list without one device (from a file): warned, and the
     * remaining device's last binding is still protected */
    CHECK_EQ(set(e.s, "input.bind.ui_accept", "key:Return", RG_SRC_FILE), RG_SET_OK);
    int acc = open_editor(&e, RG_ACT_UI_ACCEPT, 0);
    CHECK(menu_has(&e, "WARNING: no gamepad binding"));
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.ui_accept"), "key:Return");
    CHECK(strstr(e.m.status, "last keyboard binding") != NULL);
    cmd(&e, U_ACCEPT);               /* "Add a binding" (selected by the refusal) */
    CHECK(rg_menu_capturing(&e.m));
    cap_button(&e, SDL_GAMEPAD_BUTTON_SOUTH);
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.ui_accept"), "key:Return, pad:a");
    CHECK(!menu_has(&e, "WARNING: no"));
    cmd(&e, U_BACK);
    (void)acc;
    /* game actions are not guarded: map can become unbound */
    int mp = open_editor(&e, RG_ACT_MAP, 0);
    CHECK(mp >= 0);
    CHECK(!menu_has(&e, "Menu control"));
    for (int i = 0; i < 8 && nbind(&e, mp) > 0; i++) {
        editor_row(&e, 0);
        if (e.m.sub_col == 0) cmd(&e, U_RIGHT);   /* Remove stays picked on the row that moved up */
        cmd(&e, U_ACCEPT);
    }
    CHECK_EQ(nbind(&e, mp), 0);
    CHECK(strstr(e.m.status, "now unbound") != NULL);
    /* resets restore the defaults */
    cmd(&e, U_BACK);
    rg_settings_destroy(e.s);
    return 0;
}

static int t_menu_device_guard_keyboard(void) { return device_guard_flow(1); }
static int t_menu_device_guard_gamepad(void) { return device_guard_flow(0); }

/* The motion detector alone. */
static int t_capture_motion(void)
{
    rg_bind_capture c;
    rg_capture_init(&c);
    char t[96];
    /* an ordinary capture never takes motion */
    rg_capture_begin(&c, NULL, 0);
    CHECK(!c.motion);
    CHECK_EQ(rg_capture_mouse_motion(&c, 5000, 0), RG_CAPTURE_WAITING);
    rg_capture_end(&c);
    CHECK_EQ(rg_capture_mouse_motion(&c, 5000, 0), RG_CAPTURE_IDLE);
    /* a motion capture: net distance per axis, dominance 2:1 */
    rg_capture_begin_motion(&c);
    CHECK(c.motion);
    CHECK_EQ(rg_capture_mouse_motion(&c, 150, 0), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_mouse_motion(&c, 149, 0), RG_CAPTURE_WAITING);   /* 299 */
    CHECK_EQ(rg_capture_mouse_motion(&c, -100, 0), RG_CAPTURE_WAITING);  /* back: net 199 */
    CHECK_EQ(rg_capture_mouse_motion(&c, 100, 0), RG_CAPTURE_WAITING);   /* 299 */
    CHECK_EQ(rg_capture_mouse_motion(&c, 1, 0), RG_CAPTURE_DONE);        /* exactly 300 */
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "mouse:x+");
    rg_capture_begin_motion(&c);
    CHECK_EQ(rg_capture_mouse_motion(&c, -320, 200), RG_CAPTURE_WAITING);   /* diagonal: 320 < 2 x 200 */
    CHECK_EQ(rg_capture_mouse_motion(&c, -80, 0), RG_CAPTURE_DONE);         /* 400 = 2 x 200 */
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "mouse:x-");
    rg_capture_begin_motion(&c);   /* sums restart */
    CHECK_EQ(rg_capture_mouse_motion(&c, 0, 299.5f), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_mouse_motion(&c, 0, 0.5f), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "mouse:y+");
    rg_capture_begin_motion(&c);
    CHECK_EQ(rg_capture_mouse_motion(&c, 0, -1000), RG_CAPTURE_DONE);
    rg_capture_text(&c, t, sizeof t);
    CHECK_STR(t, "mouse:y-");
    /* keys and buttons are ignored, the cancel inputs still cancel */
    rg_capture_begin_motion(&c);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_A), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_mouse_button(&c, 1), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_pad_button(&c, SDL_GAMEPAD_BUTTON_SOUTH), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_pad_axis(&c, 0, SDL_GAMEPAD_AXIS_LEFTX, 32767), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_mouse_motion(&c, NAN, 0), RG_CAPTURE_WAITING);
    CHECK_EQ(rg_capture_key(&c, SDL_SCANCODE_ESCAPE), RG_CAPTURE_CANCELLED);
    rg_capture_begin_motion(&c);
    CHECK_EQ(rg_capture_pad_button(&c, SDL_GAMEPAD_BUTTON_GUIDE), RG_CAPTURE_CANCELLED);
    /* the captured text parses back to the same binding */
    rg_binding b[RG_BIND_MAX];
    CHECK_EQ(rg_binding_parse_list("mouse:y-", b, NULL, 0), 1);
    CHECK_EQ(b[0].kind, RG_BIND_MOUSE_MOTION);
    CHECK_EQ(b[0].code, 1);
    CHECK_EQ(b[0].pos, 0);
    CHECK_EQ(RG_CAPTURE_MOUSE_DIST, RG_MENU_MOTION_DIST);
    return 0;
}

/* "Capture mouse motion" through the menu, one device only. */
static int mouse_capture_flow(int kb)
{
    uienv e;
    env_init(&e, kb);
    int cr = rg_settings_find(e.s, "input.bind.camera_right");
    char def[256];
    snprintf(def, sizeof def, "%s", rg_settings_get_string(e.s, "input.bind.camera_right"));
    int n0 = nbind(&e, cr);
    CHECK_EQ(open_editor(&e, RG_ACT_CAMERA_RIGHT, n0 + 1), cr);
    CHECK(menu_has(&e, "> Capture mouse motion"));
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing(&e.m));
    CHECK(rg_menu_capturing_motion(&e.m));
    CHECK(e.cap.motion);
    CHECK(menu_has(&e, "Move the mouse far in one direction (300 px)"));
    CHECK(menu_has(&e, "keys and buttons are ignored"));
    /* presses don't bind; small motion doesn't either */
    cap_key(&e, SDL_SCANCODE_K);
    cap_button(&e, SDL_GAMEPAD_BUTTON_NORTH);
    cap_motion(&e, 120, 30);
    cap_motion(&e, 120, -30);
    CHECK(rg_menu_capturing(&e.m));
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.camera_right"), def);
    cap_motion(&e, 60, 0);           /* net 300, 0 */
    CHECK(!rg_menu_capturing(&e.m));
    /* the confirm step: nothing stored yet; other commands are ignored */
    CHECK_STR(e.m.confirm, "mouse:x+");
    CHECK(menu_has(&e, "Bind mouse:x+ to"));
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.camera_right"), def);
    int sub = e.m.sub;
    cmd(&e, U_DOWN);
    cmd(&e, U_NEXT);
    CHECK_EQ(e.m.sub, sub);
    CHECK_EQ(e.m.view, RG_MENU_VIEW_BINDINGS);
    cmd(&e, U_BACK);                 /* discard */
    CHECK_STR(rg_settings_get_string(e.s, "input.bind.camera_right"), def);
    CHECK(strstr(e.m.status, "discarded") != NULL);
    CHECK_EQ(e.m.confirm[0], 0);
    CHECK_EQ(e.m.view, RG_MENU_VIEW_BINDINGS);   /* BACK answered the question, did not leave */
    /* again, and accept */
    editor_row(&e, n0 + 1);
    cmd(&e, U_ACCEPT);
    cap_motion(&e, 10, -500);
    CHECK_STR(e.m.confirm, "mouse:y-");
    cmd(&e, U_ACCEPT);
    {
        char want[300];
        snprintf(want, sizeof want, "%s, mouse:y-", def);
        CHECK_STR(rg_settings_get_string(e.s, "input.bind.camera_right"), want);
    }
    CHECK(strstr(e.m.status, "added mouse:y-") != NULL);
    /* the motion drives the action */
    {
        rg_actions a;
        rg_actions_from_settings(&a, e.s);
        rg_input_snapshot in;
        memset(&in, 0, sizeof in);
        in.mouse_dy = -40;
        int32_t v[RG_ACT_COUNT];
        rg_actions_values(&a, &in, v);
        CHECK(v[RG_ACT_CAMERA_RIGHT] > 0);
    }
    /* a motion the action already has: no confirm, "already has" */
    editor_row(&e, nbind(&e, cr) + 1);
    cmd(&e, U_ACCEPT);
    cap_motion(&e, 0, -400);
    CHECK_EQ(e.m.confirm[0], 0);
    CHECK(strstr(e.m.status, "already has mouse:y-") != NULL);
    /* cancel (Esc / Guide) and the 5 s timeout */
    editor_row(&e, nbind(&e, cr) + 1);
    cmd(&e, U_ACCEPT);
    if (kb) cap_key(&e, SDL_SCANCODE_ESCAPE);
    else cap_button(&e, SDL_GAMEPAD_BUTTON_GUIDE);
    CHECK(!rg_menu_capturing(&e.m));
    CHECK(strstr(e.m.status, "cancelled") != NULL);
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_capturing_motion(&e.m));
    uint64_t t0 = e.t - 100;
    while (e.t < t0 + 5000) ui_feed(&e, -1, -1, 0);
    CHECK(rg_menu_capturing(&e.m));
    ui_feed(&e, -1, -1, 0);
    CHECK(!rg_menu_capturing(&e.m));
    CHECK(!e.m.capture_motion);
    CHECK(strstr(e.m.status, "no input for 5 s") != NULL);
    /* closing the overlay drops a pending confirm */
    cmd(&e, U_ACCEPT);
    cap_motion(&e, -400, 0);
    CHECK_STR(e.m.confirm, "mouse:x-");
    rg_menu_command(&e.m, RG_MENU_TOGGLE, e.t);
    CHECK_EQ(e.m.confirm[0], 0);
    CHECK(strstr(rg_settings_get_string(e.s, "input.bind.camera_right"), "mouse:x-") == NULL);
    rg_settings_destroy(e.s);
    return 0;
}

static int t_menu_mouse_capture_keyboard(void) { return mouse_capture_flow(1); }
static int t_menu_mouse_capture_gamepad(void) { return mouse_capture_flow(0); }

/* Long rows: rg_menu_wrap, and every view rendered at 640x480 (78 columns),
 * 1280x720 (84) and a narrow 40 keeps every line inside the width and every
 * character. */
static size_t nonspace(const char *s)
{
    size_t k = 0;
    for (; *s; s++) k += *s != ' ';
    return k;
}

static int wrap_check(const rg_menu_line *raw, int n, int cols, const char *what)
{
    static rg_menu_line out[4 * (RG_MENU_MAX_ROWS + 16)];
    int k = rg_menu_wrap(raw, n, cols, out, (int)(sizeof out / sizeof out[0]));
    size_t a = 0, b = 0;
    int bad = 0;
    for (int i = 0; i < n; i++) a += nonspace(raw[i].text);
    for (int i = 0; i < k; i++) {
        b += nonspace(out[i].text);
        if ((int)strlen(out[i].text) > cols) {
            if (!bad) fprintf(stderr, "%s @%d: %d > %d: \"%s\"\n", what, cols, (int)strlen(out[i].text), cols, out[i].text);
            bad = 1;
        }
    }
    CHECK(!bad);
    if (a != b) fprintf(stderr, "%s @%d: %zu vs %zu characters\n", what, cols, a, b);
    CHECK_EQ(a, b);
    return k;
}

static int render_wrap_all(uienv *e, const char *what)
{
    static rg_menu_line raw[RG_MENU_MAX_ROWS + 16];
    int n = rg_menu_render(&e->m, e->t, raw, RG_MENU_MAX_ROWS + 16);
    int longest = 0;
    for (int i = 0; i < n; i++) if ((int)strlen(raw[i].text) > longest) longest = (int)strlen(raw[i].text);
    static const int k_cols[] = { 78, 84, 40 };
    for (int c = 0; c < 3; c++) wrap_check(raw, n, k_cols[c], what);
    return longest;
}

static int t_menu_wrap(void)
{
    /* the wrapper alone */
    rg_menu_line in[3];
    memset(in, 0, sizeof in);
    snprintf(in[0].text, sizeof in[0].text, "short");
    snprintf(in[1].text, sizeof in[1].text, "> %-30s %s", "Label",
             "key:Space, key:X, key:Keypad 8, pad:a, pad:paddle1, axis:righttrigger+, mouse:x1, key:F");
    in[1].selected = true;
    in[1].indent = 33;
    snprintf(in[2].text, sizeof in[2].text, "%s",
             "012345678901234567890123456789012345678\xC3\xA9" "abcdefghij tail");
    in[2].indent = 4;
    rg_menu_line out[32];
    int k = rg_menu_wrap(in, 3, 40, out, 32);
    CHECK_STR(out[0].text, "short");
    CHECK_STR(out[1].text, "> Label");   /* "key:Space," would end at 43: breaks before, no trailing blanks */
    CHECK_STR(out[2].text, "                    key:Space, key:X,");
    for (int i = 1; i < k && out[i].selected; i++) {
        CHECK((int)strlen(out[i].text) <= 40);
        if (i > 1) CHECK(!strncmp(out[i].text, "                    ", 20));   /* indent clamped to cols / 2 */
    }
    int sel = 0;
    for (int i = 0; i < k; i++) sel += out[i].selected;
    CHECK(sel >= 3);
    /* a token longer than the line is broken hard; UTF-8 stays whole */
    CHECK_STR(out[k - 2].text, "012345678901234567890123456789012345678");   /* 39: e-acute not split */
    CHECK_STR(out[k - 1].text, "    \xC3\xA9" "abcdefghij tail");
    for (int i = 0; i < k; i++) {
        const unsigned char *p = (const unsigned char *)out[i].text;
        size_t L = strlen(out[i].text);
        if (L) CHECK(p[L - 1] != 0xC3);          /* never ends inside a sequence */
        CHECK((p[0] & 0xC0) != 0x80);
    }
    wrap_check(in, 3, 40, "unit");
    wrap_check(in, 3, 8, "unit");
    /* cap is honoured */
    CHECK_EQ(rg_menu_wrap(in, 3, 40, out, 2), 2);

    /* every view of the real menu */
    uienv e;
    env_init(&e, 1);
    cmd(&e, U_TOGGLE);
    int longest = 0;
    for (int p = 0; p < e.m.npages; p++) {
        int rows[RG_MENU_MAX_ROWS];
        int n = rg_menu_rows(&e.m, rows, RG_MENU_MAX_ROWS);
        for (int r = 0; r < n; r++) {   /* each selected row shows its own help */
            int L = render_wrap_all(&e, e.m.pages[e.m.page]);
            if (L > longest) longest = L;
            cmd(&e, U_DOWN);
        }
        cmd(&e, U_NEXT);
    }
    (void)longest;
    /* a full binding list on its row (no "..."), a conflict warning, the editor */
    CHECK_EQ(set(e.s, "input.bind.confirm",
                 "key:Space, key:X, key:Keypad 8, pad:a, pad:paddle1, axis:righttrigger+, mouse:x1, key:C",
                 RG_SRC_MENU), RG_SET_OK);
    CHECK_EQ(go_to(&e, rg_settings_find(e.s, "input.bind.confirm")), 0);
    CHECK(menu_has(&e, "mouse:x1, key:C"));
    CHECK(!menu_has(&e, "..."));
    CHECK(render_wrap_all(&e, "confirm row") > 84);   /* this one needs wrapping */
    cmd(&e, U_ACCEPT);
    render_wrap_all(&e, "editor");
    CHECK(menu_has(&e, "also: Cancel"));
    editor_row(&e, 7);
    cmd(&e, U_ACCEPT);
    cap_key(&e, SDL_SCANCODE_Z);     /* replaces key:C with attack's key: a long conflict status */
    CHECK(strstr(e.m.status, "WARNING") != NULL);
    CHECK((int)strlen(e.m.status) > 78);
    render_wrap_all(&e, "conflict status");
    editor_row(&e, 8 + 1);           /* capture mouse motion */
    cmd(&e, U_ACCEPT);
    render_wrap_all(&e, "motion prompt");
    cap_key(&e, SDL_SCANCODE_ESCAPE);
    cmd(&e, U_BACK);
    /* a guard refusal (the longest message) */
    open_editor(&e, RG_ACT_UI_OVERLAY, 0);
    cmd(&e, U_RIGHT);
    cmd(&e, U_ACCEPT);
    CHECK(strstr(e.m.status, "not removed") != NULL);
    render_wrap_all(&e, "guard refusal");
    cmd(&e, U_BACK);
    /* text entry with a long value */
    CHECK(text_open(&e, "system.screenshot_dir") >= 0);
    rg_menu_text_input(&e.m, "C:\\a\\very\\long\\folder\\name\\that\\goes\\on\\and\\on\\and\\on\\past\\the\\edge"
                             "\\of\\a\\small\\window\\for\\sure");
    render_wrap_all(&e, "text entry");
    rg_settings_destroy(e.s);
    return 0;
}

/* system.screenshot_dir applies at once: no [restart], no pending restart,
 * and a host picks the new folder up on its next pump. */
static int t_screenshot_dir_live(void)
{
    uienv e;
    env_init(&e, 1);
    int sd = rg_settings_find(e.s, "system.screenshot_dir");
    CHECK(sd >= 0);
    CHECK(!(rg_settings_def(e.s, sd)->flags & RG_SETF_RESTART));
    rg_settings_mark_applied(e.s);
    rg_host_config hc;
    rg_host_config_default(&hc);
    hc.headless = 1;
    rg_host *h = rg_host_create(&hc);
    CHECK(h != NULL);
    if (!h) { rg_settings_destroy(e.s); return 0; }
    rg_host_attach_settings(h, e.s, NULL);
    CHECK_STR(rg_host_screenshot_dir(h), ".");
    CHECK_EQ(go_to(&e, sd), 0);
    CHECK(!menu_has(&e, "[restart]"));
    cmd(&e, U_ACCEPT);
    CHECK(rg_menu_text_editing(&e.m));
    rg_menu_text_key(&e.m, RG_TEXT_BACKSPACE);
    rg_menu_text_input(&e.m, "shots");
    rg_menu_text_key(&e.m, RG_TEXT_COMMIT);
    CHECK_STR(rg_settings_get_string(e.s, "system.screenshot_dir"), "shots");
    CHECK_STR(e.m.status, "Screenshot folder set");
    int pend[8];
    CHECK_EQ(rg_settings_restart_pending(e.s, pend, 8), 0);
    CHECK(!menu_has(&e, "restart"));
    rg_host_pump(h);
    CHECK_STR(rg_host_screenshot_dir(h), "shots");
    char err[128];
    CHECK_EQ(rg_settings_set_text(e.s, sd, "", RG_SRC_API, err, sizeof err), RG_SET_OK);
    rg_host_pump(h);
    CHECK_STR(rg_host_screenshot_dir(h), ".");   /* empty = the working folder */
    rg_host_destroy(h);
    rg_settings_destroy(e.s);
    return 0;
}

/* display.fps_counter (docs/SETTINGS.md): off by default and in Original, no restart, no
 * display trial; RIGHT on its row steps off -> fps -> detailed; a headless host picks the mode
 * up on the next pump; the file and --set spellings round-trip. */
/* the selected row (its wrapped pieces) holds needle: a page-wide menu_has would also see other
 * rows (the display page has restart-flagged rows) */
static int menu_sel_has(const uienv *e, const char *needle)
{
    rg_menu_line lines[RG_MENU_MAX_ROWS + 16];
    int n = rg_menu_render(&e->m, e->t, lines, RG_MENU_MAX_ROWS + 16);
    for (int i = 0; i < n; i++) if (lines[i].selected && strstr(lines[i].text, needle)) return 1;
    return 0;
}

static int t_fps_counter(void)
{
    uienv e;
    env_init(&e, 1);
    int id = rg_settings_find(e.s, "display.fps_counter");
    CHECK(id >= 0);
    if (id < 0) { rg_settings_destroy(e.s); return 0; }
    const rg_setting_def *d = rg_settings_def(e.s, id);
    CHECK(!(d->flags & RG_SETF_RESTART));
    CHECK(!(d->flags & RG_SETF_DISPLAY));
    CHECK_EQ(d->enum_count, 3);
    CHECK_EQ(rg_settings_get_enum(e.s, "display.fps_counter"), 0);
    CHECK_EQ(rg_settings_apply_preset(e.s, "original"), 0);
    CHECK_EQ(rg_settings_get_enum(e.s, "display.fps_counter"), 0);
    CHECK_EQ(rg_settings_apply_preset(e.s, "default"), 0);
    rg_settings_mark_applied(e.s);
    rg_host_config hc;
    rg_host_config_default(&hc);
    hc.headless = 1;
    rg_host *h = rg_host_create(&hc);
    CHECK(h != NULL);
    if (!h) { rg_settings_destroy(e.s); return 0; }
    rg_host_attach_settings(h, e.s, NULL);
    CHECK_EQ(rg_host_fps_mode(h), 0);
    CHECK_EQ(go_to(&e, id), 0);
    CHECK(menu_sel_has(&e, "FPS counter"));
    CHECK(!menu_sel_has(&e, "[restart]"));
    cmd(&e, U_RIGHT);
    CHECK_EQ(rg_settings_get_enum(e.s, "display.fps_counter"), 1);
    rg_host_pump(h);
    CHECK_EQ(rg_host_fps_mode(h), 1);
    cmd(&e, U_RIGHT);
    CHECK_EQ(rg_settings_get_enum(e.s, "display.fps_counter"), 2);
    rg_host_pump(h);
    CHECK_EQ(rg_host_fps_mode(h), 2);
    int pend[8];
    CHECK_EQ(rg_settings_restart_pending(e.s, pend, 8), 0);
    CHECK(rg_settings_matches_preset(e.s, "original") == 0);
    rg_host_destroy(h);
    rg_settings_destroy(e.s);
    /* file / command line spellings */
    rg_settings *s = rg_settings_create();
    rg_settings_register_core(s);
    rg_settings_parse(s, "[display]\nfps_counter = detailed\n", "f.ini");
    CHECK_EQ(rg_settings_get_enum(s, "display.fps_counter"), 2);
    rg_settings_parse(s, "[display]\nfps_counter = FPS\n", "f.ini");
    CHECK_EQ(rg_settings_get_enum(s, "display.fps_counter"), 1);
    rg_settings_destroy(s);
    return 0;
}

/* ================================================================ main */
typedef struct test { const char *name; int (*fn)(void); } test;
static const test k_tests[] = {
    { "registry_types", t_registry_types }, { "ini_parse", t_ini_parse }, { "ini_roundtrip", t_ini_roundtrip },
    { "presets", t_presets }, { "cmdline", t_cmdline }, { "change_tracking", t_change_tracking },
    { "display_trial", t_display_trial }, { "save_load", t_save_load }, { "core_defs", t_core_defs },
    { "menu_keyboard", t_menu_keyboard }, { "menu_gamepad", t_menu_gamepad },
    { "invalid_control", t_invalid_control },
    { "binding_text", t_binding_text }, { "default_layout", t_default_layout }, { "ds2_report", t_ds2_report },
    { "multi_binding", t_multi_binding }, { "legacy_equivalence", t_legacy_equivalence }, { "tuning", t_tuning },
    { "mouse", t_mouse }, { "hotplug", t_hotplug }, { "latch", t_latch }, { "tap_cadence", t_tap_cadence }, { "tap_cadence_control", t_tap_cadence_control }, { "ui_nav", t_ui_nav },
    { "settings_bindings", t_settings_bindings }, { "script_bypass", t_script_bypass },
    { "action_aliases", t_action_aliases }, { "walk", t_walk }, { "stick_range", t_stick_range }, { "camera_convention", t_camera_convention }, { "stick_compensation", t_stick_compensation },
    { "report_control", t_report_control },
    { "menu_rebind_keyboard", t_menu_rebind_keyboard }, { "menu_rebind_gamepad", t_menu_rebind_gamepad },
    { "menu_text_entry", t_menu_text_entry }, { "menu_flags", t_menu_flags },
    { "capture", t_capture }, { "pad_family", t_pad_family }, { "prompt_style", t_prompt_style },
    { "menu_device_guard_keyboard", t_menu_device_guard_keyboard },
    { "menu_device_guard_gamepad", t_menu_device_guard_gamepad },
    { "capture_motion", t_capture_motion },
    { "menu_mouse_capture_keyboard", t_menu_mouse_capture_keyboard },
    { "menu_mouse_capture_gamepad", t_menu_mouse_capture_gamepad },
    { "menu_wrap", t_menu_wrap }, { "screenshot_dir_live", t_screenshot_dir_live },
    { "fps_counter", t_fps_counter },
};

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-settings-tests <name|all> [outdir]\n");
        return 2;
    }
    if (argc >= 3) g_out = argv[2];
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
