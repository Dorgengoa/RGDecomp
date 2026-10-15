#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetShares_1dd5a0(void *);

s32 MapAreaGetShares_1dce60(void *p4)
{
    return MapRecTableGetShares_1dd5a0((u8 *)p4 + 0x54);
}
