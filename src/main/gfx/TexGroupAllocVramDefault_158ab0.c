#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 TexGroupAllocVram_157e70(s32, s32, s32);

s32 TexGroupAllocVramDefault_158ab0(s32 a4, s32 a5)
{
    return TexGroupAllocVram_157e70(a4, a5, 0);
}
