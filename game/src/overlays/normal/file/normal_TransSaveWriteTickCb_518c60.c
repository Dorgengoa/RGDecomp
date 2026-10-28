/* rgp:protos */
#define RGP_SELF_normal_TransSaveWriteTickCb_518c60 1
#include "port/game_protos.h"
#line 1
/* === SESSION 50 (2026-09-08, SOLO): 4 BAD -> BYTE-IDENTICAL, 235 words.
 * MERGED into config/ocunits/normal.txt under the session 50 marker.
 * THE WHOLE CLOSE IS ONE LINE: `#pragma opt_propagation off` after the
 * #include.  `#pragma opt_dead_assignments off` gives the IDENTICAL object
 * (52a239b8), and so does the pair.
 *
 * WHAT IT FIXED is exactly the residue s47 named and 33 arms could not reach:
 * retail loads `b = e->fC` BEFORE `a = e->f18` and then computes arg2
 * (`lh $5,0xF8($4)`) before the jal, leaving arg3 (`ld $6,0x8($3)`) to sink
 * into the delay slot; we did the mirror image.  mwcc's propagation pass was
 * reordering the two pointer loads.  s47's note that the scheduler "is
 * choosing by OPERAND COST" is retired -- it was choosing by a propagation
 * result, and the knob is exposed.
 *
 * ARMED FOUR WAYS (build/wf-normal/s50/a_518c60b.py):
 *   - `/ * nothing * /` injected in the same place  == BASE (fad40aa5);
 *   - `#pragma opt_propagatioN off` (bogus name)    == BASE;
 *   - `#pragma opt_unroll_count off` (a real name that takes a NUMBER)
 *     FAILS TO BUILD, so the compiler is provably reading its pragma table;
 *   - `opt_propagation off` immediately followed by `opt_propagation on`
 *     == BASE, so the pragma's SCOPE is what does the work.
 * ⚠ THE 13 SOURCE ARMS THIS SESSION ADDED TO s47's 33 ARE ALL STILL NULL --
 * the call really is canonicalised; do not spend more arms on its spelling.
 * ⚠⚠ s42 recorded "the PRAGMA channel is EXHAUSTED on normal".  It is not.
 * See [[levers.d/normal-session50-levers]]. */
/* === SESSION 47 (2026-09-07, SOLO): 193 -> 4 BAD on 235 words, exact length,
 * and the OPCODE MULTISET IS NOW EXACT (opscan d=0).  Four source facts, all
 * read straight off the retail listing:
 *
 *  1. ★ THE DISPATCH IS A `switch`, NOT AN if/else-if CHAIN.  Retail's head is
 *     `beq/beql $3,$2,<arm>` x5 with `b .L00518FFC` as the DEFAULT -- branches
 *     INTO each arm ([[insect-dispatch-branch-polarity]]).  The arm BODIES sit
 *     at ASCENDING addresses for cases 0,1,2,3,4 (0x518D24, D64, E50, E88,
 *     F6C) while the COMPARE CHAIN runs 4,3,2,1,0: mwcc emits bodies in SOURCE
 *     order and tests in REVERSE ([[m2c-switch-arm-order]]).  So the source is
 *     `switch (state)` with cases written 0,1,2,3,4 and a `break` in each.
 *     Measured: switch(0..4) 0x3b8, switch(4..0) 0x3bc, if-chain(0..4) 0x3a4,
 *     if-chain(4..0) 0x3ac -- only the switch reaches retail's arm LAYOUT.
 *  2. `D_00484818 = D_00484818 + 1;` is the LAST statement of every arm that
 *     has it (cases 1-inner, 2, 3-else).  Retail's arm tails are uniformly
 *     `lh $2,-0x958 / addiu $2,$2,1 / b .L00518FF8 / sh $2,-0x958`.  This one
 *     move is what took the switch from length-wrong to 18 bad.
 *  3. case 4's inner test is INVERTED: retail is
 *     `if (normal_TransMenuIsQuickOpen_514a00() != 0) { func_28EA90(...); } else { ... }`
 *     -- it emits the func_28EA90 arm FIRST.
 *  4. `EntB *b = (EntB *)e->fC;` is declared BEFORE `EntC *a = (EntC *)e->f18;`
 *     (retail loads 0xC before 0x18), and `Ent.f18` is at 0x18, NOT packed
 *     against fC -- the draft had it at 0x10.
 *
 * ⚠ RESIDUE, 4 words at 0x00518F40-0x00518F50, and it is ONE FACT: retail puts
 * arg3 `b->f8` (an `ld`) in the jal DELAY SLOT and computes arg2 `a->fF8`
 * (`lh`) before the jal; we do the reverse.  DIAGNOSTIC THAT NAMES IT: spelling
 * arg3 as `&b->f8` (with the signature changed to take a pointer) produces
 * retail's EXACT schedule at 2 bad, wrong only in the opcode (`addiu a2,v0,8`
 * where retail has `ld $6,0x8($3)`).  So mwcc's scheduler is choosing by
 * OPERAND COST -- an address is cheap enough to sink into the delay slot, a
 * 64-bit load is not.  The open question is a 64-bit READ that still sinks.
 *
 * MEASURED NULLS (33 arms, ARMED -- the baseline object is fad40aa5 and the
 * `&b->f8` arm moved it).  ALL of these are ONE OBJECT, byte-identical to the
 * baseline: every naming of the two operands (h/v temps in both orders, s16 /
 * u16 / s32 for h, u64 / (s64)(u64) / ((s64*)b)[1] / *(&b->f8) /
 * *(volatile s64 *)&b->f8 / *(s64 *)((u8 *)e->fC + 8) for v), both declaration
 * orders of a and b, fully inlined arguments, `void *pa` for arg1, e/a/b/r
 * hoisted to function scope, the two nested blocks flattened, `if (e)` vs
 * `if (e != NULL)`, EntB respelled as two s64 fields, and the callee signature
 * as (EntC*,s16,s64) / (void*,s32,s64) / (void*,s16,u64).  mwcc canonicalises
 * this whole call -- do NOT spend more arms on the call's SPELLING.
 * Swapping the Rec2 block and the Ent block is +13 (17 bad).
 * KEEP OUT OF config/ocunits/normal.txt. */
/* SESSION 31 STAGE 2 (same six decks, re-run from the stage-1 bases).
 * Installed arm `MV_D_00484818_L122_T120_SAFE_mov` from the DEFINING-STATEMENT MOVE deck.
 *   before: 233 words, ? bad   after: 234 words, ? bad   (retail 235 words)
 * Everything below predates THIS install; read older numbers as history.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py. */
/* SESSION 31 (combined six-deck sweep, 31,338 arms over 98 units).
 * Installed arm `MV_D_00484818_L115_T95_SAFE_mov` from the DEFINING-STATEMENT MOVE deck (mkmove31.py)
 *   before: 232 words, ? bad   after: 233 words, ? bad   (retail 235 words)
 * Every line BELOW this note predates that install -- read its numbers
 * as the state at the time it was written, not as the current score.
 * Re-score with build/wf-normal/s31/nscore.py, not dv_osbuild.py.
 * KEEP OUT OF config/ocunits/normal.txt. */
/* ===== LANE nd, session 19 -- NOT ATTEMPTED (baseline scored only, 1 trip).
 * 3 words SHORT (0x3a0 vs 0x3ac).  n_odiff shows FOUR whole-block MOVES:
 * ours[35:135] <-> retail[80:124], ours[149:157] <-> retail[138:195],
 * ours[163:227] <-> retail[201:230].  Our if/else arms are emitted in a
 * different ORDER than retail's, so this needs the arm order of a 24-call
 * state machine re-derived off the listing, not a spelling.
 * ★ FIRST THING TO TRY: retail's dispatch is
 *   `lh $3,-0x958($28) / beql $3,$2(=3),.L00518CE4 / beq $3,$2(=2),.L00518CE0`
 * -- `beql` INTO the arm, so per [[insect-dispatch-branch-polarity]] the
 * D_00484818 dispatch is a SWITCH whose source case order is the compare chain
 * REVERSED.  The draft has no `switch` at all, only if/else.  The same read
 * closed the block moves on normal_MenuBattleEndLevelUpLabelUpdate_4ea3f0 in this lane.
 * The lane's budget went to the eight units with a localised diagnosis. */
#include "types.h"
#pragma opt_propagation off

typedef struct Ent  { u8 pad00[0xC]; void *fC; u8 pad10[0x8]; void *f18; } Ent;
typedef struct EntB { u8 pad00[0x8]; s64 f8; } EntB;
typedef struct EntC { u8 pad00[0xF8]; s16 fF8; } EntC;
typedef struct Rec2 { u8 pad00[0x16]; s16 f16; } Rec2;

extern u8 D_004B2570[];

extern s16    D_00484818;          /* gp - 0x958 */
extern s32    D_0048481C;          /* gp - 0x954 */
extern void  *D_004847D4;          /* gp - 0x99C */
extern s32    D_004847F4;          /* gp - 0x97C */
extern s32    D_004847F0;          /* gp - 0x980 */
extern void  *D_004847D0;          /* gp - 0x9A0 */
extern void  *D_004847D8;          /* gp - 0x998 */
extern s16    D_004847EC;          /* gp - 0x984 */
extern s16    D_004847E8;          /* gp - 0x988 */
extern s32   *D_00484744;          /* gp - 0xA2C */
extern f32    D_0047D34C;          /* gp - 0x7E24 */

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

s32 normal_TransSaveWriteTickCb_518c60(void)
{
    s16 state;
    s32 t16;

    state = D_00484818;
    if ((state != 3) && (state != 2) &&
        ((t16 = ((short)SaveGetResultStatus_37b970()), ((SavePortCardIsReady_37b9b0(1) & 0xFF) == 0)) ||
         (t16 == 6) || (t16 == 5) || (t16 == 8))) {
        normal_TransSaveSetError_51a000(8);
        return 1;
    }
    {
        state = D_00484818;
        switch (state) {
        case 0:
            normal_TransSaveShowMsg_519ff0(5);
            D_0048481C = 1;
            normal_TransSaveYesNoCursorBob_5188c0(1, 1, 1);
            SaveUiHideWidget_37b460(0x75A2);
            normal_TransSaveProgressWindowShow_519e50(1, 0);
            D_00484818 = D_00484818 + 1;
            break;
        case 1:
            MenuYesNoCursorInput_377180(&D_0048481C);
            normal_TransSaveYesNoCursorBob_5188c0(D_0048481C, 0, 1);
            if (GetPauseStep_2f6660() == 0) {
                if ((PadIsTriggered_1839f0(D_004B2570, D_004847F4) != 0) ||
                    ((PadIsTriggered_1839f0(D_004B2570, D_004847F0) != 0) && (D_0048481C == 1))) {
                    normal_TransSaveYesNoCursorBob_5188c0(D_0048481C, 1, 0);
                    PlayMenuSeThunk_289ef0(6);
                    normal_TransSaveShowMsg_519ff0(-1);
                    UiEntryListSelectByTag_28ea90(D_004847D8, 4, 0);
                } else if (PadIsTriggered_1839f0(D_004B2570, D_004847F0) != 0) {
                    normal_TransSaveYesNoCursorBob_5188c0(D_0048481C, 1, 0);
                    PlayMenuSeThunk_289ef0(5);
                    normal_TransSaveProgressWindowShow_519e50(1, 1);
                    D_00484818 = D_00484818 + 1;
                }
            }
            break;
        case 2:
            UiFadeWidgetAlpha_290690(D_004847D4, 0x75A2, 0.0f, D_0047D34C, -1.0f);
            SaveMgrSetMode_37b9e0(4);
            normal_TransSaveShowMsg_519ff0(6);
            D_00484818 = D_00484818 + 1;
            break;
        case 3:
            if (((unsigned char)SaveModeChanged_37baa0()) != 0) {
                t16 = ((short)SaveGetResultStatus_37b970());
                if ((t16 == 6) || (t16 == 5) || (t16 == 8)) {
                    PlayMenuSeThunk_289ef0(0x24);
                    normal_TransSaveSetError_51a000(6);
                } else {
                    *D_00484744 += 1;
                    normal_TransSaveProgressWindowShow_519e50(1, 0);
                    PlayMenuSeThunk_289ef0(0x23);
                    normal_TransSaveShowMsg_519ff0(9);
                    normal_TransSaveSlotListRefreshMaybe_518a80(D_004847EC);
                    {
                        Rec2 *r = ((Rec2 *)UiEntryListFindByTag_28ea40(D_004847D8, 2));
                        if (r != NULL) {
                            SaveSetLastSlot_376210(r->f16, D_004847E8);
                        }
                    }
                    {
                        Ent *e = ((Ent *)GetGameData_1fede0());
                        if (e != NULL) {
                            EntB *b = (EntB *)e->fC;
                            EntC *a = (EntC *)e->f18;
                            PartySetAreaTimeStampMirrorMaybe_3c97a0(a, a->fF8, b->f8);
                        }
                    }
                    McPortTypesInvalidateMaybe_373100();
                    D_00484818 = D_00484818 + 1;
                }
            }
            break;
        case 4:
            if ((GetPauseStep_2f6660() == 0) &&
                (PadIsTriggered_1839f0(D_004B2570, D_004847F0 | D_004847F4) != 0)) {
                PlayMenuSeThunk_289ef0(5);
                normal_TransSaveShowMsg_519ff0(-1);
                if (normal_TransMenuIsQuickOpen_514a00() != 0) {
                    UiEntryListSelectByTag_28ea90(D_004847D8, 4, 0);
                } else {
                    normal_TransSavePortCursorBob_5187c0(0, 0, 0);
                    SaveMgrRelease_37bb70();
                    StateMachineSetState_28ede0(D_004847D0, 7, 0);
                }
            }
            break;
        }
    }
    return 1;
}
