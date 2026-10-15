#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 CharaSysSetFlag4Bit1Maybe_3a5320(s32, s32);

s32 CharaSysFlag4Bit1SetArg0Related_3a5310(s32 a4)
{
    return CharaSysSetFlag4Bit1Maybe_3a5320(a4, 0);
}
