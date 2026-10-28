/* rgp:protos */
#define RGP_SELF_insect_InsectBoardPickMoveCell_4edd90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EDD90 -- 200 bytes, 50 instructions.  Six parameters; the last
 * two integer out-parameters are handed straight through to the helper on the
 * first call and only re-derived through the stack pair on the second.
 *
 * The `bnel $2, $0, .L004EDE18` carries `lw $6, 0x7C($29)` -- the TARGET
 * block's first instruction -- so the target block is the `else` arm
 * (insect-dispatch-branch-polarity / the annulled-delay-slot rule).
 */

/*rgp*/
/*rgp*/
/*rgp*/


void insect_InsectBoardPickMoveCell_4edd90(void *a, void *b, void *c, s32 *px, s32 *py, s32 k)
{
    s32 x;
    s32 y;

    if (b != 0) {
        insect_InsectBoardFindPiece_4ee190(a, b, px, py);
        if (c != 0) {
            insect_InsectBoardFindPiece_4ee190(a, c, &x, &y);
            if (insect_InsectPieceIsInPlay_5149e0(c) == 0) {
                *px = x;
                *py = y;
            } else {
                insect_InsectBoardPickMoveCellByDist_4edb80(a, b, x, y, px, py, k);
            }
        }
    }
}
