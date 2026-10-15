#include "types.h"
/* insect 0x00518610 -- 452 bytes, 113 instructions.
 *
 * Three-arm state dispatch on `o->f4`, `beql` into every block, so a `switch`
 * written 0, 1, 2 (the compare chain 2, 1, 0 REVERSED).
 * The float compared against is the MAIN image's gp literal pool entry at
 * 0x0047D288 = 0.6f -- see mwcc-float-literal-pool; writing `0.6f` would put
 * the constant in the overlay's own .lit4 instead.
 */

typedef struct Ctx {
    u8  pad0000[0x4960];
    u8  f4960[4];                   /* +0x4960 */
    u8  pad4964[0x5178 - 0x4964];
    u8  f5178[4];                   /* +0x5178 */
} Ctx;

typedef struct Obj {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
} Obj;

typedef struct Ent {
    u8  pad00[0x6C];
    s16 f6C;                        /* +0x6C */
    u8  pad6E[0xE0 - 0x6E];
    s32 fE0;                        /* +0xE0 */
} Ent;

extern s32  func_1C4A90(s32 h, s16 k);
extern s32  func_1F5BE0(void);
extern Ctx *func_31A8D0(void);
extern void func_391860(s32 h, s32 k, s32 n);
extern void insect_InsectBoardFindPiece_4ee190(void *g, Ent *e, s32 *px, s32 *py);
extern void insect_InsectBoardHoleClear_4ee780(void *g, s32 x, s32 y);
extern Ent *insect_InsectBattleGetActorSlot_50db40(Ctx *c, s32 k);
extern void insect_InsectBattlePieceResetMotion_50f960(Ent *e);
extern f32  insect_InsectPieceGetMotionPhase_5142d0(Ent *e);
extern void insect_InsectPieceMotionQueuePush_514510(Ent *e, const void *d, s32 k, f32 x, f32 y);
extern s32  insect_InsectPieceIsTurnDone_5149f0(Ent *e);
extern void insect_InsectPieceBallDamage_514f10(Ent *e, s32 k);
extern void insect_InsectPieceFaceCell_515590(Ent *e, f32 x, f32 y, f32 t);
extern void insect_InsectSeqGetTargetCell_51b710(s32 *px, s32 *py);
extern void insect_InsectBattleEffectsSpawn_51dc30(void *g, Ent *e, s32 a, s32 b, s32 c,
                                s32 x, s32 y, s32 d, s64 f);

extern const u8 D_00525330[];
extern f32 D_0047D288;              /* gp - 0x7EE8 == 0.6f */

s32 insect_InsectSeqExecReclimed_518610(Obj *o)
{
    Ent *e;
    void *g;
    Ctx *c;
    s32 a;
    s32 b;
    s32 x;
    s32 y;
    s32 h;
    void *q;

    c = func_31A8D0();
    if (o == 0 || c == 0) {
        return 1;
    }
    g = c->f4960;
    e = insect_InsectBattleGetActorSlot_50db40(c, 2);
    if (e == 0) {
        return 1;
    }
    insect_InsectBoardFindPiece_4ee190(g, e, &a, &b);
    insect_InsectSeqGetTargetCell_51b710(&x, &y);
    q = c->f5178;
    switch (o->f4) {
    case 0:
        insect_InsectPieceFaceCell_515590(e, (f32)x, (f32)y, 4.0f);
        o->f4 = o->f4 + 1;
        break;
    case 1:
        if (insect_InsectPieceIsTurnDone_5149f0(e) != 0) {
            insect_InsectPieceMotionQueuePush_514510(e, D_00525330, 6, 0.0f, 1.0f);
            o->f4 = o->f4 + 1;
        }
        break;
    case 2:
        if (insect_InsectPieceGetMotionPhase_5142d0(e) >= D_0047D288) {
            h = func_1C4A90(func_1F5BE0(), e->f6C);
            if (h != 0) {
                func_391860(h, e->fE0, -1);
            }
            insect_InsectBattleEffectsSpawn_51dc30(q, e, 0x19, 6, 0, x, y, 1, 0);
            insect_InsectBoardHoleClear_4ee780(g, x, y);
            insect_InsectPieceBallDamage_514f10(e, 0x270F);
            insect_InsectBattlePieceResetMotion_50f960(e);
            return 1;
        }
        break;
    }
    return 0;
}
