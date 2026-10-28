/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot4FadeIn_1d0600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot4FadeIn_1d0600(void *p4, int rgp_a1)
{
    return SoundSlotFadeIn_1d1f80((u8 *)p4 + 0xB2D0, (int)rgp_a1);
}
