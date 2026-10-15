#include "types.h"

/* Write the small-data s32 D_004837B4.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004837B4;

void CharaRecSetGameData_3a6e70(s32 value)
{
    D_004837B4 = value;
}
