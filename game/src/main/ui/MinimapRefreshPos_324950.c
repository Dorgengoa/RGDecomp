/* rgp:protos */
#define RGP_SELF_MinimapRefreshPos_324950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MinimapRefreshPos_324950(void *p4)
{
    return MinimapScrollToClamped_324530(p4, (u8 *)p4 + 0x30, 1, 0);
}
