#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 StrEqualNonNull_1ca6c0(void *, s32);

s32 CharaIsPlayedMotion_2124f0(void *p4, s32 a5)
{
    return StrEqualNonNull_1ca6c0((u8 *)p4 + 0xA8C, a5);
}
