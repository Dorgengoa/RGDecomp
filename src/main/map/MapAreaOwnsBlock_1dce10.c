#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableOwnsBlock_1dd1b0(void *, s32);

s32 MapAreaOwnsBlock_1dce10(void *p4, s32 a5)
{
    return MapRecTableOwnsBlock_1dd1b0((u8 *)p4 + 0x54, a5);
}
