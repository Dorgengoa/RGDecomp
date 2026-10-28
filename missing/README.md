# missing/

Game functions that the pinned snapshot **calls but does not define** (no
`game/` file holds them), written from the retail listing so the game links.
Like `overrides/`, this is derived from the copyrighted game and is **not**
covered by the repository's CC0 dedication.

- **Path:** `missing/<relpath>` is where the function would live under
  `game/` (e.g. `missing/src/main/container/NameTableNodeSetImage_15a640.c`).
- **Header:** `/* rg-missing: <symbol> (retail <image> <address>, size <n>)` plus
  why, and how it was checked.
- **Build:** `tools/gamesrcs.py` adds each file to the image of its directory.
  Once a re-ingested snapshot defines the same symbol (the file stem, or
  `FUN_<address>`, in a `game/MANIFEST.tsv` symbols column) or has a file at the
  same relpath, the stand-in is skipped and configure prints
  `missing/<relpath> is now defined by the snapshot; skipped (delete it)`.
  Then delete the file.
- Not an override: there is no `game/` file to replace, so there is no
  SHA-256 header and `tools/ingest.py --check` does not look here.

| File | Callers | Expected in |
| --- | --- | --- |
| `src/main/sys/MainSinit_469180.c` (`MainSinit_469180`, `MainSinit_469190`) | MAIN's static-ctor table D_0046F9C0 entries 0 and 1 (bound by the datareloc stage, docs/LINK.md) | a snapshot with C for the `__sinit` bodies inside D_00469140 |
| `src/main/model/ModelObjExUpdate_1b02c0.c` (`ModelObjExUpdate_1b02c0`, forwarder `func_001B02C0`) | Character2 vtable per-frame update (data2c function entry) | a snapshot with C for 0x1B02C0 (retail asm only at 675c07f) |
| `src/main/sys/TaskStepJudgeObject_3135c0.cpp` (`TaskStepJudgeObject_3135c0`, `func_003135C0`) | task table (data2c function entry) | C for 0x3135C0 |
| `src/main/ui/LiveTalkStep_321240.c` (`LiveTalkStep_321240`) | every field frame (data2c function entry) | C for 0x321240 |
| `src/main/ui/UiNineSliceSpritesLayoutMaybe_3930d0.c` (`UiNineSliceSpritesLayoutMaybe_3930d0`, `func_3930D0`) | insect menus (`func_3930D0`, an interior-entry spelling) | C for 0x3930D0 |
| `src/main/chara/func_003AB240.cpp`, `func_003AB220.cpp`, `CharaFindNextLevelRowFromCur_3ab200.cpp` (+ `func_003AB200`) | Chara vtable entries (data2c function entries) | C for 0x3AB200/0x3AB220/0x3AB240 |

Dropped: `NameTableNodeSetImage_15a640` (the interim snapshot defines it as C in
`src/main/gfx/`).

`UNBOUND.tsv`: symbols rg-game links against fatal stubs (`tools/gen_unbound.py`,
docs/LINK.md "Unbound symbols"); delete a row once something real defines it.

The 7 rows above marked "data2c function entry"/insect menus were drafted from `asm/main.s@675c07f`
and checked byte-identical with mwcc against retail (method: out/missing-staged/README.md;
integrated 2026-10-12, their UNBOUND.tsv rows removed: 113 -> 106 lines).
