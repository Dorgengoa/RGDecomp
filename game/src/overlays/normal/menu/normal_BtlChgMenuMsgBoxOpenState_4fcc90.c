/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuMsgBoxOpenState_4fcc90 1
#include "port/game_protos.h"
#line 1
/* === SESSION 72 (2026-09-21, SOLO): **MATCH**.  ONE named local plus one
 * pragma -- [[levers.d/mwcc-named-local-dead-assignment]]:
 *     row = (D_004844E4 - 1) % 2;      INSIDE the i-loop
 *     func_1319A8(&slot[i], &arr[row][i], 0x20);
 * with `#pragma opt_dead_assignments off` at file scope.  Retail computes the
 * `% 2` chain FIRST and `i * 32` in the MIDDLE of it; inlined, mwcc creates
 * `i * 32` first and the two webs come out in the wrong registers.
 * ARMED, and both halves are nulls on their own: the pragma ALONE and the
 * named `row` ALONE are each BYTE-IDENTICAL to the old 12-bad park
 * (06708e59).  Hoisting `row` OUT of the loop is +2 words; naming the source
 * pointer as well is 2 bad; naming only the destination is 12; a `Cell *rp =
 * arr[...]` row pointer is 9.
 */
/* === SESSION 71 (2026-09-21, SOLO): 26 -> 12 bad, exact 157 words.
 * The 640-byte `arr` fill is mwcc's own AGGREGATE copy
 * `*(A640 *)arr = *(const A640 *)normal_D_005251B0;` (the hand-written 2-word loop
 * was the wrong source).  The pairs/tbl fills as aggregate copies are inert.
 * LEFT (12): in the func_1319A8 loop retail computes `i*32` and `&slot[i]`
 * in the JOIN block after the `(D_004844E4 - 1) % 2` branch; ours hoists them
 * into the loop-head block as scheduler filler.  Named src/dst pointers, a
 * named k, `slot + i`, `i + arr[..]`, (s32)/(u32) casts: all ONE object
 * (the u32 index casts are +1 word). */
/* === SESSION 51 (2026-09-08): MEASURED NEGATIVE, no move (26 bad, 157 words).
 * The lever that closed the whole 3-slice twin family this session --
 * [[mwcc-union-aggregate-fill]], a `union { s16 v[4]; struct { S3 s; s16 d; } q; }`
 * view of `tbl` so the aggregate fill does not PIN `&tbl[0]` -- is INERT here:
 * `tu.q.s = *(S3 *)&D_004805A0; tu.q.d = D_004805A6;` is the BYTE-IDENTICAL
 * BASELINE OBJECT (6fbc1a3a).  Writing the scalar half FIRST is 32.
 * The pin only costs a word when the array is read BY INDEX inside a LOOP;
 * this unit reads `tbl[D_004844E4]` once, so there is nothing to fold.
 * Deck: build/wf-normal/s51/a_4fcc90.py. */
/* === SESSION 46 (2026-09-07, SOLO): 31 -> 26 BAD, exact 157 words, ONE arm:
 * `*(S3 *)tbl = *(S3 *)&D_004805A0; tbl[3] = D_004805A6;` -- a 3+1 SPLIT.
 * Retail's tbl fill is L,L,L,S,S,S then L,S, i.e. a THREE-element aggregate
 * copy followed by a scalar, not a 4-element one (`*(S4 *)tbl` and the 2+2
 * split are the same count but different objects).  The tbl store site is now
 * byte-identical.
 * RESIDUE, 26 words / 27 substitutions, is ONE fact: a 4-CYCLE a0->a1->a2->a3
 * in the caller-saved band.  Our tbl temp takes $4 and pushes the ws/wd/n
 * copy loop up to $7/$6/$5; retail gives tbl $7 and reuses $6/$5/$4 for the
 * second loop exactly as for the first.  `n` is ONE variable in our source and
 * retail keeps it in $4 in BOTH loops while we split its web.
 * ⚠⚠ MEASURED FLOOR: 19-cell DECLARATION sweep (n through all 9 scalar slots,
 * {ws,wd} and {hs,hd} as blocks, the whole loop group first), 5 tbl-fill
 * STATEMENT positions, and 4 loop-body respellings of
 * `func_1319A8(&slot[i], &arr[..][i], 0x20)` -- every one is 26 or worse and
 * most collapse onto the baseline object.  Statement position is INERT.
 * ★ NAMED CROSS HALVES, still unpaired: `tbl@post` (the fill moved before
 * `if (post != 0)`) is -1 WORD, and ANY DIFFERENCE between the two index
 * casts in the func_1319A8 line (`&slot[(s32)i]` vs `&arr[..][i]`, all six
 * mixed spellings, ONE object) is +1 WORD.  Their cross IS exact length but
 * scores 70. */
/* !! PARKED at 31 bad words of 157.  RIGHT LENGTH (0x274).  NOT under src/.
 * Three whole blocks already match word for word: the signed `% 2` idiom is
 * present, the 10-slot func_1319A8 loop, the whole `post` tail, and both
 * hand-written copy loops have retail's exact instruction sequence.
 * The residue is entirely REGISTER NUMBERING + SCHEDULE in two places.
 *  (1) 0x004FCCE8-0x004FCD34, the four gp halfword reads and the 640-byte
 *      copy loop.  retail loads D_004805A0/A2/A4 into $7/$3/$2, stores
 *      0x2D8/0x2DA/0x2DC, then loads A6 and stores 0x2DE, and runs the copy
 *      loop on $6(src)/$5(dst)/$4(count).  ours loads A4 FIRST, stores
 *      0x2DC first, and runs the loop on $7/$6/$5 -- every register exactly
 *      one higher, i.e. ours has one more value live across the block.
 *  (2) 0x004FCDA8-0x004FCDDC: ours hoists `sll $3,$17,5 / addu $4,$16,$3`
 *      (the func_1319A8 destination) ABOVE the `% 2` block; retail computes
 *      it in the middle, and the final add is `addu $2,$3,$2` where ours has
 *      `addu $2,$1,$2`.
 * ARMS MEASURED:
 *  A  the three tables as C STRUCT ASSIGNMENTS from externs -> 0x23C, 14
 *     words SHORT: mwcc picks the copy width from a size-derived alignment
 *     (lq/sq for the 640 B and the 16 B, ld/sd for the 8 B) where retail has
 *     lw/sw, lh/sh and four separate lh.  A struct assignment CANNOT
 *     reproduce them.
 *  B  the same three as explicit hand `do {...} while (--n > 0)` pointer
 *     loops (s32 pair for the 640 B, s16 pair for the 16 B) plus FOUR
 *     separate `extern s16` gp globals for the 8-byte one -> RIGHT LENGTH,
 *     31 bad.  This is the arm on disk and it is the correct shape.
 * n38e (2026-09-06/07): three arms tried against arm B, ALL COMPLETE NULLS
 *  -- every one produced a BYTE-IDENTICAL object to arm B (same 31 bad
 *     words, same exact bit patterns at every one of the 31 offsets, not
 *     just the same count):
 *   1. block-scoping the loop temps (hs/hd/n inside a `{}` for the 16 B
 *      copy, ws/wd/n inside a `{}` for the 640 B copy, instead of function-
 *      scope locals) -- NULL, confirmed the exhaustive-negative header note.
 *   2. interleaving the tbl[0..3] assignments with the ws/wd/n setup
 *      statements to mirror retail's own instruction interleave (tbl[0];
 *      ws=...; tbl[1]; wd=...; tbl[2]; n=...; tbl[3]; then the loop) -- NULL.
 *   3. for block (2)'s residue, naming the loop's two `func_1319A8`
 *      arguments as `Cell *src = &arr[row][i]; Cell *dst = &slot[i];`
 *      statements (in that order) before the call, instead of the inline
 *      expressions -- NULL, no effect even combined with arm 2's edit.
 *   4. reordering the outer local decls to put `s32 i;` before
 *      `rec`/`slot`/`q` -- NULL.
 *  mwcc's schedule for both residue blocks is provably insensitive to
 *  source-level statement order and lexical scoping here; this is NOT the
 *  same lever as FACTORY's vreg-creation-order case (there a hoisted-back
 *  statement changed the register MAP while leaving instructions in place;
 *  here every edit left BOTH instructions and registers pixel-identical).
 *  Untried: an unrelated dummy-statement/computation inserted to perturb
 *  the allocator's tie-break directly (per two-edit-cross-beats-count-
 *  ranking.md, a single edit alone is often the wrong probe); reading the
 *  degree/interference graph directly instead of guessing source shapes. */
#include "types.h"
#pragma opt_dead_assignments off
/* normal 0x004FCC90 -- open the 0x3C panel: stage the layout tables on the
 * stack, patch the second row's cells, feed the widget's 10 slots from the
 * parity-selected row and (when asked) post the whole thing. */

typedef struct Cell {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
    s32 f08;
    s32 f0C;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1C;
} Cell;                         /* 0x20 */

typedef struct Pair { s16 x; s16 y; } Pair;
typedef struct S3 { s16 a; s16 b; s16 c; } S3;
typedef struct A640 { s32 w[160]; } A640;

typedef struct Rec {
    u8    pad000[0x20];
    Cell *f20;
} Rec;

typedef struct Gate {
    u8 pad000[0x454];
    u8 f454;
} Gate;

extern s32    normal_D_005251B0[];
extern s16    D_00480590[4];    /* gp - 0x4BE0 */
extern s16    D_004805A0;       /* gp - 0x4BD0 */
extern s16    D_004805A2;       /* gp - 0x4BCE */
extern s16    D_004805A4;       /* gp - 0x4BCC */
extern s16    D_004805A6;       /* gp - 0x4BCA */
extern s16    D_004844E4;       /* gp - 0xC8C  */
extern Gate  *D_00484454;       /* gp - 0xD1C  */
extern void  *D_004844A0;       /* gp - 0xCD0  */
extern void  *D_0048449C;       /* gp - 0xCD4  */
extern void  *D_00484498;       /* gp - 0xCD8  */
extern void  *D_00481BB8;       /* gp - 0x35B8 */

extern void  memcpy(void *dst, const void *src, s32 n);
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

s32 normal_BtlChgMenuMsgBoxOpenState_4fcc90(void *a, s32 post)
{
    s16   tbl[4];
    Pair  pairs[4] __attribute__((aligned(16)));
    Cell  arr[2][10] __attribute__((aligned(16)));
    Rec  *rec;
    Cell *slot;
    s16  *q;
    s16  *hs;
    s16  *hd;
    s32  *ws;
    s32  *wd;
    s32   n;
    s32   i;
    s32   row;

    if (D_00484454->f454 == 0) {
        return 1;
    }
    hs = D_00480590;
    hd = (s16 *)pairs;
    n = 4;
    do {
        hd[0] = hs[0];
        hd[1] = hs[1];
        hs += 2;
        hd += 2;
    } while (--n > 0);

    *(S3 *)tbl = *(S3 *)&D_004805A0;
    tbl[3] = D_004805A6;

    *(A640 *)arr = *(const A640 *)normal_D_005251B0;

    arr[1][0].f04 = 0x15D;
    arr[1][0].f06 = 0x53;
    arr[1][2].f04 = 0x144;
    arr[1][3].f00 = 0x154;
    arr[1][4].f06 = 0x38;
    arr[1][5].f00 = 0x154;
    arr[1][5].f06 = 0x38;
    arr[1][6].f02 = 0x48;
    arr[1][7].f02 = 0x48;
    arr[1][7].f04 = 0x144;
    arr[1][8].f00 = 0x154;
    arr[1][8].f02 = 0x48;

    rec = ((Rec *)UiFindWidget_290460(D_0048449C, 0x3C));
    if (rec != NULL) {
        slot = rec->f20;
        if (slot != NULL) {
            for (i = 0; i < 10; i++) {
                row = (D_004844E4 - 1) % 2;
                memcpy(&slot[i], &arr[row][i], 0x20);
            }
        }
    }
    if (post != 0) {
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F7, 1);
        UiSetWidgetsVisibleById_291110(D_0048449C, 0x3C, 1, 1);
        UiSetTextStringPos_290b20(D_0048449C, 0x3C, MsgTableLookup_28aa30(D_00481BB8, D_004844E4 + 0x6E), -1, -1, 0);
        UiSetWidgetPos_290f60(D_0048449C, 0x3C, pairs[D_004844E4].x, pairs[D_004844E4].y);
        UiSetTextCenteredX_28f300(D_0048449C, 0x3C, 0x100, 0);
        q = ((s16 *)UiGetWidgetText_28f620(D_0048449C, 0x3C, 0));
        if (q != NULL) {
            *q = *q - pairs[D_004844E4].x;
        }
        UiSetTextY_28f550(D_0048449C, 0x3C, tbl[D_004844E4], 0);
    }
    StateMachineSetState_28ede0(D_00484498, 0x560C, 0);
    return 1;
}
