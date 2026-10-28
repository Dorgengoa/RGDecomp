# Linking the game: `rg-game`

The whole game (6 images) + `overrides/` + `missing/` + every port library, as one i686
executable. State of 2026-10-12. Pinned to the published decomp `675c07fe`
(SNAPSHOT-CLEAN.md) since the re-pin of 2026-10-12; the work below was done on the interim
snapshot `b09ccfa1` (SNAPSHOT-INTERIM.md), whose function sources are identical.

**Result: `rg-game.exe` links** (0 undefined, 0 duplicate). Headless it boots through
crt0, all of MAIN's static constructors and `SysBootInit_1c2ee0` (pads, IOP heap, sound,
CD watch, GfxSysInit, game-data heap), reaches `MainLoop_1c2c10` and faults there on the
first field (see "Running").

```powershell
python tools\ingest.py            # the pin (below); --check to verify
cmake --build build\i686-windows --target rg-game  # from a vcvars x86 shell
$env:RG_DATA = "data"; build\i686-windows\rg-game.exe --headless --fields 300
```

## Switching the snapshot

`tools/ingest.py` carries the pin: `PIN_SOURCE` / `PIN_REV` / `PIN_TREE`. `ingest.py` with
no `--source/--rev` ingests the pin; `ingest.py --compare-tree REPO[@REV]` says whether
another copy has the pinned tree (then only `PIN_SOURCE`/`PIN_REV` change). To move to a
different tree: change the lines, re-ingest, then `ingest.py --check` lists every STALE
override; classify each one as below (DROP / REHASH / REPORT), rename `missing/UNBOUND.tsv`
rows whose symbol was renamed, and re-run the bindings lanes (`ctest -L bindings`).

**Re-pin to the published decomp `675c07fe` (2026-10-12, SNAPSHOT-CLEAN.md):** no function
source changed, so all 103 overrides stayed current (0 dropped / 0 re-hashed / 0 renamed),
`MainSinit_469180.c` stays in `missing/`, PORT_PROVIDED is unchanged, and 7 UNBOUND rows
were renamed to the snapshot's `func_<ADDR>` spellings. Two generic tool changes cover the
published layout (no per-function `asm/matchings/main/`, no splat yamls): protos reads MAIN's
listing from `asm/main.s`, and gen_overlay_registry reads the overlay layout from the
overlay data/bss listings. Link, test and boot results: SNAPSHOT-CLEAN.md.

## Ingest stages (new / changed for the interim snapshot)

Order: `int128, gccvarargs, vu0asm, vu0bind, asmexclude, ovlsyms, datareloc, protos,
dialect, devirt, spin, hwaccess`. 0 errors; a second run writes 0 files.

| Stage | What |
| --- | --- |
| `vu0bind` (portxform.py) | The d784320c de-asm writes VU0 code as mwcc intrinsics on bound registers (`#pragma vu0_mmi_reg_binding on`, `extern u128 v asm("vf4")`, `v5 = _vmul(v5, 0xE, v4, v4)`): 108 files, 467 bindings. Each binding becomes an lvalue on the VU0 model's register file (`rg_vu0.vf[N]`/`acc`/`q`); `include/port/vu0intrin.h` implements the 35 intrinsics with the model's VU arithmetic. mwcc writes the first argument in place even when the value is discarded (`_vmul(v4, ...);` in VecLengthSq_1cb470), so each intrinsic is a macro `((d) = rg_vbi_x((d), ...))`. Verified by the bindings `gamecop2` lane (64 checks, now run on the game C). |
| `datareloc` (tools/stages/datareloc.py, **new**) | MAIN data C for the host; see "Data layer". Writes `game/DATARELOC.tsv`. |
| `dialect` | + block-scope `static void f(void);` loses `static` (clang rejects it; FrameCalcWorldMatrix/FrameUpdateWorld). + **16-byte alignment of block-scope locals**: scalar arrays of >= 16 bytes and aggregate locals get `__attribute__((aligned(16)))` (EE frames are 16-aligned; the game hands `u8 sp20[0x190]` / `DBuff db` to code that moves qwords = `movaps`). 2,101 files. |
| `protos` | + a local declaration with a struct/128-bit by-value parameter is kept even when its calls are inside a macro body (StringVectorInsert_1a6240 `Alloc6240`). |
| `hwaccess` | + 7 reviewed mask sites and 2 leave rules for the de-asm'd C (DrawListEmitBucket `ADDR()`, ModelMeshBuildUnpackPkt, ViBufReset, VideoDecFlush, GsBuildImageUploadRefPkt): 103 rewrites in 40 files, census 0 unaccounted. |

Port headers: `include/eekernel.h` replaces the decomp's (`ExitHandler()` was
`__asm__("sync.l; ei")`; now `EIntr()`), `include/port/vu0intrin.h`. Game C++ gets
`-Wno-c++11-narrowing` (FontDrawText_26cdc0 brace-initialises a u64 bitfield from an s32).

## Data layer (`datareloc`)

data2c gives every MAIN `.data/.rodata/.sdata` span one C object (6,305 files). On i686 a
pointer is 32 bits, so data2c's `(u32)&Sym` words are link-time relocations already. The
stage handles the rest (counts = DATARELOC.tsv rows):

| Rule | Rows | What |
| --- | ---: | --- |
| `main-data-interior` / `main-data` | 1,780 / – | raw word pointing into a MAIN data object (D_0044AF90's string pointers 0x0045AD30.., 0x00459D88-style string tables) -> `(u32)((u8 *)&OBJ + off)`. Unaligned targets only into char/gap objects (`main-data-unaligned` 33 left raw). |
| `main-bss` | 42 | -> `data2c_main_bss + off` |
| `arena-data` / `arena-end` | 98 / 1 | raw overlay data/bss address -> the overlay's symbol + offset (`(u32)((u8 *)&factory_D_0050CF00 + 0x8)`: nearest label the overlay's C names, else `<ov>_seg`; NORMAL/INSECT overlap words by `ARENA_DATA_OWNER`, verified by content), valid for the arena manager and the native module table alike (2026-10-25, docs/OVERLAY.md section 8; was `data2c_overlay_load_base + off`). The arena end (retail `_end`, D_004461F4, read only by the natively bound asm sbrk) -> 0. Text-range non-entries (43) and odd/ASCII words (4) left raw (numbers, not pointers). |
| `arena-fn` / `arena-fn-import` | 252 / 39 | overlay function entry: the overlay's C function when one overlay defines it, else `func_<ADDR>` (an import trampoline the registry generates). |
| `main-fn` | 13 | f32-typed .sdata words that are MAIN function addresses (McGetInfoStep_375640 ...). |
| `retyped` | 18 | 17 f32 objects (PLAN hazard: "17 addresses typed as floats") + D_00480390 (s16 pairs) re-emitted as `u32[]` with the same bytes. |
| `microcode` / `micro-unsym` | 24 / 2 | VU microcode blobs: no relocation; data2c's `(u32)&IconStealthStep_202950` inside D_00441660 (a microcode word that equals a function address) reverted to the number. |
| `fn-number` | 22 | data2c's `(u32)&EntryPad_100000` / `&func_00200000` (flag bits 0x00100000 / 0x00200000 in the ActCfg, EvScript, gaiji, menu panel and NavCfg tables) and `&MpegNextPictureMaybe_110008` in D_00450480 (the u16 pair 0x11, 0x08) are numbers. D_0047D130 (the .text start) stays a relocation. Audit: `out/bringup-checkpoint/fnword_audit.py`. |
| `alias` | 580 | game code names an address inside a data2c object (`D_004803FC` in D_00480390, `D_0044B778` = `data2c_fragment_0044B778`): asm equate `D_x = OBJ + off`. |
| `code-in-data` | 2 | MAIN's first two static ctors are MIPS words inside D_00469140: bound to `missing/src/main/sys/MainSinit_469180.c`. |
| `gap-pad` | 155 | zero pads for bytes no data object owns, so offsets stay retail. |
| `hw-word` | 45 | EE register / scratchpad addresses in data (D_00445F20's DMA channel bases 0x1000x000, ...): **not relocatable**, reported. Only SDK code (port-provided) is known to read them. |

Every object is **writable** (const dropped: VuMicrocodeTableInitMaybe_152830 fills
`D_00449DD0`) and goes to COFF section `.data$rg<ADDR>` with its retail alignment (16/8):
the linker orders grouped sections by suffix, so **MAIN data is one contiguous image in
retail order and relative offsets** (checked on the map: 6,877 symbols, one constant
offset). That fixes code that reads across objects (ctor table end = `D_0046FD64`, the
8-byte `NA` view of the 4-byte `D_0047E010`). The link needs `/OPT:NOREF` (and
`/OPT:NOICF`: the game compares function pointers).

**MAIN bss** is `data2c_bss.c` rewritten as one 128-aligned top-level-asm `.bss` block
`data2c_main_bss` (0x00481080..0x004E9E80) with a global label for each of the 3,154 MAIN
bss names the corpus uses (+ `gEventContext`, `gSystemVm` from main.symbols.txt), so the
named view and the lifted overlay ctors' `RG_MAIN_BSS_PTR` are the same bytes.
**Overlay reservations** `data2c_overlay_reserve_1..7` are emptied (the arena owns that
memory). `D_00527020 / D_005273B8 / D_00528200 / data2c_overlay_load_base` are defined only
by the arena (the stage errors if data defines them).

## Overrides (194 at the switch -> 102)

| Class | n | Files |
| --- | ---: | --- |
| DROP | 92 | 88 "C port on the VU0 model" (Vec*/Mat*/Mtx*/Frame*/Model*/Motion*/Tri*, ..., VertsPackQuantized, FixCameraRecInit): the snapshot has them as C on bound VU registers, which `vu0bind` compiles; ABI kinds checked against each override (equal, except VecLengthSq/VecLengthSqXZ `f(ii)` vs `f(i)`: the extra parameter is unused, protos fixes the callers). Vif1IntcHandler, SoundVblankIntrHandler, MovieDmacHandler, MovieVblankHandler: game C + `include/eekernel.h`. The bindings lanes now compile the game file when the override is gone (`tests/bindings/CMakeLists.txt`) and pass (gamecop2 64, platform 90 checks). Kept in `out/overrides-dropped/`. |
| REHASH | 4 | CameraObjCtor_177430.cpp (game now spells UnitVector via a vf0 binding: same stores), MoviePlayerShutdown_1d56c0 (a removed decl), MoviePlayerStart_1d5b50 (dialect alignment), PadReadData_184df0 (validation agent's 32-byte buffer; re-ported the new `aligned(16)` onto it) |
| REPORT (re-ported, kept) | 1 | GfxVblankStartHandler_15df20: the de-asm C takes no argument and calls `D_004810D0()` with none; retail passes `$a0` (the cause) through. The platform lane caught it (`cb_cause`). |
| unchanged | 97 | 92 asm-excluded SDK/L5 ports + 5 C overrides, hashes current |

`missing/`: NameTableNodeSetImage_15a640 dropped (the snapshot defines it,
`src/main/gfx/`; the platform lane now tests the game C); `MainSinit_469180.c` added.

## Providers (`overrides/PORT_PROVIDED.tsv`)

No libc/SDK *library* function became C in the snapshot (the 105 symbols that left
EXCLUDED.tsv are all game code). Game C files a port module provides instead are listed in
`overrides/PORT_PROVIDED.tsv` and not compiled (`tools/gamesrcs.py`):

| File | Provider | Rule |
| --- | --- | --- |
| `sdk/iSetAlarm.c` | src/sce/kernel | SDK hardware/kernel functions keep the port provider (the C jumps into kernel RAM) |
| `sdk/sceFsReset.c` | src/sce/sif | same (FILEIO state is the HLE's) |
| `sdk/atoi.c` | host CRT | unsuffixed libc names bind to the host CRT (BINDINGS.md) |

The other game SDK C (`sceVu0UnitMatrix`, `sceVu0Normalize`, `kill`, `_sceRpcGetFPacket2`,
...) has no port twin and is linked as is. `src/crt` gained `Atan2_129148` / `Acos_129130`
(libm double wrappers; protos now binds their callers' double arguments).

## Unbound symbols (`missing/UNBOUND.tsv`)

The link resolves everything; 89 symbols (2026-10-12: 107 at the re-pin, 98 after the 7 missing-game-code functions were ported into `missing/`, 94 after BRINGUP.md's checkpoint fixes: MtxMulAffine_13d1d0 override, datareloc `fn-number`, protos `text-alias`; 89 after the L5 overrides AabbProjectScreenBounds_13c4f0, GsPktSetXYZPixelVec_13ef70, GsPktSetSTVec_13ecc0, VecFtoi4_13e2e0, GsPktAddDmaCallTag_13f1f0) resolve to **fatal stubs** generated by
`tools/gen_unbound.py` (a call prints `rg-game: UNBOUND <sym> (<class>) called` and
aborts; data rows are 64 zero bytes). Delete a row when something real defines it.

| Class | n | Examples |
| --- | ---: | --- |
| sdk-internal | 41 | KCopyBody_*, kFindAddress, InitTLB, scePrintf, _sceSifLoadElfPart, FioSemaCreate: called only from game SDK C the port replaces higher up |
| library-internal | 29 | MSL iostream/string (Filebuf*, Streambuf*, String*, Srget, Ungetc, Fseek, Decimal*), libmpeg MpegMc*/MpegParse* |
| kernel-ram-data / -code | 18 / 3 | D_8007xxxx, func_0743C8 ...: EE kernel RAM touched by the SDK kernel patch |
| data2c-entry | 0 | (func_00200000 was a number: datareloc `fn-number`; the other 6, CharaFindNextLevelRowFromCur_3ab200, LiveTalkStep_321240, ModelObjExUpdate_1b02c0, TaskStepJudgeObject_3135c0, func_003AB220/240, now have C in `missing/`) |
| l5-no-override | 0 | (all six now have overrides: MtxMulAffine_13d1d0, AabbProjectScreenBounds_13c4f0, GsPktAddDmaCallTag_13f1f0, GsPktSetSTVec_13ecc0, GsPktSetXYZPixelVec_13ef70, VecFtoi4_13e2e0) |
| interior-entry | 0 | (func_207A90: BRINGUP fix 6; func_3930D0: `missing/src/main/ui/UiNineSliceSpritesLayoutMaybe_3930d0.c`) |
| text-address-data | 0 | (D_002931A0 = UiTextElemInit_2931a0: protos `text-alias`) |

`tools/link_readiness.py --build <dir>` (game objects only, before providers):
1,141 unresolved = overlay-data 459 (arena), excluded-asm:sdk 300 / :library 79
(providers + stubs), overlay-import 241 (registry), data-missing 21 / other 12 /
main-address-alias 9 (stubs, missing/, arena), port-runtime 16, crt 4; duplicate-def 0.

## The executable (`cmake/game_link.cmake`)

`rg-game` (EXCLUDE_FROM_ALL): `src/game/rg_game_main.c` + the stubs + every
`rg_game_<image>` object + `rg_ovl_registry_game` + `rg_trace_symtab_game`, linked with
runtime, movie (runtime/game/core), overlay bind/arena/core, trace, sce/*, ps2/*, crt, vu0,
host. `/LARGEADDRESSAWARE:NO` (DMAC bit 31), `/STACK:8M`, `/OPT:NOREF /OPT:NOICF`, `/MAP`
(`rg-game.map`). `rg_game_main.c`: `rg_movie_runtime_attach()`, then
`rg_runtime_set_service_hook(rg_ovl_service_init, &rg_ovl_generated_registry)`, the trace
symtab + `RG_TRACE_*`, `rg_runtime_init`, run; `rg_game_entry` -> `Main_15e700`. An
unhandled-exception filter prints EIP, the fault address and the image words on the stack
(resolve them with `rg-game.map`). `RG_GAME_FORCE_UNRESOLVED=ON` links with
`/FORCE:UNRESOLVED` for diagnostics only.

Overlay generator: labels now see ovlsyms-prefixed names (`normal_D_00527020`), which
fixes `rg-ovl-real-tests` (undefined `_normal_D_00527020`, `_factory_D_00510010`: the
arena had dropped every bss label only C uses); `RG_OVL_DATA2C` defaults to the snapshot's
own `config/data2c.json`.

## Running (headless, `RG_DATA=data`)

Reached, in order (each item was a crash fixed on the way): the static ctors (233 entries:
code-in-data ctors, contiguous ctor table, writable data, 16-aligned locals), `Main_15e700`
-> `SysBootInit_1c2ee0` (pad open, IOP heap, sound init/RPC/SPU, CD disk watch, sys tick
thread, `GfxSysInit_15dd20` + `GfxSetVideoMode_1451f0` through the port's libgraph, the
game-data and menu-resource heaps, CdDatArchiveOpen file loads through the CDVD HLE), then
`MainLoop_1c2c10`.

**Now (2026-10-12, docs/BRINGUP.md):** the heap shortfall is fixed: crt_heap.c is retail's
newlib malloc, with heap addresses equal to a PCSX2 probe. The title overlay loads, the
title movie plays and the title menu is drawn. With the golden input, NEW GAME loads
NORMAL and reaches the opening story screen with no fault in 6000 fields. The thirteen
fixes on the way, and the first lockstep divergence (vbl 80: there is no EE cost model),
are in BRINGUP.md.

## Open items

- `hw-word` data (45): DMA channel base tables etc. hold EE register addresses; any game
  code that dereferences them needs a hwbus spelling.
- `arena-text-interior` (46) words stay raw (overlay jump-table-like words in MAIN data).
- Adjacent-object reads are now correct inside MAIN data, but not across MAIN data and
  bss, nor between overlay data and MAIN.
