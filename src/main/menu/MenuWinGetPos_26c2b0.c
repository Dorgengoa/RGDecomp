#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 sceVu0CopyVector(s32, void *);

s32 MenuWinGetPos_26c2b0(void *p4, s32 a5)
{
    return sceVu0CopyVector(a5, (u8 *)p4 + 0x40);
}
