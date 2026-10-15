#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SrtSetVelocityFromVec_1c71c0(void *);

s32 CharaSetVelocityFromVec_238790(void *p4)
{
    return SrtSetVelocityFromVec_1c71c0((u8 *)p4 + 0x50);
}
