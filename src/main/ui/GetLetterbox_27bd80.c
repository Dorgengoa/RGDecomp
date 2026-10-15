#include "types.h"

/* Address of the static object D_004D7810.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D7810[];

void *GetLetterbox_27bd80(void)
{
    return D_004D7810;
}
