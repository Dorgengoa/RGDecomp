#include "types.h"

/* Address of the static object D_004BB8F0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB8F0[];

void *GetReadBuffHeap_2025e0(void)
{
    return D_004BB8F0;
}
