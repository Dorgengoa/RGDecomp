#include "types.h"

/* Address of the static object D_004B2C80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B2C80[];

void *GetSysParamTable_1c6be0(void)
{
    return D_004B2C80;
}
