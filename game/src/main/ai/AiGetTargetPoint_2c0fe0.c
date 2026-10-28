/* rgp:protos */
#define RGP_SELF_AiGetTargetPoint_2c0fe0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 AiGetTargetPoint_2c0fe0(void *p4, s32 a5)
{
    return (VecCopyAsPoint_1cbe10(a5, (u8 *)p4 + 0x1B0), (s32)0);
}
