# Validation against PCSX2

Ground truth for assumptions other modules made, measured on the game running
in PCSX2 2.6.3 (portable copy, `tools/trace`; PLAN.md "Verification"). PCSX2 is
used as an external reference program only (D7): nothing below comes from its
source. Where PCSX2 is the reference, note that it runs the **real** BIOS EE
kernel and the **real** IOP modules from the disc (CDVDMAN, padman, ...), so
kernel and library behaviour measured here is retail code behaviour; only the
hardware below them (drive, SPU2 clock, VU timing) is PCSX2's model.

Tools (all in `tools/trace`, see its README "Probe runs"):

- `probe.py`: patches logging trampolines into the game's EE code (written over
  PINE while the CPU thread is frozen, like the input hook) and drains a ring
  of 64-byte records at each vsync, plus watched memory ranges.
- `probe_exp.py`: in-guest experiments (`kern`, `cdlayer`) called once from the
  game's main thread at `PadReadData_184df0`'s entry.
- `vucap.py` + `tests/vu/vu_replay.c`: VIFCAP1 frame captures and their replay.

Runs used (all with the golden input script and a fresh memory card; run
artifacts under `.tools/run/`, captures under `out/captures/`, both ignored):

| run | command (abridged) | for |
|---|---|---|
| p1 | `probe.py --hooks kernel,cd,sif,pad,vif1 --every 5 --stop-vbl 2700` | ids, SIF, pad, CDVD layer 0 |
| b1 | `probe.py --hooks kernel,pad,vif1 --watch padbuf:0x4B2A80:0x100 --exp kern --exp-at 1760` | kernel experiment |
| b2 | `probe.py --hooks cd --exp cdlayer --exp-at 1800` | CDVD layer 1 |
| A | `probe.py --hooks cd,vif1,movie,pad --watch ... --stop-vbl 25000` (speed 0.5) | movies, pad buffer, battle VU frames |
| C | `probe.py --hooks vif1 --speed 0.15 --vucap-at 1740/9000/24800 --vucap-frames 10` | VU captures |
| g7, g8 | `trace.py run` exactly as the README's golden command | determinism |

Probe runs change EE timing (extra instructions per hooked call), so they are
not lockstep references; they answer questions about behaviour.

---

## 1. CDVD layer-1 LSN (docs/CDVD.md)

**Question.** Does the game read `DATA1_*` (layer 1) at manifest LBA + 16, i.e.
does `sceCdLayerSearchFile(.., 1)` return LSN = image sector + 16, and does
`sceCdRead(lsn)` deliver image sector `lsn - 16` for `lsn >= L`?

**Method.** The golden run never leaves layer 0: the game selects the layer by
story "disc" (`CdDiscSelect_1c3090`, from `StateGetRequiredDisc_3d5ed0`), and
the first battle is on disc 1. So run b2 called the game's own
`CdDiscSelect_1c3090(1)` from the main thread at the title screen (experiment
`cdlayer`), with every `sceCdLayerSearchFile` (name, layer, returned
`sceCdlFILE`) and `sceCdRead` (lsn, sectors, buffer) logged. After the
experiment the harness dumped each read's EE buffer and compared it, 16-byte
row by row, with the ISO image at sector `lsn` and at `lsn - 16`.

**Result.** Confirmed.

| file (layer 1) | LSN returned by CDVDMAN | manifest LBA | difference |
|---|---|---|---|
| `DATA1_0.HD6` | 2,739,626 | 2,739,610 | +16 |
| `DATA1_0.DAT` | 2,740,173 | 2,740,157 | +16 |
| `DATA1_1.DAT` | 2,270,894 | 2,270,878 | +16 |
| `BIN/NORMAL.BIN` | 2,740,033 | 2,740,017 | +16 (CDVD.md's table value) |
| `BIN/TITLE.BIN`, `FACTORY`, `INSECT`, `INSMENU`, `LAUNCHER`, `VIEWER`, `RGSYS.DAT` | 2,740,156 / 2,739,803 / 2,739,879 / 2,739,999 / 2,740,032 / 2,740,172 / 2,739,802 | | +16 each |

Read buffers (fraction of 16-byte rows equal to the ISO):

| read | at image `lsn - 16` | at image `lsn` |
|---|---|---|
| lsn 3,329,438 x 20, 3,329,892 x 94, 3,332,196 x 512, 3,332,708 x 207 (layer 1, untouched buffers) | **1.000** | 0.031 / 0.193 / 0.002 / 0.009 |
| lsn 2,739,626 x 140 (`DATA1_0.HD6`; the game rewrites `\` to `/` and qsorts its table in place) | 0.565 | 0.000 |
| 31 movie-stream reads, lsn 62,366..62,670 (layer 0, untouched) | 0.000-0.08 | **1.000** |

Layer 0 is passed through (`sceCdReadDvdDualInfo` gave `on_dual` = 1; the game
read `DATA0_*` at their manifest LBAs: 999,686, 1,002,028, 999,814, 541,638).
Other buffers had been reused before the dump and match neither (ignored).

**Confidence.** High for the search arithmetic (it is CDVDMAN's own code) and for
the read mapping as PCSX2 implements it. The read mapping is PCSX2's drive model,
not hardware, but the game reads its layer-1 archives correctly through it.

**Module change.** None. `cdvd_disc.c` / CDVD.md's rule is right; the "Open
issues" entry can be closed with this evidence.

---

## 2. Kernel (docs/KERNEL.md "Open questions")

**Method.** (a) Run p1 logged every libkernl syscall stub for threads,
semaphores, INTC/DMAC handlers and alarms (arguments, the kernel's return value,
the caller, the stack pointer) from power-on to vbl 2700. (b) Run b1 executed the
`kern` experiment (`probe_exp.py`) inside the game at vbl 1769 on the main thread
(priority 20): it creates semaphores, threads and INTC handlers of its own with
the game's own syscall numbers, and logs events with COP0 Count. The game is
running normally around it.

### 2a. INTC handler return value (chain stop rule)

H1 added with `AddIntcHandler(2 /*VBLANK_START*/, H1, 0)`, H2 with `next = -1`
(libgraph's `GfxVblankStartHandler_15df20` was already in the chain, added by
`sceGsSyncVCallback` with -1). H1 returned 0, then 1, then -1, then 0, 6
VBlanks each.

| H1 returns | H1 runs | libgraph handler | H2 |
|---|---|---|---|
| 0 | yes (+0) | yes (+514 cycles) | yes (+895) |
| 1 | yes | yes | **yes** |
| -1 | yes | **no** | **no** |

`next = 0` inserts at the head, `-1` appends at the tail (call order
H1, libgraph, H2). **Result: the chain stops only on a negative return; 0 and
positive values continue.** (With -1 the game's own VBlank handler did not run at
VBLANK_START for those 6 fields.)

**Module change (kernel, `kirq.c`).** "Stops at the first non-zero return" ->
"stops at the first negative return". The movie handler returns 0, so the movie
case is unaffected; any handler that returns a positive value must not end the
chain. Confidence: high (real BIOS code, unambiguous).

### 2b. SignalSema at max count

| sema | operations | results |
|---|---|---|
| max 1, init 1 | `SignalSema` | returns the sema id (success) |
| | `ReferSemaStatus` | count = **2**, max = 1 |
| | `PollSema` x2 | both succeed (return the id) |
| max 2, init 0 | `SignalSema` x3 | all succeed; count = **3** |

**Result: the retail kernel does not cap: SignalSema at max succeeds and the
count exceeds max_count.** **Module change (kernel):** remove the cap / -1
failure; count is unbounded (at least past max). Confidence: high.

### 2c. Id numbering

From p1 (boot) and b1:

- **Threads:** main = 1; the first `CreateThread` returns 2, then 3, 4, ...
  Ids are **not** reused at once: after threads 10-13 were deleted, the next
  `CreateThread` returned 14 (then 15, 16, 17; later 18-21). Next-fit / monotonic
  (wrap point not reached).
- **Semaphores: the first id is 0.** Boot: libkernl/crt creates 0, 1, 2, ...
  Reuse is **last freed, first reused** (a free list): b1 created a, b, c = 36,
  35, 38 (36 had just been freed, 35 before it), deleted b (35), and the next
  create returned 35. Every sync SIF RPC's create/delete returns the same id.
- **INTC/DMAC handlers share one id space** 1..128, allocated next-fit and
  wrapping: boot gave INTC 1 (cause 11, `AddIntcHandler2`), DMAC 2, DMAC 3 after
  2 was removed, INTC 4, 5; the per-frame `Vif1DmaStart` add/remove then walked
  6, 7, ..., 128 and wrapped to 2, 6, 7, ... (skipping ids in use).

**Module change (kernel):** sema ids start at 0 and reuse the most recently
freed id; thread ids start at 2 for the first created thread and advance
without immediate reuse; handler ids are one shared next-fit counter over
1..128 for INTC and DMAC. The game stores sema ids and tests them with `>= 0`
(`FileSlotRead_180aa0`: `if (D_0047E028 >= 0) WaitSema(..)`), so id 0 must be a
valid id. Confidence: high for the observed sequences; the thread-id wrap point
and the exact free-list order beyond what was seen are not measured.

### 2d. Scheduling: preemption, queue position, equal-priority calls

Events in order (b1; M = main thread, prio 20; TA1, TA2 prio 20; TH prio 19):

1. `StartThread(TA1)` (equal priority): TA1 does **not** run; M continues.
2. `ChangeThreadPriority(M, 20)` (its own, unchanged priority): **TA1 runs before
   the call returns** (M is moved behind TA1).
3. `StartThread(TH)` (higher): TH runs at once and blocks in `WaitSema(S2)`.
4. `StartThread(TA2)`; M then spins 3 fields reading COP0 Count with **no
   syscalls**, while a VBLANK_START handler `iSignalSema(S2)`s.
   - TH ran 2,183 cycles after each VBLANK_START, **during M's spin**: an
     interrupt that readies a higher-priority thread preempts at the
     handler's return, not at the next kernel call.
   - After TH blocked again, **M resumed, not TA2**; TA2 ran only when M blocked
     after the spin. The preempted thread goes back to the **head** of its queue.

**Module change (kernel):**
- `ChangeThreadPriority` on the running thread to an equal priority **yields**
  (rotates it to the tail). KERNEL.md says it does not.
- Head-of-queue on preemption: **as modelled** (confirmed).
- Preemption point: retail switches right after the handler returns; the port
  delivers interrupts only at kernel-call entry and the defined points. That is
  a deliberate design limit (no EE cycle model), but it now has a measured
  consequence: code that spins on handler-set state without a kernel call
  sees the higher-priority thread run in between on retail. Keep the SPIN.md
  override list in mind; no change needed unless such a spin turns up.
Confidence: high for each observed event order (one run, deterministic
scheduler).

### 2e. EIE across a blocking syscall

M executed `di` (Status 0x70030C11 -> 0x70020C11), started TA3 (prio 20) and
blocked in `WaitSema(S3)`. TA3 ran with **Status 0x70020C11 (EIE = 0)**,
signalled S3 and slept; M woke with EIE = 0.

**Result:** M wakes with EIE = 0 (as modelled), **but the other thread also
ran with EIE = 0**: a new thread does not start with EIE = 1, and EIE is not
restored per thread on switch-in; the disable carried over to the next thread.
**Module change (kernel):** KERNEL.md's "EIE is per thread; new threads start with
EIE = 1" and "the scheduler delivers interrupts before every switch-in even when
the next thread had EIE = 0" contradict this. Retail behaves as if EIE is
global state that a context switch does not touch. Confidence: medium (one
observation; did not measure how long interrupts stayed off, or whether the
idle loop re-enables them).

### 2f. VBlank phase / start line

H1 on VBLANK_START and H3 on VBLANK_END logged COP0 Count for 23 fields:

- VBLANK_START period: mean 4,920,059 EE cycles (min 4,916,759, max 4,923,295;
  interrupt-latency jitter), i.e. the 4,920,120-cycle field.
- VBLANK_START -> VBLANK_END: mean **422,351** EE cycles (418,846-425,189) =
  **22.53 lines** of 262.5. Start line 240 predicts 22.5 lines = 421,725.

**Result:** consistent with the port's start line 240 and END at the field
boundary. **Module change:** none. Confidence: medium-high (±3k cycles of
handler-dispatch jitter, so ±0.3 line).

---

## 3. SIF: per-call semaphore in synchronous `sceSifCallRpc`

**Method.** Static: disassembly of `sceSifCallRpc` (0x11A4E8). Dynamic: run p1
logged every `CreateSema`/`DeleteSema` with its caller.

**Result: yes, one semaphore per synchronous call.** The retail code builds a
sema param with max 1, init 0 on the stack, `CreateSema` (call site 0x11A640,
return address 0x11A648), stores the id in `cd->hdr.sema` (+8), sends the
packet, `WaitSema`, then `DeleteSema` (0x11A6AC). In p1, 177,705 `CreateSema`
calls in 2,700 VBlanks, almost all from 0x11A648 and from `sceSifBindRpc`'s
0x11A38C, each followed by the matching `DeleteSema`; with the LIFO free list
the same id comes back every time (id 3 at boot, 7 later). A send failure
deletes the sema and returns -2; a CreateSema failure returns -3.

The SIF model's per-call sema matches. Its sema ids will match retail only once
the kernel adopts 2c (start at 0, last-freed-first). **Module change:** none in
SIF. Confidence: high.

---

## 4. Pad (docs/PADMC.md)

**Method.** p1/A logged `scePadRead`'s return value and the 24 bytes of
`PadReadData_184df0`'s stack buffer after the call, `scePadInfoMode`/`InfoAct`
args and returns, and watched the 256-byte pad DMA buffer at 0x4B2A80 (written
by the real padman on PCSX2's emulated IOP).

**Result.**

- **`scePadRead` returns 32 and copies 32 bytes** in analog mode 0x73 (1,145
  of 1,145 calls in p1). libpad copies `length` = the buffer's +0x60 field,
  which padman sets to **0x20**, not `2 + 2 x (id & 0xF)` = 8. The game's
  `u8 sp30[0x18]` is overrun by 8 bytes on retail (into unused frame padding
  at sp+0x48..0x4F of its 0x50-byte frame; harmless there).
- Data bytes: `00 73 ff ff 7f 7f 7f 7f` then zeros, and byte 31 = `5a`.
  (Sticks 0x7F at rest under PCSX2 with no input source.)
- DMA buffer (both halves, steady state):

| offset | bytes (PCSX2 / real padman) | port model (PADMC.md) |
|---|---|---|
| 0x20 actDirect | 00 x 8 | |
| 0x28 actAlign | 00 01 ff ff ff ff | {0,1,FF..} |
| 0x30 actData | act0 `01 02 00 0a`, act1 `01 01 01 14` | {1,0,1,50}, {1,1,8,100} |
| 0x40 | `02 00 01 00` | |
| 0x50 modeTable | 04 00 07 00 | {4, 7} |
| 0x58 frame | 0x5AC, 0x5AB (halves alternate) | |
| 0x60 length | **0x20** | 8 |
| 0x64..0x6B | 02 73 03 01 02 01 02 **01** | 2, id, 3, 1, 2, 0/1, 2, **0** |
| 0x6C | 00 01 03 00 | |
| 0x70 state, reqState, ok | 06 00 01 | 6, 0/1/2, 1 |

- **Which bytes InfoMode/InfoAct read** (disassembly of 0x12BCA0, confirmed by
  the values returned): both copy the newer half (`GetDmaStr`), require
  `ok` (+0x72) = 1 and reqState (+0x71) != 2 (BUSY). InfoMode: CURID = +0x65
  >> 4 (0 for 0xF3); CUREXID = 0 if modeConfig (+0x64) = 1, else
  modeTable[+0x69] (u16 at +0x50); CUREXOFFS = +0x69; TABLE: -1 -> nrOfModes
  (+0x68), i < nrOfModes -> u16 at +0x50 + 2i. Observed returns: InfoMode(1)
  = 7 (1,078 calls), InfoMode(2) = 4 while digital, InfoMode(4, -1) = 2,
  InfoAct(-1) = 2.

**Module change (padmc):** report length 0x20 for every mode (or at least for
0x73) and copy 32 bytes; give `numActComb` = 1, the actData above and the
trailing `5a`; and add the override PADMC.md anticipated: `PadReadData_184df0`'s
buffer must be at least 32 bytes on the host (the port's C buffer is 24 bytes,
so a 32-byte copy would overflow on i686). Confidence: high for the values
(real padman); `5a` and actData are padman's, not checked against hardware.

---

## 5. VU1/VIF1 capture and replay (docs/VU.md "Validation against PCSX2")

> **Update (applied):** the V3 W-lane rule is settled and implemented in
> `src/ps2/vif/vif.c` (docs/VU.md "V3 W lane"). **All 11 captures now replay
> with 0 wrong words**, VU1 code identical, only FMAC "close" words remain.
> The replay is registered in `tests/vu/CMakeLists.txt` as `vu.replay.v<vbl>`
> (skips with 77 without captures); the pass bar is now **wrong == 0**, and
> `vu.replay_control` flips a bit in the **last** UNPACK (first MPG on title
> frames), failing on all 11. The tables and "Module changes" below are the
> pre-fix record.

**Format.** VIFCAP1 as VU.md proposes, kinds 1 (VU1 state), 2 (VIF1
registers), 3 (VIF1 words), plus extensions: 5 = PCSX2's VU1 data memory at
the next vsync (expected result), 6 = metadata, 7 = PCSX2's VU1 code memory
at the next vsync. Kind 4 (GIF packets) is **not captured**: the GS dump needs
PCSX2's GUI hotkey, which the `-nogui` harness cannot send.

**How the data is obtained (observed, not from PCSX2 source).**
- The game kicks one VIF1 chain per rendered frame (`Vif1DmaStart_15e070`,
  every 2 VBlanks at 30 fps; buffers alternate 0x6B92C0 / 0x6E03C0 at the title),
  about 10,000 EE cycles after VBLANK_START; D1_CHCR = 0x70000045 (chain mode,
  **TTE = 1**: the tag's upper 64 bits go to the VIF). The VIF i-bit interrupts
  in the chain are released by `Vif1IntcHandler_15e170` (writes VIF1_FBRST.STC).
- Savestates: the zip holds `vu1Memory.bin`, `vu1MicroMem.bin`,
  `eeHwRegs.bin` (the 0x10000000 page) and, in `PCSX2 Internal Structures.dat`,
  the `vuMicroRegs` block: VU0 VF[32] at tag+48, VI as 16-byte slots at +0x200
  (VI16 status, 17 MAC, 18 clip, 20 R, 21 I, 22 Q, 23 P, 26 TPC), VU1's block
  0x5B6 bytes later. Two savestates at consecutive vsyncs are not obtainable:
  a request takes ~9 VBlanks to be serviced while running, and a PINE
  `save_state` issued while the CPU thread is frozen hangs PCSX2.
- So frames are read **live**: one savestate locates the same bytes in
  PCSX2's process (VU0 micro at the start of the logged "VU0/1 On-Chip
  Memory" block, VU1 micro +0x2000, VU1 data +0x6000; the VU register files
  in the exe image, VU1's 0x600 after VU0's; VIF1/D1 registers over PINE),
  then `--vucap-at` reads EE RAM, VU memory and registers at N consecutive
  vsyncs (speed 0.15 so the CPU thread idles every frame). `vucap.py build`
  pairs vsyncs k, k+1 that contain exactly one kick (COP0 Count + ~234,100 =
  EE cycle, from the savestate's `cpuRegs`), walks the chain from EE RAM at
  k+1 (also at k: "chain stable" = identical), and writes the file.
  Checks per capture: D1 idle at both vsyncs, chain identical at k and k+1.

**Captures** (run C, `python tools/trace/vucap.py build .tools/run/C.jsonl
--count-offset 234106 --out out/captures`): 11 frames in three scenes, each a
pair of consecutive vsyncs with exactly one kick, D1 idle at both ends.

| scene (game vbl) | chain | VIF words | MSCAL | MPG bytes | UNPACK qw | PATH1 packets | PATH2 bytes |
|---|---|---|---|---|---|---|---|
| title menu (1956, 1958, 1960, 1962) | 221 tags | 188,054 | 0 | 704 | 0 | 0 | 749,632 |
| in-engine cutscene, game mode 11 (9002, 9004, 9006, 9008) | 3,627-3,659 tags | 594,330-595,890 | 811-822 | 151,032-152,024 | 67,901-68,917 | 3,526-3,555 | 1.87 M |
| first battle, mode 7 (24804, 24806, 24808) | 9,092 tags | 1,950,248-1,950,648 | 2,224 | 336,800 | 181,994 | 7,894-7,950 | 6.55 M |

(The title draws through PATH2/PATH3 only; VU1 memory is all zero there. Frame
24802's chain could not be walked from the k+1 snapshot and was skipped.)

**Replay** (`tests/vu/vu_replay.c`, built standalone into
`out/vu-replay/rg-vu-replay.exe` from the current `src/ps2/vif` and
`src/ps2/vu` sources; it is not in `tests/vu/CMakeLists.txt`, see below):

| scene | stream consumed | runaways / invalid | XGKICK packets well-formed | VU1 code after frame | VU1 data after frame (4,096 words) | test |
|---|---|---|---|---|---|---|
| title x4 | all | 0 / 0 | - | identical | 4,096 exact | PASS |
| cutscene x4 | all | 0 / 0 | all | **identical** (2,048/2,048 pairs) | **4,006 exact, 16 close, 74 wrong** (of ~765 words PCSX2 changed) | FAIL |
| battle x3 | all | 0 / 0 | all | **identical** | **4,010-4,016 exact, 11-17 close, 69 wrong** (of ~870 changed) | FAIL |

"close" = same-sign floats within 16 ulp (VU.md caveat 1: the FMAC is not
bit-exact). **Every wrong word is a W lane** (component 3) of a qword whose
value PCSX2 left unchanged during the frame (before = after) while the port
wrote 0: the "V3 w = 0" guess in VU.md's table of undocumented cases. A local
experiment (not applied to `src/ps2/vif`) that writes, for V3-16/V3-8 unpacks,
W = the next component in the stream (the following element's X, 0 past the
end of the payload) cuts the wrong words to 18 (cutscene) and 37 (battle), all
still W lanes of V3 elements. The exact rule (which odd/even elements get the
next component and which get 0 or keep the old value) is not settled; the
captures are there to settle it. All X/Y/Z lanes, every MPG upload and the
results of 811-2,224 microprogram runs per frame match PCSX2 to within float
tolerance.

Controls: `--control` flips one bit of the first UNPACK (title: MPG) payload
word; it FAILs on all 11 captures (title via one differing code pair, the
others via data words), so the comparison is armed.

**Confidence.** High that the VIF/VU1 interpreter reproduces PCSX2's VU1 state
for these frames apart from V3's W lane. Limits: no GIF output comparison
(kind 4 missing), so XGKICK packet contents are only checked structurally;
PCSX2's VU is itself not bit-exact against hardware; the VU1 register file at
frame start comes from a live read whose layout (VU1 = VU0 + 0x600) was
matched against a savestate by its VI values (`0x3FE 0x8001 0x78 0x1B 0x400
0xB9` in both), not by an exact-instant comparison.

**Module changes.**
- **VU/VIF (`src/ps2/vif/vif.c`, docs/VU.md):** V3 unpacks must not write
  W = 0. Start from "W = next stream component" and refine against
  `out/captures/C_v09002.vifcap` / `C_v24808.vifcap`
  (`rg-vu-replay --verbose` lists the words).
- **tests/vu/CMakeLists.txt (owner: VU):** add the replay as a test that skips
  without a capture, e.g.
  `add_executable(rg-vu-replay vu_replay.c)` +
  `target_link_libraries(rg-vu-replay PRIVATE rg_ps2_vif rg_flags)` +
  `add_test(NAME vu.replay COMMAND rg-vu-replay)` with
  `ENVIRONMENT RG_VIFCAP=<capture>` and `SKIP_RETURN_CODE 77`, plus a
  `WILL_FAIL` `vu.replay_control` with `--control`.
- To get kind 4 (GIF packets), the harness would need PCSX2's GS dump; that
  needs the GUI hotkey (not scriptable with `-nogui`). Not done.

---

## 6. Movie audio/video clock (docs/MVI.md open issue)

**Method.** Run A watched the movie player state every 5 VBlanks
(`D_004B3218` displayed-frame count via `MovieGetFrameCount_1d52d0`; the audio
decoder at `D_004B32D0`: +0x54 = bytes sent to the IOP sound buffer, +0x4C IOP
write position, +0x48 = 24,576-byte IOP ring) and logged every
`MovieFrameQueueSendNext_1d4b20`. The golden plays `01/01_01.MVI` (29.97 fps,
48,048 Hz, 2,233 frames) from vbl 3,881 until CROSS skips it at vbl ~8,160, and
`00/TITLE01`, `TITLE02` (30 fps) at the title. Time base: the game VBlank
counter at 59.94 Hz (PCSX2's 294,912,000 / 4,920,120).

**Result (01_01, 580 samples over 67.8 s):**
- Video: **0.500014 frames per VBlank** = 29.971 fps. Frames advance exactly one
  per two VBlanks, independent of audio (no frame drops, `D_004817A0` miss
  counter stayed 0).
- Audio: bytes sent to the IOP grow at **191,999.9 B/s = 47,999.97 stereo
  samples/s**, residual ±530 bytes over the whole span. 48,048 Hz consumption
  would add 13,000 bytes over the span; ruled out. The IOP buffer is refilled to
  its level as SPU2 drains it, so this is the SPU2 playback rate.
- TITLE02 (2.5 s segment): 47,995-48,025 Hz, 29.966 fps (short, noisy; same
  picture).

**Conclusion.** The player does not resync video to audio. Video is paced by
VBlank (2 fields per frame), audio plays at the SPU2's fixed 48,000 Hz. For the
48,048-Hz 29.97-fps movies the audio therefore runs 0.1% slow against the
picture and drifts late by 1 ms per second (75 ms by the end of `01_01`,
0.33 s over `97/01_14`); 30-fps content is shown at 29.97 fps, 0.1% slow, in
step with its 48,048-Hz audio at 48,000 Hz.

**Module change (movie, P4).** To be faithful: present one decoded frame per two
VBlanks (59.94 Hz / 2) and play the WAV's samples at 48,000 Hz regardless of the
header's 48,048 (i.e. resample 48,048 -> 48,000 by rate, not by time), keeping
the movie end/skip tied to the frame counter. Playing at the header rate is the
"fixed" alternative, but then audio leads the retail timeline by 0.1%.
Confidence: high for the rates; whether real SPU2 hardware runs at exactly
48,000 Hz relative to the GS 59.94 Hz clock is PCSX2's model (both derive from
the same crystal on hardware, so the ratio should hold).

---

## Determinism re-check (README "Determinism")

Three more full golden runs (power-on -> first battle, 25,320 frames, the
README's exact command):

| run | conditions | vs `goldens/newgame_battle.tsv` |
|---|---|---|
| g7 | in parallel with g8 and probe runs | **identical on all 270 common emitted frames (120..25320)** |
| g9 | in parallel with one long-running probe run (C), no other launches during it | **identical on all 282 common frames (240..25320)**; g7 vs g9 identical on 307 |
| g8 | started 25 s after g7; a probe instance (p1) was launched about 60 s into g8 | **diverged at frame 1020** (vbl 740): `@cycle` of that vsync and the 4 MB EE chunks first; first symbol difference at vbl 3860 (`GameScene`); game-mode timeline then 1 frame late (mode 11 at 4151 vs 4150) |

So with the hook installed frozen, 4 of 5 long runs (g5, g6, g7, g9) are
identical to the golden across vbl ~22,000-25,040, which strengthens the
README's claim past vbl 22k. The one divergence (g8) is early (frame 1020), not
in the late window the README worried about, and coincides with another
PCSX2 instance starting up while g8 was in its memory-card check (all portable
instances share `.tools/pcsx2/inis/PCSX2.ini`, which every launch rewrites with
its own memory-card name and PINE slot, and the shader cache: g8's log has
"Failed to open shader cache index with EACCES, are you running two
instances?"). The cause is not proven. **Harness rule adopted (tools/trace
README):** do not launch another portable PCSX2 while a reference trace is
before vbl ~3,000; for parallel reference runs start them together and launch
nothing else. Confidence: high that a quiet host reproduces the golden through
the first battle; medium on the g8 cause.
