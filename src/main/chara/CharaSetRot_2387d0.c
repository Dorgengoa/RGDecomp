#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SrtSetRot_1c73d0(void *, f32, f32, f32);

s32 CharaSetRot_2387d0(void *p4, f32 fa0, f32 fa1, f32 fa2)
{
    return SrtSetRot_1c73d0((u8 *)p4 + 0x50, fa0, fa1, fa2);
}
