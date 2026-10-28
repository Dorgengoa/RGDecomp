# Published snapshot (the pin)

**`game/` is pinned to the published decomp** (`PIN_SOURCE` / `PIN_REV` / `PIN_TREE` in
tools/ingest.py). It replaces the interim replay `b09ccfa1` (SNAPSHOT-INTERIM.md).

| | |
|---|---|
| repo (git dir) | `../RGDecomp/.git` (work tree `../RGDecomp`) |
| commit | `675c07feec314d493f9cc3d51f511bc7eb6ca07d` on `refs/heads/main`, "Rogue Galaxy matching decompilation", 2026-10-12 09:21 -0400 |
| tree | `460f59203d957c85b74cb184af1f5b75a49ac0a6` |
| files | 28,630 (src/main 17,679, src/main_data 6,306, src/overlays 2,274, asm/overlays 2,299, config 19, include 14, scripts 28, docs 2, handoff 2, asm/main.s, ...) |
| ingested `game/` | 26,292 files, tree sha256 `1e0aa7b8b95fd4697d1db328573044cde4c01f5c57bb61e1b0ec48711aaac557` |

That repository belongs to the session that publishes the decomp. The port only reads
git objects from it (`rev-parse`, `ls-tree`, `cat-file`, `show`, `grep` at the commit);
nothing is ever written there. Its HEAD is an unborn branch, so every tool names the
commit explicitly (`PIN_REV`, or `rev` in `game/SNAPSHOT.txt`), never HEAD. The stale
`../RGDecomp/.git` (one LICENSE commit, 88f5c9b) is not used.

## Checking another copy against the pin (one command)

Git tree ids hash content only, so any clone, fork or later push of the decomp holds
exactly the pinned files when its commit has tree `PIN_TREE`:

    python tools\ingest.py --compare-tree <repo>[@<rev>]

prints `IDENTICAL` (exit 0) or the A/D/M path list and counts (exit 1). It is read-only on
`<repo>`. Use it before moving `PIN_SOURCE` to, e.g., a GitHub clone: if the tree is
identical, change `PIN_SOURCE`/`PIN_REV` only and `game/` will not change (ingest writes 0
files).

History: before the publishing session committed, a robocopy of the uncommitted work tree
(08:26-08:40, 28,630 files) was read for the comparison below. The official commit's
blobs under `src/ include/ config/ asm/overlays/` (28,591 paths) are byte-identical to
the hashes taken from that work-tree read, and `asm/main.s` is the same blob. The scratch
copy was deleted once the commit existed (no port-side commit was needed).

## Differences from the interim snapshot `b09ccfa1`

Counted path by path (blob ids) over `src/ include/ config/ asm/`:

| | Interim | Published | Note |
|---|---|---|---|
| Function sources `src/main` | 17,679 | 17,679 | **0 changed, 0 renamed, 0 added, 0 removed** |
| Overlay sources `src/overlays` | 2,280 | 2,274 | 6 non-unit probe files dropped (`tiprobe.c`, `timini.c`, `i_probe.c`, `nmprobe.c`, `nmprobe.c.r4`, `ixprobe.c`) + `src/al_probe/alprobe.c`; never ingested. 4 insmenu units changed in a header comment only (`../work/BIN/...` -> `retail/BIN/...`) |
| Unit lists | | | `cunits.txt`, `ocunits/*`, `hosted.txt`, `toolchain.txt` identical; `units.txt` differs in comments only (same symbol list) |
| `config/*.symbols.txt` | | | main/title: one comment line each (local paths removed) |
| `src/main_data` | 6,306 | 6,306 | 646 files changed: extern declarations re-sorted (no effect after protos/datareloc, 37 game files differ), and **7 code entries with no C** are spelled `func_<ADDR>` instead of a guessed name (below) |
| Removed config | | | `arity.txt`, `arity_inferred.txt`, `names.txt`, `renames.txt`, `libnames.txt`, `queue.txt`, `cunits_pending.txt`, `pending/`, `*.bak17`, **`<image>.yaml` (6)** |
| Removed asm | | | **`asm/matchings/main/` (17,946 per-function listings)**, `asm/overlays/{launcher,viewer}.s` |
| Unchanged | | | `asm/main.s` (same blob), `asm/overlays/<ov>/` listings/data/bss, `include/`, `SCUS_974.90.lcf`, `config/data2c.json`, `config/hosted.txt` |

The 7 renamed no-C entries (data2c `function_entries`, "code-port obligation"):
`CharaFindNextLevelRowFromCur_3ab200` -> `func_003AB200`, `ModelObjExUpdate_1b02c0` ->
`func_001B02C0`, `TaskStepJudgeObject_3135c0` -> `func_003135C0`, `KCopyBody_11fed8` ->
`func_0011FED8`, `KCopyBody_120748` -> `func_00120748`,
`MpegParsePicSpatialScalableExt_10fdd8` -> `func_0010FDD8`,
`MpegParsePicTemporalScalableExt_10fde8` -> `func_0010FDE8`. None of the old names is
used by game C or by port code; all 7 were fatal-stub rows in `missing/UNBOUND.tsv`,
which now carry the new names.

## Tooling changes (generic: both snapshot layouts work)

| Where | Change |
|---|---|
| `tools/ingest.py` | Pin = git dir + commit + `PIN_TREE`; `--compare-tree REPO[@REV]` (above). `CONFIG_COPY` entries are optional (the arity tables are only read by `tools/census/proto_conflicts.py`). |
| `tools/stages/protos.py` `snapshot_addr_table` | MAIN's retail listing comes from per-function `asm/matchings/main/<fn>.s` when the snapshot has them, else from the combined `asm/main.s` split at each `glabel` (`split_listing`). Rules that read it: `addr-alias` (interior `alabel func_X` entries) and `missing-entry` / passthrough / def-widen gating. Checked on `b09ccfa1`, which has both: 17,731 of 17,732 named listings parse to identical instruction/label lists (the exception, `CharaFindNextLevelRowFromCur_3ab200`, has no C), the interior-entry tables are equal (57/57), and re-ingesting `b09ccfa1` with the new code gives a byte-identical `MANIFEST.tsv`. |
| `tools/gen_overlay_registry.py` | Without `config/<ov>.yaml`, the overlay layout (text vram, data file offset, bss size) is read from `asm/overlays/<ov>/data/<ov>_data.data.s` (first line's offset/VRAM columns) and `<ov>_bss.s` (`.space`). Equal to the yaml values for all five overlays of `b09ccfa1`. |

## Re-pin result

- `tools/ingest.py`: 0 missing / 0 duplicate / 0 multi-source / 0 unregistered; units
  main 17,709, title 97, insmenu 365, normal 659, factory 409, insect 744; data 6,306;
  1,068 files excluded as asm (as before). Every stage census equals the interim run except
  protos `addr-alias-unresolved` 33 -> 40 (sites 28,075 -> 28,082): the 7 renamed entries,
  which have no MAIN symbol to alias to. 46 files written, 2 removed (`config/arity*.txt`); a second run writes 0.
- `tools/ingest.py --check`: 26,290 manifest rows, 0 problems; overrides 103 files,
  0 problems.
- Overrides (103 files): **all kept, 0 renamed, 0 dropped, 0 re-hashed**. Every replaced
  `game/` file is byte-identical to the interim one (the function sources did not change,
  and no stage output for them changed), so every recorded SHA-256 is still current.
  `overrides/PORT_PROVIDED.tsv` (3 rows): paths unchanged, kept. `missing/`:
  `MainSinit_469180.c` kept (the published decomp still has no C for the two `__sinit`
  bodies inside D_00469140). `missing/UNBOUND.tsv`: 7 rows renamed (above), 107 rows total.

## Build, link, tests, boot (fresh build dir `build/clean-i686`)

Configured from scratch (`tools/build.ps1 -BuildDir build\clean-i686 -Clean`), then
`cmake --build build\clean-i686 --target all rg_game_objs rg-game -- -k 0`. The tree also
holds the settings/input layer and GPU work that other sessions landed the same morning.

- **Build:** 25,653 steps, 0 failed; all game objects compile.
- **Link:** `rg-game.exe` links with **0 undefined, 0 duplicate** symbols
  (`RG_GAME_FORCE_UNRESOLVED=OFF`); the 7 renamed UNBOUND stubs (`func_003AB200`, ...)
  are in `rg-game.map`.
- **ctest** (`-j8`, `RG_DATA` set): **393 / 394 pass**. The suite grew from 361 to 394
  (settings/input and GPU tests added by other sessions). The one failure,
  `gpu.scale2.rtt_formats` (2x internal resolution, bloom downsample: 95.4 % of target
  pixels exact, tolerance 0), is deterministic, also fails when run alone, and is a synthetic
  GPU test that uses no game code: it is in the GPU lane's in-progress work, not the re-pin.
- **Boot, no input** (`--headless --fields 4000`, `RG_STATUS_EVERY`): TITLE overlay
  (`D_0047E254 = 2`) at field 39, title movie from field 287 (vbl 250) and again from field
  1067 (vbl 1030), title menu (NEW GAME / CONTINUE / OPTIONS) drawn at field 1500, 4000 fields,
  no fault, exit 0.
- **Boot, golden input** (`tools/trace/goldens/newgame_battle.input.txt`): NEW GAME loads
  NORMAL (`D_0047E254 = 3`, sysmode 0) at field 2107 (vbl 2070); the opening story screen
  (starfield, empty message window) through 6000 fields, no fault, exit 0. Scripted input
  still drives the game with the new live-input layer present.
- **Same behaviour as the interim build:** the STATUS line of every field 1..2300 of the
  golden run, and every 100th field of the 4000-field no-input run, is identical between
  this `rg-game.exe` and the interim-pin `build/link-i686/rg-game.exe` (0 differing lines).

Logs: `out/reclean/` (ingest, build, ctest, boot).

## Open

- `gpu.scale2.rtt_formats` (above): GPU lane.
- `rg-game` does not read the settings registry yet (docs/SETTINGS.md, "rg-game ...
  doesn't do this yet"); unchanged by the re-pin.
- Everything open in LINK.md / BRINGUP.md is unchanged: the published snapshot has the same
  function C, so the 107 UNBOUND stubs, the 232 `missing-zero` arguments, `hw-word` data and
  the empty NORMAL message window are all still there.
