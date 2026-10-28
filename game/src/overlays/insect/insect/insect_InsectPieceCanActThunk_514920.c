/* rgp:protos */
#define RGP_SELF_insect_InsectPieceCanActThunk_514920 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514900 -- 8 bytes, 2 instructions.  A pure tail jump to
 * insect_InsectPieceCanAct_514920 with the argument registers untouched, so the C is a
 * void->void forwarding call and mwcc turns it into `j`. */

/*rgp*/

int insect_InsectPieceCanActThunk_514920(void *rgp_a0)
{
    return insect_InsectPieceCanAct_514920((void *)rgp_a0);
}
