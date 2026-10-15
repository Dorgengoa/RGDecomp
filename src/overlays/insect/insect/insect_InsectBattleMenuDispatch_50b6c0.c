#include "types.h"
/* insect 0x0050B6C0 -- the per-state tick dispatcher: 520 bytes, 130
 * instructions, 29 calls and exactly ONE conditional branch.  Top of the
 * branch-density ranking (bytes / (1 + br)), which is why it was opened first.
 *
 * ★ THIS IS THE UNIT THAT PROVES scripts/x_jtbl.py.  mwcc compiles a dense
 * `switch` into a REAL jump table and emits it in the OBJECT's own `.rodata`
 * under an internal `@N` label; the overlay's data assembly already carries
 * that table at jtbl_00524F90, and x_olink's lcf collects `*(.rodata)` into
 * `.data`, so without the retarget the overlay would hold the table twice and
 * every byte after it would shift.  x_jtbl finds the object's table in RETAIL's
 * own .BIN (it must occur exactly once, at an address carrying a `jtbl_`
 * label), rewrites the `lui`/`addiu` pair to %hi/%lo of that address and empties
 * the section.  That search is a REAL check: the table's words are the case
 * blocks' own addresses, so it only matches when the case ORDER and the block
 * LAYOUT are already right -- the one defect a text byte-compare cannot see.
 *
 * Case order: the table covers 0..0x1E (`sltiu $1,$2,0x1F`) and indices 0, 1 and
 * 20 point at the shared exit, so those three are the `default`, i.e. absent.
 * The case blocks are laid out in ASCENDING case order, which is source order
 * for a real jump table -- the reversed-case-order rule is about a compare
 * CHAIN and does not apply here. */
typedef struct Ent { s32 f00; } Ent;

extern s32 insect_InsectBattleGetState_50d6f0(Ent *o, s32 k);
extern void insect_InsectBattleMenuPieceCmd_501810(Ent *o);
extern void insect_InsectBattleMenuPieceInfoCmd_5014d0(Ent *o);
extern void insect_InsectBattleMenuSystemCmd_5011c0(Ent *o);
extern void insect_InsectBattleMenuOpponentIntro_501c60(Ent *o);
extern void insect_InsectBattleMenuOpponentIntroClose_5010e0(Ent *o);
extern void insect_InsectBattleMenuTeamSelect_5004f0(Ent *o);
extern void insect_InsectBattleMenuTeamConfirm_5001e0(Ent *o);
extern void insect_InsectBattleMenuDetailInfo_500080(Ent *o);
extern void insect_InsectBattleMenuOpponentInfo_4ffa80(Ent *o);
extern void insect_InsectBattleMenuLayoutPlace_4ff520(Ent *o);
extern void insect_InsectBattleMenuPlacePieceList_4ff350(Ent *o);
extern void insect_InsectBattleMenuLayoutConfirm_4ff040(Ent *o);
extern void insect_InsectBattleMenuSelectKing_4fed30(Ent *o);
extern void insect_InsectBattleMenuKingConfirm_4fe6a0(Ent *o);
extern void insect_InsectBattleMenuMatchIntro_4fe160(Ent *o);
extern void insect_InsectBattleMenuEndTurn_4fda60(Ent *o);
extern void insect_InsectBattleMenuMoveSelect_4fd990(Ent *o);
extern void insect_InsectBattleMenuActionCmd_4fd470(Ent *o);
extern void insect_InsectBattleMenuAttackConfirm_4fcf60(Ent *o);
extern void insect_InsectBattleMenuGiveUpConfirm_4fcbf0(Ent *o);
extern void insect_InsectBattleMenuResultBanner_4fc780(Ent *o);
extern void insect_InsectBattleMenuSpecialList_4fc1f0(Ent *o);
extern void insect_InsectBattleMenuSpecialTargetSelectMaybe_4fc080(Ent *o);
extern void insect_InsectBattleMenuSpecialConfirm_4fbcc0(Ent *o);
extern void insect_InsectBattleMenuReport_4fba40(Ent *o);
extern void insect_InsectBattleMenuVictoryCondSelect_4fb7c0(Ent *o);
extern void insect_InsectBattleMenuTeamSelBanner_4fb510(Ent *o);
extern void insect_InsectBattleMenuFirstTurnSelect_4fb1a0(Ent *o);

void insect_InsectBattleMenuDispatch_50b6c0(Ent *o)
{
    switch (insect_InsectBattleGetState_50d6f0(o, 2)) {
    case 2:  insect_InsectBattleMenuPieceCmd_501810(o);  break;
    case 3:  insect_InsectBattleMenuPieceInfoCmd_5014d0(o);  break;
    case 4:  insect_InsectBattleMenuSystemCmd_5011c0(o);  break;
    case 5:  insect_InsectBattleMenuOpponentIntro_501c60(o);  break;
    case 6:  insect_InsectBattleMenuOpponentIntroClose_5010e0(o);  break;
    case 7:  insect_InsectBattleMenuTeamSelect_5004f0(o);  break;
    case 8:  insect_InsectBattleMenuTeamConfirm_5001e0(o);  break;
    case 9:  insect_InsectBattleMenuDetailInfo_500080(o);  break;
    case 10:  insect_InsectBattleMenuOpponentInfo_4ffa80(o);  break;
    case 11:  insect_InsectBattleMenuLayoutPlace_4ff520(o);  break;
    case 12:  insect_InsectBattleMenuPlacePieceList_4ff350(o);  break;
    case 13:  insect_InsectBattleMenuLayoutConfirm_4ff040(o);  break;
    case 14:  insect_InsectBattleMenuSelectKing_4fed30(o);  break;
    case 15:  insect_InsectBattleMenuKingConfirm_4fe6a0(o);  break;
    case 16:  insect_InsectBattleMenuMatchIntro_4fe160(o);  break;
    case 17:  insect_InsectBattleMenuEndTurn_4fda60(o);  break;
    case 18:  insect_InsectBattleMenuMoveSelect_4fd990(o);  break;
    case 19:  insect_InsectBattleMenuActionCmd_4fd470(o);  break;
    case 21:  insect_InsectBattleMenuAttackConfirm_4fcf60(o);  break;
    case 22:  insect_InsectBattleMenuGiveUpConfirm_4fcbf0(o);  break;
    case 23:  insect_InsectBattleMenuResultBanner_4fc780(o);  break;
    case 24:  insect_InsectBattleMenuSpecialList_4fc1f0(o);  break;
    case 25:  insect_InsectBattleMenuSpecialTargetSelectMaybe_4fc080(o);  break;
    case 26:  insect_InsectBattleMenuSpecialConfirm_4fbcc0(o);  break;
    case 27:  insect_InsectBattleMenuReport_4fba40(o);  break;
    case 28:  insect_InsectBattleMenuVictoryCondSelect_4fb7c0(o);  break;
    case 29:  insect_InsectBattleMenuTeamSelBanner_4fb510(o);  break;
    case 30:  insect_InsectBattleMenuFirstTurnSelect_4fb1a0(o);  break;
    }
}
