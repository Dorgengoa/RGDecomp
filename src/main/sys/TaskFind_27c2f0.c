#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

extern s32 TaskTableFindByName_1f55d0(void *, s32);

s32 TaskFind_27c2f0(s32 a4)
{
    return TaskTableFindByName_1f55d0(D_004D7FA0, a4);
}
