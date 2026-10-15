#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 AreaBoxGetBottomYThunk_1e9890(void *);

s32 MapBlockGetBoxBottomY_1dfe60(void *p4)
{
    return AreaBoxGetBottomYThunk_1e9890((u8 *)p4 + 0x74);
}
