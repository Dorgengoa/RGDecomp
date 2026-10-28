/* SPDX-License-Identifier: CC0-1.0 */
/* The overlay hold chord and the overlay prompts (docs/INPUT.md "Opening the
 * settings overlay with a gamepad", "Prompts in the settings overlay"):
 * rg-chord-tests <name>; exit 0 = pass.  The pad report is built exactly as
 * host_sdl.c builds it: snapshot -> rg_chord_update (once per pump) ->
 * rg_chord_filter -> rg_actions_eval. */
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
    "%s:%d: %s == %lld, expected %s == %lld\n", __FILE__, __LINE__, #a, _a, #b, _b); } } while (0)
#define CHECK_STR(a, b) do { const char *_a = (a), *_b = (b); \
    if (strcmp(_a ? _a : "(null)", _b ? _b : "(null)")) { g_fail++; if (g_fail < 60) \
    fprintf(stderr, "%s:%d: %s == \"%s\", expected \"%s\"\n", __FILE__, __LINE__, #a, \
    _a ? _a : "(null)", _b ? _b : "(null)"); } } while (0)

enum { BACK = SDL_GAMEPAD_BUTTON_BACK, START = SDL_GAMEPAD_BUTTON_START, SOUTH = SDL_GAMEPAD_BUTTON_SOUTH,
       LB = SDL_GAMEPAD_BUTTON_LEFT_SHOULDER, RB = SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER,
       MISC1 = SDL_GAMEPAD_BUTTON_MISC1, PADDLE = SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1 };
#define FIELD_MS 17

static rg_settings *mk(void)
{
    rg_settings *s = rg_settings_create();
    CHECK_EQ(rg_settings_register_core(s), 0);
    CHECK_EQ(rg_actions_register_settings(s), 0);
    return s;
}

/* One or two pads feeding port 0, stepped one field (pump) at a time. */
typedef struct env {
    rg_settings *s;
    rg_actions a;
    rg_chord c;
    uint64_t t;
    int fires;
    int npads;
} env;

static void env_init(env *e, rg_settings *s)
{
    memset(e, 0, sizeof *e);
    e->s = s;
    rg_actions_from_settings(&e->a, s);
    rg_chord_init(&e->c);
    rg_chord_from_settings(&e->c, s);
    e->npads = 1;
}

/* held[p] = bit mask (1 << SDL button) of pad p's buttons this field; returns the report's buttons */
static uint16_t field2(env *e, uint32_t held0, uint32_t held1)
{
    rg_gamepad_snap pads[2];
    memset(pads, 0, sizeof pads);
    uint32_t held[2] = { held0, held1 };
    for (int p = 0; p < e->npads; p++) {
        for (int b = 0; b < 32; b++) pads[p].button[b] = (held[p] >> b) & 1;
        if (rg_chord_update(&e->c, p, &pads[p], e->t)) e->fires++;
        rg_chord_filter(&e->c, p, &pads[p]);
    }
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.pads = pads;
    in.npads = e->npads;
    rg_pad out;
    rg_actions_eval(&e->a, &in, &out);
    e->t += FIELD_MS;
    return out.buttons;
}

static uint16_t field(env *e, uint32_t held) { return field2(e, held, 0); }

#define B(x) (1u << (x))
#define SS (RG_BTN_SELECT | RG_BTN_START)

/* ---------------------------------------------------------------- tests */
static int t_chord_settings(void)
{
    rg_settings *s = mk();
    int i = rg_settings_find(s, "input.overlay_chord");
    CHECK(i >= 0);
    const rg_setting_def *d = rg_settings_def(s, i);
    CHECK_EQ(d->type, RG_SET_BINDING);
    CHECK_STR(d->category, "controls_ui");
    CHECK(!(d->flags & (RG_SETF_GAMEPLAY | RG_SETF_HIDDEN | RG_SETF_PLACEHOLDER)));
    CHECK(d->flags & RG_SETF_HAS_ORIGINAL);
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "pad:back, pad:start");
    int h = rg_settings_find(s, "input.overlay_chord_hold");
    CHECK(h >= 0);
    CHECK(rg_settings_get_float(s, "input.overlay_chord_hold") == 1.0);
    CHECK(rg_settings_def(s, h)->flags & RG_SETF_HAS_ORIGINAL);
    /* Original keeps the chord (live input only) */
    CHECK_EQ(rg_settings_set_text(s, i, "pad:a, pad:b", RG_SRC_API, NULL, 0), RG_SET_OK);
    CHECK_EQ(rg_settings_apply_preset(s, "original"), 0);
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "pad:back, pad:start");
    CHECK(rg_settings_get_float(s, "input.overlay_chord_hold") == 1.0);
    /* the validator: pad buttons only, at most 4, canonical text, empty = off */
    char err[160];
    static const char *const bad[] = { "key:F1", "pad:back, key:Return", "axis:lefttrigger+",
                                       "mouse:left", "pad:a, pad:b, pad:x, pad:y, pad:start", "pad:nope" };
    for (size_t k = 0; k < sizeof bad / sizeof bad[0]; k++) {
        err[0] = 0;
        CHECK(rg_settings_set_text(s, i, bad[k], RG_SRC_API, err, sizeof err) < 0);
        CHECK(err[0] != 0);
    }
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "pad:back, pad:start");
    CHECK_EQ(rg_settings_set_text(s, i, "PAD:LeftShoulder ,pad:rightshoulder, pad:start", RG_SRC_API, NULL, 0),
             RG_SET_OK);
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "pad:leftshoulder, pad:rightshoulder, pad:start");
    CHECK_EQ(rg_settings_set_text(s, i, "", RG_SRC_API, NULL, 0), RG_SET_OK);
    /* from_settings */
    rg_chord c;
    rg_chord_init(&c);
    rg_chord_from_settings(&c, s);
    CHECK_EQ(c.n, 0);
    rg_settings_set_text(s, i, "pad:misc1", RG_SRC_API, NULL, 0);
    rg_settings_set_float(s, "input.overlay_chord_hold", 2.0, RG_SRC_API);
    rg_settings_set_int(s, "input.min_press_fields", 4, RG_SRC_API);
    rg_chord_from_settings(&c, s);
    CHECK_EQ(c.n, 1);
    CHECK_EQ(c.button[0], MISC1);
    CHECK_EQ(c.hold_ms, 2000);
    CHECK_EQ(c.tap_fields, 4);
    rg_settings_set_int(s, "input.min_press_fields", 0, RG_SRC_API);
    rg_chord_from_settings(&c, s);
    CHECK_EQ(c.tap_fields, 2);   /* a held-back tap still reaches the game */
    /* rg_chord_set: duplicates dropped; non-buttons refused (unchanged) */
    rg_binding b[3] = { { RG_BIND_PAD_BUTTON, 0, BACK }, { RG_BIND_PAD_BUTTON, 0, BACK }, { RG_BIND_PAD_BUTTON, 0, START } };
    CHECK_EQ(rg_chord_set(&c, b, 3), 0);
    CHECK_EQ(c.n, 2);
    rg_binding k = { RG_BIND_KEY, 0, SDL_SCANCODE_F1 };
    CHECK_EQ(rg_chord_set(&c, &k, 1), -1);
    CHECK_EQ(c.n, 2);
    rg_settings_destroy(s);
    return 0;
}

/* Every way of pressing the default chord: Select / Start never reach the report. */
static int t_chord_no_leak(void)
{
    rg_settings *s = mk();
    env e;
    uint16_t r;
    /* a: both in the same field, held 1.2 s: fires once at 1 s */
    env_init(&e, s);
    int fired_at = -1;
    for (int f = 0; f < 72; f++) {
        int before = e.fires;
        r = field(&e, B(BACK) | B(START));
        CHECK(!(r & SS));
        if (e.fires != before && fired_at < 0) fired_at = f;
    }
    CHECK_EQ(e.fires, 1);
    CHECK(fired_at * FIELD_MS >= 1000 && fired_at * FIELD_MS < 1000 + FIELD_MS);
    for (int f = 0; f < 10; f++) CHECK(!(field(&e, 0) & SS));        /* release */
    /* b: Select first, Start 50 ms (3 fields) later; held; then released one by one */
    env_init(&e, s);
    for (int f = 0; f < 3; f++) CHECK(!(field(&e, B(BACK)) & SS));
    for (int f = 0; f < 70; f++) CHECK(!(field(&e, B(BACK) | B(START)) & SS));
    CHECK_EQ(e.fires, 1);
    for (int f = 0; f < 20; f++) CHECK(!(field(&e, B(START)) & SS));   /* Start still held: held back */
    for (int f = 0; f < 10; f++) CHECK(!(field(&e, 0) & SS));
    CHECK_EQ(e.fires, 1);
    /* c: both, let go after 0.5 s: no fire, nothing reaches the game */
    env_init(&e, s);
    for (int f = 0; f < 30; f++) CHECK(!(field(&e, B(BACK) | B(START)) & SS));
    for (int f = 0; f < 3; f++) CHECK(!(field(&e, B(BACK)) & SS));
    for (int f = 0; f < 20; f++) CHECK(!(field(&e, 0) & SS));
    CHECK_EQ(e.fires, 0);
    /* d: uneven press at the edge of the grace (5 fields = 85 ms) */
    env_init(&e, s);
    for (int f = 0; f < 5; f++) CHECK(!(field(&e, B(START)) & SS));
    for (int f = 0; f < 70; f++) CHECK(!(field(&e, B(BACK) | B(START)) & SS));
    CHECK_EQ(e.fires, 1);
    /* the gate is armed: the second press of a held, fired chord re-arms only after release */
    for (int f = 0; f < 80; f++) CHECK(!(field(&e, B(BACK) | B(START)) & SS));
    CHECK_EQ(e.fires, 1);
    for (int f = 0; f < 3; f++) field(&e, 0);
    for (int f = 0; f < 62; f++) field(&e, B(BACK) | B(START));
    CHECK_EQ(e.fires, 2);
    /* e: other buttons pass at once, also while the chord is held */
    env_init(&e, s);
    r = field(&e, B(SOUTH));
    CHECK(r & RG_BTN_CROSS);
    r = field(&e, B(SOUTH) | B(BACK) | B(START));
    CHECK(r & RG_BTN_CROSS);
    CHECK(!(r & SS));
    rg_settings_destroy(s);
    return 0;
}

/* A lone Start / Select still works: late by the grace, never lost. */
static int t_chord_lone_press(void)
{
    rg_settings *s = mk();
    env e;
    /* a tap (2 fields) inside the grace: seen afterwards for exactly tap_fields fields */
    env_init(&e, s);
    CHECK(!(field(&e, B(START)) & RG_BTN_START));
    CHECK(!(field(&e, B(START)) & RG_BTN_START));
    int seen = 0, first = -1;
    for (int f = 0; f < 10; f++) {
        uint16_t r = field(&e, 0);
        if (r & RG_BTN_START) { seen++; if (first < 0) first = f; }
        CHECK(!(r & RG_BTN_SELECT));
    }
    CHECK_EQ(seen, e.c.tap_fields);
    CHECK_EQ(first, 0);
    CHECK_EQ(e.fires, 0);
    /* a hold: held back for the grace (6 fields at 17 ms), then seen until release */
    env_init(&e, s);
    int on = 0, off_first = 0;
    for (int f = 0; f < 30; f++) {
        uint16_t r = field(&e, B(BACK));
        if (r & RG_BTN_SELECT) on++;
        else if (!on) off_first++;
        else CHECK(!"Select dropped while held");
    }
    CHECK_EQ(off_first, (RG_CHORD_GRACE_MS + FIELD_MS - 1) / FIELD_MS);
    CHECK_EQ(on, 30 - off_first);
    CHECK(!(field(&e, 0) & RG_BTN_SELECT));   /* released: gone at once */
    CHECK_EQ(e.fires, 0);
    /* a press that already passed, then the rest of the chord: still opens; the
     * game sees that button released */
    env_init(&e, s);
    for (int f = 0; f < 20; f++) field(&e, B(START));
    CHECK(field(&e, B(START)) & RG_BTN_START);
    for (int f = 0; f < 61; f++) CHECK(!(field(&e, B(START) | B(BACK)) & SS));
    CHECK_EQ(e.fires, 1);
    /* the chord is per pad: Select on pad 0 + Start on pad 1 is two lone presses */
    env_init(&e, s);
    e.npads = 2;
    uint16_t r = 0;
    for (int f = 0; f < 70; f++) r = field2(&e, B(BACK), B(START));
    CHECK_EQ(e.fires, 0);
    CHECK((r & SS) == SS);
    /* off (empty chord): Start reaches the game in the same field */
    rg_settings_set_text(s, rg_settings_find(s, "input.overlay_chord"), "", RG_SRC_API, NULL, 0);
    env_init(&e, s);
    CHECK(field(&e, B(START)) & RG_BTN_START);
    for (int f = 0; f < 70; f++) field(&e, B(BACK) | B(START));
    CHECK_EQ(e.fires, 0);
    rg_settings_destroy(s);
    return 0;
}

/* Rebinding: a new chord takes over, the old buttons are plain game input again. */
static int t_chord_rebind(void)
{
    rg_settings *s = mk();
    int i = rg_settings_find(s, "input.overlay_chord");
    CHECK_EQ(rg_settings_set_text(s, i, "pad:leftshoulder, pad:rightshoulder", RG_SRC_MENU, NULL, 0), RG_SET_OK);
    env e;
    env_init(&e, s);
    CHECK((field(&e, B(BACK) | B(START)) & SS) == SS);   /* no longer held back */
    for (int f = 0; f < 70; f++) field(&e, B(BACK) | B(START));
    CHECK_EQ(e.fires, 0);
    for (int f = 0; f < 3; f++) field(&e, 0);
    for (int f = 0; f < 70; f++) CHECK(!(field(&e, B(LB) | B(RB)) & (RG_BTN_L1 | RG_BTN_R1)));
    CHECK_EQ(e.fires, 1);
    /* hold time 2 s */
    rg_settings_set_float(s, "input.overlay_chord_hold", 2.0, RG_SRC_MENU);
    env_init(&e, s);
    for (int f = 0; f < 110; f++) field(&e, B(LB) | B(RB));
    CHECK_EQ(e.fires, 0);
    for (int f = 0; f < 10; f++) field(&e, B(LB) | B(RB));
    CHECK_EQ(e.fires, 1);
    /* a one-button chord on a button the game has no use for (Steam Deck R4):
     * hold opens; a tap is a tap */
    rg_settings_set_float(s, "input.overlay_chord_hold", 1.0, RG_SRC_MENU);
    CHECK_EQ(rg_settings_set_text(s, i, "pad:paddle1", RG_SRC_MENU, NULL, 0), RG_SET_OK);
    env_init(&e, s);
    for (int f = 0; f < 62; f++) field(&e, B(PADDLE));
    CHECK_EQ(e.fires, 1);
    /* a one-button chord on a game button: let go early = the tap reaches the game */
    CHECK_EQ(rg_settings_set_text(s, i, "pad:start", RG_SRC_MENU, NULL, 0), RG_SET_OK);
    env_init(&e, s);
    for (int f = 0; f < 20; f++) CHECK(!(field(&e, B(START)) & RG_BTN_START));
    int seen = 0;
    for (int f = 0; f < 6; f++) seen += !!(field(&e, 0) & RG_BTN_START);
    CHECK_EQ(seen, 2);
    CHECK_EQ(e.fires, 0);
    /* the menu: the chord row is a binding editor without the menu-control guard */
    CHECK_EQ(rg_settings_set_text(s, i, "pad:back, pad:start", RG_SRC_MENU, NULL, 0), RG_SET_OK);
    rg_menu m;
    rg_menu_init(&m, s);
    rg_menu_command(&m, RG_MENU_TOGGLE, 0);
    for (int p = 0; p < m.npages && strcmp(m.pages[m.page], "controls_ui"); p++) rg_menu_command(&m, RG_MENU_PAGE_NEXT, 0);
    CHECK_STR(m.pages[m.page], "controls_ui");
    int rows[RG_MENU_MAX_ROWS];
    int n = rg_menu_rows(&m, rows, RG_MENU_MAX_ROWS);
    int r = -1;
    for (int k = 0; k < n; k++) if (rows[k] == i) r = k;
    CHECK(r >= 0);
    for (int k = 0; k < r; k++) rg_menu_command(&m, RG_MENU_DOWN, 0);
    rg_menu_command(&m, RG_MENU_ACCEPT, 0);
    CHECK_EQ(m.view, RG_MENU_VIEW_BINDINGS);
    CHECK_EQ(m.edit, i);
    /* Add (row n + 0): a gamepad button is added */
    for (int k = 0; k < 2; k++) rg_menu_command(&m, RG_MENU_DOWN, 0);
    rg_menu_command(&m, RG_MENU_ACCEPT, 0);
    CHECK(rg_menu_capturing(&m));
    rg_menu_capture_input(&m, "pad:leftshoulder", 0);
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "pad:back, pad:start, pad:leftshoulder");
    /* a key is refused with the reason */
    m.sub = 3;
    rg_menu_command(&m, RG_MENU_ACCEPT, 0);
    CHECK(rg_menu_capturing(&m));
    rg_menu_capture_input(&m, "key:F2", 0);
    CHECK(strstr(m.status, "gamepad buttons only") != NULL);
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "pad:back, pad:start, pad:leftshoulder");
    /* remove every button: no guard (unlike the menu controls), the chord is off */
    for (int k = 0; k < 3; k++) {
        m.sub = 0;
        m.sub_col = 1;
        rg_menu_command(&m, RG_MENU_ACCEPT, 0);
    }
    CHECK_STR(rg_settings_get_string(s, "input.overlay_chord"), "");
    rg_menu_command(&m, RG_MENU_BACK, 0);
    rg_settings_destroy(s);
    return 0;
}

/* Hot-plug: a slot's chord state moves with the roster. */
static int t_chord_hotplug(void)
{
    rg_settings *s = mk();
    env e;
    env_init(&e, s);
    e.npads = 2;
    for (int f = 0; f < 3; f++) field2(&e, 0, B(BACK) | B(START));   /* pad 1 arming */
    CHECK(rg_chord_holding(&e.c, 1));
    CHECK(!rg_chord_holding(&e.c, 0));
    rg_chord_remove_slot(&e.c, 0);   /* pad 0 unplugged: pad 1 becomes slot 0 */
    e.npads = 1;
    CHECK(rg_chord_holding(&e.c, 0));
    for (int f = 0; f < 60; f++) CHECK(!(field(&e, B(BACK) | B(START)) & SS));
    CHECK_EQ(e.fires, 1);
    rg_settings_destroy(s);
    return 0;
}

static void prompts(rg_menu *m, const rg_actions *a, const rg_chord *c, rg_prompt_style st, int type)
{
    rg_menu_prompts_from_input(m, a, c, st, type);
}

static int t_overlay_prompts(void)
{
    rg_settings *s = mk();
    rg_actions a;
    rg_actions_from_settings(&a, s);
    rg_chord c;
    rg_chord_init(&c);
    rg_chord_from_settings(&c, s);
    rg_menu m;
    rg_menu_init(&m, s);
    /* unset: the generic words */
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "accept");
    char buf[256];
    rg_menu_expand(&m, "[accept] ok, [back] [nope] [r1] (X)", buf, sizeof buf);
    CHECK_STR(buf, "accept ok, back [nope] [r1] (X)");
    /* PlayStation (fixed style, any pad) */
    prompts(&m, &a, &c, RG_PROMPT_PLAYSTATION, -1);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "Cross");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_BACK), "Circle");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_PREV), "L1");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_NEXT), "R1");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_UP), "Up");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_START), "Start");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_SELECT), "Select");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "PS button or hold Select+Start 1 s");
    CHECK_STR(m.capture_hint, "Esc / PS button");
    /* DualSense: model names */
    prompts(&m, &a, &c, RG_PROMPT_PLAYSTATION, SDL_GAMEPAD_TYPE_PS5);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "PS button or hold Create+Options 1 s");
    prompts(&m, &a, &c, RG_PROMPT_PLAYSTATION, SDL_GAMEPAD_TYPE_PS4);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_SELECT), "Share");
    /* a fixed PlayStation style with an Xbox pad: PlayStation names, not the model's */
    prompts(&m, &a, &c, RG_PROMPT_PLAYSTATION, SDL_GAMEPAD_TYPE_XBOXONE);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_START), "Start");
    /* Xbox */
    prompts(&m, &a, &c, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_XBOXONE);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "A");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_BACK), "B");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_PREV), "LB");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "Xbox button or hold View+Menu 1 s");
    CHECK_STR(m.capture_hint, "Esc / Xbox button");
    prompts(&m, &a, &c, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_XBOX360);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "Xbox button or hold Back+Start 1 s");
    prompts(&m, &a, &c, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_STEAM);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "Steam button or hold View+Menu 1 s");
    {
        char t[32];
        rg_prompt_pad_button_label(PADDLE, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_STEAM, t, sizeof t);
        CHECK_STR(t, "R4");
        rg_prompt_pad_button_label(PADDLE, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_XBOXONE, t, sizeof t);
        CHECK_STR(t, "P1");
    }
    /* Nintendo: positional, so south (accept) is B */
    prompts(&m, &a, &c, RG_PROMPT_NINTENDO, SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_PRO);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "B");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_BACK), "A");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_PREV), "L");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "Home or hold Minus+Plus 1 s");
    /* keyboard: the key bindings, F1, no chord */
    prompts(&m, &a, &c, RG_PROMPT_KEYBOARD, -1);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "Enter");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_BACK), "Esc");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_PREV), "PgUp");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_NEXT), "PgDn");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "F1");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_START), "Enter");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_SELECT), "Backspace");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_LS), "W/A/S/D");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_DPAD), "Up/Left/Down/Right");
    /* rebinding shows at once: ui_accept -> key:K first, the overlay on pad:misc1 */
    rg_settings_set_text(s, rg_settings_find(s, "input.bind.ui_accept"), "key:K, key:Return, pad:x", RG_SRC_MENU, NULL, 0);
    rg_settings_set_text(s, rg_settings_find(s, "input.bind.ui_overlay"), "key:F2, pad:misc1, pad:guide", RG_SRC_MENU, NULL, 0);
    rg_settings_set_text(s, rg_settings_find(s, "input.overlay_chord"), "pad:leftshoulder, pad:rightshoulder", RG_SRC_MENU, NULL, 0);
    rg_settings_set_float(s, "input.overlay_chord_hold", 1.5, RG_SRC_MENU);
    rg_actions_from_settings(&a, s);
    rg_chord_from_settings(&c, s);
    prompts(&m, &a, &c, RG_PROMPT_KEYBOARD, -1);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "K");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "F2");
    prompts(&m, &a, &c, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_XBOXONE);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_ACCEPT), "X");
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "Share or hold LB+RB 1.5 s");
    /* chord off: the overlay binding alone */
    rg_settings_set_text(s, rg_settings_find(s, "input.overlay_chord"), "", RG_SRC_MENU, NULL, 0);
    rg_chord_from_settings(&c, s);
    prompts(&m, &a, &c, RG_PROMPT_XBOX, SDL_GAMEPAD_TYPE_XBOXONE);
    CHECK_STR(rg_menu_prompt_text(&m, RG_MP_TOGGLE), "Share");
    /* the rendered hint lines use them */
    rg_menu_command(&m, RG_MENU_TOGGLE, 0);
    rg_menu_line l[RG_MENU_MAX_ROWS + 16];
    int n = rg_menu_render(&m, 0, l, RG_MENU_MAX_ROWS + 16);
    CHECK(n >= 2);
    CHECK(strstr(l[1].text, "X edits") != NULL);
    CHECK(strstr(l[1].text, "B closes") != NULL);
    CHECK(strstr(l[1].text, "LB / RB pages") != NULL);
    CHECK(strstr(l[1].text, "open / close: Share") != NULL);
    CHECK(strchr(l[1].text, '[') == NULL);
    /* a label with % is not a format directive */
    rg_menu_set_prompt(&m, RG_MP_ACCEPT, "Keypad %");
    n = rg_menu_render(&m, 0, l, RG_MENU_MAX_ROWS + 16);
    CHECK(strstr(l[1].text, "Keypad % edits") != NULL);
    rg_settings_destroy(s);
    return 0;
}

/* The real host wiring (host_sdl.c), with an SDL virtual gamepad: a windowed
 * host, real time (SDL ticks), the overlay toggled by the chord, the game's
 * reads (rg_host_read_pad) never showing it.  Exit 77 (skipped) when no
 * window or virtual pad can be made. */
static int g_skip;

static void live_pump(rg_host *h, SDL_Joystick *j, uint32_t held, uint16_t *rep, int *open)
{
    for (int b = 0; b < SDL_GAMEPAD_BUTTON_COUNT; b++)
        SDL_SetJoystickVirtualButton(j, b, (held >> b) & 1);
    SDL_Delay(16);
    rg_host_pump(h);
    rg_pad p;
    rg_host_read_pad(h, 0, 0, &p);
    *rep = p.buttons;
    *open = rg_host_overlay_open(h);
}

static int chord_host(int off)
{
    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    rg_host_config hc;
    rg_host_config_default(&hc);
    hc.title = "rg-chord-tests (closes by itself)";
    hc.win_w = 320;
    hc.win_h = 240;
    hc.audio = 0;
    rg_host *h = rg_host_create(&hc);
    if (!h) { fprintf(stderr, "no window: %s (skipped)\n", rg_host_last_error()); g_skip = 1; return 0; }
    rg_settings *s = mk();
    if (off) rg_settings_set_text(s, rg_settings_find(s, "input.overlay_chord"), "", RG_SRC_API, NULL, 0);
    rg_host_attach_settings(h, s, NULL);
    SDL_VirtualJoystickDesc d;
    SDL_INIT_INTERFACE(&d);
    d.type = SDL_JOYSTICK_TYPE_GAMEPAD;
    d.naxes = SDL_GAMEPAD_AXIS_COUNT;
    d.nbuttons = SDL_GAMEPAD_BUTTON_COUNT;
    d.name = "rg-chord-tests virtual pad";
    SDL_JoystickID id = SDL_AttachVirtualJoystick(&d);
    SDL_Joystick *j = id ? SDL_OpenJoystick(id) : NULL;
    if (!j) { fprintf(stderr, "no virtual joystick: %s (skipped)\n", SDL_GetError()); g_skip = 1; goto out; }
    int before = rg_host_gamepad_count(h);
    uint16_t r;
    int open = 0;
    for (int i = 0; i < 120 && rg_host_gamepad_count(h) == before; i++) live_pump(h, j, 0, &r, &open);
    CHECK(rg_host_gamepad_count(h) > before);
    if (rg_host_gamepad_count(h) == before) goto out;
    /* other pads on the machine feed port 0 too: only start when the port is idle */
    for (int i = 0; i < 10; i++) live_pump(h, j, 0, &r, &open);
    CHECK(!(r & SS));
    CHECK(!open);
    /* hold the chord 1.4 s: the overlay opens once, the report never shows Select / Start */
    uint64_t t0 = SDL_GetTicks(), opened_at = 0;
    int leaks = 0;
    while (SDL_GetTicks() - t0 < 1400) {
        live_pump(h, j, B(BACK) | B(START), &r, &open);
        if (r & SS) leaks++;
        if (open && !opened_at) opened_at = SDL_GetTicks() - t0;
    }
    CHECK_EQ(leaks, 0);
    CHECK(open);
    CHECK(opened_at >= 950 && opened_at < 1400);
    for (int i = 0; i < 10; i++) { live_pump(h, j, 0, &r, &open); if (r & SS) leaks++; }
    CHECK(open);
    /* again: closes; nothing reaches the game after the release either */
    t0 = SDL_GetTicks();
    while (SDL_GetTicks() - t0 < 1300) { live_pump(h, j, B(BACK) | B(START), &r, &open); if (r & SS) leaks++; }
    CHECK(!open);
    for (int i = 0; i < 15; i++) { live_pump(h, j, 0, &r, &open); if (r & SS) leaks++; }
    CHECK_EQ(leaks, 0);
    /* uneven: Select, Start 3 pumps later, let go at 0.5 s: no toggle, no leak */
    for (int i = 0; i < 3; i++) { live_pump(h, j, B(BACK), &r, &open); if (r & SS) leaks++; }
    t0 = SDL_GetTicks();
    while (SDL_GetTicks() - t0 < 500) { live_pump(h, j, B(BACK) | B(START), &r, &open); if (r & SS) leaks++; }
    for (int i = 0; i < 15; i++) { live_pump(h, j, 0, &r, &open); if (r & SS) leaks++; }
    CHECK_EQ(leaks, 0);
    CHECK(!open);
    /* a lone Start tap reaches the game; a lone hold reaches it after the grace */
    live_pump(h, j, B(START), &r, &open);
    int seen = 0;
    for (int i = 0; i < 10; i++) { live_pump(h, j, 0, &r, &open); seen += !!(r & RG_BTN_START); }
    CHECK(seen >= 2);
    t0 = SDL_GetTicks();
    uint64_t first = 0;
    while (SDL_GetTicks() - t0 < 400) {
        live_pump(h, j, B(START), &r, &open);
        if ((r & RG_BTN_START) && !first) first = SDL_GetTicks() - t0;
    }
    CHECK(first >= RG_CHORD_GRACE_MS - 20 && first < RG_CHORD_GRACE_MS + 120);
    CHECK(!open);
    for (int i = 0; i < 5; i++) live_pump(h, j, 0, &r, &open);
out:
    if (j) SDL_CloseJoystick(j);
    if (id) SDL_DetachVirtualJoystick(id);
    rg_host_attach_settings(h, NULL, NULL);
    rg_host_destroy(h);
    rg_settings_destroy(s);
    return 0;
}

static int t_chord_host(void) { return chord_host(0); }
/* Control (WILL_FAIL): the same with the chord off must see Select / Start and no overlay. */
static int t_chord_host_control(void) { return chord_host(1); }

/* Control (WILL_FAIL): without the filter, the chord DOES reach the report. */
static int t_chord_control(void)
{
    rg_settings *s = mk();
    env e;
    env_init(&e, s);
    rg_gamepad_snap p;
    memset(&p, 0, sizeof p);
    p.button[BACK] = p.button[START] = 1;
    rg_chord_update(&e.c, 0, &p, 0);   /* updated, but not filtered */
    rg_input_snapshot in;
    memset(&in, 0, sizeof in);
    in.pads = &p;
    in.npads = 1;
    rg_pad out;
    rg_actions_eval(&e.a, &in, &out);
    CHECK(!(out.buttons & SS));
    rg_settings_destroy(s);
    return 0;
}

int main(int argc, char **argv)
{
    static const struct { const char *name; int (*fn)(void); } k[] = {
        { "chord_settings", t_chord_settings }, { "chord_no_leak", t_chord_no_leak },
        { "chord_lone_press", t_chord_lone_press }, { "chord_rebind", t_chord_rebind },
        { "chord_hotplug", t_chord_hotplug }, { "overlay_prompts", t_overlay_prompts },
        { "chord_control", t_chord_control }, { "chord_host", t_chord_host },
        { "chord_host_control", t_chord_host_control },
    };
    if (argc < 2) { fprintf(stderr, "usage: rg-chord-tests <name>\n"); return 2; }
    for (size_t i = 0; i < sizeof k / sizeof k[0]; i++)
        if (!strcmp(argv[1], k[i].name)) {
            k[i].fn();
            if (g_fail) fprintf(stderr, "%s: %d check(s) failed\n", argv[1], g_fail);
            return g_fail ? 1 : g_skip ? 77 : 0;
        }
    fprintf(stderr, "unknown test %s\n", argv[1]);
    return 2;
}
