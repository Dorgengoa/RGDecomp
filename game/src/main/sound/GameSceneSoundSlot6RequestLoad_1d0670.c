/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot6RequestLoad_1d0670 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot6RequestLoad_1d0670(s32 a4, s32 a5, s32 a6)
{
    return GameSceneSoundSlotRequestLoad_1d0b20(a4, 6, a5, a6);
}
