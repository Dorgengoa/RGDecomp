#include "types.h"
/* insect 0x00516770 -- 704 bytes, 176 instructions.
 *
 * A five-state step function, twin of insect_InsectSeqExecReclimed_518610.  Every compare
 * branches INTO its arm with a `beql`, so the source case order is the compare
 * chain REVERSED: 0, 1, 2, 3, 4.
 *
 * `sd $0, 0x0($29)` is insect_InsectBattleEffectsSpawn_51dc30's NINTH argument, an `s64` on the
 * stack past $4..$11 -- the spelling insect_InsectSeqExecReclimed_518610 already carries.
 * The `bgez` / `addiu 1` / `sra 1` fan is a signed divide by two, and both
 * latches put their `slti` in `$at`, which at-compare-class reads as the
 * "or-equal" spelling `i <= 1`.
 */

typedef struct Ent {
    u8  pad00[0x42];
    u8  f42;                        /* +0x42 */
} Ent;

typedef struct Grid {
    u8  pad000[0x1A4];
    u8  f1A4[0x14][5];              /* +0x1A4 */
    u8  pad208[0x818 - 0x208];
} Grid;

typedef struct Ctx {
    u8   pad0000[0x4960];
    Grid f4960;                     /* +0x4960 */
    u8   f5178[4];                  /* +0x5178 */
} Ctx;

typedef struct Ctl {
    u8  pad00[0x4];
    s32 f4;                         /* +0x04 */
    u8  fC[0x20 - 0x8];             /* +0x08 (the record handed to 00514510
                                     * starts at +0xC) */
    f32 f20;                        /* +0x20 */
    f32 f24;                        /* +0x24 */
    s32 f28;                        /* +0x28 */
} Ctl;

typedef struct Hit {
    s32 f00;                        /* +0x00 */
    s32 f04;                        /* +0x04 */
    s32 f08;                        /* +0x08 */
} Hit;

extern s32   D_0048103C;            /* _gp - 0x4134 */

extern Ctx  *func_31A8D0(void);
extern void  insect_InsectSeqGetActors_51b7e0(Hit *h, s32 a, s32 b);
extern void  insect_InsectSeqGetTargetCell_51b710(s32 *px, s32 *py);
extern void  insect_InsectPieceFaceCell_515590(Ent *e, f32 x, f32 y, f32 t);
extern s32   insect_InsectPieceIsTurnDone_5149f0(Ent *e);
extern void  insect_InsectPieceMotionQueueClear_514320(Ent *e);
extern void  insect_InsectPieceMotionQueuePush_514510(Ent *e, const u8 *p, f32 a, s32 k, f32 b);
extern void  insect_InsectBattlePieceResetMotion_50f960(Ent *e);
extern s32   insect_InsectBattleEffectsSpawn_51dc30(void *g, Ent *e, s32 a, s32 b, s32 c,
                                 s32 x, s32 y, s32 d, s64 f);
extern f32   insect_InsectPieceGetMotionPhase_5142d0(Ent *e);
extern s32   insect_InsectBattleEffectsIsSlotUsed_51d3a0(void *q, s32 k);
extern void  insect_InsectBoardWebPlace_4ee4d0(Grid *g, s32 x, s32 y);
extern s32   insect_InsectBoardInBounds_4efac0(Grid *g, s32 x, s32 y);
extern Ent  *insect_InsectBoardGetPiece_4ee9a0(Grid *g, s16 x, s16 y);
extern void  insect_InsectPieceSetStatus_5132d0(Ent *e, s32 k);
extern s32   insect_InsectPieceIsEnemyOf_5149b0(Ent *a, Ent *b);

s32 insect_InsectSeqExecSpiderWeb_516770(Ctl *c)
{
    s32   x;
    s32   y;
    Hit   st;
    Ctx  *ctx;
    Grid *g;
    void *q;
    Ent  *e;
    s32   j;
    s32   i;
    Ent  *ent;
    s32   px;
    s32   py;
    s32   t;
    f32   v;

    ctx = func_31A8D0();
    g = &ctx->f4960;
    q = ctx->f5178;
    insect_InsectSeqGetActors_51b7e0(&st, 2, 1);
    e = (Ent *)st.f00;
    insect_InsectSeqGetTargetCell_51b710(&x, &y);
    switch (c->f4) {
    case 0:
        D_0048103C = -1;
        insect_InsectPieceFaceCell_515590(e, (f32)x, (f32)y, 4.0f);
        c->f4 = c->f4 + 1;
        break;
    case 1:
        if (insect_InsectPieceIsTurnDone_5149f0(e) != 0) {
            insect_InsectPieceMotionQueueClear_514320(e);
            insect_InsectPieceMotionQueuePush_514510(e, &c->fC[4], c->f20, c->f28, 1.0f);
            insect_InsectBattlePieceResetMotion_50f960(e);
            insect_InsectBattleEffectsSpawn_51dc30(q, e, 0xE, 6, 0, -1, -1, 1, 0);
            c->f4 = c->f4 + 1;
        }
        break;
    case 2:
        v = c->f24;
        if (insect_InsectPieceGetMotionPhase_5142d0(e) >= v) {
            D_0048103C = insect_InsectBattleEffectsSpawn_51dc30(q, e, 0x21, 6, 0, x, y, 1, 0);
            c->f4 = c->f4 + 1;
        }
        break;
    case 3:
        if (insect_InsectBattleEffectsIsSlotUsed_51d3a0(q, D_0048103C) == 0) {
            insect_InsectBoardWebPlace_4ee4d0(g, x, y);
            for (j = -1; j <= 1; j++) {
                for (i = -1; i <= 1; i++) {
                    px = i + x;
                    py = j + y;
                    if (insect_InsectBoardInBounds_4efac0(g, px, py) == 0) {
                        continue;
                    }
                    ent = insect_InsectBoardGetPiece_4ee9a0(g, px, py);
                    if (ent == 0) {
                        continue;
                    }
                    insect_InsectPieceSetStatus_5132d0(ent, 6);
                    t = ((g->f1A4[py][px] & 0xF0) >> 4) / 2;
                    if (insect_InsectPieceIsEnemyOf_5149b0(e, ent) != 0) {
                        t = t + 1;
                    }
                    ent->f42 = t;
                }
            }
            c->f4 = c->f4 + 1;
        }
        break;
    case 4:
        return 1;
    }
    return 0;
}
