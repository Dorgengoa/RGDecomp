# UNBOUND stubs and compile-review sites: triage

Read-only triage of `missing/UNBOUND.tsv` and `build/i686-windows/game_compile_review.tsv`,
made on 2026-10-12 against the pinned snapshot `675c07fe` and the `build/clean-i686` objects.
Row-level data: `out/unbound-triage.tsv` and `out/compile-review-triage.tsv`.

## Method

- **Reachability.** `llvm-nm` over the 25,573 objects that `rg-game.map` links (tests are
  excluded) gives a symbol graph: an edge goes from each object to the objects that define
  the symbols it references. Code-to-data and data-to-code relocations count as edges, so
  vtables and function tables are followed. A breadth-first search starts at
  `rg_game_main.c.obj` (`rg_game_entry` -> `Main_15e700`). The stub object and the trace
  symtab are left out of the search. 23,321 objects are reachable. This graph
  over-approximates: if an object is unreachable here, nothing in the link can call it.
- **Retail.** `asm/main.s`, `config/main.symbols.txt` and `config/data2c.json` at
  `675c07f` (git objects only).
- **Compile review.** The current `game/` source, `game/PROTOS.tsv`, the retail listing,
  and `llvm-objdump` of the `build/clean-i686` object for each site.

## UNBOUND: 105 rows, not 107

`UNBOUND.tsv` has **105** rows. The 107 in LINK.md and SNAPSHOT-CLEAN.md includes
`func_207A90` and `SyncDCache`, which BRINGUP fixes 6 and 12 removed. LINK.md's class table
(`sdk-internal 41`, `interior-entry 2`) is out of date for the same reason.

| Triage | n | Reached | Meaning |
| --- | ---: | --- | --- |
| missing-game-code | 7 -> **0** (integrated 2026-10-12: C in `missing/`, rows removed; UNBOUND.tsv now 98 rows) | yes | Real game functions with no C in the decomp and no symbol in main.symbols.txt; they exist only as asm in `asm/main.s` |
| data-numeric-constant | 3 | yes | A data word that equals a code address but is really a number (flag bit or packed u16 pair). Binding it to a stub **silently corrupts data** today |
| data-fn-address-alias | 1 | yes | An overlay's `D_002931A0` is the MAIN function `UiTextElemInit_2931a0`. The zero-filled data stub gets **called** |
| l5-port-needed | 6 | yes | L5 vector/GS-packet asm. The sibling functions already have overrides |
| library-dead-in-practice | 6 | graph only | MSL `num_put<double>` helpers, reachable only through the motion-event text dump. No reachable code builds an ostream: `OstreamCtor_104270` has 0 references, and every MSL stream vtable is unreachable |
| dead | 82 | **no** | Every referrer is unreachable: MSL iostream/filebuf (22), libmpeg internals (26), EE kernel RAM (21), SDK internals (13). The port replaces these one level up (src/sce/kernel, src/sce/sif/fileio.c, src/movie). Keep the fatal stubs |

No SDK/library symbol that the game can reach needs a new `src/sce` provider. Everything
that can be reached is game code, an L5 override, or a data-binding error.

### Priority list for the next agent

**P0: hit on the first field, battle or battle result, or corrupting data now**

**Status 2026-10-12 (bring-up session 2):** P0 items 1, 6 and 7 and the P1 `MpegNextPictureMaybe_110008` item are DONE (override `overrides/src/main/matrix/MtxMulAffine_13d1d0.c`; protos rule `text-alias`; datareloc rule `fn-number`, 22 words; UNBOUND.tsv 98 -> 94 rows: MtxMulAffine_13d1d0, func_00200000, MpegNextPictureMaybe_110008, D_002931A0; then 89 with the other five P1 L5 overrides, hit in that order by the golden run after the opening FMV). The 10 REAL compile-review sites are fixed by protos `def-bare-return` for member calls (def-bare-return 15 -> 25, info-bare-return 16 -> 6). Details: BRINGUP.md "Checkpoint".

1. **`MtxMulAffine_13d1d0`** (L5). `ModelPrepareDrawMaybe_14f760` calls it once for every
   visible mesh node, so the first 3D model draw aborts. Write an override on the VU0 model
   that copies `overrides/src/main/matrix/MtxMulAffine_13d110.c`. The asm is 8 `lqc2`, 4
   column `vmula/vmadd` chains, and row 3 adds `a.r3 * b.w`.
2. **`func_001B02C0`** = retail `ModelObjExUpdate_1b02c0` (about 284 instructions). It is the
   update slot of the Character2 vtable `D_00470F50` (installed by 29 constructors: NPCs,
   monsters, event casts, map objects) and of `D_00470FB0`. Write C from asm in `missing/`.
3. **`func_003135C0`** = `TaskStepJudgeObject_3135c0` (about 285 instructions). It is a step
   in the task table `D_0044ECF0` (`TaskTableInit_27c310` <- `GameSessionInit`) and does the
   object collision/hit judge (SpatialMgr/SpatialGrid/HandleRegistryRef). Write C in
   `missing/`.
4. **`LiveTalkStep_321240`** (about 255 instructions). `TaskStepLiveTalk_321210` calls it
   every frame in the field (party live-talk streams). Write C in `missing/`.
5. **`func_003AB240`** (about 616 instructions, the largest). It is a Chara vtable slot after
   `CharaActionGaugeRegen`: ability/weapon use builds the ExecEffInfo list. It is reached in
   battle. Write C in `missing/`.
6. **`D_002931A0`**. `normal_MenuBattleEndInit_4ee600` passes it to `ConstructNewArray_100710`
   as the element constructor, so every battle-result screen jumps into a zero-filled .data
   block. Fix it with a stage rule (protos addr-alias / datareloc equate) that binds a MAIN
   text address declared as data (`extern const u8 D_002931A0[]`) to the C function at that
   address (`UiTextElemInit_2931a0`).
7. **`EntryPad_100000`, `func_00200000`** (19 words in 12 data objects). These are the
   flags 0x00100000 and 0x00200000 in:
   - the ActCfgLoadText name/flag tables (`D_0044BB40`, `D_0044BDA0`, `D_0044C000`,
     `D_0044C1F0`), read at session init;
   - the EvScript door/lift/vehicle flag table `D_00451F00`;
   - the gaiji metric table `D_0044E680` (`FontFindGaijiMetric`);
   - the menu panel layouts `D_00450340`/`D_004503C0`;
   - NavCfg `D_00452330`;
   - the dead SDK table `D_00446648`.

   The stub host addresses are stored in their place now. `func_00200000` is not even an
   entry: it is the `alabel` the listing splitter puts at 0x200000 inside a function. Fix it
   with a datareloc rule: never bind an `alabel`, and write the number (like `micro-unsym`).
   **One exception:** `D_0047D130` (1 word, read by `MainStaticInit_100580` /
   `EhFindExceptionTableMaybe_102690`) really is the .text start address, used for the
   exception-table code range. It is only compared, never called, so keep it bound to an
   address (better: a port text-start symbol). Do not revert it.

**P1**

- `MpegNextPictureMaybe_110008`: 5 words in the main-menu layout table `D_00450480` are the
  packed pair 0x00110008. Revert them in datareloc. Then audit the other u16-pair layout
  tables for words that hit a *real* C function (those never show up as UNBOUND).
- L5 overrides, small, all with an overridden sibling: `GsPktSetXYZPixelVec_13ef70` (field
  HUD `ScreenMarkerDrawAll_31af50`), `GsPktSetSTVec_13ecc0` (`TaskDrawMonography`, insect),
  `VecFtoi4_13e2e0` and `GsPktAddDmaCallTag_13f1f0` (`ModelDrawOffscreenCompositeMaybe_16aac0`;
  the CALL tag carries a PS2 address, so it must go through the DMAC address map), and
  `AabbProjectScreenBounds_13c4f0` (model draw with `req->bounds`).
- `func_003AB200` / `func_003AB220`: 5-instruction Chara thunks,
  `return this->vtbl[0x434 or 0x444](this, *(u16 *)(this + 0x10))`.

**P2**: `func_3930D0` = `UiNineSliceSpritesLayoutMaybe_3930d0`, a 256-instruction leaf used
by the INSECT battle UI. It is a whole function with no C, not an interior entry, so the
UNBOUND class `interior-entry` is wrong.

## Compile review: 39 sites

| Verdict | n | Sites |
| --- | ---: | --- |
| fixed since the review (protos `def-bare-return`) | 15 | ArenaAlloc*, ArenaNewChecked x2, MemStackAlloc1K, Pool/ObjPoolTryAllocElem x3, EquipSlotGet* x3, CameraDistToEye, CharaIsInParty, MapIdListFindChecked, MapMgrSkyLoadDef. The objects tail-return the callee's result (checked: PoolTryAllocElem_2d7ad0) |
| **REAL, open** | **10** | `obj->vN(..); return;` in a value function (C++ VCM calls): CharaActivateEquipSlotByRec_3ac330, CharaFindActivatableSlotByRec_3ac460, UnitFindActivatableSlotByRec_3bd6c0, CharaUseAbilityFromRec_3abe40, MenuObjInsect{GetLevel, IsMaxLevel, GetSatiety, GetInsectorParam, GetName, IsFullyGrown} |
| benign, open | 6 | NavGraphSetGoalEdge, NavMgrSetCurrent (retail `$v0` is undefined there as well), EffectSpawnFinishingBlow, MenuFadeDraw, InfoEdgeMenuLoadRequest (callers ignore the result), WarpMenuFadeOutStart (returns 0.0 like retail, but only because of register allocation) |
| correct | 8 | implicit declarations: strcmp/strcpy/strcat (builtin types), InsectCageMenuOpen_38b9a0 (no arguments, result unused), func_28EA90 = UiEntryListSelectByTag_28ea90 (pointer/int arguments only) |

**The 10 REAL sites are miscompiled now, not just undefined.** In `build/clean-i686`, clang
folds the bare-return path into the other path's constant. For example,
`MenuObjInsectGetLevel_386b90` calls `*0x1a4(vtbl)` and then does `movl $1,%eax`, and
`CharaFindActivatableSlotByRec_3ac460` always returns 0. Retail tail-returns the virtual's
`$v0`. The effects: every insect reads as max level, its name is NULL and its satiety is 0,
and Chara/Unit "find activatable slot" and "use ability" always fail. **Fix (stage rule,
protos):** let `def-bare-return` accept a member call through the `VCM`/`VCM0` accessor
(`((C0 *)p)->vN(a..); return;` -> `return ((C0 *)p)->vN(a..);` when the accessor's return
type is the def's class). The 10 sites are the C++ `info-bare-return` rows in
`game/PROTOS.tsv`. No override is needed. Optional: also spell `return 0.0f;` for the f32
`info-bare-return` sites (WarpMenuFadeOutStart, MenuFadeDraw), so that the x87 return value
no longer depends on register allocation.

Follow-up outside this list: `-Wreturn-type` (a value function that falls off its end) is
hidden by `-w` and is not in the review TSV. It is the same hazard class (clang may fold or
trap). The next step is a census in a scratch build dir with `-w` replaced by
`-Wno-everything -Wreturn-type`.
