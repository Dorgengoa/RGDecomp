#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004DCD50[];

extern s32 EffectMgrLoadPoll_2e3030(void *);

s32 EffectMgrLoadPollGlobal_2d8880(void)
{
    return EffectMgrLoadPoll_2e3030(D_004DCD50);
}
