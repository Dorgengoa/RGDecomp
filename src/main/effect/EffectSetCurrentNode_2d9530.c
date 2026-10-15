#include "types.h"

/* Write the small-data s32 D_004826E0.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004826E0;

void EffectSetCurrentNode_2d9530(s32 value)
{
    D_004826E0 = value;
}
