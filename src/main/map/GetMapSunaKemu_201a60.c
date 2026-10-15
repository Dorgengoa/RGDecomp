#include "types.h"

/* Address of the static object D_004BB480.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB480[];

void *GetMapSunaKemu_201a60(void)
{
    return D_004BB480;
}
