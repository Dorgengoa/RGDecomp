/* rgp:protos */
#define RGP_SELF_insect_InsectBattleGetPiece_4f0b90 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"
/* insect 0x004F0B90 -- 56 B / 14 words, LANE L1 arming unit.
 *
 * 14 instructions, no frame, a sibling `j insect_InsectTeamGetPiece_5138d0`.  The callee
 * (read its own 8-word listing) is a pure indexer: it returns
 * $4 + 488*$5, so this function returns a POINTER too.
 *
 * TWO divides by the same literal 5 but only ONE `break 0,7`:
 *   div/mflo  = the `/` and it carries the bnez/break pair,
 *   div/mfhi  = the `%` and it does NOT.
 * That is the rule this lane was sent to measure, so the source is the plain
 * two-expression spelling `i / 5` and `i % 5`, not one divide reused. */

/*rgp*/

void *insect_InsectBattleGetPiece_4f0b90(void *a, s32 i)
{
    return insect_InsectTeamGetPiece_5138d0((u8 *)a + (i / 5) * 0x994 + 0x35F8, i % 5);
}
