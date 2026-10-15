#include "types.h"

extern s32 SaveCalcSizeKBCurrent_37b920(void);
extern void McCardCheckFreeSpace_376220(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SaveCheckCardFreeSpace_37b980(s32 p0)
{
    s32 r0;

    r0 = SaveCalcSizeKBCurrent_37b920();
    McCardCheckFreeSpace_376220(p0, r0);
}
