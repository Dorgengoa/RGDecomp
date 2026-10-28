/* rgp:protos */
#define RGP_SELF_GetMenuPartySnapshot_205870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004BB9B0.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004BB9B0[];

void *GetMenuPartySnapshot_205870(void)
{
    return D_004BB9B0;
}
