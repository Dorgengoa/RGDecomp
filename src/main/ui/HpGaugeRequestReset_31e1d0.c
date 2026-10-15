#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 HpGaugeSetMode_31e2d0(s32, s32);

s32 HpGaugeRequestReset_31e1d0(s32 a4)
{
    return HpGaugeSetMode_31e2d0(a4, 0);
}
