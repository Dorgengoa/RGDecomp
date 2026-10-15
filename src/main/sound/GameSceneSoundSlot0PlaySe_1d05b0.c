#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundSlotPlaySe_1d1a50(void *, s32);

s32 GameSceneSoundSlot0PlaySe_1d05b0(void *p4, s32 a5)
{
    return SoundSlotPlaySe_1d1a50((u8 *)p4 + 0xB0B0, a5);
}
