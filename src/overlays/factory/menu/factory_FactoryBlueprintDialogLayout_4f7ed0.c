#include "types.h"

/* factory.bin overlay, 0x004F7ED0 -- lay out the factory screen's main dialog
 * for one of seven states.
 *
 * 1,008 instructions, 145 calls and only 13 conditional branches: the
 * branch-light tier, which is why it is opened early despite its size.  The
 * `switch` on the state uses jtbl_0050CCD0 -- the overlay's own table --
 * through scripts/f_jtbl.py.
 *
 * ★ Cases 3, 6 and 9 share a long layout block and case 4 is a variant of it;
 * retail emits all four in full, so they are written out rather than shared.
 * The differences are real (case 3 closes with func_28FCD0, the others repeat
 * func_28FD10; the +3/+0xA row offsets differ).
 *
 * ★ `ori $5, $0, 0x88EA` rather than `addiu` is just the constant not fitting a
 * SIGNED 16-bit immediate -- a plain `0x88EA` literal produces it.
 *
 * ★ `func_28FE10(...)->f18 = t` is left INLINE.  The recorded "split the call
 * out of a store whose lvalue contains it" lever is about a CONSTANT being
 * materialised before the call; here the stored value is a live local and
 * retail stores straight through `$2`.
 *
 * ★ `sra` under `bgez` with a +1 bias is a signed `/ 2`.
 *
 * ⚠⚠ PARKED -- NOT IN config/ocunits/factory.txt.  SESSION 18 (lane f18c):
 * THE LENGTH IS NOW EXACT, 1,006 words against retail's 1,006, and the unit
 * scores 55 bad.  It read `len 0xfa8 vs 0xfb8` (four words short) and was
 * recorded as "not scoreable" before this session; the `jtbl fallback` line in
 * the scorer's notes is the SCORER saying it took the table addresses off the
 * reference listing, not a defect in the C.
 *
 * ★★★★★ SESSION 18 FIX 1 -- THE FOUR MISSING WORDS.  Retail issues
 * `addiu $16, $16, 0x3` ONCE and then `daddu $7, $16, $0` before each of the
 * three func_28FD70 calls.  Session 17 wrote `ty = ty + 3;` -- REASSIGNING THE
 * SAME LOCAL -- and mwcc value-numbered it away and rematerialised three
 * `addiu $a3, $s0, 3`, one word short per case.  Writing it into a FRESH LOCAL,
 * `ty2 = ty + 3;`, keeps the value; the allocator then coalesces ty2 into ty's
 * own register ($16) and emits exactly retail's in-place `addiu $16,$16,0x3`.
 * Worth 4 words, one per big case.  ⇒ A SELF-ASSIGNMENT IS NOT A NAMED LOCAL:
 * `v = v + K` is folded back into its uses, `v2 = v + K` is a new live range
 * and survives.  This is the converse face of the `y2` win recorded above.
 *
 * ★★★★ SESSION 18 FIX 2 -- SOURCE ORDER PICKS $3 VS $4.  `ty = y + (h -
 * 0x30);` followed by `g->f4 = (s16)(x + 0x1B);` put `h - 0x30` in $4 and
 * `x + 0x1B` in $3; retail has them the other way round.  SWAPPING THE TWO
 * STATEMENTS swaps the two scratch registers and leaves the emitted ORDER
 * unchanged, because the scheduler re-interleaves them either way.  80 -> 67.
 *
 * ★★★★ SESSION 18 FIX 3 -- NAME A JUST-STORED FIELD BEFORE PASSING IT.
 * `func_290F60(D_004807EC, 0x97, g->f4, g->f6);` hoisted the gp load of
 * D_004807EC above the two `lh` re-loads of the fields we had just stored
 * through `g`; retail issues `lh, lh, lw`.  Reading them into `s16 gx, gy;` as
 * their own statements before the call pins both `lh`s ahead of the gp load.
 * 67 -> 55.  (⚠ this does NOT transfer to factory_FactoryMaterialStateTick_4ee070's func_290F60
 * call, where all three arguments come off ONE pointer -- naming all three
 * there is a measured NULL.)
 *
 * ⚠ THE REMAINING 55 -- A CALLEE-SAVED PAIR SWAP IN CASES 4, 6 AND 9 ONLY.
 * Case 3 is byte-identical.  In cases 4/6/9 retail keeps `w` in $18 and the
 * `y`/`yy` chain in $19; we have them the other way round, and the ~18 words
 * per case that name either register are the whole residue.  The live ranges
 * are identical in both builds (`w` dies at the third func_28FD70, `yy` at the
 * closing func_28FD10) and `y2` lands in $21 in both.  Case 3 differs from
 * 4/6/9 only in that its `yy` dies BEFORE `y2` is born, so case 3 needs two
 * callee-saved chains where 4/6/9 need three.
 * ARMS MEASURED IN SESSION 18:
 *   - declaration order of `w` vs `y` swapped -- INERT, byte-identical object;
 *   - PER-CASE BLOCK SCOPING (cases 3/4/6/9 each wrapped in `{}` with their own
 *     copy of all twelve locals, so mwcc could choose a different register per
 *     case the way retail does) -- WORSE, 55 -> 67: it does not move the pair,
 *     and it UNDOES fix 3 in all four cases.  Reverted.
 *
 * ★★★★★★ SESSION 19 (lane fx19a) -- THE PAIR IS NOT REACHABLE FROM THE C.
 * 340 measured variants, ~300 of them byte-identical to this file.  The rule
 * the pair obeys was READ OFF RETAIL and off the CLOSED twin
 * `factory_FactoryMaterialClearConfirmLayout_4f2170` (same clamp, same `t = (r-0x57)-(x+0x39)`, same FD70
 * triple): mwcc hands callee-saved registers out in WEB BIRTH ORDER as the
 * fixed sequence [$19, $16, $17, $18, $22, $21].  Our case 3 (births
 * w,h,x,y,r,t) lands 19/16/17/18/22/21 and is byte-identical; the twin lands
 * cw=$19, ch=$16, s=$17, x=$18 on that same sequence.  Retail's cases 4/6/9 fit
 * the SAME sequence only if their `y` web is created BEFORE `w` -- and no C
 * spelling puts it there, because `w` is the first value the case computes.
 * MEASURED NULLS (all byte-identical to this file unless noted):
 *   - DECLARATION ORDER, EXHAUSTIVE: 226 single-element relocations of all 16
 *     locals.  ZERO improved.  Only moving `lay` (111 bad, stack layout) or
 *     `sty` (77) changed anything at all.  The `f_declsweep` claim that
 *     declaration order reaches a callee-saved PAIR does NOT reach this one.
 *   - per-case FRESH LOCALS for {w,y,yy} / {h,ty,ty2} / {x} / {t,y2} / all ten,
 *     one case at a time and all three at once -- INERT, 8 cells;
 *   - `register` on w, on y+yy, on both -- INERT;
 *   - an unused `s32 dummy;` at three declaration positions -- INERT;
 *   - `switch (sel)` via a named local, `switch ((s32)o->f7C)` -- INERT;
 *   - VARIABLE REUSE (`y` reused as `yy`, `t` reused as `y2` -- the spelling
 *     that would explain why y2 sits in $21 in 4/6/9 and $18 in case 3) --
 *     INERT in all four combinations.  Merging two source names into one
 *     changes no def/ref count the allocator can see;
 *   - STATEMENT POSITION, 21 single moves of `y=`, `ty=`, `r=`, `t=`+`g->f8=`
 *     and `yy=` over every legal slot in cases 4/6/9 -- ALL WORSE (66..135) or
 *     length-broken.  The order in this file is a strict local optimum;
 *   - extra DEFS on the w web (`wk = w;`, `w = call; w = w + K;`) and extra
 *     READS (`w = w + (0xFA - w);`) -- INERT: mwcc folds and copy-propagates
 *     BEFORE the count the allocator uses, so a fake reference is unreachable;
 *   - an early dead store `y = 0;` to create the y web first -- INERT (DCE'd);
 *   - dropping the last 1/2/3 `yy` call arguments to `ty + K` -- WORSE
 *     (84/133/136 on the probe scale); dropping ALL of them is LEN(-1);
 *   - `if (0xFA > w)`, `!(w >= 0xFA)`, `(w-0x20)-0xB`, `(x+9)+(w-0x20)`,
 *     `(x+0x10)+(w-0x20)`, a named `xl = x + 0x10` (the twin's spelling),
 *     parenthesised divides, `t = r - 0x57 - (...)`, `s32 gx/gy` -- all INERT;
 *   - `r = x + (w - 0x10)` is LEN(-3); `lay.f10 = lay.f10 + (0xFA - w)` (the
 *     twin's clamp spelling) is LEN(+2) -- it reloads the stack slot;
 *   - PRAGMAS: `optimization_level 3` INERT (0/1/2 are LEN +682/+163/+161);
 *     `opt_loop_invariants`, `opt_strength_reduction`, `opt_dead_assignments`,
 *     `opt_dead_code`, `opt_unroll_loops`, `scheduling` all `off`,
 *     `optimize_for_size on`, `global_optimizer off` -- all INERT.
 *     `opt_lifetimes off` DOES move the allocator (158 bad) but wrecks case 3.
 *     `opt_propagation off` / `opt_common_subs off` LEN(+4); `peephole off`
 *     LEN(+69).
 * ⇒ RECONFIRMED: fix 3 is real -- removing `gx`/`gy` costs 12 words.
 * ⇒ RECONFIRMED: the `jtbl fallback` note is a pure consequence of a wrong
 *   LENGTH; at the exact length it never appears.
 * ⇒ THE RESIDUE IS 55 WORDS: in cases 4, 6 and 9 retail keeps `w` in $18 and
 *   the `y`/`yy` chain in $19 and we have them swapped, at retail addresses
 *   0x004F83B0-0x004F85E4, 0x004F8764-0x004F8980 and 0x004F8AA4-0x004F8CC0.
 *   Case 3 (0x004F8020-0x004F82D0) is byte-identical.  DO NOT spend another
 *   session on declaration order or statement position here.
 * ⚠⚠ It must stay OUT of the unit list.
 *
 * ⚠ SESSION 23 (lane fz23e) -- THE "WHICH WEB IS BORN FIRST" AXIS IS PRICED AND
 * DEAD TOO.  Session 19 swept declaration order; this session swept the one
 * thing all 226 of those cells held fixed, namely WHERE `w` IS CREATED.
 * Splitting `w` into a genuine two-armed phi at the clamp, in cases 4/6/9 only
 * (`wa = call + K; ... if (wa < 0xFA) { lay.f10 = ...; w = 0xFA; } else
 * { w = wa; }`), so that `w`'s web is born AFTER `y`'s -- BYTE-IDENTICAL .text,
 * 4,024 bytes, 55 bad, exact length.  mwcc coalesces the copy before the count
 * the allocator uses, exactly as the "extra DEFS on the w web" cell did.
 * ⇒ Splitting a value into two webs is the SAME measured null as adding a def.
 *
 * ★ CORRECTION to the session-19 reading: the rule "callee-saved registers go
 * out in WEB BIRTH ORDER [$19,$16,$17,$18,$22,$21]" is REFUTED BY RETAIL'S OWN
 * CASE 4.  Retail creates `w` first (`addiu $18,$2,0x3B` at 0x004F83B0) and
 * `y` second (`subu $19,$2,$3` at 0x004F83F8) yet gives $19 to `y` and $18 to
 * `w`.  Birth order is not the discriminator, so "no C spelling can put y
 * first" is not the reason this unit is stuck.
 * ★ WHAT THE DISCRIMINATOR ACTUALLY IS, read off case 3 vs case 6 (which are
 * the SAME source but for three constants): case 6 repeats
 * `func_28FD10(.., x + 0x3B, yy, 3)` AFTER the three func_28FD70 calls and case
 * 3 closes with `func_28FCD0(.., x + 0x3B, 3)` instead.  So in 4/6/9 the y->yy
 * chain OUTLIVES `w`, and in case 3 it does not -- and $19 goes to whichever of
 * the two dies LAST.  That is the whole difference between the byte-identical
 * case and the three broken ones.  It is a property of the live ranges, which
 * both builds already agree on, so it is not reachable by respelling either
 * variable; the next arm worth anything is a STRUCTURAL one (cases 4/6/9 as one
 * inlined static helper, so their allocation is built once), not another local.
 *
 * ★★★★★★★ SESSION 33 (2026-09-02, lane fg33) -- 55 -> 19 BAD, EXACT LENGTH.
 * THE "DO NOT SPEND ANOTHER SESSION ON DECLARATION ORDER OR STATEMENT POSITION"
 * VERDICT ABOVE IS OVERTURNED -- but not on either axis it was swept on.
 * THE LEVER IS WHICH SWITCH CASES SHARE THE VARIABLE.
 *   `w` used by cases 3,4,6,9 (the baseline)  -> all four $19,  55 bad
 *   `w`={3},  `w2`={4,6,9}                    -> 6 and 9 CORRECT, 19 bad
 * Cases 6 and 9 are now byte-identical; the whole residue is case 4 alone.
 *
 * THE RULE, read off eight measured groupings with a per-case REGISTER READOUT
 * (build/fg33/wy.py -- score the MAP, never the byte count, or every cell in
 * this family reads "inert"):
 *   ** a group that EXCLUDES case 3 gives $19 to its FIRST case in SOURCE ORDER
 *      and $18 to every later case;
 *   ** a group that INCLUDES case 3 gives $19 to ALL of its cases.
 *   w2={6,9} -> 6:$19 9:$18 ; w2={4,6} -> 4:$19 6:$18 ; w2={4,6,9} -> 4:$19
 *   6:$18 9:$18 ; w={3,4} -> both $19 ; w={3,9} -> both $19.
 * Case 4 is the earliest of {4,6,9} and case 3 is the only case before it, so
 * no grouping can make case 4 a non-first member of a case-3-free group.
 * 19 IS THE FLOOR FOR THIS LEVER; closing case 4 needs a different one.
 *
 * ⚠ WHY 226 SESSION-19 CELLS MISSED IT: a rename inside ONE case is COALESCED
 * (all eight of {h,x,r,t,ty,yy,y2,ty2} split for case 4 alone are BYTE-IDENTICAL,
 * md5 d44d90d665c6), and a group of ONE case is coalesced back into `w` (specs
 * {4}, {6} and {9} each reproduce the 55-bad baseline object exactly).  A
 * grouping must span TWO OR MORE cases before mwcc keeps it distinct.
 *
 * ⚠ AND WHY IT LOOKED DEAD ON DECLARATION ORDER: `w2`'s declaration POSITION
 * is inert at all 11 slots (one object); `y`'s is inert at all 10; only `w` at
 * slots 7-9 moves anything, and it moves CASE 3 -- the case that is already
 * correct -- to 75 bad.  POSITION AND GROUPING ARE DIFFERENT AXES.
 * ⚠ THE LEVER NEEDS MUTUALLY EXCLUSIVE REGIONS.  It does NOT transfer to
 * sequential code (factory_FactoryBeltExtendToward_500630's $18/$19 pair), where splitting a
 * variable needs a copy and mwcc coalesces the copy away.
 * RE-MEASURED AND STILL TRUE at the NEW baseline: the `y + 8` statement position
 * is a strict local optimum (51 slots swept, every one worse than 19).
 *
 * ★★★★★★★ SESSION 36 (2026-09-02, lane fg36) -- 19 -> 0 BAD, BYTE-IDENTICAL,
 * MERGED into config/ocunits/factory.txt.  THE WHOLE EDIT IS ONE FRESH NAME:
 *     s32 yy2;            <- declared FIRST, above `s32 w;`
 *     case 4: yy2 = ty + 0xF;  (and its five uses)  -- case 4 ONLY
 * That gives case 4 retail's map (y/yy2 = $19, w2 = $18) and leaves 3/6/9 as
 * they were.  It OVERTURNS the session-33 boundary "a group must span TWO OR
 * MORE regions -- a rename inside ONE case is coalesced": every single-case
 * split session 33 measured was DECLARED LAST (split4.py), and declared last a
 * single-case variable IS inert (yy2={4} declared last = baseline object,
 * d44d90d665c6, re-measured here).  DECLARED FIRST it takes the register.
 * The axis is GROUPING x DECLARATION POSITION together; neither alone reads.
 *
 * MEASURED THIS SESSION, all exact length (md5 = object identity):
 *   INERT (baseline d44d90d665c6): y split {4,6,9}/{4}/{6,9}/{4,6}/{4,9} at
 *     either declaration end; h, x, r, t, ty, y2, ty2 split {4,6,9}; yy
 *     reused as `y` in case 4 / in 4,6,9 / everywhere; `y + 8` named; the
 *     case-3 copy `w2 = w;` placed AFTER `yy = ty + 0xC;` at six positions
 *     (with w2 declared first or last); w2 declared first or before yy.
 *   yy2={4} declared LAST: inert.  yy2={4} declared FIRST: MATCH.
 *   yy2={4,6,9} declared first / before yy / before y: 36 (fixes 4, breaks
 *     6 and 9); yy2={6,9} either end: 37; yb+yy2 both {4,6,9}: 55.
 *   w2 given a case-3 web BEFORE yy's def (clamp phi, clamp copy, or the copy
 *     placed just above `yy =`): 55 -- the unsplit-w object 6cf71d443762.
 *   w2={4}, w3={6,9}: 37.  Case-4 statement moves at 19: y/x swap 25, ty
 *     before g->f4 22, yy before the 0x93 call 22, y after the clamp 32, r
 *     after EA90 26, x before h 28, t after gx/gy length-breaking; the
 *     `ty = (h - 0x33) + y` operand order is a distinct object still at 19.
 * READING: the variable whose grouping is live is `yy` (the y register is
 * inherited by yy after y dies, so y's own grouping never mattered), and a
 * variable's FIRST web is coloured ahead of the other variables' later webs
 * -- which is why w2={4,6,9} fixed 6 and 9 but never 4, and why yy2 confined
 * to case 4 and declared first is the only cell that reaches case 4.
 */

typedef struct Glyph {
    u8  pad0[4];
    s16 f4;
    s16 f6;
    s16 f8;
} Glyph;

typedef struct Style {
    u8  pad0[0xC];
    s32 fC;
    u8  pad10[0x9C];
} Style;

typedef struct Layout {
    void *f0;
    s32   f4;
    u8    pad8[8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    s32   f20;
    s32   f24;
    s32   f28;
    s32   f2C;
    s16   f30;
} Layout;

typedef struct Src {
    u8   pad0[4];
    s16 *f4;
} Src;

typedef struct Panel {
    u8    pad0[0x5C];
    s16   f5C;
    s16   f5E;
    u8    pad60[0x14];
    Src  *f74;
    u8    pad78[4];
    u8    f7C;
    u8    pad7D[7];
    void *f84;
} Panel;

typedef struct Row {
    u8  pad0[0x18];
    s16 f18;
} Row;

extern void *D_004807E8;
extern void *D_004807EC;
extern void *D_00484A70;
extern u8 D_0050CCC8[];
extern u8 D_0050FF50[];

extern void  factory_FactoryBlueprintDialogSetStyle_4f7c70(Panel *o, s32 a);
extern void  func_131B60(void *p, s32 v, s32 n);
extern void  func_15DE80(void);
extern void  func_28A9A0(void *dst, void *src, void *sty, s32 f);
extern void  func_28AA00(void *sty);
extern void *func_28AA30(void *bank, s32 id);
extern void  func_28D0C0(void *lay, s32 a, s32 b, s32 c);
extern Glyph *func_28EA40(void *ctx, s32 id);
extern void  func_28EA90(void *ctx, s32 id, s32 a);
extern s32   func_28F3D0(void *ctx, s32 id, s32 a);
extern s32   func_28F400(void *ctx, s32 id, s32 a);
extern void  func_28F510(void *ctx, s32 id, void *p, s32 a);
extern void  func_28F5D0(void *ctx, s32 id, s32 x, s32 y, s32 n);
extern s32   func_28F620(void *ctx, s32 id, s32 a);
extern void  func_28FCD0(void *ctx, s32 id, s32 x, s32 n);
extern void  func_28FD10(void *ctx, s32 id, s32 x, s32 y, s32 n);
extern void  func_28FD70(void *ctx, s32 id, s32 x, s32 y, s32 w, s32 h, s32 n);
extern Row  *func_28FE10(void *ctx, s32 id, s32 n);
extern void  func_290010(void *ctx, s32 id, s32 a, s32 b);
extern void  func_290F60(void *ctx, s32 id, s16 x, s16 y);
extern void  func_291110(void *ctx, s32 id, s32 a, s32 b);

void factory_FactoryBlueprintDialogLayout_4f7ed0(Panel *o)
{
    Layout lay;
    Style sty;
    Glyph *g;
    Row *row;
    s32 yy2;
    s32 w;
    s32 h;
    s32 x;
    s32 y;
    s32 r;
    s32 t;
    s32 ty;
    s32 yy;
    s32 y2;
    s32 ty2;
    s32 w2;
    s16 gx;
    s16 gy;

    func_131B60(&lay, 0, 0x34);
    lay.f0 = func_28FE10(D_004807E8, 0x92, 0);
    lay.f4 = func_28F620(D_004807E8, 0x92, 0);
    lay.f20 = 0x33;
    lay.f24 = 0x44;
    lay.f28 = 0x1A1;
    lay.f2C = 0x115;
    lay.f30 = 4;
    func_290010(D_004807E8, 0x92, 1, -1);
    func_291110(D_004807E8, 0x95, 0, 1);
    func_291110(D_004807E8, 0x94, 0, 1);
    func_291110(D_004807E8, 0x93, 0, 1);
    func_15DE80();
    func_28AA00(&sty);

    switch (o->f7C) {
    case 3:
        lay.f10 = 0x1E;
        lay.f14 = 0x30;
        lay.f18 = 0xF;
        lay.f1C = 8;
        func_291110(D_004807E8, 0x95, 1, 1);
        func_291110(D_004807E8, 0x94, 1, 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0x19), 0);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xC), 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xD), 2);
        w = func_28F400(D_004807E8, 0x92, 0) + 0x1E;
        h = func_28F3D0(D_004807E8, 0x92, 0) + 0x30;
        x = 0x103 - w / 2;
        y = 0xCE - h / 2;
        if (w < 0xFA) {
            lay.f10 = 0x118 - w;
            w = 0xFA;
        }
        r = x + 0x10 + (w - 0x20);
        func_28EA90(o->f84, 0x88EA, 1);
        g = func_28EA40(o->f84, 0x88EA);
        g->f4 = (s16)(x + 0x1B);
        ty = y + (h - 0x30);
        g->f6 = (s16)(ty + 0xC);
        t = (r - 0x57) - (x + 0x39);
        g->f8 = t;
        gx = g->f4;
        gy = g->f6;
        func_290F60(D_004807EC, 0x97, gx, gy);
        yy = ty + 0xC;
        func_28FD10(D_004807E8, 0x95, x + 0x39, yy, 0);
        func_28FD10(D_004807E8, 0x95, x + 0x3D, yy, 1);
        func_28FD10(D_004807E8, 0x95, x + 0x6D, yy, 2);
        row = func_28FE10(D_004807E8, 0x95, 0);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 1);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 2);
        row->f18 = t;
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy, 3);
        y2 = ty + 0x10;
        func_28F5D0(D_004807E8, 0x92, x + 0x48, y2, 1);
        func_28F5D0(D_004807E8, 0x92, r - 0x45, y2, 2);
        func_28D0C0(&lay, 0, 0, 0);
        ty2 = ty + 3;
        func_28FD70(D_004807E8, 0x94, x + 3, ty2, 0xA, 6, 0);
        func_28FD70(D_004807E8, 0x94, x + 0xD, ty2, w - 0x2B, 6, 1);
        func_28FD70(D_004807E8, 0x94, x + 2 + (w - 0x20), ty2, 0xA, 6, 2);
        func_28FCD0(D_004807E8, 0x95, x + 0x3B, 3);
        o->f5C = 0;
        return;

    case 4:
        factory_FactoryBlueprintDialogSetStyle_4f7c70(o, 0);
        lay.f10 = 0x3B;
        lay.f14 = 0x33;
        lay.f18 = 0x29;
        lay.f1C = 0xB;
        func_291110(D_004807E8, 0x95, 1, 1);
        func_291110(D_004807E8, 0x94, 1, 1);
        func_291110(D_004807E8, 0x93, 1, 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0x1A), 0);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xC), 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xD), 2);
        w2 = func_28F400(D_004807E8, 0x92, 0) + 0x3B;
        h = func_28F3D0(D_004807E8, 0x92, 0) + 0x33;
        x = 0x103 - w2 / 2;
        y = 0xCE - h / 2;
        if (w2 < 0xFA) {
            lay.f10 = 0x135 - w2;
            w2 = 0xFA;
        }
        r = x + 0x10 + (w2 - 0x20);
        func_28EA90(o->f84, 0x88EA, 1);
        g = func_28EA40(o->f84, 0x88EA);
        g->f4 = (s16)(x + 0x1B);
        ty = y + (h - 0x33);
        g->f6 = (s16)(ty + 0xF);
        t = (r - 0x57) - (x + 0x39);
        g->f8 = t;
        gx = g->f4;
        gy = g->f6;
        func_290F60(D_004807EC, 0x97, gx, gy);
        func_28FD10(D_004807E8, 0x93, x + 0xF, y + 8, 0);
        yy2 = ty + 0xF;
        func_28FD10(D_004807E8, 0x95, x + 0x39, yy2, 0);
        func_28FD10(D_004807E8, 0x95, x + 0x3D, yy2, 1);
        func_28FD10(D_004807E8, 0x95, x + 0x6D, yy2, 2);
        row = func_28FE10(D_004807E8, 0x95, 0);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 1);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 2);
        row->f18 = t;
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy2, 3);
        y2 = ty + 0x13;
        func_28F5D0(D_004807E8, 0x92, x + 0x48, y2, 1);
        func_28F5D0(D_004807E8, 0x92, r - 0x45, y2, 2);
        func_28D0C0(&lay, 0, 0, 0);
        ty2 = ty + 6;
        func_28FD70(D_004807E8, 0x94, x + 0xA, ty2, 0xA, 6, 0);
        func_28FD70(D_004807E8, 0x94, x + 0x14, ty2, w2 - 0x2B, 6, 1);
        func_28FD70(D_004807E8, 0x94, x + 9 + (w2 - 0x20), ty2, 0xA, 6, 2);
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy2, 3);
        o->f5E = 0;
        return;

    case 5:
        factory_FactoryBlueprintDialogSetStyle_4f7c70(o, 1);
        lay.f10 = 0x1E;
        lay.f14 = 0x13;
        lay.f18 = 0xF;
        lay.f1C = 0xB;
        func_291110(D_004807EC, 0x97, 0, 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0x1B), 0);
        func_28F510(D_004807E8, 0x92, D_0050CCC8, 1);
        func_28F510(D_004807E8, 0x92, D_0050CCC8, 2);
        func_28D0C0(&lay, 0, 0, 0);
        return;

    case 6:
        lay.f10 = 0x1E;
        lay.f14 = 0x30;
        lay.f18 = 0xF;
        lay.f1C = 8;
        func_291110(D_004807E8, 0x95, 1, 1);
        func_291110(D_004807E8, 0x94, 1, 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0x3C), 0);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xC), 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xD), 2);
        w2 = func_28F400(D_004807E8, 0x92, 0) + 0x1E;
        h = func_28F3D0(D_004807E8, 0x92, 0) + 0x30;
        x = 0x103 - w2 / 2;
        y = 0xCE - h / 2;
        if (w2 < 0xFA) {
            lay.f10 = 0x118 - w2;
            w2 = 0xFA;
        }
        r = x + 0x10 + (w2 - 0x20);
        func_28EA90(o->f84, 0x88EA, 1);
        g = func_28EA40(o->f84, 0x88EA);
        g->f4 = (s16)(x + 0x1B);
        ty = y + (h - 0x30);
        g->f6 = (s16)(ty + 0xC);
        t = (r - 0x57) - (x + 0x39);
        g->f8 = t;
        gx = g->f4;
        gy = g->f6;
        func_290F60(D_004807EC, 0x97, gx, gy);
        yy = ty + 0xC;
        func_28FD10(D_004807E8, 0x95, x + 0x39, yy, 0);
        func_28FD10(D_004807E8, 0x95, x + 0x3D, yy, 1);
        func_28FD10(D_004807E8, 0x95, x + 0x6D, yy, 2);
        row = func_28FE10(D_004807E8, 0x95, 0);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 1);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 2);
        row->f18 = t;
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy, 3);
        y2 = ty + 0x10;
        func_28F5D0(D_004807E8, 0x92, x + 0x48, y2, 1);
        func_28F5D0(D_004807E8, 0x92, r - 0x45, y2, 2);
        func_28D0C0(&lay, 0, 0, 0);
        ty2 = ty + 3;
        func_28FD70(D_004807E8, 0x94, x + 0xA, ty2, 0xA, 6, 0);
        func_28FD70(D_004807E8, 0x94, x + 0x14, ty2, w2 - 0x2B, 6, 1);
        func_28FD70(D_004807E8, 0x94, x + 9 + (w2 - 0x20), ty2, 0xA, 6, 2);
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy, 3);
        o->f5C = 0;
        return;

    case 9:
        lay.f10 = 0x1E;
        lay.f14 = 0x30;
        lay.f18 = 0xF;
        lay.f1C = 8;
        func_291110(D_004807E8, 0x95, 1, 1);
        func_291110(D_004807E8, 0x94, 1, 1);
        func_131B60(&sty, 0, 0xAC);
        sty.fC = *o->f74->f4;
        func_131B60(D_0050FF50, 0, 0x20);
        func_28A9A0(D_0050FF50, func_28AA30(D_00484A70, 0x5A), &sty, 1);
        func_28F510(D_004807E8, 0x92, D_0050FF50, 0);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xC), 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0xD), 2);
        w2 = func_28F400(D_004807E8, 0x92, 0) + 0x1E;
        h = func_28F3D0(D_004807E8, 0x92, 0) + 0x30;
        x = 0x103 - w2 / 2;
        y = 0xCE - h / 2;
        if (w2 < 0xFA) {
            lay.f10 = 0x118 - w2;
            w2 = 0xFA;
        }
        r = x + 0x10 + (w2 - 0x20);
        func_28EA90(o->f84, 0x88EA, 1);
        g = func_28EA40(o->f84, 0x88EA);
        g->f4 = (s16)(x + 0x1B);
        ty = y + (h - 0x30);
        g->f6 = (s16)(ty + 0xC);
        t = (r - 0x57) - (x + 0x39);
        g->f8 = t;
        gx = g->f4;
        gy = g->f6;
        func_290F60(D_004807EC, 0x97, gx, gy);
        yy = ty + 0xC;
        func_28FD10(D_004807E8, 0x95, x + 0x39, yy, 0);
        func_28FD10(D_004807E8, 0x95, x + 0x3D, yy, 1);
        func_28FD10(D_004807E8, 0x95, x + 0x6D, yy, 2);
        row = func_28FE10(D_004807E8, 0x95, 0);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 1);
        row->f18 = t;
        row = func_28FE10(D_004807E8, 0x95, 2);
        row->f18 = t;
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy, 3);
        y2 = ty + 0x10;
        func_28F5D0(D_004807E8, 0x92, x + 0x48, y2, 1);
        func_28F5D0(D_004807E8, 0x92, r - 0x45, y2, 2);
        func_28D0C0(&lay, 0, 0, 0);
        ty2 = ty + 3;
        func_28FD70(D_004807E8, 0x94, x + 0xA, ty2, 0xA, 6, 0);
        func_28FD70(D_004807E8, 0x94, x + 0x14, ty2, w2 - 0x2B, 6, 1);
        func_28FD70(D_004807E8, 0x94, x + 9 + (w2 - 0x20), ty2, 0xA, 6, 2);
        func_28FD10(D_004807E8, 0x95, x + 0x3B, yy, 3);
        o->f5C = 0;
        return;

    case 7:
        lay.f10 = 0x1E;
        lay.f14 = 0x13;
        lay.f18 = 0xF;
        lay.f1C = 0xB;
        func_291110(D_004807EC, 0x97, 0, 1);
        func_28F510(D_004807E8, 0x92, func_28AA30(D_00484A70, 0x46), 0);
        func_28F510(D_004807E8, 0x92, D_0050CCC8, 1);
        func_28F510(D_004807E8, 0x92, D_0050CCC8, 2);
        func_28D0C0(&lay, 0, 0, 0);
        return;

    case 8:
        lay.f10 = 0x1E;
        lay.f14 = 0x13;
        lay.f18 = 0xF;
        lay.f1C = 0xB;
        func_291110(D_004807EC, 0x97, 0, 1);
        func_131B60(&sty, 0, 0xAC);
        sty.fC = *o->f74->f4;
        func_131B60(D_0050FF50, 0, 0x20);
        func_28A9A0(D_0050FF50, func_28AA30(D_00484A70, 0x50), &sty, 1);
        func_28F510(D_004807E8, 0x92, D_0050FF50, 0);
        func_28F510(D_004807E8, 0x92, D_0050CCC8, 1);
        func_28F510(D_004807E8, 0x92, D_0050CCC8, 2);
        func_28D0C0(&lay, 0, 0, 0);
        return;
    }
}
