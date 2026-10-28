/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuWeaponGridDrawCb_503930 1
#include "port/game_protos.h"
#line 1
/* === SESSION 82 (2026-09-21, SOLO): 17 BAD -> MATCH, exact 429 words, CLOSED.
 * In config/ocunits/normal.txt; NORMAL.BIN relinked BYTE-IDENTICAL at 644
 * units.  Decks build/wf-normal/s82/{a1,b1,c1,d1,e1,f1,g1,h1}.py.  TWO edits.
 *
 * EDIT 1 (17 -> 2).  THE FRAME PARTITION IS A DECLARATION ORDER after all.
 * s48/s75 read the 15-word residue correctly (two three-slot blocks swapped
 * around `v` at 0x190) and concluded "the col temps are in the COMPILER-TEMP
 * half and u2/v2/y0 in the NAMED-LOCAL half, and NO declaration edit moves a
 * value between halves".  That conclusion was wrong, and the reason it looked
 * right is that s75 moved the col trio at four positions but NEVER MOVED `v`.
 * Read the two layouts as ONE list, descending:
 *     ours    u(1C0) v2(1B0) u2(1A0) v(190) c3(180) c2(170) c1(160)
 *     retail  c3(1C0) c2(1B0) c1(1A0) v(190) u(180) v2(170) u2(160)
 * ours IS the declaration order of the homed locals, exactly.  So retail's
 * declaration order is c3, c2, c1, v, u, v2, u2 -- the col copies are NAMED
 * LOCALS DECLARED FIRST, and `v` is declared BEFORE `u`.  Both halves at once:
 *     s32 c3; s32 c2; s32 c1; s32 v; s32 u; s32 v2; s32 u2;
 * plus the LICM hoist written by hand ABOVE the while loop, in retail's
 * emission order (c3 = col[3]; c2 = col[2]; c1 = col[1];) and the c-names used
 * at the two func_13EE40 sites.  d1.py, 7 arms:
 *     MODEL c3,c2,c1,v,u,v2,u2       2     <- installed
 *     same, hoist written c1 first   6        (the assignment order is a
 *     c1,c2,c3 decl order            7         SECOND, independent axis)
 *     c-trio first, `v` left last   13
 *     v first, c-trio last / v_first / v_second   20
 * !! THE RULE, and it is the reusable part: mwcc hands out the HOMED cells in
 * DESCENDING ADDRESS ORDER OF DECLARATION, and NAMING A COMPILER TEMP GIVES IT
 * A DECLARATION SLOT.  That is how a value crosses the "halves" s75 saw.
 * (s75 also mislabelled the third named cell `y0`; words 294/295 are
 * func_13ED60(wd, u, v), so the cell at retail 0x180 is `u`.)
 *
 * EDIT 2 (2 -> MATCH).  The 0x005039F4/F8 pair, open since s28.  g1.py swept
 * the whole colour-product surface -- all 6 factor orders x both groupings,
 * plus pointer-arithmetic spellings of either operand: EXACTLY TWO OBJECTS,
 * f14-first (2 bad) and f10-first (4 bad), because the two pointer loads are
 * POSITION-BOUND ($6 at word 41, in the annulled delay slot of the q->f18
 * guard; $5 at word 45) and WHICH pointer lands in the slot follows the SECOND
 * factor.  Retail wants q->f10 in BOTH roles, so no product spelling can do it.
 * The fix is to take the two pointers out of the product and give each its own
 * WEB, assigned in retail's order:
 *     f32 *pA;  f32 *pB;                    (declared after `ph`)
 *     pA = q->f10;
 *     pB = q->f14;
 *     for (i = 0; i < 4; i++) col[i] = (s32)(128.0f * pA[i] * pB[i]);
 * h1.py's 2x2x2 (declaration order x ASSIGNMENT order x use order) says only
 * the ASSIGNMENT order and the USE order matter, and they must agree:
 *     aAB pAB  MATCH   aAB pBA  2   aBA pAB  4   aBA pBA  2
 * declaration order of pA/pB is INERT in all four.  Same lever as EDIT 1 seen
 * at the register file instead of the frame: name the temp, then choose WHEN
 * it is first defined.
 *
 * DATED ARMED NULLS from this session, do not rebuild:
 *  * b1.py -- s75's named cross (`inline u2` -1, `inline v2` -1, the pair -2,
 *    all three -3) crossed with a1.py's `const` +1/+2 ladder (`const` on the
 *    gp pointers D_00484454 +1, D_00484458 +1, D_0048449C +2).  TWELVE cells,
 *    250-302 bad: `const` on a gp POINTER re-reads it everywhere and is a
 *    terrible +1 partner.  a1.py also: `const` on D_0044B710/normal_D_00526410/
 *    normal_D_00526420 (the lui-addressed tables) is BYTE-IDENTICAL.
 *  * e1.py -- the product re-priced on top of EDIT 1 before EDIT 2 was found.
 */
/* === SESSION 75 (2026-09-21, SOLO): STILL 17 BAD / 429 words.  No move, but
 * the 15-word STACK-SLOT fact s48 named is now bounded from three sides and one
 * NEW CROSS HALF PAIR is priced.  Sweeps: build/wf-normal/s75/c1.py, c2.py,
 * c3.py (logs alongside).
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ THE FRAME PARTITION IS RIGID, AND THAT IS THE FINDING.  Retail lays the
 * seven spilled cells out u2@0x160 v2@0x170 y0@0x180 | v@0x190 | col1@0x1A0
 * col2@0x1B0 col3@0x1C0; ours has the col LICM temps LOW (0x160-0x180) and
 * u2/v2/y0 HIGH (0x1A0-0x1C0), with `v` at 0x190 in BOTH.  Every arm this
 * session shuffles cells WITHIN one half and NOT ONE crosses `v`:
 *  - moving the `s32 col[4];` declaration (5 positions: last, after y0, before
 *    v, after v, before `Req rq`) -- the four late positions are BYTE-IDENTICAL
 *    to base (bb91c064) and `col_before_rq` is LIVE at 30 bad, so the axis
 *    fires and still cannot reach the partition;
 *  - moving the v2/u2/y0 trio (head 31, last 20, contiguous 17 == base,
 *    contiguous-after-v 20).  `trio_last`'s residue was read word by word: it
 *    re-orders u2/v2/y0 among 0x190-0x1C0 and leaves the col temps at
 *    0x160-0x180 untouched.
 * ==> the col temps are in the COMPILER-TEMP half of the frame and u2/v2/y0 in
 * the NAMED-LOCAL half, and NO declaration edit moves a value between halves.
 * [[levers.d/mwcc-stack-slot-decl-order]]'s "cells top-down = declaration
 * order" holds only WITHIN a half.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ THE HYPOTHESIS THAT FOLLOWS, AND ITS MEASUREMENT.  If the halves are fixed,
 * retail's layout says retail NAMES col1..3 and does NOT name u2/v2/y0.  Both
 * halves of that were built (c2.py):
 *  - naming col[1..3] as c1/c2/c3 (s48's hoist) at four declaration positions:
 *    head 36, before `e1` 36, before `v` 22, last 19.  Live, never better.
 *  - INLINING u2/v2/y0 at their use sites is THREE WORDS SHORT (0x6a8 vs
 *    0x6b4): mwcc CSEs all three straight back out of the loop.  Every cross of
 *    the two is therefore also -3 and unscoreable.
 * ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ PRICED SEPARATELY (c3.py), and this is the reusable number:
 *      inline u2 alone   -1 w      inline v2 alone   -1 w
 *      inline y0 alone   EXACT LENGTH, 23 bad        u2+v2  -2 w
 * `inl_y0` is the only exact-length cell.  Its residue keeps ALL 15 original
 * slot words AND adds a six-word rotation of the 0xE0/0xF0/0x100 QUAD cells --
 * so inlining y0 does not move it out of the named half either, it just creates
 * one more temp.  ==> u2 and v2 are each a clean -1 CROSS HALF looking for a +1
 * partner ([[levers.d/two-edit-cross-beats-count-ranking]]); nothing on this
 * unit is a known +1 yet.
 *
 * The other 2 words (0x005039F4/F8) are unchanged: s48's `128.0f * q->f10[i] *
 * q->f14[i]` fixes them and costs four elsewhere (19).  That is the second
 * cross half and it is still unpaired. */
/* === SESSION 48 (2026-09-07, SOLO): 35 -> 17 BAD, exact 429 words.  THREE
 * edits, and every one re-opened a recorded negative in a NEW COAT:
 *  1. ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ THE IDENTITY-CAST PIN, `q = (Req *)(s32)q;` after `q = &rq;`  (35 ->
 *     28, and it DELETES the six-word hunk this header's s45 note called the
 *     unit's only structural difference).  s28's "SIXTEEN source spellings of
 *     the pointer, all 0x6b0" predates [[mwcc-identity-cast-splits-cse]] /
 *     [[mwcc-propagated-temp-colouring]]: none of the sixteen was the cast.
 *     With it in, mwcc stops forward-substituting `&rq` into `0x220($29)`,
 *     materialises the frame address in $16 and reads BOTH guards through it,
 *     exactly as retail does.  (s32) / (u32) / inline / via (u8*) are one
 *     object; `q` pinned ABOVE the field stores is 39, and the f18 store
 *     written through the pinned `q` is 29.)
 *  2. ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ SWAP THE COUNTER ROLES, not the declarations (28 -> 17).  `k` counts
 *     the `(f32)k < fx` loop and `i` counts the inner `k < 8` loop.  The
 *     residue was a $30/$23 callee-saved transposition -- retail i=$23,
 *     {py,k}=$30 -- and ALL 24 declaration positions of `i` are ONE OBJECT
 *     (a_3930b.py), so the declaration slot is inert here just as it is on
 *     normal_TransMenuMinimapMarkersDrawMaybe_5174d0.  What moved it is WHICH NAMED VARIABLE COUNTS
 *     WHICH LOOP, i.e. the creation order of the two webs.  A dedicated
 *     counter for either loop, `k = 0;` hoisted, `py = 0;` seeded, and an
 *     explicit `i = 0;` before a `for (;;)` are all byte-identical nulls.
 *  3. `s32 v2;` declared BEFORE `s32 u2;` -- same score (17) but a DIFFERENT
 *     object, and it puts the u2/v2 pair in retail's RELATIVE slot order.
 *     Keep it: it makes the remaining residue one clean fact.
 *
 * ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  RESIDUE 17 words, and it is now ONE STACK-SLOT FACT plus one pair:
 *   - 15 w: two three-slot BLOCKS are swapped around `v` at 0x190.  Retail
 *     lays out u2@0x160 v2@0x170 y0@0x180 | v@0x190 | col1@0x1A0 col2@0x1B0
 *     col3@0x1C0; ours has the col LICM temps at 0x160-0x180 and u2/v2/y0 at
 *     0x1A0-0x1C0.  ([[mwcc-stack-slot-decl-order]] -- same instruction,
 *     different K($sp).)  MEASURED NULL: hoisting col[1..3] into explicit
 *     named locals reproduces retail's copies but scores 19-36 in all four
 *     declaration positions tried, and `licm off` is length-wrong.
 *   -  2 w: `addu $3,$6,$4` / `addu $2,$5,$4` transposed at 0x005039F4 --
 *     retail reads `q->f10[i]` BEFORE `q->f14[i]` in the colour product.
 *     ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  Spelling it that way (`128.0f * q->f10[i] * q->f14[i]`) FIXES those
 *     two and costs four elsewhere (19).  It is a CROSS HALF, not a fix.
 * KEEP OUT OF config/ocunits/normal.txt.  Sweeps: build/wf-normal/s48/
 * a_3930{a,b,c,d,e,f,g}.py. */
/* SESSION 45: 429/429 w, 35 bad.  mdiff.py reduces it to ONE six-word hunk:
 *   retail  sw $2,0x238($29) | lw $2,0x0($16) | bnel | lw $2,0x18($16)
 *   ours    lw v0,544(sp) | bnez | sw v1,568(sp) | b | move | lw v0,24(s0)
 * retail does the `rq.f18 = D_00484458;` STORE FIRST and reads BOTH guards
 * THROUGH `q` ($16); we fold the FIRST read back onto `$sp` and push the store
 * into the branch delay slot.  WARN MEASURED: five placements of `q = &rq;`
 * (above the store, at the top of the block, before the f10/f14 calls, and the
 * store written as `q->f18`) are inert or worse; reading `rq.f00`/`rq.f18`
 * directly instead of through `q` is length-wrong.
 * There is ALSO a live $30/$23 + $f30/$f23 swap worth ~13 of the 35
 * (census `fp>s7:7 s7>fp:3 $f23>$f30:2`) -- a separate colouring axis. */
#pragma optimization_level 3
/* ===== SESSION 28 (2026-09-03): 123 -> 35 BAD at the RIGHT LENGTH (429 words),
 * every arm at level 3 through build/wf-normal/s28/bulkarm28.py, every
 * declaration arm read through gmap28.py's REGISTER MAP not the byte count.
 * STILL OPEN -- deliberately NOT in config/ocunits/normal.txt.
 *  * the WHOLE pragma surface at level 3: 6,592 arms (3,280 names x 2 + the
 *    numeric family), 34 NOBUILD, 11 live (10 length-wrong, `cplusplus on`
 *    161), 0 better.  prag_3930.log.
 *  * FOUR staged whole-list declaration decks (1,642 + 3 x 2,461 arms):
 *    `e` to position 6 (123 -> 80: the prologue group s0/s1/s3/s2 all retail);
 *    j<->w, fx<->fw, fy<->fh (80 -> 57: s1/s6 and $f22-$f25 retail);
 *    k<->h, ph<->ry (57 -> 52); `v` moved past position 27 (52 -> 45).
 *    ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¦Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  the single-move decks plateau where the PAIR-SWAP decks pay.
 *  * statement order in the inner loop: `dy = normal_D_00526420[k]` BEFORE
 *    `dx = normal_D_00526410[k]` (-8) and `q->f14[i] * q->f10[i]` in the colour
 *    product (-2): 45 -> 35.  s5_3930.log.  A named-temp form of the
 *    func_13F110 arguments and `dx + x0` operand order are both worse; the
 *    i<->k declaration swap is worse in every combination.
 * WHAT IS LEFT (35 words, four classes, read off A_dxy_col's words):
 *  1. the frame-address hunk at 0x005039B4-0x005039CC (7 words): retail
 *     materialises `addiu $16,$29,0x220` and loads through $16 -- the s19
 *     "no source spelling reaches it" class, now at the right length.
 *  2. `addu v1,a2,a0` / `addu v0,a1,a0` at 0x005039F4 (2 words): the two
 *     palette-index adds in the other order.
 *  3. SPILL-SLOT ORDER (14 words): retail spills the three colour bytes at
 *     0x1A0/0x1B0/0x1C0 and the px/py/x1 group at 0x160/0x170/0x180; ours is
 *     the reverse pairing.  Spill order follows declaration order
 *     ([[factory-session32-levers]]) but no single move or swap in 8,206
 *     declaration arms flipped it without costing more elsewhere.
 *  4. the i <-> k PAIR (11 words): retail keeps the middle counter `i` in $23
 *     and the 8-point counter `k` in $30; ours the reverse.  The plain swap
 *     is worse; it interacts with class 3. */
/* ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã¢â‚¬Â¹Ãƒâ€¦Ã¢â‚¬Å“ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¦ CLOSED / MOVED, s27, BY `#pragma optimization_level 3`.
 * mwcc's DEFAULT here is -O4.  Level 3 is a DISTINCT AXIS from the `opt_*`
 * pragma namespace [[mwcc-pragma-namespace]] enumerates: 14 `opt_*` arms were a
 * clean null on normal_FieldHudLeaderChangedNop_4f50e0 and 23 were a clean null on this unit's
 * residue, while the LEVEL knob moved both.  Screened over all 68 open drafted
 * normal units in build/wf-normal/s27/olevel.log (levels 1/2/3): levels 1 and 2
 * are catastrophic on every unit, level 3 CLOSED normal_FieldHudPartyPanelsStep_4f57f0 and
 * normal_MenuBattleEndMemberRowsFadeIn_4eb5f0 outright and took normal_ShopMenuSellItemStatusLayout_50ef80 and
 * normal_BtlChgMenuWeaponGridDrawCb_503930 from LENGTH-WRONG to the RIGHT LENGTH. */
/* ===== LANE nd, session 19 -- NOT RE-ATTEMPTED (baseline scored only, 1 trip).
 * Re-confirmed 1 word short (0x6b0 vs 0x6b4).  n_odiff reports 4 short, but 3
 * of those are the listing's TRAILING ALIGNMENT NOPS at 0x00503FE4, which the
 * object does not carry -- the real deficit is ONE word, at 0x005039B0.
 * The residue is `addiu $16,$29,0x220` -- retail materialising a FRAME ADDRESS
 * that mwcc folds back into `0x220($29)`.  Same class as normal_ShopMenuSellItemStatusLayout_50ef80's
 * `sp + i*6`, and the insect session-23 narrowing of
 * [[insect-cse-two-spellings]] predicts that no source spelling reaches it.
 * The 16 spellings + 488 pragmas recorded below are that prediction confirmed.
 * DO NOT SPEND MORE ARMS ON THE SPELLING AXIS. */
#include "types.h"
/* WARNING PARKED at ONE WORD SHORT (428 of 429) -- deliberately NOT in
 * config/ocunits/normal.txt.  Everything else is exact: all 46 calls in order,
 * both nested loops, the eight-point outline table, every guard, and the
 * close path.  n_odiff's only surviving hunk is one instruction:
 *
 *   retail  addiu $16,$29,0x220 / lw $2,-0xD18 / sw $2,0x238 / lw $2,0($16)
 *           / bnel $2,$0,L / lw $2,0x18($16)          <- 8 words
 *   ours    lw $3,-0xD18 / lw $2,0x220($29) / bnez $2,L / sw $3,0x238($29)
 *           / b / daddu / lw $2,0x238($29)            <- 7 words
 *
 * Retail MATERIALISES the frame address of the 0x1C request block into a
 * register and loads through it; ours folds `&rq` back into `0x220($29)`, so
 * the pending store sinks into the branch's delay slot and the `addiu` never
 * exists.  Same instruction multiset otherwise.
 *
 * MEASURED NEGATIVE ON BOTH AXES, and this is the part worth not repeating:
 * - SIXTEEN source spellings of the pointer, all 0x6b0: the pointer assigned
 *   after the stores / before them with the stores through it / at its
 *   declaration / via a `void *` / via a `(u8 *)` cast / as `&rq.f00` /
 *   `const` / `register` / `register`-with-initialiser / assigned on both
 *   paths / `Req rq[1]` with the name decaying / a `{ s32 col[4]; Req rq; }`
 *   frame struct with `&fr.rq` (0x6a0) / the f18 store first / f00 last /
 *   a named local for D_00484458 / a `static` helper taking `Req *`, which
 *   mwcc REFUSES to inline at -O4 even with `#pragma always_inline on`
 *   (0x5f0 -- it emits the helper as its own function).
 * - THE WHOLE COMPILER-KNOB AXIS: `n_knob.py --all`, 488 variants over the
 *   244 recognised pragmas in both polarities (build/n_knob_3930_all.log).
 *   26 are LIVE (a different object from the baseline) and 462 inert, and
 *   not one of the 488 reaches 0x6b4.  Lengths seen: 470 x 0x6b0, 2 x 0x6a4,
 *   and single outliers at 0x6c4/0x6d0/0x6e0/0x728/0x74c/0x76c/0x7a0/0x7d0.
 * ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â‚¬Å¡Ã‚Â¬ÃƒÂ¢Ã¢â‚¬Å¾Ã‚Â¢ this is not a spelling of the pointer and it is not a knob.
 *
 * TWO LEVERS DID LAND and they are the reusable part:
 * - GUARD POLARITY on the four `x = e->fA; if (x <= 0) x = e->fB;` clamps.
 *   Written that way mwcc gives each a branch-LIKELY with the NEXT statement's
 *   load duplicated into the slot; retail has a plain branch + `nop`.  Written
 *   with the FALL-THROUGH arm first -- `if (e->fA <= 0) x = e->fB; else
 *   x = e->fA;` -- all four close at once.  EIGHT bad words, one edit.
 *   `ternary` is +4 words, plain `ifelse` (positive arm first) is inert.
 * - the five-argument signature: mwcc passes arguments 5..8 in $8..$11 on the
 *   EE, so `beqz $8` at the top is a guard on the FIFTH parameter.
 *
 * normal 0x00503930 -- the nine-slice / tiled panel blitter.
 *
 * `open != 0` is the draw path: it builds a 0x1C-byte request block on the
 * frame out of its own arguments plus the 0x21 and 0x55 palette tables, folds
 * the four palette entries into 0..0x7F colour bytes, opens a 0x32C sprite
 * through func_159FB0 and walks the caller's 0x20-byte record list.  Each
 * record is a tile: `f04/f06` (falling back to `f0C/f0E`) give its size,
 * `f10/f14` how many times it repeats, `f18/f1A` its step, and the last
 * partial repeat is scaled by the fractional remainder.  Every tile emits
 * EIGHT func_13ED60/func_13F110 pairs -- the 0x526410 / 0x526420 offset table
 * is an 8-point outline, so each tile is drawn eight times at one-pixel
 * offsets.  `open == 0` is the close path: reset the caller's own context to
 * the framebuffer's size - 1 and flush it.
 *
 * FIVE arguments -- mwcc passes 5..8 in $8..$11 on the EE, so the guard
 * `beqz $8` is on the FIFTH, not on $4.  $4 is read only on the close path.
 *
 * `daddu $17,$2,$0` and `daddu $18,$2,$0` in a call's DELAY SLOT capture the
 * PREVIOUS call's result: func_15DE40's value is read in func_15DE80's slot
 * and func_1451E0's in func_1451D0's, so each belongs to the statement BEFORE
 * the call it sits in.
 * func_15DE40 and func_15DE80 take NO argument (the same reading
 * normal_ShopMenuStep_50a6f0 records).
 * Every `sq`/`lq` at 0xC0..0x150 is mwcc SPILLING a 128-bit GPR, not a source
 * object; the only real frame objects are the 0x1C request block at 0x220 and
 * the four colour bytes at 0x210.
 * `lui $3,0x45 / addiu $3,$3,-0x48F0` is %hi/%lo of the main-image table at
 * 0x0044B710 -- an ADDRESS, not an integer, so it needs a symbol with a size
 * over the small-data threshold.
 * `dsll32/dsra32 ..,16` throughout the inner loop is the explicit (s16) cast
 * on values mwcc holds as int (levers.d/normal-s16-cast-sign-extension). */

typedef struct Rec {
    s16  f00;
    s16  f02;
    s16  f04;
    s16  f06;
    s16  f08;
    s16  f0A;
    s16  f0C;
    s16  f0E;
    f32  f10;
    f32  f14;
    s16  f18;
    s16  f1A;
    u16  f1C;
    u8   pad1E[2];
} Rec;

typedef struct Req {
    Rec *f00;
    s32  f04;
    s32  f08;
    s32  f0C;
    f32 *f10;
    f32 *f14;
    void *f18;
} Req;

typedef struct Wgt {
    s16  f00;
    u8   pad02[0x60 - 2];
    void *f60;
} Wgt;

typedef struct Ctx {
    u8   pad000[0x450];
    s16  f450;
    s16  f452;
} Ctx;

extern s32  D_0044B710[][2];      /* main-image table, addressed lui/%lo */
extern s16  normal_D_00526410[8];
extern s16  normal_D_00526420[8];

extern void *D_0048449C;          /* gp - 0xCD4 */
extern void *D_00484458;          /* gp - 0xD18 */
extern Ctx  *D_00484454;          /* gp - 0xD1C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuWeaponGridDrawCb_503930(void *dc, Rec *rec, s32 bx, s32 by, s32 open)
{
    Req   rq __attribute__((aligned(16)));
    s32   col[4] __attribute__((aligned(16)));
    Req  *q;
    Wgt  *wg;
    void *sc;
    void *fb;
    Rec  *e;
    void *wd;
    void *sv;
    s32   e1;
    s32   e2;
    s32   i;
    s32   w;
    s32   h;
    s32   j;
    s32   k;
    s32   sx;
    s32   sy;
    s32   ox;
    s32   oy;
    s32   px;
    s32   py;
    s32   x;
    s32   y;
    s32   c3;
    s32   c2;
    s32   c1;
    s32   v;
    s32   u;
    s32   v2;
    s32   u2;
    s32   x0;
    s32   y0;
    s32   x1;
    s32   y1;
    s32   dx;
    s32   dy;
    f32   fw;
    f32   fh;
    f32   fx;
    f32   fy;
    f32   ry;
    f32   rx;
    f32   ph;
    f32  *pA;
    f32  *pB;

    if (open != 0) {
        rq.f00 = rec;
        rq.f04 = bx;
        rq.f08 = by;
        rq.f0C = 0x32C;
        rq.f10 = ((f32 *)UiGetWidgetColor_2904b0(D_0048449C, 0x21));
        rq.f14 = ((f32 *)UiGetWidgetColor_2904b0(D_0048449C, 0x55));
        rq.f18 = D_00484458;
        q = &rq;
        q = (Req *)(s32)q;
        if (q->f00 == 0) {
            return 0;
        }
        if (q->f18 == 0) {
            return 0;
        }
        pA = q->f10;
        pB = q->f14;
        for (i = 0; i < 4; i++) {
            col[i] = (s32)(128.0f * pA[i] * pB[i]);
        }
        x = q->f04;
        y = q->f08;
        sc = GetDrawCtxNameTable_15de40();
        fb = GetDrawCtx_15de80();
        e = q->f00;
        DrawListAddTexLoad_1418c0(fb, -1, 1.0f);
        wg = ((Wgt *)NameTableFindByName_159fb0(sc, D_0044B710[D_00484454->f450][D_00484454->f452], q->f0C));
        if (wg == 0) {
            return 0;
        }
        sv = wg->f60;
        wg->f60 = q->f18;
        DrawListAddTexLoad_1418c0(fb, wg->f00, 1.0f);
        wd = DrawListBeginPrim_141b00(fb);
        GsPktSetBlendMode_13e4f0(wd, 2);
        GsPktSetAlphaBlend_13e500(wd, 1);
        GsPktSetAntialias_13e390(wd, 0);
        GsPktEnableAlphaTest_13e4d0(wd, 1);
        GsPktEnableZTest_13e460(wd, 0);
        GsPktSetTextured_13e400(wd, 1);
        GsPktSetUseUV_13e3e0(wd, 1);
        GsPktSetOriginMode_13e2f0(wd, 0);
        GsPktSetTexFilter_13e3d0(wd, 1);
        GsPktSetZWriteMask_13e430(wd, 1);
        GsPktSetGouraud_13e3b0(wd, 0);
        GsPktOpenPrim_13f730(wd, 6);
        GsPktWriteAD_13ec80(wd, 0x40, ((s64)0x014E00EB << 32) | 0x01AF0046);
        GsPktSetTexture_13ec00(wd, wg);
        c3 = col[3];
        c2 = col[2];
        c1 = col[1];
        while (e->f00 != -1) {
            if (e->f04 <= 0) {
                w = e->f0C;
            } else {
                w = e->f04;
            }
            if (e->f06 <= 0) {
                h = e->f0E;
            } else {
                h = e->f06;
            }
            if (e->f10 <= 0.0f) {
                fx = 1.0f;
            } else {
                fx = e->f10;
            }
            if (e->f14 <= 0.0f) {
                fy = 1.0f;
            } else {
                fy = e->f14;
            }
            sx = e->f18;
            if (sx <= 0) {
                sx = w;
            }
            sy = e->f1A;
            if (sy <= 0) {
                sy = h;
            }
            oy = 0;
            for (j = 0; (f32)j < fy; j++) {
                ox = 0;
                fh = (f32)h;
                ry = fy - (f32)j;
                ph = fh * ry;
                for (k = 0; (f32)k < fx; k++) {
                    fw = (f32)w;
                    px = x + (e->f00 + ox);
                    rx = fx - (f32)k;
                    py = y + (e->f02 + oy);
                    if (rx < 1.0f) {
                        fw = fw * rx;
                    }
                    if (ry < 1.0f) {
                        fh = ph;
                    }
                    if (e->f1C & 8) {
                        GsPktSetRGBAQ_13ee40(wd, 0x80, 0x80, 0x80, c3);
                    } else {
                        GsPktSetRGBAQ_13ee40(wd, col[0], c1, c2, c3);
                    }
                    u = e->f08;
                    v = e->f0A;
                    x0 = (s16)px;
                    y0 = (s16)py;
                    u2 = (s16)(u + e->f0C);
                    v2 = (s16)(v + e->f0E);
                    x1 = (s16)(s32)((f32)px + fw);
                    y1 = (s16)(s32)((f32)py + fh);
                    for (i = 0; i < 8; i++) {
                        GsPktSetUV_13ed60(wd, u, v);
                        dy = normal_D_00526420[i];
                        dx = normal_D_00526410[i];
                        GsPktSetXYZPixel_13f110(wd, x0 + dx, y0 + dy, 0);
                        GsPktSetUV_13ed60(wd, u2, v2);
                        GsPktSetXYZPixel_13f110(wd, x1 + dx, y1 + dy, 0);
                    }
                    ox += sx;
                }
                oy += sy;
            }
            e++;
        }
        GsPktClose_13f5b0(wd);
        DrawListEndPrim_141a20(fb);
        DrawListAddTexLoad_1418c0(fb, -1, 1.0f);
        wg->f60 = sv;
        DrawListAddTexLoad_1418c0(fb, wg->f00, 1.0f);
        return 1;
    }
    if (dc == 0) {
        return 0;
    }
    fb = GetDrawCtx_15de80();
    e1 = DrawEnvGetWidth_1451e0(fb);
    e2 = DrawEnvGetHeight_1451d0(fb);
    GsPktOpenPrim_13f730(dc, 6);
    GsPktWriteAD_13ec80(dc, 0x40, ((s64)(e1 - 1) << 16) | ((s64)(e2 - 1) << 48));
    GsPktClose_13f5b0(dc);
    return 1;
}
