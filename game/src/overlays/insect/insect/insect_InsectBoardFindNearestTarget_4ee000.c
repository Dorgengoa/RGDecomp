/* rgp:protos */
#define RGP_SELF_insect_InsectBoardFindNearestTarget_4ee000 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EE000 -- 400 bytes, 100 instructions.
 * A 5x7 grid scan picking the cell nearest the anchor returned through the
 * two out-parameters of insect_InsectBoardFindPiece_4ee190. */

typedef struct Obj Obj;
typedef struct Cell Cell;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 abs(s32 v);

Cell *insect_InsectBoardFindNearestTarget_4ee000(Obj *o, Cell *p, u8 flag)
{
    s32 cx;
    s32 cy;
    s32 bx;
    s32 by;
    Cell *best;
    s32 j;
    s32 i;
    s32 ok;
    s32 d;
    Cell *c;

    by = 0;
    bx = 0;
    insect_InsectBoardFindPiece_4ee190(o, p, &cx, &cy);
    best = 0;
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 5; i++) {
            ok = 1;
            c = ((Cell *)insect_InsectBoardGetPiece_4ee9a0(o, i, j));
            if (c != 0) {
                if (flag != 0) {
                    if (insect_InsectPieceIsEnemyOf_5149b0(p, c) == 0) {
                        ok = 0;
                    }
                }
                if (c == p) {
                    ok = 0;
                }
                if (ok != 0) {
                    if (best != 0) {
                        d = abs((i - cx) + (j - cy));
                        if (d <= abs((bx - cx) + (by - cy))) {
                            if (insect_InsectPieceIsInPlay_5149e0(c) != 0) {
                                best = c;
                            }
                        }
                    } else {
                        if (insect_InsectPieceIsInPlay_5149e0(c) != 0) {
                            best = c;
                            bx = i;
                            by = j;
                        }
                    }
                }
            }
        }
    }
    return best;
}
