#include "types.h"

/* Address of the static object D_004E7FB0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E7FB0[];

void *InsectBattleGetMemStack_31a8c0(void)
{
    return D_004E7FB0;
}
