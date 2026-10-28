# Render bring-up: the post-FMV field draws only sky

User report (2026-10-13): in the first 3D scene after the opening FMV (golden run, port
fields ~7,300-8,300, subtitle "He should be hiding out somewhere on Rosa.") music and
voices play, but the picture is flat blue with a grey polygon in a corner
(`out/bringup-checkpoint/shots/z8290.png`, also `old8290.png` from an older build).
Retail draws a textured in-engine cutscene there (the ship's crew on the sand of Rosa).

Scratch area: `out/render-bringup/` (game data and screenshots, never committed).

## Checkpoint (newest first)

### 2026-10-13: camera basis rows (root cause 1)

**Retail reference.** PCSX2 (portable copy only) with the golden input, software
renderer, window shots every 100 frames from game vbl ~7,970 to 16,600:
`python tools/trace/trace.py run --memcard --speed 0.5 --idle-ms 3 --every 10
--renderer 13 --shot-every 100 --shot-from 8250 --stop-vbl 16600 --regions
out/render-bringup/retail/min.cfg --input tools/trace/goldens/newgame_battle.input.txt
--slot 28033 --state-slot 7 --out .tools/run/rbshot.tsv` (shots in
`.tools/run/shots/rbshot/`, `fFRAME_vVBL.png`). Retail vbl 9,090 = "He should be..."
typing; the port's field 8,290 is vbl 8,253 (FMV end: port 7,321, retail 8,074).

**Layer 1, GS stream (port, field 8,290, `RG_GS_REC`).** The frame is not empty: 410
PATH1 packets with 6,505 XYZF2 vertices, but only 76 fall inside the 512x448 window
(XYOFFSET 1792/1824); the rest are spread over the whole 0..4095 GS range. The sky (PATH2
sprites) is fine. So geometry is drawn but mis-transformed: upstream of the renderer.

**Layer 2, EE state vs retail.** Retail EE RAM at vbl 9,006
(`out/captures/raw/C_v09006_*.zip`, the VIF capture run) vs the port at field 8,290
(`RG_STATUS_DUMP=0x4B5660:0x11A0`; note: `RG_RAM_DUMP` reads 4 KB pages through the
trace map and leaves the rest of a page zero after the first unmapped byte, so it shows
false zeros around symbols). Camera1 (`D_004B5950`, the scene camera, eye
(-3010, 57, -1906), at (-2890, 47, -1906)):

| row | retail | port |
| --- | --- | --- |
| x (+0x10) | (0, 0, 1) | (0, 0, 1) |
| y (+0x20) | (0.083, 0.9965, 0) | (-0.9968, 0.080, 0) |
| z (+0x30) | (-0.9965, 0.083, 0) | (-0.080, -0.9968, 0) |

The port's up row is retail's forward row and its forward points down: every camera
basis is rotated 90 degrees about x, so the view looks at the sky.

**Cause.** `CameraBaseLookAt_15fae0`: retail keeps side / up / dir / (unused) as ONE
4-row matrix at sp+0x80..0xBF; `MtxMul_13d240(&side, &side, &m)` (roll) and the
`setDir` virtual (slot 0x1C) read it as rows. The C declares four separate `Vec4`
locals, and clang orders them differently. The `stack-block` protos rule declined the
function (`manual-stack-block`: "sizes unknown for ['dir', 'side']", the rule does not
resolve `Vec4` from `vec.h`), so the pre-session build was already wrong the same way.
The port object confirms it (`llvm-objdump`): dir at esp+0x70, up at +0x30, side at +0x60,
so `setDir(&side)` read side, dir, then a row of the zeroed `m`.

**Fix:** override `overrides/src/main/matrix/CameraBaseLookAt_15fae0.cpp` (one struct
`{side, up, dir, old}` at retail's relative offsets).

### 2026-10-13: VU1 microcode words lost in the data stage (root cause 2)

With the camera fixed (build `fix1`) the field shows geometry, but textures are noise and
many surfaces are flat-shaded (`fix1/dump/f08290_display.png`). Layered check:

* **VIF stream.** New env capture `RG_VIF1_DUMP=path RG_VIF1_DUMP_KICKS=a-b`
  (`src/ps2/dmac/dmac.c`; one record per VIF1 channel kick; a line on stderr every 256
  kicks maps kicks to fields: field 8,288 = kick 4,128). Parsed with
  `out/render-bringup/tools/vifparse.py` against retail's VIFCAP1 at vbl 9,006: the same
  command mix (MSCAL 0x000/0x320/0x960, MSCNT, UNPACK 62/66/69/6A/6C/6E, DIRECT), and
  every model batch whose positions match a retail batch is equal apart from unused
  padding words.
* **VU1 output.** `tools/vu_replay_gif.c` (scratch copy of `tests/vu/vu_replay.c` that
  writes PATH1/PATH2 and can watch a VU qword or single-step one MSCNT) replays a port
  kick with the retail start state: it reproduces the port's GS stream exactly (same tag
  histogram as the `RG_GS_REC` of the field), with ~300 malformed PATH1 GIF tags (PRE=1,
  NREG 13-15, FLG 2/3); retail's replay has none. The bad tags are kicked from VU 0x3FE0,
  whose upper word comes from VU qword 19 (`00008000 10000000 0000000E`), and qword 19 is
  overwritten during MSCNT runs of program 0x320 (`sqi.xy vf04, (vi03++)` with
  vi03 = 0xA413): the program adds `vi04` to the batch base, but nothing loaded `vi04`.
* **Microcode.** The MPG upload at 0x320 differs from retail in two instruction pairs
  (words 16 and 20: retail lower `0x09070057` / `0x09044801`, port 0). They live at EE
  0x436D00 and 0x436D10, which the data stage emitted as zero `gap-pad`s
  (`game/DATARELOC.tsv`: the decomp names those addresses `func_00436D00` /
  `func_00436D10`, so the microcode table was split around two "functions" that no unit
  defines). `out/render-bringup/tools/datacheck.py 00436980 00445E80` (generated data vs
  the retail ELF): exactly those 4 words are missing, plus one microcode word symbolised
  as a pointer: 0x445384 = `(u32)&D_00460080` (retail: the VU word 0x00460080; on the port
  a host address).

**Fix (overrides):** `overrides/src/main_data/data2c_00436CF0.c`, `data2c_00436D08.c`
(the pads get retail's bytes) and `data2c_004452A0.c` (the literal word). Result (`fix3`):
textured, correctly lit scenes; `out/render-bringup/after/pair_f*.png` port vs retail.

**All 155 `gap-pad` rows are non-zero in retail** (`tools/gapcheck.py`): most are EE jump
tables and code bytes, which the port does not read, but the stage has no way to know which
gaps matter. Stage-rule proposal (for the bring-up lane): see "Proposals" below.

### 2026-10-13: event actors in the bind pose (root cause 3: strings symbolised as pointers)

With root causes 1-2 fixed every event actor (Steve, Zegram, the guards) stood in the bind
pose while Jaster (field motion) animated. Retail probe (`probe.py --fn
ApplyMotion:0x171a10 --fn ApplyFrameKeys:0x1542d0`, `out/render-bringup/retail/anim.jsonl`)
and the port (`RG_BREAK`) agree on the control flow (5 ModelApplyMotion / 3
AnimApplyFrameKeys per frame); the two actors go through the AMX blend path, where
`AnimBlendBufAccumulate_1533f0` -> `AnimResGetFrameKeyList_14bf10` found no motion
resource: `AmixerBindResByNameMaybe_170330` looked every clip up by a NULL name, because
`AmixerCfgClipActionCmd_16f8a0` never ran. Its keyword in the parser table `D_0044A400` is
the string at `D_004590B8+0xC8`, "AMX_CLIP_ACTION": the word "ION\0" (0x004E4F49) lies in
MAIN's `.bss` range, and the DATARELOC stage emitted it as `(u32)(data2c_main_bss +
0x63EC9)`, so the keyword read "AMX_CLIP_ACT" + four pointer bytes and never matched.

Census (`out/render-bringup/tools/symcensus.py`, retail ELF bytes under every symbolised
word): **all 42 `main-bss` rows are numbers** (u16 pairs such as `004C0005`, ASCII tails
"ION", "NRM", "_IN", "KON", "VAL", "WIN", "YAN", "INK", "PRM", "ADJ", "COL", SJIS tails),
none a pointer; two more string tails were symbolised as main-data pointers ("TLE\0" at
0x45D918 -> `&D_00454760+0x4F4`, "LUE\0" at 0x45E46C -> `&jtbl_00455510+0x3C`). Several are
script keywords ("FADE_IN", "SHIP_IN", "AUTO_LOCKON", "MENU_BATTLE", "BT1_NRM", "LB_CYAN").

**Fix (generated overrides):** `out/render-bringup/tools/mk_datafix_overrides.py` writes
24 files `overrides/src/main_data/data2c_*.c` (45 words: the 42 `main-bss` rows, the 2
string tails, the microcode word 0x445384) with retail's literal. Result (`fix4`): the
actors animate like retail (`out/render-bringup/after4/`, `after4_o850/`).

### 2026-10-13: model bounds (same class as root cause 1)

`ModelUpdateBoundsProjectedMaybe_14ff90`: `BBoxUnion_13dea0(&bb[0], &v140)` reads v140 and
v150 as one min/max pair (retail sp+0x140/0x150); the port object put v140 at esp+0x30 and
v150 at esp+0x80, so the union read an unrelated qword as the max corner. Override
`overrides/src/main/model/ModelUpdateBoundsProjectedMaybe_14ff90.cpp` (one struct).

### 2026-10-13: latent fault exposed (ScreenMarkerSlotTick_31c190)

With the keyword strings fixed the golden run faulted at field ~22,000 (`fix4b`): read of
0x120 in `ScreenMarkerGetPinned_31bf10` <- `ScreenMarkerSlotTick_31c190` <-
ScreenMarkerTickAll <- ScreenMarkerMgrUpdate <- TaskStepStatus. The C passes two
uninitialised locals (`dummy0, dummy1`); retail's `jal` (0x31C1D4) sees the function's
own untouched `$a0`/`$a1`. The path is reached only once markers are created, which the
corrupted keywords had prevented. Override `overrides/src/main/ui/ScreenMarkerSlotTick_31c190.c`
passes `(arg0, arg1)`. Class: "uninitialised local as an argument" (PLAN.md); a name grep
finds no other `dummy` argument, the general census belongs to the protos lane.

### Verification (build `build/render-i686`, 2026-10-13)

* Screenshots: `out/render-bringup/compare_f08290.png`, `compare_f10000.png`,
  `compare_f12000.png` (before = the clean-i686 exe of 06:07, after, retail);
  side-by-side port/retail pairs for fields 7,350-16,000 in `after4b_o850/` (dense
  7,350-8,400) and `after4/`, `after4_o850/` (port vbl + 753 / + 850). Field 7,650 and
  8,150 (retail 8,480 / 8,982) match retail down to the character shadows on the sand;
  10,000 matches shot, pose and subtitle.
* Golden run (`fix5/run2.log`): 27,000 fields, no fault, exit 0; gamemode 7 (battle)
  reached, then the same 7/2100 phase as BRINGUP.md's open battle-tutorial divergence.
* ctest: 617 / 617 (`out/render-bringup/ctest2.log`).
* `python tools/ingest.py --check`: 142 overrides, 0 problems.
* Port-side edit outside overrides: `src/ps2/dmac/dmac.c` gained the env-gated VIF1 capture
  (`RG_VIF1_DUMP`, `RG_VIF1_DUMP_KICKS`; off unless both are set).

### Open

* Timing: the cutscene runs ~90 vbl ahead of retail inside the event (subtitle-aligned
  pairs use port vbl + 850, `after4_o850/`); flow, not rendering.
* Overlay data (NORMAL etc.) is loaded from the retail .BIN bytes, so it has no DATARELOC
  symbolisation; not checked further.
* `main-data-interior` (1,780 rows) can only be screened for text tails (done); a u16 pair
  that happens to fall inside MAIN's `.data` cannot be told from a pointer without type
  information.

## Proposals (stage rules, for the bring-up lane)

1. **`gap-pad` keeps the retail bytes.** Emit every DATARELOC gap as an initialised byte
   array with the snapshot's/ELF's content instead of zeros (census: 155 gaps, all
   non-zero in retail; 2 of them are VU1 microcode the game DMAs to VU1). Test: the
   `datacheck.py` comparison over the microcode table range reports 0 missing words; the
   two overrides `data2c_00436CF0.c` / `data2c_00436D08.c` then retire.
2. **No symbolisation inside `microcode` runs, of `main-bss` targets, or of string
   tails.** (a) microcode: A word inside a DATARELOC `microcode`
   object is a VU instruction, never a pointer (census: 1 site, 0x445384 in D_004452A0;
   `micro-unsym` already handles two). Test: `datacheck.py` reports 0 symbolic words in
   0x436980..0x445E80. (b) `main-bss`: census 42 rows, 0 pointers (u16 pairs and
   string tails, list above): keep the number. (c) a word whose 4 retail bytes continue a
   printable string started in the previous word (`symcensus.py`: 14 rows, 2 outside
   `main-bss`) is text. Test: `symcensus.py` reports 0 rows and every `main-bss` row is a
   literal; retires the 24 generated `overrides/src/main_data/` files
   (`mk_datafix_overrides.py`).
3. **`stack-block`: resolve shared-header types.** The coverage guard declined
   CameraBaseLookAt_15fae0 and ModelUpdateBoundsProjectedMaybe_14ff90 with "sizes unknown"
   for `Vec4` locals (`vec.h`: Vec4 16, Mtx4 64). Resolving the shared headers' types lets
   the rule build both blocks (retires the two overrides). Census of the remaining
   `manual-stack-block` rows (74) to recheck after it: CharaCmdGunShoot_228f80 (`cam`,
   v50, v60), EventCastSetPosition_258a50 (spA0/spB0: clang happens to place them
   adjacent today), NumPutBool_1b2860, NumPutNanInfStr_1b3990, MenuMobPreviewLoadPoll_35eee0;
   the "slot holds no C local" rows are mostly string buffers read by an over-wide extent.
