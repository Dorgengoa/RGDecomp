#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundSlotPlaySeVol_1d1ab0(void *, s32, f32);

s32 GameSceneSoundSlot5PlaySeVol_1d05d0(void *p4, s32 a5, f32 fa0)
{
    return SoundSlotPlaySeVol_1d1ab0((u8 *)p4 + 0xB358, a5, fa0);
}
