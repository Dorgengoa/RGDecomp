#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecCopy_1cbe30(void *, s32);

s32 NavGraphSetGoalPos_311630(void *p4, s32 a5)
{
    return VecCopy_1cbe30((u8 *)p4 + 0x80, a5);
}
