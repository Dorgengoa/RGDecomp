/* rgp:protos */
#define RGP_SELF_HandleEntriesReleaseAll_3f14a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 HandleEntriesReleaseAll_3f14a0(s32 a4)
{
    return HandleEntriesReleaseExcept_3f0aa0(a4, -1);
}
