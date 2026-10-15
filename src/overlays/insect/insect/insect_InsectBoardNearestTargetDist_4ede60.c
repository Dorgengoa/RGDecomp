#include "types.h"
/* insect 0x004EDE60 -- 168 bytes.  Manhattan distance between two board
 * entities: the two out-parameter pairs sit at $29+0x4C/0x48 and 0x44/0x40,
 * i.e. FOUR bytes apart, so they are WORD locals (see the ixa05 spacing rule),
 * and stack locals are allocated in REVERSE declaration order.
 * Both guards are `if (x == 0) return 0;` -- mwcc inverts the test and puts
 * the `b <epilogue>` / `daddu $2,$0,$0` pair at the TOP. */

extern s32  insect_InsectBoardFindNearestTarget_4ee000(void);
extern void insect_InsectBoardFindPiece_4ee190(s32 t, s32 e, s32 *x, s32 *y);
extern s32  func_12DE98(s32 v);

s32 insect_InsectBoardNearestTargetDist_4ede60(s32 t, s32 a)
{
    s32 ax;
    s32 ay;
    s32 bx;
    s32 by;
    s32 b;
    s32 d;

    if (a == 0) {
        return 0;
    }
    b = insect_InsectBoardFindNearestTarget_4ee000();
    if (b == 0) {
        return 0;
    }
    insect_InsectBoardFindPiece_4ee190(t, a, &ax, &ay);
    insect_InsectBoardFindPiece_4ee190(t, b, &bx, &by);
    d = func_12DE98(bx - ax);
    return d + func_12DE98(by - ay);
}
