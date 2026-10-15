#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00481F30;

void EventCastDataGroupIdFree_250380(void)
{
    if (D_00481F30 > 0) {
        D_00481F30 = (D_00481F30 + -1);
    }
}
