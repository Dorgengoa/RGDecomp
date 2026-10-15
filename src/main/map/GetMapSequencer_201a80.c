#include "types.h"

/* Address of the static object D_004BAF20.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BAF20[];

void *GetMapSequencer_201a80(void)
{
    return D_004BAF20;
}
