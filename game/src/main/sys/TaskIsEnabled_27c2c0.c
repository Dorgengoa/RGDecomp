/* rgp:protos */
#define RGP_SELF_TaskIsEnabled_27c2c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern u8 D_004D7FA0[];

/*rgp*/

s32 TaskIsEnabled_27c2c0(s32 a4)
{
    return TaskTableIsEnabledByName_1f5540(D_004D7FA0, a4);
}
