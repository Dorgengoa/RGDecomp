/* rgp:protos */
#define RGP_SELF_GameSceneSoundSlot4FadeTo_1d0610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundSlot4FadeTo_1d0610(void *p4, s32 a5, f32 fa0)
{
    return (SoundSlotFadeTo_1d1fa0((u8 *)p4 + 0xB2D0, a5, fa0), (s32)0);
}
