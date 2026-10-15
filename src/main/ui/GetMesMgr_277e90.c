#include "types.h"

/* Address of the static object D_004D5980.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D5980[];

void *GetMesMgr_277e90(void)
{
    return D_004D5980;
}
