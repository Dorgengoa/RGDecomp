#include "types.h"
/* insect 0x004EDF10 -- 60 instructions.  Picks whichever of the two candidate
 * objects is the shorter Manhattan distance from the reference.  The six
 * out-slots occupy 0x6C..0x58 and stack locals are laid out in REVERSE
 * declaration order, so they are declared high address first.  The trailing
 * `beql` into the next instruction is the `>=` arm of the select, which two
 * of the three `<` spellings reach and the `r = b; if (db >= da) r = a;`
 * accumulator spelling does NOT (one word long, GPR compare not `$at`). */

extern void insect_InsectBoardFindPiece_4ee190(void *ctx, void *obj, s32 *x, s32 *y);
extern s32 func_12DE98(s32 v);

void *insect_InsectBoardPickNearer_4edf10(void *ctx, void *ref, void *a, void *b)
{
    s32 rx;
    s32 ry;
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    s32 da;
    s32 db;

    if (ref == 0 || a == 0 || b == 0) {
        return 0;
    }
    insect_InsectBoardFindPiece_4ee190(ctx, ref, &rx, &ry);
    insect_InsectBoardFindPiece_4ee190(ctx, a, &ax, &ay);
    insect_InsectBoardFindPiece_4ee190(ctx, b, &bx, &by);
    da = func_12DE98(rx - ax) + func_12DE98(ry - ay);
    db = func_12DE98(rx - bx) + func_12DE98(ry - by);
    if (db < da) {
        return b;
    }
    return a;
}
