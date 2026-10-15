/* ==== SOLVED, lane im36, 2026-08-27 -- BYTE-IDENTICAL (153 words, 0 bad) ===
 * Everything below this block is the parked record and is now HISTORY; two of
 * its headline claims are RETRACTED by measurement.
 *
 * (a) RETRACTED: "the length and the register swap are the same defect" and
 *     "retail's cell is NOT REACHABLE".  With `#pragma opt_dead_assignments
 *     off` and the arm-0 anti-CSE cast both in place, the object was already
 *     STRUCTURALLY EXACT -- retail's six-instruction re-materialisation of
 *     &D_004FA1D0[i] inside the i == 0 arm WAS being emitted -- and all 12 bad
 *     words were one crossed 2-colouring.  The CSE cost split was NOT the
 *     blocker here, so this unit says nothing about the three NORMAL units.
 *
 * (b) The four live ranges and their colours:
 *       web          def         ours   retail
 *       head `e`     0x4F33C0     $17    $16
 *       arm-0 `e`    0x4F3424     $16    $16
 *       arm-0 `h`    0x4F3434     $17    $17
 *       arm-2 `h`    0x4F352C     $16    $17
 *     They interfere on exactly TWO edges -- arm0-e x arm0-h, and head-e x
 *     arm2-h (because `e` is used again at 0x4F3574, AFTER arm-2's `h` dies).
 *     A four-node graph with two disjoint edges has exactly two proper
 *     2-colourings; we had the other one.  That is why every spelling that
 *     preserved the source shape returned the same two objects.
 *
 * (c) ** THE FIX: give arm 2 its OWN `h2`, declared BETWEEN `i` AND `e`. **
 *     Splitting `h` was already known to move head-e onto $16; what was never
 *     measured is the new variable's declaration POSITION:
 *         h2 first / h2 before i / h2 after h  -> 19 bad (a0H = a2H = $18)
 *         h2 LAST, after e                     -> INERT, still 12 bad
 *         h2 BETWEEN i AND e                   -> ** 0 bad, byte-identical **
 *     The recorded verdict "h's declaration position is INERT (six arms, all
 *     byte-identical)" was measured on the UNSPLIT `h` and does NOT transfer
 *     to the split one.  Split first, THEN sweep the position.
 *
 * (d) Still load-bearing, do not simplify away: `#pragma opt_dead_assignments
 *     off` (drop it -> 0x258) and the arm-0
 *     `(const Slot *)((const u8 *)D_004FA1D0 + i * 56)` cast written at BOTH
 *     arm-0 sites (drop it -> 0x24C).  Naming that cast expression, in any of
 *     seven positions, re-enables the CSE and costs 3 words.
 * ========================================================================= */
/* ==== LANE C2 (tag im12), 2026-08-26 -- THE RANKING IS NOW MAPPED =========
 * Still parked at 12 bad words, right length (153 words = 0x264).  Baseline
 * REPRODUCED (build/os_im01.py insmenu --tag im12, object 6f472945).
 *
 * (1) ** THE RESIDUE IS A TOTAL ORDER OVER FOUR VALUES, AND RETAIL'S ORDER IS
 *     NOT REACHABLE FROM ANY SPELLING MEASURED SO FAR. **  Callee-saved
 *     registers are handed out $16,$17,$18,$19 down one ranking:
 *         retail          e, h, i, buf
 *         this file       h, e, i, buf      (12 bad)
 *     TWO independent levers move that ranking, and between them they reach
 *     exactly FOUR cells, none of which is retail's:
 *       LEVER A -- the relative DECLARATION ORDER of `e` and `i` swaps those
 *         two and nothing else.  `h`'s and `buf`'s declaration positions are
 *         INERT (h first / h last / h between / buf first / buf mid: six arms,
 *         all byte-identical to the baseline).
 *       LEVER B -- whether the arm-2 `h` is a variable used ONLY in arm 2.
 *         If it is, `h` falls from rank 1 to rank 3: e,i,h,buf (19 bad, and
 *         ALL EIGHT `move a0,s0` words become CORRECT -- `e` is $16 there).
 *         If the arm-2 `h` shares a variable with anything else, rank 1.
 *         Measured over all five partitions of {arm0,arm1,arm2}: {a0a1a2},
 *         {a0|a1a2}, {a0a2|a1} give rank 1; {a0a1|a2}, {a0|a1|a2} give rank 3.
 *     Cells: h,e,i,buf = 12 (6f472945); h,i,e,buf = 29 (f7f41e2b);
 *            e,i,h,buf = 19 (cfa652aa); i,e,h,buf = 32 (64eb6d40).
 *     WANTED: e,h,i,buf.  `h` never lands on rank 2.
 *     Specs: build/vsp_im12_3370b.py, _3370c.py, _3370d.py, _3370g.py.
 *
 * (2) REF-COUNT IS NOT THE RANKING KEY -- refuted with an artefact.  Adding
 *     two references to `e` (re-assigning it in the i==0 arm and using that
 *     name at the first arm-0 call site, arm remat_to_e_first) gives an object
 *     BYTE-IDENTICAL to the baseline.  So does removing the `e` VARIABLE
 *     entirely and writing `&D_004FA1D0[i]` at all seven use sites (arm
 *     noe_all), and so does inlining it at only the guards or only the tails.
 *     A named variable and a CSE temp are the same thing to this allocator.
 *
 * (3) P1's INTERMEDIATE-LOCAL ESCAPE IS ABSORBED HERE -- re-confirmed.
 *     `t = func_28B270(...); h = t;` in arm 0, and in arms 0+1+2, with `t`
 *     declared before or after `i`: all four arms byte-identical to the
 *     baseline.  `register` on `e` or on `h`: byte-identical.  A
 *     `const Slot *const e` declared inside the loop: byte-identical.
 *
 * (4) TWO NEW WAYS TO LOSE THE LENGTH: assigning the arm-0 cast expression to
 *     `e` (or to a fresh `e2`) and then using that name at BOTH arm-0 sites
 *     re-enables the CSE and costs 3 words (0x258).  Using the name at only
 *     the FIRST site is byte-identical to writing the cast out twice.
 *
 * (5) COMPILER-KNOB AXIS: CLOSED.  build/kb_im12.py --all = 488 variants,
 *     467 INERT / 21 live, floor 12, nothing under.  Log
 *     build/im12_knob_f3370.txt.  (`opt_pointer_analysis on` dumps core;
 *     `opt_rotateloops off` 14, `opt_propagation off` 40, and every other live
 *     arm breaks the length.)  This supersedes the 117-variant BUILTIN screen
 *     in build/imk-scratch/insmenu_InsectVsMenuResPoll_4f3370/.
 * ========================================================================= */
/* PARKED 2026-08-26, lane L4 (im04).  RIGHT LENGTH (153 words = 0x264) at
 * 12 BAD WORDS -- the DANGEROUS class: i_olink's length guard would PASS it.
 * Moved out of src/overlays/insmenu/ per the parking protocol.
 *
 * Residue: a single $16 <-> $17 allocation swap.  Retail allocates
 * e=$16, h=$17, i=$18, buf=$19; we get h=$16, e=$17.  All 12 wrong words are
 * `daddu $4,$16/$17,$0` argument moves plus the two defining moves at
 * 0x004F33C0 and 0x004F352C.
 *
 * NEW MEASURED NEGATIVES (session 10, lane L4; 20 arms over 2 vsweep round
 * trips, build/v_im04_3370.py and build/v_im04_3370b.py):
 *  - Retail RE-MATERIALISES &D_004FA1D0[i] into $16 inside the i==0 arm.  That
 *    is a CSE cost split (levers.d/normal-cse-cost-split), not a spelling.
 *    `e = &D_004FA1D0[i];` re-assigned at the top of the arm is CSE'd to the
 *    IDENTICAL object as plain `e` -- hash 916ec3bc, 0x24c, SIX words short --
 *    and `#pragma opt_dead_assignments off` (already in this file) does not
 *    preserve it.  So does `e = D_004FA1D0 + i;`, a separate arm-local `e0`,
 *    and opt_loop_invariants_off / opt_moveinvariantsinaddressexpr_off /
 *    opt_optimizenonregaccess_off / opt_marknonregtemps_on: all five give the
 *    SAME hash 916ec3bc.
 *  - `#pragma opt_common_subs off` DOES defeat the CSE but overshoots to 0x268
 *    (one word LONG) and adds four NEW defects while leaving the $16/$17 swap
 *    untouched: `bnezl` for retail's `bnez` at 0x004F33FC and an extra gp
 *    reload of D_00484104 at 0x004F34CC.  opt_propagation_off 0x258,
 *    opt_lifetimes_off 0x248, `e` as `volatile` pointer 0x24c.
 *  - INERT (object hash identical to the baseline, i.e. measured NOTHING):
 *    `h` declared per-arm, and a fully non-const `Slot *` view of the array
 *    and its five callee prototypes.
 *  - The 6-word gap between plain `e` (0x24c) and retail (0x264) is EXACTLY
 *    retail's `sll/lui/subu/addiu/sll/addu` re-materialisation, so the length
 *    and the register swap are the same defect, not two.
 * Prior negatives retained below.
 */
/* !! SESSION 9 (2026-08-25): THIS UNIT IS NOW RIGHT LENGTH AT 12 BAD WORDS AND
 * MUST STAY OUT OF config/ocunits/insmenu.txt.  It used to be 3 words SHORT, so
 * i_olink's length guard caught it; `#pragma opt_dead_assignments off` (added
 * below) fixed the length and the guard would now PASS it and emit a differing
 * image with no signal saying which unit did it.  Improving a parked unit can
 * make it MORE dangerous to admit.
 * 
 * The 12 are one $16 <-> $17 swap: retail allocates e=$16, h=$17, i=$18, buf=$19
 * and we get h=$16, e=$17.  All 24 declaration orders of the four register
 * locals were enumerated (build/imv/v3370_perm.py) and they collapse to exactly
 * TWO distinct objects -- only `e` before/after `i` matters, at 29 and 12, and
 * neither side is retail.  Declaration order is a measured null here.
 * Removing the anti-CSE cast in the i == 0 arm loses the length again (0x24C),
 * so the pragma and the cast are fixing DIFFERENT words and both are needed.
 */
#pragma opt_dead_assignments off
#include "types.h"

/* insmenu 0x004F3370 (612 bytes, 156 instructions, 25 calls) -- pump the three
 * async load slots.  Each slot is 56 bytes, which is why the index arithmetic
 * is `sll 3 / subu / sll 3` rather than a multiply.
 *
 * The head guard is the inverted early return: retail branches INTO the body
 * and falls through to `b <epilogue> / daddu $2, $0, $0`, so the source reads
 * `if (D_00484300 != 1) { return 0; }`.
 *
 * PARKED AT 3 WORDS SHORT (0x258 against 0x264), a LENGTH defect.  Retail
 * RE-MATERIALISES `&D_004FA1D0[i]` inside the i == 0 arm after func_14D8E0 --
 * six instructions, `sll / lui / subu / addiu / sll / addu` -- even though the
 * pointer is already live in $16, which is callee-saved.  Our build CSEs it.
 * Writing the arm's two uses as `(const Slot *)((const u8 *)D_004FA1D0 + i*56)`
 * defeats HALF the CSE and recovers 3 of the 6 (it re-materialises the base but
 * still reuses `i * 56`); that is the spelling in this file.  Measured and not
 * better: the plain index form in the arm (6 short), a `static inline` helper
 * carrying the arm's body (6 short), the cast form in the HEAD instead (3 words
 * LONG), and a named `const Slot *e` for the head with the cast in the arm
 * (unchanged at 3 short).
 * ★ The tail guard IS fixed and is worth keeping: retail's exit is
 * `bnel $2, $3, <epilogue>` carrying `daddu $2, $0, $0`, so the source is the
 * POSITIVELY guarded `if (func_28B070(...) == 1) { ...; return 1; } return 0;`
 * -- the epilogue-merge lever.  The inverted early return costs 2 words.
 *
 * `bgez / sra 4 / addiu 0xF / sra 4` is just `n / 16` on a signed int; m2c
 * writes the bias out longhand and the plain division compiles to the same
 * four instructions.
 */

typedef struct Slot Slot;
struct Slot {
    u8 pad00[56];
};

extern const Slot D_004FA1D0[3];
extern const u8 D_004F9FF0[];
extern const u8 D_004FA008[];
extern const u8 D_004FA020[];

extern s16 D_00484300;      /* gp - 0xE70 */
extern s32 D_004842E0;      /* gp - 0xE90 */
extern s32 D_004842F8;      /* gp - 0xE78 */
extern s32 D_004842FC;      /* gp - 0xE74 */
extern s32 D_00484104;      /* gp - 0x106C */

extern void func_1F59D0(void);
extern s32 func_28B220(const Slot *a);
extern s32 func_28B210(const Slot *a);
extern s32 func_28B2E0(const Slot *a);
extern void func_14D8E0(s32 a);
extern s32 func_28B270(const Slot *a, s32 *b);
extern s32 func_206A40(void);
extern void func_42B840(s32 a, s32 b, s32 c, s32 d, s32 e);
extern s32 func_202A50(s32 a, const void *b, s32 c);
extern s32 func_1C2800(s32 a, const void *b, s32 *c);
extern void func_376B40(s32 a, s32 b, s32 c);
extern void func_202BE0(s32 a, const void *b, s32 c, s32 d, s32 e);
extern void func_28B230(const Slot *a);
extern void func_4366F0(s32 a, s32 b, s32 c);
extern void func_436450(s32 a, s32 b);
extern s32 insmenu_InsectVsGetSaveCtx_4f3850(void);
extern s32 func_14DA10(s32 a, s32 b);
extern void func_1319A8(s32 a, s32 b, s32 c);
extern void func_37BBD0(s32 a, s32 b);
extern s32 func_28B070(const void *a, s32 b);
extern void insmenu_InsectVsMenuSetupWidgets_4f3670(void);

s32 insmenu_InsectVsMenuResPoll_4f3370(void)
{
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 h;
    s32 buf;
    s32 i;
    s32 h2;
    const Slot *e;

    if (D_00484300 != 1) {
        return 0;
    }
    func_1F59D0();
    for (i = 0; i < 3; i++) {
        e = &D_004FA1D0[i];
        if (func_28B220(e) == -1) {
            continue;
        }
        if (func_28B210(e) == 0) {
            continue;
        }
        if (func_28B2E0(e) != 1) {
            continue;
        }
        if (i == 0) {
            func_14D8E0(D_004842E0);
                h = func_28B270((const Slot *)((const u8 *)D_004FA1D0 + i * 56), &sp5C);
            func_42B840(func_206A40(), 1, 0xF, D_004842E0, h);
            D_004842FC = func_202A50(h, D_004F9FF0, D_004842E0);
            func_376B40(D_004842E0, func_1C2800(h, D_004FA008, &sp5C), sp5C);
            func_202BE0(h, D_004FA020, D_004842E0, 0x32D, 0);
            func_28B230((const Slot *)((const u8 *)D_004FA1D0 + i * 56));
        } else if (i == 1) {
            h = func_28B270(e, &sp58);
            if (D_00484104 != 0) {
                func_4366F0(D_00484104, D_004842E0, h);
                func_436450(D_00484104, 0);
            }
            func_28B230(e);
        } else if (i == 2) {
            if (insmenu_InsectVsGetSaveCtx_4f3850() != 0) {
                h2 = func_28B270(e, &sp54);
                buf = func_14DA10(D_004842E0, sp54 / 16 + 1);
                if (buf != 0) {
                    func_1319A8(buf, h2, sp54);
                    func_37BBD0(D_004842F8, buf);
                }
            }
            func_28B230(e);
        }
    }
    if (func_28B070(D_004FA1D0, 3) == 1) {
        insmenu_InsectVsMenuSetupWidgets_4f3670();
        return 1;
    }
    return 0;
}
