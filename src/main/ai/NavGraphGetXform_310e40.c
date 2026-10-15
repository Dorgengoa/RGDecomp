#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MtxCopy_1cbde0(s32, s32);

s32 NavGraphGetXform_310e40(s32 a4, s32 a5)
{
    return MtxCopy_1cbde0(a5, a4);
}
