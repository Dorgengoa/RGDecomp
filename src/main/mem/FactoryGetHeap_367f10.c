#include "types.h"

/* Address of the static object D_004E9020.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E9020[];

void *FactoryGetHeap_367f10(void)
{
    return D_004E9020;
}
