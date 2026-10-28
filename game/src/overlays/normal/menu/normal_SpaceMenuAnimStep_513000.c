/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuAnimStep_513000 1
#include "port/game_protos.h"
#line 1
/* === SESSION 71 (2026-09-21, SOLO): 159 bad -> MATCH (links byte-identical;
 * n_obytecheck still prints 8 "bad" words -- every one a .lit4 literal-pool
 * relocation it cannot resolve and n_olink does).  build/wf-normal/s71/m1..m4:
 *  - ★ MAIN .lit4 VALUES WRITTEN AS LITERALS: 0.6f (D_0047D288), 3.1415927f
 *    (D_0047D1FC), 1.8f (D_0047D938), 0.7f (D_0047D248), -0.1f (D_0047D944).
 *    As externs mwcc keeps 0.6f live in callee-saved $f20 across calls; as
 *    literals it re-materialises from the pool like retail.  159 -> 14 alone.
 *    EXCEPTION: `arg0->f40 = D_0047D288;` in the 1.8f arm stays the EXTERN
 *    (with `arg0->f44 = -0.1f;` inline) -- it is what orders the two loads.
 *  - f14 == 5/6 arm: `v62 = ...; x = ...; y = spA8 + 0x38;` order.
 *  - f68 accumulate is the store-then-zero clamp: `arg0->f68 = v20;
 *    if (!(v20 < 3.1415927f)) arg0->f68 = 0.0f;` (swc1 in the bc1t slot).
 * Everything below predates this session. */
/* SESSION 65: `arg0->f48 >= 5` -> `> 4`.  [[at-compare-class]]: `>= K` puts the
 * slti in a GPR, `> K-1` puts it in $at, and retail has `slti $1,$2,0x5`.
 * build/wf-normal/s65/atscan.py now prints NO row for this unit (it printed
 * `slti_at: 1->0  slti_gpr: 2->3` before).  Bad count unchanged at 159 -- the
 * rest of the residue swamps it -- but the source now says what retail says.
 */
/* SESSION 56 (2026-09-15, SOLO): NO MOVE, 159 bad / 377 words.  Re-derived the
 * mnemonic-level shape with a tag-aware odiff (build/wf-normal/s55/odiff55.py,
 * since scripts/n_odiff.py and build/wf-normal/s27/odiff.py both hardcode a
 * fixed obj-<tag> and cannot read a fresh sandbox build).  ★ THE 159-BAD COUNT
 * IS MISLEADING: the mnemonic-sequence diff against retail's listing is only
 * SEVEN hunks (@0x00513144 lh/lui swap, @0x00513160 a missing addiu, @0x00513198
 * addiu-vs-lwc1, @0x005131EC bc1fl-vs-bc1t+swc1, @0x005131F8 an extra swc1,
 * plus the two already-named 0x005132CC / 0x005133C4 transpositions from s27).
 * The other ~140 "bad" words are byte differences INSIDE what the mnemonic
 * diff calls "equal" runs -- i.e. same opcode, different operand register --
 * so most of the residue is a CALLER-SAVED TEMP identity/permutation the
 * mnemonic tool cannot see, not the seven structural hunks.  ⚠⚠ MEASURED NULL:
 * s27's own fix ("`x = ...` BEFORE `y = spA8 + 0x38`" closes 0x00513144/160/198)
 * does NOT reproduce now.  Tried (1) inlining `v62`'s single read
 * (`arg0->f62` directly in the x expression, dropping the `s32 v62;` local) --
 * BYTE-IDENTICAL to baseline; (2) the same inlined form WITH `x` moved before
 * `y` -- ALSO byte-identical to baseline, i.e. the x/y order is now INERT
 * where s30/s31's own note says swapping it (with `v62` still a separate
 * local) is +1 word LONG.  So the s27 mechanism needs a THIRD, no-longer-
 * present ingredient to re-fire; do not re-try the bare x/y swap alone,
 * inlined or not, expecting s27's result.  NEXT: read what else changed
 * between s27's "2 hunks / 8 words" state and s30's length-fix -- the length
 * fix likely stepped on more than the x/y statement.  Reverted clean. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `E_ifelse2_L250_els` from the seed/else deck (mkelse31.py)
 *   before: 377 words, 160 bad   after: 377 words, 159 bad   (retail 377 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* SESSION 30: LENGTH-WRONG since s19 -> RIGHT LENGTH at 160 bad, l1 4 -> 3.
 * Installed because it is better on BOTH axes; s29's rule is that a length
 * unlock whose mnemonic distance l1 RISES is differently wrong, not closer.
 * The edit is one statement of the move deck: the `x = (s32)(54.0f + ...)`
 * assignment moved one position later.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* normal 0x00513000 -- PARKED, 3 words SHORT (0x5d8 vs 0x5e4).  Two defects
 * were diagnosed and FIXED here in s22; both are provable against retail's
 * listing and both are recorded levers seen from a new side.
 *
 * 1. `a == K || a == K+1` IS FOLDED INTO A `sltiu` RANGE TEST BY OUR BUILD AND
 *    RETAIL DOES NOT FOLD IT.  Retail spells the pair out --
 *        addiu $2,$0,5 / beql $3,$2,<body>   (first arm branches INTO the body)
 *        addiu $2,$0,6 / bnel $3,$2,<past>   (second arm branches PAST it)
 *    -- which is [[normal-guard-pair-or]]'s shape, while we emitted one
 *    `sltiu $2,$3,2` on `(unsigned)(f14 - 5) < 2`.  ⚠ The fold only fires when
 *    the two constants are ADJACENT and both comparisons read the field the
 *    SAME WAY; casting EITHER side blocks it:
 *        if ((arg0->f14 == 5) || ((u32)arg0->f14 == 6))
 *    Eight blocking spellings -- `(u32)`/`(s32)` on either side, `*(u8 *)`
 *    through a cast on either side, `!(x != K)` on either or both -- give ONE
 *    object, so the choice among them is free; `(s32)` on the second arm and
 *    swapping the arms are INERT (they still fold).  Worth +2 words.
 *    This is [[insect-cse-two-spellings]] again: two sites spelled the same way
 *    are one value, and here that identity is what licenses the range test.
 * 2. `s16 id16` COSTS A `dsll32/dsra32 ,16` PER ITERATION.  With an s16 local,
 *    `id16 = id16 + 1` has to re-narrow; retail has a bare `addiu $2,$17,1`
 *    with the mask only at the call (`andi $5,$17,0xFFFF`), which is `s32 id16`
 *    plus the explicit `id16 & 0xFFFF` argument.  [[normal-s16-cast-sign-extension]]
 *    in the converse direction, and [[pk-callee-param-width]] for the mask.
 *    `u32` is the same object as `s32`; `u16` reaches the right length but at
 *    310 bad (a whole-function shift) and is NOT the answer.
 *
 * SESSION 26: TWO OF THE FOUR LISTED CLASSES ARE CLOSED.  21 hunks -> 17, and
 * the two BIG structural regions are gone (83 differing words -> 38).  Still
 * 3 words short, but the residue is now transpositions and one missing
 * register, not shape.  Both fixes were read off the LISTING, not swept:
 * 1. ****** 0x005132A4 WAS A `||`, NOT A BRANCH-LIKELY PROBLEM.  The s22 note
 *    above reads it as [[mwcc-branch-likely-duplication]]; it is
 *    [[mwcc-or-operand-return-shapes]].  Retail spends 2 words on the `f14==5`
 *    arm (`beql` to the epilogue, `addiu $2,$0,1` in the ANNULLED slot) and 5
 *    on the `f14==6` arm (`bnel` INTO the continuation, then
 *    `addiu $2,$0,1 / b / nop`), which is the `||` signature and NOT in the
 *    two-`if` exit lattice.  Folding the pair (with the range-fold blocked by
 *    the `(u32)` cast, exactly as line 142 already does) took the 13-word hunk
 *    to a 3-word scheduling hunk.  ⚠ The fold MUST be blocked -- `or_plain`
 *    and `or_s32_second` both become a `sltiu` range test and lose 3 words.
 * 2. ★★★★★ THE TAIL WAS A GUARD POLARITY, worth 48 differing words -> 3.
 *    Retail tests `idKey == 8` POSITIVELY with the inner block on the
 *    FALL-THROUGH and the plain `func_2907A0(..,D_0047D248)` call OUT OF LINE
 *    and DUPLICATED, which is `bnel` on the negation; our `if (idKey != 8)`
 *    head gave `beql` with a `daddu` where retail annuls the plain arm's
 *    `lwc1 $f12,-0x7F28($28)`.  Nesting it positively closed the whole region.
 *    ⚠ The flat forms are both WORSE: `idKey == 8 && ... == 2` is 7 short and
 *    `idKey != 8 || ... != 2` is 8 short.  Measured with
 *    build/wf-normal/s26/hdiff.py, which reports the HUNK PROFILE per arm --
 *    the unit is length-wrong so pk_obytecheck cannot score it and a hash-only
 *    sweep cannot say which of four distinct objects moved the shape.
 *
 * ⚠⚠ A DEFECT THE MNEMONIC DIFF CANNOT SEE, found here: `Pair` is declared
 * `{s16 key; s16 val;}` = 4 bytes, but retail indexes `normal_D_00525AF0` with
 * `sll $2, $5, 3` -- STRIDE EIGHT.  A 4-byte Pair emits `sll ..,2` and odiff
 * compares MNEMONICS, so both read `sll` and the hunk never appears.  The
 * sibling normal_FUN_00512E20 drafted in s26 uses an 8-byte Pair.  Fix it here
 * and re-measure before spending another arm on the length.
 *
 * ******* SESSION 27: 17 HUNKS / 38 DIFFERING WORDS -> **2 HUNKS / 8 WORDS,
 * 1 WORD LONG**, and the CALLEE-SAVED REGISTER MAP NOW EQUALS RETAIL
 * (sq=7, off=$16 id16=$17 idKey=$18 ent=$19 arg0=$20 x=$21 y=$22).
 * Six fixes, every one read off the LISTING, none of them a sweep:
 * 1. `Pair` IS EIGHT BYTES: `{s16 key; s16 val; u8 pad04[4];}`.  Retail indexes
 *    normal_D_00525AF0 with `sll ..,3`.  odiff compares MNEMONICS and both spellings
 *    read `sll`, so this hunk is structurally invisible -- see the s26 note.
 * 2. ★★★★★★ `func_1FEDE0()` IS CALLED ONCE AND KEPT IN A LOCAL.  Retail does
 *    `daddu $19,$2,$0` at 0x00513030 and reads `lw $2,0x18($19)` at
 *    0x005131F8; our two calls cost a `jal`/`nop` pair.
 * 3. ★★★★★★★ `func_3ED680`'s FIRST ARGUMENT IS `ent`, NOT `arg0`
 *    (`daddu $4,$19,$0` at 0x0051351C).  THIS IS WHAT BUYS THE SEVENTH
 *    CALLEE-SAVED REGISTER: it extends ent's live range to the end of the
 *    function so mwcc can no longer coalesce it with the loop counter `n`.
 *    ⚠⚠ Before this, 13 declaration positions of `ent` were ONE object
 *    (a clean null); after it, positions 0-2 give RETAIL'S EXACT MAP.
 *    THE DECL-ORDER AXIS WAS INERT ONLY BECAUSE THE LIVE RANGE WAS WRONG.
 * 4. `q = *(void **)((u8 *)pRes + 0x20)` -- the else arm reads `f6` THROUGH a
 *    pointer at +0x20 (`lw $4,0x20($2)` then `lh $2,0x6($4)`), not off pRes.
 *    Our dead `x = *(s32*)(pRes+0x20)` was deleted by the optimiser.
 * 5. `id16` IS `s32` WITH AN EXPLICIT `(s16)` CAST ON THE SUM -- retail spends
 *    `addiu $2,$17,1 / dsll32 $17,$2,16 / dsra32 $17,$17,16` on the increment
 *    and `andi $5,$17,0xFFFF` at the call.  A true `s16` local narrows at the
 *    READ instead and costs 4 words in the loop body.  Same as 00512E20.
 * 6. ★★★★★ NAME A gp FLOAT IN A LOCAL DECLARED BEFORE THE STORE THAT USES IT.
 *    Retail issues the `lwc1` for `f44` BEFORE the integer `sw` for `f40` and
 *    sinks the second `swc1` into a delay slot; ours interleaved load/store.
 *    `{ f32 b = D_0047D950; arg0->f40 = 1.0f; arg0->f44 = b; }` closed FOUR
 *    hunks at 0x00513498/4A4/4CC/4D4 at once, and the same shape at
 *    0x005133C0 took a 6-word hunk to 5.  Also `f32 lim = D_0047D1FC;` in the
 *    f68 accumulate closed 0x005131E0 + 0x005131EC (3+2 words) and stopped
 *    the branch-likely duplication there.
 *    Statement order pays too: `x = ...` BEFORE `y = spA8 + 0x38` in the
 *    f14==5||6 arm closed 0x00513144/160/198 (retail computes y at 0x00513160
 *    and leaves the `b` delay slot for the hoisted `lwc1 $f2,0x68($20)`).
 *
 * WHAT IS LEFT -- 2 hunks, 1 word LONG (`build/wf-normal/s27/odiff.py`):
 *   * 0x005132CC ours `lwc1 jal daddu` / retail `jal daddu lwc1` -- a pure
 *     TRANSPOSITION, 0 net.  We hoist D_0047D288's load above the call.
 *   * 0x005133C4 ours `swc1 swc1 lwc1 jal addiu` / retail `addiu swc1 jal
 *     swc1` -- THE LAST WORD.  Retail's compare at 0x005133AC puts
 *     D_0047D938 in **$f12** and REUSES it as func_2907A0's argument; we
 *     compare in $f1 and reload $f12, so we load the same gp float THREE
 *     times where retail loads it twice.  Same coalescing-hint class as
 *     [[mwcc-or-operand-return-shapes]]'s `005115C0` residual.
 * MEASURED NULLS, s27 (artefacts in build/wf-normal/s27/, do not re-run):
 *   * 8 compare spellings over both sites (`>=`, reversed operands,
 *     `!(a > b)`, `< || ==`) -- v_13000_cmp.py / v_13000_cmp2.py, controls
 *     fire, every arm >= base.
 *   * 6 spellings of a named `f32 g = D_0047D938` (block scope, function
 *     scope, `const`, comma-operator in the condition, 1 or 2 call sites) --
 *     v_13000_d938.py / v_13000_g.py.  ALL WORSE; they add a hunk at
 *     0x005133A0.  Call ORDER is inert.
 *   * 7 live-range arms on the id16/n loop (reuse `i`, reuse `lookup`, reuse
 *     `val`, live-after on either, block-scope order) -- v_13000_live.py.
 *     None reaches sq=7; only fix 3 does.
 *   * `} else if` vs `} else { if` is ONE OBJECT.
 */
#include "types.h"

typedef struct V4 { f32 x; f32 y; f32 z; f32 w; } V4;

typedef struct Ent2 { u8 pad000[0x1A4]; u8 f1A4; } Ent2;
typedef struct Ent  { u8 pad00[0x18]; Ent2 *f18; } Ent;

typedef struct Obj {
    u8   pad00[0x14];
    u8   f14;
    u8   pad1C[0x20 - 0x15];
    f32  f20;
    u8   pad24[0x3C - 0x24];
    s16  f3C;
    s16  f3E;
    f32  f40;
    f32  f44;
    s16  f48;
    s16  f4A[3][4];
    s16  f62;
    u8   pad64[0x68 - 0x64];
    f32  f68;
} Obj;

typedef struct { s16 key; s16 val; u8 pad04[4]; } Pair;

extern Pair normal_D_00525AF0[9];
extern u16  D_004806A0[4];         /* gp - 0x4AD0 */
extern u16  D_00480690[4];         /* gp - 0x4AE0 */
extern f32  D_0047D93C;           /* gp - 0x7834 */
extern f32  D_0047D1FC;           /* gp - 0x7F74 : pi */
extern f32  D_0047D91C;           /* gp - 0x7854 */
extern f32  D_0047D288;           /* gp - 0x7EE8 */
extern f32  D_0047D938;           /* gp - 0x7838 */
extern f32  D_0047D944;           /* gp - 0x782C */
extern f32  D_0047D948;           /* gp - 0x7828 */
extern f32  D_0047D94C;           /* gp - 0x7824 */
extern f32  D_0047D248;           /* gp - 0x7F28 */
extern f32  D_0047D940;           /* gp - 0x7830 */
extern f32  D_0047D954;           /* gp - 0x781C */
extern f32  D_0047D950;           /* gp - 0x7820 */
extern f32  D_004806B0;           /* gp - 0x4AC0 */
extern f32  D_004806B4;           /* gp - 0x4ABC */
extern f32  D_004806B8;           /* gp - 0x4AB8 */
extern f32  D_004806BC;           /* gp - 0x4AB4 */

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

s32 normal_SpaceMenuAnimStep_513000(Obj *arg0)
{
    s32 spAC;
    s32 spA8;
    f32 sp[4] __attribute__((aligned(16)));
    Ent *ent;
    f32 rate;
    f32 v20;
    s16 idKey;
    s16 val;
    s32 i;
    s32 lookup;
    void *pRes;
    void *q;
    s32 x;
    s32 y;
    s32 v62;

    ent = ((Ent *)GetGameData_1fede0());
    if (ent == NULL) {
        return 1;
    }

    v20 = arg0->f20 + D_0047D93C;
    arg0->f20 = v20;
    if (v20 > 0.0f) {
        arg0->f20 = v20 - 3.1415927f;
    }
    rate = 12.0f * Sinf_128fd0(arg0->f20);

    val = 0;
    idKey = arg0->f4A[arg0->f3E][arg0->f3C];
    i = 0;
    do {
        if (idKey == normal_D_00525AF0[i].key) {
            val = normal_D_00525AF0[i].val;
        }
        i++;
    } while (i < 9);

    lookup = (s32)val;
    UiGetWidgetPos_2910a0(arg0, D_004806A0[lookup], &spAC, &spA8);
    pRes = UiFindWidget_290460(arg0, D_00480690[lookup]);
    q = *(void **)((u8 *)pRes + 0x20);

    if ((arg0->f14 == 5) || ((u32)arg0->f14 == 6)) {
        UiGetWidgetPos_2910a0(arg0, 0x24, &spAC, &spA8);
        v62 = arg0->f62;
        x = (s32)(54.0f + (((f32)spAC + rate) + (f32)(v62 * 90)));
        y = spA8 + 0x38;
    } else {
        s16 f6 = *(s16 *)((u8 *)q + 6);
        s32 half;

        x = (s32)((rate + (f32)spAC) - 10.0f);
        half = f6 >> 1;
        if (f6 < 0) {
            half = (s32)(f6 + 1) >> 1;
        }
        y = (spA8 + half) - 0xA;
    }

    v20 = arg0->f68 + D_0047D91C;
    arg0->f68 = v20;
    if (!(v20 < 3.1415927f)) {
        arg0->f68 = 0.0f;
    }

    if (ent->f18->f1A4 & 1) {
        UiSetWidgetAlpha_2907a0(arg0, 0x1F, 0.5f + 0.5f * Sinf_128fd0(arg0->f68));
    }

    sp[0] = D_004806B0;
    sp[1] = D_004806B4;
    sp[2] = D_004806B8;
    sp[3] = D_004806BC;
    {
        s32 id16 = 0x28;
        s32 n = 0;
        do {
            UiMoveWidgetUniform_290f50(arg0, id16 & 0xFFFF, x, y, sp[n], 0);
            n++;
            id16 = (s16)(id16 + 1);
        } while (n < 4);
    }

    if ((arg0->f14 == 5) || ((u32)arg0->f14 == 6)) {
        return 1;
    }

    if (arg0->f14 == 7) {
        if (UiGetWidgetAlpha_290770(arg0, 7) <= 0.6f) {
            arg0->f40 = 0.6f;
            arg0->f44 = 0.0f;
            UiSetWidgetAlpha_2907a0(arg0, 0x1E, arg0->f40);
            UiSetWidgetAlpha_2907a0(arg0, 7, arg0->f40);
            arg0->f48 = arg0->f48 + 1;
            if (arg0->f48 > 4) {
                arg0->f48 = 0;
                arg0->f14 = 8;
                ScreenFadeOutColor_1cf730(GetCurrentScene_1f5be0(), 0xF, 0.0f, 0.0f, 0.0f);
                UiSetWidgetAlpha_2907a0(arg0, 2, 1.0f);
                UiSetWidgetAlpha_2907a0(arg0, 1, 1.0f);
                UiFadeWidgetAlpha_290690(arg0, 1, 0.0f, D_0047D940, -1.0f);
            }
        } else if (!(UiGetWidgetAlpha_290770(arg0, 7) < 1.8f)) {
            arg0->f40 = D_0047D288; arg0->f44 = -0.1f;
            UiSetWidgetAlpha_2907a0(arg0, 0x1E, 1.8f);
            UiSetWidgetAlpha_2907a0(arg0, 7, 1.8f);
            UiSetWidgetAlpha_2907a0(arg0, 0x27, 1.0f);
            UiFadeWidgetAlpha_290690(arg0, 0x27, 0.0f, D_0047D948, -1.0f);
            UiSetWidgetPos_290f60(arg0, 0x21, -0xA, 0x31);
            UiMoveWidgetUniform_290f50(arg0, 0x21, -0x12C, 0x31, D_0047D94C, 0);
            UiSetWidgetPos_290f60(arg0, 0x22, 0xF5, 0x156);
            UiMoveWidgetUniform_290f50(arg0, 0x22, 0x214, 0x156, D_0047D94C, 0);
        }
    } else {
        if (UiGetWidgetAlpha_290770(arg0, 7) <= 0.0f) {
            { f32 b = D_0047D950; arg0->f40 = 1.0f; arg0->f44 = b; }
        } else if (!(UiGetWidgetAlpha_290770(arg0, 7) < 1.0f)) {
            { f32 b = D_0047D954; arg0->f40 = 0.0f; arg0->f44 = b; }
        }
    }

    UiFadeWidgetAlpha_290690(arg0, 0x1E, arg0->f40, arg0->f44, -1.0f);
    UiFadeWidgetAlpha_290690(arg0, 7, arg0->f40, arg0->f44, -1.0f);
    if (idKey == 8) {
        if (ProgressSlotOptionGetRelated_3ed680(ent, idKey) == 2) {
            UiSetWidgetAlpha_2907a0(arg0, 0x1C, 0.5f + (UiGetWidgetAlpha_290770(arg0, 7) / 2.0f));
        } else {
            UiSetWidgetAlpha_2907a0(arg0, 0x1C, 0.7f);
        }
    } else {
        UiSetWidgetAlpha_2907a0(arg0, 0x1C, 0.7f);
    }
    UiSetWidgetsVisibleById_291110(arg0, 0x27, 1, 1);
    UiSetWidgetsVisibleById_291110(arg0, 0x20, 1, 1);
    return 0;
}
