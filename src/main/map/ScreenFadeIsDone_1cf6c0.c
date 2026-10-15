#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockIsDone_178110(void *);

s32 ScreenFadeIsDone_1cf6c0(void *p4)
{
    return ScreenFadeBlockIsDone_178110((u8 *)p4 + 0x5980);
}
