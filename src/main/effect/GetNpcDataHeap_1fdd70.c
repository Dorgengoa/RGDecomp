#include "types.h"

/* Address of the static object D_004B6920.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B6920[];

void *GetNpcDataHeap_1fdd70(void)
{
    return D_004B6920;
}
