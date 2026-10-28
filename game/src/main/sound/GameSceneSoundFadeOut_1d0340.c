/* rgp:protos */
#define RGP_SELF_GameSceneSoundFadeOut_1d0340 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundFadeOut_1d0340(s32 a4, s32 a5)
{
    return (GameSceneSoundFadeVolume_1d0370(a4, a5, 0.0f), (s32)0);
}
