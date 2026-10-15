#include "types.h"

extern void memset(s32, s32, s32);
extern void strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EntrySetName_323910(s32 p0, s32 p1)
{
    memset((p0 + 0x54), 0, 0x22);
    if (p1 != 0) {
        strcpy((p0 + 0x54), p1);
    }
}
