#include "types.h"
/* insect 0x004EC580 -- 416 bytes, 104 instructions.
 *
 * Clears bit 0 of every cell of the 7x5 u8 grid at 0x13B, then walks the grid
 * again setting bit 0 on the cells insect_InsectBoardIsTargetMarked_4ee8c0 accepts.  Returns the
 * grid, or 0 when the entity argument is null.
 */

typedef struct Obj {
    u8  pad0000[0x13B];
    u8  f13B[7][5];                 /* +0x13B */
} Obj;

extern void insect_InsectBoardMarkAdjacentTargets_4ecf80(Obj *o, s32 e, s32 a, s32 b);
extern void insect_InsectBoardCalcMoveRange_4ed180(Obj *o, s32 e);
extern void insect_InsectBoardMovePiece_4ed8f0(Obj *o, s32 x, s32 y, s32 i, s32 j);
extern void insect_InsectBoardRestore_4ed9d0(Obj *o);
extern void insect_InsectBoardBackup_4eda20(Obj *o);
extern void insect_InsectBoardFindPiece_4ee190(Obj *o, s32 e, s32 *px, s32 *py);
extern s32  insect_InsectBoardIsTargetMarked_4ee8c0(Obj *o, s32 i, s32 j);
extern s32  insect_InsectBoardIsMovable_4ee930(Obj *o, s32 i, s32 j);

u8 *insect_InsectBoardMarkReachableTargets_4ec580(Obj *o, s32 e)
{
    s32 x;
    s32 y;
    s32 j;
    s32 i;
    s32 jj;
    s32 ii;
    s32 j1;
    s32 i1;

    for (j1 = 0; j1 < 7; j1++) {
        for (i1 = 0; i1 < 5; i1++) {
            o->f13B[j1][i1] &= 0xFE;
        }
    }
    if (e == 0) {
        return 0;
    }
    insect_InsectBoardFindPiece_4ee190(o, e, &x, &y);
    insect_InsectBoardCalcMoveRange_4ed180(o, e);
    insect_InsectBoardBackup_4eda20(o);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            if (insect_InsectBoardIsMovable_4ee930(o, i, j) != 0) {
                insect_InsectBoardMovePiece_4ed8f0(o, x, y, i, j);
                insect_InsectBoardMarkAdjacentTargets_4ecf80(o, e, -1, -1);
                for (jj = 0; jj < 7; jj++) {
                    for (ii = 0; ii < 5; ii++) {
                        if (insect_InsectBoardIsTargetMarked_4ee8c0(o, ii, jj) != 0) {
                            o->f13B[jj][ii] |= 1;
                        }
                    }
                }
            }
            insect_InsectBoardRestore_4ed9d0(o);
        }
    }
    return o->f13B[0];
}
