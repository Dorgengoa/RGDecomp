# Pad and memory card HLE

**Since 2026-10-18 the default path is native** ([NATIVE-IOP.md](NATIVE-IOP.md)): with
`RG_IOP=native` libpad and libmc call the native pad service (`src/native/input/rg_npad.c`)
and the save service (`src/native/saves`) directly, with no padman / mcserv server and no
SIF. Everything below describes the semantics both paths keep, and the HLE transport that
`RG_IOP=hle` (the oracle) still runs.

PLAN.md P4 ("Pad", "Memory card") and D4 (IOP at the RPC boundary). The DualShock 2 and
the PS2 memory card are host models behind the game's own libpad / libmc calls. Written
from scratch from the game's call sites (`game/src/main/pad`, `game/src/main/file/Mc*`,
`game/src/main/sys/McPollCardChange_372db0.c`), the retail libpad/libmc asm the snapshot
keeps (`game/src/main/sdk/scePad*.c`, `sceMc*.c`), the census, and public descriptions of
the PS2 pad protocol and card file system. No GPL code was used (D7).

| Path | What |
| --- | --- |
| `src/ps2/padmc/padman.[ch]` | IOP side, pad: DS2 model per port, the pad DMA buffer writer, SIF servers 0x80000100/101 (the `RG_IOP=hle` oracle) |
| `src/native/input/rg_pad_io.[ch]` | the host input-source and rumble interface, scripted replay (shared by padman and the native pad service; moved out of padman 2026-10-18) |
| `src/native/saves/mccard.[ch]` | card: PS2 memory card semantics over a host directory per slot (the native save service; moved from `src/ps2/padmc` 2026-10-18, unchanged) |
| `src/native/saves/mc_time.c` | card: the card-time cost model (`mcserv_config` is an alias of `mc_time_config`) |
| `src/ps2/padmc/mcserv.[ch]` | IOP side, card: the mcserv SIF server 0x80000400 (the `RG_IOP=hle` oracle) |
| `src/sce/padmc/libpad.[ch]` | EE libpad (v1 API) with retail semantics, plus `scePadEnd_12b208` |
| `src/sce/padmc/libmc.[ch]` | EE libmc with retail semantics, plus the 19 game-tree names (`sceMcInit_12c648`, ...) |
| `tests/padmc/` | CTest suite, label `padmc` |

CMake targets: `rg_ps2_padmc` (kernel-agnostic, needs `rg_ps2_sif`), `rg_sce_padmc`
(EE layer, needs the kernel and `rg_sce_sif`), `rg-padmc-tests`.

## Where the HLE sits, and why

The game calls the **library API**, never the RPC: every libpad and libmc function is an
asm-bodied SDK unit that transform 6 excludes (`game/EXCLUDED.tsv`: 32 libpad + 23 libmc
rows). So the port must provide the API in any case. Two layers:

- **EE layer = the API**, reimplemented with the retail control flow read off the asm:
  which bytes of the pad DMA buffer each reader looks at, the libmc lock / completion
  semaphores, the function number reported by `sceMcSync`, the issue-time error codes.
- **IOP layer = the RPC servers**, re-registered on the retail SIDs (0x80000100/101,
  0x80000400) over the placeholders in `src/ps2/iop`. The EE layer talks to them with
  `sceSifCallRpc` exactly where retail does: synchronous calls for pad commands and
  `sceMcInit`, `SIF_RPCM_NOWAIT` plus an end function for every other card operation.

Keeping the RPC boundary costs little and buys what the game can observe: the sync
calls create and delete one semaphore each (game-visible ids, as on retail), virtual time
passes across a call (SIF `rpc_latency`), card operations complete on the SIF0 interrupt,
and `sif_call_count` / the call log line up with retail SID/fno numbering for traces. The
request/reply **layouts** are the port's own (as for FILEIO, docs/SIF.md); only the
numbering follows retail. The game never touches the pad DMA buffer or the libmc buffers
directly: `D_004B2A80` / `D_004B2B80` appear only as the `scePadPortOpen` argument in
`PadOpenPorts_1c6bf0`.

## Pad

### Model (padman)

One DualShock 2 per port, slot 0 only (no multitap: `scePadGetSlotMax` = 1). Per port the
model keeps the controller state, main mode, lock, actuator alignment and a pending
command. **Time is the VBlank count**: `padman_update(vblank)` steps every open port once
per VBlank. libpad calls it with `ps2k_vblank_count()` on entry to every function, so the
DMA buffer always holds what padman's per-frame SIF DMA would have written by then. A
runtime may also call it from its VBlank hook to keep the buffer live for state traces.

| VBlank after `scePadPortOpen` | `scePadGetState` | buffer |
| --- | --- | --- |
| open frame | 5 (libpad's init: EXECCMD, reqState BUSY, data 0xFF) | written by libpad |
| +1 | 1 FINDPAD | `find_frames` (2) counts down from open |
| +2, +3 | 2 FINDCTP1 | `ctp1_frames` (2), identifying the DS2 |
| +4 on | 6 STABLE | data valid, mode info, `ok` = 1 |
| no controller | 0 DISCONN | after FINDPAD; back to FINDPAD when one is plugged |

A command (`scePadSetMainMode`, `scePadSetActAlign`, `scePadSetButtonInfo`) is accepted
only when STABLE and idle; reqState is BUSY (`scePadGetState` = 5 EXECCMD) for
`cmd_frames` (3) VBlanks, then COMPLETE with the new mode / alignment. A DS2 **powers up
digital** (0x41), as hardware and PCSX2 do; unplugging resets it to digital, unlocked,
motors unmapped. So the game takes its full path, verified by the `pad_game` test running
the game's own code: `PadUpdateConnection_184a50` phase 0 (mode 4) -> 0x28 -> 0x29
`SetMainMode(1, 3)` -> 0x2A (wait COMPLETE) -> 0 (mode 7) -> 0x46 `InfoAct(-1)` = 2,
`SetActAlign {0,1,FF..}` -> 0x47 -> 0x63 steady reads. `config.start_analog = 1` skips the
digital start.

`config.keep_analog_lock = 1` (off in `padman_default_config`; **on in the runtime**, via
`rg_runtime_config.pad_power_cycle = 0`): once the game has locked analog mode
(`SetMainMode(1, 3)`), the port stays 0x73 and locked. An unplug / replug still goes
DISCONN -> FINDPAD -> FINDCTP1 -> STABLE (motors unmapped, as before) but comes back in
0x73, and a `SetMainMode` to digital completes without changing the mode. The boot path is
unchanged (a pad the game never locked behaves as hardware). Reason: if
`PadIsAnalogMode_184960` is false the game raises its "analog required" pause, and a
host device change (port 1 in Insectron versus, docs/INPUT.md) must not cause that.

### DMA buffer (256 bytes, two 0x80-byte halves)

padman alternates halves by frame (`frame & 1`); libpad reads the one whose frame counter
(+0x58) is larger (signed compare, as `scePadGetDmaStr`).

| Offset | Field | Value when STABLE |
| --- | --- | --- |
| 0x00 | data[32] | [0] 0 = ok, [1] mode id (0x41 / 0x73 / 0x79), [2] ~buttons >> 8, [3] ~buttons & 0xFF, [4..7] rx ry lx ly (analog), [8..19] pressures (0x79), the rest 0, **[31] = 0x5A** |
| 0x20 / 0x28 | actDirect / actAlign | align = last SetActAlign |
| 0x30 | actData[8][4] | act 0 `01 02 00 0a`, act 1 `01 01 01 14` (func, sub, size, current) |
| 0x40 | (actuator combination) | `02 00 01 00` |
| 0x50 | modeTable u16[4] | {4, 7} |
| 0x58 | frame | frames since open |
| 0x60 | length | **0x20** in every mode |
| 0x64..0x6B | modeConfig, modeCurId, model, buttonDataReady, nrOfModes, modeCurOffs, nrOfActuators, numActComb | 2, id, 3, 1, 2, 0/1, 2, **1** |
| 0x6C | (unknown) | `00 01 03 00` |
| 0x70..0x72 | state, reqState, ok | 6, 0/1/2, 1 |

The STABLE values are the real padman's, measured on PCSX2 (which runs the disc's
padman) in analog mode 0x73 ([VALIDATION.md](VALIDATION.md) section 4): every
`scePadRead` returned 32 and copied 32 bytes (`00 73 ff ff 7f 7f 7f 7f`, zeros, `5a`), and
the buffer held the actData, +0x40, +0x6B = 1 and +0x6C bytes above. Length 0x20, the
zero tail and the trailing 0x5A are assumed to hold in 0x41 and 0x79 as well (not
measured). actData and 0x5A are padman's values, not checked against hardware.

Buttons use the SCE bit layout, so the game's decode in `PadReadData_184df0`
(`((d[2] << 8) | d[3]) ^ 0xFFFF`) yields START = 0x0800, UP 0x1000, RIGHT 0x2000, DOWN
0x4000, LEFT 0x8000, SELECT 0x0100, L3 0x0200, R3 0x0400, L2 0x01, R2 0x02, L1 0x04,
R1 0x08, TRIANGLE 0x10, CIRCLE 0x20, CROSS 0x40, SQUARE 0x80 (the word at pad struct +4,
`0x004B2574`, that tools/trace's hook ORs into).

### libpad semantics kept from retail

- `scePadGetState` on a port that is not open returns **99**, not 0 (`scePadStateClosed`).
  STABLE with reqState BUSY reads as 5.
- `scePadInfoMode` (retail 0x12BCA0, VALIDATION.md 4): copies the newer half; 0 unless
  `ok` (+0x72) = 1 and reqState (+0x71) is not BUSY; CURID = +0x65 >> 4 (0 for 0xF3);
  CUREXID = u16 at +0x50 + 2 x (+0x69); CUREXOFFS = +0x69; IDTABLE -1 = nrOfModes
  (+0x68), i < nrOfModes = u16 at +0x50 + 2i; the last three are 0 when modeConfig
  (+0x64) = 1. Observed: InfoMode(1) = 7, InfoMode(2) = 4 while digital,
  InfoMode(4, -1) = 2. (Retail does not bound the index; here an index past the
  0x80-byte half reads 0.)
- `scePadInfoAct`: 0 unless `ok` = 1 and modeConfig >= 2 (no reqState check in the
  retail asm); actno must be < nrOfActuators (+0x6A); actno -1 = nrOfActuators
  (observed 2); terms are **1-based** (1 func, 2 sub, 3 size, 4 current), byte
  +0x30 + 4 x actno + term - 1.
- `scePadRead` copies and returns the length at +0x60 (retail has no clamp; the port
  clamps at 32 only against a corrupt buffer).
- `scePadPortOpen`: buffer must be 64-byte aligned; already open -> 0; initialises both
  halves (frame 0, state 5, reqState 2, data 0xFF, length 0) before the RPC.
- `scePadSetMainMode` / `SetActAlign` / `SetButtonInfo` return the server's answer and
  set reqState BUSY in the newer half when it is 1. `EnterPressMode` / `ExitPressMode` =
  `SetButtonInfo(0xFFF / 0)`.
- `scePadInit` requires padman version (v >> 8) == 4 (the server reports 0x0421, 4.33).
- `scePadRead` returns `int`, not `unsigned char`: the game declares it `s32`, and on
  i686 a `u8` return leaves EAX's upper bits undefined.

Port deviations: `scePadInit` does not spin on an unbound server, and does not register
the SIF command handler 0x80000019 (`PadCmdCallbackHandler_12b0c8`; nothing reaches it).
`scePadSetActDirect` hands the six bytes to `padman_act_direct` directly (retail: SIF DMA
into the 0x80000101 buffer). `scePadPortOpen` marks the port open only when padman
answers 1 (retail marks it after any successful RPC).

### Host interface (`padman.h`)

```c
typedef struct rg_pad_report {
    uint8_t connected, has_pressure;
    uint16_t buttons;                 /* RG_PAD_* = SCE bits, active-high */
    uint8_t lx, ly, rx, ry;           /* 0x80 centre */
    uint8_t pressure[12];             /* DS2 frame order; derived from buttons if !has_pressure */
} rg_pad_report;
void rg_pad_set_input_source(rg_pad_input_fn fn, void *user); /* pull: (port, vblank) -> report */
void rg_pad_push_report(int port, const rg_pad_report *r);     /* push: latched state */
void rg_pad_set_rumble_hook(rg_pad_rumble_fn fn, void *user);  /* (port, small 0/1, large 0..255) */
```

The host shell (src/host) owns SDL; it either pushes a report every frame or installs a
pull source keyed by VBlank (deterministic replays). Defaults: port 0 has a neutral
controller, port 1 is empty (`padman_config.default_connected`). Rumble reaches the hook
only after the game mapped the motors with `SetActAlign` (actuator 0 = small, on/off;
1 = large, 0..255), and is switched off on disconnect / close.

**Replay.** `rg_pad_script_*` reads the tools/trace input format (`first last
BUTTON[+BUTTON]`, inclusive). The script frame is `kernel vblank - offset`; to replay a
trace script written in game VBlank units (`[0x004810C4]`, which starts about 280 vsyncs
after power-on) set the offset between the two counters. Difference to the PCSX2 hook:
the hook ORs the table into the decoded word at `0x004B2574` and leaves the DMA buffer
untouched, while the port's script goes through the buffer, so the pad buffer region of a
state trace differs while a button is held (the decoded word does not).

## Memory card

### Host layout

```
<root>/card1/                 card in slot 1: PS2 directories and files as plain host ones
<root>/card1/BASCUS-97490LV5RG_00/BASCUS-97490LV5RG_00   (save data)
<root>/card1/BASCUS-97490LV5RG_00/icon.sys               (964 bytes; the game checks 0x3C4)
<root>/card1.card             metadata (text)
<root>/card1.txt              generated index of the saves (titles from icon.sys)
<root>/card2/, card2.card     card in slot 2
<root>/backups/card1/...      automatic copies of a save before it is overwritten
```

Crash-safe writes (temp file + rename on flush / close), the backups, the index, the old
`slot0` / `slot1` names (migrated on load) and `RG_MC_SLOT1` / `RG_MC_SLOT2`: [SAVES.md](SAVES.md)
section 3.

`<root>` = `mccard_config.root`, else env `RG_SAVES`, else `saves`. Names the host cannot
hold are `%XX`-escaped per byte (`< > : " / \ | ? * %`, control bytes, a trailing `.` or
space, DOS device names). The metadata file holds the formatted flag and, per entry, the
creation order, attributes and both timestamps:

```
RGMC 1
formatted 1
seq 5
E <seq> <d|f> <attr hex> <created: 8 bytes hex> <modified> <escaped card path>
```

Files that appear on the host without a record (a save dropped in by hand) are adopted
with default attributes, after the recorded ones, in name order. Records whose file is
gone are dropped. Slot policies: `MC_SLOT_AUTO` (slot 1 default: a formatted empty card is
created when the directory is missing), `MC_SLOT_IF_EXISTS` (slot 2 default: a card only
if the directory exists), `MC_SLOT_EMPTY`, `MC_SLOT_UNFORMATTED`. `mccard_eject` /
`mccard_insert` hot-plug a slot (the next `sceMcGetInfo` reports the change).

### What the game sees

| Item | Model |
| --- | --- |
| type | 2 (PS2) when a card is in the slot, else 0 |
| free | 1 KB clusters: 8000 on an empty formatted 8 MB card, minus ceil(size / 1 KB) per file and ceil(entries / 2) per directory (entries include `.` and `..`; the root's first cluster is in the 8000) |
| format | 1 / 0; an unformatted card fails every file operation with -2 until `sceMcFormat` |
| `sceMcGetInfo` result | -1 the first time a formatted card is seen (boot, insertion), then 0; -2 while unformatted; -12 with no card (the game's `McGetInfoStep_375640` needs < -10) |
| GetDir | creation order, `.` and `..` first, `*` and `?` in the last component, paged with mode 0 / 1; files: size in bytes; directories: entry count; attributes 0x8497 (file) / 0x8427 (directory) |
| times | `sceMcStDateTime` {resv, sec, min, hour, day, month, year}; libmc installs a clock that follows the virtual clock from 2006-01-31 12:00:00, so runs are deterministic (a host can install a wall clock) |
| SetFileInfo | flags 1 created, 2 modified, 4 attributes (user bits 0x380F), 0x10 rename within the directory |
| open modes | 1 / 2 / 3 read/write, 0x200 create, 0x400 truncate, 0x800 exclusive, 0x40 = mkdir; read-only attribute denies writing |
| limits | names < 32 bytes, paths < 1024, 16 open files (-7 beyond) |

Result codes: 0 ok, -1 changed card, -2 unformatted, -3 full, -4 no entry (also: mkdir of an
existing directory, rename onto an existing name), -5 denied (bad fd, wrong mode,
directory opened as a file), -6 directory not empty, -7 too many open files, -12 no card.
Issue-time codes from libmc itself: -100 not initialised, -200 busy, -210 bad name, -91 RPC
failure, and `sceMcInit` -101 / -120 / -121.

### libmc: asynchronous, as retail

- Every operation returns 0 when issued. It takes the **lock** semaphore with `PollSema`
  (busy: -200); `sceMcSync` gives it back when it collects the result. So exactly one
  operation is in flight, and a caller that never syncs blocks every later call.
- `sceMcSync(mode, &cmd, &result)`: -1 when nothing was issued; else `*cmd` = the libmc
  function number (Mkdir 11 and Rename 19 even though they travel as Open / SetFileInfo);
  mode 0 blocks on the **done** semaphore; mode 1 returns 0 while running and charges
  `poll_cycles` (2000) of virtual time so a polling loop moves the clock (SPIN.md); 1 when
  done, with `*result`.
- `sceMcInit` creates the two semaphores the first time (init 1/max 1 and 0/1), syncs,
  binds 0x80000400, sends fno 0xFE synchronously and checks the versions (mcserv 0x210 >=
  0x20A, mcman 0x226 >= 0x20E). `sceMcEnd` syncs and deletes both semaphores; afterwards
  every operation returns -200 until the next `sceMcInit` (retail behaviour; the game's
  `McPollCardChange_372db0` does Init / GetInfo / Sync / End on every poll).
- `sceMcGetInfo`'s outputs and `sceMcChdir`'s previous-directory output are written at
  completion, in interrupt context, like retail `McGetInfoCb_12d160`. Read data and GetDir
  tables are written when the server runs (the retail IOP DMAs them during the operation).
- The `slot` argument is recorded and ignored. The game passes **1** everywhere
  (`sceMcOpen(port, 1, ..)`, `sceMcGetInfo(port, 1, ..)`) and it works on retail, so the
  real mcserv cannot be rejecting it.

**Timing.** An operation completes at issue + SIF `rpc_latency` + the card time mcserv
reports: `op_cycles` (1 ms) + 2.5 ms per KB read + 6 ms per KB written; format and
unformat take `format_cycles` (2 s). The EE end function adds the card time with
`sif_post`, so it lands in the same SIF0 interrupt path. `rg_mc_config.timing = 0` drops
the card time. These defaults are placeholders until a PCSX2 trace measures the game's
load/save step timings.

### PCSX2 `.ps2` images

Implemented in `tools/saves/ps2card.py` (import / export with `.ps2` images and PCSX2
folder cards, format, verify, restore; [SAVES.md](SAVES.md) section 4). The notes below
were the starting point; the ECC layout is still unchecked against a real formatted card.

- **Image:** 16,384 pages of 512 data bytes + 16 spare bytes = 8,650,752 bytes (a
  raw 8 MiB dump without spare areas also exists). Spare area: 12 bytes of Hamming ECC
  (3 per 128-byte chunk) + 4 bytes padding. Cluster = 2 pages (1 KB); erase block = 16 pages.
- **Superblock (page 0):** magic `"Sony PS2 Memory Card Format "`, version `"1.2.0.0"`,
  page_len 512, pages_per_cluster 2, pages_per_block 16, clusters_per_card 8192,
  alloc_offset, alloc_end, rootdir_cluster, backup_block1/2, indirect-FAT cluster list
  (32 entries), bad-block list (32), card type 2, card flags.
- **FAT:** 32-bit entries reached through the indirect-FAT clusters; bit 31 = allocated,
  low 31 bits = next cluster, 0x7FFFFFFF = end of chain (with bit 31 set); clusters are
  relative to alloc_offset.
- **Directory entry (512 bytes):** mode u16 (the attribute word above), length u32 (bytes
  / entry count), created 8 bytes, first cluster u32, parent entry index u32, modified 8
  bytes, attr u32, name[32]. Entries 0 and 1 of a directory are `.` and `..`.
- **Mapping:** import walks the root, writes each directory and file under `slot<N>/`
  and records mode and times in `slot<N>.card` in directory order (which becomes the
  creation order); export formats a fresh image and writes entries in `seq` order,
  computing ECC per page. A one-save export (`.psu`/`.max`) is simpler and may be enough.

## Integration

**`src/runtime` (RUNTIME.md) does all of the following:** `mccard_init` on the saves
directory with the virtual clock, `padman_reset`, the host input source (keyed by the
VBlank) and rumble hook (`rg_host_rumble` → SDL), padman/mcserv installed **at boot**
through `iop_hle_set_post_install`, `padman_update` from its VBLANK_START observer, and
`mccard_shutdown` at exit. The notes below describe the standalone defaults.

- Nothing to call for the defaults: the first `scePadInit` / `sceMcInit` installs the
  servers (and loads the cards from `RG_SAVES` / `saves`). After a later `rg_sif_boot`, the
  next Init re-installs them (`padman_installed()` / `mcserv_installed()`).
- To configure: `mccard_init(&cfg)` (root, slot policies, card size, clock) and
  `padman_reset(&cfg)` before the game starts; `mcserv_configure`, `rg_mc_configure` for
  timing; `rg_pad_set_input_source` / `rg_pad_push_report` and `rg_pad_set_rumble_hook`
  from the host shell. `mccard_shutdown()` at exit flushes metadata (data is written
  through on every write).
- Single host thread, like the rest of the HLE: the input source and rumble hook run on
  the kernel's thread inside a libpad call.

## API changes wanted elsewhere (not made here)

- **src/ps2/iop**: `iop_hle_install` could install padman / mcserv directly (or take a
  hook), so a trace of SIF registrations matches from boot instead of from the first
  Init. Today the placeholders answer until then; nothing calls them first.
- **src/ps2/sif**: a per-call completion delay (`sif_rpc_ctx.extra_latency`) would let
  mcserv express card time itself instead of the EE end function re-posting through
  `sif_post`.
- **src/host**: feed `rg_pad_push_report` (or a pull source) from SDL3 every frame,
  map the rumble hook to `SDL_RumbleGamepad`, call `mccard_shutdown` on exit.
- **Prototype unification (ingest transform 2)**: the game declares
  `scePadSetActDirect` `void`, `scePadRead` `s32`, `sceMcRead(s32, s32, s32)` with the
  buffer as `s32`; all are ABI-compatible on i686 with `libpad.h` / `libmc.h`.
- **`PadReadData_184df0`** reads into `u8 sp30[0x18]`, and retail padman reports 32
  bytes (VALIDATION.md 4): on the EE the 8-byte overrun lands in unused frame padding
  (sp+0x48..0x4F of its 0x50-byte frame), on the host it would be stack corruption.
  **Done:** `overrides/src/main/pad/PadReadData_184df0.c` gives it a 32-byte buffer and
  changes nothing else (`tools/ingest.py --check` verifies its SHA-256 header). The
  `pad_game` test compiles the override in place of the `game/` file, as the game
  build does.

## Tests

`rg-padmc-tests <name>`; `ctest -L padmc`. Each test boots the EE kernel and SIF HLE.

| Test | Checks |
| --- | --- |
| `pad_stable` | Closed port = 99, 64-byte alignment, double open; per-VBlank state 5, 1, 2, 2, 6; port 2 DISCONN; digital InfoMode values; SetMainMode BUSY/EXECCMD for exactly `cmd_frames`, then mode 7; InfoAct (the measured actData); SetActAlign; one command at a time; `scePadRead` = 32 with `00 73 ff ff`, zeros, `5a`; the measured DMA-buffer bytes (0x28..0x72, length 0x20, numActComb 1); InfoMode CUREXOFFS / IDTABLE sources; halves alternate by one frame; close, end. |
| `pad_mapping` | Report -> frame bytes (active-low, high byte first), all 16 buttons round-trip through the game's decode, sticks only in analog, every read reports 32 bytes, pressure mode 0x79 with derived and supplied pressures, back to 0x73. |
| `pad_replay` | A script replayed twice from a fresh kernel gives the same per-frame reads, DMA buffer hash and virtual times; buttons land on their script frames; parser errors. |
| `pad_rumble` | Motors unmapped before SetActAlign; small/large reach the hook; unchanged values do not call it; unplug -> DISCONN, motors off, SetActDirect refused, replug -> FINDPAD -> STABLE digital. |
| `pad_analog_lock` | `keep_analog_lock`: boots digital (0x41) and an unplug before the lock stays digital; after `SetMainMode(1, 3)` 600 VBlanks of arbitrary buttons and stick extremes always read 0x73, locked, `PadIsAnalogMode` true; `SetMainMode(0, 2)` ignored; unplug + replug comes back STABLE 0x73 locked without a new `SetMainMode`. Control: expects the hardware power cycle (0x41) after the replug. |
| `pad_game` | The game's own `PadOpenPorts_1c6bf0` / `PadWaitReady_1849e0` / `PadUpdateConnection_184a50` / `PadReadData_184df0` (the override) / `PadUpdateVibration_184250` (compiled from `game/` / `overrides/`, skipped if not ingested) reach phase 0x63, analog + locked + aligned, START decodes to 0x0800 at `0x004B2574`, vibration reaches the hook. |
| `mc_files` | GetInfo (-1 then 0, type 2, 8000 free), Mkdir (cmd 11, -4 on repeat), create/write/flush/close, chunked read-back, seek, write on read-only fd, GetDir order/sizes/attrs/times/paging/`??` pattern, free-space arithmetic, chdir + relative names, rename (cmd 19), read-only attribute, delete (-6 non-empty), EntSpace, the host file. |
| `mc_errors` | -100 before Init, no card (-12, type 0), unformatted (-2) -> format (takes `format_cycles`) -> 0, missing file / parent, bad name (-210), busy (-200), full card (-3), handle limit (-7), eject / insert, -200 after End. |
| `mc_async` | A blocking 8 KB write completes at exactly issue + latency + op + 8 x write cost; `sceMcSync(1)` busy first; a polled GetInfo moves time by `poll_cycles` per poll, writes its output only at completion, and finishes after exactly ceil(t / poll) polls. |
| `mc_persist` | Creation order (B before A), attributes, creation time, data and a host-hostile name survive `mccard_shutdown` + `mccard_init`; free space recomputed. |
| `mc_persist_write` -> `mc_persist_read` | The same across two processes (CTest fixture). |
| `*_control` (`WILL_FAIL`) | `pad_stable` expects STABLE one VBlank after open; `pad_mapping` expects active-high bytes; `pad_replay` shifts the script by a frame and expects the same hash; `pad_analog_lock` expects digital after a replug; `mc_files` expects free space unchanged after a save; `mc_async` expects the result visible at issue; `mc_persist` reads from another root. Each fails, and only on its armed check. |

The game's save path, card states and host save files have their own tests
(`mc_card_states`, `mc_save_cycle`, `mc_full`, `mc_exact_fit`, `mc_corrupt`,
`mc_write_fail`, `mc_backup`, `mc_layout`, `mc_crash_write` -> `mc_crash_read`, `mc_game`
running the game's own save code, `ps2card` -> `mc_pyimport`): [SAVES.md](SAVES.md)
section 2.

Status 2026-10-12: 36/36 pass (25 tests, 11 controls) in `build\saves-i686`.

## Open questions (PCSX2 trace decides)

1. **Pad timings:** `find_frames`, `ctp1_frames`, `cmd_frames` (2/2/3) are guesses. The
   trace shows how many VBlanks the game's phase variable `0x004B2588` spends in 0, 0x2A
   and 0x47 after boot.
2. **Read length:** answered (VALIDATION.md 4): 32 bytes in 0x73; the `PadReadData`
   override is in place. Open: 0x41 / 0x79 lengths (assumed 32).
3. **No-card code:** -12 assumed (any value < -10 satisfies the game; with no card the
   title stops at the game's message 0xC9, [SAVES.md](SAVES.md) section 5).
4. **First GetInfo after boot:** -1 assumed for a formatted card; if retail reports 0, the
   save menu takes a different first branch (`McGetInfoStep_375640` case -1 sets format=1).
5. **Free clusters on an empty card** (8000) and the per-directory cost: compare
   `sceMcGetInfo` free before and after a save on a PCSX2 card.
6. **actData**: answered (VALIDATION.md 4, padman's values). The meaning of +0x40 and
   +0x6C is unknown; the observed bytes are written.
7. **Case:** PS2 card names are case-sensitive; Windows folders are not. Two names that
   differ only in case would collide (the game's names never do).
8. **Card timing:** op / per-KB / format costs are placeholders; measure the game's
   save and load step counts in a trace.
