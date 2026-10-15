#include "types.h"

typedef struct Ent {
    u8 pad00[0x38];
    s8 f38;
} Ent;

typedef struct Obj {
    u8 pad00[0x58];
    void *f58;
    u8 pad5c[0x8D4];
    s8 f930;
} Obj;

extern void insect_InsectBoardFindPiece_4ee190(void *, Ent *, s32 *, s32 *);
extern void insect_InsectBoardCalcMoveRange_4ed180(void *, Ent *);
extern Ent *insect_InsectAiGetPiece_5228f0(Obj *, s32);
extern s32 insect_InsectPieceIsEnemyOf_5149b0(Ent *, Ent *);
extern s32 insect_InsectPieceIsInPlay_5149e0(Ent *);
extern s32 insect_InsectBoardIsMovable_4ee930(void *, s32, s32);
extern Ent *insect_InsectBoardGetPiece_4ee9a0(void *, s16, s16);
extern s32 insect_InsectBoardFindNearestTarget_4ee000(void *, Ent *, s32);
extern void insect_InsectBoardPickMoveCell_4edd90(void *, Ent *, s32, s32 *, s32 *, s32);

s32 insect_InsectAiPickCoverCellMaybe_5224c0(Obj *o, Ent *tgt, s32 *outA, s32 *outB)
{
    s32 a;
    s32 b;
    s32 bestI;
    s32 bestJ;
    Ent *e2;
    s32 base;
    Ent *e4;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 t;
    s32 flag;
    s32 dir;
    Ent *e3;
    Ent *e;
    s32 y;
    s32 y2;
    s32 ok;
    s32 h;

    if (tgt == 0) {
        return 0;
    }
    bestI = -0x3E7;
    bestJ = -0x3E7;
    insect_InsectBoardFindPiece_4ee190(o->f58, tgt, outA, outB);
    insect_InsectBoardCalcMoveRange_4ed180(o->f58, tgt);
    flag = 0;
    for (i = 0; i < 10; i++) {
        e = insect_InsectAiGetPiece_5228f0(o, i);
        if (e != 0 && insect_InsectPieceIsEnemyOf_5149b0(tgt, e) != 0) {
            t = e->f38;
            if (t == 8 || t == 0xD) {
                flag = 1;
            }
        }
    }
    dir = 1;
    base = 0;
    if (o->f930 == 0) {
        base = 6;
        dir = -1;
    }
    for (k = 0; k < 10; k++) {
        e2 = insect_InsectAiGetPiece_5228f0(o, k);
        if (e2 != 0 && tgt != e2 && insect_InsectPieceIsEnemyOf_5149b0(tgt, e2) == 0 &&
            insect_InsectPieceIsInPlay_5149e0(e2) != 0) {
            insect_InsectBoardFindPiece_4ee190(o->f58, e2, &a, &b);
            for (n = 0; n < 7; n++) {
                y = base + dir * (n + flag);
                y2 = y + dir;
                for (j = 0; j < 5; j++) {
                    if (insect_InsectBoardIsMovable_4ee930(o->f58, j, y) != 0 && a == j) {
                        ok = 0;
                        if (b >= y) {
                            ok = 1;
                        }
                        if (dir < 0) {
                            ok = 0;
                            if (b <= y) {
                                ok = 1;
                            }
                        }
                        if (ok != 0) {
                            if (bestI == -0x3E7 && bestJ == -0x3E7) {
                                bestI = j;
                                bestJ = y;
                            } else if (y != 0) {
                                ok = 0;
                                if (y < bestJ) {
                                    ok = 1;
                                }
                                if (dir < 0) {
                                    ok = 0;
                                    if (bestJ < y) {
                                        ok = 1;
                                    }
                                }
                                if (ok != 0) {
                                    bestI = j;
                                    bestJ = y;
                                }
                            } else {
                                e3 = insect_InsectBoardGetPiece_4ee9a0(o->f58, j, y2);
                                e4 = insect_InsectBoardGetPiece_4ee9a0(o->f58, j, y);
                                if (e3 != 0 && e4 == 0 && e3 != tgt &&
                                    insect_InsectPieceIsEnemyOf_5149b0(tgt, e3) == 0) {
                                    bestI = j;
                                    bestJ = y;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (bestI == -0x3E7 && bestJ == -0x3E7) {
        h = insect_InsectBoardFindNearestTarget_4ee000(o->f58, tgt, 1);
        if (h != 0) {
            insect_InsectBoardPickMoveCell_4edd90(o->f58, tgt, h, outA, outB, 1);
            while (flag < 7) {
                y = base + flag * dir;
                if (insect_InsectBoardIsMovable_4ee930(o->f58, *outA, y) != 0) {
                    *outB = y;
                    break;
                }
                flag++;
            }
        }
    } else {
        *outA = bestI;
        *outB = bestJ;
    }
    return 1;
}
