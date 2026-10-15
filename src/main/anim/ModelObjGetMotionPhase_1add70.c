#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MotionListGetPhase_171e90(void *);

s32 ModelObjGetMotionPhase_1add70(void *p4)
{
    return MotionListGetPhase_171e90((u8 *)p4 + 0x1F0);
}
