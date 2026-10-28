# Sound protocol (EE <-> IOP)

What the game's EE sound code sends to the IOP, what the retail IOP modules do with it, and
what a host implementation has to answer. Sources: our own R3000 disassembly of the retail
IRX files in `data/MODULES/` (offsets below are module-relative `.text` offsets), the
decompiled EE code in `game/src/main/{sound,movie,sys,sdk}/`, and the retail EE ELF for the
few functions that are not in the corpus. CC0. No PCSX2 code or text was used; libsd
export numbers and constant names follow the public ps2sdk headers (AFL) and were checked
against how SDRDRV/SKSOUND/PCMPLAY call them (argument shapes match one-to-one).

Confidence: **H** = seen in the IRX disassembly and at an EE call site; **M** = one side
only; **L** = inferred.

| Service | IOP side | EE side | Used for |
| --- | --- | --- | --- |
| RPC 0x80000701 | sdr_driver 4.1 (SDRDRV.IRX) | `sceSdRemote_1229e8` | libsd calls, plus 0x90F0 = Standard Kit (SK) command blocks |
| SK stack | SKSOUND, SKHSYNTH, SKMIDI, SKMSIN over MODHSYN/MODMIDI/MODMSIN | `SoundIopSendCmdG*S*` (gcc island 0x165608..) | banks, sequences, key on/off |
| RPC 0x80000704 | bound by SDRDRV's callback thread | `SdrCallbackThread_122fa8` (EE server) | IOP->EE libsd interrupts (never fire, see 4) |
| RPC 0x123456 | pcm_mixer 1.2 (PCMPLAY.IRX) | `SoundRpcCall_1bc5e0` | 4-port PCM stream mixer on core 1 AutoDMA |
| raw SIF DMA | IOP RAM from `sceSifAllocIopHeap` | `SifDmaSendSync_1c21e0`, `_1d2c20` | HD headers, BD staging, SQ data, PCM blocks, movie PCM |

## 1. sdr_driver, RPC 0x80000701

### Request layout (H)

`sceSdRemote_1229e8(int wait, int cmd, a1..a6)` copies its six variadic words into a static
64-byte buffer at EE 0x48D900 (cd at 0x48D940). Word 0 holds the buffer's own EE address
(ignored by the IOP). `wait` is 1 at every game call site: blocking `sceSifCallRpc`.
`wait == 0` would select `SIF_RPC_M_NOWAIT` with a callback (unused).

| `cmd` range | fno sent | send buffer, size | receive (EE 0x48D900) | Result |
| --- | --- | --- | --- | --- |
| 0x8130, 0x81A0, 0x81B0 | `cmd \| a1` (a1 = core) | `a2` (pointer to the attr struct), 0x40 | 0x40 bytes | word 0 |
| 0x8140 | `cmd \| a1` | request, 0x40 | 0x40 bytes (attr struct) | (not used) |
| 0x81C0, 0x81D0 | `cmd` | batch array, `(n+1)*8` | user buffer | (not used) |
| 0x9000..0x90F0 | `cmd` | `a1` (pointer), `a2` (size) | 0x10 bytes | word 0 |
| everything else | `cmd` | request `{self, a1..a6}`, 0x40 | 0x10 bytes | word 0 |

`sceSdRemoteInit_122890` binds 0x80000701 in a loop until `cd.server != 0` (spins 10000
between tries). The call returns the first word of the reply.

### IOP dispatch (H)

`sceSifRegisterRpc(sd, 0x80000701, func=0x588, buf=0x1C30, 0, 0, queue)` in the thread at
0x4E0 (priority from `thpri=`, default 24). The dispatcher at 0x588 switches on
`fno & 0xFFF0`. Arguments are read from the receive buffer `d`: `d+4` = a1, `d+8` = a2, ...
The result goes to the reply word at 0x14E0; the server returns 0x14E0 (0x1C70 for 0x8140,
0x1630 for 0x81C0/0x81D0).

| fno | libsd call (export #) | Args read | Game use |
| --- | --- | --- | --- |
| 0x8000 | sceSdInit (4) | lw 4 | - |
| 0x8010 | sceSdSetParam (5) | lhu 4 entry, lhu 8 value | **yes** |
| 0x8020 / 0x8040 / 0x8060 / 0x8080 | Get Param/Switch/Addr/CoreAttr (6/8/10/12) | lhu 4 | - |
| 0x8030 | sceSdSetSwitch (7) | lhu 4, lw 8 | - |
| 0x8050 | sceSdSetAddr (9) | lhu 4 entry, lw 8 byte address | **yes** |
| 0x8070 | sceSdSetCoreAttr (11) | lhu 4, lhu 8 | **yes** |
| 0x8090 / 0x80A0 | Note2Pitch (13) / Pitch2Note (14) | halfwords | - |
| 0x80B0 / 0x80C0 | ProcBatch (15) / ProcBatchEx (16) | lw 4.. | - |
| 0x80D0 | sceSdVoiceTrans (17) | lh 4 ch, lhu 8 mode, lw 12 iop, lw 16 spu, lw 20 size | **yes** (movie) |
| 0x80E0 | sceSdBlockTrans (18) | lh 4 ch, lhu 8 mode, lw 12 iop, lw 16 size, lw 20 start | **yes** (movie) |
| 0x80F0 / 0x8100 | VoiceTransStatus (19) / BlockTransStatus (20) | lh 4, lh 8 | 0x8100 **yes** (movie) |
| 0x8130 | sceSdSetEffectAttr (23) | core = fno & 0xF, attr = `d` | **yes** |
| 0x8140 / 0x8150 / 0x8180 / 0x8190 | GetEffectAttr (24) / ClearEffectWorkArea (25) / StopTrans (30) / CleanEffectWorkArea (31) | | - |
| 0x8160 | sceSdSetTransIntrHandler (26): core `d+4`, enable `d+8` -> IOP handler 0xF2C (core 0) / 0xF6C (core 1) | | - |
| 0x8170 | sceSdSetSpu2IntrHandler (27): enable `d+4` -> 0xFAC | | - |
| 0x81A0 / 0x81B0 | SetEffectMode (32) / SetEffectModeParams (33) | | - |
| 0x8F10 | sdrdrv export 4: change main/callback thread priority | | - |
| 0x9000..0x90F0 | user command table at 0x14F0[(fno>>4)&0xF]; `handler(fno, d)`; nothing registered = reply 0 | | 0x90F0 **yes** |
| 0xE620 | create + start the callback thread (entry 0xFF0) | | **yes** (init) |
| 0xE630 | terminate + delete it | | - |

0x8110/0x8120 (SetTransCallback/SetIRQCallback) are not handled ("unknown command").
SDRDRV exports (table at 0x1080): #4 = change thread priorities (main, callback), #5 =
`SetUserCommandFunction(cmd, func)` for 0x9000..0x90F0, returning the previous handler
(-1 if out of range).

### What the game sends (H unless marked)

All calls come from the EE sound worker thread (`SoundCmdWorkerThread_1b6c10`, one command
at a time) or from init. Entry encoding is libsd's: `(param << 8) | 0x80 | core` for core
parameters; `core` = bit 0.

| EE function (thread cmd) | Calls | Meaning |
| --- | --- | --- |
| `SdRemoteInitMasterVolume_165608(5)` | Init; CallbackInit(5); SetParam 0x980=0x3FFF, 0xA80=0x3FFF, 0x981=0, 0xA81=0 | MVOLL/R core 0 = 0x3FFF, core 1 = 0 (core 1 is raised later by SK G0 0x80) |
| `SoundThreadCmdEffectEnable_1b6700` (0x21) `{on, input}` | on: SetParam 0x800/0x801 = 0xFFFC if input else 0xFFCC; SetCoreAttr 2,1 / 3,1. off: MMIX 0xFFCC, SetCoreAttr 2,0 / 3,0 | MMIX both cores (0xFFCC drops SINL/R+MINL/R wet; 0xFFFC keeps memory-input wet); effect enable both cores |
| `SoundThreadCmdSetReverbMode_1b66b0` (0x22) `{core, mode}` | 0x8130 core, attr `{?, mode\|0x100, depth 0, 0}` | reverb type, `0x100` = clear work area |
| `SoundThreadCmdSetReverbDepth_1b6630` (0x23) `{core, d}` | SetCoreAttr 2\|c,1; SetParam 0xB80\|c and 0xC80\|c = `(d<<8)&0xFFFF` | EVOLL/R |
| `SoundThreadCmdSetReverbEndAddr_1b65d0` (0x24) `{core, start, end}` | SetCoreAttr 2\|c,0; 0x8050 0x1D00\|c = end | effect end address (EEA, bytes) |
| `SoundThreadCmdSetInputVolume_1b6570` (0x25) `{core, v}` | SetParam 0xF80\|c, 0x1080\|c = v | AVOLL/R (core AutoDMA input volume); movie uses core 0 |
| `SoundThreadCmdSdRemote_1b6540` (0x26) `{cmd, a1..a5}` | raw pass-through | movie audio, below |

`SoundSpuInit_1bb710` at boot: 0x21(0,0); EEA core 0 and 1 = top-of-SPU-heap work areas
(0x7000 bytes each, 0x20000 aligned); 0x21(1,0); mode core0 = 4, depth core0 = 0x28; mode
and depth core1 = 0.

Movie audio (`AudioDec*`, core 0 AutoDMA, H): Start = `0x80E0 (ch 0, mode 0x13 =
WRITE_FROM|LOOP, iop ring, size & ~0x3FF, iop ring + resume offset)`; position =
`0x8100 (0, 0)`, the EE uses `result & 0xFFFFFF` minus the ring base as the read offset;
Pause = `0x80E0 (0, 2 = STOP)` (its result, masked, is stored as resume offset) then
`0x80D0 (ch 0, mode 8 = write by PIO, iop zero buffer, spu 0x4000, 0x800)` to clear the
core 0 input buffer; volume via thread cmd 0x25 core 0 and SK master volume 0x3FFF.

### 0x90F0: hook into the SK stack (H)

SKSOUND imports sdrdrv export 5 and, at 0xD8C, calls `sdrdrv#5(0x90F0, 0xD30)` (skipped only
when its option word 0x1738 == 1). Handler 0xD30 takes byte 3 of the block (`w0 >> 24 &
0x7F`) as a module index into the table at 0x1750 and calls `module(fno, block)`. Modules
register with `sksound#17(index, handler)` (index < 7): SKSOUND = 0 (handler 0xE20),
SKHSYNTH = 1 (0x1310), SKMIDI = 2 (0x1660), SKMSIN = 3 (0xE60). The handler's return value
becomes the RPC reply word, i.e. the return value of `SoundIopSendCmdG*S*`.

## 2. SK command blocks (fno 0x90F0)

Block (64 bytes, zero-filled, built in a per-group static buffer: G0 0x44A180, G1 0x44A1C0,
G2 0x44A200, G3 0x44A240):

| Word | Field |
| --- | --- |
| w0 | module << 24 (G0..G3) |
| w1 | sub-command S (0..3, G0 also 0xA) |
| w2.. | arguments (`SoundIopSendCmdGxSy(w2, w3, ...)`) |

Every module dispatcher does `switch (w1)` and passes `w2..` as C arguments. Errors are
negative: -101 bad index / none free, -102 bad slot or state, -201 entry not loaded,
-202 track busy, -310 unknown sub-command, -402 library call failed.

SK "tracks" (SKSOUND `maxtrack=16`, 20-byte entries at `[0x1804]`): status word (bit 0 =
input attached (MIDI or MSIN), bit 1 = hsynth banks attached), input entry id, input type
(0 = MIDI, 2 = MSIN). SKSOUND exports: #8 maxtrack, #9/#10 set/get status, #11 set
(entry, type), #12..#15 field get/set, #16 first free track, #6/#7 register/unregister a
tick callback (index < 11), #18 VoiceTrans+wait. Its tick thread (hardware timer, option
`tickresolution=`) runs the callbacks in index order each tick: SKMIDI = 1, SKMSIN = 2,
SKHSYNTH = 9, so queued MIDI/MSIN input reaches the synth in the same tick (M).

### G0, SKSOUND (handler 0xE20, jump table 0x16F0)

| S | IOP action | EE sender (args) | Conf. |
| --- | --- | --- | --- |
| 0, 1 | return 0 | - | M |
| 2 | `ctl(w2, w3, w4, w5)` at 0xA64, switch on w3: | `SoundIopSendCmdG0S2_1656b8` | |
| 2 / 0x80 | SetParam 0x981 = `(w4*129)&0x7FFF`, 0xA81 = `(w5*129)&0x7FFF` (core 1 MVOL L/R) | `SoundThreadCmdSetMasterVolume_1b6ae0` (0x0C): `(3, 0x80, L, R)`; init `(3,0x80,0x7F,0x7F)` | H |
| 2 / 0x81 | SetCoreAttr 6,w4 and 7,w4 (mute both cores) | - | M |
| 2 / 0x82 | SetCoreAttr 2,w4 and 3,w4 (effect enable both cores) | init `(3, 0x82, 0)` | H |
| 2 / 0x83 | SetEffectAttr core 0 and 1, `{mode=w4, depth 0/0, delay=w5, feedback=w6}` | init `(3, 0x83, 0x105, 0, 0)`: hall, clear WA | H |
| 2 / 0x84 | EVOLL/R both cores = `w4*0x7FFF/127`, `w5*0x7FFF/127` | - | M |
| 2 / 0x8F | SetCoreAttr 10 (SPDIF mode) = w4 | init `(0, 0x8F, 0x880)` | H |
| 2 / 1, 2 | start / stop the SK tick timer | - | M |
| 3 | w2 == 0: return SK tick counter, else -310 | - | M |
| 0xA | `sceSdVoiceTrans(w2, WRITE, iop=w3, spu=w4, size=w5)` then `VoiceTransStatus(w2, 1)` (blocks until done); returns the VoiceTrans result | `SoundIopSendCmdG0SA_165778` from thread cmd 9 (`SoundSpuTransferChunks_1b6450`): `(0, staging, spuDst, n)` | H |

Note the master-volume formula: the EE passes `0x3FFF * v` (`SoundSetMasterVolume_1bb420`,
`AudioDecSetMasterVolume_1d2c00(0x3FFF)`), and SKSOUND stores `(x*129) & 0x7FFF`, which
wraps for x > 0xFE (0x3FFF -> 0x3F7F). An HLE must reproduce the formula, not "fix" it.

### G1, SKHSYNTH (handler 0x1310)

Bank-entry table (`maxentry=16`, 20 bytes at `[0x184C]`): `flags` (bit 0 HD set, bit 1 BD
set), `+4` HD IOP address, `+8` BD SPU address, `+0xC` HD size, `+0x10` BD size.

| S | Form | IOP action | EE sender | Conf. |
| --- | --- | --- | --- | --- |
| 0 | `(1, id, hd, hdSize)` / `(2, id, bd, bdSize)` | fill one half (id -1 = first free); return id | - | M |
| 0 | `(3, id, hdIop, hdSize, bdSpu, bdSize)` | fill both halves, flags = 3; return entry id | thread 5 `SoundThreadCmdBankUpload_1b6ba0` from `SoundBankUploadPart_1ba770`: `(3, -1, (hd+3)&~3, size, spuAddr, total)` | H |
| 0 | `(5, track, entry, slot)` | track -1 = first track with status&3 == 0; entry must have flags 3; slot < 16; `modhsyn#6` (= sceHSyn_Load, per its error string) `(env, track, bdSpu, hdIop, slot)`; status \|= 2; return track | thread 8 `SoundThreadCmdBankAttach_1b6b40`: `(5, tbl.x4 or tbl.x8, entry, part)` | H |
| 1 | `(1\|2\|3, entry)` | clear HD / BD / whole entry | thread 0x17 `BankRelease`: `(3, id)` | H |
| 1 | `(5, track)` | `modhsyn#28(env, track, slot)` for slots 0..14 (unload); status &= ~2 | thread 0x1A `BankDetach`: `(5, track)` | H |
| 2 | `(track, 0x1E)` | per-track flag +2 ? `modhsyn#20` : `modhsyn#12` (L: all notes off) | thread 1 `(track, 0x1E)` | H/L |
| 2 | `(track, 0x1F)` | flag +2 ? `modhsyn#21` : `modhsyn#13` (L: all sound off) | thread 2 `(track, 0x1F)` | H/L |
| 2 | `(0, 0x71, m)` | `modhsyn#18(m != 0)` (L: output mode, 1 = mono) | thread 0xA `SoundSetOutputMode_1bb3e0`: m = 0/1 | H |
| 2 | `(t, 0/1/2, v[, v2])`, `(t, 0x70, a, b)` | set track flags +2/+3 (SKMIDI/SKMSIN attach set both to 0); 0x70 -> `modhsyn#8({a,b})` | - | M |
| 3 | `(t, 0x70, i)` / `(t, 0x71)` / `(t, 0x72, entry)` | `modhsyn#26` pair [i] / `modhsyn#27` / count of voices whose current address (GetAddr 0x2040\|v<<1\|core) lies in the entry's BD range and ENVX != 0 | thread 0xB `(0, 0x71)`, no caller | M |

### G2, SKMIDI (handler 0x1660)

Sequence-data table (`maxentry=16`, 12 bytes at `[0x1ED0]`): flags, IOP address, size. MIDI
ports: `maxtrack=5`.

| S | Form | IOP action | EE sender | Conf. |
| --- | --- | --- | --- | --- |
| 0 | `(0, id, sqIop, size)` | register data (id -1 = first free); return id | thread 3 `SeqDataUpload` from FUN_001b9f00 (not in corpus): `(0, -1, (a+3)&~3, size)` after SIF-DMAing the SQ data | H |
| 0 | `(5, track, entry)` | track -1 = first free; track status bit 0 must be clear (-202); free MIDI port; `modmidi#6` = sceMidi_Load; route to the track's hsynth env (`skhsynth#4`); track input = (entry, type 0), status \|= 1; `skhsynth#9(track, 2, 0, 0)`; return track | thread 6 `SoundThreadCmdSeqAttach_1b6b80`: `(5, tbl.m8, ent.m9)` | H |
| 1 | `(0, id)` / `(5, track)` | release data / `modmidi#25` (sceMidi_Unload) and detach | thread 0x15 / 0x18 | H |
| 2 | `(track, cmd, mode, v)`, track must have status&3 == 3; jump table at 0x1D88 | | | |
| 2 / 0 | play: mode 0 = MIDI: optional `MidiSetLocation` (rewind), `SelectMidi(v)`, `MidiPlaySwitch(1)`; mode 1 = song equivalents | thread 0xE `SoundThreadCmdSeqPlay_1b6ab0`: `(track, 0, 0, block)` | H |
| 2 / 2 | stop (PlaySwitch off + SetLocation) | thread 0xF `(track, 2, 0)` | H |
| 2 / 3 | pause (PlaySwitch off) | thread 0xD `(track, 3, 0)` | H |
| 2 / 0x30 | mode 0: `MidiSetVolume(port, 0xFF, v&0xFF)`; mode 1: SongSetVolume | thread 0x12 `(track, 0x30, 0, v)` | H |
| 2 / 0x31, 0x32 | absolute (v&0xFF) / relative (v&0xFFFF) tempo | thread 0x10 / 0x11, no caller | M |
| 3 | `(track, q)`: q 0 -> state & 2, q 1 -> state & 4, q 8 -> state word +8 | thread 0x13, no caller | M |

### G3, SKMSIN (handler 0xE60): MIDI message input, used for every SE / note

MSIN entries: `maxentry=16`; ports `maxtrack=9`.

| S | Form | IOP action | EE sender | Conf. |
| --- | --- | --- | --- | --- |
| 0 | `(0\|2, id)` | allocate an entry (id -1 = first free); return id | thread 4 from FUN_001b9f00: `(0, -1)`, id kept at table +0x14C | H |
| 0 | `(5, track, entry)` | like SKMIDI attach, input type 2; return track | thread 7 from FUN_001b9f00: `(5, tbl+4, id)` | H |
| 1 | `(0\|2, id)` / `(5, track)` | release / detach | thread 0x16 / 0x19 | H |
| 2 | `(track, cmd, ...)`, track status&3 == 3 and input type 2; jump table 0x1230 (`cmd-0x10`) | builds MIDI messages for MODMSIN: `modmsin#7` = 3-byte message, `modmsin#9` = byte string | | |
| 2 / 0x10, 0x11 | key on. 0x11 args `(id, bank, prog, ch, note, vel, x)`; 0x10 has no id (IOP counter 0..126). Sends `CC#0 = bank` (`B0\|ch, 0, bank`), `Program = prog` (`C0\|ch, prog`), `{F9, 01, ch, x&0x7F, 0}`, `{FD, 10, ch, note, id, vel, 0}`; vel != 0 sets track status bits 0x40010; returns id | thread 0x20 `SoundThreadCmdKeyOn_1b6800` | H |
| 2 / 0x12, 0x13 | key off: only `{FD, 10, ch, note, id, 0, 0}` | thread 0x1B `SoundThreadCmdKeyOff_1b6970`: `(track, 0x13, id, bank, prog, ch, note, 0, 0)` | H |
| 2 / 0x40 | `{FD, 01, ch, note, id, v&0x7F, 0}` (pan) | thread 0x1E `SetPan`: `(track, 0x40, id, ch, note, v)` | H |
| 2 / 0x41 | `{FD, 02, ch, note, id, v&0x7F, (v>>7)&0x7F}` (14-bit pitch bend) | thread 0x1F; also 3rd message of KeyOn | H |
| 2 / 0x42 | `{FD, 00, ch, note, id, v&0x7F, 0}` (volume) | thread 0x1D; also 2nd message of KeyOn | H |
| 3 | `(track, 0x11, id)` -> `skhsynth#10` -> `modhsyn#23`, returns status byte & 0x70 (L: voice state of that SE id) | thread 0x14, no caller | M |

KeyOn block, word by word: `w0=0x03000000, w1=2, w2=track, w3=0x11, w4=id, w5=bank slot
(the `slot` of G1 attach), w6=program, w7=MIDI channel (always 0 from
SoundSendKeyOn_1b80c0), w8=note, w9=velocity, w10=x`. The EE picks ids 0x66..0x7E itself
when the caller passes -1 (`SoundSendKeyOn_1b80c0`). After the key on it sends 0x42
(volume `f20`, category-scaled) and 0x41 (pitch bend `f24`). The meaning of `x` (F9/01)
is not known (L: priority or pan).

### Flow

1. **Bank load** (`SoundBankUploadPart_1ba770`): HD -> `IopHeapAlloc(size+4)`, SIF DMA to
   `(p+3)&~3` (stays resident; MODHSYN reads it from IOP RAM). BD -> SPU address from the
   EE's own SPU block heap (0x5010..0x200000, align >= 64); staging `IopHeapAlloc(0x404)`;
   `SoundSpuTransferChunks_1b6450` loops: SIF DMA 0x400 bytes EE->staging, then G0/0xA
   (VoiceTrans to SPU RAM, blocking); staging freed. Then G1/0/3 registers the bank, and
   G1/0/5 attaches it to the table's two SK tracks (`x4` = MSIN track, `x8` = MIDI track)
   at slot = part index (0..4). HD/BD are Sony "SCEI HD" banks (H for flow, M for format).
2. **SE / note playback**: G3/2/0x11 key on with id, then 0x42/0x41; G3/2/0x13 key off;
   0x40/0x41/0x42 updates. The EE runs its own MIDI sequencer (`SoundSeq*`,
   `MidiFileParse_1b5b50`) and drives notes through this path.
3. **Sequences** (SKMIDI): data via thread 3 (SQ in IOP RAM), attach (6), play/stop/pause/
   volume (0xE/0xF/0xD/0x12). Reached from `SoundPlayEntry_1b8f90` for entries of type 2.
4. **Stop/free**: thread 1+2 (all notes off / sound off) per track, then detach (0x1A,
   0x18, 0x19) and release (0x17, 0x15, 0x16) from `SoundBankFree_1b9c00`,
   `SoundBankStopAll_1bad70`, `SoundStopEntry_1b8bc0`.

All thread commands are synchronous: `SoundQueueCmd_1b6d60` hands the args to the worker and
waits for its result (`D_0049D540[]` async flags are all cleared at init).

## 3. pcm_mixer, RPC 0x123456 (PCMPLAY.IRX)

EE: `SoundRpcCall_1bc5e0(fno, n, args...)` packs up to 15 words into a 64-byte buffer
(EE 0x4A2580), blocking `sceSifCallRpc(cd 0x4A25C0, fno, 0, buf, 0x40, buf, 0x40)`, returns
word 0 of the reply. `SoundRpcInit_1bc840` binds until `cd.server != 0`.

IOP: `sceSifRegisterRpc(.., 0x123456, func=0x24C, buf=0x1304, ..)`; dispatcher 0x24C switches
on `fno & 0xFFF0`, args are `d[0..3]`, the result goes to 0x1300 and the server returns
0x1300 (EE reads only word 0).

| fno | Args | IOP action | Result | EE caller | Conf. |
| --- | --- | --- | --- | --- | --- |
| 0x8000 | core, blockBytes, nBlocks | needs core 0/1, blockBytes >= 2048, nBlocks >= 2. Allocates ring `blockBytes*nBlocks` and AutoDMA buffer `2*blockBytes` (IOP), creates mixer + output threads; write pos of ports 0..3 = 1, read pos = 0 | 0 / -1 | `SoundRpcInit_1bc840`: `(1, 0x1000, 3)` | H |
| 0x8090 | port 0..3, srcIop, volL, volR | if `(wpos[port]-rpos) mod n == 0`: return 0. Else the mixer thread adds `src*vol>>15` (saturating s16) into ring block `wpos[port]`, wpos++ | 1 mixed, 0 full, -1 bad port | `SoundStreamSlotSendToIopMaybe_1bd760` | H |
| 0x80A0 | port | `(wpos[port] - rpos) mod n` | free distance (EE sends only if > 0) | same | H |
| 0x8100 | - | `sceSdSetTransIntrHandler(core, 0x1158, &sema)`, `sceSdBlockTrans(core, LOOP(0x10), dmaBuf, 2*blockBytes)`, AVOL L/R = pending volume | 0 | `SoundRpcFrameTickMaybe_1bd690` (misnamed; = output start) via 0x1D68B0 from `GameSessionInit_1f5d80`, `EvCmdScreenWipeMaybe_267b90` | H |
| 0x8400 | - | AVOL 0, `BlockTrans(core, STOP)`, clear handler | 0 / 1 not running | `SoundRpcStopAllMaybe_1bd680` (= output stop), `SoundRpcShutdown_1bc760` | H |
| 0x10 | - | stop threads, free memory | 0 | `SoundRpcShutdown_1bc760` | H |
| 0x200 | vol `(L<<16)\|R` | pending AVOL, applied at the next half-buffer IRQ | 0 | `SoundStreamSetMasterVolumeMaybe_1bc6f0`: `0x7FFF*v` both halves | H |
| 0x300 | vol `(L<<16)\|R` | AVOL now | 0 | - | M |
| 0x8080 | - | no-op | previous | - | M |

Format and timing: a block is `blockBytes/1024` pairs of `[256 s16 L][256 s16 R]` (SPU2
AutoDMA layout). With `(1, 0x1000, 3)` a block = 1024 stereo frames (21.3 ms at 48 kHz),
3 ring blocks, 8 KB DMA buffer on core 1. On each half-buffer interrupt the output thread
(0x638) picks the idle half from `BlockTransStatus(core, 0)` bit 24, copies ring block
`rpos` into it (or silence if all 4 ports had nothing), clears that ring block, advances
`rpos`, and pushes any port whose `wpos` caught up one block ahead (underrun skip).

EE side: `SoundVblankIntrHandler_1bd6f0` (INTC 3, VBLANK end) signals the slot thread once
per vblank (and counts vblanks). `SoundStreamSlotThreadMain_1bc520` calls
`SoundStreamSlotUpdate_1bea70` for slots 0..3; each sends at most one block per vblank:
0x80A0, resample/deinterleave into the EE buffer at slot+0x124 (48000 Hz copies, other
rates step with a 12-bit fraction; peak -> slot+0xEC), `SifDmaSendSync_1c21e0` to the single
IOP staging buffer (`IopHeapAlloc(0x1004)` aligned, `D_004814DC`), then 0x8090 with float
volumes scaled to 0..0x7FFF. The staging buffer is reused because 0x8090 mixes before it
returns.

## 4. EE-side server 0x80000704 (H)

`0xE620` makes SDRDRV start its callback thread (0xFF0): it binds 0x80000704 (retrying until
`cd.server != 0`), then sleeps. The IOP interrupt handlers set bits in a 64-byte event block
at 0x1530 and wake it: 0x100 = core 0 transfer done (0xF2C), 0x200 = core 1 transfer done
(0xF6C), 0x400 = SPU2 IRQ, word 1 = its argument (0xFAC). The thread copies the block and
calls `sceSifCallRpc(cd, fno 0, 0, block, 0x40, NULL, 0)`.

EE: `sceSdRemoteCallbackInit_122d70` clears the handler slots (0x4478E8/EC/F0), sends 0xE620,
and starts `SdrCallbackThread_122fa8` (priority = its argument, 5) which registers
0x80000704 with `SdrCallbackRpcDispatch_123018`. The dispatcher calls handler 0x4478E8(0, arg)
for 0x100, 0x4478EC(1, arg) for 0x200, 0x4478F0(word1, arg) for 0x400.

The handlers are installed only by `sceSdRemote(.., 0x8160/0x8170, ..)`, which the game never
sends (only `sceSdRemoteCallbackQuit_122e70`, unreached, does). SKSOUND does not import
SetTransIntrHandler either. So **no callback is ever delivered**; a host only needs the
0x80000704 server to exist (or not), never to call it.

## 5. IOP RAM used by the game

| Allocation | Size | Owner | Contents | How the IOP learns it | Conf. |
| --- | --- | --- | --- | --- | --- |
| `IopHeapAllocLocked_1c22d0(0x1004)` | 0x1000 used, 4-aligned | `SoundRpcInit_1bc840` | PCM staging block | pcm 0x8090 arg 1 | H |
| `IopHeapAlloc(size+4)` per bank part | HD size rounded up to 4 | `SoundBankUploadPart_1ba770` | HD header, resident until release | G1/0/3 w4 | H |
| `IopHeapAlloc(0x404)` per upload | 0x400 chunks (multiple of 64) | same | BD staging, freed after upload | G0/0xA w3 | H |
| `IopHeapAlloc(size+4)` per sequence | | FUN_001b9f00 | SQ (MIDI) data | G2/0/0 w4 | H |
| `sceSifAllocIopHeap(0x6000)` | 24 KB | `AudioDecCreate_1d3210` (from `MovieOpen_1d5cf0`) | movie PCM ring (core 0 AutoDMA, 1024-byte units) | sdremote 0x80E0 | H |
| `sceSifAllocIopHeap(0x800)` | 2 KB, zero-filled by SIF DMA | same | silence for the input-buffer clear | sdremote 0x80D0 | H |

Rules: destinations are rounded with `(p+3)&~3`. `SoundSpuTransferChunks_1b6450` always
DMAs a full 0x400 chunk (the last one may read past the source and write past `size` into
the 0x404 staging). `SifDmaSendSync_1c21e0` and `_1d2c20` busy-wait on `sceSifDmaStat(id) >=
0` with `DelayThread(10)`. IOP-side buffers allocated by the modules themselves
(`AllocSysMemory`: PCM ring + DMA buffer, SK tables) never reach the EE.

## 6. Minimal HLE contract

Needed for the game to proceed (everything else may be ignored or logged):

| Item | Must do |
| --- | --- |
| Binds | `sceSifBindRpc` for 0x80000701 and 0x123456 must set `cd.server != 0` (+0x24), or the EE spins forever |
| iopheap (0x80000003 fn 1/2) | return distinct non-zero IOP addresses with room for the size; keep the bytes (HD, SQ and PCM are read later by address). A 0 return sends every upload to IOP address 0 |
| SIF DMA | complete each transfer (`sceSifDmaStat` < 0) and store the data in the IOP RAM model |
| sdremote 0x8010/0x8050/0x8070/0x8130 | apply to the mixer state (master/effect/input volumes, MMIX, reverb); reply 0 is fine |
| 0xE620 | reply anything; the EE thread is created EE-side and never receives a call |
| 0x80E0/0x8100/0x80D0 (movie) | play the core 0 ring as `[256 L][256 R]` s16 blocks from the start offset; 0x8100 must return `(half << 24) \| (ringBase + readOffset)` with `readOffset` advancing in real time, or `AudioDecSendToIop_1d2e90` stops refilling once the ring is full; 0x80E0 STOP returns the same form |
| G0/0xA | copy `size` bytes from IOP `w3` into SPU RAM at `w4` before replying (the next chunk reuses the staging) |
| G0/2/0x80 etc. | core 1 master volume `(x*129)&0x7FFF`; mute/effect/SPDIF can be stored only |
| G1/0/3 | return a bank-entry id 0..15 (the EE stores it and passes it to attach) |
| G1/0/5 | parse HD at the IOP address, bind it with the BD at the SPU address to (track, slot) |
| G1/1, G2/1, G3/1 | release / detach state; reply 0 |
| G2/0/0, G3/0/0 | return an entry id >= 0 (stored at table +0x14C for MSIN; MIDI ids per sequence) |
| G2/0/5, G3/0/5 | attach; return the track |
| G3/2/0x11, 0x13, 0x40..0x42 | voice allocation by (track, id): key on with bank slot + program + note + velocity, key off, live volume/pan/pitch bend. Replies are ignored by the EE (key on returns the id) |
| G1/2/0x1E, 0x1F | stop all notes / all sounds on the track |
| G2/2/* | sequence play/stop/pause/volume on the track (SKMIDI semantics) |
| pcm 0x8000/0x8100/0x8400/0x10/0x200 | replies ignored; keep state |
| pcm 0x80A0, 0x8090 | 0x80A0 > 0 when the port can take a block, 0x8090 = 1 after mixing the block at the staging address; a ring of 3 x 1024 frames drained at 48 kHz keeps the EE pace (one block per vblank at most) |
| VBLANK INTC 3 | must fire for the PCM slot thread to run |

Open questions:

1. Exact semantics of MODHSYN exports used by SKHSYNTH (#8, #12/#13 vs #20/#21, #18, #23,
   #26, #27); the names above are inferred from call shape. An HD/BD-driven synth needs the
   SCEI HD layout (program -> sample set -> sample -> VAG) and the `F9 01` / `FD xx` message
   semantics of MODMSIN/MODHSYN (MODHSYN.IRX not disassembled beyond imports).
2. Whether SKMIDI sequences are actually played at runtime (thread 3/6 exist and are
   reached from FUN_001b9f00 / `SoundPlayEntry_1b8f90`, but most music is EE-sequenced or
   streamed through pcm_mixer).
3. Meaning of KeyOn arg `x` (`F9 01 ch x`).
4. `SPDIF 0x880` value bits; MMIX bit names (taken from ps2sdk order).
5. FUN_001b9f00 (0x1B9F00..0x1BA5EC) and `SoundStreamSlotSendToIopMaybe_1bd760` are absent from
   the decompiled corpus; read from the retail ELF.
6. How the movie player paces video against the audio position (if it does), which decides
   how strict the 0x8100 position must be.

Corrections to the old recomp notes: 0x8050 is `sceSdSetAddr` (0x1D00|core = effect end
address), not SetSwitch. In the old block dumps `{class<<24, type, subop, handle, ...}`,
"subop" is the SK track (e.g. 9) and "handle" is the G3/2 command (0x11/0x41/0x42 = key on,
pitch bend, volume); the `{0x48d900, 0, 8, ...}` words are an sdremote request, whose word 0
is the EE buffer's own address. 0x80000592..0x8000059C are CDVDFSV.

Scratch tools used (not in the repo): an R3000 IRX disassembler on top of
`tools/census/platform/irx.py`, an EE ELF reader, and a `jal`/`j` call-site scanner.
