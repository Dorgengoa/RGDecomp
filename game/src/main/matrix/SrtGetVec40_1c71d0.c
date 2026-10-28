/* rgp:protos */
#define RGP_SELF_SrtGetVec40_1c71d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 SrtGetVec40_1c71d0(void *p4, s32 a5)
{
    return (VecCopyAsDir_1cbe20(a5, (u8 *)p4 + 0x40), (s32)0);
}
