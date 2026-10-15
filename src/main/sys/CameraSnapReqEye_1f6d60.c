#include "types.h"

/* Write the small-data u8 D_00481A1C.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern u8 D_00481A1C;

void CameraSnapReqEye_1f6d60(u8 value)
{
    D_00481A1C = value;
}
