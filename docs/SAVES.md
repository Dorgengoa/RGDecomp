# Saves: the game's memory card path, the card model, host save files

PLAN.md P4 ("Memory card") and P6 ("Saves and quality of life"). The pad / card HLE as a
whole is in [PADMC.md](PADMC.md); this file covers what the game does with the card, what
the model must answer, how saves live on the host, and `tools/saves/ps2card.py`.

Status 2026-10-12: audit done (section 1), every card state the game distinguishes is
covered by tests, including the game's own save code run on the model (section 2), host
writes are crash-safe with automatic backups (section 3), PCSX2 import/export works on
synthetic cards (section 4). Boot runs with RG_DATA (empty card, a save, unformatted, no card) behave as the
decomp says: section 5.

## 1. What the game does (audit of the decomp)

Sources: `game/src/main/file/Mc*.c`, `Save*.c`, `main/sys/McPollCardChange_372db0.c`,
`main/menu/McSetErrorResult_375890.c`, the title / normal / insmenu overlay save screens,
and the data in `game/src/main_data` (strings, sizes). Read-only.

### libmc calls

| Call | Who | What for |
| --- | --- | --- |
| `sceMcInit` | `SaveMcInitStatus_375ea0` (boot), `McPollCardChange_372db0` | -101 / -120 / -121 are accepted as "initialised" |
| `sceMcGetInfo(port, 1, &type, &free, &format)` | `McGetInfoStep_375640`, `McFormatStep_3736b0`, `McSaveStep_374110` (after a save), `McPollCardChange_372db0` (free / format NULL) | card check, free space, change detection |
| `sceMcGetDir` | `McSaveDirScan_3748c0` (`/BASCUS-97490LV5RG_??`, 50 entries), `McSaveSlotScanStep_374b00` (`/<dir>/*`, 6; `/<dir>/icon.sys`, 1) | slot list |
| `sceMcMkdir` | `McSaveCreateStep_375090` | -4 (exists) is accepted |
| `sceMcOpen` | create: icon.sys `0x202`, RG.ICO `0x203`; save: data `0x202`, icon.err `3`; scan / load: data `1` | |
| `sceMcWrite` / `sceMcRead` | 0x200-byte writes (icon.sys in one 0x3C4 write first); 0x800-byte reads | |
| `sceMcFlush` / `sceMcClose` | after every written file; the create step checks the function numbers (Flush 10, Close 3) | |
| `sceMcRename` | `McSaveStep_374110`: icon.sys -> icon.err before writing, back after; `SaveDirRenameJpToUs_373160` | |
| `sceMcChdir` | `SaveDirRenameJpToUs_373160` only | |
| `sceMcFormat` | `McFormatStep_3736b0` (after the "format?" prompt) | |
| `sceMcSync(1, ..)` | every step polls; `McEndSession_372d60` blocks (mode 0) | |
| `sceMcEnd` | `McPollCardChange_372db0`, `McEndSession_372d60`, `SaveMgrRelease_37bb70` | |

Never called by the game (declared, or only in the SDK units): `sceMcDelete`, `sceMcSeek`,
`sceMcGetEntSpace`, `sceMcSetFileInfo` (other than through Rename), `sceMcUnformat`,
`sceMcGetSlotMax`, `sceMcUdCheckNewCard`. The game cannot delete a save.

### Files on the card

| Card path | Size | Notes |
| --- | --- | --- |
| `/BASCUS-97490LV5RG_NN/` | | NN = slot 00..49 (`D_00463900` / `D_00463A00`) |
| `/BASCUS-97490LV5RG_NN/icon.sys` | 0x3C4 (964) | `SaveIconSysBuild_375d10`: "PS2D", title at +0xC0 (Shift-JIS, line break at the byte offset in +6), icon names at +0x104 / +0x144 / +0x184 = "RG.ICO" |
| `/BASCUS-97490LV5RG_NN/RG.ICO` | 13-14 KB, from the disc (`SaveIconFilesLoad_37bbd0` reads "RG.ICO" from an archive) | the 3D icon, one file for list / copy / delete |
| `/BASCUS-97490LV5RG_NN/BASCUS-97490LV5RG_NN` | 0x1BC00 (113,664) | `D_004658F8`; the slot scan reads only the first 0x800 (`D_004658F0`) |
| `/BASCUS-97490LV5RG_NN/icon.err` | 0x3C4 | exists only while an overwrite is in progress (below) |

The Japanese release's directories (`BISCPS-15102LV5RG_NN`, `D_004639E0`) are renamed to
the US names by `SaveDirRenameJpToUs_373160` (save-manager mode 10): chdir `/`, rename the
directory, chdir into it, rename the data file, chdir `..`.

### The save manager (`D_004831D0`, modes = `SaveModeDispatch_375df0`'s table)

| Mode | Step | Does |
| --- | --- | --- |
| 0 | `McGetInfoStep_375640` | GetInfo on the current port; result -1 sets formatted, -2 clears it, < -10 means no card; up to 10 tries if not formatted / no card |
| 1 | `McGetInfoPollThrottled_3755f0` | idle mode: mode 0's step every 5th frame |
| 2 | `McSaveCreateStep_375090` | Mkdir, icon.sys, RG.ICO (a new save; mode 4 follows) |
| 3 | `McSaveDirScan_3748c0` + `McSaveSlotScanStep_374b00` | list the 50 slots (below) |
| 4 | `McSaveStep_374110` | write the save (below) |
| 5 | `McLoadStep_373890` | open, read 0x800 at a time to 0x1BC00 or a 0 read, close, deserialise |
| 6 | `McFormatStep_3736b0` | Format, then GetInfo |
| 10 | `SaveDirRenameJpToUs_373160` | JP -> US directory names |

Per-port record (+0x4A4 + port x 0x1C): `f0` card present, `f4` type, `f8` formatted,
`fC` "card changed format", `f10` free KB, `f14` last result, `f18` "changed" (1 after a
-1 or any non-zero result). `McCardIsReady_376280(rec, 1)` = present, type 2 **and f18 == 0**:
the load and save steps refuse a card whose last GetInfo was not 0, so after a card is
(re)inserted one more GetInfo is needed (the save screens show status 8 until then).

**A save** = mode 2 then mode 4 for an empty slot, mode 4 alone to overwrite
(`normal_TransSaveSlotListConfirm_519c60`: a slot that is "broken" or "no space" cannot be
picked; "bad data" can be overwritten). Mode 4 (`McSaveStep_374110`):

1. rename `icon.sys` -> `icon.err` (the slot reads as broken from here on);
2. open the data file `0x202` (create, write, **no truncate**: the size is fixed), serialise
   (`McSaveSerialize_375c60` -> `SaveDataSerialize_3e6100`), store the save counter at +8,
   write 0x200 at a time, flush, close;
3. open `icon.err` mode 3, write the new icon.sys (0x3C4), flush, close;
4. rename `icon.err` -> `icon.sys`; GetInfo, which must answer 0 (else status 0xC).

The game's own crash protection is the icon.err rename: a save interrupted anywhere
between 1 and 4 leaves a slot without icon.sys, which the scan reports as broken. The
game has no way to repair or delete it; on a PS2 the player deletes it in the browser.

**The slot scan** (mode 3), per slot NN: not in the root listing -> empty; GetDir
`/<dir>/*` (waits for function 13); GetDir `/<dir>/icon.sys`: no entry or size != 0x3C4 ->
broken; open the data file (error -> broken), read 0x800, close; `SlotRecordStore_3e52f0`
checks the header (below): code 0 or 10 -> valid, else bad data. After the 50 slots, every
empty slot gets "no space" when the card is formatted and has less than
`SaveCalcSizeKB_3735e0` = ceil(0x1BC00 / 1K) + ceil(RG.ICO / 1K) + 3 + 2 KB left
(111 + icon + 5).

**Free space**: `McCardCheckFreeSpace_376220(rec, kb)` = 1 no PS2 card, 2 formatted and
free < kb, 0 otherwise (an unformatted card counts as 0: the game offers to format it).
`SaveCardHasFreeSpace_37b8c0` / `SaveCheckCardFreeSpace_37b980` wrap it with
`SaveCalcSizeKBCurrent_37b920`.

### Results and messages

`McSetErrorResult_375890(mgr, libmc result)` writes the status word (+0x4F0) the UI
reads; nothing clears it but the next GetInfo / Create / Load (`SaveMgrClearResult_3759d0`):

| libmc result | Status | UI (normal_TransSave* / title_TitleLoad*) |
| --- | --- | --- |
| -2 unformatted | 7 (and formatted = 0) | "not formatted, format?" -> mode 6 |
| -3 full | 4 | "not enough free space" |
| -1, -11..-19, -40..-59, -70..-79 | 8, or **6 when in mode 4** (and present = 0) | 8: "no memory card" / removed; 6: removed during the save |
| -4 .. -8 | unchanged | (a missing file: the step marks the slot broken itself) |
| issue failures, bad state | 0xC (set by the steps) | generic failure |
| load read / close failure | 2 | load failed |

The save screens stop on status 5, 6 or 8 (`normal_TransSaveNewFileTickCb_519020`,
`normal_TransSaveWriteTickCb_518c60`), and on `SavePortCardIsReady(1) == 0` every frame.

**The boot check** (`title_TitleStateCardCheck_4ed3c0`, title state 14): for slot 1 then
slot 2, mode 0 then mode 3; `title_D_004F19F0[port]` gets the port record and the number of
valid saves. Then, with need = `SaveCalcSizeKBCurrent`:

- either card usable (`McCardCheckFreeSpace` = 0: present and enough room, or unformatted),
  or a valid save on either -> no message, on to the title (state 0x3E9 -> 4);
- else both = 1 (no card) -> message **0xC9**; both = 2 (full) -> **0xCB**; mixed ->
  **0xCA** with the size in KB. Each waits for a yes / no: retry (back to state 0) or
  continue without saving.

The title's Continue entry is enabled when either card holds a valid save
(`title_TitleAnySaveExists_4ed380`; the "SaveExists" lockstep symbol).

**Card change** (`McPollCardChange_372db0`, title only): every 10 calls, alternating ports,
Init / GetInfo(NULL free, NULL format) / Sync / End; returns 2 when a PS2 card appeared, 1
when one went away.

### The save file

`SaveDataSerialize_3e6100` (header built by `SaveHeaderBuild_3e5520`):

| Offset | Field |
| --- | --- |
| +0x04 s16 | 0x25 (`D_004658D8`; anything else: error 9 = bad data) |
| +0x06 s16 | 0 (`D_004658E0`; a mismatch sets error 10 but still loads) |
| +0x08 s32 | save counter (`SlotRecordFindLatestMaybe_3e4c90` + 1, stored by mode 4) |
| +0x10 s64 | payload length = total - 0x50 |
| +0x20 | MD5 of the payload [0x50, 0x50 + length) |
| +0x30 s64 | 0x300: length of the summary covered by the next digest |
| +0x40 | MD5 of [0x50, 0x350): the slot list's summary (location, play time, party) |
| +0x50.. | summary (to 0x350), zero to 0x800, then the chunk stream |

From 0x800 a chunk stream (`SerialWriteChunkHeader_370e50` / `UnpackWordTriple_370d70`):
a container chunk of kind 0 holding chunks 1, 2, 3, 8, 0xE, 0xF written by the six
sub-objects; zero padding to 0x1BC00. `SaveHeaderValidate_3e5100` checks the lengths, the
version, then the summary digest (the scan: `SlotRecordStore_3e52f0` passes only that one,
error 0xB) and, when loading, the payload digest (error 0xC). `SaveDataDeserialize_3e5c30`
then walks the chunks (errors 3..6). The MD5 is standard (`Md5Init_36a6b0` constants,
little-endian digest in `Md5Final_369110`); `ps2card.py check` verifies both digests.

## 2. The card model against the game

What `src/ps2/padmc/mccard.c` answers, per state the game distinguishes, and the test that
holds it (tests/padmc, label `padmc`):

| State | Model answer | Game outcome | Tests |
| --- | --- | --- | --- |
| no card | GetInfo -12, type 0; every op -12 | record present = 0, CheckFreeSpace 1, boot message 0xC9 (both slots), scan status 8 | `mc_card_states`, `mc_game` |
| unformatted | GetInfo -2, type 2, format 0, free 0; file ops -2 | CheckFreeSpace 0 (no boot message), scan status 7, mode 6 formats, GetInfo then 0 | `mc_card_states`, `mc_game` (game_full part) |
| fresh / re-inserted card | first GetInfo -1, then 0 | not ready for load / save until the second GetInfo (as retail) | `mc_card_states`, `mc_game`, `mc_errors` |
| full | free from 1 KB clusters (PADMC.md); -3 on the write that does not fit | "no space" slots, CheckFreeSpace 2, boot 0xCB / 0xCA, save status 4 and the slot left broken | `mc_full`, `mc_exact_fit` (exactly SaveCalcSizeKB free: the save fits), `mc_game` |
| existing save | listing in creation order (icon.sys, RG.ICO, data), sizes, times | slot valid, Continue enabled, load reads 0x1BC00 | `mc_save_cycle`, `mc_game` |
| corrupt | bytes as stored, short reads, -4 for missing files | icon.err only / wrong icon.sys size / no data -> broken; bad digest / short data -> bad data | `mc_corrupt`, `mc_game` |
| write failure mid-save | `mccard_inject_fault`: the Nth op fails; -12 also ejects | status 6, slot broken (icon.err); the host keeps the previous save whole, a backup of it exists, restoring it makes the slot valid | `mc_write_fail`, `mc_game` |
| process crash mid-save | nothing written until flush / close | the previous save survives | `mc_crash_write` -> `mc_crash_read` |

The real cost of a save on the model is 3 (directory, 5 entries) + 1 (icon.sys) + RG.ICO +
111 (data) + 1 when the root directory grows = at most `SaveCalcSizeKB_3735e0`, so a card the
game judges big enough always takes the save (`mc_exact_fit`).

`mc_game` compiles the game's own McGetInfoStep, McSaveCreateStep, McSaveStep,
McSaveDirScan + McSaveSlotScanStep, McLoadStep, McFormatStep, McSetErrorResult,
McCardCheckFreeSpace, McCardIsReady, SaveCalcSizeKB, McPollCardChange and the slot / path
helpers from `game/` (skipped when not ingested) and drives them the way
`SaveModeDispatch_375df0` does (one step per frame; 1 = done; other non-zero ->
McSetErrorResult). Only the serialiser and the header check are stubs (a synthetic save
with a checksum in place of the MD5). It covers the boot check, create + save + scan +
load, overwrite, the card pulled mid-overwrite (status 6, broken slot, restore from the
backup), bad data, a full card (no-space slots, status 4), unformatted -> status 7 ->
format, and card-change detection (1 on removal, 2 on insertion).

## 3. Host side

```
<saves>/                         RG_SAVES, --saves, else "saves"
  card1/                         the card in slot 1: PS2 directories as host directories
    BASCUS-97490LV5RG_00/icon.sys, RG.ICO, BASCUS-97490LV5RG_00
  card1.card                     metadata: formatted, creation order, attributes, times
  card1.txt                      generated index: directory, modified, KB, icon.sys title
  card2/, card2.card, card2.txt  slot 2 (present only if card2/ exists, by default)
  backups/card1/BASCUS-97490LV5RG_00/2026-10-12_181502/   previous versions (newest last)
```

Earlier builds used `slot0` / `slot1`; they are renamed to `card1` / `card2` on load.
`card1.txt` looks like:

```
# Memory card slot 1 (card1/). Written by the port on every change; edits are lost.
# free 7861 KB of 8000 KB
# directory                        modified (card clock)  size     title (icon.sys)
BASCUS-97490LV5RG_00               2006-01-31 12:03:10     135 KB  Rogue Galaxy / Rosa
```

**Crash-safe writes.** A file opened for writing is held in memory (saves are 113 KB);
`sceMcFlush` / `sceMcClose` write `<file>%~tmp` and rename it over the file (MoveFileEx
REPLACE_EXISTING | WRITE_THROUGH on Windows). The metadata and index files are written the
same way. A killed process therefore leaves every host file either old or new, never
half-written; stale `%~tmp` files are deleted on the next load (`%` is always escaped in
card names, so no card name can end that way). Game-visible behaviour is unchanged (sizes,
free space and listings follow the writes as before). Pulling the card (`mccard_eject`, or
an injected -12) drops writes not yet flushed, like a card pulled before mcman flushed.

`durable` (config, env `RG_MC_DURABLE=1`) also forces each committed save file to the
disk before the rename, which survives power loss too. It is off by default: on this
machine's B: drive one forced flush costs 100-700 ms, during which the game thread waits
inside the card call (a save commits 3 files). Without it the old file stays intact on a
process crash; on a power cut a just-renamed file can come back empty on some file
systems, which the backups cover.

**Backups.** Before the first change to a save directory that holds a finished save
(icon.sys plus at least two other files, none of them open for writing) the directory's
files are copied to `backups/card<N>/<dir>/<YYYY-MM-DD_HHMMSS>[_NNN]/` (written as
`<name>%~tmp` and renamed, so a snapshot is complete or absent), unless they equal the
newest snapshot. With the game's save sequence that is exactly one snapshot per
overwrite, holding the save being replaced (the create of a new save and the first save
into it take none). Formatting a card snapshots every save on it first. `backup_keep`
(default 5, < 0 = off) newest snapshots are kept per directory; `backup_root` moves them.
Restore with `ps2card.py restore NAME` (below) or by copying the files back while the game
is not running; a broken slot (icon.err) becomes valid again.

**Slots and environment.** `RG_MC_SLOT1` / `RG_MC_SLOT2` = `auto` (a formatted empty card
when the folder is missing; slot 1 default), `ifexists` (slot 2 default), `none`,
`unformatted`. `mccard_inject_fault(port, n, result)` makes the n-th card operation fail
(tests; a host "pull the card" action can use it with -12).

## 4. tools/saves/ps2card.py

Standard library only; written from public descriptions of the card format (no emulator
or GPL code).

```
python tools/saves/ps2card.py list  Mcd001.ps2                 # or a folder card, or saves/card1
python tools/saves/ps2card.py import Mcd001.ps2 [--save BASCUS-97490LV5RG_03] [--slot 2] [--force]
python tools/saves/ps2card.py export Mcd002.ps2 [--format] [--save ...] [--force]
python tools/saves/ps2card.py format blank.ps2 [--no-ecc]
python tools/saves/ps2card.py verify Mcd001.ps2
python tools/saves/ps2card.py check  saves/card1/BASCUS-97490LV5RG_00
python tools/saves/ps2card.py restore BASCUS-97490LV5RG_00 [--list | --snapshot 2026-10-12_181502]
```

`--saves` / `$RG_SAVES` and `--slot` select the port's card; `--save` takes names or globs
(default `BASCUS-97490LV5RG_*`). Import keeps the card's creation order, times and modes
(written into `card<N>.card`); replacing a save needs `--force` and backs the old one up
first. Export writes into an existing formatted image (or `--format` a new one) or a PCSX2
folder card (save folders as plain folders; PCSX2's `_pcsx2_*` files are skipped and left
alone). Run import / export / restore with the game closed.

**Image format as implemented.** 16,384 pages of 512 bytes (+16 spare: 12 ECC bytes, 4
zero) = 8,650,752 bytes, or 8,388,608 without spare. Cluster = 2 pages, erase block = 16.
Superblock at cluster 0 ("Sony PS2 Memory Card Format ", "1.2.0.0", 512 / 2 / 16, 8192
clusters, alloc_offset 41, alloc_end 8135, root at relative 0, backup blocks 1023 / 1022,
indirect-FAT list {8}, no bad blocks, type 2, flags 0x52). FAT: 32 clusters (9..40) reached
through cluster 8; entries relative to alloc_offset, bit 31 = used, 0xFFFFFFFF = end,
0x7FFFFFFF = free. Directory entries are 512 bytes (mode, length, created, first cluster,
the "." entry's back-reference to its entry in the parent, modified, attr, name at 0x40);
modes 0x8427 directory, 0xA426 "..", 0x8497 file; a deleted entry clears mode bit 0x8000
and its slot is reused. ECC: per 128-byte chunk, column parity (6 bits, inverted, 0x77
mask) and the two 7-bit line parities over the chunk index of odd-parity bytes; the tests
prove it corrects any single-bit error.

**Not verified against a real card**: the two PCSX2 cards on this machine
(`Documents/PCSX2/memcards/Mcd00{1,2}.ps2`) are blank (all 0xFF, never formatted), so the
ECC bit layout, the superblock flags and the root's ".." mode could not be compared with
what PCSX2 / a PS2 writes. `verify` on a PCSX2-formatted card that holds a save will show
any ECC difference; until then, export into a copy of a card. Reading does not depend on
ECC.

Tests: `padmc.ps2card` (python -I tests/padmc/test_ps2card.py): ECC single-bit property,
format, add / list / remove with slot reuse and a fragmented chain, root directory growth,
full card, ECC damage detection, raw and ECC images, CLI export -> verify -> import with
times and modes, refusing without `--force` and backing up with it, folder cards, the
header check, restore. It leaves a card that `padmc.mc_pyimport` reads through the C model
(listing order, sizes, creation time, attributes).

## 5. Boot runs (RG_DATA, no input)

`build\saves-i686g-game.exe --headless --fields 1000..1750 --saves runs\<case>` with
`RG_DATA=data`, `RG_STATUS_EVERY=250`, `RG_STATUS_DUMP=0x004F19F0:0x40` (the
title's two port records, `title_D_004F19F0`) and a screenshot. 2026-10-12:

| Card in slot 1 (slot 2: none) | Port record slot 1 (present, type, formatted, free, result, valid saves) | What the title does |
| --- | --- | --- |
| empty (a new `card1/`, `auto`) | 1, 2, 1, 8000, 0, 0 | no message; logo movie from vbl ~250, title menu with NEW GAME selected |
| a save (synthetic, imported with `ps2card.py import`) | 1, 2, 1, 7861, 0, **1** | no message; the menu opens on **CONTINUE**: the game's own scan accepted the file (its header MD5, computed by `hashlib`, matched `SaveHeaderValidate_3e5100`) |
| unformatted (`RG_MC_SLOT1=unformatted`) | 1, 2, 0, 0, -2, 0 | no message (an unformatted card counts as usable), title menu |
| none (`RG_MC_SLOT1=none`) | 0, 0, 0, 0, -12, 0 | stops at message **0xC9**: "No memory card (8MB)(for PlayStation®2) found in either MEMORY CARD slot 1 or 2. At least 130 KB of free space is required in order to save game data. Begin the game anyway? Yes / No"; no movie (movie_frames 0) |

Slot 2's record reads present 0, result -12 in every run. The message gives the real
`SaveCalcSizeKB`: 130 KB = 111 + 14 (RG.ICO is 13-14 KB) + 5. No real save was
available (both PCSX2 cards on this machine are blank), so loading a real save is
untested; the synthetic one is only valid as far as the slot scan reads.

## 6. Open questions

1. **First GetInfo** after insertion = -1 (PADMC.md question 4). The game copes either way;
   it decides whether the save screen briefly shows status 8 after a hot swap.
2. **Free space on an empty card**: the model starts at 8000 KB; an image formatted by this
   tool has 8134 allocatable clusters. A PCSX2 trace of `sceMcGetInfo` free before / after a
   save settles both the empty value and the per-directory cost.
3. **ECC / superblock details** of real cards (section 4).
4. **Mode 10** (JP -> US rename): no caller found in the overlays yet; untested.
5. A broken slot can only be fixed outside the game (restore a backup, or delete the
   directory). A host UI for that is P6 work.
