# UB audit, -O2 for game code, vu0frame, RG_OVL_DATA (2026-10-18)

Lane: PLAN.md D2 says the game sources build at `-O1` "until the UB audit is done". This
document is that audit: what undefined behaviour the decompiled game code has, which of it
the compiler can exploit, how each class is fixed (stage rule or flag), and the `-O2`
verification. It also records two residue items done in the same re-ingest: the `vu0frame`
stage (docs/NATIVE-CPU.md section 4: VU0 registers as function locals) and the three
`RG_OVL_DATA` sites (direct references).

Status: **DONE 2026-10-18.** Game code builds at `-O2` by default (`RG_GAME_OPT`) with three
UB flags; the route is field-for-field identical to `-O1`; the vu0frame stage, the
RG_OVL_DATA direct references and the datareloc `short-main-ptr` rule (FACTORY Slot
pointer) are in game/ (re-ingested). Summary at the end ("Checkpoint").

## Tools (reusable)

| Tool | What |
| --- | --- |
| `cmake -DRG_GAME_OPT=-O2` | optimisation level of the game objects (game/, overrides/, missing/); cmake/game.cmake. Default `-O1` |
| `cmake -DRG_UBSAN=ON [-DRG_UBSAN_CHECKS=undefined]` | UB census build: game objects with `-fsanitize=<checks> -fsanitize-recover=all` (no vptr/function), handlers from `src/game/ubsan_census.c` |
| `src/game/ubsan_census.c` | logging UBSan runtime (LLVM ships no i386 Windows ubsan runtime): one `NEW` row per check site the first time it fires, `COUNT` rows at exit, file `$RG_UBSAN_LOG` (default `ubsan_census.tsv`); reopens the log in a process restored from a save state (2026-10-25) |
| `tools/ubaudit/build.ps1 -BuildDir D [-Defs K=V,..] [-Targets ..]` | configure once + build at -j4 (the shared-PC limit) |
| `tools/ubaudit/wcensus.py BUILD_DIR` | UB-relevant frontend warnings over every game compile (`-fsyntax-only`, the build's exact flags with `-w` swapped for the warning list); `--strict-vu0` = the vu0frame completeness check |
| `tools/stages/vu0frame_census.py` | VU0 register values carried by same-file calls (call-fed reads), live-in and kept-lane functions |
| `tools/ubaudit/cmpsets.py A B` | compare two fixture sets (exes or `out/fixtures/<id>`): vbl, run hash, check run hash and frame hash per milestone |
| `tools/ubaudit/hashwalk.sh EXE A B STEP OUT` | run hashes along the route every STEP fields (<= 16 states): first divergence of two builds |
| `tools/ubaudit/objbisect.py --good D1 --bad D2 ...` | relink D1's rg-game with game objects from D2 and bisect to the object that changes a shot / run hash; `--link-only` = D1's host code + all of D2's game objects (a same-host-code comparison exe) |
| `tools/ubaudit/perf.sh EXE OUT [REPS]` | `RG_FIELD_TIMES` step ms in field / battle / town windows from fixture states |
| `tools/fixtures/soak.py run --exe <UBSan exe>` | long soak over every card with `RG_UBSAN_LOG` per card; `soak.py report` lists the sites, new vs `census/ub_ubsan_route.tsv` (docs/TEST-FIXTURES.md "Long soak") |
| `tools/ubaudit/ubsum.py LOG OUT` | UBSan runtime log -> sorted site table (`census/ub_ubsan_route.tsv`) |
| `tools/native/override_vu0frame.py [--scan] [--write] [--out D] FILE...` | the vu0frame transform (the stage class, imported) on hand-written files: overrides/, missing/, src/sce/vu0/libvu0.c; skips named-context files; see "vu0frame: overrides and libvu0" |
| `tools/ubaudit/rehash.py OVERRIDE...` | rewrite an override's `rg-override ... sha256` header to the re-ingested game file's hash (content untouched) |

Build dirs: `build/o2-i686/{o1,o2,ubsan,local-before,local-after}` (RG_NATIVE_ONLY=ON,
RG_VU0_MODE=native unless named `local-*`). Scratch: `out/ubaudit/`.

## vu0frame: VU0 registers as function locals (NATIVE-CPU.md section 4)

**Stage** `tools/stages/vu0frame.py`, registered in tools/ingest.py after `dialect` (it
adds a parameter to static helpers, so protos is measured unchanged); rows in
`game/VU0FRAME.tsv`.

- `RG_VU0_FRAME;` right after the `{` of every function whose body names the model
  (`rg_vu0*`, `RG_VU0_*`, a `vu0bind`-bound name, an intrinsic `_v*(`, a `Vu0*` macro) or
  calls a frame helper. Under RG_VU0_LOCAL (modes `local` / `native`) it is
  `rg_vu0_state rg_vu0 = RG_VU0_RESET_INIT` (vf0 = (0,0,0,1), everything else 0): the
  spellings in port/vu0.h, vu0intrin.h, libvu0.h name `rg_vu0` at the use, so ordinary
  scope makes them the function's own register file. Under `model` it is `((void)0)`.
- **Frame helpers**: a `static` function of the file that touches the model and is called
  from another function of the same file runs on its caller's register file: first
  parameter `rg_vu0_state *rg_vu0_p_`, `&rg_vu0` at every same-file call, body bracketed by
  `#pragma push_macro("rg_vu0")` / `#define rg_vu0 (*rg_vu0_p_)` / `#undef` / `pop_macro`.
  This is exactly the old per-file semantics restricted to the call tree, so it covers both
  directions: the census `tu-helper` rows (ScaleMul / InvScaleMul / StoreMatrix read what
  the caller left) and the call-fed reads (`tools/stages/vu0frame_census.py`: the caller
  reads what the helper left; 9 rows, all static helpers or override-local helpers).
  An address-taken helper would keep its own frame (`info-helper-addr`; 0 in the corpus).
- **vu0inline.h** (port replacement header): its 7 helpers became `Name_f(rg_vu0_state *,
  ...)` + `#define Name(...) Name_f(&rg_vu0, __VA_ARGS__)`, the same caller-file rule.
- **Fallback (removed later the same day)**: port/vu0.h used to keep a file-scope
  `static rg_vu0_state rg_vu0` under RG_VU0_LOCAL for code without frames (hand-written
  overrides, `src/sce/vu0/libvu0.c`, the vu0native test). Those were converted
  ("vu0frame: overrides and libvu0" below) and the static is gone: a function that
  names the model without a frame no longer compiles. `RG_VU0_NO_FRAMES` (A/B only)
  brings the per-file file back; `wcensus.py --strict-vu0` is now what every build does.
- `port/vu0_ctx.h` (the named cross-file contexts) also makes RG_VU0_FRAME a no-op, so a
  context file stays entirely on its context.

Dry run (ingest into `out/ubaudit/game-new`): 144 files, 145 frames, 38 helpers,
63 helper calls; nothing else in game/ changed. Overrides whose game file moved (rehash):
listed in "Overrides rehashed" below.

## RG_OVL_DATA (3 sites) -> direct references

The hwaccess stage's `overlay-data` rule (MAIN code reading NORMAL's FieldHud block by
literal address: `*(s16 *)0x5273C2`, `*(s8 *)0x5273CE`) now emits
`(*(T *)((unsigned char *)D_00527020 + off))` and declares `extern unsigned char
D_00527020[];` in the stage's prefix (before its `#line 1`). `D_00527020` is the arena
label MAIN already links against in 45 files (docs/OVERLAY.md "named overlay data used by
MAIN"), so the access is resolved by the linker, as retail's absolute address was.
Behaviour: the resolver path returned the same address whenever NORMAL was resident and a
scratch slot (reported once on stderr, "hwbus: overlay data ... unresolved") otherwise; no
fixture run log has that report, i.e. every access on the route was resolved, so the two
spellings are the same accesses. Sites: `CharaGetControlStateMaybe_2f5320`,
`FieldHudGetSuggestMember_203c20`, `FieldHudInitOnce_204120`. `RG_OVL_DATA` (macro,
`rg_ovl_data_ptr`, the resolver hook) stays for tests and future sites; the stage no
longer emits it. Tests updated: `tests/hwbus/test_stage.py` (expects the direct form +
declaration), `tests/hwbus/hwbus_tests.c` `game_e2e` (the store lands in `D_00527020`
itself, the resolver is not asked).

## UB census (2026-10-18)

### Static: frontend warnings (`tools/ubaudit/wcensus.py`, all 25.3k game compiles)

`out/ubaudit/wcensus/{warnings,classes}.tsv`. Flags: -Wuninitialized,
-Wsometimes-uninitialized, -Wshift-count-*, -Wshift-negative-value, -Winteger-overflow,
-Wreturn-type, -Warray-bounds(-pointer-arithmetic), -Wdivision-by-zero, -Wunsequenced,
-Wnull-dereference, -Wvarargs, -Wfortify-source, constant/float conversions, ...

| Class | Sites (files) | Verdict |
| --- | --- | --- |
| -Wincompatible-library-redeclaration | 667 (557) | decomp declares memset/strcpy/... with game types; ABI-identical on i686; not UB in practice |
| -Wuninitialized / -Wsometimes-uninitialized | 191 (130) / 16 (13) | m2c placeholders and mwcc register steering; all made defined (zero) by `-ftrivial-auto-var-init=zero` (cmake/game.cmake, BRINGUP.md); same value at every -O level |
| -Wreturn-type (C) | 19 (19) | m2c dropped the $v0 tail (`return;` / fall-off in a value function). In C the value is `undef` only if a caller uses it; reviewed: no run-hash difference O1 vs O2. Fix class if ever needed: protos `def-bare-return` style rule |
| -Wreturn-type-c-linkage | 3 | struct-returning extern "C": layout-only, not UB |
| -Warray-bounds | 2 | `InsectRecSlotRemoveItem_3cfde0` s16[4][5], `MapModelCreate_1952b0` u8[4][8][4]: decomp struct views shorter than the data (same class as the UBSan `bounds` rows) |
| -Warray-bounds-pointer-arithmetic | 9 (1) | same, pointer form |
| -Wfortify-source | 1 | `InsectMenuOpen_397ee0` memset 16 bytes over a 4-byte extern (`D_00483550`): the data image is contiguous in retail order (datareloc), the neighbours are what retail clears too |
| -Wunsequenced | 1 | `MenuPartyEquipSnapshot_2978e0`: `f(t18 = x) + g(t18)`; clang fixes the order in the frontend (left to right), so it cannot change with -O |
| -Wshift-count-overflow / -negative | 0 | the 3 sites were fixed in bring-up (dialect `wide-shift`, BRINGUP.md fix 7) |
| -Wdivision-by-zero, -Winteger-overflow, -Wvarargs, -Wnull-dereference | 0 | |

### Dynamic: UBSan on the route (`RG_UBSAN=ON`, power-on -> field 32,220)

`census/ub_ubsan_route.tsv` (every check site that fired, hits, first operands);
`tools/ubaudit/ubsum.py LOG OUT` makes it from the runtime log. -fsanitize=undefined minus
vptr/function (signed overflow is not UB under -fwrapv and is not reported).

| Class | Sites | Hits | What | Fix |
| --- | --- | --- | --- | --- |
| type_mismatch misaligned | 62 | 96,533 | decomp structs carry `aligned(8/16)` (mwcc layout) and are reached through pointers with less alignment (Variant* script values at 4, MinimapDrawEntry `Obj` at 16). x86 loads do not fault; only SSE aligned moves would | none needed: the -O2 build (vectoriser) ran the route without a fault; any movaps on such a pointer would be a crash, not a silent change |
| bounds index | 25 | 115,377 | indexing past a declared array: extern data symbols declared shorter than the real object (`D_004814F0[2]` read at [2], task/sound tables `u8[1024]` at [1040..1920]), struct-view arrays (`s16[7][2]` at [7]), `Ent[512]` at [513] | none needed (see "-O2" below: no run difference); the data image is contiguous, so these read the retail neighbours |
| float_cast | 5 | 86,594 | float->int of NaN / inf / out of range: `TexAnimeTableApplyMaybe_162f50` (NaN, 2 sites, 86k hits), `TexAnimeCfgScrollCmd_1622e0` (+inf: x/0), `AudioDecSetInputVolume_1d2b90` (4.29e9 -> s32) | **`-fno-strict-float-cast-overflow`**: saturating conversions. Without it these were poison and different builds produced different values (below) |
| type_mismatch null | 1 | 718 | `InvBroadcastPhase_3c02b0`: `vtbl = *temp_2` before the `temp_2 != NULL` test; the load is dead | `-fno-delete-null-pointer-checks` (D2) keeps the test |
| pointer_overflow | 1 | 12 | `VectorU32InsertN_1a4e80` range test `end - (tail - n) <= val` | **`-fwrapv-pointer`** (-fwrapv alone still folds `p + i < p` to `i < 0`) |

### The float-cast class changed runs

Before the flag the route's run hash was **build-dependent**: O1, the UBSan build and the
`local`-VU0 build of the same tree diverged at field 12,1xx (`tools/ubaudit/hashwalk.sh`:
equal at 12,100, different at 12,200; state trace (`RG_TRACE_*`, symbol regions)
identical to 12,165, i.e. game state was the same and only folded audio/pad data
differed) and rendered different TexAnime frames from field 8,300. With
`-fno-strict-float-cast-overflow` every build converts the same way (EE `cvt.w.s`
saturates too; NaN -> 0). This flag changes the run hash relative to earlier builds
(milestone vbls unchanged: the route reaches `saved` at the same fields).

## -O2 for the game code: verification

Builds (same tree, RG_NATIVE_ONLY=ON, RG_VU0_MODE=native, game flags incl. the three UB
flags above): `build/o2-i686/o1` (RG_GAME_OPT=-O1) and `build/o2-i686/o2`
(RG_GAME_OPT=-O2). Exe copies in `out/ubaudit/exe/`.

**Run comparison** (`regen.py --check 300` = power-on route to field 32,220 with a state
at each milestone and milestone+300, a shot at +300; `tools/ubaudit/cmpsets.py`):

- o1 vs o2 as built: all 8 milestones and 8 checks have the **same vbl and run hash**;
  6 of 8 frame hashes differed. Cause: not the game code -- the two dirs were built an
  hour apart while the renderer lane was editing src/gpu / src/native/render (the o2 dir
  links the newer host code; field 8,300 lost a depth-of-field blur). Proof:
- `tools/ubaudit/objbisect.py --good o1 --bad o2`: o1's link with ALL 25,293 game objects
  taken from o2 renders field 8,300 like o1 (the bisection stops at round 2: the culprit
  is outside the game objects). That exe (`exe/o2-mixed` = -O2 game code + o1's host
  code) vs o1: **IDENTICAL on all 8 milestones + 8 checks, run hash and frame hash**
  (`out/fixtures/c774bf02bcfb3252` vs `f83518c80b2a4111`).
- `verify.py` on the o2 set (`67323ebc17c52a5f`): 8/8 milestones OK (load N, run 300 =
  power-on run: run hash and frame).

So the game code at -O2 runs the route field-for-field identically to -O1.

## vu0frame: verification

| Comparison | Range | Result |
| --- | --- | --- |
| native, O1, before vs after the stage (no UB flags yet) | power-on -> 32,220, 8 milestones + 8 checks | IDENTICAL (run hash and frame) |
| local, frames vs `RG_VU0_NO_FRAMES` (= the old per-file register file), same host code (objbisect `--link-only`), with the UB flags | power-on -> 27,300 (title, field, battle, battle_won + checks) | IDENTICAL (run hash and frame) |
| `--strict-vu0` (no file-scope fallback) over the 275 model files | compile | 0 errors in game/; 61 hand-written overrides use the fallback (not converted: content owned elsewhere) |

The local route was cut at battle_won because the route is timed for native VU0 (local
plays the fight differently and wanders afterwards, NATIVE-CPU.md section 3). An earlier
attempt compared local before/after across the stage WITHOUT the UB flags and differed
from field 12,1xx: that was the float-cast class (the UBSan build and the native O1 build
of one tree differed the same way), not the stage; with the flag, frames on/off agree.
Kept-lane functions (22, census `lanein`): a `static`-frame variant was built and is not
needed; the stage keeps the mechanism with an empty `KEEP_FUNCS` table.

## Performance (-O1 vs -O2 game code)

`tools/ubaudit/perf.sh`, `RG_FIELD_TIMES` step column (the field's EE game code plus the
host work it drives: native render submission, GS/VIF bookkeeping), mean ms per field after
a fixture load, windows field 8,000+1,000 / battle 23,000+1,000 / town 29,060+600, three
interleaved repetitions of `exe/o1-flags` and `exe/o2-mixed` (identical host code, only the
game objects differ). Shared PC with other lanes' builds and runs: +-10 % noise per run.

| Window | -O1 step ms (3 runs) | -O2 step ms (3 runs) | mean change |
| --- | --- | --- | --- |
| field | 1.499 / 1.520 / 1.369 = 1.46 | 1.461 / 1.394 / 1.263 = 1.37 | -6 % (lower in 3/3 pairs) |
| battle | 7.920 / 8.656 / 7.823 = 8.13 | 8.096 / 8.140 / 7.266 = 7.83 | -4 % (2/3) |
| town | 10.980 / 11.071 / 10.160 = 10.74 | 11.598 / 10.804 / 9.499 = 10.63 | -1 % (2/3) |

The game's own code is a small part of the step (PERF-3D.md: 1-3 ms per field), so the gain
is modest; no window got slower beyond noise. Decision: **-O2 is the default** for the game
objects. No file needs -O1 (the -O2 run matches -O1 exactly; the objbisect tool is there
if a future change makes one differ).

Test-suite note: `devirt.verify` reads the vcall sites of the built game objects; at -O2,
unrolled loops and inlined callees add sites (`port-more`, 22 units) and one unrolled loop
re-forms a vptr offset (CharaDeserialize_3a9c50, listed in tests/devirt/
expected_mismatch.tsv). tools/devirt_verify.py gained `--tolerate STATUS`; the test passes
`--tolerate port-more` when RG_GAME_OPT is not -O1. The two fault controls stay strict.

## Overrides rehashed (re-ingest; content unchanged)

`tools/ubaudit/rehash.py`: CameraObjCtor_177430.cpp, LensFlareDraw_2ed830.cpp,
BoxToCenterExtentsVu0Maybe_14ff40.c, BoxTransformExtentsVu0Maybe_14fed0.c,
CameraBaseLookAt_15fae0.cpp, CollFrameTreeCollectTris_16bfb0.cpp, CollTriTransform_16c1a0.c
(their game files moved under vu0frame). **Retired**: `overrides/src/main_data/
data2c_00480390.c` (the save-editor lane's FACTORY fix): the new datareloc rule
`short-main-ptr` generates the same file (identical up to the order of two extern lines,
checked); the old copy is kept in `out/ubaudit/retired/`. `ingest.py --check`: 0 problems,
218 overrides.

## vu0frame: overrides and libvu0 (2026-10-18, second lane)

The 61 overrides that `--strict-vu0` listed, 2 more that name the model only in
their `#else` (model-mode) branch (MatFromSRTVu0_13bc90, MatRotateVu0_13bc20) and
`src/sce/vu0/libvu0.c` now use the stage's convention, and **port/vu0.h has no
file-scope register file any more** under RG_VU0_LOCAL (only the A/B switch
`RG_VU0_NO_FRAMES` brings it back; the model/oracle global is unchanged).

**Tool** `tools/native/override_vu0frame.py --scan --write`: imports
`tools/stages/vu0frame.py`'s `Vu0FrameStage` (no copy of its rules) and applies it to
each file in place; idempotent (a converted file is skipped). Two widenings, for
hand-written files only (both found on libvu0.c; game/ needs neither, see the stage
proposal below):

1. **File-local macros that wrap the model** count as model uses (the stage's `BOUND`
   list is replaced by one that also takes `#define NAME(...) ... rg_vu0...`):
   libvu0.c writes `LQ` / `SQ` / `FMAC`; without this, 4 public functions got no frame
   and `rot_apply` was not seen as a helper.
2. **Helper fixpoint**: a static function that touches the model only through a helper
   and is itself called (libvu0 `rot_angle` -> `qmtc2_float`, `ecossin`; its callers
   read vf4/vf5 it leaves) becomes a helper too (the stage is rerun with the helpers
   found so far counted as model uses until the set is stable). The stage's own
   single pass would give it an own frame, i.e. the caller would read reset registers.

Skipped: 6 named-context files (`RG_VU0_CTX_NAME`: xfbox / colltri, the frame is a
no-op there) and LensFlareDraw_2ed830.cpp (its only "model" hit is a call of the game
function `Vu0InnerProduct_13bd60`).

Result: 64 files, 92 frames, 31 helpers, 71 helper calls (rows: `out/ovu0/rows-write.tsv`).
Files (mechanical edit: `RG_VU0_FRAME;` after `{`, helper parameter + push/pop_macro,
`&rg_vu0` at helper calls; nothing else):

- overrides/src/main/camera/CameraObjCtor_177430.cpp
- overrides/src/main/gs/: GsPktSetRGBAQVec_13edd0.c GsPktSetXYZfVec_13efe0.c GsPktSetXYZf_13f060.c
- overrides/src/main/math/: MtxPlaneProjection_13c930.c PointInTriangle_13d720.c
  PointSegmentClosest_13dcc0.c QuatSlerp_13c270.c RayTriIntersect_13d8c0.c
  SegmentSphereIntersectWorld_13d9d0.c SegmentSphereIntersect_13da60.c
- overrides/src/main/matrix/: CameraBaseLookAt_15fae0.cpp MatFromQuat_13c440.c
  MatFromSRTVu0_13bc90.c MatMul33_13d180.c MatRotateVu0_13bc20.c MatScaleRows_13cf00.c
  MatZero_13d2c0.c MtxIdentity_13d2e0.c MtxInverse_13cf40.c MtxLookAtKeepScale_13cc50.c
  MtxMulAffine_13d110.c MtxMulAffine_13d1d0.c MtxMulChain4_13cff0.c MtxMulDir_13c860.c
  MtxMul_13d240.c MtxProjectPoint_13c8c0.c MtxRotX_13ce90.c MtxRotY_13ce20.c
  MtxRotZ_13cdb0.c MtxTransformPointsMinMax_13c780.c MtxTransformPoints_13c810.c
  MtxYawFaceTarget_13cb30.c
- overrides/src/main/vec/: AabbContainsPoint_13e130.c AabbContains_13e090.c
  AabbCorners_13e190.c AabbOverlap_13e0e0.c BBoxUnion_13dea0.c BoundsAddPoint_13dee0.c
  BoundsFrom4Points_13df00.c VecAddScaled_13bdd0.c VecDistSqXZ_13d330.c
  VecDistSq_13d360.c VecDistanceXZ_13d390.c VecDistance_13d3d0.c VecLengthSqXZ_13d410.c
  VecLengthSq_13d440.c VecLengthXZ_13d470.c VecMax4_13dfb0.c VecMaxMin_13df70.c
  VecMax_13dfe0.c VecMinMax3_13df40.c VecMin_13df90.c VecMulXyz_13bd20.c VecMul_13bd40.c
  VecReflectNeg_13dc30.c VecSetLength_13e000.c VecSetOnes4_13e170.c VecSetOnes_13e180.c
  VecSubInPlace_13e050.c VecTriCross_13de70.c Vu0InnerProduct_13bd60.c Vu0InnerProduct_13d300.c
- src/sce/vu0/libvu0.c (also built as rg_sce_vu0_oracle: model mode, frames are no-ops
  and the helpers get `&rg_vu0` = the global file, i.e. unchanged)

Test: `src/sce/vu0/vu0native_local.c` / `vu0native_tests.c` `local` now checks the
frame semantics (a value set in one call reads as reset in the next, in either file; a
frame helper writes its caller's file; the named context is still shared) instead of
the per-file register file; `--wrong` still flips one expectation.

**Verification** (build dirs `build/ovu0-i686/{native,local}`, -O2, RG_NATIVE_ONLY=ON;
exes kept in `out/ovu0/exe/{native,local}-{before,after}`; "before" = the tree with the
per-file fallback, "after" = overrides + libvu0 converted AND the fallback removed):

| Check | Result |
| --- | --- |
| build without the file-scope register file (= `--strict-vu0` for everything, not only game/) | 0 errors in game/, overrides/, missing/; one test file needed a frame (`vu0native_ieee.c`) |
| native, before vs after, `regen.py --check 300` power-on -> 32,220 (8 milestones + 8 checks) | **IDENTICAL**: vbl, run hash, check run hash and frame hash (`out/fixtures/eb062770993a40dd` vs `264f6603ac6b672f`) |
| local, before vs after, power-on -> 27,300 (title, field, battle, battle_won + checks) | **IDENTICAL** incl. frame hashes (`5115366865db9790` vs `339211dec60e490a`) |
| `verify.py` on the native-after set | 8/8 OK (run hash and frame) |
| `bootcheck.py --all`, native-after | 29/29 PASS (20 in the first pass; 9 library cards failed at start with exit 1 / no STATUS, all 9 PASS on the immediate rerun: environment, not the exe) |
| `bootcheck.py factory` | before: **FAIL** (crash 0xC0000005 in `FactoryPartObjSetFuncFlag_4fd260+0x8`, the regression the lead saw in build/play-i686), both native and local; after: **PASS**, both modes (4 runs, deterministic) |

So the factory regression of the 18:37 tree is NOT caused by this conversion (the
before exes were built from the unconverted tree and crash the same way); the
conversion removes it: some converted VU0 function on the FACTORY path read a
register its own call had not written, i.e. whatever the previous call of a function
in the same file had left in the per-file register file (exactly the hazard the
frames remove). Which file was not bisected (objbisect needs both object sets).

**Stage proposal** (tools/stages/vu0frame.py, owner: ingest): adopt the two widenings
above (a `BOUND`-like list of file-local macros whose body names the model, and the
helper fixpoint). Neither changes game/ today (`--strict-vu0` = 0 there and no game
file defines such macros or a helper-only static helper chain), but both make the
stage safe for future hand-written or re-ingested files; the override tool would then
only add the scan roots and the two skips.

## Checkpoint (2026-10-18)

- **UB census**: static 913 warnings, dynamic 94 UBSan sites (tables above). Fixed by flag:
  float->int saturation (`-fno-strict-float-cast-overflow`, the class that made builds
  differ), pointer wrap (`-fwrapv-pointer`), no forward-progress assumption
  (`-fno-finite-loops`); already defined: uninitialised locals (zero init), signed
  overflow (-fwrapv), null checks kept, strict aliasing off. Reviewed, no fix needed:
  misaligned over-aligned structs, out-of-bounds struct/extern views (contiguous retail
  data image), -Wreturn-type in C, one unsequenced expression (frontend-ordered).
- **Run hashes moved** with the float-cast flag (audio volume / TexAnime values); the
  route's milestones are at the same vbls and still reach `saved`. Fixture sets regenerate
  per exe as usual; any lane comparing run hashes against a pre-flag exe must rebuild.
- **-O2**: identical to -O1 on the whole route (8 milestones + 8 checks, run and frame
  hashes, same host code); verify.py 8/8; full ctest in build/o2-i686/o2: 710/711 before
  the devirt tolerance, then the devirt/protos/hwbus/bindings/vu0native labels 48/48.
- **vu0frame**: in game/ (145 frames, 38 helpers); native O1 identical before/after;
  local frames vs no-frames identical to 27,300. **Second lane (same day)**: the 63
  hand-written overrides + libvu0.c converted (`tools/native/override_vu0frame.py`),
  the file-scope fallback REMOVED from port/vu0.h (only `RG_VU0_NO_FRAMES` keeps it, for
  A/B); native route identical to 32,220, local identical to 27,300, verify 8/8,
  bootcheck --all 29/29; fixes the FACTORY crash. Full ctest on a fresh default build
  (build/ovu0-i686/native): 712/713, the one failure `native_only.link_audit` was a
  stale generated test (the renderer lane renamed a link-audit set in the source while
  the build was configured); it passes after re-configure. No flaky test seen.
- **RG_OVL_DATA**: 3 sites are direct references; the macro is no longer emitted.
