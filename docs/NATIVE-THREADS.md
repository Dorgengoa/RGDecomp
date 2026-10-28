# Native threads and timing (de-emulation lane: kernel)

PLAN.md D9 / "Native end state": *"EE kernel (fibers, semaphores, alarms, virtual
VBlank), spin-loop hooks -> Native game loop / host threads with explicit sync; host
clock + fixed-step logic tick; no spin loops."* Same pattern as NATIVE-FS / NATIVE-AUDIO:
census script, design, native service, game-side overrides at the highest sensible
boundary, the old path kept as the oracle behind a switch, verification against it.

Status (2026-10-18, evening): **frame-driven mode no longer needs `src/ps2/kernel`.** It is
the native kernel table (section 3e: game-visible thread / semaphore / handler ids, the event
list, the flows, in `src/native/threads`); the HLE is the oracle only, behind a dispatcher in
default builds and **not linked at all in RG_NATIVE_ONLY builds** (section 3f: link audit
`--forbid iop,kernel` PASS). **Paced mode** (section 3g): the frame driver's VBlank phases follow
the host clock through a bounded fixed-step accumulator (`display.pacing = host`, the Default
preset); the retail cadence stays the Original preset and every run without a host clock.
Run hash of a native run unchanged by all of it (31,700-field golden route, both builds).

Earlier status (2026-10-18, late): **slices 1-5 implemented and verified.** `RG_THREADS=native`
(the default) now runs **without the EE scheduler**: the kernel's frame-driven mode
(section 3d) with two game coroutines (main and the loading screen) at fixed addresses,
every other game thread a driven step, interrupts as explicit calls in the driver's pass,
logic time moved only by waits (no DMA / register costs: nominal `T0_COUNT`). Power-on to
the first battle: **same 24 milestones at the same VBlank as `RG_THREADS=hle`, 0 of 23
segments with a different main-tick count**; ticks = VBlanks (0 boot gaps, was 39); native
fixtures title / field / battle reproduce at +300. The slices 2-3 driver over the HLE
scheduler stays available as `RG_THREADS=frame`; `hle` is unchanged (run hash to field 9,000
with `RG_TIMING` still `326c86ff3a777910`). What is left of the kernel HLE on the native path:
section 5.

- **Slice 5** (2026-10-18, `RG_THREADS=native`): ps2k `cfg.native`, section 3d.
- **Slice 4** (2026-10-18): the loading screen is the driver's second game coroutine, form
  (2) of section 3c (no `GfxEndFrame` split, no gfx override).

- Slice 1 (2026-10-17, now `RG_THREADS=service`): the tick thread as a fiberless service
  thread placed by the HLE scheduler; run hash identical to `hle` (identity check).
- **Frame driver** (`RG_THREADS=native`, the default): every wait of a game flow is a
  driver point (`WaitVsyncCount`, `DelayThread`, the loading-screen condition waits, spin
  hints). Seven game threads are *driven*: parked kernel thread objects whose loop bodies
  run as plain steps at driver points (tick, stream slot, disk watch) or at once on the
  game thread that signals them, where the HLE switched to them (file requests, 3 sound
  streams). The 1.7M `DelayThread(10)` polls of `GameSessionInit` are condition waits
  (4 waits, 2,053 wakes); file requests read through native-FS async host jobs started
  when a request is queued. Power-on to the first battle: **same 24 milestones at the same
  VBlank, 0 of 23 segments with a different main-tick count, same 338 reads (8 reordered)**
  as `RG_THREADS=hle`; title/field/battle save states reproduce the power-on run at +300
  (battle +300 now checked: the battle crash is fixed). Loading screen host cost
  2.66 s -> 0.41 s of EE time for its 1,028 fields.

| Part | Where |
| --- | --- |
| Census | `tools/native/thread_census.py` (`static`, `dynamic`) -> `census/native_threads_static.tsv`, `census/native_threads_dynamic.tsv`; recorder `src/sce/kernel/kcensus.c` (`RG_KCENSUS=path`) + kernel census tap (`ps2k_set_census_tap`, `ps2k_peek_*`) |
| Native kernel table | `src/native/threads/rg_nk.c`, `rg_nk_irq.c`, `rg_nk_ss.c` (`rg_native_kernel`; `rg_native_kernel_ps2k` in RG_NATIVE_ONLY builds), API `kapi/ps2k.h` (+ generated `ps2k_api.inc` / `ps2k_rename.h`: `tools/native/thread_api.py`), coroutines `fiber/` (`rg_native_fiber`), dispatcher `src/ps2/kernel/kdispatch.c` (section 3e) |
| Paced mode | `src/native/threads/rg_pace.[ch]` (accumulator), `src/runtime/runtime.c` (`pace_*`: wait before a phase, present decision, `RG_PACE*`), setting `display.pacing` (section 3g) |
| Native service | `src/native/threads/` (`rg_native_threads`): `rg_threads.c` (`RG_THREADS=native|service|hle`, slice 1 registry, `RG_THREADS_LOG=1` exit lines), `rg_frame.c` (the frame driver: conversions registry, driver points, sync runs, condition waits, field-end drain, starvation report); game view `include/port/native_threads.h` |
| Kernel support | `src/ps2/kernel/kcore.c`, `kirq.c`: the frame-driven mode (`cfg.native`, `kn_step`, step context, phase / parked / block hooks; docs/KERNEL.md "Frame-driven mode"); service threads (`ps2k_thread_set_service`, slice 1); driven threads (`ps2k_set_start_hook`, `ps2k_thread_set_driven`, `ps2k_driven_wait/take/exit`), the signal hook (`ps2k_set_signal_hook`), poll waits (`ps2k_wait_poll`, `ps2k_activity`), `ps2k_vblank_end_count` |
| Game side | overrides: `sys/SysTickThreadMain_1c33f0.c`, `sys/SysTickThreadStart_1c3470.c`, `sys/WaitVsyncCount_15de90.c`, `sound/SoundStreamSlotThreadMain_1bc520.c`, `file/CdDiskWatchThread_17fdc0.c` (split; was the native-FS lane's), `sound/SoundCmdWorkerThread_1b6c10.c`, `sound/SoundThreadMain_1b6260.cpp` (slice 5), `file/FileReqThread_182c30.c`, `file/FileReqSubmit_1827a0.c`, `sound/SoundStreamThreadMain_1c1050.c`, `sound/SoundStreamProcessCmds_1c05f0.cpp`, `ui/LoadingScreenRequestEnd_343100.c`, `ui/LoadingScreenIsFinished_343090.c`, `ui/LoadingScreenIsClosed_3430b0.c`, `thread/LoadingScreenStop_3431e0.c` |
| Other wiring | `src/sce/kernel/eekernel.c` (`DelayThread` -> `rg_frame_delay`, `RotateThreadReadyQueue` -> `rg_frame_yield`), `src/sce/graphics/libgraph.c` (`sceGsSyncV`: a driver point after its wait), `src/ps2/spin/spin.c` (a spin hint is a driver point; natively its charge is a 32-cycle timed wait), `src/runtime/runtime.c` (`rg_threads_field_end()` after each field; `kc.native`, the native-audio fallback, DMAC / hwbus costs 0 natively) |
| Oracle | the EE kernel HLE: `RG_THREADS=hle` runs every game thread on a fiber and the generated waits; `RG_THREADS=frame` = slices 2-3 (driver over the HLE scheduler) |
| Compare | `tools/native/thread_compare.py` (runs per mode: run hash, shots, timing record); then `tools/trace/timing.py align --nowrap`, `tools/native/fs_census.py stream` |
| Tests | `rg-kernel-tests` `service_thread`, `poll_wait`, `driven_thread`, `frame_driver` (frame), `frame_native` (slice 5), `pace` (+ controls `pace_control`, `service_thread_control`, `poll_wait_control`, `frame_native_control`), ctest label `kernel` |
| Diagnostics | `RG_THREADS_LOG=1` (driven threads, flows started, steps per conversion, sync runs, condition waits, yields, VBlank gaps without a driver point; native: the kernel's passes / flow switches / charge waits); `RG_FRAME_KEEP=name,...` keeps the named conversions threads (frame: HLE threads; native: flows) for bisecting; `RG_FRAME_DEBUG=1` traces the signal hook |
| Tools | `tools/native/thread_compare.py` (modes side by side: run hash, shots, milestones, `--windows` step-time + process CPU), `tools/native/thread_perf.py` (`save` per-mode states, `measure` CPU per field from loads, modes interleaved), `tools/native/thread_sample.py PID` (sampling stack dump of a running rg-game from the link map: hang / spin finder, no debugger needed) |
| Build | `build/nthreads-i686`: `powershell -File tools/native/audio_build.ps1 -BuildDir build/nthreads-i686 -Targets rg-kernel-tests,rg-game` (the audio lane's wrapper splits a comma list; `-Reconfigure` after adding an override) |

## 1. Census

### How to rerun

```
python tools/native/thread_census.py static                       # no build; ~10 s
set RG_KCENSUS=out\nthreads\run.kcensus.tsv                        # any rg-game run, any mode
build\nthreads-i686\rg-game.exe --headless --fields 9000 --input tools\trace\goldens\newgame_battle.input.txt
python tools/native/thread_census.py dynamic out\nthreads\run.kcensus.tsv --map build\nthreads-i686\rg-game.map --label poweron9000
```

`RG_KCENSUS` also works on a fixture run (`run_from.py title|field|battle`): it records
from the load on (the recorder is host state). The recorder writes one row per SDK
kernel call made through `src/sce/kernel/eekernel.c` (with the caller's return address,
named from the link map: so every row names its game function) and per kernel-side
event (thread switch with the thread's entry, handler / alarm call with its function,
kernel-private wait, timer read, VBlank edge). It only peeks at kernel state, so a census
run is the same run (run hash unchanged). Rows made by port code that calls `ps2k_*`
directly (SIF, libcdvd, DelayThread's internal sema) appear only as switches and handler
calls. About 650 rows per field (185 MB for 9,000 fields); `dynamic` reads it in ~1 min.

### Static (compiled sources, `census/native_threads_static.tsv`)

412 kernel-API call sites in 136 functions (game/ with overrides substituted). Threads
the game creates (8 creators; the three movie threads `DefMain`, `VideoDecMain`,
`MovieReadThread` are already gone: the movie lane's `MoviePlayerStart` override):

| Entry | Creator | Priority (P = `D_0047DF30` = 20) |
| --- | --- | --- |
| `FileReqThread_182c30` | `FileReqThreadInit_182af0` | P-1 = 19 |
| `SoundCmdWorkerThread_1b6c10` | `SoundSysInit_1b6f70` | P-10 = 10 |
| `SoundThreadMain_1b6260` | `SoundThreadStart_1b6160` | 9 |
| `SoundStreamSlotThreadMain_1bc520` | `SoundRpcInit_1bc840` | P-5 = 15 |
| `SoundStreamThreadMain_1c1050` (x3) | `SoundStreamInit_1c0ea0` | 15 |
| `CdDiskWatchThread_17fdc0` | `CdDiskWatchInit_17ff70` | P-5 = 15 |
| `SysTickThreadMain_1c33f0` | `SysTickThreadStart_1c3470` | P-2 = 18 |
| `LoadingScreenThread_343510` | `LoadingScreenStart_343240` | 20 (cfg) |
| main (`Main_15e700` -> `MainLoop_1c2c10`) | crt0 | 1, then 20 (`Main_15e700`) |

Handlers: `sceGsSyncVCallback(GfxVblankStartHandler_15df20)` (VBLANK_START, tail),
`AddIntcHandler(5, Vif1IntcHandler_15e170, -1)` (`Vif1DmaStart_15e070`, every frame),
`AddIntcHandler(3, SoundVblankIntrHandler_1bd6f0, -1)` (`SoundRpcInit_1bc840`),
`SetVblankCallback_15df10(SysVblankCallback_1c33a0)` (called from the VBLANK_START
handler). Timer accesses: `T0_MODE = 0x83` (`GfxSysInit_15dd20`), `T0_COUNT` read in
`GfxEndFrame_141c20`, `GfxFlipBuffersMaybe_143650` (x2) and `Vif1IntcHandler_15e170`,
written 0 in `GfxEndFrame`. No INTC/DMAC register is polled by game code (SPIN.md).

### Dynamic (golden input, power-on to field 9,000: boot, title, NEW GAME, NORMAL load, opening FMV, first field)

Threads (11), with what each does and how it synchronises:

| T | Entry (prio) | Switches | Body / sync |
| --- | --- | --- | --- |
| 1 | main (20) | 192/field | `MainLoop_1c2c10`: one tick per frame; ends each frame in `GfxEndFrame` -> `GfxFlipBuffersMaybe` -> `WaitVsyncCount_15de90` (sema `GfxSysInit`#1, signalled by the VBLANK_START handler when `D_004810C0` is set; 7,870 blocking waits); `sceGsSyncV` 98 times (`PadWaitReady`); **`DelayThread(10)` polling: 1,697,100 calls in `GameSessionInit_1f5d80`** (waits for `LoaderCountQueued`, then for the loading screen's timer > 120) plus `DataTableBubbleSort_368220` 15,488, `CfgVmRun`, `DataTableRunCfg`, `LoadingScreenStop` (100 us), `MapLoadFromGameDataAndWait`, ...; `ThreadYield` (`RotateThreadReadyQueue(20)`) 12,060 (movie VoBuf/VideoDec waits); file-layer mutexes; the per-frame VIF1 handler add/remove + its sema (`Vif1DmaStart` / `Vif1DmaHandlerShutdown`) |
| 2 | `FileReqThread` (19) | 0.24/field | async read queue: `WaitSema(req)` (2,127 blocking), reads a request with the file-slot mutexes, sets done flags under DI/EI; main polls the flags (`FileReqThreadResume` / `FileReqAnyIncomplete`: PollSema+SignalSema) |
| 3 | `SoundCmdWorkerThread` (10) | 1 | idle with `RG_AUDIO=native` (the queue runs on the caller) |
| 4 | `SoundThreadMain` (9) | 1 | idle with `RG_AUDIO=native` |
| 5 | `SoundStreamSlotThreadMain` (15) | 1.00/field | woken by the VBLANK_END handler (`iPollSema`/`iSignalSema`), updates 4 PCM stream slots; 154k inner mutex Wait/Signal calls (`SoundStreamSlotUpdate`), none blocked on this route |
| 6 | `CdDiskWatchThread` (15) | every 30th VBlank | woken by `CdDiskWatchWakeIsr` (VBLANK_START callback); takes the file lock (the native-FS override removed the disc poll) |
| 7 | `SysTickThreadMain` (18) | 1.00/field | woken every VBlank by `SysTickThreadSignalIsr` (ready-flag handshake, never coalesced); pad vibration counters + sound-category fades, step 1.0 per VBlank; **slice 1: native step** |
| 8-10 | `SoundStreamThreadMain` (15) x3 | 0.04-0.15/field | stream command loops (`SoundStreamProcessCmds`): command sema + file reads |
| 11 | `LoadingScreenThread` (20) | 0.11/field | a second frame loop while main loads: `DrawListFrameBegin` / `LoadingScreenFrame` / `GfxEndFrame` (its own `WaitVsyncCount`, 1,030 waits) |

Handlers delivered: VBLANK_START `GfxVblankStartHandler` 8,967 (1/field), VBLANK_END
`SoundVblankIntrHandler` 8,969, VIF1 `Vif1IntcHandler` 4,515 (one per main-loop frame:
latches `T0_COUNT` into `D_004810B4`, signals the frame's sema), DMAC SIF0
`sif0_dmac_handler` 56 (port SIF), and the alarm `delay_alarm_cb` **1,713,843** (every
`DelayThread`). Timer reads: `T0_COUNT` 1.33/field on main, 0.5/field in the VIF1
handler, 0.17/field on the loading screen.

Battle (fixture `battle`, 90 fields, native mode, appended to the TSV as `battle+90-native`):
main 2 switches/field (interval 2), `FileReqThread` 0.5/field and one stream thread
1/field (battle streaming), stream slot and tick 1/field, disk watch every 30th VBlank;
VIF1 handler once per main frame; `T0_COUNT` 1.5/field on main. No other thread, handler
or `DelayThread` site appears.

Semaphore classes found: mutexes (init 1: file slots, pad, VIF1 handler, sound stream
slots), VBlank signals (vsync, tick, disk watch, stream slot), request/reply (file
requests, sound worker), and per-call semas (DelayThread, `Vif1DmaStart`'s per-frame
sema, SIF). Rows per thread / sema / handler / call site: `census/native_threads_dynamic.tsv`.

## 2. Design: the native model

### What the HLE does that the native model must not need

- An EE scheduler: priorities 0..127, ready queues, preemption at "defined points"
  (every kernel call, EI, model charges), interrupt latch/mask/EIE, handler context.
- A bus-cycle virtual clock (147.456 MHz) advanced by idle jumps **and by modelled costs**
  (DMA charges in `dmac.c`, hardware reads in `hwbus.c`, `libdma`, `libmc`, SIF), with
  VBlank edges as clock events and `T0_COUNT` computed from it.
- One host fiber per game thread, a 2-3 kB TCB per thread, sema and alarm ids that leak
  into game state.

### End state

1. **One game coroutine + a host frame driver.** The game's main flow
   (`Main_15e700` -> `MainLoop_1c2c10`, and every nested frame loop: the title, the modal
   movie, menus) runs on one fixed-address game stack. Every place where it waits for
   time (`WaitVsyncCount`, `sceGsSyncV`, `DelayThread`, `ThreadYield`) becomes a call into
   the frame driver (`rg_frame_wait(kind, arg)`), which runs everything that would have
   run meanwhile (below) and returns. Inverting the game's nested loops into host-driven
   ticks is not needed: the game keeps its own loops; the driver is what "waiting" means.
   The single game stack is kept (rather than running the game on the host thread) only
   because save states need a game stack at a fixed address that holds no host frames
   (TEST-FIXTURES.md "Fibers"): it is the native hook that replaces the EE fiber arena.
   It is one coroutine switch per frame wait, no scheduler, no priorities, no EE ids.
2. **Threads become steps.** Each other game thread is converted by class:

   | Class | Threads | Native form |
   | --- | --- | --- |
   | VBlank service | `SysTick`, `CdDiskWatch`, `SoundStreamSlot` | a step function called in the VBlank phase, in the HLE's order (handlers first, then steps by the old priority: disk watch 15, stream slot 15, tick 18) |
   | Command/stream workers | `SoundCmdWorker`, `SoundThread` (already idle under native audio), `SoundStream` x3 | the command becomes a direct call (as native audio did for the sound queue); stream reads become host I/O jobs (NATIVE-FS async) completed at the frame phase, the stream step consumes them |
   | Request queue | `FileReqThread` | `FileReqSubmit` queues a host I/O job; completion sets the request's done flags at a defined point of the frame driver (the game already polls the flags) |
   | Second frame loop | `LoadingScreenThread` | a step that draws one loading-screen frame; the frame driver calls it from the main flow's waits while a load is in progress (`GameSessionInit`'s `DelayThread` polls, `LoaderTick` waits): exactly the frames retail showed while main was blocked |
3. **Sync primitives** keep their game-visible ids only as long as game code stores them.
   With no preemption inside a step, every mutex (init 1) is uncontended and becomes a
   no-op; signal semas become flags that the driver turns into step calls;
   request/reply semas disappear with the direct calls. `DI`/`EI` become no-ops (nothing
   can interrupt).
4. **Handlers become frame-phase calls.** VBLANK_START: the counter/flip part of
   `GfxVblankStartHandler` and `SysVblankCallback` (tick + disk-watch wake); VBLANK_END:
   `SoundVblankIntrHandler` (stream-slot wake); VIF1: the per-frame "chain done" latch
   moves to the native renderer's end-of-frame (with no VIF there is nothing to wait
   for; `Vif1DmaHandlerShutdown`'s sema wait is satisfied at once).
5. **Timing.** Four clocks (PLAN "Unlocked frame rate"): host time, VBlank time, logic tick,
   audio time. The frame driver owns VBlank time as an exact rational field counter
   (59.94 Hz, the same field the HLE uses) and decides with a bounded accumulator how
   many VBlank phases are due per host frame; deterministic mode (tests, traces, fixtures)
   advances one field per wait with no host clock input. `T0_COUNT` reads (frame-time
   feedback in `GfxEndFrame`, `GfxFlipBuffersMaybe`, the VIF1 latch) get the logic cost of
   the frame in field units from the driver: in deterministic mode the nominal profile
   (fb = interval, TIMING-REFERENCE.md "What this means for the port"), never renderer
   time. `DelayThread(us)` advances logic time by `us` and runs whatever falls due (the
   1.7M 10-us polls in `GameSessionInit` become ~2 s of loading-screen frames, as on retail).
   No spin loops: `rg_spin_hint` becomes `rg_frame_wait(POLL)`.
6. **Host threads** only for work that touches no game state: file I/O, decode, audio
   output, GPU submission. Results enter game state only at defined frame-driver points,
   in submission order, so a run stays a pure function of its inputs.

### Order of events vs retail

The HLE has been validated against PCSX2 (VALIDATION.md, TIMING-REFERENCE.md) and its
order is the reference. Each conversion is done in two steps:

1. **Same order, native body.** The thread becomes a step, but the HLE scheduler still
   decides when it runs (slice 1's `ps2k_thread_set_service`). Every kernel-visible
   effect is kept, so the kernel trace hash, hence the runtime's run hash, must be
   identical to `RG_THREADS=hle`. That proves the conversion did not change behaviour.
2. **Native placement.** The frame driver calls the step at its phase. Differences against
   the HLE then come only from what the native model drops on purpose: preemption at kernel
   calls inside a frame (the HLE delivers a VBlank in the middle of the main thread when a
   DMA charge crosses the edge; natively the VBlank phase happens at the next wait) and the
   modelled DMA/register costs. Both are time-dependent by nature (retail's own preemption
   points are not reproduced by the HLE either). Checked with the logic-position
   comparison (`timing.py align`: milestone order + main-tick counts per segment), the
   state trace on tick keys (TIMING-LOCKSTEP.md) and the fixtures.

### Determinism and save states

- Native mode is single-threaded for game state: steps and the game coroutine run on one
  host thread; host jobs complete only at driver points; so runs are deterministic.
- Save states: today the kernel hook (`kstate_ss.c`) saves `K` (service threads are part
  of it: their thread objects, with the step pointers; no fiber) and the fiber arena
  saves fiber stacks. In the end state the state holds the game coroutine's stack (one
  arena slot), the driver's clocks and queues (a `threads` hook), and each converted
  step's own state is game memory already. A state carries the mode it was saved in
  (like the audio mode): `RG_THREADS` is read at boot, and the service flag lives in `K`.

### Proposals for other lanes (not done here)

- **Spin stage (`tools/stages/spin.py`, battle lane):** keep the table, change the runtime
  target: `rg_spin_hint(site)` -> `rg_frame_wait(POLL, site)` once the driver exists (no
  stage change needed, only `src/ps2/spin`); the 14 HALT rows stay. No new rows from this
  census: the KCALL/ROTATE loops it lists (`ThreadYield` in the movie layer) are gone with
  the movie service.
- **Renderer lane:** the VIF1 handler's `T0_COUNT` latch (`D_004810B4`) is frame-time
  feedback; the native renderer should provide "end of frame's GPU work" as logic time 0
  (nominal) so feedback never depends on render cost.

## 3. Slice 1: the tick thread as a native step

**What changed.**
- Kernel: `ps2k_thread_set_service(tid, wait, step)` marks a created, not yet started
  thread as a *service thread*: the kernel keeps the thread object (id, priority, status,
  wait lists, trace records) and, when the scheduler switches it in, runs
  `for (;;) { s = wait(arg); if (s < 0) break; WaitSema(s); step(arg); }` itself on the
  scheduler's host stack. Each kernel-visible effect is the one the fiber would produce:
  the k_enter delivery point of the loop's `WaitSema` (with preemption: `svc_pc` resumes
  after it), the sema logic and its `SEMA_WAIT`/status records, EIE save/restore, and the
  exit path (`ExitThread` k_enter, DORMANT). `step()` must run to completion: a blocking
  call inside it aborts with "service step of thread N blocked"; a preemption it causes
  is deferred to its end and counted (`ps2k_svc_deferred_count`).
- Game: `SysTickThreadMain_1c33f0`'s body is split into `rg_SysTickWait` (the loop
  condition: the sema id or -1) and `rg_SysTickStep` (the body, unchanged); the thread
  entry is the original loop over them. `SysTickThreadStart_1c3470` registers the thread
  with `rg_threads_service` before `StartThread`.
- Switch: `RG_THREADS=service` (was `native` until the frame driver took that name) / `hle`. The step is registered only when it
  cannot block: with `RG_AUDIO=native` its only callee that reached the kernel
  (`SoundSetCategoryVolume` -> command 0x12) goes to the engine; under `RG_AUDIO=hle|compare`
  the thread stays an HLE thread (`refused` in the log line).

**Why this thread first.** It is the cleanest "VBlank service" (1 wake per VBlank, a pure
run-to-completion body, 0 kernel calls under native audio) and it carries per-VBlank game
logic (vibration timers, sound fades) that the end state must run per VBlank phase, never
per present. `SoundStreamSlotThreadMain` has the same shape but its body takes the sound
stream mutexes (154k calls on the route); none blocked, but the HLE cannot prove they
never will, so it waits for native placement (where mutexes are uncontended by
construction). `CdDiskWatchThread` takes the file lock, same reasoning.

## 3b. The frame driver (slices 2-3, now `RG_THREADS=frame`)

(This section describes the driver over the HLE scheduler: `RG_THREADS=native` until
2026-10-18, `RG_THREADS=frame` since slice 5 took that name. Its conversions, driver points
and sync rules are shared by slice 5, section 3d.)

Still hosted by the HLE (it keeps the clock, VBlank edges, handlers and the unconverted
threads: main, loading screen, two idle sound workers), but no converted thread is ever
scheduled any more, and no game flow polls time.

### Driver points

| Wait | Where | Native form |
| --- | --- | --- |
| frame wait | `WaitVsyncCount_15de90` (override) | a driver point at the top of each round (right after the VBLANK_START wake, before the flow continues: the order the HLE gave the higher-priority service threads); the vsync semaphore protocol is unchanged (the timing record attributes loops by it) |
| `DelayThread` | `src/sce/kernel/eekernel.c` -> `rg_frame_delay` | driver point + a kernel-private timed wait (same virtual time as libkernl's alarm + semaphore, no ids: the per-call sema id was LIFO-reused, so invisible) |
| loading-screen polls | `LoadingScreenRequestEnd/IsFinished/IsClosed` (only caller `GameSessionInit_1f5d80`, which is the widescreen lane's override and stays untouched), `LoadingScreenStop_3431e0` | `rg_frame_wait_cond(cond)`: block until anything else ran (another thread, a handler, a driven step: `ps2k_wait_poll`), re-check; the predicate then returns 1. `IsFinished`'s other exit (`IsTgsDemoBuild_207f20`) is a constant 0 |
| spin hints | `src/ps2/spin/spin.c` | a driver point before the charge (the driven steps a spin may wait for run there) |
| `sceGsSyncV` (98 calls, `PadWaitReady`) | `src/sce/graphics/libgraph.c` | the kernel-private VBlank wait, then a driver point (slice 5 step 2) |
| `ThreadYield` (`RotateThreadReadyQueue(own prio)`: 4 per game frame in `MoviePlayerWaitTick_1d5810`, 12,128 to field 9,000) | `src/sce/kernel/eekernel.c` -> `rg_frame_yield` | a driver point, then the kernel's rotate (another ready flow of that priority first; with none it returns at once, as on the HLE: a poll wait there would cost a field per yield) |

`GameSessionInit`'s first loop (`LoaderTickGlobal` + `DelayThread(10)` until
`LoaderCountQueued` is 0) keeps its timed polls: its body makes progress itself, so a
condition wait could slow it. All `DelayThread` calls to field 9,000 (every site): 16,411
(HLE: 1,713,843 alarms).

### Driven threads

A conversion (`rg_thread_conv`) is registered by a constructor in the override of the
thread's entry (or, for the disk watch, of its wake ISR), keyed by the entry address. When
the game starts such a thread in native mode, the kernel's start hook parks it: the thread
object stays (id, ReferThreadStatus, Terminate/Delete work), it gets no fiber and is never
readied. It is modelled as blocked in the `WaitSema` of its loop: the driver makes it a
real waiter on that semaphore (`ps2k_driven_wait`), so the game's `SignalSema`, `PollSema`
and `iPollSema`-then-`iSignalSema` patterns see exactly the HLE's semaphore state (an
earlier version only polled counts: the game's own `PollSema` in `SoundStreamQueueFill`
then ate the stream threads' wakes and no stream ever ran). A signal marks it woken; the
step runs

- at the next driver point, in (old priority, thread id) order, on whichever game flow
  is there (VBlank services, signalled by ISRs), or
- at once, on the signalling game thread, when the conversion is `sync` and the HLE
  would have switched to it there (its old priority is higher than the signaller's; inside
  a step the signaller's priority is that step's). The kernel's signal hook calls the
  driver after the wake.

| Thread (old prio) | Conversion | Wake |
| --- | --- | --- |
| `SysTickThreadMain_1c33f0` (18) | `rg_SysTickWait/Step` (slice 1 split) | VBLANK_START ISR, driver point; `RG_AUDIO=native` only |
| `SoundStreamSlotThreadMain_1bc520` (15) | `rg_SlotWait/Step`, exit = `ExitDeleteThread` | VBLANK_END ISR, driver point; `RG_AUDIO=native` only. Main's kick `SoundRpcWorkerKick_1bd6a0` (override) ends in a driver point: its only caller, `SoundStreamSlotShutdown_1bdfd0` (every stream-channel close, i.e. every game-session shutdown), busy-waits on the slot's state around it, which the HLE ran at once (prio 15 < main's 20); without the point that loop never ended (2026-10-25 (stream close)) |
| `CdDiskWatchThread_17fdc0` (15) | `rg_DiskWatchWait/Step/Exit`, split in the thread's own override (2026-10-18, the native-FS lane being finished; the copy in a `CdDiskWatchWakeIsr_17ff10` override is gone, that function is generated again). The body's wait for the file-layer lock is a wait of its own (`rg_DiskWatchAt`): the driven thread is a real waiter on the lock, never a blocked step; sync at a flow's release | every 30th VBLANK_START, driver point; natively in the VBlank pass (`anywhere`) |
| `FileReqThread_182c30` (19) | `rg_FileReqWait/Step`, sync, drain | main's `FileReqThreadResume` / `FileReqAnyIncomplete` / `CancelAll` / `Shutdown` signal: runs there, as the HLE did |
| `SoundStreamThreadMain_1c1050` x3 (15) | `rg_StreamWait/Step` (split of `SoundStreamProcessCmds_1c05f0`), sync, wait may return `RG_CONV_READY` (a command is queued) | main's / the slot step's command signal; `RG_AUDIO=native` only |

**File requests on native-FS async jobs.** `FileReqSubmit_1827a0` (override) calls
`rg_FileReqPrefetch` once a request is queued: its reads start as `rg_fs_read_async` jobs,
one per 1 MB chunk, exactly the reads `FileReadChunked` -> `FileSlotRead` would make
(offsets, buffer extent, zero fill, slot position). The request completes for the game
(slot closed, result, done flags) when the step runs at the next wake signal, after a host
wait for its jobs, in queue order: the same point as on the HLE, so nothing the game sees
depends on host timing, and host I/O overlaps the game between queueing and wake. A cancel
or shutdown finishes the jobs and completes nothing (the generated loop read nothing then);
other slot types fall back to the generated sync path. `rg_threads_field_end()` (runtime,
after each field) waits for any job still in flight, so a save state never holds one.
A first version completed requests at the next driver point instead: `LoaderTick` polls
`FileReqAnyIncomplete` right after its signal, saw the batch incomplete and queued the next
batch one tick later (the opening movie started 2 VBlanks late); prefetch-at-queue removed
that difference. Stream ring fills (`RingBufFillFromFile`) still read synchronously inside
the stream step.

**Census of the class (2026-10-25 (sweep)).** A new driven conversion, or a new game loop
that signals one, must not busy-wait on it: `tools/census/driven_wait.py` (docs/SPIN.md
"Driven threads") lists every retail loop that wakes a driven thread's semaphore and whether
a driver point runs in it (the conversion table above is parsed from the overrides). Result:
151 loops wake a driven thread, 141 only `sync` steps that run at the signal, 0 busy-waits
left (the two kick loops above without the override); ctest `spin.driven_wait` (+ control).

### What differs from the HLE, by design

- **Placement:** a VBlank service step runs at the flow's next driver point, not where
  the HLE preempted (a kernel call inside main's frame whose DMA charge crossed the edge).
  The log's starvation line counts VBlanks with no driver point at all: 39 in 8 gaps, all
  at boot (vbl 36-96: main's init with modelled DMA/VU costs spanning up to 26 fields) plus
  1 at the NORMAL overlay load. A tick whose ISR found its previous step not yet run is
  skipped by the game's own handshake, so 39 ticks/slot updates are lost there (8,926 vs
  8,965 to field 9,000). In the end state main's work costs no virtual time, so the gaps go.
- **Waits:** condition waits wake when anything else ran, not on the 10 us grid; timed
  waits wake at the event pass, not after the INTC handlers of that instant.
- **Kernel trace** (run hash) differs: no fiber switches for converted threads, no per-poll
  semas/alarms. Main-tick counts, milestones and the read stream are the comparison.

## 3c. Slice 4: the loading screen (done 2026-10-18, form 2)

`LoadingScreenThread_343510` is a second frame loop: `DrawListFrameBegin`,
`LoadingScreenFrame`, `GfxEndFrame` (whose `GfxFlipBuffersMaybe` waits in `WaitVsyncCount`,
then flips). It cannot become a run-to-completion step as is: its wait is inside
`GfxEndFrame`, between the frame's draw and the flip, and running the whole iteration on
main inside main's wait blocks main's `GameSessionInit` loop 1 polls for a frame each (loop 1
would advance once per loading frame instead of continuously). Two forms work:

1. a step split at the vsync wait: `GfxEndFrame` in two halves (before / after the
   `WaitVsyncCount`), the driver calls "flip + next frame up to the wait" when the loading
   flow's vsync condition is due. Needs a split of `GfxEndFrame_141c20` /
   `GfxFlipBuffersMaybe_143650` (gfx code; coordinate with the renderer lane), or
2. a second driver-owned coroutine (the loading flow keeps its stack; the driver resumes it
   from main's driver points when `D_004810C4 - a >= b`), i.e. the same thing the HLE fiber
   does today, without the scheduler. This is the natural first step of slice 5.

**Done as form (2)**, inside slice 5: in the frame-driven kernel the loading screen's
thread is a *flow*, a game coroutine with its own fixed-address stack (arena slot) that the
host driver resumes when its wait is satisfied (its `WaitVsyncCount` semaphore, signalled by
the VBLANK_START handler in the pass; its `Vif1DmaHandlerShutdown` wait, satisfied by the
VIF1 completion in the next pass). Main's loading waits (`DelayThread(10)` polls of
`GameSessionInit` loop 1, the condition waits) are where it runs: the frames the HLE fiber
drew (the loading screen still spans fields 2113-3141, 1,028 fields, in every mode).
Registered as an intended flow by `rg_threads_flow` (constructor in the
`LoadingScreenStop_3431e0` override), so the log separates it from unconverted threads.
Form (1) (a `GfxEndFrame` split) was not needed: no gfx override was made. Under
`RG_THREADS=frame` it stays an HLE thread (that mode is the slices 2-3 oracle).

## 3d. Slice 5: no EE scheduler (`RG_THREADS=native`, 2026-10-18)

**Kernel frame-driven mode** (`ps2k_config.native`, docs/KERNEL.md "Frame-driven mode"):
`ps2k_step` runs `kn_step`, the host frame driver's loop: run the ready flow until it waits;
then a *pass*: due events, the latched causes' handler chains (VBLANK_START / END, VIF1, SIF0)
as explicit calls, kernel-private wakes, the **phase hook**; when every flow waits, jump
logic time to the next event. No priorities beyond the order of simultaneous wakes, no
preemption, no delivery inside a flow (`k_enter`, `EI`, `EnableIntc`, `ps2k_poll`), no
service threads. The runtime sets it from `RG_THREADS=native` (falling back to `frame`, with
a message, unless `RG_AUDIO=native`: the sound threads are steps only there).

| HLE machinery | Native path |
| --- | --- |
| priority scheduler, preemption at every kernel call / EI / charge | `kn_step`: flows run until they wait; FIFO among ready flows |
| one fiber per game thread (11 on the route) | 2 flows: main (the game coroutine, thread 1) and `LoadingScreenThread_343510`; 9 threads are driven steps (tick, stream slot, disk watch, file requests, 3 streams, and now the two sound workers `SoundCmdWorkerThread_1b6c10` / `SoundThreadMain_1b6260`, converted with a new `prologue` field) |
| INTC / DMAC delivery at defined points | handler chains called in the pass only (explicit phase calls); STAT / MASK bits kept as the latch (a cause raised before `EnableIntc` is delivered after it: the VIF1 protocol) |
| VBlank services woken by handlers, run when the scheduler picks them | the phase hook runs the steps marked `anywhere` (tick: no kernel call; disk watch: its lock wait is a real wait) in the pass of the VBlank that woke them, before any flow resumes (the HLE order: handlers, then steps by old priority); the others (they take locks a waiting flow may hold: stream slot, file requests, streams) at the flows' driver points or at their signal (sync), as in frame mode |
| `DelayThread` = CreateSema + timer alarm + WaitSema + DeleteSema | kernel-private timed wait (through `rg_frame_delay`: with driver points around it); no alarm, no sema id |
| bus-cycle clock advanced by modelled DMA / register / VU costs | logic time moves only when every flow waits: DMAC `cycles_per_qword` = 0, `hwbus_set_read_cycles(0)`; `ps2k_charge` from a flow (SIF / memory-card / DMA-busy polls, spin hints) = timed wait, elsewhere dropped (75 dropped to the battle, 0 became waits) |
| `T0_COUNT` from that clock (frame-time feedback includes DMA cost) | the same register model over logic time: a frame's own work reads 0, so `GfxEndFrame` / `GfxFlipBuffersMaybe` / the VIF1 latch see the nominal profile (fb = interval) by construction |

**Step context.** A driven step runs as its own thread (`ps2k_step_enter`): `GetThreadId`,
its priority and its own semaphore calls behave as on the thread. It has no stack, so it
must not block: a `WaitSema` with no count first runs the other woken steps (block hook: the
HLE ran lower-priority threads while it waited), then is fatal with a message. The first
run after StartThread happens at once on the starter when the HLE would have switched to the
thread (parked hook; 9 eager starts to the battle).

**Found on the way.**
- The disk-watch step, now run in the VBlank pass, hit the file-layer lock held by main
  (waiting elsewhere): fatal "driven step blocked". Its lock wait became a wait of the
  conversion (`rg_DiskWatchAt`): a real waiter, run at main's release (sync); the same
  kernel calls in the same order on the HLE. Steps that take other locks stay at driver
  points (`anywhere` = 0).
- `ThreadYield` as a poll wait (wait until anything else ran) cost a field per call:
  `MoviePlayerWaitTick_1d5810` yields 4 times per game frame with no other thread of its
  priority, a no-op on the HLE. Now a driver point + the kernel's rotate.
- `rg_frame_point` entered every slot's step context, and entering bumped the kernel's
  activity count, so every poll wait returned at once: the first native run spun at the NEW
  GAME load (found with `tools/native/thread_sample.py`). A step context is now entered only
  when the step is due.

## 3e. Native kernel table (2026-10-18, evening)

The frame-driven mode of slice 5 left the HLE: it is now the **native kernel table**, a
second implementation of the ps2k API in `src/native/threads`. The game-visible ids (thread
objects, semaphores, handler ids), the event list and the flows live there; `src/ps2/kernel`
is the oracle only (`RG_THREADS=hle|service|frame`, the kernel tests).

| Part | Where |
| --- | --- |
| API | `src/native/threads/kapi/ps2k.h`, `ps2k_ss.h` (moved from `src/ps2/kernel`; forwarders stay there); `kapi/ps2k_api.inc` + `kapi/ps2k_rename.h` generated by `tools/native/thread_api.py` (111 functions; `--check` after a prototype change) |
| Native table | `rg_nk.c` (flows, the driver loop `ps2k_step`, thread / semaphore ids, kernel-private and poll waits, driven threads, step context, trace), `rg_nk_irq.c` (logic clock, event list, handler ids and chains with the STAT / MASK latch, T0..T3), `rg_nk_ss.c` (save state, magic `NNK1`), `rg_nk_internal.h`; library `rg_native_kernel` (names `rg_nk_*`) and, in RG_NATIVE_ONLY builds, `rg_native_kernel_ps2k` (the same sources under the real names, `RG_NK_REAL_NAMES`) |
| Host coroutines | `src/native/threads/fiber/` (moved from `src/ps2/kernel`): `fiber_win32.c`, `fiber_ucontext.c`, the fixed-address arena `fiber_arena.c`; library `rg_native_fiber`, used by both implementations |
| Dispatcher (default builds) | `src/ps2/kernel/kdispatch.c`: the HLE compiles its definitions as `ps2k_hle_*` (`internal.h` includes `ps2k_rename.h`); `ps2k_init(cfg)` picks the table when `cfg.native`, the HLE otherwise; every other `ps2k_*` forwards to the one in use; host registrations made before any init (the frame driver's hooks from constructors, the census tap, the violation hook) go to both |
| Save states | the `kernel` hook (`ps2k_ss_*`) saves whichever is in use; `ss_map.c` rows `rg_nk.c.obj` `_NK` (hook) and `_nk_tap` (host) |

What the table is: the HLE's frame-driven code path, record for record (the same `k_trace`
records in the same order, so a run hash is unchanged by the move), without the priority
scheduler, preemption, delivery at kernel calls / EI / `ps2k_poll`, service threads and the
modelled kernel-call cost. Ids keep the retail numbering rules (VALIDATION.md 2c) because game
code stores and compares them. The HLE lost its frame-driven code (`kn_step`, the step context,
the phase / parked / block hooks, the native charge / delay / EI branches): `ps2k_native()` is 0
there and `ps2k_hle_init` clears `cfg.native`.

The event list's completions on the native path: VBlank edges, timed waits (`DelayThread`,
`ps2k_wait_until`, a charge from a flow), posted causes of the models still linked (DMAC /
GS: renderer lane). SIF and CD completions do not reach it any more (NATIVE-IOP.md: the native
pad / card / fileio services complete at issue, libmc's card time is a timed wait); the
device list (the oracle's CDVD sector model) is kept in the API and empty natively.

## 3f. Native-only: RG_THREADS_ORACLE (2026-10-18, evening)

`RG_NATIVE_ONLY` (docs/NATIVE-ONLY.md) now drops the EE kernel HLE from rg-game:

- `cmake/native_only.cmake`: `RG_NONLY_REPLACE` += `rg_ps2_kernel=rg_native_kernel_ps2k`
  (no HLE, no dispatcher), `rg_ps2_spin=rg_native_spin` (`rg_spin_native.c`: the spin hint as a
  driver point + a timed wait, the per-site statistics of `spin.c`), `rg_sce_kernel=
  rg_sce_kernel_native` (`eekernel.c` without the census recorder). A replacement's own
  dependencies are now mapped like any library's (it is cloned when one of them changes:
  `rg_native_threads` -> its clone). `RG_NONLY_GUARDED` += `rg_native_threads`.
- `src/native/threads/rg_threads_oracle.h`: `RG_THREADS_ORACLE` 1 by default, 0 with
  `RG_NATIVE_ONLY`. Guarded: `rg_threads.c` (`RG_THREADS=hle|frame|service` refused with a
  message, the service registry, `rg_threads_force_mode` aborts), `kcensus.h` / `kcensus.c`
  (the recorder compiled out; `RG_KC` no-op).
- `tests/native_only`: `native_only.link_audit` checks `--forbid iop,kernel` (the control,
  the twin, must still fail). `tools/native/link_audit.py` classifies `rg_sce_kernel_native`
  as native (like `rg_sce_cdvd_native`); `rg_native_*` was already native.

## 3g. Paced mode (2026-10-18, evening)

PLAN.md "Unlocked frame rate": logic fixed-step, host time decides how many ticks run. The
fixed step of the frame driver is the **VBlank phase** (one NTSC field, 2,460,060 bus cycles,
the kernel's exact `PS2K_FIELD_SUB` grid); the game's logic tick is its own 1- / 2-VBlank
interval inside the phases (counted as the main flow's frame waits, `rg_frame_logic_ticks`),
so no tick is ever shorter or longer than retail's. Four clocks: host time (SDL), VBlank time
(the phase counter), logic ticks, audio time (the native engine's 48 kHz frames, consumed per
phase).

| Cadence | When | What |
| --- | --- | --- |
| retail (deterministic) | `display.pacing = retail` (the Original preset), and **every run without a host clock**: `--headless`, `--unthrottled`, `system.throttle` off (tests, traces, fixtures, save states) | one phase per `rg_runtime_run_field`, one present per phase (`display.frame_rate` skips presents as before); with throttle on the kernel's idle jumps sleep to wall time (`rg_pacer`, unchanged) |
| host | `display.pacing = host` (the Default preset), or `RG_PACE=host` | `run_field` first waits until host time owes a phase (`rg_pace_until_tick`); the phase runs flat out (the idle-jump sleep is off: `pace_kernel_hook`); `host_half` skips the present (catch-up) only while at least `catchup` = 2 phases are owed AND the host runs a phase in under 90 % of one (moving average of the phase cost), else it presents (when the frame cap's slot has come); after k = 4 phases without a present one is forced; debt beyond k phases is dropped (a hitch: `resyncs`, which also re-anchor the host audio queue). Until 2026-10-18 late any owed phase skipped the present, which turned every slightly over-budget battle frame into a batch of 4 phases with an unseen game frame (docs/PERF-3D.md "Transition stutter"); `RG_PACE_CATCHUP=1` restores that |

The accumulator (`src/native/threads/rg_pace.[ch]`, pure, host time passed in) counts owed
host time in units of 1/2304 ns, so a phase is exactly 38,438,437,500 units (no drift). Its
structure carries both directions the renderer lane needs later: 0..k phases per present
(`rg_pace_present_now`) and N presents per phase (`rg_pace_between` gives the present slot and
the interpolation weight alpha between phases; `rg_pace_sleep_ns(.., between = 1)` sleeps to
the next slot). Without `display.interpolation` nothing presents between phases, so a present
cap above 59.94 Hz means one present per phase; with it (native-only exe, 2026-10-25,
docs/NATIVE-RENDER.md "Interpolated presentation") `pace_before_field` presents an
interpolated image at each `rg_pace_between` slot (host time in phases = ticks + alpha) and
sleeps to the next slot. VSync interplay: with `display.vsync` on, the
present waits for the display and the pacer never sleeps for a present slot; the accumulator
still owns the phases (a 60 Hz display shows 59.94 Hz logic with one repeated frame every
~17 s, no speedup). The game sees none of it: its state is a function of its inputs per phase,
so a paced run with an input script has the same run hash as a headless one (section 4).

Settings (`src/settings/rg_settings_core.c`, docs/SETTINGS.md): new `display.pacing` (retail /
host; default host, Original retail; live); `display.frame_rate` (the existing cap: original =
no cap, 30, 60, 120, 144, uncapped) and `display.vsync` feed the pacer live. Environment for
tools: `RG_PACE=retail|host`, `RG_PACE_CAP=fps`, `RG_PACE_MAX_TICKS=k`, `RG_PACE_CATCHUP=n` (phases owed before presents are skipped; 1 = the first design), `RG_PACE_LOG=1|path`, `RG_PACE_COST_AT_DECISION=1` (control: the phase cost stops at the present decision, before the GS worker wait; since 2026-10-22 the runtime samples it after that wait with `rg_pace_phase_done`, see BRINGUP-HISTORY 2026-10-22 shop close)
(summary at exit: phases / logic ticks / presents per host second, phases-per-present
histogram, resyncs; with a path also one TSV row per host second).

## 3h. Hitches (measurement, 2026-10-25)

`tools/native/hitch.py` measures what stops video and audio on a windowed real-time run of
any exe (default the latest play-test exe) with the play-test setup (RG_GPU=hw,
RG_SLOTS_PRIORITY=normal, a copy of out/playtest/settings.ini passed with `--settings`).
Routes from real inputs, no save states: `poweron` (golden route to the first save, 31,700
fields, ~10 min), `battle2` (card save2 boot, walk, encounter, battle, field, ~2.2 min), `shop`
(card zshop2, `tools/native/hitch_shop.input.txt`, ~75 s).  It joins $RG_FIELD_TIMES,
$RG_FIELD_STATS, $RG_AUDIO_LOG, $RG_PRESENT_LOG (or, for exes without it, the presents column of
the stats) and the STATUS lines with a 1 s typeperf sample of machine CPU / GPU-3D load, and
writes `out/hitch/TAG/ROUTE/hitch.md` + `hitches.tsv`: video hitches (present gap > 3 periods),
audio hitches (starved pushes), each attributed to pacer sleep / game CPU / file I/O / GPU and
GS-worker waits / present (compose + window present) / read-back waits / event pump / audio
push / off-CPU (preempted or an untimed wait).  `--load cpu:N|game:N|gamewin:N` adds contention
the tool owns (stopped by PID).  `compare DIR...` tabulates runs.

    python tools/native/hitch.py run TAG --route all [--exe EXE] [--load cpu:8]
    python tools/native/hitch.py compare out/hitch/A/poweron out/hitch/B/poweron

Why audio stops with video: the game thread renders the sound (native engine, folded into the
run hash) and pushes it after each field (runtime.c host_half); the device queue holds a
64 ms cushion (`audio.latency_ms`, host_audio.c).  Any main-thread stall longer than the
cushion starves the device, and while the game runs below real time (catch-up, pacer debt
dropped) no cushion can keep up.  First numbers and next steps: BRINGUP-HISTORY.md
"2026-10-25 (hitch)".

### 3h.1 Fixes (2026-10-26, history "2026-10-26 (hitch2)")

- **The mode-11 read-back = the lens flare's depth probe** (`GfxEndFrame_141c20`: up to four 8x8
  PSMZ32 `sceGsExecStoreImage` per game frame -> libgraph `rg_gs_store_hook` -> nr_scene.c
  `native_store` -> nr_dev.cpp `mem_read`, the early-copy path; `download_ms` of $RG_FIELD_STATS,
  `downloads` 0 because early reads are not counted there).  The map waits for the GPU to finish
  the frame being drawn.  **Probe lag** (NATIVE-RENDER.md "Lens-flare depth probe"): in real-time
  play (`gpu_config.probe_lag`, set by runtime.c for windowed throttled runs; `$RG_GPU_PROBE_LAG`)
  the read is served from the copy taken at the previous probe group, so it does not wait.  Run
  hash unchanged with it forced on (headless power-on to 31,700: `b0632cdfa80153de`, = the
  baseline and = lag off; 10,186 of 10,189 probes served a group late); tests, traces and save
  states keep the exact read (lag off headless).
- **Audio** (HOST.md "Audio"): adaptive cushion (grows after a starve shorter than the cap,
  `$RG_AUDIO_ADAPT_MS` default 192, decays after ~20 s) and a refill that leaves room for the
  pacer's owed phases (no drop after the catch-up burst).  The run hash folds the engine output
  before the push: unchanged.
- **hitch.py:** `window F0 F1 DIR...` (one field range); category `out` = time between fields in
  the caller, which on this machine is the measurement's own log writes blocking on the busy disk
  (STATUS lines, `fflush` of the field logs every 60 / 100 fields: stalls of 0.1-1.2 s at fields
  = 1 / 57-58 mod 100) -- reported as "measurement stalls", not counted as the game's hitches
  (a play-test run writes nothing per field); the game's stdout / stderr now go through a pipe
  drained into memory.  These were most of the "off-CPU" hitches of the first report.
- **File reads at a card load:** cold OS cache only (shop route field 2,718: 74 reads, 11 MB,
  145 ms cold; the same load in battle2 2.5 ms warm); not changed (an async read changes the
  game's timing; a cache warm-up would need the list of files a card load reads).

### 3h.2 Present off the game thread? (measured 2026-10-26, history "2026-10-26 (interp3)")

`$RG_PRESENT_LOG` now has two more columns: `present_ms` (the present's time on the game thread,
from the interpolation pass request to the window's present returning) and `window_ms` (of it,
`rg_host_present_shared`: the SDL draw, flush and present call; interpolated presents only).
`tools/native/present_thread.py --hz HZ PRESENT_TSV FIELD_TIMES_TSV` splits the present intervals
into "between" (no phase ran: interpolated presents in a phase gap) and "phase", and attributes
the late ones (> 1.5 periods) to phase work vs the presents' own game-thread time.  Windowed
ch07_rosa battle from the battle state, host pacing, interpolation on, 144 Hz panel
(`tools/native/interp_window.sh`), on the shared machine (two other lanes' rg-game runs):

| config | presents/s | field wall ms (EE step / worker sync / post) | present_ms mean (window part) | late time a present thread could move |
| --- | --- | --- | --- | --- |
| D3D11 144 vsync | 23.6 | 18.9 (5.0 / 2.1 / 11.3) | 23.4 (16.8) | <= 66 % (window alone 47 %) |
| Vulkan 144 vsync | 28.5 | 17.3 (5.0 / 2.9 / 9.4) | 18.0 (10.5) | <= 64 % (37 %) |
| D3D11 uncapped, vsync off | 21.3 | 18.4 (5.2 / 3.3 / 9.8) | 25.1 (22.1) | <= 62 % (54 %) |

Control and a prototype (same state, one exe, back to back): **interpolation off** (D3D11 144
vsync): 51.4 presents/s, present 3.9 ms (the overlapped field present shows the frame the worker
composed a field ago: no wait), EE step 4.4 ms; **on**: 29.5 presents/s, present 20.3 ms (13.7 of
it the window's present).  The interpolated present is synchronous with the GPU: the pass is
queued behind the phase's GS input, drained, composed, and the window's present then waits for
that GPU work (keyed mutex / queue).  **Prototype `RG_INTERP_PIPE=1`** (measured, then removed):
the interpolated present pipelined like the field present (pass + compose queued on the worker,
presented at the next present, so the game thread never waits on the window's present):
D3D11 present 20.3 -> 17.5 ms, all of it now the wait for the worker / GPU, presents/s 29.5 ->
28.8 (Vulkan 31.1, 12.0 ms); uncapped it showed 33 % repeated images.  No gain: the cost is the
pass on the GS worker and the GPU under contention, not the window's present on the game thread.

Reading: with interpolation on, the game thread spends more than a phase's budget per field
(17-19 ms vs 16.7) waiting for the interpolated presents, so the pacer owes a phase at every
present slot: no present falls between phases and the game runs below real time on this shared
machine.  A present thread would not change that (the pipelined prototype moved the window's
present off the critical path and the wait just moved to the worker), and SDL's renderer is used
on the main thread (event pump, settings overlay, window shots; SDL3 renders on the window's
thread), so it would mean moving the game loop instead.  **Not done.**  What would help is a
cheaper pass (replaying less than the whole frame per present, or presenting from a pass made
once per refresh on the worker while the next phase runs -- one device, so only if the worker has
idle time) -- to judge on a quiet machine first (`interp_window.sh` + `present_thread.py`; on the
10-25 title run without load the same path reached 141-144 presents/s, NATIVE-VULKAN.md
"Results 2").

## 4. Verification

Slice 1 subsections below were measured when slice 1 was `RG_THREADS=native`; that mode
is `RG_THREADS=service` now (same code path). The frame driver's results follow them.

### Unit (`ctest -L "kernel|spin|runtime|fixtures"`: 53/53 pass, `runtime.cdvd_realdata` skipped without RG_DATA)

`rg-kernel-tests service_thread`: a game-shaped thread (prio 18, woken by a VBLANK_START
handler; a prio-15 thread woken every 3rd VBlank; a prio-25 thread it signals; a prio-20
main thread whose `ps2k_charge`s cross VBlank edges so the service thread preempts it
mid-run; the loop ends after 40 steps and the thread exits) run once as a fiber and once
as a service thread: same trace count (1,521) and hash (`1ae42bb16395c354`), same
interleaving log, 40 steps, 0 deferred, thread DORMANT at the end. The control (one extra
kernel call in the service run) fails: 1,561 records.

### Golden route, hle vs native (`tools/native/thread_compare.py`)

| Run | hle | native |
| --- | --- | --- |
| power-on -> 9,000, `--kcensus` | run hash `388aaa4da52654b8`, shots 3000/8500/9000 `482144d6..`/`4d2cc403..`/`777bd8c3..` | identical |
| power-on -> 9,000, `RG_TIMING` | run hash `326c86ff3a777910`, same 3 shots | identical; `timing.py align --nowrap`: 22 milestones in the same order, **0 of 21 segments** with a different main-tick count; 8,965 steps, 0 deferred |
| power-on -> 23,090 (first battle + 90; game mode 7 at vbl 22,863), `RG_TIMING` | run hash `cb71c3ca1a1efcd3`, shots 1800/8300/23000/23090 | identical; 24 milestones, **0 of 23 segments** differ; 23,055 steps, 0 deferred |
| power-on -> 9,000, plain, modes native,hle,native | `388aaa4da52654b8` x3 | identical (also equal to the `--kcensus` run: recording the census does not change the run) |

Wall times are not comparable on the shared PC: the same 9,000-field run took 47 s,
256 s and 189 s in one session depending on other load. The service step does less work
than a fiber switch, so no slowdown is expected.

(The run hash folds the kernel trace hash every field, so equal hashes mean the kernel
event sequence matched field by field. Recording a census or a timing record changes the
hash relative to a plain run (TEST-FIXTURES.md note), so compare like with like.)

### Save states (native mode)

`RG_THREADS=native python tools/fixtures/regen.py --exe build/nthreads-i686/rg-game.exe
--only title,field --check 300` then `verify.py --only title,field` (set
`out/fixtures/a85e04512a204716`): title 1500 -> 1800 run hash `6588b91447d7eb32` = the
power-on run's, frame `c0a568381736f720` =; field 8000 -> 8300 `271614a13357a418` =,
frame `d54e1bf161d98507` =. The service thread has no fiber; its thread object and step
pointers travel in the kernel section.

### Frame driver (slices 2-3), 2026-10-18

Unit: `ctest -L "kernel|spin|runtime|fixtures|native_fs"` in `build/nthreads-i686`: 59/59
pass (`runtime.cdvd_realdata` skipped). New kernel tests: `poll_wait` (a flag set by a
worker on its 4th VBlank wake and one set by a handler alone: 10 us `DelayThread` polling
sees them after 6,533 / 5,007 polls, `ps2k_wait_poll` after 9 / 5 wakes, within one poll
period of the same time; the control, a 200 us timed poll, fails), `driven_thread` (parked
on StartThread, never run, one step per VBlank signal, exit -> DORMANT, restart unmarked
runs the entry, Terminate/Delete of a parked thread, ReleaseWaitThread refused),
`frame_driver` (a converted thread driven by `rg_frame_delay` points on main: 12 steps, the
exit tail, DORMANT; a condition wait ends at VBlank 9 with < 40 wakes).

`RG_THREADS=hle` is unchanged by all of this: power-on -> 9,000 with `RG_TIMING` gives run
hash `326c86ff3a777910` for `hle` and for `service`, the slice 1 value.

Golden route, `hle` vs `native` (`thread_compare.py --timing`, then `timing.py align
--nowrap` and `fs_census.py stream`):

| Run | Result |
| --- | --- |
| power-on -> 9,000 (`out/nthreads/s3e`) | 22 milestones identical at the same VBlank, **0 of 21 segments** differ; reads 129 = 129, same order; shot 3000 identical, 8500 / 9000 differ in a small region (8500: 2,478 pixels, a character's head: animation phase) |
| power-on -> 23,100, first battle (`out/nthreads/battle4`, exe `out/nthreads/exe4`) | 24 milestones identical (game mode 7 at vbl 22,863, unlock 22,957 in both), **0 of 23 segments** differ; reads 338 = 338, same multiset, 8 reordered (file requests now complete in queue order); 115 requests through async jobs, 0 on the sync path |
| driver counters to 9,000 | 48,294 driver points; steps: tick 8,926, stream slot 8,932, disk watch 96, file requests 2,092 (all sync at the signal), streams 2,450; 16,411 `DelayThread`, 4 condition waits, 2,053 wakes |

Save states, native mode, full set with `--check 300` (`out/fixtures/037d8aed5c4afb1a`,
exe `out/nthreads/exe4`): title 1500 -> 1800 run hash `24944335e50a5a4b` = power-on, frame
`c0a568381736f720` =; field 8000 -> 8300 `70ce311ce155ad7e` =, frame `e89f47fe31849838` =;
**battle 23000 -> 23300 `26cd01c3ce021e90` =, frame `7f6d9a78255fae45` =** (the battle +300
check slice 1 could not run). The same check on the slice-3 exe before the stream
conversion (`out/fixtures/7ddbe3758f6385fd`) also passed all three.

Host cost (`RG_FIELD_TIMES`, two runs each, headless, exe4): the NORMAL loading screen
(fields 2113-3141) takes **2.64 / 2.70 s of EE step time with `hle`, 0.41 / 0.41 s with
`native`** (wall 2.68 / 2.73 s -> 1.14 / 1.17 s). Its length in game time is unchanged
(1,028 fields): it is paced by the loading screen's own state machine (fades, the button
press on the golden input), not by I/O. Full 9,000-field runs: 35-43 s either way on the
shared PC (noise dominates).

### Slices 4 + 5 (frame-driven kernel), 2026-10-18 late

Unit: `ctest -L "kernel|spin|runtime|native_fs"` 56/56 and `-L fixtures` 5/5 in
`build/nthreads-i686` (`runtime.cdvd_realdata`, `native-fs-realdata-tests` skipped). New
`frame_native` (two flows; a tick step in the pass of the VBlank that woke it, before main's
frame wait returns, in step context; a disk-watch-shaped step waiting for a lock main holds
across 4 frames runs at the release; a raised VIF1 cause and a signal to the other flow do
nothing until main waits; T0 and the clock do not move across a busy loop; `DelayThread(1000)`
= 147,456 cycles, `ps2k_charge(5000)` = 5,000 cycles of timed wait; 2 flows) and its control
(the same on the HLE: fails the placement and step checks).

`RG_THREADS=hle` unchanged: power-on -> 9,000 with `RG_TIMING`, run hash `326c86ff3a777910`
(the slice 1 value), so the new overrides (disk-watch split, sound-worker splits) make the
same kernel calls in the same order.

| Run | Result |
| --- | --- |
| power-on -> 9,000, hle vs native (`out/nthreads/s5c`) | 22 milestones identical at the same VBlank, **0 of 21 segments** differ; shot 3000 identical (`d31fcb6c04b4dbde`), 8500 differs in the documented region (2,478 pixels, a character's head) |
| power-on -> 23,300, hle / native / frame (`out/nthreads/s5bat`) | hle's 24 milestones identical in native (game mode 7 at vbl 22,863, unlock 22,957), **0 of 23 segments** differ; after that the battle outcome differs (section 5) |
| native driver counters to the battle | 2 flows (main, loading screen), 9 driven threads, 151,995 passes, 53,987 flow switches; steps: tick 23,267, stream slot 23,305, disk watch 1,144, file requests 17,836 (all sync), streams 20,829; 0 charge waits, 75 charges dropped (outside a flow); 0 VBlank gaps; 119 file requests on async host jobs |
| native fixtures, `--check 300` (`out/fixtures/422115d6b5f4ee01`) | title 1500 -> 1800 run hash `d497ede817b0bad8` =, frame `c0a568381736f720` = (the same frame as the HLE-era sets); field 8000 -> 8300 `12161fa13cb1144d` =, frame `e89f47fe31849838` =; battle 23000 -> 23300 `e951b5cee044d3b1` =, frame `ead43731b54315b3` = |

### Perf (host cost per field), 2026-10-18

`tools/native/thread_perf.py measure` (`out/nthreads/perf/422115d6b5f4ee01`): each mode's own
states, 300 fields loaded twice per mode, modes interleaved; process CPU (all host threads)
minus a zero-field load, and the median `step_ms` (wall time of the field's `ps2k_step`):

| Window | hle cpu/field | frame | native | hle step med | frame | native |
| --- | --- | --- | --- | --- | --- | --- |
| title 1500-1800 | 3.02 / 2.92 ms | 2.55 / 2.97 | 3.23 / 2.60 | 1.23 / 1.19 ms | 1.23 / 1.29 | 1.23 / 1.26 |
| field 8000-8300 | 20.10 / 18.12 | 18.65 / 19.69 | 18.70 / 17.60 | 8.14 / 7.97 | 7.97 / 7.93 | 7.99 / 7.93 |
| battle 23000-23300 | 48.02 / 49.84 | 38.18 / 37.29 | 44.95 / 42.76 | 34.80 / 34.90 | 14.94 / 14.51 | 18.65 / 17.74 |

and from the power-on runs (`thread_compare.py --windows`, one run each): the NORMAL loading
screen (fields 2113-3141) **2.66 ms -> 0.43 ms** mean step per field (frame 0.42); whole
power-on -> 23,000 CPU: hle 492 s, frame 492 s, native 485 s. Title and field cost the same
in every mode (the game, the VU / GS models and the GPU dominate; the kernel's share there
was already small after slices 2-3). The battle window is not like for like: the three runs
are in different battle states after vbl 22,957 (native reaches game mode 11 at 23,217);
the HLE's extra step time there is its stream / file-request fiber traffic (38,665 steps
that are fiber switches on the HLE).

### Native kernel table, native-only, paced mode (2026-10-18, evening)

Build `build/nthreads-i686` is RG_NATIVE_ONLY=ON (`tools/native/nonly_build.ps1 -BuildDir
build/nthreads-i686 -Targets rg-game,rg-game-oracle,rg-kernel-tests`): `rg-game` links the
native table only, `rg-game-oracle` is the same-tree default twin (dispatcher + HLE). Reference
exes from before the change: `out/nthreads/base/`. Runs with `thread_compare.py --input
tools/trace/goldens/newgame_save1.input.txt --timing --spec LABEL=EXE:MODE ...` (new options).

| Check | Result |
| --- | --- |
| power-on -> 9,000 (`out/nthreads/id9000`, `id9000b`, `id9000c`) | native: run hash `2dc25f617dd6a7cb` for the old exe (HLE frame-driven), the native-only exe and the twin through the dispatcher: **the move changed no kernel record**; hle `de6995447ef2242c` and frame `92b0c258bc26e9f5` equal to the old twin's (the HLE without its frame-driven code is the same oracle); hle vs native: 22 milestones, 0 of 21 segments differ |
| power-on -> 31,700 (`out/nthreads/id31700`) | native-only and twin native: run hash `f3b853eebb958224`, the NATIVE-ONLY.md value of the pre-change exes; 38 milestones, 0 of 37 segments differ between them; hle vs native: the first 23 milestones identical (to the battle intro unlock, vbl 22,957), then the documented battle-outcome difference (section 5: 7 of 35 segments) |
| link audit (`link_audit.py check rg-game.map --forbid iop,kernel`) | **PASS** (the twin: FAIL, as the control must); `kernel` set 3 libraries / 311.6 KB (rg_ps2_kernel 230.0, rg_sce_kernel 70.1, rg_ps2_spin 11.5; code + data + bss) -> 0; added native: rg_native_kernel_ps2k 221.0, rg_native_spin 11.7, rg_sce_kernel_native 2.1, rg_native_fiber 1.8 KB; exe 12,697.8 -> 12,629.7 KB of symbols (-68 KB: the census recorder's tables) |
| fixtures, native-only exe (`regen.py --check 300` + `verify.py`, set `out/fixtures/cb8db675e1683f97`) | 14 states, **7 / 7 OK** (title / field / battle / battle_won / town / save_point / saved: run hash and frame after 300 fields equal to the power-on run) |
| ctest (`-L "kernel\|spin\|runtime\|native_only\|settings\|host" -LE fixtures -j2`, then `-L fixtures -j1`) | 122 / 122 + 6 / 6 pass; new `kernel.pace` + `kernel.pace_control` (WILL_FAIL: no debt bound, 60 phases back to back after a hitch) |
| paced vs deterministic, 1,800 fields with the golden input (`out/nthreads/pace/run.sh`) | run hash `cd8da3e2adcb8f52` for `--headless`, windowed retail and windowed host with every cap / VSync below: **pacing never reaches game state** |

Paced-mode windowed smoke runs (30 s each, `RG_PACE=host`, `RG_PACE_LOG`; shared PC):

| Settings | Phases / s | Logic ticks / s | Presents / s | Phases per present |
| --- | --- | --- | --- | --- |
| no cap, VSync off | 59.965 | 30.55 | 59.965 | 1: 1,800 |
| `display.frame_rate=30` | 59.956 | 30.54 | 30.011 | 2: 895, 1: 4, 3: 2; every whole second 60 phases / 30 presents / 30 logic ticks |
| `display.frame_rate=144` | 59.955 | 30.54 | 57.79 | 1: 1,670, 2: 65 (catch-up after heavy phases: 0 presents for a phase, never a faster one) |
| VSync on, no cap | 59.72 | 30.42 | 59.62 | 1: 1,796; one hitch at second 12 (7 phases of debt dropped, `resyncs=1`) |

No logic speedup in any run: phases per host second stay at 59.94 (at most 61 in the first
second, the anchor's first owed phase), logic ticks follow the game's 1- / 2-VBlank interval.

## 5. What remains of the kernel HLE

### On the native path after slice 5 (`RG_THREADS=native`)

Gone: the priority scheduler and preemption, delivery at kernel calls, 9 of 11 game-thread
fibers (only the two flows have stacks), service threads, `DelayThread`'s alarm + semaphore
(1.7M alarms on the HLE), the modelled DMA / register costs in the clock, the 39 boot VBlanks
with no driver point (tick steps to field 9,000: native 8,967, frame 8,926, HLE 8,965 per the
slice 1 count; stream-slot steps 8,970).

Since section 3e nothing of `src/ps2/kernel` is on the native path. What the native kernel
table still keeps, and why:

| Part | Why it is still there | Next |
| --- | --- | --- |
| the driver loop + 2 flow coroutines (arena slots) | the game's nested frame loops wait inside calls: the coroutine is the native form; save states need fixed-address stacks | paced mode drives it from the host clock (done); interpolated presents between phases: renderer lane |
| thread objects and ids, semaphores (ids, counts, waiter lists) | the game stores thread / semaphore ids (`D_0047F650`, ...), calls Refer / Terminate / Delete; a waiter is a flow or a parked step; mutexes uncontended | in the table (done); smaller records only if a census shows the fields unused |
| handler ids + chains + INTC / DMAC STAT / MASK latch, delivered in the pass | game-visible handler ids (the per-frame VIF1 add / remove); the VIF1 protocol relies on a cause raised before `EnableIntc` | VIF1: the native renderer's end of frame calls the handler directly (renderer lane) |
| event list (VBlank edges, timed waits, posted causes) | the driver's clock; the DMAC / GS models still post causes | goes with the renderer lane's models; SIF / CD completions already left it (NATIVE-IOP.md) |
| T0..T3 register model | `T0_COUNT` reads (`GfxEndFrame`, `GfxFlipBuffersMaybe`, the VIF1 latch) | already nominal; since 2026-10-18 the game reaches it through `rg_logic_t0_*` (`rg_logic_time.c`, routed by `port/hwaccess.h`), not the hwbus (NATIVE-CPU.md section 8) |
| `ps2k_charge` as a timed wait | memory-card / DMA-busy polls and spin hints wait for time to pass | goes with those callers |
| the 4,096-record trace ring (128 KB of the table's 221 KB) | the run hash folds the trace hash; the ring is for `ps2k_trace_dump` | could shrink (the hash does not need the ring) once identity with the old exe no longer matters |

Next, in order:

1. ~~Interpolated presentation between phases~~ (renderer lane, 2026-10-25: opt-in
   `display.interpolation`, presented from `pace_before_field` through `rg_pace_between`;
   docs/NATIVE-RENDER.md "Interpolated presentation"; not play-tested on a real high-refresh
   display yet).
2. VIF1 completion as a direct call from the renderer's end of frame (renderer lane).
3. `RG_NATIVE_ONLY` as the shipping default once the renderer lane lands (the oracle modes then
   live only in tests / tools).

### Battle: an outcome difference after the last common milestone

Power-on to field 23,300 (`out/nthreads/s5bat`): all 24 milestones of `hle` match `native`
(and `frame`), the last at vbl 22,957 (the battle intro unlocks). Later, `native` reaches game
mode 11 at vbl 23,217, `frame` at 23,255, `hle` not before 23,300. The first per-tick
difference is `depth_z` (the lens-flare occlusion depth read back from the Z buffer in
`GfxEndFrame`): vbl 22,939 native, 23,121 frame; every other tick column (feedback fb = 2,
counts, task runs, pad) is equal. Shots differ in every non-HLE mode from field 8,500 on (8,500:
2,478 pixels around a character's head, as documented for frame mode: animation phase).
Both alternative modes differ in the same way: a placement effect of the conversions (stream
/ file completion points relative to the game's polls), not of the frame-driven kernel; the
native run itself is deterministic (fixtures below reproduce battle +300).

## 6. Files touched outside the lane

- `src/savestate/ss_map.c`: two policy rows (`kcensus.c.obj` HOST, kernel `_k_tap` HOST)
  (slice 1). The kernel hooks (`k_start_hook`, `k_signal_hook`, and since slice 5
  `k_phase_hook`, `k_parked_hook`, `k_block_hook`) are constant per exe and stay MODEL
  statics; no new row.
- `src/runtime/runtime.c`: `rg_threads_field_end()` after each field's `ps2k_step` and its
  include (slices 2-3); slice 5: `kc.native` + the native-audio fallback (kernel init), DMAC
  `cycles_per_qword` = 0 and `hwbus_set_read_cycles(0)` when the kernel is frame-driven
  (after `hwbus_bind`).
- `src/sce/graphics/libgraph.c` (`sceGsSyncV` only) + `src/sce/graphics/CMakeLists.txt`
  (links `rg_native_threads`).
- `docs/KERNEL.md`: "Service threads and census tap", "Frame-driven mode", test table.
- `overrides/src/main/file/CdDiskWatchThread_17fdc0.c` (the native-FS lane's, finished:
  split); `overrides/src/main/file/CdDiskWatchWakeIsr_17ff10.c` removed (its body was the
  generated one).
- New, owned: `src/native/threads/rg_frame.c` (+ `rg_threads.[ch]`), the overrides listed
  in the table at the top, `src/sce/kernel/kcensus.[ch]`, `include/port/native_threads.h`,
  `tools/native/thread_census.py`, `thread_compare.py`, `thread_perf.py`, `thread_sample.py`.
- Owned, edited: `src/ps2/kernel/{ps2k.h,internal.h,kcore.c,kirq.c,kstate_ss.c}`,
  `src/sce/kernel/{eekernel.c,CMakeLists.txt}`, `src/ps2/spin/{spin.c,CMakeLists.txt}`
  (links `rg_native_threads`), `src/native/threads/CMakeLists.txt`,
  `tests/kernel/{kernel_tests.c,CMakeLists.txt}`.
- 2026-10-25 (stream close): new override `overrides/src/main/sound/SoundRpcWorkerKick_1bd6a0.c`
  (driver point after the kick; table above).
- Not edited: `tools/ingest.py` (`--check`: 0 problems, 204 overrides), `src/native/fs`,
  `game/`, other lanes' overrides (`GameSessionInit_1f5d80`, `SoundRpcInit_1bc840`,
  `MoviePlayerWaitTick_1d5810`, `GfxVblankStartHandler_15df20`), no gfx override.

- Evening (native kernel table / native-only / paced mode): new `src/native/threads/{rg_nk.c,
  rg_nk_irq.c,rg_nk_ss.c,rg_nk_internal.h,rg_pace.[ch],rg_spin_native.c,rg_threads_oracle.h}`,
  `kapi/` (moved `ps2k.h`, `ps2k_ss.h` + generated `ps2k_api.inc`, `ps2k_rename.h`), `fiber/`
  (moved from `src/ps2/kernel`), `src/ps2/kernel/kdispatch.c`, `tools/native/thread_api.py`;
  edited (owned) `src/ps2/kernel/{kcore.c,kirq.c,internal.h,kstate_ss.c,CMakeLists.txt}` (HLE
  frame-driven code removed, `ps2k.h` / `ps2k_ss.h` forwarders), `src/native/threads/{rg_threads.
  [ch],rg_frame.c,CMakeLists.txt}`, `src/sce/kernel/{kcensus.[ch],CMakeLists.txt}`,
  `include/port/native_threads.h`, `overrides/src/main/sys/WaitVsyncCount_15de90.c` (logic-tick
  count), `cmake/native_only.cmake`, `tests/native_only/CMakeLists.txt`, `tests/kernel/*`,
  `tools/native/thread_compare.py` (`--input`, `--spec`); localized: `src/runtime/runtime.c`
  (paced mode: `pace_*`, the present decision, the kernel pacing hook wrapper),
  `src/settings/rg_settings_core.c` (`display.pacing`, help texts), `src/savestate/ss_map.c`
  (rows `_NK`, `_nk_tap`, `rg_spin_native.c.obj` hooks), `tools/native/link_audit.py`
  (`rg_sce_kernel_native` native, kernel lane notes), docs KERNEL.md, NATIVE-ONLY.md,
  SETTINGS.md. Not edited: src/gpu, src/native/render, src/ps2/{gs,vif,dmac,vu,hwbus}, game/,
  tools/ingest.py, others' overrides.

## Checkpoint

- 2026-10-17: census tools + static/dynamic census; slice 1 (SysTick service step)
  implemented; unit + power-on 9,000 identity + title/field fixtures verified.
- 2026-10-18: identity to the first battle + 90 (run hash, 4 shots, 24 milestones);
  battle census appended; native fixture set `out/fixtures/a85e04512a204716` has title,
  field (with +300 checks) and battle. Resume at "What remains" item 1 (frame driver).
- 2026-10-18 (later): frame driver (`rg_frame.c`), slices 2-3: tick / stream slot / disk
  watch / file requests / 3 sound streams driven, loading-screen polls as condition waits,
  file requests on native-FS async jobs; verified to the first battle (milestones, tick
  counts, read stream) and by the full native fixture set with battle +300
  (`out/fixtures/037d8aed5c4afb1a`). Resume at section 5 item 1 (loading screen coroutine).
- 2026-10-18 (late): slices 4 + 5: kernel frame-driven mode (`RG_THREADS=native`; the old
  native is `frame`), loading screen as the second flow, sound workers converted,
  `sceGsSyncV` / `ThreadYield` driver points, disk-watch override split (ISR copy removed),
  DMA / register costs out of the clock. Verified: `hle` run hash unchanged; hle vs native
  milestones identical to the first battle (0 of 23 segments); native fixtures
  `out/fixtures/422115d6b5f4ee01` (title / field / battle +300); ctest 61/61. Resume at
  section 5 "Next" item 1 (paced mode).
- 2026-10-18 (evening): native kernel table (section 3e), RG_NATIVE_ONLY without the kernel
  HLE (3f, link audit `--forbid iop,kernel` PASS), paced mode (3g, `display.pacing`). Verified
  (section 4 "Native kernel table, native-only, paced mode"): native run hash unchanged to
  31,700 in both builds, hle / frame unchanged, fixtures 7/7 (`out/fixtures/cb8db675e1683f97`),
  ctest 128/128, paced smoke at caps none / 30 / 144 / VSync with no logic speedup. Build dir
  `build/nthreads-i686` is RG_NATIVE_ONLY=ON (rg-game + rg-game-oracle). Resume at section 5
  "Next" (interpolation hook: renderer lane).
