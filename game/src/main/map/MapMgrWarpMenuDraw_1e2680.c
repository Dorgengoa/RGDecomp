/* rgp:protos */
#define RGP_SELF_MapMgrWarpMenuDraw_1e2680 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapMgrWarpMenuDraw_1e2680(void *p4)
{
    return (WarpMenuDrawIconsMaybe_39d400((u8 *)p4 + 0x18B0), (s32)0);
}
