#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapRecTableOwnsShare_1dd210(void *, s32);

s32 MapAreaOwnsShare_1dce40(void *p4, s32 a5)
{
    return MapRecTableOwnsShare_1dd210((u8 *)p4 + 0x54, a5);
}
