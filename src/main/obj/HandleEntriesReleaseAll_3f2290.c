#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 HandleEntriesReleaseExcept_3f0b90(s32, s32);

s32 HandleEntriesReleaseAll_3f2290(s32 a4)
{
    return HandleEntriesReleaseExcept_3f0b90(a4, -1);
}
