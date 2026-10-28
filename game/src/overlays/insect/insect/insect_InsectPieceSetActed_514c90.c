/* rgp:protos */
#define RGP_SELF_insect_InsectPieceSetActed_514c90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514C90 -- 8 B / 2 words.  `j insect_InsectPieceSetStatus_5132d0` with
 * `addiu $5, $0, 0x1C` in the delay slot.  005132D0 returns nothing (its
 * epilogue leaves $2 alone on the 0x29 arm), so this wrapper is void too. */

/*rgp*/

void insect_InsectPieceSetActed_514c90(void *e)
{
    insect_InsectPieceSetStatus_5132d0(e, 0x1C);
}
