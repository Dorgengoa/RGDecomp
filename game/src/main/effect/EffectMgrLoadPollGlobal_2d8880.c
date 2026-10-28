/* rgp:protos */
#define RGP_SELF_EffectMgrLoadPollGlobal_2d8880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004DCD50[];

/*rgp*/

s32 EffectMgrLoadPollGlobal_2d8880(void)
{
    return (EffectMgrLoadPoll_2e3030(D_004DCD50), (s32)0);
}
