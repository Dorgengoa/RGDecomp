/* rgp:protos */
#define RGP_SELF_GsPktSetAlphaTestFunc_13e4c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GsPktSetAlphaTestFunc_13e4c0(void *p4, s32 a5, s32 a6)
{
    return (GsTestSetAlphaFunc_1570c0((u8 *)p4 + 0x10, a5, a6), (s32)0);
}
