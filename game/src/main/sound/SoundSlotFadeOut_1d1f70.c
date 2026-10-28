/* rgp:protos */
#define RGP_SELF_SoundSlotFadeOut_1d1f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 SoundSlotFadeOut_1d1f70(s32 a4, s32 a5)
{
    return (SoundSlotFadeTo_1d1fa0(a4, a5, 0.0f), (s32)0);
}
