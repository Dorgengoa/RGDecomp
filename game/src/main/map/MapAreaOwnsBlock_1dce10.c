/* rgp:protos */
#define RGP_SELF_MapAreaOwnsBlock_1dce10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapAreaOwnsBlock_1dce10(void *p4, s32 a5)
{
    return MapRecTableOwnsBlock_1dd1b0((u8 *)p4 + 0x54, a5);
}
