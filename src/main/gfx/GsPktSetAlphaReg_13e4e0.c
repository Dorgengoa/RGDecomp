#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GsEnvSetAlpha_157140(void *, s32);

s32 GsPktSetAlphaReg_13e4e0(void *p4, s32 a5)
{
    return GsEnvSetAlpha_157140((u8 *)p4 + 0x10, a5);
}
