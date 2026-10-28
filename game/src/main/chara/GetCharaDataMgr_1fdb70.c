/* rgp:protos */
#define RGP_SELF_GetCharaDataMgr_1fdb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004B69C0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004B69C0[];

void *GetCharaDataMgr_1fdb70(void)
{
    return D_004B69C0;
}
