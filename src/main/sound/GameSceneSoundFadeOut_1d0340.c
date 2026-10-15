#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 GameSceneSoundFadeVolume_1d0370(s32, s32, f32);

s32 GameSceneSoundFadeOut_1d0340(s32 a4, s32 a5)
{
    return GameSceneSoundFadeVolume_1d0370(a4, a5, 0.0f);
}
