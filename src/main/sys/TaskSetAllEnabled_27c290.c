#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

extern s32 TaskTableSetAllEnabled_1f5480(void *, s32);

s32 TaskSetAllEnabled_27c290(s32 a4)
{
    return TaskTableSetAllEnabled_1f5480(D_004D7FA0, a4);
}
