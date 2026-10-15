#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 CharaTintRequest_21f0e0(void *, s32, s32, f32, f32, f32, f32);

s32 CharaRequestTint_213fd0(void *p4, s32 a5, s32 a6, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    return CharaTintRequest_21f0e0((u8 *)p4 + 0x95C, a5, a6, fa0, fa1, fa2, fa3);
}
