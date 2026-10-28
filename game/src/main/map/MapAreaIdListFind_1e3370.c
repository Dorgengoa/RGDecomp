/* rgp:protos */
#define RGP_SELF_MapAreaIdListFind_1e3370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapAreaIdListFind_1e3370(void *p4, s32 a5)
{
    return MapIdListFindChecked_1e32b0(p4, (u8 *)p4 + 0x20B0, a5);
}
