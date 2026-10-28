# Toolchain

PLAN.md D1/D2: i686 (32-bit) first, Clang + CMake + Ninja.

## What is installed, and where

Nothing is installed system-wide and nothing is on PATH; `tools/build.ps1` wires it up.

| Tool | Version | Location | Source |
| --- | --- | --- | --- |
| LLVM/Clang (clang, clang++, lld-link, llvm-ar, llvm-rc) | 23.1.3 | `../tools\llvm` | official `clang+llvm-23.1.3-x86_64-pc-windows-msvc.tar.xz` (github.com/llvm/llvm-project releases), extracted |
| Ninja | 1.13.2 | `../tools\ninja\ninja.exe` | official `ninja-win.zip` (github.com/ninja-build/ninja releases) |
| CMake | 3.31.7 | `../tools\cmake-3.31.7-windows-x86_64` | portable zip (already present) |
| MSVC x86 CRT/libs | 14.29.30133 | VS 2019 Build Tools | existing install, used for its x86 libs only |
| Windows SDK | 10.0.19041 | `C:/Program Files (x86)/Windows Kits\10` | existing install (found by vcvars via the registry) |
| Python | 3.10 | `python` | existing, runs `tools/ingest.py` |

The VS 2019 `VC\Tools\Llvm` folders hold only clang-format/clang-tidy (the clang
compiler component is not installed), so the official LLVM release is used instead.
The original archives are kept in `../tools\dl\`.

## Canonical commands (Windows)

```powershell
# 0. (re)generate game/ from the pinned snapshot; verify it (and overrides/)
python tools\ingest.py            # the pin: PIN_SOURCE/PIN_REV in ingest.py (LINK.md)
python tools\ingest.py --check

# 1. configure + build every module and test into build\i686-windows, run rg-smoke/u128/vu0
powershell -ExecutionPolicy Bypass -File tools\build.ps1 -Clean

# 2. the whole test suite (all modules), or one module by label
$ctest = "../tools\cmake-3.31.7-windows-x86_64\bin\ctest.exe"
& $ctest --test-dir build\i686-windows -j8 --output-on-failure
& $ctest --test-dir build\i686-windows -L spin          # labels below

# 3. compile ALL of game/ (OBJECT libraries, not linked yet) + error census
python tools\gameerrors.py            # -> build\i686-windows\game_compile_errors.tsv
```

Test labels (`ctest -L <label>`): `port` (smoke, u128, vu0), `kernel`, `sif`, `cdvd`,
`vu` (VU1 + VIF), `gs`, `dmac`, `spin`, `protos` (PROTOS.md), `padmc`, `host`, `settings` (SETTINGS.md), `input` (INPUT.md; both need `RG_HOST`), `runtime` (RUNTIME.md; needs
`RG_HOST`), `movie` (MOVIE.md; the `real_*` and glue tests skip without `RG_DATA`), `trace` (TRACE-PORT.md; the demo tests need `RG_HOST`). Every test carries exactly one
label. `cdvd-realdata-tests` skips (exit 77) unless `RG_DATA` is set (and
`dmac.vif1_vu1_retail` when its retail fixture is missing). `src/extract` (`rg-extract`) is a separate,
standalone CMake project (`cmake -S src/extract`, see EXTRACT.md), not part of this build.

`game/` targets (`cmake/game.cmake`, all `EXCLUDE_FROM_ALL`, so step 1 does not compile
the ~18.6k game files): `rg_game_main`, `rg_game_title`, `rg_game_insmenu`,
`rg_game_normal`, `rg_game_factory`, `rg_game_insect` (OBJECT libraries, one per image)
and the umbrella `rg_game_objs`. Build one directly with
`cmake --build build\i686-windows --target rg_game_objs -- -k 0` from a vcvars x86 shell.
The source list is generated at configure time by `tools/gamesrcs.py` from
`game/MANIFEST.tsv` (kind `unit`/`data`; an `overrides/<path>` replaces `game/<path>`),
so configure never globs `game/`. `MANIFEST.tsv` is a configure dependency; re-configure
after adding an override.

Game-only flags (target `rg_game_flags`; `tools/syntaxcheck.py` uses the same): `rg_flags`
+ `-include port/prelude.h -I include -I game/include`, `-w -ferror-limit=0
-Wno-return-mismatch`, and for C `-Wno-int-conversion -Wno-incompatible-pointer-types
-Wno-incompatible-function-pointer-types -fgnu89-inline -Wno-implicit-function-declaration`
(why: PROTOS.md, `cmake/game.cmake`).

## Build (Windows)

```powershell
powershell -ExecutionPolicy Bypass -File tools\build.ps1          # configure + build + run rg-smoke
powershell -ExecutionPolicy Bypass -File tools\build.ps1 -Clean   # from scratch
```

`build.ps1`:

1. strips the `"` characters embedded in the user PATH (they break `vcvarsall.bat`),
2. runs `vcvarsall.bat x86` from VS 2019 Build Tools and imports `INCLUDE`/`LIB`,
3. configures `build\i686-windows\` with Ninja and `cmake/toolchain-i686-windows-clang.cmake`
   (clang targeting `i686-pc-windows-msvc`, linked by `lld`, static release CRT),
4. builds, then runs `rg-smoke.exe`, which must print `sizeof(void*)=4 ... PASS`.

Compile flags (PLAN D2) live on the `rg_flags` interface target in `CMakeLists.txt`:
`-m32 -msse2 -mfpmath=sse -fwrapv -fno-strict-aliasing -fno-delete-null-pointer-checks -O1`.

`build/` is gitignored. `compile_commands.json` is written there.

## Linux

`cmake/toolchain-linux-i686.cmake` (details, packages, status: [LINUX.md](LINUX.md)):
clang `-m32` targeting `i686-linux-gnu`, non-PIC/non-PIE, lld when present. Native on
Linux/WSL with a 32-bit multilib:

```sh
tools/build-linux.sh        # -> ~/rgport-build/linux-i686: configure, build, rg-smoke, ctest
```

Cross from Windows (compile + link check only; nothing runs) against a Debian i386
sysroot, into `build\linux-i686`:

```powershell
& $cmake -S . -B build\linux-i686 -G Ninja -DCMAKE_MAKE_PROGRAM=../tools/ninja/ninja.exe `
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-i686.cmake `
  -DRG_LINUX_SYSROOT=../tools/sysroot-i386-bookworm -DCMAKE_BUILD_TYPE=Release `
  -DSDL_UNIX_CONSOLE_BUILD=ON
..	ools
inja
inja.exe -C build\linux-i686
```

`cmake/toolchain-i686-linux-clang.cmake` is kept as an alias. The D3D11 GPU backend and
its `gpu` tests are Windows-only and are skipped on Linux.

## Game source (`game/`)

`game/` is generated, never edited:

```powershell
python tools\ingest.py                     # the pin (SNAPSHOT-CLEAN.md)
python tools\ingest.py --source <repo> --rev <commit> [--out <dir>]
python tools\ingest.py --check             # verify game/ against MANIFEST.tsv
python tools\ingest.py --compare-tree <repo>[@<rev>]   # same tree as the pin?
```

The pin is the published decomp, commit `675c07fe` in the git dir
`../RGDecomp/.git` ([SNAPSHOT-CLEAN.md](SNAPSHOT-CLEAN.md)). Ingest reads
only git objects at `<commit>` (never the source working tree). Only
`game/MANIFEST.tsv`, `game/SNAPSHOT.txt`, `game/EXCLUDED.tsv` and `game/PROTOS.tsv` are
tracked; the ~68 MB / ~20k source files are gitignored and regenerated.

Ingest runs the port transform stages stage-major, in this order: `int128`,
`gccvarargs`, `vu0asm`, `vu0bind`, `asmexclude` (`tools/portxform.py`), `ovlsyms`
(`tools/stages/ovlsyms.py`, OVERLAY.md: `<ov>_` prefix on overlay data names), `datareloc`
(`tools/stages/datareloc.py`, [LINK.md](LINK.md): MAIN data C for the host), `protos`
(`tools/stages/protos.py`, PROTOS.md: writes `game/include/port/game_protos.h` and
`game/PROTOS.tsv`), `dialect` (`tools/portxform.py`: C++ unnamed-type externs get a tag,
prototype-scoped struct tags get a forward declaration, GNU lvalue casts are rewritten),
`devirt` (`tools/stages/devirt.py`, DEVIRT.md: dummy virtual classes -> `__vptr` + slot
thunks, C linkage for game symbols; writes `DEVIRT.tsv`, `DEVIRT_FLAGS.tsv`), `spin`
(`tools/stages/spin.py`, SPIN.md) and `hwaccess` (`tools/stages/hwaccess.py`, HWBUS.md;
last, writes `HWACCESS.tsv`). Generated outputs get MANIFEST rows
of kind `generated`. Output is deterministic: a second run writes 0 files. Exit status is
non-zero when a stage reports errors (e.g. an unmatched spin row) or an override is stale.
It also writes `game/EXCLUDED.tsv`. Game code compiles with
`-include port/prelude.h -I include -I game/include`; see
[PORT-HEADERS.md](PORT-HEADERS.md). `python tools/syntaxcheck.py` runs
`clang -fsyntax-only` over the whole compile set.
