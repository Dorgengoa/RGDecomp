# Native CPU side: VU0 macros, hardware registers, the memory map (de-emulation lane: CPU)

PLAN.md D9 / "Native end state": *"VU0 macros on a VU0 model, `vcallms` microprograms ->
Plain C/SIMD math functions"* and *"32 MB EE-RAM block, scratchpad, uncached masks, hwbus
-> Ordinary host memory; accessors and masks removed from game code"*. Same pattern as
NATIVE-FS / NATIVE-AUDIO / NATIVE-IOP / NATIVE-THREADS: census script, design, native
replacement at the highest sensible boundary, the old path kept as the oracle behind a
switch, verification against it.

Status (2026-10-18): **VU0 done for the game path in the default build.** `RG_VU0_MODE=local`
(now the default) has no global VU0 register file and no VU interpreter on the game path:
every file computes on its own state (two cross-file protocols on named contexts), the
only microprogram is native C, and the build is **bit-identical to the model** over the
golden route (power-on to 31,700, run hash, 6 frames, 37 milestones). `native` (IEEE
floats) works and is faster but plays the first fight differently (section 3). hwbus:
census done, no CPU-side site left (all remaining accessors belong to the renderer, the
dead movie IPU path or the T0 timer); memory map: assessed, plan in section 6. Residue and
owners: section 7. **Residue cleanup (section 8):** the game heap is one ordinary allocation
with an explicit retail mapping (save states format 2), T0 is the native logic-time clock,
the dead IPU layer is stubbed, the runtime binds no VU0 outside `model`; hwbus is left with
the renderer's 11 sites.

| Part | Where |
| --- | --- |
| Switch | `RG_VU0_MODE` CMake cache entry (top-level `CMakeLists.txt`): `model` (oracle), `local`, `native` |
| VU0 headers | `include/port/vu0.h` (call-site state, TU-local register file, native float rules, `rg_vu0_srt`), `include/port/vu0_ctx.h` (named shared contexts) |
| Native microprogram | `src/native/vu0/vu0_srt.c` (`rg_vu0_srt`, the game's only VU0 microprogram as C; moved from src/sce/vu0 2026-10-25) |
| Shared contexts | `src/native/vu0/vu0_ctx.c` (`xfbox`, `colltri`) |
| Native libvu0 | `src/native/vu0/libvu0_native.c` (`rg_native_vu0`: the sceVu0* functions as plain C lanes; what a native-only rg-game links, section 9) |
| Libraries | `rg_vu0` / `rg_sce_vu0` follow the mode; `rg_vu0_oracle` / `rg_sce_vu0_oracle` are always the model (tests); `rg_native_vu0` replaces `rg_sce_vu0` in a native-only rg-game |
| Game side | overrides `matrix/MatFromSRTVu0_13bc90.c`, `matrix/MatRotateVu0_13bc20.c` (native SRT), `camera/AabbLoadToVu_13bfc0.c`, `camera/AabbPlaneDistances_13bf50.c`, `math/BoxToCenterExtentsVu0Maybe_14ff40.c`, `math/BoxTransformExtentsVu0Maybe_14fed0.c` (context `xfbox`), `model/CollFrameTreeCollectTris_16bfb0.cpp`, `model/CollTriTransform_16c1a0.c` (context `colltri`) |
| Census tools | `tools/native/vu0_census.py static` -> `census/native_vu0_static.tsv`, `native_vu0_livein.tsv`, `native_vu0_clobber.tsv`; `tools/native/hw_census.py static\|summary` -> `census/native_hw_static.tsv` |
| Tests | `ctest -R vu0native` (`rg-vu0native-tests`, + `vu0native.control`); `ctest -L port` (`vu0`), `-L bindings` (now on the oracle libraries) |
| Compare | `tools/native/vu0_compare.py --exe model=... --exe native=...` (run hash, shots, timing milestones, image metrics) |
| Build | `powershell -File tools/native/vu0_build.ps1 -Mode native [-BuildDir build/nvu0-i686] [-Targets rg-vu0native-tests,rg-game]` |

## 1. VU0 census

### How to rerun

```
python tools/native/vu0_census.py static [--jobs 2]     # ~25 s, clang -E on ~350 files
```

It takes the compiled set (game/ MANIFEST unit/data with overrides/ in place, missing/
stand-ins, the libvu0 provider), keeps the files that touch the model, runs each through
`clang -E` with the game include order, and reduces every function to a sequence of
register events (read / write, with lane masks) on vf0-31, ACC, Q, I, P, R, clip, vi1-15
and the EE GPR temps. Per function it reports the **live-in** lanes (read before any write
in the function; vf0 excluded, it is a constant): a live-in is the only way a value can
travel between functions through the register file. Same-file helper calls are applied
(a helper's reads, then its writes), and `scope` classifies what is left.

### Result (2026-10-18)

351 files: 278 game, 72 overrides, the provider `src/sce/vu0/libvu0.c`.

| Form | Sites | What it is |
| --- | --- | --- |
| `RG_VU0_BIND_VF` / `_ACC` / `_Q` | 427 / 27 / 12 | `vu0bind` stage: an mwcc `asm("vfN")` binding as an lvalue on the register file |
| mwcc intrinsics (`_vmul`, `_vmaddbc`, ...) | 332 | `include/port/vu0intrin.h`: value functions + write-back of the destination |
| `rg_vu0_*` calls | 1,008 | `vu0asm` stage output and the hand ports (overrides, libvu0.c) |
| libvu0.h-style names (`Vu0*(`) | 149 | the port's `include/libvu0.h` macros (count includes game functions named `Vu0*`) |
| `vu0inline.h` users | 5 | the 7 inline helpers |
| `vcallms` | 2 | `MatFromSRTVu0_13bc90`, `MatRotateVu0_13bc20` (program 0x0) |
| `sceVu0*` calls | 444 (143 files only call these) | `src/sce/vu0/libvu0.c` |

Functions with VU events: 255. Live-in: 20, all explained:

| Scope | Functions | Meaning |
| --- | --- | --- |
| `ctx:xfbox` | `AabbPlaneDistances_13bf50`, `BoxTransformExtentsVu0Maybe_14fed0` | read vf7, vf10-12 left by `AabbLoadToVu_13bfc0` / `BoxToCenterExtentsVu0Maybe_14ff40` (callers `AabbInFrustum_13be60`, `ModelPrepareDrawMaybe_14f760`) |
| `ctx:colltri` | `CollTriTransform_16c1a0` | reads the matrix vf10-13 `CollFrameTreeCollectTris_16bfb0` loads before its loop |
| `tu-helper` | `StoreMatrix`, `ScaleMul`, `InvScaleMul` (x2-3 files), `rot_apply` | static inline helpers fed by their callers in the same file |
| `param-reg` | `QuatSlerp_13c270`, 4 `sceVu0*` | write a register named by a parameter (`rg_f2vf(11, u)`), reviewed: same file |
| `provider` | `ecossin`, `sceVu0RotMatrix{X,Y,Z}` | libvu0.c static helper chains (reviewed) |

So, before the contexts were introduced, exactly **two cross-file register protocols**
(vf7/vf10-12 and vf10-13) and the **vcallms boundary** carried values between files; no
other function reads a register another file wrote. `native_vu0_clobber.tsv` (a read
after a call into another file that writes that register, i.e. code that relies on a
callee NOT clobbering) is empty.

Kept lanes (`lanein`, 55 functions): lanes a masked write keeps and the function later
reads or stores. Almost all are the upper GPR words of `mfc1 + qmtc2` (only lane x is
used) and `vmr32`/`mr32` sums; four store a kept w lane (`MtxInverseAffine_1cb640` vf9.w,
`MatFromQuat_13c440` vf3.w, `CollTriTransform_16c1a0` vf22.w, `VecTriCross_13de70`
vf12.w): on the EE that w is whatever the last writer of the register left. With a per-file
register file it is what the last writer *in the same file* left (deterministic, 0 at
start); the run comparison (section 3) shows whether any of it is observable.

Limits: textual order, not control flow (a conditional write followed by a read counts as
defined; a loop-carried read counts as live-in). The run comparison is the proof.

## 2. Design

### Three modes (`RG_VU0_MODE`)

| Mode | Register file | Float rules | `vcallms` | Use |
| --- | --- | --- | --- | --- |
| `model` | one global `rg_vu0` (src/ps2/vu0.c) | VU (chop, clamp, no denormals) | src/ps2/vu interpreter on the shared state (vu0_micro.c) | the bring-up model; the oracle |
| `local` | one per translation unit (`static rg_vu0_tu_`), named contexts for the 2 protocols | VU | native `rg_vu0_srt` | must be bit-identical to `model` |
| `native` | as `local` | IEEE single, round to nearest; x/0 = +-max, sqrt\|x\| kept | native `rg_vu0_srt` (IEEE form) | the target |

The mode is a compile definition on `rg_game_headers` (game code), `rg_sce_vu0` and
`rg_vu0` (`RG_VU0_LOCAL`, `RG_VU0_IEEE`). `RG_VU0_ORACLE` forces the model in one file or
target (rg-test-vu0, the bindings suites, the oracle libraries).

### How the header makes the register file per file

`port/vu0.h` used to define every op as an inline function on the global `rg_vu0`. Now
each op is `rg_vu0s_<op>(rg_vu0_state *S, ...)` and the old spelling is a macro that names
the state **at the call site**: `#define rg_vu0_fmac(...) rg_vu0s_fmac(&rg_vu0, ...)`.
The vu0bind lvalues (`RG_VU0_BIND_VF(n, T)` = `*(T *)&rg_vu0.vf[n]`) already expand at
the use. With `RG_VU0_LOCAL`, `rg_vu0` is `#define`d to a `static` register file of the
translation unit (vf0 = (0,0,0,1)), so every macro, intrinsic, bound variable, vu0inline.h
helper and libvu0.h macro of that file uses it. No game file and no stage changes.

A file of a cross-file protocol instead does

```c
#define RG_VU0_CTX_NAME xfbox
#include "port/vu0_ctx.h"      /* rg_vu0 -> extern rg_vu0_ctx_xfbox */
```

at its top (the 6 overrides listed above; 4 are verbatim copies of the game file plus
these two lines). `src/sce/vu0/vu0_ctx.c` defines the contexts. Under `model` the header
does nothing.

Why per file and not per function: the vu0bind stage defines the bound names at file
scope (`#define va154200 RG_VU0_BIND_VF(1, ...)`), so a header cannot give each function
its own locals; the census shows per function would also be correct (section 4 proposes
the stage change). A per-file static is not the global model any more (no state shared
between files, nothing to synchronise with an interpreter), and it is what the stage
change needs as its first step.

### Native float rules

`RG_VU0_IEEE` (`native`): `rg_vu_addf/subf/mulf/divf/sqrtf` are plain IEEE single
(`-msse2 -mfpmath=sse`, round to nearest), as all other game float code on the port is,
with the VU rule kept exactly where the two part ways in a way the game can see:

- a **non-finite result** (overflow, or an input with exponent 255, which the VU reads as
  a number; 0x7FFFFFFF is the VU maximum, and the model itself produces it) is recomputed
  with the VU rule (clamp to +-max), so no Inf/NaN enters game state that the model would
  not also produce;
- **x / 0 and x / denormal** give +-max with the xor sign; sqrt takes |x|;
- an add/sub with **+-1.5*2^23** as an operand uses the VU's round-toward-zero: the
  round-to-integer idiom `x + 1.5*2^23 - 1.5*2^23` (`VecWrapAngle_1cbe90`,
  `VecSinCos_1cbfb0`, `sceVu0ecossin`, the vcallms program) is floor/trunc on the VU,
  round() in IEEE;
- `vftoi` saturates to int32 (C conversion of an out-of-range float is undefined).

Not kept: round toward zero of ordinary results, flush of denormal inputs/results. Each
fallback is one predictable compare on the fast path. Section 3 shows why the first two
rules are needed (without them the first battle breaks).

### The microprogram (`vcallms 0x0`) as C

The game's only VU0 microprogram (VIF0 chain `D_00445810`, micro address 0, 112 pairs;
`rg-vucensus --dis` prints it) builds `diag(s) * Rx * Ry * Rz` with row 3 = (t.xyz, 1)
from scale vf1, Euler angles vf2, translation vf3, into vf4..vf7. `vu0_srt.c` is its C
form: every FMAC op of the program in program order on the same lanes, the MAC zero
flags of `addx.xyz vf00, vf02, vf00x` + FMAND/IBEQ as three `if`s (all angles zero; x and
y zero; z zero), and each I-bit pair's immediate used by the NEXT pair's upper op. The
sin/cos is the program's own polynomial (range reduction to |frac(|a|/2pi) - 0.5| - 0.25,
odd polynomial in 2pi*y).

One step needed a native form: the range reduction's integer part is computed as
`acc - 1.5*2^23 + 1.5*2^23` on `acc = -|a|/(2pi)`, which is `-floor(|a|/2pi)` only
with the VU's round-toward-zero adds. With IEEE rounding it becomes `round()` and the
result is wrong (0.65 off). `reduce_int()` keeps the two VU ops under VU float rules and
says `ceil(acc)` under `RG_VU0_IEEE`.

`MatFromSRTVu0_13bc90` calls `rg_vu0_srt` directly; `MatRotateVu0_13bc20` calls it with
unit scale / zero translation and then does the listing's row products in the same
order, on locals. Under `model` both keep `rg_vu0_vcallms`. With `RG_VU0_LOCAL`,
`rg_vu0_vcallms` refuses (prints, returns -1): no interpreter on that path.

### What the native exe still has

`src/sce/vu0/libvu0.c` (the sceVu0* surface, 444 game call sites) is unchanged code on
its own per-file register file: correct by the census (its helpers are static), plain C
under `native`. The vu0asm / vu0bind output in 208 game files is unchanged text; under
`native` it is value math through the per-file state.

## 3. Verification

### Unit (`ctest -R vu0native`)

`rg-vu0native-tests` (`src/sce/vu0/vu0native_tests.c`, `vu0native_ref.c`):

- **srt**: `rg_vu0_srt` with VU float rules against the src/ps2/vu interpreter running
  the retail program (loaded from the retail ELF as GfxSysInit uploads it): **200,000
  inputs, 0 mismatches, bit-exact** (cases cycle through all three zero-angle branches,
  denormal / -0 angles, angles to +-100, random bit patterns, denormal scale).
- **srt_ieee**: the IEEE form against the VU form: max 1.28e-6 of the row scale; VU form
  against S*Rx*Ry*Rz in double 2.2e-6, IEEE form 2.9e-6.
- **local**: two `RG_VU0_LOCAL` files keep separate vf5; two files on the named context
  `vntest` share it.
- **ieee**: round to nearest, x/0 = +-max (3 sign cases), sqrt(-4) = 2, ftoi
  truncation and saturation, a broadcast multiply, on the per-file register file.
- `vu0native.control` (`--wrong`) flips one expectation per check and must fail.

### Golden route (model vs local vs native)

`tools/native/vu0_compare.py`, `tools/trace/goldens/newgame_save1.input.txt`, headless,
`RG_GPU=hw`, the three builds from the same tree (2026-10-18; `out/nvu0/exe/{model,local,native}`):

**model vs local: bit-identical.** Power-on to field 31,700: run hash `f3b853eebb958224`
both, frames identical at 8,500 / 23,300 / 26,800 / 28,800 / 30,000 / 31,700, 37 timing
milestones at the same VBlank, 0 of 37 segments with a different main-tick count
(`out/nvu0/mlroute.txt`); power-on to 9,000 with shots at 1,800 / 5,000 / 8,000 / 8,500 /
9,000 also identical (run hash `666df4b479ffa33d`). So the per-file register files, the
two named contexts and the native microprogram change nothing observable, including the
kept-lane (garbage w) cases of section 1.

After the bring-up lane's re-ingest (game_protos.h regenerated, 355 files) and the
default switch, both rebuilt from the same tree: power-on to 23,300, run hash
`443ab97d3aacc893` both, frames identical at 1,800 / 8,500 / 23,300, 25 milestones, 0
segments different (`out/nvu0/final.txt`). Fixtures on the `local` exe
(`regen.py --only title,field,battle --check 300` + `verify.py`, set
`out/fixtures/6d0c18241532d2dd`): title, field and battle load-and-run-300 reproduce the
power-on run hash and frame. ctest in the `local` build dir: `vu0`, `vu0native(.control)`,
`bindings*`, `hwbus*`: 29/29 pass.

(Note for the route owners: on this tree the route no longer reaches "saved" -- both
builds enter a second battle at vbl 30,057 instead of the transporter menu; it is the
same in `model`, i.e. not caused by this lane.)

**model vs native (first try): diverged in the first battle.** Same 23 milestones to vbl
22,957 (battle intro unlocks), frames identical at 1,800 and PSNR 57.7 dB at 8,500 (ulp
differences), then the battle scene rendered blue (no world) and the route was lost.
Cause: the VU round-to-integer idiom `x + 1.5*2^23 - 1.5*2^23` in `VecWrapAngle_1cbe90`
(angle wrap to [-pi, pi]), `VecSinCos_1cbfb0` (via `Vu0SinCosAccR`), `sceVu0ecossin` and
the vcallms program: with VU chop rounding it is floor; with IEEE nearest it rounds, so
angles wrap by 2 pi and sin/cos range reductions break -- that alone did NOT change the
run (same run hash), so the second class was added: non-finite results / exponent-255
inputs / division by a denormal go to the VU rule (the model's own +-0x7FFFFFFF "max" is
a NaN bit pattern in IEEE and poisoned everything it touched). Both rules are in
`port/vu0.h` (`rg_vu_magic`, `rg_vu_nonfinite`) and unit-tested (`vu0native` `ieee`).

**model vs native (with the rules): same game up to the first battle's fight, then a
different fight.** `out/nvu0/mnroute2.txt`: the first 27 of 37 milestones at the same VBlank
with the same main-tick counts (title, opening, field, battle start, the "Basic Battle
Controls" tutorial at 23,300 -- frames PSNR 57-99 dB, 0 % bad pixels at 1,800 / 8,500 /
23,300), then the fight itself plays out differently under the scripted input (battle
won at vbl 26,227 instead of 25,965; 5 segments with a different tick count; frames from
26,800 on are a different moment of the game). This is the expected sensitivity of a
real-time fight to last-bit rounding (the same class as NATIVE-THREADS "an outcome
difference after the last common milestone"): IEEE round-to-nearest differs from the
VU's chop in the last bit of most results. Cost: field 7,000-9,000 mean step 7.5 ms
native vs 9.5 ms model (the VU float model's double conversions), battle windows not
comparable (different scenes).

**Decision: the default is `local`** (`RG_VU0_MODE` default in CMakeLists.txt): no global
register file and no interpreter on the game path, plain C value math through per-file
state, and bit-identical to the oracle, so the golden route, fixtures and every lane's
run-hash comparisons keep working. `native` stays one switch away; making it the default
is a product decision (accept that recorded inputs / goldens re-baseline) and should come
with re-recorded goldens. A middle way, if wanted: IEEE with the MXCSR rounding mode set
to toward-zero around VU math would reproduce the chop for ordinary results.

## 4. Stage proposal: function-local VU registers (tools/stages is the bring-up lane's)

**Done 2026-10-18** as the ingest stage `vu0frame` (tools/stages/vu0frame.py; design and
verification: docs/UB-AUDIT.md "vu0frame"). It differs from the proposal below in one
point: the bound names keep `RG_VU0_BIND_VF` (they already name `rg_vu0` at the use, and a
block-scope `rg_vu0` declared by `RG_VU0_FRAME` shadows the file-scope one), and static
helpers called within the file take the caller's file by pointer (both directions of the
old per-file sharing). The file-scope register file remains only as the fallback for
frame-less code (61 hand-written overrides, libvu0.c, the vu0native test).

With the census result the bound registers can be plain locals, which clang keeps in SSE
registers (a per-file static has to stay in memory: game stores through pointers may alias
it under `-fno-strict-aliasing`). Proposed `vu0bind` change, no new port semantics:

1. Keep the file-scope `typedef`s. Replace `#define NAME RG_VU0_BIND_VF(n, T)` by
   `#define NAME RG_VU0_LVF(n, T)` and emit `RG_VU0_FRAME;` as the first statement of
   every function body that uses a bound name, a `vu0asm` call or a libvu0.h macro.
   `port/vu0.h`: `#define RG_VU0_FRAME rg_vu0_state rg_vu0_l_ = rg_vu0_reset_` +
   `#define rg_vu0 rg_vu0_l_` inside such functions (a block-scope macro is not possible,
   so the stage emits `#define rg_vu0 rg_vu0_l_` before and `#undef` after each function,
   or names the frame variable `rg_vu0` directly: a local `rg_vu0_state rg_vu0` shadows
   the file one).
2. `static inline` helpers that the census marks `tu-helper` (they read registers their
   caller left: `FrameCalc*` `ScaleMul`/`InvScaleMul`/`StoreMatrix`) get the caller's frame:
   the stage adds `rg_vu0_state *rg_vu0_p_` as first parameter and passes `&rg_vu0` at
   each call (`#define rg_vu0 (*rg_vu0_p_)` inside). 9 helpers in 4 files.
3. The two `ctx:` protocols keep their named contexts (they are real cross-function state).
4. Check: `vu0_census.py` must report 0 `cross` rows, and the `local` build must stay
   bit-identical to `model` (section 3).

## 5. Hardware registers, scratchpad, masks (hwbus)

### How to rerun

```
python tools/native/hw_census.py static     # ~20 s, text only
python tools/native/hw_census.py summary
```

Kinds: `hw` (HW_R*/HW_W* sites and direct hw_r*/hw_w* calls; address -> register ->
owning model -> the lane that removes it, from the docs/HWBUS.md claims table), `spr`
(PS2_SPR / hw_spr_base), `mask` (PS2_PHYS / PS2_UNCACHED / PS2_UCAB), `ovl` (RG_OVL_DATA),
`lit-hw` (a hardware address used as a pointer outside the accessors), `data-hw` (a
register address in a data table), `lit-spr` / `lit-kseg` (literals for review: they are
DMAtag ids / flag bits, see below).

### Result (2026-10-18)

| Kind | Sites | Where | Lane that removes it |
| --- | --- | --- | --- |
| `hw` IPU / D3 / D4 | 31 | `ViBuf*` (7 movie functions) | movie: **unreachable** with the native movie player (MOVIE.md "no longer reached"); dead code |
| `hw` GS privileged | 10 | `GsDbufPutEnv_144150` (PMODE, DISPFB1, DISPLAY1), `SysInitHardware_15e670` (PMODE), override `GfxVblankStartHandler_15df20` (CSR) | renderer |
| `hw` D_ENABLER/W | 8 | `ViBufSetD3Chcr`, `ViBufSetD4Chcr` (movie, dead) | movie |
| `hw` VIF1 | 1 | `Vif1IntcHandler_15e170` (FBRST.STC) | renderer (VIF1 completion as a direct call, NATIVE-THREADS section 5) |
| `hw` T0 timer | 6 | `GfxEndFrame_141c20` (T0_COUNT read + reset), `GfxFlipBuffersMaybe_143650` (2 reads), `Vif1IntcHandler_15e170` (latch), `GfxSysInit_15dd20` (T0_MODE = 0x83) | threads: T0 is already nominal logic time in the kernel's register model; native form = the frame driver's logic time (NATIVE-THREADS section 5, "T0..T3 register model") |
| `lit-hw` | 1 | `sdk/KernelReleaseAlarm_4473a0.c` (INTC_STAT; also T1 through KSEG1 `0xB0001800-20`) | none needed: kernel-image code (its data is kernel RAM `D_8007xxxx`); compiled but referenced by nothing (the kernel HLE implements alarms) |
| `data-hw` | 18 | `data2c_00445F20` (libdma channel table: D0-D9 base addresses), `data2c_00446648` (libgraph/libdma register table) | SDK data read only by the SDK asm the port replaces (src/sce); renderer / IOP |
| `spr` | **0** | no game or port code uses PS2_SPR / hw_spr_base (only the hwbus tests) | nothing to convert |
| `mask` | 39 | PS2_PHYS / PS2_UNCACHED / PS2_UCAB: already the identity; every site builds a DMA tag or packet address (`DrawList*`, `DmaPktAddCallTag*`, `TexBuildClutUploadPkt`, `GsUploadImage16Blocks`, `ModelMeshBuildUnpackPkt`, `GfxEndFrame`, ...) or is movie dead code | renderer (packet builders go native) / movie |
| `ovl` | 3 | `RG_OVL_DATA` in `CharaGetControlStateMaybe_2f5320`, `FieldHudGetSuggestMember_203c20`, `FieldHudInitOnce_204120` (NORMAL's `D_00527020` + 0x3A2 / 0x3AE) | overlay manager (already resolves; not hardware) |
| `lit-kseg` | 14 | `\| 0x20000000` game flag bits (6), `\| 0x30000000` DMAtag REF ids (7), `ViBufAddDma`'s CHCR value | none: not addresses (HWBUS.md LEAVE_RULES) |
| `lit-spr` | 5 | `0x70000003` / `0x70000000` DMAtag END words | none: not scratchpad |

**No raw EE-RAM pointer literal** (`(T *)0x00100000..0x01FFFFFF`) is left in compiled code
(`lit-ram` = 0): data->C relocated them (DATARELOC.tsv), the two overlay literals are
`RG_OVL_DATA`.

Masks outside game code that still need host pointers below 0x10000000 (for the memory
map, section 6): three renderer overrides keep retail's `& 0x0FFFFFFF` on DMA addresses
(`gfx/RefractionCaptureFrame_13ffd0.c`, `gs/DrawCtxAddChangedCallTags_13fd70.c`,
`gs/GsPktOpen_13f4a0.c`), `src/ps2/dmac/dmac.c` maps `0x7xxxxxxx` to the scratchpad,
`src/sce/graphics/libpkt.c` applies `& 0x9FFFFFFF` to non-host-mode addresses.

### Conversions made here

- `rg_ovl_data` is its own library (`src/ps2/hwbus/CMakeLists.txt`): RG_OVL_DATA is
  overlay resolution, not hardware; a build without the bus can keep it. `rg_ps2_hwbus`
  links it, so nothing else changes.
- Nothing else in game code is CPU-side: every remaining accessor belongs to the
  emulated GS/VIF/DMAC path (renderer), the dead IPU path (movie) or the T0 timer
  (threads). They are listed above with their owners; none was changed here (the files
  are those lanes' overrides / generated code, and a T0 redirect needs the frame driver's
  logic-time API, which does not exist yet).

### Proposals

- **threads**: `unsigned rg_frame_logic_t0(void)` (T0_COUNT of the current frame in logic
  time). Then `include/port/hwaccess.h` can route constant-address T0 accesses without a
  bus: `#define HW_R32(a) (__builtin_constant_p(a) && (a) == 0x10000000u ?
  rg_frame_logic_t0() : hw_r32(a))`, and `T0_MODE` / `T0_COUNT = 0` writes become no-ops.
- **movie**: the 7 `ViBuf*` functions are unreachable natively; an override set that
  makes them assert (or drops them with their callers) removes 39 of the 56 accessor sites.
- **renderer**: GS privileged writes -> the native display state; VIF1 FBRST + the T0
  latch go with the VIF1 completion call; the 39 identity markers and the 3 `&
  0x0FFFFFFF` overrides go with the packet builders.

## 6. Memory map

### What still depends on the 32 MB EE-RAM block (2026-10-18)

The block (`src/runtime/crt0.c`, `rg_crt0_init`) is 32 MB + 4 KB, page aligned, "laid
out like EE RAM": host `base` = PS2 address 0. What lives in it and what relies on the
layout:

| Dependency | Who | Needs |
| --- | --- | --- |
| The game heap: retail newlib/dlmalloc over `sbrk` on `[base + 0x528200, base + 0x1FD0000)` (0x1AA7E00 bytes) | `src/crt/crt_heap.c` (retail-exact allocator, its state bound to the retail .data words), crt0 `sbrk`/`EndOfHeap` | the retail **capacity** (the game sizes its arenas by probing: `SysCalcFreeHeapMaybe` mallocs "everything", then 25 MB; the last 25.9 MB arena fits only with retail-identical chunk placement), and heap start **≡ 0x528200 mod 4 KB** (page rounding, trim and `memalign` decisions depend on the address bits). It does NOT need the 5.4 MB below the heap or the 0x30000 stack area above it: nothing is placed there |
| Heap probe constants | override `sys/SysCalcFreeHeapMaybe_15e1d0.c` (`0x00030000`, `0x00528200` as numbers) | the retail values; independent of where the block is |
| DMA addresses are host pointers | emulated DMAC/VIF/GIF path (renderer lane): tag ADDR is 31 bits, bit 31 = scratchpad; `dmac.c` treats `0x7xxxxxxx` as SPR | block below 2 GB (exe not large-address-aware) |
| 28-bit masks on DMA addresses | 3 renderer overrides (`RefractionCaptureFrame_13ffd0`, `DrawCtxAddChangedCallTags_13fd70`, `GsPktOpen_13f4a0`); runtime.c warns | block (and every packet buffer) below 0x10000000; that is why Windows takes the lowest free range from 0x04000000 |
| Save states | `src/savestate`: section `ram` = the block, raw, at a fixed address (0x0A000000 through `rg_crt0_set_ram_provider`) | a fixed address and size (states load only into the same exe anyway) |
| Retail-address view | `src/trace/trace_runtime.c` (`rg_trace_set_ram(base, HEAP_START, RAM_SIZE)`), `RG_SS_AUDIT=2`, `RG_STATUS_DUMP` users | `host - base` = the retail address, so port traces of heap pointers compare with PCSX2 traces |
| Literal addresses in game code / data | none: `hw_census.py` finds 0 raw EE-RAM pointer casts; data->C relocated data pointers (DATARELOC.tsv); MAIN -> overlay literals are `RG_OVL_DATA` (3 sites) | nothing |
| Scratchpad | `PS2_SPR` has 0 users; the DMAC model owns its 16 KB `spr[]` | nothing on the CPU side |
| MAIN .data/.bss, overlay arena | host statics (`rg_ovl_arena`), exe linked `/DYNAMICBASE:NO` for save states | not in the block |

So the block is, in effect, one host allocation for the retail heap whose placement is
constrained by the emulated DMA path (renderer) and whose address convention serves the
trace tools and save states.

### Plan to ordinary host memory, keeping save states

1. **Now (done, no code change needed):** game pointers are host pointers, statics are
   host statics, no PS2 literal address is dereferenced by game code, the scratchpad has
   no CPU user, the uncached/physical masks are identity markers (section 5).
2. **When the renderer's packet builders are native** (no DMA tags with host pointers,
   the 3 masking overrides gone): drop the below-0x10000000 / below-2 GB placement rules
   and the runtime.c warning; any address works.
3. **Heap as an ordinary allocation:** allocate only the heap, `0x1AA7E00` bytes, with
   its start at `page + 0x200` (so start ≡ 0x528200 mod 4 KB and every page-rounding
   decision of the retail allocator is unchanged), and keep `crt_heap.c` as is (retail
   capacity and placement behaviour, which the game's arena sizing needs). The retail
   view becomes a mapping instead of a layout: `retail = host - heap_start + 0x528200`,
   given to the trace code (`rg_trace_set_ram(heap_start - 0x528200, ...)` keeps every
   tool working unchanged). Saves 5.6 MB of address space; no behaviour change. Save
   states: the `ram` section becomes the heap range, still at a fixed address from the
   state region (`rg_crt0_set_ram_provider` already exists). Needs the savestate and trace
   owners to agree on the section/size change (states regenerate per exe anyway).
4. **Optional:** put the heap inside the state heap (`ss_heap.c`, one 26.7 MB block at
   init) so the state region has one heap instead of two; the game heap's internal layout
   stays the retail allocator's.
5. **Fixed addresses** (`/DYNAMICBASE:NO`, the state region, fiber arena) stay as long
   as raw save states are the fixture mechanism; a relocatable state format (symbolic
   pointers) is a separate project, not needed for D9.

**Update 2026-10-18: step 3 is done (section 8)**: heap-only allocation, explicit retail
mapping, save-state format 2, placement behind `RG_HEAP_DMA_PLACEMENT` for step 2.

What was implemented at the time of this plan: nothing in `crt0.c` (it carries the savestate lane's
uncommitted edits, and step 3 changes the `ram` section format, which that lane owns;
steps 2-3 are gated on the renderer). The analysis above is the deliverable; step 3 is a
~40-line change in `rg_crt0_init` + `rg_trace_set_ram` once agreed.

## 7. What remains and who owns it

(Updated 2026-10-18 by the residue-cleanup lane, section 8. Struck rows are done.)

| Residue | Where | Owner / next step |
| --- | --- | --- |
| ~~VU register state as a per-file static (not locals)~~ | | done: stage `vu0frame` (docs/UB-AUDIT.md); the file-scope fallback remains for 61 frame-less overrides + libvu0.c |
| ~~VU float rules (chop) in the default build~~ | | done: USER made `native` the default (2026-10-18) |
| `rg_vu0` global + `vcallms` on the interpreter | `src/ps2/vu0.c`, `vu0_micro.c` | only `RG_VU0_MODE=model` and the `*_oracle` test libraries; the runtime binds VU0 only in `model` (section 8), so a `local` / `native` rg-game no longer links `rg_vu0` (link-audit set `vu0`, forbidden by the native-only gate) |
| ~~HW accessors: GS privileged (10), VIF1 (1)~~ | | done 2026-10-18: port/hwaccess.h routes them to `src/native/render/nr_hw.c`; `rg_ps2_hwbus` is out of native-only rg-game (NATIVE-RENDER.md "Hardware register sites") |
| ~~HW accessors: IPU / D3 / D4 / D_ENABLE (39)~~ | 8 `ViBuf*` | done: stub overrides (section 8) |
| ~~HW accessors: T0 (6)~~ | | done: native logic-time clock (section 8) |
| Identity markers PS2_PHYS/UNCACHED/UCAB (33 now), `& 0x0FFFFFFF` in 3 overrides | packet builders | renderer; then `RG_HEAP_DMA_PLACEMENT 0` (section 8) |
| ~~RG_OVL_DATA (3)~~ | | done: direct references to the arena label `D_00527020` (hwaccess `overlay-data`, docs/UB-AUDIT.md) |
| ~~32 MB block layout~~ | | done: heap-only allocation + explicit retail mapping, save-state format 2 (section 8) |
| ~~Heap placement below 0x10000000~~ | | done 2026-10-18: `RG_HEAP_DMA_PLACEMENT` is 0 in RG_NATIVE_ONLY builds; the 3 masking overrides keep whole pointers (NATIVE-RENDER.md "DMA addresses") |
| ~~`rg_sce_vu0` (libvu0 on a per-file VU register struct)~~ | | done 2026-10-25 (section 9): `rg_native_vu0` (plain C lanes, bit-identical) in the native-only rg-game; link-audit set `vu0lib` |
| Fixed addresses (`/DYNAMICBASE:NO`, state region, fiber arena) | savestate | stay while raw save states are the fixture mechanism (section 6 step 5) |

## 8. Residue cleanup (2026-10-18): memory map, T0, movie IPU layer, runtime hooks

Build dir `build/ncleanup-i686` (`RG_NATIVE_ONLY=ON`, `RG_VU0_MODE=native`: rg-game +
rg-game-oracle). Runs under `out/ncleanup/` (game-derived, not committed).

### Memory map: the game heap as an ordinary allocation (section 6 step 3, done)

| Before | Now |
| --- | --- |
| 32 MB + 4 KB block "laid out like EE RAM", host `base` = PS2 address 0, heap = `[base + 0x528200, base + 0x1FD0000)` | **one allocation of the heap alone**: `RG_CRT0_HEAP_ALLOC` = 0x1AA7E00 + 4 KB; heap start = page + 0x200 (== 0x00528200 mod 4 KB, so crt_heap.c's page rounding / trim decisions are unchanged; the game memaligns to 16 only), end = start + 0x1AA7E00 (retail capacity: the arena probe fits as before) |
| `rg_ps2_ram.base` (the "host - base = retail address" convention) | gone. `rg_crt0_host_to_retail(p)` / `rg_crt0_retail_to_host(a)` are the explicit mapping (heap range only; 0 / NULL outside). Trace: `rg_trace_set_heap(host_start, 0x528200, size)` (trace_map.c stores the range start; `rg_trace_set_ram` stays as a wrapper for the tests). RG_STATUS_DUMP, port_trace / probe comparisons read through the trace map unchanged |
| placement below 0x10000000 always | behind **`RG_HEAP_DMA_PLACEMENT`** (rg_runtime.h, default 1; `RG_HEAP_DMA_LO` 0x04000000, `RG_HEAP_DMA_HI` 0x10000000): needed only by the still-emulated DMA path (DMA tags with host pointers, the 3 masking render overrides). crt0 (Windows lowest fit, else anywhere + the runtime warning; Linux low hints), the save-state region and runtime.c's warning follow it. **Renderer lane: set it to 0 when the packet builders are native.** |
| save-state section `ram` = the 32 MB block at 0x0A000000 | section `ram` = the heap allocation at 0x0A000000 (heap at 0x0A000200); **format version 2** (`SS_VERSION`, ss_core.c). A version-1 file is refused: "save state format 1, this build reads 2 (format 2: the ram section is the game heap, ...); regenerate it with tools/fixtures/regen.py". Same magic, so `fxlib.peek` still reads headers |

Saved: 5.3 MB of address space (the 5.4 MB below the heap and the stack area above it no
longer exist). Users of the old layout checked: crt_heap.c (break + page bits only), the
`SysCalcFreeHeapMaybe` override (retail constants), the ss_hooks audit (scans the heap now),
runtime_tests `crt0` / `gpu_smoke` (updated: start mod 4 KB, the mapping, placement only
under the flag).

### T0: native logic-time clock (section 5 proposal, done)

`include/port/hwaccess.h` routes the constant-address timer-0 accesses -- `HW_R32(T0_COUNT)`,
`HW_W32(T0_COUNT, v)`, `HW_W32(T0_MODE, v)` -- to `rg_logic_t0_count` / `rg_logic_t0_set_count` /
`rg_logic_t0_set_mode`, **new in `src/native/threads/rg_logic_time.c`** (library
`rg_native_threads`; three functions, no state). The compare folds at compile time (every
site passes a literal); other HW sites are unchanged.

- Native kernel (`RG_THREADS=native`, the only kernel of an RG_NATIVE_ONLY build): the native
  kernel table's timer 0 over logic time (`ps2k_hw_read32/write32`, rg_nk_irq.c): a flow's
  own work costs nothing, so the game reads the nominal frame profile. No bus.
- Oracle kernels (default build, `RG_THREADS=hle|service|frame`): through the hwbus as before
  (its per-read charge is part of their timing). `RG_THREADS_ORACLE=0` compiles that branch out.
- The 6 sites (`GfxEndFrame` x2, `GfxFlipBuffersMaybe` x2, the `Vif1IntcHandler` latch,
  `GfxSysInit`'s mode) are kind `logic-t0` in `hw_census.py` now.

### Movie: the dead IPU / DMA ch3-4 / D_ENABLE layer (done)

- Census tool **`tools/native/reach_census.py BUILD [--check F,..] [--why F] [--dead out.tsv]`**
  (new): static reachability over the linked rg-game (lld map + llvm-nm of every linked
  object; roots = every non-game object, a conservative over-approximation; one game
  function per object). This tree: 25,285 game objects, 21,416 reachable, 3,869 unreachable
  (`--dead` lists them: a dead-code census other lanes can use). All 8 `ViBuf*` functions
  with IPU / DMAC accesses are unreachable (`--check` exits 0).
- Overrides `overrides/src/main/movie/ViBuf{AddDma_1d4240, Delete_1d3e20, GetTs_1d3990,
  Reset_1d45b0, RestartDma_1d3e70, SetD3Chcr_1d4800, SetD4Chcr_1d47a0, StopDma_1d4180}`: body
  replaced by `rg_movie_g_unreachable("<name>")` (src/movie/mv_game.c: message + abort).
  HW sites in compiled code: 56 -> 11 (renderer only) + 6 `logic-t0`; masks 39 -> 33;
  kseg literals 14 -> 11.
- `src/movie/mv_runtime.c`: the IPU hwbus hooks and the fromIPU/toIPU DMAC bindings are gone
  (nothing can reach them); the service hook only sets the data root. `rg_movie_runtime` no
  longer links rg_ps2_hwbus / rg_ps2_dmac; test `movie.glue_ipu` removed (the hwbus keeps its
  own IPU stub, covered by `hwbus.ipu`).
- Dynamic confirmation: the golden route (attract movie, opening movie at vbl 3,149-7,319)
  runs through with the stubs in place; any call would abort.

### Runtime: dead emulation hooks

- `rg_vu0_micro_bind` (bind and unbind) is compiled only with `RG_VU0_MICRO_BIND`
  (src/runtime/CMakeLists.txt, `RG_VU0_MODE=model`). In local / native nothing references
  `rg_vu0`, so rg-game links no VU0 model (`rg_vu0` 0.9 KB -> gone).
- Left (renderer lane): VU0 / VU1 / VIF0 / VIF1 / DMAC / GS creation, `hwbus_bind` (GS
  privileged + VIF1 FBRST), the VU state in the runtime save-state hook.

### Verification (before = this tree built just before the edits)

| Check | Result |
| --- | --- |
| Golden route power-on to 31,700 (`nonly_route.py run`, native-only rg-game) | run hash **44cb9c3127bc1771 before = after**, 37 / 37 milestones at the same VBlank, **0 of 37 segments differ** (`out/ncleanup/route_{before,after}`) |
| Memory (same route) | peak private 359.1 -> 335.3 MB, working set 341.7 -> 317.9 MB (GPU driver variance dominates; the deterministic saving is the 5.3 MB) |
| Oracle twin, `RG_THREADS=hle RG_AUDIO=hle`, 3,000 fields | run hash 7e260c759300df6e before = after (the hwbus fallback keeps the oracle's timing) |
| Fixtures (`regen.py --check 300` + `verify.py`, after exe) | 16 states, all 8 milestones (title 1,500 ... saved 31,920; the route reaches "saved" again on this tree), **verify 8 / 8 OK** (run hash + frame at +300), set `out/fixtures/13a9fae2c458c2fd` (format 2). A format-1 state (`out/fixtures/58816d5808331d2a/title.rgstate`) is refused with the version message, exit 3 |
| ctest (build/ncleanup-i686, `RG_DATA` set) | `-j2 -LE fixtures` **704 / 704** + `-j1 -L fixtures` **6 / 6** (incl. `native_only.link_audit` with `vu0`, `runtime.crt0`, `trace.*`, `movie.*`, `hwbus.*`, `vu0native*`) |
| link_audit (native-only rg-game) | `check --forbid iop,kernel,vu0`: **PASS**; emulation 12 libs / 384.5 KB code -> 11 libs / 386.1 KB (rg_vu0 gone, rg_movie_runtime 1.0 -> 0 KB; the renderer lane's concurrent edits grew rg_gpu / gs / vu by 2.5 KB); exe 9,878,528 -> 9,878,016 bytes |

The renderer lane edited src/gpu, src/native/render and the runtime's GPU wiring while this
ran (the baseline needed a relink after their `nr_native_store_fn` landed); the route still
matched bit for bit.

### RG_NATIVE_ONLY is now the default

With the route, fixtures and ctest clean in the native-only build, `RG_NATIVE_ONLY`
defaults to **ON** (top `CMakeLists.txt`; a fresh configure prints the clone list and
`RG_NATIVE_ONLY:BOOL=ON`). rg-game is the native-only exe, `rg-game-oracle`
(EXCLUDE_FROM_ALL) the same-tree twin with the oracles (RG_IOP / RG_AUDIO=hle|compare,
RG_THREADS=hle|service|frame, RG_FS_ORACLE, RG_CDVD_MODEL); tests are unaffected (they never
link the clones). Existing build dirs keep their cached value (`-DRG_NATIVE_ONLY=OFF` for the
old default). Not tried: the Linux build with the new default.

### Files

New: `src/native/threads/rg_logic_time.c`, `tools/native/reach_census.py`, the 8 ViBuf
overrides. Edited: `include/port/hwaccess.h`, `src/native/threads/CMakeLists.txt`,
`src/runtime/{crt0.c, rg_runtime.h, runtime.c, CMakeLists.txt}`, `src/savestate/{ss_core.c,
ss_heap.c, ss_hooks.c, rg_savestate.h}`, `src/trace/{trace_map.c, rg_trace.h,
trace_runtime.c}` (mapping only), `src/movie/{mv_runtime.c, mv_game.c, movie_game.h,
CMakeLists.txt}`, `tests/movie/{movie_glue_tests.c, CMakeLists.txt}`,
`tests/runtime/runtime_tests.c`, `tests/native_only/CMakeLists.txt` (`vu0` set),
`tools/native/{link_audit.py, hw_census.py}`, top `CMakeLists.txt` (`RG_NATIVE_ONLY` default),
docs MOVIE.md, RUNTIME.md, TEST-FIXTURES.md, NATIVE-ONLY.md, NATIVE-THREADS.md (one row).

## 9. libvu0 as plain C (2026-10-25)

`rg_sce_vu0` was the last VU0-side library of the native-only exe: `libvu0.c` transcribes
each retail sceVu0* routine instruction by instruction onto the VU register struct
(`rg_vu0s_*` on a function-local `rg_vu0_state`), which is plain C under `native` but still
a VU model in form. `src/native/vu0/libvu0_native.c` (`rg_native_vu0`, with the
microprogram `vu0_srt.c` and the contexts `vu0_ctx.c`, both moved from src/sce/vu0) writes
the 17 functions on float lanes: the same operations in the same order with the same
per-lane rounding helpers (`rg_vu_addf/subf/mulf/divf/sqrtf` of port/vu0.h: IEEE + the VU
clamp rules under `native`, VU rounding under `local`), including the IEEE signed-zero
effects of the VU code's `0 + x` lane moves, so the results are **bit-identical** to
libvu0.c in the same mode. What libvu0.c leaves in its function-local register file is
unobservable since vu0frame, so nothing else is kept. Every source row is read before the
destination row is written (the aliasing calls the game makes).

- `cmake/native_only.cmake`: `RG_NONLY_REPLACE rg_sce_vu0=rg_native_vu0` unless
  `RG_VU0_MODE=model`; `tools/native/link_audit.py` set `vu0lib` (= `rg_sce_vu0`), forbidden
  by `native_only.link_audit`.
- `ctest -R native_vu0` (`rg-native-vu0-tests`, label `vu0native;native_only`): 20,000
  iterations (half with edge words: signed zeros, denormals, exponent-255 words, +-max,
  +-1.5*2^23, pi/2) of every function and every aliasing form against libvu0.c in the same
  mode, every output word compared; `native_vu0.libvu0_control` flips one bit (must fail).
- rg_sce_vu0 / rg_sce_vu0_oracle stay for the oracle twin and the bindings tests.

## Checkpoint

- 2026-10-25 (section 9): `rg_native_vu0` replaces `rg_sce_vu0` in the native-only rg-game
  (libvu0 as plain C lanes, bit-identical; srt / contexts moved to src/native/vu0); link-audit
  set `vu0lib`. Verified in docs/bringup/BRINGUP-HISTORY.md 2026-10-25 (D9 residue).
- 2026-10-18 (residue cleanup, section 8): heap-only memory map + explicit retail mapping +
  save-state format 2; T0 on the native logic-time clock; ViBuf IPU layer stubbed (census
  tool); runtime VU0 bind only in `model`; link-audit set `vu0`; `RG_NATIVE_ONLY` default ON.
  Verified as in section 8 (route run hash + 37 milestones identical, fixtures 8/8, ctest
  710/710, audit PASS).
