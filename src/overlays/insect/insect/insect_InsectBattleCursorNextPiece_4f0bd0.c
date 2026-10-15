#include "types.h"
/* insect 0x004F0BD0 -- 472 bytes, 118 instructions.
 *
 * Steps a cursor over the 10 slots of `o->f5EED[]` looking for one whose
 * entity passes three tests, recursing (tail) with a bumped depth when the
 * slot is rejected.  Depth is capped at 10.
 */

typedef struct Ent {
    u8  pad00[0x71];
    s8  f71;                        /* +0x71 */
} Ent;

typedef struct Obj {
    u8  pad0000[0x4960];
    u8  f4960[4];                   /* +0x4960 */
    u8  pad4964[0x4F90 - 0x4964];
    u8  f4F90[4];                   /* +0x4F90 */
    u8  pad4F94[0x5EED - 0x4F94];
    s8  f5EED[4];                   /* +0x5EED */
    u8  f5EF1;                      /* +0x5EF1 */
} Obj;

extern void insect_InsectBoardFindPiece_4ee190(void *g, Ent *e, s32 *px, s32 *py);
extern Ent *insect_InsectBattleGetPiece_4f0b90(Obj *o, s32 n);
extern void insect_InsectCursorSetPageSetCell_511c20(void *t, s32 k, s32 x, s32 y);
extern s32  insect_InsectCursorSetFindPage_511e60(void *t, s32 k);
extern s32  insect_InsectPieceTestStatus_513280(Ent *e, s32 k);
extern s32  insect_InsectPieceCanAct_514920(Ent *e);
extern s32  insect_InsectPieceIsInPlay_5149e0(Ent *e);

void insect_InsectBattleCursorNextPiece_4f0bd0(Obj *o, s32 a1, s32 a2, s32 a3, s32 a4, s32 depth)
{
    void *g;
    s32 x;
    s32 y;
    s32 k;
    s8 *p;
    s32 d;
    s32 v;
    Ent *e;
    s32 ok;
    s32 m;

    g = o->f4960;
    p = &o->f5EED[o->f5EF1];
    k = insect_InsectCursorSetFindPage_511e60(o->f4F90, a1);
    if (depth < 0xA) {
        if (a2 != 0) {
            *p = -1;
            insect_InsectBattleCursorNextPiece_4f0bd0(o, a1, 0, a3, 0x800, 0);
        } else {
            d = 1;
            if ((a4 & 0x100) != 0) {
                d = -1;
            }
            v = *p + d;
            if (v < 0) {
                v = 9;
            }
            if (v >= 0xA) {
                v = 0;
            }
            *p = v;
            e = insect_InsectBattleGetPiece_4f0b90(o, v);
            if (e->f71 == o->f5EF1) {
                ok = 0;
                if (insect_InsectPieceIsInPlay_5149e0(e) != 0) {
                    ok = 1;
                    if (insect_InsectPieceCanAct_514920(e) == 0) {
                        ok = 0;
                    }
                    if (insect_InsectPieceTestStatus_513280(e, 0x1C) != 0) {
                        ok = 0;
                    }
                }
                if (ok != 0) {
                    insect_InsectBoardFindPiece_4ee190(g, e, &x, &y);
                    m = insect_InsectCursorSetFindPage_511e60(o->f4F90, 0xA);
                    insect_InsectCursorSetPageSetCell_511c20(o->f4F90, k, x, y);
                    insect_InsectCursorSetPageSetCell_511c20(o->f4F90, m, x, y);
                    return;
                }
            }
            insect_InsectBattleCursorNextPiece_4f0bd0(o, a1, a2, a3, a4, depth + 1);
        }
    }
}
