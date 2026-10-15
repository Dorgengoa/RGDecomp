#include "types.h"

/* Address of the static object D_004BBEC0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBEC0[];

void *GetMenuEasyStack_206a80(void)
{
    return D_004BBEC0;
}
