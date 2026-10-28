/* rgp:protos */
#define RGP_SELF_MapBlockGetBoxArray1_1dfec0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockGetBoxArray1_1dfec0(void *p4)
{
    return MapBlockBoxListGetArray1_1e0390((u8 *)p4 + 0x54);
}
