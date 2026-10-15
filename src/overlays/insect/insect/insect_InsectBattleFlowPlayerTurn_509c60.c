/* BYTE-IDENTICAL -- insect session 29 (ix29).
 * Closed by the EXTERN-SIGNATURE screen (build/ix29/protoscan.py): the park
 * declared insect_InsectBattleGetState_50d6f0 with ONE parameter where 17 byte-identical
 * units declare TWO.  Retail materialises the second argument `5` into $a1
 * and REUSES it as the `case 5:` compare operand -- which is why the two bad
 * words were `addiu $a1,$zero,5` / `beql $v0,$a1`.  Discriminating: k=0/1/2/4
 * give 3/4/3/3 bad, only k=5 matches.
 */
#include "types.h"
/* insect 0x00509C60 -- 1248 bytes, 312 instructions, 50 calls.
 *
 * The overlay's biggest state step.  The outer dispatch is `beql` INTO every
 * arm, so it is a `switch` whose source case order is the compare chain
 * REVERSED: 1, 0x1C, 0xA, 5, 0x2F, 0xD, 0xB (0xA/0xD/0xB are empty and
 * degrade to plain `beq`).  The inner dispatch on `w->f8` is a real jump table
 * (jtbl_00524ED0, cases 0..7 with 4 empty); the link retargets it onto
 * retail's.
 */

typedef struct Rec {
    u8 pad0[8];
    s8 f8;                          /* +0x08 */
    s8 f9;                          /* +0x09 */
    s8 fA;                          /* +0x0A */
    s8 fB;                          /* +0x0B */
} Rec;

typedef struct Obj {
    u8  pad0000[0x4960];
    u8  f4960[0x4F90 - 0x4960];     /* +0x4960 */
    u8  f4F90[0x4FBC - 0x4F90];     /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5B30 - 0x4FBD];
    u8  f5B30[4];                   /* +0x5B30 */
} Obj;

extern void  insect_InsectCursorSetGetCell_511a40(void *g, s32 k, s32 *x, s32 *y);
extern s32   insect_InsectBattleGetStep_50d6a0(Obj *o, s32 k);
extern s32   insect_InsectBattleGetState_50d6f0(Obj *o, s32 k);
extern void  insect_InsectCursorSetPushPage_511cf0(void *g, s32 a, s32 b);
extern void  insect_InsectBattleSetStep_50d7a0(Obj *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Obj *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetFlag_50dad0(Obj *o, s32 a);
extern void  insect_InsectBattleClearFlag_50da90(Obj *o, s32 a);
extern void  insect_InsectBattlePlayerCursorPick_509b00(Obj *o);
extern Rec  *insect_InsectCursorSetFindPage_511e60(void *g, s32 k);
extern void  insect_InsectCursorSetPageSetCell_511c20(void *g, Rec *r, s32 x, s32 y);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *g, s32 k);
extern void  insect_InsectBattlePlaySe_4f45b0(Obj *o, s32 k);
extern Rec  *insect_InsectBoardGetPiece_4ee9a0(void *g, s16 x, s16 y);
extern Rec  *insect_InsectBattleGetSelectedCmd_50df20(Obj *o);
extern s32   insect_InsectBattleCanUseSpecial_4f0030(Obj *o, Rec *c);
extern void  insect_InsectBattleSaveState_50d650(Obj *o, s32 k);
extern void  insect_InsectBattleSaveStep_50d600(Obj *o, s32 k);
extern s32   insect_InsectPieceSpecialUsable_514860(Rec *c);
extern void  insect_InsectPieceReset_514740(void *p);
extern void  insect_InsectPieceCopy_515cd0(void *p, Rec *e);

void insect_InsectBattleFlowPlayerTurn_509c60(Obj *o)
{
    s32   sp6C;
    s32   sp68;
    void *grid;
    Rec  *c;
    s32   k;
    Rec  *w;
    Rec  *p;
    Rec  *q;
    s32   r;
    s32   v;
    Rec  *e;

    insect_InsectCursorSetGetCell_511a40(o->f4F90, 2, &sp6C, &sp68);
    grid = o->f4960;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        if (insect_InsectBattleGetState_50d6f0(o, 5) == 0) {
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 2, 0);
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x34);
        }
        break;
    case 0x1C:
        insect_InsectBattlePlayerCursorPick_509b00(o);
        break;
    case 0xA:
        break;
    case 5:
        insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 3), sp6C,
                            sp68);
        insect_InsectBattleClearFlag_50da90(o, 0x3D);
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
            insect_InsectBattlePlaySe_4f45b0(o, 6);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
            break;
        }
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) == 0) {
            break;
        }
        c = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)sp6C, (s16)sp68);
        k = 5;
        w = insect_InsectBattleGetSelectedCmd_50df20(o);
        r = 1;
        if (w->f8 == 2) {
            r = insect_InsectBattleCanUseSpecial_4f0030(o, c);
        }
        if (r != 0) {
            insect_InsectBattleSaveState_50d650(o, 0);
            insect_InsectBattleSaveStep_50d600(o, 0);
            insect_InsectBattleSaveState_50d650(o, 2);
            insect_InsectBattleSaveStep_50d600(o, 2);
        }
        v = w->f8;
        switch (v) {
        case 0:
            p = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
            q = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB);
            q->f8 = p->f8;
            q->f9 = p->f9;
            q->fA = p->fA;
            q->fB = p->fB;
            insect_InsectBattleSetState_50d8c0(o, 0x16, 0, -1);
            break;
        case 1:
            p = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
            q = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA);
            q->f8 = p->f8;
            q->f9 = p->f9;
            q->fA = p->fA;
            q->fB = p->fB;
            insect_InsectBattleSetState_50d8c0(o, 0x13, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            break;
        case 2:
            if (c != 0) {
                if (insect_InsectPieceSpecialUsable_514860(c) != 0) {
                    p = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
                    q = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB);
                    q->f8 = p->f8;
                    q->f9 = p->f9;
                    q->fA = p->fA;
                    q->fB = p->fB;
                    insect_InsectBattleSetState_50d8c0(o, 0x18, 0, -1);
                } else {
                    k = 0x2B;
                }
            }
            break;
        case 3:
            insect_InsectBattleSetFlag_50dad0(o, 0x2B);
            insect_InsectBattleSetState_50d8c0(o, 1, 4, -1);
            break;
        case 4:
            break;
        case 5:
            insect_InsectBattleSetState_50d8c0(o, 0x12, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            break;
        case 6:
            e = insect_InsectBoardGetPiece_4ee9a0(grid, (s16)sp6C, (s16)sp68);
            if (e != 0) {
                insect_InsectPieceReset_514740(o->f5B30);
                insect_InsectPieceCopy_515cd0(o->f5B30, e);
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
        insect_InsectBattlePlaySe_4f45b0(o, k);
        break;
    case 0x2F:
        if (insect_InsectBattleGetStep_50d6a0(o, 1) == 0xB) {
            if (insect_InsectBattleGetStep_50d6a0(o, 2) == 0xB) {
                insect_InsectBattleSetState_50d8c0(o, 0x1B, 0, -1);
                insect_InsectBattleSetFlag_50dad0(o, 0x1C);
                o->f4FBC = o->f4FBC & 0xFD;
            }
        }
        break;
    case 0xD:
        break;
    case 0xB:
        break;
    }
}
