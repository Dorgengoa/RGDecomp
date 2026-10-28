# Native file service (de-emulation lane 1)

PLAN.md D9 / "Native end state": *"CDVD sector/LSN model, FILEIO/LOADFILE HLE ->
File reads by name/offset from `data/` through the host file system; async loads as
host I/O."* This lane replaces the game's disc access. The game's own file layer now
opens its files **by name** and reads them **by byte offset** through a small host file
service; the CDVD sector model ([CDVD.md](CDVD.md)) is kept only as a check oracle and is
no longer mounted on the default game path.

Status (2026-10-17): **verified on the golden route to the first battle.** Unit +
real-data oracle tests pass; full ctest 636/636 run (the 637th, a long GPU replay, was
stopped by an earlier pause). The golden run on the native path (`out/nativefs/run2`)
reaches the first battle (game mode 7) at vbl **22,863** (old path 22,903: 40 vbl
earlier, the boot's saved drive time), with **0 oracle mismatches over all 338 reads**
and the **same read multiset** as the old path (328 of 338 in the same position; 3
reorders of one read past 3 others, like the retail/port reorders in BRINGUP.md).

| Part | Where | What |
| --- | --- | --- |
| Census | `tools/native/fs_census.py` | `static`: every caller of the disc/file SDK surface, climbed to the game's file API; `dynamic RUN.jsonl`: every read of a timing record mapped to its file |
| Service | `src/native/fs/rg_fs.[ch]` (`rg_native_fs`) | mount = index of `data/` by path; open by game name; sync positional reads; async reads on a host worker with caller-side delivery; read observers; stats |
| Oracle | `src/native/fs/rg_fs_oracle.[ch]` (`rg_native_fs_oracle`) | `RG_FS_ORACLE=1`: every native read is re-read through the CDVD sector model (MANIFEST -> LSN -> sectors) and compared byte for byte |
| Game side | `overrides/src/main/file/` (9 overrides), `include/port/native_fs.h` | the game's file layer over `rg_fs` |
| Wiring | `src/runtime/runtime.c` step 5, `src/game/rg_game_main.c` | `rg_fs_mount(data)` always; the CDVD model + drive only with `cfg.cdvd_model` (demo/tests; `RG_CDVD_MODEL=1`) |
| Timing record | `src/trace/timing.c`, `tools/trace/timing.py` | `FsRead` records (file, offset, length), counted as `cd_reads` |
| Tests | `tests/native_fs/` | `native-fs-tests` (synthetic), `native-fs-realdata-tests` (every disc file vs the oracle; `RG_DATA`) |

## 1. Census

Rerun: `python tools/native/fs_census.py static` (writes `census/native_fs_static.tsv`)
and `python tools/native/fs_census.py dynamic <run>/port.jsonl` (writes
`census/native_fs_dynamic.tsv`). Both are plain text processing (no build).

### Static (call graph, before this lane)

22 SDK symbols of the disc/file surface are called from game C: 14 `sceCd*`
(+ `CdDiskReadyNewMaybe_12a508`), FILEIO `sceOpen/Read/Write/Lseek/Close`,
`sceFsReset`, `sceSifLoadModule` and the overlay loader `OverlayLoadFile_100410`.
19 functions call them directly (level 1), 18 more at level 2, 9 at level 3.

| Path | Level-1 functions | What | Sync? |
| --- | --- | --- | --- |
| **file slots** (the game's fd layer, 12 slots `D_0049B100`) | `FileSlotOpenPath_1810a0`, `FileSlotRead_180aa0`, `FileSlotSeek_180ed0`, `FileSlotGetSize_180d50`, `FileSlotClose_180540` | device by prefix (`FilePathGetDeviceIndex`, table `D_0044A610`): 0 `host:` (FILEIO), 1 `cddat:` (member of a DAT archive), 2 `net:` (stubs), 4 `cdrom:` (disc file). Types 1/4: open = name -> (LSN, size); read = `sceCdRead(lsn + block, n)` + `sceCdSync(0)`, whole 2048-byte blocks | blocking on the calling thread |
| **archives** | `CdDatArchiveOpen_183110` (via `CdDatArchivesInit_182e70`, `CdDatArchivesOpenOnLayer_182dc0`) | reads `<DATA..>.HD6` (the index: names, block offsets, sizes) whole into a heap buffer, searches `<DATA..>.DAT` and keeps its LSN in `Buf.w0`; `DirTableFindFile_182f70` returns member LSN = `w0` + block offset | blocking |
| disc info | `CdDatArchivesInit_182e70`, `CdInitDvdMode_15e5d0`, `CdDiskWatchThread_17fdc0`, `CdDiskWatchInit_17ff70`, `CdWaitFileFound_180290` | dual-layer info, drive init/media mode, disc-present polling, power-off callback, "insert the disc" retry loop | - |
| overlay seek | `OverlayLocateFiles_1c3300` -> `FileCdSearchLocked_180360`, `OverlayCdSeek_1c32b0` | LSNs of the 7 `.BIN`s, `sceCdSeek` ahead of a load | - |
| overlay load | `OverlayLoad_1c3210` -> `OverlayLoadFile_100410` | FILEIO read of the `.BIN`: **already native** (bound by `src/ps2/overlay`, the file is not read; [OVERLAY.md](OVERLAY.md)) | - |
| debug writes | `FileWriteAll_180060` | FILEIO `host0:` write | - |
| IOP boot | `IopRebootWithImage_15e560`, `IopLoadModuleRetry_15e420`, `SoundRpcInit_1bc840` | `sceFsReset`, 15 LOADFILE module loads, `sceCdChangeThreadPriority` | - |

Above the file slots everything is game logic and stays as it is:
`FileReadChunked_180400` (1 MB chunks), `FileReadByPath_181f80` (sync whole-file
loads, e.g. `ResidentFileReadMaybe_1820a0`), `FileGetSizeByPath_181ee0`
(`LoaderTick_1ccc30`), the **async request queue** `FileReqSubmit_1827a0` +
`FileReqThread_182c30` (a game thread does the reads; the game polls each request's
done flags; `FileReqCancelAll_182510`), and the sound streams
(`SoundStreamProcessCmds_1c05f0`, `RingBufFillFromFile_1c1090`: `cdrom:` files read
in ring-buffer spans). Movies and sound banks never went through here: the movie
service and the sound HLE open their files themselves.

So the game has **one** disc read primitive (`FileSlotRead` -> `sceCdRead` +
`sceCdSync(0)`), one index read (`CdDatArchiveOpen`), and its asynchrony is its own:
a game thread blocking on synchronous slot reads. No caller polls the drive
(`sceCdSync(1)` is never used); no `sceCdSt*` streaming.

### Dynamic (golden NEW GAME run, old CDVD path)

`out/battle/run-a/port.jsonl` (golden input to vbl 26,000): **340 `sceCdRead`s, 53 MB,
4 files**, all sector-aligned windows into the archives:

| File | Reads | MB |
| --- | --- | --- |
| `DATA0_0.DAT` | 205 | 36.6 |
| `DATA0_1.DAT` | 133 | 16.0 |
| `DATA0_0.HD6` | 1 | 0.29 |
| `DATA0_1.HD6` | 1 | 0.11 |

i.e. two index reads at boot, then only `cddat:` archive members (no `cdrom:` file,
no `host:` file is opened on this route).

## 2. Design

### Boundary

The highest boundary that still leaves the game's logic alone is the **file slot**
layer: it is where a name becomes something readable and where every read happens.
Everything above it (loader queue, request thread, chunking, streams, resource
parsers) is game code that never saw a sector. The overrides replace only the
disc-facing parts:

| Override | Change |
| --- | --- |
| `FileSlotOpenPath_1810a0` | `cdrom:`: `rg_fs_open(name)` (was: `sceCd(Layer)SearchFile` retried until the disc answered). `cddat:`: the archive lookup also returns which archive matched; the slot gets that archive's handle. Slot layout unchanged: `u.info.f0` = rg_fs handle (was 0), `f2` = first 2048-byte block **inside that file** (was the disc LSN), size/block count as before |
| `FileSlotRead_180aa0` | one `rg_fs_read_fill(handle, (f2 + block) * 2048, buf, n * 2048)` (was `sceCdRead` + `sceCdSync(0)` + retry loop). Same bytes, same buffer extent (whole blocks; zeros past the end of the file, as the sector model gave), same return value, same game locks |
| `CdDatArchiveOpen_183110` | index read whole by name; the DAT opened by name, its handle kept in `rg_cddat_fd[slot]`; `Buf.w0` = 0, so `DirTableFindFile` yields block offsets relative to the archive |
| `CdDatArchivesInit_182e70` | no disc wait / dual-layer query: the dual flag stays 1 (the game keeps picking `DATA0_*` / `DATA1_*` names by disc row), `layer1_start` (never used) = 0 |
| `FileCdSearchLocked_180360` | existence + size by name; lsn 0 |
| `OverlayCdSeek_1c32b0` | empty (the seek only hid drive latency) |
| `CdDiskWatchThread_17fdc0` | no `sceCdGetDiskType` poll (the folder cannot be ejected); thread and locks kept |
| `CdDiskWatchInit_17ff70` | no `sceCdPOffCallback` |
| `CdInitDvdMode_15e5d0` | no `sceCdInit` / `sceCdMmode` |

`FileSlotSeek/GetSize/Close` need no change (for types 1/4 they only do arithmetic on
the slot). `CdWaitFileFound_180290` is left as it is: only the replaced error paths
called it.

After this, the default game path calls **no `sceCd*` function** except
`SoundRpcInit_1bc840`'s `sceCdChangeThreadPriority` (a constant `return 1`; the sound
lane's file), and the runtime does not mount the CDVD model or register the drive as a
kernel device.

### Service (`src/native/fs/rg_fs.h`)

- `rg_fs_mount(dir)`: recursive index of `data/` (directory walk, not MANIFEST.tsv;
  `converted/` and `MANIFEST.tsv` skipped): canonical key -> host path, size.
- `rg_fs_open(name)`: any game spelling (`cdrom0:\BIN\NORMAL.BIN;1`, `\DATA0_0.HD6;1`,
  `BIN/NORMAL.BIN`): device prefix dropped, `\` -> `/`, `;1` dropped, ASCII case
  ignored. Same name -> same handle; no close; the host file opens on first read and
  stays open.
- `rg_fs_read_fill(h, off, buf, len)`: one positional host read (`ReadFile` with an
  offset / `pread`), zero fill past EOF; returns bytes from the file or -1.
- Async: `rg_fs_read_async(h, off, buf, len, cb, user)` queues to a host worker thread;
  completion is visible **only** through `rg_fs_poll` / `rg_fs_wait` / `rg_fs_pump` on the
  caller's thread, and callbacks run there. The moment the game sees a completion is
  decided by when it polls, never by host I/O timing, so runs stay deterministic.
- Observers (`rg_fs_add_read_hook`): timing record, oracle. Stats: reads, bytes, host
  ns, opens, misses, errors (printed at runtime shutdown).

No sector size, LSN, layer, drive state or latency model exists in the service. The
2048-byte unit that remains is the game's own (its slot block size and the HD6 index's
offset unit).

**Async and the game.** The game's asynchrony is its request thread
(`FileReqThread_182c30`), which now does host reads that complete immediately in
virtual time; its done flags flip at the same point in its own control flow as before.
That thread is game logic and becomes a host thread with the threading lane (D9
"native game loop / host threads"); the async API is the primitive for that and for
the native audio/movie streamers. It is not wired into the default path yet, by
choice: the virtual-time load latency is already zero, and moving reads onto a worker
would add a host-timing dependence for no measurable gain on 53 MB per run.

### Oracle

`RG_FS_ORACLE=1` (runtime step 5) opens the old sector model next to the service and,
inside every read, maps the file to its LSN (`cdvd_disc_find`), reads the same range
as sectors and `memcmp`s; the summary is printed at shutdown
(`rg_fs oracle: N reads compared, M mismatched`). `RG_CDVD_MODEL=1` additionally mounts
the model + drive for libcdvd callers (nothing in the game calls them now).

## 3. Verification

Build: `build/nativefs-i686` (Release, configured like `render-i686`;
`out/bringup-checkpoint/bld.ps1 -BuildDir build/nativefs-i686`). `tools/ingest.py
--check`: 0 problems (170 overrides).

**Tests.** `native-fs-tests` (synthetic: names, spellings, skip rules, reads across
and past EOF, bad handles, async poll / wait / pump delivery order, "not delivered
until polled", hooks, stats) and `native-fs-realdata-tests` (`RG_DATA`: all 124 disc
files opened natively, size checked, first 256 KB + a middle block + the last partial
block read and compared with the CDVD sector model: **343 reads, 31 MB, 0 mismatches**)
pass. Full `ctest -j 6` in `build/nativefs-i686`: **636 passed, 0 failed**; the last
one (`gpu` scale2.replay-all, ~minutes) was stopped by the pause, not failed.

**Golden run** (`tools/trace/goldens/newgame_battle.input.txt`, `RG_GPU=hw`, headless,
`RG_TIMING`, `RG_TIMING_STOP_VBL=23150`, fresh `saves/`):

| | old path (`out/nativefs/base`, battle-i686 exe of 18:08, before this lane) | native path (`out/nativefs/run1` to vbl 16,600; **`run2`** (fixtures-i686 exe of 21:38) to the battle; `RG_FS_ORACLE=1`) |
| --- | --- | --- |
| TITLE overlay, main loop | vbl 120 | **vbl 62** (boot index reads no longer wait on the drive model: -58 vbl, ~1 s) |
| title movies | 249..1029, 1029..2105 | 191..971, 971..2105 (the attract movie ends at the same input) |
| NORMAL load (CROSS = NEW GAME) | overlay 2107, loadscreen 2113..3141 | overlay 2107, loadscreen 2113..3141 (unchanged: this screen's length is not I/O bound) |
| opening FMV | 3151..7321 | 3149..7319 |
| first battle (gamemode 7) | **22,903** (unlock 22,997) | **22,863** (unlock 22,957), `out/nativefs/run2` |
| disc reads | 338 `sceCdRead`, 52.8 MB, 4 files | run2: **338 `FsRead`, 52.7 MB, same 4 files; same multiset as the old stream, 328 in the same position** (reads #111-114, #302-305: one read moved past 3 others; #328/329 swapped; `fs_census.py stream`) |
| oracle | - | run2: **338 reads compared, 0 mismatched**, 0 unmapped sectors (`port.log`) |
| wall | 730 s to vbl 23,150 | run2: 487 s to vbl 23,150 (host I/O 20.9 ms for the route) |

Load-time gain: every disc read now completes in zero virtual time (was 1 ms + 370 us
per 2 KB sector of simulated drive time, i.e. ~5.5 MB/s: the 52.8 MB of this route cost
~9.6 s of game time before). Visible on the route as the boot (-58 vbl) and as per-read
latency in the field; the NORMAL loading screen and the FMV are paced by the game
itself and do not shrink. Host I/O for the whole route is tens of ms (positional reads
from the OS cache; the runtime prints `rg_fs: N reads ... ms host I/O` at shutdown).

Artifacts: `out/nativefs/base/{port.jsonl,port.milestones.tsv,fs_dynamic.tsv}`,
`out/nativefs/run1/{port.log,partial.jsonl,partial.milestones.tsv,fs_dynamic.tsv}`
(`partial.jsonl` = the record minus its torn last line),
`out/nativefs/run2/{port.log,port.jsonl,port.milestones.tsv,fs_dynamic.tsv}`.
Stream check (reusable): `python tools/native/fs_census.py stream out/nativefs/base/port.jsonl
out/nativefs/run2/port.jsonl` (exit 0 = same multiset; lists moved and one-sided reads).

## 4. What remains of the CDVD / IOP file path

- **Default game path:** no `sceCd*` call except `SoundRpcInit_1bc840`'s
  `sceCdChangeThreadPriority` (constant `return 1`, sound lane's file); the CDVD model and
  drive are not mounted and no CDVD kernel device exists (`cfg.cdvd_model = 0`).
- **Still linked** (not on the default path): `src/ps2/cdvd` + `src/sce/cdvd` (libcdvd for
  the demo/tests, `RG_CDVD_MODEL=1`, and the oracle), `CdWaitFileFound_180290` (only the
  replaced error paths called it), the timing record's `sceCdRead` source.
- **FILEIO (0x80000001):** `FileSlot*` type 0 (`host:` device, debug, not used on the
  route) and `FileWriteAll_180060` (`host0:` debug writes) still go through FILEIO HLE.
  Next: route `host:` through `rg_fs` (a host root) and writes through a host write call.
- **LOADFILE / sceFsReset / IOP reboot** (`LoadIopModules_15e240`,
  `IopRebootWithImage_15e560`): module list only; removed with the IOP/SIF HLE by the
  sound lane (native audio engine).
- Overlays (`OverlayLoadFile_100410`), movies (`src/movie`) and sound banks
  (`src/ps2/iop/sound`) already read host files directly.
- Async: `rg_fs_read_async` exists and is tested but is not on the default path (see
  "Async and the game"); the game's request thread becomes a host thread with the
  threading lane.

## 5. Resume checkpoint (next steps, exact commands)

Steps 1-2 are DONE (2026-10-17, `out/nativefs/run2`, see section 3): pass on all three
criteria. Remaining: 3 and 4.

1. Rebuild (tree is consistent; the default path is the native one), from .:
   `powershell -ExecutionPolicy Bypass -File out/bringup-checkpoint/bld.ps1 -BuildDir build/nativefs-i686`
2. Re-run the native golden run to the battle (about 12-13 min; PowerShell, from .):
   ```
   $o = "out/nativefs/run2"; mkdir "$o/bin","$o/saves"
   copy build/nativefs-i686/rg-game.exe,build/nativefs-i686/rg-game.map "$o/bin"
   $env:RG_DATA = "data"; $env:RG_GPU = "hw"; $env:RG_FS_ORACLE = "1"
   $env:RG_TIMING = "$o/port.jsonl"; $env:RG_TIMING_STOP_VBL = "23150"
   & "$o/bin/rg-game.exe" --headless --fields 24000 --saves "$o/saves" --input tools/trace/goldens/newgame_battle.input.txt *> "$o/port.log"
   python tools/trace/timing.py build "$o/port.jsonl" --map "$o/bin/rg-game.map"
   python tools/native/fs_census.py dynamic "$o/port.jsonl" --out "$o/fs_dynamic.tsv"
   ```
   Pass: `mem_gamemode 7` near vbl 22,900 and `mem_locked 0` ~94 vbl later in
   `port.milestones.tsv` (old path: 22,903 / 22,997), `rg_fs oracle: ... 0 mismatched`
   at the end of `port.log`, and the read stream equal to `out/nativefs/base` up to
   reorders. Optionally `timing.py align --nowrap` against `out/nativefs/base/port.*`.
   A run without `RG_FS_ORACLE` gives the plain host I/O time in its shutdown line.
3. Finish ctest: `ctest -j 6` in `build/nativefs-i686` (636/637 already passed).
4. Then: `host:`/FILEIO writes onto rg_fs (section 4); update CDVD.md/RUNTIME.md
   "CDVD on the kernel loop" to say the game no longer uses it.
