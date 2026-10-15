#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecAdd_13be20(void *, void *, s32);

s32 XformPairAddPos_19a1f0(void *p4, s32 a5)
{
    return VecAdd_13be20((u8 *)p4 + 0x10, (u8 *)p4 + 0x10, a5);
}
