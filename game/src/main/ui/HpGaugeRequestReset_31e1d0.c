/* rgp:protos */
#define RGP_SELF_HpGaugeRequestReset_31e1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 HpGaugeRequestReset_31e1d0(s32 a4)
{
    return (HpGaugeSetMode_31e2d0(a4, 0), (s32)0);
}
