# CDVD model

The game reads the disc by sector (PLAN.md P2, "File HLE"): it looks a file up with
`sceCdSearchFile`/`sceCdLayerSearchFile`, gets its first sector number (LSN), and reads
sectors with `sceCdRead`. FILEIO is used only for IOP module loads. The port serves those
reads from the extracted `data/` folder ([EXTRACT.md](EXTRACT.md)); it never reads the ISO.

| Part | Where | What |
| --- | --- | --- |
| Disc | `src/ps2/cdvd/cdvd_disc.c` | `data/MANIFEST.tsv` turned into an LSN -> (file, offset) map, lookup by ISO path and layer, sector reads |
| Drive | `src/ps2/cdvd/cdvd_drive.c` | one asynchronous N-command (read or seek) at a time, completed on a virtual clock |
| libcdvd | `src/sce/cdvd/libcdvd.c` | the `sceCd*` functions, over the two above |
| Game names | `src/sce/cdvd/libcdvd_game_names.c` | the same functions under the names the decompiled game calls (`sceCdRead_12a728`, ...) |
| Tests | `tests/cdvd/` | synthetic fixtures (always), real data (with `RG_DATA`) |

All of it is CC0, written from scratch in C99. ps2sdk (AFL) was read as a reference for
CDVDMAN's behaviour and libcdvd's constants; no code was copied. Nothing in this module
depends on the EE kernel; the kernel drives it through `cdvd_poll()` (see "Drive").

## LSN space and layer 1

**Rule.** On the dual-layer disc, with L = the number of layer-0 sectors:

- `sceCdReadDvdDualInfo` reports `on_dual = 1`, `layer1_start = L`.
- `sceCdLayerSearchFile(fp, name, 1)` returns `fp->lsn = L + r`, where r is the file's
  extent inside the layer-1 ISO volume. Layer 0 (and `sceCdSearchFile`, which is
  `sceCdLayerSearchFile(.., 0)`) returns the extent as is.
- `sceCdRead(lsn, ..)` and `sceCdSeek(lsn)` reach drive sector `lsn` if `lsn < L`, and
  `lsn - 16` if `lsn >= L`.

The disc image is a linear dump of the drive's sectors, so image sector = drive sector.
For Rogue Galaxy, L = **1646704** (Redump's layer break, and layer 0's volume size). The
layer-1 volume's sector 0 is image sector 1646688 = L - 16, and its PVD is image sector
1646704. So:

| | LSN the game sees | Image sector (manifest `lba`) |
| --- | --- | --- |
| Layer-0 file | extent | extent |
| Layer-1 file | L + r = image + 16 | 1646688 + r |
| Layer-1 PVD | L + 16 = 1646720 | 1646704 |
| `DATA1_0.DAT` | 2740173 | 2740157 |
| `BIN/NORMAL.BIN` (both layers) | 1001888 (L0), 2740033 (L1) | 1001888, 2740017 |
| End of disc | 3402224 (exclusive) | 3402208 |

LSNs L..L+15 are layer 1's system area. That area has no sectors of its own, so the drive
returns image sectors 1646688..1646703 for them: the last 10 sectors of `DATA0_0.DAT`, 5
zero sectors and a UDF anchor. The model does the same.

**Evidence.**

1. *The game adds nothing.* `CdDatArchivesInit_182e70` calls
   `sceCdReadDvdDualInfo(&D_004811DC, &D_004811E4)` and keeps the dual flag; the
   `layer1_start` it gets back is never used in arithmetic. `CdDatArchiveOpen_183110`,
   `FileCdSearchLocked_180360`, `CdWaitFileFound_180290` and `FileSlotOpenPath_1810a0`
   call `sceCdLayerSearchFile(fp, name, D_004811E0)` when the disc is dual (the layer is
   chosen by `CdDatArchivesOpenOnLayer_182dc0`; `DATA0_*` sits on layer 0 and `DATA1_*`
   on layer 1). The LSN from the search goes straight to `sceCdRead`
   (`FileSlotRead_180aa0` reads `e->lsn + sect`; archive members add a sector offset
   within the archive). So whatever CDVDMAN returns from a search, it must accept in a
   read.
2. *The EE library is a thin RPC.* In the game's libcdvd, `sceCdSearchFile_129ae0` is
   `sceCdLayerSearchFile(fp, name, 0)`, and `sceCdLayerSearchFile_1297e0` only sends the
   name and layer to CDVDFSV (SIF RPC 0x80000597) and copies 0x24 bytes of
   `sceCdlFILE` back. `sceCdRead` passes the LSN to CDVDFSV 0x80000595 function 1. The
   arithmetic happens on the IOP, in CDVDMAN 2.38 from `IOPRP300.IMG`.
3. *CDVDMAN* (ps2sdk `iop/cdvd/cdvdman/src/cdvdman.c`, a reconstruction of Sony's
   module): `DvdDual_infochk` sets `m_layer_1_lsn` = the TOC's layer-0 end PSN - 0x30000
   + 1 (the layer-0 sector count), and `sceCdReadDvdDualInfo` reports it as
   `layer1_start`. `CD_newmedia` reads the layer-1 PVD at `fs_base2 + 0x10` with
   `fs_base2 = m_layer_1_lsn`. `CdSearchFileInner` adds `fs_base2` to a layer-1 file's
   extent. `cdvdman_read` and `sceCdSeek` pass the LSN through `sceCdLsnDualChg`, which
   for a dual-layer disc (`m_opo_or_para != 0`) subtracts 0x10 from LSNs at or above
   `m_layer_1_lsn` before the drive command.
4. *The image agrees.* For CDVDMAN's own PVD read (LSN L + 16, drive sector L) to land on
   the layer-1 PVD, which is at image sector 1646704, L must be 1646704. That is the
   layer-0 volume size and Redump's layer break. `cdvd-realdata-tests` checks this
   against the image when `RG_ISO` is set.

Not yet checked against a PCSX2 CDVD trace of the real game (see "Open issues").

**Table-driven.** The 16 is `CDVD_L1_SYSTEM_AREA` in `cdvd.h`. The geometry comes from
the manifest's `# volume` lines (v2): L = layer-1 volume base + 16. A v1 manifest has no
`# volume` lines, so `k_known_discs` in `cdvd_disc.c` supplies the geometry by image
SHA-1. A v1 manifest of an unknown disc with layer-1 files is refused. If L and layer 0's
volume size ever disagree, the model logs a warning and trusts the PVD position.

## Disc

`cdvd_disc_open(data_dir)` reads `MANIFEST.tsv` (v1 or v2; it stops at the first
`# section` line, so converted movies are not disc files). Each copy of each file becomes
an extent in image space: start = the copy's LBA, length = ceil(size / 2048). The two
copies of a file stored on both layers (35 files) point at the one `data/` file. Extents
are sorted and must not overlap. Files are opened lazily and kept open.

`cdvd_disc_read(lsn, count, buf)`:

- splits the request into runs that stay inside one file, one gap, and one side of L;
- reads each run with one `fread` at the run's byte offset in the file;
- **reads spanning files** just continue into the next extent;
- the bytes after a file's last byte, up to the end of its last sector, read as zero.
  On this disc every such tail is zero in the image too (checked: all 153 part-filled
  last sectors, counting both copies), so
  every sector inside a file is byte-exact;
- a request that runs past the end of the disc reads nothing and returns `CDVD_E_RANGE`.
  A missing or short `data/` file returns `CDVD_E_IO`.

**Sectors outside any file: zeros, with a warning.** The image has 764 such sectors in 3
runs: 0..384 (system area, volume descriptors, path tables, directories, UDF),
1646698..1646703 (5 zero sectors and a UDF anchor) and 3402194..3402207 (layer 1's end).
300 of them are not zero. The game never reads them: directories are walked only by
CDVDMAN on the IOP during a search, and the HLE replaces the search with a name lookup.
So the model returns zeros, counts them (`*unmapped`), and logs one warning per run
(at most 64 in all). If a reader of these sectors ever turns up, the extractor can save
the 764 sectors (1.5 MB) next to the files and the model can serve them exactly.

`cdvd_disc_map(lsn, &path, &offset)` gives the file and byte offset of one LSN, for trace
tools. `cdvd_lsn_to_image` and `cdvd_image_to_lsn` convert between the two numberings.

`cdvd_disc_find(name, layer)` accepts the game's spelling (`\BIN\NORMAL.BIN;1`, with or
without `cdrom0:`) or a manifest path. It ignores case and the `;1` version. It finds only
copies on the requested layer. On a single-layer disc the layer is ignored.

## Drive

The PS2 drive runs one N-command at a time. `cdvd_drive_read`/`cdvd_drive_seek` return 0
while a command is pending, as libcdvd does. Otherwise they return 1 and schedule
completion at `now + command_us + count * sector_us` (defaults 1000 us and 370 us per
sector, about 5.5 MB/s; `cdvd_drive_set_timing`). Bad parameters (no disc, LSN out of
range, zero sectors) are still accepted and complete with an error, like the real drive.

- **`cdvd_poll(now_us)`** is the hook for the EE kernel: it advances the drive's clock
  (virtual microseconds, never backwards) and completes a due command. The data is
  copied into the caller's buffer at completion, not at submit, so code that reads the
  buffer before `sceCdSync` sees stale bytes, as on hardware. Then the completion
  callback runs (`sceCdCallback`'s function, with `SCECdFuncRead` = 1 or
  `SCECdFuncSeek` = 4). The kernel should call `cdvd_poll` from a context where running
  that callback is allowed (on the PS2 it runs on libcdvd's callback thread).
- **`cdvd_next_event(&due)`** tells the kernel when to poll next.
- **`cdvd_drive_wait()`** (used by `sceCdSync(0)`) calls the hook set with
  `cdvd_drive_set_wait_hook(fn, ctx)` until the command completes. The hook must block
  the calling EE thread, run others, and return only after `cdvd_poll(t >= due)`. With
  no hook installed (today, before the kernel exists), the drive jumps its own clock to
  `due` and completes the command at once.
- Errors use libcdvd's codes: `0x00` none, `0x01` aborted (`sceCdBreak`), `0x12` no
  disc, `0x20` illegal LSN (past the end), `0x22` bad parameter, `0x30` host read error.

Not thread-safe: the EE runs one thread at a time (PLAN.md P2).

## libcdvd

From `census/platform_sdk_surface.tsv` (libcdvd, 14 boundary functions) and
`platform_sif_rpc.tsv`:

| Function (game name) | Behaviour |
| --- | --- |
| `sceCdInit` (`sceCdInit_12a008`) | `SCECdINIT`/`SCECdINoD`: mounts `$RG_DATA`, else `data`, if nothing is mounted (`sceCdHleMount` does it explicitly); returns 0 if that fails. `SCECdEXIT`: clears the callback. The game passes 3 extra arguments; they are ignored. |
| `sceCdMmode` (`_12ada0`) | Stores the media mode; returns 1. |
| `sceCdChangeThreadPriority` (`_12ab30`) | Returns 1 (there is no IOP CDVD thread). |
| `sceCdGetDiskType` (`_12a9d8`) | `SCECdPS2DVD` (0x14) when mounted, else `SCECdNODISC`. |
| `sceCdDiskReady`, `CdDiskReadyNewMaybe_12a508` | `SCECdComplete` (2) when mounted, else `SCECdNotReady` (6). |
| `sceCdTrayReq` (`_12ae98`) | `*traychk = 0` (the tray was not opened); returns 1. |
| `sceCdReadDvdDualInfo` (`_12acd0`) | `on_dual`, `layer1_start` per the rule above; returns 1. |
| `sceCdSearchFile` (`_129ae0`), `sceCdLayerSearchFile` (`_1297e0`) | Fills the 36-byte `sceCdlFILE` (`lsn`, `size`, `name` = `NAME.EXT;1`, `date` zero, `flag` 0); returns 1, or 0 if not found (error stays 0, which `FileSlotOpenPath_1810a0` treats as "no such file"). |
| `sceCdRead` (`_12a728`) | Starts an asynchronous read (2048-byte sectors only; another pattern completes with `0x22`). Returns 0 if a command is pending. |
| `sceCdSeek` (`_12a908`) | Starts an asynchronous seek. |
| `sceCdSync` | Even modes (0, 16) block until the N-command completes and return 0. Odd modes return 1 while busy, else 0. |
| `sceCdGetError` (`_12aa98`) | The last N-command's error. |
| `sceCdPOffCallback` (`_129690`) | Stores the power-off callback; `sceCdHlePowerOff()` runs it (host shutdown). |
| `sceCdCallback`, `sceCdBreak` | Not called by the game; provided for completeness. |

`sceCdSt*` (CDVDSTM streaming) is **not implemented**: the census found no `sceCdSt*`
client linked on the EE and no CDVDSTM RPC server use. Movies and sound read through
`sceCdRead` like everything else.

Deviations from the hardware, all deliberate:

- A search while a read is pending first lets the read finish (`cdvd_drive_wait`). Real
  libcdvd returns 0 and the game retries in a tight loop, which would never let virtual
  time advance. Only the timing differs.
- Name lookup ignores case. Rogue Galaxy upper-cases its paths before searching.
- `sceCdlFILE.date` is zero (the manifest has no dates; the game does not read it).

## Tests

`tools\build.ps1` builds them into the normal tree; run with CTest
(`ctest -R cdvd` in `build\i686-windows`).

- `cdvd-tests` builds a synthetic `data/` folder that copies the real disc's layout at
  small scale (layer 0 = 30 sectors, layer-1 volume at image 14, so L = 30). It checks
  the geometry and both conversions, lookup on each layer (including a file on both
  layers, a layer-1-only file, an empty file, and that converted-section rows are not disc
  files), reads that span two files, a file / gap / file read, reads across L, the
  layer-1 system area reaching layer 0's last sectors, the end of the disc, LSN -> (file,
  offset), v1 manifests (single layer; known disc by SHA-1; unknown dual disc refused),
  overlapping extents, a missing data file, and the libcdvd layer: asynchronous
  completion at the scheduled virtual time, no data before completion, busy refusal, the
  completion callback, blocking `sceCdSync` with and without a wait hook, the error codes,
  and the game-name entry points.
- `cdvd-realdata-tests` is skipped (exit 77) unless `RG_DATA` points at a real extraction.
  It checks `layer1_start` = 1646704 and the LSN end, `SYSTEM.CNF`'s text, and reads
  parts of 9 files through libcdvd (layer 0, layer 1, both copies of `BIN/NORMAL.BIN`,
  `DATA1_0.DAT` deep inside, `MOVIE/99/STAFF_A.MVI`, the last sectors of `DATA0_0.DAT`)
  against the extracted files, plus a 10-sector read across L. With `RG_ISO` set to the
  disc image it also compares every read with the image at the image sector the rule
  gives, and checks that LSN L + 16 maps to the image's layer-1 PVD.

Results (2026-10-11): both pass; the real-data test passes with `RG_DATA` and `RG_ISO`.

## Open issues

- Confirm the layer-1 rule with a PCSX2 trace of the game's CDVD reads (LSNs of
  `DATA1_*` reads should be manifest LBA + 16).
- Timing is a rough constant-rate model with no seek time. Loading-screen pacing depends
  on it; tune it against PCSX2 if needed.
- **Done 2026-10-12 (RUNTIME.md "CDVD on the kernel loop"):** the runtime registers
  the drive as a kernel device (`next` = `cdvd_next_event`, `poll` = `cdvd_poll`, µs ↔
  bus cycles) and installs a wait hook that blocks on `ps2k_wait_until(due)`. A blocking
  `sceCdSync` now completes at the exact due cycle while other threads run.
  `cdvd_drive_set_clock(us)` (new) resets the drive's clock when a kernel run starts.
- The game-name wrappers assume PLAN.md transform 6 binds the excluded asm units by
  symbol name. Their prototypes in the game differ (`s32` vs pointers); on i686 cdecl
  that is harmless, and transform 2 will unify them.
