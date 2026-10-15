#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 StrCopyBounded_42cad0(s32, s32, s32);

s32 UskStackSetName_42e3b0(s32 a4, s32 a5)
{
    return StrCopyBounded_42cad0(a4, a5, 0x20);
}
