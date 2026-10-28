/* rgp:protos */
#define RGP_SELF_GetNavMgr_2d1950 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004DCCC0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004DCCC0[];

void *GetNavMgr_2d1950(void)
{
    return D_004DCCC0;
}
