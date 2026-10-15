#include "types.h"

/* Address of the static object D_004E7BA0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E7BA0[];

void *GetSysTextStyle_313570(void)
{
    return D_004E7BA0;
}
