#include "types.h"

/* Address of the static object D_004B8700.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B8700[];

void *GetInsectCageMgr_1fdb30(void)
{
    return D_004B8700;
}
