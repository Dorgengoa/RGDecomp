#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundSlotFadeTo_1d1fa0(void *, s32, f32);

s32 GameSceneSoundSlot4FadeTo_1d0610(void *p4, s32 a5, f32 fa0)
{
    return SoundSlotFadeTo_1d1fa0((u8 *)p4 + 0xB2D0, a5, fa0);
}
