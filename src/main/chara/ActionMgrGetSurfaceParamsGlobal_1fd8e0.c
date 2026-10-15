#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

extern s32 ActionMgrGetSurfaceParams_233b20(void *);

s32 ActionMgrGetSurfaceParamsGlobal_1fd8e0(void)
{
    return ActionMgrGetSurfaceParams_233b20(D_004B8680);
}
