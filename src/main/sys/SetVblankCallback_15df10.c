#include "types.h"

/* Write the small-data s32 D_004810D0.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004810D0;

void SetVblankCallback_15df10(s32 value)
{
    D_004810D0 = value;
}
