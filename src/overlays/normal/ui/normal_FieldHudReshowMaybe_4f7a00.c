/* SESSION 39 (n39g, SOLO): 4 bad -> MATCH, 117/117 words, byte-identical.
 * THE "THREE TEMP REGISTERS, NOTHING ELSE" RESIDUE BELOW WAS A MISSING
 * CALLEE ARGUMENT.  func_3C1BD0 takes TWO arguments, not one:
 *     if (func_3C1BD0(e->f18, cur) != 0)
 * config/arity_inferred.txt proves it at high confidence (PartyIsInReserve_3c1bd0 = 2
 * int args), and retail's listing shows it directly -- `lh $5,0x342($3)`
 * loads the guard value into $5 and NOTHING WRITES $5 between there and the
 * `jal func_3C1BD0`, whose delay slot sets only $4.  $5 was never a guard
 * temp; it was argument two, and the guard reads it on the way past.
 * That is why every one of the ~500 arms in sessions 23/24/32 failed: they
 * were all trying to make the ALLOCATOR put a guard temp in $5, when the
 * right answer was that the value belongs in $5 because it is an ARGUMENT.
 * The base then coalesces onto the dying shift register $3 for free -- the
 * "which of two dying temps does mwcc recycle" question this header's s32
 * section left open never had to be answered.
 * ⚠ GENERALISABLE: a small residue made only of REGISTER NUMBERS around a
 * call is a signature question first and an allocator question second.
 * Screen every extern in the file against config/arity_inferred.txt before
 * spending a single allocator arm -- see build/wf-normal/s39/arityscreen.py,
 * and [[merged-callee-signature-oracle]]. */
#include "types.h"
/* normal 0x004F7A00 -- resets the three gameplay party slots.  Re-registers
 * each slot's widget, clears the slot record when its owner is still live,
 * releases the 0x310-byte entry behind it, then re-arms the two chrome
 * widgets.  Obj is normal_FieldHudInit_4f71a0's (the constructor's) struct.
 *
 * !! PARKED at the RIGHT LENGTH, 7 BAD (s24; was 13 bad at the right length
 * in s23).  NOT merged.
 *
 * SOLVED (s23): `u16 id` + `id += 7` (NOT `id = id + 7`, which narrows twice)
 * is [[mwcc-daddiu-unsigned-narrow]]; func_290010 / func_290F60 /
 * normal_FieldHudPartyPanelLayoutMaybe_4f7700 take a **u16** id so the ids pass UNCAST; `i * 125 + 0xA`
 * and `&D_00484414[i]` are mwcc's strength-reduced multiplies.
 *
 * ====== s24 -- THE SHARED OPEN QUESTION IS ANSWERED ======
 * "What makes mwcc compute a value BEFORE an intervening call instead of
 * sinking it past?"  ==>  THE VALUE IS A CSE SHARED BY A USE ON EACH SIDE OF
 * THE CALL.  A CSE that spans a call must live in a CALLEE-SAVED register, so
 * mwcc materialises it BEFORE the call -- and then fills the guard's DELAY
 * SLOT with it for free.  It is not a spelling of the pointer and not a
 * declaration position; it is whether the two uses are the SAME EXPRESSION.
 *
 * The s23 draft wrote `w->f33C[(u32)i].f6 = -1`.  That (u32) cast on the
 * STORE split it from the guard's READ and destroyed the very CSE that puts
 * the address in $16.  The whole 21-arm s23 deck swept the cast's PLACEMENT
 * when the cast ITSELF was the defect.  Removing it reproduces retail's
 * branch verbatim:
 *     addu $3,$20,$3 / lh 0x342($3) / beq (PLAIN) / addiu $16,$3,0x342 (SLOT)
 * ==> [[mwcc-index-cast-defeats-cse]] is a LEVER IN BOTH DIRECTIONS: reach for
 *     the cast to BREAK a CSE, and REMOVE it to BUILD one.
 *
 * TWO further s24 findings, each worth a word:
 *  1. `(u32)i` BELONGS ON f4/f0, NOT ON f6.  Retail's webs are
 *     {f6 read, f6 store} and {f4, f0, D_00484414 index}.  With the cast on
 *     f4/f0 the base dies before the call and is RECOMPUTED after it, exactly
 *     as retail does -- the frame drops 0x70 -> 0x60 and the 6th callee-saved
 *     register ($21, an extra sq/lq PAIR) disappears.
 *  2. THE STORE MUST TAKE THE MEMBER'S ADDRESS:
 *     `*(s16 *)&w->f33C[i].f6 = -1;`  [[mwcc-member-address-no-cse]] -- taking
 *     &member AT THE STORE SITE stops the address being generated at the READ
 *     site, so the scheduler emits it AFTER the `lh`, where it can be sunk.
 *     13 bad -> 7 bad and the LENGTH closes.  `*(&..)` without the cast is
 *     INERT (base object); the cast is load-bearing.  FOUR spellings are ONE
 *     object (a8f254b4): `*(s16 *)&m`, a block-scope `s16 *q = &m; *q = -1;`,
 *     `*(s16 *)((u8 *)&w->f33C[i] + 6)`, and `A8 *t = &w->f33C[i]; t->f6 = -1;`
 *
 * THE 7 REMAINING BAD ARE ONE DECISION: WHAT $16 HOLDS.
 * Ours keeps the BASE `w + i*8` and folds the offset into both accesses
 * (`lh 0x342($16)` / `sh 0x342($16)`); retail keeps the BAKED ADDRESS
 * `$16 = base + 0x342` and stores through `0($16)`.  The LENGTH is a WASH:
 * ours saves retail's `addiu` but wastes branch B's delay slot on a `nop`
 * where retail duplicates `addiu $2,$19,7` into the annulled slot.  The two
 * branches COMPETE FOR ONE FILLER -- whichever branch gets a real instruction
 * leaves `id += 7` free for the other ([[mwcc-branch-likely-duplication]],
 * both directions live in ONE unit here).
 *
 * !! MEASURED NULLS, ~40 arms this session -- do NOT re-run:
 *   - GUARD SPELLING IS FULLY CANONICALISED: a named `s16 cur` / `s32 cur`
 *     read local (declared first or last), `-1 !=` on the left, an `(s32)`
 *     cast on the read, and an empty-then `if/else` are SIX arms, ONE object.
 *   - INNER STATEMENT ORDER is inert to LENGTH: f6-first, f6-between-f4-and-f0,
 *     f0-before-f4, D-before-f6 are 5 arms / 5 DISTINCT objects, all 0x1d8.
 *   - WHERE `id += 7` LIVES is inert: the for-INCREMENT clause
 *     `for (i = 0; i < 3; i++, id += 7)` is the SAME OBJECT as the trailing
 *     statement.
 *   - A POINTER ASSIGNED **BEFORE THE GUARD** IS STILL CANONICALISED INTO THE
 *     BASE CSE: q declared first / last and the byte-address form
 *     `(s16 *)((u8 *)w + 0x342 + i * 8)` are THREE arms, ONE object, +1 word.
 *     s23 measured this on the OLD base; re-measured here on the NEW one, so
 *     it now binds BOTH bases.  Only &member AT THE STORE SITE works.
 *   - Moving `&D_00484414[i]`'s index to `(u32)i` is INERT (three spellings,
 *     one object b038d5ad).
 *   - `*(s16 *)((u8 *)w + 0x342 + i * 8) = -1` inline is 14 bad, right length.
 * ==> normal_MenuBattleEndDrawLevelUpGlow_4e9f00 parks on the SAME class -- try the CSE reading.
 *
 * ====== s32 (lane nc32m): 7 BAD -> 4 BAD, LENGTH STILL RIGHT ======
 * s24's open question ("what makes mwcc BAKE an offset into a pointer instead
 * of folding it into the addressing mode") IS ANSWERED, and it is a CROSS OF
 * TWO EDITS NEITHER OF WHICH PAYS ALONE:
 *   (a) a volatile ACCESS-SITE PIN on the guard read
 *         cur = *(volatile s16 *)&w->f33C[i].f6;
 *   (b) a BYTE-ADDRESS spelling of the store pointer, assigned BEFORE the call
 *         q = (s16 *)((u8 *)w + i * 8 + 0x342);
 * (a) with a member-spelled q is 118 words; (b) with a plain read is 118
 * words; TOGETHER they are 117 words / 4 bad and the WHOLE SCHEDULE becomes
 * retail's:  addu / lh / PLAIN beq / addiu $16,..,0x342 SUNK INTO THE DELAY
 * SLOT / ... / beql + annulled `addiu $2,$19,7` / ... / sh $2,0x0($16).
 * MECHANISM: the two branches compete for one filler.  The address must be
 * (i) a value, so it needs a pointer whose spelling mwcc will not fold back
 * into the member access -- the byte form -- and (ii) the LAST instruction
 * before the guard branch, so the filler SINKS it.  A pointer defined inside
 * the outer if (p2) bakes the address but emits it AFTER the branch: 118 w.
 * A pointer defined before the guard WITHOUT the volatile pin: 118 w, the
 * addiu lands BEFORE the lh and the filler duplicates `id += 7` (beql).
 *
 * !! THE REMAINING 4 BAD ARE THREE TEMP REGISTERS, NOTHING ELSE:
 *      0x4F7ACC ours addu $4,$20,$3   retail addu $3,$20,$3
 *      0x4F7AD0 ours lh   $3,0x342($4) retail lh  $5,0x342($3)
 *      0x4F7AD4 ours beq  $3,$2        retail beq $5,$2
 *      0x4F7AD8 ours addiu $16,$4,0x342 retail addiu $16,$3,0x342
 *    Retail COALESCES `w + i*8` onto the dying shift register $3 and puts the
 *    loaded value in $5; ours puts the base in $4 and recycles $3 for the
 *    value.  The dataflow, the schedule and every other word are identical.
 *
 * !! s32 MEASURED NULLS -- ~500 arms, 8 bulk decks, all identity-armed:
 *   - 30 arms ON ONE OBJECT at 117/4: read spelling (member / byte / volatile
 *     struct cast / (u32) index), q spelling (7 forms incl. `&arr[0].f6+i*4`),
 *     the ORDER of the two statements, cur as s16/s32, `-1 != cur`, and the
 *     declaration position of q and cur.
 *   - WHOLE-LIST DECLARATION SWEEP, ALL 120 PERMUTATIONS of the 5 locals =
 *     TWO objects only: 4 bad, or 22 bad when `i` is declared before `id`.
 *   - PRAGMA CHANNEL ARMED AND SPENT: optimization_level 0-4, opt_propagation,
 *     opt_common_subs, opt_repositioncode, opt_loop_invariants, peephole,
 *     optimize_for_size, opt_dead_assignments, opt_foldconstants,
 *     opt_moveinvariantsinaddressexpr, opt_recomposeaggregates (+ a bogus
 *     name as the arming control).  Six of them MOVE the object; none is
 *     better than 4, all are longer.
 *   - THE ACCUMULATE SPELLING DOES NOT PICK THE DESTINATION REGISTER:
 *     `b = i * 8; b = (s32)w + b;` swaps the addu's OPERANDS (addu $4,$3,$20)
 *     but still writes $4.  5 accumulate forms x 3 uses x 5 decl positions.
 *   - Statement moves inside the loop (6), loop-condition spellings, trailing
 *     store order, `i`/`id`/`cur`/`e` retypings, wrapping the body in
 *     `if (w->f378 != 0)` instead of an early return: all 4 bad or worse.
 *   - HOISTING THE CALL ARGUMENT (`ev = e->f18;` before the guard) is the ONE
 *     edit that moves these three registers -- it gives base $5 / value $3,
 *     the exact TRANSPOSE of retail -- but it costs a word (the jal's delay
 *     slot becomes a nop): 118 w.  ==> the next lane's door: find the edit
 *     that reserves a register across the guard for FREE, or a model for
 *     which of the two dying temps mwcc recycles for the addu. */

typedef struct A8 { s32 f0; s16 f4; s16 f6; } A8;
typedef struct A4 { s16 f0; s16 f2; } A4;
typedef struct T310 { u8 pad000[0x310]; } T310;
typedef struct Ev { u8 pad00[0x18]; void *f18; } Ev;

typedef struct Obj {
    u8    pad000[0x2B0];
    s16   f2B0;
    s16   f2B2;
    u8    pad2B4[0x2CC - 0x2B4];
    f32   f2CC[3];
    u8    pad2D8[0x33C - 0x2D8];
    A8    f33C[3];
    A4    f354[3];
    u8    pad360[0x364 - 0x360];
    s32   f364;
    s32   f368;
    s32   f36C;
    u8    pad370[0x378 - 0x370];
    s16   f378;
} Obj;

extern T310 *D_00484414;          /* gp - 0xD5C */

extern void  func_290010(void *p, u16 id, s32 c, s32 d);
extern void  func_290F60(void *p, u16 id, s32 x, s32 y);
extern Ev   *func_1FEDE0(void);
extern u8    func_3C1BD0(void *p, s32 k);
extern void  func_33C040(T310 *a);
extern void  normal_FieldHudTacticsModeIconRefresh_4f7be0(Obj *p);
extern void  normal_FieldHudPartyPanelLayoutMaybe_4f7700(Obj *p, u16 id, s32 c, s32 d);
extern void  normal_FieldHudPartyPanelsRefresh_4f7d00(Obj *p);
extern void  normal_FieldHudPanelsClearMaybe_4f70d0(Obj *p);
extern void  normal_FieldHudPanelFrameLayout_4f87c0(Obj *p);
extern void  normal_FieldHudRadarFadeTo_4f11d0(Obj *p, f32 a, f32 b);

void normal_FieldHudReshowMaybe_4f7a00(Obj *w)
{
    u16  id;
    s32  i;
    Ev  *e;
    s16 *q;
    s16  cur;

    if (w->f378 == 0) {
        return;
    }
    func_290010(w, 0x24, 1, -1);
    func_290F60(w, 0x24, 0xDF, 0x15);
    normal_FieldHudTacticsModeIconRefresh_4f7be0(w);
    e = func_1FEDE0();
    id = 6;
    for (i = 0; i < 3; i++) {
        func_290010(w, id, 1, -1);
        normal_FieldHudPartyPanelLayoutMaybe_4f7700(w, id, i, 1);
        w->f2CC[i] = 1.0f;
        func_290F60(w, id, i * 125 + 0xA, 0x17C);
        cur = *(volatile s16 *)&w->f33C[i].f6;
        q = (s16 *)((u8 *)w + i * 8 + 0x342);
        if (cur != -1) {
            if (func_3C1BD0(e->f18, cur) != 0) {
                w->f33C[(u32)i].f4 = 0;
                w->f33C[(u32)i].f0 = 0;
                *q = -1;
                if (D_00484414 != 0) {
                    func_33C040(&D_00484414[i]);
                }
            }
        }
        id += 7;
    }
    normal_FieldHudPartyPanelsRefresh_4f7d00(w);
    w->f364 = 0;
    w->f368 = 0;
    w->f36C = 0;
    normal_FieldHudPanelsClearMaybe_4f70d0(w);
    normal_FieldHudPanelFrameLayout_4f87c0(w);
    func_290F60(w, 2, 0, 0x178);
    func_290010(w, 2, 1, -1);
    w->f2B0 = 1;
    w->f2B2 = 0;
    normal_FieldHudRadarFadeTo_4f11d0(w, 1.0f, 5.0f);
}
