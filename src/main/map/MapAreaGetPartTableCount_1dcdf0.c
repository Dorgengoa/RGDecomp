#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableGetPartTableCount_1dd540(void *);

s32 MapAreaGetPartTableCount_1dcdf0(void *p4)
{
    return MapRecTableGetPartTableCount_1dd540((u8 *)p4 + 0x54);
}
