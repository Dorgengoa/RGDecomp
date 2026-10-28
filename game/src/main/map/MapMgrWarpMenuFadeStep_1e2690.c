/* rgp:protos */
#define RGP_SELF_MapMgrWarpMenuFadeStep_1e2690 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapMgrWarpMenuFadeStep_1e2690(void *p4)
{
    return (WarpMenuFadeStep_39dab0((u8 *)p4 + 0x18B0), (s32)0);
}
