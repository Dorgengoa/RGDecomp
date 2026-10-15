#include "types.h"

/* Write the small-data u8 D_00481A18.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_00481A18;

void CameraSnapReqAt_1f6d70(u8 value)
{
    D_00481A18 = value;
}
