/* rgp:protos */
#define RGP_SELF_GetLoaderMgr_1f59d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B5160.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B5160[];

void *GetLoaderMgr_1f59d0(void)
{
    return D_004B5160;
}
