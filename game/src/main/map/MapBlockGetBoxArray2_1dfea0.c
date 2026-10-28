/* rgp:protos */
#define RGP_SELF_MapBlockGetBoxArray2_1dfea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapBlockGetBoxArray2_1dfea0(void *p4)
{
    return MapBlockBoxListGetArray2_1e02d0((u8 *)p4 + 0x54);
}
