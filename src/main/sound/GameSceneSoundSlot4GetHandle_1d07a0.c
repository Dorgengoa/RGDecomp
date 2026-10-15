#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundSlotGetHandle_1d2150(void *);

s32 GameSceneSoundSlot4GetHandle_1d07a0(void *p4)
{
    return SoundSlotGetHandle_1d2150((u8 *)p4 + 0xB2D0);
}
