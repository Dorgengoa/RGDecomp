#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GameReqQueuePushWarp_1f5af0(s32, s32, s32, s32);

s32 GameReqPushWarp_285ea0(s32 a4, s32 a5, s32 a6, s32 a7)
{
    return GameReqQueuePushWarp_1f5af0(a6, a5, a7, a4);
}
