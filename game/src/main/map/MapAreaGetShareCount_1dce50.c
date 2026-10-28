/* rgp:protos */
#define RGP_SELF_MapAreaGetShareCount_1dce50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 MapAreaGetShareCount_1dce50(void *p4)
{
    return ((short)MapRecTableGetShareCount_1dd560((u8 *)p4 + 0x54));
}
