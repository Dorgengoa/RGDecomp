# VU0 / VU1 interpreter and VIF

PLAN.md D3, phase 1: a VIF1 + VU1 interpreter that turns the game's own DMA
chains into GIF packets for the GS renderer. Everything here was written from
public hardware descriptions (the VU and EE user's manuals' semantics). No
PCSX2 or DobieStation code was read or copied. Play! (BSD-2) was consulted only
for a few semantic questions, listed under "Sources"; nothing was vendored.

| path | what |
| --- | --- |
| `src/ps2/vu/vu.h` | VU state and API (`vu_init`, `vu_start`/`vu_continue`, `vu_run`, `vu_step`, `vu_load_code`, PATH1 sink) |
| `src/ps2/vu/vu.c` | interpreter and pipeline model |
| `src/ps2/vu/vu_float.c` | VU float arithmetic (no Inf/NaN/denormals, chop rounding, saturation) |
| `src/ps2/vu/vu_decode.[ch]`, `vu_disasm.c` | decoder, register-use summary, disassembler; shared by the interpreter, the census tool and the tests |
| `src/ps2/vif/vif.[ch]` | VIF0/VIF1 command processor |
| `src/ps2/vif/vu_retail.[ch]` | read-only access to the retail ELF's microcode packets (tools and tests only) |
| `src/ps2/vif/vucensus.c` | `rg-vucensus`: disassembles every uploaded block and writes the census below |
| `tests/vu/` | `rg-vu-tests`, `rg-vif-tests`, `rg-vu-smoke` (`ctest -L vu`) |

## Wiring

```c
vu_state vu1;  vif_state vif1;
vu_init(&vu1, 1);
vif_init(&vif1, 1, &vu1);
vu1.gif_sink  = gs_vu1_gif_sink;  vu1.gif_user  = gs;   /* PATH1: XGKICK   */
vif1.gif_sink = gs_vif1_gif_sink; vif1.gif_user = gs;   /* PATH2: DIRECT   */
vif_write(&vif1, words, nwords);  /* the VIF word stream the DMAC delivers */
```

`vif_write` accepts any split of the stream (a command may straddle calls).
VU0 micro mode is the same `vu_state` with `id = 0` (4 KB + 4 KB); set
`vu0.vu1 = &vu1` to give it the VU1 register window at 0x4000. `vcallms imm`
is `vu_start(&vu0, imm * 8); vu_run(&vu0, budget)`. For game code that is
`rg_vu0_vcallms(imm)` (`src/ps2/vu0_micro.c`), which also syncs the registers
with the macro-mode model `rg_vu0` before and after the run, so macro and
micro mode see one VU0 (PORT-HEADERS.md "VU0 micro mode"); src/runtime binds
its VU0 to it.

**Synchronous model.** MSCAL/MSCALF/MSCNT run the VU program to its end
before the VIF reads the next word (budget `vif.vu_cycle_budget`, default
1,000,000 cycles; a runaway is counted in `stats.vu_runaways` and reported in
`vif.error`). FLUSHE/FLUSH/FLUSHA are therefore no-ops. The game double-buffers
(TOPS/TOP), so a UNPACK that on hardware overlaps a running program lands in
the other buffer and the result is the same. A program that relied on
UNPACK data arriving *while it runs* would break; none of the retail programs
waits on VIF data.

## VU model

### Pipeline, as far as the programs can observe it

The VU interlocks VF registers (a reader stalls until the writer's result
exists), so the values a program computes do not depend on timing. What does
depend on timing is state the hardware does **not** interlock: the MAC, status
and clip flags, Q and P. The interpreter therefore counts cycles:

- Each pair gets an issue cycle = previous issue + 1, raised to the ready time
  of every VF field it reads (per field: `x`, `y`, `z`, `w`). VF results from
  the upper unit and from lower loads/moves are ready 4 cycles after issue.
  ACC chains (MULA, MADDA, ...) do not stall.
- MAC + status (from FMAC ops) and clip (from CLIP) become visible to
  FMAND/FMEQ/FMOR, FSAND/FSEQ/FSOR, FCAND/FCEQ/FCOR/FCGET **4 cycles after
  issue**. MAX/MINI, ABS, FTOI/ITOF and loads do not touch the flags.
- DIV and SQRT write Q 7 cycles after issue, RSQRT 13. A Q read before that
  sees the old Q (`stats.q_early_reads` counts it). A second DIV/SQRT/RSQRT,
  or WAITQ, stalls until the pending one has landed.
- EFU ops write P after: ESADD 11, ERSADD 18, ELENG 18, ERLENG 24, ESUM 12,
  ESQRT 12, ERSQRT 18, ERCPR 12, ESIN 29, EATAN/EATANxy/EATANxz 54, EEXP 44
  cycles. The same old-value/stall rules as Q apply (WAITP).
- At the end of a program (E bit) every in-flight write lands (`vu_drain`).

The retail code is scheduled exactly against these numbers, which is why they
are modelled and not approximated:

- the head program issues `div Q, vf00w, vf05x` and `div Q, vf00w, vf05y`
  back to back, and reads Q with `addq.x` / `addq.y` exactly 6 and 7 pairs
  later. With the stall-on-busy rule the first read gets 1/x and the second
  1/y. Without it both would see the same value
  (`tests/vu: waitq_div_chain`);
- the character programs test a sign with `mulz.z vf00, ...` (flags only)
  followed **exactly 4 pairs later** by `fmeq vi, vi` (0x20 = Sz), with other
  flag-setting FMAC ops in between whose flags must not be visible yet;
- the clip-culling code issues three CLIPs, three NOPs, then
  `fcand vi01, 0x03ffff`, which needs all three results and none newer.

The census counts 80 Q reads within 7 pairs of a DIV and 45 flag reads within
4 pairs of an FMAC/CLIP across the 62 programs.

### Pair semantics

- **Upper before lower, writes after both.** Both halves read the register
  file as it was before the pair; the upper's result is written after the
  lower has run (179 sites in the retail code have a lower op reading a field
  the paired upper writes). No retail pair has both halves writing the same VF
  field. If one did, the upper's write wins here.
- **I bit (LOI).** The lower word is loaded into I. The upper in the **same**
  pair still sees the **previous** I. The retail VU0 sin/cos routine proves it:
  `mulai.xyzw acc, vf10, I [loi 12582912]` followed by
  `msubai acc, vf11, I` / `maddai acc, vf11, I [loi -0.159155]` is the
  round-to-integer trick (subtract and add 1.5 * 2^23), which only works if
  each upper uses the I loaded one pair earlier. 64 retail pairs have an upper
  that reads I in an I-bit pair.
- **Branches** have one delay slot. Targets are `pc + 8 + imm11 * 8`; JR/JALR
  jump to `VI * 8`; BAL/JALR link `(pc + 16) / 8`. VI0 is always 0, VF0 always
  (0, 0, 0, 1).
- **E bit**: the next pair (the delay slot) still runs, then the program
  stops. TPC (where MSCNT resumes) is the address that would have run next. If
  the E pair is itself a taken branch, as in the head program's
  `nop[e] / b 0x0328`, TPC is the branch target. So the game's pattern
  "MSCAL 0x320 once, then MSCNT per batch" re-enters at 0x330 every time.
- **Integer-branch hazard.** If a conditional branch (IBxx) reads a VI that
  the immediately preceding pair's lower *integer* op (IADD*, ISUB*, IAND,
  IOR, ILW, ILWR, MTIR, XTOP, XITOP, LQI/LQD/SQI/SQD increments) wrote, and the branch did
  not stall, it reads the VI value from 4 pairs back. This follows the
  behaviour both open emulators implement. Flag ops (FC*, FS*, FM*) are
  excluded: the retail code branches on their result in the very next pair 67
  times (FCAND x40, FCOR x22, FMAND x5) and is obviously meant to see the new
  value, while it **never** branches right after an integer ALU write (it
  always leaves a NOP). JR/JALR are excluded too (`iaddiu vi03, 0x73a` /
  `jalr vi15, vi03` appears back to back). So the hazard never fires on retail
  code. It is modelled (and can be switched off with `vu.int_branch_quirk = 0`)
  only so that a future hand-written test cannot silently depend on the
  opposite.
- **M bit** (VU0 interrupt enable) and **D/T bits** (debug break) are
  accepted. D/T stop the run only with `vu.break_on_dt`. None appear in the
  retail code.
- **XGKICK** walks GIF tags from `VI * 16` up to the EOP tag (PACKED
  `NLOOP*NREG` qwords, REGLIST `ceil(NLOOP*NREG/2)`, IMAGE `NLOOP`, NREG 0 =
  16, addresses wrap at 16 KB) and hands the whole packet to the PATH1 sink as
  a snapshot taken at the moment XGKICK executes. Hardware transfers it in the
  background while the program continues. A program that overwrote a kicked
  buffer before the GIF had read it would differ. The retail programs
  double-buffer their output.
- **Memory.** LQ/SQ/ILW/ISW addresses are qword indices, wrapped to the data
  memory (VU1: 1024 qwords, VU0: 256). ILW/ILWR read the first dest field's
  low 16 bits; ISW/ISWR write the zero-extended VI to every dest field. VU0
  addresses with bit 0x400 set reach VU1 VF00-VF31 (0x400-0x41F) and VI00-VI15
  (0x420-0x42F, x word).

### Floating point

`vu_float.c`: a VU single has the IEEE layout but no Inf, NaN or denormals.

- An exponent of 0 reads as (signed) zero whatever the fraction.
- Exponent 255 is an ordinary binade. 0x7F800000 is 2^128 and 0x7FC00000 is
  1.5 * 2^128, and arithmetic on them gives finite results.
- Results are computed in double and **chopped** (rounded toward zero) to 24
  bits.
- Overflow saturates to +-0x7FFFFFFF (O flag). Results below 2^-126 become +-0
  (U and Z flags).
- MAC bits, per lane, with x in the high bit of each nibble: `15..12 O`,
  `11..8 U`, `7..4 S`, `3..0 Z`. **Lanes outside the dest mask get 0.**
- Status: bits 0-3 = OR of this result's Z/S/U/O, bit 4 I, bit 5 D (from
  FDIV), bits 6-11 the sticky copies. FSSET writes bits 6-11 only.
- MADD/MSUB chop the product to a VU float and then chop the sum. An overflow
  in the product is reported.
- FTOI truncates and saturates to int32. ITOF chops.
- MAX/MINI compare sign-magnitude bit patterns (denormals compare as 0) and
  return one operand unchanged.
- DIV: x/0 is +-max with D, 0/0 is +-max with I (sign = xor of the operand
  signs). SQRT of a negative number is sqrt(|x|) with I. RSQRT by 0 is
  +-max with D (I if 0/0).

The memory notes of the retired recomp list two real bugs this avoids:
producing IEEE Inf/NaN (every CLIP comparison against NaN is false, so
geometry behind the camera escaped culling), and clamping before computing the
O flag (which made O permanently 0).

## VIF model

`vif.c` covers every command code: NOP, STCYCL, OFFSET, BASE, ITOP, STMOD,
MSKPATH3, MARK, FLUSHE/FLUSH/FLUSHA, MSCAL/MSCALF/MSCNT, STMASK, STROW, STCOL,
MPG, DIRECT/DIRECTHL and UNPACK 0x60-0x7F. VIF0 rejects the VIF1-only codes
(OFFSET, BASE, MSKPATH3, FLUSH, FLUSHA, DIRECT, DIRECTHL) as invalid.

- **UNPACK**: S/V2/V3/V4 x 32/16/8 bits plus V4-5. 16- and 8-bit values are
  sign-extended unless USN. V4-5 expands each 5-bit channel `<< 3` and A to
  0x80. The data is padded to a 32-bit boundary. ADDR is 10 bits (VIF1) or 8
  bits (VIF0); FLG adds TOPS (VIF1). The W lane of V3 is described in
  "V3 W lane" below.
- **Write cycles**: if CL >= WL ("skipping write") qword *i* goes to
  `ADDR + (i / WL) * CL + i % WL`. If CL < WL ("filling write") qword *i* goes
  to `ADDR + i` and only the first CL of every WL consume data. NUM counts
  written qwords (0 = 256).
- **Mask**: when the m bit is set, MASK row `min(cycle, 3)` gives per field 0
  data, 1 ROW, 2 COL[row], 3 write-protect. STMOD offset (data + ROW) and
  difference (ROW += data; write ROW) apply to data fields only.
- **Double buffering**: OFFSET sets DBF = 0 and TOPS = BASE. Every
  MSCAL/MSCALF/MSCNT latches TOP = TOPS and ITOP = ITOPS, flips DBF, and sets
  TOPS = BASE + (DBF ? OFFSET : 0). XTOP/XITOP read the latched values.
- **MPG**: NUM (0 = 256) pairs at IMM * 8. It invalidates the decode cache.
  `vif.mpg_hook` sees every upload (used by the census).
- **i bit**: after the command completes, `vif.irq` is set and `irq_fn`
  called. With `stall_on_irq` `vif_write` returns early with the words
  consumed so far.

Choices where public documentation is silent or says "undefined":

| case | here |
| --- | --- |
| V2 z,w | x, y repeated (x y x y) |
| V3 w | measured against PCSX2, see "V3 W lane" (no longer a guess) |
| filling cycles (cycle >= CL) without mask | re-write the last element read |
| WL = 0 | treated as WL = 1 |
| MSCAL while the VU is still running (runaway) | previous run abandoned, counted |

Apart from V3 w, none of these has been checked against the game. The
captured frames (see "Validation") use only CL = WL = 1 and CL = 2, WL = 1
(skipping write), no STMOD and no masked UNPACK, so the filling, WL = 0 and
runaway rows, MASK and MODE stay unverified against PCSX2.

### V3 W lane

A V3 element supplies X, Y and Z; the unpacker still writes all four lanes.
What lands in W was measured against PCSX2 on the 11 frame captures of
docs/VALIDATION.md section 5 (the game uses V3-16 for positions and V3-8,
never V3-32). With element index e counted from 0 within the UNPACK (the
data elements read, so fill cycles repeat the W of the element they repeat):

| format | W |
| --- | --- |
| V3-16 | the next 16-bit value of the VIF stream, extended like X/Y/Z (sign unless USN): the following element's X, the padding halfword when 3 x NUM is odd, or, when the payload ends on a word boundary, the low half of the next stream word (normally the next VIF code, e.g. W = 0xFFFFC05C before the V2-16 UNPACK `662CC05C`). **Except** elements with e mod 16 = 7 or 9, whose W is 0. |
| V3-8 | element 0: the next byte (the padding byte when NUM = 1); every other element: 0 |
| V3-32 | the next 32-bit stream word (following element's X, or the word after the payload). Extrapolated from V3-16; the game never uses V3-32, so it is unmeasured. |

Evidence (each scene repeats its frames exactly, so elements are counted
once per scene, cutscene + battle): 15 distinct V3-16 elements with
e mod 16 in {7, 9} have W = 0 where the next halfword is non-zero (3 more,
at the payload end, are 0 too), and no element with another e mod 16 does;
about 170 distinct elements (mostly non-zero values), covering every
other e mod 16, have W = the next halfword; 6 distinct last elements take the next VIF code's low half
(0xFFFFC05C, 0xFFFFC00C, 0xFFFF8021, 0xFFFF8009, 0xFFFF802F). Every V3-8
element beyond 0 is 0 (30+ distinct elements with a non-zero next byte); one
V3-8 element 0 takes the next byte (0xFFFFFF89). With this rule the replay
has 0 wrong words in all 11 captures (with the old W = 0: 74 wrong W lanes
per cutscene frame, 69 per battle frame). Alternatives, as wrong words in
frames 9002 / 24808: never write W (keep the old value) 72 / 160; next
component everywhere, 0 past the payload 17 / 35 (past the payload kept:
18 / 37); the rule above but V3-16 e mod 16 = 7, 9 kept instead of 0 5 / 8;
V3-8 elements >= 1 kept instead of 0 4 / 66; V3-8 element 0 also 0 1 / 0.

The mechanism behind the e mod 16 = 7, 9 and V3-8 exceptions is not known;
it is what PCSX2 does (the reference for the port), and real hardware may
differ: the public VIF descriptions do not define W for V3.

Implementation: W reads past the payload come from the stream words that
follow in the same `vif_write` call (`vif.ahead`). If the payload ends the
call, the W lanes of the last element are written when the next word arrives
(`vif.wpend*`, with that moment's MASK and MODE: STMOD offset/difference is
applied to the deferred lane then); a stream that never continues leaves
them unchanged. So results do not depend on how the stream is split
(`vif.split_stream`).

## Opcode census (the 62 retail programs)

`rg-vucensus` replays every MPG packet listed in `census/platform_vu1.tsv`
through the VIF, so the census also exercises the MPG path. It finds the
census's 66 blocks and 62 unique code hashes, with **0 undecodable
encodings**. Coverage:

- **Upper:** 41 distinct mnemonics are used. All 41 are implemented and all
  are unit-tested.
- **Lower:** 41 distinct mnemonics are used. All 41 are implemented and
  unit-tested. ESIN is tested at 0 only.
- **Not used by the game, but implemented:** RNEXT/RGET/RINIT/RXOR, the
  remaining EFU ops, FS*/FC*/FM* variants, LQD, ILWR/ISWR, MTIR, XITOP and
  ITOF4/12. All of these are unit-tested except EEXP/EATAN, which are tested
  at single points.

Regenerate with
`build\<dir>\src\ps2\vif\rg-vucensus.exe --md out.md [--dis DIR]`. `--dis`
writes one disassembly listing per block.

<!-- generated by rg-vucensus from SCUS_974.90; regenerate, do not edit -->

Blocks uploaded: 66 (62 unique by content), 7574 instruction pairs in unique blocks.

| VU | packet | dest | pairs | sha1 (census) |
| --- | --- | --- | --- | --- |
| VU1 | 0x436CB0 | 0x0320 | 87 | 2ce6ef18c3c3 |
| VU1 | 0x436F80 | 0x0320 | 4 | 10e53a7e96d3 |
| VU1 | 0x436FB0 | 0x0320 | 66 | 84c53508f462 |
| VU1 | 0x4371D0 | 0x2620 | 256 | 794d31381c48 |
| VU1 | 0x4371D0 | 0x2E20 | 256 | 520465c6a913 |
| VU1 | 0x4371D0 | 0x3620 | 102 | dbbf81d408cd |
| VU1 | 0x438520 | 0x2620 | 2 | ad5e430b2187 |
| VU1 | 0x438540 | 0x2620 | 218 | b7b250300727 |
| VU1 | 0x438C40 | 0x0960 | 3 | deccfa26e4d4 |
| VU1 | 0x438C70 | 0x0960 | 199 | d3c05f868c9c |
| VU1 | 0x4392C0 | 0x0960 | 27 | da0dc161975b |
| VU1 | 0x4393B0 | 0x0960 | 216 | 08f098da0f47 |
| VU1 | 0x439A80 | 0x0960 | 159 | 269ddfa75666 |
| VU1 | 0x439F90 | 0x0960 | 16 | f973eb46197e |
| VU1 | 0x43A020 | 0x0960 | 186 | bbdff8528024 |
| VU1 | 0x43A620 | 0x10E0 | 26 | 4300ad63ed1e |
| VU1 | 0x43A700 | 0x10E0 | 44 | 30dae1eb3859 |
| VU1 | 0x43A870 | 0x10E0 | 200 | 496c0e0bd576 |
| VU1 | 0x43AEC0 | 0x10E0 | 73 | e2e97f5893bd |
| VU1 | 0x43B120 | 0x10E0 | 120 | 9f3b3de71f50 |
| VU1 | 0x43B4F0 | 0x10E0 | 237 | 02b13bbad6ac |
| VU1 | 0x43BC90 | 0x1900 | 88 | 70c291b98892 |
| VU1 | 0x43BF60 | 0x1900 | 103 | 7e52378f8dbd |
| VU1 | 0x43C2B0 | 0x1900 | 249 | 179b5d9f91ab |
| VU1 | 0x43CA90 | 0x1900 | 83 | 56de054b9bc8 |
| VU1 | 0x43CD40 | 0x1900 | 119 | fc1f2c689f85 |
| VU1 | 0x43D110 | 0x1900 | 256 | 4611813a8b4a |
| VU1 | 0x43D110 | 0x2100 | 28 | 2503e290c5a8 |
| VU1 | 0x43DA10 | 0x1900 | 256 | d9cb29033ec5 |
| VU1 | 0x43DA10 | 0x2100 | 42 | c48037157fce |
| VU1 | 0x43E380 | 0x1900 | 92 | c1b551961546 |
| VU1 | 0x43E670 | 0x1900 | 92 | 355d3695d7cb |
| VU1 | 0x43E980 | 0x39D0 | 19 | aca907392cb2 |
| VU1 | 0x43EA30 | 0x39D0 | 52 | 537492003594 |
| VU1 | 0x43EBE0 | 0x39D0 | 28 | 1a47c0f9d172 |
| VU1 | 0x43ECD0 | 0x39D0 | 71 | e234682a6881 |
| VU1 | 0x43EF20 | 0x39D0 | 57 | ee02c9430675 |
| VU1 | 0x43F100 | 0x39D0 | 104 | cb1aec2f9d4e |
| VU1 | 0x43F450 | 0x39D0 | 37 | fb86f020b9f5 |
| VU1 | 0x43F590 | 0x39D0 | 79 | a15ba11ed363 |
| VU1 | 0x43F820 | 0x0320 | 49 | 9ffeebc9a8f4 |
| VU1 | 0x43F9C0 | 0x1900 | 256 | fe0fbc2a4cff |
| VU1 | 0x43F9C0 | 0x2100 | 242 | e94f7ff9e827 |
| VU1 | 0x440970 | 0x0320 | 84 | 89a0476d2755 |
| VU1 | 0x440C20 | 0x10E0 | 256 | f680a6470a76 |
| VU1 | 0x440C20 | 0x18E0 | 68 | 6f2533ba23b6 |
| VU1 | 0x441660 | 0x0320 | 57 | a2745c52063d |
| VU1 | 0x441840 | 0x10E0 | 256 | 1e12d15dff78 |
| VU1 | 0x441840 | 0x18E0 | 178 | 3b0d21caec36 |
| VU1 | 0x4425F0 | 0x0320 | 60 | 0144b9fc86e9 |
| VU1 | 0x4427E0 | 0x10E0 | 256 | e8b19794bd47 |
| VU1 | 0x4427E0 | 0x18E0 | 11 | b79e9d87bb0c |
| VU1 | 0x443050 | 0x2620 | 256 | eb83629c83b8 |
| VU1 | 0x443050 | 0x2E20 | 256 | 86e64a02985e |
| VU1 | 0x443050 | 0x3620 | 37 | f4a4adf1f4dc |
| VU1 | 0x4441A0 | 0x0320 | 63 | 66895c8eb0a3 |
| VU1 | 0x4443B0 | 0x2620 | 256 | 8b7c26a3a31c |
| VU1 | 0x4443B0 | 0x2E20 | 218 | f10d9ec058ec |
| VU1 | 0x4452A0 | 0x2620 | 172 | d89fb9e97a13 |
| VU0 | 0x445810 | 0x0000 | 112 | 607931373190 |
| VU0 | 0x445810 | 0x0640 | 20 | 8e1fb4263f01 |
| VU1 | 0x445C60 | 0x0960 | 59 | 2c979f8cf610 |

### Upper opcodes

| opcode | uses | blocks |
| --- | --- | --- |
| NOP | 2713 | 62 |
| MADDAbc | 799 | 40 |
| MADDbc | 468 | 41 |
| MULAbc | 468 | 40 |
| MULbc | 339 | 43 |
| MULq | 274 | 32 |
| MUL | 269 | 35 |
| ADDbc | 218 | 32 |
| SUB | 218 | 32 |
| MAXbc | 180 | 30 |
| FTOI4 | 174 | 23 |
| MINIbc | 163 | 25 |
| CLIP | 159 | 22 |
| ADD | 149 | 23 |
| MULi | 134 | 23 |
| FTOI0 | 98 | 22 |
| MULA | 84 | 19 |
| MADD | 82 | 17 |
| MAX | 77 | 15 |
| MINI | 76 | 13 |
| ITOF15 | 67 | 7 |
| SUBbc | 63 | 20 |
| OPMULA | 51 | 17 |
| OPMSUB | 50 | 16 |
| ITOF0 | 37 | 11 |
| ABS | 18 | 4 |
| MADDA | 18 | 4 |
| MADDAi | 18 | 4 |
| MSUBAi | 18 | 4 |
| MSUBbc | 16 | 4 |
| ADDi | 15 | 6 |
| SUBi | 15 | 5 |
| MSUBi | 9 | 4 |
| MULAi | 9 | 4 |
| ADDA | 6 | 2 |
| ADDq | 6 | 4 |
| ADDAbc | 5 | 2 |
| MAXi | 4 | 2 |
| MINIi | 3 | 2 |
| MADDi | 2 | 2 |
| MSUBAbc | 2 | 1 |

### Lower opcodes

| opcode | uses | blocks |
| --- | --- | --- |
| NOP | 2372 | 62 |
| LQ | 1241 | 56 |
| SQ | 698 | 45 |
| IADDIU | 690 | 51 |
| ILW | 419 | 56 |
| MOVE | 223 | 27 |
| IADD | 206 | 45 |
| ISW | 202 | 32 |
| LOI | 202 | 28 |
| DIV | 156 | 31 |
| IBNE | 129 | 48 |
| LQI | 120 | 20 |
| FCAND | 101 | 21 |
| IBEQ | 101 | 42 |
| IAND | 75 | 29 |
| SQI | 65 | 13 |
| XGKICK | 60 | 22 |
| IOR | 55 | 13 |
| JR | 55 | 42 |
| B | 50 | 27 |
| ISUBIU | 42 | 22 |
| MR32 | 36 | 5 |
| WAITQ | 35 | 17 |
| XTOP | 34 | 20 |
| FCSET | 28 | 19 |
| MFIR | 24 | 8 |
| JALR | 23 | 7 |
| FCOR | 22 | 4 |
| MFP | 21 | 6 |
| IADDI | 20 | 9 |
| RSQRT | 18 | 4 |
| ERSQRT | 12 | 2 |
| FMEQ | 10 | 5 |
| FMAND | 7 | 3 |
| WAITP | 7 | 6 |
| ERLENG | 5 | 2 |
| ESIN | 3 | 1 |
| BAL | 2 | 2 |
| IBLTZ | 2 | 2 |
| SQD | 2 | 2 |
| ESUM | 1 | 1 |

### Static hazard patterns (unique blocks, straight-line scan)

| pattern | sites |
| --- | --- |
| invalid upper or lower encodings | 0 |
| I bit (LOI) pairs | 202 |
| I bit pairs whose upper reads I | 64 |
| E bit pairs | 19 |
| E bit in a branch delay slot | 0 |
| branch in a branch delay slot | 0 |
| cond. branch reading a VI the previous lower op wrote | 67 |
| upper reads Q < 7 pairs after DIV/SQRT/RSQRT (no WAITQ) | 80 |
| flag read < 4 pairs after an FMAC/CLIP | 45 |
| lower reads a VF field the paired upper writes | 179 |
| upper and lower write the same VF field | 0 |
| D/T bits | 0 |
| M bits | 0 |

Writers at the 'cond. branch reading a VI the previous lower op wrote' sites: FCAND x40; FCOR x22; FMAND x5;

## Tests

`ctest -L vu` runs 186 tests; the smoke ones are skipped (return 77) when the
retail ELF is missing. The `vu.<name>` unit tests run with the VU1 block
translator on (the default); `vu.interp.<name>` repeats each with
`RG_VU_BLOCKS=0` and `vu.check.<name>` with `RG_VU_BLOCKS_CHECK=1` ("Block
translator").

| test | what it proves |
| --- | --- |
| `vu.decode_retail` | decoder + disassembler on 18 retail instruction words; the test encoder matches retail encodings |
| `vu.arith`, `vu.acc_forms`, `vu.opmula_cross`, `vu.ftoi_itof`, `vu.move_mr32` | every FMAC/ACC form, conversions, cross product: hand-computed results |
| `vu.float_edges`, `vu.flags_overflow_underflow`, `vu.mac_dest_mask`, `vu.vf0_const` | 0x7F800000/0x7FC00000 as numbers, denormal inputs, chop rounding, saturation, U/O/Z/S flags, dest-masked MAC lanes |
| `vu.mac_latency`, `vu.stall_shifts_flags`, `vu.clip`, `vu.clip_24bit` | flags visible at +4 cycles, stalls move that point, CLIP history and FC*/FS*/FM* ops |
| `vu.q_latency`, `vu.waitq_div_chain`, `vu.div_special`, `vu.efu`, `vu.efu2` | Q/P latency and stalls, divide-by-zero/invalid, EFU values |
| `vu.integer`, `vu.memory`, `vu.pair_order`, `vu.loi`, `vu.random` | integer ops (16-bit wrap), every load/store form, upper/lower ordering, I-bit timing, R LFSR |
| `vu.branches`, `vu.cond_branches`, `vu.ebit_tpc`, `vu.ebit_with_branch`, `vu.int_branch_quirk` | delay slots, links, E-bit/TPC/MSCNT, the integer-branch hazard |
| `vu.xgkick`, `vu.xtop`, `vu.vu0_window`, `vu.runaway_budget` | PATH1 packet extent (PACKED/REGLIST/IMAGE, NREG 0, no EOP), TOP/ITOP, VU0->VU1 window, cycle budget |
| `vif.unpack_*` | all 13 UNPACK formats, USN, skipping/filling writes, mask rows, ROW/COL, offset/difference modes |
| `vif.tops_double_buffer`, `vif.direct_and_kick`, `vif.split_stream`, `vif.irq_stall`, `vif.vif0` | BASE/OFFSET/DBF/TOPS/ITOP across MSCAL/MSCALF/MSCNT, MPG + XGKICK + DIRECT to the sinks, word-at-a-time feeding, i-bit stall, VIF0 differences |
| `vu.float_diff.*` (16) | every float helper (add/sub/mul/madd/msub, to_d/from_d, ftoi/itof, cmp, clip, div/sqrt/rsqrt, EFU) bit-identical, result and flags, to the pre-optimisation reference (`tests/vu/vu_float_ref.c`; "Performance"); `vec`: the four-lane SSE2 forms (`vu_vec_inl.h`) lane for lane equal to the scalar helpers, MAC bits included |
| `vu.replay_same.*` (11) | translator on: the same PATH1 stream, VU1 memory, registers and cycle count as the pre-optimisation copy in `tests/vu/ref` on every PCSX2 capture, and translated pairs reported ("Performance", "Block translator") |
| `vu.replay_same_interp.*`, `vu.replay_check.*` (11 each) | the same with `RG_VU_BLOCKS=0`, and with the per-block lockstep check |
| `vu.blkfuzz`, `vu.blkfuzz_check`, `vu.blkfuzz_pool` | random programs, registers, budgets, restarts and re-uploads: translator and interpreter agree on the full state after every `vu_run` (also with the lockstep check, and with a 5-block pool flushed all the time) |
| `vu.progfuzz_same.{blocks,interp,check}` | the same random programs on the live build (translator on / off / checked) and on `tests/vu/ref`: one FUZZHASH |
| `vu.smoke.census` | all retail MPG packets parse; 66 blocks / 62 unique / 0 undecodable |
| `vu.smoke.vu0_srt` | **real correctness check on retail code**: the VU0 microprogram behind `MatFromSRTVu0`/`MatRotateVu0` (vcallms 0x0: scale vf1, Euler angles vf2, translation vf3, matrix out in vf4-7), run for 8 angle sets, gives orthonormal rotations (max error 1e-6) equal to Rx·Ry·Rz in row-vector form to 1.2e-6, and applies scale and translation. That routine's own sin/cos polynomial depends on chop rounding, I-bit timing, FMAC flag latency and FMAND/IBEQ |
| `vu.smoke.variants` | all 16 distinct VU1 variants from `VuMicrocodeTableInitMaybe_152830` (head 0x320 + kind 0x39D0 + tail 0x2620, plus one second-level piece per slot): MSCAL 0x320 then two MSCNT batches on synthetic input. Every variant reaches its E bit, every XGKICK packet is a well-formed GIF packet ending in EOP, and two runs are bit-identical |

Deliberately wrong controls, which must **fail**: `vu.mac_latency_control`
(expects flags at +3), `vif.unpack_v4_control` (V4-5 without the expansion),
`vu.float_diff_control` (add compared against mul),
`vu.smoke.variants_control` (a different seed in the second run, so
"deterministic" must be violated) and `vu.blkfuzz_control` (one stall cycle
added to the translator's state halfway, which the comparison must report).

The synthetic batch for the VU1 smoke test follows the layout every head
program reads (from the disassembly): a GIF tag template at qw 0, the output
offset at qw 76.x, a second tag template at qw 86, and at TOP a header with
the vertex count in y, `count | EOP` in z and array offsets in w and in the
next qword. The vertex loops are unrolled, so the test tries counts 4, 8, 2,
12, ... and keeps the first that terminates (4 for 15 variants, 12 for the
kind-4 head 0x4425F0). Kind 4 emits no XGKICK on this input. The output is
**not** checked for correctness, only for structure and determinism.

## Accuracy caveats

1. **Rounding is modelled, the arithmetic unit is not.** Results are exact,
   then chopped to 24 bits. The real FMAC has a narrower internal adder (it
   drops bits when exponents differ a lot) and can differ by 1 ulp. A
   byte-exact match of vertex output against PCSX2 or hardware is therefore not
   expected. PCSX2 is not bit-exact against hardware either. Compare with a
   tolerance, or compare the post-FTOI4 integer coordinates with +-1.
2. EFU functions use libm (`sin`, `atan`, `exp`, `sqrt`), not the hardware's
   polynomials. The retail code uses ERSQRT x12, ERLENG x5, ESIN x3 and
   ESUM x1.
3. The pipeline model covers FMAC/FDIV/EFU latencies and VF stalls. It does
   not model the integer pipeline beyond the branch hazard, XGKICK/GIF
   arbitration stalls, or the VIF/VU running concurrently (see "Synchronous
   model"). Cycle counts (`stats.cycles`) are approximate and only meant for
   ordering.
4. Under-specified VIF cases (the table above) are guesses.
5. Hardware details not modelled: VU0 macro mode (COP2 is `src/ps2/vu0.c` /
   `include/port/vu0.h`, another agent's area), VU0 M-bit interrupts,
   VIF FIFO and STAT, MARK/IRQ timing relative to DMA, VU1 GIF PATH1/2/3
   masking (`mskpath3` is recorded only).
6. Thread safety: a `vu_state` must not be shared between threads. It holds
   its own decode cache (`dc_store`, about 192 KB), so allocate it statically
   or on the heap, not on the stack.

## Validation against PCSX2 (what to capture)

The trace harness (`tools/trace`) hashes EE memory at VBlanks. It does not
see VIF/VU traffic. Validating this interpreter needs, per frame, the **input
stream** and the **expected GIF output**:

1. **Input: the VIF1 stream.** Two ways:
   - a savestate at a VBlank (PCSX2's state contains EE RAM, VU1 data and code
     memory, VU1 registers and VIF1 registers), plus the VIF1 DMA chain start
     addresses the game kicks during the next frame (D1_TADR/MADR/QWC/CHCR at
     each `sceDmaSend` to channel 1). The chain is then walked from the EE RAM
     image on the port side.
   - or, simpler to consume: a flat log of every VIF1 word delivered, captured
     by stepping through the DMA chain at kick time from the harness (EE RAM
     read by `live.py`). Note that the chain may be rebuilt between kicks.
2. **Expected output: PATH1/PATH2 GIF packets.** A PCSX2 GS dump (`.gs`, taken
   with the GS dump hotkey for one or more frames) records every GIF transfer
   with its path. Filter path 1 (XGKICK) and path 2 (DIRECT).
3. **Initial VU1 state** for the first batch: the 16 KB data memory, the
   16 KB code memory, VF/VI/ACC/Q/P/I/R/flags and TPC, plus VIF1
   CYCLE/MASK/MODE/ROW/COL/BASE/OFST/TOPS/ITOPS/DBF. All of this is in the
   savestate.

Proposed file `vifcap` (little-endian), one per captured frame:

```
"VIFCAP1\0"
u32 n_records
record:  u32 kind, u32 bytes, payload
  kind 1  VU1 state   : data[16384] code[16384] vf[32][4]u32 vi[16]u16 acc[4]u32 q p i r mac status clip tpc
  kind 2  VIF1 regs   : cl wl mode mask row[4] col[4] base ofst tops itops dbf (u32 each)
  kind 3  VIF1 words  : u32[] in delivery order (one record per DMA kick; DMAtag upper halves included when TTE=1)
  kind 4  GIF packet  : u32 path, u8[] packet (expected output, in order)
```

A replay test loads kinds 1 and 2, feeds every kind-3 record to `vif_write`,
and diffs the PATH1/PATH2 packets against kind 4. GIF tags and registers must
match exactly. XYZ/ST/RGBAQ values are compared with the tolerance from caveat
1. The same capture validates each native microprogram replacement (D3 phase
2) against this interpreter.

### Replay test (what exists)

Kind 4 could not be captured (docs/VALIDATION.md section 5); the captures
carry instead kind 5 (PCSX2's VU1 data memory at the next vsync), kind 6
(metadata) and kind 7 (VU1 code memory at the next vsync).
`tests/vu/vu_replay.c` (`rg-vu-replay <capture> [--control] [--verbose]`)
replays one capture and compares VU1 data memory word by word (exact; close
= same-sign floats within 16 ulp or integers off by 1, caveat 1; wrong) and
code memory pair by pair, plus structural checks (stream fully consumed, no
runaway or invalid command, PATH1 packets whole qwords). Pass: 0 wrong words
and identical code memory. `--verbose` lists wrong words.

ctest (label `vu`): `vu.replay.v01956` ... `vu.replay.v24808`, one per
capture in `out/captures/C_v<vbl>.vifcap` (gitignored, made by
`tools/trace/vucap.py build`), each skipped (exit 77) when its file is
missing; and `vu.replay_control` (WILL_FAIL), which flips bit 30 of the
first payload word of the last UNPACK in frame 9002 and must fail.

Current results: title frames 4,096 exact; cutscene frames 4,080 exact /
16 close / 0 wrong; battle frames 4,079-4,085 exact / 11-17 close / 0 wrong;
code memory identical in all 11; control 2 wrong (fails as required).

## Performance

Checkpoint 2026-10-13 (`build/vuperf-i686`; scratch tools and raw output in
`out/vuperf/`, game data and measurements, never committed). The 3D field went
from 212 to 22 ms per field (fields 7000-8000, headless, hardware GS at x1), bit
for bit the same game.

**Problem** (GPU.md "Checkpoint 2"): in the 3D field the VU1 interpreter was
87-91 % of wall time, and most of that was the static CRT's `ldexp`/`frexp`
(`__ctrlfp`, `__set_exp`, `__decomp`), which `vu_float.c` called to build and
split doubles: four CRT calls per add or multiply.

**Step 1: bit manipulation for the conversions** (`vu_float_inl.h`, inline;
`vu_float.c` keeps the public `vu_f_*` entry points as wrappers; `vu.c` calls
the inline forms). Same arithmetic (double add/sub/mul, SSE2, round to
nearest), only the conversions changed:

- `vu_f_to_d`: exponent `e - 127 + 1023` at bit 52, the 23 fraction bits at
  bit 29, sign at bit 63; `e == 0` is a signed zero.
- `vu_f_from_d`: VU exponent = double exponent field - 896 (frexp's
  `ex + 126`), fraction = the top 23 mantissa bits (the old
  `(m*2-1)*2^23` chop); zero, overflow (>= 256) and underflow (<= 0,
  including subnormal doubles) as before.
- `ldexp(x, +-n)` in FTOI/ITOF: a multiplication by the exact power of two.
- CLIP: the double compares `x > |w|`, `x < -|w|` are magnitude compares of
  the VU values (exponent 0 reads as zero).
- EFU and FDIV moved from `vu.c` to `vu_float.c` (`vu_efu`, `vu_fdiv`) so the
  differential test can reach them; their libm calls are unchanged.

**Exactness.** `tests/vu/vu_float_ref.c` is the pre-change implementation
(plus `vu.c`'s CLIP/EFU/FDIV float code), renamed `ref_*`;
`rg-vu-float-diff CLASS COUNT` compares result bits and condition bits
(Z/S/U/O, FDIV I/D). Every binary class first runs the full cross product of
an edge set (all 256 exponents x 8 fractions {0, 1, 2, 0x3FFFFF, 0x400000,
0x555555, 0x7FFFFE, 0x7FFFFF} x 2 signs = 4,096 values, 16.7 M pairs), then
COUNT random pairs (a mix of uniform patterns, edge values, exponent 0/1/127/255
with random fractions, and operands whose exponents are within 32 of each
other for sums or sum near 0, 1 and 254 for products: cancellation, rounding,
overflow and underflow edges). `from_d` also sweeps every double exponent
field with 4,096 mantissas x 2 signs. ctest `vu.float_diff.*` (15 classes)
runs COUNT = 1 M; `vu.float_diff_control` (add compared against mul) must fail.

Long proof run (`out/vuperf/proof`, 12 processes, about 1.5 h), all with
**0 mismatches**:

| class | checked |
| --- | --- |
| `to_d` | all 4,294,967,296 patterns |
| `ftoi`, `itof` | all 2^32 patterns x frac 0/4/12/15 (17,179,869,184 each) |
| `add`, `sub`, `mul`, `cmp`, `clip`, `div`, `sqrt`, `rsqrt` | 16.7 M edge pairs + 1e9 random each |
| `madd`, `msub` (accumulator random, near the product, or cancelling it) | 1e9 random each |
| `from_d` | 1e9 random doubles (any pattern, the VU binades, subnormals) + the exponent sweep |
| `efu` (all 13 EFU ops, random fsf) | 1e9 random |

**Step 2: per-pair overhead in `vu.c`** (each exact by construction; covered
by the interpreter comparison below):

- `vu_run` inlines the pair step (`step_pair`, always inline; `vu_step` is a
  wrapper for the tests).
- The decode cache entry also holds the pair's VF read components (upper and
  lower merged, duplicates and VF0 dropped: VF0 is never marked busy) and its
  VF write components as indexes into `vf_ready`; the stall is the maximum
  over that list and `mark_ready` stores into it. The entry keeps only the
  four `vu_use` fields the step reads, so it still fits `dc_store`'s 96 bytes
  per pair (a first version grew `vu_state` by 64 KB, and `rg-hwbus-tests`,
  which keeps two on the stack, overflowed its 1 MB stack).
- The VI history for the integer-branch quirk is a ring (`vi_hist_pos`): one
  32-byte copy per pair instead of shifting five.
- `commit_events` is called only when an event, Q or P is pending.
- FMAC: one lane loop per kind, the broadcast/Q/I operand converted to double
  once (`vuf_from_d(da * dt)` is `vuf_mul` with the conversion hoisted), MAC
  bits from a 16-entry table (`mac_spread`); the upper reads VF in place
  instead of copying fs/ft (nothing writes VF before its results land) and
  writes its results straight into the output.
- `exec_upper`, `exec_lower`, `commit_events`, `push_event` and the decode
  cache hit are always inline (at `-O1` clang had stopped inlining them once
  the step itself was inlined into `vu_run`); a miss calls `dc_fill`.

**Interpreter comparison.** `tests/vu/ref/` holds verbatim copies of
`src/ps2/vu` at checkpoint 0a6381a (before this work); `rg-vu-replay-ref` is
the PCSX2 frame replay built on them, and `rg-vu-replay` prints a `HASH` line
(FNV-1a of the PATH1 stream with VU addresses, of final VU1 data memory, VF,
ACC, VI, Q/P/I/R, MAC/status/clip, TPC, and the cycle count, plus pairs,
cycles, stalls, quirk count). ctest `vu.replay_same.*` requires identical
lines on all 11 captures (the 4 title ones run no VU1 code; the 3 cutscene and
4 battle ones run 1.27 M and 2.74 M pairs each). `rg-vu-replay --reps N`
prints the best `vif_write` time: 1,020 -> 56 ms (cutscene `C_v09002`) and
2,311 -> 128 ms (battle `C_v24804`), 834 -> 47 ns per pair.

**Game check** (`out/vuperf/vrun.sh`, `vcmp.sh`, `ramcmp2.py`): the golden
input (`tools/trace/goldens/newgame_battle.input.txt`), headless, `RG_GPU=hw`
x1, 8,000 fields, with the binary before this work (`out/vuperf/base_bin`, same
tree otherwise) and after it. Results:

- `--screenshot` at field 8000: byte-identical PNG.
- `RG_STATUS_EVERY=250` lines (fields 250-8000): identical.
- GS recording of fields 7900-7960 (`RG_GS_REC`, 78 MB, 2.87 M lines of
  `tools/gsrec_dump.py --regs`): 690 lines differ, all in register bits the GS
  ignores (the high word of `ZBUF_1` and bits 40-63 of `ALPHA_1`, where the
  game leaves a host pointer). The same 660 `ZBUF_1` lines differ between two
  runs of the *same* binary (ASLR moves the game RAM).
- EE RAM (`RG_RAM_DUMP`, 32 MB) at fields 7000, 7500 and 8000: 503 / 551 / 566
  words differ, and every one is a host pointer: into game RAM at the same
  offset (31 / 63 / 70, as between two runs of one binary) or into the exe
  at the same symbol + offset in each build's map (the image layout changed).

The same checks with the final binary (`new4_bin`): screenshot, STATUS lines
and GS recording as above; RAM 892 / 940 / 955 differing words, all relocated
pointers by the same classification. Full `ctest` in `build/vuperf-i686`: 503
tests, 0 failures (the 4 `gpu.*game_replay`/`readback_lag` tests and the 2
real-CD tests skip there: no `RG_GPU_REPLAY_DIR` / disc image configured).

**Numbers** (`out/vuperf/frun.sh`: the golden input headless, unthrottled,
`RG_GPU=hw` x1, RTX 3080, under `out/gpuperf2/prof/rgprof.exe` at 2 ms; ms per
field from `RG_FIELD_TIMES`, shares from `anal.py` on the main thread; run to
run noise is about 1-2 ms, mostly in the GPU wait):

| build | 7000-8000 | 7000-7599 | 7600-8000 | worst field | VU1 | GS model | GPU wait (`mirror_download`, `draw`) |
| --- | --- | --- | --- | --- | --- | --- | --- |
| before (`base_bin`) | 212.4 | 97.1 | 385.1 | 1,836 | 193.4 (91 %) | 5.2 | 10.1 |
| step 1 (`new1_bin`) | 27.6 | 15.2 | 46.0 | 299 | 14.8 (54 %) | 5.0 | 4.7 |
| step 2 (`new3_bin`) | 25.9 | 14.5 | 43.0 | 243 | 11.7 (45 %) | 5.0 | 6.1 |
| + inlining (`new4_bin`, final) | **22.1** | **12.6** | **36.2** | 214 | 10.6 (48 %) | 4.6 | 3.9 |

**Where the field goes now** (final, fields 7000-8000, 22.1 ms): `vu_run`
46 % (the whole interpreter is one function now; in the replay profile the
float conversions are ~20 % of it, the stall scan and ready marks ~10 %, the
flag event queue ~6 %, the rest the pair bookkeeping and the upper/lower
switches), `gs_xfer_hwreg` 18 % (GS model, `src/ps2/gs`), the CPU waiting in
`ntdll` under `D3D11Backend::draw` 11 % and in `mirror_download` 7 % (GPU
renderer), `gs_gif_write` 1.6 %. The field is real-time (16.7 ms) only in its
lighter part: 7000-7599 at 12.6 ms; 7600-8000 at 36 ms is still twice too slow.

**Not done / next steps.**

- The VU interpreter is at ~47 ns per pair (170 cycles); the profile is flat,
  and further micro work gave less than 10 % per step, so this stopped here.
  Compiling `rg_ps2_vu` at `-O2` measured 12 % faster on the replay but PLAN
  D2 keeps `-O1` until the UB audit, so it was not changed. The next real
  step is the one D3 plans: native code for the retail microprograms (62
  unique, `vu.smoke.census`), or a translator of decoded blocks with the flag
  and stall bookkeeping resolved statically per block; `rg-vu-replay-ref`,
  `vu.replay_same.*` and the game check above are the harness for it.
- `gs_xfer_hwreg` (4.6 ms per field) and the CPU-side waits of the D3D11
  backend (~5 ms) are now a third of the field; they are outside `src/ps2/vu`.
- Done since: the block translator, next section.

## Block translator

Done 2026-10-13 (`build/vublock-i686`; scratch tools, binaries, runs and
logs in `out/vublock/`, never committed). Option (a) of the plan above: a portable translator of
decoded blocks, no code generation. `src/ps2/vu/vu_block.c`, private
interface `vu_internal.h`.

**Switches.** On by default for VU1 (`vu_state.blocks`; env
`RG_VU_BLOCKS=0` forces the interpreter). `RG_VU_BLOCKS_CHECK=1`
(`vu_state.blocks_check`) runs every block on the interpreter first, then
the translated block from the same state, and aborts on any difference in
the full state (lockstep check). VU0 always interprets. `vu_release(vu)`
frees the block cache (`vu_init` does not, it zeroes the struct).
`RG_VU_BLOCKS_STATS=1` prints a summary line on stderr every 64 Mi pairs
(pairs translated / interpreted, block runs, blocks built, variants, pool).
`RG_VU_BLOCKS_POOL=N` caps the block pool (default 16,384 blocks; beyond it
the pool is flushed), for tests.

| file | what |
| --- | --- |
| `src/ps2/vu/vu_block.c` | blocks, timing variants, operations and their handlers, dispatcher, lockstep check |
| `src/ps2/vu/vu_vec_inl.h` | four-lane SSE2 forms of the float helpers |
| `src/ps2/vu/vu_internal.h` | what `vu.c` and `vu_block.c` share (decode cache entry, step, XGKICK, commit) |
| `tests/vu/vu_blkfuzz.c` | `rg-vu-blkfuzz`: translator against interpreter on random programs |
| `tests/vu/vu_progfuzz.c`, `vu_fuzzgen.h` | `rg-vu-progfuzz(-ref)`: random programs on the live build and on `tests/vu/ref` |

**Blocks.** A block starts at any entry pc and runs to the delay slot of the
first branch or E bit, or 192 pairs. It is decoded once, from the
interpreter's own decode cache entries, and pooled by content (start pc and
raw words), so a re-uploaded program finds its blocks again. `vu_load_code`
now only acts when the bytes change, and then invalidates the decode cache
and the blocks that overlap the changed range.

**Timing variants.** Within a block every issue cycle follows from the
pipeline state at entry, and only three things in that state can move it:
VF results still in flight that pairs 0-2 read (the interpreter keeps
`vf_ready <= cycle + 3`, so 2 + 2 + 1 bits), a DIV/SQRT/RSQRT still in flight
when the block has a Q-waiting pair, and an EFU op still in flight when it
has a P-waiting pair. That is the variant key (16 bits). Each variant is
compiled on first use by running the interpreter's issue rule (`step_pair`)
on relative cycles, so stalls, the cycle count, the stall count, Q/P landing,
and the cycle each MAC/clip flag event becomes visible are constants.
Usually a block has one variant (185 blocks, 186 variants for a cutscene
frame). The key costs 4 ANDs when the previous translated block's in-flight
set (its "tail") does not meet the block's live-in reads.

**What runs.** A variant is a list of pre-decoded operations (16 bytes:
handler, destination offset, fields, immediate) executed in order; handlers
take their arguments in registers (`regparm(3)` on i686). FMAC handlers
(one per kind x operand source VF/bc/Q/I), OPMULA/OPMSUB, MAX/MINI,
ITOF/FTOI and ABS work
on the four lanes at once with SSE2 (`vu_vec_inl.h`): VU -> double for four
lanes from 32-bit halves, the double operation, and double -> VU for the
common results (VU exponent 1-255, and +-0) with the MAC bits from the sign
and zero masks; a lane outside that (overflow, underflow) is redone with the
scalar `vuf_from_d`, so each lane is bit for bit the scalar helper. Each
variant remembers its last two successors (pc, block, variant), so the
common transition skips the map lookup and the variant search; the Q/P part
of the key is rechecked on the way. Flags: an FMAC writes its MAC value to a per-block
slot; the slot is copied to `vu->mac` only at the points where something
can see it (before an FM*/FC*/FCSET pair, and at the end). The sticky status
bits are an OR over the MAC values that landed inside the block, folded in
once at the end. Clip events shift in at the same points, in order. Events
that land after the block are pushed onto the interpreter's flag queue with
their absolute cycles, and VF results still in flight are written back to
`vf_ready`. Q and P land where the interpreter would observe them (before a
Q/P reader or a new DIV/EFU, and at the end). The integer-branch quirk's VI
history is kept for the block's last 4 pairs.

Upper/lower ordering keeps "both read the registers as before the pair, the
upper lands last": the upper writes directly unless the lower reads one of
its destination fields (then the lower runs first) or a conflict needs the
upper's result parked in a temporary.

**Interpreter changes** (`vu.c`, all modes). The VI history of the
integer-branch quirk was five 32-byte copies of the VI file per pair; it is
now a log of the last 4 pairs' VI writes (register and old value), and the
VI file "4 pairs ago" is the current one with those writes undone: the same
values for any run that starts with `vu_start` (`vu.progfuzz_same.*` below;
only a caller that sets `running` by hand after changing VI could tell).
`vu_load_code` does nothing when the bytes are unchanged (the decode cache
is a pure function of them) and otherwise invalidates the decode cache and
the overlapping blocks. XGKICK copies the packet with `memcpy` when it does
not wrap.

**Fallback** (the block's pairs are interpreted one by one):

- a branch or E bit in a delay slot, or an E pair whose delay slot branches;
- FSEQ/FSSET/FSAND/FSOR in the block (the status flag is settled lazily);
  the retail code has none;
- a conditional branch that reads a VI the previous pair's integer op wrote
  (the integer-branch quirk can fire), inside the block or at its first pair
  against the previous block; the retail code never does this;
- D/T bits with `break_on_dt`;
- the cycle budget would run out inside the block;
- a pending state the key cannot encode (never produced by the interpreter);
- a block that already has 16 timing variants and meets a 17th entry state;
- after a stop inside a block (budget), until the branch/E-bit sequencing is
  back at a block boundary.

Assumption: code memory changes only through `vu_load_code` between
programs (the VIF's MPG, in the synchronous model), not from inside a
running program (for example from the PATH1 sink). The interpreter would
pick up such a change at the next pair, a translated block only at its end.

On the retail captures the fallback rate is 0 (every pair translated).

**Exactness evidence** (all pass):

- `vu.replay_same.*` (translator on, must report translated pairs),
  `vu.replay_same_interp.*` (`RG_VU_BLOCKS=0`) and `vu.replay_check.*`
  (lockstep check): HASH lines identical to `rg-vu-replay-ref` on all 11
  PCSX2 captures; the translator runs 100 % of their pairs (cutscene frame:
  185 blocks, 186 variants, 10.2 pairs per block run).
- `rg-vu-blkfuzz` (`vu.blkfuzz`, `vu.blkfuzz_check`, `vu.blkfuzz_pool`,
  control `vu.blkfuzz_control` must fail): random programs over every opcode
  class, random dest masks, small register sets (so results feed each other
  and stall), I/E/M/D/T bits, short branches, JR/JALR, random registers,
  flags and memory, random cycle budgets (so runs stop inside blocks), MSCNT
  and MSCAL restarts, partial code re-uploads. Interpreter and translator
  compared on the full state after every `vu_run` call. 20,000 iterations
  (397 M pairs, 70 % translated, 1.6 M quirk firings) and many shorter seeds,
  with a 5-block pool too: 0 differences.
- `rg-vu-progfuzz` vs `rg-vu-progfuzz-ref` (`vu.progfuzz_same.*`): the same
  random programs on the reference copy of the original interpreter
  (`tests/vu/ref`) and on the live build with the translator on, off and
  lockstep-checked: identical FUZZHASH (3,000 iterations, 60 M pairs,
  260 k quirk firings).
- Float fast paths (`vuf_to_d` from 32-bit halves, `vuf_from_d` exponent
  1-255 first) against the original ldexp/frexp code (`rg-vu-float-diff`,
  `out/vublock/proof`): `to_d` all 2^32 patterns, `itof` all 2^32 x 4
  fraction widths (17.2 G, through `vuf_from_d`), add/sub/mul/from_d 217 M,
  madd/msub 200 M cases: 0 mismatches. The SSE2 forms against the scalar
  helpers: `vu.float_diff.vec` (7.3 M lanes per run, edge, zero and
  near-exponent operands, every dest mask), 0 mismatches.
- Every VU unit test passes with the translator on, off and checked
  (`vu.*`, `vu.interp.*`, `vu.check.*`); `ctest -L vu`: 186 / 186. Full
  `ctest` in `build/vublock-i686`: 608 tests, 0 failures (6 skipped: the
  `gpu.*game_replay`/`readback_lag` and real-disc tests, not configured
  there).
- **In the game** (`out/vublock/vrun.sh`, `vrun2.sh`, `vcmp.sh`,
  `vcmp2.sh`; golden input, headless, `RG_GPU=hw` x1; one binary, run with
  `RG_VU_BLOCKS=0` and with the default): to field 8000, screenshot
  byte-identical, all 32 STATUS lines identical, GS recording of fields
  7900-7960 byte-identical, EE RAM at 7000 / 7500 / 8000 differs in 36 / 68 /
  75 words, every one a pointer into game RAM at the same offset (ASLR); to
  field 16000 (the VU1-heavy part, below), screenshot at 16000 identical, 64
  STATUS lines identical, GS recording of fields 13900-13960 (100 MB)
  byte-identical, RAM at 12000 / 14000 / 16000 89 / 98 / 102 words, all
  game-RAM pointers. A game run with `RG_VU_BLOCKS_CHECK=1` to field 16000
  checked every one of 45.3 M block runs (495 M VU1 pairs, 397,043 XGKICKs)
  against the interpreter: 0 mismatches; translated 100 %, fallback 0, 139
  blocks, 140 variants, no pool flush.

**The golden run has changed under this work.** Other areas moved while it
was done (the movie path now plays, VIF interrupt timing in `src/ps2/dmac`,
the game sources): in the current tree the golden input reaches no VU1 work
before field 8000 (the stats line shows VU1 starting after it; fields
7000-8000 are now a 2D information screen over a movie, where the earlier
binary drew VU1 3D geometry), and VU1 runs from about field 8000 to the end.
The current tree also crashes at field 22,900 in game code
(`MtxInverseAffine_1cb640` from the map task code, read of 0xFFFFFFFF),
identically with `RG_VU_BLOCKS=0`, so the measurements stop at 16000. The
previous checkpoint's binary (`out/vuperf/new4_bin`) on today's data still
gives 23.8 ms per field for 7000-8000 with VU1 at 10.1 ms.

**Numbers** (`out/vublock/frun.sh`: headless, unthrottled, `RG_GPU=hw` x1,
RTX 3080, under `rgprof` at 2 ms; ms per field from `RG_FIELD_TIMES`, VU1 =
`anal.py`'s vu1 bucket on the main thread; final binary `out/vublock/bin4`,
two runs per mode, alternating; the machine was shared with other sessions,
noise about 1-2 ms):

| fields | interpreter | translator | VU1 interpreter | VU1 translator |
| --- | --- | --- | --- | --- |
| 7000-7599 | 3.10 / 2.85 | 3.35 / 3.17 | 0.0 | 0.0 |
| 7600-8000 | 4.28 / 3.98 | 4.68 / 3.97 | 0.1 | 0.1 |
| 8000-15999 | 9.84 / 8.07 | 8.19 / 6.26 | 3.02 / 2.99 | 1.12 / 1.16 |
| 14000-14999 (heaviest VU1) | 22.41 / 21.80 | **12.86 / 12.15** | 13.77 / 14.22 | **4.84 / 4.54** |

So where VU1 works, it is 2.9-3.1x faster in the game (13.8-14.2 -> 4.5-4.8 ms
per field in the heaviest 1000 fields), and those fields go from 22 to 12 ms.
The PCSX2 frame replays (`rg-vu-replay --reps 9`, best `vif_write`, VIF and
the test's hashing included): cutscene `C_v09002` 55 -> 22 ms, battle
`C_v24804` 132 -> 51 ms, 47 -> about 17 ns per pair.

**Where VU1 time goes now** (fields 14000-14999, translator, 4.5-4.8 ms of
12.2-12.9): the variant loop and block end (`run_variant`, 8 % of the
field), FMAC handlers (`h_MADD_bc` 7 %, `h_MUL_vf` 3 %, `h_MUL_bc` 2.5 %,
the other FMAC forms under 1 % each), the dispatcher (`vu__block_run` 2 %),
flag sync points (`h_sync` 1.4 %), loads/stores and integer ops under 1 %
each. 1.73 operations are dispatched per pair (C_v24804). Outside the VU the
field is the GS model (`xfer_row`, `gs_xfer_mask`, 2.4-2.7 ms), the CPU
waiting on the D3D11 backend (`mirror_download`, `draw`), VU0 micro mode
(still the interpreter, about 2 %) and VU0 macro ops (`rg_vu0_fmac`, 3 %,
`src/ps2/vu0.c`).

**Next steps.**

- VU0 micro mode (`vcallms`) through the translator: needs the VU0 memory
  window (0x4000) and 4 KB masks in the load/store handlers; about 2 % of the
  heaviest fields.
- Fewer dispatches: fuse common upper+lower handler pairs, and chain a
  block's successor variant directly when it is static (loops), to cut the
  per-block end work. Both stay inside this design; generating C per retail
  microprogram (D3 option b) is not needed for the "few ms" goal now.
- The dropped VU1 workload before field 8000 and the crash at 22,900 are in
  the game/runtime areas; once the golden run is stable again, re-measure
  7000-8000.

## Sources

- VU and EE (VIF) user's manuals' instruction semantics, as summarised in
  public documentation; retail disassembly for the timing evidence above.
- Play! (github.com/jpd002/Play-, BSD-2-clause) was consulted for three
  semantic points: that the upper and lower of a pair both read pre-pair
  registers, that a branch after an integer write reads an older VI, and how
  V4-5/S/V2 UNPACK fill components. No code was copied or vendored.
- Memory notes of the retired recomp (documentation only): MAC/status flag
  layout and the "lanes outside dest are cleared" rule, the 24-bit clip mask,
  Q latency, the no-Inf/NaN requirement and the clamp-after-flags order.
