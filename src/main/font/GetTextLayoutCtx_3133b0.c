#include "types.h"

/* Address of the static object D_004E74F0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E74F0[];

void *GetTextLayoutCtx_3133b0(void)
{
    return D_004E74F0;
}
