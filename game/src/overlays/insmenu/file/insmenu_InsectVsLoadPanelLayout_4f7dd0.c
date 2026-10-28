/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsLoadPanelLayout_4f7dd0 1
#include "port/game_protos.h"
#line 1
/* SESSION 14 (2026-08-27, lane iv33 Convert, with analysis lanes im39/im40/iv32).
 * ===================== CLOSED.  324 WORDS / 0 BAD. =====================
 * BYTE-IDENTICAL.  .text sha1 4bc03365.  Scored by
 *     rm -rf build/obj-iv33
 *     python build/dv_osbuild.py insmenu --tag iv33 insmenu_InsectVsLoadPanelLayout_4f7dd0 --verbose
 *   -> `insmenu_InsectVsLoadPanelLayout_4f7dd0   324  MATCH   1/1 byte-identical`
 * SAME-SESSION CALIBRATOR, same tag, same scorer, run FIRST: the previous
 * draft of this file scored 324 words / 12 bad at exactly 0x004F8144 8154 8164
 * 8168 8174 8178 8184 8188 8198 81B4 81D4 81F4 (.text sha1 690de226).  The
 * round is armed in both directions.  The winning object differs from that one
 * at EXACTLY those 12 words and nowhere else, and all 12 now equal retail.
 * This unit was the LAST open function in INSMENU.BIN; it closes the overlay at
 * 365/365 count and 61,152/61,152 bytes.
 *
 * 1. THE FIX IS SIX TOKENS ACROSS TWO HUNKS, AND IT IS A CROSS OF TWO LEVERS
 *    THAT ARE EACH A NEGATIVE ON THEIR OWN.  That is why thirteen prior rounds
 *    (800+ arms) missed it: every one of them swept ONE axis at a time.
 *
 *    LEVER 1 -- mwcc hands the caller-saved run $8,$7,$6,$5 to the function's
 *    loop-resident / loop-crossing locals IN SOURCE DECLARATION ORDER.
 *    Declaration order must therefore be key, then ws, then wd (k follows).
 *
 *    LEVER 2 -- A LONG-LIVED SCALAR ONLY ENTERS THAT RANKING IF THE COMPARE
 *    THAT CONSUMES IT CARRIES A CONVERSION NODE.  With a plain signed
 *    `tbl[n].id == key` compare, `key` is demoted below every cursor and its
 *    declaration slot goes completely inert -- which is precisely why the
 *    recorded verdict in section 5/R3 below ("all 13 declaration slots for
 *    `key`, ALL inert") was a TRUE measurement of the WRONG CELL.
 *
 *    LEVER 3 (independent, and it is what made every prior unsigned arm look
 *    catastrophic) -- `r` MUST BE DECLARED BEFORE `n`.  With levers 1+2 in
 *    place but `r` left after `n`, the low pool rotates whole (ours
 *    k=$4 w0=$3 w1=$2 r=$5 against retail k=$5 w0=$4 w1=$3 r=$2) and the score
 *    is 44 bad.  Moving one declaration cures all 44.  The boundary is sharp
 *    and measured on both sides: r immediately BEFORE n = 0 bad, r immediately
 *    AFTER n = 44 bad.
 *
 *    ISOLATION, measured: right declaration order + fully signed compare = 15
 *    bad; unsigned compare + r left after n = 44 bad; parked order + unsigned
 *    = 46 bad; all three together = 0 bad.  Cast alone and order alone are
 *    both WORSE THAN THE 12 THIS FILE SAT AT.
 *
 * 2. THE SIX EDITS, against the 12-bad draft:
 *      (1) struct Ent: `s32 id;`            -> `u32 id;`
 *      (2) `s32 key;` moved to be the FIRST declaration after the two arrays
 *      (3) `const s32 *ws;` declared BEFORE `s32 *wd;`
 *      (4) `s16 r;` moved up so it is declared before `s32 e;` and `s32 n;`
 *      (5) `while (tbl[n].id != -1)`        -> `!= 0xFFFFFFFF`
 *      (6) `if (tbl[n].id == key)`          -> `== (u32)key`
 *    Everything else -- both pragmas, the twice-read `tbl[n].id`, `s16 r`,
 *    `s32 key`, `r = 0;` before the word-copy loop, the explicit cursor copy
 *    loops -- is UNCHANGED and all of it is still load-bearing (section 5).
 *
 * 3. THE TRIGGER IS THE CONVERSION NODE AT THE `if`, NOT SIGNEDNESS AND NOT
 *    THE VARIABLE TYPE.  All of these emit the identical object 4bc03365:
 *    `u32 id` + `0xFFFFFFFF` + `== (u32)key`; `s32 id` + `!= -1` + `== (u32)key`;
 *    `u32 id` + `0xFFFFFFFF` + `== key` (implicit conversion); and even a fully
 *    SIGNED source with a NO-OP `(s32)key` cast at the search compare.  But
 *    making `key` ITSELF u32, so there is no conversion node at all, reverts to
 *    15 bad.  The site matters too: unsigning only the `while` sentinel test
 *    leaves 15 bad -- the load-bearing site is the `if`.
 *
 * 4. THE EXEMPLAR EXISTS: src/wf/insmenu/insmenu_InsectVsSaveScreenClose_4f7990.c, which closed
 *    hours before this one.  Same shape (scalar loaded from
 *    ctx->field1188->field08, two-cursor copy loop, search of the copied table
 *    against that scalar) and register-for-register the same allocation --
 *    read its retail listing at 0x004F7A10-0x004F7A94: kind=$8, src=$7, dst=$6,
 *    n=$5, and its C declares those four consecutively in exactly that order.
 *    ** SECTION 3 OF THE SESSION-13 BLOCK BELOW ("THERE IS NO EXEMPLAR", and
 *    the generalisation "a void() function has no pre-coloured value, so the
 *    shape has no reachable source template anywhere in the tree") IS REFUTED. **
 *    It was true when written only because 004f7990 was still parked.
 *
 * 5. RE-ARMED AT THE NEW FLOOR -- do not remove any of these:
 *      drop `#pragma opt_pulloutconstants off`  ->   9 bad
 *      drop `#pragma opt_dead_assignments off`  -> 323 words (one short)
 *      `s32 r` instead of `s16 r`               -> 322 words
 *      `s16 key` instead of `s32 key`           -> 328 words
 *
 * 6. RETRACTIONS.  Four recorded claims in the blocks below are now FALSE:
 *    * SESSION 13 section 2: "RETAIL'S (6,7,8) IS RANK 2 AND NOTHING REACHES
 *      IT" -- reached, by many arms.  The lattice was complete only over
 *      SIGNED-compare sources.
 *    * SESSION 13 section 2: "the rank-1 / unsigned arms cost 44-46 bad words,
 *      so they are a MECHANISM PROBE, not a candidate" -- those 44 words are
 *      entirely `r`s declaration slot and one move cures them.
 *    * SESSION 13 section 3: "THERE IS NO EXEMPLAR" -- see section 4 above.
 *    * SESSION 13 section 6 and SESSION 12 sections 5/6: "declaration order of
 *      anything" and "key's type/signedness/width" are BOTH on the
 *      do-not-re-grind list.  The fix is precisely the CROSS of those two
 *      axes, and no round ever crossed them.  ** A whole-population
 *      "declaration order is inert here" reading is the TELL that the scalar
 *      has been GATED OUT of the ranking, not that the axis is dead. **
 *
 * 7. MEASURED INERT AT THE WINNING STATE (do not re-grind): `r` may sit
 *    anywhere before `n`; `key` may sit before `tbl`; all 24 permutations of
 *    {k,w0,w1,r} inside the low block are ONE .text image; `n++` vs `n = n+1`;
 *    `i++` vs `i = i+1`; `k -= 1;` at the loop top vs `--k` in the test;
 *    `(u32)-1` vs `0xFFFFFFFF`; the compare operand order; deleting the
 *    unused `s32 e;`; casting k, w0 or r.  The 244-pragma knob axis stays
 *    SPENT (build/im14_knob3.log is the one valid sweep; floor unmoved).
 *
 * ADMITTED.  This file is byte-identical and belongs in src/ and in
 * config/ocunits/insmenu.txt.  The sections below are kept for their measured
 * negatives only; where they conflict with this block, this block wins.
 */
/* SESSION 13 (2026-08-27, lane im35).  FLOOR UNMOVED AT 12.  832 objects
 * measured, 676 of them at FULL 324-word fidelity.  Read section 0 first:
 * it is a tool, and it makes every future pass on this unit ~free.
 *
 * 0. ===== THE BIG REPRO: full-unit fidelity at mini-repro cost =====
 *    build/im35_core.c is THIS FILE with the comments stripped.  Compiled by
 *    build/mr_im35.py (a copy of mr_im15.py pointed at ~/rgd/work-im35m) it
 *    produces .text sha1 690de226 -- BYTE-IDENTICAL to the object
 *    build/dv_osbuild.py insmenu --tag im35 emits, and build/im35_score.py
 *    scores it 324 words / 12 bad at exactly words
 *    221,225,229,230,233,234,237,238,242,249,257,265 -- the same twelve
 *    dv_osbuild prints.  So N WHOLE-FUNCTION variants can be scored in ONE
 *    ssh round trip.  200 arms in one trip was comfortable.
 *      build/im35_score.py <dir>   word-for-word vs retail, relocs excluded
 *      build/im35_triple.py <dir>  the (wd, ws, key) register triple per arm
 *      build/im35_dis.py <obj>     disassemble any .o off disk, no ssh
 *    ** A FULL-UNIT ROUND TRIP BUYS NOTHING ON THIS UNIT.  Use the big repro. **
 *
 * 1. THE RESIDUE, exactly.  A 3-cycle of register names, nothing else:
 *      ours wd=$8 ws=$7 key=$6 n=$7   retail wd=$6 ws=$7 key=$8 n=$6
 *      221 0x004F8144  addiu $8,$29,0xB0   | addiu $6,$29,0xB0
 *      225 0x004F8154  lw    $6,0x8($3)    | lw    $8,0x8($3)
 *      229 0x004F8164  sw    $4,0x0($8)    | sw    $4,0x0($6)
 *      230 0x004F8168  sw    $3,0x4($8)    | sw    $3,0x4($6)
 *      233 0x004F8174  addiu $8,$8,0x8     | addiu $6,$6,0x8
 *      234 0x004F8178  daddu $7,$0,$0      | daddu $6,$0,$0
 *      237 0x004F8184  bnel  $6,$4         | bnel  $8,$4
 *      238 0x004F8188  addiu $7,$7,0x1     | addiu $6,$6,0x1
 *      242 0x004F8198  sll   $5,$7,0x3     | sll   $5,$6,0x3
 *      249 0x004F81B4  bnel  $6,$3         | bnel  $8,$3
 *      257 0x004F81D4  bnel  $6,$3         | bnel  $8,$3
 *      265 0x004F81F4  bne   $6,$3         | bne   $8,$3
 *    `n` is derivative: it takes the LOWER of the two cursor registers freed
 *    at the copy loop's exit ($7 for us, $6 for retail).  Only key<->wd is real.
 *
 * 2. THE LATTICE.  Across ~350 structural arms only FOUR triples exist:
 *      (wd,ws,key) = (8,7,6)  base, wd declared first
 *                    (7,8,6)  ws declared first
 *                    (8,6,7)  wd first  + an UNSIGNED search compare
 *                    (6,8,7)  ws first  + an UNSIGNED search compare
 *    So: the {ws,wd} pair fills two slots in REVERSE DECLARATION ORDER, and
 *    `key` takes a slot whose RANK is 0 with a signed compare and 1 with an
 *    unsigned one.  RETAIL'S (6,7,8) IS RANK 2 AND NOTHING REACHES IT.
 *    The rank-1 arms (`u32 id`, or just `tbl[n].id == (u32)key`) also invert
 *    the whole low pool (r/k/w0/w1 go $5/$4/$3/$2) and cost 44-46 bad words,
 *    so they are a MECHANISM PROBE, not a candidate.
 *    ! THIS REFUTES THE OLD HEADER'S "key is pinned" reading: key is NOT
 *    pinned to $6, it is pinned to a RANK, and rank 2 is what is missing.
 *
 * 3. THE PRIMARY MOVE THE PASS WAS GIVEN -- copy an already-MATCHED function
 *    that has retail's allocation -- IS A MEASURED NEGATIVE.  THERE IS NO
 *    EXEMPLAR.  build/im35_scan2.py screens every listing for "a register
 *    modified INSIDE a loop is LOWER-numbered than a register defined before
 *    it, untouched inside it, and used after it".  ARMED: it HITS on retail's
 *    own 004f7dd0 listing (6,8) and MISSES on our object.  Over the 9,504
 *    functions that have a C source it returns FOUR: this unit, its parked
 *    twin insmenu_InsectVsSaveScreenClose_4f7990, and two where the high register is a
 *    FUNCTION PARAMETER (pre-coloured) -- SlotRecordReset_3eeca0 and
 *    AnimKeyEvalQuat_1555b0.  A void() function has no pre-coloured value, so
 *    the shape has no reachable source template anywhere in the tree.
 *    (build/im35_scan.py, the narrower sll/addu/addiu/lw-0 form, returns 19
 *    functions corpus-wide, 3 with sources, same conclusion.)
 *
 * 4. THIS UNIT IS A MEMBER OF A NAMED PROJECT-WIDE CLASS.
 *    src/anim/AnimKeyEvalQuat_1555b0.c calls it "the unfixable symmetric-naming
 *    class" -- 7 words of pure register naming, ELEVEN spellings exactly
 *    inert, "retail's register order is NOT this function's definition order,
 *    whatever else it is" -- and names CameraChaseStep_161b60 and ScriptVmRunEntry_176940 as the
 *    other members.  The ONE member that fell is
 *    src/event/EvCmdEventPlayerCreate_261220.cpp, and its lever was
 *    "THE LEVER WAS NEVER DECLARATION ORDER -- IT WAS THAT THE LOCAL SHOULD
 *    NOT EXIST".  That lever was applied here to EVERY local in the region
 *    (round 12 below) and the floor did not move.
 *
 * 5. NEGATIVES MEASURED THIS SESSION.  Report is arms / INERT / EFFECTIVE
 *    WIDTH (distinct non-base .text images).  Base = 690de226, 12 bad.
 *    * SALVAGE mr-im24, 51 arms, 20 INERT, EW 17.  ** ITS BASE WAS VALIDATED
 *      TO REPRODUCE THE DEFECT ** -- a00_base.c emits wd=$8/key=$6/n=$7, the
 *      same three registers in the same three roles as the full unit.  The
 *      repro was real; it just contains no fix.  0/51 target shape.
 *    * R1 mini, 52 arms: statement position of the key chain (5 positions x
 *      2 decl orders), all 6 statement orders of WS/WD/K, all 6 declaration
 *      orders of {wd,ws,key}, chain split at Handle* , Ctx* , Sub*, 4 copy-loop
 *      spellings, pressure locals, 3 search-loop shapes.  0 hits.
 *      * moving the key chain AFTER ws/wd forces the cursors to CALLEE-SAVED
 *        $17-$19 and grows the function -- that is the old header's 0x514.
 *    * R2 mini, 45 arms, 19 INERT, EW 7: Sub* , Handle* , s32-temp splits x all 6
 *      declaration orders, key sunk past the copy loop, key as pointer, wd/ws
 *      as u32, no-key re-read, low-decl shuffles.  0 hits.
 *    * R3 BIG, 62 arms, 37 INERT, EW 5: all 12 orders of the FOUR cursors,
 *      all 13 declaration slots for `key` x 3 cursor orders (39 arms, ALL
 *      inert -- key's declaration slot is inert in the full unit too), split
 *      counters, merged temps, n/i merged, assignment-order swaps.  0 hits.
 *    * R4 BIG, 26 arms, 19 INERT, EW 3: MERGING the two copy loops onto ONE
 *      cursor pair (s32* with casts, and u8*) is EXACTLY INERT -- 690de226.
 *      So "retail's wd and hd are one variable" is a NULL, not a negative.
 *      The `register` storage class is EXACTLY INERT on key/wd/ws/k/n/r and
 *      on all four cursors -- 12 arms, all 690de226.
 *    * R5 BIG, 200 arms, 136 INERT, EW 10: `#pragma optimization_level N` IS
 *      recognised (0/1/2 -> 424/374/369 words, 4 -> 323, 3 -> 18 bad) and it
 *      does not reach 12; plus all 190 PAIRS of 20 allocation/motion pragmas
 *      on top of dead_off+pull_off -- knob1/2/3 only ever varied ONE at a
 *      time.  Nothing below 12.
 *    * R6, 79 arms, 59 INERT, EW 13.  THE DEF-ORDER AXIS IS DEAD: with the
 *      call replaced by a global load, `key` defined FIRST and `key` defined
 *      LAST emit the SAME OBJECT (91771154).  Allocation order is not
 *      definition order.  Also: the split base and the merged base crossed
 *      with 34 code-motion pragmas -- 58 of 68 inert, floor 12.
 *    * R7 BIG, 20 arms, 6 INERT, EW 12.  THE PRIORITY/LOOP-WEIGHT AXIS IS
 *      DEAD: copy-loop trip counts 2 / 8 / 60 / 240 all leave wd=$8 key=$6
 *      (13 bad each).  Also wd-is-also-n (one integer cursor used as the
 *      search index) INERT; Ent* search cursor 320 words.
 *    * R8 BIG, 97 arms, 11 INERT, EW 23: the factorial type/position lattice.
 *      24 arms reach wd<key -- ALL of them ws-declared-first AND unsigned --
 *      best 44 bad.  This is where section 2's lattice comes from.
 *    * R9 BIG, 109 arms, 13 INERT, EW 5: decomposition of the unsigned
 *      trigger (u32 member x -1 literal form x cast-on-key x compare operand
 *      order x r-position x cursor order).  Only the four triples.  0 at (6,7,8).
 *    * R10 BIG, 43 arms, 5 INERT, EW 17: "colder key" battery -- unsigned in
 *      the search only / the if-chain only / both, s64 and u64 casts, the
 *      if-chain as a `switch`, val u16/s32, id `long`.  key never exceeds $7.
 *    * R11 BIG, 29 arms, 13 INERT, EW 5: chain spelling (member vs [2] vs raw
 *      cast vs triple-index vs void*-returning callee vs const/volatile) and
 *      six search-compare forms (==, reversed, !(!=), subtract, xor).  0 hits.
 *    * R12 BIG, 19 arms, 7 INERT, EW 6: delete each local in turn -- no
 *      w0/w1, one temp, no ws, no k, no key (re-read through Sub*), no e,
 *      tbl as s32[30].  Best 12 (inert), worst 28.  The SysCmd lever does not
 *      transfer.
 *
 * 6. WHAT THE NEXT PASS MUST NOT RE-GRIND (all of the above, but especially):
 *    pragmas in ANY combination up to pairs, `optimization_level N`, the
 *    `register` keyword, declaration order of anything, statement order of
 *    anything, splitting or re-typing the pointer chain, merging the two copy
 *    loops, merging wd with n, deleting any local, loop trip counts, and
 *    key's type/signedness/width.  All measured, all with an inert-split.
 *
 * 7. WHAT IS LEFT, in priority order.
 *    a) Find rank 2.  Everything above says `key`'s slot among {key,ws,wd} is
 *       chosen by ONE scalar heuristic with (so far) two attainable values.
 *       The productive experiment is NOT another spelling of this function --
 *       it is a 20-line MINI-REPRO of "one long-lived scalar + one two-cursor
 *       copy loop" swept over the heuristic's likely inputs (use count of the
 *       scalar, number of interfering pointers, whether the scalar's def is a
 *       load vs a call result vs a constant) until a THIRD triple appears.
 *       If a third triple exists, the axis is open; if 200 arms of that
 *       repro still give only two, the unit is a compiler-build question.
 *    b) The twin insmenu_InsectVsSaveScreenClose_4f7990 has the IDENTICAL screen signature
 *       (cursor $6 / scalar $8) and is parked at 13.  Whatever moves one
 *       moves 1,824 B, so instrument them together.
 *    c) Do NOT spend full-unit round trips.  Section 0.
 *
 * [SUPERSEDED BY SESSION 14 -- CLOSED, 0 BAD, THIS FILE IS ADMITTED.]
 * STILL PARKED, RIGHT LENGTH / WRONG BYTES (12 words, 1,296 B).  A length
 * guard does not catch it, so this file stays out of src/ and out of
 * config/ocunits until the register rank falls.
 */
/* SESSION 12 (2026-08-26, lane C4 / tag im14).
 * ================= THE LENGTH DEFECT IS CLOSED. =================
 * This unit is no longer ONE WORD SHORT.  It builds at 0x510 == retail, 324
 * words, and the residue is 12 BAD WORDS, all one register-allocation swap.
 * Everything below that predates this block is superseded where it conflicts.
 *
 * 1. THE LEVER, and it was found by looking at a MATCHED unit, not by sweeping.
 *    insmenu_InsectVsSaveScreenOpen_4f8ef0 is the twin the old header names ("the SAME one word
 *    blocks 004f7dd0 and 004f8ef0").  It is ADMITTED and BYTE-IDENTICAL today
 *    (build/dv_osbuild.py --tag im14 printed `304  MATCH  1/1 byte-identical`)
 *    and its retail asm carries the identical shape at 0x004F9050:
 *        sll $3,$3,2 / addu $3,$3,$29 / addiu $3,$3,0x30 / lw $3,0x0($3)
 *    Its first line is `#pragma opt_dead_assignments off`.
 *    ARMING CONTROL, measured both directions (build/vsp_im14_ctl.py):
 *        f8ef0 as shipped              -> 0 bad, object cb59686a
 *        f8ef0 with the pragma REMOVED -> len 0x4bc vs 0x4c0, ONE WORD SHORT
 *    So the pragma IS the mechanism for this exact defect, proven on a unit
 *    that reaches MATCH.
 *
 * 2. THE PRAGMA ALONE IS NOT ENOUGH HERE -- IT NEEDS THE SOURCE STATEMENT.
 *    Measured on this unit (build/vsp_im14_b.py):
 *        dead_off alone                       len 0x50c   (still short)
 *        the array element read TWICE alone   len 0x50c   (still short)
 *        BOTH                                 len 0x510   RIGHT LENGTH
 *    The statement is: retail reads `tbl[n].id` TWICE in source, once in the
 *    while test and once in the `if`, instead of caching it in `e`.  With
 *    dead-assignment elimination off, the second read's address computation
 *    survives as the `addiu` and the loads still CSE.  This is the same shape
 *    f8ef0 has (`while (ids[n] != -1) { func_28EB10(.., ids[n]); n++; }`).
 *    (`while ((e = tbl[n].id) != -1)` in the TEST is INERT once the `if`
 *    re-reads -- arm e_in_test, build/vsp_im14_k.py.)
 *
 * 3. TWO MORE MEASURED MOVES, 31 -> 26 -> 12 bad words.
 *    * `r = 0;` belongs BEFORE the word-copy loop, not after it.  Retail's
 *      pre-loop basic block is 8 instructions and ours was 7: retail schedules
 *      `move $2,$0` at 0x004F8150, between the two loads of the `key` chain.
 *      A basic-block scheduler cannot hoist across the loop, so the statement
 *      is in that block in retail's source.  (`r = 0` BEFORE the func_1FEDE0
 *      call is wrong -- it goes callee-saved and the object is 0x508.)
 *    * `#pragma opt_pulloutconstants off` (SECOND-ORDER knob screen,
 *      build/im14_knob2.log, 484 arms on top of dead_off: 459 INERT, 25 live,
 *      one winner) removes ALL 14 words of head damage that
 *      opt_dead_assignments off introduces -- five `li $5,<id>` / `addiu
 *      $4,$4,%lo` transpositions in the call setups plus the 1.0f/-1.0f
 *      materialisation order at 0x004F7F90.  It is INERT on f8ef0, so it is
 *      unit-specific, not a general companion.
 *    * declaring `wd` BEFORE `ws` (pair swap) fixes ws -> $7.
 *
 * 4. THE 12-WORD RESIDUE, in one sentence: `key` and `wd` have exchanged
 *    registers.  Retail wd=$6, ws=$7, key=$8, n=$6; ours wd=$8, ws=$7,
 *    key=$6, n=$7.  Words 221,225,229,230,233,234,237,238,242,249,257,265.
 *    Nothing else in the function differs.
 *
 * 5. NEGATIVES MEASURED THIS SESSION AGAINST THAT RESIDUE -- do not re-run.
 *    * KNOB, THREE ORDERS, all on ARMED bases (the session-9 488-arm log is
 *      void because its base was the short source; these are not):
 *        486 arms on the right-length-less base (build/im14_knob.log):
 *            462 INERT, 24 live; only TWO reach 0x510 --
 *            opt_dead_assignments off (31 bad) and opt_repositioncode on (102).
 *        484 arms on dead_off      (build/im14_knob2.log): 459 INERT, 25 live,
 *            best opt_pulloutconstants off = 12.
 *        482 arms on dead_off+pull (build/im14_knob3.log): 458 INERT, 24 live,
 *            NOTHING below 12.  The knob axis is now spent WITH the arming
 *            proof the old sweep lacked.
 *    * `key`'s DECLARATION POSITION IS INERT.  Five positions (first, between
 *      the pointers, after ws, last, before tbl) all emit object 22d7081a
 *      byte-identical, in BOTH ws/wd orders (build/vsp_im14_h.py, 8 arms,
 *      5 INERT / 3 live-and-worse; build/vsp_im14_d.py, 7 arms, 5 INERT).
 *      Only the {wd,ws} ADJACENCY order is live, and it is already right.
 *    * `key`'s STATEMENT position and its intermediate-local spellings are
 *      INERT: hnd_split, ctx_sub_named, key_via_tmp, wd_via_tmp all emit
 *      22d7081a (build/vsp_im14_f.py).  Moving the assignment after `k = 15`
 *      is 0x514 -- LONGER.
 *    * SCOPING is inert: wrapping ws/wd/k/w0/w1 in an inner block emits the
 *      same object as the plain declaration order (build/vsp_im14_g.py).
 *    * Loop spelling is inert: for-form, three_reads, cmp operand swap, and
 *      dropping the now-unused `e` all emit 22d7081a
 *      (build/vsp_im14_k.py, build/vsp_im14_j.py, build/vsp_im14_i.py).
 *    * Whole-declaration-block permutations: 8 arms, 5 INERT, 3 worse
 *      (build/vsp_im14_j.py).  Nothing beats 12.
 *
 * 6. WHAT THE NEXT PASS SHOULD ATTACK: the allocator's PRIORITY ORDER between
 *    a long-lived scalar (`key`) and the copy loop's destination cursor
 *    (`wd`).  Ours ranks them [key, ws, wd] -> $6,$7,$8; retail ranks them
 *    [wd, ws, key].  It is NOT declaration order (proved above), NOT statement
 *    order, NOT scope, NOT type (u32 key is inert, s16 key is 0x518), and NOT
 *    reachable from any of the 244 pragmas in either polarity.  A MINI-REPRO
 *    of just "one long-lived scalar plus a two-cursor copy loop" scored by
 *    objdump (build/mr_im14.py takes a directory of scratch .c) is the right
 *    next instrument -- build/mr-im14 already has 16+17 cells for the
 *    addressing question and the harness works.
 *
 * 7. THE OLD "23 SPELLINGS, EVERY ONE FOLDS" NEGATIVE IS NOT REFUTED -- it is
 *    OUT OF SCOPE.  Every one of those probes was a pure SOURCE probe at the
 *    default knob setting, and the split is not reachable that way.  The
 *    session-11 claim "EXACTLY ONE SPELLING PRODUCES RETAIL'S SHAPE and it is
 *    not this code" is OVERTURNED: q_both is not the only one, and the shape
 *    is reachable with a DEAD address register once dead-assignment
 *    elimination is off.
 *
 * [SUPERSEDED BY SESSION 14 -- CLOSED, 0 BAD, THIS FILE IS ADMITTED.]
 * STILL PARKED, but now RIGHT LENGTH / WRONG BYTES (12 words).  A length guard
 * NO LONGER catches it, so this file must stay out of src/ and out of
 * config/ocunits until the register swap falls.
 */
#pragma opt_pulloutconstants off
#pragma opt_dead_assignments off
#include "types.h"

/* insmenu 0x004F7DD0 (1,296 bytes, 324 instructions, 34 calls) -- the long
 * panel setup, then a lookup that turns the current entry id into a layout row
 * and applies that row to the two 0x88C2 widgets.
 *
 * The two tables are copied into the frame by EXPLICIT loops through word and
 * halfword cursors, not by local-array initialisers.  That is deliberate and
 * it is a LINK constraint, not a style choice: an initialised local makes mwcc
 * emit its own copy of the template into the object's .rodata, olink's lcf
 * collects *(.rodata) into .data, and the overlay would then carry both that
 * copy and the insmenu_D_004F97A0 / insmenu_D_004F9820 already in its own data -- every byte
 * after them shifts and the image is no longer byte-identical.  The same
 * mechanism blocks insmenu_FUN_004EF7B0's compiled jump table.
 *
 * The word-pair cursor is why the entry copy is `lw/lw/sw/sw` rather than the
 * `lw/lh/lh/...` a member-by-member copy of Ent would give, and it is also the
 * all-loads-before-all-stores rule: one local per load, in listing order.
 *
 * `r` and the two counters are s16: retail re-normalises `r` with
 * `dsll32 16 / dsra32 16` before scaling it by 20, which is the cost a narrow
 * local pays and which an s32 would not.
 *
 * [SUPERSEDED BY SESSION 14 -- CLOSED, 0 BAD, THIS FILE IS ADMITTED.]
 * PARKED AT ONE INSTRUCTION, A LENGTH DEFECT.  0x50C against retail's 0x510.
 * The whole deficit is the array-index addressing in the search loop: retail
 * materialises the element address as
 *     sll <i> / addu <x>, <i>, $29 / addiu <x>, <x>, <frame off> / lw <x>, 0(<x>)
 * and we fold the frame displacement into the load,
 *     sll <i> / addu <x>, <i>, $29 / lw <x>, <frame off>(<x>).
 * The SAME one word blocks insmenu_InsectVsLoadPanelLayout_4f7dd0 and insmenu_InsectVsSaveScreenOpen_4f8ef0 --
 * 2,512 bytes on one fix -- so it was probed properly rather than swept.
 *
 * ⚠ MEASURED BOUNDED NEGATIVE, 23 SPELLINGS IN TWO PROBE-TU ROUNDS
 * (src/overlays/insmenu/improbe.c, deleted after use).  Every one of these
 * FOLDS: s16 index, s32 index, u16 index, s64 index, a named `const s32 *p = a`
 * read as `p[i]`, `*(const s32 *)((const u8 *)a + i*4)`, the same with `i << 2`,
 * `*(&a[i] + 0)`, `q = a + i` then `*q`, `b = a` re-taken every iteration then
 * `b[i]`, the array inside a struct local, an array of one-member structs, an
 * array of 8-byte structs read at member 0, a nested-struct first member, a
 * whole-struct copy in the test, a second local below it, a 2 KB pad in front
 * of it, and a `volatile` array (which hoists a pointer instead).
 *
 * ★ EXACTLY ONE SPELLING PRODUCES RETAIL'S SHAPE, and it is not this code:
 * when the element ADDRESS is genuinely live at two uses --
 * `q = &a[i]; g(*q); g2(q);` -- mwcc emits `addiu s1, a0, 48 / lw a0, 0(s1)`.
 * Here retail's address register is dead the instant the load consumes it
 * (`lw $4, 0x0($4)` overwrites it), so that mechanism does not apply.
 * ★ And retail folds in the very same function where the member offset is
 * NON-ZERO: 004F7DD0's `.val` read is `addu $2, $5, $29 / lh $2, 0xB4($2)`.
 * So the split is specifically member-offset-zero, which is where there is
 * nothing to gain from folding -- and our build folds anyway.
 * Do not sweep this further without a different compiler build.
 */

typedef struct Ent Ent;
struct Ent {
    u32 id;
    s16 val;
    s16 pad06;
};

typedef struct Slot Slot;
struct Slot {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field24;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8 pad0000[0x1188];
    void *field1188;
};

typedef struct Sub Sub;
struct Sub {
    u8 pad00[8];
    s32 field08;
};

extern u8 insmenu_D_004FA180[];
extern s32 insmenu_D_004F97A0[];
extern s16 insmenu_D_004F9820[];
extern s16 D_0048436C;      /* gp - 0xE04*/
extern f32 D_0047D34C;
extern f32 D_0047D28C;
extern f32 D_0047D3C4;
extern f32 D_0047D240;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insmenu_InsectVsLoadPanelLayout_4f7dd0(void)
{
    Ent tbl[15] __attribute__((aligned(16)));
    s16 rows[6][2][5] __attribute__((aligned(16)));
    s32 key;
    const s32 *ws;
    s32 *wd;
    const s16 *hs;
    s16 *hd;
    s32 k;
    s32 w0;
    s32 w1;
    s16 r;
    s16 h0;
    s16 h1;
    s32 e;
    s32 n;
    s16 (*base)[5];
    s32 i;
    const s16 *m;
    Slot *p;

    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CA7, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88BC, 1, 1);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BC, 1.0f, D_0047D34C, 0.0f);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88BF, 5, 5);
    UiSetWidgetColor_2905b0(insmenu_D_004FA180, 0x88BF, 0.0f, 0.0f, 0.0f, D_0047D28C);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C6, 1, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C7, 1, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C8, 1, 1);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88C8, 0x117, 0x1F);
    UiSetSpriteUv_28f970(insmenu_D_004FA180, 0x88C3, 0xC0, 0x12, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88C3, 0x30, 0xF);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88C1, -0x12, 0xC);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88C0, -0xF, 0xF);
    UiSetWidgetColor_2905b0(insmenu_D_004FA180, 0x88C0, 0.0f, 0.0f, 0.0f, D_0047D28C);
    UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C1, 0x5A, 0xC, D_0047D34C, 0);
    UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88C0, 0x5D, 0xF, D_0047D34C, 0);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C1, 1.0f, D_0047D34C, -1.0f);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88C0, D_0047D28C, D_0047D3C4, -1.0f);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88C2, 1, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88BA, 1, 1);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x88CC, 1, -1);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x88E0, 1, -1);
    UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x88F4, 1, -1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x890D, 0, 1);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88BA, 0xC8, 0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88CC, 0x38, 0x49);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88E0, 0x38, 0xC0);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x88F4, 0x38, 0x137);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x890B, 0x1E5, 0x4A);
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 0x890C, 0x1E9, 0x4C);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x88BA, 1.0f, D_0047D34C, 0.0f);
    UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x88BA, 0, 0, D_0047D240, 0);
    key = ((Sub *)((Ctx *)((Handle *)GetGameData_1fede0())->field24)->field1188)->field08;
    r = 0;
    ws = insmenu_D_004F97A0;
    wd = (s32 *)tbl;
    k = 15;
    do {
        w0 = ws[0];
        w1 = ws[1];
        wd[0] = w0;
        wd[1] = w1;
        ws += 2;
        wd += 2;
    } while (--k > 0);
    n = 0;
    while (tbl[n].id != 0xFFFFFFFF) {
        if (tbl[n].id == (u32)key) {
            r = tbl[n].val;
            break;
        }
        n++;
    }
    if (key == 0x193) {
        if (D_0048436C == 2) {
            r = 1;
        }
    } else if (key == 0x1F6) {
        if (D_0048436C == 2) {
            r = 0;
        }
    } else if (key == 0x1F7) {
        if (D_0048436C == 2) {
            r = 1;
        }
    }
    hs = insmenu_D_004F9820;
    hd = (s16 *)rows;
    k = 30;
    do {
        h0 = hs[0];
        h1 = hs[1];
        hd[0] = h0;
        hd[1] = h1;
        hs += 2;
        hd += 2;
    } while (--k > 0);
    base = rows[r];
    for (i = 0; i < 2; i++) {
        p = ((Slot *)UiGetWidgetSprite_28fe10(insmenu_D_004FA180, 0x88C2, i));
        if (p != 0) {
            m = base[i];
            p->f00 = m[0];
            p->f08 = m[1];
            p->f0A = m[2];
            p->f0C = m[3];
            p->f04 = m[3];
            p->f0E = m[4];
            p->f06 = m[4];
        }
    }
}
