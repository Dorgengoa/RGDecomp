#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

extern s32 ActionMgrMoveAll_231720(void *);

s32 TaskCharaMove_1f9790(void)
{
    return ActionMgrMoveAll_231720(D_004B8680);
}
