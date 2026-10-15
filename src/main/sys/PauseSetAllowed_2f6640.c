#include "types.h"

/* Write the small-data u8 D_00482774.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_00482774;

void PauseSetAllowed_2f6640(u8 value)
{
    D_00482774 = value;
}
