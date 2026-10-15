#include "types.h"

/* Address of the static object D_004BC910.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BC910[];

void *GetStreamMgr_207ea0(void)
{
    return D_004BC910;
}
