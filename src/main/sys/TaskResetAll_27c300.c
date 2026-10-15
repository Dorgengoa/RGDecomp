#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

extern s32 TaskTableResetEntries_1f5660(void *);

s32 TaskResetAll_27c300(void)
{
    return TaskTableResetEntries_1f5660(D_004D7FA0);
}
