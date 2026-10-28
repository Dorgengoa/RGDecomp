/* rgp:protos */
#define RGP_SELF_insect_InsectBoardMarkAdjacentTargetsAt_4ed140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004ED140 -- 56 bytes, 14 instructions.  A pure forwarder; the two
 * -1 arguments are CSEd into one `addiu` plus a `daddu`.
 */

/*rgp*/
/*rgp*/

void insect_InsectBoardMarkAdjacentTargetsAt_4ed140(void *o, short rgp_a1, short rgp_a2)
{
    insect_InsectBoardMarkAdjacentTargets_4ecf80(o, insect_InsectBoardGetPiece_4ee9a0(o, (short)rgp_a1, (short)rgp_a2), -1, -1);
}
