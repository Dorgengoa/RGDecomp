/* rgp:protos */
#define RGP_SELF_MapAreaGetShares_1dce60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapAreaGetShares_1dce60(void *p4)
{
    return MapRecTableGetShares_1dd5a0((u8 *)p4 + 0x54);
}
