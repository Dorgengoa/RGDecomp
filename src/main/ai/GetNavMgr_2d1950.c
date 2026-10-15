#include "types.h"

/* Address of the static object D_004DCCC0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004DCCC0[];

void *GetNavMgr_2d1950(void)
{
    return D_004DCCC0;
}
