#include "types.h"
/* insect 0x004ED4A0 -- 12 instructions.  One call feeding another; the
 * argument is held in $16 across the inner call. */

extern s32 insect_InsectBoardGetPiece_4ee9a0(s32 a);
extern void insect_InsectBoardCalcMoveRange_4ed180(s32 a, s32 b);

void insect_InsectBoardCalcMoveRangeAt_4ed4a0(s32 a)
{
    insect_InsectBoardCalcMoveRange_4ed180(a, insect_InsectBoardGetPiece_4ee9a0(a));
}
