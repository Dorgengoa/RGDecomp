<!-- Copied 2026-10-12 from private/pc-port-research-01a116f0/frame-rate/DETACHED-FRAME-RATE.md. Source links point at that research folder's sources/ snapshot; in the port, the same files are under game/. -->

# Detached frame rate: source audit and PC-port recommendation

Date: 2026-10-07. Project: Rogue Galaxy, SCUS_974.90. Naming is treated as complete. This supplements [the PC-port research](../PC-PORT-RESEARCH.md).

## Decision

Design for independently paced rendering from the first host loop. Preserve the game's logical update cadence and frame-unit conventions, emulate its VBlank services independently of monitor refresh, and interpolate a separate presentation state. Target 60/120/144 Hz and uncapped presentation through that separation. Do not make high-rate simulation the first implementation target.

The audit found useful extraction points, but the existing engine is **not already frame-rate independent**. Its timestep compensates for some slow frames; it does not make faster calls safe. The main task registry separates update-oriented and draw-oriented work, but draw callbacks have persistent writes, and title mode uses a separate loop.

This is a source-grounded design recommendation, not a claim that detached rendering is implemented or proven across the game. Two original scalar functions were compiled and exercised on the host. No full game or emulator session was run for this audit.

## Evidence and reproducibility

The [evidence manifest](evidence.json) pins 67 source, assembly, header, and symbol-map files by SHA-256. Copies are under `sources/`; links below refer to these snapshots. Prior source inventory was used to locate functions rather than repeating a whole-corpus scan.

[Task-table extraction](extract_registry.py) reads the ELF32 load segments of `private/main-data-c3468400/build/link/SCUS_974.90`, requiring SHA-1 `87e9eff1d795c894fc09047270baab70d6a8d2c8`. It extracts 176 records from address `0x0044ECF0`, including the terminating record, plus the timing threshold. See [registry](task-registry.tsv) and [metadata](task-registry-metadata.json). The table is stronger evidence of dispatch order than guesses from function names. It does not prove every entry executes in every mode.

Source comments can be stale. For example, the camera timer comment describes `dt` as `1/30`, while its body adds `dt / 30` and the scene defaults to a factor of one. This report uses executable bodies and explicit data values, and does not treat a comment saying “matching” or “parked” as fresh build verification.

## Current timing paths

### Main frame and graphics feedback

[MainLoop](sources/src/main/sys/MainLoop_1c2c10.c), lines 103–116, begins the draw list, polls disc status, invokes the mode callback, ends the graphics frame, conditionally advances sound sequences, then services both pads. These actions share the outer frame iteration. Pad servicing is outside the sound ownership conditional.

The inspected two-entry callback table points to gameplay `0x001F5CF0` and overlay address `0x004F0B20`. [GameFrameStep](sources/src/main/sys/GameFrameStep_1f5cf0.c) calls [GameFrameUpdate](sources/src/main/sys/GameFrameUpdate_27c4c0.c), which updates scene time and input, handles pause state, repeatedly dispatches until stable, then draws the pause overlay. The pause drawing outside the task registry must also move into the presentation boundary.

[GfxEndFrame](sources/src/main/gfx/GfxEndFrameMaybe_141c20.c), lines 93–103 and 175–179, measures EE timer and VU-related work, divides by the environment timing divisor, takes the larger value, and clamps the stored frame-time value to `[interval, 2 × interval]`. Those samples are taken before the presentation wait. This value is a legacy normalized workload measurement, not arbitrary host elapsed seconds.

The [reference assembly at 0x00143650](sources/asm/matchings/main/FUN_00143650.s), lines 22–55, compares the virtual VBlank count with the environment interval, calls `WaitVsyncCount`, and stores a new count. Preserve that logical clock contract when replacing hardware presentation; host swapchain completion must not become its clock source.

### Scene timestep and per-call counters

[GameSceneTimeScaleUpdate](sources/src/main/sys/GameSceneTimeScaleUpdateMaybe_1cebe0.c) resets the scale factor and count field to one. With scaling unlocked and unsuspended, it computes `f = graphics_feedback / 2`. It changes behavior only when `f > 1`: either assigns the larger scale or, in the named double-step mode, writes two to `+0x5E04` when `f > 1.1`. The threshold was read from the ELF as `1.100000023841858`.

[GameSceneGetTimeStep](sources/src/main/map/GameSceneGetTimeStep_1ceba0.c) returns the product of the two floats at `+0x5E08` and `+0x5E0C`. These are frame-unit scales. Passing `1/120` seconds to existing consumers would change their units. Calling the old frame loop at 120 Hz with nominal scale one would also change behavior.

The countdown at `+0x5E10` decrements once per invocation, even before the locked/suspended checks. Other fixed-call behavior exists independently of this timestep. The count field's complete indirect consumer chain was not established; do not assume that setting it to two repeats the entire task table twice.

### Cadence changes and VBlank services

[SceneOverlayModeOn](sources/src/main/sys/SceneOverlayModeOnMaybe_288340.c) sets interval one and locks the scene time scale; [SceneOverlayModeOff](sources/src/main/sys/SceneOverlayModeOffMaybe_288300.c) restores interval two and unlocks it. The title overlay has the same explicit [one-interval setup](sources/src/overlays/title/title/title_TitleSetMenuFrameModeMaybe_4eaa40.c) and [two-interval restoration](sources/src/overlays/title/title/title_TitleRestoreFrameModeMaybe_4eaa00.c).

This supports one- and two-VBlank scheduling modes. It does not establish a single universal simulation frequency. “Approximately 30 Hz gameplay / 60 Hz menus” is a working interpretation, pending a reference trace of video mode, actual VBlank frequency, interval changes, skipped waits, and task execution. Keep the clock rate configurable and rational; do not bake an unverified exact 30.000 or 60.000 Hz into gameplay conversions.

[SysVblankCallback](sources/src/main/sys/SysVblankCallback_1c33a0.c) signals the frame worker and wakes the disc watchdog every 30 callbacks. [FrameThread](sources/src/main/sys/FrameThreadMaybe_1c33f0.c) advances vibration and sound-category fades, and conditionally advances sound sequences with `1.0`. MainLoop advances those sequences when the opposite ownership flag is selected. [FrameThreadSignalIsr](sources/src/main/sys/FrameThreadSignalIsrMaybe_1c34f0.c) uses a readiness handshake, so worker wakes can coalesce under load.

A 144 Hz monitor must not imply 144 legacy VBlank callbacks per second. Preserve one owner for sequence advancement and measure worker ordering/coalescing before replacing it with an always-catch-up service loop.

## Where to split execution

The extracted registry has update/service entries before index 92, a separator at 92, then **82 draw-region entries at indices 93–174**, beginning with `Update Draw Info`; index 175 terminates the table. Earlier entries cover character logic, movement, event processing, effects, menus, camera, fades, loading, and sound. [TaskTableInit](sources/src/main/sys/TaskTableInit_27c310.cpp) copies and hashes the records into the mutable task table.

Use that boundary to organize the audit, not as a proof of purity. [TaskTableRun](sources/src/main/sys/TaskTableRun_1f5340.c) checks enable flags and immediately returns if a callback changes the task list. [GameModeDispatch](sources/src/main/sys/GameModeDispatch_27c670.c) changes modes, temporarily masks tasks during pause, and returns the task-runner result. Preserve restart order and exactly the reference side effects within each logical tick; extra presents must not rerun the dispatcher. Do not accidentally remove intentional same-tick restarts either.

[TitleFrameStep](sources/src/overlays/title/title/title_TitleFrameStep_4f0b20.c), lines 34–78, handles movie pause/resume and input, calls title update and title draw together, and services additional background work. Title requires its own extraction. Gameplay's task split alone will not detach it.

| Area | Source finding | Port treatment |
| --- | --- | --- |
| Character movement | [ActionMgrMoveAll](sources/src/main/chara/ActionMgrMoveAllMaybe_231720.cpp), lines 421 and 496, passes scene time into movement after building ordered collision/attachment context. | Keep movement and collision on the logical update schedule. Interpolate only the displayed transforms. |
| AI / navigation | [TaskCharaThink](sources/src/main/ai/TaskCharaThink_1fa9c0.c) increments a counter and branches on its call count. | Retain its logical cadence; multiplying calls by presentation FPS changes decisions/work scheduling. |
| Object updates and sound events | [SceneObjsStep](sources/src/main/obj/SceneObjsStep_1f97a0.cpp) mixes timestep-driven virtual updates, once-per-call integer counters, queued sound consumption, and flag clearing. | Invoke only as scheduled simulation work. It is not an interpolation helper. |
| Animation / combat events | [CharaFireAnimEvents](sources/src/main/chara/CharaFireAnimEventsMaybe_20f0b0.c) traverses animation phase intervals, handles wraparound, fires collision/event callbacks, and updates flags and timers. | Keep authoritative phase/event traversal on simulation ticks. Sampling a render pose must not fire attacks, sounds, or scripts again. |
| Effects | [TaskStepProgEffect](sources/src/main/effect/TaskStepProgEffect_2d8710.c) calls [EffectTimedSlotTick](sources/src/main/effect/EffectTimedSlotTick_2d4c10.c) with literal `1.0`. | Age and spawn effects at the legacy rate; interpolate particle/ribbon presentation independently. |
| Camera | [TaskUpdateDrawInfo](sources/src/main/gfx/TaskUpdateDrawInfo_2f6ff0.cpp) copies the camera before applying shake and generating view packets. [CameraShakeTimerStep](sources/src/main/camera/CameraShakeTimerStep_305860.c) advances time separately. | A useful place to introduce a presentation camera. Preserve the simulation camera for collision, targeting, and sound-listener behavior. Audit aspect/global-state writes too. |
| Draw-side writes | [TaskDrawCharaPre](sources/src/main/chara/TaskDrawCharaPre_1f8ba0.cpp), lines 211–252 and 311–316, writes table/character fields and calls light-blend target setters. [LightningBoltDraw](sources/src/main/effect/LightningBoltDraw_2d67a0.c) configures a persistent ribbon and passes stack-built nodes into its immediate draw path. | Classify each write as authoritative, persistent presentation history, or disposable scratch. Move it or isolate it before repeated rendering. Do not enqueue borrowed stack pointers for asynchronous rendering. |
| Graphics readback | GfxEndFrame reads four optional 8×8 depth regions and stores each minimum result into persistent slots. | Trace consumers and preserve the required view/tick/result ordering. Until classified, assume presentation-rate-dependent readbacks could affect behavior. |
| Input and UI | [PadBindingsUpdate](sources/src/main/pad/PadBindingsUpdateMaybe_15fcd0.c) distinguishes held, triggered, and released values; [pad-service assembly](sources/asm/matchings/main/FUN_001843a0.s) contains persistent input state/timers. | Poll host devices responsively, queue timestamped transitions, and deliver edges on a defined logical tick once. Preserve held state, repeat timers, disconnects, and mode changes. |
| Pause / play time | [PauseStepUpdate](sources/src/main/sys/PauseStepUpdate_2f5fb0.cpp) includes interval-counted work; [PlayTimeStep](sources/src/main/sys/PlayTimeStep_2f7570.c) multiplies interval by scene timestep. | Define separate world/UI/service pause behavior. Neither play time nor repeat rates should follow the number of presents. |
| Movies | [VideoDecPutTs](sources/src/main/movie/VideoDecPutTs_1d2750.c) and [VideoDecTimeStamp](sources/src/main/movie/VideoDecTimeStamp_1d4e60.c) preserve timestamp data; [MovieFrameQueueSendNext](sources/src/main/movie/MovieFrameQueueSendNextMaybe_1d4b20.c) consumes the output queue. The inspected [MovieVblankHandler](sources/src/main/movie/MovieVblankHandler_1d4c90.c) does not contain a playback scheduler. | Use the planned decoder replacement with media timestamps and an explicit audio playback clock. Exact original A/V synchronization remains a separate runtime validation item; do not infer it from the handler's name. |

This is a focused audit of the main loop and representative high-risk paths, not exhaustive certification of every draw callback, RNG use, virtual call, or overlay.

## Executed experiment

[run_timing_probe.py](run_timing_probe.py) compiles the unchanged captured time-scale and effect-timer bodies into an x64 DLL using MSVC 19.29, with small stubs for their dependencies. The wrapper defines only test state and the ELF-derived threshold. It does not emulate the hardware timer, dispatch loop, or renderer.

**All 13 scene cases and the effect-expiry assertion passed.** See [build log](timing-probe-build.log), [wrapper](timing_probe.c), and [results](timing-probe-results.json).

| Input / scenario | Observed result |
| --- | --- |
| Feedback 0, 0.25, 0.5, 1, or 2; base scale one | Returned effective scale remains one; count remains one |
| Feedback 3 or 4; ordinary mode | Effective scale 1.5 or 2 |
| Named double-step mode, feedback 2.1 / 2.3 | Scale stays one; count changes from one to two above the threshold |
| Locked or suspended scaling | Factor/count remain one; this does not by itself prove world simulation is paused |
| Countdown one / two, initial scale 0.5 | First expires and restores scale one; second decrements and preserves scale 0.5 |
| Active effect, initial age zero, increment one | Reset callback after exactly 16 invocations |

If that effect were called once per present, its illustrative lifetime would be 0.533 s at 30 FPS, 0.267 s at 60, 0.133 s at 120, and 0.111 s at 144. Those are arithmetic consequences of the measured call count, **not measured in-game durations**. They demonstrate why multiplying frame-loop calls is unsafe even if some movement code accepts a timestep.

## Proposed host architecture

Keep four explicit clocks/contracts: monotonic host scheduling time, virtual legacy VBlank time, mode-specific logical update time, and audio/media playback time. Display refresh is a presentation policy, not the source of game time.

Use elapsed host time to schedule discrete logical work. Maintain the mode's one-/two-VBlank relationship and internal frame-unit parameters. Keep renderer workload telemetry separate from legacy timing feedback. For the first faithful slice, feed a controlled nominal timing profile; record original slow-frame behavior separately before choosing how much to reproduce. Avoid simultaneously doing host catch-up and injecting renderer-induced slow-frame scaling, which could compensate twice.

A fixed-step accumulator with interpolation is a standard foundation; Glenn Fiedler describes the accumulator, interpolation, and overload tradeoff in [Fix Your Timestep](https://gafferongames.com/post/fix_your_timestep/). Rogue Galaxy still needs the mode and service contracts above layered onto it.

After each logical tick, publish previous/current presentation snapshots with tick timestamps, stable entity IDs and generations, camera state, transforms/poses, effect state, and retained resource handles. Use a single thread initially to simplify ownership; detached rate does not require concurrent simulation and rendering.

At each presentation, interpolate eligible positions, rotations, skeletal poses, camera parameters, and effect presentation from snapshots. Generate updated model/view inputs **before** skinning, VU work, and packet emission. Replaying identical completed DMA/GIF packets at 120 Hz repeats the same poses and will not produce smooth 120 Hz motion. Keep packet capture/replay as a graphics correctness milestone while designing the renderer to retain the earlier transform/pose boundary.

Do not interpolate across teleports, camera cuts, animation discontinuities, scene loads, or entity-ID reuse. Reset history there. Snapshot resource ownership must outlive asynchronous GPU consumption, overlay unloads, and draw-heap resets. Separate temporal render history such as blur from authoritative game state.

Previous/current interpolation introduces a one-logical-tick presentation delay relative to the simulated timeline. Measure end-to-end latency; responsive device polling does not eliminate that delay or raise gameplay's decision rate. A later presentation-only camera response can reduce perceived latency, but needs its own collision/aiming consistency design. Do not promise 120 Hz simulation responsiveness from 120 Hz rendering.

Catch up in bounded discrete steps with explicit telemetry when host work falls behind. Avoid arbitrarily large physics deltas or silently dropping authoritative events. Define focus loss, long stalls, loading, and pause policy per clock. A frozen world can still require menus, audio, input, and service work. For mode transitions with different tick spacing, use snapshot timestamps and reset interpolation history where needed instead of reusing an old accumulator divisor.

## Implementation order and acceptance gates

1. **Instrument the reference timing contract.** Log virtual VBlank index, interval, frame feedback, scene factors/count field, pause/mode flags, task calls/restarts, pad edges, sequence owner, service wakes, and depth-query consumption. Capture title, field, combat, menu, pause, movie, warp/load, and an overloaded frame. Establish exact frequency and the count-field consumer chain. This is the next concrete implementation task.
2. **Build the host clock and scheduling boundary with rendering at legacy cadence.** Preserve logical ordering, counters, sound ownership, and mode changes. Make renderer cost unable to change game time. Keep a reference timing mode for comparison. Pass identical tick-indexed input, RNG seed, and controlled asynchronous completions through the reference and host slice.
3. **Separate presentation writes and snapshots.** Start with a field character and camera; then title/UI, animation, and effects. Include pause drawing outside the registry. Audit all reachable draw callbacks before claiming they can run freely. Classify depth readbacks and resource lifetimes.
4. **Enable high-rate presentation.** First interpolate camera/root transforms, then poses and effect visuals. Demonstrate real intermediate motion at 60/120/144 Hz and uncapped output. Extend to the remaining overlays after their update/draw boundaries pass the same tests.

| Verification | Required evidence |
| --- | --- |
| Render-rate independence | Same logical-tick state and event sequence for controlled inputs at 30/60/120/144, uncapped, and jittered rendering; include renders with zero updates and frames requiring multiple updates |
| Combat / animation | Same collision outcomes, attack windows, damage, AI decisions, phase-wrap events, sound triggers, and effect spawn/expiry ticks |
| Input / UI | One action per edge even during catch-up; no lost quick press/release; stable held/repeat rates; disconnect/reconnect and mode-transition coverage |
| Audio / movie | One sequence owner, stable fades/vibration/play-time behavior, no A/V drift or skip/completion regression when changing FPS or pausing |
| Presentation isolation | Re-render one snapshot repeatedly without changing simulation/RNG/event queues; snapshots survive resource recycling and overlay changes |
| Visual quality | Smooth camera, character pose, trails and effects; no ghosting through cuts/teleports; temporal effects scale with presentation time only where intentionally designed |
| Load / overload | Bounded catch-up, recorded time policy, stable mode/task restart order, correct depth-query result ownership |

For cross-architecture comparisons, distinguish logical-event equality from float tolerances and normalize pointer/padding fields before hashing. Do not assume x64 and EE floating-point execution is bitwise identical. Within one controlled host build, varying presentation frequency should not change authoritative results.

## Remaining uncertainties

Exact active video timing and mode cadence, every consumer of the scene count field, original VBlank worker behavior under load, depth-slot consumers, all draw-time mutations/RNG, all overlay-specific loops, and original media synchronization still need traces or broader call-graph auditing. No performance number or whole-game high-FPS compatibility claim follows from this pass.

The architectural decision is nevertheless actionable now: retain legacy logical timing, put independently paced snapshots and interpolation into the renderer design, and make clock isolation a gate before high-FPS presentation. This should be part of the initial PC-port foundation, not a frame-cap patch after renderer completion.

Rerun the executed checks from `..`:

```powershell
python private/pc-port-research-01a116f0/frame-rate/extract_registry.py
python private/pc-port-research-01a116f0/frame-rate/run_timing_probe.py
```
