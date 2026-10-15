#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockStep_177f90(void *);

s32 ScreenFadeStep_1cf6e0(void *p4)
{
    return ScreenFadeBlockStep_177f90((u8 *)p4 + 0x5980);
}
