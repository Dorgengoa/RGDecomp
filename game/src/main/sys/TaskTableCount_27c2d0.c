/* rgp:protos */
#define RGP_SELF_TaskTableCount_27c2d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

/*rgp*/

s32 TaskTableCount_27c2d0(void)
{
    return TaskTableCountEntries_1f5570(D_004D7FA0);
}
