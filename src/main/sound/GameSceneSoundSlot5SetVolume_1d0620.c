#include "types.h"

/* Tail-call adapter: marshal and forward.  The callee arity is the
   w1_arity read-before-write scan; a register overwritten without
   being read may hide an ignored parameter the bytes cannot see. */

extern s32 SoundSlotSetVolumeNow_1d2020(void *, f32);

s32 GameSceneSoundSlot5SetVolume_1d0620(void *p4, f32 fa0)
{
    return SoundSlotSetVolumeNow_1d2020((u8 *)p4 + 0xB358, fa0);
}
