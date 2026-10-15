#include "types.h"

/* Address of the static object D_004B8BB0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B8BB0[];

void *GetMapSkyHeap_201ab0(void)
{
    return D_004B8BB0;
}
