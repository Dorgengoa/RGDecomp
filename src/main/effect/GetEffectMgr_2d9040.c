#include "types.h"

/* Address of the static object D_004DCD50.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004DCD50[];

void *GetEffectMgr_2d9040(void)
{
    return D_004DCD50;
}
