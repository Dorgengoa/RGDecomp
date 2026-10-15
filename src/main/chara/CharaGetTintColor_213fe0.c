#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 CharaTintGetColor_21f1b0(void *, s32);

s32 CharaGetTintColor_213fe0(void *p4, s32 a5)
{
    return CharaTintGetColor_21f1b0((u8 *)p4 + 0x95C, a5);
}
