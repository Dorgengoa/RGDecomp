#include "types.h"
/* insect 0x005040A0 -- 1,356 bytes, 339 instructions, 56 calls, 18 conditional
 * branches, br/ins 0.053.  An eight-arm state dispatch on
 * insect_InsectBattleGetStep_50d6a0(o, 0), the insect_InsectBattleMenuTeamSelect_5004f0 family; read that unit's
 * prototype block first.
 *
 * The compare chain runs 0xB, 0x22, 0x25, 0x24, 0x1C, 0x1B, 0xA, 1 --
 * REVERSED -- so the source case order is 1, 0xA, 0x1B, 0x1C, 0x24, 0x25,
 * 0x22, 0xB, and the block ADDRESSES of the five non-empty arms (0x41CC,
 * 0x4248, 0x4264, 0x4450, 0x4498) are that same order forwards.
 *
 * THREE EMPTY CASES ARE IN THE SOURCE -- 0xA, 0x25 and 0xB.  Each is a plain
 * `beq` to the shared exit with a `nop`, never a `beql`: there is no arm body
 * to merge into a delay slot, which is what distinguishes an empty case from a
 * missing one.
 *
 * 0x1B FALLS THROUGH into 0x1C.  The tell is that 0x1B's block never sets $5:
 * `addiu $5, $0, 0x1C` is the case-0x1C COMPARE's own constant, CSE'd into
 * 0x1B's insect_InsectBattleSetStep_50d7a0 call, and 0x1C's first statement
 * (`lw $17, 0x5B28($20)`) sits BOTH in the case-0x1C compare's branch-likely
 * delay slot and at the end of 0x1B's block.  Case 1's `addiu $6, $0, 0x1` is
 * the same trick against insect_InsectCursorSetPushPage_511cf0's third argument.
 *
 * insect_InsectBoardGetPiece_4ee9a0's two coordinates are s16: the `dsll32 16 / dsra32 16`
 * pair after each `addu` is the 16-bit narrowing of an s8 + s8 sum, and s32
 * parameters would drop both.
 */

typedef struct Slot {
    u8 pad00[0x8];
    s8 m8;                      /* +0x08 */
    s8 m9;                      /* +0x09 */
    s8 mA;                      /* +0x0A */
    s8 mB;                      /* +0x0B */
} Slot;

typedef struct Rec {
    u8 pad00[0x18];
    s8 m18;                     /* +0x18 */
    u8 pad19[0x38 - 0x19];
    s8 m38;                     /* +0x38 */
    s8 m39;                     /* +0x39 */
    u8 pad3A[0x4F - 0x3A];
    s8 m4F;                     /* +0x4F */
} Rec;

typedef struct Owner {
    u8 pad00[0x66];
    s8 m66;                     /* +0x66 */
} Owner;

typedef struct Ins {
    u8   pad0000[0x4960];
    u8   m4960[0x4F90 - 0x4960];/* +0x4960 */
    u8   m4F90[0x2C];           /* +0x4F90 */
    u8   m4FBC;                 /* +0x4FBC */
    u8   pad4FBD[0x50E8 - 0x4FBD];
    u8   m50E8[0x5B18 - 0x50E8];/* +0x50E8 */
    s32  m5B18;                 /* +0x5B18 */
    u8   pad5B1C[0x5B20 - 0x5B1C];
    s32  m5B20;                 /* +0x5B20 */
    s32  m5B24;                 /* +0x5B24 */
    Rec *m5B28;                 /* +0x5B28 */
    s32  m5B2C;                 /* +0x5B2C */
} Ins;

extern void  insect_InsectBoardCalcAttackRange_4ec720(void *e, Owner *a, Rec *q, s32 c, s32 d);
extern void  insect_InsectBoardFindPiece_4ee190(void *e, Rec *t, s32 *x, s32 *y);
extern Rec  *insect_InsectBoardGetPiece_4ee9a0(void *e, s16 x, s16 y);
extern void  insect_InsectBattlePlaySe_4f45b0(Ins *o, s32 k);
extern s32   insect_InsectBattlePopSavedStep_50d540(Ins *o, s32 k);
extern s32   insect_InsectBattlePopSavedState_50d590(Ins *o, s32 k);
extern s32   insect_InsectBattleGetSavedStep_50d5e0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetSavedState_50d5f0(Ins *o, s32 k);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattlePopState_50d880(Ins *o, s32 k);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleTestFlag_50da40(Ins *o, s32 k);
extern void  insect_InsectBattleClearFlag_50da90(Ins *o, s32 k);
extern void  insect_InsectBattleSetFlag_50dad0(Ins *o, s32 k);
extern Owner *insect_InsectBattleGetSpecialRec_50db30(Ins *o);
extern s32   insect_InsectCursorSetGetEvents_5119f0(void *a, s32 mask);
extern void  insect_InsectCursorSetGetCell_511a40(void *a, s32 k, s32 *x, s32 *y);
extern void  insect_InsectCursorSetSetSize_511bd0(void *a, s32 k, s32 v);
extern void  insect_InsectCursorSetPageSetCell_511c20(void *a, Slot *s, s32 x, s32 y);
extern void  insect_InsectCursorSetPopPage_511ca0(void *a);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern Slot *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);
extern s32   insect_InsectPieceTestStatus_513280(Rec *t, s32 k);
extern s32   insect_InsectAbilityTableGetMatchCount_51cee0(void *c);
extern s32  *insect_InsectAbilityTableCollect_51cef0(void *c, s8 a, s8 b, s8 c2, s32 d);

void insect_InsectBattleFlowSpecialSelect_5040a0(Ins *o)
{
    void *c;
    void *e;
    Rec *t;
    Rec *q;
    Slot *p;
    Slot *d;
    s32 *r;
    s32 n;
    s32 k;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;

    e = o->m4960;
    p = insect_InsectCursorSetFindPage_511e60(o->m4F90, 2);
    t = insect_InsectBoardGetPiece_4ee9a0(e, p->m8 + p->mA, p->m9 + p->mB);
    if (t == 0) {
        p = insect_InsectCursorSetFindPage_511e60(o->m4F90, 0xA);
        t = insect_InsectBoardGetPiece_4ee9a0(e, p->m8 + p->mA, p->m9 + p->mB);
    }
    if (t == 0) {
        return;
    }

    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        insect_InsectCursorSetPushPage_511cf0(o->m4F90, 0xC, 1);
        o->m5B28 = t;
        o->m5B20 = 0;
        o->m5B24 = 0;
        o->m5B2C = 0;
        insect_InsectBattleSetState_50d8c0(o, 0x18, 2, -1);
        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
        insect_InsectBoardFindPiece_4ee190(e, t, &sp7C, &sp78);
        insect_InsectCursorSetPageSetCell_511c20(o->m4F90, insect_InsectCursorSetFindPage_511e60(o->m4F90, 0xB),
                            sp7C, sp78);
        break;
    case 0xA:
        break;
    case 0x1B:
        o->m4FBC = o->m4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
        /* fall through */
    case 0x1C:
        q = o->m5B28;
        c = o->m50E8;
        r = insect_InsectAbilityTableCollect_51cef0(c, q->m38, q->m39, q->m18, 0);
        n = insect_InsectAbilityTableGetMatchCount_51cee0(c);
        insect_InsectCursorSetGetCell_511a40(o->m4F90, 0xC, &sp74, &sp70);
        insect_InsectCursorSetSetSize_511bd0(o->m4F90, 1, n);
        o->m5B18 = r[sp70];
        insect_InsectBoardCalcAttackRange_4ec720(e, insect_InsectBattleGetSpecialRec_50db30(o), q, -1, -1);
        insect_InsectBattleSetFlag_50dad0(o, 0x23);
        insect_InsectBattleClearFlag_50da90(o, 0x15);
        if (insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x80) != 0) {
            if (insect_InsectPieceTestStatus_513280(t, 0x18) != 0 ||
                insect_InsectPieceTestStatus_513280(t, 0x19) != 0 || t->m4F <= 0) {
                insect_InsectBattlePlaySe_4f45b0(o, 0x2B);
            } else {
                k = 2;
                if (insect_InsectBattleTestFlag_50da40(o, 0x37) != 0) {
                    k = 0xA;
                }
                p = insect_InsectCursorSetFindPage_511e60(o->m4F90, k);
                d = insect_InsectCursorSetFindPage_511e60(o->m4F90, 0xB);
                d->m8 = p->m8;
                d->m9 = p->m9;
                d->mA = p->mA;
                d->mB = p->mB;
                insect_InsectBattlePlaySe_4f45b0(o, 5);
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x24, 2, -1);
                o->m4FBC = o->m4FBC | 2;
            }
            return;
        } else {
            if (insect_InsectCursorSetGetEvents_5119f0(o->m4F90, 0x20) != 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, 0x22, 2, -1);
                o->m4FBC = o->m4FBC | 2;
                insect_InsectBattlePlaySe_4f45b0(o, 6);
            }
        }
        break;
    case 0x24:
        if (insect_InsectBattleGetSpecialRec_50db30(o)->m66 != 0) {
            insect_InsectBattleSetState_50d8c0(o, 0x19, 0, -1);
        } else {
            insect_InsectBattleSetState_50d8c0(o, 0x1A, 0, -1);
        }
        break;
    case 0x25:
        break;
    case 0x22:
        if (insect_InsectBattleTestFlag_50da40(o, 0x37) != 0) {
            insect_InsectBattleSetState_50d8c0(o, insect_InsectBattlePopSavedState_50d590(o, 0), 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattlePopSavedStep_50d540(o, 0), 0, -1);
            insect_InsectBattleSetState_50d8c0(o, insect_InsectBattlePopSavedState_50d590(o, 2), 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattlePopSavedStep_50d540(o, 2), 2, -1);
        } else {
            insect_InsectBattlePopState_50d880(o, 0);
            insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, insect_InsectBattleGetSavedState_50d5f0(o, 2), 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, insect_InsectBattleGetSavedStep_50d5e0(o, 2), 2, -1);
        }
        insect_InsectCursorSetPopPage_511ca0(o->m4F90);
        o->m4FBC = o->m4FBC & 0xFD;
        insect_InsectBattleClearFlag_50da90(o, 0x37);
        insect_InsectBattleClearFlag_50da90(o, 0x23);
        insect_InsectBattleSetFlag_50dad0(o, 0x15);
        break;
    case 0xB:
        break;
    }
}
