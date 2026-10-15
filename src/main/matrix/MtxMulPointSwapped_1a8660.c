#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MtxMulPoint_13c890(s32, s32);

s32 MtxMulPointSwapped_1a8660(s32 a4, s32 a5)
{
    return MtxMulPoint_13c890(a5, a4);
}
