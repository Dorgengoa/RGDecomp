# Rogue Galaxy PC port

A native PC port of *Rogue Galaxy* (PS2, SCUS-97490 v1.01) built from the
[matching decompilation](../decomp). The game's own code is compiled for the host, and
the PS2 hardware and IOP services are replaced by a host platform layer. See
[PLAN.md](PLAN.md).

Status: `game/` is ingested from the published decomp, commit `675c07fe`
([docs/SNAPSHOT-CLEAN.md](docs/SNAPSHOT-CLEAN.md)), with all transform stages, and all of
it builds. `rg-game.exe` links the whole game (0 undefined, 0 duplicate). Headless, it
boots to the title menu, and with the scripted NEW GAME input it loads the NORMAL overlay and
shows the opening story screen ([docs/LINK.md](docs/LINK.md),
[docs/BRINGUP.md](docs/BRINGUP.md)). Build and test commands:
[docs/TOOLCHAIN.md](docs/TOOLCHAIN.md).

## You need your own copy of the game

No game data is included, and none will be accepted. On first run, `rg-extract` checks
your ISO's hash and unpacks it into a local `data/` folder.

## Layout

| Path | Contents |
| --- | --- |
| `game/` | Decompiled game source, **generated** by `tools/ingest.py` from a pinned snapshot. Never hand-edited. |
| `overrides/` | Hand-ported replacements for individual `game/` files, each recording the hash of the file it replaces |
| `src/sce/` | The Sony SDK API surface the game calls, reimplemented |
| `src/ps2/` | Hardware/IOP models: EE scheduler, DMA/VIF/VU1/GS, IOP service HLE |
| `src/host/` | SDL3 shell, renderer backend, audio, config, saves |
| `src/extract/` | `rg-extract`, the first-run ISO extractor |
| `tools/` | Ingest, transforms, censuses, trace comparison |
| `census/` | Census outputs (TSV) |
| `probes/` | One-off experiments that settle a design question |
| `third_party/` | Vendored permissive code, each with its own license |

## License

The port's original code and documentation are dedicated to the public domain under
[CC0 1.0](LICENSE).

CC0 does **not** cover `game/` or `overrides/`. That code is decompiled from, and
derived from, a copyrighted game owned by Level-5 and Sony Interactive Entertainment. No
rights to it are granted here.

Vendored code under `third_party/` keeps its own license; see
[THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md). No GPL-licensed code is used.
