/* rgp:protos */
#define RGP_SELF_GetAbilityReq_27a640 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the static object D_004D7C70.  It is not four bytes wide, so mwcc gives it %hi/%lo without needing const. */

extern u8 D_004D7C70[];

void *GetAbilityReq_27a640(void)
{
    return D_004D7C70;
}
