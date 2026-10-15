#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

extern s32 TaskTableEntryAt_1f55b0(void *, s32);

s32 TaskTableGetEntry_27c2e0(s32 a4)
{
    return TaskTableEntryAt_1f55b0(D_004D7FA0, a4);
}
