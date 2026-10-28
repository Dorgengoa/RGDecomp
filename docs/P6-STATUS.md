# P6 PC features: status inventory (2026-10-26)

What exists in the code today for every bullet of PLAN.md "P6 — PC features" (and the P6 part
of "Unlocked frame rate"). The goal is to assign the next lanes. Claims were checked against
the code, not only the docs. Line numbers are as of 2026-10-26 in the uncommitted tree.

**Census tool:** `python tools/settings_census.py -o census/settings.tsv --summary` parses the
registration tables (`src/settings/rg_settings_core.c`, `src/host/host_input.c`). For every
registered setting it writes id, type, default, Original value, flags, menu visibility and
the source lines that **read** it. A setting with zero readers has no effect. Run it again
after a lane adds settings. Today it reports 99 settings (35 of them bindings; the controls
lane added `input.overlay_chord` and `input.overlay_chord_hold` on 2026-10-26), 7
placeholders (the audio lane activated its 6 on 2026-10-26), 2 hidden, 2 gameplay. Every non-placeholder setting has at least one reader.
The only setting that is read but has no effect is `graphics.anisotropic`, and only in the
shipping exe (see below).

**Summary: 59 features: 34 done, 11 partial, 14 missing** (ray tracing and texture packs are
blocked by the plan).

Size: S = under a lane-day, M = 1-3 lane-days, L = more than that or needs research first.
"Run hash" means the state-trace gate: a non-gameplay option must leave the run hash and the
audio hash unchanged.

## Graphics

| Feature | Status | Evidence | Missing | Size | Dependencies / risk |
| --- | --- | --- | --- | --- | --- |
| Windowed, resizable | done | `display.window_mode`, `display.width/height` (rg_settings_core.c:60-69); `SDL_WINDOW_RESIZABLE` host_sdl.c:237 | | | |
| Borderless fullscreen | done | `display.window_mode=fullscreen`; F11 / Alt+Enter host_sdl.c:893 | | | |
| Exclusive fullscreen | partial | `window_mode=exclusive` uses the mode closest to the window size (host_sdl.c:347) | No resolution or refresh-rate picker: you get the desktop's closest mode to `display.width/height` | S | host_sdl.c (shared with the audio and controls lanes) |
| Monitor selection | partial | `display.monitor` INT 0..15 (rg_settings_core.c:70), host_sdl.c:398 | The menu shows a number, not display names. Indexes over the connected count are not clamped or reported | S | Needs a dynamic ENUM or a label callback in the registry |
| VSync | done | `display.vsync`, host_sdl.c:396; runtime.c pacer | | | |
| Frame cap / uncapped | partial | `display.frame_rate` original/30/60/120/144/uncapped (runtime.c:321), `display.pacing`, `display.interpolation` (runtime.c:330) | No 165/240 Hz or "match display refresh" values. Interpolation is opt-in: effects and 2D show the latest frame. The P6 frame-rate gate (logic identical at 30/60/120/144/uncapped/jittered over the corpus) has not been run as a matrix | M | **The interpolation lane owns this** (runtime.c, src/native/render). Don't touch it in parallel |
| Display changes revert unless confirmed | done | `RG_SETF_DISPLAY` trial, rg_settings.c:1303, rg_menu.c `change()` | | | |
| Internal resolution 1x-8x / match window | done | `graphics.internal_res` gpu_gfx.c:25 -> runtime.c:1785 `gpu_gfx_scale` | Sharpness of fonts and 2D at high scale not re-audited for the native renderer | | |
| Aspect 4:3 / 16:9 / 16:10 / 21:9 / auto (widened projection and culling, HUD and menu anchoring, movies pillarboxed) | done | `graphics.aspect`, `movie_aspect`, `ui_layout` (rg_aspect.c:86-91, rg_layout.c); WIDESCREEN.md stages 0-3, run hashes identical across aspects | (32:9 checked too) | | |
| Anti-aliasing (FXAA, SSAA 2-4x) | done | `graphics.antialiasing` -> nr_d3d11.cpp:2314, nr_vulkan.cpp PS_fxaa | MSAA left out on purpose (coverage is decided in the shader, rg_settings_core.c:37) | | |
| Downsampling filter | done | `graphics.downsample` -> nr_d3d11.cpp:2312 | | | |
| **Anisotropic filtering** | **missing (inert)** | `graphics.anisotropic` (default **16x**) -> `enh.aniso` (gpu_gfx.c:45). Only `gpu_core.cpp:1573` (rg_gpu, the old GS renderer) uses it. The RG_NATIVE_ONLY exe drops rg_gpu, and nr_dev.cpp / nr_draw.hlsl never read `enh.aniso` | Anisotropic taps in the native draw shader, or sampler `MaxAnisotropy` on both backends | M | src/native/render + nr_draw.hlsl: **conflicts with the interpolation lane**. Until it lands, the menu offers a live-looking option that does nothing |
| Texture filtering original / bilinear / nearest | done | `graphics.texture_filter` -> nr_dev.cpp:2535, 3229 | | | |
| Bloom / depth of field / motion blur toggles | missing | placeholders (rg_settings_core.c:130-138). The `effect_class` hook is in gpu_core.cpp:1370 (old renderer, returns -1); the native renderer has none | Identify the game's effect passes (decomp + GS dump), classify them in nr_dev, then offer original / enhanced / off | L | Native renderer files (interpolation lane). "Off" must stay presentation-only |
| Draw distance / LOD bias | missing | `graphics.lod_bias` placeholder, 0 readers | Engine research: where LOD and far clip are decided, and whether culling feeds logic | L | High run-hash risk: culling can feed AI or visibility logic |
| Shadow resolution | missing | `graphics.shadow_res` placeholder, 0 readers | Shadows are plane-projected (`DrawPktBuildPlaneShadowMtx`); "resolution" may not apply. Re-scope or drop | M | |
| Brightness / gamma | done | `graphics.gamma`, `graphics.brightness` -> nr_d3d11.cpp:2344 | | | |
| Sharpening, CRT / scanline filter | done | `graphics.sharpen`, `graphics.output_filter` -> nr_d3d11.cpp:2321, 2351 | | | |
| Texture replacement packs + dump tool | missing | nothing in src/; `tools/assets/gaiji.py` is the only texture rebuilder | Dump-by-hash tool, then a loader in the asset override layer | L | Depends on P7 mods (**on hold**, USER) |
| FPS counter (extra) | done | `display.fps_counter` host_sdl.c:437 | | | |
| Graphics API D3D11 / Vulkan (extra) | done | `display.backend` [restart], runtime.c:1472 | | | |
| Ray tracing (`graphics.raytracing`) | missing | no setting, no code | Everything | L | **Blocked by the plan:** after the D9 native end state and the P5 whole-game gate |

## Controls

| Feature | Status | Evidence | Missing | Size | Dependencies / risk |
| --- | --- | --- | --- | --- | --- |
| Input actions independent of PS2 buttons, adapter to the pad report | done | `k_act` 34 actions (host_input.c:25), `rg_actions_from_settings` host_input.c:509 | | | |
| Keyboard / mouse / gamepad rebinding, several bindings per action, in the menu | done | `input.bind.*` (34), `RG_BIND_MAX 8` (rg_input.h:113); binding editor rg_menu.c:347 (capture key / button / axis / mouse motion, remove, reset) | | | |
| Deadzones, sensitivity, per-axis inversion | done | `input.deadzone_*`, `sensitivity_*`, `invert_*` (host_input.c:430-444) | | | |
| Mouse camera (deterministic) | done | `input.mouse_look` + yaw/pitch scale and invert (host_input.c:450-460, 1088) | | | |
| Keyboard walk modifier | done | `input.bind.walk` | | | |
| Stick dead-zone compensation (gameplay) | done | `input.stick_compensation` GAMEPLAY, Original off (host_input.c:467) | | | |
| Rumble (new optional feature) | missing | `input.vibration` hidden; the US build never vibrates (CONTROLS-AUDIT.md section 7) | Would need invented triggers | M | Low value. Skip unless asked |
| Gamepad hotplug, switching devices mid-play | done | host_sdl.c:513/524 `pad_added/removed`, roster activity; ctest `input.hotplug` | | | |
| Prompts that match the device | partial | `prompts.style` live (host_sdl.c:501); 8 gaiji glyphs swapped (PROMPTS.md); **the settings overlay's hints follow the device in use** (2026-10-26: PlayStation / Xbox / Nintendo / keyboard labels from the bindings, model names for PS4/PS5/360/Steam Deck; the port's prompt tags `[accept]` `[back]` ... `[start]` `[select]` `[dpad]` `[ls]` in the overlay text, INPUT.md "Prompts in the settings overlay") | Wide keyboard labels in the game font; prompts baked into other textures (PAUSE screen Square). START / SELECT words: scoped, none to remap (`tools/prompts/msgscan.py`: the message files never name them) | M | Font overrides (`FontFindGaijiMetric_26f8c0`). Presentation only |
| Full controller navigation of all menus, Steam Deck | done (needs a real-pad try) | game menus are native; the overlay menu has full gamepad commands and an on-screen keyboard for text (rg_menu.c); **the overlay opens from any pad with a held chord**: Back + Start (Select + Start) for 1 s, `input.overlay_chord` / `input.overlay_chord_hold`, rebindable, never reaches the game's pad report (INPUT.md "Opening the settings overlay with a gamepad"; ctests `input.chord_*`) | Tried only through the pure tests: a person must try it on an Xbox pad with the Game Bar, a DualSense, a Switch Pro and a Steam Deck, and on the PAUSE / map screens. Cost: a lone Start / Select press reaches the game 100 ms late (live input only) | | host_input.c (`rg_chord`), host_sdl.c `overlay_input` / `live_snapshot` |
| Pressure-sensitive button audit | done | CONTROLS-AUDIT.md (the game reads no pressure) | | | |
| Camera convention, DS2 stick range, 1/2 players, tap latch (extras) | done | `input.camera_convention`, `stick_ds2_range`, `players`, `min_press_fields` | | | |

## Audio

| Feature | Status | Evidence | Missing | Size | Dependencies / risk |
| --- | --- | --- | --- | --- | --- |
| Master volume | done | `audio.master_volume` -> `rg_host_set_volume` host_sdl.c:433 (after the mix) | | | |
| Music / effects / voice / movie volumes | done (needs a by-ear try) | 2026-10-26 (p6 audio): `audio.music/effects/voice/movie_volume` live, read by runtime.c `audio_mix_update`; the engine's presentation mix (`ra_present.c`, NATIVE-AUDIO.md "Source volumes") beside the unchanged model mix: music = SQ notes + BGM / jingle streams, effects = the game's SE key ons + other streams, voice = event voice / LiveTalk streams, movie = bus 0 stream; run hash and audio hash identical at 4 volume mixes (`tools/native/audio_volume_gate.py`); ctest `audio.source_gain` | Battle shouts played from SE banks count as effects (no category in the engine's data); the HLE-oracle builds push the model mix | | |
| Output device selection | done (needs a real-device try) | `audio.device` live (no restart): opened by name, LEFT / RIGHT in the overlay steps through the devices present (`rg_menu_set_choices`), missing -> the default, taken again when it appears (HOST.md "Audio devices and focus"); ctest `host.audio_device` (SDL dummy driver) | Friendly "System default" label for "" (the row shows "(empty)") | | |
| Hot-switching | done (needs a real unplug) | the host's own stream, rebound on a device change or `SDL_EVENT_AUDIO_DEVICE_REMOVED` with the queue kept (no re-prime, the game never waits on the device); the default-device path follows the system default (SDL) | Tried only with injected events on the dummy driver | | |
| Keep playing when unfocused | done | `audio.background` live, Original and default on (keep playing, as the console); off mutes the stream gain on `SDL_EVENT_WINDOW_FOCUS_LOST` (host_sdl.c); ctest `host.audio_focus` | Pause-on-focus-loss (a game pause, not an audio setting) not built | | |
| Audio buffer latency (extra) | done | `audio.latency_ms` host_sdl.c:435 | | | |

## Saves and quality of life

| Feature | Status | Evidence | Missing | Size | Dependencies / risk |
| --- | --- | --- | --- | --- | --- |
| Crash-safe writes | done | src/native/saves/mccard.c (tmp + MoveFileEx WRITE_THROUGH; `RG_MC_DURABLE` fsync, mccard.c:179); SAVES.md section 3 | | | |
| Backups | done | `backup_keep` 5 (mccard.c:421), snapshots per overwrite | Not a setting (no `saves.*` keys); restore only through `ps2card.py restore` | S | |
| Named save slots with metadata | partial | retail save UI and slots; `card1.txt` index with icon.sys titles | No port-side names or a save browser. The retail slot list may already be enough: decide whether this is needed | M | |
| PCSX2 memory-card import | partial | `tools/saves/ps2card.py import Mcd001.ps2` (CLI) | Not in the game or the menu; no `--import-card` launcher flag | S | |
| Saves folder | missing | `RG_SAVES` / `--saves` only (SAVES.md section 3) | `saves.dir` setting ([restart]) | S | |
| Fast loading | done | the native FS has no latency model (NATIVE-FS.md:129) | | | |
| Event-scene / FMV skip | done (retail) | Start -> Skip (events); movies: Triangle skips "when allowed" (CONTROLS-AUDIT.md:226) | `gameplay.skip_seen_movies` placeholder: only matters for movies retail won't skip. Low priority | S-M | |
| Text speed (gameplay) | missing | `gameplay.text_speed` placeholder, GAMEPLAY, 0 readers | Find the message typewriter step in the decomp; an override that is labelled as gameplay | M | Changes the run hash by design when on; must be off in Original |
| Battle speed-up (gameplay) | missing | no setting | Fixed-step tick multiplier for battles (several logic ticks per VBlank) | M-L | Gameplay option; interacts with pacing and interpolation (runtime.c, interpolation lane) |

## Accessibility

| Feature | Status | Evidence | Missing | Size | Dependencies / risk |
| --- | --- | --- | --- | --- | --- |
| Subtitle and UI scale | missing | no setting; rg_layout.c already transforms 2D (anchoring) | A scale factor on the layout transform for text / message windows, or a font-scale override | M | rg_layout.c (the widescreen code). Wrapping must stay the game's |
| Reduced camera shake | missing | shake is applied in the draw task to a camera copy: `TaskUpdateDrawInfo_2f6ff0` (WIDESCREEN-AUDIT.md:35, FRAMERATE-AUDIT.md:68) | Scale the shake offset in that override | S | Probably presentation-only. **Prove it with the run hash** (the shaken camera may feed culling) |
| Reduced flashing | missing | no setting | Classify flash / full-screen white passes (shares work with the screen-effects row) and clamp them | M-L | Native renderer (interpolation lane) |
| Colour-blind-friendly markers | missing | no setting | Audit which markers rely on colour alone (minimap, targets) | M | Probably texture or CLUT overrides |
| Remapped prompts throughout | partial | = the Controls "prompts" row | same | | |

## Gates and the Original preset

| Feature | Status | Evidence | Missing | Size | Dependencies / risk |
| --- | --- | --- | --- | --- | --- |
| "Original" preset | done | `RG_SETF_HAS_ORIGINAL` values; `--preset original`; settings test: gameplay flags off in Original | | | |
| Original vs every non-gameplay option: identical logic | partial | per-feature run-hash checks (widescreen, interpolation, gfx: GPU.md:1356, NATIVE-RENDER.md) | No matrix runner: every non-gameplay, non-placeholder setting at a non-Original value, over the boot fixtures and the golden route, comparing run and audio hashes against Original | S-M | tools/ only. **Should exist before more options land** |
| Frame-rate gate | partial | interpolation passes keep the run hash (NATIVE-RENDER.md "Interpolated presentation") | The full corpus at 30/60/120/144/uncapped/jitter | M | Interpolation lane |
| Every setting changeable with keyboard alone and with gamepad alone | partial | the menu model covers every visible type: steps, the binding capture, the on-screen keyboard for STRING (rg_menu.c:403, 541); `system.screenshot_dir` and `audio.device` can be entered with a gamepad | (a) Done 2026-10-26: a gamepad alone opens the overlay with the held chord (Controls); the chord row itself takes only gamepad buttons, so with the keyboard alone it can be reset or emptied, not extended. (b) Hidden on purpose: `system.throttle` (testing), `input.vibration` (no effect). (c) `display.monitor` is reachable but meaningless without names | S | Controls lane |
| Settings outside the Original preset | note | `input.min_press_fields`=2, `input.stick_ds2_range`=on, `input.players`, `audio.latency_ms` and the window size have no Original value, so Original uses the defaults | Decide whether `min_press_fields` (it stretches sub-field taps to 2 fields) belongs in "original". Scripts bypass it (INPUT.md:389), so verification runs are unaffected | S | |

**Options-matrix gate (2026-10-26 (p6 optgate), interrupted for a restart):** `tools/p6/optgate.py`; resume note and findings so far in `out/optgate/RESUME.md`.

## Recommended lane order

Rules for all lanes:

- **Register new settings in the lane's own module table**, the way `rg_actions_register_settings`
  does, or only flip a `PH` flag in `rg_settings_core.c`. That way two lanes never rewrite the
  same table.
- Every lane re-runs `tools/settings_census.py` (a new setting must have readers) and the
  options-matrix gate once it exists.
- Nothing may change the Original run hash or audio hash. Gameplay options carry `GP` and are
  off in Original.

**Wave 1 (now, 3 concurrent, disjoint files):**

1. **Audio lane** (done 2026-10-26 except the by-ear / real-device tries, history
   "2026-10-26 (p6 audio)"): music / effects / voice / movie volumes in the native mixer (after the audio
   hash point), output device list + selection + hot-switch, and mute-when-unfocused.
   Files: `src/native/audio/*`, `src/host/host_audio.c`, and the focus events in `host_sdl.c`.
   Clears 4 placeholders plus 2 partial rows. M.
2. **Controller access and prompts lane** (done 2026-10-26 except the real-pad try, history
   "2026-10-26 (p6 pad)"): a fallback chord that opens the settings overlay
   (Steam Deck, Xbox pads, no Guide); device-matched hints inside the overlay; port
   extension tags and the START / SELECT word remap if the message dump is cheap. Files:
   `src/host/host_input.c`, `src/settings/rg_menu.c`, prompt / font overrides. This lane
   touches `host_sdl.c` only in `overlay_input`; agree on that with lane 1. S-M. This is the
   P6 gate's gamepad-alone condition.
3. **Options-matrix gate lane (tools only):** `tools/` runner. It reads `census/settings.tsv`
   and sets every live non-gameplay setting to a non-Original value (one at a time, then all
   at once), runs the boot fixtures and the golden route headless, and diffs the run and
   audio hashes against `--preset original`. Also settles the `min_press_fields` /
   Original question. S-M. It touches no src.

**Wave 2 (after wave 1, or when a slot frees up):**

4. **Display lane:** an exclusive-mode resolution and refresh picker, display names for
   `display.monitor`, and the `saves.dir` setting. Files: `host_sdl.c`. Start it after lane 1
   is done with that file. S-M.
5. **Saves QoL lane:** `saves.*` settings (`dir`, `backup_keep`), in-game or launcher PCSX2
   import (`--import-card`), and a decision on named slots. Files: `src/native/saves/mccard.c`
   and a new settings table. S-M.
6. **Accessibility lane:** reduced camera shake (an override of `TaskUpdateDrawInfo_2f6ff0`,
   proven with the run hash) and UI / subtitle scale on `rg_layout.c`. Colour-blind work
   comes after an audit. M.

**Wave 3 (after the interpolation lane lands; native renderer files):**

7. **Renderer features lane:** anisotropic filtering in the native renderer (today the menu
   offers it with default 16x and it does nothing), more frame-cap values (165 / 240 / match
   refresh), then classification of the screen-effect passes (bloom / DOF / motion blur /
   flashing). M, then L.
8. **Gameplay QoL lane:** text speed, then a battle speed-up. Both labelled `[gameplay]`. M-L.
9. **Research spikes:** LOD bias and shadow resolution (re-scope or drop). L.

**Blocked or on hold:** ray tracing (after D9 + the P5 gate), texture packs and the dump tool
(P7 mods, on hold), rumble (the game never vibrates; only if asked).
