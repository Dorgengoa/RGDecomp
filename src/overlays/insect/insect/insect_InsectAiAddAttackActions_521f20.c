#include "types.h"
/* insect 0x00521F20 -- 496 bytes, 124 instructions.
 *
 * Walks the 7x5 grid in the direction chosen by `o->f930`, collecting every
 * acceptable target into the record list at `o + 0xC4`.
 * The `dsll32/dsra32 ..,16` pairs are (s16) casts of s32 locals and the
 * `lh 0xA0($29)` is the same cast read straight out of the spill slot.
 */

typedef struct Rec {
    s32 f0;                         /* +0x00 */
    s32 f4;                         /* +0x04 */
    s32 f8;                         /* +0x08 */
    u8  padC[0x10 - 0xC];
    s8  f10;                        /* +0x10 */
    s8  f11;                        /* +0x11 */
    u8  pad12[0x14 - 0x12];
    s8  f14;                        /* +0x14 */
    u8  pad15[0x1C - 0x15];
    s8  f1C;                        /* +0x1C */
} Rec;

typedef struct Ctx {
    u8  pad00[0x58];
    void *f58;                      /* +0x58 */
    u8  pad5C[0xC4 - 0x5C];
    u8  fC4[4];                     /* +0xC4 */
    u8  padC8[0x930 - 0xC8];
    s8  f930;                       /* +0x930 */
} Ctx;

extern void insect_InsectBoardMarkAdjacentTargetsAt_4ed140(void *g, s16 x, s16 y);
extern void insect_InsectBoardCalcMoveRange_4ed180(void *g, s32 e);
extern s32  insect_InsectBoardIsTargetMarked_4ee8c0(void *g, s32 i, s32 j);
extern s32  insect_InsectBoardIsMovable_4ee930(void *g, s32 x, s32 y);
extern s32  insect_InsectBoardGetPiece_4ee9a0(void *g, s16 i, s16 j);
extern s32  insect_InsectBoardInBounds_4efac0(void *g, s32 x, s32 y);
extern s32  insect_InsectPieceIsEnemyOf_5149b0(s32 e, s32 t);
extern s32  insect_InsectPieceIsInPlay_5149e0(s32 t);
extern s32  insect_InsectPieceIsKing_514b00(s32 t);
extern void insect_InsectAiActionListAdd_5232e0(void *l, Rec *r);
extern Rec *insect_InsectAiActionNew_523330(void *l);

s32 insect_InsectAiAddAttackActions_521f20(Ctx *o, s32 e, s32 px, s32 py)
{
    s32 ret;
    s32 start;
    s32 step;
    s32 row;
    s32 i;
    s32 j;
    s32 t;
    Rec *r;

    ret = 0;
    if (e == 0) {
        return 0;
    }
    step = 1;
    start = 0;
    if (o->f930 == 0) {
        start = 6;
        step = -1;
    }
    insect_InsectBoardCalcMoveRange_4ed180(o->f58, e);
    if (insect_InsectBoardInBounds_4efac0(o->f58, px, py) != 0 &&
        insect_InsectBoardIsMovable_4ee930(o->f58, px, py) != 0) {
        insect_InsectBoardMarkAdjacentTargetsAt_4ed140(o->f58, px, py);
        for (j = 0; j < 7; j++) {
            row = start + j * step;
            for (i = 0; i < 5; i++) {
                if (insect_InsectBoardIsTargetMarked_4ee8c0(o->f58, i, row) != 0) {
                    t = insect_InsectBoardGetPiece_4ee9a0(o->f58, i, row);
                    if (t != 0 && insect_InsectPieceIsEnemyOf_5149b0(e, t) != 0 &&
                        insect_InsectPieceIsInPlay_5149e0(t) != 0) {
                        r = insect_InsectAiActionNew_523330(o->fC4);
                        if (r != 0) {
                            r->f10 = (s8)px;
                            r->f11 = (s8)py;
                            r->f0 = e;
                            r->f4 = t;
                            r->f8 = t;
                            r->f14 = 3;
                            if (insect_InsectPieceIsKing_514b00(t) != 0) {
                                r->f1C = r->f1C + 1;
                            }
                            insect_InsectAiActionListAdd_5232e0(o->fC4, r);
                            ret = 1;
                        }
                    }
                }
            }
        }
    }
    return ret;
}
