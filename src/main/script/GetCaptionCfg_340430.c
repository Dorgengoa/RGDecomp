#include "types.h"

/* Address of the static object D_004E8850.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E8850[];

void *GetCaptionCfg_340430(void)
{
    return D_004E8850;
}
