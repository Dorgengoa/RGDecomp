# tools/trace: PCSX2 reference-trace harness (prototype)

License: CC0 1.0, like the rest of the port's own code. PCSX2 (GPL) is used as
an external program only (PLAN.md D7). No PCSX2 code is copied here. The PINE
client (`pine.py`) is written from the public protocol description. Anything
else we know about PCSX2 internals (the savestate block layout, the `cpuRegs`
field offsets) was observed from its output files and process memory, not
read from its source.

This is plan step 4, the PCSX2 side of the **state-trace lockstep** in
PLAN.md "Verification". The harness boots the game in an isolated portable
PCSX2 and, at each sampled VBlank, hashes the EE/IOP memory regions listed in a
config file. Most of those regions are named game variables. It feeds scripted
pad input deterministically, and it compares two traces down to the first
divergent frame and the variables that differ there. A golden reference trace
from power-on to the first player-controlled battle is in `goldens/`.

**Port runs need not start at power-on:** `python tools/fixtures/run_from.py
battle --run 300` loads a save state of the golden route at a milestone (title
menu field 1500, first field 8000, first battle 23000) into the same build and
runs from there (RG_TRACE_* / RG_TIMING work from the loaded field on).
docs/TEST-FIXTURES.md has the commands and limits.

## Files

| file | what |
|---|---|
| `emu.py` | portable PCSX2 setup, ini generation, launch/stop (by PID), fresh memory card, savestate snapshots, `FrameClock` (EE cycle -> VBlank index) |
| `live.py` | fast snapshots: freezes PCSX2's CPU thread at a vsync and reads RAM with ReadProcessMemory (Windows); window screenshots |
| `pine.py` | PINE IPC client (batched reads/writes, savestate, status) |
| `input.py` | deterministic scripted input: a guest-side input table plus a hook in the game's pad decoder; `#!stick` lines (docs/INPUT.md "Scripted sticks") add a stick table and a longer trampoline (only for scripts that have them) |
| `stickprobe.py` | retail stick probe: load a PCSX2 save state, patch the input tables (buttons + `#!stick`, `--rel` = keys relative to the patch VBlank), log `--watch` ranges per VBlank (JSONL) and `--shot` window screenshots (`--renderer 13` = software, the null renderer 11 gives black shots) |
| `cardboot.py` | boot a game-save card (a port card folder, exported to `.ps2` with its ECC rewritten in mcman's bit order, or a `.ps2`) through CONTINUE and screenshot event-anchored milestones (plans `lib`, `factory`; docs/TEST-FIXTURES.md "Retail comparison") |
| `trace.py` | `run` (produce a trace) and `compare` (first divergent frame + named symbols) |
| `symbols.spec` | hand-picked game-state symbols with the evidence for each |
| `gen_regions.py` | `symbols.spec` -> `regions_symbols.cfg` (sizes from the decomp's symbol boundaries) |
| `regions_symbols.cfg` | generated: one region per symbol (`sym:<Name>`) |
| `regions.cfg` | default set: coarse 1 MB chunks, IOP, scratchpad + `include regions_symbols.cfg` |
| `regions_golden.cfg` | goldens' set: all symbols + 4 MB chunks + overlay arena (keeps TSVs small) |
| `pcsx2_portable.ini` | template for the portable copy's `PCSX2.ini`; every setting is there for isolation or determinism |
| `goldens/newgame_battle.{input.txt,tsv}` | golden input script and reference trace (power-on -> first battle) |
| `examples/start_cross.txt` | small example input script |
| `probe.py` | probe runs: guest call-logging trampolines, watched memory per vsync, experiments, savestates, VU frame snapshots (docs/VALIDATION.md) |
| `probe_exp.py` | in-guest experiments run by `probe.py --exp` (`kern`: kernel semantics; `cdlayer`: layer-1 CDVD) |
| `mips.py` | tiny R5900 assembler used for the trampolines and experiments |
| `vucap.py` | VIFCAP1 builder: pairs consecutive-vsync VU/VIF1 snapshots around each VIF1 kick |
| `timing.py` | reference timing contract: `probe.py --hooks timing` JSONL -> per-frame `ticks` TSV, `events`, `milestones`, summary; `align` compares two milestone files (docs/TIMING-REFERENCE.md). Also reads the port's record (`RG_TIMING`, src/trace/timing.c; `--map` names wrapper call sites); `align --nowrap` compares a port run without wrapped game functions (docs/TIMING-LOCKSTEP.md) |
| `gen_timing_sites.py`, `timing_sites.tsv` | the timing record's site table, generated from `probe.py`'s `build_timing_hooks` (ids, game functions, dump specs): the port's `rg_timing_sites.h` (built) and the future `probe_wrap` stage's input. `--check` (CTest `trace.timing_sites_sync`) fails on drift |
| `audiocap.py` | reference **audio**: PCSX2's SDL audio backend into SDL3's `disk` driver (raw s16 48 kHz), with a PINE poll of game VBlank, movie-decoder bytes and file size for alignment; optional `--input` (docs/SOUND.md "Validation") |
| `port_trace.py` | **port side**: run the port exe headless (`RG_TRACE_*`) and compare against a golden (docs/TRACE-PORT.md) |
| `gen_port_symtab.py` | **port side**: regions -> generated `&D_xxxxxxxx` symbol table for the port recorder |
| `port_regions.cfg` | **port side**: pointer slots and the curated exclude/pending lists for port compares |

## Setup

```
python tools/trace/emu.py setup        # once; --force to recopy
python tools/trace/gen_regions.py      # after editing symbols.spec
```

- Copies `C:\Program Files\PCSX2` (v2.6.3) to `.tools/pcsx2/` (gitignored) and
  creates `portable.txt` next to the exe. Verified on 2.6.3: the log reports
  `DataRoot Directory: .tools\pcsx2`, and inis, sstates, memcards,
  logs and cache all stay there. The user's `Documents\PCSX2` is never written.
- **BIOS**: the BIOS folder and file are read from the user's own
  `Documents\PCSX2\inis\PCSX2.ini` (`bios\PS2_BIOS`, `ps2-0230a-20080220.bin`).
  The portable copy points at that folder; no BIOS file is copied. A symlink
  needs admin rights here, and a hardlink can't cross volumes. Caveat: PCSX2
  keeps `<bios>.nvm`/`.mec` next to the BIOS and could write them. Each run
  hashes them before and after and warns if they changed. No run so far
  changed them.
- PINE uses slot 28012, so it can't collide with the user's PCSX2 on 28011.
  Parallel runs need distinct `--slot` values. Their `--out` names must also
  differ, because the trace tag names the memory card.
- Verified CLI flags (from `-help` in 2.6.3): `-batch -nogui -fastboot
  -logfile <f> -statefile <f> -- <iso>`. `-nogui` implies batch. Input
  recording has no flag. Caution: an unknown flag (e.g. `--version`) on the
  *installed* exe opens the GUI with the user's settings. Always launch the
  portable copy through `emu.py`.

## Usage

```
# reproduce the golden (about 15 min) and check it
python tools/trace/trace.py run --memcard --speed 0.5 --idle-ms 3 --every 10 --emit-every 60 \
    --stop-vbl 25040 --frames 40000 --regions tools/trace/regions_golden.cfg \
    --input tools/trace/goldens/newgame_battle.input.txt --out .tools/run/mine.tsv
python tools/trace/trace.py compare tools/trace/goldens/newgame_battle.tsv .tools/run/mine.tsv

# short boot trace, every vsync, all regions
python tools/trace/trace.py run --frames 600 --out .tools/run/a.tsv
```

`run` options:
- Core: `--mode live|state` (default live), `--speed` (PCSX2 NominalScalar;
  default 0.1 live, 0.02 state), `--renderer` (11 Null default, 13 SW),
  `--regions`, `--input`, `--memcard` (fresh 8 MB card in slot 1, recreated
  every run), `--set Section/Key=Value` (repeatable ini override, recorded in
  the header), `--slot`, `--no-hook`.
- Cadence: `--every N` samples only VBlanks that are multiples of N.
  `--emit-every N` writes rows only for frames that are multiples of N;
  sampling stays at `--every`, which keeps the frame count exact. `--idle-ms`
  is the CPU-thread idle time that counts as "asleep at vsync" (use 3 at speed
  0.5 or more).
- Stopping: `--frames`, `--stop-vbl V`, or `--stop-mode M --stop-after F`
  (stop F frames after game mode M is first seen).
- Debug aids: `--shot-every N --shot-from F` saves window screenshots (needs
  `--renderer 13`) to `.tools/run/shots/<tag>/`, which is how the golden input
  script was written. `--status-every` prints a status line with vbl,
  main-loop mode, overlay, game mode, title vars and the pad word.

`compare A B [--key frame|vbl] [--only REGEX] [--ignore REGEX]` prints:
- the first divergent key, its game vbl, and the last matching key;
- the **symbols** (`sym:*`) that differ there, then the other regions;
- each region's first divergent key.

Only regions present in both traces are judged. `--key vbl` matches samples by
the game's own VBlank counter instead of the power-on frame index. Use it for
PCSX2-vs-port comparisons: the port has no BIOS boot, so no power-on index.
`--only '^sym:'` restricts the comparison to named variables.

Trace TSV: `frame <TAB> region <TAB> hash`.
- `frame` is the absolute VBlank index since power-on (`emu.FrameClock`).
- `hash` is the first 64 bits of BLAKE2b.
- Pseudo-regions: `@cycle` is the u32 EE cycle at the vsync; `@vbl` is the
  game's VBlank counter `[0x004810C4]`.
- `#` lines are metadata: versions, settings, input script, `overlay
  <frame> <id> <file>` and `gamemode-change <frame> <mode>` events,
  frame-vbl offset notes, and the stop reason.

Region files: `space name start end [chunk]`, `space name *PTR[+OFF] size`
(follow a u32 pointer stored in the same snapshot), or `include <file>`. The
spaces are `ee` (32 MB), `iop` (2 MB) and `spr` (16 KB scratchpad, offsets
0..0x4000).

Input script: `first_vbl last_vbl BUTTON[+BUTTON]` per line, inclusive, in
game VBlank counter units. The counter starts about 280 vsyncs after power-on.
Buttons: L2 R2 L1 R1 TRIANGLE CIRCLE CROSS SQUARE SELECT L3 R3 START UP RIGHT
DOWN LEFT.

## Symbol-level regions: how they were chosen

There is no data-symbol map yet: `main.symbols.txt` holds functions plus two
data names. So `symbols.spec` (42 entries) is hand-picked. The evidence comes
from:
- the naming database (`config/names.txt` at naming commit 2efa6b43, ingested
  into `game/`), whose comments name the globals each function touches
  ("task table D_004D7FA0", "party D_00483820", "heaps D_004BB890/D_004BB8F0",
  ...);
- the matching decomp sources: `Rand_133710` gives the RNG state at
  `*(_impure_ptr 0x00449858) + 0xA8`; `OverlayLoad_1c3210` gives the overlay
  id `D_0047E254`; `MainLoop_1c2c10` gives the main-loop mode `D_0047E224`;
  `PadReadData_184df0` gives the pad word;
- the title-overlay notes for the title variables.

Each line in `symbols.spec` carries its evidence. Sizes are explicit where a
struct size is known (CGameScene 0xB570, 6 cameras x 0x2F0, pads 0x270,
CActionManager 0x40, mgCMemory 0x60, ...). Otherwise `auto` means the
distance to the next `D_` address that any decomp source references (8,928 of
them under `game/src`), capped at 0x1000. Pointer globals are hashed twice: as
the pointer value (`PartyPtr`) and dereferenced (`Party`, `RandState`).

Coverage:

| group | symbols |
|---|---|
| frame / system | VblankCount, VblankWaitFlag, GameMgrPtr, SysMode, SysModeNext, LoadedOverlayId, DataSetLang |
| game flow | GameModeStack, GameModePhaseStack (16-deep; [0] is the current mode, 6 field, 7 battle, 11 event) |
| RNG | RandState |
| input | Pad0, Pad1 |
| tasks | TaskTable, TaskStateDepth |
| game data | GameData, GameDataPtr, PartyPtr, Party, CharaListHost, ActionMgr, SkillTimers, SkillSlots |
| scene / camera / events | GameScene, Camera0-5, EventScenePtr, EventContext, SystemVm, MenuStateMachine, TimerAccumA/B |
| heaps | HeapA, HeapB (mgCMemory headers), HeapNpcData |
| title | TitleMenuSel, TitleMenuOpened, TitleCounter, SaveExists |

Arming check: a golden copy with one planted wrong hash (`sym:RandState` at
frame 12000) makes `compare` report exactly that frame and `symbols
differing: RandState`.

## Long run: power-on -> title -> NEW GAME -> first battle

Script: `goldens/newgame_battle.input.txt`, written by stepping with
screenshots. Timeline (from the golden; frame = power-on vsync,
vbl = game counter):

| frame | vbl | event |
|---|---|---|
| ~70-83 | 0 | BIOS / boot ELF |
| 300 | 20 | overlay 2 `TITLE.BIN` loaded (main-loop mode 1) |
| ~750 | ~470 | "Checking memory cards" (with an empty card: no dialog) |
| ~1900 | ~1620 | title menu open (NEW GAME / CONTINUE / OPTIONS, cursor on NEW GAME) |
| 2180 | 1900 | input: CROSS = NEW GAME |
| 2920 | 2640 | overlay 3 `NORMAL.BIN` loaded (main-loop mode 0, game mode -1) |
| 4150 | 3870 | game mode 11 (events: story screen, opening FMV, Salgin cutscenes; CROSS every 360 vbl advances dialogue) |
| ~24250 | ~23970 | game mode 7 briefly (battle set-up), then 11: "Basic Battle Controls" tutorial (3 pages) |
| 24730-24975 | 24450-24695 | input: START x3 (tutorial pages) |
| **24990** | **24710** | **game mode 7: battle under player control (first controllable frame)** |
| 25320 | 25040 | golden stops (`--stop-vbl 25040`) |

Cost: the golden run (Null renderer, speed 0.5, sample every 10th VBlank,
emit every 60th) takes about 14 min wall for 25,320 frames, roughly 29
emulated frames/s. It has 2,491 samples and 325 emitted frames, and the TSV
is 0.6 MB. An exploratory run with the SW renderer and screenshots at the
same settings took about 17 min.

Getting there needed three things:
- **A memory card.** With no card the game shows "No memory card ... Begin
  the game anyway? Yes / No" (cursor on No). Scripted LEFT/CROSS reached the
  game's pad word (verified per frame) but the dialog never reacted; the
  reason is not found. `--memcard` inserts a fresh card that PCSX2 creates
  unformatted. The game then skips the dialog. The fresh card is
  byte-identical every run (SHA-256 47EBE237...).
- **Dense sampling.** See "Frame numbering" below.
- **Installing the input hook with the EE frozen.** See "Determinism" below.

Not reached / not tried: the first *field* (game mode 6) comes after this
battle. The battle itself needs real play (CROSS-mashing alone takes Jaster
to 6/80 HP within ~1,500 frames), so a longer golden needs a battle script.

## Frame-accurate sampling: what was chosen and why

PINE (opcodes 0-15) has memory read/write, savestate save/load, status and
title, but **no pause or frame step**. Options investigated:

| option | verdict |
|---|---|
| PINE reads while running | **Torn.** The PINE thread reads while the EE runs. 1 MB takes ~50 ms, so 32 MB takes ~1.6 s, about 100 frames at full speed. |
| Frame-advance / pause hotkeys | They exist (`FrameAdvance`, `TogglePause`), but only as key or pad bindings in the focused GUI window. Not scriptable from `-nogui`. Rejected. |
| Game's own frame counter `[0x004810C4]` | A **label** only. It doesn't stop the EE. It is 0 for the first ~280 vsyncs, and near the battle load it can lag the vsync count by 1-2 (interrupt latency). Recorded as `@vbl`, and the `compare --key vbl` key. |
| **Savestate per sample** (`--mode state`) | Consistent. The save runs on PCSX2's CPU thread inside vsync handling with the EE/IOP stopped. The `.p2s` zip holds `eeMemory.bin`, `iopMemory.bin`, `Scratchpad.bin`, and `cpuRegs.cycle` in `PCSX2 Internal Structures.dat` (tag `cpuRegs` + 32 + 960). Too slow here: 42 MB written per sample, 0.1-9 s on the busy B: HDD, once more than 30 s. Kept as the authoritative cross-check. |
| **Freeze at vsync + in-process read** (`--mode live`, chosen) | At NominalScalar < 1 the CPU thread (EE, IOP and DMA all run on it) spends part of each frame asleep in the frame limiter, inside vsync handling, the same point where savestates are taken. `live.py` watches the thread's cycle count (`QueryThreadCycleTime`). When it stops moving, it `SuspendThread`s the thread, confirms it didn't move, and reads `cpuRegs.cycle`. It accepts only if that cycle is on the vsync grid. Then it reads EE/IOP RAM with `ReadProcessMemory` (addresses from PCSX2's log), reads the scratchpad over PINE, re-checks, and resumes. |

`cpuRegs` is found by scanning PCSX2's writable image memory for the EE COP0
PRId/Config pair (0x2E20, 0x73443) at the observed offset, with GPR[0] = 0,
retried for up to 10 s after VM start. **Equivalence check**: a state-mode
trace and a live-mode trace of the same boot were identical on all 152
common frames, including IOP and scratchpad.

### Frame numbering (FrameClock)

- **Power-on grid.** Vsync k is at cycle k * 4,915,200 (the BIOS runs at
  60 Hz) up to frame 109. The game then switches to NTSC: frame 110 is at
  0x203A3A1F (one odd 4,930,071-cycle frame), and later frames are 4,920,120
  apart. `first_frame()` uses this grid, so a run whose first sample comes
  late still numbers frames the same way.
- **Clean intervals.** Each sample must lie a clean number of periods from
  the last accepted one, within 2,000 cycles; vsync samples land within
  about ±80. Video-mode switches make odd frames, so a sample that is only
  roughly on the grid is held as pending and accepted when the next interval
  from it is clean. Mid-frame idles (CD or GS waits) never confirm and are
  dropped.
- **u32 wraps.** `cpuRegs.cycle` is u32 and wraps every 873 frames.
  `live.py` polls it every millisecond to unwrap. The host can still stall
  for tens of seconds on a slow-disk flush and miss wraps; that happened in
  one run and lost 2 x 873 frames. So the wrap count between two samples is
  now pinned by the game's VBlank counter delta (873 frames is far beyond its
  ±2 jitter).
- **Sparse sampling breaks numbering.** At speed 1.0 the Null-renderer EE
  rarely idles during FMVs (one run went 6,000 frames without a sample). Over
  gaps that long, odd frames add up and numbering drifts. Keep `--every` at
  10 or less and speed 0.5 or less, and thin the output with `--emit-every`
  instead.
- Coverage: one instance at speed 0.1 sampled 897 of 902 vsyncs. With 2-3
  instances on a loaded host, 40-85%.

## Scripted input

| option | verdict |
|---|---|
| Input recording `.p2m2` | Exists in 2.6.3 (Input Recording menu: New/Play/Stop, `*.p2m2`, needs `EnableRecordingTools`). **GUI only**: no CLI flag, and playback starts from a dialog. Not used. |
| PINE writes to the pad DMA buffer (0x4B2A80) or the button word (0x4B2574) | Racy: a host-timed write lands on a host-timed frame. Rejected. |
| The game's own key capture/replay | `PadUpdate_1843a0` has record (mode 1) and playback (mode 2) of 6-byte pad records at 0x3000000, which is devkit RAM beyond 32 MB, and `MainLoop_1c2c10` reseeds the RNG (`Srand(0x270F)`) when `D_00481550` is set. Retail-unusable as is; noted for the port. |
| **Guest input table + pad-decoder hook** (chosen, `input.py`) | Deterministic by construction. Details below. |

How the hook works:
- A table of u16 button words, one per game VBlank, goes into EE RAM that is
  unused after boot (`0x000F0100`, 32,636 VBlanks). A 17-word trampoline goes
  at `0x000F0000`. `PadReadData_184df0` is patched at `0x184E58`: `j tramp`
  with the original `xori` in the delay slot.
- For the port-0 pad object (`$s1 == 0x004B2574`), the trampoline ORs
  `table[[0x004810C4]]` into the decoded active-high button word.
- The table is always full length and zero padded, so every run executes the
  same instructions. The hook is installed in **every** run, with an empty
  table when there is no `--input`.
- **The writes are made while the CPU thread is frozen at a vsync**, at the
  first 60 Hz-grid idle after the ELF appears (~vsync 28), via
  `LiveSampler.frozen_call`. See "Determinism" for why.
- The port can mirror the hook exactly: OR `table[vbl]` into the pad word on
  the same game VBlank.
- `verify()` checks the hook and trampoline in every snapshot.
- Limits: `ram@00100000` contains the patched code bytes. Port 1, sticks and
  pressure are not scripted.

## Determinism

Short runs (600 VBlanks from power-on):

| runs compared | result |
|---|---|
| same settings, two runs in parallel, no hook | identical, 516 common frames, all regions incl. IOP and scratchpad |
| speed 0.1 vs 0.2 | identical (276 common) |
| hooked no input x2; hooked with input x2 | identical (88 / 505 common) |
| no input vs input (arming) | identical until the first input the game reads (CROSS at vbl 205), then `pad0` and RAM diverge in that frame |
| savestate mode vs live mode | identical (152 common) |
| SW (13) vs Null (11) renderer | identical (152 common) |
| MTVU on | identical in this window; kept off anyway |
| **host RTC** | **diverges at frame 109** (IOP RAM). Fix: fixed RTC (template) |
| unhooked vs hooked | diverge at frame 289: a few extra EE instructions per pad poll move IOP RAM and EE chunks 0x400000/0x1C00000/0x1D00000/0x1F00000 (EE-timing-sensitive state) |

Long runs (power-on -> first battle, 25,320 frames):

| runs compared | result |
|---|---|
| **g5 vs g6**: hook installed frozen, two runs in parallel | **identical on all 266 common emitted frames (120..25320)**, all 42 symbols + 4 MB chunks + overlay. Identical game-mode/overlay timelines, no frame-vbl offset change |
| golden (g5) vs g6 by `--key vbl --only '^sym:'` | identical (263 common) |
| g7, g9 (2026-10-12) vs golden | **identical** (270 and 282 common frames through 25320; g7 vs g9 identical on 307) |
| g8 (2026-10-12) vs golden | diverged at frame 1020 (vsync cycle, then EE chunks; symbols from vbl 3860). A second PCSX2 instance was launched at that moment; see "Parallel runs" below and docs/VALIDATION.md |
| earlier runs with the hook written while the EE ran (x7, x8 SW; g1, g3, g4 Null) | **not reproducible**. g3's sample cycles drifted by 12-79 cycles from frame 1,800, and its RandState/GameScene diverged at vbl 9,440. x7 vs x8 diverged at vbl 23,047 (stack RAM), then 24,116 (VblankWaitFlag, IOP). g4 vs g5 diverged at vbl ~24,080 (RandState, Party, Camera1, SkillTimers, VblankCount). Everything that did match matched g5 up to vbl ~22,300 |

The likely cause: PINE wrote the hook into a code page while the EE thread
was running. PCSX2 then invalidated recompiled blocks from the PINE thread at
a host-timing-dependent moment. The visible symptom is vsync-handling cycles
that differ by a few dozen cycles. With the writes made while the EE is
frozen, the two runs since then matched over the whole 25k frames. Since then 4 of 5
long runs matched the golden over all 25k frames (g5, g6, g7, g9); the fifth
(g8) diverged early when another instance was launched (2026-10-12, see below).

**Parallel runs.** All portable instances share `.tools/pcsx2/inis/PCSX2.ini`
(rewritten by every launch with its card name and PINE slot) and the shader
cache. One run (g8) diverged exactly when another instance started during its
memory-card phase. Launch reference runs together and start nothing else while
any of them is before vbl ~3,000.

Settings that make it deterministic, all in the template:
- fixed RTC
- MTVU off
- GameDB code patches off (SCUS-97490 patches EE 0x124898; RAM keeps the
  retail word)
- no host input sources
- `-fastboot`
- with `--memcard`, a fresh card per run

## Limits / next steps

- Live mode is Windows-only and tied to PCSX2 2.6.3 internals: the `cpuRegs`
  signature and offsets, and the "EE Main Memory @" log line. Pin the PCSX2
  version, and re-run the state-vs-live equivalence check after any upgrade.
  The power-on grid constants in `emu.py` are specific to this BIOS and game.
- The game's VBlank counter can lag the vsync count by 1-2 around the battle
  load. For port lockstep, `--key vbl` is the natural key, but expect ±1-frame
  alignment issues there.
- The symbols are hand-picked from naming comments, not from a data-symbol
  map. Several sizes are `auto` (to the next referenced symbol), so they may
  include neighbours.
- EE-timing-sensitive state (stacks near 0x1F00000, IOP RAM, parts of 0x400000)
  won't match a port that has no EE cycle timing. Compare symbols
  (`--only '^sym:'`) for lockstep.
- The no-card dialog ignores scripted input (unexplained); use `--memcard`.
- Not reached: the first field (game mode 6), which is after the first
  battle. That needs a battle input script.
- Savestate checkpoints (resume from mid-run) are not implemented. Live
  snapshots are disk-free, and a full golden run takes ~15 min.
- Run artifacts go to `.tools/run/` (traces, `*.emulog.txt`, PID files, shots).
  PCSX2 processes are stopped by PID only.

## Probe runs (probe.py)

`trace.py` answers "what is in memory at this vsync". `probe.py` answers
"what did the game call, with which arguments, and what came back", which
docs/VALIDATION.md needed. It patches small trampolines into the game's code
(written over PINE with the CPU thread frozen, in the same frozen call as
the input hook) that append 64-byte records to a ring in EE RAM that is zero
after boot (map in `probe.py`'s docstring). The harness drains the ring at
each sampled vsync. Hook sets (`--hooks`):

| set | what |
|---|---|
| `kernel` | libkernl syscall stubs for threads, semaphore create/delete, INTC/DMAC handlers, alarms: args + kernel return value |
| `sema` | Signal/Wait/Poll/ReferSema (very high rate: sample with `--every` 5 or less) |
| `cd` | `sceCdRead` args + mode, `sceCdLayerSearchFile` name + returned `sceCdlFILE`, `sceCdReadDvdDualInfo` |
| `sif` | `sceSifCallRpc` entry |
| `pad` | `scePadRead` (return = bytes copied + the caller's buffer), `scePadInfoMode`/`InfoAct` |
| `movie` | `MovieVblankHandler`, `MovieFrameQueueSendNext` (+ audio decoder fields) |
| `vif1` | `Vif1DmaStart_15e070` (the frame's VIF1 chain address, COP0 Count) |
| `sm` | `StateMachineSetState_28ede0` (every UI/title state-machine transition) |
| `heap` | newlib malloc family + `sbrk` |
| `timing` | the frame-rate timing contract (docs/TIMING-REFERENCE.md): VBlank handler, frame-worker wakes, `GfxEndFrame` (raw T0/VU samples, stored feedback, flip bookkeeping, depth slot 0), `WaitVsyncCount`, scene time scale (+0x5E00..+0x5E14 before/after), `TaskTableRun` (+ restart flag), task-list changes, interval and scale-lock setters, game-mode push/pop, overlay loads, pad updates, pause requests, state machines, `sceCdRead`, movie open/close/draw. 21 sites, about 10 records per VBlank |

Dumps: a hook logs six words. Besides the fixed forms (`reg`/`abs`/`ptr`/`stk`
+ six consecutive words), `('words', [...])` takes six independent items:
`W_abs(addr)`, `W_ptr(addr, off...)` (pointer chain, null-checked),
`W_reg(r, off...)`, `W_stk(slot, off...)` (return hooks), `W_fpr(n)` (float
argument bits). `Hooks.leaf` hooks two-word `jr ra; insn` accessors, which
`entry` cannot relocate.

Other options: `--watch NAME:ADDR:SIZE` (hex dump per sample),
`--exp kern|cdlayer --exp-at VBL` (run an experiment once from the main
thread at `PadReadData_184df0`'s entry), `--locate-vu-at VBL` (one
savestate, then find VU memory and VU registers in PCSX2's process memory),
`--vucap-at VBL --vucap-frames N` (EE RAM + VU0/1 memory + VU registers +
VIF1/D1 registers over PINE at N consecutive vsyncs, saved to
`out/captures/raw/`), `--state-at VBL` (savestate while running). Output is
JSON lines. Probe runs change EE timing: they are not lockstep references.

Things learned building it:
- A PINE `save_state` issued while the CPU thread is frozen hangs PCSX2
  (the request blocks PINE until the CPU thread services it; observed twice).
  Savestates are only requested while running, and consecutive-vsync data is
  read live instead (`--vucap-at`).
- At speed 0.5 the CPU thread does not idle at every vsync (title: about one
  in two); consecutive-vsync windows need `--speed 0.15`.
- COP0 Count = EE cycle - ~234,100 (+-150) in these runs (read from a
  savestate's `cpuRegs`); `vucap.py build --count-offset` needs it.
- PCSX2 process layout (v2.6.3, observed): VU0 micro memory is at the
  start of the log's "VU0/1 On-Chip Memory" block, VU1 micro = VU0 micro + 0x2000, VU1 data =
  VU0 micro + 0x6000; the VU register files live in the exe's writable image
  (VU1's at VU0's + 0x600); EE hardware registers are read over PINE.
- Savestate `PCSX2 Internal Structures.dat` 'vuMicroRegs': VU0 VF[32] at tag +
  48, VI[32] as 16-byte slots at +0x200 (VI16 status, 17 MAC, 18 clip, 20 R,
  21 I, 22 Q, 23 P, 26 TPC), VU1's block 0x5B6 bytes after VU0's.

Analysis is ad hoc Python over the JSON lines; the results and the exact
commands are in docs/VALIDATION.md.

## Retail parity harness (tools/parity)

`tools/parity/parity.py` builds on probe.py (emit_log, W_ptr items, Hooks), input.py (the
guest table, here indexed by a game-frame counter) and live.py (ring drained from PCSX2 memory):
the port and retail sampled once per game frame at GfxEndFrame, first divergence per field.
See docs/TEST-FIXTURES.md "Retail parity".
