/* MATCH, ix66 (2026-09-14).  Closed by the ONE-CASE SWITCH lever (same
 * session as insect_InsectBattleAttackResolve_4f3480): inside the f38 == 0x11 arm, `t != 0xE` is a
 * `switch (t) { case 0xE: ... break; }` and the y/x loop nest sits in an
 * `else`.  The switch's DEFAULT edge is an unconditional jump to the trailing
 * `return 0` join with an empty own block: mwcc fills its slot from the join's
 * `move $v0,$zero` and MARKS the join, so the 0x11 arm's fall-out at 004EF2A0
 * stays `b <join>`+`nop` as in retail.  As `if (t != 0xE) return 0;` the exit
 * is an independent return, the join is unmarked, and the fall-out takes the
 * copy (`b <epilogue>`+`move`, the 2-bad park).  Exit C spelled `return 0;`
 * under the switch is +1 word.  build/ix66/sweep_4ef0f0_ix66b_switch.log.
 * (ix24i3 draft otherwise unchanged.) */
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x004EF0F0 -- 1252 bytes, 313 instructions, 46 branches.
 * Grid probe with a 14-entry jump table (jtbl_00524970).  m2c REFUSES this
 * unit ("the corresponding jump table is not provided"), so the arms are read
 * off the table targets and ordered by BLOCK ADDRESS, which is mwcc's SOURCE
 * order: 4EF2FC (6,13), 4EF35C (7,9), 4EF49C (1,2,4,5,8), then the empty
 * break group 0,3,10,11,12 which mwcc retargets straight to the switch join
 * and which therefore needs no case labels at all.
 *
 * ONE guarded `/` at 0x004EF3D8 -- `bnez $2 / div / break 0,7` -- so the file
 * carries #pragma divbyzerocheck on (levers.d/mwcc-divbyzerocheck-pragma).
 *
 * `t` is a NAMED local holding ctx->f62: retail spills it with sq/lq to
 * 0xA0($29) for the switch and RE-LOADS ctx->f62 with `lb` at the two
 * equality tests, so those two sites are the bare member, not `t`.
 * The first func_12DE98 result really is discarded.
 */

typedef struct Ent {
    u8  pad00[0x38];
    s8  f38;                        /* +0x38 */
} Ent;

typedef struct Ctx {
    u8  pad00[0x62];
    s8  f62;                        /* +0x62 */
} Ctx;

extern s32  func_12DE98(s32);
extern void insect_InsectBoardCalcAttackRange_4ec720(void *, Ctx *, Ent *, s16, s16);
extern void insect_InsectBoardFindPiece_4ee190(void *, Ent *, s32 *, s32 *);
extern s32  insect_InsectBoardIsInAttackRange_4ee850(void *, s32, s32);
extern Ent *insect_InsectBoardGetPiece_4ee9a0(void *, s16, s16);
extern s32  insect_InsectPieceIsEnemyOf_5149b0(Ent *, Ent *);
extern s32  insect_InsectPieceIsDizzy_514c10(Ent *);
extern s32  insect_InsectPieceIsFlipped_514c30(Ent *);
extern s32  insect_InsectPieceIsPoisoned_514c70(Ent *);

Ent *insect_InsectBoardAbilityFindTarget_4ef0f0(void *g, Ent *tgt, Ctx *ctx, s32 sx, s32 sy,
                         s32 *px, s32 *py, Ent *cur)
{
    s32 n;
    s32 m;
    s32 ok;
    Ent *e;
    s32 y;
    s32 x;
    s32 t;
    s32 i;
    s32 j;
    s32 dy;
    s32 dx;
    s32 v;
    s32 lx;
    s32 ly;
    s32 cx;
    s32 cy;
    s32 ex;
    s32 ey;
    s32 tx;
    s32 ty;

    if (tgt == 0 || ctx == 0) {
        return 0;
    }
    insect_InsectBoardCalcAttackRange_4ec720(g, ctx, tgt, sx, sy);
    t = ctx->f62;

    if (tgt->f38 == 0x11) {
        switch (t) {
        case 0xE:
            insect_InsectBoardFindPiece_4ee190(g, tgt, &cx, &cy);
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 5; j++) {
                    if (insect_InsectBoardIsInAttackRange_4ee850(g, j, i) != 0) {
                        cx = j;
                        cy = i;
                    }
                }
            }
            for (dy = -1; dy <= 1; dy++) {
                for (dx = -1; dx <= 1; dx++) {
                    e = insect_InsectBoardGetPiece_4ee9a0(g, cx + dx, cy + dy);
                    if (e != 0 && insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0) {
                        *px = sx;
                        *py = sy;
                        if (cur != 0) {
                            if (cur == e) {
                                return e;
                            }
                        } else {
                            return e;
                        }
                    }
                }
            }
            break;
        }
    } else {
        for (y = 0; y < 7; y++) {
            for (x = 0; x < 5; x++) {
                e = insect_InsectBoardGetPiece_4ee9a0(g, x, y);
                if (e != 0) {
                    switch (t) {
                    case 6:
                    case 13:
                        if (insect_InsectBoardIsInAttackRange_4ee850(g, x, y) != 0 &&
                            insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0) {
                            *px = sx;
                            *py = sy;
                            if (cur != 0) {
                                if (cur == e) {
                                    return e;
                                }
                            } else {
                                return e;
                            }
                        }
                        break;

                    case 7:
                    case 9:
                        if (insect_InsectBoardIsInAttackRange_4ee850(g, x, y) != 0) {
                            m = 0;
                            insect_InsectBoardFindPiece_4ee190(g, tgt, &tx, &ty);
                            insect_InsectBoardFindPiece_4ee190(g, e, &ex, &ey);
                            lx = func_12DE98(ex - tx);
                            ly = func_12DE98(ey - ty);
                            if (ly != 0) {
                                m = (ey - ty) / ly;
                            }
                            n = 0;
                            if (m > 0) {
                                m = 0;
                                while (m < 7) {
                                    if (insect_InsectBoardGetPiece_4ee9a0(g, tx, m) != 0) {
                                        break;
                                    }
                                    n++;
                                    m++;
                                }
                            } else if (m < 0) {
                                while (m >= 0) {
                                    if (insect_InsectBoardGetPiece_4ee9a0(g, tx, m) != 0) {
                                        break;
                                    }
                                    n++;
                                    m--;
                                }
                            }
                            if (n > 0) {
                                if (ctx->f62 == 7) {
                                    return e;
                                }
                                if (cur != 0) {
                                    if (cur == e) {
                                        return e;
                                    }
                                } else {
                                    return e;
                                }
                            }
                        }
                        break;

                    case 1:
                    case 2:
                    case 4:
                    case 5:
                    case 8:
                        if (insect_InsectBoardIsInAttackRange_4ee850(g, x, y) != 0 &&
                            insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0) {
                            ok = 1;
                            if (ctx->f62 == 4) {
                                v = tgt->f38;
                                switch (v) {
                                case 3:
                                    if (insect_InsectPieceIsFlipped_514c30(e) != 0) {
                                        ok = 0;
                                    }
                                    break;
                                case 7:
                                    if (insect_InsectPieceIsPoisoned_514c70(e) != 0) {
                                        ok = 0;
                                    }
                                    break;
                                case 9:
                                    if (insect_InsectPieceIsDizzy_514c10(e) != 0) {
                                        ok = 0;
                                    }
                                    break;
                                }
                            }
                            insect_InsectBoardFindPiece_4ee190(g, e, px, py);
                            if (ok != 0) {
                                if (cur != 0) {
                                    if (cur == e) {
                                        return e;
                                    }
                                } else {
                                    return e;
                                }
                            }
                        }
                        break;

                    case 0:
                    case 3:
                    case 10:
                    case 11:
                    case 12:
                        break;
                    }
                }
            }
        }
    }
    return 0;
}
