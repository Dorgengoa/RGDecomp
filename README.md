# Rogue Galaxy PC port

A native Windows port of *Rogue Galaxy* (PlayStation 2, North America, SCUS-97490 v1.01).
It is not an emulator. The game's own code comes from the matching decompilation of the
retail executable and is compiled for the PC. The PS2 hardware, operating system and sound
system are replaced by native PC code: a Direct3D 11 / Vulkan renderer, a native audio
engine, and native file, controller, memory-card and movie services.

**You need your own copy of the game.** This branch and the download contain no game
content: no art, sound, music, movies, text or game data, and no bytes taken from the
game's executable. The first-run setup reads everything it needs from your own disc image.

- **Play it:** download `release/RogueGalaxyPC-1028a-win32.zip` and follow
  [QUICKSTART.md](QUICKSTART.md). In short: unzip it, put your `.iso` in the folder, run
  `Setup.exe` once, then run `rg-game.exe`.
- **Build:** 1028a (2026-10-28).

## Current state

The port is **playable but unfinished**. Expect bugs; please report them with the steps
that led there.

- The whole game is compiled natively: all game code from the decompilation, the five game
  overlays (title, story, Factory, Insectron, Insectron menu) and the parts of the Sony
  libraries the game uses. No emulation code is linked into the shipping executable.
- Tested through automated runs on every build: new game to the first save (title,
  opening movie, first field, first battle, town, save point, saving), booting saves from
  every chapter, maps, battles, game over, the shop, the Factory and Insectron.
- Play-testers have played from the start through the early boss fights. **A complete
  playthrough has not been confirmed yet.** Later chapters are covered by the automated save tests only.
- Windows 10 or 11, 64-bit, with a Direct3D 11 or Vulkan graphics card. The executable is
  32-bit; a 64-bit build and Linux are planned.

## Features added over the original

**Display and graphics**
- Window, borderless fullscreen (F11 or Alt+Enter) or exclusive fullscreen; resizable
  window; VSync.
- Internal resolution 1x to 8x, or matched to the window.
- Widescreen: 4:3, 16:9, 16:10, 21:9 or automatic, with a widened view, HUD and menus
  anchored to the screen edges, and movies kept at their own aspect ratio.
- Anti-aliasing (FXAA, 2x to 4x supersampling), texture filtering (original, bilinear,
  nearest), sharpening, CRT / scanline filter, brightness and gamma.
- Frame rate: original, 30, 60, 120, 144 or uncapped, with optional interpolation for
  smoother motion above 30 fps (off by default).
- Direct3D 11 (default) or Vulkan.
- FPS counter.

**Controls**
- Keyboard, mouse and any SDL-supported gamepad, with rebinding in the menu (several
  bindings per action).
- Dead zones, sensitivity and inversion per stick; mouse camera; a walk key.
- PC-style or original camera direction on the right stick.
- Hot-plugging controllers and switching devices mid-game; button names in the settings
  menu follow the device you use (PlayStation, Xbox, Nintendo, keyboard).
- Optional compensation for the game's own stick dead zone (a gameplay option, off by
  default).

**Audio**
- Master, music, effects, voice and movie volumes.
- Output device selection, switching live, and falling back when a headset is unplugged.
- Keep playing or mute when the window loses focus.

**Saves and loading**
- Memory-card saves as files in `saves\`, written crash-safe, with automatic backups.
- No disc loading delays.

**Settings menu**
- In-game settings overlay: F1, or hold Back + Start on a gamepad for one second.
- An "Original" preset that restores the PS2 look and behaviour.
- Settings are saved in `settings.ini` next to the game.

## Known issues

- No complete playthrough has been confirmed yet (see above).
- Fixes not yet confirmed by a player: platforms made by the monography shot in an
  early boss fight vanished at once (fixed in this build); menus and tutorials changing
  the aspect ratio; hitches where audio and video stop together; stripes in shadows at
  some internal resolutions.
- Saving can cause a short slowdown and an audio hiccup.
- Closing a shop runs at about 15 fps for half a second.
- The anisotropic filtering setting has no effect yet.
- Exclusive fullscreen has no resolution or refresh-rate picker; the monitor setting
  shows a number, not the monitor's name.
- The bloom, depth-of-field and motion-blur toggles, draw distance and shadow resolution
  in the menu are placeholders.
- Movie audio runs at the disc's 48,048 Hz clock; long movies may drift very slightly.
- Windows SmartScreen warns about the unsigned executables (choose "More info", then
  "Run anyway").
- If the game crashes, `rg-game-crash.txt` and `rg-game-crash.dmp` appear next to it.
  Please include them in a report.

## Planned

- A confirmed full playthrough, with automated runs covering every chapter.
- Display: exclusive-mode resolution and refresh picker, monitor names, more frame-rate
  caps (165, 240, match display), a save-folder setting.
- Saves: import of PCSX2 memory-card saves from the menu.
- Graphics: anisotropic filtering, toggles for bloom, depth of field, motion blur and
  flashing effects.
- Accessibility: reduced camera shake, subtitle and UI scale, colour-blind-friendly
  markers.
- Gameplay options (off by default): text speed, battle speed-up.
- A 64-bit build, Linux and macOS.
- Later: HD texture packs and modding support; optional ray-traced shadows and ambient
  occlusion.

## How the download avoids shipping game content

The game executable is built from code compiled out of the decompilation, but it also
needs the game's data tables (numbers, names and parameters stored in the retail
executable and overlays). Those bytes are **not** in the download. The packaging step
compares the built `rg-game.exe` against the retail files and zeroes every byte that
matches them, leaving `rg-game.blank`. It writes `rg-game.fill`, a table of positions:
for each zeroed run, which retail file and offset to copy it from. The table holds no
content.

`Setup.exe` checks that your disc image is the supported one (SHA-1), unpacks its files
into `data\`, copies each run back from those files into `rg-game.blank`, and checks the
result's SHA-256 before writing `rg-game.exe`. A different disc or a damaged download is
refused, so nothing half-built is ever run. The game itself reads only `data\`, never the
disc image.

## Supported disc

| | |
| --- | --- |
| Title | Rogue Galaxy (USA) |
| Serial | SCUS-97490, version 1.01 |
| Image | 6,967,721,984 bytes, SHA-1 `87377e721be58e8b6a5a7501721563500d237df7` |

Other regions and versions are not supported yet; `Setup.exe` names the disc it found.

## License

The port's own code and documentation are dedicated to the public domain under
[CC0 1.0](LICENSE).

CC0 does **not** cover the game code compiled into `rg-game.exe`. That code is decompiled
from, and derived from, *Rogue Galaxy*, a copyrighted game by Level-5 and Sony Interactive
Entertainment, and no rights to it are granted. *Rogue Galaxy* is a trademark of its
owners. This project is not affiliated with or endorsed by them.

Third-party libraries keep their own licenses: see
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md) and `THIRD_PARTY_LICENSES.txt`. No
GPL-licensed code is used.

## Working on the port

This branch also holds the port's full source, so others can build and change it.

| Path | Contents |
| --- | --- |
| `game/` | The game's decompiled C, as the port compiles it: generated by `tools/ingest.py` from a snapshot of the matching decompilation, with the port's transform stages applied. Never edited by hand. Its data tables hold placeholders (below). |
| `pregen/` | Build inputs normally generated from the private decomp snapshot: the overlay registry (`overlay-gen/`, used when the snapshot is absent) and `DATAFILL.tsv` (the files that hold data placeholders) |
| `overrides/` | Hand-ported replacements for single `game/` files, each recording the hash of the file it replaces |
| `src/` | The PC side: native renderer (D3D11 / Vulkan), audio, file system, threads, pad, saves, settings, host shell (SDL3), the Sony SDK surface the game calls, `rg-extract` / `Setup.exe` |
| `include/`, `cmake/`, `CMakeLists.txt` | Port headers and the build |
| `tools/` | Ingest and transform stages, censuses, test fixtures and gates, packaging |
| `tests/`, `probes/`, `census/`, `missing/` | Unit tests, design experiments, census outputs, stand-ins for functions the snapshot calls but does not define |
| `docs/` | Design notes and bring-up history; start with `docs/PORT-OVERVIEW.md`, `PLAN.md` and `docs/TOOLCHAIN.md` |

### Workspace layout

Scripts take paths relative to the repository root (run them from there) or to its parent
folder, the workspace:

```
workspace/
  port/        this repository
  tools/       llvm, ninja, cmake-3.31.7-windows-x86_64, dl/SDL3-3.4.18.tar.gz (docs/TOOLCHAIN.md)
  work/        optional: loose retail files some research tools read
  RGDecomp/    optional: the matching decompilation (tools/ingest.py)
```

`RG_TOOLS` overrides the tools folder and `LLVM_ROOT` the LLVM install.

### First build

1. Extract your disc: build or download `Setup.exe` / `rg-extract`, then
   `rg-extract "Rogue Galaxy (USA).iso" -o data` in the repository root.
2. Fill the game data from it: `python tools/gamedata_fill.py --data data`. The published
   `game/` and `overrides/` hold placeholders instead of the game's data values; this puts
   them back from your own disc and checks every file's SHA-256. In a git checkout it marks
   the filled files skip-worktree: they now hold game data, so never commit them.
3. Build: `powershell -ExecutionPolicy Bypass -File tools\build.ps1` (i686, clang + Ninja,
   Visual Studio 2019 Build Tools for the Windows SDK and C runtime), or the play-test
   recipe `python tools/playtest/build_playtest.py --tag dev --steps check,configure,build`.
4. Run `build\i686-windows\rg-game.exe --data data`.

The research and gate scripts under `tools/` were written for the original workspace and
some expect files that are not part of this repository (PCSX2 traces, save-state
fixtures); their docstrings say what they read.
