/* rgp:protos */
#define RGP_SELF_XformPairMulColor_19a170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 XformPairMulColor_19a170(void *p4, s32 a5)
{
    return (VecMul_13bd40(a5, (u8 *)p4 + 0x40, (u8 *)p4 + 0x90), (s32)0);
}
