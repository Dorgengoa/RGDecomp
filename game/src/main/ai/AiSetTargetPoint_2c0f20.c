/* rgp:protos */
#define RGP_SELF_AiSetTargetPoint_2c0f20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 AiSetTargetPoint_2c0f20(void *p4, void *rgp_a1)
{
    return (VecCopyAsPoint_1cbe10((u8 *)p4 + 0x1B0, (void *)rgp_a1), (s32)0);
}
