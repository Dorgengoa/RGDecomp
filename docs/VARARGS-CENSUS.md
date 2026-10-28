# Varargs census: EE 64-bit slots vs i686 4-byte slots

Census taken 2026-10-12 of the generated `game/` tree, read-only. The per-argument table is
`out/varargs-census.tsv`. The scripts are in `out/varargs/`:

- `cands.py` and `cands2.py` pick the candidate files.
- `astscan.py` runs the clang AST scan.
- `analyze.py` builds the read models, does the slot walk and writes the TSV.

The scan is of the tree as regenerated at 17:29. That ingest already carries the new protos
rule `vararg-narrow` (`tools/stages/protos.py`). The rule is described under "Proposed
generic rule" below.

## Background

Both mwcc and gcc 2.9 on the EE pass every variadic argument in one 64-bit GPR or stack
slot. A `va_arg(ap, s32)` reads the low word of its slot. That word is the value for any
`s32`/`s64`/pointer argument, so the EE never mis-aligns.

i686 cdecl pushes 4 bytes for an int, pointer or float, and 8 bytes for `s64`, `u64` or
`double`. After any 8-byte argument read as 4 bytes, every later read is off by 4. The
reverse also shifts: a 4-byte argument read as 8 bytes (`%lld`, `%f`).

## Method

1. **Candidate files.** These are compiled game files (from
   `build/clean-i686/compile_commands.json`) that name a function declared variadic
   anywhere: in game/src, in `game_protos.h`, `crt.h` or `libsif.h`. Excluded printf-family
   and sceOpen names were added. 375 files.
2. **AST scan.** Each candidate is compiled with its own compile command, plus
   `-fsyntax-only -Xclang -ast-dump`. For every `CallExpr`, the scan records:
   - the callee;
   - the caller's view of the callee type;
   - the static type of each argument after conversion: the parameter type for fixed
     parameters of the view, and the default-promoted type in the `...` part;
   - for casts, the type of the operand.

   Lines are mapped back through the protos preamble's `#line 1`.
3. **Read models.** Each callee's model is one of:
   - **count-driven**: SoundSendCmd and SoundRpcCall read `count` × `s32`. `count` is the
     literal second argument.
   - **fixed**: each SoundIopSendCmd* reads N × `int`, and `sceSdRemote_1229e8` reads 6 ×
     `unsigned`.
   - **printf**: Sprintf, Fprintf, DbgPrintf and scePrintf read according to their format.
     The format is a string literal, or a `D_xxxxxxxx` resolved from the retail images:
     `SCUS_974.90` segments, or `BIN/<OVL>.BIN` at 0x004E9E80 for `insect_`/`normal_`/...
     symbols. A `char *` data word is followed to its string. Format widths are those of
     the MSVC UCRT on i686: `%d %c %x %s %p` are 4 bytes, `%f`-family are 8, and
     `%lld`/`%I64d` are 8.
4. **Slot walk.** Arguments are paired with reads by ordinal, which is EE semantics, and
   each pair is classified. The i686 effect comes from the byte offsets: which pushed
   argument each read actually lands on.

## Variadic functions

### Defined in game code (17, all compiled; 4 files hand-walked by `gccvarargs`)

| Function | Fixed | Reads |
| --- | --- | --- |
| `SoundSendCmd_1b6cc0` | `(s32 cmd, s32 count, ...)` | `count` × `va_arg(s32)`; count > 10 returns -1 |
| `SoundRpcCall_1bc5e0` | `(s32 fno, s32 count, ...)` | `count` × `va_arg(s32)`; count >= 16 returns 0 |
| `SoundIopSendCmdG{0..3}S*_1656b8..166020` (14) | `(int a0, ...)` | a fixed N × `va_arg(int)`: G0S2 4, G0SA 3, G1S0 5, G1S1 1, G1S2 3, G1S3 2, G2S0 3, G2S1 1, G2S2 3, G2S3 1, G3S0 2, G3S1 1, G3S2 8, G3S3 2 |
| `DbgPrintf_15e780` | `(s32 fmt, ...)` | `va_start` → `Vprintf_138e68` → host `vprintf`: driven by the format |

### Providers and SDK used by game code (handled outside game/)

| Name | Provider | Reads |
| --- | --- | --- |
| `Sprintf_1343b8` | `src/crt/crt_libc.c` → host `vsprintf` | format |
| `Fprintf_12f9a0` | `src/crt/crt_libc.c` → host `vfprintf(stderr)` | format |
| `sceSdRemote_1229e8` | `src/sce/sif/game_names.c` | always 6 × `va_arg(unsigned)`, unused words ignored by the command |
| `Vprintf_138e68` | `crt_libc.c` | takes a `va_list`; not variadic |
| `scePrintf_119288` | **unbound stub** (`rg_game_unbound.c`) | format; its 2 callers (`MpegDefaultErrorPrint_115918`, `sceCdChgSys_12ae70`) reach the stub |
| `sceOpen_11b928` | `game_names.c`, non-variadic `(name, flags)` | 2 callers, both pass 2 arguments; fine |

Variadic views of non-variadic definitions:

- 54 C++ `F(...)` declarations are already patched by protos (`decl-patched varargs:`).
- `DataTableCtor_41e9d0` and `DataTableCtor_41ef20` are only taken by address.
- `CharaTableCreate_223ff0(...)` is declared but not called.

No game function pointer has a variadic type.

## Call sites

| Callee | Sites | Variadic view / non-variadic local view |
| --- | --- | --- |
| Sprintf_1343b8 | 412 | mixed (callers keep their views; 517 of the 1,157 argument rows come through a non-variadic view) |
| Fprintf_12f9a0 | 92 | mostly `(fp, msg)`: 74 sites pass no variadic argument |
| SoundSendCmd_1b6cc0 | 83 | variadic (header) |
| SoundIopSendCmd* | 39 | variadic |
| sceSdRemote_1229e8 | 37 | 18 variadic, 19 non-variadic `(s32,s32,s32,s32)`-style views |
| SoundRpcCall_1bc5e0 | 8 | variadic |
| DbgPrintf_15e780 | 5 | variadic |
| scePrintf_119288 | 2 | non-variadic |
| **total** | **678** | |

The TSV has 1,157 rows, one per variadic-position argument or per read past the arguments.

| Class | Rows | Sites | Meaning |
| --- | --- | --- | --- |
| ok | 780 | | widths and kinds agree |
| fmt-unknown | 171 | 113 (Sprintf) | runtime format (message table lookups, `o->f98`, ...). **Every argument pushed is 4 bytes**, so widths cannot drift. |
| read-past-args-benign | 145 | 37 | `sceSdRemote_1229e8` always reads 6 words |
| read-past-args | 42 | 19 SoundIop + 4 Sprintf | the callee reads more than was passed (see below) |
| extra-arg | 15 | 13 | passed, never read (same on both) |
| int64-read-as-32 | 3 | 2 | see below |
| shifted | 1 | 1 | a 4-byte argument that lands on the wrong slot after an int64 |

No site pushes:

- a `float` in a variadic position;
- a `double` that gets read: the only `double` is an unread extra in `SoundSetMasterVolume_1bb420`;
- a struct by value;
- a 4-byte value read as `%lld` or `%f`.

No printf format in the corpus uses `ll`, `L` or `I64`, and the resolved ones contain no
`%f`.

## Findings, by impact

1. **Key-on SE path, the SOUND.md root cause. Fixed in the tree by `vararg-narrow`.**
   - `SoundSendKeyOn_1b80c0` (`game/src/main/sound/SoundSendKeyOn_1b80c0.c:29`) passes
     args 9, 10 and 12 (vel, pan, bend; `s64`) to `SoundSendCmd_1b6cc0(0x20, 10, ...)`.
   - `SoundPlayEntryKeyOn_1b81e0` (`:87`) does the same.

   These are now `(s32)(...)`. The TSV shows them as `ok`, with the note "narrowed in
   tree". They were the only 64-bit arguments among the 83 SoundSendCmd sites.
2. **`TaskEntryFormatStatus_208a90` (`main/sys/TaskEntryFormatStatus_208a90.c:23`)
   is real and open, but debug only.**
   - **The bug.** The local view `extern s32 Sprintf_1343b8(s32, void *, s64, s64, s32)`
     converts `(s8)v1` and `(s8)v2` to `s64` before pushing. The format is
     `" [%c][%c]%s"` (`D_0045C608`).
   - **Effect on i686.**
     - The first `%c` is correct.
     - The second `%c` reads the high word of v1 (0).
     - `%s` reads the low word of v2 (0x20 or 0x2A) **as a pointer**, which is an access
       violation.
   - **Where it runs.** The function sits in the debug-menu vtable at `data2c_004713A0`.
   - **Why vararg-narrow misses it.** The 64-bit width comes from the **view's parameter
     type**, not from the expression, so a cast on the argument is converted straight back
     to `s64`.
3. **Read past the arguments: dropped register passthrough (Sprintf, 4 sites).** These are
   wrong strings on i686. Retail relied on `$a2`/`$a3` still holding values.
   - `EvMonographChrName_2e93f0` (`main/event/...:16`) and `EvMonographFncName_2e93a0`
     call `Sprintf(a1, "mono_chr_%03d_%s")` (or `mono_fnc_...`) with no further
     arguments. Their incoming `a2` and `a3` are unmodified, so retail passed them
     through.
     - **i686 effect:** stack garbage, so a garbage monograph name, and `%s` can fault.
     - **Fix:** `Sprintf(a1, fmt, a2, a3)`.
     - These are the highest-impact open sites: they run from `EvSpawnChrMonographs_2e91e0`.
   - `insect_InsectBattleDrawNumberRec_4f1490:17` calls `Sprintf(buf, "%d")` with no
     argument. Its definition `(s32 a, void *r)` has no third parameter, so the number
     probably came in `$a2` from its callers. **Check against the retail asm.**
     **Checked (2026-10-13):** yes. The definition passes its untouched entry `$a2`;
     the caller insect_InsectBattleRematchPromptDraw_4f14e0 loads `$a2` with i / a / b /
     c / e before its five calls. Fixed by two overrides
     (`out/bringup-checkpoint/mk_insect_number_overrides.py`).
   - `insect_InsectPiecePlayMotion_5145e0:68` passes `"%s%02d"` with only `*p`. The `%02d`
     reads `$a3` in retail; check against the asm.
     **Checked (2026-10-13):** the listing never sets `$a3` in this function; at the
     second Sprintf (0x5146F4, piece type 0x10 and id 0 only) it holds whatever the first
     Sprintf_1343b8 -> VfprintfR_1374e0 left in `$7`, data-dependent. Not spellable;
     open until a PCSX2 probe of `$a3` there. On i686 `%02d` reads the next stack slot
     (an int: no fault).
4. **Fixed-length IOP packets read past the arguments (SoundIopSendCmd*, 19 sites, 36
   words).**
   - Example: `SoundThreadCmdSetPan_1b68c0` passes 5 words to G3S2, which reads 8.
   - The tail words are stale registers on the EE and caller stack on i686. This is not a
     regression in kind, but the packet tail is now non-deterministic. It matters only if
     the IOP HLE reads those words for that command.
   - `SoundThreadCmdKeyOn_1b6800:13` passes a final `(s64)*(s32 *)...` to G3S2. It is the
     **last** read, so the low word is read and nothing shifts: harmless.
5. **Extra arguments** (13 sites): harmless on both targets. Examples:
   - `SoundRpcCall(0x8100, 0, p2, p3)`;
   - `SoundSendCmd(0xC, 2, t, t, v)`, where `v` is an unread `double`;
   - Sprintf formats with `?` placeholders (`rc/param/planet/%s_2_?.pac`).

## Proposed generic stage rule (an extension of protos `vararg-narrow`)

For every direct call to a callee whose **truth** is variadic, apply the steps below. Truth
is a game C definition, or a provider definition in `src/crt`, `src/sce` or `overrides`.

1. **Normalize the view.** If the caller keeps a non-variadic local view, convert each
   argument at a position at or after the definition's fixed count to the view's parameter
   type: `(T_view)(expr)`, which is what mwcc did. Then call through the definition's
   variadic prototype: blank the local declaration, or cast the callee to it. This turns
   TaskEntryFormatStatus's `s64` view parameters into explicit, narrowable expressions.
2. **Build a read model** for each callee:
   - **Uniform `va_arg(T)`**: as today.
   - **Count-driven**: `count` × T when the count argument is an integer literal.
   - **Fixed list**: for provider bodies, scan their `va_arg` loops as well.
   - **printf family** (`Sprintf_1343b8`, `Fprintf_12f9a0`, `DbgPrintf_15e780`,
     `scePrintf_119288`): parse the format from a literal or from `D_` data in the retail
     image, following a `char *` word.
3. **Narrow.** Where the static type at a variadic position is 8-byte integer and the
   ordinal read is a 4-byte integer, pointer or `%c`/`%d`/`%x`/`%s`/`%p`, emit
   `(T_read)(expr)`. That is exactly the EE's low-word read.
   - Decide "8-byte" from the **clang type**, not from the textual `_expr_kind`, which
     misses `(s64) * (s32 *)...`.
   - When the format is unknown and the argument is 8-byte integer, log
     `info-vararg-wide`. The current corpus has 0 such arguments.
4. **Missing variadic arguments.** These are reads past the arguments with a resolved
   format or count. Extend `missing-passthrough` to variadic callees: if the enclosing
   function's incoming GPR parameter in that slot (`$a2`, `$a3`, ...) is unmodified and no
   earlier call clobbers it, pass it. This fixes the 2 EvMonograph sites. Otherwise log
   `manual-vararg-missing`: the 2 insect sites, and SoundIop packet tails, which can take
   `0`.
5. **Log, never rewrite**, these EE-also-wrong pairings: float or double read as int, and
   int read as `%f`. There are 0 today.

Expected effect on the current tree:

- TaskEntryFormatStatus is fixed by steps 1 and 3.
- EvMonographChrName and EvMonographFncName are fixed by step 4.
- 2 insect sites are flagged for asm review.
- No other changes.
