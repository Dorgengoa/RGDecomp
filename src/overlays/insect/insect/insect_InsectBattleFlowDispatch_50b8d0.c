#include "types.h"
/* insect 0x0050B8D0 -- 2,088 bytes, 522 instructions, 109 calls, 36 conditional
 * branches, br/ins 0.069.  The overlay's MASTER per-frame dispatcher: a real
 * 40-entry jump table (jtbl_00525010, `sltiu $1, $2, 0x28`) on
 * insect_InsectBattleGetState_50d6f0(o, 0), where 37 of the 40 arms are a single call to the
 * state handler for that mode -- including six of this pass's and the previous
 * two passes' own units.
 *
 * The cases are laid out in ASCENDING order because it is a TABLE, so the
 * reversed-compare-chain rule does not apply.  There is no `default:`: an
 * out-of-range value skips the switch and lands on the common tail, which is
 * why the range check's `beql` targets .L0050BD0C (one past .L0050BD08, the
 * `daddu $4, $16, $0` every in-range arm's `b` falls into).
 *
 * The common tail is ordinary code AFTER the switch, not a case.  Only case 3
 * can skip it, and it does so with an early `return;` -- `bnel $4, $3,
 * .L0050C0D8` with `ld $31` in the delay slot, i.e. the epilogue head PLUS ONE.
 *
 * The tail's `for (i = 0; i < 2; i++)` is bottom-tested with the entry jumping
 * to the test (`b .L0050BF4C` with `i = 0` in its delay slot), and its
 * `continue` is the two-call guard whose `beql` carries the increment.  Note
 * the loop counter is REASSIGNED from o->f5EF1 inside the body -- that is in
 * the source, not a compiler artefact.
 *
 * Every guard is written with its FALL-THROUGH arm first.  The three that read
 * backwards from m2c's rendering are: case 0's 0050da40(o, 2) `!= 0` (the long
 * arm), the tail's `i != 0` (the 0x3E/0x3F arm), and the 0x30 / 0x2D chain,
 * where the two-call arm is the LAST else.
 */

typedef struct Ins {
    u8    pad000[0x870];
    void *f870;                     /* +0x0870 */
    u8    pad874[0x35F8 - 0x874];
    u8    f35F8[0x3F8C - 0x35F8];   /* +0x35F8 */
    u8    f3F8C[0x4F90 - 0x3F8C];   /* +0x3F8C */
    u8    f4F90[0x2C];              /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5DD0 - 0x4FBD];
    s16   f5DD0;                    /* +0x5DD0 */
    u8    pad5DD2[0x5EF1 - 0x5DD2];
    u8    f5EF1;                    /* +0x5EF1 */
    u8    pad5EF2[0x5EF8 - 0x5EF2];
    s32   f5EF8;                    /* +0x5EF8 */
} Ins;

typedef struct Slot { u8 pad00[6]; s16 f6; } Slot;
typedef struct Ctx  { u8 pad00[0x18]; Slot *f18; } Ctx;

extern void  func_1D0E30(void *h, s32 id, s32 a, s32 b);
extern void *func_1F5BE0(void);
extern Ctx  *func_1FEDE0(void);
extern void  func_207880(s32 a, s32 b);
extern void  func_285EA0(s32 a, s32 b, s16 c, s32 d);
extern void  insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern s32   insect_InsectBattleAllActed_4f4600(Ins *o);
extern s32   insect_InsectBattleIsSideDefeated_4f4670(Ins *o, s32 k);
extern void  insect_InsectBattleFlowSelectFirstTurn_501ff0(Ins *o);
extern void  insect_InsectBattleFlowConfirmPrompt_502180(Ins *o);
extern void  insect_InsectBattleFlowTextEntryMaybe_5024c0(Ins *o);
extern void  insect_InsectBattleFlowTeamSelBanner_5028f0(Ins *o);
extern void  insect_InsectBattleFlowSelectVictoryCond_502a30(Ins *o);
extern void  insect_InsectBattleFlowPlaceTeam_502c20(Ins *o);
extern void  insect_InsectBattleFlowExpReward_502f00(Ins *o);
extern void  insect_InsectBattleFlowVictoryPose_5036b0(Ins *o);
extern void  insect_InsectBattleFlowSpecialConfirm_5038b0(Ins *o);
extern void  insect_InsectBattleFlowSpecialTargetSelect_503b50(Ins *o);
extern void  insect_InsectBattleFlowSpecialSelect_5040a0(Ins *o);
extern void  insect_InsectBattleFlowGiveUpConfirm_5045f0(Ins *o);
extern void  insect_InsectBattleFlowAttackTargetSelect_504750(Ins *o);
extern void  insect_InsectBattleFlowActionCmd_504ce0(Ins *o);
extern void  insect_InsectBattleFlowMoveSelect_5051b0(Ins *o);
extern void  insect_InsectBattleFlowMatchStart_505530(Ins *o);
extern void  insect_InsectBattleFlowManualControlConfirm_505b60(Ins *o);
extern void  insect_InsectBattleFlowSelectKing_505ee0(Ins *o);
extern void  insect_InsectBattleFlowKingPromptMaybe_506480(Ins *o);
extern void  insect_InsectBattleFlowLayoutConfirm_506660(Ins *o);
extern void  insect_InsectBattleFlowPlacePiece_5067c0(Ins *o);
extern void  insect_InsectBattleFlowLayout_506b20(Ins *o);
extern void  insect_InsectBattleFlowOpponentInfoView_507490(Ins *o);
extern void  insect_InsectBattleFlowDetailInfoView_5077e0(Ins *o);
extern void  insect_InsectBattleFlowTeamConfirm_507970(Ins *o);
extern void  insect_InsectBattleFlowTeamSelectInput_507c80(Ins *o);
extern void  insect_InsectBattleFlowAutoSelectTeam_508380(Ins *o);
extern void  insect_InsectBattleFlowTeamSelectOpen_5084f0(Ins *o);
extern void  insect_InsectBattleFlowStageCaption_508670(Ins *o);
extern void  insect_InsectBattleFlowBattleBegin_5088c0(Ins *o);
extern void  insect_InsectBattleFlowTurnResume_508a20(Ins *o);
extern void  insect_InsectBattleFlowTurnStart_508b30(Ins *o);
extern void  insect_InsectBattleFlowTurnEnd_509150(Ins *o);
extern void  insect_InsectBattleFlowCpuTurn_5093e0(Ins *o);
extern void  insect_InsectBattleFlowPlayerTurn_509c60(Ins *o);
extern void  insect_InsectBattleFlowLoad_50a140(Ins *o);
extern u32   insect_InsectBattleGetState_50d6f0(Ins *o, s32 k);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern s32   insect_InsectPieceTestStatus_513280(void *e, s32 k);
extern s32   insect_InsectTeamFindKing_513840(void *h);
extern void *insect_InsectTeamGetPiece_5138d0(void *h, s32 i);
extern s32   insect_InsectPieceIsInPlay_5149e0(void *e);

void insect_InsectBattleFlowDispatch_50b8d0(Ins *o)
{
    s32   i;
    s32   m;
    s32   n;
    void *ea;
    void *h;
    void *eb;
    s32   w;
    void *g;

    g = func_1F5BE0();
    o->f870 = g;
    if (g == 0) {
        return;
    }
    switch (insect_InsectBattleGetState_50d6f0(o, 0)) {
    case 0:
        if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
            insect_InsectBattleSetFlag_50dad0(o, 5);
            insect_InsectBattleSetFlag_50dad0(o, 7);
            insect_InsectBattleSetState_50d8c0(o, 2, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
            func_1D0E30(o->f870, 0x884, 0, 0);
        } else {
            insect_InsectBattleSetFlag_50dad0(o, 5);
            insect_InsectBattleSetState_50d8c0(o, 2, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 0, 1, -1);
        }
        break;
    case 1:
        insect_InsectBattleFlowLoad_50a140(o);
        break;
    case 2:
        if (insect_InsectBattleTestFlag_50da40(o, 6) != 0) {
            if (insect_InsectBattleTestFlag_50da40(o, 3) == 0) {
                w = 0x1F4;
                if (insect_InsectBattleTestFlag_50da40(o, 2) != 0) {
                    w = 0x1F6;
                }
                func_285EA0(-1, w, func_1FEDE0()->f18->f6, 0);
            }
            insect_InsectBattleSetState_50d8c0(o, 3, 0, -1);
        }
        break;
    case 3:
        if ((insect_InsectBattleTestFlag_50da40(o, 2) != 0) && (o->f5DD0 != -1)) {
            return;
        }
        insect_InsectBattleSetState_50d8c0(o, 4, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, 5, 2, -1);
        func_207880(0x4F, 1);
        break;
    case 4:
        insect_InsectBattleFlowBattleBegin_5088c0(o);
        break;
    case 5:
        insect_InsectBattleFlowStageCaption_508670(o);
        break;
    case 6:
        insect_InsectBattleFlowTeamSelectOpen_5084f0(o);
        break;
    case 7:
        insect_InsectBattleFlowTeamSelectInput_507c80(o);
        break;
    case 8:
        insect_InsectBattleFlowTeamConfirm_507970(o);
        break;
    case 9:
        insect_InsectBattleFlowLayout_506b20(o);
        break;
    case 10:
        insect_InsectBattleFlowPlacePiece_5067c0(o);
        break;
    case 11:
        insect_InsectBattleFlowLayoutConfirm_506660(o);
        break;
    case 12:
        insect_InsectBattleFlowPlaceTeam_502c20(o);
        break;
    case 13:
        insect_InsectBattleFlowKingPromptMaybe_506480(o);
        break;
    case 14:
        insect_InsectBattleFlowSelectKing_505ee0(o);
        break;
    case 15:
        insect_InsectBattleFlowMatchStart_505530(o);
        break;
    case 16:
        insect_InsectBattleFlowPlayerTurn_509c60(o);
        break;
    case 17:
        insect_InsectBattleFlowCpuTurn_5093e0(o);
        break;
    case 18:
        insect_InsectBattleFlowTurnEnd_509150(o);
        break;
    case 19:
        insect_InsectBattleFlowMoveSelect_5051b0(o);
        break;
    case 20:
        insect_InsectBattleFlowActionCmd_504ce0(o);
        break;
    case 21:
        insect_InsectBattleFlowTurnResume_508a20(o);
        break;
    case 22:
        insect_InsectBattleFlowAttackTargetSelect_504750(o);
        break;
    case 23:
        insect_InsectBattleFlowGiveUpConfirm_5045f0(o);
        break;
    case 24:
        insect_InsectBattleFlowSpecialSelect_5040a0(o);
        break;
    case 25:
        insect_InsectBattleFlowSpecialTargetSelect_503b50(o);
        break;
    case 26:
        insect_InsectBattleFlowSpecialConfirm_5038b0(o);
        break;
    case 27:
        insect_InsectBattleFlowDetailInfoView_5077e0(o);
        break;
    case 28:
        insect_InsectBattleFlowOpponentInfoView_507490(o);
        break;
    case 29:
        insect_InsectBattleFlowTurnStart_508b30(o);
        break;
    case 30:
        insect_InsectBattleClearFlag_50da90(o, 0xB);
        break;
    case 31:
        insect_InsectBattleFlowVictoryPose_5036b0(o);
        break;
    case 32:
        insect_InsectBattleFlowExpReward_502f00(o);
        break;
    case 33:
        insect_InsectBattleFlowSelectVictoryCond_502a30(o);
        break;
    case 34:
        insect_InsectBattleFlowTeamSelBanner_5028f0(o);
        break;
    case 35:
        insect_InsectBattleFlowTextEntryMaybe_5024c0(o);
        break;
    case 36:
        insect_InsectBattleFlowManualControlConfirm_505b60(o);
        break;
    case 37:
        insect_InsectBattleFlowConfirmPrompt_502180(o);
        break;
    case 38:
        insect_InsectBattleFlowAutoSelectTeam_508380(o);
        break;
    case 39:
        insect_InsectBattleFlowSelectFirstTurn_501ff0(o);
        break;
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0xC) != 0) {
        for (i = 0; i < 2; i++) {
            if ((insect_InsectBattleIsSideDefeated_4f4670(o, i) == 0) &&
                (insect_InsectBattleTestFlag_50da40(o, 0x40) == 0)) {
                continue;
            }
            if (insect_InsectBattleTestFlag_50da40(o, 0x40) != 0) {
                i = o->f5EF1;
            }
            m = 0x1F;
            n = 0xA;
            if (insect_InsectBattleTestFlag_50da40(o, 0x38) != 0) {
                h = o->f35F8;
                ea = insect_InsectTeamGetPiece_5138d0(h, insect_InsectTeamFindKing_513840(h));
                h = o->f3F8C;
                eb = insect_InsectTeamGetPiece_5138d0(h, insect_InsectTeamFindKing_513840(h));
                if ((insect_InsectPieceIsInPlay_5149e0(ea) == 0) &&
                    (insect_InsectPieceIsInPlay_5149e0(eb) == 0)) {
                    i = 0;
                    if (o->f5EF1 == 0) {
                        if (insect_InsectPieceTestStatus_513280(ea, 0x24) == 0) {
                            i = 1;
                        }
                    } else if (insect_InsectPieceTestStatus_513280(eb, 0x24) != 0) {
                        i = 1;
                    }
                }
            } else if (insect_InsectBattleTestFlag_50da40(o, 0x48) != 0) {
                if (insect_InsectBattleIsSideDefeated_4f4670(o, 0) != 0) {
                    i = 0;
                } else {
                    i = 1;
                }
            } else if (insect_InsectBattleTestFlag_50da40(o, 0x4A) != 0) {
                i = 1;
            } else if (insect_InsectBattleTestFlag_50da40(o, 0x49) != 0) {
                if (insect_InsectBattleIsSideDefeated_4f4670(o, 1) != 0) {
                    i = 1;
                } else {
                    i = 0;
                }
            } else if (insect_InsectBattleTestFlag_50da40(o, 0x4B) != 0) {
                i = 0;
            }
            if (i != 0) {
                insect_InsectBattleSetFlag_50dad0(o, 0x3E);
                insect_InsectBattleSetFlag_50dad0(o, 0x3F);
            } else {
                m = 0x1E;
                n = 0xD;
                insect_InsectBattleSetState_50d8c0(o, 0x17, 2, -1);
            }
            o->f5EF8 = n;
            insect_InsectBattleSetState_50d8c0(o, m, 0, -1);
            insect_InsectBattleClearFlag_50da90(o, 0xB);
            insect_InsectBattleClearFlag_50da90(o, 0xC);
            insect_InsectBattleClearFlag_50da90(o, 0x26);
            insect_InsectBattleClearFlag_50da90(o, 0x27);
            insect_InsectBattleClearFlag_50da90(o, 0x28);
            insect_InsectBattleClearFlag_50da90(o, 0x34);
            o->f4FBC |= 0x40;
            return;
        }
        if (insect_InsectBattleGetState_50d6f0(o, 5) == 0) {
            insect_InsectBattleSetFlag_50dad0(o, 0xB);
        }
    }
    if ((insect_InsectBattleTestFlag_50da40(o, 0xB) != 0) &&
        (insect_InsectBattleGetState_50d6f0(o, 5) == 0) &&
        (insect_InsectBattleAllActed_4f4600(o) != 0) &&
        (insect_InsectBattleGetState_50d6f0(o, 0) != 0x12)) {
        insect_InsectBattleSetState_50d8c0(o, 0x12, 0, -1);
        insect_InsectBattleClearFlag_50da90(o, 0x27);
        o->f4FBC |= 2;
        o->f4FBC |= 0x40;
        insect_InsectBattleClearFlag_50da90(o, 0x48);
        insect_InsectBattleClearFlag_50da90(o, 0x4A);
        insect_InsectBattleClearFlag_50da90(o, 0x49);
        insect_InsectBattleClearFlag_50da90(o, 0x4B);
    }
    if ((insect_InsectBattleTestFlag_50da40(o, 0xD) != 0) &&
        (insect_InsectBattleTestFlag_50da40(o, 0x41) == 0) &&
        (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x40) != 0)) {
        if (insect_InsectBattleTestFlag_50da40(o, 0x30) != 0) {
            insect_InsectBattleClearFlag_50da90(o, 0x30);
        } else if (insect_InsectBattleTestFlag_50da40(o, 0x2D) != 0) {
            insect_InsectBattleClearFlag_50da90(o, 0x2D);
        } else {
            insect_InsectBattleSetFlag_50dad0(o, 0x2D);
            insect_InsectBattleSetFlag_50dad0(o, 0x30);
        }
        insect_InsectBattlePlaySe_4f45b0(o, 0xB);
    }
}
