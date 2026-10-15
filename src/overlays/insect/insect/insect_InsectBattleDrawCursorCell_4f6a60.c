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

extern s32  func_141B00(s32 a);
extern s32  insect_InsectBoardIsHole_4ee7e0(void *g, s8 col, s8 row);
extern s32  insect_InsectBoardGetPiece_4ee9a0(void *g, s8 col, s8 row);
extern void insect_InsectBattleCellPrimEnd_4f6d20(Ins *o, s32 a, s32 h);
extern void insect_InsectBattleDrawCellQuad_4f6d30(Ins *o, s32 h, s32 flag, f32 x, f32 y, f32 t, f32 s);
extern void insect_InsectBattleCellPrimSetup_4f7400(Ins *o, s32 h, s32 k);

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
    h = func_141B00(a);
    col = c->f8;
    row = c->f9;
    if (insect_InsectBoardGetPiece_4ee9a0(g, col, row) != 0 || insect_InsectBoardIsHole_4ee7e0(g, col, row) != 0) {
        flag = 0;
        k = 2;
    }
    insect_InsectBattleCellPrimSetup_4f7400(o, h, k);
    insect_InsectBattleDrawCellQuad_4f6d30(o, h, flag, (f32)col, (f32)row, t, 1.0f);
    insect_InsectBattleCellPrimEnd_4f6d20(o, a, h);
}
