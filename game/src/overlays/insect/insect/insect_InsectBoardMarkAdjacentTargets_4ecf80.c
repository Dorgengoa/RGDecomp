/* rgp:protos */
#define RGP_SELF_insect_InsectBoardMarkAdjacentTargets_4ecf80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004ECF80 -- 448 bytes, 112 instructions.
 * Clears the 7x5 mark array at o+0x13B, then re-marks the 3x3 neighbourhood
 * of (x,y) and returns the array. */

typedef struct Cell Cell;

typedef struct Obj {
    u8  pad00[0x13B];
    u8  f13B[7][5];                 /* +0x13B */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

u8 *insect_InsectBoardMarkAdjacentTargets_4ecf80(Obj *o, Cell *p, s16 x, s16 y)
{
    s32 tx;
    s32 ty;
    Cell *c;
    s32 j;
    s32 i;
    s32 dy;
    s32 dx;
    s32 rx;
    s32 ry;

    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            o->f13B[j][i] &= 0xFE;
        }
    }
    if (p == 0) {
        return 0;
    }
    if (x == -1 && y == -1) {
        insect_InsectBoardFindPiece_4ee190(o, p, &tx, &ty);
        x = tx;
        y = ty;
    }
    for (dy = -1; dy <= 1; dy++) {
        ry = y + dy;
        for (dx = -1; dx <= 1; dx++) {
            rx = x + dx;
            if (insect_InsectBoardInBounds_4efac0(o, (long long)(rx), (long long)(ry)) != 0) {
                if (insect_InsectBoardIsHole_4ee7e0(o, rx, ry) == 0) {
                    c = ((Cell *)insect_InsectBoardGetPiece_4ee9a0(o, rx, ry));
                    o->f13B[ry][rx] |= 1;
                    if (c != 0) {
                        if (insect_InsectPieceIsEnemyOf_5149b0(p, c) == 0) {
                            o->f13B[ry][rx] &= 0xFE;
                        }
                    }
                }
            }
        }
    }
    return o->f13B[0];
}
