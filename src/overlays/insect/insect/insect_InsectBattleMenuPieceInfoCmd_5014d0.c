#include "types.h"
/* insect 0x005014D0 -- 832 bytes, 208 instructions, 32 calls, 8 conditional
 * branches.  The insect_InsectBattleGetStep_50d6a0(o, 2) state-dispatch family; the direct
 * template is insect_InsectBattleMenuPieceCmd_501810.c (same five cases, same argument shapes).
 *
 * No jump table -- a compare CHAIN testing 0xB, 0x20, 0x1C, 0x1D, 1, so the
 * SOURCE order is the REVERSE: 1, 0x1D, 0x1C, 0x20, 0xB.  The block addresses
 * (501560, 501680, 5016EC, 501704, 5017BC) run forwards in that same order,
 * which is the cross-check.
 *
 * The NULL guard here has an EMPTY arm: `beql $16,$0` jumps straight into the
 * epilogue with `ld $31` in the annulled delay slot, so the source is
 * `if (p != 0) { switch ... }` and not 00501810's if/else pair.
 *
 * o->f502C and o->f4F90 stay ARRAY MEMBERS (retail rematerialises
 * `addiu $4,$17,0x502C` at every site); o->f4960 is used once, so it is not
 * hoisted into a local the way 00501810 needs.
 *
 * 0x3E000000 is 0.125f, not 0.25f.
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

typedef struct Card { u8 pad00[0x8]; s8 f08; volatile s8 f09; } Card;

typedef struct Ent { u8 pad00[0x5C]; s32 f5C; } Ent;

extern const u8 D_00523DB0[];

extern Ent  *insect_InsectBoardGetPiece_4ee9a0(void *a, s8 x, s8 y);
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
extern void  insect_InsectCursorSetPushPage_511cf0(void *a, s32 k, s32 v);
extern void *insect_InsectCursorSetFindPage_511e60(void *a, s32 k);
extern s32   insect_InsectPieceIsKing_514b00(Ent *p);

extern void func_28F510(void *h, s32 id, s32 a, s32 b);
extern void func_290010(void *h, s32 id, s32 a, s32 b);
extern void func_290690(void *h, s32 id, f32 a, f32 b, f32 c);
extern f32  func_290770(void *h, s32 id);

void insect_InsectBattleMenuPieceInfoCmd_5014d0(Ins *o)
{
    Card *c;
    Ent  *p;
    s32   n;
    s32   i;

    c = insect_InsectCursorSetFindPage_511e60(o->f4F90, 2);
    p = insect_InsectBoardGetPiece_4ee9a0(o->f4960, c->f08, c->f09);
    if (p != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(o, 2)) {
        case 1:
            insect_InsectCmdMenuClear_4efd40(o->f502C);
            insect_InsectCmdMenuAdd_4efc80(o->f502C, 6);
            insect_InsectCmdMenuAdd_4efc80(o->f502C, 3);
            n = insect_InsectCmdMenuCount_4efc10(o->f502C);
            insect_InsectCursorSetPushPage_511cf0(o->f4F90, 5, 0);
            insect_InsectCursorSetSetSize_511bd0(o->f4F90, 1, n);
            o->f4FBC = o->f4FBC & 0xFD;
            insect_InsectCmdMenuLayout_4fab80(o, 2, 1, p->f5C);
            insect_InsectBattleSetStep_50d7a0(o, 5, 0, -1);
            func_28F510(o->f878, 0x7564, p->f5C, 0);
            i = 0;
            while (i < insect_InsectCmdMenuCount_4efc10(o->f502C)) {
                insect_InsectCmdMenuEntryRefresh_4f0060(o, i, 0);
                i++;
            }
            func_290010(o->f878, 0x7564, 1, -1);
            func_290010(o->f878, 0x7589, insect_InsectPieceIsKing_514b00(p), -1);
            insect_InsectBattleSetStep_50d7a0(o, 0x1C, 2, -1);
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523DB0, 1);
            break;
        case 0x1D:
            func_290690(o->f878, 0x755F, 0.0f, 0.125f, -1.0f);
            func_290690(o->f87C, 0xC37E, 0.0f, 0.125f, -1.0f);
            insect_InsectBattleSetState_50d8c0(o, 0x10, 0, -1);
            insect_InsectBattleSetStep_50d7a0(o, 0xB, 2, -1);
            break;
        case 0x1C:
            insect_InsectBattleCursorUpdateDesc_4f4530(o, D_00523DB0, 0);
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
