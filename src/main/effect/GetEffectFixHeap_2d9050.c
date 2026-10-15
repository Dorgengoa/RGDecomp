#include "types.h"

/* Address of the static object D_004DCCF0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004DCCF0[];

void *GetEffectFixHeap_2d9050(void)
{
    return D_004DCCF0;
}
