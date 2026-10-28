# MVI movies

Rogue Galaxy keeps its 89 FMV movies in `MOVIE/<dir>/*.MVI` (1980.9 MiB in all; see
[EXTRACT.md](EXTRACT.md) for which disc layer holds which directory). An MVI file is a plain
MPEG-2 program stream that is XOR-scrambled sector by sector. Its video is MPEG-2 Main
Profile @ Main Level. Its audio is a Sony `SShd`/`SSbd` block-interleaved 16-bit PCM
stream, carried in private stream 1.

Everything below was measured on all 89 files of the extracted `data/` (2026-10-11) with
an offline parser (`out/mvi/survey.py`, scratch). Several files were also checked
individually: `00/TITLE01`, `00/GAMEOVER`, `01/01_11`, `09/09_17C`, `13/13_07_1A`,
`97/01_14`, `98/09_08_1` and `99/STAFF_A`. Field values that never vary are stated as
facts. Values that do vary are listed in the per-movie table at the end.

Sources (documentation only, no code copied):

- The decompiled player in `../RGDecomp` (commit 2efa6b435), `src/main/movie/`:
  `MovieStreamReadSectors_1d3430`, `MovieSectorsDescramble_1d3560`, `StrSum4_1d3600`,
  `AudioDecPcmCallback_1d4ca0`, `MpegDemuxPssRing_115340` and `MoviePlayerStart_1d5b50`.
- Memory notes from the retired `recomp` effort (movie-menu-log, movie-audio-format,
  native-mpeg-decode).
- The `pc-assets` offline import of `GAMEOVER.MVI` (`tools/import_live_events.py`), which
  was used as an independent cross-check.

Two older memory claims are wrong. The audio is not ADX. And the "static 2048-byte
keystream" and the "per-sector LCG" are the same thing: the LCG restarts from the same seed
in every sector.

## File layout

```
offset 0                                     2048*N        2048*N+4
| sector 0 | sector 1 | ... | sector N-1 |   tail (4 bytes)  |
  \___________ MPEG-2 program stream, 16384-byte packs ___/  \_ 00 00 01 B9 _/
  every byte XORed with keystream[offset mod 2048]
```

- Every file is `2048*N + 4` bytes long. The 4-byte tail is the MPEG program end code
  (`00 00 01 B9`), scrambled with keystream bytes 0-3 like the start of a sector. The game
  reads whole sectors only (`MovieStreamReadSectors` rounds the size down to 2048), so it
  never reads the tail.
- The program stream is made of **16384-byte packs** (8 sectors), all the same size, with
  no gaps. Each pack begins with a 14-byte MPEG-2 pack header without stuffing. The SCR
  starts at 0.
- Pack 0 carries the only system header (`00 00 01 BB`).
- Only these stream ids appear: `E0` (video), `BD` (private stream 1, audio), `BE`
  (padding) and the final `B9`. Padding packets fill each pack to 16384 bytes. They are the
  "all-zero plaintext" sectors that made the keystream easy to recover.
- The pack header's program_mux_rate is 192200, 567200 or 629700 bytes/s (192000 or 567000
  in the two 48 kHz movies). The video stream's nominal bit rate is 3.0, 3.5, 4.0 or 4.5
  Mbit/s.

## Encryption

Each 2048-byte sector is XORed with the same 2048-byte keystream. That keystream is 512
little-endian 32-bit words:

```
k[0]   = seed = 0x98293255
k[i+1] = k[i] * 0x02E90EDD   (mod 2^32)
plain_word[i] = cipher_word[i] XOR k[i]      for i = 0..511, restarting every sector
```

So the keystream starts `55 32 29 98`, and the first word of every file decrypts to
`00 00 01 BA`. The transform is its own inverse.

How the game gets the seed:

1. `MovieStreamReadSectors_1d3430` de-obfuscates a 23-byte string stored at `0x0044B330`
   in `SCUS_974.90`: `out[i] = in[i] ^ k`, with `k` starting at `0x3E` and stepping
   `k = k*13 + 1` (mod 256).
2. `StrSum4_1d3600` adds the string's bytes into four byte lanes (byte `i` goes to lane
   `i % 4`, mod 256). The lanes, read as a little-endian word, give the seed.
3. `MovieSectorsDescramble_1d3560` applies the LCG to each 2048-byte block it reads. It is
   gated on the global `D_004817F0`, which is non-zero in the retail game, and every
   retail movie is scrambled.

Using the extracted ELF, `rg-extract-mvi-tests` (run with `RG_DATA` set) re-derives
`0x98293255` from step 1. The seed does not depend on the movie. All 89 files decrypt to
valid program streams with it.

## Video stream (`E0`)

| Field | Value |
| --- | --- |
| Codec | MPEG-2 video, Main Profile @ Main Level (`profile_and_level` 0x48), 4:2:0 |
| Width | 512 |
| Height | 448 (`TITLE01`, `TITLE02`, `STAFF_A`) or 336 (the other 86, letterboxed movies) |
| Frame rate | `frame_rate_code` 4 = 30000/1001 (73 movies) or 5 = 30 (16 movies), `frame_rate_extension` 0 |
| Aspect | `aspect_ratio_information` 2 = 4:3 DAR (75 movies) or 1 = square samples (14 movies) |
| Scan | `progressive_sequence` 1. Every picture is a progressive frame picture with `repeat_first_field` 0. `top_field_first` is set in 6 movies but has no effect. |
| Sequence headers | exactly one per file, at the start |
| GOP | N = 18, M = 3 (I BB P BB P ...) for most of the 6784 GOPs, with shorter GOPs (16, 8, 20, 14 ...) at scene cuts. 661 GOPs are closed (at least one per file) and the rest are open. FFmpeg decodes every picture of every file tested, including the leading B pictures. |
| `low_delay` | 0 (B pictures are present) |
| VBV buffer | 896/1152/1280/1408 kbit, matching the nominal bit rate |

The frame counts range from 150 (`01/01_11`) to 14760 (`99/STAFF_A`). The 89 movies hold
116,956 frames in all. Video PTS steps are 3003 ticks (90 kHz) at 29.97 fps or 3000 at 30
fps. The first PTS is between 4065 and 12838 ticks.

Per-movie variations (lists of which movies differ):

- 30 fps: `00/TITLE01`, `TITLE02`, `W_ARISA/B/C`, `W_ROZAA`, `01/01_11`, `02/02_01`,
  `99/13_55A`-`G`, `99/STAFF_A`.
- Square-sample aspect (code 1): `00/GAMEOVER`, `W_ARISA/B/C`, `W_EDENA/B`, `W_ROSEA/B`,
  `01/01_01`, `01/01_11`, `02/02_05`, `13/13_07_2C`, `99/11_01A`, `99/STAFF_A`.

## Audio stream (`BD`)

Each private-stream-1 payload begins with 4 framing bytes, always `FF A0 00 00`. The game
skips them too (`AudioDecPcmCallback_1d4ca0` copies from payload+4, length-4). The rest of
the payloads, concatenated, form one stream:

```
"SShd"  u32 24                 header chunk, 24 bytes of body:
        u32 format    = 1        16-bit signed little-endian PCM
        u32 rate      = 48048    sample rate (Hz); 48000 in 01/01_11 and 99/STAFF_A
        u32 channels  = 2
        u32 interleave= 512      bytes per channel per block
        s32 -1, s32 -1           (unused here; probably loop points)
"SSbd"  u32 body_len           body chunk
        body: [L 512 bytes][R 512 bytes][L 512 bytes][R 512 bytes] ...
```

- The body is **block-interleaved**: 256 left samples, then 256 right samples, and so on.
  It is not sample-interleaved. Played as LRLR it sounds robotic. `body_len` is always a
  multiple of 1024. The final payload is padded with zeros after `body_len`.
- All 89 movies are stereo with a 512-byte interleave. 87 are at 48048 Hz and 2 at
  48000 Hz.
- The audio PES packets carry a PTS. Fitting PTS against byte position gives exactly the
  header rate (48048.0 or 48000.0) in every file. The residual is 18-20 ticks (0.2 ms), the
  same in every file, which is encoder rounding.

## Timing and sync

- **In all 89 files, the first audio PTS equals the first video PTS.** So audio sample 0
  is presented with the first displayed frame.
- On that timeline the audio and video lengths differ by -32 to +36 ms at the end (the
  audio usually runs a few ms longer).
- **48048 Hz.** 48048 = 48000 × 1.001. The encoder stamped the audio against a nominal
  30 or 29.97 fps PTS clock while the PS2 SPU2 plays at a fixed 48000 Hz. For the 30 fps
  movies (`frame_rate_code` 5) this is exactly NTSC compensation: on hardware, 30-fps
  content shown at 59.94/2 runs 1.001 slower, and so does 48048-Hz audio played at
  48000 Hz. Both stay in sync. For the 29.97 fps movies, the PTS timeline itself already
  runs at 29.97, so playing the audio at 48000 Hz would drift 0.1% late (0.33 s over
  `97/01_14`, 5.5 min). Whether the game's player corrects for this, or the hardware simply
  drifts, is an open question (see below). The two 48000-Hz movies (`01/01_11`,
  `99/STAFF_A`) are 30 fps with a 192000/567000 mux rate. They were evidently encoded
  without the compensation.

## Conversion (`rg-extract --convert-movie`)

`src/extract/mvi.{h,cpp}` (CC0, written from this document) converts one movie into two
files:

| Output | Content |
| --- | --- |
| `OUT.mpg` | The descrambled MPEG-2 program stream, bit-exact. Every audio (`BD`) packet becomes a padding (`BE`) packet of the same size, so the video PES packets, the pack layout, the SCRs and the PTS/DTS are untouched and the file is the same size as the MVI. The tail decodes to the program end code. |
| `OUT.wav` | Canonical RIFF/WAVE, PCM 16-bit LE, channels and rate from `SShd` (rate written as-is: 48048 or 48000), de-interleaved to LRLR. Sample 0 is presented at the first video PTS: silence is prepended, or samples dropped, if the first audio PTS differs. That never happens on the retail disc. |

Why this choice:

- **MPEG-PS for video.** The source already is a valid MPEG-2 PS once descrambled, so the
  converter only XORs and relabels whole packets. It never rewrites or re-encodes the
  bitstream. FFmpeg's `mpeg` demuxer and `mpeg2video` decoder are both in an LGPL build
  (neither needs `--enable-gpl`). The converter keeps the 16 KiB pack structure and the
  SCR/PTS, so seeking and timestamps work as on the PS2. Matroska would mean computing a
  per-frame PTS from GOP temporal references and writing EBML. That is more code and more
  risk, for no gain. An elementary `.m2v` would lose the timestamps.
- **WAV for audio.** FFmpeg does not recognise substream `FF` of private stream 1 (ffprobe
  on a descrambled MVI shows only the video stream), and it has no decoder for
  block-interleaved `SShd`. Re-interleaving to standard PCM costs nothing and needs no
  decoder at runtime: the P4 movie service can stream the WAV to SDL directly, and FFmpeg
  is needed only for video. The DVD-LPCM substream (`A0`) was ruled out because it allows
  only 48000/96000/44100/32000 Hz, which cannot express 48048 without changing timing.
  Size: the `.mpg` files are exactly the size of the MVI files (audio packets become
  padding), 2,077,131,108 bytes for all 89; the `.wav` files add 749,815,628 bytes.
  Dropping the padding packets would save about 0.7 GB but change the byte layout.

Interface: `rgx::mvi::convert_movie(in, out_mpg, out_wav, &info, &err)`, which streams with
a 1 MiB window and removes partial outputs on error, and `convert_movie_memory(...)` for
tests. The command line is `rg-extract --convert-movie IN.MVI OUT`, which writes
`OUT.mpg` and `OUT.wav`. It returns 0 on success, 1 for usage, 2 if the input is
unreadable, 5 if a write fails and 6 for a malformed movie. The extraction pass calls
the same function for every `MOVIE/<dir>/<name>.MVI` and writes
`data/converted/MOVIE/<dir>/<name>.{mpg,wav}` (docs/EXTRACT.md).

The converter refuses (exit code 6):

- input whose first sector does not descramble to a pack header;
- a lost start-code sync, a truncated packet, or an unknown stream id;
- an unknown private-stream substream;
- a missing or implausible `SShd`/`SSbd`, a non-PCM format, or audio shorter than
  `body_len`;
- data after the end code;
- a missing MPEG-2 sequence header or extension.

## Verification (2026-10-11)

Tests:

- `rg-extract-mvi-tests` (CTest) runs with no game data. It checks the keystream words,
  that `descramble()` gives the same result however the input is chunked, and the seed
  derivation. It builds a synthetic movie (pack, system header, MPEG-2 sequence header
  split across PES packets, an `SShd` header plus a body split mid-block over 2 packets,
  zero fill, padding, end code), scrambles it and converts it. The `.mpg` must equal the
  expected bytes, and the WAV header and PCM must match, in sync and with ±2-3 frame PTS
  offsets (silence prepended or samples dropped). It also checks refusals: an unscrambled
  input, a truncation, empty input and an unknown stream id.
- With `RG_DATA=data`, the test also re-derives the seed from `SCUS_974.90` and converts
  `TITLE01` fully. A copy cut at 2 MiB must be refused.
- `rg-extract-tests` still passes.

All 89 movies convert without error. The picture counts sum to 116,956, the same as the
independent Python survey. Each 43 MB movie converts in about 0.16 s (warm cache).

ffprobe/ffmpeg (tools only) on 8 converted movies:

| Movie | Layer | Decoded frames (= pictures) | Decode errors | Video s | WAV | A/V end diff |
| --- | --- | --- | --- | --- | --- | --- |
| 00/TITLE01 | 0 | 540, 512x448, 30/1 | 0 | 18.000 | 48048 Hz 2 ch 18.003 s | +3.3 ms |
| 00/GAMEOVER | 0 | 210, 512x336, 30000/1001 | 0 | 7.007 | 48048 Hz 7.012 s | +4.7 ms |
| 01/01_11 | 0 | 150, 512x336, 30/1 | 0 | 5.000 | 48000 Hz 5.003 s | +2.7 ms |
| 09/09_17C | 1 | 570, 512x336, 30000/1001 | 0 | 19.019 | 48048 Hz 18.989 s | -30.0 ms |
| 13/13_07_1A | 1 | 454, 512x336, 30000/1001 | 0 | 15.148 | 48048 Hz 15.153 s | +4.4 ms |
| 97/01_14 | 0 | 9835, 512x336, 30000/1001 | 0 | 328.161 | 48048 Hz 328.163 s | +1.3 ms |
| 98/09_08_1 | 1 | 5048, 512x336, 30000/1001 | 0 | 168.435 | 48048 Hz 168.440 s | +4.6 ms |
| 99/STAFF_A | 1 | 14760, 512x448, 30/1 | 0 | 492.000 | 48000 Hz 492.000 s | 0.0 ms |

Each converted `.mpg` was checked by decoding every frame with ffmpeg and comparing
framemd5. It is identical to an independent numpy descramble of the original MVI, decoded
by the same ffmpeg. For 8 of 8 movies that gives identical first, last and all frames.
The `.wav` probes as `pcm_s16le` at the stated rate. On the PCM checks: the mean absolute
sample-to-sample step is 12 (LRLR order) and 4089 (byte-swapped), and L/R correlation is
0.71. Those are the signatures of correctly de-interleaved little-endian stereo.

`GAMEOVER` was also checked against the `pc-assets` offline import, which has its own
descramble and its own PCM de-interleave. All 210 RGBA frames are byte-identical. Its
`audio.pcm` (1,347,584 bytes) is byte-identical to our WAV data. One frame (200) of
`13_07_1A` was viewed and looks correct (colour, geometry, no block errors).

Sync: every file has its first audio PTS equal to its first video PTS. The audio PTS is
linear at the header rate in every file, so the WAV's sample 0 maps to the first frame. The
end-of-stream differences above are the authored lengths, and stay within ±36 ms across
all 89 files.

## Open issues

- **48048 Hz on 29.97 fps movies.** It isn't yet known whether the PS2 player resyncs
  video to the audio clock or drifts 0.1%. Before P4 chooses a playback clock, read the
  game's sync logic: `VideoDecMain_1d5240` and `MovieVblankHandler_1d4c90` against the
  audio position from `AudioDecIopGetArea_1d2df0`. The converted files keep the authored
  timeline, so either policy can be applied at playback (play the WAV at its header rate,
  or at 48000 Hz with frames paced by the audio clock).
- **Aspect.** The 336-line movies are letterboxed content for a 448-line screen. Code 1
  versus code 2 is probably an encoder setting, not a display intent. P4 should place
  frames the way the game does (the target texture in `MovieSetTargetTexByName_1d5650`),
  not by the stream's DAR.
- The system header still lists stream `BD` although no `BD` packets remain. FFmpeg
  ignores this. Rewriting the header is not worth changing the byte layout.
- Wired into the extraction pass (2026-10-11): outputs go to
  `data/converted/MOVIE/<dir>/<name>.{mpg,wav}`, listed in the manifest's `converted`
  section, and the original `.MVI` files stay in place byte-identical, because the game's
  own movie code still reads them by sector until the movie layer is replaced (P4).

## Per-movie table

Frames are picture start codes. Video seconds are frames divided by the frame rate. Audio
seconds are `body_len / 4 / rate`. Bytes are the file size without the 4-byte tail.

| File | Bytes | Size | fps | Aspect | Frames | Video s | Audio Hz | Audio s | Mux B/s |
| --- | ---: | --- | --- | --- | ---: | ---: | ---: | ---: | ---: |
| 00/GAMEOVER.MVI | 2,195,460 | 512x336 | 29.97 | 1:1 SAR | 210 | 7.007 | 48048 | 7.012 | 192200 |
| 00/M_TRAINA.MVI | 3,096,580 | 512x336 | 29.97 | 4:3 | 181 | 6.039 | 48048 | 6.042 | 192200 |
| 00/M_TRAINB.MVI | 3,571,716 | 512x336 | 29.97 | 4:3 | 211 | 7.040 | 48048 | 7.044 | 192200 |
| 00/M_TRAINC.MVI | 4,096,004 | 512x336 | 29.97 | 4:3 | 241 | 8.041 | 48048 | 8.045 | 567200 |
| 00/M_TRAIND.MVI | 3,358,724 | 512x336 | 29.97 | 4:3 | 195 | 6.506 | 48048 | 6.511 | 192200 |
| 00/RUSH.MVI | 76,251,140 | 512x336 | 29.97 | 4:3 | 4513 | 150.584 | 48048 | 150.585 | 192200 |
| 00/TITLE01.MVI | 8,404,996 | 512x448 | 30 | 4:3 | 540 | 18.000 | 48048 | 18.003 | 192200 |
| 00/TITLE02.MVI | 30,965,764 | 512x448 | 30 | 4:3 | 1830 | 61.000 | 48048 | 61.000 | 192200 |
| 00/W_ARISA.MVI | 6,455,300 | 512x336 | 30 | 1:1 SAR | 336 | 11.200 | 48048 | 11.205 | 192200 |
| 00/W_ARISB.MVI | 25,362,436 | 512x336 | 30 | 1:1 SAR | 1244 | 41.467 | 48048 | 41.468 | 192200 |
| 00/W_ARISC.MVI | 4,784,132 | 512x336 | 30 | 1:1 SAR | 270 | 9.000 | 48048 | 9.010 | 192200 |
| 00/W_BEDANA.MVI | 5,783,556 | 512x336 | 29.97 | 4:3 | 342 | 11.411 | 48048 | 11.413 | 192200 |
| 00/W_BEDANB.MVI | 7,569,412 | 512x336 | 29.97 | 4:3 | 443 | 14.781 | 48048 | 14.785 | 192200 |
| 00/W_EDENA.MVI | 10,534,916 | 512x336 | 29.97 | 1:1 SAR | 719 | 23.991 | 48048 | 23.992 | 192200 |
| 00/W_EDENB.MVI | 15,007,748 | 512x336 | 29.97 | 1:1 SAR | 983 | 32.799 | 48048 | 32.805 | 192200 |
| 00/W_GHOSTA.MVI | 9,846,788 | 512x336 | 29.97 | 4:3 | 583 | 19.453 | 48048 | 19.458 | 192200 |
| 00/W_GHOSTB.MVI | 5,685,252 | 512x336 | 29.97 | 4:3 | 330 | 11.011 | 48048 | 11.013 | 192200 |
| 00/W_JYURAA.MVI | 4,653,060 | 512x336 | 29.97 | 4:3 | 271 | 9.042 | 48048 | 9.047 | 192200 |
| 00/W_JYURAB.MVI | 7,667,716 | 512x336 | 29.97 | 4:3 | 450 | 15.015 | 48048 | 15.020 | 192200 |
| 00/W_JYURAC.MVI | 9,306,116 | 512x336 | 29.97 | 4:3 | 541 | 18.051 | 48048 | 18.057 | 567200 |
| 00/W_ROSEA.MVI | 4,407,300 | 512x336 | 29.97 | 1:1 SAR | 320 | 10.677 | 48048 | 10.677 | 192200 |
| 00/W_ROSEB.MVI | 2,686,980 | 512x336 | 29.97 | 1:1 SAR | 180 | 6.006 | 48048 | 6.010 | 192200 |
| 00/W_ROZAA.MVI | 4,390,916 | 512x336 | 30 | 4:3 | 261 | 8.700 | 48048 | 8.701 | 567200 |
| 00/W_ROZAB.MVI | 5,701,636 | 512x336 | 29.97 | 4:3 | 331 | 11.044 | 48048 | 11.045 | 192200 |
| 00/W_ZERAA.MVI | 7,536,644 | 512x336 | 29.97 | 4:3 | 443 | 14.781 | 48048 | 14.785 | 192200 |
| 00/W_ZERAB.MVI | 5,160,964 | 512x336 | 29.97 | 4:3 | 300 | 10.010 | 48048 | 10.011 | 192200 |
| 01/01_01.MVI | 39,550,980 | 512x336 | 29.97 | 1:1 SAR | 2233 | 74.508 | 48048 | 74.544 | 192200 |
| 01/01_11.MVI | 2,818,052 | 512x336 | 30 | 1:1 SAR | 150 | 5.000 | 48000 | 5.003 | 192000 |
| 02/02_01.MVI | 4,390,916 | 512x336 | 30 | 4:3 | 261 | 8.700 | 48048 | 8.701 | 567200 |
| 02/02_05.MVI | 135,430,148 | 512x336 | 29.97 | 1:1 SAR | 5965 | 199.032 | 48048 | 199.033 | 192200 |
| 04/04_01_3.MVI | 3,457,028 | 512x336 | 29.97 | 4:3 | 210 | 7.007 | 48048 | 7.012 | 192200 |
| 04/04_03.MVI | 8,470,532 | 512x336 | 29.97 | 4:3 | 510 | 17.017 | 48048 | 17.018 | 192200 |
| 06/06_03.MVI | 21,381,124 | 512x336 | 29.97 | 4:3 | 991 | 33.066 | 48048 | 33.066 | 192200 |
| 07/07_01A.MVI | 6,111,236 | 512x336 | 29.97 | 4:3 | 360 | 12.012 | 48048 | 12.015 | 192200 |
| 07/07_01B.MVI | 10,207,236 | 512x336 | 29.97 | 4:3 | 600 | 20.020 | 48048 | 20.023 | 192200 |
| 07/07_03A.MVI | 9,158,660 | 512x336 | 29.97 | 4:3 | 540 | 18.018 | 48048 | 18.019 | 567200 |
| 07/07_03B.MVI | 11,239,428 | 512x336 | 29.97 | 4:3 | 660 | 22.022 | 48048 | 22.026 | 192200 |
| 07/07_05.MVI | 8,077,316 | 512x336 | 29.97 | 4:3 | 475 | 15.849 | 48048 | 15.851 | 192200 |
| 07/07_06A.MVI | 11,190,276 | 512x336 | 29.97 | 4:3 | 660 | 22.022 | 48048 | 22.026 | 192200 |
| 07/07_06B.MVI | 18,251,780 | 512x336 | 29.97 | 4:3 | 1070 | 35.702 | 48048 | 35.703 | 192200 |
| 09/09_17A.MVI | 3,457,028 | 512x336 | 29.97 | 4:3 | 209 | 6.974 | 48048 | 6.974 | 192200 |
| 09/09_17B.MVI | 6,782,980 | 512x336 | 29.97 | 4:3 | 405 | 13.514 | 48048 | 13.485 | 567200 |
| 09/09_17C.MVI | 9,617,412 | 512x336 | 29.97 | 4:3 | 570 | 19.019 | 48048 | 18.989 | 567200 |
| 10/10_12A.MVI | 20,955,140 | 512x336 | 29.97 | 4:3 | 1237 | 41.275 | 48048 | 41.276 | 567200 |
| 10/10_12B.MVI | 5,062,660 | 512x336 | 29.97 | 4:3 | 300 | 10.010 | 48048 | 10.011 | 192200 |
| 11/11_01E.MVI | 14,811,140 | 512x336 | 29.97 | 4:3 | 865 | 28.862 | 48048 | 28.867 | 192200 |
| 11/11_01G.MVI | 12,009,476 | 512x336 | 29.97 | 4:3 | 706 | 23.557 | 48048 | 23.560 | 192200 |
| 13/13_07_1A.MVI | 6,750,212 | 512x336 | 29.97 | 4:3 | 454 | 15.148 | 48048 | 15.153 | 192200 |
| 13/13_07_2C.MVI | 3,407,876 | 512x336 | 29.97 | 1:1 SAR | 300 | 10.010 | 48048 | 10.011 | 192200 |
| 13/13_07_2G.MVI | 5,652,484 | 512x336 | 29.97 | 4:3 | 330 | 11.011 | 48048 | 11.013 | 192200 |
| 97/01_14.MVI | 209,453,060 | 512x336 | 29.97 | 4:3 | 9835 | 328.161 | 48048 | 328.163 | 192200 |
| 97/02_06A.MVI | 11,550,724 | 512x336 | 29.97 | 4:3 | 672 | 22.422 | 48048 | 22.426 | 192200 |
| 97/02_06B.MVI | 7,634,948 | 512x336 | 29.97 | 4:3 | 458 | 15.282 | 48048 | 15.286 | 192200 |
| 97/02_06C.MVI | 21,250,052 | 512x336 | 29.97 | 4:3 | 1253 | 41.808 | 48048 | 41.809 | 192200 |
| 97/04_015.MVI | 40,681,476 | 512x336 | 29.97 | 4:3 | 2401 | 80.113 | 48048 | 80.117 | 192200 |
| 97/04_01_1.MVI | 27,983,876 | 512x336 | 29.97 | 4:3 | 1680 | 56.056 | 48048 | 56.061 | 567200 |
| 97/04_14.MVI | 43,057,156 | 512x336 | 29.97 | 4:3 | 2518 | 84.017 | 48048 | 84.017 | 192200 |
| 97/06_13.MVI | 19,628,036 | 512x336 | 29.97 | 4:3 | 1022 | 34.101 | 48048 | 34.105 | 192200 |
| 97/06_15A.MVI | 11,321,348 | 512x336 | 29.97 | 4:3 | 662 | 22.089 | 48048 | 22.090 | 192200 |
| 97/06_15B.MVI | 11,157,508 | 512x336 | 29.97 | 4:3 | 661 | 22.055 | 48048 | 22.058 | 567200 |
| 97/06_15C.MVI | 5,554,180 | 512x336 | 29.97 | 4:3 | 330 | 11.011 | 48048 | 11.013 | 192200 |
| 97/07_02.MVI | 117,456,900 | 512x336 | 29.97 | 4:3 | 6922 | 230.964 | 48048 | 230.969 | 192200 |
| 98/09_03.MVI | 15,826,948 | 512x336 | 29.97 | 4:3 | 923 | 30.797 | 48048 | 30.801 | 192200 |
| 98/09_05.MVI | 47,087,620 | 512x336 | 29.97 | 4:3 | 2768 | 92.359 | 48048 | 92.361 | 192200 |
| 98/09_06A.MVI | 44,269,572 | 512x336 | 29.97 | 4:3 | 2986 | 99.633 | 48048 | 99.634 | 567200 |
| 98/09_06B.MVI | 41,959,428 | 512x336 | 29.97 | 4:3 | 2753 | 91.858 | 48048 | 91.860 | 192200 |
| 98/09_08_1.MVI | 85,884,932 | 512x336 | 29.97 | 4:3 | 5048 | 168.435 | 48048 | 168.440 | 567200 |
| 98/09_08_2A.MVI | 43,417,604 | 512x336 | 29.97 | 4:3 | 2544 | 84.885 | 48048 | 84.886 | 192200 |
| 98/09_08_2B.MVI | 9,175,044 | 512x336 | 29.97 | 4:3 | 540 | 18.018 | 48048 | 18.019 | 192200 |
| 99/11_01A.MVI | 13,352,964 | 512x336 | 29.97 | 1:1 SAR | 888 | 29.630 | 48048 | 29.634 | 192200 |
| 99/11_01B.MVI | 18,907,140 | 512x336 | 29.97 | 4:3 | 986 | 32.900 | 48048 | 32.900 | 629700 |
| 99/11_01C.MVI | 10,665,988 | 512x336 | 29.97 | 4:3 | 556 | 18.552 | 48048 | 18.520 | 629700 |
| 99/11_01D.MVI | 17,793,028 | 512x336 | 29.97 | 4:3 | 929 | 30.998 | 48048 | 30.998 | 192200 |
| 99/11_01F.MVI | 13,533,188 | 512x336 | 29.97 | 4:3 | 705 | 23.524 | 48048 | 23.528 | 192200 |
| 99/11_01H.MVI | 19,611,652 | 512x336 | 29.97 | 4:3 | 1014 | 33.834 | 48048 | 33.838 | 192200 |
| 99/13_05A.MVI | 27,443,204 | 512x336 | 29.97 | 4:3 | 1421 | 47.414 | 48048 | 47.419 | 629700 |
| 99/13_05B.MVI | 23,085,060 | 512x336 | 29.97 | 4:3 | 1380 | 46.046 | 48048 | 46.050 | 192200 |
| 99/13_05C.MVI | 41,943,044 | 512x336 | 29.97 | 4:3 | 2214 | 73.874 | 48048 | 73.878 | 192200 |
| 99/13_07_1B.MVI | 89,473,028 | 512x336 | 29.97 | 4:3 | 5277 | 176.076 | 48048 | 176.080 | 192200 |
| 99/13_07_2A.MVI | 7,782,404 | 512x336 | 29.97 | 4:3 | 406 | 13.547 | 48048 | 13.549 | 629700 |
| 99/13_07_2B.MVI | 27,803,652 | 512x336 | 29.97 | 4:3 | 1444 | 48.181 | 48048 | 48.186 | 629700 |
| 99/13_55A.MVI | 6,520,836 | 512x336 | 30 | 4:3 | 345 | 11.500 | 48048 | 11.503 | 192200 |
| 99/13_55B.MVI | 8,241,156 | 512x336 | 30 | 4:3 | 436 | 14.533 | 48048 | 14.535 | 192200 |
| 99/13_55C.MVI | 6,275,076 | 512x336 | 30 | 4:3 | 333 | 11.100 | 48048 | 11.104 | 629700 |
| 99/13_55D.MVI | 7,979,012 | 512x336 | 30 | 4:3 | 420 | 14.000 | 48048 | 14.002 | 192200 |
| 99/13_55E.MVI | 5,816,324 | 512x336 | 30 | 4:3 | 396 | 13.200 | 48048 | 13.203 | 192200 |
| 99/13_55F.MVI | 6,651,908 | 512x336 | 30 | 4:3 | 351 | 11.700 | 48048 | 11.700 | 192200 |
| 99/13_55G.MVI | 7,405,572 | 512x336 | 30 | 4:3 | 390 | 13.000 | 48048 | 13.000 | 192200 |
| 99/STAFF_A.MVI | 249,774,084 | 512x448 | 30 | 1:1 SAR | 14760 | 492.000 | 48000 | 492.000 | 567000 |
