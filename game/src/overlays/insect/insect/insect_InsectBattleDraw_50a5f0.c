/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDraw_50a5f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050A5F0 -- 532 bytes, 133 instructions.
 *
 * A flat table of `if (flag) draw` calls -- pure transcription.
 */

typedef struct Obj {
    u8  pad0000[0xC0];
    s32 fC0;                        /* +0xC0 */
    u8  padC4[0x4F90 - 0xC4];
    u8  f4F90[4];                   /* +0x4F90 */
} Obj;

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

void insect_InsectBattleDraw_50a5f0(Obj *o)
{
    DrawListAddTexLoad_1418c0(o->fC0, 0x29E, 1.0f);
    if (insect_InsectBattleTestFlag_50da40(o, 0x1E) != 0) {
        insect_InsectBattleDrawPlacementCells_4f68a0(o, o->fC0, 0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x20) != 0) {
        insect_InsectBattleDrawMoveRangeCells_4f67b0(o, o->fC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x22) != 0) {
        insect_InsectBattleDrawTargetCells_4f6620(o, o->fC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x23) != 0) {
        insect_InsectBattleDrawAttackRangeCells_4f6490(o, o->fC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x22) != 0) {
        insect_InsectBattleDrawCursorCell_4f6a60(o, o->fC0, ((s32)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB)), 0.0f);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x23) != 0) {
        insect_InsectBattleDrawCursorCell_4f6a60(o, o->fC0, ((s32)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB)), 0.0f);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x15) != 0) {
        insect_InsectBattleDrawCursorCell_4f6a60(o, o->fC0, ((s32)insect_InsectCursorSetFindPage_511e60(o->f4F90, 2)), 0.0f);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x21) != 0) {
        insect_InsectBattleDrawCursorCell_4f6a60(o, o->fC0, ((s32)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA)), 0.0f);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x14) != 0) {
        insect_InsectBattleDrawPieceCells_4f6b80(o, o->fC0, 0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x24) != 0) {
        insect_InsectBattleDrawHoleCells_4f4d00(o, o->fC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x25) != 0) {
        insect_InsectBattleDrawWebCells_4f4bf0(o, o->fC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x1A) != 0) {
        insect_InsectBattleDrawDizzyStars_4f4fe0(o);
    }
    insect_InsectBattleDrawMarkerModels_4f4a30(o);
}
