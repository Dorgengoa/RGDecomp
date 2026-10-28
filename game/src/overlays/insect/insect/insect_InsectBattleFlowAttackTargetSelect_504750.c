/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowAttackTargetSelect_504750 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00504750 -- 1,412 bytes, 353 instructions, 59 calls, 25 conditional
 * branches, br/ins 0.071.  A nine-arm state dispatch of the
 * insect_InsectBattleGetStep_50d6a0(o, 0) family.  Picked by x_large.py (the LARGE-END
 * ranker): the best profile above 1,400 bytes -- family, no jalr, no float,
 * no jump table, no divide trap.
 *
 * The compare CHAIN runs 0xB, 0x51, 0x1E, 0x1D, 0xA, 0x49, 0x1C, 0x1B, 1 --
 * REVERSED -- so source case order is 1, 0x1B, 0x1C, 0x49, 0xA, 0x1D, 0x1E,
 * 0x51, 0xB, and the block addresses (0x50488C, 0x5048D4, 0x504964, 0x504AC4,
 * 0x504B60) agree with the five non-empty ones in that order.  0xA, 0x1E, 0x51
 * and 0xB are `case K: break;` -- all four get a plain `beq` + `nop` to the
 * shared exit rather than a `beql`, because the exit's first word (`ld $31`)
 * is already claimed by the ENTRY guard's branch-likely, which targets one
 * instruction PAST it (0x00504CB8).
 *
 * The 0xB that case 0x1B passes to insect_InsectCursorSetPushPage_511cf0 has no instruction of
 * its own: $5 still holds the `addiu $5,$0,0xB` the case-0xB COMPARE emitted
 * at 0x00504818, which is also why that one compare takes $5 and every other
 * one takes $3.
 *
 * Case 0x1B FALLS THROUGH into case 0x1C (no `b` at 0x00504960).
 *
 * o->f4960 is HOISTED into $18 for its four uses, so it is a named local;
 * o->f4F90 is REMATERIALISED at all sixteen of its sites (bare
 * `addiu $4, $19, 0x4F90`), so it stays an array member written inline --
 * insect-array-member-blocks-cse, both halves in one function.
 *
 * x6C/x68/x64/x60 are s32 frame slots declared in DESCENDING address order.
 * They are read `lh` at insect_InsectBoardGetPiece_4ee9a0's two coordinates and `lw` at
 * insect_InsectBoardIsTargetMarked_4ee8c0's, which is the callee's parameter width emitting the
 * narrowing -- keep the locals s32.
 *
 * insect_InsectBattleTestFlag_50da40(o, 0x37) has its guard written with the FALL-THROUGH arm
 * (the != 0 / insect_InsectBattlePopSavedState_50d590 block) first and the branch-likely target
 * second.
 */

typedef struct Card {
    u8 pad00[8];
    s8 f8;                      /* +0x08 */
    s8 f9;                      /* +0x09 */
    s8 fA;                      /* +0x0A */
    s8 fB;                      /* +0x0B */
} Card;

typedef struct Ins {
    u8    pad000[0x4960];
    u8    f4960[0x4F90 - 0x4960];   /* +0x4960 */
    u8    f4F90[0x2C];              /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x5B20 - 0x4FBD];
    void *f5B20;                    /* +0x5B20 */
    u8    pad5B24[0x5B2C - 0x5B24];
    void *f5B2C;                    /* +0x5B2C */
    u8    pad5B30[0x5EF1 - 0x5B30];
    u8    f5EF1;                    /* +0x5EF1 */
} Ins;

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

void insect_InsectBattleFlowAttackTargetSelect_504750(Ins *o)
{
    s32   x6C;
    s32   x68;
    s32   x64;
    s32   x60;
    s32   flag;
    void *t;
    void *e;
    Card *m;
    s32   code;
    s32   sel;
    s32   st;
    s32   v;
    Card *b;
    void *hit;
    void *h2;

    m = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 2));
    t = o->f4960;
    e = insect_InsectBoardGetPiece_4ee9a0(t, m->f8 + m->fA, m->f9 + m->fB);
    if (e == 0) {
        m = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA));
        e = insect_InsectBoardGetPiece_4ee9a0(t, m->f8 + m->fA, m->f9 + m->fB);
    }
    if (e != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
        case 1:
            o->f5B20 = e;
            insect_InsectBattleSetState_50d8c0(o, 0x15, 2, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
            v = 0x32;
            if (o->f5EF1 != 0) {
                v = 0x33;
            }
            insect_InsectBattleSetFlag_50dad0(o, v);
            break;
        case 0x1B:
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 0xB, 0);
            b = ((Card *)insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xB));
            b->f8 = m->f8;
            b->f9 = m->f9;
            b->fA = m->fA;
            b->fB = m->fB;
            o->f4FBC &= 0xFD;
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 0, -1);
            insect_InsectBoardMarkAdjacentTargets_4ecf80(t, e, -1, -1);
            insect_InsectBattleSetFlag_50dad0(o, 0x22);
            insect_InsectBattleClearFlag_50da90(o, 0x15);
            insect_InsectBattleSetFlag_50dad0(o, 0x28);
            /* fall through */
        case 0x1C:
            insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x6C, &x68);
            hit = insect_InsectBoardGetPiece_4ee9a0(t, x6C, x68);
            flag = (u8)!o->f5EF1 + 0x32;
            insect_InsectBattleClearFlag_50da90(o, flag);
            if (hit != 0) {
                if (insect_InsectPieceIsEnemyOf_5149b0(e, hit) == 0) {
                    hit = 0;
                }
                if (hit != 0) {
                    insect_InsectBattleSetFlag_50dad0(o, flag);
                }
            }
            o->f5B2C = hit;
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                code = 0x2B;
                if (insect_InsectBoardIsTargetMarked_4ee8c0(t, x6C, x68) != 0) {
                    h2 = insect_InsectBoardGetPiece_4ee9a0(t, x6C, x68);
                    if ((h2 != 0) && (insect_InsectPieceIsEnemyOf_5149b0(e, h2) != 0)) {
                        insect_InsectBattleSetStep_50d7a0(o, 0x47, 2, -1);
                        insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                        insect_InsectCursorSetPushPage_511cf0(o->f4F90, 7, 1);
                    }
                    code = 5;
                }
                insect_InsectBattlePlaySe_4f45b0(o, code);
            } else if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                insect_InsectBattleSetStep_50d7a0(o, 0x1D, 2, -1);
                o->f5B2C = 0;
                insect_InsectBattlePlaySe_4f45b0(o, 6);
            }
            break;
        case 0x49:
            insect_InsectCursorSetGetCurCell_511a90(o->f4F90, &x64, &x60);
            sel = -1;
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x80) != 0) {
                sel = x64;
            }
            if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, 0x20) != 0) {
                sel = 1;
            }
            if (sel != -1) {
                st = 0x4B;
                code = 5;
                if (sel != 0) {
                    st = 0x4A;
                    code = 6;
                }
                insect_InsectBattleSetStep_50d7a0(o, 0xA, 0, -1);
                insect_InsectBattleSetStep_50d7a0(o, st, 2, -1);
                insect_InsectBattlePlaySe_4f45b0(o, code);
            }
            break;
        case 0xA:
            break;
        case 0x1D:
            insect_InsectBattleClearFlag_50da90(o, 0x28);
            insect_InsectBattleClearFlag_50da90(o, 0x22);
            insect_InsectBattleSetFlag_50dad0(o, 0x15);
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
            insect_InsectCursorSetPopPage_511ca0(o->f4F90);
            o->f4FBC &= 0xFD;
            insect_InsectBattleClearFlag_50da90(o, 0x37);
            insect_InsectBattleClearFlag_50da90(o, 0x32);
            insect_InsectBattleClearFlag_50da90(o, 0x33);
            break;
        case 0x1E:
            break;
        case 0x51:
            break;
        case 0xB:
            break;
        }
    }
}
