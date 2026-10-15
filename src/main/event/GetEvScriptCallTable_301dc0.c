#include "types.h"

/* Address of the static object D_00452250.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_00452250[];

void *GetEvScriptCallTable_301dc0(void)
{
    return D_00452250;
}
