#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 FileReqSubmit_1827a0(s32, s32, s32, s32, s32);

s32 FileReqSubmitWhole_1829f0(s32 a4, s32 a5, s32 a6)
{
    return FileReqSubmit_1827a0(a4, a5, a6, 0, -1);
}
