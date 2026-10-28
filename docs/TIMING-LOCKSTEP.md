# Port timing record and milestone-aligned lockstep

Design note for PLAN.md "Unlocked frame rate" step 1 (port half) and for the lockstep
comparison in "Verification". The PCSX2 half and the measurements are in
[TIMING-REFERENCE.md](TIMING-REFERENCE.md).

**State (2026-10-12).** The port's recorder (`src/trace/timing.c`, `RG_TIMING=path`)
is implemented with every source that needs no game-function wrapping, plus the C API
the wrappers will call and the generated site table. `timing.py build` reads a port
record and `timing.py align --nowrap` compares it with a PCSX2 capture ("First port
run" below). The `probe_wrap` ingest stage is **not written** (another lane owns
`tools/stages`); "The wrapper stage" below is its contract.

## Why vbl-keyed lockstep can't work

`trace.py compare --key vbl` assumes both sides reach the same state at the same game
VBlank. The port spends no virtual time on guest code (TRACE-PORT.md "Lag frames",
KERNEL.md `kcall_cycles` 0). Measured retail costs that the port does not reproduce:

| Where | Retail | Port today |
| --- | --- | --- |
| Title session init, `DataTableBubbleSort_368220` | first frame at vbl 539, first title state at 469 | state 1 at vbl 96 (BRINGUP.md) |
| Overlay loads | TITLE 7 vbl, NORMAL 25 vbl | CD model latency only |
| NORMAL's loading screen | 594 `loadscreen` frames, vbl 2,666..3,865 | as long as the CD model makes it |
| Lag frames | 10 main-loop frames with dvbl 3..32; each shifts the 2-VBlank grid's phase | none |
| Battle | every tick needs 1.26 fields of EE time on average | 0 |

After the first of these, every later state is shifted in VBlanks while the logic is
the same tick for tick. So lockstep has to key on **logic position**: which milestone,
and how many main-loop ticks since it.

## Port-side record: same schema, same tool

The port writes the JSONL schema `probe.py` writes, so `timing.py build` produces the
same `ticks`/`events`/`milestones` TSVs from either side and `timing.py align` compares
them.

```
{"t":"meta","hooks":["timing"],"sites":{...},"side":"port","input":...}
{"t":"r","seq":N,"k":"entry|ret","fn":"GfxEndFrame","vbl":V,"cnt":C,
 "a":[a0,a1,a2,a3],"v0":V0,"ra_name":"MainLoop_1c2c10","pair":P,"d":[w0..w5]}
```

| Field | Port source |
| --- | --- |
| `vbl` | `rg_trace_read_vbl()` (the game counter `D_004810C4` through the address map) |
| `cnt` | `(uint32_t)(2 * ps2k_now())`: EE-cycle units of the virtual clock. It moves only at waits, so per-tick `dcyc` shows the virtual schedule, not compute |
| `a`, `v0` | the wrapped function's arguments and result as u32; pointer arguments (the wrapper's `flags`) reverse-mapped to PS2 addresses (`rg_trace_ps2_addr`) so `sm=00948d90`-style keys match |
| `ra_rva` / `ra_name` | the caller. Wrappers pass `__builtin_return_address(0)`; the record holds its RVA (`ra_rva`) and `timing.py build --map rg-game.map` names it from the link map (`Syms.host_name`). Built-in synthetic records carry `ra_name` directly |
| `pair` | guest thread id << 8 \| call depth (built-in entry/return pairs: `0x80000000 \| n`); `timing.py` pairs entry/return by `(fn, pair)` (PCSX2 records pair by `sp`) |
| `d` | the same words as the PCSX2 dump specs (the generated table), read with `rg_trace_read`; pointer chains (`W_ptr`, `W_reg(r, 0x270, 0x24)`) follow host pointers through the reverse map, else raw if the page is readable, as TRACE-PORT.md "Pointers" does for derefs |
| `src` | port only: `mem` (synthesised from game memory), `ovl`, `sce`, `movie` (a built-in observer); absent on wrapper records |

### Running it

| Variable | Meaning |
| --- | --- |
| `RG_TIMING` | JSONL path; enables the record (or `rg_runtime_config.timing_out`). Read by `rg_trace_apply_env`, which the game and the demo already call; independent of `RG_TRACE_OUT` |
| `RG_TIMING_STOP_VBL` | request quit once the game vbl reaches V |
| `RG_TIMING_MEMTICKS=0` | no synthetic `GfxEndFrame` records |
| `RG_TIMING_PADREADS=0` | no `scePadRead` records |

With `RG_TIMING` set the input script (`--input`) is keyed by the game counter + 1, as
in traced runs (TRACE-PORT.md "Sample point"). Off, the cost is one `NULL` test per
observer call site and `if (rg_timing_on)` in each future wrapper.

```powershell
$env:RG_DATA = "data"; $env:RG_TIMING = "out\timing\port\RUN.jsonl"
build\timing-i686\rg-game.exe --headless --fields 6000 --input tools\trace\goldens\newgame_battle.input.txt
python tools\trace\timing.py build out\timing\port\RUN.jsonl --map build\timing-i686\rg-game.map
python tools\trace\timing.py align --nowrap out\timing\newgame_battle2.milestones.tsv out\timing\port\RUN.milestones.tsv
```

### Where each record comes from

| Record | PCSX2 hook | Port source today | With `probe_wrap` |
| --- | --- | --- | --- |
| `VblankStart` | handler entry, counter not yet incremented | kernel VBlank observer at VBLANK_START, before any game handler; the same six words. Port extra `x`: vsync-sema waits since the last VBlank (`vsw`) and the last waiting thread (`vst`), from the kernel trace hook | unchanged |
| `MemState` (port only) | none: `timing.py` derives the same view from hook records | at each VBlank, on change: `d` = interval and sync (`DrawCtx+0x270 -> +0x24/+0x28`), `GameModeStack[0]`, `GameModePhaseStack[0]`, `D_0047E254`, scene `+0x5E14` (lock \| suspend << 8); `a` = sysmode, pause step, task depth, scene multiplier `+0x5E0C` | kept (cheap; feeds `mem_*`) |
| `GfxEndFrame` | trampoline | **synthesised** (`"src":"mem"`) when the frame context's flip counter `+0xF00` moves, checked at each VBlank and before every other built-in record (so an event after a flip lands in the next tick, as on PCSX2). Words from the context (`T0`, VIF1 time = 0). Loop by thread: the last thread blocked on the vsync semaphore `D_0047DF18`; thread 1 is `MainLoop_1c2c10`, or `MoviePlayModal_267c60` while a movie is open outside TITLE (heuristic) | wrapper; the synthetic source switches itself off at the first wrapped call |
| `OverlayLoad` | trampoline | overlay manager observer (`rg_ovl_set_load_hook`, around `rg_ovl_load`): entry with the loader index, return | wrapper (observer silenced) |
| `sceCdRead` | libcdvd stub | SDK HLE observer (`sceCdHleSetReadHook`): lsn, sectors, buffer, pattern | unchanged (port code, not game code) |
| `MovieOpen` / `MovieShutdown` | trampolines | movie service observer (`rg_movie_g_set_hook`) at `rg_movie_g_open`/`_close`: no caller, plus `"path"` | wrappers (observer silenced) |
| `scePadRead` (port only) | (`pad` hook set) | SDK HLE observer (`scePadHleSetReadHook`): port, slot, bytes | unchanged |
| `TickWake`, `WaitVsync`, `SceneTimeScale`, `TaskTableRun`, `SetVsyncInterval`, `SetTimeScaleLocked/Suspended`, `GameModePush/Pop`, `PadUpdate`, `PauseRequest`, `StateMachineSetState`, `MovieDrawFrame`, `SoundSeqUpdate`, `TaskListChanged` | trampolines | not recorded (their effect on interval, game mode and lock shows in `MemState`) | wrappers |

The observers are one function pointer each in the owning module (overlay, libcdvd,
libpad, movie service); `rg_timing_attach` installs them, plus the kernel VBlank
observer and the kernel trace hook (`ps2k_set_trace_hook`, otherwise unused).

### The wrapper stage (contract; not written)

A table-driven ingest stage, like `spin` (SPIN.md): `tools/stages/probe_wrap.py` reads
`tools/trace/timing_sites.tsv`. That table is **generated** from `probe.py`'s
`build_timing_hooks` by `tools/trace/gen_timing_sites.py` (a recording stand-in for
`probe.Hooks`, no ELF), and CTest `trace.timing_sites_sync` fails when it is stale. The
same run writes `rg_timing_sites.h` into the build (`RG_TIMING_<Site>` ids = probe.py's
meta `sites` numbers, and the dump specs as data for `timing.c`), so the two sides
cannot drift.

`timing_sites.tsv` columns: `id`, `site` (record `fn`), `kind` (`entry`, `leaf`,
`entry_ret`, `ret` = log the return only), `addr`, `func` (the game function, e.g.
`GfxEndFrame_141c20`), `entry` / `ret` (word specs: `abs:ADDR+o..`, `arg:N+o..`,
`fpr:12`; informational for the stage, `timing.c` has them), `flags` (`skipzero=a0`).

For each row whose `func` is defined under `game/src` (not `sceCdRead_12a728`, which is
port code) the stage:

1. renames the definition `GfxEndFrame_141c20(` to `GfxEndFrame_141c20__rg_body(` (static);
2. appends a wrapper with the prototype from `game/PROTOS.tsv`:

```c
/* declared locally, as overrides declare port functions (src/trace/rg_timing.h) */
extern int rg_timing_on;
void rg_timing_enter(int site, unsigned flags, const void *ra, uint32_t a0, uint32_t a1,
                     uint32_t a2, uint32_t a3, uint32_t f12);
void rg_timing_leave(int site, unsigned flags, uint32_t v0);

void GfxEndFrame_141c20(Ctx *a0, s32 a1)
{
    if (!rg_timing_on) { GfxEndFrame_141c20__rg_body(a0, a1); return; }
    rg_timing_enter(4 /* id column */, 1u << 0 /* a0 is a pointer */, __builtin_return_address(0),
                    (uint32_t)(uintptr_t)a0, (uint32_t)a1, 0, 0, 0 /* f12 bits */);
    GfxEndFrame_141c20__rg_body(a0, a1);
    rg_timing_leave(4, 0, 0);
}
```

- **Always call both** enter and leave, whatever `kind` says: the runtime keeps the
  arguments for return dumps (`W_stk`) and the pairing id, and logs only what the site
  logs (`ret` sites write no entry, `entry` sites no return, `skipzero` leaves are
  dropped when that argument is 0).
- `flags`: bit *n* = argument *n* is a pointer (from the prototype), bit 4
  (`RG_TIMING_RETPTR`) = the result is. Pointers go through the reverse map in `a`/`v0`
  and are followed as host pointers by `arg:` chains.
- `f12`: the bits of the first `float` argument (`SoundSeqPlayersUpdateAll_1bb110`'s
  step, `fpr:12`), else 0. Arguments beyond a3 are not needed by any site.
- Rename-in-place keeps every call (in and outside the defining file) going through the
  wrapper. Overlay functions are not wrapped: every PCSX2 site is in MAIN, and overlay
  callers show up through `ra_rva`.
- Cost when off: one load and branch per call. The ids are stable (they are probe.py's).

Rejected alternatives: link-time `--wrap` (misses calls inside the defining object and
depends on the linker); hand-written overrides (would duplicate game code the
transforms already produce).

Tests (`ctest -L trace`): `timing_sites_sync`; `timing_unit` (synthetic game memory:
every built-in source, the wrapper API for a chain dump, a return-only site, a `skipzero`
leaf and an `fpr` word, the synthetic tick switching off once `GfxEndFrame` is wrapped,
then `timing.py build`/`align` on the result) with its `WILL_FAIL` control; `timing_demo`
(`rg-runtime-demo` with `RG_TIMING`: one `VblankStart` per field at 4,920,120 EE cycles,
CD and pad reads, a clean end).

### What the port record will show (expected)

- `fb = interval` on every tick, `t0 ≈ 0`: the nominal profile (no cost model).
- `dvbl = interval` on every main tick; no late flips; the VBlank grid keeps one phase.
- `loadscreen` length set by the CDVD model; `moviemodal` length set by the movie
  path's pacing (one `MovieDrawFrame` per tick, as retail).
- Sequence steps 2.0 / 1.0, never above; `ts_mult` always 1.
- `ts_count` 1, `ts_dbl` 0, sequence owner `main`, wakes = VBlanks, 0 coalesced.

Each of these is a gate the record can check by itself (`timing.py` summary fields).

**Measured on the first port run (below), synthetic ticks:** `dvbl = interval` on every
main and loading-screen tick but one (a dvbl 6 at the start of NORMAL's loading
screen), one late flip, sync 0. But **`fb` is not the nominal value**: the stored
feedback `+0xF10` reads **2.0038** (525/262 lines) on 3,843 of 3,983 ticks, and 1.0038
on half the interval-1 title ticks. Retail sees 2.0038 only on movie frames (the VIF1
T0 sample spanning two fields plus a line). So the port's VIF1-time sample
`D_004810B4` (or T0 at `GfxEndFrame` entry) spans the whole interval: no field reset
of T0 between flips, or the VIF1 latch taken from the previous frame. Harmless while
the scene scale is locked (title, events), but in unlocked modes retail turns fb > 2
into a next-tick multiplier fb / 2 (TIMING-REFERENCE.md), so field and battle would run
at ×1.0019 every tick. To be traced with the `GfxEndFrame` entry words once wrapped
(`T0`, `VUTIME` are 0 in the synthetic records).

P6 adds a `{"t":"present"}` record per host present, so the frame-rate gate ("re-rendering
one snapshot changes no game state") can count presents per tick next to the tick rows.

## First port run vs the golden capture (2026-10-12)

`build/timing-i686/rg-game.exe --headless --fields 8000 --input
tools/trace/goldens/newgame_battle.input.txt`, `RG_DATA=data`,
`RG_TIMING=out/timing/port/newgame_golden_input.jsonl` (20,067 records, about 10
minutes). `timing.py build`: 3,983 ticks (1,058 main, 2,925 loadscreen), 17 milestones.
Against `newgame_battle2` rebuilt with this `timing.py`
(`out/timing/port/golden_newgame_battle2.*`, 55 milestones),
`timing.py align --nowrap`: 28 vs 15 milestones, 14 matched, exit 1.

| # | Milestone | Golden vbl / main ticks | Port vbl / main ticks | Reading |
| --- | --- | --- | --- | --- |
| 0 | `overlay_load 2` vs `mem_sysmode 1`, `mem_interval 2` | 9 / 0 | 0 / 0 (overlay at 1) | **first sequence difference**, an artifact of VBlank sampling: retail's TITLE load spans vbl 9..16, so its sysmode-1 and interval rows come after the load; the port's load takes no virtual time and the Db already holds 2 at boot. Not a logic divergence |
| 1 | `loop main` -> `movie_open` (title load screen, interval 1, locked) | 539..678: **140** | 121..249: **129** | **first segment with a different tick count.** `TitleStateLoadRes` waits on resource loads: a time-dependent segment (CD model), as expected |
| 2 | title movie loop | 389 | 390 | one tick: the background movie's loop point is VBlank-paced (`title_TitleMovieUpdate_4f04c0`) |
| 3 | title menu until `TitleMovieStop` | 550 | 538 | the CROSS press is scripted at vbl 1,900; the port reaches it on a different tick (input keyed by VBlank, not by tick: "Input on aligned keys") |
| 4 | `overlay_load 3`, `mem_sysmode 0`, `loop loadscreen` | 2,607, 2,666 | 2,107, 2,113 | match (1 tick each side) |
| 5 | after `loop loadscreen` | `mem_gamemode 11`, `mem_locked 1`, `loop main`, the opening FMV, battle | nothing: 2,925 loading-screen ticks to the end (vbl 7,961) | **flow divergence**: NORMAL's boot never leaves the loading screen (retail: 594 ticks). The known bring-up blocker (BRINGUP.md: game mode stays -1) |

So the first logic divergence the record finds is (5); (1)..(3) are the expected
time-dependent segments and (0) is a sampling artifact. The title's interval and lock
changes, both overlay loads, both title movies and the loading-screen thread are
reproduced in order.

## Golden run to the first battle (2026-10-13, BRINGUP.md "Checkpoint" session 3)

`out/bringup-checkpoint/run-s` (build 24, `RG_GPU=hw`, `RG_TIMING`): `align --nowrap`
matches every milestone through the battle's unlock: FMV end at port vbl 7,321 (retail
8,074), `mem_gamemode 7` 7,791 main ticks later (retail 7,758), `mem_locked 0` 47 ticks
after that on both sides. The field segment has no milestones (the scene scale stays
locked), so the flow check there is the CD-read stream: `lsncmp.py` (sequence alignment
of the `sceCdRead` lsn/sector records) finds the two streams equal through it, with
one-read reorders; `lsnname.py` names a sector from the DATA*.HD6 index. That is how
the NEW GAME party divergence (bitfield layout) was found.

**Input keying.** The golden input is keyed by the game VBlank and the port runs ahead
of retail (753 vbl at the FMV end, ~1,060 at the battle: CD model, loading screens).
So far this has not changed the flow: the field's CROSS presses come every 360 vbl and
each dialogue waits for the next one, so arriving early only shortens the wait; the
battle-tutorial START presses (24,450..24,690) come after the port's battle start and
the pages wait for them. No re-keying was needed to reach the battle. It will be needed
where a press must land inside a window (a QTE, a menu cursor that moves with time, or
a press retail sends before a page exists): use the milestone-relative keys above
(`M<idx>+<ticks>`); the battle start (`gamemode_push 7`) and the FMV end
(`movie_shutdown`) are good anchors for this script.

## Milestone-aligned comparison

### Milestones

`timing.py build` writes `RUN.milestones.tsv`: `vbl  main_tick  kind  key`, in logic
order (frame index, then record order; never VBlank order). `main_tick` is the number of
main-loop ticks before the event. `key` holds only what both sides reproduce: game
values and caller names.

| Kind | Key | Example (golden run) |
| --- | --- | --- |
| `overlay_load` | overlay id | `2` at vbl 9, `3` at 2,607 |
| `set_interval` | interval, sync, caller | `1 sync=0 by title_TitleSceneOverlayModeOn_4eaa40` |
| `scale_locked` | value, caller | `0 by BattleModeUpdate_280220` |
| `gamemode_push` / `gamemode_pop` | mode, phase | `7 phase=2` (battle start, vbl 23,964) |
| `sm_state` | state-machine PS2 address, state | title `sm=00948d90 state=1..5,14`; battle HUD `sm=004bc278 state=23001..23003` |
| `movie_open` / `movie_shutdown` | caller (players are heap objects) | `MoviePlayModal_267c60` |
| `loop` | the frame loop entered | `loadscreen`, `moviemodal`, `main` |
| `mem_interval`, `mem_gamemode`, `mem_locked`, `mem_sysmode` | the new value | what game memory holds at a VBlank when it differs from the previous VBlank: the port reads it (`MemState`, `VblankStart`); on PCSX2 `timing.py` tracks it from the setter, push/pop, task-table and VBlank records. Several changes inside one VBlank collapse to the last on both sides (NORMAL's boot pushes 1, 6, 11 at vbl 3,865: `mem_gamemode 11`). A first value equal to the boot default (game mode -1, lock 0, sysmode 0) is not a change |

The golden run has 40 milestones from hooks plus 15 `mem_*` (55; `timing.py build`
since 2026-10-12). Candidates to add when the port records them: map
loads (`OverlayLoad` covers images only), save/load completion, and battle end
(`gamemode_pop` 7).

### Aligning

`timing.py align A.milestones.tsv B.milestones.tsv [--kinds ...]`:

1. **Sequence.** Match the two `(kind, key)` lists with `difflib`. The first non-equal
   block is a **flow divergence**: the two runs did different things (a different menu
   choice, a different state machine path). Reported with both sides' surroundings.
2. **Segments.** For each pair of consecutive matched milestones compare the number of
   main-loop ticks between them. Equal on both sides when the logic in between does not
   depend on time. A difference is reported per segment (`<- tick count differs`); the
   VBlank deltas are printed beside it and are allowed to differ.
3. Exit 0 only if the sequences are identical and no segment differs.

`--nowrap` keeps only the kinds a port run yields without wrapped game functions
(`overlay_load`, `loop`, `movie_open`/`movie_shutdown` keyed by kind alone, the `mem_*`
views) on both sides.

Checked on PCSX2 runs:

| A vs B | Result |
| --- | --- |
| `newgame_battle2` vs itself | IDENTICAL, 0 of 39 segments differ (exit 0) |
| `newgame_battle2` vs a copy with battle start moved one tick (control) | 2 segments reported (exit 1) |
| `newgame_battle2` vs `newgame_battle_perturbed` | the segment from the battle HUD to the tutorial differs: 60 vs 32 ticks (the golden state trace agrees with 60: mode 11 at vbl ≤24,182). A second PCSX2 instance was started during the perturbed run: a real divergence, found. Its last 3 milestones are missing (records lost after vbl 24,330), and the long segment into the battle reads 7,753 vs 7,758 ticks because of an earlier lost window (exit 1) |
| `newgame_battle2` vs `title_idle` (no input) | the first 16 milestones match with equal tick counts, then the flows part where NEW GAME is pressed (`TitleMovieStop` vs `TitleMovieUpdate`) |

Segments whose tick count may legitimately differ, and how to treat them:

| Segment contains | Why it differs | Treatment |
| --- | --- | --- |
| `loop loadscreen` .. `loop main` | the loading thread draws while the CD loads | compare tick counts of the main loop only (`main_tick` already excludes `loadscreen`) |
| CD-polling modes (game mode 3 loading, `StreamStep`) | ticks spent waiting for data | flag segments with CD reads; compare state at the next milestone instead of tick counts |
| `moviemodal` | FMV length in ticks follows the decoder's pacing | `main_tick` excludes it; compare the movie's frame count separately |
| title idle timer / attract | counts ticks against a VBlank-paced movie | input-dependent; usually not crossed |
| unlocked modes with retail slow frames | `ts_mult` > 1 moves things further in one tick | tick counts still equal; positions differ: compare with float tolerance or start the port with a cost model |

### State comparison on aligned keys

Today's `port_trace.py check` compares region hashes at equal game VBlanks. With the
timing record on both sides the key becomes `(milestone index, main ticks since it)`:

1. **Map PCSX2 samples to ticks.** PCSX2 samples when the EE thread is idle at a vsync,
   which in the main loop is inside `WaitVsyncCount` at the end of a tick. The
   golden's `ticks.tsv` (same run, see "Golden" below) gives, for each sampled vbl, the
   tick whose `WaitVsync` spans it, hence the key.
2. **Sample the port at the same logical point**: in `rg_timing_enter` of `WaitVsync`
   (main thread) instead of at VBLANK_START. `RG_TRACE_KEYS` becomes a list of tick keys
   (`port_trace.py --keys-from golden.tsv --timing golden.ticks.tsv`).
3. `trace.py compare` gets `--key tick` (a third key column in the TSV: `M<idx>+<ticks>`);
   the rest of its report (first divergent key, symbols differing, per-region first
   divergence) is unchanged.
4. Inside segments flagged as time-dependent, skip state rows and resume at the next
   milestone.

### Input on aligned keys

The golden input script is keyed by game VBlank. At interval 2 the game reads the pad
once per tick, and the tick phase can differ (TIMING-REFERENCE.md "Ticks, waits and
lag"), so the same VBlank-keyed script gives the port different edges, or misses a
press. Rebase it:

1. `timing.py rebase-input golden.input.txt golden.ticks.tsv golden.milestones.tsv`
   (to write) turns each line `first last BUTTONS` into `M<idx>+<t0> M<idx>+<t1>
   BUTTONS`, using the ticks whose `PadUpdate` saw the press in the golden.
2. The port's input source resolves `M<idx>+<t>` at run time: the timing runtime counts
   milestones and main ticks as they happen and serves the word to `PadUpdate` on that
   tick. This needs the runtime milestone detector, the same code that writes the
   record.
3. Until (2) exists: run the port once with no input to the first input-dependent
   milestone, translate the next input line's key to that run's VBlanks, rerun, repeat.
   Valid as long as the flow up to each press does not depend on input.

### Golden for this

Probe runs and the golden state trace are different runs. Hooks shift EE timing by a
few cycles, which was harmless here (the game-mode timeline matched), but a lockstep
golden should hash regions **and** log timing in one run: `trace.py run` installs its
input hook through `input.install(extra=...)`, the same path `probe.py` uses, so it can
install the `timing` blobs and drain the ring at each sample. That is the next
harness step, then a new golden (`newgame_battle.timing`).

## Order of work

1. Harness: one-run golden with region hashes + timing (above); a field/menu input
   script that reaches `SceneOverlayModeOn` and an unlocked field.
2. Port: `timing_sites.tsv` generator and `src/trace/timing.c` **done** (2026-10-12);
   the `probe_wrap` stage is next, then check the expected values above on the title.
3. `timing.py align` on port vs golden: the milestone sequence first (it needs no state
   hashing), then tick-keyed state rows, then rebased input.
4. Decide the cost model only where step 3 shows a time-dependent segment that matters
   (the BubbleSort and load segments are already aligned away).
