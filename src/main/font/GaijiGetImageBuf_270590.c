#include "types.h"

/* Address of the static object D_004C3180.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004C3180[];

void *GaijiGetImageBuf_270590(void)
{
    return D_004C3180;
}
