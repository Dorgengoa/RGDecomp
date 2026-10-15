#include "types.h"

/* Address of the static object D_004B4120.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B4120[];

void *GetFileNameSlotTable_1ed0c0(void)
{
    return D_004B4120;
}
