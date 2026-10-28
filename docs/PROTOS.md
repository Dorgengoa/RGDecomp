# Transform 2: prototype unification (`tools/stages/protos.py`)

PLAN.md transform 2.  The decomp declares every callee locally, per file.  mwcc's MIPS
EABI tolerated a wrong argument count, a void-vs-value return or an int/pointer swap;
i686 cdecl does not.  This stage makes every direct call ABI-correct against the
**definition** and writes `include/port/game_protos.h`.

## Policy

| What | Rule |
| --- | --- |
| Truth | The C definition in its registered unit.  An `asm` function, or a C body holding an `asm` block (syscall stubs, COP2 helpers), has a placeholder signature: it is **not** truth.  For a name with **no C truth in the corpus**, the port provider's declared prototype is the truth (`info-provider-protos`, 271 at 2efa6b43): the definitions in `overrides/` and `missing/` (C ports of excluded asm files), then the declarations of `src/crt/crt.h` (soft-double, libgcc, libm, MSL; BINDINGS.md).  These go into game_protos.h like any definition (variadic ones excepted: callers keep their views).  The 9 host-CRT names (`strlen`, `memcpy`, ...) never go into the header; a file whose local view is ABI-wrong (`extern s64 strlen(s32)`) gets that declaration patched in place.  Excluded names with no provider (sce* kernel stubs, `Atan2_129148`, ...) keep their callers' views. |
| i686 kinds | ABI identity is decided per transport kind, not per EE register class: `f` float (ST0 return), `d` double (ST0 return, 8 stack bytes), `q` 8-byte integer (EDX:EAX, 8 bytes), `i` 4-byte integer/pointer.  `int` vs `long long` and `double` vs `long long` returns differ; a `void` view of an `f`/`d` callee is an ABI break (the call statement would leave ST0 on the x87 stack), so C++ declarations of x87-returning callees are patched to the real return. |
| 8-byte GPR transport | The EE passes double, s64 and u64 in ONE 64-bit GPR: a value crosses a call as bits.  Where the caller's view and the definition disagree on double vs integer (soft-double callers that typed the register `s64`/`s32`), argument and return are spelled `__builtin_bit_cast` (`arg-bitcast`, `ret-bitcast`), after converting to the view's type (what mwcc did), never as a C numeric conversion.  A double-returning call written straight as the argument of a double parameter passes unconverted (retail moved the register). |
| Double carriers | A 4-byte integer parameter (`double-param`) or local (`double-local`) whose every occurrence is `v = F(..);` with F returning double, a whole argument landing in a double (or 8-byte) parameter, `return v;` from a double function, or its declaration, is retyped `double` (an s32 cannot hold the 64-bit register mwcc kept live).  Fixpoint: the soft-double compare wrappers `Double{Less,Greater,...}_1002xx(s32, s32)` become `(double, double)`, then their callers' arguments pass unconverted. |
| Header | `include/port/game_protos.h`: one prototype per externally linked, C-linkage definition, builtin C types only (`s32`->`int`, `f32`->`float`, every pointer -> `void *`).  Each is wrapped in `#ifndef RGP_SELF_<f>`.  Skipped: static, C++-linkage, struct/128-bit/unknown-typedef by value, symbols declared in `include/*.h`. |
| C files (strict) | Preamble: `#define RGP_SELF_<f> 1` for each function the file defines (and for header names the file must keep its own view of), `#include "port/game_protos.h"`, `#line 1`.  Every local declaration of a header symbol is blanked (`/*rgp*/`, newlines kept).  Calls compile against the definition. |
| C++ files (local) | No header (C++ has no int<->pointer conversion, so `void *` prototypes cannot be used).  Each ABI-wrong local declaration is patched in place to the definition's shape, keeping the local spelling per register-class slot. |
| Argument mapping | As the EE passed them: GPR arguments (int, pointer, s64, promoted/double) fill `$a0..` in order, `f32` fills `$f12..` in order, independently.  The k-th GPR parameter of the definition takes the caller's k-th GPR argument; same for FPR.  So `UiMoveWidgetUniform(a,b,c,d, 0, 0.25f)` against `(s32,s32,s32,s32,f32)` drops the `0`, not the `0.25f`. |
| Extra args | Dropped (`drop-extra`); kept as `((void)(x), first)` when they have side effects (`drop-extra-keep-eval`). |
| Missing args | If no other call precedes this one in the enclosing function and that function's k-th incoming parameter of the class is unmodified, pass it (`missing-passthrough`: the register still holds it).  If the enclosing function has no such parameter, it is widened (`def-widen`, fixpoint).  Otherwise `0` (`missing-zero`). |
| Void def, value used | If the definition's only exit is a final tail call to a value-returning function, retail returns that value (`$v0`/`$f0` survive the epilogue): the definition becomes `return G(..);` with **G's** type whatever class the callers read (`def-tail-return`).  A C++ void definition ending in a virtual call `p->m(..);` (m declared once in the file, `virtual void m(..)`) returns that call's `$v0`/`$f0`: the method and the definition get the callers' type and `return` is inserted (`def-tail-vcall-return`; `CharaGetIconRecMaybe_3ae3e0`, whose retail ends in the slot-0x340 `jalr` with nothing after it, now returns the record pointer its 26 callers read).  Otherwise the use becomes `(F(..), (T)0)` (`void-value-zero`: the callee's asm leaves `$v0` unset, e.g. `VecCopy_1cbe30`). |
| Value def, other class used | `T F(..) { return G(..); }` as the only return, where callers read G's class (e.g. an `s32` adapter forwarding an `f32` getter: retail returns G's `$f0`): F is retyped to G's return type (`def-tail-retype`).  Also a **pure forwarder** whose own view of G returns T (so mwcc emitted a bare tail jump, no conversion) while G is defined in the other class, or an int forwarder of a double: F takes G's type whoever calls it. |
| Hosted statics | A hosted guest (`config/hosted.txt`, `static` in its host's file as an mwcc register lever) that other units call loses `static` in its definition and its host's declarations (`hosted-unstatic`: `ScriptGetInt_26a2a0`, `ScriptSetRefInt_26a1e0`, `ScriptGetCodeAddr_26a200`, `CharIsNotSpace_15e8e0`). |
| Address-style names | `func_XXXXXX`/`FUN_00xxxxxx` at a MAIN address that no file defines are renamed in every file, before the analysis, to the MAIN symbol at that address (`config/main.symbols.txt` at the snapshot) or, for an interior entry (`alabel` of a multi-entry listing), to the C entry `func_<start>_e<k>` (`addr-alias`, 987 names in 1,471 files).  The call then binds to the real definition (header prototype, ABI mapping) and the object references the real symbol, so **no link-time alias** is needed (COFF has no `__attribute__((alias))`; `/ALTERNATENAME` would bind the symbol but leave every such call with its unchecked local view).  The rest are logged `addr-alias-unresolved` (18: kernel-RAM addresses the SDK kernel patch calls, interior entries with no C entry, one address with no symbol). `ingest.py` hands the table to the stage (`snapshot_addr_table`). |
| 4/8-byte slots | An argument whose view type and definition type differ in width (s64 vs s32/pointer) is cast to the definition's type (`arg-cast`); in C++ a function name passed as an argument whose declaration this stage retyped is cast back to the view's parameter type. |
| Not mechanical | A view that passes or returns a struct/128-bit by value (EE struct returns use a hidden pointer), a data view of a code symbol (`extern u8 F[];`), a name bound to a same-image duplicate: C keeps its local declaration and the header proto is suppressed with `RGP_SELF_<f>`; logged `manual-call` / `manual-decl`.  C++ declarations used only for their address are not patched. |
| MAINâ†’overlay imports | MAIN calls overlay code by address names (`func_4EC3E0`, `FUN_004efc40`) that no MAIN file defines. The overlay definition at that address (name suffix `_4ec3e0`, every overlay defining it) is the truth: when all agree on the ABI shape, the import name is bound to it (`overlay-import-bound`, 194 at 2efa6b43) and declared in game_protos.h, so thunks such as `FactoryMenuIsActiveThunk_4ec3e0` get `def-tail-return` (`unsigned char`) and their callers read the value. Agreement is per i686 kind.  When only the return differs and the value views are integer (void vs EAX: a void caller ignores it) the value-returning view is taken (`overlay-import-disagree`, 3).  Otherwise (12 names, including the former "ret only" `func_5069E0`, f32 in NORMAL vs void in FACTORY: an x87 hazard) the import is bound **per calling file** (`overlay-import-per-site` + an `overlay-import-site` row per file): the overlay resident when that MAIN code runs is the one whose definition the caller's own view matches (parameter kinds, then classes, then count, then return; ties by the overlay named in the caller's path), so `TaskStepFactory_367960` binds `func_5069E0` to FACTORY's `void (A *)` and `FieldHudFadeIn_203ee0` binds `func_4F11D0` to NORMAL's `(Obj *, f32, f32)`.  Such a name gets no game_protos.h prototype; the file's own declaration is patched in place to the chosen definition's shape (C files too).  The trampoline behind the name is a bare jump (OVERLAY.md Â§6), so a per-file prototype is all the ABI needs.  Same data as the `import-proto` rows of tools/gen_overlay_registry.py. |
| Pointer returns | C: where the caller's view returned a pointer (or the definition does) and the value is used, the call is cast back to the view's type so `F()->x` / `F() + 1` keep their meaning (`ret-cast`). |
| ptr-vs-int args | C: left to the compiler with `-Wno-int-conversion` (the cast is free on i686). |
| f32 vs int return | Decided from the retail listings (asm/matchings at the snapshot): of the 21 former `manual-ret-class` rows, 14 were callers reading `$f0` from `MapBlockGetBox{Volume,BottomY,TopY}_1dfe60..80`, whose retail is `j AreaBox*Thunk_1e98x0` â†’ `j AreaBox*_1e98x0` (`lwc1 $f0`): the void thunks now return G's float and the s32 forwarders are retyped float, so those callers read the real value; 6 were the tail calls of forwarders already retyped (`ModelObjGetMotionPhase_1add70`, `GameSceneSoundSlot{4,5}GetVolume`, the factory grid snaps; no longer logged).  What is left is logged `ret-class-convert` (1: `EvCmdScreenFadeSetDelay_267990` reads `$v0` from a chain ending in `ScreenFadeBlockSetDelay_1780c0`, whose asm sets only `$f0`): retail's reader got a register the callee never set, C conversion stands in. |

Every rewrite and every flag is a row of `PROTOS.tsv` (`file line callee rule detail`;
`decl-removed` rows are logged only when the removed declaration was ABI-wrong).

## Compile flags (clang 23, C)

`-Wint-conversion`, `-Wincompatible-pointer-types` and
`-Wincompatible-function-pointer-types` are errors by default but downgradable; the
staged tree needs `-Wno-int-conversion -Wno-incompatible-pointer-types
-Wno-incompatible-function-pointer-types` on C sources.  Wrong argument counts,
`conflicting types` and using a void value are hard errors with no flag (the stage
removes all of them).  In C++ every int<->pointer conversion is a hard error
(`-fpermissive` and `-fms-compatibility` do not help), which is why C++ keeps its
patched local declarations.

## Registering the stage in ingest.py

Done: `tools/ingest.py` runs the stages stage-major and calls the optional
`prepare()` / `extra_outputs()` / `report()` hooks; `game_protos.h` and `PROTOS.tsv`
get MANIFEST rows of kind `generated`.  The original recipe:

The stage needs the whole corpus before it can rewrite one file, and it emits two
files of its own.  It is still a `Stage` (`name`, `apply(relpath, data)`), plus:

```python
sys.path.insert(0, str(PORT / "tools" / "stages"))
import protos
PROTOS = protos.ProtoStage()
STAGES = [PROTOS, ...]

# in ingest(), before the per-file loop -- pass the bytes the stage will see:
PROTOS.prepare({p: snap.read(p) for p in paths})
# ... per-file loop calls PROTOS.apply(p, data) as for any stage ...
# after the loop, before the MANIFEST is written:
outputs.update(PROTOS.extra_outputs())   # include/port/game_protos.h, PROTOS.tsv
```

It was measured on top of the `int128,gccvarargs,vu0asm,asmexclude` stages (the
`game/` those produced), so register it after them.  `apply()` raises if a file's bytes differ from what `prepare()` saw, so a stage that
runs before it must run over the whole tree first (stage-major order) and hand
`prepare()` its output.  `apply()` is idempotent (files carry `/* rgp:protos */`).
The two extra outputs need MANIFEST rows (e.g. kind `generated`).

## Rules added 2026-10-12 (bring-up session 2, BRINGUP.md "Checkpoint")

- **Interior-entry ordinals (`addr-alias`, `def-vthunk-naked`).** The C entry of an
  interior address is `func_<start>_e<k>`. `k` used to be the address's ordinal among
  the listing's `alabel`s. data2c's `config/data2c.json` `function_entries` (address ->
  symbol) is now ground truth: an address it lists takes its `k`; the alabels it does not
  cover take the remaining defined `k` in address order. ContainerViewGetAtFwd_418ab0
  defines e1..e15 for its unlabelled 16-byte `jr` stubs (vtable words) and e16 for its one
  alabel 0x418BB0; the old rule bound `func_00418BB0` (DataTable view GetAt) to `_e1`, a
  stub that dispatches vtable slot 0x10 (LoadResidentBin), which wiped the world data
  tables. `_name_addr` uses the same mapping and reads an unlabelled entry's listing from
  its instruction line, so those stubs become naked forwarders (def-vthunk-naked 142 ->
  201).
- **`text-alias`.** A `D_<addr>` name at a MAIN text address where a C function is
  defined, declared as a data array (`extern const u8 D_002931A0[];`), is renamed to the
  function and the data declaration dropped (NORMAL MenuBattleEndInit's element ctor
  `UiTextElemInit_2931a0`). Names used as struct tags are left alone.
- **`def-bare-return` for member calls.** `((C *)p)->vN(..); return;` in a value
  definition becomes `return (T)((C *)p)->vN(..);` when vN is declared `virtual R vN(..)`
  (or as a VCM accessor) with R of the definition's class (10 sites:
  MenuObjInsect*, Chara/Unit *ByRec).

## Rules added 2026-10-13 (bring-up session 3, BRINGUP.md "Checkpoint")

Census: `out/bringup-checkpoint/rules_census.py` -> `vcall-rules-census.tsv`,
`stackblock-census.tsv`, `bitfield-census.tsv`. Fixtures: `tests/protos/fixture`
(`MeshGroupPkts_400900.cpp`, `StackBlock_400a00.c`), checked by `protos.stage`.

- **Virtual calls against the listing (`_vcall_pairs`).** A C++ definition's retail
  `jalr` sites are paired in order with its C member calls to methods declared `virtual`
  in the file (only when the counts agree; else `info-vcall-unpaired`, 17).
  - **`vcall-widen`** (254, before the def-widen fixpoint): the jalr receives an
    incoming argument register, untouched since entry, that the C definition never
    declared. The definition gets `int rgp_aN` parameters (its callers then pass what
    retail held through the `missing-*` rules: def-widen 365 -> 735).
    CharaGetEquippedWeapon_3acd40 is `slot374()` = CharaGetWeaponId_2f5a50(chara,
    slot) with the slot in its own `$a1`; without it the first battle read
    `chara + garbage*2 + 0x23E` and faulted.
  - **`vcall-forward`** (289): the call passes those registers (`p0->v8(p1, p2, p3)`);
    the virtual's one declaration in the file gets `int rgp_fwdK = 0` parameters
    (other calls pass 0). f32 parameters are not GPR lanes (devirt passes GPR first).
    `manual-vcall-forward` (11): the method is declared several times in the file.
  - **`def-vcall-v0`** (26): `$v0` at every `jr $31` is that jalr's result (no later
    write or call) and the C definition is void: the call becomes `rgp_v0 = obj->m(..);`
    and the definition returns it, typed as the virtual (a void virtual declared once is
    typed int). ModelMeshGetGroupPktsMaybe_15b150 / ModelMeshMode1GetGroupPktsMaybe_1645c0
    (the mesh slot-0x18 packet-cursor class). `manual-vcall-v0` (5): not a top-level
    statement / several declarations.
  - **`info-vcall-set-args`** (41, not rewritten): retail sets further argument
    registers before the jalr that the C does not pass (constants, loads, `p3 & 1`);
    listed for review (e.g. normal_FieldHudAllySuggestOpen_4efc50 passes six).
- **`stack-block`** (86; `manual-stack-block` 72; 2026-10-18; **114 / 9 since 2026-10-19**, see "Stack-block census and rule fixes"). Every call argument that is a stack
  address `sp+OFF` in the listing (`&x`, `&x.f..`, an array `x`) and the extent `E` the
  callee reaches through it (`asmflow.Flow.extent`: forward must-dataflow of
  `ENTRY(reg)+c` over the callee, into `jal`s and tail jumps, depth 4). When
  `[OFF, OFF+E)` holds another local's address, or `E` exceeds the local's (primitive)
  size, the locals are placed in one 16-aligned byte block at retail's relative offsets
  (`__builtin_offsetof` for a local seen only through a member address) and every use
  becomes `(*(T *)(rgp_blkN + POS))`; a typedef'd negative-size array stops the build if
  two C types overlap. **Coverage guard** (after a rendering regression): every 16-byte
  slot the callees reach must hold a placed local of known size (primitive types, or
  structs of the file resolved with mwcc's natural alignment); otherwise the block is not
  built (`manual-stack-block`). CameraBaseLookAt_15fae0's side / up / dir rows are one
  retail matrix, but `up` is only written by inline VU0 code (no call argument maps it):
  the first version placed side and dir with a hole between them, MtxMul read garbage
  and every camera looked at the sky (no 3D in the field; the VU1 load dropped from
  ~12-24 ms to ~0.15 ms per field). Fixture `HoleBlock_400a80.c`. 82 blocks, 74 manual.
  Covers CollRaycastNearest_1c86e0 / CollRaycastNearestHit_1c8ad0
  (point/dir/Ray block) and CollSweepTri_1c7790 (`f32 mn[3]` receiving an `sq`); their
  overrides and ModelMeshGetGroupPktsMaybe_15b150's are retired
  (`out/bringup-checkpoint/retired-overrides/`).
  **2026-10-18 (BRINGUP.md (g)): 86 blocks, 72 manual.** Two blind spots closed: (1) frames
  larger than 32 KB (`lui $1, hi; ori $1, $1, lo; addu $29, $29, $1`) made every sp-relative
  argument an unknown term (`asmflow._expr` now folds sp + a 32-bit constant); (2) struct
  sizes came only from structs defined in the file, so a header type (`Vec4`, include/vec.h)
  had no size and the coverage guard declined (`_struct_layout` now also reads the game
  headers' C view, C++-only `#ifdef __cplusplus` parts dropped, `aligned(N)` honoured). New
  blocks: CameraFollowLeaderStepMaybe_3081e0 (the camera collision box {lo, hi}),
  ModelUpdateBoundsProjectedMaybe_14ff90 (BBoxUnion's {v140, v150} pair) -- both overrides
  retired (`out/mapreg/retired-overrides/`) -- CharaCmdGunShoot_228f80 (a matrix written
  through `&v50` over v60 / cam) and EvMapObjNodeApplyPartMatrixMaybe_367230 (0x40 bytes
  into a `Mat34`). The depth-4 extent limit was not the cause (the 3081e0 extent was found).
  New log rows **`info-stack-block-unresolved`** (680): every stack-address argument whose
  extent is only a lower bound (the pointer reaches a jalr, a callee without a listing, or
  depth > 4) -- the review list for misses of this class. Trace one definition's analysis:
  `RG_PROTOS_SB_TRACE=<regex of def names> python tools/ingest.py --out <scratch>` (stderr
  `sb-trace` lines: locals, each call argument's listing term and extent, groups).

Dialect stage (tools/portxform.py), same session: **`bitfield-gcc`**. clang's
i686-windows-msvc target lays bitfields out the MSVC way (units of the declared type,
aligned to it; a type-size change starts a unit; the next member follows the whole
unit); mwcc packs like GCC. `-mno-ms-bitfields` is rejected for the MSVC ABI. A run of
bitfields in a struct/class whose fields each stay inside one byte at their GCC
positions is re-declared with 1-byte types, and the struct keeps mwcc's alignment with
`__attribute__((aligned(A)))` after its closing brace (22 runs). WorldDataCmdSetPartyMember_3b9b00's
`u8 pad98[2]; u64 f0:1, f1:1, f2:1;` read `f2` at +0xA0 instead of +0x9A, so every NEW
GAME party command was skipped (party leader -1). Left alone and listed: 157 runs with
a field crossing a byte (141 are single-type runs that fill whole units, equal on both
ABIs when the run starts aligned), 2 with an unknown type.

## Rules added 2026-10-13 (bring-up session 4, BRINGUP.md "Checkpoint")

**64-bit values in 4-byte C (`wide-param`, `wide-arg`, `wide-local`).** The EE's GPRs
are 64 bits and mwcc never narrows a register for a C conversion to a 4-byte integer:
`(int)c->flags64` passes the whole `ld`, `s32 a = F64()` is a `daddu` move. A 32-bit ALU
op (addu, sll, ...) sign-extends its result, so a value stays "wide" only through copies
and the logical / doubleword ops. When it reaches an op that reads all 64 bits (a
`beq`/`bne` compare, `slt`, `sd`, `dsrl`..) retail sees the high word; the port's C
conversion cut it. `asmflow.wide_flow` is the forward may-taint over a listing (sources:
`ld`/`lq`/`dsll32` results, an 8-byte call result, an 8-byte parameter; spill slots
`sd`/`ld` at `$sp` carry the taint; `dsll32` ends a value: `dsll32`/`dsra32` is mwcc's
sign extension). The stage, iterated to a fixpoint:
- **`wide-param`** (13): a call passes a wide register to a callee whose definition
  declares that GPR parameter 4-byte, and the callee's listing reads all 64 bits of it
  (directly, or by passing it on to a callee that does or whose parameter is 8 bytes):
  the parameter becomes `long long` (`unsigned long long` when it was unsigned).
- **`wide-arg`**: that call's argument, when the C spells an explicit 4-byte cast, is
  passed without it. (In the game every such site was a view that already said u64; the
  former `arg-cast` narrowed it, and the retyped definition now matches the view.)
- **`wide-local`** (4): a 4-byte local assigned `v = F(..);` with F returning an 8-byte
  integer, whose register reaches a 64-bit read or a widened parameter: retyped to F's
  return type (not when its address is taken).
`RG_PROTOS_NO_WIDE=1` disables the three (ingest bisection, the test control).

The bug it fixed: `ActCfgTableFindCallNameByFlags_2207b0(tbl, flags, (int)c->f568)`
compared the 64-bit action-call masks (`ActInfoCallGetMask_2310a0` returns s64, kept in an
`s32 a`) against the chara's 64-bit state flags. Cut to 32 bits, the global action
`#èˆ¹å…¥` matched for every chara every frame; the port restarted it every frame, its time
event ran `CharaCmdSetShipPos_22d430`, and the leader was moved out of the first
battle's circle (BRINGUP.md). The census (`out/bringup-checkpoint/widecensus.py`,
`widecensus.tsv`) lists the same class over every listing: the two connection-mask
lookups of CharaTryStartAction_216700, `ObjSpawnFromDef_3bb5e0`, `CharaResRequestMon_1f29d0` /
`CharaResRequest_1f2d90`, `EventFireIntervalTriggers_3e0220` / `PlayTimeSplit_3d6350`
(64-bit play-time ticks into UModDi3 / U64ToDouble), `BattleModeUpdate_280220`'s
`BtlChgMenuGetResult_204ac0` result, `TreasureBoxPoolCollectInReach_3391d0`, the insect
board bounds. Fixture `tests/protos/fixture/src/main/listing/WideFlags_400c00.c`
(`protos.stage` checks, `protos.abi` runtime check, `protos.abi_control_wide` WILL_FAIL).

Also fixed in this session: three regexes in protos.py and two in portxform.py held a
literal backspace (0x08) where `\b` was meant (an earlier shell edit dropped a level of
escaping): the struct-by-value test for `u128` parameters, the f32 lane test of
`vcall-forward` (one more forward: 289 -> 290), and the const/volatile strip of the
bitfield-gcc member parser.

## Rules added 2026-10-17 (first-battle fix, BRINGUP.md "2026-10-17")

Same carrier stage (`_infer_wide_carriers`, `_wide_inline`), same switch
`RG_PROTOS_NO_WIDE`:
- **`wide-ret`**: a C definition returning a 4-byte integer whose listing's `$v0` at
  the return (after the `jr $31` delay slot) is an 8-byte call result or an 8-byte
  parameter, and some caller's listing reads that result whole (a compare / `slt` /
  `sd` on it, an 8-byte parameter or a callee that reads it whole, or the return value
  of an 8-byte definition): the return becomes `long long` (unsigned kept). Candidates
  are labelled `cnd:` in the callers' `wide_flow` and promoted between iterations.
- **`wide-local`** now also retypes accumulators (`v |= F64(..)`, `^=`, `&=`) and
  locals whose value is the `$v0` of a definition that returns 8 bytes.
- **`wide-inline-param`**: a listing-less static helper (mwcc inlined it, so retail kept
  the caller's 64-bit register) receives an 8-byte integer parameter of its caller by
  name in a 4-byte parameter: retyped to an 8-byte integer. Inside such a helper, the
  parameter passed by name to a listed definition whose listing reads all 64 bits
  widens that parameter (`wide-param`, detail "inlined helper ..."); the site-based
  `wide-param` cannot see calls inside inlined helpers.
- `asmflow.wide_flow` reports `('ret', ..)` after the delay slot (`jr $31; sltu` bit
  tests and `jr $31; dsra32` sign extensions are not wide).

The bug: `ActDataCnctGetCmndMask_2274c0` (declared `s32`) returns
`ActInfoCmndGetMask_2311f0`'s 64-bit action-command mask untouched; the connection
lookups (`ActCfgTableFind{Normal,}CnctByMask`, their inlined `Try1`/`Try2`/`find_item`/
`find_mitem`/`try_link` helpers with `u32/s32 mask`, `ActDataFindCnctByMask_225c00`,
`CharaTableDataFindTimeCnctByMask_226640`) test `(mask & M) == M`. A mask in the high word
only cut to 32 bits is 0 and matches any state: the leader's CharaTryStartAction started
a connection action at the first battle that retail never starts, every frame. Census:
`out/battle/wideret_census.py` (`wideret_census.tsv`); fixture
`tests/protos/fixture/src/main/listing/WideRet_400d00.c` (`protos.stage` checks
`wide-ret*`, `wide-inline-param`; `protos.abi` runtime check).

## Rules added 2026-10-17, part 2 (battle tutorial, BRINGUP.md "2026-10-17 (battle tutorial)")

- **`ret-zext`** (20 sites): a call to a definition returning a signed 4-byte
  integer whose caller's listing zero-extends `$v0` before anything else reads it
  (`dsll32 X, $2, 0` ... `dsrl32 Y, X, 0` on the straight-line path after the delay
  slot, every paired jal) gets `((unsigned int)F(..))`.  The unit's own view said
  `u32`; the unified prototype (the definition's `s32`) made `(u64)F()` / `hi | F()`
  sign-extend.  `ParseFlagNames_1ca700` builds every 64-bit action prmt / attr / call /
  cmnd mask from the ActCfg text in two 32-bit halves (18 sites in ActTimeAttr,
  ActDataAttr, ActTimePrmt, ActDataPrmt, ActInfoCall, ActInfoCmnd, ActInfoStart,
  CharaTableMtnDefineEnd); a half with bit 31 set came out as `0xFFFFFFFF` in the
  high word.  The Hooded Man's battle-stance attr (`0x80000000`) then carried
  `0x170000000000` (all four no-collision bits), CharaCalcBoundsRangeMaybe_237f20
  returned 0, no ground was found, and his tutorial AI script took the "not near
  ground" branch.  Plus 2 RevelationBoardGetCells_3eb510 sites (pointer arithmetic).
  `RG_PROTOS_NO_ZEXT=1` (and `RG_PROTOS_NO_WIDE=1`) disables it.  Census:
  `tools/bringup/zext_census.py` (every zero-extended call result over all listings:
  ParseFlagNames 18, RevelationBoardGetCells 2, DoubleToUInt 4 (already unsigned),
  sceGifPkCloseGifTag 1 (SDK, no C definition)).  Fixture
  `tests/protos/fixture/src/main/listing/ZextFlags_400e40.c` (`protos.stage` checks
  `ret-zext` and a sign-extending control; `protos.abi` runtime check; fails in
  `protos.abi_control_wide`).

## Rules added 2026-10-17, part 3 (first hit, BRINGUP.md "2026-10-17 (first hit)")

- **`vslot-lane`** (2 sites, `_vslot_lanes`, before the def-widen fixpoint): EABI
  passes GPR and float arguments in separate register files, so `F(void *, float)` and
  `G(void *, H *, float)` can share a vtable slot (F never reads `$a1`). On i686 the
  float is F's 2nd stack word, but the slot's callers push `(this, h, f)`. Families:
  data tables (`data2c_*.c`, `(u32)&Fn` entries) sharing >= 2 identical (slot,
  function) pairs; in a family slot, a definition whose float parameters follow fewer
  GPR parameters than a sibling definition takes in total gets `int rgp_aN`
  inserted in front of its first float (direct callers then fill the lane through the
  missing-* rules). `manual-vslot-lane` when the definition also has retyped/added
  parameters or GPRs after its floats. `RG_PROTOS_NO_VSLOT=1` disables it.
  Sites: `NodeRefObjUpdate_318af0` and `JudgeObjectStep_314360` (slot 2 = Step of the
  judge-object vtables D_00471AA0..D_00471D00, next to
  `NodeRefObjMotionGateUpdate_318230(void *, int, float)` and
  `ProjectileMoveStep_317db0(void *, void *, float)`; `HandleRegistryStepAll_314e10`
  calls the slot as `(this, grid, dt)`). Their `dt` was the grid pointer read as a
  float (~1e-38): judge lifetimes never ran down, the per-frame body judges of every
  chara piled up, the judge pool (HandleHeapPoolAlloc, 0x8C0-byte objects) ran dry
  and every attack judge spawn (CharaSpawnClsnJudge_227c70 ->
  NodeRefObjMotionGateCloneAndRegister_228690) got no object: no attack shape, no
  BattleApplyHit, no hit ever landed. Census: `tools/bringup/vslot_census.py`
  (post-stage prototypes; with `--min-shared 1` unrelated classes merge and it adds
  5 false rows). Fixture `tests/protos/fixture/src/main/vslot/VStep_401000.c` +
  `src/main_data/data2c_0048000{0,20}.c` (`protos.stage` checks; `protos.abi`
  calls both slot entries as `(this, h, dt)`; `protos.abi_control_vslot` WILL_FAIL).
- **Native SDK prototypes as providers**: `src/sce/vu0/sce_vu0.h` joins
  `PROVIDER_HEADERS`. The decomp's SDK units are `asm`, so the stage had no truth for
  libvu0 and left the game's views alone; `GuardWaveEffectStart_2d5ad0` declared
  `sceVu0CopyVector(void *)` and retail passes its own `$a1` (the position) as the
  source untouched: the native `sceVu0CopyVector(dst, src)` read a stale stack word and
  the first guarded hit faulted. Provider headers may now use array typedefs
  (`typedef float sceVu0FVECTOR[4] ..;` parameters are read as `float *`). Effect: 2
  `missing-passthrough` (GuardWaveEffectStart, HatenaMarkProximityCheck_3452b0), local
  libvu0 declarations replaced by the header (~120 files, decl-removed/-patched,
  ret-cast), `sceVu0InversMatrix`'s void value read as 0. Census of what is left over
  every `src/sce/**/*.h`: `tools/bringup/sce_arity_census.py` (sceMcClose/sceMcEnd
  extra arguments only, harmless on cdecl). Fixture: `FixCopyVector_13c480` in
  `fixture/providers/crt.h` + `src/main/arity/FixCopyUser_13c4e0.c`.

## Rules added 2026-10-18 (ABI sweep + run state, BRINGUP.md "2026-10-18 (b)")

Census: `tools/bringup/abi_census.py [--game DIR] vvz args sret` classifies the
`void-value-zero`, `manual-call`/`manual-decl`/`missing-zero`/`manual-missing` rows and the
u128 local views against the retail listings (`asmflow.exit_class` / `reg_after_call`,
helpers added to asmflow.py); output `out/abi_census/*.tsv`. Before -> after this batch:
void-value-zero 883 (caller listing reads $v0 and the callee forwards a value: **22**
BUG-pass, 706 dead, 78 returned, 76 noasm, 1 undef) -> 798 (1 BUG-pass:
`InsectronRewardLookupMaybe_3e84f0`, a virtual tail through a base-class method; 1 undef:
`AudioDecEndPut_1d24c0`, nothing to forward); u128 views of scalar definitions 3 -> 0;
manual-call 166 -> 145, manual-decl 190 -> 135. Fixtures `tests/protos/fixture/src/main/abi2/`
+ `src/overlays/normal/x/normal_ResReady_4ec100.c` + `src/main/ovl/TransReady_203870.c`;
`protos.stage` checks, `protos.abi` runtime checks, new control `protos.abi_control_abi2`
(`run_stage.py --fault abi2`, all five switches below off: every new check fails).

- **`def-v0-return`** (51, `_v0_listing`, switch `RG_PROTOS_NO_V0RET`): a void C definition
  whose callers read its value, where retail's listing returns a call's result at EVERY exit
  ($v0 after each `jr $31` is the RET of a jal, or the exit is a tail `j`) and every such
  jal/j pairs with one C call of a value-returning definition. The calls become
  `(rgp_v0 = G(..))`, every `return;` / the end returns `rgp_v0`, GNU `return (void)e;`
  becomes `return (e, rgp_v0);` (C++: the assignment is spelled through `(T)(long)`).
  Shapes `_tail_call` did not see: one tail call per branch (insect_InsectBattleIsSideAi_4f1950,
  insect_InsectAiGetPiece_5228f0), `G(..); return;` early exits (MapGetNorthAngle_1e36b0),
  a conditional second call with the first call's $v0 live (insect_InsectStoryGetRankTierMaybe_510420).
- **Overlay-import tail value** (switch `RG_PROTOS_NO_IMPORTTAIL`): the tail fixpoint skipped a
  MAIN->overlay import name; it now takes the overlay definition's evidence. Fixes the
  transporter class for every `*MenuResReady` thunk: MenuTransIsReady_203870 (route
  override retired), HelpMenuResReady_2032b0, InsectEntryMenuResReady_203390,
  ShopMenuResReady_203760, ThinkMenuResReady_203650 (each read 0 forever: those menus
  would never open).
- **`u128-view`** (4, `_u128_views`, switch `RG_PROTOS_NO_U128VIEW`): a local view returning
  or taking u128/s128 where the definition has a 4/8-byte scalar (one EE register either
  way; i686: sret pointer / 16 stack bytes) gets kind `o` slots, so the ordinary rules bind
  the call to the definition (C: header prototype; C++: patched).
  ActionPacketInitBattleDefeat_3e33e0 (route override retired) and
  EvMapObjFindTargetInFrontMaybe_2e9560 (`MapDataGetId_1e7bd0`, `EvMapObjGetId_366b70`,
  `TargetRefSetMapObjKind8_2e63f0`: the "examine target in front" ids).
- **extern "C" block linkage** (parse_file, switch `RG_PROTOS_NO_EXTERNC`): a C++ definition
  first declared inside the file's `extern "C" { }` has C linkage ([dcl.link]); it was
  treated as C++ linkage, so every C caller was `manual-call` with its own (wrong) view.
  HatenaMarkListStep_344ee0 now gets `missing-passthrough` of its list (route override
  retired). Side effect: such definitions enter game_protos.h; an override that keeps an
  incompatible local declaration of one no longer compiles (CameraObjApplyInputMaybe_1619e0,
  see BRINGUP.md).
- **`ee-round-floor`** (1, `_ee_round`, switch `RG_PROTOS_NO_EEROUND`): `(E + 12582912.0f) -
  12582912.0f` (or 8388608.0f) -> `__builtin_floorf(E)`. The EE FPU rounds toward zero only,
  so retail's trick is floor(); SSE rounds to nearest. AngleWrap_1cbf30: the run-state bug.
  Census of the corpus C and every listing (`lui` of 0x4B40/0x4B00 constants): this is the
  only instance (DrawListResetClipRangeMaybe_148040 uses 2^24 as a bound, not a rounding).
- **Provider prototypes**: an override-defined name that no corpus file declares and that is
  not a game symbol (no `_xxxxxx` suffix, e.g. the file lane's `rg_FileReq*`) is no longer
  put in game_protos.h (it only conflicted with the overrides' own declarations).

Left (not a rule yet): the small-aggregate class -- `HandleTableGet_1a1d50(Table *, Handle h)`
(a 4-byte union by value is one GPR on the EE and 4 stack bytes on i686) keeps the
definition out of the header, so its four EffDef* callers that omit the handle (retail passes
their own `$a1`) stay `manual-call` with a missing argument (`abi_census.py args`:
MISSING-entry 4); same family HandleTableGetDeref / EffInstDestroyByHandle / EffHdlRemove
(~30 manual rows). **2026-10-25:** the short ones are rule `short-agg` (below); the rest pass
the handle as s32, ABI-identical to the 4-byte union.

## Stage rules added 2026-10-18 (UB-audit lane, docs/UB-AUDIT.md)

Not protos rules, but stage changes of the same re-ingest; recorded here so the rule
history stays in one place.

| Stage / rule | What | Census |
| --- | --- | --- |
| `vu0frame` (new stage, tools/stages/vu0frame.py, after `dialect`) `frame` | `RG_VU0_FRAME;` after the `{` of every function body that names the VU0 model or calls a frame helper: the register file becomes a function local (docs/NATIVE-CPU.md section 4) | 145 functions in 144 files |
| `vu0frame` `helper` / `helper-call` / `helper-decl` | a `static` model function called from another function of the same file takes the caller's file: first parameter `rg_vu0_state *rg_vu0_p_`, `&rg_vu0` at each same-file call, body bracketed with push_macro/`#define rg_vu0 (*rg_vu0_p_)`/pop_macro; forward and block-scope declarations (`void ScaleMul(void);` inside FrameCalcWorldMatrix) get the parameter | 38 helpers, 53 calls, 10 declarations |
| `vu0frame` `info-helper-addr` | a helper whose address is taken keeps its own frame (review item) | 0 |
| `hwaccess` `overlay-data` (changed) | `*(T *)A` with A in an overlay's data/bss -> `(*(T *)((unsigned char *)sym + off))` + `extern unsigned char sym[];` in the stage prefix (was `RG_OVL_DATA(T, ovl, sym, symaddr, off)`) | 3 sites |
| `datareloc` `short-main-ptr` (new) | in an s16/u16-typed data2c object, a 4-aligned word INSIDE (offset > 0) a MAIN symbol the corpus names (a bss label <= 0x40 bytes below it, or a named data object) becomes a relocation: `D_004807F8` = 0x00484A38 = `D_00484A30` + 8 -> `(u32)(data2c_main_bss + 0x39B8)` (the FACTORY menu Slot pointer, BRINGUP.md 2026-10-18 (d)); retires `overrides/src/main_data/data2c_00480390.c` | 1 site; `short-main-candidate` rows list all 13 MAIN-range words in short objects (12 stay: short pairs such as (24, 74) = 0x004A0018, and D_0047EAC8's (0, 24, 48, 72) table, which reads as the exact start of D_00480030) |

## Inputs outside the snapshot

The provider table makes `game/` depend on the port tree: `overrides/**`, `missing/**`
and `src/crt/crt.h` (`PROVIDER_DIRS` / `PROVIDER_HEADERS` in protos.py).  Re-ingest
after changing a provider's signature; `ingest.py --check` only re-hashes.  An override
of a *unit* file (one that includes game_protos.h) must not keep a local declaration
that conflicts with a provider prototype (`SysCalcFreeHeapMaybe_15e1d0.c` was updated
to the staged spelling for `Malloc_130dd8`/`Free_130e30`).

## Tests (`tests/protos`, `ctest -L protos`)

| Test | Checks |
| --- | --- |
| `protos.stage` | the stage over `tests/protos/fixture` (a small corpus with its own provider header and override) is idempotent and makes the expected decisions: provider and override prototypes in the header, per-site import binding (and no header prototype for it), hosted-unstatic, addr-alias, double-param/-local, ret-bitcast, def-tail-vcall-return, missing-passthrough, lane reorder |
| `protos.stage_control` (WILL_FAIL) | the same with the provider table removed |
| `protos.abi` | the staged fixture linked against native providers: `s64`/`s32`-typed soft-double callers get the right double bits, a void-declared float callee called 24 times leaves no x87 garbage, `MatFromQuat`-style missing argument passed through, `MotionListSetRateById`-style float slot remapped, hosted static and address alias link and run, double-param compare wrapper, a void definition ending in a virtual call returns the call's pointer |
| `protos.abi_control_providers`, `protos.abi_control_bits`, `protos.abi_control_wide`, `protos.abi_control_vslot` (WILL_FAIL) | the same fixture staged without the provider table / with double handled as an 8-byte integer (no bit transport, no carriers) / without the 64-bit carrier rules / without `vslot-lane` |

## Tools

- `tools/stages/protos_pre.py <pkl> --out DIR`: protos alone on its ingest input (dumped by
  `RG_INGEST_PRE_PROTOS=<pkl> tools/ingest.py --out <scratch>`); with
  `RG_PROTOS_SB_CENSUS` + `tools/census/stackblock_census.py` = the stack-block census
  (`--compare OLD.tsv` = verdict transitions); `tools/census/sbpadcheck.py <pkl>
  <PROTOS.tsv>` = a padded block's own `$sp` accesses in the pad; `tools/census/sblisting.py
  <pkl> NAME..` = listings as the stage parses them (CFG indices = escape `insn`).
- `tools/stages/run_protos.py`: applies the stage to a copy of `game/` under
  `out/protos-test/` and prints the per-rule census.
- `tools/stages/measure_protos.py --mode raw|naive|staged [--strict] [--sample N]`:
  clang `-fsyntax-only` over the sources, prototype-related errors by class
  (`out/protos-measure/<mode>.tsv`).  `naive` = the header force-included with no
  rewrites.

## Rule added 2026-10-18: `retwiden` (play-test 2, BRINGUP.md "User play-test 2")

A separate ingest stage, `tools/stages/retwiden.py`, after devirt. A definition returning a
1- or 2-byte integer (`u8 s8 u16 s16 bool char short` ..) whose name is used anywhere other
than as `F(` (vtable words `(u32)&F`, callback arguments, function pointers) returns the
4-byte type of the same signedness, every `return E;` becoming `return (T)(E);`; its own
file's declarations follow. Reason: the EE callee leaves the narrow value extended in
`$v0`, so a caller reading the slot through a wider type (`VCM0(s32, 0x3D0)` on
`u8 UnitHasParent_3a3600`) gets the right value; i686 returns only AL / AX and the upper
bytes of EAX are garbage. Direct calls are already typed by the unified prototype.
400 definitions at the 675c07fe pin. The bug it fixed: `BattleRecordDefeat_3a3410` never
recorded a defeated enemy, so battles awarded no EXP, money, drops or bestiary counts.
`RG_PROTOS_NO_RETWIDEN=1` disables it; tests `protos.retwiden` (+ `_control`, WILL_FAIL).
Dry run / listing on game/: `python tools/stages/retwiden.py --list`.

## Stack-block census and rule fixes (2026-10-19, BRINGUP.md "2026-10-19 (a)")

Review of every `info-stack-block-unresolved` row (680) and every `manual-stack-block` row
(72) after the 3081e0 / 228f80 bugs. Scripted, not read by hand:

- `RG_INGEST_PRE_PROTOS=<pkl> python tools/ingest.py --out <scratch>` dumps the protos
  stage's exact input; `python tools/stages/protos_pre.py <pkl> --out <dir> [--files RX]`
  re-runs protos alone (~3 min instead of ~5, same PROTOS.tsv).
- `RG_PROTOS_SB_CENSUS=<jsonl>` (stage switch): one JSON line per stack-address call
  argument (callee listing, lane, sp offset, extent, escapes, listing constants), per
  definition's locals (type, size, offsets) and per group outcome.
- `python tools/census/stackblock_census.py <jsonl> --pkl <pkl> --out census/stackblock_sites.tsv`
  re-measures every unsettled site (call depth 12) and resolves function-pointer targets:
  virtual calls on the local itself (the vtable its ctor chain stores at sp+off+V, read
  from the retail ELF, slot S -> method listing), virtual calls on another object (every
  vtable stored at offset V anywhere, slot S, <= 40 candidates), callbacks stored in an
  object field (every `sw <%lo(F)>, X(base)`, or a reviewed source list
  `CALLBACK_SOURCES`: the Variant change callback = the ScriptFn* handlers of
  ScriptEmitCmdHandlerMaybe_3da110), function pointers passed as call arguments (the
  call site's constant), MAIN calls into overlay addresses (every overlay's function
  there), and two reviewed bounds (`REVIEWED`: MSL string inline buffer, cfg-VM command
  handler args). Verdicts: OK / OK-block / BUG: under-sized local / BUG: split block /
  needs-human; rows of files replaced by an override are prefixed `override:`.

Census (game/ re-ingested 2026-10-19): 798 rows = 466 OK, 253 OK-block, 0 BUG, 79
needs-human (25 virtual calls whose vtable is not found or has > 40 candidates, 17 cfg-VM
runs (default handler at +0x404 unresolved), 13 callback fields with no stored target, 12
script-native dispatch, 12 function pointers from elsewhere; 3 of them in overridden
files), 2 size unknown. Before the stage fixes the same tool reported 3 BUG rows (below)
and ~490 needs-human.

Stage fixes (`tools/stages/asmflow.py` Flow.extent, `tools/stages/protos.py`):

1. **Switch callees.** A `jr $r` jump-table dispatch (a `%lo(jtbl_..)` just before) was a
   dead end: the case bodies were never analysed (VariantGetS16_36fcc0 reached 4 bytes
   instead of 16). Its successors are now the labels and every instruction nothing else
   reaches (jtbl targets carry no label in the listings): `CFG.switch`, `CFG.cases`.
2. **Length-driven callees** (`Flow.LEN_ARG`: memcpy/memmove/memset/memcmp/memchr/
   strncpy/strncmp/Strncasecmp/Md5Update): the reach is the length argument when it is a
   constant (listing term at the call, or a tracked constant inside a callee), not the
   unroll width of the word loop (memcpy reported 40 for `memcpy(&tmp, p, 4)`, memset 32
   for 0x54); a data-dependent length is an escape (`lenvar`). NUL-terminated string
   arguments (`Flow.STR_ARG`: strlen/strcmp/strcpy/strcat/Sprintf ..) are assumed to stay
   inside their C object. Net: 25 blocks that only existed because of those unroll widths
   are gone (DamagePopupDraw*, the menu `tmp`/`buf` blocks, FileBuildDevicePath ...) and
   extents that were under-measured (memset 0x54 reported as 0x20) are now right.
3. **More precise dataflow**: values stored to memory and loaded back from the same base
   + offset (sp slots survive calls; IterInit_370170 stores the container and reloads it
   for the virtual count), the pointer's null tests (`beqz ptr` cannot be taken: a stack
   address is non-zero), constants, function-pointer facts (`fld`/`vt`/`ofld`/`ovt`/`arg`/
   `sym`) recorded on the escapes, interior entries (`func_0010ACB8` = sceVu0RotMatrixZ's
   second entry; Flow name `img:owner@OFF`), call depth 4 -> 8 (`RG_PROTOS_SB_DEPTH`).
4. **Header/class layouts** (`tools/stages/clayout.py`): unions, anonymous nested
   struct/union members, GCC bitfields, C++ classes without bases/virtuals (member
   functions, access specifiers skipped), enums and typedef aliases. CVar (0x38),
   EventCastSetPosition_258a50's locals: now sized (one more block).
5. **Trailing pad**: a block slot past every placed local that a callee *writes*
   (write extent, `Flow.rw_extent`) is padded instead of declining the block. Slots only
   read stay holes (CameraBaseLookAt_15fae0's 4th row is still the override's).
   **Bug fixed:** ScriptCmdEffectGetParamFloat_32d940 declared `s32 sp40[4]` but
   EffectCopyHandle_2dd3b0 stores a 20-byte effect handle into it (and
   EffectGetParamFloat_2e0460 reads it back): 4 bytes past the array on the port.

6. **Struct locals and member arrays** (found by the stack-guard census run, below): the
   own-size test only knew primitive locals, so a struct local smaller than its callee's
   reach was never grouped, and an array member passed without `&` (`t1.m08`) was not a
   site at all. Now: own size from the type layout (minus the member offset for `&x.f` /
   `x.f`). **Bugs fixed (+47 blocks):** the variant-pool scope object (`Query`/`Big`, C
   0xE08 bytes, ScriptExecOpStream_3dffa0 / VariantPoolReset_3e01f0 reach 0xE0D) in
   EventFireTriggers_3e2660, TreasureBox*, MapObjParamRefreshConds*, WorldDataCmdRunOpStream*,
   PtalkFindPairRow (override, below); DrawBufPairInitMaybe_15dc50 `Rec t1, t2` (MemStackCtor
   writes 0x54 bytes into the 0x50-byte member: 4 bytes into the next record); model desc
   records (0x88 in C, 0x90 written: EffectEntryBuildChr, EventCastObjLoadInfoCfg,
   InsectCageLoadFxModels, Character2NewFromInfoCfgWithColl*, ...); f32/s32 locals
   receiving 8-byte pairs (BloomExtractBlur, CBlurTexBlur, ScreenColorFilter, MenuWinDraw
   `al`), and more (census rows `OK-block`).
7. A hole that a C local named for its retail slot (`spNNN`, `sp60q`) fills is placed by
   that name, BEFORE the trailing pad of fix 5 (the pad alone was a regression:
   CollFrameTreeCalcBounds_16be80's recursive call writes {lo, hi} through `&sp50` into sp50
   and sp60; padding slot 0x10 made the C read a zero sp60 and changed the save2_battle2
   fight, BRINGUP 2026-10-19 (b)). Placed: CollFrameTreeCalcBounds_16be80 sp60,
   Character2DrawWithOwnLightMaybe_1ae720 sp70 (one light state with sp60q),
   ScriptCmdEffectGetParamFloat_32d940 sp5C. Remaining padded blocks (no named local in the
   pad): ParamScriptMotionEventCmd_1af180 (x2), ParticleEmitterSpawnMaybe_1a8ad0 `rot`
   (MtxMul writes a 4th row), InsectApplyItem_3cf310 `rec`, MenuItemUseTargetState_2ae490
   `v80`; a pad is still wrong if retail kept a differently named, never address-taken local
   there -- review list.
8. A group whose local is used inside a macro body or redeclared in a nested scope is
   declined (`manual-stack-block` "appear in a macro"): the use-by-use rewrite cannot reach
   it (PtalkFindPairRowMaybe_3e2160's `TRY(X)` spells `&big`).

9. **All 8 EABI argument registers** (`$4..$11`, was `$4..$7`) in Flow.extent and the stage's
   lanes: AabbTransformBounds_13c710 hands its {lo, hi} to MtxTransformPointsMinMax_13c780 in
   `$8/$9`, so NodeObjGetWorldBounds_194420's reach was 0. **Bug fixed:**
   MapAreaModelAddDrawOffRect_189300 `u8 b90[16]` / `bA0[16]` (one {lo, hi} pair, found by the
   stack-guard census; placed through the generalised name rule: any lower-case prefix +
   hex offset, candidates sharing the anchor's prefix), BtlEffSetRowFindMatchingRec_3fb3c0
   (variant pool).
10. `typedef struct {..} NAME __attribute__((aligned(N)));` (attribute after the name) is now
    found. **Bug fixed:** CharaMoveHangMaybe_234920 `M3 n` (3 rows) + `V4 w` = the 4-row
    matrix FrameCalcWorldMatrix / MtxInverseAffine / MatMul write and read.

Overrides added: `overrides/src/main/event/PtalkFindPairRowMaybe_3e2160.cpp` (`Big` gets
the retail 0x18-byte tail) and `overrides/src/overlays/factory/factory/factory_FactoryStep_5069e0.cpp`
(`VP8 sp1D0` + `sp1F0` as one block: FactoryPartGroupStep_4fea10 / BeltTileGroupSetVisible_4ff110
read +0x20 flag and +0x24 Def pointer = sp1F0; the "Def pointer is the small integer 5"
FACTORY fault of BRINGUP 2026-10-18 (f) -- an inline struct type the stage cannot place).

Determinism: the stage output is identical under PYTHONHASHSEED=1 and 2 (protos_pre, whole
PROTOS.tsv + staged files). EventCastSetPosition_258a50's decision changed between ingests
because of fix 4 (its `spA0`/`spB0` types became sizable: "sizes unknown" -> block), not
ordering.

Final counts (game/ 2026-10-19 ~06:00, tree 2fa6d3cb..): stack-block 114, manual 9 (7 iterator
pairing, PtalkFindPairRow macro -> override, CameraBaseLookAt hole -> override), unresolved 559.
Census `census/stackblock_sites.tsv`: 933 rows = 469 OK, 357 OK-block, 0 BUG in stage-built
files (4 `override: BUG` rows = the two overridden files above), 103 needs-human (28 virtual
calls with no / too many vtable candidates, 26 callback fields with no stored target, 21
function pointers from elsewhere, 17 cfg-VM runs, 12 script-native dispatch, 3 in overridden
files), 2 size unknown.

Earlier counts (after fixes 1-5): stack-block 86 -> 64, manual-stack-block 72 -> 7 (all 7 are "cannot place": the
C iterator calls pair with the wrong listing jals after a loop rotation; each iterator is
8 bytes and every callee reaches 8: harmless), info-stack-block-unresolved 680 -> 532
(rows now include data-length `lenvar` escapes). Stage time: stack rule ~15 s -> ~25 s.
Fixture `tests/protos/fixture/src/main/listing/PadBlock_401600.c` (trailing pad, switch
callee, memcpy length) in `protos.stage`.

**Stack-guard census build** (diagnostic, never shipping): `RG_PROTOS_SB_GUARD=1` at ingest
(into a scratch tree) puts every address-escaping local the stage did not block inside a
16-aligned byte array with 16 canary bytes before and 48 after
(`__attribute__((cleanup(rg_sbguard_chk)))`); configure with
`-DRG_GAME_TREE=<scratch tree> -DRG_SBGUARD=ON` (src/game/sbguard_census.c; overruns
logged once per site to `$RG_SBGUARD_LOG`, default `sbguard_census.tsv`). C++ locals of
class types (possible constructors) are not guarded. Writes past an object are seen,
reads are not.

## Stage added 2026-10-19: `wideret` (play-test 2, gun delay)

`tools/stages/wideret.py`, an ingest stage **before** protos (so the unified prototypes and
the header follow it). A MAIN definition typed with a 4-byte integer return whose retail
`$v0` at `jr $31` is a 64-bit value (asmflow `wide_flow`: `ld` / `lq` / `dsll32` results
and calls to 8-byte-returning definitions, iterated to a fixpoint so chains are found)
returns `long long`; in its file the 4-byte locals assigned or `|=` / `&=` / `^=`
accumulated from a wide call or a wide local (fixpoint), and a listing-less static helper
whose value reaches such a local or the return, become 8-byte too. The protos stage's own
`wide-ret` handles one level (a 4-byte definition returning an 8-byte call result that a
caller reads whole) and no accumulators or helpers.

The bug it fixed: the ActCfg PENDING prmt / cmnd mask chain
(`CharaTableDataCollectPendingPrmtFlags_2267f0` -> `ActCfgTableEvalPendingPrmtFlags_221380`
+ inline `applySubs`, `..Refs_221040`, `ActCfgTableEvalNormalPendingPrmtFlags_2217a0`)
returned s32; retail ORs and returns all 64 bits. `CharaActionUpdateMaybe_215ca0` keeps the
command flags (Chara +0x568) across an action frame only through that mask, so the battle
command bits 32-63 (SQUARE gun 1 << 56, CROSS sword 1 << 55, ...) pressed during an
action's recovery were dropped instead of buffered. 10 definitions at the 675c07fe pin
(also `PlayTimeSplitFromHandle_3d6220`, `SavePlayTimeSplit_3eebf0`, and four the protos
rule widened anyway). `RG_PROTOS_NO_WIDERET=1` disables it. Census / dry run:
`python tools/bringup/wideret_census.py` (post-protos game/), `python tools/stages/wideret.py`.

**Stack-guard census run (2026-10-19, `out/sblock/guardexe`, 4,928 guarded locals; the
census stage version before fixes 7-10):** `bootcheck.py --all` (29 cards) + the full golden
route (power-on -> saved 31,700) with `RG_SBGUARD_LOG`. Hits (all writes past the C object,
all now handled by the stage): EventFireTriggers_3e2660 `q` (bytes 3592..3596 of a 3592-byte
Query), DrawBufPairInitMaybe_15dc50 `t1`/`t2` (bytes 92..95 of an 88-byte Rec),
MapAreaModelAddDrawOffRect_189300 `b90` (bytes 16..31 of 16). They led to fixes 6 and 9. Guard
exclusions (the dialect stage matches call text the guard would rewrite): locals in a
`wide-shift` (`F(..) << 48`) or `arg-order` (`F(G(&x), x)`) statement, names used in a macro
or redeclared in a nested scope, C++ class-typed locals. Census-build artefacts seen and fixed
in the guard pass, not in game/: LoaderReleaseById_1cd340 int3 (wide-shift), MsgTableParseText
runaway (arg-order `len`).

## Stack-block: function-pointer resolution in the stage (2026-10-24, BRINGUP-HISTORY "2026-10-24 (sblock2)")

The census classifier's function-pointer resolutions moved into the stage, so a stack
address that reaches an indirect call is measured by the stage itself (it was a lower
bound, `info-stack-block-unresolved`). `tools/stages/sbresolve.py` (`Resolver`, used by
`protos._stack_blocks` through `_sb_resolver()` and by `tools/census/stackblock_census.py`;
switch `RG_PROTOS_NO_SBRESOLVE=1`). Vtable and table words come from the game tree's
`src/main_data/data2c_*.c` u32 tables (by address, so interior labels such as
`D_00477600 = D_004775E0 + 0x20` work; overlay data is not in the tree, so an overlay vtable
keeps the site open). Target classes:

| Fact (asmflow escape `src`) | Targets |
| --- | --- |
| `vt` V,S: virtual on the passed object | vtables stored at that frame offset by the caller or the ctors it calls (`vptr_stores`, delay slots applied first), carried into nested callees at the same object offsets |
| `dsym` D,o: `lw f, o(%lo(D))` | the one data word (CameraObjCtor_177430 calls its vtable directly) |
| `dtbl` D: `%lo/%gp_rel(D)` + index | every function of table D (AnimKeyEval* key interpolators D_0047DEF0 / D_0047DF00) |
| `ovt` V,S: virtual on another object | slot S of every vtable code stores at +V (V corrected by `this = base + d` at the jalr: EventObjMgrFindFirstHit_2e8560 calls node+0x10, vptr at node+0xEC = +0xDC); <= 40 candidates; a scanned set whose members disagree, or that holds vtables not in the tree, stays open and raises no extent |
| `fld`/`ofld` X: callback field | functions stored at +X anywhere (scanned), or `CALLBACK_SOURCES` (reviewed) |
| `arg`/`sym` | the call site's function argument |
| `JALR_SOURCES` | reviewed: ScriptCallWithArgs_302770's native = an entry of D_00452250 (event call table) or D_0044B7D0 (chara commands) |
| `REVIEWED_VTABLES` | reviewed receivers per (function, slot): chara/unit (CharaActBlownAway/Damage 0x20C), insect item D_00475B10 (InsectGetStats/InsectStatsGet), camera (CameraApplyAnimSample, CameraObjOrbitControl & co.), event objects (EventObjMgrFindFirstHit 0x24), map area model D_00470480 (SceneMapAreas/MapData collect, func_00187D40_e1) |
| `REVIEWED` bounds | MSL string inline buffer; cfg-VM handlers get the arg block inside the context (+0x428, 0x80 x 8 bytes; the default handler +0x404 is only ever zeroed) |
| port arity | a jalr paired with a C member call (`_vcall_pairs`, + the `vcall-forward` lanes, `_vcall_fwd`) that does not pass the pointer's lane: retail's register leftover, no port callee gets it (DataTableHashBucketFind, WeaponCombineLookup, InvAddItemCore/InvMoveItem ...); `REVIEWED_PORT_LANES` where an inline operator hides the pairing (NumPutPadOutput_1a4610 `Streambuf::overflow(c)`) |
| no listing | a port-only split entry (`entry_002d94b0_e6`) whose C definition takes fewer parameters than the lane |
| `fentries` | interior entries `func_XXXXXXXX_eK` resolved to `owner@OFF` |

asmflow additions (Flow.extent): `%gp_rel` symbols and indexed tables (`tbl`/`dtbl`),
`dsym`; fields of the passed object keyed by their offset whichever register holds the base
(`sw vt, 0xF0($4)` then `lw t, 0xF0($16)`); a field of an incoming argument is `ofld`; the
chains `fld -> vt -> lw` and `ofld -> ovt -> lw` re-read as a virtual of the pointed-to
object; a register known to be 0 decides `beqz`/`bnez` (PartyFindMember_3c2130's `$9`
reached a vcall only on the `obj == 0` path). clayout / `_type_size`: array dimensions with
literal arithmetic (`u8 pad1B4[0x228 - 0x1B4]`, `s32 sp[0x30 / 4]`) size the type (they made
the whole struct unsizable, so the stage never compared the reach).

Census (`census/stackblock_sites.tsv`, game/ re-ingested 2026-10-24): 965 rows = 595 OK,
366 OK-block, 4 `override: BUG` (the PtalkFindPairRow / FactoryStep overrides, unchanged),
**0 needs-human** (was 103). `--compare` of the 10-19 table: 97 needs-human -> OK, 1 -> not
listed (complete inside its local), 2 size unknown -> OK, 3 override needs-human -> OK.
Stage: stack-block 114 -> 118 (+6 real, -2 artefacts), manual 9, unresolved 559 -> 87 (each
listed in the census with its verdict). The census now also lists complete sites whose local
the stage cannot size (24, all OK by `REVIEWED_TYPE_SIZES`: MTX/VEC typedef arrays, a list
iterator, `WorldPosition : Vec4`).

**Bugs found and fixed by the rule** (all hidden by an unsizable type, so the reach was never
compared): CharaSysEncounterSetupMaybe_3a4440 `Desc4440 desc` (0x1C8 in C; CharaStateReset_3a79b0
writes to +0x1CE: 6 bytes into the next local); the model-desc class of fix 6 again
(InfoCfgParseAll_1afd00 reads +0x88..+0x90 of a 0x88-byte record: the next C local's bytes) in
EventCastCreateObj_24b8c0, MapObjLoadStep_1e0850, MenuItemModelCreate_2a7190,
MenuModelCreate_294330, factory_FactoryCursorModelLoad_504250. Artefacts removed:
ParamScriptMotionEventCmd_1af180's two blocks (`s32 sp[0x30 / 4]` was sized 4: the "pad" was
the array itself).

**Padded blocks reviewed** (`tools/census/sbpadcheck.py <pkl> <PROTOS.tsv>` lists a
definition's own `$sp` accesses in a padded slot): ParticleEmitterSpawnMaybe_1a8ad0 `rot`:
MtxMul_13d240 writes a 4th row; retail reuses that slot for a float stored only after the call
(a different C local, not live across it): pad correct. InsectApplyItem_3cf310 `rec` (Rec
0x10, InsectBreedRecReset writes 0x14; retail's next address-taken local starts at +0x18): pad
correct. MenuItemUseTargetState_2ae490 `v80` (V80 0x60, ExecInfoInit* write 0x6C; retail's
byte local at +0x6F): pad correct. ParamScriptMotionEventCmd x2: artefacts, gone (above).
CameraBaseLookAt_15fae0 stays the override's.

Caveat (scanned sets): "every vtable stored at +V" is only as good as the store scan; a class
whose vptr store the scan does not see (stored at a sub-object offset, by memcpy ...) is
missing from the set. That is why a disagreeing or partly unknown scanned set stays open, and
why the receivers above are reviewed by hand.

**Stack-guard census rerun (2026-10-24, tree `out/sblock2/gguard`, 7,385 guarded locals, exe
`build/sblock2g-i686`):** golden route power-on -> 31,800 and `bootcheck.py --all` (29/29
PASS): **0 overruns** (10-19: 3 sites, since fixed). Arming control: the same exe with
CharaSysEncounterSetupMaybe_3a4440's `desc` guarded instead of blocked (altlink) logs
`post overrun bytes [456, 461] (object size 456)` on ch01_salgin's random encounter -- the
CharaStateReset_3a79b0 overrun the rule now fixes, seen at run time.

## Rule added 2026-10-25: `short-agg` (+ the short-call check; BRINGUP-HISTORY "2026-10-25 (sweep)")

The class of the Insectron return-to-title bug 2: a C file's own local declaration of a callee
that is SHORTER than the definition, where the definition stays out of game_protos.h because
it takes a small aggregate by value (`HandleTableGet_1a1d50(Table *, Handle h)`, Handle a
4-byte union). The stage logged it `manual-decl` "count N vs M" and left the call short, so
the callee read a stale stack word on i686 (retail passed whatever the register held: the
caller's own entry `$a1`).

- **`short-agg-decl` / `short-agg-call`** (`_short_agg_sites`, switch
  `RG_PROTOS_NO_SHORTAGG`): C files only. When the view is a prefix of the definition by
  register class, every aggregate parameter of the definition is word-size (`_type_size` <= 4
  bytes in the definition's file: one GPR on the EE, one 4-byte slot on i686, so an `int`
  slot either way), and the enclosing functions have no by-value aggregate parameters, the
  declaration gets the missing slots (`int` for the aggregate, the definition's builtin
  spelling otherwise) and each call the missing arguments, chosen as for a header callee:
  MISSING_ARG_ASM, passthrough, the retail entry value, the listing; `missing-unused` passes 0.
  A site where any value is unknown (manual-missing / missing-zero) is left alone for an
  override: no guessed 0. On the 675c07fe corpus: exactly the 4 `HandleTableGet_1a1d50`
  effect sites (`EffDefDestroy_1a0a90`, `EffDefUnlinkByHandle_1a0040`,
  `EffDefDestroyInstancesByTag_19ff40`, `EffDefGetDurationByHandle_1a0a50`), each passing the
  caller's handle parameter (passthrough), the same code as the 2026-10-25 overrides, which
  are retired. Measured with `protos_pre.py` with and without the switch: no other staged
  file differs.
- **Not mechanical (overrides):** a struct returned BY VALUE through MWCC's hidden `$a0`
  pointer against a definition that takes that pointer as a plain first parameter AND a
  by-value iterator (`Iter NumPutBool_1b2860(Iter, Ios *, s8, s32)` from
  `OstreamWriteBool_1b2710`), and a short *definition* (the thunk `NumPutDoubleThunk_1b2840(void
  *, s32)` whose retail is a bare jump passing `$a0..$t0`) with its by-value-struct caller
  `OstreamWriteFloat_1b25c0`: three overrides under `overrides/src/main/libc/` (MSL iostream
  text writers of the motion-event debug dump; not on a tested path).
- **Check:** `tools/bringup/protos_deficits.py` lists every call the stage left short of its
  definition (`manual-decl` "count N vs M" with a `manual-call` site) and every by-value struct
  return view against a scalar / void definition (`ret Iter vs int`: sret); exit 1 while one
  has no override. ctest `protos.deficits` (over RG_GAME_TREE) + control
  `protos.deficits_control` (`--ignore-overrides`, WILL_FAIL). Now: 4 sites, all overridden
  (NumPutDoubleThunk, OstreamWriteBool, OstreamWriteFloat, RevelationBoardDrawSprite).
- Fixture: `tests/protos/fixture/src/main/abi2/HandleGet_401900.c` / `HandleUser_401940.c`
  (`protos.stage` "short-agg"; runtime `protos.abi` "short-agg: a word-size union argument
  the view dropped"); controls `protos.stage_control_shortagg`, `protos.abi_control_shortagg`
  (`run_stage.py --fault shortagg`).

## Manual rows closed (2026-10-25, BRINGUP-HISTORY "2026-10-25 (protos manual rows)")

Every row the stage leaves for a human now has a verdict, decided by tools wherever possible,
in **`census/protos_manual.tsv`** (`tools/bringup/protos_manual.py`; columns file, line,
callee, rule, verdict, evidence). Rules covered: manual-call, manual-decl, manual-missing,
missing-zero, manual-vcall-forward, manual-vcall-v0, manual-stack-block,
info-stack-block-unresolved, ret-class-convert, vararg-missing, void-value-zero,
info-bare-return, addr-alias-unresolved, info-vcall-set-args, info-vcall-unpaired.

| | rows | verdicts |
| --- | ---: | --- |
| before (game/ 07:06) | 1,318 | 96 stack-block rows verdicted by census/stackblock_sites.tsv; 1,222 open |
| first pass (same tree) | 1,318 | 12 BUG (6 call sites), 76 vcall rows + 4 vvz + 8 missing rows needs-retail-check, the rest OK |
| after (re-ingested) | 1,308 | **1,301 OK, 5 fixed-override, 2 fixed-rule, 0 BUG, 0 needs-retail-check**; 10 rows gone (fixed by the rules below) |

Evidence per class (tools, not reading):
- **manual-call / manual-decl:** `tools/bringup/protos_irabi.py` compiles the caller and the
  callee's definition (override / missing / provider header when that is the truth) with the
  build's own commands to LLVM IR and compares the lowered i686-windows-msvc signatures: stack
  words (integer / pointer / by-value aggregate bytes / float / double / over-aligned aggregate
  passed BY ADDRESS), return class and width (AL / AX / EAX / EDX:EAX / ST0 / sret). `--all`
  does the same for **every direct call of every compiled unit** (90k calls; summaries cached
  per unit under out/protos2/ir/sum): it found the five `ret-narrow-view` sites and the two
  missing/ views below, none of them a manual row. The control (`--ignore-overrides`)
  re-finds every call the 2026-10-25 overrides fix (NumPutDouble/Bool thunks, OstreamWrite*,
  RevelationBoardDrawSprite) on its own.
- **void-value-zero:** abi_census `vvz` + the callers of a `returned` caller
  (`asmflow.reg_after_call` over a reverse jal index) + "the C assigns the zero to a local it
  never reads"; 2 callers reached only through tables reviewed.
- **missing-* / manual-missing:** `tools/bringup/vslot_reads.py` (methods at a vtable slot and
  whether their listings read a register; `--fn` deep reads through jalr slots) plus PORT
  ARITY: the lanes are `rgp_aN` forwards and every port C definition at the end of the virtual
  chain takes fewer parameters (CharaTopPriorityStatusMaybe_3b6a80, the item count / AddCount
  slots, the 75 DataTable vtables), so 0 vs a dead register is never read on i686.
- **vcall rows (76):** a review per receiver class family (chara/unit, DataTable, items,
  cameras +0xC0, event objects +0xDC, container views, judge handles +0xB0); every extra
  register is an mwcc leftover the real receiver's method does not read; no `$v0` reader of a
  manual-vcall-v0 definition (out/protos2/vcall_review/verdicts.tsv).
- **ret-class-convert / info-bare-return:** retail callers never read the value (or read a
  register the callee never sets). **addr-alias-unresolved:** link-resolved names (data2c
  objects, kernel HLE, asm-unit interior labels).

### Rules added

- **`agg-view` / `agg-bits`** (`_agg_views`, switch `RG_PROTOS_NO_AGGVIEW`): a local view taking
  an aggregate BY VALUE whose alignment is REQUIRED > 4 (an `aligned(N)` attribute, or a
  GCC-packed bitfield run the dialect stage's `bitfield-gcc` rule will pin `aligned(8)`:
  `RGBAQ { u64 r:8 .. }`), where the definition has an integer scalar of the same size in that
  GPR lane. MSVC x86 cannot pass such an aggregate by value: clang passes its ADDRESS. The view
  slot becomes kind `a`, the call binds to the definition and passes
  `__builtin_bit_cast(<def type>, (x))`. **Bug:** `FontDrawGaiji_26dd50(.., s64 rgba)` got the
  pointer and a stale word as its colour from FontDrawText_26cdc0, FontDrawTextGradient_26c6e0
  and MesWinDrawGlyphs_271b70 (every gaiji glyph: button icons in message windows). Aggregates
  of natural alignment (a struct holding an s64) go by value in the same words and are left
  alone (protos_irabi `OK-bits`).
- **`u128-view` extra lane** (switch `RG_PROTOS_NO_U128EXTRA`): a u128 view parameter in a GPR
  lane the definition does not have, whose listing never reads that register, is kind `o` too,
  so the ordinary mapping drops it. **Bug:** EvMapObjPartStep_363ba0 viewed
  `VecSolveDistanceConstraint_364740(Vec4 *, Vec4 *, f32, f32)` as `(.., u128, f32, f32)`; on
  i686 the u128 was a pointer word in front of the floats, so the push-apart distance was the
  pointer's bits and the scale the distance.
- **`ret-narrow-view`** (switch `RG_PROTOS_NO_NARROWVIEW`): C++ only, the patched declaration
  keeps a POINTER or WIDER-NARROW spelling of a u8 / s8 / u16 / s16 return; the result is cast
  to the definition's type, then back (`((void *)(long)(unsigned char)F(..))`). 5 sites:
  EventSysUpdate_26ac10 (`ObjRecHasFlags6_1c3eb0(..) == 0` on garbage upper bytes),
  EvCmdEventStartMaybe_248450 (CharaGetId as a script argument), MapAreaRelease_1d9ee0
  (MapDataGetId), OstreamWriteCStr_1a1dd0 (IosGetFlags), MenuItemOpenState_2b2870 (`s16` view
  of a `u8`).
- **Object-like type macros** (parse_file, switch `RG_PROTOS_NO_TYPEMACRO`): `#define RT bool`
  style macros naming a scalar type resolve like typedefs. **Bug (the lead):**
  CharaCollClampFloorCeilingMaybe_2364e0 returned `RT` (= bool), an unknown type, so it stayed out
  of the header and CharaMoveCollideMaybe_234dc0 read its `bool` through an `s32` view:
  `!= 0` saw AL plus garbage upper EAX bytes (retail `beqzl v0`; clang returns `setcc al`), and
  could set the 0x1000 landing flag / x410 timer when the clamp found nothing. The definition
  is now in game_protos.h and the call gets `ret-narrow`.

Not rules (one site each): `overrides/src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c` (the
file's own view passed the size as u64 to `StringReplaceRange_1b3da0(void *, s32 x5)`: every
later argument one slot off; MSL num_put, untested path) and
`missing/src/main/sys/TaskStepJudgeObject_3135c0.cpp` (its `s32` views of the `s16`
CharaGetBaseActionMode_213830 / CharaGetId_214a80: `== 0` and ActorFindById on garbage upper
bits in the chara stomp judge).

### Checks (ctest -L protos)

`tools/bringup/protos_deficits.py` gained `--manual` (every manual row has a reviewed, non-BUG
verdict; `fixed-override` needs its override) and `--ir BUILD` (protos_irabi over the manual
pairs with the build's compile_commands.json; a BUG passes only when overridden or reviewed
OK). ctest `protos.manual` / `protos.manual_control` and `protos.irabi` / `protos.irabi_control`
(controls `--ignore-overrides`, WILL_FAIL). Fixture `tests/protos/fixture/src/main/abi3/`
(GaijiDraw / GaijiUser, PushApart / PushUser + listing, Low8Sum `#define RT u8` + C++ int and
pointer views): `protos.stage` checks, `protos.abi` runtime checks, controls
`protos.stage_control_abi3` / `protos.abi_control_abi3` (`run_stage.py --fault abi3`).

After a re-ingest: `python tools/bringup/protos_irabi.py` (manual pairs) and
`python tools/bringup/protos_manual.py` regenerate the table; a new manual row fails
`protos.manual` until it is reviewed (add a REVIEWED entry with listing evidence, a rule, or an
override).
