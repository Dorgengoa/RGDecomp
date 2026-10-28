/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecSyakuDrill_518f10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00518F10 -- 272 bytes.  Locates two actors on the grid and walks
 * the first one one cell toward the second along the y axis.  The parameter
 * is REUSED for the first actor and the system handle for the grid, which is
 * what puts the actor in $16 and the grid in $17. */

typedef struct Actor {
    u8 pad0000[0x71];
    s8 f71;                         /* +0x71 */
} Actor;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/*rgp*/

s32 insect_InsectSeqExecSyakuDrill_518f10(Actor *a)
{
    f32    rx;
    f32    ry;
    f32    rz;
    s32    ax;
    s32    ay;
    s32    bx;
    s32    by;
    Actor *b;
    s32    dir;
    u8    *g;
    u8    *h;

    g = ((u8 *)InsectBattleGet_31a8d0());
    if (a == 0 || g == 0) {
        return 1;
    }
    a = ((Actor *)insect_InsectBattleGetActorSlot_50db40(g, 0));
    b = ((Actor *)insect_InsectBattleGetActorSlot_50db40(g, 1));
    h = g + 0x4960;
    if (a == 0 || b == 0) {
        return 1;
    }
    dir = 1;
    if (a->f71 == 0) {
        dir = -1;
    }
    insect_InsectBoardFindPiece_4ee190(h, a, &ax, &ay);
    insect_InsectBoardFindPiece_4ee190(h, b, &bx, &by);
    insect_InsectBoardCellToWorld_4eda70(h, &rx, &ry, &rz, 0, (f32)bx, (f32)(by - dir));
    insect_InsectPieceMoveTo_5157d0(a, 0, rx, ry, rz, 10.0f);
    return 1;
}
