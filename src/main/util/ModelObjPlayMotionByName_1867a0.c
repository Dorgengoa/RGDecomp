#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MotionListSelectByNameAll_1720b0(void *, s32, s32);

s32 ModelObjPlayMotionByName_1867a0(void *p4, s32 a5, s32 a6)
{
    return MotionListSelectByNameAll_1720b0((u8 *)p4 + 0x1F0, a5, a6);
}
