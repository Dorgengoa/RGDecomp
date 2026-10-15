#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 CollFrameTreeCollectTris_16bfb0(s32, s32, s32, s32, s32);

s32 CollFrameTreeCollectTrisFwd_16c180(s32 a4, s32 a5, s32 a6, s32 a7)
{
    return CollFrameTreeCollectTris_16bfb0(a4, 3, a5, a6, a7);
}
