# Sound (SPU2 engine + IOP sound HLE)

**2026-10-17:** the shipping path is now the native audio engine ([NATIVE-AUDIO.md](NATIVE-AUDIO.md),
`RG_AUDIO=native`, default). Everything below is the bring-up HLE, kept as the oracle
(`RG_AUDIO=hle|compare`).

PLAN.md D4 (sound at the RPC boundary) and P4 (audio). The protocol the game speaks is
in [SOUND-PROTOCOL.md](SOUND-PROTOCOL.md); this file describes what the port does with it,
how accurate that is, and how to check it. Everything here is CC0 and written from
scratch: public SPU/SPU2 documentation (psx-spx for ADPCM, envelope and reverb formulas;
ps2sdk's AFL headers for libsd entry numbers), our own disassembly of the retail IRX
files in `data/MODULES/`, and the game's own data. No PCSX2 or other GPL code or text.

| Path | What |
| --- | --- |
| `src/ps2/spu/spu2.[ch]` | SPU2 engine: 2 MiB sound RAM, 2 cores x 24 voices, ADPCM, pitch, interpolation, ADSR, volume sweeps, noise, PMON, MMIX routing, AutoDMA input, reverb, `spu2_render()` |
| `src/ps2/iop/sound/snd_srv.c` | servers: sdr_driver `0x80000701` (libsd calls, movie audio, `0x90F0` SK dispatch: G0 SKSOUND, G1 SKHSYNTH, G2 SKMIDI, G3 SKMSIN) and pcm_mixer `0x123456`; clock, render loop, output FIFO |
| `src/ps2/iop/sound/snd_synth.c` | the hardware synth (SKHSYNTH/MODHSYN): bank slots, MIDI channel state, note -> HD layers -> voices, per-id volume/pan/bend, voice allocation |
| `src/ps2/iop/sound/snd_seq.c` | SKMIDI/MODMIDI sequence player for SCEI SQ data |
| `src/ps2/iop/sound/snd_hd.[ch]` | SCEI HD bank parser |
| `src/ps2/iop/sound/snd_pack.[ch]`, `snd_eesim.[ch]` | tools/tests only: HD6/DAT archive + `.snd` pack reader, and an EE-driver stand-in that sends the game's requests |
| `src/ps2/iop/sound/rg_sound_play.c` | `rg-sound-play`: headless bank/SE/sequence -> WAV |
| `tests/sound/` | CTest suite, label `sound` |

CMake targets: `rg_ps2_spu`, `rg_ps2_sound` (links `rg_ps2_sif`, `rg_ps2_iop`),
`rg_snd_tools`, `rg-sound-play`, `rg-sound-tests`.

## Wiring

```c
rg_sif_boot(&cfg);          /* registers the placeholder sound servers */
snd_install(NULL);          /* re-registers 0x80000701 and 0x123456 with the real HLE */
/* per field, host side: */
snd_sync();
n = snd_output_read(buf, max);
rg_host_audio_push(h, buf, n);
```

`src/runtime` does exactly this: `snd_install` from the IOP post-install hook (the
end of `iop_hle_install`), `snd_sync` from its VBLANK_START observer, and the drain +
push in the host half of every field (RUNTIME.md "One field").

`snd_install` must run after `rg_sif_boot` / `iop_hle_install` (both call
`sif_server_register`, the later one wins). The engine never touches the host: the host
pulls.

## Time

- 1 output frame = 3072 bus cycles (147.456 MHz / 48 kHz, exact), so one NTSC field is
  800.8 frames; `snd_frames_for_field(k)` gives the integer split.
- The clock is `sif_now()` (the kernel's virtual clock once `src/sce/sif` installs its
  hooks). Every sound RPC first renders up to the current clock (`snd_sync`), so key ons,
  sequencer ticks and the movie read position land at exact sample times and the output
  is a pure function of the virtual-time call sequence: deterministic.
- Rendered audio goes to an output FIFO (2 s default); if the host does not drain it,
  the oldest frames are dropped (`snd_output_dropped`).
- Without a clock (`snd_set_clock(NULL)`), servers never render and tools/tests pull with
  `snd_render(buf, frames)`.
- SKSOUND ticks at 240 Hz (its `tickresolution` default; the game passes no option), so
  the SK tick runs every 200 frames inside the render loop. SKMIDI sequences advance on it.
- **Caveat:** MSIN key ons/offs and volume/pan/bend updates are applied at the RPC's
  sample time. Retail queues them in MODMSIN and applies them on the next 240 Hz tick, so
  retail can be up to 4.2 ms later.

## SPU2 engine (`spu2.c`)

### Voices

- **ADPCM:** 16-byte blocks, shift (0..12; 13..15 act as 9), filters 0..4
  (`{0,0},{60,0},{115,-52},{98,-55},{122,-60}` / 64, filters 5..15 clamped to 4),
  flags bit 0 loop end, bit 1 repeat, bit 2 loop start. At the end of an end-flagged block
  ENDX is set and NAX jumps to LSAX; without repeat the voice is muted (envelope 0, off).
  A loop-start block sets LSAX unless software wrote LSAX since the key on.
- **Pitch:** 14-bit register, 0x1000 = 48 kHz, clamped to 0x3FFF; a 12-bit phase counter
  fetches `floor(N * pitch / 4096)` samples after N frames. PMON (voice 1..23) scales the
  step by the previous voice's output.
- **Interpolation (choice):** 4-tap **cubic B-spline** (`(1-t)^3/6, (3t^3-6t^2+4)/6,
  (-3t^3+3t^2+3t+1)/6, t^3/6`, 256 phases, exact integer Q15 weights). The hardware uses a
  4-tap Gaussian ROM table; the B-spline is the closed-form curve of the same family
  (weights 1/6, 4/6, 1/6 at phase 0 vs roughly 0.16/0.69/0.16), so the high-frequency
  roll-off is similar, but samples differ by small amounts. Linear and sample-and-hold
  are selectable (`spu2_set_interp`, `snd_config.interp`). Dropping the real table in
  later only changes `g_bspline`.
- **ADSR:** psx-spx envelope formula, per sample: rate = shift<<2|step,
  `cycles = 1 << max(0, shift-11)`, `step = (7-s or -8+s) << max(0, 11-shift)`,
  exponential increase above 0x6000 waits 4x, exponential decrease scales the step by
  `level/0x8000`; the generator waits `cycles` samples and then steps (saturating
  0..0x7FFF). Attack -> decay at 0x7FFF; decay runs while `(level >> 11) > SL` (checked
  before the step, so SL 15 sustains at full level); sustain uses ADSR2's mode/direction/
  rate; release runs to 0 and turns the voice off. Rate 0x7F effectively never steps.
- **Volumes:** fixed (`bit 15 = 0`: value = bits 0..14 as signed, x2) or swept
  (`bit 15 = 1`: bit 14 exponential, 13 decrease, 12 negative phase, bits 0..6 rate, same
  envelope generator). Applies to voice VOLL/VOLR and core MVOLL/MVOLR. EVOL, AVOL
  (external input) and BVOL (sound data / AutoDMA input) are plain s16.
- **Noise:** psx-spx LFSR with the core's 6-bit noise clock; voices with NON output it.
- **KON** resets the decoder, NAX = SSA, envelope 0 in attack, clears ENDX. The
  hardware's few-sample key-on latency is not modelled.

### Cores and mixing

Per core and sample: voice outputs `out * env >> 15`, then `* VOLX >> 15`, are summed
into dry L/R (VMIXL/VMIXR) and wet L/R (VMIXEL/VMIXER). MMIX routes three sources
(ps2sdk bit names): `MSND*` voices, `SIN*` the AutoDMA input (`* BVOL`), `MIN*` the
external input (`* AVOL`; for core 1 that is core 0's output). Wet goes into the reverb;
`dry + reverb * EVOL` is clipped and multiplied by MVOL; core 1's output is the DAC.
Mute (core attr 6) zeroes the core output.

**Reset state:** AVOL (core 0 -> core 1) = 0x7FFF on both cores. The game never sets it.
Confirmed for core 1 from LIBSD.IRX: sceSdInit writes core 1 AVOLL/R (0x1F900790/2) =
0x7FFF and core 0 AVOL, BVOL on both cores = 0 (`0x1850..0x1870`). Core 0's AVOL is not used
by the mix here.

### Reverb

The psx-spx reverb (same-side and cross reflections with IIR, four combs, two all-pass
filters) on the core's work area, at half rate (24 kHz: wet input averaged over 2
samples, output held for 2). Presets per libsd mode come from the retail
`LIBSD.IRX` data (0x4B70: 10 records of 4 + 32 halfwords, psx register order; 0x4B48:
work-area sizes in 8-byte units, e.g. HALL 0x15BC -> 0xADE0 bytes, STUDIO_C 0xDFC ->
0x6FE0 bytes, which matches the game's 0x7000-byte reservations). Address registers are
in 8-byte units (x4 halfwords). The work area is `[EEA - size + 1, EEA]`; EEA keeps only
address bits 17..20 (`addr | 0x1FFFF`), which is why the game aligns its areas to 0x20000.
`mode | 0x100` clears the work area.

Caveats: no input/output FIR resampling (the hardware filters around its half-rate
step); ECHO/DELAY `delay`/`feedback` are stored but not applied to the registers; the
exact rounding of each multiply is not hardware-verified.

## IOP HLE (`snd_srv.c`)

### sdr_driver 0x80000701

All of SOUND-PROTOCOL.md section 1. `0x8010/0x8020` SetParam/GetParam, `0x8030/0x8040`
switches (KON/KOFF/VMIX/...), `0x8050/0x8060` addresses, `0x8070/0x8080` core attributes,
`0x8090/0x80A0` Note2Pitch/Pitch2Note, `0x8130` SetEffectAttr (`{int core, int mode,
s16 depthL, s16 depthR, int delay, int feedback}`, the layout the game builds; until 2026-10-17
the HLE read `{u16 core, u16 mode, ...}` and every in-game reverb mode arrived as 0:
NATIVE-AUDIO.md "Findings"; depth -> EVOL), `0x8140`
GetEffectAttr, `0x8150/0x8190` clear the work area, `0x8160/0x8170` store the handler
(no callback is ever delivered: section 4), `0xE620/0xE630/0x8F10` no-ops,
`0x9000..0x90E0` reply 0, `0x90F0` the SK dispatcher (module = block byte 3 & 0x7F,
unregistered index -> -310). `0x8000` sceSdInit resets registers and voices but keeps
sound RAM.

**Movie audio (core 0 AutoDMA):** `0x80E0` BlockTrans `WRITE_FROM|LOOP` starts playing
the IOP ring at `start` as 1 KiB units of `[256 L][256 R]` s16. Like the hardware, the core
plays from a two-half input buffer: the start copies the start unit and the next one into
it, and each time a half has been played (256 frames at 48 kHz on the virtual clock) it
takes the next unit from IOP RAM. `0x8100` returns the DMA position,
`(half << 24) | (ringBase + offset of the next unit to transfer)`, half = that offset >=
size/2, so it runs two units ahead of the unit being played (`snd_movie_position` still
reports the unit being played). `0x80E0` STOP returns the same form and freezes;
`0x80D0` VoiceTrans copies IOP <-> SPU RAM (the zero-buffer clear at SPU 0x4000) and
returns the size. Why the buffer matters: after its one-ring preset the EE's
AudioDecSendToIop refills `(position - write - 1 KiB) mod size` bytes; with the position
of the unit being played (0 right after the start) that is 23 KiB, which overwrote the
preset before it was heard. Every movie lost its first 6144 frames (128 ms) and the
rest played 128 ms early (fixed 2026-10-12, test `movie_refill`; "Validation" below).

### SK modules

| Module | Implemented |
| --- | --- |
| G0 SKSOUND | S0/S1 -> 0; S2 ctl 0x80 core 1 MVOL `(x*129) & 0x7FFF` (wrap reproduced: 0x3FFF -> 0x3F7F), 0x81 mute, 0x82 effect enable, 0x83 SetEffectAttr both cores, 0x84 EVOL `x*0x7FFF/127`, 0x8F SPDIF (stored), 1/2 timer flag; S3 tick counter; S0xA VoiceTrans into sound RAM before replying |
| G1 SKHSYNTH | 16 bank entries (HD copied from IOP RAM when the entry is filled and parsed; BD = SPU address/size); attach (track -1 = first track with status&3 == 0, slot < 16) sets status bit 1; detach cuts the track's voices; S2 0x1E all notes off (release), 0x1F all sound off (cut), 0x71 mono, 0x70 stored; S3 0x72 counts voices whose SSA is in the entry's BD and ENVX != 0 |
| G2 SKMIDI | 16 data entries (SQ copied at register), 5 MIDI ports; attach sets status bit 0, input type 0; S2 play (rewind if ended, SelectMidi(v), start), stop (+rewind, release), pause, 0x30 volume (0x80 = unity), 0x31 absolute tempo (BPM), 0x32 relative tempo (0x100 = 1.0, **L**); S3 state |
| G3 SKMSIN | 16 entries; attach input type 2; S2 0x10/0x11 key on (`CC0 = bank slot`, program, `F9 01 ch x` = the note's pan, `FD 10 ch note id vel`), 0x12/0x13 key off (FD 10 with velocity 0), 0x40 pan, 0x41 14-bit bend, 0x42 volume per (ch, note, id); S3 0x11 voice state |

Error codes follow section 2 (-101/-102/-201/-202/-310/-402). Track status, input
types and the -1 "first free" rules are the ones the IRX code uses.

### pcm_mixer 0x123456

Section 3: `0x8000 (core, blockBytes, nBlocks)` allocates the ring and a 2-half DMA
buffer, wpos = 1 / rpos = 0; `0x8090` mixes `src * vol >> 15` (saturating, L volume on
the even 256-sample halves of each 512-sample pair, R on the odd) into block wpos and
returns 1, or 0 when `(wpos - rpos) mod n == 0`; `0x80A0` returns that distance;
`0x8100` starts core AutoDMA from the DMA buffer with the pending volume (BVOL);
`0x8400` stops (1 if not running); `0x10` frees; `0x200` pending volume (applied at the
next half interrupt), `0x300` immediate. Each time a half finishes playing (every
`blockBytes/4` frames), that half is refilled from ring block rpos (or silence), the ring
block is cleared, rpos advances, and any port whose wpos equals the new rpos is pushed
one block ahead (underrun skip). With `(1, 0x1000, 3)` a block written to an empty ring
plays 3072 frames after output start (tested to the frame). Default pending volume
before the first `0x200`: 0x7FFF both sides (**L**).

## HD banks (`snd_hd.c`)

The game's banks are `.snd` packs (`snd2\...` in DATA0_0.DAT) holding `NAME.hd`,
`NAME.bd` (raw ADPCM for sound RAM), `NAME_nnn.sq` (BGM packs), `.cfg`, `.vol` and SMF
`.mid` files the EE sequencer parses itself. HD = `IECS` chunks with reversed names:

| Chunk | Layout |
| --- | --- |
| Vers @0, Head @Vers.size | Head +0xC HD size, +0x10 BD size, +0x14 Prog, +0x18 Sset, +0x1C Smpl, +0x20 Vagi offsets (0xFFFFFFFF = absent) |
| Prog / Sset / Smpl / Vagi | `{IECS, name, u32 size, u32 max index (0xFFFFFFFF = empty), u32 offset[max+1] from the chunk}` |
| Prog record (0x24 + splits) | u32 split offset, u8 nsplit, u8 split size (0x14), u8 volume, u8 pan, s8 transpose, s8 detune, ..., LFO fields |
| split (0x14) | u16 sset, u8 key lo, u8 key crossfade, u8 key hi, u8 number, u16 bend lo, u16 bend hi, key-follow pitch/amp/pan + centres, u8 volume, u8 pan, s8 transpose, s8 detune |
| Sset | u8 velocity curve, u8 vel lo, u8 vel hi, u8 count, u16 sample[count] |
| Smpl (0x2A) | u16 vag, vel lo/xfade/hi, vel-follow pitch/amp fields, +0x0B base note, +0x0C detune, +0x0D pan, +0x0E group, +0x0F priority, +0x10 volume, +0x12 ADSR1, +0x14 ADSR2, key-follow AR/DR/SR/RR/SL, LFO, +0x28 LFO attr, +0x29 SPU attr |
| Vagi (8) | u32 BD offset, u16 sample rate, u8 loop, u8 pad |

All 800 non-empty HDs in DATA0_0 parse (`sound.hd_real`); empty banks (no samples) exist
and are accepted.

## Synth (`snd_synth.c`)

From MODHSYN.IRX code (`out/sound-disasm/MODHSYN.s`; offsets are its sub_ names and its
voice/channel record fields). Messages reach it as MIDI bytes (sub_1640 parses the input
buffers each 240 Hz tick: channel messages -> sub_1350, `F9` (4 data bytes) and `FD` (6)
-> sub_148c); key ons are queued per core and started in the same tick (sub_3dec ->
sub_45b0 writes VOLL/VOLR, PITCH, SSA, ADSR, VMIX, then KON).

- **Layers** (sub_6cac): splits with `key lo & 0x7F <= note <= key hi & 0x7F` (bit 7 is the
  crossfade flag), the split's Sset if `vel lo <= vel <= vel hi` and it has samples, and
  each Sset sample with `vel lo & 0x7F <= vel <= vel hi & 0x7F`.
- **Pitch** (sub_4a48) = `Note2Pitch(sample base note, 0, note + prog/split transpose,
  prog/sample/split detune + bend) * (rate << 16) * 0x057619F1 >> 42 >> 16` (Q16 rate /
  48000, 65536 at 48 kHz). The bend is one voice field (+52) with **last writer wins**: key
  on (the channel's `F9 02` value if one is pending, else the channel bend), channel `E0`
  when the channel bend changes (all its voices), per-id `FD 02` (SKMSIN 0x41). Value
  (sub_4c50) = `(bend14 - 0x2000) * range / 8192` (truncated toward 0) in 1/128 semitone,
  range = split bend hi (bend >= 0) or lo; the game's banks have 256 = 2 semitones.
- **Volume** (sub_41dc, sub_4e80, sub_4ca4), all integer:
  `v22 = prog.vol * split.vol * sample.vol * curve(vel) / 16384 * crossfade >> 16`;
  `v24 = vol43 * vol84 * v22 >> 14`; `VOLL/R = min(gain * v24 >> 7, 0x3FFF)` with the
  track volume (256 * 127/127 >> 8) = 1. `vol43` = CC7, `vol84` = the note volume, both
  as `(v << 7) / 127` (127 -> 128). The note volume starts as the channel expression
  (CC11), or a pending `F9 00` raw value, and is replaced by per-id `FD 00` (SKMSIN 0x42)
  and by CC11 when CC11 changes (last writer wins). Velocity curve (sub_98a4, Sset byte 0
  low nibble): 0 v, 1 128-v, 2 sq(v), 3 128-sq(v), 4 128-sq(128-v), 5 sq(128-v), with
  `sq(v) = max(1, v*v/127)`; 6..9 repeat 0..3. Crossfade (sub_52f4): below the sample's
  velocity crossfade point with `vel lo` bit 7 set, `(vel - lo + 1) << 16 / (xf - lo + 1)`,
  at or above it with `vel hi` bit 7, `(hi + 1 - vel) << 16 / (hi + 1 - xf)`; the same for
  the note against the split's key range, multiplied in.
- **Pan** (sub_5074, sub_5158): base = `|prog.pan| - 128 + |split.pan| + |sample.pan| +
  key follow` clamped to 0..127, key follow = `((note - split kf centre) * split kf +
  (note - prog kf centre) * prog kf) / 12` (prog record +0x0A/+0x0B, split +0x0E/+0x0F).
  The note's pan offset is `x - 64` (>= -63) of the key on's `F9 01 x` (SKMSIN sends the
  key on's last argument there; the EE passes the SE pan), else CC10 - 64; then per-id
  `FD 01` and CC10 changes. `p = offset + base - 64`; both gains 128, and the far side's
  `(63 - |p|) * 128 / 63` (0 at |p| >= 63). Mono output (SKHSYNTH 0x71) = both 128.
- Per-id messages address voices by (channel, note, id); id 127 = any id.
- sample SPU attribute: bit 0/1 dry L/R, bit 2/3 wet L/R, bits 4-5 core
  (0x10 core 0, 0x20 core 1, else the core with more free voices) (sub_727c).
- Note2Pitch: 12 semitone and 128 fine ratios (2^(k/12), 2^(k/1536), Q16, computed
  offline) and octave shifts; may differ from libsd's ROM table by 1 LSB.

Not modelled: LFOs (pitch/amp/pan, incl. their key/velocity follow depths), portamento,
the surround pan mode (prog byte +0x0C bit 0), the alternate drum mode (track flag byte
+3 = 1), user velocity tables (Sset curve high nibble), the SKMIDI track volume path (the
port multiplies sequence voices by `seq_vol / 128`, **L**), voice stealing (the port takes
the quietest released voice, else the lowest-priority oldest), and the one-tick delay of
MSIN messages (Time, above).

## Sequences (`snd_seq.c`)

SQ = `IECS Vers, Sequ, Midi`; Midi block `{u32 stream offset, u16 ppq (480 in all game
files)}`; stream = VLQ delta then `{event, [delta]}`; 8n note off has one data byte;
running status; **if an event's last data byte has bit 7 set, its delta is omitted
(0) and the value is `byte & 0x7F`**; metas (`FF 51` tempo, `FF 2F` end) are followed by a
delta. Loops: NRPN MSB (CC 0x63) 0 + data entry (CC 6) marks the loop start; NRPN MSB 1
+ data entry v jumps back (v = 0 forever, else v times). All 92 `.sq` files on the disc
parse start to end with this grammar. Tick rate = `ppq * 1e6 * speed / (240 * tempo *
256)` MIDI ticks per SK tick, exact rational accumulator. CC 0 bank slot, 7 volume,
10 pan, 11 expression, 64 sustain, 120/121/123, program, pitch bend are applied; An/Dn are
read and ignored.

## Tests (`ctest -L sound`)

`rg-sound-tests <name>`. Tests needing the game data read `RG_DATA` (CMake points it at
`<repo>/data` when the archives are there) and exit 77 = skipped otherwise.

| Test | Checks |
| --- | --- |
| `adpcm` | hand-computed blocks: filter 0 nibbles, shift 0 extremes, filter 1 chain from history 64 (60, 56, 53), filter 2 saturation, shift 13 -> 9, flags |
| `adsr` | sample by sample: linear attack vs `floor(n/4)*6`, exponential attack vs the closed form with the 0x6000 slow-down, exponential decay vs the formula and the SL switch, sustain rate 0x7F hold, linear release ramp and the exact sample the voice turns off |
| `pitch` | Note2Pitch values (0x1000, x2, /2, +7, -1, +64 fine, clamp) and NAX/fetch position after 1000 frames at 0x800/0x1000/0x2000 |
| `loop` | loop start from the flag, ENDX and jump at the end block, repeat keeps the voice, KON clears ENDX, one-shot mutes after its end block, software LSAX wins |
| `hd_synthetic` | parser on a hand-built bank incl. absent program, velocity window, bad magic |
| `hd_real` (data) | sy_000.hd counts and field values, every program's layers inside the BD, all 800 banks in DATA0_0 parse |
| `se_keyon` | full RPC path on a synthetic bank: SK master-volume wrap, key on -> voice on core 0 at the BD with pitch 0x2000 for +12, audible, per-id volume 0 -> VOLL 0, key off -> release -> silence, -102 / -310 errors |
| `se_keyon_real` (data) | sy_000 bank uploaded through G0/0xA chunks, G1/G3 setup, key on renders non-silent audio, two runs hash-identical |
| `midi` | synthetic SQ through G2: note on at the first SK tick, note off exactly at frame 24000 (480 ticks at 120 BPM), end at FF 2F, replay rewinds, stop |
| `pcm_ring` | free distance 1/2/0, refused when full, bad port; mixed blocks appear in the core 1 output at frames 3072 and 4096, sample-exact through BVOL and MVOL; stop/shutdown replies |
| `movie` | 0x8100 position: start offset + 2 buffered units, +1 unit after 256 frames, exact after 1 s at 48 kHz incl. the half bit; STOP reply and freeze; 0x80D0 clear; FIFO frame count; 60 fields = 48048 frames |
| `movie_refill` | the game's first refill after the start (AudioDecIopGetArea formula on the 0x8100 position) reaches only the unit already in the input buffer; all 24 preset units are heard in order at the expected level |
| `render_hash` | SE + bend + key off + sequence, FNV-1a of 1 s of output: equal across two runs and equal to the pinned value |
| `modhsyn_bend` | per-id bend (SKMSIN 0x41 -> FD 02) on a split with range 0x400: 0x2000 unbent, 0 = -1024/128 (8 semitones down, pitch 2580), 0x3FFF = +1023, 0x1FFF truncates to 0, another id or note untouched, id 127 = any id |
| `modhsyn_volume` | VOLL/VOLR from the MODHSYN chain: volume 0x28 -> 5080 (the title cursor's words), 0x7F -> 0x3F80, FD 01 pan 0x60 -> left 7874, pan 0 -> right 0, key-on F9 01 x = 0 -> right 0, velocity 64 -> 0x2000, Sset curve 2 at velocity 64 -> 0x1000 |
| `reverb` | HALL work area placement (ESA = 0x200000 - 0xADE0) and a reverb tail after the dry voice ended |
| `*_control` (`WILL_FAIL`) | `adpcm_control` expects a wrong filter-1 sample, `pcm_ring_control` expects the block 1024 frames early, `movie_control` expects 44.1 kHz, `movie_refill_control` refills from the unit being played (21 of 24 preset units lost), `modhsyn_bend_control` expects the old `>> 14` depth (-4 semitones), `modhsyn_volume_control` expects the old product `0x3FFF * 40 / 127`; each must fail, and does |
| `play_tool` (data) | `rg-sound-play` renders sy_000 program 3 to a WAV |

Status 2026-10-12: 23/23 pass (16 tests, 6 controls, 1 tool run), `build\audio-i686`.

## rg-sound-play

```
rg-sound-play [--data DIR] --snd snd2\sy_000.snd --list
rg-sound-play --snd snd2\sy_000.snd --prog 3 [--note N] [--vel 127] [--hold 1.0] [--len 3]
              [--pan 0x40] [--sevol 0x7F] [--bend 0x2000] -o se.wav
rg-sound-play --snd snd2\bgm\bg_000.snd --seq [--block 0] [--vol 0x80] [--len 60] -o bgm.wav
```

Loads the pack from the archives, boots the HLE like the game (sceSdInit, MVOL, SK init,
effect areas, reverb mode 4 on core 0), uploads the bank through the RPC path and plays
an SE (MSIN key on/off; `--pan/--sevol/--bend` are the key on's `x` and the 0x42 / 0x41
words that follow it) or the pack's sequence (SKMIDI). Prints peak, mean square, key
ons, unresolved notes, voice steals, clipped samples and the output hash.
`RG_SOUND_VERBOSE=1` prints voices and MIDI ticks per second for sequences. Example:
`bg_000` at volume 0x40 renders 30 s with 417 notes, 0 unresolved, peak 24727, no clipping,
spectral flatness 0.1-0.27 (tonal).

## Validation against PCSX2 (2026-10-12)

No-input title run (power-on, logos movie `00/TITLE01`, title movie `00/TITLE02` with the
menu over it, then the attract movie `00/RUSH`), port vs the portable PCSX2 2.6.3. Raw
captures stay in `out/audio/` (gitignored: game audio). The SK hsynth/MIDI path is silent
in this run on both sides (port log: SKMIDI track 4 plays with track volume 0, every key
on has VOLL/VOLR 0; PCSX2: nothing is left after removing the movie, below), so the SE
path was checked separately with a scripted cursor move (last subsection).

### Capturing

- **PCSX2.** 2.6.3's release build has no SPU2 WAV dump: `SPU2/Debug` `Global_Enable` +
  `Log_WAVE_Output` write nothing (a run with both on left no new file under
  `.tools/pcsx2`), and media capture needs FFmpeg DLLs the portable copy lacks plus a GUI
  hotkey. `tools/trace/audiocap.py` takes the audio at the host sink instead: the SDL
  backend (`SPU2/Output/Backend = SDL`, `SyncMode = Disabled`, so nothing is
  time-stretched) with SDL3's `disk` driver writing the device stream (s16 stereo,
  48000 Hz; PCSX2 logs "sample rate = 48000, stretching disabled") to a raw file on a
  fast local disk (on B: the driver blocked on writes and consumed 40-48k frames/s). The
  driver paces itself with sleeps (`SDL_AUDIO_DEVICE_SAMPLE_FRAMES=4795`: 99 ms + ~1 ms
  overhead, ~48.2k frames/s); PCSX2 produces 48000 x 59.96/59.94 frames per wall second,
  so the capture has occasional drops or inserted blocks (tens to hundreds of frames every
  few seconds, and 82,808 frames once while PCSX2 fell to 56.5 vbl/s under a parallel
  build). Between them the capture is sample-exact: against the movie WAVs, coherence
  >= 0.996 from 100 Hz to 20 kHz. `audiocmp.py` splits every capture into such runs.
- **VBlank alignment.** While it runs, audiocap polls over PINE every 2 ms: host time,
  the game VBlank counter `[0x004810C4]`, the movie decoder's "bytes sent to the IOP"
  (`D_004B32D0+0x54`) and the raw file size, into `<out>.poll.tsv`. A capture frame maps
  to host time (file size, +-1 device chunk = 100 ms) and from there to the game VBlank.
  That is good to a few VBlanks only, so sections are aligned by content: each movie run
  is located in the capture to the sample, and its start is tied to the VBlank the decoder
  began sending (TITLE01 vbl 707/708, TITLE02 1504, RUSH 5128; the content-derived VBlank
  of movie sample 0 comes out 2-7 later, the output latency).
- **Port.** `RG_AUDIO_WAV=<path>` makes the runtime write every frame the host half
  receives to a 48 kHz s16 stereo WAV, plus `<path>.fields.tsv` (field, kernel VBlank,
  game VBlank, frames so far, cycle). Sample 0 is virtual time 0, so frame n is cycle
  3072 n exactly (runtime test `audio_wav`). `RG_SND_LOG=<path>` logs every sdr_driver
  call (frame, fno, words; SK blocks w1..w11) and one `KON` line per synth key on
  (track/ch/prog/note/vel/id, layer fields, pitch, volumes, bend range);
  `RG_SND_LOG_ALL=1` adds the 0x8100 polls.

```
python tools/trace/audiocap.py --out out/audio/pcsx2_title --stop-vbl 6300 --raw-dir <local temp dir>
set RG_DATA=data& set RG_AUDIO_WAV=out\audio\port_title.wav& set RG_SND_LOG=out\audio\port_sdr.tsv
build\audio-i686\rg-game.exe --headless --fields 6300 --saves out\audio\saves_empty
python tools/sound/audiocmp.py report out/audio/port_title.wav out/audio/pcsx2_title.wav --movies 00/TITLE01,00/TITLE02,00/RUSH
```

### Results: movie audio (core 0 AutoDMA)

| | port | PCSX2 |
| --- | --- | --- |
| rate, channels | 48000 Hz (800.79 frames/field over 6300 fields), L/R | 48000 Hz, L/R |
| channel order | L = movie L, R = movie R (corr 1.0000; L~R 0.578 is the movie's own) | 2x2 fit: L = 0.6193 L + 0.0001 R, R = -0.0003 L + 0.6196 R |
| level vs the movie WAV | 0.9917 (-0.07 dB): BVOL 0x7FFF, MVOL 0x3FFF x2, AVOL 0x7FFF, MVOL 0x3F7F x2 | 0.6213 (-4.13 dB), flat 500 Hz-20 kHz |
| low end | flat | first-order high-pass near 40 Hz (-0.5 dB and +0.35 rad at 100 Hz, -2.6 dB and +0.73 rad at 50 Hz) |
| DC | none | -95 on both channels (-50.7 dBFS) from the first movie start on; it halves with PCSX2's output volume (-49.6 at 50 %), so it comes from its SPU2 output, not the host |
| residual after gain x movie | -83 dBFS (rounding) | -42 dBFS median (DC, high-pass, capture inserts; nothing else plays) |
| spectrum (TITLE02 11.8-17.3 s, RUSH 7.9-10.9 s) | dB-spectrum correlation 0.9997 / 1.0000; port - PCSX2 = +4.0..+4.1 dB in every octave from 125 Hz, +4.8 dB at 62.5 Hz | |
| peak, clipping | 15811, 0 clipped | 9571, 0 clipped |
| gaps / dropouts | none (no zero or held runs between audible audio) | only the capture's own inserts |
| loudness during TITLE02 | -19..-27 dBFS RMS per second | -23..-31 dBFS (the same +4 dB) |
| timing | movie sample 0 at the `0x80E0` start, to the sample (fields 287, 1067, 4667) | TITLE01 data from vbl 707 to 1484, TITLE02 from 1504 to 5103, RUSH from 5128 |

- **Fixed: the first 128 ms of every movie were lost.** Before the input-buffer model
  ("IOP HLE" above), the port's audio for each movie was the WAV from sample 6144 on,
  starting at the `0x80E0` start: the first 24 KiB were overwritten by the EE's first
  refill before they were played (port log: the start's position poll returned the ring
  base, so AudioDecIopGetArea reported 0x5C00 bytes free), and everything after came
  128 ms earlier than its stream position. PCSX2's TITLE02 starts with its quiet first
  6144 samples present (normalised correlation 0.99 in each 1 KiB block from sample 0).
  After the fix the port plays sample 0 at the start (offset 0 in all three movies); the
  boot timeline (`STATUS` lines over 6300 fields) is unchanged.
- **Open: PCSX2's movie path is 4.1 dB quieter, high-passed and offset by DC.** The
  register values the port uses are retail's (LIBSD sceSdInit: core 1 AVOL 0x7FFF; the
  game: BVOL 0x7FFF through thread cmd 0x25, core 0 MVOL 0x3FFF, core 1 MVOL
  `(0x7F * 129) & 0x7FFF`), and with psx-spx's fixed-volume scaling (x2) they give 0.992.
  Nothing in the game's or libsd's code accounts for 0.62, a 40 Hz high-pass or a constant
  -95, so these look like PCSX2's own SPU2 output processing; only a hardware recording
  can settle it. Not changed.
- **Timeline (not sound).** The port reaches the logos movie 420 VBlanks earlier (field
  287 vs vbl 707: no BIOS, an instant card check) and starts TITLE02 in the field it stops
  TITLE01 (PCSX2: 20 vbl later, the MVI open on the CD). TITLE01 plays 780 fields in the
  port and 777 vbl in PCSX2 (poll resolution), TITLE02 3600 vs 3599. Both then play the
  attract movie `00/RUSH`.

### Results: SE path (MSIN key on)

Input `out/audio/se_input.txt` (DOWN at game vbl 2400, 2600, 2800 on the title menu; the
port keys it by kernel VBlank). The cursor SE is a plain SE: `SoundPlayDefault/Vol` ->
`SoundPlayEntry_1b8f90` -> `SoundPlayEntryKeyOn_1b81e0` -> thread cmd 0x20 -> G3 0x11
(track 0, bank slot 0, prog 4, note 60, vel 0x7F, x = pan 0x40), then 0x42 volume
`vol * D_004A1E40[0] / 127` = 0x29 and 0x41 bend 0x2000 (the callers pass pan 0x40 and
bend 0x2000). The confirm jingle (progs 27/50/51) is EE-sequenced (`SoundSeqNoteOnOff` ->
`SoundSendKeyOn_1b80c0`, same thread command). `tools/sound/se_extract.py` removes the
movie under the SE; `tools/sound/se_compare.py` locates the movie per SE (PCSX2 captures
drop/insert blocks), finds the onset and reports f0 and level:

```
python tools/sound/se_compare.py out/audio/pcsx2_se.wav --at 45.38,52.05
python tools/sound/se_compare.py out/audio/port_se3.wav --at 40.05,43.38,46.72
```

**Root cause: the port's EE sends the wrong key-on words.** Both key-on callers pass three
`s64` values (velocity, pan, bend) to the varargs `SoundSendCmd_1b6cc0(0x20, 10, ...)`,
which reads ten `va_arg(ap, s32)`. On the EE each argument is one 64-bit slot, so the
thread gets `[track, id, bank, prog, ch, note, vel, pan, volume, bend]`; on i686 an `s64`
takes two 32-bit slots, so it gets `[..., note, vel, 0, pan, 0]`: x (F9 01) = 0, the 0x42
volume = the pan (0x40), the 0x41 bend = 0, and the real volume and bend are dropped.
This is EE code in `game/` (bring-up lane): `SoundSendKeyOn_1b80c0` and
`SoundPlayEntryKeyOn_1b81e0` must pass `(s32)` for their `s64` arguments to
`SoundSendCmd_1b6cc0`. Verified with an experimental build (the two units patched in a
scratch copy, linked into `buildudio-i686g-game.exe` only; the log then shows
`11 ... 3C 7F 40`, `42 ... 29`, `41 ... 2000`).

The IOP side was also wrong and is fixed from MODHSYN ("Synth" above): bends were scaled
`>> 14` (MODHSYN: `/ 8192`, twice the depth), channel and per-id bends added (MODHSYN:
one field, last writer), the F9 01 pan was ignored, and the volume was a float-like
product instead of MODHSYN's integer chain. With the EE's wrong words the old port played
-1 semitone (0 bend at half depth) and +4.1 dB (0x40 instead of 0x29).

| title cursor SE (prog 4, note 60) | f0 | peak L/R | RMS 0.1 s L/R | vs PCSX2 (level) |
| --- | --- | --- | --- | --- |
| PCSX2 2.6.3 (2 clean presses) | 2209.8 / 2205.9 Hz | 6057/6010, 6403/6381 | 1648/1642, 1689/1659 | |
| port before (EE words wrong, old IOP) | 2084.7 / 2084.0 Hz | 15284/15327 | 4298/4301 | +7.8 dB peak, +8.2 dB RMS |
| port, IOP fixed, EE words still wrong (tree as committed) | 1968.9 / 1966.9 Hz | 15060/3 | 4355/1 | -2 semitones, hard left |
| port, IOP fixed + EE fix (experimental build, 3 presses) | 2210.2 / 2202.0 / 2205.9 Hz | 9624/9623 .. 9725/9667 | 2610/2615 .. 2634/2635 | +3.8 dB peak, +3.9 dB RMS |
| `rg-sound-play --prog 4 --note 60 --sevol 0x28` (HLE replay) | 2206.9 Hz | 9499/9499 | 2591/2591 | |

The movie path differs by 4.1 dB between the two (PCSX2's 0.62 output gain, "movie
audio" above), so with both fixes the SE voice is within 0.2-0.3 dB of PCSX2 and its
pitch within the FFT's resolution (0.1 %); before, the voice was 3.9 dB too loud. The
2 kHz-band envelope per 10 ms after the peak matched before and is unchanged (same
ADSR, same sample).

Tools: `tools/trace/audiocap.py` (PCSX2 capture; `--input` scripts need `--speed 0.5
--timescale 2.0`), `tools/sound/audiocmp.py` (`movie`, `stats`, `report`),
`tools/sound/se_extract.py`, `tools/sound/se_compare.py`.

## What PCSX2 captures would validate

PCSX2 is a reference runtime only (never a code source). Useful captures, each
compared against the same scripted request sequence replayed into the HLE:

1. **Single-voice WAV per SE:** run the title screen, trigger one menu SE, record the
   SPU2 output (PCSX2's WAV dump or an external recorder; the recorder needs its ffmpeg
   DLLs). Compare pitch (FFT peak), envelope shape (RMS per 1 ms) and level. Validates
   Note2Pitch scaling, ADSR, volume formula, pan law, velocity handling.
2. **Interpolation:** a sample played at a non-integer pitch (any transposed note):
   high-frequency content differs between the Gaussian table and the B-spline.
3. **Reverb tail:** a dry SE in a room using core 0 mode 4 (STUDIO_C, depth 0x28);
   compare tail length and spectrum.
4. **BGM:** record 60 s of a town/menu BGM and compare onset times (sequencer timing,
   tempo, loops), levels per channel (CC7/CC11/track volume, velocity curve) and voice
   stealing artefacts.
5. **Register dumps:** with PCSX2's SPU2 debug logging, the VOLL/VOLR/PITCH/ADSR values
   written by MODHSYN for a known key on give the exact MODHSYN formulas to replace the
   approximations listed above.
6. **Movie/pcm_mixer pacing:** the EE's `0x8100` reads and `0x80A0` replies per vblank
   during an FMV and a voiced scene; the HLE must produce the same refill cadence.

## Load-screen audio (checkpoint 2026-10-12)

User report: in a windowed run (`RG_GPU=hw`) the audio during the load screen is a
little stuttery. Measured with the golden NEW GAME input
(`tools/trace/goldens/newgame_battle.input.txt`), 3,600 fields, RTX 3080, default 3x
internal resolution, `build/audio2-i686`, results in `out/audio2/`.

**Verdict: the emulated audio is clean; the device is starved because the NORMAL
loading screen runs slower than real time.** That comes from the GPU renderer (below), not
from audio, CD reads or the pacer. The title's resource-load screen (fields 500-700) is
fine: 16.68 ms per field and the device never starves there.

### Measuring (`RG_AUDIO_LOG`)

`RG_AUDIO_LOG=<path>` (any windowed or headless run) writes one TSV row per field:
`wall_ms` (field end to field end), `work_ms` (wall minus the pacer's sleep),
`slept_ms`, `present_ms`, `cd_reads` / `cd_sectors` / `cd_ms` (the wall time spent
inside `cdvd_disc_read`, via `cdvd_set_io_clock`), `frames` pushed, the host queue before
and after the push (`q_before`, `q_after`, frames), `starves` / `starve_frames` (device
pulls the SDL stream could not fill, counted in the stream's get callback), the
regulator's `pad` / `drop` frames and `ratio`, the pacer's `resyncs`, and the GPU
renderer's per-field `gpu_prims`, `gpu_batches`, `gpu_dst_copies`, `gpu_writebacks`,
`gpu_up_kb`, `gpu_down_kb`. Wall clock only; nothing feeds back into the run.

### Numbers

| Fields (game vbl) | What | work ms/field avg (max) | GPU batches / dst copies / write-backs per field | device starved (old host) |
| --- | --- | --- | --- | --- |
| 500-700 | title resource load | 10.3 (25) | 18 / 0 / 0 | 0 |
| 1900-2150 | NEW GAME, title fade | 13.5 (33) | 22 / 5 / 0 | 23 ms |
| 2150-2700 | NORMAL loading screen | 21.6 (68) | 241 / 225 / 219 | 3.09 s of 12.3 s |
| 2700-3500 | loading screen, then story screen | 26.5 (92) | 441 / 423 / 419 | 10.1 s of 23.4 s |

- In 2150-3500, about 470 of 1,350 fields take more than 20 ms (420 more than 33 ms), so the
  virtual clock runs at about 60-75 % speed, the pacer re-anchors 46 times
  (`max_lag_ns` 250 ms), and audio is produced at the same rate. No output buffer can
  cover a producer that is slower than the device; the gaps are the missing time.
- **CD is not it:** 22 reads in 2150-3500, 1.6 ms of wall time in all (at most 0.4 ms in a field).
- **The emulated audio is clean:** the `RG_AUDIO_WAV` of the same run (music through the
  whole load, fields 2150-3140) has no run of 64 or more zero frames and no sample step
  above 8000; it is byte-identical with `audio.latency_ms` 0 and 64. Sequence time
  freezing in loading loops (TIMING-REFERENCE.md "Sound-sequence owner") is not involved:
  the load-screen music is not EE-sequenced.
- **Where the time goes:** headless with no rasterizer (`RG_GS_NULL=1`) the same fields
  cost 7.3 / 8.3 ms; headless GPU at 1x 13.4 / 24.3 ms; windowed at native resolution
  18.4 / 23.9 ms, so it is not fill rate but per-batch cost (about 25-40 µs a batch).
  Flush reasons in fields 2150-3000 (temporary counters, removed): a primitive
  overlapping an earlier one of a *serial* batch 256k (about 300 a field), `GS_MEM_READ`
  66k, feedback splits 25k, state changes 3k. Every alpha-blended state is serial in the
  renderer (`need_dst = abe || date || merge`, GPU.md "Batching"), so the loading
  screen's few hundred overlapping blended sprites per field each become one batch with
  a destination snapshot (`CopySubresourceRegion`), an `unbind_all` and about 20 D3D11
  calls.
- Tried and reverted: writing a target back only when its *dirty* pages (not its whole
  page set) meet the batch's read set cut write-backs from 456k to 19k in the run, but
  the field cost did not move (20.2 / 26.0 ms): the write-backs were not the bottleneck.

**Fix belongs to the GPU renderer** (open item there): cheaper serial batches (no
`unbind_all` per draw, a vertex ring with `NO_OVERWRITE`, constant/state updates only on
change, one snapshot per group of non-overlapping prims), or an exactness-preserving way
to blend without a snapshot. Until then the load screen will run below full speed.

**Follow-up (2026-10-12, GPU.md "Performance"):** ordered blending (ROVs), high-byte
texels, batches across unchanged CLUT reloads and a cheaper draw path took the loading
screen from ~480 batches and ~460 destination copies per field to 4.3 and 0.1. Same
windowed x3 golden run (`out/gpuperf/win_base` vs `win_new`, `RG_AUDIO_LOG`), fields
2150-3150: wall 35.7 → 19.1 ms per field (about 87 % of real time; the rest is GPU fill
at x3), device starved 4.45 s (544 starves) → 0.06 s (31). At x1 (`RG_GPU_SCALE=1`,
`win_new_x1`) they run in real time: wall 16.75 ms, 0.002 s starved.

### Host output regulator (`audio.latency_ms`)

Before this, the host pushed each field's audio straight into the SDL stream, so the
queue held about one field and any field that ended late starved the device, which then
rebuilt its cushion only by starving. `src/host/host_audio.c` (pure, test
`host.audio_reg`) keeps a cushion of `audio.latency_ms` (default 64 ms, 0 = old
behaviour, live):

- silence up to the target before the first push, and again when the device starved
  (or the pacer re-anchored: `rg_host_audio_resync`) and the queue is below half the
  target;
- a playback-rate trim (`SDL_SetAudioStreamFrequencyRatio`, at most ±0.5 %) on the
  smoothed queue error, for device clock drift (HOST.md open item);
- when the queue is more than max(target/2, two fields) over the target (the pacer caught
  up after a hitch that had already been padded), the front of the push is dropped.

Silence and drops are host-side only: `RG_AUDIO_WAV`, the run hash and headless runs do
not change. Measured: outside the load screen the device no longer starves (fields
1900-2150: 0 vs 23 ms); in the load screen the total silence is unchanged (2.96 s vs
3.09 s in 2150-2700), as expected while the game runs below real time. Simulated
(`host.audio_reg`): 25 ms late every 7th field or 12 ms every 3rd never starves; ±0.3 %
device drift for 30 minutes holds the queue within 30 ms of the target without a starve
or a drop; a 150 ms and a 400 ms hitch are one starve each and the queue is back at the
target afterwards; the old behaviour starves at least 18 times in a minute of a
loading-like pattern with re-anchors.

## Open items

- MODHSYN LFOs, portamento, surround pan mode, drum mode, user velocity tables and voice
  stealing ("Synth", not modelled); MODHSYN #8 (`0x70`) meaning.
- **EE key-on varargs (bring-up lane):** `SoundSendKeyOn_1b80c0` and
  `SoundPlayEntryKeyOn_1b81e0` must cast their `s64` arguments to `s32` for
  `SoundSendCmd_1b6cc0`; until then every SE and EE-sequenced note plays hard left, without
  its volume, and 2 semitones flat (bend 0) (Validation, SE path). Other varargs callers
  passing `s64` would have the same problem.
- From the PCSX2 validation (above): PCSX2's movie-path gain, high-pass and DC.
- SKMIDI relative/absolute tempo units are inferred (**L**).
- Reverb: hardware resampling filters, ECHO/DELAY feedback/delay registers.
- IRQ address (IRQA) and SPU2 interrupts are not modelled (the game installs no handler).
- KON latency and the exact hardware ADSR counter granularity.
- The NORMAL loading screen ran at 60-75 % speed in the GPU renderer, so its music had
  gaps on the device ("Load-screen audio"). Since GPU.md "Performance" it runs at ~87 %
  at x3 (real time at x1) and the device starves 0.06 s instead of 4.45 s over fields
  2150-3150; the remaining x3 cost is GPU fill.
