#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MinimapSetAllExplored_32b6d0(s32, s32);

s32 MinimapSetCurAllExplored_32b6c0(s32 a4)
{
    return MinimapSetAllExplored_32b6d0(a4, 0);
}
