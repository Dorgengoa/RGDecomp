#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SrtGetRot_1c7440(void *, s32);

s32 CharaGetRot_2388e0(void *p4, s32 a5)
{
    return SrtGetRot_1c7440((u8 *)p4 + 0x50, a5);
}
