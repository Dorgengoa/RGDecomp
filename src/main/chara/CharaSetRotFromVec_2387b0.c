#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SrtSetRotFromVec_1c7420(void *);

s32 CharaSetRotFromVec_2387b0(void *p4)
{
    return SrtSetRotFromVec_1c7420((u8 *)p4 + 0x50);
}
