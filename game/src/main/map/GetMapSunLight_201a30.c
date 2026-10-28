/* rgp:protos */
#define RGP_SELF_GetMapSunLight_201a30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BB6C0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB6C0[];

void *GetMapSunLight_201a30(void)
{
    return D_004BB6C0;
}
