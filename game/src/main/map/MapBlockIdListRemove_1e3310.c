/* rgp:protos */
#define RGP_SELF_MapBlockIdListRemove_1e3310 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockIdListRemove_1e3310(void *p4, s32 a5)
{
    return (MapIdListRemoveChecked_1e3250(p4, (u8 *)p4 + 0x21F8, a5), (s32)0);
}
