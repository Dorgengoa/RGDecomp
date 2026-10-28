/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageWeaponListBuild_504b50 1
#include "port/game_protos.h"
#line 1
/* === SESSION 86 (2026-09-22): 6 BAD -> MATCH.  The $4/$5 transposition was
 * CREATION ORDER ([[levers.d/mwcc-allocator-decompiled]]: later creation ->
 * lower register).  Retail's p=$4 < q->f10=$5 < q=$6 means p is DEFINED LAST,
 * after q->f10 is read, i.e. inside the compare: `(p = m->f7C[a])->f10->f2E`.
 * s54's 'inline either side' arms dropped the NAME; the fix keeps p named and
 * moves only its first def.  Deck build/wf-normal/s86/a1.py. */
/* === SESSION 81 (2026-09-21, SOLO): STILL 6 BAD / 127 words.  FIRST ARM ON
 * THIS UNIT IN 27 THAT REACHES THE ALLOCATOR AT EXACT LENGTH -- and it is the
 * wrong direction.  Decks build/wf-normal/s81/f1.py (the discovery), g1.py
 * (board-wide), j1.py (the cross).
 * THE LEVER: [[levers.d/mwcc-register-binding-exit-seed]] (INSECT s95), never
 * used outside INSECT before today:
 *     #pragma vu0_mmi_reg_binding on
 *     extern s32 gzz asm("r4");        // a register NUMBER, not "a0"
 *     #pragma vu0_mmi_reg_binding off
 * ARMED TWO WAYS: `#pragma zz_not_a_pragma on` == base, and `bind r2` == base
 * (r2 is already the return-register seed, so it is a MEANINGFUL control, not
 * a second bogus name).  Measured here:
 *     r3 24   r4 17   r5 19   r6 19   r7 18   r8 17   (all EXACT LENGTH)
 *     r12 byte-identical;  r16-r20 +2 words (the extra save/restore)
 * FIVE NEW OBJECTS at the right length on a unit whose 26 source arms (s54)
 * were inert or worse.  None better than 6.
 * j1.py CROSSED the binding with s54's source arms (6 sources x 6 bindings,
 * 42 arms): EVERY CROSS IS DOMINATED BY THE BINDING -- the source half adds
 * nothing once a register is reserved.  Also new and BYTE-IDENTICAL:
 * `p = (Ent *)(s32)m->f7C[a]` and the same on `q`, i.e.
 * [[levers.d/mwcc-propagated-temp-colouring]]'s identity cast is REMOVED BY
 * PROPAGATION on this unit -- so the web-preservation idea is a null too.
 * !! The residue is a PAIR TRANSPOSITION (p=$4/temp=$5 retail, p=$5/temp=$4
 * ours) and s95's own note says ONE bound register shifts a carrier ONE lower.
 * A one-register shift CANNOT produce a transposition.  The unexplored arm is
 * a MULTI-REGISTER binding (r4+r5 alone is 19) or an FPR binding.
 * ALSO: the [[levers.d/caller-saved-colour-follows-scheduler]] two-arm probe
 * (h1.py) does NOT fire here -- `optimization_level 2` + `opt_propagation off`
 * + `schedule on` is 129 words, not the base, so the level changes more than
 * the schedule on this unit and the probe is inconclusive, not negative.
 * `optimization_level 3`/`4` == default. */
/* === SESSION 54 (2026-09-12, SOLO): 6 BAD / 127 words (retail 128, the last
 * word is padding).  THE RESIDUE IS NAMED AND THE WHOLE BLOCK-SPELLING AXIS IS
 * A MEASURED NULL.
 * All six words are in the selection sort's inner block and they are ONE
 * TWO-WEB TRANSPOSITION:
 *     retail  p=$4  q=$6  q->f10=$5  p->f10=$2
 *     ours    p=$5  q=$6  q->f10=$4  p->f10=$2
 * Same instructions, same schedule, same offsets, same everything else:
 *   0x00504CB8 lw $4/$5,0x7C($8)      0x00504CC8 lw $2,0x10($4/$5)
 *   0x00504CCC lw $5/$4,0x10($6)      0x00504CD4 lh $5/$4,0x2E($5/$4)
 *   0x00504CD8 slt $1,$5/$4,$2        0x00504CE8 sw $4/$5,0x0($7)
 * `p` is the LONG web (first lw to the last sw); the `q->f10` deref temp is
 * the SHORT one.  Retail gives the long web the lower register.
 * Ã¢Å¡Â Ã¢Å¡Â  26 arms over three decks, ALL negative or inert -- do not re-run them:
 *  a_504b50.py  (8) statement order of `q`/`p`, compare polarity `<` vs `>`,
 *      store order inside the if, decl order q-before-p, and their crosses:
 *      7, 9 or 10 bad, never better.  The `>` polarity (7, object e9b25d09)
 *      is a DIFFERENT class (v0>a0/a1>v0), not a partial fix.
 *  a_504b50b.py (9) NAMED DEREF TEMPS in both orders (`Def *dp,*dq;`),
 *      named s16 value temps in both orders, `>=`-with-empty-then, inlining
 *      either side into the compare: SEVEN of the nine are BYTE-IDENTICAL to
 *      the baseline.  The inner block's spelling cannot reach the allocator.
 *  a_504b50c.py (8) whole-function vreg perturbations: dropping the unused
 *      `__x71_0` declaration, block-scoping `p`/`q` inside the inner loop,
 *      reusing the dead `e` for either pointer, `p` declared first or last of
 *      the whole list, and a third `t` for the swap: ALL BYTE-IDENTICAL
 *      except `E_via_t` (9).
 * Ã¢â€¡â€™ the axis is NOT source order, NOT declaration position and NOT the block.
 * s53's wide pragma screen already covers this unit (it is in plow.txt) and is
 * a clean null.  Next: the allocator itself
 * ([[levers.d/mwcc-allocator-decompiled]]) -- why a SHORT web takes $4 ahead
 * of a LONG one whose def dominates it.
 */
/* === SESSION 51 (2026-09-08, SOLO): 55 -> 6 BAD, exact 127 words, FIVE edits.
 * relscan is CLEAN, dslot is CLEAN, opscan d=0, mdiff has ZERO hunks: the whole
 * remaining residue is ONE caller-saved TRANSPOSITION in the bubble sort, and
 * the FIVE facts the earlier headers named (FACT 1, FACT 2, the `move s3,zero`,
 * the CSE re-read) are all now BOUGHT.  Read this before re-opening.
 *
 * WHAT WENT IN, in the order it was measured (each `->` is the new bad count):
 *  1. 55 -> +2w  THE 12-BYTE COPY.  `struct Kind { f32 v[3]; }` copied
 *     ELEMENT-WISE (`tbl.v[i] = D_004805F0.v[i]`) finally emits retail's three
 *     `lwc1`/three `swc1` instead of the `ld`+`swc1` pair, and relscan's
 *     `0x004805F4 retail 1 -> ours 0` goes away.  s49 had tried f32 MEMBERS but
 *     always with the AGGREGATE copy, which keeps the `ld`; the pair is the
 *     lever.  Uses become `*(s32 *)&tbl.v[(s16)kind]`.
 *  2. -1w        FACT 2, CONFIRMED: the `&&` is a NESTED if.  `if (func_3D4750
 *     (...) != 0) { if (func_3D4C20(e) != 0) ... }`.
 *  3. 46         AND THE INNER TEST IS WRITTEN THE OTHER WAY ROUND:
 *     `if (func_3D4C20(e) == 0) { m->f7C[cnt] = e; cnt++; } else { last = e; }`
 *     is retail's `bnel $2,$0,.L00504C7C | daddu $21,$18,$0` (the THEN arm is
 *     the one that falls into the loop bottom, so mwcc threads `last = e` into
 *     the annulled slot).  Written `!= 0` first it costs an extra `b`.
 *  4. 46 -> 27   THE LOOP IS A ROTATED `goto`, NOT A `while`:
 *         goto next;
 *         for (;;) { ...body... next: e = func_370040(&it); if (e == 0) break; }
 *     That is what makes mwcc emit retail's `bnel $18,$0,.L00504C30 |
 *     lw $2,0x10($18)` -- the loop-back branch-likely DUPLICATING `e->f10`,
 *     [[mwcc-branch-likely-duplication]].  A plain `while ((e = f()) != 0)`
 *     sinks `e = v0` into the slot instead and never threads.  `for(;;)` with
 *     the test at the TOP is exact-length but a different object (46).
 *  5. 27 -> 20   THE CSE RE-READ.  Retail loads `tbl.v[kind]` TWICE (`lw $3`
 *     for the compare, `lw $6` for func_3D4750's third argument); we CSE'd it.
 *     Spelling the ARGUMENT `((const s32 *)&tbl)[(s16)kind]` while the compare
 *     stays `*(s32 *)&tbl.v[(s16)kind]` breaks the CSE.  Ã¢Å¡Â  EVERY index-cast
 *     variant ((u32)/(s32)/byte-offset/pointer-cast) is ONE object -- it is the
 *     BASE expression that has to differ, not the index
 *     ([[mwcc-index-cast-defeats-cse]] does NOT apply here).  A `volatile` read
 *     gives the identical object, so the cast spelling is not a hack.
 *  6. 20 -> 15   `last = 0;` ABOVE the `normal_BtlChgPageGetMember_505f90(m)` call, so mwcc
 *     sinks it into that jal's delay slot; and `w->f18` read BELOW the call,
 *     inline as func_3C2FB0's first argument (drop `__x71_0`)
 *     ([[normal-session49-levers]], the load-below-the-call lever).
 *  7. 15 -> 9    THE COPY IS AN AGGREGATE AFTER ALL -- but a 4-ALIGNED one.
 *     `typedef struct KindP { s32 pad; Kind k; } KindP;`
 *     `extern const KindP D_004805EC ...;`  `tbl = D_004805EC.k;`
 *     Same three lwc1/swc1 as the element-wise form, but retail's SCHEDULE
 *     (store, arg, store, arg, store, jal, arg -- the element-wise form emits
 *     arg, arg, store, arg, store, jal, store).  Ã¢Ëœâ€¦ THE GENERAL LEVER: mwcc
 *     treats an 8-byte-or-larger `.sdata` extern as 8-ALIGNED and copies it
 *     with `ld`; naming the symbol ONE WORD LOWER inside a wrapper struct and
 *     indexing past the pad makes it 4-aligned and changes both the WIDTH and
 *     the SCHEDULE of the block move.  s49's "the next arm has to make one END
 *     4-aligned" was exactly right.
 *  8. 9 -> 6     NAME THE COMPARE'S LEFT OPERAND.  `kv = *(s32 *)&tbl.v[
 *     (s16)kind]; if (kv == e->f10->f02)` with `s32 kv;` in the decl list.
 *     That flips the v0/v1 pair (the tbl value vs the `e->f10`/`f02` chain) to
 *     retail's.  Ã¢Å¡Â  Naming the OTHER side (`Def *d = e->f10;`) is INERT in all
 *     five decl positions, and so is reversing the `==` operands -- mwcc
 *     canonicalises `==`, so only the LEFT operand's temp can be forced.
 *     `kv`'s own decl position and its type (s32/u32) are inert; `s16 kv` is 7.
 *
 * THE FLOOR, 6 words at 0x00504CB8/CC8/CCC/CD4/CD8/CE8: a clean $4<->$5
 * transposition in the bubble sort.  retail gives `p` (= m->f7C[a], the FIRST
 * load, live to the store) $4 and the `q->f10`/`f2E` chain $5; we do the
 * reverse.  Census `a1>a0:4 a0>a1:3`, and it is INVARIANT under ~45 arms:
 *   - p/q decl order, p/q statement order (9), inlining either side of the
 *     compare, `p` re-read inside the `if`, the swap via `m->f7C[b]` (9),
 *     naming `vp/vq` or `dp/dq` in either order and at either end of the decl
 *     list (ALL ONE OBJECT -- mwcc folds the name onto the temp), identity-cast
 *     pins on q, p, q->f10 and p->f10, reusing the dead `e` for either side;
 *   - `>` instead of `<` (7), swapping the two stores (7), `<=` on the inner
 *     bound (8), `a + 1 < cnt` (27), a `j = cnt - 1` hoist (12), an outer
 *     `while` (inert), `(s32)` casts on the compare (inert);
 *   - the WIDE PRAGMA SCREEN at this coat: 13 live columns, best is 7
 *     (`opt_treetransformation off` == `opt_addtogether...off`, one object),
 *     and CROSSING that 7 with `>`, the store swap and the p/q swap gives
 *     8, 8, 10.  `floatsp32 off` 10, `nofpregforblkmv on` 16.  ARMED (the
 *     bogus-name column built, `opt_unroll_count off` did not).
 * => the transposition is not reachable from this function's C.  The next arm
 *    has to be an allocator-level fact, not a spelling.
 *
 * Ã¢Å¡Â  `D_004805EC` is a NEW SYMBOL invented by edit 7 (a 4-byte pad in front of
 * the real table at 0x004805F0).  It has never been through the link -- check
 * it resolves before this unit ever goes into config/ocunits/normal.txt. */
/* === SESSION 49 (2026-09-08): no move (55 bad, 127 words), but FACT 1 in the
 * s45 header is now CONFIRMED BY AN INDEPENDENT SCREEN and priced exactly.
 * build/wf-normal/s49/relscan.py reports `0x004805F4 retail 1 -> ours 0`: retail
 * issues THREE `lwc1` off $28 (-0x4B80/-0x4B7C/-0x4B78) and we issue an `ld`
 * that swallows the middle address, so the 12-byte copy is the ONLY defect the
 * relocation stream can see and every other reference is exact and in order.
 * FOUR NEW ARMS ON THE COPY TYPE, all BYTE-IDENTICAL to the baseline (55 bad)
 * AND all still emitting the `ld`, verified through relscan:
 *   struct Kind { f32 v[3]; } with `*(s32 *)&tbl.v[i]` at the uses,
 *   struct Kind { u8 raw[12]; } with `((s32 *)tbl.raw)[i]`,
 *   struct Kind { s32 a,b,c; } with `(&tbl.a)[i]`.
 * mwcc's choice of `ld` is NOT reachable from the member spelling; it is an
 * alignment deduction about two addresses that are 8-aligned in both builds.
 * The next arm has to make one END 4-aligned, not retype the struct.
 * Everything below predates this. */
/* SESSION 45 (n45g1..n45g8): 57 -> 55 bad, exact 127 words.  ONE EDIT PLUS
 * TWO NAMED FACTS THAT DO NOT YET CROSS.
 *
 * INSTALLED: `if (cnt >= 2)` -> `if (cnt > 1)`.  Same `slti`, same immediate,
 * but retail puts the predicate in `$at` and the `>= K` spelling puts it in a
 * general temp -- [[levers.d/mwcc-compare-operator-picks-register]].  It also
 * empties the `at>v0:2` entry from the substitution census, which is the tell
 * for this lever.
 *
 * FACT 1 (worth +2 words, still unbought): `tbl = D_004805F0;` is a 12-byte
 * aggregate copy of `struct Kind { s32 v[3]; }` and retail does it as THREE
 * WORDS THROUGH THE FPU --
 *     lwc1 $f2,-0x4B80($28) | lwc1 $f1,-0x4B7C | lwc1 $f0,-0x4B78 |
 *     swc1 $f2,0x90($29)    | swc1 $f1,0x94    | swc1 $f0,0x98
 * -- while we emit `ld` + `lwc1` + `sd` + `swc1`, i.e. mwcc believes the
 * struct is 8-ALIGNED and copies 8 bytes at a time.  BOTH ends are at the
 * SAME addresses in both builds (gp-0x4B80 and sp+0x90, each 8-aligned), so
 * this is a decision mwcc made about the TYPE, not about the placement.
 * WARN MEASURED: element-wise `tbl.v[i] = D_004805F0.v[i];` gives GPR lw/sw
 * (the wrong idiom); a `const Kind *kp` indirection is INERT; dropping
 * `const` is INERT; dropping the `.sdata` attribute loses %gp_rel entirely
 * (lui/ld); `f32 v[3]` and `s32 v[4]` are length-wrong.
 *
 * FACT 2 (worth -1 word, and it is very likely a genuine SOURCE CORRECTION):
 * retail's control flow is NOT our `&& ... else`.
 *     beqz $2,.L00504C7C | nop                      <- func_3D4750 == 0 does
 *     jal func_3D4C20 | daddu $4,$18,$0                NOTHING AT ALL
 *     bnel $2,$0,.L00504C7C | daddu $21,$18,$0      <- != 0 -> last = e
 *     sll $2,$19,2 | addu | addiu $19,$19,1 | sw $18,0x7C($2)
 * and .L00504C7C is the LOOP BOTTOM, so `m->f7C[cnt] = e; cnt++;` runs only
 * when func_3D4750 SUCCEEDED and func_3D4C20 failed.  Our `&&` form runs it
 * when func_3D4750 fails too.  The nested spelling is ONE WORD SHORT on its
 * own, which is exactly what you expect of a cross half against FACT 1's +2 --
 * so the unit needs nested + the 3-word copy + one more -1.
 *
 * THE REMAINING -1 CANDIDATES, both visible in mdiff: we emit an EXTRA
 * `move s3,zero`, and we CSE `tbl.v[(s16)kind]` between the compare and
 * func_3D4750's third argument where retail RE-READS it (`lw $6,0x0($17)`) --
 * [[levers.d/mwcc-index-cast-defeats-cse]] is the lever for the second, and
 * the `(u32)` cast on either site was inert against the `&&` shape but has
 * NOT been tried against the nested one. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `EX_L71_0_1_ext` from the extract/split deck.
 *   before: 126 words, ? bad   after: 127 words, 62 bad   (retail 127 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `B_and_L75_bol` from the boolean/compound deck (mkbool31.py)
 *   before: 125 words, ? bad   after: 126 words, ? bad   (retail 127 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* normal 0x00504B50 -- rebuilds the field menu's target list.  Clears the
 * 240-slot pointer table at 0x7C, walks the world's entity iterator, keeps
 * every entity whose f10->f2 kind matches the three-entry code table indexed
 * by `kind`, sorts the survivors by f10->f2E ascending with a selection sort,
 * and appends the one "special" entity func_3D4C20 flagged.
 *
 * The three-word copy from gp -0x4B80/-0x4B7C/-0x4B78 into sp+0x90 is an
 * AGGREGATE COPY of D_004805F0 = { 0, 1, -1 } (verified in
 * asm/data/main_data.data.s): mwcc block-copies it through $f0-$f2, which is
 * why an integer table is moved with lwc1/swc1.
 * `dsll32/dsra32 ..,16` on arg1 is [[normal-s16-cast-sign-extension]]: an s32
 * parameter with an explicit (s16) cast at the index. */

typedef struct Kind { f32 v[3]; } Kind;
typedef struct It   { u8 pad00[0x8]; } It;
typedef struct Filt { u8 pad00[0x18]; } Filt;

typedef struct Def { u8 pad00[0x2]; s8 f02; u8 pad03[0x2E - 3]; s16 f2E; } Def;
typedef struct Ent { u8 pad00[0x10]; Def *f10; } Ent;

typedef struct World { u8 pad00[0x18]; s32 f18; } World;

typedef struct Own { u8 pad00[4]; } Own;

typedef struct Menu {
    u8   pad000[0x7A];
    s16  f7A;
    Ent *f7C[0xF0];
} Menu;

typedef struct KindP { s32 pad; Kind k; } KindP;
extern KindP D_004805EC __attribute__((section(".sdata")));  /* gp - 0x4B84 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgPageWeaponListBuild_504b50(Menu *m, s32 kind)
{
    Kind   tbl __attribute__((aligned(16)));
    It     it __attribute__((aligned(16)));
    Filt   filt __attribute__((aligned(16)));
    World *w;
    Ent   *last;
    Own   *o;
    s32    cnt;
    s32    kv;
    Ent   *e;
    Ent   *p;
    Ent   *q;
    s32    j;
    s32    a;
    s32    b;
    s32 __x71_0;
    s32 __x71_1;

    w = ((World *)GetGameData_1fede0());
    if (w == 0) {
        return 1;
    }
    normal_UiPageGetLayout_289b60(m);
    for (j = 0; j < 0xF0; j++) {
        m->f7C[j] = 0;
    }
    tbl = D_004805EC.k;
    InvViewCtorFromOwner_3cec70(&filt, w, 0, -1, -1, -1);
    IterInit_370170(&it, &filt, 0, 0);
    last = 0;
    __x71_1 = normal_BtlChgPageGetMember_505f90(m);
    o = ((Own *)PartyGetSlotChara_3c2fb0(w->f18, __x71_1));
    cnt = 0;
    goto next;
    for (;;) {
        kv = *(s32 *)&tbl.v[(s16)kind];
        if (kv == e->f10->f02) {
            if (((unsigned char)ItemIsEquippableBy_3d4750(e, o, ((const s32 *)&tbl)[(s16)kind], 1)) != 0) {
                if (((s32)PartyFindItemHolder_3d4c20(e)) == 0) {
                    m->f7C[cnt] = e;
                    cnt++;
                } else {
                    last = e;
                }
            }
        }
    next:
        e = ((Ent *)IterNext_370040(&it));
        if (e == 0) break;
    }
    m->f7A = cnt;
    if (cnt > 1) {
        for (a = 0; a < cnt - 1; a++) {
            for (b = a + 1; b < cnt; b++) {
                q = m->f7C[b];
                if (q->f10->f2E < (p = m->f7C[a])->f10->f2E) {
                    m->f7C[a] = q;
                    m->f7C[b] = p;
                }
            }
        }
    }
    m->f7C[cnt] = last;
    m->f7A = m->f7A + 1;
    return 0;
}
