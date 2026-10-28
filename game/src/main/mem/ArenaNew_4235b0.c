/* rgp:protos */
#define RGP_SELF_ArenaNew_4235b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 ArenaNew_4235b0(s32 a4, s32 a5, s32 a6, s32 a7)
{
    return ArenaAllocAligned_370330(a5, a4, a6, a7);
}
