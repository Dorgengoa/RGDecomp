#include "types.h"

/* Address of the static object D_00445ED0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_00445ED0[];

void *sceGsGetGParam_1082a0(void)
{
    return D_00445ED0;
}
