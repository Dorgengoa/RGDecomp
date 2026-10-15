/* SESSION 14 (2026-08-27, lane im34).  ***MATCHED -- 600 words, 0 bad,
 * byte-identical.***  Confirmed twice with the same object sha1 1102c6a3:
 * build/dv_osbuild.py insmenu --tag im34 (600 words, MATCH) and arm n8_c_top
 * of build/vsp_im34_b.py.  build/p5_order.py on the final object reads
 * a1-first 10 / a0-first 0 at the ten two-load call sites (baseline was 6/4).
 *
 * ==== THE FIX ====
 * A FUNCTION-SCOPE `Ctx *c;` (declared immediately after `Obj *o;`) assigned
 * in ITS OWN STATEMENT at exactly the four flipping sites:
 *     c = o->field24;
 *     func_431310(c, sp7C);        (sel==6 and sel==7)
 *     func_431110(c, sp78);        (sub==0x3C and sub==0x3D)
 * The other five two-load sites keep `func_43xxx0(o->field24, spNN)` verbatim.
 * With `c` named, mwcc emits `lw $5,<stack>` before the jal and `lw $4,0x24($19)`
 * in the delay slot -- retail's order -- at all ten sites.
 *
 * ==== WHY IT IS THE FUNCTION-SCOPE DECLARATION AND NOT "NAMING" ====
 * Every block-scoped spelling of the same idea is INERT (object sha1 identical
 * to the a0-first baseline a8938f1f), measured in one round trip,
 * build/vsp_im34_b.py:
 *     n1_c_only        { Ctx *c = o->field24; f(c, spNN); }          INERT
 *     n2_c_then_v      { Ctx *c = ...; s32 v = spNN; f(c, v); }      INERT
 *     n3_v_then_c      { s32 v = spNN; Ctx *c = ...; f(c, v); }      INERT
 *     n4_c_const       { Ctx *const c = o->field24; ... }            INERT
 *     n5_c_sep_assign  { Ctx *c; c = o->field24; ... }               INERT
 *     n7_c_reg         { register Ctx *c = ...; ... }                INERT
 * and at function scope the ORDER of the two named values decides it:
 *     n8_c_top   `c = o->field24; f(c, spNN);`                  MATCH 1102c6a3
 *     n10_cv_top `c = o->field24; v = spNN; f(c, v);`           MATCH 1102c6a3
 *     n9_vc_top  `v = spNN; c = o->field24; f(c, v);`                INERT
 * Naming the volatile READ never mattered (session 12 measured five inert arms
 * of that; n9 confirms it a sixth time).  Naming the POINTER, at function
 * scope, is the whole lever.
 *
 * ==== SESSION 12's TRIGGER RULE, CORRECTED ====
 * Session 12: "a0-first iff some LATER call in the arm takes >= 1 argument".
 * Measured here (build/vsp_im34_a.py, build/vsp_im34_b.py, read with
 * build/p5_order.py so a wrong-length arm still scores):
 *   later call arg = a CONSTANT             -> site stays STACK-FIRST
 *       m3_later_const  `t = func_430B10((Ctx *)0x10);`        bad 6
 *       m2_later_int    `im_probe_i(1);`                       8 a1-first / 2
 *       m1_later_float  `im_probe_f(D_0047D49C);` ($f12, no $4) 8 a1-first / 2
 *   later call arg loaded from the STACK or a GP ADDRESS -> STACK-FIRST
 *       g2_later_stack  `func_430B10((Ctx *)sp74)`             bad 6
 *       g4_later_global `func_430B10((Ctx *)&D_00484304)`      bad 6
 *   later call arg derived from `o`/$19 -> a0-FIRST (the defect)
 *       the baseline itself, and session 12's `(Ctx *)o` arm.
 * => the trigger is a later definition of $4 FROM `o`, not any later argument.
 *    It cannot be removed (retail has it too); naming `c` is what beats it.
 *
 * ==== MEASURED NEGATIVES ADDED (do not re-grind) ====
 * build/vsp_im34_a.py, 32 arms, 31 compiled, 27 right-length, 23 INERT
 * (effective width 9).  The whole CALLEE PROTOTYPE GRAMMAR axis is INERT:
 * `void *c`, `const Ctx *c`, `Ctx *const c`, K&R `func_431310()` on either or
 * both callees, varargs `(Ctx *c, ...)`, `long a` / `const s32 a` second
 * parameter, and the same four on the LATER callees (void*, K&R, Ctx *const,
 * void* return).  Also INERT: extern declaration ORDER (both directions),
 * local declaration order and scope for `t` and for `sel`/`sub`,
 * `do { } while (0)` around the trigger statements, `void *field24`,
 * `volatile int` slots.  LIVE and WORSE: `func_430B10(o->field24)[0] = 0x25B`
 * (16), `sub = sp78` before the call (14), swapping sel==7's two calls (11).
 * build/vsp_im34_b.py, 28 arms, 27 compiled, 23 right-length, 13 INERT
 * (effective width 15).  Also worse: `volatile long` slots (28), hoisting the
 * trigger call above the two 0-arg calls (24), `(Ctx *)o` at the trigger (64).
 * Arming: ctl_neg_comment INERT, ctl_pos_s7_0arg reproduced session 12's
 * one-site fix (a0-first 4 -> 3), ctl_pos_later_const reproduced sweep A.
 *
 * Tools: build/vs_im34.py (N full-unit spellings, one round trip),
 * build/vsp_im34_{a,b}.py, build/p5_order.py.
 */
/* SESSION 12 (2026-08-26, lane C5, tag im15).  FLOOR UNCHANGED AT 8 WORDS.
 * Baseline re-measured today with build/dv_osbuild.py --tag im15:
 * 600 words (= 0x960/4, arming proof), 8 bad, object a8938f1f -- reproduces
 * the session-11 figure exactly.
 *
 * ==== THE RESIDUE IS ONE CLASS, NOT TWO ====
 * All 8 words are FOUR transpositions of the same two instructions:
 *   0x004EB3E0/3E8 (sel==6)    0x004EB3FC/404 (sub==0x3C)
 *   0x004EB434/43C (sub==0x3D) 0x004EB4C4/4CC (sel==7)
 * retail: lw $5,<stack> ; jal ; lw $4,0x24($19)      ("stack-first")
 * ours:   lw $4,0x24($19) ; jal ; lw $5,<stack>      ("a0-first")
 * Nothing else in the 600 words differs.  Probe: build/p5_order.py <obj>
 * decodes rt/rd rather than matching whole words, so it survives a change of
 * callee-saved register, stack layout OR function length -- it reads the
 * order on an arm that scores "-" for a length mismatch.  On the baseline it
 * prints a1-first 6 / a0-first 4 at exactly the ten two-load call sites.
 *
 * ==== THE TRIGGER, MEASURED (this is the new thing) ====
 * A call whose two argument registers are both set by loads emits a0-FIRST
 * if and only if SOME LATER CALL IN THE SAME ARM TAKES AT LEAST ONE ARGUMENT
 * (i.e. redefines $4 or $5).  If every later call in the arm is argument-less
 * -- or there is no later call -- the order is retail's stack-first.
 * Evidence, every cell with a matched control in the same round trip:
 *   build/vsp_im15_c.py  sel==7 later call ->
 *       0x14 constant arg2  a9cbaa13  a0-first  (still wrong)
 *       register arg2       2065a72e  a0-first
 *       1-arg func_430B10   8c03f877  a0-first
 *       0-ARG call          9dd72ea5  STACK-FIRST  <- fixed
 *     sub==0x3C tail ->
 *       drop the store only 4d009c3f  a0-first
 *       0-ARG call          4a53e479  STACK-FIRST  <- fixed
 *       plain global store  c0bcdfbf  STACK-FIRST  <- fixed
 *   build/vsp_im15_h.py  SAME LENGTH PAIR, 556 words both, sel==6 body cut to
 *     a single nested if:  0-arg call in the successor 92a12ce9 STACK-FIRST,
 *     1-arg call in the successor aeb7aba7 a0-first.  So the trigger reaches
 *     into DOMINATED SUCCESSOR BLOCKS, not just the call's own block.
 *   build/vsp_im15_b.py  s6_strip 48ea9987 and s7_strip a23e4a93 each fix
 *     exactly their own site by deleting the later argument-taking call.
 * The consequence: the trigger cannot be removed without changing the CFG,
 * because those later calls are what the arm is FOR.
 *
 * ==== WHAT WAS REFUTED THIS SESSION ====
 * * "the flipping arms are the ones whose body CONTINUES with another
 *   o->field24 use" (the session 9 + 11 discriminator) is a CORRELATION, NOT
 *   THE CAUSE.  build/vsp_im15_a.py replaces the LATER o->field24 with
 *   `(Ctx *)o` -- same instruction count, no field24 CSE left -- at each site
 *   separately (2a7f12ed, 349302d3, 3715e388) and all four sites stay
 *   a0-first.  Independently, `#pragma opt_common_subs off` (570fb267,
 *   611 words) also leaves all four a0-first.  It is not CSE.
 *
 * ==== MEASURED NEGATIVES ADDED (all with a live control in the same run) ====
 * COMPILER-KNOB AXIS IS NOW CLOSED, not merely screened: build/kn_im15.py
 *   --all = the FULL 488-variant pragma namespace (244 names x on/off),
 *   469 INERT on a8938f1f, 19 live, and NOT ONE live arm is both the right
 *   length and better than 8.  The live set is cats_off / export_on /
 *   force_active_on / lib_export_on (8 bad, cosmetic), reverse_bitfields_on
 *   (10), and eleven wrong-length or failing arms (schedule_off 0xb1c,
 *   peephole_off 0x974, no_branch_likely_on 0x9dc, opt_repositioncode_on
 *   0x97c, opt_common_subs_off 0x98c, floatsp32_off / fp_library_off 0x95c,
 *   far_call_on, interrupt_on, cplusplus_on, plus four compiler failures).
 *   This SUPERSEDES the session-9 "117-pragma screen".
 *   NOTE: peephole_off and no_branch_likely_on both keep all four sites
 *   a0-first, so the decision is NOT in the peephole or the branch-likely
 *   pass.  schedule_off fills no delay slot with a load at all.
 * NAME THE VOLATILE READ BEFORE THE CALL -- 5 arms, 5 INERT, byte-identical
 *   to the baseline (build/vsp_im15_d.py).  `v = sp7C; func_431310(c, v);`
 *   compiles to the same object as `func_431310(c, sp7C)`, for a fresh local,
 *   for the dead `sel` / `sub` locals, at one site and at all four.  The
 *   factory/normal "name it BEFORE" lever does not reach this decision.
 * DEEPER arg1 EXPRESSION TREE that still folds to one `lw` -- 3 arms, 3
 *   INERT (build/vsp_im15_f.py): a nested sub-struct `o->inner.field24`, a
 *   one-element array `o->field24[0]`, and `*o->field24`.  mwcc canonicalises
 *   the address expression before the ordering decision.
 * register / const / prototype spellings -- 4 arms, 4 INERT
 *   (build/vsp_im15_g.py, control ctl_s7_0arg live at 9dd72ea5):
 *   `register Obj *o`, both callees redeclared to RETURN s32, `(s32)sp7C` on
 *   arg2, and swapping the two externs' declaration order.
 * `Obj *const o = func_1FEDE0();` at the declaration is live but 0x95c.
 *
 * ==== THE ONE LEVER THAT DOES MOVE IT, AND ITS PRICE ====
 * Making arg1 an expression that needs a REAL extra instruction flips the
 * order: `(*(Ctx **)((u8 *)o + 0x24))` at the four sites (888737bb, 0x964 =
 * ONE WORD LONG) turns the sub==0x3C and sub==0x3D sites stack-first, at the
 * cost of one shared `addiu $s0, $s3, 0x24`; sel==6 becomes
 * `lw a1 / lw a0 / jal / addiu` (right order, wrong delay slot) and mwcc
 * FOLDS the address back at sel==7, restoring a0-first there.  The recorded
 * session-11 lead "volsite4 is only one word long, nobody has looked at its
 * words" is now looked at: build/vsp_im15_e.py e1_volsite4 b7ada10a, 601
 * words, still THREE a0-first sites.  That lead is spent.
 *
 * ==== POPULATION CONTEXT (build/p5_rule.py, every retail listing) ====
 * Project-wide there are only 38 calls with this argument shape.  Retail's
 * own 2x2: a1-first/later-argcall 8, a1-first/none 16, a0-first/later-argcall
 * 6, a0-first/none 8 -- so RETAIL DOES NOT OBEY OUR RULE, and three of the
 * eight a1-first/later-argcall sites are eb230's own.  None of the other 35
 * sites belongs to a function that has a C source, so there is no worked
 * answer to copy anywhere in the tree (checked with rgd.src_path).
 *
 * ==== WHERE THE NEXT PASS SHOULD AIM ====
 * The source-spelling axis and the compiler-knob axis are both closed for
 * this decision.  What is left is (a) some construct that makes the LATER
 * call not define $4 -- none exists in C -- or (b) the possibility that the
 * ARM BODIES are mis-decompiled in a way that changes nothing else in 600
 * words, which is hard to believe.  Do not re-run: the CSE hypothesis, the
 * pragma namespace, naming the volatile read, deeper arg1 trees, or the
 * volsite family.  Mini-repro note: build/mr-im15 (12 cells) does NOT
 * reproduce the flip at small scale -- every cell is stack-first -- so the
 * trigger needs eb230's register pressure as well as the arm shape.
 *
 * TOOLS LEFT: build/p5_order.py (order probe), build/p5_dis.py (disassemble
 * any scratch object), build/p5_rule.py (population), build/p5_hunt.py,
 * build/p5_bad.py, build/vs_im15.py, build/kn_im15.py, build/mr_im15.py,
 * specs build/vsp_im15_{a,b,c,d,e,f,g,h}.py.
 *
 * PARKED AT 8 WORDS.  RIGHT LENGTH, WRONG BYTES -- the dangerous class.  It
 * must stay out of config/ocunits/insmenu.txt and out of src/.
 */
/* SESSION 11 (2026-08-26, lane L5).  FLOOR MOVED 10 -> 8.  Fresh baseline
 * measured with build/dv_osbuild.py --tag im05: 600 words, 8 bad.
 *
 * ==== WHAT CLOSED (2 words, 0x004EB594 / 0x004EB598) ====
 * The w->field4C6 / w->field4C7 store pair was NOT a scheduling artefact and
 * NOT a statement-order problem.  It is ONE SUB-STRUCT ASSIGNMENT -- the
 * main-pass-34 lever (BATCHED loads-then-stores = one struct assignment,
 * INTERLEAVED load/store pairs = N statements).  Retail's
 *     lbu a2,-3676(gp) / lbu a1,-3675(gp) / sb a2,0x4C6(v0) / sb a1,0x4C7(v0)
 * is mwcc's 2-byte struct copy, emitted in canonical member order for BOTH
 * the loads and the stores, which is why no combination of two separate byte
 * assignments could get the register allocation and the emission order right
 * at the same time (session 9 measured all four at 4/4/2/2).  The spelling
 * now in this file:
 *     typedef struct { u8 b0; u8 b1; } Pair;   Widget { ... Pair p4C6; }
 *     extern Pair D_00484314;                  w->p4C6 = D_00484314;
 * Sweep artefact: build/vs_im05_eb230.py, arm `pair` 8 vs baseline 10; the
 * two hand-written orders in the same sweep scored 12 (direct_c6first) and
 * 13 (direct_c7first), re-confirming session 9's negative on that axis.
 *
 * ==== WHAT REMAINS: 8 words, the four lw transpositions ====
 * 0x004EB3E0/3E8, 0x004EB3FC/404, 0x004EB434/43C, 0x004EB4C4/4CC.
 * Retail issues `lw $5,<stack>` BEFORE the jal and puts `lw $4,0x24($19)` in
 * the delay slot; we emit them the other way round.  Session 9's discriminator
 * re-confirmed: exactly the four arms whose body CONTINUES with another
 * o->field24 use flip; the five that end at the call are correct.
 *
 * NEGATIVES ADDED THIS SESSION (13 arms, two sweeps; the second sweep was
 * scored against the pair-corrected baseline of 8):
 *   INERT (object sha1 identical to baseline -- measured NOTHING):
 *     callee_vol      second parameter declared `volatile s32` on both callees
 *     const_ctx       Ctx *const field24;
 *     callee_s64      second parameter widened to s64
 *     volsite4_A      volatile-cast at the sel==6 site alone
 *     volsite4_B      volatile-cast at the sub==0x3C site alone
 *   LIVE and WORSE / wrong length:
 *     vol_f24         Ctx *volatile field24;               0x964 vs 0x960
 *     vol_f24_pair    same + pair                          0x964 vs 0x960
 *     vol_o           Obj *volatile o;                     0xA38 vs 0x960
 *     volsite4        volatile-cast at all four sites      0x964 vs 0x960
 *     volsite_later   volatile-cast on the LATER field24 use in each
 *                     flipping block                       10 (worse than 8)
 *     slots_array     the three escaped slots as one `volatile s32 slot[3]`
 *                     instead of three scalars             26
 * => the volatile axis on the STRUCT MEMBER is now closed too: it is honoured
 *    (the object changes) but it always costs exactly one extra word.
 * => NOTE for the next pass: volsite4 is ONE WORD LONG at 0x964.  It is the
 *    only arm found that is neither short nor inert; if the four
 *    transpositions are right in it, the whole residue is one spurious word.
 *    UNMEASURED -- score_obj refuses a length mismatch, so nobody has looked
 *    at its words.  That is the single cheapest open lead on this unit.
 *
 * PARKED AT 8 WORDS.  RIGHT LENGTH, WRONG BYTES -- the dangerous class.  It
 * must stay out of config/ocunits/insmenu.txt and out of src/.
 */
/* SESSION 9 (2026-08-25): floor still 10 words.  117-pragma screen: 109 INERT,
 * nothing better.  The 10 are FIVE transpositions -- four of `lw $4, 0x24($19)`
 * against `lw $5, 0x7C($29)`/`0x78($29)` at the func_431310 / func_431110 sites,
 * one of the `w->field4C6` / `w->field4C7` store pair.
 * Two things measured and both negative:
 *   * swapping the two stores in the source scores WORSE (12), so the order in
 *     this file is right and that word is a scheduling artefact, not a statement
 *     order;
 *   * u32/u16/s16/u64 on both callees' second parameter is INERT.  That is the
 *     im-callee-param-signedness lever, and it does NOT reach here because the
 *     argument is a VARIABLE (`sp7C`), not a constant -- the lever acts through
 *     how the constant is materialised.
 */
#include "types.h"

/* insmenu 0x004EB230 -- the overlay's largest function (600 instructions,
 * 2,400 bytes, 123 calls): the insect-menu confirm handler.  It reads the
 * current selection triple out of the context, asks func_28E100 which button
 * was pressed, and dispatches to one of ~29 short arms that reconfigure the
 * panel and hand off to the per-page builders.
 *
 * ★★★★★ EVERY DISPATCH HERE IS AN if/else-if CHAIN, NOT A switch, AND THE
 * WHOLE FUNCTION IS UNIFORM ON THAT.  Classifying all 66 conditional branches
 * by their delay slots: every converted `bnel` carries THE NEXT GUARD'S
 * CONSTANT (`addiu $2, $0, 0x4` ahead of the `== 4` test), never a case body's
 * store.  That is the chain tell, so the cases run in SOURCE order -- not the
 * reversed order a switch would need.  m2c renders all eleven of them as
 * `switch` and every one of those would be the right length and the wrong
 * bytes.
 *
 * ★★★★ CONSTANTS ARE SHARED BETWEEN A GUARD AND THE ARM IT GUARDS.  Retail
 * calls `func_431310(ctx, 2)` with no `addiu $5, $0, 2` anywhere in the arm --
 * $5 still holds the 2 the `a18 == 2` test materialised.  Likewise
 * `func_430DB0(ctx, 0x259)` reuses $3 from the `a16 == 0x259` compare, and
 * `n = 1` / `n = 2` reuse the 1 and 2 of the `r == 1` / `r == 2` tests.  An
 * argument that is never materialised in its own block is not a missing
 * instruction; write the literal and let mwcc share it.
 *
 * ★★★ `ctx->field24` is re-read as `lw $4, 0x24($19)` before EVERY call --
 * 40-odd times -- with the object itself in $19.  That is the struct-member
 * form (offset folded into the load, base cached); the cast form
 * `*(X **)((u8 *)o + 0x24)` would CSE the ADDRESS into the callee-saved
 * register instead.  See insmenu_FUN_004ED0F0.
 *
 * ★★★ `w->bit0 = 1` is a ONE-BIT BITFIELD and the proof is the fold: retail
 * emits `addiu $3, $0, -0x2 / daddiu $4, $0, 0x1 / and / or`, and the
 * `daddiu` of the literal 1 is what a bitfield assignment of a constant folds
 * to.  A hand-written masked byte assignment folds both arms instead.
 *
 * ★★★★★★ THE TWO LEVERS THAT TOOK THIS FROM `len` TO 10 WORDS, both about the
 * three stack outputs of func_430940:
 *   1. They are `volatile s32`.  Plain, mwcc keeps the value the compare
 *      loaded and passes it straight on (`daddu $5, $3, $0`) where retail
 *      RELOADS `lw $5, 0x7C($29)` for the argument -- one word short in each
 *      of nine arms, 591 against 600.
 *   2. But volatile ALONE overshoots to 607, because then every compare in the
 *      chain reloads too, and retail loads the chain value exactly ONCE.  The
 *      shape retail has is a PLAIN LOCAL for the chain over a VOLATILE SLOT for
 *      the arguments: `sel = sp7C;` then `if (sel == 3) ... func_431310(ctx,
 *      sp7C)`.  That is exact on length and on all 123 call gaps.
 * ⇒ When a compare chain and its arms read the same escaped local, ask which
 *   of the two reads retail repeats.  Measured: plain 591, volatile 607,
 *   plain-local-over-volatile-slot 600.
 *
 * ★★★★ `*func_430B10(ctx) = 0x25B` written as one statement materialises the
 * constant BEFORE the call; retail materialises it after.  Splitting only the
 * CALL out (`t = func_430B10(ctx); *t = 0x25B;`) is the documented lever and
 * was worth 8 words across two sites.
 *
 * ★★★ Two guard polarities were inverted in the first draft and both are the
 * fall-through rule: `bnel $2, $0, L` branches AWAY on != 0, so the source
 * condition is `== 0` and the != 0 arm is what follows the `if`.  7 words at
 * the top guard, 3 more on `p->field10`.
 *
 * PARKED AT 10 WORDS, in two clusters, both allocation/scheduling:
 *   - 8 words, four sites (0x004EB3E0, 0x004EB3FC, 0x004EB434, 0x004EB4C4):
 *     retail issues `lw $5, <stack>` BEFORE the `jal` and puts
 *     `lw $4, 0x24($19)` in the delay slot; ours has them the other way round.
 *     ★ The discriminator is measured and is worth recording: the FIVE arms
 *     whose body ENDS at the call match perfectly, and the FOUR whose body
 *     continues with another `ctx->field24` use are the ones that flip.  So it
 *     is not the volatile read and not the argument list -- it is what else is
 *     left to schedule in the block.  Naming the volatile read in a temp ahead
 *     of the call changed the object not at all.
 *   - 2 words at 0x004EB594: `sb $6, 0x4C6` / `sb $5, 0x4C7` transposed.  All
 *     four load-order x store-order combinations measured (4/4/2/2 words); the
 *     store source order is what picks the registers and there is no ordering
 *     that gets both the registers and the emission order right.
 *
 * ★★ Two stores before a call fill that call's delay slot: `s->field00 = X;
 * s->field04 = Y; fn();` puts `sw $3, 0x4($2)` in the `jal`'s slot, and
 * `D_00484304 = 1; insmenu_InsectVsConfirmDialogFadeOut_4ee940();` puts the `sb` in that one's.
 */

typedef struct {
    s32 field00;
    s32 field04;
    s32 field08;
} Cfg;

typedef struct {
    u8 pad0000[0x1188];
    Cfg *field1188;
} Ctx;

typedef struct {
    u8 pad00[0x24];
    Ctx *field24;
} Obj;

typedef struct {
    u8 pad00[0x10];
    s16 field10;
} Panel;

typedef struct {
    s32 field00;
    s32 field04;
} Slot;

typedef struct {
    u8 b0;
    u8 b1;
} Pair;

typedef struct {
    u8 pad00[4];
    u8 bit0 : 1;
    u8 pad05[0x4C1];
    Pair p4C6;
} Widget;

/* gp bytes: 0x0048430C = gp - 0xE64, 0x00484304 = gp - 0xE6C,
 * 0x00484314 = gp - 0xE5C, 0x00484315 = gp - 0xE5B, 0x004842E8 = gp - 0xE88.
 * D_0047D49C = gp - 0x7CD4 is the float pool.  All five are inside the gp
 * window, so none of them is const. */
extern u8 D_0048430C;
extern u8 D_00484304;
extern Pair D_00484314;
extern u8 D_004842E8;
extern f32 D_0047D49C;

/* Outside the gp window (0x47D170..0x48D170) -- const, so %hi/%lo. */
extern const u8 D_004FA1A0[];
extern const u8 D_004FA180[];
extern const u8 D_004B2570[];
extern const u8 D_004B27E0[];

extern s32 insmenu_InsectVsConfirmDialogIsOpaque_4ee8e0(void);
extern Obj *func_1FEDE0(void);
extern void func_430940(Ctx *c, s32 *a, s32 *b, s32 *d);
extern s32 func_28E100(const void *a, const void *b, const void *c, s32 d);
extern Panel *func_28EC60(const void *a);
extern void insmenu_InsectVsConfirmDialogFadeOut_4ee940(void);
extern void insmenu_InsectVsTitleBannerSlideOut_4f2ed0(void);
extern void func_431310(Ctx *c, s32 a);
extern void func_431110(Ctx *c, s32 a);
extern void func_430DB0(Ctx *c, s32 a);
extern Slot *func_430B90(Ctx *c);
extern s32 *func_430B10(Ctx *c);
extern s32 *func_430AF0(Ctx *c);
extern Widget *func_430B70(Ctx *c, s32 a);
extern void func_4320A0(s32 *a);
extern void func_431F60(s32 *a);
extern void func_2882A0(void);
extern void func_28EDE0(void *a, s32 b, s32 c);
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
extern void insmenu_InsectVsBackGuideShow_4ea030(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f2ab0(void);
extern void insmenu_InsectVsTopPanelFadeOut_4f2b60(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f2350(void);
extern void insmenu_InsectVsRegisterPanelFadeOut_4f2440(void);
extern void insmenu_InsectVsTopPanelFocus_4f2680(void);
extern void insmenu_InsectVsRegisterPanelFocus_4f1f80(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f1b10(void);
extern void insmenu_InsectVsTwoPlayerPanelFadeOut_4f1bc0(void);
extern void insmenu_InsectVsTwoPlayerPanelFocus_4f16a0(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f1040(void);
extern void insmenu_InsectVsPwWatchPanelFadeOut_4f10f0(void);
extern void insmenu_InsectVsPwBattlePanelFocus_4f0bc0(void);
extern void insmenu_InsectVsWatchPanelFocus_4f0a00(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f0530(void);
extern void insmenu_InsectVsRegPwPanelFadeOut_4f05e0(void);
extern void insmenu_InsectVsRegPwPanelFocus_4f00d0(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4efc20(void);
extern void insmenu_InsectVsRegSavePanelFadeOut_4efcd0(void);
extern void insmenu_InsectVsRegSavePanelFocus_4ef7b0(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4ef090(void);
extern void insmenu_InsectVsRegTeamPanelFadeOut_4ef140(void);
extern void insmenu_InsectVsRegViewPanelFocus_4eec60(void);
extern void insmenu_InsectVsRegDeletePanelFocus_4eeac0(void);

s32 insmenu_InsectVsMenuStateConfirm_4eb230(void)
{
    Obj *o;
    Ctx *c;
    Panel *p;
    Widget *w;
    Cfg *q;
    Slot *s;
    s32 *t;
    u8 c6;
    u8 c7;
    s32 a18;
    s32 a17;
    s32 a16;
    s32 r;
    s32 n;
    volatile s32 sp7C;
    volatile s32 sp78;
    volatile s32 sp74;
    s32 sel;
    s32 sub;

    if (D_0048430C != 0) {
        if (insmenu_InsectVsConfirmDialogIsOpaque_4ee8e0() == 0) {
            D_00484304 = 1;
            return 1;
        }
        D_0048430C = 0;
        D_00484304 = 0;
        return 1;
    }
    D_00484304 = 0;

    o = func_1FEDE0();
    q = o->field24->field1188;
    a18 = q->field00;
    a17 = q->field04;
    a16 = q->field08;
    func_430940(o->field24, (s32 *)&sp7C, (s32 *)&sp78, (s32 *)&sp74);
    r = func_28E100(D_004FA1A0, D_004B2570, D_004B27E0, 0);
    p = func_28EC60(D_004FA1A0);
    n = 0;
    if (r == 1) {
        if (p->field10 == 0) {
            n = 1;
        } else {
            n = 2;
        }
    } else if (r == 2) {
        p->field10 = 1;
        n = 2;
    }
    if (n > 0) {
        D_00484304 = 1;
        insmenu_InsectVsConfirmDialogFadeOut_4ee940();
        if (n == 1) {
            insmenu_InsectVsTitleBannerSlideOut_4f2ed0();
            if (a18 == 2) {
                sel = sp7C;
                if (sel == 3) {
                    func_431310(o->field24, sp7C);
                    insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
                    insmenu_InsectVsTopPanelFadeOut_4f2b60();
                } else if (sel == 4) {
                    func_431310(o->field24, sp7C);
                    insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
                    insmenu_InsectVsTopPanelFadeOut_4f2b60();
                } else if (sel == 5) {
                    func_431310(o->field24, sp7C);
                    insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
                    insmenu_InsectVsTopPanelFadeOut_4f2b60();
                } else if (sel == 6) {
                    c = o->field24;
                    func_431310(c, sp7C);
                    sub = sp78;
                    if (sub == 0x3C) {
                        c = o->field24;
                        func_431110(c, sp78);
                        insmenu_InsectVsMenuEnterRecordStep_4f2350();
                        insmenu_InsectVsRegisterPanelFadeOut_4f2440();
                        t = func_430B10(o->field24);
                        *t = 0x25B;
                    } else if (sub == 0x3D) {
                        c = o->field24;
                        func_431110(c, sp78);
                        insmenu_InsectVsMenuEnterRecordStep_4f2350();
                        insmenu_InsectVsRegisterPanelFadeOut_4f2440();
                        t = func_430AF0(o->field24);
                        *t = 0x265;
                    } else if (sub == 0x3E) {
                        func_431110(o->field24, sp78);
                        insmenu_InsectVsMenuEnterRecordStep_4f2350();
                        insmenu_InsectVsRegisterPanelFadeOut_4f2440();
                    } else if (sub == 0x3F) {
                        func_431110(o->field24, sp78);
                        insmenu_InsectVsMenuEnterRecordStep_4f2350();
                        insmenu_InsectVsRegisterPanelFadeOut_4f2440();
                    }
                } else if (sel == 7) {
                    c = o->field24;
                    func_431310(c, sp7C);
                    func_431110(o->field24, sp78);
                    insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
                    insmenu_InsectVsTopPanelFadeOut_4f2b60();
                }
            } else if (a18 == 3) {
                if (a16 == 0x12D) {
                    if (sp74 == 0x133) {
                        func_431310(o->field24, 2);
                        func_431110(o->field24, 0x14);
                        func_430DB0(o->field24, 0xC9);
                        s = func_430B90(o->field24);
                        s->field00 = 3;
                        s->field04 = 0x1E;
                        insmenu_InsectVsMenuEnterRecordStep_4f1b10();
                        insmenu_InsectVsTwoPlayerPanelFadeOut_4f1bc0();
                        func_2882A0();
                    }
                } else if (a16 == 0x12E) {
                    w = func_430B70(o->field24, 2);
                    if (w != 0) {
                        w->p4C6 = D_00484314;
                        /* Store SOURCE order sets the REGISTERS here: written
                         * 4C6 then 4C7 the two bytes land in the opposite
                         * registers (4 words wrong).  All four combinations of
                         * load order x store order were measured: 4 / 4 / 2 / 2. */
                        w->bit0 = 1;
                    }
                    func_290690(D_004FA180, 0xA, 0.0f, D_0047D49C, -1.0f);
                    func_28EDE0(&D_004842E8, 0x7539, 0);
                }
            } else if (a18 == 4) {
                if (a16 == 0x191 && sp74 == 0x196) {
                    func_431310(o->field24, 2);
                    func_431110(o->field24, 0x14);
                    func_430DB0(o->field24, 0xC9);
                    s = func_430B90(o->field24);
                    s->field00 = 4;
                    s->field04 = 0x28;
                    insmenu_InsectVsMenuEnterRecordStep_4f1040();
                    insmenu_InsectVsPwWatchPanelFadeOut_4f10f0();
                }
            } else if (a18 == 5) {
                if (a16 == 0x1F5 && sp74 == 0x1FA) {
                    func_431310(o->field24, 2);
                    func_431110(o->field24, 0x14);
                    func_430DB0(o->field24, 0xC9);
                    s = func_430B90(o->field24);
                    s->field00 = 5;
                    s->field04 = 0x32;
                    insmenu_InsectVsMenuEnterRecordStep_4f1040();
                    insmenu_InsectVsPwWatchPanelFadeOut_4f10f0();
                }
            } else if (a18 == 6) {
                if (a17 == 0x3C) {
                    if (a16 == 0x259) {
                        if (sp74 == 0x25F) {
                            func_431310(o->field24, 2);
                            func_431110(o->field24, 0x14);
                            func_430DB0(o->field24, 0xCA);
                            s = func_430B90(o->field24);
                            s->field00 = 6;
                            s->field04 = 0x3C;
                            insmenu_InsectVsMenuEnterRecordStep_4f0530();
                            insmenu_InsectVsRegPwPanelFadeOut_4f05e0();
                        }
                    } else if (a16 == 0x25E) {
                        func_430DB0(o->field24, 0x259);
                        func_4320A0(func_430B10(o->field24));
                        insmenu_InsectVsMenuEnterRecordStep_4f0530();
                        insmenu_InsectVsRegPwPanelFadeOut_4f05e0();
                    }
                } else if (a17 == 0x3D) {
                    if (a16 == 0x263) {
                        if (sp74 == 0x26A) {
                            func_431310(o->field24, 2);
                            func_431110(o->field24, 0x14);
                            func_430DB0(o->field24, 0xCA);
                            s = func_430B90(o->field24);
                            s->field00 = 6;
                            s->field04 = 0x3D;
                            insmenu_InsectVsMenuEnterRecordStep_4efc20();
                            insmenu_InsectVsRegSavePanelFadeOut_4efcd0();
                        }
                    } else if (a16 == 0x269) {
                        func_430DB0(o->field24, 0x263);
                        func_431F60(func_430AF0(o->field24));
                        insmenu_InsectVsMenuEnterRecordStep_4efc20();
                        insmenu_InsectVsRegSavePanelFadeOut_4efcd0();
                    }
                } else if (a17 == 0x3E) {
                    if (a16 == 0x26D && sp74 == 0x270) {
                        func_431310(o->field24, 2);
                        func_431110(o->field24, 0x14);
                        func_430DB0(o->field24, 0xCA);
                        s = func_430B90(o->field24);
                        s->field00 = 6;
                        s->field04 = 0x3E;
                        insmenu_InsectVsMenuEnterRecordStep_4ef090();
                        insmenu_InsectVsRegTeamPanelFadeOut_4ef140();
                    }
                } else if (a17 == 0x3F) {
                    if (a16 == 0x277 && sp74 == 0x27B) {
                        func_431310(o->field24, 2);
                        func_431110(o->field24, 0x14);
                        func_430DB0(o->field24, 0xCA);
                        s = func_430B90(o->field24);
                        s->field00 = 6;
                        s->field04 = 0x3F;
                        insmenu_InsectVsMenuEnterRecordStep_4ef090();
                        insmenu_InsectVsRegTeamPanelFadeOut_4ef140();
                    }
                }
            }
        } else {
            if (a18 == 2) {
                if (a16 == 0xC9) {
                    insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
                    insmenu_InsectVsTopPanelFocus_4f2680();
                } else if (a16 == 0xCA) {
                    insmenu_InsectVsMenuEnterRecordStep_4f2350();
                    insmenu_InsectVsRegisterPanelFocus_4f1f80();
                }
            } else {
                insmenu_InsectVsBackGuideShow_4ea030();
                if (a18 == 3) {
                    if (a16 == 0x12D) {
                        insmenu_InsectVsMenuEnterRecordStep_4f1b10();
                        insmenu_InsectVsTwoPlayerPanelFocus_4f16a0();
                    } else if (a16 == 0x12E) {
                        func_28EDE0(&D_004842E8, 0x7538, 0);
                    }
                } else if (a18 == 4) {
                    if (a16 == 0x191) {
                        insmenu_InsectVsMenuEnterRecordStep_4f1040();
                        insmenu_InsectVsPwBattlePanelFocus_4f0bc0();
                    }
                } else if (a18 == 5) {
                    if (a16 == 0x1F5) {
                        insmenu_InsectVsMenuEnterRecordStep_4f1040();
                        insmenu_InsectVsWatchPanelFocus_4f0a00();
                    }
                } else if (a18 == 6) {
                    if (a17 == 0x3C) {
                        if (a16 == 0x259) {
                            insmenu_InsectVsMenuEnterRecordStep_4f1b10();
                            insmenu_InsectVsRegPwPanelFocus_4f00d0();
                        } else if (a16 == 0x25E) {
                            func_431310(o->field24, 2);
                            func_431110(o->field24, 0x14);
                            func_430DB0(o->field24, 0xCA);
                            s = func_430B90(o->field24);
                            s->field00 = 6;
                            s->field04 = 0x3C;
                            insmenu_InsectVsMenuEnterRecordStep_4f0530();
                            insmenu_InsectVsRegPwPanelFadeOut_4f05e0();
                        }
                    } else if (a17 == 0x3D) {
                        if (a16 == 0x263) {
                            insmenu_InsectVsMenuEnterRecordStep_4efc20();
                            insmenu_InsectVsRegSavePanelFocus_4ef7b0();
                        } else if (a16 == 0x269) {
                            func_431310(o->field24, 2);
                            func_431110(o->field24, 0x14);
                            func_430DB0(o->field24, 0xCA);
                            s = func_430B90(o->field24);
                            s->field00 = 6;
                            s->field04 = 0x3D;
                            insmenu_InsectVsMenuEnterRecordStep_4efc20();
                            insmenu_InsectVsRegSavePanelFadeOut_4efcd0();
                        }
                    } else if (a17 == 0x3E) {
                        if (a16 == 0x26D) {
                            insmenu_InsectVsMenuEnterRecordStep_4ef090();
                            insmenu_InsectVsRegViewPanelFocus_4eec60();
                        }
                    } else if (a17 == 0x3F) {
                        if (a16 == 0x277) {
                            insmenu_InsectVsMenuEnterRecordStep_4ef090();
                            insmenu_InsectVsRegDeletePanelFocus_4eeac0();
                        }
                    }
                }
            }
        }
    }
    return 1;
}
