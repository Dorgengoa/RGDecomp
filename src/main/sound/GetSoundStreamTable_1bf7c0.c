#include "types.h"

/* Address of the static object D_004A3AC0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004A3AC0[];

void *GetSoundStreamTable_1bf7c0(void)
{
    return D_004A3AC0;
}
