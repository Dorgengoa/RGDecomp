/* SPDX-License-Identifier: CC0-1.0 */
/* Input-action layer: actions, bindings and their text, the default layout,
 * settings registration, evaluation, the DS2 adapter, the gamepad roster,
 * the press latch and UI navigation.  docs/INPUT.md.  Pure: no SDL_Init
 * (only SDL's key / gamepad name tables). */
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>

#include "host_internal.h"
#include "rg_input.h"
#include "rg_menu.h"

/* ------------------------------------------------------------ action table */
typedef struct action_info {
    const char *id, *label;
    int target;        /* rg_pad input, -1 = UI */
} action_info;

#define BIT(name) (__builtin_ctz(RG_BTN_##name))

static const action_info k_act[RG_ACT_COUNT] = {
    { "move_left", "Move left", RG_IN_LX_NEG },
    { "move_right", "Move right", RG_IN_LX_POS },
    { "move_up", "Move forward", RG_IN_LY_NEG },
    { "move_down", "Move back", RG_IN_LY_POS },
    { "camera_left", "Camera left", RG_IN_RX_NEG },
    { "camera_right", "Camera right", RG_IN_RX_POS },
    { "camera_up", "Camera up", RG_IN_RY_NEG },
    { "camera_down", "Camera down", RG_IN_RY_POS },
    { "dpad_up", "D-pad up", BIT(UP) },
    { "dpad_down", "D-pad down", BIT(DOWN) },
    { "dpad_left", "D-pad left", BIT(LEFT) },
    { "dpad_right", "D-pad right", BIT(RIGHT) },
    /* labels: docs/CONTROLS-AUDIT.md 4b; "?" = role inferred, not yet confirmed in a run.
     * Cross / Square / Circle confirmed on retail (battle tutorial: X sword, SQUARE gun,
     * CIRCLE jump); the ids keep their old names so config files stay valid. */
    { "confirm", "Confirm / Talk / Sword attack (Cross)", BIT(CROSS) },
    { "cancel", "Cancel / Jump (Circle)", BIT(CIRCLE) },
    { "attack", "Gun / Sub-weapon (Square)", BIT(SQUARE) },
    { "menu", "Menu / Battle commands (Triangle)", BIT(TRIANGLE) },
    { "camera_turn_left", "Camera left / Previous tab / Accept suggestion (L1)", BIT(L1) },
    { "camera_turn_right", "Camera right / Guard? / Next tab (R1)", BIT(R1) },
    { "decline", "Decline suggestion / Page (L2)", BIT(L2) },
    { "camera_recentre", "Recentre camera / Zoom (hold) (R2)", BIT(R2) },
    { "switch_leader", "Switch leader (L3)", BIT(L3) },
    { "first_person", "First-person look (R3)", BIT(R3) },
    { "pause", "Pause / Skip (Start)", BIT(START) },
    { "map", "Map / Camera type (Select)", BIT(SELECT) },
    { "walk", "Walk (hold: move at walking speed)", -1 },
    { "ui_up", "Menu: up", -1 },
    { "ui_down", "Menu: down", -1 },
    { "ui_left", "Menu: decrease", -1 },
    { "ui_right", "Menu: increase", -1 },
    { "ui_accept", "Menu: accept", -1 },
    { "ui_back", "Menu: back", -1 },
    { "ui_page_prev", "Menu: previous page", -1 },
    { "ui_page_next", "Menu: next page", -1 },
    { "ui_overlay", "Open / close settings", -1 },
};

const char *rg_action_id(int a) { return a >= 0 && a < RG_ACT_COUNT ? k_act[a].id : NULL; }
const char *rg_action_label(int a) { return a >= 0 && a < RG_ACT_COUNT ? k_act[a].label : NULL; }
int rg_action_target(int a) { return a >= 0 && a < RG_ACT_COUNT ? k_act[a].target : -1; }
bool rg_action_is_axis(int a) { return a >= 0 && a < RG_ACT_GAME_COUNT && k_act[a].target >= 16; }

/* Pre-audit ids (docs/INPUT.md "Actions"): still accepted on input. */
static const struct { const char *id; int act; } k_alias[] = {
    { "shoulder_left", RG_ACT_CAMERA_TURN_LEFT },
    { "shoulder_right", RG_ACT_CAMERA_TURN_RIGHT },
    { "trigger_left", RG_ACT_DECLINE },
    { "trigger_right", RG_ACT_CAMERA_RECENTRE },
    { "stick_left_click", RG_ACT_SWITCH_LEADER },
    { "stick_right_click", RG_ACT_FIRST_PERSON },
    { "start", RG_ACT_PAUSE },
    { "select", RG_ACT_MAP },
};
#define N_ALIAS ((int)(sizeof k_alias / sizeof k_alias[0]))

const char *rg_action_alias(int i, int *action)
{
    if (i < 0 || i >= N_ALIAS) return NULL;
    if (action) *action = k_alias[i].act;
    return k_alias[i].id;
}

int rg_action_from_id(const char *id)
{
    if (!id) return -1;
    for (int a = 0; a < RG_ACT_COUNT; a++)
        if (SDL_strcasecmp(id, k_act[a].id) == 0) return a;
    for (int i = 0; i < N_ALIAS; i++)
        if (SDL_strcasecmp(id, k_alias[i].id) == 0) return k_alias[i].act;
    return -1;
}

/* ------------------------------------------------------------ binding text */
static const char *const k_mouse_names[] = { NULL, "left", "middle", "right", "x1", "x2" };

static char *trim(char *s)
{
    while (*s && isspace((unsigned char)*s)) s++;
    char *e = s + strlen(s);
    while (e > s && isspace((unsigned char)e[-1])) *--e = 0;
    return s;
}

static int parse_one(char *b, rg_binding *out, char *err, size_t errcap)
{
    char *colon = strchr(b, ':');
    if (!colon) { rgh_err(err, errcap, "binding '%s' needs key:/mouse:/pad:/axis:", b); return -1; }
    *colon = 0;
    char *kind = trim(b), *val = trim(colon + 1);
    memset(out, 0, sizeof *out);
    if (!SDL_strcasecmp(kind, "key")) {
        SDL_Scancode sc = !SDL_strcasecmp(val, "comma") ? SDL_SCANCODE_COMMA : SDL_GetScancodeFromName(val);
        if (sc == SDL_SCANCODE_UNKNOWN || sc >= RG_LATCH_KEYS) { rgh_err(err, errcap, "unknown key '%s'", val); return -1; }
        out->kind = RG_BIND_KEY;
        out->code = (uint16_t)sc;
        return 0;
    }
    if (!SDL_strcasecmp(kind, "mouse")) {
        for (int i = 1; i <= 5; i++)
            if (!SDL_strcasecmp(val, k_mouse_names[i])) { out->kind = RG_BIND_MOUSE; out->code = (uint16_t)i; return 0; }
        size_t L = strlen(val);
        if (L == 2 && (val[1] == '+' || val[1] == '-') &&
            (tolower((unsigned char)val[0]) == 'x' || tolower((unsigned char)val[0]) == 'y')) {
            out->kind = RG_BIND_MOUSE_MOTION;
            out->code = tolower((unsigned char)val[0]) == 'y';
            out->pos = val[1] == '+';
            return 0;
        }
        rgh_err(err, errcap, "unknown mouse input '%s' (left|middle|right|x1|x2|x+|x-|y+|y-)", val);
        return -1;
    }
    if (!SDL_strcasecmp(kind, "pad")) {
        SDL_GamepadButton gb = SDL_GetGamepadButtonFromString(val);
        if (gb == SDL_GAMEPAD_BUTTON_INVALID || (int)gb >= RG_GP_BUTTONS) {
            rgh_err(err, errcap, "unknown gamepad button '%s'", val); return -1;
        }
        out->kind = RG_BIND_PAD_BUTTON;
        out->code = (uint16_t)gb;
        return 0;
    }
    if (!SDL_strcasecmp(kind, "axis")) {
        size_t L = strlen(val);
        int pos = L ? (val[L - 1] == '+' ? 1 : val[L - 1] == '-' ? 0 : -1) : -1;
        if (pos < 0) { rgh_err(err, errcap, "axis '%s' needs a + or - suffix", val); return -1; }
        val[L - 1] = 0;
        SDL_GamepadAxis ga = SDL_GetGamepadAxisFromString(trim(val));
        if (ga == SDL_GAMEPAD_AXIS_INVALID || (int)ga >= RG_GP_AXES) {
            rgh_err(err, errcap, "unknown gamepad axis '%s'", val); return -1;
        }
        out->kind = RG_BIND_PAD_AXIS;
        out->code = (uint16_t)ga;
        out->pos = (uint8_t)pos;
        return 0;
    }
    rgh_err(err, errcap, "unknown binding kind '%s'", kind);
    return -1;
}

int rg_binding_parse_list(const char *text, rg_binding out[RG_BIND_MAX], char *err, size_t errcap)
{
    size_t n = strlen(text ? text : "");
    char *buf = (char *)malloc(n + 1);
    if (!buf) { rgh_err(err, errcap, "out of memory"); return -1; }
    memcpy(buf, text ? text : "", n + 1);
    int cnt = 0, rc = 0;
    for (char *p = buf; p && !rc; ) {
        char *comma = strchr(p, ',');
        if (comma) *comma = 0;
        char *b = trim(p);
        p = comma ? comma + 1 : NULL;
        if (!*b) continue;
        rg_binding one;
        if (parse_one(b, &one, err, errcap)) { rc = -1; break; }
        int dup = 0;
        for (int i = 0; i < cnt; i++)
            if (!memcmp(&out[i], &one, sizeof one)) dup = 1;
        if (dup) continue;
        if (cnt >= RG_BIND_MAX) { rgh_err(err, errcap, "more than %d bindings", RG_BIND_MAX); rc = -1; break; }
        out[cnt++] = one;
    }
    free(buf);
    return rc ? -1 : cnt;
}

size_t rg_binding_format(const rg_binding *b, char *out, size_t cap)
{
    char tmp[96] = "";
    switch (b->kind) {
    case RG_BIND_KEY:
        if (b->code == SDL_SCANCODE_COMMA) snprintf(tmp, sizeof tmp, "key:comma");
        else snprintf(tmp, sizeof tmp, "key:%s", SDL_GetScancodeName((SDL_Scancode)b->code));
        break;
    case RG_BIND_MOUSE:
        snprintf(tmp, sizeof tmp, "mouse:%s", b->code >= 1 && b->code <= 5 ? k_mouse_names[b->code] : "?");
        break;
    case RG_BIND_MOUSE_MOTION:
        snprintf(tmp, sizeof tmp, "mouse:%c%c", b->code ? 'y' : 'x', b->pos ? '+' : '-');
        break;
    case RG_BIND_PAD_BUTTON:
        snprintf(tmp, sizeof tmp, "pad:%s", SDL_GetGamepadStringForButton((SDL_GamepadButton)b->code));
        break;
    case RG_BIND_PAD_AXIS:
        snprintf(tmp, sizeof tmp, "axis:%s%c", SDL_GetGamepadStringForAxis((SDL_GamepadAxis)b->code),
                 b->pos ? '+' : '-');
        break;
    default:
        break;
    }
    size_t n = strlen(tmp);
    if (cap) { size_t c = n < cap - 1 ? n : cap - 1; memcpy(out, tmp, c); out[c] = 0; }
    return n;
}

size_t rg_binding_format_list(const rg_binding *b, int n, char *out, size_t cap)
{
    size_t len = 0;
    if (cap) out[0] = 0;
    for (int i = 0; i < n; i++) {
        char one[96];
        rg_binding_format(&b[i], one, sizeof one);
        const char *sep = i ? ", " : "";
        size_t need = strlen(sep) + strlen(one);
        if (cap && len + need < cap) { strcat(out, sep); strcat(out, one); }
        len += need;
    }
    return len;
}

int rg_binding_validate(const char *text, char *norm, size_t normcap, char *err, size_t errcap, void *user)
{
    (void)user;
    rg_binding b[RG_BIND_MAX];
    int n = rg_binding_parse_list(text, b, err, errcap);
    if (n < 0) return -1;
    if (rg_binding_format_list(b, n, norm, normcap) >= normcap) { rgh_err(err, errcap, "too long"); return -1; }
    return 0;
}

/* ------------------------------------------------------------ default layout */
static void add(rg_actions *a, int act, int kind, int code, int pos)
{
    if (a->nbind[act] >= RG_BIND_MAX) return;
    rg_binding *b = &a->bind[act][a->nbind[act]++];
    b->kind = (uint8_t)kind;
    b->code = (uint16_t)code;
    b->pos = (uint8_t)pos;
}
#define K(act, sc) add(a, act, RG_BIND_KEY, sc, 0)
#define P(act, btn) add(a, act, RG_BIND_PAD_BUTTON, btn, 0)
#define AX(act, axis, pos) add(a, act, RG_BIND_PAD_AXIS, axis, pos)

int rg_actions_raw(double f)
{
    if (f <= 0) return 0;
    if (f >= 1) return 32767;
    return (int)(f * 32767.0 + 0.5);
}

static void tuning_default(rg_actions *a)
{
    a->deadzone[0] = a->deadzone[1] = rg_actions_raw(0.25);
    a->threshold = rg_actions_raw(0.35);
    a->sensitivity[0] = a->sensitivity[1] = 1.0f;
    memset(a->invert, 0, sizeof a->invert);
    a->mouse_sensitivity = 1.0f;
    a->vibration = 1.0f;
    a->stick_compensation = false;
    a->players = RG_PLAYERS_ONE;
    a->min_press_fields = 2;
    /* docs/BRINGUP.md "User play-test, 2026-10-18": a round gamepad stick at full
     * tilt on a diagonal read ~0.52 after the game's decode (walk, not run), and
     * the orbit camera turns the PS2 way round; both default to the PC behaviour */
    a->stick_square = true;
    a->camera_pc = true;
    a->camera_view = RG_CAMVIEW_NONE;
}

void rg_actions_default(rg_actions *a)
{
    memset(a, 0, sizeof *a);
    tuning_default(a);
    /* keyboard */
    K(RG_ACT_MOVE_LEFT, SDL_SCANCODE_A);
    K(RG_ACT_MOVE_RIGHT, SDL_SCANCODE_D);
    K(RG_ACT_MOVE_UP, SDL_SCANCODE_W);
    K(RG_ACT_MOVE_DOWN, SDL_SCANCODE_S);
    K(RG_ACT_CAMERA_LEFT, SDL_SCANCODE_J);
    K(RG_ACT_CAMERA_RIGHT, SDL_SCANCODE_L);
    K(RG_ACT_CAMERA_UP, SDL_SCANCODE_I);
    K(RG_ACT_CAMERA_DOWN, SDL_SCANCODE_K);
    K(RG_ACT_DPAD_UP, SDL_SCANCODE_UP);
    K(RG_ACT_DPAD_DOWN, SDL_SCANCODE_DOWN);
    K(RG_ACT_DPAD_LEFT, SDL_SCANCODE_LEFT);
    K(RG_ACT_DPAD_RIGHT, SDL_SCANCODE_RIGHT);
    K(RG_ACT_CONFIRM, SDL_SCANCODE_SPACE);
    K(RG_ACT_CONFIRM, SDL_SCANCODE_X);
    K(RG_ACT_CANCEL, SDL_SCANCODE_C);
    K(RG_ACT_ATTACK, SDL_SCANCODE_Z);
    K(RG_ACT_MENU, SDL_SCANCODE_TAB);
    K(RG_ACT_SHOULDER_LEFT, SDL_SCANCODE_Q);
    K(RG_ACT_SHOULDER_RIGHT, SDL_SCANCODE_E);
    K(RG_ACT_TRIGGER_LEFT, SDL_SCANCODE_1);
    K(RG_ACT_TRIGGER_RIGHT, SDL_SCANCODE_3);
    K(RG_ACT_STICK_LEFT_CLICK, SDL_SCANCODE_V);
    K(RG_ACT_STICK_RIGHT_CLICK, SDL_SCANCODE_B);
    K(RG_ACT_START, SDL_SCANCODE_RETURN);
    K(RG_ACT_SELECT, SDL_SCANCODE_BACKSPACE);
    K(RG_ACT_WALK, SDL_SCANCODE_LSHIFT);
    K(RG_ACT_UI_UP, SDL_SCANCODE_UP);
    K(RG_ACT_UI_UP, SDL_SCANCODE_W);
    K(RG_ACT_UI_DOWN, SDL_SCANCODE_DOWN);
    K(RG_ACT_UI_DOWN, SDL_SCANCODE_S);
    K(RG_ACT_UI_LEFT, SDL_SCANCODE_LEFT);
    K(RG_ACT_UI_LEFT, SDL_SCANCODE_A);
    K(RG_ACT_UI_RIGHT, SDL_SCANCODE_RIGHT);
    K(RG_ACT_UI_RIGHT, SDL_SCANCODE_D);
    K(RG_ACT_UI_ACCEPT, SDL_SCANCODE_RETURN);
    K(RG_ACT_UI_ACCEPT, SDL_SCANCODE_SPACE);
    K(RG_ACT_UI_BACK, SDL_SCANCODE_ESCAPE);
    K(RG_ACT_UI_BACK, SDL_SCANCODE_BACKSPACE);
    K(RG_ACT_UI_PAGE_PREV, SDL_SCANCODE_PAGEUP);
    K(RG_ACT_UI_PAGE_PREV, SDL_SCANCODE_Q);
    K(RG_ACT_UI_PAGE_NEXT, SDL_SCANCODE_PAGEDOWN);
    K(RG_ACT_UI_PAGE_NEXT, SDL_SCANCODE_E);
    K(RG_ACT_UI_OVERLAY, SDL_SCANCODE_F1);
    /* gamepad (SDL positional layout: SOUTH = DS2 cross, whatever the label) */
    AX(RG_ACT_MOVE_LEFT, SDL_GAMEPAD_AXIS_LEFTX, 0);
    AX(RG_ACT_MOVE_RIGHT, SDL_GAMEPAD_AXIS_LEFTX, 1);
    AX(RG_ACT_MOVE_UP, SDL_GAMEPAD_AXIS_LEFTY, 0);
    AX(RG_ACT_MOVE_DOWN, SDL_GAMEPAD_AXIS_LEFTY, 1);
    AX(RG_ACT_CAMERA_LEFT, SDL_GAMEPAD_AXIS_RIGHTX, 0);
    AX(RG_ACT_CAMERA_RIGHT, SDL_GAMEPAD_AXIS_RIGHTX, 1);
    AX(RG_ACT_CAMERA_UP, SDL_GAMEPAD_AXIS_RIGHTY, 0);
    AX(RG_ACT_CAMERA_DOWN, SDL_GAMEPAD_AXIS_RIGHTY, 1);
    P(RG_ACT_DPAD_UP, SDL_GAMEPAD_BUTTON_DPAD_UP);
    P(RG_ACT_DPAD_DOWN, SDL_GAMEPAD_BUTTON_DPAD_DOWN);
    P(RG_ACT_DPAD_LEFT, SDL_GAMEPAD_BUTTON_DPAD_LEFT);
    P(RG_ACT_DPAD_RIGHT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    P(RG_ACT_CONFIRM, SDL_GAMEPAD_BUTTON_SOUTH);
    P(RG_ACT_CANCEL, SDL_GAMEPAD_BUTTON_EAST);
    P(RG_ACT_ATTACK, SDL_GAMEPAD_BUTTON_WEST);
    P(RG_ACT_MENU, SDL_GAMEPAD_BUTTON_NORTH);
    P(RG_ACT_SHOULDER_LEFT, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
    P(RG_ACT_SHOULDER_RIGHT, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);
    AX(RG_ACT_TRIGGER_LEFT, SDL_GAMEPAD_AXIS_LEFT_TRIGGER, 1);
    AX(RG_ACT_TRIGGER_RIGHT, SDL_GAMEPAD_AXIS_RIGHT_TRIGGER, 1);
    P(RG_ACT_STICK_LEFT_CLICK, SDL_GAMEPAD_BUTTON_LEFT_STICK);
    P(RG_ACT_STICK_RIGHT_CLICK, SDL_GAMEPAD_BUTTON_RIGHT_STICK);
    P(RG_ACT_START, SDL_GAMEPAD_BUTTON_START);
    P(RG_ACT_SELECT, SDL_GAMEPAD_BUTTON_BACK);
    P(RG_ACT_UI_UP, SDL_GAMEPAD_BUTTON_DPAD_UP);
    AX(RG_ACT_UI_UP, SDL_GAMEPAD_AXIS_LEFTY, 0);
    P(RG_ACT_UI_DOWN, SDL_GAMEPAD_BUTTON_DPAD_DOWN);
    AX(RG_ACT_UI_DOWN, SDL_GAMEPAD_AXIS_LEFTY, 1);
    P(RG_ACT_UI_LEFT, SDL_GAMEPAD_BUTTON_DPAD_LEFT);
    AX(RG_ACT_UI_LEFT, SDL_GAMEPAD_AXIS_LEFTX, 0);
    P(RG_ACT_UI_RIGHT, SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    AX(RG_ACT_UI_RIGHT, SDL_GAMEPAD_AXIS_LEFTX, 1);
    P(RG_ACT_UI_ACCEPT, SDL_GAMEPAD_BUTTON_SOUTH);
    P(RG_ACT_UI_BACK, SDL_GAMEPAD_BUTTON_EAST);
    P(RG_ACT_UI_PAGE_PREV, SDL_GAMEPAD_BUTTON_LEFT_SHOULDER);
    P(RG_ACT_UI_PAGE_NEXT, SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER);
    P(RG_ACT_UI_OVERLAY, SDL_GAMEPAD_BUTTON_GUIDE);
    P(RG_ACT_UI_OVERLAY, SDL_GAMEPAD_BUTTON_TOUCHPAD);
}

void rg_actions_from_input_map(rg_actions *a, const rg_input_map *m)
{
    memset(a, 0, sizeof *a);
    tuning_default(a);
    a->stick_square = false;   /* the legacy rg_input_eval: per-axis, PS2 camera */
    a->camera_pc = false;
    a->deadzone[0] = a->deadzone[1] = m->deadzone;
    a->threshold = m->threshold;
    for (int act = 0; act < RG_ACT_GAME_COUNT; act++) {
        int in = k_act[act].target;
        if (in < 0) continue;   /* the walk modifier: no map input */
        for (int s = 0; s < RG_MAP_SLOTS; s++)
            if (m->key[in][s]) K(act, m->key[in][s]);
        for (int s = 0; s < RG_MAP_SLOTS; s++)
            if (m->pad_button[in][s] >= 0) P(act, m->pad_button[in][s]);
        for (int s = 0; s < RG_MAP_SLOTS; s++)
            if (m->pad_axis[in][s] >= 0) AX(act, m->pad_axis[in][s] >> 1, m->pad_axis[in][s] & 1);
    }
}
#undef K
#undef P
#undef AX

/* ------------------------------------------------------------ settings */
static const char *const k_players[] = { "one", "two" };
static const char *const k_players_l[] = { "One (every gamepad is player 1)", "Two (2nd gamepad is player 2)" };
static const char *const k_prompts[] = { "auto", "playstation", "xbox", "nintendo", "keyboard" };
static const char *const k_prompts_l[] = { "Auto (device in use)", "PlayStation", "Xbox", "Nintendo", "Keyboard" };
static const char *const k_camconv[] = { "pc", "original" };
static const char *const k_camconv_l[] = { "PC (right turns the view right, up looks up)", "Original (PS2)" };

/* Binding defaults are generated once from rg_actions_default and live as
 * long as the process (the registry keeps pointers to them). */
static char g_bind_ids[RG_ACT_COUNT][48];
static char g_bind_defaults[RG_ACT_COUNT][RG_BIND_MAX * 40];

int rg_actions_register_settings(rg_settings *s)
{
    rg_actions d;
    rg_actions_default(&d);
    rg_setting_def defs[RG_ACT_COUNT + 32];
    int n = 0;
    memset(defs, 0, sizeof defs);
    for (int a = 0; a < RG_ACT_COUNT; a++) {
        snprintf(g_bind_ids[a], sizeof g_bind_ids[a], "input.bind.%s", k_act[a].id);
        rg_binding_format_list(d.bind[a], d.nbind[a], g_bind_defaults[a], sizeof g_bind_defaults[a]);
        rg_setting_def *x = &defs[n++];
        x->id = g_bind_ids[a];
        x->type = RG_SET_BINDING;
        x->category = a < RG_ACT_GAME_COUNT ? "controls" : "controls_ui";
        x->label = k_act[a].label;
        x->def_s = g_bind_defaults[a];
        x->validate = rg_binding_validate;
        x->max_len = RG_BIND_MAX * 40;
    }
    static const rg_setting_def tune[] = {
        { .id = "input.deadzone_move", .type = RG_SET_FLOAT, .category = "controls", .label = "Move stick deadzone",
          .help = "fraction of full deflection", .def_f = 0.25, .min_f = 0.0, .max_f = 0.95, .step_f = 0.05 },
        { .id = "input.deadzone_camera", .type = RG_SET_FLOAT, .category = "controls", .label = "Camera stick deadzone",
          .def_f = 0.25, .min_f = 0.0, .max_f = 0.95, .step_f = 0.05 },
        { .id = "input.trigger_threshold", .type = RG_SET_FLOAT, .category = "controls",
          .label = "Analog-as-button threshold", .help = "triggers / axes bound to buttons",
          .def_f = 0.35, .min_f = 0.05, .max_f = 0.95, .step_f = 0.05 },
        { .id = "input.sensitivity_move", .type = RG_SET_FLOAT, .category = "controls", .label = "Move sensitivity",
          .def_f = 1.0, .min_f = 0.25, .max_f = 4.0, .step_f = 0.25 },
        { .id = "input.sensitivity_camera", .type = RG_SET_FLOAT, .category = "controls", .label = "Camera sensitivity",
          .def_f = 1.0, .min_f = 0.25, .max_f = 4.0, .step_f = 0.25 },
        { .id = "input.invert_move_x", .type = RG_SET_BOOL, .category = "controls", .label = "Invert move X" },
        { .id = "input.invert_move_y", .type = RG_SET_BOOL, .category = "controls", .label = "Invert move Y" },
        { .id = "input.invert_camera_x", .type = RG_SET_BOOL, .category = "controls", .label = "Invert camera X" },
        { .id = "input.invert_camera_y", .type = RG_SET_BOOL, .category = "controls", .label = "Invert camera Y" },
        { .id = "input.mouse_sensitivity", .type = RG_SET_FLOAT, .category = "controls", .label = "Mouse sensitivity",
          .help = "1.0: 20 px per field = full deflection", .def_f = 1.0, .min_f = 0.1, .max_f = 10.0, .step_f = 0.1 },
        /* Mouse camera (docs/INPUT.md "Mouse camera implementation"): mouse motion
         * turns the field / battle camera directly (not through the stick).  Live
         * input like any other, so not a gameplay option; Original = off. */
        { .id = "input.mouse_look", .type = RG_SET_BOOL, .category = "controls", .label = "Mouse camera",
          .help = "mouse motion turns the field and battle camera; the cursor is captured while the camera runs",
          .flags = RG_SETF_HAS_ORIGINAL, .def_i = 1, .orig_i = 0 },
        { .id = "input.mouse_yaw_scale", .type = RG_SET_FLOAT, .category = "controls",
          .label = "Mouse camera speed (horizontal)", .help = "1.0: 0.086 degrees per count",
          .def_f = 1.0, .min_f = 0.1, .max_f = 10.0, .step_f = 0.1 },
        { .id = "input.mouse_pitch_scale", .type = RG_SET_FLOAT, .category = "controls",
          .label = "Mouse camera speed (vertical)", .help = "1.0: 0.086 degrees per count",
          .def_f = 1.0, .min_f = 0.1, .max_f = 10.0, .step_f = 0.1 },
        { .id = "input.mouse_invert_x", .type = RG_SET_BOOL, .category = "controls", .label = "Mouse camera: invert X" },
        { .id = "input.mouse_invert_y", .type = RG_SET_BOOL, .category = "controls", .label = "Mouse camera: invert Y" },
        /* The US build never turns a motor on (docs/CONTROLS-AUDIT.md section 7): kept for
         * the rumble hook and a future optional rumble feature, hidden from the menu. */
        { .id = "input.vibration", .type = RG_SET_FLOAT, .category = "controls",
          .label = "Vibration strength (unused: the game never vibrates)",
          .help = "scales rumble the game requests; the US build requests none",
          .flags = RG_SETF_HIDDEN, .def_f = 1.0, .min_f = 0.0, .max_f = 1.0, .step_f = 0.1 },
        { .id = "input.stick_compensation", .type = RG_SET_BOOL, .category = "controls",
          .label = "Stick dead-zone compensation",
          .help = "skip the game's own ~39% stick dead zone; the stick deadzone settings then apply alone",
          .flags = RG_SETF_GAMEPLAY | RG_SETF_HAS_ORIGINAL, .def_i = 0, .orig_i = 0 },
        /* docs/INPUT.md "Stick range" and "Camera stick convention" */
        { .id = "input.stick_ds2_range", .type = RG_SET_BOOL, .category = "controls",
          .label = "Gamepad sticks: DualShock 2 range",
          .help = "round dead zone, and full tilt reads full in every direction like a PS2 stick "
                  "(off: each axis on its own; a round stick then walks on diagonals)",
          .def_i = 1 },
        { .id = "input.camera_convention", .type = RG_SET_ENUM, .category = "controls",
          .label = "Camera stick direction",
          .help = "PC: right turns the view right and up looks up (the PS2 camera swings the other way "
                  "round in the field and battle, and looks down on up); Original: as on the PS2. "
                  "The invert settings apply on top",
          .flags = RG_SETF_HAS_ORIGINAL, .def_i = 0, .orig_i = 1,
          .enum_names = k_camconv, .enum_labels = k_camconv_l, .enum_count = 2 },
        { .id = "input.players", .type = RG_SET_ENUM, .category = "controls", .label = "Players",
          .def_i = 0, .enum_names = k_players, .enum_labels = k_players_l, .enum_count = 2 },
        { .id = "input.min_press_fields", .type = RG_SET_INT, .category = "controls", .label = "Minimum press length",
          .help = "fields a short tap is held for (0 = off)", .def_i = 2, .min_i = 0, .max_i = 8, .step_i = 1 },
        /* docs/PROMPTS.md: rg-game swaps the gaiji2 button glyphs to the style
         * rg_host_prompt_style resolves (live; presentation only).  Original =
         * the PS2 prompts (the texture is never written). */
        { .id = "prompts.style", .type = RG_SET_ENUM, .category = "controls", .label = "Button prompts",
          .help = "auto follows the device in use; keyboard shows your key bindings; "
                  "scripted runs always show PlayStation prompts",
          .flags = RG_SETF_HAS_ORIGINAL, .def_i = RG_PROMPTS_AUTO,
          .orig_i = RG_PROMPTS_PLAYSTATION, .enum_names = k_prompts, .enum_labels = k_prompts_l, .enum_count = 5 },
        /* docs/INPUT.md "Opening the settings overlay with a gamepad": a held
         * chord for pads whose Guide button the system takes (Xbox Game Bar,
         * Steam) and pads without a touchpad.  Live input only (scripts and
         * headless runs never see it), so Original keeps it as well. */
        { .id = "input.overlay_chord", .type = RG_SET_BINDING, .category = "controls_ui",
          .label = "Open / close settings: hold together",
          .help = "gamepad buttons held together for the hold time open or close this menu (Guide may be "
                  "taken by Steam or the Xbox Game Bar). While they are held together the game never sees "
                  "them; a lone press of one reaches the game 0.1 s late. Empty = off",
          .flags = RG_SETF_HAS_ORIGINAL, .def_s = "pad:back, pad:start", .orig_s = "pad:back, pad:start",
          .validate = rg_chord_validate, .max_len = RG_BIND_MAX * 40 },
        { .id = "input.overlay_chord_hold", .type = RG_SET_FLOAT, .category = "controls_ui",
          .label = "Open / close settings: hold time", .help = "seconds the chord must be held",
          .flags = RG_SETF_HAS_ORIGINAL, .def_f = 1.0, .orig_f = 1.0, .min_f = 0.5, .max_f = 3.0, .step_f = 0.25 },
    };
    for (size_t i = 0; i < sizeof tune / sizeof tune[0]; i++) defs[n++] = tune[i];
    int rc = rg_settings_register(s, defs, n);
    /* pre-audit ids keep loading from files, presets and --set */
    static char alias_ids[N_ALIAS][48];
    for (int i = 0; i < N_ALIAS; i++) {
        snprintf(alias_ids[i], sizeof alias_ids[i], "input.bind.%s", k_alias[i].id);
        if (rg_settings_add_alias(s, alias_ids[i], g_bind_ids[k_alias[i].act]) != 0) rc = -1;
    }
    return rc;
}

void rg_actions_from_settings(rg_actions *a, const rg_settings *s)
{
    rg_actions_default(a);
    for (int act = 0; act < RG_ACT_COUNT; act++) {
        char id[64];
        snprintf(id, sizeof id, "input.bind.%s", k_act[act].id);
        if (rg_settings_find(s, id) < 0) continue;
        rg_binding b[RG_BIND_MAX];
        memset(b, 0, sizeof b);
        int n = rg_binding_parse_list(rg_settings_get_string(s, id), b, NULL, 0);
        if (n < 0) continue;   /* cannot happen: the validator refused it */
        memcpy(a->bind[act], b, sizeof b);
        a->nbind[act] = n;
    }
#define F(id) rg_settings_get_float(s, id)
    if (rg_settings_find(s, "input.deadzone_move") >= 0) {
        a->deadzone[0] = rg_actions_raw(F("input.deadzone_move"));
        a->deadzone[1] = rg_actions_raw(F("input.deadzone_camera"));
        a->threshold = rg_actions_raw(F("input.trigger_threshold"));
        a->sensitivity[0] = (float)F("input.sensitivity_move");
        a->sensitivity[1] = (float)F("input.sensitivity_camera");
        a->invert[RG_AXIS_MOVE_X] = rg_settings_get_bool(s, "input.invert_move_x");
        a->invert[RG_AXIS_MOVE_Y] = rg_settings_get_bool(s, "input.invert_move_y");
        a->invert[RG_AXIS_CAMERA_X] = rg_settings_get_bool(s, "input.invert_camera_x");
        a->invert[RG_AXIS_CAMERA_Y] = rg_settings_get_bool(s, "input.invert_camera_y");
        a->mouse_sensitivity = (float)F("input.mouse_sensitivity");
        a->vibration = (float)F("input.vibration");
        if (rg_settings_find(s, "input.stick_compensation") >= 0)
            a->stick_compensation = rg_settings_get_bool(s, "input.stick_compensation");
        if (rg_settings_find(s, "input.stick_ds2_range") >= 0)
            a->stick_square = rg_settings_get_bool(s, "input.stick_ds2_range");
        if (rg_settings_find(s, "input.camera_convention") >= 0)
            a->camera_pc = rg_settings_get_enum(s, "input.camera_convention") == 0;
        a->players = rg_settings_get_enum(s, "input.players");
        a->min_press_fields = rg_settings_get_int(s, "input.min_press_fields");
    }
#undef F
}

/* ------------------------------------------------------------ evaluation */
static int axis_dir(int16_t v, int pos)
{
    int x = pos ? v : -(int)v;
    return x < 0 ? 0 : x > 32767 ? 32767 : x;
}

static int deadzoned(int mag, int dz)
{
    if (mag <= dz || dz >= 32767) return 0;
    return (int)((int64_t)(mag - dz) * 32767 / (32767 - dz));
}

void rg_stick_shape(int x, int y, int dz, int *ox, int *oy)
{
    *ox = *oy = 0;
    if (x < -32767) x = -32767;
    if (y < -32767) y = -32767;
    double r = sqrt((double)x * x + (double)y * y);
    int outer = dz >= RG_STICK_OUTER ? 32767 : RG_STICK_OUTER;   /* a huge dead zone: no outer edge */
    if (r <= dz || dz >= outer || r <= 0) return;
    /* radial rescale between the dead zone and the outer edge (a DS2 stick reads
     * full before its gate; worn or round-gated pads rarely reach 32767) */
    int rr = r >= outer ? outer : (int)r;
    int mag = (int)((int64_t)(rr - dz) * 32767 / (outer - dz));
    if (x == 0 || y == 0) {   /* on an axis: exact integers */
        *ox = x > 0 ? mag : x < 0 ? -mag : 0;
        *oy = y > 0 ? mag : y < 0 ? -mag : 0;
        return;
    }
    /* circle -> square: divide by the cosine to the nearest axis */
    double ax = fabs((double)x), ay = fabs((double)y);
    double k = mag / (ax > ay ? ax : ay);
    double fx = x * k, fy = y * k;
    int vx = (int)lround(fx), vy = (int)lround(fy);
    *ox = vx > 32767 ? 32767 : vx < -32767 ? -32767 : vx;
    *oy = vy > 32767 ? 32767 : vy < -32767 ? -32767 : vy;
}

/* the other axis of a stick axis (LEFTX <-> LEFTY, RIGHTX <-> RIGHTY), or -1 */
static int stick_partner(int axis)
{
    switch (axis) {
    case SDL_GAMEPAD_AXIS_LEFTX: return SDL_GAMEPAD_AXIS_LEFTY;
    case SDL_GAMEPAD_AXIS_LEFTY: return SDL_GAMEPAD_AXIS_LEFTX;
    case SDL_GAMEPAD_AXIS_RIGHTX: return SDL_GAMEPAD_AXIS_RIGHTY;
    case SDL_GAMEPAD_AXIS_RIGHTY: return SDL_GAMEPAD_AXIS_RIGHTX;
    default: return -1;
    }
}

void rg_actions_values(const rg_actions *a, const rg_input_snapshot *in, int32_t out[RG_ACT_COUNT])
{
    for (int act = 0; act < RG_ACT_COUNT; act++) {
        int axis_act = rg_action_is_axis(act);
        int dz = act >= RG_ACT_CAMERA_LEFT && act <= RG_ACT_CAMERA_DOWN ? a->deadzone[1] : a->deadzone[0];
        int v = 0;
        for (int k = 0; k < a->nbind[act]; k++) {
            const rg_binding *b = &a->bind[act][k];
            int d = 0;
            switch (b->kind) {
            case RG_BIND_KEY:
                if (in->keys && b->code < in->nkeys && in->keys[b->code]) d = 32767;
                break;
            case RG_BIND_MOUSE:
                if (b->code >= 1 && b->code <= 32 && (in->mouse_buttons >> (b->code - 1)) & 1) d = 32767;
                break;
            case RG_BIND_MOUSE_MOTION: {
                float m = b->code ? in->mouse_dy : in->mouse_dx;
                if (!b->pos) m = -m;
                if (m > 0) {
                    double x = (double)m * a->mouse_sensitivity * (32767.0 / 20.0);
                    d = x >= 32767.0 ? 32767 : (int)x;
                    if (!axis_act) d = d >= a->threshold ? 32767 : 0;
                }
                break;
            }
            case RG_BIND_PAD_BUTTON:
                for (int p = 0; p < in->npads; p++)
                    if (b->code < RG_GP_BUTTONS && in->pads[p].button[b->code]) d = 32767;
                break;
            case RG_BIND_PAD_AXIS:
                for (int p = 0; p < in->npads; p++) {
                    if (b->code >= RG_GP_AXES) break;
                    int x;
                    int partner = stick_partner(b->code);
                    if (axis_act && a->stick_square && partner >= 0) {
                        /* the whole stick: round dead zone, DS2 square range */
                        int sx, sy;
                        rg_stick_shape(in->pads[p].axis[b->code], in->pads[p].axis[partner], dz, &sx, &sy);
                        x = axis_dir((int16_t)sx, b->pos);
                    } else {
                        x = axis_dir(in->pads[p].axis[b->code], b->pos);
                        x = axis_act ? deadzoned(x, dz) : (x >= a->threshold ? 32767 : 0);
                    }
                    if (x > d) d = x;
                }
                break;
            default:
                break;
            }
            if (d > v) v = d;
        }
        out[act] = v;
    }
}

void rg_actions_to_pad(const rg_actions *a, const int32_t v[RG_ACT_COUNT], rg_pad *out)
{
    rg_pad_neutral(out);
    for (int act = 0; act < RG_ACT_GAME_COUNT; act++) {
        int t = k_act[act].target;
        if (t >= 0 && t < 16 && v[act] > 0) out->buttons |= (uint16_t)(1u << t);
    }
    int walk = v[RG_ACT_WALK] > 0;
    /* stick axes: [k] = LX, LY, RX, RY from the half-axis actions */
    static const int neg[4] = { RG_ACT_MOVE_LEFT, RG_ACT_MOVE_UP, RG_ACT_CAMERA_LEFT, RG_ACT_CAMERA_UP };
    static const int pos[4] = { RG_ACT_MOVE_RIGHT, RG_ACT_MOVE_DOWN, RG_ACT_CAMERA_RIGHT, RG_ACT_CAMERA_DOWN };
    uint8_t *st[4] = { &out->lx, &out->ly, &out->rx, &out->ry };
    for (int k = 0; k < 4; k++) {
        int x = v[pos[k]] - v[neg[k]];
        float sens = a->sensitivity[k / 2];
        if (sens != 1.0f) {
            double y = (double)x * sens;
            x = y > 32767.0 ? 32767 : y < -32767.0 ? -32767 : (int)y;
        }
        if (a->invert[k]) x = -x;
        /* camera convention (docs/INPUT.md): the PS2 orbit camera (field, battle)
         * swings right around the leader on stick right = the view turns left, and
         * every camera looks down on stick up; first person already turns right */
        if (a->camera_pc && ((k == 2 && a->camera_view == RG_CAMVIEW_ORBIT) ||
                             (k == 3 && a->camera_view != RG_CAMVIEW_NONE)))
            x = -x;
        int o;
        if (a->stick_compensation) {
            o = rg_stick_compensate(x);
        } else {
            o = 128 + x * 128 / 32767;
            o = o < 0 ? 0 : o > 255 ? 255 : o;
        }
        if (walk && k < 2)   /* move stick: never past the walk band */
            o = o > RG_WALK_POS ? RG_WALK_POS : o < RG_WALK_NEG ? RG_WALK_NEG : o;
        *st[k] = (uint8_t)o;
    }
    rg_pad_fill_pressure(out);
}

uint8_t rg_stick_compensate(int v)
{
    if (v == 0) return 0x80;
    int m = v < 0 ? -v : v;
    if (m > 32767) m = 32767;
    int k = (int)(((int64_t)m * 78 + 16383) / 32767);
    if (k < 1) k = 1;
    if (k > 78) k = 78;
    return (uint8_t)(v > 0 ? 128 + 49 + k : 128 - 50 - k);
}

int rg_game_stick_value(uint8_t raw)
{
    int d = (int)raw - 128;
    if (d < RG_GAME_DEADZONE && d > -RG_GAME_DEADZONE) return 0;
    return d > 0 ? (d - 49) * 128 / 78 : (d + 50) * 128 / 78;
}

void rg_actions_eval(const rg_actions *a, const rg_input_snapshot *in, rg_pad *out)
{
    int32_t v[RG_ACT_COUNT];
    rg_actions_values(a, in, v);
    rg_actions_to_pad(a, v, out);
}

int rg_actions_ds2_report(const rg_actions *a, const rg_input_snapshot *in, uint8_t out[RG_DS2_REPORT_BYTES])
{
    rg_pad p;
    rg_actions_eval(a, in, &p);
    return rg_pad_ds2_report(&p, out);
}

/* ------------------------------------------------------------ roster */
void rg_roster_init(rg_pad_roster *r) { memset(r, 0, sizeof *r); }

int rg_roster_slot(const rg_pad_roster *r, uint32_t id)
{
    for (int i = 0; i < r->n; i++)
        if (r->id[i] == id) return i;
    return -1;
}

int rg_roster_add(rg_pad_roster *r, uint32_t id)
{
    int s = rg_roster_slot(r, id);
    if (s >= 0) return s;
    if (r->n >= RG_MAX_GAMEPADS) return -1;
    r->id[r->n] = id;
    return r->n++;
}

int rg_roster_remove(rg_pad_roster *r, uint32_t id)
{
    int s = rg_roster_slot(r, id);
    if (s < 0) return -1;
    memmove(&r->id[s], &r->id[s + 1], (size_t)(r->n - s - 1) * sizeof r->id[0]);
    r->n--;
    if (r->active_kind == RG_DEV_GAMEPAD && r->active_id == id) {
        r->active_kind = r->n ? RG_DEV_GAMEPAD : RG_DEV_KEYBOARD_MOUSE;
        r->active_id = r->n ? r->id[0] : 0;
    }
    return s;
}

void rg_roster_note_activity(rg_pad_roster *r, rg_device_kind kind, uint32_t id)
{
    r->active_kind = kind;
    r->active_id = kind == RG_DEV_GAMEPAD ? id : 0;
}

int rg_roster_port_slots(const rg_pad_roster *r, int players, int port, int out[RG_MAX_GAMEPADS])
{
    int k = 0;
    if (players == RG_PLAYERS_TWO) {
        if (port >= 0 && port < 2 && port < r->n) out[k++] = port;
        return k;
    }
    if (port != 0) return 0;
    for (int i = 0; i < r->n; i++) out[k++] = i;
    return k;
}

bool rg_roster_port_connected(const rg_pad_roster *r, int players, int port)
{
    if (port == 0) return true;
    return port == 1 && players == RG_PLAYERS_TWO && r->n >= 2;
}

int rg_roster_rumble_slot(const rg_pad_roster *r, int players, int port)
{
    if (players == RG_PLAYERS_TWO) return port >= 0 && port < 2 && port < r->n ? port : -1;
    if (port != 0 || !r->n) return -1;
    if (r->active_kind == RG_DEV_GAMEPAD) {
        int s = rg_roster_slot(r, r->active_id);
        if (s >= 0) return s;
    }
    return 0;
}

bool rg_gamepad_snap_active(const rg_gamepad_snap *g, int threshold)
{
    for (int b = 0; b < RG_GP_BUTTONS; b++)
        if (g->button[b]) return true;
    for (int a = 0; a < RG_GP_AXES; a++)
        if (g->axis[a] >= threshold || g->axis[a] <= -threshold) return true;
    return false;
}

/* ------------------------------------------------------------ press latch */
void rg_latch_clear(rg_press_latch *l) { memset(l, 0, sizeof *l); }

static void bump(uint8_t *c, int fields)
{
    int f = fields < 0 ? 0 : fields > 255 ? 255 : fields;
    if (*c < f) *c = (uint8_t)f;
}

void rg_latch_key(rg_press_latch *l, int sc, int fields)
{
    if (sc > 0 && sc < RG_LATCH_KEYS) bump(&l->key[sc], fields);
}

void rg_latch_mouse(rg_press_latch *l, int button, int fields)
{
    if (button >= 1 && button <= RG_LATCH_MOUSE) bump(&l->mouse[button - 1], fields);
}

void rg_latch_pad(rg_press_latch *l, int slot, int button, int fields)
{
    if (slot >= 0 && slot < RG_MAX_GAMEPADS && button >= 0 && button < RG_GP_BUTTONS)
        bump(&l->pad[slot][button], fields);
}

void rg_latch_step(rg_press_latch *l)
{
    for (int i = 0; i < RG_LATCH_KEYS; i++) if (l->key[i]) l->key[i]--;
    for (int i = 0; i < RG_LATCH_MOUSE; i++) if (l->mouse[i]) l->mouse[i]--;
    for (int s = 0; s < RG_MAX_GAMEPADS; s++)
        for (int b = 0; b < RG_GP_BUTTONS; b++) if (l->pad[s][b]) l->pad[s][b]--;
}

void rg_latch_remove_slot(rg_press_latch *l, int slot)
{
    if (slot < 0 || slot >= RG_MAX_GAMEPADS) return;
    memmove(l->pad[slot], l->pad[slot + 1], (size_t)(RG_MAX_GAMEPADS - slot - 1) * sizeof l->pad[0]);
    memset(l->pad[RG_MAX_GAMEPADS - 1], 0, sizeof l->pad[0]);
}

void rg_latch_apply_keys(const rg_press_latch *l, const bool *keys, int nkeys, bool *out, int outn)
{
    for (int i = 0; i < outn; i++) {
        bool k = keys && i < nkeys ? keys[i] : false;
        out[i] = k || (i < RG_LATCH_KEYS && l->key[i]);
    }
}

uint32_t rg_latch_apply_mouse(const rg_press_latch *l, uint32_t buttons)
{
    for (int i = 0; i < RG_LATCH_MOUSE; i++)
        if (l->mouse[i]) buttons |= 1u << i;
    return buttons;
}

void rg_latch_apply_pad(const rg_press_latch *l, int slot, rg_gamepad_snap *g)
{
    if (slot < 0 || slot >= RG_MAX_GAMEPADS) return;
    for (int b = 0; b < RG_GP_BUTTONS; b++)
        if (l->pad[slot][b]) g->button[b] = 1;
}

/* ------------------------------------------------------------ UI navigation */
void rg_ui_nav_init(rg_ui_nav *n)
{
    memset(n, 0, sizeof *n);
    n->delay_ms = 400;
    n->rate_ms = 90;
}

int rg_ui_nav_update(rg_ui_nav *n, const int32_t values[RG_ACT_COUNT], uint64_t now_ms,
                     int out[RG_ACT_COUNT - RG_ACT_GAME_COUNT])
{
    int k = 0;
    for (int act = RG_ACT_GAME_COUNT; act < RG_ACT_COUNT; act++) {
        int i = act - RG_ACT_GAME_COUNT;
        int on = values[act] > 0;
        int repeats = act <= RG_ACT_UI_RIGHT || act == RG_ACT_UI_PAGE_PREV || act == RG_ACT_UI_PAGE_NEXT;
        if (on && !n->held[i]) {
            out[k++] = act;
            n->next_ms[i] = now_ms + n->delay_ms;
        } else if (on && repeats && now_ms >= n->next_ms[i]) {
            out[k++] = act;
            n->next_ms[i] = now_ms + n->rate_ms;
        }
        n->held[i] = (uint8_t)on;
    }
    return k;
}

/* ------------------------------------------------------------ rebinding capture */
void rg_capture_init(rg_bind_capture *c)
{
    memset(c, 0, sizeof *c);
    c->cancel[0].kind = RG_BIND_KEY;
    c->cancel[0].code = SDL_SCANCODE_ESCAPE;
    c->cancel[1].kind = RG_BIND_PAD_BUTTON;
    c->cancel[1].code = SDL_GAMEPAD_BUTTON_GUIDE;
    c->ncancel = 2;
}

void rg_capture_begin(rg_bind_capture *c, const rg_gamepad_snap *pads, int npads)
{
    memset(c->axis_held, 0, sizeof c->axis_held);
    memset(&c->result, 0, sizeof c->result);
    for (int p = 0; pads && p < npads && p < RG_MAX_GAMEPADS; p++)
        for (int a = 0; a < RG_GP_AXES; a++) {
            int v = pads[p].axis[a];
            c->axis_held[p][a][1] = v > RG_CAPTURE_AXIS_LOW;
            c->axis_held[p][a][0] = v < -RG_CAPTURE_AXIS_LOW;
        }
    c->motion = false;
    c->motion_sum[0] = c->motion_sum[1] = 0;
    c->state = RG_CAPTURE_WAITING;
}

void rg_capture_begin_motion(rg_bind_capture *c)
{
    rg_capture_begin(c, NULL, 0);
    c->motion = true;
}

void rg_capture_end(rg_bind_capture *c) { c->state = RG_CAPTURE_IDLE; }

static rg_capture_state capture_take(rg_bind_capture *c, int kind, int code, int pos)
{
    rg_binding b;
    memset(&b, 0, sizeof b);
    b.kind = (uint8_t)kind;
    b.code = (uint16_t)code;
    b.pos = (uint8_t)pos;
    for (int i = 0; i < c->ncancel; i++)
        if (!memcmp(&c->cancel[i], &b, sizeof b)) { c->state = RG_CAPTURE_CANCELLED; return c->state; }
    /* a motion capture binds only motion; other presses are ignored */
    if (c->motion != (kind == RG_BIND_MOUSE_MOTION)) return c->state;
    c->result = b;
    c->state = RG_CAPTURE_DONE;
    return c->state;
}

rg_capture_state rg_capture_key(rg_bind_capture *c, int sc)
{
    if (c->state != RG_CAPTURE_WAITING) return c->state;
    /* only keys the binding text can name */
    if (sc <= SDL_SCANCODE_UNKNOWN || sc >= RG_LATCH_KEYS) return c->state;
    const char *n = SDL_GetScancodeName((SDL_Scancode)sc);
    if (!n || !*n) return c->state;
    return capture_take(c, RG_BIND_KEY, sc, 0);
}

rg_capture_state rg_capture_mouse_button(rg_bind_capture *c, int button)
{
    if (c->state != RG_CAPTURE_WAITING || button < 1 || button > 5) return c->state;
    return capture_take(c, RG_BIND_MOUSE, button, 0);
}

rg_capture_state rg_capture_pad_button(rg_bind_capture *c, int button)
{
    if (c->state != RG_CAPTURE_WAITING || button < 0 || button >= RG_GP_BUTTONS ||
        button >= SDL_GAMEPAD_BUTTON_COUNT) return c->state;
    return capture_take(c, RG_BIND_PAD_BUTTON, button, 0);
}

rg_capture_state rg_capture_pad_axis(rg_bind_capture *c, int slot, int axis, int16_t value)
{
    if (c->state != RG_CAPTURE_WAITING || slot < 0 || slot >= RG_MAX_GAMEPADS || axis < 0 ||
        axis >= RG_GP_AXES || axis >= SDL_GAMEPAD_AXIS_COUNT) return c->state;
    uint8_t *held = c->axis_held[slot][axis];
    int v = value;
    /* a direction re-arms once the axis is back at rest in that direction */
    if (v <= RG_CAPTURE_AXIS_LOW) held[1] = 0;
    if (v >= -RG_CAPTURE_AXIS_LOW) held[0] = 0;
    if (v >= RG_CAPTURE_AXIS_HIGH && !held[1]) { held[1] = 1; return capture_take(c, RG_BIND_PAD_AXIS, axis, 1); }
    if (v <= -RG_CAPTURE_AXIS_HIGH && !held[0]) { held[0] = 1; return capture_take(c, RG_BIND_PAD_AXIS, axis, 0); }
    return c->state;
}

rg_capture_state rg_capture_mouse_motion(rg_bind_capture *c, float dx, float dy)
{
    if (c->state != RG_CAPTURE_WAITING || !c->motion) return c->state;
    if (dx != dx || dy != dy) return c->state;   /* NaN */
    c->motion_sum[0] += dx;
    c->motion_sum[1] += dy;
    for (int a = 0; a < 2; a++) {
        float v = c->motion_sum[a], o = c->motion_sum[a ^ 1];
        float av = v < 0 ? -v : v, ao = o < 0 ? -o : o;
        if (av >= (float)RG_CAPTURE_MOUSE_DIST && av >= 2.0f * ao)
            return capture_take(c, RG_BIND_MOUSE_MOTION, a, v > 0);
    }
    return c->state;
}

size_t rg_capture_text(const rg_bind_capture *c, char *out, size_t cap)
{
    if (c->state != RG_CAPTURE_DONE) { if (cap) out[0] = 0; return 0; }
    return rg_binding_format(&c->result, out, cap);
}

size_t rg_capture_cancel_hint(const rg_bind_capture *c, char *out, size_t cap)
{
    size_t len = 0;
    if (cap) out[0] = 0;
    for (int i = 0; i < c->ncancel; i++) {
        char one[96];
        rg_binding_format(&c->cancel[i], one, sizeof one);
        const char *sep = i ? " / " : "";
        size_t need = strlen(sep) + strlen(one);
        if (cap && len + need < cap) { strcat(out, sep); strcat(out, one); }
        len += need;
    }
    return len;
}

/* ------------------------------------------------------------ overlay hold chord */
/* docs/INPUT.md "Opening the settings overlay with a gamepad".  Per pad slot:
 *
 *   IDLE     no chord button held
 *   PENDING  some (not all) chord buttons held, for less than grace_ms: held
 *            back from the game, so a chord pressed a little unevenly never
 *            leaks its first button
 *   ARMED    all held: held back; after hold_ms the chord fires (LOCKED)
 *   LOCKED   fired or broken off: held back until every chord button is up
 *   PASS     a lone press outlived the grace: the game sees it as it is
 *   TAP      a lone press released inside the grace (or a one-button chord
 *            released before hold_ms): the game sees the buttons pressed for
 *            tap_fields fields, so a tap is never lost
 */
static bool chord_button_ok(int b) { return b >= 0 && b < RG_GP_BUTTONS && b < SDL_GAMEPAD_BUTTON_COUNT; }

void rg_chord_init(rg_chord *c)
{
    memset(c, 0, sizeof *c);
    c->hold_ms = 1000;
    c->grace_ms = RG_CHORD_GRACE_MS;
    c->tap_fields = 2;
}

void rg_chord_reset(rg_chord *c) { memset(c->slot, 0, sizeof c->slot); }

int rg_chord_set(rg_chord *c, const rg_binding *b, int n)
{
    uint32_t mask = 0;
    if (n < 0 || n > RG_CHORD_MAX) return -1;
    for (int i = 0; i < n; i++) {
        if (b[i].kind != RG_BIND_PAD_BUTTON || !chord_button_ok(b[i].code)) return -1;
        mask |= 1u << b[i].code;
    }
    if (mask != c->mask) rg_chord_reset(c);
    c->n = 0;
    for (int i = 0; i < n; i++) {
        int dup = 0;
        for (int k = 0; k < c->n; k++) dup |= c->button[k] == b[i].code;
        if (!dup) c->button[c->n++] = (uint8_t)b[i].code;
    }
    c->mask = mask;
    return 0;
}

int rg_chord_validate(const char *text, char *norm, size_t normcap, char *err, size_t errcap, void *user)
{
    int rc = rg_binding_validate(text, norm, normcap, err, errcap, user);
    if (rc != 0) return rc;
    rg_binding b[RG_BIND_MAX];
    int n = rg_binding_parse_list(norm, b, err, errcap);
    if (n < 0) return -1;
    if (n > RG_CHORD_MAX) {
        if (err && errcap) snprintf(err, errcap, "a chord has at most %d buttons", RG_CHORD_MAX);
        return -1;
    }
    for (int i = 0; i < n; i++)
        if (b[i].kind != RG_BIND_PAD_BUTTON || !chord_button_ok(b[i].code)) {
            char t[64];
            rg_binding_format(&b[i], t, sizeof t);
            if (err && errcap) snprintf(err, errcap, "%s: a chord takes gamepad buttons only (pad:...)", t);
            return -1;
        }
    return 0;
}

void rg_chord_from_settings(rg_chord *c, const rg_settings *s)
{
    if (rg_settings_find(s, "input.overlay_chord") < 0) return;
    rg_binding b[RG_BIND_MAX];
    int n = rg_binding_parse_list(rg_settings_get_string(s, "input.overlay_chord"), b, NULL, 0);
    if (n < 0 || rg_chord_set(c, b, n) != 0) rg_chord_set(c, b, 0);
    double hold = rg_settings_get_float(s, "input.overlay_chord_hold");
    c->hold_ms = (uint32_t)(hold * 1000.0 + 0.5);
    int f = rg_settings_find(s, "input.min_press_fields") >= 0 ? rg_settings_get_int(s, "input.min_press_fields") : 2;
    c->tap_fields = f < 2 ? 2 : f;
}

static uint32_t chord_held(const rg_chord *c, const rg_gamepad_snap *g)
{
    uint32_t h = 0;
    for (int i = 0; i < c->n; i++)
        if (g->button[c->button[i]]) h |= 1u << c->button[i];
    return h;
}

bool rg_chord_update(rg_chord *c, int slot, const rg_gamepad_snap *g, uint64_t now_ms)
{
    if (slot < 0 || slot >= RG_MAX_GAMEPADS) return false;
    rg_chord_slot *s = &c->slot[slot];
    if (!c->n) { memset(s, 0, sizeof *s); return false; }
    uint32_t h = g ? chord_held(c, g) : 0, all = c->mask;
    if (s->phase == RG_CHORD_TAP) {
        if (s->tap_left) s->tap_left--;
        if (s->tap_left) return false;
        s->phase = RG_CHORD_IDLE;
    }
    switch (s->phase) {
    case RG_CHORD_IDLE:
        if (!h) break;
        s->t0 = now_ms;
        s->seen = h;
        s->phase = h == all ? RG_CHORD_ARMED : RG_CHORD_PENDING;
        break;
    case RG_CHORD_PENDING:
        s->seen |= h;
        if (h == all) { s->phase = RG_CHORD_ARMED; s->t0 = now_ms; }
        else if (!h) { s->phase = RG_CHORD_TAP; s->tap_left = (uint8_t)c->tap_fields; }
        else if (now_ms - s->t0 >= c->grace_ms) s->phase = RG_CHORD_PASS;
        break;
    case RG_CHORD_ARMED:
        if (h == all) {
            if (now_ms - s->t0 >= c->hold_ms) { s->phase = RG_CHORD_LOCKED; return true; }
        } else if (c->n == 1) {   /* released early: a one-button chord's tap reaches the game */
            s->phase = RG_CHORD_TAP;
            s->seen = all;
            s->tap_left = (uint8_t)c->tap_fields;
        } else {
            s->phase = h ? RG_CHORD_LOCKED : RG_CHORD_IDLE;   /* broken off: nothing reaches the game */
        }
        break;
    case RG_CHORD_LOCKED:
        if (!h) s->phase = RG_CHORD_IDLE;
        break;
    case RG_CHORD_PASS:
        if (h == all) { s->phase = RG_CHORD_ARMED; s->t0 = now_ms; }
        else if (!h) s->phase = RG_CHORD_IDLE;
        break;
    default:
        s->phase = RG_CHORD_IDLE;
        break;
    }
    return false;
}

void rg_chord_filter(const rg_chord *c, int slot, rg_gamepad_snap *g)
{
    if (!c->n || slot < 0 || slot >= RG_MAX_GAMEPADS) return;
    const rg_chord_slot *s = &c->slot[slot];
    if (s->phase == RG_CHORD_IDLE || s->phase == RG_CHORD_PASS) return;
    for (int i = 0; i < c->n; i++) {
        int b = c->button[i];
        g->button[b] = s->phase == RG_CHORD_TAP && s->tap_left && (s->seen & (1u << b)) ? 1 : 0;
    }
}

bool rg_chord_holding(const rg_chord *c, int slot)
{
    if (!c->n || slot < 0 || slot >= RG_MAX_GAMEPADS) return false;
    int p = c->slot[slot].phase;
    return p == RG_CHORD_PENDING || p == RG_CHORD_ARMED || p == RG_CHORD_LOCKED;
}

void rg_chord_remove_slot(rg_chord *c, int slot)
{
    if (slot < 0 || slot >= RG_MAX_GAMEPADS) return;
    memmove(&c->slot[slot], &c->slot[slot + 1], (size_t)(RG_MAX_GAMEPADS - slot - 1) * sizeof c->slot[0]);
    memset(&c->slot[RG_MAX_GAMEPADS - 1], 0, sizeof c->slot[0]);
}

/* ------------------------------------------------------------ device type and prompts */
rg_pad_family rg_pad_family_from_sdl_type(int t)
{
    switch (t) {
    case SDL_GAMEPAD_TYPE_PS3:
    case SDL_GAMEPAD_TYPE_PS4:
    case SDL_GAMEPAD_TYPE_PS5:
        return RG_PAD_FAMILY_PLAYSTATION;
    case SDL_GAMEPAD_TYPE_XBOX360:
    case SDL_GAMEPAD_TYPE_XBOXONE:
    case SDL_GAMEPAD_TYPE_STEAM:          /* Steam Controller / Deck: A B X Y in Xbox positions */
        return RG_PAD_FAMILY_XBOX;
    case SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_PRO:
    case SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_LEFT:
    case SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT:
    case SDL_GAMEPAD_TYPE_NINTENDO_SWITCH_JOYCON_PAIR:
    case SDL_GAMEPAD_TYPE_GAMECUBE:
        return RG_PAD_FAMILY_NINTENDO;
    default:                              /* UNKNOWN, STANDARD, anything newer */
        return RG_PAD_FAMILY_GENERIC;
    }
}

const char *rg_pad_family_name(rg_pad_family f)
{
    static const char *const n[] = { "none", "playstation", "xbox", "nintendo", "generic" };
    return (unsigned)f < 5 ? n[f] : "none";
}

const char *rg_prompt_style_name(rg_prompt_style s)
{
    static const char *const n[] = { "playstation", "xbox", "nintendo", "keyboard" };
    return (unsigned)s < RG_PROMPT_COUNT ? n[s] : "playstation";
}

rg_prompt_style rg_prompt_style_resolve(int setting, bool scripted, rg_device_kind active,
                                        rg_pad_family family, rg_prompt_style previous)
{
    if (scripted) return RG_PROMPT_PLAYSTATION;
    if (setting > RG_PROMPTS_AUTO && setting <= RG_PROMPTS_KEYBOARD)
        return (rg_prompt_style)(setting - RG_PROMPTS_PLAYSTATION);
    if (active == RG_DEV_KEYBOARD_MOUSE) return RG_PROMPT_KEYBOARD;
    if (active == RG_DEV_GAMEPAD) {
        switch (family) {
        case RG_PAD_FAMILY_PLAYSTATION: return RG_PROMPT_PLAYSTATION;
        case RG_PAD_FAMILY_NINTENDO: return RG_PROMPT_NINTENDO;
        case RG_PAD_FAMILY_XBOX:
        case RG_PAD_FAMILY_GENERIC: return RG_PROMPT_XBOX;
        default: break;
        }
    }
    return (unsigned)previous < RG_PROMPT_COUNT ? previous : RG_PROMPT_PLAYSTATION;
}

/* ------------------------------------------------------------ prompt labels */
/* docs/INPUT.md "Prompts in the settings overlay".  Gamepad buttons are SDL
 * positional (south = Cross / A / B on a Switch pad). */
static rg_prompt_style label_family(rg_prompt_style st, int sdl_type, bool *specific)
{
    rg_pad_family f = sdl_type >= 0 ? rg_pad_family_from_sdl_type(sdl_type) : RG_PAD_FAMILY_NONE;
    rg_prompt_style ff = f == RG_PAD_FAMILY_PLAYSTATION ? RG_PROMPT_PLAYSTATION
                       : f == RG_PAD_FAMILY_NINTENDO ? RG_PROMPT_NINTENDO
                       : f == RG_PAD_FAMILY_NONE ? RG_PROMPT_PLAYSTATION : RG_PROMPT_XBOX;
    if (st == RG_PROMPT_KEYBOARD || (unsigned)st >= RG_PROMPT_COUNT) st = ff;
    *specific = f != RG_PAD_FAMILY_NONE && f != RG_PAD_FAMILY_GENERIC && ff == st;
    return st;
}

size_t rg_prompt_pad_button_label(int button, rg_prompt_style style, int sdl_type, char *out, size_t cap)
{
    bool sp = false;
    rg_prompt_style st = label_family(style, sdl_type, &sp);
    int ps = st == RG_PROMPT_PLAYSTATION, nin = st == RG_PROMPT_NINTENDO;
    const char *l = NULL;
#define PICK(p, x, n) (ps ? (p) : nin ? (n) : (x))
    switch (button) {
    case SDL_GAMEPAD_BUTTON_SOUTH: l = PICK("Cross", "A", "B"); break;
    case SDL_GAMEPAD_BUTTON_EAST: l = PICK("Circle", "B", "A"); break;
    case SDL_GAMEPAD_BUTTON_WEST: l = PICK("Square", "X", "Y"); break;
    case SDL_GAMEPAD_BUTTON_NORTH: l = PICK("Triangle", "Y", "X"); break;
    case SDL_GAMEPAD_BUTTON_BACK:
        l = PICK(sp && sdl_type == SDL_GAMEPAD_TYPE_PS4 ? "Share" : sp && sdl_type == SDL_GAMEPAD_TYPE_PS5 ? "Create" : "Select",
                 sp && sdl_type == SDL_GAMEPAD_TYPE_XBOX360 ? "Back" : "View", "Minus");
        break;
    case SDL_GAMEPAD_BUTTON_START:
        l = PICK(sp && (sdl_type == SDL_GAMEPAD_TYPE_PS4 || sdl_type == SDL_GAMEPAD_TYPE_PS5) ? "Options" : "Start",
                 sp && sdl_type == SDL_GAMEPAD_TYPE_XBOX360 ? "Start" : "Menu", "Plus");
        break;
    case SDL_GAMEPAD_BUTTON_GUIDE:
        l = PICK("PS button", sp && sdl_type == SDL_GAMEPAD_TYPE_STEAM ? "Steam button" : "Xbox button", "Home");
        break;
    case SDL_GAMEPAD_BUTTON_LEFT_STICK: l = PICK("L3", "LS", "L-stick"); break;
    case SDL_GAMEPAD_BUTTON_RIGHT_STICK: l = PICK("R3", "RS", "R-stick"); break;
    case SDL_GAMEPAD_BUTTON_LEFT_SHOULDER: l = PICK("L1", "LB", "L"); break;
    case SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER: l = PICK("R1", "RB", "R"); break;
    case SDL_GAMEPAD_BUTTON_DPAD_UP: l = "Up"; break;
    case SDL_GAMEPAD_BUTTON_DPAD_DOWN: l = "Down"; break;
    case SDL_GAMEPAD_BUTTON_DPAD_LEFT: l = "Left"; break;
    case SDL_GAMEPAD_BUTTON_DPAD_RIGHT: l = "Right"; break;
    case SDL_GAMEPAD_BUTTON_MISC1: l = PICK("Mic", "Share", "Capture"); break;
    case SDL_GAMEPAD_BUTTON_TOUCHPAD: l = "Touchpad"; break;
    /* Xbox Elite P1-P4; the Steam Deck's back grips are R4 / L4 / R5 / L5 */
    case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1: l = sp && sdl_type == SDL_GAMEPAD_TYPE_STEAM ? "R4" : "P1"; break;
    case SDL_GAMEPAD_BUTTON_LEFT_PADDLE1: l = sp && sdl_type == SDL_GAMEPAD_TYPE_STEAM ? "L4" : "P3"; break;
    case SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2: l = sp && sdl_type == SDL_GAMEPAD_TYPE_STEAM ? "R5" : "P2"; break;
    case SDL_GAMEPAD_BUTTON_LEFT_PADDLE2: l = sp && sdl_type == SDL_GAMEPAD_TYPE_STEAM ? "L5" : "P4"; break;
    default: break;
    }
    if (!l) {
        rg_binding b = { RG_BIND_PAD_BUTTON, 0, (uint16_t)button };
        return rg_binding_format(&b, out, cap);
    }
    return (size_t)snprintf(out, cap, "%s", l);
}

static size_t axis_label(int axis, int pos, rg_prompt_style style, int sdl_type, char *out, size_t cap)
{
    bool sp = false;
    rg_prompt_style st = label_family(style, sdl_type, &sp);
    int ps = st == RG_PROMPT_PLAYSTATION, nin = st == RG_PROMPT_NINTENDO;
    const char *dir = axis == SDL_GAMEPAD_AXIS_LEFTX || axis == SDL_GAMEPAD_AXIS_RIGHTX ? (pos ? "right" : "left")
                                                                                         : (pos ? "down" : "up");
    switch (axis) {
    case SDL_GAMEPAD_AXIS_LEFTX: case SDL_GAMEPAD_AXIS_LEFTY:
        return (size_t)snprintf(out, cap, "%s %s", PICK("L-stick", "LS", "L-stick"), dir);
    case SDL_GAMEPAD_AXIS_RIGHTX: case SDL_GAMEPAD_AXIS_RIGHTY:
        return (size_t)snprintf(out, cap, "%s %s", PICK("R-stick", "RS", "R-stick"), dir);
    case SDL_GAMEPAD_AXIS_LEFT_TRIGGER: return (size_t)snprintf(out, cap, "%s", PICK("L2", "LT", "ZL"));
    case SDL_GAMEPAD_AXIS_RIGHT_TRIGGER: return (size_t)snprintf(out, cap, "%s", PICK("R2", "RT", "ZR"));
    default: {
        rg_binding b = { RG_BIND_PAD_AXIS, (uint8_t)pos, (uint16_t)axis };
        return rg_binding_format(&b, out, cap);
    }
    }
#undef PICK
}

static size_t key_label(int sc, char *out, size_t cap)
{
    static const char *const k_short[][2] = {
        { "Escape", "Esc" }, { "Return", "Enter" }, { "PageUp", "PgUp" }, { "PageDown", "PgDn" },
        { "Backspace", "Backspace" }, { "Left Shift", "LShift" }, { "Right Shift", "RShift" },
        { "Left Ctrl", "LCtrl" }, { "Right Ctrl", "RCtrl" },
    };
    const char *n = SDL_GetScancodeName((SDL_Scancode)sc);
    if (!n || !*n) n = "?";
    for (size_t i = 0; i < sizeof k_short / sizeof k_short[0]; i++)
        if (!strcmp(n, k_short[i][0])) { n = k_short[i][1]; break; }
    return (size_t)snprintf(out, cap, "%s", n);
}

size_t rg_prompt_binding_label(const rg_binding *b, rg_prompt_style style, int sdl_type, char *out, size_t cap)
{
    static const char *const k_mouse[] = { "?", "Mouse left", "Mouse middle", "Mouse right", "Mouse 4", "Mouse 5" };
    switch (b->kind) {
    case RG_BIND_KEY: return key_label(b->code, out, cap);
    case RG_BIND_MOUSE: return (size_t)snprintf(out, cap, "%s", b->code <= 5 ? k_mouse[b->code] : "Mouse");
    case RG_BIND_PAD_BUTTON: return rg_prompt_pad_button_label(b->code, style, sdl_type, out, cap);
    case RG_BIND_PAD_AXIS: return axis_label(b->code, b->pos, style, sdl_type, out, cap);
    default: return rg_binding_format(b, out, cap);
    }
}

/* The binding to show for an action in a style: keyboard -> the first key
 * (else mouse button); a gamepad style -> the first gamepad button or axis;
 * else the first binding.  NULL when unbound. */
static const rg_binding *pick_binding(const rg_actions *a, int act, rg_prompt_style st)
{
    if (act < 0 || act >= RG_ACT_COUNT || a->nbind[act] <= 0) return NULL;
    const rg_binding *b = a->bind[act];
    int n = a->nbind[act];
    for (int pass = 0; pass < 2; pass++)
        for (int i = 0; i < n; i++) {
            int k = b[i].kind;
            bool want = st == RG_PROMPT_KEYBOARD ? (pass ? k == RG_BIND_MOUSE : k == RG_BIND_KEY)
                                                 : (k == RG_BIND_PAD_BUTTON || k == RG_BIND_PAD_AXIS);
            if (want) return &b[i];
        }
    return &b[0];
}

size_t rg_prompt_action_label(const rg_actions *a, int act, rg_prompt_style style, int sdl_type, char *out, size_t cap)
{
    const rg_binding *b = pick_binding(a, act, style);
    if (!b) return (size_t)snprintf(out, cap, "-");
    return rg_prompt_binding_label(b, style, sdl_type, out, cap);
}

size_t rg_prompt_chord_label(const rg_chord *c, rg_prompt_style style, int sdl_type, char *out, size_t cap)
{
    size_t len = 0;
    if (cap) out[0] = 0;
    for (int i = 0; i < c->n; i++) {
        char one[48];
        rg_prompt_pad_button_label(c->button[i], style, sdl_type, one, sizeof one);
        len += (size_t)snprintf(out + (len < cap ? len : cap), len < cap ? cap - len : 0, "%s%s", i ? "+" : "", one);
    }
    return len;
}

static void join4(const rg_actions *a, const int act[4], rg_prompt_style st, int t, char *out, size_t cap)
{
    char l[4][40];
    for (int i = 0; i < 4; i++) rg_prompt_action_label(a, act[i], st, t, l[i], sizeof l[i]);
    snprintf(out, cap, "%s/%s/%s/%s", l[0], l[1], l[2], l[3]);
}

void rg_menu_prompts_from_input(rg_menu *m, const rg_actions *a, const rg_chord *c, rg_prompt_style st,
                                int sdl_type)
{
    static const int k_ui[] = {
        [RG_MP_UP] = RG_ACT_UI_UP, [RG_MP_DOWN] = RG_ACT_UI_DOWN, [RG_MP_LEFT] = RG_ACT_UI_LEFT,
        [RG_MP_RIGHT] = RG_ACT_UI_RIGHT, [RG_MP_ACCEPT] = RG_ACT_UI_ACCEPT, [RG_MP_BACK] = RG_ACT_UI_BACK,
        [RG_MP_PREV] = RG_ACT_UI_PAGE_PREV, [RG_MP_NEXT] = RG_ACT_UI_PAGE_NEXT,
    };
    char t[RG_MENU_PROMPT_LEN];
    for (int p = RG_MP_UP; p <= RG_MP_NEXT; p++) {
        rg_prompt_action_label(a, k_ui[p], st, sdl_type, t, sizeof t);
        rg_menu_set_prompt(m, (rg_menu_prompt)p, t);
    }
    rg_prompt_action_label(a, RG_ACT_PAUSE, st, sdl_type, t, sizeof t);
    rg_menu_set_prompt(m, RG_MP_START, t);
    rg_prompt_action_label(a, RG_ACT_MAP, st, sdl_type, t, sizeof t);
    rg_menu_set_prompt(m, RG_MP_SELECT, t);
    static const int k_dpad[4] = { RG_ACT_DPAD_UP, RG_ACT_DPAD_LEFT, RG_ACT_DPAD_DOWN, RG_ACT_DPAD_RIGHT };
    static const int k_ls[4] = { RG_ACT_MOVE_UP, RG_ACT_MOVE_LEFT, RG_ACT_MOVE_DOWN, RG_ACT_MOVE_RIGHT };
    static const int k_rs[4] = { RG_ACT_CAMERA_UP, RG_ACT_CAMERA_LEFT, RG_ACT_CAMERA_DOWN, RG_ACT_CAMERA_RIGHT };
    if (st == RG_PROMPT_KEYBOARD) {
        join4(a, k_dpad, st, sdl_type, t, sizeof t);
        rg_menu_set_prompt(m, RG_MP_DPAD, t);
        join4(a, k_ls, st, sdl_type, t, sizeof t);
        rg_menu_set_prompt(m, RG_MP_LS, t);
        join4(a, k_rs, st, sdl_type, t, sizeof t);
        rg_menu_set_prompt(m, RG_MP_RS, t);
    } else {
        bool sp;
        rg_prompt_style f = label_family(st, sdl_type, &sp);
        rg_menu_set_prompt(m, RG_MP_DPAD, f == RG_PROMPT_NINTENDO ? "+Control Pad" : "D-pad");
        rg_menu_set_prompt(m, RG_MP_LS, f == RG_PROMPT_XBOX ? "Left stick" : "L-stick");
        rg_menu_set_prompt(m, RG_MP_RS, f == RG_PROMPT_XBOX ? "Right stick" : "R-stick");
    }
    /* open / close: the overlay action's binding for the device, plus the chord on a gamepad */
    char ov[RG_MENU_PROMPT_LEN];
    rg_prompt_action_label(a, RG_ACT_UI_OVERLAY, st, sdl_type, ov, sizeof ov);
    if (st != RG_PROMPT_KEYBOARD && c && c->n) {
        char ch[RG_MENU_PROMPT_LEN];
        rg_prompt_chord_label(c, st, sdl_type, ch, sizeof ch);
        snprintf(t, sizeof t, "%s or hold %s %g s", ov, ch, c->hold_ms / 1000.0);
    } else {
        snprintf(t, sizeof t, "%s", ov);
    }
    rg_menu_set_prompt(m, RG_MP_TOGGLE, t);
    /* the capture's cancel inputs (key:Escape / pad:guide, rg_capture_init) */
    rg_binding esc = { RG_BIND_KEY, 0, SDL_SCANCODE_ESCAPE };
    char k[32], g[32];
    rg_prompt_binding_label(&esc, RG_PROMPT_KEYBOARD, -1, k, sizeof k);
    rg_prompt_pad_button_label(SDL_GAMEPAD_BUTTON_GUIDE, st, sdl_type, g, sizeof g);
    snprintf(m->capture_hint, sizeof m->capture_hint, "%s / %s", k, g);
    snprintf(m->prompt_style, sizeof m->prompt_style, "%s", rg_prompt_style_name(st));
}

/* ------------------------------------------------------------ mouse look */
/* docs/INPUT.md "Mouse camera implementation".  Motion is converted to look
 * units (Q12 radians) as it arrives; the fraction below one unit is carried to
 * the next motion, so slow motion is neither lost in a dead band nor rounded
 * up, and a take never saturates the way a stick does (the clamp is 8 rad). */
void rg_look_acc_init(rg_look_acc *a)
{
    memset(a, 0, sizeof *a);
    a->yaw_scale = a->pitch_scale = 1.0f;
}

void rg_look_acc_reset(rg_look_acc *a)
{
    a->rem_yaw = a->rem_pitch = 0.0;
    a->pend_yaw = a->pend_pitch = 0;
}

void rg_look_acc_from_settings(rg_look_acc *a, const rg_settings *s)
{
    if (rg_settings_find(s, "input.mouse_look") < 0) return;
    bool on = rg_settings_get_bool(s, "input.mouse_look");
    if (!on && a->enabled) rg_look_acc_reset(a);
    a->enabled = on;
    a->yaw_scale = (float)rg_settings_get_float(s, "input.mouse_yaw_scale");
    a->pitch_scale = (float)rg_settings_get_float(s, "input.mouse_pitch_scale");
    a->invert_x = rg_settings_get_bool(s, "input.mouse_invert_x");
    a->invert_y = rg_settings_get_bool(s, "input.mouse_invert_y");
}

static void look_add(double *rem, int64_t *pend, double units)
{
    double t = *rem + units;
    double q = floor(t + 0.5);
    *rem = t - q;
    *pend += (int64_t)q;
    const int64_t lim = (int64_t)1 << 40;
    if (*pend > lim) *pend = lim;
    if (*pend < -lim) *pend = -lim;
}

void rg_look_acc_motion(rg_look_acc *a, float dx, float dy)
{
    if (!a->enabled || !isfinite(dx) || !isfinite(dy)) return;
    const double k = RG_LOOK_RAD_PER_COUNT * RG_LOOK_UNITS_PER_RAD;
    if (fabs((double)dx) > 1e9 || fabs((double)dy) > 1e9) return;
    double yaw = (double)dx * a->yaw_scale * k;      /* right = turn right */
    double pitch = -(double)dy * a->pitch_scale * k; /* SDL y grows down: up = look up */
    if (a->invert_x) yaw = -yaw;
    if (a->invert_y) pitch = -pitch;
    look_add(&a->rem_yaw, &a->pend_yaw, yaw);
    look_add(&a->rem_pitch, &a->pend_pitch, pitch);
}

static int32_t look_clamp(int64_t v)
{
    return (int32_t)(v > RG_LOOK_MAX ? RG_LOOK_MAX : v < -RG_LOOK_MAX ? -RG_LOOK_MAX : v);
}

void rg_look_acc_take(rg_look_acc *a, rg_look *out)
{
    out->yaw = look_clamp(a->pend_yaw);
    out->pitch = look_clamp(a->pend_pitch);
    a->pend_yaw = a->pend_pitch = 0;
}
