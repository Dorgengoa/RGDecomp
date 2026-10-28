# Input-action layer (`src/host/rg_input.h`)

PLAN.md P4 "Pad" and P6 "Controls". Live input goes through **actions** that don't name
PS2 buttons. Each action has several bindings across keyboard, mouse and gamepads. An
adapter turns the action values into the exact DualShock 2 report the game reads.
Bindings and tuning live in the settings registry (docs/SETTINGS.md), so the file, the
command line and the menu all edit the same thing.

All of it is original CC0 code. It's pure (no `SDL_Init`; it uses only SDL's key and
gamepad name tables), so the tests drive it directly.

| Path | What |
| --- | --- |
| `src/host/rg_input.h` | Actions, bindings, the action map, evaluation and the DS2 adapter, the gamepad roster, the press latch, UI navigation |
| `src/host/host_input.c` | Implementation, the default layout, `input.*` settings registration |
| `src/host/host_sdl.c` | Live wiring: SDL events → roster, latch, activity; snapshots → `rg_actions_eval`; rumble; overlay navigation |
| `tests/settings/` | `rg-settings-tests`, CTest label `input` |

## Determinism first

- **Scripts bypass everything.** `rg_host_read_pad` checks the input script before
  anything else: port 0 reads the `tools/trace/input.py` table, port 1 reads neutral. No
  binding, setting, latch, overlay or device state is consulted. `input.script_bypass`
  checks this with input settings changed, over 400 VBlanks, in two separate hosts with
  identical report hashes. The runtime's `pad_script`/`determinism` tests are unchanged and
  pass.
- **The adapter is a pure function.** `rg_actions_eval(map, snapshot)` gives the same
  `rg_pad` for the same snapshot, every time. There's no time, no state, and no "previous
  report". Edges stay where the game makes them: it compares successive pad reads, exactly
  as on hardware.
- **Live state changes only at field boundaries.** SDL's keyboard and gamepad state, mouse
  motion and the latch are updated in `rg_host_pump` (once per field, in the runtime's host
  half). So every read inside one field sees the same snapshot.
- **Press latch.** A tap that goes down and up between two pumps would never be seen, and
  at 30 fps logic the game samples only every second VBlank. Every key, mouse button and
  gamepad button **down event** therefore keeps its input held for at least
  `input.min_press_fields` fields (default 2; 0 turns it off). Held inputs are unaffected.
  The latch steps once per pump, so it's deterministic for a given event sequence.

## Actions

Ids name the **game role** from the controls audit (docs/CONTROLS-AUDIT.md sections 3, 4
and 4b), not the PS2 button. The default PS2 positions are unchanged. Game actions (each
drives exactly one `rg_pad` input, except `walk`):

| Action id | Menu label (role) | DS2 target | Keyboard | Gamepad (SDL positional) |
| --- | --- | --- | --- | --- |
| `move_left/right/up/down` | Move (camera-relative) | left stick X-/X+/Y-/Y+ | A / D / W / S | left stick |
| `camera_left/right/up/down` | Rotate camera / camera height | right stick | J / L / I / K | right stick |
| `dpad_up/down/left/right` | D-pad (menus, lock-on target) | d-pad | arrow keys | d-pad |
| `confirm` | Confirm / Talk / Sword attack | Cross | Space, X | South |
| `cancel` | Cancel / Jump | Circle | C | East |
| `attack` | Gun / Sub-weapon | Square | Z | West |
| `menu` | Menu / Battle commands | Triangle | Tab | North |
| `camera_turn_left` | Camera left / Previous tab / Accept suggestion | L1 | Q | left shoulder |
| `camera_turn_right` | Camera right / Guard? / Next tab | R1 | E | right shoulder |
| `decline` | Decline suggestion / Page | L2 | 1 | left trigger |
| `camera_recentre` | Recentre camera / Zoom (hold) | R2 | 3 | right trigger |
| `switch_leader` | Switch leader | L3 | V | left stick click |
| `first_person` | First-person look | R3 | B | right stick click |
| `pause` | Pause / Skip | Start | Return | Start |
| `map` | Map / Camera type | Select | Backspace | Back |
| `walk` | Walk (hold) | none: limits the move stick to the walk band | Left Shift | unbound |

**Provisional roles.** Three roles are **inferred** by the audit from flag bits whose
consumers were not traced: jump (Circle in the field; the battle table reads Cross),
sub-weapon (Circle in battle) and guard (R1 held in battle). Their labels carry a `?`
until a recorded run confirms them; then only the label text changes. Confirm/cancel are
hard-wired to Cross/Circle in the game (`MenuGridCursorInput_28e170`), so a "Japanese
layout" can only be a report-level swap of the two buttons everywhere.

**Old ids still load.** The pre-audit ids are aliases: a config file line, a preset,
`--set` and `rg_action_from_id` accept them and act on the new id; the file is written
back with the new id. (`confirm`, `cancel`, `attack`, `menu`, the sticks and the d-pad
keep their ids.) The old C enum names (`RG_ACT_SHOULDER_LEFT`, ...) are `#define`s of the
new ones.

| Old id | New id |
| --- | --- |
| `shoulder_left` / `shoulder_right` | `camera_turn_left` / `camera_turn_right` |
| `trigger_left` / `trigger_right` | `decline` / `camera_recentre` |
| `stick_left_click` / `stick_right_click` | `switch_leader` / `first_person` |
| `start` / `select` | `pause` / `map` |

Host UI actions (never reach the game):

| Action id | Keyboard | Gamepad |
| --- | --- | --- |
| `ui_up/down/left/right` | arrows, W/S/A/D | d-pad, left stick |
| `ui_accept` / `ui_back` | Return, Space / Escape, Backspace | South / East |
| `ui_page_prev` / `ui_page_next` | Page Up, Q / Page Down, E | left / right shoulder |
| `ui_overlay` | F1 | Guide, touchpad |
| (`input.overlay_chord`, not an action) | | hold Back + Start (Select + Start) for 1 s: "Opening the settings overlay with a gamepad" |

The keyboard layout differs from the old `rg_input_map` default: movement is W A S D
(was W A F D), Triangle is Tab (was S), and Cross is Space as well as X. With a key bound
to several actions, every one of them fires: Return is both `pause` and `ui_accept`, and
if you bind `confirm` to Return as well, Return sends Cross + Start.

Fixed hotkeys stay outside the action map: Esc quits (only while the overlay is closed),
F11 / Alt+Enter toggles fullscreen (and updates `display.window_mode`), F12 takes a
screenshot. While Alt is held, the keyboard doesn't feed the game.

## Bindings

Up to 8 per action (`RG_BIND_MAX`), stored in `input.bind.<action>` as text:

| Form | Source |
| --- | --- |
| `key:<SDL scancode name>` | key (`key:Space`, `key:Left Shift`, `key:Keypad 8`); `key:comma` names the `,` key |
| `mouse:left` `middle` `right` `x1` `x2` | mouse button |
| `mouse:x+` `x-` `y+` `y-` | mouse motion in that direction (relative, per field) |
| `pad:<SDL gamepad button>` | `a` (south), `b`, `x`, `y`, `back`, `guide`, `start`, `leftstick`, `leftshoulder`, `dpup`, `misc1`, `touchpad`, … |
| `axis:<SDL gamepad axis>+` or `-` | `leftx-`, `righty+`, `lefttrigger+`, … |

```ini
[input]
bind.confirm = key:Return, key:K, mouse:left, pad:a, axis:righttrigger+
bind.camera_right = axis:rightx+, mouse:x+
bind.cancel =                      # unbound
```

- Names are case-insensitive. The registry stores the **canonical** form (SDL's spelling,
  `", "` separated, duplicates dropped), so `KEY:return ,pad:A` becomes
  `key:Return, pad:a`. Order is kept.
- A bad list (unknown key, missing axis sign, a ninth binding) is invalid as a whole: from
  a file the action keeps its default, with a warning naming the line.
- `rg_binding_parse_list` / `rg_binding_format_list` are the text API.
  `rg_binding_validate` is the registry validator.

## Rebinding from the menu

The settings overlay edits `input.bind.*` directly (docs/SETTINGS.md "Menu API"). It works
with keyboard alone and with a gamepad alone.

- **Binding editor.** ACCEPT on a binding row (Controls or Menu controls page) lists the
  action's bindings, one row each, then "Add a binding", "Capture mouse motion", "Reset to
  default (...)" and "Back". On a binding row LEFT/RIGHT picks `[Replace]` or `[Remove]`,
  ACCEPT does it.
  Each row shows "also: <action>" when another action of the same context has the input.
- **Capture.** Replace and Add start a capture: "Press a key, mouse button, gamepad button
  or stick for <action>  (key:Escape / pad:guide cancels, N s)". The first **new** press
  becomes the binding (`rg_bind_capture`, `rg_capture_*` in `rg_input.h`):
  - a key down (not a repeat; keys SDL can't name are ignored), mouse buttons 1-5, any
    gamepad button;
  - a gamepad axis that moves past half deflection (`RG_CAPTURE_AXIS_HIGH`) after being at
    rest in that direction (`RG_CAPTURE_AXIS_LOW`, a quarter). The detector is seeded with
    the pads' state when the capture starts, so a trigger or stick already held must return
    first; each direction re-arms on its own. The result is `axis:<name>+` or `-`;
  - mouse motion is not captured here (too easy to trigger by accident); it has its own
    capture (below).
  Inputs held when the capture starts (the ACCEPT press itself) never send a new down
  event, so they aren't captured. **Cancel:** `key:Escape` or `pad:guide` (the detector's
  `cancel` list), or no input for `capture_ms` (5 s; `rg_menu_tick`). Both leave the
  bindings unchanged. Closing the overlay cancels too. Esc and Guide therefore can't be
  captured; they can still be written in the file.
- **Mouse motion** ("Capture mouse motion", an explicit row, never part of an ordinary
  capture). The detector (`rg_capture_begin_motion`, `rg_capture_mouse_motion`) sums the
  relative motion per axis from the start and takes `mouse:x+`/`x-`/`y+`/`y-` once one axis
  has moved `RG_CAPTURE_MOUSE_DIST` (300 px) net **and** at least twice as far as the other
  (a diagonal wobble doesn't count). Keys, mouse buttons and gamepad inputs are ignored
  meanwhile; Esc / Guide and the 5 s timeout cancel as usual. The result is not stored yet:
  the editor asks "Bind mouse:x+ to <action>?  accept = bind, back = discard", and every
  other command is ignored until one of the two. ACCEPT adds it (through the same path as
  Add: duplicates, conflicts, the device guard); BACK, or closing the overlay, drops it.
  The host feeds `SDL_EVENT_MOUSE_MOTION` to the detector only while a capture waits.
- **Result.** Replace swaps the binding in place; Add appends (the validator refuses a ninth
  binding with its message). A press the action already has changes nothing ("already
  has"). The list is stored with `rg_settings_set_text`, source MENU, so it's canonical and
  saved like any menu change.
- **Conflicts.** The context is the setting's category: game actions (`controls`) and menu
  actions (`controls_ui`). If another action in the same context already has the input,
  the binding is still added, to both, and the status line warns: "WARNING: Cancel / ...
  has it too (both fire)". `rg_menu_binding_conflicts(m, index, token, out, cap)` lists
  them. Across contexts nothing is reported (Return is both `pause` and `ui_accept` by
  default).
- **Remove** takes the selected binding out; a game action may end up unbound.
- **Device guard (menu controls).** Every `controls_ui` action (`ui_up/down/left/right`,
  `ui_accept`, `ui_back`, `ui_page_prev/next` and the overlay toggle `ui_overlay`) keeps at
  least one **keyboard** binding (`key:`) and at least one **gamepad** binding (`pad:` or
  `axis:`), so the overlay can always be opened and driven from the keyboard alone and from
  a gamepad alone. A Remove or Replace that would take away the last binding of either
  device is refused, nothing changes, and the status says why ("not removed: key:F1 is its
  last keyboard binding, and the menu must work from the keyboard alone and from a gamepad
  alone. Add another keyboard binding first (selected)."). The cursor moves to "Add a
  binding"; after a refused Replace that row becomes "Add <captured input> instead", and
  ACCEPT on it adds the input while keeping the old one (any other ACCEPT or BACK drops the
  offer). Mouse buttons and motion count for neither device. A list that already lacks a
  device (from a file) shows "WARNING: no gamepad binding; add one ..." in the editor;
  the remaining device's last binding is still protected, and no menu control can become
  unbound.
- **Reset:** "Reset to default" in the editor (one action), "Reset all bindings (game and
  menu) to defaults" on either controls page (every `input.bind.*`), and the page's
  "Reset this page to defaults" (bindings and tuning of that page).
- **Host side** (`host_sdl.c`). While the menu is capturing, key/mouse/gamepad down events
  and axis motion go only to the detector (no hotkeys, nothing reaches the game: the
  overlay already makes pad reads neutral). The menu commands of the pump in which a
  capture started or finished are dropped, and the UI navigation state still sees the
  pressed input, so the capturing press doesn't also act on the menu. Scripts are not
  affected: they bypass all live input.

## Device type and button prompts

`rg_pad_family_from_sdl_type` maps `SDL_GetGamepadType`:

| SDL type | `rg_pad_family` |
| --- | --- |
| `PS3`, `PS4`, `PS5` | `PLAYSTATION` |
| `XBOX360`, `XBOXONE`, `STEAM` (Steam Controller / Deck: Xbox-style labels) | `XBOX` |
| `NINTENDO_SWITCH_PRO`, `NINTENDO_SWITCH_JOYCON_LEFT/RIGHT/PAIR`, `GAMECUBE` | `NINTENDO` |
| `UNKNOWN`, `STANDARD`, anything newer | `GENERIC` |

`rg_host_active_pad_family(h)` is the family of the most recently used gamepad (slot 0 if
none was used yet); `NONE` without a gamepad, and always headless.

**`prompts.style`** (Controls page; `auto`, `playstation`, `xbox`, `nintendo`, `keyboard`;
default `auto`, Original `playstation`; live; not a gameplay option; rg-game swaps the
`gaiji2` button glyphs to the resolved style, docs/PROMPTS.md "Implementation"). `rg_prompt_style_resolve(setting,
scripted, active_kind, family, previous)`:

1. **scripted** (an input script is set, or the host is headless): `PLAYSTATION`, whatever
   the setting (even `--set prompts.style=xbox`) and the devices, so traces and frame
   hashes never depend on the machine;
2. a fixed setting wins;
3. `auto`: keyboard/mouse last used → `KEYBOARD`; a gamepad → its family (`GENERIC` →
   `XBOX`, as PROMPTS.md); nothing used yet → the previous style (initially
   `PLAYSTATION`).

`rg_host_prompt_style(h)` applies it with the attached settings and remembers the result.
`rg-host-demo` shows it in the title bar.

## Evaluation and the DS2 adapter

`rg_actions_values(map, snapshot, v)` gives every action a magnitude 0..32767; the
strongest binding wins:

| Source | Digital action (buttons, d-pad, UI) | Stick half axis (`move_*`, `camera_*`) |
| --- | --- | --- |
| key, mouse button, pad button | 32767 | 32767 (full deflection) |
| gamepad axis | 32767 at or above `threshold`, else 0 | the whole stick: round deadzone, rescaled, stretched onto the DS2's square range ("Stick range" below); with `input.stick_ds2_range` off (and the legacy map) that stick's deadzone per axis, rescaled |
| mouse motion | 32767 at or above `threshold`, else 0 | `pixels × mouse_sensitivity × 32767/20` (20 px in one field = full) |

All gamepads that feed a port are merged the same way. `rg_actions_to_pad` is the
adapter:

- **buttons:** the bit of every digital game action with a non-zero value;
- **each stick axis:** `(positive − negative)`, times that stick's sensitivity, clamped,
  negated if the axis is inverted, then `128 + v·128/32767` clamped to 0..255. This is the
  old `rg_input_eval` formula, so opposite keys still cancel to 0x80. With
  `input.stick_compensation` on, `rg_stick_compensate(v)` replaces the last step; with
  `walk` held, the two move axes are then clamped to the walk band (below);
- **pressure:** 0/255 from the buttons (`rg_pad_fill_pressure`). The game never enables
  pressure mode, so nothing reads it.

`rg_pad_ds2_report` then writes the 20-byte `scePadRead` buffer, unchanged (HOST.md "The
pad report"); `rg_actions_ds2_report` does both. That host-side buffer is labelled 0x79
(analog + pressure) for the tests; the bytes the game actually reads come from padman,
which reports the mode the game set: **0x73** (analog, locked) once the game has locked
it (Devices, "Analog mode is locked").

**Equivalence with the old map.** `rg_actions_from_input_map` turns an `rg_input_map`
into actions, binding for binding. `input.legacy_equivalence` checks that the two paths
give byte-identical `rg_pad`s for 40,000 random snapshots, with the default map and a
custom one. That covers edge values at the deadzone and threshold, short key arrays, and
0–2 gamepads. `rg-host-demo --config` still works this way (`rg_host_apply_input_map`).

## Walking and running

The leader's speed has three bands, not a continuum (`PlayerControlUpdateMaybe_1fc4a0`):
the move vector (after the game's own decode, rotated by the camera yaw and clamped to
length 1) stands still below 0.16, **walks** from 0.16 and **runs** from 0.9.

- **Keyboard movement runs by default.** A key gives full deflection: report bytes 0x00 /
  0xFF, which the game reads as -1 / +1. A diagonal (two keys) is clamped to length 1, so
  it runs as well. (`input.sensitivity_move` below 1 scales keys too.)
- **`walk` (default Left Shift)** clamps the two move axes to `[0x24, 0xDB]`
  (`RG_WALK_NEG`, `RG_WALK_POS`). With the game's decode those bytes read exactly -68/128
  and +68/128 = 0.53125, the nearest game value to the middle of the walk band (0.53).
  A diagonal reads 0.751, still a walk. Smaller stick deflections pass unchanged, so walk
  with a gamepad stick is "never faster than walking". The camera stick is not affected.
  (The bytes are asymmetric because the game's negative side starts one step later:
  `+49` vs `+50` below.)
- `walk` drives no PS2 input of its own, so it never reaches the game except through the
  move axes, and scripted runs don't see it.

## Stick dead zone (the game applies its own)

Every stick reader in the game (all twelve `PadGetAnalog*` getters, `PadAnyInput_183e80`)
decodes a report byte `v` as `d = v - 128`: `|d| < 50 -> 0`, `d > 0 -> (d - 49) * 128 / 78`,
`d < 0 -> (d + 50) * 128 / 78` (integer division), then `/ 128` for the float getters.
That is a fixed **~39% dead zone per axis** (square, not radial) applied by the game
after the report. `rg_game_stick_value` is this decode, for tests.

- The port's `input.deadzone_move` / `input.deadzone_camera` (default 25%) run **before**
  the report, inside the game's 39%. So the effective dead zone is the larger of the two,
  and a port dead zone below ~39% appears to do nothing. This is the original behaviour
  and stays the default.
- **`input.stick_compensation`** (off by default, off in the Original preset, flagged
  `[gameplay]`) pre-maps each axis past the game's dead zone: host value `v` (after the
  port dead zone, sensitivity and inversion) becomes `k = round(|v| * 78 / 32767)` (1..78)
  and the byte `128 + 49 + k` or `128 - 50 - k`; 0 stays 0x80 (`rg_stick_compensate`). The
  game then reads about `|v| / 32767` (within 2/128), so the port dead zone is the only
  one. It changes how small deflections act (slow walking, slow camera), so it is a
  gameplay option, not an enhancement. It is per axis (the game's dead zone is too);
  walk still lands on 0x24 / 0xDB.

## Stick range (DualShock 2 square vs a round modern stick)

Added 2026-10-18 for the play-test symptom "sometimes when turning the character walks
although the stick is fully deflected" (BRINGUP.md "User play-test, 2026-10-18").

- **Cause.** Modern gamepads (XInput, DualSense, Switch Pro via SDL) report a round range:
  at full tilt on a 45-degree diagonal each axis reads ~0.707 (23,170). The old adapter
  rescaled each axis on its own (25% dead zone) and wrote `128 + v*128/32767`, so a full
  diagonal became bytes (206, 206), which the game's decode (above) reads as 0.367 per axis,
  |mv| = 0.52: the **walk band** (run needs 0.9). Model (`out/play/stickmodel.py`): at full
  tilt the old path ran only within ~17 degrees of the four axes and walked everywhere in
  between, so a turn along the rim (or any diagonal relative to the camera) dropped to a walk.
  Port check (boot-save save2, `#!stick` bytes): (206, 206) -> A34 = 1, 1.2 units/tick (walk);
  (255, 255) and (255, 128) -> A34 = 2, 3.6 units/tick (run); with square bytes no reversal,
  90/180-degree turn or 3-field walk-band blip leaves the run state (only a stick through the
  centre gives the 2-field run stop, as on the PS2).
- **Retail.** The game logic is the same (the decode and the 0.16 / 0.9 bands are matched
  code; `tools/trace/stickprobe.py` injects stick bytes into retail on PCSX2 and they reach
  the pad struct at 0x4B2578.. as written). A DS2 stick reaches its corners (its output is
  close to square); on a round output the game could never run on a diagonal at all (full
  round diagonal = byte ~218 = 0.55 per axis = |mv| 0.78 < 0.9). PCSX2 compensates the same
  way: its DualShock 2 default `AxisScale = 1.33` (also in the user's own PCSX2.ini) maps a
  full round diagonal to ~(248, 248) = run.
- **Fix (`rg_stick_shape`, src/host/host_input.c):** for stick half-axis actions bound to a
  gamepad stick axis, the whole stick is evaluated: round dead zone (`input.deadzone_move` /
  `_camera`), the radius rescaled from [dead zone, 92%] to 0..1 (`RG_STICK_OUTER`: 92% tilt
  reads full, as a DS2 saturates before its gate; without it a 95% stick on an axis decoded
  to 0.89 and walked), then the circle stretched onto the square (divide by the cosine to the
  nearest axis). Full tilt reads 32767 on the dominant axis in every direction (corners at
  45 degrees, as a DS2), 90% tilt runs and 70% tilt walks in every direction
  (`input.stick_range`). Setting `input.stick_ds2_range` (default
  on, also in Original: it is how a DS2 behaves; off = the old per-axis path). The legacy
  `rg_input_map` path keeps the old evaluation (`input.legacy_equivalence`).
- Scripts and traces are unaffected (they carry stick bytes).

## Camera stick convention

Added 2026-10-18 for the play-test symptom "right-stick camera reversed".

- **Retail (default options, `+0x1A = 1`: both invert bits off):** the orbit camera (field
  modes 0 / 2 / 18 and the battle camera, which runs the follow-leader step) **swings right
  around the leader on stick right, so the view turns left**; stick up raises the eye, so
  the view **looks down**. First person (R3) turns the view **right** on stick right and
  looks down on up. Measured on retail (PCSX2, `stickprobe.py` from the battle state
  `v23990`, RX = 255: the scene slides right, i.e. the view turns left;
  `out/play/r3_cam.png`) and on the port (orbit: the mouse lane's measurement; first person:
  `out/play/fp/m.png`, the scene slides left). The port's chain (SDL `rightx+` -> action ->
  byte 255 -> native pad frame byte 4 -> pad struct +0x10) is the same as a DS2 and PCSX2
  (`InvertR = 0`), so **the port behaved exactly like retail: a convention mismatch, not a
  bug** (modern PC / console convention: right turns the view right, up looks up).
- **Fix:** setting `input.camera_convention` = `pc` (default) / `original` (Original
  preset). PC flips the right stick X **only while the orbit camera reads it** and the right
  stick Y while either camera (orbit or first person) reads it; menus, Insectron, Factory and
  the lock-on / target-follow cameras get the stick unchanged. The game's hint is the camera
  override's `rg_game_look_take(site)` call: `rg-game` passes the camera that ran in the
  last 4 fields to `rg_host_set_camera_view` (`RG_CAMVIEW_ORBIT` / `_FIRST_PERSON` /
  `_NONE`; `RG_CAMVIEW_LOG=1` prints changes), and `rg_actions_to_pad` applies the flip
  after `input.invert_camera_x/_y`, which keep working on top. Keyboard and mouse bindings on
  the camera actions follow the same convention. The game's own Options (camera X / Y
  reverse) still work as on the PS2. Live port-0 input only: script bytes are never changed,
  so runs, traces and fixtures are unaffected; the flip happens before the bytes are
  recorded, so a recorded live session replays identically.

## Tuning settings

| Id | Type | Default | Effect |
| --- | --- | --- | --- |
| `input.deadzone_move`, `input.deadzone_camera` | float 0..0.95 | 0.25 (8192) | per-stick deadzone, fraction of full deflection (inside the game's own ~39%, above) |
| `input.stick_compensation` | bool | off | **gameplay**: skip the game's dead zone (above); off in Original |
| `input.trigger_threshold` | float 0.05..0.95 | 0.35 (11468) | analog → digital (triggers on L2/R2, axes or mouse motion on buttons) |
| `input.sensitivity_move`, `input.sensitivity_camera` | float 0.25..4 | 1 | stick deflection multiplier (clamped) |
| `input.invert_move_x/_y`, `input.invert_camera_x/_y` | bool | off | per-axis inversion, on top of the camera convention (the game also has its own camera invert X/Y options) |
| `input.stick_ds2_range` | bool | on (Original: on) | round dead zone + DS2 square range ("Stick range") |
| `input.camera_convention` | pc / original | pc (Original: original) | PC: right turns the view right, up looks up ("Camera stick convention") |
| `input.mouse_sensitivity` | float 0.1..10 | 1 | mouse motion scale (motion bound to actions, e.g. `mouse:x+`) |
| `input.mouse_look` | bool | on (Original: off) | mouse camera ("Mouse camera implementation") |
| `input.mouse_yaw_scale`, `input.mouse_pitch_scale` | float 0.1..10 | 1 | mouse camera speed: 1.0 = 0.0015 rad (0.086°) per count |
| `input.mouse_invert_x`, `input.mouse_invert_y` | bool | off | mouse camera inversion (independent of the stick and the game's own options) |
| `input.vibration` | float 0..1 | 1 | **hidden, no effect in this game** (Rumble, below) |
| `input.players` | one / two | one | port policy, below |
| `input.min_press_fields` | int 0..8 | 2 | press latch length |

Fractions become raw units with `rg_actions_raw(f) = (int)(f·32767 + 0.5)`. None of them
is consulted under a script. Apart from `input.stick_compensation`, none of them is a
gameplay option.

## Devices: hot-plug, ports, switching

`rg_pad_roster` keeps the connected gamepads in connection order (slot 0 = oldest).
Unplugging closes the gap, and plugging in appends. The host keeps its `SDL_Gamepad`
array and the latch rows in the same slot order.

| `input.players` | Port 0 (player 1) | Port 1 (player 2) |
| --- | --- | --- |
| `one` (default) | keyboard + mouse + **every** gamepad | not connected |
| `two` | keyboard + mouse + gamepad slot 0 | gamepad slot 1, connected only while ≥ 2 pads |

**When `two` matters.** The story game is single-player, but the game services both
ports: `MainLoop_1c2c10` calls `PadUpdate_1843a0` for port 0 and port 1 every frame, the
shared menu cursor (`MenuGridCursorInput_28e170`) reads both, and the **Insectron versus
mode** uses port 1 for the second player: the controller-setup step
(`insmenu_InsectVsMenuStateCtrlSetStep_4eabb0`) checks analog mode on both pads, and
closing it calls `SetPad2Enabled_2882b0`; the battle then reads the pad of the player
whose turn it is (`insect_InsectCursorSetGetPad_511000`). While `IsPad2Enabled_2882c0`,
the pause and "analog required" checks also watch port 1. So set `input.players = two`
(and connect two gamepads) for Insectron versus play; `one` is the default for
everything else.

- **Switching devices mid-play** needs nothing in `one` mode: every device drives player 1
  all the time. The roster records the **most recently used** device (key or mouse-button
  down, gamepad button down, or a gamepad axis past the threshold).
  `rg_host_active_device(h, name, cap)` reports it, for button prompts later.
- **Rumble** goes to the most recently used gamepad (`one`) or the port's gamepad (`two`),
  scaled by `input.vibration`. It's re-sent after a settings change. **The US build never
  vibrates** (CONTROLS-AUDIT.md section 7: the driver maps the motors, but every write to
  the motor bytes is a zero-write and the per-VBlank vibration tick is never installed),
  so this path is never exercised by the game. `input.vibration` is kept for the hook and
  is hidden from the menu. Rumble on hits or explosions would be a **new optional
  feature** driven from game events on the host side, off in Original.
- **Port 1** is reported to padman as connected exactly when
  `rg_host_port_connected(h, 1)`: a live (unscripted, windowed) two-player setup with at
  least two pads. Before, it was "at least two gamepads". The runtime now asks the host.
  `one` is the default; `two` is for the Insectron versus mode (above).
- **Analog mode is locked.** The game puts each pad in analog mode and locks it
  (`PadUpdateConnection_184a50`: `scePadSetMainMode(1, 3)`). If `PadIsAnalogMode_184960`
  (state STABLE or FINDCTP1 and mode id 7) is false, `GameFrameUpdate_27c4c0` raises the
  "analog required" pause (reason 4, port 1: 5). The port's report never switches modes
  (there is no Analog button to bind), and the runtime runs padman with
  `keep_analog_lock` (`rg_runtime_config.pad_power_cycle = 0`, the default): once the
  game has locked a port it stays mode 0x73, locked, across an unplug / replug (a host
  device change) and a software request for digital. The boot path is unchanged (a pad
  powers up digital, 0x41, and the game locks it), so traces still match hardware. A real
  disconnect still shows the game's own pause while the port is gone. `padmc.pad_analog_lock`
  checks it (`pad_power_cycle = 1` restores the hardware power cycle).
- An unplug in `two` mode moves the remaining pad to player 1 (slot 0). padman sees port 1
  disconnect, which the game handles like a real unplug (PADMC.md).

## Opening the settings overlay with a gamepad

Added 2026-10-26 (P6 wave 1, "p6 pad"). Guide and the touchpad (`ui_overlay`) are not
reliable on their own: the Xbox Game Bar takes Guide on Windows, Steam takes it (Steam
Deck, Steam Input), and Xbox pads have no touchpad. So a **held chord** opens and closes
the overlay too: by default **Back + Start held together for 1 s** (Select + Start on a
DualShock layout, View + Menu on Xbox, Share/Create + Options on PS4/PS5, Minus + Plus on
Switch). The keyboard route (F1) is unchanged.

| Id | Values (default; Original) | Flags |
| --- | --- | --- |
| `input.overlay_chord` | binding list of 0-4 `pad:` buttons, held together (`pad:back, pad:start`; the same) | Menu controls page; live; empty = off. Not a gameplay option: live input only |
| `input.overlay_chord_hold` | 0.5-3 s, step 0.25 (1.0; 1.0) | Menu controls page; live |

Original keeps the chord: it is an access feature on live input, like the `ui_*`
bindings, and scripted / headless runs never evaluate it.

**The game never sees the chord** (`rg_chord`, `src/host/host_input.c`; per pad slot, so
Back on one pad and Start on another are two ordinary presses):

| What the player does | What the game's pad report shows |
| --- | --- |
| both buttons in the same field, held 1 s | nothing; the overlay toggles at 1 s; nothing until both are up again |
| one button, the other within 100 ms (`RG_CHORD_GRACE_MS`), held | nothing |
| the chord let go before 1 s | nothing (no toggle) |
| a lone tap shorter than 100 ms | the tap, right after the release, held `max(input.min_press_fields, 2)` fields |
| a lone press held longer | the press from 100 ms on, until released (so Start / Select reach the game **100 ms late**, live input only) |
| a lone press held past 100 ms, then the rest of the chord | the first button until the chord is complete, then released; the overlay still toggles |
| any other button, at any time | unchanged, no delay |

The 100 ms grace is what keeps a slightly uneven chord from leaking its first button
(Select alone opens the map; Start alone pauses). The game has no use for Select + Start
pressed together, so nothing is lost by holding the pair back.

- **Rebinding.** The chord row is an ordinary binding editor (capture a gamepad button to
  add it, Remove, Reset). Keys, axes, mouse input or more than 4 buttons are refused by its
  validator (`rg_chord_validate`: "a chord takes gamepad buttons only"). It is not a menu
  control, so the device guard does not apply and removing every button turns it off. With
  the keyboard alone you can remove buttons or reset it, not add gamepad buttons.
- **One-button chord.** A single button (for example a Steam Deck back grip,
  `pad:paddle1` = R4 (SDL's names: `paddle1` right upper, `paddle2` left upper, `paddle3`
  right lower, `paddle4` left lower), or `pad:misc1`) opens the overlay when held for the hold time.
  On a button the game uses, a press let go before the hold time reaches the game as a tap
  after the release; holding it in the game is then impossible.
- **Where.** `rg_chord_update` runs once per pump in `overlay_input` (host_sdl.c) on each
  pad's latched state; `rg_chord_filter` is applied to that pad's snapshot in
  `live_snapshot` (the game's reads, after the press latch) and in `overlay_input` (the
  menu actions). It doesn't fire while a binding capture waits (the press is the capture).
  The game's reads in a field all see the same filtered state.
- **Determinism.** `rg_host_read_pad` returns the script's pad before any live source,
  and headless hosts don't pump, so traces, fixtures and the run hash can't see the chord.

## Prompts in the settings overlay

The overlay's own hint lines name the inputs of the device in use, from the bindings
(rebinding shows at once):

- **Style.** `prompts.style` resolved like the game's glyphs (`auto` = the device used
  last; a fixed style wins), except that the overlay ignores the "scripted" rule: it is
  host text, never part of a game frame. `overlay_input` resolves it each pump while the
  overlay is open.
- **Labels** (`rg_prompt_binding_label`, `rg_prompt_action_label`): the action's first key
  (keyboard style, short names: Enter, Esc, PgUp, Backspace) or its first gamepad
  button / axis (pad styles); positional, as the bindings:

| SDL button | PlayStation | Xbox | Nintendo |
| --- | --- | --- | --- |
| south / east / west / north | Cross / Circle / Square / Triangle | A / B / X / Y | B / A / Y / X |
| back / start | Select / Start (PS4: Share / Options, PS5: Create / Options) | View / Menu (Xbox 360: Back / Start) | Minus / Plus |
| guide | PS button | Xbox button (Steam: Steam button) | Home |
| shoulders, triggers, stick clicks | L1 R1, L2 R2, L3 R3 | LB RB, LT RT, LS RS | L R, ZL ZR, L-stick R-stick |
| paddles | P1-P4 | P1-P4 (Steam Deck: R4 L4 R5 L5) | P1-P4 |

  Model names (Share, Create, Back, Steam, R4) are used only when the pad in use is that
  model and its family is the style shown.
- **Tags.** The menu's hint templates (`rg_menu.c`) use the port's own prompt tags
  `[up] [down] [left] [right] [accept] [back] [prev] [next] [toggle] [start] [select]
  [dpad] [ls] [rs] [cancel]`; `rg_menu_expand` replaces them with the labels the host set
  (`rg_menu_set_prompt`, filled by `rg_menu_prompts_from_input`), or generic words when
  none is set (tests, `rg-host-demo --menu`). Other bracketed text (the game's `[r1]`,
  markers like `[restart]`) is left alone. `[toggle]` is the overlay binding plus the
  chord on a gamepad ("Xbox button or hold View+Menu 1 s"), F1 on the keyboard; `[cancel]`
  is the capture's cancel inputs ("Esc / Xbox button").
- Lines that use them: the page hint ("LB / RB pages  Up / Down select  Left / Right
  change  A edits  B closes  (open / close: ...)"), the binding editor's hint and capture
  prompt, the motion-capture confirm, the text-entry gamepad line, the display-trial
  prompt.
- **Game text is unaffected.** The tags are the overlay's; the game font's port-only tags
  (docs/PROMPTS.md "Missing glyphs") are still not needed: no port text is drawn with the
  game font. The message-word remap (START / SELECT in the game's text) was scoped with
  `tools/prompts/msgscan.py`: the English `.txt` message files never name START or SELECT
  (only a debug memory-card viewer string); the only controller words are "DUALSHOCK(R)2
  analog controller" (the not-connected message, the Insectron versus setup) and "the left
  and right directional buttons" (Insectron versus setup). So there is nothing to remap for
  START / SELECT.

**Code (chord and prompts).** `src/host/rg_input.h`, `host_input.c`: `rg_chord_*`, the two
settings (in `rg_actions_register_settings`' table), `rg_prompt_*_label`,
`rg_menu_prompts_from_input`. `src/settings/rg_menu.[ch]`: the prompt table, tags,
`rg_menu_expand`, the hint templates; the device guard now covers `input.bind.*` only.
`src/host/host_sdl.c`: `rg_host` fields `chord`, `menu_prompt_prev`; `apply_settings`,
`pad_removed`, `live_snapshot` (filter), `overlay_input` (update, toggle, prompts).
`tests/settings/chord_tests.c` (`rg-chord-tests`); `settings_tests.c` `menu_keyboard`: the
chord row is edited by Remove from the keyboard. `tools/settings_census.py` prints BINDING
defaults / Original values; `tools/prompts/msgscan.py` (message-word scan);
`tools/playtest/vcrun_build.py` (cmake --build / ctest in the MSVC x86 environment).

## UI navigation

`rg_ui_nav_update(nav, values, now_ms, out)` turns the `ui_*` action values into commands:
a press edge fires at once, and directions and pages repeat after 400 ms, then every 90 ms.
Accept, back and the overlay toggle never repeat. The host feeds it every pump from **all**
devices at once (focused keyboard + every gamepad), so the overlay works with keyboard
alone or gamepad alone (docs/SETTINGS.md "Menu API").

## Mouse camera (design)

Implemented 2026-10-17: see "Mouse camera implementation" below for what was built and
where it departs from this design.

Mouse motion can already be bound to the `camera_*` half axes, but that goes through the
DS2 stick: clamped to full deflection per field, through the game's dead zone, and at the
stick's fixed turn rate. A real mouse camera adds yaw/pitch directly. The audit
(CONTROLS-AUDIT.md section 6) sets the constraints:

- **Camera yaw is game state.** `PlayerControlUpdateMaybe_1fc4a0` rotates the move stick by
  the camera yaw, and first-person yaw turns the character. A mouse delta applied at
  presentation time would change logic with the frame rate, which the P6 gate forbids.
- So mouse deltas are **quantised per tick**, **latched at PadUpdate**, and **recorded in
  input scripts** exactly like pad input.

Host side (this layer):

1. With `input.mouse_look` on, the game focused and the overlay closed, the mouse is in
   relative mode. Raw counts accumulate between pumps; at each `rg_host_pump` (field
   boundary) the accumulator, times `input.mouse_yaw_scale` / `input.mouse_pitch_scale`
   and the invert settings, moves into a per-port **pending look** value, rounded to
   integer **look units** (Q12: 1/4096 rad), with the rounding remainder carried to the
   next field so no motion is lost or invented.
2. **Latch.** When the game calls `PadUpdate_1843a0` for port 0 from `MainLoop_1c2c10`
   (the once-per-frame call; extra edge-consuming calls do not latch again), the pending
   value moves into a port-side `look` record `{int32 yaw, int32 pitch}` next to the pad
   (not inside the game's 0x264-byte pad struct) and pending resets to 0. Only port 0 has
   a look channel; Insectron and Factory cameras keep using the stick path.
3. **Determinism.** The record is integers, so a run is a pure function of the latched
   values. The scales and inversion are applied before quantisation and are baked into the
   record, so a replay doesn't depend on the replaying machine's settings.

Game side (overrides, owned by the game-overrides work, not this layer): consume the
record once per tick at the camera choke points (`CameraObjApplyInputMaybe_1619e0` or
`CameraObjOrbitControlMaybe_161260` for the orbit modes, `CameraFirstPersonUpdate_307f00`;
lock-on and target-follow stay on the stick path at first), and **discard** it when the
camera did not run that tick (pause, menus, events), so nothing bursts on resume. Units:
yaw is radians (the stick's full rate is 0.075 rad/tick); first-person pitch is radians;
orbit "pitch" is an eye-height offset in world units with a 55-unit range, so the override
converts pitch look units with one fixed constant (proposal: 1 rad of look = 20 world
units), part of the override and never a setting.

### Input-script extension: the look channel

Scripts stay `tools/trace/input.py` compatible: the look channel lives in lines that
`input.py` reads as **comments**, so the button table and its blob stay byte-identical.

```text
# buttons, as today: first last BUTTON[+BUTTON...]  (game VBlank counter)
300 301 CROSS
#!look 1 0                      # channel version (required before any look line)
#!look 412 -96 0                # vbl yaw pitch: one latched delta
#!look 420 431 8 -4             # first last yaw pitch: the same delta at every latch in range
```

- **Key:** the game VBlank counter (`[0x004810C4]`), like the buttons. A look line applies
  to the latch that happens **at** that VBlank (a range: every latch inside it). A latch
  at a VBlank with no look line latches 0. Ticks are every second VBlank in the field, so
  a recorder writes one single-VBlank line per non-zero latch, at the VBlank it latched
  on; replay then reproduces the record exactly.
- **Values:** signed integers in look units (Q12 radians, after scale, inversion and
  quantisation); `yaw` positive turns right, `pitch` positive looks up. Overlapping lines
  add, like buttons OR. Values outside ±32767 per latch are an error.
- **Bypass:** with a script, the look record comes **only** from the script (live mouse
  ignored), as port 0 buttons do. No `#!look` line = zero look every tick, so every
  existing script keeps its meaning.
- **Parser:** `host_script.c` skips the lines today (they are comments). Implementing the
  channel means parsing `#!look` into a second table (int16 pairs, the same length as the
  button table) and a `rg_input_script_look(s, vbl, &yaw, &pitch)` accessor;
  `rg_input_script_blob` stays unchanged, and `input.py` keeps ignoring the lines (or
  learns them later for PCSX2 replays through the same override).

Settings (all non-gameplay, off or neutral in Original, added with the implementation):
`input.mouse_look` (off), `input.mouse_yaw_scale`, `input.mouse_pitch_scale`,
`input.mouse_invert_y`, "mouse holds camera height" (skip the orbit height ease-back
while mouse look is active).

## Scripted sticks (`#!stick`, route inputs)

Field walking needs the left stick (the game has no d-pad movement:
`PadGetAnalogLXNorm_183af0` reads only the stick bytes), so input scripts have a stick
channel, added 2026-10-18 for the regression route (docs/TEST-FIXTURES.md "Route").
Like `#!look`, the lines are comments to `tools/trace/input.py`, so the button table and
the PINE blob are unchanged. PCSX2 runs get the sticks since 2026-10-18 (`tools/trace/input.py`:
a script with stick lines installs a longer trampoline that stores the scripted bytes over the
scePadRead frame's stick bytes; at most 1,014 VBlanks from the first stick line per script;
scripts without stick lines keep the original trampoline, so goldens are unchanged).
`tools/trace/stickprobe.py` runs such a script on retail from a PCSX2 save state ("Retail
stick probe" in tools/trace/README.md).

```text
#!stick 1 0                      # channel version (required before any stick line)
#!stick 28800 29180 128 0        # FIRST LAST LX LY: left stick held up for the range
#!stick 30420 30460 255 255 128 0  # ... RX RY: right stick too (centred when omitted)
```

- **Key:** the same VBlank key as the buttons (inclusive range). In a plain rg-game run
  that is the kernel VBlank count, i.e. the **field number** (`--fields`, `--shot`),
  not the game counter: see docs/RUNTIME.md "Pad" (the `cfg.game_vblank` TODO; traced
  runs key on the game counter + 1).
- **Values:** stick bytes 0..255 (`0x80` centre, 0 = left / up), exactly what the DS2
  report carries. The game's dead zone is ±49 around 0x80 and its run band needs
  |stick| >= 0.9 after rescaling (docs/CONTROLS-AUDIT.md), so diagonals need corner
  values (255, 0), not 127·(sin, cos), to run.
- **Overlap:** a later line overrides an earlier one on the VBlanks they share. Outside
  every line the sticks are centred.
- Code: `src/host/host_script.c` (parse, table `rg_input_script.stick`, 4 bytes per
  VBlank), applied in `rg_input_script_pad`.

## Mouse camera implementation

Build tree `build/mouse-i686`; scratch, scripts, runs and screenshots in `out/mouse/` (game
imagery, never committed).

### Mechanism, and why not the stick

Mouse motion is **not** fed into the right-stick bytes of the pad report. That path exists
already (`mouse:x+` bindings on `camera_*`) and is what this replaces: a stick byte is
clamped at full deflection (a fast flick saturates at 0.075 rad/tick), passes the game's
~39% per-axis dead zone (slow motion is lost or snaps to the first live step), and is
quantised to 78 steps per direction; sub-step accumulation could hide the dead zone but not
the clamp or the fixed turn rate. Instead the delta is applied in radians at the narrowest
point that is still logic-tick quantised, as the design above says:

1. **Host** (`host_sdl.c`, pure part in `host_input.c`): while captured, each pump's
   relative motion goes through `rg_look_acc_motion`: `units = counts × scale ×
   0.0015 rad × 4096`, inverted if set, rounded to whole look units (Q12 rad) with the
   remainder carried, so slow motion is never lost and nothing saturates (a latch is
   clamped only at ±32767 units = 8 rad). Pending units wait for the next latch.
2. **Latch** (new override `overrides/src/main/sys/MainLoop_1c2c10.c`): two added calls to
   `rg_game_look_latch()` (in `src/game/rg_game_main.c`), right before the main loop's
   two port-0 `PadUpdate_1843a0` calls (mode start and the per-frame one). It asks
   `rg_host_look_latch(host, vbl)` for the delta and makes it the frame's record,
   **replacing** the previous one: a record no camera took is dropped, so motion during a
   pause, a menu or an event never bursts out later. Other `PadUpdate` callers (movie,
   pause, loading loops) don't latch.
3. **Consume** (new overrides): `rg_game_look_take()` returns the record once and 0 when
   there is none, so without motion (and always in Original) the generated code path runs
   unchanged.
   - `CameraObjApplyInputMaybe_1619e0.c` (orbit: modes 0 follow leader, 2 preset, 18
     zoom, and mode 31 with the battle "camera" option off, which calls the follow-leader
     step): `s.a −= yaw / 4096` (radians, the same quantity the stick's `0.075 × RX`
     gives; `s.a > 0` swings the camera right around the leader so the *view* turns left,
     measured below, hence mouse right = view right subtracts), skipped while the game locks yaw input (`+0x214 & 2`, or the `+0x250` input
     lock timer); `s.b += pitch × (−20 / 4096)` world units of eye height (1 rad of look
     = 20 units; mouse up lowers the eye = looks up; the orbit keeps its own [−15, 40]
     clamp and its ease-back above 20).
   - `CameraFirstPersonUpdate_307f00.cpp` (mode 1): `yaw −= yaw_units / 4096`,
     `pitch −= pitch_units / 4096` (radians), same clamp, wrap and character turn as the
     stick. Signs derived from the code (eye = target + 5·(sin yaw·cos pitch, sin pitch,
     cos yaw·cos pitch), the same `RotY` convention as the orbit), **not run-verified**:
     the golden run never enters first person.
   - Lock-target (31 with the option on), target-follow (32), Insectron (15) and Factory
     (16) cameras stay on the stick path (bind the mouse to `camera_*` there).
4. **Capture policy** (`look_update_capture`): relative mouse mode only while
   `input.mouse_look` is on, a camera asked for look within the last 30 fields
   (`rg_host_set_look_active`, set by `rg-game` before every field from the last
   `rg_game_look_take` call), the window is focused, the overlay is closed and no script
   drives the run. So the cursor is free on the title, in movies, menus and event scenes,
   after Alt+Tab and with F1 open; leaving capture drops pending motion. While captured,
   `mouse:x±/y±` bindings receive no motion (no double turn).

**Determinism.** The record is integers latched at a game VBlank, so a run is a pure
function of `(vbl, yaw, pitch)` triples. Under a script the record comes only from the
script's `#!look` lines (design above, now parsed by `host_script.c` into
`rg_input_script.look`, accessor `rg_input_script_look`); scripts without them latch 0, and
`input.py`'s table and blob are byte-identical with or without look lines
(`input.look_script`). `rg-game --look-record FILE` writes every non-zero latch as
`#!look VBL YAW PITCH` lines (after a `#!look 1 0` header), ready to append to the
button script.

**Scripted mouse input (verification).** `rg-game --mouse-motion FIRST-LAST:DX:DY`
(repeatable) feeds DX, DY counts of relative motion into the host before each field in
FIRST..LAST, through the same settings and accumulator as live motion, also in scripted
and headless runs (like `--prompt-style`). `RG_LOOK_LOG=1` prints a `LOOK field=… vbl=…
site=0|1 yaw=… pitch=…` line per consumed record.

### Settings

| Id | Values (default; Original) | Flags |
| --- | --- | --- |
| `input.mouse_look` | bool (on; **off**) | live; Controls page; not a gameplay option (live input, like any binding) |
| `input.mouse_yaw_scale`, `input.mouse_pitch_scale` | 0.1..10 (1.0 = 0.0015 rad = 0.086° per count) | live |
| `input.mouse_invert_x`, `input.mouse_invert_y` | bool (off) | live; independent of the stick inversion and the game's own camera options |

"Mouse holds camera height" (design) is not implemented: the orbit only eases back when
the eye is above 20 units, so mouse pitch inside [−15, 20] already holds.

### Code

| File | What |
| --- | --- |
| `src/host/host.h` | `rg_look`, `RG_LOOK_MAX`; `rg_input_script.look` + `rg_input_script_look`; `rg_host_look_latch`, `rg_host_look_inject`, `rg_host_set_look_active`, `rg_host_look_captured` |
| `src/host/rg_input.h`, `host_input.c` | `rg_look_acc` (init / from_settings / motion / take / reset, pure); the five settings |
| `src/host/host_script.c` | the `#!look` channel (version line, single and range lines, sums checked, errors with `file:line`) |
| `src/host/host_sdl.c` | accumulation at the end of each pump, the capture policy, the latch (script + injected) |
| `src/game/rg_game_main.c` | `rg_game_look_latch` / `rg_game_look_take` (C entry points for the overrides), `look_apply()` before every field, `--mouse-motion`, `--look-record`, `RG_LOOK_LOG` |
| `overrides/src/main/sys/MainLoop_1c2c10.c` (new) | the two latch calls |
| `overrides/src/main/camera/CameraObjApplyInputMaybe_1619e0.c` (new) | orbit yaw / eye height |
| `overrides/src/main/camera/CameraFirstPersonUpdate_307f00.cpp` (new) | first-person yaw / pitch |
| `tests/settings/mouse_look_tests.c` (new), `tests/settings/CMakeLists.txt` | `rg-mouse-look-tests`, label `input` |

`tools/ingest.py --check`: 0 problems (145 overrides). No `game/`, `tools/`, `src/gpu` or
`src/ps2` file changed.

### Verification

Golden input (`tools/trace/goldens/newgame_battle.input.txt`), headless, `RG_GPU=hw`,
`RG_GS_DUMP` frames; scripts `out/mouse/scripts/` (`build.cmd`, `run.sh NAME EXE FIELDS
[args]`, `INPUT=` for another script; `sheet.py`), runs `out/mouse/runs/`. "Base" =
`out/mouse/base/rg-game.exe`, built in `build/mouse-i686` before any edit; "final" =
`out/mouse/final-rg-game.exe`.

**Where the camera reads look in the golden run.** A logging-breakpoint run of the base
exe (`RG_BREAK` on the four camera input functions, `runs/base-diag`) finds the orbit
(`CameraObjApplyInputMaybe_1619e0`) at game VBlanks 2227, 3103-3105, 7291-7343,
10967-11047, 20097-20111, **22863-24413** and 24533-24653, and never first person,
lock-target or target-follow. Fields 8,000-16,000 are event scenes (scripted cameras):
the orbit only runs for ~40 ticks during two fades, so mouse motion there correctly
changes nothing visible (`runs/mm-f2`: 68 records taken, only during the fades). The battle
in the run (game mode 7) uses the orbit from field ~22,900 (battle mode 31 with the
camera option off calls the follow-leader step) until the game is paused at ~24,450; the
rest of the run (to 27,000) is the PAUSE screen.

| Check | Result |
| --- | --- |
| **Original identical**: final exe `--preset original --mouse-motion 1-27000:20:10` (motion every field, setting off) vs base `--preset original`, `RG_GS_DUMP_FIELDS` 1500, 8000, 9000, 10500, 12000, 14000, 16000, 20000, 23000, 24500, 25500, 26500 | all 36 dump files (display, local memory, GS regs + CLUT) byte-identical, the 54 `STATUS` lines identical (`runs/final-orig` vs `runs/base-orig`) |
| the same with the first build (pre sign fix), `runs/new-orig` | all 36 dump files (display, local memory, GS regs + CLUT) byte-identical, the 54 `STATUS` lines identical |
| **battle yaw**: `--set input.mouse_look=on --mouse-motion 23001-23010:20:0` (5 ticks x ~245 units = 0.3 rad) | f23000 identical to base; at f23012 the background has moved **46 px left** (best horizontal match of rows 30-110 against base): the view turned right. Before the sign fix the same test moved it 47 px right |
| **battle pitch**: mouse up (`0:-15`) then down (`0:15`) | up: the eye drops and the view looks up at the sky; down: the eye rises and looks down on the party (`05-battle-pitch-sheet.png`) |
| **record / replay**: `runs/mm-byaw` (yaw 22950-24400, `--look-record`) vs `runs/replay-byaw` (golden + the 725 recorded `#!look` lines as `--input`, `--preset original`, no motion) | all 24 dump files byte-identical, the 725 `LOOK` lines identical: a script reproduces mouse play exactly, independent of the replaying machine's settings |
| **no effect while paused**: motion over fields 24,800-26,600 (`runs/mm-yaw`, `mm-pitch`) | 900 non-zero latches, **0 taken**, f25500/f26500 identical to base, STATUS identical |
| logic flow with mouse look | the `STATUS` lines (vbl, overlay, modes) are identical to base in every mouse run |

Screenshots (`out/mouse/shots/`, left = Original, right = mouse): `01-battle-yaw-f23012`,
`04-battle-yaw-f23262` (60 more fields of yaw), `02-battle-lookup-f23700`,
`03-battle-lookdown-f23950`, `05-battle-pitch-sheet` (top Original, bottom mouse, f23100,
23300 look up, 23700, 23900 look down); single frames `mouse-fNNNNN.png` /
`orig-fNNNNN.png`.

**Tests**: `ctest -L "settings|host|input"` in `build/mouse-i686`: 87/87
(`gpu.gfx.game_replay` skipped as before), including the five new `input.look_*`.

### Known issues

- Lock-target (battle camera option on), target-follow, Insectron and Factory cameras are
  stick-only; first person is implemented but not run-verified (not in the golden run).
- Orbit yaw goes through the orbit's own close-range factor (`min_dist / dist`, faster
  when the camera is pushed in against a wall), exactly like the stick.
- The capture policy is untested with a real mouse and window (headless never captures);
  Esc still quits while captured (the existing hotkey), F1 or Alt+Tab release the cursor.
- A movie or loading loop shorter than 30 fields keeps the mouse captured; motion in it
  is latched after it ends (at most ~0.5 s of motion, never more).
- `input.py` (PCSX2 replays) ignores `#!look` lines: a mouse recording replays on the port
  only.

### Checkpoint (newest first)

- 2026-10-17: done. Original byte-identical to the base exe at 12 fields with motion
  injected; battle yaw / pitch, record-replay and pause checks above; orbit yaw sign
  fixed after the first direction measurement; `ctest -L "settings|host|input"` 87/87.
- 2026-10-17: code, settings, overrides and `rg-mouse-look-tests` in; `ctest -L
  "settings|host|input"` 87/87 in `build/mouse-i686`.
- 2026-10-17: started (`build/mouse-i686`, configured like `build/render-i686`); baseline
  exe saved before any edit as `out/mouse/base/rg-game.exe` (+ `.map`).

## Host API additions (host.h)

| Function | What |
| --- | --- |
| `rg_host_attach_settings(h, s, save_path)` | Applies display, volume, screenshot dir and input settings now and on every change; owns the overlay |
| `rg_host_config_from_settings(&hc, s)` / `rg_host_settings_from_config(s, &hc)` | Settings → host config, and program flags → overrides |
| `rg_host_actions(h)` | The live action map (editable) |
| `rg_host_apply_input_map(h)` | Legacy `rg_input_map` → actions |
| `rg_host_port_connected(h, port)` | The port policy above |
| `rg_host_active_device(h, name, cap)` | Most recently used device |
| `rg_host_active_pad_family(h)`, `rg_host_prompt_style(h)` | Gamepad family and prompt style (above) |
| `rg_host_capture(h)` | The host's rebinding detector |
| `rg_host_menu_script(h, script)` | Drives the overlay from code (`rg-host-demo --menu`) |
| `rg_host_overlay_open(h)`, `rg_host_set_overlay(h, open)` | Overlay state |
| `rg_host_set_vsync`, `rg_host_set_window_size`, `rg_host_set_volume`, `rg_host_volume` | Live display/audio changes |
| `rg_host_request_window_shot(h, path)` | PNG of the next presented window, overlay included |
| `rg_host_look_latch(h, vbl, &look)`, `rg_host_look_inject(h, dx, dy)`, `rg_host_set_look_active(h, on)`, `rg_host_look_captured(h)` | Mouse camera ("Mouse camera implementation") |

## Tests (`ctest -L input`)

| Test | Checks |
| --- | --- |
| `input.binding_text` | Every binding kind parses to the right code/direction; canonical format and re-parse; duplicates and empties; 8 error cases; every default list round-trips; action id lookup and targets |
| `input.default_layout` | Every default key and gamepad button → its bit; UI-only keys/buttons → no game bit; WASD/IJKL/stick extremes; opposite keys cancel; trigger threshold at exactly `raw(0.35)` − 1 / + 0 |
| `input.ds2_report` | Exact 20 bytes for keyboard + gamepad together (Cross + R2, sticks, pressure order), the game's decode, 100 repeats identical |
| `input.multi_binding` | Six bindings on one action, each alone; a key on two actions fires both; rebinding replaces the default; strongest analog binding wins; 8 fit, 9 are refused |
| `input.legacy_equivalence` | 2 × 20,000 random snapshots: actions == the old `rg_input_eval`, byte for byte |
| `input.tuning` | Exact deadzone rescale (20000 → 189), per-stick sensitivity (147 → 167, clamp), per-stick deadzone, per-axis inversion, threshold edge, every tuning setting reaching the map |
| `input.mouse` | Motion → camera (exact value, sensitivity, clamp), buttons incl. x1, motion on a digital action against the threshold |
| `input.hotplug` | Roster order, re-add, gap closing, full roster; port slots and connection in both modes; rumble follows the active pad; reports through the roster in both modes; unplug moves player 2 to player 1, and re-plug restores it; activity detection |
| `input.latch` | A sub-field tap is seen for exactly 2 fields, the same within a field; held keys; latch 0 = off; re-press extends; mouse and pad latches; slot removal |
| `input.ui_nav` | Edge, 400 ms delay, 90 ms repeat, release; accept/toggle don't repeat; game actions ignored |
| `input.settings_bindings` | Bindings from INI text (normalised), a bad one → default with the line, `F10`/`misc1`; the registry's defaults rebuild `rg_actions_default` exactly |
| `input.action_aliases` | Every pre-audit id maps to its new action; old ids load from INI (no warnings) and `--set`; the file is written with new ids only; inferred labels carry `?`; an alias can't shadow a real id |
| `input.walk` | The game decode (dead zone edges, ±128), walk bytes decode to ±68; all 8 keyboard directions run (band 2) and with walk land in the walk band at 0x24/0xDB; walk alone moves nothing and doesn't limit the camera; a gamepad stick is limited, a small one unchanged; rebinding |
| `input.stick_compensation` | `rg_stick_compensate` endpoints and first step; monotonic over all 65,535 values, never in the game dead zone, within 2/128 of linear; off: a 30% stick is inside the game dead zone, on: it moves; keyboard and walk unchanged; the setting is `[gameplay]`, off by default and in Original; `input.vibration` hidden and labelled |
| `input.script_bypass` | Headless host + attached settings + script: 400 VBlanks of port 0 == the script, port 1 neutral, port 1 not connected, identical hashes in two hosts; no script → neutral |
| `input.capture` | The detector alone: idle ignores input; unknown/unnamed keys ignored; first press wins; `key:comma`, `key:Keypad 8`, `mouse:x1`, `pad:leftstick`; mouse buttons 0/6 and out-of-range buttons ignored; Esc and Guide cancel; axis thresholds in both directions; an axis held at begin must return to rest (per pad, per direction); the text parses back to the same binding; the cancel hint |
| `input.capture_motion` | The motion detector: an ordinary capture never takes motion; net sums (299 waits, back-and-forth, exactly 300 binds); the 2:1 dominance on a diagonal; sums restart per capture; all four directions; keys, buttons, axes and NaN ignored; Esc and Guide cancel; the text parses back |
| `input.menu_mouse_capture_keyboard` / `_gamepad` | One device only, through the menu: "Capture mouse motion" starts a motion capture (the host detector in motion mode, the 300 px prompt); presses and small motion don't bind; the confirm step (nothing stored, other commands ignored); BACK discards, ACCEPT adds and the motion drives the action; an existing motion → "already has"; Esc/Guide cancel; the 5 s timeout; closing the overlay drops a pending confirm |
| `input.pad_family` | Every `SDL_GamepadType` (and out-of-range values) → family, names; `SDL_GAMEPAD_TYPE_COUNT` pinned so a new SDL type is noticed; a headless host reports `NONE` |
| `input.prompt_style` | Scripted → PlayStation for every setting × device × family × previous; fixed settings; `auto` per device and family; no device keeps the previous style; the setting (enum names, category, planned, not gameplay, Original = playstation, file); headless and scripted hosts report PlayStation for every setting, also with `--set prompts.style=xbox` |
| `input.look_quantise` | `rg_look_acc`: off drops motion; 100 counts = 614 units then 615 (remainder carried); up = pitch +, right = yaw +; scales and inversion; 10,000 motions of 0.05 counts = 3072 units in total with >1000 non-zero takes (no dead band); back-and-forth nets 0; 20,000 random motions sum to the exact total within one unit; a flick clamps at �32767 and the excess is dropped; NaN/inf ignored; reset |
| `input.look_settings` | the five ids, not gameplay / planned / hidden; defaults (on, 1, 1, off, off); Original = off and `matches_preset`; from_settings keeps pending and remainder |
| `input.look_script` | `#!look` lines leave the button table and the PINE blob byte-identical; values, ranges, overlapping lines add; no channel = 0; nine error cases (no / bad / repeated version, range, sum, integers, first > last, too many values, beyond the table); `#!lookx` is a comment |
| `input.look_host` | headless host: injected motion reaches the next latch once; injections add; live settings (invert, scale); Original drops motion; a script's channel is a pure function of the vbl, plus injection; a buttons-only script latches 0 for 200 VBlanks; pad reads unchanged; never captured headless |
| `input.look_control` (`WILL_FAIL`) | expects injected motion to arrive with `input.mouse_look` off (the gate check is armed) |
| `input.report_control` (`WILL_FAIL`) | Expects Cross from a key bound only to Circle; proves the report checks are armed |
| `input.chord_settings` (`rg-chord-tests`) | the two settings (category, flags, defaults, Original = default, `--preset original` restores them); the validator refuses keys, axes, mouse, 5 buttons, unknown names; canonical text; empty = off; `from_settings` (hold, tap = max(min_press_fields, 2)) |
| `input.chord_no_leak` | through filter + `rg_actions_eval`, field by field: the chord pressed together, uneven within the grace (3 and 5 fields), held to fire, let go early, released one button at a time: Select / Start never in the report; fires exactly once per hold, re-arms only after release; other buttons pass at once |
| `input.chord_lone_press` | a lone tap reaches the report for exactly `tap_fields` fields after release; a lone hold appears after the grace (6 fields) and stays until release; a press that already passed still lets the chord fire; per pad; chord off = no delay |
| `input.chord_rebind` | L1 + R1 takes over (Select / Start immediate again, L1 / R1 never in the report); hold 2 s; a one-button chord on R4 fires; one on Start lets a tap through; the menu editor adds a captured pad button, refuses a key with the reason, removes all (no guard) |
| `input.chord_hotplug` | the chord state follows the roster when an earlier pad is unplugged |
| `input.overlay_prompts` | generic words and tag expansion; PlayStation / PS4 / PS5 / Xbox One / 360 / Steam / Switch / keyboard labels for accept, back, pages, toggle, capture hint, Start / Select, sticks, d-pad; rebinding changes them; chord off; the rendered page hint uses them, `%` in a label is safe |
| `input.chord_control` (`WILL_FAIL`) | expects Select + Start in the report without the filter (the checks are armed) |
| `input.chord_host` | the real `host_sdl.c` wiring: a windowed host (320x240, closes itself) and an **SDL virtual gamepad**, real time: holding Back + Start opens the overlay at 0.95-1.4 s and closes it the second time; uneven press let go at 0.5 s does nothing; `rg_host_read_pad` never shows Select / Start (0 of ~250 reads); a lone Start tap is seen, a lone hold from ~100 ms. Skipped (77) without a display |
| `input.chord_host_control` (`WILL_FAIL`) | the same with `input.overlay_chord` empty: Select / Start leak and the overlay stays shut (the live checks are armed) |

## Open items

- **Button prompts** per device (P6): done for the `gaiji2` glyphs (PROMPTS.md
  "Implementation"); prompts baked into other textures and the full-name keyboard labels
  are open there. Rebinding from the menu is done (above).
- **Mouse camera**: done for the orbit and first-person cameras ("Mouse camera
  implementation"); lock-target / target-follow / Insectron / Factory cameras are still
  stick-only, and live capture needs a person to try it with a real mouse.
- **Confirm the inferred roles** (jump, sub-weapon, guard) in a recorded run, then drop
  the `?` from the labels.
- **Analog pressure.** Resolved: the game never enters pressure mode and reads only
  report bytes 0–7 (CONTROLS-AUDIT.md), so the 0/255 pressure the adapter writes is exact
  and nothing reads it.
- **Chorded hotkeys** (Alt+Enter) stay hard-coded; the binding grammar has no modifiers
  (`walk` is an action, not a modifier syntax).
- **Steam Input / Guide button.** Done 2026-10-26: the held chord ("Opening the settings
  overlay with a gamepad"); `ui_overlay` can still be rebound too. The chord has only pure
  tests: someone has to try it on real pads (Xbox with the Game Bar on, a DualSense, a
  Switch Pro, a Steam Deck in Steam Input) and on the PAUSE and map screens.
- **Optional rumble** (a new feature; the game never vibrates).
- **Interactive checks.** Hot-plug, the overlay, walk and the compensation curve with a
  real gamepad are covered only by the pure tests plus a windowed smoke run
  (`rg-host-demo --overlay --window-shot`); a person still has to try them with real
  devices.
