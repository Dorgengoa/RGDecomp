#include "types.h"

/* Address of the static object D_004B2570.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B2570[];

void *GetPad0_1c6c60(void)
{
    return D_004B2570;
}
