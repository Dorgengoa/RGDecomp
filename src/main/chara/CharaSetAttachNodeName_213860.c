#include "types.h"

extern void strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CharaSetAttachNodeName_213860(s32 p0, s32 p1)
{
    if (p1 != 0) {
        strcpy((p0 + 0xB24), p1);
    }
}
