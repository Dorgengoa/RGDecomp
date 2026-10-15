#include "types.h"
/* insect 0x00504CE0 -- 1,220 bytes, 305 instructions, 54 calls, 16 conditional
 * branches, br/ins 0.052.  A state dispatch of the insect_InsectBattleGetStep_50d6a0(o, 0)
 * family with a SECOND, compiled-switch dispatch nested inside it.
 *
 * OUTER: a compare CHAIN 0xB, 0xA, 0x2F, 5, 1 -- reversed -- so source case
 * order is 1, 5, 0x2F, 0xA, 0xB, and the block addresses (0x504D70, 0x504DB8,
 * 0x50512C) agree with the first three.  0xA and 0xB are the empty-case pair:
 * the LATER one in source (0xB) keeps its `beql` and targets the epilogue head
 * PLUS ONE (0x00505188, past the `ld $31` already run in the delay slot) while
 * the earlier (0xA) gets a plain `beq` + `nop` to 0x00505184.  Drop either and
 * the chain is two words short.
 *
 * INNER: a real 8-entry jump table (jtbl_00524E80) on m->f8, cases 0..7 laid
 * out in ASCENDING order -- source order for a table, so the reversed-chain
 * rule does not apply.  Entry 1 points at the shared join, which is
 * `case 1: break;` in the source; the `sltiu $1, $2, 0x8` range check sends
 * out-of-range to that same join, so there is no `default:`.
 *
 * o->f4F90 is REMATERIALISED at all nine of its sites (bare `addiu $4, $20,
 * 0x4F90`), so it is an array member; o->f4960 is HOISTED into $19 across the
 * whole body for its ONE use in case 6, so that one is a local assigned before
 * the guard -- insect-array-member-blocks-cse, both halves.
 *
 * Declaration order gives t=$19, h=$18, code=$17 (descending from the highest);
 * statement order gives h = o->f5B1C BEFORE t = o->f4960, which is the order
 * the two computations are emitted in with the `addiu $19` sunk into the
 * guard's delay slot.  insect-stmt-order-vs-decl-order: the two levers point
 * in opposite directions here.
 *
 * x6C/x68 are s32 frame slots declared in DESCENDING address order;
 * insect_InsectBoardGetPiece_4ee9a0's coordinates are s16, which is what makes the reload
 * `lh` rather than `lw`.
 */

typedef struct Card {
    u8 pad00[8];
    s8 f8;                      /* +0x08 */
    s8 f9;                      /* +0x09 */
    s8 fA;                      /* +0x0A */
    s8 fB;                      /* +0x0B */
} Card;

typedef struct Ins {
    u8  pad000[0x4960];
    u8  f4960[0x4F90 - 0x4960]; /* +0x4960 */
    u8  f4F90[0x2C];            /* +0x4F90 */
    u8  f4FBC;                  /* +0x4FBC */
    u8  pad4FBD[0x5B1C - 0x4FBD];
    s32 f5B1C;                  /* +0x5B1C */
    u8  pad5B20[0x5B30 - 0x5B20];
    u8  f5B30[0x5D18 - 0x5B30]; /* +0x5B30 */
} Ins;

extern s32   insect_InsectBoardGetPiece_4ee9a0(void *a, s16 x, s16 y);
extern s32   insect_InsectBattleCanUseSpecial_4f0030(Ins *o, s32 h);
extern void  insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern void  insect_InsectBattlePopSavedStep_50d540(Ins *o, s32 k);
extern void  insect_InsectBattlePopSavedState_50d590(Ins *o, s32 k);
extern void  insect_InsectBattleSaveStep_50d600(Ins *o, s32 k);
extern void  insect_InsectBattleSaveState_50d650(Ins *o, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern Card *insect_InsectBattleGetSelectedCmd_50df20(Ins *o);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern Card *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);
extern void  insect_InsectPieceSetStatus_5132d0(s32 h, s32 k);
extern void  insect_InsectPieceClearStatus_513340(s32 h, s32 k);
extern void  insect_InsectPieceReset_514740(void *a);
extern s32   insect_InsectPieceSpecialUsable_514860(s32 h);
extern void  insect_InsectPieceCopy_515cd0(void *a, s32 v);

void insect_InsectBattleFlowActionCmd_504ce0(Ins *o)
{
    s32 x6C;
    s32 x68;
    void *t;
    s32 h;
    s32 code;
    Card *m;
    Card *a;
    Card *b;
    s32 hit;
    s32 ok;

    insect_InsectCursorSetGetCell_511a40(o->f4F90, 2, &x6C, &x68);
    h = o->f5B1C;
    t = o->f4960;
    if (h != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
        case 1:
            insect_InsectBattleSetFlag_50dad0(o, 0x3D);
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0xA, 0);
            insect_InsectBattleSetState_50d8c0(o, 0x13, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            break;
        case 5:
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                insect_InsectBattlePlaySe_4f45b0(o, 6);
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                insect_InsectPieceClearStatus_513340(h, 0x26);
            } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                code = 5;
                m = insect_InsectBattleGetSelectedCmd_50df20(o);
                ok = 1;
                if (m->f8 == 2) {
                    ok = insect_InsectBattleCanUseSpecial_4f0030(o, h);
                }
                if (ok != 0) {
                    insect_InsectBattleSaveState_50d650(o, 0);
                    insect_InsectBattleSaveStep_50d600(o, 0);
                    insect_InsectBattleSaveState_50d650(o, 2);
                    insect_InsectBattleSaveStep_50d600(o, 2);
                }
                switch (m->f8) {
                case 0:
                    a = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA);
                    b = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB);
                    b->f8 = a->f8;
                    b->f9 = a->f9;
                    b->fA = a->fA;
                    b->fB = a->fB;
                    insect_InsectBattleSetFlag_50dad0(o, 0x37);
                    insect_InsectBattleSetState_50d8c0(o, 0x16, 0, -1);
                    break;
                case 1:
                    break;
                case 2:
                    if (h != 0) {
                        if (insect_InsectPieceSpecialUsable_514860(h) != 0) {
                            a = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA);
                            b = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB);
                            b->f8 = a->f8;
                            b->f9 = a->f9;
                            b->fA = a->fA;
                            b->fB = a->fB;
                            insect_InsectBattleSetFlag_50dad0(o, 0x37);
                            insect_InsectBattleSetState_50d8c0(o, 0x18, 0, -1);
                        } else {
                            code = 0x2B;
                        }
                    }
                    break;
                case 3:
                    insect_InsectBattlePopSavedState_50d590(o, 0);
                    insect_InsectBattlePopSavedStep_50d540(o, 0);
                    insect_InsectBattlePopSavedState_50d590(o, 2);
                    insect_InsectBattlePopSavedStep_50d540(o, 2);
                    insect_InsectBattleSetFlag_50dad0(o, 0x2B);
                    insect_InsectBattleSetState_50d8c0(o, 1, 4, -1);
                    break;
                case 4:
                    insect_InsectPieceSetStatus_5132d0(h, 0x1C);
                    insect_InsectBattleSetState_50d8c0(o, 0x15, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0x21, 2, -1);
                    break;
                case 5:
                    insect_InsectBattleSetFlag_50dad0(o, 0x37);
                    insect_InsectBattleSetState_50d8c0(o, 0x12, 0, -1);
                    insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
                    break;
                case 6:
                    insect_InsectBattleSetFlag_50dad0(o, 0x37);
                    insect_InsectCursorSetGetCell_511a40(o->f4F90, 0xA, &x6C, &x68);
                    hit = insect_InsectBoardGetPiece_4ee9a0(t, x6C, x68);
                    if (hit != 0) {
                        insect_InsectPieceReset_514740(o->f5B30);
                        insect_InsectPieceCopy_515cd0(o->f5B30, hit);
                        insect_InsectBattleSetStep_50d7a0(o, 0x20, 2, -1);
                        insect_InsectBattleSetState_50d8c0(o, 0xD, 1, -1);
                        insect_InsectBattleSetStep_50d7a0(o, 0x2F, 0, -1);
                        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0, 1);
                    }
                    break;
                case 7:
                    insect_InsectBattleSetState_50d8c0(o, 0x17, 0, -1);
                    break;
                }
                insect_InsectBattlePlaySe_4f45b0(o, code);
            }
            break;
        case 0x2F:
            if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB && insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB) {
                insect_InsectBattleSetState_50d8c0(o, 0x1B, 0, -1);
                insect_InsectBattleSetFlag_50dad0(o, 0x1C);
                o->f4FBC = o->f4FBC & 0xFD;
            }
            break;
        case 0xA:
            break;
        case 0xB:
            break;
        }
    }
}
