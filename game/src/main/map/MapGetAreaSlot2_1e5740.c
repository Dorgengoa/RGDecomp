/* rgp:protos */
#define RGP_SELF_MapGetAreaSlot2_1e5740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapGetAreaSlot2_1e5740(s32 a4)
{
    return ((s32)MapGetAreaSlot_1e5770(a4, 2));
}
