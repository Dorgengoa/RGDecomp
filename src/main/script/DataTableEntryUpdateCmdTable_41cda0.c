#include "types.h"

/* Address of the static object D_00467E80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_00467E80[];

void *DataTableEntryUpdateCmdTable_41cda0(void)
{
    return D_00467E80;
}
