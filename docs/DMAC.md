# DMA controller model and the graphics SDK surface

PLAN.md P3 ("DMA/VIF1 path"). Two layers:

- `src/ps2/dmac/`: a model of the EE DMA controller. It covers the ten channels, their
  registers and the global registers, source chain, destination chain, normal and
  interleave modes, and the scratchpad.
- `src/sce/graphics/`: the libdma, libgraph and libpkt functions the game calls, built on
  the DMAC, VIF, VU and GS models.

Everything was written from public descriptions of the EE DMAC (the EE User's Manual's
register and DMAtag semantics), the retail asm bodies in `game/`, and the game's own call
sites. No emulator code was used (PLAN.md D7).

| Path | What |
| --- | --- |
| `src/ps2/dmac/dmac.[ch]` | DMAC model (`dmac_*`), CMake target `rg_ps2_dmac` |
| `src/sce/graphics/libdma.[ch]` | `sceDma*` and the SDK binding `sce_graphics_bind` |
| `src/sce/graphics/libgraph.[ch]` | `sceGs*` |
| `src/sce/graphics/libpkt.[ch]` | `sceGifPk*` |
| `src/sce/graphics/graphics_game_names.c` | the game-tree symbol names (`sceDmaSend_10a040`, ...) |
| `tests/dmac/` | `rg-dmac-tests`, CTest label `dmac` |

CMake targets: `rg_ps2_dmac`, `rg_sce_graphics`, `rg-dmac-tests`.

## Wiring

```c
dmac_state *d = dmac_create();          /* host memory mode, bound to the kernel */
gs_state *gs = gs_create();
vu_init(&vu1, 1); vif_init(&vif1, 1, &vu1);
vu1.gif_sink  = gs_vu1_gif_sink;  vu1.gif_user  = gs;   /* PATH1 */
vif1.gif_sink = gs_vif1_gif_sink; vif1.gif_user = gs;   /* PATH2 */
dmac_attach_vif(d, 1, &vif1);           /* also VIF0: dmac_attach_vif(d, 0, &vif0) */
dmac_attach_gs(d, gs);                  /* GIF -> PATH3, VIF1 readback <- GS */
dmac_set_out(d, DMAC_SIF1, sif_sink, sif);   /* SIF/IOP agent */
dmac_set_in(d, DMAC_SIF0, sif_source, sif);
sce_graphics_bind(d, gs);               /* before the game's first SDK call */
```

| Ch | Name | Direction | Modes | Bound to |
| --- | --- | --- | --- | --- |
| 0 | VIF0 | to VIF0 | normal, source chain (TTE) | `vif_write(vif0)` |
| 1 | VIF1 | to VIF1 (DIR=1) / from VIF1 (DIR=0) | normal, source chain (TTE) | `vif_write(vif1)`; readback `gs_read_fifo` |
| 2 | GIF | to GS | normal, source chain | `gs_gif_write(PATH3)`, held while VIF1 has PATH3 masked |
| 3 | fromIPU | to memory | normal | `dmac_set_in` (movie service) |
| 4 | toIPU | from memory | normal, source chain | `dmac_set_out` (movie service) |
| 5 | SIF0 | to memory | normal, destination chain | `dmac_set_in` (+ `dmac_set_start`) |
| 6 | SIF1 | from memory | normal, source chain (TTE) | `dmac_set_out` |
| 7 | SIF2 | either (DIR) | normal | `dmac_set_out` / `dmac_set_in` |
| 8 | fromSPR | scratchpad to memory | normal, destination chain, interleave | internal 16 KB scratchpad |
| 9 | toSPR | memory to scratchpad | normal, source chain, interleave | internal 16 KB scratchpad |

Peripheral callbacks:

- **Out:** `dmac_out_fn(user, ch, data, bytes, flags)`. It gets the exact byte stream in
  transfer order. `flags & DMAC_OUT_TAG` marks the 8 bytes that are a DMAtag's upper
  half (TTE).
- **In:** `dmac_in_fn(user, ch, dst, bytes)`. It returns the bytes it produced, in whole
  qwords. A short return holds the channel until `dmac_service()`.
- **Start:** `dmac_start_fn(user, ch)`. It runs when a to-memory channel starts, so the
  IOP or IPU side knows the EE is ready. It may produce data from inside the call.
- **SIF0 destination chain:** each tag is a whole qword from the source, with the EE
  DMAtag in its low 64 bits.
- **Unbound channels:** an out channel with nothing bound drops its data, prints one
  message, and counts the data in `stats[ch].unbound_qwords`. An in channel with nothing
  bound holds.

## Timing model

- **Transfers are synchronous.** A transfer runs inside the call that starts it:
  - `sceDmaSend` and the other libdma kicks;
  - a CHCR store with STR=1 through `dmac_hw_write32` or `dmac_write_chcr`;
  - a FIFO write, D_CTRL/D_ENABLEW write or `dmac_service` that releases a held channel.

  When that call returns, CHCR.STR already reads 0, the data has gone all the way through
  (VIF → VU program run → XGKICK → GS raster, or GIF → GS), and D_STAT.CIS is latched.
- **Virtual time.** The transfer is then charged to the virtual clock: one
  `ps2k_charge(qwords × cycles_per_qword)` per outermost call. The count includes tags,
  and the default is 1 bus cycle per qword, the DMAC's peak rate.
  - The charge is a kernel delivery point. So a DMAC or VIF handler runs at "kick time +
    cost", inside the kicking call.
  - A higher-priority thread readied by that handler preempts the kicker there.
  - Cost incurred in handler context, or outside a guest thread, is not charged. It goes
    into `uncharged_cycles`.
- **Why synchronous:** the recomp's measurements (memory notes `dma-kick-blocks-guest`,
  `async-dma-scoping`) found that the game polls CHCR.STR right after every kick, so
  there is no guest work for an asynchronous DMAC to overlap.
- **Holds.** A channel is held (STR stays 1, nothing moves) only while one of these is
  true. Each hold resumes on the event named:

  | Hold | Resumes when |
  | --- | --- |
  | D_CTRL.DMAE = 0, or D_ENABLEW.CPND = 1 | that register is written back |
  | GIF while VIF1 MSKPATH3 is set | a VIF1 DMA, VIF1 FIFO write or VIF1 reset clears the mask |
  | An in channel whose source returned short | `dmac_service()` |

  libdma never spins on a held channel. `DmaWaitChannelIdle` first runs held work. A
  channel that is still held is then reported and stopped (STR cleared), which is what
  retail does after its 16M-poll timeout.
- **No silent truncation.** Chains are capped at `max_tags` = 2^24 tags per kick (the
  recomp's 4096 cap truncated a real 4,125-tag list; memory note `dma-chain-tag-cap`).
  Hitting the cap prints `chain TRUNCATED`.

## Address mapping

The game's pointers are host pointers in the i686 build. DMA addresses (MADR, TADR, ASR,
tag ADDR) are 32-bit, and bit 31 is the scratchpad flag (tag bit 63).

| Address | `DMAC_MEM_HOST` (default; the game) | `DMAC_MEM_GUEST` (tests, PS2 captures) |
| --- | --- | --- |
| bit 31 set | scratchpad `spr[addr & 0x3FF0]` | same |
| `0x7xxx_xxxx` | host pointer | scratchpad (raw SPR window) |
| `0x2xxx_xxxx`, `0x3xxx_xxxx` | host pointer, no stripping | uncached / UCAB mirror: stripped to physical |
| `0x0xxx_xxxx` | host pointer | `ram[phys & ~15]`, bounds-checked |
| below 64 KB, `0x1xxx_xxxx` (guest) | bus error | bus error |

- **Why the two modes can't be told apart automatically:** the Windows i686 executable
  loads at 0x0040_0000, inside the PS2's 32 MB range. So a host pointer and an EE
  physical address can look identical.
- **What host mode depends on:**
  - The exe must not be `/LARGEADDRESSAWARE`. A tag's ADDR field is 31 bits, and bit 31
    means scratchpad.
  - Transform 5 (address literals) must turn `0x2000_0000|p`, `0x3000_0000|p` and
    `p & 0x0FFF_FFFF` on host pointers into plain `p`. The sites found here:
    - `GsUploadImage16Blocks_1d27a0` builds its packet at
      `((u32)dst & 0x0FFFFFFF) | 0x20000000`.
    - The same function passes `(u32)src & 0x0FFFFFFF` to `sceGifPkRef`.
- **Scratchpad pointers.** The game's scratchpad pointers (`PS2_SPR(off)` after
  transform 5) should point into `dmac->spr`. `sceDmaSend` and the other address
  arguments go through `dmac_canon_addr`: a pointer into `spr` becomes
  `0x8000_0000|offset`, as `DmaAddrFromSpr` does for `0x7xxx_xxxx`.
- **Bus errors.** A bad address sets D_STAT.BEIS, stops the channel and prints. It
  never crashes the host.
- **Low address bits.** Guest mode clears the low 4 address bits, as the hardware does.
  Host mode keeps them, so a host buffer that is only 8-aligned is still read correctly.
- **Scratchpad wrap.** The scratchpad side wraps at 16 KB (SADR, and SPR addresses in
  chains).

## Chain semantics

Source chain (`MOD=1` on VIF0, VIF1, GIF, toIPU, SIF1, toSPR):

| Tag | Data | Next tag |
| --- | --- | --- |
| REFE (0) | `ADDR` | ends |
| CNT (1) | after the tag | after the data |
| NEXT (2) | after the tag | `ADDR` |
| REF (3), REFS (4) | `ADDR` | after the tag |
| CALL (5) | after the tag | `ADDR`. Pushes the address after the data to ASR0, then ASR1. CHCR.ASP counts the entries. |
| RET (6) | after the tag | pops ASR1, then ASR0; with ASP=0 the chain ends |
| END (7) | after the tag | ends |

- **Start.** A kick first moves MADR/QWC data, if QWC > 0, then reads the tag at TADR.
  `sceDmaSend` sets QWC=0.
- **CHCR bits 31:16** take bits 31:16 of each tag's first word (the TAG field).
- **IRQ.** With CHCR.TIE set, a tag's IRQ bit ends the transfer after that tag's data.
  Without TIE, the bit is ignored.
- **Errors.**
  - A third nested CALL (ASP already 2) stops the channel and sets BEIS. The hardware
    behaviour is undocumented.
  - REFS does not stall. Its stall source has already run to completion, because every
    transfer is synchronous. D_STADR is still written by the STS source channel.
- **TTE.** With CHCR.TTE set, the tag's upper 64 bits go to VIF0, VIF1 and SIF1 ahead of
  the data, which is the VIF contract in `vif.h`. On GIF, toIPU and toSPR, TTE is
  ignored and counted in `stats.tte_ignored`.
  - The evidence: `FixedTexUploadImpl_15d680` sets TTE on the GIF channel. Its libpkt
    tags would corrupt the GIF stream if they were sent as data.
  - Unverified for toSPR.
- **After the last tag:**
  - REFE leaves TADR at the tag + 16.
  - CNT and NEXT leave TADR at the next tag.
  - END leaves TADR at the END tag.
  - RET with ASP=0 leaves TADR after its data.

  None of these values is read by the game, and none is verified.

Destination chain (`MOD=1` on SIF0 and fromSPR): each tag is read from the source (the
`in` callback, or the scratchpad at SADR). MADR = ADDR and QWC are taken from the tag.
CNTS (0) and CNT (1) continue, END (7) ends, and IRQ+TIE ends. Any other id is treated
as CNT and reported.

Interleave (`MOD=2`, SPR only) moves TQWC qwords, then skips SQWC qwords on the memory
side, until QWC runs out. Both values come from D_SQWC.

Not modelled: MFIFO (D_CTRL.MFD; a warning is printed once and the transfers run plain),
the stall that REFS and the drain channel do on D_STADR, D_PCR priority and CPCOND0
(stored only), the release cycle (stored only), and VIF0/GIF FIFO back-pressure.

## Interrupts and D_STAT

- **CIS and CIM** (bits 0-9 and 16-25) live in the kernel (`ps2k_raise_dmac`,
  `ps2k_hw_read32(D_STAT)`), which delivers DMAC handlers (KERNEL.md).
- **SIS, MEIS and BEIS** (13-15, write 1 to clear) and **SIM and MEIM** (29-30, write 1
  to toggle) live in the DMAC.
- **Reads and writes.** `dmac_hw_read32(D_STAT)` merges the two sets of bits.
  `dmac_hw_write32(D_STAT)` splits a write between them.
- **The `HW_*` accessor must ask `dmac_hw_claims` before `ps2k_hw_claims`.** Both claim
  D_STAT, and the DMAC forwards the kernel's part.
- **Without the kernel** (`d->kernel = 0`, used by tests), the DMAC keeps CIS and CIM
  itself and delivers nothing.
- **VIF i bit.** It raises INTC VIF0 or VIF1 through `vif->irq_fn` (set by
  `dmac_attach_vif`).
  - **Raised inside a DMA kick, it is posted after the kick** (`vif_irq_deferred`,
    `ps2k_post_intc(.., 1)` once the kick is charged): the kicking code runs on, as
    the EE does while the chain is in flight, and the handler runs at the next
    advance of the virtual clock. `GfxEndFrame_141c20` kicks the frame's VIF1 chain and
    then zeroes T0; delivered inside the kick, `Vif1IntcHandler_15e170`'s T0 sample
    (`D_004810B4`) read the whole interval and the frame-time feedback `+0xF10` was
    2.0038 on every tick (TIMING-LOCKSTEP.md). A CPU write to the VIF FIFO still
    raises at once.
- **The VIF does not stall on the i bit.** On hardware it stops until the CPU writes
  VIF1_FBRST.STC. The game's `Vif1IntcHandler_15e170` does that, and it also signals the
  frame semaphore. Here the stream continues and the interrupt stays latched, so
  delivery happens at the next delivery point.
  - This matters because `Vif1DmaStart_15e070` kicks the list before it installs and
    enables the INTC 5 handler. The kernel's level-held STAT bit is what delivers it
    later.
- **GS interrupts.** `dmac_attach_gs` routes `gs->irq` (SIGNAL/FINISH/VSINT, filtered by
  IMR) to INTC GS when nothing else claimed it.

## FIFO windows

These are for the `HW_*` accessor's 128-bit FIFO stores and loads, and are used by
libgraph:

- `dmac_vif_fifo_write(d, which, qwords, n)` covers 0x10004000 and 0x10005000. After a
  VIF1 write, a GIF channel held by MSKPATH3 resumes if the mask was cleared.
- `dmac_gif_fifo_write` covers 0x10006000.
- `dmac_vif1_fifo_read` reads GS→EE data.
- `dmac_vif_reset` covers VIF FBRST.RST, which clears MSKPATH3.

The VIF1 FIFO route is the fix for the recomp's post-gate display freeze (memory note
`post-gate-display-freeze`). `sceGsExecStoreImage` releases MSKPATH3 by writing
`MSKPATH3(0)` to the VIF1 FIFO.

## SDK surface (`src/sce/graphics`)

**What is implemented.** The census (`census/platform_sdk_surface.tsv`) lists 6 libdma,
13 libgraph and 11 libpkt boundary functions. All of them are implemented, with the
retail register sequence and return values.

**The SDK binding.** `sce_graphics_bind(dmac, gs)` chooses the DMAC and GS the SDK
functions use. VIF1 comes from `dmac->vif[1]`.

**Game names.**
- The game-tree names of the asm-bodied units are in `graphics_game_names.c`:
  `sceGsResetGraph_108110`, `sceGsSetDefDispEnv_1083c8`, `sceGsSyncPath_109030`,
  `sceGsSyncVCallback_109b18`, `sceDmaSend_10a040`, `sceGifPkTerminate_10a420`,
  `DmaWaitChannelIdle_109bb8`, and the unreached `sceDmaSendN/Recv/RecvN/Pause/Restart_*`.
- Units whose game name is the SDK name (`sceGsPutDispEnv`, `sceDmaGetChan`,
  `sceGifPkCnt`, ...) are defined once.
- `sceDmaSync_10a2e0`, `sceGifPkInit_10a400`, `sceGifPkReset_10a410` and
  `sceGsGetGParam_1082a0` have C bodies in the game tree, so they are compiled from
  there. The SDK names `sceDmaSync`, `sceGifPkInit` and `sceGifPkReset` exist here for
  the tests and other host code.

**Signatures follow the game's declarations where they differ from Sony's headers.**
For example, `sceGifPkRef(pk, u64 addr, ...)` and `sceGifPkOpenGifTag(pk, rg_u128)`
pass by value under cdecl.

| Function | Behaviour here |
| --- | --- |
| `sceDmaReset(mode)` | Clears channels 0-4, 8 and 9, clears D_STAT CIS and masks except the SIF channels, and calls PutEnv(0). Mode 1 sets DMAE. Returns the old DMAE. |
| `sceDmaPutEnv` / `GetEnv` | D_CTRL STS/STD/MFD from the retail channel→field tables. RCYC is written only when `rcycle != 0`. D_PCR, D_SQWC, D_RBOR and D_RBSR. Returns -1..-4 for a bad field. |
| `sceDmaGetChan(id)` | `&dmac->ch[id]`, the live register block (`sceDmaChan` layout: the game sets TTE through it). Returns NULL for id > 9. |
| `sceDmaSend(ch, tag)` | Waits idle, sets TADR (unless TADR == -1, as retail does), QWC=0 and `CHCR = (CHCR & ~0xD) \| 0x105`. Returns that CHCR value. |
| `sceDmaSync(ch, mode, t)` | Mode 1 returns STR (a busy answer lets 32 cycles pass). Otherwise it waits idle and returns 0. |
| `sceGsResetGraph(mode, ...)` | Mode 0: GS reset, GParam, IMR 0xFF00, removes the SyncV callback, SetGsCrt (SMODE2 INT/FFMD). Mode 5: GParam + SetGsCrt. Mode 1: CSR.FLUSH. The odd returns are retail's. |
| `sceGsResetPath` | Resets VIF1 and VU1 registers, then writes the retail VIF init qwords (STCYCL 4/4 ... ITOP 0) to the VIF1 FIFO. |
| `sceGsSetDefDispEnv` | Retail packing: PMODE 0x66, SMODE2 1/2/3, MAGH = (w+2559)/w, NTSC/PAL/DTV origins, DH = 2h-1 in FRAME mode. GetGsDxDyOffset reads as 0. |
| `sceGsPutDispEnv` | PMODE, SMODE2, DISPFB2, DISPLAY2, BGCOLOR (circuit 1 + EXTDATA on GS revision 1). |
| `sceGsSetDefDrawEnv`, `SetDefClear`, `zbufaddr`, `SetDefDBuff` | Retail bit packing, including the read-modify-write of PRMODECONT, COLCLAMP and DTHE, and the field-mode FBP adjust. They return 8, 6, (pages) and void. |
| `sceGsPutDrawEnv(tag)` | A GIF normal-mode kick of NLOOP+1 qwords. Returns 0, or -1 if the GIF is stuck. |
| `sceGsSwapDBuff(db, id)` | PutDispEnv + PutDrawEnv. Returns the PutDrawEnv result. |
| `sceGsSyncV(mode)` | **Blocks** until the next VBLANK_START (below). Returns CSR.FIELD when interlaced, else 1. |
| `sceGsSyncVCallback(f)` | `AddIntcHandler(2, f, -1)` + `EnableIntc(2)`, or removes the handler for NULL. Returns the old function. |
| `sceGsSyncPath(mode, t)` | Mode 0 returns 0, or -1 with retail's diagnostics if a VIF1/GIF channel is still held, VIF1 is mid-command or a GIF path is mid-packet. Any other mode returns the busy mask (1 VIF1 DMA, 2 GIF DMA, 4 VIF1, 8 VU1 (never), 0x10 GIF path). |
| `sceGsSetDefStoreImage` | Retail struct: NOP, MSKPATH3(1), FLUSHA, DIRECT 6 + 5 A+D. Returns 7. |
| `sceGsExecStoreImage(sp, dst)` | The full retail algorithm, described below. Returns 0 or -1. |
| `sceGifPk*` | Exactly the words the retail bodies write (Terminate's QWC fix-up, CloseGifTag's NLOOP by FLG/NREG, RefLoadImage's 0x7FFF-qword IMAGE slices). The one exception: in host mode, `sceGifPkRef` does not apply retail's `& 0x9FFFFFFF` to the address, because that would corrupt a host pointer. |

`sceGsExecStoreImage`, step by step:

1. Works out the transfer size per PSM. When the image is not a whole number of qwords,
   it pads the height: CT32 to 4 rows, CT24 to 16, 16-bit/T8/T4 to 8. It writes the
   padded TRXREG back into the struct.
2. Masks FINISH and clears it. Sends the 7 qwords over VIF1.
3. Reads the image: the multiple-of-8 qwords by VIF1 to-memory DMA, the rest through
   the VIF1 FIFO, then the partial qword. It discards the padding.
4. Restores IMR and BUSDIR, and writes `MSKPATH3(0)` to the VIF1 FIFO.

**Not in the census** (the game never calls them):

- `sceGsSetDefLoadImage` and `sceGsExecLoadImage` are implemented from SDK semantics,
  not checked against retail. `SetDefLoadImage`'s return value of 6 is a guess.
- `sceGsSetHalfOffset` and the `sceVif1Pk*` family are not implemented. The game does not
  link them.

### sceGsSyncV

- **Retail busy-waits.** `VSync_116a30` polls INTC_STAT.
- **SPIN.md requires a block.** Lower-priority threads then run, and the kernel's idle
  jump (and the pacing hook) sees the wait.
- **How it blocks:** `ps2k_wait_vblank()`, a kernel-private wait (KERNEL.md
  "Platform glue"). It takes no semaphore or alarm id, and the thread is readied after
  the next VBLANK_START's handlers and the alarms due with it, so the game's
  VBLANK_START handlers have run when the thread wakes. (Until 2026-10-12 it armed a
  cycle alarm on a private semaphore, which took a game-visible id.)
- Called outside a guest thread, or in a handler, it returns without waiting and prints
  once.

## Deviations and open questions

1. **Resolved 2026-10-12:** `sceGsSyncV` uses `ps2k_wait_vblank` and takes no id.
   Formerly: **the private SyncV semaphore took a game-visible id** during the wait. A semaphore
   another thread creates meanwhile gets a different id than on retail.
   `DelayThread` has the same property, but there it is retail behaviour. A kernel-private
   wait (requested below) would remove it.
2. **`CSR.FIELD` toggles only if someone calls `gs_vsync`** at VBLANK_START. The
   runtime's VBlank observer does, every field (RUNTIME.md). The game ignores `sceGsSyncV`'s return value.
3. **VIF i bit without stall, and REFS without stall** (see above).
4. **The GIF reset in `sceGsResetPath` / `ExecStoreImage` error paths** now calls
   `gs_gif_reset` (path state only). Formerly it had no separate effect. The GS model has no GIF-only reset, and its paths are idle between whole
   packets.
5. **`GsPutIMR`'s return value.** `ExecStoreImage` restores the IMR it read. Retail
   restores `GsPutIMR`'s return value, which is presumably the old IMR (unverified).
6. **Unverified hardware details:** TTE on GIF/toSPR, TADR after END/RET, a third nested
   CALL, and destination tag ids other than CNT/CNTS/END. They need a PCSX2 trace of a
   real chain (the VIFCAP format in VU.md would carry it).

## Requests for other modules (not changed here)

Done 2026-10-12 (RUNTIME.md "Changes made to other modules"): the kernel-private wait
and the VBLANK_START observer, the start-line accessor, and `gs_gif_reset`. The list
below is kept as it was written.

- **kernel:**
  - A `ps2k_wait_vblank()` (or kernel-private wait object) for `sceGsSyncV`, so that it
    does not consume a semaphore id.
  - A VBLANK_START observer hook, so the platform can call `gs_vsync` (CSR.FIELD,
    VSINT) on every field, not only when the game is waiting.
  - The DMAC currently predicts VBLANK_START with the default start line 240. Exposing
    the configured line, or the next VBLANK_START time, would remove the hsync-step
    fallback.
- **HW accessor (transform 5):** route 0x10008000-0x1000E06F, D_ENABLER/W and the VIF/GIF
  FIFO windows to `dmac_hw_*` / `dmac_*_fifo_*`, **before** the kernel for D_STAT.
  VIF1_FBRST.RST should call `dmac_vif_reset(d, 1)`.
- **Prototype unification (transform 2):**
  - `sceDmaSync_10a2e0.c` declares `DmaWaitChannelIdle_109bb8(void)`, so the channel
    argument is not passed under cdecl. The binding ignores anything that is not a
    channel block, which is safe because transfers are synchronous, but the declaration
    should take `sceDmaChan *`.
  - Game declarations of `sceGifPkRef` (`u64` address) and `sceGifPkOpenGifTag`
    (`u128`) must stay as they are. The implementations match them.
- **GS:** a GIF-only reset (`gs_gif_reset`) that drops path tag state without touching
  registers, for `GIF_CTRL.RST`.

## Tests (`tests/dmac`, `ctest -L dmac`)

| Test | Checks |
| --- | --- |
| `chain_tags` | Every source tag type in one chain: CNT, NEXT, REF, REFS, nested CALL→CALL→RET→RET, REFE. It checks the exact order of data and TTE halves, and the final CHCR/MADR/TADR/ASP/TAG. Also: END and RET(ASP 0) ending, IRQ with and without TIE, a third-CALL overflow (BEIS), a scratchpad REF that wraps at 16 KB, uncached/UCAB mirrors (guest mode), and a bus error. |
| `normal_spr` | Normal mode. toSPR/fromSPR. SPR interleave (TQWC 2 / SQWC 1). fromSPR destination chain with D_STADR. DMAE=0 and D_ENABLEW.CPND holds and their release. CHCR through `dmac_hw_write32`. |
| `dstat_interrupts` | D_STAT without the kernel (CIS w1c, CIM/SIM toggles). With the kernel: a DMAC handler runs inside the kick, exactly 100 cycles are charged for 100 qwords, a masked channel's CIS stays latched and is cleared by w1c, and a VIF1 i bit → INTC 5 handler, run after the kick once time advances. |
| `mskpath3` | A GIF kick is held while VIF1 has PATH3 masked. It resumes on a VIF1 FIFO `MSKPATH3(0)`, and on a VIF1 reset. |
| `sif_ipu_hooks` | SIF1 source chain with TTE halves. A re-entrant sink (no duplicate data). GIF ignores TTE. SIF0 destination chain from a source that starts empty, delivers half a qword, then completes. toIPU/fromIPU. An unbound channel drops data instead of hanging. |
| `vif1_vu1_retail` | Guest mode with the retail ELF loaded at its EE addresses. One VIF1 chain does five CALLs into the retail RET-tagged MPG packets (four second-level pieces + head 0x441660), REF-UNPACKs a synthetic batch, then MSCAL 0x320 + 2 × MSCNT. The retail code lands at VU1 0x320 byte-exact. XGKICK packets reach the GS on PATH1 and draw: 2 primitives, 1,004 pixels, and non-zero VRAM. Skipped (77) without the ELF. |
| `path3_storeimage` | Uploads through libpkt (`sceGifPkRefLoadImage`) + GIF chain DMA with TTE set, as `FixedTexUploadImpl` does. Then `sceGsSetDefStoreImage` + `sceGsExecStoreImage` round trips for CT32 64x32 (all DMA), CT32 6x5, CT24 5x3, CT16 10x3 and T8 24x9 (the FIFO, partial-qword and padded-height paths). Checks byte equality, no overrun, MSKPATH3 released, IMR/BUSDIR restored and the readback FIFO drained. Also `sceGsExecLoadImage`. |
| `libgraph_env` | `sceDmaReset`/`PutEnv` D_CTRL fields. The game's `ResetGraph(0,1,2,1)` + `SetDefDBuff(CT32 640x448, Z24, clear)`: every DISPLAY/FRAME/ZBUF/XYOFFSET/SCISSOR/TEST/GIFtag/clear word against hand-computed values. `SwapDBuff` lands the draw env in the GS registers and clears exactly 640×448 pixels. Field-mode zbufaddr/FBP. |
| `syncv_blocking` | Under the kernel, 6 × `sceGsSyncV` each return after exactly one VBLANK_START, no earlier than its time, and within 1,000 cycles of it. A priority-50 thread runs during every wait, which proves it blocks rather than spins. The semaphore id is freed. Returns FIELD/1. |
| `chain_tags_control` (`WILL_FAIL`) | RET ignores the address stack (`debug_ret_ends_chain`). It must fail, and does. |
| `syncv_blocking_control` (`WILL_FAIL`) | `sceGsSyncV` does not wait (`sce_graphics_debug_syncv_nowait`). It must fail, and does. |

Build and run (2026-10-11, all 11 pass, the retail test with the ELF present):

```
powershell -ExecutionPolicy Bypass -File tools\build.ps1 -BuildDir build\dma-i686
ctest --test-dir build\dma-i686 -L dmac
```
