/* SESSION 39 (n39a, SOLO): 2 bad -> MATCH, 81/81 words, byte-identical.
 * The residue session 38 wrote off as "pure register-choice, no source-shape
 * lever" was a CALLEE SIGNATURE defect, not a register-colouring artifact.
 * func_1CD4F0 is a TWO-argument function -- (void *h, s32 id) -- in every
 * other unit of the corpus that calls it (src/overlays/insect/*, src/wf17/
 * factory/factory_FactoryMenuResReady_4ec0e0.c and factory_FactoryHelpPageLoadPoll_4f1ce0.c, both merged,
 * src/overlays/normal/normal_ShopMenuResPoll_50ae40.c, normal_HelpMenuPageLoadState_5220b0.c).  This
 * unit declared it with ONE arg.  Writing
 *     D_004807BC = func_1CD4F0(h, D_004807B8);
 * makes retail's `lw $5,-0x49B8($28)` at 0x005246A0 what it always was: the
 * SECOND ARGUMENT setup, hoisted into the beql branch-likely delay slot,
 * with the `D_004807B8 == -1` guard at 0x005246B0 REUSING the argument
 * register.  Ours was loading the same global into v1 purely as a guard
 * temp.  One edit, both bad words gone.
 * LESSON, generalisable: before calling a two-word register residue a
 * scheduler artifact, run [[merged-callee-signature-oracle]] over every
 * extern in the file -- a MISSING TRAILING ARGUMENT reads exactly like a
 * wrong register choice, because the argument setup is scheduled far from
 * the call and the guard that reuses it looks like an unrelated load.
 * (normal_SpaceMenuResPollState_510e30.c, this unit's own sibling, still declares
 * func_1CD4F0 with one arg -- it is open, check it there too.) */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_D_004849BC_L54_T59_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 81 words, 48 bad   after: 81 words, 25 bad   (retail 81 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_D_004849C4_L54_T66_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 81 words, 53 bad   after: 81 words, 48 bad   (retail 81 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
#include "types.h"
/* SESSION 30: 58 -> 53 bad on two axes in series -- a defining-statement move
 * (`D_004849C4 = 1;` hoisted above `D_004849BC = 1;`) then the EXIT SINK
 * (`return 0;` at the first site replaced by `goto _s302;` with the return
 * re-introduced at the END of the body).  The sink is the axis that closed
 * 0050b570; s29's exit screen could not reach it because that screen only
 * touched return VALUES returned MORE THAN ONCE.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* normal 0x00524680 -- the sibling of normal_FUN_00510E30 on its own latch
 * pair (0x004807BC / 0x004807B8); the extra arm is gated on the gp s16 at
 * 0x004849F4 being 1. */
/* SESSION 38 (n38g): 25 -> 2 bad, still 81/81 words.
 * Fix (CONFIRMED, the whole move): `D_004849BC = 1;` must be the LAST
 * defining statement before `func_1CD340(h, D_004807B8);`, not right after
 * `D_004849B4 = func_202A50(...)` -- retail's `sb $2,-0x7B4($28)` sits in
 * the delay slot of the `jal func_1CD340`, not up near func_202A50. Moving
 * just this one statement down past func_202BE0 and the `D_004849F4==1`
 * guard closed 23 of the 25 bad words in one move (this is the SAME class
 * as session 30's `D_004849C4 = 1;` hoist -- read the defining STATEMENT
 * POSITION off the disassembly, don't assume decl-adjacent source order).
 * MEASURED NULL on the residue: merging the two early guards into
 * `if (D_004807BC != 0 || D_004807B8 == -1) return 1;` (worse, 31 bad --
 * wrong shape for this pair, unlike [[normal-guard-pair-or]]'s same-value
 * pairs); reading `D_004807B8` into a named local before the second guard
 * and reusing it at the `func_1CD490` call (worse, 3 bad -- promotes the
 * value to a callee-saved reg s1 across the intervening calls, which
 * retail does not do; retail RELOADS the global from memory at every use).
 * Residue (2 bad, exact length): retail's second guard
 * (`D_004807B8 == -1`) loads the global into $5(a1) in the first guard's
 * branch-likely delay slot; ours loads the identical value into v1(3) in
 * the same delay slot -- same position, same instruction, wrong register.
 * Pure register-choice, no source-shape lever found this session. */
extern s32   D_004807BC;          /* gp - 0x49B4 */
extern s32   D_004807B8;          /* gp - 0x49B8 */
extern void *D_0048499C;          /* gp - 0x7D4  */
extern void *D_004849B4;          /* gp - 0x7BC  */
extern s16   D_004849F4;          /* gp - 0x77C  */
extern u8    D_004849BC;          /* gp - 0x7B4  */
extern s16   D_004849C4;          /* gp - 0x7AC  */
extern u8    D_005268D0[];
extern u8    D_005268F0[];
extern u8    D_00526908[];

extern void *func_1F59D0(void);
extern s32   func_1CD4F0(void *h, s32 id);
extern void *func_15DE40(void);
extern void  func_14D8E0(void *p);
extern void  func_14D9D0(void *p, s32 k);
extern void *func_1CD490(void *h, s32 id, s32 *out);
extern void *func_206A40(void);
extern void  func_42B840(void *a, s32 b, s32 c, void *d, void *e);
extern void *func_202A50(void *a, u8 *b, void *c);
extern void  func_202BE0(void *a, u8 *b, void *c, s32 d, s32 e);
extern void *func_1C2800(void *a, u8 *b, s32 *out);
extern void  normal_HelpMenuDataLoad_524850(void *a, s32 k);
extern void  func_1CD340(void *h, s32 id);

s32 normal_InsectEntryMenuResPoll_524680(void)
{
    void *h;
    void *q;
    s32   tmp;

    h = func_1F59D0();
    if (D_004807BC != 0) {
        return 1;
    }
    if (D_004807B8 == -1) {
        return 1;
    }
    D_004807BC = func_1CD4F0(h, D_004807B8);
    if (D_004807BC != 1) {
        goto _s302;
    }
    func_15DE40();
    func_14D8E0(D_0048499C);
    func_14D9D0(D_0048499C, 1);
    q = func_1CD490(h, D_004807B8, &tmp);
    func_42B840(func_206A40(), 2, 0xB, D_0048499C, q);
    D_004849B4 = func_202A50(q, D_005268D0, D_0048499C);
    func_202BE0(q, D_005268F0, D_0048499C, 0x32D, 0);
    if (D_004849F4 == 1) {
        normal_HelpMenuDataLoad_524850(func_1C2800(q, D_00526908, &tmp), tmp);
    }
    D_004849BC = 1;
    func_1CD340(h, D_004807B8);
    D_004807B8 = -1;
    D_004849C4 = 1;
    return 1;
_s302:
    return 0;
}
