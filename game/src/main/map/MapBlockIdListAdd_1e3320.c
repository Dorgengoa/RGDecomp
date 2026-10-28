/* rgp:protos */
#define RGP_SELF_MapBlockIdListAdd_1e3320 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockIdListAdd_1e3320(void *p4, s32 a5)
{
    return (MapIdListAddChecked_1e3280(p4, (u8 *)p4 + 0x21F8, a5), (s32)0);
}
