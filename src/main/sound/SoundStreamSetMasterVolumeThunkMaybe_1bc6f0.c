#include "types.h"

extern void SoundStreamSetMasterVolumeMaybe_1bc6f0(f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SoundStreamSetMasterVolumeThunkMaybe_1bc6f0(f32 fa0)
{
    SoundStreamSetMasterVolumeMaybe_1bc6f0(fa0);
}
