#include "types.h"

/* Write the small-data s32 D_004837BC.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004837BC;

void CharaEventLogSetGameData_3a6a20(s32 value)
{
    D_004837BC = value;
}
