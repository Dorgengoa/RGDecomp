# Publishing a player build

How a play-test build becomes the public branch tree and player zip, with no game content
and nothing that identifies the machine or its user. First done 2026-10-28 for 1028a.

## One command

```
python tools/release/make_release.py --tag TAG --exe build/ptTAG-i686/rg-game.exe \
    --map build/ptTAG-i686/rg-game.map --setup build/release-tools/rg-setup.exe
```

Output `out/release/publish/` = the branch tree: `README.md`, `QUICKSTART.md`, `LICENSE`,
`THIRD_PARTY_NOTICES.md`, `THIRD_PARTY_LICENSES.txt`, `release/RogueGalaxyPC-TAG-win32.zip`,
`release/SHA256SUMS.txt`. Docs come from `tools/release/template/` (`@TAG@`, `@DATE@`);
update the README's state / issues / planned lists from BRINGUP.md and P6-STATUS.md first.

The zip is one folder `RogueGalaxyPC/`: `Setup.exe`, `rg-game.blank`, `rg-game.fill`,
`QUICKSTART.txt`, the README and the licenses. Player flow: unzip, drop the `.iso` in,
run `Setup.exe` (unpacks `data/` with rg-extract's code, rebuilds `rg-game.exe`), run
`rg-game.exe` (finds `data/`, `saves/`, `settings.ini` beside itself).

## No game content: blank + fill

`tools/release/blankexe.py` zeroes every exe byte that equals the retail files: pass 1
compares each address-named data symbol (`D_X`, `data2c_fragment_X`, `<ov>_D_X`) with
SCUS_974.90 / BIN/<OV>.BIN; pass 2 zeroes any run of >= 8 bytes shared with the ELF, an
overlay BIN or an IOP module. `rg-game.fill` lists (exe offset, file, file offset, length)
plus both SHA-256 values, no content; the round trip is checked. 1028a: 56,353 runs,
181,756 bytes. `rg-setup` (`src/extract/setup_main.cpp`, target `rg-setup`) applies it on the
player's machine and refuses a result whose SHA-256 differs.

## Leak gate (make_release fails on any hit)

Every tree file and every zip member is scanned for:
- retail bytes: a 16-byte window with >= 8 distinct values found in the ELF, an overlay BIN
  or an IOP module. Windows also present in `build/release-tools/crtref/out/crtref.exe`
  (built from no game code, same C/C++ runtime) count as library text;
- identifying text: user name, profile path, computer name, git user.name / user.email and
  the port's absolute path and drive, read from the environment at run time.

## Building the tools

`rg-setup` / `rg-extract`: i686 clang, static CRT, own dir `build/release-tools`
(`python tools/playtest/vcrun.py build/release-tools -- cmake --build . --target rg-setup`;
configure with the i686 toolchain file, `-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded`).
`crtref`: `build/release-tools/crtref` (same flags).

## The source tree (same branch)

`tools/release/make_source.py` (maintainer-only, not published: its rewrite rules name the
build machine's folders) turns this checkout into the branch tree, merged with the release
folder above:

- files: everything git sees, minus stray build dirs, binaries and caches, plus all of
  `game/`, and `pregen/overlay-gen/` (a build's generated overlay registry, used by
  `src/ps2/overlay/CMakeLists.txt` when the snapshot repo is not there);
- data: every value in `game/src/main_data`, `overrides/src/main_data` and
  `pregen/overlay-gen/ovl_native_gen.c` that equals the retail bytes at its address becomes a
  placeholder; `pregen/DATAFILL.tsv` lists each file's SHA-256 once filled.
  `tools/gamedata_fill.py --data data` puts the values back from the developer's own disc
  (2026-10-28: 6,145 files, 55,770 placeholders, every file byte-identical after filling);
- paths: machine paths become repo-relative or workspace-relative (`../tools`, `../work`,
  `../RGDecomp`, README "Workspace layout"); the build scripts themselves default to
  `<repo>/../tools` (`RG_TOOLS`, `LLVM_ROOT`);
- the port's own README moves to `docs/PORT-OVERVIEW.md`; the root README is the release
  README plus `tools/release/template/DEVELOPERS.md`;
- leak gate: binary files on the 16-byte rule above; text files fail on a retail run of 48+
  bytes (shorter matches are names, paths, save ids and SDK messages the code needs); the
  decomp's own C (`game/src/main`, `overlays`, `include`, `config`) is public already;
  identifying text and any drive path other than generic `C:` locations fail.

Verified 2026-10-28 by copying the tree outside the workspace, filling it from `data/` and
building it with `build_playtest.py`.
