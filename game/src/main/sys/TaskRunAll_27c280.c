/* rgp:protos */
#define RGP_SELF_TaskRunAll_27c280 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

/*rgp*/

s32 TaskRunAll_27c280(void)
{
    return TaskTableRun_1f5340(D_004D7FA0);
}
