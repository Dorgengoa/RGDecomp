#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 VecCopyAsDir_1cbe20(void *);

s32 SrtSetVec40FromVec_1c71b0(void *p4)
{
    return VecCopyAsDir_1cbe20((u8 *)p4 + 0x40);
}
