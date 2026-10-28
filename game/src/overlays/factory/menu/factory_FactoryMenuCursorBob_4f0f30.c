/* rgp:protos */
#define RGP_SELF_factory_FactoryMenuCursorBob_4f0f30 1
#include "port/game_protos.h"
#line 1
/* ====================================================================
 * SESSION 57 (2026-09-03), tag fg57 / bulk tag ba57a.  CLOSED -- BYTE-IDENTICAL
 * at the link (md5 516db788c32c, 109 w; the sweeper's raw score is 1 because
 * this object's own .lit4 word is retargeted by f_olink/t_lit4, exactly as
 * insmenu's last 15 were).  Arming pair 005069e0 = MATCH / 1a0e9c68216b and
 * 005032d0 = MATCH / 29791c8bcf44; the same bulk run reproduced A000_ident =
 * 174f4deaf58f, A001_f14left = 5b2595a2f978 and s37's C3 = 88d37a8b5f07 / 112 w.
 *
 * === THE LEVER: a volatile-pinned HOISTED read of f08 into an s16 local ===
 *     s16 q;
 *     q = *(volatile s16 *)&r->f08;             <- hoisted ONE statement up
 *     x = (s32)(t + (f32)(r->f04 + r->f14 * q));   <- f14 written LEFT
 * The s53 lever (005032d0) plus the TYPE of the pinned local.  s23 had run the
 * same pin into an s32 local (`y`) and read 11 bad -- "the pinned local is
 * promoted out of the expression-temp pool and lands in $8".  That was the
 * TYPE, not the pin: an s32 local holds the sign-extended lh result as a
 * distinct value and stays live into $8; an s16 local IS the lh result, the
 * load is created first (rd = the first-created dying operand's register, a3),
 * f14 is the left operand (rs = a0), and the mult word is retail's 00873818.
 * `s64 q` with `(s32)q` at the use is the same object (narrowing conversion,
 * s37's lever); `u16 q` is 1 bad (lhu); `s32 q` is the 10-bad object.
 * Read as a rule: s56's 6-cell truth table was right about rs (= the left C
 * operand) and about "an extra use pulls the load earlier", but rd is the
 * FIRST-CREATED dying operand's register, not rs's -- and a pinned read is a
 * creation without a use.  The "three mutually contradictory requirements"
 * were two.
 * Batch: 93 arms, build/fg57/s57/mk57_0f30.py, log build/fg57/logs/
 * s57_e0f30.txt.  Everything that re-spells the multiply, folds an earlier
 * read (void/bare/if-empty/dead local/if(0)/q-q), or pins through a volatile
 * pointer is one of the two known objects; only the typed pinned local moves.
 ==================================================================== */
/* ====================================================================
 * SESSION 56 (2026-09-03), tag fg56 / bulk tags ba56q ba56r ba56s.  STILL
 * 2 / 174f4deaf58f, 109 w -- RE-DERIVED at start.  ARMING PAIR CHANGED this
 * session because 00500450 was under sweep: 005069e0 = MATCH / 1a0e9c68216b
 * AND 005032d0 = MATCH / 29791c8bcf44, held in every tree-based scoring run
 * (swb56.py).  bulkarm.py carries no arming units; its arming proof is the
 * 14-arm battery on the CLOSED 005032d0 (below) plus a cross-check of two
 * non-identity arms through swb56.py.
 * RECORDED-LIVE DELIVERY CELL, established this session because this unit had
 * none: x0f30/L1_mm_14_pre (r->f14 written LEFT) = 5b2595a2f978 / 4 bad /
 * 109 w, reproduced by BOTH harnesses in the same run.
 *
 * === THE RESIDUE, RE-DERIVED FROM THE OBJECTS (not from this header) ===
 * Read with asm-listing-word-mnemonics in hand: there are NO phantom hunks
 * here, the two cvt.w.s cells are byte-EQUAL.  Exactly two words differ:
 *   w2   retail lwc1 $f1,-32160(gp)   ours lwc1 $f1,0(gp)
 *   w35  retail 00873818 = mult rd=a3 rs=a0 rt=a3
 *        ours   00e43818 = mult rd=a3 rs=a3 rt=a0
 * The two operand LOADS are byte-identical -- w30 `lh a3,8(v0)` = r->f08
 * FIRST, w32 `lh a0,20(v0)` = r->f14 SECOND -- and rd = a3 in both.  So the
 * whole real residue is WHICH OPERAND REGISTER IS WRITTEN IN THE rs FIELD,
 * with the allocation already retail's.  (dis.py hides the EE 3-operand rd;
 * decode the word.)
 *
 * === ★★★ THE MECHANISM, a 6-cell truth table read off the objects ===
 * The control is inside this function: the y statement's `mult1` (w42,
 * 70a21018, rd=v0 rs=a1 rt=v0) is BYTE-CORRECT, and there rd == rt because
 * f16's register stays live for the `r->f16 == 7` guard.  Probing x by making
 * an operand live past the multiply (semantics-CHANGING arms, never delivery
 * candidates -- M_live*):
 *   both operands die, f08 left  -> rs=a3 rd=a3      (= rs, the left/first)
 *   both operands die, f14 left  -> rs=a3 rd=a3      (loads SWAP, mult word
 *                                                     IDENTICAL: 3 bad + lit4)
 *   f08 live, f08 left           -> rs=t0 rd=a2 = rt (f14 dies, takes rd)
 *   f08 live, f14 left           -> f08 loaded FIRST anyway; rs=a2 rd=a2
 *   f14 live, f08 left           -> f14 loaded FIRST; rs=a2 rd=a2
 *   f14 live, f14 left           -> rs=t0 rd=a2 = rt  <- RETAIL'S STRUCTURE
 *   BOTH live                    -> the product takes a THIRD register
 * ⇒ THE RULES: (1) rs is ALWAYS the LEFT C operand; (2) rd is the register of
 * a DYING operand and, when both die, rd = rs; (3) an EXTRA USE of a value
 * pulls its load EARLIER.  Retail needs f08 loaded first AND f14 written left
 * AND f14 not dead at the multiply -- i.e. an extra use of f08 (to load it
 * first) and an extra use of f14 (to keep it live) -- and with both, rule (2)
 * gives the product a third register.  The combination is NOT REACHABLE.
 * PARKED on that, not on a guess.
 *
 * === THE SPELLING LATTICE: 197 ARMS, EXACTLY TWO OBJECTS ===
 * 4 plain access spellings x 4 x 2 operand orders x 2 addend positions (64),
 * plus every pairing involving a SECOND `Rec *`, an `s16 *` ARRAY VIEW or a
 * LAUNDERED pointer, at both alias-declaration ends (132).  Result:
 *   174f4deaf58f  2 bad  n=99   every cell with f08 written LEFT
 *   5b2595a2f978  4 bad  n=98   every cell with f14 written LEFT
 * The alias axis -- reading the two operands through DIFFERENT bases, which
 * no earlier session tried -- is COMPLETELY INERT.  s23's "the crossed
 * combination cannot come from any operand order" is upheld with a 197-cell
 * denominator and a mechanism instead of an inference.
 *
 * === THE PRAGMA SURFACE: 6,592 ARMS, NONE BETTER ===
 * `build/ti-pragmas-valid.txt` (title's recorded 244 names) NO LONGER EXISTS
 * in this tree, so the namespace was re-derived rather than inherited: every
 * lowercase identifier in mwccps2.exe (3,280) in BOTH polarities, plus the
 * numeric-grammar family.  35 NOBUILD, 6,557 scored, 15 LIVE, ZERO better.
 * `opt_arithtransformation off` is exact length at 3 bad; `optimization_level`
 * 3 and 4 are INERT and 0/1/2 break length; `schedule off` = level 2's object.
 * ⚠ bulkarm needs `timeout` on the remote compile -- the namespace still
 * contains the recorded input-dependent hang.
 *
 * === THE .lit4 WORD: BOTH HALVES ARE NOT SIMULTANEOUSLY REACHABLE ===
 * w2's gp target is 0x0047D3D0 = 0.1570796371f (pi/20), mwcc's float literal
 * pool, already declared `extern f32 D_0047D3D0` in normal_BtlChgMenuItemTargetCursorBobCb_4fd540.c.
 * Writing the extern gives retail's EXACT displacement (`lwc1 $f1,-32160(gp)`)
 * and SINKS the load from w2 to w9 -> 8 bad (10 with f14 left).  The literal
 * keeps retail's SCHEDULE and takes its own .lit4, which f_olink retargets.
 * That is insmenu's recorded direction confirmed on a second overlay.  INERT:
 * a local `const f32`, a file-scope `static const f32`, `1.5707964e-1f`,
 * `(f32)0.15707963705062866`, `3.1415927f / 20.0f`, `3.1415927f * 0.05f`.
 *
 * Generators build/fg56/s56/mk56_0f30{,b}.py; logs build/fg56/logs/
 * s56_x0f30.txt, s56_y0f30.txt, s56_prag0f30.txt.  Full detail:
 * memory levers.d/factory-session56-levers.md.
 ==================================================================== */
/* ====================================================================
 * SESSION 52 (2026-09-03), tag fg52 (secondary lane; 005050c0 CLOSED this
 * session).  STILL 2 / 174f4deaf58f, re-derived with the arming pair
 * 005069e0 = MATCH and 005032d0 = 7 / d7c9a6c54435 (00500450 was under sweep).
 * SIX arms that make the RIGHT operand evaluate first ALL fold to the known
 * f14-left object 5b2595a2f978 (4 bad): `static inline s32 mul16(a,b){return
 * b*a;}` with s32 or s16 params and either argument order (M1/M2/M1b), an
 * assignment inside the right operand `r->f14 * (q = r->f08)` (M3), the
 * product in a named local first (M7), `q = r->f08;` then `r->f14 * q` (M8).
 * Inline arguments, in-expression assignments and plain copies are all
 * propagated before operand selection; the only decision left is which
 * operand is written on the LEFT.  Logs build/fg52/logs/s52_0f30_b1.log.
 ==================================================================== */
/* ====================================================================
 * SESSION 49 (2026-09-03), tags fg49/fg49b/fg49c/fg49k.  Board unchanged 400/409 = 97.80% / 91.88%.  Baseline RE-DERIVED at start; arming pair held in EVERY scoring run (005069e0 = MATCH / 1a0e9c68216b, 00509f10 = bad 11 / 977182cbe9b7); every batch carried a cmp-verified identity arm AND a recorded-live delivery cell that reproduced its recorded md5.  Full detail: memory levers.d/factory-session49-levers.md; arms build/fg49/arms/s49/, generators build/fg49/s49/, logs build/fg49/logs/s49_*.log.
 *
 * === factory_FactoryMenuCursorBob_4f0f30: STILL 2 / 174f4deaf58f (1 real word + .lit4).  Integer-cast operand spellings FOLD AWAY ===
 * `r->f14 * *(s16 *)((s32)r + 8)`, `((u8 *)r + 8)`, `*(s16 *)((s32)r + 0x14) * r->f08`, both operands cast, and
 * `r->f14 * r->f08 + r->f04` are ALL the recorded 4-bad object 5b2595a2f978 (f14 left); `r->f08 * *(s16 *)((s32)r + 0x14)`
 * and `r->f08 * r->f14 + r->f04` are the baseline.  Nine arms = ONE pair of objects decided solely by which operand is
 * written on the LEFT: mwcc loads the left operand first and makes it rs, and the integer-add cast is folded straight
 * back into the lh displacement.  Retail's crossed form (rs = f14 loaded second, rd = rt = f08 loaded first) is
 * unreachable in a 40+ cell lattice.  Decode the words, not the listing: dis.py prints the EE 3-operand mult as
 * `mult a0,a3` and hides rd; the y-statement multiply is `mult1` (0x70a21018) in both objects.
 * C++ (whole file extern "C"): BYTE-IDENTICAL.
 * ==================================================================== */
/* ====================================================================
 * SESSION 37 (2026-09-02), lane fg37f.  Board 393 -> 396/409 = 96.82% count,
 * 120,424/134,224 = 89.72% bytes.  Arming pair held in EVERY scoring run:
 * factory_FactoryStep_5069e0 = MATCH, factory_FactoryRectFrameCorner_509f10 = bad 11 / md5 977182cbe9b7.
 * "INERT" below means the arm's object md5 EQUALS this unit's baseline md5.
 *
 * === factory_FactoryMenuCursorBob_4f0f30 (12 cells, baseline 174f4deaf58f, 2 bad = 1 real word + 1 .lit4) ===
 * A1 named local `k7 = 7;` OPENING the case-0 block (before `r = ...`), k7 declared FIRST, guard `r->f16 == k7` -- INERT 174f4deaf58f
 * A2 same, k7 declared LAST -- INERT 174f4deaf58f
 * A3 `k7 = 7;` after `r = func_28EA40(...)`, k7 declared FIRST -- INERT 174f4deaf58f
 * A4 `k7 = 7;` between the x and y statements, k7 declared FIRST -- INERT 174f4deaf58f
 * A5 the y statement placed BEFORE the x statement -- 777e1f62a128, 17 bad, exact length
 * A6 y + the `r->f16 == 7` guard before x (x last) -- e4e4d706997e, 28 bad, exact length
 * A7 `b4 = r->f04;` named out of the x expression, b4 declared FIRST -- INERT 174f4deaf58f
 * A8 same, b4 declared LAST -- INERT 174f4deaf58f
 * C1 `s64 q; q = r->f08;` then `r->f04 + r->f14 * (s32)q`, q declared FIRST -- 5b2595a2f978, 4 bad (the KNOWN f14*f08 object; the s64 does NOT block the fold)
 * C2 same, q declared LAST -- 5b2595a2f978, 4 bad
 * C3 same without the (s32) cast -- 88d37a8b5f07, NO LINK: unresolved __floatdisf, len 0x1c0 vs 0x1b4
 * C4 `s64 q; q = r->f14;` then `(s32)q * r->f08` -- 5b2595a2f978, 4 bad
 * => s34/s36's "rd = rt is not reachable from the multiply's SOURCE FORM" UPHELD a third time. NEW BOUNDS: (a) the s35 named-local-constant lever is INERT here at all three statement positions and both declaration ends -- the `addiu $3,$0,7` sits between the two operand loads but never competes for $7/$4; (b) session 37's narrowing-conversion instrument (s64) does not reach it either; (c) the block-OPENER axis is live but strictly worse (17 / 28). Both s36 twists are class-MISMATCHED here: the two operand loads are already byte-identical to retail (no load-coalesce residue) and there is no callee-saved substitution anywhere in the unit.
 ==================================================================== */

#include "types.h"

/* SESSION 23, lane fz23j -- 2 bad, EXACT LENGTH, UNCHANGED.  Read this before
 * touching the 0x004F0FBC `mult` again.
 * The residue is TWO words, one of them LINK-ADJUDICABLE:
 *   0x004F0F38 ours C7810000 / retail C7818260 -- lwc1 $f1, low 16 bits only,
 *     register fields identical: this object's own .lit4, f_olink retargets it.
 *   0x004F0FBC ours 00E43818 mult $7,$7,$4 / retail 00873818 mult $7,$4,$7.
 * NEW MEASUREMENT that reframes the whole residue: in the `f14 * f08` arm the
 * SCHEDULE IS IDENTICAL to retail -- both emit `lh $7,..` at 0x004F0FA8 and
 * `lh $4,..` at 0x004F0FB0.  Only WHICH VALUE gets which register differs:
 *   ours    $7=f14 (first evaluated) $4=f08, mult rd=$7 coalesced with rs
 *   retail  $7=f08 (first evaluated) $4=f14, mult rd=$7 coalesced with rt
 * So rd ALWAYS coalesces with the FIRST-EVALUATED operand's register, and the
 * first-evaluated is always the LEFT C operand.  Retail needs left=f14 with
 * f08 evaluated first -- the crossed combination -- so it cannot come from any
 * operand order.  The f08 load must be emitted by something that is NOT the
 * multiply's operand.
 * MEASURED INERT / WORSE this lane (all at exact length):
 *  - `y = *(volatile s16 *)&r->f08;` then `r->f14 * y`  -> 11 bad.  The pin
 *    DOES buy retail's operand assignment (rs=f14, f08 evaluated first) but the
 *    pinned local is promoted out of the expression-temp pool and lands in $8,
 *    shifting f14 to $6 and f04 to $7 (retail $4 and $6).  This REPRODUCES the
 *    earlier `p` result: a volatile-pinned local takes $8 no matter which local
 *    it is -- reusing an EXISTING local (y, which ends in $7) does not help.
 *  - `r->f14 * ((s16 *)r)[4]` (the two-spellings lever on the RIGHT operand)
 *    -> 4 bad, byte-identical to the plain `r->f14 * r->f08` arm.  Spelling
 *    complexity does NOT move mwcc's operand evaluation order.
 *  - `(*(volatile s16 *)&r->f14) * r->f08` (pin the LEFT operand in place, no
 *    local) -> 4 bad, also byte-identical to the plain `f14 * f08` arm.
 * The only route left is a construct that emits the f08 load OUTSIDE the
 * multiply while keeping the value an ordinary expression temp in $7.
 * Case 1 at 0x004F1060 is the CONTROL and is byte-correct: there retail really
 * is `r->f04 + r->f14 * r->f08` and it loads f14 first, so the left-first rule
 * holds in the same function.
 */

typedef struct Rec {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    u8  pad0C[0x8];
    s16 f14;
    s16 f16;
} Rec;

typedef struct Obj {
    u8    pad00[0x5C];
    f32   f5C;
    u8    pad60[0x4];
    void *f64;
    void *f68;
    u8    pad6C[0xC];
    u8    f78;
} Obj;

extern f32   D_0047D3EC;                        /* _gp - 0x7D84 */
extern void *D_004807EC;                        /* _gp - 0x4984 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void factory_FactoryMenuCursorBob_4f0f30(Obj *o, s32 flag)
{
    Rec *r;
    f32  t;
    s32  x;
    s32  y;
    s16  q;

    o->f5C = o->f5C + 0.15707964f;
    if (o->f5C > 0.0f) {
        o->f5C = D_0047D3EC;
    }
    t = 6.0f * Sinf_128fd0(o->f5C);
    switch (o->f78) {
    case 0:
        r = ((Rec *)UiEntryListFindByTag_28ea40(o->f68, 0x88B8));
        q = *(volatile s16 *)&r->f08;
        x = (s32)(t + (f32)(r->f04 + r->f14 * q));
        y = (s32)(t + (f32)(r->f06 + r->f16 * r->f0A));
        if (r->f16 == 7) {
            y = (s32)((f32)0x177 + t);
        }
        if (flag != 0) {
            UiSetWidgetPos_290f60(o->f64, 0x1E, x, y);
        } else {
            UiMoveWidgetUniform_290f50(o->f64, 0x1E, x, y, 0.5f, 0);
        }
        break;
    case 1:
        r = ((Rec *)UiEntryListFindByTag_28ea40(o->f68, 0x88C2));
        x = (s32)(t + (f32)(r->f04 + r->f14 * r->f08));
        y = r->f06;
        if (flag != 0) {
            UiSetWidgetPos_290f60(D_004807EC, 0x97, x, y);
        } else {
            UiMoveWidgetUniform_290f50(D_004807EC, 0x97, x, y, 0.5f, 0);
        }
        break;
    }
}
