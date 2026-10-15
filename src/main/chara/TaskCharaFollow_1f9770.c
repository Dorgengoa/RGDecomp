#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

extern s32 ActionMgrFollowUpdateAll_2316d0(void *);

s32 TaskCharaFollow_1f9770(void)
{
    return ActionMgrFollowUpdateAll_2316d0(D_004B8680);
}
