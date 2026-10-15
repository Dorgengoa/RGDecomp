#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern void InsectCageMgrUpdate_39a620(void *, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B8700[];

void TaskStepInsectCage_1fb1b0(void)
{
    s32 r0;
    f32 r1;

    r0 = GetCurrentScene_1f5be0();
    r1 = GameSceneGetTimeStep_1ceba0(r0);
    InsectCageMgrUpdate_39a620(D_004B8700, r1);
}
