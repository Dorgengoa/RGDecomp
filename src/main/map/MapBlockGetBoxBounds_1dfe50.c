#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 AreaBoxGetBoundsThunk_1e97b0(void *);

s32 MapBlockGetBoxBounds_1dfe50(void *p4)
{
    return AreaBoxGetBoundsThunk_1e97b0((u8 *)p4 + 0x74);
}
