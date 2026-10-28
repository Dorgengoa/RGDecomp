# Overlays: how retail loads them, and the port's overlay manager

PLAN.md P2 "Overlay manager" and transform 7 "Overlay data".

| Path | What |
| --- | --- |
| `src/native/ovl/` | **the native module table** (what a native-only rg-game links, section 8) and the shared interface `ovl.h` |
| `src/ps2/overlay/ovl.[ch]` | the arena manager: registry binding, load/switch, address map, resolvers, unknown-address records (`ovl.h` forwards to src/native/ovl) |
| `src/ps2/overlay/ovl_asm.h` | helpers for the generated sources: asm symbol spelling, `RG_OVL_ARENA_PTR`, `RG_MAIN_BSS_PTR`, the `RG_OVL_TRAMPOLINE` import thunk (i686) |
| `src/ps2/overlay/ovl_bind.c` | game-facing binding `OverlayLoadFile_100410`, and `rg_ovl_service_init` (bind + hwbus resolver) |
| `tools/gen_overlay_registry.py` | the registry generator (build time) |
| `tools/ovl_lift.py` | lifts the overlays' MIPS static initializers to C |
| `tools/stages/ovlsyms.py` | ingest stage: `<ov>_` prefix on each overlay's own data/bss names |
| `overrides/src/main/sys/SysCalcFreeHeapMaybe_15e1d0.c` | override (link-time address used as a number) |
| `tests/overlay/` | `ctest -L overlay` (26 tests: 18 + the native module table's 4 + 4 controls) |

## 1. Retail: how overlays are loaded, entered, switched and unloaded

### The files and the header

Seven MWo3 files in `BIN/`, all loaded at **0x004E9E80**, header included, so
`vram = 0x004E9E80 + file offset` and `.text` starts at 0x004E9EC0. LAUNCHER and VIEWER
are 256-byte nop stubs that retail never loads (see the mode table below).

| off | field | off | field |
| --- | --- | --- | --- |
| +0x00 | `"MWo3"` | +0x14 | bss size |
| +0x04 | id (viewer 1, title 2, insmenu 3, launcher 4, normal 5, factory 6, insect 7) | +0x18 | `.ctors` start |
| +0x08 | load address 0x004E9E80 | +0x1C | `.dtors` start (= `.ctors` end) |
| +0x0C | text size (includes the 0x40 nop pad `<ov>_entry`) | +0x20 | name, `"title.bin"` |
| +0x10 | data size | | file size = 0x40 + text + data |

| overlay | loader index | id | text | data @ | data | bss @ | bss | end | .ctors |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| TITLE | 2 | 2 | 0x7540 | 0x004F1400 | 0x500 | 0x004F1900 | 0x280 | 0x004F1B80 | 4 @0x004F18A0 |
| INSMENU | 6 | 3 | 0xF8C0 | 0x004F9780 | 0xA00 | 0x004FA180 | 0x180 | 0x004FA300 | 2 @0x004FA140 |
| NORMAL | 3 | 5 | 0x3AE40 | 0x00524D00 | 0x2300 | 0x00527000 | 0x1200 | **0x00528200** | 17 @0x00526F60 |
| FACTORY | 4 | 6 | 0x215C0 | 0x0050B480 | 0x4880 | 0x0050FD00 | 0xF00 | 0x00510C00 | 22 @0x0050FC50 |
| INSECT | 5 | 7 | 0x39C40 | 0x00523B00 | 0x2300 | 0x00525E00 | 0x280 | 0x00526080 | 17 @0x00525D60 |

The generator derives every one of these from the snapshot (yaml + data asm, the
`link_overlay.py` ctor rule) and, given `--bin`, checks them against the retail headers
and the retail `.data` bytes: 5/5 identical.

### The load path (MAIN, all C except the two asm library units)

- **`MainLoop_1c2c10`**: calls `OverlayLocateFiles_1c3300` once. Then, per mode
  `D_0047E224`:
  - mode 0: `OverlayLoad_1c3210(6)` INSMENU if `SysModeMsgIsInsMenu_1c6970`, else `(3)` NORMAL;
  - mode 1: `(2)` TITLE;
  - mode 2: `(1)` LAUNCHER; default `(0)` VIEWER.

  It then calls the mode's **init** `D_0047E230[mode](D_004A3EF0)` and loops on its
  **step** `D_0047E238[mode]()`; **exit** is `D_0047E240[mode]`. Mode 0's are MAIN
  functions (`FUN_001f5d80`, `FUN_001f5cf0`, `GameSessionShutdown_1f5bf0`). Mode 1's are
  TITLE's: `title_TitleSessionInit_4f0cb0`, `title_TitleFrameStep_4f0b20` and
  `title_TitleSessionShutdown_4f0820`. The tables are 2 entries long, followed by
  `-1, -1`, so modes 2 and up (LAUNCHER, VIEWER) are dead in retail.
- **Other loads:**
  - `FactoryModeUpdate_27db40` loads FACTORY (4) in phase 2 and NORMAL (3) in phase 201;
  - `InsectBattleModeUpdate_27e0d0` loads INSECT (5), then INSMENU (6) or NORMAL (3);
  - `GameSessionShutdown_1f5bf0` loads NORMAL (3);
  - `CdDiscSelect_1c3090` switches the disc row `D_0048155C` and re-runs
    `OverlayLocateFiles_1c3300`.
- **`GetLoadedOverlayId_1c3200`** (`D_0047E254`, initially -1) gives the loader index.
  It is read by 11 MAIN functions: `TargetSlotShow/Hide`, `EvCmdMenuInsectResultOpen/Close` and seven
  `InsectBattle*` (e.g. `InsectBattleGetPromptResult_319500`), to branch on the resident overlay (e.g. `== 3`, NORMAL).
- **`OverlayLocateFiles_1c3300`**: for each of the 7 paths `D_0044AF90[disc][i]`, it
  strips the device and calls `FileCdSearchLocked_180360`. The resulting LSNs go into
  `D_004A6F80[7]`, which `OverlayCdSeek_1c32b0` uses to `sceCdSeek` ahead of a load.
- **`D_0044AF90[3][7]`** (.rodata) holds the path strings at 0x0045AD30 + 0x20·k:
  rows `cdrom0:\BIN\`, `cdrom1:\BIN\`, `host0:BIN/`; columns (= loader index) VIEWER,
  LAUNCHER, TITLE, NORMAL, FACTORY, INSECT, INSMENU.
- **`OverlayLoad_1c3210(i)`**:
  1. `OverlayCdSeek(i)`; returns 1 if i is outside 0..6;
  2. `while (!OverlayLoadFile_100410(D_0044AF90[disc][i], D_0047D134[0])) {}`, where
     `D_0047D134[0]` = `&data2c_overlay_load_base` = 0x004E9E80;
  3. `D_0047E254 = i`; return 0.

  **There is no "already loaded" check**: loading the resident overlay re-initialises it.
- **`OverlayLoadFile_100410(path, load)`** (asm, crt0/MSL band):
  1. `n = FileReadAll_1004b0(path, load)`: FILEIO `sceOpen` / `sceLseek` ×2 / `sceRead` /
     `sceClose`, the WHOLE file over the arena; `n <= 0` → return 0;
  2. `OverlayLoadNotifyStubMaybe_100400(load)` (empty);
  3. `FlushCache(0)`, `FlushCache(2)`;
  4. `if (hdr+0x14) memset(load + n, 0, bss)`: bss starts right after the file image;
  5. `RunStaticCtors_100df0(hdr+0x18, hdr+0x1C, 0, 0)`: calls every word of `.ctors` in
     ascending order, then `EhRegisterFragmentStubMaybe_1026b0(0, 0)`;
  6. return 1.

### Entry, switch, unload

- **No entry point.** Nothing jumps to the overlay after loading. `<ov>_entry`
  (0x004E9EC0, 0x40 bytes) is the nop pad at the section origin (memory note
  `overlay-entry-pad`). MAIN reaches overlay code in three ways:
  1. **Fixed addresses**: `jal func_4F6AB0` and similar. **206 distinct names** in 157
     MAIN files. Each is an absolute in the decomp lcf (`func_4F6BF0` is the one lcf
     name no compiled MAIN file uses). Among them are 19 one-line MAIN tail-call thunks
     (`FactoryMenuIsActiveThunk_4ec3e0`, `ShopMenuIsOpenThunk_50ab00`, ...).
  2. **MAIN data slots holding overlay function addresses**: the mode tables above, plus
     vtables and handler tables that live in MAIN's `.data` but belong to an overlay.
     `factory_FUN_004ec5e0` installs `D_0047CD30`/`D_0047CD50` (FACTORY), and the INSECT
     ctors install `D_0047CE58`…`D_0047D120`. data2c (decomp d784320c) symbolizes
     **88 slots → 69 names** (FACTORY 21 names, INSECT 45, TITLE 3), plus
     `data2c_overlay_load_base`: the "89 references".
  3. **Callbacks** that overlay code stores into MAIN structures at run time (state
     machines, menus). On the port these are plain host function pointers.
- **Overlay code → MAIN**: direct `jal`s to MAIN functions, absolute MAIN data, and
  **`$gp`-relative MAIN small data**. The overlays are linked against MAIN's gp
  0x00485170, and their own small data was linked INTO MAIN's `.sdata`/`.sbss`:
  - every overlay TU's `ios_base::Init` object and its RegisterGlobalObject node are at
    0x00484xxx (MAIN `.sbss`);
  - FACTORY's part-path tables are inside `D_00480390`.

  No relocation happens at load.
- **Switch = load the next overlay over the arena.**
  - No destructors run: every `.dtors` list is empty (header +0x1C points at a single 0).
  - The new file overwrites text and data, and bss is zeroed. Memory between the new
    overlay's bss end and 0x00528200 is not touched, so it keeps the previous overlay's
    bytes.
  - **Static initializers** (62, all compiler `__sinit`s):
    1. construct each TU's `ios_base::Init` and `wios_base::Init` (MAIN `.sbss`);
    2. **register their destructors** with `RegisterGlobalObject_100dc0` (push onto
       MAIN's chain at `D_004853D0`);
    3. construct the overlay's static objects: `SysMsgInit`, `MemStackCtor`,
       `ConstructArray`, `UiSelFrameReset`, `ScreenFadeBlockInit`, and FACTORY's
       part/belt/floor tables (one 1650-instruction initializer);
    4. copy a few gp words.
  - **Hazard:** every reload pushes the SAME nodes again, so the chain becomes cyclic.
    Retail only walks it in `DestroyGlobalChain_100d60` (`Main_15e700` after
    `MainLoop_1c2c10` returns, i.e. never). A port binding of `DestroyGlobalChain` must
    not walk it after an overlay reload.

### Memory around the overlay

- **Arena: 0x004E9E80..0x00528200 (0x3E380 bytes).** That is the largest reservation,
  NORMAL's 0x40 + text + data + bss. MAIN's ELF carries one empty LOAD segment per
  overlay, plus a 9th segment at 0x00528200.
- **The heap starts at 0x00528200 regardless of the resident overlay.** crt0 does
  `SetupHeap(0x00528200)` (rg_runtime.h); `SysCalcFreeHeapMaybe_15e1d0` computes
  `0x2000000 - 0x2000 - 0x30000 - 0x528200`.
- **The gap after a smaller overlay's bss is unused padding.** Nothing allocates from it:
  no MAIN code addresses 0x004E9E80+ by number apart from the names in §2.

## 2. MAIN → overlay address references (census, naming 2efa6b43 + data2c d784320c)

| Kind | Count | Port handling |
| --- | --- | --- |
| `func_XXXXXX` / `FUN_004efc40` calls in MAIN C | 206 names | generated trampolines → resident overlay |
| data2c pointer slots | 88 slots / 69 names | 66 trampolines (data2c's stale names `title_FUN_004f0cb0`, `insect_FUN_…`, `func_00504DD0`…); 3 names (`func_004EC7B0/C0/D0`) are FACTORY's own symbol names, so a direct static binding |
| `data2c_overlay_load_base` (`D_0047D134[0]`) | 1 | arena label = arena start |
| named overlay data used by MAIN | `D_00527020` (45 files: the FieldHud* wrappers, AttackChain*, …), `D_005273B8` | arena labels aliasing NORMAL's bss (only NORMAL covers them) |
| `D_00528200` (arena end = heap start) | 1 (`SysCalcFreeHeapMaybe_15e1d0`) | arena-end label + override (uses it as a number) |
| literal addresses | 2 (`*(s16*)0x5273C2`, `*(s8*)0x5273CE`) | hwaccess stage → `RG_OVL_DATA` → `rg_ovl_hwbus_resolve` |
| raw arena words in MAIN data | **190** (NORMAL 146, TITLE 42, INSMENU 1, 1 unowned) | **not handled here**: see open issues |

- **24 of the 272 import names are a function entry in two overlays.** Examples:
  0x004F0820 is `title_TitleSessionShutdown` and `insect_InsectBattleCalcWinStats`;
  0x004EC0E0 is in FACTORY and INSECT.
- **21 of them have DISAGREEING prototypes**, for example `func_4EC0E0`: factory
  `int(void)`, insect `void(void *)`.
- The address is ambiguous; only the resident overlay decides. That is why calls
  dispatch at run time.

## 3. Port design

1. **Everything is statically linked.** All five overlays' C is in the exe. Functions
   were already `<ov>_`-prefixed by the decomp.
2. **Data names get a prefix too.** The **`ovlsyms` stage** gives each overlay's own
   `.data`/`.bss` names (`D_`/`jtbl_` in the overlay's [data, bss end)) an `<ov>_`
   prefix.
   - Retail names collide: NORMAL and INSECT share 8 names (`D_00524D08`…`D_005251B0`).
   - At 2efa6b43 the stage makes 3416 renames in 564 files with 0 errors.
3. **One shared arena** (`ovl_arena_gen.c`, top-level asm): a zero-filled, 128-aligned
   0x3E380-byte block in `.bss`.
   - Every overlay data/bss label is a plain label at its retail offset (745 labels),
     plus MAIN's aliases.
   - Overlays therefore alias each other's memory exactly as on the PS2. Code that indexes
     past a symbol stays inside the same contiguous retail layout.
   - `RG_OVL_ARENA_PTR(a)` / `rg_ovl_host_ptr(a)` map any arena address.
4. **Registry** (`ovl_registry_gen.c`). Per overlay:
   - name, loader index, MWo3 id, sizes, and the ctor/dtor ranges;
   - the **pristine `.data` image**: `u32` words; pointer words are link-time
     relocations (`(uint32_t)&sym`);
   - the `.ctors` list (lifted functions), and empty `.dtors`;
   - the **function map**: address → name → host function (96/364/658/408/743 entries =
     the C units; jump-table case labels and the nop pad have none);
   - the **label map**.

   Registry-wide: the arena, and the import table.
5. **`rg_ovl_load(ovl)`** follows `OverlayLoadFile`:
   1. write the MWo3 header at arena+0;
   2. clear the text range (retail overwrites it with code; a stale read sees zeros, not
      the previous overlay's data);
   3. copy the pristine `.data`;
   4. zero the bss;
   5. mark the overlay resident;
   6. run its `.ctors` in table order.

   It does not run the outgoing overlay's dtors (`rg_ovl_set_run_dtors` exists; retail's
   lists are empty), and it does not touch the memory past the bss. **Object mode**
   (overlay data as C objects, once data2c covers overlays) restores each object from a
   snapshot taken at bind time and zeroes bss objects.
6. **Calls by address:**
   - **Import trampolines** (`RG_OVL_TRAMPOLINE`, naked i686): push (table, index), call
     `rg_ovl_call_import_at`, tail-jump to the host function for (resident overlay,
     address). The caller's frame passes through unchanged: cdecl arguments, sret
     pointer, eax/edx/st(0) returns. Tested: int, float/x87, 16-byte struct, 2 arguments.
   - **`rg_ovl_resolve_fn(addr)`** serves any other function-pointer-by-address use.
   - **Unknown targets** (no overlay resident, not an entry of the resident overlay, a
     data-slot import whose attributed overlay is not resident) are recorded (kind,
     overlay, address, count, name) and reported once.
   - Default is **fatal** (`abort`, P1 policy). `rg_ovl_set_fatal(0)` returns a stub
     that returns 0 instead.
7. **`RG_OVL_DATA`**: `rg_ovl_service_init` installs `rg_ovl_hwbus_resolve` with
   `hwbus_set_ovl_resolver`. `normal:D_00527020` resolves to the arena while NORMAL is
   resident, and to NULL otherwise (hwbus then uses its scratch slot and reports).
8. **Static initializers.** At 2efa6b43 the `.ctors` targets are MIPS code inside each
   overlay's `.data`, carried as opaque `.word`s. `tools/ovl_lift.py` lifts all 62 to C
   (`ovl_ctors_gen.c`, `<ov>_sinit_<addr>`).
   - It is a symbolic executor: constants, lui/addiu/$gp addresses, and loads
     materialised into temps in program order.
   - **Every branch must fold to a constant.** They are all mwcc's
     `&sym ? x : 0` diamonds; a data-dependent branch or a loop is an error.
   - Calls are marshalled by the R5900 EABI ($4–$11, $f12–$f19, 8-byte stack slots)
     against the callee's prototype from `game_protos.h` (`BUILTIN_PROTOS` for the asm
     MSL callees). Anything else raises an error with the address.
   - Address spelling: own labels / `RG_OVL_ARENA_PTR`, MAIN functions, MAIN data
     symbol + offset (containing object), and `RG_MAIN_BSS_PTR` for unnamed MAIN `.sbss`.
9. **Raw pointers in overlay data.** splat left some pointer words numeric.
   - Words equal to one of the overlay's own function entries or labels, or pointing
     inside its own data/bss, are **relocated**: 178 (INSMENU 78 callback-table entries,
     FACTORY 72, NORMAL 28). Each is logged as `raw-reloc` for review.
   - Words inside the overlay's own text that are not entries are kept raw: 724 dead
     jump tables (`jtbl_*`). C `switch` compiles natively, and the C only names them in
     comments.
   - 10 TITLE jump-table words name labels with no host definition: kept raw,
     `unbound-ref`.
   - MAIN-range coincidences (`raw-ptr-candidate`, 55, packed shorts like 0x00100000)
     are kept raw.

## 4. Generator: `tools/gen_overlay_registry.py`

```
python tools/gen_overlay_registry.py --out build/ovl-gen [--game game]
       [--source ../RGDecomp --rev 2efa6b43]   (default: game/SNAPSHOT.txt)
       [--data2c ../RGDecomp@d784320c]         (MAIN data slots; optional)
       [--bin data/BIN]                          (cross-checks only; nothing emitted from it)
```

- **Reads git objects at the rev** (never the worktree):
  - `config/<ov>.yaml`, `config/<ov>.symbols.txt`, `config/main.symbols.txt`;
  - `asm/overlays/<ov>/data/<ov>_data.data.s`, `asm/overlays/<ov>/<ov>_bss.s`;
  - `asm/data/*.s` and `asm/main.s` (MAIN data/rodata labels), `SCUS_974.90.lcf`.

  From `game/` it reads MANIFEST (defined symbols), `game_protos.h`, and the MAIN and
  overlay sources (overlay-range names).
- **Writes:** `ovl_registry_gen.c`, `ovl_arena_gen.c`, `ovl_ctors_gen.c`, and
  `OVERLAY_REGISTRY.tsv` (rows: `ctor`, `import`, `import-proto` (agree / DISAGREE),
  `main-alias`, `data-slot`, `raw-reloc`, `raw-text-word`, `raw-ptr-candidate`,
  `unbound-ref`, `main-raw-ovl-word`, `bin-check`).
- **Exits 1 on any error**, such as:
  - a ctor that does not lift;
  - an import that is no defined function;
  - a MAIN name covered by 0 or 2 overlays;
  - `ovlsyms.OVERLAY_DATA` disagreeing with the snapshot;
  - a header or `.data` mismatch with `--bin`.
- **Both data forms.**
  - Asm data (2efa6b43): arena mode, as above.
  - C data (`src/<ov>_data/*.c` in MANIFEST, data2c style with `sizeof` checks):
    object mode. **Limit:** the ctors are then expected as C too (not lifted). This path
    is exercised only by the synthetic object-mode test; no real snapshot has overlay
    data as C yet.
- **CMake** runs it at build time (`rg_ovl_gen`) when Python, `game/` and the snapshot
  repo in `game/SNAPSHOT.txt` exist. Targets:
  - `rg_ovl_registry_table`: `RG_OVL_TABLE_ONLY`, no game symbols (tests);
  - `rg_ovl_arena`;
  - `rg_ovl_registry_game`: an OBJECT library, compiled in ALL, linked only by the game.

  Result at 2efa6b43: 62/62 ctors lifted, 272 imports, 0 errors, 5/5 BIN checks.

## 5. Bindings and overrides

| Game function | Kind | Behaviour |
| --- | --- | --- |
| `OverlayLoadFile_100410` (asm, excluded) | **binding**, `ovl_bind.c` | path (host string, or one of D_0044AF90's raw retail addresses 0x0045AD30+0x20k, decoded to loader index k%7) → overlay; `rg_ovl_load`; return 1. Unknown path → abort (retail would retry forever). The .BIN is not read. |
| `FileReadAll_1004b0` (asm) | none needed | only caller is OverlayLoadFile |
| `RunStaticCtors_100df0` (asm) | binding needed for MAIN's own table (`MainStaticInit_100580`), owned by the runtime (`rg_crt0_run_ctors`); the overlay path does not use it | walk u32 table, then `EhRegisterFragmentStubMaybe` |
| `DestroyGlobalChain_100d60` (asm) | binding needed elsewhere | must NOT walk the chain once an overlay was reloaded (cycle) |
| `SysCalcFreeHeapMaybe_15e1d0` | **override** written | `(s32)D_00528200` / `(s32)D_00030000` → the retail numbers 0x528200 / 0x30000 |
| `OverlayLoad_1c3210`, `OverlayLocateFiles_1c3300`, `OverlayCdSeek_1c32b0`, `GetLoadedOverlayId_1c3200`, `OverlayLoadNotifyStubMaybe_100400` | unchanged C | |
| 16 of the 19 MAIN thunks (`*Thunk_4ec3e0`, `_4f9f60`, `_523260`, `_524590`, `_4f32f0`, `_4f3300`, `_4f3240`, `_4f3250`, `_50ab00`, `_50ab10`, `_511690`, `_5110c0`, `_521290`, `_516a50`, `_516a60`, `_507400`) | needs a **protos-level** fix | they are `void T(void){ func_X(); }`, but the overlay callee returns `int` / `unsigned char` (retail `j` passes $v0 through). protos then rewrites callers to `(T(), 0)`; e.g. `FactoryModeUpdate_27db40` phase 100 `(FactoryMenuIsActiveThunk_4ec3e0(), 0) != 0` is always false. Feed the `import-proto` rows into protos so thunk and callers get the callee's type. |

Registration of the stage (tools/ingest.py is owned elsewhere):

```python
import ovlsyms                                    # tools/stages/ovlsyms.py
os_ = ovlsyms.OvlSymsStage()
... Stage("ovlsyms", os_.apply, ("unit", "data"), os_)  # after asmexclude, before protos
```

**Runtime:** `rg_runtime_set_service_hook(rg_ovl_service_init, (void *)&rg_ovl_generated_registry)`.
**Game link:** `$<TARGET_OBJECTS:rg_ovl_registry_game>` + `ovl_arena_gen.c` (`rg_ovl_arena`) +
`rg_ps2_overlay_bind`.

## 6. Tests (`ctest -L overlay`, 18, all pass on build/ovl-i686)

| Test | Checks |
| --- | --- |
| `data_restore` | switch α→β→α and α→α restore .data; header in the arena; text cleared; bytes past bss untouched; load counts |
| `bss_zero` | bss zeroed on every load, before ctors (a ctor's bss write survives) |
| `ctor_order` | table order, re-run on every load; ctors see restored data, zero bss, overlay already resident |
| `resolver_current` | `resolve_fn` and `hwbus_resolve` follow the resident overlay; non-resident and text addresses → NULL |
| `shared_address` | two overlays, one address: lookup per overlay; trampoline dispatch to the resident one with int / float (x87) / 16-byte sret / two-arg calls |
| `unknown` | before any load, non-entry address, interior address, data slot with the wrong overlay resident: records (kind, overlay, address, count, name), hook once per record, stub returns 0 |
| `address_map` | host ↔ PS2, `label_at`, find by name / loader index / path (`cdrom0:\…;1`, `host0:…`) |
| `object_mode` | data-as-C objects restored, bss objects zeroed, object address map |
| `bind_validation` | unsorted table and oversize overlay rejected |
| `bind_hwbus` | `OverlayLoadFile_100410` by path and by D_0044AF90's raw retail address; `RG_OVL_DATA` through hwbus while resident, hwbus scratch and report when not |
| `real_registry` | generated registry (table mode): retail header values, ctor counts, function counts 96/364/658/408/743, 206+66 imports each naming a function entry, mode-table slots resolve to `title_TitleSession*`, 0x4F0820 differs between TITLE and INSECT, NORMAL labels |
| `arena` | linked arena: 128-alignment, size, label offsets, MAIN aliases (`D_00527020` = `normal_D_00527020`, `D_00528200` = arena end, `data2c_overlay_load_base`), the NORMAL/INSECT collision resolved; a real NORMAL load (data image, resolver, bss reset) |
| `bin_data` | table-mode pristine image = retail `.data` bytes for all five, sizes/header fields (skips, exit 77, without BINs) |
| `gen_unit` | `test_gen.py`, 12 tests: lifter on hand-assembled MIPS (gp ctor/register/copy, constant diamond, branch-likely slot, EABI stack args with a delay-slot write, float args + mul.s), lifter errors, data-asm parser (`.word sym/.float/.short/.byte`, gap error), ctor-table rule, ovlsyms (collision, idempotent, MAIN untouched, out-of-range errors) |
| `*_control` ×4 (`WILL_FAIL`) | reversed ctor table; alpha's result expected with beta resident; one real function entry moved by 4 bytes; ovlsyms NORMAL range shifted |

## 7. Open issues

(2026-10-25: with the native module table, 1 is fully symbolic -- `<ov>_D_x + off`, section 8
item 6 -- 2 is `data2c_main_bss + off` spelled by the generator, 3 holds for the arena only:
the module table defines `D_00527020` / `D_005273B8` in NORMAL's segment and
`data2c_overlay_load_base` as a token; 7 no longer applies to it (no text range in memory);
9: object mode is not supported by the module table.)

Items 1-3 are handled by the `datareloc` ingest stage since the interim snapshot
(docs/LINK.md "Data layer": raw arena words, D_0044AF90's string pointers, one
labelled MAIN bss block, arena aliases defined only by the arena).


1. **MAIN data holds raw arena addresses: 190 words** (`main-raw-ovl-word` rows).
   - Examples: `.sdata` `D_00480390` (data2c typed it `s16[1656]`) holds TITLE data
     pointers such as 0x004F1500; NORMAL's tables.
   - On the port they must become `(u32)&<ov>_D_…` (arena labels). The MAIN data owner
     (data2c/ingest) has to relocate them; the TSV gives each word, value and owner.
   - **Same for `D_0044AF90`** (`.rodata`, raw string pointers). The binding decodes it,
     but `OverlayLocateFiles_1c3300` passes those raw values to `Strchr_1347c0` and would
     fault.
2. **MAIN `.bss` naming.** The lifted ctors use `RG_MAIN_BSS_PTR()` =
   `data2c_main_bss + (a - 0x481080)` (data2c's single block; `-DRG_MAIN_BSS_SYM=` to
   rename). MAIN's named bss symbols must alias into that same block, or the ctors'
   `ios_base::Init` nodes and MAIN's view diverge.
3. **`D_00527020`, `D_005273B8`, `D_00528200` and `data2c_overlay_load_base` are defined
   by the arena.** A MAIN data generator must not define them again.
4. **The 16 value-dropping thunks** (§5) are a protos issue. The registry TSV has the
   callee prototypes. (Done: protos binds agreeing imports to the overlay definition,
   PROTOS.md "MAIN→overlay imports".)
5. **21 imports have disagreeing prototypes across overlays.** The trampoline is
   ABI-transparent, so the caller's declaration decides how arguments are passed. A
   wrong declaration in MAIN is the same bug as in any cdecl call (PROTOS.md). The
   protos stage binds each MAIN calling file to the overlay whose definition its view
   matches (the one resident when that code runs) and patches that file's declaration
   (`overlay-import-per-site`, 12 names / 18 files at 2efa6b43), so no shared prototype
   is needed for these names.
6. **The `RegisterGlobalObject` chain cycles after reloads** (§1). The
   `DestroyGlobalChain` binding must not walk it.
7. **Text-range contents are zeros on the port.** Retail has MIPS code there. Nothing is
   known to read overlay text as data.
8. **Trampolines are i686-only** (naked asm). x64 (P7) needs a new spelling.
9. **Object mode is untested on real data**, and lifting is asm-snapshot-only: a future
   snapshot with overlay data/ctors as C needs the ctors' C names in the registry
   (generator TODO).

## 8. Native module table (`src/native/ovl`, D9; 2026-10-25)

PLAN.md D9: the shipping exe has no PS2 memory map. The arena manager above places every
overlay at its retail offset in one shared 0x3E380-byte block and resolves calls by
(resident overlay, retail address). A native-only rg-game with `RG_NATIVE_OVL` (CMake
option; native-only builds only) links the **native module table** instead: each overlay is
an ordinary statically linked module, and "loading" one is switching the active module.

| Path | What |
| --- | --- |
| `src/native/ovl/ovl.h` | the ONE interface both managers implement (moved here; `src/ps2/overlay/ovl.h` forwards). Native fields: `rg_ovl_desc.seg`, `rg_ovl_import.fns`; the address-map functions are arena-manager only |
| `src/native/ovl/ovl_native.c` | bind / load / active module / import dispatch / reports (`rg_native_ovl`) |
| `src/native/ovl/ovl_native_bind.c` | `OverlayLoadFile_100410` (module by the path's file name; `load` ignored) and `rg_ovl_service_init` (bind only: no hwbus resolver) |
| `src/native/ovl/ovl_gen.h` | asm symbol spelling, `RG_OVL_TRAMPOLINE`, `rg_ovl_bits_f32` (shared with the arena manager's generated files) |
| `<build>/overlay-gen/ovl_native_gen.c` | generated: segments, .data images, ctor tables, import x module tables, trampolines, `rg_ovl_generated_registry` (OBJECT library `rg_ovl_native_game`) |
| `tests/overlay/ovl_native_tests.c` | `ctest -R overlay.native_` (4 tests + 4 controls) |

### Design

1. **A data segment per module.** `ovl_native_gen.c` emits, per overlay, `<ov>_seg`: its
   .data followed by its .bss (data_size + bss_size bytes, 128-aligned like the retail data
   start), with every data/bss label the code names (`normal_D_00527020`, `factory_jtbl_...`,
   `<ov>_bss`) at its offset inside the segment. Code that indexes past a symbol stays in
   its own module's contiguous layout, as on the PS2. MAIN's aliases into one overlay
   (`D_00527020`, `D_005273B8` = NORMAL bss) are labels in that module's segment.
2. **Load = `memcpy(seg, data_image)`; `memset(seg + data_size, 0, bss_size)`; active = ovl;
   ctors in table order** (the 62 lifted `__sinit`s, unchanged). Reloading the active module
   repeats it (retail does). No dtors (retail lists are empty; `rg_ovl_set_run_dtors` kept).
3. **Imports by build-time table.** Each of the 242 MAIN import names (`func_4F6AB0`, ...)
   gets `rg_ovl_imp_N[5]`: the host function each module defines under it (53 names are
   defined by more than one module, with different code). The trampoline (ABI-transparent
   naked i686, as before) calls `rg_ovl_call_import_at(table, N)`, which returns
   `fns[active]`; none, or no module loaded: reported (kind, module, name), then abort (default)
   or a stub returning 0. A data-slot import of another module: reported (DOMAIN), active
   module's entry used (the arena manager's rule).
4. **No retail address anywhere.** Descriptors carry name, file, loader index, MWo3 id,
   sizes, image, ctors, segment (load / ctor-range fields 0); imports carry name, domain,
   kind, table (address 0); no function / label maps, no arena. `rg_ovl_bind` rejects an
   arena registry, address-keyed tables and imports with an address.
5. **Symbolic addresses in the shared generated code.** `ovl_ctors_gen.c` (both managers)
   spells an own unnamed address as `label + offset` (nearest label at or below it;
   `<ov>_seg` exists in both forms) and unnamed MAIN bss as `data2c_main_bss + offset`
   (was `RG_OVL_ARENA_PTR(0x...)` / `RG_MAIN_BSS_PTR(0x...)`); the .data images' interior
   self-pointers likewise (was `rg_ovl_arena + off`).
6. **MAIN data pointing into overlays** (datareloc, docs/LINK.md "Data layer"): the 98
   `arena-data` words are now `(u32)((u8 *)&<ov>_D_x + off)` (was
   `data2c_overlay_load_base + off`). The 7 words whose value lies in both NORMAL's and
   INSECT's data range (0x00524D00..0x00526080) are attributed by `ARENA_DATA_OWNER`
   (checked against the snapshot listings: D_004684C0's two ResGroup lists are NORMAL's,
   D_00480390's five string pointers are INSECT's "insect" / "menu" / "effect" / 2 SJIS
   words); any other ambiguous word fails the stage. The arena end (D_004461F4, retail
   `_end` read only by the natively bound asm `sbrk`) becomes 0. `D_0044AF90`'s path
   pointers were already relocated, so the binding needs no raw-address decoding.
   `data2c_overlay_load_base` (D_0047D134[0], OverlayLoadFile's `load` argument) is a
   16-byte token the binding ignores; `D_00528200` (arena end) is not defined (no compiled
   code references it).
7. **RG_OVL_DATA** sites were already direct label references (hwaccess `overlay-data`), so
   the RG_OVL_DATA backing `rg_ovl_data` (src/ps2/hwbus) and the arena binding's hwbus
   resolver leave the exe with the arena manager.

### Semantics against retail

Identical where the retail code is well-behaved: .data restored and .bss zeroed on every
load, before the ctors, which run with the module active; a reload re-initialises. What the
arena reproduced and the modules do not: (a) overlays no longer share bytes -- a load no
longer clobbers another overlay's data (NORMAL's data under INSECT's image, or the stale
bytes past a smaller overlay's bss). Retail code only reads an overlay's data while that
overlay is resident (the MAIN wrappers on `D_00527020` are NORMAL-mode code; NORMAL's bss at
0x00527020+ is above every other overlay's end, so retail never clobbers it either); (b) no
MWo3 header / text range in memory (nothing reads it); (c) a MAIN call through an import
reaches the active module's function exactly as before.

### Trace address map (`src/trace/trace_map.c`)

The trace recorder resolves PS2 addresses (region files, pointer slots) through symbols, the
arena and the heap. A native-only exe has no arena, so overlay addresses were unmapped
there (no trace of overlay data, and host pointers into a module segment could not be
translated back). Now (2026-10-25, overlay-coverage lane): the generator keeps each
descriptor's `text_size` in the module table (a size, not an address: the text bytes between
the 0x40 MWo3 header and .data; `load` stays 0), and trace_map maps

- forward: an address in [arena base + 0x40 + text_size, + data_size + bss_size) (the arena
  manager's `data_vram()`) of the **active**
  module (`rg_ovl_current()`) to `seg + offset`; the text range and the bytes past the
  module's .bss are unmapped (retail code / another overlay's bytes; the arena manager
  shows zeros or stale data there);
- reverse: a host pointer into **any** module's segment to that module's retail data address
  (the segments are disjoint, so this does not depend on residency).

`ctest -R overlay.native_trace_map` (+ control: text_size 0 = no mapping) checks both on the
synthetic modules; `routecmp.py run --ovl-regions BUILD` traces one `ovl:<name>` window per
overlay (docs/TEST-FIXTURES.md "Factory and Insectron drivers").

### Verification

See the 2026-10-25 entry in docs/bringup/BRINGUP-HISTORY.md (link audit, gates on
build/nd9-i686).

Overlay gameplay coverage and the golden-route lockstep against the oracle twin: the
2026-10-25 (overlay coverage) entry in docs/bringup/BRINGUP-HISTORY.md.
