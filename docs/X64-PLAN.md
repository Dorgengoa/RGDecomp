# x64 readiness census and migration plan (P7)

**Status 2026-10-26: the x64 exe runs the full golden power-on route (32,000 fields, card saved) with the run hash and the audio command log EQUAL to i686 at every field (section 0.7).  2026-10-25 (night): the x64 crash was address-space exhaustion (fixed, section 0.6).  2026-10-25 (evening): strategy A COMMITTED by the user and under way; see section
0 for the step-by-step progress.**  The census below (sections 1-7) is the plan as written
in the morning; section 0 records what was built and how each gate came out.

## 0. Progress (strategy A, lane started 2026-10-25)

The i686 build stays the default and unchanged: no x64 stage runs for i686, and every edit
to a port source is either x64-only (`#if defined(_WIN64)` / `__x86_64__`, CMake
`RG_ARCH STREQUAL "x64"`) or proven object-identical (`tools/x64/i686_same.py`).

**Design change from section 6: the x64 stages DERIVE a second tree instead of re-ingesting
game/.**  `tools/x64/derive.py` reads game/ (after every ingest stage), overrides/ and
missing/ and writes the x64 source tree (default `build/x64-src/{game,overrides,missing}`,
~15-30 s incremental on a quiet disk, 4-15 min cold).  The i686 game/ never changes, the 244 override hashes
stay valid, other lanes' re-ingests need no coordination, and the overrides get the same
rewrite as the generated files.  `Ptr32Stage` keeps the ingest Stage interface
(prepare/apply/extra_outputs/report), so it can also run as the last ingest stage.
Re-run derive after a re-ingest or an override edit, then rebuild the x64 dir.

| Step | State | Gate result |
| --- | --- | --- |
| 1 plumbing | DONE | x64 configure OK; ctest -L x64 5/5 (link gate + 2 controls, runtime self-check, fiber arena); i686 configure: compile_commands.json byte-identical |
| 2 ptr32 stage | DONE (first cut) | x64 compile of every TU: 0 errors; layout gate 0 game records differ (74,590 compared) |
| 3 datareloc ADDR32 | DONE | 1,127 data objects as asm; overlay module table as asm (`gen_overlay_registry.py --arch x64`); x64 link: see below |
| 4 ABI pieces | fiber, trampoline, vthunks, ss_heap, ss_map, crash handler, EE-kernel name clashes, SDK structs in game memory DONE; samplers / `_`-prefix tools open | x64.fiber_arena passes |
| 5 libc / bit-cast / asserts | libc + operator new DONE (derive `libc`); crt size parameters masked | compiles |
| 6 bring-up | power-on route DONE (0.7); gate set in progress (0.7 "Gates") | golden route: run hash **equal to i686 at every field 1-32,000** (final 20a59d8fc0743062), audio command log byte-identical; 8 x64 bug classes fixed on the way (0.7) |

### 0.1 Tools (all under tools/x64 unless noted; run from the port root)

| Tool | What |
| --- | --- |
| `derive.py [--out build/x64-src] [-j N]` | the x64 source tree: stages `ptr32`, `addr32`, `dalign`, `vthunk`, `libc`, `vcmwiden`, `xalign`, `narrowabi` (below and 0.7); writes `<out>/game/PTR32.tsv` (one row per rewrite) and `<out>/DERIVE.txt` (counts, problems) |
| `tools/stages/ptr32.py` | the ptr32 stage (`python tools/stages/ptr32.py FILE --inc game/include` prints one rewritten file) |
| `addr32.py` | datareloc x64 mode: data-layer objects holding pointer words -> top-level asm, same section / alignment / size, ADDR32 relocations |
| `pecheck.py EXE..` | the link gate: LAA off, no DYNAMICBASE / HIGHENTROPYVA, image below 2 GB |
| `linkgate.py` | the x64 build's linker launcher (`CMAKE_<LANG>_LINKER_LAUNCHER`): links, runs pecheck, FAILS the link and deletes the exe if the flags are missing |
| `xprobe.py --db <i686 build> --out DIR [--layout]` | CMake-free compile of the derived tree TU by TU (x64, full codegen, the x64 game flags) with error classes; `--layout` = the layout gate (i686 compile of the original vs x64 compile of the derived file, record sizes and offsets) |
| `i686_same.py --db <i686 build> --orig <pre-edit tree> FILE..` | proves edited port sources compile to the same i686 objects (same path, COFF timestamp masked); `--x64` also compiles them for x64 |
| `winabi_census.py` | Win64 argument-position census (R4), section 0.4 |
| `vmmap.py`, `hashdiff.py`, `dataparity.py` | address-space census of a running exe; RG_HASH_LOG comparison; initial data-image parity i686 vs x64 (section 0.6) |
| `pairrun.sh OUT FIELDS I686_EXE X64_EXE` | the parity run (section 0.7): both exes on the golden route in parallel with RG_HASH_LOG + RG_AUDIO_CMDLOG, then hashdiff and the audio command-log comparison (`OUT/pair.txt`) |
| `ssdiff.py A.rgstate A.map B.rgstate B.map` | whole-state diff of two exes' save states at the same field: the game heap word by word and the statics aligned by symbol, host pointers normalised (heap -> R+offset, image -> symbol+offset); `sspeek.py` prints words side by side, `heapwalk.py` compares the malloc chunk chains |
| `dumpdiff.py`, `heapdiff.py` | RG_STATUS_DUMP / RG_BREAK_SPEC line diffs of two logs |
| `rva2sym.py MAP RVA..` | names BRK / BRKSTACK / crash RVAs through an i686 or x64 map |
| `datalayout.py MAP [MAP2]` | data-layer layout gate: host - retail address constant along every run (ctest `x64.datalayout`) |
| `narrowabi.py [--root build/x64-src] [--check]` | narrow-integer call census (1/2-byte argument / return widths, caller declaration vs definition) and the derive pass `narrowabi` (ctest `x64.narrowabi`) |
| `x87census.py EXE` | where an i686 exe computes on the x87 unit or calls the CRT (rounding not under the guest MXCSR): x87 ops per object, CRT callees per object |
| `libmcheck.c` | the host CRT double libm under the guest MXCSR vs round to nearest, per arch (build it for i686 and x64) |
| `gates.sh BUILD OUT [steps]` | the gate set on one build dir (regen verify boot map cam link addr render ctest; restores the shared save2 card after regen) |
| `vcninja.ps1 DIR x86/x64 [targets]`, `buildretry.sh DIR ARCH LOG` | vcvars + ninja in an existing build dir; retry loop for builds racing other lanes' edits (`BUILD_TARGETS="rg-game"`) |

The x64 build: `tools/build.ps1 -Arch x64 [-X64Src build/x64-src]` (vcvarsall x64,
`cmake/toolchain-x64-windows-clang.cmake`, default dir `build/x64-windows`), or configure
with `-DRG_X64_SRC=<derived tree>`.  CMake: `RG_ARCH` comes from the toolchain's pointer
size; `cmake/x64.cmake` holds every x64-only piece (linker launcher, derived tree, game
flags, start-up self-check in every executable, tests/x64).

### 0.2 Step 1 (plumbing): gates

- `x64.lowmem_link`: pecheck on rg-smoke and rg-x64-lowmem. `x64.lowmem_link_control`:
  rg-x64-lowmem-ctl is linked `/LARGEADDRESSAWARE /DYNAMICBASE /HIGHENTROPYVA
  /BASE:0x140000000` without the launcher; pecheck must report `LARGE_ADDRESS_AWARE is set`.
  `x64.linkgate_control`: linkgate.py around a fresh bad link must fail for that reason
  (PASS_REGULAR_EXPRESSION, so a compile error cannot pass the control).
- `x64.lowmem_runtime`: 1 GB of malloc, VirtualAlloc bottom-up and top-down, a thread
  stack, a fiber stack, the image: all below 2 GB.  `src/x64/lowmem_check.c` (a
  constructor in every x64 executable) exits 86 before main if the image, stack, heap or a
  top-down VirtualAlloc is above 2 GB.
- i686: a fresh configure before and after the edits gives a byte-identical
  compile_commands.json; build.ninja differs only in CMake's own re-run dependency list.

### 0.3 Step 2 (ptr32): rules and results

Rules (spelling `T * RG_P32`, `RG_P32` = `__ptr32 __uptr` from `include/port/x64.h`,
force-included ahead of prelude.h in x64 game objects only):

| Rule | Sites | What |
| --- | --- | --- |
| member | 7,865 (153 function pointers) | record member declarators, incl. inline anonymous records, pointer-to-array `T (*p)[N]`, members after an inline method body, members whose type is a pointer typedef (`PX p;` -> `PX RG_P32 p;`) |
| global / extern | 2,953 (+5 with an inline record body) | file-scope (column 0) and block-scope `extern` pointer declarations, not `static`, no non-null initializer |
| ptrptr | 2,785 | `(T **)` casts -> `(T * RG_P32 *)` |
| dptr | 830 (+ pointer typedefs with a star) | every other `T **` / `T ***` (locals, parameters, returns, prototypes, macro bodies): a pointer to a pointer in game code points at a game-memory slot |
| localarr | 63 | local arrays of pointers `T *list[4]` (retail stack slots are 4 bytes; walked with `T **`) |
| addrlocal | 172 | a pointer local whose address is taken (`f(&self)`) |
| sizeof | few | `sizeof(T *)` |
| fncall | 91 | a call through a `RG_P32` function pointer member / global is wrapped `RG_FPC(p->cb)(..)` (macro bodies too); RG_FPC casts to the ordinary pointer type with `__typeof_unqual__` (plain `__typeof__` keeps the address space) |

Gates (xprobe over all 25,447 TUs of build/soak2-i686's compile db):
- **compile: 0 TUs fail** (first pass 1,129 in the census probe; 74 after the first
  stage cut; the address-space errors drove the dptr / localarr / addrlocal rules).
- **layout: 74,590 records compared, 0 game records differ** (15 rows are
  `rg_thread_conv`, the port's own host struct in include/port/native_threads.h, which is
  never in game memory).  Census probe before the stage: 5,911 instances in 3,880 TUs.

LLVM `__ptr32` gaps found (R1), each made LOUD by an x64 game flag (cmake/x64.cmake):

| Gap | Symptom | Flag / handling |
| --- | --- | --- |
| call through a `__ptr32` function pointer | tail call: silent 8-byte load; else isel crash | stage `fncall` + `-fno-optimize-sibling-calls` (every missed site is then an isel error) |
| switch-to-lookup-table of function addresses into a `__ptr32` slot | "unsupported expression in static initializer: addrspacecast" | `-fno-jump-tables` |
| loop / SLP vectors of `__ptr32` | "Do not know how to widen/split this operator's operand" | `-fno-vectorize -fno-slp-vectorize` |
| `__ptr32` static initializer with an address | error | data layer as asm (step 3); stage skips initialised globals |

### 0.4 R4: Win64 argument positions (census)

`tools/x64/winabi_census.py` (reads protos_irabi.py's cached i686 IR summaries,
out/protos2/ir/sum, plus game_protos.h and the data tables):
- direct calls: 80,183 compared; **1 class mismatch** (VecSolveDistanceConstraint_364740
  from EvMapObjPartStep_363ba0, position 2: view passes an aggregate by address, the
  definition reads a float) and **8 width mismatches** (FontDrawGaiji_26dd50 x3,
  NameTableNodeSetImage_15a640, StringReplaceRange_1b3da0, TextReaderPushValue_15f640,
  TextStyleSet{Grad,}RgbaQuad_26f{1b0,250}: i64 vs 32-bit at one position).  These are
  the irabi BUG-kind rows (benign on i686, reviewed for i686 in docs/PROTOS.md); each
  needs an x64 verdict before bring-up.  Output build/x64-probe/winabi_direct.tsv.
- vtable families (tables sharing >= 2 (slot, function) pairs): 0 slot pairs disagree on
  a position's class.
- devirt slot calls with a float in the view or at the slot: 765 checked; 0 with no
  agreeing function at that table offset, 688 where only some do (the offset alone does
  not identify the family: a class -> vtable map is needed to turn these into verdicts).
- libc redeclarations with a 32-bit size: rewritten by derive `libc` (558 declarations:
  the size parameter becomes `__SIZE_TYPE__`, so every call widens; `operator new(u32)`
  likewise).

### 0.5 Step 4-6: port pieces and bring-up (2026-10-25 evening)

Port-side edits (each x64-only or proven i686 object-identical with `i686_same.py`
against the pre-x64 backup, COFF timestamp masked; 49 compiles checked, 0 differ):

| File | x64 change |
| --- | --- |
| `src/native/threads/fiber/fiber_arena.c` | Win64 switch (rbx rbp rdi rsi r12-r15, xmm6-15, MXCSR, x87 CW, TEB gs:8/0x10/0x1478) and first-switch frame; `fa_start` trampoline |
| `src/native/ovl/ovl_gen.h` | Win64 import trampoline (rcx rdx r8 r9 xmm0-3 kept, shadow space, rip-relative table) |
| `src/savestate/ss_heap.c`, `ss_map.c` | ss_heap enabled on x64; map policy names without the i686 `_` |
| `src/game/rg_game_main.c` | crash report / RG_BREAK / RG_WATCH on the x64 CONTEXT |
| `src/crt/crt_heap.c` | newlib chunk links `CRT_P32` (the retail heap lives in game memory) |
| `src/crt/crt_{heap,libc,msl}.c` | `RG_GSIZE`: size parameters of game-called functions read as 32 bits (a 5th+ argument is a 4-byte stack write by the 32-bit caller: `ConstructNewArray_100710` crashed) |
| `src/sce/kernel/eekernel.h`, `include/port/x64.h` | EE `CreateThread` / `ExitThread` / `TerminateThread` / `SuspendThread` / `ResumeThread` renamed `rg_ee_*` (kernel32's undecorated exports collide on x64); `ThreadParam` pointers `SCE_P32` |
| `src/sce/sif/libsif.h`, `sif_ee.c`, `src/sce/graphics/libdma.h`, `libpkt.h` | SIF RPC / DMA env / GIF packet structs (game memory) with `SCE_P32` pointers; the one call through `sd->func` cast |
| `tools/gen_overlay_registry.py`, `src/ps2/overlay/CMakeLists.txt` | `--arch x64`: the native module table's data images as asm `.long` words (i686 output byte-identical, checked) |
| `cmake/x64.cmake` | the LOUD flags also on src/sce/* and src/crt libraries |

Derive passes added during bring-up: `vcmwiden` (devirt slot-call views pass every
integer argument as 64 bits, sign/zero-extended: WorldSubsysLinkTree_419e60 read a
garbage s16 id through a `(void *, s16)` view of an s32 slot function); ptr32 rules for
one-line declarations after `;`, `typedef struct {..} Name` names, `(T *volatile *)` casts,
`__attribute__` after a declarator, pointer typedefs with a star (`Native *natives`: the
script VM's native table), `extern struct {..} *g;`.

Bring-up runs (`tools/x64/xrun.py EXE --ref <i686 exe> --fields N`: golden input,
headless, RG_GPU=hw, run hash compared; i686 reference = build/x64i-i686/rg-game.exe of
the same tree, configured with `-DRG_GPU_VULKAN=OFF` because the Vulkan lane's
nr_vulkan.cpp did not compile at that moment):

| Field | x64 | i686 |
| --- | --- | --- |
| 600 | 23097594b4346206 | 23097594b4346206 |
| 3,000 | fead30e28c5f5a6a | fead30e28c5f5a6a |
| 8,000 | 3a920c453318b851 | 3a920c453318b851 |
| 16,000 | c7c9852bac47b0e8 | c7c9852bac47b0e8 |
| 18,000 | 0b59bcf1328d4d08 | 0b59bcf1328d4d08 |
| 20,000 | 04b328cd4e7ea1cc | 04b328cd4e7ea1cc |
| 22,000 | 3cbe965f017b5737 | 3cbe965f017b5737 |
| 22,500 | **ebfdbac6b043b836** | 628ce6b77471b59a |
| 23,000 | crash | f00d3b802535d2ff |
| 23,500 | crash | aea27d683ca86083 |
| 24,000 | 1234530ae0b2d87e (no crash) | dbb610ea08065605 |
| 32,000 | crash | 20a59d8fc0743062 |

**Open (next):** the x64 route DIVERGES between fields 22,000 and 22,500 (the run up to the
first battle, 23,000), and from there the x64 runs are not deterministic: runs to 23,000,
23,500 and 32,000 fault in the native renderer's mesh decoder (`exec` in
src/native/render/nr_mesh.c, `dec->m` NULL, via nr_model_record -> nr_mesh_get ->
nr_mesh_decode), the run to 24,000 does not.  A run that differs between runs points at
undefined bits (an argument or slot read wider than it was written, R4) or uninitialised
host memory.  Next: the state trace (RG_TRACE_OUT, tools/trace/port_trace.py compare) of
both exes over 22,000-22,500 to find the first differing game field; then the remaining
milestones, the x64 fixture set (regen / verify), bootcheck, mapcheck, render_gate,
link_audit on the x64 map, the samplers and `_`-prefix tools (2.5), R4 verdicts for the 9
direct rows.  Repro: `python tools/x64/xrun.py build/x64-windows/rg-game.exe --ref
build/x64i-i686/rg-game.exe --fields 22500`.

### 0.6 Bring-up 2 (2026-10-25 night): the "divergence" was address-space exhaustion

**Root cause 1 (the crashes and the early divergence): the 2 GB address space was full.**
`tools/x64/vmmap.py` (new) on a running x64 rg-game: the NVIDIA 64-bit D3D11 driver reserves
a **1 GB contiguous range** (its GPU-VA mirror, under 1 MB committed) and commits about 256 MB
more, all below 2 GB (an x64 LAA:NO process gets its NULL-hint allocations below 2 GB; a
minimal x64 D3D11 program, ../x64-scratch/d3dvm, shows the same: 675 MB left after
device creation).  The i686 32-bit driver reserves 128 MB.  So the x64 port had about 650 MB:
`calloc` in nr_mesh_decode returned NULL (the `dec->m` NULL crash; field 12,711 in one run),
and allocation failures made behaviour depend on run length and layout (the hash log
diverged at field 15,426 in a 22,500-field run, not in a 16,000-field run).  Explicit
allocations above 4 GB DO work in a LAA:NO process, and the driver falls back above 4 GB when
no 1 GB hole exists below 2 GB.
**Fix (generic): the address-space fence** `rg_x64_va_fence()` in src/x64/lowmem_check.c:
one 64 KB reservation every 512 MB below 2 GB, placed before the graphics backend is created
and kept for the life of the process (the driver reserves lazily after device creation; a
fence released after creation was tried and did not hold), so no free hole below 2 GB
reaches 512 MB.  Called through `RG_X64_VA_FENCE(on)` (src/gpu/gpu_internal.h; no-op on i686)
around backend creation in src/native/render/nr_dev.cpp (covers the Vulkan and D3D11
backends) and src/gpu/gpu_core.cpp.  `RG_X64_VA_FENCE=0` = control, `RG_X64_VA_LOG=1` prints
the free space (1,927 MB free before the device, 1,574 MB after, largest hole 511 MB).
No driver address is stored in game memory, so the range above 4 GB is harmless.
Result: runs to 26,000 and 32,000 fields without a crash; two x64 runs to 26,000 have
identical hash logs (repeatable); hash log equal to i686 at every field 1-24,823.

**Root cause 2 (trace tool, not the game): the x64 trace read stored host pointers as
"ptr:?".**  src/trace/trace_regions.c refused to translate 32-bit pointer words when
`sizeof(void *) > 4` (sym:RandState differed from vbl 2).  Under strategy A host pointers
fit 32 bits: `RG_TRACE_HOSTPTR32` (1 on _WIN64).  After the fix, `routecmp.py pair` i686 vs
x64 to field 24,900, every 2nd vbl: **sym: trace IDENTICAL on all 12,433 frames** (class
"presentation": the run hash differs only through audio).

**Open: the audio part of the hash differs from field 24,824** (kernel trace from 25,040).
RG_AUDIO_CMDLOG of the two exes differs at line 18,902: x64 sends sound-thread command
`1E 7 1 0 3C 40` once where i686 does not, and lacks a later `1D` (a 1D/1E pair every 2
fields there): the EE side's sound-request timing differs while the traced game state is
equal.  **Next step:** find the EE code that issues commands 0x1D / 0x1E and trace its
inputs over fields 24,700-24,900 (add its state to a regions file, or RG_BREAK on it); also
possible: an x64 host-side difference in the native audio engine / IOP sound command
decoding (look for pointer-sized or `long` fields in structs read from game or IOP memory
under src/native/audio and src/ps2/iop/sound).  RG_SND_LOG produced no file in these runs.
Repro: `RG_HASH_LOG=x.tsv` runs of both exes to 25,000 (golden input), then
`python tools/x64/hashdiff.py ref.tsv x64.tsv`.

**R4 verdicts (the 9 direct rows): all benign on x64** (checked in the x64 objects /
sources).  VecSolveDistanceConstraint_364740 (class row): the call passes floats in
xmm2/xmm3 to a `(void *, void *, f32, f32)` definition (the census IR summary is stale).
Width rows: FontDrawGaiji_26dd50 x3: every caller passes a 64-bit
`__builtin_bit_cast(long long, ..)`; NameTableNodeSetImage_15a640 pos 9: callers pass
`(int)`, definition s32; StringReplaceRange_1b3da0: the definition reads narrower than the
view (the override passes s32); TextReaderPushValue_15f640: the 8-byte Value / Val struct
(type + 4-byte union under ptr32) is passed packed in rdx, the definition reads s64;
TextStyleSet{Grad,}RgbaQuad_26f{1b0,250}: the definition reads only bytes 0-3 of the u64.
The 688 undecided devirt sites are untouched.

New tools: `tools/x64/vmmap.py PID | --exe-like TEXT [--when-commit MB]` (address-space
census by allocation, type and module); `tools/x64/hashdiff.py A.tsv B.tsv` (two
RG_HASH_LOG files: first differing field per part, equal / differing spans);
`tools/x64/dataparity.py I686_EXE X64_EXE` (initial data-layer image parity, pointer words
compared by symbol + offset through the maps: 9,864 objects, 16,681 pointer words equal by
symbol, **0 differences**).

i686: edited nr_dev.cpp, gpu_core.cpp, gpu_internal.h, trace_regions.c: `i686_same.py`
(build/x64i-i686 compile db) 10 compiles, 0 differ; lowmem_check.c is x64-only; i686
rg-game rebuilds clean.  **Not run in this session:** the full i686 gate set (regen --check /
verify, bootcheck, mapcheck, ctest, render_gate, link_audit, addr_census) and the x64 gates
(task 3: x64 fixture set, bootcheck, mapcheck, render_gate, link_audit/addr_census on the
x64 map); the samplers and `_`-prefix tools (task 4).  Known x64 gate issue: src/host/smoke.c
requires `sizeof(void *) == 4`, so rg-smoke fails on x64 by design and needs an x64 form.

### 0.7 Bring-up 3 (2026-10-26): full power-on route equal to i686

**Result: the x64 exe runs the whole golden power-on route (title, FMV, field, first battle,
town, save point, transporter, card saved; 32,000 fields) with the run hash equal to i686 at
EVERY field (1-32,000, final 20a59d8fc0743062 on both) and the RG_AUDIO_CMDLOG byte-identical
(timestamps included).**  The card it saves differs from the i686 one only in host pointer words
(heap and vtable addresses that retail's save also stores raw, and the checksum over them).
Repro: `sh tools/x64/pairrun.sh OUT 32000 <i686 rg-game.exe> <x64 rg-game.exe>`.

The "audio difference at 24,824" was the first VISIBLE symptom of several x64 bugs; the run
hash covers pad / audio / display / kernel trace only, so game state had parted earlier
without showing.  Found by comparing whole save states of the two exes at the same field
(`ssdiff.py`, below; `--save-state` puts the game heap at the same host address 0x0A000000 in
both) and bisecting, then RG_WATCH / RG_BREAK on the first differing word.  Causes and fixes
(all x64-only; every port-source edit proven i686 object-identical with `i686_same.py`):

| # | Cause | Symptom | Fix |
| --- | --- | --- | --- |
| 1 | float sqrt rounding: under the guest MXCSR (round toward zero) x64 clang inlines `sqrtss` (chop); the i686 build calls the CRT's `sqrtf` (libcpmt xfprec: x87 fsqrt, round to NEAREST, no DAZ) from 49 game objects and the VU0 model's `rg_vu_sqrtf` | emitter-sound pan 1 ulp apart -> extra 0x1E pan commands (field ~22,000) | `include/port/sqrtf_rn.h` `rg_sqrtf_rn` (round-to-nearest in any MXCSR mode, denormals as x87: double sqrt + integer rounding); `include/port/x64.h` maps `sqrtf` / `__builtin_sqrtf` to it (game objects), cmake/x64.cmake force-includes x64.h into the VU0 libraries; ctest `x64.sqrtf_rn` (every 7th float bit pattern vs nearest) + control |
| 2 | the x64 UCRT's double `sin` / `cos` / `tan` are WRONG under round-toward-zero (errors up to 2^32 ulp; i686 UCRT within 3 ulp) | FOV / camera-shake values (render only on the route) | src/crt/crt_math.c `HOST_RN`: the host double libm runs with MXCSR rounding to nearest on x64 (still not bit-equal to i686's UCRT: a different libm, 1 ulp apart in a few % of inputs; `tools/x64/libmcheck.c`) |
| 3 | DATA LAYOUT: x86-64 clang 16-aligns every global array of 16 bytes or more; the data layer (one `.data$rgXXXXXXXX` object per retail address, laid out back to back) moved at 340 places | the font width table (D_0044E851 + 4 * code read across 0044E852 / 0044E854) gave every glyph the default width (text boxes twice as wide), and every other cross-object table read | derive pass `dalign`: every data-layer array without an explicit alignment gets `aligned(__alignof__(T))` (1,521 objects); gate `tools/x64/datalayout.py` (host - retail address constant along each run; 0 breaks only in x64) + ctest `x64.datalayout` |
| 4 | NARROW INTEGERS: i686 clang extends every 1/2-byte argument and return to 32 bits (signext / zeroext), Win64 clang does not; a caller whose declaration disagrees with the definition reads/passes garbage upper bits | CharaEffEntrySpawn_22fad0 declares `GetObjNodeByName_1ce3a0(u8 *, s16, char *)`, the definition reads an s32 id: the first battle's hit effects were placed at the origin -> no hit at vbl 24,790 -> projectile, sequencer and audio differences from field 24,824 | derive pass `narrowabi` (`tools/x64/narrowabi.py`): caller declarations rewritten to the definition's widths (4,845 declaration positions: narrow arguments widened to s32 / u32, returns narrowed to the definition's type so the caller extends as the i686 callee did, and 32-bit integer views of POINTER parameters passed as 64-bit integers: Win64 stores only the low 4 bytes of an int stack argument, ModelMeshUpdateBoundsMaybe_150170 -> ModelCalcNodesBoundsMaybe_1531c0 arg 4); declarations in the defining TU and C++-linkage ones untouched; ctest `x64.narrowabi` (0 mismatches left in the derived tree) |
| 5 | 8-byte pointer stores into game memory the ptr32 stage missed: `typedef struct {..} __attribute__((aligned(2))) Obj;` lost its name (the attribute parsed as a function type), so `Obj **out` kept 8-byte slots (ResGroupListInit_429fd0); `*(R (**)(A))(E)` casts (MenuGridCursorInput_28e170 callback table: crash at the transporter menu, field 30,940); field macros `F(p, char *, o)` (SaveHeaderBuild_3e5520: crash in strcpy at the save, MotionEventCfgEventCmd_1b4180, EvMapObjThrowStart_3661f0) | zeroed neighbour words, wild pointers | tools/stages/ptr32.py: `strip_attrs` in the typedef scan, rule `dptr-fn` (the slot read as a u32 and converted), rule `dptr-macro` (a field macro's pointer-type argument gets RG_P32) |
| 6 | port structs in game memory with host pointers: the MSL string (`msl_string.data`, src/crt/crt_mslstr.c), the global-destructor chain nodes and the ostream sentry (src/crt/crt_msl.c) | an 8-byte data pointer stored into the string's 12-byte object zeroed the next word (archive names) | `CRT_P32` (now in src/crt/crt.h) on those members; the dtor call goes through a plain local (no call through a __ptr32 function pointer, R1) |
| 7 | the game's varargs are retail 32-bit words: `Sprintf_1343b8(buf, fmt, (s32)rec->name, n)` passes a pointer as an s32 whose 8-byte vararg slot has undefined upper bits | crash in the UCRT's `%s` at the save (field 31,161) | src/crt/crt_libc.c `rg_gvformat` (x64): Sprintf / Fprintf / Vprintf walk the format and fetch integer and pointer conversions as 32-bit words, `ll`/`q`/`j` as 64, floats as double |
| 8 | x86-64 clang also ASSUMES 16-byte alignment for an extern object of 16 bytes or more and copies it with movaps; the data layer keeps retail addresses | SaveSysMsgGet_373840 (a 108-byte struct at retail ...084) faulted at every card boot (bootcheck) | derive pass `xalign`: every extern data declaration of game code gets `__attribute__((aligned(1)))` (29,301 declarators; only a weaker assumption, always correct) |

Diagnostics added: rg-game's RG_BREAK on x64 prints the argument registers (rcx rdx r8 r9) as
`args=` and `RG_BREAK_DUMPARG=1..4` dumps at them (src/game/rg_game_main.c).  rg-smoke has an x64
form (src/host/smoke.c: 8-byte pointers, image below 2 GB).

**Known, not fixed:** (a) x64 in SAVE-STATE MODE runs out of address space below 2 GB. `RG_SS=1` alone (no state written) parts the x64 run from i686 at field 26,674 (i686 under RG_SS stays equal); whole states of the two exes at 23,001 and 26,600 differ only in benign pointer words, and at 26,650 the x64 run logs "hook runtime failed to save" (a 4 MB malloc failed). `tools/x64/vmmap.py PID --below-mb 2048` on that run: free space below 2 GB 293 MB (largest hole 238 MB) mid-route, 133 MB (111 MB) later, 69 MB (largest 31 MB) at ~26,600. The ss mode adds a 256 MB host-heap reservation at 0x20000000 (src/savestate/ss_heap.c SS_HEAP_SIZE) and a 64 MB arena to a process whose 64-bit driver DLLs (nvgpucomp64 94 MB, nvwgf2umx 85 MB) also sit below 2 GB, and committed memory keeps growing over the route. So regen (which writes states) goes off route before battle_won on x64; the earlier "save at 18,000 perturbs" finding is most likely the same exhaustion (not re-measured). Next: measure what grows (a non-ss x64 run with the same vmmap poll), then shrink the x64 ss reservations (size SS_HEAP_SIZE to use) or move host-only allocations above 4 GB (only memory game pointers reach must stay below 2 GB). (b) remaining x64-only game-memory differences that do not reach the hash on the route: character
light-blend vectors with flipped sign (Character2LightBlendSetTarget_1aebe0's inputs), a DMA-packet
serial counter (R+01913E0) 0x240 apart after the battle load, bytes left in reused heap blocks
(i686 holds a stale host pointer where x64 holds 0).  (c) the 688 undecided devirt slot sites
(0.4) are still undecided; route parity shows none fired on the route.

**Gates** (2026-10-26; `tools/x64/gates.sh BUILD OUT [steps]`, outputs in out/x64g/{i686,x64};
i686 = build/x64g-i686 = the tree with every x64 edit, x64 = build/x64-windows):

| Gate | i686 | x64 |
| --- | --- | --- |
| pair run (golden route, 32,000 fields) | - | run hash + audio command log equal to i686 at every field |
| `regen.py --check 300` + `verify.py` | **8/8 OK** (run + frame hash; the regen-written save2 card differed and was restored, as always) | regen FAILED: save-state mode runs out of address space below 2 GB on x64 ("Known, not fixed" (a)), so the route went off before battle_won |
| `bootcheck.py --all` | **29/29 PASS** | **29/29 PASS**, every milestone line (fields, modes, encounter fields) identical to i686 |
| `mapcheck.py` | **5/5 DRAWN** | **5/5 DRAWN**, the same detail scores |
| `camprobe.py ch01_salgin ch05_factory` | = retail | = retail (the same values) |
| `link_audit.py check --forbid all --extra rg_ps2_hwbus` | PASS | PASS (on the x64 map) |
| `addr_census.py --check` | PASS (0 arith, 0 marker) | PASS |
| `render_gate.sh` | PASS (route 24 fields failing 0, emu = native ab389a3d1d0232e0; 8 boot fixtures; mapcheck 5 DRAWN; close-up 38.6 dB) | not run: needs the x64 oracle twin rg-game-oracle (emulation build, not built for x64) |
| ctest | -LE fixtures **742/743** (host.audio_reg: the hitch lane's audio regulator, host_sdl.c edited after this build), -L fixtures **12/12** | -L x64 **9/9** (x64.sqrtf_rn + control, x64.datalayout, x64.narrowabi, link gates, fiber arena); everything else **707/752**: 45 fail = 33 Not Run (test executables that do not build on x64: the protos ABI fixtures and overlay native-data tests use i686 data2c with `(u32)&fn` initializers, rg-runtime-tests links kernel32's GetThreadId against the EE one), 9 SEGFAULT (bindings x5, padmc mc_game x3, settings.wide_strips: 32-bit host test harnesses), 3 Failed (dialect.bitfields, trace.deref, trace.demo_pipeline: tests that assert 4-byte pointers) |

Census: section 1 onwards is the morning's, unchanged.

Census and plan, 2026-10-25 (morning). **Nothing in the tree was changed for x64**: no game/,
stage, override or src/ edit. What exists: four census scripts, a scratch toolchain
file, a probe compile of every TU for x86_64, a throwaway `__ptr32` rewrite trial, and
small low-memory test programs. Everything regenerates into `build/x64-probe/`
(scratch, never committed).

PLAN.md D1 put x64 after i686 as P7. D9 (100% native) now passes its build gates
(`native_only.link_audit`, `native_only.addr_census`), so the port is a native i686
Windows program. This document answers three questions: what assumes 4-byte pointers,
how much of it there is, and what the cheapest safe route to x64 is.

**Recommendation (section 5): strategy A, "x64 with a 32-bit game address space".**
Link the exe `/LARGEADDRESSAWARE:NO` with a fixed low base. Windows then keeps
**every** address of the 64-bit process below 2 GB. This was measured, D3D11 driver
included. The rest of strategy A:

- A new ingest stage `ptr32` gives every pointer stored in game memory its i686 size
  (`T * __ptr32 __uptr`).
- datareloc emits pointer words as 32-bit absolute relocations.
- A handful of port pieces get x64 forms: the fiber switch, two asm-thunk generators,
  the save-state heap and the samplers.

Retail memory layouts stay as they are, and so do the on-disc asset formats (in-place
relocation), the raw save format and the retail-address trace mapping. Estimate:
**8-13 lane-days** to an x64 build that passes the regression corpus.

## 1. Tools (reusable; run from the port root)

| Script | What | Output (`build/x64-probe/`) |
| --- | --- | --- |
| `tools/census/x64_census.py [--db build/soak2-i686]` | Text census of the built game tree: game/src, overrides/src, missing/src and game/include, limited to TUs in the i686 compile db. Counts 32-bit address casts, pointer members of records, pointer loads through casts, file-scope pointer externs, int pointer arithmetic, in-place relocation, asm, `long`, varargs and int128. About 30 s | `census_sites.tsv`, `census_records.tsv`, `census_summary.txt` |
| `tools/census/x64_probe.py run [-j 4]` then `report` | Probe compile: every TU of an i686 build's `compile_commands.json` is recompiled for `x86_64-pc-windows-msvc`. `-m32`, `-w` and `-Wno-int-conversion` are dropped; `-Wpointer-to-int-cast -Wint-to-pointer-cast -Wshorten-64-to-32 -Wint-conversion` are added. Game TUs run the front end only; port TUs compile to objects so back-end errors show. `-fdump-record-layouts-complete` runs on both the i686 and the x64 compile and reports every record whose size or field offsets differ. Resumable through `results.jsonl`. About 27 min at -j4 | `diag_sites.tsv`, `layout_diff.tsv`, `summary.txt` |
| `tools/census/x64_ptr32_trial.py [--every 10]` | Strategy-A trial: a throwaway `__ptr32` rewrite of a sample of game TUs (copies under `ptr32/`), compiled for x64, with layouts compared against the unmodified i686 compile. Baseline from the probe's `results.jsonl`. About 3 min | `ptr32_summary.txt`, `ptr32_layout_left.tsv` |
| `tools/census/x64_infra.py` | Port code, build files and tools that assume i686: arch guards, x86 asm, WOW64 samplers, `CONTEXT.Eip`, `-m32`, `_`-prefixed symbols, host addresses kept as `uint32_t` | `infra_sites.tsv` |
| `cmake/toolchain-x64-windows-clang.cmake` | Scratch toolchain: the triple plus the low-memory link flags (section 4). Configuring stops at CMakeLists.txt's pointer-size guard by design; step 1 lifts it | |
| `build/x64-probe/lowmem/t4.c`, `t7.c`, `t8.c` | Scratch programs: ADDR32 data relocations; where a `/LARGEADDRESSAWARE:NO` x64 process gets its memory (heap, stacks, D3D11 device, mapped buffers, DLLs); the LLVM `__ptr32` indirect-call bug | |

Rerun order: `x64_census.py`, `x64_infra.py`, `x64_probe.py run` then `report`,
`x64_ptr32_trial.py`. The probe takes the compile db of an existing i686 build. It
does not configure CMake, so it needs neither vcvars x64 nor a CMakeLists change.
clang finds the MSVC/SDK headers itself.

## 2. Census results (tree built by build/soak2-i686, 2026-10-25)

### 2.1 Game code (`x64_census.py`: 25,307 built files and headers)

| Class | Sites | Files | What it means on x64 |
| --- | --- | --- | --- |
| `(u32)&X` address casts | 14,777 | 914 | 14,678 are **static initializers in data2c** (14,443 function words, mostly vtables; 217 data; 18 other). These are **hard errors** on x64. 99 sites are in code |
| pointer members of records | 7,507 (+133 function-pointer members) | 3,772 | 5,642 record definitions hold pointers, and **4,732 of them are offset-coded** (`pad*`/`unk*` members encode retail offsets). Every one of them changes layout on x64 |
| pointer loaded through a cast `*(T **)p`, `((T **)p)[i]` | 2,637 | 880 | an 8-byte read of a 4-byte slot |
| file-scope pointer externs (`extern T *D_x;`) | 2,133 | 1,826 | the storage is a data2c `u32` word or MAIN bss, so an 8-byte read on x64 |
| `vc_u32 __vptr` (devirt) | 2,016 | 1,738 | already 4 bytes: fine |
| `(T *)((u32)p + n)` int pointer arithmetic | 248 | 168 | fine below 4 GB |
| in-place asset relocation `p->f = (s32)((u8 *)base + p->f)` | 33 | 4 | `ModelResRelocate_14bfd0`, `MotResRelocateBlockList_14bbc0`, `NavGraphRebind_311210`, `ScriptVmExec_173b00`. The on-disc formats have 4-byte slots; also `MotResRelocate_14bd50`, `MotResCopyAndRelocate_154650` |
| plain `long` | 761 | 303 | mostly the protos stage's `(int)(long)arg` casts. Win64 `long` is 4 bytes like i686; Linux x64 `long` is 8 |
| inline asm | 282 | 217 | **201 naked i686 forwarders in 143 files** (protos rule `def-vthunk-naked`: `movl 4(%esp),%eax; movl V(%eax),%eax; jmp *S(%eax)`); 72 datareloc top-level asm (portable); 7 MIPS lines in 1 non-built header |
| varargs | 55 | 4 | portable: stage `gccvarargs` already emits `va_arg`, and Win64 slots are 8 bytes like the EE's |
| `rg_u128` / `rg_s128` | 719 | 600 | portable (`_BitInt(128)` aligned 16) |

The save format is a raw `memcpy` of game objects (SAVE-FORMAT.md: the StateBlock,
party and Insectron team table chunks). Its layout is the in-memory layout, pointer
words included.

### 2.2 Data layer (datareloc)

- MAIN data: 6,306 data2c objects. **1,093 TUs** hold pointer words, about
  **16,750 pointer-to-int initializer words** (probe count, including
  `(u32)((u8 *)&X + off)`). All of them are compile errors on x64
  (`initializer element is not a compile-time constant`).
- 21 more of these errors are in generated overlay tables (`build/*/overlay-gen`)
  and 1 in tests.
- The objects are `u32[]` with `sizeof` checks (`data2c_sizecheck_*`). Their layout
  never changes; only the pointer words need another spelling.
- DATARELOC.tsv rules that produce pointer words: arena-fn 255, arena-data 98,
  bytes-ptr 47, main-bss 42, arena-fn-import 39, main-fn 13, and others.
  `hw-word` (45) and `raw-word` stay numbers.
- MAIN bss is already a top-level asm block with labels. That form is portable.

### 2.3 Port-side ABI pieces (`x64_infra.py`, plus reading the code)

| Piece | Where | x64 status |
| --- | --- | --- |
| Fiber switch (ebp/ebx/esi/edi, TEB SEH head, StackBase/Limit/DeallocationStack, x87 CW, MXCSR) | `src/native/threads/fiber/fiber_arena.c` (28 asm lines) | gated `__i386__` (`FA_SUPPORTED 0`). Needs an x64 switch: rbx, rbp, rdi, rsi, r12-r15, **xmm6-15** (Win64 non-volatile), gs:[8]/[0x10]/[0x1478] TEB fields, no SEH chain. Save states depend on it |
| Overlay import trampoline | `src/native/ovl/ovl_gen.h` (`pushl idx; pushl table; call; jmp *%eax`) | `#error` on x64: 2 TUs + generated `ovl_native_gen.c` |
| Naked vthunk forwarders | protos rule `def-vthunk-naked` (`tools/stages/protos.py`), 201 sites | needs an x64 spelling: `mov eax,[rcx+V]; mov eax,[rax+S]; jmp rax` (this = rcx; the slots are u32) |
| Save-state heap (malloc routing by return address, `_malloc_base`) | `src/savestate/ss_heap.c` | gated `__i386__` (`SS_HEAP_SUPPORTED 0`); the logic is portable |
| Save-state format | `ss_core.c`: header addresses as `uint32_t` (`image_base`, `ram`, section addrs) | valid under strategy A (all addresses below 2 GB); needs an arch tag in the header |
| Crash handler | `src/game/rg_game_main.c` `CONTEXT.Eip/Esp/...` (22 errors) | Rip/Rsp/... |
| `vcall.h` | `VC_CC __cdecl` on i686, empty elsewhere | fine: Win64 has one convention |
| `vu0.h` | `(char *)(unsigned long)` GPR-as-pointer (2 warnings) | fine below 4 GB; `uintptr_t` would be cleaner |
| Heap size check | `src/crt/crt_heap.c` (1 error: negative-size array, a `sizeof` assert) and `missing/` (17: three units' `sizeof(struct)` asserts) | struct sizes assert the i686 layout: they fail exactly where the layout changes, so they are useful gates |
| VU JIT | `src/ps2/vu/vu_block.c` (i386 asm paths) | oracle/tests only (not in the native-only exe): its C fallback runs |
| Soft-double, int128, MXCSR guest mode | `crt_math.c`, `u128.h`, `ps2k_fpu.h`, `rg_nk_internal.h` | portable (the guards already include x86_64) |
| Host addresses as `uint32_t` | 65 sites in 28 files (src 21, tests 7): libmc/libpad/libsdr/fileio/sif EE-side RPC buffers, dmac, timing, demo | fine under A; each one is a truncation under true 64-bit |

Calling convention: clang's x86_64-pc-windows-msvc target uses the Win64 ABI for
every function. There is no MSVC/clang split, because both sides are clang. What
changes against i686 cdecl:

- Arguments are positional registers (RCX/XMM0 by position), so an int/float
  mismatch between a caller's view and the callee is no longer benign. On i686 both
  sides used the same 4-byte stack slot. Exposure: 2,976 `VCALL*`/`VCM*` sites, of
  which 207 have a float in their parameter list. The protos stage already unified
  direct calls.
- A struct of 1/2/4/8 bytes returns in RAX; other sizes return through a hidden
  pointer.
- A 32-bit argument read as 64-bit has undefined upper bits. 789 game-local
  redeclarations of `memset`/`strlen`/... with `u32`/`s32` sizes
  (`-Wincompatible-library-redeclaration`, 653 TUs), plus 4 hard errors (`'X' takes
  type size_t`), are a real x64 hazard.

### 2.4 Third party and host

SDL3 (FetchContent) and D3D11 build for x64 upstream. They are trivial, and
`_deps` was not probed. The `src/host`, `src/gpu` and `src/settings` structs change
layout (pointer members) but are never shared with game memory or files. They are
host structs only.

### 2.5 Test infrastructure

- `tools/fixtures/hangsample.py` and `tools/native/thread_sample.py` use
  `Wow64GetThreadContext`/`WOW64_CONTEXT`/`Eip`/`Esp`, so they read a 32-bit target
  only.
- `tools/perf3d/rgprof.c` uses `CONTEXT.Eip`.
- Nine tools parse `_`-prefixed C symbols from the link map: i686 COFF decorates C
  names, x64 does not. These include `link_readiness.py`, `parity/parity.py`,
  `native/reach_census.py`, `thread_census.py` and `bringup/brklog.py`.
  `src/savestate/ss_map.c` classifies objects from the map and must be checked too.
- 101 files name `i686`/`-m32` (tools 56, src 28, tests 8): build dirs `*-i686`,
  `tools/build.ps1` (`vcvarsall x86`), `fixtures/build.ps1`, `relink.py`, the Linux
  toolchain and so on.
- `CMakeLists.txt` stops on `CMAKE_SIZEOF_VOID_P != 4`, and `RG_COMMON_FLAGS` hard
  codes `-m32`.
- `devirt_verify.py` and `bringup/retnat.py` read i686 disassembly.
- Fixture sets are per exe anyway (states load only into the same exe), so they
  regenerate and need no format work beyond an arch tag.

## 3. Probe compile (x86_64-pc-windows-msvc, every TU)

25,796 TUs (25,292 game-side: game/overrides/missing/data2c; SDL3 skipped). 27 min
at -j4, 3,183 CPU-s. **1,129 TUs fail**:

| Errors | TUs | Cause |
| --- | --- | --- |
| `initializer element is not a compile-time constant` | 1,093 data2c + 20 generated overlay tables + 1 test | pointer words in static data (2.2) |
| negative-size array (`sizeof` asserts) | 3 missing/ + 1 crt | i686 layout asserts |
| `no member named Eip/...` | 1 (`rg_game_main.c`) | crash handler |
| `RG_OVL_TRAMPOLINE: i686 only` | 2 + generated | trampoline |
| `'memset'/... takes type size_t` | 4 game | local libc redeclarations |
| `size of source type does not match destination` | 1 game (`MesWinDrawGlyphs_271b70`) | a `__builtin_bit_cast` of a pointer-sized value |
| tests (ovl, protos vcall, vu smoke) | 5 | i686 asm / trampoline in tests |

Only **5 ordinary game TUs** fail to compile. The x64 problem is almost entirely
silent: it is layouts and truncations, not errors.

| Warning class (unique sites) | Sites | TUs | Notes |
| --- | --- | --- | --- |
| `-Wint-conversion` (implicit pointer to/from `u32`/`s32`) | 25,652 | 6,585 | the u32-held-pointer class: game-main 20,465, ovl 4,822, overrides 364. Truncation/extension, benign below 2 GB |
| `-Wpointer-to-int-cast` | 19,647 | 1,883 | data2c 16,754 (the errors above), game 1,739, generated 1,065 |
| `-Wint-to-pointer-cast` | 6,307 | (all) | game 5,946, game/include 218 |
| `-Wvoid-pointer-to-int-cast` | 3,316 | | |
| `-Wincompatible-library-redeclaration` | 789 | 653 | see 2.3 (a real hazard) |
| `-Wint-to-void-pointer-cast` | 449 | 316 | |
| `-Wshorten-64-to-32` | 107 | 66 | `size_t`/pointer difference to int: harmless at game sizes |

**Layouts** (i686 vs x64, `-fdump-record-layouts-complete`, game TUs without
data2c):

- 18,987 TUs; 61,582 record instances compared.
- **5,911 differ, in 3,880 TUs (20%)**.
- Unique differing records: **4,514**. 3,707 are pointer-member offset-coded
  views, 716 are pointer-member views without pad fields, and 91 differ only
  through a nested record.
- Every one of them is a wrong view of retail memory on x64 (strategy B), or needs
  the `ptr32` stage (strategy A).

## 4. What a 32-bit game address space on x64 needs (strategy A), measured

Three experiments (`build/x64-probe/lowmem/`, clang 23.1.3, lld-link):

1. **Every address below 2 GB** (`t7.c`, linked `/LARGEADDRESSAWARE:NO /DYNAMICBASE:NO
   /HIGHENTROPYVA:NO /BASE:0x400000`). Where things landed:

   | Allocation | Address |
   | --- | --- |
   | image | 0x401000 |
   | main stack | 0x14ED94 |
   | 1 GB `malloc` | 0x02E2D040 |
   | 4 x 64 MB `malloc` | up to 0x4EE61040 |
   | `VirtualAlloc` 256 MB | 0x52E70000 |
   | `VirtualAlloc` with `MEM_TOP_DOWN` | 0x7FD70000 |
   | a second thread's stack | 0x62F6FF24 |
   | **hardware D3D11 device** (NVIDIA, FL 11_0) | 0x6B6EA068 |
   | a mapped 64 MB dynamic vertex buffer | 0x7A070000 |

   53 of 54 modules loaded below 2 GB. Only `ntdll.dll` stays at 0x7FF8xxxxxxxx: it is
   mapped before the image is read, and nothing of it is stored in game memory. The
   same program linked large-address-aware put all 54 modules above 2 GB. So for a
   64-bit LAA:NO image, Windows enforces exactly the 2 GB space the i686 exe has today
   (that exe is not large-address-aware either). Sign- or zero-extending a 32-bit game
   word gives the same pointer.
2. **Pointer words in static data** (`t4.c`):
   - `(u32)&X` in an initializer is a hard error on x64, and so is a `__ptr32`
     initializer (`unsupported expression in static initializer: addrspacecast`).
   - Emitted as asm (`.long X+1`, `.long f`), they become `IMAGE_REL_AMD64_ADDR32`
     relocations. These are correct with the low base.
   - **lld-link does not diagnose an ADDR32 that overflows.** The same object linked
     with the default base 0x140000000 links silently and crashes (`t4b.exe`). The
     low-base link flags therefore need a gate.
3. **`__ptr32` codegen** (`t5.c`, `t6.c`, `t8.c`):
   - `T * __ptr32 __uptr` members are 4 bytes. Loads are `movl` plus zero extension,
     stores truncate, and conversions to and from ordinary pointers and `u32` are
     implicit or plain casts.
   - **LLVM bug: a call THROUGH a `__ptr32` function pointer** (`m->fn(3)`) breaks
     in one of two ways. As a non-tail call it crashes instruction selection
     (`Cannot select X86ISD::CALL ... load (s32)`). As a tail call it is **silently
     miscompiled** to `jmpq *(%rax)`, an 8-byte load from the 4-byte slot. This
     happens on Windows and Linux x86-64, at -O1 and -O2, with or without
     `-fno-optimize-sibling-calls`. clang emits `call addrspace(271)` without an
     addrspacecast.
   - Copying the member into an ordinary function pointer first
     (`void (*f)(int) = m->fn; f(3);`) or casting (`((void (*)(int))m->fn)(3)`)
     compiles correctly.
   - Rule for the stage: function-pointer members and typedefs are **not**
     `__ptr32`. They become a 4-byte slot type with an explicit widening cast at each
     call, or the stage casts every call through one. There are 133 such members.
   - AArch64 has no `__ptr32` lowering at all (it crashes); see risk R5.

**Trial (`x64_ptr32_trial.py --every 10`).** 1,915 game TUs, every 10th. The
mechanical rewrite covers member, global, typedef, `(T **)` cast and `sizeof(T *)`
sites. Results:

- Rewrites: 768 member declarations, 302 globals, 243 pointer-loading casts.
- Differing records: **606 in 382 TUs before the rewrite, 6 in 6 TUs after (99%)**.
  The 6 are anonymous struct types declared inline in a member
  (`struct { ... } *unk8;`), which the trial skips. That is a rewriter limit, not a
  design limit.
- 19 TUs fail to compile:
  - 13 are `assigning 'T **' to 'T * __ptr32 *' changes address space of nested
    pointer`: a local `T **pp = &s->ptrfield`. This is exactly the class that must
    not compile silently. The real stage retypes those locals or is fixed by hand.
  - 5 TUs are rewriter parse slips.
  - 2 are C++ overload resolution.
- Extrapolated to the whole tree: about 60 leftover records and about 190 TUs to
  touch after the stage.
- The game build passes `-Wno-incompatible-pointer-types`. The x64 build must turn
  `incompatible-pointer-types` (and the address-space error) back on, at least for a
  census pass, or `T **pp = &p32` mismatches pass silently.

## 5. Strategies, estimates, recommendation

Observed pace on this project: from the empty skeleton on 2026-10-11 to the D9 build
gates on 2026-10-25, the lanes produced one generator stage per lane-day. protos,
devirt, datareloc, hwaccess, vu0frame, wideret and stack-block each took one day,
with re-ingest and full gates, plus 1-3 days of bring-up debugging per large change.
A "lane-day" below is one agent lane at that pace.

**A. x64 with a 32-bit game address space (recommended).** Link LAA:NO with a low
fixed base, add a `ptr32` stage for the pointers that live in game memory, and have
datareloc emit ADDR32 words. Game logic, retail layouts, assets, the save format,
save states and the trace mapping stay unchanged.

| Step | Work | Lane-days |
| --- | --- | --- |
| 1 | Arch-aware CMake (`RG_ARCH`, `-m32` only for i686, pointer guard 4 or 8), x64 toolchain, low-memory link flags, **gate** `x64.lowmem_link` (PE header: LAA off, base below 2 GB, no DYNAMICBASE) and a startup self-check (crt0 / ss_heap: every arena below 2 GB) | 0.5 |
| 2 | Stage `ptr32` (from the trial): members, column-0 externs, pointer typedefs, `(T **)` casts, `sizeof(T *)`, inline anonymous member structs; function pointers as 4-byte slots with call-site casts (LLVM bug). Plus a layout **gate**: `x64_probe` layout diff = 0 for game TUs, with a control (an injected 8-byte member must fail). About 190 TUs of nested-pointer fixes | 2-3 |
| 3 | datareloc x64 mode: the 1,093 pointer-holding objects as asm `.long sym+off` (ADDR32), same section and alignment rules, the same for the generated overlay tables (21) | 1 |
| 4 | ABI pieces: x64 fiber switch + TEB + xmm6-15 + save-state tests (1); trampoline + `def-vthunk-naked` x64 spelling (0.5); ss_heap x64, crash handler, map tools without `_`, x64 samplers (`GetThreadContext`), arch tag in the save-state header (1) | 2.5 |
| 5 | libc redeclarations (789) to the real prototypes (protos rule), `MesWinDrawGlyphs` bit cast, the `sizeof` asserts | 0.5 |
| 6 | Bring-up to the gates: unknown 4-byte assumptions (memcpy of pointer-holding structs into `u32` buffers, unions of pointer and f32/u32, Win64 int/float positional mismatches in the 207 float VCALL slots). Golden routes, run hashes = i686 | 2-5 |
| | **Total** | **8.5-12.5** |

**B. True 64-bit pointers.** Real pointer types in game memory, layouts recomputed.

- Every u32-held pointer gets retyped: about 25.7k implicit conversion sites, 6.3k
  int-to-pointer casts and 1.7k pointer-to-int casts, against types declared per
  file.
- All 4,514 differing records (3,707 offset-coded) need consistent relayout across
  every TU that views the same object. That needs the shared headers that
  `main-headers` has only partly built.
- 2,016 u32 vptrs and vtables become pointer-sized; 14.7k data words get retyped and
  objects resized, which breaks the `data2c_sizecheck`s and neighbour reads.
- The asset formats with in-place relocation (4+ formats) need host-side shadow
  structures.
- The raw-memcpy save chunks (StateBlock, party, team table) need a serializer
  rewrite to stay retail-card compatible.
- Save states change format, and the retail-address trace mapping, parity and
  lockstep tools lose their 1:1 layout.
- Estimate: **40-80+ lane-days**, with a long tail of silent layout bugs and no
  oracle at the struct level. It buys more than 2 GB of address space. The game
  uses a 26.7 MB heap.

**C. Hybrid.** Do A now. Later, any subsystem rewritten natively (D9-style: renderer,
audio, host) uses ordinary 64-bit host types behind its API, and game memory keeps
`__ptr32`. Move to B only if the 2 GB cap ever matters, which nothing suggests.

**Recommendation: A, followed by C where it comes free.** The work is about 90%
mechanical and generator-driven, matching how this port was built. It keeps
byte-for-byte retail memory layouts, so every existing oracle carries over: run
hashes, the trace map, parity and save states. The cost is a 2 GB cap, which is
today's i686 cap.

## 6. Migration plan (strategy A), with gates

Order matters: each step ends in a passing gate. The i686 build stays the default and
must stay byte-identical: a ptr32/ADDR32 stage is a no-op on i686 (the spellings are
`#define`d away or emitted only under `RG_ARCH=x64`).

1. **Plumbing.** `cmake/toolchain-x64-windows-clang.cmake` (exists as scratch), an
   arch switch in CMakeLists.txt, `tools/build.ps1 -Arch x64` (`vcvarsall x64`), build
   dir `build/*-x64`.
   - Gate: `x64.lowmem_link` (PE-header check plus a control that links without
     LAA:NO and must fail), and the existing ctest set on i686 unchanged.
2. **`ptr32` stage** (tools/stages/ptr32.py, run after protos/devirt). It reuses
   `x64_ptr32_trial.py`'s rewriter and adds inline member structs and the
   function-pointer slot form. Rows go to `game/PTR32.tsv`.
   - Gate: `x64_probe.py` layout diff = 0 over game TUs (new ctest `x64.layouts`,
     with a control). x64 compile with
     `-Werror=incompatible-pointer-types` and the address-space errors on: 0 errors.
3. **datareloc ADDR32.** Pointer-holding objects become top-level asm (as data2c_bss
   already is).
   - Gate: the x64 link resolves; an x64-vs-i686 data image diff (every word equal
     after subtracting the image base / symbol addresses) is clean.
4. **Port ABI pieces** (fiber, trampolines, naked thunks, ss_heap, crash handler,
   tools).
   - Gate: ctest on x64 (kernel, fibers, savestate round trip, overlay, protos
     vcall).
5. **Bring-up.**
   - Gates in order: bootcheck --all; golden routes with run hashes **equal to the
     i686 exe's**. Same input, same game state: retail layouts are unchanged, so
     the hashes must match.
   - Then the fixture set regenerated for x64 (verify.py), mapcheck, render_gate,
     and `native_only.link_audit` / `addr_census` on the x64 map.
   - Then a long soak. The P7 gate from PLAN.md: the regression corpus passes on x64.
6. Later (C): Linux x64 (below), and the native subsystems' own structs on real
   64-bit types.

## 7. Risks

- **R1 LLVM `__ptr32` bugs.** The indirect-call bug was found within ten minutes;
  more may exist (vectorizer, atomics, memcpy lowering). Mitigations:
  - keep function pointers out of `__ptr32`;
  - run the full route gates, not just unit tests;
  - keep the repro (`lowmem/t8.c`) and report it upstream;
  - fallback: a `u32` slot type with accessor macros in place of `__ptr32` (more
    churn, same layouts).
- **R2 ADDR32 silent overflow.** lld-link accepts an ADDR32 relocation that overflows
  when the base is above 4 GB. The link gate in step 1 is the only defence. Never
  drop `/DYNAMICBASE:NO` or the low `/BASE` on x64.
- **R3 hidden 4-byte assumptions** the census cannot see: unions of a pointer with
  f32/u32, `memcpy(dst, obj, 4)` of a pointer, pointer tables walked with `+= 4`.
  Under A they are all still correct wherever the stored word is a `__ptr32`. They
  break only for a pointer held in an *ordinary* (64-bit) pointer variable that was
  stored into memory through a cast. The probe's `-Wint-conversion` /
  `-Wpointer-to-int-cast` sites are the place to look; the run-hash equality gate
  catches the rest.
- **R4 Win64 positional registers.** An int/float mismatch through `VCALL` slot
  types or casted callbacks is benign on i686 and wrong on x64: 207 float VCALL
  sites. Same with 32-bit size arguments read as `size_t` (789 libc
  redeclarations). Needs a protos rule or a census before bring-up.
- **R5 other platforms.** Linux x86-64 can do A: `__ptr32` lowers there too (same
  call bug), plus a non-PIE low link, `MAP_32BIT` arenas, a low custom allocator and
  `pthread_attr_setstack` from the arena. Shared libraries (GL/Vulkan drivers) load
  high, which is fine as long as their pointers never enter game memory.
  **macOS arm64 cannot do A** (`__PAGEZERO` reserves the low 4 GB, and there is no
  AArch64 `__ptr32` lowering). It would need B or a based-pointer scheme. That
  decision belongs with "other platforms" in P7 and does not block Windows x64.
- **R6 2 GB address-space cap** as today. The game heap is 26.7 MB, the state heap
  reserves 256 MB and the fiber arena 64 MB. Only HD texture packs (P7 mods) could
  push toward the cap; GPU memory is not counted.
- **R7 tools.** The samplers, map parsers and fixture scripts quietly assume i686
  (2.5). Until they are ported, debugging x64 hangs is harder: port the samplers in
  step 4.
