#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 StreamChanSetSaveResumeReq_1d70b0(s32, s32);

s32 StreamChanSaveResumePoint_1d6b00(s32 a4)
{
    return StreamChanSetSaveResumeReq_1d70b0(a4, 1);
}
