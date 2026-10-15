#include "types.h"

extern void HatenaMarkListStep_344ee0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482DE0;

void HatenaMarkStepAll_345d60(void)
{
    HatenaMarkListStep_344ee0(&D_00482DE0);
}
