#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetBlockCount_1dd550(void *);

s32 MapAreaGetBlockCount_1dce20(void *p4)
{
    return MapRecTableGetBlockCount_1dd550((u8 *)p4 + 0x54);
}
