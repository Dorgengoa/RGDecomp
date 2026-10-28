# Bring-up history (archived from BRINGUP.md on 2026-10-19)

The full running log, verbatim, as BRINGUP.md held it before consolidation: the early
boot sections (fixes 1-13, first lockstep divergence, diagnostics), every dated checkpoint
(newest first, e.g. "2026-10-19 (c)", "2026-10-18 (g)") and the user play-test logs.
Other docs that cite "BRINGUP.md (x)" mean the entry with that heading here.
The current status and open items are in ../BRINGUP.md.

---

# Boot bring-up (`rg-game`, headless)

Running log of the boot bring-up after the first link (LINK.md). Each fix below has its
class (stage rule, override, or port module bug) and the evidence for it. State as of
2026-10-12, interim snapshot `b09ccfa1`.

**Re-pinned to the published decomp `675c07fe` (2026-10-12, SNAPSHOT-CLEAN.md):** the
regression below still holds on a fresh `build/clean-i686`. No input: TITLE at field 39,
title movie at field 287 and 1067, menu at field 1500, 4000 fields without a fault. Golden
input: NORMAL at field 2107 (vbl 2070), 6000 fields without a fault. The STATUS lines are
identical, field by field, to the interim build's.

**Start at a milestone instead of power-on** (docs/TEST-FIXTURES.md): save states of
the golden route at the title menu (field 1500), the first field after the FMV (8000)
and the first battle (23000) load in about a second into the same build:
`python tools/fixtures/run_from.py battle --run 300 [-- --shot 23100:out/x.png]`
(regenerates the set, one ~8 min power-on run, when the exe changed). Plain rg-game:
`--save-state FIELD:FILE` / `--load-state FILE` (`--fields` stays absolute).

## 2026-10-26 (play-test 1026a): play-test build 1026a (shadow bands, hitch2, rpkt, interp3, p6 pad, p6 audio, x64 shared edits)

USER request.  Built only through `tools/playtest/build_playtest.py --tag 1026a` (build dir
`build/pt1026a-i686`, gate dir `out/regress1026a`).  The dir was configured and part-built by an
aborted 09:54 attempt from an older tree (its summary kept as `summary-aborted-0954.tsv`, its
manifest `out/regress1026a/1026a-manifest.txt`): reconfigured and `ninja -t clean`ed, then a full
rebuild from the current tree (25,932 steps, 0 errors, ~14 min at -j8).  Not committed.

- **Source manifest** `out/playtest/1026a-manifest.txt` (`srcmanifest.py write` at 21:13, before
  the configure): HEAD 0a6381a2, 316 tracked files changed + untracked, 1,087 files hashed.
  `srcmanifest.py compare` after the build and again after all gates / ctest: 0 changed, 0 added,
  0 removed.  Contents: hitch2 (lens-flare probe lag, adaptive audio cushion), rpkt (remembered
  packets, nr_game_ptr), shadow bands (gs_uv16 in nr_draw.hlsl), interp3 (composite pairing),
  p6 pad (overlay hold chord, device prompts), p6 audio (source volumes, device switching,
  background audio), the x64 lane's shared-source edits.
- **Gates** (exe `out/regress1026a/rg-game.exe`, run from Git Bash in three batches for the 2 h
  shell limit): ingest --check 0 problems; configure = play-test config; regen --check 300 PASS,
  power-on to 31,700 run hash **b0632cdfa80153de** (save2 card differed -> restored from
  `out/regress1026a/save2_backup`, `diff -r` identical, re-checked after the render gate and ctest);
  verify 8/8; bootcheck --all 29/29; mapcheck 5/5 DRAWN; link_audit --forbid all --extra
  rg_ps2_hwbus PASS; addr_census --check PASS (0 / 0); insectrun title, gameover, factory,
  factory_place PASS; shop_close PASS (D3D11 + Vulkan); render_gate (D3D11, oracle twin, tag
  pt1026a, `out/nrender/runs/gate_pt1026a.txt`) PASS: route 24 fields PSNR min 31.31, failing 0,
  run hash emu = native **ab389a3d1d0232e0**; boot fixtures 8/8 PASS with equal hashes; mapcheck
  5 DRAWN; save2 close-up x3 38.58 / 38.64 dB.
- **ctest** (build dir, all targets built after the gates; rg-game.exe unchanged by it):
  `-j2 -LE fixtures` 755/755 (7 environment skips as before), `host.audio_reg` passed;
  `-j1 -L fixtures` 13/13 (incl. `fixtures.shadowbands` / `_control`, run with Git's sh on PATH).
- **Installed** `out/playtest/rg-game-1026a.exe` + `rg-game-1026a.map`; play.bat /
  play-from-save.bat / play-test-save.bat point at it; player notes `out/playtest/1026a-NOTES.txt`
  (what is new, what to try).  Smoke (windowed from out/playtest, 1,600 fields, D3D11 RTX 3080)
  PASS, run hash c1d233bd0e9574b3 (= 1025c's smoke).  The options gate (tools/p6/optgate.py) was
  not run (not asked).  Not play-tested yet.

## 2026-10-26 (p6 audio): music / effects / voice / movie volumes after the hash point; output device by name with hot switch; mute when unfocused

Lane "p6 audio" (P6-STATUS.md wave 1 item 1). Build `build/p6audio-i686`. Not committed, not
play-tested (no play-test exe built).

- **Source volumes** (NATIVE-AUDIO.md "Source volumes"): `ra_present.c` (new, HOST for save
  states) renders a presentation mix beside the unchanged model mix in `ra_mix.c bus_tick`
  while any gain is not 1: per-source parts added as `(g - 1) * part` (bit-exact at unity), its
  own reverb copies, a mirrored FIFO; runtime.c folds the model frames into the run hash and
  pushes `rg_audio_runtime_present()`. Sources found in the code: music = SQ notes
  (`v->seq`) + PCM ports playing `wav/BGM_MWV_NEW` (stream channel 0, `BgmPlayTrack_2075e0`) or
  `snd2/mwv` jingles (`StreamPlayMwv_207340`); effects = the game's SE key ons + other streams;
  voice = `wav/<lang>/EVnn-nnnn` (`EventVoicePlay_24efd0`) and `LiveTalk`; movie = the bus 0
  stream. The port -> path link: the stream manager's channels (`GetStreamMgr_207ea0`, name at
  +0, slot at +0x80), read in `SoundStreamSlotSendToIopMaybe_1bd760` before each block. Golden
  route source census (`$RG_AUDIO_SRCLOG`): 5 BGM + 1 jingle starts = music, 41 event-voice +
  4 LiveTalk lines = voice, no other stream paths.
- **Device**: the host's own SDL stream bound to a logical device opened by name
  (`audio.device`, live); missing -> default (flagged), re-taken on ADDED; REMOVED for our
  device -> rebind to the default, queue kept; overlay LEFT / RIGHT steps through the devices
  (`rg_menu_set_choices`, additive in rg_menu.c/h). **Focus**: `audio.background` (Original /
  default on = keep playing) off mutes the stream gain on focus loss.
- Settings: the 6 audio placeholders activated in `rg_settings_core.c` (flags / help only;
  `audio.background` gets Original on, `audio.device` loses RS); census 99 settings, 7
  placeholders, no setting without a reader.
- New tool `tools/native/audio_volume_gate.py` (golden route at Original + 3 volume mixes,
  compares run hash and the audio part of `$RG_HASH_LOG`, prints the stream source census).
- Shared-file edits: host_sdl.c (audio device / focus only: struct fields, create / destroy,
  apply_settings audio rows, 2 event cases, the audio section; overlay_input untouched),
  rg_menu.c/h (choice hook, additive), runtime.c (`audio_mix_update`, the push), ss_map.c (1
  row), rg_settings_core.c (audio rows), host.h, host_audio.c.
- **Gates** (exe `build/p6audio-i686/rg-game.exe`): run hash power-on to 31,700
  `b0632cdfa80153de` and audio part `513dbc56cc877a2c` identical at Original and at 3 volume
  mixes (`out/p6audio/gate.txt`); regen --check 300 rc 0 (save2 card differed -> restored from
  `out/p6audio/backup`, verified identical); verify 8/8; bootcheck --all 29/29; mapcheck 5/5
  DRAWN; camprobe ch01_salgin / ch05_factory eye = retail (-3328.2, 97.0, -1894.9) /
  (6589.3, -644.1, 5831.7); ctest -j2 -LE fixtures 755/755 (new: audio.source_gain,
  host.audio_device, host.audio_focus), -j1 -L fixtures 12/12; D3D11 render gate
  (`out/nrender/runs/gate_p6audio.txt`): route x1 24 fields PSNR min 31.31, failing 0, run hash
  emu = native `ab389a3d1d0232e0` (= the shadow / hitch2 gates), 8 boot fixtures PASS with equal
  hashes, mapcheck 5/5, save2 close-up x3 38.58 / 38.64 dB. (The save2_battle2 native run sat at
  0 CPU for ~2 h: it was waiting in `rg_slots.c` for a machine slot held by two other lanes'
  runs, not a hang; it ran as soon as they exited.)
- **Needs the user (by ear / real hardware):** each slider during a voiced event scene, a battle
  (SE vs BGM), an FMV; a device change in the overlay while sound plays, and unplugging a USB /
  Bluetooth headset mid-play; focus loss with "Play audio when unfocused" off.

## 2026-10-26 (p6 pad): the settings overlay opens from any gamepad (held Select + Start); overlay prompts follow the device

P6 wave 1, lane 2 (docs/P6-STATUS.md "Controller access and prompts lane").  Build
`build/p6pad-i686` (play-test configuration, via `tools/playtest/build_playtest.py --steps
configure,build,snapshot`); gate exe `out/p6pad/gates/rg-game.exe`; logs `out/p6pad/`.  Not
committed, no play-test exe.

- **Hold chord** (docs/INPUT.md "Opening the settings overlay with a gamepad"): Back + Start
  (Select + Start / View + Menu / Create + Options / Minus + Plus) held 1 s toggles the
  overlay, from any pad, so Xbox pads (Game Bar takes Guide, no touchpad) and the Steam Deck
  (Steam takes Guide) can reach the settings without a keyboard.  `rg_chord` (pure, per pad
  slot) holds the chord's buttons back from the game's pad report while they are pressed,
  held and released; a lone Start / Select reaches the game after a 100 ms grace (a tap
  inside it is delivered right after the release, never lost).  Settings
  `input.overlay_chord` (binding list of 0-4 pad buttons, rebindable in the menu's binding
  editor, empty = off) and `input.overlay_chord_hold` (0.5-3 s), Menu controls page,
  registered in host_input.c's table, Original = default (live input only).
- **Overlay prompts** (INPUT.md "Prompts in the settings overlay"): the menu's hint lines are
  templates with the port's own tags (`[accept]` `[back]` `[prev]` `[next]` `[toggle]`
  `[start]` `[select]` `[dpad]` `[ls]` `[rs]` `[cancel]`), filled each pump while the overlay
  is open from the bindings and the device in use (`prompts.style`, auto = last used):
  PlayStation / Xbox / Nintendo / keyboard labels, model names for PS4 / PS5 / Xbox 360 /
  Steam Deck.  The capture prompt names the right cancel button.
- **Message-word remap: scoped, nothing to do.** `tools/prompts/msgscan.py` (new) scans every
  DATA archive file and pack entry: the English message `.txt` files never say START or
  SELECT (one debug memory-card viewer string); the only controller words are
  "DUALSHOCK(R)2 analog controller" and "left and right directional buttons" (not-connected
  message, Insectron versus setup).
- **Tests:** new `rg-chord-tests` (`tests/settings/chord_tests.c`): `input.chord_settings`,
  `chord_no_leak`, `chord_lone_press`, `chord_rebind`, `chord_hotplug`, `overlay_prompts`,
  control `chord_control` (WILL_FAIL), and `input.chord_host` + control
  `chord_host_control`: the real host_sdl.c wiring with an **SDL virtual gamepad** in a
  small window, real time (opens at 0.95-1.4 s, closes, 0 Select / Start reads in ~250).
  `settings.menu_keyboard` edits the chord row by Remove (it takes no keys).
- **Gates** (exe `out/p6pad/gates/rg-game.exe`): regen --check 300 PASS (save2 card differed
  -> restored from the backup, re-checked equal: 5 files), power-on to 31,700 run hash
  **b0632cdfa80153de**; verify 8/8; bootcheck --all 29/29; mapcheck 5/5 DRAWN; camprobe
  ch01_salgin eye (-3328.2, 97.0, -1894.9), ch05_factory (6589.3, -644.1, 5831.7) = retail;
  ctest -j2 -LE fixtures **752/752** (8 skipped as before) + -j1 -L fixtures 12/12
  (`fixtures.shadowbands` / `_control` need Git's `sh` on PATH: they fail to start from a
  PowerShell ctest, pass from Git Bash; save2 card unchanged afterwards); D3D11 render gate (`tools/native/render_gate.sh`,
  tag p6pad) route 24 fields PSNR min 31.31, failing 0, run hash emu = native
  **ab389a3d1d0232e0**; 8 boot fixtures PASS with equal run hashes; mapcheck 5/5; save2
  close-up x3 38.6 dB.
- **Shared files touched:** `src/host/host_sdl.c` (rg_host fields `chord`,
  `menu_prompt_prev`; one line each in create, `apply_settings`, `pad_removed`,
  `live_snapshot`; `overlay_input`), `tests/settings/settings_tests.c` (menu_keyboard: the
  chord row), `tests/settings/CMakeLists.txt`, `tools/settings_census.py` (BINDING defaults
  and Original values), `tools/playtest/build_playtest.py` (render gate: Git's usr/bin on
  PATH, it failed from PowerShell with "grep: command not found").  New:
  `tools/playtest/vcrun_build.py` (cmake --build / ctest in the MSVC x86 environment),
  `tools/prompts/msgscan.py`.  Census rerun: 99 settings (35 bindings).  The audio lane
  added choice lists to `rg_menu.[ch]` (`rg_menu_set_choices`) while this ran; both
  changes coexist (not in this lane's gate exe).
- **Needs a person with real pads:** Xbox (Game Bar on), DualSense, Switch Pro, Steam Deck in
  Steam Input; the chord on the PAUSE and map screens; whether the 100 ms delay on a lone
  Start / Select is noticeable.

## 2026-10-26 (interp3): composite calls paired by their parts (battle posed 75 -> 92 %); smoothness check; present thread measured; Vulkan zero-copy counter is fine

Lane "interp3" (BRINGUP "Start here" items 3 and 5; user priority: smooth core gameplay before
P6).  Build `build/interp3-i686`; exes `out/interp3/exe/base` (the tree before the pairing change,
with the census fields), `exe/s1` (pairing), `exe/s2` = gate exe `out/interp3/final` (+ present-log
columns, trace, window-shot knob).  Not committed, not play-tested, no play-test exe.

1. **Unpaired composite calls** (NATIVE-RENDER.md "13c").  Census tool
   `tools/native/interp_groups.py` over the `RG_INTERP_DEBUG=1` group lines (new fields `ks` /
   `kp`: the key's groups this / previous frame).  ch07_rosa battle, simulated 144 Hz: of 10,302
   group passes 16.3 % had no pair (11.3 % "surplus", 5.0 % "key new"), 8.5 % failed a check (of
   them 5.1 % are not character composites: a 256 x 256 render-to-texture).  Cause: the pairing key
   was (work target, destination) as frame tokens, and each character's view of the work buffer
   is a target the frame creates (token = creation ordinal), so the tokens shift when a view comes
   or goes.  Fix (`nr_iprec.cpp` place_plan): a group signature from its parts (device mesh id +
   index count, order-free); frame-wide greedy pairing by box distance, same signature and
   destination first, then per key as before (`RG_INTERP_ZSPAIR=0` = old).  **Posed: battle 7,752
   -> 9,516 (75.2 -> 92.4 %), unpaired 1,674 -> 127; Salgin walk 23,471 -> 24,971 of 27,257 (86.1 ->
   91.6 %), unpaired 1,706 -> 230**; of the character composites 98.6 / 97.0 % are posed.  Images
   (same exe and state, ZSPAIR 0 vs 1): step judder isolated 0.34 -> 0.21, real 0.35 -> 0.26;
   switch ratio real 1.52 -> 1.39 (isolated 1.18 both); pops 0.  Run hash on = off (battle
   88081d075183d936, walk 555dcdd095e9a8ba).
2. **Smoothness check** (`RG_INTERP_TRACE=path` in nr_interp.c, `tools/native/interp_trace.py`;
   runners `tools/native/interp3_battle.sh` (headless battle: census + trace), `interp_window.sh`
   (real window)).  Per present: outcome, alpha, displayed camera and up to 16 objects; the checker
   finds repeats / jumps / backward steps, the switch ratio and the share of motion at game-frame
   switches against a snap control from the same trace, cut frames, resets.  Headless (exact
   simulated clocks): battle 120 / 144 / 240 Hz switch ratio 0.99 / 1.00 / 1.00, motion at
   switches 24.4 / 20.2 / 12.2 % (= 1 / presents per frame; snap 100 %, ratio 4.3 / 4.3 / 13), no
   repeats, jumps 0 / 0 / 0.23 %; Salgin walk + pan 144 Hz the same (repeats 0.3 %); **cuts**:
   battle_won + 2,400 fields (victory -> field) 3 cut frames, their 15 presents shown as recorded,
   largest object step at a cut 376 units vs largest camera move an interpolated pass spanned 3.6
   (nothing interpolated across a cut), run hash on = off (cd246d89fb098a43).  All PASS.
   **Real window (144 Hz panel, D3D11 / Vulkan, vsync on / off, uncapped):** not shown -- on the
   shared machine (two other lanes' rg-game runs) the game ran below real time with interpolation
   on (17-19 ms per field, logic 26-30/s, 21-28 presents/s), so every present slot found a phase
   owed and almost none fell between phases (motion at switches 94-100 %).  The traces themselves
   were clean (no backward model steps, no repeats).  To redo on a quiet machine:
   `tools/native/interp_window.sh TAG EXE STATE 5900 144 d3d11:144:1 vulkan:144:1 d3d11:uncapped:0`.
3. **Present on the game thread** (NATIVE-THREADS.md "3h.2").  `RG_PRESENT_LOG` gains
   `present_ms` / `window_ms`; `tools/native/present_thread.py` joins it with `RG_FIELD_TIMES`.
   Windowed battle, D3D11 144 vsync, same exe and state: interpolation off 51.4 presents/s at 3.9 ms
   per present; on 29.5 /s at 20.3 ms (13.7 the window's present): the interpolated present waits
   for the GPU to finish the pass it just queued, and with it the game thread exceeds a phase's
   budget (17-19 ms per field).  Prototype `RG_INTERP_PIPE=1` (pass + compose queued on the worker,
   presented at the next present, like the overlapped field present): 17.5 ms per present, all of it
   now the worker / GPU wait, 28.8 /s, 33 % repeated images uncapped -- no gain, **removed**.  So a
   present thread is not the fix (and SDL's renderer stays on the main thread); the pass's cost on
   the worker / GPU is, to be judged on a quiet machine.
4. **Vulkan zero-copy FPS counter / black grabs** (NATIVE-VULKAN.md "Results 2").  In-process
   read-back only (`RG_WINDOW_SHOT_HOST=1`: host_sdl.c takes the window shot after the counter;
   `tools/native/vkshot.sh`): at power-on fields 600 / 840 / 1,200 / 1,560 / 1,800 / 2,400 the
   Vulkan zero-copy back buffer carries the detailed counter line and is pixel-identical to D3D11
   below it (600 / 840 are logo fades, ~95-98 % black in both).  Code read: the frame is released
   after `SDL_FlushRenderer` (submit + queue wait), overlay and counter drawn in a LOAD pass on the
   same image.  No port bug found; the grabs were Desktop Duplication's view of a flip-model window.
   Not tested: what the monitor shows to a person (no screen capture by rule).

Gates (exe `out/interp3/final`, script `out/interp3/gates.sh`): regen --check 300 exit 0 (the
save2 card differed -> restored from the backup, verified equal) + verify **8/8** (battle + 300
ad41eb7c5ccf63f7 as before); power-on to 31,700 **b0632cdfa80153de** (= reference); bootcheck --all
**29/29**; mapcheck **5/5 DRAWN**; camprobe ch01_salgin / ch05_factory eye = retail; ctest -j2
754/755 (7 skipped as usual), the one failure `fixtures.shadowbands` a timeout under load that
passes alone (with its control, 110 s); render gate (D3D11, oracle `out/interp3/final/rg-game-oracle.exe`)
x1 route 24 fields PSNR min 31.31, bad max 0.91 %, failing 0, **run hash emu = native
ab389a3d1d0232e0**; 8 boot fixtures PASS with equal run hashes (34.40 / 34.39 / 38.25 / 37.81 /
36.19 / 35.29 / 45.22 / 39.52 dB); mapcheck 5 / 5; save2 close-up x3 38.58 / 38.64 dB.  The gate exe
is a snapshot: the shared tree has since taken other lanes' edits.

Shared files touched (all small, nothing runs differently with interpolation and the env knobs
off): src/runtime/runtime.c (`present_start` + two present-log columns), src/host/host_sdl.c
(`RG_WINDOW_SHOT_HOST`), src/native/render/nr_interp.c (`RG_INTERP_TRACE`),
src/native/render/nr_iprec.cpp (group signature + frame-wide pairing, debug fields).  New tools:
tools/native/{interp_groups.py, interp_trace.py, present_thread.py, interp3_battle.sh,
interp_window.sh, vkshot.sh}.  Docs: NATIVE-RENDER.md "13c" + tools row, NATIVE-THREADS.md "3h.2",
NATIVE-VULKAN.md "Results 2", BRINGUP.md items 3 / 5.

Left: the quiet-machine real-window check at 120 / 144 / uncapped, and a cheaper pass if the
interpolated present still exceeds the budget there; rigid composite parts still move only with their copy; the 2-3 px distant characters
whose clear is too large (1.8 % on the walk) stay placed; a 144 Hz play-test.

## 2026-10-26 (shadow bands): bands through the shadow-map shadows at internal res x3 / x5 / x6 -- the sprite snap's float error broke the game's CT16 channel shuffle

USER play-test 1025b/c: "shadows have strange lines going through them", apparently all shadows.
Lane "shadow", build `build/shadow-i686` (tree + this change), not committed, not play-tested.

- **Reproduced** on `out/playtest/rg-game-1025c.exe` and the tree, headless, `boot:save2` field
  3,850 (the Hooded Man at the transporter) and `boot:save2_battle2` 5,000: light vertical bands
  through every shadow-map shadow at internal res **x3** (what `internal_res = window` picks for
  the default 1280x960 window and for 1080p), weaker at x5 / x6; none at x1, x2, x4.  D3D11 and
  Vulkan alike.  Retail (`out/retail/cb1/save2_control.png`, PCSX2 cardboot) and our x1: smooth.
- **Cause** (NATIVE-RENDER.md "Shadow maps at the internal resolution"): the character shadows
  are shadow maps (`ShadowMapRender_146680` -> 192x192 CT32 buffer -> `ShadowMapBlur_145b60`:
  in-place bilinear blur, then a CT16 channel shuffle that copies each texel's red/green into its
  alpha, then one full-screen bilinear sprite darkening the frame by that alpha).  Upscaled
  sprites evaluate their texture coordinates at the native pixel centre (`PF_SNAP`, ddx
  extrapolation); at x3 the extrapolation lands a few ulps below u = k + 1/2, so the shuffle's
  bilinear read took 1/16 of the neighbouring CT16 texel (the other half of a 32-bit pixel): the
  alpha of the first texel of every 8 broke (mirror dump at the shadow draw: 27 texels whose
  alpha is 0-32 where their red is 130-165, columns 8k), and the 192 -> 512 magnification made
  them bands.  Found with a new target / mirror dump knob (below); the blur stage was equal to
  x1 at the centre sub-sample, the shuffle was not.  Not the shadow volumes, not depth, not
  ordering.
- **Fix:** `src/gpu/shaders/nr_draw.hlsl` `gs_uv16`: under `PF_SNAP`, the bilinear position
  (texels) is the GS's 4-bit sub-texel position, within 1/4096 texel below a 1/16 step counting as
  on it (`PF_GSLIN`, `PF_NATTAP`).  x1 untouched (no snap); x2 / x4: bilinear sprites on exact
  boundaries move by <= 8 levels (transporter beams, compass).  `RG_NR_UV16=0`: control (old snap).
- **Images:** `out/shadow/save2_3850_before_after_x1.png` (1025c x3 / fixed x3 / x1),
  `out/shadow/battle2_5000_before_after.png` (battle x3 before / after),
  `out/shadow/retail_save2_control.png`.  Shadow region vs x1 at x3: 29.52 -> 31.31 dB.
- **Regression check:** `tools/shadow/shadowcheck.py` (save2 3,850 at x1 + scales; the shadow
  map's alpha vs its red in the mirror at the shadow draw, shadow region PSNR vs x1): x3 / x5 / x6
  0 texels (D3D11 and Vulkan); control (`--control`, RG_NR_UV16=0) 27 texels, FAIL as required.
  ctests `fixtures.shadowbands` (x3, x5) and `fixtures.shadowbands_control`, D3D11.
- **Tools:** `RG_NR_RTDUMP=FBP:FRAME:N:DIR` (+ `RG_NR_RTDUMP_TBP=T`: only draws texturing from T,
  their registers / vertices on stderr and the 4 MB mirror they decoded from), nr_dev.cpp;
  `tools/shadow/{pam2png.py, vramrect.py, shadow_ab.py, shadowcheck.py}`.
- **Gates:** exe `build/shadow-i686/rg-game.exe` (logs `out/shadow/gates/`): regen --check 300 exit 0 (save2 card differed -> restored from the backup, verified identical), verify 8/8; run hash to 31,700 `b0632cdfa80153de` (= the hitch2 baseline); bootcheck --all 29/29; mapcheck 5/5 DRAWN; camprobe ch01_salgin / ch05_factory eye = retail; ctest -j2 -LE fixtures 743/743, -j1 -L fixtures 12/12 (incl. the two new ones); D3D11 render gate (`out/nrender/runs/gate_shadow.txt`): route x1 24 fields PSNR min 31.31, failing 0, run hash emu = native `ab389a3d1d0232e0` (= checkpoint 12), 8 boot fixtures PASS with equal hashes, mapcheck 5/5, save2 close-up x3 38.58 / 38.64 dB (38.10-38.31 before).  Vulkan: shadowcheck x3 PASS, control FAIL as required.  Field 8,150 plane shadows (shadow volumes) at x3: no bands.
- **Shared files touched:** `src/native/render/nr_dev.cpp` (render lane's: the RG_NR_RTDUMP block
  after the native draw, the RG_NR_UV16 control bit in the PF_SNAP block; nothing else),
  `src/gpu/shaders/nr_draw.hlsl` (gs_uv16, PF_NOUV16), `tests/fixtures/CMakeLists.txt` (2 tests),
  docs (this entry, BRINGUP.md symptom row + tools, NATIVE-RENDER.md).

Left: a play-test at the user's settings (x3 by default); ship it in the next play-test exe.  The
shadow volumes / coplanar plane shadows ("Level 4" known difference at 8,150) were not changed.

## 2026-10-26 (hitch2): the mode-11 read-back is the lens-flare probe, served a frame late in play; adaptive audio cushion; hitch.py names its own log stalls

Lane "hitch2" ("Start here" item 1: USER play-test, audio and video stop together).  Build
`build/hitch2-i686`; exes `out/hitch2/base` (the tree without these changes) and
`out/hitch2/new3` (with them; = the gate exe `out/hitch2/gate`); runs `out/hitch/<tag>/poweron`.
Not committed, not play-tested.  Run scripts (A/B pairs, full-route hash check, gates): `out/hitch2/*.sh`.

- **The read-back (goal 1).** The `download_ms` waits of the scripted scenes (game mode 11,
  fields 12,148-22,432) are the lens flare's depth probe: `GfxEndFrame_141c20` reads up to four
  8x8 PSMZ32 rectangles per game frame with `sceGsExecStoreImage` and takes the minimum Z (the
  flare's occlusion) -> libgraph `rg_gs_store_hook` -> nr_scene.c `native_store` -> nr_dev.cpp
  `mem_read` (early-copy path: the map waits for the GPU to finish the frame being drawn; these
  reads are not in the `downloads` column, which counts only the write-back path).  Found from
  the stats (downloads 0, download_ms > 0 every second field = every 30 Hz game frame) and the
  only `gpu_mem_read` caller.  **Fix: probe lag** (`gpu_config.probe_lag`, nr_dev.cpp `lag_read`,
  NATIVE-RENDER.md "Lens-flare depth probe"): in real-time play each probe takes a staging copy
  of its 12 px page neighbourhood (<= 2 x 2 pages) and is served from the copy of the previous
  probe group (= the previous frame), so the map finds a finished copy; no copy holding its pages
  = its own copy, waited for (exact).  On only where runtime.c sees a windowed, throttled run
  without display hashing; `$RG_GPU_PROBE_LAG=0/1` overrides.  A first version kept the copies in
  the staging ring shared with the HotRead early copies, which recycled them every batch (0 hits):
  probe reads no longer become HotRead entries.  **Run hash unchanged:** headless power-on to
  31,700 `b0632cdfa80153de` for the baseline exe, the new exe (lag off) and the new exe with
  `RG_GPU_PROBE_LAG=1` (10,186 of 10,189 probes served a group late; also equal to 14,000,
  `c9ec4bced061af23`).  Visual effect: the flare's occlusion follows the depth one game frame
  late.
- **Audio (goal 2; host_audio.c, host_sdl.c, host.h, runtime.c; HOST.md "Audio").**  The sound
  is rendered on the game thread, so a stall's audio does not exist until the game runs again: no
  thread can fill that gap, only a deeper cushion covers the NEXT stall.  (a) Adaptive cushion:
  after a starve shorter than the cap the target grows by 1.25 x the starve + 10 ms, at most
  `$RG_AUDIO_ADAPT_MS` (default 192 ms, 0 = fixed); after ~20 s without a starve or a
  near-empty queue it steps back by 8 ms per ~2 s.  (b) The refill after a starve leaves room for
  half the audio of the phases the host-clock pacer owes (`rg_host_audio_owed`), so the catch-up
  burst no longer overflows into a drop (drops in the loaded runs: 33-50 ms with it vs 334-617 ms
  without).  (c) Present off the game thread: not done (the present waits were load, below).  A
  first build gated growth on "no pacer re-anchor", but the host-clock pacer re-anchors on every
  stall over 4 phases, so it never grew; fixed (n3 run: target 64 -> 81 -> 128 ms at two starves,
  back to 64 after ~20 s).  ctest `host.audio_reg` extended (simulated 120 ms stalls every 5 s:
  a fixed cushion starves at each, the adaptive one at most twice, then decays to the base; owed
  refill).  Run hash: folded before the push, unchanged (above).
- **File reads (goal 3):** the shop route's 241 ms card-load gap is a cold OS cache (field 2,718:
  74 reads, 11 MB, 145 ms; the same load in the battle2 route, warm, 2.5 ms).  Not changed: async
  reads would change the game's timing; a warm-up needs the list of files a card load reads.
- **hitch.py:** `window F0 F1 DIR...`; category `out` (time between fields in the caller).  On
  this machine most remaining stalls of 0.1-1.4 s were the measurement itself: STATUS writes and
  the field logs' `fflush` (every 60 / 100 fields) blocking on the shared disk (fields = 1 and
  57-58 mod 100); they are reported as "measurement stalls" and not counted (a play-test run
  writes nothing per field).  The game's stdout / stderr now go through a pipe drained into
  memory.  These were most of the "off-CPU" hitches of the 10-25 report.  Default exe 1025c.
- **Measurements** (power-on to 16,000, interleaved pairs new / base, same machine minutes;
  machine shared with the other lanes).  Window 12,148-16,000 (mode 11), read-back wait per field
  mean / p99 / max: base 1.6-2.1 / 5.4-6.6 / 6.4-9.6 ms in all 7 pairs (quiet, cpu:8, game:2,
  gamewin:1, gamewin:3 x2), new **0.0 / 0.0 / 4.0-5.5** (the max is the scene's first probe);
  under the heavy load of the morning (machine CPU 97 %) the base reached 4.0 / 25.1 / 187.9 ms
  (`h2base1`; the 10-25 run 7.4 / 37.2 / 145.0).  Whole runs (video hitches = present gap > 50 ms;
  measurement stalls excluded; new vs base): quiet 9 vs 14 and 21 vs 3, cpu:8 15 vs 22, game:2 7 vs 10,
  gamewin:3 22 vs 39 and 14 vs 20; audio silence gamewin:3 (final exe) 49 ms vs
  2,248 ms.  The per-run spread is larger than most differences: on a quiet machine the game
  hardly hitches in this route either way; the read-back fix removes the one port wait that
  grew with GPU contention.
- **Gates** (exe `out/hitch2/gate/rg-game.exe` = new3): regen --check 300 PASS (save2 card differed
  -> restored from the backup), verify 8/8; bootcheck --all 29/29; mapcheck 5/5 DRAWN; camprobe
  ch01_salgin / ch05_factory eye = retail; ctest -j2 -LE fixtures 743/743 (8 skipped as
  before) + -j1 -L fixtures 10/10; run hash = baseline (above).
- **Shared files touched:** src/gpu/gpu.h (one field `probe_lag` at the end of gpu_config),
  src/native/render/nr_dev.cpp (LagRead / lag_read, snapshot serials, exit counters), runtime.c
  (gc.probe_lag, `rg_host_audio_owed` call, `target` column of RG_AUDIO_LOG), host files, tests,
  docs HOST.md / NATIVE-RENDER.md / NATIVE-THREADS.md "3h.1".  nr_const.c / nr_scene* untouched.

Left: a quiet-machine poweron to 23,000+ and battle / shop routes with the final exe (battle
present waits were load in the 10-25 report; not re-measured); present off the game thread if a
play-test still hears gaps under load; a card-load file warm-up if the first load after boot
matters; the 4 ms first-probe wait per scene.

## 2026-10-26 (rpkt): remembered-packet gap closed (sorted-path chain, view packets), walkers refuse unreadable memory, poison mode; FPS counter seen under Vulkan zero-copy

Lane "rpkt" (BRINGUP "Start here" item 4, then item 3's FPS-counter image).  Build
`build/rpkt-i686`, exe `out/regress_rpkt/rg-game.exe`.  Not committed.

**Audit** (new `tools/native/gameptr_census.py [--check]`, ctest `native_only.gameptr_census`):
every place the native renderer reads game memory -- the four DMA walkers' `host()` (nr_const.c,
nr_fx.c, nr_mesh.c, nr_im.c), every raw cast of a 32-bit game address (11, each on an allowlist
with the reason it cannot read dead memory) and every in-place `nr_const_apply` (4).  Pointers into
game packet memory that outlive the point where the game may reuse it:
1. the request's light packet (src[2], the light record's +4 "emitted" mark) -- fixed in 1025c;
2. the request's camera VIEW packet (src[1] = ctx +0x36B0, `DrawListEnsureViewPacket`'s "built
   this frame" mark, the same kind of mark; reset only by that context's `GfxEndFrame`): was
   applied in place by `nr_const_apply`;
3. the SORTED path's node header: `ModelQueueSortedPackets_14f0d0` writes r100 (view) and r110
   (light) into every node and `DrawListEmitBucket_1405a0` CALLs both from the frame chain, which
   `nr_fx.c` walks at the send (the BRINGUP item-4 residual);
4. every walker translated any address >= 0x10000 below 2 GB to a host pointer unchecked, so any
   garbage tag (the 1025b REF to 0x3F800000) faulted.
Kept in place (built for the draw, live when read): the item packets (object matrix, model info,
skin) and the mesh's material packet (`tbl->addrs[]`); the camera-matrix / plane / light notes and
`lstate` were already copies.  Not the renderer's: the GIF channel's chain walk in
`libdma_native.c` (the game's own just-built chain; unchanged).

**Fix** (`src/native/render/nr_scene.c`, `nr_const.c`, `nr_fx.c`, `nr_mesh.c`, `nr_im.c`, `nr.h`,
new `nr_mem.[ch]`, `CMakeLists.txt`; overrides generated by `tools/native/render_overrides.py`:
`ModelQueueSortedPackets_14f0d0.cpp`, `DrawListFrameBegin_1425d0.c`, new
`CameraWriteViewPacket_148740.c`):
- view packets are noted by address like lights (`nr_note_view` -> `g_vpk`), a request's view
  packet is applied from the copy written there for that context (unknown: in place only when
  still one self-contained RET block, else `no view`);
- `nr_chain_packet` resolves the node header's view / light packets at build time by the records'
  rule: memory equal to the copy = the address unchanged (chain, VU memory and run hash
  unchanged); else the copy is written into the frame's packet stack and the node CALLs it (one per
  context, packet and frame); unknown and not a block = an empty RET;
- `nr_game_ptr` (nr_mem.c): every walker's host(), inline payloads and REF ranges must be
  committed readable memory (VirtualQuery, per-thread region cache reset each frame); a bad
  address fails the walk like an unknown layout (counted: "native render game memory: N walker
  reads refused") instead of faulting;
- poison mode `RG_NR_POISON=1|2`: `DrawListFrameBegin` poisons the frame packet stack's used part
  before `MemStackReset`; every walker reports ("nr: POISON: <reader> ...") / aborts (2) on a
  poisoned tag or payload head.
Shop route with `RG_NR_STALE=1`: request view packets 67,465, 0 not noted, 0 stale; sorted-chain
packets 11,382 view + 11,382 light, 0 copies needed (the 1025b stale light is the unsorted
MapSky path's; the 4 stale light notes are applied from the copies as in 1025c).

**Regression:** `tools/fixtures/poisoncheck.py --exe EXE --suite shop,boot,drivers,soak [--mode
1|2] [--control]`: PASS = the suites pass + 0 poisoned + 0 refused walker reads + the poison armed.
Poison sees dead memory not yet rewritten; reused memory (the 1025b case: the menu's packets over
the field's stack) reads as live data and shows as refused reads -- both count.
Results: shop PASS (30,013,973 qwords poisoned, 0 poisoned, 0 refused); boot (bootcheck --all, 29 cards under poison) PASS (1,887,235,702 qwords poisoned, 0 poisoned, 0 refused; every card still passes with the poison);
`--control` (`RG_NR_NOTE_COPY=0`) PASS: 4 refused reads (the old stale walk, now refused instead
of faulting, so the 1025c A/B no longer crashes).  ctests `fixtures.poison` (shop, mode 2) and
`fixtures.poison_control`.  Not run: the `drivers` and `soak` suites (long; next).

**Gates** (exe `out/regress_rpkt/rg-game.exe`): ingest --check 0 problems; regen --check 300
PASS (save2 card restored from the backup); verify 8/8; bootcheck --all 29/29; mapcheck 5/5
DRAWN; link_audit PASS; addr_census PASS (0 / 0); shop_close PASS (D3D11 + Vulkan); camprobe
ch01_salgin eye (-3328.2, 97.0, -1894.9), ch05_factory (6589.3, -644.1, 5831.7) = retail; render
gate (D3D11, oracle twin) PASS: route 24 fields PSNR min 31.31, 0 failing, boot fixtures 8/8,
map 5 DRAWN, run hash **ab389a3d1d0232e0** both (= 1025c's: unchanged); ctest -j2 753/753 (incl. the new `fixtures.poison`, `fixtures.poison_control`, `native_only.gameptr_census`; environment skips as before).

**FPS counter under Vulkan zero-copy (item 3):** new `tools/native/ddcap.cpp` (DXGI Desktop
Duplication grab, x64, `ddcap_build.cmd`) and `wincap.py --dd [--burst N]` (window raised
topmost for the grab, refused when covered).  1025c with `--set display.fps_counter=detailed`:
D3D11 and Vulkan read-back (`RG_VK_PRESENT=0`) show the detailed line; Vulkan zero-copy: 5 of 6
grabs black over the whole client area, one (26 s, opening movie) shows the picture with "32 FPS"
only.  So the counter IS drawn under zero-copy, but in the short form and most grabs are black;
open (docs/NATIVE-VULKAN.md "FPS counter capture"; the present path is the hitch lane's area).
A burst run was cut short (the window got minimised during it); the desktop was in use.

**Shared files touched:** `tests/native_only/CMakeLists.txt` (+1 test), `tests/fixtures/CMakeLists.txt`
(+2 tests), `tools/native/wincap.py` (`--dd`, `--burst`, largest window first),
`tools/native/render_overrides.py` (sorted / framebegin / view generators; its `gen_endprim` and
`gen_bucket` no longer match the tree -- pre-existing drift, those two files untouched).

## 2026-10-26 (x64): the full power-on route runs on x64 with the i686 run hash at every field

Full record: docs/X64-PLAN.md section 0.7.  Builds: `build/x64-windows` (x64, derived tree
`build/x64-src`), `build/x64g-i686` (i686, the same src tree).  Nothing committed.

- **Result:** `tools/x64/pairrun.sh` on the golden route to 32,000 fields: run hash equal to
  i686 at EVERY field (final 20a59d8fc0743062 on both: the i686 hash is the one the previous
  lanes had, so the i686 run did not change), RG_AUDIO_CMDLOG byte-identical with timestamps;
  the saved card differs only in host pointer words (heap / vtable addresses retail also
  saves raw) and the checksum over them.
- **Method:** the run hash (pad / audio / display / kernel trace) showed the parting at 24,824,
  but game memory had parted earlier.  New `tools/x64/ssdiff.py` diffs the save states of the two
  exes at one field (heap word by word, statics by symbol, host pointers normalised; the game
  heap is at 0x0A000000 in both under --save-state), bisected to the first differing word, then
  RG_WATCH (fixed heap address) / RG_BREAK (x64 now prints rcx rdx r8 r9 and dumps at them).
- **Eight x64 bug classes fixed** (all x64-only; every port-source edit i686 object-identical by
  `i686_same.py`): float sqrt rounding (i686 = CRT x87 nearest, x64 = sqrtss chop:
  `include/port/sqrtf_rn.h`); x64 UCRT sin/cos/tan wrong under chop (crt_math `HOST_RN`); the
  data layer's 16-byte array alignment on x86-64 (derive `dalign`: 1,521 objects; the font width
  table made every text box twice as wide); small-integer argument / return extension (derive
  `narrowabi`, 4,845 declaration positions incl. int views of pointer stack arguments: the first battle's hit effects at the origin was the
  "audio" divergence); 16-byte alignment assumed for extern objects (derive `xalign`: movaps
  fault at every card boot); ptr32 gaps (attribute typedef names, `R (**)(A)` casts, field macros
  with pointer types: crashes at the transporter menu and the save); port structs in game memory
  (MSL string, dtor chain, ostream sentry: CRT_P32); 32-bit varargs for %s (crt `rg_gvformat`).
- **New tools:** pairrun.sh, ssdiff.py, sspeek.py, heapwalk.py, dumpdiff.py, heapdiff.py,
  rva2sym.py, datalayout.py, narrowabi.py, vmmap.py --below-mb, x87census.py, libmcheck.c, gates.sh, vcninja.ps1,
  buildretry.sh (all tools/x64).  ctests: x64.sqrtf_rn (+control), x64.datalayout, x64.narrowabi.
  rg-smoke has an x64 form.
- **Gates** (`tools/x64/gates.sh`; table in X64-PLAN 0.7 "Gates"): i686 (build/x64g-i686, validates
  the rg_x64_va_fence and every x64 edit) regen+verify 8/8 OK (save2 restored), bootcheck 29/29,
  mapcheck 5/5 DRAWN, camprobe = retail, link_audit + addr_census PASS, render_gate PASS, ctest
  742/743 (host.audio_reg = hitch lane WIP) + fixtures 12/12.  x64: bootcheck 29/29 (milestones
  identical to i686), mapcheck 5/5 (same scores), camprobe = retail, link_audit + addr_census
  PASS, ctest -L x64 9/9, all 707/752 (33 Not Run: i686-only fixtures / GetThreadId link; 9
  SEGFAULT + 3 Failed: 32-bit test harnesses); render_gate not run (no x64 oracle twin);
  regen FAILED.
- **Open:** x64 save-state mode exhausts the address space below 2 GB (RG_SS=1 alone parts at
  field 26,674; free below 2 GB falls 293 -> 69 MB, largest hole 31 MB, a 4 MB malloc fails at
  26,650): the regen failure.  The 688 undecided devirt sites untouched (none fired on the route).

## 2026-10-25 (shopfix): shop-close crash fixed (stale light-packet pointer); crash log file; FPS counter; play-test build 1025c

**User report:** 1025b, buy "Grand Edge" in a store, close the store: crash (event log
`_nr_const_apply + 0x3da`).  **Reproduced** headless from a copy of the user's card
(`out/fixtures/cards/zuser1025`, "Rosa: Salgin: Near the Item Shop", 863 z): through the door
north-west of the transporter into the item shop, Shihawa (SHOP), Buy -> Grand Edge (7th row,
320 z) -> x1 -> Yes (543 z) -> CIRCLE: 0xC0000005 reading 0x3F800000 at the 2nd CIRCLE (field
4,750) on 1025b and on the pre-fix tree, D3D11 and Vulkan alike (4/4 runs).  Input found with new
`tools/fixtures/cardwhere.py` (leader position + camera-relative stick from a card boot, works
on play-test exes) and screenshot sheets; kept as `tools/trace/goldens/shopcrash_buyclose.input.txt`.

**Root cause.** Not the remembered camera / light / plane notes suspected in the triage: copying
those (below) left the crash in place.  A temporary key log on every `nr_const_apply` showed
the faulting walk = key 2 of a field-context draw (`MapSkyDrawLayers_17e760` -> `ModelDraw` ->
`ModelEmitDrawPacketsMaybe_14ec20` -> `nr_model_record2`): the request's light packet
`src[2] = LightStateGetPacket_1428f0(ctx)`, i.e. the current light record's +4 pointer.  The
game sets that pointer when `LightStateEmitOnce` / `LightStateResetEmit` write the light packet
into a frame's packet stack and uses it only as an "already emitted" mark.  The field context did
not draw during the shop menu (frames 2,488 -> 3,007), so its record kept a pointer into a stack
the menu had reused; the first field frame after the close walked the menu's data as DMA tags
and followed a REF to 0x3F800000 (the float 1.0).  The PS2 never faulted on it (the packet is not
re-read by the CPU; DMA addresses wrap to 32 MB, the VIF takes any words); the port's assumption
"a packet named by a draw request, or remembered per context, is live when the record is made"
was wrong.  `RG_NR_STALE=1` confirms: "stale light note: ctx 00D20DB0 packet 053792D0 noted
frame 2488, used frame 3007".

**Fix (src/native/render/nr_scene.c, nr_const.[ch]; generic, the whole class):** every packet the
renderer remembers is copied when its builder writes it (one inline RET block,
`nr_const_inline_bytes`) and applied from the copy (`nr_const_apply_inline`): the per-context
camera / light / plane notes, and every light packet also by address (`g_lpk`, 256).  A request's
light packet is applied from the copy written at that address for that context; one the table
does not know is read in place only when it is still one self-contained RET block (no pointer
followed), else the context's last light packet.  `lstate` was already applied at build time; the
interpolation camera copies and the mesh cache (content-hashed) were already safe.  In normal play
the copies equal memory, so output is unchanged (verify 8/8 and the render gate below; save2 boot
run: 6 request packets not in the table, all read in place as before).  `RG_NR_NOTE_COPY=0`
restores the old reads (the regression then crashes again at 4,750: A/B).  Residual, documented in
NATIVE-RENDER.md "Remembered packets": the sorted path's DMA chain still CALLs the node header's
light packet (the game's own chain, walked by nr_fx.c); not hit by the regression.

**Regression:** `tools/fixtures/shopcrash.py --exe EXE [--api d3d11,vulkan] [--stale]` (PASS = no
exception, shop menu seen, back in the field by 5,100); ctest `fixtures.shopcrash` (D3D11, skips
without the card); play-test gate `shop` (both APIs) in `build_playtest.py`.  1025b and the pre-fix
tree FAIL it on both APIs; the fixed tree PASSES both.

**Crash log (src/game/rg_game_main.c `rg_game_crash`):** the stderr report is also appended to
`rg-game-crash.txt` beside the exe with time, exe path, field and game vbl, function names from
`<exe>.map` beside the exe (symbols past the code section shown as "not in the exe's code") and a
minidump `rg-game-crash.dmp` (dbghelp loaded at crash time, MiniDumpWithIndirectlyReferencedMemory,
~0.2 MB).  `RG_CRASH_LOG=FILE` / `=0`.  `build_playtest.py install` copies the map beside the exe
(`rg-game-1025c.map`).  Offline: `tools/native/crashsym.py MAP LOG`.  Checked with the A/B crash.

**FPS counter (hitch lane's patch `out/hitch/fps_patch/fps_counter.patch`, applied):**
`display.fps_counter = off | fps | detailed` (default off, Original off), drawn by host_sdl.c after
the window shot.  Two fixes to the patch: the ctest's ini strings held raw newlines (did not
compile), and its "no [restart]" check looked at the whole display page (which has restart rows):
now `menu_sel_has` on the selected row.  `ctest -L settings` 45/45.  Windowed `detailed` seen on
D3D11 ("60 FPS 16.6 ms (max 18.6) logic 31/s") and on Vulkan with `RG_VK_PRESENT=0` (read-back
present: "60 FPS 16.7 ms (max 21.1) logic 30/s"); with Vulkan zero-copy present a desktop /
PrintWindow capture is black for the whole window (capture limitation, the counter goes through the
same SDL renderer call), so that mode is not confirmed by an image.  New `tools/native/wincap.py`.

**Gates (exe `out/regress1025c/rg-game.exe`, build `build/shopfix-i686`):** regen --check 300 PASS
(save2 card restored from the backup); verify 8/8; bootcheck --all 29/29; mapcheck 5/5 DRAWN;
link_audit check --forbid all --extra rg_ps2_hwbus PASS; addr_census --check PASS (0 / 0);
insectrun title, gameover, factory, factory_place PASS; shop_close PASS (D3D11 + Vulkan);
ctest -j2 750/750 (7 environment skips as before); render_gate (D3D11, oracle twin) PASS: route 24 fields PSNR min 31.31, 0 failing, run hash ab389a3d1d0232e0 both; boot fixtures 8/8 PASS (save2, factory, insectron, save2_battle2, ch06_vedan, ch09_labyrinth, ch12_mariglenn, ch13_mariglenn; emu = native hashes); mapcheck 5 DRAWN.  No gate failure traced to the x64 lane's nr_dev.cpp / gpu_core.cpp / gpu_internal.h / trace_regions.c edits (they are in this build).

**Play-test build 1025c:** `out/playtest/rg-game-1025c.exe` (+ `rg-game-1025c.map`): the whole
tree at 22:29 (Vulkan zero-copy present + the zero-copy-at-power-on fix, pose interpolation
checkpoint 13, soak overrides, the x64 lane's i686-no-op edits, this fix, the crash log, the FPS
counter).  The .bats point at it.  The user's path on the installed exe itself: `shopcrash.py --exe out/playtest/rg-game-1025c.exe` PASS on D3D11 and Vulkan (4 stale light uses applied from copies, 51 request packets read in place), and a windowed D3D11 run of the same input to 5,100 exits 0 with no exception.  Smoke (windowed from out/playtest, 1,600 fields) PASS, run hash c1d233bd0e9574b3.

## 2026-10-25 (hitch): hitch measurement tool, first loaded numbers; FPS counter staged as a patch (not in the tree)

*Later the same night: the FPS-counter patch was applied (two test fixes), gated and shipped in 1025c -- see "2026-10-25 (shopfix)".*

Lane "hitch" (USER play-test report: frequent hitches where audio and video stop together, exe
1025b via play.bat, machine shared with other lanes' game processes).  Stopped early on a
wrap-up request: **no source change is in the tree** (tools and docs only; run hashes untouched,
nothing to gate).  Out dir `out/hitch/`; partial build dir `build/hitch-i686` (configure done,
build stopped at ~11,000 / 25,928 steps; reusable).

- **Tool:** new `tools/native/hitch.py` (+ route input `tools/native/hitch_shop.input.txt`),
  docs/NATIVE-THREADS.md "3h. Hitches".  Built on the existing per-field logs
  (`tools/perf3d/stutter.py` loaders); adds audio starves, present gaps, an off-CPU estimate
  (wall - pace - main-thread CPU - timed waits), machine CPU / GPU samples and owned contention
  (`--load`).  1025b has no $RG_PRESENT_LOG: present times come from the stats' presents column.
- **Why audio stops with video (architecture, confirmed in the code):** audio is not on an
  independent thread.  The native engine renders on the game thread (deterministic, folded into
  the run hash) and `host_half` pushes it after each field; the SDL device thread only drains a
  64 ms cushion.  Any game-thread stall > ~64 ms starves the device; the regulator then re-pads
  the cushion with silence (so a hitch of H ms costs about H ms of silence), and while the game
  runs below real time (pacer catch-up, debt beyond 4 phases dropped) no cushion can help.
- **Loaded baseline, 1025b, 3 routes (`out/hitch/base1`).** Machine during the runs: other
  lanes' rg-game / rg-game-oracle processes plus this lane's own -j4 build; CPU total mean
  63-78 %, GPU-3D mean 31-85 % (typeperf).

  | route | s | CPU / GPU % | video hitches (> 50 ms) | per min | audio starves | silence ms |
  | --- | --- | --- | --- | --- | --- | --- |
  | shop | 76 | 63 / 85 | 73 | 58 | 15 | 244 |
  | battle2 | 135 | 78 / 52 | 478 | 212 | 41 | 441 |
  | poweron | 600 | 70 / 31 | 1,857 | 186 | 412 | 10,205 |

  Every audio starve in battle2 and 324 / 412 in poweron coincide with a video hitch: the same
  game-thread stall.  Causes (excess over the route's median field):
  * **poweron, fields 12,148-22,432 (game mode 11.0, the scripted scenes between the FMV and the
    first battle): GPU read-back waits** (`download_ms` of $RG_FIELD_STATS, up to 145 ms in one
    field): 855 video hitches and 308 of the 412 audio starves (3.96 s of silence).  A GPU->CPU
    read-back on the game thread is a sync point that grows with any GPU contention: **port
    fault** (the work and the wait are ours; contention magnifies it).  Which read-back is not
    identified yet (next step 1).
  * **battle / shop: present-path waits.** Battles present every 4th field (pacer catch-up): the
    zero-copy present's compose (`read` column: `gpu_present_shared` -> `display_post` ->
    `share_out`, keyed-mutex `AcquireSync` + copy + Flush) takes 22-70 ms and the window present
    4-13 ms, while main-thread CPU is 6-8 ms of the 45-88 ms field: the thread waits on the GPU.
    With the GPU 50-85 % busy from other processes this is mostly **load**, but it is the game
    thread that waits, which is why audio stops too (port design: present and audio push on one
    thread).  The quiet-machine run (next step 2) splits the two.
  * **file I/O:** one 241 ms gap at the shop route's card load (77 synchronous reads, 145 ms in
    `rg_fs` on the game thread): port (synchronous reads; disk contention magnifies).
  * **off-CPU:** 4-11 hitches per route of 0.2-1.2 s with the main thread neither running nor in
    a timed wait (poweron field 21,223; 31,196-31,464 in the transporter menu): preemption under
    load or an untimed wait; not attributed yet.
  * **event pump:** 2 x 120-140 ms inside `rg_host_pump` (battle2 fields 1,334, 5,633):
    unexplained (SDL device enumeration or the window system).
- **FPS counter (USER, relayed):** implemented, then taken out of the tree unbuilt at wrap-up;
  the patch is `out/hitch/fps_patch/fps_counter.patch` (`git apply` from the port root; the
  files are LF).  Design: setting `display.fps_counter` = off | fps | detailed (default off,
  Original off, live, no restart / display trial) in rg_settings_core.c; drawn by `draw_fps` in
  host_sdl.c `present_tex` after the settings overlay and AFTER the window-shot read-back, right
  before `SDL_RenderPresent`, so screenshots, `--shot`, render_gate images and the run hash never
  contain it.  Backend-neutral: D3D11 zero-copy, Vulkan and the copy path all present through
  `present_tex`, so the Vulkan lane needs nothing extra.  `detailed` = FPS, mean / max present
  interval over 0.5 s, game-logic rate (`rg_frame_logic_ticks`, reported each field by one call
  `rg_host_fps_logic` in runtime.c `host_half`, presentation only) and "AUDIO STARVED"; ctest
  `settings.fps_counter`; SETTINGS.md rows.

Next steps, in order:
1. Find the mode-11 read-back: `hitch.py run X --route poweron --fields 23000` with the
   renderer's download counters per call site (`RG_GPU_RT_LOG`); take it off the game thread or
   lag it a frame (the copy path already has `readback_lag`).
2. Quiet-machine baseline: `hitch.py run quiet --route all` when `tasklist` shows no other
   rg-game*, then `--load cpu:8`, `--load game:2`, `--load gamewin:1`, to see which contention
   (CPU or GPU) makes the battle / shop present waits.
3. Audio independence within determinism (the engine output must stay on the virtual clock):
   (a) adaptive cushion: raise `latency_ms` after starves, decay when stable (A/V lag only under
   load); (b) no silence re-pad when the pacer is about to catch up owed phases; (c) the present
   (compose + window present) off the game thread, so a GPU wait no longer delays the audio
   push.  (c) touches the presenter: coordinate with the Vulkan lane.
4. Apply the FPS-counter patch, build, run `ctest -L settings` and the brief's gates.

## 2026-10-25 (cov3): story Insectron final won from a card, rank reward verified; factory production reached

Lane "cov3" (the two coverage gaps soak2 left: the story Insectron reward path and factory
production). Tools and docs only: no game code, override or stage changed, no port bug found. Exe
for all runs: `build/soak2-i686` (snapshot `out/fixtures/runs/bootexe/e110a68e153a92c6`, = the
soak2 gate tree); runs `out/cov3/` (game-derived, not committed). Docs: TEST-FIXTURES.md "Story
Insectron", "Factory production"; SAVE-FORMAT.md "Insects and cages".

- **Caged insects on a card.** Inventory kinds 4 / 5 / 6 (insect / Insector Trap 0x4B0 / Rearing
  Cage 0x4B1) are 0x1C-byte objects holding an index into the **GameRec table** = chunk 12 (party
  +0x174, 0x33C0: 15 insect records x 0x34, 3 trap x 0x7F0, 3 rearing x 0x84C), decoded from the
  item vtables (`ItemGameRecAcquire/Bind/Reset_*`, `InsectItemSetup_3d1fb0`, `InsectRecSlot*`) and
  `WorldDataCmdAddItemMaybe_3b9d40` (how a section's insect goes into a cage). `saveedit.py
  --section-insects SID` (the developers' Insectron start states, e.g. 115 'Insectron E-5'),
  `--add-insect`, `--strong-insects`; cards `insect_final` / `insect_final_s`. Live check: after
  CONTINUE the game's GameRec equals the card's except the 15 re-resolved insect pointers and the
  satiety timers (+0x30 f32, ticking); a first guess (+0x30 = s32 exp) was corrected by that diff
  (exp is +0x12, `InsectItemGetExp_392240`).
- **Trigger from the script data.** New `tools/fixtures/evscan.py` (SB2 .stb scanner /
  disassembler, `ScriptVmExec_173b00` format): event commands 1574 MenuInsectEntryOpen / 1587
  InvCountInsects are called only by `map/m04/m04.pac` m04.stb routine 0xED04 = the receptionist,
  NPC 24228 (talk dispatcher, var 121 = 3): >= 5 caged insects, then "Continue from Rank E, Battle 5?"
  with vars 5 / 6 / 7 = 1 / 1 / 4. NPC position from zone ZL05 npc tables.
- **The match is played by a policy, not watched.** New `tools/fixtures/insectstory.py`: boot ->
  talk -> auto team / auto layout / default king -> each player turn decided from a memory probe of
  the INSECT battle object (pieces, 7 x 5 board, move / attack marks, cursor pages, command list,
  side to move) -> results -> field control; `boot_route.txt` + `replay`. Run `out/cov3/story4`:
  INSECT at 4,180, battle 6,150..18,480 (3 player turns, the enemy king KO'd), 1,173 s.
- **Reward = retail.** Table `rc/param/purpose/insectron_2_en.pac` insectron_param_EN (#100 rank
  key, 3 x (item, count)); asm 003E84F0 = the override's VCALL 0x70; key 1, first clear (var 6 >=
  var 5) -> pair 0 = Battle Feed 16747 x5. Port: vars 0x73 / 0x74 = 16747 / 5, Battle Feed 0 -> 5 in
  the live inventory, rank var 5 1 -> 2, vars 6 / 7 -> 0. **Repro of the original bug**: the same
  route replayed from power-on on an altlink exe with the stage's original two TUs
  (`out/cov3/prefix`, `t = (InsectronRewardLookupMaybe_3e84f0(g), (s16 *)0)`): the match is won and
  the rank rises, but vars 0x73 / 0x74 stay 0 and no Battle Feed is added; the current tree's exe on
  the same route: 16747 x5 (`out/cov3/story4/replay_fixed`, `replay_prefix`; again on the final
  tool's route `out/cov3/story5`: field control 18,520, replays rc 0 both, fixed 16747 x5, original 0).
- **Factory production reached** (soak2 open item 5): first product, Divine Blessing from the
  Healing vial plan, in the inventory (+1, materials -2 each, transporter save diff). Not timing alone:
  alchemy materials must pass an Athanor, and the Athanor is not in the Place list until its item
  group (34) is unlocked (the list is the item-def table filtered by unlock time, not the inventory).
  New: `saveedit.py --unlock-group`, recipe `factory_prod`, `factory.py --plan healing_ath --save`
  (+ `--no-demo`, `--until`), `tools/fixtures/fdump.py`. Game rule, no port bug; runs
  `out/cov3/factory/final`, `final_replay` (power-on replay rc 0, run hash 6fd8c7397564dc37).
- **Regression wiring:** `soak.py drivers` (insectstory + insectrun + factory production, PASS /
  FAIL per driver verdict), the cards in `saveedit.py make` and `make_allcard.py`;
  `fixtures.saveedit` test covers the insect / cage writer (synthetic save, stub item table).

| # | Finding | Class | Status | Repro |
| --- | --- | --- | --- | --- |
| 1 | Story Insectron reward never granted with the stage's code (record forced NULL) | override (soak lane, 2026-10-25) | verified at run time now (was by construction) | `insectstory.py replay out/cov3/story5/boot_route.txt --exe out/cov3/prefix/rg-game.exe` (no reward) vs the current exe (Battle Feed x5) |
| 2 | Factory: "improperly processed" / "not on time" | game rule | closed (Athanor + equal route lengths) | `factory.py run --card factory_prod --plan healing_ath --cords --produce 1000 --save` |

Gates: no code / override / stage changed (tools, tests and docs only), so regen / verify / bootcheck /
mapcheck / link_audit / addr_census were not re-run for this lane; `fixtures.saveedit` (ctest,
`build/soak2-i686`) PASS; `ingest.py --check` unaffected (no game/ or overrides/ file touched).

## 2026-10-25 (vulkan present): zero-copy presentation and interpolation on Vulkan; readback_lag, GPU profile, a 32-bit validation layer; shop-close crash triaged (not fixed)

Lane "vulkan" second pass (docs/NATIVE-VULKAN.md "Presentation", "Validation", "Results 2"; build
`build/vk2-i686`, exes `out/vk2/b6`, `out/vk2/b7`).  D3D11 rendering unchanged (route dumps identical
to the previous exe at all 24 fields; fxc headers byte-identical).

1. **Zero-copy presentation on Vulkan**: the window's renderer becomes SDL's Vulkan renderer on the
   backend's own instance / device (`rg_host_use_vulkan`, `gpu_vk_present_device`); the backend submits
   on queue 1, SDL on queue 0; frames are two backend images (grow-only, SHADER_READ_ONLY_OPTIMAL)
   wrapped as SDL textures; a timeline semaphore (every submission signals its serial) + a busy flag
   per slot.  No Windows API (surface via `SDL_Vulkan_CreateSurface`, extensions by name).
   `RG_VK_PRESENT=0` = the old read-back path.
2. **Interpolated presentation works on Vulkan** windowed (it only lacked zero-copy).  Pose metrics
   (`interp_pose.sh`, same battle state) match D3D11: isolated switch ratio 1.18 / 1.18, step judder
   0.34 / 0.34, run hash 88081d075183d936 both.
3. **Fix (both backends)**: zero-copy was disabled for the whole run when the first present found the
   display off (power-on), so windowed runs from power-on never used zero-copy or interpolation (D3D11
   too).  runtime.c now skips such a frame; a real failure prints a message.
4. `readback_lag` and `RG_GPU_PROFILE` implemented for Vulkan (lag checked with dumps; profile table
   counts equal to D3D11's).  New `RG_PRESENT_LOG` (runtime) + `tools/native/present_pacing.py` /
   `present_pace.sh` (windowed pacing per API / mode).
5. **Validation**: `tools/native/build_vvl_x86.ps1` builds VK_LAYER_KHRONOS_validation for x86 from
   source (clang-cl -m32, Apache-2.0 / MIT deps); the loader ignores layer path variables in this
   elevated process, so the backend loads it itself (`RG_VK_LAYER_DLL`, handle wrapping off);
   `tools/native/vk_validate.sh`.  Route + windowed interpolation, also with sync validation: no errors,
   one harmless warning id.

Gates: Vulkan render_gate (b6) route 31.45 dB / 0 failing, 8/8 boot PASS with oracle hashes, mapcheck
5/5, close-up 38.93 / 38.96; D3D11 render_gate (b7) route 31.31 / 0 failing, mapcheck 5/5, close-up
38.25 / 38.33, boot save2 PASS, other 7 boot fixtures NOT run (stopped at wrap-up); backend_compare
identical run hashes, 45.60 dB min; link_audit PASS; addr_census PASS; ctest -j2 748/748.  Windowed
144 Hz pacing measured only under heavy machine load (numbers in NATIVE-VULKAN.md; to redo).

**Shop-close crash (user play-test of 1025b, interrupt): triaged, NOT fixed.**  Event log fault
`_nr_const_apply + 0x3da` = the data-copy loop of `feed_blk` (nr_const.c) reading the payload of a
DMA tag: a REF/REFE/CNT packet whose data address is no longer mapped, i.e. a stale packet pointer
walked by `nr_const_apply` (callers in nr_scene.c: `lstate_apply`, `game_constants` with packets
remembered per draw context in `g_cam` / `g_light` / `g_plane`, which outlive the shop's packets).
Not reproduced yet.  Repro set-up: the user's card copied (unmodified) to `out/shopcrash/usercard`
and fixture `out/fixtures/cards/zuser1025` (Salgin transporter, Jaster Lv 3, Simon's shop beside it);
`talksweep.py zuser1025 --control 3720`: stick E 12 fields + CROSS opens Simon (modes 12/*:
`out/shopcrash/sweep/E_12.input.txt`).  Next: extend that input to Buy -> Grand Edge -> confirm ->
close, run 1025b / the tree exe headless (both backends) to reproduce, then check which remembered
packet is stale (drop `g_cam` / `g_light` / `g_plane` / `g_lst` entries when the overlay or the draw
context they came from goes away, or validate addresses against live game memory), add the run as a
fixture regression, crash log file beside the exe (not done), build 1025c.  The .bats still point
at 1025b.

## 2026-10-25 (x64 lane, night): the x64 crash was a full 2 GB address space; hash equal to i686 to field 24,823

Full record: docs/X64-PLAN.md section 0.6.
- **Cause:** the NVIDIA 64-bit D3D11 driver reserves a 1 GB contiguous range (plus about 256 MB
  committed) below 2 GB in the LAA:NO x64 process (the i686 driver: 128 MB), leaving about
  650 MB: NULL calloc in nr_mesh_decode (the `dec->m` crash) and run-length-dependent behaviour
  (the hash log diverged at 15,426 in a 22,500-field run, not in a 16,000-field run).  Found
  with the new `tools/x64/vmmap.py`.
- **Fix:** `rg_x64_va_fence()` (src/x64/lowmem_check.c, called through `RG_X64_VA_FENCE` in
  src/gpu/gpu_internal.h around backend creation in nr_dev.cpp and gpu_core.cpp): 64 KB posts
  every 512 MB below 2 GB, kept for the process; the driver then puts its range above 4 GB.
  Runs to 26,000 / 32,000 without a crash; two runs to 26,000 identical.
- **Trace fix:** src/trace/trace_regions.c translated no 32-bit stored host pointers on a
  64-bit build (`RG_TRACE_HOSTPTR32`).  routecmp pair to 24,900: sym: trace identical on all
  12,433 frames.
- **Open:** the audio part of the run hash differs from field 24,824 (RG_AUDIO_CMDLOG: a 1D/1E
  sound-thread command issued at a different time); next step in X64-PLAN.md 0.6.
- R4: the 9 direct winabi rows are all benign on x64.  New tools: vmmap.py, hashdiff.py,
  dataparity.py (0 initial data-image differences).  i686_same: 10 compiles, 0 differ.  The
  i686 and x64 gate sets were not run this session.

## 2026-10-25 (x64 lane, evening): strategy A under way; the x64 exe runs the route to field 22,000 with the i686 run hash

USER committed P7 to strategy A (docs/X64-PLAN.md).  Full record: X64-PLAN.md section 0.
Pre-edit backup: ..-backups (BACKUP_OK).  Builds: `build/x64i-i686` (i686, the edited tree,
`-DRG_GPU_VULKAN=OFF` while the Vulkan lane's nr_vulkan.cpp was mid-change), `build/x64-windows`
(x64, `RG_X64_SRC=build/x64-src`); scratch tree and build `../x64-scratch` (not part of the
port).

- **Design:** the x64 stages DERIVE a second source tree (`tools/x64/derive.py`: game/ +
  overrides/ + missing/ -> build/x64-src) instead of changing the ingest: game/, the override
  hashes and other lanes' re-ingests are untouched; i686 never runs an x64 stage.
- **Step 1 (plumbing):** `RG_ARCH` from the toolchain; `cmake/x64.cmake` (linker launcher
  `tools/x64/linkgate.py` + `pecheck.py`: an x64 link without LAA:NO / DYNAMICBASE:NO /
  HIGHENTROPYVA:NO / low base FAILS and the exe is deleted; start-up self-check
  `src/x64/lowmem_check.c` in every executable); `tools/build.ps1 -Arch x64`.  ctest -L x64 5/5
  (incl. two controls that must fail for the gate's reason).  i686: fresh-configure
  compile_commands.json byte-identical before/after.
- **Step 2 (ptr32):** `tools/stages/ptr32.py` (RG_P32 = `__ptr32 __uptr`, include/port/x64.h);
  xprobe over all 25,447 TUs: 0 compile errors; layout gate 74,590 records, 0 game records
  differ.  LLVM `__ptr32` gaps made loud: `-fno-optimize-sibling-calls` (calls through a ptr32
  function pointer), `-fno-jump-tables`, `-fno-vectorize -fno-slp-vectorize`.
- **Step 3:** data layer as asm ADDR32 words (`tools/x64/addr32.py`, 1,127 objects); overlay
  module table `gen_overlay_registry.py --arch x64` (i686 output byte-identical).
- **Step 4/5:** fiber switch, overlay trampoline, naked vthunks, ss_heap/ss_map, crash handler,
  EE-kernel names vs kernel32, SDK structs in game memory (`SCE_P32`), crt size parameters,
  libc redeclarations (`__SIZE_TYPE__`), devirt views widened to 64-bit integers (`vcmwiden`).
  i686: `tools/x64/i686_same.py` vs the backup, 47 compiles, 0 differ.
- **R4 census** `tools/x64/winabi_census.py`: 80,183 direct calls, 1 class + 8 width rows (the
  irabi BUG-kind set); vtable families 0; 688 devirt sites undecided without a class -> vtable map.
- **Step 6 (bring-up):** x64 rg-game links and boots (D3D11 native device); `tools/x64/xrun.py`
  golden route: run hash **equal to i686 at fields 600, 3,000, 8,000, 16,000, 18,000, 20,000,
  22,000**; different at 22,500; past that the x64 runs are not deterministic (runs to 23,000 /
  23,500 / 32,000 fault in the native mesh decoder, nr_mesh.c `exec`, `dec->m` NULL; the run to
  24,000 does not).  Next: state trace of both exes over 22,000-22,500.  Bugs fixed on the way
  (each a stage rule): one-line declarations, `typedef struct {..} Name`, `(T *volatile *)` casts,
  `__attribute__` after a declarator, `Native *natives` (script VM natives table, 8-byte stride),
  `extern struct {..} *gEventContext`, s16 slot-call views, crt `size_t` stack arguments.

i686 gates (exe `out/x64/gate/rg-game.exe` = build/x64i-i686; script `out/x64/gates.sh`):
regen --check 300 + verify **8/8** (run hash and frame; the regen-written save2 card differed
and was restored from the backup, as in soak2); bootcheck --all **29/29 PASS**; mapcheck **5/5 DRAWN**;
`link_audit check --forbid all --extra rg_ps2_hwbus` PASS; `addr_census --check` PASS (0 arith, 0
marker); render_gate.sh x64lane: route 24 fields failing 0 (run hash emu = native ab389a3d1d0232e0),
8 boot fixtures PASS, mapcheck 5 DRAWN, close-up 38.3 dB; ctest -j2 -LE fixtures **741/741** (7
skipped: realdata, game_replay, readback_lag) + -j1 -L fixtures **7/7**.  x64 (build/x64-windows):
ctest -L x64 5/5 + -L x64-long 2/2 (`x64.layouts` 2,994 records 0 differ; control 246 differ).
Not play-tested.

## 2026-10-25 (checkpoint 13): character poses interpolated (opt-in); display-delay lead measured, kept off

Renderer lane (docs/NATIVE-RENDER.md "Checkpoint 13"; build `build/interp2-i686`, gate exe
`out/interp2/final`).  Only `src/native/render/nr_interp.[ch]` and `nr_iprec.cpp` changed;
nothing new runs with `display.interpolation` off.

1. **Poses.** With interpolation on, characters (the offscreen composites: parts drawn into a work
   buffer, copied into the frame by strips cut for the recorded box) now show in-between poses:
   `RG_INTERP_ZSCALE=4` (new default inside the opt-in feature) draws each composite call's parts
   with the bones interpolated (camera / object rows as recorded), moves the call's copy by its own
   pair's centres and widens the copy and the work buffer's clear to the union of both frames'
   boxes, so no limb is cut.  Calls that cannot be paired fall back to checkpoint 12's placement.
   Interpolating the parts' camera rows too lost the hero's cape for 2-3 presents per game frame
   (Salgin walk), so bones only.  ch07_rosa battle at a simulated 144 Hz (123 presents, characters
   isolated on a cleared frame): switch ratio 2.03 -> 1.18 (1 = even motion), step judder
   0.64 -> 0.34; real image: switch ratio 2.32 -> 1.52, step judder 0.53 -> 0.33, pops 0; run hash
   on = off (88081d075183d936); census mesh items interpolated 31.2 -> 97.4 %.  Montages
   `out/interp/pose/c13_iso.png` / `c13.png`, walk `out/interp2/c13walk_montage.png`.
2. **Display delay.** Measured, not shipped: `RG_INTERP_LEAD=x` extrapolates x game frames past the
   newest frame (x frames less delay); at 0.5 / 1 the isolated pose switch ratio goes 1.18 -> 1.59 /
   1.87 (real image 1.52 -> 1.74 / 2.04: an overshoot at every change of motion), so the default stays 0 (one game frame of delay, 33 ms at 30 Hz
   logic).  Trade-off in NATIVE-RENDER.md 13b.
3. **Tools:** `tools/native/interp_pose.sh` (battle route per ZSCALE mode, isolated and real) and
   `interp_pose.py` (crop step judder, peak share, **switch ratio** with `--switches REF`,
   montages); `RG_INTERP_ISOLATE=1` (measurement: the composite characters alone, scene depth
   kept); `RG_INTERP_DEBUG` prints each strip group's pose decision (why codes).

Gates (interpolation off, exe `out/interp2/final`): `link_audit.py check --forbid all --extra
rg_ps2_hwbus` PASS; `addr_census.py --check` PASS (0 arith / 0 marker); `regen.py --check 300` +
`verify.py` 8 / 8 (battle + 300 run hash ad41eb7c5ccf63f7, as before; the regen's save2 card differed
and the backup was put back); `bootcheck.py --all` 29 / 29; `mapcheck.py` 5 / 5 DRAWN; ctest -j2
747 / 748 (7 skipped as usual), the one failure `sound.hd_real` a 120 s timeout on the loaded machine
that passes alone (0.15 s); `render_gate.sh` (oracle twin
`out/interp2/oracle`, tags c13r + c13b) x1: route 24 fields PSNR min 31.31, failing 0, run hash emu =
native ab389a3d1d0232e0; 8 boot fixtures PASS with equal run hashes; mapcheck 5 / 5; close-up x3
38.25 / 38.33 dB.  Interpolation on: run hash = off on every measured run (battle 88081d075183d936,
walk 555dcdd095e9a8ba), exact-replay checks all same.

Open: a real 144 Hz play-test; calls that fall back to placement (2,550 of 10,302 groups in the
battle window: unpaired or no clear found); rigid (non-skinned) composite parts still move only
with their call's copy; Salgin close-up crop dominated by the pan (switch ratio 2.10 -> 2.01).

## 2026-10-25 (vulkan): a Vulkan backend for the native renderer (Linux prerequisite)

Lane "vulkan" (docs/NATIVE-VULKAN.md). The native-only device had one `GpuBackend`, Direct3D 11;
`src/native/render/nr_vulkan.cpp` is the second (Vulkan 1.3: dynamic rendering, push
descriptors, fragment shader interlock for the ordered views, dual-source blending; volk loads
the loader at run time, VMA for memory). **Decision: Vulkan, not SDL_GPU** (SDL_GPU has no
ordered views, no fragment-shader storage writes, no dual-source blending, no texel buffers;
table in NATIVE-VULKAN.md). Shaders: the existing HLSL compiled to SPIR-V by DXC at build time
(`nr_vulkan.cmake`, 24 entries); one `#ifdef __spirv__` annotation in `nr_draw.hlsl` (dual-source
output index; fxc output byte-identical).

Selection: setting `display.backend` (d3d11 default, vulkan; restart) or `RG_GPU_API=vulkan|d3d11`;
Vulkan unavailable -> stderr line and D3D11. Hooks outside the new files: `gpu_config.api`
(gpu.h), the setting (rg_settings_core.c), two lines in runtime.c `gpu_start`, the backend choice
in nr_dev.cpp `gpu_create` (D3D11 call now `_WIN32`-only), the include in the render
CMakeLists, the prototype in gpu_internal.h. Third party vendored under `third_party/`
(Vulkan-Headers Apache-2.0/MIT, volk MIT, VMA MIT; THIRD_PARTY_NOTICES.md, `third_party/VENDORED.txt`);
DXC is a build tool (`tools/native/fetch_dxc.py`, `../tools/dxc`).

Found and fixed on the way (route comparison against D3D11): (1) DXC's ordered views lack the
`Coherent` decoration -> stale interlocked reads (speckles on the town ground); the backend adds it
when loading fragment shaders. (2) NVIDIA's Vulkan biases `FragCoord.z` as UNORM24 when no depth
attachment is bound, which hid the town sky glare behind far geometry (25.7 dB); ordered-depth draws
now get no rasterizer bias (the shader's 2 units stay), D3D11's own no-DSV bias is not reproducible
exactly (measurements in NATIVE-VULKAN.md "Depth bias").

Results (exe `out/vk/b8/rg-game.exe`, build `build/vk-i686`): Vulkan vs D3D11 on the golden route
(new `tools/native/backend_compare.sh`) 24 fields, 6 identical, PSNR min 45.6 dB, 0.00 % bad, run
hash identical; D3D11 output pixel-identical to the 1025b gate. Gate with `RG_GPU_API=vulkan`
(render_gate.sh, oracle = emulated GS): route 31.45 dB min / 0.88 % bad / 0 failing (D3D11 31.31 /
0.91), all 8 boot fixtures PASS with oracle run hashes, mapcheck 5/5 DRAWN, save2 close-up x3
38.93 / 38.96 dB; link_audit `--forbid all --extra rg_ps2_hwbus` PASS, addr_census PASS. Not done:
zero-copy presentation (and so interpolated presentation) is D3D11-only, `readback_lag` and
`RG_GPU_PROFILE` not implemented; Linux CMake wiring without `rg_gpu` (NATIVE-VULKAN.md
"Linux: what remains"; the backend, nr_dev.cpp and nr_iprec.cpp compile for i686-linux-gnu).

## 2026-10-25 (soak2): widened soak: abilities, map sweep, factory power cords; two overrides

Lane "soak2" (the first soak's limits: fixed story points, one map per card, no abilities, no
factory production, no story Insectron). Builds `build/soak2-i686` (-O2 native-only, 05:58) and
`build/soak2-ubsan-i686` (RG_UBSAN=ON, 06:17); snapshots `out/soak2/exe-o2`, `exe-ubsan`; runs
`out/soak2/` (game-derived, not committed). Docs: TEST-FIXTURES.md "Widened soak" (tools, results
table), SAVE-FORMAT.md "Abilities".

**Tools.** `saveedit.py --abilities` / `--learn` (the section's #106 abilities as
`CharaLearnAbility_3ad460` stores them: learned u64 at Chara +0x2E0, actives in the 10 equip
slots, Burning Strike sets flags 1005/1006; checked in a battle: Jaster's Flash Sword / Break Throw
/ Whirlwind listed and used); `make --wide --maps` (`w_<library card>` with abilities + Burning
Strike, `m_<jump>`: 77 jump points spread per planet at the late story point);
`autobattle.py --wide` (abilities, items, voluntary leader switch, gun, cut-in handling);
`soak.py --wide --maps --fast-boot` (+ zone coverage, CROSS-through walks, game over continuation),
`soak.py fights` (one --wide fight per card, lost fights played through the game over),
`soak.py coverage`, `report --baseline`; `factory.py --plan --cords --produce` (power cords,
floor edits, profiles); recipes `factory_parts`, `insect_story`.

**Coverage.** -O2: 105 cards, 309,160 fields, 13 soak battles + 13 fights (8 won, 4 lost, 12 timeout,
1 leader-switch loop, 1 ended in the item screen (tool, fixed)), 57 ability uses / 52 cut-ins, 18 battle items, 20 voluntary
leader switches, 112 gun segments; zones 39 distinct (planets 1-9: 31 of 36; ghost ship EX 7 floors;
Alistia 1/4); 177 heap walks clean. UBSan: 97 cards, 211,047 fields, 11 battles, 26 abilities,
134 heap walks clean. Game over (lost fights): GAME OVER -> loading -> logos / intro, no hang.
Factory: power cords power every part, Run accepted ("OPERATING"); no item yet (game rules:
"Not all materials arrived at the assembler on time" on the raw template, "improperly processed
materials" on the equalised / Freeze layouts). Story Insectron: not reached (needs caged insects,
inventory kinds 4-6, not writable by the editor).

| # | Finding | Class | Status | Repro |
| --- | --- | --- | --- | --- |
| 1 | Battle ability list: scroll thumb drawn over the list header (host NaN from `(x - end) / 0` in `UiPageScrollBarSized_2891e0`; EE DIV.S by 0 = +-MAX) | override (EE-float residue) | FIXED `overrides/src/main/ui/UiPageScrollBarSized_2891e0.c` | card w_ch07_rosa, `autobattle.py prep`, TRIANGLE (battle menu) + CROSS (Abilities): UBSan float_cast `normal_BtlChgMenuAbilityListCursorBobCb_502150` / shot `out/soak2/thumbm` |
| 2 | Ally route thresholds read past `thr[4]` / `thr2` / `thr3` (waypoint kind 4); retail reads the frame neighbours v250.x / thr[0] / v200.x | override (stack layout) | FIXED `overrides/src/main/ai/AiRouteMoveToPosMaybe_2beed0.c` | cards w_ch04_prison, w_ch05_factory soak (UBSan bounds `AiRouteMoveToPosMaybe_2beed0.c:418`) |
| 3 | FACTORY menu exit open loop failed (menu wraps, CIRCLE hides it) | tool | FIXED (soak.py `factory_menu_row`) | m_81 / w_ch11_mariglenn / w_space_deck menu pass row Factory |
| 4 | Battle item screen (17/200) ended the autobattle | tool | FIXED (autobattle SUBMENU) | w_ch10_kuje soak battle |
| 5 | Factory production stops on game rules (timing / processing) | game rule | open (needs a processed-material layout) | `factory.py run --card factory_parts --plan healing_eq --cords --produce 3000` |
| 6 | `factory_FactoryStep_5069e0` override: `struct S` 16-aligned over 8-aligned part groups | misaligned class (risk if clang vectorises) | noted | w_ch08c_zerard UBSan soak, factory menu |
| 7 | Story Insectron reward path unreachable from a card | coverage gap | open (cage / insect objects) | `insect_story` card |

UBSan sites new to soak2 (16): 4 struct / extern view classes (aliases into the contiguous
`D_00480390` blob, `S2C0.arr[3]`, `Ai.info[4]`), `EvTargetSetGetTargets_336940` `&NULL->sub`
(address only), the FactoryStep misaligned rows (6), and the two fixed sites (1, 2): after the
fixes, the alt UBSan exe's rerun of w_ch04_prison / w_ch05_factory / w_ch07_rosa / w_ch03_falls
(same battles, same ability uses) has neither row.

**Gates** (exe `out/soak2/gate/rg-game.exe` = `build/soak2-i686` rebuilt with the two overrides,
current tree; script `out/soak2/gates.sh`): `regen.py --check 300` OK + `verify.py` **8/8** (run hash and frame; the save2 card it wrote differed and was restored from the backup); `bootcheck.py --all` **29/29 PASS**; `mapcheck.py` **5/5 DRAWN**; ctest -j2 -LE fixtures **741/741** (8 skipped: realdata, game_replay, readback_lag, link_audit_control) + -j1 -L fixtures **7/7**; `ingest.py --check` 0 problems (244 overrides; no re-ingest: no stage change). Also: `factory.py --plan healing_eq --cords --produce` on the UBSan exe (same verdict; its only rows new to the soaks are the FactoryStep misaligned class, 6). Not play-tested.

## 2026-10-25 (x64 census): P7 readiness measured; plan = a 32-bit game address space on x64

Census and plan only. No game/, stage, override or src/ change; full write-up in
docs/X64-PLAN.md. New tools: `tools/census/x64_census.py` (text census of the built game
tree), `x64_probe.py` (every TU of build/soak2-i686 recompiled for x86_64-pc-windows-msvc,
diagnostics by class, i686-vs-x64 record layouts), `x64_ptr32_trial.py` (a throwaway
`__ptr32` rewrite of every 10th game TU) and `x64_infra.py` (i686 assumptions in
src/tools/tests). Scratch toolchain: `cmake/toolchain-x64-windows-clang.cmake`. Output:
`build/x64-probe/`.

Results:

- **Probe:** 25,796 TUs, 1,129 fail. 1,093 are data2c and 21 generated overlay tables
  (`(u32)&X` static initializers are not constants on x64: about 16.7k words); the rest are
  the crash handler, trampoline `#error`, `sizeof` asserts, 4 libc redeclarations and test
  files. Only 5 ordinary game TUs fail.
- **Silent classes:**
  - 25.7k `-Wint-conversion` (u32-held pointers), 19.6k pointer-to-int, 6.3k int-to-pointer;
  - 789 libc redeclarations with 32-bit sizes;
  - **4,514 unique game records change layout** (3,707 offset-coded), 5,911 instances in
    3,880 of 18,987 game TUs.
- **Census:** 7,507 pointer members in 5,642 records, 2,637 `*(T **)` loads, 2,133
  pointer externs aliasing data2c/bss words, 201 naked i686 forwarders (protos
  `def-vthunk-naked`), 33 in-place asset relocations (ModelRes/MotRes/NavGraph/ScriptVm),
  2,016 devirt `u32` vptrs (already fine).
- **Low memory:** a `/LARGEADDRESSAWARE:NO /DYNAMICBASE:NO /BASE:0x400000` x64 exe kept
  heap, stacks, a hardware D3D11 device, mapped buffers and 53/54 DLLs below 2 GB (only
  ntdll high). ADDR32 data relocations work. **lld does not diagnose an ADDR32 overflow
  with the default base** (silent crash: needs a link gate).
- **LLVM bug:** a call through a `__ptr32` function pointer crashes isel or, as a tail
  call, miscompiles to an 8-byte load (repro `build/x64-probe/lowmem/t8.c`). Function
  pointers must stay out of `__ptr32`.
- **Trial:** differing records 606 to 6 (99%) on 1,915 TUs. 13 TUs hit the wanted
  "changes address space of nested pointer" error (`T **pp = &s->p32`).

Recommendation: strategy A (32-bit game address space: LAA:NO exe + `ptr32` stage +
datareloc ADDR32 + x64 fiber/trampoline/thunk/samplers), 8.5-12.5 lane-days, all retail
layouts, assets, saves and the trace map unchanged. True 64-bit pointers (B) are estimated
at 40-80+ lane-days. macOS arm64 cannot use A (R5). PLAN.md P7 points to the plan.

## 2026-10-25: play-test build 1025b (return-to-title fix, protos rules, D9 address gate, protos manual rows)

**Build.** New script `tools/playtest/build_playtest.py --tag 1025b` (the 1024a / 1025a recipe in
one command: ingest check, configure + build in an own dir, snapshot, gates, copy + .bat update,
windowed smoke; summary in `out/regress1025b/summary.tsv`). `ingest.py --check` 0 problems (26,291
manifest rows, 244 overrides): game/ = the 09:17-09:22 protos re-ingest, no re-ingest here. Fresh
`build/pt1025b-i686` (Release, RG_GAME_OPT=-O2, RG_NATIVE_ONLY ON, RG_NATIVE_OVL ON, RG_VU0_MODE
native, no UBSan / sbguard = build/play-i686's cache), `rg-game` + `rg-game-oracle` -j4, 25,898
steps, 0 errors, 52 warnings, 10:29-10:50 (`out/regress1025b/build.log`). No source file changed
between configure and the end of the gates. Snapshot `out/regress1025b/rg-game.exe` (+ .map,
9,126,400 bytes) = `out/playtest/rg-game-1025b.exe`; play.bat / play-from-save.bat /
play-test-save.bat launch it; older exes kept. Cards not re-made.

**Contents vs 1025a** (1025a = tree of 05:00):
- Insectron "Return to title" and game over -> title (session shutdown hang): the
  EffTableDestroyAll spin (bug 2 of "2026-10-25 (stream close)"), now by the protos `short-agg`
  rule (06:56 re-ingest; the 05:20 effect overrides retired). The slot-kick override (bug 1) was
  already in 1025a.
- MSL iostream overrides: NumPutDoubleThunk_1b2840, OstreamWriteFloat_1b25c0,
  OstreamWriteBool_1b2710 ("2026-10-25 (sweep)"), NumPutFixedZeroStrMaybe_1b3c90.
- D9 address arithmetic ("2026-10-25 (D9 address gate)", 07:57 ingest): GS privileged / VIF1_FBRST /
  logic T0 through native register calls, PS2_PHYS / UNCACHED / UCAB markers stripped, the
  SysCalcFreeHeapMaybe / DrawList* / GfxVblankStartHandler overrides, KernelReleaseAlarm port-provided.
- Protos manual rows ("2026-10-25 (protos manual rows)", 09:22 ingest): landing-flag bool read
  through an s32 view (CharaCollClampFloorCeilingMaybe_2364e0), gaiji glyph colour passed by
  address (FontDrawGaiji_26dd50, 3 callers), VecSolveDistanceConstraint_364740 extra lane, 5
  narrow-return views, TaskStepJudgeObject_3135c0 declarations.
- Renderer checkpoint 12 (z-scale composites in the opt-in interpolation, `RG_NR_REINT=1`
  format-changing views, kept title-movie transfers made into words lazily).
- Ally route thresholds (AiRouteMoveToPosMaybe_2beed0) and battle scroll thumb
  (UiPageScrollBarSized_2891e0) overrides of 08:3x.

**Gates** (`out/regress1025b`, all PASS): regen.py --check 300 exit 0 (save2 card differed after
regen -> restored from the backup) + verify.py **8/8** (run hashes = 1025a's); bootcheck --all
**29/29**; mapcheck **5/5 DRAWN**; `link_audit.py check --forbid all --extra rg_ps2_hwbus` PASS (0
pending emulation libraries); `addr_census.py --build build/pt1025b-i686 --check` PASS (0 arith,
0 marker); render_gate.sh x1 PASS (route PSNR min 31.31, 0 failing, emu = native run hash
ab389a3d1d0232e0; 8/8 boot fixtures PASS; map 5 DRAWN; save2 close-up x3 38.25 / 38.33 dB;
`out/nrender/runs/gate_pt1025b.txt` + `gate_pt1025b_rest.txt`: the first run was stopped by the
agent shell's 2 h background limit after 4 boot fixtures, the other 4 + map + tex re-run);
insectrun.py --title done (TITLE ovl 2, 3/201 at 21,100); gameover.py title+continue (lost 5,090,
TITLE 5,820); factory.py every phase ok (Run refused, factory not ready; exit to field ok);
FACTORY Place repro (soak o2/002, ch06_mines, 5,700 fields) rc 0, no exception. Windowed smoke
from out/playtest (double-click style, 1,600 fields): D3D11 native device on the RTX 3080, rc 0,
run hash c1d233bd0e9574b3 (= 1024a / 1025a). ctest not run (not a play-test gate; 742/742 on
build/addr-i686 and 748/748 on build/protos2-i686 today). Not play-tested.

## 2026-10-25 (protos manual rows): every row the protos stage left for a human closed; 4 rules, 2 one-site fixes, an IR ABI audit of every call

Several bugs this week came from rows the protos stage logged and left (dropped arguments, short
declarations, return-width views). Task: a verdict for every manual / unresolved row of
game/PROTOS.tsv, real bugs fixed, shapes with >= 2 sites made rules, checks in ctest. Build
`build/protos2-i686` (native-only, fresh), gates `out/protos2/gates/`, scratch `out/protos2/`.

**Tools (mechanical evidence, reusable):**
- `tools/bringup/protos_irabi.py`: compiles a caller and the callee's definition (override /
  missing / provider header when that is the truth) with the build's own compile_commands to
  LLVM IR and compares the lowered i686-windows-msvc signatures (stack words; aggregates by
  value vs by ADDRESS; return class and width; sret). Default: the manual-call / manual-decl
  pairs (~1 min cold). `--all`: every direct call of every compiled unit (25,293 units, 90k
  calls, ~2.5 h cold at -j3, summaries cached in out/protos2/ir/sum).
- `tools/bringup/vslot_reads.py PKL SLOT.. | --fn F`: methods at a vtable slot (sbresolve's
  vtable scan) and whether their listings read given argument registers; `--fn` follows jalr
  slots (over-approximate).
- `tools/bringup/protos_manual.py`: joins irabi, abi_census vvz, the stack-block census, the
  callers' listings (reverse jal index + `reg_after_call`) and a REVIEWED table into
  **census/protos_manual.tsv** (one verdict + evidence per row).

**Counts.** Before (game/ 07:06): 1,318 manual/unresolved rows, 96 verdicted (stack-block
census), 1,222 open. First pass: 12 BUG rows (6 call sites), 88 needs-retail-check (76 vcall
rows delegated to a review by receiver class family: all OK; 8 manual-missing: all OK by port
arity; 4 vvz: dead C locals), the rest OK. After (re-ingested): **1,308 rows = 1,301 OK,
5 fixed-override, 2 fixed-rule, 0 BUG, 0 needs-retail-check**; 10 rows gone (fixed by rules).
Missing-args re-check (PROTOS-MISSING-ARGS.md): missing-zero 7 / manual-missing 15 all OK
(lanes reach only methods that do not read them / port definitions with fewer parameters),
missing-unused 276 exact, missing-dead 631 = source never passed the argument.

**Real bugs found and fixed:**
1. **CharaCollClampFloorCeilingMaybe_2364e0 (the lead):** `#define RT bool` return read as an
   unknown type -> out of the header -> CharaMoveCollideMaybe_234dc0's `s32` view tested
   `!= 0` on AL + garbage upper EAX (clang: `setcc al`; retail `beqzl v0`): spurious landing
   flag 0x1000 / x410 timer. Fix: object-like type macros resolve like typedefs; the call gets
   `ret-narrow`.
2. **FontDrawGaiji_26dd50 colour (3 callers):** views pass an `aligned(8)` RGBAQ / RGBA by
   value; MSVC x86 passes such an aggregate BY ADDRESS, the definition reads `s64 rgba` = the
   pointer + a stale word (every gaiji glyph from FontDrawText_26cdc0, FontDrawTextGradient_26c6e0,
   MesWinDrawGlyphs_271b70). The alignment comes from the dialect stage's bitfield-gcc pin on
   `u64 r:8..` runs. Rule `agg-view` / `agg-bits` (`__builtin_bit_cast`).
3. **VecSolveDistanceConstraint_364740 from EvMapObjPartStep_363ba0:** the view's extra `u128`
   (retail `$a2`, never read) was a pointer word in front of the floats: distance = pointer
   bits, scale = distance. Rule: `u128-view` extra lane (dropped).
4. **5 C++ views reading narrow returns through pointer / wider types** (whole-corpus audit, not
   manual rows): EventSysUpdate_26ac10 `ObjRecHasFlags6_1c3eb0(..) == 0`, EvCmdEventStartMaybe_248450
   (CharaGetId as a script argument), MapAreaRelease_1d9ee0 (MapDataGetId),
   OstreamWriteCStr_1a1dd0 (IosGetFlags), MenuItemOpenState_2b2870 (`s16` view of `u8`). Rule
   `ret-narrow-view`.
5. **missing/src/main/sys/TaskStepJudgeObject_3135c0.cpp** (C port of an excluded asm unit):
   `s32` views of the `s16` CharaGetBaseActionMode_213830 / CharaGetId_214a80 (`== 0` and
   ActorFindById on garbage upper bits in the chara stomp judge): declarations fixed.
6. **NumPutFixedZeroStrMaybe_1b3c90:** its own view passed the size as u64 to
   StringReplaceRange_1b3da0's s32: every later argument one slot off. Override
   `overrides/src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c` (MSL num_put; untested path).
The audit's control (`--ignore-overrides`) re-finds every call the earlier 2026-10-25 overrides
fix (NumPutDouble/Bool thunks, OstreamWrite*, RevelationBoardDrawSprite) by itself.

**Re-ingest** (one, 09:17-09:22, after the address-arithmetic lane's 07:57 ingest, no other
ingest/ninja running): 13 files written (10 staged units, game_protos.h, PROTOS.tsv, MANIFEST),
tree 2f8235b2..; `ingest.py --check` 0 problems (244 overrides). protos_pre with all four
switches off vs on: exactly those 10 units + the header differ.

**Gates** (`out/protos2/gates/rg-game.exe` = build/protos2-i686): regen.py --check 300 exit 0
(save2 card differed after regen -> restored from the backup, as in the sweep) + verify.py 8/8
(run hashes and frames unchanged: no golden re-time); bootcheck --all 29/29 PASS; insectrun.py
--title done (TITLE ovl 2 at 21,100); gameover.py title+continue (lost 5,090, TITLE 5,820, field
~10,780); factory.py same verdict (Run refused, exit to field ok); ctest -j2 748/748 passed (8 skipped: real-data / GPU replay / link_audit_control), incl. the new protos.manual(+control), protos.irabi(+control), protos.stage_control_abi3, protos.abi_control_abi3.

**Checks:** ctest `protos.manual` (+ `_control`), `protos.irabi` (+ `_control`) via
tools/bringup/protos_deficits.py `--manual` / `--ir BUILD`; fixture tests/protos/fixture/src/main/abi3
(`protos.stage` 4 checks, `protos.abi` 4 runtime checks; controls `protos.stage_control_abi3`,
`protos.abi_control_abi3` = `run_stage.py --fault abi3`, every check fails there).

Files: new tools/bringup/{protos_irabi,protos_manual,vslot_reads}.py, census/protos_manual.tsv,
overrides/src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c, tests/protos/fixture/src/main/abi3/* (+ a
listing in fixture/asm/main.s); edited tools/stages/protos.py (`_agg_views`, `_explicit_align`,
`_dialect_bitfield_align`, `_def_reads_reg`, u128-view extra lane, `ret-narrow-view`, type
macros in parse_file), tools/bringup/protos_deficits.py, missing/src/main/sys/TaskStepJudgeObject_3135c0.cpp,
tests/protos/{CMakeLists.txt,run_stage.py,test_main.c}; docs PROTOS.md ("Manual rows closed"),
PROTOS-MISSING-ARGS.md ("Re-check"), BRINGUP.md (fix-class table, tools).

## 2026-10-25 (D9 address gate): no PS2 address arithmetic left in the compiled game set

Second half of the D9 build gate (PLAN.md "Native end state"; the link half was the "D9
residue" entry below). `tools/native/addr_census.py --build build/addr-i686 --check`: **PASS,
0 arith / 0 marker** (was 36 / 44). New ctest `native_only.addr_census` (fails on any arith or
marker site) + `native_only.addr_census_control` (`--inject`: one synthetic site per kind, must
FAIL), label `native_only`, pure text, every build.

| Kind (class) | before | after | how |
| --- | --- | --- | --- |
| hw (arith) | 10 | 0 | hwaccess stage pass `NATIVE_REGS`: GS privileged -> `rg_gs_reg_r64 / w64(RG_GS_<REG>)` (register id = the renderer's `preg[]` slot; nr_hw.c native, hwbus.c oracle twin), VIF1_FBRST -> `rg_vif1_fbrst_w32`; the GfxVblankStartHandler_15df20 override by hand |
| logic-t0 (done) | 6 | 0 | same pass: `rg_logic_t0_count / _set_count / _set_mode` direct (now `native-reg`, done: 13 calls) |
| data-hw (arith) | 18 | 0 | `dead-data` (inert): reachability over D_ references from compiled code; D_00445F20 (libdma channel table) and D_00446648 (kernel TLB table, reached only by D_004468F8 <- the excluded asm InitTLB32MB_1200f8) are unreachable |
| lit-spr (arith) | 5 | 0 | 1 dead-data (D_00446648); 4 `dmatag` (reviewed REVIEWED rows: DMAtag END ids in GfxEndFrame_141c20, the VIF0 init packet D_00445810, a GS packet D_00455310, libpkt open_tag) |
| lit-hw (arith) | 1 | 0 | KernelReleaseAlarm_4473a0 (kernel-RAM body of the ReleaseAlarm syscall: INTC poll + T3 via 0xB000xxxx, no game caller) -> `overrides/PORT_PROVIDED.tsv` (the port kernel owns alarms); the census now also flags KSEG0/1-mirrored hardware pointers |
| ps2-addr-def (arith) | 2 | 0 | SysCalcFreeHeapMaybe_15e1d0 override: retail `32 MB - 0x2000 - stack - end` = heap size - 0x2000 -> `rg_crt0_heap_size() - 0x2000` (new in crt0.c; same value 0x1AA5E00) |
| mask (marker) | 32 | 0 | the stage strips PS2_PHYS / UNCACHED / UCAB sites to the operand (identity on host pointers; HWACCESS.tsv keeps the list); 3 overrides by hand (DrawListFrameBegin, DrawListEndPrim, DrawListEmitBucket's ADDR macro -- the census now also sees markers inside macro bodies) |
| lit-kseg (marker) | 12 | 0 | `flag` (inert): the stage's reviewed LEAVE_RULES (flag bits, DMAtag / CHCR REF ids) + crt_eelibm's sqrt bit trick |
| raw-word (inert) | 95 | 95 | datareloc data words, unchanged |

One re-ingest of game/ (33 files, all hwaccess output; tree 378f9f02...); 7 override headers
rehashed (`tools/ubaudit/rehash.py`: content unchanged). Tests: `tests/hwbus/test_stage.py`
updated for the new spellings (+ native-register and header-id tests). Docs: HWBUS.md "Native
register sites", NATIVE-RENDER.md "Hardware register sites", NATIVE-ONLY.md, PLAN.md gate
definition.

Gates, build/addr-i686 (`out/addr/gates`): regen.py --check 300 + verify.py **8 / 8** (run
hashes identical to nd9 / 1025a / g12; card save2 restored); bootcheck --all **29 / 29**;
mapcheck **5 / 5 DRAWN**; link_audit check --forbid all --extra rg_ps2_hwbus **PASS**;
render_gate x1 **PASS** (route PSNR min 31.31, 0 failing, emu = native run hash
ab389a3d1d0232e0; 8 boot fixtures PASS); ctest -j2 -LE fixtures 735 + -j1 -L fixtures 7: **742 / 742** (incl. the two new addr_census tests and the updated hwbus.stage_unit). Exe 9,126,912 bytes.

## 2026-10-25 (sweep): both stream-close bug classes swept game-wide; game over -> title -> CONTINUE

Follow-up of "2026-10-25 (stream close)" below: sweep its two bug classes over the whole game,
add automated checks, exercise the other session-shutdown paths. Build `build/sweep-i686`
(native-only, fresh), exe snapshot + runs `out/sweep/` (game-derived, not committed).

**Class 1, busy-wait on a driven thread: census `tools/census/driven_wait.py`** (docs/SPIN.md
"Driven threads"; retail loops from the spin census's loader, the driven conversions parsed
from the overrides' `rg_thread_conv`, sema ids at every SignalSema / iSignalSema / WakeupThread
/ ResumeThread site from a register simulation, driver points = WaitVsyncCount / DelayThread /
sceGsSyncV / VSync / RotateThreadReadyQueue / ThreadYield + any function whose override calls
`rg_frame_point` / `_delay` / `_wait_cond` / `_yield` / `_frame_wait` + spin-hinted loops).
7,895 retail loops; 151 wake a driven thread: 141 WAKE-SYNC (only `sync` steps above the
signaller's priority: they run at the signal), 4 WAKE-DP (driver point every iteration:
MoviePlayModal x2 and the two inner kick loops of `SoundStreamSlotShutdown_1bdfd0`), 4
WAKE-DP-SOME reviewed (its two outer loops: every iteration pushes a command, so the inner loop
kicks; `GameFrameUpdate_27c4c0` / `GameModeDispatch_27c670` mode re-dispatch: no exit on slot
state), 2 WAKE-ONCE (StreamMgrCloseAll / StreamMgrUpdate: per-channel signals, the step runs at
the caller's next driver point), **0 BUSY-WAIT** (2 without the overrides' driver points: the
two loops fixed by `SoundRpcWorkerKick_1bd6a0`, so the census finds the known bug). The other
hole of the spin census, loops SAFE only through a non-driver-point WaitSema that poll memory
written by a driven thread / an ISR: 5, all in replaced SDK code (sceSdRemoteInit, scePadInit
x2, sceMcInit, SceFsInit). **No new real bug in class 1.** ctest `spin.driven_wait` (fails on
an open row) + `spin.driven_wait_control` (`--no-overrides`, WILL_FAIL); both skip without the
retail images.

**Class 2, arguments dropped by short local declarations.** Open sites fixed by override:
`overrides/src/main/libc/NumPutDoubleThunk_1b2840.c` (the thunk's retail is `jal
NumPutDouble_1b29d0` with $a0..$t0 passed through; the decomp's thunk took 2 params and called
with 1 of 5), `OstreamWriteFloat_1b25c0.cpp` and `OstreamWriteBool_1b2710.cpp` (MWCC returns the
iterator through a hidden $a0 pointer, the definitions take it as a plain first parameter;
i686/MSVC returns a 4-byte struct in EAX, so the stream buffer was passed as the out pointer and
NumPutBool's value was a stale word). MSL iostream writers of the motion-event text dump: no
tested path reaches them; compile + link checked (altlink), shapes from the listings. **Stage
rule `short-agg`** (protos, docs/PROTOS.md): a C file's short view of a definition kept out of
game_protos.h only by word-size by-value aggregates gets the missing slots (`int` for the
aggregate) and the missing arguments from the usual passthrough / entry / listing rules; a
site with an unknown value is left for an override. On the corpus exactly the 4
`HandleTableGet_1a1d50` effect sites (protos_pre with / without the switch: no other staged
file differs), the same code as their 2026-10-25 overrides, which are **retired**
(`overrides/src/main/effect/EffDef{Destroy_1a0a90,UnlinkByHandle_1a0040,
DestroyInstancesByTag_19ff40,GetDurationByHandle_1a0a50}.c`; copies in out/sweep/retired).
`protos_deficits.py` now also flags by-value struct-return views against a scalar definition
(sret); 4 sites left, all overridden (the 3 above + RevelationBoardDrawSprite). ctest
`protos.deficits` + `protos.deficits_control` (`--ignore-overrides`, WILL_FAIL); fixture
`abi2/HandleGet_401900.c` / `HandleUser_401940.c` with `protos.stage` + `protos.abi` checks and
controls `protos.stage_control_shortagg`, `protos.abi_control_shortagg`. Re-ingest (one, 06:56-07:07):
6 files written (4 effect units, PROTOS.tsv, MANIFEST), `ingest.py --check` 0 problems, 241
overrides. Found on the way: the manual row `CharaCollClampFloorCeilingMaybe_2364e0` (`ret int vs
RT`, RT = `#define bool`) reads a bool through an s32 view (ret-narrow shape, not a short call;
not changed).

**Class 3, game over and the other session ends: `tools/fixtures/gameover.py`** (new;
TEST-FIXTURES.md "Game over"): card `gameover_ch01_salgin` = ch01_salgin + party cut to Jaster +
every HP = 1; autobattle prep's box walk meets the first encounter (fight at 4,840), no input:
lost (7/701) at 5,090 ("Jaster was defeated..." waits for a press), CROSS every 120 fields:
**TITLE (ovl 2) at 5,820**, then CONTINUE -> FILE 01 -> load -> recap: **field control (6/100) at
~10,780** (verdict `title+continue`). Also seen: with an empty saves dir the same CROSS presses
start a NEW GAME from that title (opening movie, Rosa desert at 8,244). Insectron Return to
title: insectrun --title (gates). Field system menu has no quit to title (stream close entry).

**Gates** (`out/sweep/gates/rg-game.exe` = build/sweep-i686 after the re-ingest, script
`out/sweep/gates/gates.sh`): regen.py --check 300 exit 0 (save2 card differed after regen ->
restored from the backup) + verify.py 8/8 (run hash and frame); insectrun.py run --title done
(TITLE ovl 2 at 21,100); gameover.py title+continue (lost 5,090, TITLE 5,820, field control
~10,780); factory.py same verdict as before (Run refused, exit to field ok); bootcheck --all
29/29 PASS; ingest.py --check 0 problems (241 overrides); ctest -j2 731/740 + 8 skipped
(real-data / GPU replay / link_audit_control): 1 failed, `hwbus.stage_unit` (5 asserts on
`PS2_UNCACHED` / `PS2_UCAB` spellings): tools/stages/hwaccess.py was changed at 07:39 by
another lane, after this sweep's re-ingest (06:56); not this sweep's files. New tests all pass
(spin.driven_wait(+control), protos.deficits(+control), protos.stage / abi short-agg checks and
both shortagg controls).

Files: new `tools/census/driven_wait.py`, `census/driven_wait.tsv`, `tools/fixtures/gameover.py`,
`overrides/src/main/libc/{NumPutDoubleThunk_1b2840.c,OstreamWriteBool_1b2710.cpp,
OstreamWriteFloat_1b25c0.cpp}`, fixture `tests/protos/fixture/src/main/abi2/{HandleGet_401900,
HandleUser_401940}.c`; edited `tools/stages/protos.py` (`_short_agg_sites`),
`tools/bringup/protos_deficits.py` (sret views, `--ignore-overrides`), `tests/protos/`
(CMakeLists, run_stage.py, test_main.c), `tests/spin/CMakeLists.txt`; retired the 4 effect
overrides; docs SPIN.md, PROTOS.md, NATIVE-THREADS.md, TEST-FIXTURES.md (also repaired 8
form-feed-corrupted `tools\fixtures` paths), BRINGUP.md.

## 2026-10-25 (checkpoint 12): composite placement, format-changing views, title transfers

Renderer lane follow-ups of checkpoints 10 / 11 (docs/NATIVE-RENDER.md "Checkpoint 12"; build
`build/nrf-i686`, gate snapshot `out/nrf/g12`).  No game/ change; run hashes unchanged.

1. **Z-scale composites in interpolated presents.** In battle 67 % of the mesh items are
   offscreen-composite character parts; checkpoint 11 left them at the latest frame.  Their own
   constants cannot be interpolated (they also place the part in the work buffer: the strips cut
   it).  Now (`RG_INTERP_ZSCALE=2`, default inside the opt-in feature) the device recorder finds
   the strip groups that copy the parts into the frame, pairs each character's union box with
   the previous frame's and moves its strips by the lerp of the two centres.  ch07_rosa
   auto-battle at a simulated 144 Hz (`tools/native/interp_fight.sh`): step judder 1.46 -> 0.53
   (snap 2.00), judder on the characters 1.95 -> 0.78, pops 0, exact-replay check 203 / 203,
   interpolation on = off run hash.  Salgin walk + pan: background judder 0.51 -> 0.22.  Pose
   still steps per game frame; display delay not reduced (needs extrapolation).
2. **Format-changing views** (BRINGUP item 8 leftover): backend `rt_reinterpret` (sub-sample by
   sub-sample through a scratch copy of local memory).  `RG_NR_REINT=1` (default): binds over a
   live target of another format and reads up to 4 texels past a target at the internal
   resolution: mirror reads `dir 2` 760 -> 0 on the battle at x3, images identical at x1 and x3.
   `RG_NR_REINT=2` (off): sampling a target as another format, `dir 4` 337 -> 34, but the CT16
   dust effect is blockier at x3.
3. **Title / menu ms after checkpoint 10**: the title movie's 1 KB CT32 macroblocks went through
   the palette "kept words" path (~400 per field).  Kept transfers are now stored as they came
   and made into words only when a CLUT load reads them (`RG_NR_KEEP_EAGER=1`: old path); worker
   transfer time 3.17 -> 1.65 s per boot:save2 run, CLUT results unchanged.  boot:save2 ms/field
   (base before 10 / checkpoint 11 / now): fields 0-999 1.50 / 1.97 / 1.28, 1,000-1,999
   1.74 / 2.46 / 1.58, whole run 2.36 / 2.10 / 1.71.

Gates (`out/nrf/g12`): ctest -j2 734 / 734; regen --check 300 + verify 8 / 8; bootcheck --all
29 / 29; mapcheck 5 / 5; render_gate x1 PASS (route PSNR min 31.31, 0 failing, 8 boot fixtures,
emu = native run hashes), x3 route 0 failing (30.76), 16:9 route 0 failing (30.78); run hashes
unchanged with interpolation off and equal with it on.

Tools: `tools/native/interp_fight.sh` (+ `interp_fight_rosa.route.txt`), `perf_exes.sh`,
`shotset_diff.py`; `interp_smooth.py` step judder.  Open: composites' pose, display delay, a
real 144 Hz play-test, `RG_NR_REINT=2` look at x3.

## 2026-10-25: play-test build 1025a (Factory Place fix, native overlays + VU0, no emulation library)

**Build.** `build/play-i686` reconfigured 05:00 (`cmake -S . -B build/play-i686`; `RG_NATIVE_OVL`
was not in the cache, so the ON default took: "overlays as native modules (no arena)"), then
`cmake --build build/play-i686 --target rg-game -j 4` (88 steps, 0 errors, 05:01-05:03,
`out/regress1025a/build.log`) + `-j 4` all for ctest (50 steps). Tree: the 01:21 re-ingest (datareloc
`_sub_` rule: `data2c_00468380.c` = the FACTORY Place crash fix), the soak overrides
(`SysMsgPostMaybe_1c3560` u8, Insectron reward lookup + `InsectBattleMatchUpdateMaybe_319800`),
D9 residue (native VU0, native overlay modules), checkpoint 11 interpolation (opt-in), parity data
overrides. Snapshot `out/regress1025a/rg-game.exe` (+ .map) = `out/playtest/rg-game-1025a.exe`;
play.bat / play-from-save.bat / play-test-save.bat launch it (play-test-save's comment now says 30
saves). Cards not re-made.

**Gates** (logs `out/regress1025a`, script `gates.sh` = the 1024a script + the soak's Place repro +
factory.py / insectrun.py): `regen.py --check 300` OK (save2 card differed after regen -> restored
from the backup) + `verify.py` 8/8 (run hash and frame); `bootcheck.py --all` 29/29 PASS;
`mapcheck.py` 5/5 DRAWN; `link_audit.py check --forbid all --extra rg_ps2_hwbus` PASS (0 pending
emulation libraries linked); FACTORY Place repro (`out/soak/o2/findings/002/poweron.input.txt`,
card ch06_mines, 5,700 fields) rc 0, no exception, factory floor at 4950 (`place/s4950.png`);
`factory.py run` every phase ok (verdict "refused (factory not ready)", exit to field ok);
`insectrun.py run` (no --title) done, battle 4,600 fields, back at INSMENU; ctest -j2 734/734
(8 skipped: 2 realdata, runtime.cdvd_realdata, 3 game_replay, readback_lag,
link_audit_control). Windowed smoke (`out/regress1025a/smoke`, double-click style from
out/playtest, `--fields 1600` + shots): D3D11 native device on the RTX 3080, data from the junction,
IOP native, title menu at 1500, rc 0, run hash c1d233bd0e9574b3 (= 1024a's smoke). Not
play-tested; Insectron return-to-title hang not covered (other lane).

## 2026-10-25 (stream close): every game-session shutdown hung (return to title); two port bugs, both fixed

The "Hang (open, native IOP sound streams): Insectron Return to title" of the overlay-coverage
entry below. Build `build/hang-i686` (native-only + oracle twin), exes `out/hang/fix2/`, runs
`out/hang/` (game-derived, not committed).

**Path.** Return to title ends the game session: `GameSessionShutdown_1f5bf0` ->
`StreamMgrCloseAll_1d6740` -> `StreamChanClose_1d6dc0` per open channel ->
`SoundStreamSlotFree_1bd3a0` -> `SoundStreamSlotShutdown_1bdfd0`, then `EffectMgrShutdown_2e3140`.
The same function ends every session (game over -> title too); no other route had ever run it,
so neither bug showed on the golden routes. `SoundStreamSlotShutdown_1bdfd0` is the only caller
of `SoundRpcWorkerKick_1bd6a0`.

**Bug 1 (threads lane, class: busy-wait on a driven thread).** `SoundStreamSlotShutdown` pushes
stop (2) / close (0xA) into the slot's command ring and loops `while (busy) kick()` until the
stream slot reports state 0 / 7. The kick signals the stream-slot thread's semaphore. On the EE
that switched at once to the slot thread (priority 15, main 20), which consumed the command and
woke the stream thread (15, also before main resumed). Natively the slot thread is a driven,
non-sync conversion (`rg_SlotWait/Step`): its step runs only at a driver point, and the loop has
none (no DelayThread / spin hint: the census classed it SAFE through `WaitSema(q->sema)`), so it
spun forever. Fix: override `overrides/src/main/sound/SoundRpcWorkerKick_1bd6a0.c`, the kick ends
in `rg_frame_point()` (a no-op outside the frame driver): the woken slot step and the stream step
it wakes run there, as on the EE. Scoped to the kick, not `sync` on the slot conversion: the
other game-flow signallers of that semaphore (`SoundStreamSlotQueueStop_1bcd40`,
`SoundRpcShutdown_1bc760`) do not wait, so their deferred step is the documented placement
difference, and the golden routes keep their timing (verify 8/8 below). Control: the same exe
with the game's kick (`altlink.py`, `out/hang/nokick`) stays at 11/0 in INSMENU past 19,600.

**Bug 2 (protos class: argument dropped by a short local declaration).** With bug 1 fixed the
main thread spun in `EffTableDestroyAll_1a0240` (hangsample: `EffDefDestroy_1a0a90` /
`HandleTableGet_1a1d50`): the loop destroys the table's first def until the list is empty, and
`EffDefDestroy` never found it. Retail passes the handle (entry `$a1`, never written before the
jal) as `HandleTableGet_1a1d50`'s second argument; the decomp declares the callee with one
parameter, and protos leaves it (`manual-decl` "count 1 vs 2": the definition takes a by-value
union `Handle`, so the callee is not in the header), so on i686 the callee read a stale stack word.
Same in `EffDefUnlinkByHandle_1a0040`, `EffDefDestroyInstancesByTag_19ff40`,
`EffDefGetDurationByHandle_1a0a50` (listings checked: `$5` = entry `$a1` at each jal). Fix: four
overrides under `overrides/src/main/effect/` passing the handle (a 4-byte union by value = one
stack word). New census `tools/bringup/protos_deficits.py` (PROTOS.tsv short calls, exit 1 while
one has no override): the 4 effect sites + RevelationBoardDrawSprite (override existed) covered;
2 open, both in the MSL iostream text writer, not on any tested path:
`NumPutDoubleThunk_1b2840` (1 of 5) <- `OstreamWriteFloat_1b25c0`, `OstreamWriteBool_1b2710` (4 of
5) <- `MotionEventEffectWriteText_1b1470`. The other `HandleTableGet_*` / `EffHdlRemove_*` manual
rows pass the handle as s32 (ABI-identical).

**Secondary: the RG_IOP=hle fault in `EffResGetNameMaybe_1a83d0` <- `EffDefCmdObjectMds_19c030`
(~18,640) is bug 2**, reachable in native mode too: replaying `out/ovlcov/ins_on2/boot_route.txt`
on the twin with RG_IOP=hle RG_AUDIO=hle faults on the old twin (orc2, eip rva 0x13326B, read
0xCA) and on the fixed twin with the four effect files swapped back (`out/hang/noeff_orc`), and
runs to 19,500 without a fault on the fixed twin. (Unlinked defs left stale entries the effect
script then read.)

**Paths tested (fixed exe).** Insectron return to title (`insectrun.py run --title`): TITLE (ovl 2,
3/201) at ~19,700 on the native-only exe, on the oracle twin, and on the twin under RG_IOP=hle
RG_AUDIO=hle (closed loop: battle ends 18,500 there; insectrun now keeps one battle-start state per
RG_IOP / RG_AUDIO / RG_THREADS set, a state only loads under its own init fingerprint). Opening-movie
skip (newgame route + START at 4,000 = "PAUSE / START Continue / TRIANGLE Skip", TRIANGLE at
4,100, `out/hang/mskip`): movie ends at once, story continues, field at 9,000 (the movie path closes
its stream through `MovieStreamClose_1d3660`, not the slot kick). Field system menu: System has
only Settings / Help (no quit to title in the field). Game over: not reached (save2 battle 2
without attacks: Jaster down at ~21,000, the Hooded Man fights on at 396/400 HP); it ends the
session through the same `GameSessionShutdown_1f5bf0`. No retail run needed: the kick semantics
are the EE kernel's (signal to a higher-priority waiter switches at once).

**Gates** (`out/hang/fix2/rg-game.exe` = build/hang-i686): regen.py --check 300 + verify.py 8/8
(save2 card backed up and restored), bootcheck --all 29/29, factory.py same verdict as before
(Run refused, exit to field ok), insectrun.py done (INSMENU at 19,000) and --title done (TITLE),
ingest.py --check 0 problems (242 overrides), ctest -j2 734/734 (7 skipped: real-data / GPU replay).

Files: new `overrides/src/main/sound/SoundRpcWorkerKick_1bd6a0.c`,
`overrides/src/main/effect/{EffDefDestroy_1a0a90,EffDefUnlinkByHandle_1a0040,
EffDefDestroyInstancesByTag_19ff40,EffDefGetDurationByHandle_1a0a50}.c`,
`tools/bringup/protos_deficits.py`; edited `tools/fixtures/insectrun.py` (state per mode set,
docstring), docs NATIVE-THREADS.md (driven threads table, files), TEST-FIXTURES.md, BRINGUP.md.

## 2026-10-25 (overlay coverage): FACTORY / INSMENU / INSECT played to an end, ON = OFF; golden routes native = oracle twin; trace_map over the module table

Follow-up of the D9 residue entry below (its open items: autobattle never reached the factory
/ Insectron overlays, no lockstep against the oracle twin, trace_map blind to overlays in a
native-only exe). Build dirs `build/ovlcov-i686` (RG_NATIVE_OVL ON, + rg-game-oracle) and
`build/ovlcov-off-i686` (OFF = arena manager in the native-only exe), one tree; exe snapshots
and runs in `out/ovlcov/` (game-derived, not committed).

**Coverage (new drivers, docs/TEST-FIXTURES.md "Factory and Insectron drivers").**
- `tools/fixtures/factory.py` on the new card `factory_plans` (save2 + Factory row + the 72
  "Obtained Factory Hint" story flags = all 33 production plans known + 5 of each material):
  Place x2 / Move + rotate / Remove on the floor, User's Manual pages, Blueprints -> 'Healing
  vial' -> Set -> the game's "parts layout template" (3 Source Tables, tubes, assembler,
  Completion Table), Set Material with a closed-loop source-table pick per material, Run, Go
  Back -> halt -> NORMAL -> field. Run is **refused** ("Is all the machinery connected to a
  power source?"): the template has no power cords; placing one is the open step, so no item
  is produced yet. (The library card ch05_factory is a NORMAL town area without random
  encounters: autobattle's "no battle in the box walk" there is the area, not a port bug; the
  FACTORY overlay is covered by factory.py instead.)
- `tools/fixtures/insectrun.py` on the new card `insectron_play`: Watch Battle CPU vs CPU
  played to its end (11,500 -> 16,100, 2P wins), rematch No, back to the INSMENU mode list.
  Finding: with the old `insectron` card only each team's leader is on the board and the
  battle **never ends** (48,500 fields watched; stats make no difference): the manufactured
  teams lacked per-insect formation fields. `saveedit.py --insect-formation` sets them
  (+0x18 / +0x21 = slot, +0x20 / +0x22 = 1; found by booting, not decoded); the old card is
  unchanged (bootcheck's insectron milestones only need the battle to start).
- `saveedit.py patch --add-item ID[:N]` implemented (the usage text had it, the code did not);
  team spec `@S` sets the six stats.

**ON vs OFF (RG_NATIVE_OVL)**: both drivers give the same result on both exes (same closed-loop
picks UP 5 / LEFT 6 / RIGHT 11, same phase ends, battle end 16,100; the generated boot routes
are byte-identical). Power-on replays of those routes (`routecmp.py pair`): factory run hash
d0b24a339fa07cf0 on both, 232 STATUS rows, 35 milestones and 231 sym: trace vbls identical;
insect af8a8594cd5865a5 on both, 378 / 39 / 377 identical; shots equal except the factory's Set
Material legend, which also differs between two runs of the same exe (a wall-clock animation).

**Golden routes, native-only rg-game vs oracle twin rg-game-oracle** (same tree; arena overlay
manager, VU0 library, hwbus and the IOP/sound oracles linked in the twin, every RG_* switch at
its default), `routecmp.py pair` with RG_TIMING, the sym: trace every 50 game VBlanks and
milestone shots:

| Route | run hash | STATUS rows | milestones (align) | sym: trace | shots |
| --- | --- | --- | --- | --- | --- |
| newgame_save2, power-on to 32,170 | bc05abfdcc9a0b65 both | 643 identical | 46, 0 segments differ (files identical) | 642 vbls identical | 1 of 8 equal; 7 differ by <= 4 LSB on character / model silhouette edges |
| boot_save2_battle2 (card save2) | a5ab6babd00d8311 both | 158 identical | 30 identical | 157 vbls identical | 1 of 5 equal; 4 differ by <= 3 LSB, same edges |

Classification: **identical game state and timing; presentation-only difference** (silhouette
edge pixels, deterministic: a rerun of each exe reproduces its own shots exactly). Not overlay
code (the arena and the module table hold the same bytes, below); it is in the renderer path of
the native-only clone vs the twin (renderer lane). Also seen: a traced run presents different
frames at a given field than an untraced run of the same exe (pacing), so shots are compared
only between runs of the same configuration. (rg-game's run hash folds pad reads, audio and the
kernel trace, not frames: `display_hash_every` is 0.)

**Module data = arena data.** `RG_STATUS_DUMP` of NORMAL's data+bss window (0x00524D00,
0x3500 bytes) at field 5,000 of the battle-2 route, native module vs the twin's arena: 3,376
words, 62 differ, all host pointers: 28 into each exe's image, 34 into the game heap with
delta exactly the difference of the two heap bases (0x05000200 vs 0x05740200).

**trace_map over the module table** (`src/trace/trace_map.c`, OVERLAY.md section 8 "Trace
address map"): the generator now keeps `text_size` in the native descriptors (a size; `load`
stays 0); an address in the active module's retail data window (arena base + 0x40 header +
text_size, + data + bss) maps to its segment, a host pointer into any module segment maps
back. `routecmp.py --ovl-regions BUILD` traces one `ovl:<name>` window per overlay: the
native exe records them only while that module is active (factory route: factory 124, normal
53, title 54 of 231 vbls), the arena exe always. Bug of the first version, found by the dump
above: the 0x40 MWo3 header was missing from the data start (windows 0x40 low); fixed, and
`overlay.native_trace_map` (+ control) pins it. Overlay-window hashes still differ between two
exes (the host pointers above), so they are a residency / mapping check, not a lockstep judge.

**Bugs / findings**
- **Hang (open, native IOP sound streams): Insectron "Return to title"** (FIXED: entry
  "2026-10-25 (stream close)" above). INSMENU -> Return to
  title -> Yes -> "We look forward to your next battle!" -> LoadingModeUpdate_285450 (game
  mode 3/100) at ~19,620 of the insect route; the main thread then spins forever in
  `SoundStreamSlotShutdown_1bdfd0` (pushes stop command 2, kicks `SoundRpcWorkerKick_1bd6a0`,
  waits for the stream slot to report state 0 / 7, which never comes) <- `SoundStreamSlotFree_1bd3a0`
  <- `StreamChanClose_1d6dc0`, after the loading mode's `StreamPauseChan` x3 /
  `StreamStopChan` x3. Same on the ON exe and on the oracle twin with default switches (not
  overlay code). Repro: `insectrun.py run --title --exe EXE` (or run_from.py --boot-save
  insectron_play with that run's boot_route.txt to 19,900); `hangsample.py PID` shows the loop.
  Owner: native audio / IOP lane. (With RG_IOP=hle RG_AUDIO=hle on the twin the battle runs at
  other timing, ends ~17,660, so the native-timed route does not line up; that run faulted in
  `EffResGetNameMaybe_1a83d0` <- `EffDefCmdObjectMds_19c030` at ~18,640 with presses landing
  mid-transition: noted, not pursued.)
- No bug found in the native overlay manager (src/native/ovl): every load / switch on the
  routes above (TITLE -> NORMAL -> FACTORY -> NORMAL; TITLE -> INSMENU -> INSECT -> INSMENU)
  behaves as with the arena manager, and no log has an `ovl:` report.

**Verification**: `ctest -L "overlay|trace|native_only"` on build/ovlcov-i686: 46 / 46 (the two
native_vu0 tests are not built in this dir); link audit of the ON exe `--forbid all --extra
rg_ps2_hwbus` PASS, the OFF exe FAILs `--forbid overlay` as it must; `addr_census.py --build
build/ovlcov-i686`: overlay / arena kinds 0, totals unchanged (arith 36, marker 44, inert 95).

Files: `tools/fixtures/factory.py`, `insectrun.py`, `routecmp.py`, `hangsample.py` (new);
`tools/fixtures/saveedit.py` (`--add-item`, `--insect-formation`, `@S`, recipes
`factory_plans`, `insectron_play`); `src/trace/trace_map.c`, `rg_trace.h`;
`tools/gen_overlay_registry.py` (native descriptors keep text_size);
`tests/overlay/ovl_native_tests.c` + `CMakeLists.txt` (`overlay.native_trace_map`); docs
OVERLAY.md section 8, TEST-FIXTURES.md.

## 2026-10-25 (checkpoint 11): interpolated presentation, opt-in

Renderer lane (docs/NATIVE-RENDER.md "Interpolated presentation", checkpoints 11a-c). Resumed a
stopped agent's work: `nr_interp.[ch]` + `nr_iprec.cpp` (the frame retained as the device's
command list, replayed with interpolated mesh constants), wired in `nr_scene.c`, `nr_gs.c`,
`nr_hw.c`, the runtime and the setting `display.interpolation` (bool, default off, Original off;
with `display.pacing = host` and `display.frame_rate` 120 / 144 / uncapped). Fixed: substituted
constant rows overwrote the depth format's largest Z (every interpolated depth-tested mesh
vanished); a camera pan read as a cut (object jumps now measured in world space over view depth,
cuts by view turn); added 2D / effect / generated-primitive interpolation (immediate draws paired
by frame-stable state keys and order, triangles lerped); trimmed the replay of later frames
(bit-identical, 3.7 -> 2.2 ms per pass in battle2). Headless at a simulated 144 Hz: a pan moves
8-10 px every present instead of 40 px every fifth, no pops, exact-replay checks all same; run
hash and shots unchanged with interpolation on or off. Gates (snapshot `out/interp/g11`): ctest
732/732, regen + verify 8/8 (save2 card restored), bootcheck 29/29, mapcheck 5/5,
render_gate c11 all PASS. Tools: `interp_run.sh`, `interp_smooth.py --crop`,
`interp_census.py`, `interp_walk.input.txt`, `render_fx.sh` `RG_FX_SCRIPT`. Open: Z-scale
composites exact (13-24 % of mesh items), one game frame of display delay, no play-test on a
real high-refresh display, no headless battle-effects window.

## 2026-10-25 (D9 residue): no emulation library left in the native-only exe

`rg_sce_vu0`, `rg_ps2_overlay`, `rg_ps2_overlay_bind`, `rg_ovl_arena` (and `rg_ovl_data`, the
RG_OVL_DATA backing the arena binding pulled in) are out of the native-only rg-game.
`link_audit.py check build/nd9-i686/rg-game.map --forbid all --extra rg_ps2_hwbus`: **PASS, 0
pending emulation libraries** (the same-tree twin rg-game-oracle FAILs on all five, as it must).
Exe 9,093,632 bytes (oracle twin 10,419,200; checkpoint-10 native-only 9,172,992).

- **VU0** (NATIVE-CPU.md section 9): `rg_native_vu0` = `src/native/vu0/libvu0_native.c` (the 17
  sceVu0* functions as plain C on float lanes) + `vu0_srt.c` / `vu0_ctx.c` (moved from
  src/sce/vu0). Bit-identical to libvu0.c in the same RG_VU0_MODE: `ctest -R native_vu0`
  420,000 word comparisons (random + edge words, every aliasing form), 0 mismatches.
  `RG_NONLY_REPLACE rg_sce_vu0=rg_native_vu0`; link-audit set `vu0lib`.
- **Overlays** (OVERLAY.md section 8): the native module table `src/native/ovl` (`rg_native_ovl`
  + generated `rg_ovl_native_game`): per-overlay data segment `<ov>_seg` with its labels, load =
  restore .data / zero .bss / activate / ctors; imports dispatch by a build-time table (import x
  module), no retail address anywhere (no arena, no address map). CMake option `RG_NATIVE_OVL`
  (native-only builds), default ON after the gates below. `ovl.h` moved to src/native/ovl (one
  interface, two managers); the shared lifted ctors and .data images spell addresses as
  `label + offset` / `data2c_main_bss + offset`. Link-audit set `overlay`.
- **MAIN data -> overlay data** (datareloc, re-ingested game/ once, 7 files changed): the 98
  `arena-data` words are `<ov>_D_x + off` (was `data2c_overlay_load_base + off`); 7 words in
  the NORMAL/INSECT overlap attributed by `ARENA_DATA_OWNER` (checked against the listings);
  D_004461F4 (retail `_end`, dead: sbrk is bound natively) = 0. The re-ingest also carried the
  soak lane's `factory_sub_004EC7F0` datareloc fix (D_00468380) already in tools/.
- Gate test `native_only.link_audit` forbids `...,vu0lib` and (RG_NATIVE_OVL) `overlay`.
- Census: `tools/native/addr_census.py --build <dir>` (new): PS2 address arithmetic left in the
  compiled set. Overlay / arena kinds: **0**. Left (renderer / dead-data lanes): HW accessors
  10 (GS privileged + VIF1, routed natively by port/hwaccess.h), data-hw 18 (dead SDK
  DMA-channel tables), lit-spr 5 (DMAtag END ids, not addresses), lit-hw 1
  (KernelReleaseAlarm INTC poll), ps2-addr-def 2 (SysCalcFreeHeapMaybe_15e1d0's retail heap
  arithmetic); markers 44 (PS2_PHYS/UNCACHED/UCAB, KSEG masks: identities), inert raw data
  words 95.

Verification, build/nd9-i686 (RG_NATIVE_ONLY + RG_NATIVE_OVL, RG_VU0_MODE=native):
ctest -j2 -LE fixtures 725 + -j1 -L fixtures 7: **732 / 732** (after one fix in the new
test's control: a NULL deref instead of a check failure); regen.py --check 300 + verify.py
**8 / 8** (set f20500df0389397e; out/fixtures/cards/save2 restored afterwards); bootcheck
--all **29 / 29 PASS** (factory: FACTORY at 4400 / NORMAL at 6400; insectron: INSMENU 2300,
INSECT 10300, insect battle 15/101 at 11500); mapcheck **5 / 5 DRAWN**; autobattle ch07_rosa
**won** (2,538 fields, no crash). Autobattle on ch05_factory: prep finds no battle in the box
walk ("no battle in the box walk"; bootcheck's optional encounter is `never` for that card), and
the INSECT battle is not an autobattle target, so the factory / insectron overlays are covered
by bootcheck's milestones. Not run: the golden-route lockstep vs the oracle twin.
Then `RG_NATIVE_OVL` default ON (existing build dirs pick it up at the next configure).

## 2026-10-25 (soak): long soak over every card; FACTORY Place crash fixed; Insectron reward lookup; SysMsgPost byte

Lane "soak" (P5 gate: find what a playthrough would hit). New tool `tools/fixtures/soak.py`
(docs/TEST-FIXTURES.md "Long soak"): one session per card (25 library cards + save2 + factory +
insectron) chained from save states: world-heading exploration with a visited-cell novelty
score, main-menu passes (seeded random walk through Items / Equip / Revelation / Allies /
Strategy / Recorder / Frog Log / Factory / System), a transporter save + reload check (save2,
alistia), every random battle fought by `autobattle.fight`; per segment crash / hang / no
progress / unknown log line / UBSan / stack-guard / game-heap (dlmalloc walk of the state)
checks; findings keep their start state, input, power-on route and triage shots. Builds:
`build/soak-i686` (-O2 native-only, 23:26) and `build/soak-ubsan-i686` (RG_UBSAN=ON); test exes
with the fixed TU(s) by `altlink.py`: `out/soak/alt` (-O2), `out/soak/alt-ubsan`,
`out/soak/alt-guard` (= `build/sblock2g-i686`, the 20:44 stack-guard exe), `out/soak/alt2`
(-O2 + both fixes below). Results `out/soak/{o2,ubsan,guard}` (`soak.py report DIR`;
`out/soak/o2_report.md`, `ubsan_report.md`).

| Pass | Exe | Fields | Battles (won / lost) | Findings |
| --- | --- | --- | --- | --- |
| -O2 native-only | soak-i686 (first 10 cards), then `out/soak/alt` | 346,235 (28 cards, 10.6k-15.9k each) | 28 (17 / 6) | 1 crash (fixed), 1 long event, 5 Factory exits (tool), 1 autobattle (tool) |
| UBSan | `out/soak/alt-ubsan` | 175,964 (28 cards, ~6k each) | 18 (3 / 1; the rest stopped by autobattle limits) | 179 UBSan sites (91 on the route census, 88 new: triaged below), 9 autobattle (tool) |
| stack guard | `out/soak/alt-guard` (7,385 guarded locals) | 134,554 (28 cards, ~4k each) | 12 | **0 overruns**; 1 battle-segment timeout that did not reproduce (replayed 650 fields from its state cleanly; autobattle now retries a timed-out segment once), 2 cutscene `stuck` rows (this 20:44 exe cannot shoot after a load: no frame hash), 5 autobattle (tool) |

**Found and fixed:**
- **FACTORY → Place crashes the game (crash, every build since the factory is reachable).**
  Repro: card ch06_mines, main menu row "Factory" ("Linking to the factory via remote
  control"), Place: access violation at eip=1 (soak.py finding o2/002; power-on input
  `out/soak/o2/findings/002/poweron.input.txt`). Cause: the UI draw-callback table
  `D_00468380` (id -> callback) holds id 0x1A = the FACTORY function at 0x004EC7F0 as a raw word;
  the C port names it `factory_sub_004EC7F0` (inside factory_FactoryRelated_4ec7e0.cpp, no
  glabel), and datareloc only took `<ov>_FUN_ / _func_` spellings, so the word stayed a number:
  `UiDrawWidgets_291910` called host address 0x004EC7F0 (a MAIN function's interior, different
  per link: `GameRecFindFreeInsectSlot+0x1f0` here, `CharaGetStatA8_3b0340` in the guard exe),
  which popped one argument too many and "returned" to the pushed literal 1. Found with the
  soak's crash replay + `RG_WATCH` on the smashed stack slot + `RG_BREAK` at the call
  (`out/soak/o2/findings/002/rep*`, `out/soak/wdump.py` widget-list dump). **Stage rule**:
  datareloc's overlay-entry regex takes `_sub_` too (`tools/stages/datareloc.py`); scratch ingest
  changes exactly `src/main_data/data2c_00468380.c` (`arena-text-interior` -> `arena-fn`); census
  of the other 43 `arena-text-interior` words and of raw MAIN-text words in pointer tables: no
  other function. Verified on the altlink exe: the same power-on input opens and closes Place.
  Landed in game/ by the D9-residue lane's 01:21 re-ingest (it carried the rule; a scratch
  ingest at 03:00 equals game/), so this lane did not re-ingest.
  **The play-test exe `out/playtest/rg-game-1024a.exe` (built before this) has the crash.**
- **`SysMsgPostMaybe_1c3560` turned a message byte into `v & 1`** (UBSan `invalid_value`, insectron
  card): the decomp views byte 4 of the posted message block as `bool` (`o4`) as well as `b4` /
  `h4`; clang copies a bool as `andb $1` + store, retail as `lbu`/`sb`. Override
  `overrides/src/main/sys/SysMsgPostMaybe_1c3560.cpp` (`u8`). Only union-view `bool` member in
  the corpus; the only `invalid_value` site of the soak.
- **Insectron reward lookup** (BRINGUP open item `InsectronRewardLookupMaybe_3e84f0`, PROTOS.md
  abi2 "1 BUG-pass"): retail tail-calls slot 0x70 of `(Game+8)->+0xA0->+0xC`, forwarding $a1 (the
  team key) and returning the record; the port's definition was `void (p)` and the caller
  `InsectBattleMatchUpdateMaybe_319800` read `(F(g), (s16 *)0)`, so a story Insectron rank reward
  (StateVar 0x73/0x74 + `InvAddItemRepeat`) was never granted. Overrides
  `overrides/src/main/map/InsectronRewardLookupMaybe_3e84f0.cpp` (`void *(p, key)`, VCALL slot
  0x70) and `overrides/src/main/sys/InsectBattleMatchUpdateMaybe_319800.c` (passes
  `*(s16 *)(e + 0x5EFC)`, reads the record). Run-time check (insectron card, INSECT battle at
  11,500): the object's vtable is `D_00479180`, slot 0x70 = `DataTableFindByKey_3680a0(this, key,
  ..)` (the keyed lookup `TableFindFloorByKey_40b230` also uses). The story tournament itself is
  not reachable from a card yet, so the reward path is verified by construction only.
- **Tooling found on the way:** the UBSan census runtime crashed after `--load-state` (its static
  `FILE *` is captured by the state; now reopened per process, `src/game/ubsan_census.c`; same guard
  in `src/game/sbguard_census.c`); `autobattle.fight` now returns its end state and presses CROSS
  through in-battle prompts (7/2100).

**Triaged, not port bugs (tool / game / known class):** ch02_dorgenark 11/0 for 8,000 fields = the
Ch2 intro cutscene advancing line by line (long event); the FACTORY is left by Go Back + "Halt
factory operations?" (the menu pass now does that); autobattle leader-switch / heal loops in the
battle menu (documented limitation); UBSan: 29 misaligned + 27 bounds rows of the census's benign
classes (extern data declared shorter than the contiguous image: MenuMainResLoad `D_00482400[2]`,
title `D_00480418[4]`, struct views shorter than the data), `insect_InsectBattleFlowTurnStart_508b30`
`[-1]` (a piece not on the board: retail reads the same byte), `EffSpriteListDraw_2dcab0` reading
uninitialised entry floats (`EffSpriteListAlloc` sets only id / group / tex; MemStack leftovers,
same in retail), and 31 float_cast rows of inf / NaN (projection / billboard / UnitBaseUpdate /
WrapAngle): the EE has no inf / NaN, so these are the EE-float residue (open exact-model item, EE
floats lane); the casts saturate (`-fno-strict-float-cast-overflow`). Game heap: every walk clean
(chunk chain to top, footers, no adjacent free chunks); in-use bytes flat per card except small
battle-time growth (ch10_kuje +1.3 KB / 27 chunks, ch06_vedan UBSan +2.4 KB) that does not climb.

**Checks** (exe `out/soak/gate/rg-game.exe` = `build/soak-i686` rebuilt 03:11 from the current tree:
the 01:21 re-ingest, RG_NATIVE_OVL ON, the three overrides; script `out/soak/gates.sh`): `regen.py
--check 300` + `verify.py` **8/8** (run hash and frame; the save2 card it wrote differed and was
restored from the backup); `bootcheck.py --all` **29/29 PASS**; the FACTORY Place power-on repro
exits 0 (no exception); ctest -j2 -LE fixtures **725/725** (8 skipped: realdata, game_replay,
readback_lag, link_audit_control) + -j1 -L fixtures **7/7**; `ingest.py --check` 0 problems (238
overrides). Not run: mapcheck (no renderer change), retail comparison of the soak areas. Not
play-tested.

## 2026-10-25: play-test build 1024a; widescreen re-shoot on the native device

**Build.** `build/play-i686` (Release, ninja -j4), full recompile 23:37-23:58 on 10-24 (23,308
steps, 21 warnings, `out/regress1024a/build.log`) from the tree with: EE floats (PS2 rounding +
retail libm), widescreen stage 3 + gaps, item 8 fix, stack-block re-ingest (22:15), renderer
checkpoint 10 (native-only exe links neither `rg_gpu` nor `rg_ps2_gs`), the parity2 data overrides
(`overrides/src/main_data`, 22:45) and the 23:09 Insectron overrides. Snapshot
`out/regress1024a/rg-game.exe` (+ .map) = `out/playtest/rg-game-1024a.exe`; play.bat /
play-from-save.bat / play-test-save.bat launch it. `make_allcard.py` refreshed `saves-all`
(cards re-made since 10-23; now 30 files: zshop / zshop2 added as FILE 29 / 30; old card kept in
`out/regress1024a/saves-all.1023`). `saves-save2` left as it was (may hold play-test saves).

**Gates** (logs `out/regress1024a`, script `gates.sh`): `regen.py --check 300` OK (fixture set
regenerated for this exe; shared save2 card identical after regen) + `verify.py` 8/8 (run hash and
frame after load); `bootcheck.py --all` 29/29 PASS; `mapcheck.py` 5/5 DRAWN; ctest -j2 722/722
(8 skipped: 2 realdata, runtime.cdvd_realdata, 3 game_replay, readback_lag, link_audit_control);
`link_audit.py check rg-game.map --forbid iop,kernel,vu0,render-dma,render-vu,render` PASS (pending
still linked: rg_ovl_arena, rg_ps2_overlay, rg_ps2_overlay_bind, rg_sce_vu0). Windowed smoke
(`out/regress1024a/smoke`, double-click style: no --data / --saves, `--fields 1600` + shots):
D3D11 native device on the RTX 3080, data from the junction beside the exe, 3x from the
settings.ini beside it, title menu at 1500, rc 0.

**Widescreen re-shoot** (`tools/wide/stage3shots.py --aspects 4:3,16:9,21:9,32:9 --log`, 15
scenarios, `out/regress1024a/wide`) vs `out/wide4/f_new` (exe `out/wide4/r1`, the gaps lane's):
`idcheck.py` every one of 60 run hashes SAME (equal across aspects too, one aspect change per run
after the title). No shot is pixel-identical, but the differences are tiny: new
`tools/wide/oldnewsheet.py` (OLD | NEW contact sheets per aspect + `edges.tsv`: diff %, near-black
share of the side regions) and `out/regress1024a/diffmag.py` (`diffmag.txt`): max 1-5 levels on
3D / field / battle pixels (float rounding), 0 changed pixels in the side regions of every
full-screen menu (Allies, Strategy, Recorder, Frog Log, System, Items / context / target,
transporter, save, shop, Revelation list) at 16:9 / 21:9 / 32:9, side near-black share equal in
every shot. The only larger change is the Revelation board's flashing slot (53x49 px inside the 4:3
screen, up to 33 levels; revboard / revstones at all aspects) = the parity2 packed-word fix. So the
renderer lane's "the stage-3 exe left parts of the strips black, the native device draws them
whole" is relative to `out/wide3/s3final` (before the gaps pass); against r1 (gaps) the strips are
unchanged, i.e. the native device draws them as the twin path did after the gaps fix. Visual check
of the sheets (`out/regress1024a/widecmp/sheet_{4x3,16x9,21x9,32x9}_N.png`,
`row_map_items.png`): no screen looks wrong; at 32:9 the strips beyond the 30 % mirror cap are
stretched (streaks on the parchment of Items / Revelation / save / shop), as designed.

## 2026-10-24 (night, parity2): Revelation flashing slot = packed numbers relocated as pointers; parity sweep on the EE-float default

Lane "parity2" (build dir `build/parity2-i686`, exe snapshot `out/parity2/exe1`, scratch
`out/parity2/`). Changes: `overrides/src/main_data` (17 files, 7 new), tools. No game/ re-ingest,
no stage change.

**(A) Revelation board flashing slot differs between links (found by the widescreen lane).**
- Not an uninitialised read and not the renderer. Proof chain (instrumented altlink exes,
  `out/parity2/rev/`): the same objects linked with a neutral padding object or `rg_layout.obj`
  first (new `altlink.py --first OBJ`) reproduce it (slot interior (39,37,40) / (41,37,37) /
  (44,51,57) by layout); RevelationBoardUpdate / 34c170 / 34ce10 arguments and lerp outputs are
  identical in every layout; WARP, the GS draw path (`RG_GPU_NO_NATIVE=1`) and the lazy-transfer
  controls keep the layout dependence, so the GS input itself differs; a GS local-memory dump
  (`RG_GS_DUMP_*`) differs only in the frame buffer at the slot; logging every XYZ2 in the slot
  box (`GsPktSetXYZPixel_13f110`) shows sprite 12's closing **UV** differs.
- Cause: `RevelationBoardDrawSprite_34c170` reads the sprite table D_004539F0 (s16 x, y, w, h);
  entry 12's w/h word 0x00400040 (= 64, 64) was emitted by data2c as
  `(u32)&DataTableCompareThunk_400040` (a MAIN function at 0x400040), so on the host it holds a
  host code address and the UV changes with every link. (Its neighbour 0x004C008A was the
  10-13 `main-bss` fix.) Retail (PCSX2, new `cardboot.py --plan revel`, shots
  `out/parity2/retail_revel`): blue-grey slot interior (43,50,57); the fixed port (45,53,60).
- **Class census** `tools/parity/pairptr_census.py` (new): pointer words in the data layer
  whose retail value is a packed pair (low half a small s16, neighbours packed pairs, sparse
  pointers, unaligned target); reads overrides first. 22 words in 16 objects checked by hand
  against their retail neighbours, all packed numbers: coordinate / rect tables (D_00451060,
  D_00462790, D_004627C0, D_00468D70, D_0044E680), (index, offset) tables (D_00453810,
  D_00450CC0, D_00453930, D_00462BA0, D_00464140), D_00450870 and its three copies, an ASCII
  group table (D_004544F0), packed GS words (D_00446648), and 0x00453A54. The census's other
  high scorers are real pointer tables (string pointers at an 8-byte stride, D_0044EA00 /
  D_0044EB20; (ptr, packed) pairs D_0044C750).
- **Fix** `tools/parity/datafix_packed.py` (new, idempotent; the verified list with its
  evidence is in the script): retail's number in each word, in `overrides/src/main_data`
  (existing 10-13 overrides edited, header hash kept; 7 new ones). `ingest.py --check`:
  234 overrides, 0 problems. Stage-rule alternative for the stack-block lane (not done here):
  a `packed-word` row in tools/stages/datareloc.py for these addresses (and the 10-13
  `main-bss` rows), then retire the overrides.
- **Determinism:** three links of the same objects (plain, padding object first, rg_layout first;
  `out/parity2/fix/x1..x3`) give byte-identical shots and run hashes at 4250 / 4300 / 4500 /
  4700 / 5050 (board, stone list, slot filled, ability list); `build/parity2-i686` (current tree,
  a fourth link) gives the same pixels.

**(B) Parity sweep on the default build (EE floats chop + retail libm, current tree incl. the
22:15 re-ingest).** `sweep.py --exe out/parity2/exe1/rg-game.exe --out out/parity2/sw`, retail
rerun for every scenario (the cards were rebuilt 10-24). New `tools/parity/divclass.py OUT`
classifies first divergences (ulp / float / int / rng / timing).

| scenario | identical fields (10-19 chop sw1) | rng first differs (sw1) | first int divergence | class |
| --- | --- | --- | --- | --- |
| walk_save2 | 239/257 (111) | never (353) | 627 c0.m3d8 | floats only; collision flag flips after 600 frames of ulp drift |
| walk_ch01_salgin | 239/257 (239) | 610 (610) | - | ulp drift -> rng |
| walk_ch02_juraika | 234/257 (234) | never | 524 c2.m3d8 | ulp drift |
| walk_ch03_burkaqua | 224/257 (207) | 13 (0) | 306 (after rng) | **load timing**: rngtrace: DynClothDefInit_169420 draws 4 Rand at frames 13 / 18 on the port, 23 / 28 on retail (same pattern, 10 frames later) |
| walk_ch04_prison | 235/257 (235) | never | - | ulp only |
| walk_ch05_factory | 234/257 (234) | 569 (569) | - | ulp drift -> rng |
| walk_ch06_mines | 114/257 (110) | 515 (410) | 289 c2.m3d8 | spawn y ulps, position drift from frame 264 -> collision flag |
| walk_ch06_vedan | 235/257 (235) | never | - | ulp only |
| walk_ch07_rosa | 174/257 (174) | 689 (689) | 682 c0.a34 | spawn ulps, drift |
| walk_ch10_kuje | 234/257 (207) | never (611) | 597 c1.m3d8 | ulp drift |
| battle2 | 140/257 (126) | 0 (0) | 0 | anchored ~1,600 frames after a card boot: state already apart at the anchor (as 10-19) |

Classes left (no ABI / logic divergence found): (1) EE float residue: spawn heights 1-2 ulps
at frame 0, motion phase 0.0274999961 vs 0.027499998 (division: PCSX2 rounds DIV.S to nearest,
the port chops) and yaw ulps (adder dropped bits, libm 1 ulp); they grow into collision-flag
(m3d8) flips and rng after 290-690 frames: needs the opt-in exact model (`RG_EE_FPU_EXACT`,
open). (2) Load timing: object / cloth init frames earlier on the port (burkaqua), retail long
frames at frame 41 (`frametime`). (3) battle2 compares a state that diverged before its anchor.

**Checks** (exe `out/parity2/exe1` = build/parity2-i686, current tree after the 22:15 re-ingest and
the renderer lane's runtime.c fix): `regen.py --check 300` + `verify.py` **8/8** (new set; the save2
card it wrote is byte-identical to the shared one); `bootcheck.py --all` **29/29 PASS**; ctest -j2
-L "port|protos|devirt|overlay|host|native_only" **72/72** (1 skipped: link_audit_control);
`ingest.py --check` 0 problems (234 overrides). Not run: full ctest, mapcheck. Not play-tested.

## 2026-10-24 (night): renderer plan steps 2-4: no GS model, no GS renderer in the native-only exe

BRINGUP.md item 2; docs/NATIVE-RENDER.md "Checkpoint 10" / "Verification (10)".  Build
`build/nrender2-i686`; exes `out/nrender2/bin/c10d` (final), `out/nrender2/bin/oracle` (twin),
`out/nrender2/base` (before: build/lowres-i686 of 18:31).

**Result.** `tools/native/link_audit.py check --forbid iop,kernel,vu0,render-dma,render-vu,render`
**PASSES**: the native-only rg-game links neither `rg_gpu` nor `rg_ps2_gs` (exe 10,058,240 -> 9,172,992
bytes at the time; the `native_only.link_audit` ctest now forbids `render` wherever the D3D11 device is
built; headless Linux keeps the software GS model).  What replaced them, all in `rg_native_render` and
RG_NATIVE_ONLY code only (the twin and default builds compile the old paths):
* a native GS state block (`nr_gs.h`: register words, CLUT cells, privileged registers, transfer
  progress), the GIF input (`nr_gs.c`: streaming per-path parse into immediate records + IMAGE data,
  arbitration at packet boundaries, SIGNAL / FINISH / LABEL raised on the EE thread), the worker
  (`nr_q.c`), the privileged registers (`nr_hw.c`), GS address arithmetic (`nr_gsmem.c`);
* local memory on the GPU only: transfers batched and swizzled by `CS_xfer`, copies `CS_l2l_*`, CLUT
  loads from kept palette words (CPU) or `CS_clut`, the lens-flare probe the one read-back, save states
  through the runtime blob;
* the device: `nr_dev.cpp` (forked from gpu_core.cpp with the new `tools/native/srcfuncs.py`),
  `nr_d3d11.cpp` (moved from src/gpu/gpu_d3d11.cpp; rg_gpu compiles it with RG_GPU_EXACT=1),
  `nr_gfx.c`; the twin's GS-draw-path fallbacks of immediates drawn natively (counted).

**Open items closed.** ch09 glow: not the feedback margin but a C = As blend whose texture is a frame
copy with alpha 0xFF (the GS doubles, the dual-source factor saturates): such immediates go through
the ordered colour view (23.92 dB FAIL -> 35.29 PASS); found with new twin knobs
`RG_NR_IM_EMU_FBP` / `RG_NR_IM_EMU_ALPHA`.  Composite draw-back at x3 natively: upscaled-texel taps
are the default now (`RG_NR_NATTAP=1` = old): x3 route 0 failing, save2 close-up x3 38.2 dB.

**Bug found on the way (fixed 22:45).** Save states of native-only exes from about 20:00 to 22:45 lost
the display after `--load-state` (PMODE in the state block, which runtime.c had allocated in host
memory): verify.py frame checks failed; now the state block and the local-memory image are part of the
runtime's save-state blob.  States written by those exes are refused (blob size): regenerate.

**Checks** (exe c10d unless noted): render_gate x1 (c10b, same render code): route 24 fields PSNR min
31.31, 0 failing, run hashes equal; 8 boot fixtures PASS (save2 34.35, factory 34.39, insectron 38.29,
save2_battle2 37.81, ch06 36.19, ch09 35.29, ch12 45.22, ch13 39.52 dB); mapcheck 5/5; x3 route PASS
with the NATTAP default; 16:9 route PASS; widescreen stage 3 shots (15 scenarios, 16:9) vs
`out/wide3/s3final`: run hashes equal, differences only where the stage-3 exe left parts of the
mirrored edge strips black; item 8 repro (ch07_rosa x3) base vs native 201 px; `regen.py --check 300`
+ `verify.py` 8/8 (frames and run hashes after load); `bootcheck.py --all` 29/29 PASS; `mapcheck.py` 5/5
DRAWN; ctest -j2 722/722 (7 skipped: realdata, game_replay, readback_lag); link audit PASS.

**Performance** (headless, RG_FIELD_TIMES wall): boot:save2 to 4,050 back to back on the shared PC:
2.31 ms/field native-only vs 2.88 before (fields 2,000-4,050 0.6-4.4 ms faster per field, the title
0-2,000 0.3-0.4 ms slower: open); route x1 5.82 ms/field (twin emu 29.20), x3 7.15.

**Next:** interpolated presentation (no longer blocked by the GS model); the title / menu ms; the
6,672 native target reads through the mirror (format-changing views) from item 8.

## 2026-10-24 (sblock2): stack-block census closed; function-pointer resolver in the protos stage; RE-INGESTED

Lane "sblock2" (BRINGUP.md open item "Stack-block census"; details docs/PROTOS.md
"Stack-block: function-pointer resolution in the stage"). **game/ re-ingested once, 22:15:
other lanes' next build recompiles everything** (game_protos.h also picked up the EE-floats
lane's `rg_ee_*` provider prototypes from src/crt/crt.h, waiting since its last ingest);
stage-level source changes are 7 files only. No override went stale.

- **Resolver in the stage** (`tools/stages/sbresolve.py`, used by protos `_stack_blocks` and
  by `tools/census/stackblock_census.py`; `RG_PROTOS_NO_SBRESOLVE=1` disables): own-local
  vtables (ctor chains, delay slots), `dsym` / `dtbl` function tables, foreign vtables with
  the `this` offset corrected, stored callbacks, reviewed receivers / sources / bounds, the
  port's member-call arity (`_vcall_pairs` + `vcall-forward` lanes), port-only split entries,
  `fentries` interiors. asmflow: `%gp_rel` tables, object fields keyed by offset whatever
  register holds the base, arg-field vptrs, zero-register branch pruning. clayout /
  `_type_size`: array dims with literal arithmetic. Stage time +~10 s; deterministic
  (PYTHONHASHSEED 1 = 2). Fixture `FnTblBlock_401800` + `data2c_00480040.c` (`protos.stage`).
- **Census** (`census/stackblock_sites.tsv`): 103 needs-human -> **0** (97 -> OK, 1 -> complete
  inside its local, 2 size-unknown -> OK, 3 override -> OK; transitions in
  `out/sblock2/compare9.txt`); 965 rows = 595 OK, 366 OK-block, 4 `override: BUG` (unchanged
  overrides). info-stack-block-unresolved 559 -> 87, all with census verdicts.
- **Real bugs found, fixed by rule** (6 new blocks; each hidden by an unsizable struct):
  CharaSysEncounterSetupMaybe_3a4440 `desc` (CharaStateReset_3a79b0 writes 6 bytes past the
  0x1C8-byte Desc4440 -- **confirmed at run time**: a guard control on that local in the guard
  exe logged `post overrun bytes [456, 461]` on the ch01_salgin random encounter); the
  model-desc class (InfoCfgParseAll_1afd00 reads 8 bytes past the 0x88 record) in
  EventCastCreateObj_24b8c0, MapObjLoadStep_1e0850, MenuItemModelCreate_2a7190,
  MenuModelCreate_294330, factory_FactoryCursorModelLoad_504250. Removed: the two
  ParamScriptMotionEventCmd_1af180 "padded" blocks (an artefact: `s32 sp[0x30 / 4]` was sized 4).
- **Padded blocks** (`tools/census/sbpadcheck.py`): ParticleEmitterSpawn `rot`, InsectApplyItem
  `rec`, MenuItemUseTargetState `v80`: pads correct (the retail slot past each is a different
  local, not live across the call / starting past the callee's write end).
- **Guard census rerun** (`RG_PROTOS_SB_GUARD=1` tree `out/sblock2/gguard`, 7,385 guarded
  locals; `build/sblock2g-i686` with `RG_SBGUARD=ON`): golden route power-on -> 31,800 and
  `bootcheck.py --all` 29/29 PASS, **0 overruns** (10-19: 3 sites). Arming proven by the
  CharaSysEncounterSetup control above.
- Test before landing: `altlink.py` exe with the 7 changed TUs (`out/sblock2/alt`):
  bootcheck --all 29/29 PASS.
- New tools: `tools/census/sbpadcheck.py`, `tools/census/sblisting.py`,
  `stackblock_census.py --compare` (verdict transitions), `REVIEWED_SITES` /
  `REVIEWED_TYPE_SIZES` in the census.
- Checks after landing (build/sblock2-i686 from the current tree): bootcheck.py --all 29/29 PASS;
  mapcheck.py 5/5 DRAWN; ctest -j2 722/722 (8 skipped); regen.py --check 300 all 8 milestones +
  verify.py run_hash 8/8 OK, but every verify **frame** check reads `None`: a `--shot` after
  `--load-state` is never taken by an exe built from the current src/ -- also with my 7 TUs
  reverted (altlink `out/sblock2/revert`), while out/wide4/r1 (src of 20:07) shoots; src files
  changed since are src/native/render (nr_gs/nr_im/nr_q) and src/settings/rg_layout (other
  lanes). Not this lane's change; flagged for the renderer / widescreen owners.
- Left: the 4 `override: BUG` rows stay the PtalkFindPairRow / FactoryStep overrides'; overlay
  vtables are not in the tree (an overlay receiver keeps a site open); scanned candidate sets
  ("every vtable stored at +V") miss a class whose vptr store the scan does not see, hence the
  reviewed receivers.

## 2026-10-24 (late): widescreen stage 3 gaps closed

Second pass over stage 3 (docs/WIDESCREEN.md "Stage 3 gaps"; build tree `build/wide4-i686`,
scratch and shots `out/wide4/`). Lane: `src/settings`, `tools/wide`, host tests.

- **Screens:** `tools/wide/stage3shots.py` gained the area map (SELECT), Allies (+ member
  commands), Strategy, Battle Recorder / Frog Log / System, the Revelation board / stone list
  / ability list, the battle command menu and its Items grid, the Dorgenark bridge, its main
  menu and the Galaxy Map (planet select at the helm), and the aspect 32:9 (auto on a
  3840x1080 display); the battle2 shots were retimed (results 7300, map help 7550, field
  7690). 16 scenarios x 4:3 / 16:9 / 21:9 / 32:9.
- **Found:** the main-menu sub-screens with a tiled backdrop (Allies, Strategy, Recorder,
  Frog Log, Revelation list) showed black at the left and upper right at 21:9 / 32:9 (the
  strip rule "lowest layer per drawing function" kept only the first tile's strips); the
  Revelation board showed off-screen cells and the cursor box in the side (its 1396-sprite
  cell packet counted as one background); at 32:9 the main menu's mirrored strip reached
  the portrait-circle cut-out (black half disc); the main menu's backdrop packet is a
  translucent black shadow sprite then the art (the first pass mirrored the art only by
  using the packet's last colour).
- **Fixed** (`src/settings/rg_layout.c`): strip coverage per screen rows and seam; topmost
  sprite per packet; per-sprite background test (an eighth of the screen each way); strips
  faded toward the canvas edge in up to 16 RGBAQ bands (75 %, `RG_LAYOUT_STRIP_FADE`,
  `RG_LAYOUT_STRIPS=smear`), packet colour restored; mirrored span capped at 30 % of the
  art; dedicated menu tasks laid out as the menu from their first packet (first-frame
  layout); `RG_LAYOUT_H` guard / constant clash -> `RG_LAYOUT_FRAME_H`.
- **Census** (`tools/wide/menucensus.py`): no menu with a non-indexed full-screen background
  among the screens reached; per-element screens are overlays over the live 3D (battle HUD
  and command menu, factory floor, INSMENU attract).
- **Renderer lane mid-change:** the shared tree rendered black / blue frames during this
  pass (src/native/render edits 19:25-20:11), so the shots and fixture gates ran on
  `out/wide4/r1/rg-game.exe` = `build/wide3-i686`'s objects relinked with this pass's
  `rg_layout.c` (new `tools/wide/relink.py`), baseline `out/wide3/s3final` (same objects).
- **Checks:** run hashes identical across the 4 aspects in all 16 scenarios; one aspect
  change per run (the title); Original / 4:3 vs baseline: all 19 run hashes identical, 76/86
  and 18/20 shots pixel-identical (the rest: two documented nondeterministic spots, a 1-level
  difference between two baseline runs, and the Revelation board's flashing slot, which
  differs between any two exes built from the same objects: an uninitialised read in the
  board's slot colour path, not the layout); fixture gates on r1: regen --check 300 + verify 8/8, bootcheck --all 29/29, mapcheck 5/5 (regen's save2 card differed from the shared one in 216 header bytes, so the shared `out/fixtures/cards/save2` was restored from a backup); `tools/ingest.py --check` 224 overrides, 0 problems; `build/wide4-i686`: all targets and rg-game build without the old `RG_LAYOUT_H` warning, ctest -L "wide|settings|host" 52/52 (this configuration has no render label), full ctest 630/630 (5 skipped: 3 realdata, gpu_smoke, link_audit_control; the fixtures label run serially, one rg-game at a time).
- **Found for other lanes:** Revelation board flashing slot pixels depend on the exe's layout
  (`RevelationBoardPktSetColorLerp_34ce10` / `RevelationBoardDrawSprite_34c170` override).
- **Open:** the strips are mirrored art (dimmed), not new art; not play-tested; text at 32:9
  is squeezed to 0.375 (fine at the window's resolution, unreadable in x1 shots).

## 2026-10-24: Linux rg-game links (native-only, headless renderer)

Cross build `build/linux-i686` (Debian 12 i386 sysroot, clang/lld from Windows; logs
`out/linux3/`). **rg-game links**: ELF32 i386 `EXEC` (non-PIE, base 0x00400000), 12.4 MB.
Every default target (54 executables) also builds and links. Not run: no WSL here.

What still broke after the 10-18/19 fixes, and the fixes:
- `src/sce/padmc/libmc.c` (`$RG_MC_TRACE`, new since 10-18): `timespec_get` / `TIME_UTC`
  -> `mc_wall_ts()` (`clock_gettime(CLOCK_REALTIME)` off Windows).
- `src/native/render/nr_scene.c`: `gpu_nr_filtlog_frame` (the texture-filter lane's new
  hook in src/gpu) called unguarded in `nr_frame_begin` -> under `#ifdef RG_HAVE_GPU` (one
  line, renderer lane's file).
- `src/ps2/gs/gs_async.c`: the 10-19 `_Alignas(8)` fields were not enough: clang chooses
  inline vs libatomic from the pointer's type, and `ld64`/`st64` took a plain
  `volatile uint64_t *` (4-aligned on i386 SysV) -> `__atomic_load`/`__atomic_store`
  undefined. They now take an `aligned(8)` typedef: inline SSE2 `movq`, no `__atomic` call
  left in the object (Windows code unchanged: the MSVC ABI already aligns 8).
- `cmake/game_link.cmake`: `--no-icf` is not an ELF lld option -> `--icf=none`.

Headless renderer (`runtime.c gpu_start`, `!RG_HAVE_GPU && RG_NATIVE_ONLY`): a native-only
exe without a GPU backend never installed the frame-chain walker (only the D3D11 path did),
so it would stall on the title like the 10-22 `RG_GPU=sw` case. Now the walker is installed
and feeds the software GS model; VU1 programs run in nr_vux, nr_scene stays unattached (the
game keeps MSCAL + CALL). The build-time guard is simply "no `rg_gpu` target" (configure
prints `rg-game: no GPU backend for Linux: headless renderer`); no stub library needed.

Audits (new `tools/native/elf_audit.py`; `tools/native/link_audit.py` now parses ld.lld
`-Map` too): 256 undefined dynamic symbols, all provided by the NEEDED libraries (libc 207,
libm 42, libgcc_s 4, 3 weak); GLIBC_2.34 required (time64 entry points); no TEXTREL.
`link_audit check`: PASS; linked emulation = the Windows native-only set minus `rg_gpu`.
`elf_audit` over all 54 Linux executables: 0 failures.

Windows unchanged: own dir `build/linux2-win-i686`, `all` + rg-game build clean,
`ctest -j2 -L "host|runtime|native"`: 81/81 passed (3 skipped: real-data / control).

Left: running it (WSL + `libc6:i386 libstdc++6:i386`), save states are Windows-only, no
SIGSEGV handler, a Vulkan / SDL_GPU backend (checklist in docs/LINUX.md).

## 2026-10-24: widescreen stage 3, no aspect switch for menus (resume item 1)

USER (2026-10-19 play-test): menus and tutorials must not change the aspect. Stage 2
pillarboxed every full-screen menu at 4:3 (help sheets shrank the screen and widened it
again; the main menu's portrait circle showed squashed characters). Done in
`build/wide3-i686` (docs/WIDESCREEN.md "Stage 3"):

- The 4:3 switch for full-screen menus is gone (debug `RG_LAYOUT_MENU_PILLARBOX=1` only); the
  canvas, WIDE flag and 3D projection stay wide. The task that draws a full-screen indexed
  background is a "menu task": everything it draws, background included, is squeezed about
  the screen centre (one 4:3 element), so the background's holes stay on their panels.
- Menus park panels off screen; squeezed, they would appear in the side areas: off-screen
  menu sprites collapse, half-off / small ones are clipped (UV cut), wide title bars are
  pinned to the canvas edge.
- The sides: the menu's lowest background layer gets mirrored edge strips appended to its
  own GsPkt (A+D sprites; no renderer change), so the art reaches the canvas edges; a help
  sheet over a scene capture stretches its dimmed margin instead; the frame clear is black on
  menu screens.
- The squashed characters: the circle is a 256x256 copy of the field frame
  (`MenuCaptureScreenTex_298810`, x 191..446), anamorphic on a wide canvas. New override
  (`tools/wide/menu_overrides.py`) resamples it from the wide frame (`rg_layout_capture_wide`),
  so it holds the 4:3 picture.
- Tools: `tools/wide/stage3shots.py` (menu / tutorial / item / shop / save / factory / insect
  scenarios at any aspect, `RG_ASPECT_LOG` per run), `tools/wide/idcheck.py` (two exes: run
  hashes + shot pixels). Host test `settings.wide_menu`.
- Results: no aspect change at any menu / tutorial open or close (aspect log: one change per
  run, title -> game); run hashes identical at 4:3 / 16:9 / 21:9 in 8 scenarios; Original /
  4:3 against a same-tree baseline: run hashes identical, 62 / 64 shots pixel-identical, the
  2 others nondeterministic in the baseline itself (field 3790 at (173, 386), insect team
  select at (338, 81)). Shots `out/wide3/a13`, `out/wide3/compare/sheet1.png`, `sheet2.png`.
  Checks (exe `out/wide3/s3final`, built 17:48 from the tree with the 17:42 EE-float flip and retimed goldens): regen --check 300 + verify 8/8, mapcheck 5/5, bootcheck --all 29/29, ctest -L "wide|render|settings" 47/47 (game_replay skipped), full ctest 721/721 (8 skipped: realdata, game_replay, readback_lag, link_audit_control); ingest --check 0 problems.
- Found on the way: `rg_layout.h` uses `RG_LAYOUT_H` both as its include guard and as the
  448.0f frame height (clang warns "macro redefined"; harmless, left as is). The tree moved
  under this work (EE-float / GPU agents): the pause / battle2 run hashes changed between
  builds of the same day, so every Original comparison above is between two exes of one tree.

## 2026-10-24: EE floats (resume item 3): PS2 rounding by default, retail libm, goldens re-timed

Lane "eefpu" (build dir `build/eefpu-i686`, scratch `out/eefpu/`). USER decision (via the lead):
PS2 rounding (chop) by default; the exact add/sub/div model stays opt-in. No game/ re-ingest.

- **Flip:** `src/native/threads/rg_nk.c` ps2k_init: the kernel step runs with MXCSR = round
  toward zero + FTZ + DAZ unless `RG_EE_FPU=ieee` (comments in rg_nk_internal.h, ps2k_fpu.h).
- **Retail libm in src/crt:** `src/crt/crt_eelibm.c` = the retail fdlibm float routines in C
  from the listings: Sinf / Cosf / Tanf / Atan2f (+Atanf) / Asinf / Acosf / Powf with their
  kernels, RemPio2f **and the large-argument KernelRemPio2f_127170**, KernelTanf_127ae0,
  IeeeSqrtf_125988 (the integer bit-by-bit sqrt), Scalbnf_128f08; R5900 build (exponent 255
  normal, no denormals, no Inf/NaN branches), retail constant bit patterns, listing operation
  order. Retail quirks kept: ih = iq[jz-1] >> 8 for q0 == 0 (KernelRemPio2f), t = x - 1 (not
  |x| - 1) in powf's |y| > 2^27 branch, folded constants (acosf(-1), huge*huge = FLT_MAX). A
  zero divisor gives sign | 0x7F7FFFFF as PCSX2's DIV.S (`ee_divz`; asinf/acosf of |x| > 1 =
  +FLT_MAX, never NaN). `crt_math.c`: Sinf_128fd0 .. Powf_1291c0 call it when the MXCSR rounds
  toward zero (the EE mode), the host libm otherwise (`RG_EE_FPU=ieee`, as before).
- **Verification** (`tools/parity/eelibm_check.py`, new; work dir `out/eefpu/eelibm`):
  `tools/parity/eediv/ee_interp.py` (new) runs the retail machine code with the EE float model;
  it reproduces all **113,903 / 113,903** PCSX2 libm pairs (out/parity/libm/pairs.txt, 37 s), so
  it serves as the retail reference for the routines never probed: 60,030 vectors (tanf / asinf
  / acosf / powf over the game's ranges and edges, sinf / cosf / tanf up to 1e8 =
  KernelRemPio2f). The C compiled through `eediv_cc.py` (exact model) matches **all 173,933**
  references; the shipping build (plain SSE under the chop MXCSR) matches 32 % of the PCSX2
  pairs exactly and every miss is 1 ulp (the EE adder's dropped bits and the RN division are
  only in the exact model). Listings: `tools/parity/eediv/listing.py NAME` (new; decomp
  symbols + its mips-ps2 objdump on the retail ELF; `--words ADDR N` for tables).
- **Gun cycle 16 VBlanks** (`guncadence.py port`, default env): A taps/10 every 16, B held 16,
  C taps/6 16; retail 16. `RG_EE_FPU=ieee`: 14 (out/eefpu/gun1, gun1i).
- **Goldens re-timed (staged, landed 2026-10-24 17:42:26 local = 21:42:26 UTC in one step,
  `tools/fixtures/stage_swap.py`, backup out/eefpu/swap_backup):**
  `newgame_save2.input.txt`: retime.py from the battle state: the "Suggestions" sheet opens at
  25,860 (was 25,890), so its three STARTs moved to 25,930 / 26,050 / 26,170 and the SQUAREs
  resume at 26,210; win 26,510, field control 28,740, transporter menu 30,740, back in the field
  31,680: all as before, so **fxlib.MILESTONES unchanged** (battle_won 26,780, town 28,840,
  save_point 30,220, trans_menu 30,780, saved 31,700). `boot_save2_battle2.input.txt`: retime.py
  from a state at 4,890 (same as 10-19): no mid-battle help sheet any more, the fight lasts to
  7,160 (results 7/504 7,200-7,420), "Map Display" sheet, field control 7,630: **battle2_won
  7,250, battle2_field 7,700** (was 6,450 / 6,900; STATUS milestones must be multiples of 50),
  `boot-end: 7700`, rewards.py default `--fields 7700`.
- **Checks** (exe `out/eefpu/exe1/rg-game.exe` = build/eefpu-i686): regen.py --check 300 (set
  `out/fixtures/09c963c5179057aa`, power-on to 32,000 in 230 s, save2 card byte-identical to the
  staged one) + **verify.py 8/8**; `saveedit.py make` (cards from the new save2; the hand-made
  zshop / zshop2 and save1 untouched); **bootcheck --all 29/29**; **mapcheck 5/5**;
  **ctest -j2 721/721** (713 passed, 8 data-dependent skips as usual; logs out/eefpu/ctest.log).
  New check in the crt bindings suite (tests/bindings/test_crt.c): 22 retail references within
  1 ulp under the EE MXCSR, EE zero division = +FLT_MAX, host libm under round to nearest
  (`ctest -L bindings` 9/9).
- Note for other lanes: `regen.py` always rewrites `out/fixtures/cards/save2`; an exe built
  before this change (host rounding) replays the new golden with the help sheet 30 fields
  later, so its regen may not reach the save: rebuild from the current tree first (the flip is
  in src/); `RG_EE_FPU=ieee` runs need the backed-up goldens (out/eefpu/swap_backup).
- **Open:** opt-in exact build `RG_EE_FPU_EXACT` not wired (plan: out/parity/eefloat/README.txt;
  eediv_cc.py as C/CXX compiler launcher for rg_game_* and for crt_eelibm.c; measure build time
  and frame cost); not play-tested; parity sweep (tools/parity/sweep.py) not rerun on the new
  default.

## 2026-10-24: item 8 (low-res model parts) fixed: render targets lost upscaled pages

**Cause (proven per draw).** Not the texture filter. The battle renderer draws each character
through its own page-offset FBP into one 512-wide buffer (bp 10752 / 10848 / 10880 bw8, plus
64x64 bw1 work targets inside it) and copies each part's screen box into the frame (fb 0)
with two CT24 sprites (GS draw path). Between the two copies the game uploads textures into
the top rows of that buffer, which marked the whole source target `stale`, so
`direct_source` refused it and the second copy read the part from the **1x mirror**: one
flat colour per native pixel, silhouette included, for exactly the parts whose second copy
came after an upload. At field 7000 that is Jaster's screen-left pauldron (box 222,164-241,187),
the hip item (334,275-351,302) and the gun. Both pauldrons use the same texture (14912), so
"which pool slot" was a red herring; the order of uploads and copies decides. Same class:
every view switch (`rt_bind` evicting an overlapping view) wrote back and reloaded the whole
buffer through the 1x mirror, a stale target reloaded every row at 1x, and composites whose
read set reached 1-2 texels past the target (bottom of the frame, the 192x192 blur passes)
fell back to the mirror (12,857 GS-path batches in the repro run).

**How it was found.** New `RG_NR_FILTLOG=file` (gpu_core.cpp; one line per textured native
draw `F`, per GS-draw-path batch `G` with the source and why direct sampling declined, CPU
writes into live targets `W`, stale reloads `L`, page copies `C`, display circuits `S`),
summarised by new `tools/native/filtlog.py LOG [--frames A:B] [--tbp ..] [--mirror]`, and
`RG_NR_DBGSKIP=K:F:T` (skip native draws of kind m/i/* into FBP F with TBP T) to find which
draw paints a region. The first suspect was checked and ruled out: under the old rule
(`nr_tex_ordinary`: any live target overlapping the texture's pages keeps TEX1) 47,227 draws
kept the GS filter, but their TEX1 is already bilinear, so the shot was byte-identical
either way. Repro scripts: `out/lowres/run.sh EXE STATE OUT [ENV=..]` (route replay to
7002 at x3, shot 7000, Jaster crop) and `out/lowres/repro.sh` (+ prep).

**Fix (src/gpu only).**
* Per-page staleness: `Rt.stale_pages`. A stale target reloads only its stale pages
  (`rt_load_stale_pages`); direct sampling (GS path `direct_source`, native immediates)
  refuses a stale target only where the pages read are stale (`rt_current_in`).
* Page-compatible eviction (`rt_page_compatible`: same kind and PSM, page-aligned bases,
  any widths): the evicted view is written back as before but kept until the new one is
  loaded, then the shared pages are copied at the internal resolution (`rt_copy_pages`,
  new backend `GpuBackend::rt_copy`, D3D11 CopySubresourceRegion).
* GS-path direct sampling accepts the 2-texel bilinear margin past a source target other
  than the one drawn into (as the native path already did); the shader clamps to the
  target's edge (gs_draw.hlsl `fetch_direct`, DIRECT bits 16-28). In place stays exact
  (gpu-tests `scene.alias_pages` "in-place strips" samples real texels past the target).
* Filter rule (the requested change, kept): a texture is non-ordinary only if a live target
  spans pages of it that a GPU draw wrote since their last host->local upload (renderer
  page set `drawn`, `tex_pages_ordinary`, both paths); `RG_NR_TEXRT=overlap` = old rule.
* `out/lowres/lazy_miss.patch` reviewed again and landed (gpu_core.cpp: no `im_read`
  narrowing on a lazy miss).
* Control: `RG_GPU_RT_PAGECOPY=0` restores whole-target staleness and drop + 1x reload.

**Result.** ch07_rosa battle, field 7000, x3, play-i686 base relinked with these files
(`out/lowres/rl5`, run hash 422dc81477b58725 = before): the pauldron, gun and hip item show
x3 detail (`out/lowres/final_ba.png`, before/after); the shot changes only on character parts
(2,264 px). GS-path batches sampling a target through the mirror: 12,858 -> 1 (the display
buffer before its first draw). Left open: native immediates still decode 6,672 target reads
from the mirror (format-changing views such as a CT16 view of a CT32 buffer, and reads 3+
texels past a 64x64 target): effect passes, not model parts. Retail oracle (cardboot.py)
not run.

**Checks** (build/lowres-i686 = current tree, after the EE-float flip landed 17:42; rebuilt 18:31): `regen.py --check 300` + `verify.py` **8/8**; `bootcheck.py --all` **29/29 PASS**; `mapcheck.py` **5/5 DRAWN**; ctest -j2 **721/721** (labels gpu|gs|native 224/224 earlier; `gpu.scene.alias_pages` caught the first, unrestricted margin version: in-place strips sample real texels past the target, hence the s != ct guard). The visual A/B was done on play-i686 relinked with these files (`tools/fixtures/relink.py`, gpu_d3d11.cpp with this build's shader headers): the route `out/lowres/fight/route.txt` no longer reaches the same fight on the new tree; renderer changes did not move run hashes (rl4/rl5/rl6 identical under the same goldens).

## 2026-10-23: items 6/7 (Revelation / item context menu) triage started

Cut short by session end; no source changes. late_game card boots on build/play-i686 and a
main-menu-open state was written (`out/fixtures/c579ec343fd4386a/boot/late_game_menu.rgstate`).
No repro input yet, no guard-census run. Next step in BRINGUP.md item 7.

Continued (item 7 only; item 6 handed to another lane): repro = power-on on the late_game card
with `tools/trace/goldens/item_use.input.txt` (Items -> Heal Potion -> Use). Soft lock, not a
crash: RG_BREAK showed `MenuItemCommandSelectState` -> SetState(0x2D) and
`MenuItemCommandState_2ad540` running every frame but stuck at its gate
`MenuItemCmdFadeSequenceStep_2adce0`; RG_WATCH on D_004824F0 saw no write. The function writes
its phase through `#define W (*(s16 *)&D_004824F0)` while declaring it
`extern const .. __attribute__((section(".sdata")))`; clang dropped every store. The dialect
`const-data` rule (2026-10 loading-screen fix) only matched decls ending in `;` right after the
name; it now allows one trailing `__attribute__((..))` (tools/portxform.py). Census
`tools/census/constwrite_census.py` (new): 59 cast writes in 13 files; 177 game/ files change.
New `tools/bringup/altlink.py` links a test exe with TUs swapped without touching the shared
build dir (used here: fixed exe reaches the target panel; build/play-i686 stuck). The stack-block
suspect (MenuItemUseTargetState `v80`, census OK-block) was not involved: that state is never
reached. game/ not re-ingested (another lane was building/regressing on build/play-i686); landing
steps in BRINGUP.md item 7. For item 6: same method (pon run on a card + RG_BREAK on the
StateMachineSetState_28ede0 RVA from rg-game.map to follow the menu states); main-menu
Revelation states (RevelationBoardOpen_349220 ...) are not in the const-write census, but
item-menu Revelation used the same fade gate and was stuck by this bug.

Item 6 (Revelation crash), separate lane: repro on build/play-i686 with
`tools/trace/goldens/revelation.input.txt` (late_game card, main menu row 4): EXCEPTION 0xC0000005
reading 0x77C in RevelationBoardPktSetColorLerp_34ce10 (stack: RevelationBoardDrawSprite_34c170 <-
RevelationBoardDraw_349e70 <- UiDrawWidgets), all registers 0. Different class from item 7: retail
34c170 is a pass-through (it never touches $a0 or $f12-$f19 before `jal 34ce10`; the 9th float is
its first stack word); the decomp passed uninitialised `u0`/`u2..u7` and an `FArg` struct, so the
board pointer read as 0 (auto-var-init zero). The caller and 34ce10 already had the right 9-float
signature. Fix: override `overrides/src/main/menu/RevelationBoardDrawSprite_34c170.c` with the real
signature, forwarding everything. altlink exe (out/alt-item6): board opens, Place -> Thunder Stone
(item grid), slot filled, Flash Sword in the ability list, backs out clean. `} FArg;` appears in no
other game/ file. Not landed (needs a re-configure of build/play-i686, owned by another lane).

Landing items 6/7 (DONE; first written as an in-progress note at 13:20): `python tools/ingest.py` (178 game/ files written,
log out/ingest1023b.log); overrides TargetSlotDraw_320b00 / DrawListEndPrim_141a20 re-hashed
(`ingest.py --check`: 0 problems; constwrite census 0 writes in game/ and overrides/); build/play-i686
re-configured and `--target rg-game` rebuilt (NOTE: rg-game is EXCLUDE_FROM_ALL, a plain
`cmake --build` says "no work to do" without relinking it); snapshot out/regress1023b/rg-game.exe.
Repros on it (new `tools/bringup/cardrepro.py`, shots in out/regress1023b/rep_item6|rep_item7):
item 7 target panel at 4100, back to field menu 4310; item 6 board + slot filled 4700, Flash Sword
in the ability list 5050, no exception. Checks on the snapshot (logs out/regress1023b):
`bootcheck.py --all` **29/29 PASS**; `mapcheck.py` **5/5 DRAWN**; `regen.py --check 300` + `verify.py`
**8/8** OK (run hashes equal to 1023a's: the golden route never hits the rewritten writes);
ctest -j2 **720/720** (8 skipped, as before). Play-test copy `out/playtest/rg-game-1023b.exe`;
play.bat / play-from-save.bat / play-test-save.bat launch it; headless 300 fields without `--data`
mounted `out/playtest/data` (124 files). Roll back: revert the
const-data regex in tools/portxform.py, re-ingest, restore the two override hashes (old values in
out/ingest1023b.log), move the 34c170 override aside, rebuild --target rg-game.

## 2026-10-23: widescreen NPC name labels and damage numbers

Both were drawn inside `TaskDrawStatus_2058b0` (layout suppressed, world task):
`ScreenMarkerDrawAll_31af50` -> `FontDrawText` per glyph (labels + their icons) and
`DamagePopupDraw_2d3240` (one GsPkt per digit, all popups in one DrawList prim), so a
per-packet squeeze could not fix the spacing. New `rg_layout_about_begin(ax, screen_px)` /
`_end` (src/settings/rg_layout.[ch]): while set, each packet's X is squeezed by s about the
given point (wins over suppress / Z test; returns 1 so sharp-X applies). Overrides generated by
`tools/wide/label_overrides.py`: labels/icons about the label's projected centre, digits about
the projected point. Checks (`out/widecheck/shots.py`, crops `out/widecheck/crop.py`): save2
town 3790 (Hooded Man label) and battle2 5125 (damage numbers): run hashes unchanged
(a315d67eb778da35 / bda00a5fe9c133ae), 4:3 battle shot byte-identical, 4:3 town differs only in
the message-window glyph that already differs run to run; 16:9 labels/numbers now 4:3-shaped
on their anchor (`out/widecheck/town_crop.png`, `battle_crop.png`). Not run (session end):
mapcheck.py, wide/render ctests; host test for rg_layout_about not added.

2026-10-23 regression check + play-test build 1023a (everything since 10-22 23:18: squeezed-text
Y-only snap + PF_SHARPX, host audio declick, about-point labels/damage numbers, pacer
`rg_pace_phase_done`, exe-relative dirs/settings, hw GPU default, rg_slots headless-only):
exe build/play-i686 2026-10-23 00:08 (ninja: no work to do), snapshot `out/regress1023/rg-game.exe`,
logs there. `bootcheck.py --all` **29/29 PASS**; `mapcheck.py` **5/5 DRAWN**; `regen.py --check 300`
(217 s, set `out/fixtures/c579ec343fd4386a`) + `verify.py` **8/8** OK (run hashes equal to the
10-22 set's); ctest -j2 **720/720** (8 skipped, as before). Play-test copy
`out/playtest/rg-game-1023a.exe`; play.bat / play-from-save.bat / play-test-save.bat now launch it;
`saves-all` rebuilt by `make_allcard.py` (28 files; zshop/zshop2 left out by staging a filtered
cards dir, since make_allcard would append them as FILE 29/30). `out/playtest/data` is a junction
to `data`, so double-clicking the exe mounts it (checked headless 1500 fields without
`--data`: `rg_fs: mounted ...\out\playtest\data: 124 files`); saves go to `out/playtest/saves`,
settings to `out/playtest/settings.ini`.

Item 8 (intermittent low-res model parts), texture-cache provocation, no repro: exe snapshot of
build/play-i686 00:08 in `out/lowres/exe/` (+ .map, so states work); `autobattle.py prep/fight
ch07_rosa` (3,000 battle fields, Lord Bee fight, route `out/lowres/fight/route.txt`), replayed with
`play.py` and 30 shots (5200..8100 step 100) under: default vs `RG_NR_TEXCACHE_MB=8` (the floor;
the run takes 2x as long, so eviction/re-decode is heavy) at x1 and at `RG_GPU_SCALE=3`; default vs
`RG_GPU_LAZY_CPU=1` (CPU decode of lazy transfers) at x3; default run twice (determinism). New
`tools/native/shotdiff.py A B [--out D]` (changed px, bbox, high-frequency ratio B/A): **every
pair byte-identical** (run hash 0657fe7c439210f4). So LRU eviction, same-size slot reuse and
re-decode (key = registers + CLUT content + page/transfer content) do not change a pixel in a
deterministic headless run; at x3 the model crops look sharp. The native mesh path samples level 0
only (no mip choice); mesh fallbacks in the run: 27 of 190,147; immediate GS-path prims 67,622
(texture feedback). Not ruled out: timing-only paths (windowed pacing / GS worker batches),
map changes, and a latent key mismatch: a lazy-transfer miss on an immediate batch materialises
only the texels the batch reads (`im_read`) but files the whole decoded rect under the transfer's
content key (gpu_core.cpp, `lazy_miss`), so a later batch reading other texels of the same upload
would hit stale texels (did not change any pixel here). No source change.

Item 8, lazy_miss review (code read, no build: play-i686 owned by the landing lane). A lazy
entry is only made from a transfer that arrives whole in one packet (elide_decide: x=y=0,
n >= bytes), so split transfers never become partial entries; gs_mem_lazy_texels needs every
block of the texture owned by that one entry, and writing any of its blocks replays the whole
transfer (lz_write), so a partial write inside the texture cannot happen. The real hole: the
immediate path does not run lazy_before_draw, and `im_read` is the UNWRAPPED UV box, so a
batch whose UVs lie wholly past the level-0 rect (repeat, U >= 2^TW) intersects it to an empty
`mr`: nothing is written, upload_pages(tex) uploads the stale pages, and the GPU decode of the
old pool-slot texels is filed under the transfer's content key (reused until evicted, for every
later upload of the same bytes). Immediates only (meshes pass im_read NULL). Fix (uncompiled):
`out/lowres/lazy_miss.patch` (no im_read narrowing on a lazy miss; costs nothing). Minor
second hole, not patched: a transfer whose edges are not block-aligned leaves old texels in
its edge blocks that the content key does not cover (non-pow2 images in a pow2 texture).

Item 8, user evidence (field 7000 x3, Jaster's right pauldron + hip item low-res, deterministic,
same with an 8 MB cache). Replayed on `out/lowres/exe` (play.py from ch07_rosa_battle.rgstate,
route `out/lowres/fight/route.txt`): `out/lowres/dump7000/s07000.png`, zoom
`out/lowres/dump7000_zoom.png`: the screen-left pauldron is point-sampled at about one texel per
native pixel, the other shows sub-native detail. `RG_NR_FRAMEDUMP=950` (frame 950 = field ~7000
after this state; 954 frames to 7002) in `out/lowres/dump7000/log.txt`: 145 native draws; every
character texture is T8 (CLD=1) in a pool at tbp 10752-15168, e.g. 14336 / 14592 / 14656 (256x256,
tbw4) and 14912 (256x128). The filter setting `graphics.texture_filter` defaults to bilinear
(10-18 fix for low-res weapons) but applies only to textures `nr_tex_ordinary()` calls ordinary:
any live render target whose pages overlap the texture's pages sends the draw back to TEX1
(nearest). `out/lowres/x3rt.log` shows short-lived targets inside the pool (bp 14336 bw3 CT32 h192
and CT16 h384 = pages 448-465; 10752/10976/11008/11040/11104 bw1 h64), so parts whose texture
sits in those pages flip to nearest while such a target lives: per part, per slot, deterministic
for one route, "random" across play. Lead suspect, not yet proven per draw (needs a per-draw log
of g.lin / nr_tex_ordinary: no build while play-i686 is being landed). `RG_GPU_TRACE`
(`out/lowres/trace7000.txt`, 100 MB, 6 min) has no target events. `RG_RENDER=emu` diverges the game
(different scene at 7000; `out/lowres/emu7000`), so it is no oracle for this. cardboot.py retail
check not run. Next: log per draw, then decide "texture is a target" by GPU-newer pages (the target
drew there after the last upload) instead of page overlap.

## 2026-10-22: default settings file and exe-relative dirs

rg_game_main.c: windowed runs without `--settings` load/save `<exe dir>/settings.ini`
(`rg_game_default_settings_path`); headless runs unchanged, so tests/goldens are unaffected.
Built rg-game (build/play-i686); not play-tested. Autosave on change still open (resume item 5).

Same day: `rg_game_exe_dir_path` (factored out of the settings helper) also feeds
`rg_game_default_dirs`: without `--data`/`$RG_DATA`, data = `<exe dir>/data` when that folder
exists (else the runtime's `data`); without `--saves`/`$RG_SAVES`, saves = `<exe dir>/saves`
(mccard creates it). Fixture tools pass `--saves` and `RG_DATA`, so they are unaffected. Checked:
headless 120 fields with a `data` junction beside the exe mounted it and wrote `saves/card1` there.

2026-10-22 autosave: rg_menu.c `close_menu` writes `save_path` when the overlay closes with
`dirty` set (one write per session of edits, not per key; trial reverts happen first). Save row
kept. rg-game + rg-settings-tests built; `ctest -R ^settings\.` 22/23 (wide_layout: stale
registration, "unknown test" in the binary, unrelated). Not play-tested.

2026-10-22 black-shot check (`out/shotcheck/shotcheck.py`, headless, newgame_save2 input,
shots at 1500/8000): build/play-i686 is all black with RG_RENDER=emu + RG_GPU=hw, with emu +
software GS, and with the native renderer when RG_GPU is unset; native + `RG_GPU=hw` shows the
title (max pixel 243). Cause is a title stall (`title_ctr=0 movie_frames=0`), not the shot
writer; the Oct 17 fixtures exe (not native-only) shoots fine in emu+hw. No fix made.
Follow-up: root cause of the software-GS stall is libdma_native.c `rg_dma_start`: without
`rg_vif1_chain_hook` (set only in runtime.c `gpu_start` after `gpu_create`) each VIF1 chain is
"a chain the walker cannot take, ignored", so the frame's VIF1 i-bit interrupt is never posted.
Fix: `gpu_choose` defaults cfg.gpu to hw under RG_NATIVE_ONLY + native renderer (explicit
`RG_GPU=0/sw/off` still honoured, with a stall warning); `gpu_start` falls back to WARP when the
hardware adapter fails. shotcheck (now also native_hw / native_sw modes): native default and
native hw both max 243 @1500, 255 @8000; native_sw black as expected. bootcheck was unaffected
because fxlib.game_env does `setdefault("RG_GPU", "hw")`.

2026-10-22 save slowdown (resume item 10): new `RG_MC_TRACE=1` (libmc.c native path; counters
from `mccard_get_io_stats`) prints one stderr line per card op: host wall us, files written/bytes,
files read, metadata rewrites, backups. Golden route save (newgame_save2, ~31,600): 11 ops (4 open,
4 flush/close, 2 setinfo, 1 open-read), 24 h_write_atomic files (130 KB), 9 card1.card+card1.txt
rewrites, 0 fsync (durable off; MoveFileEx WRITE_THROUGH measured ~1 ms), 0 backups (first save);
4-10 ms per op on both B: (HDD) and C: (NVMe), ~55 ms total spread over separate fields.
RG_FIELD_TIMES: save-menu fields 13-17 ms, mostly gs_wait, vs ~10 ms in town (runs were
concurrent, numbers noisy). Card I/O is not the dominant cost; no card fix made.

2026-10-22 rg_slots (resume item 5, last piece): `src/game/rg_slots.c` now drops to BELOW_NORMAL
and waits for one of the two machine-wide slots only when `--headless` is on the command line
(found by scanning `GetCommandLineW`, since the constructor runs before main). Windowed runs get
normal priority and no slot. Overrides both ways: `RG_SLOTS_PRIORITY=normal|low`, `RG_SLOTS=1|0`.
Checked: headless 1200 fields ran BelowNormal; with `RG_SLOTS_PRIORITY=normal`, Normal. Windowed
not run.

2026-10-22 audio popping (resume item 12): engine WAV (`RG_AUDIO_WAV`) of windowed boot-save2
runs (title, CONTINUE, town): 0 clicks, 0 hard gaps. All pops were host splices in
host_sdl.c `rg_host_audio_push`: device starves, the regulator's silence pads (after a starve or
a `rg_pace` re-anchor; frequent when the host runs below 59.94 Hz) and front drops, each a step
in the waveform. Fix: `rg_audio_declick` (host_audio.c, 2 ms linear crossfade) on the starve
callback (fade the tail out), pads (tail fades into the silence) and the first block after any
splice (including a block dropped whole). New `RG_AUDIO_DECLICK=0` (A/B), `RG_AUDIO_HOST_WAV`
(+ `.events.tsv`), alog `resyncs` now counts `R.pace` too; scanner
`tools/native/audio_popscan.py`. Concurrent (loaded) A/B, `out/audiocheck/l3_*`: off 193 clicks
+ 108 hard gaps, all at splices; on 0 / 0 (`l2_dc1`: starves and pads, 0 at starve/pad
splices). `ctest -R "audio|sound|^host"` 54/54 (host.audio_reg gained de-click checks). Not
judged by ear.

2026-10-22 shop slowdown (resume item 11): card `zshop2` = `saveedit.py patch --section 13020
--spawn-jump 34 --no-help` (Zerard bounty-sheet shop, Faye; ch04's 4010 refuses to sell), input
`out/shopcheck/shop.input.txt` (stick E 15 fields, CROSS x4 opens the shop ~3,935, Buy list,
CIRCLE out; back in the field 4,257), found with new `tools/fixtures/talksweep.py`.
`stutter.py run` windowed, RG_GPU=hw, build/play-i686 (`out/shopcheck/win1/report_shop.md`):
opening and browsing are smooth (60 fps, GS worker 5-9 ms/field, 1-2 tex decodes/field). The
spike is the CLOSE: fields 4,223-4,255 (~0.55 s) present only every 3-4 fields, 63-69 ms frames
(~15 fps): every field then draws the full 3D scene AND the fading shop UI (gsq ~5 MB/field vs
2.8 in town; per field 24 rt_creates, 52 rt_writebacks, ~21 nr tex decodes, ~2 MB uploads,
GS worker T1 ~14 ms + read-back waits 8-18 ms in the first frames); EE step stays 4 ms, no file
reads. In town the same 3D costs ~11 ms GS wait/field but the game renders it at 30 Hz, so it
fits. Not texture-cache churn (decodes match the field's steady state). Leads: the 24 render
target creates per 3D field (feedback / CLUT targets recreated every frame instead of reused)
and the read-backs; no fix made.

2026-10-22 shop close, cause + fix (item 11). The render targets were not the cause:
`rt_creates` are logical (the backend pool serves them), and `RG_GPU_PROFILE` gives
write-back + load ~0.5 ms GPU/field. New `RG_GPU_RT_LOG=FILE` (gpu_core.cpp) shows the 24/field
come from the game's post-effect chain reusing scratch VRAM (bp 10752-11616, 14336, 16256)
at bw 8/3/1 and CT32/CT16. Every reinterpretation drops one (bp,bw,psm) target and loads
another. That is inherent to the target model. Its CPU cost (unbind_all, pages_of) is ~2 ms
of the worker. rgprof, headless, close fields: the worker takes ~16 ms/field, 6 ms of it
GS-model host->local transfers (`xfer_image_body`/`gs_pixel_addr`, 3 M px/field;
PERF-3D proposal 1), and the main thread waits in `gs_async_wait_mark`. The real bug was
pacing. `rg_pace_present_now` sampled the phase cost before the GS-worker wait (host_half
waits after the decision), so the cost looked like ~5 ms and catch-up kept skipping
presents: 4-field batches, sync 45 ms. Fix: new `rg_pace_phase_done` (rg_pace.c/.h), called
in host_half after the sync/wait, now provides the cost sample. The control is
`RG_PACE_COST_AT_DECISION=1`. Windowed A/B (`out/shopcheck/win3ctl` control vs `win2`,
`win4`): shop_close new-image median 32.2 -> 23.4/22.6 ms, frames > 40 ms 7 -> 2/3. Still
one 72 ms batch at the start while the moving average catches up. shop_open now has 1-2
~35 ms frames where the control's max was 21 ms. field/after windows unchanged (new images
33 ms). ctest gpu.* + kernel.* 122/122 (incl. kernel.pace), mapcheck 5/5 DRAWN.

2026-10-22 regression check of the day's changes (settings.ini/autosave, exe-relative saves,
RG_MC_TRACE, GPU default + WARP fallback, rg_slots priority): exe build/play-i686 23:18 (id
`7a47cfea729971e1`, snapshot `out/regress1022/rg-game.exe`; logs there). `bootcheck.py --all`
**29/29 PASS** (no fault); `mapcheck.py` **5/5 DRAWN**; `regen.py --check 300` (217 s, set
`out/fixtures/7a47cfea729971e1`) + `verify.py` **8/8** OK; ctest -j2 **719/720**, the one
failure `native.nmcheck_control5` (WILL_FAIL) was a -j race, not today's changes: all six
`nmcheck_control${c}` rebuilt the SAME corpus `corp24804c.bin`, so a control could read a
half-written corpus. Fix: per-control corpus `corp24804c${c}.bin` (src/native/render/CMakeLists.txt);
reconfigured, the 6 controls pass 3x at -j6. `settings.wide_layout` "unknown test": the
CMake list was right (test is in host_tests.c since 10-19); `rg-host-tests.exe` was a stale
10-18 binary (ctest does not build). `ninja rg-host-tests` fixed it; passes.

2026-10-22 widescreen text (resume item 9): shots via `tools/wide/stage2shots.py --only menu,pause`
at 4:3 / 16:9, native and `graphics.internal_res=3x` (out/textcheck/a, c, d; crops by
`out/textcheck/crop.py`). Fonts and HUD digits are **point-sampled sprites** (GS MMAG nearest;
`graphics.texture_filter` does not touch sprites, forcing bilinear changed nothing). Stage 2
squeezes them to 0.75 in guest pixels; at native res nearest then drops every 4th texel column,
and at 3x the upscaled sprite path snapped coverage and texture coordinates to *native* pixels
(gpu_core.cpp sprite snap + nr_draw.hlsl PF_SNAP), reproducing the same dropped columns at any
scale; the 4/3 stretch at present makes the uneven strokes visible. Fix: the GsPktClose override
tells nr_im when `rg_layout_packet` (now returns int) squeezed the packet
(`nr_im_note_xscaled` -> `im_rec.xs` -> `gpu_set_im_xfree` during the marker); such sprites snap
only Y (coverage + `R[22].w` in PF_SNAP). 4:3 and unsqueezed packets unchanged (layout inactive;
battle/tutorial/menu 4:3 shots byte-identical; field 4:3 differs only in the pulsing X icon).
Result at 3x: no texel column lost (`out/textcheck/field_16x9_before_after_3x.png`); columns
are still 2 or 3 px wide (2.25 px per texel). Native res (1x) is not improved. mapcheck 5/5
DRAWN; ctest wide/settings/gpu/nr/render 174/174 (4 skipped).
Follow-up, same day: sharp-bilinear X for those sprites. gpu_core.cpp sets `PF_SHARPX`
(0x8000) on immediate draws with `R[22].w` (xfree sprite), TME, point filter, not a live-target
read; nr_draw.hlsl then samples the two texels either side of the nearest texel boundary
(point sampler, nearest in Y) and weights them by the pixel footprint `|ddx(u)|`
(`saturate((u - seam)/fw + 0.5)`), so a 0.75x glyph keeps every column. Shots (stage2shots
menu,pause, 4:3 + 16:9, 1x and 3x; pre = the previous exe): all 4:3 shots byte-identical at 3x
and at 1x except the pulsing X icon in field; 16:9 differs only in squeezed 2D. Crops and
before/after: `out/textcheck/sharp/` (`field_16x9_before_after_1x.png` etc., compare script
`cmp.py PRE POST tag`). mapcheck 5/5 DRAWN; ctest gpu/render/nr/wide/settings 129/129 (4 skipped).

## Where it gets to

```powershell
$env:RG_DATA = "data"
$env:RG_STATUS_EVERY = 500          # one STATUS line per 500 fields (below)
build\link-i686\rg-game.exe --headless --fields 4000 --screenshot shot.png
```

- **No input:** crt0, the static ctors and SysBootInit run, and MainLoop loads the
  **TITLE overlay** (`D_0047E254 = 2`, game vbl 38). The title state machine
  (StateMachineSetState) runs states 1, 2, 3, 14 (card check), 4 and 5 (TitleStateMain,
  vbl 249). The **title movie plays**: `title_TitleMoviePlay_4f0600` runs at vbl 249 (the
  JAPAN Studio and Level-5 logos, one decoded frame every two vbls), and again at vbl 1029
  (1800 frames). The **title menu** is drawn at field 1500 (NEW GAME / CONTINUE / OPTIONS
  over the logo). It ran 4000 fields with no fault.
- **Golden input** (`tools/trace/goldens/newgame_battle.input.txt`, CROSS at vbl 1900):
  NEW GAME loads the **NORMAL overlay** (`D_0047E254 = 3`, sysmode 0) at about vbl 2120 and
  shows the opening story screen (starfield and an empty message window). GameMode stays
  -1 through vbl 5963 with no fault (retail: -1 at vbl 2640, 11 at vbl 3870). The message
  window draws no text: that is the next blocker.

## Fixes

| # | Fault | Root cause | Fix | Class |
| --- | --- | --- | --- | --- |
| 1 | `MainLoop_1c2c10+0x30`: the main MemStack `Memalign(16, 0x18B0000)` returns NULL | The port's allocator (src/crt/crt_heap.c) never gave memory back to sbrk, and when it grew it asked sbrk for the whole request, not just what the free top chunk lacked. Retail's newlib malloc trims the top on free (`sbrk(-0x1904000)` after SysCalcFreeHeapMaybe's 25 MB probe) and extends the top only by the shortfall | crt_heap.c is now newlib's dlmalloc 2.6 as retail links it, read from MallocR_1310d0 / FreeR_12f9f8 / MallocExtendTop_130e78 / MallocTrim_12fcf0 / MemalignR_130c10: SIZE_SZ 4, 16-byte alignment, MINSIZE 16, 4 KB pages, trim threshold 0x20000, binblocks, last remainder. The state is bound to retail .data (`rg_crt_heap_bind(D_00449868, D_00449C70)`). crt0's RAM block is 4 KB aligned, so page rounding agrees | port module bug (crt) |
| 2 | `strcpy(.., NULL)` in DataTableLoadBinFile_368bf0 | data2c printed 47 pointer words as text: `char D_00480010[4] = " FF\0"` is the pointer 0x00464620 (DataTable file names in D_004644F0) | datareloc rule `bytes-ptr`: in a byte-typed object, a 4-aligned word that is a 4-aligned address inside a MAIN data object becomes a relocation. Real text ("END", "IMG", "NaN") is odd, off a word boundary, or points into bss | stage rule (datareloc) |
| 3 | `ArenaAlloc_3702f0` always returned 0 | `ArenaAllocAligned_370330(..); return;` in a value function. mwcc leaves the callee's $v0; clang returned 0 | protos `def-bare-return`: `G(..); return;` in a value def becomes `return (T)G(..);` when G returns the same class (15 sites; `info-bare-return` logs the 16 it cannot spell) | stage rule (protos) |
| 4 | `VariantGetInt_15f780(0)` in DataTableCmdEntryDefine_40f6e0 | `missing-zero`: the decomp drops an argument whose register still holds the caller's incoming value after the C changed the parameter (`arg` advanced in $s1, $a0 untouched) | protos `missing-entry`: retail's listing (asm/matchings at the pinned rev) decides. A backward control-flow search from the `jal` (delay slots, branch-likely annulment, labels) proves the register holds the entry value, and the call gets an entry copy `__typeof__(p) rgp_entry_p = p;` (31 sites). The same search now gates `missing-passthrough` and `def-widen` (SaveCardHasFreeSpace_37b8c0 loads $a0 itself, so the def-widen was wrong) and spells a single reaching constant or global load (`missing-asm`). A reviewed table `MISSING_ARG_ASM` covers `Fill3U64Default_3b0990(arg0 + 0x2F0)` in two chara ctors | stage rule (protos) |
| 5 | `VariantGetInt_15f780(u_0)` with an uninitialised local (4 DataTable command handlers, SoundStreamSlotAlloc `u1, u2`, MesWinSetStyle `u`) | m2c spells an incoming register the function never declared as an uninitialised local | protos: never-assigned locals `u`, `uN`, `u_N` passed as arguments are treated as missing arguments, then passthrough / def-widen (asm-gated) | stage rule (protos) |
| 6 | `UNBOUND func_207A90` | The interior entry's C name is Ghidra-spelled (`FUN_00207a80_e1`), so `addr-alias` found no `func_00207A80_e1` | addr-alias also accepts `FUN_<start>_e<k>`. The UNBOUND row was removed | stage rule (protos) |
| 7 | int3 in LoaderReleaseById_1cd340 | `(F() << 0x30) >> 0x30` on a 32-bit int is UB; clang traps (TrapUnreachable on the MSVC target) | dialect `wide-shift`: `(__typeof__((F(..)) + 0LL))(F(..)) << K` for a call result shifted by >= 32 (3 sites; census `build/boot/ubscan.py` = `-Wshift-count-overflow` over the corpus) | stage rule (dialect) |
| 8 | (same scan) C++ value functions that can flow off their end are `unreachable` (trap) | mwcc just returned $v0 | `-fno-strict-return` for game C++ (cmake/game.cmake) | build flag |
| 9 | stack overrun in MsgTableParseText_28aab0 (`len` = garbage) | `SaveMenuMsgTableParse(fs, ArchiveGetFileByPath(.., &size), size)`: clang/i686 evaluates arguments right to left and read the stale `size` | dialect `arg-order`: a nested call writing `&x` before a later argument reads x is hoisted into `({ __typeof__(G) rgp_ao0 = G; F(.., rgp_ao0, .., x); })` (11 sites) | stage rule (dialect) |
| 10 | EIP 0 in SaveModeDispatch_375df0 | The only pointer-to-member-function call: mwcc PMFs are 12 bytes `{delta, vtbl, fn}`, called through PtmfScall_100e70. clang's MSVC PMF is 4 bytes | override `overrides/src/main/file/SaveModeDispatch_375df0.cpp` (spells PtmfScall) | override |
| 11 | TextStyleGetRgba_26f2a0 got `self` as its out pointer | The EE returns a struct through a hidden $a0 pointer, which is the definition's first parameter (`void F(R *out, ..)`). MSVC returns a struct of <= 8 bytes in EDX:EAX | protos `sret-call`: `R F(a..)` against `void F(R *, a..)` becomes `({ R rgp_sret; F((void *)&rgp_sret, (T)a..); rgp_sret; })`, and the caller's declaration is patched (18 sites) | stage rule (protos) |
| 12 | `UNBOUND SyncDCache` | GfxFlipBuffersMaybe_143650 calls the SDK cache op | no-op SyncDCache / iSyncDCache / InvalidDCache / iInvalidDCache in src/sce/kernel/eekernel.c. The UNBOUND row was removed | port module (kernel) |
| 13 | `ovl: fatal: func_004EAA80 has no target` | The title's menu callback 0x004EAA80 and state handlers 0x004EAB00 / 0x004E9FF0 are functions the C defines (`title_FUN_004eaa80`) inside a symbols.txt entry, so neither the registry nor datareloc knew them | gen_overlay_registry.py and datareloc take `<ov>_(FUN|func)_XXXXXXXX` definitions from the overlay C (3 entries; the raw state-table words are now relocations). `ovl_real_tests` expects title 99 functions | tools / stage rule |

## First lockstep divergence

`port_trace.py check` against `goldens/newgame_battle.tsv` (golden input, `--stop-vbl
3000`): **first divergence at vbl 80** in `GameDataPtr`, `SkillSlots` and `SkillTimers`.
Later divergences follow from it: TitleMenuSel 140, SaveExists and TitleCounter 260,
TitleMenuOpened 380, the mode and overlay symbols 2120.

Cause: the port gets through the title's session init far sooner than retail. Probe runs
(`probe.py --hooks sm`, `--fn DelayThread:0x117618`, `--watch`) show:

- retail: first title SM transition at vbl 469, TitleStateMain at 708, GameDataPtr set at
  vbl 515;
- port: SM at vbl 96, TitleStateMain at 249, GameDataPtr set before vbl 73.

From vbl ~60 to ~300, retail is **CPU-bound** in `DataTableBubbleSort_368220`. It calls
`DelayThread(10)` every 256 compares, about 800 per 20 vbls, with no CD reads in that
window. The pad and CD are not the cause: `PadUpdateConnection` returns 1 from vbl 9, and
the CD reads stop. Guest code costs no virtual time on the port (TRACE-PORT.md "Lag
frames", `kcall_cycles` 0), so the sort finishes in the same field. **Lockstep from boot
needs an EE cost model**: a design decision (charge cycles per guest work unit, or align
the two traces on game events instead of vbl). The heap layout itself matches retail. The
title SM object is at PS2 0x00948D90 on both sides.

## Diagnostics added

| Knob | What |
| --- | --- |
| `RG_HEAP_LOG=1` | crt_heap: one line per malloc/free/memalign with the PS2 address and caller RVA (`build/boot/rva.py` resolves it with rg-game.map) |
| `RG_STATUS_EVERY=N` | rg_game_main: field, game vbl, overlay id, sysmode, game mode/phase, title counter/menu, movie frames decoded |
| `RG_STATUS_DUMP=addr:size,..` | with the above: hex of PS2-address ranges through the trace address map (pairs with `probe.py --watch`) |
| `RG_VEH=1` | report first-chance access violations (when the unhandled filter is never reached); stack overflows are always reported |
| `RG_STACK_KB=N` | host stack per guest thread |
| probe.py `--hooks heap,sm`, `--fn NAME:ADDR[:ret]` | retail malloc family / sbrk; StateMachineSetState; any function |

## Next blockers

1. The NORMAL opening story screen draws an empty message window and GameMode stays -1.
   It needs the next debugging step: message text load and draw, and the movie and mode
   flow from the golden input.
2. The EE cost model, for lockstep (above).
3. 232 `missing-zero` arguments remain (after-call registers and listings with no asm).
   Each one is a candidate for the next fault of class 4.

## Checkpoint

Running state of the bring-up (updated at each milestone; newest first). Scratch tools
live in `out/bringup-checkpoint/` (`bld.ps1` incremental build + link, `maprva.py`
symbol -> exe RVA, `callsites.py` return-address RVAs of calls inside a function for
`RG_BREAK`, `rva.py` RVA -> symbol, `fnword_audit.py` data-word audit).

### 2026-10-19 (c) -- Retail parity: harness, gun cadence root cause (EE float rounding), EE FPU mode (opt-in, flip held)

Lane "parity" (scratch `out/parity/`, build dir `build/parity-i686`). Harness and tools:
docs/TEST-FIXTURES.md "Retail parity". No game/ re-ingest, no stage change.

- **Harness** `tools/parity/parity.py` (+ `fields.py`, `sweep.py`): same scripted input on the
  port and on PCSX2, ~260 game-state fields sampled once per game frame on both sides at the
  same code point (entry of GfxEndFrame_141c20), inputs keyed by **game frames** (not VBlanks:
  retail drops frames), plans anchored on events (game mode / phase / overlay), first
  divergence per field with context. New rg-game diagnostics (src/game/rg_game_main.c, all
  opt-in): `RG_BREAK_SPEC` (pointer-chain dump at every logged RG_BREAK hit, SDUMP lines;
  RG_STATUS_DUMP now shares the parser, spec up to 4 KB, unreadable pointers print NULL),
  `RG_INPUT_KEY=frames` (script keyed by the hits of the first RG_BREAK site), `RG_WATCH=addr`
  (hardware write breakpoint, WATCH lines with the writer's RVA); BRK lines end in ` hit=N`.
  `rg_crt_rand_next` (src/crt/crt_libc.c) is the newlib RNG state, no longer static.
- **Gun cycle 14 vs 16 VBlanks = EE float rounding.** The shot motion advances 0.9 per frame on
  a 7.0 clip; its phase reaches the cancel threshold one frame earlier with round-to-nearest.
  Retail rounds every float add/sub/mul toward zero (EE FPU; PCSX2 = SSE with RC=chop), and
  **retail's soft double (gcc fp-bit) also rounds toward zero**: PCSX2 probe of dptofp:
  0.70136020040698988 -> 0x3F338C57 (the nearest is ...58), out/parity/d2f.py. Fix:
  `RG_EE_FPU=chop` -- the kernel step (flows, handler chains, alarms, driven steps; ps2k_step
  entry/exit, around NK.pacing) runs with MXCSR = RTZ + FTZ + DAZ (src/native/threads/rg_nk.c,
  rg_nk_internal.h). With it: gun every 16 VBlanks (guncadence.py port: 16,16,16..; retail 16),
  motion time / phase bit-exact with retail every frame (parity walk_save2), atof of text
  configs exact (below). **Default stays IEEE** (lead: the flip revisits a user decision; held).
  With the mode off the run hash is unchanged (cc8aee46f64819db on the old and new exe);
  cost ~0 (37.8 s vs 37.9 s, same 6,900-field run).
- **atof** (src/crt/crt_libc.c): newlib's strtod fast path (one double op, rounded by the
  current mode) instead of the host's correctly rounded strtod: "0.275" in a config is
  0x3E8CCCCC on retail (motion clip rates, InfoCfgKeyCmd_1ab2a0; found with RG_WATCH).
- **Host scopes** `src/native/threads/kapi/ps2k_fpu.h` (PS2K_FPU_HOST_SCOPE: round to nearest
  inside, only when the caller is in the EE mode): sceDmaSend (native frame-chain walk),
  sceGsPutDrawEnv/PutDispEnv/SwapDBuff/ResetGraph, rg_audio_game_{bank,seq,cmd,pcm,pcm_mix,
  stream_write}, rg_layout_packet. Census: `tools/parity/fpboundary.py EXE` (616 host functions
  called from game code). Left to the renderer lane: nr_model_record2, nr_note_plane/light.
- **Exact retail float model (PCSX2 EE FPU), verified 113,903 / 113,903:** the retail
  fdlibm sinf / cosf / atan2f written in C from the listings (tools/parity/eediv/ee_libm.c)
  reproduce every Sinf / Cosf / Atan2f call probed on PCSX2 during a juraika walk
  (out/parity/libm/pairs.txt, test out/parity/libmtest) when compiled with: MUL round toward
  zero; ADD / SUB: the smaller-exponent operand first loses the bits the EE adder shifts out
  (mask 0xFFFFFFFF << (diff - 1), diff >= 25 leaves only its sign), then round toward zero;
  DIV round to nearest; no FP contraction. Plain chop matches 33 %, the host CRT 30 %.
  Implementation ready, not wired: tools/parity/eediv/rg_ee_ops.cpp (inline helpers, exact
  RN division without an MXCSR switch) + eediv_cc.py (compiler launcher: unoptimised IR,
  fadd / fsub / fdiv -> helpers except in the VU0 models, llvm-link, -O2); waiting for the
  lead (cmake/game.cmake option, src/crt libm).
- **Sweep (chop, exe of 04:09; out/parity/sw1/summary.tsv):** 10 card walks + battle2, no ABI /
  logic divergence; walks stay identical but for ulps 350-760 frames (rng never diverges in
  juraika, prison, vedan). Found again independently: the CollFrameTreeCalcBounds_16be80
  regression of the 02:30 sblock ingest (burkaqua: the leader never touches the ground, map
  block collision 0 tris vs retail 28; gone with the 03:5x tree). Other classes: load timing
  (tools/parity/rngtrace.py: DynClothDefInit 10 frames earlier on the port = instant loads)
  and 4-8 retail long frames per walk (menu opening, loads; inputs are frame-keyed).
- **Open (found by the harness, chop on):** (a) PCSX2 rounds float DIVISION to nearest
  (mphase 1.0999999/40: retail 0.027499998, port chop 0.027499996); (b) libm: retail sinf /
  cosf / atan2f are fdlibm float (RemPio2f, KernelSinf, ...), the port calls the MSVC CRT ->
  1-ulp yaw while walking; (c) spawn heights already differ in the 7th digit at field control.
  These ulps grow: after 120-350 frames a collision flag (Chara +0x3D8) flips, the rng
  diverges, encounters differ. Proposed fixes (need the lead's go: shared build / crt):
  float fdiv -> exact RN helper (IR-level rewrite, VU0 div excluded), C fdlibm float routines
  from the retail listings.

- **STATUS at wrap-up (lead: agent count reduced):** default NOT flipped. **USER DECISION
  (via lead):** chop via MXCSR during game code becomes the DEFAULT; the EE libm (fdlibm
  float C in src/crt) becomes the default libm for game code under chop; the exact add/sub
  mask + RN division rewrite stays an opt-in cache option only (proposed name
  RG_EE_FPU_EXACT, default OFF, never the shipping default; parity/oracle builds). The
  renderer-owned nr_model_record2 / nr_note_plane / nr_note_light stay under chop (matches
  VU1) -- renderer lane: no PS2K_FPU_HOST_SCOPE there. Tree state: consistent; with
  RG_EE_FPU unset every run is as before (run hash cc8aee46f64819db unchanged on the
  save2_battle2 boot), so **the goldens still match the current tree**.
  **Resume (one lane, in order):**
  1. Flip: src/native/threads/rg_nk.c ps2k_init (comment "Flip pending"): chop unless
     RG_EE_FPU=ieee.
  2. EE libm: move tools/parity/eediv/ee_libm.c into src/crt (Sinf_128fd0 / Cosf_128d30 /
     Atan2f_1291a8 = ee_sinf / ee_cosf / ee_atan2f; the host versions stay for RG_EE_FPU=ieee
     via an MXCSR check, or drop them). Without the exact rewrite its divisions are plain
     native divss (chop) and its add/sub plain chop: deterministic, close to retail, not
     bit-exact. Still to write from the listings for full coverage: Tanf (KernelTanf),
     Asinf / Acosf (IeeeAsinf / IeeeAcosf), Powf (IeeePowf), the large-argument
     KernelRemPio2f (ee_libm.c falls back to long double there).
  3. Re-time (docs/TEST-FIXTURES.md "Re-timing the route", tools/fixtures/retime.py):
     regen.py --only title,field,battle; retime from battle; shift the field block; tapsearch
     at the pad; write newgame_save2.input.txt; re-time boot_save2_battle2.input.txt;
     fxlib.MILESTONES + run_from.py docstring + TEST-FIXTURES table; regen.py --check 300,
     verify.py 8/8, saveedit.py make (cards from the new save2), bootcheck.py --all 29/29;
     message the lead before and after (other lanes' route gates).
  4. Opt-in exact mode: cmake/game.cmake option RG_EE_FPU_EXACT setting C/CXX_COMPILER_LAUNCHER
     of rg_game_${img} to `python tools/parity/eediv/eediv_cc.py` (plan:
     out/parity/eefloat/README.txt); eediv_cc.py already excludes rg_vu* (vu0.h) functions;
     measure build time and frame cost; use it for battle parity runs.
  Harness data kept: out/parity/sw1 (sweep, chop), sw2 (burkaqua after the sblock fix),
  out/parity/gunr/retail.jsonl (retail gun_route, stock PCSX2; port side not run yet:
  `parity.py port gun_route --exe out/parity/exe7/rg-game.exe --out out/parity/gunr --env
  RG_EE_FPU=chop` uses the chop battle fixture out/fixtures/20d7e4519169ba5f), out/parity/libm
  (retail libm pairs). Exes: out/parity/exe7 (current tree + this lane's changes).

### 2026-10-19 (b) -- stack-block, second pass: struct locals; save2_battle2 regression found and fixed; RE-INGESTED twice

Lane "sblock" again (docs/PROTOS.md "Stack-block census", fixes 6-8).

- **02:30 re-ingest (45 files):** struct locals smaller than their callee's reach and array
  members passed without `&` are now grouped (found by the stack-guard census run:
  EventFireTriggers_3e2660 `Query q` 0xE08 vs 0xE0D, DrawBufPairInitMaybe_15dc50 `Rec t1/t2`
  MemStack 0x54 in a 0x50 member); +47 blocks. Overrides added:
  PtalkFindPairRowMaybe_3e2160 (`Big` + retail tail; macro use), factory_FactoryStep_5069e0
  (`sp1D0` + `sp1F0` one block: the 2026-10-18 (f) "Def pointer = 5" FACTORY fault).
- **Regression in that ingest, fixed in the 03:5x re-ingest (5 files):** bootcheck
  save2_battle2 failed (battle2_won at 6450: still fighting; lead's report on build/play-i686
  ~03:00). Bisected by object swap (scratch tree `out/sblock/bis`, `out/sblock/bisect.sh`): 1 of
  the 42 changed files, **CollFrameTreeCalcBounds_16be80**. Its recursive call writes a {lo, hi}
  bounds pair through `&sp50` into sp50 and **sp60** (retail sp+0x50 / sp+0x60); sp60 is never
  address-taken, so the new trailing-pad rule (fix 5) padded slot 0x10 and the C's reads of
  sp60 saw zeros -> wrong collision bounds -> the fight played differently. Fix (stage): a
  hole that a local NAMED for its slot (`spNNN`, also `sp60q`) fills is placed by that name
  BEFORE any padding. Same correction for Character2DrawWithOwnLightMaybe_1ae720 (`sp60q` +
  `sp70` = one 0x1A0-byte light state; the `sp70 + 0xC0` ambient write was going to a separate
  array) and ScriptCmdEffectGetParamFloat_32d940 (`sp5C` placed). save2_battle2 PASS again
  with the original 02:10 milestones: **no re-time needed**; lead/play-test: the route goldens
  stay as they are.
- Determinism check (lead's question on EventCastSetPosition_258a50): protos output identical
  under PYTHONHASHSEED=1 and 2; the decision changed between ingests because of fix 4 (header /
  union layouts made its locals sizable), not ordering. The wideret/retwiden stages are in every
  full ingest of this lane (`ingest --check` 0 problems, 220 overrides).
- **Two more small re-ingests (~05:30, 7 files; ~06:00, 3 files)**, from the stack-guard census
  hit MapAreaModelAddDrawOffRect_189300 `b90`/`bA0`: all 8 EABI argument registers ($8-$11) in
  the extent analysis, name placement generalised (`b90` + `bA0`), `typedef .. NAME
  __attribute__((aligned))` layouts -> CharaMoveHangMaybe_234920 `M3 n` + `V4 w` (4-row matrix)
  and BtlEffSetRowFindMatchingRec_3fb3c0 blocks. Final game/ tree 2fa6d3cb..: stack-block 114,
  manual 9, unresolved 559; `ingest --check` 0 problems, 220 overrides; fixture 0 failures.
  Final exe `out/sblock/exe` (build/sblock-i686 ~06:05): **bootcheck --all 29/29**, **full
  route 8/8** (same hashes as the 03:5x exe: battle 757d39d1dac5e463, saved ab6c8b4ed54dd050),
  mapcheck 5/5 DRAWN, camprobe = retail. Stack-guard census (exe of the pre-fix-7 stage): hits
  only EventFireTriggers q, DrawBufPairInit t1/t2, MapAreaModelAddDrawOffRect b90 -- all fixed.
- **Resume / next** (lane stopped at the user's agent-count reduction): review the 103
  needs-human rows of `census/stackblock_sites.tsv` (virtual calls with unknown vtables,
  callback fields, function pointers from elsewhere, cfg-VM default handler +0x404, script
  native dispatch); review the 5 remaining padded blocks (PROTOS.md fix 7 list); fold the
  classifier's resolutions (vtables, callbacks, fn-pointer args) into the stage so those
  extents feed blocks; a fresh guard census on the current stage (`RG_PROTOS_SB_GUARD=1`
  ingest into a scratch tree + `-DRG_GAME_TREE=<tree> -DRG_SBGUARD=ON`). Fast loop:
  `out/sblock/pre6.pkl` + `tools/stages/protos_pre.py` (re-dump when an earlier stage changes).
- **Verification of the 03:5x exe** (`out/sblock/exe`, build/sblock-i686 after the 03:5x re-ingest,
  game/ tree 48999dd9..): `bootcheck.py --all` **29/29 PASS** (save2_battle2 with the 02:10
  milestones); full golden route `regen.py --check 300` + `verify.py` **8/8 OK** (reaches saved
  31,700; battle hash 757d39d1dac5e463 = the pre-02:30 exe's again, later hashes differ from the
  regressed 02:35 exe as expected); `mapcheck.py` 5/5 DRAWN; `camprobe.py` = retail;
  `tests/protos/run_stage.py --check` 0 failures (new fixture NameBlock_401700).

### 2026-10-19 (a) -- stack-block census: every unresolved / manual site classified; stage fixes; RE-INGESTED

Lane "sblock" (scratch `out/sblock/`, build dir `build/sblock-i686`). Details and numbers:
docs/PROTOS.md "Stack-block census and rule fixes"; per-site table `census/stackblock_sites.tsv`
(tool `tools/census/stackblock_census.py`, fast stage loop `tools/stages/protos_pre.py`).

- **game/ RE-INGESTED 2026-10-19 00:2x (35 files changed; `ingest --check` 0 problems, 218
  overrides).** Other lanes: your next build recompiles ~33 game files (stack-block
  changes) -- no override of yours was touched. The CameraBaseLookAt_15fae0 override's
  recorded hash was refreshed (the stage now builds a (padded) block in the snapshot file;
  the override, which places side/up/dir/old, stays). 4 game files differ from the 23:54
  tree only in CRLF line endings (the ingest writes the snapshot's CRLF; whoever wrote LF
  versions: the content is identical).
- **Bug fixed (stage):** ScriptCmdEffectGetParamFloat_32d940 `s32 sp40[4]` receives a 20-byte
  effect handle (EffectCopyHandle_2dd3b0): 4-byte stack overrun on the port (script
  `effect get param float`); now a padded block.
- **Stage fixes:** switch (jump-table) callees analysed; memcpy/memset/.. reach = their length
  argument (25 bogus blocks from unrolled-loop widths removed); spill/field reloads, null
  tests, interior entries, depth 8; C++/union/bitfield layouts. Census: 798 rows, 0 BUG left,
  79 needs-human (function-pointer targets that cannot be resolved statically: listed).
- Runtime safety net: stack-guard census build (`RG_PROTOS_SB_GUARD=1` ingest +
  `-DRG_GAME_TREE= -DRG_SBGUARD=ON`); new opt-in CMake cache vars `RG_GAME_TREE` (default
  game/) and `RG_SBGUARD` (default OFF).
- Verification (exe `out/sblock/exe` = build/sblock-i686 after the re-ingest): `bootcheck.py --all`
  **29/29 PASS**; `mapcheck.py` 5/5 DRAWN; `camprobe.py` ch01_salgin eye (-3328.2, 97.0, -1894.9),
  ch05_factory (6589.3, -644.1, 5831.6) = retail; route prefix `regen.py --only
  title,field,battle,battle_won --check 300` + `verify.py` **4/4 OK** (run + frame hashes; the full
  route past ~26,700 is being re-timed by the play-test lane after the retwiden/wideret battle
  fixes, lead's instruction -- the stall at 31,200 is not from this re-ingest); `ctest -j2`
  717/718 (fail: `settings.wide_layout`, tests/host/host_tests.c:1220 `lpkt_x(0)` 83 vs 147 --
  the play-test lane's widescreen work in src/host, no game code); `tests/protos/run_stage.py
  --check` 0 failures (controls fail as they must).

### 2026-10-18 (g) -- missing map geometry root-caused (renderer); ps2card ECC; controls; stack-block large frames

Lane "mapreg" (scratch `out/mapreg/`; no build dir of its own was needed: runs on existing
exes, one relink).

- **Missing map geometry (ch06_vedan, ch09_labyrinth, ch12/13_mariglenn): renderer; masked
  on the current tree, not fixed.** New detector `tools/fixtures/mapcheck.py` (detail
  fraction of the shot at control+40 vs the retail shot, `--battle` also scores a random
  encounter; calibrated: missing 0.18-0.48, drawn 0.95-1.1; docs/TEST-FIXTURES.md "Map
  check"). MISSING: route5 exe2/exe3/exe4, ovu0 native-before (18:29) and native-after
  (19:13) -- so neither the VU0 conversion nor -O2 / the UB flags. DRAWN: build/play-i686
  20:37 (current tree, after the renderer's checkpoint 7): all 4 cards field AND battle
  (ratios 1.01-1.03 field, 0.94-1.05 battle) + ch08c control. Cause: `nr_mesh.c` rejects
  meshes whose UVs do not fit V2-8 unsigned ("UV not 8-bit unsigned", `RG_NR_DEBUG=1`: 34
  packets in ch09 = 21,780 of 56,925 mesh draws fall back); the frame chain walker of the
  17:45..19:13 native-only builds dropped all VU work ("VU work dropped (no VU1)"), so the
  fallback meshes never drew. Checkpoint 7 hands VU work to the VIF / VU1 models, which is why
  it draws now. Proof: current exe with `RG_NR_VU=0` = MISSING again (ratio 0.18), same run
  hash. Diagnosis + fix: docs/NATIVE-RENDER.md "Regression: missing map geometry"
  (renderer-owned files, not edited here). **Do not drop VU1 from the native-only link before
  the decoder takes these UVs** (gate: `mapcheck.py --env RG_NR_VU=0`).
- **Jaster without head and legs** (15:03 exe): drawn whole on every current exe (all
  bootcheck / battle shots of this lane; e.g. `out/mapreg/mcb_play2037/ch09_labyrinth_b6030.png`).
- **ps2card ECC fixed** (`tools/saves/ps2card.py _colmask`: bits 0..2 = 0x55/0x33/0x0F, 4..6 =
  0xAA/0xCC/0xF0). tests/padmc/test_ps2card.py: `test_column_parity_order` (pinned vectors),
  `test_matches_cardboot` (ps2card == cardboot's ECC on 200 random chunks and every written
  page of a formatted card). Retail (PCSX2) boots ch01_salgin from the UNMODIFIED ps2card
  export to field control (`cardboot.py ch01_salgin --ecc ps2card`, `out/mapreg/cb`); cardboot's
  default is now `--ecc ps2card` (`--ecc mcman` keeps the rewrite).
- **Controls**: docs/CONTROLS-AUDIT.md battle table and 4b labels corrected to the retail
  tutorial (X sword, SQUARE gun, CIRCLE jump). Code relying on the old reading: the goldens'
  SQUARE presses (`boot_save2_battle2.input.txt` wins with the gun; replays fine, unchanged);
  `autobattle.py` already defaults to CROSS = sword; **`src/host/host_input.c` labels** still
  say "Cancel / Jump? / Sub-weapon? (Circle)" and "Attack (Square)", and docs/INPUT.md rows
  52-53 / 66-67 the same (proposal for the input owner: "Cancel / Jump", "Gun (battle)",
  "Confirm / Examine / Talk / Sword (battle)").
- **protos stack-block: the missed CameraFollowLeaderStepMaybe_3081e0 box is now a stage
  block; RE-INGESTED (game/: 4 files changed, 2 overrides retired).** Not the depth-4 extent
  (the extent was found: 0x20). (1) Frames > 32 KB (`lui $1; ori; addu $29,$29,$1`) made every
  sp-relative argument an unknown term: `asmflow._expr` now folds sp + a 32-bit constant.
  (2) `_struct_layout` only knew structs defined in the file (Vec4 is in include/vec.h): it now
  reads the game headers' C view (C++-only parts dropped, `aligned(N)` honoured). New log rows
  `info-stack-block-unresolved` (680 rows in 246 definitions; 243 are
  VariantFireChangeCallback_36e480 jalr callbacks, then IterInit_370170 41, VariantSetRaw 29,
  sceVu0RotMatrixX/Y/Z 66, CfgVmRun 18: review list) and the trace switch
  `RG_PROTOS_SB_TRACE=<regex>`. Census: stack-block 82 -> 86, manual 75 -> 72 (left: 61 "slot
  holds no C local", 7 "cannot place", 4 "sizes unknown"). New blocks:
  CameraFollowLeaderStepMaybe_3081e0 ({lo, hi}), ModelUpdateBoundsProjectedMaybe_14ff90
  ({v140, v150}) -- **both overrides retired** to `out/mapreg/retired-overrides/` --,
  CharaCmdGunShoot_228f80 (a matrix written through `&v50` over v60 / cam: was a stack
  overrun on the port) and EvMapObjNodeApplyPartMatrixMaybe_367230 (0x40 bytes into a
  `Mat34`). `ingest --check` 0 problems, 217 overrides; `tests/protos/run_stage.py --check` 0
  failures (control fails as it must), test_vu0frame OK. **Other lanes: your next build
  re-configures (override glob) and recompiles these 4 game files.**
- **Verification** (exe `out/mapreg/exe_sb` = build/play-i686 20:37 relinked with the 4
  re-staged files, `relink.py`): camera equal to retail without the override (ch01_salgin eye
  (-3328.2, 97.0, -1894.9), ch05_factory (6589.3, -644.1, 5831.6); new
  `tools/fixtures/camprobe.py`); `bootcheck.py --all` **29/29 PASS** (14 encounters; also 29/29
  on play-i686 before the re-ingest); `regen.py --check 300` + `verify.py` **8/8 OK** (run and
  frame hashes); `mapcheck.py` 5/5 DRAWN.
- Files: new `tools/fixtures/mapcheck.py`, `tools/fixtures/camprobe.py`; edited
  `tools/stages/asmflow.py`, `tools/stages/protos.py`, `tools/saves/ps2card.py`,
  `tools/trace/cardboot.py`, `tests/padmc/test_ps2card.py`, docs (NATIVE-RENDER.md new
  section, TEST-FIXTURES.md, PROTOS.md, CONTROLS-AUDIT.md, this entry); game/ re-ingested.

### 2026-10-18 (f) -- battles fought across the library; retail comparison of every card; camera collision fixed

Scratch `out/route5/` (exe snapshots `exe/` = build/route3-i686 15:03, `exe3/` = the -O2
re-ingested tree 18:17 + the camera override), retail shots `out/retail/`. Tools and method:
docs/TEST-FIXTURES.md "Auto-battle", "Retail comparison".

- **Retail boots of manufactured cards work** (`tools/trace/cardboot.py`): all 25 library cards,
  save2 and factory load through CONTINUE on PCSX2 and reach field control at vbl ~3,150-3,300.
  **Bug (tools, not the port): `tools/saves/ps2card.py` writes the card ECC with the wrong
  column-parity bit order.** Evidence: the same card exported by ps2card was not seen by retail
  (no CONTINUE; `out/retail/cb1` first run went NEW GAME -> "Basic Battle Controls"), the same
  image with every spare area rewritten (bits 0..2 = parity under 0x55/0x33/0x0F, 4..6 =
  0xAA/0xCC/0xF0) loads. cardboot rewrites the ECC itself; proposal for the ps2card owner: fix
  `_colmask` (tools/saves is not this lane's).
- **Resolved, not port bugs** (same on retail): the magenta pillar in `ch09_labyrinth`
  (`out/retail/cb1/pairs.png`); "Battle Recorder" / "Frog Log" rows after leaving the factory
  (`factory_menu_before.png` "? ? ?", `factory_menu_after.png` named: retail does the same).
  Main-menu rows of all 25 cards match.
- **Bug (fixed by override): the field camera never collided with the map.** Retail's camera is
  pulled in / raised by walls and terrain, the port's stayed at the default orbit (eye 120 units
  from the look-at, +10 high) in ~half the areas (behind a fence in ch05_factory, outside the hut
  wall in ch03_burkaqua). Measured (cardboot logs Camera0..5; port: `RG_STATUS_DUMP` of
  0x4B56B0..): ch01_salgin control eye retail (-3328.2, 97.0, -1894.9) vs port (-3369.1, 75.6,
  -1894.1); ch05_factory retail 4 units from the look-at vs port 67; ch06_vedan identical.
  `RG_BREAK` on the return sites: `CameraSweepEyeCollisionMaybe_160c90` and
  `CollSweepCollectHits_1c7550` always 0, because `MapEvQueryCollTrisMaybe_1ff1e0` returned 0
  triangles in `CameraFollowLeaderStepMaybe_3081e0`. Cause: the query box is `&lo` with the
  callee reading lo and lo + 16 (= hi); retail's frame has lo at sp+0x61C0 and hi at sp+0x61D0
  (asm `addiu $6, $29, 0x61C0` before `jal MapEvQueryCollTrisMaybe_1ff1e0`), the C declares two
  separate locals (UB). Override
  `overrides/src/main/camera/CameraFollowLeaderStepMaybe_3081e0.cpp` (one struct {lo, hi});
  `ingest --check` 0 problems. Verified on exe3: ch01_salgin eye (-3328.2, 97.0, -1894.9) and
  ch05_factory (6589.3, -644.1, 5831.6), both equal to retail.
  **Stage-rule proposal (protos `stack-block`, UB / -O2 owner):** this site produced no
  `stack-block` row at all (game/PROTOS.tsv), although its pattern is the rule's: the extent of
  `&lo` through `MapEvQueryCollTrisMaybe_1ff1e0` -> `MapSlotsQueryCollTrisMaybe_1e34f0` ->
  `MapAreaTreeQueryCollTrisMaybe_1dade0` -> ... is probably past the depth-4 dataflow; either
  deepen it for these collision queries or log every stack-address argument whose extent was not
  resolved (`info-stack-block-unresolved`) so misses like this one are listed. Other callers of
  the same queries already use `rgp_blk` (CameraModeLockTargetUpdateMaybe_3062e0, TaskCharaInfo
  ..), so the rule works where the extent is found.
- **Regression seen and gone: Jaster without head and legs.** The 15:03 exe drew Jaster with no
  head and his legs missing (boots floating under him) in every area and in save2
  (`out/retail/pairs_save2.png`, retail whole; exeF 13:53 whole, `out/retail/jaster_old_new.png`);
  the -O2 re-ingested tree (exe3, 18:17) draws him whole again. Recorded for the UB / -O2 owner
  (it came and went with re-ingests of the VU0 / matrix / anim math).
- **New fault on the -O2 re-ingested tree (exe3, 18:17): FACTORY load.** `bootcheck.py factory`
  (passed on the 15:03 exe and on exeF): `EXCEPTION 0xC0000005 at
  factory_FactoryPartObjSetFuncFlag_4fd260+0x8 read 0x0000004D; stack:
  factory_FactoryPartObjStatePlace_4fdf10+0x43 <- factory_FactoryPartObjStep_4fe000+0x68 <-
  factory_FactoryPartGroupStep_4fea10+0x27 <- factory_FactoryStep_5069e0+0x33ea` at field ~4,250
  (`ovl=4 gamemode=16/4`, the factory scene's first part placement). eax = 5: the Def pointer
  `s->f24` the placement passes is the small integer 5 (read of 5 + 0x48). Log
  `out/route5/final/logs/factory.log`. For the UB / -O2 owner (this lane did not bisect -O0 vs
  -O2: a full rebuild per try).
- **New on the re-ingested tree (exe2 17:45, exe3 18:17): map geometry missing in some areas.**
  ch06_vedan (cyan sky only, no buildings / rails), ch09_labyrinth (black; no walls, no pillar),
  ch12_mariglenn and ch13_mariglenn (black but a sliver of ground): characters, HUD and minimap
  draw, the map does not, in the field and in battle (`out/route5/final/fights_sheet.png`).
  Control-shot brightness ch09 8 vs 53, ch12 15 vs 34 against the 15:03 exe; retail draws them
  (`out/retail/pairs_exe3_ctl.png`). Not the camera override: `out/route5/exe4` (exe3 relinked
  with the generated CameraFollowLeaderStepMaybe_3081e0.cpp, `relink.py SRC=GAMEPATH`) is as
  dark. The other 20 areas draw. For the UB / -O2 owner (bisect re-ingest vs -O2).
- **Battles across the library** (`autobattle.py`, `bootcheck.py --all --fight` on exe3): 13
  fights, 6 won, 6 lost, 1 stuck, **no crash, no hang** (table: docs/TEST-FIXTURES.md
  "Checkpoint (auto-battle)"); bootcheck 28/29 PASS (factory: the fault above).
- Open (not a bug, a difference to check later): the battle controls are X sword, SQUARE gun,
  CIRCLE jump (retail tutorial); docs/CONTROLS-AUDIT.md's battle table has Square / Cross inferred
  the other way round.

### 2026-10-18 (e) -- the whole game from manufactured saves: card library smoke test, 25/25 areas

Scratch `out/route4/`. Details: docs/TEST-FIXTURES.md "Card library", docs/SAVE-FORMAT.md.

- **Save decoding finished for fixtures**: CONTINUE places the party from the save's summary
  (`SysMsgFillFromSaveRecMaybe_3e4d10` -> mode message kind 1 -> `PartyLoadAndPlaceMembersMaybe_2f4b00`),
  the map from party +0x4 planet / +0x6 area / +0x8 sky; characters (level, stats, equipment),
  inventory objects, party members, money, progress slots decoded. The game's own data drives
  the cards: `rc/param/initial_status5` (278 developer start states per chapter phase),
  `phase_param`, `planetarea_matrix5`, `dbg/map_jump_en.txt`, transporter tables
  (new tools `tools/fixtures/gamedata.py`, `cfgdump.py`, `rgdata.py`, `cardlib.py`).
- **Smoke test: `bootcheck.py --all` 29/29 PASS on `build/route3-i686`** (fresh build of the
  re-ingested tree, native VU0, RG_NATIVE_ONLY=ON; also 25/25 + 4/4 on `out/route3/exeF`)
  (field control with the chapter's party, main menu, 15 random battles entered). Areas:
  Rosa (Salgin, residential, Sil desert, labyrinth, Kuje desert), the Dorgenark, Juraika (jungle,
  Burkaqua, falls, Leo King's castle), Zerard (plaza, prison, factory district, Gladius tower,
  spaceport), Vedan (Myna, mines, Cancer King area), Mariglenn (3 points), Alistia, ghost ship,
  ghost ship EX, space (Dorgenark deck). **No crash or hang** in any of them.
- Card bug (not a port bug, recorded for the next editor): a party member with no weapon in
  slot 1 faults in battle: `EXCEPTION 0xC0000005 at CharaCmdShot_229bc0+0x99 read 0x00000000;
  stack: ScriptCallWithArgs_302770 <- ActTimeEvntRunInRange_2281d0 <- ActCfgTableRunTimeEvnts_221f40
  <- CharaPostUpdateMaybe_20f0b0 <- ActionMgrPostUpdateAll_232670 <- TaskTableRun_1f5340 <-
  GameModeDispatch_27c670` (vcall on the NULL `CharaGetEquippedWeapon` result). Retail
  parties always have weapons; the editor now equips the section's equipment.
- Observation (needs retail): magenta glowing pillar in the Rosa labyrinth (ch09 card).
- The FACTORY data override `overrides/src/main_data/data2c_00480390.c` is gone: the re-ingested
  `game/src/main_data/data2c_00480390.c` now has the relocation itself (the proposed stage
  rule landed); FACTORY loads on build/route3-i686 (factory fixture PASS).

### 2026-10-18 (d) -- FACTORY / INSECT / INSMENU reached (manufactured saves); FACTORY load fault fixed

Scratch `out/route3/` (`ins1/` Insectron menu walk, `fac/` factory runs, `exeF/` relinked exe).
Details: docs/TEST-FIXTURES.md "Manufactured saves", docs/SAVE-FORMAT.md.

- **All five used overlays now load in fixtures**: TITLE, NORMAL (route), FACTORY
  (`--boot-save factory`), INSMENU and INSECT (`--boot-save insectron`). The cards are
  manufactured from save2 with the new save editor (`tools/fixtures/saveedit.py`): flag 0x3E8
  = main-menu Factory row; story var 5 >= 3 = title INSECTRON row (standalone Insectron mode,
  INSMENU); two registered teams in chunk 15 = Watch Battle (CPU vs CPU, INSECT, game mode 15).
  `tools/fixtures/bootcheck.py`: 3/3 PASS with the fixed exe.
- **Bug (fixed by override): rg-game faults on the first FACTORY load.** Evidence (boot of the
  factory card, Factory confirmed at field 4,100, FACTORY loaded at 4,200 = `ovl=4 gamemode=16/3`):
  `rg-game: EXCEPTION 0xC0000005 at rva 0x00019026 write 0x00484A3C`, ecx=0x00484A38;
  stack (rva.py): `factory_FactoryMenuBuildWidgets_4ea1d0+0x1e6` <- `factory_FactoryMenuResReady_4ec0e0`
  <- `FactoryMenuResReady_204890` <- `FactoryModeUpdate_27db40` <- `GameModeDispatch_27c670`.
  Cause: `D_004807F8` (`D_00480390` + 0x468, the factory menu's shared Slot pointer) is the
  retail word 0x00484A38 (= MAIN .sbss `D_00484A30` + 8) and data2c / DATARELOC left it a
  number, so the overlay wrote through a raw PS2 address. Census of the data2c files for words
  in MAIN's data/bss range (0x0047D000..0x004E9E80): this is the only real pointer (the other
  hits are u16 pairs and VU microcode). Fix: `overrides/src/main_data/data2c_00480390.c`
  (standard header, only that word becomes `(u32)(data2c_main_bss + 0x39B8)`); `ingest --check`
  0 problems (219 overrides); relinked `out/route3/exeF` = build/battle-i686 + the override:
  FACTORY menu opens, Blueprints grid, "Halt factory operations?" -> back to NORMAL / field.
  **Build dirs need a reconfigure** to pick up the new override file (cmake/game.cmake).
  **Done (UB-audit lane, same day): datareloc rule `short-main-ptr` relocates the word; the
  override is retired (docs/UB-AUDIT.md, docs/PROTOS.md).** Original proposal: flag `.data` words equal to a MAIN symbol interior
  address (data/sbss range) that no symbol covers exactly, instead of only words equal to a
  symbol start; 0x00484A38 sits 8 bytes into `D_00484A30`.
- **Observation (not verified against retail)**: after leaving the factory, the main menu rows 4
  and 5 read "Battle Recorder" / "Frog Log" where they read "? ? ?" before (save2 has neither
  unlocked: no 0x40E5 item, Hunter locked). Possibly stale row textures after the NORMAL
  reload (`TopMenuLayoutEntries_294ad0` picks the "???" texture only for locked rows).
  Shot: run `--boot-save factory` to 5,600. Needs a retail comparison before it is called a bug.
- No fault in INSMENU or INSECT over the scripted paths (title -> Insectron menus -> card load
  of both teams -> announcer intro -> battle, CPU turns to field 15,000).
- Save editor caveat: the port writes host pointers into the raw object chunks (StateBlock +4,
  team table +0x1188); the loaders keep their live values, so cards load back.

### 2026-10-18 (c) -- rebuilt, full ctest green, route re-timed (newgame_save2)

Scratch `out/route2/`. Details: docs/TEST-FIXTURES.md "Route" and "Checkpoint (route save2)".

- **Build**: `build/battle-i686` reconfigured with `-DRG_VU0_MODE=native` (user decision;
  the cache had `local`), full rebuild (25.5k objects, -j4) on the re-ingested game/
  (de031765) with the three overrides the user rehashed; `ingest --check` 0 problems.
  One transient compile error in src/gpu/gpu_core.cpp (renderer lane mid-edit,
  `lazy_before_draw` used before its definition) was gone on retry.
- **ctest -j2 (rg-game tests -j1): 708/708 pass** (7 skipped: realdata / GPU replay data
  absent), incl. the new `protos.*` abi2 fixture tests and `protos.abi_control_abi2`.
  One flake on the first run: `sif.native_sdk` failed once under -j2 and passes alone:
  it and `sif.native_sdk_control` write the same `host0:SIF_NATIVE_FIO.BIN` in the shared
  `RG_SIF_TMP`; fixed with `RESOURCE_LOCK rg_sif_tmp` on every sif test
  (tests/sif/CMakeLists.txt).
- **Run state confirmed fixed in play**: on the route the leader's A34 goes 2 -> 20/21/22 ->
  0 within ~50 fields of releasing the stick; the 2-field stick-tap work-around is gone
  (the pad step is now a 20-field DR tap onto the pad centre).
- **Battle behaviour changed twice today** (expected, the battle AI uses AngleWrap and VU0
  float math): with the fixed AngleWrap the first battle shows a "Suggestions" tutorial
  and runs longer (won at 27,220 instead of 26,600, local VU0); with native VU0 the
  tutorials come 140 fields later and the win 380 earlier (26,840). The new route
  `tools/trace/goldens/newgame_save2.input.txt` is timed on the native build: battle won
  26,840, Salgin control 28,960, transporter menu 30,960, "File 1 saved." ~31,700, field
  31,900; fixture milestones battle_won 27,000 / town 29,060 / save_point 30,440 /
  trans_menu 31,000 (new) / saved 31,920, all verified; `--boot-save save2` works.
- **No new game bugs** seen on the route (no crash, menus open, card written and loaded).
  The CPU lane's "second battle at vbl ~30,057" did not occur on this route/tree (field
  control 28,960 -> transporter event, no battle mode after 26,840).
- **Diagnostic note**: `RG_STATUS_DUMP=h0x0AA3....` in a run without a save state (plain
  boot) faults (the game RAM block is only at 0x0A000000 with the state region); set
  `RG_SS=1` for such runs.

### 2026-10-18 (b) -- run state root cause (EE rounding), ABI sweep, re-ingest -- BLOCKED at the build

Scratch `out/runstate/` (probe logs `p1`..`p4`, `b5.log`; decoder `dec.py`; retail probe
`ret_aw.jsonl`; trial trees `game-base`, `game-trial`; retired overrides `retired-overrides/`;
exe `exe5` = build/battle-i686 + the four route overrides + host_script/runtime of exe4 +
the AngleWrap fix, via relink.py).

- **Run-state root cause: AngleWrap_1cbf30 depends on the EE FPU rounding mode.** A per-field
  dump of the leader (`RG_STATUS_DUMP`, yaw +0x64, angular velocity +0x94, move dir +0x450)
  showed the yaw already equal to the move direction (1.680) and the turn controller still
  turning at the cap (-1.047/frame), then a chaotic 5-cycle; every error in (-pi, pi) came
  out as -sign(e)*pi. AngleWrap computes `x - 2pi*sign(x)*trick(0.5 + |x|/2pi)` with
  `trick(t) = (t + 12582912.0f) - 12582912.0f`: the EE FPU only rounds toward zero (floor),
  SSE rounds to nearest. Retail probe (PCSX2, golden input to vbl 8400,
  `probe.py --fn AngleWrap:0x1cbf30:ret:w=f12:r=f0`, new `fN` / `r=` items): 103/103 calls
  match the floor model (e.g. 1.55 -> 1.55, -1.28 -> -1.28, -3.73 -> 2.553). Fix: protos rule
  `ee-round-floor` (`__builtin_floorf`), PROTOS.md 2026-10-18. Verified with exe5 (boot of
  the route's save1, stick 40 fields then released, `b5.log`): yaw converges smoothly to the
  move direction, after release A34 goes 2 -> 0x14/0x15/0x16 (run stop) -> 0 (stand). Effect
  well beyond the leader: every chara/NPC/AI turn and the battle AI used the broken wrap;
  with the fix the first battle plays differently (exe5: the Action Gauge tutorial is still
  up at field 30,605, see "route" below).
- **ABI sweep** (PROTOS.md "Rules added 2026-10-18"): census tool
  `tools/bringup/abi_census.py`; rules `def-v0-return` (51), overlay-import tail value
  (the `*MenuResReady` class: Help/InsectEntry/Shop/Think menus had the transporter bug
  too), `u128-view` (4), extern "C" block linkage (the HatenaMark class), provider filter.
  Route overrides retired (moved to `out/runstate/retired-overrides/`):
  ActionPacketInitBattleDefeat_3e33e0, HatenaMarkListStep_344ee0, MenuTransIsReady_203870,
  normal_TransMenuResReady_516a90 -- the trial tree's generated files carry the same fixes.
- **Re-ingest done** (game/ tree de031765.., 355 files changed incl. game_protos.h).
  `tools/bringup/trial_syntax.py --trial DIR` (new): `-fsyntax-only` of every changed file
  (and given overrides) with build/battle-i686's compile commands against a trial tree,
  ~25 s; all generated files pass.
- **BLOCKED -- three other lanes' overrides need their hash updated after the re-ingest**
  (`ingest --check`: 3 problems). The edit was refused by the session's permission
  classifier ("modify shared resources"), so it is left for the user / the owning lanes:
  - `overrides/src/main/sound/SoundStreamThreadMain_1c1050.c`, `overrides/src/main/sys/MainLoop_1c2c10.c`:
    rehash only (game file change = a local declaration blanked, the override's own
    declaration is compatible with the new header prototype).
  - `overrides/src/main/camera/CameraObjApplyInputMaybe_1619e0.c`: rehash AND its line
    `extern void CameraObjOrbitControlMaybe_161260(Obj0Arg0 *, In *, s32, s32, s32);` must go
    (replace by `/*rgp*/`, as in the generated file): the definition now has C linkage, the
    header says `int ..(void *, void *, void *, int, int)` and the override's view is a
    conflicting declaration (hard compile error).
  Until then build/battle-i686 cannot be rebuilt (not started: no reconfigure, no full
  rebuild, no ctest on the new tree). `python tools/bringup/trial_syntax.py --trial game
  <the three override paths>` checks the fix in seconds.
- **Route (orchestrator report: leaves to the PAUSE menu at 28,800):** expected, the route
  after field 24,700 is port-timed against the broken battle AI. With the AngleWrap fix the
  first battle runs longer (exe5: still in battle, "The Action Gauge" tutorial up at 30,605),
  so the route's fixed START presses at 26,100.. open the pause menu. The continuation
  (battle inputs, Salgin walk, transporter) must be re-timed on the rebuilt exe
  (`tools/fixtures/play.py` segments); the 2-field stick tap workaround is no longer needed
  (the run state ends on release). `--boot-save save1` (card written by exe4) still loads
  to field control (exe5, 3,725) and is the way to test field behaviour meanwhile.
- **Tools**: relink.py `SRC=GAMEPATH` sources (compile a scratch copy of a game file with
  that file's command); probe.py `--fn` items `fN` (FPR bits) and `r=` (items at return);
  `tools/bringup/listings.py` (shared listing loader, was in out/bringup-checkpoint).

### 2026-10-18 (route) -- first battle won, Salgin, first save

Route lane (docs/TEST-FIXTURES.md "Route"; scratch `out/route/`, exes relinked from
`build/battle-i686` with `tools/fixtures/relink.py`: `out/route/exe4` = the tree of
10-17 23:31 + the four overrides below). The new route input
`tools/trace/goldens/newgame_save1.input.txt` plays power-on -> first battle **won**
(26,600) -> Salgin field control (28,700) -> transporter event + tutorial -> transporter
menu -> **save to MEMORY CARD slot 1 / FILE 01 written** (31,360, the port's card folder
holds `BASCUS-97490LV5RG_00` + `icon.sys` + `RG.ICO`) -> back in the field (31,600); booting
that card through CONTINUE loads it (field control on the transporter at ~3,725).

Game bugs found on the way (each fixed by a NEW override, `ingest --check` 0 problems):
- **Crash at the first enemy defeat (~field 24,880)**: `ActionPacketInitBattleDefeat_3e33e0`'s
  local view declared `u128 CharaSysGetEncounterEntryIdMaybe_3a36f0(..)`; on i686 a u128
  return is an sret pointer, so the callee read the hidden pointer as its object (RG_BREAK
  on the callee: args `0c21e398 0a5c5bc0` from ActionPacketInitBattleDefeat+0x54 <-
  BattleRecordDefeat_3a3410 <- BattleUnitOnHit; read 0x15). Override: s32 return. Census:
  only other u128-returning local declaration is `Md5DigestQword_369050` (4 sites, probably
  real).
- **Crash in the first field after the battle (~28,700)**: `HatenaMarkListStep_344ee0`
  called `HatenaMarkListAssignNearby_344900()` with no argument (protos `manual-decl` /
  `manual-call` row, C++ callee); retail passes its own `$a0` (the list) through. The
  callee walked a stale stack word as the list (raw guest pointer 0x670B80, write fault in
  HatenaMarkSetAssigned_345110). Override passes `arg0`.
- **Transporter menu never opens (game mode 20 phase 1 forever)**: `MenuTransIsReady_203870`
  became `r = (func_516A90(), 0)` (protos `void-value-zero`): the overlay callee's view is
  void because `normal_TransMenuResReady_516a90` is a bare `j normal_TransMenuResPoll_5181d0`
  whose int result passes through in `$v0`. Overrides: the ready poll returns the value,
  `MenuTransIsReady_203870` uses it.
- **Class census for the stage owner** (`game/PROTOS.tsv`, not fixed here): 166
  `manual-call` rows and 190 `manual-decl` rows (58 "count 0 vs 1", 9 "0 vs 2", 9 "0 vs 4",
  ... calls that drop arguments the callee reads, the HatenaMark class), and 883
  `void-value-zero` rows (each a caller reading 0 where retail reads the callee's `$v0`, the
  transporter class). Both shapes produce silent wrong behaviour, not compile errors.

Open (not fixed; the route works around it):
- **Jaster stays in the run state after the stick is released** (field): CharaActLoco_21cc10
  keeps `A34 = 2` because CharaSelectLocoState_21e190 sees facing `(sin, cos)(+0x64)` far from
  the move direction `+0x450` (dot < D_0047DB58, "still turning"): after a run toward
  (0.994, 0, -0.109) the facing yaw converges to -3.114 rad (should be atan2(x, z) = 1.68),
  i.e. Jaster runs with a ~90-degree facing error and the yaw stops turning once the stick
  is released (`out/route/r1`..`r4`: `RG_STATUS_DUMP=h0x0AA3ADB4:2,h0x0AA3A3E4:4,h0x0AA3A7D0:16`).
  Effects: running animation in place, `CharaIsStandOrWalkMaybe_20fe90` = 0 so CROSS
  (examine / talk / transporter) does nothing. Next step: RG_BREAK on the writers of
  Chara rot.y (`CharaUpdateMovement_20a7d0` f94 integration, `CharaSetRot_2387d0`) vs a
  retail probe of `[chara+0x64]` while walking. Route workaround: a 2-field stick tap toward
  the facing direction (sets the move direction = facing, the state exits).
- **Software GS (no `RG_GPU`) after `--load-state`**: a state saved at boot field 3,650 of
  the boot-save route faults in the GS worker (`gs_draw_kick+0xd53` ->
  `XmmCopyLargeLoop`, write 0x20C00000) and a power-on SW run to 5,100 spun at 100% CPU
  around field 4,200 (Salgin, after the story recap). With `RG_GPU=hw` both are fine.
- **Port vs retail:** plain rg-game runs key input scripts on the kernel VBlank count
  (= field), not the game counter (docs/RUNTIME.md "Pad" TODO), 33 VBlanks apart in this
  part of the game; the golden was timed on retail game vbls. After the first battle's
  tutorial both timelines re-align on the golden's START presses (retail battle resumes at
  vbl 24,732, port at field ~24,700). Retail replay of the new route (docs/TEST-FIXTURES.md
  "Route", `.tools/run/route_save1.tsv`): identical through the old golden; during the
  resumed battle the port opens "The Action Gauge" tutorial at ~field 26,000 (vbl ~25,967)
  while retail had not opened it by vbl 26,120 (the route's START then paused retail): one
  more symptom of the non-lockstep battle AI (Rand_133710 call counts), not chased.

### 2026-10-17 (first hit) -- battle tutorial opens

Scratch: `out/battle4/` (retail probes `apply.jsonl`, `clsn.jsonl`; port runs `p1`..`p4`,
`v2`..`v4`; perf census `census/`). Build dir `build/battle-i686` (note: the default
target does NOT relink `rg-game`; build `--target rg-game` too, as
`out/bringup-checkpoint/bld.ps1` does).

- **ctest after the ret-zext re-ingest**: 637/637 (no regressions). After this entry's
  changes: 651/651 (`ctest -j2`), `ctest -L protos` 7/7.
- **Hit pipeline, retail** (`probe.py --fn`): TaskStepJudgeObject_3135c0 ->
  SpatialMgrCollideAll_315800 -> QuadTreeApplyHits_315660 -> NodeRefObjApplyHit_3184a0
  (the attack judge's slot) -> BattleApplyHit_2ef930 -> CharaResolveActionHitMaybe_3b28d0
  -> BattleUnitOnHit. Attack judges come from CharaSpawnClsnJudge_227c70 (enemy
  attack time-clsn, first at 24073) -> NodeRefObjMotionGateCloneAndRegister_228690.
- **Port**: SpatialMgrCollideAll ran but never called QuadTreeApplyHits: no attack shape
  was ever built (NodeRefObjBuildAttackShape_318aa0 returned 0 for every object). The
  spawns happened (22913.. Hooded Man, 23155.. enemies), but CloneAndRegister never
  reached NodeRefObjMotionGateDefaultCtor: HandleHeapPoolAlloc gave no object. The
  per-frame body judges (6 per frame from ActionMgrPostUpdateAll) were never freed
  (retail reuses 6 slots; the port's list grew by 6 every frame).
- **Root cause 1 (rule `vslot-lane`, PROTOS.md part 3):** the judge Step slot (vtable
  slot 2) is called `(this, grid, dt)` by HandleRegistryStepAll_314e10; its
  implementations NodeRefObjUpdate_318af0 and JudgeObjectStep_314360 were `(void *,
  float)` (EABI: dt in $f12 regardless of $a1). On i686 dt read the grid pointer
  (~1e-38): judge lifetimes never ran down, the pool filled within frames of the
  battle start. Census `tools/bringup/vslot_census.py` (2 rows, both fixed).
- **Root cause 2 (native SDK prototypes as providers, PROTOS.md part 3):** with hits
  landing, the first guarded hit faulted in sceVu0CopyVector <- GuardWaveEffectStart_2d5ad0
  (view `sceVu0CopyVector(void *)`, retail passes its own $a1 as the source). The
  stage now reads `src/sce/vu0/sce_vu0.h` (array typedefs decay to pointers); census
  `tools/bringup/sce_arity_census.py`. (This is the ~field 23,100 crash the audio lane
  reported in every build of the tree after the first fix.)
- **Applied:** protos.py (`_vslot_lanes`, `_lanepad_params`, PROVIDER_HEADERS +
  array-typedef decay), re-ingested (trial trees `out/battle4/game-trial`,
  `game-trial2`; `ingest --check` 0 problems), fixtures `src/main/vslot/VStep_401000.c`,
  `src/main_data/data2c_0048000{0,20}.c`, `src/main/arity/FixCopyUser_13c4e0.c`
  (+ provider `FixCopyVector_13c480`), new control `protos.abi_control_vslot`.
- **Verification** (`tools/fixtures/run_from.py --exe build\battle-i686\rg-game.exe
  --fields 24800 battle -- --shot ..`, RG_GPU=hw, golden input; `out/battle4/v4`):
  BattleUnitOnHit from 23003 (+140; retail +113), 16 hits by 23395, then
  ScriptFnTransporterWarp at **23395** (+532; retail +215: the AI is not lockstep, RNG
  state differs, see the previous entry): the **battle tutorial opens** ("Basic Battle
  Controls (1) 01/03", `s24200.png`), the golden STARTs page it 1/3 -> 3/3 and close it
  (`s24700.png`), the battle resumes and HP changes (`s24805.png`, Jaster 73/80). No crash
  to 24810.
- **VU1 workload** (`RG_PERF_CENSUS`, `out/battle4/census`): fields 23050-23099 now
  1.40 M pairs / field (0x0328 program 597 calls / field); retail C_v24804 2.74 M per
  (2-field) frame = 1.37 M / field: the earlier 6.1 M / field battle figure (PERF-3D.md)
  was the divergent pre-fix state. After the tutorial (24760-24799) 4.25 M / field
  with the five enemies crowding the camera (`s24805.png`); retail's 24804 scene is not
  the same scene (positions are not lockstep), so this is not a demonstrated bug.
- **Next divergence:** the golden input ends at the tutorial's close (retail battle
  resumes ~24732). Open items: (1) the battle starts ~1,100 vbl earlier in the port
  than in retail (22863 vs 23963) and the AI's RandInt draws differ (Rand_133710
  call count before the battle), so post-battle-start lockstep needs RNG parity
  first; (2) extend the golden route past the first battle (needs battle inputs that
  win it; game-save fixtures, TEST-FIXTURES.md "Mechanism 1", need play past this
  battle). Tool notes: `tools/bringup/brklog.py rows --stack N` now reads the
  `BRKSTACK` lines (RG_BREAK_STACK); `run_from.py` needs its options BEFORE the
  milestone (`--exe X --fields N battle -- --shot ..`; options after the milestone
  are rejected by argparse).

### 2026-10-17 (battle tutorial) -- PAUSED checkpoint

Scratch: `out/battle2/` (probe records `pcsx2/*.jsonl`, port runs `p1`..`p7`, retail RAM
`ret23971/ee.bin` = battle+7, `ret23990/ee.bin`), `out/battle3/` (post-fix runs `v1`, `p8`,
`p9`, `hit.jsonl`). Build dir `build/battle-i686` (built with the fix below).

- **Correction to the previous entry:** the leader is retail **0xa3a380 (id 0, Jaster)** in
  both builds; the pool is identical (enemies ids 128..133 at 0xa344c0..0xa37e90, incl.
  0xa37300 = id 129, which retail has too). Retail **0xa397f0 is id 8, the Hooded Man**:
  his tutorial AI script (`AiUpdate` -> label 100 at battle+0, label 200 at +1, natives via
  ScriptVmExec) requests `ステップ攻撃` / `#1ステ左` / `#1戦立ち` / `#1ガード` through
  AiCmdRequestActionByNameOrLoco -> CharaRequestAction (fA68) -> CharaActDispatch.
  Battle start is port vbl 22863 = retail 23963 (first AI entries); both sides start the
  same AI labels on the same frames.
- **Root cause 1 (fixed, rule `ret-zext`, PROTOS.md):** ParseFlagNames_1ca700 (s32) halves
  of the 64-bit ActCfg prmt/attr/call/cmnd masks were sign-extended (`hi | F()`); retail
  zero-extends (`dsll32/dsrl32`, the unit's view said u32). The Hooded Man's stance attr
  `0x80000000` became `0xFFFFFFFF80000000` -> f3D0 got all four no-collision bits
  (0x1700<<32) -> CharaCalcBoundsRangeMaybe_237f20 returned 0 -> no collision tris, no
  ground (f3D8 = 0, retail 0xF) -> his script's AiCmdCharaIsNearGround branch differed and
  he never acted. Found with RG_BREAK on CharaOrFlags3D0_238960 (args `.. 80000000
  ffffffff`). Applied: protos.py `_ret_zext`/`_zext_after`, 20 sites, ingest into game/
  (tree c38d3fa4.., `ingest --check` 0 problems), fixture ZextFlags_400e40.c +
  run_stage/test_main/CMake checks; `ctest -L protos` 6/6, abi-ok prints the new check ok,
  abi-wide fails it as intended.
- **After the fix** (`out/battle3/v1`, golden input, RG_GPU=hw): the Hooded Man starts
  actions (first at 22907 = +44; retail +5), enemies attack from +7 (retail +25); his AI
  native sequence (`out/battle3/p8`, `tools/bringup/natdiff.py`) now equals retail's up
  to a RandInt loop (29 vs 21 iterations): RNG state differs (Rand_133710 is the game's
  own; the number of rand calls before the battle differs), so exact AI lockstep is not
  expected.
- **Still open (next divergence): no hit ever lands.** Port: CharaResolveActionHitMaybe_3b28d0
  is never called to +236 (`p9`), BattleUnitOnHit never to field 25600, HP unchanged,
  golden START (24450..) then opens the pause menu (`v1/s25500.png`). Retail: first
  Resolve at 24078 (+115) from **BattleApplyHit_2ef930 (ra 0x2eff04)**, a0 0x5ca3c0 /
  0x5c7d80 (BattleUnits), immediately followed by OnHit; 4 OnHits then the tutorial
  (ScriptFnTransporterWarp). Next step: RG_BREAK on BattleApplyHit_2ef930 (entry, then its
  internal early-outs / callees) for the window 22863..23100 vs a retail probe of the same
  function (`--fn Apply:0x2ef930`), and compare the attack-collision (clsn) state of an
  attacking enemy (ActInfoClsnStart_23e990 parses masks with ParseFlagNames too, not
  zero-extended in retail, so probably not the same bug). Commands:
  `RG_BREAK=<rva of BattleApplyHit_2ef930 from maprva.py> RG_BREAK_FROM_VBL=22860
  RG_BREAK_MAX=200 RG_BREAK_STACK=40 rg-game --headless --fields 23100 --saves <empty dir>
  --input tools/trace/goldens/newgame_battle.input.txt` and
  `python tools/trace/probe.py --out X.jsonl --fn Apply:0x2ef930 --fn Resolve:0x3b28d0 --stop-vbl 24100`.
- **Tools added** (`tools/bringup/`, per the reuse directive): `brklog.py` (RG_BREAK log ->
  rows with names, image base recovered at `call reg` breaks; `structdiff` of BRKDUMP
  objects vs a PCSX2 eeMemory.bin), `retnat.py` + `natdiff.py` (AI native-call traces,
  retail vs port, first divergence), `zext_census.py` (the ret-zext census).
- **Uncommitted state:** tools/stages/protos.py (ret-zext), game/ re-ingested (12 files +
  PROTOS.tsv/MANIFEST.tsv), tests/protos (fixture C + asm/main.s + run_stage.py +
  test_main.c + CMakeLists.txt), tools/bringup/*, docs (this entry, PROTOS.md). Nothing
  half-done; no processes left running.

### 2026-10-17 (first-battle "pushed back" loop)

Scratch in `out/battle/` (build dir `build/battle-i686`, configured like render-i686).
- **State found:** the session-4 `wide-*` rules were already in `game/` and in the
  user's build (render-i686 compiled 08:43 on 10-13 from the 05:59 staged tree), and the
  golden run with them (`run-z`) still never pushes game mode 11 (battle stays 7/201).
  `tools/stages/asmflow.py` was syntactically fine and consistent with `game/`
  (`ingest --check` 0 problems; a trial re-ingest into `out/battle/game-reingest`
  compares the tools with the tree). One real bug fixed in it: `wide_flow` reported
  `$v0` at `jr $31` BEFORE the delay slot, so `jr $31; sltu $2,$0,$2` (bit tests) and
  `jr $31; dsra32` looked like wide returns (17 false candidates -> 7 real).
- **Root cause (port side):** retail's `run-z`/PCSX2 `actstart.jsonl`: every
  CharaStartActionByName before the battle tutorial comes from CharaActDispatch
  (ra 0x20d77c); the port also starts actions from **CharaTryStartAction_216700**
  (the leader's input connections, called from CharaActLoco) with the mask
  `0x2000000000000000` (a high-word-only connection). The connection lookups
  (ActCfgTableFindNormalCnctByMask_220d10 / FindCnctByMask_220950 and their inlined
  static helpers Try1/Try2/find_item/find_mitem/try_link, ActDataFindCnctByMask_225c00,
  CharaTableDataFindTimeCnctByMask_226640) test `(mask & M) == M` with
  `M = ActDataCnctGetCmndMask_2274c0(..)`, declared `s32` but returning the 64-bit
  `ActInfoCmndGetMask_2311f0` result in `$v0` untouched; the helpers also took `s32/u32
  mask`. Cut to 32 bits, a high-word mask is 0 and matches everything: the leader starts
  (and restarts) a connection action it should not. Same class: the chara's own
  64-bit prmt/attr flag accumulators (`s32 r; r |= F64(..); return r;` in
  ActCfgTableEval{Prmt,Attr}FlagsRefs, CharaTableDataCollect{Attr,Prmt}Flags).
- **Rules being added (protos, `_infer_wide_carriers`):** `wide-ret` (a 4-byte def whose
  listing returns an 8-byte call result / 8-byte parameter in `$v0` and a caller's
  listing reads it whole), `wide-local` extended to `v |= F64()` accumulators and to
  values returned by 8-byte definitions, `wide-inline-param` (listing-less static
  helpers receiving the caller's 8-byte parameter by name) and helper-site `wide-param`.
  Census script `out/battle/wideret_census.py` -> `wideret_census.tsv`.
- **Applied (ingest into `game/`, tree 4063b14a..):** wide-ret 5 (ActDataCnctGetCmndMask_2274c0,
  ActCfgTableEval{Prmt,Attr}FlagsRefs, CharaTableDataCollect{Attr,Prmt}Flags), wide-local
  4 -> 9, wide-inline-param 6 (Try1/Try2, find_item/find_mitem/find_link/try_link), wide-param
  13 -> 15 (ActDataFindCnctByMask_225c00 / CharaTableDataFindTimeCnctByMask_226640 through
  try_link). `_key_def` now prefers an external definition over a static copy with the
  listing's name (CharaTableDataCollectPrmtFlags_226710 had one in 221cc0.c). Before the
  change, a trial re-ingest of the old tools reproduced `game/` exactly (tree e95ee1ca..).
  `ctest -L protos` 6/6 (new fixture WideRet_400d00.c). Build `build/battle-i686` OK.
- **Verification** (`out/battle/run-a`, `RG_GPU=hw`; note a headless run without
  `RG_GPU=hw` uses the software GS and is ~20x slower in 3D): golden input, battle at vbl
  22,903, unlock +94 vbl (unchanged). `RG_BREAK` on CharaStartActionByName / BattleUnitOnHit /
  CharaCmdSetShipPos from vbl 22,800 (`brk1.log`): no CharaCmdSetShipPos, no pre-battle
  start (the bugged build started the leader's connection action from CharaTryStartAction
  at 22,865, 22,867, .. every other vbl, and hit someone at 22,871: the loop the user saw).
  Now the first starts are the enemies' AI attacks via CharaActDispatch (+124 vbl), the
  same chara objects as retail (0xa344c0, a35050, a35be0, a36770, a37e90). With battle
  inputs after the unlock (`out/battle/battle_port2.input.txt`, `brk3.log`) the leader
  (0xa3a380) starts an action through CharaTryStartAction on the presses (23,163 .. 23,623)
  and nothing else: **the leader is controllable**. `ctest` (build/battle-i686) 622/622.
- **Next divergence (open): the battle tutorial still does not open.** Retail
  (`pcsx2/actstart.jsonl`, `evtrig.jsonl`): the leader (retail 0xa397f0) plays a scripted /
  AI sequence via CharaActDispatch from battle+4 vbl (`#1ステ左`, `#1戦立ち`, `ステップ攻撃`,
  `#1ガード`, `#1戦立ち`, `ジャンプ`), enemies attack from +25, BattleUnitOnHit fires 4 times
  (+113..+215; event `0x22060003` from BattleUnitOnHit+0x584) and the 4th is followed at
  once by ScriptFnTransporterWarp (the tutorial push, via VariantFireGetCallbackOnce).
  Port: the leader starts nothing by itself, enemies start attacking at +124/+266, and
  BattleUnitOnHit is never called up to +960 (with or without inputs), so the tutorial
  event never fires; START then opens the pause menu. Also the chara pool differs: the port
  has an active object at 0xa37300 (retail: none) and the leader one 0xb90 slot later
  (0xa3a380 vs 0xa397f0). Start there: what retail's CharaActDispatch call flags for the
  leader come from (ActCfgTableFindCallNameByFlags with `f568`), and the extra pool entry.

### User play-test 2, 2026-10-18 (out/playtest/rg-game-1018e.exe = build/play-i686 20:37, -O2, native-only, gamepad, widescreen)

1. **Low-resolution textures in 3D field scenes:** the controlled character's sword and gun
   look very low-res; so do the main character's face and some NPC faces. Suspects: mip/LOD
   selection (TEX1 LCM/L/K, MXL, MIPTBP) or texture upload/decode picking a smaller level
   in the native renderer; compare with retail (tools/trace/cardboot.py) and emu mode.
   **Renderer lane finding (2026-10-18 late):** not a native-renderer defect. `--boot-save save2`
   field 3,790 / 3,850 at internal scale 3, native-only (`out/nrender/bin/u22/rg-game.exe`) vs the
   oracle twin in emu mode (`tools/native/render_fx.sh tx_{emu,native}`): 39.0 / 38.8 dB, 0.01 %
   bad pixels, and the sword hilt, gun and faces are equally blocky in both; the retail shot of
   the same view (`out/retail/cb1/save2_control.png`) shows the same texel size at 1x. Those
   materials sample with GS nearest filtering (TEX1 MMAG / MMIN = nearest) and small textures;
   at 1x on a TV that reads as soft, at 3x+ on a monitor every texel is a sharp square. The
   native path follows the GS choice exactly like the emulated one (`nr_fill`: lin = MMAG ||
   MMIN linear), and the GS LOD depends on Q only, so the scale does not change the level
   chosen. Remedy available today: `graphics.texture_filter=bilinear` (3D, non-render-target
   textures; `gpu_gfx.c`). Suggestion for the settings lane: make bilinear the default of the
   upscaled presets. Regression check kept: the two fields above in the renderer lane's image
   checks (`render_fx.sh ... boot:save2 3 3800 3790,3850`, emu vs native).
2. **Gun fires inconsistently:** sometimes a delay between shots. Unknown whether retail has
   it. Suspects: button presses lost between pad polls and logic ticks (host pacing, input
   latching), or game behaviour (cooldown/reload). Compare with retail.
3. **Widescreen: UI is stretched.** The 3D looks right; the UI should scale but never
   stretch. = WIDESCREEN.md stage 2 (renderer-side layout transform for the non-WIDE-aware
   2D: text, windows, menus, party HUD, compass).
7. **(2026-10-19) Launch by double-clicking the exe (no .bat).** Today the play-test .bat
   files pass `--data`, `--saves`, `RG_GPU=hw` and `RG_SLOTS_PRIORITY=normal`. Make these
   defaults: find the data next to the exe (or via a config.ini / the settings file), fall
   back to the current lookup; hardware GPU by default when windowed; saves in `saves\`
   beside the exe by default; the rg_slots BELOW_NORMAL priority (and probably the slot
   wait) only for headless/test runs, not normal play. Keep every flag/env as an override
   so the fixture tools keep working. Not started (work paused).
6. **(2026-10-19) Widescreen: menus switch the aspect.** Tutorial/help sheets shrink the
   screen to 4:3 and back; the main menu's window onto the 3D shows squashed characters.
   Both come from stage 2's whole-screen pillarbox (by design so far). User: the aspect
   must not change. Plan: WIDESCREEN.md "USER 2026-10-19: no aspect switch for menus".
   Not assigned (work paused).
5. **(2026-10-19) Text darker than remembered** on the boot "reading memory card" screen and
   the Load menu (unselected FILE entries look grey; user remembers white). Main-menu text
   matches retail (out/retail/cb1/ch01_salgin_menu.png). Needs retail shots of those two
   screens (renderer lane). Also: an emu-mode headless `--shot` (RG_RENDER=emu, RG_GPU=hw) on
   out/playtest/rg-game-1019a.exe came out all black.
4. **No experience or money after battles** (early game, Salgin). Possibly intended
   (tutorial). Check against retail on the same battle (save2 / save2_battle2 cards,
   cardboot.py); if retail awards EXP/gold, it's a port bug. If intended, keep it.

**Play-test 2 lane checkpoint (build/play2-i686, scratch `out/play2/`):**

- **Goldens RE-TIMED 2026-10-19 ~02:10 for the retwiden + wideret fixes** (lead request):
  `tools/trace/goldens/newgame_save2.input.txt`: the first battle closed loop with the new
  `tools/fixtures/retime.py` (win 26,510, was 26,840; only the "Suggestions" sheet opens),
  the field block shifted -220, the pad step removed (tapsearch: no step needed, the old
  DR x20 now walks off the pad). Milestones (`fxlib.MILESTONES`, TEST-FIXTURES.md table):
  battle_won 26,780, town 28,840, save_point 30,220, trans_menu 30,780, saved 31,700.
  `regen.py --check 300` on `out/play2/exe-w` (= build/play2-i686, set
  `out/fixtures/90cb29c5bf155a58`): power-on to 32,000 in one run, card written
  (`out/fixtures/cards/save2`: now Jaster L1 12 EXP, 231 money), **verify.py 8/8**.
  `boot_save2_battle2.input.txt` re-timed from a state at 4,890 (results 6,390, field control
  6,820; milestones battle2_won 6,450, battle2_field 6,900): bootcheck save2 + save2_battle2
  PASS. Card library remade from the new save2 (`saveedit.py make`); **`bootcheck --all`
  29/29 PASS** (`out/play2/bc/`, no early-exit retry needed). The earlier "hang after 31,200" was the desync: CROSS at the old
  pad step opened a dialogue (game mode 12/1) and the save inputs never matched; my
  regen with the old golden sat in it (killed, PID 25732).
- **FOR THE LEAD (route hang after 31,200 on exes built 00:20):** this lane changed GAME
  BEHAVIOUR on purpose since 23:00: (1) stage `retwiden` (game/ re-ingest ~23:05): battles
  now award EXP / money / drops (BattleRecordDefeat fixed) -> the route's results screen can
  show level-up pages and different money / items, so every port-timed input after the
  first battle (route newgame_save2 past ~26,700, boot_save2_battle2 past ~6,300) may need
  re-timing; (2) stage `wideret` (game/ patched ~00:00): battle commands pressed during an
  action's recovery are now buffered (as retail): the route's SQUARE taps in the first battle
  fire more shots, so the battle can end at another field. Both are retail-faithful fixes;
  the route (and battle2) must be re-timed, not the fixes reverted. Not touched: memory
  card I/O, the transporter / save menu code, pad timing (host_input.c: labels only; the
  latch is unchanged). The stage 2 overrides (GsPktClose, TaskTableRun, compass, world sites)
  are inert at 4:3 (no layout code runs with the Original preset).

- **Item 4 (no EXP / money) = port bug, FIXED by a new ingest stage `retwiden`; game/
  RE-INGESTED 2026-10-18 ~23:05 (400 files, tree 25345a22..; `ingest --check` 0 problems,
  overrides 217 / 0 problems; a scratch ingest with the stage off reproduced the previous
  game/ byte for byte, only SNAPSHOT.txt differs).** Other build dirs recompile ~400 game
  files. Measured with the new `tools/fixtures/rewards.py` (party EXP at Chara +0x4B8,
  money at party +0x160 per STATUS line): save2_battle2 (Baphu / Mishi in Salgin) on the
  user's exe: results screen "0 EXP, 0 Dosh", records unchanged. Cause:
  `BattleRecordDefeat_3a3410` is called for every killed enemy (RG_BREAK) but returns early
  at `ActorCastToUnit(..)->v3D0() != 0`: slot 0x3D0 is `u8 UnitHasParent_3a3600` (retail
  `sltu`: 0 for an enemy); the decomp calls the slot through `VCM0(s32, ..)`, and on i686 a
  `u8` return is only AL, EAX's upper bytes held a pointer -> "has a parent" -> no defeat
  recorded -> `BattleCalcResults_3a2100` saw 0 enemies -> 0 EXP, 0 money, no drops, no
  bestiary. Systemic class: every 1/2-byte-returning function whose address is taken
  (vtables, callback tables) and is called through a wider type. Fix: stage
  `tools/stages/retwiden.py` (after devirt): such definitions (400) return u32 / s32 with
  `return (T)(E);` (value converted to T first, then extended = retail's register).
  After: same battle, same timing, Jaster and the Hooded Man +12 EXP, money 100 -> 228,
  results screen shows the gains. RG_PROTOS_NO_RETWIDEN=1 disables the stage.

- **Item 2 (gun delay) = port bug: buffered battle commands dropped (64-bit masks cut
  to 32 bits); FIXED (stage `wideret`, game/ patched 2026-10-19 ~00:00).**
  Measured with the new `tools/fixtures/guncadence.py` (pattern from AT: SQUARE taps
  every 10 VBlanks, held 200, taps every 6; a shot = an entry of `CharaCmdShot_229bc0`;
  port by RG_BREAK, retail by `probe.py --fn Shot:0x229bc0`). Same battle on both (the
  route's first battle, golden input + the pattern at 24,760, `out/play2/gun/`):
  retail fires every **16** VBlanks whatever the tap rate (a press during the shot's
  recovery is kept and fires when the recovery ends); the port fires 2-3 VBlanks after an
  accepted press and **drops every press made during the recovery** (cadence 20 with taps
  every 10, 18 with taps every 6, a 40-VBlank gap when a tap lands just before the window
  opens) = "sometimes a delay between shots". The live input path is not the cause:
  press latch, pump-per-field and SDL events deliver one edge per tap for every tap length
  and period >= 4 fields (new test `input.tap_cadence` + `_control`). Cause: the command
  flags (Chara +0x568; SQUARE gun = bit 56, CROSS sword 55, ...) survive an action frame only
  through the action's PENDING prmt / cmnd mask (`CharaActionUpdateMaybe_215ca0`:
  `m568 &= ActCfgTableEvalPendingPrmtFlags(..)`); that chain
  (`CharaTableDataCollectPendingPrmtFlags_2267f0`, `ActCfgTableEvalPendingPrmtFlags_221380`
  + its inline `applySubs`, `..Refs_221040`, `ActCfgTableEvalNormalPendingPrmtFlags_2217a0`)
  is typed s32 in the decomp; retail ORs and returns all 64 bits (`or $16,$16,$2` ..
  `daddu $2,$16,$0`), the port cut bits 32-63, so no battle command was ever buffered.
  The protos stage's wide-ret handles one level only. New stage `tools/stages/wideret.py`
  (before protos; detection = `tools/bringup/wideret_census.py`, asmflow wide_flow
  fixpoint): 10 MAIN definitions return long long with their accumulators / static helper
  (also PlayTimeSplitFromHandle_3d6220 / SavePlayTimeSplit_3eebf0 and four the protos
  rule already widened). **game/ was patched with exactly this stage's diff (17 files +
  game_protos.h + PROTOS.tsv rows, MANIFEST hashes updated, `ingest --check` 0 problems)
  instead of a full re-ingest**, because `tools/stages/protos.py` was being edited by
  another lane at the time (23:33) and a full ingest with it changed 29 other files
  (stack-block decisions, e.g. FileBuildDevicePath_1821f0, EventCastSetPosition_258a50);
  the next full ingest (by that lane) includes `wideret` from tools/ingest.py. Note for the
  protos owner: EventCastSetPosition_258a50's stack block flips between ingests
  ("sizes unknown" / "incomplete" extents), i.e. that decision is not stable.

  **After the fix** (`out/play2/exe-w`, same tutorial battle, same input): the port fires
  at a constant cadence whatever the tap rate (presses during the recovery are kept), every
  14 VBlanks; retail every 16. **Open (residual, new finding):** one game frame shorter gun
  cycle on the port: per-frame logic is 30 Hz on both (PlayerControlUpdate every 2 VBlanks,
  retail probe `retail_ctl.jsonl`), and in both each cycle is CharaPlayMotion (the shot
  motion restarted) followed by the shot 2 VBlanks later, but the restart comes after 7
  frames on the port and 8 on retail (`retail_try.jsonl` vs `tutw/play.log`). Suspects: the
  motion frame reaching the cancel window one frame earlier (float accumulation / rounding
  of the motion frame, `ActionEntryTimeMatch_228310` / `..Pending_2283b0` thresholds,
  `CharaActionGetCancelMaskMaybe_210b60`). Not a dropped press; the user-visible "delay
  sometimes" is gone.
  **Root-caused 2026-10-19 (parity lane, entry (c) above): EE float rounding** (retail rounds
  toward zero; the shot clip time 0.9/frame on 7.0 reaches the cancel phase a frame early
  with round-to-nearest); `RG_EE_FPU=chop` gives 16 VBlanks.
- **Item 3 (widescreen UI stretched): stage 2 done**, docs/WIDESCREEN.md "Stage 2": layout
  transform at the game's 2D packet builder (GsPktClose + TaskTableRun overrides, new
  `src/settings/rg_layout.[ch]`), full-screen menus pillarboxed 4:3, world-anchored sites
  suppressed; setting `graphics.ui_layout` keep / stretch. Original never activates it;
  run hashes identical across 4:3 / 16:9 / 16:10 / 21:9. Sheet `out/play2/wide/s2b/sheet.png`.
- **Item 4 (bootcheck "FAIL at 0 s"): cause = `run_from.py` scratch dirs named by the start
  second** (`runs/boot-YYYYMMDD-HHMMSS`): two runs starting in the same second (another
  lane's bootcheck on the shared fixtures dir, or consecutive passes) collided: the second
  `copytree` raised at once (exit 1, no STATUS line: the 0 s FAIL seen in
  `out/ovu0/bc-all.log` and `out/stutter/bootcheck.log`, in bursts while other lanes ran), or
  one run's cleanup removed the other's saves. Fixed: `tempfile.mkdtemp` names. Hardened
  `bootcheck.py`: private exe copy per check (a relink of the build dir mid-run cannot hit
  later cards), early exits keep their log (`runs/bootlib/<name>.early-exit.log`) and are
  retried once. TEST-FIXTURES.md "bootcheck / run_from robustness".
- **Input labels** (lead): `src/host/host_input.c` / INPUT.md now say Cross = Confirm / Talk /
  Sword attack, Square = Gun / Sub-weapon, Circle = Cancel / Jump (retail-confirmed); test
  `input.action_aliases` updated.

### User play-test, 2026-10-18 (out/playtest/rg-game-1018.exe = build/battle-i686 09:59; native render/threads/audio/IOP, VU0 local, gamepad)

**Play-test lane checkpoint (2026-10-18, build/play-i686, scratch `out/play/`):**

- **Camera (symptom 1) = convention, not a bug.** Retail with default options (`+0x1A = 1`)
  swings the orbit camera right around the leader on stick right (view turns LEFT) and
  looks down on stick up; first person turns the view right. Retail measured on PCSX2 with
  the new stick injection (`tools/trace/stickprobe.py`, battle state `v23990`, RX = 255,
  `out/play/r3_cam.png`); the port's chain is byte-identical (SDL rightx+ -> 255 -> frame
  byte 4) and behaves the same (`out/play/fp/m.png` for first person). Fix: setting
  `input.camera_convention` = pc (default) / original (Original preset): orbit X and every
  camera's Y flipped for live input while that camera reads the stick (game hint
  `rg_host_set_camera_view` from the camera overrides' `rg_game_look_take` site, in
  `src/game/rg_game_main.c` look_apply). INPUT.md "Camera stick convention".
- **Walking on turns (symptom 2) = the port's stick conversion.** A round modern stick at
  full tilt on a diagonal gave bytes (206, 206) = 0.367 per axis after the game's decode,
  |mv| 0.52 = walk band (run needs 0.9); the old per-axis adapter ran only within ~17
  degrees of the axes (`out/play/stickmodel.py`). Port check from `--boot-save save2`
  (`out/play/sw.sh`, `dec2.py`): (206, 206) walks (A34 1, 1.2/tick), (255, 255) runs (A34 2,
  3.6/tick); with square bytes no reversal / 90 / 180-degree turn / 3-field blip leaves the
  run (the game logic and the ee-round-floor fix are fine). A DS2 reaches its corners
  (PCSX2's default AxisScale 1.33 compensates round pads the same way). Fix:
  `rg_stick_shape` (round dead zone + circle-to-square), setting `input.stick_ds2_range`
  (default on, Original on). INPUT.md "Stick range". Tests `input.stick_range`,
  `input.camera_convention`.
- **Stutter (symptom 3): measured, the cause is in the renderer lane (GS worker), not fixed
  here.** `RG_FIELD_TIMES` gained columns (RUNTIME.md) so every millisecond of a field is
  attributed. Windowed, `RG_GPU=hw`, host pacing, exe = build/play-i686 + the columns
  (`out/play/exeT*`), states from the fixtures / `play.py --save` (`out/play/st1T` 22,600 =
  before the battle, `st2T` 26,700 = before the win):
  - **Quiet PC:** 0 pacing resyncs in all runs; 60 phases/s. Battle start (22,600-23,400):
    14 of 400 frames over 33.3 ms (33-48 ms, 22,955-23,019). Battle end + results + Hooded
    Man + Salgin load (26,700-29,300): 28 of 1,300 frames over (33-43 ms). The first 3 frames
    after a scene starts cost 60-75 ms (cold renderer). In each, `gs_wait`/`sync` (the EE
    thread waiting for the GS worker) is 70-90% of the frame; EE game code, native audio
    (`audio` ~0.02 ms/field), the pump and native render submission are small. Salgin town
    (boot-save, 3,700-4,300) is the worst: ~40 ms/frame average with single fields of
    80-106 ms, all `sync`.
  - **Profile** (`tools/perf3d/rgprof.exe`, 2 ms, `out/play/prof1`, Salgin): main thread
    75% in `gs_async_drain` / `gs_async_wait_mark`; the GS worker thread: GS model 51%
    (`xfer_image_body` 16%, `gs_pixel_addr` 16%, `gs_read_pixel` 7%, `lz_blocks` 5%,
    `pages_of`, `gs_mem_materialize_rect_h`), D3D11 backend `nr_draw`/`kick` with driver
    time, `mirror_download` / `readback`, `make_target` / `rt_bind` / `rt_writeback` (render
    target creation) at scene starts. The spike fields (3,773 / 3,797 / 3,809 / 3,979 /
    4,177) are the same functions: **GS image transfers through the GS memory model and GPU
    read-backs on the worker**. **For the renderer lane** (src/ps2/gs, src/gpu): (1) the
    per-frame image transfer path (`xfer_image_body` -> `gs_pixel_addr` per pixel,
    `gs_read_pixel`) is the largest single cost in town and battle; a block/row-swizzle
    fast path or keeping these transfers on the GPU would remove most of the spikes;
    (2) `mirror_download` / `readback` stalls the worker on the GPU; (3) first-use
    render-target creation (`make_target`, `rt_bind`) and texture decode/upload at scene
    start (the 60-75 ms first frames) could be prewarmed or pooled.
  - **Under load** (the play-test PC was busy with agent builds; reproduced with two ctest
    -j2 runs beside a windowed run): pacing resyncs (debt > 4 phases dropped = visible
    jumps) and occasional single fields of 0.7-1.6 s whose time is entirely outside the
    emulation step: `out` (between fields, in rg-game's loop / OS scheduling; 822 ms at boot
    field 2,458) or not attributed (690 ms at 27,801, 1,563 ms at 28,963 in the old-column
    run). Not reproducible on a quiet PC (3 quiet runs, 0 such fields); consistent with the
    process being descheduled or paged under memory/CPU pressure. Retest on a quiet machine.
  - Pacing (src/native/threads rg_pace) behaves as designed (catch-up without presents,
    resync after 4 phases); no change made. Audio: the native engine's `pcm underruns`
    counter counts idle stream ports pushed ahead (ra_mix.c `pcm_block_done`), not audible
    gaps; host audio work is ~0.02 ms/field.
- **Verification:** build/play-i686 (RG_VU0_MODE=native) fixture set `68705b0f6340f05c`:
  route run hashes at all 8 milestones identical to build/battle-i686's set (the input
  changes do not touch scripted runs), `verify.py` 8/8; ctest `input|settings|host|runtime|
  kernel|spin|trace|prompts` 151/151, `fixtures|native_only` 8/8 (-j1).

- **Controller camera is reversed** (right stick turns the camera the opposite way the user expects). Not the
  mouse-camera override: CameraObjApplyInputMaybe only adds mouse yaw. Check (a) what retail does with the same
  stick input and the default camera options (options +0x1A bits 4/2 -> CameraSetAxisSigns_160470;
  CONTROLS-AUDIT.md section 6), (b) the port's pad adapter axis mapping (INPUT.md: v -> 128 + v*128/32767,
  input.invert_camera_x/_y), (c) the new native pad path (src/native/input/rg_npad.c). If retail's default is
  the same direction, it's a preference: offer input.invert_camera_x default/preset instead of a code change.
- **Movement bug** (one issue; user confirmed the "movement bug" IS this): **sometimes when turning, the character
  starts WALKING instead of running although the stick is fully deflected in the new direction**. Suspects: the
  2026-10-18 ee-round-floor fix area (AngleWrap_1cbf30 / turn controller / run-stop state), analog magnitude
  during a direction reversal (stick passing through the dead zone), or retail behaviour (check on PCSX2 with
  the same stick motion; PCSX2 can't replay sticks from input.py -> probe while driving a pad manually or add
  stick support to the harness).

- **Stutter at transitions** (2026-10-18 late: measured and partly fixed by the stutter lane, docs/PERF-3D.md "Transition stutter": host pacing batched up to 4 phases per present whenever a battle frame ran slightly over budget, fixed in rg_pace; the rest is the battle's steady GS-residue cost, proposals to the renderer lane): brief hitches when things load, when a battle starts and when it ends (the PC was
  also busy with agent builds/runs, so may be partly load). Measure on a quiet machine with RG_FIELD_TIMES around
  those milestones (fixtures: battle, battle_won; --boot-save). Suspects: native-render first-use work (mesh
  decode + hashing, texture decode/upload bursts, D3D11 shader/pipeline or state-object creation on first use),
  synchronous sound-stream ring reads inside the stream step (NATIVE-THREADS.md), bank loads in the native audio
  engine, paced-mode catch-up (max 4 phases then debt dropped -> visible jump). Fix = prewarm/async where possible.

### User play-test, 2026-10-13 (build/render-i686, windowed, RG_GPU=hw)

- **3D scenes run at about 1-2 fps.** Since the render fixes (RENDER-BRINGUP.md) the
  scenes draw real geometry and animate; the speed numbers in GPU.md / VU.md were taken
  on builds that drew little or no 3D, so they do not describe this. Profile the fixed
  scene windowed (fields ~7,400-16,000) before anything else perf-related. Release build
  (-O3), same configuration as clean-i686.
- **First battle: the controlled character repeats a "pushed back" animation** and the
  player cannot act. Probably the same divergence as the open battle-tutorial item
  (CharaCmdSetShipPos_22d430 moving the leader out of the battle circle every frame);
  check whether the wide-param / wide-arg / wide-local rules (PROTOS.md) are in the
  user's build and fix it. Not believed to be frame-rate related.
- Many other things work normally. Cutscenes can already be skipped from the Start menu
  (PLAN.md P6: no separate skip setting needed).

### 2026-10-13 (session 3)

New scripts in `out/bringup-checkpoint/`: `lsncmp.py` (align two records' CD reads),
`lsnname.py` (sector -> DATA*.HD6 file), `cdcmp.py` (CD-read bursts by ticks after the
FMV), `listings.py` / `lst.py` (pinned retail listings, cached), `refs.py`,
`rettype_review.py`, `rules_census.py`, `bf_layout_check.py` / `bf_verify_all.py`,
`vcall_v0_census.py`, `mk_insect_number_overrides.py`, `mk_usk_overrides.py`;
retired overrides in `retired-overrides/`; PCSX2 probe records in `pcsx2/`.

**MILESTONE (build 24, `run-s`): the golden NEW GAME run reaches the first battle.**
`gamemode 7` at port vbl 22,903 (retail 23,964), 7,791 main ticks after the FMV
(retail 7,758, +0.4 %); `mem_locked 0` 47 ticks later on both sides; no fault to
field 27,000 (`timing.py align --nowrap`: every milestone through the battle's unlock
matches, the differing tick counts are the CD-model / input-phase segments). The
CD-read streams (`lsncmp.py`) are equal from NORMAL's loading screen (71 reads) through
the FMV and the field (98, 33, 82 reads in a row with a few one-read reorders) to the
battle (retail vbl 24,132 / port 23,067). ctest **614 / 614** (the count includes
other lanes' new tests; this lane added `dialect.bitfields` + `_control` and the protos
fixture checks).

**Rendering regression found and fixed (coordinator report; build 29, `run-x`):** builds
19..28 drew no 3D in the field (the VU1 agent measured ~0.15 ms VU1/field instead of
12-24; screenshots `out/bringup-checkpoint/shots/`: same dialogue at field 8,290 in
every build, but the 3D geometry gone and the camera looking at the sky). Bisected by
disabling the new protos rules (`RG_PROTOS_NO_VCALL`, `RG_PROTOS_NO_STACKBLOCK` env
switches for ingest): the `stack-block` rule had built CameraBaseLookAt_15fae0's
side/dir block without its `up` row (written by inline VU0 code). Fixed by the rule's
coverage guard (PROTOS.md); the final build draws the pre-session scene again
(`shots/x8290.png`), GPU prims over the golden run 17.5 M. The field-22,900 MtxInverseAffine
fault the VU1 agent saw was the unaligned `f32 inv[16]` fixed in build 24. The timeline
is not shifted: the FMV ends at port vbl 7,321 in every build (retail 8,074) and the
CD-read stream after it equals retail's; fields 7,000..8,000 are the post-FMV dialogue
scene in both the old and new builds. Final build `run-x`: same battle milestones as
`run-s` (battle at vbl 22,903, unlock +47 ticks), no fault to field 27,000; no-input
title run 4,000 fields clean.

**Next divergence (open):** 60 ticks after the battle unlocks, retail pushes game mode
11 (the battle tutorial: TransporterWarpModeUpdate locks the scene, event
`ev01-0011`'s pack and `0x17bef4..` are read, the START presses at vbl 24,450..24,690
page through it, `gamemode_pop 11 -> 7` at 24,709). The port instead enters battle
phase 2100 after 53 ticks (BattleModeUpdate_280220: the leader is outside the battle
circle `D_00482200`/`D_00482210` -> `FieldHudBtlEscOpen_203d20`, the "escape?" window),
returns to phase 201 when the window resolves, and repeats (2100/201 every ~100 ticks)
to field 27,000; the tutorial never opens. Probed:
- The battle circle is identical (center (-2889.98, 22.95, -1906.4), radius 600; retail
  `pcsx2/btlarea.jsonl` watch 0x482200, port `run-t` `RG_STATUS_DUMP`). On both sides
  every enemy (0x80..0x85) has ObjRec flag 0x800000, so the leader-distance check runs
  on both (retail `pcsx2/btlloco.jsonl`: the leader stays at (-2880.7, 21.9, -1909.6)
  through vbl 24,099).
- In the port the leader is moved at battle+53 ticks to (~0, 1250, -750) by
  **CharaCmdSetShipPos_22d430** (a chara-script command, name table D_0044B7D0: the
  position transformed by area slot 1's matrix), called from the leader's command
  stream (`run-w`, `RG_BREAK` on every position setter with `RG_BREAK_FROM_VBL`). Retail
  never enters CharaCmdSetShipPos up to vbl 24,200 (`pcsx2/shippos.jsonl`). So the port
  runs a chara-script branch retail does not (a condition on state / flags, or a
  command looked up wrongly): next step, trace the script that issues it (the caller of
  CharaCmdSetShipPos and the condition before it) on both sides.

New `RG_BREAK` options (src/game/rg_game_main.c): `RG_BREAK_DUMPARG=K` dumps
`RG_BREAK_DUMP` bytes at stack word K instead of `[eax]` (break on a call instruction to
see an out-pointer argument); `RG_BREAK_FROM_VBL=V` ignores hits before game vbl V.

**Golden run past the FMV (build n, `RG_GPU=hw`, `RG_TIMING`):** private copy of the exe
in `out/bringup-checkpoint/run-o/bin`, own `--saves` dir, 26,000 fields requested.
No fault to field 19,000 (GameMode 11 throughout). Retail alignment
(`timing.py align --nowrap` + `out/bringup-checkpoint/cdcmp.py`, which pairs the CD-read
bursts after the FMV by main ticks since its `movie_shutdown`): the milestones match
through the FMV (port vbl 7,321 / retail 8,074: the port is 753 vbl ahead, the loading
screen and title being CD-model timed); after it the retail capture has no milestones
until the battle (scene scale locked: events), so the CD-read bursts are the flow
check. Bursts 0..22 pair one to one (same read counts, port 51 ticks earlier, the
input phase); burst 22 is the big area load (41 reads retail, 44 port; 165 vs 61 ticks,
the CD model is faster), after which the shift is ~238..285 ticks and the bursts keep
pairing with small split/merge differences (retail `2,4` vs port `2,2` ...) through
retail tick ~5,200 after the FMV (retail vbl ~18,800, port vbl ~17,100). No flow
divergence so far. Retail's battle (`gamemode_push 7`) is 7,759 ticks after the FMV;
the port should reach it near vbl ~22,300.

**First fault and the flow divergence behind it (build n, field ~20,000):** access
violation in `CharaGetWeaponId_2f5a50+0x8` <- `CharaGetEquippedWeapon_3acd40` <-
CharaRebuildEquipStats / CharaRecalcStats / CharaDeactivateEquipSlot /
CharaResetBattleVars <- GameDataBattleBegin_3e6930 <- BattleEncounterSetupMaybe_2f25f0
<- EvCmdBattleEncounterSetupMaybe_244a10 (the first battle's setup; port vbl ~20,150,
retail ~21,160). Two causes:
1. `this->slot374()` is CharaGetWeaponId_2f5a50(chara, slot) (vtable D_004722A0
   +0x374); retail passes CharaGetEquippedWeapon's own untouched `$a1` (the slot, from
   the slot-0x384 callers CharaGetEquippedWeaponSlot1_1f1f00 / `_e1`: 1 / 0); the C
   declared no such parameter. Fixed by the protos rule **`vcall-widen`** (PROTOS.md).
2. **Flow divergence found with the CD-read stream** (`lsncmp.py`: the
   `sceCdRead` lsn/sector sequences of both records, sequence-aligned; `lsnname.py`
   names a sector from the DATA*.HD6 index): in NORMAL's loading screen retail reads
   the party leader's resources (`chara\pc\c001_base1/skin1.chr`, weapons, `c001.stb`,
   `ch_001.snd`, effects) and the `map\m01\m01_test03` packs; the port read none of them,
   loaded c001 lazily at vbl 11,035 and again in the battle setup, where retail loads
   the `ev01-0020` event. PCSX2 probes (`pcsx2/leader.jsonl`, `wdcmd.jsonl`,
   `cfgvm.jsonl`, `cfgrun.jsonl`): after NewGamePartyInitMaybe_3e74f0 retail runs the
   world-data table's CfgVm commands (`WorldDataCmdSetPartyMember_3b9b00` adds members 0
   and 8; leader `party+0x18E` 0xFFFF -> 0); the port ran the same commands, but
   SetPartyMember returned at once: its guard `g->f2` is bit 2 of the byte at +0x9A
   (`lbu 0x9A; dsll32 29; dsrl32 31`), and `u8 pad98[2]; u64 f0:1, f1:1, f2:1;` puts
   the bits at +0xA0 under clang's MSVC bitfield layout. So PartySyncCharaRes saw leader
   -1 and loaded nothing. Fixed by the dialect rule **`bitfield-gcc`** (PROTOS.md):
   every bitfield record in the corpus now has mwcc's layout (807 files checked with
   `bf_verify_all.py`: clang `-fdump-record-layouts` of i686-windows-msvc vs
   mipsel-linux-gnu, 0 records differ; before: 5 records, among them the data-table
   entry defines and the OSD config).

**After the two fixes (builds 21/22):** NORMAL's loading screen now issues the same 71
CD reads as retail in a row (`lsncmp.py`: retail vbl 2,635..3,867 = port 2,109..3,143:
party leader resources and the m01 packs included), then 60 equal reads after the FMV.
Two latent bugs on code paths the party now reaches:
- NavGraphInit_310ec0 -> UskMemoryAlloc_42dae0 faulted reading address 0x3380 (the
  size): the decomp's static inline search helpers call DListGetHead/Tail with no
  argument and protos' `missing-passthrough` filled in the helper's own parameter; mwcc
  inlined them and retail's `$a0` is the allocator's untouched heap. Overrides
  UskMemoryAlloc_42dae0 / UskMemoryLeaseBegin_42d740 (`mk_usk_overrides.py`). Census
  of missing-passthrough inside listing-less helpers: 10 rows in 8 files (Notify,
  Pool_Alloc, mgrEnt, findA/findB/findLargest, three `_e1` entries): see Next steps.
- PointInOrientedBox_1c8430 -> MtxInverseAffine_1cb640 `movaps` into `f32 inv[16]`
  (field function points, TaskStepFuncPoint_200190): the dialect rule that 16-aligns
  block-scope arrays only matched indented declarations; the file is one line. It now
  also matches a declaration right after `{` / `;` (8 more arrays).

**Retail alignment until the fault (build n):** the CD-read streams are equal (66 then
31, 33, 41 reads in a row, small reorders) from the end of the FMV to retail vbl
21,153 / port 20,153, apart from the c001 loads above.

**Next steps (session 3):**
1. The CharaCmdSetShipPos divergence above (battle tutorial never opens).
   Session 4 (interrupted) found the cause and added the `wide-param` / `wide-arg` /
   `wide-local` protos rules (PROTOS.md "Rules added 2026-10-13"; `game/` is staged with
   them, `ctest -L protos` passes, the build compiles). Not yet confirmed by a golden run
   through the battle start.
2. `info-vcall-set-args` (41 rows in `vcall-rules-census.tsv`): retail passes further
   computed argument registers to a virtual the C calls with fewer; most are dead
   leftovers, review the ones whose slot target reads them.
3. `vcall-widen` is broad (254 definitions, def-widen 365 -> 735): it adds parameters
   wherever an untouched incoming register reaches a jalr; narrowing it to slots whose
   targets read the register needs the vtable data (slot -> candidate definitions).
4. missing-passthrough inside listing-less static inline helpers (10 rows, 8 files):
   only the USK allocators were wrong (overridden); a stage rule should resolve a helper's
   missing register at its inlined call site.
5. 157 -> 20 bitfield runs are left unrewritten by `bitfield-gcc` (start offset unknown
   or no unit assignment); `bf_verify_all.py` shows none of them differs today, but
   rerun it after a snapshot bump.
6. `insect_InsectPiecePlayMotion_5145e0` `%02d` (`$a3`): PCSX2 probe.

**-Wreturn-type review (task 3):** `out/bringup-checkpoint/returntype-review.tsv`
(helpers `rettype_review.py`, `refs.py`). For each of the 19 sites retail's `$v0` at
`jr $31` is the last call's result on each path (asmflow terms), and **no reader
consumes it**: statement calls, dead locals (`r0`/`r5`/`r10`/`rv6` assigned and never
read), task-table entries (`TaskTableRun_1f5340` calls them as void), a debug-menu
vtable. No change needed; the one C++ site (EvRemoveChrMonographs_2e9060) is defined
by `-fno-strict-return` (cmake/game.cmake).

**Insect printf sites (task 3):**
- `insect_InsectBattleDrawNumberRec_4f1490` (`"%d"`, no argument): retail passes its
  entry `$a2`, untouched, to Sprintf; its caller `insect_InsectBattleRematchPromptDraw_4f14e0`
  loads `$a2` with i / a / b / c / e (listing 0x4F1604..0x4F16A0) before the five
  calls, values the C computes and never passes. **Fixed** with two overrides
  (`mk_insect_number_overrides.py`): the definition takes `s32 n`, the caller passes
  the five numbers.
- `insect_InsectPiecePlayMotion_5145e0` (`"%s%02d"` = D_005252D8 with `*p`): the `%02d`
  reads `$a3`, which the listing never sets: at that call it is whatever
  `Sprintf_1343b8` -> `VfprintfR_1374e0` left in `$7` (the preceding call on that path).
  Not spellable from the listing; i686 reads the next stack slot (an int, no fault).
  Left open: needs a PCSX2 probe of `$a3` at 0x5146F4 (only for piece type 0x10, id 0).

### 2026-10-12 (session 2)

**Recovered.** Ingest re-run: 0 files written, 0 problems. `build/clean-i686` rebuilt,
rg-game links (0 undefined / 0 duplicate). The 7 asm-only functions were already
integrated (UNBOUND.tsv 98 rows, missing/README.md, LINK.md, UNBOUND-TRIAGE.md updated
by the previous agent). The literal-newline string in `src/game/rg_game_main.c` is gone
(cause found: the agent shell tool drops one level of backslash escaping, so a `"\\n"`
in an inline python edit script lands in the C file as a real newline; edit C string
escapes with the editor tool, not inline scripts).

**Diagnostics added.** `RG_BREAK_DUMP=N` (hex-dumps N bytes at `[eax]` on each
`RG_BREAK` hit: put the break on a call's return address to see the returned object);
`RG_STATUS_DUMP=pRVA/O1/..+OFF:size` now prints `NULL` instead of faulting while the
pointer chain is not set up. `tools/trace/probe.py --fn NAME:ADDR[:ret][:w=ITEMS]`:
ITEMS fill the record's six `d` words (`aN`, `aN+OFF+OFF..`, `@ADDR+OFF..`).

**Blocker root cause (STEP 2): found.** NORMAL's loading screen never ends because the
main thread loops forever in `MapLoadFromGameDataAndWait_2f4920` (thread 1 waits in
`DelayThread` from +0xC5; `MapLoadIsSettledMaybe_1e4e10` -> `MapDataIsLoaded` = 0 for
area slot 0, 492k polls). The map manager's area ids are all -1: the party's area
(`party+6`) and sky (`party+8`) were never set because `PartySetAreaMaybe_3cab50(party,
2, 1, 0)` finds no sub-area: every planet-area view node has `x4 == NULL`. The nodes'
ids are linked by `WorldSubsysLinkIds_4155c0` through `DataTableFindByKey` on the
`area_param.cfg.bin` table, which is **empty** on the port (retail: 143 entries, PCSX2
probe at vbl 308). The table did parse (143 entries at vbl 20) and is then **cleared at
vbl 45** by `DataTableLoadResidentBin_368d00` (resident read fails -> `Clear`), called
from `DataTableViewGetAtThunk_4198a0` (+3 siblings). Retail's thunk is `j func_00418BB0;
addiu $4,$4,-0x88` (view GetAt: `this-0x88`, entry `i`), but the port called
`func_00418AB0_e1` (0x418AC0 = a `jr *0x10(vptr)` stub -> vtable slot 0x10 =
LoadResidentBin). Cause: protos `addr-alias` names the k-th `alabel` of a listing
`_e<k>`; ContainerViewGetAtFwd_418ab0's C (and data2c.json `function_entries`) number
every 16-byte stub (e1..e15 = 0x418AC0..0x418BA0), so its one alabel 0x418BB0 is `_e16`.
**Fix (stage rule, protos):** `_entry_ordinal` takes data2c's `function_entries` as
ground truth and gives the alabels it does not cover the remaining defined `k` in
address order; `_name_addr` (def-vthunk-naked) uses the same mapping and reads an
unlabelled entry's listing from its instruction line, so the 15 stubs become naked
vtable forwarders too.

Repro of the finding (exe/map RVAs change per build: recompute with maprva/callsites):
```
RG_DATA=data RG_STATUS_EVERY=1 RG_STATUS_DUMP=p<RVA D_00483894>/0x34/0x8+0x70:0x20 rg-game.exe --headless --fields 90
   -> +0x7C (count) 0x8F at vbl 45, 0 at vbl 46
RG_BREAK=<RVA DataTableLoadResidentBin_368d00> -> callers DataTableViewGetAtThunk_*+0xf
probe.py --fn LinkIds4155c0:0x4155c0:w=a1+0x34+0x8+0x7c --stop-vbl 700   (retail count 0x8f)
```

**STEP 1 (in progress, same ingest):** override `MtxMulAffine_13d1d0` (UNBOUND row
removed); datareloc `fn-number` (EntryPad_100000 / func_00200000 -> 0x100000 / 0x200000
everywhere but D_0047D130; MpegNextPictureMaybe_110008 -> 0x00110008 in D_00450480;
audit `fnword_audit.py`: no other layout word hits a function); protos `text-alias`
(D_002931A0 -> UiTextElemInit_2931a0, data declaration dropped); protos
`def-bare-return` for `((C *)p)->vN(..); return;` when vN is a value-returning virtual.

**Result of the e16 fix (build c):** the area table keeps its 143 entries; the party's
area is set (`PartySetAreaMaybe` finds the sub-area, MapLoad sets slot 0 area 100, sky
100) and the port issues the same 28 CD reads as retail up to lsn 1170412. The loading
screen still does not end: the area load of slot 0 fails at vbl 2181 (slot state -1,
`MapAreaLoadUpdate_1d9300` case 21). Cause: `MapAreaDataIsLoadDone_1e8ba0` returns `u8`
(`sete al`), but the C++ caller declares it `s32` and reads all of EAX (0x067A0E00 ->
"done" while the area data was still in state 13), then `IsLoadOk` = 0 -> failure.
**Fix (stage rule, protos `ret-narrow`):** a call whose definition returns
u8/s8/u16/s16/bool while the caller's view is a full int gets its result cast to the
definition's type (the EE extends every result into the register; i686 leaves EAX's
upper bits undefined).

**Varargs (coordinator request, sound agent's finding):** protos rule `vararg-narrow`:
for a variadic definition whose every `va_arg(ap, T)` reads one 4-byte-or-less integer
type, a call's variadic argument that is 64-bit (parameter/local/cast/call result typed
s64/u64) is cast to T. On the EE each vararg is one 64-bit slot; on i686 an s64 takes
two slots and shifts every later read. Census: 6 arguments at 2 sites,
SoundSendKeyOn_1b80c0 and SoundPlayEntryKeyOn_1b81e0 -> SoundSendCmd_1b6cc0 (velocity,
pan, bend). Double arguments to an int va_arg would be logged `info-vararg-wide` (none).

**Frame-time feedback (STEP 2b): fixed** in src/ps2/dmac/dmac.c: a VIF i-bit interrupt
raised inside a DMA kick is posted one cycle after the kick has been charged (DMAC.md
"VIF interrupts"). Before, `Vif1IntcHandler_15e170` ran inside `GfxEndFrame_141c20`'s
`Vif1DmaStart` (before `T0 = 0`), so its T0 sample was the whole interval: perf meter
t0 = 1.34 % / t1 = 100.19 % of the interval, `+0xF10` = 2.0038. Test
`dmac.dstat_interrupts` updated (handler runs after the kick once time advances).

**Build e (ret-narrow + devirt lane rule):** the area load completes, MapLoad returns,
and GameSessionInit runs its 15 warm-up ticks. Two faults found and fixed on the way:
- `VecSub_13be40(NULL)` in `CameraBaseLookAt_15fae0` via `CameraBaseApplyLookAt_15fa80`:
  `self->slot20(f32 t, &at, &eye)` (camera_cpp.h) dispatches to `CameraBaseLookAt(c,
  eye, at, f32 roll)`. On the EE the float rides `$f12` and order across lanes is free;
  on i686 it is positional. **Fix (stage rule, devirt):** a slot call passes the GPR
  arguments first and the f32 ones after them (`lane_reordered`, 6 slots: camera 0x20,
  Chara 0x2BC x2, EffObj 0x1C, EventCast 0x34, SceneObj 0x34). Census
  `out/bringup-checkpoint/vt_lane_census.py`: no table-referenced definition puts an f32
  before a GPR parameter, so this order matches every target.
- The main thread then waits in GameSessionInit for `LoadingScreenIsFinished` (state 7):
  state 5 needs `cur == n` (12 text lines), but `cur` never advanced because
  `LoadingScreenResetEntriesMaybe_343140` writes `*(s32 *)&D_004E898C = 1` through an
  `extern const s32 D_004E898C;` declaration and **clang deleted the store** (a store to
  a const object is UB). **Fix (stage rule, dialect `const-data`):** `const` is dropped
  from extern declarations of data2c objects (`D_xxxxxxxx`, overlay-prefixed, `data2c_*`;
  1,735 declarations); every data object is writable on the port already.

**Varargs census follow-ups (docs/VARARGS-CENSUS.md, coordinator):**
- `vararg-missing` (protos): a printf-family call (Sprintf_1343b8, Fprintf_12f9a0,
  DbgPrintf_15e780) whose format (literal or a MAIN `char D_x[]`) reads more arguments
  than passed gets the registers retail passed: a spellable reaching value, or the
  enclosing function's own parameter when the listing shows the register is its entry
  value and the C never assigns it. The call goes through an unprototyped (C) /
  `(...)` (C++) function type, so the fixed-arity local view does not reject or convert
  the arguments. EvMonographChrName_2e93f0 / EvMonographFncName_2e93a0 ->
  `Sprintf(a1, fmt, a2, a3)`. Otherwise `manual-vararg-missing` is logged.
- `vararg-narrow` for views: a fixed-arity local view with 8-byte parameters at variadic
  positions read by a 4-byte conversion: the argument is cast to int and the call goes
  through the variadic type (TaskEntryFormatStatus_208a90, `" [%c][%c]%s"`).
- Open: `insect_InsectBattleDrawNumberRec_4f1490` (`"%d"` with no argument) and
  `insect_InsectPiecePlayMotion_5145e0` (`"%s%02d"` with one): overlay formats are not
  resolved by the rule; check against the retail listing. SoundIop packet tails (19
  sites) read past the arguments: harmless unless the IOP HLE reads those words.

**MILESTONE (build g, 2026-10-12 evening): the NEW GAME golden run leaves NORMAL's
loading screen.** GameMode 11 at field ~3,500 (vbl <= 3,463; retail vbl 3,865), the
opening FMV plays (movie frames 176 at field 3,500, 1,924 at field 7,000). No-input title
run: unchanged (4,000 fields, title menu, no fault). Also in build g:
- **Frame-time feedback verified:** title run, `+0xF10` = 2.0 (the interval) at field
  700; perf meter t0 1.3 %, t1 0 (was 100.19 %).
- protos placeholder rule (`u`/`uN` never assigned) now also matches pointer locals
  (`void *u;`): `NodeObjBasicDrawModel_196b10` passed an uninitialised `u` to
  `NodeCalcWorldMatrix_186130` (retail: the untouched entry `$a0` = arg0) and faulted
  in the first map draw.

**Next fault (open):** golden run, field ~7,000+ (during or right after the FMV): access
violation reading 0xFFFFFFFF in `TriCalcBounds_1cb540+0x5c6` <- `CollSweepTri_1c7790`
<- `CollRaycastNearest_1c86e0` <- `MapDataCollectCollTrisMaybe_1e6c80` <-
`MapAreaTreeCollectCollTrisNearMaybe_1dac30` <- `TaskCharaInfo_1f9c70`.
Repro: `sh out/bringup-checkpoint/regress.sh <exe> <outdir> 8000`; resolve the crash's
stack words with `out/bringup-checkpoint/rva.py <map>`.

Build note: a windowed `build/clean-i686/rg-game.exe` started by someone else held the
exe; `out/bringup-checkpoint/link_alt.ps1` relinks into `rg-game-alt.exe`.

**Field after the FMV (builds h..j):**
- `CollRaycastNearest_1c86e0` / `CollRaycastNearestHit_1c8ad0` (overrides): the point,
  direction and Ray locals are one retail stack block (sp+0x90/+0xA0/+0xB0);
  `CollSweepTri_1c7790(&point, ..)` reads the Ray at point+0x50/+0x60. Now one struct.
- `CollSweepTri_1c7790` (override): `f32 mn[3], mx[3]` receive 16-byte stores from
  `TriCalcBounds_1cb540` (retail: two 16-byte slots); were 12-byte unaligned arrays ->
  stack overrun, fault reading 0xFFFFFFFF.
- `ModelMeshGetGroupPktsMaybe_15b150` (override): mesh vtable slot 0x18, called as
  `cur += m->v18(cur, ..)` by ModelQueueSortedPackets_14f0d0. Retail forwards `$a1` to
  the slot-0x28 virtual (ModelMeshBuildUnpackPktMaybe_15b2a0) and returns its `$v0`;
  the C (`p0->v8(); .. ` in a void function) dropped both -> packet cursor advanced by
  garbage. **Class to automate next:** member calls that forward argument registers and
  whose `$v0` survives to the function's return (a protos/devirt rule like
  def-vthunk-naked, for non-tail vcalls; read the listing: `jalr` with `$a1..$a3`
  untouched since entry, `$v0` not written after it).

**Builds k..m:** five more L5 overrides, each hit in turn by the golden run in the
field after the FMV (AabbProjectScreenBounds_13c4f0, GsPktSetXYZPixelVec_13ef70,
GsPktSetSTVec_13ecc0, VecFtoi4_13e2e0, GsPktAddDmaCallTag_13f1f0; the CALL tag carries
the host address like every other tag, PS2_PHYS is the identity). UNBOUND.tsv: 89 rows,
no `l5-no-override` left. Build l ran the golden input past field 10,500 (GameMode 11,
in the field after the FMV) without a fault; the run is slow there (~500 fields per
several minutes).
- protos `def-fallthrough-return`: a value definition that falls off its end right after
  `G(..);` returns G's value (retail `$v0`), when G returns the definition's class and
  def-tail-return does not already own it. -Wreturn-type census
  (`out/bringup-checkpoint/returntype_census.py`, `returntype-census.tsv`): 20 sites in
  the game C (17 "does not return a value", 3 "not in all control paths": NavMgr,
  Camera*Mode*, Minimap*View, PlayTimeGet, EvTargetPointInVolumes, ...); 1 matched the
  rule (EvTargetPointInVolumes_3527a0); the rest end in a void call or an assignment
  (retail returns a stale `$v0`) and are listed for review.
- tools/devirt_verify.py: units with protos `def-vthunk-naked` forwarders count as thunk
  units (their `jmp *S(%eax)` sites are compared), so the e16/stub fix does not read as
  139 "port-fewer" disagreements.
- ctest (build m): **471 / 471 pass**.

### Next steps

1. Run the golden input further (the battle is at retail vbl ~23,964): find the next
   fault or flow divergence; `timing.py align --nowrap` against
   `out/timing/port/golden_newgame_battle2.*` now that the loading screen ends.
2. Automate the vcall argument / `$v0` passthrough class (ModelMeshGetGroupPkts) and the
   split-local stack-block class (CollRaycastNearest*) with listing-driven stage rules
   instead of overrides; census both.
3. Review the 19 remaining -Wreturn-type sites and the 2 insect printf sites.
4. Field-run speed (the headless run slows to a few fields per second in the field).

**Build n (final state of session 2):** build l's golden run hit an `int3` at field
~11,500 in `VecWrapAngle_1cbe90+0x1` (<- MapNodeMoveStep_2fa4a0 <- MapSequencerUpdate):
`f32 *c; if (c) {..}` before c is set (a mwcc register-steering idiom) is a branch on an
uninitialised value, which clang lowers to `unreachable`. **Fix (build flag):**
`-ftrivial-auto-var-init=zero` for all game C/C++ (cmake/game.cmake), which makes the
whole class defined. Results: ctest **472 / 472**; ingest second run 0 files written,
`--check` 0 problems (113 overrides); no-input title run 4,000 fields clean (title menu);
**golden NEW GAME run 14,000 fields with no fault**: NORMAL loads, GameMode 11 by
field 3,500, the opening FMV plays (fields ~3,300..7,400), then the field/event flow
runs on (GameMode 11) to field 14,000. Not yet compared with retail past the FMV.
