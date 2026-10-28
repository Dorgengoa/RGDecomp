/* rgp:protos */
#define RGP_SELF_insect_InsectAiSpecialTargetEmperorsRage_51e8f0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x0051E8F0 -- 1160 bytes, 290 instructions, 46 branches.
 * Target picker over the 5x7 battle grid.  Two whole scan passes -- the
 * mode==0 pass walks a ray from the caster toward each candidate and the
 * mode!=0 pass just filters -- each ending in the same comparison against the
 * currently-held target, so BOTH fall through to one trailing `return best`
 * (levers: "an early return costs a word; make it the TRAILING block").
 * Carries retail's divide-by-zero trap twice
 * (levers.d/mwcc-divbyzerocheck-pragma).
 */

typedef struct Ent Ent;

typedef struct Ctx {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Ctx;

extern s32  abs(s32);
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

Ent *insect_InsectAiSpecialTargetEmperorsRage_51e8f0(Ctx *o, Ent *tgt, s32 c, s32 sx, s32 sy, s32 mode,
                         Ent *cur)
{
    s32 ex;
    s32 ey;
    Ent *best;
    s32 i;
    Ent *e;
    s32 j;
    s32 blocked;
    s32 ok;
    s32 dx;
    s32 dy;
    s32 lx;
    s32 ly;
    f32 vb;

    best = 0;
    if (tgt == 0 || c == 0) {
        return 0;
    }

    if (mode == 0) {
        insect_InsectBoardMarkReachableTargets_4ec580(o->f58, (int)tgt);
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 5; j++) {
                if (insect_InsectBoardIsTargetMarked_4ee8c0(o->f58, j, i) != 0) {
                    e = ((Ent *)insect_InsectBoardGetPiece_4ee9a0(o->f58, j, i));
                    blocked = 0;
                    ok = 0;
                    if (e != 0 && tgt != e &&
                        insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0 &&
                        insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                        ok = 1;
                        dx = 0;
                        dy = 0;
                        insect_InsectBoardFindPiece_4ee190(o->f58, e, &ex, &ey);
                        lx = abs(ex - sx);
                        ly = abs(ey - sy);
                        if (lx != 0) {
                            dx = (ex - sx) / lx;
                        }
                        if (ly != 0) {
                            dy = (ey - sy) / ly;
                        }
                    ray:
                        if (((Ent *)insect_InsectBoardGetPiece_4ee9a0(o->f58, ex, ey))) {
                            ex += dx;
                            ey += dy;
                            goto ray;
                        }
                        if (ex < 0 || ex >= 4 || ey < 0 || ey >= 6) {
                            blocked = 1;
                        } else if (insect_InsectBoardIsHole_4ee7e0(o->f58, ex, ey) != 0) {
                            blocked = 1;
                        }
                    }
                    if (ok != 0) {
                        if (blocked != 0) {
                            insect_InsectPieceSetStatus_5132d0(e, 0x12);
                            return e;
                        }
                        if (best != 0) {
                            vb = insect_InsectPieceGetHpRatio_512e70(best);
                            if (!(vb < insect_InsectPieceGetHpRatio_512e70(e))) {
                                best = e;
                            }
                        } else {
                            best = e;
                        }
                    }
                }
            }
        }
        if (best != 0 && cur != 0) {
            if (best == cur) {
                return 0;
            }
            if (insect_InsectPieceIsKing_514b00(cur) != 0) {
                return 0;
            }
            vb = insect_InsectPieceGetHpRatio_512e70(best);
            if (!(vb < insect_InsectPieceGetHpRatio_512e70(cur))) {
                return 0;
            }
            if (insect_InsectPieceTestStatus_513280(cur, 0x12) != 0) {
                return 0;
            }
        }
    } else {
        insect_InsectBoardCalcAttackRange_4ec720(o->f58, c, tgt, sx, sy);
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 5; j++) {
                if (insect_InsectBoardIsInAttackRange_4ee850(o->f58, j, i) != 0) {
                    ok = 0;
                    e = ((Ent *)insect_InsectBoardGetPiece_4ee9a0(o->f58, j, i));
                    if (e != 0 && tgt != e &&
                        insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0 &&
                        insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        if (best != 0) {
                            if (insect_InsectPieceIsKing_514b00(best) == 0) {
                                vb = insect_InsectPieceGetHpRatio_512e70(best);
                                if (!(vb < insect_InsectPieceGetHpRatio_512e70(e))) {
                                    best = e;
                                }
                            }
                        } else {
                            best = e;
                        }
                    }
                }
            }
        }
        if (best != 0 && cur != 0) {
            if (best == cur) {
                return 0;
            }
            if (insect_InsectPieceIsKing_514b00(cur) != 0) {
                return 0;
            }
            vb = insect_InsectPieceGetHpRatio_512e70(best);
            if (!(vb < insect_InsectPieceGetHpRatio_512e70(cur))) {
                return 0;
            }
        }
    }
    return best;
}
