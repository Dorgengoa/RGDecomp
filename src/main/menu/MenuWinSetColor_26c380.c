#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 sceVu0CopyVector(void *, s32);

s32 MenuWinSetColor_26c380(void *p4, s32 a5)
{
    return sceVu0CopyVector((u8 *)p4 + 0x50, a5);
}
