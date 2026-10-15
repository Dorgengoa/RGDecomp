#include "types.h"

/* Address of the static object D_004A4F80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004A4F80[];

void *SysGetSoundThreadStack_1c3530(void)
{
    return D_004A4F80;
}
