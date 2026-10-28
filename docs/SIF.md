# SIF / IOP HLE

**Oracle only since 2026-10-18** ([NATIVE-IOP.md](NATIVE-IOP.md)): the default
`RG_IOP=native` never calls into `src/ps2/sif` / `src/ps2/iop` (the SDK entries in
`src/sce/sif` answer natively, the runtime does not boot the SIF); this HLE runs with
`RG_IOP=hle`, or when a sound path is left on the HLE.

PLAN.md D4 (IOP at the RPC boundary) and P2 ("IOP RAM model"). There is no R3000
emulation: the IOP is 2 MiB of RAM, a heap, a module log, and host C servers
registered by SIF RPC id. Everything here was written from scratch from the census
(`census/PLATFORM.md` section 3, `platform_sif_rpc.tsv`, `platform_sdk_surface.tsv`),
the game's call sites and public SDK knowledge. No GPL code was used.
The sound protocol itself (what the sound servers must do) is in
[SOUND-PROTOCOL.md](SOUND-PROTOCOL.md).

| Path | What |
| --- | --- |
| `src/ps2/iop/iop.[ch]` | IOP RAM (2 MiB, KSEG/0xBC000000 aliases folded), sysmem-style heap, static area for server buffers, module + reboot log |
| `src/ps2/iop/iop_hle.c` | HLE servers: FILEIO 0x80000001, iopheap 0x80000003, LOADFILE 0x80000006, logging placeholders for padman 0x80000100/101, mcserv 0x80000400, sdr_driver 0x80000701, pcm_mixer 0x123456 |
| `src/ps2/sif/sif.[ch]` | SIF core: registers, SIF1/SIF0 DMA, event queue, RPC registry and calls, EE-side servers, raw commands, reports, call log |
| `src/sce/sif/` | EE SDK surface: sifcmd, sifrpc, SIF DMA syscalls, iopheap, loadfile, iopcontrol, fileio, libsdr sdremote, plus the game-tree names (`game_names.c`) |
| `tests/sif/` | CTest suite, label `sif` |

CMake targets: `rg_ps2_iop`, `rg_ps2_sif`, `rg_ps2_iop_hle`, `rg_sce_sif`, `rg-sif-tests`.

## Execution model

- **Single host thread** (the kernel's). Nothing locks.
- **EE addresses are host pointers** (i686). IOP addresses are offsets into the IOP
  RAM array; `iop_phys` folds 0x80000000/0xA0000000/0xBC000000 aliases.
- **The SIF core is kernel-agnostic.** Two hooks connect it:
  - `now()` is the clock. `src/sce/sif` uses `ps2k_now()`.
  - `schedule(due)` asks for `sif_deliver()` at or after `due`. `src/sce/sif` maps it
    to `ps2k_post_dmac(5 /*SIF0*/, due - now)` and installs a DMAC SIF0 handler
    (as the SDK's `sceSifInitCmd` does) that calls `sif_deliver()`.

  So every IOP -> EE event (RPC reply copy + end function, IOP -> EE RPC request,
  IOP -> EE command) runs in **interrupt context** at its due time, like the
  retail SIF0 DMA-end interrupt. Without hooks (unit tests) `sif_advance()` /
  `sif_deliver()` drive it.
- **Servers run at call time.** `sceSifCallRpc` copies the send data into the
  server's receive buffer (in IOP RAM), runs the host server function at once, and
  queues the completion (reply copy into the EE receive buffer, end function, busy
  flag cleared) at `now + rpc_latency`. The reply is never visible before the
  completion event, even with zero latency.
- **Synchronous calls block on a semaphore**, created per call and signalled from
  the SIF0 handler (`CreateSema` / `WaitSema` / `DeleteSema`, as libkernl does), so
  the scheduler can run other threads and move virtual time. Outside a guest thread
  (host setup code) the call delivers its events directly.
- **Cost model** (`rg_sif_boot_config`, all default 0): `rpc_latency`, `dma_setup`,
  `dma_cycles_per_qword` (SIF1 DMA completion time for `sceSifDmaStat`),
  `boot_latency` (reboot -> SMFLAG.BOOTEND).

## Boot

`src/runtime` calls `rg_sif_boot` right after the kernel and the card/pad models are up
(RUNTIME.md "Init order", step 7). It also sets `iop_hle_set_post_install` (new), so
padman, mcserv and the sound HLE replace their placeholders inside `iop_hle_install`.

`rg_sif_boot(&cfg)` (after `ps2k_init`) resets SIF + IOP, registers the HLE servers
and wires the hooks. If the game reaches `sceSifInitRpc`/`sceSifInitCmd` first, it is
called with defaults. The game's sequence then works unchanged:

1. `IopRebootWithImage`: `sceSifRebootIop(IOPRP300.IMG)` records the reboot, clears
   IOP RAM/heap/module list and the SMFLAG boot bits; `sceSifSyncIop` returns 1 once
   BOOTEND is set again (it moves time to the boot event itself, because the game
   spins on it without a kernel call). Bindings and in-flight calls are dropped; the
   servers stay registered (their buffers are re-reserved).
2. `sceSifInitRpc`, `sceSifInitIopHeap` (binds 0x80000003), `sceFsReset`.
3. `LoadIopModules`: 15 `sceSifLoadModule` calls go over LOADFILE 0x80000006 fno 0;
   each is recorded with its arguments (`iop_module_dump()` prints the table) and
   gets ids 1..15. Unknown module names are accepted and reported.

## SDK semantics implemented

| Area | Functions | Notes |
| --- | --- | --- |
| RPC client | `sceSifBindRpc`, `sceSifCallRpc`, `sceSifCheckStatRpc` | `sceSifClientData` keeps the SDK layout; `serve` (+0x24, which the game polls) is non-NULL once bound; `buff` = the server buffer's IOP address. `SIF_RPCM_NOWAIT` returns at once; `sceSifCheckStatRpc` is 1 until the SIF0 completion. End functions run in handler context for both modes. |
| RPC EE servers | `sceSifSetRpcQueue`, `sceSifRegisterRpc`, `sceSifGetNextRequest`, `sceSifExecRequest`, `sceSifRpcLoop`, `sceSifRemoveRpc(Queue)` | IOP code calls them with `sif_iop_call_ee(sid, fno, data, size)`; the request is queued and the queue's thread is woken (`iWakeupThread`). |
| commands | `sceSifInitCmd`, `sceSifAddCmdHandler`, `sceSifRemoveCmdHandler`, `sceSifSendCmd`, `isceSifSendCmd`, `sceSifGet/SetSreg` | EE -> IOP: extra data is SIF1-copied, then the IOP handler runs; `SET_SREG` is handled. IOP -> EE: `sif_iop_send_cmd` (event). |
| SIF DMA | `sceSifSetDma`, `isceSifSetDma`, `sceSifDmaStat`, `sceSifGetReg`, `sceSifSetReg`, `sceSifSetDChain` (no-op) | `sceSifDmaData` = {EE src, IOP dst, size, mode}. Data is copied at submit; the id completes at submit + cost. Any element outside IOP RAM fails the whole list (returns 0, reported). |
| registers | MSCOM, SMCOM, MSFLAG (EE writes set), SMFLAG (EE writes clear), CTRL, 32 sregs | SMFLAG = SIFINIT\|CMDINIT\|BOOTEND (0x70000) after boot. |
| iopheap | `sceSifInitIopHeap`, `sceSifAllocIopHeap`, `sceSifFreeIopHeap`, `sceSifFreeSysMemory_11ea40`, `AllocSysMemory`, `Query*` | RPC 0x80000003 fno 1/2/4/5/6/7/9. Heap [0x0C0000, 0x1F0000), 256-byte blocks, first fit. Server buffers sit in [0x010000, 0x0C0000). |
| loadfile / iopcontrol | `sceSifLoadModule(_11f7a0)`, `sceSifLoadStartModule`, `sceSifRebootIop(_11fcd0)`, `sceSifResetIop`, `sceSifSyncIop(_11fc80)`, `sceSifIsAliveIop` | LOADFILE fno 0 request `{s32 argsz; char path[252]; char args[252]}`, reply `{id, result}`. |
| fileio | `sceOpen/Close/Read/Write/Lseek` (+ `_11b928` etc.), `sceFsReset` | FILEIO 0x80000001, port-own request `iop_fio_req`. `cdrom0:\X;1` -> `<cdrom_root>/X` (`RG_DATA` or `data/`), `host0:` -> `host_root`; other devices -> -ENODEV. Reads arrive by SIF0 write into the EE buffer. SCE flags RDONLY/WRONLY/RDWR/APPEND/CREAT/TRUNC. |
| libsdr | `sceSdRemoteInit(_122890)`, `sceSdRemote(_1229e8)`, `sceSdRemoteCallbackInit(_122d70)`, `sceSdRemoteCallbackQuit(_122e70)` | Packing follows the retail asm (header of `src/sce/sif/libsdr.c`): buf[0] = EE address of buf, buf[1..6] = args; 0x9000..0x90F0 send the caller's block; 0x8130/0x81A0/0x81B0 use fno = cmd\|core; return = reply word 0. The callback thread registers EE server 0x80000704 and dispatches word0 bits 0x100/0x200/0x400 as `SdrCallbackRpcDispatch`. |

## Reporting

`sif_set_report(fn)` (default: stderr) receives: unknown server (bind reported once
per SID, every call reported), unknown function (a server sets `ctx->unknown`),
bad IOP address, send larger than the server buffer, IOP call to a missing EE
server, command without handler. A call to an unknown SID still queues its
completion, so a synchronous caller never hangs, and leaves the receive buffer
untouched. `sif_call_log_get()` keeps the last 256 calls with status, and
`sif_call_count(sid, fno)` counts every pair. The placeholder servers print the
first call of each (sid, fno) with its first four words (silence: `RG_IOP_QUIET=1`)
and reply zeros.

## Tests

`rg-sif-tests <name>`; `ctest -L sif`.

| Test | Checks |
| --- | --- |
| `dma_iop_ram` | SIF1 list into IOP RAM incl. the 0xBC000000 alias, completion at exactly setup + qwords x cost, out-of-range list rejected without partial copy, register semantics (MSFLAG set, SMFLAG clear, sregs), heap first fit. |
| `rpc_call` | Bind token, send data lands in the server's IOP buffer, reply invisible until delivery, two function numbers, per-(sid,fno) counts, call log order. |
| `rpc_async` | Two async calls with 1000-cycle latency complete at exact times in FIFO order with their end functions. |
| `registry` | Register/replace/unregister, bufferless server, send truncation report, the HLE server set, reboot keeps servers. |
| `unknown` | Unknown bind/call reported with SID/fno, waiter released, receive buffer untouched; unknown fno reported; missing EE server / command handler reported; unknown module flagged. |
| `sdk_kernel` | End to end on the EE kernel: reboot + sync with boot latency, the game's 15-module load (ids, args), bind polled at +0x24, AllocIopHeap + SetDma + DmaStat/DelayThread loop, sync call blocks >= latency with the end function in handler context, async call + `sceSifCheckStatRpc`, FILEIO write/lseek/read through `host0:`/`cdrom0:`, sdremote 0x8010/0x90F0/0xE620 counts, IOP -> EE 0x80000704 callback reaching an SPU2 handler on the callback thread. |
| `*_control` (`WILL_FAIL`) | `dma_iop_ram_control` expects the data at a wrong IOP address; `rpc_async_control` delivers completions early. Each must fail its check, and does. |

Status 2026-10-11: 8/8 pass (6 tests, 2 controls), `build\iop-i686`.

## Open issues

- **Retail sema/handler ids: settled** ([VALIDATION.md](VALIDATION.md) section 3).
  Retail sync `sceSifCallRpc` creates one semaphore per call (max 1, init 0) and
  deletes it after `WaitSema`, as modelled here. With the kernel's sema ids now starting
  at 0 and reusing the last freed id first (KERNEL.md "Id numbering"), every sync call
  gets the same id, as on retail; id 0 is valid, so `sif_ee.c` treats a sema id `>= 0`
  (not `> 0`) as "block on it". The SIF0 DMAC handler id comes from the shared
  INTC/DMAC range 1..128.
- **Placeholders.** padman, mcserv, sdr_driver and pcm_mixer reply zeros. The real
  pad/memcard/sound HLE replaces them by re-registering the SID.
- **libpad / libmc / fileio packet layouts** of the retail EE libraries are not
  modelled: the port reimplements those SDK functions, so each server's request
  layout is the port's own. Only the SID/fno numbering follows retail.
- **Case-sensitive hosts.** `cdrom0:` paths are upper case. On Linux, FILEIO `open`
  falls back to a per-component case-insensitive directory scan when the exact path is
  missing (`fopen_ci` in `iop_hle.c`, [LINUX.md](LINUX.md)).
- **`rg_sif_boot` before `ps2k_init`** would leave a stale DMAC handler id; boot
  after the kernel is initialised.
- **SIF2, `sceSifSetDChain`, DMA tag IRQ bits** are not modelled; no game path uses them.
