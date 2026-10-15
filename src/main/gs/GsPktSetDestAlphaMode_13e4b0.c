#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GsTestSetDestAlphaMode_157010(void *, s32);

s32 GsPktSetDestAlphaMode_13e4b0(void *p4, s32 a5)
{
    return GsTestSetDestAlphaMode_157010((u8 *)p4 + 0x10, a5);
}
