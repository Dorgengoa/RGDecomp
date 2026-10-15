#include "types.h"

extern s32 strlen(s32);
extern void strcpy(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MotionEventSeSetName_1b1800(s32 p0, s32 p1)
{
    s32 r0;

    if (p1 != 0) {
        r0 = strlen(p1);
        if ((u32)r0 < 8) {
            strcpy((p0 + 0x30), p1);
        }
    }
}
