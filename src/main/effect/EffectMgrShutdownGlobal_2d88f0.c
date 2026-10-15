#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004DCD50[];

extern s32 EffectMgrShutdown_2e3140(void *);

s32 EffectMgrShutdownGlobal_2d88f0(void)
{
    return EffectMgrShutdown_2e3140(D_004DCD50);
}
