#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 ArenaAllocAligned_370330(s32, s32, s32, s32);

s32 ArenaNew_3f7400(s32 a4, s32 a5, s32 a6, s32 a7)
{
    return ArenaAllocAligned_370330(a5, a4, a6, a7);
}
