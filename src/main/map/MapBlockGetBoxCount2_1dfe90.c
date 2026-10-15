#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapBlockBoxListGetCount2_1e02c0(void *);

s32 MapBlockGetBoxCount2_1dfe90(void *p4)
{
    return MapBlockBoxListGetCount2_1e02c0((u8 *)p4 + 0x54);
}
