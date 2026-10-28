/* rgp:protos */
#define RGP_SELF_CharaSetSrtVec40_2387c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 CharaSetSrtVec40_2387c0(void *p4, f32 fa0, f32 fa1, f32 fa2)
{
    return (SrtSetVec40_1c7170((u8 *)p4 + 0x50, fa0, fa1, fa2), (s32)0);
}
