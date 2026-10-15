#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockGetColor_1780e0(void *, s32);

s32 ScreenFadeGetColor_1cf660(void *p4, s32 a5)
{
    return ScreenFadeBlockGetColor_1780e0((u8 *)p4 + 0x5980, a5);
}
