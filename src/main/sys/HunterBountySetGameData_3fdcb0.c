#include "types.h"

/* Write the small-data s32 D_00483B28.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_00483B28;

void HunterBountySetGameData_3fdcb0(s32 value)
{
    D_00483B28 = value;
}
