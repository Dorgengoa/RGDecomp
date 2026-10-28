/* SPDX-License-Identifier: CC0-1.0 */
/* Mouse camera (docs/INPUT.md "Mouse camera implementation"): the look
 * accumulator, the settings, the input-script look channel and the host latch.
 * rg-mouse-look-tests <name>; exit 0 = pass. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "host.h"
#include "rg_input.h"
#include "rg_settings.h"

static int g_fail;
#define CHECK(c) do { if (!(c)) { g_fail++; if (g_fail < 60) \
    fprintf(stderr, "%s:%d: CHECK failed: %s\n", __FILE__, __LINE__, #c); } } while (0)
#define CHECK_EQ(a, b) do { long long _a = (long long)(a), _b = (long long)(b); \
    if (_a != _b) { g_fail++; if (g_fail < 60) fprintf(stderr, \
    "%s:%d: %s == %lld, expected %s == %lld\n", __FILE__, __LINE__, #a, _a, #b, _b); } } while (0)

static rg_settings *mk(void)
{
    rg_settings *s = rg_settings_create();
    CHECK_EQ(rg_settings_register_core(s), 0);
    CHECK_EQ(rg_actions_register_settings(s), 0);
    return s;
}

static int set(rg_settings *s, const char *id, const char *text)
{
    return rg_settings_set_text(s, rg_settings_find(s, id), text, RG_SRC_API, NULL, 0);
}

static rg_look_acc acc_on(float xs, float ys)
{
    rg_look_acc a;
    rg_look_acc_init(&a);
    a.enabled = true;
    a.yaw_scale = xs;
    a.pitch_scale = ys;
    return a;
}

/* Units, sub-step accumulation, no saturation or quantisation loss. */
static int t_look_quantise(void)
{
    rg_look l;
    /* off: motion is dropped */
    rg_look_acc a;
    rg_look_acc_init(&a);
    CHECK(!a.enabled);
    rg_look_acc_motion(&a, 100, 100);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    /* 1 count at scale 1 = RG_LOOK_RAD_PER_COUNT rad = 6.144 units: 100 counts = 614 (614.4) */
    a = acc_on(1, 1);
    rg_look_acc_motion(&a, 100, 0);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 614);
    CHECK_EQ(l.pitch, 0);
    /* the 0.4 remainder is carried: the next 100 give 615 (1228.8 - 614 = 614.8) */
    rg_look_acc_motion(&a, 100, 0);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 615);
    /* mouse up (dy < 0) is look up (pitch > 0); right is yaw > 0 */
    a = acc_on(1, 1);
    rg_look_acc_motion(&a, -10, -10);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, -61);
    CHECK_EQ(l.pitch, 61);
    /* inversion and scales */
    a = acc_on(2.0f, 0.5f);
    a.invert_x = a.invert_y = true;
    rg_look_acc_motion(&a, 10, 10);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, -123);   /* -122.88 */
    CHECK_EQ(l.pitch, 31);   /* 30.72 */
    /* sub-step: 10,000 motions of 0.05 counts, a take every 7 = 500 counts =
     * exactly 3072 units in total, no take loses or invents anything */
    a = acc_on(1, 1);
    long long sy = 0, sp = 0;
    int nonzero = 0;
    for (int i = 0; i < 10000; i++) {
        rg_look_acc_motion(&a, 0.05f, -0.05f);
        if (i % 7 == 6 || i == 9999) {
            rg_look_acc_take(&a, &l);
            sy += l.yaw;
            sp += l.pitch;
            nonzero += l.yaw != 0;
            CHECK(l.yaw >= 0 && l.yaw <= 3);   /* 7 x 0.3072 = 2.15 per take */
        }
    }
    CHECK(llabs(sy - 3072) <= 1);
    CHECK(llabs(sp - 3072) <= 1);
    CHECK(nonzero > 1000);   /* small motion is not lost in a dead band */
    /* back and forth nets zero */
    a = acc_on(1.3f, 0.7f);
    sy = sp = 0;
    for (int i = 0; i < 1000; i++) {
        rg_look_acc_motion(&a, (i & 1) ? 3.3f : -3.3f, (i & 1) ? -1.7f : 1.7f);
        rg_look_acc_take(&a, &l);
        sy += l.yaw;
        sp += l.pitch;
    }
    CHECK(llabs(sy) <= 1);
    CHECK(llabs(sp) <= 1);
    /* random motion: the sum of the takes == round(total) within one unit */
    a = acc_on(1.7f, 0.9f);
    srand(7);
    double tot_y = 0, tot_p = 0;
    sy = sp = 0;
    for (int i = 0; i < 20000; i++) {
        float dx = (float)(rand() % 4001 - 2000) / 100.0f, dy = (float)(rand() % 4001 - 2000) / 100.0f;
        rg_look_acc_motion(&a, dx, dy);
        tot_y += (double)dx * 1.7f * RG_LOOK_RAD_PER_COUNT * RG_LOOK_UNITS_PER_RAD;
        tot_p += -(double)dy * 0.9f * RG_LOOK_RAD_PER_COUNT * RG_LOOK_UNITS_PER_RAD;
        if (i % 3 == 0) {
            rg_look_acc_take(&a, &l);
            sy += l.yaw;
            sp += l.pitch;
        }
    }
    rg_look_acc_take(&a, &l);
    sy += l.yaw;
    sp += l.pitch;
    CHECK(fabs((double)sy - tot_y) <= 1.0);
    CHECK(fabs((double)sp - tot_p) <= 1.0);
    /* a flick far beyond a latch's range clamps (no wrap) and the excess is dropped */
    a = acc_on(10, 10);
    rg_look_acc_motion(&a, 1e6f, -1e6f);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, RG_LOOK_MAX);
    CHECK_EQ(l.pitch, RG_LOOK_MAX);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    rg_look_acc_motion(&a, -1e6f, 1e6f);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, -RG_LOOK_MAX);
    CHECK_EQ(l.pitch, -RG_LOOK_MAX);
    /* NaN / inf are ignored */
    rg_look_acc_motion(&a, NAN, INFINITY);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    /* reset drops pending and remainder */
    a = acc_on(1, 1);
    rg_look_acc_motion(&a, 0.1f, 0);
    rg_look_acc_motion(&a, 50, 50);
    rg_look_acc_reset(&a);
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    CHECK(a.rem_yaw == 0.0 && a.rem_pitch == 0.0);
    return 0;
}

/* The settings: ids, types, defaults, the Original preset, not gameplay. */
static int t_look_settings(void)
{
    rg_settings *s = mk();
    const char *ids[] = { "input.mouse_look", "input.mouse_yaw_scale", "input.mouse_pitch_scale",
                          "input.mouse_invert_x", "input.mouse_invert_y" };
    for (size_t i = 0; i < sizeof ids / sizeof ids[0]; i++) {
        int k = rg_settings_find(s, ids[i]);
        CHECK(k >= 0);
        if (k < 0) continue;
        const rg_setting_def *d = rg_settings_def(s, k);
        CHECK(!(d->flags & RG_SETF_GAMEPLAY));
        CHECK(!(d->flags & RG_SETF_PLACEHOLDER));
        CHECK(!(d->flags & RG_SETF_HIDDEN));
        CHECK(d->label != NULL);
    }
    CHECK(rg_settings_get_bool(s, "input.mouse_look"));          /* default on */
    CHECK(rg_settings_get_float(s, "input.mouse_yaw_scale") == 1.0);
    CHECK(rg_settings_get_float(s, "input.mouse_pitch_scale") == 1.0);
    CHECK(!rg_settings_get_bool(s, "input.mouse_invert_x"));
    CHECK(!rg_settings_get_bool(s, "input.mouse_invert_y"));
    rg_look_acc a;
    rg_look_acc_init(&a);
    rg_look_acc_from_settings(&a, s);
    CHECK(a.enabled);
    /* Original: off */
    CHECK_EQ(rg_settings_apply_preset(s, "original"), 0);
    CHECK(!rg_settings_get_bool(s, "input.mouse_look"));
    CHECK(rg_settings_matches_preset(s, "original"));
    rg_look_acc_from_settings(&a, s);
    CHECK(!a.enabled);
    set(s, "input.mouse_look", "on");
    set(s, "input.mouse_yaw_scale", "2.5");
    set(s, "input.mouse_pitch_scale", "0.5");
    set(s, "input.mouse_invert_y", "true");
    CHECK(!rg_settings_matches_preset(s, "original"));
    /* from_settings keeps the remainder and the pending value */
    a.enabled = true;
    a.yaw_scale = a.pitch_scale = 1;
    rg_look_acc_motion(&a, 1, 0);   /* 6.144: pending 6, remainder 0.144 */
    rg_look_acc_from_settings(&a, s);
    CHECK(a.enabled && a.yaw_scale == 2.5f && a.pitch_scale == 0.5f && a.invert_y && !a.invert_x);
    rg_look l;
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.yaw, 6);
    CHECK(fabs(a.rem_yaw - 0.144) < 1e-6);
    rg_look_acc_motion(&a, 0, 10);   /* inverted: down = up... = -30.72 */
    rg_look_acc_take(&a, &l);
    CHECK_EQ(l.pitch, 31);
    /* out of range refused */
    CHECK(set(s, "input.mouse_yaw_scale", "50") < 0 || rg_settings_get_float(s, "input.mouse_yaw_scale") <= 10.0);
    rg_settings_destroy(s);
    return 0;
}

static const char *k_buttons_only = "10 20 CROSS\n15 CIRCLE+START\n100 140 UP\n";
static const char *k_with_look =
    "10 20 CROSS\n"
    "#!look 1 0\n"
    "15 CIRCLE+START\n"
    "#!look 50 100 -200       # one latch\n"
    "#!look 60 63 8 -4\n"
    "#!look 62 1 1\n"
    "  #!look 70 32767 -32767\n"
    "100 140 UP\n"
    "# an ordinary comment\n";

/* The input-script look channel. */
static int t_look_script(void)
{
    char err[256];
    rg_input_script a = { 0 }, b = { 0 };
    CHECK_EQ(rg_input_script_parse(&a, k_buttons_only, "a", err, sizeof err), 0);
    CHECK_EQ(rg_input_script_parse(&b, k_with_look, "b", err, sizeof err), 0);
    /* the button table and its blob are unchanged by look lines */
    CHECK_EQ(a.count, b.count);
    CHECK_EQ(a.span, b.span);
    CHECK(!memcmp(a.words, b.words, a.count * sizeof a.words[0]));
    size_t na = rg_input_script_blob(&a, NULL, 0);
    uint8_t *ba = (uint8_t *)malloc(na), *bb = (uint8_t *)malloc(na);
    rg_input_script_blob(&a, ba, na);
    rg_input_script_blob(&b, bb, na);
    CHECK(!memcmp(ba, bb, na));
    free(ba);
    free(bb);
    /* no channel */
    rg_look l = { 5, 5 };
    CHECK_EQ(rg_input_script_look(&a, 50, &l), 0);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    CHECK(a.look == NULL);
    /* values; ranges; overlapping lines add; elsewhere 0 */
    CHECK_EQ(rg_input_script_look(&b, 50, &l), 1);
    CHECK_EQ(l.yaw, 100);
    CHECK_EQ(l.pitch, -200);
    for (uint32_t v = 60; v <= 63; v++) {
        rg_input_script_look(&b, v, &l);
        CHECK_EQ(l.yaw, v == 62 ? 9 : 8);
        CHECK_EQ(l.pitch, v == 62 ? -3 : -4);
    }
    rg_input_script_look(&b, 70, &l);
    CHECK_EQ(l.yaw, 32767);
    CHECK_EQ(l.pitch, -32767);
    rg_input_script_look(&b, 51, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    rg_input_script_look(&b, 1000000, &l);   /* beyond the table */
    CHECK_EQ(l.yaw, 0);
    /* errors */
    static const char *bad[] = {
        "#!look 50 1 2\n",                      /* no version line */
        "#!look 2 0\n",                         /* unknown version */
        "#!look 1 0\n#!look 50 1\n#!look 1 0\n", /* repeated version / too few values: 50 1 = version again */
        "#!look 1 0\n#!look 50 40000 0\n",      /* out of range */
        "#!look 1 0\n#!look 50 30000 0\n#!look 50 3000 0\n", /* the sum is out of range */
        "#!look 1 0\n#!look 50 x 0\n",          /* bad integer */
        "#!look 1 0\n#!look 60 50 1 1\n",       /* first > last */
        "#!look 1 0\n#!look 50 1 2 3 4\n",      /* too many values */
        "#!look 1 0\n#!look 99999 1 2\n",       /* beyond the table */
    };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; i++) {
        rg_input_script c = { 0 };
        err[0] = 0;
        int rc = rg_input_script_parse(&c, bad[i], "bad", err, sizeof err);
        if (rc == 0) fprintf(stderr, "accepted bad script %u\n", (unsigned)i);
        CHECK_EQ(rc, -1);
        CHECK(strstr(err, "bad:") != NULL);
        rg_input_script_free(&c);
    }
    /* "#!lookx" and "# !look" are plain comments */
    rg_input_script c = { 0 };
    CHECK_EQ(rg_input_script_parse(&c, "#!lookx 1 2\n# !look 50 1 2\n5 CROSS\n", "c", err, sizeof err), 0);
    CHECK(c.look == NULL);
    rg_input_script_free(&c);
    rg_input_script_free(&a);
    rg_input_script_free(&b);
    return 0;
}

static rg_host *mk_host(rg_settings *s)
{
    rg_host_config hc;
    rg_host_config_default(&hc);
    rg_host_config_from_settings(&hc, s);
    hc.headless = 1;
    rg_host *h = rg_host_create(&hc);
    CHECK(h != NULL);
    if (h) rg_host_attach_settings(h, s, NULL);
    return h;
}

/* The host latch: injected motion (the scripted mouse path rg-game
 * --mouse-motion uses), the setting gate, scripts, consume-once. */
static int t_look_host(void)
{
    rg_settings *s = mk();
    rg_host *h = mk_host(s);
    if (!h) return 1;
    rg_look l;
    CHECK(!rg_host_look_captured(h));   /* headless never captures */
    /* nothing pending: zero */
    rg_host_look_latch(h, 0, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    /* default on: injected motion arrives at the next latch, once */
    rg_host_look_inject(h, 100, -50);
    rg_host_look_latch(h, 1, &l);
    CHECK_EQ(l.yaw, 614);
    CHECK_EQ(l.pitch, 307);
    rg_host_look_latch(h, 2, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    /* several injections before a latch add up */
    rg_host_look_inject(h, 10, 0);
    rg_host_look_inject(h, 10, 0);
    rg_host_look_latch(h, 3, &l);
    CHECK_EQ(l.yaw, 123);   /* 0.4 carried + 122.88 = 123.28 */
    /* the settings apply live (the host checks them every pump) */
    set(s, "input.mouse_invert_x", "true");
    set(s, "input.mouse_yaw_scale", "0.5");
    CHECK(rg_host_pump(h));
    rg_host_look_inject(h, 100, 0);
    rg_host_look_latch(h, 4, &l);
    CHECK_EQ(l.yaw, -307);   /* 0.28 - 307.2 = -306.92 */
    /* Original: off, injected motion is dropped */
    CHECK_EQ(rg_settings_apply_preset(s, "original"), 0);
    CHECK(rg_host_pump(h));
    rg_host_look_inject(h, 100, 100);
    rg_host_look_latch(h, 5, &l);
    CHECK_EQ(l.yaw, 0);
    CHECK_EQ(l.pitch, 0);
    /* a script with a look channel: the latch is the script's value at the vbl
     * (the setting does not matter: settings never touch a scripted run) */
    char err[256];
    rg_input_script sc = { 0 }, sb = { 0 };
    CHECK_EQ(rg_input_script_parse(&sc, k_with_look, "b", err, sizeof err), 0);
    CHECK_EQ(rg_input_script_parse(&sb, k_buttons_only, "a", err, sizeof err), 0);
    rg_host_set_input_script(h, &sc);
    rg_host_look_latch(h, 50, &l);
    CHECK_EQ(l.yaw, 100);
    CHECK_EQ(l.pitch, -200);
    rg_host_look_latch(h, 50, &l);   /* a script latch is a pure function of the vbl */
    CHECK_EQ(l.yaw, 100);
    rg_host_look_latch(h, 51, &l);
    CHECK_EQ(l.yaw, 0);
    /* scripted + injected (the test path): both, added */
    set(s, "input.mouse_look", "on");
    set(s, "input.mouse_invert_x", "false");
    set(s, "input.mouse_yaw_scale", "1");
    CHECK(rg_host_pump(h));
    rg_host_look_latch(h, 0, &l);   /* flush the carried remainder's unit, if any */
    rg_host_look_inject(h, 100, 0);
    rg_host_look_latch(h, 50, &l);
    CHECK(l.yaw == 100 + 614 || l.yaw == 100 + 615);
    /* a buttons-only script latches 0 (every existing script keeps its meaning) */
    rg_host_set_input_script(h, &sb);
    for (uint32_t v = 0; v < 200; v++) {
        rg_host_look_latch(h, v, &l);
        CHECK_EQ(l.yaw, 0);
        CHECK_EQ(l.pitch, 0);
    }
    /* the pad reads are untouched by the look channel */
    rg_pad p, q;
    rg_host_set_input_script(h, &sc);
    rg_host_read_pad(h, 0, 15, &p);
    rg_input_script_pad(&sb, 15, &q);
    CHECK(!memcmp(&p, &q, sizeof p));
    /* the camera-activity hint is accepted headless (no capture) */
    rg_host_set_look_active(h, true);
    CHECK(rg_host_pump(h));
    CHECK(!rg_host_look_captured(h));
    rg_host_set_input_script(h, NULL);
    rg_host_destroy(h);
    rg_settings_destroy(s);
    rg_input_script_free(&sc);
    rg_input_script_free(&sb);
    return 0;
}

/* Control (WILL_FAIL): expects motion to arrive with the setting off. */
static int t_look_control(void)
{
    rg_settings *s = mk();
    rg_settings_apply_preset(s, "original");
    rg_host *h = mk_host(s);
    if (!h) return 1;
    rg_look l;
    rg_host_look_inject(h, 100, 0);
    rg_host_look_latch(h, 1, &l);
    CHECK_EQ(l.yaw, 614);
    rg_host_destroy(h);
    rg_settings_destroy(s);
    return 0;
}

typedef struct test { const char *name; int (*fn)(void); } test;
static const test k_tests[] = {
    { "look_quantise", t_look_quantise }, { "look_settings", t_look_settings },
    { "look_script", t_look_script }, { "look_host", t_look_host },
    { "look_control", t_look_control },
};

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "usage: rg-mouse-look-tests <name|all>\n");
        return 2;
    }
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
