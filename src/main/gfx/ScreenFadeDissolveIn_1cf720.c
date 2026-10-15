#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockDissolveIn_178220(void *, s32, f32);

s32 ScreenFadeDissolveIn_1cf720(void *p4, s32 a5, f32 fa0)
{
    return ScreenFadeBlockDissolveIn_178220((u8 *)p4 + 0x5980, a5, fa0);
}
