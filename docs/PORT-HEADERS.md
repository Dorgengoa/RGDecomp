# Port headers and the asm/u128 ingest stages

PLAN.md transform 4 (VU0/COP2), transform 6 (assembly-bodied units), the
"128-bit types and MMI" hazard, and the gcc-island varargs. All of it is either
a port-side header or an ingest stage. `game/` stays generated and is never
edited by hand.

## How game code is compiled

```
clang -target i686-pc-windows-msvc <D2 flags> -std=gnu99 (or -std=gnu++17)
      -include port/prelude.h
      -I include            # port replacement headers, AHEAD of
      -I game/include       # the snapshot's headers
```

CMake gives game targets this through the `rg_game_headers` interface library
and links `rg_vu0` (`src/ps2/vu0.c`, which holds the VU0 register file). The
compile set is every MANIFEST row of kind `unit` or `data`. Rows of kind
`excluded` are kept in `game/` for reference but are never compiled.

| File | Role |
| --- | --- |
| `include/port/prelude.h` | Force-included. Pulls in `u128.h` and `vu0.h`. Stays freestanding: no system headers, because game files declare their own `memcpy`/`sqrtf` prototypes. |
| `include/port/u128.h` | `rg_u128` / `rg_s128`. |
| `include/port/vu0.h` | The VU0 macro-mode model: register file `rg_vu0` plus one `rg_vu0_*` call per COP2 instruction. |
| `include/vu0inline.h` | Replaces `game/include/vu0inline.h` (7 helpers, 15 users). |
| `include/libvu0.h` | Replaces the decomp's `include/libvu0.h` (d784320c, 30 macros). Not used in the 2efa6b43 snapshot yet. |
| `src/ps2/vu0.c` | `rg_vu0` state: vf0 = (0,0,0,1). |
| `src/ps2/vu0_micro.c` | `rg_vu0_vcallms(imm)`: VU0 micro mode on the same register file (below). |
| `tools/portxform.py` | The stages. `python tools/portxform.py STAGE[,STAGE] IN OUT` runs them on a single file. |
| `tools/syntaxcheck.py` | `clang -fsyntax-only` over the whole compile set, plus an error-class census. |

## Stages (`tools/ingest.py` → `tools/portxform.py`), in run order

Each stage works on a lexed view with comments and string contents blanked, so
text inside comments is never rewritten. Each stage is idempotent: the CLI
re-applies every stage and fails if a second pass changes anything, and a
second `ingest.py` run writes 0 files.

| Stage | Applies to | 2efa6b43 census |
| --- | --- | --- |
| `int128` | unit, data, **include** (`vec.h`) | 465 files, 509 sites |
| `gccvarargs` | unit, data | 4 files, 62 sites |
| `vu0asm` | unit, data | 36 files, 39 asm statements translated |
| `asmexclude` | unit, data | 1,174 symbols cut; 1,173 files excluded, 1 function cut inside a compiled file |

### `int128`: the u128 substitute

**How the game uses 128-bit types** (582 compiled files):

- 469 per-file typedefs (`typedef unsigned __int128 u128;`, `__int128 s128`, and 13 gcc-style `unsigned int u128 __attribute__((mode(TI)))`).
- 693 struct members and variables.
- 697 `*(u128 *)p` qword moves. These are the lq/sq idiom; `vec.h`'s `Vec4::operator=` and `VEC4_ZERO` use it too.
- 105 `= 0` stores (`sq $0`).
- 28 value casts (`(s128) M2C_FIELD(...)` copies).
- 35 by-value parameters in 8 files and 8 returns in 7 files.
- No 128-bit shift or arithmetic was found in compiled game code.

The packet builders' shifts and ORs live in SDK/MMI asm, which is excluded.
The census's `asm_cop2_q`/`asm_lqsq` rows are asm too.

**Choice: `typedef unsigned _BitInt(128) __attribute__((aligned(16))) rg_u128;`**
(and the signed form), not a struct.

- A struct would break `= 0`, `==`, value casts and every integer operator.
- `_BitInt(128)` on i686 clang 23 keeps all of them. `*`, `/` and `%` are lowered inline, with no `__udivti3` libcall.
- `sizeof` is 16 and the byte layout is little-endian, the same as the EE.
- Its natural alignment on i686 is only 8, so `aligned(16)` is forced. Struct offsets, tail padding and array stride then match the EE (`Pad`/`Tail` asserts).
- By-value parameters and returns work across real calls (`noinline` tests).

The game also has two other spellings:

- `mode(TI)`. Clang accepts it on i686 as a hidden i128 type, but it is rewritten anyway so there is one type.
- `__int128_t`/`__uint128_t`. These are rewritten too.

C++ accepts `_BitInt` as a clang extension; the warning is silenced in the header.

### `gccvarargs`: the gcc 2.9 island varargs

There are 4 files: DbgPrintf, SdRemote*/SoundIopSendCmd*, SoundRpcCall and
SoundSendCmd. Each one hand-walks 8-byte EE varargs slots. The stage rewrites
the idiom as a whole:

| EE idiom | Becomes |
| --- | --- |
| `typedef char *va_list;` | `#include <stdarg.h>` |
| `ap = (char *)__builtin_next_arg(L) - (…args_info…);` (and the `VS()` macro) | `va_start(ap, L)` |
| `ap += 8; … ((T *)ap)[-2] …` and `ap += 8; … *(T *)(ap - 8) …` | `va_arg(ap, T)` |

`va_end` is not added; it is a no-op on i686. A port header can't do this job:
the slot stride itself changes from 8 to 4.

### `vu0asm`: inline VU0 asm becomes calls into the VU0 model (transform 4)

The model keeps one global VU0 register file because the game's COP2 code
passes values from block to block. For example, `vf31 = (1,1,1,1)` is set by
one routine and read by later ones, and every libvu0.h macro is a fragment
around C. An mwcc `asm volatile { }` block, or a GNU `__asm__("…" : ops)`
statement, is translated only when every instruction is one of these:

- `lqc2` / `sqc2` / `lq` / `sq`
- `qmtc2` / `qmfc2` / `cfc2` / `ctc2` / `mfc1` / `mtc1`
- `addiu` / `move` into a temp
- any VU0 macro op: `vadd`/`vsub`/`vmul`/`vmax`/`vmini`/`vmadd`/`vmsub`, their ACC forms and their bc/q/i forms, plus `vopmula`/`vopmsub`, `vabs`/`vmove`/`vmr32`, `vftoiN`/`vitofN`, `vclipw`, `vdiv`/`vsqrt`/`vrsqrt`
- `vwaitq`/`vnop`/`nop`/`sync`, which become nothing

The translation is refused in any of these cases:

- **Any EE GPR is read before the block writes it.** That would read a C argument through the MIPS calling convention.
- **Any hardware FPR (`$fN`) is used.**
- **The block has a label, branch or other directive.**
- **The function is non-void and has no C `return`.** The asm itself supplies v0.

C variables are operands, as in mwcc asm. Every C statement keeps the original
instruction as a comment. A refused block is left alone and `asmexclude` cuts
its function.

Translated sites (39 in 36 files):

- **game (24 sites, 22 files):**
  - `AnimKeyEvalQuat` ×2
  - `FrameCalcLocalMatrix` ×2
  - `DynClothSolveSpring`, `ClothSolveDistance`, `VecSolveDistanceConstraint`
  - `ParticleSwirlReset`, `ParticleEmitterSpawn` (CopyXYZ), `ProjectileDrawModel` (CopyXYZ)
  - `MapAreaModelInit`, `SweptSphereTriContacts`, `CollFrameTreeCollectTris`
  - `MatFromPosScale`, `MatMulPoint`, `MatMulVec4`, `VecCopyAsDir`, `VecWeightedSum3`
  - `FrameCalcWorldMatrix` (Vu0MulMatrix2), `FrameResetXform`, `ModelSet{Pos,Rot,Scale}`
  - the GNU `lerp` in `AnimKeyBlendMaterial_1559e0`, whose template contains raw newlines.
- **sdk band / path (15 sites, 14 files):**
  - `Vec{Add,Sub,Scale,AddInPlace,Length,Normalize}_13xxxx`, `MtxMul{Point,Vec4}`, `MatFromQuatFull`
  - `sceVu0Normalize`, `sceVu0UnitMatrix`
  - `iSetAlarm` (`sync`), and `KernelReleaseAlarm`'s two GNU barriers (an empty `"=r"/"0"` launder and `sync`)

The refused blocks are left as they are; the next stage cuts their functions.

### `asmexclude`: assembly-bodied units (transform 6)

The stage cuts these:

- every `asm T f(…) {…}` function;
- every C function that still contains an asm block or GNU asm after `vu0asm`;
- any C function in a file that has to go whole, because a used static asm helper or asm in a class member forces the whole file out. These rows are `collateral`; there are 0 in this snapshot.

What happens to a cut function:

- **Non-static:** the definition becomes its prototype plus `/* [port] asmexclude … */`.
- **Unused static:** it is dropped.
- **File with no C definition and no data definition left:** the file is marked `excluded` in MANIFEST and its body is kept verbatim.

`game/EXCLUDED.tsv` has one row per cut symbol, with these columns:
`symbol file image reason lib lib_reason scope detail`.

- `reason`: asm-function, asm-block, gnu-asm or collateral.
- `lib`: sdk, library or game. It comes from the path (`sdk/`, `libc`, `lib*`, `gcc`) or from the MAIN address band (crt0/MSL `0x100000–0x108000`, SDK `0x108000–0x140000`, the sdremote island and libkernl), using the same table as `tools/census`.
- `scope`: file or function.
- `detail`: the body class (cop2, cop2+ee, mmi, mmi+ee, ee or nops) and the first refusal reason.

`ingest.py --check` verifies the file through its MANIFEST row (kind `generated`).

**2efa6b43:** 1,174 symbols (sdk 851, library 213, game 110). The 110 game rows break down as:

- 72 asm functions that are COP2 / COP2+EE: the `Vec*`/`Mat*`/`Camera*`/`Frame*` leaves at 0x1cb2b0–0x1cbfb0 and so on.
- 21 C functions with EE/MMI blocks that read argument registers, for example `MotionList*`, `CharaRes*`, the `Movie*`/`Sound*` vblank handlers, `MtxCopy`, `Swap128`, `VecAdd`/`VecSub`.
- 9 EE asm functions.
- 5 `<ovl>_entry` nop pads. These are not functions.
- 3 MMI asm functions (`VecCopy`, `CharaCanGrabLedge`, `CirclePushOutXZ`).

Every one of these gets bound to `src/sce` or to an override; none is stubbed
silently.

## VU0 float semantics

Default: `RG_VU0_IEEE` is not defined.

| Behaviour | What the model does |
| --- | --- |
| Inputs | exp 0 reads as ±0, so there are no denormals. exp 255 is an ordinary number (1.m·2^128), never Inf or NaN. |
| Results | Rounded toward zero to 24 bits. \|r\| ≥ 2^129 clamps to ±0x7FFFFFFF. \|r\| < 2^-126 flushes to ±0. |
| madd/msub | The product is rounded, then the sum (not fused). |
| `vdiv` | x/0 gives ±max, with the sign of x XOR the sign of y. |
| `vsqrt` | Takes \|x\|. `vrsqrt` is fs / sqrt(\|ft\|) and rounds twice. |
| `vftoiN` | Truncates and saturates to int32. |
| `vitofN` | int / 2^N. |
| `vclipw.xyz` | Shifts the 24-bit clip history by 6 and sets +x −x +y −y +z −z. |
| lq/sq/lqc2/sqc2 | The address is NOT masked with `~15` (host objects are where the pointer says). |

**Approximations:**

- The arithmetic is done in double and then truncated. Mul is exact. Add/sub is exact except when the 53-bit rounding of the exact sum carries across the truncation point.
- The real VU adder's missing guard bits (1-ulp differences on large exponent gaps) are not modelled.
- `vrsqrt` rounds twice.
- MAC/status flags are not modelled: cfc2 of vi16/vi17 reads 0. Clip (vi18), R/I/Q/P are modelled.
- GPR temps hold host pointers as 32 bits (`Vu0InversMatrixLoad`). That is fine on i686, but needs revisiting for x64.
- With `-DRG_VU0_IEEE` the model uses plain IEEE single arithmetic: faster, but not faithful.

## Native VU0 modes (2026-10-18)

`RG_VU0_MODE` (CMake: `model` | `local` | `native`) chooses how this model is built
into game code; everything above describes `model`, the bring-up model and oracle.
`local` gives every translation unit its own register file (`port/vu0.h` names the
state at each call site, `rg_vu0s_<op>(&rg_vu0, ...)`; the two cross-file register
protocols share named contexts through `port/vu0_ctx.h`) and replaces `vcallms` by the
microprogram as C (`rg_vu0_srt`, src/sce/vu0/vu0_srt.c); `native` adds IEEE single
arithmetic. Census, design and verification: [NATIVE-CPU.md](NATIVE-CPU.md).

## VU0 micro mode (`vcallms`)

On the PS2 macro mode (COP2 from the EE) and micro mode (a program in VU0
micro memory) are one VU0: vf00-vf31, ACC, vi00-vi15, Q, P, I, R and the clip
flag are the same registers. The port keeps two representations of them,
`rg_vu0` for the inline macro ops and a `vu_state` for the src/ps2/vu
interpreter (docs/VU.md), and makes them the **same state at the boundaries**:

- `rg_vu0_vcallms(imm)` copies vf1-31, ACC, vi1-15, Q, P, I, R and clip from
  `rg_vu0` into the bound interpreter VU0, runs the program at `imm * 8` to
  its E bit (`vu_start` + `vu_run`, then `vu_drain`), and copies the same
  registers back. It returns 0, or -1 when no VU0 is bound or the program
  does not end (registers unchanged / as far as it got, with a message).
- That is exact, not an approximation: the model is synchronous, so no macro
  op runs while the program runs. (On hardware a COP2 macro instruction
  issued while VU0 is busy waits for the program; the game always follows
  `vcallms` with `vnop`.)
- Chosen over making `rg_vu0` alias the interpreter's registers because it
  leaves every inline `rg_vu0_*` op and the game-facing layout untouched: the
  only cost is two 600-byte copies per `vcallms`.
- Not shared: MAC/status flags (the macro model does not keep them) and the EE
  GPR temps (micro mode cannot see them).
- `rg_vu0_micro_bind(vu)` names the interpreter VU0 whose micro memory holds
  the programs. src/runtime binds its VU0, the one VIF0 MPG uploads fill
  (GfxSysInit sends the `D_00445810` VIF0 chain); the bindings tests bind
  their own, loaded from the retail ELF.
- Callers: `MatFromSRTVu0_13bc90` and `MatRotateVu0_13bc20` (overrides,
  `vcallms 0x0` into the scale/Euler/translation program). `ctest -L bindings`
  (`ovr_vcallms`) checks them bit-exact against the program run directly on a
  second interpreter (the tests/vu `vu0_srt` procedure) on 500 random inputs,
  against S·Rx·Ry·Rz + T in double (worst 3.4e-6 relative), and that the
  register file is one state across the call.

### libvu0.h users still need the binding layer

The C around the libvu0.h macros, in later snapshots, binds variables to VU
registers with `#pragma vu0_mmi_reg_binding` and `extern u128 x asm("vfN")`,
and uses mwcc intrinsics (`_vmul`, `_vmaddbc`, `_vopmsub`, …). When such a
snapshot is ingested, those bindings must map onto `rg_vu0.vf[N]` / `rg_vu0.acc`
and the intrinsics onto `rg_vu0_fmac` and the other model calls. That is a
follow-up stage; it does not exist yet.

The 2 `asm("r4")`/`asm("r5")` GPR bindings in
`insect_InsectPieceFaceCell_515590.c` are unused externs. Clang reads them as
asm labels, so they need nothing.

## Tests

`tools/build.ps1` builds the tests and runs them after `rg-smoke`. Both pass.

- **`rg-test-u128`** (`tests/test_u128.c` and `test_u128_cpp.cpp`):
  - static asserts on size, alignment, struct offsets, padding and stride;
  - runtime checks on byte layout, casts and sign extension, shifts across halves, carry, `*` `/` `%`, signed shift/negate, by-value parameters and returns, `= 0`, qword puns, stack alignment;
  - in C++, `Vec4::operator=` from `vec.h`.
- **`rg-test-vu0`** (`tests/test_vu0.c`, `test_libvu0.c`):
  - every float-model rule above;
  - every op family, with masks, Q/I sources and vf0 read-only;
  - each of the 7 `vu0inline.h` helpers and all 30 `libvu0.h` macros, with known vectors (the ACC heads are closed the way the original routines close them);
  - end to end: CMake runs `portxform.py int128,gccvarargs,vu0asm,asmexclude` on `tests/xlat/push_apart.c` (the mwcc block of DynClothSolveSpring_16a480, verbatim, plus an EE-only block that must be cut) and on `tests/xlat/lerp_gnu.c` (the GNU lerp with raw newlines, verbatim from the snapshot), then calls the results.
- **Arming control:** the same test built with `-DRG_VU0_IEEE` fails exactly the 8 VU-semantics checks (round-toward-zero ×2, clamp, exp-255, denormal, flush, x/0 ×2).

## Remaining clang errors

Measured with `python tools/syntaxcheck.py`; results go to
`build/syntax/syntax_classes.tsv` and `syntax_errors.tsv`. The census for the
current snapshot is in the session report. None of the remaining classes
involve u128, asm, VU0 or varargs. They are prototype and dialect issues for
transform 2 (prototype unification) and overrides.
