# Platform censuses (PLAN.md step 2b)

What the game needs from the platform layer (`src/sce/`, `src/ps2/`).

- **Source:** `../RGDecomp` at commit `2efa6b43548fed253fafdee4d22c8d61d506acde`
  (naming fold 12). The commit is pinned in `tools/census/platform/common.py`.
- **Ground truth for edges:** the retail binaries (`work/SCUS_974.90`,
  `work/BIN/*.BIN`, `work/MODULES/*.IRX`, `IOPRP300.IMG`). Call edges come
  from decoded `jal`/`j`. Address-taken edges come from `lui`+`addiu`/`ori`
  pairs and from data words. Argument values come from straight-line
  constant propagation over the retail code. Source facts (C body or asm
  body, file path) come from the pinned tree, read through
  `tools/census/snapshot.py`.
- **Regenerate:** `python tools/census/platform/run_all.py --rebuild`
  (about 1 minute). The cache is `out/platform_cache.pkl`.
- **Library vs game:** MAIN's library code is one link band,
  0x100000..0x13BC20, plus two islands. The first is 0x165608..0x1660E0, the
  gcc-built sdremote command wrappers. The second is 0x446000..0x448000,
  kernel patch code. Every overlay function and the rest of MAIN is game
  code. Family boundaries follow link order and are listed in
  `common.LIB_RANGES`.

| File | Rows | What |
| --- | --- | --- |
| `platform_sdk_surface.tsv` | 1116 | Every MAIN library function, with role, family, body kind, game callers and library callers |
| `platform_ee_syscalls.tsv` | 273 | Syscall stubs, plus thread, semaphore, interrupt and alarm call sites with recovered arguments |
| `platform_sif_rpc.tsv` | 156 | RPC servers and (server, function number) pairs, the IOP module that serves each, modules loaded, all IOP modules |
| `platform_gs.tsv` | 255 | Privileged GS writes, A+D register writes (code and .data), constant arguments to GS setters, blend table |
| `platform_vu1.tsv` | 154 | Every MPG upload block, the VU1 variant table, VU0 program, `vcallms`, MSCAL sites, uploaders |
| `platform_misc.tsv` | 378 | Constant-address hardware register access, scratchpad, the per-area API list |

---

## 1. SDK surface: the `src/sce` implement-list

| Role | SDK families | Runtime (libc, libm, libgcc, mwcc-rt, MSL C++) |
| --- | --- | --- |
| `boundary` (game code calls it directly) | **158** | 109 (+2 boundary-ptr) |
| `internal` (reached only through the boundary) | 245 | 145 |
| `data-ref` (vtables, libmpeg MC tables, kernel tables) | 28 | 68 |
| `unreached` (dead, or crt0/kernel only) | 333 | 28 |

The 158 SDK boundary functions by family:

| Family | Count |
| --- | --- |
| libkernl | 45 |
| libvu0 | 20 |
| libsdr-gcc | 15 |
| libcdvd | 14 |
| libmc | 14 |
| libgraph | 13 |
| libpkt | 11 |
| libpad | 10 |
| libmpeg | 9 |
| libdma | 6 |
| libsdr | 1 |

Bodies: 138 are asm and 20 are C. The libkernl 45 break down as:

- threads/semaphores: 21
- interrupt/DMA-controller handlers and enables: 10
- fileio: 6
- IOP heap and load: 6
- SIF: 5 (`sceSifInitRpc`, `sceSifBindRpc`, `sceSifCallRpc`, `sceSifSetDma`, `sceSifDmaStat`)
- cache: 2
- `DisableIntr`/`EnableIntr`

- **No game code takes the address of any SDK function.** Every use is a
  direct call, so the list above is complete for `src/sce`. The only
  `boundary-ptr` rows are 2 MSL iostream destructors registered as
  static-destructor callbacks.
- **Overlays barely touch the SDK.** Only TITLE calls SDK functions:
  `sceGsSyncV`, `CreateSema` and `sceMcInit`. All other overlay library
  use is libc, libm and soft-float.
- **Runtime boundary (109).** These go to the host CRT or the compiler and
  need no `sce` work:
  - libc 33: memcpy/memset/str*/sprintf/rand/qsort/malloc/free/abort/assert.
  - libm 18: `sinf` alone has 331 call sites; `cosf` 169.
  - libgcc 19: the soft-double `dp*` helpers plus `__divdi3` and its kin.
  - mwcc-rt 11: double compares and u64 to double conversions.
  - MSL C++ 28: new/delete, array construct/destroy, `RegisterGlobalObject`
    (455 sites), iostream init ctors (218 static-init sites each), std::string.
- **Two mwcc-rt boundary functions are platform work, not CRT.**
  `OverlayLoadFile_100410`, the MWo3 overlay loader called by
  `OverlayLoad_1c3210`, and `MainStaticInit_100580` belong to the overlay
  manager and static-init order (PLAN P2).

## 2. EE kernel

- **168 `syscall` sites** in libkernl, all in library code. **48 are
  reachable from game code.** The reachable ones that matter:
  - threads: Create/Delete/Start/ExitDelete/Terminate, ChangeThreadPriority,
    RotateThreadReadyQueue, GetThreadId, ReferThreadStatus, SleepThread,
    iWakeupThread
  - semaphores: Create, Delete, Signal, iSignal, Wait, Poll, iPoll
  - handlers: Add/RemoveIntcHandler, Add/RemoveDmacHandler,
    `_Enable`/`_DisableIntc`, `_Enable`/`_DisableDmac`
  - others: FlushCache, SIF DMA (SetDma, SetDChain, DmaStat, Set/GetReg,
    StopDma), GsGet/PutIMR, SetVSyncFlag, SetGsCrt, EndOfHeap,
    GetMemorySize, Exit
- **Event flags, TLB, alarms, OSD config and ExecPS2 are not reached from
  game code.** The exception is a few crt and exit-path stubs reached via
  `Exit`/`abort`. Every other stub at 0x116180..0x116a30 not listed above is
  dead.
  - `DelayThread` (18 game callers) is library code built on the **timer-2
    alarm system**: `SetTimerAlarm`, plus a TIMER2 INTC handler installed by
    `InitTimer`. The host should implement it as a virtual-time sleep.
  - The 0x446xxx kernel-patch code (alarm, VBlank and ExecPS2 patches
    copied into the kernel) is library-internal and not needed.
- **Threads.** There are 11 game thread entries and 3 library ones. Every
  game priority derives from the main-thread priority `D_0047DF30`, which is
  initially 0x14 (20). `Main_15e700` sets the main thread to that value.

| Entry | Creator | Stack | Priority |
| --- | --- | --- | --- |
| `FileReqThread_182c30` | `FileReqThreadInit` | 0x2000 | P-1 |
| `SoundCmdWorkerThread_1b6c10` | `SoundSysInit` | cfg (likely 0x2000) | cfg (likely P-10; field mapping unverified) |
| `SoundThreadMain_1b6260` | `SoundThreadStart` | 0x800 | worker priority - 1 |
| `SoundStreamSlotThreadMain_1bc520` | `SoundRpcInit` | 0x1000 | P-5 |
| `SoundStreamThreadMain_1c1050` | `SoundStreamInit` | 0x1000 | P-5 (`D_0047E220`) |
| `CdDiskWatchThread_17fdc0` | `CdDiskWatchInit` | 0x800 | P-5 |
| `SysTickThreadMain_1c33f0` | `SysTickThreadStart` | 0x1000 | ? (not set on the straight-line path) |
| Movie `DefMain_1d52b0` | `MoviePlayerStart` | 0x800 | P |
| Movie `VideoDecMain_1d5240` | `MoviePlayerStart` | 0x4000 | P |
| Movie `MovieReadThread_1d4f50` | `MoviePlayerStart` | 0x4000 | P |
| `LoadingScreenThread_343510` | `LoadingScreenStart` | from cfg | from cfg |
| Library: `KernelTopThread` | crt0 | 0x400 | 0 |
| Library: `SdrCallbackThread_122fa8` | sdremote | 0x1000 | ? |
| Library: `CdCallbackThread_1292e0` | libcdvd | ? | ? |

  Where the const-prop `p_*` columns and the `src` column disagree, `src`
  wins. One example: `SoundRpcInit` sets `tp.size = 0x1000`, but const-prop
  reads 0.
- **63 `CreateSema` sites** (25 in game code). Almost all are binary
  semaphores (max 1, init 0 or 1). `title_TitleObjectsCreate` creates one
  with init 0xB.
- **Interrupt handlers the game installs:**
  - INTC VIF1(5): `Vif1IntcHandler_15e170`. It reads `T0_COUNT` and writes
    `VIF1_FBRST`, so the game uses VIF1 interrupt and stall for its
    double-buffered DMA lists.
  - INTC VBLANK_END(3): `SoundVblankIntrHandler_1bd6f0`.
  - INTC VBLANK_START(2): `MovieVblankHandler_1d4c90`. A second VBLANK_START
    handler arrives through `sceGsSyncVCallback(GfxVblankStartHandler_15df20)`.
  - DMAC GIF(2): `MovieDmacHandler_1d4b10`.

  Library handlers: libmpeg DMAC fromIPU(3) and toIPU(4), sifcmd DMAC
  SIF0(5), timer INTC TIMER2(11).

**Consequences for src/ps2:**

- The scheduler needs priority-ordered cooperative threads with about 14
  entries, sleep/wakeup and RotateThreadReadyQueue (`ThreadYield_1d2b70`).
- Interrupt delivery is needed for VBlank start/end, VIF1, the GIF DMAC and
  the two IPU DMACs.
- `DelayThread` needs a virtual clock.

## 3. SIF RPC and the IOP

The IOP side was established by scanning every IRX and every IOPRP300.IMG
module for calls to sifcmd export 17 (`sceSifRegisterRpc`). Each EE bind
`sid` matches a registering module.

| SID | IOP module (file) | EE side | Function numbers used (reached from game) |
| --- | --- | --- | --- |
| 0x80000001 | FILEIO 2.18 (IOPRP300.IMG) | fileio | 0 open, 1 close, 2 read, 3 write, 4 lseek, 0xFF init. 0xFD/0xFE plus 5..0x1A are linked but unreached |
| 0x80000003 | FILEIO (iopheap) | iopheap | 1 alloc, 2 free |
| 0x80000006 | LOADFILE 2.2 (IOPRP) | loadfile | 0 module load, 0xFF bind |
| 0x80000100 / 0x80000101 | padman 4.33 (PADMAN.IRX) | libpad | 1 (every pad command uses fno 1, with a sub-command in the buffer) |
| 0x80000400 | mcserv 2.16 (MCSERV.IRX) | libmc | 1 getinfo, 2 open, 3 close, 5 read, 6 write, 0xA flush, 0xC chdir, 0xD getdir, 0xE rename/setinfo, 0x10 format, 0xFE init |
| 0x80000592 | CDVDFSV 2.38 (IOPRP) | libcdvd | 0 init |
| 0x80000593 | CDVDFSV (S-commands) | libcdvd | 3 disk type, 4 error, 5 tray, 0x22 mmode, 0x23 thread priority, 0x27 dual-layer info |
| 0x80000595 | CDVDFSV (N-commands) | libcdvd | 1 read, 5 seek, 0xE ready |
| 0x80000597 | CDVDFSV (search file) | libcdvd | 0 |
| 0x8000059A / 0x8000059C | CDVDFSV (disk ready) | libcdvd | 0 |
| 0x80000701 | sdr_driver 4.1 (SDRDRV.IRX) | libsdr `sceSdRemote` | fno = libsd remote command: 0x8010 SetParam, 0x8050 SetAddr, 0x8070 SetCoreAttr, 0x8130 SetEffectAttr, 0x90F0 (gcc island `SoundIopSendCmd*`: 64-byte command blocks), 0xE620 callback init |
| 0x80000704 | **EE-side server** (`SdrCallbackThread_122fa8`), bound by SDRDRV | libsdr | IOP to EE callbacks |
| **0x123456** | **pcm_mixer 1.2 (PCMPLAY.IRX)** | game `SoundRpcCall_1bc5e0` | 0x8000 init, 0x8090 and 0x80A0 stream-slot updates, 0x8400 and 0x10 shutdown |

- **IOP boot sequence:**
  1. `IopRebootWithImage_15e560` reboots the IOP with
     `cdrom0:\MODULES\IOPRP300.IMG;1`. The image holds FILEIO, CDVDMAN,
     CDVDFSV, LOADFILE and the IOP core.
  2. `LoadIopModules_15e240` loads 15 modules from `cdrom0:\MODULES\`, in
     this order: sio2man, padman, mcman, mcserv, libsd, sdrdrv, modhsyn,
     modmidi, modmsin, cdvdstm, sksound (`maxtrack=16`), skhsynth
     (`maxentry=16`), skmidi (`maxtrack=5 maxentry=16`), skmsin
     (`maxtrack=9 maxentry=16`), pcmplay.
- **Corrections to the retired recomp notes:**
  - SID 0x123456 is Sony's sample **pcm_mixer** (PCMPLAY.IRX), not CRI
    middleware.
  - 0x80000592..0x8000059C are the standard CDVDFSV services, not sound.
  - The Standard Kit sound modules (SKSOUND, SKHSYNTH, SKMIDI, SKMSIN, plus
    MODHSYN, MODMIDI, MODMSIN) **register no RPC servers at all**. They are
    driven through **sdrdrv** (SKSOUND imports `sdrdrv`), via `sceSdRemote`
    commands from the EE.
  - CDVDSTM is loaded but registers no sifcmd server. No `sceCdSt*` client
    is linked on the EE, so it is probably unused (unverified).
- **The game streams bulk data to IOP RAM by raw SIF DMA**
  (`SifDmaSendSync_1c21e0` and `_1d2c20` call `sceSifSetDma`):
  - sound banks and SPU transfer chunks
  - stream slots
  - movie audio (`AudioDec*`)

  Their destinations come from `sceSifAllocIopHeap`.
- **Disc reads bypass FILEIO.** The game file layer (`CdDatArchiveOpen`,
  `FileSlotRead`, `FileCdSearchLocked`) reads **sectors with `sceCdRead`**
  after `sceCdSearchFile`/`sceCdLayerSearchFile`. It also calls
  `sceCdReadDvdDualInfo` and `sceCdMmode(2)` (DVD). `sceOpen`/`sceRead` are
  used only by `FileSlotOpenPath`/`FileSlotRead`/`FileWriteAll`, the
  host0/cdrom path variant.

**Consequences for src/ps2 IOP HLE:**

- Six services: fileio+iopheap, loadfile (the module list only), padman,
  mcserv, CDVDFSV (7 function numbers), and **sound = sdremote + SK
  semantics + pcm_mixer**.
- Plus an IOP RAM model for the SIF DMA targets.
- `sceCdRead` takes LBA plus sector count. The `data/` layout from D8 must
  map an LBA range back to a file (keep an LBA-to-file table in the
  manifest), or `sceCdSearchFile` must return synthetic LBAs that the read
  HLE resolves.

## 4. GS

- **Display (static):**
  - `sceGsResetGraph(0, 1, 2, 1)`: interlaced, NTSC, frame mode.
  - `sceGsSetDefDBuff(.., PSMCT32, 640, 448, ..)`.
  - A prebuilt A+D packet sets SCISSOR_1 to 0..639 by 0..223, i.e. a
    640x224 field buffer for one of the contexts.
- **Privileged register writes:**
  - libgraph `sceGsPutDispEnv` writes PMODE, SMODE2, DISPFB1/2, DISPLAY1/2,
    EXTDATA and BGCOLOR.
  - Game `GsDbufPutEnv_144150` writes PMODE, DISPFB1 and DISPLAY1 itself.
  - CSR is written by ResetGraph and StoreImage, BUSDIR by StoreImage.
  - **GS-to-host readback is used.** `sceGsExecStoreImage` is called from
    `GfxEndFrame_141c20` and `GsDownloadImage_140f20`, so the renderer must
    support downloads.
- **Primitives through the game packet API** (`GsPktOpenPrim`/`SetPrimType`,
  266 constant sites):

  | Primitive | Sites |
  | --- | --- |
  | SPRITE | 192 |
  | TRISTRIP | 35 |
  | TRIANGLE | 13 |
  | LINE | 8 |
  | LINESTRIP | 7 |
  | POINT | 6 |
  | TRIFAN | 5 |

  3D geometry primitives come from VU1 microcode GIF tags and are not
  statically visible.
- **Blending:**
  - 12 ALPHA presets in `D_00449EF0`, decoded in the `table` rows: Cs/Cd
    lerp, additive `(Cs-0)*As+Cd`, subtractive `(0-Cs)*As+Cd`,
    FIX=128 variants, and multiply-like `(Cd-0)*As`.
  - `GsPktSetBlendMode` preset indices used: 1, 2, 9, 3, 7, 8, 0, 10.
- **Tests:**
  - Alpha test functions: GREATER (24), GEQUAL (11), ALWAYS (8), NEVER (2),
    LESS (1). References are mostly 0 or 1, plus 0x80/0x81.
  - Destination-alpha test and FBA are both used.
  - Z test via `GsPktSetZTest` is 0 or 2. ZTE is always set by
    `GsTestSetZTest`.
- **Registers seen in A+D (code heuristic plus data packets):** TEX0_1/2,
  TEX1_1, TEX2_2, CLAMP_1/2, MIPTBP1_2/2_1, TEXA, TEXCLUT, TEXFLUSH, FOG,
  FOGCOL, ALPHA_1, TEST_1, FBA_1, FRAME_1, ZBUF_1, SCISSOR_1,
  XYOFFSET_1/2, PRMODECONT, DTHE, COLCLAMP, DIMX, and BITBLTBUF, TRXPOS,
  TRXREG and TRXDIR (uploads). Not seen: PABE, SCANMSK, SIGNAL, LABEL,
  context-2 ALPHA/TEST/FRAME/ZBUF.
- **Limit:** `ad_code` is a heuristic: a constant GS id stored at offset%16
  == 8. Rows marked `low` may be noise. Values held in struct fields are
  `dyn`. A GS-dump census in P3 will give the exact set.

## 5. VU1 and VU0 microcode

- **VU1:**
  - 53 DMA-tagged VIF packets (all RET-tagged pieces) hold 64 MPG blocks:
    7,450 instructions, 59.6 KB of code, 62 unique code hashes.
  - All of it sits at 0x436CB0..0x445C60 in MAIN .data.
  - `VuMicrocodeTableInitMaybe_152830` builds the `[4][12][4]` piece table.
    48 variants (4 passes × 12 kinds), each a head (VU addr 0x320), a kind
    piece (0x39D0) and a tail (0x2620..). Planes 1..3 copy plane 0 with
    patches.
  - Per-kind data lists (0x449DD0..0x449EF0, plus `D_0047DEC0`/`DED0`)
    reference second-level pieces at VU addresses 0x960, 0x10E0, 0x1900
    and 0x2100.
  - `ModelDrawOffscreenCompositeMaybe_16aac0` uploads one more piece
    (0x445C60).
  - 4 small preamble packets have no static referrer.
  - VU1 programs are therefore assembled from swappable pieces. A native
    replacement (D3 phase 2) should key on the **piece hash set per draw**,
    not on whole programs.
- **MSCAL kicks:** `DmaPktAddMscalCall_145b20` has 4 call sites (model draw,
  shadow casters, effect quads, effect models). The kick qword is
  `D_0047DE60`.
- **VU0 micro mode is used.** One VIF0 packet (0x445810, CNT) uploads 132
  instructions (blocks at 0x0 and 0x640). `GfxSysInit_15dd20` sends it once
  through `Vif0SendInitPacketMaybe_13bcc0`. There are 2 `vcallms 0x0` sites:
  - `MatRotateVu0_13bc20`, with 11 callers in animation
  - `MatFromSRTVu0_13bc90`, with 6 callers in node and transform code

  These two need a C reimplementation of that microprogram, or a VU0
  interpreter. COP2 macro-mode use is covered by `census/asm_bodies.tsv`.

## 6. Everything else

- **Movie/IPU:**
  - libmpeg is used only through 9 entry points: Create, Delete,
    GetPicture, Reset, IsEnd, AddCallback, AddStrCallback, DemuxPssRing,
    and a stop-DMA helper.
  - **The game's own movie code (`ViBuf*`, `VideoDecMain`, `DefMain`,
    `MovieReadThread`, `AudioDec*`) drives IPU and DMA channels 3 and 4
    directly.** It touches IPU_CMD, IPU_CTRL, IPU_BP, D3/D4
    CHCR/MADR/QWC/TADR, D_ENABLER/W and D_STAT, and installs VBlank and
    GIF-DMAC handlers.
  - So the D4/P4 movie service must replace this game-side layer through
    overrides. Replacing `sceMpeg*` alone is not enough.
- **Timers:** the game reads `T0_COUNT` directly (`GfxEndFrame`,
  `GfxFlipBuffersMaybe`, `Vif1IntcHandler`) and sets `T0_MODE` in
  `GfxSysInit`. src/ps2 needs a timer-0 model on the virtual clock. Timer 2
  belongs to the kernel alarm library. No RTC or clock read is linked:
  there is no `sceCdReadClock`.
- **Scratchpad:**
  - **No game code does a constant-address scratchpad load or store.**
    `lui 0x7000` in game code builds DMA END tags (0x7000xxxx).
  - Scratchpad is used by libmpeg, through DMA channels 8 and 9.
  - Any pointer-held use is outside this census (see
    `census/addr_literals.tsv`).
- **Pad:** libpad v1 API, 10 functions: Init, PortOpen, Read, GetState,
  GetReqState, InfoAct, InfoMode, SetMainMode, SetActDirect and
  SetActAlign (analog mode and vibration).
- **Memory card:** 14 libmc functions (no Delete or Unformat from game
  code). `sceMcSync` has 10 callers.
- **CDVD:** 14 libcdvd functions (see §3).
- **Cache and DMA:** `FlushCache` (10 callers), `SyncDCache` (1). DMA goes
  through `sceDmaGetChan`, `Send` and `Sync`. GIF packets go through
  `sceGifPk*`.

## Limits and uncertainty

- Edges are static: `jal`/`j`/`lui+addiu`/data words. Indirect calls
  through registers loaded from computed addresses are invisible, but no
  game code takes the address of an SDK function, so the SDK boundary is
  unaffected.
- Argument recovery is straight-line constant propagation from the function
  entry, with no merging at branch targets. A `?` or `argN` means not
  static, or passed through from the caller. Values marked
  `(init X)` are .data initial values, not runtime values.
- Syscall numbers are the nearest `li $v1` before each `syscall`. A few
  wrapper rows (`iWakeupThread_117468 -0x2F`) are approximate.
- Library family boundaries are link-order address ranges (set by hand).
  libsdr-gcc and the kernel patch island are named by observation.
- IOP function numbers are EE-side only. The IOP dispatch was not
  decompiled, so the meaning of fno 0x8090/0x80A0 (pcm_mixer) and of the
  0x90F0 SK command payloads still has to come from IRX disassembly.
