#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecCopy_1cbe30(s32, s32);

s32 MapNodeMoveReqGetPos_2fa8a0(s32 a4, s32 a5)
{
    return VecCopy_1cbe30(a5, a4);
}
