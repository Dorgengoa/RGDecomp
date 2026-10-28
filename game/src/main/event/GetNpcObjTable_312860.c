/* rgp:protos */
#define RGP_SELF_GetNpcObjTable_312860 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004E72B0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004E72B0[];

void *GetNpcObjTable_312860(void)
{
    return D_004E72B0;
}
