#include "types.h"

/* Address of the static object D_004D3B80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D3B80[];

void *MesMgrGetSharedWin_277710(void)
{
    return D_004D3B80;
}
