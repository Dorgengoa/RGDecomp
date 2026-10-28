# Rogue Galaxy PC port — plan

Drafted 2026-10-11. Status: **plan approved** (D1–D8 confirmed by the user on 2026-10-11;
D9 "100% native, no emulation" added by the user on 2026-10-17, superseding the end state
of D3 and D4). Bring-up (P0-P3) runs on emulated scaffolding; the de-emulation track is
now active.

**Where to resume:** docs/BRINGUP.md "Start here (next session)" (current status, priorities,
latest play-test exe, backup location); the dated log is docs/bringup/BRINGUP-HISTORY.md.

## Goal

Build a native PC executable that runs **the whole game**: all of MAIN plus all five
overlays (TITLE, INSMENU, NORMAL, FACTORY, INSECT), compiled from the decompiled C/C++.
The game's own logic boots, schedules threads, loads areas, fights battles and saves. The
PS2 hardware and IOP services are replaced by a host platform layer underneath it.

**The target is a 100% native port: no emulation in the shipping executable** (USER
directive 2026-10-17, decision D9). The finished game runs as if it had been written for
Windows: game code calls native rendering, audio, file, input and threading services
directly. No VU/VIF/GS/DMAC/IPU/SPU2/IOP/SIF hardware models, no virtual PS2 memory map,
no PS2 packet formats as a runtime interface. The emulated components built during
bring-up (P2-P3) are scaffolding and verification oracles only; they move out of the game
executable into tests/tools as the native replacements land (see "Native end state").

Out of scope:

- Re-implementing game logic by hand. `private/pc-assets-01a116f0` already tried
  that: selected routines inside a native shell. It has a playable slice, but it can't
  grow into the full game without rewriting all of it.
- Emulating the R5900. `recomp/` is retired, and its code isn't reused here (see "Prior
  work" below).

## Starting point

| Input | State |
| --- | --- |
| Decompiled source | 100% C for all six scored images: 19,993 functions, every byte matched. Each image relinks byte-identical. |
| Data | `.data`/`.rodata`/`.bss` are generated C (d784320c). MAIN `.data` holds 0 raw address literals. |
| Names | Final (naming fold 12). The other session is preparing the clean, publishable tree. **This port starts from that tree, pinned by commit hash.** |
| LAUNCHER.BIN, VIEWER.BIN | Each is a 256-byte stub, so they need no work. |
| IOP modules | 16 IRX files in `work/MODULES`, none decompiled: CDVDSTM, LIBSD, MCMAN/MCSERV, PADMAN, SIO2MAN, SDRDRV, PCMPLAY, and the sound stack (SKMIDI, SKHSYNTH, SKMSIN, SKSOUND, MODHSYN, MODMIDI, MODMSIN). |

What the source looks like matters for every decision below:

- **Most files declare their own local struct views**, with padding up to an offset
  (`u8 pad000[0x64]; s32 field;`). Many hold pointers in `s32`/`u32` fields. Shared
  headers are only partly built (`private/main-headers-a94e7c21`).
- **Virtual calls go through dummy classes** (`class Unit { virtual void v0(); ... v35(); }`)
  whose slot numbers were chosen so that *mwcc* emits retail's vtable load. Another
  compiler lays out vtables differently, so these call sites won't carry over unchanged.
- **The remaining assembly is mostly the Sony SDK** (`src/main/sdk`, libvu0, libmpeg/IPU,
  DMA, SIF), plus inline COP2/VU0 macros (`include/libvu0.h`, `vu0inline.h`) and two
  EE-asm targets (0x003AB220/0x003AB240).
- **Some matching levers are harmless on a host**: `#pragma optimization_level`, `x = x;`,
  launder casts and `.sdata` section attributes. Others aren't: an uninitialised local
  used as an argument, under-argued calls, and declaration/definition arity mismatches
  (`config/arity*.txt`) all need fixing.

## Architecture

```
+--------------------------------------------------------------+
| game/        decompiled MAIN + 5 overlays, compiled as-is    |
|              after mechanical transforms (generated)         |
| overrides/   hand-ported replacements for individual files   |
+--------------------------------------------------------------+
| sce/         the Sony SDK API surface the game calls         |
|              (sceGs*, sceDma*, scePad*, sceMc*, sceCd*,      |
|               sceSif*, sceMpeg*, sceVu0*, EE kernel calls)   |
|              -- reimplemented, NOT ported from the asm bodies|
+--------------------------------------------------------------+
| ps2/         hardware models behind the SDK surface:         |
|              EE thread scheduler, INTC/VBlank, DMA/VIF1,     |
|              VU1, GS, IOP-service HLE (file, pad, mc, sound, |
|              stream), IPU/movie                              |
+--------------------------------------------------------------+
| host/        SDL3 window/input/audio, renderer backend,      |
|              config, extracted-data access, save storage     |
+--------------------------------------------------------------+
```

This is the **bring-up** architecture. The `ps2/` layer is transitional: per D9 it is
removed from the shipping executable, and the end state is two layers, the game (with
its draw, sound, file and movie code paths rewritten or overridden to call native
services) on top of native host services (renderer, audio engine, file system, threads,
input). See "Native end state".

The SDK layer is the main boundary. The game never touches hardware directly except in a
few places: a census found 34 files with hardware-register or scratchpad literals, nearly
all of them in `lib/sce`. So replacing the SDK *API* means only those few game-side files
need edits.

### Decisions (all confirmed 2026-10-11)

**D1. Build 32-bit (i686) first, and move to x64 later as its own track.** The source
stores pointers in 32-bit fields throughout, its per-file structs encode 4-byte pointer
offsets, assets are fixed up in place, and the generated data tables are `u32`. On i686
all of that just works. A probe in the research env already showed what x64 does to it:
`VuMicrocodeTableInit`'s table grows from 0x600 to 0xC00 bytes. The x64 alternative (game
addresses as explicit 32-bit handles, with every dereference translated) touches nearly
every function before the first boot. On i686 the first boot needs only the transforms
below. x64 becomes P7, once shared headers and real types exist.
*(This reverses the research env's "x64 + explicit addresses" lean. That was a design
review; this is a sequencing choice.)*

**D2. Compiler: Clang/LLVM with CMake + Ninja.** Clang accepts the GNU attributes and
extensions in the corpus, targets i686/x64 on Windows and Linux, and works with
sanitizers. Flags:

- `-m32 -msse2 -mfpmath=sse` (no x87 excess precision)
- `-fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks`
- `-O1` until the UB audit is done. *(Done 2026-10-18, docs/UB-AUDIT.md: game code at
  `-O2` (`RG_GAME_OPT`, cmake/game.cmake) with `-fno-strict-float-cast-overflow
  -fwrapv-pointer -fno-finite-loops -ftrivial-auto-var-init=zero`; platform code keeps
  `-O1` / its own per-source `-O2`.)*

**D3. Graphics: emulate first, then go native.** *(Superseded in its end state by D9
(2026-10-17): the emulated path below is bring-up scaffolding and the reference oracle
only. The shipping renderer is fully native: the game's render code emits host draw calls
(vertex/index buffers, native-format textures with hardware sampling, standard depth and
blend state, render targets for its full-screen effects) through a retained scene/pose
boundary, with no DMA chains, VIF/VU1 programs or GS emulation at runtime. Native
replacements are checked against the emulated path on recorded frames. Do not spend
effort optimising the emulated path beyond what testing needs.)* First backend: run the game's own DMA
chains through a VIF1 + VU1 interpreter into a hardware-accelerated GS renderer (a GPU
implementation of GS primitives, blending, and texture/CLUT upload). Its scope is limited
to the GS features this game uses, which a register census settles. That gets correct
pixels without understanding each microprogram. After that, replace each VU1
microprogram, hottest first, with native C++ that emits host vertex buffers. The set is
finite (`VuMicrocodeTableInit` lists it), and each one can be checked against the
interpreter on captured packets. The GPU API sits behind a small interface; D3D11 on
Windows comes first, because `pc-assets` already has working device, texture and
readback code.

**D4. IOP: re-implement the services at the RPC boundary (HLE).** File I/O, CDVD
streaming, pad, memory card and sound get host implementations of each module's RPC
protocol. `recomp` memory notes already document the protocols: L5 fileio packets, PADMAN,
SKMIDI/MSIN, MVI. Sound is the biggest item. It needs a software SPU2-style voice mixer
(ADPCM, ADSR, pitch, reverb) plus hsynth/MIDI sequencer semantics. Fallback if sound
fidelity stalls: run the sound IRX files on an R3000 interpreter with a minimal IOP kernel.
*(Superseded in its end state by D9: the RPC/SIF/IOP-RAM HLE and the SPU2-style mixer are
bring-up scaffolding. The shipping build has a native audio engine that loads the game's
banks and sequences directly and is called by the game's sound API (no sdremote packets,
no SIF DMA, no IOP memory); files are read by name through the host file system (no
sector/LSN model); pad and saves are native services. The R3000 fallback is dropped.)*

**D9. 100% native, no emulation (USER directive 2026-10-17).** The shipping executable
contains no hardware emulation of any kind. Every `ps2/` model (EE kernel fibers and
virtual VBlank clock, DMAC, VIF, VU0/VU1, GS, IPU, SPU2, IOP/SIF, CDVD sectors, hwbus,
the 32 MB EE-RAM block and PS2 address masks) is replaced by native code: game threads
become a native game loop or host threads with explicit synchronisation, timing comes
from the host clock with the fixed-step logic tick ("Unlocked frame rate"), memory is
ordinary host allocation, VU0 macros are plain C/SIMD math, and the hardware-facing game
code (render, sound, movie, file, pad) is rewritten or overridden to call native services.
Emulated components may live on only in tests/tools as oracles. Gate in "Native end
state".

**D5. Platform library: SDL3** for the window, input, gamepads and audio output. It runs
on Windows, Linux and macOS.

**D6. Repo shape: a separate repo that consumes a pinned decomp snapshot.** `game/` is
regenerated by `tools/ingest.py` from a commit hash plus transforms. It's never
hand-edited. Hand changes live in `overrides/<path>`, and each records the SHA-256 of the
original file it replaces, so a changed upstream file makes its override fail loudly. The
matching repo stays the reference and isn't modified for the port.

**D8. Game data: extract it once, on first run.** No game data ships with the port. On
first run, `rg-extract` takes the user's ISO and does the following:

- Checks the ISO's SHA-1 against the known US v1.01 image (SCUS-97490). It rejects any
  other image, and names the region or version when it can.
- Unpacks the disc filesystem into a `data/` folder, keeping the original paths.
- Converts formats that are worth converting, once: MVI movies are decrypted and remuxed
  or transcoded to a standard container. Other files stay byte-identical, so the game's
  own loaders still parse them.
- Writes a manifest of every output file's hash. On each launch the port checks that the
  manifest exists, and re-checks the hashes when asked to.

At runtime the port reads only `data/`, never the ISO. The extractor is the only code
that understands ISO 9660/UDF. The mod-profile loader (from `pc-assets`) overlays mod
folders on `data/` by path. This is the usual pattern for this kind of port: OpenGOAL
extracts the ISO on first run; Ship of Harkinian and the SM64 port convert the user's ROM.

**D7. License: CC0 1.0 for all original port code and docs.**

- The repo root carries the CC0 text in `LICENSE`. The README says CC0 covers only the
  port's own code (platform layer, tools, renderer, docs).
- The decompiled game code in `game/` and `overrides/` is derived from Level-5/Sony's
  copyrighted game. CC0 can't cover it, and the README says so.
- **No GPL code, ever.** That rules out PCSX2 and DobieStation as code sources. Both can
  still be used as tools: PCSX2 as the trace and GS-dump oracle, never copied from.
- Permissive code (BSD/MIT/zlib/Apache), such as Play! (BSD-2-clause) for VU, GS or SPU2
  reference, may be vendored under `third_party/`. Each import keeps its own license
  header and gets an entry in `THIRD_PARTY_NOTICES.md`.
- FFmpeg, if used, must be an LGPL build (no `--enable-gpl`) and linked dynamically.

## Mechanical transforms (`tools/ingest.py`)

Applied to the pinned snapshot in this order. Each one is a script with a census
(how many sites it changed) and is idempotent.

1. **Unit selection.** Take only the sources that are registered in `cunits.txt` and the
   `ocunits` lists, plus the generated data sources. Drop stale or unregistered drafts.
   The `naming` tree has about 26k `.c`/`.cpp` files on disk, and not all of them are
   linked units.
2. **Prototype unification.** Generate one `game_protos.h` from the *definitions*.
   Compile every file against it. Each conflict, whether arity, a return type or an
   `s32`-vs-pointer argument, goes into a report and gets fixed by an override. Seed the
   report from `config/arity*.txt`. Known example: `ObjRecGetLiveObject` is called with 1
   argument but defined with 2.
3. **Virtual calls: de-virtualise the class declarations; call sites stay as they are.**
   The probe in `probes/vtable/` settled the mwcc ABI from retail:
   - The vptr points at the vtable symbol. Word 0 is RTTI (0 in all game classes),
     word 1 is 0, and slot k is at byte offset 8 + 4k.
   - The vptr sits after the data declared before the first virtual.
   - `this` is never adjusted at the call site.

   Clang's Itanium layout differs, so each dummy class's first `virtual` becomes an
   explicit `__vptr` member, and every virtual becomes an inline cdecl thunk
   `VCM(ret, (args), 8+4k)` (see `probes/vtable/vcall.h`).
   - **Check:** each function's (VOFF, slot) multiset must equal retail's `lw $25` pairs.
     The census found 3,445 virtual-call sites.
   - **Exceptions that need overrides:** the one real constructor
     (`CameraObjCtor_177430`) and the one pointer-to-member site
     (`SaveModeDispatch_375df0`). mwcc's member-pointer record is 12 bytes; clang's is 8.
4. **VU0/COP2.** Swap in a port copy of `include/libvu0.h`/`vu0inline.h` with the same
   macro names implemented in C (or SSE). Write them against `sceVu0*` semantics, with a
   unit test per macro.
5. **Address literals.** Rewrite scratchpad (`0x70000000`), uncached and
   uncached-accelerated masks (`0x20000000|p`, `0x30000000|p`), KSEG addresses and
   hardware registers into `PS2_SPR(off)`, `PS2_UNCACHED(p)` and `HW_W32(reg, v)`
   accessors. `HW_*` calls go to the `ps2/` models.
6. **Assembly-bodied units.** Exclude them and bind each symbol to an `sce/`
   implementation or an override. Every excluded symbol is listed in a manifest, so
   nothing gets stubbed silently.
7. **Overlay data.** Compile each overlay's `.data`/`.bss` into its own block, so that
   loading an overlay can restore it (see P2).
8. **Matching-only pragmas.** Strip them, or leave them where they're ignored.

## Unlocked frame rate (a goal from P3 on)

The port must render at any frame rate (60, 120, 144 Hz and uncapped) while the game
keeps its original logic cadence. Retail runs gameplay on a two-VBlank interval (about
30 fps) and menus/title on one (about 60 fps). Many systems count calls, not time:
effect lifetimes, AI counters, animation events, input repeat. So "call the frame loop
faster" breaks the game. The approach comes from the audit in
[docs/FRAMERATE-AUDIT.md](docs/FRAMERATE-AUDIT.md):

- **Logic stays fixed-step.** Each logical tick runs the game's update and its task
  table exactly as retail does, on the virtual VBlank clock and the mode's 1-/2-VBlank
  interval. Host elapsed time decides *how many* ticks to run (a bounded accumulator),
  never the size of a tick.
- **Presentation is separate.** After each tick, publish a snapshot (camera, entity
  transforms, skeletal poses, effect state). Each present interpolates between the last
  two snapshots and builds model/view inputs **before** skinning, VU work and packet
  emission, so in-between frames show real motion, not repeated packets. Reset history
  across cuts, teleports, scene loads and entity-id reuse.
- **Draw-side writes get classified.** The task table splits update (0–91) from draw
  (93–174), but draw callbacks write persistent state. Each write is moved to the tick,
  kept as presentation history, or isolated as scratch, before a draw may run more than
  once per tick. Title and pause drawing have their own loops and need the same split.
- **Four clocks:** host time, virtual VBlank time, logical tick time, audio/media time.
  Monitor refresh is never a game clock, and renderer cost never feeds the game's
  frame-time feedback (`GfxEndFrame`).

Work order across phases:

1. **P2:** the virtual clock and the 1-/2-VBlank tick boundary already exist; add
   tick-level instrumentation (interval, scene time scale, task calls, pad edges, sound
   owner) on both the port and the PCSX2 harness.
2. **P3:** build the renderer with a retained transform/pose boundary from the start,
   not only DMA packet replay, so interpolation does not need a second renderer later.
3. **P4/P5:** move draw-side writes out of the draw tasks area by area (field camera and
   characters first, then title/UI, animation, effects, then the overlays).
4. **P6:** turn on high-rate presentation with interpolation (camera and root transforms,
   then poses and effects) plus a frame-rate setting (locked 30/60, a fixed cap, or
   uncapped, with VSync on or off).

**Gate (P6):** for the regression corpus, the logical state and event sequence (combat
outcomes, AI decisions, effect spawn/expiry ticks, sound triggers, input edges) is
identical at 30, 60, 120 and 144 fps, uncapped and jittered presentation, including
frames with zero ticks and frames with several. Re-rendering one snapshot repeatedly
changes no game state.

Progress (2026-10-25, renderer lane, docs/NATIVE-RENDER.md "Interpolated presentation"):
opt-in `display.interpolation` (default off, Original off) in the native-only exe. The
renderer retains the last 5 frames as the device's own command list; presents between
VBlank phases replay the shown frame with camera, object and bone transforms interpolated
from the previous frame (mesh items keyed by decoded mesh + context + variant, nearest
instance) and 2D / effect / generated-primitive triangles lerped when paired by state and
order; unmatched items snap to the latest. Logic and run hash unchanged (passes never touch
local memory and are undone before anything reads the device). Measured headless at a
simulated 144 Hz: a right-stick pan moves 8-10 px every present instead of 40 px every
fifth (judder 0.14 vs 2.00), no pops. Since checkpoints 12-13 (docs/NATIVE-RENDER.md) the
characters (Z-scale composites) move with the scene and their poses are interpolated too (bones,
with the composite copy widened). Not yet: the draw-side write classification above (the replay
approach does not need it for presentation), play-testing on a real 144 Hz display; the
one-game-frame display delay stays (extrapolating it away brings a step back at every change of
motion: measured, `RG_INTERP_LEAD`, default 0).

## Native end state (D9)

The port is finished only when it runs natively, as if the game had been written for
Windows. Each emulated subsystem gets a native replacement; the emulated version is kept
only as a test oracle until its replacement passes, then leaves the game executable.

| Bring-up (emulated) | Native replacement |
| --- | --- |
| VIF1 + VU1 interpreter/translator, DMA chains | Game render code (model/packet builders, `GsDraw*`, effects) emits host vertex/index buffers and draw calls; the VU1 microprograms' transform, lighting, skinning and clipping become C/SIMD or GPU shaders |
| GS model + exact GPU raster (swizzled 4 MB VRAM mirror, ROV ordering) | Native renderer: textures decoded once into native formats (hardware filtering), standard depth buffer and blend state, real render targets for bloom/blur/DOF; a GS-exact blend fallback only for equations hardware blending cannot express |
| VU0 macros on a VU0 model, `vcallms` microprograms | Plain C/SIMD math functions |
| EE kernel (fibers, semaphores, alarms, virtual VBlank), spin-loop hooks | Native game loop / host threads with explicit sync; host clock + fixed-step logic tick; no spin loops |
| 32 MB EE-RAM block, scratchpad, uncached masks, hwbus | Ordinary host memory; accessors and masks removed from game code |
| CDVD sector/LSN model, FILEIO/LOADFILE HLE | File reads by name/offset from `data/` through the host file system; async loads as host I/O |
| SIF/IOP HLE, IOP RAM, sdremote packets, SPU2-style mixer, SK servers | Native audio engine called by the game's sound API: loads banks/sequences/streams directly, host mixing |
| IPU + DMA ch3/4 movie layer | Native movie player service (own MPEG-2 decoder, already built) |
| Pad/MC servers (padman/mcserv) | Native input-action layer and save files, called directly |

Rules:

- Replacements happen at the highest sensible boundary (the game's own API: draw calls,
  sound calls, file loads), not by making a faster emulator. Performance work goes into
  the native path; the emulated path is optimised only as far as tests need.
- Every replacement is verified against the emulated oracle (frames, audio, state traces)
  on the regression corpus before the emulated path is removed from the game build.
- **Gate (native):** the shipping executable links none of `src/ps2/*` models (`vu`, `vif`,
  `gs`, `dmac`, `iop`, `sif`, `spu`, `cdvd`, `hwbus`, kernel fibers) and no PS2 address
  arithmetic remains in game code; the regression corpus and a full playthrough pass; the
  game runs well above its original frame rate on modest PC hardware.
  The two build halves are ctest gates: `native_only.link_audit` (the map: no emulation
  library) and `native_only.addr_census` (`tools/native/addr_census.py --check`: 0 `arith`
  and 0 `marker` sites in the compiled game set -- no HW accessor, hardware / scratchpad
  literal, PS2_PHYS / UNCACHED / UCAB identity marker, unreviewed KSEG mask,
  `RG_PS2_ADDR_` define, overlay-arena address map or EE-RAM cast; each with a control test
  that must fail). Words that only look like addresses are classified, not counted: tables no
  compiled code reaches (`dead-data`, by reachability), reviewed DMAtag ids and flag bits
  (`dmatag` / `flag`, the script's REVIEWED table and the hwaccess stage's LEAVE_RULES), and
  datareloc's raw data words (`raw-word`).
  *Status 2026-10-25:* link half met -- the native-only rg-game links no emulation library
  (`link_audit.py check --forbid all`, gate test `native_only.link_audit`; the last ones were
  libvu0 on the VU register struct and the overlay arena, now `src/native/vu0` and the native
  overlay module table `src/native/ovl`). Address half met 2026-10-25 (later the same day):
  `addr_census.py --check` PASS, 0 arith / 0 marker (was 36 / 44): the game's register sites
  call the native services by name, identity markers stripped, the retail heap calculation is
  the runtime heap's size, the kernel-RAM ReleaseAlarm body is port-provided
  (docs/bringup/BRINGUP-HISTORY.md 2026-10-25 "D9 address gate"). Left of D9: the regression
  corpus / full playthrough and the frame-rate goal.

## Phases and gates

Each phase has one pass/fail gate. The gate is a reproducible command, not a screenshot
someone looked at once.

### P0 — Foundation

- Set up the repo skeleton, CMake toolchain files (i686 Clang on Windows, `-m32` on
  Linux) and CI-style scripts.
- Ingest the clean snapshot once the other session publishes it. Record its commit hash.
- Build `rg-extract` (D8): hash check, filesystem unpack, manifest. MVI conversion
  comes in P4.
- Run the censuses: real asm bodies by symbol (game vs SDK), virtual-call sites,
  address-literal sites, prototype conflicts, EE syscalls used, SIF RPC ids per IOP
  module, GS registers and primitive types used, VU1 microprogram list.
- Confirm the mwcc vtable layout (D2/transform 3).
- **Gate:** every census exists as a checked-in TSV. `ingest.py` reproduces `game/`
  byte-for-byte from the pinned hash. `rg-extract` unpacks the retail ISO into `data/`,
  every file in the manifest is byte-identical to the disc, and a wrong or modified ISO
  is refused.

### P1 — It compiles and links

- Run transforms 1–8.
- Write `sce/` stubs that log and abort on first call.
- Fix compile errors with overrides. Each override is the smallest edit that keeps the
  logic the same.
- **Gate:** the i686 executable links with **zero unresolved symbols**, and every stubbed
  symbol is in the manifest.

### P2 — It boots headless

Implement, in this order:

- **Memory.** A 32 MB game RAM block for the game's own heap manager (`EndOfHeap` and
  the overlay arena), a 16 KB scratchpad, and static constructors run in retail order.
- **EE kernel.** Threads with EE semantics: priority-based, non-preemptive, and running
  one at a time. Use host fibers under a single scheduler, not free-running OS threads.
  Also semaphores, `WakeupThread`/`SleepThread`, alarms, interrupt handlers (VBlank,
  DMAC) delivered at defined points, and a virtual VBlank clock.
- **Overlay manager.** Loading an overlay resets its `.data`/`.bss` from the initial
  image, runs its constructors and binds its entry point. Calls from MAIN into the
  0x4E9E80 arena go through a table keyed by (overlay, address). The 89 overlay
  references in MAIN data come from linker imports in `data2c`.
- **File HLE.** The game reads the disc **by sector**: `sceCdSearchFile`, then
  `sceCdRead` (CDVDFSV, 0x80000592..59C), not FILEIO. So the CDVD model translates an
  LSN range to (file, offset) using the LBAs in `data/MANIFEST.tsv`, including layer-1
  addressing. FILEIO/LOADFILE are still used for module loads.
- **IOP RAM model.** Sound banks, stream slots and movie audio are sent into IOP RAM by
  raw SIF DMA, so the IOP HLE needs addressable IOP memory.
- **Timer 0.** The game reads `T0_COUNT` directly, so model timer 0 on the virtual clock.
  Model timer 2 for `DelayThread`'s alarms too.
- Pad with no input, and a memory-card stub.
- **Gate:** the game runs headless from cold boot to the title-menu loop for N virtual
  frames with no stub hit, and a **state-trace comparison** (see Verification) against
  PCSX2 matches for those frames.

### P3 — It draws

- DMA/VIF1 path, VU1 interpreter and the GS renderer, under the D3 scope.
- Display/CRTC setup, interlace/field handling, frame presentation.
- Keep a retained transform/pose boundary in the renderer for the unlocked frame rate.
- **Gate:** title screen and menus render. Per-frame GS-output comparison against PCSX2
  GS dumps of the same frames passes within a pixel threshold.

### P4 — It plays

- **Pad:** SDL3 gamepad and keyboard mapped to the DS2 report, through an input-action
  layer that later supports rebinding (P6).
- **Settings foundation:** the typed settings registry, config file, an in-game settings
  overlay with basic display (window mode, VSync, scale) and audio volume options. P6
  adds the rest.
- **Memory card:** host save files with the PS2 directory and icon semantics. Optionally
  import and export PCSX2 `.ps2` card saves.
- **Movies:** an FFmpeg-backed service at the `sceMpeg`/movie-player boundary. It plays
  the movies `rg-extract` converted, so no decryption happens at runtime. The MVI
  decrypt and container are already known; add the conversion to `rg-extract`. The
  service must keep start/stop/skip/completion semantics, not just decode frames.
- **Audio:** sound HLE per D4. The Sony Standard Kit sound stack registers no RPC
  server. It is driven by `sceSdRemote` commands through SDRDRV (0x80000701), plus
  pcm_mixer (0x123456, PCMPLAY). So the HLE is three things:
  - the sdremote command protocol,
  - SK hsynth/MIDI semantics over an SPU2-style mixer,
  - pcm_mixer.
- **Movie layer override:** the game's own movie code drives the IPU and DMA
  channels 3 and 4 directly and installs its own handlers. The movie service replaces
  that layer, not just `sceMpeg*`.
- **Gate:** a scripted input run goes cold boot → new game → first town → first
  battle → save → reload, with no stubs hit and audio playing.

### P5 — Whole game

- Bring up every overlay and every area. Run the factory (FACTORY), Insectron (INSECT)
  and menu (INSMENU/NORMAL) paths.
- Build a regression corpus of recorded input runs with state-trace checkpoints, run on
  every change.
- De-emulation track (D9), run alongside bring-up from now on, not after it: native
  renderer, native audio engine, native file/movie/pad services, native threading and
  timing. See "Native end state".
- **Gate:** a full playthrough is possible on the native build, and the regression
  corpus passes.

### P6 — PC features

The features players expect from modern PS2/N64-era source ports (Ship of Harkinian,
Zelda 64 Recompiled, OpenGOAL). Background research:
`private/pc-port-research-01a116f0/pc-experience/PC-EXPERIENCE-AND-MODDING.md`.

Ground rules:

- **One settings registry** (typed, with defaults and validation) drives the in-game
  settings menu, the config file and the command line, so they can't disagree. Settings
  that need a restart say so; display changes revert after a timeout unless confirmed.
- **An "Original" preset** reproduces the PS2 look and behaviour exactly (native
  resolution, 4:3, original frame rate, original filtering). It is what the
  verification runs use. Every enhancement is a toggle on top of it.
- **No enhancement changes game logic** unless it is explicitly labelled a gameplay
  option. The state-trace corpus must pass with every graphics, audio and input option.
- The settings registry, input-action layer and display basics are built in P4, so the
  menu grows as features land. P6 is where the full set is finished.

**Graphics settings**

- Display: windowed (resizable), borderless fullscreen, exclusive fullscreen, monitor
  selection, VSync, frame cap / uncapped (see "Unlocked frame rate").
- Internal resolution scale (1x–8x or match window), with fonts and 2D UI rendered sharp
  at the higher scale.
- Aspect ratio: 4:3, 16:9, 16:10, ultrawide. This means widened projection and culling,
  HUD and menu anchoring, and cutscene framing, not just a stretched image. Movies keep
  their aspect (pillarboxed) by default.
- Anti-aliasing (MSAA/SSAA, and a post-process option), anisotropic filtering, and
  texture filtering (original, bilinear, nearest).
- Toggles for screen effects: bloom, depth of field, motion blur and other full-screen
  passes; each can be original, enhanced (full resolution) or off.
- Draw distance / LOD bias and shadow resolution, where the engine allows it.
- Brightness/gamma, and optional output filters (sharpening, CRT/scanline).
- Texture replacement packs (HD textures) through the asset override layer (P7 mods),
  with a dump tool for texture authors.
- **Ray tracing (USER 2026-10-18; after the D9 native end state and the P5 whole-game gate,
  never before).** An optional `graphics.raytracing` mode (off in the Original preset, and
  never a requirement): ray-traced shadows, ambient occlusion and reflections, perhaps
  global illumination later, layered on the native renderer. Prerequisites: the native
  renderer owns every draw (no GS/VU1 fallback), so the scene's meshes and transforms are
  known on the host; the world, character and effect geometry can be put into acceleration
  structures, rebuilt or refit per frame for skinned meshes; materials can be classified
  (opaque, alpha-tested, additive effects, which should stay raster). Backend: D3D12 DXR
  or Vulkan RT, behind a capability check, with the raster path as the fallback. Lighting
  must stay true to the art (the PS2 lighting is mostly baked into vertex colours and
  textures), so start with shadows and AO as toggles, each compared against the Original
  look. No game logic change; the state-trace gate holds with it on.

**Controls**

- Input actions independent of PS2 buttons, with an adapter that feeds the game its
  original pad report. Keyboard, mouse and gamepad rebinding, with several bindings per
  action, in the settings menu.
- Analog deadzones, sensitivity, inversion per axis, and real mouse camera control (not
  just a mouse mapped onto the stick; deterministic: per-tick deltas latched at PadUpdate
  and recorded in input scripts, docs/INPUT.md). A keyboard walk modifier; an optional
  compensation for the game's own stick dead zone (a gameplay option). The US build never
  vibrates, so rumble would be a new optional feature.
- Gamepad hotplug and switching devices mid-play; button prompts that match the active
  device (PlayStation, Xbox, Nintendo, keyboard); full controller navigation of all
  menus, including on handheld PCs such as the Steam Deck.
- An audit of pressure-sensitive (analog) button use in the original controls: done
  (docs/CONTROLS-AUDIT.md; the game reads no pressure).

**Audio**

- Separate music, effects, voice and movie volumes; output device selection and
  hot-switching; option to keep playing audio when the window is unfocused.

**Saves and quality of life**

- Named save slots with metadata, backups and crash-safe writes; optional import of
  PCSX2 memory-card saves.
- Fast loading (no simulated disc latency). No cutscene-skip setting: the game already
  skips event scenes from the Start menu ("Skip"), confirmed by the user 2026-10-13.
  A skip for FMV movies is only worth adding if the retail game has none.
- Optional quality-of-life toggles that change pacing (text speed, battle speed-up) are
  labelled as gameplay options and kept off in the Original preset.

**Accessibility**

- Subtitle and UI scale, reduced camera shake and flashing, colour-blind-friendly
  markers where feasible, and remapped prompts throughout.

- **Gate:** the regression corpus gives identical logic results with the Original
  preset and with every non-gameplay option turned on. The frame-rate gate holds (see
  "Unlocked frame rate"). Every setting can be changed from the in-game menu with
  keyboard alone and with a gamepad alone.

### P7 — x64, other platforms, modding

- **x64.** Use the shared headers and real types (from the `main-headers` work) to
  replace `s32`-held pointers in game structs. Asset loaders that relocate in place need
  host-side relocation. Gate: the regression corpus passes on x64.
  *Census + plan 2026-10-25: [docs/X64-PLAN.md](docs/X64-PLAN.md).* It recommends instead
  "x64 with a 32-bit game address space": a `/LARGEADDRESSAWARE:NO` low-base exe (every
  address < 2 GB, measured), a `ptr32` stage (`T * __ptr32`) for pointers in game memory,
  and datareloc ADDR32 words. Retail layouts, assets, saves and save states stay as they
  are. Estimate 8.5-12.5 lane-days, against 40-80+ for true 64-bit pointers. Scripts:
  `tools/census/x64_*.py`.
  *2026-10-25 (evening): strategy A committed (USER) and under way*: an x64 build exists
  (`tools/build.ps1 -Arch x64`, `tools/x64/derive.py`), links, passes its link / runtime
  gates and runs the golden route with the i686 run hash (night: to field 24,823 after the
  address-space fence; audio hash open from 24,824); progress and gates in X64-PLAN.md section 0.
- Linux and macOS builds.
- A modding API, building on the asset/mod-profile system already in `pc-assets`.

## Verification

The project's main advantage: **the same source compiles to a byte-identical PS2 build.**
That gives a reference for every behaviour.

- **State-trace lockstep.** Run PCSX2 with scripted input and a fixed boot. Each virtual
  frame, hash the key game-state regions (task registry, party/battle structs, RNG,
  camera). The port records the same hashes from the same input. The first frame that
  differs localises the bug. This needs determinism from both sides: same VBlank count
  per logic frame, same RNG, and file loads that complete in a fixed number of frames.
- **Function-level differential tests.** For a suspect function, capture its inputs and
  the memory it touches in PCSX2 (or a non-matching instrumented PS2 build of the same
  source), replay them on the host build, and compare the memory it writes.
- **Graphics.** Compare GS dumps for the GS backend. Capture VIF/VU input and GIF output
  separately to test the VU1 interpreter and each native microprogram.
- **Arming.** Every comparison tool gets a deliberate-fault control (a wrong offset, a
  swapped callback) that must fail. Same rule as the matching project.

## Known hazards (checklist for P1/P2)

- **Integer divide by zero.** On MIPS it doesn't trap; on x86 it does. Route `/` and `%`
  on non-constant divisors through a checked helper, or catch the trap. Census the sites.
- **Uninitialised reads.** Some matching drafts deliberately pass uninitialised locals.
  Audit with `-Wuninitialized` and MSan on Linux.
- **Under- and over-argued calls.** These are harmless on MIPS registers and undefined
  under cdecl. Transform 2 handles them.
- **EE float behaviour.** The EE FPU has no denormals, NaN or Inf, and clamps instead.
  Set FTZ/DAZ. Add clamping only where traces show a difference. (2026-10-24: game code runs
  with round toward zero + FTZ + DAZ by default and the retail float libm, docs/BRINGUP.md item 3.)
- **Timing-dependent code.** The recomp found wall-clock-sensitive branches and load
  races. Fixed virtual time in P2 avoids them; the trace comparison catches the rest.
- **128-bit types and MMI.** `u128`, `lq`/`sq` and the MMI intrinsics need a struct or
  SSE type with the same layout.
- **Static constructor order across overlays,** and overlay BSS lifetime.
- **Addresses typed as floats in data.** 17 `.sdata` words that data2c typed as `f32`
  are really code or data addresses. For example, `D_0047FA00 = 5.08e-39f` is the bit
  pattern of `McGetInfoStep_375640`. They need re-typing in data2c or ingest, or FTZ
  will flush them to zero.
- **Return-type mismatch between a dummy virtual and its implementation.** An `f32` vs
  `s32` mismatch breaks the i686 return convention. Screen every vtable slot against its
  implementation's definition.
- **Class `operator new` that can return null.** Build with `-fcheck-new`.
- **The soft-double helpers** (`dpadd` and friends) become native `double`. Spot-check
  results with differential tests.

## Prior work: what to reuse

| Source | Reuse |
| --- | --- |
| Matching repo `decomp/` + `naming/` | The game source (via the clean snapshot). Its tooling (`vcensus.py`, `arity*.txt`, `data2c`) feeds the transforms. |
| `private/pc-port-research-01a116f0` | Portability census, host syntax probes, the detached-frame-rate audit, PC-experience/modding research. |
| `private/pc-assets-01a116f0` | Windows platform code (D3D11 device and readback, XInput, XAudio2, timer), TIM2/IM3 deswizzle, ISO importer, mod-profile loader, its SB2/event and asset-format documentation. Use it as a component library and reference, not as the architecture. |
| `private/main-headers-a94e7c21` | Shared struct layouts. Needed for P7 x64, useful earlier for overrides. |
| Memory notes from the retired `recomp/` | Protocol and format knowledge: L5 fileio packets, PADMAN, SKMIDI/MSIN audio, the MVI format and decrypt, VU1 MAC/clipping behaviour, GS wrap modes, EE thread/COP0 deadlocks. Documentation only; none of its code. |
| PCSX2 | The reference runtime for traces and GS dumps. Used as a tool only; none of its code (GPL, see D7). |
| Play! (BSD-2-clause) | Reference and vendorable code for the VU interpreter, GS renderer, SPU2 and IOP HLE, with attribution (D7). |

## First concrete steps (while the clean snapshot is being prepared)

1. Create the repo skeleton, toolchain files and an empty `ingest.py` with the snapshot
   hash as a parameter.
2. Write the censuses (P0) against the current `naming` tree, so they're ready to re-run
   on the snapshot.
3. Settle the mwcc vtable layout with a two-file probe compiled by mwcc, then by clang.
4. Build the PCSX2 trace harness (scripted input + per-frame state hashing). Both P2 and
   everything after it are gated on it.
5. Write `rg-extract`'s hash check and filesystem unpack (D8).
6. Add `LICENSE` (CC0 1.0), `THIRD_PARTY_NOTICES.md` and the README license note (D7).
