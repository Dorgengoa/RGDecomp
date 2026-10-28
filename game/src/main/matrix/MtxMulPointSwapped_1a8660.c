/* rgp:protos */
#define RGP_SELF_MtxMulPointSwapped_1a8660 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MtxMulPointSwapped_1a8660(s32 a4, s32 a5, void *rgp_a2)
{
    return (MtxMulPoint_13c890(a5, a4, (void *)rgp_a2), (s32)0);
}
