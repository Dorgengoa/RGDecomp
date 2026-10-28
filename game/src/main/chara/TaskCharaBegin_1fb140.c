/* rgp:protos */
#define RGP_SELF_TaskCharaBegin_1fb140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004B8680[];

/*rgp*/

s32 TaskCharaBegin_1fb140(void)
{
    return ActionMgrPreUpdateAll_232c00(D_004B8680);
}
