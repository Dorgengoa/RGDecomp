#include "types.h"
/* insect 0x0051ED80 -- 716 bytes, 180 instructions, 17 calls, 27 branches.
 * Sibling of insect_InsectAiSpecialTargetEmperorsRage_51e8f0: the same 5x7 battle-grid target picker, but
 * the mode!=0 pass only COUNTS candidates (an s8 counter, hence the
 * dsll32/dsra32 24 narrowing at every use) and tags the caster when two or
 * more are found.  Both passes join one trailing `return best`.
 */

typedef struct Ctx {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Ctx;

typedef struct Ent {
    u8  pad00[0x1A];
    s16 f1A;                        /* +0x1A */
} Ent;

extern void insect_InsectBoardMarkReachableTargets_4ec580(s32);
extern void insect_InsectBoardCalcAttackRange_4ec720(s32, s32, Ent *, s16, s16);
extern s32  insect_InsectBoardIsInAttackRange_4ee850(s32, s32, s32);
extern s32  insect_InsectBoardIsTargetMarked_4ee8c0(s32, s32, s32);
extern Ent *insect_InsectBoardGetPiece_4ee9a0(s32, s16, s16);
extern s32  insect_InsectBattleCalcBaseDamage_50ffb0(Ent *, Ent *, s32);
extern f32  insect_InsectPieceGetHpRatio_512e70(Ent *);
extern void insect_InsectPieceSetStatus_5132d0(Ent *, s32);
extern s32  insect_InsectPieceIsEnemyOf_5149b0(Ent *, Ent *);
extern s32  insect_InsectPieceIsInPlay_5149e0(Ent *);
extern s32  insect_InsectPieceIsKing_514b00(Ent *);

Ent *insect_InsectAiSpecialTargetBerserker_51ed80(Ctx *o, Ent *tgt, s32 c, s32 sx, s32 sy, s32 mode,
                         Ent *cur)
{
    s32 ok;
    s32 n;
    Ent *best;
    s32 i;
    s32 j;
    Ent *e;
    f32 vb;

    best = 0;
    if (tgt == 0 || c == 0) {
        return 0;
    }

    if (mode == 0) {
        insect_InsectBoardMarkReachableTargets_4ec580(o->f58);
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 5; j++) {
                ok = 0;
                if (insect_InsectBoardIsTargetMarked_4ee8c0(o->f58, j, i) != 0) {
                    e = insect_InsectBoardGetPiece_4ee9a0(o->f58, j, i);
                    if (e != 0 && tgt != e &&
                        insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0 &&
                        insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                        ok = 1;
                    }
                    if (ok != 0) {
                        if (best != 0) {
                            if (insect_InsectPieceIsKing_514b00(best) != 0) {
                                {
                                    s32 rr;
                                    rr = insect_InsectBattleCalcBaseDamage_50ffb0(tgt, e, 0);
                                    if (e->f1A > rr) {
                                    } else {
                                        best = e;
                                    }
                                }
                            } else {
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
    } else {
        insect_InsectBoardCalcAttackRange_4ec720(o->f58, c, tgt, sx, sy);
        n = 0;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 5; j++) {
                if (insect_InsectBoardIsInAttackRange_4ee850(o->f58, j, i) != 0) {
                    e = insect_InsectBoardGetPiece_4ee9a0(o->f58, j, i);
                    if (e != 0 && tgt != e &&
                        insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0 &&
                        insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                        n = (s8)(n + 1);
                    }
                }
            }
        }
        if ((s8)n >= 2) {
            insect_InsectPieceSetStatus_5132d0(tgt, 0x12);
            return tgt;
        }
    }

    if (cur != 0 && best != 0) {
        if (cur == best) {
            return 0;
        }
        vb = insect_InsectPieceGetHpRatio_512e70(best);
        if (!(vb < insect_InsectPieceGetHpRatio_512e70(cur))) {
            return 0;
        }
    }
    return best;
}
