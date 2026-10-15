#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MapCaptionSetOffsetY_33f1f0(void *, s32);

s32 MapMgrCaptionSetOffsetY_1e2640(void *p4, s32 a5)
{
    return MapCaptionSetOffsetY_33f1f0((u8 *)p4 + 0x18E8, a5);
}
