#include "types.h"

/* Address of the static object D_004B69C0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B69C0[];

void *GetCharaDataMgr_1fdb70(void)
{
    return D_004B69C0;
}
