#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockSetDelay_1780c0(void *, s32);

s32 ScreenFadeSetDelay_1cf6f0(void *p4, s32 a5)
{
    return ScreenFadeBlockSetDelay_1780c0((u8 *)p4 + 0x5980, a5);
}
