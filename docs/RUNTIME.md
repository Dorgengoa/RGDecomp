# Platform runtime (`src/runtime`)

PLAN.md P2–P4: the glue that boots every model under the host shell, in a fixed order,
and drives the kernel's virtual clock one field at a time. The game isn't linkable yet,
so the EE side starts in a crt0 equivalent that calls a weak, replaceable game entry.
`rg-runtime-demo` runs the whole stack without game code.

All of it is original CC0 code. No GPL code, no emulator code.

| Path | What |
| --- | --- |
| `src/runtime/rg_runtime.h` | The API: config, init/run/shutdown, stats, crt0 layout and bindings |
| `src/runtime/runtime.c` | Init order, VBlank observer, CDVD device + wait hook, pad source + rumble, IOP post-install, the per-field host half |
| `src/runtime/crt0.c` | `rg_ps2_main` (crt0 equivalent), the game RAM block, `sbrk` / `EndOfHeap` / `RunStaticCtors_100df0` bindings, weak `rg_game_entry` |
| `src/runtime/demo/demo_guest.[ch]` | Guest-side smoke workload: EE threads using libpad, libcdvd, libsdr/SK and libdma/libgraph. Also writes a synthetic disc folder |
| `src/runtime/demo/runtime_demo.c` | `rg-runtime-demo` |
| `tests/runtime/` | `rg-runtime-tests`, `determinism.cmake`; CTest label `runtime` |

CMake targets: `rg_runtime`, `rg_runtime_demo_guest`, `rg-runtime-demo`, `rg-runtime-tests`.
They need the host shell, so they're built only with `RG_HOST=ON` (the default).

## API

```c
rg_runtime_config cfg;
rg_runtime_default_config(&cfg);     /* data/saves from RG_DATA/RG_SAVES, windowed, paced */
cfg.headless = 1;                    /* optional: no window/audio/live input, unthrottled */
rg_runtime_init(&cfg);               /* the fixed order below */
while (rg_runtime_run_field() == 0)  /* one field: EE until VBLANK_START, then host half */
    ;
rg_runtime_shutdown();
```

- `rg_runtime_run_field()` returns 0 to keep going, `RG_RUN_QUIT` when the window closed
  or Esc was pressed, or the kernel's `PS2K_RUN_*` stop code + 1 (main exited, stall,
  deadlock, time limit). `rg_runtime_run(n)` loops it.
- One runtime per process: the kernel, the SIF/IOP and the pad/card/sound models are
  singletons. Init → shutdown → init works (the `init_order` test does it twice).
- Everything runs on the host thread that called init. That thread becomes the kernel's
  scheduler fiber while the EE runs.
- **Settings (optional).** `rg_runtime_config_from_settings(&cfg, s)` copies
  `system.throttle`, `audio.enabled`, `display.window_mode` and `display.scale` into the
  config and sets `cfg.settings`. Init step 1 then builds the host config from the registry,
  turns any cfg field set afterwards into a command-line override
  (`rg_host_settings_from_config`), and attaches the registry to the host, which applies it
  live and owns the settings overlay. `cfg.settings_path` is the overlay's "Save" target.
  `rg-runtime-demo` takes `--settings/--set/--preset` (SETTINGS.md). Headless runs are
  unaffected: no live source is read.
- `rg_runtime_set_service_hook(fn, user)` runs `fn` after init. It's where the overlay
  manager and the movie service attach (see "Hooks for other services").

## Init order

`rg_runtime_init_order()` reports the steps that ran. The `init_order` test checks the
order and what each step left behind.

| # | Step | What | Why here |
| --- | --- | --- | --- |
| 1 | host | `rg_host_create` (window, audio stream, gamepads), the input script, `rg_pacer_init` | The pad source and the pacer need it; a failure here costs nothing else |
| 2 | kernel | `ps2k_init` (start line, stop/stall limits, stack size) | `ps2k_init` resets all kernel state: everything that registers with the kernel comes after it |
| 3 | graphics | `gs_create`, VU0/VU1 (`vu0.vu1 = &vu1`; `rg_vu0_micro_bind(&vu0)` so game `vcallms` runs on it, PORT-HEADERS.md), VIF0/VIF1, `dmac_create`; `vu1.gif_sink` → PATH1, `vif1.gif_sink` → PATH2, `dmac_attach_vif` ×2, `dmac_attach_gs` (PATH3, VIF1 readback, GS irq → INTC GS); `sce_graphics_bind` | DMAC.md "Wiring" |
| 4 | hwbus | `hwbus_init`, `hwbus_bind(dmac, gs)` | Needs the bound models. The DMAC is asked before the kernel for D_STAT (HWBUS.md) |
| 5 | cdvd | `sceCdHleMount(data)` if `MANIFEST.tsv` exists, `cdvd_drive_set_clock(0)`, the drive wait hook, a kernel device | Needs the kernel (device list) |
| 6 | cards | `mccard_init(saves, virtual clock)`, `padman_reset`, `rg_pad_set_input_source`, `rg_pad_set_rumble_hook` | Before the IOP boot so mcserv/padman install over ready models |
| 7 | iop | `iop_hle_set_post_install`, then `rg_sif_boot` (SIF + IOP reset, FILEIO/iopheap/LOADFILE, kernel hooks). The post-install runs inside it: `padman_install`, `mcserv_install`, `snd_install` | SIF.md: after `ps2k_init`. SOUND.md: `snd_install` after `iop_hle_install` |
| 8 | observers | `ps2k_add_vblank_observer(on_vblank)`, `ps2k_set_pacing_hook(rg_pacer_hook)` | Last kernel registration; nothing runs before the first field |
| 9 | game-ram | `rg_crt0_init`: the game heap (one allocation, NATIVE-CPU.md section 8) | Allocated before step 1 (this step only records it). With `RG_HEAP_DMA_PLACEMENT` (the emulated DMA path's 28-bit masks) it must end below 0x10000000, and a windowed host's D3D11 renderer and display driver fragment the low address space (a windowed GPU run got 0x1CFCB000 and faulted). Windows: `VirtualAlloc` at the lowest free range from 0x04000000 (GPU.md "Real game validation") |

Shutdown runs in reverse: `ps2k_finish` (destroys the guest fibers), drops the IOP
post-install and the pad/CDVD hooks, `mccard_shutdown` (flushes card metadata),
`sceCdHleUnmount`, `ps2k_shutdown`, unbinds hwbus and libgraph, frees the models, the RAM
block and the host. The stats stay readable after shutdown.

## One field

`rg_runtime_run_field()`:

1. The first call starts the EE: `ps2k_start(rg_ps2_main, …, main_priority)`.
2. `ps2k_step(ps2k_vblank_count() + 1)` runs the scheduler until the next VBLANK_START
   has been processed and its interrupts delivered. The kernel yields at its first
   scheduler-context point after that, with every guest thread intact.
3. The **host half**:
   - `rg_host_pump` (window events, hotkeys, gamepad hot-plug; quit → `RG_RUN_QUIT`);
   - audio: drain `snd_output_read` into `rg_host_audio_push`;
   - display: `gs_read_display(GS_READ_FRAME)` → `rg_host_present` (windowed), and into
     the run hash every `display_hash_every` fields;
   - fold the kernel trace hash and the clock into `run_hash`.

Real-time pacing happens inside the kernel: `rg_pacer_hook` throttles every idle jump of
the virtual clock, so fields come out at 59.94 Hz (HOST.md "Pacing"). Headless runs are
unthrottled and are a pure function of their inputs.

### VBlank observers

The kernel calls its observers when it **processes** a VBLANK_START or VBLANK_END event,
at the event's exact virtual time, after the INTC cause is latched and before any game
handler runs. The runtime's observer does the model-side half of the field there:

| Edge | Work |
| --- | --- |
| VBLANK_START | `gs_vsync` (CSR.FIELD toggle, VSINT → INTC GS), `padman_update(vblank)` (padman's per-frame DMA buffer write), `snd_sync` (renders audio up to this cycle) |
| VBLANK_END | counted |

Observers can run on a guest thread's fiber (a kernel call that crossed the event), so
they must not make thread-context or blocking kernel calls. Host work that can block or
use a lot of stack (presenting, SDL events) is in the host half instead.

### Audio per field

`snd_sync` at each VBLANK_START renders up to that cycle, 3072 bus cycles per 48 kHz
frame. One field is 2,460,060 cycles (KERNEL.md), so fields alternate between 800 and
801 frames and average 800.80 (`audio_field` test: 599 fields, sum exact to the frame,
average 800.7997).

`RG_AUDIO_WAV=<path>` (any build, headless too) also writes every frame the host half
receives to a 48 kHz s16 stereo WAV and `<path>.fields.tsv` (field, kernel VBlank, game
VBlank, frames so far, cycle); the header is rewritten every 60 fields and at shutdown.
Sample n is virtual cycle 3072 n. Used for the PCSX2 audio validation (SOUND.md
"Validation"); test `audio_wav`.

`RG_AUDIO_LOG=<path>` writes one TSV row per field of host-side measurements: wall and
work time, pacer sleep, present time, CD read wall time, frames pushed, the host queue
before and after the push, device starves, the output regulator's pads, drops and rate,
pacer re-anchors and the GPU renderer's per-field batches, destination copies and
write-backs (SOUND.md "Load-screen audio"). Wall clock only. A pacer re-anchor is passed
to the host (`rg_host_audio_resync`) so the output queue can rebuild its cushion.

### Pad

padman's input source is `pad_source` in `runtime.c`:

- It calls `rg_host_read_pad(host, port, vbl, …)`. `vbl` is `cfg.game_vblank(kernel
  VBlank)`, or the kernel VBlank count when that's NULL. Input scripts are keyed by
  `vbl`.
- **Port 0** is always connected. **Port 1** is connected when `rg_host_port_connected(host,
  1)` says so: a windowed run with no script, `input.players = two` and at least two
  gamepads (INPUT.md "Devices"). With the default `one`, every gamepad drives port 0.
- Pressure comes from the host pad, whose byte order is the same as the DS2's.
- Rumble: padman's hook → `rg_host_rumble(host, port, small, large)` →
  `SDL_RumbleGamepad` (large motor = low-frequency 0..255, small = high-frequency
  on/off). It's re-sent every 1,800 pumps while a motor runs, because SDL caps a
  rumble's duration.
- **TODO (game link).** The scripts of `tools/trace/input.py` are keyed by the game's own
  counter `[0x004810C4]`, which the game's VBlank handler increments. Once the game
  links, set `cfg.game_vblank` to a function that returns that counter (`D_004810C4`).
  Until then the kernel count is used, which is off by the VBlanks before the game
  installs its handler. Traced runs already do this: `rg_trace_apply_env` installs
  `rg_trace_game_vblank` (counter + 1, docs/TRACE-PORT.md "Sample point").

### CDVD on the kernel loop

The drive (CDVD.md) keeps virtual microseconds; the kernel keeps bus cycles. The runtime
registers the drive as a **kernel device**:

- `next`: `cdvd_next_event` (µs) → `ceil(us × 147.456)` cycles. The idle jump stops
  there, and a pending command keeps an idle kernel from reporting DEADLOCK.
- `poll`: `cdvd_poll(floor(now / 147.456))`. It runs on every event pass, which also
  keeps the drive's clock in step with the kernel. Completion callbacks run in handler
  context.
- **Wait hook** (`sceCdSync(0)` → `cdvd_drive_wait`): `ps2k_wait_until(due)`, a
  kernel-private wait. No sema id is used, other threads run, and the device poll at the
  due cycle completes the command before the waiter runs again. The `cdvd_async` test
  checks the waiter wakes at exactly the due cycle (issue + 202,015 cycles = 1,370 µs for
  one sector) and that `sceCdSync(1)` reports busy with no data in the buffer before
  then.
- The drive's clock is reset to 0 at init (`cdvd_drive_set_clock`, new), because the
  kernel clock restarts there.

## Kernel additions (src/ps2/kernel, docs/KERNEL.md)

| API | What |
| --- | --- |
| `ps2k_start` / `ps2k_step(until_vblank)` / `ps2k_finish` | `ps2k_run` in pieces. `ps2k_step` returns `PS2K_RUN_YIELD` at the first scheduler point where the VBlank count reached the target. `ps2k_run` is now start + step(0) + finish, unchanged in behaviour. |
| `ps2k_add_vblank_observer` / `remove` | The observer list (up to 16). |
| `ps2k_add_device` / `remove` | Models with their own completion clock (up to 8): `next(user, &due)`, `poll(user, now)`. |
| `ps2k_wait_vblank()` | Kernel-private wait for the next VBLANK_START. It takes no sema or alarm id. The thread is readied after that VBLANK_START's handlers and the alarms due with it have been delivered, the order the old `sceGsSyncV` alarm had. `sceGsSyncV` now uses it (DMAC.md deviation 1 resolved). |
| `ps2k_wait_until(time)` | Kernel-private timed wait. |
| `ps2k_vblank_start_line()`, `ps2k_vblank_enabled()`, `ps2k_vblank_start_time(k)`, `ps2k_vblank_end_time(k)` | The configured line and exact edge times. |

While a thread is in a kernel-private wait, `ReferThreadStatus` reports status WAIT with
wait type 0. Retail `sceGsSyncV` busy-waits, so the thread would read RUN there.

## crt0

What the retail entry (`game/src/main/sdk/entry.c`, `entry` at 0x00100008) does, and the
host equivalent in `crt0.c`:

| Retail | Host |
| --- | --- |
| Zero GPRs, FPRs, HI/LO, SA; FCR31 = 0 | Nothing (host ABI) |
| Clear BSS `[0x00481080, 0x00528200)` (byte, quad, byte loops) | MAIN `.bss` is host statics, zero at load. The overlay-arena part (from 0x004E9E80) belongs to the overlay manager. **TODO(overlay)** |
| `SetupThread` (syscall 0x3C): gp 0x00485170, stack 0x01FD0000 + 0x30000, args 0x00485280, root = `CrtRootExitThread_100220` | Guest thread 1 is created by `ps2k_start` at `cfg.main_priority` (default 1; `Main_15e700` sets its own from `D_0047DF30` first thing). Guest stacks are unused (KERNEL.md). argc/argv = 1, `{"cdrom0:\SCUS_974.90;1"}`, as ExecPS2 passes them from SYSTEM.CNF BOOT2 |
| `SetupHeap` (syscall 0x3D): heap from 0x00528200, size -1 → up to the stack bottom | `rg_crt0_init`: the heap alone, one host allocation (`RG_CRT0_HEAP_ALLOC`), heap start = page + 0x200 (== 0x00528200 mod 4 KB: newlib malloc rounds the break to pages), 0x1AA7E00 bytes. No EE-RAM image: the retail view is the explicit mapping `rg_crt0_host_to_retail` / `rg_crt0_retail_to_host` (NATIVE-CPU.md section 8). Placement below 0x10000000 only with `RG_HEAP_DMA_PLACEMENT` |
| `InitSys_120918` (alarms, timers, threads, ExecPS2, TLB, IOP reset callbacks) | The kernel HLE is already up |
| `FlushCache(0)`; `ei` | No-op; thread 1 starts with EIE = 1 |
| `Main_15e700(argc, argv)` | `cfg.entry`, else `rg_game_entry` |
| `Exit_12f4e0(ret)`: newlib `_atexit` chain (LIFO), `__cleanup`, Exit syscall | `rg_ps2_exit`: the `rg_crt0_atexit` list (LIFO), then `ExitThread` → `PS2K_RUN_MAIN_EXIT` |

Static constructors run inside the game: `Main_15e700` calls `MainStaticInit_100580` →
`RunStaticCtors_100df0(0x0046F9C0, 0x0046FD64, …)`. That's an excluded asm unit, so
`crt0.c` provides its binding: it calls each 32-bit entry of the table in order. Its tail
call, `EhRegisterFragmentStubMaybe_1026b0`, returns 0 and does nothing.

**Bindings for the excluded asm units** (PLAN transform 6), with the game's own names:

- `EndOfHeap()` returns the heap end.
- `sbrk(incr)` is newlib's sbrk over the heap: it returns the old break, or `(void *)-1`
  with errno ENOMEM. On Linux the definition in the executable interposes libc's `sbrk`
  for every caller outside libc (glibc's malloc uses its internal `__sbrk`), so no rename
  is needed ([LINUX.md](LINUX.md)).
- `RunStaticCtors_100df0` (above).

**The game entry is a weak symbol.** `rg_game_entry` in `crt0.c` is
`__attribute__((weak))`. The game build defines a strong `rg_game_entry(argc, argv)` that
calls `Main_15e700`, and the linker takes that one. The default prints once and returns
`RG_GAME_NOT_LINKED`; the `crt0` test checks this.

**Open issues for the game link:**

- `SysCalcFreeHeapMaybe_15e1d0` computes the free heap from the **addresses** of
  linker-defined symbols `D_00030000` (the stack size) and `D_00528200` (`end`). On the
  host these must be absolute symbols with those values, or the function needs an
  override that uses `rg_crt0_ram()`. The heap block is sized so that the game's probe
  (0x2000000 − 0x2000 − 0x30000 − 0x528200 − 0x10 bytes) fits; the `crt0` test checks it.
- `sbrk`'s break variable `D_004461F4` is no longer used (the binding keeps its own).
- The newlib atexit chain and `__cleanup` aren't bound yet (see `rg_ps2_exit`).

## Hooks for other services

| Service | Hook | Status |
| --- | --- | --- |
| Overlay manager (`src/ps2/overlay`) | `hwbus_set_ovl_resolver` (RG_OVL_DATA), the MAIN → 0x4E9E80 call table, the overlay-arena BSS | TODO: attach from `rg_runtime_set_service_hook` |
| Movie service (`src/movie`) | `rg_movie_runtime_attach`: the data root only (the IPU hooks and DMAC ch3/4 bindings are gone with the game's IPU layer, NATIVE-CPU.md section 8) | Wired (rg_game_main.c) |
| GPU renderer (`src/gpu`) | `rg_runtime_gs()->hooks` | Wired (below, "GS renderer"): `cfg.gpu` / `RG_GPU` |

## GS renderer

`cfg.gpu` (default -1: `RG_GPU`) picks what draws the GS model's primitives: 0 the
software rasterizer (the reference, default), 1 the Direct3D 11 GPU renderer on the
hardware adapter (`RG_GPU=hw`), 2 on WARP (`RG_GPU=warp`). `cfg.gpu_scale` (default 0:
`RG_GPU_SCALE`, else 1) is the internal resolution, 1 to 8. The GS model itself (GIF,
registers, transfers, CLUT, local memory) runs the same either way; with the GPU the
present, the run hash's display read-out and `rg_runtime_screenshot` use
`gpu_read_display` (native size x scale; the host scales any source size), and the frame
buffer grows to `scale^2` x 1 M pixels. `rg_runtime_gpu()` returns the renderer (NULL on
the software path); anyone reading `gs->vram` directly must `gpu_sync` it first. Builds
without `src/gpu` (Linux, no `fxc`) fall back to the software GS with a message, as does a
failed device creation. docs/GPU.md "Real game validation" has the results on the game.

**The renderer is created last in init** (after the RAM block and the service hooks).
Game pointers are host addresses, and DMA tags, `PS2_PHYS`-style masks and a few
unconverted `& 0x0FFFFFFF` sites keep 28 bits. Created in step 3, the D3D11 runtime and
the NVIDIA driver took enough low address space that the 32 MB RAM block landed at
0x143A2000, and the game's first VIF1 chain (GfxEndFrame → Vif1DmaStart → sceDmaSend)
faulted in the DMAC model reading the masked address 0x043A...; created last, the block
stays at 0x0629xxxx. Init now warns if the RAM block ends above 0x10000000
(`runtime.gpu_smoke` checks it).

Validation knobs (read at init; all off by default):

| Variable | What |
| --- | --- |
| `RG_GS_DUMP_DIR` + `RG_GS_DUMP_FIELDS=a,b,..` | at the end of each listed field: `fNNNNN_display.png` (what is presented), `fNNNNN_local.png` (`gs_read_display` of local memory; GPU: after `gpu_sync`), `fNNNNN.vram` (4 MB), `fNNNNN.regs` (preg, reg, CLUT). `tools/gpu_validate.py REF GPU` compares a software and a GPU run |
| `RG_GS_REC=file` + `RG_GS_REC_FIELDS=a-b` | a GS input recording of fields a..b (`gs_rec_*`, GS.md "Recordings"): snapshot at the start of field a, then every GIF write, privileged write, VSync, GIF reset and FIFO read. `rg-gpu-tests replay FILE` replays it through both renderers; `tools/gsrec_dump.py` lists it. Game data: keep under `out/` |
| `RG_FIELD_TIMES=file` | wall time of every field (EE + host half), TSV: `wall step read present gs_wait` (PERF-3D.md) + since 2026-10-18 `pace` (paced-mode sleep), `sync` (GS worker drain / wait before presenting), `pump` (rg_host_pump), `audio`, `post` (rest of the host half), `out` (between fields, in the caller); attribution: BRINGUP.md "User play-test, 2026-10-18", `out/play/frames.py`, `unacc.py` |
| `RG_FIELD_STATS=file` | per-field counter deltas for attributing slow fields (host CPU per thread by cycle counts, page faults, private bytes, file reads, sound banks, GS worker traffic, GPU target / upload / read-back / flush work, native-renderer first-use work, presents and new images); `tools/perf3d/stutter.py`, docs/PERF-3D.md "Transition stutter" |
| `RG_WINDOW_SHOT=field:path` | windowed runs: a PNG of the window as presented (after the host's scaling) at the end of that field (GPU.md "Real game validation") |

## Changes made to other modules

- **kernel:** the additions above. `kcore.c` (start/step/finish, kernel-private waits),
  `kirq.c` (observers, devices, the idle-jump target, the edge-time accessors).
- **libgraph:** `sceGsSyncV` uses `ps2k_wait_vblank`. `sceGsResetPath` and the
  `sceGsExecStoreImage` error path call `gs_gif_reset` (GIF_CTRL.RST).
- **GS:** `gs_gif_reset(gs)` drops every path's tag and packet state and its queued data,
  and frees the bus. Registers, VRAM and the CLUT are untouched.
- **hwbus:** `GIF_CTRL.RST` calls `gs_gif_reset`.
- **IOP:** `iop_hle_set_post_install(fn, user)`, called at the end of every
  `iop_hle_install`. The runtime installs padman, mcserv and the sound HLE there, so the
  real servers answer from boot, and after any later `rg_sif_boot`.
- **CDVD:** `cdvd_drive_set_clock(us)`.
- **host:** `rg_host_rumble`, `rg_host_rumble_state`.

## `rg-runtime-demo`

```
rg-runtime-demo [--headless] [--fields N] [--data DIR] [--saves DIR] [--input script.txt]
                [--screenshot out.png] [--unthrottled] [--hash-every N]
                [--parts pad,cd,snd,gfx] [--fixture DIR]
```

It boots the whole stack and runs guest threads that use only the SDK surface:

| Thread (priority) | What |
| --- | --- |
| main (60) | Starts the others, then loops `sceGsSyncV`; returns after N fields |
| gfx (20) | `sceGsResetGraph(0,1,2,1)`, `sceGsResetPath`, `sceGsSetDefDBuff` 640x448 CT32. Each field it sends one VIF1 DMA chain (END tag): MPG of a 2-instruction VU1 program (`XGKICK vi00`), an UNPACK V4-32 of a 2-sprite PACKED GIF packet, MSCAL. It then calls `sceGsSwapDBuff` and `sceGsSyncV`. The sprite turns green while CROSS is held |
| pad (30) | `scePadInit`, `scePadPortOpen`, a read every field; analog mode, `SetActAlign`, then `SetActDirect` follows CROSS (rumble) |
| snd (35) | `sceSdRemoteInit`, the game's SPU init sequence, a synthetic HD/BD bank uploaded with `sceSifAllocIopHeap` + `sceSifSetDma` + SK G0/0xA. It registers the bank (G1), makes an MSIN track (G3) and sends an SE key-on at field 10 (G3/0x11) and a key-off at field 70 |
| cd (40) | `sceCdInit`, `sceCdSearchFile("\SYSTEM.CNF;1")`, async `sceCdRead`, `sceCdSync(1)`, then `sceCdSync(0)` |

Without `--data` or `RG_DATA` it writes a synthetic single-layer disc (`MANIFEST.tsv` v2,
`SYSTEM.CNF`, `DEMO.BIN`). It prints one line per part and `run_hash=`, then exits 0 if
every enabled part passed: pad stable and read, the CD text read, the key-on accepted and
audible (peak > 1000), and frames drawn plus a display read-out.

With `RG_TRACE_OUT` set it also records a state trace (`RG_TRACE_*`, docs/TRACE-PORT.md):
`src/trace` links its recorder into the demo and defines `RG_WITH_TRACE`, which enables a
guarded call in `runtime_demo.c`. Without the variable the hook does nothing.

Example (windowed, 120 fields, 2026-10-12): all parts PASS. The screenshot shows the box
and the moving sprite at 640x448.

## Tests (`ctest -L runtime`)

`rg-runtime-tests <name> <tmpdir>`. Every test runs headless and unthrottled on a
synthetic disc.

| Test | Checks |
| --- | --- |
| `init_order` | The 9 steps in order, twice (init → shutdown → init). After init: SIF booted; padman, mcserv and the real sound servers (`sdr_driver`, `pcm_mixer`, not the placeholders) registered at boot; `sif_now() == ps2k_now()`; RAM, models, start line 240. 5 fields run, and the SIF clock still follows the kernel. |
| `vblank_rate` | Fields until 10 virtual seconds. Every `run_field` advances exactly one VBLANK_START. In the first second, exactly 60 starts and 59 ends (the formula, F = BUSCLK/59.94). Every observer call happens at its edge's exact cycle. Measured rate 59.9400 Hz. |
| `audio_field` | 600 fields with nothing playing. The first field holds `floor(t_VBS0 / 3072)` frames. The next 599 sum exactly to `floor(t_VBS599/3072) − floor(t_VBS0/3072)`, average 800.80, each 800 or 801. Nothing dropped, and every frame reached the host. |
| `pad_script` | Script `40 80 CROSS`, `100 START` through the host → padman → libpad. Every one of 122 reads equals the script word for its VBlank; CROSS is seen on VBlanks 40..80 and START once. Actuators aligned; CROSS switched the rumble on and off (≥ 2 changes, motors off at the end). |
| `cdvd_async` | The CD thread alone: search, async read, `sceCdSync(1)` busy with the buffer untouched, `sceCdSync(0)` wakes at exactly the due cycle (202,015 cycles after issue), one device completion, `SYSTEM.CNF`'s first line, no sema id left behind. |
| `cdvd_realdata` | The same against `RG_DATA` (skipped, exit 77, without it). |
| `audio_wav` | `RG_AUDIO_WAV` with the demo's SE for 90 fields: RIFF/fmt/data header (PCM, 2 ch, 16 bit, 48000 Hz), data size = frames the host got, peak in the file = the runtime's peak (> 1000), one sidecar row per field whose frame count equals floor(VBLANK_START time / 3072). |
| `smoke_all` | Every part for 90 fields: SE key-on accepted, `key_ons ≥ 1`, audible (peak > 1000); CD read; > 50 pad reads; ≥ 85 frames, ≥ 85 XGKICK packets on PATH1, ≥ 170 sprites; display 640x448. |
| `crt0` | RAM alignment, heap size 0x1AA7E00 (the game's free-heap probe fits), `EndOfHeap`, `sbrk` grow/shrink/refuse, `RunStaticCtors_100df0` order, the weak `rg_game_entry` → `RG_GAME_NOT_LINKED` and MAIN_EXIT in field 0. |
| `gpu_smoke` | The demo for 90 fields on the software GS, then through the GPU renderer (`cfg.gpu`; WARP, `RG_GPU_HW=1` the adapter): the same 640x448 frame within ±2 (measured: identical), the renderer attached to `rg_runtime_gs()`, and the game RAM block ending below 0x10000000 in both runs (with the renderer created in step 3 it lands at 0x10CD6000 on an RTX 3080: the check fails). Skipped (77) without `src/gpu`. |
| `kernel_glue` | 4 × `sceGsSyncV` each wake once, at the exact VBLANK_START cycle, after the game's VBLANK_START handler ran. A lower-priority thread creates and deletes a sema 8 times during the waits and always gets id 0 (sema ids start at 0, last freed first; KERNEL.md, VALIDATION.md 2c): no hidden sema. `ps2k_wait_until` wakes at the exact cycle. |
| `determinism` | `determinism.cmake`: two **separate processes** run `rg-runtime-demo --headless --fields 600` (10 virtual seconds, every part, a pad script, the display folded in every 60 fields). The `run_hash` and the final screenshot must be identical. |
| `vblank_rate_control` (`WILL_FAIL`) | Expects 60 VBLANK_ENDs in the first second (a 60.00 Hz field). Fails on that check. |
| `pad_script_control` (`WILL_FAIL`) | Expects the script one VBlank late. Fails: 4 reads differ. |
| `determinism_control` (`WILL_FAIL`) | The second process's script releases CROSS one VBlank earlier. The hashes differ (a97654e2… vs f2ad1dc6…), so the equality check fails. |

`run_hash` folds in, per field, the kernel trace hash (thread switches, sema and wakeup
events, interrupts, times), the virtual time and every audio sample. It also folds in
every pad-source answer (port, VBlank, word) and, at the chosen interval, the display
read-out.

Status 2026-10-12: 14/14 runtime tests pass (11 tests, 3 controls; `build/audio-i686`) and `cdvd_realdata`
is skipped without `RG_DATA`. With `RG_DATA=data` it passes: LSN 8577 on the dual-layer
disc. A fresh full build (`build/runtime-full-i686`, `-Clean`) passes 286/286 CTest
tests across all labels; the two RG_DATA tests are skipped there.

## Open questions

1. **Observer vs handler order at the same edge.** Observers run when the event is
   processed, so before the game's handlers. On hardware, the GS field flip and VSINT
   come with the VBlank edge too. A PCSX2 trace decides whether the game's VBLANK_START
   handler should see CSR.FIELD already toggled.
2. **Field cut.** A field ends at the first scheduler point after VBLANK_START. A guest
   thread that was running when the edge passed (inside a kernel call) keeps running
   until it blocks. Presentation then shows what it drew up to that point. That's
   deterministic, but not cycle-exact against hardware scan-out.
3. **Main thread priority** before `Main_15e700` changes it: 1 here. The retail
   `SetupThread` value is unverified.
4. **Audio clock drift** against the device: handled by the host output regulator
   (HOST.md "Audio", 2026-10-12). The runtime still pushes exactly what the virtual
   clock produced; a field slower than real time (the NORMAL loading screen in the GPU
   renderer, SOUND.md "Load-screen audio") still leaves the device short.
5. **Port 1 connection** in windowed runs follows `input.players` and the gamepad count. A hot-plug is seen by
   padman as an unplug or replug, which the game handles (PADMC.md).
