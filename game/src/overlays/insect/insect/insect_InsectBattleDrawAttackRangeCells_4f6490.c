/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawAttackRangeCells_4f6490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F6490 -- 388 bytes, 97 instructions.
 * Redraws every occupied cell of the 5x7 grid at unit brightness, then the
 * selected cell again at half brightness through a fresh handle. */

typedef struct Grid {
    u8  pad00[4];
} Grid;

typedef struct Sub {
    u8  pad00[4];
} Sub;

typedef struct Obj {
    u8   pad0000[0x4960];
    Grid f4960;                     /* +0x4960 */
    u8   pad4964[0x4F90 - 0x4964];
    Sub  f4F90;                     /* +0x4F90 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/
/*rgp*/

void insect_InsectBattleDrawAttackRangeCells_4f6490(Obj *a, void *b)
{
    s32 cx;
    s32 cy;
    Grid *g;
    void *h;
    s32 y;
    s32 x;
    void *h2;

    g = &a->f4960;
    h = DrawListBeginPrim_141b00(b);
    insect_InsectCursorSetGetCell_511a40(&a->f4F90, 0xB, &cx, &cy);
    insect_InsectBattleCellPrimSetup_4f7400(a, h, -1);
    for (y = 0; y < 7; y++) {
        for (x = 0; x < 5; x++) {
            if (insect_InsectBoardIsInAttackRange_4ee850(g, x, y) != 0) {
                if (x != cx || y != cy) {
                    insect_InsectBattleDrawCellQuad_4f6d30(a, h, 3, (f32)x, (f32)y, 0.0f, 1.0f);
                }
            }
        }
    }
    insect_InsectBattleCellPrimEnd_4f6d20(a, b);
    if (insect_InsectBoardIsInAttackRange_4ee850(g, cx, cy) != 0) {
        h2 = DrawListBeginPrim_141b00(b);
        insect_InsectBattleCellPrimSetup_4f7400(a, h2, 2);
        insect_InsectBattleDrawCellQuad_4f6d30(a, h2, 3, (f32)cx, (f32)cy, 0.0f, 0.5f);
        insect_InsectBattleCellPrimEnd_4f6d20(a, b);
    }
}
