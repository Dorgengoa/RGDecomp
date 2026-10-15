#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetBoxCount_1dd530(void *);

s32 MapAreaGetBoxCount_1dcdd0(void *p4)
{
    return MapRecTableGetBoxCount_1dd530((u8 *)p4 + 0x54);
}
