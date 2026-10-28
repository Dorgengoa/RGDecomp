/* SPDX-License-Identifier: CC0-1.0 */
/* Input-action layer (PLAN.md P4 "Pad", P6 "Controls"; docs/INPUT.md).
 *
 *   actions    game actions named by game role, not PS2 button (move /
 *              camera half axes, d-pad, confirm, cancel, attack, menu,
 *              camera turn, decline, recentre, switch leader, first person,
 *              pause, map), the walk modifier, plus host UI actions
 *              (settings overlay toggle and navigation)
 *   bindings   up to RG_BIND_MAX per action, mixed across keyboard keys,
 *              mouse buttons, mouse motion, gamepad buttons and gamepad
 *              axes; stored as text in the settings registry
 *              ("input.bind.<action>")
 *   tuning     per-stick deadzone and sensitivity, per-axis inversion,
 *              trigger threshold, mouse sensitivity, vibration strength,
 *              the walk modifier and the optional dead-zone compensation
 *              (a gameplay option, off in "original")
 *   devices    a gamepad roster with hot-plug (stable connection order),
 *              one- or two-player port policy, the most recently used device
 *              (for prompts and rumble), and a press latch so a tap shorter
 *              than a field still reaches the game
 *   adapter    action values -> the exact rg_pad / DS2 report the game reads
 *              (rg_pad_ds2_report).  Pure: the same snapshot always gives the
 *              same report.  Input scripts bypass all of this in
 *              rg_host_read_pad (host.h), so scripted runs stay deterministic.
 *
 * Everything here is pure (no SDL_Init; only SDL's name tables for key and
 * gamepad names), so tests drive it directly.
 */
#ifndef RG_INPUT_H
#define RG_INPUT_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "host.h"
#include "rg_settings.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------ actions */
/* Ids name the game role (docs/CONTROLS-AUDIT.md section 3 / 4b), not the PS2
 * button; the default PS2 position is in the comment.  Roles marked "?" are
 * INFERRED by the audit and still provisional.  The pre-audit ids
 * (shoulder_left, trigger_right, stick_left_click, start, select, ...) stay
 * accepted as aliases: rg_action_from_id and the settings registry
 * (input.bind.<old id>) map them to the new ones. */
typedef enum rg_action {
    /* analog half axes (left stick = move, right stick = camera) */
    RG_ACT_MOVE_LEFT, RG_ACT_MOVE_RIGHT, RG_ACT_MOVE_UP, RG_ACT_MOVE_DOWN,
    RG_ACT_CAMERA_LEFT, RG_ACT_CAMERA_RIGHT, RG_ACT_CAMERA_UP, RG_ACT_CAMERA_DOWN,
    /* digital game actions */
    RG_ACT_DPAD_UP, RG_ACT_DPAD_DOWN, RG_ACT_DPAD_LEFT, RG_ACT_DPAD_RIGHT,
    RG_ACT_CONFIRM,          /* Cross: confirm / examine / talk */
    RG_ACT_CANCEL,           /* Circle: cancel; jump? (field), sub-weapon? (battle) */
    RG_ACT_ATTACK,           /* Square: attack */
    RG_ACT_MENU,             /* Triangle: main menu / battle commands */
    RG_ACT_CAMERA_TURN_LEFT, /* L1: turn camera left / previous tab / accept suggestion */
    RG_ACT_CAMERA_TURN_RIGHT,/* R1: turn camera right / guard? / next tab */
    RG_ACT_DECLINE,          /* L2: decline suggestion / page */
    RG_ACT_CAMERA_RECENTRE,  /* R2: recentre camera / zoom (hold) */
    RG_ACT_SWITCH_LEADER,    /* L3 */
    RG_ACT_FIRST_PERSON,     /* R3 */
    RG_ACT_PAUSE,            /* Start: pause / skip */
    RG_ACT_MAP,              /* Select: map / camera type */
    /* host modifier (drives no PS2 input itself): while held, the move stick
     * is limited to the walk band (RG_WALK_POS / RG_WALK_NEG) */
    RG_ACT_WALK,
    RG_ACT_GAME_COUNT,
    /* host UI (never reach the game) */
    RG_ACT_UI_UP = RG_ACT_GAME_COUNT, RG_ACT_UI_DOWN, RG_ACT_UI_LEFT, RG_ACT_UI_RIGHT,
    RG_ACT_UI_ACCEPT, RG_ACT_UI_BACK, RG_ACT_UI_PAGE_PREV, RG_ACT_UI_PAGE_NEXT,
    RG_ACT_UI_OVERLAY,       /* open / close the settings overlay */
    RG_ACT_COUNT
} rg_action;

/* Pre-audit enum names (source compatibility). */
#define RG_ACT_SHOULDER_LEFT     RG_ACT_CAMERA_TURN_LEFT
#define RG_ACT_SHOULDER_RIGHT    RG_ACT_CAMERA_TURN_RIGHT
#define RG_ACT_TRIGGER_LEFT      RG_ACT_DECLINE
#define RG_ACT_TRIGGER_RIGHT     RG_ACT_CAMERA_RECENTRE
#define RG_ACT_STICK_LEFT_CLICK  RG_ACT_SWITCH_LEADER
#define RG_ACT_STICK_RIGHT_CLICK RG_ACT_FIRST_PERSON
#define RG_ACT_START             RG_ACT_PAUSE
#define RG_ACT_SELECT            RG_ACT_MAP

/* The walk band.  The game maps a stick byte v with d = v - 128:
 * |d| < 50 -> 0, d > 0 -> (d - 49) * 128 / 78, d < 0 -> (d + 50) * 128 / 78
 * (integer division), then / 128; the leader walks when the move vector's
 * length is >= 0.16 and runs at >= 0.9 (PlayerControlUpdateMaybe_1fc4a0).
 * 0xDB (d = +91) and 0x24 (d = -92) both decode to +-68/128 = 0.53125, the
 * nearest game value to the band's middle (0.53); a diagonal (both axes) is
 * 0.751, still a walk.  Full deflection (0x00 / 0xFF) decodes to +-1 = run. */
#define RG_WALK_POS 0xDB
#define RG_WALK_NEG 0x24
/* The game's own per-axis dead zone, in report bytes: |v - 128| < 50 reads 0. */
#define RG_GAME_DEADZONE 50

const char *rg_action_id(int a);       /* "move_left", "confirm", "ui_accept", ... */
const char *rg_action_label(int a);    /* menu text */
/* -1 if unknown; also accepts the pre-audit ids (rg_action_alias). */
int rg_action_from_id(const char *id);
/* The i-th pre-audit alias: old id -> action.  NULL past the end. */
const char *rg_action_alias(int i, int *action);
/* The rg_pad input an action drives (0..15 = button bit number, 16..23 =
 * RG_IN_* stick half axis), or -1 for UI actions and the walk modifier. */
int rg_action_target(int a);
bool rg_action_is_axis(int a);         /* the 8 stick half axes */

/* ------------------------------------------------------------ bindings */
#define RG_BIND_MAX 8

typedef enum rg_bind_kind {
    RG_BIND_NONE = 0,
    RG_BIND_KEY,          /* code = SDL_Scancode */
    RG_BIND_MOUSE,        /* code = SDL mouse button (1 left, 2 middle, 3 right, 4 x1, 5 x2) */
    RG_BIND_MOUSE_MOTION, /* code = 0 x, 1 y; pos = direction */
    RG_BIND_PAD_BUTTON,   /* code = SDL_GamepadButton */
    RG_BIND_PAD_AXIS      /* code = SDL_GamepadAxis; pos = direction */
} rg_bind_kind;

typedef struct rg_binding {
    uint8_t kind;   /* rg_bind_kind */
    uint8_t pos;    /* axis / motion direction: 1 = +, 0 = - */
    uint16_t code;
} rg_binding;

/* Text: comma-separated  key:<SDL scancode name> | mouse:left|middle|right|x1|x2
 * | mouse:x+|x-|y+|y- | pad:<SDL gamepad button> | axis:<SDL gamepad axis>+|-.
 * "key:comma" names the ',' key.  Empty text = unbound.  Duplicates are
 * dropped.  Returns the count (0..RG_BIND_MAX) or -1 (reason in err). */
int rg_binding_parse_list(const char *text, rg_binding out[RG_BIND_MAX], char *err, size_t errcap);
/* Canonical text (round-trips through rg_binding_parse_list). */
size_t rg_binding_format_list(const rg_binding *b, int n, char *out, size_t cap);
size_t rg_binding_format(const rg_binding *b, char *out, size_t cap);
/* The settings validator for BINDING settings (normalises to canonical text). */
int rg_binding_validate(const char *text, char *norm, size_t normcap, char *err, size_t errcap, void *user);

/* ------------------------------------------------------------ the action map */
enum { RG_AXIS_MOVE_X, RG_AXIS_MOVE_Y, RG_AXIS_CAMERA_X, RG_AXIS_CAMERA_Y, RG_AXIS_COUNT };
enum { RG_PLAYERS_ONE = 0, RG_PLAYERS_TWO = 1 };
/* rg_actions.camera_view: which game camera read the stick last (the game's hint,
 * rg_host_set_camera_view; docs/INPUT.md "Camera stick convention") */
enum { RG_CAMVIEW_NONE = 0, RG_CAMVIEW_ORBIT = 1, RG_CAMVIEW_FIRST_PERSON = 2 };

typedef struct rg_actions {
    rg_binding bind[RG_ACT_COUNT][RG_BIND_MAX];
    int nbind[RG_ACT_COUNT];
    int deadzone[2];          /* left (move), right (camera) stick: raw 0..32767 */
    int threshold;            /* analog -> digital: raw 0..32767 */
    float sensitivity[2];     /* move, camera: deflection multiplier */
    uint8_t invert[RG_AXIS_COUNT];
    float mouse_sensitivity;  /* 1.0: 20 px of motion in one field = full deflection */
    float vibration;          /* 0..1 rumble strength (the US game never vibrates:
                                 docs/CONTROLS-AUDIT.md section 7) */
    bool stick_compensation;  /* gameplay option: pre-map sticks past the game's
                                 own dead zone (rg_stick_compensate) */
    int players;              /* RG_PLAYERS_* */
    int min_press_fields;     /* press latch length (0 = off) */
    bool stick_square;        /* gamepad sticks: round dead zone + the DualShock 2's
                                 square range (rg_stick_shape); off: per axis */
    bool camera_pc;           /* camera stick convention: PC (right = view right,
                                 up = look up) instead of the PS2 original */
    int camera_view;          /* runtime, not a setting: RG_CAMVIEW_* (the host
                                 copies its hint in before each evaluation) */
} rg_actions;

/* Fraction 0..1 -> raw axis units: (int)(f * 32767 + 0.5). */
int rg_actions_raw(double fraction);

/* The default keyboard + mouse + gamepad layout (docs/INPUT.md). */
void rg_actions_default(rg_actions *a);
/* The legacy rg_input_map's bindings and deadzone/threshold, action by
 * action (each map input is one action's target). */
void rg_actions_from_input_map(rg_actions *a, const rg_input_map *m);

/* Registers input.bind.<action> for every action plus the tuning settings,
 * with rg_actions_default as the defaults. */
int rg_actions_register_settings(rg_settings *s);
/* Builds the action map from the registry's effective values (an invalid
 * binding text cannot be stored; see rg_binding_validate). */
void rg_actions_from_settings(rg_actions *a, const rg_settings *s);

/* ------------------------------------------------------------ evaluation */
/* One port's live sources for one field.  Any part may be absent. */
typedef struct rg_input_snapshot {
    const bool *keys;              /* SDL keyboard state by scancode */
    int nkeys;
    uint32_t mouse_buttons;        /* bit (b - 1) for SDL mouse button b */
    float mouse_dx, mouse_dy;      /* relative motion in this field, pixels */
    const rg_gamepad_snap *pads;   /* the gamepads feeding this port */
    int npads;
} rg_input_snapshot;

/* Every action's magnitude 0..32767: digital sources give 32767; a gamepad
 * axis on a digital action is 32767 at or above the threshold, else 0; on a
 * stick half axis it is deadzoned (per stick) and rescaled; mouse motion is
 * scaled by mouse_sensitivity.  The strongest binding wins. */
void rg_actions_values(const rg_actions *a, const rg_input_snapshot *in, int32_t out[RG_ACT_COUNT]);
/* The adapter: game action values -> the pad the game reads.  Buttons from
 * the digital actions; each stick axis = (positive - negative) x sensitivity,
 * clamped, inverted if set, then 128 + v * 128 / 32767 clamped to 0..255
 * (the legacy rg_input_eval formula), or rg_stick_compensate when
 * stick_compensation is on; with the walk action held the two move axes are
 * clamped to [RG_WALK_NEG, RG_WALK_POS]; pressure 0/255 from the buttons. */
void rg_actions_to_pad(const rg_actions *a, const int32_t v[RG_ACT_COUNT], rg_pad *out);
/* DualShock 2 stick range for one physical stick (x, y raw SDL values): a round
 * dead zone dz (0..32767), the rest rescaled to 0..1 along the radius, then the
 * circle stretched onto the square (full tilt reads 32767 on the dominant axis
 * in every direction, as a DS2 stick reaches its corners).  The radius is
 * rescaled from [dz, RG_STICK_OUTER] (92% tilt reads full, as a DS2 saturates
 * before its gate): a pure axis value gives (x - dz) * 32767 / (OUTER - dz). */
#define RG_STICK_OUTER 30146   /* 0.92 * 32767 */
void rg_stick_shape(int x, int y, int dz, int *ox, int *oy);
/* Dead-zone compensation for one axis value v (-32767..32767, after the
 * host dead zone, sensitivity and inversion): 0 -> 0x80, otherwise
 * k = round(|v| * 78 / 32767) clamped to 1..78 and 0x80 + 49 + k (positive)
 * or 0x80 - 50 - k (negative), so the smallest host deflection is the first
 * byte past the game's dead zone and full deflection is 0x00 / 0xFF.  The
 * game then reads about |v| / 32767 (k * 128 / 78 / 128): the host dead zone
 * becomes the only one.  Per axis (the game's dead zone is per axis too). */
uint8_t rg_stick_compensate(int v);
/* The game's own stick decode (all twelve getters): a report byte ->
 * -128..128 (divide by 128 for the Norm getters). */
int rg_game_stick_value(uint8_t raw);
/* values + to_pad. */
void rg_actions_eval(const rg_actions *a, const rg_input_snapshot *in, rg_pad *out);
/* The 20-byte scePadRead buffer for a snapshot (eval + rg_pad_ds2_report). */
int rg_actions_ds2_report(const rg_actions *a, const rg_input_snapshot *in,
                          uint8_t out[RG_DS2_REPORT_BYTES]);

/* ------------------------------------------------------------ devices */
#define RG_MAX_GAMEPADS 8

typedef enum rg_device_kind {
    RG_DEV_NONE = 0, RG_DEV_KEYBOARD_MOUSE, RG_DEV_GAMEPAD
} rg_device_kind;

/* Connected gamepads in connection order (slot 0 = oldest).  A removal
 * closes the gap, so slots stay dense; ids are the SDL joystick instance ids
 * (any nonzero u32 in tests). */
typedef struct rg_pad_roster {
    uint32_t id[RG_MAX_GAMEPADS];
    int n;
    rg_device_kind active_kind;   /* most recently used device */
    uint32_t active_id;           /* its gamepad id (RG_DEV_GAMEPAD) */
} rg_pad_roster;

void rg_roster_init(rg_pad_roster *r);
/* Returns the new slot, the existing slot for a known id, or -1 when full. */
int rg_roster_add(rg_pad_roster *r, uint32_t id);
/* Returns the slot the id had (later slots shift down by one), or -1. */
int rg_roster_remove(rg_pad_roster *r, uint32_t id);
int rg_roster_slot(const rg_pad_roster *r, uint32_t id);
void rg_roster_note_activity(rg_pad_roster *r, rg_device_kind kind, uint32_t id);
/* The slots feeding `port`: ONE player: every gamepad drives port 0 (port 1
 * gets none).  TWO players: slot 0 -> port 0, slot 1 -> port 1.  Returns the
 * count. */
int rg_roster_port_slots(const rg_pad_roster *r, int players, int port, int out[RG_MAX_GAMEPADS]);
/* Port 0 is always connected; port 1 only with TWO players and >= 2 pads. */
bool rg_roster_port_connected(const rg_pad_roster *r, int players, int port);
/* Which gamepad slot rumbles for `port`: ONE player: the most recently used
 * gamepad (else slot 0); TWO: the port's slot.  -1 if none. */
int rg_roster_rumble_slot(const rg_pad_roster *r, int players, int port);
/* Does this gamepad snapshot count as "being used" (any button, or an axis
 * past the threshold)? */
bool rg_gamepad_snap_active(const rg_gamepad_snap *g, int threshold);

/* ------------------------------------------------------------ press latch */
/* A press seen by an event keeps its input "held" for at least N fields, so a
 * tap that starts and ends between two field boundaries still reaches the
 * game (which may sample only every second VBlank).  Counters step once per
 * field (rg_host_pump).  Deterministic for a given event sequence. */
#define RG_LATCH_KEYS 512
#define RG_LATCH_MOUSE 8
typedef struct rg_press_latch {
    uint8_t key[RG_LATCH_KEYS];
    uint8_t mouse[RG_LATCH_MOUSE];
    uint8_t pad[RG_MAX_GAMEPADS][RG_GP_BUTTONS];
} rg_press_latch;

void rg_latch_clear(rg_press_latch *l);
void rg_latch_key(rg_press_latch *l, int scancode, int fields);
void rg_latch_mouse(rg_press_latch *l, int button, int fields);
void rg_latch_pad(rg_press_latch *l, int slot, int button, int fields);
void rg_latch_step(rg_press_latch *l);                 /* one field passed */
void rg_latch_remove_slot(rg_press_latch *l, int slot); /* mirrors rg_roster_remove */
/* ORs the latched presses into copies of the live state. */
void rg_latch_apply_keys(const rg_press_latch *l, const bool *keys, int nkeys, bool *out, int outn);
uint32_t rg_latch_apply_mouse(const rg_press_latch *l, uint32_t buttons);
void rg_latch_apply_pad(const rg_press_latch *l, int slot, rg_gamepad_snap *g);

/* ------------------------------------------------------------ UI navigation */
/* Edge + auto-repeat for the overlay: rg_ui_nav_update takes the held state
 * of the UI actions (from rg_actions_values > 0) and the time, and emits the
 * actions that fire now (press edges, then repeats after `delay_ms` every
 * `rate_ms` for the four directions and the page actions). */
typedef struct rg_ui_nav {
    uint8_t held[RG_ACT_COUNT - RG_ACT_GAME_COUNT];
    uint64_t next_ms[RG_ACT_COUNT - RG_ACT_GAME_COUNT];
    uint32_t delay_ms, rate_ms;
} rg_ui_nav;

void rg_ui_nav_init(rg_ui_nav *n);
/* values: rg_actions_values output.  Writes fired actions (RG_ACT_UI_*) to
 * out; returns the count. */
int rg_ui_nav_update(rg_ui_nav *n, const int32_t values[RG_ACT_COUNT], uint64_t now_ms,
                     int out[RG_ACT_COUNT - RG_ACT_GAME_COUNT]);

/* ------------------------------------------------------------ rebinding capture */
/* "Press a key / button" detection for the settings menu (docs/INPUT.md
 * "Rebinding from the menu").  Pure and time-free: the menu owns the timeout.
 * The host feeds it raw device events while the menu is capturing; the first
 * NEW press becomes the binding:
 *   - a key down (not a repeat), a mouse button down, a gamepad button down;
 *   - a gamepad axis moving past RG_CAPTURE_AXIS_HIGH in one direction after
 *     having been at or under RG_CAPTURE_AXIS_LOW in that direction (axes are
 *     seeded from the pads' state at begin, so a stick or trigger already
 *     held when the capture starts must return to rest first).
 * Inputs held when the capture starts never produce a new down event, so the
 * press that started the capture (Return, South) is not captured.  The
 * cancel inputs (default key:Escape and pad:guide) cancel instead of binding.
 * Mouse motion is not captured by a normal capture (too easy to trigger by
 * accident).  A separate motion capture (rg_capture_begin_motion, the menu's
 * "Capture mouse motion" row) takes ONLY mouse motion: the relative motion is
 * summed per axis and becomes mouse:x+/x-/y+/y- once one axis has moved
 * RG_CAPTURE_MOUSE_DIST pixels net and at least twice as far as the other;
 * keys and buttons other than the cancel inputs are ignored meanwhile. */
#define RG_CAPTURE_AXIS_HIGH 16384   /* 0.5 of full deflection */
#define RG_CAPTURE_AXIS_LOW 8192     /* 0.25 */
#define RG_CAPTURE_MOUSE_DIST 300    /* px of net relative motion (motion capture) */
#define RG_CAPTURE_CANCEL_MAX 4

typedef enum rg_capture_state {
    RG_CAPTURE_IDLE = 0,    /* not started / result taken */
    RG_CAPTURE_WAITING,     /* listening */
    RG_CAPTURE_DONE,        /* `result` holds the binding */
    RG_CAPTURE_CANCELLED    /* a cancel input was pressed */
} rg_capture_state;

typedef struct rg_bind_capture {
    rg_capture_state state;
    rg_binding result;
    rg_binding cancel[RG_CAPTURE_CANCEL_MAX];   /* inputs that cancel */
    int ncancel;
    /* per gamepad slot, axis and direction: 1 = held past LOW (must return) */
    uint8_t axis_held[RG_MAX_GAMEPADS][RG_GP_AXES][2];
    bool motion;              /* motion capture: only mouse motion binds */
    float motion_sum[2];      /* net relative x / y since begin */
} rg_bind_capture;

/* Sets the default cancel inputs (key:Escape, pad:guide); state IDLE. */
void rg_capture_init(rg_bind_capture *c);
/* Starts listening.  pads (may be NULL) is the current state of the gamepads
 * by roster slot, used to seed the axis rest state. */
void rg_capture_begin(rg_bind_capture *c, const rg_gamepad_snap *pads, int npads);
/* Starts a motion capture (see above): only mouse motion binds. */
void rg_capture_begin_motion(rg_bind_capture *c);
/* Event feeds; each returns the state after the event (a no-op unless
 * WAITING). */
rg_capture_state rg_capture_key(rg_bind_capture *c, int scancode);
rg_capture_state rg_capture_mouse_button(rg_bind_capture *c, int button);
rg_capture_state rg_capture_pad_button(rg_bind_capture *c, int button);
rg_capture_state rg_capture_pad_axis(rg_bind_capture *c, int slot, int axis, int16_t value);
/* Relative mouse motion (ignored unless a motion capture is waiting). */
rg_capture_state rg_capture_mouse_motion(rg_bind_capture *c, float dx, float dy);
/* Stops listening (state IDLE). */
void rg_capture_end(rg_bind_capture *c);
/* The canonical text of the captured binding ("key:Space"); "" otherwise. */
size_t rg_capture_text(const rg_bind_capture *c, char *out, size_t cap);
/* "Esc / pad:guide" style text naming the cancel inputs (for the prompt). */
size_t rg_capture_cancel_hint(const rg_bind_capture *c, char *out, size_t cap);

/* ------------------------------------------------------------ overlay hold chord */
/* docs/INPUT.md "Opening the settings overlay with a gamepad".  Gamepad
 * buttons held together for hold_ms toggle the settings overlay
 * (input.overlay_chord, default pad:back + pad:start = Select + Start;
 * input.overlay_chord_hold, default 1 s).  Per pad slot, the chord's buttons
 * never reach the game while the chord is being pressed, held, or released:
 *   - a chord button pressed alone is held back for grace_ms (RG_CHORD_GRACE_MS);
 *     if the rest of the chord follows in that time the press never reaches
 *     the game, else the game gets it from then on (PASS) as it is;
 *   - a lone tap released inside the grace reaches the game afterwards, held
 *     for tap_fields fields (max(input.min_press_fields, 2)), so no tap is lost;
 *   - the whole chord: held back until every chord button is up again,
 *     whether it fired or was let go early (a one-button chord let go early
 *     is a tap, as above);
 *   - a chord completed while its first button already passed (PASS: held
 *     longer than the grace) still fires; the game then sees that button
 *     released.
 * rg_chord_update runs once per pump on the slot's snapshot (latch applied);
 * rg_chord_filter applies the result to every snapshot read in that field.
 * Scripted and headless runs never call either.  Pure; time is passed in. */
#define RG_CHORD_MAX 4
#define RG_CHORD_GRACE_MS 100

typedef enum rg_chord_phase {
    RG_CHORD_IDLE = 0, RG_CHORD_PENDING, RG_CHORD_ARMED, RG_CHORD_LOCKED, RG_CHORD_PASS, RG_CHORD_TAP
} rg_chord_phase;

typedef struct rg_chord_slot {
    uint8_t phase;        /* rg_chord_phase */
    uint8_t tap_left;     /* TAP: fields still to press */
    uint32_t seen;        /* chord buttons pressed since IDLE (bit = SDL button) */
    uint64_t t0;          /* PENDING: first press; ARMED: whole chord down */
} rg_chord_slot;

typedef struct rg_chord {
    uint8_t button[RG_CHORD_MAX];   /* SDL_GamepadButton */
    int n;                          /* 0 = off */
    uint32_t mask;                  /* bit per chord button */
    uint32_t hold_ms, grace_ms;
    int tap_fields;
    rg_chord_slot slot[RG_MAX_GAMEPADS];
} rg_chord;

/* Off, hold 1000 ms, grace RG_CHORD_GRACE_MS, tap 2 fields. */
void rg_chord_init(rg_chord *c);
/* The chord's buttons: 0..RG_CHORD_MAX pad buttons (duplicates dropped);
 * -1 (unchanged) for anything else.  A different set resets every slot. */
int rg_chord_set(rg_chord *c, const rg_binding *b, int n);
/* input.overlay_chord, input.overlay_chord_hold, input.min_press_fields. */
void rg_chord_from_settings(rg_chord *c, const rg_settings *s);
/* The settings validator: a binding list of at most RG_CHORD_MAX pad: buttons
 * (empty = off). */
int rg_chord_validate(const char *text, char *norm, size_t normcap, char *err, size_t errcap, void *user);
/* One step for a slot (g = its snapshot this pump, NULL = nothing held).
 * Returns true once when the chord fires. */
bool rg_chord_update(rg_chord *c, int slot, const rg_gamepad_snap *g, uint64_t now_ms);
/* Clears (or, for a pending tap, sets) the chord buttons in a snapshot of that slot. */
void rg_chord_filter(const rg_chord *c, int slot, rg_gamepad_snap *g);
/* The slot's chord buttons are being held back (PENDING, ARMED, LOCKED). */
bool rg_chord_holding(const rg_chord *c, int slot);
void rg_chord_reset(rg_chord *c);
void rg_chord_remove_slot(rg_chord *c, int slot);   /* mirrors rg_roster_remove */

/* ------------------------------------------------------------ device type and prompts */
/* The family of a gamepad, from SDL_GetGamepadType (docs/PROMPTS.md). */
typedef enum rg_pad_family {
    RG_PAD_FAMILY_NONE = 0,       /* no gamepad */
    RG_PAD_FAMILY_PLAYSTATION,    /* PS3, PS4, PS5 */
    RG_PAD_FAMILY_XBOX,           /* Xbox 360, Xbox One / Series, Steam (Deck): Xbox labels */
    RG_PAD_FAMILY_NINTENDO,       /* Switch Pro, Joy-Cons, GameCube */
    RG_PAD_FAMILY_GENERIC         /* standard / unknown mapping */
} rg_pad_family;

/* The button prompt style (the `prompts.style` setting minus "auto"). */
typedef enum rg_prompt_style {
    RG_PROMPT_PLAYSTATION = 0,    /* the original gaiji2 texture */
    RG_PROMPT_XBOX,
    RG_PROMPT_NINTENDO,
    RG_PROMPT_KEYBOARD,
    RG_PROMPT_COUNT
} rg_prompt_style;

/* `prompts.style` values (enum index order). */
enum { RG_PROMPTS_AUTO = 0, RG_PROMPTS_PLAYSTATION, RG_PROMPTS_XBOX, RG_PROMPTS_NINTENDO,
       RG_PROMPTS_KEYBOARD };

/* SDL_GamepadType value -> family (pure; out-of-range = GENERIC). */
rg_pad_family rg_pad_family_from_sdl_type(int sdl_gamepad_type);
const char *rg_pad_family_name(rg_pad_family f);     /* "playstation", "xbox", ... "none" */
const char *rg_prompt_style_name(rg_prompt_style s); /* "playstation", "xbox", "nintendo", "keyboard" */
/* The style to show.  scripted (an input script or a headless run): always
 * PLAYSTATION, whatever the setting and devices, so traces and frame hashes
 * never depend on the machine.  Otherwise a fixed setting wins; "auto"
 * follows the most recently used device: keyboard/mouse -> KEYBOARD, a
 * gamepad -> its family (GENERIC -> XBOX, docs/PROMPTS.md), no device yet ->
 * `previous` (start with PLAYSTATION). */
rg_prompt_style rg_prompt_style_resolve(int setting, bool scripted, rg_device_kind active,
                                        rg_pad_family family, rg_prompt_style previous);

/* Prompt labels (docs/INPUT.md "Prompts in the settings overlay").  sdl_type
 * is the SDL_GamepadType of the pad in use (-1: none); it picks model labels
 * (Options / Share / Create, View / Back, the Deck's R4..L5) when its family
 * matches the style.  The keyboard style labels pad-only bindings by that
 * pad's family (PlayStation without one).  Positional, as the bindings:
 * south = Cross / A / B (Switch). */
size_t rg_prompt_pad_button_label(int sdl_button, rg_prompt_style style, int sdl_type, char *out, size_t cap);
/* Any binding: keys get short names (Esc, Enter, PgUp), mouse buttons
 * "Mouse left", axes "L-stick up" / "LT" / "ZR", buttons as above. */
size_t rg_prompt_binding_label(const rg_binding *b, rg_prompt_style style, int sdl_type, char *out, size_t cap);
/* The action's binding for the style (keyboard: its first key, else mouse
 * button; a pad style: its first pad button or axis; else its first
 * binding), labelled; "-" when unbound. */
size_t rg_prompt_action_label(const rg_actions *a, int action, rg_prompt_style style, int sdl_type,
                              char *out, size_t cap);
/* "Select+Start", "View+Menu", "Minus+Plus" ... */
size_t rg_prompt_chord_label(const rg_chord *c, rg_prompt_style style, int sdl_type, char *out, size_t cap);
/* Fills the settings menu's prompt table (rg_menu_set_prompt: the [accept]
 * ... [toggle] tags) and its capture hint for a style. */
struct rg_menu;
void rg_menu_prompts_from_input(struct rg_menu *m, const rg_actions *a, const rg_chord *c,
                                rg_prompt_style style, int sdl_type);

/* Host side (host_sdl.c).  The family of the most recently used gamepad
 * (slot 0 if no gamepad was used yet); NONE without a gamepad (and always
 * NONE headless). */
rg_pad_family rg_host_active_pad_family(const rg_host *h);
/* The prompt style now: rg_prompt_style_resolve with the attached
 * `prompts.style` (auto without settings), scripted = a script is set or the
 * host is headless.  Remembers the result as the next `previous`. */
rg_prompt_style rg_host_prompt_style(rg_host *h);
/* The host's rebinding detector (the overlay feeds it while capturing). */
rg_bind_capture *rg_host_capture(rg_host *h);

/* ------------------------------------------------------------ mouse look */
/* Mouse camera (docs/INPUT.md "Mouse camera implementation").  Relative
 * motion -> look units (rg_look, host.h: Q12 radians), with
 * input.mouse_yaw_scale / input.mouse_pitch_scale and the inversions applied
 * first.  The fraction below one unit is carried into the next motion, so slow
 * motion is neither lost in a dead band nor rounded up; there is no stick-like
 * saturation (a take is clamped only at RG_LOOK_MAX = 8 rad).  Pure. */
#define RG_LOOK_UNITS_PER_RAD 4096.0
#define RG_LOOK_RAD_PER_COUNT 0.0015   /* one count at scale 1.0 (0.086 deg) */
typedef struct rg_look_acc {
    bool enabled;                 /* input.mouse_look */
    float yaw_scale, pitch_scale; /* input.mouse_yaw_scale / _pitch_scale */
    bool invert_x, invert_y;      /* input.mouse_invert_x / _y */
    double rem_yaw, rem_pitch;    /* carried sub-unit remainders */
    int64_t pend_yaw, pend_pitch; /* whole units since the last take */
} rg_look_acc;
/* Off, scales 1, nothing pending. */
void rg_look_acc_init(rg_look_acc *a);
/* The input.mouse_* settings (pending motion and remainders are kept; turning
 * the setting off drops them). */
void rg_look_acc_from_settings(rg_look_acc *a, const rg_settings *s);
/* dx > 0 = right, dy > 0 = down (SDL relative motion, counts).  Ignored when
 * off, or for non-finite values. */
void rg_look_acc_motion(rg_look_acc *a, float dx, float dy);
/* The pending whole units (clamped to +-RG_LOOK_MAX, the excess dropped);
 * pending -> 0, the remainders stay. */
void rg_look_acc_take(rg_look_acc *a, rg_look *out);
/* Drops pending units and remainders (the mouse was released). */
void rg_look_acc_reset(rg_look_acc *a);

#ifdef __cplusplus
}
#endif
#endif
