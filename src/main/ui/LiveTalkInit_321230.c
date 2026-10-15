#include "types.h"

extern void LiveTalkSlotsInit_3216c0(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482B60;

void LiveTalkInit_321230(void)
{
    LiveTalkSlotsInit_3216c0(&D_00482B60);
}
