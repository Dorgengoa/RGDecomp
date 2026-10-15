#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s16 D_004B3350;
extern const s16 D_004B3352;

void StaticInitMovieRead_46a110(void)
{
    *(s16 *)&D_004B3350 = 0;
    *(s16 *)&D_004B3352 = 0;
}
