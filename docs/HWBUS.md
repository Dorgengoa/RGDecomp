# Hardware register bus and the address-literal stage

PLAN.md transform 5 ("Address literals"). Two parts:

- `src/ps2/hwbus/`: the EE hardware register bus. `HW_R32`/`HW_W32` (and the 8, 16, 64
  and 128-bit forms) land here and are routed to the model that owns the register,
  through that model's public API. It also backs `PS2_SPR()` and `RG_OVL_DATA()`.
- `tools/stages/hwaccess.py`: the ingest stage that rewrites the game's literal-address
  idioms into those accessors.

| Path | What |
| --- | --- |
| `src/ps2/hwbus/hwbus.[ch]` | the router, claims table, unknown-address records, per-read charge, `hw_spr_base` |
| `src/ps2/hwbus/ovldata.c` | `rg_ovl_data_ptr` (backs `RG_OVL_DATA`) and the overlay-manager resolver hook |
| `include/port/hwaccess.h` | the spellings the stage emits: `HW_R*`/`HW_W*`, `PS2_SPR`, `PS2_PHYS`/`PS2_UNCACHED`/`PS2_UCAB`, `RG_OVL_DATA`. Freestanding, C and C++. |
| `tools/stages/hwaccess.py` | the stage (Stage interface, plus a CLI for a copy of `game/`) |
| `tests/hwbus/` | `rg-hwbus-tests`, `test_stage.py`, `stage_game.py`; CTest label `hwbus` |

CMake: `rg_ps2_hwbus` (links `rg_ps2_dmac`, `rg_ps2_gs`, `rg_ps2_vif`, `rg_ps2_sif`,
`rg_ps2_kernel`). Tests: `rg-hwbus-tests`, plus `rg_hwbus_game_e2e`, an OBJECT library
built from `game/` files run through the stage.

## The bus

### Claims table

| Range | Registers | Owner and API |
| --- | --- | --- |
| `0x10000000-0x10001FFF` | T0..T3 COUNT/MODE/COMP/HOLD | kernel: `ps2k_hw_read32`/`write32` |
| `0x10002000-0x1000203F` | IPU_CMD/CTRL/BP/TOP | IPU hook (`hwbus_set_ipu`), else a stub |
| `0x10003000-0x100030AF` | GIF_CTRL/MODE/STAT/TAG*/CNT/P3* | local; GIF_STAT is synthesised (M3P from VIF1 MSKPATH3, OPH/APATH from the GS bus owner) |
| `0x10003800-0x1000397F` | VIF0 registers | `vif_state` of `dmac->vif[0]` |
| `0x10003C00-0x10003D7F` | VIF1 registers | `vif_state` of `dmac->vif[1]`. FBRST.RST → `dmac_vif_reset`, FBRST.STC clears STAT.INT. |
| `0x10004000`, `0x10005000` | VIF0/VIF1 FIFO (128-bit) | `dmac_vif_fifo_write`; VIF1 read → `dmac_vif1_fifo_read` |
| `0x10006000` | GIF FIFO (128-bit) | `dmac_gif_fifo_write` |
| `0x10007000`, `0x10007010` | IPU out/in FIFO (128-bit) | IPU hook, else stub |
| `0x10008000-0x1000E06F` | DMAC channels, D_CTRL..D_STADR | `dmac_hw_read32`/`write32` |
| `0x1000F000`, `0x1000F010` | INTC_STAT, INTC_MASK | kernel |
| `0x1000F200-0x1000F260` | SIF MSCOM/SMCOM/MSFLAG/SMFLAG/CTRL/BD6 | `sif_reg_get`/`sif_reg_set` (BD6 stored locally) |
| `0x1000F520`, `0x1000F590` | D_ENABLER, D_ENABLEW | `dmac_hw_read32`/`write32` |
| `0x12000000-0x120010FF` | GS privileged (PMODE..BGCOLOR, CSR, IMR, BUSDIR, SIGLBLID) | `gs_read_priv`/`gs_write_priv` |

- **D_STAT.** Both the DMAC and the kernel claim it. `hwbus_claims` asks
  `dmac_hw_claims` FIRST (DMAC.md): the DMAC merges its SIS/MEIS/BEIS and SIM/MEIM bits
  with the kernel's CIS/CIM and forwards writes. The test control
  (`hwbus_debug_kernel_first`) proves the order matters.
- **Inside a range, the owning model decides.** A hole such as `0x10000040`, VIF0's
  missing BASE, or a misaligned address is unknown.
- **Widths.**
  - The GS privileged registers are 64-bit. A 32-bit access reads or writes one half;
    CSR, IMR and SIGLBLID writes are never merged with a stale half.
  - IPU_CMD/TOP are 64-bit.
  - Everything else is 32-bit. A 64-bit access uses the low word, and the high word
    reads 0.
  - 8/16-bit reads extract lanes. 8/16-bit writes read-modify-write the word without
    charging for the read.
  - FIFOs are 128-bit only. A 32-bit access to a FIFO moves nothing.
- **Read-only registers.** A write to one (VIF CYCLE, MODE, ROW, ...) is counted in
  `stats.ignored_writes`. It is not reported as unknown.
- **Unbound models.** A known owner whose model is not bound (`hwbus_bind` not called)
  is dropped, counted in `stats.unbound`, and printed once.

### Unknown addresses

- Reads return 0 and writes are dropped.
- The first access to each address prints one line (to stderr, or to the
  `hwbus_set_log` hook).
- Each address is recorded with its read/write counts, first width and last value
  written: `hwbus_unknown_count/get/total`. Nothing is ever ignored silently.

### Spin backstop (SPIN.md "(a) accessor charge")

- Every read charges `read_cycles` (default `HWBUS_DEFAULT_READ_CYCLES` = 4) through
  `ps2k_charge`, and writes charge nothing. A hardware poll loop therefore always lets
  virtual time pass, and due interrupts are delivered at the read.
- This is the backstop for the three `HW` rows of `census/spin_loops.tsv`
  (`ViBufRestartDma` ×2 and `ViBufStopDma`, all on IPU_CTRL) and for any poll the
  census cannot see.
- As in the DMAC, the charge applies only in guest-thread context outside a handler.
  Anywhere else the cycles go to `stats.uncharged_cycles`.
- `hwbus_set_read_cycles(0)` turns the charge off. `hwbus_set_charge(fn, user)` replaces
  it (used by tests).

### Wiring

`src/runtime` does this at init (RUNTIME.md "Init order", step 4).

```c
ps2k_init(&cfg);  sif_init(&sc);
dmac_state *d = dmac_create();  gs_state *gs = gs_create();
/* ... dmac_attach_vif(d, 0/1, ...), dmac_attach_gs(d, gs) as in DMAC.md ... */
hwbus_init();
hwbus_bind(d, gs);               /* VIFs from d->vif[], GS from d->gs if NULL */
hwbus_set_ipu(&movie_ipu_hooks); /* when the movie service exists */
hwbus_set_ovl_resolver(ovl_manager_resolve, mgr);
```

### Scratchpad and mirrors

- `PS2_SPR(off)` is `hw_spr_base() + (off & 0x3FFF)`. `hw_spr_base()` is the bound DMAC's
  `spr[]`, so `dmac_canon_addr` recognises those pointers as `0x8000_0000|off`. With no
  DMAC bound it is a private block, reported once.
- `PS2_PHYS(p)`, `PS2_UNCACHED(p)` and `PS2_UCAB(p)` are the **identity**. In host mode
  a DMA address is the host pointer (DMAC.md "Address mapping"), so stripping or
  setting segment bits would corrupt it. Since 2026-10-25 (D9 gate
  `native_only.addr_census`) the stage strips the game's sites to the bare operand, so
  no marker is left in compiled game code; the macros stay defined for hand-written code
  and HWACCESS.tsv lists every stripped site (rules `mask-*`).

### Overlay data (`RG_OVL_DATA`)

**2026-10-18: the stage no longer emits it.** The three MAIN sites are direct references to
the arena label (`(*(T *)((unsigned char *)D_00527020 + off))`, docs/UB-AUDIT.md
"RG_OVL_DATA"); the macro and resolver below stay for tests and any future site.

`RG_OVL_DATA(T, ovl, sym, symaddr, off)` is an lvalue,
`*(T *)rg_ovl_data_ptr("ovl", "sym", symaddr, off)`.

- **The overlay manager must resolve it.** It installs
  `hwbus_set_ovl_resolver(fn, user)`, where `fn(user, ovl, sym, sym_addr)` returns the
  host address of `sym` while `ovl` is resident, or NULL when it is not.
- **Unresolved accesses** (no resolver, or the overlay is not resident) go to a zeroed
  scratch slot and are reported once per symbol. Retail would read or write whatever
  the resident overlay keeps at that address.
- **The two MAIN sites** are both NORMAL's field-HUD work block `D_00527020` (bss
  0x00527000-0x00528200 of NORMAL; no other overlay's data/bss covers these addresses):

  | Site | Literal | Rewritten to |
  | --- | --- | --- |
  | `CharaGetControlStateMaybe_2f5320` | `*(s16 *)0x5273C2` | `RG_OVL_DATA(s16, normal, D_00527020, 0x00527020u, 0x3A2)` (the ally-suggest state) |
  | `FieldHudInitOnce_204120` | `*(s8 *)0x5273CE` | `RG_OVL_DATA(s8, normal, D_00527020, 0x00527020u, 0x3AE)` |

  Evidence: naming `config/names.txt` at 2efa6b43 (`FieldHudGetSuggestMember_203c20`:
  "+0x3A2 (D_005273C2)"; `FieldHudGetSuggestMemberPtr_203c60`: "D_005273B8 = FieldHud
  D_00527020 +0x398"). The overlay `*.symbols.txt` tables list only functions. MAIN
  already names `D_00527020` directly: `FieldHudInitOnce` and the FieldHud* tail-call
  wrappers.
- **Ranges.** The overlay data/bss ranges come from `config/<ovl>.yaml` (vram
  0x004E9E80 + the `data` subsegment start, + data + bss sizes).

## The stage (`tools/stages/hwaccess.py`)

### Scope

Compiled **game** files only. SDK and library files are left alone; they are classified
the same way as `asmexclude` (`portxform.classify_lib`: by path, or by the MAIN address
band). Asm blocks and asm functions are skipped too, because `asmexclude` cuts them.
Comments and string literals are never rewritten (the lexed view blanks them).

### Rules

| Rule | Before | After |
| --- | --- | --- |
| `hw-load` | `*(volatile T *)A` (rvalue) | `((T)HW_Rn(A))` |
| `hw-store` | `*(volatile T *)A = v` | `HW_Wn(A, v)` |
| `hw-rmw` | `*(volatile T *)A op= v` | `HW_Wn(A, (T)HW_Rn(A) op (v))` |
| `alias-store` | `#define NAME (*(volatile T *)A)` … `NAME = v` / `NAME op= v` | `HW_Wn(A, v)`; the define becomes the `hw-load` rvalue, so a missed store would not compile |
| `scratchpad` | `(T *)0x7000xxxx` | `(T *)PS2_SPR(0xxxxx)` |
| `mask-phys` | `p & 0x0FFFFFFF` | `(p)` (was `PS2_PHYS(p)` until 2026-10-25) |
| `mask-uncached` | `(p & 0x0FFFFFFF) \| 0x20000000` | `(p)` (was `PS2_UNCACHED(p)`) |
| `mask-ucab` | `p \| 0x30000000` | `(p)` (was `PS2_UCAB(p)`) |
| `mask-regex` | `((u64)((s64)x << 0x24) >> 0x24) \| 0x20000000`; `LOW28(c->phys…)` | `((u64)(u32)x)`; `(c->phys…)` |
| `native-read` / `native-write` (after the rules above) | `HW_R32/W32(T0_COUNT)`, `HW_W32(T0_MODE)`, `HW_R64/W64(GS privileged)`, `HW_W32(VIF1_FBRST)` | `rg_logic_t0_count()` / `_set_count(v)` / `_set_mode(v)`, `rg_gs_reg_r64(RG_GS_<REG>)` / `rg_gs_reg_w64(RG_GS_<REG>, v)`, `rg_vif1_fbrst_w32(v)`: the native service by name ("Native register sites" below) |
| `overlay-data` | `*(T *)A`, with A in an overlay's data/bss (MAIN files) | `RG_OVL_DATA(T, ovl, sym, symaddr, off)` |

- **What counts as hardware.** Addresses `0x1000_0000-0x10FF_FFFF` and
  `0x1200_0000-0x1200_FFFF`. The width comes from `T` (8/16/32/64). An unknown type is an
  error.
- **The mask and mirror rules are a reviewed table** (`MASK_RULES`): file symbol,
  exact operand, expected count. They are not a pattern applied blindly. In this game,
  0x2000_0000 / 0x3000_0000 / 0x0FFF_FFFF are just as often DMAtag ids (NEXT, REF), CHCR
  TAG fields or flag bits. A rule whose site count does not match is an error.
- **`LEAVE_RULES`** documents the reviewed medium/high census rows that stay:
  - `ViBufAddDma`'s `(ch & 0x0FFFFFFF) | 0x30000000` is a CHCR value, not an address;
  - the DMAtag `qwc | REF` words;
  - flag bits.
- **An overlay literal missing from `OVERLAY_SITES` is an error**, never a guess.
- **Includes and line numbers.** A changed file gets
  `/* rgp:hwaccess */ #include "port/hwaccess.h"` followed by `#line 1`, so presumed
  line numbers (and the census line numbers) do not move.
- **Idempotent.** The CLI re-applies the stage to every changed file and fails if
  anything changes.
- **Every rewrite is logged:** `HWACCESS.tsv` (file, presumed line, symbol, rule,
  address, before, after).
- **`report()` reconciles the log with `census/addr_literals.tsv`.** Every game row
  must come out rewritten, inside asm (cut), or left with a reason. The CLI also writes
  `HWACCESS_census.tsv` with each row's disposition.

### Result on 2efa6b43

`out/hw-test/game`, 2026-10-11:

- **84 rewrites in 31 files, 0 errors:**
  - hw-load 23, hw-store 19, hw-rmw 1, alias-store 5;
  - mask-phys 25, mask-uncached 3, mask-ucab 2, mask-regex 4;
  - overlay-data 2.
- **176 census game rows:**
  - 80 rewritten;
  - 7 in asm (`GfxVblankStartHandler`, `Vif1IntcHandler`, `VecWrapAngle`; cut by
    `asmexclude`; their overrides must call `HW_*`);
  - 89 left: 78 low-confidence tag ids, flags, colours and limits, and 11 reviewed
    `LEAVE_RULES` rows.
- **`clang -fsyntax-only`** on all 31 changed files (D2 flags, PORT-HEADERS.md include
  order): 0 errors before, 0 after.
- **2 SDK/library files** carry matching literals and are skipped:
  `sdk/KernelReleaseAlarm_4473a0.c` and the sdremote-island
  `SdRemoteInitMasterVolume_165608.c`.

### Registration (for the integration step; `tools/ingest.py` is not edited here)

Register it **last, after `spin`**. Spin matches loop headers textually, and the IPU
polls are loop conditions.

```python
import hwaccess                                   # tools/stages/hwaccess.py
def make_stages():
    ...
    hw = hwaccess.HwAccessStage()                 # reads census/addr_literals.tsv
    return [ ..., Stage("spin", sp.apply, ("unit",), sp),
            Stage("hwaccess", hw.apply, ("unit",), hw) ]
```

- **What ingest then picks up:**
  - `hw.extra_outputs()` gives `{"HWACCESS.tsv": ...}`, the generated MANIFEST row;
  - `hw.report()` gives the summary and the census reconciliation;
  - `hw.errors` makes ingest exit 1;
  - `hw.stats` gives the per-rule counts.
- **Link `rg_ps2_hwbus` into the game executable.** `include/port/hwaccess.h` is
  reached through the existing `-I include`.
- **Alternative to the per-file include:** add `#include "port/hwaccess.h"` to
  `include/port/prelude.h` (it is freestanding). The stage's include line is then
  harmless (include-guarded).

Standalone, on a copy:

```
python tools/stages/hwaccess.py --game game --out out/hw-test/game [--changed list.txt]
python tools/stages/hwaccess.py --game game --one game/<rel> OUT.c     # one file
```

### Native register sites (D9, 2026-10-25)

The registers a native service owns are not reached through `HW_*` in game code: the stage's
last pass (`NATIVE_REGS`, `native_read` / `native_write`) turns them into direct calls.
`T0_COUNT` / `T0_MODE` -> `rg_logic_t0_*` (native logic time, NATIVE-CPU.md section 8); the
GS privileged registers -> `rg_gs_reg_r64 / w64(RG_GS_<REG>)` by register id (the slot in the
renderer's register block: `RG_GS_PMODE` 0 ... `RG_GS_BGCOLOR` 14, `RG_GS_CSR` 16 ...;
`include/port/hwaccess.h`), defined by `src/native/render/nr_hw.c` in native-only builds and by
`hwbus.c` (over the bus) in the oracle twin; `VIF1_FBRST` -> `rg_vif1_fbrst_w32`. The address
forms (`rg_gs_priv_r64 / w64`) stay for libgraph. Game files: GsDbufPutEnv_144150,
SysInitHardware_15e670, Vif1IntcHandler_15e170, GfxEndFrame_141c20, GfxFlipBuffersMaybe_143650,
GfxSysInit_15dd20 (+ the GfxVblankStartHandler_15df20 override by hand).
`tools/native/addr_census.py --check` (ctest `native_only.addr_census`) fails on any `HW_*`,
hardware / scratchpad literal or identity marker left in the compiled set.

## Tests (`tests/hwbus`, `ctest -L hwbus`)

| Test | Checks |
| --- | --- |
| `claims` | The owner of every region, D_STAT → DMAC first, holes, misaligned and unclaimed addresses → unknown. |
| `kernel` | T0_MODE/T1_COMP/INTC_MASK through the bus land in `ps2k` (toggle semantics), and 8/16-bit reads. |
| `dmac` | D_CTRL; D4 MADR/QWC (16-bit mask); the D_ENABLEW/R sequence; D_STAT merge and the w1c split between kernel (CIS) and DMAC (BEIS, SIM toggle); MovieOpen's `\|=` RMW. |
| `fifo_vif_gif` | VIF1 FIFO MARK → VIF1_MARK; VIF0 FIFO STCYCL → VIF0_CYCLE; VIF1_FBRST.RST → `dmac_vif_reset` (MSKPATH3 and GIF_STAT.M3P cleared); STC clears STAT.INT; a read-only write is ignored; a GIF FIFO A+D packet sets GS FOGCOL. |
| `gs_priv` | PMODE 64-bit, SysInitHardware's 64-bit RMW, 32-bit halves, CSR w1c, IMR. |
| `sif` | SMFLAG after boot, MSCOM, MSFLAG set and SMFLAG clear semantics, BD6. |
| `ipu` | The stub (BUSY reads 0, RST) and hooked IPU registers. |
| `unknown` | Reads return 0, writes are dropped, logged once per address, and the records (counts, width, last value, total). |
| `spin_charge` | Hook: reads charge, writes don't, configurable/off. Outside a thread → uncharged. In a guest thread: exactly 4 cycles per read on the real clock, and a T0_COUNT poll loop terminates. |
| `spr_ovl` | `PS2_SPR` → `dmac->spr` (and `dmac_canon_addr` → 0x8000_0040), identity mirrors, an unresolved `RG_OVL_DATA` round trip. |
| `dstat_order` | D_STAT BEIS read and cleared through the DMAC. |
| `game_e2e` | Game files from `game/` run through the stage and compiled like game code: `ViBufSetD4Chcr` (D_ENABLEW CPND around the CHCR store), `ViBufStopDma` (saves D4/D3/IPU registers, IPU_CTRL poll), `ViBufDelete`, `ViBufGetFifoIndex` (the mask is the identity on a host address above 0x0FFF_FFFF, where retail's mask would break), and `FieldHudInitOnce` (its `RG_OVL_DATA` store lands at NORMAL `D_00527020`+0x3AE through a resolver). |
| `stage_unit` | `test_stage.py`, 14 fixture tests: load/store/rmw, nesting, widths, alias defines (CRLF), comments/strings/asm/flag values untouched, SDK path and SDK band untouched, `#line` kept, scratchpad, overlay sites, an unmapped overlay literal → error, overlay range exclusivity, table/regex/UCAB rules, CHCR left, rule count mismatch → error, idempotence. |
| `stage_game` | `stage_game.py`: the stage over a copy of `game/` (`out/hw-test/game`). 0 errors, every census row accounted for, idempotent, no new clang errors in the 31 changed files, and no hardware dereference or MAIN overlay literal left outside asm. |
| `dstat_order_control` (`WILL_FAIL`) | `hwbus_debug_kernel_first`: the kernel is asked first, so BEIS is lost. It fails, as it must. |
| `stage_unit_control` (`WILL_FAIL`) | Alias defines are ignored, so the alias test fails. |
| `stage_game_control` (`WILL_FAIL`) | Alias defines are ignored, giving 5 new clang errors ("expression is not assignable": `GS_PMODE =` and `T0_COUNT =`). This proves the syntax check is armed. |

Build and run (2026-10-11, 17/17 pass):

```
build\hw-i686  (cmake ... -DRG_HOST=OFF, toolchain-i686-windows-clang)
ctest --test-dir build\hw-i686 -L hwbus
```

## Deviations

- **No IPU model.** The stub makes IPU_CTRL.BUSY and IPU_CMD.BUSY read 0 and
  `RST` clear it, so the movie code's polls end. Commands go nowhere. The movie layer
  is being replaced (MVI.md); a service can take the registers with `hwbus_set_ipu`.
- **VIF_STAT is partial.** It has VPS (busy if a command is partly received), DBF and
  INT; FQC/FDR/VEW/VGW/MRK/ER read 0. VIF FBRST.FBK/STP have no effect, because the
  model never stalls.
- **GIF_CTRL.RST** calls `gs_gif_reset` (path tag/packet state and queues; registers
  and VRAM untouched). Until 2026-10-12 it had no effect. PSE is stored and
  reflected in GIF_STAT. GIF_TAG*/CNT/P3* read 0.
- **SIF BD6** is plain storage.

## API requests (other modules, not changed here)

- **GS:** `gs_gif_reset(gs)` for GIF_CTRL.RST. Done 2026-10-12.
- **VIF:** a public `vif_read_reg(v, idx)` / `vif_write_reg(v, idx, val)` with the STAT
  bits (FQC, FDR, VEW/VGW, MRK). The bus reads `vif_state` fields directly for now.
- **Movie / IPU:** an IPU service that installs `hwbus_ipu_hooks` (registers + FIFO).
- **Overlay manager:** install `hwbus_set_ovl_resolver`. Resolve `normal:D_00527020`
  to NORMAL's bss block while NORMAL is resident (PLAN.md transform 7).
- **Overrides** for the asm-cut `Vif1IntcHandler_15e170` (T0_COUNT read,
  VIF1_FBRST.STC) and `GfxVblankStartHandler_15df20` (GS CSR) should use
  `HW_R32/HW_W32`/`HW_R64`.
- **Kernel:** none. `ps2k_hw_*` and `ps2k_charge` are enough.
