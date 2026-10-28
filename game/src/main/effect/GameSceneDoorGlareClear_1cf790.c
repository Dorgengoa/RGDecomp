/* rgp:protos */
#define RGP_SELF_GameSceneDoorGlareClear_1cf790 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneDoorGlareClear_1cf790(void *p4, int rgp_a1)
{
    return (DoorGlareParamsClear_1ce720((u8 *)p4 + 0x5934, (int)rgp_a1), (s32)0);
}
