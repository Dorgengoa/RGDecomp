/* rgp:protos */
#define RGP_SELF_insect_InsectPieceIsKing_514b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x514B00 -- 8 B / 2 words.  `j insect_InsectPieceTestStatus_513280` with
 * `addiu $5, $0, 0x1A` in the delay slot: a TAIL CALL, so the wrapper's return
 * type has to agree with the callee's (s32, settled in insect_InsectBattleMenuFirstTurnSelect_4fb1a0.c). */

/*rgp*/

s32 insect_InsectPieceIsKing_514b00(void *e)
{
    return insect_InsectPieceTestStatus_513280(e, 0x1A);
}
