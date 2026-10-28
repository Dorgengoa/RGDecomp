/* rgp:protos */
#define RGP_SELF_insect_InsectSeqExecNone_51b6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0051B6F0 -- 32 bytes.  `sltu $2, $0, $2` on the callee's result is
 * the `!= 0` normalisation, i.e. the return is a boolean. */
/*rgp*/

s32 insect_InsectSeqExecNone_51b6f0(void)
{
    return InsectBattleGet_31a8d0() != 0;
}
