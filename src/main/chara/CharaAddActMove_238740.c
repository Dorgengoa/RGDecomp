#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecAdd_1cbdc0(void *, void *, s32);

s32 CharaAddActMove_238740(void *p4, s32 a5)
{
    return VecAdd_1cbdc0((u8 *)p4 + 0xB0, (u8 *)p4 + 0xB0, a5);
}
