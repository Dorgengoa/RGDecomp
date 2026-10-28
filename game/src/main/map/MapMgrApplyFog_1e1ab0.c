/* rgp:protos */
#define RGP_SELF_MapMgrApplyFog_1e1ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapMgrApplyFog_1e1ab0(void *p4)
{
    return (MapEnvApplyFog_1e5ba0((u8 *)p4 + 0x68), (s32)0);
}
