#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MemStackHeapAllocFrontAligned_14dde0(s32, s32, s32);

s32 MemStackHeapAllocFrontAlign64_14dd00(s32 a4, s32 a5)
{
    return MemStackHeapAllocFrontAligned_14dde0(a4, a5, 4);
}
