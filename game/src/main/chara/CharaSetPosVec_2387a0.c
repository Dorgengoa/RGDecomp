/* rgp:protos */
#define RGP_SELF_CharaSetPosVec_2387a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaSetPosVec_2387a0(void *p4, void *rgp_a1)
{
    return SrtSetPosFromVec_1c7410((u8 *)p4 + 0x50, (void *)rgp_a1);
}
