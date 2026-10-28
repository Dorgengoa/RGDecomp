# Settings registry (`src/settings`)

PLAN.md P4 "Settings foundation" and the P6 ground rules. One typed registry drives the
config file, the command line and the in-game settings menu, so the three can't
disagree. All of it is original CC0 code in plain C: no SDL, no third-party parser, no
new dependencies.

| Path | What |
| --- | --- |
| `src/settings/rg_settings.h` | The API: definitions, typed access, INI text, presets, command line, change tracking, display trials |
| `src/settings/rg_settings.c` | The registry |
| `src/settings/rg_settings_core.c` | The P4 core set: display, graphics placeholders, audio, gameplay placeholders, system |
| `src/settings/rg_menu.[ch]` | The menu model the host overlay draws (pure: commands in, text lines out) |
| `src/host/rg_input.h`, `host_input.c` | Registers the `input.*` settings (docs/INPUT.md) |
| `src/host/host_sdl.c` | Applies settings live; the overlay (F1 / gamepad Guide) |
| `tests/settings/` | `rg-settings-tests`, CTest labels `settings` and `input` |

CMake: `rg_settings` (static library, added before `src/host`; `rg_host` links it
publicly). `tests/settings` is built with `RG_HOST`.

## Model

Each setting is an `rg_setting_def`:

| Field | Meaning |
| --- | --- |
| `id` | `section.name[.more]`, lower case `[a-z0-9_.]`. Stable: it's the file key and the `--set` name |
| `type` | `BOOL`, `INT`, `FLOAT`, `ENUM` (stored as an index into `enum_names`), `STRING`, `BINDING` (a string checked by a validator; docs/INPUT.md) |
| `category` | Menu page. Defaults to the first id component |
| `label`, `help` | Menu text; also written as comments in the file |
| `def_*` | Default |
| `orig_*` + `RG_SETF_HAS_ORIGINAL` | Value in the "original" preset. Without the flag, the default is used |
| `min/max/step` | INT and FLOAT range, menu step |
| `enum_names`, `enum_labels` | ENUM values (file text) and their menu text |
| `validate`, `max_len` | STRING/BINDING check and normalisation |

Flags:

| Flag | Meaning |
| --- | --- |
| `RG_SETF_RESTART` | Takes effect after a restart. The menu marks the row `[restart]` always, and "(restart pending)" once changed (`rg_settings_restart_pending`) |
| `RG_SETF_DISPLAY` | A display change. The menu applies it as a trial that reverts unless confirmed |
| `RG_SETF_GAMEPLAY` | Changes game logic. Labelled `[gameplay]`, and must be off in "original" (a test checks this) |
| `RG_SETF_PLACEHOLDER` | Planned (P6). Stored, validated, shown "(planned)", but has no effect yet |
| `RG_SETF_HIDDEN` | In the file, not in the menu |

Registration checks every definition: bad ids, duplicate ids, and defaults or originals
outside their range are refused with a warning; the rest still register. A definition
registered after a file was loaded picks up that file's value (kept as an unknown key until
then).

### Two value layers

Every setting has a **persistent** value (default, preset, config file, menu) and an
**effective** value (the persistent one, or a command-line override):

| Source | Persistent | Effective |
| --- | --- | --- |
| default, preset, file | written | follows, unless overridden |
| menu, API | written | written; clears an override |
| command line (`--set`) | untouched | written, marked overridden |

Saving writes the persistent layer, so `--set` never leaks into the file, and an override
survives a later `--preset` or `--settings` on the same command line. The menu shows
overridden values as "(--set)". `rg_settings_source()` says where the effective value came
from.

### Validation

Invalid text is never stored:

- **API and menu** (`rg_settings_set_*`, `rg_settings_set_text`): `RG_SET_INVALID` with the
  reason; the value stays as it was.
- **Config file**: the setting falls back to its **default** (not to an earlier line), with a
  warning that names the line, e.g. `settings.ini:9: t.i: 99 is outside 0..10; using the
  default (5)`.
- **Command line**: the override is skipped with a warning, and counted as an error.

Text forms: BOOL takes `true/false, on/off, yes/no, 1/0, enabled/disabled` (any case).
INT takes `strtol(…, 0)` (so `0x0A`). FLOAT must be finite and in range. ENUM names are
case-insensitive. Strings longer than `max_len` (default 1023) are refused.

Warnings go to `stderr` with an `rg-settings:` prefix by default
(`rg_settings_set_warn` redirects or silences them); `rg_settings_warnings` counts them.

## Config file

A small INI dialect, parsed by `rg_settings_parse` (a few dozen lines, no library):

```ini
# Rogue Galaxy PC port settings
preset = original              # top level only: applies the preset here; later lines win

[display]
window_mode = fullscreen       # id = display.window_mode
scale = integer
vsync = true

[audio]
master_volume = 80

[input]
bind.confirm = key:Return, pad:a   # id = input.bind.confirm
invert_camera_y = yes

[system]
screenshot_dir = "C:\shots dir"   # quotes keep spaces and '#'; \" and \\ inside quotes
```

- `[section]` prefixes the keys below it with `section.`. Before any section, keys are full
  ids (`display.vsync = on` works at the top).
- A `#` starts a comment at the start of a line or after whitespace, outside quotes. So
  `key:Keypad #` would need quotes; key names don't otherwise contain ` #`.
- A UTF-8 BOM (Notepad) and CRLF line ends are accepted.
- **Unknown keys** warn ("kept") and are written back by `rg_settings_format`, in their
  section, so a file from a newer build survives a save by an older one.
- `rg_settings_load(path)`: a missing file is not an error (first run).
- `rg_settings_format(out, cap, flags)` writes every setting with a comment block (label,
  help, type/range/enum values, default, `[restart]`, `[gameplay]`, `[planned: no effect
  yet]`). `RG_FMT_CHANGED_ONLY` writes only non-default values; `RG_FMT_NO_COMMENTS`
  drops the comments. The output round-trips through the parser byte for byte (tested).
- `rg_settings_save(path)` writes `<path>.tmp` and renames it over the file. On Windows
  `rename` can't replace a file, so the old file is removed first; the `.tmp` is complete
  by then, so a crash leaves either the old file, or no file plus a complete `.tmp`.

## Command line

`rg_settings_apply_args(s, argc, argv, &errors, &settings_path)` consumes, in order:

| Argument | Effect |
| --- | --- |
| `--set id=value` or `--set=id=value` | Override (effective layer). The value may be quoted |
| `--preset name` or `--preset=name` | Applies a preset (persistent layer) |
| `--settings path` or `--settings=path` | Loads a file (persistent layer). The last one is returned so the program can save back to it |

It compacts `argv` in place (other arguments keep their order) and returns the new `argc`.
`rg-host-demo` and `rg-runtime-demo` call it first, then parse their own flags. Program
flags that set `rg_host_config` after `rg_host_config_from_settings` (`--scale`,
`--fullscreen`, `--vsync`, `--mute`) are turned into overrides by
`rg_host_settings_from_config`, so attaching the registry doesn't undo them.

```
rg-host-demo --settings rg.ini --set display.scale=integer --preset original
rg-host-demo --write-settings defaults.ini      # every setting with its comments
```

## Presets

- **`original`**: every setting's original value (or its default where none is given):
  native resolution, 4:3, original frame rate and filtering, no enhancements, no gameplay
  options. The verification runs use this one. `rg_settings_matches_preset(s, "original")`
  is their guard.
- **`default`**: every default.
- **User presets**: `rg_settings_add_preset(s, name, label, ini_text)`. Settings the text
  doesn't name go to their defaults when it's applied. The text is fully validated when the
  preset is added.

Applying a preset writes the persistent layer of every setting (source `PRESET`).
Command-line overrides stay on top.

Where "original" differs from "default" today: `graphics.internal_res` (native vs match
window), `graphics.anisotropic` (off vs 16x), `gameplay.skip_seen_movies` (off vs on),
`prompts.style` (playstation vs auto), `input.mouse_look` (off vs on; docs/INPUT.md "Mouse
camera implementation"). The rest are equal until the P6 features land.

## The core settings (`rg_settings_register_core`)

Existing knobs, now in the registry:

| Id | Type | Default | Original | Flags | Applied by |
| --- | --- | --- | --- | --- | --- |
| `display.window_mode` | windowed / fullscreen / exclusive | windowed | windowed | display | host, live (exclusive is borderless for now) |
| `display.width`, `display.height` | int 320..16384 / 224..16384 | 1280 / 960 | – | display | host, live (only when the setting changes, so a hand-resized window keeps its size) |
| `display.scale` | linear / nearest / integer / stretch (`rg_scale_mode` order) | linear | linear | display | host, live |
| `display.vsync` | bool | off | off | display | host, live; with host-clock pacing the pacer then never sleeps for a present slot (the present waits for the display) |
| `display.pacing` | retail / host | host | retail | | runtime, live (docs/NATIVE-THREADS.md "Paced mode"): retail = one present per VBlank phase, the virtual clock slept to wall time (the Original cadence); host = the logic's VBlank phases follow host time through a bounded fixed-step accumulator (at most 4 phases back to back, older debt dropped), presents follow `display.frame_rate` / VSync. Runs without a host clock (`--headless`, `--unthrottled`, `system.throttle` off) are always retail; `RG_PACE=retail\|host` overrides |
| `audio.enabled` | bool | on | on | restart | host create / runtime |
| `audio.master_volume` | int 0..100 | 100 | 100 | | host, live (`SDL_SetAudioStreamGain`) |
| `audio.latency_ms` | int 0..500, step 8 | 64 | – | | host, live: the output queue target (`rg_host_set_audio_latency`; 0 = off, push as produced; SOUND.md "Load-screen audio") |
| `system.throttle` | bool | on | on | restart, hidden | runtime (`rg_runtime_config_from_settings`) |
| `system.screenshot_dir` | string | `.` | – | | host, live (F12 uses the new folder at once; `rg_host_screenshot_dir`) |

Renderer graphics settings (P6, docs/GPU.md "Graphics settings"; applied live by the
runtime and `rg-host-demo --gpu` through `gpu_gfx_from_settings`, GPU renderer only except
the frame cap and the display ones):

| Id | Values (default; original) | Applied by |
| --- | --- | --- |
| `display.monitor` | 0..15 (0), display | host (`rg_host_set_monitor`) |
| `display.frame_rate` | original, 30, 60, 120, 144, uncapped (original) | runtime: presentation cap; logic stays on the virtual clock (host pacing: the pacer's present slots; at most one present per VBlank phase unless `display.interpolation` is on) |
| `display.interpolation` | bool (off; off) | runtime + native renderer, live (native-only exe; `RG_INTERP=1\|0` overrides): the unlocked frame rate. With host pacing and a cap above 60 (120 / 144 / uncapped) presents between VBlank phases show in-between images: camera, model and bone transforms interpolated between the last two game frames (one game frame of delay), unmatched items, 2D and effects as the latest frame; logic stays at 59.94 Hz fixed step and the run hash is unchanged (docs/NATIVE-RENDER.md "Interpolated presentation") |
| `display.fps_counter` | off, fps, detailed (off; off) | host, live: corner text drawn by the window's renderer at present time (`draw_fps` in host_sdl.c, after the settings overlay and any window shot, so it is never in a screenshot, `--shot` dump, render_gate image or the run hash; works for every backend that presents through the SDL renderer: D3D11 zero-copy, Vulkan, the read-back copy path). `fps` = presents per second over the last half second; `detailed` adds the mean / max present interval, the game-logic rate (`rg_frame_logic_ticks`, reported by the runtime each field through `rg_host_fps_logic`) and `AUDIO STARVED` when the device queue ran dry in that half second |
| `graphics.internal_res` | native, 2x..8x, window (window; native) | `gpu_set_scale`, live |
| `graphics.antialiasing` | off, fxaa, ssaa2, ssaa3, ssaa4 (off) | scale x N + post chain (MSAA dropped: shader-decided coverage) |
| `graphics.downsample` | box, bilinear, bicubic, lanczos (box) | post chain (SSAA, minification to the window) |
| `graphics.anisotropic` | off, 2x, 4x, 8x, 16x (16x; off) | draw shader, 3D triangles with ordinary textures |
| `graphics.texture_filter` | original, bilinear, nearest (original) | draw shader, same scope |
| `graphics.gamma` | 0.5..2 (1) | post chain |
| `graphics.brightness` | 0.5..1.5 (1) | post chain |
| `graphics.sharpen` | 0..1 (0) | post chain |
| `graphics.output_filter` | off, scanlines, crt (off) | post chain, at the window resolution |
| `graphics.aspect` | 4:3, 16:9, 16:10, 21:9, auto (4:3), display | `rg-game`: the game's WIDE flag, widened to any shape by the stage 1 overrides, + the host canvas (docs/WIDESCREEN.md); 21:9 = 64:27; auto = the window's shape, clamped to 4:3..32:9 |
| `graphics.movie_aspect` | keep, stretch (keep) | with a wide aspect: movies pillarboxed at 4:3, or stretched (docs/WIDESCREEN.md) |

`display.window_mode` exclusive now switches to the display mode closest to
`display.width x height` (borderless if none).


Placeholders (`RG_SETF_PLACEHOLDER`, from PLAN.md P6):

| Id | Values (default; original) |
| --- | --- |
| `graphics.bloom`, `graphics.depth_of_field`, `graphics.motion_blur` | original, enhanced, off (original) |
| `graphics.lod_bias` | -2..2 (0) |
| `graphics.shadow_res` | original, 2x, 4x (original) |
| `audio.music_volume`, `audio.effects_volume`, `audio.voice_volume`, `audio.movie_volume` | 0..100 (100) |
| `audio.background` | bool (on) |
| `audio.device` | string, empty = system default (restart) |
| `gameplay.text_speed` | original, fast, instant (original), **gameplay** |
| `gameplay.skip_seen_movies` | bool (on; off) |

`prompts.style` (auto / playstation / xbox / nintendo / keyboard; default auto, original
playstation; live: rg-game swaps the `gaiji2` button glyphs, docs/PROMPTS.md
"Implementation") is registered with the input settings, on the Controls page (docs/INPUT.md "Device type and button prompts").

The input settings (`input.bind.*`, deadzones, the stick dead-zone compensation
(gameplay, off in Original), sensitivity, inversion, vibration (hidden: the game never
vibrates), players, press latch) are listed in docs/INPUT.md. Renamed binding ids keep
loading through `rg_settings_add_alias` (an old id resolves to the new setting in files,
presets, `--set` and `rg_settings_find`; files are written with the new id).

## Menu API (`rg_menu.h`) and the overlay

The menu model is pure, so it's tested without a window:

```c
rg_menu m;
rg_menu_init(&m, settings);          /* pages = categories with visible rows + "presets" */
m.save_path = "rg.ini";              /* shows a "Save settings" row */
rg_menu_command(&m, RG_MENU_TOGGLE, now_ms);   /* UP DOWN LEFT RIGHT ACCEPT BACK PAGE_PREV PAGE_NEXT */
rg_menu_tick(&m, now_ms);            /* reverts an expired display trial */
n = rg_menu_render(&m, now_ms, lines, cap);    /* title, page bar, rows, help, trial prompt, status */
```

- **Pages:** one per category that has visible settings, in registration order (Display,
  Graphics, Audio, Gameplay, System, Controls, Menu controls), then "Presets & save".
  PAGE_PREV/NEXT wrap.
- **Rows:** LEFT/RIGHT step the value (`rg_settings_step`: bool toggles, enum cycles, int
  and float move by `step` and clamp; floats snap to the step grid). ACCEPT steps bools and
  enums forward. Each settings page ends with "Reset this page to defaults"; a page with
  binding rows also has "Reset all bindings (game and menu) to defaults". The presets page
  lists every preset ("(active)" on the one that matches) and "Save settings". Row
  codes are `-1 - (RG_ROW_* + RG_ROW_STRIDE * i)`.
- **Flags on rows:** `[restart]` (always, for `RG_SETF_RESTART`), `[gameplay]`,
  `(planned)`, "(restart pending)" once a restart setting changed, "(--set)" for a
  command-line override. The help area under the rows repeats what each flag of the
  selected row means ("[restart] takes effect after a restart; ...", "display change:
  reverts in 15 s unless kept").
- **Binding rows:** ACCEPT opens the binding editor (`RG_MENU_VIEW_BINDINGS`), described in
  docs/INPUT.md "Rebinding from the menu" (capture, "Capture mouse motion" with its
  confirm step, and the device guard that keeps every menu control on the keyboard and on
  a gamepad). The page row shows the whole binding list (no "..."); long rows wrap.
- **Long rows** (`rg_menu_wrap(in, n, cols, out, cap)`): `rg_menu_render` produces logical
  lines (up to 319 characters) and each carries an `indent` for its continuation lines
  (33 = the value column on settings rows, 49 = the "also:" column in the binding editor,
  4 otherwise). The wrapper breaks at the last space that fits, else hard (never inside a
  UTF-8 sequence), indents continuations by `indent` (at most half the width), drops
  trailing blanks and keeps the selected/header flags, so no character is lost. The host
  overlay wraps to the columns that fit its scale and keeps the title lines pinned and
  every wrapped line of the selected row in view.
- **String rows:** ACCEPT opens text entry (`RG_MENU_VIEW_TEXT`, below).
- **BACK** closes the menu (in an editor it returns to the page).
- **Text entry** (`rg_menu_text_editing`). The field starts with the current value and the
  cursor at the end. Keyboard: the host starts SDL text input and feeds
  `rg_menu_text_input(m, utf8)` (control characters dropped, a UTF-8 sequence is one
  character for the cursor and Backspace) and `rg_menu_text_key(m, RG_TEXT_*)`
  (Backspace, Delete, Left, Right, Home, End, Enter = commit, Esc = cancel); the keyboard
  doesn't navigate the menu meanwhile. Gamepad: an on-screen selector of 6 character rows
  (a-z, A-Z, digits `. - _`, `/ \ : ~ ( ) ! , ' + = @ &`) and a row of Space, Delete,
  Clear, OK, Cancel; directions move (wrapping), ACCEPT types the selected key, BACK deletes
  before the cursor, PAGE_PREV/NEXT move the text cursor. Commit goes through
  `rg_settings_set_text`, so the validator applies: an invalid value keeps the editor open
  with the reason in the status line. The field holds up to `RG_MENU_TEXT_MAX - 1` (255)
  bytes. Closing the overlay drops an open edit.
- **Display trials:** changing a `RG_SETF_DISPLAY` row calls `rg_settings_trial_begin`
  first. The menu then shows "Keep these display settings? accept = keep, back = revert
  (N s)". ACCEPT keeps, BACK reverts, LEFT/RIGHT on a display row change it again (the
  trial is extended and keeps the oldest values), everything else is ignored. If nothing is
  pressed for `trial_ms` (15 s), `rg_menu_tick` reverts. Closing the overlay reverts an
  open trial. The settings layer does the bookkeeping (`rg_settings_trial_*`,
  `rg_settings_tick`), so other front ends get the same behaviour.

The **host overlay** (`rg_host_attach_settings(h, s, save_path)`):

- toggled by the `ui_overlay` action: F1, or the gamepad Guide / touchpad button. It's
  rebindable (docs/INPUT.md). `rg_host_set_overlay(h, open)` opens it from code
  (`rg-host-demo --overlay`);
- navigated by the `ui_*` actions from every device at once, keyboard alone or gamepad
  alone, with key-repeat-style auto-repeat (400 ms, then every 90 ms) for directions and
  pages;
- drawn by `rg_host_present` over the scaled frame, with SDL's built-in debug font, scaled
  to the window, long rows wrapped to the width (`rg_menu_wrap`, above).
  `rg_host_request_window_shot` (`rg-host-demo --window-shot`) captures it;
- driven from code by `rg_host_menu_script(h, "next,down,accept,text:abc,press:key:F")`
  (`rg-host-demo --menu ...`, for smoke runs): menu commands, typed text, presses that
  go through the rebinding detector like live ones, and `motion:DX:DY` (relative mouse
  motion for a motion capture);
- while a binding is being captured, raw device events go to the detector, not to the
  menu, the fixed hotkeys (F11, F12) or the game, and the press that finished the capture
  is absorbed (that pump's menu commands are dropped). While text is typed, the keyboard
  goes to the text field and only gamepads navigate;
- while it's open, live pad reads are neutral, so menu presses don't reach the game. Input
  scripts are unaffected (they bypass live input entirely);
- Esc is "back" while it's open, and still quits while it's closed (the old hotkey).

`rg_host_attach_settings` applies the settings at once and again whenever
`rg_settings_generation` changes (checked in every `rg_host_pump`). That's how menu,
API and `--set` changes reach the window, audio and input.

## Using it from a program

```c
rg_settings *s = rg_settings_create();
rg_settings_register_core(s);
rg_actions_register_settings(s);                       /* src/host/rg_input.h */
const char *path = NULL;
argc = rg_settings_apply_args(s, argc, argv, &errors, &path);

rg_runtime_config cfg;                                 /* src/runtime */
rg_runtime_default_config(&cfg);
rg_runtime_config_from_settings(&cfg, s);              /* throttle, audio, window mode, scale; cfg.settings = s */
cfg.settings_path = path;                              /* overlay "Save" target */
rg_runtime_init(&cfg);                                 /* the host gets the registry, applies it live */
rg_settings_mark_applied(s);                           /* start of "restart pending" tracking */
```

`rg-game` (`src/game/rg_game_main.c`) doesn't do this yet. It belongs to the game-link
work and was left untouched; these lines are all it needs.

## Tests (`ctest -L settings`)

| Test | Checks |
| --- | --- |
| `settings.registry_types` | Six types; four bad definitions refused with warnings; every bool spelling; int hex/range/garbage; float range/NaN; enum case and error list; string validator normalisation; binding normalisation and UNCHANGED; wrong type; unknown id; display text; reset |
| `settings.ini_parse` | BOM, top-level ids, sections (case, spaces), CRLF, trailing comments, quoted values with `#` and `\"`; invalid → **default** (not the earlier line) with the line number; unknown keys kept and written back; a late definition picks up a kept key |
| `settings.ini_roundtrip` | Every core and input setting, with odd strings (spaces, `#`, quotes, backslashes), an empty binding, a 16-digit float: format → parse → format is byte-identical; `CHANGED_ONLY` holds exactly the 11 changes + the unknown key and reproduces the values; truncated output |
| `settings.presets` | Fresh = default; original values; user preset (add, duplicate, bad value, unknown id); unnamed settings → default; `preset =` in a file; gameplay options off in original |
| `settings.cmdline` | `--set` both forms, quoted values, case-folded ids, `--preset`, `--settings`, argv compaction; 2 errors counted; overrides survive a later preset and file; the saved layer excludes them; a menu change replaces an override; `clear_overrides`; a missing `--settings` file |
| `settings.change_tracking` | One callback per effective change and none for no-ops; an override hides file changes; preset event count; restart-pending set and cleared |
| `settings.display_trial` | Revert exactly at the deadline (fake clock); extension keeps the oldest values across two settings; confirm; an override restored by a revert; int clamp, float grid, enum wrap, text rows |
| `settings.save_load` | Atomic save (no `.tmp` left), replacing an existing file, reload equality, override not saved, the comment block; missing file |
| `settings.core_defs` | Categories, every default parses back unchanged, graphics placeholders flagged, the old knobs exist, `display.scale` order = `rg_scale_mode`; `rg_host_config_from_settings`; `rg_host_settings_from_config` overrides; a headless host applies scale and volume |
| `settings.menu_keyboard` | Keyboard only, through the real UI bindings: reaches and changes **every** visible setting (over 60): bool/enum/int/float by stepping (confirming display trials), strings by typing, bindings by "Add a binding" + a captured key; BACK reverts a trial; an unconfirmed trial reverts after 15 s; applying Original from the presets page; render; close/reopen |
| `settings.menu_gamepad` | The same with gamepad buttons only (strings through the on-screen selector, bindings by a captured paddle), plus left-stick navigation with exact auto-repeat timing |
| `settings.menu_rebind_keyboard` | Keyboard only, through the real UI bindings and the host's capture detector: open `confirm`'s editor; add (F); menu commands ignored while capturing; replace binding 0; a duplicate in the same action is refused; a conflict with `cancel` warns, keeps both, and both fire; no warning across contexts (a menu key); Esc cancels; the 5 s timeout (still waiting at +4950 ms, cancelled at +5000, detector stopped, a later press ignored); remove; reset action; the device guard on `ui_overlay` (F1 refused, touchpad removed, then Guide refused); "Reset all bindings" restores `rg_actions_default` exactly; closing the overlay cancels a capture |
| `settings.menu_rebind_gamepad` | The same with gamepad buttons only: captures a paddle, a trigger axis, East (conflict with `cancel`); Guide cancels |
| `settings.menu_text_entry` | Keyboard: initial value and cursor, Backspace (UTF-8 aware), control characters dropped, Home/Delete/End/Left/Right, insert, commit, file round trip with `#`; cancel; the 255-byte limit; closing drops the edit. Gamepad: the selector (wrap, column clamp, Space, Delete, Clear, OK, Cancel, BACK deletes, pages move the cursor). An invalid value keeps the editor open with the validator's reason; a valid one is normalised |
| `settings.menu_flags` | `[restart]` shown before a change, "(restart pending)" after and gone when changed back; `[gameplay]`, `(planned)` and the help explanations; every visible restart/gameplay row carries its marker; the display trial prompt counts 15 s and reverts at exactly +15000 ms |
| `settings.menu_device_guard_keyboard` / `_gamepad` | One device only, for every menu control (`ui_*`, overlay toggle included): removing every binding (last row first) is refused exactly twice (the last key, the last gamepad binding), with the reason and the cursor on "Add a binding"; the survivors drive the action (rebuilt map); replacing the device's last binding with the other device's input is refused and offered as "Add <input> instead", which ACCEPT adds; a replace within one device is allowed; moving keeps the offer, BACK drops it; a file list without a gamepad binding shows the warning and still protects its key; game actions (`map`) can become unbound |
| `settings.menu_wrap` | `rg_menu_wrap`: break before a word that doesn't fit, no trailing blanks, indent clamped to half the width, selected flag on every piece, hard break without splitting UTF-8, `cap`; every row of every page (each with its help) and the editors (a full 8-binding row with no "...", a conflict status, the motion prompt, a guard refusal, a long text field) at 78 (640x480), 84 (1280x720) and 40 columns: no line wider, no character lost |
| `settings.screenshot_dir_live` | `system.screenshot_dir` has no `RG_SETF_RESTART`: no `[restart]`, set through text entry with "set" (no restart note), nothing pending; a headless host picks it up on the next `rg_host_pump` (`rg_host_screenshot_dir`), empty → `.` |
| `settings.fps_counter` | `display.fps_counter`: off by default and in Original, no `[restart]`, no display trial; RIGHT steps off -> fps -> detailed and a headless host picks each up on the next pump (`rg_host_fps_mode`); `detailed` / `FPS` spellings parse from a file |
| `settings.invalid_control` (`WILL_FAIL`) | Expects an out-of-range file value to be kept; proves the fallback check is armed |

## P6 menu work: checkpoint

- 2026-10-12: started (rebinding capture, pad family + `prompts.style`, text entry,
  flag markers). Build dir `build/menu-i686`.
- 2026-10-12: code + tests in, `ctest -L "settings|input|host|padmc|runtime"` 84/84 green
  in `build/menu-i686` (`runtime.cdvd_realdata` skipped, as before).
- 2026-10-12: windowed smoke run (`rg-host-demo --frames 25 --menu ... --window-shot`):
  `out/menu/01-controls-page.png` … `09-prompts-row.png` (Controls page, binding editor,
  capture prompt, a conflict warning, keyboard text entry, the on-screen selector, flag
  markers on Audio, a display trial, `prompts.style`). Docs updated. Done.
- 2026-10-12, follow-ups: device guard for the menu controls (keyboard + gamepad binding
  each, refusal + "Add ... instead" offer), long rows wrapped (`rg_menu_wrap`, host overlay),
  `system.screenshot_dir` no longer `[restart]` (it was always applied live; a headless
  host now applies settings changes in `rg_host_pump` too), "Capture mouse motion" (300 px,
  2:1 dominance, confirm step). Tests: `settings.menu_device_guard_keyboard/_gamepad`,
  `settings.menu_wrap`, `settings.screenshot_dir_live`, `input.capture_motion`,
  `input.menu_mouse_capture_keyboard/_gamepad`; `menu_rebind_*` updated for the guard and
  the new editor row.
- 2026-10-12: windowed shots at 640x480 and 1280x720 (`rg-host-demo --set
  display.width=W --set display.height=H --menu ... --window-shot`):
  `out/menu/10-long-binding-row-WxH.png` (an 8-binding row wrapped under its value column),
  `11-editor-conflict` (wrapped "also:" note and WARNING status), `12-guard-refusal`,
  `13-guard-offer` ("Add pad:a instead"), `14-motion-capture` (prompt), `15-motion-confirm`
  ("Bind mouse:x+ to Camera right?"), `16-long-help` (a wrapped help line). Nothing runs
  past the right edge at either size.
- 2026-10-12: `ctest -L "settings|input|host|padmc|runtime"` in `build/menu-i686`: every
  menu, input, host, padmc and runtime test passes (`runtime.cdvd_realdata` and
  `gpu.gfx.game_replay` skipped). Three fail on the graphics-settings lane's in-flight
  `rg_settings_core.c` / GPU work, not on this change: `settings.save_load` (the
  `display.scale` help text changed), `settings.core_defs` (graphics settings no longer
  `RG_SETF_PLACEHOLDER`) and `gpu.gfx.anisotropic`; those tests belong to that lane to
  update. Done.

## Open items

- **Rebinding and text entry**: done, including mouse-motion capture and the per-device
  guard on the menu controls (docs/INPUT.md). Not guarded: a hand-edited file or a user
  preset can still leave a menu control without a device; the editor then warns, and
  "Reset all bindings" stays reachable from the device that is left.
- **Exclusive fullscreen and monitor selection**: implemented (docs/GPU.md "Graphics
  settings", "Display (host)"); only smoke-tested on one monitor.
- **Default config path.** Programs take `--settings FILE`; nothing loads a file
  implicitly yet. A per-user location (`SDL_GetPrefPath`) should be chosen when `rg-game`
  adopts the registry.
- **The overlay font** is SDL's 8x8 debug font. A proper UI (glyph prompts per device from
  `rg_host_prompt_style`, controller-friendly layout) is still to come. Long rows wrap
  (no horizontal scrolling); below 1x scale (narrower than ~650 px) the overlay doesn't
  shrink the font further, it only wraps to fewer columns.
- **Gameplay presets.** The P6 gate needs the regression corpus run with "original" and
  with every non-gameplay option on; `rg_settings_matches_preset` is the hook for that
  check, but the corpus doesn't exist yet.
