/* rgp:protos */
#define RGP_SELF_EventGlobalObjInit_257930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004BD2D0[];

/*rgp*/

s32 EventGlobalObjInit_257930(void)
{
    return (EventGlobalObjReset_257940(D_004BD2D0), (s32)0);
}
