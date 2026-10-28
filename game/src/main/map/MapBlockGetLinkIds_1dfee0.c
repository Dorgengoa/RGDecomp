/* rgp:protos */
#define RGP_SELF_MapBlockGetLinkIds_1dfee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockGetLinkIds_1dfee0(void *p4)
{
    return MapBlockBoxListGetLinkIds_1e03b0((u8 *)p4 + 0x54);
}
