# Bindings: who provides every excluded symbol

PLAN.md transform 6 cuts every asm-bodied function out of the build
(`asmexclude`, [PORT-HEADERS.md](PORT-HEADERS.md)); `game/EXCLUDED.tsv` lists
the 1,174 symbols. This page says, for each one the game actually needs, what
provides it in the port: a port module, the host C runtime, an override, or
nothing because nothing calls it.

```powershell
python tools\excluded_coverage.py --md   # ~20 s
```

- **Input:** `llvm-nm` over the compiled game objects
  (`build\i686-windows\CMakeFiles\rg_game_*.dir`, or `--objdir`), the
  `jal`/call targets inside the excluded game files (their overrides need the
  same callees), `census/platform_sdk_surface.tsv` for families, and a scan of
  `src/` (C definitions plus `llvm-nm` of built module objects) for providers.
- **Referenced** means reachable from game code: an undefined symbol of a
  non-library game object, or a callee of an excluded game file. Compiled
  *library-band* objects (the 135 MAIN library functions with C bodies) only
  count when game code reaches them, and the walk stops at a library function
  a port module already replaces (its internals are not needed).
- **Output:** `build\bind-i686\excluded_coverage.tsv` (one row per excluded
  symbol: family, reference counts, example callers, provider) and
  `build\bind-i686\abi_conflicts.tsv` (below). `--md` rewrites the table here.

## Coverage

Provider classes: `port:<module>` = a CC0 module under `src/` defines the
symbol; `host-crt` = the unsuffixed libc names the host CRT provides as is;
`override` = a C port of the game file under `overrides/`; `todo:*` =
referenced and still unbound; `drop:*` = not needed (no reference from game
code, only from library code the port replaces, or a nop pad).

<!-- coverage:begin -->
| Provider | sdk | library | game | total |
| --- | ---: | ---: | ---: | ---: |
| `port:src/crt/crt_heap.c` | 0 | 3 | 0 | 3 |
| `port:src/crt/crt_libc.c` | 2 | 17 | 0 | 19 |
| `port:src/crt/crt_math.c` | 22 | 16 | 0 | 38 |
| `port:src/crt/crt_msl.c` | 0 | 12 | 0 | 12 |
| `port:src/crt/crt_mslstr.c` | 0 | 3 | 0 | 3 |
| `port:src/ps2/overlay` | 0 | 1 | 0 | 1 |
| `port:src/runtime/crt0.c` | 2 | 1 | 0 | 3 |
| `port:src/sce/cdvd` | 15 | 0 | 0 | 15 |
| `port:src/sce/graphics` | 36 | 0 | 0 | 36 |
| `port:src/sce/kernel` | 32 | 0 | 0 | 32 |
| `port:src/sce/mpeg` | 7 | 0 | 0 | 7 |
| `port:src/sce/padmc` | 41 | 0 | 0 | 41 |
| `port:src/sce/sif` | 48 | 0 | 0 | 48 |
| `port:src/sce/vu0` | 17 | 0 | 0 | 17 |
| `override` | 92 | 0 | 93 | 185 |
| `host-crt` | 9 | 0 | 0 | 9 |
| `drop:lib-internal` | 9 | 4 | 0 | 13 |
| `drop:not-a-function` | 1 | 1 | 5 | 7 |
| `drop:unreferenced` | 518 | 155 | 12 | 685 |
| **total** | 851 | 213 | 110 | 1174 |

Referenced: **398** of 1174 excluded symbols (game objects + excluded game-file callees).
<!-- coverage:end -->

## What is bound where

### `src/sce/vu0` (libvu0, 17 functions)

`sceVu0{Add,Sub,Scale,ScaleXYZ,Div,Inter,Copy}Vector`, `InnerProduct`,
`OuterProduct`, `{Copy,Mul,Transpose,Invers}Matrix`, `RotMatrix{,X,Y,Z}` —
every libvu0 function the game calls (the rest of libvu0 is unreferenced;
`sceVu0UnitMatrix`/`Normalize` and `MtxMulVec4_10a8c0` = ApplyMatrix compile
from the snapshot through the `vu0asm` stage).

Each is written on the VU0 model (`include/port/vu0.h`): one `rg_vu0_*` call
per retail COP2 instruction, on the same registers. So results carry the VU
rounding (round toward zero, clamp, no denormals; `sceVu0DivVector(v, 3)`
gives 0x3EAAAAAA where IEEE gives ...AB), and the register file is left as
the hardware leaves it. `RotMatrix*` keep Sony's `_sceVu0ecossin` (a
polynomial sin from the S5432 constants at retail 0x00445F60, cos as
`sqrt(1 - sin^2)` with the sign from the angle's quadrant). MMI moves (lq/sq,
the pextlw/pcpyld transposes) are plain copies; EE GPRs are not modelled.

### `src/crt` (C/C++ runtime under game names)

| File | Symbols | Game semantics kept |
| --- | --- | --- |
| `crt_libc.c` | `__assert`, `Abort`, `Exit` (both weak; the runtime owns exit), `Fflush`, `Fprintf`, `Vprintf`, `Sprintf`, `Index`, `Strchr`, `Strstr`, `Strtol`, `Atof`, `Toupper`, `Strupr`, `Strcasecmp`, `Strncasecmp`, `Rand`, `Srand`, `Qsort` | newlib's rand LCG (state 1 at boot); the 4.4BSD qsort (equal keys land where retail puts them; MSVC's qsort orders them differently, checked); newlib's ctype quirks: the casecmp loop folds *signed* chars, so bytes 0x80..0xFF index the 128 `.rodata` bytes before `_ctype_` (their upper/lower bits are kept as two masks) |
| `crt_heap.c` | `Malloc`, `Free`, `Memalign` | retail's newlib malloc (dlmalloc 2.6, read from MallocR/FreeR/MallocExtendTop/MallocTrim/MemalignR; state in retail .data D_00449868/D_00449C70, docs/BRINGUP.md fix 1) over the runtime's game-RAM block and its `sbrk` (crt0's SetupHeap range), so heap addresses equal retail's, so the game's own "how much heap is left" probe and its big `memalign`ed arenas behave as on the PS2, and exhaustion returns NULL. The game's own allocators (MemStack*, the game-data heap) are game code on top and are not replaced |
| `crt_math.c` | libm (`Sinf`…`Floorf`, `Sin`, `Cos`, `Sqrt`, `FabsDouble`, `Finite`, `Isnan`), fp-bit soft double (`dpadd`/`dpsub`/`dpmul`/`dpdiv`/`dptofp`/`fptodp`/`dptoli`/`litodp`, `DoubleCmp`), libgcc (`Divdi3`, `ModDi3`, `UDivDi3`, `UModDi3`), conversions (`DoubleTo{S64,U64,UInt}`, `FloatTo{S64,U64}`, `S64To{Double,Float}`, `UIntToDouble`, `U64ToDouble`) | conversions follow the linked call chains: `__fixunsdfsi` saturates (negative → 0, ≥2^32 → 0xFFFFFFFF), `__floatdisf` sets the sticky bit against double rounding, `U64ToDouble` halves with a sticky bit; s64 `/0` returns 0 instead of trapping. float libm: under the EE MXCSR (`RG_EE_FPU=chop`, the default since 2026-10-24) the retail fdlibm float routines in C (`crt_eelibm.c`, within 1 ulp of retail; bit-exact with the opt-in exact model, `tools/parity/eelibm_check.py`), the host's with `RG_EE_FPU=ieee`; double libm: the host's |
| `crt_msl.c` | `OperatorNew`/`Delete`, `ConstructNewArray` (16-byte cookie {size, n, dtor}), `ConstructArray`, `DestroyArray` (last element first), `DestroyGlobalChain` (pops {next, dtor, obj} nodes from `D_004853D0`), `IosBaseInitCtor`/`WIosBaseInitCtor` (no-op), `OstreamFlush`/`WOstreamFlush`, `OstreamSentryCtor`/`WOstreamSentryCtor` | mwcc ctor/dtor callbacks are `(this, 1)` / `(this, -1)`. The ostream pair is the retail flush/sentry logic on the `basic_ios` layout the asm reads (rdbuf +0x20, flags +0x38, state +0x3A, exceptions +0x3B, tie +0x40; pubsync = streambuf vtable +0x18); the ios_base::failure throw prints its message and aborts (nothing catches it), and a stream whose `basic_ios` pointer is NULL (the never-constructed standard streams `IosBaseInitDtor` flushes) is left alone |
| `crt_mslstr.c` | `StringReserve`, `StringReplace`, `StringReplaceFill` (MSL `basic_string<char>`, used by `StrMapInsertNode_*` key copies) | the 12-byte short/long layout and retail's capacity policy |

`FlushCache` is in `src/sce/kernel` (`eekernel.c`, a no-op with `iFlushCache`).

Unsuffixed libc names (`memcpy`, `memset`, `strcpy`, `strlen`, `strcmp`,
`strcat`, `strncpy`, `strncmp`, `memmove`) bind to the host CRT. No `src/crt`
symbol redefines a host CRT name; `__assert` is newlib's and has no MSVC
twin.

### Interrupt handlers, VU0 micro mode, libmpeg, the dtor chain

| Symbol | Provider | What it does in the port |
| --- | --- | --- |
| `GfxVblankStartHandler_15df20` | override | VBLANK_START handler (via `sceGsSyncVCallback`): busy flag, `D_004810C8 = !CSR.FIELD` through `HW_R64(0x12001000)`, optional callback `D_004810D0(cause)`, counter `D_004810C4` (wraps to 0, never negative), on request `D_004810C0` `iSignalSema(D_0047DF18)`; `sync; ei` = `EIntr()` (only the handler's EIE copy, docs/KERNEL.md) |
| `Vif1IntcHandler_15e170` | override | INTC cause 5 only: if `D_0047DF14 >= 0`, `D_004810B4 = T0_COUNT` (`HW_R32`), `iSignalSema`, `VIF1_FBRST = STC` (`HW_W32`, clears the VIF1 model's interrupt stall); counter `D_004810B0` |
| `SoundVblankIntrHandler_1bd6f0` | override | VBLANK_END: unless busy (`D_00481504`), `iPollSema(D_0047E214)` and `iSignalSema` when it was 0 (a free count is taken back); counter `D_00481508` |
| `MovieDmacHandler_1d4b10`, `MovieVblankHandler_1d4c90` | override | retail body `sync; ei; return 0`; no caller left after the MoviePlayerStart override, kept for later snapshots |
| `MatFromSRTVu0_13bc90`, `MatRotateVu0_13bc20` | override | `vcallms 0x0` is `rg_vu0_vcallms(0)` (`src/ps2/vu0_micro.c`): the retail VU0 microprogram that GfxSysInit uploads runs on the src/ps2/vu interpreter over the SAME register file as the macro model (synced both ways at the call; PORT-HEADERS.md "VU0 micro mode"). src/runtime binds its VU0. With `RG_VU0_MODE` local/native they call `rg_vu0_srt`, the program as native C (NATIVE-CPU.md); the bindings suites build the overrides with `RG_VU0_ORACLE` (the model path) |
| 7 libmpeg entry points (`MpegCreate`, `MpegAddCallback`, `MpegAddStrCallback`, `MpegDemuxPssRing`, `MpegGetPicture`, `MpegReset`, `MpegIsEnd`) | `src/sce/mpeg` | named only by the never-run decoder layer (`VideoDecCreate/SetStream/DecodeBs`, `MovieReadThread`; MOVIE.md); each says once on stderr that it was reached and returns the end/failure value. `MpegStopDmaMaybe` has no caller after the MovieOpen override |
| `RegisterGlobalObject_100dc0` (game C, not excluded) | override | retail stores the chain head by absolute address `*(N **)0x004853D0` (MAIN .bss; the hwaccess stage only rewrites hardware and overlay ranges), spelled `D_004853D0.v = n` |
| `NameTableNodeSetImage_15a640` (no file in the snapshot) | `missing/` | stand-in from the retail listing (0x15A640, 0x5C4 bytes; checked against the decomp's `FUN_0015a640.c`): texture node setup, GS TEX0/TEX1 words. `tools/gamesrcs.py` compiles it until the snapshot defines the symbol, then skips it with a note: **delete it then** (`missing/README.md`) |

### Overrides (`overrides/`)

C ports of asm-bodied game files, each headed with the SHA-256 of the file it
replaces (overrides/README.md; `tools/ingest.py --check` verifies them).
`tools/gamesrcs.py` compiles an override of an `excluded` MANIFEST row in its
place (before this, excluded rows were skipped even with an override).

They cover the Level-5 vector/matrix/GS-packet library that sits in MAIN's
SDK address band 0x13BC20..0x140000 (EXCLUDED.tsv says `lib=sdk` by address;
`excluded_coverage.py` calls these families `l5-math` and `l5-gspkt`) and the
game-scope asm (`Vec*`/`Mat*` leaves at 0x1CB2B0..0x1CBFB0, `Frame*`,
`Model*`, ...). COP2 code is ported on the VU0 model instruction by
instruction, EE code as C. The per-symbol plan is below.

<!-- gamescope:begin -->
| Symbol | Body | Refs | Provider | Plan / note |
| --- | --- | ---: | --- | --- |
| `entry_002d94b0` | ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `AnimApplyMaterialKeys_154200` | cop2+ee | 1 | `override` | returns $v0 0/1; calls AnimResGetMaterialKeyList_14bef0, ArrayGetChecked_153160, AnimKeyEvalMaterial_155af0 (game_protos types) |
| `AnimSlotApplyToMaterial_154540` | cop2+ee | 1 | `override` | caller passes arg1 as s32 (same width on i686) |
| `MotionListSetBlendSpeedById_172170` | ee | 1 | `override` | caller ModelObjSetMotionBlendSpeed_1add60 declares s32 return and returns it; asm never sets $v0 (garbage in retail too) |
| `MotionListSetRateById_172110` | ee | 2 | `override` | CONFLICT: caller_sigs has one caller 's32 (s32, s32, f32, s32)' / 'MotionListSetRateById_172110(m, 0, vol, 3)' (float 3rd) vs ModelObjSetMotionRate_1add50 '(void *, s32, s32, f32)'; same on MIPS ($6 / $f12), different on i686 - override follows the asm order int,int,int,float; the float-3rd caller must be fixed. Also s32 return declared, asm leaves $v0 unset |
| `MotionPlayerGetBlendMaybe_172ce0` | ee | 2 | `override` | adda.s/msub.s -> 1 - d*d with product rounded (plain float) |
| `CameraBaseGetMatrix_15fc60` | cop2 | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `CameraBaseGetPos_142e40` | cop2 | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `CameraBaseSetPos_154520` | cop2 | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `CameraBaseSetRotation_15fc20` | cop2 | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `CharaCanGrabLedge_20fc40` | mmi+ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `CharaResFindFreeSlot_1f0440` | ee | 1 | `override` | caller declares s32 return - same EAX |
| `CharaTableEntryGetWaitFrameParam_2260c0` | ee | 1 | `override` |  |
| `SurfaceParamFindByTriAttr_23a2b0` | ee | 1 | `override` | asm quirk kept: a miss returns the terminator record (key<0), not NULL; caller declares s32 return |
| `DListNodeAdvance_42eb00` | ee | 61 | `override` | callers mix s32/pointer return - same EAX on i686 |
| `MotionListFindSubEntry_172430` | ee | 5 | `override` |  |
| `MotionListIsFinished_171d90` | ee | 9 | `override` |  |
| `GfxVblankStartHandler_15df20` | ee | 1 | `override` | interrupt handler (sync/ei; runtime agent): busy 0x4810D4=1; 0x4810C8 = !(GS CSR 0x12001000 bit 13 FIELD); calls optional callback fn ptr at 0x4810D0; ++vblank counter 0x4810C4 (reset to 0 if it goes negative); if request flag 0x4810C0: iSignalSema(sema id at 0x47DF18), clear flag; busy=0. Returns 0 |
| `MeshMaterialReset_14b230` | cop2+ee | 3 | `override` | sw/sh/sb zeroing + sqc2 vf0 + sq $0 |
| `Vif1IntcHandler_15e170` | ee | 1 | `override` | interrupt handler (sync/ei; runtime agent): INTC handler(cause in $a0); only when cause==5 (VIF1): if sema id at gp-0x725c (0x47DF14) >= 0 -> store TIMER0 COUNT (0x10000000) to 0x4810B4, iSignalSema(sema), write 8 (STC) to VIF1_FBRST 0x10003C10; then ++counter at 0x4810B0 (also when sema<0). Returns 0 |
| `VuMicrocodeData_436d00` | ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `VuMicrocodeData_436d10` | ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `DrawEnvSetZbuf_157520` | ee | 1 | `override` | reads MIPS $8 = 5th arg; $6/$7 unused |
| `InsectRecPostMsgBuildNop_3cf0b0` | ee | 1 | `override` | retail is lw $v1,0x18($a0) only (no observable effect); the caller passes an int id, so the port drops the load (no-op) |
| `MapAreaLoadHandleAt_1dd120` | ee | 9 | `override` | asm: only n==0 returns o (n<0 and n>0 -> NULL) |
| `BoxToCenterExtentsVu0Maybe_14ff40` | cop2+ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `BoxTransformExtentsVu0Maybe_14fed0` | cop2 | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `CirclePushOutXZMaybe_1c82c0` | mmi+ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `TriCalcBounds_1cb540` | cop2 | 2 | `override` | straight-line COP2 leaf |
| `VecScalePoint_1cbc60` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `VecSinCos_1cbfb0` | cop2+ee | 2 | `override` | reads the 3-qword table D_0044B2C0 (extern f32[12]; needs the data layer) |
| `CameraBaseLookAt_15fae0` | cop2+ee | 0 | `drop:unreferenced` | no caller in compiled game code or excluded files |
| `MatDecomposeScaleRotPos_1cad20` | cop2+ee | 4 | `override` | callers void:3/s32:1 -> void; scale = row lengths via vsqrt (.word 0x4A0403BD); calls MatToRotPos_1cade0 |
| `MatIdentity_1cbe40` | cop2 | 9 | `override` | straight-line COP2 leaf |
| `MatMulPointRelMaybe_1cb5d0` | cop2 | 1 | `override` | no caller sig; 4 pointer args from the asm ($5 only supplies +0x30 translation) |
| `MatMulPointXyz_1cb780` | cop2+ee | 3 | `override` | w lane of the vf8 temp comes from .sdata D_0047E2BC (externs D_0047E2B0..BC, gp=0x485170; need the data layer); result uses vf0w |
| `MatMulVec4Args_1cb7f0` | cop2+ee | 6 | `override` | stack qword zero loop + 4 swc1 -> lqc2 vf8 |
| `MatMul_1cb700` | cop2 | 12 | `override` | straight-line COP2 leaf |
| `MatOrthonormalizeY_1cb300` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `MatScaleRows_1cbc20` | cop2 | 2 | `override` | callers declare arg2 f32*/s32: pointer either way |
| `MtxCopy_1cbde0` | mmi+ee | 2 | `override` | one caller declares s32 MtxCopy(s32,s32) and returns it (asm $v0 unset); 64-byte copy via temp (4 lq then 4 sq) |
| `MtxInverseAffine_1cb640` | cop2+ee | 4 | `override` | returns $f0 = det (vf9.x, before the divide); caller conflict void:2 / f32:2 -> f32 (void-declaring callers leave ST0 on the x87 stack) |
| `MtxMulDir_1cb910` | cop2 | 2 | `override` | straight-line COP2 leaf |
| `XformPairInit_19a240` | cop2+ee | 7 | `override` | callers void:5/s32:2 -> void (asm sets no $v0); calls VecSetOnes_13e180/VecSetOnes4_13e170 (SDK-band asm, other lane) |
| `CollTriTransform_16c1a0` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `FadeSnap_186d80` | ee | 1 | `override` | asm quirk kept: with list!=0 the final store is always -1.0f at +0x18; caller declares s16 2nd arg (int class, fine) |
| `FrameGetRot_14a1f0` | cop2+ee | 2 | `override` | beql: null rot -> sq $0 to out; callers (void*\|s32, ptr) |
| `FrameSetRotMode_14a250` | cop2+ee | 1 | `override` | bnel/beqz delay slots; $6 is 1 on every path |
| `FrameSetRot_14a390` | cop2+ee | 13 | `override` | c.eq.s compares -> host float ==; delay-slot stores kept |
| `ModelInit_151d50` | cop2+ee | 7 | `override` | callers void:4/s32:1 -> void; 2 callers call ModelInit_151d50() with NO argument (under-argued on cdecl); calls VecSetOnes_13e180 (other lane) |
| `NodeObjInit_1951b0` | cop2+ee | 3 | `override` | callers void:2/s32:1 -> void ($v0=1 is clobbered by the following jal) |
| `VertsPackQuantized_164bb0` | cop2+ee | 1 | `override` | div.s on host IEEE (x/0 -> Inf, not EE max); vftoi0 via model |
| `MovieDmacHandler_1d4b10` | ee | 0 | `override` | interrupt handler (movie agent): body is just sync; ei; return 0 |
| `MovieVblankHandler_1d4c90` | ee | 0 | `override` | interrupt handler (movie agent): body is just sync; ei; return 0 |
| `MotionListGetPlayerState_1723a0` | ee | 3 | `override` | returns MotionPlayerGetState result or 0; callers declare void |
| `FixCameraRecInit_193860` | cop2+ee | 1 | `override` | callers declare (s32): pointer-width on i686 |
| `EventVoicePendingPop_24e6b0` | ee | 1 | `override` |  |
| `SoundVblankIntrHandler_1bd6f0` | ee | 1 | `override` | interrupt handler (sync/ei; runtime/sound agent): if busy flag 0x481504==0: flag=1; r=iPollSema(sema id at 0x47E214); if r<0 iSignalSema(same sema); flag=0. Always ++counter 0x481508. Returns 0 |
| `FieldHudGetSuggestMember_203c20` | ee | 2 | `override` | reads NORMAL overlay bss 0x5273C2/0x5273B8 via RG_OVL_DATA(s16, normal, D_00527020, ..., 0x3A2 / 0x398) like the hwaccess stage (docs/HWBUS.md) |
| `WorldDataRelated_1fecd0` | ee | 1 | `override` | only the two getter calls are observable; caller declares (s32) arg (ignored) |
| `MesWinAddCharY_274d10` | ee | 1 | `override` |  |
| `Swap128_1cb4f0` | mmi+ee | 1 | `override` | qword swap |
| `TriNormalDot_1cb600` | cop2 | 4 | `override` | straight-line COP2 leaf |
| `TriNormal_1cb970` | cop2 | 5 | `override` | straight-line COP2 leaf |
| `VecAdd3_1cbd60` | cop2 | 5 | `override` | straight-line COP2 leaf |
| `VecAddMaxZero_1cbd40` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `VecAddMinZero_1cbd20` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `VecAddXyzW0_1cbda0` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `VecAddXyzW1_1cbd80` | cop2 | 5 | `override` | straight-line COP2 leaf |
| `VecAdd_1cbdc0` | cop2 | 44 | `override` | C file with asm block reading $4/$5/$6; whole function ported; callers void:38/s32:6 -> void |
| `VecCopyAsPoint_1cbe10` | cop2 | 15 | `override` | asm writes no $v0/$f0 -> void; callers conflict void:11 / s32:4 (two declare one arg (void *)) |
| `VecCopy_1cbe30` | mmi | 98 | `override` | 19 callers declare s32 return (asm leaves $v0 unset); 16-byte memcpy |
| `VecCross_1cb9f0` | cop2 | 7 | `override` | straight-line COP2 leaf |
| `VecDistSqXZ_1cb390` | cop2 | 26 | `override` | straight-line COP2 leaf |
| `VecDistSq_1cb3c0` | cop2 | 21 | `override` | returns $f0 (f32); caller conflict f32:17 / void:1 -> f32 (a void-declaring caller leaves ST0 on the x87 stack) |
| `VecDistXZ_1cb3f0` | cop2 | 6 | `override` | straight-line COP2 leaf |
| `VecDist_1cb420` | cop2 | 7 | `override` | straight-line COP2 leaf |
| `VecDivScalarPoint_1cbbc0` | cop2+ee | 3 | `override` | straight-line COP2 leaf |
| `VecDivScalar_1cbbf0` | cop2+ee | 3 | `override` | straight-line COP2 leaf |
| `VecDot3_1cba90` | cop2 | 23 | `override` | straight-line COP2 leaf |
| `VecDotDiff_1cba40` | cop2 | 11 | `override` | straight-line COP2 leaf |
| `VecDotXZ_1cba70` | cop2 | 5 | `override` | straight-line COP2 leaf |
| `VecLengthSqXZ_1cb450` | cop2 | 14 | `override` | straight-line COP2 leaf |
| `VecLengthSq_1cb470` | cop2 | 23 | `override` | straight-line COP2 leaf |
| `VecLengthXZ_1cb490` | cop2 | 6 | `override` | straight-line COP2 leaf |
| `VecLength_1cb4c0` | cop2 | 7 | `override` | straight-line COP2 leaf |
| `VecLerpDir_1cbaf0` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `VecLerpPoint_1cbac0` | cop2 | 11 | `override` | straight-line COP2 leaf |
| `VecLerp_1cbb20` | cop2 | 7 | `override` | straight-line COP2 leaf |
| `VecLinearCombine_1cb8b0` | cop2+ee | 15 | `override` | straight-line COP2 leaf |
| `VecMax_1cb5b0` | cop2 | 4 | `override` | straight-line COP2 leaf |
| `VecMinMax_1cb570` | cop2 | 11 | `override` | straight-line COP2 leaf |
| `VecMin_1cb590` | cop2 | 4 | `override` | straight-line COP2 leaf |
| `VecNegate_1cb9a0` | cop2 | 3 | `override` | straight-line COP2 leaf |
| `VecNormalizeXZ_1cbb50` | cop2 | 7 | `override` | straight-line COP2 leaf |
| `VecNormalize_1cbb80` | cop2 | 31 | `override` | straight-line COP2 leaf |
| `VecScaleDir_1cbc80` | cop2 | 1 | `override` | no callers; signature from the asm |
| `VecScaleToLength_1cb510` | cop2 | 21 | `override` | straight-line COP2 leaf |
| `VecScale_1cbca0` | cop2 | 31 | `override` | straight-line COP2 leaf |
| `VecSubAsPoint_1cbcc0` | cop2 | 2 | `override` | straight-line COP2 leaf |
| `VecSubCross_1cb9c0` | cop2 | 1 | `override` | straight-line COP2 leaf |
| `VecSubDotXZ_1cba10` | cop2 | 3 | `override` | straight-line COP2 leaf |
| `VecSubXyzW0_1cbce0` | cop2 | 5 | `override` | straight-line COP2 leaf |
| `VecSub_1cbd00` | cop2 | 78 | `override` | C file with asm block reading $4/$5/$6; whole function ported; callers void:73/s32:2 -> void |
| `VecWrapAngle_1cbe90` | cop2+ee | 4 | `override` | callers void:3/s32:1 -> void; reads .sdata qword D_0047E2A0 (gp-0x6ED0; needs the data layer) |
| `factory_entry` | nops | 0 | `drop:not-a-function` | `<overlay>_entry` nop pad, not a function |
| `insect_entry` | nops | 0 | `drop:not-a-function` | `<overlay>_entry` nop pad, not a function |
| `insmenu_entry` | nops | 0 | `drop:not-a-function` | `<overlay>_entry` nop pad, not a function |
| `normal_entry` | nops | 0 | `drop:not-a-function` | `<overlay>_entry` nop pad, not a function |
| `title_entry` | nops | 0 | `drop:not-a-function` | `<overlay>_entry` nop pad, not a function |
<!-- gamescope:end -->

## Still unbound (referenced, no provider yet)

None: `excluded_coverage.py` lists no `todo:*` row. What is left depends on the
data snapshot, not on code:

Things the overrides and `src/crt` reference that live in **data**, not code
(library/`.sdata` words no generated data file defines yet; the data layer
must emit them): `D_004853D0` (MSL global-destructor chain head),
`D_0044B2C0` (VecSinCos polynomial), gp-relative constants `D_0047D1E4..D_0047D7CC`,
`D_0047DE00..D_0047DE40`, `D_0047E2A0..D_0047E2BC`, `D_004817A0..D_004817E8`,
`D_004B32xx..D_004B3364`, `D_00445810` (the VIF0 init chain, which also carries the
VU0 microprogram `vcallms 0x0` runs), `D_00458A50`, the handler words
`D_004810B0..D_004810D4`, `D_0047DF14`, `D_0047DF18`, `D_00481504`, `D_00481508` and
`D_0047E214`.
`NameTableNodeSetImage_15a640` is bound by the `missing/` stand-in until the clean
snapshot (which carries `src/u31/FUN_0015a640.c`) defines it.

Caller-side fixes the overrides need (found while porting; asm decides the
provider's signature): `MatFromQuat_13c440` takes `(dst, quat)` but callers
pass one argument; `MotionListSetRateById_172110` is `(int, int, int, float)`
but one caller declares the float third; `ModelInit_151d50` is called with no
argument by two callers; void-declared callers of float-returning
`VecDistance_13d3d0`, `VecDistSq_1cb3c0`, `MtxInverseAffine_1cb640`,
`PointSegmentClosest_13dcc0` leak an x87 slot per call (also in the ABI table).
All of these are now applied by the protos stage with the override as the
truth (PROTOS.md "Truth", `ctest -L protos` has a regression case for each).

## ABI conflicts (callers disagree with the provider)

On the EE a wrong caller-side declaration still worked: ints and floats live
in different register files, and soft-double values are 64-bit GPRs. Under
i686 cdecl a float/double return comes back in x87 ST0 and an int in EAX
(64-bit: EDX:EAX), and a 64-bit parameter takes two stack slots. A caller
that declares `s64 dpmul(s64, s64)` reads EDX:EAX after a function that
returned in ST0 (and leaves ST0 on the x87 stack). `excluded_coverage.py`
screens every caller declaration of every excluded symbol and writes
`build/bind-i686/abi_conflicts.tsv`. These need the caller-side declaration
fixed (the `protos` stage or a port header), not the provider: the providers
use the semantic types (`double` for the soft-double helpers, as PLAN.md
"soft-double helpers become native double" says).

**Fixed by the protos stage (2026-10-12):** the provider prototypes
(`overrides/`, `missing/`, `src/crt/crt.h`) are now the truth for every
caller of a name with no C definition, so the declarations listed below are
removed (C, game_protos.h) or patched (C++), and the call sites are remapped
(missing argument passed through for `MatFromQuat_13c440` / `ModelInit_151d50`,
the float lane for `MotionListSetRateById_172110`). Soft-double values keep
their bits across a declared `s64`/`s32` (`__builtin_bit_cast`, and `s32`
carriers retyped `double`), x87 returns are never declared `void`, and
`strlen`'s `s64` view is patched in place. docs/PROTOS.md has the rules;
the table below was generated before that change (re-run
`excluded_coverage.py --md` to see what is left).

<!-- abi:begin -->
| Symbol | Provider | Conflict | Caller declarations: return (params) x count |
| --- | --- | --- | --- |
| `Atof_12dee8` | `port:src/crt/crt_libc.c` | return | double (i) x2 e.g. src/main/sound/GameSceneSoundEnvParseMapIndex_1d15c0.c; int64 (i) x1 e.g. src/main/str/TextReaderSkipSpace_15e940.c |
| `Cos_128278` | `port:src/crt/crt_math.c` | return,param-width | int (i) x1 e.g. src/main/camera/CameraSetEyeDistance_160030.cpp; double (d) x1 e.g. src/main/sys/FieldControlBeginMaybe_2f13b0.cpp |
| `DoubleToU64_13ab28` | `port:src/crt/crt_math.c` | return,param-width | int (q) x7 e.g. src/main/chara/EventTriggerSysUpdateMaybe_3e02c0.c; int64 (q) x3 e.g. src/main/chara/CharaSysBattleBegin_3a1350.c; double (q) x1 e.g. src/main/file/GameDataDeserialize_3e5fe0.c; void (q) x1 e.g. src/main/sys/PlayTimeAdvance_3d61a0.c; int64 (i) x1 e.g. src/main/sys/PlayTimeSplit_3d6350.c |
| `DoubleToUInt_13bb78` | `port:src/crt/crt_math.c` | return | int (q) x6 e.g. src/main/chara/UnitBaseStampDeathTime_3b15a0.cpp; int (d) x1 e.g. src/main/chara/CharaSysUpdate_3a0c10.cpp; int64 (q) x1 e.g. src/main/script/ScriptEvalQueryOpMaybe_3daaf0.cpp |
| `FloatToU64_13acb8` | `port:src/crt/crt_math.c` | return | int64 (f) x2 e.g. src/main/script/ScriptEvalQueryOpMaybe_3daaf0.cpp; int (i) x1 e.g. src/main/chara/EventTriggerSysUpdateMaybe_3e02c0.c; int (f) x1 e.g. src/main/event/EventFireIntervalTriggers_3e0220.c |
| `MtxInverseAffine_1cb640` | `override:overrides/src/main/matrix/MtxInverseAffine_1cb640.c` | return | void (ii) x2 e.g. src/main/ai/NavGraphSetXform_310dc0.c; float (ii) x2 e.g. src/main/camera/CameraTargetFollowUpdate_307340.cpp |
| `PointSegmentClosest_13dcc0` | `override:overrides/src/main/math/PointSegmentClosest_13dcc0.c` | return | float (iiii) x1 e.g. src/main/anim/DynColliderEllipsoidPushSegmentMaybe_166ba0.c; void (iiii) x1 e.g. src/main/sound/SoundCalcSegmentVolPan_1b7d30.c |
| `Sin_128880` | `port:src/crt/crt_math.c` | return,param-width | int (i) x2 e.g. src/main/camera/CameraSetEyeDistance_160030.cpp; int64 (q) x1 e.g. src/main/math/AxisAngleBetweenVecs_1d7da0.c |
| `StringReplaceFill_1075d0` | `port:src/crt/crt_mslstr.c` | param-width | void (iqiqi) x1 e.g. src/main/libc/NumPutFixedZeroStrMaybe_1b3c90.c; void (iiiii) x1 e.g. src/main/str/StringAppendFill_106e90.c |
| `Tanf_1290b8` | `port:src/crt/crt_math.c` | return | float (f) x1 e.g. src/main/gfx/ViewSetPerspective_1564a0.c; void (f) x1 e.g. src/main/sys/GameSessionInit_1f5d80.cpp |
| `U64ToDouble_100370` | `port:src/crt/crt_math.c` | return | int64 (i) x3 e.g. src/main/file/SaveHeaderBuild_3e5520.cpp; int (i) x2 e.g. src/main/event/ItemGroupUnlock_3cbac0.c; int (q) x2 e.g. src/main/script/ScriptEvalQueryOpMaybe_3daaf0.cpp; double (q) x1 e.g. src/main/chara/BattleHistoryCalcAverages_3a7bd0.c; double (d) x1 e.g. src/main/file/GameDataDeserialize_3e5fe0.c; int64 (q) x1 e.g. src/main/script/VariantGetDouble_36f6c0.c; int64 (void) x1 e.g. src/main/sys/TicksToSeconds_3d6460.c |
| `UDivDi3_139eb0` | `port:src/crt/crt_math.c` | return,param-width | int64 (qq) x2 e.g. src/main/libc/NumPutFormatU64_1a4970.c; int64 (qi) x1 e.g. src/main/sys/PlayTimeSplit_3d6350.c; int (ii) x1 e.g. src/main/util/Base58EncodeBlock_42f2d0.c |
| `UIntToDouble_100320` | `port:src/crt/crt_math.c` | return | double (i) x4 e.g. src/main/map/MapDataGetColorA_1e7510.c; int64 (i) x1 e.g. src/main/script/VariantGetDouble_36f6c0.c |
| `UModDi3_13a430` | `port:src/crt/crt_math.c` | return,param-width | int64 (qq) x3 e.g. src/main/container/PoolInit_36ae50.c; int64 (ii) x2 e.g. src/main/event/EventFireIntervalTriggers_3e0220.c; int (ii) x1 e.g. src/main/chara/EventTriggerSysUpdateMaybe_3e02c0.c; int64 (qi) x1 e.g. src/main/sys/PlayTimeSplit_3d6350.c |
| `VecDistSq_1cb3c0` | `override:overrides/src/main/vec/VecDistSq_1cb3c0.c` | return | float (ii) x19 e.g. src/main/ai/AiPointClearOfCharasMaybe_2bc920.c; void (ii) x1 e.g. src/main/ai/NavNodeDistSq_3118d0.c |
| `VecDistance_13d3d0` | `override:overrides/src/main/vec/VecDistance_13d3d0.c` | return | float (ii) x44 e.g. src/main/ai/AiCmdGetDistance_2c7480.c; void (i) x1 e.g. src/main/camera/CameraDistToEye_13fd00.c; void (ii) x1 e.g. src/main/camera/CameraDistToEye_15cdc0.c |
| `dpadd` | `port:src/crt/crt_math.c` | return,param-width | double (dd) x2 e.g. src/main/chara/BattleHistoryCalcAverages_3a7bd0.c; int64 (qq) x2 e.g. src/main/menu/MenuObjBattlePairSpawnSparkMaybe_385a30.c; int (ii) x1 e.g. src/main/camera/CameraSetEyeDistance_160030.cpp; int64 (qi) x1 e.g. src/main/sys/PlayTimeAdvance_3d61a0.c |
| `dpdiv` | `port:src/crt/crt_math.c` | return | double (dd) x2 e.g. src/main/chara/BattleHistoryCalcAverages_3a7bd0.c; int64 (qq) x2 e.g. src/main/script/VariantDiv_36c4d0.c; void (qd) x1 e.g. src/main/sys/TicksToSeconds_3d6460.c |
| `dpmul` | `port:src/crt/crt_math.c` | return,param-width | double (dd) x10 e.g. src/main/ai/AiCmdTurnToward_2c87a0.c; int64 (qq) x9 e.g. src/main/ai/AiUpdate_2c05b0.cpp; int (ii) x2 e.g. src/main/camera/CameraSetEyeDistance_160030.cpp; int (qi) x1 e.g. src/main/map/MapCfgFuncPlightData_18abe0.c |
| `dpsub` | `port:src/crt/crt_math.c` | return,param-width | int64 (qq) x3 e.g. src/main/chara/CharaSelectStateFromFlagsMaybe_20e9f0.cpp; int64 (iq) x1 e.g. src/main/script/ScriptEvalQueryOpMaybe_3daaf0.cpp; int (ii) x1 e.g. src/main/sys/PlayTimeSplit_3d6350.c |
| `dptofp` | `port:src/crt/crt_math.c` | param-width | float (q) x7 e.g. src/main/ai/AiUpdate_2c05b0.cpp; float (i) x3 e.g. src/main/camera/CameraSetEyeDistance_160030.cpp; float (d) x3 e.g. src/main/chara/CharaSysUpdate_3a0c10.cpp |
| `dptoli` | `port:src/crt/crt_math.c` | return,param-width | int (q) x5 e.g. src/main/event/WorldOnPartyLocationChanged_3ec050.c; int64 (q) x1 e.g. src/main/script/ScriptEvalQueryOpMaybe_3daaf0.cpp; int (i) x1 e.g. src/main/sys/PlayTimeSplit_3d6350.c |
| `fptodp` | `port:src/crt/crt_math.c` | return | int64 (f) x12 e.g. src/main/ai/AiCmdStepTowardMaybe_2c9210.c; double (f) x4 e.g. src/main/chara/BattleHistoryCalcAverages_3a7bd0.c; int (f) x2 e.g. src/main/camera/CameraSetEyeDistance_160030.cpp; int (iif) x1 e.g. src/main/sound/SoundStreamSlotSetFillThreshold_1bd450.c; int (void) x1 e.g. src/main/sys/PlayTimeAdvance_3d61a0.c |
| `litodp` | `port:src/crt/crt_math.c` | return | int64 (i) x4 e.g. src/main/chara/CharaSysEncounterDistRoll_3a59d0.c; double (i) x1 e.g. src/main/chara/BattleHistoryCalcAverages_3a7bd0.c; int (i) x1 e.g. src/main/sys/PlayTimeSplit_3d6350.c |
| `strlen` | `host-crt` | return | int (i) x150 e.g. src/main/ai/AiCmdStrIntern_2c1ac0.c; int64 (i) x1 e.g. src/main/util/Md5Digest_369090.c |

Param classes: i = 32-bit int/pointer, f = float, d = double, q = 64-bit int.
<!-- abi:end -->

## Tests

`ctest -L bindings` (`tests/bindings`):

- `bindings`: `sce_vu0` (hand-computed vectors/matrices, the VU truncation
  case, register side effects, rotations against libm), `crt` (rand sequence,
  qsort order of equal keys, ctype quirks, conversion rounding/saturation,
  MSL cookies and destructor order, MSL string layout and growth, heap
  coalescing/alignment/exhaustion), and one suite per override lane listed in
  `tests/bindings/lanes.cmake` (the overrides compiled with the game flags,
  run against hand-computed results).
  Two lanes go beyond hand-computed leaves:
  - `ovr_platform` (`ovr_platform.c` + `platform_host.c`): the five handler
    overrides run as real handlers under the kernel HLE, with HW_* through the
    hwbus over GS/DMAC/VIF1 models: VBLANK_START/END and INTC VIF1 delivery,
    semaphore signals (and the cases that must not signal), counters and their
    wrap, CSR.FIELD, T0_COUNT capture, VIF1_FBRST STC reaching the VIF, cause
    filtering, chain continuation, no kernel context violation;
    `RegisterGlobalObject` against `DestroyGlobalChain`; the `missing/`
    `NameTableNodeSetImage` against hand-computed TEX0/TEX1/size; the MSL
    ostream flush/sentry on a hand-built `basic_ios`.
  - `ovr_vcallms`: `MatFromSRTVu0`/`MatRotateVu0` with the retail microprogram
    (read from the retail ELF; the suite skips, exit 77 when run alone,
    without it): bit-exact against the tests/vu `vu0_srt` procedure on 500
    random inputs, against S·Rx·Ry·Rz + T in double (worst 3.4e-6), the
    register file one state across the call, unbound `vcallms` = -1.
- `bindings.control*`: the same tests built with `-DRG_BT_WRONG`, which flips
  one expectation per suite; each must FAIL (the deliberate-fault control).
