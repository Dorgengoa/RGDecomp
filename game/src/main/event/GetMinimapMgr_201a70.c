/* rgp:protos */
#define RGP_SELF_GetMinimapMgr_201a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BAF50.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BAF50[];

void *GetMinimapMgr_201a70(void)
{
    return D_004BAF50;
}
