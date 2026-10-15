/* === SESSION 95 (2026-09-23): 4 -> MATCH at exact 325 words.  ONE EDIT:
 * normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080's prototype takes `s32 d` (was s16), so arg 4
 * (src->f012) is loaded into a TEMP in the call emitter's second phase instead
 * of lazily in its third.  WHY IT WORKS (build/wf-normal/s95/sch.py, a gdb
 * trace of mwcc's list scheduler, FUN_004c07e0/FUN_004c0a00): the PRE-RA
 * scheduler runs in register-PRESSURE mode (pick = min pressure score, ties to
 * the EARLIER node; score 16, last use -(1+k), new live def +k).  Cycle 0 took
 * `move a2,v0` (15) and then n2's sll (17, first in list), so n2's narrowing was
 * ready at cycle 1 and beat (s16)b on list order.  With the temp load in the
 * list AHEAD of the sll it takes cycle 0's second slot, the sll slips to cycle
 * 1, and (s16)b's narrowing goes first -- the post-RA scheduler keeps that
 * order (its ties also go to the earlier node).  Every spelling that loads arg
 * 4 through a conversion is the same object (22 arms, deck s95/a8.py).
 * Nulls this session (all byte-identical): 12 heavier arg-7 spellings,
 * prototype x cast on args 5/7, bb copies at 9 positions, copies of src/o/id3
 * via inline assignment, n2 merged with id/t/id2/k3 (webs are split), inline
 * helpers and comma/ternary forms (6 bad, one object). */
/* === SESSION 94 (2026-09-23): 180 -> 4 BAD at exact 325 words.  NOT MERGED.
 * Eight edits (build/wf-normal/s94 h1..h12), each read off an aligned diff
 * or the allocator dump:
 *  1. the tail's three INLINE ASSIGNMENTS -- `normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080(o,
 *     id3 = q + 0x2E, ...)`, `(s16)(n2 = i * 2)`, `(s16)(n3 = n2 + 1)` --
 *     retail CSEs q+0x2E and n2+1 into callee-saved $22/$18 across the calls
 *     (180 -> 142); then `id3 = q + 0x2E;` as its own statement BEFORE the
 *     first call (its `addiu` fills the 3C85D0 delay slot; 14 -> 13).
 *  2. `k3 = i * 3;` BEFORE `ob = func_3C2FB0(...)` -- retail computes it into
 *     $22 first and does NOT CSE it into the i*52 chain (+2 words alone).
 *  3. the +2's partner: the inner-else `measure` block spelled on ONE fresh
 *     chain -- `o->f02C[(u32)i]` on the store AND both w loads -- and the
 *     outer-else w on `o->f02C[(s32)i].f028 / o->f02C[i].f02C` (142 -> 119).
 *  4. `Obj *ob;` DECLARED AFTER `i` -- the s93 vreg-index lever; srch.py
 *     (single index/cost moves replayed against retail's map) named it at
 *     12/15 webs; the whole callee-saved map then goes retail's (119 -> 24).
 *     s93's "ob's position is INERT (optimistic spill)" was true at s93's coat;
 *     edits 1-3 moved ob into simplify, where the index decides.
 *  5. `func_3C85D0(Scr *a, s32 b, ...)` -- an s32 second parameter, so the
 *     `lh` of src->f010 is created before ctx->f018's `lw` (24 -> 14).
 *  6. `pk = (const s16 *)(s32)&D_00526170[(u32)j * 3];` BEFORE the j-loop
 *     guard, guard spelled `nd->f02C == pk[0]` (13 -> 4).
 * RESIDUE (4 words, 271/272/274/275): the first ee080 call's two narrowings
 * `dsll32/dsra32 $10,$23` ((s16)b) and `$8,$17` ((s16)n2) are TRANSPOSED --
 * the [[levers.d/argument-setup-order-class]].  Armed nulls, all byte-identical
 * or worse: implicit vs explicit narrowing on all four args (16 arms, ONE
 * object); n2/n3/id3 declaration position (21 arms, ONE object); n2 as a
 * statement at seven positions; the 3C85D0 result hoisted into `en`; a named
 * `bs = (s16)b` (s16/s32, pre/post, inline); n2 left to CSE (23 arms);
 * `s16 b` parameter (259).  `pre.py` shows our scheduler INPUT has n2's
 * narrowing first; the second call has the same input order and matches.
 * Everything below predates this session. */
/* === SESSION 93 (2026-09-22): STILL 180 BAD.  The {ctx, k3, ob} three-cycle
 * this file has carried is now stated in the allocator's own terms, and HALF
 * of it is reachable.
 *
 * THE WEBS (s93/irf.py + ral0.py on ra/u370.raf.json):
 *     32 = o (s0)   33 = b (s7)   35 = ob (s6)   39 = e   49 = lift (s8)
 *     50 = i (s5)   62 = ctx (s4, a PROMOTED call-result temp)
 *     79 = k3 (s3, a PROMOTED temp -- `s32 k3` never reaches the allocator)
 *     84 (s2)   92 = id2 (s1, also promoted)
 * Select order ours [32, 92, 84, 79, 62, 50, 35, 33, 49]; retail needs
 * [32, ?, ?, ctx, ob, i, k3, b, lift], i.e. REMOVAL k3, i, ob, ctx where we
 * remove ob, i, ctx, k3.
 *  - `k3` IS reachable: `u8 *k3 = (u8 *)(i * 3)` with `(s32)k3 + 0x15/0x16/
 *    0x17` is a NEW OBJECT at 185 (d639512e), so the s93 promotion lever fires
 *    here -- but k3 is STILL a temp (80) in the arm's dump, so the pointer
 *    cast of an integer EXPRESSION is weaker than the cast of a CALL RESULT.
 *  - `ob`'s DECLARATION POSITION IS INERT: declared after `i`, and declared
 *    last of all, are both BYTE-IDENTICAL to base (afafbc2c) -- because ob is
 *    removed by OPTIMISTIC SPILL (pass -1), where the pick is min(cost/degree)
 *    and the index is only a tie-break.  Moving ob therefore needs s91's
 *    SPILL-COST lever ([[levers.d/mwcc-spill-cost-reference-count]]:
 *    cost(ob)=4, deg 66; the other spill candidates are b 3/106, lift 3/102,
 *    148 2/47), NOT a declaration.
 *  - `ctx = func_1FEDE0(); ctx = (Ctx *)(s32)ctx;` is LIVE (210, c45406a1) and
 *    worse alone; `u8 *id2` is byte-identical to whatever it is crossed with.
 * ==> the next arm is the CROSS: k3 un-promoted AND cost(ob) raised so ob
 * leaves the spill set, with ob declared after `i`.  Deck s93/{ga,gb}.py.
 * Everything below predates this session. */
/* === SESSION 87 (2026-09-22): STILL 180 BAD.  s87/e1.py ran the whole
 * 68-name boolean `opt_*` table spelled `off` -- this unit had NO pragma
 * sweep on record.  Armed both ways.  Four live columns, none better:
 * opt_dead_assignments 181 at exact length (a new cross half), common_subs
 * +57 w, loop_invariants +3, propagation +3.  The pragma-ALONE column is
 * closed on this unit.  Everything below predates this session. */
/* === SESSION 83 (2026-09-21, SOLO): 293 -> 180 BAD, exact 325 words, and the
 * FRAME IS NOW RETAIL'S 160 (was 176).  Five installs, all of them arms a
 * previous session had priced and rejected ON A DIFFERENT COAT
 * ([[levers.d/reprice-retired-units]]).  Decks build/wf-normal/s83/b1..b3,
 * c1, c2, d1, e1, e2, f1, f2, g1..g4; record build/wf-normal/s83/HANDOFF.md.
 *
 * WHAT WENT IN, in the order it was measured:
 *  1. 293 -> (-1 w)  DROP the `(s32)i` cast on the ob->measure STORE.  That
 *     one cast was holding i*52 in TWO callee-saved registers at once (s3
 *     def@53 and s7 def@98, both live over 98..148), which is the TENTH
 *     long-lived value that pushed `lift` onto the stack at 0xA0(sp).
 *     Dropping it takes sp-locals 3 -> 0 for one word.
 *     -- THE SCREEN: read `fr.py`'s sp-locals column, not `bad`.  Four of the
 *     seven cast subsets free the register; only this one costs a single word.
 *  2. +1 w   `Scr *scr = ctx->f018;` used at the func_3C2010(#2)/func_3C1C20
 *     PAIR ONLY (#1 keeps `ctx->f018` inline).  Retail loads the member ONCE
 *     into a callee-saved register and copies it into $4 TWICE
 *     (`lw $17,0x18($19)` / `daddu $4,$17,$0` x2); we re-read it, because a
 *     CALL is a barrier for that load, so retail cannot have written the
 *     member three times.  325 w, 249 bad.  `scr` used EVERYWHERE is +2 and
 *     re-spills `lift` -- the site list is load-bearing.
 *  3. 249 -> 247  `D_00526170[(u32)j * 3]` in the j-loop GUARD (+2) crossed
 *     with `(s32)i` on BOTH operands of the else-branch divide (-2).  The
 *     +2 half is what takes the frame 176 -> 160: it frees a SECOND register.
 *  4. 247 -> 182  `ob = func_3C2FB0(...)` moved ABOVE `k3 = i * 3;` (-2 w,
 *     dist 211 -> 182) crossed with the `p->f020` store DUPLICATED into both
 *     arms of the en-guard (+2 w) instead of the shared `p->f020 = (s16)t;`.
 *     Retail emits `sh $2,0x20($17)` TWICE, once in a `b` delay slot
 *     ([[levers.d/mwcc-branch-likely-duplication]]).
 *  5. 182 -> 180  drop the `(s32)i` on the f02C GUARD and on the else
 *     branch's NUMERATOR (keep it on the denominator).  All 11 cast subsets
 *     re-priced at this coat: `n_GE1` is the only exact-length winner.
 *
 * THE MAP IS NOW MOSTLY RETAIL'S (build/wf-normal/s83/webs.py):
 *   s0=o  s1=scr/t/id2/e  s2=idx/j/...  s5=i  s7=b  s8=lift   all EXACT.
 *   The residue is a THREE-CYCLE over {ctx, k3, ob}:
 *       retail  ctx=s3  ob=s4  k3=s6
 *       ours    k3=s3   ctx=s4 ob=s6
 * ARMED NULLS at the 180/182 coat -- do not re-run:
 *  * `k3` spelled `i+i+i` / `3*i` / `(s32)((u32)i*3)` is ONE object with
 *    `i*3` (mwcc canonicalises); `(i<<1)+i` and `i*2+i` are a second object
 *    at 281 bad.  The k3-vs-index CSE is NOT breakable by spelling.
 *  * k3/ob/id2/func_291250 statement permutations (7 cells): `k3` first is
 *    +2 w, `id2` early is 195, `ob` after the first func_291250 is 182 with
 *    dist 186.  Nothing under 180.
 *  * `scr` given an identity cast, assigned twice, or moved above the
 *    `o->f00C` store; `o` copied through a second name; the `ctx == 0` guard
 *    flattened to an early return -- ALL BYTE-IDENTICAL.
 *  * `(u32)j*3` on `pk` as well as the guard is the SAME object as the guard
 *    alone at this coat.
 * NEXT: the {ctx,k3,ob} three-cycle, and the words 272-307 reorder that adiff
 * still shows around the two normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080 calls.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* === SESSION 73 (2026-09-21, SOLO): EXACT LENGTH FOR THE FIRST TIME --
 * 0x508 (3 short) -> 325 words / 0x514, 293 bad.  INSTALLED: s49's arm 3, the
 * named re-derived base pointer in the j-loop body
 *   `pk = (const s16 *)(s32)&D_00526170[j * 3];` + `pk[1]` / `pk[2]`
 * which splits the `D_00526170` CSE the relocation screen has been naming
 * since s49 (`build/wf-normal/s49/relscan.py`: retail 2 refs -> ours 1).
 * âš  s49 priced this arm at +2 OVER a 1-word deficit and retired it; the
 * deficit is now 3, so it lands EXACTLY.  [[levers.d/reprice-retired-units]] --
 * re-price every arm a previous session rejected on length.
 * âš âš  BE CLEAR ABOUT WHAT THIS BOUGHT: the alignment distance is 200 -> 201,
 * i.e. UNCHANGED (build/wf-normal/s73/b6.py).  The value is that the unit is
 * now `bad`-scoreable at all -- every later edit can be measured in words
 * instead of in length.  Do not read 293 as a regression; it is the first
 * score this unit has ever had.
 *
 * READ OF THE OBJECT (build/wf-normal/s73/ed370.sbs, full 325-word sbs):
 *  â˜… FRAME 176 vs RETAIL 160.  Retail has ZERO stack locals -- its whole
 *    160-byte frame is `sd ra` + `sq s0..s8`.  We have exactly ONE, `lift` at
 *    0x A0(sp) (3 accesses: `sw zero` / `sw v1` / `lw v1`), so we carry TEN
 *    long-lived values where retail carries NINE.
 *      retail  o=$s0 ?=$s1 e/j=$s2 ctx=$s3 ob=$s4 i=$s5 k3=$s6 b=$s7 lift=$s8
 *      ours    ob=$s0 o=$s1 e=$s2 ?=$s3 ctx=$s4 i=$s5 k3=$s6 ?=$s7 b=$s8
 *  â˜… RETAIL'S `(o->f00C - 1) < i` GUARD IS A BRANCH-LIKELY: `beqzl at,0x304`
 *    with the next statement's `sll a0,s2,0x1` in the ANNULLED slot, then
 *    `li s8,126`.  Ours is `beqz` + a wasted `nop`.  See
 *    [[levers.d/mwcc-branch-likely-duplication]] -- this is the next edit.
 *  â˜… retail RECOMPUTES the j-loop address (`sll/addu/sll/addu` from `j`) in the
 *    body; we hold a scaled index in a callee-saved register.
 *
 * MEASURED NULLS THIS SESSION -- do not re-run:
 *  - THE PER-BLOCK INTEGER-ADDRESS FORM IS THE WRONG DIRECTION (b1.py).  All
 *    15 non-empty subsets of the four `o->f02C[i]` access blocks rewritten as
 *    `r = (Rec *)((s32)o->f02C + (u32)i * 0x34)` are SHORTER, 0x4ac..0x508 --
 *    a named block pointer CSEs the address ONCE where retail recomputes it.
 *    s71's note "rewrite the o->f02C accesses per 004ec220's s71 form" is
 *    hereby RETRACTED for this unit.
 *  - ADDING AN INDEX CAST BUYS NOTHING (b2.py): `(u32)i` / `(s32)i` at each of
 *    the 10 currently-bare `o->f02C[i]` occurrences = 20 cells, every one
 *    length-neutral or SHORTER (0x4f4..0x508).  Many new objects, so armed.
 *  - FREEING A REGISTER BY INLINING A NAMED VALUE IS A NULL (b4.py): k3, id2,
 *    t, id, n2 each inlined, and `lift` declared first / last -- the frame is
 *    -176 in all eight cells and decl order is inert for `lift`.
 *  - BREAKING THE j*3 CSE DOES NOT FREE THE REGISTER (b5.py): 11 spellings of
 *    `pk` / the guard index ((u32)j, (u32)(j*3), j+j+j, byte arithmetic, the
 *    plain `&`) -- every CSE-breaking one is +3 words (0x520) and the frame
 *    STAYS -176; the byte-arithmetic forms make it WORSE (-192).
 * NEXT: the `beqzl` on the `(o->f00C - 1) < i` guard, then hunt the tenth
 * long-lived value.  KEEP OUT OF config/ocunits/normal.txt. */
/* === SESSION 71 (2026-09-21, SOLO): read, not advanced (still 0x510, 1 short).
 * The three s31 `(s32)i`/`(u32)i` index casts are PAYING for missing words:
 * removing them is 17 words short but the alignment distance IMPROVES
 * (217 -> 185, build/wf-normal/s71 inline sweep).  Retail's shape, read off the
 * listing: `o->f02C[i]` recomputes i*52 (((i*3)*4+i)*4) at EVERY access block;
 * `o->f008 = q; if (q > 8) o->f008 = 8;` is the store-then-clamp idiom (retail
 * `bnez at` with the `sw` in its slot); D_00526170's %hi/%lo is rematerialised
 * in the j-loop body; `t = -1 / 0x6F` is a beqzl with `li v0,-1` in the slot.
 * INSTALLED: the store-then-clamp and the en != 0 arm first (dist 217 -> 200,
 * now 0x508, three short -- the recompute words are what is missing).
 * Next: rewrite the o->f02C accesses per 004ec220's s71 integer-address form
 * `(Rec *)((s32)o->f02C + (u32)i * 0x34)`, then re-price the casts. */
/* === SESSION 49 (2026-09-08): no move (length 0x510 vs retail 0x514, one word
 * SHORT), but the missing word is NAMED.  build/wf-normal/s49/relscan.py reports
 * `0x00526170 retail 2 -> ours 1`: retail materialises `%hi/%lo(D_00526170)`
 * TWICE inside the j-loop -- once for the `nd->f02C == D_00526170[j*3]` guard
 * and again at .L004ED674 for `[j*3+1]` and `[j*3+2]` -- because the
 * `jal func_290460` between them clobbers the caller-saved register holding it.
 * We materialise it ONCE and park it in a callee-saved register.
 * THREE ARMS TO SPLIT THAT CSE, ALL LONG (target 325 words):
 *   `[(u32)(j*3) + 1]` on the two body uses only        330
 *   `((const s16 *)(s32)D_00526170)[...]` on both       329
 *   a `const s16 *pk = (const s16 *)(s32)&D_00526170[j*3];` local  327
 * So the split is reachable but every spelling costs +3..+6 where retail's
 * costs +1; the callee-saved register we free is not being given back.
 * Everything below predates this. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `I_u32_L445_7_idx` from the index-cast deck.
 *   before: 316 words, ? bad   after: 322 words, ? bad   (retail 325 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `I_s32_L439_4_idx` from the index-cast deck (mkidx31.py)
 *   before: 307 words, ? bad   after: 316 words, ? bad   (retail 325 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x004ED370 -- 1312 B.  Written FRESH in s31 (lane a4).
 * Sibling of the merged normal_MenuBattleEndOpen_4ec990.cpp: same Scene/Rec/Src/Obj
 * shapes, reused verbatim from that byte-identical unit.
 *
 * `lw $25,0($20) / lw $25,0x444($25) / jalr $25` is a C++ virtual call --
 * vptr at offset 0, slot 0x444 = index (0x444-8)/4 = 271.  Hence .cpp.
 */
struct Obj {
    virtual void s000();
    virtual void s001();
    virtual void s002();
    virtual void s003();
    virtual void s004();
    virtual void s005();
    virtual void s006();
    virtual void s007();
    virtual void s008();
    virtual void s009();
    virtual void s010();
    virtual void s011();
    virtual void s012();
    virtual void s013();
    virtual void s014();
    virtual void s015();
    virtual void s016();
    virtual void s017();
    virtual void s018();
    virtual void s019();
    virtual void s020();
    virtual void s021();
    virtual void s022();
    virtual void s023();
    virtual void s024();
    virtual void s025();
    virtual void s026();
    virtual void s027();
    virtual void s028();
    virtual void s029();
    virtual void s030();
    virtual void s031();
    virtual void s032();
    virtual void s033();
    virtual void s034();
    virtual void s035();
    virtual void s036();
    virtual void s037();
    virtual void s038();
    virtual void s039();
    virtual void s040();
    virtual void s041();
    virtual void s042();
    virtual void s043();
    virtual void s044();
    virtual void s045();
    virtual void s046();
    virtual void s047();
    virtual void s048();
    virtual void s049();
    virtual void s050();
    virtual void s051();
    virtual void s052();
    virtual void s053();
    virtual void s054();
    virtual void s055();
    virtual void s056();
    virtual void s057();
    virtual void s058();
    virtual void s059();
    virtual void s060();
    virtual void s061();
    virtual void s062();
    virtual void s063();
    virtual void s064();
    virtual void s065();
    virtual void s066();
    virtual void s067();
    virtual void s068();
    virtual void s069();
    virtual void s070();
    virtual void s071();
    virtual void s072();
    virtual void s073();
    virtual void s074();
    virtual void s075();
    virtual void s076();
    virtual void s077();
    virtual void s078();
    virtual void s079();
    virtual void s080();
    virtual void s081();
    virtual void s082();
    virtual void s083();
    virtual void s084();
    virtual void s085();
    virtual void s086();
    virtual void s087();
    virtual void s088();
    virtual void s089();
    virtual void s090();
    virtual void s091();
    virtual void s092();
    virtual void s093();
    virtual void s094();
    virtual void s095();
    virtual void s096();
    virtual void s097();
    virtual void s098();
    virtual void s099();
    virtual void s100();
    virtual void s101();
    virtual void s102();
    virtual void s103();
    virtual void s104();
    virtual void s105();
    virtual void s106();
    virtual void s107();
    virtual void s108();
    virtual void s109();
    virtual void s110();
    virtual void s111();
    virtual void s112();
    virtual void s113();
    virtual void s114();
    virtual void s115();
    virtual void s116();
    virtual void s117();
    virtual void s118();
    virtual void s119();
    virtual void s120();
    virtual void s121();
    virtual void s122();
    virtual void s123();
    virtual void s124();
    virtual void s125();
    virtual void s126();
    virtual void s127();
    virtual void s128();
    virtual void s129();
    virtual void s130();
    virtual void s131();
    virtual void s132();
    virtual void s133();
    virtual void s134();
    virtual void s135();
    virtual void s136();
    virtual void s137();
    virtual void s138();
    virtual void s139();
    virtual void s140();
    virtual void s141();
    virtual void s142();
    virtual void s143();
    virtual void s144();
    virtual void s145();
    virtual void s146();
    virtual void s147();
    virtual void s148();
    virtual void s149();
    virtual void s150();
    virtual void s151();
    virtual void s152();
    virtual void s153();
    virtual void s154();
    virtual void s155();
    virtual void s156();
    virtual void s157();
    virtual void s158();
    virtual void s159();
    virtual void s160();
    virtual void s161();
    virtual void s162();
    virtual void s163();
    virtual void s164();
    virtual void s165();
    virtual void s166();
    virtual void s167();
    virtual void s168();
    virtual void s169();
    virtual void s170();
    virtual void s171();
    virtual void s172();
    virtual void s173();
    virtual void s174();
    virtual void s175();
    virtual void s176();
    virtual void s177();
    virtual void s178();
    virtual void s179();
    virtual void s180();
    virtual void s181();
    virtual void s182();
    virtual void s183();
    virtual void s184();
    virtual void s185();
    virtual void s186();
    virtual void s187();
    virtual void s188();
    virtual void s189();
    virtual void s190();
    virtual void s191();
    virtual void s192();
    virtual void s193();
    virtual void s194();
    virtual void s195();
    virtual void s196();
    virtual void s197();
    virtual void s198();
    virtual void s199();
    virtual void s200();
    virtual void s201();
    virtual void s202();
    virtual void s203();
    virtual void s204();
    virtual void s205();
    virtual void s206();
    virtual void s207();
    virtual void s208();
    virtual void s209();
    virtual void s210();
    virtual void s211();
    virtual void s212();
    virtual void s213();
    virtual void s214();
    virtual void s215();
    virtual void s216();
    virtual void s217();
    virtual void s218();
    virtual void s219();
    virtual void s220();
    virtual void s221();
    virtual void s222();
    virtual void s223();
    virtual void s224();
    virtual void s225();
    virtual void s226();
    virtual void s227();
    virtual void s228();
    virtual void s229();
    virtual void s230();
    virtual void s231();
    virtual void s232();
    virtual void s233();
    virtual void s234();
    virtual void s235();
    virtual void s236();
    virtual void s237();
    virtual void s238();
    virtual void s239();
    virtual void s240();
    virtual void s241();
    virtual void s242();
    virtual void s243();
    virtual void s244();
    virtual void s245();
    virtual void s246();
    virtual void s247();
    virtual void s248();
    virtual void s249();
    virtual void s250();
    virtual void s251();
    virtual void s252();
    virtual void s253();
    virtual void s254();
    virtual void s255();
    virtual void s256();
    virtual void s257();
    virtual void s258();
    virtual void s259();
    virtual void s260();
    virtual void s261();
    virtual void s262();
    virtual void s263();
    virtual void s264();
    virtual void s265();
    virtual void s266();
    virtual void s267();
    virtual void s268();
    virtual void s269();
    virtual void s270();
    virtual s32 measure(s32 a);
};

typedef struct Rec {
    s32 f000;
    s32 f004;
    s32 f008;
    s32 f00C;
    s32 f010;
    s32 f014;
    s16 f018;
    u8  pad01A[6];
    s32 f020;
    s32 f024;
    f32 f028;
    f32 f02C;
    f32 f030;
} Rec;

typedef struct Src {
    s16 f000;
    s16 f002;
    s16 f004;
    s16 f006;
    s32 f008;
    s32 f00C;
    s16 f010;
    s16 f012;
    s16 f014;
    s16 f016;
} Src;

typedef struct Slot {
    f32 f000;
    f32 f004;
    s16 f008;
    u8  pad00A[2];
} Slot;

typedef struct Scene {
    s32   f000;
    s32   f004;
    s32   f008;
    s32   f00C;
    u8    pad010[4];
    u8    f014[0x18];
    Rec  *f02C;
    Slot  f030[9];
    u8    f09C[0x10];
    u8    f0AC[0x40];
    void *f0EC;
    s8    f0F0[9];
    s8    f0F9[9];
    s16   f102;
    u8    pad104[2];
    s16   f106;
    void *f108;
    s16   f10C;
    s16   f10E;
    u8    pad110[1];
    u8    f111;
    u8    f112;
    u8    f113;
    u8    f114;
} Scene;

typedef struct Elem {
    s16 f000;
    s16 f002;
    u8  pad004[4];
    s16 f008;
    s16 f00A;
    u8  pad00C[0x14];
    s16 f020;
    u8  pad022[0x42];
    s16 f064;
    u8  pad066[6];
    s16 f06C;
} Elem;

typedef struct Handle { u8 pad000[0x20]; Elem *f020; } Handle;

typedef struct Node { u8 pad000[0x2C]; s16 f02C; } Node;

typedef struct Ent { u8 pad000[0x10]; Node *f010; } Ent;

typedef struct Scr { u8 pad000[0x30]; s16 f030; } Scr;

typedef struct Stage { u8 pad000[0x238]; void *f238; } Stage;

typedef struct Ctx {
    u8     pad000[0x14];
    void  *f014;
    Scr   *f018;
    u8     pad01C[4];
    Stage *f020;
} Ctx;

extern "C" const s16 D_00526170[];

extern "C" Ctx  *func_1FEDE0(void);
extern "C" s32   func_3C2010(Scr *a, s32 b, s32 c);
extern "C" s32   func_3C1C20(Scr *a, s32 b, s32 c);
extern "C" Obj  *func_3C2FB0(Scr *a, s32 i);
extern "C" s32   func_13ADE0(f32 v);
extern "C" void  func_291250(void *a, u16 id, s32 c, s32 d);
extern "C" Elem *func_28FE10(void *a, u16 id, s32 c);
extern "C" Node *func_3AE3E0(Obj *a);
extern "C" Handle *func_290460(void *a, u16 id);
extern "C" void  func_290010(void *a, u16 id, s32 c, s32 d);
extern "C" Src  *func_3A2040(Stage *a, s32 i);
extern "C" Ent  *func_3C85D0(Scr *a, s32 b, s32 c, s32 d);
extern "C" void  func_288E50(void *a, s16 b, s32 c, s32 d);
extern "C" void  normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080(Scene *o, s32 id, Ent *e, s32 d, s16 n, s32 f, s16 g);
extern "C" void  normal_MenuBattleEndWeaponGaugeUpdateMaybe_4ed890(Scene *o, s32 id, s16 n, s32 c);

extern "C" void normal_MenuBattleEndMemberRowsRefreshMaybe_4ed370(Scene *o, s32 b);

void normal_MenuBattleEndMemberRowsRefreshMaybe_4ed370(Scene *o, s32 b) {
    Ctx *ctx;
    Node *nd;
    Src *src;
    Ent *en;
    Elem *e;
    Elem *p;
    Handle *h;
    Scr *scr;
    s32 k3;
    s32 id2;
    s32 q;
    s32 id;
    s32 n2;
    s32 t;
    s32 lift;
    s32 i;
    Obj *ob;
    s32 j;
    s16 w;
    const s16 *pk;
    s32 id3;
    s32 n3;

    ctx = func_1FEDE0();
    if (ctx != 0) {
        o->f00C = func_3C2010(ctx->f018, 1, 1);
        scr = ctx->f018;
        t = func_3C2010(scr, 1, 1);
        q = t + func_3C1C20(scr, 1, 1);
        o->f008 = q;
        if (q > 8) {
            o->f008 = 8;
        }
        lift = 0;
        for (i = 0; i < o->f008; i = i + 1) {
            k3 = i * 3;
            ob = func_3C2FB0(ctx->f018, i);
            func_291250(o->f014, k3 + 0x17, 0, o->f02C[i].f020);
            id2 = k3 + 0x15;
            func_291250(o->f014, id2, 0, func_13ADE0(o->f02C[i].f028));
            func_291250(o->f014, id2, 1, func_13ADE0(o->f02C[i].f02C));
            func_291250(o->f014, id2, 2, o->f02C[i].f004);
            e = func_28FE10(o->f014, id2, 0);
            if (e != 0) {
                e->f06C = 0x14;
                if (o->f02C[i].f02C == 0.0f) {
                    if (o->f02C[i].f028 == 0.0f) {
                        e->f06C = 0;
                        e->f064 = 0;
                    } else {
                        o->f02C[(u32)i].f02C = (f32)ob->measure(o->f02C[i].f020 - 1);
                        w = (s16)(116.0f * (o->f02C[(u32)i].f028 / o->f02C[(u32)i].f02C));
                        e->f064 = w;
                        if (w == 0) {
                            e->f06C = 0;
                        }
                    }
                } else {
                    w = (s16)(116.0f * (o->f02C[(s32)i].f028 / o->f02C[i].f02C));
                    e->f064 = w;
                    if (w == 0) {
                        e->f06C = 0;
                    }
                }
                nd = func_3AE3E0(ob);
                for (j = 0; j < 10; j = j + 1) {
                    pk = (const s16 *)(s32)&D_00526170[(u32)j * 3];
                    if (nd->f02C == pk[0]) {
                        h = func_290460(o->f014, k3 + 0x16);
                        if (h != 0) {
                            e = h->f020;
                        }
                        e->f000 = 1;
                        e->f002 = 1;
                        if ((o->f00C - 1) < i) {
                            lift = 0x7E;
                        }
                        pk = (const s16 *)(s32)&D_00526170[j * 3];
                        e->f008 = (s16)(lift + pk[1]);
                        e->f00A = pk[2];
                    }
                }
            }
            if (i < o->f00C) {
                q = i * 4;
                id = q + 0x2D;
                func_290010(o->f014, id, 1, -1);
                src = func_3A2040(ctx->f020, i);
                if (src != 0) {
                    h = func_290460(o->f014, id);
                    if (h != 0) {
                        p = h->f020;
                        if (p != 0) {
                            en = func_3C85D0(ctx->f018, src->f010, 0, 0);
                            if (en != 0) {
                                func_288E50(p, en->f010->f02C, 0x20, 0x26);
                                p->f000 = 0;
                            }
                            en = func_3C85D0(ctx->f018, src->f014, 0, 0);
                            if (en != 0) {
                                func_288E50((u8 *)p + 0x20, en->f010->f02C, 0x20, 0x26);
                                p->f020 = (s16)0x6F;
                            } else {
                                p->f020 = (s16)-1;
                            }
                        }
                    }
                    id3 = q + 0x2E;
                    normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080(o, id3,
                                        func_3C85D0(ctx->f018, src->f010, 0, 0),
                                        src->f012, (s16)(n2 = i * 2), 0, (s16)b);
                    normal_MenuBattleEndWeaponSlotSetupMaybe_4ee080(o, id3,
                                        func_3C85D0(ctx->f018, src->f014, 0, 0),
                                        src->f016, (s16)(n3 = n2 + 1), 1, (s16)b);
                    normal_MenuBattleEndWeaponGaugeUpdateMaybe_4ed890(o, q + 0x2F, (s16)n2, 0);
                    normal_MenuBattleEndWeaponGaugeUpdateMaybe_4ed890(o, q + 0x30, (s16)n3, 1);
                }
            }
        }
    }
}
