# Rogue Galaxy PC port

A native Windows port of *Rogue Galaxy* (PlayStation 2, North America, SCUS-97490 v1.01).
It is not an emulator. The game's own code comes from the matching decompilation of the
retail executable and is compiled for the PC. The PS2 hardware, operating system and sound
system are replaced by native PC code: a Direct3D 11 / Vulkan renderer, a native audio
engine, and native file, controller, memory-card and movie services.

**You need your own copy of the game.** This branch and the download contain no game
content: no art, sound, music, movies, text or game data, and no bytes taken from the
game's executable. The first-run setup reads everything it needs from your own disc image.

- **Play it on Windows:** download `release/RogueGalaxyPC-1112a-win32.zip` and follow
  [QUICKSTART.md](QUICKSTART.md). In short: unzip it, put your `.iso` in the folder, run
  `Setup.exe` once, then run `rg-game.exe`.
- **Play it on Linux (x86-64):** download `release/RogueGalaxyPC-1112a-linux-x86_64.zip`
  and follow [QUICKSTART-linux.md](QUICKSTART-linux.md): unzip it, put your `.iso` in the
  folder, run `./rg-setup` once, then run `./rg-game`.
- **Build:** 1112a (2026-11-12).

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
- Windows 10 or 11, 64-bit, with a Direct3D 11 or Vulkan graphics card. The Windows
  executable in the download is 32-bit; a 64-bit Windows build exists and runs the same
  automated routes, but is not in the download yet.
- Linux, x86-64, with a Vulkan driver (X11 or Wayland): a native 64-bit build in its own
  download. It runs the same automated routes as Windows with the same results; it has had
  less play-testing.

## Features added over the original

**Display and graphics**
- Window, borderless fullscreen (F11 or Alt+Enter) or exclusive fullscreen; resizable
  window; VSync.
- Internal resolution 1x to 8x, or matched to the window.
- Widescreen: 4:3, 16:9, 16:10, 21:9 or automatic, with a widened view, HUD and menus
  anchored to the screen edges, and movies kept at their own aspect ratio.
- Exclusive fullscreen with a resolution and refresh-rate picker; monitors listed by name.
- Anti-aliasing (FXAA, 2x to 4x supersampling), texture filtering (original, bilinear,
  nearest), anisotropic filtering up to 16x, sharpening, CRT / scanline filter, brightness
  and gamma.
- Bloom, depth of field and motion blur: original, enhanced or off.
- Frame rate: original, 30, 60, 120, 144, 165, 240, the display's rate or uncapped, with
  optional interpolation for smoother motion above 30 fps (off by default).
- HD texture packs: dump the game's textures as PNG and draw replacements (PNG / DDS, any
  size) from `textures\SCUS-97490
eplacements`; file names follow PCSX2's texture-pack
  naming (off by default).
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

**Accessibility and gameplay options**
- UI and subtitle scale (75 to 150 %), camera shake (0 to 100 %), reduced flashing.
- Colour-blind modes for markers told apart by colour alone.
- Text speed (original, fast, instant) and battle speed-up (1.5x to 3x); off by default.

**Saves and loading**
- Memory-card saves as files in `saves\`, written crash-safe, with automatic backups; the
  saves folder and the number of backups can be set.
- Save manager in the settings menu: list saves and name them.
- Import saves from a PCSX2 memory card (the card file is only read).
- No disc loading delays.

**Settings menu**
- In-game settings overlay: F1, or hold Back + Start on a gamepad for one second.
- An "Original" preset that restores the PS2 look and behaviour.
- Settings are saved in `settings.ini` next to the game.

## Known issues

- No complete playthrough has been confirmed yet (see above).
- Fixes not yet confirmed by a player: the Item Storage crash at the transporter; Monsha's
  head and tail tip; floors culled while on screen; interpolated frames out of sync;
  subtitles snapping from the left at wide aspect ratios; Exchange Points showing "Qu";
  extra bold outlines on faces; the inventory selection frame; menu sides at 16:9 / 21:9.
- Saving can cause a short slowdown and an audio hiccup.
- Closing a shop runs at about 15 fps for half a second.
- "Enhanced" depth of field and motion blur currently look the same as "Original".
- The shadow-resolution setting in the menu is a placeholder.
- Movie audio runs at the disc's 48,048 Hz clock; long movies may drift very slightly.
- Windows SmartScreen warns about the unsigned executables (choose "More info", then
  "Run anyway").
- If the game crashes on Windows, `rg-game-crash.txt` and `rg-game-crash.dmp` appear next to it.
  Please include them in a report.

## Planned

- A confirmed full playthrough, with automated runs covering every chapter.
- The 64-bit Windows build in the download; later macOS.
- Optional ray tracing (Vulkan, 64-bit build): sun shadows, ambient occlusion, reflections
  and light from the art's lamps, screens and flames. Working in development builds, not
  in this download yet.
- Shadow resolution; enhanced depth of field and motion blur.
- Modding support beyond texture packs.

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
## Building from source

This branch also holds the port's source, so others can build and change it.

| Path | Contents |
| --- | --- |
| `game/` | The game's decompiled C, as the port compiles it: generated by `tools/ingest.py` from a snapshot of the matching decompilation, with the port's transform stages applied. Never edited by hand. Its data tables hold placeholders (below). |
| `overrides/` | Hand-ported replacements for single `game/` files, each recording the hash of the file it replaces |
| `src/` | The PC side: native renderer (D3D11 / Vulkan), audio, file system, threads, pad, saves, settings, host shell (SDL3), the Sony SDK surface the game calls, `rg-extract` / `Setup.exe` |
| `include/`, `cmake/`, `CMakeLists.txt` | Port headers and the build |
| `pregen/` | Build inputs normally generated from the decomp snapshot: the overlay registry and `DATAFILL.tsv` (the files that hold data placeholders) |
| `missing/` | Stand-ins for functions the snapshot calls but does not define |
| `tests/` | Unit tests (`ctest`) |
| `third_party/` | Vendored single-header libraries (see THIRD_PARTY_NOTICES.md) |
| `tools/` | The build script, the data fill, the ingest stages and the scripts the tests run |

### Requirements (Windows)

Put these in a `tools` folder next to the repository (or point `RG_TOOLS` at it; `LLVM_ROOT`
overrides the LLVM folder):

```
workspace/
  port/        this repository
  tools/
    llvm/                              LLVM/Clang 23 (official Windows release, extracted)
    ninja/ninja.exe                    Ninja 1.13
    cmake-3.31.7-windows-x86_64/       CMake 3.31 (portable zip)
    dxc/bin/x64/dxc.exe                DirectX Shader Compiler with SPIR-V (python tools/native/fetch_dxc.py)
    dl/SDL3-3.4.18.tar.gz              optional: SDL3 source for offline builds (else downloaded)
```

Also needed: Visual Studio 2022 Build Tools (MSVC 14.44: the x86 C runtime and the Windows SDK) and Python 3.10+.

### First build

1. Extract your disc with `Setup.exe` from the release zip, or with `rg-extract`:
   `rg-extract "Rogue Galaxy (USA).iso" -o data` in the repository root.
2. Fill in the game data: `python tools/gamedata_fill.py --data data`. The published `game/`
   and `overrides/` hold placeholders instead of the game's data values; this puts them back
   from your own disc and checks every file's SHA-256. In a git checkout it marks the filled
   files skip-worktree: they now hold game data, so never commit them.
3. Build: `powershell -ExecutionPolicy Bypass -File tools\build.ps1 -Game` (i686, Clang +
   Ninja; the same options as the release build).
4. Run `build\i686-windows\rg-game.exe --data data`.

Run the unit tests with `ctest --test-dir build\i686-windows`. Some tests need files that are
not part of this repository (save-state fixtures, traces) and skip or fail without them.
