#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockInit_178490(void *);

s32 ScreenFadeInit_1cf770(void *p4)
{
    return ScreenFadeBlockInit_178490((u8 *)p4 + 0x5980);
}
