#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 MsgGetTextByIndex_279040(s32);

s32 DiscStatusMessageGetText_39ecd0(void)
{
    return MsgGetTextByIndex_279040(0x2E);
}
