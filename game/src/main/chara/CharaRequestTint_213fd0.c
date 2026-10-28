/* rgp:protos */
#define RGP_SELF_CharaRequestTint_213fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaRequestTint_213fd0(void *p4, s32 a5, s32 a6, f32 fa0, f32 fa1, f32 fa2, f32 fa3, float rgp_f4)
{
    return (CharaTintRequest_21f0e0((u8 *)p4 + 0x95C, a5, a6, fa0, fa1, fa2, fa3, (float)rgp_f4), (s32)0);
}
