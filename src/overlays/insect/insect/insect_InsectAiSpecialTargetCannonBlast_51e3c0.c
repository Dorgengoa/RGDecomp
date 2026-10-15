#include "types.h"
/* insect 0x0051E3C0 -- 404 bytes, 101 instructions.
 *
 * A 7x5 scan over a grid, keeping the "best" entry.  The two coordinate
 * parameters are narrowed at the CALL, not in the prologue, so they are s32
 * parameters feeding s16 callee parameters (the converse of ixa09's lever).
 * The `beql $2,$0,.L0051E510` with `addiu $17,$17,1` annulled is the inner
 * `continue`.
 */

typedef struct Ctx {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Ctx;

extern void insect_InsectBoardCalcAttackRange_4ec720(s32 h, s32 c, s32 b, s16 d, s16 e);
extern s32 insect_InsectBoardIsInAttackRange_4ee850(s32 h, s32 i, s32 j);
extern s32 insect_InsectBoardGetPiece_4ee9a0(s32 h, s16 i, s16 j);
extern f32 insect_InsectPieceGetHpRatio_512e70(s32 o);
extern s32 insect_InsectPieceIsEnemyOf_5149b0(s32 b, s32 o);
extern s32 insect_InsectPieceIsInPlay_5149e0(s32 o);
extern s32 insect_InsectPieceIsKing_514b00(s32 o);

extern f32 D_0047D344;              /* _gp - 0x7E2C */

s32 insect_InsectAiSpecialTargetCannonBlast_51e3c0(Ctx *a, s32 b, s32 c, s32 d, s32 e)
{
    s32 best;
    s32 j;
    s32 i;
    s32 o;
    f32 v;

    if ((b == 0) || (c == 0)) {
        return 0;
    }
    insect_InsectBoardCalcAttackRange_4ec720(a->f58, c, b, d, e);
    best = 0;
    for (j = 6; j >= 0; j--) {
        for (i = 0; i < 5; i++) {
            if (insect_InsectBoardIsInAttackRange_4ee850(a->f58, i, j) == 0) {
                continue;
            }
            o = insect_InsectBoardGetPiece_4ee9a0(a->f58, i, j);
            if (o == 0) {
                continue;
            }
            if (b == o) {
                continue;
            }
            if (insect_InsectPieceIsEnemyOf_5149b0(b, o) == 0) {
                continue;
            }
            if (insect_InsectPieceIsInPlay_5149e0(o) == 0) {
                continue;
            }
            if (best == 0) {
                best = o;
                continue;
            }
            if (insect_InsectPieceIsKing_514b00(best) == 0) {
                if (insect_InsectPieceGetHpRatio_512e70(best) < D_0047D344) {
                    continue;
                }
                v = insect_InsectPieceGetHpRatio_512e70(best);
                if (v < insect_InsectPieceGetHpRatio_512e70(o)) {
                    continue;
                }
                best = o;
            } else {
                if (insect_InsectPieceGetHpRatio_512e70(o) <= D_0047D344) {
                    best = o;
                }
            }
        }
    }
    return best;
}
