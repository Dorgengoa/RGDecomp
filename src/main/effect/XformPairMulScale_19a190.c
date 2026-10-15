#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecMul_13bd40(s32, void *, void *);

s32 XformPairMulScale_19a190(void *p4, s32 a5)
{
    return VecMul_13bd40(a5, (u8 *)p4 + 0x30, (u8 *)p4 + 0x80);
}
