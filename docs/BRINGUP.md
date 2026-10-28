# Bring-up: current status and open items

What the game does on the port today, what is open, and where to resume. The full running
log (the early boot fixes 1-13, every dated checkpoint, the user play-test logs) is in
[bringup/BRINGUP-HISTORY.md](bringup/BRINGUP-HISTORY.md), verbatim; docs that cite
"BRINGUP.md (g)" or "2026-10-19 (c)" mean the entry with that heading there.

**Keep this file short.** Add a dated entry to the history file (newest first) and update
the sections below; don't grow this file with logs.

Status as of 2026-10-25 (late), work paused; all agent lanes stopped cleanly (tree builds, no
background jobs, nothing committed).

## Start here (next session)

Latest play-test exe: `out/playtest/rg-game-1028a.exe` (= 1026a + the boss monograph fix, 10-28); before it `out/playtest/rg-game-1026a.exe` (all gates pass; player notes `out/playtest/1026a-NOTES.txt`). Pre-x64 backup of the
whole tree: `..-backups` (`BACKUP_OK` lists the contents and the restore command). In
priority order:

1. **Hitches (USER play-test 10-25: audio + video stop together). Fixed in the tree 10-26, not
   play-tested.** The scripted scenes' read-back (fields 12,148-22,432, up to 145-190 ms under
   load) was the lens flare's 8x8 depth probe: in real-time play it is now served from the
   previous frame's copy (probe lag; window wait 2 ms mean / 7-10 max -> 0 / 4-5; tests and save
   states keep the exact read; run hash equal to 31,700 even with it forced on). Audio: adaptive
   cushion (grows after a starve up to 192 ms, decays after ~20 s) and a catch-up-aware refill (no
   drop after the catch-up burst). hitch.py now separates its own log-write stalls (most of the
   remaining 0.1-1.4 s "off-CPU" stalls on this machine). Card-load file reads: cold OS cache only,
   unchanged. Next: ship a play-test exe with it and ask the user; if gaps remain under load, the
   present off the game thread (coordinate with the Vulkan lane). docs/NATIVE-THREADS.md "3h.1";
   history "2026-10-26 (hitch2)".
2. **x64 (P7, USER committed):** the whole power-on route (32,000 fields, card saved) runs with the
   run hash and the audio command log EQUAL to i686 at every field (2026-10-26; 8 x64 bug
   classes fixed: float sqrt / libm rounding, data-layer alignment, small-integer and int-for-pointer
   call ABI, extern alignment, ptr32 gaps, crt structs, 32-bit varargs). Gates: X64-PLAN.md 0.7
   "Gates". Next: x64 save-state mode exhausts the address space below 2 GB (RG_SS=1 parts at
   field 26,674, regen fails; X64-PLAN 0.7 "Known (a)"),
   the failing x64 test harnesses (45 of 752 ctests: 32-bit assumptions in test programs and
   i686-only fixtures), a windowed x64 play-test exe, the 688 undecided virtual-call sites, the
   WOW64 samplers / `_`-prefix tools. docs/X64-PLAN.md section 0.7; history "2026-10-26 (x64)".
3. **Vulkan leftovers:** quiet-machine 144 Hz pacing matrix (`tools/native/present_pace.sh`,
   `tools/native/interp_window.sh` + `present_thread.py`); Linux CMake wiring (after x64).  The
   zero-copy FPS-counter / black-grab question is answered (2026-10-26, interp3): the window's own
   back buffer read in-process (`RG_WINDOW_SHOT_HOST=1`, `tools/native/vkshot.sh`) shows the
   picture and the detailed counter, pixel-identical to D3D11 at 6 power-on fields: no port bug;
   the grabs were Desktop Duplication + logo fades.  docs/NATIVE-VULKAN.md "Results 2".
4. **Remembered packets: CLOSED 2026-10-26 (rpkt)** -- the sorted path's node-header view / light
   packets are resolved at build time (`nr_chain_packet`), view packets are copied like lights,
   every walker refuses unreadable memory (`nr_game_ptr`), poison mode `RG_NR_POISON` +
   `tools/fixtures/poisoncheck.py` (ctests `fixtures.poison`, `fixtures.poison_control`), audit
   `tools/native/gameptr_census.py`. Left: item / material packets are still read in place at record
   time (live then; poison found no stale read); run `poisoncheck.py --suite drivers,soak` as one
   long pass (docs/NATIVE-RENDER.md "Remembered packets", history "2026-10-26 (rpkt)").
5. **Interpolation:** composite calls now pair by their parts (2026-10-26, interp3): battle
   posed 75.2 -> 92.4 % of strip groups (unpaired 16.3 -> 1.2 %), walk 86.1 -> 91.6 %; character
   step judder 0.35 -> 0.26; run hash unchanged.  Smoothness check `RG_INTERP_TRACE` +
   `tools/native/interp_trace.py`: headless 120 / 144 / 240 Hz even (switch ratio 1.0, motion at
   switches = 1 / presents-per-frame, no repeats / jumps).  Left: a **real-window** high-refresh
   check on a quiet machine (on the loaded 10-26 machine the game ran below real time with
   interpolation on, 17-19 ms per field, so no present fell between phases: each interpolated
   present waits ~20 ms for the GPU pass); a pipelined present was prototyped and removed (no gain:
   the cost is the pass, not the present call; NATIVE-THREADS.md "3h.2"); display delay kept.  NATIVE-RENDER.md "13c",
   history "2026-10-26 (interp3)".
6. **Coverage left:** Insectron ranks above E and the rank-menu entry; `soak.py drivers` not run
   as one pass yet; `RG_EE_FPU_EXACT` not wired; P6 PC features (PLAN.md).

Working method that held up: 3 agent lanes, each in its own `build/<lane>-i686`; never kill by
name pattern; background shell jobs die at 2 h, so split gate runs (`build_playtest.py --steps /
--gates`); regen rewrites the shared `out/fixtures/cards/save2` card -- restore it from its
backup after every regen; ship play-test exes only through `tools/playtest/build_playtest.py`.

## Where the game gets to

- **Power-on route** (`tools/trace/goldens/newgame_save2.input.txt`, re-timed 2026-10-19
  for the retwiden/wideret fixes): title, NEW GAME, opening FMV, field, first battle (won at
  ~26,510), town, save point, transporter menu, card saved at 31,700. Milestones in
  `fxlib.MILESTONES` and docs/TEST-FIXTURES.md: title 1500, field 8000, battle 23000,
  battle_won 26780, town 28840, save_point 30220, trans_menu 30780, saved 31700.
- **Card library** (docs/TEST-FIXTURES.md): 25 manufactured saves from chapter 1 to the late
  game plus save2, save2_battle2, factory, insectron. `bootcheck.py --all` 29/29 (boot to
  field control, main menu, walk, optional encounter). Battles are fought with
  `autobattle.py` (no crash or hang in 13 fights).
- **Retail comparisons:** `tools/trace/cardboot.py` boots any card on PCSX2;
  `tools/parity/parity.py` diffs ~260 game-state fields per frame against retail under the
  same input. The 2026-10-24 (night) sweep on the EE-float default found no ABI/logic divergence:
  224-239/257 fields identical on 8 of 10 walks, rng equal on 5; the rest is float ulps (division,
  adder; opt-in exact model open) and load timing (BRINGUP-HISTORY.md "2026-10-24 (night, parity2)").
- **Latest play-test build:** `out/playtest/rg-game-1026a.exe` (2026-10-26: 1025c + shadow-band fix (x3/x5/x6), lens-flare probe lag + adaptive audio cushion (hitch2), remembered packets (rpkt), composite pairing (interp3), settings overlay hold chord + device prompts (p6 pad), source volumes / output device / background audio (p6 audio), the x64 lane's shared-source edits; all play-test gates pass incl. `shop` and the full D3D11 render gate; notes for the player `out/playtest/1026a-NOTES.txt`, source manifest `out/playtest/1026a-manifest.txt`; `tools/playtest/build_playtest.py`; history "2026-10-26 (play-test 1026a)").
- **Checks on every change:** `regen.py` + `verify.py` (8/8), `bootcheck.py --all` (29/29),
  `mapcheck.py` (5/5 DRAWN), `camprobe.py` (camera = retail), ctest -j2 (713+).

## Native state (D9)

Native and default: file system, audio, threads/timing (frame-driven kernel, host pacer),
IOP/pad/memory card, VU0 math (vu0frame), DMAC, hwbus, VIF1/VU1 (translated programs incl.
INSECT), the native renderer draws every primitive class (checkpoint 9) and, since
checkpoint 10 (2026-10-24), runs without the GS model and the GS renderer: native GS state
block, GIF input, device and GPU-only local memory in `rg_native_render`. Since 2026-10-25 also libvu0 (`rg_native_vu0`, plain C lanes) and the overlays (native module
table `src/native/ovl`: per-overlay data segments, no retail-address arena; `RG_NATIVE_OVL`,
default ON). Gate `tools/native/link_audit.py check --forbid all --extra rg_ps2_hwbus` PASSES
with **no emulation library linked** (docs/NATIVE-ONLY.md), and since the D9 address gate
(history 2026-10-25 "D9 address gate") **no PS2 address arithmetic** in the compiled set:
`tools/native/addr_census.py --check` (ctest `native_only.addr_census`) 0 arith / 0 marker;
the game's register sites call the native services by name, identity markers stripped, the
free-heap probe uses the runtime heap's size; dead SDK tables / DMAtag ids / flag bits are
classified as data. D9 left: regression corpus + full playthrough, frame rate.
Since 2026-10-25 a second GPU backend, **Vulkan** (`display.backend=vulkan` / `RG_GPU_API=vulkan`;
D3D11 stays the default): gate-equivalent to D3D11 on Windows, the prerequisite for Linux
(docs/NATIVE-VULKAN.md, history "2026-10-25 (vulkan)"); since the evening also zero-copy presentation and
interpolation on Vulkan (history "2026-10-25 (vulkan present)"; the shop-close crash triaged there is fixed in 1025c, history "2026-10-25 (shopfix)").

**x64 (P7, strategy A, since 2026-10-25 evening):** `tools/build.ps1 -Arch x64` after
`tools/x64/derive.py` (derived tree `build/x64-src`; game/ is never re-ingested for x64). The
night lane found the crash / "nondeterminism" was 2 GB address-space exhaustion (NVIDIA x64 D3D11
reserves 1 GB below 2 GB), fixed by `rg_x64_va_fence()`. 2026-10-26: run hash and audio command
log equal to i686 at EVERY field of the power-on route (1-32,000; `tools/x64/pairrun.sh`); x64 gate
results in X64-PLAN.md 0.7. docs/X64-PLAN.md sections 0.6-0.7; history "2026-10-26 (x64)".
The i686 build stays the default and is unchanged (every port-source edit proven i686
object-identical).

## Resume list (in order)

1. **DONE 2026-10-24 (not play-tested): Widescreen stage 3, no aspect switch for menus**
   (USER). Menus, help sheets, shop / save / factory / insect screens no longer switch the
   screen to 4:3: the canvas, WIDE flag and 3D stay wide; a full-screen menu is laid out as
   one centred 4:3 element whose background is extended to the canvas edges by mirrored edge
   strips; slid-out panels stay hidden; the main menu's portrait circle (a copy of the field
   frame) is resampled so the party is in proportion. Original / 4:3 unchanged, run hashes
   identical across aspects. docs/WIDESCREEN.md "Stage 3"; build/wide3-i686, exe
   `out/wide3/s3final/rg-game.exe`, shots `out/wide3/a13`, `out/wide3/compare`. Checks (exe `out/wide3/s3final`, built 17:48 from the tree with the 17:42 EE-float flip and retimed goldens): regen --check 300 + verify 8/8, mapcheck 5/5, bootcheck --all 29/29, ctest -L "wide|render|settings" 47/47 (game_replay skipped), full ctest 721/721 (8 skipped: realdata, game_replay, readback_lag, link_audit_control); ingest --check 0 problems.
   **Second pass 10-24 (late): the gaps closed** (WIDESCREEN.md "Stage 3 gaps", BRINGUP-HISTORY.md
   "2026-10-24 (late): widescreen stage 3 gaps closed"; `out/wide4/`): every remaining menu and 32:9
   checked, tiled backdrops and the Revelation board fixed, strips faded; checks on the relinked exe
   `out/wide4/r1` (renderer lane mid-change): regen + verify 8/8, bootcheck 29/29, mapcheck 5/5,
   Original / 4:3 run hashes identical; full ctest 630/630 in `build/wide4-i686`.
2. **DONE 2026-10-24 (not play-tested): Renderer plan steps 2-4** (BRINGUP-HISTORY.md "2026-10-24:
   renderer plan steps 2-4"; docs/NATIVE-RENDER.md "Checkpoint 10"). The native-only rg-game links
   neither `rg_gpu` nor `rg_ps2_gs`: native GS state block + GIF input + worker, local memory on the
   GPU only, the device in `rg_native_render`; `link_audit.py check --forbid
   iop,kernel,vu0,render-dma,render-vu,render` PASSES. Both open items closed (ch09 glow = texel
   alpha > 0x80 under C = As; composite draw-back at x3 natively with upscaled-texel taps). Next:
   interpolated presentation (unlocked frame rate): no longer blocked by the GS model; needs the
   whole frame retained natively (2D / effect records, stable item identities).
   **Interpolated presentation: DONE, opt-in, not play-tested** (checkpoints 11-13, 2026-10-25;
   `display.interpolation` + `display.pacing = host` + `display.frame_rate` 120/144/uncapped):
   camera, objects, 2D / effects, character placement and (13) character poses; one game frame of
   display delay kept (BRINGUP-HISTORY.md "2026-10-25 (checkpoint 13)"). Needs a real 144 Hz play-test.
3. **DONE 2026-10-24: EE floats (USER decision: PS2 rounding by default)** (BRINGUP-HISTORY.md
   "2026-10-24: EE floats"). Game code runs with MXCSR = round toward zero + FTZ + DAZ by
   default (`src/native/threads/rg_nk.c` ps2k_init; `RG_EE_FPU=ieee` = the old host rounding).
   The float libm is the retail fdlibm float code in C (`src/crt/crt_eelibm.c`: sinf / cosf /
   tanf / asinf / acosf / atan2f / powf with KernelRemPio2f, IeeeSqrtf, Scalbnf), used under
   the EE MXCSR, host libm under `ieee`; checked by `tools/parity/eelibm_check.py` (exact
   model build 100 % of 173,933 retail references, shipping build within 1 ulp). Gun cycle
   **16 VBlanks** as retail (was 14). Goldens re-timed and landed 17:42 local: route only
   moved its help-sheet STARTs (milestone fields unchanged), `boot_save2_battle2` re-timed
   (battle2_won 7,250, battle2_field 7,700); regen + verify 8/8, saveedit make, bootcheck
   29/29, mapcheck 5/5, ctest 721/721. **Open:** the opt-in exact build (`RG_EE_FPU_EXACT`: eediv_cc.py as
   compiler launcher for rg_game_* and the libm; plan in `out/parity/eefloat/README.txt`) is
   not wired; never the shipping default (D9).
4. **Fresh play-test build** after 1-3 (`build/play-i686` -> `out/playtest`, bootcheck +
   mapcheck first; `tools/fixtures/make_allcard.py` refreshes the 28-file test card).
   **2026-10-23: built `out/playtest/rg-game-1023a.exe`** (before 1-3; has the 10-22/23
   launch, pacer, text, audio and label fixes). bootcheck 29/29, mapcheck 5/5, verify 8/8,
   ctest 720/720 (logs `out/regress1023`). Launch: double-click the exe (`data` junction
   beside it) or play.bat / play-from-save.bat / play-test-save.bat (28-file card).
   **2026-10-23: `out/playtest/rg-game-1023b.exe`** = 1023a + items 6/7 fixes (re-ingest, 34c170
   override); the three .bat files launch it. bootcheck 29/29, mapcheck 5/5, verify 8/8 (run hashes
   equal to 1023a), ctest 720/720 (logs `out/regress1023b`). Build note: rg-game is
   EXCLUDE_FROM_ALL, so use `cmake --build build/play-i686 --target rg-game`.
   **2026-10-24/25: `out/playtest/rg-game-1024a.exe`** = items 1-3 + item 8 + the stack-block
   re-ingest (22:15) + renderer checkpoint 10 + the parity2 data overrides (22:45) + the 23:09
   Insectron overrides (full recompile of `build/play-i686`, 23:37-23:58); the three .bat files
   launch it. regen --check 300 + verify 8/8, bootcheck --all 29/29, mapcheck 5/5, ctest -j2
   722/722 (8 skipped), `link_audit.py check --forbid iop,kernel,vu0,render-dma,render-vu,render`
   PASS (4 pending libs). Test card `saves-all` refreshed (make_allcard: now 30 files, + zshop /
   zshop2 as FILE 29 / 30; the 10-23 card is in `out/regress1024a/saves-all.1023`). Windowed
   smoke: D3D11 native device, exe-relative data, title at 1500, rc 0. Widescreen re-shoot vs
   `out/wide4/f_new` (r1): every run hash equal, menu edge strips pixel-identical (sheets
   `out/regress1024a/widecmp/`). Logs `out/regress1024a`; history "2026-10-25: play-test build 1024a".
   **Known crash in 1024a (fixed in tools/ + game/ since, 2026-10-25 soak):** main menu -> Factory ->
   Place crashes (raw callback word in D_00468380); rebuild before handing it out. History
   "2026-10-25 (soak)".
   **2026-10-25: `out/playtest/rg-game-1025a.exe`** = 1024a + the Place crash fix (01:21 re-ingest),
   SysMsgPostMaybe byte fix, Insectron reward overrides, native VU0 + native overlay modules
   (`RG_NATIVE_OVL` ON, reconfigured), opt-in interpolation, parity data overrides; the three .bat
   files launch it. regen --check 300 + verify 8/8, bootcheck 29/29, mapcheck 5/5, ctest -j2
   734/734 (8 skipped), `link_audit --forbid all --extra rg_ps2_hwbus` PASS, Place repro rc 0 (no
   exception), factory.py + insectrun.py (no --title) pass, windowed smoke OK. Logs
   `out/regress1025a`; history "2026-10-25: play-test build 1025a".
   **2026-10-25: `out/playtest/rg-game-1025b.exe`** = 1025a + the return-to-title / game-over fix
   (protos short-agg), iostream overrides, D9 address gate, protos manual-rows fixes (09:22 ingest),
   renderer checkpoint 12; built and gated by `tools/playtest/build_playtest.py --tag 1025b`: verify 8/8,
   bootcheck 29/29, mapcheck 5/5, link_audit + addr_census PASS, render_gate PASS, insectrun --title,
   gameover, factory, Place repro, windowed smoke OK. Logs `out/regress1025b`; history "play-test build 1025b".
   **2026-10-25: `out/playtest/rg-game-1025c.exe`** (+ `rg-game-1025c.map` for the crash log) = 1025b +
   the shop-close crash fix, crash log file, FPS counter (`display.fps_counter` off / fps / detailed),
   Vulkan zero-copy present + power-on fix, checkpoint 13 poses, soak2 overrides. All play-test gates
   incl. the new `shop` gate, full D3D11 render gate, ctest 750/750. Logs `out/regress1025c`; history
   "2026-10-25 (shopfix)". Not play-tested yet.
   **2026-10-26: `out/playtest/rg-game-1026a.exe`** (+ `.map`) = 1025c + the shadow-band fix, hitch2 (lens-flare
   probe lag, adaptive audio cushion), rpkt, interp3 pairing, p6 pad (overlay hold chord, device prompts), p6 audio
   (source volumes, output device, background audio), the x64 lane's shared-source edits. All play-test gates incl.
   `shop` and the full D3D11 render gate, ctest 755/755 + fixtures 13/13. Logs `out/regress1026a`; source manifest
   `out/playtest/1026a-manifest.txt`; history "2026-10-26 (play-test 1026a)". Not play-tested yet.
5. **DONE 2026-10-22 (not play-tested): Launch by double-clicking the exe** (no .bat): data next to the exe or via config,
   hardware GPU by default when windowed, saves beside the exe, the rg_slots low priority
   and slot wait only for headless/test runs; every flag/env stays an override.
   **Settings must persist** (USER 10-19): `rg_settings_save` exists and the overlay saves
   only when a settings path is given (`rg_settings_apply_args` -> `cfg.settings_path` in
   rg_game_main.c). **2026-10-22: done for windowed runs** -- with no `--settings` and no
   `--headless`, rg-game loads `settings.ini` beside the exe first (`--set`/`--preset` still
   override) and the overlay's Save row writes it. Not yet: autosave on every menu change;
   not play-tested (built in build/play-i686 only).
   **Autosave (10-22):** closing the overlay (Back/F1) after any change writes the settings file once (`close_menu` in rg_menu.c); Save row still saves mid-session. Not play-tested.
   **Dirs (10-22):** no `--data`/`$RG_DATA` -> `<exe dir>/data` if it exists; no `--saves`/`$RG_SAVES` -> `<exe dir>/saves`. GPU: hw by default under the native renderer (`gpu_choose`).
   **rg_slots (10-22):** BELOW_NORMAL priority + slot wait only with `--headless`; windowed = normal priority, no slot. Overrides: `RG_SLOTS_PRIORITY=normal|low`, `RG_SLOTS=1|0`.

### User play-test 3 (2026-10-19, out/playtest/rg-game-1019b.exe) -- to triage on resume

Ranked by severity (crashes/breakage first). Each needs a repro from a card
(`saves-all` FILE NN or a library card + input script), a retail check where it's a
"looks/sounds different" item, and a regression check once fixed.

6. **Entering the Revelation flow crashes the game.** (Main menu -> Revelation; the item is
   flashing = an item to slot.) **DONE 2026-10-23 (landed in build/play-i686, play-test exe 1023b).**
   Repro `tools/trace/goldens/revelation.input.txt` (late_game card): access violation reading
   0x77C in `RevelationBoardPktSetColorLerp_34ce10` (from RevelationBoardDrawSprite_34c170 <-
   RevelationBoardDraw_349e70) as the board opens. Not the const-write class: a register
   pass-through the stages missed -- retail 34c170 forwards $a0 (board) and $f12-$f19 + one
   stack float unchanged; the decomp spelled them as uninitialised locals (`u0`, `FArg`), so the
   board pointer was 0. Override `overrides/src/main/menu/RevelationBoardDrawSprite_34c170.c`
   (real 7-int + 9-float signature, the caller already passes it); `FArg` pattern is unique in
   game/. altlink exe: board, Place -> Thunder Stone, Flash Sword learned, back out, no crash.
   Landed: rerun on build/play-i686 (`tools/bringup/cardrepro.py`, shots out/regress1023b/rep_item6):
   board + slot filled 4700, Flash Sword in the ability list 5050, no exception.
   **2026-10-24 (night):** the board's flashing slot looked different in every link: sprite table
   D_004539F0's w/h word 0x00400040 was a pointer to DataTableCompareThunk_400040 (data2c); fixed with
   21 more packed words in `overrides/src/main_data` (`tools/parity/datafix_packed.py`); three links
   byte-identical, slot as retail (BRINGUP-HISTORY.md "2026-10-24 (night, parity2)").
7. **Any action from the item menu's context menu breaks the game** (Items -> pick an item
   -> context menu -> Use / etc.). Likely the same class as 6 (menu code; possibly a
   stack-block "needs-human" row such as MenuItemUseTargetState `v80`, or a retwiden/wideret
   miss). Check the census rows for these menus first.
   **DONE 2026-10-23 (re-ingested, landed in build/play-i686, play-test exe 1023b).** Symptom: soft lock,
   no crash: after Use (any of the 6 rows) the context menu stays, the hand cursor goes, no input
   is taken. Cause: `MenuItemCmdFadeSequenceStep_2adce0` declares its phase word
   `extern const s16 D_004824F0 __attribute__((section(".sdata")))` (mwcc load-hoist lever) and
   writes it through `W = ..`; clang deletes stores to a const object, so the phase never leaves 0.
   The dialect `const-data` rule (tools/portxform.py) missed decls with a trailing
   `__attribute__`; regex fixed. Census `tools/census/constwrite_census.py`: 59 such writes in 13
   files (also `MenuPartyFadeSequenceStep_2b9240` = Allies member commands, PadUpdate_1843a0,
   ItemSpriteSpinDrawCb, NpcObjTableCharaLoadUpdate, INSECT/NORMAL cursor-bob and seq files);
   the rule rewrites 177 files. Verified with `tools/bringup/altlink.py` (test exe, one TU
   swapped): `tools/trace/goldens/item_use.input.txt` reaches the target panel and backs out;
   build/play-i686 stayed stuck. Landed: ingest (178 files), STALE overrides TargetSlotDraw_320b00 /
   DrawListEndPrim_141a20 (read-only consts) re-hashed, census now 0 writes; item_use rerun on
   build/play-i686: target panel at 4100, back to the field menu at 4310 (out/regress1023b/rep_item7).
8. **Low-res weapons, monsters and character parts: FIXED 2026-10-24 (not play-tested)**
   (history entry "2026-10-24: item 8"). Cause: the battle renderer draws each character
   through a page-offset view of one 512-wide buffer and copies each part's box into the
   frame twice; a texture upload into another page of that buffer between the copies made
   the whole target `stale`, so the second copy read the part from the 1x mirror (one colour
   per native pixel). Not the texture filter (TEX1 is bilinear there either way). Fix in
   src/gpu: per-page staleness (`Rt.stale_pages`: stale pages reload alone, direct sampling
   refused only where read pages are stale), page-for-page copies at the internal resolution
   when one view evicts another (`rt_copy_pages`, backend `rt_copy`), the 2-texel bilinear
   margin accepted for GS-path direct sampling of another target, the filter rule now
   "drawn since upload" (`RG_NR_TEXRT=overlap` = old), and `lazy_miss.patch` landed. Controls
   / tools: `RG_GPU_RT_PAGECOPY=0`, `RG_NR_FILTLOG` + `tools/native/filtlog.py`,
   `RG_NR_DBGSKIP`. Verified on the field-7000 x3 repro (`out/lowres/final_ba.png`). Open:
   native immediates still decode 6,672 target reads from the mirror (effect passes: format
   views, reads 3+ texels past a target); retail oracle not run; play-test. **2026-10-25
   (checkpoint 12b, docs/NATIVE-RENDER.md):** reads past a target and binds over another
   format now at the internal resolution (`RG_NR_REINT=1`, default; images unchanged at x1 and
   x3: the chain feeds mesh textures); sampling a target as another format (`RG_NR_REINT=2`)
   works but makes the CT16 dust effect blockier at x3: off.

9. **Text looks odd at any aspect other than 4:3** (cause found, fixed 2026-10-22, history
   entry "widescreen text"). Fonts are point-sampled sprites squeezed to 0.75 by stage 2; the
   upscaled sprite path snapped them to native pixels, so every 4th texel column was dropped at
   any internal res. Now squeezed packets snap only Y (`gpu_set_im_xfree`), and squeezed
   point-sampled sprites get a sharp-bilinear X filter (nr_draw.hlsl `PF_SHARPX`, set in
   gpu_core.cpp): nearest in Y, in X a 2-tap box over one output pixel, so every column survives
   at 1x and 3x with ~1 px soft edges (crops out/textcheck/sharp/). 4:3 byte-identical. Open:
   not play-tested windowed; squeezed portraits are a touch softer at 1x.
10. **Saving slows everything down and the audio suffers.** Measured 2026-10-22 (RG_MC_TRACE=1,
   golden save at ~31,600, saves on the B: HDD and on C: NVMe): a save is 11 card ops, 24 atomic
   temp+rename writes (130 KB; card1.card + card1.txt rewritten on every open/flush/setinfo), no
   fsync, no backup on a first save; 4-10 ms host time per op, ~55 ms total, one op per field.
   Not the main cost: save-menu fields run 13-17 ms (gs_wait-dominated) vs ~10 ms in town. Next:
   RG_FIELD_TIMES on a windowed paced save + audio underrun counts; card-side option is moving
   commits to a worker (~5-10 ms/op saved).
11. **Opening, using and closing a shop menu causes a slowdown.** Measured 2026-10-22 (card
   zshop2 + talksweep.py, BRINGUP-HISTORY): open/browse smooth; the CLOSE runs ~0.55 s at
   ~15 fps: 3D scene + fading UI drawn every field, GS worker bound (24 rt_creates, 52
   writebacks, read-back waits per field). Cause found + fixed 2026-10-22 (BRINGUP-HISTORY):
   the pacer's phase-cost estimate excluded the GS-worker wait, so a worker-bound 16 ms field
   looked cheap and catch-up ran 4-field batches (65 ms frames). Now 1-2 field frames: close
   new-image median 32 -> 23 ms, frames > 40 ms 7-10 -> 2-3. Left: ~16 ms worker/field
   (GS-model transfers ~6 ms, target churn ~2 ms) and one 72 ms batch at the start.
12. **Subtle popping in the audio.** 2026-10-22: cause found and fixed in the host, not
   the engine. Engine WAV clean (0 clicks); every pop was a host stream splice (device
   starve, silence pad after a starve / pacer re-anchor, dropped frames), now crossfaded
   (`rg_audio_declick`, docs/HOST.md "Audio"); loaded A/B 193 clicks -> 0. Scanner
   `tools/native/audio_popscan.py` (docs/NATIVE-AUDIO.md "Pop scan"). Left: needs a
   play-test by ear; pads still cause soft ~40 ms dropouts when fields run long.

## Open items (not scheduled)

- **Stack-block census:** DONE 2026-10-24 (BRINGUP-HISTORY "2026-10-24 (sblock2)"): the
  function-pointer resolver is in the protos stage (`tools/stages/sbresolve.py`), all 103
  needs-human rows have verdicts (0 left; `census/stackblock_sites.tsv`), 6 real overruns
  fixed by rule, the 5 padded blocks reviewed. Left: the 4 `override: BUG` rows stay the
  PtalkFindPairRow / FactoryStep overrides' (no stage rule yet: macro use, inline struct);
  overlay vtables are not in the tree (an overlay receiver keeps a site open). docs/PROTOS.md.
- **Insectron-only:** `InsectronRewardLookupMaybe_3e84f0`: DONE 2026-10-25 (soak lane, overrides
  3e84f0 + 319800; slot 0x70 = DataTableFindByKey_3680a0 checked at run time). **Reached
  2026-10-25 (cov3)**: card `insect_final_s` (caged insects via `saveedit.py --section-insects`)
  -> receptionist -> the Rank E final played and won by `insectstory.py` -> Battle Feed x5
  (insectron_param_EN key 1, retail's data) in vars 0x73 / 0x74 and the inventory, rank var 5 = 2
  (BRINGUP-HISTORY "2026-10-25 (cov3)"; docs/TEST-FIXTURES.md "Story Insectron").
- **Factory production:** reached 2026-10-25 (cov3): Divine Blessing produced from the Healing vial
  plan and in the inventory (`factory.py --card factory_prod --plan healing_ath --produce --save`);
  the soak2 stop was game rules (Athanor needed, not in the Place list until unlock group 34).
- **Widescreen gaps:** closed 2026-10-24 (late), docs/WIDESCREEN.md "Stage 3 gaps": every
  menu the cards reach checked at 4:3 / 16:9 / 21:9 / 32:9 (Allies, Strategy, Revelation,
  Recorder, Frog Log, System, battle command menu, area map, Dorgenark menu and Galaxy Map,
  NPC labels / damage numbers); tiled backdrops and the Revelation board fixed; side strips
  faded toward the canvas edge. Left: the strips are still mirrored art (dimmed), not new
  art; not play-tested.
- **Linux:** rg-game **links** (2026-10-24, cross build `build/linux-i686`): 0 undefined
  symbols without a provider (`tools/native/elf_audit.py`), GLIBC_2.34, `link_audit.py check`
  PASS on the ELF map. No GPU backend: the headless renderer (walker -> software GS). Not run
  (needs WSL / a Linux box); save states Windows-only; Vulkan / SDL_GPU backend checklist in
  docs/LINUX.md.
- **Black headless shots on a native-only exe** (2026-10-22, build/play-i686): software-GS
  part FIXED. A native-only exe has no VIF1/VU1 models; the frame chain runs only through the
  native walker (`rg_vif1_chain_hook`), installed by `gpu_start` with the GPU renderer. With
  `RG_GPU` unset every VIF1 send was dropped, the end-of-frame VIF1 interrupt never came, and
  the title stalled. runtime.c `gpu_choose` now defaults to `RG_GPU=hw` in native-only exes
  (warns on an explicit `RG_GPU=sw`); `gpu_start` retries on WARP if no hardware adapter.
  Open: `RG_RENDER=emu` is still black (unsupported on native-only, NATIVE-RENDER.md); rg-game
  should refuse emu / warn instead.
- **Build host** disk cleanup (`~/old_work.txt`) waits on the user; then LLVM + remote
  compiles.
- **Return to title / session shutdown:** FIXED 2026-10-25 (history "2026-10-25 (stream close)"):
  every game-session shutdown (Insectron Return to title; game over -> title shares
  `GameSessionShutdown_1f5bf0`) hung in the stream-slot close, then in the effect-table
  teardown. `insectrun.py run --title` reaches TITLE; game over -> TITLE -> CONTINUE -> field
  control: `tools/fixtures/gameover.py run` (2026-10-25 (sweep)).
- **Full playthrough** on the native build (P5 gate). Machine stand-in: `tools/fixtures/soak.py`
  (2026-10-25: 346k -O2 + 176k UBSan + guard fields over 28 cards; 1 crash found and fixed, open
  list in history "2026-10-25 (soak)"). **Widened 2026-10-25 (soak2)**: `--wide --maps` (cards with
  the sections' abilities + Burning Strike, 77 jump-point cards, autobattle with abilities / items /
  leader switch / gun, `soak.py fights`): 309k -O2 + 211k UBSan fields, 39 zones (planets 1-9: 31 of
  36), 57 abilities used, factory power cords + Run accepted; 2 overrides (ability-list scroll thumb
  NaN, AiRouteMoveToPos threshold frame), history "2026-10-25 (soak2)". Left: no story progression,
  factory production stops on game rules (material processing), story Insectron unreachable,
  autobattle leader-switch loop.

## User play-test findings and their status

| Date | Finding | Status |
| --- | --- | --- |
| 10-18 | Right-stick camera reversed | Fixed: `input.camera_convention` pc (default) / original |
| 10-18 | Walking instead of running on turns | Fixed: round-stick-to-DS2 shaping, `input.stick_ds2_range` |
| 10-18 | Stutter at loads, battle start/end | Fixed: host pacer (rg_pace catch-up rule), battle CLUT read-backs removed (renderer ckpt 9), first-frame pre-warm |
| 10-18 | FACTORY crash | Fixed: VU0 per-file register state (vu0frame) + `factory_FactoryStep_5069e0` stack block |
| 10-18 | Map not drawn (ch06/09/12/13) | Fixed: native 16-bit mesh UVs |
| 10-18 | Low-res sword, gun, faces | Retail look (GS nearest filter); `graphics.texture_filter` default now bilinear for 3D |
| 10-18 | Gun fires inconsistently | Fixed: 64-bit command masks (stage `wideret`); the 14 vs 16 VBlank cycle (EE rounding) fixed 10-24: EE floats by default, 16 as retail (not play-tested) |
| 10-18 | Widescreen UI stretched | Fixed: stage 2 (`graphics.ui_layout`) |
| 10-18 | No EXP / money after battles | Port bug, fixed: stage `retwiden` (u8/s16 returns through vtables) |
| 10-19 | Darker text (caption font) | Fixed: GS alpha > 0x80 blend factor (`RG_NR_ASAT`) |
| 10-19 | Load menu rows grey | Not a bug: the menu's own fade (port 172-198, retail 186) |
| 10-19 | Menus/tutorials change the aspect | Done 10-24 (widescreen stage 3), not play-tested |
| 10-19 | Needs .bat files to launch | Done 10-22 (double-click the exe), not play-tested |
| 10-25 | Crash after buying Grand Edge and closing the shop (1025b) | Fixed in 1025c: stale light packet (renderer copies remembered packets); regression `tools/fixtures/shopcrash.py`, ctest `fixtures.shopcrash` |
| 10-25 | Frequent hitches, audio and video stop together (1025b) | Lens-flare read-back and audio cushion fixed (hitch2), in 1026a, not play-tested; part machine load |
| 10-25 | Wants an FPS counter | Done in 1025c: `display.fps_counter` |
| 10-25 | Shadows have strange lines (bands) going through them (1025b/c) | Fixed 10-26, in 1026a, not play-tested: internal res x3 / x5 / x6 broke the shadow map's CT16 channel shuffle (sprite snap float error; `nr_draw.hlsl gs_uv16`); ctest `fixtures.shadowbands` (`tools/shadow/shadowcheck.py`); history "2026-10-26 (shadow bands)" |
| 10-27 | Monography shot platforms on an early boss expire instantly (1026a) | Fix in play-test exe `out/playtest/rg-game-1028a.exe` (10-28, all gates incl. render PASS, `out/regress1028a/summary.tsv`), not play-tested, not reproduced in game (no card at that boss; status 31 code never runs in the first battle, RG_BREAK armed). Cause: boss monographs (`ObjTypeMonographUpdate_371a70`, kind 5) are removed unless the boss's status 31 time left (vtable 0x1D0 -> `CharaStatusTimeLeftInt_3b6cd0` -> 0x1CC `CharaStatusTimeLeft_3b6d00`) is > 0; 3b6d00 took the status id as `s64`, every caller passes 4 bytes, so on i686 the high word was a stale stack word, `ids[slot] != id`, time left 0. Override `overrides/src/main/chara/CharaStatusTimeLeft_3b6d00.cpp` (s32 id, widened inside; retail compares the sign-extended $a1). Class census `tools/census/s64param_census.py`: the other 2 table-reached s64 parameters use only the low 16 bits. Test exe `out/mono1027/alt/rg-game.exe` (altlink off build/pt1026a-i686) |

## Fix classes found in bring-up (where the rules live)

Most port bugs were ABI/typing gaps between the decomp's C and the EE, fixed mechanically
by ingest stages (tools/stages; docs/PROTOS.md, docs/UB-AUDIT.md):

| Class | Stage / rule |
| --- | --- |
| Arguments the decomp dropped or spelled as uninitialised locals | protos `missing-*`, passthrough, def-widen (asm-gated) |
| Struct return through a hidden pointer | protos `sret-call` |
| 64-bit values cut to 32 bits | protos wide-ret, stage `wideret` (multi-level chains) |
| 1/2-byte returns read through wider function pointers | stage `retwiden` |
| Locals the callee reads/writes as one block | protos `stack-block` (+ asmflow large frames, clayout struct sizes) |
| Arguments dropped by a caller's own short declaration of a callee kept out of the header (by-value union / struct parameter): the callee reads a stale stack word | protos `short-agg` (2026-10-25 sweep: word-size aggregates, the 4 `HandleTableGet_1a1d50` effect sites; their overrides retired); the rest overrides (3 MSL iostream sites: sret view / short thunk); ctest `protos.deficits` (`tools/bringup/protos_deficits.py`: fails on a short or sret-view call without an override) |
| Over-aligned aggregates by value (MSVC x86 passes their address), u128 views with an extra GPR lane, narrow returns read through C++ pointer / wider views or a macro-typed definition (`#define RT bool`) | protos `agg-view` / `agg-bits`, `u128-view` extra lane, `ret-narrow-view`, type macros (2026-10-25 manual-row close-out: FontDrawGaiji colours, VecSolveDistanceConstraint floats, CharaCollClamp bool, ObjRecHasFlags6 test); every manual row verdicted in `census/protos_manual.tsv`; ctest `protos.manual`, `protos.irabi` (clang-IR ABI of every manual call pair, `tools/bringup/protos_irabi.py`; `--all` = every direct call of the game) |
| Busy-waits on a driven (fiberless) thread that retail ran at once from a SignalSema | driver point at the signal (override `SoundRpcWorkerKick_1bd6a0`, 2026-10-25); census `tools/census/driven_wait.py` (151 waking loops, 0 busy-waits left), ctest `spin.driven_wait` (+ control); docs/SPIN.md "Driven threads" |
| Call argument evaluation order, wide shifts | dialect `arg-order`, `wide-shift` |
| Pointer words printed as data | datareloc rules |
| Packed numbers (s16 pairs) printed as pointers: host address in the data, behaviour changes with every link | `overrides/src/main_data` (10-13 `main-bss` rows; 10-24 `tools/parity/datafix_packed.py`, census `pairptr_census.py`); stage-rule candidate |
| VU0 register state | stage `vu0frame` |
| Function passed as `void *` (C++) | stage `fnvoid` |
| Uninitialised-branch / flow-off-end UB | build flags (`-ftrivial-auto-var-init=zero`, `-fno-strict-return`, UB-AUDIT flags) |
| EE float rounding | runtime MXCSR mode (`RG_EE_FPU`, chop by default since 10-24) + retail libm (`src/crt/crt_eelibm.c`) |

## Tools (bring-up)

Fixtures and checks: `tools/fixtures/` (run_from, regen, verify, bootcheck, play, retime,
tapsearch, steer, saveedit, make_allcard, autobattle, mapcheck, camprobe, rewards,
guncadence, montage, soak, gameover); retail: `tools/trace/cardboot.py`, `probe.py`; parity:
`tools/parity/` (parity, sweep, rngtrace, divclass, fpcensus, fpboundary, eelibm_check, eediv/listing,
eediv/ee_interp, pairptr_census, datafix_packed); `cardboot.py --plan revel` (Revelation board on retail);
link-layout probe: `tools/bringup/altlink.py --first OBJ`; landing staged goldens: `tools/fixtures/stage_swap.py`; census:
`tools/census/driven_wait.py` (driven-thread busy-waits), `tools/census/stackblock_census.py` (+ `sbpadcheck.py` padded slots, `sblisting.py`
listings from a protos_pre pickle), `tools/bringup/wideret_census.py`, `tools/bringup/protos_deficits.py`
(short call sites the protos stage left; `--manual`, `--ir`), `tools/bringup/protos_irabi.py` (clang-IR call ABI
vs definitions), `tools/bringup/protos_manual.py` (manual-row verdicts), `tools/bringup/vslot_reads.py`
(vtable-slot methods vs argument registers); hangs: `tools/fixtures/hangsample.py PID`; perf:
`tools/perf3d/stutter.py`, `RG_FIELD_STATS`; renderer: `tools/native/render_gate.sh` and
the NATIVE-RENDER.md tools table; shadow maps: `tools/shadow/` (shadowcheck, shadow_ab, pam2png, vramrect + `RG_NR_RTDUMP`); play-test exe: `tools/playtest/build_playtest.py --tag TAG --note ..`
(ingest check, own build dir build/pt<TAG>-i686 with the play-test cache, every play-test gate, copy to
out/playtest + .bat update, windowed smoke; `--steps` / `--gates` re-run parts). rg-game debug env: `RG_STATUS_EVERY`, `RG_BREAK`,
`RG_BREAK_SPEC`, `RG_WATCH`, `RG_HASH_LOG`, `RG_HEAP_LOG`, `RG_VEH` (history file,
"Diagnostics added").
**Crash log (2026-10-25):** an unhandled exception is reported on stderr AND appended to
`rg-game-crash.txt` beside the exe (play-test: `out/playtest/rg-game-crash.txt`) with the
field, the function names from the link map beside the exe (`rg-game-<TAG>.map`, copied by
`build_playtest.py install`) and a small minidump `rg-game-crash.dmp` (dbghelp, stacks only);
`RG_CRASH_LOG=FILE` / `=0` (stderr only). Name a stderr report offline with
`tools/native/crashsym.py MAP LOG`. Navigation from a card without save states:
`tools/fixtures/cardwhere.py`; the shop-close regression: `tools/fixtures/shopcrash.py`; the real
window with host overlays (FPS counter): `tools/native/wincap.py [--printwindow]`; cmake / ctest
of a play-test build dir from an agent shell: `tools/playtest/vcrun.py BUILD -- ctest -j2`.
