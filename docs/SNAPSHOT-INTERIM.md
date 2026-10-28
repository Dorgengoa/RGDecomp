# Interim snapshot (port ingest unblock)

**Superseded (2026-10-12):** `game/` is now pinned to the published decomp `675c07fe`
(SNAPSHOT-CLEAN.md). This page is kept as the record of the interim pin.
**Not the official snapshot.** A local REPLAY of decomp `main` onto `naming`, built
so the port can link against MAIN-100%-C + data2c before the official replay lands.
Replace it with the official commit as soon as that exists.

| | |
|---|---|
| repo | `out/snap-repo` (local clone of `../RGDecomp`, never pushed) |
| branch / commit | `port-interim` @ `b09ccfa1359e336e72f14be48bf32214cbc9654f` |
| parents | naming `2efa6b43` + main `d784320c` (merge commit, tree = replay result) |
| ingest dry-run | `out/game-interim/` (26,293 files), log `out/ingest-interim.log` |

## How it was built

`d784320c` was fetched from naming's `refs/remotes/origin/main` (the clone's own
`origin/main` is naming's stale local `main` = `5abebede`, not usable).

    git read-tree naming; git merge --no-commit -s ours d784320c
    git read-tree --reset d784320c; git checkout-index -a -f
    git checkout naming -- NAMING.md config/names.txt scripts/{rename,rerename,sortsrc,names_merge,naming_verify,nm_refine,nm_wave}.py
    python scripts/rename.py --apply      # 19,722 entries, 40,557 files edited, 39,392 renamed
    python scripts/sortsrc.py --apply     # 19,953 moves, 271 to src/main/sdk
    (both re-run as dry runs afterwards: 0 edits / 0 moves)

No `rerename.py` step was needed: `names.txt` already carries the final names (rerename
rewrites it in place), and main's new sources only use `FUN_`/`func_` tokens.
`naming_verify.py` (remote build) was not run, so the images were NOT rebuilt/relinked.

## Verification

- rename.py validation: 0 errors -> no guess-vs-retail collisions (every `names.txt` old
  symbol is still in scope after main; no new name clashes with a main unit name).
- cunits/ocunits: main 17,709 / title 97 / insmenu 365 / normal 659 / factory 409 /
  insect 744; every symbol has a source file except the 30 hosted guests (static in
  their host, per `config/hosted.txt`). 0 `FUN_` left in cunits; 4 overlay `func_`
  units are unnamed in naming too.
- diff vs naming `2efa6b43`: 6,696 paths (A 6,526 / M 154 / D 16) vs main's own
  6,686 (`817e31bc..d784320c`). After mapping names back to `FUN_`, every path but two
  has a basename main changed. The two (naming-only edits the replay drops):
  `scripts/i_olink.py` (chunked-scp WinError 206 fix) and `dump.txt` (stray 78 KB dump).
  Neither is read by ingest.
- `include/libvu0.h` present.

## Data sources

`src/main_data/`: 6,306 files = 6,305 `.c` (`data2c_<ADDR>.c` per span, `data2c_bss.c`,
`data2c_ov1..7_bss.c` overlay reservations) + `generated.h`. Data objects keep their
`D_xxxxxxxx` names (6,112), plus `data2c_gap_*` (128), `data2c_fragment_*` (31),
`jtbl_*` (12) and 14 VU-microcode blobs still named `func_<ADDR>`. The renaming only
touched function-pointer initialisers and `generated.h` externs (837 files). No overlay
data dirs (main only).

## Ingest dry-run result

`python tools/ingest.py --source out/snap-repo --rev b09ccfa1 --out out/game-interim`
(`--out` is supported). All units resolved, 0 missing, 0 dupes; data=6,306; 1,068 files
excluded as asm (5 game, 213 library, 850 sdk). Exit 1 only because of the override check:
96 of 193 `overrides/` entries are STALE (their recorded base hash no longer matches the
ingested file, e.g. the `Vec*_1cbxxx` units that main de-asm'd). They must be re-based
when moving to this snapshot or to the official one.

## Likely differences from the official snapshot

- Its commit hash and merge message will differ; it may keep the `i_olink.py` fix and drop `dump.txt`.
- It may delete/edit `names.txt` lines or run a fresh fold; this one uses naming's `names.txt` unchanged.
- It will have been rebuilt and relinked byte-identical; this one was not.
