/* rgp:protos */
#define RGP_SELF_MapBlockIdListClear_1e32e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockIdListClear_1e32e0(void *p4)
{
    return (MapIdListClearThunk_1e5ac0((u8 *)p4 + 0x21F8), (s32)0);
}
