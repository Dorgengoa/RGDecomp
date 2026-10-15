#include "types.h"

/* Address of the static object D_004B6800.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B6800[];

void *GetCameraFollowParams_1f6d80(void)
{
    return D_004B6800;
}
