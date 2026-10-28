/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot4GetVolume_1d0770 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

float GameSceneSoundSlot4GetVolume_1d0770(void *p4)
{
    return SoundSlotGetVolume_1d2120((u8 *)p4 + 0xB2D0);
}
