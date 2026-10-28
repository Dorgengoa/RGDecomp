/* rgp:protos */
#define RGP_SELF_XformPairSumRot_19a1b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 XformPairSumRot_19a1b0(void *p4, s32 a5)
{
    return (VecAdd_13be20(a5, (u8 *)p4 + 0x20, (u8 *)p4 + 0x70), (s32)0);
}
