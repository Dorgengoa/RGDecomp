#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecAdd_13be20(s32, void *, void *);

s32 XformPairSumUvOffset_19a150(void *p4, s32 a5)
{
    return VecAdd_13be20(a5, (u8 *)p4 + 0x50, (u8 *)p4 + 0xA0);
}
