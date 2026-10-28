# Host shell (`src/host`)

PLAN.md "host/" layer, D5 (SDL3). The platform shell the port runs inside: a window that
presents the GS display read-out, keyboard and gamepad input mapped to a DualShock 2
report, a deterministic input-script source for regression runs, a 48 kHz audio stream,
real-time pacing for the kernel's virtual clock, and PNG screenshots. It is standalone:
the game isn't linked yet, so `rg-host-demo` drives the GS model directly.

All of it is original CC0 code except SDL3 (zlib, see below). No GPL code, no emulator code.

| Path | What |
| --- | --- |
| `src/host/host.h` | The whole public API (C) |
| `src/host/host_pad.c` | DS2 report, input names, keyboard/gamepad map, config text |
| `src/host/rg_input.h`, `host_input.c` | Input-action layer: actions, bindings, DS2 adapter, gamepad roster, press latch, UI navigation (INPUT.md) |
| `src/host/host_script.c` | Input scripts (the `tools/trace/input.py` format and table) |
| `src/host/host_scale.c` | Presentation rectangle math (aspect + scaling modes) |
| `src/host/host_png.c` | PNG writer (stored deflate), CRC-32, Adler-32 |
| `src/host/host_pace.c` | Cycle/ns conversion, NTSC field times, the pacing hook |
| `src/host/host_sdl.c` | SDL3 window, renderer, events, gamepads, audio stream |
| `src/host/demo/host_demo.c` | `rg-host-demo` |
| `tests/host/` | CTest suite, label `host` |
| `src/settings/`, `tests/settings/` | Settings registry + menu model (SETTINGS.md); tests for it and the input layer, labels `settings` and `input` |

CMake targets: `rg_host` (static library, links `SDL3::SDL3-static`), `rg-host-demo`,
`rg-host-tests`. The top-level option `RG_HOST` (default ON) adds both directories.
`src/host/smoke.c` still belongs to the top-level `rg-smoke` target and isn't in `rg_host`.

## SDL3: how it's obtained

- **Version:** SDL 3.4.18, the latest release tag (`release-3.4.18`) on 2026-10-11.
- **Source, not a prebuilt DLL.** `src/host/CMakeLists.txt` uses `FetchContent` on the
  official release *source* archive `SDL3-3.4.18.tar.gz`, pinned by SHA-256
  `9c75cf16…34a3`. That hash equals the digest GitHub publishes for the release asset.
  SDL is configured as a static library (`SDL_STATIC=ON`, `SDL_SHARED=OFF`; tests,
  examples, install and camera are off) and built by our i686 clang toolchain, so the
  binaries need no DLL and use the same static CRT as the rest of the port.
- **Offline builds.** If `RG_SDL3_ARCHIVE` (default `../tools\dl\SDL3-3.4.18.tar.gz`,
  next to the LLVM/Ninja archives) exists, it's used instead of the download. The hash is
  checked either way.
- The top level strips `-O` from per-config flags for port code. SDL gets `-O2` back as a
  private option, since it's third-party code.
- Recorded in `THIRD_PARTY_NOTICES.md`. Ship SDL's `LICENSE.txt` with any binary.
- **Cost:** the first configure extracts SDL into `<build>/_deps`, and building SDL adds
  a few minutes to a clean build (the first configure was about 12 minutes here). Configure with `-DRG_HOST=OFF` to skip it.

## Build and test

```powershell
powershell -ExecutionPolicy Bypass -File tools\build.ps1 -BuildDir build\host-i686
ctest --test-dir build\host-i686 -L host
build\host-i686\rg-host-demo.exe                      # window
build\host-i686\rg-host-demo.exe --headless --frames 40 --input tests\host\data\demo_input.txt --screenshot out.png
```

## Window and presentation

- `rg_host_create(&cfg)` opens a resizable, high-DPI-aware window (default 1280x960) with
  an SDL renderer. The default renderer backend is SDL's choice (Direct3D 11/12 on
  Windows).
- `rg_host_present(h, rgba, w, h)` takes the `gs_read_display` output: RGBA8 in R,G,B,A
  byte order (`SDL_PIXELFORMAT_RGBA32`). It copies the frame (it's kept for screenshots),
  uploads it to a streaming texture, and draws it into the rectangle from `rg_fit_rect`,
  letterboxed on black.
- **Aspect.** A 640x448 interlaced frame is displayed at 4:3 (`aspect_num/den`, default
  4:3). Each source pixel is therefore 0.933 wide. 0:0 means square source pixels.
  `rg_host_set_aspect(h, canvas, content)` changes it live (graphics.aspect = 16:9: a
  16:9 canvas, with the frame 4:3 pillarboxed inside it on the title and in movies);
  `rg_host_present` and the runtime use `rg_host_fit` / `rg_fit_rect_content`, which is
  `rg_fit_rect` until an aspect is set (docs/WIDESCREEN.md).
- **Scaling modes** (`rg_scale_mode`, `--scale`):

  | Mode | Rectangle | Filter |
  | --- | --- | --- |
  | `linear` (default) | Largest 4:3 rectangle in the window | Bilinear |
  | `nearest` | Same | Nearest |
  | `integer` | Height = n x source lines (largest n that fits), width = round(height x 4/3). If not even n = 1 fits, falls back to `linear` | Sharp: nearest-neighbour to n x the source in a render target, then linear to the final width. Lines stay crisp, and only the non-integer horizontal factor is filtered |
  | `stretch` | Whole window | Bilinear |

  Example: in a 1920x1080 window, `integer` gives 1195x896 at (362, 92) with n = 2.
- **Settings overlay:** F1 or the gamepad Guide button (rebindable) opens the settings
  menu drawn over the frame (SETTINGS.md "Menu API"). While it's open, live pad reads are
  neutral and Esc means "back". Rows longer than the window wrap (`rg_menu_wrap`): the
  overlay works out how many 8 px columns fit at its scale (78 at 640x480, 84 at 1280x720)
  and continues a long row on indented lines, so nothing runs off the right edge.
- **Hotkeys** (handled in `rg_host_pump`): Esc quits (overlay closed). F11 or Alt+Enter toggles
  fullscreen (borderless desktop fullscreen). F12 writes `rg-shot-NNNN.png` (the next free
  number) into `screenshot_dir` (`system.screenshot_dir`, applied at once;
  `rg_host_screenshot_dir`). While Alt is held, the keyboard doesn't feed the pad, so
  Alt+Enter never reaches the game as START.
- **Display settings** (P6, docs/GPU.md "Graphics settings"): `display.window_mode`
  exclusive uses the display mode closest to `display.width x height`
  (`rg_host_set_fullscreen_mode`; borderless if there is none), `display.monitor` moves the
  window and fullscreen to that display (`rg_host_set_monitor`). With the GPU renderer, the
  runtime may hand `rg_host_present` a frame already resampled to the window rectangle
  (post chain); it is then drawn 1:1.
- `vsync` defaults to off, because the pacer owns timing. Turning it on as well makes the
  presentation block on the monitor.

## Input

### The pad report

`rg_pad` holds what the game reads from one controller:

- `buttons`: the game's active-high word, using the SCE bits. These are identical to
  `tools/trace/input.py` `BUTTONS`: L2 0x0001, R2 0x0002, L1 0x0004, R1 0x0008, TRIANGLE
  0x0010, CIRCLE 0x0020, CROSS 0x0040, SQUARE 0x0080, SELECT 0x0100, L3 0x0200, R3 0x0400,
  START 0x0800, UP 0x1000, RIGHT 0x2000, DOWN 0x4000, LEFT 0x8000.
- `lx ly rx ry`: 0x00 to 0xFF, centre 0x80. 0x00 is left or up.
- `pressure[12]`: 0 or 255, because every host source is digital or treated as digital.

`rg_pad_ds2_report` writes the 20-byte `scePadRead` buffer of a DualShock 2 in analog plus
pressure mode, for the future pad HLE:

- `[0]` = 0x00 and `[1]` = 0x79.
- `[2..3]` = buttons, active low. The game decodes them as `0xFFFF ^ (raw[2]<<8 | raw[3])`.
- `[4..7]` = rx, ry, lx, ly.
- `[8..19]` = pressure, in the order right, left, up, down, triangle, circle, cross,
  square, L1, R1, L2, R2.

### Live sources and mapping

**Since 2026-10-12, live input goes through the input-action layer: see
[INPUT.md](INPUT.md).** Actions (move, camera, confirm, cancel, ...) have several
bindings each across keyboard, mouse and gamepads, stored in the settings registry
([SETTINGS.md](SETTINGS.md)); an adapter produces the same `rg_pad` / DS2 report as
before. In short:

- **Port 0** is the keyboard and mouse (only while the window has focus) plus, with
  `input.players = one` (the default), **every** gamepad. With `two`, port 0 gets the
  first gamepad and **port 1** the second.
- Gamepads are opened on hot-plug and kept in connection order (`rg_pad_roster`).
- SDL's gamepad database gives every supported controller the same positional layout.
  SOUTH is DS2 cross whatever the controller labels it.
- Deadzone (per stick, default 0.25 = 8192), analog-as-button threshold (default
  0.35 = 11468), sensitivity, per-axis inversion, vibration strength and a press latch
  (a tap shorter than a field is held for 2 fields) are settings.
- Default keyboard: move W A S D, camera I J K L, d-pad arrows, Cross Space/X, Circle C,
  Square Z, Triangle Tab, L1/R1 Q/E, L2/R2 1/3, L3/R3 V/B, Start Return, Select
  Backspace. The full table is in INPUT.md.

The older per-PS2-input map below (`rg_input_map`, `rg_input_eval`) is still in the API
and still tested. `rg-host-demo --config` loads it and converts it with
`rg_host_apply_input_map`. The action layer gives byte-identical reports for the same
map (`input.legacy_equivalence`). Its own defaults were:

| DS2 | Keyboard | Gamepad |
| --- | --- | --- |
| Cross / Circle / Square / Triangle | X / C / Z / S | South / East / West / North |
| L1 / R1 / L2 / R2 | Q / E / 1 / 3 | Left and right shoulder / left and right trigger |
| L3 / R3 | V / B | Left and right stick click |
| Start / Select | Return / Backspace | Start / Back |
| D-pad | Arrow keys | D-pad |
| Left stick | W A F D (up, left, down, right) | Left stick |
| Right stick | I J K L | Right stick |

### Config file (`--config`, `rg_input_map_load`)

```
# INPUT = binding[, binding...]     (a line REPLACES that input's bindings)
CROSS = key:Space, pad:a
L2    = axis:lefttrigger+, key:Left Shift
LX-   = axis:leftx-, key:A
SELECT =                            # unbind
deadzone = 6000
threshold = 16000
```

- **Inputs:** L2 R2 L1 R1 TRIANGLE CIRCLE CROSS SQUARE SELECT L3 R3 START UP RIGHT DOWN
  LEFT, and the stick half-axes LX- LX+ LY- LY+ RX- RX+ RY- RY+. Names are
  case-insensitive.
- **Bindings:**
  - `key:` takes an SDL scancode name (`SDL_GetScancodeFromName`: "Space", "Return",
    "Left Shift", "Keypad 8" and so on).
  - `pad:` takes an SDL gamepad button name ("a", "b", "x", "y", "back", "start",
    "leftshoulder", "dpup" and so on; "a" is the south button).
  - `axis:` takes an SDL gamepad axis name with a direction suffix ("leftx-",
    "righttrigger+").
- **Limits:** up to 4 bindings of each kind per input.
- **Unchanged inputs:** inputs not listed keep their defaults.
- **Errors** name the line: `line 3: unknown key 'Foo'`.
- **Current map:** `rg-host-demo --write-config map.cfg` dumps it in this format. The dump
  round-trips through the parser exactly, and a test checks that.
- **Known limit:** a key whose SDL name is "," can't be written, because the comma
  separates bindings.

### Input scripts (regression runs)

The format and the compiled table are **exactly** those of `tools/trace/input.py`, so a
port run and a PCSX2 reference run see the same button word on the same game VBlank.

- **Lines:** `first last BUTTON[+BUTTON...]` (inclusive) or `vbl BUTTON`. `#` starts a
  comment.
- **Integers:** read like Python `int(x, 0)`: `0x`/`0o`/`0b` prefixes, `_` separators,
  and no leading zeros.
- **Button names:** case-insensitive. Extra tokens after the third are ignored, as in
  `input.py`.
- **The table:** one u16 per **game VBlank counter** value (`[0x004810C4]`), always
  `RG_SCRIPT_MAX_ENTRIES` = 32,636 long and zero padded. Overlapping lines are ORed
  together. A script that reaches past the table is rejected.
- **Deliberate difference:** a negative VBlank is an error here. `input.py` would index
  its table from the end.
- **Overrides live input:** `rg_host_set_input_script(h, &s)` makes port 0 read **only**
  the script. Sticks stay centred and pressure follows the word. Port 1 reads neutral.
  That matches a hooked PCSX2 run, which has no host input sources.
- **Port model:** the future pad HLE calls `rg_host_read_pad(h, 0, vbl, &pad)` with the
  game's own VBlank counter, which mirrors the trampoline's `table[[0x004810C4]]`.
- **Not scripted:** analog sticks and port 1, because the harness doesn't script them
  either (tools/trace/README.md "Limits").
- `rg_input_script_blob` emits the harness's PINE blob (u32 count, then the words). CTest
  compares it byte for byte with `input.py`'s output.

## Audio

`rg_host_audio_push(h, lr, frames)` queues 48 kHz stereo s16 interleaved PCM into an SDL
audio stream bound to the playback device `audio.device` names (the system default when
empty; "Audio devices and focus" below). SDL converts to the device format. What the game
build pushes is the engine's presentation mix (the per-source volumes, NATIVE-AUDIO.md
"Source volumes"); the run hash has already folded the model mix.

- `rg_host_audio_queued` reports the backlog, so the future mixer can regulate itself
  (the demo keeps it under 200 ms).
- One NTSC field is 800.8 frames. The demo pushes `floor(48000·1001·(k+1)/60000) −
  floor(48000·1001·k/60000)` frames for field k, which keeps the long-run rate exact.
- **Headless,** or when no device can be opened, pushes are counted
  (`rg_host_audio_pushed_total`) and dropped.
- **Output regulator** (`host_audio.c`, `audio.latency_ms`, default 64 ms, 0 = off, live
  via `rg_host_set_audio_latency`): a cushion of silence before the first push and after
  a starve or a pacer re-anchor (`rg_host_audio_resync`) that left the queue under half
  the target, a playback-rate trim of at most ±0.5 % (`SDL_SetAudioStreamFrequencyRatio`)
  for clock drift, and a drop from the front of a push when the queue is far over the
  target. Starves are counted in the stream's get callback; `rg_host_audio_stats`
  reports them with the queue, pads, drops and ratio. Presentation only: the frames the
  game rendered are unchanged (SOUND.md "Load-screen audio", test `host.audio_reg`).
- **Adaptive cushion and catch-up-aware refill** (2026-10-26, NATIVE-THREADS.md "3h"): after
  a starve of S ms (shorter than the cap and not a pacer re-anchor) the target grows by
  1.25 S + 10 ms, at most `$RG_AUDIO_ADAPT_MS` (default 192; 0 = fixed); after ~20 s with
  no starve and no near-empty queue it steps back to the setting by 8 ms every ~2 s (the
  rate trim drains the excess). The refill after a starve leaves room for half the audio
  of the phases the host-clock pacer owes (`rg_host_audio_owed`, set by runtime.c before
  the pushes), so the catch-up burst no longer overflows into a drop. `RG_AUDIO_LOG`
  has a `target` column.
- **De-click** (2026-10-22, `rg_audio_declick`, 96 frames = 2 ms): each place the host
  breaks the stream is crossfaded instead of stepped. A starve: the get callback queues a
  fade of the last pushed frame to silence (once per starve). A pad: the tail fades into
  the silence. The first block after a starve, pad, drop (also a whole dropped block,
  carried to the next push) or empty queue crossfades from what was playing.
  `RG_AUDIO_DECLICK=0` turns it off (A/B); `RG_AUDIO_HOST_WAV=<path>` writes what the
  stream is fed (+ starve silence) and `<path>.events.tsv` the splices
  (NATIVE-AUDIO.md "Pop scan").

### Audio devices and focus (2026-10-26, P6)

- **The stream is the host's own** (`SDL_CreateAudioStream`), bound to a logical device
  opened with `SDL_OpenAudioDevice`. Changing the device unbinds it and binds it to a new
  one: what is queued keeps playing, and the regulator, de-click and rate trim see one
  continuous stream (no re-prime, no desync: the game never waits on the device).
- **`audio.device`** (STRING, live, no restart): the device name; "" = the system default
  (opened as the default, so SDL moves it when the system default changes). Opened by name
  (`rg_audio_device_pick`: exact, then ignoring case). A name that is not present plays on
  the default (`rg_host_audio_device(h, &fallback)` reports it); the named device is taken
  again when it appears (`SDL_EVENT_AUDIO_DEVICE_ADDED`). In the settings overlay LEFT / RIGHT
  on the row steps through "" and the devices present (`rg_menu_set_choices`, the list is
  re-read after a device event); ACCEPT still opens the text editor. The value is persisted
  by name like every setting.
- **Unplug while playing:** `SDL_EVENT_AUDIO_DEVICE_REMOVED` for our logical device ->
  the stream is rebound to the default (logged `rg-host: audio device removed`), the
  queue is kept. A default device that changes is followed by SDL itself.
- **`audio.background`** (BOOL, Original and default **on** = keep playing, as the console
  did): off mutes while the window has no input focus (`SDL_EVENT_WINDOW_FOCUS_LOST` /
  `GAINED`). The mute is the stream gain (`rg_audio_output_gain`: master volume x focus), so
  the queue drains normally and nothing upstream changes. Pausing the game on focus loss is
  not part of this setting.

## Pacing

`rg_pacer_hook` has exactly the `ps2k_pacing_fn` type. A test assigns it to one, which
checks this at compile time. Install it with
`ps2k_set_pacing_hook(rg_pacer_hook, &pacer)`.

- **The hook:** before each idle jump of the kernel's virtual clock from `from` to `to`
  (bus cycles), it sleeps until the wall clock reaches the anchor plus `to`. It uses
  `SDL_DelayPrecise`.
- **Anchor:** set on the first call, and again when virtual time goes backwards (a new
  kernel run) or after `rg_pacer_reset`.
- **Falling behind:** if wall time is behind by more than `max_lag_ns` (default 250 ms,
  e.g. a debugger stop or a load hitch), the pacer re-anchors instead of running flat out
  to catch up, and counts a `resync`. A smaller lag is caught up.
- **Unthrottled** (`rg_pacer_init(&p, 0)`, used by `--headless` and tests): returns
  immediately and never reads the clock. A run is then a pure function of its inputs.
- **Exact arithmetic:**
  - `rg_cycles_to_ns(c) = c·15625/2304`;
  - `rg_field_cycles(k) = k·2460060`, the kernel's own `PS2K_FIELD_SUB` field
    (matches PCSX2: BUSCLK/59.94).
- Throttling the idle jumps is enough. Virtual time advances only at those jumps, or
  through `ps2k_charge`, which isn't throttled. Since the kernel reaches the next VBlank
  through an idle jump, fields come out at 59.94 Hz.

## Screenshots

`rg_host_screenshot(h, path)` writes the last presented frame at **source** resolution
(640x448), not the scaled window. The output is therefore independent of the window size
and of the GPU, which is what makes the headless hash test meaningful.

- **Format:** RGBA8 PNG, filter 0, a zlib stream of stored deflate blocks. That's about
  1.1 MB per frame, which is fine for screenshots.
- No third-party encoder is used. The writer is about 100 lines, written from the
  PNG/zlib RFCs.

## `rg-host-demo`

Each field the demo:

1. sends PATH3 GIF packets (A+D) to the GS model, which draws with its software
   rasterizer:
   - a background sprite;
   - a rotating Gouraud triangle;
   - a bouncing half-transparent sprite blended with ALPHA `(Cs−Cd)·As>>7+Cd`;
   - a pad panel: 16 squares in button-bit order, plus two stick boxes;
2. calls `gs_vsync`;
3. reads the PCRTC out with `gs_read_display`:
   - SMODE2 is interlaced FRAME mode;
   - DISPLAY1 has DW 2559, MAGH 3 and DH 895, which is libgraph's `2·448−1`;
   - the result is 640x448;
4. presents the frame;
5. pushes a test tone: 440 Hz, or 660 Hz while CROSS is held;
6. paces with `rg_pacer_hook`.

The title bar shows the pad word, both sticks, fps, the scale mode, fullscreen state, the
gamepad count, and whether a script is active.

```
rg-host-demo [--headless] [--frames N] [--screenshot out.png] [--input script.txt]
             [--config map.cfg] [--write-config map.cfg]
             [--scale linear|nearest|integer|stretch] [--fullscreen]
             [--unthrottled] [--mute] [--vsync]
             [--settings FILE] [--set id=value] [--preset original|default]
             [--write-settings FILE] [--overlay] [--window-shot out.png]
             [--menu up,down,accept,...,text:abc,press:key:F,motion:DX:DY]
```

`--settings/--set/--preset` go to the settings registry (SETTINGS.md); the demo's own
flags win over them. `--write-settings` writes the registry (every setting, commented).
`--overlay` opens the settings overlay at start, and `--window-shot` saves the last
presented window, overlay included. `--menu` opens it and applies a list of menu
commands, typed text, capture presses and relative mouse motion for a motion capture
(`motion:DX:DY`) first (`rg_host_menu_script`, SETTINGS.md); the title bar also shows the
prompt style (`rg_host_prompt_style`). A headless host has no events, but it still applies
settings changes in `rg_host_pump`, as a windowed one does.

`--headless` means no window, no audio device and no live input. It runs unthrottled, for
60 frames by default. At the end it prints `frames=… size=640x448 hash=<FNV-1a of the
frame> audio_frames=…`.

## Tests (`ctest -L host`)

The settings registry and the input-action layer have their own labels, `settings` and
`input` (SETTINGS.md, INPUT.md).

| Test | Checks |
| --- | --- |
| `host.pad_report` | Neutral pad; DS2 report bytes (active low, 0x79, stick order, pressure order); the game's decode gives back the word; input names. |
| `host.input_mapping` | Default keyboard map: buttons, sticks, opposite keys cancel, the `nkeys` bound. Gamepad: buttons, trigger threshold, full stick range, deadzone with rescale (exact value). Two gamepads merge; keyboard and gamepad together. |
| `host.input_config` | Parse: replace and unbind, multiple bindings, names with spaces, deadzone/threshold. 8 error cases, each with its line number. format→parse round trip (memcmp). Truncated format output. |
| `host.input_script` | `start_cross.txt` words and span; hex, octal, binary, `_`, case and single-VBlank forms; overlaps ORed; extra tokens ignored; empty range; the 32,636-entry limit at its edge; 7 error cases; `rg_input_script_pad`. |
| `host.script_determinism` | Two independent replays through a headless `rg_host`: 400 VBlanks of port 0/1 DS2 reports hash identically and match the table. Port 1 neutral. The blob layout. No script → neutral. |
| `host.script_vs_input_py.*` | `tools/trace/input.py` (run by Python) and the C compiler produce **byte-identical** table blobs for `start_cross.txt`, `script_edge.txt` and `demo_input.txt`. |
| `host.scaling` | 15 hand-computed rectangles (linear, nearest, integer including fallback and a 224-line source, stretch, square pixels, degenerate) and a ~12,000-case property sweep: inside the window, centred, 4:3 within rounding, integer heights. |
| `host.png_roundtrip` | Encode, then decode with an independent decoder in the test (chunk CRCs, zlib header, LEN/NLEN, Adler-32, filters 0–4) for 1x1, 37x23, 300x300 (multiple stored blocks) and 640x448. CRC-32/Adler-32 reference vectors. |
| `host.png_python_write` + `host.png_python_check` | The same PNG decoded by Python's `zlib`, every pixel compared. |
| `host.pacing` | Exact conversions (1 s, 1 ms, a 4e15-cycle overflow case). `rg_field_cycles` equals the kernel's `PS2K_FIELD_SUB` arithmetic for 14,286 values of k, and `RG_BUSCLK == PS2K_BUSCLK`. With a fake clock: 600 fields throttled land exactly on virtual time, with or without 5 ms of work per field; a 400 ms stall re-anchors once and the cadence is kept; a 100 ms stall is caught up; backwards time re-anchors; unthrottled never sleeps or reads the clock. With the real clock: 6 fields take at least 100 ms. Compile-time `ps2k_pacing_fn` type check. |
| `host.demo_headless` | Runs `rg-host-demo --headless --frames 40 --input demo_input.txt` twice: byte-identical PNGs and identical frame hashes. `pngcheck` decodes the PNG at 640x448 with at least 8 colours. **Control:** a script that differs only on the last frame gives a different screenshot, which proves scripted input reaches the frame. |
| `host.audio_device` | `rg_audio_device_pick` (exact, case, missing, empty); the overlay's choice stepping on `audio.device` (next, wrap, previous, a saved name not present, no choices = text only); headless: a name is harmless; on SDL's dummy video + audio drivers: a missing name falls back to the default (flagged), a present name (lower-cased) is opened, a REMOVED event for it rebinds to the default and pushes keep working, an ADDED event takes it back, "" returns to the default |
| `host.audio_focus` | `rg_audio_output_gain`; the registry rows (`audio.background` Original/default on, the four volumes live with Original 100); a dummy-driver host: mute only when unfocused and `audio.background` off, through direct calls and through pushed focus events + the registry |
| `host.png_corrupt_control` (`WILL_FAIL`) | One flipped pixel byte must be rejected by the test decoder. Proves the PNG check is armed. |

## Open issues

- **The demo runs below real time: about 32 fps, not 59.94.** It measured 23.7 ms per
  frame for the GS software rasterizer (one full-screen clear sprite, one triangle, about
  20 small sprites, at `-O1`) and 6.8 ms for `gs_read_display`. The host's own present
  costs 0.2�0.9 ms. The GS model is the correctness oracle, not the production renderer
  (PLAN D3), so this is expected. The pacer just never sleeps, and re-anchors once the lag
  passes 250 ms. The demo prints these per-stage timings when it exits.
- **Field length (resolved 2026-10-11).** `PS2K_FIELD_SUB` used to be 12300384/5 =
  2,460,076.8 bus cycles, which matched neither its own formula (BUSCLK·1001/60000 =
  2,460,057.6) nor PCSX2. It is now **2,460,060** bus cycles, PCSX2's BUSCLK/59.94
  (4,920,120 EE cycles per vsync in tools/trace), so virtual time lines up with
  reference traces. `host.pacing` pins `rg_field_cycles(1) == 2460060` and
  `rg_field_cycles(k) == k·PS2K_FIELD_SUB/PS2K_SUB`; 60,000 fields take 1001.000977 s.
- **Slow first configure.** On this machine SDL's configure checks took about 12 minutes,
  on the busy B: drive. Later configures are cached.

- **No interactive verification in CI.** Window, fullscreen, gamepad hot-plug and audio
  output are exercised only by running the demo by hand. The tests cover only the parts
  that are pure or headless.
- **Pressure is 0/255 only.** Analog triggers could feed L2/R2 pressure proportionally,
  but the DS2 face buttons have no host equivalent. Decide when the pad HLE lands, by
  checking what the game reads.
- **Deinterlacing.** The display read-out is a full FRAME-mode frame. If the game ends up
  presenting FIELD-mode fields (224 lines), the host scales them with the same 4:3 math
  (tested), but a weave or bob deinterlacer isn't written.
- **Pad HLE wiring (done 2026-10-12, RUNTIME.md "Pad").** The runtime's padman input
  source calls `rg_host_read_pad` with the VBlank from `cfg.game_vblank` (the kernel
  count until the game links), and padman's rumble hook calls the new
  `rg_host_rumble(h, port, small, large)` → `SDL_RumbleGamepad`.
- **Audio clock drift (done 2026-10-12).** The output regulator ("Audio") trims the
  playback rate by up to ±0.5 % on the smoothed queue error; simulated ±0.3 % drift for
  30 minutes stays within 30 ms of the target with no starve or drop.
- **Linux** builds of `rg_host` compile and link (i686 cross build, [LINUX.md](LINUX.md));
  not run yet. macOS hasn't been tried. Nothing here is Windows-specific.
