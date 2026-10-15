#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapBlockBoxListGetCount1_1e0380(void *);

s32 MapBlockGetBoxCount1_1dfeb0(void *p4)
{
    return MapBlockBoxListGetCount1_1e0380((u8 *)p4 + 0x54);
}
