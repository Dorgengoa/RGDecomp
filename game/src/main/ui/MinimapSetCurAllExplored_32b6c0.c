/* rgp:protos */
#define RGP_SELF_MinimapSetCurAllExplored_32b6c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MinimapSetCurAllExplored_32b6c0(s32 a4)
{
    return (MinimapSetAllExplored_32b6d0(a4, 0), (s32)0);
}
