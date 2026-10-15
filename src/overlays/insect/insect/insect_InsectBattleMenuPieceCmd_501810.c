#include "types.h"
/* insect 0x00501810 -- 1,096 bytes, 274 instructions, 46 calls, 14 conditional
 * branches, br/ins 0.051.  The insect_InsectBattleGetStep_50d6a0(o, 2) state dispatch family
 * again; header is insect_InsectBattleMenuTeamSelect_5004f0.c.  No jump table -- a compare CHAIN of
 * five, testing 0xB, 0x20, 0x1C, 0x1D, 1, so source order is the REVERSE:
 * 1, 0x1D, 0x1C, 0x20, 0xB.  The block addresses (5018CC, 501AC0, 501B2C,
 * 501B44, 501BFC) run in that same order forwards, which is the cross-check.
 *
 * The NULL guard is laid out FIRST (bnel to the switch), so the source tests
 * `p == 0` and the dispatch is the else, not the other way round.
 *
 * o->f502C and o->f4F90 are ARRAY MEMBERS, not (u8 *)o + K: retail
 * rematerialises `addiu $4, $20, 0x502C` at all eleven sites, and the pointer
 * arithmetic spelling is a CSE candidate that mwcc parks in a callee-saved
 * register instead.  o->f4960 IS hoisted by retail, so that one is a local.
 * See insect-array-member-blocks-cse.
 *
 * The case-1 loop is entered by a branch to its TEST (b .L00501A38), i.e. an
 * unrotated `while` whose condition re-calls insect_InsectCmdMenuCount_4efc10 every
 * iteration -- a `do/while` puts the call at the bottom only and is one block
 * short.
 */

typedef struct Ins {
    u8    pad000[0x878];
    void *f878;                 /* +0x0878 */
    void *f87C;                 /* +0x087C */
    u8    pad880[0x4960 - 0x880];
    u8    f4960[0x4F90 - 0x4960];   /* +0x4960 */
    u8    f4F90[0x2C];              /* +0x4F90 */
    u8    f4FBC;                    /* +0x4FBC */
    u8    pad4FBD[0x502C - 0x4FBD];
    u8    f502C[4];                 /* +0x502C */
} Ins;

typedef struct Card { u8 pad00[0x8]; s8 f08; s8 f09; } Card;

typedef struct Ent { u8 pad00[0x5C]; s32 f5C; } Ent;

extern const u8 D_00523D80[];

extern Ent  *insect_InsectBoardGetPiece_4ee9a0(void *a, s8 x, s8 y);
extern s32   insect_InsectBoardHasAdjacentEnemy_4ef670(void *a, Ent *p);
extern s32   insect_InsectCmdMenuCount_4efc10(void *a);
extern void  insect_InsectCmdMenuAdd_4efc80(void *a, s32 k);
extern void  insect_InsectCmdMenuClear_4efd40(void *a);
extern void  insect_InsectCmdMenuEntryRefresh_4f0060(Ins *o, s32 i, Ent *p);
extern void  insect_InsectBattleCursorUpdateDesc_4f4530(Ins *o, const u8 *t, s32 k);
extern void  insect_InsectCmdMenuLayout_4fab80(Ins *o, s32 a, s32 b, s32 c);
extern s32   insect_InsectBattleGetStep_50d6a0(Ins *o, s32 k);
extern void  insect_InsectBattleSetStep_50d7a0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectBattleSetState_50d8c0(Ins *o, s32 a, s32 b, s32 c);
extern void  insect_InsectCursorSetSetSize_511bd0(void *a, s32 k, s32 v);
extern void  insect_InsectCursorSetPageSetCell_511c20(void *a, void *b, s8 x, s8 y);
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern void *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);
extern s32   insect_InsectPieceTestStatus_513280(Ent *p, s32 k);
extern s32   insect_InsectPieceCanAct_514920(Ent *p);
extern s32   insect_InsectPieceIsKing_514b00(Ent *p);

extern void func_28F510(void *h, s32 id, s32 a, s32 b);
extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);

void insect_InsectBattleMenuPieceCmd_501810(Ins *o)
{
    s8   a;
    s8   b;
    void *t;
    Ent  *p;
    Card *c;
    s32  n;
    s32  i;

    c = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
    a = c->f08;
    b = c->f09;
    t = o->f4960;
    p = insect_InsectBoardGetPiece_4ee9a0(t, a, b);
    if (p == 0) {
        insect_InsectBattleSetState_50d8c0(o, 0, 2, -1);
    } else {
        switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
        case 1:
            insect_InsectCursorSetPageSetCell_511c20(o->f4F90, insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA), a, b);
            insect_InsectCmdMenuClear_4efd40(o->f502C);
            if (insect_InsectPieceTestStatus_513280(p, 0x1C) == 0 && insect_InsectPieceCanAct_514920(p) != 0) {
                if (insect_InsectPieceTestStatus_513280(p, 0x26) == 0) {
                    insect_InsectCmdMenuAdd_4efc80(o->f502C, 1);
                }
                if (insect_InsectBoardHasAdjacentEnemy_4ef670(t, p) != 0) {
                    if (insect_InsectPieceTestStatus_513280(p, 0x27) == 0) {
                        insect_InsectCmdMenuAdd_4efc80(o->f502C, 0);
                    }
                }
                if (insect_InsectPieceTestStatus_513280(p, 0x28) == 0) {
                    insect_InsectCmdMenuAdd_4efc80(o->f502C, 2);
                }
            }
            insect_InsectCmdMenuAdd_4efc80(o->f502C, 6);
            insect_InsectCmdMenuAdd_4efc80(o->f502C, 3);
            insect_InsectCmdMenuAdd_4efc80(o->f502C, 5);
            n = insect_InsectCmdMenuCount_4efc10(o->f502C);
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 4, 0);
            insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, n);
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectCmdMenuLayout_4fab80(o, 3, 1, p->f5C);
            insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
            func_28F510(o->f878, 0x7564, p->f5C, 0);
            i = 0;
            while (i < insect_InsectCmdMenuCount_4efc10(o->f502C)) {
                insect_InsectCmdMenuEntryRefresh_4f0060(o, i, p);
                i++;
            }
            func_290010(o->f878, 0x7560, 1, -1);
            func_290010(o->f878, 0x7564, 1, -1);
            func_290010(o->f878, 0x7589, insect_InsectPieceIsKing_514b00(p), -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523D80, 1);
            break;
        case 0x1D:
            func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectBattleSetState_50d8c0(o, 0x10, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            break;
        case 0x1C:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523D80, 0);
            break;
        case 0x20:
            func_290690(o->f878, 0x7565, 0.0f, 0.125f, -1.0f);
            func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f878, 0x7530, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            if (func_290770(o->f878, 0x7530) <= 0.0f) {
                insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            }
            break;
        case 0xB:
            func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            break;
        }
    }
}
