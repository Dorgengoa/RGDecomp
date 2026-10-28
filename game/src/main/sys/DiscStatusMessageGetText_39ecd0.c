/* rgp:protos */
#define RGP_SELF_DiscStatusMessageGetText_39ecd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 DiscStatusMessageGetText_39ecd0(void)
{
    return MsgGetTextByIndex_279040(0x2E);
}
