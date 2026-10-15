#include "types.h"

/* Address of the static object D_004D3A80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D3A80[];

void *MesItemNameTableAlt_2776f0(void)
{
    return D_004D3A80;
}
