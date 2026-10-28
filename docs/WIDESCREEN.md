# Widescreen, stage 0: the game's WIDE mode as a setting

PLAN.md P6 "Aspect ratio", stage 0 of docs/WIDESCREEN-AUDIT.md "Plan". Build tree
`build/wide-i686`; scratch, scripts and screenshots in `out/wide/` (game imagery, never
committed).

## What it does

`graphics.aspect = 16:9` turns on the game's own hidden 16:9 mode (`D_00481638 = 1`, the
variable behind `SetAspectMode_1c6a90` / `GetAspectMode_1c6aa0` / `IsWidescreen_1c6ab0`) and
shows the 512x448 frame on a 16:9 canvas. In game that means (audit sections 1-3):

- **3D:** `SceneCameraApplyAspect_1c6a10` sets the projection aspect to 0.5625 instead of
  0.75: Hor+, vertical framing kept, the horizontal field of view goes from 52 to 66 degrees.
  Frustum culling widens with it (`ViewSetPerspective_1564a0`).
- **2D drawn by the 12 WIDE-aware sites** (`GsDrawSpriteCentered/AnchorBR/AnchorBL`,
  `DrawRotatedQuad`, HP gauges, minimap entries, target slots, attack chain, lens flare,
  door cursors) is narrowed to 0.75 of its width, so on the 16:9 canvas it has its
  original proportions. Positions are W-relative, so corner HUD stays in its corners.
- **Everything else 2D** (menus, the battle menu in the NORMAL overlay, fonts, message
  windows, the compass) is not WIDE-aware and is shown stretched by 4/3, exactly as the PS2
  showed it on a 16:9 TV. That is stage 1/2 work (the renderer-side layout transform).

Two whole screens are not WIDE-aware at all, so instead of retail's stretch the port shows
them **4:3, pillarboxed inside the 16:9 canvas**, and clears the flag while they are up so
nothing on them is narrowed:

| Screen | Detected by | Shown |
| --- | --- | --- |
| Title (logo movie, menu) | TITLE overlay loaded (`D_0047E254 == 2`) | 4:3 pillarbox, flag 0 |
| Movies (opening FMV, ...) | the movie service has a movie open (`rg_movie_g_size` non-zero) | `graphics.movie_aspect = keep` (default): 4:3 pillarbox, flag 0; `stretch`: 16:9, flag 1 (retail) |
| Everything else | | 16:9, flag 1 |

**4:3 (the Original preset and the default) never writes the flag**, so the game runs
exactly as before; after a live switch from 16:9 back to 4:3 the flag is written to 0 once.

## Settings

| Id | Values (default; Original) | Flags |
| --- | --- | --- |
| `graphics.aspect` | `4:3` "4:3 (original)", `16:9`; stage 1: `16:10`, `21:9` "21:9 (ultrawide)", `auto` "Match the window" (4:3; 4:3) | display (menu trial, reverts in 15 s unless kept); live |
| `graphics.movie_aspect` | `keep` "Keep 4:3 (pillarbox)", `stretch` "Stretch to the screen" (keep; keep) | live; only matters at 16:9 |

Both were P6 placeholders; at stage 0 `graphics.aspect` lost its `16:10`, `21:9` and `auto` values (back in stage 1)
(they need stage 1; a file that names one falls back to 4:3 with a warning). For a 16:9
window use e.g. `--set display.width=1280 --set display.height=720` or a fullscreen mode;
the default 1280x960 window letterboxes the 16:9 canvas.

```
rg-game --set graphics.aspect=16:9 --set display.width=1280 --set display.height=720
rg-game --set graphics.aspect=16:9 --set graphics.movie_aspect=stretch   # retail WIDE look
```

## Code

| File | What |
| --- | --- |
| `src/settings/rg_aspect.[ch]` (new) | The policy, pure: settings + (title?, movie open?) -> flag write (-1 / 0 / 1), canvas aspect, frame aspect inside the canvas |
| `src/settings/rg_settings_core.c` | `graphics.aspect` (4:3 / 16:9, display) and `graphics.movie_aspect` made real |
| `src/game/rg_game_main.c` | `aspect_apply()` before every field (no guest code runs then): the policy, the flag write, `rg_host_set_aspect`; `--shot FIELD:PNG` (repeatable) writes the native display and `-view.png`, the picture as presented |
| `src/host/host_scale.c` | `rg_fit_rect_content` (canvas fit + the frame's shape inside it), `rg_present_image` (headless "as presented" picture: canvas at the source height, horizontal linear resample, black bars) |
| `src/host/host_sdl.c`, `host.h` | `rg_host_set_aspect` / `rg_host_get_aspect` / `rg_host_fit`; `rg_host_present` uses `rg_host_fit` (identical to the old 4:3 `rg_fit_rect` until an aspect is set) |
| `src/runtime/runtime.c`, `rg_runtime.h` | `gfx_frame` takes the rectangle from `rg_host_fit` (was a 4:3 literal) and, on a non-4:3 canvas, lets "match window" internal resolution reach the canvas *width* too (512 columns stretched to 16:9 need ~1.5x the factor of the 448 rows); computed from the canvas, so a pillarboxed movie keeps the field's factor. `rg_runtime_read_display` (pixels for `--shot`) |

No `src/gpu`, `game/`, `tools/` or override file changed; no new override was needed
(the flag is a plain MAIN `.bss` word the host writes between fields).

## Revisions to the audit's stage 0

1. **The flag is written before every field, not once "after boot".** `SysCfgTvModeCmd_1c2b10`
   (boot config) can write it, and `SceneCameraApplyAspect_1c6a10` resets anything that is
   not 1 to 0. A per-field write between fields is idempotent, needs no override, and makes
   the setting live (menu trial, revert). 4:3 never writes it.
2. **Title and movies are pillarboxed, not stretched.** The audit's stage 0 was "retail
   WIDE, the host presents 16:9". Retail stretched the title and every movie. Both are
   whole screens with no WIDE-aware element, so the CENTER class can be applied to the
   whole frame on the host side (4:3 frame inside the 16:9 canvas, flag 0) without the
   stage 2 marker packets. In-game menus are *not* treated this way: they are drawn over
   the live (widened) 3D scene or over a screen capture of it, so pillarboxing them would
   squeeze the scene; they wait for stage 2.
3. **Internal resolution follows the canvas width.** At 16:9 "match window" picks its
   factor from the canvas width as well as the height (the audit put per-axis scaling in
   stage 3; this is the cheap uniform version of it). 4:3 is unchanged.
4. **Setting id:** the existing placeholder `graphics.aspect` (not a new `display.aspect`),
   cut to the two values stage 0 can honour.
5. **PCSX2 reference not taken.** The audit's ground-truth check (PCSX2 with
   `D_00481638 = 1`, frame for frame) is still open; it is a separate run with the retail
   harness (`tools/trace`). Only the in-game 3D/HUD frames are comparable; the title and
   movie frames differ by design (flag 0 there).

## Verification

Runs: golden input (`tools/trace/goldens/newgame_battle.input.txt`), headless, unthrottled,
`RG_GPU=hw`, 25,000 fields (title, NEW GAME, story screen, opening FMV ~3,200-7,300, the
Rosa event scenes, the first battle from ~22,900). Scripts in `out/wide/scripts/`
(`build.cmd`, `run.sh NAME EXE FIELDS [args]`), runs in `out/wide/runs/`.

**Original is unchanged.** "Before" = `out/wide/base/rg-game.exe`: the same game objects
and the libraries built before any change, linked with the pre-change `rg_game_main.c`
(reconstructed: `out/wide/scripts/make_orig_main.py`, `out/wide/base/build_base.cmd`).
"After" = `build/wide-i686/rg-game.exe`. Both `--preset original`, `RG_GS_DUMP_FIELDS`
1500, 7100, 8000, 8290, 12000, 20000, 23000, 23600, 24500:

| Compared | Result |
| --- | --- |
| displayed frame (`fNNNNN_display.png`) at all 9 fields | byte-identical |
| local memory read-out (`fNNNNN_local.png`) at all 9 fields | byte-identical |
| GS registers + CLUT (`fNNNNN.regs`) at all 9 fields | byte-identical |
| the 50 `RG_STATUS_EVERY=500` lines (vbl, overlay, sysmode, game mode, movie frames) | identical |
| `--shot` native PNGs of an after-run vs the before-run dumps | byte-identical |

(`src/gpu` was rebuilt between the two builds by the perf lane's concurrent work: the
after-run reports far fewer GPU batches; the output is identical regardless.)

**16:9** (`--preset original --set graphics.aspect=16:9`):

- the 50 status lines are identical to the Original run (same flow, same battle timing);
- title (1500), story screen (3000) and movie frames (4000, 7100) are the *same native
  frames* as Original (flag 0 on the title and in movies; the story screen is NORMAL
  overlay 2D, which never reads the flag); title and movies are presented pillarboxed;
- from the first 3D scene (8000) the native frames differ: wider Hor+ view, characters in
  proportion on the 16:9 canvas, nothing missing at the frame edges in these scenes;
  subtitles, the battle party HUD, the pause/escape menu and the minimap frame are
  stretched (expected: not WIDE-aware); minimap markers and the target cursor are narrowed
  (WIDE-aware);
- windowed (`--set display.width=1280 --set display.height=720`, `RG_WINDOW_SHOT`): the
  story screen fills the 1280x720 window, the FMV is a 960x720 pillarbox; internal
  resolution "match window" chose 3x (2x before, from the height alone) and did not change
  when the movie started.

Screenshots (`out/wide/shots/`, `-4x3` = Original as presented at 597x448, `-16x9` =
graphics.aspect 16:9 as presented at 796x448, `-native` = the 512x448 frame):
`01-title-f1500-*`, `02-fmv-f4000-*` (`-keep` pillarbox, `-stretch` retail),
`03-fmv-f7100-*`, `04-story-f3000-*`, `05-field-f8000/f8290/f12000-*`,
`06-battle-f23000/f23600/f24500-*`, `07-window-*-16x9-1280x720` (the real SDL presenter).

**Tests** (`ctest -L wide`, also in `-L host` / `-L settings`):

| Test | Checks |
| --- | --- |
| `host.wide_fit` | `rg_fit_rect_content`: 16:9 canvas, 4:3 pillarbox (linear, nearest, integer = the old 4:3 integer rectangle, stretch proportion), letterbox of a wider frame, degenerate; sweep: 4:3 and "content = canvas" are `rg_fit_rect` exactly, the pillarbox is inside the canvas, centred, 4:3 |
| `host.wide_present` | `rg_present_image`: identity at square pixels, 597 / 796 widths, monotonic ramp with exact end values, the 4:3-in-16:9 middle equals the 4:3 image and the bars are black, too-small buffer, NULL |
| `host.wide_present_control` (`WILL_FAIL`) | an unpillarboxed frame must fail the bar check (the check is armed) |
| `host.wide_host` | a headless host starts at 4:3 and `rg_host_fit` equals the old 4:3 `rg_fit_rect` in every mode (sweep); set/get aspect, the post-chain frame lands in the same rectangle, reset on bad values, headless present keeps the frame |
| `settings.wide_policy` | 4:3 never writes the flag (64 screen states); 16:9 field / title / movie keep / movie stretch / title wins; the one undo write after a live switch back; through the registry: enum names and flags, `--set`, the Original preset (4:3 / keep, `matches_preset`), a file value `21:9` falls back to 4:3 |

`settings.core_defs` now expects `graphics.aspect` / `movie_aspect` to be real (not
placeholders).

## Known issues

- Menus, the battle menu (NORMAL overlay), fonts, message windows, captions and the
  compass are stretched by 4/3 at 16:9 (retail behaviour; stage 2 layout transform).
- `CompassHudRender_370fb0`, `DrawModelWithCamera_28bf80` (menu model previews) and the
  session-init projections keep aspect 0.75 (stretched 3D in those places). Fixed in
  stage 1 (below).
- Screen-space logic that uses the projection (screen markers, door-cursor fades,
  aim-offscreen; audit section 6) sees the wider view: presentation state, but a
  state-trace comparison across aspects must exclude it.
- Detection lag: the screen state is sampled before each field, so the switch into or out
  of a pillarboxed movie happens one field late (on a black or fading frame in practice).
- The headless `-view.png` resample is a plain horizontal linear filter at 448 lines; the
  window uses SDL's (or the GPU post chain's) filter at the window size.

## Stage 1: any aspect (overrides)

Done 2026-10-17. Build tree `build/wide-i686`; scratch, runs and screenshots in
`out/wide/stage1/` (game imagery, never committed); reusable scripts in `tools/wide/`.

### What it does

`graphics.aspect` has its other values back: `4:3`, `16:9`, `16:10`, `21:9` (64:27, i.e.
2560x1080) and `auto` (the window's shape: `rg_host_window_size`, or `display.width` x
`display.height` headless; clamped to 4:3..32:9; within 1% of 4:3 counts as 4:3). Every
wide shape uses the stage 0 mechanism (the game's WIDE flag, the anamorphic 512x448 frame
on a canvas of that shape, title and kept movies 4:3 pillarboxed with the flag cleared);
what stage 1 adds is that the values the game derives from the flag follow the canvas:

- `rg_aspect_d()` = den/num of the frame shape (0.75 at 4:3, 0.5625 at 16:9, 0.625 at
  16:10, 0.4219 at 64:27): the projection aspect. Hor+: horizontal FOV 52 / 66 / 61 / 82
  degrees at 4:3 / 16:9 / 16:10 / 21:9 for the default 40.2 degree vertical.
- `rg_hud_xscale()` = (4/3) / (num/den) (1 / 0.75 / 0.833 / 0.5625): replaces the 0.75
  width factor of the WIDE-aware 2D, so those elements keep their proportions on any canvas.

Both are computed once per field (`rg_aspect_set_current`, called from `aspect_apply` in
`rg_game_main.c`, between fields) into static floats, as exact float quotients of small
integers, so 16:9 gives exactly retail's 0.5625f / 0.75f. **While our policy does not own
the flag** (4:3, title, kept movies; or the game's own key-capture mode setting it) they
return the retail constants 0.5625 / 0.75, so every override computes exactly what the
generated code did. The overrides only ever call them on the game's WIDE branch, so at 4:3
(flag 0) not even the call happens.

`IsWidescreen` stays the game's flag: there is no renderer-side transform yet (stage 2),
so nothing is squeezed twice. When stage 2 adds one for an element, that element's
override must use 1.0 there instead of `rg_hud_xscale()`.

### Overrides (new, all mine; `tools/ingest.py --check`: 161 overrides, 0 problems)

Generated from the `game/` files by `tools/wide/wide_overrides.py` (copy, header with the
MANIFEST sha256, prototypes after `#include "types.h"`, exact one-match replacements;
`--check` = dry run, `--force` = rewrite, the re-port path when a snapshot bump marks them
STALE). The diffs are one or two lines each:

| Override | Change |
| --- | --- |
| `camera/SceneCameraApplyAspect_1c6a10.c` | WIDE branch: `ViewSetAspect(ctx, rg_aspect_d())` (was 0.5625) |
| `gfx/GsDrawSpriteCentered_3834d0.c`, `gfx/GsDrawSpriteAnchorBR_3836a0.c`, `gfx/GsDrawSpriteAnchorBL_383860.c`, `gfx/DrawRotatedQuad_383c70.c` | width factor `rg_hud_xscale()` (was 0.75) |
| `ui/HpGaugeDraw_31d090.c`, `ui/HpGaugeDrawThin_31d2d0.c` | bar width `40 * rg_hud_xscale()` |
| `ui/MinimapDrawEntries_329460.c` | `MinimapSetAspectScale(rg_hud_xscale())` |
| `battle/TargetSlotDraw_320b00.c` | lock-on slot offsets x `rg_hud_xscale()` |
| `battle/AttackChainDraw_380660.c`, `battle/AttackChainStartMaybe_382910.c` | chain scale `rg_hud_xscale()` (also its right-anchored `512 - 62*sc` positions, which therefore stay at the same distance from the right edge on any canvas) |
| `effect/LensFlareDraw_2ed830.cpp` | ghost x scale |
| `effect/DoorCursorDraw_304aa0.cpp` | cursor half width `30 * rg_hud_xscale()` |
| `gfx/CompassHudRender_370fb0.cpp` | **not WIDE-aware in retail**: with the flag, perspective `rg_aspect_d()` (was 0.75 always) and the four marker sprites' half width `208 * rg_hud_xscale()` (was 0xD0); the compass keeps its screen position (pixel 75, 388), which is retail's (stretched) WIDE position; LEFT anchoring is stage 2 |
| `menu/DrawModelWithCamera_28bf80.cpp` | **not WIDE-aware in retail**: menu model previews take `rg_aspect_d()` with the flag (were 0.75: stretched models) |
| `sys/GameSessionInit_1f5d80.cpp` | the session-start projection takes `rg_aspect_d()` with the flag (was 0.75) |

Not overridden, on purpose:

- `title_TitleSessionInit_4f0cb0` (title 3D at 0.75): the title is shown 4:3 pillarboxed
  with the flag cleared, so 0.75 is right there.
- `ShadowMapRender_146680` (aspect 1.0, off-screen).
- `insect_InsectBattleDrawPreviewModel_4f5fc0` divides a model scale by 0.75; the insect
  overlay is not WIDE-aware in retail either. Not reached by any golden; candidate for a
  later override (multiply by `rg_aspect_d()` / 0.75 with the flag).

No `game/`, `tools/ingest.py`, `tools/stages`, `src/gpu`, `src/ps2` or foreign override
file changed. None of the target functions was overridden by anyone else; none of them is
one of the mouse camera's (`CameraObjApplyInputMaybe_1619e0`, `CameraFirstPersonUpdate_307f00`,
`MainLoop_1c2c10`), which are untouched.

### Code (besides the overrides)

| File | What |
| --- | --- |
| `src/settings/rg_aspect.[ch]` | `RG_ASPECT_16_10 / 21_9 / AUTO`; `rg_aspect_resolve` (setting + window -> reduced shape); `rg_aspect_step_ratio` (the stage 0 policy for any shape); `rg_aspect_step_settings` takes the window size; `rg_aspect_d_for` / `rg_hud_xscale_for` (pure); `rg_aspect_set_current` / `rg_aspect_d` / `rg_hud_xscale` (what the overrides read) |
| `src/settings/rg_settings_core.c` | `graphics.aspect` = 4:3 / 16:9 / 16:10 / 21:9 / auto (new values appended: old files keep their meaning) |
| `src/game/rg_game_main.c` | `aspect_apply`: window size for auto, `rg_aspect_set_current` before every field |
| `tests/host/host_tests.c`, `tests/host/CMakeLists.txt` | `settings.wide_policy` updated (enum, 21:9 and auto through the registry, a bad value `32:9` falls back to 4:3); new `settings.wide_any` (labels settings, wide) |
| `tools/wide/` (new) | `run.sh` (golden run with dumps and `--shot`s), `runcmp.py` (two runs: STATUS lines, every dump byte-wise, shots, differing-pixel counts), `pairsheet.py` (labelled side-by-side sheets), `bestmatch.py` (rank frames by similarity to a reference, to line up a PCSX2 shot), `pcsx2_wide.py` (PCSX2 with the WIDE flag and window shots), `wide_overrides.py` |

The host (`rg_fit_rect_content`, `rg_present_image`) and the runtime's "match window"
internal resolution were already shape-generic; no change.

### Verification

Golden input, headless, `RG_GPU=hw`, 24,600 fields, `tools/wide/run.sh` with RG_GS_DUMP
and `--shot` at fields 1500, 7100, 8000, 8290, 10000, 12000, 20000, 23000, 23600, 24000,
24500. "Base" = `out/wide/stage1/base/rg-game.exe`, built from the tree as found before any
stage 1 edit (stage 0 + everyone else's current work); "stage 1" = `out/wide/stage1/s1/rg-game.exe`.

| Compared (`tools/wide/runcmp.py`) | Result |
| --- | --- |
| Original (`--preset original`), stage 1 vs base | 49 STATUS lines identical; all 33 dump files (display, local memory, GS regs + CLUT at 11 fields) byte-identical; 11 `--shot` PNGs identical |
| 16:9, stage 1 vs base (= stage 0) | the same: everything byte-identical, i.e. **no visible change at 16:9 in this run** (the intentional changes, compass / model previews / session-start projection, are not exercised: see below) |
| 16:10, 21:9, auto (3440x1440 = 43:18) vs base 16:9 | 49 STATUS lines identical (same flow and battle timing at every aspect); title (1500) and movie (7100) native frames identical; every 3D frame from 8000 differs (wider view) |

Where the golden reaches the changed code (`RG_BREAK` on the three non-retail-WIDE
overrides, `runs/diag`): `GameSessionInit_1f5d80` once at game vbl 2069 (after NEW GAME,
TITLE overlay still loaded, so flag 0: 0.75 as before); `CompassHudRender_370fb0` every
other vbl 22865-24561 (the battle), but the compass is invisible there (it returns at its
alpha test, `arg->f1C <= 0`: frames byte-identical); `DrawModelWithCamera_28bf80` never.
So these three are verified only by construction (flag-gated, Original identical); no
input script reaches free field walking or the main menu yet.

One non-visual difference: at 16:10 / 21:9 / auto the f7100 (movie) GS register dump
differs from 16:9 in one word, reg 0x0C (XYZF3, the last vertex written); the display is
identical. It is the vertex left over from the last wide field before the movie, whose
projection differs by aspect.

Screenshots (`out/wide/stage1/shots/`, as presented at 448 lines: `-4x3` 597, `-16x9`
796, `-16x10` 717, `-21x9` 1062, `-auto-43x18` 1070 wide): `f8000`, `f8290`, `f12000`,
`f20000` (event scenes), `f23000`, `f23600` (battle: HP gauges, target cursor), `f24500`
(pause). In all of them the 3D is in proportion and widens Hor+; the event letterbox
stretches with the canvas; the party HUD, the top battle bars and subtitles stretch (not
WIDE-aware: stage 2); nothing missing at the frame edges in these scenes, including 21:9.

**PCSX2 WIDE reference** (`tools/wide/pcsx2_wide.py --renderer 13 --speed 0.5`: retail
with the golden input, `D_00481638 = 1` written at sampled vsyncs from game vbl 7400, window
shots). Retail's timeline under this input differs from the port's by about 1,000 vbl in
the event scenes (the port reaches the battle at ~22,900, PCSX2 at ~24,000, as in
tools/trace/README.md), so frames are lined up by content: `tools/wide/bestmatch.py`
ranked a dense port 16:9 run (every 30 fields, 18,500-21,500) against the PCSX2 shot at
vbl 19,964 and found f18950 (mean grey difference 1.5/255).
`shots/pcsx2-wide-v19964-vs-port-169-f18950.png`: the same horizontal field of view and
framing (scene edges, character positions and proportions), the subtitle at the same
(unsqueezed) width; only the animation phase differs. Retail WIDE and the port's 16:9
agree. Not a pixel comparison (PCSX2's software renderer, window scaling, offset timing).

Windowed (`--set graphics.aspect=auto --set display.width=1920 --set display.height=800`,
the real SDL presenter, `RG_WINDOW_SHOT`): `shots/window-auto-1920x800-f8290.png` fills the
1920x800 (12:5) window edge to edge, 3D in proportion.

Tests: `ctest -L "settings|host|wide|input"` 88/88 (`gpu.gfx.game_replay` skipped),
including the new `settings.wide_any`: shapes from every setting and window
(1280x720 -> 16:9, 3440x1440 -> 43:18, 1366x768 -> 683:384, 1281x960 -> 4:3, portrait ->
4:3, 7680x1080 -> clamped 32:9), exact retail constants at 4:3 and 16:9 (also from
1920x1080), s = d / 0.75 and monotonic over a width sweep, and the published values
(retail constants unless the policy owns the flag; kept movie; stretched movie; undo).

### Known issues (stage 1)

- Everything listed under "Known issues" above for menus, the battle menu, text and
  captions still applies, at any aspect; at 21:9 the stretch is 1.78x, so stage 2 matters
  more there.
- The compass and model-preview changes are not seen in any run (above).
- Screen-space logic that uses the projection (screen markers, door-cursor fades,
  aim-offscreen) sees the view of the chosen aspect: presentation state, as in stage 0.
- `auto` follows the window live: a window resized by dragging changes the projection
  every field while dragging (harmless, but visible).
- 21:9 and wider show set edges built for 4:3 in some event scenes (audit "Risks"); not
  seen in the golden's scenes.

### Stage 2 plan notes (from this work; not implemented)

- **The anchor point is the draw call, not the task.** The 12 WIDE sites show the game
  already distinguishes WORLD elements (squeeze about their own centre) from
  corner-anchored ones (`AttackChainDraw` scales its `512 - 62*sc` positions, i.e. a RIGHT
  anchor). The cheapest stage 2 is per-helper: give `GsDrawSprite*` / `DrawRotatedQuad`
  overrides an anchor-class global (set by the per-task hook in `TaskTableRun_1f5340`) and
  transform the *position* there (`x*s` / `W-(W-x)*s` / `W/2+(x-W/2)*s`), on the CPU, before
  the packet is built. That covers much of the battle HUD without a renderer change; only
  primitives emitted through raw `GsPkt*` calls (fonts, menu windows, the NORMAL overlay's
  battle menu) need the renderer-side marker packets of the audit.
- **Scissor**: fonts and message windows clip through `GsPktSetScissor_28c2e0`,
  `MesWinSetScissor_271fa0`, `FontSetScissor_26e380`; a CPU-side transform must apply to
  these too, or text will clip at the old 4:3 rectangle.
- **Order with the flag**: once an element is positioned by the stage 2 transform, its
  WIDE squeeze must come from the transform's `s` and the override's `rg_hud_xscale()` must
  return 1.0 for it; keep one switch (e.g. `rg_hud_xscale()` returns 1.0 while the current
  task's class is not WORLD) rather than editing each override again.
- **Compass**: LEFT class: its override already owns the screen matrix, so moving its
  centre (`D_0047D830`, frame pixel 75) to `75 * s` is a one-line change there once the
  rest of the left-hand HUD moves with it (alone it would detach from the stretched HUD).
- **Screens to pillarbox whole** (stage 0's CENTER-the-frame trick) could be extended to
  full-screen menus that hide the 3D (shop, factory, insect), detected by their draw task,
  before any per-element work.

## Stage 2: the 2D keeps its shape (layout transform)

Done 2026-10-19 (play-test 2 item 3: "the 3D looks great but the UI is stretched; scale but
never stretch"). Build tree `build/play2-i686`; scratch and shots in `out/play2/wide/`.
Setting `graphics.ui_layout` = `keep` (default: "Keep proportions (anchored)") | `stretch`
("Stretch (PS2 on a 16:9 TV)", the stage 1 look); Original = keep, but at 4:3 nothing runs.

### What it does

On a wide canvas every 2D element the game does not narrow itself was stretched by
A / (4/3). Stage 2 squeezes it back by s = `rg_hud_xscale_for(content)` (0.75 at 16:9,
0.833 at 16:10, 0.5625 at 21:9) about an anchor: `x' = a + (x - a) * s`, a = the left edge,
the centre or the right edge, so the element keeps its 4:3 shape at the height-scaled size
and corner HUD stays in its corner. Three mechanisms:

1. **Layout transform** (`src/settings/rg_layout.[ch]`), at the game's own 2D packet builder.
   Every EE-built 2D primitive goes through a GsPkt (`DrawListBeginPrim` .. `GsPktClose` ..
   `DrawListEndPrim`); the `GsPktClose` override hands the finished packet to
   `rg_layout_packet`, which walks its DMA chain (CNT + VIF DIRECT; CALL / REF skipped) and
   GIF tags (PACKED, REGLIST, A+D) to every vertex X (XYZ2 / XYZ3 / XYZF2 / XYZF3) and
   scissor and rewrites them in place. It has to happen at close: the native renderer
   decodes the packet at `DrawListEndPrim` (NATIVE-RENDER.md "Immediate packets"), right
   after, so a packet cannot wait for the rest of its widget. **Anchors are one frame
   behind**: the `TaskTableRun_1f5340` override brackets each game task
   (`rg_layout_task_begin` / `_end`); at a task's end its packets (original rectangles) are
   clustered by 2D overlap, each cluster gets an anchor (its centre in the left / middle /
   right third; a cluster as wide as the screen = a whole-screen layout, kept together about
   the centre) and each packet identity (task, calling function, n-th such packet of the
   task in the frame) is filed; the next frame applies it as the packet closes. A packet
   with no anchor from the last frame (a widget's first frame) uses its own rectangle.
   Packets drawn outside any task form one group per frame. A field without packets (the
   second VBlank of a 30 Hz frame) keeps the anchors.
   Left alone: packets drawn into another buffer than the frame's draw buffer (FRAME FBP of
   the first full-screen packet, normally 0: minimap tiles, character composites, blur /
   glare / DOF work buffers, texture animations); packets with the Z test on (3D effects and
   world labels such as NPC names, positioned by projection); packets spanning the screen
   edge to edge and tall background pieces running past an edge (fades, letterbox bars,
   backgrounds keep covering the screen); packets drawn while a world-anchored site
   suppresses the layout (`rg_layout_suppress`). A scissor-only packet (font / message window
   scissor) uses its rectangle as its element; narrower-than-screen scissors move with their
   element.
2. **Whole-screen pillarbox for full-screen menus**: a packet covering the visible screen
   with an indexed-colour UI texture (PSMT8 / PSMT4 / ...), drawn by a game task (the
   field's screen-effect passes sample 32/24/16-bit render targets), means a full-screen
   menu (main menu, transporter menu, help sheets, battle results, loading screens). The
   next field the aspect policy treats the screen like the title: frame 4:3 pillarboxed in
   the canvas, WIDE flag 0 (`rg_layout_wants_pillarbox`, read by `rg_aspect_step_settings`;
   detection keeps running while pillarboxed). These menus show the 3D through holes in
   their backgrounds (the main menu's portrait circle): pillarboxing keeps menu, frame art
   and scene consistent, which moving the panels over a stretched background could not.
   One field of lag when a menu opens or closes (like stage 0's movie detection).
3. **World-anchored 2D** narrows itself about its own position (stage 1) and is not laid
   out: the overrides `TargetSlotDraw_320b00`, `LensFlareDraw_2ed830`,
   `DoorCursorDraw_304aa0`, `CompassHudRender_370fb0` wrap their body in
   `rg_layout_suppress(1/0)` and use `rg_hud_xscale_world()`; the task `TaskDrawStatus_2058b0`
   (enemy HP gauges, damage numbers) is suppressed in the `TaskTableRun` override and
   `HpGaugeDraw*` use `rg_hud_xscale_world()`. The compass also moves its screen centre with
   the left anchor (`1792 + (x - 1792) * s`). **`rg_hud_xscale()` returns 1.0 while the
   layout is active**, so the HUD WIDE sites (attack chain, minimap entries, GsDrawSprite*
   helpers) draw at full width and stage 2 squeezes them with the rest of their widget (the
   "one switch" of the stage 2 plan notes).

Not changed by stage 2: 3D (VU1 output never passes a GsPkt), the title and movies (stage 0
pillarbox), 4:3. Game logic: the run hash of every tested scenario is identical at 4:3 /
16:9 / 16:10 / 21:9.

### Code

| File | What |
| --- | --- |
| `src/settings/rg_layout.[ch]` (new) | packet scan, anchors, frame-behind clustering, full-screen menu detection, stats, `RG_LAYOUT_LOG` |
| `src/settings/rg_aspect.[ch]` | `graphics.ui_layout`; `rg_aspect_set_current` drives `rg_layout_set_frame` / `_set_detect`; full-screen menus -> pillarbox; `rg_hud_xscale()` 1.0 while active, `rg_hud_xscale_world()` |
| `src/settings/rg_settings_core.c` | `graphics.ui_layout` (keep / stretch) |
| `overrides/src/main/gs/GsPktClose_13f5b0.c` | one call, `rg_layout_packet(pkt, caller)`, after the tags are patched |
| `overrides/src/main/sys/TaskTableRun_1f5340.c` (new) | task brackets; world task `TaskDrawStatus_2058b0` suppressed |
| overrides `TargetSlotDraw`, `LensFlareDraw`, `DoorCursorDraw`, `CompassHudRender`, `HpGaugeDraw`, `HpGaugeDrawThin` | world-anchored: suppressed wrapper and / or `rg_hud_xscale_world()`; compass centre left-anchored |
| `tests/host/host_tests.c` | `settings.wide_layout`: anchors, map, GIF scan (A+D, PACKED, scissor), inactive at s = 1, left / right / centre, full / Z test / suppressed untouched, frame-behind grouping |
| `tools/wide/stage2shots.py` (new) | the milestone screens at every aspect + contact sheet |
| `tools/wide/laysum.py` (new) | one field of an `RG_LAYOUT_LOG` with symbol names (task, caller, rectangle, decision) |
| `tools/fixtures/montage.py` | `--grid DIR --rows .. --grid-cols ..` (states x aspects sheet) |

No `src/native/render`, `src/gpu` or `src/ps2` file was touched.

Debug: `RG_LAYOUT=0` turns stage 2 off (transform and pillarbox detection),
`RG_LAYOUT_IMMEDIATE=1` lays every packet out by its own rectangle (no grouping),
`RG_LAYOUT_LOG=file` logs one line per packet and per field.

### Verification

- **Original / 4:3**: the hooks stay inactive (with `--preset original` an `RG_LAYOUT_LOG`
  file is not even opened); `save2_battle2` boot run: run hash `8c92377eaf60f320` and shot
  equal with `RG_LAYOUT=0`. All stage 2 code is gated by `rg_layout_active()` (our policy
  owns the WIDE flag) or `g_detect` (canvas wider than 4:3).
- **Same game at every aspect**: `tools/wide/stage2shots.py` scenarios (save2 boot + main
  menu, transporter menu, battle 2 + pause, battle 2 to results / map help) at 4:3, 16:9,
  16:10, 21:9: run hashes identical per scenario (menu `6c66562390f3b6f1`, trans
  `63afdc6b617ce300`, pause `b4af6b4ab7c08dc2`, battle2 `8c92377eaf60f320`).
- Contact sheets: `out/play2/wide/s2a/sheet.png` (first pass), `out/play2/wide/s2b/sheet.png`
  (final): title (4:3 pillarbox), field HUD (compass bottom-left, minimap right, prompt
  centred, in proportion), main menu / transporter menu / help sheets / results
  (pillarboxed 4:3), battle HUD (party panels bottom-left, weapon bar top-left, radar
  bottom-right, in proportion), pause dialogue (centred).

### Known issues (stage 2)

- (Fixed 2026-10-23) NPC name labels and damage numbers: `rg_layout_about_begin/_end` squeezes
  their packets about the projected point (overrides `ScreenMarkerDrawAll_31af50`,
  `DamagePopupDraw_2d3240`, generated by `tools/wide/label_overrides.py`).
- A newly appearing widget's first frame is laid out by its own rectangles (frame-behind
  grouping); a widget whose packets change identity every frame keeps per-packet anchors.
- Full-screen menu detection keys on an indexed-colour covering texture drawn in a task; a
  full-screen menu drawn otherwise would be laid out per element over its stretched
  background. (Stage 3, 2026-10-24: the 4:3 switch for these screens is gone, see
  "Stage 3".)
- Event-scene subtitles checked (route field 8,290: centred, in proportion, letterbox bars
  still cover). Shop, factory and insect screens: checked in stage 3; 32:9 and the remaining
  menus in its second pass ("Stage 3 gaps").

### USER 2026-10-19: no aspect switch for menus (stage 3: done 2026-10-24, section "Stage 3")

Play-test of 1019a at a wide aspect: when a tutorial/help sheet appears the screen shrinks
to 4:3 and widens again when it closes; when the main menu opens, the 3D scene seen through
the menu's "window" (portrait circle) shows the characters squashed (the scene, or the
screen capture the menu draws over, was rendered with the widened projection and is then
shown inside the 4:3 pillarbox). The user wants **no aspect change** for these: the canvas
and the 3D stay at the wide aspect the whole time; menus and help sheets are laid out as UI
(scaled by height, kept in proportion, centred/anchored) over the full-width scene.

Direction (to design): drop the whole-screen pillarbox (mechanism 2) for in-game menus and
help sheets (keep it only for the title and kept movies). Lay a full-screen menu out as ONE
4:3 element centred in the canvas (panels, frame art and the background texture together,
so the holes stay aligned with their panels), and fill the side areas: the live 3D (or the
captured scene) at its proper wide projection, optionally dimmed/blurred, or the menu's
background art extended (mirrored/stretched edge strips). Keep the WIDE flag set while the
menu is up so the scene behind keeps the wide projection (no squash, no switch). Help sheets
over the field/battle become a centred element over the unchanged wide scene. Check the
screen-capture path (the menu background that samples a capture of the scene) so the
capture is shown at its own aspect, not squeezed. Gate: no aspect change at any
menu/tutorial open/close (canvas content rect constant), scene proportions identical with
and without the menu, run hashes identical across aspects, Original untouched.

## Stage 3: no aspect switch for menus

Done 2026-10-24 (BRINGUP.md resume item 1, the USER request above). Build tree
`build/wide3-i686`; scratch, runs and shots in `out/wide3/` (game imagery, never committed).

### What it does

The canvas, the WIDE flag and the 3D projection stay wide while any menu, help sheet or
dialogue is up: stage 2's whole-screen 4:3 pillarbox for full-screen menus (mechanism 2) is
gone (only `RG_LAYOUT_MENU_PILLARBOX=1` brings it back, for before/after comparisons). The
title and kept movies are still shown 4:3 (stage 0). Instead, a full-screen menu is laid out
as **one 4:3 element in the middle of the wide canvas** (`src/settings/rg_layout.c`):

- **Menu tasks.** A game task that draws a full-screen indexed-colour background (the stage 2
  detection) is a menu task for that frame and the next. Everything it draws is squeezed by
  s about the screen centre, its indexed-colour background pieces included (so the holes in
  the background stay on their panels). Other tasks keep their own anchors (stage 2).
  Non-indexed covering packets (fades, dims, scene captures) still cover the whole canvas.
- **Pieces off the 4:3 screen stay hidden.** Menus park panels off screen and slide them in
  (the main menu's sub-menu labels, the transporter's rows). Squeezed toward the centre they
  would show in the canvas's side areas, so menu sprites (PRIM sprite, from an A+D PRIM or
  the GIF tag's PRE field) entirely off the 4:3 screen collapse to zero width; sprites mostly
  off it, or small, are clipped to it (UV cut with them); bars at least a quarter of the
  screen wide, mostly on screen and bleeding off an edge (title bars) get their outer vertex
  pinned to the canvas edge.
- **The sides are filled with the menu's own background.** The tall, wide indexed background
  pieces of a menu get **mirrored edge strips**: A+D sprites appended to the same GsPkt
  (`append_ad`: only when the packet is one A+D GIF tag at the top of its memory stack with
  room left; GsPktClose then reserves the longer packet). Each strip covers the canvas from
  the piece's squeezed edge to the canvas edge and samples the piece's own edge art mirrored
  across the seam, so the art continues without a joint and the cut-outs do not move. Per
  drawing function only its lowest background layer is extended (the main menu's backdrop,
  drawn over its tiles, would mirror its shaded cut-out into the side); a layer drawn by
  another function (the save screen over the transporter menu) replaces the strips below it.
  A help sheet drawn over a full-screen scene capture (the battle tutorials) is an overlay:
  its strips stretch its edge column (the dimmed margin) instead of mirroring the sheet.
  What no strip covers shows the frame clear, drawn black on menu screens (at 4:3 the menu
  covers it entirely).
- **Main menu portrait circle.** The circle shows a 256x256 copy of the field frame
  (x 191..446, y 106..361) taken when the menu opens (`MenuCaptureScreenTex_298810`). On a
  wide canvas that frame is anamorphic, so the copy held a horizontally squashed scene: the
  "squashed characters" (stage 2 showed it in the 4:3 pillarbox). The new override
  `menu/MenuCaptureScreenTex_298810.c` calls `rg_layout_capture_wide`, which resamples the
  copy (linear in x) from the wide frame's columns `256 + (x - 256) * s`, so the texture holds
  what the 4:3 copy holds and the circle shows the party in proportion at every aspect. It
  returns 0 (the game's own copy runs) unless the layout is active.

Field HUD, battle HUD, dialogues and the pause dialogue are not menu tasks and keep their
stage 2 anchors; factory and insect screens without a full-screen indexed background (the
factory floor with its button column, the INSMENU attract screen) keep stage 2's per-element
layout over the wide 3D.

### Code

| File | What |
| --- | --- |
| `src/settings/rg_layout.[ch]` | menu tasks (`menu_task`: this frame and the one before), `rg_layout_menu_screen`, `rg_layout_wants_pillarbox` debug only; the GIF scan records UV / ST, RGBAQ, PRIM (A+D and tag PRE) and the vertex index since PRIM; `menu_sprites` (hide / clip / pin / background strips), `append_ad`; black frame clear on menu screens; `rg_layout_capture_wide`; stats `menu`, `capture`, `strips`; `RG_LAYOUT_LOG` packet lines add `tbp=` and `u=`, plus `->` lines (where off-screen menu pieces went) and `strips:` / `append:` lines |
| `src/settings/rg_aspect.c` | no `title = 1` for full-screen menus (only with `RG_LAYOUT_MENU_PILLARBOX=1`); `RG_ASPECT_LOG=file`: one line per change of the presented shape (field, WIDE flag, canvas, content, menu screen) |
| `overrides/src/main/menu/MenuCaptureScreenTex_298810.c` (new, generated by `tools/wide/menu_overrides.py`; `tools/ingest.py --check`: 224 overrides, 0 problems) | one call before the copy loop: `if (rg_layout_capture_wide(src, dst)) return;` |
| `tests/host/host_tests.c`, `tests/host/CMakeLists.txt` | new `settings.wide_menu`: menu task from a covering PSMT8 background, background and panel squeezed about the centre, a 32-bit capture left covering, another task keeps its anchor, no pillarbox request, the menu ends two frames after its background, an off-screen sprite stays hidden, a small sprite across the edge is clipped with its UV |
| `tools/wide/stage3shots.py` (new) | the menu / tutorial / shop / save / factory / insect screens the cards reach, at chosen aspects: shots, run hash and `RG_ASPECT_LOG` per run, contact sheet |
| `tools/wide/idcheck.py` (new) | two shot dirs from two exes: run hashes and shot pixels (the Original / 4:3 gate) |
| `tools/wide/menu_overrides.py` (new) | the stage 3 override generator (`--check` / `--force`, same scheme as `wide_overrides.py`) |

No `src/gpu`, `src/native/render`, `src/crt` or `game/` file was touched and no renderer hook
was needed (the strips are ordinary GS sprites in the game's own packet).

### Verification

Scenarios (`tools/wide/stage3shots.py`, cards from `out/fixtures/cards`): main menu (save2),
transporter menu + save screen (save2), item menu, context menu, target panel (late_game,
`item_use`), shop (zshop2), "The Lock-On Function" tutorial, battle and pause (save2 +
battle2 script), factory menu and blueprints (factory), INSMENU, team select and the Insectron
battle (insectron).

- **No aspect switch:** `RG_ASPECT_LOG` shows one change per run after the title (title 4:3
  -> the game's wide shape) and none at any menu, tutorial, shop or save screen open / close,
  at 16:9 and 21:9, in all 8 scenarios.
- **Same game at every aspect:** run hash identical at 4:3 / 16:9 / 21:9 in every scenario.
- **Original / 4:3 unchanged:** a baseline exe built from the same tree with the stage 2
  `src/settings` files and without the new override (`out/wide3/base_same`) against the
  stage 3 exe (`out/wide3/s3final`), all 8 scenarios at 4:3 and three with `--preset
  original` (`tools/wide/idcheck.py`): run hashes identical, 62 of 64 shots pixel-identical;
  the other two (field 3790, 18x18 px at (173, 386); insect team select, 18x137 px at
  (338, 81)) differ between two runs of the baseline itself as well (pre-existing
  nondeterminism, not stage 3).
- Shots: `out/wide3/a13/` (all scenarios at 4:3 / 16:9 / 21:9; `sheetA.png`, `sheetB.png`),
  `out/wide3/compare/sheet1.png`, `sheet2.png` (columns 4:3 | stage 2 16:9 | stage 3 16:9 |
  stage 3 21:9; the stage 2 column is the exe from the start of this work, an older tree, so
  battle timings differ), `out/wide3/a14/save_21x9-view.png` (save screen after the last fix).

### Known issues (stage 3)

(Revised by the second pass below, "Stage 3 gaps".)

- The side strips mirror the menu's background art. Since the second pass they darken
  toward the canvas edge (75 % at the edge), so a strong feature near the art's edge (the
  main menu's compass rose, a planet on the Galaxy Map) reads as a dim vignette, but it is
  still a mirrored copy, not new art.
- A menu whose background is not an indexed-colour covering texture drawn by a task is not a
  menu task (stage 2's detection) and keeps the per-element layout. Census (second pass):
  none among the screens the cards reach; the per-element screens are overlays over the live
  3D (battle HUD and command menu, factory floor, INSMENU attract).
- Strips need the background packet at the top of its memory stack with room left; if not,
  that side shows the black clear (`append:` lines in `RG_LAYOUT_LOG`; never seen in the
  scenarios, `menucensus.py` counts them).
- A menu's first frame: fixed for dedicated menu tasks (second pass); left for a task that
  also draws a non-menu screen (INSMENU attract -> team select: the packets before the
  background on that frame are the attract screen's last frame, laid out as it was).

### Stage 3 gaps (2026-10-24, second pass)

Build tree `build/wide4-i686`; scratch, runs and shots in `out/wide4/` (game imagery, never
committed). The shared tree's renderer was mid-change during this pass (src/native/render
edits 19:25-20:11 rendered black / blue frames), so the screens and gates below ran on
`out/wide4/r1/rg-game.exe` = the stage 3 build's objects (`build/wide3-i686`, i.e.
`out/wide3/s3final`) relinked with this pass's `rg_layout.c` (`tools/wide/relink.py`);
`out/wide3/s3final` is its same-tree baseline. `build/wide4-i686` builds (all targets and
rg-game) with the same `src/settings`.

**Screens checked** (`tools/wide/stage3shots.py`, 16 scenarios, 4:3 / 16:9 / 21:9 / 32:9;
32:9 = `graphics.aspect=auto` on a 3840x1080 display):

| Screen | Before this pass (21:9 / 32:9) | Now |
| --- | --- | --- |
| Main menu (field, Dorgenark) | compass rose mirrored; at 32:9 the mirror reached the portrait-circle cut-out (black half disc at the left edge) | faded strips; mirrored span capped |
| Allies, member commands, Strategy, Revelation ability list, Battle Recorder, Frog Log | left side black, upper right black: their backdrop is 576x384 tiles (2 x 3) drawn by one function, and "only the lowest layer per function" kept only the first tile's strips | strips per screen rows: every tile row extended; the tile right of the 4:3 screen is real art, squeezed into view |
| Revelation board, stone list | board cells and the cursor box off the 4:3 screen shown in the right side; mirrored cells / cursor; left black | per-sprite background test: cells and boxes hidden / clipped like other menu sprites; the board parchment extends (no cells); left strip from the parchment |
| System sub-menu, Items / context / target, transporter + save, shop | OK | OK (faded strips) |
| Galaxy Map (Dorgenark bridge, planet select, `TaskDrawMenuSpace`) | menu task, centred; starfield mirrored | same, faded (a planet near the edge shows twice, dimmed) |
| Area map (SELECT in the field) | overlay centred, in proportion | unchanged |
| Battle command menu, its Items grid | per-element over the battle (`BattleMenuDraw`, `TaskDrawMenuBtlChg`), in proportion | unchanged |
| Help sheets (Lock-On, Map Display), results, pause | OK | unchanged |
| Factory, blueprints, INSMENU, team select, Insectron battle | OK | unchanged |
| NPC name labels, damage numbers (after 10-23) | -- | on their NPC / target, in proportion, at 16:9 / 21:9 / 32:9 |

At 32:9 the shots (x1 internal resolution, 512-wide frame) squeeze text to 0.375 and small
glyphs are unreadable in them; that is the shot resolution, not the layout.

**Fixes** (`src/settings/rg_layout.c`, `menu_sprites` / `strip_emit`):

1. *Strip coverage per screen rows*: each side keeps the rows (and the seam) a drawing
   function already extended this frame; a piece of the same function is skipped only when
   at least half its visible rows are already covered from a seam at least as far out. A
   later layer reaching further out (Revelation board parchment over the menu backdrop) is
   extended from its own edge; within one packet the topmost sprite of the rows wins (the
   main menu backdrop packet is a translucent black shadow sprite, then the art: the first
   pass happened to mirror the art only because the strips took the packet's last colour).
2. *Per-sprite background test*: in a background packet only sprites at least an eighth of
   the screen wide and tall are background tiles (strips, never hidden); smaller ones follow
   the hide / clip / pin rules of other menu sprites.
3. *Faded strips*: up to 16 bands per side (as many as fit in 320 appended qwords), each
   with its own RGBAQ (the kicking vertex's colour scaled by 1 - 0.75 * smoothstep(t), t = 0
   at the seam, 1 at the canvas edge), the packet's last colour restored after them; only
   with a modulating texture function (TEX0 TFX 0), else one unfaded strip as before.
   `RG_LAYOUT_STRIP_FADE=0..100` (default 75), `RG_LAYOUT_STRIPS=smear` (stretch the outer
   6 texels: soft on parchment, streaks on the Galaxy Map's stars; comparison
   `out/wide4/vcmp/v.png`). Considered and not done: multi-tap blur (alpha passes ghost at
   any useful radius), symmetric-background detection (needs the texture data).
4. *Mirror cap*: at most the outer 30 % of the piece's art is mirrored; beyond, the strip is
   stretched (32:9 main menu).
5. *Dedicated menu tasks* (first frame): a task that drew a menu background and never drew a
   laid-out packet in a frame without one (that frame or the one before) is the menu from
   its first packet, also on a later menu's first frame; drawing without a background two
   frames running disqualifies it for good.
6. `RG_LAYOUT_H` (the include guard) was also the frame-height constant (redefined, a
   warning in every includer): the constant is `RG_LAYOUT_FRAME_H` now.
7. `RG_LAYOUT_LOG` "strips:" lines say "(faded)"; `RG_LAYOUT_LOG_STRIPS=1` dumps every
   appended A+D qword.

**Census** (`tools/wide/menucensus.py`, all 16 scenarios at 21:9 and 32:9): menu tasks
`TaskDrawMenuMain`, `TaskDrawMenuTrans`, `TaskDrawMenuShop`, `TaskDrawMenuSpace`,
`TaskDrawMenuInsectVs`, `TaskDrawMenuWin`, `TaskDrawEvent1` (help sheets); no task with a
direct-colour covering picture plus its own per-element layout (no non-indexed full-screen
menu); per-element layouts spanning the screen: `BattleMenuDraw` (battle HUD, by design),
`TaskDrawMenuBtlChg` (1 transition field), `TaskDrawMenuFactory` (3 fields),
`TaskDrawMenuInsectVs` (INSMENU attract, 539 fields): overlays over the live 3D, correct per
element; no `append:` failures.

**Verification:**
- Run hashes identical at 4:3 / 16:9 / 21:9 / 32:9 in all 16 scenarios; `RG_ASPECT_LOG`:
  one change after the title per run, none at any menu / map / help sheet.
- Original / 4:3 (`idcheck.py`, r1 vs `out/wide3/s3final`): 16 scenarios at 4:3 and 3 with
  `--preset original`: every run hash identical; 76 of 86 shot files (4:3) and 18 of 20
  (Original) pixel-identical. The rest: field 3790 (18x18 px, documented), team select
  (documented), battle command menu (153 px, max 1 level: differs between two runs of the
  baseline itself) and the Revelation board's flashing slot (44x49 px, up to 58 levels): that
  one differs between three exes built from the same game objects (s3final, r1, and r0 =
  the first-pass `rg_layout.c` relinked the same way), i.e. it depends on the exe's layout,
  not on the layout code (an uninitialised read in the board's slot colour path:
  `RevelationBoardPktSetColorLerp_34ce10` / the `RevelationBoardDrawSprite_34c170` override;
  for the stack-block / protos lanes).
- `settings.wide_strips` (new host test): faded bands (count, colours, mirrored U at the
  canvas edge, colour restored), off-screen small sprite hidden in a background packet,
  same-function layer over the same rows skipped, another function's layer extended, a
  later layer reaching further out extended, dedicated menu task centred on a reopened
  menu's first frame.
- Fixture gates on r1: regen --check 300 + verify 8/8, bootcheck --all 29/29, mapcheck 5/5 (regen's save2 card differed from the shared one in 216 header bytes, so the shared `out/fixtures/cards/save2` was restored from a backup); `tools/ingest.py --check` 224 overrides, 0 problems; `build/wide4-i686`: all targets and rg-game build without the old `RG_LAYOUT_H` warning, ctest -L "wide|settings|host" 52/52 (this configuration has no render label), full ctest 630/630 (5 skipped: 3 realdata, gpu_smoke, link_audit_control; the fixtures label run serially, one rg-game at a time).
- Shots: `out/wide4/f_new/` (all scenarios x 4 aspects); contact sheets
  `out/wide4/f_new/sheet_menus1.png` (transporter, save, items, shop),
  `sheet_sub.png` (Allies, Strategy, Recorder, Frog Log, System), `sheet_rest.png`
  (Revelation, battle command menu, Dorgenark menu, Galaxy Map), `sheet_battle.png`,
  `sheet_map.png`, `sheet_ins.png`; before / after at 21:9 `out/wide4/ba/sheet_before_after.png`.

**Tools** (new): `tools/wide/menucensus.py` (menus / late first frames / non-indexed
backgrounds / screen-spanning per-element layouts / append failures from `RG_LAYOUT_LOG`s),
`tools/wide/aspectrow.py` (one screen at every aspect as presented, side by side),
`tools/wide/relink.py` (relink rg-game from an existing build tree's objects with your own
sources recompiled: an exe and a same-tree baseline that differ only in your files while a
lane you do not own is mid-change). `stage3shots.py`: scenarios `worldmap`, `allies`,
`strategy`, `menurows`, `revel`, `btlmenu`, `dorg`; aspect `32:9`; `battle2` shots retimed
(results 7300, map help 7550, field 7690).

## Checkpoint (newest first)

- 2026-10-24 (late): **stage 3 gaps closed** (section "Stage 3 gaps"): 32:9 and every
  remaining menu checked; tiled menu backdrops (Allies, Strategy, Recorder, Frog Log,
  Revelation list) and the Revelation board fixed; strips faded toward the canvas edge;
  first-frame menu layout for dedicated menu tasks; `RG_LAYOUT_H` clash gone; census tool.

- 2026-10-24: **stage 3 done** (section "Stage 3"): no aspect switch for menus / help
  sheets; menus laid out as one centred 4:3 element with mirrored background strips at the
  sides; portrait-circle capture resampled; Original / 4:3 unchanged; run hashes identical
  across aspects.

- 2026-10-19: **stage 2 done** (section "Stage 2", play-test 2 lane): layout transform at
  GsPktClose + TaskTableRun, full-screen menu pillarbox, world sites suppressed; Original
  untouched; run hashes identical across aspects.

- 2026-10-17: **stage 1 done** (section "Stage 1"). 16 new overrides (ingest --check 0
  problems), `graphics.aspect` 4:3 / 16:9 / 16:10 / 21:9 / auto. Original and 16:9
  byte-identical to the pre-stage-1 exe at 11 fields; all aspects same STATUS flow;
  PCSX2 WIDE reference matches the port's 16:9 framing. `ctest -L "settings|host|wide|input"`
  88/88. Reusable scripts in `tools/wide/`.

- 2026-10-17: done. `ctest -L "settings|host|wide"` 53/53 (gpu.gfx.game_replay skipped)
  and `-L "runtime|input"` 37/37 (`runtime.cdvd_realdata` skipped) in `build/wide-i686`.
  Golden runs: Original byte-identical to the pre-change build at 9 fields; 16:9 shots in
  `out/wide/shots/`.
- 2026-10-17: code and tests in. The first `build/wide-i686` build compiled
  `rg_game_main.c` after the edits had started (ninja reached it last), so the "before"
  exe was linked by hand from that build's untouched libraries and the reconstructed
  pre-change `rg_game_main.c`.
- 2026-10-17: started (`build/wide-i686`, configured like `build/render-i686`).
