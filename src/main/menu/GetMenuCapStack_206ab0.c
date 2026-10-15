#include "types.h"

/* Address of the static object D_004BBC20.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BBC20[];

void *GetMenuCapStack_206ab0(void)
{
    return D_004BBC20;
}
