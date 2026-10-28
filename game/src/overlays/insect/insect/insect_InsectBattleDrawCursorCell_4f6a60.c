/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawCursorCell_4f6a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F6A60 -- 276 bytes, 69 instructions, 6 calls, 2 conditional
 * branches.  Two board queries joined by `||`: the first `bnel` jumps INTO the
 * shared tail with the flag cleared in its delay slot, the second `beql` jumps
 * PAST it with the -1 default in ITS delay slot, which is the short-circuit
 * shape ([[factory-or-join-folds-the-return]]).
 */

typedef struct Cell {
    u8 pad00[8];
    s8 f8;                          /* +0x8 */
    s8 f9;                          /* +0x9 */
} Cell;

typedef struct Ins Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleDrawCursorCell_4f6a60(Ins *o, s32 a, Cell *c, f32 t)
{
    s32 flag;
    s32 k;
    s8  col;
    s8  row;
    s32 h;
    void *g;

    k = -1;
    flag = 1;
    g = (u8 *)o + 0x4960;
    h = ((s32)DrawListBeginPrim_141b00(a));
    col = c->f8;
    row = c->f9;
    if (insect_InsectBoardGetPiece_4ee9a0(g, col, row) != 0 || insect_InsectBoardIsHole_4ee7e0(g, col, row) != 0) {
        flag = 0;
        k = 2;
    }
    insect_InsectBattleCellPrimSetup_4f7400(o, h, k);
    insect_InsectBattleDrawCellQuad_4f6d30(o, h, flag, (f32)col, (f32)row, t, 1.0f);
    insect_InsectBattleCellPrimEnd_4f6d20(o, a);
}
