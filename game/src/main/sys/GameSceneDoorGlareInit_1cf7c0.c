/* rgp:protos */
#define RGP_SELF_GameSceneDoorGlareInit_1cf7c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneDoorGlareInit_1cf7c0(void *p4)
{
    return ((s32)DoorGlareParamsInit_1ce8a0((u8 *)p4 + 0x5934));
}
