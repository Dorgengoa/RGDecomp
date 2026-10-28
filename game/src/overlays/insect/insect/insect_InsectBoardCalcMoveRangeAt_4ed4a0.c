/* rgp:protos */
#define RGP_SELF_insect_InsectBoardCalcMoveRangeAt_4ed4a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004ED4A0 -- 12 instructions.  One call feeding another; the
 * argument is held in $16 across the inner call. */

/*rgp*/
/*rgp*/

void insect_InsectBoardCalcMoveRangeAt_4ed4a0(s32 a, short rgp_a1, short rgp_a2)
{
    insect_InsectBoardCalcMoveRange_4ed180(a, insect_InsectBoardGetPiece_4ee9a0(a, (short)rgp_a1, (short)rgp_a2));
}
