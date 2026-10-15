#include "types.h"

/* Address of the static object D_004D7C40.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D7C40[];

void *GetInteractState_27a650(void)
{
    return D_004D7C40;
}
