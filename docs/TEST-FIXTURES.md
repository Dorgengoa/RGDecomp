# Test fixtures: start runs at points of interest

**Status (2026-10-18, late): port save states work, wired into rg-game, deterministic. The
route goes past the first battle to the first save** (`tools/trace/goldens/
newgame_save2.input.txt`, "Route" below, re-timed for the AngleWrap fix + re-ingest + native
VU0): eight milestones from the title menu to "saved on the memory card, back in the field",
all eight verified by `verify.py`, and a **game-save fixture** (`run_from.py --boot-save
save2`): power-on with the card the route wrote, CONTINUE loads it; it needs no state, so it
survives rebuilds.

**2026-10-18, latest: the whole game is testable from manufactured saves.** The save editor
applies the game's own per-chapter start states and spawns the party anywhere the debug jump
table names; the **card library** (25 cards: every chapter, every planet, the Dorgenark, the
ghost ship / EX, Alistia, space, a late-game card with all menu rows) passes
`bootcheck.py --lib`, the broad smoke test ("Card library").

**2026-10-18 later:** manufactured game saves reach FACTORY, INSMENU and INSECT
("Manufactured saves", save editor docs/SAVE-FORMAT.md), a steering tool walks the leader
("Navigation"), and a second battle extends the route from the save2 card.

Problem: every test run replayed the golden input from power-on (~23,000 fields to the
first battle, ~8 minutes headless). Now a run can start at any milestone of the route in
about a second, or boot the route's own save.

## Quick start

```powershell
# build (Release, clang i686, ninja -j4) into build/fixtures-i686
powershell -ExecutionPolicy Bypass -File tools\fixtures\build.ps1
# start at the first battle and run 300 fields (regenerates the set if the exe changed)
python tools\fixtures\run_from.py battle --run 300
python tools\fixtures\run_from.py field --fields 9000 -- --shot 8500:out\x.png
python tools\fixtures\run_from.py --fields 31100 save_point -- --shot 31000:out\menu.png
python tools\fixtures\run_from.py --boot-save save2 --run 600 -- --shot 3800:out\boot.png
python tools\fixtures\run_from.py --list
```

Options may come before or after the milestone (fixed 2026-10-18; everything after `--`
goes to rg-game).

`run_from.py` uses `build/fixtures-i686/rg-game.exe` (or `--exe`, `$RG_FIXTURES_EXE`).
Any other build works the same way: its set is generated on first use.

| Milestone | Field (game vbl) | What is on screen | State size | Power-on to here | Load |
| --- | --- | --- | --- | --- | --- |
| `title` | 1,500 (1,467) | title menu over the attract movie (TITLE overlay) | 15.8 MB | ~3 s | ~1 s |
| `field` | 8,000 (7,967) | first 3D field after the opening FMV (NORMAL) | 26.0 MB | ~23 s | ~1 s |
| `battle` | 23,000 (22,967) | first battle (game mode 7 at vbl 22,863), after its intro unlocks | 33.1 MB | ~400-490 s | ~1 s |
| `battle_won` | 26,780 (26,747) | first battle won: results screen, then the Hooded Man scene (game mode 11) | 36.8 MB | ~165 s | ~1 s |
| `town` | 28,840 (28,807) | first field control in Salgin, walking (game mode 6) | 36.5 MB | ~177 s | ~1 s |
| `save_point` | 30,220 (30,187) | beside the first transporter after its tutorial (game mode 6) | 36.5 MB | ~188 s | ~1 s |
| `trans_menu` | 30,780 (30,747) | transporter menu open (game mode 20), before Save | 36.8 MB | ~194 s | ~1 s |
| `saved` | 31,700 (31,667) | saved to slot 1 / FILE 01, back in the field (loads with `<set>/cards/`) | 36.5 MB | ~205 s | ~1 s |

(2026-10-24: the EE float default (`RG_EE_FPU=chop`, BRINGUP.md resume item 3) left every
milestone field unchanged; only the route's help-sheet START presses moved (the "Suggestions"
sheet opens at 25,860, was 25,890). Set of the 10-24 exe: `out/fixtures/09c963c5179057aa`.)
(2026-10-19: rows from `battle_won` on re-timed by -220 fields for the retwiden + wideret
fixes, "Route" below; earlier note: rows from `battle_won` on: route `newgame_save2`, exe `build/battle-i686` of 2026-10-18
10:47 (RG_VU0_MODE=native), set `out/fixtures/58816d5808331d2a`; this build reaches the
battle in ~130 s instead of ~450 s. The title/field/battle sizes and times are from the
10-17 exe.)

Times are wall clock on the shared dev PC (headless, `RG_GPU=hw`); save itself takes
50-90 ms, a load 60-80 ms plus process start and init.

### rg-game flags

- `--save-state FIELD:FILE` (repeatable): write a state after FIELD completes.
- `--state-note TEXT`: note stored in the states (default: the file name).
- `--load-state FILE`: load after init and continue from the state's field. `--fields`
  stays absolute (load 23000, `--fields 23300` = 300 fields).
- `RG_SS=1`: the save-state machinery without either flag (a power-on baseline in the
  same mode; the run is identical either way).
- `RG_SS_AUDIT=1` (`=2` adds game RAM): after each save/load, list the words in saved
  memory that point into CRT-heap blocks, grouped by owner (see "Audit").
- Exit code 3: the state was refused (another build, corrupt, truncated, different init).
  Nothing was written back, so the message is the whole story. Exit 4: a load failed
  half way (a hook refused; should not happen).
- rg-game prints `rg-game: run_hash=<hex>` at exit, and `SAVESTATE` / `LOADSTATE` lines.

Without `--save-state`/`--load-state`/`RG_SS` nothing changes for a run (malloc goes
straight to the CRT heap; the normal Win32 fiber backend).

### Fixture sets (`out/fixtures/<exe-id>/`, game-derived data, never committed)

`tools/fixtures/regen.py` replays the golden input once from power-on with a
`--save-state` at every milestone. Set layout:

- `bin/rg-game.exe`, `bin/rg-game.map`: a copy of the build. States load only into it,
  so the set stays usable after the build dir is rebuilt.
- `<milestone>.rgstate`, `manifest.json` (exe SHA-256, input SHA-256, env, per milestone:
  field, vbl, run hash, size, wall time to reach it), `regen.log`.
- With `--check K`: `<milestone>+K.check.rgstate` and `<milestone>+K.poweron.png`
  (`verify.py` compares against them). `--trace` also records the power-on state trace.

`<exe-id>` = the first 16 hex digits of the exe's SHA-256. `run_from.py` regenerates
when the manifest's exe hash differs (or `--no-regen` fails instead). Milestones are
defined in `tools/fixtures/fxlib.py` (`MILESTONES`); add a row and rerun regen.

Scratch saves dir: each loaded run gets a fresh empty saves dir. The memory-card files
are host state (not in the state); the route writes no card before field 31,080, so a
fresh dir equals what the saver had for every milestone but `saved`, whose runs get a
copy of `<set>/cards/` (the card the generating run left, `fxlib.CARD_MILESTONES`).
Caveat: a run loaded in the middle of the game's card dialogue (between "Checking the
memory card" and "File 1 saved.") sees a different card object and the game goes back to
slot selection; start such runs from a state before the dialogue.

## Route (`tools/trace/goldens/newgame_save2.input.txt`)

One power-on-to-end input: the old golden `newgame_battle.input.txt` verbatim (to field
24,695: title, NEW GAME, opening, first battle, its tutorial) plus a continuation written
on the port. **Keys are fields** in a plain rg-game run (rg-game keys scripts on the
kernel VBlank count, docs/RUNTIME.md "Pad"; the old golden was timed on retail's game
counter, 33 apart, which does not matter while its presses fall in long waits). The file
header lists the milestones; the fixture milestones above are taken from it.

`newgame_save2` (2026-10-18, late) is the re-timed continuation; `newgame_save1` (same day,
exe4) is kept for history: its battle inputs were timed against the broken turn controller
(AngleWrap, BRINGUP.md "2026-10-18 (b)") and on the current tree its START presses open the
PAUSE menu. Timings below: `build/battle-i686` 2026-10-18 10:47, **RG_VU0_MODE=native**,
RG_RENDER/THREADS/IOP/AUDIO=native, RG_GPU=hw.

| Field | What happens | Input |
| --- | --- | --- |
| 24,700 | first battle resumes after the "Basic Battle Controls" tutorial | SQUARE every 10 fields |
| ~26,120 | "Suggestions" tutorial (1 page; new with the fixed battle AI) | START 26,180 |
| ~26,340 | "The Action Gauge" tutorial (3 pages) | START x3 (26,400 / 520 / 640), SQUARE to 26,840 |
| ~26,840 | **battle won** (game mode 7/4001 -> 11/1), results screen 26,970 | CROSS every 120 through the Hooded Man dialogue |
| ~28,960 | **first field control in Salgin** (mode 6) | stick up 29,060-29,440 |
| ~29,400 | transporter event, "Transporter Functions" tutorial (~29,960) | CROSS x4, START x3 |
| ~30,340 | field control beside the transporter | |
| 30,662-30,830 | toward the transporter pad: jump the ledge (CIRCLE x3), four stick segments | `#!stick` + CIRCLE |
| 30,890-30,909 | onto the pad centre (DR x20, found with `tapsearch.py`); **no stick-tap work-around**: the run state settles on release (A34 0 at ~50 fields after release) | `#!stick` |
| 30,960 | transporter menu (game mode 20): Save / Teleport / ??? / Item Storage | CROSS 30,950 |
| 31,030-31,410 | Save -> MEMORY CARD slot 1 -> FILE 01 (NEW DATA) -> "Create new data?" Yes | CROSS, CROSS, CROSS, LEFT, CROSS |
| ~31,700 | **"File 1 saved."** (`saves/card1/BASCUS-97490LV5RG_00/`) | CROSS, CIRCLE x2 |
| ~31,900 | back in the field; walk 31,970-32,090 | stick |

The battle part is **not robust**: the battle AI's float math moves the tutorials. Seen on
2026-10-18: AngleWrap fix (save1 -> local-VU0 tree: tutorials appear, win at 26,600 -> 27,220,
field control 28,700 -> 29,300) and VU0 local -> native (tutorials +140 fields, win
27,220 -> 26,840, field control 29,300 -> 28,960). Everything after field control only
shifted with it (the stick and button lines moved as a block; only the pad step was
searched again and came out the same). Any change to battle-relevant code needs a re-time
("Re-timing the route" below).

Walking needs the left stick: the `#!stick` channel (docs/INPUT.md "Scripted sticks").
Limit: input tables are 32,636 VBlanks long (input.py's guest table and
`RG_SCRIPT_MAX_ENTRIES` in src/host/host.h), so a route file ends before field 32,636; a
longer route starts a new file from a milestone (e.g. `saved` or `--boot-save save2`).

### Re-timing the route (after a change that moves the battle)

1. `regen.py --only title,field,battle` (the prefix to 24,695 is battle-insensitive so
   far), then `play.py --from battle --input <SQUARE-only file> --status 20 --shots ..`:
   the first `gamemode=11/0` after 24,720 is the "Suggestions" tutorial.
2. Put START ~60 fields after each tutorial opens, run again from a `--save` just before;
   repeat for "The Action Gauge" (3 pages, 120 apart). Look for `7/4001` -> `11/1` (win).
3. Shift the field block (stick/button lines from the first stick line to the pad) by
   the change in field-control time (first `gamemode=6/100`).
4. At the pad, `tapsearch.py` from a state ~60 fields after the last stick line:
   `--lens 16,20 --then "+60 +63 CROSS" --want-mode 20` lists the taps that open the
   transporter menu with the end position (pad centre (-2102, -1830)).
5. Shift the save block by the same amount, write the golden, then `regen.py --check 300`
   (continuous power-on replay: proves chained segments = the replay) and `verify.py`.
Scratch helpers of the 10-18 re-time: `out/route2/mk.py` (route file from segment specs:
`sq A B`, `btn F NAME`, `cx A B STEP`).

**Staging a re-time (2026-10-24)** while other lanes use the goldens and cards: copy
`tools/fixtures`, `tools/trace` and `out/fixtures/cards` into a scratch root (same relative
paths), add a `data` junction to the real data and set `RG_DATA`; the fixture tools resolve
everything from their own location, so regen / retime / verify / saveedit / bootcheck run
there unchanged and write `<stage>/out/fixtures`. Then land the goldens, fxlib.py and the
cards in one step: `python tools/fixtures/stage_swap.py --stage S --backup B --file
tools/trace/goldens/newgame_save2.input.txt --file tools/fixtures/fxlib.py --dir
out/fixtures/cards/save2 ...` (copies next to the targets first, then switches with renames,
~60 ms; prints the time; old versions in B). STATUS-line milestones must be multiples of
`RG_STATUS_EVERY` (50 for bootcheck).

### Re-time 2026-10-19 (retwiden + wideret fixes, play-test 2 lane)

The two game fixes of 2026-10-19 (battles award EXP / money; battle commands pressed during
an action's recovery are buffered, BRINGUP.md "User play-test 2") moved the battle: the
route's SQUARE taps now fire every gun cycle, the battle is won at **26,510** (was 26,840),
only the "Suggestions" help sheet opens (25,890; "The Action Gauge" no longer appears before
the win) and field control in Salgin comes at **28,740** (was 28,960). The field block was
shifted by **-220** as a whole; at the pad no step is needed any more (tapsearch: no tap ->
transporter menu; the old `DR x20` step now walks off the pad and CROSS opens a dialogue,
game mode 12/1). Milestones: battle_won 26,780, town 28,840, save_point 30,220, trans_menu
30,780, saved 31,700 (`fxlib.MILESTONES`).

New tool, `tools/fixtures/retime.py` (closed loop, replaces steps 1-2 of the recipe above):
from a save state it plays short segments and picks the next presses from the game mode at
the end of each (fight 7/201: SQUARE every 10; help sheet 11/x before the win: START 60 fields
after it opens, then every 120; after the win: CROSS every 120), stops at a target mode
(e.g. `--until 6/100`) and writes the prefix + generated lines (`route.txt`) and the state
there:

```powershell
python tools\fixtures\retime.py --exe SET\bin\rg-game.exe --from SET\battle.rgstate `
    --base tools\trace\goldens\newgame_save2.input.txt --start 24720 --until 6/100 --out out\route\rt1
```

**How it was written** (reusable, `tools/fixtures/`):
- `play.py --from <milestone or .rgstate> --to F --input X --out D [--shots A:B:S]
  [--status N] [--save F]`: one segment from a state; `montage.py D` makes a contact
  sheet of the shots. Chain segments with `--save`. **Rule:** a segment's new input lines
  must start after the field its state was saved at (the pad read keyed at that field
  happened before the save); otherwise the chain and the continuous replay differ by one
  game tick (2 fields).
- `relink.py --build-dir build/X --out D SRC...`: rebuild rg-game from an existing build
  dir with a few sources recompiled (overrides, host files): minutes instead of a full
  rebuild; `--prebuilt SRC=OBJ` reuses an object when the tree's source has moved on.
  The route exe `out/route/exe4` is `build/battle-i686` + the four route overrides +
  the `#!stick` host change.
- `tapsearch.py --from STATE --input BASE --at F --lens 2,4,8 [--then "+40 +43 CROSS"]
  --to T --out D [--want-mode M] [--stop]`: tries every stick direction x length as one
  `#!stick` tap at F (plus the `--then` lines, fields relative to F) and prints the game
  mode at T and the leader's position (RG_STATUS_DUMP of the Salgin leader at 0x0AA3A3E0);
  `HIT` marks taps reaching game mode M. 16 tries ~2 min. Used for the transporter pad.
- `play.py --shots` is capped at 32 (rg-game `RG_MAX_SHOTS`); more is refused up front
  (it used to end in an rg-game usage error, exit 2).
- Positions and states for steering came from `RG_STATUS_DUMP` (host addresses of the
  leader, `h0x0AA3A3F0:12` = Jaster's position) and `RG_BREAK` (scratch scripts in
  `out/route/`: `greedy.py` tries 8 stick directions per step from a state and keeps the
  one closest to a target, `tap.py`, `pos.sh`).

**Retail check (2026-10-18, route save1; not repeated for save2).** PCSX2 replays only buttons (input.py), so a retail replay
is at best valid up to the first stick line (field 28,800). Run: `trace.py run --memcard
--speed 0.5 --renderer 13 --shot-every 300 --shot-from 24600 --stop-vbl 29600 --input
tools/trace/goldens/newgame_save1.input.txt` (`.tools/run/route_save1.tsv`, shots in
`.tools/run/shots/route_save1/`, 16 min). Retail matches the port to the end of the old
golden (battle tutorial, battle resumes at vbl 24,710) and the SQUARE attacks fight the
battle (Jaster 36/80 HP at vbl 25,820, enemies taking hits), **but "The Action Gauge"
tutorial had not opened by vbl 26,120** (port: ~field 26,000), so the route's START at
26,100 opened the pause menu and the rest of the battle inputs navigated it ("Return to the
title screen?" No). So the continuation is **port-timed, not a retail route**: the battle
AI is not lockstep (RNG, BRINGUP.md 10-17), and the tutorial is triggered by battle events.
A retail-valid version would need event-robust inputs (e.g. probe the game mode and
splice per-milestone segments) and stick support in input.py's trampoline.

## Game-save fixtures (`--boot-save`)

`python tools/fixtures/run_from.py --boot-save save2 [--run K | --fields N] [--exe X]`:
power-on with a copy of `out/fixtures/cards/save2/` as the saves dir (memory card slot 1
holding the route's FILE 01) and `tools/trace/goldens/boot_save2.input.txt`: title menu
(CONTINUE is the default cursor when a save exists) -> slot 1 -> FILE 01 -> "Load the data
in file 1?" Yes -> "File 1 loaded." -> story recap -> **field control on the Salgin
transporter at ~3,730** (`# boot-end: 3750`). No save state is involved, so it works with
any build. The card is game-derived data (never committed); `regen.py` rewrites
`cards/<fxlib.ROUTE_CARD>` (= `save2`) whenever its run reaches the save (and keeps the
set's own copy in `<set>/cards/`). `save1` (+ `boot_save1.input.txt`) is the card of the
old route (exe4), left as it was: it still boots to field control at 3,730 on the current
tree. ~9 s wall to control. For RG_STATUS_DUMP addresses in a boot run add `RG_SS=1`
(fixed RAM block at 0x0A000000; without it the dump reads unmapped host memory and
crashes).

### Checkpoint (route save2, 2026-10-18 late)

- Build `build/battle-i686` (reconfigured, **RG_VU0_MODE=native** per the user decision,
  full rebuild 25.5k objects at -j4, rg-game 10:47; game/ = re-ingest de031765). Set
  `out/fixtures/58816d5808331d2a`: `regen.py --check 300` power-on -> 32,220 in one run,
  205 s, 16 states, card written (`cards/save2`). `verify.py`: **all 8 milestones** OK
  (run hash and frame hash at N+300 equal between power-on and loaded runs).
  `--boot-save save2` and `save1`: game mode 6 at 3,730.
- An intermediate set for the local-VU0 build of the same tree (`out/fixtures/4b4a2f3ee4ac173b`,
  exe copy `out/route2/rg-game-local.exe`) also verified 8/8 with that build's timings
  (win 27,220, control 29,300, saved 32,260); superseded.
- Route scratch: `out/route2/` (segment runs `n*` = local VU0, `m*` = native, tap searches
  `ts*`, boot walks `bw/`).
- Not done: extending the route past the save (goal "first town exploration"). From
  `--boot-save save2` the objective marker (yellow star in the SELECT map, the dimmed
  scene is a paused map view) lies off the plaza; plain stick walks hit walls (plaza
  bounded at z -1856 .. -1944); no random encounter in Salgin's streets. Needs a target
  position (objective marker in memory) or a hand-steered path; `tapsearch.py` /
  `out/route/greedy.py` can do the steering once a target is known.

### Checkpoint (route save1, 2026-10-18)

- Set `out/fixtures/5025500ccf58f601` (exe `out/route/exe4/rg-game.exe` =
  `build/battle-i686` relinked with `tools/fixtures/relink.py` + the four route overrides
  + the `#!stick` host change; its copy `bin/rg-game.exe` is the exe to pass while
  `build/fixtures-i686` is stale: `--exe out/fixtures/5025500ccf58f601/bin/rg-game.exe` or
  `$RG_FIXTURES_EXE`). `regen.py` power-on -> 31,620 in one run: 677 s, all seven states,
  card written (`card1/BASCUS-97490LV5RG_00`, "RogueGalaxy[01] / JasterLv01 00:06").
  `run_from.py` loads of battle_won / town / save_point / saved: 1.2-1.7 s each, shots
  as in the table; `--boot-save save1`: field control at 3,725, 12 s.
- `build/fixtures-i686` needs a full rebuild after the 10-17 re-ingests (~23k objects,
  hours at -j4 on the shared PC; started and stopped 10-18): `build.ps1 -Reconfigure`.
- Tests: `fixtures.cli` (new, run_from argument handling, `--print`, no game run) passes
  standalone; the host test for `#!stick` (tests/host `input_script`, extended) passes
  (`rg-host-tests input_script`, built standalone against the relinked `rg_host.lib`,
  `out/route/ht.py`).

- **`tools/fixtures/talksweep.py CARD --exe EXE --control C`** (2026-10-22): find an
  interaction next to a card's spawn (shop, NPC): 8 stick directions x short walks, CROSS x4,
  reports game modes after the walk (12/* = talk / menu). Shop card used for resume item 11:
  `saveedit.py copy cards/save2 cards/zshop2` + `patch --section 13020 --spawn-jump 34
  --no-help` (Zerard bounty-sheet shop); E walk 15 opens the shop (`out/shopcheck/`).

- **`tools/fixtures/cardwhere.py CARD --exe EXE --input F --to FIELD [--shots A,B] [--out D]`**
  (2026-10-25): where the leader is after an input script booted from a card: navprobe's probes
  (`RG_BREAK` on the per-tick leader lookup + the camera objects) on a `run_from.py --boot-save`
  run, so play-test exes (no save states) work too (the exe needs its `.map` beside it: use the
  build dir's copy). Prints game mode, map id, leader x/y/z + yaw and the camera-relative stick
  bytes for the 8 world headings. Used to walk the user's card into Salgin's item shop.
- **`tools/fixtures/shopcrash.py --exe EXE [--api d3d11,vulkan] [--stale]`** (2026-10-25): the
  1025b shop-close crash regression. Card `zuser1025` (a copy of the user's play-test card,
  Salgin "Near the Item Shop"), input `tools/trace/goldens/shopcrash_buyclose.input.txt`: door
  north-west of the transporter, into the item shop, Shihawa (SHOP), Buy -> Grand Edge (7th row)
  -> x1 -> Yes (863 -> 543 z) -> CIRCLE out (closed ~4,800), field to 5,100. PASS = no exception,
  shop menu seen, back in the field. 1025b and the pre-fix tree crash at field 4,750 on both
  APIs; ctest `fixtures.shopcrash` (D3D11), play-test gate `shop` (both).
- **`tools/fixtures/poisoncheck.py --exe EXE [--suite shop,boot,drivers,soak] [--mode 1|2]
  [--control]`** (2026-10-26): the stale-packet regression: runs those tools with
  `RG_NR_POISON` (dead frame packet stacks poisoned; renderer reads of them reported) and fails on
  any poisoned or refused walker read (docs/NATIVE-RENDER.md "Remembered packets"); ctests
  `fixtures.poison`, `fixtures.poison_control`.

## Navigation (steer.py)

Walking to a place is a closed loop over short `play.py`-style segments, now a local tool
instead of hand iteration.

- **`tools/trace/navprobe.py`** reads, at the end of a segment from a state: the field
  **leader's position and yaw** (`RG_BREAK` on the return of the `ActionMgrFindById_233b50`
  call in `PlayerControlUpdateMaybe_1fc4a0`, eax = the leader Chara: pos +0x70, yaw +0x64),
  the **active camera** (Camera0..5 at 0x4B5660 + k x 0x2F0: +0x50 look-at, +0x60 eye; the
  one looking at the leader), the **objective markers** the minimap draws (yellow star:
  `RG_BREAK` on the return of `StateBlockCollectMapMarkers_3cc390` in
  `MinimapDrawEntry_325720` with `RG_BREAK_DUMPARG=1` = its vec4 out array), the **map id**
  (`D_004838C0`->+0x18->+4) and the game mode. RVAs come from the exe's own map +
  llvm-objdump (cached as `navprobe.json` next to the exe), so any build works.
  `python tools/trace/navprobe.py where|marker --from STATE --exe EXE`.
- The move stick is **camera-relative** (calibrated from the save2 boot state: stick up moves
  along the camera's look direction, stick right along it minus 90 degrees);
  `navprobe.stick_for(heading, cam)` gives full-deflection DS2-square bytes (run band).
- **`tools/fixtures/steer.py --from STATE --input BASE --out D (--target X,Z .. | --marker)
  [--step 40] [--stop-on-mode]`**: per step aim at the waypoint, play `--step` fields, save a
  state; a step with less than `--min-gain` of the expected progress is retried from the same
  state with the heading turned +-45 / 90 / 135 / 180 degrees, scored by progress plus
  `--explore` x new ground reached (a candidate that did not move scores worst), the winner is
  followed for `--detour` steps (wall following). `--stop-on-mode` ends the walk when the game
  mode or map id changes (event, battle, area change) and keeps the state there. Output:
  `D/route.txt` (BASE + `#!stick` lines with `# steer:` comments; they start after each
  state's field, so the file replays the walk continuously), `walk.tsv`, `step*.rgstate`,
  `last.rgstate`; `--keep` keeps every trial's log/state. One rg-game at a time; a step with
  retries costs ~8 x 2 s.
- **`--search`** (2026-10-18 late): A* instead of the greedy walk, over a walkability grid
  sampled on demand: a node is a grid cell (`--cell`, default 60 units) reached by a saved
  state; expanding it plays `--step` fields in the 8 world headings from that state (one
  rg-game run each, ~2-3 s), and each heading that ends in an unseen cell (same game mode
  and map) becomes a node with g = walked distance, h = straight distance to the target.
  Every probe lands in `grid.tsv` (cell, end position, start position, mode) = the sampled
  walkability; `--max-expand` caps the cost (8 runs per node). Output as the greedy walk
  (`route.txt`, `last.rgstate` = the node nearest the target). Slower per step than the
  greedy walk, but it backs out of pockets instead of oscillating.
  First test (exe `out/route3/exeF`, save2 control state, target the Salgin marker 6,300
  units away, `--cell 80 --step 40 --max-expand 30`, 13 min): 30 cells of the plaza sampled
  (`out/route4/srch1/grid.tsv`); the branches leaving the plaza eastward started random
  battles (game mode 7), which end a branch, so the search filled the plaza instead. Random
  encounters are the practical limit: use it where there are none (towns, the Dorgenark) or
  for short hops; an encounter-off switch for steering is not found yet (the encounter
  enable is the chara-system bit `WorldDataCmdSetFieldEnablesMaybe_3b9260` sets, re-set on
  CONTINUE by `GameStartModeUpdate_2858f0`).
- Limits (greedy mode): no map knowledge. In Salgin's streets the direct heading to a far marker
  runs into walls and corners. After battle 2 (state at 7,100, (-1868, -1794)) it ends in a
  pocket east of the plaza and oscillates between two points ~20 units apart (`out/route3/w6.log`);
  a long walk needs waypoints (`--target x1,z1 x2,z2 ..`, read off `walk.tsv` or the SELECT map)
  or a path search over the collision mesh (not written).

### Route extension: battle 2 (`boot_save2_battle2.input.txt`)

From `--boot-save save2`, steer.py toward the objective marker (3602, 1072; the party is at
(-2102, -1830)) walked east out of the plaza and a **random encounter** started the second
battle at ~4,000 (Baphu / Mishi; game mode 7). Hand-added: "The Lock-On Function" tutorial
(3 pages, START x3), SQUARE every 10 fields (won, results 7/504 at ~6,300), CROSS, "The Map
Display" tutorial (2 pages, START x2), field control at ~6,760. Verified as one continuous
power-on run and in `bootcheck.py` (`save2_battle2`: 4 milestones, 39 s). **Re-timed
2026-10-24** for the EE float default (gun every 16 VBlanks): no mid-battle help sheet, results
7/504 at 7,200, field control 7,630; milestones battle2_won 7,250, battle2_field 7,700
(`boot-end: 7700`). It is a separate
input started from the card, so the 32,636-field table limit restarts at 0 (fields here are
those of the boot run, not the route's). Port-timed like the first battle: re-time after
battle-relevant changes or a new save2 card.

### Checkpoint (manufactured saves + navigation, 2026-10-18 late)

- Every overlay the game uses now loads in a fixture: TITLE / NORMAL (route), **FACTORY**
  (`--boot-save factory`), **INSMENU** and **INSECT** (`--boot-save insectron`), plus a second
  battle (`save2_battle2`). `bootcheck.py` 4/4 PASS (exe `out/route3/exeF` = build/battle-i686
  + the FACTORY data override, relink.py; `save2_battle2` also passes on the set exe
  `out/fixtures/58816d5808331d2a`). FACTORY needs `overrides/src/main_data/data2c_00480390.c`
  (BRINGUP.md 2026-10-18 (d)): build dirs must be **reconfigured** to pick the new override up.
- Salgin's streets do have random encounters (the save2 checkpoint above saw none on the plaza).
- `fixtures.saveedit` (ctest, no game data) passes standalone.
- Scratch: `out/route3/` (`ins1/` Insectron walk, `fac/`, `w*/` steering, `exeF/`).
- Not done: the objective marker (3602, 1072) and a save3 card; a later-area save (SAVE-FORMAT.md
  "Open").

## Manufactured saves (FACTORY, INSMENU, INSECT)

The item factory and the Insectron are many hours into the story, so instead of playing there
the fixtures **edit the route's own save** (save2) with `tools/fixtures/saveedit.py` (format:
docs/SAVE-FORMAT.md) and boot it like any game-save fixture. No save state is involved, so
they work with any build (the factory one needs the FACTORY data fix below).

| Fixture | Card (from save2) | What the patch unlocks | Boot script | Milestones (`fxlib.BOOT_FIXTURES`) |
| --- | --- | --- | --- | --- |
| `save2` | (regen.py writes it) | | `boot_save2.input.txt` | control 3,750: NORMAL, mode 6 |
| `factory` | `--set-flag 0x3E8` | main menu row 6 "Factory" (`TopMenuRow6UnlockedMaybe_29ac20`) | `boot_factory.input.txt`: CONTINUE, TRIANGLE, row 6, "Linking to the factory via remote control...", Blueprints grid, Go Back, "Halt factory operations?" Yes, close menu | factory 4,400: **FACTORY** (ovl 4), mode 16/100; factory_exit 6,400: NORMAL, mode 6 |
| `insectron` | `--var 5=3 --insect-team 0:ALPHA:0,1,2,3,4 --insect-team 1:BRAVO:5,6,7,8,9` | title row INSECTRON (summary var 5 >= 3) = standalone Insectron mode; two registered teams for Watch Battle | `boot_insectron.input.txt`: title INSECTRON, Watch Battle, P1 = ALPHA and P2 = BRAVO loaded from FILE 01, Battle Start | insmenu 2,300: **INSMENU** (ovl 6); insect 10,300: **INSECT** (ovl 5, announcer intro); insect_battle 11,500: mode 15/101, CPU vs CPU turns |

```powershell
python tools\fixtures\saveedit.py make                     # cards/factory, cards/insectron from cards/save2
python tools\fixtures\make_allcard.py                      # all library saves on ONE card (FILE NN) for play-testing: out/playtest/saves-all
python tools\fixtures\bootcheck.py --exe out\route3\exeF\rg-game.exe [--shots out\bc] [--states]
python tools\fixtures\run_from.py --boot-save insectron --run 600 -- --shot 12000:out\ins.png
```

- `bootcheck.py`: one power-on run per fixture with `RG_STATUS_EVERY=50`; a milestone passes
  when the STATUS line at its field has the overlay index and game mode (3/3 PASS, 2026-10-18,
  exe `out/route3/exeF`: save2 11 s, factory 29 s, insectron 111 s). `--states` writes
  `out/fixtures/<exe-id>/boot/<name>_<milestone>.rgstate` (RG_SS=1) for `play.py --from`.
- `run_from.py --boot-save NAME --input X`: X replaces the boot script (new, for trying
  variants without writing a golden).
- **How the paths were found** (reusable): the decomp names the gates (factory row = flag
  0x3E8; insect row = key item 0x40E5; title INSECTRON row = any save's summary var 5 >= 3,
  `McSaveHeaderCheckClearedMaybe_372fd0`; registered teams = chunk 15 of a save,
  `SaveFileReadInsectTeams_3e49d0`); menus were walked from save states with `play.py`
  segments + `montage.py` (scratch `out/route3/ins1/e*`, `out/route3/fac/`).
- INSMENU is not the in-story insect cage menu: that one (main menu row 5, game mode 14,
  `InsectMenuModeUpdate_27e610`) is MAIN code. INSMENU is the title's standalone Insectron
  mode (title result 3 -> mode message kind 2 -> `OverlayLoad_1c3210(6)`), and INSECT is the
  battle (game mode 15) it and the story tournament (`ScriptFnPushInsectBattleMode_3d74c0`) start.
- (Solved 2026-10-18 late, "Card library" below: party +0x4 is the planet; CONTINUE takes the
  positions from the save's summary, not from the party object.)

## Card library (the broad smoke test)

**One manufactured card per chapter / planet / major area, booted and smoke-tested by one
command** (`bootcheck.py --lib`). Each card is the route's save2 + `saveedit.py patch` with
the game's own data (docs/SAVE-FORMAT.md "Game data the save editor uses"):

- **story point** = an `initial_status5` section, the developers' start state for that
  chapter phase: party (who is active / reserve / away), levels and stats, equipment,
  items, money, story flags, vars, flag sets, map markers; chapter + the 15 progress slots
  follow from the section id;
- **spawn** = a point of the game's debug jump table (`dbg/map_jump_en.txt`: planet,
  position, yaw) or an event's end position (`event_param5`); planet / area / sky in the
  party object, positions + camera in the summary (what CONTINUE reads, SAVE-FORMAT.md
  "How CONTINUE places the party"); area / sky from `planetarea_matrix5` at that story point;
- `--no-help`: the 'Help Sheet' flags (tutorial pop-ups seen).

Definitions: `tools/fixtures/cardlib.py` (LIBRARY: name -> sections, spawn, description);
`saveedit.py make` builds them into `out/fixtures/cards/<name>/` (game-derived, never
committed).

```powershell
python tools\fixtures\saveedit.py make                                  # all cards from cards/save2
python tools\fixtures\bootcheck.py --lib --exe EXE [--shots D] [--keep-logs D] [--tsv F]
python tools\fixtures\bootcheck.py --all --exe EXE                      # + save2/factory/insectron/battle2
python tools\fixtures\bootcheck.py ch04_prison --exe EXE --states       # states for play.py / navprobe / steer
```

**How a card is checked** (`bootcheck.py`, library cards): pass 1 boots the card
(CONTINUE -> slot 1 -> FILE 01 -> load, then CROSS every 100 fields from 3,700 through the
chapter recap; `LoadingScreenFrame_3435d0` takes CROSS or START once the recap text and the
load are done) with `RG_STATUS_EVERY=10` and finds the field where control starts (first
`ovl=3 gamemode=6/100`). Pass 2 replays only the recap presses before that field (later
CROSS presses would talk to whoever stands in front) and then the smoke actions relative
to control C: TRIANGLE C+60 (main menu, game mode 17), CIRCLE C+260 (menu first: once the
party walks a random encounter can start), walk camera-forward C+350..C+550, a box walk (left / back / right / forward, 150 fields each) to C+3,500.
Milestones (`fxlib.lib_milestones`): control C+40 (6/100), menu C+160 (17/*), field C+340
(6/*), encounter = any game mode 7 in C+700..C+3,500 (optional: reported, never fails). The
generated scripts stay in `out/fixtures/runs/bootlib/<name>.input.txt` (`run_from.py
--boot-save NAME --input` that file repeats a run). A fault prints the symbolized EXCEPTION
and stack (`fxlib.crash_report`, from the exe's map). ~45-75 s per card.

### Checkpoint (card library, 2026-10-18 late)

**25/25 library cards PASS and 4/4 original boot fixtures PASS** (exe `out/route3/exeF`,
build/battle-i686 + the then FACTORY override; RG_GPU=hw). **Re-run on the current tree:
`build/route3-i686` (fresh full build after the 10-18 re-ingest, RG_VU0_MODE=native,
RG_NATIVE_ONLY=ON): `bootcheck.py --all` 29/29 PASS** (`out/route4/r3.txt`, `r3.tsv`; ~60 min
incl. a slow first run), 17 random battles entered, no fault; FACTORY loads without the old
override. Every card reaches field control
in its area with its chapter's party, opens and closes the main menu; 15 of 25 also met a
random encounter in the box walk (battles ran without a fault). No crash, no hang. Contact
sheet of the control shots: `out/route4/ctl_sheet.png`; logs / shots `out/route4/lib1`,
`lib2` (the second run after moving three spawns and putting the menu before the walk).

| Card | Sections | Spawn | Area | Result (exeF) |
| --- | --- | --- | --- | --- |
| `ch01_salgin` | 1020 | 1 | Ch1 20 'Traveling with Desert Claw': Rosa, Salgin, in front of the church | PASS + encounter |
| `ch01_residential` | 1030 | 5011 | Ch1 30 'To the Residential Area': Rosa, Salgin streets (signboard) | PASS |
| `ch02_dorgenark` | 2010 | 902 | Ch2 10 'Off Rosa and Belowdecks': the Dorgenark, bridge (planet 1) | PASS |
| `ch02_juraika` | 2020 | 2 | Ch2 20 'Searching the Jungle': Juraika, jungle entrance | PASS + encounter |
| `ch03_burkaqua` | 3010 | 23 | Ch3 10 'Searching Burkaqua': Juraika, the chief's house | PASS |
| `ch03_falls` | 3040 | 5106 | Ch3 40 'To the Altar by the Falls': Juraika, waterfall area (signboard) | PASS |
| `ch04_zerard` | 4010 | 3 | Ch4 10 'To the Galaxy Corporation': Zerard, central plaza | PASS |
| `ch04_prison` | 4020 | 1301 | Ch4 20 'Escaping from Prison': Zerard prison, B15 route | PASS + encounter |
| `ch05_factory` | 5020 | 5203 | Ch5 20 'The Factory': Zerard, Insectron venue / factory district | PASS |
| `ch06_vedan` | 6030 | 4 | Ch6 30 'Searching Myna': Vedan, Myna path | PASS + encounter |
| `ch06_mines` | 6040 | 44 | Ch6 40 'The Mines': Vedan mines (43, at the elevator, refuses the menu) | PASS + encounter |
| `ch07_rosa` | 7010 | 5004 | Ch7 10 'To the Rizahna Ruins': Rosa, Sil desert (signboard) | PASS + encounter |
| `ch08a_vedan` | 8120 | 5308 | Ch8-A 20 'Cancer King Ruins': Vedan (signboard) | PASS + encounter |
| `ch08b_juraika` | 8220 | 5111 | Ch8-B 20 'Leo King's Castle': Juraika, castle (signboard) | PASS + encounter |
| `ch08c_zerard` | 8320 | 5239 | Ch8-C 20 'Gladius Towers': Zerard, tower 1F (signboard) | PASS + encounter |
| `ch09_labyrinth` | 9030 | 5008 | Ch9 30 'Solving the Key Piece Mystery': Rosa, labyrinth (signboard) | PASS + encounter |
| `ch10_kuje` | 10010 | 5006 | Ch10 10 'Kuje Desert': Rosa, Kuje desert (signboard) | PASS + encounter |
| `ch11_mariglenn` | 11010 | 5400 | Ch11 10 'Ti'atha Forest': Mariglenn, south gate road (signboard; jump 5 'Ti'atha forest' spawns in an unloaded black area) | PASS |
| `ch12_mariglenn` | 12010 | 5403 | Ch12 10 'Gathering Drigellums': Mariglenn (signboard) | PASS + encounter |
| `ch13_mariglenn` | 13010 | 5404 | Ch13 10 'Obtaining the Sacred Sword': Mariglenn (signboard) | PASS + encounter |
| `alistia` | 13020, 28010 | planet 21 (-668, 31, -1607) | Alistia [10] (planet 21): Lapatia Village transporter (record 901, AR_transp_param_EN; the E_EV18-0020 end position replays that event) | PASS |
| `ghost_ship` | 13020, 14010 | 62 | Ghost ship (planet 7), docking point | PASS |
| `ghost_ship_ex` | 13020, 14030 | 3011 | Ghost ship EX (planet 10), 10F | PASS + encounter |
| `space_deck` | 13020 | 82 | Space (planet 9): the Dorgenark's deck | PASS |
| `late_game` | 13020 | 32 | Ch13 20 + Factory row (flag 0x3E8 = 1000, also set by the section), Insectron rank var 5 = 3: Zerard spaceport | PASS |

Findings while building it (BRINGUP.md 2026-10-18 (e)):
- The smoke test found no port bug in these 25 areas. Three first-run failures were the game's
  own rules / card choices: the mine elevator (jump 43) and the Ti'atha forest point (jump 5,
  which also spawns in an unloaded black area) refuse the menu ("You can't open the menu
  here / now"); the Alistia event end position replays E_EV18-0020; ghost ship EX started a
  battle before the menu. Fixed by other spawns (signboards, the Lapatia transporter) and
  by opening the menu before walking.
- A hand-edited party without weapons crashed the first battle (`CharaCmdShot_229bc0+0x99`,
  NULL from `CharaGetEquippedWeapon`): a card bug (retail parties always carry weapons), fixed
  by applying the section's equipment (SAVE-FORMAT.md "Characters").
- Observation, not verified against retail: a glowing magenta pillar in the Rosa labyrinth
  (`ch09_labyrinth` control shot); probably the area's barrier effect.

Not done: the walk is checked by mode only (the leader's position is not compared; `--states`
+ `navprobe.py where` can); battles are not fought (no attack presses), only entered; no
retail comparison of the library areas. (Both done 2026-10-18 night: "Auto-battle", "Retail comparison" below.)

## Auto-battle (`autobattle.py`, `bootcheck.py --fight`)

Battles across the library are fought by a closed-loop input generator,
`tools/fixtures/autobattle.py` (docstring = full reference):

```powershell
python tools\fixtures\autobattle.py prep ch07_rosa --exe EXE     # battle state of the card's box walk
python tools\fixtures\autobattle.py fight ch07_rosa --exe EXE --shots [--out D]
python tools\fixtures\autobattle.py probe out\fixtures\<id>\fight\ch07_rosa_battle.rgstate --exe EXE
python tools\fixtures\bootcheck.py --lib --fight --exe EXE --shots out\bc --tsv out\bc.tsv
```

- **prep**: bootcheck's card-library script (pass 1: field control C; pass 2: the box walk's
  first battle), then the same script again with `RG_SS=1` and a `--save-state` at the first
  fight-phase field (game mode 7/201) + 4: `out/fixtures/<exe-id>/fight/CARD_battle.rgstate`
  (+ `.json`). ~80 s per card; cached per exe.
- **fight**: one rg-game segment at a time (~1-3 s each) from the state; each segment ends with
  a memory probe and a screenshot and the next input is chosen (run at the nearest live enemy,
  sword attacks, potions through the battle menu when the leader's HP is low, leader switch when
  the leader is down, L1 to accept suggestions). Verdicts: won / lost / escaped / timeout /
  stuck / crash / hang. Outputs: `fight.tsv`, `route.txt` (replays the whole fight from the state
  with `play.py --input`), `result.json`, shots (`montage.py D`).
- **Memory probe** (one `RG_STATUS_DUMP`, pointer chains through RVAs from the exe's map, so any
  build works): CharaSys `D_004837C0` +0x14 -> party record manager (+0x8 pool), +0x18 -> party
  object (+0x18E leader id, +0x190 active[3]), +0x1C -> enemy object manager (+0x10 pool). Pools
  (`PoolGetUsedElem_36acb0`): +0x08 base, +0x10 stride, +0x14 count, +0x20 used bitmap. Records
  (party 0x4C8, enemies 0x410 bytes): +0xC chara id, +0x14 HP, +0x1C max HP. Positions from the
  action manager `D_004B8680` +0x20 (sorted DList, node +4 next, Chara at node +0x10: +0x64 yaw,
  +0x70 pos, +0x424 s16 id; party ids 0..9, enemies 128+), walked with `/4` hops. The party
  record HP follows the HUD only after the battle menu closes.
- **Battle controls** (retail "Basic Battle Controls" tutorial, seen on PCSX2): **X sword, SQUARE
  gun, CIRCLE jump** (docs/CONTROLS-AUDIT.md's "Square = attack, Cross = jump (inferred)" is wrong
  for the US build; the first route battle's SQUARE presses fired the gun). Battle phases
  (`BattleModeUpdate_280220`): 7/101-200 intro, 7/201 fight, 7/500 (results 7/504) and 7/4000
  won, 7/600 escaped, 7/700-701 lost, 7/2000 battle menu open (the action is paused).
- **Battle menu** (TRIANGLE): Abilities / Change Equipment / Items / Switch Characters, one page
  per active member (LEFT/RIGHT page; the panel sits over that member's HUD slot). The cursor
  wraps, remembers its row between openings, skips disabled rows (Items when nothing usable is
  left), and presses while the menu is still opening are lost: so the tool reads the highlighted
  row from the screenshot (`menu_row`, a blue bar; a downed member's page shows none) and moves
  one row per short segment. Leader down: the game prints "Jaster is down and cannot fight.
  Switch characters or revive the downed character." and keeps the menu open (CIRCLE does
  nothing, the downed leader's rows do nothing); RIGHT to a living member's page + Switch
  Characters makes that member the leader.

`bootcheck.py --fight` (library cards): after a passing check, prep + fight; the verdict is
reported (`fight:won` etc. in the summary / `--tsv`); only a crash, hang or refused state fails
the card (a lost battle is a balance result, not a port bug).

### Checkpoint (auto-battle, 2026-10-18 night)

`bootcheck.py --all --fight --shots` on `out/route5/exe3` (build/route3-i686 18:17: the -O2
re-ingested tree, RG_VU0_MODE=native, RG_NATIVE_ONLY=ON, RG_GAME_OPT=-O2, + the camera
override): **28/29 PASS** (factory FAILs: a new FACTORY fault of this tree, BRINGUP.md (f)).
Results `out/route5/final/` (`bc.txt`, `bc_rest.txt`, `bc.tsv`, shots, logs); fight dirs
`out/fixtures/<exe-id>/fight/<card>/`; contact sheet `out/route5/final/fights_sheet.png`.
**No crash and no hang in any of the 13 fights** (~55,000 battle fields in all).

| Card | Encounter | Fight | Fields | Killed | Heals |
| --- | --- | --- | --- | --- | --- |
| ch01_salgin | Cactulus x5 (Lv 2 Jaster + Hooded Man) | lost | 1,068 | 0/5 | 2 |
| ch02_juraika | Horrorwood x2, Blue Thunder | **won** | 3,240 | 3/3 | 7 |
| ch04_prison | Tarantula, Savage Dog (challenge "finish in 18 s with Simon alone" failed) | **won** | 2,284 | 2/2 | 0 |
| ch06_mines | Moleman x5 | **won** | 2,958 | 5/5 | 1 |
| ch06_vedan | Zombie x4 | **won** | 1,680 | 4/4 | 0 |
| ch07_rosa | Lord Bee + 4 others | **won** | 2,720 | 5/5 | 0 |
| ch08a_vedan | Vedabird x5 | lost | 3,976 | 0/5 | 7 |
| ch08b_juraika | Club Titan x2, Evil Monkey | lost | 4,570 | 1/3 | 8 |
| ch09_labyrinth | Rolling Stone x2, Dark Spirit x3 | lost | 3,588 | 0/5 | 8 |
| ch10_kuje | Sarvil x3, Yellowfly (4,500 HP each) | **won** | 4,138 | 4/4 | 2 |
| ch12_mariglenn | Manticore, Magic Priest, Luminous x2 | lost | 4,372 | 3/4 | 3 |
| ch13_mariglenn | Devil, Gold Mask, Phantom | lost | 1,232 | 0/3 | 2 |
| ghost_ship_ex | 3 (12,000+ HP each) | stuck (leader-switch loop, all but Jaster down) | 2,888 | 0/3 | 1 |

The other 12 library cards met no battle in the box walk ("no battle"); `save2_battle2` (the
scripted second battle) passes. Losses are balance results: the cards carry the developers'
start-state levels and a simple attacker (no abilities, no guarding, no dodging) loses to
groups that hit for 40-370 per blow. Known limits: no ability / skill use, no guard; potions
only (first item); the leader-switch loop can cycle when only a non-leader page is alive
(ghost_ship_ex). Earlier runs on the 15:03 exe (`out/route5/fights2/`, before the menu reader)
gave 3 wins; the cursor reader and the leader switch raised it to 6.

## Factory and Insectron drivers (`factory.py`, `insectrun.py`; 2026-10-25)

The FACTORY / INSMENU / INSECT overlays had only bootcheck's load milestones. Two closed-loop
drivers now play them to an end, and every run leaves a power-on **boot route** (boot script
+ the driver's input) that `routecmp.py` replays on two builds (RG_NATIVE_OVL ON / OFF,
native-only / oracle twin). Docstrings = full reference.

```powershell
python tools\fixtures\saveedit.py make factory_plans insectron_play      # the two cards (from cards/save2)
python tools\fixtures\factory.py run   --exe EXE [--out D]                # ~1-2 min
python tools\fixtures\insectrun.py run --exe EXE [--out D] [--title]      # ~6 min (a 4,600-field CPU battle)
python tools\fixtures
outecmp.py pair Doot_route.txt --card factory_plans --exe-a ON --exe-b OFF --out C
python tools\fixtures\hangsample.py PID                                   # where a hung rg-game spins
```

- **Cards.** `factory_plans` = save2 + flag 0x3E8 (Factory row) + the 72 "Obtained Factory
  Hint NNNN" story flags 1100..1171 (every production plan is known:
  `FactoryCompletionUpdate_3e7ae0` marks a plan record known when its story flag is set;
  `bit_flag_param_EN` names them) + 5 of each of the 50 materials (category 11), via the new
  `saveedit.py patch --add-item ID[:N]` (was in the usage text, not implemented).
  `insectron_play` = the insectron card's two teams with the new `--insect-formation`: insect
  i gets +0x18 / +0x21 = i and +0x20 / +0x22 = 1 (found by booting, not decoded). **With the
  plain insectron card only each team's crowned leader is placed and a CPU-vs-CPU Watch
  Battle never ends** (48,500 fields, two leaders keeping their distance; the stats, `@S` in
  the new team spec, make no difference); with the formation fields all ten insects play and
  the battle ends (2P wins at ~16,100, rematch prompt).
- **factory.py** (from the FACTORY-menu state at 4,400 of `boot_factory.input.txt`): floor
  (Place two Source Tables, Move one with UP x2 + R1 rotate, Remove one), User's Manual (two
  pages), plan (Blueprints -> 'Healing vial' -> Set -> Yes -> "Load a parts layout template
  similar to the selected production plan?" Yes -> "Clear out all the placed parts?" Yes: the
  game builds the plan's layout = 3 Source Tables, tubes, assembler, Completion Table), Set
  Material (Alchemy tab, the plan's three materials; "Select a source table" is closed loop:
  D-pad presses + CROSS until the material grid comes back with the slot's OK, detector
  `grid_open`), Run, Go Back -> "Halt factory operations?" Yes -> NORMAL -> field. Verdict of
  Run: **refused** ("The factory isn't ready yet. Is all the machinery connected to a power
  source? Are the routes properly connected?", detector `dialog_open`): the template has no
  power cords. (Power cords: solved 2026-10-25 soak2, `--cords`, see "Widened soak" below:
  the Run is then accepted and the line operates; no item produced yet, game rules.)
- **insectrun.py** (from the battle-start state at 11,500 of `boot_insectron.input.txt`):
  1,000-field segments without input until the STATUS game mode leaves 15 (battle end E),
  then at E + 1,600: rematch "No" -> "Thanks for watching!" -> INSMENU (ovl 6) mode list =
  done. `--title` goes on through Return to title to TITLE (hung until 2026-10-25, below).
- **routecmp.py**: one route on one exe with STATUS, the timing record (milestones) and the
  sym: state trace (`regions_symbols.cfg`, every 50 game VBlanks; `--ovl-regions BUILD` adds
  one `ovl:<name>` window per overlay data+bss, mapped through the arena or the active
  native module, trace_map.c); `pair` / `compare` classify two runs: identical (run hash =
  pad reads + audio output + kernel trace and clock, and the sym: trace agrees) /
  presentation / timing / state / crash. rg-game does not fold frames into the run hash
  (`display_hash_every` 0), so pixels are judged by the `--shots` hashes, listed separately.
  Caveats found on the way: a traced run (RG_TRACE_*) presents different frames at a given
  field than an untraced one (pacing), so compare shots only between runs of the same
  configuration; and the Set Material screen's button legend differs run to run on the
  same exe (a wall-clock animation), so those shots never match.
- **hangsample.py PID**: suspends each thread of a 32-bit rg-game a few times, reads EIP
  and the stack words in the image, symbolized from the map (WOW64 context from 64-bit
  Python). Found the hang below in one call.

### Results (2026-10-25, build/ovlcov-i686 ON + rg-game-oracle, build/ovlcov-off-i686 OFF; one tree)

Exes `out/ovlcov/on3`, `orc3`, `off3` (on2 / orc2 / off2: the same tree before the trace_map
fix, which touches only the trace recorder). Runs `out/ovlcov/` (fac_*, ins_*, cmp_*).

| Driver | RG_NATIVE_OVL=ON | OFF |
| --- | --- | --- |
| factory.py | 12 phases ok; picks UP 5 / LEFT 6 / RIGHT 11; Run refused (no power cord); NORMAL field at 11,500 | identical (same picks, phase ends, verdict; boot_route.txt byte-identical) |
| insectrun.py | battle 11,500 -> 16,100 (4,600 fields, 2P wins), rematch No, INSMENU at 19,000 | identical (battle end 16,100, same route) |

| Power-on replay (routecmp.py) | run hash | STATUS rows | milestones | sym: trace | shots | class |
| --- | --- | --- | --- | --- | --- | --- |
| factory boot_route, ON vs OFF (traced) | d0b24a339fa07cf0 both | 232 = | 35 = | 231 vbls identical | 4/10 differ: Set Material legend only, also differs ON vs ON rerun | identical |
| factory boot_route, ON vs OFF (untraced) | equal | = | = | - | same 4, same cause | identical |
| insect boot_route, ON vs OFF | af8a8594cd5865a5 both | 378 = | 39 = | 377 vbls identical | 6/6 equal | identical |

The golden-route lockstep (native-only vs oracle twin): docs/bringup/BRINGUP-HISTORY.md
2026-10-25 (overlay coverage).

**Hang (FIXED 2026-10-25, BRINGUP-HISTORY "2026-10-25 (stream close)"): Insectron "Return to
title".** INSMENU -> Return to title -> Yes -> "We look forward to your next battle!" -> game mode
3/100 (LoadingModeUpdate_285450) at ~19,620, then `GameSessionShutdown_1f5bf0` ->
`StreamMgrCloseAll` -> `StreamChanClose_1d6dc0` -> `SoundStreamSlotFree_1bd3a0` ->
`SoundStreamSlotShutdown_1bdfd0` spun forever: two port bugs in a row, (1) its kick
(`SoundRpcWorkerKick_1bd6a0`) signalled the driven stream-slot thread, which only runs at a
driver point the loop never reached (override: the kick ends in a driver point), (2) then
`EffTableDestroyAll_1a0240` spun: `HandleTableGet_1a1d50` was called without its handle in four
effect units (overrides; census `tools/bringup/protos_deficits.py`). Every game-session shutdown
takes this path. Now `insectrun.py run --title` reaches TITLE (ovl 2) at ~19,700 on the
native-only exe, the oracle twin and the twin under RG_IOP=hle RG_AUDIO=hle (insectrun keeps
one battle-start state per mode-switch set). The RG_IOP=hle fault in `EffResGetNameMaybe_1a83d0`
(native-timed route replayed on the hle twin, ~18,640) was bug (2): gone with the effect overrides,
back without them.

## Game over (`gameover.py`; 2026-10-25)

Every game session ends in `GameSessionShutdown_1f5bf0` (stream channels closed through the
driven stream-slot step, effect tables destroyed); Insectron "Return to title" is
`insectrun.py run --title`, the game-over path is this driver:

```powershell
python tools\fixtures\gameover.py make [--base ch01_salgin]     # card gameover_<base>
python tools\fixtures\gameover.py run [--exe EXE] [--then continue|none] [--press CROSS|NONE]
```

Card `gameover_<base>` = library card + party cut to its leader + every character's HP = 1.
`run`: `autobattle.prep` (box walk to the first encounter, state at the fight phase), no input
until the game mode leaves the fight (7/701 = lost), then one CROSS per 120 fields
("<leader> was defeated..." waits for a press) until the title overlay (ovl 2), then
CONTINUE -> slot 1 -> FILE 01 -> load -> recap (bootcheck.LOAD / RECAP relative to the title)
until field control (ovl 3, 6/100). Each post-loss segment's saves dir holds the card (a state
does not carry the memory card; with an empty one CONTINUE is missing and CROSS starts a NEW
GAME, which also works: opening movie, Rosa desert). 2026-10-25, build/sweep-i686: lost at
5,090, TITLE at 5,820, CONTINUE -> field control at ~10,780 (verdict `title+continue`, 26 s
from the cached battle state). Output `out/fixtures/<exe-id>/gameover/<card>/` (phases.tsv,
route.txt, result.json, shots).

## Long soak (`soak.py`: what a play-tester would hit)

`tools/fixtures/soak.py` plays every card for thousands of fields with scripted input and
collects crashes, hangs, soft locks, UBSan / stack-guard rows and heap damage (docstring =
full reference; added 2026-10-24 for the P5 gate):

```powershell
python tools\fixtures\soak.py run --exe EXE --out out\soak\D [CARD ..] [--fields 12000] [--seed 1] [--resume]
python tools\fixtures\soak.py report out\soak\D [more dirs]      # markdown: per-card table, findings, UBSan sites (new vs census/ub_ubsan_route.tsv)
python tools\fixtures\soak.py repro out\soak\D\findings\NNN      # rerun one finding's segment from its saved start state
python tools\fixtures\soak.py heap --exe EXE STATE ..            # dlmalloc walk of a state's game heap
```

- **Session per card** (default: the 25 library cards + save2 + factory + insectron): the
  bootcheck boot to field control, a save state there (RG_SS=1), then one rg-game segment at a
  time from the last state. One saves dir per session (card writes persist across segments).
- **Activities**: explore (one world heading per 160-240-field segment, camera-compensated with
  `navprobe.stick_for`, chosen by a visited-cell novelty score, banned for one pick after it
  failed to move the leader; CROSS now and then = examine / talk); every 6th activity a menu
  pass (TRIANGLE, DOWN x r to a main-menu row, a seeded random walk of DOWN / UP / LEFT / RIGHT
  / CROSS / L1 / R1 presses through its sub-screens -- item use, equipment, Revelation
  placements, Allies, Strategy, Recorder, System -- then CIRCLE x8, more CIRCLEs if still in a
  menu); on cards that spawn at a transporter (save2, alistia) one save to FILE 01 first, then a
  fresh boot from the written card (reload check); a battle (game mode 7) is fought with
  `autobattle.fight` and its results dismissed; a lost battle / title / a repeat stuck point
  restarts the session from its boot state; other modes (event, talk, loading) get CROSS every
  30 fields. factory: the boot_factory golden then the loop; insectron: boot_insectron then
  CROSS every 300 fields in 1,500-field segments (INSECT CPU vs CPU).
- **Checks per segment**: exit code / EXCEPTION (crash, symbolized), wall-clock timeout (hang;
  a timeout spent waiting for an rg_slots slot is retried), state / probe at the end field (no
  progress), log lines outside the known set (one finding per distinct line), UBSan rows
  (`RG_UBSAN_LOG` per card; a `-DRG_UBSAN=ON` exe), stack-guard rows (`RG_SBGUARD_LOG`; a
  `-DRG_SBGUARD=ON` exe), a **dlmalloc walk of the game heap** every 4th end state (`heapwalk`:
  chunk chain from `sbrk_base` to `top` read from the retail `av_` / params in the state's
  statics: sizes, free-chunk footers, no adjacent free chunks, top ends at sbrk_base +
  sbrked_mem; in-use bytes tracked per card), a menu pass that does not get back to the field
  (`menu-stuck`), a save that writes nothing, 8 segments with nothing changing (`stuck`).
- **Output** `D/<card>/`: `session.tsv` (segment, fields, kind, mode, map id, leader x/z, note),
  `segNNNN/` (input, log, last 3 states, menu shots), `battleNN/` (autobattle dirs),
  `ubsan.tsv`, `sbguard.tsv`, `summary.json`; `D/findings/NNN/` (finding.json, start state,
  input, log, route since boot, triage shots for stuck / menu / save findings);
  `D/summary.tsv`, `D/findings.tsv`.
- Cost: ~2 s per segment plus the battles (~3 s per 40-field autobattle segment); ~3-6 min per
  card at 12,000 fields on an idle machine. One rg-game at a time.
- Triage helpers: a crash / hang finding is replayed once from its start state with 16 shots and
  STATUS every 10 fields (`findings/NNN/shots/`); `findings/NNN/route.txt` + the card replays it
  from power-on (`run_from.py --boot-save CARD --input route.txt`, also on another exe of the same
  tree, e.g. the stack-guard one). Long events (40 advance segments with the frame still changing)
  end the session without a finding; the FACTORY is left through Go Back + "Halt factory
  operations?" Yes.
- Limits: cards are fixed story points (no story progression); exploration rarely leaves the
  spawn map (`--maps`: one card per jump point instead); autobattle uses abilities / items / the
  gun only with `--wide` and can loop on leader switching (a `battle-stuck`
  finding is usually that); an exe that cannot shoot after `--load-state` (before the 10-24 22:45
  runtime fix) has no frame hash, so long cutscenes read as `stuck`.

### Checkpoint (long soak, 2026-10-25)

Three passes over all 28 cards (BRINGUP-HISTORY "2026-10-25 (soak)"): -O2 native-only 346,235
fields (28 battles), UBSan 175,964 fields (179 sites, 88 not on the route census, triaged), stack
guard 134,554 fields (0 overruns). One port crash (FACTORY
-> Place: raw callback word, datareloc `_sub_` rule) and one UBSan `invalid_value` (SysMsgPost
`bool` byte, override) fixed; the reload check passed on both transporter cards; every game-heap
walk clean. Results `out/soak/{o2,ubsan,guard}`.

## Widened soak (`soak.py --wide --maps`, `soak.py fights`, `factory.py --cords`; 2026-10-25 soak2)

The first soak's limits (fixed story points, one map per card, no abilities, no factory
production, no story Insectron) widened with game data instead of hand-made input:

```powershell
python tools\fixtures\saveedit.py make --wide --maps                     # w_<library card> + m_<jump> cards
python tools\fixtures\soak.py run --exe EXE --out D --wide --maps --fast-boot --fields 5000 --map-fields 1200 [--resume]
python tools\fixtures\soak.py fights --exe EXE --out D2 [CARD ..]         # one --wide fight per w_ card (box-walk battle)
python tools\fixtures\soak.py coverage D [D2 ..]                          # zones per planet + battle tactic totals
python tools\fixtures\factory.py run --card factory_parts --plan healing_eq --cords --produce 3000 --exe EXE
```

- **Abilities in the cards** (`saveedit.py --abilities`, `--learn DATAID:ID,..`): the initial_status
  #106 lists are applied the way `CharaLearnAbility_3ad460` does (docs/SAVE-FORMAT.md "Abilities"):
  learned bit (chara_ability_param3 index) at payload +0x2DC, actives into the 10 equip slots
  (sub-chunk 6). The `w_` cards = every library card + `--abilities` + Burning Strike Lv1 (1341,
  which also sets flags 1005/1006 'Burning Strike Possible'). The plain library cards are unchanged.
- **autobattle `--wide`** (soak `--wide` turns it on): on a seeded schedule the battle menu's
  Abilities row (row k of the leader's list: actives and the combination attacks Fated Passion /
  Supernova / ..), Items (row k on the leader), a voluntary leader switch (next page + Switch
  Characters), the gun (SQUARE) every 5th segment and at range; ability cut-ins (game mode 10/2,
  ~280 fields) are counted and played through with face-button presses (Burning Strike chips);
  the battle menu's item screen (game mode 17/200 inside a battle) is backed out of instead of
  ending the fight. Result fields: ability_tries, cutins, items, lead_switch, gun, other_modes.
- **Map sweep** (`--maps`, cardlib `map_points()` + `MAP_EXTRA`): per planet a greedy
  farthest-point spread of the jump table's signboards / next-episode markers / bases / bridges /
  stations / ghost-ship floors (77 points), each its own `m_<jump>` card at the late story point
  (13020, + 14010 / 14030 on the ghost ships) with abilities; `--map-fields` per card.
  Coverage = planet zones (party +0xC, planet_zone_param_2_EN #403) at field-mode segment ends,
  now in session.tsv's map column (planet/area/zone) and `soak.py coverage`.
- **Walks** in `--wide` press CROSS every ~60 fields with p 0.5 (doors, shops, signboards, NPCs);
  a non-field mode that persists gets CIRCLE on alternate advance segments (shops / menus).
- **Game over** (`--wide`): the first lost battle per card is played on through the game over
  to the title (session shutdown) before the restart; `gameover` column = reached / tried.
- **`--fast-boot`**: one boot run with states before each recap CROSS (3790, 3890, ..), the
  session starts at the first one >= control + 20 (halves the boot cost; 25 s per map card).
- **Factory production** (`factory.py --plan --cords --produce`, docstring): power cords from the
  wall-socket stubs to each part's power point (part group +0x20 fine points; the last move must
  point INTO the part), floor edits (`floor_script`: remove / place / move in coarse cells, the
  list cursor and the R1 rotation persist), profiles `healing` / `healing_eq` / `freeze`.
- **Story Insectron venue** card `insect_story` (13020, jump 33, rank var 5 = 3, var 7 = 4, two
  registered teams): boots in the venue; talk sweeps reach only NPC talk (12/x).

### Results (2026-10-25 soak2; exes out/soak2/exe-o2 = build/soak2-i686, out/soak2/exe-ubsan = build/soak2-ubsan-i686)

Runs `out/soak2/{o2,ubsan,fights-o2,fac*}` (game-derived, not committed); `soak.py report D` /
`coverage D`; BRINGUP-HISTORY "2026-10-25 (soak2)".

| Pass | Cards | Fields | Battles | Abilities / cut-ins | Items / leader switches / gun | Findings |
| --- | --- | --- | --- | --- | --- | --- |
| -O2 `--wide --maps` | 25 w_ + save2 + factory + insectron + 77 m_ = 105 | 309,160 | 13 (4 won, 8 timeout, 1 ended in the item screen: tool, fixed) | 25 / 22 | 6 / 10 / 43 | 1 (tool: FACTORY exit, fixed) |
| UBSan `--wide --maps` | 97 (no MAP_EXTRA) | 211,047 | 11 | 26 / 23 | 3 / 14 / 44 | 2 (tool: FACTORY exit, fixed); 16 UBSan sites new to soak2 (triaged below) |
| -O2 `fights` (one --wide fight per w_ card) | 25 (13 with a box-walk battle) | 50,896 battle fields | 13: 4 won, 4 lost, 4 timeout, 1 stuck (leader-switch loop) | 32 / 30 | 12 / 10 / 69 | 0 |

- **Zones** (party +0xC at field-mode segment ends, -O2 pass): 39 distinct; planets 1-9: 31 of the
  36 listed (Rosa 8/8, Zerard 7/7, Vedan 4/4, Juraika 6/7 (no Rhyzas Swamp), Mariglenn 4/5 (no
  Palace Gate), Dorgenark 1/2 (no Captain's Cabin), Rose Nebula / Space read as the Dorgenark's
  deck zone 110), ghost ship EX 7 of 100 floors, Alistia 1/4; 4 zone transitions by walking.
- **Game heap**: 177 (-O2) + 134 (UBSan) dlmalloc walks, all clean.
- **Game over** (fights pass, lost battles w_ch04_prison / w_ch12_mariglenn): GAME OVER (11/0) ->
  loading (-1/-1) -> boot logos / story intro / opening movie, no hang, no crash (the session
  shutdown path the 10-25 stream-close fix covers; not reached by a test before).
- **Factory**: power cords placed by `--cords` power every part (part states 3 -> 5, `fparts.py`
  dumps) and the Run is accepted ("OPERATING"); soak2 produced nothing: the raw Healing-vial template
  stops with "Not all materials arrived at the assembler on time", the equalised layout (`healing_eq`)
  and Freeze defense with "There were improperly processed materials in the assembler" (no Athanor in
  the Place list). **Closed 2026-10-25 (cov3)**: "Factory production" below (Divine Blessing produced
  and in the inventory). No crash / hang in any factory run.
- **Story Insectron**: not reached in soak2 (no caged insects on a card). **Closed 2026-10-25
  (cov3)**: "Story Insectron" below (the Rank E final won from a card, rank reward granted).

**Found and fixed** (overrides, tested with altlink exes `out/soak2/alt-o2`, `alt-ubsan`, then in
`build/soak2-i686` for the gates):
- `UiPageScrollBarSized_2891e0` (override): a list that does not scroll divides by 0
  (`(x - end) / (hi - lo)`); the host's NaN reached `(s32)(22 + v * row)` in
  `normal_BtlChgMenuAbilityListCursorBobCb_502150` = INT_MIN: the battle menu's ability-list scroll
  thumb was drawn over the header instead of inside its track (UBSan float_cast, every w_ card that
  opened Abilities). The EE has no NaN: DIV.S by 0 = +-FLT_MAX, then 22 + MAX * 0 = 22. Shots
  `out/soak2/thumbm/crop_{exe-o2,alt-o2}.png`.
- `AiRouteMoveToPosMaybe_2beed0` (override): a waypoint kind of 4 indexes `thr[4]` / `thr2[4]` /
  `thr3[4]`; retail's frame (asm 002BEED0) puts element 4 on v250.x / thr[0] / v200.x, clang's
  layout on something else (ally route thresholds). Locals kept in retail-order frame structs.
- Tools: FACTORY exit is closed loop (`factory_menu_row`), autobattle backs out of the in-battle
  item screen (game mode 17/200) instead of ending the fight.

**Triaged, not port bugs** (UBSan sites new to soak2): extern / struct views shorter than the data
(`D_00480830[1]` and `D_00480680[4]` are aliases into the contiguous `D_00480390` blob,
`S2C0.arr[3]`, `Ai.info[4]`): same bytes as retail; `EvTargetSetGetTargets_336940` takes
`&NULL->sub` (address only); `factory_FactoryStep_5069e0` (override) `struct S` declared 16-aligned
over 8-aligned part groups (misaligned class; no aligned vector access seen at -O2; risk noted).

## Story Insectron (`insectstory.py`; 2026-10-25 cov3)

The tournament match in the Zerard stadium and its rank reward (`InsectBattleMatchUpdateMaybe_319800`
-> `InsectronRewardLookupMaybe_3e84f0`, the soak lane's override, until now verified by
construction only), played from a manufactured card:

```powershell
python tools\fixtures\saveedit.py make insect_final insect_final_s            # the two cards (from cards/save2)
python tools\fixtures\insectstory.py run --exe EXE [--card insect_final_s] [--out D]   # ~25-40 min
python tools\fixtures\insectstory.py replay D\boot_route.txt --exe EXE         # power-on replay + vars / reward
python tools\fixtures\evscan.py find 1574,1587                                 # which SB2 scripts call these event commands
python tools\fixtures\evscan.py dis "map\m04\m04.pac" m04.stb --around 1587 --func
python tools\fixtures\soak.py drivers --exe EXE --out D                         # insectstory + insectrun + factory production
```

- **Caged insects on a card** (docs/SAVE-FORMAT.md "Insects and cages"): inventory kinds 4 / 5 / 6 are
  0x1C-byte objects that point into the GameRec table (chunk 12: 15 insect, 3 trap, 3 rearing-cage
  records). `saveedit.py --section-insects 115` adds what the developers' start state 'Insectron
  E-5' (initial_status 115) gives: 3 Insector Traps, 3 Rearing Cages, 15 named insects in the cages
  (the 16th, Dark Emperor, does not fit, as in game), feed, the Insectron License; `--strong-insects`
  = level 5, stats 100, HP x3, attack / defense x4. Checked live: after CONTINUE the game's GameRec
  table equals the card's except the 15 re-resolved insect pointers and the ticking satiety timers
  (`insectstory.py` phase "gamerec"), and the team screen lists the card's insects.
- **The trigger, from the script data** (no input search): event commands 1574
  `EvCmdMenuInsectEntryOpen_25c3f0` and 1587 `EvCmdInvCountInsects_25c280` (table `D_0044D6F0`) are
  called only by `map/m04/m04.pac` m04.stb (`evscan.py find`, SB2 bytecode: 12-byte {op, a, b}, a
  native call = `PUSHIMM 1, ID` + args + `NATIVE argc+1`, `ScriptVmExec_173b00`). Routine 0xED04 is
  the receptionist (NPC 24228, "Announcer"), run by the talk dispatcher when var 121 = 3: var 6 = 0 ->
  "Would you like to enter the tournament?" -> at least 5 insects (`InvCollectInsects_3c4d90`: list
  0 + list 7) -> rank menu (sets var 6 and the fee var 29); var 6 != 0 -> "Continue from Rank X, Battle
  var7 + 1?" -> at least 5 insects -> the match. The NPC stands at (6881.09, -889.8, 3358.88)
  (`rc/param/zone/zl05_2_en.pac` ZL05_*npc.cfg.bin #101 / #102).
- **Cards**: `insect_final` / `insect_final_s` = save2 + section 13020 + `--section-insects 115`
  (`_s`: strong) + vars 5 = 1 (rank E), 6 = 1 (entered rank E), 7 = 4 (battle 5 = the final, the only
  one that pays), spawned facing the receptionist (`saveedit.INSECT_DESK`).
- **The match is played, not watched**: the story battle (INSECT, mode 0) gives the player's side to
  the pad (Move / Special Move / Parameters / Help / End Turn per piece, Attack when an enemy is in
  range). The driver reads the battle object every decision (`RG_STATUS_DUMP` of `*D_00482AF0`:
  pieces, 7 x 5 board, move / attack marks, cursor pages, command list, state / step stacks, side to
  move; layout in the docstring) and plays: each non-king piece attacks (king first, then the
  weakest) or moves toward the enemy king, then End Turn; the CPU plays its own side. Team: "Have your
  Insectors automatically selected?" Yes, Auto-Layout Yes, the default king.
- **Reward = retail's data and logic**: the table is `rc/param/purpose/insectron_2_en.pac`
  insectron_param_EN (#100 {rank key, 3 x (item, count)}; key 1 = Rank E: Battle Feed 16747 x5 /
  Sanchez Fruit 16731 x1 / none); retail's `InsectronRewardLookupMaybe_3e84f0` (asm 003E84F0: `lw
  8(a0); lw 0xA0; lw a0, 0xC; jr vtable[0x70]` with $a1 = the team key) = DataTableFindByKey on it, and
  `InsectBattleMatchUpdateMaybe_319800` takes pair k = 0 when var 6 >= var 5 (first clear), sets vars
  0x73 / 0x74 to item / count and adds the items, then rank var 5 = var 6 + 1 and vars 6 / 7 = 0. The
  stage's original code (before the soak lane's overrides) forced the record to NULL
  (`t = (InsectronRewardLookupMaybe_3e84f0(g), (s16 *)0)`), so a win paid nothing.

### Results (2026-10-25 cov3; exe `build/soak2-i686` = bootexe e110a68e153a92c6)

| Run | What | Result |
| --- | --- | --- |
| `out/cov3/story4` (`insectstory.py run`) | boot 3,750 -> talk (INSECT at 4,180, "it's the final round!") -> team 6,150 -> 3 player turns, enemy king KO'd -> field 18,480 | **won**; vars 5 / 6 / 7 = 1 / 1 / 4 -> 2 / 0 / 0, var 0x73 / 0x74 = 16747 / 5, Battle Feed 0 -> 5 in the live inventory; GameRec live = card (except pointers / satiety timers); 1,173 s |
| `story4/replay_fixed` (power-on replay, same exe) | the whole route from power-on | rc 0, same vars, Battle Feed x5 in the inventory (run hash 4e63ee519c0f13b7) |
| `story4/replay_prefix` (altlink exe `out/cov3/prefix`: the stage's original InsectBattleMatchUpdate / InsectronRewardLookup) | same route | rc 0, match won, rank 2, but vars 0x73 / 0x74 = 0 / 0 and no Battle Feed: the bug the soak lane's overrides fix |
| `out/cov3/story5` (final tool, the after-loop fix) | same as story4 to the battle end 18,480 (deterministic), field control 18,520 | **won**, same vars and Battle Feed x5; 2,041 s (rg-game slot waits) |
| `story5/replay_fixed` / `replay_prefix` | power-on replays of story5's `boot_route.txt` (ends 18,600) | fixed: 6/100, 16747 x5 in vars and inventory (run hash 3eb123b131a49f82); original stage code: 0 / 0, no Battle Feed, and one message box fewer after the match (no "obtained" line), so the route's last CROSS talks to the receptionist again (12/1) |

Notes: the policy needs the strong card (`insect_final_s`); with the section's own insect values
(`insect_final`) the same policy trades hits slowly (soak2-era stats: ~10 HP per hit, `out/cov3/story2`).
The after-battle loop must not press CROSS in field control: the receptionist stands in front of
the party (an early version re-entered the "Which rank will you enter?" menu; fixed, `story4_after`).

## Factory production (`factory.py --plan healing_ath --produce --save`; 2026-10-25 cov3)

`factory.py run --card factory_prod --plan healing_ath --cords --produce 1000 --save` (~4-7 min):
Healing vial -> "Success!" -> "Divine Blessing (Healing vial) production was a success!" -> "Obtained a
sample of Divine Blessing!", then exit to the field and a transporter save; the written card's
inventory has Divine Blessing (16589) +1 and Dreamflower Ash / Dream Mushroom / Hoho Bird Feather -2
each (result.json `inventory_delta`). Runs `out/cov3/factory/final`, `final_replay`.

- **Rules** (`FactoryProduceRun_505e00`, result codes in `fdump.py`): each material passes the machine
  of its class (item_param #4 field 4: alchemy -> Athanor, mechanical -> Disassembler, circuit ->
  Washer, gem -> Grinder, metal -> Smelter -> Form Press -> Cooler tube; raw at the assembler =
  0xE "improperly processed", a wrong class 8..0xD, metal not pressed / cooled 0x11 / 0x10); all inputs
  reach the assembler in the same tick (else 0x15 "not on time"; a part takes length x 30 ticks: tube
  / table 1, Athanor 6, Assembler III 8), so routes need equal length sums; Assembler I / II / III take
  1 / 2 / 3 inputs and plan types 2-4 check which input carries which material (0x13).
- **Why soak2 had no Athanor**: the Place list is the item-def table filtered by
  `ContainerViewItemFilterMatch_40c280`, not the inventory; Athanor / Assembler III (unlock groups
  34 / 35) appear only when unlocked (retail: by producing that part's own plan). Card `factory_prod`
  = factory_plans + `saveedit.py --unlock-group 34 --unlock-group 35`.
- `healing_ath` = template + one Athanor per route (outer tables moved down; all routes 9 units) + 8
  power cords, no demo phases (the input script is limited to 32,636 VBlanks from power-on,
  `src/host/host_script.c`). `fdump.py EXE STATE [--grid] [--defs]` dumps the live factory object
  (result code, material slots, part groups and cells). Power-on replay `factory.py replay
  out\cov3\factory\final\boot_route.txt`: rc 0, run hash 6fd8c7397564dc37 (exe out/soak2/gate). On
  success the game adds the product (`InvAddItemRepeat_3c47b0` in `FactoryProducePollResult_4f74d0`),
  consumes the materials and unlocks the product's group.

## Map check (`mapcheck.py`: is the map drawn?)

Automatic detector for the "missing map geometry" class (BRINGUP.md 2026-10-18 (g),
NATIVE-RENDER.md "Regression: missing map geometry"): characters and HUD draw, the map does
not (black void or the clear colour).

```powershell
python tools\fixtures\mapcheck.py --exe EXE [CARD ...] [--env K=V] [--tsv F]   # default: the 4 cards that lost it + ch08c_zerard
python tools\fixtures\mapcheck.py --exe EXE ch09_labyrinth --env RG_NR_VU=0   # the renderer gate (VU work dropped)
python tools\fixtures\mapcheck.py --score a.png b.png                          # just the score
python tools\fixtures\camprobe.py --exe EXE ch05_factory                        # field camera at control / field (collision check)
```

One power-on run per card (bootcheck pass-1 script to 4,710, shots every 50 fields); the
shot >= 40 fields after field control is scored by its **detail fraction** (8x8 blocks, at
640 wide, with luminance std > 1.5) and compared with the retail CONTINUE shot
`out/retail/cb1/<card>_control.png`: ratio >= 0.6 = DRAWN. Calibrated on the 15:03 exe, exe3
and retail: missing 0.18-0.48, drawn 0.95-1.1. ~25-80 s per card.

## Retail comparison (`tools/trace/cardboot.py`)

Every library card (and save2, factory) booted on retail PCSX2 through CONTINUE, screenshots at
the port's milestones, compared side by side:

```powershell
python tools\trace\cardboot.py ch09_labyrinth [CARD ...] --out out\retail\cb1           # plan lib
python tools\trace\cardboot.py factory --plan factory --out out\retail\cb1
python tools\fixtures\montage.py --pairs PORT_SHOTS_DIR out\retail\cb1 [--match REGEX] --out F
```

- **Card export**: the card folder goes through `tools/saves/ps2card.py export --format`, then
  cardboot **rewrites every page's ECC** (`reecc`). With ps2card's own ECC retail did not see the
  save (title menu without CONTINUE: the mashed CROSS started NEW GAME and ran into the first
  battle tutorial); with the rewritten ECC every card loads. The difference is the column-parity
  bit order: retail's mcman checks bits 0..2 = parity of the bits under 0x55, 0x33, 0x0F and bits
  4..6 = 0xAA, 0xCC, 0xF0; ps2card.py packs 0x55, 0xAA, 0x33, -, 0xCC, 0x0F, 0xF0 (`_colmask`).
  **Fixed 2026-10-18 (BRINGUP.md (g))**: `_colmask` uses mcman's order; test_ps2card.py pins it
  and compares every written page with cardboot's ECC; cardboot's default is now `--ecc ps2card`
  (no rewrite; retail boots ch01_salgin from the unmodified export, `out/mapreg/cb`);
  `--ecc mcman` still rewrites (also the erased pages' spare areas, which ps2card leaves 0xFF).
- **Event-driven boot**: retail is slower in places (title data sort, loads), so fixed-time boot
  scripts do not line up. cardboot installs input.py's hook with an empty table (unfrozen: a
  screenshot comparison needs no cycle determinism) and writes presses into the table a few
  VBlanks ahead of the game VBlank it polls over PINE, anchored on events: overlay `D_0047E254`,
  game mode / phase `D_004B51A0` / `D_004B51E0`. Plan `lib`: CROSS every 60 VBlanks until field
  control (6/100), then control C+40, TRIANGLE C+60, menu C+160, CIRCLE C+260, field C+340 (the
  port's bootcheck milestones). Plan `factory`: boot_factory's menu walk with menu_before, factory,
  factory_goback, menu_after, field_after shots. Each shot also records Camera0..5 (look/eye) in
  `<card>.json`. One PCSX2 at a time (refuses when a harness PID file is live); ~70 s per card.
- Port shots for the pairs: `bootcheck.py --lib --shots D` (same milestone names).

### Results (2026-10-18, retail vs build/route3-i686 15:03 exe; BRINGUP.md 2026-10-18 (f))

All 25 library cards + save2 + factory booted on retail with the same saves (no card refused).
Contact sheets: `out/retail/pairs_ctl_*.png`, `pairs_menu.png`, `pairs_save2.png`; retail shots
`out/retail/cb1/`.

- **Same on both** (no port bug): the magenta pillar in `ch09_labyrinth` (retail has it: the
  labyrinth's own glowing pillar); main-menu rows for every card (menu shots, row column diff
  equal across cards); after leaving the factory, rows 4/5 read "Battle Recorder" / "Frog Log"
  on retail too (`factory_menu_before` "? ? ?", `factory_menu_after` named, icons still dark):
  game behaviour, not stale textures.
- **Port bug 1, camera never collides with the map**: in about half of the areas the port's field
  camera stays at the default orbit (look-to-eye 120 units, +10 high) where retail's is pulled in
  and raised by walls / terrain (ch01_salgin 85, ch03_burkaqua 87, ch05_factory 4 units; the port
  even shows the camera behind a fence or outside a hut wall); open areas match exactly
  (ch06_vedan, eye identical to 0.1). Cause: adjacent locals passed as one box; fixed by override
  (BRINGUP.md (f)). **Verified** on exe3: control-shot cameras equal retail's in every area
  (`out/retail/pairs_exe3_ctl.png`; ch01_salgin and ch05_factory eyes equal to 0.1).
- **Port bug 2, Jaster renders without head and legs** (boots floating below him) on the 15:03
  exe, in every area and in save2 (a game-written save); exeF (13:53, build/battle-i686) drew him
  whole, retail draws him whole. A regression of the re-ingested tree; gone on exe3 (18:17).
- **Port bug 3 (exe2 17:45 and exe3 18:17, not on the 15:03 exe): map geometry not drawn** in
  ch06_vedan (sky only), ch09_labyrinth, ch12_mariglenn, ch13_mariglenn (black: only characters,
  HUD and a sliver of ground), field and battle alike; retail and the 15:03 exe draw the areas.
  Not the camera override (exe4 = exe3 relinked with the generated file: same). For the UB / -O2
  owner (BRINGUP.md (f)).

## Retail parity (`tools/parity/`)

The same scripted input on the port and on retail PCSX2, game state sampled once per game frame
on both, aligned on game frames and events, the first divergence per field reported. Finds
logic divergences (ABI / typing / float rounding) that a screenshot or milestone check cannot.

```powershell
python tools\parity\parity.py list                                   # scenarios, field groups
python tools\parity\parity.py run walk_save2 --exe EXE --out out\parity\w          # EE floats are the default since 10-24
python tools\parity\eelibm_check.py all          # src/crt/crt_eelibm.c vs retail (PCSX2 pairs + the retail code)
python tools\parity\eediv\listing.py KernelTanf_127ae0   # retail listing of a MAIN function (decomp objdump)
python tools\parity\parity.py port battle2 --exe EXE --out D         # port side only (multi-pass)
python tools\parity\parity.py retail battle2 --out D                 # retail side only (PCSX2)
python tools\parity\parity.py compare D [--groups chara,anim] [--shift 60] [--context 4]
python tools\parity\sweep.py --exe EXE --out D [--env K=V] [--skip-retail] [SCEN ..]   # summary.tsv
python tools\parity\fpcensus.py EXE      # float ops per game function (SSE single / double / x87)
python tools\parity\fpboundary.py EXE    # host functions called from game code + their float work
python tools\parity\rngtrace.py SCEN --exe EXE --dir D [--frames N]   # who calls Rand, per frame, port vs retail
python tools\parity\divclass.py D       # first divergences of a sweep by class (ulp / float / int / rng / timing)
python tools\parity\pairptr_census.py   # data words relocated as pointers that are packed numbers (link-layout bug class)
python tools\parity\datafix_packed.py   # writes the verified ones back as numbers (overrides/src/main_data)
```

- **Sampling point**: the entry of `GfxEndFrame_141c20` (once per game frame, after its logic).
  Port: `RG_BREAK` there + `RG_BREAK_SPEC` (the fields' pointer chains, SDUMP lines, any
  build with its .map). Retail: a probe.py-style trampoline at the same address that counts
  frames (FRAMECTR 0xE1000) and appends the field words (`probe.emit_log`, `W_ptr`/`W_abs`) to
  the ring at 0xA0000, drained from PCSX2's memory without freezing.
- **Fields** (`fields.py`, ~260): mode / phase / overlay, newlib RNG state (retail
  `_impure_ptr`+0xA8, port `rg_crt_rand_next`), frame time, pause; party records (HP, EXP,
  money, leader); the action manager's chara list (position, yaw, action, action timer,
  command masks +0x568 / +0x570, flags +0x3D0 / +0x3D8, motion phase) and each chara's motion
  player (clip frame, time, blend, rate); enemy records; cameras 0-1. Chains are retail
  addresses of MAIN globals (`@ADDR/hop..+off`); the port resolves the same `D_00xxxxxx`
  symbols from its map; floats compare bit-exact.
- **Input keyed by game frames**: retail drops a frame now and then (loads, the menu opening:
  frametime > 1), the port never does. Port: `RG_INPUT_KEY=frames` (script keys = hits of the
  first RG_BREAK site); retail: input.py's table indexed by FRAMECTR. PCSX2 runs with
  EECycleRate 3 and fast CDVD (`--ee-rate`) to drop fewer frames.
- **Scenarios** (`parity.SCENARIOS`): `walk_<card>` (card boot, field control, menu, walk, a
  box walk), `battle2` / `battle2_walk` (save2's scripted second battle with gun / sword
  patterns), `gun_route` (the route's first battle, golden from power-on on retail, the
  `battle` milestone on the port, VBlank keys). A plan is waits on events (with mashing) and
  presses / sticks at frame offsets; the port runs it in passes (one per wait), retail live.
  Plan actions must be >= 30 frames after a wait (retail sees the anchor a few frames late).
- Runtime: ~2-3 min port (passes from power-on) + ~80 s retail per walk scenario. One PCSX2 and
  one rg-game at a time.

Checkpoint / resume list (flip, EE libm, re-time, opt-in exact mode): BRINGUP.md 2026-10-19 (c),
"STATUS at wrap-up"; done 2026-10-24 (BRINGUP-HISTORY.md "2026-10-24") except the opt-in exact
build. Exact float model for parity builds: tools/parity/eediv (README in eediv_cc.py;
verified bit-exact on 113,903 retail libm calls).

- **EE libm check** (`eelibm_check.py`): `interp` runs the retail machine code of the libm
  (tools/parity/eediv/ee_interp.py: a small R5900 interpreter with the EE float model) on the
  113,903 PCSX2 pairs (113,903 / 113,903, 37 s); `vectors` makes 60,030 new references from the
  retail code (tanf / asinf / acosf / powf, large-argument sinf / cosf = KernelRemPio2f, edge
  cases); `c` builds `src/crt/crt_eelibm.c` plain (shipping: SSE under the chop MXCSR) and
  exact (eediv_cc.py) with a driver and compares. 2026-10-24: **exact build 100 %** on all
  173,933 references; plain build 32 % exact on the pairs, every miss 1 ulp (host CRT under
  chop: 30 %, misses up to several ulps). Work dir `out/eefpu/eelibm`.

### Results (2026-10-24 night, EE floats default; BRINGUP-HISTORY "2026-10-24 (night, parity2)")

Sweep `out/parity2/sw/summary.tsv` (exe `out/parity2/exe1`, retail rerun on the rebuilt cards):
identical fields 224-239/257 on 8 of 10 walks (10-19 chop: 111-239), rng never differs on 5
walks; no ABI / logic divergence. Left: EE float residue (spawn-height ulps, division rounded to
nearest on retail, adder bits) growing into collision-flag flips / rng after 290-690 frames
(opt-in exact model open), load timing (burkaqua: DynClothDefInit_169420's Rand draws 10 frames
earlier on the port), battle2 apart at its anchor.

### Results (2026-10-19, BRINGUP.md 2026-10-19 (c))

- Gun cadence 14 vs 16 VBlanks: EE float rounding (retail rounds toward zero, soft double too).
  `RG_EE_FPU=chop` gives 16 and makes the motion timers bit-exact with retail; **the default
  since 2026-10-24** (USER decision; `RG_EE_FPU=ieee` = the old host rounding, 14).
- Remaining float divergences with chop (open): division (PCSX2 rounds it to nearest), the EE
  adder's dropped bits, libm (fixed 10-24: retail fdlibm float in src/crt, within 1 ulp; exact
  only with the opt-in exact model), spawn heights; they grow into a collision-flag flip
  and an rng divergence after 120-350 frames of walking, so battles compared from a card boot
  start from different states. Sweep tables: `out/parity/sw1/summary.tsv`.

## Rewards and gun cadence probes (play-test 2)

```powershell
python tools\fixtures\rewards.py --exe EXE --boot-save save2 --input tools\trace\goldens\boot_save2_battle2.input.txt --fields 6900
python tools\fixtures\guncadence.py port --exe EXE                    # save2_battle2 fight
python tools\fixtures\guncadence.py retail-input --base tools\trace\goldens\newgame_battle.input.txt --at 24760 --out F
python tools\trace\probe.py --out R.jsonl --input F --fn Shot:0x229bc0 --stop-vbl 25700
python tools\fixtures\guncadence.py retail R.jsonl --at 24760         # same report for retail
python tools\fixtures\guncadence.py port-log LOG --at N               # a kept port RG_BREAK log
```

- `rewards.py`: party EXP (Chara +0x4B8, all ten records) and money (party +0x160) at every
  STATUS line (RG_STATUS_DUMP, RG_SS=1), one row per change; any exe with its .map.
- `guncadence.py`: SQUARE patterns (taps every 10 VBlanks, held 200, taps every 6) ->
  `CharaCmdShot_229bc0` entries (port: RG_BREAK; retail: probe.py `--fn`), per pattern the
  shot times, intervals and presses without a shot. The port's script keys are fields
  (game vbl = field - 33 on the route), retail's are game vbl: compare in one unit.
- 2026-10-24, default build (EE floats on): `guncadence.py port` gives a shot every **16**
  VBlanks in all three patterns (retail 16); with `RG_EE_FPU=ieee` 14 (out/eefpu/gun1, gun1i).

## bootcheck / run_from robustness (2026-10-19)

- `run_from.py` scratch run dirs are unique (`tempfile.mkdtemp`, time stamp kept in the
  name); they used to be named by the start second only, so two runs starting in the same
  second (another lane's bootcheck, consecutive passes) shared one dir: the second
  `copytree` failed at once ("FAIL (0 s)", exit 1) or one run's cleanup deleted the
  other's saves.
- `bootcheck.py` runs a private copy of the exe (`out/fixtures/runs/bootexe/<exe-id>/`,
  same content -> same exe id), so a relink of the build dir during a long `--all` cannot
  replace or lock the file under a later card; a run that exits within 20 s without one
  STATUS line keeps its log (`out/fixtures/runs/bootlib/<name>.early-exit.log`), prints
  the reason and is retried once.

## Determinism evidence

`python tools/fixtures/verify.py [--trace]` (after `regen.py --check 300 [--trace]`): for
each milestone N, run A = the power-on run (saved N and N+300, shot N+300), run B = load
N, run 300 fields, shot. 2026-10-17, exe `76ec8e866b39f03e`, `RG_GPU=hw`:

| N | run hash at N+300 (A = B) | frame hash at N+300 (A = B) | `port_trace.py compare --key vbl` |
| --- | --- | --- | --- |
| 1,500 | `a286f39ab1471fb5` | `c0a568381736f720` | IDENTICAL on all 60 common vbls (1470..1765) |
| 8,000 | `77380244a9cc6b0b` | `5ce0a612303a9693` | IDENTICAL, 60 vbls (7970..8265) |
| 23,000 | `04d73a2d3b29869b` | `8c4247c804bf87c3` | IDENTICAL, 60 vbls (22970..23265) |

(With `--trace` in both runs; the trace samples every 5th vbl, symbol regions of
`regions_symbols.cfg`. The run hash folds the kernel trace hash, audio, pad words and
virtual time every field, so equal hashes mean every field matched, not just the last.)
The same check without trace recording: see "Plain-mode check" below. The current set
(`out/fixtures/b6c31fc1b80fa62a`, a later relink) reproduced the plain-mode hashes exactly. Earlier smoke:
load at 600 (title movie playing) to 700 = power-on to 700 (run hash
`150486e8641d6978`, frame `5dd2b5ceb8f9658e`).

Save-state mode itself does not change a run: power-on to 1,800 gives the same run hash
with and without `RG_SS=1` (`ee00168d6c038032`). Note: recording a state trace
(`RG_TRACE_*`) changes the run hash (`a286f39a...` with trace), so compare run hashes
only between runs with the same trace setting.

Plain-mode check (no trace; the set regen.py makes by default), same exe: all three
milestones match on run hash and frame hash: 1,800 `ee00168d6c038032` / `c0a568381736f720`,
8,300 `38a34e56e200e9bc` / `d54e1bf161d98507`, 23,300 `25cb154cb7c2ec7e` /
`321fcbde88a5577c`. The frames at 8,300 and 23,300 differ from the traced runs' (the
trace recorder changes the run itself, not only the hash: a question for the trace
lane; it does not affect states, which compare like with like).

## Design

A state is the game at a field boundary (after `rg_runtime_run_field` returns, no guest
code running). It loads only into the same exe: the header stores a 128-bit hash of the
exe file; a load also refuses another address layout or another init.

| Section | Content | Why raw works |
| --- | --- | --- |
| `ram` | the game heap (crt0's one allocation, newlib malloc's arena; format 2, docs/NATIVE-CPU.md section 8) | reserved at a fixed address |
| `statics.map` + `statics` | every `.data/.bss` byte owned by GAME or MODEL code | exe linked `/DYNAMICBASE:NO`; ranges from `rg-game.map` |
| `heap` | the **state heap**: every allocation by game or model code, allocator metadata included | fixed address; init allocations happen in the same order every run (fingerprint checked) |
| `fibers` + `stack` xN | fiber slot table, each guest stack from its saved esp to the top | own fiber backend with stacks at fixed addresses |
| `hook:<name>` | per-subsystem blobs | the hook keeps the loading process's host bindings |

- **Classification from the link map** (`src/savestate/ss_map.c`): bare objects are GAME
  (and `rg_ovl_arena`); `rg_*` port libs are MODEL; HOST (never restored, their mallocs go
  to the CRT heap): SDL/CRT/C++ runtime, `rg_host`, `rg_gpu`, `rg_settings`, `rg_trace*`,
  `rg_native_fs*`, `rg_ps2_cdvd`, `rg_savestate`, `rg_game_main.c.obj`, `rg_slots.c.obj`,
  `rg_game_ss.c.obj`, `mccard.c.obj`, `gs_async.c.obj` (GS worker thread), census and
  recorder objects. HOOK: `runtime.c.obj` (R) and the kernel's `_K`. Per-symbol HOST rows:
  callbacks host code installs into models (the timing record's movie / overlay / pad /
  CDVD hooks, the spin reporter). The map's timestamp must equal the PE TimeDateStamp.
- **State heap** (`ss_heap.c`): `malloc/calloc/realloc/free/strdup/_strdup` are replaced
  for the whole exe; a new allocation is routed by its caller (`__builtin_return_address`
  in the map's `.text` ranges): HOST code gets the UCRT heap (`_malloc_base` & co.), all
  other code the state heap. Free/realloc go by the pointer's address. `_msize` is NOT
  replaced (libucrt's `msize.obj`, pulled in by the CRT's own `_recalloc`, defines it with
  `_msize_base`; nothing in the port calls it). 16-byte headers record the allocating
  caller (audits), 152 bins, coalescing, 1 MB commit steps. An init fingerprint (hash of
  the alloc/free sequence until `rg_ss_mark_init_done`) must match saver and loader.
- **State region** (`rg_ss_init`, first thing in main when states are asked for): game
  heap `RG_CRT0_HEAP_ALLOC` (26.7 MB) at 0x0A000000, heap start 0x0A000200 (crt0 takes it via
  `rg_crt0_set_ram_provider`; it was a 32 MB EE-RAM image before format 2), fiber
  arena 64 MB at 0x0C100000, state heap 256 MB reserved at 0x20000000. Fixed addresses:
  "lowest free" differed run to run (0x05900000 vs 0x05940000). If a range is taken the
  lowest free one is used and a warning says this process's states load nowhere else.
- **Fibers** (`src/ps2/kernel/fiber_arena.c`): own i686 switch (ebp/ebx/esi/edi, TEB SEH
  head, StackBase, StackLimit, DeallocationStack, x87 CW, MXCSR on the fiber's stack);
  `fiber_win32.c` delegates to it when an arena is set. 64 KB uncommitted guard per slot;
  a load commits each saved fiber's whole slot. Created-but-never-run fibers are saved
  too (their first-switch frame). `fa_entry` wraps the thread in
  `__try/__except(UnhandledExceptionFilter)`: clang accepts it on i686-msvc, and a fault on
  a guest fiber reaches rg-game's crash report (seen during bring-up of this lane).
- **Hooks** (one per subsystem, `rg_ss_add_hook`; `can_save`, `pre_save`, `save_size`,
  `save`, `pre_load`, `load`, `post_load`):
  - `kernel` (`kstate_ss.c`): restores K, keeps this process's scheduler fiber,
    observers, devices, pacing/trace/violation hooks and run-control config; refuses
    another VBlank line, kcall cost, EIE model or stack size.
  - `runtime` (`runtime.c` `rg_runtime_ss_*`): saves started/finished/last_rc, the stats
    (run hash continues), VU0/VU1 and VIF0/VIF1 (keeping this process's VU block config;
    a fresh translation cache). pre_save drains the GS worker and syncs the GPU renderer;
    pre_load stops the worker and detaches the renderer; post_load clears the GS model's
    host side (async, hooks, recorder), re-attaches the renderer (re-upload of local
    memory) and restarts the worker. Refuses to save during a GS recording or census.
  - `movie` (`src/movie/mv_game.c` `rg_movie_g_ss_*`, registered by `rg_game_ss.c`): the
    playing movie's decoder file position; after a load both files are reopened (the
    movie structs come back raw from the state heap). Saving during a movie works (the
    title milestone is over the attract movie).
- **Services that need nothing**: rg_fs (sync reads, handles are mount indices), RNG
  (static in rg_crt), the overlay arena, hwbus/IOP/SIF/sound statics, the input script
  (keyed by game vbl, loaded by the loader), cards (host; fresh scratch dir).
- **File format** (`ss_core.c`): header (magic `RGSTATE1`, format version 2 since
  2026-10-18: the `ram` section is the heap allocation, version-1 files are refused with a
  "regenerate" message; build id, addresses,
  fingerprint, `rg_ss_meta`: field, game vbl, kernel vblank/now, run hash, note, input,
  header hash), page-elided sections with a hash each, trailer `RGSEND!!`. **A load reads
  and verifies every section before writing anything back.** `tools/fixtures/fxlib.py
  peek()` reads the header without rg-game.

### Audit (`RG_SS_AUDIT`)

Lists words of the saved memory (changed MODEL/GAME statics, state heap chunks, fiber
stacks; game RAM with `=2`) that point into CRT-heap blocks, grouped by owner. A real hit
is a host pointer inside saved state: fix it with a policy row in `ss_map.c` or a hook.
It is a heuristic: the CRT heap sits around 0x01Cxxxxx, inside the value range of VU
microcode, SPU/IOP RAM and GS local memory, so data buffers (`snd_srv g_state`,
`gs_create` = local memory, `iop g_ram`) show up as false positives; static words still
equal to the exe image are skipped. The determinism check is the real proof.

### Adding a subsystem (D9 native services)

A native subsystem that replaces a model registers its own hook before
`rg_ss_mark_init_done` (from rg-game's `rg_game_ss_before_init`, as the movie hook
does): save its game-visible state, rebuild its host resources (devices, threads,
files) in `load`/`post_load`. If its code allocates host resources with malloc, put its
library on the HOST list in `ss_map.c` (or keep the host part in a HOST object) so those
blocks stay out of the state heap. As models leave the executable, the raw sections
shrink; the format and hooks stay.

## Tests (`ctest -L fixtures`)

`tests/fixtures/` (needs the rg-game target built and `data/`; software GS, so no GPU
needed): `fixtures.save` (power-on 120 fields, states at 60 and 120),
`fixtures.roundtrip` (load 60, run to 120: run hash = the power-on run's), and WILL_FAIL
controls `fixtures.refuse.corrupt` (one flipped byte mid-file), `.truncated` (last 4 KB
cut) and `.foreign` (build id rewritten with a valid header checksum): each passes only
when rg-game refuses with exit 3, the expected message and no field run. 5/5 pass in
~5 s (`ctest -L fixtures -j1` in build/fixtures-i686); the logs in
`tests/fixtures/work/` show the three refusals ("section ram fails its checksum",
"truncated section fibers", "saved by a different build").

## Files

| File | What |
| --- | --- |
| `src/savestate/rg_savestate.h`, `ss_internal.h` | API (init, hooks, save/load/peek, audit) |
| `src/savestate/ss_map.c` | map + PE parsing, classification policy tables |
| `src/savestate/ss_heap.c` | state region, allocator, malloc interposition |
| `src/savestate/ss_core.c` | file format, `rg_ss_save/load/peek` |
| `src/savestate/ss_hooks.c` | kernel + runtime hooks, `rg_ss_audit` |
| `src/ps2/kernel/fiber_arena.[ch]`, `kstate_ss.c`, `ps2k_ss.h` | fiber arena + kernel hook |
| `src/runtime/runtime.c` (`rg_runtime_ss_*`), `crt0.c` (`rg_crt0_set_ram_provider`) | runtime hook, RAM provider |
| `src/movie/mv_game.c`, `mv_dec.c`, `mv_audio.c`, `mv_service.c` | movie hook (file reopen) |
| `src/game/rg_game_ss.[ch]` | rg-game CLI (`--save-state`, `--load-state`, `RG_SS`) |
| `tools/fixtures/build.ps1`, `fxlib.py`, `regen.py`, `run_from.py`, `verify.py` | build, set generation, start-at-milestone, determinism check |
| `tools/fixtures/play.py`, `montage.py`, `relink.py`, `tapsearch.py` | route segments from a state, contact sheets, fast relink with replaced objects, stick-tap search |
| `tools/trace/goldens/newgame_save2.input.txt`, `boot_save2.input.txt` | the route (fxlib.GOLDEN); booting its save |
| `tools/trace/goldens/newgame_save1.input.txt`, `boot_save1.input.txt` | the previous route (history) and its save |
| `tools/fixtures/saveedit.py`, `bootcheck.py` | save editor (docs/SAVE-FORMAT.md; `make` = the manufactured + library cards), boot-fixture smoke test (`--lib` / `--all`, two-pass for library cards, symbolized crashes) |
| `tools/trace/goldens/boot_factory.input.txt`, `boot_insectron.input.txt` | manufactured-save boots: FACTORY; INSMENU + INSECT |
| `tools/fixtures/steer.py`, `tools/trace/navprobe.py` | closed-loop `#!stick` steering; leader / camera / objective-marker probes |
| `tools/fixtures/cardlib.py`, `gamedata.py`, `cfgdump.py`, `rgdata.py` | the card library; archive / .pac reader; CfgVm .cfg.bin disassembler; parsed game tables (initial_status, phases, planetarea, map jumps, items, levels, flag names) |
| `tools/fixtures/mapcheck.py`, `camprobe.py` | "is the map drawn?" detector (detail fraction vs retail shot), field camera probe at the card milestones |
| `tools/fixtures/soak.py` | long soak over every card: explore / menu passes / saves / autobattle fights from chained states; crash, hang, soft-lock, UBSan, stack-guard and game-heap (dlmalloc walk) checks; findings with repro states ("Long soak") |
| `tools/fixtures/autobattle.py` | auto-battle: battle state of a card (`prep`), closed-loop fight (`fight`), memory probe (`probe`); `bootcheck.py --fight` |
| `tools/fixtures/factory.py`, `insectrun.py` | FACTORY gameplay driver (floor actions, plan + layout template, closed-loop Set Material, Run verdict, halt -> NORMAL) and Insectron driver (CPU-vs-CPU INSECT battle to its end -> INSMENU); both write a power-on `boot_route.txt` ("Factory and Insectron drivers") |
| `tools/fixtures/soak.py` (`--wide --maps --fast-boot`, `fights`, `coverage`), `cardlib.py` (`w_` / `m_` cards), `saveedit.py` (`--abilities`, `--learn`, `make --wide --maps`), `factory.py` (`--plan --cords --produce`) | the widened soak ("Widened soak") |
| `tools/fixtures/insectstory.py`, `evscan.py` | story Insectron driver (card -> receptionist -> team -> the match played from memory probes -> rank reward -> field; `boot_route.txt`, `replay`) and the SB2 script scanner / disassembler (which `.stb` calls an event command, routine + callers) ("Story Insectron") |
| `tools/fixtures/fdump.py`, `factory.py` (`--plan healing_ath --save`, `--until`, `--no-demo`), `saveedit.py` (`--unlock-group`, `--section-insects`, `--add-insect`, `--strong-insects`), `soak.py drivers` | factory production ("Factory production"), insects and cages on a card, the driver pass |
| `tools/fixtures/routecmp.py` | one route on two builds: run hash, STATUS, milestones, sym: trace (+ `--ovl-regions` overlay windows), classification identical / presentation / timing / state / crash |
| `tools/fixtures/hangsample.py` | EIP + stack sampler of a running 32-bit rg-game (where a hang spins), symbolized from the map |
| `tools/trace/cardboot.py`, `tools/fixtures/montage.py --pairs` | retail (PCSX2) boot of a card through CONTINUE with event-driven presses and milestone shots (ps2card ECC as exported; `--ecc mcman` rewrites it); port vs retail side-by-side sheets |
| `tests/fixtures/` | ctest label `fixtures` (`fixtures.saveedit`: the editor on a synthetic save) |

Shared-file wiring: top `CMakeLists.txt` (`add_subdirectory(src/savestate)`, and
`tests/fixtures` after the game link), `cmake/game_link.cmake` (`rg_savestate`,
`rg_game_ss.c`, `/DYNAMICBASE:NO`), `src/ps2/kernel/CMakeLists.txt`, `fiber_win32.c`
(delegation), `rg_runtime.h`, `rg_game_main.c` (5 small call sites).

## Limitations

- i686 Windows only (the Linux ucontext backend would need arena stacks).
- A state is valid for one exe only; any rebuild needs `regen.py` (~3.5 min for the full
  set with the 10-18 native build, was ~11 min; `--only title,field` is ~20 s).
- Saver and loader must use the same init-relevant options: `RG_GPU` kind (the set
  records it; default hw), `RG_GS_ASYNC`, `RG_CDVD_MODEL`, same `data/`. A mismatch is
  refused with a message naming the fingerprint.
- Not combinable with host diagnostics that hold files in model statics during the save
  (`RG_GS_REC`/`RG_PERF_CENSUS` are refused; `RG_SND_LOG`, `RG_VIF_DUMP` are not checked).
  `RG_TIMING`/`RG_TRACE_*` are fine on the loading side (their hooks are kept).
- GPU renderer at scale > 1: the load re-uploads local memory, so upscaled render
  targets restart from native resolution (only tested at scale 1).
- Card state is not in the state; the CLI does not check that no card file is open.
- Game-save fixtures exist since 2026-10-18 (`--boot-save save1`, above). The card files
  are not in save states: see "Scratch saves dir".
- Software GS (no `RG_GPU`): a state loaded in Salgin faulted in the GS worker (BRINGUP.md
  2026-10-18); the sets are made with `RG_GPU=hw`.
