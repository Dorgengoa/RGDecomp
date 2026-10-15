#include "types.h"

/* Write the small-data u8 D_00482778.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_00482778;

void PauseSetRequest_2f6620(u8 value)
{
    D_00482778 = value;
}
