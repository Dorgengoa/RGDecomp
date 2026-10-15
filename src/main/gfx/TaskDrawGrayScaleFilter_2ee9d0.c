#include "types.h"

extern s32 GetCurrentScene_1f5be0(void);
extern void GameSceneTintApply_1ce8f0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawGrayScaleFilter_2ee9d0(void)
{
    s32 r0;

    r0 = GetCurrentScene_1f5be0();
    GameSceneTintApply_1ce8f0(r0);
}
