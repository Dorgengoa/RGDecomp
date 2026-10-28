/* rgp:protos */
#define RGP_SELF_insect_InsectAiSpecialTargetCharmBeam_51e560 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051E560 -- 904 bytes, 228 instructions, 21 calls, 30 branches.
 * Sibling of insect_InsectAiSpecialTargetEmperorsRage_51e8f0 / insect_InsectAiSpecialTargetBerserker_51ed80: the 5x7 grid target
 * picker again, this time walking rows 6..0 and ranking candidates first by a
 * 19-entry priority table copied onto the stack from insect_D_005245F0, then by
 * either a float score (mode==0) or an integer score (mode!=0).
 */

typedef struct Ctx {
    u8  pad00[0x58];
    s32 f58;                        /* +0x58 */
} Ctx;

typedef struct Ent {
    u8  pad00[0x18];
    s8  f18;                        /* +0x18 */
    u8  pad19[0x38 - 0x19];
    s8  f38;                        /* +0x38 */
} Ent;

extern s16  insect_D_005245F0[19];
extern f32  D_0047D90C;             /* _gp - 0x7864 */
extern f32  D_0047DC84;             /* _gp - 0x74EC */
extern f32  D_0047D288;             /* _gp - 0x7EE8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

Ent *insect_InsectAiSpecialTargetCharmBeam_51e560(Ctx *o, Ent *tgt, s32 c, s32 sx, s32 sy, s32 mode,
                         Ent *cur)
{
    s32 ok;
    Ent *best;
    s32 i;
    s32 j;
    Ent *e;
    s32 t;
    s16 *s;
    s16 *d;
    s32 n;
    f32 vb;
    s16 tbl[19] __attribute__((aligned(16)));

    best = 0;
    if (tgt == 0 || c == 0) {
        return 0;
    }
    if (insect_InsectPieceIsKing_514b00(tgt) != 0 &&
        insect_InsectPieceGetHpRatio_512e70(tgt) <= D_0047D90C) {
        return 0;
    }
    if (insect_InsectPieceGetHpRatio_512e70(tgt) <= 0.5f &&
        !(insect_InsectPieceGetHpRatio_512e70(tgt) < D_0047DC84)) {
        return 0;
    }

    d = tbl;
    s = insect_D_005245F0;
    n = 0x13;
    do {
        *d = *s;
        s++;
        d++;
        n--;
    } while (n > 0);

    insect_InsectBoardCalcAttackRange_4ec720(o->f58, c, tgt, sx, sy);
    for (i = 6; i >= 0; i--) {
        for (j = 0; j < 5; j++) {
            if (insect_InsectBoardIsInAttackRange_4ee850(o->f58, j, i) != 0) {
                ok = 0;
                e = ((Ent *)insect_InsectBoardGetPiece_4ee9a0(o->f58, j, i));
                if (e != 0 && tgt != e &&
                    insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0 &&
                    insect_InsectPieceIsInPlay_5149e0(e) != 0 &&
                    insect_InsectPieceIsKing_514b00(e) == 0 &&
                    !(insect_InsectPieceGetHpRatio_512e70(e) < D_0047D288) &&
                    (mode == 0 ||
                     insect_InsectPieceRollVsResist_512bf0(e, insect_InsectPieceGetStat_512e20(e, 1, 0),
                                         tgt->f18) != 0)) {
                    ok = 1;
                }
                if (ok != 0) {
                    if (best != 0) {
                        if (tbl[best->f38] >= tbl[e->f38]) {
                            if (mode != 0) {
                                t = insect_InsectPieceGetStat_512e20(best, 1, 0);
                                if (!(t < insect_InsectPieceGetStat_512e20(e, 1, 0))) {
                                    best = e;
                                }
                            } else {
                                vb = insect_InsectPieceGetHpRatio_512e70(best);
                                if (vb <= insect_InsectPieceGetHpRatio_512e70(e)) {
                                    best = e;
                                }
                            }
                        }
                    } else {
                        best = e;
                    }
                }
            }
        }
    }

    if (cur != 0 && best != 0 && tbl[best->f38] >= tbl[cur->f38]) {
        if (mode != 0) {
            t = insect_InsectPieceGetStat_512e20(best, 1, 0);
            if (!(t < insect_InsectPieceGetStat_512e20(cur, 1, 0))) {
                best = 0;
            }
        } else {
            vb = insect_InsectPieceGetHpRatio_512e70(best);
            if (vb <= insect_InsectPieceGetHpRatio_512e70(cur)) {
                best = 0;
            }
        }
    }
    return best;
}
