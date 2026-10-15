#include "types.h"

extern void LiveTalkStep_321240(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482B60;

void TaskStepLiveTalk_321210(void)
{
    LiveTalkStep_321240(&D_00482B60);
}
