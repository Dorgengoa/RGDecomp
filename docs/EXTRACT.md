# rg-extract

`rg-extract` is the port's first-run tool (PLAN.md D8). It checks that the user's disc
image is Rogue Galaxy (USA) v1.01, SCUS-97490, and unpacks the disc's files into a `data/`
folder. The port reads only `data/` and never the ISO. Every disc file is written
byte-identical (the game still reads them by sector, see [CDVD.md](CDVD.md)), and the 89
MVI movies are also converted into `data/converted/` (MPEG-2 program stream + WAV, see
[MVI.md](MVI.md)) for the P4 movie service.

Source: `src/extract/` (C++17, no dependencies beyond the standard library; SHA-1 and
SHA-256 are our own CC0 code).

## Usage

```
rg-extract [options] <disc image .iso>

  -o, --out DIR        output folder (default: 'data' next to rg-extract)
  -f, --force          replace an existing complete extraction
  -l, --list           list the disc's files and exit (no hash check, no writes)
  -q, --quiet          no progress line
      --no-movies      do not write the converted movies (data/converted/MOVIE)
      --expect-sha1 H  accept an image with SHA-1 H instead of the built-in one
                       (for testing; the port only supports the built-in image)
```

Exit codes: 0 ok, 1 usage, 2 unreadable image, 3 wrong image, 4 output exists,
5 write failed or disk full, 6 malformed image.

What a run does:

1. Parses both ISO 9660 volumes and reads `SYSTEM.CNF`. If the serial, version or image
   size is wrong, it stops at once and names the disc it found (for example
   "Rogue Galaxy (Europe), SCES-54552 (Europe (PAL)) version 1.00").
2. Checks free space on the output drive: the disc files (6.22 GiB), 1.5 times the movie
   bytes for the converted movies, and 64 MiB of slack.
3. Makes one sequential pass over the whole image. The pass computes the image SHA-1 and a
   SHA-256 of every file copy, and writes each file into `<out>.partial/`.
4. If the SHA-1 isn't the accepted value, it deletes `<out>.partial/` and refuses the
   image. Files stored on both layers must hash the same on each layer.
5. Converts each `MOVIE/<dir>/<name>.MVI` it just wrote into
   `converted/MOVIE/<dir>/<name>.mpg` and `.wav` (the same code as `--convert-movie`) and
   hashes the outputs. The `.MVI` stays in place, byte-identical. A movie that does not
   convert is a warning, not an error: it is listed as `# convert_failed` in the manifest
   and the run still succeeds (on the accepted disc all 89 convert). A write error during
   conversion is fatal (exit code 5).
6. Writes `MANIFEST.tsv`, then renames `<out>.partial/` to `<out>/`. With `--force`, an
   old `<out>/` is first moved to `<out>.old/` and deleted after the rename.

A `data/` folder that holds a `MANIFEST.tsv` counts as complete. Without `--force` it is
never overwritten, and neither is a non-empty folder without one. An interrupted run
leaves only `<out>.partial/` (marked with `.rg-extract-partial`), and the next run
removes it.

## Accepted image

| Field | Value |
| --- | --- |
| Title | Rogue Galaxy (USA), SCUS-97490, `VER = 1.01` |
| Size | 6,967,721,984 bytes (3,402,208 sectors) |
| SHA-1 | `87377e721be58e8b6a5a7501721563500d237df7` |

The SHA-1 was computed by `rg-extract` from the project's own copy
(`../ROMS\Rogue Galaxy (USA).iso`). It matches Redump's entry for this disc
(redump.org/disc/6567: same size, layer break 1646704, same SHA-1, CRC-32 044f1164,
MD5 86170ff39c8e02c82bc043c9fe42baaf).

## MANIFEST.tsv

```
# rg-extract manifest v2
# source_sha1	87377e72...
# source_size	6967721984
# source_serial	SCUS-97490	VER 1.01
# volume	0	0	1646704
# volume	1	1646688	1755520
path	size	sha256	lba	copies
BIN/FACTORY.BIN	155264	<sha256>	1001658	L0:1001658,L1:2739787
...
# section	converted
path	size	sha256	source	kind
converted/MOVIE/00/GAMEOVER.mpg	2195460	<sha256>	MOVIE/00/GAMEOVER.MVI	movie-video
converted/MOVIE/00/GAMEOVER.wav	1347628	<sha256>	MOVIE/00/GAMEOVER.MVI	movie-audio
...
```

Lines starting with `#` are metadata. Then comes a header row, then one row per disc file,
sorted by path. `# volume` gives each ISO 9660 volume's layer, the image sector of its
sector 0, and its volume space size; the CDVD model needs it for layer-1 addressing
([CDVD.md](CDVD.md)). The disc-file rows have the same five columns as in v1. `path` uses `/` and has no `;1` version suffix. `lba` is the absolute
disc sector (2048-byte sectors from the start of the image) of the copy that was written.
`copies` lists every copy as `L<layer>:<absolute sector>`. The game finds files by name,
and libcdvd turns the names into sector numbers, so the CDVD model
([CDVD.md](CDVD.md)) uses these LBAs to serve sector reads, and trace tools use them to
match reads to files.

After the disc files, `# section	converted` starts a second table with its own header:
one row per converted output (`path` under `converted/`, `size`, `sha256`, the `source`
disc file, and `kind`: `movie-video` or `movie-audio`). Movies that failed to convert are
listed above that header as `# convert_failed	<source>	<reason>`. A reader that wants
only disc files stops at the first `# section` line. Version 1 manifests (written before
2026-10-11 evening) have neither the `# volume` lines nor the section.

## Disc layout

The disc is a PS2 DVD9: two ISO 9660 volumes in one image, with a UDF 1.02 bridge on each.

| | Layer 0 | Layer 1 |
| --- | --- | --- |
| Image sectors | 0 .. 1646703 | 1646688 .. 3402207 |
| Volume space (PVD) | 1,646,704 sectors | 1,755,520 sectors |
| Files | 83 | 76 |
| Bytes | 3,371,515,328 | 3,594,367,172 |

- **Layer 1** begins 16 sectors before the end of layer 0. The layer-1 PVD sits at sector
  1646704, which is layer 0's volume size and Redump's layer break. Its extents are
  relative to sector 1646688. The two ranges overlap by 16 sectors (1646688..1646703):
  for layer 1 they are its system area, which has no sectors of its own on the disc; for
  layer 0 they are the last 10 sectors of `DATA0_0.DAT`, 5 zero sectors, and a UDF
  anchor in the last sector. [CDVD.md](CDVD.md) explains how the drive addresses them.
- **No multi-extent files, and no file larger than 4 GiB.** The largest file is
  `DATA1_0.DAT` at 1.26 GiB. The reader still supports ISO 9660 multi-extent records
  (flag 0x80), and all offsets are 64-bit, because the image itself is 6.5 GB.
- **UDF is ignored.** Its allocation descriptors use a 30-bit length field, which
  overflows for files of 1 GiB or more. The UDF entry for `DATA0_0.DAT` claims
  246,542,336 bytes with an extent type of "allocated, not recorded". ISO 9660 is the
  only correct view of this disc.
- **35 files exist on both layers**: `BIN/*.BIN` (7), `MOVIE/00/*.MVI` (26), `RGDMY.DAT`
  and `RGSYS.DAT`. All 35 pairs are byte-identical, so the extractor merges both layers
  into one tree and writes each of these files once.

Merged tree: **124 files, 6,673,873,692 bytes (6.22 GiB)**, plus 178 converted movie
files (89 `.mpg` + 89 `.wav`, 2,826,946,736 bytes, 2.63 GiB) under `converted/`.

| Top level | Files | Size | Layer |
| --- | --- | --- | --- |
| `SYSTEM.CNF` | 1 | 57 B | 0 |
| `SCUS_974.90` | 1 | 3.5 MiB | 0 (main ELF) |
| `MODULES/` | 16 | 0.6 MiB | 0 (IRX modules, `IOPRP300.IMG`) |
| `BIN/` | 7 | 0.7 MiB | both (overlays) |
| `DATA0_0.DAT` / `.HD6` | 2 | 1259.4 MiB | 0 |
| `DATA0_1.DAT` / `.HD6` | 2 | 894.7 MiB | 0 |
| `DATA1_0.DAT` / `.HD6` | 2 | 1293.3 MiB | 1 |
| `DATA1_1.DAT` / `.HD6` | 2 | 915.6 MiB | 1 |
| `MOVIE/` (00-07 and 97 on layer 0; 08-13, 98, 99 on layer 1; 00 on both) | 89 | 1980.9 MiB | see left |
| `RGDMY.DAT` | 1 | 16 MiB | both (padding file) |
| `RGSYS.DAT` | 1 | 1 KiB | both |

Large files (over 50 MB): `DATA1_0.DAT` 1,355,851,776; `DATA0_0.DAT` 1,320,284,160;
`DATA1_1.DAT` 959,963,136; `DATA0_1.DAT` 938,082,304; `MOVIE/99/STAFF_A.MVI` 249,774,084;
`MOVIE/97/01_14.MVI` 209,453,060; `MOVIE/02/02_05.MVI` 135,430,148;
`MOVIE/97/07_02.MVI` 117,456,900; `MOVIE/99/13_07_1B.MVI` 89,473,028;
`MOVIE/98/09_08_1.MVI` 85,884,932; `MOVIE/00/RUSH.MVI` 76,251,140.

Run `rg-extract --list <iso>` for the full table.

Note: the older extraction in `../work\` was made from layer 0 only. It has no
`DATA1_*` files and no `MOVIE/08`-`13`, `98` or `99`.

## Building and testing

```
cmake -S src/extract -B build/extract -G "Visual Studio 16 2019" -A x64
cmake --build build/extract --config Release
build/extract/Release/rg-extract-tests.exe
```

The directory also works through `add_subdirectory(src/extract)` from the top-level build.
`rg-extract-tests` (also registered with CTest) checks SHA-1 and SHA-256 against the FIPS
vectors. It also builds small synthetic disc images (single and dual layer, a
multi-extent file, an empty file, a file on both layers) and checks that:

- extraction is byte-exact, and the manifest rows (sizes, hashes, LBAs, copies) are right;
- an existing extraction is refused without `--force` and replaced with it;
- a wrong `--expect-sha1`, a one-byte-tampered image, a different serial (named in the
  message, including a known release such as SCES-54552), and a same-serial
  wrong-content image are all refused, and no output folder is left behind;
- copies that differ between layers, unsafe names (`..`, `CON.TXT`, `A:B`), a truncated
  image and a missing file are all rejected.

It also builds a small image with a valid synthetic movie and a junk `.MVI` under
`MOVIE/00/` and checks that the valid one is converted (outputs equal to
`convert_movie_memory` on the same bytes, rows in the converted section), the junk one is
only a warning (`# convert_failed`, no outputs), both originals are byte-identical, and
`convert_movies = false` (`--no-movies`) writes no `converted/` folder. The dual-layer
test checks the `# volume` lines.

## Verification (2026-10-11)

- A full run on the project's ISO wrote 124 files (6,673,873,692 bytes) in 328 s
  (I/O-bound, about 20 MiB/s on a busy HDD). The SHA-1 it computed equals Redump's.
- `SCUS_974.90`, `BIN/*.BIN`, `MODULES/*` (IRX and `IOPRP300.IMG`), `DATA0_*.HD6`,
  `RGSYS.DAT` and `RGDMY.DAT` are byte-identical to the older, independent extraction in
  `../work\`. So are `DATA0_0.DAT`, `DATA0_1.DAT` and all 52 layer-0 movies. In
  total, 82 files are byte-identical, and that is every file in the older extraction.
  Spot-checked manifest SHA-256 values match `sha256sum`.
- A second run into the same `data/` without `--force` is refused (exit code 4).
- Second full run (same day, with movie conversion; `--force` into the same `data/`):
  193 s in all, of which the 89 movie conversions took 53 s. All 89 converted, none
  failed. Output: 124 disc files as before (same SHA-256 values) plus 178 converted files
  (2.63 GiB). `converted/MOVIE/00/TITLE01.{mpg,wav}` hash the same as
  `rg-extract --convert-movie data/MOVIE/00/TITLE01.MVI`.
