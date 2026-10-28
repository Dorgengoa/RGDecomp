/* rgp:protos */
#define RGP_SELF_normal_HelpMenuDataLoad_524850 1
#include "port/game_protos.h"
#line 1
/* === SESSION 88 (2026-09-22): 76 BAD -> MATCH, exact 150 words, MERGED.
 * Four edits, each measured, and every one of them was reachable only because
 * the PREVIOUS session's verdicts were re-read as CROSS HALVES, not nulls.
 *
 *  1. *** THE DOUBLE-ASSIGNMENT ADDRESS LEVER on the write-back pointer
 *     (levers.d/mwcc-double-assignment-address), 76 -> 36.  s87/d3 had said
 *     "a named byte offset is ALL BYTE-IDENTICAL: mwcc sinks the multiply back
 *     to its use.  A named `pw` pointer hoisted instead is 15 words short (the
 *     D load CSEs)."  Both sentences are that lever's exact trigger: ONE
 *     statement computes the INDEX into the variable, the NEXT reassigns the
 *     same variable to add the BASE --
 *         pw = (Rec *)((u32)j * sizeof(Rec));      <- after `tmp = *pa;`
 *         ... the six pa<-pb copies ...
 *         pw = (Rec *)((u8 *)D_004849E8 + (s32)pw);
 *     Two webs, so the multiply cannot sink and the D load cannot CSE, which
 *     is retail's map exactly (j*118 at idx 50-59, D loaded only at idx 93).
 *     The first assignment's POSITION is the axis: after `tmp = *pa` is 36,
 *     before it is 5 words SHORT, after the f06 copy 39, after f66 70.
 *     s88/c1.py.
 *  2. *** `Rec *pb` DECLARED BEFORE `Rec *pa`, 36 -> 23 (s88/d1.py).
 *  3. *** `s32 i` DECLARED BEFORE `s32 j`, 23 -> 7 (s88/e1.py).  s87/d1 swept
 *     all 6 orders of {j,i,off} and got TWO objects, 76 and 82 -- a null AT
 *     THAT COAT.  At the 23-bad coat the same sweep splits 23 / 7.  A decl
 *     order is a TIE-BREAK; it only shows up once the values it ranks exist.
 *  4. *** THE GUARD IS SPELLED FROM `pa`, 7 -> 1 (s88/f1.py):
 *         if ((*pa).f02 > (*pb).f02)     -- was (*pb).f02 < (*pa).f02
 *     read straight off bad3: retail does `lh $9,0x2($4)` (pa->f02) BEFORE it
 *     computes pb at all, so pa is the guard's LEFT operand.  s61 priced this
 *     spelling at the 0x264 coat as "a different object"; here it is -6.
 *  5. *** THE LAST WORD -- `addu $4,$5,$6` vs retail `addu $4,$6,$5`, pa's
 *     add, pure operand order.  s87/d2 measured the TEXTUAL swap NORMALISED
 *     and that is still true (s88/f1 `offFirst` == base).  What picks the
 *     first operand is the TYPE: *** mwcc emits the POINTER-TYPED operand of
 *     a `ptr + int` FIRST. ***  So make `off` the pointer and D the integer:
 *         u8 *off;  off = (u8 *)(i * sizeof(Rec));
 *         Rec *pa = (Rec *)(off + (s32)D_004849E8);
 *     ALL EIGHT arms of s88/g1.py MATCH -- u8 ptr / s8 ptr / Rec ptr / u32 off, both textual
 *     orders, and the pa double-assignment -- so the discriminator is provably
 *     the OPERAND TYPE and not the text.  (levers.d/mwcc-commutative-add-
 *     operand-order gains a second, stronger rule.)
 * Everything below predates this session and is kept for the map it records.
 */
/* === SESSION 87 (2026-09-22): STILL 76 BAD / 150 words.  FOUR ARMED NULLS.
 * THE MAP, read off the objects (s71's header is right; this is exact):
 *   retail  i=$8  j=$7 off=$6 D=$5 pa=$4 pb=$5 (reuses D's reg) scratch=$3
 *   ours    i=$6  j=$7 off=$5 D=$9 pa=$4 pb=$3            scratch=$9
 * and in the FIRST copy block every one of our registers sits ONE LOWER than
 * retail's because retail has an EXTRA LIVE VALUE there: it computes the
 * write-back address's `j*118` at idx 50/51/53/57/59, inside the first lb/sb
 * loop's preheader, and only loads D_004849E8 at idx 93.  We compute the whole
 * thing at idx 88-97, one block later.
 *  - s87/d1.py: all 6 declaration orders of {j,i,off} = TWO objects (76 with
 *    `i` last, 82 otherwise); `off` computed inside the inner loop does not
 *    compile (C89 mixed decls); `off` inlined into pa is +1 word.
 *  - s87/d2.py: the `+` OPERAND ORDER at pa and at both pb sites, 8 arms.
 *    mwcc NORMALISES it -- every swap that keeps the length is byte-identical
 *    to base, and `(u8 *)D + j*sizeof` (without the (u32) index cast) is the
 *    5-words-short object s71 already recorded.
 *  - s87/d3.py: SPLIT the write-back address -- a named byte offset
 *    `off2 = (u32)j * sizeof(Rec)` at the top of the if (and after `tmp=*pa`,
 *    and as a decl-initialiser, s32 and u32), with the load+add left at the
 *    old site.  ALL BYTE-IDENTICAL: mwcc sinks the multiply back to its use.
 *    A named `pw` pointer hoisted instead is 15 words short (the D load CSEs).
 *  - s87/d4.py: the 68-name `opt_*` table CROSSED with that `off2_top` source
 *    (s71's table sweep was measured against the BASE source, a different
 *    cell).  Armed; three live columns, all length-wrong or worse.
 * ==> the multiply's POSITION is not reachable from C and no optimiser pass
 * pins it.  The next arm has to find what makes retail's block carry the
 * extra live value, not where the source writes it.
 * Everything below predates this session. */
/* === SESSION 71 (2026-09-21, SOLO): LENGTH FIXED -- 0x264 (3 over) -> EXACT
 * 150 words, 76 bad.  NOT merged.  Sweeps build/wf-normal/s71/h1.py, h2.py.
 *  - s31's move deck had put `tmp = *pa;` AFTER pa was overwritten: the swap
 *    was semantically broken.  Restored to the top of the if.
 *  - `#pragma opt_loop_invariants off` (replaces the inert
 *    opt_moveinvariantsinaddressexpr): retail hoists NOTHING here.  The full
 *    opt_* table on/off on top of it is a measured null.
 *  - `off = i * sizeof(Rec);` computed in the OUTER loop and
 *    `pa = (Rec *)((u8 *)D_004849E8 + off);` -- retail keeps i*118 across the
 *    inner loop while reloading D each iteration; no pragma does that.
 *  - write-back through `pb = &D_004849E8[(u32)j];` re-derived after the
 *    pa<-pb copies: retail reloads D ONCE and RECOMPUTES j*118 (the (u32)
 *    index cast breaks the CSE; without it 5 words short).
 *  - `j` declared before `i` (82 -> 76).
 * LEFT: a caller-saved permutation in the loop head -- retail puts the
 * reloaded D and pb in the SAME register ($a1), which pushes off to $a2 and i
 * to $t0; ours gives D $t1 and pb $v1.  Named-base, pb += j, operand-order
 * and index/byte spellings all collapse to the same object.
 */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_tmp_L102_T108_DEREF_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 153 words, ? bad   after: 152 words, ? bad   (retail 150 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
#pragma opt_loop_invariants off
/* === SESSION 61 (2026-09-15, SOLO): current length is 150w / 0x260, retail
 * 0x258 -- TWO WORDS OVER (the s31 header's "0x264/three over" is stale).
 * Tried the s31 header's own named "one real lead" -- the LICM/repositioning
 * pragma family -- individually: `opt_repositioncode off`,
 * `opt_lifetimes off`, `opt_constnonchanging off`, `opt_scalarizeliveranges
 * off`, `opt_serializeassignments off`, each alone alongside the existing
 * `opt_moveinvariantsinaddressexpr off`.  ALL FIVE reproduce the exact same
 * 150w/0x260 object -- the compiler-knob axis this unit was PARKED on for 30
 * sessions is now a clean, citable NULL.  This unit's real residue is still
 * the whole-loop-nest hoisting the s31 body itself describes (retail
 * materialises all eight LICM'd constants inside the swap block instead of a
 * shared preheader); no pragma in the optimizer-settings family turns that
 * off case-by-case, so the fix -- if one exists -- has to be a SOURCE
 * restructuring that stops mwcc from recognising the invariance at all
 * (e.g. breaking the expressions' textual identity across the three
 * lb/sb copy loops), not a knob. Not attempted this session. */
/* PARKED (lane nu06, WF40 P6).  RESIDUE: LENGTH, 0x264 vs 0x258 -- THREE WORDS
 * OVER, and the draft is otherwise the right instruction multiset.  mwcc runs
 * LICM over the whole loop nest and hoists EIGHT loop-invariants into the outer
 * preheader at 0x005248A4-0x005248C4 -- `addiu $9,$29,0x40` (tmp), `addiu
 * $8,$0,0x3B`, `$7,0x20`, `$6,0x10`, `$5,8`, `addiu $4,$29,0x46`,
 * `addiu $3,$29,0x86`, `addiu $15,$29,0xA6` -- which costs a THIRD callee-saved
 * register (`sq $18` / `lq $18`, frame -0xF70 not -0xF80, tmp at $29+0x40 not
 * $29+0x30) and a `daddu` copy at each use.  Instruction census ours vs retail:
 * daddu 17 vs 6, sq 3 vs 2, addiu 50 vs 53, sll 7 vs 10, subu 4 vs 6, lw 3 vs 4.
 * Retail hoists NOTHING: it materialises all eight inside the swap block and
 * RECOMPUTES 118*j a third time for the `list[j] = tmp` copy.
 *
 * The body shape is settled and correct: the 0x3B lh/sh loop is `tmp = *pa`
 * (whole-Rec, align 2), and the three lb/sb loops unrolled by two (0x20/0x10/8
 * iterations) are mwcc's inline copy of the three align-1 sub-STRUCTS -- they
 * count DOWN, so they are compiler copies, not source loops.
 *
 * EXHAUSTIVE ARMS, 4 sweeps / 30 cells, object sha1 in brackets (baseline
 * 70b3ad24 = 0x264):
 *   INERT (byte-identical object to the baseline):
 *     block-scoped `Rec tmp;` inside the if vs function scope [70b3ad24];
 *     s8 vs u8 for the three sub-struct arrays [70b3ad24];
 *     `Rec *pt = &tmp;` used for the third copy [70b3ad24];
 *     `Rec tmp[1];` + `tmp[0]` [70b3ad24];
 *     `tmp` declared BEFORE pa/pb [70b3ad24];
 *     `tmp = D_004849E8[i]` instead of `tmp = *pa` [70b3ad24];
 *     splitting the three s16 into a `Hdr` sub-struct with the third copy as
 *     one OR three member statements [70b3ad24 both].
 *   LIVE BUT WRONG LENGTH:
 *     third copy re-indexed `D_004849E8[j].fXX = tmp.fXX` 0x28c [bb5dc479];
 *     that + tmp at function scope 0x28c [bb5dc479]; + pb/pa decl order 0x28c
 *     [84cb37d3]; + i/j decl order 0x28c [53f383a4];
 *     pb/pa declaration order 0x264 [4420c268]; i/j declaration order 0x264
 *     [049d1a83]; pa/pb declared INSIDE the if 0x264 [00ecfae3];
 *     guard spelled `pa->f02 > pb->f02` 0x264 [2f06060a];
 *     `j <= D_004849F0 - 1` 0x268 [1c10ad1a];
 *     no `pa` (index D_004849E8[i] inline) 0x27c [47912897];
 *     no `pb` 0x29c [b95d3d86];
 *     `Hdr` with the SECOND copy as one assignment 0x26c [54e999e4];
 *     both copies' headers as one assignment 0x2a8 [0504d08f];
 *     the three tail copies written as SOURCE for-loops over s8 arrays --
 *     0x1fc, i.e. 23 words SHORT, with the loop counter at block scope OR at
 *     function scope giving ONE object [4dc72f4a both].  So the byte loops are
 *     definitely NOT source loops.
 *   NOT TRIED (forbidden this session): the compiler-knob axis.  The next
 *     session's one real lead is a pragma that disables LICM / code
 *     repositioning (`opt_constnonchanging`, `opt_repositioncode`,
 *     `opt_lifetimes`) -- this is a HOISTING residue, not a spelling one, and
 *     four sweeps of the spelling axis have now measured it null.
 */
/* normal 0x00524850 -- runs the normal_D_005260D0 command list into the 0x76-byte
 * record array D_004849E8, then selection/bubble-sorts it ascending on the
 * s16 at +0x02.  frame -0xF80 = 0x30 save area, the swap temp at $29+0x30
 * (0x76 B) and the 0xED0-byte ScriptVm at $29+0xB0, so the two stack objects
 * are declared vm-then-tmp (mwcc allocates in REVERSE declaration order).
 *
 * ONE lh/sh copy loop of 0x3B (`tmp = list[i]`, whole-struct, align 2) but
 * TWO field-wise copies -- three interleaved lh/sh plus three unrolled-by-two
 * lb/sb loops of 0x20/0x10/0x08 iterations.  Those byte loops are mwcc's
 * inline copy of an align-1 sub-STRUCT, not source loops (they count DOWN),
 * so the tail three members are wrapped in their own struct types.
 */

typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;
typedef struct B40 { s8 b[0x40]; } B40;
typedef struct B20 { s8 b[0x20]; } B20;
typedef struct B10 { s8 b[0x10]; } B10;
typedef struct Rec { s16 f00; s16 f02; s16 f04; B40 f06; B20 f46; B10 f66; } Rec;

extern u8 normal_D_005260D0[];

extern Rec *D_004849E8;           /* gp - 0x788 */
extern s32  D_004849EC;           /* gp - 0x784 */
extern s32  D_004849F0;           /* gp - 0x780 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_HelpMenuDataLoad_524850(s32 a, s32 b)
{
    ScriptVm vm __attribute__((aligned(16)));
    s32      i;
    s32      j;
    u8      *off;

    D_004849EC = 0;
    TextReaderCtor_15f140(&vm);
    BuildKeywordHashTable_15f270(&vm, normal_D_005260D0);
    TextReaderOpen_15f1b0(&vm, a, b);
    TextReaderParseAll_15f3f0(&vm);

    for (i = 0; i < D_004849F0 - 1; i++) {
        off = (u8 *)(i * sizeof(Rec));
        for (j = i + 1; j < D_004849F0; j++) {
            Rec *pb = &D_004849E8[j];
            Rec *pa = (Rec *)(off + (s32)D_004849E8);
            Rec *pw;

            if ((*pa).f02 > (*pb).f02) {
                Rec tmp __attribute__((aligned(16)));

                tmp = *pa;
                pw = (Rec *)((u32)j * sizeof(Rec));
                (*pa).f00 = (*pb).f00;
                (*pa).f02 = (*pb).f02;
                (*pa).f04 = (*pb).f04;
                (*pa).f06 = (*pb).f06;
                (*pa).f46 = (*pb).f46;
                (*pa).f66 = (*pb).f66;
                pw = (Rec *)((u8 *)D_004849E8 + (s32)pw);
                pw->f00 = tmp.f00;
                pw->f02 = tmp.f02;
                pw->f04 = tmp.f04;
                pw->f06 = tmp.f06;
                pw->f46 = tmp.f46;
                pw->f66 = tmp.f66;
            }
        }
    }
}
