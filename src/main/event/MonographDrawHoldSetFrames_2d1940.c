#include "types.h"

/* Write the small-data s32 D_00482634.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_00482634;

void MonographDrawHoldSetFrames_2d1940(s32 value)
{
    D_00482634 = value;
}
