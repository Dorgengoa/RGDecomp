#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockDraw_177540(void *);

s32 ScreenFadeDraw_1cf6d0(void *p4)
{
    return ScreenFadeBlockDraw_177540((u8 *)p4 + 0x5980);
}
