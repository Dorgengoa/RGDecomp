#include "types.h"

/* Write the small-data u8 D_004819AC.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_004819AC;

void SetGameExitRequest_1f57d0(u8 value)
{
    D_004819AC = value;
}
