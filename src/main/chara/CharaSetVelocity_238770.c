#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SrtSetVelocity_1c7190(void *, f32, f32, f32);

s32 CharaSetVelocity_238770(void *p4, f32 fa0, f32 fa1, f32 fa2)
{
    return SrtSetVelocity_1c7190((u8 *)p4 + 0x50, fa0, fa1, fa2);
}
