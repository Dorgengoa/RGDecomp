/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowOpponentInfoView_507490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00507490 -- 844 bytes, 211 instructions.
 *
 * insect_FUN_005038B0's sibling: a six-arm `switch` on
 * insect_InsectBattleGetStep_50d6a0(o, 0) whose compares are all `beql` INTO their arms, so
 * the source case order is the chain (0xB, 0x2F, 0xD, 0x1C, 0xA, 1) REVERSED
 * and the block addresses agree -- 0x507510 (1) < 0x507538 (0xA) <
 * 0x507574 (0x1C) < 0x5076FC (0xD) < 0x507764 (0x2F).  Case 0xB is EMPTY and
 * its compare annuls the `ld $31`. */

typedef struct Obj {
    u8  pad0000[0x4940];
    u8  f4940[1];                   /* +0x4940 */
    u8  pad4941[0x4F90 - 0x4941];
    u8  f4F90[1];                   /* +0x4F90 */
    u8  pad4F91[0x4FBC - 0x4F91];
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5B30 - 0x4FBD];
    u8  f5B30[1];                   /* +0x5B30 */
    u8  pad5B31[0x5DA8 - 0x5B31];
    s32 f5DA8;                      /* +0x5DA8 */
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
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowOpponentInfoView_507490(Obj *o)
{
    void *e;
    s32 t;
    s32 m;
    s32 n;

    insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &m, &n);
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectBattleSetState_50d8c0(o, 0xA, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        break;
    case 0xA:
        if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0x1A) {
            insect_InsectBattleSetFlag_50dad0(o, 0x1D);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        }
        break;
    case 0x1C:
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0 ||
            insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
            insect_InsectBattleClearFlag_50da90(o, 0x1C);
            insect_InsectBattleClearFlag_50da90(o, 0x1D);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
            insect_InsectBattlePlaySe_4f45b0(o, 5);
        } else {
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x10) != 0) {
                    insect_InsectPieceReset_514740(o->f5B30);
                    e = o->f4940;
                    t = ((short)insect_InsectTeamSlotGetEnemyKeyMaybe_513e90(e));
                    insect_InsectPieceLoadFromSource_515da0(o->f5B30, o->f5DA8, 1, n, t,
                                        ((short)insect_InsectTeamSlotGetEnemyRowMaybe_513e80(e)));
                    insect_InsectBattleSetStep_50d7a0(o, 0x1E, 2, -1);
                    insect_InsectBattleSetState_50d8c0(o, 0xD, 1, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x2F, 0, -1);
                    insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
                    insect_InsectBattleClearFlag_50da90(o, 0x1D);
                    insect_InsectBattlePlaySe_4f45b0(o, 5);
                } else {
                    if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x40) != 0) {
                        if (insect_InsectBattleTestFlag_50da40(o, 2) == 0) {
                            insect_InsectBattleSetStep_50d7a0(o, 0xC, 2, -1);
                            insect_InsectBattleSetStep_50d7a0(o, 0xD, 0, -1);
                            o->f4FBC = o->f4FBC | 2;
                            insect_InsectBattlePlaySe_4f45b0(o, 5);
                        }
                    }
            }
        }
        break;
    case 0xD:
        if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0xD) {
            o->f4FBC = o->f4FBC & 0xFD;
            if (insect_InsectCursorSetGetEventsExcept_5119b0(o->f4F90, 0x4000) != 0) {
                insect_InsectBattlePlaySe_4f45b0(o, 6);
                insect_InsectBattleSetStep_50d7a0(o, 0xE, 2, -1);
                insect_InsectBattlePopStep_50d760(o, 0);
            }
        }
        break;
    case 0x2F:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) {
            if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB) {
                insect_InsectBattleSetState_50d8c0(o, 0x1B, 0, -1);
                insect_InsectBattleSetFlag_50dad0(o, 0x36);
                insect_InsectBattleSetFlag_50dad0(o, 0x1C);
                o->f4FBC = o->f4FBC & 0xFD;
            }
        }
        break;
    case 0xB:
        break;
    }
}
