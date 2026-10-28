/* rgp:protos */
#define RGP_SELF_SrtSetVec40FromVec_1c71b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 SrtSetVec40FromVec_1c71b0(void *p4, void *rgp_a1)
{
    return (VecCopyAsDir_1cbe20((u8 *)p4 + 0x40, (void *)rgp_a1), (s32)0);
}
