/* rgp:protos */
#define RGP_SELF_MapAreaIdListClear_1e3300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapAreaIdListClear_1e3300(void *p4)
{
    return (MapIdListClearThunk_1e5ac0((u8 *)p4 + 0x20B0), (s32)0);
}
