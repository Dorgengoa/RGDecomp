# Spin loops

The EE kernel HLE ([KERNEL.md](KERNEL.md)) runs one guest thread at a time, never
preempts it, and moves its virtual clock only at kernel calls, `ps2k_poll` /
`ps2k_charge`, or when every thread is blocked. A guest loop that waits for memory or a
hardware register to change, with nothing inside it that blocks, therefore never sees the
change: on the host it hangs (or, under clang, may be deleted, see "HALT" below). This
document is the census of those loops and the mechanism that handles them.

| Path | What |
| --- | --- |
| `tools/census/spin_loops.py` | The census (retail asm + source), writes `census/spin_loops.tsv` |
| `census/spin_loops.tsv` | One row per loop that polls something; `hint` column drives the stage |
| `tools/stages/spin.py` | Ingest stage `spin`: instruments the loops the table marks |
| `src/ps2/spin/` | `rg_spin_hint` / `rg_spin_halt` runtime (`spin.h`, `spin.c`, CMake target `rg_ps2_spin`) |
| `tests/spin/spin_tests.c` | 7 tests + 4 armed controls on the real kernel HLE |
| `tools/census/driven_wait.py` | Driven-thread busy-wait census -> `census/driven_wait.tsv` (section "Driven threads"); ctest `spin.driven_wait` + control |

## Census method

Ground truth is the **retail code**: all of MAIN (including the SDK band and the 186
functions the pinned snapshot still has only as asm) plus the five overlays, decoded with
the platform census loader (`tools/census/platform/common.py`, read-only).

1. **Loops.** Every backward branch whose target is inside the function (`b`, `beq`/`bne`,
   `bgez`.., `bc0f`/`bc1t`/`bc2t`, intra-function `j`). Back-edges to the same head are one
   loop. 7,895 loops in the six images.
2. **Does the loop yield?** A call graph from decoded `jal`/`j` plus each `syscall` stub's
   number gives every function a level: **BLOCK** (reaches `WaitSema` 0x44, `SleepThread`
   0x32, `Exit*`), **ROTATE** (`RotateThreadReadyQueue`), **KCALL** (any other syscall), none.
   `sceGsSyncV` and `VSync_116a30` are seeded BLOCK: retail busy-waits on `INTC_STAT`
   there, but the port's `sceGsSyncV` must block until VBLANK_START. A loop is SAFE only
   when a BLOCK call runs on every iteration (no branch in the body skips it).
   **KCALL and ROTATE do not count as yielding**: a kernel call is an interrupt delivery
   point, but no virtual time passes while the caller stays ready, so a loop around
   `PollSema` or `ThreadYield` still waits forever for a timed event.
3. **What is polled?** A register-taint pass over the loop body labels each load by its
   address: a constant (hardware register / GS / scratchpad / global), a field of a pointer
   the loop does not change (`ptr`), or a walk. Calls taint `$v0` with the callee's
   return summary (up to 3 levels; callee loads through an argument pointer are resolved
   when the caller passes a constant address). Spill slots carry taint. `bc0x` = CPCOND0
   (DMA), `cfc2 vi29` / `bc2x` = VU0 status. A loop is a **poll** when every exit
   condition depends only on such invariant locations (no induction variable, no pointer
   walk, no varying call result, nothing the loop stores itself).
4. **Who sets it?** Every constant-address store in every function, plus stores through
   an argument pointer at call sites that pass a constant address. Each writer is placed
   in the interrupt handlers and thread entries that reach it (PLATFORM.md §2).
5. **Source line.** Each retail loop is matched to a `while` / `for` / `do` / goto-label
   loop in the ingested `game/` file of its function: the loop whose condition (weight 3)
   or body (weight 1) mentions the polled symbol, hardware literal or callee, then
   position within the function, then the innermost. `src_match` says which.
6. **Cross-check from source.** A separate scan of every compiled `game/` unit for
   empty-body loops on globals or pointer fields and for `volatile` / hardware-literal
   loops was compared with the result. It found one loop the asm pass missed
   (`SoundStreamShutdown_1c0b70` line 105; its exit flows through a `volatile` local).
   That loop is a hand-reviewed `MANUAL` row in the census script. The other hits were
   iterators, VM dispatch loops, or loops that are already in the table.

Regenerate (about 15 s, using the cached platform pickle):
`python tools/census/spin_loops.py [--rebuild]`.

## Classes

| Class | Meaning | Handling |
| --- | --- | --- |
| SAFE | a BLOCK-level call runs every iteration | none |
| HW | waits on a hardware status (DMA CHCR/QWC, `D_STAT`, CPCOND0, VIF/GIF/IPU status, GS CSR, `INTC_STAT`, VU0 status) | the model answers at once; HW accessor charges per read |
| TIMER | busy-waits on T0..T3 COUNT | HW accessor charges per read |
| HANDLER-FLAG | waits on memory written by a handler, another thread, a callback or the IOP | stage `spin` hint |
| SDK-POLL | the exit depends on an SDK status function called in the loop | the `src/sce` function must let time pass or answer at once |
| HALT | a deliberate infinite loop: the condition is loop-invariant (error trap, or a non-volatile wait that mwcc compiled into a hang) | stage `spin` halt |
| PROGRESS | not a spin: the loop's own callees write the value | none |

## Results (119 rows)

| Image / lib | SAFE | HW | TIMER | HANDLER-FLAG | SDK-POLL | HALT | PROGRESS |
| --- | --- | --- | --- | --- | --- | --- | --- |
| main game | 19 | 3 | 0 | 10 | 4 | 14 | 0 |
| main sdk | 7 | 48 | 0 | 3 | 6 | 1 | 1 |
| main library (MSL/libc) | 0 | 0 | 0 | 0 | 0 | 1 | 1 |
| title | 0 | 0 | 0 | 1 | 0 | 0 | 0 |
| insmenu, normal, factory, insect | 0 | 0 | 0 | 0 | 0 | 0 | 0 |

- **No TIMER loop exists.** `T0_COUNT` is read only to measure frame time
  (`GfxEndFrame_141c20`, `GfxFlipBuffersMaybe_143650`, `Vif1IntcHandler_15e170`), never
  polled. The KERNEL.md worry about `T0_COUNT` polling loops does not apply to this game.
- **Game HW: 3 loops**, all `IPU_CTRL` busy-waits in the movie layer
  (`ViBufRestartDma_1d3e70` ×2, `ViBufStopDma_1d4180`), which the movie service replaces
  anyway (PLAN P4).
- **SDK HW: 48 loops**, all in asm-bodied SDK functions that `src/sce` replaces. They list
  what the replacements must answer immediately: `sceGsExecStoreImage` (9: VIF1 CHCR/STAT,
  GS CSR), `sceGsSyncPath` (5: VIF1/GIF CHCR, VIF1_STAT, VU0, GIF_STAT),
  `sceGsPutDrawEnv` (GIF CHCR), libmpeg/IPU (31: `IPU_CTRL`, IPU/SPR DMA), `VSync_116a30`
  (`INTC_STAT`, behind `sceGsSyncV`), `kputchar`.
- **Game SDK-POLL: 4 loops.** `IopRebootWithImage_15e560` spins on `!sceSifRebootIop()`
  and `!sceSifSyncIop()`, so the IOP HLE must return success at once.
  `CdDatArchiveOpen_183110` (×2) retries `sceCdSearchFile` until it is non-zero, so a
  missing file loops forever, as on retail.
- **SDK-internal SDK-POLL: 6 loops** (`sceSifInitCmd`, `sceSifInitRpc`,
  `sceSifExecRequest` ×2, `sceSifRpcLoop`, `sceSdTransToIOP`). They are replaced with
  their functions.

### HANDLER-FLAG loops (instrumented)

| Site | Function | Waits for | Set by | Yields today |
| --- | --- | --- | --- | --- |
| 0x001BFF4C | `SoundStreamQueueStop_1bff30` (label `A`) | stream object busy/ring state | stream thread | WaitSema(mutex)/PollSema/SignalSema = KCALL |
| 0x001C02B8 | `SoundStreamWaitFileSize_1c02a0` (`loop_1`) | same | stream thread | KCALL |
| 0x001C0530 | `SoundStreamWaitIdle_1c0510` (`loop_1`) | same | stream thread | KCALL |
| 0x001C0638 | `SoundStreamProcessCmds_1c05f0` | command ring | main thread | WaitSema(cmd sema), conditional |
| 0x001C0C54 | `SoundStreamShutdown_1c0b70` l.105 (manual) | stream busy | stream thread | KCALL |
| 0x001C0CF8 | `SoundStreamShutdown_1c0b70` l.113 | stream busy | stream thread | KCALL |
| 0x001D2A00 | `VideoDecDecodeBs_1d29e0` | `VoBufGetData(D_004B3330)` (count `D_004B3340/44`) | `VoBufDecCount` (DefMain) | ThreadYield = ROTATE |
| 0x001D5274 | `VideoDecMain_1d5240` | `D_004B3340[0] == 0` | VoBuf* (movie threads) | ROTATE |
| 0x001D5700 | `MoviePlayerShutdown_1d56c0` | `D_004817E0` | `MovieReadThread_1d4f50` | ROTATE |
| 0x104F07BC | `title_TitleMoviePlay_4f0600` | `MovieIsStarted()` → `D_004817BC` | `MovieOpen`, `MovieReadThread` | ROTATE |

Not instrumented:
- `MoviePlayModal_267c60` @0x267F28 has the same `MovieIsStarted` wait, but it has no
  source in this snapshot (asm-only unit). On the clean snapshot the census gives it a
  line and the stage picks it up.
- `sceTtyWrite` / `sceTtyRead` are replaced. `KernelSetAlarm_447260` is the unreached
  kernel-patch island.

### HALT loops (instrumented, 14 in game)

Error traps `for (;;) {}`:
- `CdDatArchiveOpen` l.92: allocation failure;
- `ResidentFileReadMaybe`: forbidden path prefix;
- `BlockHeapFree`: node not found;
- `MapScriptCmdTableBuild`, `SystemVmBuildCmdTable`, `AiScriptVmBuildCmdTable` and
  `ScriptVmInitWithCmdTable`: duplicate command id.

`SoundThreadStart_1b6160` hangs when thread or sema creation fails.

There are also six `MemStack*` "wait while locked" loops (`while (p->lock != 0) {}`).
The field is not volatile, so mwcc hoisted the load and retail **hangs for good** if the
loop is ever entered. Under clang the same C loop is worse. C11 6.8.5p6 lets the compiler
assume a side-effect-free loop with a non-constant condition terminates, so clang may
delete it outright, and the code would carry on past a locked stack. `rg_spin_halt` is
an opaque call, so it keeps the loop and reports it (default: message + `abort()`).

## Mechanism

Two complementary pieces, each deterministic (the charge depends only on iteration
counts):

**(b) Table-driven hint: chosen for memory waits and HALT.** Stage `spin` rewrites
exactly the loops the table marks (`hint` = `hint` | `halt`), in the controlling
expression *after* the condition, so the call runs once per iteration that actually
continues. A loop whose flag is already set costs nothing, and `continue`/`goto` paths
are covered.

```
while (c)          ->  while ((c) && (rg_spin_hint(SITE), 1))
do ..; while (c);  ->  do ..; while ((c) && (rg_spin_hint(SITE), 1));
for (i; c; s)      ->  for (i; (c) && (rg_spin_hint(SITE), 1); s)
for (;;)           ->  for (; (rg_spin_hint(SITE), 1);)
label: .. goto label;  ->  label: rg_spin_hint(SITE); ..
```

`SITE = (image index << 28) | retail loop head`, so every report names a retail
instruction. A one-line `extern` declaration (`extern "C"` in C++) is prepended to an
instrumented file. Once `include/port` gets a `port/spin.h` in the prelude, that line can
go. Loops are located by function name + loop kind + normalised header text, nearest to
the table line, so earlier stages that move lines do not break it. A row that does not
resolve to exactly one loop is an error, never a guess. The stage is idempotent.

`rg_spin_hint(site)` = `ps2k_charge(cycles_per_iter)` (default 32 bus cycles, about one
retail iteration). That advances the clock, processes due events, delivers interrupts
and lets a thread a handler readied preempt the spinner. It also reports, once per
episode, three things:
- a wait longer than `report_cycles` (default 10 s virtual);
- a spin with EIE = 0, which nothing can end;
- a spin inside a handler.

`rg_spin_halt(site)` reports (default: stderr + `abort()`). With a hook installed, it
parks the thread (`SleepThread` forever) and the other threads keep running.

**(a) Accessor charge: for hardware.** Transform 5 rewrites hardware-register reads to
`HW_R32()`. That accessor should call the owning model (`ps2k_hw_read32` for timers,
INTC and `D_STAT`; the DMA/GS/IPU models for the rest) and then `ps2k_charge(n)` with a
small n (writes charge nothing). That covers every hardware poll without a table,
including ones this census cannot see (computed addresses), at the cost of perturbing
time slightly on non-loop reads, which retail also pays. In this game it matters mainly
as a safety net: no game TIMER loop exists, and the 3 game HW loops are in the movie
layer that is being replaced.

**Why (b) and not (a) for memory flags.** (a) cannot see plain memory: a flag in `.bss`
is not a register access. Charging every global load is impossible and would perturb
everything. (b) touches 24 loops in 23 files, names each one, and leaves every other
loop byte-for-byte as decompiled.

**Alternative considered: kernel-side charge.** Setting `cfg.kcall_cycles > 0`, or
making `RotateThreadReadyQueue` / a non-blocking `WaitSema` charge time when nothing else
is ready, would release the KCALL/ROTATE loops above without instrumentation. But it
changes the timing of every kernel call in the game, and it does nothing for the HALT
loops or for loops with no kernel call. If wanted, it is a kernel change (not made here).

### Requirements on `src/sce` (from the SDK-POLL / HW / SAFE rows)

- `sceGsSyncV` must block (wait for the next VBLANK_START). Retail busy-waits on
  `INTC_STAT` (`VSync_116a30`). Game wait loops that call it (e.g. `PadWaitReady_1849e0`)
  are safe only because of that.
- `sceGsSyncPath`, `sceGsPutDrawEnv`, `sceGsExecStoreImage`, `sceDmaSync`: complete the
  DMA/GS work synchronously, or block. Never return "busy" to a caller that loops.
- `sceSifRebootIop`, `sceSifSyncIop`: return 1 immediately.
- `sceSifDmaStat`: callers loop with `DelayThread(10)`, so completion on the virtual
  clock is fine.
- `sceCdSync(1)`, `sceMcSync(1)`, `PollSema`, `MpegIsEnd`, and any other status query a
  caller may poll: let time pass inside (`ps2k_charge`) or answer from a model that
  completes on the clock. `sceCdSync(0)` blocks through the drive wait hook (CDVD.md).
- `sceCdSearchFile` / `sceCdLayerSearchFile`: `CdDatArchiveOpen` retries until success.
  A file missing from `data/` therefore hangs, as on retail. Log it.

## Wiring (done)

`tools/ingest.py` runs `spin` LAST (`int128, gccvarargs, vu0asm, asmexclude, protos,
dialect, spin`), so `protos` never sees `rg_spin_*` as an undeclared game symbol, and
prints `SpinStage.report()`; any row error makes ingest exit 1. On the 2efa6b43 ingest it
instruments the same 24 loops (10 hint, 14 halt) in 23 files with 0 errors, and every
inserted call sits within 3 presumed lines of its table row.

Line matching survives the `protos` preamble: the stage measures *presumed* lines
(`#line N` honoured), and the protos preamble ends in `#line 1`. The declaration line
`spin` prepends is followed by `#line 1` as well, so compiler diagnostics keep the
original line numbers.

CMake: `src/ps2/spin` (`rg_ps2_spin`) and `tests/spin` (`rg-spin-tests`, `ctest -L spin`)
are in the top-level build. Link `rg_ps2_spin` into the game executable when it exists.

## Verification

- **Stage, on a copy:** `python tools/stages/spin.py --out out/spin-test` (`--full`
  copies all of `game/`; the default copies `include/`, `config/` and the touched files).
  Result: 24 loops in 23 files (10 hint, 14 halt), 0 errors, idempotent (a second pass
  changes nothing). `clang -fsyntax-only` with the port flags reports 0 errors on all 23
  files, the same as the originals.
- **Runtime:** `rg-spin-tests` on the real kernel HLE:
  - `handler_flag`: leaves at the first VBLANK_START, exactly ⌈t/32⌉ iterations;
  - `thread_flag`: a higher-priority thread woken by `DelayThread(1000)` preempts the
    spinner at 147,456 cycles exactly;
  - `rotate_flag`: the movie `ThreadYield` shape;
  - `determinism`, `di_report`, `halt`, `long_wait`.

  All pass. The controls `handler_flag_control`, `thread_flag_control` and
  `rotate_flag_control` run the uninstrumented loop and fail, so the hazard is real and
  the checks are armed. `determinism_control` perturbs the charge by one cycle and also
  fails. Built by hand with clang (i686) for this run. The CMake target is declared in
  `src/ps2/spin/CMakeLists.txt`.

## Driven threads (census `tools/census/driven_wait.py`, 2026-10-25)

Since the native frame driver (docs/NATIVE-THREADS.md "Driven threads") most game threads are
*driven steps*: a non-`sync` conversion (stream slot, tick) runs only at a driver point; a
`sync` one runs at the signal of a lower-priority signaller. A loop on a game flow that
signals such a step and then polls what the step would write spins forever natively, although
on the EE the signal switched to the waiter at once. The spin census above classed those
loops SAFE through their `WaitSema` (a WaitSema on a free mutex blocks nothing and is no
driver point): the Insectron return-to-title hang (`SoundStreamSlotShutdown_1bdfd0`,
BRINGUP-HISTORY "2026-10-25 (stream close)").

`driven_wait.py` (same retail loader / loop finder as spin_loops.py; ~15 s) lays the port's
driver points over the retail code: the conversions are parsed from the overrides
(`rg_thread_conv`: entry, sync, old priority), each thread's wake semaphores are the ones its
entry (and direct callees) wait on and never signal themselves, every `SignalSema` /
`iSignalSema` / `WakeupThread` / `ResumeThread` site's sema id comes from a register
simulation (a global id, or the field offset), and a function is a driver point when it is
one of WaitVsyncCount / DelayThread / sceGsSyncV / VSync / RotateThreadReadyQueue /
ThreadYield, when its OVERRIDE calls `rg_frame_point` / `_delay` / `_wait_cond` / `_yield` /
`_frame_wait`, or when the spin stage hints its loop. Classes per loop (TSV
`census/driven_wait.tsv`):

| Class | Meaning | Count (2026-10-25) |
| --- | --- | --- |
| WAKE-SYNC | wakes only `sync` steps whose old priority is above the signaller's (they run at the signal) | 141 |
| WAKE-DP | wakes a non-sync step; a driver point is reached on every iteration (<= 2 calls deep) | 4 (MoviePlayModal x2, the two inner `while (busy) kick();` loops of SoundStreamSlotShutdown, fixed by the kick override) |
| WAKE-DP-SOME | a driver point only on some iterations / deeper: reviewed by hand (`REVIEWED` in the script, with the reason) | 4, all reviewed (SoundStreamSlotShutdown outer loops: every iteration kicks; GameFrameUpdate / GameModeDispatch mode re-dispatch: no exit on slot state) |
| WAKE-ONCE | wakes, no driver point, every exit an induction / walk test (signals per element, ends by itself; the step runs at the caller's next driver point) | 2 (StreamMgrCloseAll, StreamMgrUpdate) |
| BUSY-WAIT | wakes a non-sync step, no driver point, a poll exit: **the bug class** | **0** (2 with `--no-overrides`: the 2026-10-25 kick loops) |
| IN-STEP | a loop inside a driven step whose wake is deferred (equal priority) | 0 |
| SAFE-NONDP | no wake, SAFE for the spin census only through a non-driver-point WaitSema, polls memory a driven thread or an ISR writes | 5, all replaced SDK code (`sceSdRemoteInit`, `scePadInit` x2, `sceMcInit`, `SceFsInit`: src/sce) |
| SAFE-NONDP-PTR | the same on a pointer field nothing in the loop writes (setter unknown: review) | 0 |

`--check` exits 1 on an open row (BUSY-WAIT, SAFE-NONDP*, WAKE-DP-SOME in a compiled unit not
reviewed). ctest: `spin.driven_wait` and its control `spin.driven_wait_control`
(`--no-overrides`: must find the two kick loops; WILL_FAIL); both skip (77) without the
retail images / platform cache. Fix for a new BUSY-WAIT: an override of the signalling
function ending in `rg_frame_point()` (as `SoundRpcWorkerKick_1bd6a0`); a stage rule if a
family ever shows up. Limits: may-analysis through callees (a driver point deeper than 2
calls counts as "some"), sema ids through pointer fields matched by offset only, flows found
by direct calls from `Main_15e700` / the loading screen (code reached through function
pointers shows ctx `?`).

## Limits

- The census only sees exits through constant addresses, invariant pointers, argument
  pointers passed as constants, and SDK status calls. A wait whose condition is reached
  through a function pointer, or computed through memory the taint pass loses, can be
  missed. The source cross-check found one such loop, which is now a manual row.
- "Yields" is a may-analysis on retail callees. A loop marked SAFE through an SDK
  function relies on the `src/sce` replacement blocking the way retail did.
- Setter contexts come from static reachability from the known handler and thread
  entries. Callback-driven writers (libcdvd/SIF callbacks, function pointers) show as
  bare function names.
- The table pins `game/` line numbers of the 2efa6b43 ingest. After a re-ingest from the
  clean snapshot, re-run the census before the stage; the stage refuses rows it cannot
  match.
