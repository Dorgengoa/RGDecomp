#include "types.h"
/* insect 0x005051B0 -- 884 bytes, 221 instructions, 39 calls, 11 conditional
 * branches, br/ins 0.050.  insect_InsectBattleGetStep_50d6a0(o, 0) state dispatch family;
 * header is insect_InsectBattleMenuTeamSelect_5004f0.c.  Compare chain 0x2B, 0x1D, 0x1C, 0xA, 1,
 * so source order is 1, 0xA, 0x1C, 0x1D, 0x2B -- and the block addresses
 * 505218, (none), 5052C0, 50546C, 5054D0 confirm it.
 *
 * `case 0xA: break;` IS in the source and sits between case 1 and case 0x1C.
 * Its beql targets .L00505510, ONE INSTRUCTION PAST the epilogue head that the
 * default's `b` targets, because the branch-likely already ran `ld $31` in its
 * delay slot -- read the two exit addresses as different or the empty case is
 * invisible.
 *
 * Case 1's insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0xA, 1) emits ONLY the jal: both
 * 0xA and 1 are the constants the case-0xA and case-1 COMPARES built, CSE'd
 * into the arm.
 *
 * x40/x44 are read `lw` in case 0x1C and `lh` in case 1 -- the slots are s32
 * and the halfword comes from insect_InsectBoardCalcMoveRangeAt_4ed4a0's s16 parameters.
 */

typedef struct Ins {
    u8  pad000[0x4960];
    u8  f4960[0x4F90 - 0x4960];     /* +0x4960 */
    u8  f4F90[0x2C];                /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5B1C - 0x4FBD];
    s32 f5B1C;                      /* +0x5B1C */
} Ins;

typedef struct Card { u8 pad00[0x8]; s8 f8, f9, fA, fB; } Card;

extern void  insect_InsectBoardCalcMoveRangeAt_4ed4a0(void *a, s16 x, s16 y);
extern s32   insect_InsectBoardMovePiece_4ed8f0(void *a, s32 a1, s32 a2, s32 a3, s32 a4);
extern void  insect_InsectBoardBackup_4eda20(void *a);
extern s32   insect_InsectBoardIsMovable_4ee930(void *a, s32 x, s32 y);
extern void  insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetSavedStep_50d5e0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetSavedState_50d5f0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectPieceSetStatus_5132d0(s32 h, s32 k);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern void  insect_InsectCursorSetGetCurCell_511a90(void *a, s32 *x, s32 *y);
extern void  insect_InsectCursorSetPageSetCell_511c20(void *a, void *b, s32 x, s32 y);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern Card *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);

void insect_InsectBattleFlowMoveSelect_5051b0(Ins *o)
{
    s32 x4C;
    s32 x48;
    s32 x44;
    s32 x40;
    void *t;
    Card *c;
    Card *d;

    t = o->f4960;

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0xA, 1);
        o->f4FBC = o->f4FBC & 0xFD;
        insect_InsectBoardBackup_4eda20(t);
        c = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
        d = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA);
        d->f8 = c->f8;
        d->f9 = c->f9;
        d->fA = c->fA;
        d->fB = c->fB;
        insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x40, &x44);
        insect_InsectBoardCalcMoveRangeAt_4ed4a0(t, x40, x44);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        insect_InsectBattleSetState_50d8c0(o, 0x12, 2, -1);
        break;
    case 0xA:
        break;
    case 0x1C:
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 2, &x48, &x4C);
        insect_InsectCursorSetGetCell_511a40(o->f4F90, 0xA, &x40, &x44);
        insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 3), x40, x44);
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
            if (x48 == x40 && x4C == x44) {
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                insect_InsectBattlePlaySe_4f45b0(o, 6);
            } else if (insect_InsectBoardIsMovable_4ee930(t, x40, x44) != 0) {
                o->f5B1C = insect_InsectBoardMovePiece_4ed8f0(t, x48, x4C, x40, x44);
                insect_InsectBattleSetStep_50d7a0(o, 0x2B, 0, -1);
                insect_InsectBattleSetState_50d8c0(o, 1, 3, -1);
                insect_InsectBattleClearFlag_50da90(o, 0x20);
                insect_InsectBattleClearFlag_50da90(o, 0x21);
                insect_InsectPieceSetStatus_5132d0(o->f5B1C, 0x26);
                o->f4FBC = o->f4FBC | 2;
                insect_InsectBattlePlaySe_4f45b0(o, 5);
            } else {
                insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
            }
            return;
        } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
            insect_InsectBattlePlaySe_4f45b0(o, 6);
        }
        break;
    case 0x1D:
        insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 0), 0, -1);
        insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetSavedStep_50d5e0(o, 0), 0, -1);
        insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 2), 2, -1);
        break;
    case 0x2B:
        if (insect_InsectBattleGetStep_50d6a0(o, 3) == 0xB) {
            insect_InsectBattleSetState_50d8c0(o, 0, 3, -1);
            insect_InsectBattleSetState_50d8c0(o, 0x14, 0, -1);
        }
        break;
    }
}
