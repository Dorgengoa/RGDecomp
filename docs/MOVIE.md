# Movies

PLAN.md P4 asks for a movie service at the `sceMpeg`/movie-player boundary. It plays the
movies that `rg-extract` converted (docs/MVI.md), so nothing is decrypted at runtime. The
game's own movie layer drives the IPU and DMA channels 3/4 and installs its own handlers.
So the service replaces that **layer**, not just `sceMpeg*`, and it has to keep the
start/stop/skip/completion semantics.

| Path | What |
| --- | --- |
| `src/movie/movie.h` | Public API: decoder (`rg_mvdec_*`), conversion, audio (`rg_mvaudio_*`), service (`rg_movie_*`) |
| `src/movie/mv_dec.c` | Program stream demultiplexer and MPEG-2 video decoder |
| `src/movie/mv_vlc.c` | VLC code lists (ISO/IEC 13818-2 Annex B) and table builder |
| `src/movie/mv_idct.c` | 8x8 IDCT |
| `src/movie/mv_color.c` | YCbCr to RGBA, and the PS2 16x16-block layout |
| `src/movie/mv_audio.c` | WAV reader and the `SShd`/`SSbd` re-encoder |
| `src/movie/mv_service.c` | Movie service (state machine, frame FIFO, virtual clock pacing) |
| `src/movie/rg_movie_play.c` | `rg-movie-play` tool |
| `tests/movie/` | `rg-movie-tests`, `reference.tsv`, `ffprobe_pts.txt` (`ctest -L movie`) |

Everything in `src/movie` and `tests/movie` is original CC0 code (D7). It has no external
dependency and links no FFmpeg. FFmpeg is used only as an external verification tool, by
one test that runs `ffmpeg.exe` as a separate process and is skipped when it is missing.

## Decoder decision: a from-scratch CC0 decoder

**Option (a): FFmpeg as an LGPL shared library (i686 Windows).**

- No official 32-bit Windows binaries exist. FFmpeg ships only source. The common
  third-party builds (BtbN, gyan.dev) are win64 only, and the gyan.dev builds are GPL. There
  is no maintained, LGPL-only, i686 shared build to pin by hash.
- That leaves building FFmpeg ourselves: an MSYS2/mingw-w64 i686 toolchain, `configure
  --disable-gpl --disable-nonfree --enable-shared --disable-static`, trimmed to `mpeg` +
  `mpeg2video`. Then we would have to ship the DLLs plus the LGPL text and an offer of the
  corresponding source, and re-verify the license audit at every FFmpeg bump. It also adds
  a second toolchain (gcc/mingw) to a clang-only project, and a runtime DLL that has to
  match the 32-bit process.
- What it would decode is a tiny subset of `mpeg2video`, and the PS stream is already
  trivial to demultiplex (docs/MVI.md).

**Option (b): a CC0 decoder for exactly the subset these 89 files use.** It is feasible
because the survey below shows the streams use a very small part of MPEG-2. Frame
pictures only, `frame_pred_frame_dct = 1`, no concealment vectors and no alternate scan,
so there is no field motion, field DCT, dual prime or 4:2:2. That leaves VLC tables, a
dequantiser, an IDCT, half-pel motion compensation and picture reordering: about 1,600
lines of C.

**Decision: (b).** The port keeps zero runtime dependencies for movies. No DLL, no LGPL
obligations, nothing to build outside CMake. The output is deterministic and
bit-reproducible across runs, which the replay tests need. It is verified against FFmpeg on
every frame of every movie (below). PLAN.md P4's "FFmpeg-backed service" wording is
superseded by this choice. The LGPL dynamic-link rule in THIRD_PARTY_NOTICES.md stays as
the fallback if a future need (say a modded movie in another codec) ever comes up.

## Stream survey (all 89 converted movies, 116,956 pictures)

Measured by demultiplexing every `.mpg` and parsing every header (scratch survey script,
2026-10-11):

| Syntax element | Values seen |
| --- | --- |
| `sequence_extension` | 89 x `profile_and_level 0x48` (MP@ML), `progressive_sequence 1`, `chroma_format 1` (4:2:0), no size extension |
| sequence header matrices | `load_intra_quantiser_matrix 0` (default intra matrix) and `load_non_intra_quantiser_matrix 1` in all 89 |
| other extensions | sequence display (89). No quant matrix extension, no scalable or copyright extension. One user data per file. |
| picture types | I 6,784, P 32,854, B 77,318; no D pictures |
| `picture_coding_extension` | all 116,956: `picture_structure 3` (frame), `frame_pred_frame_dct 1`, `concealment_motion_vectors 0`, `q_scale_type 1` (non-linear), `intra_vlc_format 1` (table B-15), `alternate_scan 0`, `intra_dc_precision 0` (8 bit), `repeat_first_field 0`, `progressive_frame 1` |
| `f_code` | 1..4 in each direction (I pictures 15) |
| slices | 2,575,986; `extra_bit_slice 0` everywhere |
| GOPs | 6,784; 661 closed, none broken |

Supported, with each item checked on real data: everything above, plus the B-14 table
(non-intra blocks) and skipped macroblocks in P and B pictures. Implemented but not
exercised by any retail movie: a linear `q_scale_type`, `intra_vlc_format 0`, a non-zero
`intra_dc_precision`, the quant matrix extension, and edge replication for
out-of-picture motion vectors (the counter `rg_mvdec_oob_predictions()` reads **0** over
the whole corpus).

Refused with `RG_MV_ERR_UNSUPPORTED`: field pictures, `frame_pred_frame_dct 0`,
concealment vectors, alternate scan, D pictures, non-4:2:0 chroma and MPEG-1 streams. A
stream that is not one of these 89 files gets a clear error, never wrong pixels.

## Decoder (`rg_mvdec_*`)

- **Demux.** The converted `.mpg` is read in 64 KiB chunks. `E0` PES payloads are appended
  to an elementary-stream buffer, which is compacted as data is consumed, so memory stays
  bounded by the largest picture plus one chunk (the 250 MB `STAFF_A` is streamed). PES PTS
  values are kept with their ES byte range. Per 13818-1, a picture whose start code begins
  in a PES with a PTS takes that PTS. A picture without one gets the previous frame's PTS
  plus `90000 * den / num` (3003 or 3000). That matches ffprobe on every frame where
  ffprobe has a PTS, and ffprobe reports N/A where we extrapolate.
- **Picture unit.** A picture runs from its start code to the next picture, sequence, GOP or
  end code. Slices end where the next 23 bits are zero. A final macroblock can be shorter
  than 23 bits: an early "fewer than 23 bits left" test dropped the bottom-right macroblock
  of some pictures, and comparing against FFmpeg caught it.
- **VLC.** Every Annex B table is written as its code list (`"0000 0101 11"` style) and
  expanded at decoder creation. Building a table fails if the list is not prefix-free.
  `movie.vlc` also checks each table's Kraft sum against the unused code space the
  standard implies (start-code prefixes, vacated B-15 slots), so a dropped or duplicated
  row fails the test. DCT tables are two-level: a 12-bit table for codes up to 12 bits,
  and an 8-bit table for codes that begin with `0000 0000` (13-16 bits).
- **Dequantisation** is per 7.4, with saturation and mismatch control (toggle the LSB of
  `F[7][7]` when the sum is even).
- **IDCT.** Separable, double precision, even/odd split, rounded to nearest. It skips rows
  known to be zero (from the coefficient positions). `movie.idct` runs the IEEE 1180-1990
  procedure: 3 ranges x 2 signs x 10,000 blocks, peak error <= 1, pmse <= 0.06, omse <=
  0.02, pme <= 0.015, ome <= 0.0015. It also checks that the sparse path equals the full
  transform.
- **Motion compensation.** Frame prediction, half-pel bilinear `(a+b+1)>>1` and
  `(a+b+c+d+2)>>2`, and bidirectional `(f+b+1)>>1`. Chroma vectors are `mv/2`, truncated
  toward zero. The P-picture "No MC" macroblock and P skips reset the PMVs. B skips reuse
  the previous macroblock's type and vectors.
- **Reordering.** Three frame buffers. B pictures are output at once. An I/P picture
  releases the previous reference. Leading B pictures with no forward reference use the
  backward one. `want_pixels = 0` parses past a B picture without decoding it; the service
  uses this when it drops a frame.

### Verification against FFmpeg (all 89 movies)

Our decoder and `ffmpeg -f rawvideo -pix_fmt yuv420p` were run side by side on every
movie, frame by frame (a scratch script; `movie.real_psnr` repeats the comparison on 5
movies in CTest):

| | Result |
| --- | --- |
| Frames | 116,956 = FFmpeg's count, movie by movie (and = the docs/MVI.md picture counts) |
| PSNR (Y+Cb+Cr) | worst frame 61.6 dB; per-movie mean 64.9-85.3 dB; 3,916 frames bit-identical |
| Max absolute sample difference | 6 (most movies 2-4) |
| Picture types and PTS | identical to ffprobe wherever ffprobe has a PTS (`movie.real_timestamps`) |

The remaining differences are IDCT rounding. FFmpeg uses its own integer IDCT. Ours is a
more exact double-precision transform, and neither is "the" answer: 13818-2 specifies the
IDCT only to IEEE 1180 accuracy, plus mismatch control. The PS2 IPU has its own IDCT too.
So bit-exactness with either one would be arbitrary. What the tests pin is our own
output: per-frame FNV hashes at 6 indices per movie, plus a digest over all frames
(`reference.tsv`), so any change to decoding shows up.

### Performance

`rg-movie-play --bench`, i686 build at the project's `-O1` (this dev machine, warm
cache, decode only):

| Movie | Frames | Mean | Slowest frame |
| --- | ---: | ---: | ---: |
| 00/GAMEOVER | 210 | 0.40-0.43 ms | 1.4 ms |
| 00/TITLE01 (512x448) | 540 | 0.41 ms | |
| 97/01_14 (5.5 min) | 9,835 | 1.26-1.72 ms | 3.6 ms |
| 02/02_05 | 5,965 | 1.27-1.30 ms | 9.3 ms |
| 99/STAFF_A (512x448, 8 min) | 14,760 | 0.95-1.12 ms | 9.6 ms |

The whole service path is about 1.3 ms per frame (decode, plane copy into the FIFO and
the RGBA/block conversion). A full 01_14 run through the service, simulated over 19,690
fields, takes 13 s of wall time. The 33 ms frame budget has a large margin, so decoding
runs synchronously on the calling thread, with no worker thread.

## Colour and the GS upload layout

`rg_mv_to_rgba` uses BT.601 studio swing in 8-bit fixed point. Each chroma sample covers
2x2 luma samples with no interpolation, which is what the IPU's CSC does.

`rg_mv_to_ps2_blocks` writes the layout that the game's upload packets expect.
`GsUploadImage16Blocks_1d27a0` sets TRXREG 16x16 and emits one IMAGE transfer per block,
`src += 0x400`, looping **x outer, y inner**. So the frame in EE memory is 16x16 RGBA32
blocks (row-major inside), in column-major block order. That is exactly the CSC output
of `sceMpegGetPicture`, and `movie.color` pins it. Alpha is 0x80: `MovieDrawFrame_1d5870`
draws with blending off and the alpha test set to ALWAYS, so alpha only has to be valid.

## Audio

### Path: the game's AudioDec layer, fed the original byte stream

On the PS2, `MpegDemuxPssRing_115340` hands each private-stream-1 payload, after its 4
framing bytes, to `AudioDecPcmCallback_1d4ca0`. That function copies it into the AudioDec
ring. `AudioDecBeginPut` collects the 0x28-byte `SShd`+`SSbd` header in state 0, then
`AudioDecSendToIop_1d2e90` moves 1 KiB units to the IOP ring that sdr_driver `0x80E0`
AutoDMA plays (`0x8100` = play position; docs/SOUND.md). The sound HLE already models
that whole path on the virtual clock.

So the service keeps it. `rg_mvaudio_read_ss` regenerates the exact original stream from
the WAV: `SShd` (format 1, rate, 2 channels, interleave 512, -1, -1), `SSbd` with
`body_len`, and blocks of `[256 L][256 R]` s16. `movie.audio_ss` checks the header fields,
the block interleave, the zero-padded last block, and that any read chunking gives the
same bytes. The game-side feed (see the overrides below) writes these bytes into the
game's own read buffer and calls the unmodified `AudioDecPcmCallback_1d4ca0` on it. Master
volume, input-volume fades (`AudioDecSetInputVolume`), pause (`AudioDecPause`), the
preset check (`AudioDecIsPreset`) and the IOP ring all stay the game's own code.

`rg_mvaudio_read_pcm` / `rg_movie_read_pcm` give LRLR PCM for host-side use
(`rg-movie-play --window` pushes it straight to SDL at 48 kHz).

### 48048 Hz vs 48000 Hz: what the game does (docs/MVI.md open question)

The game's player has **no A/V sync at all**:

- `MovieVblankHandler_1d4c90` and `MovieDmacHandler_1d4b10` are the two `asm-block`
  EXCLUDED.tsv rows. Their whole body is `sync; ei; return 0`. They count nothing and
  pace nothing.
- `VideoDecMain_1d5240` only runs `VideoDecDecodeBs_1d29e0`. That loop decodes whenever a
  VoBuf slot is free (`VoBufGetData`), with no clock.
- A frame reaches the screen only through `MovieFrameQueueSendNext_1d4b20`, which the game
  calls once per game frame (title: `title_TitleMovieUpdate_4f04c0`). It pops one decoded
  frame if one is ready, otherwise it counts an underrun in `D_004817A0`, which nothing
  reads.
- `AudioDecIopGetArea_1d2df0` uses the `0x8100` position only to compute free ring space
  for refills. It is never compared against video.

So on hardware, video advances one frame per game frame, and the SPU2 plays the ring at
its fixed 48000 Hz. For the 30 fps / 48048 Hz movies that is exactly NTSC-compensated: a
30 fps movie shown at 59.94/2 and 48048 Hz audio played at 48000 Hz both run 1.001x slow,
so they stay in sync. For the 73 movies at 29.97 fps / 48048 Hz, the audio falls behind
by 0.1%: 0.33 s by the end of `97/01_14`, the longest of them.

**Measured** ([VALIDATION.md](VALIDATION.md) section 6, PCSX2 with the game's own player,
`01/01_01.MVI` over 67.8 s): video advanced **0.500014 frames per VBlank** (29.971 fps),
exactly one frame per two VBlanks, no drops (`D_004817A0` stayed 0); the audio sent to
the IOP grew at **47,999.97 stereo samples/s**, i.e. the SPU2 plays the 48048-Hz WAV at
48000 Hz; there is no resync. TITLE02 (30 fps) gave the same picture.

**Policy.** The service plays the audio as the hardware does (48048 Hz content at 48000 Hz
on the virtual clock, resampled by rate, not by time) in both modes. By default
(`RG_MOVIE_SYNC_AUDIO`, kept pending the user's decision) it chooses each frame from the
audio actually heard, so lip sync holds over the whole movie. On a 29.97 movie it repeats
about one frame per 1,000 (10 in `01_14`). `RG_MOVIE_SYNC_RETAIL` is exactly the measured
retail behaviour: frame n is shown from display start + n x 2 fields (2 x 2,460,060 bus
cycles, `RG_MOVIE_FIELD_CYCLES`), one new frame per `rg_movie_take_frame` call at most and
only once its 2-VBlank slot has come, never dropped or resynced, whatever rate the caller
pops at; audio drains at 48000 Hz. On the 29.97 / 48048 movies the audio therefore drifts
late by 1 ms per second (75 ms by the end of `01_01`), as on retail. Movie end and skip
stay tied to the frame counter. On the 30 fps movies the two modes give the same frames.

## Service (`rg_movie_*`)

### Composition decision: through the game's GS upload, not a host overlay

The game composites movies itself, and it draws everything else over them. The memory
note `native-mpeg-decode` STEP-34 traced it with `[texbind]`: the decoded frame is
uploaded as 896 16x16 PSMCT32 tiles to GS page 336 (`tbp0 10752`, the texture named by
`MovieSetTargetTexByName_1d5650`). `MovieDrawFrame_1d5870` draws a black 512x448 backdrop
and the movie texture as a sprite centred at `((512-w)/2, (448-h)/2) + (+0x17970,
+0x17974)`. It reads `w`/`h` from `D_004B3210`/`D_004B3214`, so the 336-line movies are
letterboxed by the game, not by the stream's DAR. It then draws `ScreenFadeBlockDraw`
(the fades), and the game's menus are drawn after it. `ingame-movie-display` shows the
same flags (`D_004817BC`) gating in-game movies. A host overlay would have to recreate
fades, letterboxing, z-order with menus and the attract-to-menu handover. The recomp
effort's overlay needed chroma-key and "is the movie live" heuristics, and three of them
failed. So the service hands frames to the game's own upload path: it writes the frame
in block layout into the VoBuf slot, and the game's own GIF packet DMAs it.

### States

```
IDLE --start--> PREROLL --FIFO full (or EOF)--> PLAYING --last frame's interval over--> COMPLETE
                   |                              |  ^
                   |                         pause|  |resume
                   |                              v  |
                   |                             PAUSED
  any state --skip--> STOPPED       any state --stop--> IDLE      start failure --> ERROR
  restart: back to PREROLL from frame 0          loop: at EOF rewind, PTS continues
```

| Game flag / call | Service |
| --- | --- |
| `MovieIsStarted()` = `D_004817BC` | `status.started`: set when PREROLL fills the FIFO (`fifo_frames`, default 2 = VoBuf), as `MovieReadThread` does on `VoBufIsFull && MovieAudioIsPreset` |
| `MovieIsFinished()` | `status.finished`: COMPLETE, STOPPED, ERROR or IDLE. A missing or broken movie reads as finished, so the game never hangs. |
| `MovieGetFrameCount()` = `D_004B3218` | `status.frames_decoded` (pictures decoded, ahead of display by the FIFO, as on the PS2) |
| `MovieFrameQueueSendNext` | `rg_movie_take_frame(now)`: a new frame (1) or keep the one on screen (0) |
| `MoviePlayerWaitTick` (once per game frame) | `rg_movie_update(now)` |
| `MoviePause` / `MovieResume` (`D_004817E8`) | `rg_movie_pause/resume`: the clock freezes, no frames are given out |
| loop flag `D_004817C8` (MovieOpen arg 7) | `config.loop`: rewind at EOF, frame PTS continue, audio wraps |
| player shut down early | `rg_movie_skip` (STOPPED), then `rg_movie_stop` |
| `MovieIsReadStalled()` | always 0: there are no disc reads |

**Clock.** `now` is the virtual clock in bus cycles (`ps2k_now()`). The audio position is
derived from it: the SPU2 HLE consumes the movie ring at exactly 48000 frames per virtual
second from display start (the moment the game issues `0x80E0`), and AutoDMA keeps
running through underruns. Content time is `frames / header_rate`. `take_frame` shows the
newest decoded frame whose PTS is at most half a frame past that time, so |A/V| <= half a
frame. Late frames are dropped, and B frames that will be dropped are not even decoded.
Without audio, the movie runs on its own PTS timeline in real time. Nothing reads the wall
clock, so a run is a pure function of the stream and the sequence of `now` values.

### Override list (the game boundary)

The five overrides are in `overrides/src/main/movie/`. Each is a small edit of the
generated file, with the `rg-override` sha256 header (`ingest.py --check`: 0 problems).
They compile cleanly with the `rg_game_*` flags plus `-Wall`. They call the game-facing
glue `src/movie/movie_game.h` (`rg_movie_g_*`: plain C types, declared locally in each
override, so `game/` needs no extra include path). The overrides are game-derived and not
CC0, see `overrides/README.md`. The final game link needs `rg_movie_game`, plus
`rg_movie_runtime` with the runtime. Evidence comes from `game/src/main/movie`,
`game/EXCLUDED.tsv` and `census/platform_misc.tsv`.

| Function (main image) | Today | Override |
| --- | --- | --- |
| `MovieOpen_1d5cf0` | resets the player globals; allocs VoBuf / ViBuf / MPEG work / read buffer / frame buffers; **writes `D_CTRL |= 3`, `D_STAT = 4`** (census `hwreg DMA D_CTRL/D_STAT ... MovieOpen yes`); `MpegStopDmaMaybe` + `VideoDecCreate` (`MpegCreate`, SDK asm); `AudioDecCreate`; `VideoDecSetStream` x2; `MovieStreamOpen` + a 0x14000-byte pre-read of the scrambled `.MVI` | keep the global resets, the VoBuf/tag/read-buffer allocs and `AudioDecCreate`; drop the DMAC pokes, libmpeg and stream calls; `rg_movie_start(path, ps2k_now())` with `config.audio = arg6`, `loop = arg7`. Fill `D_004B3210` (+0 width, +4 height, +8 frame count 0, +0xA8 state 0) from `status`, and set `D_004817B0/B4` to the stream size (MovieIsFinished needs >= 5 while playing). |
| `MoviePlayerStart_1d5b50` | `CreateThread` x3 (`DefMain_1d52b0`, `VideoDecMain_1d5240`, `MovieReadThread_1d4f50`), `AddIntcHandler(2, MovieVblankHandler)`, `AddDmacHandler(2, MovieDmacHandler)` | keep `AudioDecSetInputVolume(0)` and `MovieSetTargetTexByName`; build the per-slot upload packets with `GsUploadImage16Blocks_1d27a0` (what `VideoDecDecodeBs` does at frame 0); set `+0x17900 = 1`. No threads, no handlers. |
| `MoviePlayerWaitTick_1d5810` | 4x `ThreadYield` (called every game frame and inside the title's `MovieIsStarted` wait, SPIN 0x104F07BC) | `rg_movie_update(ps2k_now())`, then the `MovieReadThread` duties: feed `rg_movie_read_ss` bytes through `AudioDecPcmCallback_1d4ca0` (descriptor `+8 = readbuf-4`, `+0xC = n+4`, ring = `D_004817AC`) and `AudioDecSendToIop`; on the started edge `MovieDisplayStart_1d2b80` + `AudioDecStartThunk_1d30d0` + `D_004817BC = 1`; mirror pause (`D_004817E8`) to `rg_movie_pause`/`AudioDecPause`; write `D_004B3218 = frames_decoded`; on `finished` `VideoDecSetState(D_004B3210, 3)` |
| `MovieFrameQueueSendNext_1d4b20` | pops a VoBuf tag in state 2 and DMAs its GIF packet (`tag+0x40`) on ch2 | `rg_movie_take_frame(ps2k_now())`; on a frame, `rg_mv_to_ps2_blocks` into the next slot (`D_004B3330[0] + slot*0xE0000`), then the original `DrawCtxVif1HandlerStop` + `sceDmaSend(ch2, tag+0x40)` + `sceDmaSync`; otherwise `D_004817A0++` as on retail |
| `MoviePlayerShutdown_1d56c0` | `VideoDecFlush`, `D_004817E4 = 1`, spin until `D_004817E0` (SPIN 0x1D5700), Terminate/DeleteThread x3, remove the handlers, `VideoDecDelete`, `AudioDecReset/Delete`, `MovieStreamClose`, `CdDiskWatchSetEnabled` | `rg_movie_stop`, `AudioDecReset/Delete`, `CdDiskWatchSetEnabled(+0x17910)`, `+0x17900 = 0`. There are no threads to tear down, which also removes the recomp-era teardown deadlock (`movie-thread-teardown-deadlock`). |

These stay unchanged, because they only read the flags the overrides maintain:
`MovieIsStarted_1d5640`, `MovieIsFinished_1d5680`, `MovieGetFrameCount_1d52d0`,
`MoviePause_1d5b40`, `MovieResume_1d5b30`, `MovieIsReadStalled_1d62a0`,
`MovieSetTargetTexByName_1d5650`, `MovieDrawFrame_1d5870`, `MovieFrameResend_1d4be0`
(resends the current slot), `MovieAudioIsPreset_1d2490`, all of `AudioDec*`, the
title-overlay `title_TitleMovie*` functions and `EvCmdPlayMovie_*`.

These are no longer reached, so they need no port work:

- `MovieReadThread_1d4f50`, `VideoDecMain_1d5240`, `DefMain_1d52b0`,
  `VideoDecDecodeBs_1d29e0` (HANDLER-FLAG loops 0x1D2A00, 0x1D5274 and 0x1D5700 in
  SPIN.md), and `VideoDec*`/`ViBuf*`/`VoBuf*` apart from the slot ring.
- The `ViBuf*` functions hold all of the game's own IPU and DMA ch3/ch4 register accesses
  (census `D3_fromIPU_*`, `D4_toIPU_*`, `IPU_CTRL/CMD/BP ... yes`) and SPIN's 3 `IPU_CTRL`
  HW loops (`ViBufRestartDma_1d3e70` x2, `ViBufStopDma_1d4180`).
- `MovieVblankHandler_1d4c90` and `MovieDmacHandler_1d4b10`: EXCLUDED `asm-block game`,
  never installed. They still have trivial overrides (`EIntr(); return 0`, the retail
  `sync; ei` body), so any later caller (e.g. a clean-snapshot `MoviePlayModal_267c60`
  path) links.
- The libmpeg/IPU SDK band: the 114 `asm-function`/`asm-block` `sdk band:sce-sdk` rows
  under `src/main/movie` (`Ipu*`, `DmaIpu*`, `Mpeg*`).
  The game's own decoder layer (`VideoDecCreate_1d5470`, `VideoDecSetStream_1d5430`,
  `VideoDecDecodeBs_1d29e0`, `MovieReadThread_1d4f50`) is still compiled and names 7
  libmpeg entry points (`MpegCreate`, `MpegAddCallback`, `MpegAddStrCallback`,
  `MpegDemuxPssRing`, `MpegGetPicture`, `MpegReset`, `MpegIsEnd`); `src/sce/mpeg`
  binds them to stubs that say once on stderr that they were reached and return the
  value that ends the caller's work (docs/BINDINGS.md). `MpegStopDmaMaybe` has no
  caller left (the MovieOpen override drops it).
- `MovieStreamOpen/ReadSectors/Rewind/Close` and `MovieSectorsDescramble_1d3560`: the
  service reads the converted files, so the `.MVI` is not decrypted at runtime (PLAN).

`MoviePlayModal_267c60` drives the in-game event movies (`EvCmdPlayMovie_2455a0/268680`).
It has no source in this snapshot (asm-only unit, SPIN.md). It calls the same Movie* API
as `title_TitleMoviePlay_4f0600`, so it works through the overrides above once the clean
snapshot gives it a body.

### Runtime binding and the A/V mode

`rg_movie_runtime_attach()` (`src/movie/mv_runtime.c`, library `rg_movie_runtime`)
registers `rg_movie_runtime_service` with `rg_runtime_set_service_hook`. After init, that
hook passes the runtime's data dir to the service. Nothing else: since 2026-10-18 the 8
`ViBuf*` functions that held the game's IPU / DMA ch3-4 / D_ENABLE register code are stub
overrides that stop with a message (`rg_movie_g_unreachable`; statically unreachable per
`tools/native/reach_census.py`, docs/NATIVE-CPU.md section 8), so the IPU hwbus hooks, the
fromIPU/toIPU DMAC bindings, `rg_movie_ipu_get_stats` and the `movie.glue_ipu` test that
used to catch stray accesses are gone. (The hwbus keeps its own idle IPU stub for the
oracle tests.)

The A/V mode is a runtime setting: `RG_MOVIE_SYNC=audio` (the default, audio-led) or
`retail`, or `rg_movie_g_set_sync()`. `movie.glue_game` plays GAMEOVER through the glue in
both modes, with the start gate, pause, the SS feed and the missing-movie path.

## Tool: `rg-movie-play`

```
rg-movie-play [--data DIR] MOVIE                 decode all frames, print a summary
rg-movie-play --hash MOVIE                       index type pts fnv64 per frame
rg-movie-play --yuv out.yuv MOVIE                raw yuv420p ("-" = stdout)
rg-movie-play --bench MOVIE                      ms/frame and slowest frame
rg-movie-play --png prefix --every 30 MOVIE      PNGs (RG_HOST builds)
rg-movie-play --service [--sync audio|retail] [--pop-every N] [--skip-at SEC] [--hash] MOVIE
                                                 run through the service on a simulated
                                                 virtual clock; prints A/V drift and drops
rg-movie-play --window MOVIE                     play with sound, paced (RG_HOST builds)
```

`MOVIE` is a `.mpg` path or a game path (`MOVIE/00/TITLE01.MVI`, `00/TITLE01`,
`cdrom0:\MOVIE\00\TITLE01.MVI;1`), resolved under `--data` (default `$RG_DATA`, then
`data`).

## Tests (`ctest -L movie`)

27 tests. The `real_*` and `glue_game` tests and the tool runs skip (exit 77) without `RG_DATA`;
`real_psnr` also skips without an `ffmpeg` executable.

| Test | Checks |
| --- | --- |
| `vlc` | every Annex B table builds prefix-free; Kraft sums match the standard's unused code space; spot codes |
| `idct` | IEEE 1180 procedure (all 5 error bounds, 60,000 blocks); sparse path = full path |
| `color` | black/white/red BT.601 values; PS2 block order (column-major) and alpha |
| `audio_ss` | `SShd`/`SSbd` fields, block interleave, zero padding, chunked reads; host PCM order |
| `resolve` | game path forms map to `data/converted/MOVIE/<dir>/<name>` |
| `service_sm` | IDLE, then PREROLL (no frame before display start), PLAYING after 2 frames, every frame in order, COMPLETE; nothing after completion; stop gives IDLE |
| `service_skip` | skip while playing and during preroll: finished, no more frames |
| `service_restart` | restart after completion replays identically from frame 0; restart mid-movie |
| `service_pause` | clock and frame frozen while paused; resumes without drops |
| `service_loop` | loops continue in order with drift <= half a frame, never finished |
| `service_error` | missing movie or unmappable path: ERROR, finished, not started; an empty stream finishes |
| `av_sync`, `av_sync_30` | 10,000-frame movies at 29.97 or 30 fps with 48048 or 48000 Hz audio: max A/V error <= half a frame for the whole movie; retail pacing is exact on 30/48048 |
| `determinism_synth` | two identical service runs give identical frames and field counts |
| `real_frames` | 5 movies: frame count, size and rate as ffprobe reports them |
| `real_hashes` | per-frame hashes and full digests equal `reference.tsv` |
| `real_timestamps` | PTS = ffprobe's on every frame where ffprobe has one (1,898 frames), constant step |
| `real_service` | GAMEOVER through the service with a game-style path: completes, 210 frames, A/V <= half a frame, SS header, restart, skip; 01_11 (48000 Hz) in retail mode shows all 150 frames |
| `real_av_sync` | **the full 5.5-minute `97/01_14`**: max A/V error 16.7 ms (half a frame), 0 drops, 10 repeats (the 0.1%) |
| `real_determinism` | decoding after a rewind gives the same hashes; two service runs are identical |
| `real_psnr` | 5 movies vs `ffmpeg` (separate process): same frame count, worst PSNR >= 55 dB, max diff <= 8 (measured 63.0 dB / 3) |
| `av_sync_control` (WILL_FAIL) | retail pacing on 29.97/48048 must break the bound: it drifts 333 ms over 10,000 frames |
| `retail_cadence` | retail mode with a pop at every VBlank (VALIDATION.md 6): exactly j/2 + 1 frames shown at field j, every frame in order, none dropped; audio frames = elapsed x 48000 exactly; 2,000 frames over 3,998 fields; A/V at the last frame = 0.1% of elapsed (66.6 ms) |
| `retail_cadence_control` (WILL_FAIL) | expects a new frame at every VBlank pop in retail mode |
| `hashes_control` (WILL_FAIL) | one reference hash flipped must fail |
| `play_tool`, `play_tool_service` | the tool decodes GAMEOVER and plays 01_11 through the service |
| `glue_game` | the `rg_movie_g_*` glue (both A/V modes, start gate, pause, finished on a missing movie) (`glue_ipu` removed with the IPU hooks, 2026-10-18) |

Last run (2026-10-12, build dir `build/movie-i686`): **27/27 passed**, the two
WILL_FAIL controls included. That is 23 `rg-movie-tests` cases, 2 glue tests and the 2
tool runs. The dev machine has `RG_DATA` data and `C:\ffmpeg`, so nothing was skipped.

## Open issues

- **The overrides are untested in the game.** They are written and compile, but `game/`
  does not link yet. Points to check at the first real run:
  - the `AudioDecPcmCallback` feed descriptor and the free-space arithmetic on the
    AudioDec ring;
  - `D_004817B0/B4` held at 0x7FFFFFFF;
  - the slot write order in `MovieFrameQueueSendNext`.
- **The service hook has a single slot.** `rg_runtime_set_service_hook` replaces the
  previous hook, and the overlay manager wants it too. Until the runtime takes a list (or
  one combined hook calls both), whoever builds the game executable must call
  `rg_movie_runtime_service` from that combined hook. Also, nothing calls
  `rg_movie_runtime_attach()` yet: the game executable's `main` should, before
  `rg_runtime_init`.
- **Game frame rate during movies.** The service does not depend on it: audio-master
  pacing shows the right frame at any pop rate, and retail mode now paces by the virtual
  clock (one frame per two VBlanks, VALIDATION.md 6), so popping every VBlank or every
  other one gives the same frames. Only a caller that pops slower than every two VBlanks
  lags (as the retail game would).
- **Default sync policy (pending a user decision).** Audio-master deliberately departs
  from the hardware's 0.1% drift on 29.97 fps movies. `RG_MOVIE_SYNC_RETAIL` is the
  measured retail behaviour if strict faithfulness is preferred.
- **Looping audio** wraps the PCM. The SS stream for the AudioDec feed is not re-headered
  on a loop pass, and no retail call site is known to loop with audio.
- **The IPU CSC's alpha thresholds** (TH0/TH1) are not modelled: alpha is a constant 0x80.
  This is invisible with `MovieDrawFrame`'s blend and test settings.
