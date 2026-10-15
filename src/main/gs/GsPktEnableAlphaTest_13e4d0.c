#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GsTestSetAlphaTest_157100(void *, s32);

s32 GsPktEnableAlphaTest_13e4d0(void *p4, s32 a5)
{
    return GsTestSetAlphaTest_157100((u8 *)p4 + 0x10, a5);
}
