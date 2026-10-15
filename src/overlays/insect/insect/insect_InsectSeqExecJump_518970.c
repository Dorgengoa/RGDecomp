#include "types.h"
/* insect 0x00518970 -- 844 bytes, 211 instructions.
 *
 * insect_InsectSeqExecReclimed_518610's five-arm twin: `beql` INTO every block, so a `switch`
 * written 0, 1, 2, 3, 4 -- the compare chain (4, 3, 2, 1, 0) REVERSED, with
 * the block addresses 0x518A54 / 0x518A80 / 0x518AC8 / 0x518B40 / 0x518B74
 * agreeing.  Case 4 is the only arm that returns 1. */

typedef struct Ctx {
    u8  pad0000[0x4960];
    u8  f4960[4];                   /* +0x4960 */
    u8  pad4964[0x506C - 0x4964];
    u8  f506C[4];                   /* +0x506C */
    u8  pad5070[0x5080 - 0x5070];
    u8  f5080[4];                   /* +0x5080 */
    u8  pad5084[0x51C4 - 0x5084];
    u8  f51C4[4];                   /* +0x51C4 */
    u8  pad51C8[0x5F82 - 0x51C8];
    u8  f5F82[4];                   /* +0x5F82 */
} Ctx;

typedef struct Obj {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
} Obj;

typedef struct Ent {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x5C - 0x19];
    s32 f5C;                        /* +0x5C */
} Ent;

extern void func_1343B8(void *a, s32 b, s32 c, s32 d);
extern Ctx *func_31A8D0(void);
extern void insect_InsectBoardCellToWorld_4eda70(void *g, f32 *px, f32 *py, f32 *pz, s32 k,
                                f32 x, f32 y);
extern void insect_InsectBoardFindPiece_4ee190(void *g, Ent *e, s32 *px, s32 *py);
extern Ent *insect_InsectBoardGetPiece_4ee9a0(void *g, s16 x, s16 y);
extern void insect_InsectBoardTakeAt_4ef770(void *g, s16 x, s16 y);
extern void insect_InsectBoardPlacePiece_4ef830(void *g, Ent *e, s16 x, s16 y);
extern s32  insect_InsectBattleGetSpecialRec_50db30(Ctx *c);
extern Ent *insect_InsectBattleGetActorSlot_50db40(Ctx *c, s32 k);
extern void insect_InsectBattleDamagePopupSpawn_50f730(Ent *e, s32 t, u32 col);
extern void insect_InsectPlaySe_510870(s32 k);
extern s32  insect_InsectMsgGet_512b70(void *q, s32 k);
extern s32  insect_InsectPieceIsMotionDone_514280(Ent *e);
extern f32  insect_InsectPieceGetMotionPhase_5142d0(Ent *e);
extern void insect_InsectPieceMotionQueueClear_514320(Ent *e);
extern void insect_InsectPieceMotionQueuePush_514510(Ent *e, const void *d, s32 k, f32 x, f32 y);
extern s32  insect_InsectPieceIsEnemyOf_5149b0(Ent *e, Ent *t);
extern s32  insect_InsectPieceIsTurnDone_5149f0(Ent *e);
extern s32  insect_InsectPieceIsSick_514c50(Ent *e);
extern void insect_InsectPieceTryInflictSick_514ca0(Ent *e, s8 k);
extern void insect_InsectPieceFaceCell_515590(Ent *e, f32 x, f32 y, f32 t);
extern void insect_InsectPieceSetYawTarget_5156d0(Ent *e, f32 a, f32 b);
extern void insect_InsectPieceMoveTo_5157d0(Ent *e, s32 k, f32 x, f32 y, f32 z, f32 t);
extern void insect_InsectSeqGetTargetCell_51b710(s32 *px, s32 *py);
extern void insect_InsectBattleLogPush_51c2f0(void *r, void *k, s32 a, s32 b, s32 d);
extern void insect_InsectAiGetAction_522300(void *p);

extern const u8 D_00525340[];

s32 insect_InsectSeqExecJump_518970(Obj *o)
{
    Ent *e;
    s32 n;
    Ent *t;
    Ctx *c;
    s32 j;
    void *q;
    void *r;
    void *g;
    void *k;
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    f32 sx;
    f32 sy;
    f32 sz;

    c = func_31A8D0();
    if (o == 0 || c == 0) {
        return 1;
    }
    q = c->f506C;
    r = c->f5080;
    g = c->f4960;
    e = insect_InsectBattleGetActorSlot_50db40(c, 0);
    insect_InsectAiGetAction_522300(c->f51C4);
    n = insect_InsectBattleGetSpecialRec_50db30(c);
    if (e == 0) {
        return 1;
    }
    insect_InsectBoardFindPiece_4ee190(g, e, &ax, &ay);
    insect_InsectSeqGetTargetCell_51b710(&bx, &by);
    switch (o->f4) {
    case 0:
        insect_InsectPieceFaceCell_515590(e, (f32)bx, (f32)by, 4.0f);
        o->f4 = o->f4 + 1;
        break;
    case 1:
        if (insect_InsectPieceIsTurnDone_5149f0(e) != 0) {
            insect_InsectPieceMotionQueueClear_514320(e);
            insect_InsectPieceMotionQueuePush_514510(e, D_00525340, 6, 0.0f, 1.0f);
            o->f4 = o->f4 + 1;
        }
        break;
    case 2:
        if (insect_InsectPieceGetMotionPhase_5142d0(e) >= 0.25f) {
            insect_InsectBoardCellToWorld_4eda70(g, &sx, &sy, &sz, 0, (f32)bx, (f32)by);
            insect_InsectPieceMoveTo_5157d0(e, 0, sx, sy, sz, 10.0f);
            o->f4 = o->f4 + 1;
        }
        break;
    case 3:
        if (insect_InsectPieceIsMotionDone_514280(e) != 0) {
            insect_InsectPieceSetYawTarget_5156d0(e, 0.0f, 4.0f);
            o->f4 = o->f4 + 1;
        }
        break;
    case 4:
        t = insect_InsectBoardGetPiece_4ee9a0(g, (s16)(ax + ((bx - ax) / 2)),
                                (s16)(ay + ((by - ay) / 2)));
        k = c->f5F82;
        if (t != 0) {
            if (insect_InsectPieceIsEnemyOf_5149b0(e, t) != 0) {
                j = 0x9C;
                insect_InsectPieceTryInflictSick_514ca0(t, e->f18);
                if (insect_InsectPieceIsSick_514c50(t) == 0) {
                    j = 0x41;
                    insect_InsectBattleDamagePopupSpawn_50f730(t, -1, 0x80402080);
                    insect_InsectPlaySe_510870(7);
                }
                func_1343B8(k, insect_InsectMsgGet_512b70(q, j), t->f5C, n);
                insect_InsectBattleLogPush_51c2f0(r, k, -5, -1, 0);
            }
        }
        insect_InsectBoardTakeAt_4ef770(g, (s16)ax, (s16)ay);
        insect_InsectBoardPlacePiece_4ef830(g, e, (s16)bx, (s16)by);
        return 1;
    }
    return 0;
}
