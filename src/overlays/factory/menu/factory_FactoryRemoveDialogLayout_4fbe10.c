/* SESSION 37, lane fg37d -- CLOSED, BYTE-IDENTICAL (was 4 bad, 438 words).
 * THE CLOSE IS ONE LINE, and it needs TWO knobs at once:
 *     func_28FD10(o->f68, 0x5C, (dx + 0x3B) + ((hgt << 16) >> 16),
 *                 dy + 0x24, 3);
 * was
 *     func_28FD10(o->f68, 0x5C, (s16)hgt + (dx + 0x3B), dy + 0x24, 3);
 *
 * The residue was the six-instruction argument block at 0x004FC2F4.  Retail:
 *   addiu $3,$18,0x3B / dsll32 $2,$16,16 / lw $4,0x68($20)
 *   dsra32 $2,$2,16   / addiu $7,$17,0x24 / addu $6,$3,$2
 * Ours emitted the two-instruction NARROW first, so it took $3 and the addiu
 * took $2, and the addu came out transposed.  The callee-saved map ALREADY
 * agreed with retail ($16=hgt, $17=dy, $18=dx, $20=o), so NO allocation lever
 * could pay -- the only question was which temp is BORN FIRST.
 *
 * TWO KNOBS, ONE LEVER; EACH IS INERT WITHOUT THE OTHER:
 *  (a) the `addu`'s rs/rt follows the SOURCE OPERAND ORDER but the EMISSION
 *      order ignores it: writing `(dx + 0x3B) + (s16)hgt` flips
 *      `addu $6,$3,$2` to `addu $6,$2,$3` and changes nothing else
 *      (5 bad, md5 e90646a4c245).
 *  (b) the narrowing SPELLING `((hgt << 16) >> 16)` vs `(s16)hgt` is
 *      BYTE-IDENTICAL in the recorded operand order, but in the REVERSED
 *      order it flips the SCHEDULE: the shift form loses the scheduler's
 *      longest-chain-first priority, so the `addiu` is issued first, takes
 *      $3, and the whole block comes out retail word for word.
 * => When a residue is "which of two short expressions is emitted first" and
 *    the register map already matches, sweep OPERAND ORDER x EXPRESSION
 *    SHAPE as a PRODUCT.  Session 23's five `(s16)hgt` spellings and session
 *    36's naming/pin battery each swept one factor alone and read one object.
 *
 * MEASURED INERT the same run at the 4-bad baseline (md5 eac1df8f578f):
 * `xb` / `nn` region aliases declared FIRST and LAST, both together, a `p2`
 * alias, the `x0 + 0x39` sum named, the `dy + 0x24` argument named, the
 * three FE10 calls inlined, and the shift form in the ORIGINAL operand order.
 * WORSE / length-breaking: volatile on `cp->f18` -1 word (s36, re-confirmed).
 */

#include "types.h"

/* factory.bin overlay, 0x004FBE10 -- open the confirm / detail dialog.
 *
 * 440 instructions, 13 conditional branches, 61 calls: the largest member of
 * the branch-light band.
 *
 * ★ The dispatch is `if (v == 1) ... else if (v == 2 || v == 3)` with an inner
 * `if (v == 2)`, the same shape as `004FA8C0`'s 12/15 test -- not a `switch`.
 * m2c renders it as nested switches.
 * ★ `bgez / sra 1 / addiu 1 / sra 1` is a plain signed `/ 2`, four times here.
 * ★ `slt $1, $17, $2` and `slti $1, $19, 0xFA` both land in `$at` because the
 * consumer is `beql`/`beqz` -- factory's 85-of-85 default polarity, not a
 * register-pressure signal.
 * ★ `$21 = p + 4` exists only so four `lh`s survive the calls at the tail; the
 * FILL block writes the same object through `p` itself.  Both spellings are in
 * this one function, and the sub-object pointer has the four uses mwcc needs
 * before it will spend a register on it.
 * ★ `hgt` is `s32` -- retail's `subu $16, $3, $6` has no truncation, so an
 * `s16` local is wrong; the one narrowed use carries an explicit `(s16)`.
 *
 * ⚠⚠ PARKED, 437 words against 438 -- ONE WORD SHORT, and DELIBERATELY NOT IN
 * `config/ocunits/factory.txt`.  Everything above is settled; the residue is
 * the 1/2/3 dispatch and nothing else.
 *
 * Retail compares 1, then 2, then 3 with THREE SEPARATE `addiu`/branch pairs.
 * `v == 2 || v == 3` is range-optimised by mwcc into `addiu $2, $4, -2` +
 * `sltiu $2, $2, 2` -- the recorded range-optimisation, here on a pair rather
 * than the recorded triple.  SIXTEEN spellings measured over four probe
 * builds and NONE is 438 words:
 *   `||` either way round, `v` as `s32` instead of `u8`  -- 437 (-1)
 *   `!(v != 2 && v != 3)`                                -- 439 (+1)
 *   non-short-circuit `|`                                -- 440 (+2)
 *   `v == 2 ? 1 : v == 3`                                -- 441 (+3)
 *   a third disjunct outside the range                   -- 442 (+4)
 *   `switch (v) { case 1: ... case 2: case 3: ... }`     -- +3 on the same base
 *   a `goto` shared between two `else if`s               -- +2
 * ⚠ It is NOT a `switch`: for a compiled compare chain the bodies run in
 * ASCENDING ADDRESS = source order and the chain runs REVERSED, and here the
 * case-1 body is FIRST while the chain tests 1 first -- both cannot hold for a
 * switch.  So the source really is `if (v == 1) ... else if (<2 or 3>)`, and
 * what is missing is the spelling of `<2 or 3>` that mwcc does NOT
 * range-optimise on two CONTIGUOUS values.  `004FA8C0`'s identical shape on
 * 12/15 needs no lever precisely because those two are not contiguous.
 *
 * ★ Also measured and NOT the answer: five spellings of the `(s16)hgt`
 * narrowing (a named `s16` local, the `<< 16 >> 16` form, casting the three
 * `->f18` stores, reading `q->f04` back).  All are 437 too, so the ninth
 * callee-saved register mwcc spends on the narrowing costs nothing net.
 *
 * ★★★★★★ SESSION 23 (lane fz23e) -- THE UNIT IS NOW THREE INDEPENDENT LEVERS,
 * TWO OF THEM FIXED IN THIS FILE.  Aligning our object against retail
 * instruction-by-instruction (not by length) shows the -1 was never one defect:
 *   +2 retail  the 1/2/3 dispatch (range optimisation)      -- FIXED
 *   +2 retail  `p->f04 = t - 0x16` needs a REDUNDANT (s16)  -- FIXED
 *   -3 ours    a 9th callee-saved register ($fp) holding a
 *              hoisted `(s16)hgt`                           -- STILL OPEN
 * 437 + 2 + 2 - 3 = 438.  The file is now 441 words: both fixes are in, the
 * $fp lever is not.  ⇒ A ONE-WORD LENGTH GAP CAN BE THREE LEVERS THAT NEARLY
 * CANCEL.  ALIGN THE STREAMS BEFORE BELIEVING A LENGTH IS ONE DEFECT.
 *
 * ★ DISPATCH -- SOLVED by the `goto` spelling the old note priced at "+2" and
 * dismissed.  `else if (v == 2) goto two_or_three; else if (v == 3) {
 * two_or_three: ... }` gives retail's three separate compares exactly
 * (`beql v,2 -> body` / `addiu 3` / `bnel v,3 -> epilogue`).  The old note's
 * "+2" WAS the fix; it read as wrong only because the other two levers were
 * still unfixed.
 *
 * ★ `t` -- SOLVED.  mwcc's narrowness knowledge is TYPE-driven: `(s16)` on an
 * `s16`-typed local FOLDS AWAY (measured -- `p->f04 = (s16)t - 0x16` with
 * `s16 t` is byte-identical to no cast at all), but it does NOT survive an
 * `s32` local that was ASSIGNED a cast.  So retail's `t` is `s32`, written
 * `t = (s16)(0x100 - (wd + 0x14) / 2);`, and the second use carries its own
 * explicit `(s16)` -- which is why retail sign-extends a value it just
 * sign-extended (0x004FBF68 and again 0x004FC020).
 *
 * ⚠⚠ THE REMAINING RESIDUE, 3 WORDS, IS ONE MECHANISM.  Retail stores raw
 * `hgt` (`sh $16,0x18(..)` three times) and computes `dsll32/dsra32` at the
 * single `(s16)hgt` use, into caller-saved $2.  mwcc instead notices `sh hgt`
 * and `sh (s16)hgt` are the same store, materialises `(s16)hgt` ONCE before the
 * three stores, and -- because it is then live across three calls -- spends a
 * NINTH callee-saved register on it ($fp), costing `sq`/`lq` plus a `daddu`.
 * MEASURED INERT ON THIS RESIDUE (session 23, all still 441 / $fp present):
 *   - a named late `s32 hn = (s16)hgt;` immediately before the FD10 call;
 *   - `u32 hgt` instead of `s32 hgt`;
 *   - a SECOND SPELLING of the cast operand,
 *     `(s16)(x1 - 0x57 - (dx + 0x39))` -- fully CSE'd back, object unchanged.
 * (Session 22's five spellings -- a named `s16` local, `<< 16 >> 16`, casting
 * the three `->f18` stores, reading `q->f04` back -- are also inert here.)
 * The next arm to try is one that stops mwcc UNIFYING A STORE OPERAND WITH A
 * NARROWED TWIN, not another spelling of the cast itself.
 *
 * ★★★★★★ LANE fz23g, 2026-08-31, round 3 -- THE $fp IS GONE.  441 -> 440.
 * State on disk: `s16 hgt`, `s16 f18`, and the FD10 argument written WITHOUT a
 * cast (`dx + 0x3B + hgt`).  MEASURED 440 words, len 0x6e0 vs retail 0x6d8 --
 * TWO words long, down from three.  The 441 baseline was RE-CONFIRMED offline
 * against build/obj-fz23e (`len 0x6e4 vs 0x6d8`) before any edit.
 *
 * ⚠⚠ THE HEADER CLAIM `hgt is s32, so an s16 local is wrong` IS OVERTURNED as
 * a diagnosis of the $fp: it was an INFERENCE from `subu $16,$3,$6`, never a
 * measurement of hgt's own type.  With `s16 hgt` the object saves only $16-$23
 * -- eight callee-saved registers, NO $fp, no sq/lq/daddu.  Confirmed by
 * disassembling build/obj-fz23g: the save block is s0..s7 only.
 * WHAT REPLACES IT, and the whole remaining +2: mwcc narrows an `s16` local at
 * its DEFINITION (`dsll32 $21,$3,16` / `dsra32 $21,$21,16` at 0x460/0x47c of
 * the object) AND AGAIN at the int-promotion use (0x4f0/0x4f8).  Retail narrows
 * ONCE, at the use.  So the two known types cost:
 *     s32 hgt -> +3 (hoisted narrow held in $fp across the three calls)
 *     s16 hgt -> +2 (a redundant narrow at the definition)
 *     retail  ->  0
 * NOTE this also QUALIFIES the session-23 rule `an (s16) cast on an s16-typed
 * local folds away`: the CAST folds, but the INT PROMOTION of an s16 local in
 * an arithmetic expression still emits its own dsll32/dsra32 pair.
 *
 * MEASURED INERT this round, do not re-sweep:
 *   - declaring `Cell.f18` as `u16` instead of `s16` while keeping `s32 hgt`
 *     and `(s16)hgt` at the use: 441 words, $fp back.  An UNSIGNED store field
 *     does NOT make the store conversion a different object, which
 *     RE-CONFIRMS the `same store mod 2 to the 16` model in the note above --
 *     mwcc reuses the signed-narrowed value as the operand of any 16-bit store
 *     regardless of the field's signedness.
 * MEASURED WORSE, do not re-sweep:
 *   - `dx + 0x3B + (s32)(((s64)hgt << 48) >> 48)` with `s32 hgt`: 446 words,
 *     +5.  The shift pair does reach dsll32/dsra32 sa=16, but the s64 round
 *     trip costs its own truncation code.  A 64-bit shift spelling of the
 *     narrowing is dead.
 *
 * ⇒ NEXT ARM.  Kill the DEFINITION narrow of the `s16` local, not the $fp:
 * make mwcc believe the subtraction already fits (both operands narrow), or
 * find the spelling where an s16 local assigned from an s32 expression is left
 * un-narrowed until its first promoting use.  That is now a two-word target on
 * a unit whose other two levers are closed.
 *
 * LANE fz23k, 2026-08-31 -- **EXACT LENGTH AT LAST: 438 words, 4 bad.**
 * State on disk: `s32 hgt`, `(s16)hgt` at the use, and -- the lever --
 * A NAMED HANDLE FOR THE THREE func_28FE10 CALLS:
 *     cp = func_28FE10(o->f68, 0x5C, 0);   cp->f18 = hgt;   (three times)
 * THE SAME `s32 hgt` + `(s16)hgt` SOURCE WITH THE CALLS WRITTEN INLINE IS 441
 * WITH $fp (re-measured this session as the control, object e39b4a07).  Naming
 * the handle stops mwcc hoisting the `dsll32/dsra32` pair up into the call
 * sequence, so the narrowed value is no longer live across three calls and the
 * NINTH callee-saved register disappears: 441 -> 438.  The `$fp` and the `s16`
 * DEFINITION narrow are the same defect seen from two sides, and neither is
 * reachable by re-spelling the cast -- it is reachable from the CALL that
 * produces the store base pointer.  [[brief lever 6, NAME THE HANDLE FIRST]].
 * WARNING the named handle is INERT with `s16 hgt` (byte-identical to the 440
 * baseline) -- it only pays once the narrow is a separate value.
 *
 * Then `(s16)hgt + (dx + 0x3B)` instead of `dx + 0x3B + (s16)hgt`: 5 -> 4.
 * It fixes the `addu $6,$3,$2` ENCODING at 0x004FC308.
 *
 * THE REMAINING 4 WORDS ARE ONE ROTATION, 0x004FC2F4-0x004FC300.  Registers and
 * colouring already match ($16 = hgt, $18 = dx in both builds):
 *     retail  addiu $3,$18,0x3B / dsll32 $2,$16,16 / lw $4,0x68($20) / dsra32 $2
 *     ours    dsll32 $3,$16,16  / lw $4,0x68($20)  / dsra32 $3,$3,16 / addiu $2
 * i.e. mwcc emits the TWO-instruction narrow before the ONE-instruction
 * `dx + 0x3B`, and the first-born temp takes $3.  Retail emits the addiu first.
 * A SCHEDULER TIE-BREAK on chain length, not an operand-order defect.
 * MEASURED INERT against it (all byte-identical to the 4-bad object 731c796f):
 *   `(s16)hgt + (0x3B + dx)`; `dy + 0x24` written `0x24 + dy`; naming
 *   `dx + 0x3B`, naming `dy + 0x24`, naming the narrow, naming BOTH in either
 *   order, and a fresh `s32 xb` local for it (mwcc folds every one of them
 *   away); `o->f68` hoisted into a `void *` local for that one call; three
 *   SEPARATE `Cell *` handle locals instead of one reused `cp`; and
 *   `cp->f18 + (dx + 0x3B)` at the use (forwarded back to `hgt`, no `lh`).
 * MEASURED WORSE: `0x3B + dx + n` and `(dx + 0x3B) + n` (5, back to ab22bbfe);
 *   `0x3B + (n + dx)` (5); `n + 0x3B + dx` (5); `dx + (n + 0x3B)` (5);
 *   `(s16)*(volatile s32 *)&hgt` (0x6f0, it pins hgt to the stack);
 *   hoisting `func_28D0C0(&rec,0,0,0)` above the call (14).
 * MEASURED INERT ON LENGTH this session, do not re-sweep: `hgt` declared FIRST
 *   or LAST in the declaration list (both byte-identical, s16 and s32);
 *   `hgt = (s16)((x1-0x57)-(dx+0x39))` in one statement (442); a self-narrow
 *   `hgt = (s16)hgt;` at five statement positions (442/442/442/444/441);
 *   `((hgt << 16) >> 16)` at the use (identical object to the `(s16)` cast);
 *   casting the three `->f18` stores and/or `p->f08` (all ONE object with the
 *   plain use-cast -- mwcc unifies a 16-bit store operand with the narrowed
 *   twin, RE-CONFIRMED); `hgt = p->f08;` or `hgt = q->f04;` as the definition
 *   (byte-identical to the s16 baseline); `(s16)(x1-0x57) - (s16)(dx+0x39)`
 *   (0x6f0); `q->f04` at the use (s16 -> 439, s32 -> 443); `p->f08` at the use
 *   (450 -- it costs reloads).
 */

typedef struct Sub {
    s16 f00;
    s16 f02;
    s16 f04;
    u8  pad06[0xA];
    s16 f10;
} Sub;

typedef struct Box {
    u8  pad00[0x4];
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
    u8  pad10[0x4];
    s16 f14;
    s16 f16;
} Box;

typedef struct Cell {
    u8  pad00[0x18];
    s16 f18;
} Cell;

typedef struct Rec {
    void *f00;
    s32   f04;
    u8    pad08[0x8];
    s32   f10;
    s32   f14;
    s32   f18;
    s32   f1C;
    u8    pad20[0x14];
} Rec;                                          /* 0x34 */

typedef struct Dlg {
    u8    pad00[0x5C];
    s32   f5C;
    u8    pad60[0x4];
    u8    f64;
    u8    pad65[0x3];
    void *f68;
    void *f6C;
} Dlg;

extern void *D_00484A70;                        /* _gp - 0x700  */
extern void *D_004807EC;                        /* _gp - 0x4984 */

extern void func_131B60(void *p, s32 v, s32 n);
extern s32 func_1451D0(s32 h);
extern s32 func_1451E0(s32 h);
extern s32 func_15DE80(void);
extern void *func_28AA30(void *p, s32 k);
extern void func_28B8E0(void *p, s32 a, s32 b, s32 c);
extern void func_28D0C0(Rec *r, s32 a, s32 b, s32 c);
extern Box *func_28EA40(void *w, s32 id);
extern void func_28F300(void *w, u16 id, s32 a, s32 k);
extern s32 func_28F3D0(void *w, u16 id, s32 k);
extern s32 func_28F400(void *w, u16 id, s32 k);
extern void func_28F510(void *w, u16 id, void *p, s32 k);
extern void func_28F550(void *w, u16 id, s32 a, s32 k);
extern s32 func_28F620(void *w, u16 id, s32 k);
extern void func_28FBF0(void *w, u16 id, s32 a, s32 k);
extern void func_28FC90(void *w, u16 id, s32 a, s32 k);
extern void func_28FD10(void *w, u16 id, s32 a, s32 b, s32 k);
extern void func_28FD70(void *w, u16 id, s32 a, s32 b, s32 c, s32 d, s32 k);
extern Cell *func_28FE10(void *w, u16 id, s32 k);
extern void func_290010(void *w, u16 id, s32 a, s32 b);
extern void func_290690(void *w, u16 id, f32 a, f32 b, f32 c);
extern void func_290F60(void *w, u16 id, s32 v, s32 k);

void factory_FactoryRemoveDialogLayout_4fbe10(Dlg *o)
{
    Rec rec;
    Box *p;
    Sub *q;
    s32 wd;
    s32 w;
    s32 ht;
    s32 hh;
    s32 dx;
    s32 dy;
    s32 x0;
    s32 x1;
    s32 hgt;
    s32 d;
    s32 t;
    u8  v;
    Cell *cp;

    v = o->f64;
    if (v == 1) {
        func_28F510(o->f68, 0x5A, func_28AA30(D_00484A70, 0xC8), 0);
        func_28F510(o->f68, 0x5A, func_28AA30(D_00484A70, 0xC9), 1);
        func_28F510(o->f68, 0x5A, func_28AA30(D_00484A70, 0xCA), 2);
        wd = func_28F400(o->f68, 0x5A, 0);
        if (wd < func_28F400(o->f68, 0x5A, 1)) {
            wd = func_28F400(o->f68, 0x5A, 1);
        }
        if (wd < func_28F400(o->f68, 0x5A, 2)) {
            wd = func_28F400(o->f68, 0x5A, 2);
        }
        func_28B8E0(func_28FE10(o->f68, 0x5A, 0), wd + 0x14, 0x5D, 3);
        t = (s16)(0x100 - (wd + 0x14) / 2);
        func_290F60(o->f68, 0x5A, t, 0xB2);
        func_290010(o->f68, 0x5A, 1, -1);
        func_290010(D_004807EC, 0x97, 1, -1);
        func_290690(o->f68, 0x5A, 1.0f, 0.125f, -1.0f);
        func_290690(D_004807EC, 0x97, 1.0f, 0.125f, -1.0f);
        func_28FC90(o->f68, 0x5B, 6, 0);
        func_28FBF0(o->f68, 0x5B, wd + 8, 0);
        p = func_28EA40(o->f6C, 0x8912);
        p->f14 = 0;
        p->f16 = 0;
        p->f04 = (s16)t - 0x16;
        p->f06 = 0xB8;
        p->f08 = 0;
        p->f0A = 0x1C;
        p->f0C = 0;
        p->f0E = 2;
        func_290F60(D_004807EC, 0x97, p->f04, p->f06);
        o->f5C = 0;
    } else if (v == 2) {
        goto two_or_three;
    } else if (v == 3) {
two_or_three:
        if (v == 2) {
            func_28F510(o->f68, 0x55, func_28AA30(D_00484A70, 0xB), 0);
        } else {
            func_28F510(o->f68, 0x55, func_28AA30(D_00484A70, 0xD2), 0);
        }
        func_28F510(o->f68, 0x55, func_28AA30(D_00484A70, 0xC), 1);
        func_28F510(o->f68, 0x55, func_28AA30(D_00484A70, 0xD), 2);
        func_131B60(&rec, 0, 0x34);
        rec.f00 = func_28FE10(o->f68, 0x55, 0);
        rec.f04 = func_28F620(o->f68, 0x55, 0);
        rec.f10 = 0x1C;
        rec.f14 = 0x30;
        rec.f18 = 0xF;
        rec.f1C = 8;
        w = rec.f10 + func_28F400(o->f68, 0x55, 0);
        ht = rec.f14 + func_28F3D0(o->f68, 0x55, 0);
        if (w < 0xFA) {
            d = 0xFA - w;
            w = 0xFA;
            rec.f10 = rec.f10 + d;
        }
        hh = func_15DE80();
        dx = func_1451E0(hh) / 2 - w / 2;
        dy = func_1451D0(hh) / 2 - ht / 2;
        x0 = dx + 0x10;
        x1 = x0 + (w - 0x20);
        p = func_28EA40(o->f6C, 0x8912);
        p->f14 = 1;
        p->f16 = 0;
        p->f04 = dx + 0x1B;
        q = (Sub *)&p->f04;
        p->f06 = dy + 0x24;
        hgt = (x1 - 0x57) - (dx + 0x39);
        p->f08 = hgt;
        p->f0A = 0;
        p->f0C = 1;
        p->f0E = 0;
        func_28FD10(o->f68, 0x5C, dx + 0x39, dy + 0x24, 0);
        func_28FD10(o->f68, 0x5C, dx + 0x3D, dy + 0x24, 1);
        func_28FD10(o->f68, 0x5C, dx + 0x6D, dy + 0x24, 2);
        cp = func_28FE10(o->f68, 0x5C, 0);
        cp->f18 = hgt;
        cp = func_28FE10(o->f68, 0x5C, 1);
        cp->f18 = hgt;
        cp = func_28FE10(o->f68, 0x5C, 2);
        cp->f18 = hgt;
        func_28FD10(o->f68, 0x5C, (dx + 0x3B) + ((hgt << 16) >> 16), dy + 0x24, 3);
        func_28D0C0(&rec, 0, 0, 0);
        func_28F550(o->f68, 0x55, dy + 8, 0);
        func_28F300(o->f68, 0x55, x0 + (w - 0x20) / 2, 0);
        func_28F550(o->f68, 0x55, dy + 0x28, 1);
        func_28F300(o->f68, 0x55, dx + 0x53, 1);
        func_28F550(o->f68, 0x55, dy + 0x28, 2);
        func_28F300(o->f68, 0x55, x1 - 0x3D, 2);
        func_28FD70(o->f68, 0x58, dx + 0xA, dy + 0x1B, 0xA, 6, 0);
        func_28FD70(o->f68, 0x58, dx + 0x14, dy + 0x1B, w - 0x2B, 6, 1);
        func_28FD70(o->f68, 0x58, dx + 9 + (w - 0x20), dy + 0x1B, 0xA, 6, 2);
        func_290010(o->f68, 0x55, 1, -1);
        func_290010(D_004807EC, 0x97, 1, -1);
        func_290690(o->f68, 0x55, 1.0f, 0.125f, -1.0f);
        func_290690(D_004807EC, 0x97, 1.0f, 0.125f, -1.0f);
        func_290F60(D_004807EC, 0x97, q->f00 + q->f10 * q->f04, q->f02);
        o->f5C = 1;
    }
}
