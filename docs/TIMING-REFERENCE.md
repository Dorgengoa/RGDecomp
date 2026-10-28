# Reference timing contract (PCSX2)

PLAN.md "Unlocked frame rate", work-order step 1: what retail actually does with VBlanks,
frame intervals, frame-time feedback and the scene time scale, measured in the PCSX2
harness with the golden input and with no input. The port-side record and the
milestone-aligned comparison built on this are in [TIMING-LOCKSTEP.md](TIMING-LOCKSTEP.md).
The source audit this checks is [FRAMERATE-AUDIT.md](FRAMERATE-AUDIT.md).

All of it is original CC0 code and analysis. PCSX2 2.6.3 (the portable copy under
`.tools/pcsx2`) is used as a program only.

## Tools

| Path | What |
| --- | --- |
| `tools/trace/probe.py --hooks timing` | 21 hook sites (below), about 10 records per VBlank |
| `tools/trace/probe.py --drain-s S` | new: drain the record ring at any point when no vsync idle came for S seconds |
| `tools/trace/timing.py build RUN.jsonl` | writes `RUN.ticks.tsv`, `RUN.events.tsv`, `RUN.milestones.tsv`, `RUN.summary.json` |
| `tools/trace/timing.py align A.milestones.tsv B.milestones.tsv` | milestone-aligned comparison (TIMING-LOCKSTEP.md); `--nowrap` against a port run |
| `src/trace/timing.c` (`RG_TIMING=path`) | the port's record in the same schema (TIMING-LOCKSTEP.md) |

`probe.py` gained a general six-word dump (`('words', [...])` with `W_abs`, `W_ptr`
pointer chains, `W_reg`, `W_stk`, `W_fpr` for float arguments), `Hooks.leaf` for
two-word `jr ra; insn` accessors, and two install fixes found while capturing (see
"Harness lessons").

Captures (under `out/timing/`, gitignored):

| Run | Input | Range | Command |
| --- | --- | --- | --- |
| `newgame_battle2` | golden `newgame_battle.input.txt` | vbl 0..26,000: boot, title, NEW GAME, NORMAL load, opening FMV, events, battle set-up, tutorial, 1,290 vbl of player-controlled battle | `probe.py --hooks timing --speed 0.5 --drain-s 1.0 --stop-vbl 26000` |
| `title_idle` | none | vbl 0..9,000: boot, title logo, title menu with its looping background movie | `probe.py --hooks timing --input "" --stop-vbl 9000` |
| `newgame_battle_perturbed` | golden | vbl 0..25,548 | the first golden capture. A second PCSX2 instance was started during it and its flow diverged (battle tutorial at vbl 24,125 instead of the golden's 24,182). Kept as the alignment tool's real-world control only |

`newgame_battle2` agrees with the golden state trace's game-mode timeline (mode 7 at
23,964 / golden ≤23,971, mode 11 at 24,181 / golden ≤24,182, mode 7 again at 24,707 /
golden 24,710; the golden samples every 10th vbl).

Not reached by either input: the in-game main menu and other `SceneOverlayModeOn`
callers, pause, field mode 6 for more than one frame, a warp, slow motion
(`GameSceneSetTimeScale`). A field/menu input script is the next capture.

## What a record is

Every hook appends `{fn, k, vbl, cnt, a0..a3, v0, ra, sp, d[6]}`: `vbl` is the game
counter `[0x004810C4]` at the call, `cnt` the COP0 Count (EE clock, 294.912 MHz).

| Site | Address | Logs |
| --- | --- | --- |
| `VblankStart` | `GfxVblankStartHandler_15df20` entry | per VBlank, before the counter increments: wait flag, frame-worker ready flag `D_0047E250`, disk-watch counter, sequence owner `D_00481554`, pause step, sysmode |
| `TickWake` | `PadVibrationTick_1837a0` | one `SysTickThreadMain_1c33f0` wake |
| `GfxEndFrame` | `GfxEndFrame_141c20` entry + return | entry: raw `T0_COUNT`, VIF1-time sample `D_004810B4`, divisor, sync, pending, skip. Return: stored feedback `+0xF10`, flip vbl `+0xF00`, late `+0xF04`, interval `Db+0x24`, depth slot 0 on/z |
| `WaitVsync` | `WaitVsyncCount_15de90` entry + return | base, count |
| `SceneTimeScale` | `GameSceneTimeScaleUpdate_1cebe0` entry + return | `+0x5E00..+0x5E14` before and after |
| `TaskTableRun` | `TaskTableRun_1f5340` entry + return | game mode, phase, pause step, task depth, sysmode; return = restart flag |
| `TaskListChanged` | `SetTaskListChanged_1f56b0` (leaf, only a0 ≠ 0) | who changed the task list |
| `SetVsyncInterval`, `SetTimeScaleLocked`, `SetTimeScaleSuspended` | `144140`, `1ceb90`, `1ceb60` | value + caller |
| `GameModePush` / `Pop`, `OverlayLoad` | `1f58f0`, `1f58a0`, `1c3210` | mode/phase, overlay id |
| `PadUpdate` | `PadUpdate_1843a0` return | pad object, current word `+4`, previous `+0x5C`, lock `+0x24C` |
| `PauseRequest`, `StateMachineSetState`, `sceCdRead`, `MovieOpen`, `MovieShutdown`, `MovieDrawFrame` | | arguments + caller |

A **tick** is one `GfxEndFrame_141c20` return. Three loops call it: `MainLoop_1c2c10`
(`loop=main`, the only one that runs the task table), `LoadingScreenThread_343510`
(`loadscreen`, its own EE thread while the main thread loads) and `MoviePlayModal_267c60`
(`moviemodal`, a modal FMV loop). The caller comes from the entry record's `ra`, named
from the decomp's asm (read-only). Everything logged between two returns is folded into
the row: task runs and restarts, the scene update, pad updates, sequence advances,
VBlanks, worker wakes, movie frames, CD reads, and the rare events.

Caveats. Hooks add about 40 EE instructions per record (≈ 0.02 % of a frame), so
probe runs are not lockstep references, but the game flow matched the golden. Feedback
values are PCSX2's EE/VIF timing model, not hardware: the slow-frame counts below are
"what this emulator measures", and with the Null renderer.

## Findings

### VBlank frequency

| Run | Consecutive VBlank pairs | Mean period (EE cycles) | Rate |
| --- | --- | --- | --- |
| newgame_battle2 | 25,661 | 4,920,120.09 | 59.94000 Hz |
| title_idle | 9,000 | 4,920,119.84 | 59.94000 Hz |

The handler-entry period scatters by ±6,600 cycles (interrupt latency), but the grid is
exactly 4,920,120 EE cycles = 294,912,000 / 59.94 (the BIOS runs a 60 Hz grid until
power-on frame 110, before the game counter starts). The port's kernel uses
BUSCLK / 59.94 (RUNTIME.md `vblank_rate`): the same clock. No VBlank was missed, and the
game counter advanced once per VBlank in both runs (one gap, inside a harness stall).

### The interval and when it changes

| vbl | Interval | Set by |
| --- | --- | --- |
| 17 | 2 | `title_TitleSessionInit_4f0cb0` |
| 538 | 1 (scale locked) | `title_TitleSceneOverlayModeOn_4eaa40`, title state 14 `TitleStateLoadRes` |
| 678 | 2 (unlocked) | `title_TitleSceneOverlayModeOff_4eaa00`, title state 4 `TitleStateCardCheck` + the title movie starts |
| 2,633 | 2 | `SystemHeapsInit_2020d0` (NORMAL boot) |

So **interval 1 ran for 140 ticks (vbl 538..678) in 26,000 VBlanks**, during the title's
resource-load screen. The title menu and its background movie run at **interval 2**, and
so does everything in NORMAL that the input reached: the opening FMV, the event scenes,
battle set-up, the tutorial and the battle. "Menus at 60 fps" holds only where
`SceneOverlayModeOn_288340` is called: `MainMenuModeUpdate_27d460`,
`SpaceMenuModeUpdate_27d130`, `TransporterMenuModeUpdate_27cc20` and the event command
`EvCmdSceneOverlayModeSet_25bc80` (static callers; not reached by this input). The
interval is a game-mode property set at those transitions, never adapted to load.

### Ticks, waits and lag

| Loop / interval | Ticks | VBlanks | dvbl = interval | Late flips |
| --- | --- | --- | --- | --- |
| main / 1 | 140 | 139 | 139 | 1 (the first) |
| main / 2 | 9,722 | 19,868 | 9,711 | 15 |
| loadscreen / 2 | 594 | 1,258 | 587 | 1 |
| moviemodal / 2 | 2,083 | 4,195 | 2,082 | 1 |

`GfxFlipBuffersMaybe_143650`: `late = now - last >= interval`. A frame that is not late
waits with `WaitVsyncCount(last, interval)`; a late frame flips **immediately** (the
interval setter always passes `sync = 0`, so the `WaitVsyncCount(now, 1)` branch never
runs), and the next frame's base is the counter at that flip. Consequences:

- After a lag frame the two-VBlank grid **changes phase** (dvbl 3, 5, 7 are seen). Retail
  logic is not on a fixed even/odd VBlank lattice.
- A frame can be late without its dvbl showing it: at vbl 24,719 the battle compute took
  2.95 fields, the flip landed mid-field 24,719 (dvbl 2, late 1), and the next frame got
  one field.
- The loading-screen thread sometimes waits 3..7 fields without being late: it is
  starved by the loading main thread.
- `waited = 1` in 775 main ticks: the compute took more than one field, so only one
  field was left to wait.

Lag in the main loop came only from loads, movie open/close, scene changes and the
first battle frames: 10 ticks with dvbl 3..32 (an eleventh, dvbl 340, is the harness
stall below). Every battle tick needs more than one field of
EE time (mean T0 330 lines = 1.26 fields, all 753 battle ticks above 262 lines): at
interval 1 battle would lag every frame. Event scenes average 0.45 field, the title 0.45,
the loading screen 0.24, the modal FMV 0.06.

### Frame-time feedback (`GfxEndFrame_141c20`, `+0xF10`)

`fb = clamp(max(T0 / div, VIF1_T0 / div), interval, 2 × interval)`. `T0_MODE = 0x83`
counts HBLANKs, `div` (`Db+0x2C`) is 262, so the unit is fields: the EE time since the
last flip, or the T0 value the VIF1 interrupt latched (`Vif1IntcHandler_15e170`), which
is the end of the frame's VIF1/VU1 chain. Both are sampled before the flip wait.

| Run | Ticks | fb > interval | fb = 2 × interval (clamped) |
| --- | --- | --- | --- |
| newgame_battle2 | 12,539 | 37 | 12 |
| title_idle | 4,265 | 25 | 4 |

Most "over" values are 2.0038: a movie frame whose VIF1 sample is 525 lines (two fields
plus one line). Real slow frames are the late flips above.

### Scene time scale (`+0x5E04..+0x5E10`)

The update runs once per main tick (8,781 calls, one per task-table tick). Lock state:

| vbl | Locked | By |
| --- | --- | --- |
| 538 / 678 | 1 / 0 | title overlay mode on/off |
| 3,865 | 0 then 1 | `FieldExploreModeUpdate_2833a0`, then mode 11 (`TransporterWarpModeUpdate_27f140`, the event mode) |
| 24,061 | 0 | `BattleModeUpdate_280220` |
| 24,181 | 1 | mode 11 (tutorial) |
| 24,707 | 0 | back to battle |

- **Locked (title, events, menus): slow frames change nothing.** 12 slow ticks in mode
  11 were followed by multiplier 1. The game just runs slower in VBlank time; logic per
  tick is unchanged.
- **Unlocked (field, battle): the next tick's multiplier `+0x5E0C` = fb / 2.** Seen
  once: vbl 24,719 fb 2.954, then multiplier 1.4771, timestep 1.4771, for exactly one
  tick, then 1 again. Fb ≤ 2 never changes it; interval 1 can never trigger it
  (fb ≤ 2 × 1).
- `+0x5E08` (scale) stayed 1.0, countdown `+0x5E10` stayed −1 (no `SetTimeScale`).
  Suspended `+0x5E15` stayed 0.
- **Count field `+0x5E04` was 1 in all 8,781 updates.**

**Consumers of `+0x5E04`: none.** Decoding every load, store and `addiu` with an offset
in `0x5E00..0x5E1C` in the retail MAIN ELF (`../work/SCUS_974.90`), every access to
`+0x5E00..+0x5E14` is inside the accessor block `0x001CEB60..0x001CED18` (the other hits
are `+0x5E18`/`+0x5E1C` of a different object at `0x001D1288..0x001D1688`, and `%lo`
halves of the globals `0x00465E00`/`0x00475E00`). The five overlays' disassembly in the
decomp has no such offset. `+0x5E04` is only stored: 1 by
`GameSceneTimeScaleUpdate_1cebe0` and `GameSceneTimeScaleReset_1cecf0`, 2 by the
double-step branch. That branch needs `+0x5E00` ≠ 0, and the only store to `+0x5E00` is
`sb $0` in `GameSceneTimeScaleReset_1cecf0`. No `addiu base, 0x5E00` or other base
reaches it. So in retail **double-step mode is dead and the count field is write-only**
(the capture agrees: `ts_dbl` 0, `ts_count` 1 throughout). The audit's question "does
setting it to two repeat the task table" is moot. The port can keep the field for data
layout and needs no catch-up logic for it.

The live time-scale path is `GameSceneGetTimeStep_1ceba0` (`+0x5E08 × +0x5E0C`): 49 call
sites in 42 functions, all MAIN: movement and collision (`ActionMgrMoveAll`,
`CharaMoveCollideMaybe`, `CharaUpdateMovement`, `GetScaledGravity`), the camera,
`BattleModeUpdate` (8), events (`EventCueStep`, `EventObjMgrUpdateAll`), map and texture
animation, effects, `SceneObjsStep`, `PlayTimeStep`, `GameDataTick`, the minimap,
`PadIdleTimerUpdate`, `StreamStep`, AI and script `GetSceneTimeStep` commands. These are
the frame-unit consumers: one tick = 1.0 at interval 2.

### Sound-sequence owner

`D_00481554` is written only by `SoundSetThreadedUpdate_1c3520`, called once, from
`SysBootInit_1c2ee0`, with 0. So **`MainLoop_1c2c10` always advances the sequences**,
after `GfxEndFrame`, with step = the feedback value (VBlank units). The capture: 9,861
main-loop advances, 0 from the frame worker, steps 2.0 (9,707), 1.0 (139 at interval 1),
4.0 (9) and 2.16..3.27 after slow frames. The `SysTickThreadMain_1c33f0` branch with
step 1.0 is dead. Sequences **do not advance** during `loadscreen` and `moviemodal`
frames (MainLoop is not iterating): sequence time freezes across the loading screen and
the opening FMV.

### VBlank services

- `SysTickThreadMain_1c33f0` woke on all 25,662 VBlanks; the readiness handshake never
  coalesced a wake (ready flag always 1 at the interrupt). It runs vibration and the
  sound-category fades with step 1.0 per VBlank, independent of the tick rate.
- `CdDiskWatchWakeIsr_17ff10` every 30th VBlank (`D_00481558` counter).
- The port must run these per **virtual** VBlank, never per present.

### Task table, pause, input, depth queries

- `TaskTableRun_1f5340`: exactly one run per main-loop tick in NORMAL (title ticks run
  none: the title loop has no task table). **2 restarts in 26,000 VBlanks**, both from
  `FieldControlActivate_27a960` (battle start and the return to battle after the
  tutorial), each giving a second run in the same tick.
- Pause step stayed 0. The three `PauseRequest(0)` calls were START presses in the
  tutorial (mode 11).
- Pad: `PadUpdate` runs at the end of each main tick (port 0 twice, port 1 once), so
  the game sees the pad only every **interval** VBlanks: at interval 2 a scripted press
  is first seen at the next odd/even counter in phase with the flips (CROSS scripted
  from 1,900 appeared at the 1,901 update). 63 ticks had a port-0 edge. A one-VBlank
  press can be missed, and a phase shift after a lag frame changes which counters are
  sampled.
- Depth query: only slot 0 is used, by `LensFlareDraw_2ed830` (a draw task). It writes
  on/x/y, `GfxEndFrame` reads 8×8 Z and stores the minimum, and the next frame's
  `LensFlareDraw` reads it. Slot 0 was on in every frame (z = −1 off-screen in 6,312
  frames, 0 in 6,227). It is presentation-only state: no update-side consumer.

### Loads and movies

- Overlay loads: TITLE at vbl 9 (7 vbl), NORMAL at 2,607 (25 vbl), synchronous in
  `MainLoop_1c2c10`.
- NORMAL's first load ran 594 `loadscreen` ticks (vbl 2,666..3,865) with 70 CD reads.
- The opening FMV is a `moviemodal` loop: 2,083 ticks, one `MovieDrawFrame` per tick,
  interval 2, vbl 3,912..8,076, 2,371 CD reads.
- The title background movie draws inside the main loop (925 frames over the title)
  and loops (vbl 678, 1,486, 5,105 in `title_idle`).
- Mid-scene loads in mode 11 appear as single long ticks (dvbl 7..10, 2,000..2,700
  lines of EE time, CD reads in the same tick).

### Harness lessons

- **The ELF loads in pieces.** `input.install` waited only for its own pad hook site;
  at `--speed 0.25` every hook site above 0x1B0000 was overwritten by the rest of the
  load and silently lost. `probe.py` now waits until every hook site holds the retail
  code, re-checks inside the frozen write, and reads every patch back.
- **Ring overflow.** At speed 0.5 the CPU thread did not idle at a vsync for 600..1,200
  VBlanks in places (FMV, battle). `--drain-s` drains at any point. One 883-VBlank
  stall (vbl 16,230..17,114, event mode) still lost 2,477 records in `newgame_battle2`:
  no drain ran either, so the harness itself was stalled (README "u32 wraps": 873 frames).
  `timing.py` lists these windows in the TSV header and the summary; tick counts inside
  them are merged.
- A second PCSX2 instance started mid-run changed the flow of the first
  (`newgame_battle_perturbed`); keep reference runs alone.

## What this means for the port

1. Clock: 59.94 Hz virtual VBlanks are right. Interval 2 almost everywhere: the logical
   tick is ≈ 29.97 Hz, and interval 1 only in the title load screen and (by source) the
   in-game menus.
2. Feedback: with zero-cost guest code the port's T0 reads ≈ 0, so fb = interval: the
   "nominal profile". That matches retail in more than 99.7 % of main ticks. Retail's slow frames
   have three effects the port won't reproduce without a cost model: the one-tick
   multiplier in unlocked modes, sequence steps above 2, and phase shifts of the VBlank
   grid. None changes the order or count of logic ticks.
3. The count field needs nothing. The thread-owned sequence path needs nothing.
4. Per-VBlank services (frame worker, disk watch, vibration, fades) stay on virtual
   VBlanks; sequences stay on MainLoop ticks with the feedback step.
5. Input must be delivered on ticks (the game samples it once per tick), so lockstep
   input has to be keyed to ticks, not VBlanks, when the two sides' tick phases differ
   (TIMING-LOCKSTEP.md).
