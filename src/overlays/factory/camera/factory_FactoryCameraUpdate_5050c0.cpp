#include "types.h"

/* ====================================================================
 * SESSION 52 (2026-09-03), tag fg52.  CLOSED: 13 bad -> BYTE-IDENTICAL,
 * 650 w, md5 a5b66bf7b9d3 (arms A1_const_sdata_attr = A2_const_sbss_attr,
 * one object; rebuilt from this tree file with the arming pair 005069e0 =
 * MATCH / 1a0e9c68216b and 00500450 = 2 / 409c28db0188 and the recorded
 * delivery cell N7 = 67 / 4fcc0bc6f0bd live in every batch).
 *
 * THE EDIT (two lines, one lever -- the STORE TARGET'S ALIAS CLASS):
 *
 *     extern const f32 D_004808A0 __attribute__((section(".sdata")));
 *     ...
 *     *(f32 *)&D_004808A0 = arg0->f380.v.x;
 *
 * Both s47 sub-residues -- the final gp store sunk below all 17 restores AND
 * the GPR-first, s2/s0/s1 restore interleave -- closed together.  Neither is
 * a separate decision: mwcc's exit-block list scheduler pairs `ld ra` with
 * the value LOAD once the store is free to move, and the pairs then run
 * (s2,f31) (s0,f30) (s1,f29) with `lq s1` held two slots by its WAR on the
 * load's base.  While the store is alias-pinned above the restores (a store
 * to a plain gp global may alias the stack loads), `ld ra` pairs with f31
 * instead and the canonical FPR-first order follows.  s47's "moving the
 * store alone leaves 6 bad" arithmetic assumed the interleave was fixed; it
 * is a by-product of the same schedule.
 *
 * HOW IT WAS FOUND -- a corpus screen over all 11,576 matched units (the
 * five overlays AND main; s47's screen was overlays only), armed on this
 * unit's retail epilogue (build/fg52/s52/episcreen.py, leadrule*.py):
 *   - GPR-first is NOT unique: 65 units, 10 of them with nothing but restores
 *     in the exit block, every one of those with `daddu v0,sN,zero` (return a
 *     callee-saved) as the block's only computation.
 *   - the ONLY matched precedent for a store sunk below a restore is MAIN's
 *     12-unit StaticInitInitialStatus_46e290 family, whose sunk store is `*(s32 *)&CONST = t`
 *     -- a store through a cast of a `const` object -- while the SAME family's
 *     stalled stores to plain gp globals (StaticInitTextEntryResMaybe_46f910, StaticInitInsectMenu_46de40) stay
 *     above `ld ra`.  18 matched units end with a stalled gp store; none is
 *     sunk.  => the alias class of a const object is "modifies nothing".
 *   - `extern const f32` alone is addressed absolutely (lui, 651 w, store
 *     sunk, interleave unchanged: C1/C3/C5/C7/A3 = 60c77324fb85); the section
 *     attribute keeps it in small data and gives the whole retail tail.
 * INERT at this baseline (build/fg52/logs/s52_b{1,2}.log): the `*(f32 *)&`
 * cast on the non-const target (C6), volatile on the target, the value,
 * both, or the declaration (V1-V4), a `__restrict` cast (R2), a one-float
 * struct copy (S1) -- all 334b9da5b0b6; a `__restrict` pointer local (R1)
 * = 653 w / bd4f21781cdf (a GPR local shifts s0..s2 to s1..s3).
 *
 * The retail object at 0x4808A0 is writable small data, so retail's source
 * did not literally say `const`; the const declaration is this TU's way of
 * telling mwcc the store cannot alias the stack.  Whatever retail wrote,
 * the bytes are the bytes.
 ==================================================================== */

/* ====================================================================
 * SESSION 47 (2026-09-03), tag fg47.  DRAFT: 15 -> 13 bad at EXACT LENGTH
 * (650 w), md5 9e43c8853654 -> 334b9da5b0b6, census exact, all 26 mapped
 * FPR webs on retail's register (build/fg47/logs/s47_n1_fmap.log).  NOT in
 * factory.txt; board unchanged at 400/409.  Arming pair held in every run:
 * 005069e0 = MATCH / 1a0e9c68216b, 00509f10 = bad 11 / 977182cbe9b7.
 *
 * WHAT LANDED (one edit, predicted by the s46 allocator model before it was
 * built): the inner 0.5f guard is now retail's ONE shared assignment after
 * the nested ifs (`if (a<.5f) { if (b<.5f) { S } } var_f27 = D_0047D8D4;`,
 * FIX 3 of [[mwcc-branch-likely-duplication]]), AND the five top callee-saved
 * webs var_f31 var_f30 temp_f29 temp_f28 var_f27 are declared as a GROUP
 * AHEAD of the sp* stack locals, in that order.  s46 had shown that form is
 * census-exact only with var_f27 before sp8C and then rotates the top five
 * (v27 removed first -> $f31).  Under the model the fix is to make v27 the
 * FIFTH removal while still ahead of sp88: N1 (group before sp9C), N2 (before
 * sp8C) and N3 (top four before sp9C, v27 before sp8C) are ONE object at 13;
 * N5 (v31 alone ahead, v27 before sp8C) = 58 = the staircase; N6 (group before
 * sp88) = 653 w = the s46 spill; N7 (v27 then v31 ahead) = 67 = s46's object.
 *
 * RESIDUE (13 bad, 650 w) = THE EPILOGUE ONLY (blocks: 5 regions, 0 cells):
 * retail `lwc1 $f0,896(s1); ld ra; lq s2; lwc1 f31; lq s0; lwc1 f30; lq s1;
 * lwc1 f29..f20; swc1 $f0,D_004808A0; jr` -- the final store SUNK below every
 * restore and the restores in a NON-canonical order (GPR-first pairs, s0
 * before s1).  Ours: store right after its load, then the canonical
 * `ld ra; lwc1 f31; lq s2; lwc1 f30; lq s1; lwc1 f29; lq s0; f28..f20`.
 * PARKED AS A CLASS with this negative (every arm on the N1 base, all
 * byte-identical 334b9da5b0b6 unless noted):
 *   - store TARGET: static f32 / defined f32 / extern f32[1] / extern struct
 *     {f32 v} / another gp global (D_0047D8D4) / an object field (arg0->f484)
 *     / a byte-offset pointer store -- the store never moves (E20-E28);
 *   - store VALUE from a plain field (arg0->f3A0, E23): 14, store unmoved;
 *   - a C++ reference to the global (E24) and a static inline setter (E34);
 *   - ALL three volatile pins removed (E30, 648 w) or each alone (E31 649,
 *     E32 = byte-identical -> the temp_f28 pin is INERT at this baseline,
 *     E33 649): the epilogue residue is identical in every one;
 *   - `#pragma opt_pointer_analysis on` SEGFAULTS the compiler (rc 139 under
 *     wibo on the build host; the exe copied to this Windows box hangs after
 *     its usage warning even on a 1-line file, so it cannot be run natively);
 *     `off` is byte-identical.
 *   - CORPUS SCREEN (build/fg47/scan_epi*.py, canon.py, read-only over the
 *     2,100 matched units): 550 end with a non-stack store and NOT ONE has it
 *     below the `ra` restore; 24 have the adjacent `load; store; ld ra` shape
 *     retail keeps as-is; the only matched units with computation scheduled
 *     below the restores are insect 0050fb10 / 00510480 (an ALU return value
 *     stalled on a load or a div) -- mwcc's exit-block scheduler pushes a
 *     STALLED consumer behind every ready restore, which is exactly what
 *     retail did to this store and what ours never does for a STORE.
 *   With s46's 11 spellings + 5 pragmas this is 30+ arms; do not re-spend.
 *
 * Instruments: build/fg47/{swb47,mk47m,fmap47,fbirth,scan_epi,scan_epi2,
 * scan_epi3,canon,tail,dumpw}.py; logs build/fg47/logs/s47_*.log.
 ==================================================================== */

/* ====================================================================
 * SESSION 46 (2026-09-03), tag fg46.  DRAFT: 215 -> 15 bad at EXACT LENGTH
 * (650 w), md5 0df5af163304 -> 9e43c8853654.  NOT in factory.txt; board
 * unchanged at 400/409.  Arming pair held in every run: 005069e0 = MATCH /
 * 1a0e9c68216b, 00509f10 = bad 11 / 977182cbe9b7.  Every verdict below was
 * read on a per-web REGISTER MAP (build/fg46/fmap46.py), not the byte score.
 *
 * THE ALLOCATOR IS A MODEL NOW ([[factory-session46-levers]]): callee-saved
 * float webs are removed in ASCENDING DECLARATION ORDER in repeated passes, a
 * web is skipped while it still has >= 12 interfering callee-saved neighbours
 * (degrees update within the pass), and colours are assigned in REVERSE
 * removal order, LOWEST free register first.  Checked by hand against 26
 * webs on four objects.  s45's "uniform downshift" was temp_f20_2 sitting at
 * degree exactly 12: temp_f27b (case 11, idx 368-384) declared BEFORE it is
 * removed in the same pass and unsticks it, so it is removed early and
 * coloured LAST ($f31).  The 30-slot relocation sweep of temp_f20_2 is the
 * staircase of exactly that (build/fg46/logs/s46_sweep_fmap.log).
 *
 * WHAT LANDED, in order (each alone, then combined; logs s46_b*.log):
 *  1. Callee-saved declaration order = the 11 clique webs DESCENDING by retail
 *     register, then temp_f20_2, temp_f27b, temp_f31, temp_f28_3, var_f27_2,
 *     var_f20_2 (temp_f27b AFTER temp_f20_2 keeps it stuck; temp_f31 and
 *     temp_f28_3 after temp_f27b so they come off in the same pass as
 *     var_f27_2/var_f20_2).  121 colouring cells -> 0 (arm Z1, 649 w).
 *  2. Guard 3's D_0047D24C load pinned (`*(volatile f32 *)&D_0047D24C *
 *     temp_f4`): with the colouring right the 1.0f mtc1 nop is gone, so the
 *     pin s45 measured at +1 is now exactly 650 w.  (Z2 = 48 bad.)
 *  3. Caller-saved class, same model: var_f3 declared before var_f2 (-8);
 *     nd declared after temp_f4 (-9).
 *  4. `||` site 1 then-arm order `var_f24 = var_f20; var_f22_2 = temp_f28_2;`
 *     (-3) -- s45 read it inert at 460, where the diff was displacement-blind.
 *  5. Tail `func_13BE20(arg0->pad370, &arg0->f360, &spA0); v42(arg0->pad370)`
 *     (-4); `(u8 *)` casts on both = 652.
 *  6. `temp_f29 = arg0->f2BC;` BEFORE the two fabsf (-2): c.le.s/lwc1 order.
 *  7. Prologue `temp_f23 = ..; var_f22 = -arg0->f41C; var_f22 *= arg0->f3B0;
 *     temp_f20 = ..;` -- the ONLY one of 12 statement orders that is retail
 *     (loads f41C, f418, f3AC, f3B0; neg in place; mul f23; f20; jal; mul f22
 *     in the slot).  A two-def local `fx = f41C; fx = -fx;` collapses to the
 *     same objects as the split statements.  22 -> 15.
 *
 * RESIDUE (15 bad, 650 w):
 *  - inner 0.5f guard (2 w): retail = ONE shared `var_f27 = D_0047D8D4` after
 *    the nested ifs (three predecessors; mwcc threads only the FIRST -- the
 *    outer bc1fl -- and leaves the inner bc1f+nop).  That form is census
 *    EXACT at 650 w with var_f27 declared before sp9C (67 bad = v27/v31/v30/
 *    t29/t28 rotated by one) and SPILLS the 1.0f web (653) with var_f27 in any
 *    of the 27 callee-saved slots (one object).  The stack locals' slots are
 *    part of the ordering: var_f27 before sp9C..sp8C = the 650/67 object,
 *    before sp88 or later = the 653 spill (13-slot sweep, s46_v27s_fmap.log).
 *  - epilogue (13 w): retail sinks `swc1 $f0,D_004808A0` below every restore
 *    and interleaves `lq s2, lwc1 f31, lq s0, lwc1 f30, lq s1`; ours stores
 *    first.  11 spellings (volatile, local, casts, extern "C", return forms,
 *    f32 return type, a constant store) and 5 pragmas (optimization_level 3,
 *    peephole, opt_dead_assignments, opt_propagation, arming zzz) are all
 *    byte-identical or worse.  Same class as MAIN's parked cohort
 *    ([[main-pass33-lists]]: 488 pragmas null).  Do not re-spend spellings.
 *
 * MEASURED INERT this session (baseline md5 in the lever file): temp_f20_2
 * load spellings and merges; rider self-assign removal; volatile sp*; the
 * other 11 prologue orders; goto / empty-then guard forms; the `var_f27`
 * inside-the-inner-if form (built on a misread branch offset, probe-traps #89).
 ==================================================================== */

/* ====================================================================
 * SESSION 45 (2026-09-02), tag fg45.  DRAFT: 460 -> 215 bad at EXACT LENGTH
 * (650 w), md5 7652b8968761 -> 0df5af163304.  NOT in factory.txt; board
 * unchanged at 400/409.  Arming pair held in every run: 005069e0 = MATCH /
 * 1a0e9c68216b, 00509f10 = bad 11 / 977182cbe9b7.  Scored by OPCODE CENSUS
 * and LENGTH (probe-traps #86); census distance 50 -> 2 (only the inner
 * 0.5f guard: retail bc1f+nop, ours bc1fl with the D8D4 load duplicated).
 *
 * WHAT LANDED, in the order it was measured (each arm alone at the tree
 * baseline, then combined; build/fg45/logs/b1..b6.log):
 *  1. THE PRODUCT (the root of the FPR shift).  Retail computes BOTH
 *     `var_f2*t` and `var_f3*t` BEFORE the four calls and stores/keeps them;
 *     ours forwarded `var_f2*t` into an adda.s/madd.s AFTER the calls,
 *     coalescing var_f2 with var_f20/var_f27_2 and keeping var_f2 + t live in
 *     callee-saved FPRs across the calls.  Merged 005069e0.cpp:819-821 spells
 *     it `spDC = var_f2; spDC *= t;` -- the COMPOUND ASSIGN blocks the fold
 *     ([[insect-compound-assign-blocks-fold]]).  Both sites: adda.s/madd.s/
 *     mul.s/add.s/mov.s/mtc1 all EXACT (L1 50 -> 41).  `sp94 = var_f2*t`
 *     without the alias is BYTE-IDENTICAL to the baseline (re-derived null).
 *  2. The normalize guard pair transcribed VERBATIM from the merged sibling
 *     (repeated division in the first then-arm, self-assign in the second):
 *     +1 word alone, buys bc1t/beq/lui.
 *  3. The four `||` collapses (block_51/57/79/85): beql 3->7, bne 5->1
 *     exact, -1 word each (the baseline was +1 at each site by cancellation).
 *     Then-arm order and the bitfield spelling are INERT (same object).
 *  4. The eight clamps: six get the self-assign third arm, the two empty-then
 *     clamps take the merged sibling's inverted-middle form (`e1`); the
 *     positive-middle form gives bc1fl, wrong.  bc1t 0 -> 6, L1 -> 34.
 *  5. temp_f28 = arg0->f2BC PINNED (`*(volatile f32 *)&`): ours CSE'd it
 *     into temp_f29's register, freeing a callee-saved FPR it then spent
 *     holding sp9C where retail spills it.  ((f32*)arg0)[0xAF] and the
 *     (u8*)+0x2BC spelling give the SAME object.  swc1/nop exact.
 *  6. switch(temp_3) arms in ASCENDING source order (case 0 first):
 *     [[m2c-switch-arm-order]] -- the file's old comment applied the
 *     diagnosis at the wrong layer.
 *  7. D_0047D24C: retail loads it at guards 1, 2, 3 and negates ONCE at
 *     guard 2, reusing -D at guard 4; ours CSE'd one load.  `nd =
 *     -*(volatile f32 *)&D_0047D24C;` before guard 2, used at 2 and 4, is
 *     EXACT LENGTH (649 -> 650) and the SAME OBJECT as the parked GP248
 *     two-symbol spelling.  Pinning guard 3 too is +1 (651).
 *  8. The six f20-named locals declared LAST: 217 -> 215, cells 125 -> 121.
 *     Whole-list DESC/ASC/callee-saved-DESC all read 649 (a colouring-
 *     dependent nop vanishes); DESC = 116 cells, ASC = 147.  Colouring is
 *     NOT a declaration-order problem here -- the remaining map is a uniform
 *     one-register DOWNSHIFT of the callee-saved webs with retail's $f20 web
 *     at our top.  Take membership from the object (probe-traps #84).
 *
 * MEASURED INERT / WORSE at these baselines (do not re-spend):
 *  - inner 0.5f guard: single assignment after the nested ifs (651/652,
 *    var_f27 spilled), `&&` chain (same object), else self-assign, volatile
 *    on either copy (byte-identical), three copies (649), assignment hoisted
 *    before the inner if (648: fixes the branch, loses lwc1+nop).
 *  - sp8C volatile pin at the access: 464 (worse) at the tree baseline.
 *  - prologue order of `var_f22 = -f41C*f3B0`: statement-first / operand
 *    swap move the schedule but not the count; compound form byte-identical.
 *  - var_f2/var_f3 declaration swap (D1): no cell moved.
 * RESIDUE (650 w exact): 18 structural regions -- the prologue schedule of
 * the f41C/f418/f3AC loads (regions 1-4, net 0), the 1.0f mtc1->add.s nop
 * (colouring-induced), the inner guard, and the epilogue order (retail
 * sinks the D_004808A0 store below the restores) -- plus 121 colouring cells.
 ==================================================================== */

/* ====================================================================
 * SESSION 44 (2026-09-02), tag fg44/fg44a.  Board UNCHANGED at 400/409 =
 * 97.80% count, 123,320/134,224 = 91.88% bytes -- this session closed NOTHING.
 * Arming pair held in every scoring run: factory_FactoryStep_5069e0 = MATCH /
 * 1a0e9c68216b, factory_FactoryRectFrameCorner_509f10 = bad 11 / 977182cbe9b7.
 *
 * === THE ONE CHANGE LANDED HERE: u8 FLAGS + BARE TRUTH TEST ===
 * `s32 var_3; s32 var_3_2;` -> `u8`, and `if (var_3 != 0)` -> `if (var_3)`.
 * The BAD COUNT DOES NOT MOVE (460 before and after, md5 2dd4174ebe5d ->
 * 7652b8968761, exact length 650 w).  It is landed anyway because the
 * OPCODE CENSUS goes EXACT IN BOTH DIRECTIONS AT ONCE:
 *     daddiu  retail 4   before 0    after 4
 *     addiu   retail 35  before 39   after 35
 * [[mwcc-daddiu-unsigned-narrow]]: a REGISTER-RESIDENT u8/u16 gives
 * `daddiu`; s32/u32/s64/u64 give `addiu`.  Do NOT try s8/s16 (they add
 * dsll32/dsra32).  ⚠ THE BARE TEST IS MANDATORY -- keeping `!= 0` on the u8
 * buys an `andi` retail does not have and BREAKS THE LENGTH (652 vs 650).
 * ⚠ The bare test ALONE, type held at s32, is BYTE-IDENTICAL to the
 * baseline -- the u8 is the lever, the bare test only pays for it.
 * ⚠ A positional word diff reports "0 fixed / 0 broke": at 460 bad this
 * unit is DISPLACEMENT-dominated and index-to-index comparison is
 * meaningless.  Score this unit by OPCODE CENSUS until the CFG lands.
 *
 * === THE MERGED 1-PARAMETER DEFINITIONS ARE WRONG-BUT-INERT: DO NOT
 *     "FIX" OUR DECLARATIONS TO MATCH THEM ===
 * build/fg44/protoscan44.py flags our
 *     extern "C" f32 factory_FactoryGridSnapZ_503670(void *, f32);
 *     extern "C" f32 factory_FactoryGridSnapX_5036a0(void *, f32);
 * against the MERGED definitions `void factory_FactoryGridSnapZ_503670(S *p)` and
 * `s32 factory_FactoryGridSnapX_5036a0(void *p)` -- ONE parameter, 8 call sites here
 * pass TWO.  ⚠ OUR DECLARATIONS ARE RIGHT.  Retail marshals a FLOAT into
 * $f12 in the delay slot immediately before `jal 0x005036A0` (idx 406) and
 * moves $f0 into $f31/$f28 after it, so the callee really does take a float
 * and return one.  ⇒ A MERGED CALLEE'S DEFINITION DOES NOT CONSTRAIN A
 * PARAMETER THE CALLEE IGNORES -- the definition is only ground truth for
 * parameters its BODY READS.  See [[merged-callee-signature-oracle]].
 ==================================================================== */

/* factory.bin overlay, 0x005050C0 -- 2,600 B / 650 words.
 *
 * SIX `jalr $25` sites, every one `lw $25,0xC0($16)` / `lw $25,SLOT($25)`, so
 * the func_1C3BC0 result is a C++ object whose vptr sits at its OWN offset
 * 0xC0 and whose `this` is passed UNADJUSTED.  Measured here today with a
 * throwaway probe: a class carrying `u8 pad00[0xC0];` ahead of its first
 * virtual emits exactly `lw $25,0xC0($4)` / `lw $25,8+4*N($25)`, so
 *     0x84->v31  0xA4->v39  0xA8->v40  0xB0->v42  0xB4->v43  0xC8->v48.
 * The dummy slots are DECLARED AND NEVER DEFINED, so no vtable is emitted and
 * `nm` shows no mangled name.  (Re-derived, not assumed: C reaches only
 * `jalr $2` -- measured on all three fn-pointer spellings.)
 *
 * arg0 is a DIFFERENT object from the call target; m2c had merged the two.
 *
 * ** THE C++ TAX ON THIS UNIT IS ALIGNMENT. **  `__attribute__((aligned(16)))`
 * yields lq/sq in C and is a MEASURED NULL in C++ (mwcc's C++ front end parses
 * the attribute and drops it) -- so are `#pragma align 16`, `#pragma options
 * align`, the member-attribute form and the array typedef.  The one spelling
 * that reaches a 16-byte load/store from C++ is a GNU MODE attribute:
 *     typedef unsigned int u128 __attribute__((mode(TI)));
 * so V is a union of that with the float view, and the six vector copies stay
 * lq/sq while `.v.x` / `.v.z` stay lwc1/swc1.
 *
 * spA0..spAC are ONE address-taken 16-byte object, not four scalars: m2c's
 * split made mwcc treat spA4/spA8 as never initialised and delete the reads.
 */

/* STATE 2026-08-31 (fx21b).  650 -> this draft is 0xA30 vs retail 0xA28, i.e.
   TWO WORDS LONG, with the frame (0xD0), the six `jalr $25`, the eighteen
   lq/sq and the callee-saved set all matching retail.
   The whole excess is ONE construct: mwcc contracts `var_f24 + <named product>`
   into mtc1/adda.s/madd.s at 0x005054F4 and 0x005056C0 where retail keeps a
   plain add.s (ours 5 madd.s, retail 3).  MEASURED NULL on that contraction:
   operand order either way, sp94-vs-temp_f0_2, naming the product at all
   ([[normal-named-product-local]] does NOT reach these two sites), and
   `#pragma fp_contract off` / `#pragma opt_fma off`.
   `volatile` on the product DOES kill it (see
   build/parked-fx21b/factory_FactoryCameraUpdate_5050c0.EXACTLEN-volatile.cpp = exact 0xA28
   length, 462/650 bad; and .madd3-volatile.cpp = madd 3/3 but 0xA24) -- at the
   cost of a dedicated stack slot that pushes the frame to 0xE0 and shifts every
   sp-relative access, so it is NOT installed.  Find a frame-free blocker.
   Also measured NULL here: comparing against var_f27 instead of the 1.0f
   literal at the `!(temp_f26_2 <= 1.0f)` guard. */

extern "C" f32 fabsf(f32);

extern f32 D_0047D24C;
/* MEASURED fy22G: retail loads D_0047D24C FOUR times and CSEs nothing; we CSE
   it into $f3 and duplicate the neg instead.  Spelling the NEGATED uses as
   `-D_0047D248.b` (struct GP248{f32 a;f32 b;} at 0x0047D248, 8 B so it stays
   in small data) DOES reach retail's shape at the join -- it is +1 word
   (0xa28 -> 0xa2c) and drops the edit distance -- but it then leaves the unit
   one word long, so it is PARKED here, not installed.  [[insect-cse-two-spellings]] */
extern f32 D_0047D8D4;
extern const f32 D_004808A0 __attribute__((section(".sdata")));

typedef unsigned int u128 __attribute__((mode(TI)));

struct VF { f32 x; f32 y; f32 z; f32 w; };
union  V  { u128 q; VF v; };

struct P4 { f32 x; f32 y; f32 z; s32 w; };

class VObj {
public:
    u8 pad00[0xC0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31(f32 a, f32 b, f32 c);   /* vtable slot 0x84 */
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39(void *p);   /* vtable slot 0xA4 */
    virtual void v40(void *p);   /* vtable slot 0xA8 */
    virtual void v41();
    virtual void v42(void *p);   /* vtable slot 0xB0 */
    virtual void v43(void *p);   /* vtable slot 0xB4 */
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48(f32 a);   /* vtable slot 0xC8 */
};

struct Root { u8 pad00[0x4344]; s32 f4344; };

struct S {
    u8  pad00[0x29C];
    f32 f29C;
    u8  pad2A0[0x8];
    f32 f2A8;
    u8  pad2AC[0xC];
    f32 f2B8;
    f32 f2BC;
    u8  pad2C0[0x8];
    s32 f2C8;
    u8  pad2CC[0x4];
    s32 f2D0;
    u8  pad2D4[0x2E];
    s8  f302;
    u8  pad303[0x5D];
    V   f360;
    u8  pad370[0x10];
    V   f380;
    V   f390;
    f32 f3A0;
    f32 f3A4;
    f32 f3A8;
    f32 f3AC;
    f32 f3B0;
    f32 f3B4;
    f32 f3B8;
    f32 f3BC;
    f32 f3C0;
    f32 f3C4;
    f32 f3C8;
    u8  pad3CC[0x4];
    f32 f3D0;
    f32 f3D4;
    f32 f3D8;
    f32 f3DC;
    f32 f3E0;
    f32 f3E4;
    u8  pad3E8[0x18];
    f32 f400;
    u8  pad404[0x4];
    f32 f408;
    u8  pad40C[0xC];
    f32 f418;
    f32 f41C;
    V   f420;
    V   f430;
    u8  pad440[0x10];
    V   f450;
    V   f460;
    u8  pad470[0x10];
    s8  f480;
    s8  f481;
    s8  f482;
    u8  f483;
    f32 f484;
};

extern "C" f32   factory_FactoryGridSnapZ_503670(void *, f32);
extern "C" f32   factory_FactoryGridSnapX_5036a0(void *, f32);
extern "C" f32   factory_FactoryFineGridSnapZ_5036d0(void *, f32);
extern "C" f32   factory_FactoryFineGridSnapX_503700(void *, f32);
extern "C" s32   factory_FactoryCameraShakeStep_504ee0(void *);
extern "C" s32   func_10AAB8(void *, void *, void *, f32);
extern "C" f32   func_128D30(f32);
extern "C" f32   func_128FD0(f32);
extern "C" f32   func_1291A8(f32, f32);
extern "C" s32   func_13BE20(void *, void *, void *);
extern "C" s32   func_13BE40(void *, void *, void *);
extern "C" f32   func_13C050(f32);
extern "C" f32   func_13D470(void *);
extern "C" f32   func_13D4A0(void *);
extern "C" s32   func_183A20(void *, s32);
extern "C" u8 D_004B2570[];
extern "C" void *func_1C3BC0(void *, s32);
extern "C" s32   func_1CBCA0(void *, void *, f32);
extern "C" s32   func_1CBDC0(void *, void *, void *);
extern "C" void *func_1F5BE0();

extern "C" void factory_FactoryCameraUpdate_5050c0(struct S *arg0);

void factory_FactoryCameraUpdate_5050c0(struct S *arg0){
    u8  spC0[0x10];
    u8  spB0[0x10];
    P4  spA0;
    f32 var_f31;
    f32 var_f30;
    f32 temp_f29;
    f32 temp_f28;
    f32 var_f27;
    f32 sp9C;
    f32 sp98;
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    f32 sp70;
    f32 temp_f26;
    f32 temp_f26_2;
    f32 temp_f25;
    f32 temp_f25_2;
    f32 temp_f24;
    f32 var_f24;
    f32 temp_f23;
    f32 var_f23;
    f32 var_f22;
    f32 var_f22_2;
    f32 var_f21;
    f32 var_f21_2;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f27b;
    f32 temp_f31;
    f32 temp_f28_3;
    f32 var_f27_2;
    f32 var_f20_2;
    f32 temp_f28_2;
    f32 var_f20;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    f32 temp_f1_4;
    f32 temp_f1_5;
    f32 temp_f1_6;
    f32 temp_f4;
    f32 nd;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f0_3;
    f32 var_f3;
    f32 var_f2;
    s32 temp_18;
    s32 temp_2_3;
    u8 var_3;
    u8 var_3_2;
    s8 temp_2_4;
    s8 temp_3;
    s8 var_2;
    Root *temp_2;
    VObj *temp_2_2;
    void *temp_4;
    void *temp_4_2;
    void *temp_4_3;

    temp_2 = (Root *)(func_1F5BE0());
    temp_2_2 = (VObj *)(func_1C3BC0(temp_2, temp_2->f4344));
    temp_2_2->v31(0.0f, 0.0f, 0.0f);
    temp_2_2->v39((void *)spB0);
    temp_2_2->v40((void *)spC0);
    func_13BE40(&spA0, (void *)spB0, (void *)spC0);
    temp_f26 = func_1291A8(spA0.x, spA0.z);
    temp_f25 = func_1291A8(spA0.y, func_13D470(&spA0));
    temp_f24 = func_13D4A0(&spA0);
    temp_f23 = arg0->f418 * arg0->f3AC;
    var_f22 = -arg0->f41C;
    var_f22 *= arg0->f3B0;
    temp_f20 = arg0->f3B4;
    temp_18 = func_183A20(D_004B2570, 2);
    var_f21 = temp_f20 * (f32) (temp_18 - func_183A20(D_004B2570, 1));
    if (var_f21 <= (D_0047D24C * temp_f20)) {
        temp_f1 = arg0->f3C8 * (temp_f24 - arg0->f3DC);
        if (temp_f1 < 1.0f) {
            if (temp_f1 > 0.0f) {
                var_f21 *= temp_f1;
            } else {
                var_f21 = -temp_f1 * temp_f20;
            }
        }
    }
    nd = -*(volatile f32 *)&D_0047D24C;
    if (!(var_f21 < (nd * temp_f20))) {
        temp_f1_2 = arg0->f3C8 * (arg0->f3E0 - temp_f24);
        if (temp_f1_2 < 1.0f) {
            if (temp_f1_2 > 0.0f) {
                var_f21 *= temp_f1_2;
            } else {
                var_f21 = temp_f1_2 * temp_f20;
            }
        }
    }
    temp_f4 = arg0->f3B0;
    if (var_f22 <= (*(volatile f32 *)&D_0047D24C * temp_f4)) {
        temp_f1_3 = arg0->f3C4 * (temp_f25 - arg0->f3D4);
        if (temp_f1_3 < 1.0f) {
            if (temp_f1_3 > 0.0f) {
                var_f22 *= temp_f1_3;
            } else {
                var_f22 = -temp_f1_3 * temp_f4;
            }
        }
    }
    if (!(var_f22 < (nd * temp_f4))) {
        temp_f1_4 = arg0->f3C4 * (arg0->f3D8 - temp_f25);
        if (temp_f1_4 < 1.0f) {
            if (temp_f1_4 > 0.0f) {
                var_f22 *= temp_f1_4;
            } else {
                var_f22 = temp_f1_4 * temp_f4;
            }
        }
    }
    /* The three float-accumulator clusters m2c could not represent.  Each is
       an ordinary lerp `x + rate * (target - x)`; mwcc reaches retail's
       mtc1/adda.s/sub.s/madd.s from exactly this spelling -- measured in
       build/f18/LEVERS-ORCH.md.  Registers read off 0x0050535C-0x005053A4. */
    arg0->f3B8 = func_13C050(arg0->f3B8 + arg0->f3E4 * (temp_f23 - arg0->f3B8));
    arg0->f3BC = func_13C050(arg0->f3BC + arg0->f3E4 * (var_f22 - arg0->f3BC));
    arg0->f3C0 = arg0->f3C0 + arg0->f3E4 * (var_f21 - arg0->f3C0);
    arg0->f3A0 = func_13C050(temp_f26 + arg0->f3B8);
    arg0->f3A4 = func_13C050(temp_f25 + arg0->f3BC);
    var_f27 = 1.0f;
    arg0->f3A8 = (f32) (temp_f24 + arg0->f3C0);
    temp_f0 = arg0->f400;
    temp_f1_5 = arg0->f408;
    var_f30 = arg0->f2B8;
    temp_f29 = arg0->f2BC;
    temp_f26_2 = fabsf(temp_f0);
    temp_f25_2 = fabsf(temp_f1_5);
    var_f2 = temp_f0 / temp_f26_2;
    var_f3 = temp_f1_5 / temp_f25_2;
    if (!(temp_f26_2 <= 1.0f)) {
        var_f3 = temp_f1_5 / temp_f25_2;
    } else {
        var_f2 = temp_f0;
    }
    if (!(temp_f25_2 <= 1.0f)) {
        var_f2 = var_f2;
    } else {
        var_f3 = temp_f1_5;
    }
    temp_2_3 = arg0->f2C8;
    var_f24 = arg0->f390.v.x;
    var_f23 = arg0->f390.v.z;
    sp9C = arg0->f420.v.x;
    var_f22_2 = arg0->f380.v.x;
    var_f21_2 = arg0->f380.v.z;
    temp_f12 = arg0->f360.v.x;
    temp_f20_2 = arg0->f360.v.z;
    sp98 = arg0->f420.v.z;
    switch (temp_2_3) {                             /* switch 1 */
    case 15:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
        var_f31 = arg0->f2B8;
        temp_f28 = *(volatile f32 *)&arg0->f2BC;
        temp_f1_6 = arg0->f29C * arg0->f484;
        sp94 = var_f2;
        sp94 *= temp_f1_6;
        sp90 = var_f3 * temp_f1_6;
        sp8C = factory_FactoryFineGridSnapX_503700(arg0, temp_f12);
        sp88 = factory_FactoryFineGridSnapX_503700(arg0, temp_f20_2);
        sp84 = factory_FactoryFineGridSnapX_503700(arg0, sp9C);
        sp80 = factory_FactoryFineGridSnapX_503700(arg0, sp98);
        var_f20 = var_f24 + sp94;
        if (var_f20 < var_f31) {
            var_f20 = var_f31;
        } else if (!(var_f20 <= temp_f28)) {
            var_f20 = temp_f28;
        } else {
            var_f20 = var_f20;
        }
        temp_f0_3 = var_f23 + sp90;
        if (temp_f0_3 < var_f31) {
            var_f31 = var_f31;
        } else if (!(temp_f0_3 <= temp_f28)) {
            var_f31 = temp_f28;
        } else {
            var_f31 = temp_f0_3;
        }
        temp_f28_2 = factory_FactoryFineGridSnapX_503700(arg0, var_f20);
        temp_f0_4 = factory_FactoryFineGridSnapZ_5036d0(arg0, var_f31);
        var_3 = 0;
        if (!(arg0->f2D0 & 1)) {
            var_f24 = var_f20;
            var_f23 = var_f31;
            var_f22_2 = temp_f28_2;
            var_f21_2 = temp_f0_4;
        } else {
            if ((arg0->f482 == 0) || !(arg0->f484 < 1.0f)) {
                if (!(temp_f26_2 <= 0.0f) || (((u64) ((s64) arg0->f483 << 0x3E) >> 0x3F) != 0)) {
                    var_f24 = var_f20;
                    var_f22_2 = temp_f28_2;
                } else {
                    var_f24 = sp8C;
                    var_f22_2 = sp8C;
                }
                if (!(temp_f25_2 <= 0.0f) || (((u64) ((s64) arg0->f483 << 0x3E) >> 0x3F) != 0)) {
                    var_f23 = var_f31;
                    var_f21_2 = temp_f0_4;
                } else {
                    var_f23 = sp88;
                    var_f21_2 = var_f23;
                }
            }
            if ((sp8C != sp84) || (sp88 != sp80)) {
                var_3 = 1;
            }
        }
        arg0->f390.v.x = var_f24;
        arg0->f390.v.z = var_f23;
        arg0->f380.v.x = var_f22_2;
        arg0->f380.v.z = var_f21_2;
        if (var_3) {
            arg0->f302 = 1;
        }
        break;
    case 11:                                        /* switch 1 */
    case 17:                                        /* switch 1 */
    case 18:                                        /* switch 1 */
    case 19:                                        /* switch 1 */
        temp_f0_5 = arg0->f2A8 * arg0->f484;
        temp_f27b = var_f2;
        temp_f27b *= temp_f0_5;
        sp7C = var_f3 * temp_f0_5;
        temp_f31 = factory_FactoryGridSnapX_5036a0(arg0, temp_f12);
        temp_f28_3 = factory_FactoryGridSnapX_5036a0(arg0, temp_f20_2);
        sp78 = factory_FactoryGridSnapX_5036a0(arg0, sp9C);
        sp74 = factory_FactoryGridSnapX_5036a0(arg0, sp98);
        var_f27_2 = var_f24 + temp_f27b;
        if (var_f27_2 < var_f30) {
            var_f27_2 = var_f30;
        } else if (!(var_f27_2 <= temp_f29)) {
            var_f27_2 = temp_f29;
        } else {
            var_f27_2 = var_f27_2;
        }
        var_f20_2 = var_f23 + sp7C;
        if (var_f20_2 < var_f30) {
            var_f20_2 = var_f30;
        } else if (!(var_f20_2 <= temp_f29)) {
            var_f20_2 = temp_f29;
        } else {
            var_f20_2 = var_f20_2;
        }
        sp70 = factory_FactoryGridSnapX_5036a0(arg0, var_f27_2);
        temp_f0_6 = factory_FactoryGridSnapZ_503670(arg0, var_f20_2);
        var_3_2 = 0;
        if ((arg0->f480 < 0) && ((arg0->f482 == 0) || !(arg0->f484 < 1.0f))) {
            if (!(temp_f26_2 <= 0.0f) || (((u64) ((s64) arg0->f483 << 0x3E) >> 0x3F) != 0)) {
                var_f22_2 = sp70;
                var_f24 = var_f27_2;
            } else {
                var_f24 = temp_f31;
                var_f22_2 = temp_f31;
            }
            if (!(temp_f25_2 <= 0.0f) || (((u64) ((s64) arg0->f483 << 0x3E) >> 0x3F) != 0)) {
                var_f23 = var_f20_2;
                var_f21_2 = temp_f0_6;
            } else {
                var_f23 = temp_f28_3;
                var_f21_2 = var_f23;
            }
        }
        if ((temp_f31 != sp78) || (temp_f28_3 != sp74)) {
            var_3_2 = 1;
        }
        arg0->f390.v.x = var_f24;
        arg0->f390.v.z = var_f23;
        arg0->f380.v.x = var_f22_2;
        arg0->f380.v.z = var_f21_2;
        if (var_3_2) {
            arg0->f302 = 1;
            if (arg0->f480 < 0) {
                temp_2_4 = arg0->f481;
                if (temp_2_4 < 6) {
                    arg0->f481 = (s8) (temp_2_4 + 1);
                }
                temp_3 = arg0->f481;
                /* [[m2c-switch-arm-order]] + [[insect-switch-arm-break-vs-return]]:
                   retail tests ==1 THEN ==0 and stores f480 SEPARATELY in all
                   three arms (`b .L864; sb` twice plus the fall-in store).
                   m2c's shared `block_102` store is one word short. */
                switch (temp_3) {
                case 0:
                    arg0->f480 = 7;
                    break;
                case 1:
                    arg0->f480 = 3;
                    break;
                default:
                    arg0->f480 = 0;
                    break;
                }
            }
        }
        /* [[insect-guard-polarity-length]]: retail's guard is the POSITIVE
           `< 0.5f` with the else arm folded into the bc1fl delay slot; the
           inverted spelling costs bc1t/nop/b instead of one bc1fl. */
        if (temp_f26_2 < 0.5f) {
            if (temp_f25_2 < 0.5f) {
                arg0->f480 = 0;
                arg0->f481 = -1;
            }
        }
        var_f27 = D_0047D8D4;
        break;
    default:                                        /* switch 1 */
        func_1CBCA0(&spA0, (void *)((u8 *)arg0 + 0x400), arg0->f3D0);
        temp_4 = (void *)((void *)((u8 *)arg0 + 0x380));
        func_1CBDC0(temp_4, temp_4, &spA0);
        temp_4_2 = (void *)((void *)((u8 *)arg0 + 0x390));
        func_1CBDC0(temp_4_2, temp_4_2, &spA0);
        var_f0 = arg0->f390.v.x;
        if (var_f0 < var_f30) {
            var_f0 = var_f30;
        } else if (!(var_f0 <= temp_f29)) {
            var_f0 = temp_f29;
        } else {
            var_f0 = var_f0;
        }
        arg0->f390.v.x = var_f0;
        var_f0_2 = arg0->f390.v.z;
        if (var_f0_2 < var_f30) {
            var_f0_2 = var_f30;
        } else if (!(var_f0_2 <= temp_f29)) {
            var_f0_2 = temp_f29;
        } else {
            var_f0_2 = var_f0_2;
        }
        arg0->f390.v.z = var_f0_2;
        arg0->f460 = arg0->f390;
        arg0->f450.v.x = factory_FactoryGridSnapX_5036a0(arg0, arg0->f460.v.x);
        arg0->f450.v.z = factory_FactoryGridSnapZ_503670(arg0, arg0->f460.v.z);
        arg0->f430 = arg0->f450;
        break;
    }
    arg0->f420 = arg0->f360;
    var_f0_3 = arg0->f380.v.x;
    if (var_f0_3 < var_f30) {
        var_f0_3 = var_f30;
    } else if (!(var_f0_3 <= temp_f29)) {
        var_f0_3 = temp_f29;
    } else {
        var_f0_3 = var_f0_3;
    }
    arg0->f380.v.x = var_f0_3;
    temp_f0_7 = arg0->f380.v.z;
    if (temp_f0_7 < var_f30) {
        var_f30 = var_f30;
    } else if (!(temp_f0_7 <= temp_f29)) {
        var_f30 = temp_f29;
    } else {
        var_f30 = temp_f0_7;
    }
    arg0->f380.v.z = var_f30;
    temp_4_3 = (void *)((void *)((u8 *)arg0 + 0x360));
    func_10AAB8(temp_4_3, (void *)((u8 *)arg0 + 0x380), temp_4_3, arg0->f3E4 * var_f27);
    temp_f20_3 = arg0->f3A8 * func_128D30(arg0->f3A4);
    spA0.x = temp_f20_3 * func_128FD0(arg0->f3A0);
    spA0.y = arg0->f3A8 * func_128FD0(arg0->f3A4);
    temp_f20_4 = arg0->f3A8 * func_128D30(arg0->f3A4);
    temp_f0_8 = temp_f20_4 * func_128D30(arg0->f3A0);
    spA0.w = 0;
    spA0.z = temp_f0_8;
    func_13BE20(arg0->pad370, &arg0->f360, &spA0);
    temp_2_2->v42(arg0->pad370);
    temp_2_2->v43(&arg0->f360);
    arg0->f430 = arg0->f360;
    arg0->f450 = arg0->f380;
    arg0->f460 = arg0->f390;
    factory_FactoryCameraShakeStep_504ee0(arg0);
    temp_2_2->v48(1.0f);
    *(f32 *)&D_004808A0 = arg0->f380.v.x;
}
