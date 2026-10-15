#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockSetCaptureObj_177f70(void *, s32, s32);

s32 ScreenFadeSetCaptureObj_1cf650(void *p4, s32 a5, s32 a6)
{
    return ScreenFadeBlockSetCaptureObj_177f70((u8 *)p4 + 0x5980, a5, a6);
}
