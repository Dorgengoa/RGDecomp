/* rgp:protos */
#define RGP_SELF_insect_InsectBoardNearestTargetDist_4ede60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EDE60 -- 168 bytes.  Manhattan distance between two board
 * entities: the two out-parameter pairs sit at $29+0x4C/0x48 and 0x44/0x40,
 * i.e. FOUR bytes apart, so they are WORD locals (see the ixa05 spacing rule),
 * and stack locals are allocated in REVERSE declaration order.
 * Both guards are `if (x == 0) return 0;` -- mwcc inverts the test and puts
 * the `b <epilogue>` / `daddu $2,$0,$0` pair at the TOP. */

/*rgp*/
/*rgp*/
extern s32  abs(s32 v);

s32 insect_InsectBoardNearestTargetDist_4ede60(s32 t, s32 a, unsigned char rgp_a2)
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
    b = ((s32)insect_InsectBoardFindNearestTarget_4ee000((void *)t, (void *)a, (unsigned char)rgp_a2));
    if (b == 0) {
        return 0;
    }
    insect_InsectBoardFindPiece_4ee190(t, a, &ax, &ay);
    insect_InsectBoardFindPiece_4ee190(t, b, &bx, &by);
    d = abs(bx - ax);
    return d + abs(by - ay);
}
