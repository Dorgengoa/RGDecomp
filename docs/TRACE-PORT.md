# Port-side state trace (`src/trace`)

PLAN.md "Verification", state-trace lockstep: the port records the same per-VBlank region
hashes as the PCSX2 harness (`tools/trace`, its README), in the same TSV format, so
`trace.py compare --key vbl` finds the first VBlank where the port and PCSX2 differ and
names the variables. The game isn't linked yet, so the recorder is built to work the
moment it links, and runs today against `rg-runtime-demo` with synthetic symbols.

All of it is original CC0 code.

| Path | What |
| --- | --- |
| `src/trace/rg_trace.h` | API: hash, address map, regions, recorder, runtime glue |
| `src/trace/blake2b.c` | BLAKE2b (RFC 7693) |
| `src/trace/trace_map.c` | PS2 address ↔ host address map |
| `src/trace/trace_regions.c` | region-file and port-config parsers, the bytes each region hashes |
| `src/trace/trace_rec.c` | the recorder (TSV writer, cadence, stop, fault control) |
| `src/trace/trace_runtime.c` | runtime glue: `RG_TRACE_*` environment, VBlank observer; `RG_TIMING` (the timing record's service hook) |
| `src/trace/timing.c`, `rg_timing.h` | the timing record (probe.py's JSONL schema), docs/TIMING-LOCKSTEP.md |
| `src/trace/demo/trace_demo_syms.[ch]` | synthetic symbols for `rg-runtime-demo` |
| `tools/trace/gen_port_symtab.py` | generates the game's symbol table (`&D_xxxxxxxx`) |
| `tools/trace/port_regions.cfg` | port annotations: pointer slots, exclusions (determinism hygiene) |
| `tools/trace/port_trace.py` | run the port exe headless and compare against a golden |
| `tests/trace/` | `rg-trace-tests`, `xcheck.py`, `demo_e2e.py`, `test_port_tools.py`; CTest label `trace` |

CMake targets: `rg_trace_core` (no runtime), `rg_trace` (glue, needs `RG_HOST`),
`rg_trace_demo`, `rg_trace_symtab_game` (OBJECT, generated; only the game exe links it),
`rg-trace-tests`.

## Format: what must match `trace.py` exactly

| Item | PCSX2 side (`trace.py`) | Port side |
| --- | --- | --- |
| Hash | `hashlib.blake2b(data, digest_size=8).hexdigest()` | `rg_trace_hash_hex`: BLAKE2b with **outlen 8 in the parameter block** (not a truncated 64-byte digest; the `hash_xcheck_control` test proves the difference is caught) |
| Row | `frame\tregion\thash` | same |
| Pseudo rows | `@cycle` (`%08x` EE cycle), `@vbl` (decimal u32 at 0x004810C4), first, then regions in file order | `@cycle` = low 32 bits of the kernel's virtual bus cycle; `@vbl` = the game counter through the address map |
| `frame` | power-on vsync index (`FrameClock`) | kernel field index (`ps2k_vblank_count() - 1`). Port and PCSX2 frames are not comparable: compare with `--key vbl` |
| Region names | `sym:<Name>`; chunked `name@%08X` | same (same parser grammar: `include`, `0x`/`0o`/`0b`/`_` numbers, chunk tails) |
| Range bytes | `ee[a:b]`, clipped at 32 MB | same, through the address map |
| Deref `*PTR[+OFF] size` | `p = u32[PTR] & 0x1FFFFFFF`; null or `p+OFF+size > 32 MB` → hash of `"ptr:%08x" % p` | see "Pointers" |
| `iop` / `spr` regions | IOP RAM, scratchpad | no row (an `# unmapped` note) |
| Metadata | `#` lines | `# port`, `# regions`, `# portcfg`, `# input`, `# ptrmode`, `# every`/`# keys`, `# key` (what the vbl comes from), `# unmapped`, `# note`, `# fault`, `# gamemode-change`, `# overlay` (id only), `# stop`, `# samples`, `# port-stats` |
| Emit cadence | rows when `frame % --emit-every == 0` (power-on frames) | rows when `vbl % RG_TRACE_EVERY == 0`, or exactly the vbls in `RG_TRACE_KEYS` (`port_trace.py --keys-from golden.tsv` writes it). `compare --key vbl` keeps the first sample of each vbl and drops vbl 0 |

Cross-checks: `trace.hash_xcheck` (C hash == `trace.h` on 16 buffers, 0 to 1 MB) and
`trace.image_xcheck` (the recorder over a synthetic 32 MB EE image == `trace.py`'s own
`load_regions`/`region_bytes`/`h`, row for row, and `trace.py compare` parses the port
file and reports IDENTICAL).

## Sample point

The glue adds a kernel VBlank observer (`ps2k_add_vblank_observer`, after the runtime's
own). It samples at **VBLANK_START, at the event's exact virtual time, before any game
handler for it runs**. PCSX2 samples at the same instant: its CPU thread is frozen in
the frame limiter inside vsync handling, before the VBLANK_START interrupt reaches the
EE. So on both sides the game counter has not been incremented for this VBlank yet. The
observer may run on a guest fiber; it only reads memory and writes the file.

**Key.** The vbl is the u32 at `RG_TRACE_VBL_ADDR` (default 0x004810C4,
`GfxVblankStartHandler_15df20`'s counter) when the address map covers it; otherwise the
kernel field index, and the trace says so in a `# key` line. Before the game links,
the key is the kernel count.

**Input keying (resolves the RUNTIME.md `cfg.game_vblank` TODO for traced runs).**
`rg_trace_apply_env` sets `cfg.game_vblank = rg_trace_game_vblank`, which returns the
game counter **+ 1** (`RG_TRACE_INPUT_LEAD`). padman builds the frame's report at
VBLANK_START, before the handler increments the counter; the game decodes it later in
that frame, when the counter is one higher. `input.py`'s hook ORs `table[counter]` at
decode time. So the report built at VBLANK_START must carry the word for `counter + 1`.
The demo shows the effect: two scripts that differ from vbl 71 diverge at exactly vbl 71.
Re-verify the lead on the game: PCSX2's `Pad0` row against the port's at the first
scripted press.

## Address map

PCSX2 regions are EE addresses. On the port the bytes live in three kinds of host
memory. `rg_trace_host_ptr` / `rg_trace_read` (forward) and `rg_trace_ps2_addr`
(reverse) try them in this order:

1. **Symbols**: PS2 range → host object. These are MAIN `.data`/`.bss` (`D_xxxxxxxx`),
   which are host statics.
   - The game table is generated: `gen_port_symtab.py` writes `extern char D_x[];` and
     `{0x..., size, D_x, "D_x"}` for every data symbol the `sym:` regions touch, plus the
     VBlank counter, `GameModeStack` and `LoadedOverlayId`. The game's data symbols have C
     linkage (the devirt stage), so `&D_x` links from C.
   - CMake builds it into `rg_trace_symtab_game` from `regions_golden.cfg` + `game/src`
     whenever `game/` is present. The game exe links that object and calls
     `rg_trace_register_game_symtab()` before `rg_trace_apply_env`.
   - At 2efa6b43 it yields 55 symbols and 0 gaps for the 42 `sym:` regions.
   - **Sizes.** With `--src`, a symbol covers up to the next `D_` name referenced
     outside comments (the same boundary rule as `gen_regions.py`'s `auto`). It is clipped
     at the overlay arena and the heap. This assumes each host object is at least that
     long, which holds when data2c keeps the retail layout (its `sizeof` checks). When the
     data snapshot lands, pass its symbol list with `--symbols` (`addr name size`). Real
     sizes then turn a hole into a `gap` row (in the `.tsv` next to the C file), and the
     recorder skips that region with an `# unmapped` note rather than reading a
     neighbour.
   - Tests and the demo add symbols at run time (`rg_trace_add_symbol`). Overlapping
     ranges are refused.
2. **Overlay arena** [0x004E9E80, 0x00528200): the bound overlay registry's arena
   (`rg_ovl_bound()`, OVERLAY.md §3). Labels are at their retail offsets, so arena
   addresses map 1:1. `rg_trace_set_arena` overrides it (tests).
3. **RAM block**: the crt0 32 MB block (host base = PS2 address 0), mapped only from the
   heap start 0x00528200 up. The game's heap (`sbrk` from 0x00528200) is there at its
   retail addresses. Below the heap start the block is unused (statics live in host
   objects), so those addresses are deliberately unmapped instead of hashing zeros.

An address no mapping covers is **unmapped**. The recorder then writes no row for that
region (an `# unmapped <frame> <region> <reason>` note, once). `compare` only judges
regions present in both traces, and reports the rest as "regions only in A".

## Pointers

On i686 a pointer stored in game memory is a 32-bit **host** address. PCSX2 stores PS2
addresses. The recorder handles both:

- **Deref regions (`*PTR+OFF size`), host mode (default).**
  - Read the u32 at PTR through the map.
  - 0 → hash `"ptr:00000000"`, the same as PCSX2's null marker.
  - Otherwise reverse-map `value + OFF` to a PS2 address and read the region through the
    map. The bytes are the same, and a read that spans objects stays safe.
  - If the reverse map misses but the host memory is readable (Windows `VirtualQuery`),
    read it raw, with a `# note`.
  - If it isn't readable, hash `"ptr:?%08x"`, a marker PCSX2 never produces, so the
    region diverges visibly.
  - PCSX2's "pointer past RAM" marker has no host equivalent.
- **`ps2ptr <region>`** (port config) or `RG_TRACE_PS2PTRS=1`: the stored value is a PS2
  address (a raw number the port kept, e.g. OVERLAY.md open issue 1's raw arena words).
  The PCSX2 rule applies exactly: mask, null/past-RAM marker, read through the forward
  map. The image cross-check runs in this mode.
- **Pointer slots: `ptrs <region> <off>,...`** (port config). After gathering the bytes,
  each listed 32-bit host pointer is replaced by its PS2 address (reverse map) before
  hashing. Then a pointer field hashes like PCSX2's.
  - Static targets translate exactly (`GameDataPtr` → `D_004B8B30`).
  - Heap targets translate exactly **if** the port's heap layout matches retail (same
    allocations, same sizes, same order).
  - Arena targets translate exactly.
  - Untranslatable values are left as is, counted (`untranslated` in `# port-stats`),
    and noted once.
- **Function pointers and vtables** have no reverse map yet: a host code address is not
  in any mapping. Regions holding them stay `pending` (below). The overlay registry's
  function tables plus a generated MAIN function table (`&FUN_x`) would be the next step.
- **x64 (P7):** a 32-bit field cannot hold a host pointer. Host-mode derefs then hash
  the `ptr:?` marker. The trace needs real struct types first (PLAN P7).

## Determinism hygiene: what cannot match

| State | Why it can't match PCSX2 | Handling |
| --- | --- | --- |
| EE cycle `@cycle` | the port has no EE cycle timing (guest code costs no virtual time; `kcall_cycles` 0) | never judged (`compare` skips `@`-rows; `--key vbl` drops it) |
| Coarse RAM chunks `ram@`, `ram4m@` | MAIN code bytes don't exist; statics are host objects; RAM below the heap is unused | `exclude`; `--only '^sym:'` |
| EE stack 0x01FD0000–0x02000000 | guest threads run on host fibers with host stacks | not a `sym:` region; inside the excluded chunks |
| IOP RAM, scratchpad (`iop`, `spr`) | the IOP is HLE (no IOP code or RAM image); the scratchpad isn't EE address space | unmapped on the port; `exclude` |
| Overlay arena text range (`overlay`) | zeros on the port (OVERLAY.md open issue 7); the region also runs into the heap | `exclude` |
| PCSX2's input hook (0x000F0000 trampoline, patched `PadReadData_184df0` at 0x184E58) | PCSX2-only code patch | inside excluded chunks |
| `VblankWaitFlag` | set only while the main thread waits in `WaitVsyncCount`; on PCSX2 a heavy frame lags, the port never does | `exclude` |
| Lag frames in general | PLAN.md: lockstep needs "same VBlank count per logic frame". A PCSX2 frame that takes 2 vsyncs shifts every later logic state by one vbl | not filterable; it shows up as a divergence in everything at once. The `# gamemode-change` lines and `compare`'s per-region first-divergence list localise it |
| DMA/GIF packet buffers, libpad/padman buffers, sound buffers | host-library implementations; timing-dependent contents | not `sym:` regions; `Pad0`/`Pad1` are `pending` |
| Structs with vtables, function pointers or heap pointers | host addresses | `pending` until their slots are declared and heap parity is confirmed |

`tools/trace/port_regions.cfg` holds the curated list. `exclude` lines are never judged;
`pending` lines are judged only with `--strict`.

**Judged by default:** VblankCount, LoadedOverlayId, SysMode, SysModeNext,
GameModeStack, GameModePhaseStack, DataSetLang, RandState, TaskStateDepth, GameDataPtr
(slot-translated), SkillTimers, SkillSlots, TimerAccumA/B, TitleMenuSel,
TitleMenuOpened, TitleCounter, SaveExists.

**Pending:** GameMgrPtr, PartyPtr, CharaListHost, EventScenePtr, Party, GameScene,
Camera0-5, TaskTable, GameData, ActionMgr, EventContext, SystemVm, MenuStateMachine,
HeapA/B, HeapNpcData, Pad0/1.

The default compare is `--key vbl --only '^sym:' --ignore <exclude|pending>`
(`port_trace.py compare`).

## Running

The recorder is driven by environment variables (`rg_trace_config_from_env`). An exe
supports them by calling `rg_trace_apply_env(&cfg)` before `rg_runtime_init`. The game
exe will do that after `rg_trace_register_game_symtab()`. `rg-runtime-demo` does it
under `RG_WITH_TRACE`: `src/trace/CMakeLists.txt` defines it and links `rg_trace_demo`.
Two small guarded blocks in `runtime_demo.c` (an include and the call) are the only change outside `src/trace`.
The glue itself uses only public APIs (a service hook and a kernel observer).

| Variable | Meaning |
| --- | --- |
| `RG_TRACE_OUT` | TSV path; enables tracing |
| `RG_TRACE_REGIONS` | region file (required) |
| `RG_TRACE_PORTCFG` | port config (`ptrs`, `ps2ptr`) |
| `RG_TRACE_INPUT` | input script (`input.py` format) → `cfg.input_script` unless the exe set one |
| `RG_TRACE_EVERY` / `RG_TRACE_KEYS` | cadence: vbl multiple / file of vbls |
| `RG_TRACE_STOP_VBL` / `RG_TRACE_FRAMES` | stop at game vbl V / after N samples (`rg_runtime_request_quit`) |
| `RG_TRACE_VBL_ADDR` / `RG_TRACE_VBL_KERNEL=1` | counter address / force the kernel count |
| `RG_TRACE_INPUT_LEAD` | `game_vblank` lead (default 1, see "Sample point") |
| `RG_TRACE_PS2PTRS=1` | treat every stored pointer as a PS2 address |
| `RG_TRACE_FAULT=addr:vbl[:xor]` | deliberate-fault control: XOR a byte at the first sample with vbl ≥ V (default xor 1) |
| `RG_TRACE_HEADLESS=0` | keep the window (default: headless, unthrottled) |

```
# against a PCSX2 golden (once the game links)
python tools/trace/port_trace.py check tools/trace/goldens/newgame_battle.tsv \
    --exe build/i686-windows/rogue-galaxy.exe --out .tools/run/port.tsv \
    --regions tools/trace/regions_golden.cfg \
    --input tools/trace/goldens/newgame_battle.input.txt
#   = run (RG_TRACE_KEYS from the golden's vbls, stop at its last vbl) + compare

# the demo pipeline today
python tools/trace/port_trace.py run --exe build/trace-i686/src/runtime/rg-runtime-demo.exe --demo \
    --regions tests/trace/data/demo_regions.cfg --portcfg tests/trace/data/demo_port.cfg \
    --input tests/trace/data/demo_input.txt --stop-vbl 300 --out .tools/run/demo.tsv
python tools/trace/port_trace.py compare A.tsv B.tsv --portcfg tests/trace/data/demo_port.cfg
```

`port_trace.py compare` calls `trace.py`'s own `compare` (shared code, unchanged), so
the report reads the same as PCSX2-vs-PCSX2: first divergent vbl, the `sym:` names
there, and each region's first divergence. `--strict` judges `pending` too, `--only ''`
judges every region, and `--ignore RE` adds to the ignore list. `trace.py` itself was
not modified.

## Demo (until the game links)

`trace_demo_syms.c` registers the demo guest's result globals at made-up PS2
addresses (`tests/trace/data/demo_regions.cfg`):

| Region | Host | Shows |
| --- | --- | --- |
| `sym:VblankCount` @0x004810C4 | `fields_done` | the game-counter key path (the demo's main increments it after each `sceGsSyncV`) |
| `sym:DemoPadWords` | `pad_word[4096]` | input-dependent state |
| `sym:DemoPadReads`, `DemoGfxFrames`, `DemoPadStable` | counters | per-frame state; `DemoPadStable` is excluded in `demo_port.cfg` |
| `sym:DemoPtrs` (`ptrs 0,4,8`) | `void *[3]` = `&pad_reads`, a 64-byte `rg_crt0_sbrk` block, NULL | slot translation → 0x00502000, 0x00528200, 0 |
| `sym:DemoPadReadsVia` `*0x00502100` | host-pointer deref | equals `DemoPadReads` |
| `sym:DemoHeap` `*0x00502104`, `sym:DemoHeapDirect` 0x00528200 | RAM block | deref and direct address agree |
| `sym:DemoNull` | null deref | `ptr:00000000` |
| `sym:DemoUnmapped` (MAIN text), `iop` | none | `# unmapped` notes, no rows |

A 300-vbl demo trace takes about 1 s.

## Tests (`ctest -L trace`)

11 tests: 8 checks and 3 controls. All pass on `build/trace-i686` (2026-10-12), and
`ctest -L runtime` still passes 13/13 with the hook compiled into the demo.

| Test | Checks |
| --- | --- |
| `deref` | Forward and reverse map across symbols, arena and RAM block (gaps and below-heap unmapped). Overlapping symbol refused. Host-pointer deref through the map, null marker, unreadable marker `ptr:?00000012`, raw read outside the map with a note. `ps2ptr` region. Slot translation (static, heap, NULL, untranslatable left as is). A span across a gap and an `iop` region unmapped. The same through the recorder: rows, `# unmapped`, `# note`, stop-vbl. |
| `parse` | `trace.py` grammar: chunks with a short tail, `1_000`, `0o`, `0b`, `include` relative to the file, `spr`, deref with an offset. Python's rejection of `010`. Port-config errors (unknown region or keyword, `ptrs` without offsets). |
| `symtab_gen` | `gen_port_symtab.py --symbols` fixture → C, compiled and linked against stand-in `D_` definitions. Lookups hit the right host objects, a size is clipped at the arena, non-`sym:` regions are not taken. |
| `hash_xcheck` | C hash == `hashlib.blake2b(digest_size=8)` for 16 buffers |
| `image_xcheck` | 18 rows from the C recorder == `trace.py` row for row over a 32 MB image: chunked, empty, clipped-at-32 MB, valid/null/past-RAM/kseg0/exact-end derefs, `iop`/`spr` skipped by both. `trace.py compare` reads the port TSV: IDENTICAL. |
| `tools_unit` | `port_regions.cfg` names exist; every `sym:` region matches at most one exclude/pending rule; default vs `--strict` ignore sets. Golden vbls 20..25040. Generator gap reporting. On `game/src`: 0 gaps, nothing inside the arena, one `extern` per row. |
| `demo_pipeline` | Two `rg-runtime-demo` runs (same script) are IDENTICAL by vbl. Stop at vbl 300, keyed by the game counter, the unmapped notes. Slot translation, deref, null and heap hashes recomputed in Python. |
| `demo_fault` | `RG_TRACE_FAULT` at vbl 150 is reported as FIRST DIVERGENCE at vbl 150, symbols differing: DemoPadWords. A script that differs from vbl 71 diverges at vbl 71 in DemoPadWords. A fault in the excluded `DemoPadStable` is IDENTICAL under the port config, but `trace.py compare` without it reports vbl 150 DemoPadStable. |
| `hash_xcheck_control` (`WILL_FAIL`) | Expects the first 8 bytes of a 64-byte BLAKE2b digest: all 16 differ |
| `image_xcheck_control` (`WILL_FAIL`) | One perturbed expected row: reported at `sym:Kseg` |
| `demo_fault_control` (`WILL_FAIL`) | Golden vs the faulted run, required to match: compare exits 1 |

## Open items

1. **Lag frames.** The biggest expected source of false divergence. The port never
   lags; PCSX2 does during loads and heavy scenes (the README already sees the counter
   lag the vsync count by 1–2 near the battle load). If the game paces logic by its
   counter, both sides still see the same logic per vbl. If it paces by
   `WaitVsyncCount`, the port needs a cost model first.
2. **Input lead.** The +1 is reasoned, not yet measured against PCSX2's `Pad0` rows.
3. **Pending regions.** Their pointer slots need auditing (struct layouts from the
   `main-headers` work), and heap parity needs confirming. SDK allocations that retail
   made from the game heap but host libraries don't would shift every heap address.
   The first `PartyPtr` comparison will tell.
4. **Function pointers / vtables:** a reverse map for code (generated MAIN function table
   plus the overlay registry's function maps).
5. **Symbol sizes:** switch `--src` to `--symbols` from the data snapshot when it lands.
6. **`# overlay` lines** carry the id only (PCSX2 adds the file name from
   `D_0044AF90`, whose words are raw PS2 string addresses on the port).
