#include "types.h"

/* Address of the static object D_004BB570.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB570[];

void *GetLensFlareMgr_201a40(void)
{
    return D_004BB570;
}
