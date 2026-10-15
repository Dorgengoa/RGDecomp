#include "types.h"
/* insect 0x004ED140 -- 56 bytes, 14 instructions.  A pure forwarder; the two
 * -1 arguments are CSEd into one `addiu` plus a `daddu`.
 */

extern s32 insect_InsectBoardGetPiece_4ee9a0(void *);
extern void insect_InsectBoardMarkAdjacentTargets_4ecf80(void *, s32, s32, s32);

void insect_InsectBoardMarkAdjacentTargetsAt_4ed140(void *o)
{
    insect_InsectBoardMarkAdjacentTargets_4ecf80(o, insect_InsectBoardGetPiece_4ee9a0(o), -1, -1);
}
