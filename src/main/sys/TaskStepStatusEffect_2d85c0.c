#include "types.h"

extern void StatusEffectStep_33c160(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826B0;

void TaskStepStatusEffect_2d85c0(void)
{
    StatusEffectStep_33c160(&D_004826B0);
}
