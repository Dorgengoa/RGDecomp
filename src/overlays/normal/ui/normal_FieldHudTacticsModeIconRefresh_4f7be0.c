/* === SESSION 80 (2026-09-21, SOLO): 2 bad -> MATCH, exact 70 words, on ONE
 * WORD: `const` on the read-only table.  The residue was retail emitting
 * `lw $4,0x10($6)` (v10 = D_00526250[i].f10) BEFORE `sh $3,0xC($8)`
 * (b->f0C = v0C) and us emitting the store first.  Every prior arm on this
 * unit (s38, s69, s72, s76) moved STATEMENTS or DECLARATIONS; none of them
 * could work, because a list scheduler MAY NOT hoist a load over a store it
 * cannot prove disjoint from.  `D_00526250` was declared non-const, so the
 * `Box *` store aliased it and the load was pinned.  `extern const Row
 * D_00526250[4];` releases it and the two words fall into retail's order.
 * ARMED: the same edit crossed with two statement reorderings gives the
 * IDENTICAL object (e9aa8d82), and both reorderings WITHOUT const are 11 and
 * 8 bad -- the const is the whole fix.  build/wf-normal/s80/c1.py.
 * NOT A NEW MECHANISM: this is [[levers.d/mwcc-const-sdata-load-hoist]] moved
 * off the prologue and off gp -- there the alias barrier is the prologue's own
 * $sp stores and the fix carries `.sdata`; here it is an ordinary body store,
 * D_00526250 is a lui-addressed table, and `const` ALONE is the edit.
 * [[levers.d/mwcc-const-global-unpins-load]] */
/* === SESSION 76 (2026-09-21, SOLO): 7 -> 2 BAD, exact 70 words.  A TWO-EDIT
 * CROSS, and the second edit REOPENED AN AXIS FIVE SESSIONS CALLED DEAD.
 *  1. the three `1.8f` arguments of func_2905B0 spelled as the gp-pool extern
 *     `extern f32 D_0047D608;` (gp - 0x7B68).  This KILLS the .lit4 word at
 *     0x004F7C98 and mwcc still CSEs the three reads into ONE `lwc1 $f12`.
 *     !! s73's header says this is "+2 words" -- WRONG.  It is EXACT LENGTH,
 *     9 bad: the .lit4 word closes and a THREE-WORD rotation appears at
 *     0x004F7CA0/A4/A8 (`mtc1 $2,$f15` emitted two slots early).  All ten
 *     argument-expression spellings of that rotation (named `k`, named `m` for
 *     -1.0f, both, a named widget id, a named panel pointer, a pointer-deref
 *     read, decl-list vs block-scope) are ONE OBJECT a7b7615a -- the front end
 *     normalises argument side effects, exactly as insect-session64-levers
 *     predicts.  `const` on the extern is +1 word, `volatile` is 11.
 *  2. `#pragma opt_dead_assignments off` KILLS THAT ROTATION: 9 -> 6.  Found
 *     by sweeping the 68-name opt_* table against the 9-bad coat (a4.log,
 *     armed: bogus == base, opt_unroll_* fail to build).  The group-A/B table
 *     (84 arms, a3.log) is a clean null.
 *  3. â˜…â˜… AND THE PRAGMA OPENS THE DECLARATION/STATEMENT AXIS.  At the OLD
 *     coat s44/s52/s54 measured the three row loads over ~200 arms and found
 *     TWO objects ("DECL ORDER IS NOT THE LEVER here", "retail's ascending
 *     load order is not reachable").  At THIS coat the same six decl
 *     permutations reach EIGHT objects (a5.log).  Splitting the decls from the
 *     assignments and writing the assignments in ASCENDING field order --
 *         s32 v0C, v08, v04, v10;      (the decl ORDER is inert, 3 orders)
 *         v04 = ...f04;  v08 = ...f08;  v0C = ...f0C;
 *     -- gives retail's ascending emission order and 6 -> 2 (a6.log, 54 arms).
 *     â‡’ `opt_dead_assignments off` IS THE PRAGMA THAT MAKES SOURCE STATEMENT
 *     POSITION THE VREG CREATION ORDER.  It is the same lever s72 used on
 *     normal_LeaderHudGaugeBarSet_506630; mwcc-vreg-creation-source-position's "neither does
 *     any pragma" is WRONG.  RUN IT AS A BOARD SCREEN.
 * RESIDUE, 2 words at 0x004F7C64/68, ONE ADJACENT SWAP: retail emits
 * `lw $4,0x10($6)` (the f10 read) BEFORE `sh $3,0xC($8)`; we emit the store
 * first.  A load with three successors vs a store with none -- retail takes
 * HEIGHT, we take SOURCE ORDER (insect-session64-levers' two tie-break rules,
 * and note normal_LeaderHudGaugeBarSet_506630's 2-word residue is the SAME pair the OTHER way
 * round).  MEASURED NULL, do not re-run:
 *   - the v10 statement at all 10 positions through the load/store block
 *     (a7.log): 24/24/24/11/9/8/[2]/3/LEN/LEN -- the installed slot is best;
 *   - all 24 orders of the four v04/v08/v0C stores x v10 at three gaps
 *     (a8.log, 72 arms, ~20 distinct objects so it provably fires): nothing
 *     under 2.  A SECOND 2-bad object exists (41451039, stores f08/f0A/f04/f0C
 *     with v10 after all four) and its two words are the SAME class one slot
 *     further out, so the two do not cross.
 * âš  `s32 v10 = ...;` written after any statement in the block FAILS TO BUILD
 * (C89 declaration placement) -- those rows in a7.log are compile errors, not
 * sandbox failures.
 * Sweeps: build/wf-normal/s76/a1..a8.  KEEP OUT OF config/ocunits/normal.txt.
 */
/* === SESSION 73 (2026-09-21, SOLO): 8 -> 7 bad, exact 70 words.  ONE EDIT:
 * the `-0.1f` argument of `func_2904E0` written as the gp-POOL EXTERN
 * `extern f32 D_0047D7A0;` (gp - 0x79D0).  The object said so:
 * n_obytecheck's "defined in this object's .lit4" note means WE emitted a
 * local literal (`lwc1 $fN,0x0(<own .lit4>)`) where retail loads the shared
 * MAIN pool.  Screen: build/wf-normal/s73/lit4back.py.
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¦ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  THE OTHER .lit4 WORD GOES THE OTHER WAY: `1.8f` -> `D_0047D608` is +2,
 * because the three 1.8f arguments share ONE load as a literal and become
 * three separate gp loads as a variable.  Price each SITE alone; a value that
 * appears once is a candidate, a value CSE'd across arguments is not.
 * Everything below predates this session. */
/* === SESSION 54 (2026-09-12, SOLO): STILL 6 BAD / 70 words.  The s38 header's
 * "pure list-scheduler tie-break, no source-level lever" is now PRICED, and the
 * two open sub-questions are answered.
 * The residue is the ORDER OF THE THREE ROW LOADS and it drags the second site
 * with it:
 *     retail  lw $5,0x4  lw $4,0x8  lw $3,0xC   (ASCENDING offset, $5/$4/$3)
 *     ours    lw $5,0xC  lw $4,0x8  lw $3,0x4
 * so retail's `v0C` owns $3 and is still live at `b->f04 = v0C`, which is why
 * `addiu $3,$4,0x6` CANNOT schedule until after `sh $3,0x4($8)`; our `v04`
 * owns $3 and dies at the first `sh`, freeing $3 early -- that IS the
 * 0x004F7C6C/0x004F7C70 swap, not a separate fact.
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¦ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¦ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  19 arms over three decks, ALL negative -- do not re-run:
 *  a_4f7be0.py  (4) all four remaining DECL permutations of `v0C/v08/v04`:
 *      TWO objects only.  {0C,08,04},{04,0C,08},{0C,04,08} = baseline 6;
 *      {04,08,0C},{08,04,0C} = 7, and the ascending one emits f08,f0C,f04 --
 *      the load order does NOT follow the declaration order.
 *  a_4f7be0b.py (8) reading the ONCE-USED fields AT THEIR USE instead of into
 *      a local (the s38 header's "read each field into a local" was measured
 *      on the TWICE-read fields and over-generalised): 23-24 bad, and dropping
 *      `v0C` too is length-wrong.  `C_inline_04only` ties at 6 on a new object
 *      with the SAME six bad words -- a relocation-only difference, not a half.
 *  a_4f7be0c.py (7) DECLARATION split from ASSIGNMENT
 *      ([[levers.d/mwcc-vreg-creation-source-position]]): the decl slot is
 *      INERT and only the ASSIGNMENT order matters, but assignment order
 *      04,08,0C does NOT produce load order f04,f08,f0C -- mwcc reorders it to
 *      f08,f0C,f04.  Only the descending assignment order reaches the
 *      baseline object.
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡Ãƒâ€šÃ‚Â¬ÃƒÆ’Ã‚Â¢ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¾Ãƒâ€šÃ‚Â¢ retail's ascending load order is not reachable from any permutation of
 * these four reads.  Attack what makes mwcc REORDER them.
 */
/* === SESSION 52 (2026-09-08, SOLO): PLATEAU AT 6 HOLDS, 11 more arms.  Two
 * channels the 180-arm s44 sweep and the s45 seven had not touched:
 *  - AGGREGATE READ of the triple (s44/s45 only ever tried scalar temps): a
 *    12-byte `S3 t = *(const S3 *)&D_00526250[i].f04;` as an initialiser, as a
 *    separate assignment, and as the s51 UNION view
 *    ([[mwcc-union-aggregate-fill]]) are ALL 0x130 against retail's 0x118 --
 *    mwcc emits the copy into a real stack temp and then reloads.  The
 *    aggregate channel is DEAD here; the three loads must stay scalar.
 *  - POINTER CHAIN: `const s32 *q = &D_00526250[i].f04;` with the reads as
 *    `q[0..3]` is 7 ascending / 6 descending -- a NEW object (13d69d5a) at the
 *    plateau, so the sweep still has reach and still cannot beat 6.
 * Also re-confirmed: ascending decl order is 7 and its residue shows OUR loads
 * come out 0x08,0x0C,0x04 -- i.e. the decl order does not even set the
 * EMISSION order, which is what s44 concluded.  The register map is a function
 * of emission order in both ours and retail; the tie-break over three
 * independent loads off one base is still the whole residue. */
/* SESSION 45: 70/70 w, 6 bad.  s44's 180-arm HARD PLATEAU is CONFIRMED, and
 * mdiff.py (build/wf-normal/s45/) re-states it far more precisely than s44's
 * "the emission order of three independent loads":
 *   retail  lw $4,0x10($6) | sh $3,0xC($8) | sh $3,0x4($8) | addiu $3,$4,0x6
 *   ours    lw a0,16(a2)   | sh a1,12(t0)  | addiu v1,a0,6  | sh a1,4(t0)
 * THE WHOLE RESIDUE IS THAT `v10 + 6`'s `addiu` IS SCHEDULED ONE SLOT EARLIER
 * FOR US.  Seven further arms this session -- `6 + v10`, the `v10` load moved
 * to three positions, a named `v6` temp in two places, `b->f0E` before
 * `b->f06` -- all read 6 (five distinct objects, so the SOURCE is moving and
 * the schedule is not).  Re-reading `D_00526250[i].f10` twice is length-wrong.
 */
/* SESSION 44 (n44c/d/f/h, SOLO): 180 further arms, HARD PLATEAU AT 6.
 * All three s43 board screens are SILENT on this unit (opscan/spscan/brscan
 * all d=0), so the residue is pure colouring/schedule.  Read off exactly:
 *   retail  lw $5,4($6)  lw $4,8($6)  lw $3,0xC($6)   ASCENDING address order
 *   ours    lw $5,0xC    lw $4,8      lw $3,4         DESCENDING
 * In BOTH, the three temps take $5,$4,$3 in EMISSION order, so the whole
 * 6-word residue is the emission order of three independent loads.
 * ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¦ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â ÃƒÆ’Ã†â€™Ãƒâ€ Ã¢â‚¬â„¢ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¢ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã‚Â¦ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â¡ÃƒÆ’Ã†â€™ÃƒÂ¢Ã¢â€šÂ¬Ã…Â¡ÃƒÆ’Ã¢â‚¬Å¡Ãƒâ€šÃ‚Â  WHAT IS NOW MEASURED DEAD:
 *  - 12 arms = all 6 decl permutations x {v10 first, v10 last}: they collapse
 *    onto TWO objects (6 and 7 bad).  DECL ORDER IS NOT THE LEVER here; the
 *    only thing it changes is v08's register, and v04 is emitted LAST and
 *    coloured $3 in every single source order tried.  s39's "invariant map"
 *    reading is confirmed and is now explained.
 *  - 5 arms of INLINING the reads at their stores (f0C inline -- the one
 *    spelling s39 had not tried -- and every cross with f04/f08): all are
 *    71 words, ONE WORD LONG.  The three locals are load-bearing.
 *  - 105 arms = declaration SPLIT from assignment x every legal position of
 *    the four assignment statements through the store block
 *    ([[mwcc-vreg-creation-source-position]]).  Best is 6, i.e. the installed
 *    object; 52 of 105 read 24 (the four-live-temps coat).
 *  - 68 arms = the same placement lattice over stores written in ASCENDING
 *    FIELD order (f04,f06,f08,f0A,f0C,f0E).  All but one read 24.  The
 *    installed store order is retail's.
 * The next arm is NOT a source-order one.  What would have to change is which
 * of the three loads mwcc schedules first, and that is a scheduler tie-break
 * over three loads off one base with no dependence between them. */
/* SESSION 39 (n39c, SOLO): 7 -> 6 bad, still exact 70/70 words.
 * The one word bought: DECLARING THE TRIPLE IN FULL REVERSE (v0C, v08, v04)
 * puts v08 in retail's $4.  [[mwcc-decl-statement-order]] is right that the
 * FULL REVERSAL is the arm to probe first -- session 38 tried exactly one
 * other permutation (f08,f0C,f04), got a null, and concluded the axis was
 * dead; it was not, it was the wrong permutation.
 *
 * 23 ARMS THIS SESSION, all scored, hard plateau at 6.  What they establish:
 *  - ALL SIX decl permutations of the triple, and all six again with the
 *    declaration split from the assignment (12 arms): 6 or 7 bad, never less.
 *  - The register map is INVARIANT to source order at f04->$3, f08->$4,
 *    f0C->$5 whenever only three temps are live; retail is the exact MIRROR,
 *    f04->$5, f08->$4, f0C->$3.  In BOTH ours and retail the registers run
 *    DESCENDING in EMISSION order -- the only real difference is that retail
 *    emits the three loads in ASCENDING address order (f04,f08,f0C) and ours
 *    emits them in the reverse.  So this is a list-scheduler emission-order
 *    difference showing up as a register map, not a colouring rule.
 *  - NULL/regression on: a named `Row *w` pointer with the triple forward
 *    (7) or reversed (6); swapping the guard's operands to
 *    `D_00526250[i].f00 == id` (7 fwd / 6 rev); reading f04 inline at its
 *    store (7); reading BOTH f04 and f08 inline with only v0C a local (24);
 *    loading v10 last (8 fwd / 6 rev); loading v10 first (6).
 *  - STORE-ORDER PERTURBATION IS THE ONE AXIS THAT MOVES THE MAP, and it
 *    moves it the wrong way: making v10 an initialised decl alongside the
 *    triple puts FOUR temps live at once, at which point mwcc widens the
 *    pool to $4-$7 AND re-colours the row base register from $6 to $4
 *    (24 bad).  Reversing the six stores, or storing f0C/f04 first: 24 bad.
 * Untried: anything that changes how many values are live across the
 * bnel at 0x004F7C48 without changing the store order. */
#include "types.h"
#pragma opt_dead_assignments off
extern f32   D_0047D7A0;          /* gp - 0x79D0, -0.1f */
extern f32   D_0047D608;          /* gp - 0x7B68, 1.8f */
/* normal 0x004F7BE0 -- retunes widget 0x24 whenever the party-member id at
 * f3D4 changes; the five-column table at D_00526250 is searched by that id.
 * `sw $16, 0x3D4($17)` appears twice because it is the SHARED trailing store
 * duplicated into the branch-likely delay slot. */
/* SESSION 38 (n38g): parked at 70/70 words, 7 bad -- length is now exact.
 * Two fixes applied and CONFIRMED against retail:
 *   1. `id` must be `s32`, not `s16` -- an s16 local forced a redundant
 *      dsll32/dsra32 sign-extend pair both before the table loop and at the
 *      final `p->f3D4 != id` compare (6 extra words total).
 *   2. `p->f3D4` is `s32`, not `s16` -- retail reads/writes it with
 *      `lw`/`sw`, not `lh`/`sh` (was 4 of the 11 bad words at 70/70).
 *   3. Each 20-byte Row field the loop copies into `Box` must be read into a
 *      LOCAL once and reused for both destination stores (`f0C`->`f0C`/`f04`
 *      pair, `f10`->`f06`(+6)/`f0E` pair); reading the field twice from
 *      D_00526250[i] directly cost 2 extra words (was 76 words before this).
 * RESIDUE (7 bad, exact length): retail's three loads for f04/f08/f0C into
 * $5/$4/$3 come out in SOURCE order (f04,f08,f0C); ours emits them
 * REORDERED as f08,f0C,f04 regardless of the locals' declaration order --
 * tried reordering the three `s32 vXX = ...;` decls to f08,f0C,f04 to match
 * the emitted order, NULL (identical object, same 7 bad). Reads as a pure
 * list-scheduler tie-break over three independent loads with no source-level
 * lever found yet; the retail register choices (a1,a0,v1 for f04,f08,f0C)
 * don't correspond to any of the value's use order, decl order, or GPR
 * ascending/descending rule tried. Untried: mkmove-style defining-statement
 * perturbation (see [[levers.d/mwcc-vreg-creation-source-position]]) on just
 * this triple. */
typedef struct Row {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
} Row;

typedef struct Box {
    u8  pad000[0x4];
    s16 f04;
    s16 f06;
    s16 f08;
    s16 f0A;
    s16 f0C;
    s16 f0E;
} Box;

typedef struct Ret {
    u8   pad000[0x20];
    Box *f20;
} Ret;

typedef struct A {
    u8    pad000[0xC];
    void *f0C;
} A;

typedef struct N {
    u8  pad000[0x3D4];
    s32 f3D4;
} N;

extern const Row D_00526250[4];

extern A   *func_1FEDE0(void);
extern Ret *func_290460(N *p, u16 id);
extern void func_2905B0(N *p, u16 id, f32 a, f32 b, f32 c, f32 d);
extern void func_2904E0(N *p, u16 id, f32 a, f32 b, f32 c, f32 d, f32 e);

void normal_FieldHudTacticsModeIconRefresh_4f7be0(N *p)
{
    A   *a;
    Ret *r;
    Box *b;
    s32  id;
    s32  i;

    a = func_1FEDE0();
    if (a == NULL) {
        return;
    }
    id = *(s16 *)((u8 *)a->f0C + 0x24);
    r = func_290460(p, 0x24);
    if (r != NULL) {
        b = r->f20;
        if (b != NULL) {
            for (i = 0; i < 4; i++) {
                if (id == D_00526250[i].f00) {
                    s32 v0C, v08, v04, v10;
                    v04 = D_00526250[i].f04;
                    v08 = D_00526250[i].f08;
                    v0C = D_00526250[i].f0C;
                    b->f08 = v04;
                    b->f0A = v08;
                    b->f0C = v0C;
                    v10 = D_00526250[i].f10;
                    b->f04 = v0C;
                    b->f06 = v10 + 6;
                    b->f0E = v10;
                }
            }
        }
    }
    if (p->f3D4 != id) {
        func_2905B0(p, 0x24, D_0047D608, D_0047D608, D_0047D608, -1.0f);
        func_2904E0(p, 0x24, 1.0f, 1.0f, 1.0f, -1.0f, D_0047D7A0);
    }
    p->f3D4 = id;
}
