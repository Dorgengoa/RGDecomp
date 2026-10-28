# Native-only build (`RG_NATIVE_ONLY`): the D9 link gate, first step

PLAN.md D9 / "Native end state", gate: *"the shipping executable links none of `src/ps2/*`
models"*. The IOP, sound and file lanes (NATIVE-IOP.md, NATIVE-AUDIO.md, NATIVE-FS.md) made
their native paths the default, but the oracles stayed **linked**: the choice was a run-time
switch (`RG_IOP`, `RG_AUDIO`, `RG_FS_ORACLE`, `RG_CDVD_MODEL`) inside libpad / libmc /
`src/sce/sif` / the runtime. This lane adds the build-time switch and the measurement.

Status (2026-10-25, D9 address gate): **no PS2 address arithmetic left** in the compiled
game set: `tools/native/addr_census.py --check` PASS, 0 `arith` / 0 `marker` sites (was 36 /
44), gate test `native_only.addr_census` (+ `_control`, which injects one site per kind and must
FAIL). The game's T0 / GS privileged / VIF1_FBRST sites call the native services by name
(`rg_logic_t0_*`, `rg_gs_reg_r64 / w64(RG_GS_<REG>)`, `rg_vif1_fbrst_w32`; HWBUS.md "Native
register sites"), the identity markers are stripped, SysCalcFreeHeapMaybe uses the runtime
heap's size (`rg_crt0_heap_size`), the kernel-RAM ReleaseAlarm body is port-provided. Left and
classified (not addresses): `dead-data` 19 words in the SDK DMA-channel / TLB tables no
compiled code reaches, `dmatag` 4 END ids, `flag` 12 reviewed bit / tag-id literals, `raw-word`
95 datareloc data words. The D9 gate (PLAN.md "Native end state") is the pair
`native_only.link_audit` + `native_only.addr_census`.

Status (2026-10-25): **no emulation library left** in the native-only rg-game:
`link_audit.py check --forbid all --extra rg_ps2_hwbus` PASSES with 0 pending (the last four,
`rg_sce_vu0` and the overlay arena manager / binding / arena, went on 2026-10-25: section 4,
NATIVE-CPU.md section 9, OVERLAY.md section 8). The gate test forbids every set.

Status (2026-10-18): **done for the IOP / sound / CDVD set.** `build/nonly-i686/rg-game.exe`
(`RG_NATIVE_ONLY=ON`) links none of the 9 forbidden libraries (`link_audit.py check`: PASS;
the same-tree default twin `rg-game-oracle`: FAIL, as it must). Golden route power-on to
field 31,700: **run hash identical** to the twin (`f3b853eebb958224`), **37 / 37 milestones
identical** (`timing.py align --nowrap`: 0 segments differ); fixtures (7 milestones, +300
check) regenerated and verified with the native-only exe; ctest in that config: section 3.
Linked emulation: 24 libraries / 437 KB code / 5.96 MB data+bss -> 15 / 374 KB / 1.76 MB;
exe 9,781,760 -> 9,686,528 bytes (-93 KB).

| Part | Where |
| --- | --- |
| Option | `RG_NATIVE_ONLY` (top `CMakeLists.txt`, **default ON since 2026-10-18**, NATIVE-CPU.md section 8; existing build dirs keep their cached value) |
| Clone mechanism | `cmake/native_only.cmake` (included by `cmake/game_link.cmake` when ON) |
| Guards | `#if RG_IOP_ORACLE` (`src/native/iop/rg_iop.h`) in `src/sce/sif/{sif_ee,fileio,libsdr}.c`, `src/sce/padmc/{libpad,libmc}.c`, `src/runtime/runtime.c`; `RG_NATIVE_ONLY` in `src/native/audio/ra_host.c`, `src/native/iop/rg_iop.c` |
| Native libcdvd | `src/sce/cdvd/libcdvd_native.c` (`rg_sce_cdvd_native`) |
| Link audit | `tools/native/link_audit.py` (`report`, `check`, `diff`, `refs`; reads the Linux ld.lld `-Map` too, docs/LINUX.md "Audit") |
| Address census | `tools/native/addr_census.py [--build DIR] [--tsv OUT] [--sites] [--check] [--inject]`: PS2 address arithmetic left in the compiled set (D9 gate's second half; reuses hw_census.py + overlay / arena / retail-address / KSEG-mirror kinds; classes `arith` / `marker` fail `--check`; `dead-data` by reachability, `dmatag` / `flag` from its REVIEWED table + the hwaccess stage's LEAVE_RULES, `raw-word` from DATARELOC.tsv are `inert`) |
| Gate test | `tests/native_only/` (ctest label `native_only`): `link_audit` (+ control), `addr_census` (+ control) |
| Build | `tools/native/nonly_build.ps1` (build dir `build/nonly-i686`); targets `rg-game` (native-only) and `rg-game-oracle` (same-tree default twin) |
| Route / startup / memory | `tools/native/nonly_route.py` (`run`, `startup`, `compare`) |

## 1. What the option does

`-DRG_NATIVE_ONLY=ON` changes **only what rg-game links**. Every library keeps its normal
definition (tests, demos and tools keep linking the oracles through them, unchanged); for
rg-game, `cmake/native_only.cmake` walks the link closure and gives every library that
reaches an oracle, or whose sources have oracle branches, a native-only clone: the same
sources and properties, compiled with `RG_NATIVE_ONLY=1`, linking the clones of its
dependencies and none of the dropped libraries. A clone keeps the original's output name
(in `<build>/nonly/`), so the map still says `rg_runtime:runtime.c.obj` (the save-state
policy rows in `src/savestate/ss_map.c` and the audit match on those names). A dropped
library still gives its include directories (headers only: types and constants the guarded
code names, e.g. `SND_CYCLES_PER_FRAME`).

Dropped (`RG_NONLY_DROP`): `rg_ps2_sif`, `rg_ps2_iop`, `rg_ps2_iop_hle` (FILEIO / LOADFILE
/ iopheap servers), `rg_ps2_padmc` (padman, mcserv), `rg_ps2_sound` (+ `rg_snd_tools`),
`rg_ps2_spu`, `rg_ps2_cdvd`, `rg_native_fs_oracle`. Replaced: `rg_sce_cdvd` (libcdvd over the
sector model) by `rg_sce_cdvd_native`. Cloned (configure prints the list): the guarded
`rg_runtime`, `rg_sce_sif`, `rg_sce_padmc`, `rg_native_iop`, `rg_native_audio`, and what
links them or a dropped library: `rg_ps2_hwbus`, `rg_movie_runtime`, `rg_ps2_overlay_bind`,
`rg_trace`, `rg_savestate`.

### Source guards (no behaviour change in the default config)

`src/native/iop/rg_iop.h`: `RG_IOP_ORACLE` is 1 by default, 0 with `RG_NATIVE_ONLY`; then
`rg_iop_native()` / `rg_iop_hle()` are the constants 1 / 0 and `RG_IOP_PICK(native, hle)`
keeps only its native expression. Every HLE tail / helper is inside `#if RG_IOP_ORACLE`
(preprocessor, not dead-code elimination: the clone has no reference to an HLE symbol at
any optimisation level).

| File | Native-only |
| --- | --- |
| `src/sce/sif/sif_ee.c` | no SIF boot, no SIF0 DMAC handler, no RPC client / EE servers / heap / loadfile over the HLE; the native "no IOP" answers only. `sif_reg_get` / `sif_reg_set` are defined here over the native register shadow (the HW SIF registers `src/ps2/hwbus` maps; NATIVE-IOP.md section 4 asked for exactly this) |
| `src/sce/sif/fileio.c`, `libsdr.c` | native fileio (`rg_iop_fio`) only; sdremote = unconverted |
| `src/sce/padmc/libpad.c`, `libmc.c` | the native pad and save services only |
| `src/runtime/runtime.c` | no CDVD glue / device / mount, no `iop_post_install`, no padman / `snd_sync` in `on_vblank`, no SIF boot, no `snd_output_read`; `RG_FS_ORACLE` / `RG_CDVD_MODEL` say "ignored"; `$RG_AUDIO_LOG`'s cd_* columns are 0; audio compare clocks are NULL |
| `src/native/iop/rg_iop.c` | `RG_IOP=hle` refused with a message; `rg_iop_set_mode` stays native |
| `src/native/audio/ra_host.c` | `RG_AUDIO=hle|compare`, `RG_AUDIO_PCM/MOVIE=hle` refused with a message |
| `src/sce/cdvd/libcdvd_native.c` (new) | libcdvd with no drive: always-ready PS2 DVD, searches by name through `rg_fs` (lsn 0), sector reads refused (reported once as an unconverted disc reader), idle drive; `sceCdHleSetReadHook` accepted (it can never fire) |

## 2. Link audit (`tools/native/link_audit.py`)

Reads the lld-link `/MAP` rg-game writes (`rg-game.map` next to the exe): every public and
static symbol row names `lib:object`; a symbol's size is the distance to the next symbol of
its section (sums are exact per section). Classes: `iop` (forbidden for a native-only exe:
the libraries above), `render` / `kernel` / `cpu` (emulation still needed, with the owning
lane), `vu0lib` (libvu0 on the VU register struct), `overlay` (the overlay arena manager,
arena and RG_OVL_DATA backing; was `ps2-other` until 2026-10-25), `native`, `port`.

```
python tools/native/link_audit.py report build/nonly-i686/rg-game.map [--all] [--by object] [--tsv out.tsv]
python tools/native/link_audit.py check  build/nonly-i686/rg-game.map [--forbid iop|render|kernel|cpu|vu0|vu0lib|overlay|all]
python tools/native/link_audit.py diff   build/niop-i686/rg-game.map build/nonly-i686/rg-game.map
python tools/native/link_audit.py refs   build/niop-i686/rg-game.map   # who pulls the forbidden code in (llvm-nm)
```

`check --forbid all` is the D9 end-state gate (fails until the renderer, threads and CPU
lanes finish). Data sizes include `.bss` (the 2 MiB IOP RAM and 2 MiB sound RAM models are
`.bss`): the column is memory footprint, not file size.

## 3. Verification

All from one tree (2026-10-18 ~06:30), `build/nonly-i686`: `rg-game` (native-only) and
`rg-game-oracle` (the same game objects and host sources linked with the oracle-capable
libraries, i.e. what a default build links). Run dirs under `out/nonly/` (game-derived, not
committed). RG_GPU=hw, every RG_IOP / RG_AUDIO / RG_THREADS at its default.

**Build-dir-only workaround (not in the repo build):** another lane's untracked override
`overrides/src/main/camera/CameraObjApplyInputMaybe_1619e0.c` no longer compiles against
`game/include/port/game_protos.h` regenerated at 05:36 (conflicting prototype of
`CameraObjOrbitControlMaybe_161260`). `build/nonly-i686` sets `CMAKE_PROJECT_INCLUDE` =
`out/nonly/local_workaround.cmake`, which defines `RGP_SELF_CameraObjOrbitControlMaybe_161260`
for that one file. Both exes share the object, so the comparison is unaffected; the owner of
the override has to fix it for everyone else.

### Link audit (`link_audit.py`, `rg-game-oracle.map` -> `rg-game.map`)

| Class | Before: libs, code KB, data+bss KB | After |
| --- | --- | --- |
| iop (forbidden) | 9, 63.8, 4,206.8 | **0** |
| render (renderer lane) | 6, 312.3, 1,204.6 | 6, 312.3, 1,204.3 |
| kernel (threads lane) | 3, 36.1, 275.5 | 3, 36.1, 275.5 |
| cpu (VU0/CPU lane) | 3, 20.6, 25.1 | 3, 20.6, 25.1 |
| ps2-other (overlay loader) | 3, 4.6, 252.5 | 3, 4.6, 252.5 |
| **emulation total** | **24, 437.5, 5,964.5** | **15, 373.7, 1,757.3** |

Removed: `rg_ps2_sound` 2,103 KB (2 MiB sound RAM .bss), `rg_ps2_iop` 2,095 KB (2 MiB IOP
RAM), `rg_ps2_sif` 30, `rg_ps2_spu` 16, `rg_ps2_padmc` 10, `rg_ps2_cdvd` 9, `rg_ps2_iop_hle`
4, `rg_native_fs_oracle` 2, `rg_sce_cdvd` 2; the SDK surface shrinks (`rg_sce_sif` 19 -> 4 KB,
`rg_sce_padmc` 19 -> 12 KB); added `rg_sce_cdvd_native` 1 KB. `refs` on the native-only map
(with `--game`): no linked object references a forbidden library. Tables:
`out/nonly/audit_{before,after}.tsv`.

### Golden route (`nonly_route.py run`, power-on to field 31,700, `newgame_save1`)

| | rg-game-oracle (default twin) | rg-game (native-only) |
| --- | --- | --- |
| run hash | f3b853eebb958224 | **f3b853eebb958224** |
| milestones (align --nowrap) | 37 | 37, **0 segments differ** (game mode 7 at vbl 22,863, ...) |
| peak working set | 289.9 MB | 229.3 MB |
| peak private bytes | 279.5 MB | 237.5 MB |
| wall (headless, shared PC, another lane's rg-game running) | 714 s | 601 s (not a speed claim) |

3,000-field repeats (2 each): private bytes 203.1 / 202.8 MB (twin) vs 198.0 / 188.4 MB
(native-only), run hashes identical: the memory saving is real but its size beyond the
4.2 MB of removed .bss is noisy (GPU driver allocations dominate the variance).

### Startup (`nonly_route.py startup`, power-on to the end of field 1, 3 runs each)

Twin 0.513 / 0.507 s (min), native-only 0.511 s: no measurable difference (init is the
D3D11 device and the window-less host; the IOP boot was already skipped at run time).

### Fixtures (native-only exe, `out/fixtures/62d5912c7b5c33de`)

`regen.py --check 300`: 14 states, all 7 milestones reached at their fields (title 1,500 ...
saved 31,620). `verify.py`: **7 / 7 OK** (each milestone loaded, 300 fields: run hash and
frame hash equal to the power-on run). States only load into the exe that wrote them; the
set is the native-only build's own.

### ctest (`build/nonly-i686`, `RG_DATA` set)

`ctest -j2 -LE fixtures` 701 tests + `ctest -j1 -L fixtures` 6 (one rg-game at a time):
**707 / 707 pass** after one fix. The test suites never link the clones: every oracle test
(padmc / sif / sound / runtime / cdvd / native_audio compare ...) builds and runs exactly as in
a default build; the fixtures tests and `native_only.*` use the native-only rg-game.

Fix: `trace.timing_demo` failed (also in `build/niop-i686`, so not caused by this lane): it
runs `rg-runtime-demo`, which drives the bring-up sound / SIF path, without `RG_IOP=hle`
since native became the default. `tests/trace/CMakeLists.txt` now pins `RG_IOP=hle` for it,
as `tests/runtime` does.

## 4. What is still linked, and who removes it

`link_audit.py check build/nonly-i686/rg-game.map --forbid all` lists them (the D9 end-state
gate; it fails until these lanes finish):

| Library (code / data+bss KB) | Lane | To leave the exe |
| --- | --- | --- |
| ~~`rg_ps2_dmac`, `rg_sce_graphics`, `rg_ps2_hwbus`~~ **gone (2026-10-18 (7))**; ~~`rg_ps2_vu` + `rg_ps2_vif`~~ **gone (8)**; ~~`rg_gpu`, `rg_ps2_gs`~~ **gone (2026-10-24 (10))**: the whole `render` set | renderer (docs/NATIVE-RENDER.md "DMA without the DMAC", "Still emulated") | `RG_RENDER=native` as the only path; then add these to a `render` drop set in `cmake/native_only.cmake` and `--forbid iop,render` in the gate test |
| ~~`rg_ps2_kernel` 29 / 201, `rg_sce_kernel` 6 / 65, `rg_ps2_spin` 1 / 10~~ **gone (2026-10-18)** | threads (docs/NATIVE-THREADS.md "Native kernel table", "Native-only") | done: replaced in rg-game by `rg_native_kernel_ps2k` (the native kernel table under the real ps2k names), `rg_native_spin` and `rg_sce_kernel_native` (libkernl without the census recorder); `tests/native_only` forbids `iop,kernel` |
| `rg_ps2_hwbus` 6 / 23, `rg_vu0` 1 / 2, ~~`rg_sce_vu0` 14 / 1~~ **gone (2026-10-25)** | VU0/CPU | hwbus / rg_vu0 gone earlier; `rg_sce_vu0` replaced by `rg_native_vu0` (libvu0 as plain C lanes, NATIVE-CPU.md section 9; set `vu0lib`) |
| ~~`rg_ps2_overlay`, `rg_ps2_overlay_bind`, `rg_ovl_arena` (249 KB arena), `rg_ovl_data`~~ **gone with `RG_NATIVE_OVL` (2026-10-25)** | overlay | the native module table `rg_native_ovl` + generated `rg_ovl_native_game` (per-overlay data segments, no retail addresses; OVERLAY.md section 8); set `overlay` |

### Proposals (not done here: owners' files)

- **Threads lane: done 2026-10-18** (NATIVE-THREADS.md "Native-only"). Not as proposed (a
  guarded clone of `rg_ps2_kernel`) but further: the frame-driven mode moved out of the HLE
  into the native kernel table (`src/native/threads/rg_nk*.c`), which replaces the whole HLE
  library in rg-game (`RG_NONLY_REPLACE rg_ps2_kernel=rg_native_kernel_ps2k`, also
  `rg_ps2_spin=rg_native_spin`, `rg_sce_kernel=rg_sce_kernel_native`). `RG_THREADS_ORACLE`
  (`src/native/threads/rg_threads_oracle.h`) guards the consumers: the HLE modes and the
  service registry in `rg_threads.c`, the census recorder (`kcensus.c`). `native_only.cmake`
  now maps a replacement's own dependencies like any library's (a replacement is cloned when
  one changes).
- **Kernel, SIF0:** nothing installs a SIF0 DMAC handler natively any more; the generic
  handler mechanism stays for VIF1 until the renderer calls its end-of-frame handler directly.
- **Audio lane:** compare mode (`RG_AUDIO=compare`) now exists only in default builds; moving
  it to a tool (an exe that links `rg_ps2_sound` and the engine) would let the default build
  drop the HLE too.
- **Default flip: done 2026-10-18** (NATIVE-CPU.md section 8): `RG_NATIVE_ONLY` defaults ON;
  `rg-game-oracle` is the oracle twin; tests are unaffected (they never link the clones).

## Checkpoint

- 2026-10-25 (D9 address gate, BRINGUP-HISTORY.md): `addr_census.py --check` PASS (0 arith / 0
  marker, was 36 / 44); ctest `native_only.addr_census` + `_control`. hwaccess stage: native
  register calls + stripped markers (one re-ingest, 33 files); `rg_gs_reg_r64 / w64` in nr_hw.c +
  hwbus.c; `rg_crt0_heap_size`; KernelReleaseAlarm_4473a0 in PORT_PROVIDED.tsv.

- 2026-10-25 (D9 residue, BRINGUP-HISTORY.md): `rg_sce_vu0` -> `rg_native_vu0` (`RG_NONLY_REPLACE`), the
  overlay arena manager -> the native module table (`RG_NATIVE_OVL`, default ON: replace
  `rg_ps2_overlay=rg_native_ovl`, drop `rg_ps2_overlay_bind`, `rg_ovl_arena`; `rg_ovl_data` no longer
  referenced). link_audit sets `vu0lib`, `overlay` (`ps2-other` gone); the gate test forbids them.
  `check --forbid all`: PASS, 0 pending. ctest 732/732, fixtures 8/8, bootcheck 29/29, mapcheck 5/5.
- 2026-10-24 (renderer lane, NATIVE-RENDER.md checkpoint 10): `rg_gpu` and `rg_ps2_gs` out of the
  native-only rg-game (RG_NONLY_DROP where the D3D11 device exists; headless Linux keeps the software
  GS model): the native GS state block / GIF input / worker (`nr_gs.c`, `nr_q.c`, `nr_hw.c`) and the
  device (`nr_dev.cpp`, `nr_d3d11.cpp`) in `rg_native_render`; local memory is the GPU's alone.
  `check --forbid iop,kernel,vu0,render-dma,render-vu,render` PASSES (4 pending libraries left:
  `rg_sce_vu0`, the overlay loader / arena); exe 10,058,240 -> 9,172,992 bytes; the gate test now
  forbids `render` too.
- 2026-10-19 (renderer lane, NATIVE-RENDER.md checkpoint 9): no change to the link (`render` still =
  `rg_ps2_gs` + `rg_gpu`; `check --forbid ...,render` FAIL on those two as before).  What moved:
  every primitive of the gate runs is drawn by the native pipeline (the GS-exact raster only for
  the remaining immediate fallbacks), the GIF parser's input is down to texture uploads, SIGNAL
  packets and markers (DIRECT / PATH3 drawing packets are immediate records; `libdma_native.c`
  `rg_gif3_hook`), battle CLUT read-backs gone.  Next for the link: NATIVE-RENDER.md "Still
  emulated (after checkpoint 9)" steps 2-4.

- 2026-10-19 (renderer lane, NATIVE-RENDER.md checkpoint 8): `RG_NONLY_DROP` + `rg_ps2_vif`,
  `rg_ps2_vu` (every VU1 program native: `nr_vux.c` at the frame walker); link_audit set
  `render-vu`; gate test forbids `iop,kernel,vu0,render-dma,render-vu` + `rg_ps2_hwbus`. Left of
  `render`: `rg_ps2_gs`, `rg_gpu`.

- 2026-10-18 (renderer lane, NATIVE-RENDER.md checkpoint 7): `RG_NONLY_DROP` + `rg_ps2_dmac`,
  `RG_NONLY_REPLACE` + `rg_sce_graphics=rg_sce_graphics_native`, `rg_ps2_hwbus=rg_ovl_data`;
  `rg_native_render` is a guarded clone; link_audit set `render-dma`; gate test forbids
  `iop,kernel,vu0,render-dma` + `rg_ps2_hwbus`.

- 2026-10-18 (CPU residue lane, NATIVE-CPU.md section 8): `RG_NATIVE_ONLY` default ON; gate
  `native_only.link_audit` forbids `iop,kernel,vu0` (`vu0` = the VU0 model `rg_vu0`, only linked
  by `RG_VU0_MODE=model`, where the test drops it); hwbus stays (renderer's GS privileged + VIF1
  sites); rg_movie_runtime no longer links hwbus / dmac.

- 2026-10-18: option, clone mechanism, guards, native libcdvd, link_audit.py, gate test,
  `rg-game-oracle` twin, nonly_build.ps1 / nonly_route.py. Verified (section 3): audit PASS
  (twin FAIL), golden route run hash + 37 milestones identical, fixtures 7/7, ctest 707/707.
  Next (other lanes): renderer -> `render` drop set; threads -> `RG_THREADS_ORACLE`
  (section 4).
- 2026-10-18 (threads lane): `kernel` set gone from rg-game (see section 4 and
  NATIVE-THREADS.md); `native_only.link_audit` checks `--forbid iop,kernel`. Resume: `powershell -File tools/native/nonly_build.ps1 -Targets
  rg-game,rg-game-oracle`, then `ctest -L native_only` in build/nonly-i686.
