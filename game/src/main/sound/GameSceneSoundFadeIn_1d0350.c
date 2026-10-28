/* rgp:protos */
#define RGP_SELF_GameSceneSoundFadeIn_1d0350 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

/*rgp*/

s32 GameSceneSoundFadeIn_1d0350(s32 a4, s32 a5)
{
    return (GameSceneSoundFadeVolume_1d0370(a4, a5, 1.0f), (s32)0);
}
