#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapGetAreaSlot_1e5770(s32, s32);

s32 MapGetAreaSlot1_1e5750(s32 a4)
{
    return MapGetAreaSlot_1e5770(a4, 1);
}
