# Rogue Galaxy

A matching decompilation of *Rogue Galaxy* for the PlayStation 2.

All of the game's own code -- every function in its executable and its five code overlays --
has been decompiled to C (or C++), and it compiles byte-for-byte to the same binaries as the
retail game. The libraries the game links (the Sony SDK, the C runtime, the MPEG/IPU
library and the Metrowerks runtime) are partly C; the rest is linked as it shipped, from
your own copy of the game. The original toolchain is used: Metrowerks CodeWarrior for PS2
(`mwccps2` 3.0.1b210) for the game, and Sony's `ee-gcc` 2.9 for a small island of
kernel-resident library code.

It builds the following files of the NTSC-U release (`SCUS-97490`, v1.01):

| File | Description | SHA-1 |
| --- | --- | --- |
| `SCUS_974.90` | main executable | `87e9eff1d795c894fc09047270baab70d6a8d2c8` |
| `BIN/TITLE.BIN` | title screen overlay | `e82573fce90bd496d75efedf6d781ac04791d81d` |
| `BIN/INSMENU.BIN` | Insectron menu overlay | `c17c97b2401a2fb864b88dfbf47eb5b7989aab8d` |
| `BIN/NORMAL.BIN` | field / battle overlay | `147dd08d8b1d46af494db7ef146b5f1379ce9555` |
| `BIN/FACTORY.BIN` | Factory overlay | `03ce9121a240b4b57cc6343f70e1eadb473b55e7` |
| `BIN/INSECT.BIN` | Insectron battle overlay | `164e56f939e39c78b10851bec1e38de39a81996a` |

**This repository does not include any game code, assets, executables, or data.** That
includes the game's ELF, its overlays, the disc image, any file extracted from it, its
disassembly and its data values. A copy of the game's files, taken from a legally owned
disc, is required to build the project: the parts that are not C, and the game's data
values, are extracted from them at setup, and the build compares its output against them.

## Status

**Game code**

| Image | Functions in C |
| --- | --- |
| `SCUS_974.90` | 16,243 / 16,243 |
| `TITLE.BIN` | 107 / 107 |
| `INSMENU.BIN` | 365 / 365 |
| `NORMAL.BIN` | 659 / 659 |
| `FACTORY.BIN` | 409 / 409 |
| `INSECT.BIN` | 744 / 744 |
| **Total** | **18,527 / 18,527** |

**Libraries** (`SCUS_974.90` only)

| | Functions in C |
| --- | --- |
| Sony SDK, C runtime, MPEG/IPU, Metrowerks runtime, crt0 | 699 / 1,473 |

All six images rebuild byte-identical to retail. The library functions that are not C are
assembled from your copy of the game by `scripts/extract.py`; turning them into C is a
stretch goal, and not needed to understand or port the game.

The game's initialised and zero-filled data (`.data`, `.rodata`, `.sdata`, `.bss`) is
also C, in `src/main_data/`; the repository carries its names, types and layout, and
`scripts/extract.py` fills in the values from your copy of the game.

Functions carry descriptive names (`<Name>_<address>`). Names ending in `Maybe` or
`Related` mark a role that was inferred but not fully proven; see
[docs/NAMING.md](docs/NAMING.md).

## Dependencies

- Linux x86-64 or WSL, with Python 3.10 or newer (standard library only), `curl`, `tar` and `xz`
- the i386 C runtime, for Sony's 32-bit `ee-gcc`
  (Debian/Ubuntu: `sudo dpkg --add-architecture i386 && sudo apt install libc6:i386`)

`scripts/setup_toolchain.sh` downloads the rest, each checked against a pinned SHA-256:

- [decompals binutils](https://github.com/decompals/binutils-mips-ps2-decompals) (`as`, `nm`, `objcopy`)
- [wibo](https://github.com/decompals/wibo), which runs the Windows compilers on Linux
- Metrowerks CodeWarrior for PS2 `mwccps2` / `mwldps2` **3.0.1b210-060308** and Sony
  `ee-gcc` **2.9-ee-991111-01**, from the [decomp.me compiler archive](https://github.com/decompme/compilers)

Building from Windows is also possible, with the compilers on a Linux machine reached over
SSH; see [docs/BUILDING.md](docs/BUILDING.md).

## Setup

1. Clone the repository.
2. Copy the following files from your disc into a `retail/` directory at the root of the
   repository (or point `RGD_RETAIL_DIR` at another directory):

   ```
   retail/SCUS_974.90
   retail/BIN/TITLE.BIN
   retail/BIN/INSMENU.BIN
   retail/BIN/NORMAL.BIN
   retail/BIN/FACTORY.BIN
   retail/BIN/INSECT.BIN
   ```

3. Install the toolchain and tell the build to run on this machine:

   ```sh
   sh scripts/setup_toolchain.sh
   export RGD_HOST=local
   ```

4. Extract the parts of the build that come from the game itself:

   ```sh
   python3 scripts/extract.py
   ```

   This checks your files against the SHA-1 table above and writes `asm/` and the data
   values in `src/main_data/`. They are ignored by git and must never be committed.

## Building

```sh
python3 scripts/verify.py
```

This compiles every unit of the main executable and of the five overlays, compiles the
data C, links all six images and compares each of them with your retail files. A full
build takes a few hours, most of it compiling the main executable's ~17,000 units. If
everything matches, it prints:

```
SCUS_974.90  : BYTE-IDENTICAL
TITLE.BIN    : BYTE-IDENTICAL
INSMENU.BIN  : BYTE-IDENTICAL
NORMAL.BIN   : BYTE-IDENTICAL
FACTORY.BIN  : BYTE-IDENTICAL
INSECT.BIN   : BYTE-IDENTICAL
ALL BYTE-IDENTICAL
```

The linked images are written to `build/link/SCUS_974.90` and
`build/overlay-c-<ti|im|nm|fc|ix>/<OVERLAY>.BIN`. A line reading `DIFFERS` means the built image
is not the same as the retail one, so something in the source or the setup does not
match. `python3 scripts/verify.py --link-only` relinks from the existing objects.

The individual steps can also be run on their own:

```sh
python3 scripts/hostbuild.py               # compile the main executable (+ data C)
python3 scripts/link.py                    # link and compare SCUS_974.90
python3 scripts/sandbox_build.py --tag ti <symbols...>   # compile overlay units
python3 scripts/t_olink.py title           # link and compare TITLE.BIN
                                          # (i_olink insmenu, n_olink normal,
                                          #  f_olink factory, x_olink insect)
```

## Project structure

```
RGDecomp/
├── asm/                    generated by scripts/extract.py, except:
│   ├── reginfo_pin.s       .reginfo for the main link
│   └── overlays/<ov>/      overlay .bss reservations
├── config/
│   ├── units.txt           every main unit, in link order
│   ├── cunits.txt          main units compiled from C
│   ├── ocunits/<ov>.txt    overlay units compiled from C
│   ├── *.symbols.txt       symbol tables (address, size) per image
│   ├── data2c.json         description of the main data, for the generated data C
│   ├── toolchain.txt       per-unit compiler exceptions (ee-gcc island, extra flags)
│   ├── asm/                skeletons extract.py rebuilds asm/ from (labels and
│   │                       addresses only)
│   ├── main_data/          skeletons of src/main_data/ (names, types, layout)
│   └── ...                 jump tables, hosted static functions, object fix-ups
├── docs/                   building and naming notes
├── include/                shared headers
├── scripts/                build, link and verification tooling
├── src/
│   ├── main/<subsystem>/   the main executable, one function per file
│   ├── main/sdk/           Sony SDK and C library functions
│   ├── main_data/          data C (values filled in by extract.py)
│   └── overlays/<ov>/      the five overlays
├── handoff/                manifest of the generated data C
└── SCUS_974.90.lcf         linker command file for the main executable
```

## Contributing

The game code is complete. Issues and pull requests that improve names, types and
documentation, or that turn remaining library functions into C, are welcome, as long as
`python3 scripts/verify.py` still reports `ALL BYTE-IDENTICAL`.

## Credits

This project builds on the work and tools of the decompilation community:

- [wibo](https://github.com/decompals/wibo), [decompals binutils](https://github.com/decompals/binutils-mips-ps2-decompals)
- [splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm),
  [rabbitizer](https://github.com/Decompollaborate/rabbitizer)
- [m2c](https://github.com/matt-kempster/m2c), [objdiff](https://github.com/encounter/objdiff)
- The [Kingdom Hearts](https://github.com/ethteck/kh1) decompilation, whose retail SDK
  symbol lists identified many of this game's library functions

## Legal

This project is not affiliated with, endorsed by, or sponsored by Level-5 or Sony
Interactive Entertainment. *Rogue Galaxy* is a trademark of its respective owners. No
copyrighted game data is included in this repository.
