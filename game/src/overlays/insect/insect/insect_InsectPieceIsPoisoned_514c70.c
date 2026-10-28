/* rgp:protos */
#define RGP_SELF_insect_InsectPieceIsPoisoned_514c70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514C70 -- 32 bytes.  A one-line predicate wrapper: the key is
 * the literal 0 in $5 and `sltu $2,$0,$2`, i.e. `!= 0`. */

/*rgp*/

s32 insect_InsectPieceIsPoisoned_514c70(void *e)
{
    return insect_InsectPieceTestStatus_513280(e, 0) != 0;
}
