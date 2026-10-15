#include "types.h"

extern void StatusEffectDraw_33c100(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004826B0;

void TaskDrawStatusEffect_2d85b0(void)
{
    StatusEffectDraw_33c100(&D_004826B0);
}
