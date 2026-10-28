# Missing arguments still filled with 0 (protos `missing-zero`)

Analysis (2026-10-12 morning), then **implemented as protos stage rules** the same day
(section "Implemented" at the end: census before/after, all 22 high-risk arguments now
carry the retail value). Per-argument table of the analysis:
`out/protos-missing-args.tsv` (high-risk rows first).

## Input and method

- Sites: the 235 `missing-zero` rows of `game/PROTOS.tsv` (a copy taken at 09:33 the same
  day). BRINGUP.md says "232"; that was the row count of an earlier ingest. The 235 rows
  have **421 missing arguments**. A row is a call, and one call can miss up to 9 registers.
  For example, `SystemVmCall_250a50` misses `$f12..$f19`, and
  `title_TitleOptionsHighlightPair_4ef890` misses `$6..$8`.
- Source: the pinned decomp `675c07f` (line numbers in PROTOS.tsv match the snapshot
  source). Retail listings: `asm/main.s` and `asm/overlays/<ov>/<ov>.s` at the same
  commit, split at `glabel`.
- Which register is missing: protos' own lane mapping. GPR parameters fill `$a0..$t3` in
  order, f32 parameters fill `$f12..$f19`, and an m2c placeholder `u`/`uN` uses up its
  slot.
- Caller side: the call is matched to its `jal` in the enclosing function's listing (the
  n-th C call to the n-th `jal`, with targets compared **by address**, because overlay
  listings name cross-image targets `func_XXXXXX`). A backward reaching-definition search
  runs from the `jal`. It handles delay slots and branch-likely annulment, and treats a
  previous `jal` as a definition of every caller-saved register. The definition is then
  spelled symbolically (`ENTRY($k)`, constant, `lui/addiu` address, `lw`/`lh` from a base,
  `$v0` of a previous call, `$sp+off`, or `CLOBBER(<previous callee>)` = a dead
  caller-saved register).
- Callee side: forward liveness from the callee's entry. Does any path read the register
  before writing it? It follows `jal`s and tail `j`s into their listings and treats a
  `jalr` as unknown. Stores to `$sp` that are never reloaded by offset are flagged as a
  varargs/RPC save area. The search is path-insensitive, so it can only over-report reads.
- Scratch scripts (not part of the port): `mzan.py` (listing CFG, reaching definitions,
  liveness), `mzrun.py` (site matching), `mz_emit.py` (classification, hand-reviewed
  table) in the session scratchpad. They are small and can be lifted into the stage.

## Result

| Category | Args | Calls | Callee reads it | Retail value | Proposed fill |
| --- | ---: | ---: | --- | --- | --- |
| **HIGH: callee reads, retail value is a real value** | **22** | **20** | yes | entry param / local / global / earlier return | see table below |
| callee-unused (liveness proves no read) | 211 | 164 | no | mostly CLOBBER | keep 0 (exact) |
| callee-unused-fp (path-insensitive false read, hand-checked) | 29 | 29 | no | CLOBBER | keep 0 |
| garbage-forward: only into a varargs save area / RPC block, or forwarded to a `jalr` | 159 | 42 | indirectly | CLOBBER | keep 0 |

Of the 399 non-high arguments, **397 have a retail value that is a dead caller-saved
register** (`CLOBBER`: the previous call's leftovers). The remaining 2 are callee-unused.
mwcc never relies on a caller-saved register surviving a call, so the original source
**did not pass these arguments**. The definition's extra parameter is an m2c artifact
(a scratch register read as a parameter: `VecLengthSq_1cb470`'s `qmfc2 $5`,
`EventCastGetObjId_24c160`'s iterator node in `$6`). 0 is exactly as good as retail's
garbage for all of them.

### High-risk sites (fix these)

| Site | Call | Missing | Proposed fill | Retail evidence | What 0 does now |
| --- | --- | --- | --- | --- | --- |
| DynClothSubstep_1697c0.cpp:231,243 | VecScale_13be00(**u**, d, s) | arg 0 | `u` (keep the C argument) | `$4 = $sp+0xB0` = the local `VEC u` | the placeholder rule removed a real array local: stores the vector at NULL |
| DynClothSubstep_1697c0.cpp:237,238 | VecScale_13be00(pa, **u**, s) | arg 1 | `u` | `$5 = $sp+0xB0` | `lqc2 0(NULL)` |
| EffCurveEvaluate_197530.c:23 | EffCurveFindKeySpan_197700(arg0, &frame) | f32 arg 2 | widen the def to `(O *arg0, f32 t)` and pass `t` | `$f12` never written before the jal; all **19 callers pass `(p, t0)` and protos drops `t0`** (`drop-extra`) | every effect curve is evaluated at t = 0 |
| EventCastSetScale_257fb0.c:74 | MenuWinSetScale_26c2f0(o) | f32 args 1,2 | `a`, `b` | `$f12`/`$f13` untouched since entry (incoming `a`, `b`); callee `swc1 $f12,0x7C($4)` | the menu window scale is set to 0 |
| WorldSubsysZoneEntryAttach_41c510.c:35, _427020.c:35 | MemStackArrayGet_3f23f0(p) | arg 1 | `idx` | `$5 = lh 0x10(p1)` = `idx = p1->f10` | always element 0 |
| WorldSubsysZoneEntryAttach_41e3d0.c:56 | MemStackArrayGet_3f23f0(p) | arg 1 | `n` | `$5 = lh 0x10(t)` = `n = t->f10` | always element 0 |
| ObjRecTableBindSlot_1c53a0.c:11 | ObjRecTableFindFree_1c5320() | arg 0 | `arg0` | `$4` never written (incoming table) | scans the table at NULL |
| factory_FactoryBlueprintGridSetIcon_4f8f90.c:57 | func_28FE10(o->f80, 0x25) | arg 2 | `n` | incoming `$6` | always sprite 0 |
| factory_FactoryHelpPageLoadPoll_4f1ce0.c:87,91 | func_290AC0(c->f88, id) | arg 2 | `t` | `$6 = $v0(func_1347C0)+1` = `t = r + 1` | takes the memset arm: texture name cleared |
| insect_InsectAbilityTableCmdMotionMaybe_51c9e0.c:44 | func_15F720() | arg 0 | entry copy of `a` (before `a = a + 8`) | `$4` never written | `lw 0(NULL)` |
| insect_InsectBattleCamRestoreSaved_4f1a60.c:31 | InsectBattleCamSetEyeGoal_4f3220(o, &o->m60) | args 2, f32 3 | `c`, `t` | incoming `$6`, `$f12` | wrong camera goal and timing |
| insmenu_InsectVsMenuOpen_4f3120.c:121 | func_436950() (TextEntryCtor) | arg 0 | `s` | `$4 = $v0` of `s = func_14E230(0x248, ..)` | placement ctor on NULL |
| normal_BtlChgMenuTextClipDrawCb_503840.c:23, normal_TransMenuTextClipRectDrawCb_517c90.c:23 | func_26F600() | arg 0 | `p` | `$4 = &D_004DB150` (= `p`, NULL-tested just before) | `sh $0,0x20(NULL)` |
| normal_TransWarpListClipDrawCb_51d030.c:34 | func_26F600() | arg 0 | `q` | `$4 = &D_004DB150` | `sh $0,0x20(NULL)` |
| normal_SpaceMenuMainState_510d90.c:21 | normal_SpaceMenuCancel_5117e0() | arg 0 | `r` | `$4 = lw -0xAB8($gp)` = D_004846B8 (`_gp` 0x485170) = `r` | `lbu 0x14(NULL)` |

10 of the 22 arguments are in overlays. The stage never saw those listings (it loads only
`asm/main.s`).

### Low and none, by callee (keep 0)

- callee-unused: `title_TitleOptionsHighlightPair_4ef890` (60 args), `VecLengthSq_1cb470` (37),
  `RecordSetStateClamped_430db0` (29), `VecLengthSqXZ_1cb450` (21), `RecordAdvanceState_430bf0`
  (12), `ModelMotionEventReleaseHandlers_1b02b0` (11), `CharaSysEventLogKeyRemove_3a3380`
  (6), and 35 others.
- callee-unused-fp: `EventCastGetObjId_24c160` (22), `EventCastFindKeyByObjId_24b1d0`
  (3), `EventVoiceChanSet{Playing,Protected,Requested}` (4). The register is the inlined
  list iterator's node. It is loaded in a branch-likely delay slot, and the compare that
  reads it is reachable only on that path.
- garbage-forward:
  - `SystemVmCall_250a50` `$f12..$f19` (64): reach `Fprintf` only.
  - `MesWinPushNumVar{,0}` `$7`, `$f12..` (41): reach `Sprintf` only. The format consumes
    `$6` only.
  - `RevelationBoardGetCells_3eb510` `$6` (13), `MenuObjInsectSatietyUnderCap_386bd0`
    `$5/$6` (12), `HandleRegistry{Clear,Reset}`, `ObjRefTableClear`: forwarded to a
    virtual call.
  - `SoundRpc*Thunk` `$6/$7`: packed into the RPC block.
  - `CdInitDvdMode_15e5d0` `$5..$7`, `SavePointActivate_426480`: reach a printf only.

## Rules that decide all 421 automatically (for the protos stage)

Applied in this order, they reproduce every verdict in the TSV except the 4 DynCloth rows
(rule F) and the hand-spelled local names (rule E prefers a C local; the raw expression
is also correct).

- **A. Callee liveness gate.** Compute the callee's live-in argument registers from its
  listing: forward dataflow from entry, through `jal`/tail `j` into the target's listing.
  A `jalr` counts as "forwarded". A store to `$sp` that is never reloaded by offset counts
  as a save area. If the missing register is not live-in, 0 is exact (`missing-unused`,
  211 args). Two refinements:
  - Path sensitivity for registers loaded in a branch-likely delay slot would clear the
    29 iterator false positives. Rule B already covers them.
  - A dead arg can be filled with any value, so the stage could just stop logging these.
- **B. Dead caller-saved value.** If every reaching definition of the register at the
  `jal` is an earlier call (or the register is set only on paths through one), the source
  never passed the argument: fill 0 and log `missing-dead` (397 args, including all of
  A's).
- **C. FPR lanes.** Extend `asm_reg_reaching`, `_passthrough`, `_entry_value` and
  `def-widen` from `$4..$11` to `$f12..$f19`; today `_asm_arg` returns `noasm` for
  `cls == "f"`.
  - Entry value plus a declared f32 parameter in that lane → passthrough (EventCastSetScale:
    `a`, `b`).
  - Entry value but no such parameter → **def-widen with an f32 parameter**, and the
    fixpoint must then **keep** the callers' extra f32 that `drop-extra` removes today:
    EffCurveEvaluate_197530 and its 19 callers.
- **D. Overlay listings.** Also load `asm/overlays/<ov>/<ov>.s` (`split_listing` works
  unchanged). Match `jal`s **by target address**: overlay listings write cross-image
  targets as `func_XXXXXX`, and the C may use either spelling. 10 high-risk arguments and
  69 of the 235 rows are in overlays.
- **E. Spell more reaching definitions** (extend `_asm_value_expr`). Prefer an existing C
  local the function assigns the same value to, if it is not reassigned between that
  assignment and the call:
  - `lui`+`addiu` of a symbol address, including folded `lui 0x4E; addiu -0x4EB0` →
    `(void *)D_xxxxxxxx`.
  - `lw ±off($gp)` without a relocation → the symbol at `_gp + off` (`_gp = 0x00485170`,
    SCUS_974.90.lcf).
  - `daddu $a, $v0` after `jal G` → the C variable assigned from `G(..)`.
  - `lh/lw off(ENTRY $k)` → the local assigned `param_k->field`, or
    `*(s16 *)((u8 *)param_k + off)`.
  - `daddiu $a, $v0, k` → `var + k`.
- **F. Placeholder gate.** `_reg_placeholders` must not drop an argument whose register
  retail sets to a stack address (`addiu $r, $sp, off`), or whose local is an array or
  aggregate type (resolve typedefs: `VEC u;` with `VEC` = `f32[4]`). Gating it on rule
  B/C's `entry` verdict is enough. Otherwise a real buffer becomes NULL (DynClothSubstep,
  4 calls).
- **G. Signature-parse fallback.** `ObjRecTableBindSlot_1c53a0`'s first parameter is
  typed with an inline anonymous struct (`struct { u8 pad[0x434C]; s32 x; } *arg0`). The
  missing-entry rule did not fire although the listing proves `$4` is the entry value.
  Make `_encl_def`/`sig` survive inline struct types (or fall back to the positional name).
- **Report the rest.** If a missing register is live-in to the callee and its reaching
  definition is none of the above (none remain today), log `manual-missing` instead of
  silently passing 0.

## Related findings outside the 235 rows

- `drop-extra` rows whose dropped register the callee's listing reads (rule A run over
  the 968 drop-extra rows):
  - 19 are EffCurveEvaluate_197530's `t0` (above).
  - 4 are not yet checked: `SoundStreamSlotOpenLoop_1bce80` `$5`,
    `normal_BtlChgPageAbilityListScroll_504ea0` `$5`, `title_TitleLoadSlotListCancel_4ee8c0`
    `$4/$5`.
  - Each such row means the definition dropped a parameter that retail uses.
- Accuracy limits:
  - The liveness is path-insensitive (it over-reports reads, never under-reports).
  - `jal`↔C call pairing is by order. At AbilityModeRun_2790e0.cpp:863 (C++ method `Wait`, listed as AbilityModeRun_2790e0; callee `SystemVmCall_250a50`)
    there are 3 `jal`s for 1 C call; all three give the same CLOBBER verdict.

## Implemented (2026-10-12): rules A-G in the protos stage

Code: `tools/stages/asmflow.py` (listing parse, instruction CFG with delay slots and
branch-likely annulment, symbolic reaching values, callee liveness; lifted from the
analysis scripts) and `tools/stages/protos.py` (`_site`, `_asm_term`, `_callee_reads`,
`_spell`, `_missing_value`, `_reg_placeholders`, `blank_paren_structs`).
`snapshot_addr_table` also reads `asm/overlays/<ov>/<ov>.s` (split at `glabel`) and `_gp`
from `SCUS_974.90.lcf`. Every decision is made from the listings; there is no per-site
table left (`MISSING_ARG_ASM` is empty: its two chara-ctor rows are now spelled by rule E).

What the stage does with a missing argument, in order:

1. `missing-passthrough` / `missing-entry` / `def-widen`, as before, but the register test
   now covers **`$f12..$f19`** (rule C) and **overlay listings** (rule D), and the call is
   paired with its `jal` (or tail `j`) **by target address** among the calls to the same
   address (`func_1839F0` in an overlay listing = `PadIsTriggered_1839f0` in the C). When
   the C and the listing disagree on the number of such calls, every candidate `jal` must
   give the same value (or all be dead), else the site is "no listing".
   - `def-widen` is gated by rule A: never for a register the callee does not read; an FPR
     needs a proven read (a varargs save area is not one: `SystemVmCall_250a50`'s
     `$f12..` reach only `Fprintf`). A widened definition's callers keep the argument they
     used to lose (`EffCurveEvaluate_197530(O *, float rgp_f0)`: the 19 `drop-extra`
     rows of `t0` are gone).
2. **A** `missing-unused`: the callee's listing (followed through `jal` / tail `j`) never
   reads the register before writing it -> 0 is exact.
3. **B** `missing-dead`: a reaching definition of the register is an earlier call's
   clobber -> the source never passed it -> 0.
4. **E** `missing-asm`: the reaching value is spelled in C, preferring a local the function
   assigned the same value to (and did not modify before the call):
   symbol address (`lui/addiu`, `%lo`, `%gp_rel`, or overlay `lui 0x4E; addiu
   (0x4DB150 & 0xFFFF)`), a load from a symbol or `$gp+off` (`_gp` + off -> `D_xxxxxxxx`),
   an earlier call's `$v0` (the C variable assigned from that call), `$v0 + k`, a load from
   an incoming pointer (`*(T *)((char *)p + off)`, or the local `x = p->fOFF`), entry
   register + k, a constant.
5. `manual-missing` (0, logged): the callee may read it and the value has no spelling.
   None today.
6. `missing-zero` (0, logged): no listing for the enclosing function, or the call cannot
   be paired. One call today: AbilityModeRun_2790e0.cpp:863 (C++ method `Wait` inlined 3
   times into the listing; callee `SystemVmCall_250a50`, its `$f12..$f19` reach only
   `Fprintf`).

Placeholders (rule F, and a generalisation): a call argument that is a never-assigned
local is a missing argument when it is m2c's `u`/`uN`/`u_N`, **or any other scalar local
whose register retail proves to be the caller's entry value**; never when the local is an
array or aggregate (`VEC u;` in DynClothSubstep_1697c0, retail `addiu $4,$sp,0xB0`). The
generalisation found 3 more uninitialised-local reads: `SoundStreamSlotOpenLoop_1bce80`
passed an unset `x` where retail passes its incoming `$a1` (the stream name the queue
`strcpy`s; the definition is widened and `StreamChanUpdate_1d72d0` keeps its `arg0`),
`NodeObjBasicDrawFromParentMaybe_196a00` (`unin` = entry `arg0`), and
`MenuGridCursorBobCb_342490` (`w`; the callee never reads it: 0). In C++ the fill is cast
to the local view's slot type.

Signature parse (rule G): `blank_paren_structs` blanks an inline `struct { .. }` written
inside parentheses before the brace walk, so `ObjRecTableBindSlot_1c53a0(struct { u8
pad[0x434C]; s32 x; } *arg0, ..)` is a definition again (passthrough `arg0`).

### Census (args; calls in parentheses)

| | before (09:33 ingest) | after |
| --- | ---: | ---: |
| `missing-zero` (0, unknown) | 421 (235) | **8 (1)** |
| `missing-unused` (0 exact, rule A) | - | 200 (153) |
| `missing-dead` (0, rule B) | - | 181 (71) |
| `missing-asm` (rule E spelling; before: reviewed table + constants/globals) | 3 (3) | 13 (13) |
| `manual-missing` | - | 0 |
| `missing-passthrough` | 1,114 (843) | 1,120 (848) |
| `missing-entry` | 31 (31) | 32 (32) |
| `def-widen` (definitions) | 348 | 348 (+EffCurveEvaluate_197530 `float`, +SoundStreamSlotOpenLoop_1bce80 `$a1`; -3 widenings for registers the callee never reads: GoTitleMenuUpdateThunk_39bf70, RecordAdvanceState_430bf0, MenuGridCursorBobCb_342490's `$a1`) |
| `drop-extra` (calls) | 968 | 946 (-19 `t0` of EffCurveEvaluate, -4 DynCloth `u`, -1 StreamChanUpdate `arg0`; +2 placeholders now dropped: SoundStreamSlotOpenLoop's `x`, NodeObjBasicDraw's `unin`) |

The 421 analysed arguments map exactly onto the analysis categories: callee-unused 210 ->
`missing-unused` (one -> `missing-dead`), callee-unused-fp 29 -> `missing-dead`,
garbage-forward 159 -> `missing-dead` 151 + the 8 `missing-zero` above, and the 22
high-risk arguments:

| Site | Now passed |
| --- | --- |
| DynClothSubstep_1697c0.cpp:231,237,238,243 | `u` (array local kept, rule F) |
| EffCurveEvaluate_197530.c:23 | `rgp_f0` (definition widened with `float`; 19 callers pass `t0`) |
| EventCastSetScale_257fb0.c:74 | `a`, `b` (FPR passthrough) |
| WorldSubsysZoneEntryAttach_41c510/427020.c:35, _41e3d0.c:56 | `idx`, `idx`, `n` (local = `p->f10`) |
| ObjRecTableBindSlot_1c53a0.c:11 | `arg0` (rule G) |
| factory_FactoryBlueprintGridSetIcon_4f8f90.c:57 | `n` (overlay passthrough) |
| factory_FactoryHelpPageLoadPoll_4f1ce0.c:87,91 | `t` (local = `r + 1`, `r` = the call's `$v0`) |
| insect_InsectAbilityTableCmdMotionMaybe_51c9e0.c:44 | `rgp_entry_a` |
| insect_InsectBattleCamRestoreSaved_4f1a60.c:31 | `c`, `t` |
| insmenu_InsectVsMenuOpen_4f3120.c:121 | `s` (= `func_14E230(..)`'s `$v0`) |
| normal_BtlChgMenuTextClipDrawCb_503840.c:23, normal_TransMenuTextClipRectDrawCb_517c90.c:23 | `p` (local = `&D_004DB150`) |
| normal_TransWarpListClipDrawCb_51d030.c:34 | `q` |
| normal_SpaceMenuMainState_510d90.c:21 | `r` (local = `D_004846B8`, `lw -0xAB8($gp)`) |

The 4 unverified `drop-extra` rows, checked with the same liveness:
`normal_BtlChgPageAbilityListScroll_504ea0` never reads `$5`, `title_TitleLoadSlotListCancel_4ee8c0`
never reads `$4`/`$5` (the drops are exact). `SoundStreamSlotOpenLoop_1bce80` **does** read
`$5` (passed on to `SoundStreamSlotQueueOpen_1be8a0`'s `strlen`/`strcpy`): fixed by the
generalised placeholder rule above.

Tests: `tests/protos/fixture/src/main/listing/` + `fixture/asm/main.s` exercise rules A,
B, C (FPR passthrough), E (symbol address in a local), F (array local) and G (inline struct
parameter) and the no-widen gate (`ctest -R protos.stage`).

## Re-check (2026-10-25, protos manual-row close-out)

The arguments still filled with 0 on the re-ingested tree, against the current listings:

| Rule | Rows | Verdict |
| --- | ---: | --- |
| `missing-zero` | 7 | all OK: Notify / InvObjCastToCage / IterInit lanes reach only IsKindOf (slot 0x34 / 0x20) and count (slot 0x8) methods that read neither `$a2` nor `$a3` (tools/bringup/vslot_reads.py); SystemVmCall_250a50's `$f12..` reach only Fprintf |
| `manual-missing` | 15 | all OK: the lanes are `rgp_aN` forwards and every port definition at the end of the virtual chain has fewer parameters (census/protos_manual.tsv evidence) |
| `missing-unused` | 276 | exact: the callee's listing never reads the register |
| `missing-dead` | 631 | rule B: the only reaching definitions are earlier calls' clobbers, so the source never passed the argument. A deep read over-approximation (`vslot_reads.deep_reads`, every vtable's method at each jalr slot) says 60 such lanes of 24 callees MAY be read (mostly WorldSubsysRelease_* / ModelObjExCtor virtual chains): not reviewed per receiver: retail passed the previous callee's leftovers there, which mwcc never treats as a value |

No argument is left on 0 where retail passes a defined value that the callee reads.
