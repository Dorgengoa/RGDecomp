# Native audio engine (de-emulation lane: sound)

PLAN.md D9 / "Native end state": *"SIF/IOP HLE, IOP RAM, sdremote packets, SPU2-style
mixer, SK servers -> Native audio engine called by the game's sound API: loads
banks/sequences/streams directly, host mixing."* This lane follows the NATIVE-FS pattern:
census script, design, native service, game-side overrides at the highest sensible
boundary, the old path kept as an oracle behind a switch, verification against it.

Status (2026-10-17): **all four sound paths run natively** (SE notes, sequenced BGM,
PCM streams, movie audio). `RG_AUDIO=native` (the default) sends no sound SIF RPC, no SIF
DMA and touches no IOP memory for sound (the HLE's sdr_driver received 0 calls in a
power-on run to field 9,000); `RG_AUDIO=hle` is the old path unchanged;
`RG_AUDIO=compare` runs both from the same command stream and writes both outputs.
Verified against the HLE oracle from power-on to field 9,000 (**SNR 56.6 dB**, peak
difference 10 LSB) and from the title / field / battle fixtures (**56.9 / 57.4 / 57.1
dB**); native mode against the oracle: levels within 0.16-0.28 dB (p95), semitone-band
spectra correlate >= 0.995 (p5); native runs are deterministic (section 3). ctest
`-L audio` 8/8; with `-L "audio|sound|fixtures|native_fs"` 38/38.

| Part | Where |
| --- | --- |
| Census | `tools/native/audio_census.py` (`static`, `dynamic`) -> `census/native_audio_*.tsv` |
| Engine | `src/native/audio/` (`rg_native_audio`): `rg_audio.h` API, `ra_mix.c` voices/buses/reverb/streams, `ra_synth.c` notes -> voices, `ra_seq.c` SQ player, `ra_engine.c` state/banks/tracks/clock, `ra_hd.c` HD parser, `ra_game.c` game command set, `ra_host.c` env/logs/WAV/runtime glue (HOST for save states) |
| Game side | `include/port/native_audio.h`; overrides `overrides/src/main/sound/` (7), `overrides/src/main/movie/AudioDecCreate_1d3210.c`, `AudioDecDelete_1d31d0.c`, `overrides/src/main/sys/SifDmaSendSync_1d2c20.c` |
| Oracle | `src/ps2/iop/sound` + `src/ps2/spu` (unchanged except the effect-attr fix, section 5, and `snd_clock_frame()`) |
| Compare | `RG_AUDIO=compare`, `RG_AUDIO_NATIVE_WAV`, `tools/native/audio_compare.py` |
| Tests | `tests/native_audio/` (`native-audio-tests`), ctest label `audio` |
| Build | `tools/native/audio_build.ps1` (build dir `build/naudio-i686`, ninja -j4) |

## 1. Census

`python tools/native/audio_census.py static` (no build): the sound worker's command table,
what each command sends, every literal sender, the rest of the IOP-facing surface and its
callers 2 more levels up. Result (2026-10-17):

- **One queue.** Every driver request goes through `SoundQueueCmd_1b6d60(cmd, args, size)`
  (via `SoundSendCmd_1b6cc0` varargs): 38 thread commands (table `D_0044AE10`, ids
  0x01..0x26), synchronous, one s32 result. 32 have literal senders; 0x0B, 0x10, 0x11,
  0x13, 0x14, 0x1C have none (implemented anyway).
- Each command became 1-3 SK blocks (`SoundIopSendCmdG*S*` -> `sceSdRemote(0x90F0)`) or
  libsd calls (0x21-0x25 `sceSdRemote 0x8010/0x8050/0x8070/0x8130`), 0x26 = raw libsd
  pass-through (the movie layer: 0x80E0 BlockTrans, 0x8100 status, 0x80D0 VoiceTrans).
- **Data uploads outside the queue** (raw SIF DMA + IOP heap): `SoundBankUploadPart_1ba770`
  (HD to IOP heap, BD through 1 KiB staging + cmd 9 = G0/0xA), `SoundBankLoad_1b9f00`
  (SQ sequences, cmd 3), `AudioDecCreate_1d3210` + `AudioDecSendToIop2Area_1d2ca0` via
  `SifDmaSendSync_1d2c20` (movie PCM ring), `SoundStreamSlotSendToIopMaybe_1bd760`
  (PCM stream blocks, `SifDmaSendSync_1c21e0` + pcm_mixer 0x8090).
- **pcm_mixer** RPC 0x123456: only `SoundRpcCall_1bc5e0`; fnos 0x8000 init (`SoundRpcInit`),
  0x80A0/0x8090 (stream slot thread), 0x8100/0x8400 start/stop, 0x200 volume, 0x10 shutdown.
- Init: `SoundIopInit_1b7160` (sdremote init, master volumes, SK settings),
  `SoundSpuInit_1bb710` (effect areas, reverb, volumes; through the queue).
- Above that everything is game logic (categories, bank tables, the EE's own SMF
  sequencer `SoundSeq*`, stream slots, AudioDec ring, BGM/event/character SE APIs:
  207 functions in levels 1-3).

`dynamic LOG...` counts commands in a run's `RG_AUDIO_CMDLOG` (one line per command;
`B` bank/sequence loads, `P` pcm calls, `K` native key ons, `V` sounding voices once a
second). Golden route power-on to field 9,000 (`out/naudio/cmp4/cmdlog.tsv`,
`census/native_audio_dynamic.tsv`): 12,280 log lines of 38 kinds (key ons split per track). Dominant: 9,032 movie
position polls (0x26/0x8100, 3 per field while a movie plays), 1,161 + 1,161 all-notes-off
/ all-sound-off on track 7 (once per field during the opening), 566 input-volume sets
(0x25); then 38 sequence volumes, 33 key ons (116 voice key ons), 25 sequence stops, 21
bank attaches, 16 bank loads, 13 SE-input attaches, 10 reverb depths, 3 sequence loads /
attaches / plays, 6 movie starts/stops, 1,960 PCM blocks (not logged per block), 1 PCM
init/start/volume.  Unused on this route: 0x0B, 0x0D, 0x10, 0x11, 0x13, 0x14, 0x1C, 0x1F
(bend sent only inside key on here).

## 2. Design

### Boundary

The game's sound driver interface is the queue plus the four upload sites; everything
below it is IOP protocol, everything above is game logic. The overrides replace exactly
that layer and nothing above it:

| Override | Native mode |
| --- | --- |
| `SoundQueueCmd_1b6d60` | runs the command on the engine directly on the caller's thread (`rg_audio_game_cmd`): no worker thread hop, no SK block, no RPC. hle: the original body (`queue_hle`); compare: original, then the engine, ids checked |
| `SoundBankUploadPart_1ba770` | `rg_audio_game_bank(hd, size, bd, size)`: the engine copies HD and BD from game memory; no IOP heap, no DMA, no G0/0xA chunks, no G1 register. The game's SPU block heap bookkeeping stays (an address is only a budget handle; a part that does not fit gets no BD, as before) |
| `SoundBankLoad_1b9f00` | each SQ sequence: `rg_audio_game_seq(ptr, size)`; slot keeps no IOP address |
| `SoundIopInit_1b7160` | starts the engine (`rg_audio_game_init`); the IOP-side init runs only while the HLE still serves something |
| `SoundRpcInit_1bc840` | no pcm_mixer bind, no IOP staging; stream thread/semaphores/VBlank handler stay (game logic) |
| `SoundRpcCall_1bc5e0` | pcm_mixer calls -> engine PCM ports (`rg_audio_game_pcm`) |
| `SoundStreamSlotSendToIopMaybe_1bd760` | the block built in game memory is mixed into the engine port (`rg_audio_game_pcm_mix`); no DMA, no 0x8090 |
| `AudioDecCreate_1d3210` / `AudioDecDelete_1d31d0` | the AudioDec ring + zero block are engine stream buffers (handles the game's ring arithmetic runs on) |
| `SifDmaSendSync_1d2c20` | (only movie-audio callers) copies into the engine stream buffer |

Switches (`ra_host.c`): `RG_AUDIO=native|hle|compare` (default native),
`RG_AUDIO_PCM=hle`, `RG_AUDIO_MOVIE=hle` (leave that path on the HLE; mixer commands then
also go to the HLE and the runtime adds both outputs), `RG_AUDIO_BREAK=pitch|volume|reverb`
(deliberately wrong engine, for controls), `RG_AUDIO_CMDLOG`, `RG_AUDIO_NATIVE_WAV`.
The mode lives in model state (`ra_game.c`), so a save state carries it: a fixture set
generated in one mode loads in that mode (section 4).

### Engine (`src/native/audio`)

Carried over from the HLE as native code (the sound semantics), with the transport and
hardware model dropped:

| Kept (semantics) | Dropped (emulation) |
| --- | --- |
| SK ids/rules the game checks: first-free entries, track attach rules, -101/-102/-201/-202/-310 | SIF RPC, sdr_driver/pcm_mixer servers, SK block decoding |
| MODHSYN note semantics (`ra_synth.c` = snd_synth.c): HD layer resolution, pitch (Note2Pitch x VAG rate), integer volume chain (prog x split x sample x velocity curve x crossfade x CC7 x note volume x pan gain), pan law, F9/FD per-note messages, bend ranges, allocation and stealing | VOLL/VOLR/PITCH register writes, VMIX masks, KON/KOFF switch words |
| SQ player (`ra_seq.c` = snd_seq.c): VLQ stream, running status, SCEI loop markers, tempo, exact 240 Hz tick accumulator | SKMIDI/MODMIDI port model |
| PS-ADPCM decode per 16-byte block from the bank's BD **in host memory** (loop start/end/repeat, history carried across the loop jump, bit-exact with the HLE: test `adpcm_same`) | 2 MiB sound RAM, SSA/LSAX/NAX address registers, VoiceTrans |
| ADSR integer state machine (psx-spx formula), pitch phase (0x1000 = 48 kHz), cubic B-spline interpolation | volume sweeps (the game writes fixed volumes only), noise, PMON (unused by the synth) |
| Two mix buses (the hardware's two cores as a mix graph): 24 voices each, dry/wet sums by the sample's attribute, a stream input (bus 0: movie, bus 1: PCM), bus 0 chained into bus 1, psx reverb on a per-bus s16 work buffer (LIBSD presets/sizes), master gain with SK's `(x*129)&0x7FFF` | MMIX/core attribute registers, effect work area in sound RAM, EEA/ESA |
| PCM ports: ring of 3 x 1024-frame blocks, 4 ports, double-buffered output, underrun push-ahead (the game's refill pacing depends on it) | AutoDMA, IOP staging |
| Movie stream: 1 KiB [256 L][256 R] units, double buffer, position two units ahead (the game's AudioDec refill arithmetic depends on it) | BlockTrans/BlockTransStatus registers |

Mixing is float (voice x envelope x gain summed per bus); integer arithmetic stays where
it is part of the sound (ADPCM, envelope, the reverb network on its s16 buffer). Buses are
not clipped between stages (the hardware clipped each core); only the final s16 output is.

Banks: HD and BD are reference-counted host blobs; a voice keeps its BD alive, so releasing
a bank while a voice still sounds is safe (on the PS2 the voice played whatever was
uploaded there next).

### Time

The engine renders 48 kHz frames up to a clock the host provides (`ra_set_clock`); every
API call first renders up to the clock, so each command lands at an exact sample and the
output is a pure function of the timed command sequence (deterministic, like the HLE).
The 240 Hz SK tick runs every 200 frames from a tick origin. Runtime glue (`ra_host.c`,
3 calls in `src/runtime/runtime.c`): native clock = virtual clock / 3072 (the same frames
the HLE used); compare mode uses the HLE's own render position and tick origin
(`snd_clock_frame()`), so both engines apply every command on the same frame. In the D9
end state the clock is the game loop's tick; nothing in the engine depends on the PS2
kernel.

### Runtime

`on_vblank`: `snd_sync()` then `rg_audio_runtime_sync()` (engine renders to the same
frame). Host half: after reading the HLE's frames, `rg_audio_runtime_mix()`: native mode
adds the engine's frames (the HLE then only contributes when a path is left on it), compare
mode writes them to `$RG_AUDIO_NATIVE_WAV` frame-aligned with `$RG_AUDIO_WAV`.

### Source volumes (P6, 2026-10-26)

`audio.music_volume`, `audio.effects_volume`, `audio.voice_volume`, `audio.movie_volume`
(percent, Original 100; PLAN.md P6 "Audio"). **Presentation only: the run hash, the audio hash
part of `$RG_HASH_LOG`, `$RG_AUDIO_WAV` and everything the game sees are the same at any
volume.** How:

- The engine's mix (`ra_mix.c` `bus_tick`) is the **model mix**: unchanged, same float
  operations in the same order (SSE, no contraction, PLAN.md D2). The runtime folds it into
  the run hash and writes it to `$RG_AUDIO_WAV`, as before.
- Beside it, while any source gain is not 1, `bus_tick` renders a **presentation mix**
  (`ra_present.c`, `g_rp`) from the same voice samples: each source's part of a bus sum is
  scaled as a delta, `sum + (g - 1) * part`, so with every gain at 1 it is the model's value bit
  for bit. It has its own copy of each bus's reverb (cloned from the model's when it starts), so
  a quieter source also leaves a quieter tail; bus 0 (movie) chains into bus 1 as in the model.
  The result goes to a presentation FIFO that mirrors the model FIFO (same capacity, same drops;
  `ra_output_read2`). The runtime pushes `rg_audio_runtime_present()` to the host, after the
  hash fold (runtime.c host half).
- A gain change ramps over 10 ms. When every gain is back at 1 the second mix stops once its
  reverb copies equal the model's (checked every 100 ms), at the latest after 2 s.
- `ra_present.c` is HOST for save states (ss_map.c row): never saved, never read by the model.
  A load is detected (the model's frame counter / FIFO is not where it left them) and the copies
  are taken again; the PCM parts restart empty (those blocks play at the model level).

Which voice is which source (checked in the code, not guessed):

| Source | Engine path | How it is recognised |
| --- | --- | --- |
| music | notes of SQ sequences (`ra_seq.c` -> `ra_synth_note_on(..., seq = 1)`) | `v->seq` |
| music | PCM ports playing `wav/BGM_MWV_NEW/BG_%03d.mwv` (`BgmPlayTrack_2075e0`, stream channel 0) and `snd2/mwv/%03d.mwv` (`StreamPlayMwv_207340`: the 800+ fanfares after a battle, weapon combine, Revelation board; also script `SpPlay` numbers) | stream path |
| effects | the game's key ons (`SoundQueueCmd` 0x20 -> `ra_key_on`, `seq = 0`): SE banks of the scene / character / system slots | `!v->seq` |
| effects | PCM ports playing any other path (scripted `StreamChanStart` / `SpPlay` strings) | stream path |
| voice | PCM ports playing `wav/<lang>/EV%02d-%04d/...mwv` (`EventVoicePlay_24efd0`, event dialogue) and `wav/<lang>/LiveTalk/...mwv` (`LiveTalkVoicePlay_2070f0`) | stream path |
| movie | the movie stream on bus 0 (`ra_movie_*`, AudioDec ring) | bus 0 stream input |

The stream path: the game's 4 PCM ports are the stream slots of the stream manager's 4
channels (`GetStreamMgr_207ea0`, 224 bytes each; device path at +0, slot id at +0x80:
`StreamChanGetName_1d72b0` / `StreamChanGetSlotId_1d72c0`). The override
`SoundStreamSlotSendToIopMaybe_1bd760` reads (only reads) the channel whose slot is the port
before each block and calls `rg_audio_game_pcm_source(port, path)`; `ra_pcm_source_of` maps
"BGM" / "SND2/MWV" -> music, "LIVETALK" / an "/EVnn-" folder -> voice, the rest -> effects.
Each port's block is added unclamped into a per-source ring parallel to the model ring
(`ra_present_pcm_*`), so mixed ports separate. `$RG_AUDIO_SRCLOG=<path>`: one row per path
change (frame, port, source, path) -- the source census `tools/native/audio_volume_gate.py`
prints.

Not separable: a character's battle shouts or grunts that the game plays as SE notes from a
bank count as effects (the engine sees banks and programs, no category); only streamed lines
are "voice". The HLE oracle paths (`RG_IOP=hle` builds, `RG_AUDIO=hle|compare`) push the model
mix (no source volumes there).

Gates: ctest `audio.source_gain` (below); `tools/native/audio_volume_gate.py` (the golden
route at the Original preset and at three non-Original volume mixes: run hash and audio part
identical).

## 3. Verification

### Tests (`ctest -L audio`, `build/naudio-i686`)

`native-audio-tests <name>`; data tests read `RG_DATA` (77 = skipped without it). The
oracle is the HLE driven through its SIF RPC path by `snd_eesim` (the game's request
sequence); the native side gets the same requests through `rg_audio_game_*` (the thread
command ids). Metric (`audio_metric`): SNR over the whole render, worst 50 ms window SNR
(windows above -60 dBFS), best lag in +-8 frames. Pass: SNR >= 40 dB, worst window >= 20
dB, lag 0.

| Test | Result (2026-10-17) |
| --- | --- |
| `adpcm_same` | 20,000 random blocks + the note2pitch grid bit-identical to the HLE |
| `ids` | entries, tracks, SE ids, error codes (SK rules) |
| `pcm` | 4-port PCM: free-block replies equal every call, first block heard at frame 3072, **SNR 75.2 dB, peak diff 2 LSB** |
| `se_compare` | sy_000 SEs (title cursor, held note with volume/pan/bend changes, overlapping notes): **SNR 61.6 dB**, worst window 25.0 dB, lag 0 |
| `seq_compare` | bg_000 sequence 20 s with a volume change and stop/replay: 203 notes each, **SNR 47.7 dB**, worst window 36.2 dB |
| `source_gain` (2026-10-26) | one scene with every source (bg_000 sequence, two held sy_000 SEs, a jingle and an event-voice PCM port, a looping movie stream, reverb on) under 4 gain settings: the model frames bit-identical in all; at unity presentation = model and no second mix; every gain 0 (reverb off: with reverb the 10 ms ramp leaves a tail in the copy, as it should): presentation peak 0-1 LSB after the ramp; music 0.2 for 0.5 s then 1: identical before, different during, the second mix stops and the presentation is the model again; the path classifier on the game's formats |
| `*_control` (WILL_FAIL) | engine one semitone sharp (se/seq: SNR -2.8 / -3.0 dB, lag -6/-8) or 6 dB quiet (pcm: 6.0 dB): each fails, as required |

### Compare mode on the golden route

```
set RG_AUDIO=compare& set RG_AUDIO_WAV=out\naudio\cmp4\hle.wav& set RG_AUDIO_NATIVE_WAV=out\naudio\cmp4\native.wav
set RG_AUDIO_CMDLOG=out\naudio\cmp4\cmdlog.tsv
rg-game.exe --headless --fields 9000 --saves <fresh> --input tools/trace/goldens/newgame_battle.input.txt
python tools/native/audio_compare.py out/naudio/cmp4/hle.wav out/naudio/cmp4/native.wav --align start --table
```

Power-on to field 9,000 (`out/naudio/cmp4`): 150 s, 116 key ons, 84 sequence notes, 16
banks, 3 sequences, 1,960 PCM blocks, two movies: **SNR 56.6 dB, median 50 ms window
55.8 dB, 1st percentile 26.6 dB, worst 19.5 dB (a quiet -44 dBFS passage at 122 s), peak
|diff| 10 LSB, lag 0, levels equal to 0.1 dB, 0 id mismatches.**

### Fixtures (title / field / battle)

`python tools/native/audio_fixtures.py --nat-exe out/naudio/fx-nat/rg-game.exe --cmp-exe
out/naudio/fx-cmp/rg-game.exe` (reusable; the docstring has the method). Two fixture sets
of the same build (exe `1836487c94feb8ea` regenerated with `RG_AUDIO=native`, a
byte-appended copy `fe8dbb64f96e3553` with `RG_AUDIO=compare`: the audio mode is saved
in the state, so a set loads in the mode it was made in). Per milestone: the compare run's
HLE vs engine (sample metric), the native run vs that HLE output (envelope metric:
native mode applies commands on the caller's frame and ticks from its own origin, so
sequenced notes may move by up to one 240 Hz tick), and the native run twice
(determinism). Results in `out/naudio/fx/<milestone>/`.

| Milestone (+fields) | compare: HLE vs engine | native vs HLE (envelope) | native rerun |
| --- | --- | --- | --- |
| title +1200 (menu, attract movie, NEW GAME) | SNR 56.9 dB, worst window 25.0, p1 34.5, peak diff 7, lag 0 | level p95 0.16 dB, spectrum p5 0.9999 | identical (run hash `214bf7aff4024526`, WAV equal) |
| field +1500 (first field: streams, SEs, BGM) | SNR 57.4 dB, worst 41.5, p1 44.6, peak diff 10 | level p95 0.28 dB, spectrum p5 0.9954 | identical (`d68bc95415ba86be`) |
| battle (+~100 of 900) | SNR 57.1 dB, peak diff 16 (10 key ons, pan/volume/bend) | level p95 0.16 dB, spectrum 0.9989 | identical (`583fffa275dc46c4`) |

**Battle caveat (not audio):** every build of the current tree crashes about 100 fields
after the battle milestone (access violation reading 0x8 in `sceVu0CopyVector` from
`GuardWaveEffectStart_2d5ad0` <- `BattleApplyHit_2ef930`), in both audio modes and also
in another lane's exe without the native audio engine (set `14304f903b1a1f5d`, 22:52);
the 22:19 fixtures exe (`b6c31fc1b80fa62a`) runs 300 fields clean. So the battle numbers
cover the ~1.6 s before that crash.

Native mode from power-on to field 9,000 (`out/naudio/nat1`, 33 s wall): vs the compare
run's HLE output level p95 0.16 dB, spectrum p5 0.9978; the control (`RG_AUDIO_BREAK=pitch`,
`out/naudio/nat1brk`) fails it (spectrum p5 0.80, level p95 2.6 dB).

### Pop scan (2026-10-22)

`tools/native/audio_popscan.py WAV [--alog TSV]`: clicks (|second difference| > 12x its
local RMS and > 1500) and zero-gaps inside audio (hard when a neighbour sample is >= 64,
soft when a sound decayed into it). Uses `<wav>.fields.tsv` (from `RG_AUDIO_WAV`) for
fields, `<wav>.events.tsv` (from `RG_AUDIO_HOST_WAV`, HOST.md "Audio") to name the host
splice next to each event, and `--alog` (`RG_AUDIO_LOG`) for starves/pads/drops per field.
Capture: `RG_AUDIO_WAV=..\e.wav RG_AUDIO_HOST_WAV=..\h.wav RG_AUDIO_LOG=...tsv python
tools/fixtures/run_from.py --boot-save save2 --run 3000 --exe build/play-i686/rg-game.exe
--windowed` (scratch in `out/audiocheck/`).

Finding (resume item 12): the engine output (`RG_AUDIO_WAV`) had 0 clicks and 0 hard gaps
in every run (title, CONTINUE, town); all pops were host splices: device starves after a
long field, the regulator's silence pads after a starve or pacer re-anchor (frequent when
the host runs slower than 59.94 Hz: `R.pace` resyncs, now included in the alog `resyncs`
column) and frames dropped after a catch-up. Loaded windowed run, de-click off: 193 clicks
+ 108 hard gaps, all at splices; on (same load, starves/pads/drops present): 0 clicks, 0
hard gaps. Pads and starves are still audible as short dropouts (now soft); fewer of them
needs a faster field, not the audio path.

## 4. Next steps / resume

1. Build: `powershell -ExecutionPolicy Bypass -File tools
ativeudio_build.ps1`
   (`-Reconfigure` after adding an override; `-Targets a,b`).
2. Tests: `ctest -L audio -j2` in `build
audio-i686`.
3. Compare run: the commands in section 3; fixtures: `tools/native/audio_fixtures.py`
   after regenerating both sets (`RG_AUDIO=native|compare python tools/fixtures/regen.py --exe ...`,
   ~7 min each, one at a time).
4. Open items: the runtime still renders the HLE (silence) every field in native mode
   (drop `snd_sync`/`snd_output_read` when `rg_audio_hle_needed()` is 0); the per-voice
   float path vs the HLE's integer truncation makes quiet reverb tails differ by ~20 dB
   SNR in the worst 50 ms windows (-44 dBFS passages; the psx reverb network is sensitive
   to input rounding); MODHSYN features the HLE never modelled (LFOs, portamento, drum
   mode, user velocity tables) are equally absent here (SOUND.md "Open items"); volume
   sweeps/noise/PMON are not in the engine (the game's banks and driver do not use them).

## 5. Findings

- **HLE bug fixed (oracle): `sceSdSetEffectAttr` layout.** The game builds
  `{int core, int mode, s16 depth L, s16 depth R, int delay, int feedback}`
  (`SoundThreadCmdSetReverbMode_1b66b0` stores the mode as a word at +4, depths as
  halfwords at +8/+10), the ps2sdk libsd layout. The HLE read `{u16 core, u16 mode, ...}`,
  so every in-game reverb mode set (`SoundSpuInit`'s STUDIO_C on core 0, the per-bank
  `.vol` settings through `SoundBankVolParse_1b7200`) arrived as mode 0: **the bring-up
  build never had reverb** except the SK 0x83 init path. Found by compare mode: the native
  engine (which takes the mode from the command) differed from the HLE only in its reverb
  (fields 2,100-3,100: 7 dB SNR; with `RG_AUDIO_BREAK=reverb` 57 dB). Fixed in
  `snd_srv.c` (0x8130 parse and the 0x8140 reply) and `snd_eesim.c`; `ctest -L sound`
  still passes.
- The key on's reply is not used by the game (`SoundSendKeyOn_1b80c0` drops it); the HLE
  path returns 1, the engine the id. Compare mode does not check it.

- PCM "underruns" in the engine's stats (and the HLE's) count idle ports being pushed one
  block ahead each block (4 ports, mostly unused): not audible dropouts.

## 6. What remains of SIF / IOP / SPU for sound

**Update 2026-10-18 ([NATIVE-IOP.md](NATIVE-IOP.md)):** with `RG_IOP=native` (the default
when every sound path is native) the runtime no longer installs the sound HLE, no longer
calls `snd_sync` per VBlank nor `snd_output_read` per field: it reads the engine's frames
with `rg_audio_runtime_read`. The paragraph below describes `RG_IOP=hle`.

Native mode (default): no sound RPC (0x80000701, 0x123456), no SIF DMA, no IOP heap, no
SPU2 model in the sound path. Still linked in the exe: `src/ps2/iop/sound` + `src/ps2/spu`
(the HLE, behind `RG_AUDIO=hle|compare` and the `RG_AUDIO_PCM/MOVIE=hle` switches), and
the runtime still calls `snd_install`/`snd_sync`/`snd_output_read` every field (the HLE
renders silence in native mode). The IOP boot itself (LOADFILE of the sound IRX modules,
`sceSifInitRpc`, the sound placeholder servers) is the IOP/SIF lane's. To remove: drop
the HLE calls from the runtime when `rg_audio_hle_needed()` is 0, then move the HLE to
tests/tools only (the tests already link it directly).

## 7. Files touched outside the lane

Small wiring edits in shared files (re-read before editing; others edit them too):
`CMakeLists.txt` (2 `add_subdirectory` lines), `src/runtime/CMakeLists.txt`
(`rg_native_audio` link + `RG_HAVE_NATIVE_AUDIO`), `src/runtime/runtime.c` (include + 3
clock helpers, and 3 calls: `rg_audio_runtime_init` at step 7, `rg_audio_runtime_sync`
in `on_vblank`, `rg_audio_runtime_mix` in the host half), `src/savestate/ss_map.c` (one
policy row: `ra_host.c.obj` is HOST), `src/ps2/iop/sound/snd.h`/`snd_srv.c`
(`snd_clock_frame()`, the effect-attr layout fix), `snd_eesim.c` (same layout),
`docs/SOUND.md` (pointer + layout note). P6 source volumes (2026-10-26): `runtime.c`
(`audio_mix_update` + the push of `rg_audio_runtime_present`), `ss_map.c` (`ra_present.c.obj`
is HOST), `rg_settings_core.c` (the four volume rows lose PH), the read-only stream tag in
`SoundStreamSlotSendToIopMaybe_1bd760.cpp`. New overrides in `overrides/src/main/movie/`
(`AudioDecCreate`, `AudioDecDelete`) and `overrides/src/main/sys/SifDmaSendSync_1d2c20.c`
belong to this lane (movie audio transport only; the movie lane's overrides are untouched).
