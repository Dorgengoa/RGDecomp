/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot4SetVolume_1d0630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot4SetVolume_1d0630(void *p4, f32 fa0)
{
    return (SoundSlotSetVolumeNow_1d2020((u8 *)p4 + 0xB2D0, fa0), (s32)0);
}
