#include "types.h"

extern void ScreenMarkerTickAll_31c250(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ScreenMarkerTickAllThunk_31c250(s32 p0)
{
    ScreenMarkerTickAll_31c250(p0);
}
