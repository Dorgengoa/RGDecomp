#include "types.h"

extern void sceCdInit_12a008(s32, s32, s32, s32);
extern void sceCdMmode_12ada0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void CdInitDvdMode_15e5d0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    sceCdInit_12a008(0, p1, p2, p3);
    sceCdMmode_12ada0(2);
}
