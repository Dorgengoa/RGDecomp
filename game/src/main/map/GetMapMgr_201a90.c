/* rgp:protos */
#define RGP_SELF_GetMapMgr_201a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B8C70.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B8C70[];

void *GetMapMgr_201a90(void)
{
    return D_004B8C70;
}
