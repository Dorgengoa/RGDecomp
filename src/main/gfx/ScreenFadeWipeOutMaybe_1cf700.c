#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ScreenFadeBlockWipeOutMaybe_178120(void *, s32, s32, f32);

s32 ScreenFadeWipeOutMaybe_1cf700(void *p4, s32 a5, s32 a6, f32 fa0)
{
    return ScreenFadeBlockWipeOutMaybe_178120((u8 *)p4 + 0x5980, a5, a6, fa0);
}
