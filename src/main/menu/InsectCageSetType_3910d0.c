#include "types.h"

/* Write the small-data u8 D_00483330.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_00483330;

void InsectCageSetType_3910d0(u8 value)
{
    D_00483330 = value;
}
