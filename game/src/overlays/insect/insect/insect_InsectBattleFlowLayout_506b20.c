/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowLayout_506b20 1
#include "port/game_protos.h"
#line 1
/* insect 0x00506B20 -- 2,412 bytes.  CLOSED insect session 69 (2026-09-14).
 * The 0xB residue this park carried since ix24 (a $s0 web retail keeps from
 * the dispatch compare through cases 1 / 0x1B / 0x2F, COPIED into $a1 and
 * into $v1 before each case-0x2F `bne`) is a KNOWN-CONSTANT web that
 * constant propagation was eating: with `#pragma opt_propagation off` a plain
 * `kb = 0xB;` stays a register web, a later LITERAL 0xB is served from it by
 * copy (`move $v1,$s0 ; bne $v0,$v1`), and a literal's copy is created at
 * the use (so site 2's `move $a1,$s0` follows `move $a0,$s5`, where a named
 * `kb` there is created early and lands first).  The same pragma closed
 * normal_TransSaveWriteTickCb_518c60 ([[levers.d/mwcc-opt-propagation-pragma]]).  Under it
 * the only other effect in this function is that a `for (i = 0; i < 5; i++)`
 * keeps its entry test, so the three loops are `do { } while (++i < 5)`.
 * The s59 one-sided-if phi (`if (dsp != 0) kb = 0xB;`) is NOT needed and is
 * gone: it made the web's value UNKNOWN, which is exactly why the compares
 * used $s0 directly (one word short) and never took the copy.
 * Decks build/ix69/arms_506b20_ix69{a..h}_*.py (casts, case 0xB, const
 * objects, second definitions: all null; prop_off crosses: MATCH); residue
 * reads build/ix69/dis_506b20_*.txt; record build/ix69/FINDINGS.md.
 *
 * The ix68 / ix63 park headers follow (their "DO NOT MERGE" is historical).
 * ---------------------------------------------------------------------- */
/* !! ix63 PARK, DOES NOT MATCH: 4 bad of 603, EXACT length 0x96C, frame 0x90.
 * DO NOT MERGE.  18 -> 4 in one session, and the root the park had carried
 * since ix28 is CLOSED.
 *
 * ==== 1. THE 0xB WEB, VIA THE s59 ONE-SIDED-IF PHI (18 -> 10)
 *
 * build/ix63/offscan.py --imm (the NORMAL s44 IMMEDIATE screen, ported to
 * insect in s63 and never run on this image before) put this unit at the top
 * of the board with one line:  `addiu 0xb: retail 2 -> ours 6`.  That is this
 * park's own recorded root: retail materialises 0xB ONCE into $s0 and keeps
 * the web; we rematerialise it at every site.
 *
 * ix24/ix28/ix32/ix56 spent ~40 arms looking for "a spelling of 0xB that
 * constant propagation cannot follow" -- (s32)(u8*), (s64), (u64), (void*), a
 * null index, +0, the initialiser form, `register`, every decl position, and
 * seven opaque second definitions.  All inert; `#pragma opt_propagation off`
 * proved the mechanism but is whole-file and +7 words.
 *
 * The answer is the s59/s61/s62 ONE-SIDED-IF PHI, which postdates every one of
 * those attempts:
 *
 *     kb = 0xB;
 *     if (dsp != 0) { kb = 0xB; }
 *
 * mwcc does not fold it.  A plain `kb = 0xB;` is BYTE-IDENTICAL to base (the
 * old null re-confirmed as the deck's own control).
 *
 * ⚠ THE USE SET IS A SEPARATE AXIS FROM THE CONDITION, and they must be
 * crossed.  With kb at the guard + the two 0050d8c0 calls but NOT the case-0x2F
 * compares: `dsp != 0` / `g != 0` / `bb != 0` / `e != 0` are ONE object at 10
 * bad EXACT LENGTH, while the address-taken conditions `s8C`/`s88`/`s84`/`s80`
 * and `o->f5EF1` are 11-13 and ONE WORD LONG.  With the compares included the
 * same conditions read 16/-2 and 505/-1 respectively.  (On insect_InsectAiPlanScissorThrow_51f1d0
 * s61 found the opposite -- there the ADDRESS-TAKEN operand won.  The operand
 * class is per unit; sweep it.)
 *
 * ==== 2. `mm` MUST NOT BE A NAME (10 -> 4)
 *
 * Retail puts `nn` in $s1 and `mm` in $s0; we had them inverted, 6 words at
 * 0x005071D0-0x00507210.  NEITHER decl order NOR statement order reaches it:
 * the nn/kk/mm decl group is a TWO-object axis (nn-first 10, mm-first 12) and
 * all five statement permutations are 13-22.  DELETING the name does:
 *
 *     insect_InsectPieceLoadFromSource_515da0(o->m5B30, o->f5DA8, kk, nn,
 *                         insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(e),
 *                         insect_InsectTeamSlotGetEnemyRowMaybe_513e80(e));
 *
 * inlining `mm = insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(e);` into the argument list is 4 bad with
 * ZERO callee-saved, caller-saved and FPR substitutions.  ⚠ ix56's 123-arm
 * decl sweep read 93 byte-identical here; re-sweeping it under the new web was
 * right (the axis had changed) but it is STILL a null -- the lever was the
 * name's EXISTENCE, exactly as ix47 found on insect_InsectSeqExecAbiImpact_519760.
 *
 * ==== 3. THE LAST FOUR, and what does NOT move them (~35 arms)
 *
 * A. 0x00506F7C (case 0x1B): retail sets $a0 then $a1 at
 *    `insect_InsectBattleSetState_50d8c0(o, kb, 2, -1)`; we set $a1 then $a0.  A pure
 *    ARGUMENT-EVALUATION-ORDER transposition.  MEASURED NULL: `o->f4FBC &=`,
 *    a named temp for the read-modify-write, and `(s32)(u8)kb` are all
 *    byte-identical to this park (the cast adds one caller-saved sub);
 *    hoisting the RMW above the 511cf0 call is 12.
 * B. 0x00507374 / 0x0050738C (case 0x2F): retail COPIES the web into a
 *    caller-saved register before each `bne` (`daddu $3,$16,$0`); we emit
 *    `addiu $v1,$zero,11`.  Same LENGTH, different words.  ⚠⚠ EVERY spelling
 *    that gives the compare the web makes mwcc use $s0 DIRECTLY and come out
 *    ONE WORD SHORT PER SITE: `== kb` on one compare 5/-1, on both 10/-2,
 *    commuted `kb ==` and nested ifs identical to that, a `kc` copy 10/-2, a
 *    conditional-expression `kc = (dsp != 0) ? kb : kb;` 10/-2, a `kc` phi
 *    +3/580.  The target is the COPY, not the use, and nothing here reaches it.
 * ⚠ the conditional-EXPRESSION form of the kb phi itself is 12, so on this
 *   unit the STATEMENT phi and the ?: phi are NOT the same lever (s62 saw the
 *   same split on insect_InsectAiPlanScissorThrow_51f1d0).
 * ⚠ a SECOND constant-0xB web (`kc = (dsp != 0) ? 0xB : 0xB;`) is folded into
 *   the first -- byte-identical to this park.
 *
 * Decks build/ix63/arms_506b20_ix63{b,c,d,e,f,g}_*.py, ~90 arms, every one with
 * both armc controls firing.  Full record build/ix63/FINDINGS.md.
 */
/* PARKED, NOT MATCHING -- do not merge.  ix56 (session 56, solo).
 * EXACT LENGTH 0x96c, frame 0x90, .text sha1 418b8b90, **18 bad of 603**
 * (ix42s parked this at 31).  Two edits, both from session 55's levers:
 *
 *   31 -> 29  `ret_ab`: an explicit `return;` at the end of BOTH `if (z !=
 *             NULL)` blocks in `case 0x1C` (the 0x80 and 0x20 sub-branches).
 *             005070B4 and 0050719C were the only two residue words that were
 *             NOT a register substitution -- retail branches straight to the
 *             epilogue at 507468, we branched to 507360, itself an
 *             unconditional branch to 507468.  mwcc threads only ONE
 *             predecessor of a shared exit (levers.d/mwcc-branch-likely-
 *             duplication); giving each sub-branch its own `return;` gives
 *             each its own threaded jump.  Writing the `return;` INSIDE the
 *             `if` and writing it after the closing `}` are the same object.
 *
 *   29 -> 18  `y1`: SPLIT `y` PER LIVE RANGE -- `case 0x1C`'s uses renamed to
 *             `y1`, `case 0x1E`'s left as `y`.  This is levers.d/insect-
 *             session55-levers verbatim: a name with several live ranges is
 *             several vregs created where they are WRITTEN, so declaration
 *             order cannot order it, and eleven words of $s0/$s1 fall out on
 *             the split alone.  Splitting the OTHER range (`y2`) is the same
 *             object, as is doing both.
 *
 * MEASURED NULLS THIS SESSION, controls (IXCTL=insect_InsectSeqGetSubState_4ea330) firing
 * `_pos MATCH` / `_neglen ?` in every deck:
 *   - deck F, the whole-list decl sweep across the pointer/scalar boundary:
 *     `t`,`nn`,`mm`,`idx`,`y1`,`z` x all 21 slots, 123 arms, 93 BYTE-IDENTICAL
 *     to base, nothing better.  ix42s's "moving the decls is catastrophic"
 *     was measured on the five POINTERS as a group; the names the residue
 *     actually names are simply INERT.
 *   - deck G, the s55 SPLIT x DECL-SLOT CROSS: `t` split three ways plus `z`
 *     and `u`, each new name swept through all 21 slots, 110 arms, 100
 *     byte-identical.  The cross that paid 10 words on 0050c4b0 pays nothing
 *     here.
 *   - deck H, group C of the compiler's own pragma table, `off` alone and
 *     level-first, x the named `kb = 0xB`: `common_subs`, `loop_invariants`,
 *     `propagation` are all WRONG LENGTH; `dead_assignments`, `dead_code`,
 *     `strength_reduction` byte-identical; `lifetimes` = 213 bad.  `kb` alone
 *     is byte-identical, reproducing ix24's null at the new base.
 *   - deck I, `case 0xB:` put back (ix32 dropped it): 21 bad as the only arm,
 *     64 with it first, and +2 words if the early `if` is kept as well.  It
 *     DOES build the register web -- one of 506B8C/B90 matches -- but it
 *     moves the branch-likely duplication off the first compare.
 *   - deck J, ten backend optimiser names x on/off x `kb`, 44 arms, ARMED BY
 *     COMPILER ERROR (`opt_unroll_count off` = NOOBJ): 34 of 40 byte-identical.
 *     s52's "the 56 backend names are a measured null" now holds on a SECOND
 *     unit.
 *   - deck K, **the `register` STORAGE CLASS IS COMPLETELY INERT**: `register`
 *     on `kb`, `t`, `nn`, `mm`, `base`, `y1`, `z` and on `t`+`nn` together,
 *     plus initialiser-vs-assignment and two decl positions for `kb` -- 12
 *     arms, EVERY ONE byte-identical to base.  levers.d/mwcc-allocator-
 *     decompiled lists the register HINT as an unswept allocator input; C's
 *     `register` does not write it.
 *
 * THE 18 THAT REMAIN ARE ONE ROOT.  Retail materialises 0xB ONCE into $s0 at
 * the dispatch compare (00506B8C `addiu $s0,$zero,11` / `beql $v0,$s0`) and
 * keeps that web for all five uses -- the two `insect_InsectBattleSetState_50d8c0(o,0xB,2,-1)`
 * argument passes at 00506CC4 and 00506F80 and the two `== 0xB` compares in
 * case 0x2F at 00507374/50738C -- while we rematerialise `addiu ...,$zero,11`
 * at each (7 words).  Because that web is created BEFORE any arm-local it
 * takes $s0 and pushes `t` (case 1, 5 words) and `nn`/`mm` (case 0x1C's 0x10
 * branch, 6 words) up to $s1, which is the other 11.  Establish the web and
 * the unit closes.
 *
 * Deck H proved the mechanism directly: `#pragma opt_propagation off` makes
 * the named `kb` a REAL web -- `kb` + the pragma is 0x980 where the pragma
 * alone is 0x988, two words cheaper -- so constant propagation is exactly what
 * eats `kb`.  The pragma itself is +7 words of length and `opt_*` has no
 * sub-function scope, so it is not shippable.  What is left is a source
 * spelling of 0xB that propagation cannot follow: ix24 tried (s32)(u8 *),
 * (s64), (u64), (void *), a null index and +0; this session added the
 * initialiser form, `register`, and every decl position.  All inert.
 */
/* !! ix32 PARKED DRAFT -- EXACT LENGTH, 37 bad. DO NOT MERGE.
 * 40 -> 37 in ix32: bind the dispatch value to a local and test 0xB BEFORE the
 * switch (`dsp = insect_InsectBattleGetStep_50d6a0(o, 0); if (dsp == 0xB) return;`), dropping
 * the now-dead `case 0xB:` arm.  This was ix28's own listed UNTRIED idea.
 * ⚠ KEEPING the dead arm as well is +2 words (0x974 vs 0x96c).
 *
 * IT DOES NOT REACH THE CORE DEFECT, which is unchanged from ix28: retail holds
 * 0xB in $s0 across the whole function (s0>s1:11, s1>s0:7 survive every arm).
 * NEW MEASURED NULLS this session, at the 40 baseline:
 *   * binding the dispatch value alone (`dsp = ...; switch (dsp)`) is
 *     BYTE-IDENTICAL to base -- the switch subject is not the axis;
 *   * ARM ORDER is live and WORSE: `case 0xB` written immediately before
 *     `case 0x1D` is 42, folded onto the same label 42 (same object), and
 *     hoisted to the FIRST arm 83.  So the 0xB/0x1D branch-likely swap is not
 *     reachable by reordering the arms ([[levers.d/mwcc-branch-likely-duplication]]
 *     fix 3 does not fire here).
 * Still untried: forcing a WEB for 0xB by a route constant propagation cannot
 * undo -- ix28 spent seven opaque integer second definitions and all were
 * byte-identical, so it needs a value that is not a compile-time constant.
 */
/* !! PARKED, DOES NOT MATCH: EXACT LENGTH, 40 bad. DO NOT MERGE.  -- ix28, 2026-09-02.
 * ix24 parked this at 199 as "a pure callee-saved rename, parked by rule" after an
 * exhaustive 119-permutation sweep of the five pointer declarations.  Two arms took it
 * to 40:
 *   1. `y = insect_InsectTeamGetPiece_5138d0(base, idx); y = (Node *)(s32)y;`  (case 0x1C) -- the
 *      pointer->integer->pointer ROUND TRIP keeps y a NAMED WEB instead of a propagated
 *      call-result temp; that alone moved the PARAMETER o from $19 to retail's $21 and
 *      took 199 -> 60.  The same round trip on z, the case-0x1E y, idx, kk, hnd, c, nn,
 *      mm, g is inert or worse; on bb it rotates the map the wrong way.
 *   2. declaration order g, e, bb, base, pv = retail's registers DESCENDING
 *      ($20 $19 $18 $17 $17): 60 -> 40.  ix24's 119-permutation "floor" was measured
 *      UNDER the y-temp promotion, which is why it never saw this cell.
 * THE 40 THAT REMAIN are ONE FACT: retail holds the constant 0xB in $16 from the
 * dispatch compare (`addiu $16,$0,0xB / beql $2,$16`) through case 1, 0x1B and 0x2F
 * (five uses), so every arm-local we put in $16 sits in $17 there, and the 0xB/0x1D
 * return-branches swap their branch-likely slot.  A named `kb = 0xB` is constant-
 * propagated at every declaration position and under seven "opaque" integer second
 * defs ((s32)(u8 *), (s64), (u64), (void *), null-index, +0): all byte-identical.
 * Untried: dispatching through an `if (n == 0xB) return;` before the switch. */
#include "types.h"
#pragma opt_propagation off
#pragma divbyzerocheck on
/* insect 0x00506B20 -- 2,412 bytes, 603 instructions, 98 calls, 45 conditional
 * branches.  ix24e2.
 *
 * NOT a jump table: an 18-arm `beql`-dispatched switch on
 * insect_InsectBattleGetStep_50d6a0(o, 0).  Per [[insect-dispatch-branch-polarity]] a `beql`
 * INTO the arm is a switch and the COMPARE CHAIN IS THE REVERSE of the source
 * case order, so the source order is
 *   1  47  4C  46  4D 48  4E 49  4F  50  4A  4B  1B  1C  2F  1D  1E  B
 * which is exactly the ADDRESS order of the arm bodies.  Five of the arms
 * (47 4C 46 1D B) are empty `break;`s and cost 3 words each.
 *
 * `bnez $16 / div / break 0,7` at 00506E60 is `#pragma divbyzerocheck on`.
 *
 * `$17`/`$19` are `&o->m35F8[o->f5EF1]` (stride 0x994) and
 * `&o->m4920[o->f5EF1]` (stride 0x20); `$18` doubles as `o + 0x4B4C` and as
 * the 0xA in the 0x1C arm, which is why 0xA is a NAMED LOCAL there and not a
 * literal (retail materialises it twice, once per path).
 */

typedef struct E20 {
    u8  pad00[0x0F];
    s8  f0F[5];                         /* +0x0F */
    u8  pad14[0x20 - 0x14];
} E20;

typedef struct B994 {
    u8  pad00[0x994];
} B994;

typedef struct Node {
    u8  pad00[0x6C];
    s16 f6C;                            /* +0x6C */
    u8  pad6E[0x1E8 - 0x6E];
} Node;

typedef struct Obj {
    u8   pad0000[0x35F8];
    B994 m35F8[2];                      /* +0x35F8 */
    E20  m4920[2];                      /* +0x4920 */
    u8   m4960[0x4B4C - 0x4960];        /* +0x4960 */
    u8   m4B4C[0x4F90 - 0x4B4C];        /* +0x4B4C */
    u8   m4F90[0x4FBC - 0x4F90];        /* +0x4F90 */
    u8   f4FBC;                         /* +0x4FBC */
    u8   pad4FBD[0x5058 - 0x4FBD];
    u8   m5058[0x5B30 - 0x5058];        /* +0x5058 */
    u8   m5B30[0x5D18 - 0x5B30];        /* +0x5B30 */
    s32  f5D18;                         /* +0x5D18 */
    u8   pad5D1C[0x5D30 - 0x5D1C];
    s32  f5D30;                         /* +0x5D30 */
    u8   pad5D34[0x5D38 - 0x5D34];
    s32  f5D38;                         /* +0x5D38 */
    u8   pad5D3C[0x5D48 - 0x5D3C];
    s32  f5D48;                         /* +0x5D48 */
    u8   pad5D4C[0x5D60 - 0x5D4C];
    s32  f5D60;                         /* +0x5D60 */
    u8   pad5D64[0x5D68 - 0x5D64];
    s32  f5D68;                         /* +0x5D68 */
    u8   pad5D6C[0x5D78 - 0x5D6C];
    s32  f5D78;                         /* +0x5D78 */
    u8   pad5D7C[0x5DA8 - 0x5D7C];
    s32  f5DA8;                         /* +0x5DA8 */
    u8   pad5DAC[0x5EF1 - 0x5DAC];
    u8   f5EF1;                         /* +0x5EF1 */
    u8   pad5EF2[0x5EF8 - 0x5EF2];
    s32  f5EF8;                         /* +0x5EF8 */
} Obj;

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

void insect_InsectBattleFlowLayout_506b20(Obj *o)
{
    s32   s8C;                          /* $sp+0x8C */
    s32   s88;                          /* $sp+0x88 */
    s32   s84;                          /* $sp+0x84 */
    s32   s80;                          /* $sp+0x80 */
    s32   s7C;                          /* $sp+0x7C */
    s32   s78;                          /* $sp+0x78 */
    u8   *g;
    E20  *e;
    u8   *bb;
    B994 *base;
    u8   *pv;
    Node *z;
    Node *y;
    Node *y1;
    void *hnd;
    s32   t;
    s32   u;
    s32   i;
    s32   n;
    s32   m;
    s32   c;
    s32   j;
    s32   idx;
    s32   nn;
    s32   kk;
    s32   mm;
    s32   dsp;
    s32   kb;

    insect_InsectCursorSetGetCell_511a40(o->m4F90, 8, &s8C, &s88);
    g = o->m4960;
    bb = o->m4B4C;
    e = &o->m4920[o->f5EF1];
    base = &o->m35F8[o->f5EF1];
    dsp = insect_InsectBattleGetStep_50d6a0(o, 0);
    kb = 0xB;
    if (dsp == kb) {
        return;
    }
    switch (dsp) {
    case 1:
        t = 0x4C;
        insect_InsectBattleSetFlag_50dad0(o, 0x1E);
        if (insect_InsectTeamSlotIsLayoutDone_513ed0(e) != 0) {
            t = 0x47;
            insect_InsectCursorSetPushPage_511cf0(o->m4F90, 7, 1);
        } else {
            insect_InsectBattleSetFlag_50dad0(o, 0x11);
        }
        insect_InsectBattleSetStep_50d7a0(o, t, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, kb, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, t, 2, -1);
        return;
    case 0x47:
    case 0x4C:
    case 0x46:
        return;
    case 0x4D:
    case 0x48:
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetStep_50d6a0(o, 0) + 1, 0, -1);
        return;
    case 0x4E:
    case 0x49:
        t = -1;
        insect_InsectCursorSetGetCurCell_511a90(o->m4F90, &s8C, &s88);
        if (insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x80) != 0) {
            t = s8C;
        }
        if ((insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x20) != 0) && (t == -1)) {
            t = 1;
        }
        if (t != -1) {
            n = insect_InsectBattleGetStep_50d6a0(o, 0) + 1;
            m = 6;
            if (t == 0) {
                n = n + 1;
                m = 5;
            } else {
                i = 0;
                do {
                    e->f0F[i] = -1;
                } while (++i < 5);
            }
            insect_InsectBattleSetStep_50d7a0(o, n, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x46, 0, -1);
            insect_InsectBattlePlaySe_4f45b0(o, m);
        }
        return;
    case 0x4F:
        insect_InsectCursorSetPushPage_511cf0(o->m4F90, 8, 1);
        insect_InsectBattleCamSave_4f1b50(o);
        insect_InsectBattleSetStep_50d7a0(o, 0x1B, 0, -1);
        return;
    case 0x50:
        insect_InsectBattleCamSave_4f1b50(o);
        o->f5EF8 = 8;
        pv = o->m5058;
        c = insect_InsectFormationGetCount_4efdb0(pv);
        j = Rand_133710() % c;
        if (j >= c) {
            j = 0;
        }
        hnd = insect_InsectFormationGetRow_4efdc0(pv, j);
        i = 0;
        do {
            insect_InsectFormationDecodeCell_4effa0(hnd, i, &s84, &s80, o->f5EF1);
            if (o->f5EF1 == 0) {
                s80 = s80 - 5;
            }
            insect_InsectTeamSlotSetCell_5140c0(e, i, s84, s80);
        } while (++i < 5);
        insect_InsectBattleSetStep_50d7a0(o, 0x4B, 0, -1);
        return;
    case 0x4A:
        insect_InsectTeamSlotClearLayout_514210(e);
        insect_InsectBattleSetStep_50d7a0(o, 1, 0, -1);
        return;
    case 0x4B:
        o->f4FBC = o->f4FBC | 2;
        insect_InsectBattleSetState_50d8c0(o, 0xC, 0, -1);
        return;
    case 0x1B:
        o->f5EF8 = 8;
        insect_InsectBattleClearFlag_50da90(o, 0x27);
        insect_InsectCursorSetPushPage_511cf0(o->m4F90, 8, 0);
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBattleSetState_50d8c0(o, 0xB, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        return;
    case 0x1C:
        z = ((Node *)insect_InsectTeamGetPiece_5138d0(base, s88));
        if (insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x80) != 0) {
            if (z != NULL) {
                u = 0xA;
                t = 1;
                if (insect_InsectPieceTestStatus_513280(z, 0x21) != 0) {
                    insect_InsectBoardFindPiece_4ee190(g, z, &s7C, &s78);
                    if (o->f5EF1 == 0) {
                        s78 = s78 - 5;
                    }
                    insect_InsectCursorSetPageSetCell_511c20(o->m4F90,
                                        ((s32)insect_InsectCursorSetFindPage_511e60(o->m4F90, 9)),
                                        s7C, s78);
                    insect_InsectTeamSlotPlaceOrderRemove_513fa0(e, s88);
                    u = 0xA;
                    t = 0x1B;
                    insect_InsectPieceClearStatus_513340(z, 0x21);
                    insect_InsectBoardRemovePiece_4ef7f0(g, z);
                }
                o->f4FBC = o->f4FBC | 2;
                insect_InsectBattleSetState_50d8c0(o, u, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, t, 0, -1);
                insect_InsectBattlePlaySe_4f45b0(o, 5);
                return;
            }
        } else if (insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x20) != 0) {
            if (z != NULL) {
                idx = ((signed char)insect_InsectTeamSlotPlaceOrderPop_514020(e));
                if (idx != -1) {
                    y1 = ((Node *)insect_InsectTeamGetPiece_5138d0(base, idx));
                    y1 = (Node *)(s32)y1;
                    if (insect_InsectPieceTestStatus_513280(y1, 0x21) != 0) {
                        insect_InsectPieceClearStatus_513340(y1, 0x21);
                        insect_InsectBoardRemovePiece_4ef7f0(g, y1);
                        insect_InsectModelMemReleasePiece_512400(bb, y1->f6C);
                        insect_InsectTeamSlotClearCell_5140b0(e, idx);
                    }
                } else {
                    o->f5D18 = 9;
                    o->f5D48 = 0x1E;
                    o->f5D30 = 9;
                    o->f5D60 = 0x1B;
                    o->f5D38 = 0xB;
                    o->f5D68 = 0xA;
                    o->f5D78 = 0x5DD;
                    insect_InsectBattleSetState_50d8c0(o, 0x25, 0, -1);
                }
                insect_InsectBattlePlaySe_4f45b0(o, 6);
                return;
            }
        } else {
            if (insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x10) != 0) {
                insect_InsectPieceReset_514740(o->m5B30);
                if (((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(e)) == -1) {
                    nn = insect_InsectTeamSlotGetMember_513eb0(e, s88);
                } else {
                    nn = s88;
                }
                kk = o->f5EF1;
                insect_InsectPieceLoadFromSource_515da0(o->m5B30, o->f5DA8, kk, nn,
                                    ((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(e)),
                                    ((short)insect_InsectTeamSlotGetEnemyRowMaybe_513e80(e)));
                insect_InsectBattleSaveState_50d650(o, 0);
                insect_InsectBattleSaveStep_50d600(o, 0);
                insect_InsectBattleSaveState_50d650(o, 2);
                insect_InsectBattleSaveStep_50d600(o, 2);
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                insect_InsectBattleSetState_50d8c0(o, 0xD, 1, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x2F, 0, -1);
                insect_InsectCursorSetPushPage_511cf0(o->m4F90, 0, 1);
                insect_InsectBattlePlaySe_4f45b0(o, 5);
                return;
            }
            if ((insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x40) != 0) &&
                (insect_InsectBattleTestFlag_50da40(o, 2) == 0)) {
                insect_InsectBattleSaveState_50d650(o, 0);
                insect_InsectBattleSaveStep_50d600(o, 0);
                insect_InsectBattleSaveState_50d650(o, 2);
                insect_InsectBattleSaveStep_50d600(o, 2);
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                insect_InsectBattleSetState_50d8c0(o, 0xE, 1, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x30, 0, -1);
                insect_InsectCursorSetPushPage_511cf0(o->m4F90, 6, 1);
                insect_InsectBattlePlaySe_4f45b0(o, 5);
            }
        }
        return;
    case 0x2F:
        if ((insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) &&
            (insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB)) {
            insect_InsectBattleSetState_50d8c0(o, 0x1B, 0, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x1C);
            o->f4FBC = o->f4FBC & 0xFD;
        }
        break;
    case 0x1D:
        return;
    case 0x1E:
        y = ((Node *)insect_InsectTeamGetPiece_5138d0(base, 0));
        i = 0;
        do {
            if (insect_InsectPieceTestStatus_513280(y, 0x21) != 0) {
                insect_InsectPieceClearStatus_513340(y, 0x21);
                insect_InsectBoardRemovePiece_4ef7f0(g, y);
                insect_InsectModelMemReleasePiece_512400(bb, y->f6C);
                insect_InsectTeamSlotClearCell_5140b0(e, i);
            }
            y = (Node *)((u8 *)y + 0x1E8);
        } while (++i < 5);
        insect_InsectTeamSlotRemoveMember_514100(e, insect_InsectTeamSlotGetMember_513eb0(e, 4));
        insect_InsectBattleSetFlag_50dad0(o, 0xF);
        insect_InsectBattleSetState_50d8c0(o, 6, 0, -1);
        return;
    }
}
