#include "types.h"

/* Address of the static object D_004DCB10.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004DCB10[];

void *GetEventObjMgr_2d1960(void)
{
    return D_004DCB10;
}
