/* rgp:protos */
#define RGP_SELF_MapShareIdListClear_1e32f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapShareIdListClear_1e32f0(void *p4)
{
    return (MapIdListClearThunk_1e5ac0((u8 *)p4 + 0x2154), (s32)0);
}
