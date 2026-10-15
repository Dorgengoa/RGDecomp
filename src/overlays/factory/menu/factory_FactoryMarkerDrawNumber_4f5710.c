#pragma optimization_level 3
/* ====================================================================
 * SESSION 38 (2026-09-02), tag fg38.  BYTE-IDENTICAL -- 472/472 words, 0 bad.
 * Arming in the SAME run: factory_FactoryStep_5069e0 = MATCH, factory_FactoryRectFrameCorner_509f10 = bad 11 /
 * md5 977182cbe9b7, and the `#pragma optimization_level 4` twin of this file = `?` len 0x764
 * vs 0x760 (473 words), which proves the level pragma is READ and that the scorer still
 * fails a wrong length.  The chain from s37's 471-word baseline (md5 28c3ee5a8bda):
 *
 *  A1  `d = *(s32 *)(s32)&digits[j];`      475w   the s37 00500630 lever, never tried here.
 *      It BREAKS THE FOLD at 0x004F5B70 (retail's `addu/addiu 0xC0/lw 0(r)` word for word)
 *      -- the "project-wide toolchain class" of s37 is REFUTED, the shape is reachable from
 *      C.  The +4 are four RELOADS of t->f10 after stores into `digits`: the cast makes the
 *      array address-taken and mwcc then invalidates the cached load at every store.
 *  B1  + `s32 n10 = t->f10` for the four PRE-RENDER uses      472w  94 bad  EXACT LENGTH.
 *      (declaration position and init position of n10 are INERT: 4 cells, one object)
 *  C2  + `void *g;` declared AFTER `s32 nd;`                  50    closes s4<->s5 (44 w):
 *      nd and the render-loop j share $s5, g is $s4; `nd` declared FIRST is the same object.
 *  D2  + `s16 n10`                                            41    (D1 n10 before val: 43)
 *  G2  + `bx = x0;` copy named, `x0 = bx;` at the re-derive,
 *      bx declared FIRST                                       9     (declared LAST: 39)
 *  E4  + `s32 b;` before `s32 a;` AND `b = 0; a = 0;`         4     (either alone: 6 / 11)
 *  I1  + first arm's `xj` inlined (`x0 + j * w` at both uses)  3    (= naming the product)
 *  K3  + `if (nd > 1)` for `if (nd >= 2)`                     +1w   gives retail's `slti $at`
 *      ([[at-compare-class]]) but rotates the whole setup block's caller-saved map;
 *  R4  + `hgt = t->f18 * 16;` BEFORE `w = t->f16 * 16;`        1    restores the map: 1 bad.
 *  U1  + `started = 1;` + `#pragma optimization_level 3`      MATCH.
 *      Every `= K` spelling at -O4 HOISTS the constant into the loop preheader (+1 word:
 *      K = 1 / 2 / -1, u8 / s16 / s64 / u32, init at the top, `= 1` at block end -- 9 cells);
 *      `+= 1` is the right length but `addiu t3,t3,1` for retail's `addiu t3,zero,1`.
 *      -O3 rematerialises the constant in place, exactly [[factory-optimization-level-3]];
 *      s37's knob screen on this unit tried levels 0/1/2 only.
 * INERT at 3-9 bad (one object each): `2 <= nd`, `!(2 > nd)`; first-arm operand swap
 * `xj + (t->f16 - 1) * 16`; `2 <= nd` etc.  WORSE: `if (nd < 2) {..} else {..}` +10w (mwcc
 * lays the if-arm first and relocates the a-block); `nd - 1 >= 1` (addiu/blez, 3 bad).
 * Under K3, bx's declaration position is INERT (5 cells) and hgt declared FIRST is 35 bad,
 * `w` first / `top` first / a separate col counter / a,b order all +1 -- only R4 pays.
 ==================================================================== */
/* ====================================================================
 * SESSION 37 (2026-09-02), lane fg37a.  Board 393 -> 396/409 = 96.82% count,
 * 120,424/134,224 = 89.72% bytes.  Arming pair held in EVERY run:
 * factory_FactoryStep_5069e0 = MATCH, factory_FactoryRectFrameCorner_509f10 = bad 11 / md5 977182cbe9b7.
 *
 * === LANE fg37a, 2026-09-02, factory session 37.  54 cells.  STILL 471 words / ONE WORD SHORT.
 * Baseline RE-CONFIRMED md5 ab3f8a453176, 471 words, len 0x75c vs 0x760.  h.py's "bad 257" is a
 * SHIFT ARTIFACT; the REAL aligned residue (ours[k]<->retail[k] for k<=279, ours[k]<->retail[k+1]
 * for k>=280, branch immediates masked) is 89.  Scorer: build/fg37/arms/f5710/res.py.
 *
 * *** BEST OBJECT THIS SESSION: md5 28c3ee5a8bda, 471w, aligned residue 86 (arm R6). ***
 *     R6 = in the ELSE arm write `xj = x0 + j * w;` BEFORE `q = t->f16 * d;`.
 *     It CLOSES the mult/mult1 pipe swap at 0x004F5D34-0x004F5D48 (3 words -> 1; the survivor
 *     differs only by the s4/s5 swap).  Land it with any future length fix.
 *     build/fg37/arms/f5710/R6.c ; C_R6_S1 is the same object (28c3ee5a8bda), C_R6_R2 87, C_R6_R1 88.
 *
 * BYTE-IDENTICAL TO THE BASELINE (md5 ab3f8a453176) -- MEASURED NULLS, do not re-sweep:
 *   ADDRESS/SUBSCRIPT: `dg = &digits[j]; d = *dg;` with `s32 *dg` declared FIRST-among-scalars (P1a)
 *     AND declared as the very first local of the function (P1b) -- the s36 "declared FIRST" twist is
 *     INERT here, the fz23f "declared last" null is now widened to BOTH ends;  `d = *(j + digits);` (P2);
 *     a TRUE 2D array `s32 digits[10][1]` with `d = digits[j][0]` and all five stores rewritten (L8).
 *   FRAME/AGGREGATE: `struct { s32 d[10]; s32 pad[2]; } dg;` replacing `s32 digits[10]` (ST1) and
 *     `struct { s32 c[4]; s32 d[10]; s32 pad[2]; } bf;` replacing BOTH arrays (ST2).  Both reproduce
 *     the frame EXACTLY (digits 0xC0, col 0xB0) and are byte-identical -- [[mwcc-member-address-no-cse]]
 *     is INERT on a stack array here.
 *   SECOND TEXTUAL REFERENCE, new regions: `q = t->f16 * digits[j];` in the else arm (Y4);
 *     `if (digits[j] == -0xFF)` as the second guard (Y5).  (fz23k had only tested the -1 test.)
 *   DECL ORDER: `void *g;` declared FIRST, i.e. above `void *h;` (S1);  `nd` moved to the head of
 *     the s32 group, before `x` (S2);  `void *g;` moved down to sit immediately above `nd` (S4);
 *     a separate render counter `jj` declared first among the s32s, used for the whole render loop
 *     including both `x0 + jj*w` (R4) -- coalesced with `j`.
 *   PRAGMAS, screened at LINE 1 with the screen ARMED (see the arming note): `optimization_level 3`,
 *     `opt_strength_reduction off`, `opt_dead_assignments off`, `optimize_for_size on`,
 *     `opt_partial_redundancy off`, `opt_unroll_loops off`, `opt_vectorize_loops off`,
 *     and the negative control `zzz_not_a_pragma on`.
 *
 * LIVE OBJECTS, all still 471 words unless noted (md5 / aligned residue):
 *   R6   28c3ee5a8bda / 86   xj before q in the else arm  <== BEST, banked
 *   C_R6_R2 2cca81a8399f / 87 ; C_R6_R1 4dd0005e33e8 / 88
 *   R1   28d6cdb34096 / 91   `b = 0; a = 0;` instead of `a = 0; b = 0;`
 *   R2   e2c8e7501815 / 90   declaration order of `a` and `b` swapped
 *   R3   e3515a1e5df4 / 92   `void *g;` declared LAST
 *   S3   1fde4207ee90 / 104  `nd` declared LAST
 *   Y1 == Y2  971671a11ed9 / 98   `dg = &digits[j]` with a SECOND use of the element through the
 *         pointer (`q = t->f16 * dg[0]`, and `if (*dg == -0xFF)`) -- ONE object, does NOT split the
 *         address, and 9 words worse.
 *   V1 == L9  9f36041444fc / 474 words (0x768, +3)   `*(volatile s32 *)&digits[j]`  and
 *         `((s32 (*)[1])digits)[j][0]`  -- the known fz23k +3 group.  ⚠ DISASSEMBLED: the fold is
 *         STILL PRESENT (`lw $5,0xC0($3)`); the +3 is entirely extra `lh` reloads of t->f10.
 *   Y6   95adb58cee9f / 481 words   `dg` live ACROSS the colour calls in the else arm.
 *   R5   be3c83dc8362 / 472 words, bad 208   `started = 1;` -- ⚠⚠ THE RIGHT LENGTH BUT A FALSE
 *         POSITIVE: the +1 is fy07's hoisted constant near 0x004F58B4, which displaces ~170 words
 *         and then the missing 0x004F5B70 word puts it back.  Do not chase this.
 *   Knobs, all far worse: opt_common_subs off 491w fdcca2a1b3ab; opt_lifetimes off 471w 3b29e2fd057c
 *         residue 286; opt_loop_invariants off 468w 523586846a2a; opt_propagation off 475w
 *         45bb941787a4; optimization_level 0/1/2 = 746/559/536w (ae6dc42d3f38 / d78b292b0eb6 /
 *         95135d05fe51); peephole off 542w 7607e0441f89; schedule off 532w 4fa22ac8f9cd;
 *         no_branch_likely on 477w 3f5ea796f1c6.
 *
 * ⚠⚠ THE LENGTH WORD IS A PROJECT-WIDE CLASS.  A census of EVERY overlay retail listing
 * (build/fg37/arms/f5710/findpat2.py, log build/fg37/logs/5710_census.txt) finds 48 FOLDED indexed
 * $sp loads, 14 SPLIT ones, 6 folded indexed stores and 0 split stores.  The 14 split sites are in
 * factory_FactoryMarkerDrawNumber_4f5710 (mine), insmenu_InsectVsSaveScreenClose_4f7990/004f7dd0/004f8ef0 and normal_FieldHudRadarDrawArrow_4f2ff0 /
 * 00501a70 / 00511150 (2) / 005135f0 (5) / 005174d0 -- and NOT ONE is in a byte-identical unit, so
 * the project has no worked example of the shape.  src/overlays/insmenu/insmenu_InsectVsSaveScreenOpen_4f8ef0.c's
 * header records the SAME defect as a 23-spelling bounded negative over 2,512 B of insmenu, names
 * the only known producer (the element ADDRESS live at TWO uses with a call, `q = &a[i]; g(*q);
 * g2(q);` -- unreachable here, the address dies at the load) and ends "Do not sweep this further
 * without a different compiler build."  With my 12 spellings the class is ~35 deep.  TREAT THIS AS A
 * TOOLCHAIN QUESTION (mwcc build / flags), not a source question, and note that 1,888 B of factory
 * plus 2,512 B of insmenu ride on the same one word.
 *
 * ⚠ HARNESS TRAP, cost 10 cells: `S.index("#pragma divbyzerocheck on")` matches the copy INSIDE THIS
 * HEADER COMMENT (the fz23f prose, ~line 7), not the real directive.  Ten knob arms were spliced into
 * a comment and read as a clean 10-arm null.  Put pragmas on LINE 1 and ARM the knob screen -- the
 * arming control is `optimization_level 0/1/2` (746/559/536 words here) plus `zzz_not_a_pragma on`
 * (must be byte-identical).
 *
 * STILL OPEN after this session, in priority order: (1) the 0x004F5B70 word -- toolchain, not source;
 * (2) the s4/s5 callee-saved pair swap, ~40 of the 86 residue words, which is now an 8-cell null on
 * declaration position and needs a WEB SPLIT on `g` or on the render-loop `j` instead;
 * (3) the a/b + $v0/$v1 permutation across 0x004F5A34-0x004F5B58, ~30 words, untouched;
 * (4) `started = 1` in place without fy07's hoist, 1 word;
 * (5) 0x004F5D28 `addu $5,$2,$22` operand order in the -0xFF arm only, 1 word.
 ==================================================================== */

#include "types.h"

/* factory.bin overlay, 0x004F5710 -- 1888 B / 472 words.  Render one table-
 * driven decimal number as a strip of digit sprites.
 *
 * DIVIDE-TRAP UNIT: three `bnez / break 0,7` pairs (`x / m`, `m / 10` and
 * `cnt / nd`); `#pragma divbyzerocheck on` is the key ([[NEGATIVES 6.6]]).
 * The `/ 2` and `% 2` sites are shifts and carry no check.
 *
 * TEMPLATE: src/overlays/factory/factory_FactoryMarkerDrawItemIcon_4f5490.c and
 * factory_FactoryMarkerDrawBase_4f5e70.c -- identical context/projection preamble
 * (`func_15DE80` / `func_159FB0(.., D_0050CBF8, -1)` / `func_15D340` /
 * `p.x - 0x260`, `p.y - 0x640`) and the same twelve-call render setup.
 *
 * * `ld 0x8($16)` + `dsll32/dsra32 ..,0` is an s64 table member and an
 *   explicit s32 copy of it; the `!= 0` tests are on the full 64 bits.
 * * `col[3] > 0.0f` compares an s32 array element against a float literal --
 *   `cvt.s.w` then `c.le.s` is the promotion, not a float array.
 * * `mult` + `mult1` are `j * w` and `t->f16 * d` scheduled into the two EE
 *   multiply pipes; the second must be NAMED because it stays live across the
 *   colour calls.
 * * D_0050BB20/D_0050CBF8 are overlay data outside the gp window, so both are
 *   incomplete arrays taking %hi/%lo.
 */

/* ==== LANE fz23g, 2026-08-31, round 3.  STILL 471 words / ONE WORD SHORT.
 * State on disk is fz23f's exact 471-word baseline (`d = digits[j];`),
 * RE-CONFIRMED before any edit by scoring build/obj-fz23f offline:
 * `472 words, len 0x75c vs 0x760`.
 *
 * THREE MEASURED ARMS ON THE 0x004F5B70 FOLD, ALL WORSE.  Do not re-sweep:
 *   1. `d = *(s32 *)((s32)digits + j * 4);`        -> 475 words (0x76c), +4.
 *      The named-open [[insect-pool-argument-integer-add]] cell.  It DOES block
 *      the displacement fold, but `(s32)digits` is LOOP-INVARIANT: mwcc hoists
 *      the base out of the render loop into a NINTH callee-saved register, so
 *      the +1 for the split address is paid three more times in sq/lq/daddu.
 *      -- so the integer-add cast is NOT the blocker here; the invariant base is.
 *   2. `d = *(s32 *)((s32)&col[j] + 0x10);`        -> 440 words (0x6e0), -31.
 *      The `second base` idea (col ends at $sp+0xBC so &col[4] IS digits) is
 *      ⚠⚠ ACTIVELY DANGEROUS: with no syntactic reference to `digits` left,
 *      mwcc DEAD-STORE-ELIMINATES the entire digit-extraction loop (31 words).
 *      Any second-base spelling must still mention `digits` somewhere.
 *   3. `d = *(s32 *)((s32)&digits[j - 1] + 4);`    -> 476 words (0x770), +5.
 *      Chosen because it is fully loop-VARIANT (nothing to hoist) and, if mwcc
 *      folded 0xBC+4, would give retail's exact `addu`-then-`addiu` order.
 *      It does neither: the `j - 1` is not strength-reduced into the frame
 *      displacement and a base is still hoisted.
 *
 * ⇒ READING.  mwcc's own lowering of `digits[j]` already emits retail's first
 * word (`addu $3,$3,$29`) and keeps 0xC0 as the LOAD DISPLACEMENT.  Every
 * spelling that blocks that fold does so by introducing a base subexpression
 * mwcc then treats as loop-invariant and promotes.  The next arm must block the
 * fold with something the loop CANNOT hoist and that still names `digits` --
 * e.g. an addend that is a loop-carried variable known to be zero, or reaching
 * the element through a pointer that is genuinely re-derived per iteration.
 * The three cheap cast spellings are now spent.
 * ========================================================================= */

/* ==== LANE fz23k, 2026-08-31.  STILL 471 words / ONE WORD SHORT (baseline
 * RE-CONFIRMED offline against build/obj-fz23v5: `len 0x75c vs 0x760`), but the
 * ROUND-3 MECHANISM ABOVE IS **OVERTURNED** and the search space is smaller.
 * Twenty-one further cells measured, none of them 472.
 *
 * OVERTURNED: `(s32)digits + j*4` -> 475 IS NOT A HOISTED LOOP-INVARIANT BASE.
 * Disassembling that variant's object and diffing it against retail shows
 * `addiu $3,$3,0xC0` is STILL MISSING at 0x004F5B70 -- the fold happened anyway
 * -- and the +4 is ENTIRELY three or four extra `lh $7,0x10($16)` RELOADS of
 * `t->f10` in the loops at 0x004F5858-0x004F58A4.  Taking the address of
 * `digits` makes mwcc's alias analysis reload the loop bound after every store
 * into the array.  So NO ADDRESS SPELLING TESTED BLOCKS THE FOLD; they only
 * cost aliasing.  The recorded `next arm must block the fold with something the
 * loop cannot hoist` aims at a mechanism that does not exist.
 *
 * ONE OBJECT (0x768, +3), all seven of these -- the whole `block the fold`
 * family collapses to a single cell:
 *     *(s32 *)((u8 *)digits + j * 4)      *(s32 *)((u8 *)digits + (j << 2))
 *     *(s32 *)((u8 *)&digits[0] + j * 4)  *(s32 *)((s8 *)digits + j * 4)
 *     *(s32 *)&((u8 *)digits)[j * 4]      *(volatile s32 *)&digits[j]
 *     ((volatile s32 *)digits)[j]
 * `*(s32 *)((s32)digits + j * 4)` is a DISTINCT object (0x76c, +4), so
 * [[insect-pool-argument-integer-add]]'s `(s32)ptr` vs `(u8 *)ptr` split is
 * RE-CONFIRMED here -- it just does not buy the word.
 *
 * BYTE-IDENTICAL TO THE BASELINE (measured null, do not re-sweep):
 *   `*(digits + j)`; `digits[(u32)j]`; two AND three textual references to
 *   `digits[j]` in the loop (the `mwcc will CSE the ADDRESS if the element is
 *   named twice` hypothesis is REFUTED); `volatile s32 digits[10]` as the
 *   DECLARATION; `s32 digits[10] __attribute__((aligned(16)))`; and -- the
 *   important one -- the 004f5e70 lever, HOISTING THE `for` INIT OUT OF THE
 *   HEADER, IS A MEASURED NULL ON THIS UNIT: `j = 0;` given its own statement
 *   ahead of `top = y0 + hgt - 0x10;` (the exact edit that closed 004f5e70),
 *   the same for the `col[j]` loop, and a SEPARATE render counter `i` cleared
 *   ahead of `top`, are all byte-identical.
 * `digits[(s64)j]` is +2 (0x764).
 *
 * RETAIL FOLDS 0xC0 AT EVERY OTHER SITE IN THIS SAME FUNCTION --
 * `sw $8,0xC0($7)` at 0x004F5838, 0x004F5874 and 0x004F58FC and
 * `sw $0,0xC0($29)` at 0x004F5898.  So the un-folded `addiu` at 0x004F5B70 is
 * SITE-SPECIFIC, not a property of the array or of the frame, and is very
 * probably a SCHEDULING artefact rather than anything the address expression
 * can reach.  Attack it from the SCHEDULE, not from the subscript.
 *
 * CARRY FORWARD once the length is fixed: `xj = x0 + j * w;` written BEFORE
 * `q = t->f16 * d;` in the else-arm is a LIVE object at the same length
 * (cc14225e) and is the [[normal-named-product-local]] axis for residue (b),
 * the `mult`/`mult1` pipe swap at 0x004F5D34.
 * The three `trunc.w.s` at 0x004F5C24/0x004F5C28/0x004F5C3C are GENUINELY
 * different instructions from retail's `cvt.w.s` (funct 0x0D vs 0x24), not a
 * listing artefact.  Naming the three conversions in their own locals is
 * byte-identical; `col[x] * (1.0f / 1.5f)` reaches a `.lit4` reciprocal and is
 * THREE WORDS SHORT.  Unresolved.
 *
 * GUARD STRUCTURE swept too (the brief calls guard polarity a LENGTH lever with
 * no default) -- all BYTE-IDENTICAL to the baseline, do not re-sweep:
 *   `if (d == -1) { continue; } else if (d == -0xFF)`; the `continue` rewritten
 *   as a nested `if (d != -1) { ... }` around the whole body; `t->f10 > j` as
 *   the loop compare; and both together.  `if (d != -0xFF)` with the arms
 *   swapped and `if (d + 0xFF == 0)` are LIVE objects at the SAME length.
 *   `top = y0 + hgt; top = top - 0x10;` split into two statements is 0x758,
 *   one word SHORTER -- the wrong direction, but it proves the pre-loop
 *   statement schedule does reach this function's length.
 * ========================================================================= */

/* ==== RE-PARKED by lane fz23f, 2026-08-31.  471/472 words -- ONE WORD SHORT,
 * and the missing word is LOCATED EXACTLY.  Read this before the fy07 note.
 *
 * fy07's 472/472 + 189-wrong baseline was REPRODUCED from this file (round 1,
 * tag fz23f) -- but only after repairing the file, which DID NOT COMPILE: the
 * fy07 park block had been pasted INSIDE the header comment, so its closing
 * a close-comment token ended the comment early and the tail of the original comment was left
 * at file scope.  Nobody had ever compiled 004f5710 from this path.
 *
 * THE ADVANCE.  fy07 measured `started += 1` alone as "one word SHORT" and
 * rejected it, and separately recorded residue item (2) as "one word FEWER".
 * THOSE TWO WERE NEVER COMBINED.  They are the same word.  With
 *     started += 1;            (no `started = 0;` in front of it)
 * the HOIST and the compound-assign's extra `daddu $x,$0,$0` BOTH disappear:
 * the ~94-word displacement that made up half of the 189 is GONE, ours and
 * retail align 1:1 from word 0 all the way to 0x004F5B6C, and the residue
 * under best alignment falls 189 -> 95.  PRECISION: the 471 LENGTH was measured
 * on exactly the source now on disk (round trip 2); the 95-word alignment count
 * was read off round trip 3's object, which differs from it only by the
 * measured-inert `dg` cell below and is the same 471 words.
 *
 * THE WHOLE REMAINING LENGTH GAP IS ONE INSTRUCTION AT 0x004F5B70:
 *     retail  addu  $3, $3, $29      ours  addu  $3, $3, $29
 *             addiu $3, $3, 0xC0           lw    $5, 0xC0($3)
 *             lw    $5, 0x0($3)
 * `digits` is the stack array at $sp+0xC0 and `$3` is `j << 2` arriving from
 * the loop-bottom delay slot.  mwcc FOLDS 0xC0 into the `lw` displacement;
 * retail materialises the address first.  Everything from 0x004F5B70 to the
 * end is retail displaced by one word BECAUSE OF THIS SINGLE INSTRUCTION --
 * fix it and the length is 472 and the unit is scoreable again.
 *
 * MEASURED INERT for that word, this session (do not re-sweep):
 *   `dg = &digits[j]; d = *dg;` with `s32 *dg` declared last.  Naming the
 *   address does NOT stop the fold -- mwcc forward-substitutes the pointer
 *   and still emits `lw $5, 0xC0($3)`.  Length stayed 471.
 * UNTRIED and still open for that word: the [[insect-pool-argument-integer-add]]
 *   distinction `(s32)digits + j*4` vs `(u8 *)digits + j*4` (they are NOT the
 *   same object), and reaching the array through a second, differently-spelled
 *   base ([[insect-cse-two-spellings]]) -- note `col` ends at $sp+0xBC so
 *   `&col[4]` IS `digits`.
 *
 * WHAT IS LEFT AFTER THAT WORD (95 words, all already visible in the 471
 * alignment, none of it length):
 *  (a) the callee-saved pair swap: ours $s4 where retail has $s5 (`addiu
 *      $s4,$s4,1` vs `addiu $s5,$s5,1`, `move $s4,$zero` vs `move $s5,$zero`,
 *      and ~16 `daddu $4,$s4,$0`).  fy07 measured decl-order INERT here.
 *  (b) the EE multiply pipes: ours `mult $ac2,$s1,$v0` where retail has
 *      `mult $ac3,$s1,$v1`, plus a $v0/$v1 and $a1/$a2 shuffle across
 *      0x004F5B44-0x004F5B5C.  [[normal-named-product-local]] is STILL the
 *      untried axis.
 *  (c) every remaining `beql`/`b`/`bnel` target, which differs by exactly 4
 *      and is pure consequence of the one missing word.
 *
 * TO GET BACK TO fy07's MEASURED, SCOREABLE 472/189 STATE: put `started = 0;`
 * back in front of `started += 1;` in the digit loop.  That is the only edit
 * between the two states.
 * ========================================================================= */

/* ==== PARKED by lane fy07, 2026-08-27.  472/472 words, 189 wrong. ==========
 * Best of 39 measured spellings (build/fy07_run{,2,3}.py, one ssh round trip
 * each; baseline reproduced 208 every time -- that is the arming proof).
 *   208  as-drafted (`if (d > 0 || started != 0) {...} else if (neg==0)`)
 *   206  + the INVERTED `&&` shape below      <- fixes the branch POLARITY
 *   195  + `started = 0; started += 1;`       <- kills a HOISTED constant
 *   189  + original declaration order         <- FLOOR, and it is flat
 *
 * WHAT THE INVERSION BOUGHT (re-usable).  Retail is
 *     bgtzl d -> ARM ; bnez started -> ARM' ; if (neg==0) dp++ ; ARM: ...
 * i.e. BOTH tests branch INTO the arm and the ELSE-part is the FALL-THROUGH.
 * `if (A || B) X else Y` gives mwcc's other layout (`if(A) goto X; if(!B) goto
 * Y; X:`).  Spelling it as `if (!A && !B) Y else X` reproduces retail exactly,
 * delay slot and all (the duplicated `sll $7,dp,2` at .L004F58EC is the tell).
 *
 * WHAT THE COMPOUND ASSIGN BOUGHT.  As `started = 1;` mwcc promotes the
 * literal to a register OUTSIDE the loop -- an extra `addiu $9,$0,1` at
 * 0x004F58B4 and `daddu $started,$9,$0` in the body where retail has a plain
 * `addiu $11,$0,1`.  That ONE extra instruction shifts every word from
 * 0x004F58B4 to 0x004F5B74 by four bytes and costs ~180 of the 208.  The
 * [[insect-compound-assign-blocks-fold]] spelling blocks the promotion (d and
 * j then land on retail's $9/$10) but costs its own word: it emits
 * `daddu $x,$0,$0 / addiu $x,$x,1` where retail has ONE `addiu $x,$0,1`.
 * A one-instruction, non-hoisted `started = 1` is the whole remaining gap and
 * NO spelling found it.
 *
 * RESIDUE, in instruction terms (189 words):
 *  (1) ~170 words: the +1 word shift 0x004F58F0-0x004F5B74 caused by the extra
 *      `daddu $started,$0,$0` above.  Everything in that span is retail's
 *      stream displaced by one word, not different code.
 *  (2) 0x004F5B70/74: retail splits the address, `addiu $3,$3,0xC0` then
 *      `lw $5,0x0($3)`; we fold it to `lw $5,0xC0($3)` after `addu $3,$3,$29`.
 *      One word FEWER -- this is what keeps the total at 472.
 *  (3) the render loop swaps two CALLEE-SAVED regs: ours j=$20/g=$21, retail
 *      j=$21/g=$20 (~16 words of `daddu $4,$21,$0` vs `daddu $4,$20,$0`,
 *      plus `addiu $21,$21,1` and `slt $2,$21,$4`).  NOT decl-order: `i` as a
 *      separate counter at three positions and `g` moved twice all produced a
 *      BYTE-IDENTICAL object (sha1 a5759299) -- [[mwcc-decl-order-tiebreak]]
 *      is INERT here, presumably because j is not passed verbatim as an arg.
 *  (4) 0x004F5CD0-0x004F5D48: the two EE multiply pipes are assigned the other
 *      way round and one `addu` has its operands transposed --
 *        ours 0x5D34 `mult1 $2,$20,$17`   retail `mult  $4,$21,$17`
 *        ours 0x5D3C `addu  $22,$19,$2`   retail `mult1 $23,$2,$5`
 *        ours 0x5D28 `addu  $5,$22,$2`    retail `addu  $5,$2,$22`
 *      i.e. `t->f16 * d` and `j * w` are issued to the opposite pipes.
 *      [[normal-named-product-local]] (name the product) is the axis to try
 *      next and was NOT reached in this lane.
 *
 * SPELLINGS MEASURED AND REJECTED (all 39 live objects, none below 189):
 *   || form: plain `started`, `!started`, `d < 1`, `x = x - d*m`, `x -= m*d`,
 *     `digits[dp++] = d`, nd++ before dp++, `started = 1` last in the body.
 *   started type: u8 / s8 / s16 all change the FRAME SIZE (0x764/0x768 vs
 *     0x760) and are dead; u32 is byte-identical to s32.
 *   `register s32 started` is byte-identical to plain s32 (mwcc ignores it).
 *   `started += 1` alone (relying on the pre-loop 0) is one word SHORT.
 *   declaration position of started (5 positions), of g (3), of nd (2) and a
 *     separate render counter i (3 positions): all inert or worse.
 * NOT TRIED: naming the two float/integer products (lever 4 above), and any
 *   pragma other than divbyzerocheck (the knob axis is called spent).
 *
 * The `#pragma divbyzerocheck on` below IS load-bearing and is NOT part of the
 * residue.  NOT MEASURED on this unit (it never reached a matching state, so a
 * pragma-off length would not have been diagnostic); the armed screen counts
 * THREE `bnez/break 0,7` sites here, and the pragma-off arm was measured
 * exactly on the lane's other three units -- see the fy07 lane report.
 * ========================================================================= */

#pragma divbyzerocheck on

typedef struct Cell {
    f32 f00;
    f32 f04;
    f32 f08;
    u8  pad0C[0x2];
    u8  f0E;
    u8  f0F;
    u8  pad10[0x4];
} Cell;                                         /* 0x14 */

typedef struct Panel {
    u8    pad00[0x78];
    Cell *f78;
} Panel;

typedef struct Num {
    s16 f00;
    s16 f02;
    u8  pad04[0x4];
    s64 f08;
    s16 f10;
    s16 f12;
    s16 f14;
    s16 f16;
    s16 f18;
    s16 f1A;
    s16 f1C;
    s16 f1E;
    u8  pad20[0x20];
} Num;                                          /* 0x40 */

typedef struct Vec { f32 x; f32 y; f32 z; f32 w; } Vec;
typedef struct Pos { s32 x; s32 y; s32 z; s32 w; } Pos;
typedef struct Ref { s16 f00; } Ref;

extern u8   D_0050CBF8[];
extern Num  D_0050BB20[];

extern void *func_15DE80(void);
extern void *func_15DE40(void);
extern Ref  *func_159FB0(void *ctx, void *name, s32 k);
extern void  func_1418C0(void *ctx, s16 k, f32 v);
extern s32   func_15D340(Pos *out, Vec *v);
extern void *func_141B00(void *h);
extern void  func_141A20(void *h);
extern void  func_13E500(void *g, s32 a);
extern void  func_13E4F0(void *g, s32 a);
extern void  func_13E4D0(void *g, s32 a);
extern void  func_13E4C0(void *g, s32 a, s32 b);
extern void  func_13E430(void *g, s32 a);
extern void  func_13E3D0(void *g, s32 a);
extern void  func_13E400(void *g, s32 a);
extern void  func_13E460(void *g, s32 a);
extern void  func_13E2F0(void *g, s32 a);
extern void  func_13F730(void *g, s32 a);
extern void  func_13EC00(void *g, void *p);
extern void  func_13EE40(void *g, s32 a, s32 b, s32 c, s32 d);
extern void  func_13ED60(void *g, s32 a, s32 b);
extern void  func_13EF10(void *g, s32 a, s32 b, s32 c);
extern void  func_13F5B0(void *g);

void factory_FactoryMarkerDrawNumber_4f5710(Panel *o, s32 idx)
{
    s32   bx;
    Pos   p;
    Vec   v;
    s32   digits[10];
    s32   col[4];
    void *h;
    Ref  *r;
    Cell *e;
    Num  *t;
    s64   val;
    s32   x;
    s32   m;
    s32   d;
    s32   j;
    s32   dp;
    s32   nd;
    void *g;
    s32   started;
    s32   neg;
    s32   b;
    s32   a;
    s32   x0;
    s32   y0;
    s32   w;
    s32   hgt;
    s32   top;
    s32   xj;
    s32   q;
    s16   n10;

    h = func_15DE80();
    r = func_159FB0(func_15DE40(), D_0050CBF8, -1);
    if (r != 0) {
        func_1418C0(func_15DE80(), r->f00, 1.0f);
    }
    e = &o->f78[idx];
    if (e->f0E == 0) {
        return;
    }
    if (e->f0F == 0) {
        return;
    }
    v.x = e->f00;
    v.y = e->f04;
    v.z = e->f08;
    v.w = 1.0f;
    t = &D_0050BB20[idx];
    val = t->f08;
    x = (s32)val;
    n10 = t->f10;
    m = 1;
    for (j = 0; j < n10 - 1; j++) {
        m = m * 10;
    }
    for (j = 0; j < 10; j++) {
        digits[j] = -1;
    }
    neg = (t->f1A & 1) != 0;
    if ((t->f1A & 0x14) != 0) {
        for (j = 0; j < n10; j++) {
            digits[j] = -0xFF;
        }
    }
    if (val == 0) {
        if (neg != 0) {
            digits[0] = 0;
        } else {
            digits[n10 - 1] = 0;
        }
    }
    dp = 0;
    nd = 0;
    started = 0;
    for (j = 0; j < n10; j++) {
        d = x / m;
        if (d <= 0 && started == 0) {
            if (neg == 0) {
                dp++;
            }
        } else {
            started = 1;
            digits[dp] = d;
            dp++;
            nd++;
            x -= d * m;
        }
        m = m / 10;
    }
    if (val == 0) {
        nd++;
    }
    if (nd == 0) {
        return;
    }
    if (func_15D340(&p, &v) == 0) {
        return;
    }
    p.x = p.x - 0x260;
    p.y = p.y - 0x640;
    g = func_141B00(h);
    func_13E500(g, 1);
    func_13E4F0(g, 1);
    func_13E4D0(g, 1);
    func_13E4C0(g, 5, 0);
    func_13E430(g, 1);
    func_13E3D0(g, 1);
    func_13E400(g, 1);
    func_13E460(g, 0);
    func_13E2F0(g, 1);
    func_13F730(g, 6);
    func_13EC00(g, r);
    func_13EE40(g, 0x80, 0x80, 0x80, 0x80);
    func_13F730(g, 6);
    func_13EC00(g, r);
    x0 = p.x + t->f00 * 16;
    bx = x0;
    y0 = p.y + t->f02 * 16;
    for (j = 0; j < 4; j++) {
        col[j] = 0x80;
    }
    hgt = t->f18 * 16;
    w = t->f16 * 16;
    if ((t->f1A & 2) != 0) {
        w = t->f1C * 16;
        hgt = t->f1E * 16;
    }
    if (neg == 0) {
        x0 -= w * t->f10;
    }
    if ((t->f1A & 8) != 0 && (t->f1A & 0x14) == 0) {
        x0 = bx;
        if (nd != t->f10) {
            b = 0;
            a = 0;
            if (nd > 1) {
                a = t->f10 / nd - 1;
            } else if (t->f10 % 2 == 0) {
                b = t->f10 / 2 - 1;
            } else {
                b = t->f10 / 2;
            }
            x0 -= w * (b + a);
        }
    }
    top = y0 + hgt - 0x10;
    for (j = 0; j < t->f10; j++) {
        d = *(s32 *)(s32)&digits[j];
        if (d == -1) {
            continue;
        }
        if (d == -0xFF) {
            if ((t->f1A & 0x10) != 0) {
                if ((t->f1A & 0x40) != 0 && col[3] > 0.0f) {
                    col[3] = 0x26;
                }
                if ((t->f1A & 0x20) != 0) {
                    func_13EE40(g, 0x55, 0x55, 0x55, col[3]);
                } else {
                    func_13EE40(g, (s32)(col[0] / 1.5f), (s32)(col[1] / 1.5f),
                                (s32)(col[2] / 1.5f), col[3]);
                }
            } else {
                if ((t->f1A & 0x40) != 0 && col[3] > 0.0f) {
                    col[3] = 0x26;
                }
                if ((t->f1A & 0x20) != 0) {
                    func_13EE40(g, 0x80, 0x80, 0x80, col[3]);
                } else {
                    func_13EE40(g, col[0], col[1], col[2], col[3]);
                }
            }
            func_13ED60(g, t->f12, t->f14);
            func_13EF10(g, x0 + j * w, y0, 0);
            func_13ED60(g, t->f12 + t->f16, t->f14 + t->f18);
            func_13EF10(g, (t->f16 - 1) * 16 + (x0 + j * w), top, 0);
        } else {
            xj = x0 + j * w;
            q = t->f16 * d;
            if ((t->f1A & 0x40) != 0 && col[3] > 0.0f) {
                col[3] = 0x26;
            }
            if ((t->f1A & 0x20) != 0) {
                func_13EE40(g, 0x80, 0x80, 0x80, col[3]);
            } else {
                func_13EE40(g, col[0], col[1], col[2], col[3]);
            }
            func_13ED60(g, t->f12 + q, t->f14);
            func_13EF10(g, xj, y0, 0);
            func_13ED60(g, t->f16 + (t->f12 + q), t->f14 + t->f18);
            func_13EF10(g, xj + (t->f16 - 1) * 16, top, 0);
        }
    }
    func_13F5B0(g);
    func_141A20(h);
}
