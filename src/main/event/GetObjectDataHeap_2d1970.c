#include "types.h"

/* Address of the static object D_004DCAB0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004DCAB0[];

void *GetObjectDataHeap_2d1970(void)
{
    return D_004DCAB0;
}
