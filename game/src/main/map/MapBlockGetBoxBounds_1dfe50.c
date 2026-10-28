/* rgp:protos */
#define RGP_SELF_MapBlockGetBoxBounds_1dfe50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockGetBoxBounds_1dfe50(void *p4, int rgp_a1, int rgp_a2)
{
    return (AreaBoxGetBoundsThunk_1e97b0((u8 *)p4 + 0x74, (int)rgp_a1, (int)rgp_a2), (s32)0);
}
