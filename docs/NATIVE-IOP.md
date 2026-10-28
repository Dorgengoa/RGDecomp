# Native IOP: no SIF, no IOP, no pad / memory-card servers (de-emulation lane: IOP)

PLAN.md D9 / "Native end state": *"SIF/IOP HLE, IOP RAM ... -> native ...; Pad/MC servers
(padman/mcserv) -> Native input-action layer and save files, called directly."* Same pattern
as NATIVE-FS / NATIVE-AUDIO / NATIVE-THREADS: census script, design, native services called
at the game's highest sensible boundary, the old path kept as the oracle behind a switch,
verification against it.

Status (2026-10-18): **`RG_IOP=native` (the default) makes 0 calls into `src/ps2/sif`,
`src/ps2/iop`, padman or mcserv on the golden route** (power-on to the first save and back
in the field, 31,700 fields; census counter, section 4). libpad and libmc answer from the
native pad and save services directly; the IOP boot (reboot, module loads, `sceFsReset`,
SIF init) is a no-op with the same return contract; the runtime no longer boots the SIF or
renders the sound HLE every field. `RG_IOP=hle` is the old path unchanged (the oracle).

| Part | Where |
| --- | --- |
| Switch + census counters | `src/native/iop/rg_iop.[ch]` (`rg_native_iop`): `RG_IOP=native\|hle`, `RG_IOP_API` / `RG_IOP_HLE` counters, `RG_IOP_CENSUS=path`, `RG_IOP_ASSERT=1`; game view `include/port/native_iop.h` |
| Native fileio | `src/native/iop/rg_iop_fio.[ch]`: device mapping + stdio of FILEIO 0x80000001 as a host service (the FILEIO HLE server now calls it too) |
| Native pad service | `src/native/input/rg_npad.[ch]` (`rg_native_input`): the DS2 the game sees through libpad; `rg_pad_io.[ch]`: input source, latched reports, rumble hook, scripts (moved out of padman, shared by both paths) |
| Native save service | `src/native/saves/mccard.[ch]` (moved from `src/ps2/padmc`), `mc_time.c` (card time model, shared with mcserv) (`rg_native_saves`) |
| SDK surface | `src/sce/padmc/libpad.c`, `libmc.c` (native branches), `src/sce/sif/{sif_ee,fileio,libsdr}.c` (native "no IOP" answers) |
| Game side | overrides `overrides/src/main/sys/IopRebootWithImage_15e560.c`, `LoadIopModules_15e240.c` |
| Runtime | `src/runtime/runtime.c`: mode decision (step 6), no SIF boot / post-install (step 7), native pad step in `on_vblank`, no `snd_sync` / `snd_output_read` (engine frames read directly), census report at shutdown |
| Census tool | `tools/native/iop_census.py` (`static`, `dynamic`, `compare`) -> `census/native_iop_*.tsv`; `tools/native/iop_instrument.py` (inserts the counters) |
| Oracle | `RG_IOP=hle`: `src/sce/sif` -> `src/ps2/sif` + `src/ps2/iop` + padman / mcserv (`src/ps2/padmc`) + the sound HLE, as before |
| Tests | `ctest -L native_iop` (padmc.native.*, padmc.npad_equiv, sif.native_sdk, runtime.native.*); `-L "padmc\|sif"` |
| Build | `powershell -File tools/native/audio_build.ps1 -BuildDir build/niop-i686 -Targets "rg-sif-tests,rg-padmc-tests,rg-game"` (`-Reconfigure` after adding an override) |

## 1. Census

`python tools/native/iop_census.py static` (game sources with overrides in place, units the
port excludes skipped) -> `census/native_iop_static.tsv`: **221 call sites** into the
IOP-facing SDK surface.

| Area | Sites | Game callers (the boundary) | Native path now |
| --- | --- | --- | --- |
| memcard (libmc) | 95 | 13: the save manager steps `McGetInfoStep_375640`, `McFormatStep_3736b0`, `McLoadStep_373890`, `McSaveCreateStep_375090`, `McSaveStep_374110`, `McSaveDirScan_3748c0`, `McSaveSlotScanStep_374b00`, `SaveDirRenameJpToUs_373160`, `McEndSession_372d60`, `McPollCardChange_372db0`, ... | libmc native -> save service |
| sdremote (libsdr) | 40 | 22: `SoundIopSendCmdG*`, `SdRemoteInitMasterVolume_165608`, `SoundThreadCmd*` | none reached (native audio overrides above them) |
| pad (libpad) | 19 | 7: `PadSysInit_185080`, `PadPortOpen_184ed0`, `PadWaitReady_1849e0`, `PadUpdateConnection_184a50`, `PadReadData_184df0`, `PadIsAnalogMode_184960`, `PadUpdateVibration_184250` | libpad native -> pad service |
| loadfile | 17 | `LoadIopModules_15e240` (15 modules via `IopLoadModuleRetry_15e420`), `SysInitHardware_15e670` | override: nothing loaded |
| sifdma | 16 | sound bank / stream / movie-audio upload sites | none reached (native audio) |
| iopheap | 13 | `IopHeapInitOnce_1c2310`, `IopHeapAllocLocked_1c22d0`, `SoundRpcInit_1bc840`, sound bank sites, `AudioDecCreate_1d3210` | `sceSifInitIopHeap` native no-op (from `IopHeapInitOnce`); allocations not reached |
| fileio | 10 | `FileSlot*` type 0 (`host:`), `FileWriteAll_180060` (`host0:` debug), `IopRebootWithImage_15e560` (`sceFsReset`) | native fileio (host files); 1 `sceOpen` at boot |
| sifrpc / iopcontrol | 8 | `SysInitHardware_15e670` (`sceSifInitRpc`), `IopRebootWithImage_15e560`, `SoundRpcInit_1bc840` (hle branch) | native no-ops / override |

`dynamic` (the runtime counts every SDK entry and every HLE entry; `RG_IOP_CENSUS=path`):
golden route power-on to 2,500 and to 31,700, both modes; `compare NATIVE HLE` prints them
side by side (section 4). The pad and card call paths:

```
pad   game Pad* (7 units) -> libpad scePad* (src/sce/padmc/libpad.c)
        hle:    -> sceSifCallRpc 0x80000100 fno 1 (sync) -> padman server; readers read
                   padman's DMA buffer halves (padman_update per VBlank, sif0_write)
        native: -> rg_npad_* (src/native/input) ; rg_npad_update per VBlank
card  game Mc*/Save* -> libmc sceMc* (src/sce/padmc/libmc.c)
        hle:    -> sceSifCallRpc 0x80000400 (NOWAIT + end fn; Init sync) -> mcserv -> mccard;
                   completion on the SIF0 event + sif_post(card time)
        native: -> mccard_* directly; completion at issue + mc_time_cost on the virtual clock
input  host (src/host input-action layer / scripts) -> runtime pad_source -> rg_pad_io (shared)
```

## 2. Design

### Boundary

- **Pad and card: the libpad / libmc API.** Every libpad and libmc function is an asm SDK
  unit the port reimplements anyway (`game/EXCLUDED.tsv`), and the game never touches the
  pad DMA buffer or the libmc buffers. So the API is the highest boundary that leaves the
  game's own pad and save state machines alone; above it, nothing changes. The native
  branch is chosen per call (`rg_iop_native()`), so the same exe runs either path.
- **IOP boot: the game's two boot functions** (`IopRebootWithImage_15e560`,
  `LoadIopModules_15e240`): native overrides do only the game's own DVD-mode init. The
  remaining SDK entries the boot reaches (`sceSifInitRpc` from `SysInitHardware_15e670`,
  `sceSifInitIopHeap` from `IopHeapInitOnce_1c2310`) answer natively in `src/sce/sif`.
- **Everything else in `src/sce/sif`** has a native answer that never calls the HLE: the
  "no IOP" contract (reboot / sync / alive 1, module ids 1.., registers read as a booted
  IOP, fileio on host files). SIF RPC binds / calls, SIF DMA, IOP heap allocations,
  sdremote and EE-side RPC servers have no native meaning: they answer safely (bind
  non-NULL, end functions run, DMA complete, heap budget handles) and are counted as
  **unconverted** (stderr once per kind). The golden route has 0.

### Native pad service (`rg_npad`)

The padman semantics docs/PADMC.md describes, without the transport: per-VBlank steps
FINDPAD -> FINDCTP1 -> STABLE / DISCONN, digital power-up, commands BUSY for `cmd_frames`,
`keep_analog_lock`, the 32-byte read, the measured mode table and actuator answers. Readers
answer from a per-port view as of the last steps; two views alternate by frame and libpad's
open resets only some of their fields, exactly as the two DMA buffer halves, so even a
reopened port reads what it read on the PS2 (the game opens each port once). Input comes
from the shared `rg_pad_io` source (the runtime's `pad_source`: the input-action layer or
the input script), asked once per port per VBlank step exactly as padman asked, so the
input-source calls (and what the run hash folds from them) are the same in both modes.
`PadReadData_184df0`'s 32-byte override stays (the read length is 32 natively too).

### Native save service (`mccard` + `mc_time`) and libmc

`mccard.c` (PS2 card semantics on host files: directories, icon.sys, attributes, times,
crash-safe writes, backups, metadata; docs/SAVES.md) was already kernel- and SIF-agnostic;
it moved to `src/native/saves` unchanged, so saves stay byte-compatible. The card time model
moved with it (`mc_time_*`; `mcserv_config` is now an alias, mcserv uses `mc_time_cost`).
Native libmc keeps what the game observes: one operation in flight (-200 until `sceMcSync`
collects it, -100 before Init, -200 after End), issue-time codes (-210 names), the
function number `sceMcSync` reports (Mkdir 11, Rename 19), completion at issue + card time
(polled `sceMcSync(1)` charges `poll_cycles` = a timed wait natively; `sceMcSync(0)` is a
kernel-private timed wait), GetInfo / Chdir outputs written at completion. No semaphores
(the HLE created two per `sceMcInit` and one per sync RPC; ids are opaque to the game).

### Runtime

Step 6 decides the mode: `RG_IOP` (default native), forced to hle (with a message) while a
sound path still needs the IOP HLE (`rg_audio_hle_needed()`: `RG_AUDIO=hle|compare`,
`RG_AUDIO_PCM/MOVIE=hle`). Native: `rg_npad_reset` instead of `padman_reset`; step 7 does
no `rg_sif_boot` / `iop_hle_set_post_install` (so no SIF0 DMAC handler, no servers, no
`snd_install`), only `rg_fio_set_roots(data dir)`; `on_vblank` steps the native pad (no
`padman_update`, no `snd_sync`); the host half reads the engine's frames with the new
`rg_audio_runtime_read` (no `snd_output_read` / `rg_audio_runtime_mix`). Save states: the
mode is model state (travels with a state); `rg_iop_fio.c.obj` (FILE handles) and
`mccard.c.obj` (now in `rg_native_saves`) are HOST rows in `ss_map.c`.

## 3. Verification

Exe `build/niop-i686/rg-game.exe` (RG_GPU=hw, RG_THREADS / RG_AUDIO / FS at their native
defaults). Run dirs under `out/niop/` (game-derived, not committed).

### Golden route, native vs the HLE oracle (`out/niop/a` native, `out/niop/b` `RG_IOP=hle`)

Power-on to field 31,700 with `tools/trace/goldens/newgame_save1.input.txt`, `RG_TIMING` and
`RG_IOP_CENSUS` in both (`out/niop/a/run.sh native|hle`):

| Check | Result |
| --- | --- |
| `timing.py align a/port.milestones.tsv b/port.milestones.tsv --nowrap` | 30 milestones each, **sequences identical, 0 of 29 segments with a different main-tick count** (game modes 11 / 7 / 11 / 7 / 11 at the same VBlanks: 3141, 22863, 23217, 24707, 26067) |
| frame hashes at 1800 / 8300 / 23090 / 26800 / 28800 / 30200 / 31400 / 31650 | **all 8 identical** (1800 = `c0a568381736f720`, the documented title frame) |
| census, native run | **0 HLE entries, 0 unconverted**; 77,108 SDK calls: libpad (scePadGetState 45,121, Read 15,940, InfoMode 15,875, ...), libmc (Init 2, GetInfo 10, GetDir 2, Sync 123, End 1), `sceOpen` 1 (native fileio), `sceSifInitRpc` 1 + `sceSifInitIopHeap` 1 (native no-ops) |
| census, hle run | 267,506 HLE entries (padman_update 108,673, sif0_write 63,438, snd_output_read 63,400, snd_sync 31,700, 44 RPCs incl. 15 LOADFILE, reboot, sync); the same game-level SDK calls (the extra hle rows are libpad/libmc internal calls and the boot sequence the overrides skip) |
| run hash | differs (expected: the HLE's sync RPCs create / wait on / delete semaphores, which the kernel trace hash folds, and the HLE pushes silence frames before the game starts its sound driver) |

Both runs stop following the route at the same place: at 28,800 the game shows its pause
menu instead of Salgin field control, so neither reaches the route's save (31,360). The
oracle does the same, so this predates the lane (the route was written on
`out/route/exe4`; the battle outcome difference of NATIVE-THREADS.md section 5 applies).
The route agent owns that.

### Save / load round trip (`out/niop/bs`)

Through the game-save fixture (`run_from.py --boot-save save1`: the card the route wrote
with the old HLE build):

- **Native loads an existing save**: CONTINUE -> slot 1 -> FILE 01 -> "File 1 loaded." ->
  field control on the Salgin transporter (shots `load_2700.png`, `load_3890.png`); per-tick
  timing record identical to the oracle's boot (`timing.py build`, all 2,312 ticks equal);
  census 0 HLE entries.
- **Native writes a save**: `save_try.txt` (boot script + transporter -> Save -> slot 1 ->
  FILE 02 -> "Create new data?" Yes): "Saving data to file 2..." -> **"File 2 saved."**
  (`sv_montage.png`). Same input under `RG_IOP=hle`: same screens.
- **Cards compared** (`card_native` vs `card_hle`, kept with `--saves`): `card1.card`
  (metadata: attributes, both timestamps, creation order), `card1.txt`, both `icon.sys`,
  both `RG.ICO` and FILE 01 **byte-identical**; FILE 02's save data differs, but it also
  differs between two native runs and between two hle runs (also with `RG_GS_ASYNC=0`): the
  game writes run-dependent bytes (151 bytes: a 16-byte checksum at 0x20 plus per-character
  fields), not a card-path difference. Open question for the save lane.
- **Cross-load**: the oracle loads the natively written FILE 02 and the native path loads
  the oracle-written FILE 02 ("Load the data in file 2?" -> field control, `xl_montage.png`).

### Fixtures (`out/fixtures/b2ab31e033d5b2ce`, native)

`regen.py --exe build/niop-i686/rg-game.exe --only title,field,battle --check 300`, then
`verify.py`: title 1500 -> 1800 run hash `cd8da3e2adcb8f52` = power-on, frame
`c0a568381736f720` =; field 8000 -> 8300 `7b38c7a5e5bb9042` =, `e89f47fe31849838` =; battle
23000 -> 23300 `cc6ba1fae858b957` =, `ead43731b54315b3` =.

**Save-state bug found and fixed (`src/savestate/ss_heap.c`).** The first native set
crashed loading `field` (write fault in `heap_alloc`): the heap header, incl. its `commit`
mark, is restored raw from the saver, while the loader had committed pages only up to the
saved `top`; a saver that had committed past its top (top shrinks on free, commit never)
made the loader allocate into uncommitted pages. The HLE's init allocations happened to
hide it. Fix: the allocator tracks the pages this process really committed in its host
static (`H.committed`), not in the restored header. Native states from 7,400 / 8,000 load
since; `ctest -L fixtures` passes.

### Tests (`build/niop-i686`, `ctest -j2`)

`-L "padmc|sif|sound|fixtures|native_fs|native_iop|audio|runtime|kernel"`: **156/156 pass**
(with `RG_DATA`).

| Test | Checks |
| --- | --- |
| `padmc.npad_equiv` | the native pad service and padman over SIF run the same 420-VBlank session (unplugs, port 2 plugged for a while, every command incl. refused ones, SetReqState, closes / reopens, End, rumble): **41,153 answers identical** (every API return, every read's 32 bytes, rumble calls, virtual time per frame), keep_analog_lock off and on. Control (`npad_equiv_control`, native cmd_frames 2) fails |
| `padmc.native.*` (19 + 5 controls) | the whole pad + memory-card suite on the native services: pad_stable (states 5,1,2,2,6, InfoMode / InfoAct values, nothing written to the DMA buffer, 0 padman RPCs), pad_mapping, pad_replay, pad_rumble, pad_analog_lock, pad_game (the game's pad code), mc_files / errors / async (native completion timing = card time, no RPC latency) / persist, the save tests (card_states, save_cycle, full, exact_fit, corrupt, write_fail, backup, layout) and mc_game (the game's own save code) |
| `sif.native_sdk` | `RG_IOP=native` with no `rg_sif_boot`: the game's boot sequence, registers, fileio round trip through `host0:` / `cdrom0:`, the "no IOP" answers for RPC / DMA / heap / sdremote (counted unconverted); HLE counter stays 0. Control: one `sif_reg_get` must show |
| `runtime.native.init_order`, `runtime.native.pad_script` | the runtime boots with no SIF / padman / mcserv and 5 fields make 0 HLE entries; the demo's pad (script, vibration) on the native service |
| existing `padmc.*`, `sif.*`, `runtime.*` | unchanged on the HLE: the padmc / sif suites pin `RG_IOP=hle` themselves, the runtime tests get `RG_IOP=hle` (the demo drives the bring-up sound / SIF path) |

`tools/ingest.py --check`: my two overrides pass. Three other lanes' overrides are stale
after a concurrent re-ingest of `game/` (MainLoop, CameraObjApplyInputMaybe,
SoundStreamThreadMain).

## 4. What remains linked of src/ps2/{sif,iop,padmc,spu}

**Update 2026-10-18 ([NATIVE-ONLY.md](NATIVE-ONLY.md)):** `-DRG_NATIVE_ONLY=ON` builds the
rg-game below without any of these libraries (native-only clones of the SDK surface and the
runtime, `#if RG_IOP_ORACLE`); default builds and all tests are unchanged.


Nothing of it runs on the native path (census: 0 entries; `RG_IOP_ASSERT=1` aborts on the
first). It all stays **linked** in rg-game, because the oracle is chosen at run time, not
build time:

| Library | Why still linked | To drop it from the shipping exe |
| --- | --- | --- |
| `rg_ps2_sif` (`src/ps2/sif`), `rg_ps2_iop` + `rg_ps2_iop_hle` (`src/ps2/iop`) | `RG_IOP=hle` and the HLE branches of `src/sce/sif` (sif_ee / fileio / libsdr), libpad and libmc in the same functions; the runtime's step 7 hle branch; `src/ps2/hwbus` maps the HW SIF registers to `sif_reg_get` (0 reads on the route) | a build option (e.g. `RG_IOP_ORACLE=OFF`) that compiles the SDK surface native-only and leaves these libraries to the test executables (which already link them directly); hwbus answers the SIF registers from the native shadow |
| `rg_ps2_padmc` (padman, mcserv) | the HLE branches of libpad / libmc; `mcserv_config` is an alias of the native time model | same option |
| `rg_ps2_sound` (`src/ps2/iop/sound`) + `rg_ps2_spu` | `RG_AUDIO=hle|compare`, `RG_AUDIO_PCM/MOVIE=hle` (which force `RG_IOP=hle`), and the runtime's hle branch | same option, with the audio lane's compare mode moving to a tool |

Moved out of `src/ps2` into native libraries the default path uses: `mccard` (save
service), the card time model, the pad input source / rumble / script interface. The kernel
keeps its generic DMAC handler mechanism; nothing installs a SIF0 handler natively.
Proposed for the threads lane (not done here): the "SIF RPC latency" event-list use and the
SIF0 handler chain in NATIVE-THREADS.md section 5 are gone on the native path; the
memory-card poll still charges `poll_cycles` (a timed wait), and the blocking `sceMcSync`
uses `ps2k_wait_until`.

## 5. Files touched

- New: `src/native/iop/` (`rg_iop.[ch]`, `rg_iop_fio.[ch]`, CMake), `src/native/input/`
  (`rg_npad.[ch]`, `rg_pad_io.[ch]`, CMake), `src/native/saves/` (`mccard.[ch]` moved,
  `mc_time.c`, CMake), `include/port/native_iop.h`, overrides
  `sys/IopRebootWithImage_15e560.c`, `sys/LoadIopModules_15e240.c`,
  `tools/native/iop_census.py`, `tools/native/iop_instrument.py`,
  `census/native_iop_static.tsv`, `census/native_iop_dynamic.tsv`, this file.
- Owned, edited: `src/sce/padmc/{libpad,libmc}.c`, `src/sce/padmc/CMakeLists.txt`,
  `src/sce/sif/{sif_ee,fileio,libsdr}.c`, `sif_internal.h`, `src/ps2/padmc/{padman,mcserv}.[ch]`, `src/ps2/padmc/CMakeLists.txt`,
  `src/ps2/sif/sif.c`, `src/ps2/iop/{iop.c,iop_hle.c,CMakeLists.txt}` (census
  counters; FILEIO server on the native fileio), `tests/padmc/*`, `tests/sif/*`.
- Shared, localized: `src/runtime/runtime.c` (includes; step 6 mode decision + native pad
  reset; step 7 native branch; `on_vblank`; host-half audio read; shutdown report),
  `src/savestate/ss_map.c` (rows: `rg_native_saves mccard.c.obj`, `rg_native_iop
  rg_iop_fio.c.obj` HOST), `src/savestate/ss_heap.c` (the commit fix above),
  `src/ps2/iop/sound/snd_srv.c` (3 census counters), `src/native/audio/{ra_host.c,
  rg_audio_game.h}` (`rg_audio_runtime_read`), `tests/runtime/{runtime_tests.c,CMakeLists.txt}`,
  docs `PADMC.md`, `SIF.md`, `NATIVE-AUDIO.md` (pointers).
- Not edited: `tools/ingest.py`, `tools/stages`, `tools/fixtures`, `game/`, `src/gpu`,
  `src/native/render`, `src/ps2/gs`, `src/ps2/kernel`, `src/native/threads`.

## Checkpoint

- 2026-10-18: census (static 221 sites; dynamic both modes), `RG_IOP` switch + counters,
  native pad service (two-view semantics, equivalence test), native save service + libmc,
  native "no IOP" SDK answers + fileio, boot overrides, runtime without SIF / sound HLE.
  Verified: golden route milestones + 8 frames identical to the oracle, 0 HLE entries;
  save written / loaded / cross-loaded; fixtures title / field / battle +300 (after the
  ss_heap commit fix); ctest 156/156. Next: the build option that leaves the HLE out of
  the shipping exe (section 4), hwbus SIF registers native, the save-data nondeterminism
  question (section 3).
