#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SrtSetPosFromVec_1c7410(void *);

s32 CharaSetPosVec_2387e0(void *p4)
{
    return SrtSetPosFromVec_1c7410((u8 *)p4 + 0x50);
}
