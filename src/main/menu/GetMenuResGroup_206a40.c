#include "types.h"

/* Address of the static object D_004BC0A0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BC0A0[];

void *GetMenuResGroup_206a40(void)
{
    return D_004BC0A0;
}
