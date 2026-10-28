# EE kernel HLE

PLAN.md P2, "EE kernel". A host library that gives the game the EE kernel's
thread, semaphore, interrupt, alarm and timer semantics. It is independent of
the game build. All of it was written from scratch from the census, the game's
own call sites and public PS2 hardware documentation. No GPL code was used.

| Path | What |
| --- | --- |
| `src/ps2/kernel/ps2k.h` | Core API (`ps2k_*`): scheduler, threads, semaphores, interrupts, alarms, timers, clock, trace |
| `src/ps2/kernel/kcore.c` | State, trace, scheduler loop, threads, semaphores, `DelayThread` |
| `src/ps2/kernel/kirq.c` | Virtual clock and event queue, INTC/DMAC handler chains and delivery, alarms, T0..T3, register accessors |
| `src/ps2/kernel/fiber.h` | Fiber backend interface (adopt host thread, create, switch, destroy) |
| `src/ps2/kernel/fiber_win32.c` | Windows Fibers backend (in use) |
| `src/ps2/kernel/fiber_ucontext.c` | POSIX `ucontext` backend (Linux; stacks mmapped below 2 GB with a guard page, [LINUX.md](LINUX.md)) |
| `src/sce/kernel/eekernel.[ch]` | SDK names and structs (`CreateThread`, `WaitSema`, `AddIntcHandler`, ...) as thin wrappers, plus the game-tree symbol names |
| `tests/kernel/` | CTest suite (`rg-kernel-tests <name>`, label `kernel`) |

CMake targets: `rg_ps2_kernel`, `rg_sce_kernel`, `rg-kernel-tests`.

## Execution model

- **One host thread owns the kernel.** `ps2k_run(main, arg, prio)` turns the
  calling host thread into the scheduler fiber, creates guest thread 1 for
  `main`, and loops. Each guest thread is a host fiber with its own host stack
  (1 MiB reserve by default, `cfg.host_stack_size`). The guest stack that the
  game passes in `ThreadParam` is recorded and returned by `ReferThreadStatus`,
  but nothing runs on it.
- **Exactly one guest thread runs at a time.** A thread runs until it blocks,
  yields, exits, or is preempted at a defined point (below). The scheduler
  always picks the head of the highest-priority non-empty ready queue
  (0 = highest, 127 = lowest). Queues are FIFO within a priority.
- **Preemption happens only at defined points.** The EE kernel itself is
  preemptive only through interrupts. Here interrupts are latched and
  delivered only at these points:
  1. the entry of every thread-context kernel call (`k_enter`),
  2. `EIntr`/`EnableIntr` and `EnableIntc`/`EnableDmac`, which libkernl ends with `ei`,
  3. `ps2k_poll()` / `ps2k_charge()`, called by models and overrides,
  4. the scheduler loop (kernel/idle context), before every switch-in.

  After delivery, if a handler readied a thread with strictly higher priority
  than the running one, the running thread goes back to the **head** of its
  ready queue and the other thread runs. A kernel call that readies a
  higher-priority thread (`SignalSema`, `WakeupThread`, `StartThread`,
  `ChangeThreadPriority`, `ResumeThread`, ...) switches immediately, as the
  real kernel does.
- **Termination of `ps2k_run`:**
  - `MAIN_EXIT`: thread 1 returned, or called `ExitThread`, or was terminated.
  - `STOPPED`: `ps2k_request_stop()` was called.
  - `TIME_LIMIT`: `cfg.stop_at_cycles` was reached.
  - `DEADLOCK`: nothing is ready and no event is queued.
  - `STALL`: nothing was ready for `cfg.stall_cycles` of virtual time, while
    VBlank events kept the queue non-empty.

## Interrupt-enable state (the recomp's deadlock cause)

The retired recomp lost every `StartThread` because COP0 Status.IE read 0.
libkernl's `StartThread` (via `CpuIntrDisabled_117070`) treats IE == 0 as
"inside an interrupt handler" and returns -1. The model keeps two separate bits:

| Bit | Meaning here |
| --- | --- |
| Status.IE (bit 0) | 1 in thread and kernel context, 0 inside a handler. `ps2k_cop0_status()` synthesises it; `CpuIntrDisabled_117070()` returns `!IE`. |
| Status.EIE (bit 16) | The `DI`/`EI` flag. **Global thread-context state** (retail, [VALIDATION.md](VALIDATION.md) 2e): a context switch neither saves it per thread nor restores it, so a `di` before a blocking call carries over to the next thread, and a new thread starts with whatever EIE is current (not 1). Handlers start with EIE = 0. An `ei` inside a handler (every game handler ends with `sync; ei`) changes only the handler's copy. `cfg.eie_per_thread = 1` selects the earlier per-thread model (saved on switch-out, restored on switch-in, new threads start with EIE = 1); default 0 = retail. |

- Delivery in thread context requires EIE = 1. A thread that disables
  interrupts and keeps running sees no handlers, even across kernel calls.
- A thread that **blocks** with EIE = 0 does not stop the system. The
  scheduler (kernel context, EIE = 1) delivers pending interrupts. The next
  thread then runs with EIE = 0 (retail, VALIDATION.md 2e) until someone
  executes `ei`; the blocked thread wakes with the then-current EIE.
  Confidence medium (one observation); whether the retail idle loop
  re-enables interrupts was not measured, so kernel/idle context keeps
  delivering as before.
- `DisableIntr_120660`/`DIntr` and `EnableIntr_1206b0`/`EIntr` return the
  previous EIE (1 = was enabled). That matches the retail asm: the game's
  `t = DisableIntr(); ...; if (t) EnableIntr();` pattern works unchanged.
- `DelayThread` returns `0x80008008` when EIE = 0, as libkernl does.

## Context rules ("i" functions)

- Every kernel call is a thread-context call or an "i" call. An "i" call
  outside a handler, or a thread-context call inside one, is a **violation**.
  The violation hook runs (default: print and `abort()`; tests install a
  recorder), and the call returns -1 without acting.
- One exception follows libkernl: `StartThread` / `StartThread_1176e0` inside
  a handler returns -1 **silently**, because the retail wrapper checks IE
  before it issues the syscall.
- Blocking calls (`WaitSema`, `SleepThread`, `DelayThread`, `ExitThread`)
  outside a guest thread are violations. Non-blocking calls such as
  `CreateSema` are allowed from host code before `ps2k_run` for setup.

## Interrupts

- **INTC** causes 0..14 and **DMAC** channels 0..9 each have a STAT bit and
  a MASK bit. A model raises a cause with `ps2k_raise_intc` / `ps2k_raise_dmac`
  (now) or `ps2k_post_intc` / `ps2k_post_dmac` (after a virtual delay). The
  STAT bit stays latched, masked or not, until delivery. So enabling a cause
  whose bit is already latched delivers at once. This level-held behaviour is
  what the recomp needed to stop losing VIF1 signals.
- **Delivery order:**
  - INTC causes in ascending order, then DMAC channels in ascending order,
    then kernel alarms in firing order.
  - The kernel clears the STAT bit, then runs that cause's handler chain.
- **Handler chains** (`AddIntcHandler(cause, fn, next)`, also `AddDmacHandler`):
  - `next == 0` inserts at the head, `next == -1` appends at the tail
    (measured, VALIDATION.md 2a). Any other value also appends.
  - A handler is called as `fn(cause)`. The `...Handler2` variants are called
    as `fn(cause, arg, NULL)`.
  - The chain stops only at the first **negative** return; 0 and positive
    values continue (VALIDATION.md 2a, real BIOS kernel).
  - Ids: INTC and DMAC handlers share **one** id range 1..128
    (`PS2K_HANDLER_ID_MAX`), allocated next-fit from the id after the last
    one given out, wrapping and skipping ids in use (VALIDATION.md 2c: boot
    gives INTC 1, DMAC 2, DMAC 3 after 2 was removed, INTC 4, 5; the per-frame
    VIF1 add/remove walks 6..128 and wraps to 2). Up to 16 handlers per cause.
- `EnableIntc`/`DisableIntc`/`EnableDmac`/`DisableDmac`, and their `i` forms,
  return 1 if the mask changed and 0 if it was already in that state.
- Registers are modelled by `ps2k_hw_read32` / `ps2k_hw_write32`.
  `ps2k_hw_claims(addr)` tells the future `HW_*` accessor which ones are
  handled here:
  - `INTC_STAT`: write 1 to clear.
  - `INTC_MASK`: write 1 to toggle.
  - `D_STAT`: low bits are write-1-to-clear status, bits 16+ toggle the mask.

## Virtual clock

- **Units:** bus cycles, at 147.456 MHz. `ps2k_now()` returns the current time.
- **Advance:** the clock moves only in two ways:
  - the scheduler is idle: it jumps to the next queued event (or the next
    due time of a registered device, below), after calling
    the pacing hook `ps2k_set_pacing_hook(fn)` with (from, to);
  - something calls `ps2k_charge(cycles)` explicitly. There is also an
    optional per-kernel-call charge, `cfg.kcall_cycles`, default 0.

  Nothing reads the wall clock. Events at the same time fire in insertion
  order, so a run is a pure function of its inputs.
- **NTSC timing**, exact rational arithmetic in units of 1/2625 bus cycle:
  - field = 2,460,060 cycles: matches PCSX2, BUSCLK / 59.94 (tools/trace measures
    4,920,120 EE cycles per field), so virtual time lines up with reference traces.
    Exact NTSC (BUSCLK × 1001 / 60000) would be 2,460,057.6. Until 2026-10-11 the
    constant was 2,460,076.8, an arithmetic slip that matched neither;
  - hsync = field / 262.5 = 9,371.66 cycles (15,734 Hz).
- **VBlank:**
  - VBLANK_START of field k is at `floor((k·field + 240·hsync))`. The line is
    set by `cfg.vblank_start_line`.
  - VBLANK_END is at `floor((k+1)·field)`.
  - The first VBLANK_START is at about 15.25 ms.
  - VBlank events can be turned off (`cfg.vblank_enable = 0`).
  - `ps2k_vblank_count()` counts VBLANK_START events.

## Platform glue (added for src/runtime, docs/RUNTIME.md)

- **Stepping.** `ps2k_run` = `ps2k_start` + `ps2k_step(0)` + `ps2k_finish`.
  `ps2k_step(until_vblank)` returns `PS2K_RUN_YIELD` at the first
  scheduler-context point where `ps2k_vblank_count() >= until_vblank` (that
  VBLANK_START processed and its interrupts delivered), with every guest thread
  intact; any other return is terminal. The runtime runs one field per step.
- **VBlank observers** (`ps2k_add_vblank_observer`, up to 16) run when a
  VBLANK_START/END event is processed, at its exact cycle, after the cause is
  latched and before any handler. They must not make thread-context kernel calls
  (they can run on a guest fiber inside a kernel call).
- **Devices** (`ps2k_add_device`, up to 8): `next(user, &due)` and
  `poll(user, now)`. The idle jump stops at the earliest due time, an idle kernel
  with a due device is not deadlocked, and every event pass polls each device in
  handler context after the kernel's own events. The CDVD drive is one.
- **Kernel-private waits** take no game-visible id:
  - `ps2k_wait_vblank()` readies the thread after the next VBLANK_START's
    handlers and the alarms due with it (the order the old `sceGsSyncV` alarm
    had); `sceGsSyncV` uses it.
  - `ps2k_wait_until(t)` readies it at the event pass at cycle `t`, before
    devices are polled (so the CDVD wait hook sees its command complete).
  - `ReferThreadStatus` reports status WAIT, wait type 0, for both.
- **Accessors:** `ps2k_vblank_start_line()`, `ps2k_vblank_enabled()`,
  `ps2k_vblank_start_time(k)`, `ps2k_vblank_end_time(k)`.
- Tested by `tests/runtime` (`vblank_rate`, `kernel_glue`, `cdvd_async`); the 16
  kernel tests are unchanged and pass.

## Alarms and DelayThread

- **`SetAlarm(time, fn, arg)` / `iSetAlarm`:**
  - `time` is in hsync units. The alarm fires at the first cycle of hsync
    `(current hsync + time)`.
  - Alarms are one-shot. Up to 64 can be active.
  - The callback runs in handler context as `fn(id, (u16)hsync, arg)`.
  - `ReleaseAlarm` cancels an alarm that has not been delivered yet.
- **`ps2k_set_cycle_alarm`** is the bus-cycle alarm behind libkernl's
  `SetTimerAlarm`.
- **`DelayThread(usec)` follows libkernl's own algorithm:**
  1. If EIE = 0, return `0x80008008`.
  2. `CreateSema(init 0, max 1)`; if that fails, return `0x80008003`.
  3. Set a timer alarm `floor(usec × 147456 / 1000)` bus cycles ahead. The
     alarm does `iSignalSema`.
  4. `WaitSema`, then `DeleteSema`, then return 0.

  So `DelayThread` uses up and frees a semaphore id, exactly as retail does.

## Id numbering (VALIDATION.md 2c)

- **Threads:** main = 1 (`ps2k_start`). Created threads start at 2 and are
  allocated next-fit: the cursor moves past each id handed out, so a freed id
  is not reused until the cursor comes round (observed: after 10-13 were
  deleted the next ids were 14, 15, ...). The cursor wraps over
  1..`PS2K_MAX_THREADS`-1 skipping ids in use; the retail wrap point was not
  reached in the measurements, so the wrap is an assumption.
- **Semaphores:** ids start at **0**, and the most recently freed id is
  reused first (a LIFO free list, initially 0, 1, 2, ...). Id 0 is valid: the
  game tests sema ids with `>= 0`. Every synchronous SIF RPC's per-call
  semaphore therefore gets the same id each time.
- **Handlers:** above (one shared INTC/DMAC range).
  That matters for state-trace comparison, because sema ids are visible to
  the game.

## Timers T0..T3

- Each timer keeps COUNT/MODE/COMP (and HOLD on T0/T1) and is computed lazily
  from the virtual clock.
- **MODE bits:**
  - CLKS: BUSCLK, /16, /256, or HBLNK.
  - ZRET, CUE, CMPE, OVFE.
  - EQUF/OVFF are set by events and cleared by writing 1.
- **Interrupts:** a compare or overflow schedules an event that sets the flag
  and raises INTC cause 9+n.
- **Game setup:** the game writes `T0_MODE = 0x83` (HBLNK, count enabled).
  It then reads and writes `T0_COUNT` directly (`GfxEndFrame_141c20`,
  `GfxFlipBuffersMaybe_143650`, `Vif1IntcHandler_15e170`). Those accesses must
  be routed to `ps2k_hw_read32`/`write32` by the address-literal transform
  (PLAN transform 5).

## SDK surface (`src/sce/kernel`)

- **SDK names** take the SDK structs, with the same field offsets as the
  game's per-file copies:
  - `struct ThreadParam` (48 bytes);
  - `struct SemaParam` (24 bytes).
- **Functions:**
  - Threads: `CreateThread`, `DeleteThread`, `StartThread`, `ExitThread`,
    `ExitDeleteThread`, `TerminateThread`, `ChangeThreadPriority`,
    `RotateThreadReadyQueue`, `ReleaseWaitThread`, `ReferThreadStatus`,
    `GetThreadId`, `SleepThread`, `WakeupThread`, `CancelWakeupThread`,
    `SuspendThread`, `ResumeThread`, `DelayThread`.
  - Semaphores: `CreateSema`, `DeleteSema`, `SignalSema`, `WaitSema`,
    `PollSema`, `ReferSemaStatus`.
  - Interrupts: `Add/RemoveIntcHandler(2)`, `Add/RemoveDmacHandler(2)`,
    `Enable/DisableIntc`, `Enable/DisableDmac`, `DIntr`, `EIntr`.
  - Alarms: `SetAlarm`, `ReleaseAlarm`.
  - Cache: `FlushCache`, `iFlushCache`, no-ops (host memory is coherent and the
    DMA models read it directly; moved here from `src/crt/crt_ee.c`).
  - Every one that has an `i` form in the SDK has it here too.
- **Game-tree symbols** of the asm-bodied libkernl units, for transform 6 to
  bind:
  - `StartThread_1176e0`, `DelayThread_117618`;
  - `EnableIntc_1170e8`, `DisableIntc_117080`;
  - `EnableDmac_1171b8`, `DisableDmac_117150`;
  - `DisableIntr_120660`, `EnableIntr_1206b0`;
  - `CpuIntrDisabled_117070`.
- **Prototypes are not unified yet.** The game declares these functions
  inconsistently: `void f(void)` in about 30 files, `s32 f(s32)` in others
  (the census lists them). Transform 2 (prototype unification) has to point
  them at `eekernel.h`.
- **Name clash with Win32 (i686 is fine, x64 is not).** Win32 has functions
  with the same names: `CreateThread`, `ExitThread`, `TerminateThread`,
  `SuspendThread`, `ResumeThread`.
  - On i686 there is no clash: Win32 imports are stdcall-decorated
    (`_CreateThread@24`) and these are cdecl (`_CreateThread`). The tests
    link and call these through the same executable that imports kernel32.
  - A TU must not include both `eekernel.h` and `<windows.h>`.
  - On x64 the names collide. P7 needs a rename, e.g. `#define` to `sce_*`
    in ingest.

## Service threads and census tap (docs/NATIVE-THREADS.md)

- `ps2k_thread_set_service(tid, wait, step)`: a created, not started thread whose body is
  `for (;;) { s = wait(arg); if (s < 0) break; WaitSema(s); step(arg); }` runs without a
  fiber; the scheduler runs the loop on its own stack with every kernel-visible effect
  of the fiber version (trace hash identical: test `service_thread`). A blocking call in
  `step` aborts; a preemption it causes is deferred to its end (`ps2k_svc_deferred_count`).
  Used by `RG_THREADS=native` (the tick thread).
- `ps2k_set_census_tap(fn)` + `ps2k_peek_sema` / `ps2k_peek_priority`: measurement hooks
  for `RG_KCENSUS` (`src/sce/kernel/kcensus.c`); no behaviour change, not in the trace hash.
- Frame driver support (`RG_THREADS=native`, docs/NATIVE-THREADS.md "3b"): **driven
  threads** (`ps2k_set_start_hook`; the hook may `ps2k_thread_set_driven(id)`, and
  StartThread then parks the thread: status WAIT, no fiber, never readied;
  `ps2k_driven_wait(id, sema)` makes it a real waiter on its loop's semaphore, a signal
  marks it woken instead of readying it, `ps2k_driven_take` / `ps2k_driven_exit`);
  `ps2k_set_signal_hook` (a thread-context SignalSema that woke a parked thread calls it on
  the signaller); **poll waits** `ps2k_wait_poll(t)` (wake at `t` only if something else ran
  since this thread's last poll wait: another thread switched in, or a handler / alarm ran;
  `ps2k_activity()` counts those); `ps2k_vblank_end_count()`. Tests `poll_wait`,
  `driven_thread`, `frame_driver`. With `RG_THREADS=hle` none of this is used and the
  trace hash is unchanged.

## Frame-driven mode (`cfg.native`, `RG_THREADS=native`, docs/NATIVE-THREADS.md "Slice 5")

**Moved out of the HLE (2026-10-18):** this mode is now the native kernel table,
`src/native/threads/rg_nk*.c` (docs/NATIVE-THREADS.md "Native kernel table"), a second
implementation of the ps2k API (`src/native/threads/kapi/ps2k.h`). The HLE defines the API
as `ps2k_hle_*`; `src/ps2/kernel/kdispatch.c` defines `ps2k_*` and forwards to the table when
`ps2k_init` gets `cfg.native` (the HLE itself has no frame-driven code any more;
`ps2k_native()` is 0 there). RG_NATIVE_ONLY builds link the table under the real names and no
HLE. The description below is unchanged (the table reproduces it record for record: the run
hash of a native run is the same as before the move).

The native path's kernel: no EE scheduler. `ps2k_step` runs the host frame driver's loop
instead of the scheduler loop.

- **Flows.** Only game threads that are neither driven nor service threads get a fiber:
  on the golden route main (the game coroutine, thread 1) and the loading screen's frame
  loop. A flow runs until it waits (semaphore, kernel-private wait, `SleepThread`,
  `DelayThread`, a charge) and is never preempted: `k_enter`, `EI`, `EnableIntc` and
  `ps2k_poll` are not delivery points; a signal that readies another flow does not switch.
  Ready flows run FIFO when the running one waits (the ready queue orders simultaneous
  wakes by priority). Fibers come from the fixed-address arena when save states are on.
- **The pass.** Each time the driver regains control it processes due events, delivers
  what is latched (VBLANK_START / END chains, the VIF1 completion, SIF0: explicit calls in
  handler context), wakes kernel-private waiters, then calls the **phase hook**
  (`ps2k_set_phase_hook`: the frame driver runs the driven steps that may run anywhere,
  e.g. the tick, every VBlank), then resumes a ready flow or, when every flow waits, jumps
  logic time to the next event.
- **Logic time.** `K.now` moves only in that jump: a flow's own work costs nothing, so
  `T0_COUNT` reads give the nominal frame profile and the VBlank grid never interrupts a
  frame. `ps2k_charge` from a flow is a timed wait (the callers that still charge are
  polls waiting for time: SIF, memory card, DMA busy, spin hints); outside a flow it is
  dropped. The runtime sets the pure cost models to 0 (`dmac cycles_per_qword`,
  `hwbus_set_read_cycles`). `DelayThread` is a kernel-private timed wait (no semaphore, no
  alarm).
- **Step context.** `ps2k_step_enter(id)` / `ps2k_step_leave`: while a driven thread's
  step runs (in the pass or on a flow) the current thread is that thread (`GetThreadId`,
  its priority, its own semaphore calls). A step has no stack: a blocking call is fatal
  ("driven step of thread N blocked"), except that a `WaitSema` with no count first calls
  the **block hook** (`ps2k_set_block_hook`: the driver runs other woken steps that may
  signal it). `ps2k_set_parked_hook`: StartThread of a driven thread on the starter (the
  driver runs its first part at once when the HLE would have switched to it).
- Kept as game-visible records: thread objects and ids, semaphores (ids, counts, waiters:
  a flow or a parked driven thread), handler chains and ids, the INTC/DMAC STAT/MASK bits
  (a cause raised before `EnableIntc` is delivered after it, as the VIF1 protocol needs),
  timers computed from `K.now`. Unused on the native route: alarms (`SetAlarm`), service
  threads, `kcall_cycles`.
- A save state records the mode (`cfg.native`); a load into the other mode is refused.
- Counters: `ps2k_get_native_stats` (passes, flow switches, flows, charge waits / drops,
  delays). Test `frame_native` (+ `frame_native_control`: the same scenario on the HLE
  must fail its no-preemption and placement checks).

## Deviations from the real kernel (deliberate)

- **No asynchronous preemption.** A thread spinning on a flag that a handler
  sets, with no kernel call in the loop, never sees the handler. Virtual time
  also does not advance while a thread runs. The fix belongs at the spin site:
  an override calls `ps2k_poll()`, or `ps2k_charge(n)` for a timing loop
  (for example `T0_COUNT` polling). A future option is to charge cycles per
  `T0_COUNT` read in the register accessor. **This is the main hazard to
  watch in P2 bring-up.**
- **Guest stacks are unused.** `StartThread`'s retail wrapper clears a
  0x2A0-byte context at the top of the guest stack; this HLE does not touch
  guest memory.
- **No thread or kernel memory in guest RAM.** TCBs and the sema table live in
  host memory. Kernel-patch code (0x446xxx) and the OSD/TLB/ExecPS2 stubs are
  not modelled; the census says the game does not reach them.
- **Timer GATE modes and the HOLD/SBUS latch are not modelled.** With ZRET,
  the count is assumed to start at or below COMP until its first wrap. A
  compare event raises the INTC cause even if the flag was not acknowledged.
- **The scheduler delivers interrupts before every switch-in, even while the
  global EIE is 0.** Kernel/idle context has interrupts enabled here. Retail
  carries EIE = 0 into the next thread (VALIDATION.md 2e, modelled), but
  whether the retail idle loop re-enables interrupts was not measured.

## Open questions (verify against PCSX2 traces in P2)

Questions 1-5 were answered on PCSX2 running the real BIOS kernel
([VALIDATION.md](VALIDATION.md) section 2) and the model now follows the
measurement:

1. **Chain stop rule** (2a): the chain stops only on a negative return; 0
   and positive values continue. `next = 0` = head, `-1` = tail.
2. **`SignalSema` at max count** (2b): succeeds; the count exceeds
   `max_count` (no cap).
3. **Id allocation** (2c): see "Id numbering". Open: the thread-id wrap
   point and the free-list order beyond what was observed.
4. **Preempted thread position** (2d): head of its ready queue, confirmed.
   `ChangeThreadPriority` on the running thread to its own unchanged
   priority **yields** (it goes to the tail of its queue; an equal-priority
   ready thread runs before the call returns). An `i` call that changes the
   interrupted thread's priority requests the same rotation at handler
   return. Retail also preempts right after an interrupt handler returns;
   the port still delivers only at the defined points (deliberate limit).
5. **EIE across a blocking syscall** (2e): the blocked thread wakes with
   EIE = 0, and EIE is global, not per thread (medium confidence; see the
   EIE row above and `cfg.eie_per_thread`).
6. **VBlank phase.** The start line is 240, and fields alternate at exactly
   59.94 Hz, with no even/odd half-line distinction. Interlaced field parity
   (GS CSR.FIELD) belongs to the GS model.
7. **Alarm `time` argument.** The second callback argument is the hsync
   count at expiry, truncated to 16 bits. The real value is T3-based.
8. **The `ucontext` backend builds and links for i686 Linux but has not run
   yet** ([LINUX.md](LINUX.md)). glibc's i386 `swapcontext` saves the x87
   environment but not MXCSR, and makes a `sigprocmask` syscall per switch;
   a small asm switch is the fallback if either matters.

## Tests

`tests/kernel/kernel_tests.c`. Run one test with
`rg-kernel-tests <name>`, or all of them with no argument. CTest: `ctest -L kernel`.

| Test | Checks |
| --- | --- |
| `priority_order` | A higher-priority thread runs inside `StartThread`. Lower ones run by priority, FIFO among equals, only after main blocks. |
| `non_preemption` | A model raises VIF1 mid-loop and the handler readies a priority-10 thread, but the priority-50 loop finishes untouched. The switch happens at the next kernel call. |
| `wakeup_counting` | Banked wakeups (3 → 3 instant `SleepThread` returns), `WakeupThread(self)` fails, `iWakeupThread` from VBlank, `CancelWakeupThread` returns 2. |
| `semaphores` | Producer/consumer interleave, FIFO waiter order, `numWaitThreads`, `SignalSema` past max succeeds (count 2 of max 1, 3 of max 2) and polls drain it, `DeleteSema` releases a waiter with < 0, `iSignalSema` from VBlank. |
| `vblank_count` | 600 fields: exactly 600 starts, 599 ends, the exact cycle time. A time-limited run delivers exactly 60. |
| `delay_thread` | `DelayThread(1000)` = 147,456 cycles exactly. Three concurrent delays wake in order at exact offsets. Sema ids are freed. `DelayThread` under DI returns `0x80008008`. |
| `di_ei` | DI masks delivery across kernel calls; EI delivers. Return values. A DI thread that blocks wakes with EIE = 0, and the thread that runs meanwhile sees EIE = 0 (retail global EIE). Handler sees IE = 0. Latched cause is delivered on `EnableIntc`. |
| `di_ei_per_thread` | The same scenario with `cfg.eie_per_thread = 1`: the other thread sees EIE = 1. |
| `intc_chain` | `next = 0` head / `-1` tail order; returns 0, 1, 5 continue the chain, -1 stops it. |
| `ids` | Main = 1, threads 2, 3, 4, no reuse of deleted ids; semas from 0 with last-freed-first reuse, id 0 usable; the INTC/DMAC handler id sequence from VALIDATION.md 2c including the wrap 128 -> 2. |
| `determinism` | Same 2,428-record scenario twice gives the same trace hash. A 1 µs change gives a different hash. |
| `context_violations` | `iSignalSema` in a thread, and `WaitSema`/`SignalSema` in a handler, are flagged. `StartThread` in a handler returns -1 quietly. |
| `timers` | T0 HBLNK count after 100 ms, T2 ZRET compare period, T1 overflow, flag w1c, stop freezes the count, `INTC_MASK` readback. |
| `alarms` | `ReleaseAlarm` cancels. An alarm chain re-armed with `iSetAlarm` lands on exact hsyncs. |
| `thread_lifecycle` | Rotate round-robin, `ChangeThreadPriority` preempts and returns the old priority, `ChangeThreadPriority(self, same)` yields to an equal-priority thread, suspend/resume, terminate and delete a waiter, restart after exit, `ExitDeleteThread`, main exit with blocked threads. |
| `run_limits` | `DEADLOCK`, `STALL`, and 400 KiB of host recursion on a guest thread. |
| `service_thread`, `poll_wait`, `driven_thread`, `frame_driver` | Native-threads support over the HLE (docs/NATIVE-THREADS.md) |
| `frame_native` | Frame-driven mode: two flows, a tick step in the VBlank pass in step context, a lock waited for as a real waiter, no preemption, nominal T0, exact timed waits (`frame_native_control`: on the HLE, must fail) |
| `*_control` (`WILL_FAIL`) | `non_preemption_control` injects a preemption (`ps2k_debug_force_preempt`). `di_ei_control` delivers under DI. `determinism_control` perturbs the replay. `intc_chain_control` expects the old stop-on-non-zero rule. Each must fail its check, and does. |

Build: `tools\build.ps1` (or `-BuildDir build\kernel-i686`), then
`ctest --test-dir build\kernel-i686 -L kernel`. Status on 2026-10-12 (after the VALIDATION.md section 2
changes): 20/20 pass (16 tests and 4 controls), and the determinism hash is
identical across separate processes.
