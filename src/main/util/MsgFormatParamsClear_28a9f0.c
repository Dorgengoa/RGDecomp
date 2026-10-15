#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 memset(s32, s32, s32);

s32 MsgFormatParamsClear_28a9f0(s32 a4)
{
    return memset(a4, 0, 0xAC);
}
