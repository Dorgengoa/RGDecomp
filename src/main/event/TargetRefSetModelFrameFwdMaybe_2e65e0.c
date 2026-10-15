#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 TargetRefSetModelFrame_2e6560(s32, s32, s32, s32, f32);

s32 TargetRefSetModelFrameFwdMaybe_2e65e0(s32 a4, s32 a5, s32 a6, f32 fa0)
{
    return TargetRefSetModelFrame_2e6560(a4, a5, -1, a6, fa0);
}
