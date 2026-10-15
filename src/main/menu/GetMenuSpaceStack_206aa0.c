#include "types.h"

/* Address of the static object D_004BBDA0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBDA0[];

void *GetMenuSpaceStack_206aa0(void)
{
    return D_004BBDA0;
}
