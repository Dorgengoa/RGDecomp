/* rgp:protos */
#define RGP_SELF_GetWorldDataMgr_1fedf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B8A80.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B8A80[];

void *GetWorldDataMgr_1fedf0(void)
{
    return D_004B8A80;
}
