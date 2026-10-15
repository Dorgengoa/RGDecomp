#include "types.h"

extern s32 SceneSoundGetSlot0HandleCur_207df0(void);
extern void SoundPlayDefault_1b9ae0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ScenePlaySe_277690(s32 p0)
{
    s32 r0;

    r0 = SceneSoundGetSlot0HandleCur_207df0();
    SoundPlayDefault_1b9ae0(r0, p0, 0);
}
