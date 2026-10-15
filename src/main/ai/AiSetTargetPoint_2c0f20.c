#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecCopyAsPoint_1cbe10(void *);

s32 AiSetTargetPoint_2c0f20(void *p4)
{
    return VecCopyAsPoint_1cbe10((u8 *)p4 + 0x1B0);
}
