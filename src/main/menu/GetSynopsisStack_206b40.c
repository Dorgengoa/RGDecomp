#include "types.h"

/* Address of the static object D_004BB950.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB950[];

void *GetSynopsisStack_206b40(void)
{
    return D_004BB950;
}
