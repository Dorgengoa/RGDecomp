#include "types.h"

/* Write the small-data s32 D_00482B90.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_00482B90;

void SetEntryTableGlobal_32c2d0(s32 value)
{
    D_00482B90 = value;
}
