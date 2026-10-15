#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

extern s32 ActionMgrPreUpdateAll_232c00(void *);

s32 TaskCharaBegin_1fb140(void)
{
    return ActionMgrPreUpdateAll_232c00(D_004B8680);
}
